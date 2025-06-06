#ifndef _DOLPHIN_OSRESETSW_H_
#define _DOLPHIN_OSRESETSW_H_

#include <types.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*OSResetCallback) (void);

OSResetCallback OSSetResetCallback (OSResetCallback callback);
BOOL            OSGetResetSwitchState ();
BOOL            OSGetResetButtonState (void);

#ifdef __cplusplus
}
#endif

#endif
