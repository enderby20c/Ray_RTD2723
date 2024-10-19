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
// ID Code      : UserCommonGosdInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GOSD_AUTO_ADDRESS                      _MAX_ADDRESS_OF_32BIT
#define _GOSD_DEFAULT_POLLING_MS                (100)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    WORD usImageSourceStartFlashBank; // = _GOSD_IMAGE_SOURCE_FLASH_START_BANK in RTDxxxxGosdImageSource.h
    WORD usImageIndex;
} StructGosdLoadImageInfo;

typedef struct
{
    StructGosdRectangle stDrawWin; // crop size
    StructGosdPosition stCanvasPos; // position in canvas
    BYTE ucAlpha; // 0 : alpha function disable
    DWORD ulColorKey;
    BYTE b1ColorKeyEn                : 1; // color key function enable / disable
} StructGosdCreateWin;

typedef enum
{
    _DRAW_NO_POLLING = 0,
    _DRAW_POLLING
} EnumGosdDrawPolling;

typedef enum
{
    _GOSD_LOAD_NO_POLLING = 0,
    _GOSD_LOAD_POLLING
} EnumGosdLoadPolling;

typedef enum
{
    _GOSD_BLEND_ZERO = 0, // zero or, 0
    _GOSD_BLEND_ONE, // 1
    _GOSD_BLEND_DESTALPHA, // source color
    _GOSD_BLEND_INVDESTALPHA, // inverse source alpha
    _GOSD_BLEND_SRCALPHA, // source alpha
    _GOSD_BLEND_INVSRCALPHA, // inverse source alpha (1-Sa)
    _GOSD_BLEND_SRCCOLOR, // destination alpha
    _GOSD_BLEND_INVSRCCOLOR, // inverse destination lapha (1-Da)
    _GOSD_BLEND_DESTCOLOR, // destination color
    _GOSD_BLEND_INVDESTCOLOR, // inverse destination color
    _GOSD_BLEND_MINALPHA, // min of source alpha and inverse destination alpha
    _GOSD_BLEND_CONSTALPHA, // const alpha
    _GOSD_BLEND_INVCONSTALPHA, // inverse const alpha
} EnumGosdSeBlendFunction;

typedef enum
{
    _GOSD_BLEND_OPENGL_0 = 0,
    _GOSD_BLEND_OPENGL_1,
    _GOSD_BLEND_OPENGL_2,
    _GOSD_BLEND_OPENGL_3,
    _GOSD_BLEND_OPENGL_4,
    _GOSD_BLEND_OPENGL_5,
    _GOSD_BLEND_OPENGL_6,
    _GOSD_BLEND_OPENGL_7,
    _GOSD_BLEND_OPENGL_8,
    _GOSD_BLEND_OPENGL_9,
    _GOSD_BLEND_OPENGL_10,
    _GOSD_BLEND_OPENGL_11,
    _GOSD_BLEND_OPENGL_12,
    _GOSD_BLEND_OPENGL_13,
    _GOSD_BLEND_OPENGL_14,
    _GOSD_BLEND_OPENGL_15,
    _GOSD_BLEND_OPENGL_16,
    _GOSD_BLEND_OPENGL_17,
    _GOSD_BLEND_OPENGL_18,
    _GOSD_BLEND_OPENGL_19,
    _GOSD_BLEND_OPENGL_20,
    _GOSD_BLEND_OPENGL_21,
    _GOSD_BLEND_OPENGL_22,
    _GOSD_BLEND_OPENGL_23,
    _GOSD_BLEND_OPENGL_24,
    _GOSD_BLEND_OPENGL_25,
    _GOSD_BLEND_OPENGL_26,
    _GOSD_BLEND_OPENGL_27,
    _GOSD_BLEND_OPENGL_28,
    _GOSD_BLEND_OPENGL_29,
    _GOSD_BLEND_OPENGL_30,
    _GOSD_BLEND_OPENGL_31,
    _GOSD_BLEND_OPENGL_32,
    _GOSD_BLEND_OPENGL_33,
    _GOSD_BLEND_OPENGL_34,
    _GOSD_BLEND_OPENGL_35,
    _GOSD_BLEND_OPENGL_36,
    _GOSD_BLEND_OPENGL_37,
    _GOSD_BLEND_OPENGL_38,
    _GOSD_BLEND_OPENGL_39,
    _GOSD_BLEND_OPENGL_40,
    _GOSD_BLEND_OPENGL_41,
    _GOSD_BLEND_OPENGL_42,
    _GOSD_BLEND_OPENGL_43,
    _GOSD_BLEND_OPENGL_44,
    _GOSD_BLEND_OPENGL_45,
    _GOSD_BLEND_OPENGL_46,
    _GOSD_BLEND_OPENGL_47,
    _GOSD_BLEND_OPENGL_48,
    _GOSD_BLEND_OPENGL_49,
    _GOSD_BLEND_OPENGL_50,
    _GOSD_BLEND_OPENGL_51,
    _GOSD_BLEND_OPENGL_52,
    _GOSD_BLEND_OPENGL_53,
    _GOSD_BLEND_OPENGL_54,
    _GOSD_BLEND_OPENGL_55,
    _GOSD_BLEND_OPENGL_56,
    _GOSD_BLEND_OPENGL_57,
    _GOSD_BLEND_OPENGL_58,
    _GOSD_BLEND_OPENGL_59,
    _GOSD_BLEND_OPENGL_60,
    _GOSD_BLEND_OPENGL_61,
    _GOSD_BLEND_OPENGL_62,
    _GOSD_BLEND_OPENGL_63,
}EnumGosdSeOpenGlBlendFunction;

