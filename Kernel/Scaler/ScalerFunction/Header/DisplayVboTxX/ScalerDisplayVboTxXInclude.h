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
// ID Code      : ScalerDisplayVboTxXInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PANEL_STYLE == _PANEL_VBO)
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
#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
extern void ScalerDisplayVboTxXForceLinkTraining(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable);
#endif

extern void ScalerDisplayVboTxXSetLocknInterrupt(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable);
extern void ScalerDisplayVboTxXSetUnLocknInterrupt(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable);
extern bit ScalerDisplayVboTxXHpdnStatus(EnumDisplayVboTxPort enumDisplayVboTxPort);
extern bit ScalerDisplayVboTxXLocknStatus(EnumDisplayVboTxPort enumDisplayVboTxPort);
extern bit ScalerDisplayVboTxXGetLocknVoltageLevel(EnumDisplayVboTxPort enumDisplayVboTxPort);
extern bit ScalerDisplayVboTxXAlnPatternStatus(EnumDisplayVboTxPort enumDisplayVboTxPort);
extern void ScalerDisplayVboTxXInitialTable(EnumDisplayVboTxPort enumDisplayVboTxPort);

extern bit ScalerDisplayVboTxXLockDetect_EXINT0(EnumDisplayVboTxPort enumDisplayVboTxPort);
extern bit ScalerDisplayVboTxXLockStatus_EXINT0(EnumDisplayVboTxPort enumDisplayVboTxPort);
extern bit ScalerDisplayVboTxXUnLockDetect_EXINT0(EnumDisplayVboTxPort enumDisplayVboTxPort);
#endif

