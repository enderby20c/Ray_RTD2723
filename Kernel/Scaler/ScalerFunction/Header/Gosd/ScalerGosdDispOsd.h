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
// ID Code      : ScalerGosdDispOsd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_GOSD_DISP_OSD_H__
#define __SCALER_GOSD_DISP_OSD_H__

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// Register mapping for osd1,osd2, osd3
#define GET_GOSD_GDMA_OSD_REG_SR_OFFSET(x)              (((x) == _GOSD_PLANE_OSD1) ? (0x0000) : (((x) == _GOSD_PLANE_OSD3) ? (0x100) : (0x80)))
#define GET_GOSD_GDMA_OSD_REG_FB_OFFSET()               (0x01000000)

// SR line buffer size
// #define _GDMA_SR_OSD1_2_LB_Size                      (2112)
// #define _GDMA_SR_OSD3_LB_Size                        (272)

// Max extension for FB mode
#define _GOSD_MAX_EXTENSION                             (4)

// For SR
#define _GOSD_SR_MAX_RATIO                              (4)
#define _GOSD_SR_FACTOR_BIT                             (20)
#define CLAMP(x, upper, lower)                          (MINOF((upper), MAXOF((x), (lower))))
#define _GOSD_SR_EXTENSION                              ((_GOSD_MAX_EXTENSION + 1) * _GOSD_SR_MAX_RATIO)

#define _GOSD_SHARPNESS_TABLE_LENGTH                    (30)

// DB wait timeout
#define _GOSD_BUFFER_WAIT_TIME                          (100)

// H proch limit
#define _GOSD_GDMA_H_PORCH_LIMIT                        (80)
#define _GOSD_GDMA_H_PORCH_LIMIT_FB                     (160)

// Width limit
#define _GOSD_GDMA_MAX_WIDTH_OSD1                       (_HW_GOSD_GDMA_MAX_WIDTH_OSD1)
#define _GOSD_GDMA_MAX_WIDTH_OSD3                       (512)



//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b2C0_sel               : 2;
    BYTE b2C1_sel               : 2;
    BYTE b2C2_sel               : 2;
    BYTE b2C3_sel               : 2;
} StructGosdMixerLayerSel;

typedef struct
{
    bit bOSDDisplayEn;
    StructGosdGdmaRectangle stWinRect;
    StructGosdGdmaRectangle stDispRect;
    StructGosdGdmaPlaneSRParam stDispSRParam;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    bit bOSDDisplayEn_Front;
    StructGosdGdmaRectangle stWinRect_Front;
    StructGosdGdmaRectangle stDispRect_Front;
    StructGosdGdmaPlaneSRParam stDispSRParam_Front;

    bit bOSDDisplayEn_Back;
    StructGosdGdmaRectangle stWinRect_Back;
    StructGosdGdmaRectangle stDispRect_Back;
    StructGosdGdmaPlaneSRParam stDispSRParam_Back;
#endif
} StructGosdDisplayParam;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
extern void ScalerGosdDispOsdCalculateSRParam(StructGosdGdmaSRParam *pstSR, WORD usWinSize, WORD usDispSize);
extern void ScalerGosdDispOsdConfigLineBuffer(BYTE ucL1_sta, BYTE ucL4_sta, BYTE ucL5_sta, BYTE ucL1_size, BYTE ucL4_size, BYTE ucL5_size);
extern void ScalerGosdDispOsdSetGdmaPaletteSelect(EnumGosdDisplayOSD enumOSD);
extern void ScalerGosdDispOsdSetRegScaleUp(EnumGosdDisplayOSD enumOSD);
extern void ScalerGosdDispOsdClearOsd(StructGosdGdmaOsdCtrl *pstPlane);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerGosdDispOsdSetSRExtension(void);
#endif

#if((_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON) && (_GOSD_DISPLAY_BW_CTRL_SUPPORT == _ON))
extern void ScalerGosdDispOsdBwCtrlGetClientInfo(StructBwCtrlClientInfo *pstClientInfo, StructGosdGdmaWinInfo *pstWinInfo, EnumGosdDisplayOSD enumOSD, bit bBack);
#endif
#endif

extern void ScalerGosdDispOsdSetDisplayDBApply(EnumDBApply enumDBApply);
extern void ScalerGosdDispOsdSetMixerDBApply(EnumDBApply enumDBApply);

#endif // #if(_GOSD_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_GOSD_DISP_OSD_H__
