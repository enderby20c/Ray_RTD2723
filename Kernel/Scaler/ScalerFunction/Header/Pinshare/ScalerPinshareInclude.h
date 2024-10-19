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
// ID Code      : ScalerPinshareInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of DP Cable ID Detect GPIO Voltage Stable Delay Time
//--------------------------------------------------
#define _PINSHARE_DP_UHBR_CABLE_ID_DETECT_STABLE_DELAY_TIME      200 // Unit: us


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _10_BIT_ADC_0,
    _10_BIT_ADC_1,
    _10_BIT_ADC_2,
    _10_BIT_ADC_3,
} Enum10BitAdcChannel;

#if((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1))
typedef enum
{
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    _LS_ADC_0,
    _LS_ADC_1,
    _LS_ADC_2,
    _LS_ADC_3,
#endif

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    _LS_ADC_0_0,
    _LS_ADC_0_1,
    _LS_ADC_0_2,
    _LS_ADC_0_3,

    _LS_ADC_1_0,
    _LS_ADC_1_1,
    _LS_ADC_1_2,
    _LS_ADC_1_3,
#endif
} EnumLsAdcChannel;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerPinsharePowerOnReset(void);
extern void ScalerPinshareSoftReset(void);

#if((_HW_IIC_SUPPORT == _ON) || (_TYPEC_IIC_SUPPORT == _ON))
extern void ScalerPinshareHwIICPin(BYTE ucHwIICPinNum);
#endif

extern void ScalerPinshareRx0TypeCPinAssert(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerPinshareRx0TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerPinshareRx1TypeCPinAssert(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerPinshareRx1TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerPinshareRx2TypeCPinAssert(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerPinshareRx2TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation);

#if(_DP_SUPPORT == _ON)
#if(_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON)
extern void ScalerPinshareDpAuxRxConfig(EnumInputPort enumInputPort, EnumPowerTarget enumPowerTarget);
#endif
#endif
