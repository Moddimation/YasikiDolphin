#include <dolphin/base/PPCArch.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include <stddef.h>

#include "GXPrivate.h"

static OSThread*         __GXCurrentThread;
static GXBool            CPGPLinked;
static BOOL              GXOverflowSuspendInProgress;
static GXBreakPtCallback BreakPointCB;
static u32               __GXOverflowCount;
#if DEBUG
static int IsWGPipeRedirected;
#endif

__GXFifoObj* CPUFifo;
__GXFifoObj* GPFifo;
void*        __GXCurrentBP;

static void __GXFifoReadEnable (void);
static void __GXFifoReadDisable (void);
static void __GXFifoLink (u8 arg0);
static void __GXWriteFifoIntEnable (u8 arg0, u8 arg1);
static void __GXWriteFifoIntReset (u8 arg0, u8 arg1);

#if DEBUG
static s8 __data_0[] = "[GXOverflowHandler]";
#endif

static void
GXOverflowHandler (s16 interrupt, OSContext* context)
{
#pragma unused(interrupt)
#pragma unused(context)

#if DEBUG
    if (__gxVerif->verifyLevel > 1)
    {
        OSReport (__data_0);
    }
#endif
    ASSERTLINE (0x15A, !GXOverflowSuspendInProgress);

    __GXOverflowCount++;
    __GXWriteFifoIntEnable (0, 1);
    __GXWriteFifoIntReset (1, 0);
    GXOverflowSuspendInProgress = TRUE;

#if DEBUG
    if (__gxVerif->verifyLevel > 1)
    {
        OSReport ("[GXOverflowHandler Sleeping]");
    }
#endif
    OSSuspendThread (__GXCurrentThread);
}

static void
GXUnderflowHandler (s16 interrupt, OSContext* context)
{
#pragma unused(interrupt)
#pragma unused(context)

#if DEBUG
    if (__gxVerif->verifyLevel > 1)
    {
        OSReport ("[GXUnderflowHandler]");
    }
#endif
    ASSERTLINE (0x184, GXOverflowSuspendInProgress);

    OSResumeThread (__GXCurrentThread);
    GXOverflowSuspendInProgress = FALSE;
    __GXWriteFifoIntReset (1U, 1U);
    __GXWriteFifoIntEnable (1U, 0U);
}

static void
GXBreakPointHandler (s16 interrupt, OSContext* context)
{
#pragma unused(interrupt)

    OSContext exceptionContext;

    __GXData->cpEnable = __GXData->cpEnable & 0xFFFFFFDF;
    GX_SET_CP_REG (1, __GXData->cpEnable);
    if (BreakPointCB != NULL)
    {
        OSClearContext (&exceptionContext);
        OSSetCurrentContext (&exceptionContext);
        BreakPointCB();
        OSClearContext (&exceptionContext);
        OSSetCurrentContext (context);
    }
}

static void
GXCPInterruptHandler (s16 interrupt, OSContext* context)
{
    __GXData->cpStatus = GX_GET_CP_REG (0);
    if (GET_REG_FIELD (__GXData->cpEnable, 1, 3) && GET_REG_FIELD (__GXData->cpStatus, 1, 1))
    {
        GXUnderflowHandler (interrupt, context);
    }
    if (GET_REG_FIELD (__GXData->cpEnable, 1, 2) && GET_REG_FIELD (__GXData->cpStatus, 1, 0))
    {
        GXOverflowHandler (interrupt, context);
    }
    if (GET_REG_FIELD (__GXData->cpEnable, 1, 5) && GET_REG_FIELD (__GXData->cpStatus, 1, 4))
    {
        GXBreakPointHandler (interrupt, context);
    }
}

