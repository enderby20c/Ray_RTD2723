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
// ID Code      : ScalerDisplayVboTxXInterface.h No.0000
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
#if(_PANEL_STYLE == _PANEL_VBO)
extern void ScalerDisplayVboTxXAPhyControl(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable);
extern void ScalerDisplayVboTxXDPhyControl(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable);
extern void ScalerDisplayVboTxXHtpdnControl(EnumDisplayVboTxPort enumDisplayVboTxPort, EnumDisplayVboTxControlMode enumDisplayVboTxControlMode, bit bValue);
extern void ScalerDisplayVboTxXForceVideoOutput(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable);

extern void ScalerDisplayVboTxXIntHandler_EXINT0(void);
#endif

