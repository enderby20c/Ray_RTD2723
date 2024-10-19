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
// ID Code      : ScalerGosdSeInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_GOSD_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GOSDSE_CMD_LENGTH_DEFAULT                 0x00001000UL

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _GOSD_SEINFO_OPERATION_MODE_FCV = 0,
    _GOSD_SEINFO_OPERATION_MODE_BITBLIT = 1,
    _GOSD_SEINFO_OPERATION_MODE_STRETCH = 2,
    _GOSD_SEINFO_OPERATION_MODE_STRETCH_BITBLIT = 3
}EnumGosdSeOperationMode;

typedef enum
{
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8 = 0x2,
    _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8U8 = 0x3,
#endif
    _GOSD_SEINFO_COLOR_FORMAT_RGB565 = 0x8,
    _GOSD_SEINFO_COLOR_FORMAT_RGB888 = 0x9,
    _GOSD_SEINFO_COLOR_FORMAT_ARGB1555 = 0xA,
    _GOSD_SEINFO_COLOR_FORMAT_ARGB4444 = 0xB,
    _GOSD_SEINFO_COLOR_FORMAT_ARGB8888 = 0xC,
    _GOSD_SEINFO_COLOR_FORMAT_INDEX8 = 0xE,
    _GOSD_SEINFO_COLOR_FORMAT_YUV444 = 0x10,
    _GOSD_SEINFO_COLOR_FORMAT_YV12_422 = 0x14,
    _GOSD_SEINFO_COLOR_FORMAT_NV12_422 = 0x15,
    _GOSD_SEINFO_COLOR_FORMAT_YUY2_422 = 0x16,
    _GOSD_SEINFO_COLOR_FORMAT_YV12_420 = 0x18,
    _GOSD_SEINFO_COLOR_FORMAT_NV12_420 = 0x19
}EnumGosdSeColorFormat;

typedef enum
{
    _GOSD_SEINFO_ARGB_FORMAT,
    _GOSD_SEINFO_AFBC_FORMAT,
    _GOSD_SEINFO_YUV_FORMAT
}EnumGosdSeColorFormatType;

typedef enum
{
    _GOSD_SEINFO_ARGB_ORDER_ARGB = 0,
    _GOSD_SEINFO_ARGB_ORDER_ARBG = 1,
    _GOSD_SEINFO_ARGB_ORDER_AGRB = 2,
    _GOSD_SEINFO_ARGB_ORDER_AGBR = 3,
    _GOSD_SEINFO_ARGB_ORDER_ABRG = 4,
    _GOSD_SEINFO_ARGB_ORDER_ABGR = 5,

    _GOSD_SEINFO_ARGB_ORDER_RAGB = 8,
    _GOSD_SEINFO_ARGB_ORDER_RABG = 9,
    _GOSD_SEINFO_ARGB_ORDER_RGAB = 10,
    _GOSD_SEINFO_ARGB_ORDER_RGBA = 11,
    _GOSD_SEINFO_ARGB_ORDER_RBAG = 12,
    _GOSD_SEINFO_ARGB_ORDER_RBGA = 13,

    _GOSD_SEINFO_ARGB_ORDER_GARB = 16,
    _GOSD_SEINFO_ARGB_ORDER_GABR = 17,
    _GOSD_SEINFO_ARGB_ORDER_GRAB = 18,
    _GOSD_SEINFO_ARGB_ORDER_GRBA = 19,
    _GOSD_SEINFO_ARGB_ORDER_GBAR = 20,
    _GOSD_SEINFO_ARGB_ORDER_GBRA = 21,

    _GOSD_SEINFO_ARGB_ORDER_BARG = 24,
    _GOSD_SEINFO_ARGB_ORDER_BAGR = 25,
    _GOSD_SEINFO_ARGB_ORDER_BRAG = 26,
    _GOSD_SEINFO_ARGB_ORDER_BRGA = 27,
    _GOSD_SEINFO_ARGB_ORDER_BGAR = 28,
    _GOSD_SEINFO_ARGB_ORDER_BGRA = 29
}EnumGosdSeArgbOrder;

typedef enum
{
    _GOSD_SEINFO_OPCODE_WRITE_REGISTER = 0x01,
    _GOSD_SEINFO_OPCODE_FETCH_CLUT = 0x02,
    _GOSD_SEINFO_OPCODE_LOCK_CLUT = 0x04,
    _GOSD_SEINFO_OPCODE_EXT_FMTFCV = 0x0B,
    _GOSD_SEINFO_OPCODE_NOP = 0x0F
} EnumGosdSeOpCode;

typedef enum
{
    _GOSD_SEINFO_REGMODE_REGISTER = 0,
    _GOSD_SEINFO_REGMODE_CLUT = 1
} EnumGosdSeRegMode;

typedef enum
{
    _GOSD_SEINFO_BLENDING_ROP = 0,
    _GOSD_SEINFO_BLENDING_FB = 2,
    _GOSD_SEINFO_BLENDING_GL = 3,
    _GOSD_SEINFO_BLENDING_ALPHA = 4,

    _GOSD_SEINFO_BLENDING_MAX = 999
} EnumGosdSeBlendingMode;

