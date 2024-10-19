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
// ID Code      : ScalerTypeCAdcInterface.h No.0000
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
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerTypeCAdcClkSel(BYTE ucClockSel);
extern void ScalerTypeCAdcInitial(void);
#if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)
extern void ScalerTypeCAdcCheckLocPowExist(void);
#else
extern void ScalerTypeCAdcSetLocPowExist(EnumTypeCLocalPowerExist enumLocPowExist);
#endif
extern EnumTypeCLocalPowerExist ScalerTypeCAdcGetLocPowExist(void);
#endif
