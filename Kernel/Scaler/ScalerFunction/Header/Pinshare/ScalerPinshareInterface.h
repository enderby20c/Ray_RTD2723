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
// ID Code      : ScalerPinshareInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerPinshareConfig(BYTE ucPorStatus);
extern void ScalerPinshareInitial(void);
extern void ScalerPinshareGpioDdcPinSwitch(BYTE ucPinType);

extern bit ScalerPinshareGetDPSourcePower(EnumInputPort enumInputPort);

extern void ScalerPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType);
extern void ScalerPinsharePadDrivenConfig(EnumConfigPin enumConfigPin, EnumPadDrivingCurrentType enumPadDrivingCurrentType);
extern void ScalerPinsharePwmUpdSyncSwitch(void);
#if(_HDMI_SUPPORT == _ON)
extern void ScalerPinshareRxHpdPullDownSet(EnumInputPort enumInputPort, bit bEnable);
#endif

#if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)
extern void ScalerPinshareTypeCAdcInitial(void);
extern WORD ScalerPinshareTypeCAdcGetAdcIdealData(EnumTypeC10BitAdcChannel enumChannel);
#endif