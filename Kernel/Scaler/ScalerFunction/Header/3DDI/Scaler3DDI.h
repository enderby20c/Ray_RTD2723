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
// ID Code      : Scaler3DDI.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_3DDI_H__
#define __SCALER_3DDI_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#define _3DDI_1ST_BANK_OFFSET                                ((WORD)0x03 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // PATH 1: bank3, 0x0600
#define _3DDI_2ND_BANK_OFFSET                                ((WORD)0x05 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // PATH 2: Bank5, 0x0A00

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_COLOR_IP_3DDI == _ON)
#if(_3DDI_MEMORY_BW_CTRL_SUPPORT == _ON)
extern void Scaler3DDIBwCtrlGetWriteClientInfo(StructBwCtrlClientInfo *pstInfo);
extern void Scaler3DDIBwCtrlGetReadClientInfo(StructBwCtrlClientInfo *pstInfo);
extern void Scaler3DDISetBwCtrl(EnumInputDataPath enum3DDIInputPath);
#endif
#endif


#endif // End of #ifndef __SCALER_3DDI_H__