void
GXInitFifoBase (GXFifoObj* fifo, void* base, u32 size)
{
    __GXFifoObj* realFifo = (__GXFifoObj*)fifo;

    ASSERTMSGLINE (0x1FF, realFifo != CPUFifo, "GXInitFifoBase: fifo is attached to CPU");
    ASSERTMSGLINE (0x201, realFifo != GPFifo, "GXInitFifoBase: fifo is attached to GP");
    ASSERTMSGLINE (0x203, ((u32)base & 0x1F) == 0, "GXInitFifoBase: base must be 32B aligned");
    ASSERTMSGLINE (0x205, base != NULL, "GXInitFifoBase: base pointer is NULL");
    ASSERTMSGLINE (0x207, (size & 0x1F) == 0, "GXInitFifoBase: size must be 32B aligned");
    ASSERTMSGLINE (0x209, size >= 0x10000, "GXInitFifoBase: fifo is not large enough");

    realFifo->base  = base;
    realFifo->top   = (u8*)base + size - 4;
    realFifo->size  = size;
    realFifo->count = 0;
    GXInitFifoLimits (fifo, size - 0x4000, (size >> 1) & ~0x1F);
    GXInitFifoPtrs (fifo, base, base);
}

void
GXInitFifoPtrs (GXFifoObj* fifo, void* readPtr, void* writePtr)
{
    __GXFifoObj* realFifo = (__GXFifoObj*)fifo;
    BOOL         enabled;

    ASSERTMSGLINE (0x231, realFifo != CPUFifo, "GXInitFifoPtrs: fifo is attached to CPU");
    ASSERTMSGLINE (0x233, realFifo != GPFifo, "GXInitFifoPtrs: fifo is attached to GP");
    ASSERTMSGLINE (0x235,
                   ((u32)readPtr & 0x1F) == 0,
                   "GXInitFifoPtrs: readPtr not 32B aligned");
    ASSERTMSGLINE (0x237,
                   ((u32)writePtr & 0x1F) == 0,
                   "GXInitFifoPtrs: writePtr not 32B aligned");
    ASSERTMSGLINE (0x23A,
                   realFifo->base <= readPtr && readPtr < realFifo->top,
                   "GXInitFifoPtrs: readPtr not in fifo range");
    ASSERTMSGLINE (0x23D,
                   realFifo->base <= writePtr && writePtr < realFifo->top,
                   "GXInitFifoPtrs: writePtr not in fifo range");

    enabled         = OSDisableInterrupts();
    realFifo->rdPtr = readPtr;
    realFifo->wrPtr = writePtr;
    realFifo->count = (u8*)writePtr - (u8*)readPtr;
    if (realFifo->count < 0)
    {
        realFifo->count += realFifo->size;
    }

    OSRestoreInterrupts (enabled);
}

void
GXInitFifoLimits (GXFifoObj* fifo, u32 hiWatermark, u32 loWatermark)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

    ASSERTMSGLINE (0x262, realFifo != GPFifo, "GXInitFifoLimits: fifo is attached to GP");
    ASSERTMSGLINE (0x264,
                   (hiWatermark & 0x1F) == 0,
                   "GXInitFifoLimits: hiWatermark not 32B aligned");
    ASSERTMSGLINE (0x266,
                   (loWatermark & 0x1F) == 0,
                   "GXInitFifoLimits: loWatermark not 32B aligned");
    ASSERTMSGLINE (0x268,
                   hiWatermark < realFifo->top - realFifo->base,
                   "GXInitFifoLimits: hiWatermark too large");
    ASSERTMSGLINE (0x26A,
                   loWatermark < hiWatermark,
                   "GXInitFifoLimits: hiWatermark below lo watermark");

    realFifo->hiWatermark = hiWatermark;
    realFifo->loWatermark = loWatermark;
}

