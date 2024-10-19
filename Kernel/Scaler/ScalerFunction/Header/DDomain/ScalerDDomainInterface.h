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
// ID Code      : ScalerDDomainInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Structure of HV Background Active Diff
//--------------------------------------------------
typedef struct
{
    BYTE b1HBWidthDiff : 1;
    BYTE b1VBHeightDiff : 1;
} StructHVBActiveDiff;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern WORD ScalerDDomainGetDisplayFormat_R1a1(EnumDisplayFormatItem enumItem);
extern void ScalerDDomainSetDisplayFormat_R1a1(EnumDisplayFormatItem enumItem, WORD usData);
extern WORD ScalerDDomainGetDisplayBackground_R1(EnumDisplayBackgroundItem enumItem);
extern void ScalerDDomainSetDisplayBackground_R1(EnumDisplayBackgroundItem enumItem, WORD usData);

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
extern WORD ScalerDDomainGetDisplayFormat_R1a2(EnumDisplayFormatItem enumItem);
extern void ScalerDDomainSetDisplayFormat_R1a2(EnumDisplayFormatItem enumItem, WORD usData);
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
extern WORD ScalerDDomainGetDisplayFormat_R2a1(EnumDisplayFormatItem enumItem);
extern void ScalerDDomainSetDisplayFormat_R2a1(EnumDisplayFormatItem enumItem, WORD usData);
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
extern WORD ScalerDDomainGetDisplayBackground_R2(EnumDisplayBackgroundItem enumItem);
extern void ScalerDDomainSetDisplayBackground_R2(EnumDisplayBackgroundItem enumItem, WORD usData);
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
extern WORD ScalerDDomainGetDisplayFormat_R2a2(EnumDisplayFormatItem enumItem);
extern void ScalerDDomainSetDisplayFormat_R2a2(EnumDisplayFormatItem enumItem, WORD usData);
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
extern WORD ScalerDDomainGetDisplayBackground_R3(EnumDisplayBackgroundItem enumItem);
extern void ScalerDDomainSetDisplayBackground_R3(EnumDisplayBackgroundItem enumItem, WORD usData);
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
extern WORD ScalerDDomainGetDisplayFormat_R3a1(EnumDisplayFormatItem enumItem);
extern void ScalerDDomainSetDisplayFormat_R3a1(EnumDisplayFormatItem enumItem, WORD usData);
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
extern WORD ScalerDDomainGetDisplayFormat_R3a2(EnumDisplayFormatItem enumItem);
extern void ScalerDDomainSetDisplayFormat_R3a2(EnumDisplayFormatItem enumItem, WORD usData);
#endif

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
extern void ScalerDDomainBackgroundSetColor10bit(WORD usRed, WORD usGreen, WORD usBlue, EnumDBApply enumDBApply);
extern void ScalerDDomainBoxPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue);
extern void ScalerDDomainPatternGenFrontSetBox(BYTE *pucCommand, bit bEnable);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDDomainPatternGenBackSetBox(BYTE *pucCommand, bit bEnable);
#endif
#endif

