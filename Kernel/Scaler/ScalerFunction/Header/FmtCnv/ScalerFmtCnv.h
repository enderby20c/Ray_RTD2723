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
// ID Code      : ScalerFmtCnv.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_FMT_CNV_H__
#define __SCALER_FMT_CNV_H__


#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FC_SUB3_VS_DELAY_DISABLE,
    _FC_SUB3_VS_DELAY_FROM_SUB1,
    _FC_SUB3_VS_DELAY_NONE,
} EnumFCSub3VsDelayType;

typedef enum
{
    _FC_HALFSD_DROP_MODE,
    _FC_HALFSD_AVERAGE_MODE,
    _FC_HALFSD_1331_MODE,
    _FC_HALFSD_1111_MODE,
} EnumFCHalfSDMode;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerFmtCnvResetPath(EnumInputDataPath enumInputDataPath, bit bEnable);

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
extern void ScalerFmtCnvHalfSDSettingByClock(EnumInputDataPath enumInputDataPath, WORD usPixelClock);
extern void ScalerFmtCnvHalfSDSetFactor(EnumInputDataPath enumInputDataPath, BYTE ucFactor);
extern BYTE ScalerFmtCnvHalfSDGetRegisterFactor(BYTE ucHalfSDSetting);
extern void ScalerFmtCnvHalfSDSetFirstPixel(EnumInputDataPath enumInputDataPath, WORD usHstart);
extern bit ScalerFmtCnvHalfSDGetFirstPixel(EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvHalfSDSetFactorByWidth(EnumInputDataPath enumInputDataPath, WORD usWidth);
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
extern void ScalerFmtCnvFtoPInterlaceSetting(EnumInputDataPath enumInputDataPath);
#endif

extern void ScalerFmtCnvCtsFifoInitSetting(EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvSetSourceType(EnumInputDataPath enumInputDataPath, EnumFormatConversionSourceType enumFormatConversionSourceType);
extern void ScalerFmtCnvSetVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable);
extern void ScalerFmtCnvCheckHsExpandEnable(EnumInputDataPath enumInputDataPath, WORD usHSwidth);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerFmtCnvFBFinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvFBSetStatus(EnumFrontBackMode enumFrontBackMode);
extern BYTE ScalerFmtCnvAdjustExtensionLen(void);
#endif

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
extern void ScalerFmtCnvSetPixelMode(EnumInputDataPath enumInputDataPath, EnumFmtCnvPixelMode enumFmtCnvPixelMode);
#endif

#if(_DUAL_DP_SUPPORT == _ON)
extern void ScalerFmtCnvSetDualDpSourceType(void);
#endif

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
extern void ScalerFmtCnvEagleSightEnable(bit bEnable);
extern void ScalerFmtCnvEagleSightSetPixelModeConv(EnumFmtCnvPixelMode enumFmtCnvPixelMode);
#endif
#endif // End of #if(_FORMAT_CONVERSION_SUPPORT == _ON)

extern EnumFCSub3VsDelayType ScalerFmtCnvGetSub3VSyncDelayType(void);
extern EnumFCHalfSDMode ScalerFmtCnvGetHalfSDModeSelect(EnumInputDataPath enumInputDataPath, BYTE ucFactor);


#endif // End of #ifndef __SCALER_FMT_CNV_H__
