#ifndef _DOLPHIN_SI_H_
#define _DOLPHIN_SI_H_

#include <types.h>

#include <dolphin/os.h>

#define PAD_CHAN0_BIT         0x80000000
#define PAD_CHAN1_BIT         0x40000000
#define PAD_CHAN2_BIT         0x20000000
#define PAD_CHAN3_BIT         0x10000000

#define SI_ERROR_UNDER_RUN    0x0001
#define SI_ERROR_OVER_RUN     0x0002
#define SI_ERROR_COLLISION    0x0004
#define SI_ERROR_NO_RESPONSE  0x0008
#define SI_ERROR_WRST         0x0010
#define SI_ERROR_RDST         0x0020
#define SI_ERROR_UNKNOWN      0x0040
#define SI_ERROR_BUSY         0x0080

#define SI_TYPE_MASK          0x18000000u
#define SI_TYPE_N64           0x00000000u
#define SI_TYPE_DOLPHIN       0x08000000u
#define SI_TYPE_GC            SI_TYPE_DOLPHIN
#define SI_GC_WIRELESS        0x80000000
#define SI_GC_NOMOTOR         0x20000000
#define SI_GC_STANDARD        0x01000000
#define SI_WIRELESS_RECEIVED  0x40000000
#define SI_WIRELESS_IR        0x04000000
#define SI_WIRELESS_STATE     0x02000000
#define SI_WIRELESS_ORIGIN    0x00200000
#define SI_WIRELESS_FIX_ID    0x00100000
#define SI_WIRELESS_TYPE      0x000f0000
#define SI_WIRELESS_LITE_MASK 0x000c0000
#define SI_WIRELESS_LITE      0x00040000
#define SI_WIRELESS_CONT_MASK 0x00080000
#define SI_WIRELESS_CONT      0x00000000
#define SI_WIRELESS_ID        0x00c0ff00
#define SI_WIRELESS_TYPE_ID   (SI_WIRELESS_TYPE | SI_WIRELESS_ID)
#define SI_N64_CONTROLLER     (SI_TYPE_N64 | 0x05000000)
#define SI_N64_MIC            (SI_TYPE_N64 | 0x00010000)
#define SI_N64_KEYBOARD       (SI_TYPE_N64 | 0x00020000)
#define SI_N64_MOUSE          (SI_TYPE_N64 | 0x02000000)
#define SI_GBA                (SI_TYPE_N64 | 0x00040000)
#define SI_GC_CONTROLLER      (SI_TYPE_GC | SI_GC_STANDARD)
#define SI_GC_RECEIVER        (SI_TYPE_GC | SI_GC_WIRELESS)
#define SI_GC_WAVEBIRD                                                                             \
    (SI_TYPE_GC | SI_GC_WIRELESS | SI_GC_STANDARD | SI_WIRELESS_STATE | SI_WIRELESS_FIX_ID)
#define SI_GC_KEYBOARD (SI_TYPE_GC | 0x00200000)
#define SI_GC_STEERING (SI_TYPE_GC | 0x00000000)

#define SI_MAX_CHAN    4

typedef void (*SICallback) (s32 chan, u32 sr, OSContext* context);
typedef void (*SITypeAndStatusCallback) (s32 chan, u32 type);

BOOL SITransfer (s32        chan,
                 void*      output,
                 u32        outputBytes,
                 void*      input,
                 u32        inputBytes,
                 SICallback callback,
                 OSTime     delay);
u32  SIGetCommand (s32 chan);
u32  SIEnablePolling (u32 poll);
u32  SIDisablePolling (u32 poll);
u32  SISetXY (u32 x, u32 y);
void SITransferCommands (void);
BOOL SIBusy (void);

#endif // _DOLPHIN_SI_H_
