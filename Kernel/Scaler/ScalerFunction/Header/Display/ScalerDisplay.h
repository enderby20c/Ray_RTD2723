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
// ID Code      : ScalerDisplay.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DISPLAY_H__
#define __SCALER_DISPLAY_H__

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
#if(_PANEL_STYLE == _PANEL_LVDS)
extern void ScalerDisplayLvdsTxDataSel(void);
extern void ScalerDisplayLvdsTxPortSwap(void);
extern void ScalerDisplayLvdsClkInfoSelect(void);
extern void ScalerDisplayLvdsDrivingControl(BYTE ucDriv);
extern void ScalerDisplayLvdsPhaseConrol(void);
extern void ScalerDisplayLvdsSlewRateConrol(void);
extern void ScalerDisplayVcmControl(BYTE ucType);
extern void ScalerDisplayLvdsSetPreEmphasis(BYTE ucPreEmphais);
extern void ScalerDisplayLvdsStronglyPullDown(bit bOn);
extern void ScalerDisplayLvdsWeaklyPullDown(bit bOn);

#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
extern void ScalerDisplayLvdsStronglyWeaklyPullDownUserControl(void);
extern void ScalerDisplayLvdsDoubleCurrentUserControl(void);
extern void ScalerDisplayLvdsDrivingCurrentUserControl(void);
extern void ScalerDisplayLvdsTerminationUserControl(void);
#endif
#endif


#endif // End of #ifndef __SCALER_DISPLAY_H__
