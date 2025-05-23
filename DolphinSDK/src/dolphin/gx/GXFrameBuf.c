#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "GXPrivate.h"

GXRenderModeObj GXNtsc240Ds = {
    VI_TVMODE_NTSC_DS,
    640,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240DsAa = {
    VI_TVMODE_NTSC_DS,
    640,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240Int = {
    VI_TVMODE_NTSC_INT,
    640,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_TRUE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240IntAa = {
    VI_TVMODE_NTSC_INT,
    640,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_TRUE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480IntDf = {
    VI_TVMODE_NTSC_INT,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 8, 8, 10, 12, 10, 8, 8 }
};

GXRenderModeObj GXNtsc480Int = {
    VI_TVMODE_NTSC_INT,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480IntAa = {
    VI_TVMODE_NTSC_INT,
    640,
    242,
    480,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 4, 8, 12, 16, 12, 8, 4 }
};

GXRenderModeObj GXNtsc480Prog = {
    VI_TVMODE_NTSC_PROG,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480ProgAa = {
    VI_TVMODE_NTSC_PROG,
    640,
    242,
    480,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 4, 8, 12, 16, 12, 8, 4 }
};

GXRenderModeObj GXMpal240Ds = {
    VI_TVMODE_MPAL_DS,
    640,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXMpal240DsAa = {
    VI_TVMODE_MPAL_DS,
    640,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXMpal240Int = {
    VI_TVMODE_MPAL_INT,
    640,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_TRUE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXMpal240IntAa = {
    VI_TVMODE_MPAL_INT,
    640,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_TRUE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXMpal480IntDf = {
    VI_TVMODE_MPAL_INT,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 8, 8, 10, 12, 10, 8, 8 }
};
GXRenderModeObj GXMpal480Int = {
    VI_TVMODE_MPAL_INT,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXMpal480IntAa = {
    VI_TVMODE_MPAL_INT,
    640,
    242,
    480,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 4, 8, 12, 16, 12, 8, 4 }
};
GXRenderModeObj GXPal264Ds = {
    VI_TVMODE_PAL_DS,
    640,
    264,
    264,
    40,
    23,
    640,
    528,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXPal264DsAa = {
    VI_TVMODE_PAL_DS,
    640,
    264,
    264,
    40,
    23,
    640,
    528,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXPal264Int = {
    VI_TVMODE_PAL_DS,
    640,
    264,
    264,
    40,
    23,
    640,
    528,
    VI_XFB_MODE_SF,
    GX_TRUE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXPal264IntAa = {
    VI_TVMODE_PAL_DS,
    640,
    264,
    264,
    40,
    23,
    640,
    528,
    VI_XFB_MODE_SF,
    GX_TRUE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXPal528IntDf = {
    VI_TVMODE_PAL_INT,
    640,
    528,
    528,
    40,
    23,
    640,
    528,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 8, 8, 10, 12, 10, 8, 8 }
};
GXRenderModeObj GXPal528Int = {
    VI_TVMODE_PAL_INT,
    640,
    528,
    528,
    40,
    23,
    640,
    528,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};
GXRenderModeObj GXPal524IntAa = {
    VI_TVMODE_PAL_INT,
    640,
    264,
    524,
    40,
    23,
    640,
    524,
    VI_XFB_MODE_DF,
    GX_FALSE,
    GX_TRUE,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 },
    { 4, 8, 12, 16, 12, 8, 4 }
};
GXRenderModeObj GXRmHW = {
    VI_TVMODE_NTSC_DS,
    320,
    240,
    240,
    40,
    0,
    640,
    480,
    VI_XFB_MODE_SF,
    GX_FALSE,
    GX_FALSE,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

void
GXAdjustForOverscan (GXRenderModeObj* rmin, GXRenderModeObj* rmout, u16 hor, u16 ver)
{
    u16 hor2 = (u16)(hor * 2);
    u16 ver2 = (u16)(ver * 2);
    u32 verf;

    if (rmin != rmout)
    {
        *rmout = *rmin;
    }

    rmout->fbWidth   = (u16)(rmin->fbWidth - hor2);
    verf             = (ver2 * rmin->efbHeight) / (u32)rmin->xfbHeight;
    rmout->efbHeight = (u16)(rmin->efbHeight - verf);
    if (rmin->xFBmode == VI_XFB_MODE_SF && (rmin->viTVmode & 2) != 2)
    {
        rmout->xfbHeight = (u16)(rmin->xfbHeight - ver);
    }
    else
    {
        rmout->xfbHeight = (u16)(rmin->xfbHeight - ver2);
    }
    rmout->viWidth   = (u16)(rmin->viWidth - hor2);
    rmout->viHeight  = (u16)(rmin->viHeight - ver2);
    rmout->viXOrigin = (u16)(rmin->viXOrigin + hor);
    rmout->viYOrigin = (u16)(rmin->viYOrigin + ver);
}

void
GXSetDispCopySrc (u16 left, u16 top, u16 wd, u16 ht)
{
    CHECK_GXBEGIN (0x3B9, "GXSetDispCopySrc");

    __GXData->cpDispSrc = 0;
    SET_REG_FIELD (0x3BC, __GXData->cpDispSrc, 10, 0, left);
    SET_REG_FIELD (0x3BD, __GXData->cpDispSrc, 10, 10, top);
    SET_REG_FIELD (0x3BE, __GXData->cpDispSrc, 8, 24, 0x49);

    __GXData->cpDispSize = 0;
    SET_REG_FIELD (0x3C1, __GXData->cpDispSize, 10, 0, wd - 1);
    SET_REG_FIELD (0x3C2, __GXData->cpDispSize, 10, 10, ht - 1);
    SET_REG_FIELD (0x3C3, __GXData->cpDispSize, 8, 24, 0x4A);
}

void
GXSetTexCopySrc (u16 left, u16 top, u16 wd, u16 ht)
{
    CHECK_GXBEGIN (0x3D5, "GXSetTexCopySrc");

    __GXData->cpTexSrc = 0;
    SET_REG_FIELD (0x3D8, __GXData->cpTexSrc, 10, 0, left);
    SET_REG_FIELD (0x3D9, __GXData->cpTexSrc, 10, 10, top);
    SET_REG_FIELD (0x3DA, __GXData->cpTexSrc, 8, 24, 0x49);

    __GXData->cpTexSize = 0;
    SET_REG_FIELD (0x3DD, __GXData->cpTexSize, 10, 0, wd - 1);
    SET_REG_FIELD (0x3DE, __GXData->cpTexSize, 10, 10, ht - 1);
    SET_REG_FIELD (0x3DF, __GXData->cpTexSize, 8, 24, 0x4A);
}

void
GXSetDispCopyDst (u16 wd, u16 ht)
{
#pragma unused(ht)

    u16 stride;

    ASSERTMSGLINE (0x3F3, (wd & 0xF) == 0, "GXSetDispCopyDst: Width must be a multiple of 16");
    CHECK_GXBEGIN (0x3F4, "GXSetDispCopyDst");

    stride                 = (u16)(wd * 2);
    __GXData->cpDispStride = 0;
    SET_REG_FIELD (0x3FA, __GXData->cpDispStride, 10, 0, (stride >> 5));
    SET_REG_FIELD (0x3FB, __GXData->cpDispStride, 8, 24, 0x4D);
}

void
GXSetTexCopyDst (u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap)
{
    u32 rowTiles;
    u32 colTiles;
    u32 cmpTiles;
    u32 peTexFmt;
    u32 peTexFmtH;

    CHECK_GXBEGIN (0x415, "GXSetTexCopyDst");

    __GXData->cpTexZ = 0;
    peTexFmt         = (u32)(fmt & 0xF);
    ASSERTMSGLINEV (0x434, peTexFmt < 13, "%s: invalid texture format", "GXSetTexCopyDst");

    if (fmt == GX_TF_Z16)
    {
        peTexFmt = 0xB;
    }
    switch (fmt)
    {
        case GX_TF_I4:
        case GX_TF_I8:
        case GX_TF_IA4:
        case GX_TF_IA8:
        case GX_CTF_YUVA8:
            SET_REG_FIELD (0, __GXData->cpTex, 2, 15, 3);
            break;
        default:
            SET_REG_FIELD (0, __GXData->cpTex, 2, 15, 2);
            break;
    }

    __GXData->cpTexZ = (fmt & _GX_TF_ZTF) == _GX_TF_ZTF;
    peTexFmtH        = (peTexFmt >> 3) & 1;
    !peTexFmt;
    SET_REG_FIELD (0x44B, __GXData->cpTex, 1, 3, peTexFmtH);
    peTexFmt = peTexFmt & 7;
    __GetImageTileCount (fmt, wd, ht, &rowTiles, &colTiles, &cmpTiles);

    __GXData->cpTexStride = 0;
    SET_REG_FIELD (0x454, __GXData->cpTexStride, 10, 0, rowTiles * cmpTiles);
    SET_REG_FIELD (0x455, __GXData->cpTexStride, 8, 24, 0x4D);
    SET_REG_FIELD (0x456, __GXData->cpTex, 1, 9, mipmap);
    SET_REG_FIELD (0x457, __GXData->cpTex, 3, 4, peTexFmt);
}

void
GXSetDispCopyFrame2Field (GXCopyMode mode)
{
    CHECK_GXBEGIN (0x468, "GXSetDispCopyFrame2Field");
    SET_REG_FIELD (0x469, __GXData->cpDisp, 2, 12, mode);
    SET_REG_FIELD (0x46A, __GXData->cpTex, 2, 12, 0);
}

void
GXSetCopyClamp (GXFBClamp clamp)
{
    u8 clmpB;
    u8 clmpT;

    CHECK_GXBEGIN (0x47D, "GXSetCopyClamp");

    clmpT = (clamp & 1) == 1;
    clmpB = (clamp & 2) == 2;

    SET_REG_FIELD (0x481, __GXData->cpDisp, 1, 0, clmpT);
    SET_REG_FIELD (0x482, __GXData->cpDisp, 1, 1, clmpB);

    SET_REG_FIELD (0x484, __GXData->cpTex, 1, 0, clmpT);
    SET_REG_FIELD (0x485, __GXData->cpTex, 1, 1, clmpB);
}

u32
GXSetDispCopyYScale (f32 vscale)
{
    u8  enable;
    u32 iScale;
    f32 fScale;
    u32 ht;
    u32 reg;

    CHECK_GXBEGIN (0x49B, "GXSetDispCopyYScale");

    ASSERTMSGLINE (0x49D, vscale >= 1.0f, "GXSetDispCopyYScale: Vertical scale must be >= 1.0");

    iScale = (u32)(256.0f / vscale) & 0x1FF;
    fScale = 256.0f / (f32)iScale;
    enable = (iScale != 256);

    reg    = 0;
    SET_REG_FIELD (0x4A6, reg, 9, 0, iScale);
    SET_REG_FIELD (0x4A7, reg, 8, 24, 0x4E);
    GX_WRITE_RAS_REG (reg);
    __GXData->bpSent = 1;
    SET_REG_FIELD (0x4AB, __GXData->cpDisp, 1, 10, enable);
    ht = (u32)GET_REG_FIELD (__GXData->cpDispSize, 10, 10) + 1;

    return (u32)(ht * fScale);
}

void
GXSetCopyClear (GXColor clear_clr, u32 clear_z)
{
    u32 reg;

    CHECK_GXBEGIN (0x4C4, "GXSetCopyClear");
    ASSERTMSGLINE (0x4C6, clear_z <= 0xFFFFFF, "GXSetCopyClear: Z clear value is out of range");

    reg = 0;
    SET_REG_FIELD (0x4C9, reg, 8, 0, clear_clr.r);
    SET_REG_FIELD (0x4CA, reg, 8, 8, clear_clr.a);
    SET_REG_FIELD (0x4CB, reg, 8, 24, 0x4F);
    GX_WRITE_RAS_REG (reg);

    reg = 0;
    SET_REG_FIELD (0x4CF, reg, 8, 0, clear_clr.b);
    SET_REG_FIELD (0x4D0, reg, 8, 8, clear_clr.g);
    SET_REG_FIELD (0x4D1, reg, 8, 24, 0x50);
    GX_WRITE_RAS_REG (reg);

    reg = 0;
    SET_REG_FIELD (0x4D5, reg, 24, 0, clear_z);
    SET_REG_FIELD (0x4D6, reg, 8, 24, 0x51);
    GX_WRITE_RAS_REG (reg);
    __GXData->bpSent = 1;
}

void
GXSetCopyFilter (GXBool aa, const u8 sample_pattern[12][2], GXBool vf, const u8 vfilter[7])
{
    u32 msLoc[4];
    u32 coeff0;
    u32 coeff1;

    CHECK_GXBEGIN (0x4F1, "GXSetCopyFilter");

    if (aa != 0)
    {
        msLoc[0] = 0;
        SET_REG_FIELD (0x4F5, msLoc[0], 4, 0, sample_pattern[0][0]);
        SET_REG_FIELD (0x4F6, msLoc[0], 4, 4, sample_pattern[0][1]);
        SET_REG_FIELD (0x4F7, msLoc[0], 4, 8, sample_pattern[1][0]);
        SET_REG_FIELD (0x4F8, msLoc[0], 4, 12, sample_pattern[1][1]);
        SET_REG_FIELD (0x4F9, msLoc[0], 4, 16, sample_pattern[2][0]);
        SET_REG_FIELD (0x4FA, msLoc[0], 4, 20, sample_pattern[2][1]);
        SET_REG_FIELD (0x4FB, msLoc[0], 8, 24, 1);

        msLoc[1] = 0;
        SET_REG_FIELD (0x4FE, msLoc[1], 4, 0, sample_pattern[3][0]);
        SET_REG_FIELD (0x4FF, msLoc[1], 4, 4, sample_pattern[3][1]);
        SET_REG_FIELD (0x500, msLoc[1], 4, 8, sample_pattern[4][0]);
        SET_REG_FIELD (0x501, msLoc[1], 4, 12, sample_pattern[4][1]);
        SET_REG_FIELD (0x502, msLoc[1], 4, 16, sample_pattern[5][0]);
        SET_REG_FIELD (0x503, msLoc[1], 4, 20, sample_pattern[5][1]);
        SET_REG_FIELD (0x504, msLoc[1], 8, 24, 2);

        msLoc[2] = 0;
        SET_REG_FIELD (0x507, msLoc[2], 4, 0, sample_pattern[6][0]);
        SET_REG_FIELD (0x508, msLoc[2], 4, 4, sample_pattern[6][1]);
        SET_REG_FIELD (0x509, msLoc[2], 4, 8, sample_pattern[7][0]);
        SET_REG_FIELD (0x50A, msLoc[2], 4, 12, sample_pattern[7][1]);
        SET_REG_FIELD (0x50B, msLoc[2], 4, 16, sample_pattern[8][0]);
        SET_REG_FIELD (0x50C, msLoc[2], 4, 20, sample_pattern[8][1]);
        SET_REG_FIELD (0x50D, msLoc[2], 8, 24, 3);

        msLoc[3] = 0;
        SET_REG_FIELD (0x510, msLoc[3], 4, 0, sample_pattern[9][0]);
        SET_REG_FIELD (0x511, msLoc[3], 4, 4, sample_pattern[9][1]);
        SET_REG_FIELD (0x512, msLoc[3], 4, 8, sample_pattern[10][0]);
        SET_REG_FIELD (0x513, msLoc[3], 4, 12, sample_pattern[10][1]);
        SET_REG_FIELD (0x514, msLoc[3], 4, 16, sample_pattern[11][0]);
        SET_REG_FIELD (0x515, msLoc[3], 4, 20, sample_pattern[11][1]);
        SET_REG_FIELD (0x516, msLoc[3], 8, 24, 4);
    }
    else
    {
        msLoc[0] = 0x01666666;
        msLoc[1] = 0x02666666;
        msLoc[2] = 0x03666666;
        msLoc[3] = 0x04666666;
    }
    GX_WRITE_RAS_REG (msLoc[0]);
    GX_WRITE_RAS_REG (msLoc[1]);
    GX_WRITE_RAS_REG (msLoc[2]);
    GX_WRITE_RAS_REG (msLoc[3]);

    coeff0 = 0;
    SET_REG_FIELD (0, coeff0, 8, 24, 0x53);
    coeff1 = 0;
    SET_REG_FIELD (0, coeff1, 8, 24, 0x54);
    if (vf != 0)
    {
        SET_REG_FIELD (0x52E, coeff0, 6, 0, vfilter[0]);
        SET_REG_FIELD (0x52F, coeff0, 6, 6, vfilter[1]);
        SET_REG_FIELD (0x530, coeff0, 6, 12, vfilter[2]);
        SET_REG_FIELD (0x531, coeff0, 6, 18, vfilter[3]);
        SET_REG_FIELD (0x532, coeff1, 6, 0, vfilter[4]);
        SET_REG_FIELD (0x533, coeff1, 6, 6, vfilter[5]);
        SET_REG_FIELD (0x534, coeff1, 6, 12, vfilter[6]);
    }
    else
    {
        SET_REG_FIELD (0, coeff0, 6, 0, 0);
        SET_REG_FIELD (0, coeff0, 6, 6, 0);
        SET_REG_FIELD (0, coeff0, 6, 12, 21);
        SET_REG_FIELD (0, coeff0, 6, 18, 22);
        SET_REG_FIELD (0, coeff1, 6, 0, 21);
        SET_REG_FIELD (0, coeff1, 6, 6, 0);
        SET_REG_FIELD (0, coeff1, 6, 12, 0);
    }
    GX_WRITE_RAS_REG (coeff0);
    GX_WRITE_RAS_REG (coeff1);
    __GXData->bpSent = 1;
}

void
GXSetDispCopyGamma (GXGamma gamma)
{
    CHECK_GXBEGIN (0x555, "GXSetDispCopyGamma");
    SET_REG_FIELD (0x556, __GXData->cpDisp, 2, 7, gamma);
}

#if DEBUG
static void
__GXVerifCopy (void* dest, u8 clear)
{
    u8  clmpT;
    u8  clmpB;
    u32 x0;
    u32 y0;
    u32 dx;
    u32 dy;

    CHECK_GXBEGIN (0x56A, "GXCopyDisp");

    clmpT = GET_REG_FIELD (__GXData->cpDisp, 1, 0);
    clmpB = (u32)GET_REG_FIELD (__GXData->cpDisp, 1, 1);
    x0    = GET_REG_FIELD (__GXData->cpDispSrc, 10, 0);
    dx    = GET_REG_FIELD (__GXData->cpDispSize, 10, 0) + 1;
    y0    = GET_REG_FIELD (__GXData->cpDispSrc, 10, 10);
    dy    = GET_REG_FIELD (__GXData->cpDispSize, 10, 10) + 1;

    ASSERTMSGLINE (0x574,
                   clmpT || y0 != 0,
                   "GXCopy: Have to set GX_CLAMP_TOP if source top == 0");
    ASSERTMSGLINE (0x576,
                   clmpB || y0 + dy <= 528,
                   "GXCopy: Have to set GX_CLAMP_BOTTOM if source bottom > 528");
    ASSERTMSGLINE (0x57B,
                   (__GXData->peCtrl & 7) != 3 || clear == 0,
                   "GXCopy: Can not do clear while pixel type is Z");
    if ((u32)(__GXData->peCtrl & 7) == 5)
    {
        ASSERTMSGLINE (0x581, clear == 0, "GXCopy: Can not clear YUV framebuffer");
        ASSERTMSGLINE (0x583,
                       (x0 & 3) == 0,
                       "GXCopy: Source x is not multiple of 4 for YUV copy");
        ASSERTMSGLINE (0x585,
                       (y0 & 3) == 0,
                       "GXCopy: Source y is not multiple of 4 for YUV copy");
        ASSERTMSGLINE (0x587,
                       (dx & 3) == 0,
                       "GXCopy: Source width is not multiple of 4 for YUV copy");
        ASSERTMSGLINE (0x589,
                       (dy & 3) == 0,
                       "GXCopy: Source height is not multiple of 4 for YUV copy");
    }
    else
    {
        ASSERTMSGLINE (0x58D,
                       (x0 & 1) == 0,
                       "GXCopy: Source x is not multiple of 2 for RGB copy");
        ASSERTMSGLINE (0x58F,
                       (y0 & 1) == 0,
                       "GXCopy: Source y is not multiple of 2 for RGB copy");
        ASSERTMSGLINE (0x591,
                       (dx & 1) == 0,
                       "GXCopy: Source width is not multiple of 2 for RGB copy");
        ASSERTMSGLINE (0x593,
                       (dy & 1) == 0,
                       "GXCopy: Source height is not multiple of 2 for RGB copy");
    }
    ASSERTMSGLINE (0x597,
                   ((u32)dest & 0x1F) == 0,
                   "GXCopy: Display destination address not 32B aligned");
}
#endif

void
GXCopyDisp (void* dest, GXBool clear)
{
    u32 reg;
    u32 tempPeCtrl;
    u32 phyAddr;
    u8  changePeCtrl;

    CHECK_GXBEGIN (0x5B1, "GXCopyDisp");

#if DEBUG
    __GXVerifCopy (dest, clear);
#endif
    if (clear)
    {
        reg = __GXData->zmode;
        SET_REG_FIELD (0, reg, 1, 0, 1);
        SET_REG_FIELD (0, reg, 3, 1, 7);
        GX_WRITE_RAS_REG (reg);

        reg = __GXData->cmode0;
        SET_REG_FIELD (0, reg, 1, 0, 0);
        SET_REG_FIELD (0, reg, 1, 1, 0);
        GX_WRITE_RAS_REG (reg);
    }
    changePeCtrl = FALSE;
    if ((clear || (u32)GET_REG_FIELD (__GXData->peCtrl, 3, 0) == 3) &&
        (u32)GET_REG_FIELD (__GXData->peCtrl, 1, 6) == 1)
    {
        changePeCtrl = TRUE;
        tempPeCtrl   = __GXData->peCtrl;
        SET_REG_FIELD (0, tempPeCtrl, 1, 6, 0);
        GX_WRITE_RAS_REG (tempPeCtrl);
    }
    GX_WRITE_RAS_REG (__GXData->cpDispSrc);
    GX_WRITE_RAS_REG (__GXData->cpDispSize);
    GX_WRITE_RAS_REG (__GXData->cpDispStride);

    phyAddr = (u32)dest & 0x3FFFFFFF;
    reg     = 0;
    SET_REG_FIELD (0x5D8, reg, 21, 0, phyAddr >> 5);
    SET_REG_FIELD (0x5D9, reg, 8, 24, 0x4B);
    GX_WRITE_RAS_REG (reg);

    SET_REG_FIELD (0x5DC, __GXData->cpDisp, 1, 11, clear);
    SET_REG_FIELD (0x5DD, __GXData->cpDisp, 1, 14, 1);
    SET_REG_FIELD (0x5DE, __GXData->cpDisp, 8, 24, 0x52);
    GX_WRITE_RAS_REG (__GXData->cpDisp);

    if (clear)
    {
        GX_WRITE_RAS_REG (__GXData->zmode);
        GX_WRITE_RAS_REG (__GXData->cmode0);
    }
    if (changePeCtrl)
    {
        GX_WRITE_RAS_REG (__GXData->peCtrl);
    }
    __GXData->bpSent = 1;
}

void
GXCopyTex (void* dest, GXBool clear)
{
    u32 reg;
    u32 tempPeCtrl;
    u32 phyAddr;
    u8  changePeCtrl;

    CHECK_GXBEGIN (0x604, "GXCopyTex");

#if DEBUG
    __GXVerifCopy (dest, clear);
#endif
    if (clear)
    {
        reg = __GXData->zmode;
        SET_REG_FIELD (0, reg, 1, 0, 1);
        SET_REG_FIELD (0, reg, 3, 1, 7);
        GX_WRITE_RAS_REG (reg);

        reg = __GXData->cmode0;
        SET_REG_FIELD (0, reg, 1, 0, 0);
        SET_REG_FIELD (0, reg, 1, 1, 0);
        GX_WRITE_RAS_REG (reg);
    }
    changePeCtrl = 0;
    tempPeCtrl   = __GXData->peCtrl;
    if (((u8)__GXData->cpTexZ != 0) && ((u32)(tempPeCtrl & 7) != 3))
    {
        changePeCtrl = 1;
        tempPeCtrl   = (tempPeCtrl & 0xFFFFFFF8) | 3;
    }
    if (((clear != 0) || ((u32)(tempPeCtrl & 7) == 3)) && ((u32)((tempPeCtrl >> 6U) & 1) == 1))
    {
        changePeCtrl  = 1;
        tempPeCtrl   &= 0xFFFFFFBF;
    }
    if (changePeCtrl)
    {
        GX_WRITE_RAS_REG (tempPeCtrl);
    }
    GX_WRITE_RAS_REG (__GXData->cpTexSrc);
    GX_WRITE_RAS_REG (__GXData->cpTexSize);
    GX_WRITE_RAS_REG (__GXData->cpTexStride);

    phyAddr = (u32)dest & 0x3FFFFFFF;
    reg     = 0;
    SET_REG_FIELD (0x635, reg, 21, 0, phyAddr >> 5);
    SET_REG_FIELD (0x636, reg, 8, 24, 0x4B);
    GX_WRITE_RAS_REG (reg);

    SET_REG_FIELD (0x639, __GXData->cpTex, 1, 11, clear);
    SET_REG_FIELD (0x63A, __GXData->cpTex, 1, 14, 0);
    SET_REG_FIELD (0x63B, __GXData->cpTex, 8, 24, 0x52);
    GX_WRITE_RAS_REG (__GXData->cpTex);

    if (clear != 0)
    {
        GX_WRITE_RAS_REG (__GXData->zmode);
        GX_WRITE_RAS_REG (__GXData->cmode0);
    }
    if (changePeCtrl)
    {
        GX_WRITE_RAS_REG (__GXData->peCtrl);
    }
    __GXData->bpSent = 1;
}

void
GXClearBoundingBox (void)
{
    u32 reg;

    CHECK_GXBEGIN (0x65B, "GXClearBoundingBox");
    reg = 0x550003FF;
    GX_WRITE_RAS_REG (reg);
    reg = 0x560003FF;
    GX_WRITE_RAS_REG (reg);
    __GXData->bpSent = 1;
}

void
GXReadBoundingBox (u16* left, u16* top, u16* right, u16* bottom)
{
    CHECK_GXBEGIN (0x671, "GXReadBoundingBox");
    *left   = __PERegs[PE_PI_XBOUND0_ID];
    *top    = __PERegs[PE_PI_YBOUND0_ID];
    *right  = __PERegs[PE_PI_XBOUND1_ID];
    *bottom = __PERegs[PE_PI_YBOUND1_ID];
}
