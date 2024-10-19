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
// ID Code      : ScalerHdcp14Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HW_HDCP_1_4_SEPARATE_CIPHER_SUPPORT == _ON)
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
extern void ScalerHdcp14RxCipherDownLoadKey(bit bEnable);
extern void ScalerHdcp14RxCipherDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray);

extern WORD ScalerHdcp14RxCipherProc(BYTE *pucAksv, BYTE *pucAn, bit bRepeater);
extern void ScalerHdcp14RxWriteShaInput(BYTE *pucInputArray, bit bIsFirst);
#endif
