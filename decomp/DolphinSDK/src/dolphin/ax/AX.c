#include <dolphin/ax.h>

#include <dolphin.h>

#include "AXPrivate.h"

void
AXInit (void)
{
#ifdef DEBUG
    OSReport ("Initializing AX¥n");
#endif
    __AXAllocInit();
    __AXVPBInit();
    __AXSPBInit();
    __AXAuxInit();
    __AXClInit();
    __AXOutInit();
}

void
AXQuit (void)
{
#ifdef DEBUG
    OSReport ("Shutting down AX¥n");
#endif
    __AXAllocQuit();
    __AXVPBQuit();
    __AXSPBQuit();
    __AXAuxQuit();
    __AXClQuit();
    __AXOutQuit();
}
