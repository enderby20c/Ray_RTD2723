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
// ID Code      : ScalerFmtCnvInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FMTCNV_EXTENSION_DEFAULT                       (8)

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#define GET_FMTCNV_EXTENSION_LEN()                      (ScalerGetBit(P31_66_EXTENSION_NUM, 0x3F))
#else
#define GET_FMTCNV_EXTENSION_LEN()                      (0)
#endif
#define SET_FMTCNV_EXTENSION_LEN(x)                     {ScalerSetBit(P31_66_EXTENSION_NUM, ~0x3F, ((BYTE)(x) & 0x3F));}

#define _FMTCNV_HS_PULSE_WIDTH_MIN_VALUE                (4)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FORMAT_CONVERSION_P0 = _BIT0,
    _FORMAT_CONVERSION_P1 = _BIT1,
    _FORMAT_CONVERSION_P2 = _BIT2,
    _FORMAT_CONVERSION_P3 = _BIT3,

    _FORMAT_CONVERSION_P1_P0 = (_BIT1 | _BIT0),
    _FORMAT_CONVERSION_P2_P1_P0 = (_BIT2 | _BIT1 | _BIT0),

    _FORMAT_CONVERSION_P3_P2 = (_BIT3 | _BIT2),
    _FORMAT_CONVERSION_P3_P2_P1_P0 = (_BIT3 | _BIT2 | _BIT1 | _BIT0),
} EnumFormatConversionPath;

//--------------------------------------------------
// Enumerations of Format Conversion Capture DB Apply Ctrl
//--------------------------------------------------
typedef enum
{
    _FC_CAPTURE_DB_APPLY,
    _FC_CAPTURE_DB_CLR,
} EnumFmtCnvCapDBCtrl;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
extern EnumFormatConversionPath ScalerFmtCnvPathMapping(EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvInitialSetting(EnumSourceType enumSourceType, EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvFinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath, bit bWait);
extern bit ScalerFmtCnvCheckIDomainTimingAffected(EnumInputDataPath enumInputDataPath, EnumInputPort enumInputPort);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
extern void ScalerFmtCnvFtoPControl(EnumInputDataPath enumInputDataPath, bit bEnable);
extern void ScalerFmtCnvFtoPSetFifo(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath, WORD usHwidth, WORD usVstart);
#endif

extern bit ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(EnumInputDataPath enumInputDataPath);
extern EnumInputPort ScalerFmtCnvGetInputPortType(EnumInputDataPath enumInputDataPath);
extern bit ScalerFmtCnvResetStatus(EnumInputDataPath enumInputDataPath);

extern void ScalerFmtCnvSetBackgroundStatus(EnumInputDataPath enumInputDataPath, bit bEnable);
extern void ScalerFmtCnvSetBackgroundColor(EnumInputDataPath enumInputDataPath, BYTE ucR, BYTE ucG, BYTE ucB);

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
extern void ScalerFmtCnvEagleSightCaptureDoubleBufferEnable(bit bEn);
extern void ScalerFmtCnvEagleSightSetCaptureDBCtrl(EnumFmtCnvCapDBCtrl enumDBCtrl);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerFmtCnvFBGetFullToFBStatus(void);
extern bit ScalerFmtCnvFBGetFBModeStatus(void);
extern void ScalerFmtCnvFBSetOutputFormat(WORD usHwidth, BYTE ucHstart, BYTE ucHSwidth);
extern bit ScalerFmtCnvResetFBModeStatus(EnumInputDataPath enumInputDataPath);
#endif

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
extern EnumFmtCnvPixelMode ScalerFmtCnvGetPixelModeFactor(EnumInputDataPath enumInputDataPath);
extern EnumFmtCnvPixelMode ScalerFmtCnvGetPixelModeTargetFactor(EnumInputDataPath enumInputDataPath);
#endif
#endif

extern EnumFormatConversionSourceType ScalerFmtCnvConvertPortType(EnumInputPort enumInputPort);
extern bit ScalerFmtCnvPerformanceEqualCheck(EnumInputDataPath enumInputDataPath);
extern bit ScalerFmtCnvGetFrontBackSupport_EXINT5(void);
extern bit ScalerFmtCnvFtoPGetStatus_EXINT0(EnumInputDataPath enumInputDataPath);
extern EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(EnumInputDataPath enumInputDataPath);

extern DWORD ScalerFmtCnvGetPixelModeSpeedLimit(EnumInputDataPath enumInputDataPath, EnumFmtCnvPixelMode enumFmtCnvPixelMode);
extern DWORD ScalerFmtCnvGetDataPathMaxSpeedLimit(void);
