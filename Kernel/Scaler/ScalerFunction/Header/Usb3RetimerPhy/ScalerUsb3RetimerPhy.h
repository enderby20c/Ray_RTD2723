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
// ID Code      : ScalerUsb3RetimerPhy.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB3_RETIMER_PHY_H__
#define __SCALER_USB3_RETIMER_PHY_H__

#if(_USB3_RETIMER_PHY_SUPPORT == _ON)
//****************************************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************************************


//****************************************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************************************


//****************************************************************************************************
// VARIABLE EXTERN
//****************************************************************************************************


//****************************************************************************************************
// FUNCTION EXTERN
//****************************************************************************************************
extern void ScalerUsb3RetimerPhyKModeInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyKModeEndSetting(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyUfpRxKOobs(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyUfpRxKOffset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyUfpJfmMuxSel(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyDfpRxKOobs(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyDfpRxKOffset(EnumTypeCPcbPort enumTypeCPcbPort);

#endif

#endif // End of #ifndef __SCALER_USB3_RETIMER_PHY_H__