void
GXSetCPUFifo (GXFifoObj* fifo)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
    BOOL         enabled  = OSDisableInterrupts();

    CPUFifo               = realFifo;
    if (CPUFifo == GPFifo)
    {
        u32 reg = 0;

        GX_SET_PI_REG (3, (u32)realFifo->base & 0x3FFFFFFF);
        GX_SET_PI_REG (4, (u32)realFifo->top & 0x3FFFFFFF);
        SET_REG_FIELD (0x294, reg, 21, 5, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 5);
        SET_REG_FIELD (0x295, reg, 1, 26, 0);
        GX_SET_PI_REG (5, reg);
        CPGPLinked = GX_TRUE;
        __GXWriteFifoIntReset (1, 1);
        __GXWriteFifoIntEnable (1, 0);
        __GXFifoLink (1);
    }
    else
    {
        u32 reg;

        if (CPGPLinked)
        {
            __GXFifoLink (0);
            CPGPLinked = GX_FALSE;
        }
        __GXWriteFifoIntEnable (0, 0);
        reg = 0;
        GX_SET_PI_REG (3, (u32)realFifo->base & 0x3FFFFFFF);
        GX_SET_PI_REG (4, (u32)realFifo->top & 0x3FFFFFFF);
        SET_REG_FIELD (0x2B7, reg, 21, 5, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 5);
        SET_REG_FIELD (0x2B8, reg, 1, 26, 0);
        GX_SET_PI_REG (5, reg);
    }
    __sync();

    OSRestoreInterrupts (enabled);
}