typedef enum
{
    _GOSD_BITBLIT_NOFX = 0x00000000, // uses none of the effects
    _GOSD_BITBLIT_BLEND_ALPHACHANNEL = 0x00000001, // enables blending and uses alphachannel from source
    _GOSD_BITBLIT_BLEND_COLORALPHA = 0x00000002, // enables blending and uses alpha value from color
    _GOSD_BITBLIT_COLORIZE = 0x00000004, // modulates source color with the color's r/g/b values
    _GOSD_BITBLIT_SRC_COLORKEY = 0x00000008, // don't blit pixels matching the source color key
    _GOSD_BITBLIT_DST_COLORKEY = 0x00000010, // write to destination only if the destination pixel matches the destination color key
    _GOSD_BITBLIT_SRC_PREMULTIPLY = 0x00000020, // modulates the source color with the (modulated) source alpha
    _GOSD_BITBLIT_DST_PREMULTIPLY = 0x00000040, // modulates the dest. color with the dest. alpha
    _GOSD_BITBLIT_DEMULTIPLY = 0x00000080, // divides the color by the alpha before writing the data to the destination
    _GOSD_BITBLIT_SRC_PREMULTCOLOR = 0x00000100, // modulates the source color with the color alpha
    _GOSD_BITBLIT_XOR = 0x00000200, // bitwise xor the destination pixels with the source pixels after premultiplication

    _GOSD_BITBLIT_ROTATE90 = 0x00000400, // rotate the image by 90 degree clockwise
    _GOSD_BITBLIT_ROTATE180 = 0x00000800, // rotate the image by 180 degree clockwise
    _GOSD_BITBLIT_ROTATE270 = 0x00001000, // rotate the image by 270 degree clockwise

    _GOSD_BITBLIT_VERTICAL_MIRROR = 0x00002000,    // flip vertically (x positon is not changed)
    _GOSD_BITBLIT_HORIZONTAL_MIRROR = 0x00004000,  // flip horizontally (y positon is not changed)

    _GOSD_BITBLIT_OUTPUT_ALPHA_CONST = 0x00008000,  // Force the output of alpha channel to be a constant value
} EnumGosdSeBitBlitFlags;

typedef enum
{
    _GOSD_BITBLIT_MODE_ROP = 0,
    _GOSD_BITBLIT_MODE_FB = 2,
    _GOSD_BITBLIT_MODE_GL = 3,
    _GOSD_BITBLIT_MODE_ALPHA = 4
} EnumGosdSeBitBlitMode;

