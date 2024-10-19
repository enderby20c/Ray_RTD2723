/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary                    */
/*                                                                              */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerGosdDispOsdInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Source format
//--------------------------------------------------
typedef struct
{
    EnumGosdDisplayOSD enumOSD;
    DWORD ulSurfaceId;
    StructGosdGdmaRectangle stWinRect;
    StructGosdGdmaRectangle stDispRect;
    EnumDBApply enumDBApply;
} StructGosdDispOsdDisplayArgument;

typedef enum
{
    /* big endian below */
    _GDMA_COLOR_FORMAT_4BIT = 1, /* 4-bit index */
    _GDMA_COLOR_FORMAT_8BIT = 2, /* 8-bit index */
    _GDMA_COLOR_FORMAT_RGB565 = 4, /* 16-bit RGB (565) with constant alpha */
    _GDMA_COLOR_FORMAT_ARGB1555 = 5, /* 16-bit ARGB (1555) */
    _GDMA_COLOR_FORMAT_ARGB4444 = 6, /* 16-bit ARGB (4444) */
    _GDMA_COLOR_FORMAT_ARGB8888 = 7, /* 32-bit ARGB (8888) */
    _GDMA_COLOR_FORMAT_YCBYCR88 = 10, /* M-cap 422 */
    _GDMA_COLOR_FORMAT_YCBCRA4444 = 11, /* 16-bit YCBCRA (4444) */
    _GDMA_COLOR_FORMAT_YCBCRA8888 = 12, /* 32-bit YCBCRA (8888) */
    _GDMA_COLOR_FORMAT_RGBA5551 = 13, /* 16-bit RGBA (5551) */
    _GDMA_COLOR_FORMAT_RGBA4444 = 14, /* 16-bit RGBA (4444) */
    _GDMA_COLOR_FORMAT_RGBA8888 = 15, /* 32-bit RGBA (8888) */
    _GDMA_COLOR_FORMAT_ARGB6666 = 17, /* 24-bit RGBA (6666) */
    _GDMA_COLOR_FORMAT_ARGB8888_RGB6TO8 = 18, /* 32-bit AFBC only */
    _GDMA_COLOR_FORMAT_RGB888_RGB6TO8 = 19, /* 24-bit AFBC only */
    _GDMA_COLOR_FORMAT_RGB556 = 20, /* 16-bit RGB (556) with constant alpha */
    _GDMA_COLOR_FORMAT_RGB655 = 21, /* 16-bit RGB (655) with constant alpha */
    _GDMA_COLOR_FORMAT_RGB888 = 22, /* 24-bit RGB (888) with constant alpha */
    _GDMA_COLOR_FORMAT_ARGB8888_ARGB6TO8 = 24, /* 32-bit AFBC only */
    _GDMA_COLOR_FORMAT_YCBYCR888 = 28, /* 24-bit YCBCRA (888) */

    /* litttle endian below */
    _GDMA_COLOR_FORMAT_4BIT_LITTLE = (_BIT5 | 1), /* 4-bit index */
    _GDMA_COLOR_FORMAT_8BIT_LITTLE = (_BIT5 | 2), /* 8-bit index */
    _GDMA_COLOR_FORMAT_RGB565_LITTLE = (_BIT5 | 4), /* 16-bit RGB (565) with constant alpha */
    _GDMA_COLOR_FORMAT_ARGB1555_LITTLE = (_BIT5 | 5), /* 16-bit ARGB (1555) */
    _GDMA_COLOR_FORMAT_ARGB4444_LITTLE = (_BIT5 | 6), /* 16-bit ARGB (4444) */
    _GDMA_COLOR_FORMAT_ARGB8888_LITTLE = (_BIT5 | 7), /* 32-bit ARGB (8888) */
    _GDMA_COLOR_FORMAT_YCBYCR88_LITTLE = (_BIT5 | 10), /* M-cap 422 */
    _GDMA_COLOR_FORMAT_YCBCRA4444_LITTLE = (_BIT5 | 11), /* 16-bit YCBCRA (4444) */
    _GDMA_COLOR_FORMAT_YCBCRA8888_LITTLE = (_BIT5 | 12), /* 32-bit YCBCRA (8888) */
    _GDMA_COLOR_FORMAT_RGBA5551_LITTLE = (_BIT5 | 13), /* 16-bit RGBA (5551) */
    _GDMA_COLOR_FORMAT_RGBA4444_LITTLE = (_BIT5 | 14), /* 16-bit RGBA (4444) */
    _GDMA_COLOR_FORMAT_RGBA8888_LITTLE = (_BIT5 | 15), /* 32-bit RGBA (8888) */
    _GDMA_COLOR_FORMAT_ARGB6666_LITTLE = (_BIT5 | 17), /* 24-bit RGBA (6666) */
    _GDMA_COLOR_FORMAT_ARGB8888_RGB6TO8_LITTLE = (_BIT5 | 18), /* 32-bit AFBC only */
    _GDMA_COLOR_FORMAT_RGB888_RGB6TO8_LITTLE = (_BIT5 | 19), /* 24-bit AFBC only */
    _GDMA_COLOR_FORMAT_RGB556_LITTLE = (_BIT5 | 20), /* 16-bit RGB (556) with constant alpha */
    _GDMA_COLOR_FORMAT_RGB655_LITTLE = (_BIT5 | 21), /* 16-bit RGB (655) with constant alpha */
    _GDMA_COLOR_FORMAT_RGB888_LITTLE = (_BIT5 | 22), /* 24-bit RGB (888) with constant alpha */
    _GDMA_COLOR_FORMAT_ARGB8888_ARGB6TO8_LITTLE = (_BIT5 | 24), /* 32-bit AFBC only */
    _GDMA_COLOR_FORMAT_YCBYCR888_LITTLE = (_BIT5 | 28), /* 24-bit YCBCRA (888) */
} EnumGosdGdmaColorType;

