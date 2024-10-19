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
// ID Code      : ScalerPinshare.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_PINSHARE_H__
#define __SCALER_PINSHARE_H__

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
extern void ScalerPinshareAdjustFlashDrive(void);
extern void ScalerPinshareAdjustFlashSlewRate(void);

#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
    (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
    (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
extern bit ScalerPinshareGetTypeCDPSourcePower(EnumInputPort enumInputPort);
#endif

#endif // End of #ifndef __SCALER_PINSHARE_H__