void
GXSetGPFifo (GXFifoObj* fifo)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
    BOOL         enabled  = OSDisableInterrupts();

    __GXFifoReadDisable();
    __GXWriteFifoIntEnable (0, 0);
    GPFifo = realFifo;

    GX_SET_CP_REG (16, (u32)realFifo->base & 0xFFFF);
    GX_SET_CP_REG (18, (u32)realFifo->top & 0xFFFF);
    GX_SET_CP_REG (24, realFifo->count & 0xFFFF);
    GX_SET_CP_REG (26, (u32)realFifo->wrPtr & 0xFFFF);
    GX_SET_CP_REG (28, (u32)realFifo->rdPtr & 0xFFFF);
    GX_SET_CP_REG (20, (u32)realFifo->hiWatermark & 0xFFFF);
    GX_SET_CP_REG (22, (u32)realFifo->loWatermark & 0xFFFF);
    GX_SET_CP_REG (17, ((u32)realFifo->base & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG (19, ((u32)realFifo->top & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG (25, realFifo->count >> 16);
    GX_SET_CP_REG (27, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG (29, ((u32)realFifo->rdPtr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG (21, (u32)realFifo->hiWatermark >> 16);
    GX_SET_CP_REG (23, (u32)realFifo->loWatermark >> 16);

    __sync();

    if (CPUFifo == GPFifo)
    {
        CPGPLinked = GX_TRUE;
        __GXWriteFifoIntEnable (1, 0);
        __GXFifoLink (1);
    }
    else
    {
        CPGPLinked = GX_FALSE;
        __GXWriteFifoIntEnable (0, 0);
        __GXFifoLink (0);
    }
    __GXWriteFifoIntReset (1, 1);
    __GXFifoReadEnable();

    OSRestoreInterrupts (enabled);
}

void
GXSaveCPUFifo (GXFifoObj* fifo)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
    ASSERTMSGLINE (0x321, realFifo == CPUFifo, "GXSaveCPUFifo: fifo is not attached to CPU");
    __GXSaveCPUFifoAux (realFifo);
}

#define SOME_MACRO1(fifo)                                                                      \
    do {                                                                                       \
        u32 temp     = (u32)GX_GET_CP_REG (29) << 16;                                          \
        temp        |= GX_GET_CP_REG (28);                                                     \
        fifo->rdPtr  = OSPhysicalToCached (temp);                                              \
    }                                                                                          \
    while (0)

#define SOME_MACRO2(fifo)                                                                      \
    do {                                                                                       \
        s32 temp     = (s32)GX_GET_CP_REG (25) << 16;                                          \
        temp        |= GX_GET_CP_REG (24);                                                     \
        fifo->count  = temp;                                                                   \
    }                                                                                          \
    while (0)

void
__GXSaveCPUFifoAux (__GXFifoObj* realFifo)
{
    BOOL enabled = OSDisableInterrupts();

    GXFlush();

    realFifo->base  = OSPhysicalToCached (GX_GET_PI_REG (3));
    realFifo->top   = OSPhysicalToCached (GX_GET_PI_REG (4));
    realFifo->wrPtr = OSPhysicalToCached (GX_GET_PI_REG (5) & 0xFBFFFFFF);

    if (CPGPLinked)
    {
        SOME_MACRO1 (realFifo);
        SOME_MACRO2 (realFifo);
    }
    else
    {
        realFifo->count = (u8*)realFifo->wrPtr - (u8*)realFifo->rdPtr;
        if (realFifo->count < 0)
        {
            realFifo->count += realFifo->size;
        }
    }
    OSRestoreInterrupts (enabled);
}

void
GXSaveGPFifo (GXFifoObj* fifo)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
    u32          cpStatus;
    u16          readIdle;
    u32          temp;
#pragma unused(temp)

    ASSERTMSGLINE (0x36A, realFifo == GPFifo, "GXSaveGPFifo: fifo is not attached to GP");

    cpStatus = GX_GET_CP_REG (0);
    readIdle = (u16)GET_REG_FIELD (cpStatus, 1, 2);

    ASSERTMSGLINE (0x371, readIdle, "GXSaveGPFifo: GP is not idle");

    SOME_MACRO1 (realFifo);
    SOME_MACRO2 (realFifo);
}

void
GXGetGPStatus (GXBool* overhi,
               GXBool* underlow,
               GXBool* readIdle,
               GXBool* cmdIdle,
               GXBool* brkpt)
{
    __GXData->cpStatus = GX_GET_CP_REG (0);
    *overhi            = (u8)GET_REG_FIELD (__GXData->cpStatus, 1, 0);
    *underlow          = (u8)GET_REG_FIELD (__GXData->cpStatus, 1, 1);
    *readIdle          = (u8)GET_REG_FIELD (__GXData->cpStatus, 1, 2);
    *cmdIdle           = (u8)GET_REG_FIELD (__GXData->cpStatus, 1, 3);
    *brkpt             = (u8)GET_REG_FIELD (__GXData->cpStatus, 1, 4);
}

void
GXGetFifoStatus (GXFifoObj* fifo,
                 GXBool*    overhi,
                 GXBool*    underflow,
                 u32*       fifoCount,
                 GXBool*    cpuWrite,
                 GXBool*    gpRead,
                 GXBool*    fifowrap)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

    *underflow            = GX_FALSE;
    *overhi               = GX_FALSE;
    *fifoCount            = 0;
    *fifowrap             = GX_FALSE;

    if (realFifo == GPFifo)
    {
        SOME_MACRO1 (realFifo);
        SOME_MACRO2 (realFifo);
    }

    if (realFifo == CPUFifo)
    {
        __GXSaveCPUFifoAux (realFifo);
        *fifowrap = (u8)GET_REG_FIELD (GX_GET_PI_REG (5), 1, 26);
    }

    *overhi    = (realFifo->count > realFifo->hiWatermark);
    *underflow = (realFifo->count < realFifo->loWatermark);
    *fifoCount = (u32)(realFifo->count);
    *cpuWrite  = (CPUFifo == realFifo);
    *gpRead    = (GPFifo == realFifo);
}

void
GXGetFifoPtrs (GXFifoObj* fifo, void** readPtr, void** writePtr)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

    ASSERTMSGLINE (0x3F2,
                   realFifo == CPUFifo || realFifo == GPFifo,
                   "GXGetFifoPtrs: fifo is not CPU or GP fifo");

    if (realFifo == CPUFifo)
    {
        realFifo->wrPtr = OSPhysicalToCached (GX_GET_PI_REG (5) & 0xFBFFFFFF);
    }
    if (realFifo == GPFifo)
    {
        SOME_MACRO1 (realFifo);
        SOME_MACRO2 (realFifo);
    }
    else
    {
        realFifo->count = (u8*)realFifo->wrPtr - (u8*)realFifo->rdPtr;
        if (realFifo->count < 0)
        {
            realFifo->count += realFifo->size;
        }
    }
    *readPtr  = realFifo->rdPtr;
    *writePtr = realFifo->wrPtr;
}

void*
GXGetFifoBase (GXFifoObj* fifo)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

    return realFifo->base;
}

u32
GXGetFifoSize (GXFifoObj* fifo)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

    return realFifo->size;
}

