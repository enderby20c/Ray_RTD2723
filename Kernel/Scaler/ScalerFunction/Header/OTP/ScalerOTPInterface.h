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
// ID Code      : ScalerOTPInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HW_FUSE_TYPE != _TYPE_NONE)
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
extern bit ScalerOTPMemoryCheckDoneBit(void);
extern bit ScalerOTPMemoryReadData(EnumOTPMemoryData enumOTPMemoryData, BYTE *pucReadArray);

extern void ScalerOTPMemoryGetHdcp14RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void ScalerOTPMemoryGetHdcp14TxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void ScalerOTPMemoryGetHdcp22RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