typedef enum
{
    _GOSD_SEINFO_ROPCODE_BLACK = 0,
    _GOSD_SEINFO_ROPCODE_AND = 1,
    _GOSD_SEINFO_ROPCODE_AND_NOT = 2,
    _GOSD_SEINFO_ROPCODE_COPY = 3,
    _GOSD_SEINFO_ROPCODE_NOT_AND = 4,
    _GOSD_SEINFO_ROPCODE_B = 5,
    _GOSD_SEINFO_ROPCODE_XOR = 6,
    _GOSD_SEINFO_ROPCODE_OR = 7,
    _GOSD_SEINFO_ROPCODE_NOR = 8,
    _GOSD_SEINFO_ROPCODE_XNOR = 9,
    _GOSD_SEINFO_ROPCODE_NOT_B = 10,
    _GOSD_SEINFO_ROPCODE_OR_NOT = 11,
    _GOSD_SEINFO_ROPCODE_NOT_A = 12,
    _GOSD_SEINFO_ROPCODE_NOT_OR = 13,
    _GOSD_SEINFO_ROPCODE_NAND = 14,
    _GOSD_SEINFO_ROPCODE_WHITE = 15,
} EnumGosdSeRopCode;

typedef enum
{
    _GOSD_SEINFO_BLENDING_COLORKEY_NONE = 0,
    _GOSD_SEINFO_BLENDING_COLORKEY_SOURCE = 1,
    _GOSD_SEINFO_BLENDING_COLORKEY_DESTINATION = 2,
    _GOSD_SEINFO_BLENDING_COLORKEY_BOTH = 3
} EnumGosdSeBlendingColorkeyMode;

typedef enum
{
    _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONST = 0,
    _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_CONST = 1,
    _GOSD_SEINFO_BLENDING_DFB_ALPHA_DEST = 2,
    _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_DEST = 3,
    _GOSD_SEINFO_BLENDING_DFB_ALPHA_SRC = 4,
    _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_SRC = 5,
    _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONSTANT_0 = 6,
    _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONSTANT_1 = 7,

    _GOSD_SEINFO_BLENDING_DFB_ALPHA_MAX = 999,
} EnumGosdSeBlendingAlphaMode;

typedef enum
{
    _GOSD_SEINFO_BLENDING_DFB_CLR_CONSTANT_0 = 0,
    _GOSD_SEINFO_BLENDING_DFB_CLR_CONSTANT_1 = 1,
    _GOSD_SEINFO_BLENDING_DFB_CLR_DESTALPHA = 2,
    _GOSD_SEINFO_BLENDING_DFB_CLR_1_DESTALPHA = 3,
    _GOSD_SEINFO_BLENDING_DFB_CLR_SRCALPHA = 4,
    _GOSD_SEINFO_BLENDING_DFB_CLR_1_SRCALPHA = 5,
    _GOSD_SEINFO_BLENDING_DFB_CLR_SRCCLR = 6,
    _GOSD_SEINFO_BLENDING_DFB_CLR_1_SRCCLR = 7,
    _GOSD_SEINFO_BLENDING_DFB_CLR_DESTCLR = 8,
    _GOSD_SEINFO_BLENDING_DFB_CLR_1_DESTCLR = 9,
    _GOSD_SEINFO_BLENDING_DFB_CLR_MIN_SRCALPHA_1_DESTALPHA = 10,

    _GOSD_SEINFO_BLENDING_DFB_CLR_MAX = 999,
} EnumGosdSeBlendingColorMode;

typedef enum
{
    _GOSD_SEINFO_STRETCH_EVEN = 0,
    _GOSD_SEINFO_STRETCH_ODD = 1,
} EnumGosdSeStretchType;

typedef enum
{
    _GOSD_SEINFO_STRETCH_2TAP = 0,
    _GOSD_SEINFO_STRETCH_4TAP = 1,
}EnumGosdSeStretchTap;

typedef enum
{
    _GOSD_SEINFO_STRETCH_FIR = 0,
    _GOSD_SEINFO_STRETCH_REPEATE_DROP = 1
}EnumGosdSeStretchAlgo;

typedef enum
{
    _GOSD_SEINFO_LAYERTYPE_SRC1 = 0,
    _GOSD_SEINFO_LAYERTYPE_SRC2 = 1,
    _GOSD_SEINFO_LAYERTYPE_RSLT = 2
}EnumGosdSeLayerType;

typedef struct
{
    EnumGosdSeStretchType enumHorizontalTypeSel;
    EnumGosdSeStretchType enumVerticalTypeSel;
    EnumGosdSeStretchTap enumHorizontalTapNumberSel;
    EnumGosdSeStretchTap enumVerticalTapNumberSel;
}StructGosdSeStretchConfig;