void
GXGetFifoLimits (GXFifoObj* fifo, u32* hi, u32* lo)
{
    __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

    *hi                   = realFifo->hiWatermark;
    *lo                   = realFifo->loWatermark;
}

GXBreakPtCallback
GXSetBreakPtCallback (GXBreakPtCallback cb)
{
    GXBreakPtCallback oldcb   = BreakPointCB;
    BOOL              enabled = OSDisableInterrupts();

    BreakPointCB              = cb;
    OSRestoreInterrupts (enabled);

    return oldcb;
}

void* __GXCurrentBP;

void
GXEnableBreakPt (void* break_pt)
{
    BOOL enabled = OSDisableInterrupts();

    __GXFifoReadDisable();
    ASSERTMSGLINE (0x44A,
                   (u8*)break_pt >= GPFifo->base && (u8*)break_pt <= GPFifo->top,
                   "GXEnableBreakPt: Break point value not in fifo range");
    GX_SET_CP_REG (30, (u32)break_pt);
    GX_SET_CP_REG (31, ((u32)break_pt >> 16) & 0x3FFF);
    __GXData->cpEnable = (__GXData->cpEnable & 0xFFFFFFFD) | 2;
    __GXData->cpEnable = (__GXData->cpEnable & 0xFFFFFFDF) | 0x20;
    GX_SET_CP_REG (1, __GXData->cpEnable);
    __GXCurrentBP = break_pt;
    __GXFifoReadEnable();

    OSRestoreInterrupts (enabled);
}

void
GXDisableBreakPt (void)
{
    BOOL enabled       = OSDisableInterrupts();

    __GXData->cpEnable = __GXData->cpEnable & 0xFFFFFFFD;
    __GXData->cpEnable = __GXData->cpEnable & 0xFFFFFFDF;
    GX_SET_CP_REG (1, __GXData->cpEnable);
    __GXCurrentBP = NULL;
    OSRestoreInterrupts (enabled);
}

void
__GXFifoInit (void)
{
    __OSSetInterruptHandler (0x11, GXCPInterruptHandler);
    __OSUnmaskInterrupts (0x4000);
    __GXCurrentThread           = OSGetCurrentThread();
    GXOverflowSuspendInProgress = FALSE;
}

static void
__GXFifoReadEnable (void)
{
    SET_REG_FIELD (0, __GXData->cpEnable, 1, 0, 1);
    GX_SET_CP_REG (1, __GXData->cpEnable);
}

static void
__GXFifoReadDisable (void)
{
    SET_REG_FIELD (0, __GXData->cpEnable, 1, 0, 0);
    GX_SET_CP_REG (1, __GXData->cpEnable);
}

static void
__GXFifoLink (u8 en)
{
    SET_REG_FIELD (0x4B0, __GXData->cpEnable, 1, 4, (en != 0) ? 1 : 0);
    GX_SET_CP_REG (1, __GXData->cpEnable);
}

static void
__GXWriteFifoIntEnable (u8 hiWatermarkEn, u8 loWatermarkEn)
{
    SET_REG_FIELD (0x4C6, __GXData->cpEnable, 1, 2, hiWatermarkEn);
    SET_REG_FIELD (0x4C7, __GXData->cpEnable, 1, 3, loWatermarkEn);
    GX_SET_CP_REG (1, __GXData->cpEnable);
}

static void
__GXWriteFifoIntReset (u8 hiWatermarkClr, u8 loWatermarkClr)
{
    SET_REG_FIELD (0x4DE, __GXData->cpClr, 1, 0, hiWatermarkClr);
    SET_REG_FIELD (0x4DF, __GXData->cpClr, 1, 1, loWatermarkClr);
    GX_SET_CP_REG (2, __GXData->cpClr);
}

