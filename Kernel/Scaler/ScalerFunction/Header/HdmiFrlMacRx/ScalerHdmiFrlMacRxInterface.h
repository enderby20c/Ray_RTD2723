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
// ID Code      : ScalerHdmiFrlMacRxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_FRL_SUPPORT == _ON)

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
extern void ScalerHdmiFrlMacRxResetProc(EnumInputPort enumInputPort);
extern bit ScalerHdmiFrlMacRxEnterPowerSavingCheck(EnumInputPort enumInputPort);
extern bit ScalerHdmiFrlMacRxEnterFakePowerSavingCheck(void);
extern void ScalerHdmiFrlMacRxClrFltReady(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRxLinkTrainingDisable(EnumInputPort enumInputPort);
extern EnumHdmiFrlRate ScalerHdmiFrlMacRxGetFrlRate(EnumInputPort enumInputPort);
#endif // End of #if(_HDMI_FRL_SUPPORT == _ON)