typedef struct
{
    DWORD ulSurfaceId;
    EnumGosdSeColorFormat enumFormat;
    EnumGosdSeArgbOrder enumArgbOrder;
    DWORD ulAddress;
    DWORD ulLength;
    WORD usPitch;
    DWORD ulAddressC1;
    WORD usPitchC1;
    // DWORD ulAddressC2;
    // WORD usPitchC2;
    WORD usFullWidth;
    WORD usFullHeight;
    bit bBigEndian;
    DWORD ulClutAddress;
    bit bAfbcYuvTrans;
}StructGosdSeSurfaceInfo;

typedef struct
{
    EnumGosdSeLayerType enumLayerType;
    bit bSelectConst;  // src: input_select, rslt: output_alpha
    DWORD ulConstClrValue;
    BYTE ucConstAlphaValue;
    StructGosdSeSurfaceInfo stSurface;
    WORD usDataX;
    WORD usDataY;
    WORD usDataWidth;
    WORD usDataHeight;
    EnumOsdRotateType enumRsltRotateModeSel;
    EnumGosdSeMirrorMode enumRsltMirrorModeSel;
}StructGosdSeLayerInfo;

typedef struct
{
    bit bLayerControl;

    EnumGosdSeBlendingMode enumModeSel;

    EnumGosdSeRopCode enumRopCode;

    EnumGosdSeBlendingColorkeyMode enumColorKeyModeSel;
    DWORD ulSrcColorKeyValue;
    DWORD ulDstColorKeyValue;
    bit bEnableDstPremultiply;
    bit bEnableSrcPremulcolor;
    bit bEnableSrcPremultiply;
    bit bEnableXor;
    bit bEnableColorize;
    bit bEnableColorAlpha;
    bit bEnableAlphaChannel;
    bit bEnableDemultiply;
    EnumGosdSeBlendingAlphaMode enumDstAlphaModeSel;
    EnumGosdSeBlendingAlphaMode enumSrcAlphaModeSel;
    EnumGosdSeBlendingColorMode enumDstClrModeSel;
    EnumGosdSeBlendingColorMode enumSrcClrModeSel;
#if(_HW_GOSD_SE_BITBLIT_OPENGL_CONSTANT_COEFF_SUPPORT == _ON)
    BYTE ucGLDstAlphaIndex;
    BYTE ucGLSrcAlphaIndex;
    BYTE ucGLDstClrIndex;
    BYTE ucGLSrcClrIndex;
#else
    BYTE b6GLDstAlphaIndex : 6;
    BYTE b6GLSrcAlphaIndex : 6;
    BYTE b6GLDstClrIndex : 6;
    BYTE b6GLSrcClrIndex : 6;
#endif
    BYTE ucDstAlphaValue;
    BYTE ucSrcAlphaValue;
    BYTE ucConstAlphaValue;
    BYTE ucConstAlphaValueForBlendColor;
    DWORD ulConstClrValue;

    EnumGosdSeLinearGradientMode enumSrc2LinearGradientModeSel; // Src2 Only
    DWORD ulStartClrValue;
    WORD usClrStepXAlpha;
    WORD usClrStepXRed;
    WORD usClrStepXGreen;
    WORD usClrStepXBlue;
    WORD usClrStepYAlpha;
    WORD usClrStepYRed;
    WORD usClrStepYGreen;
    WORD usClrStepYBlue;
}StructGosdSeBitBlitInfo;

typedef struct
{
    EnumGosdSeStretchAlgo enumAlgoSel;
}StructGosdSeStretchInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerGosdSeGetExecute(void);
extern bit ScalerGosdSeCheckSurfaceStatus(DWORD ulSurfaceId, EnumGosdSeLayerType enumType);

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
extern void ScalerGosdSeInitial(void);
extern void ScalerGosdSePowerOnInitial(void);
extern EnumGosdSyncCmdFeedBack ScalerGosdSeFormatConversion(StructGosdSeLayerInfo *pstSrc1LayerInfo, StructGosdSeLayerInfo *pstRsltLayerInfo);
extern EnumGosdSyncCmdFeedBack ScalerGosdSeBitBlit(StructGosdSeLayerInfo *pstSrc1LayerInfo, StructGosdSeLayerInfo *pstSrc2LayerInfo, StructGosdSeLayerInfo *pstRsltLayerInfo, StructGosdSeBitBlitInfo *pstBitBlitInfo);
extern EnumGosdSyncCmdFeedBack ScalerGosdSeStretch(StructGosdSeLayerInfo *pstSrc1LayerInfo, StructGosdSeLayerInfo *pstRsltLayerInfo, StructGosdSeStretchInfo *pstStretchInfo);
extern EnumGosdSyncCmdFeedBack ScalerGosdSeStretchBitBlit(StructGosdSeLayerInfo *pstSrc1LayerInfo, StructGosdSeLayerInfo *pstSrc2LayerInfo, StructGosdSeLayerInfo *pstRsltLayerInfo, StructGosdSeStretchInfo *pstStretchInfo, StructGosdSeBitBlitInfo *pstBitBlitInfo);
extern bit ScalerGosdSePollingDone(DWORD ulWaitTimeout);
extern void ScalerGosdSeDone_Handler(void);
extern EnumGosdSyncCmdFeedBack ScalerGosdSeExecute(void);
#endif

#endif