typedef struct
{
    EnumGosdSeBlendFunction enumSrcAlphaBlend;
    EnumGosdSeBlendFunction enumDestAlphaBlend;
    BYTE ucSrcAlpha;
    BYTE ucDestAlpha;
    DWORD ulSrcColorKey;
    DWORD ulDestColorKey;
} StructGosdSeAlphaSettings;

typedef struct
{
    EnumGosdSeBlendFunction enumSrcAlphaBlend;
    EnumGosdSeBlendFunction enumDestAlphaBlend;
    EnumGosdSeBlendFunction enumSrcColorBlend;
    EnumGosdSeBlendFunction enumDestColorBlend;
    BYTE ucSrcAlpha;
    BYTE ucDestAlpha;
    BYTE ucConstAlpha;
    BYTE ucConstAlphaForBlendColor;
    DWORD ulColor;
    DWORD ulSrcColorKey;
    DWORD ulDestColorKey;
} StructGosdSeDirectFbSettings;

typedef struct
{
#if(_HW_GOSD_SE_BITBLIT_OPENGL_CONSTANT_COEFF_SUPPORT == _ON)
    BYTE ucSrcAlphaBlend;
    BYTE ucDestAlphaBlend;
    BYTE ucSrcColorBlend;
    BYTE ucDestColorBlend;
#else
    BYTE b6SrcAlphaBlend : 6;
    BYTE b6DestAlphaBlend : 6;
    BYTE b6SrcColorBlend : 6;
    BYTE b6DestColorBlend : 6;
#endif
    BYTE ucSrcAlpha;
    BYTE ucDestAlpha;
    BYTE ucConstAlpha;
    BYTE ucConstAlphaForBlendColor;
    DWORD ulColor;
    DWORD ulSrcColorKey;
    DWORD ulDestColorKey;
} StructGosdSeOpenGlSettings;

typedef union
{
    StructGosdSeAlphaSettings stAlphaSettings;
    StructGosdSeDirectFbSettings stDirectFbSettings;
    StructGosdSeOpenGlSettings stOpenGlSettings;
} UnionGosdSeBitBlitSettings;

