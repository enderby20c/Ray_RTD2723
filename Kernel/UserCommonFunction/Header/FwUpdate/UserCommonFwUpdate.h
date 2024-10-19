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
// ID Code      : UserCommonFwUpdate.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_FW_UPDATE_H__
#define __USER_COMMON_FW_UPDATE_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
#define _FW_UPDATE_SHA256_RESULT_SIZE               32
#define _FW_UPDATE_SHA256_ARRAY_SIZE                64

// Signature File Address(256 byte)
#define _FW_UPDATE_SIGN_INFO_SECTOR                 9
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
extern bit UserCommonFwUpdateRTKRsaCalculate(BYTE *pucResult);
extern bit UserCommonFwUpdateHwHashCalculateBasedSHA256(BYTE *pucResult);
extern bit UserCommonFwUpdateCompareHashResult(BYTE *pucCurHash, BYTE *pucOrgHash);
extern bit UserCommonFwUpdateRTKRsaLoadKeyAndSignature(StructSignKeyInfoType *pstHdcp2SignKeyInfoType);
#endif

#endif

#endif // End of #ifndef __USER_COMMON_FW_UPDATE_H__