extern void ScalerDDomainSetDspcLineLength(void);
#if((_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON))
extern void ScalerDDomainSetBackgroundVerticalChange(EnumDisplayMode enumDisplayMode);
#endif
extern bit ScalerDDomainGetBackgroundStatus(EnumDDomainRegion enumDDomainRegion);
extern void ScalerDDomainBackgroundEnableByRegion(EnumDisplayRegion enumDisplayRegion, bit bEnable);
extern void ScalerDDomainBackgroundEnable(EnumDDomainRegion enumDDomainRegion, bit bEnable);
extern void ScalerDDomainBackgroundSetColorByRegion(EnumDisplayRegion enumDisplayRegion, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
extern void ScalerDDomainBackgroundSetColor(EnumDDomainRegion enumDDomainRegion, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
extern void ScalerDDomainPatternGenEnable(bit bEnable);
extern void ScalerDDomainPatternGenModeAdjust(EnumDPatternGenMode enumDPatternGenMode);
extern void ScalerDDomainPatternGenAdjustColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
extern void ScalerDDomainPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue);

extern void ScalerDDomainBoxPatternGenAdjustColor10bit_Inside(WORD usRed, WORD usGreen, WORD usBlue);
extern void ScalerDDomainBoxPatternGenAdjustColor10bit_Outside(WORD usRed, WORD usGreen, WORD usBlue);
extern void ScalerDDomainBoxPatternGenSetWidthHeight(WORD usWidth1, WORD usWidth2, WORD usHeight1, WORD usHeight2);
extern void ScalerDDomainBoxPatternGenSetRegionInOut(bit bEnable, StructDPatternGenBoxSetting *pstDPatternGenBoxSetting);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDDomainBoxPatternGenSetWidthHeight_Back(WORD usWidth1, WORD usWidth2, WORD usHeight1, WORD usHeight2);
extern void ScalerDDomainBoxPatternGenSetRegionInOut_Back(bit bEnable, StructDPatternGenBoxSetting *pstDPatternGenBoxSetting);
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
extern void ScalerDDomainFreeSyncODSetBackgroundGrayLevel(void);
#endif

#if(_FW_DISPLAYTOP_AVG_REQ_SUPPORT == _ON)
extern void ScalerDDomainSetDdmReqAvgReqFactor(EnumDisplayRegion enumDisplayRegion, WORD usFifoHwidth, WORD usDdmHwidth, WORD usHtotal);
extern void ScalerDDomainSetDdmReqAvgReqEnable(EnumDisplayRegion enumDisplayRegion, bit bEnable);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern WORD ScalerDDomainGetFBNoneSepR1a1ActiveHwidth(void);
extern WORD ScalerDDomainGetFBNoneSepR3a1ActiveHwidth(void);
extern WORD ScalerDDomainGetFBNoneSepR1a2ActiveHwidth(void);
extern WORD ScalerDDomainGetFBNoneSepR3a2ActiveHwidth(void);
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
extern void ScalerDDomainSetCaptureWindowEnable(bit bCapWinEnable);
extern void ScalerDDomainSetCaptureWindowBackground(EnumDisplayBackgroundItem enumItem, WORD usData);
extern WORD ScalerDDomainGetCaptureWindowBackground(EnumDisplayBackgroundItem enumItem);
extern void ScalerDDomainSetCaptureWindowActiveRegion(EnumDisplayFormatItem enumItem, WORD usData);
extern WORD ScalerDDomainGetCaptureWindowActiveRegion(EnumDisplayFormatItem enumItem);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDDomainSetExtensionExtract(bit bEnable);
extern void ScalerDDomainSetDspcDenDelay(BYTE ucData);
extern BYTE ScalerDDomainGetDspcDenDelay(void);
extern void ScalerDDomainSetCaptureWindowEnable_Back(bit bCapWinEnable);
extern void ScalerDDomainSetCaptureWindowBackground_Back(EnumDisplayBackgroundItem enumItem, WORD usData);
extern WORD ScalerDDomainGetCaptureWindowBackground_Back(EnumDisplayBackgroundItem enumItem);
extern void ScalerDDomainSetCaptureWindowActiveRegion_Back(EnumDisplayFormatItem enumItem, WORD usData);
extern WORD ScalerDDomainGetCaptureWindowActiveRegion_Back(EnumDisplayFormatItem enumItem);
extern void ScalerDDomainSetCaptureWindowRefBG(bit bEnable);
extern WORD ScalerDDomainGetExtension(void);
#endif
#endif
#endif

#if((_2P_PIP_DISPLAY_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
extern bit ScalerDDomainGetR2DenEnable(void);
extern void ScalerDDomainSetR2DenEnable(bit bEnable, EnumDBApply enumDBApply);
#endif

extern void ScalerDDomainSetResetDdmRegion(EnumDisplayRegion enumDisplayRegion);
extern void ScalerDDomainGetHVBActiveDiff(EnumDisplayRegion enumDisplayRegion, StructHVBActiveDiff *pstData);
#if(_HW_ADJ_A1_LB_START_ADDR == _ON)
extern void ScalerDDomainSetDisplayTopLBStartAddr(EnumDisplayRegion enumDisplayRegion, WORD usHorSize);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
extern bit ScalerDDomainGetPbplrFullStatus(void);
#endif
