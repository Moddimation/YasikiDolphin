#ifndef _DOLPHIN_VITYPES_H_
#define _DOLPHIN_VITYPES_H_

#include <types.h>

// Merge format/mode to one value for TV info (see GXRenderModeObj)
#define VI_TV_INFO(format, mode) (((format) << 2) + (mode))
// Get TV format from TV info
#define VI_TV_INFO_FMT(info)     ((info) >> 2)
// Get TV scan mode from TV info
#define VI_TV_INFO_MODE(info)    ((info) & 0b00000011)

#define VI_INTERLACE             0
#define VI_NON_INTERLACE         1
#define VI_PROGRESSIVE           2
#define VI_3D                    3

#define VI_NTSC                  0
#define VI_PAL                   1
#define VI_MPAL                  2
#define VI_DEBUG                 3
#define VI_DEBUG_PAL             4
#define VI_EURGB60               5
#define VI_GCA                   6

#define VI_TVMODE(FMT, INT)      (((FMT) << 2) + (INT))

typedef u8 VIBool;
#define VI_FALSE             ((VIBool)0)
#define VI_TRUE              ((VIBool)1)
#define VI_DISABLE           ((VIBool)0)
#define VI_ENABLE            ((VIBool)1)

#define VI_3D                3
#define VI_TVMODE_NTSC_3D    ((VITVMode)VI_TVMODE (VI_NTSC, VI_3D))
#define VI_GCA               6
#define VI_TVMODE_GCA_INT    (VITVMode) VI_TVMODE (VI_GCA, VI_INTERLACE)
#define VI_TVMODE_GCA_PROG   (VITVMode) VI_TVMODE (VI_GCA, VI_PROGRESSIVE)
#define VI_TVMODE_PAL_PROG   (VITVMode)6

#define VI_EXTRA             7
#define VI_TVMODE_EXTRA_INT  ((VITVMode)VI_TVMODE (VI_EXTRA, VI_INTERLACE))
#define VI_TVMODE_EXTRA_DS   ((VITVMode)VI_TVMODE (VI_EXTRA, VI_NON_INTERLACE))
#define VI_TVMODE_EXTRA_PROG ((VITVMode)VI_TVMODE (VI_EXTRA, VI_PROGRESSIVE))

#define VI_HD720             8
#define VI_TVMODE_HD720_PROG ((VITVMode)VI_TVMODE (VI_HD720, VI_PROGRESSIVE))

typedef enum
{
    VI_TVMODE_NTSC_INT = 0,       // VI_TVMODE(VI_NTSC, VI_INTERLACE),
    VI_TVMODE_NTSC_DS = 1,        // VI_TVMODE(VI_NTSC, VI_NON_INTERLACE),
    VI_TVMODE_NTSC_PROG = 2,      // VI_TVMODE(VI_NTSC, VI_PROGRESSIVE),

    VI_TVMODE_PAL_INT = 4,        // VI_TVMODE(VI_PAL, VI_INTERLACE),
    VI_TVMODE_PAL_DS = 5,         // VI_TVMODE(VI_PAL, VI_NON_INTERLACE),

    VI_TVMODE_EURGB60_INT = 20,   // VI_TVMODE(VI_EURGB60, VI_INTERLACE),
    VI_TVMODE_EURGB60_DS = 21,    // VI_TVMODE(VI_EURGB60, VI_NON_INTERLACE),
    VI_TVMODE_EURGB60_PROG = 22,  // VI_TVMODE(VI_EURGB60, VI_PROGRESSIVE),

    VI_TVMODE_MPAL_INT = 8,       // VI_TVMODE(VI_MPAL, VI_INTERLACE),
    VI_TVMODE_MPAL_DS = 9,        // VI_TVMODE(VI_MPAL, VI_NON_INTERLACE),
    VI_TVMODE_MPAL_PROG = 10,     // VI_TVMODE(VI_MPAL, VI_PROGRESSIVE),

    VI_TVMODE_DEBUG_INT = 12,     // VI_TVMODE(VI_DEBUG, VI_INTERLACE),

    VI_TVMODE_DEBUG_PAL_INT = 16, // VI_TVMODE(VI_DEBUG_PAL, VI_INTERLACE),
    VI_TVMODE_DEBUG_PAL_DS = 17   // VI_TVMODE(VI_DEBUG_PAL, VI_NON_INTERLACE)
} VITVMode;

typedef enum
{
    VI_TV_FMT_NTSC,               // 0
    VI_TV_FMT_PAL,                // 1
    VI_TV_FMT_MPAL,               // 2
    VI_TV_FMT_DEBUG,              // 3
    VI_TV_FMT_DEBUG_PAL,          // 4
    VI_TV_FMT_EURGB60,            // 5
    VI_TV_FMT_6,                  // 6
    VI_TV_FMT_7,                  // 7
    VI_TV_FMT_8                   // 8
} VITvFormat;

typedef enum VIScanMode
{
    VI_SCAN_MODE_INT,
    VI_SCAN_MODE_DS,
    VI_SCAN_MODE_PROG
} VIScanMode;

typedef enum VIXFBMode
{
    VI_XFB_MODE_SF,
    VI_XFB_MODE_DF
} VIXFBMode;

typedef void (*VIRetraceCallback) (u32 retraceCount);

#endif