typedef struct
{
    EnumGosdSeBitBlitMode enumMode;
    UnionGosdSeBitBlitSettings unBitBlitSettings;
} StructGosdSeBitBlitSettings;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
extern EnumGosdSyncCmdFeedBack UserCommonGosdResetSync(DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdMemoryResetSync(DWORD ulWaitTimeout);

extern EnumGosdSyncCmdFeedBack UserCommonGosdGetSurfaceStatusSync(EnumGosdSurfaceStatus *penumStatus, DWORD ulSurfaceId, DWORD ulWaitTimeout);
extern bit UserCommonGosdPollingSurfaceStatusSync(EnumGosdSurfaceStatus enumTargetStatus, DWORD ulSurfaceId, DWORD ulWaitTimeout);

extern EnumGosdSyncCmdFeedBack UserCommonGosdCreateSurfaceSync(DWORD ulSurfaceId, EnumGosdPixelFormat enumFormat, WORD usWidth, WORD usHeight, DWORD ulAddr, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdReleaseSurfaceSync(DWORD ulSurfaceId, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdReleaseMultiSurfaceSync(DWORD ulSurfaceId, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdSetLoadImageInfoSync(DWORD ulSurfaceId, StructGosdLoadImageInfo *pstSrc, EnumGosdLoadPolling enumPolling, DWORD ulWaitTimeout);

extern EnumGosdSyncCmdFeedBack UserCommonGosdImageConvertSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdCopyPasteSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdRotateSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition, EnumOsdRotateType enumRotateSel, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdMirrorSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition, EnumGosdSeMirrorMode enumMirrorSel, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdDrawRectangleSync(DWORD ulSurfaceIdResult, StructGosdRectangle stRect, DWORD ulColor, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdDrawLinearGradientRectangleSync(DWORD ulSurfaceIdResult, StructGosdRectangle stRect, EnumGosdSeLinearGradientMode enumLinearGradientMode, DWORD ulStartColor, DWORD ulEndColor, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdBitBlitPasteSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdDestination, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stDestPosition, StructGosdPosition stOutPosition, DWORD ulBlitFlags, StructGosdSeBitBlitSettings *pstBlitSettings, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdStretchPasteSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdRectangle stOutRect, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdSretchBitBlitPasteSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdDestination, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stDestPosition, StructGosdRectangle stOutRect, DWORD ulBlitFlags, StructGosdSeBitBlitSettings *pstBlitSettings, DWORD ulWaitTimeout);
extern bit UserCommonGosdGetDrawing(void);

extern EnumGosdSyncCmdFeedBack UserCommonGosdDisplayOsdResetSync(EnumGosdDisplayOSD enumOsd, DWORD ulWaitTimeout);
extern EnumGosdSyncCmdFeedBack UserCommonGosdDisplaySurfaceSync(EnumGosdDisplayOSD enumOsd, DWORD ulSurfaceId, StructGosdRectangle *pstWinRect, StructGosdRectangle *pstDispRect, EnumDBApply enumDBApply, DWORD ulWaitTimeout);
extern void UserCommonGosdDisplayDisable(EnumGosdDisplayOSD enumOsd, EnumDBApply enumDBApply);
extern bit UserCommonGosdGetDisplaying(EnumGosdDisplayOSD enumOsd);
extern EnumGosdSyncCmdFeedBack UserCommonGosdDisplayGetOsdParamSync(EnumGosdDisplayOSD enumOsd, StructGosdDisplayOsdParam *pstOsdParam, DWORD ulWaitTimeout);
extern void UserCommonGosdDispOsdSetMixerLayer(EnumGosdDisplayOSD enumOsd, EnumGosdMixerOrder enumMixerOrder, EnumDBApply enumDBApply);
extern void UserCommonGosdDisplayOsdSetMixerBlend(StructGosdMixerLayerSetting *pstMixer, EnumDBApply enumDBApply);
extern void UserCommonGosdDisplayOsdSetMixerPlaneAlpha(EnumGosdMixerOrder enumMixerOrder, StructGosdMixerPlaneAlpha_ARGB stAlphaARGB, StructGosdMixerPlaneOffset_ARGB stOffsetARGB, BYTE ucPlaneAlphaEnable, EnumDBApply enumDBApply);
extern void UserCommonGosdDisplayOsdSetDBTriggerEvent(EnumGosdGdmaDBTriggerEvent enumDBEvent);
extern EnumGosdGdmaStatus UserCommonGosdDisplayOsdSetClearRegion(EnumGosdDisplayOSD enumOsd, StructGosdGdmaClearX stClear_x, StructGosdGdmaClearY stClear_y, bit bClearEnable, EnumDBApply enumDBApply);

extern void UserCommonGosdDisplayOsdSharpnessSetting(EnumGosdDisplayOSD enumOsd, DWORD *pulSharpnessTable, EnumDBApply enumDBApply);

extern void UserCommonGosdContinuousReset(EnumGosdDisplayOSD enumOsd);
extern bit UserCommonGosdContinuousStepDisplay(BYTE ucStepIdx, EnumGosdDisplayOSD enumOsd, DWORD ulSurfaceId, StructGosdRectangle *pstWinRect, StructGosdRectangle *pstDispRect);
extern bit UserCommonGosdContinuousStepDisplayChangePosition(BYTE ucStepIdx, EnumGosdDisplayOSD enumOsd, StructGosdPosition *pstDispPosition);
extern void UserCommonGosdContinuousEnable(BYTE ucTimerMs, EnumGosdDisplayOSD enumOsd, EnumGosdContinuousType enumType, BYTE ucTotalStepNumber);
extern void UserCommonGosdContinuousUrgentChange(EnumGosdDisplayOSD enumOsd);
extern bit UserCommonGosdGetContinuousStatus(EnumGosdDisplayOSD enumOsd);
#endif // end of #if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)

#endif