typedef struct
{
    EnumGosdDisplayOSD enumOSD;
    StructGosdGdmaWinWH stFullWH;

    EnumGosdGdmaColorType enumColorType;
    EnumGosdRGBOrder enumRgbOrder;
    BYTE ucAlpha; // 0 : alpha function disable

    DWORD ulOsdAddr;
    DWORD ulPaletteAddr;
    DWORD ulPitch;

    DWORD ulColorKey;
    BYTE b1ColorKeyEn                   : 1; // color key function enable / disable

#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    BYTE b1Compressed                   : 1; // indicate this picture needs to decompress
#endif
} StructGosdGdmaCreateWin;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile DWORD g_pulGosdDispOsdDisplayingSurfaceId[_GOSD_PLANE_MAXNUM];

// __attribute__((section(".ddr_data.g_ppstGosdDispOsdContinuousArgument"), aligned(32)))
extern volatile StructGosdDispOsdDisplayArgument g_ppstGosdDispOsdContinuousArgument[_GOSD_PLANE_MAXNUM][_GOSD_CONTINUOUS_STEP_MAX];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
extern void ScalerGosdDispOsdSetRegSharpness(EnumGosdDisplayOSD enumOsd, DWORD *pulSharpnessTable, EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdDisplayDisableWithBackup(void);
extern void ScalerGosdDispOsdDisplayEnableByBackup(void);
#endif

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
extern void ScalerGosdDispOsdInitial(EnumGosdDisplayOSD enumOSD);
extern EnumGosdSyncCmdFeedBack ScalerGosdDispOsdDisplaySurface(StructGosdDispOsdDisplayArgument *pstArgument);
extern bit ScalerGosdDispOsdGetOsdParam(EnumGosdDisplayOSD enumOsd, StructGosdDisplayOsdParam *pstParam);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerGosdDispOsdSetExtension(BYTE ucExtension);
#endif

extern bit ScalerGosdDispOsdGetDisplaying(EnumGosdDisplayOSD enumOsd);
extern void ScalerGosdDispOsdSetGdmaDBApply(EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdSetGdmaSetDBTriggerEvent(EnumGosdGdmaDBTriggerEvent enumDBEvent);
extern EnumGosdGdmaStatus ScalerGosdDispOsdSetGdmaClearRegion(EnumGosdDisplayOSD enumOSD, StructGosdGdmaClearX stClear_x, StructGosdGdmaClearY stClear_y, bit bClearEnable, EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdSetGdmaOsdDisable(EnumGosdDisplayOSD enumOSD, EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdSetMixerOSDEnable(EnumGosdDisplayOSD enumOSD, bit bEnable, EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdSetMixerPlaneAlpha(EnumGosdMixerOrder enumMixerOrder, StructGosdMixerPlaneAlpha_ARGB stAlphaARGB, StructGosdMixerPlaneOffset_ARGB stOffsetARGB, BYTE ucPlaneAlphaEnable, EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdSetMixerLayer(EnumGosdDisplayOSD enumOSD, EnumGosdMixerOrder enumMixerOrder, EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdSetMixerFactor(StructGosdMixerLayerSetting *pstMixer, EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdSetTimingGenEn(bit bEn);
#endif // #if(_GOSD_SUPPORT == _ON)

