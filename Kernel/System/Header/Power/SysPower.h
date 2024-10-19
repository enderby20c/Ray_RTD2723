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
// ID Code      : SysPower.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_POWER_H__
#define __SYS_POWER_H__


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
extern void SysPowerSwitch(EnumPowerAction enumSwitch);



extern void SysPowerSystemClockSelect(BYTE ucClockSel);

extern void SysPowerRecoverIsolationAreaData(void);
extern bit SysPowerCheckNormal(void);


#endif // End of #ifndef __SYS_POWER_H__
