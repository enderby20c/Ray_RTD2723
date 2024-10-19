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
// ID Code      : ScalerVgaAdcInclude.h No.0000
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
#if(_HW_VGA_ADC_SUPPORT == _ON)
extern void ScalerVgaAdcBandgap(bit bSelect);
#endif

#if(_VGA_SUPPORT == _ON)
extern void ScalerVgaAdcOutputClkSetting(void);
extern void ScalerVgaAdcPowerSetting(void);
extern void ScalerVgaAdcBiasCurrentSetting(void);

extern void ScalerVgaAdcBandWidthSetting(DWORD ulAdcClock);
extern void ScalerVgaAdcSchmittTriggerSetting(void);
#endif // End of #if(_VGA_SUPPORT == _ON)