void
__GXInsaneWatermark (void)
{
    __GXFifoObj* realFifo = GPFifo;

    realFifo->hiWatermark = realFifo->loWatermark + 512;
    GX_SET_CP_REG (20, (realFifo->hiWatermark & 0x3FFFFFFF) & 0xFFFF);
    GX_SET_CP_REG (21, (realFifo->hiWatermark & 0x3FFFFFFF) >> 16);
}

void
__GXCleanGPFifo (void)
{
    GXFifoObj  dummyFifo;
    GXFifoObj* gpFifo  = GXGetGPFifo();
    GXFifoObj* cpuFifo = GXGetCPUFifo();
    void*      base    = GXGetFifoBase (gpFifo);

    dummyFifo          = *gpFifo;
    GXInitFifoPtrs (&dummyFifo, base, base);
    GXSetGPFifo (&dummyFifo);
    if (cpuFifo == gpFifo)
    {
        GXSetCPUFifo (&dummyFifo);
    }

    GXInitFifoPtrs (gpFifo, base, base);
    GXSetGPFifo (gpFifo);
    if (cpuFifo == gpFifo)
    {
        GXSetCPUFifo (cpuFifo);
    }
}

OSThread*
GXSetCurrentGXThread (void)
{
    BOOL      enabled;
    OSThread* prev;

    enabled = OSDisableInterrupts();
    prev    = __GXCurrentThread;

    ASSERTMSGLINE (
        0x532,
        !GXOverflowSuspendInProgress,
        "GXSetCurrentGXThread: Two threads cannot generate GX commands at the same time!");

    __GXCurrentThread = OSGetCurrentThread();
    OSRestoreInterrupts (enabled);

    return prev;
}

OSThread*
GXGetCurrentGXThread (void)
{
    return __GXCurrentThread;
}

GXFifoObj*
GXGetCPUFifo (void)
{
    return (GXFifoObj*)CPUFifo;
}

GXFifoObj*
GXGetGPFifo (void)
{
    return (GXFifoObj*)GPFifo;
}

u32
GXGetOverflowCount (void)
{
    return __GXOverflowCount;
}

u32
GXResetOverflowCount (void)
{
    u32 oldcount;

    oldcount          = __GXOverflowCount;
    __GXOverflowCount = 0;
    return oldcount;
}

#define SET_REG_FIELD2(line, reg, mask, val)                                                   \
    do {                                                                                       \
        ASSERTMSGLINE (line,                                                                   \
                       ((val) & ~(mask)) == 0,                                                 \
                       "GX Internal: Register field out of range");                            \
        (reg) = ((u32)(reg) & ~(mask)) | ((u32)(val));                                         \
    }                                                                                          \
    while (0)

volatile void*
GXRedirectWriteGatherPipe (void* ptr)
{
    u32  reg     = 0;
    BOOL enabled = OSDisableInterrupts();

    CHECK_GXBEGIN (0x5A6, "GXRedirectWriteGatherPipe");
    ASSERTLINE (0x5A7, OFFSET (ptr, 32) == 0);
    ASSERTLINE (0x5A9, !IsWGPipeRedirected);
#if DEBUG
    IsWGPipeRedirected = TRUE;
#endif

    GXFlush();
    while (PPCMfwpar() & 1) {}
    PPCMtwpar ((u32)OSUncachedToPhysical ((void*)GXFIFO_ADDR));
    if (CPGPLinked)
    {
        __GXFifoLink (0);
        __GXWriteFifoIntEnable (0, 0);
    }
    CPUFifo->wrPtr = OSPhysicalToCached (GX_GET_PI_REG (5) & 0xFBFFFFFF);
    GX_SET_PI_REG (3, 0);
    GX_SET_PI_REG (4, 0x04000000);
    SET_REG_FIELD (0x5C8, reg, 21, 5, ((u32)ptr & 0x3FFFFFFF) >> 5);

    reg &= 0xFBFFFFFF;
    GX_SET_PI_REG (5, reg);
    __sync();

    OSRestoreInterrupts (enabled);

    return (volatile void*)GXFIFO_ADDR;
}
