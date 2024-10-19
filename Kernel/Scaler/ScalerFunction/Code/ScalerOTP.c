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
// ID Code      : ScalerOTP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_OTP__

#include "ScalerFunctionInclude.h"
#include "OTP/ScalerOTP.h"

#if(_HW_FUSE_TYPE != _TYPE_NONE)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : ScalerOTPMemoryCheckDoneBit
// Input Value  : None
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerOTPMemoryCheckDoneBit(void)
{
#if(_HW_FUSE_TYPE == _OTPFUSE_TYPE)
    return ScalerOTPFuseCheckDoneBit();

#elif(_HW_FUSE_TYPE == _EFUSE_TYPE)
    return ScalerOTPMemoryEfuseCheckDoneBit();
#endif
}

//--------------------------------------------------
// Description  : ScalerOTPMemoryReadData
// Input Value  : enumOTPMemoryData, pucOTPMemoryGetData
// Output Value : _SUCCESS, _FAIL
//--------------------------------------------------
bit ScalerOTPMemoryReadData(EnumOTPMemoryData enumOTPMemoryData, BYTE *pucReadArray)
{
//Example
/*
#if(_HW_FUSE_TYPE != _TYPE_NONE)
BYTE pucReadArray[_HW_OTPFUSE_IOSC_TRIMDATA_LEN] = {0};

if(ScalerOTPMemoryCheckDoneBit() == _TRUE)
{
    ScalerOTPMemoryReadData(_OTPMEMORY_IOSC_TRIMDATA, pucReadArray);
}
else
{
    //OTPFuse is empty, set IP ideal value
}
#endif
*/

#if(_HW_FUSE_TYPE == _OTPFUSE_TYPE)
    return ScalerOTPFuseReadData(enumOTPMemoryData, pucReadArray);

#elif(_HW_FUSE_TYPE == _EFUSE_TYPE)
    return ScalerOTPMemoryEfuseReadData(enumOTPMemoryData, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : GET HDCP1.4 RX Key
// Input Value  : enumOTPMemoryData, usSubAddr, usLength, pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerOTPMemoryGetHdcp14RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if((_HW_FUSE_TYPE == _OTPFUSE_TYPE) && (_HW_FUSE_HDCP_1_4_RXKEY == _ON))
    ScalerOTPFuseGetHdcp14RxKey(enumOTPMemoryData, usSubAddr, usLength, pucReadArray);

#elif((_HW_FUSE_TYPE == _EFUSE_TYPE) && (_HW_FUSE_HDCP_1_4_RXKEY == _ON))
    ScalerOTPMemoryEfuseGetHdcp14RxKey(enumOTPMemoryData, usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : GET HDCP1.4 TX Key
// Input Value  : enumOTPMemoryData, usSubAddr, usLength, pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerOTPMemoryGetHdcp14TxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if((_HW_FUSE_TYPE == _OTPFUSE_TYPE) && (_HW_FUSE_HDCP_1_4_TXKEY == _ON))
    ScalerOTPFuseGetHdcp14TxKey(enumOTPMemoryData, usSubAddr, usLength, pucReadArray);

#elif((_HW_FUSE_TYPE == _EFUSE_TYPE) && (_HW_FUSE_HDCP_1_4_TXKEY == _ON))
    ScalerOTPMemoryEfuseGetHdcp14TxKey(enumOTPMemoryData, usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : GET HDCP2 RX Key
// Input Value  : enumOTPMemoryData, usSubAddr, usLength, pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerOTPMemoryGetHdcp22RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if((_HW_FUSE_TYPE == _OTPFUSE_TYPE) && (_HW_FUSE_HDCP_2_2_RXKEY == _ON))
    ScalerOTPFuseGetHdcp22RxKey(enumOTPMemoryData, usSubAddr, usLength, pucReadArray);

#elif((_HW_FUSE_TYPE == _EFUSE_TYPE) && (_HW_FUSE_HDCP_2_2_RXKEY == _ON))
    ScalerOTPMemoryEfuseGetHdcp2RxKey(enumOTPMemoryData, usSubAddr, usLength, pucReadArray);
#endif
}

#endif
