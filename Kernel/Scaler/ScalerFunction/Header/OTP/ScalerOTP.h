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
// ID Code      : ScalerOTP.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_OTP_H__
#define __SCALER_OTP_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HW_FUSE_TYPE == _OTPFUSE_TYPE)
typedef struct
{
    EnumOTPMemoryData enumDataId;
    WORD usAddress;
    WORD usLength;
} StructOTPMapping;

//-------------------------------------------------
// OTPfuse Bank
//-------------------------------------------------
typedef enum
{
    _OTPFUSE_BANK0 = 0x00,
    _OTPFUSE_BANK1 = 0x01,
    _OTPFUSE_BANK2 = 0x02,
    _OTPFUSE_BANK3 = 0x03,
    _OTPFUSE_BANK4 = 0x04,
    _OTPFUSE_BANK5 = 0x05,
    _OTPFUSE_BANK6 = 0x06,
} EnumOTPfuseBANK;

//-------------------------------------------------
// OTPfuse Bit Mode
//-------------------------------------------------
typedef enum
{
    _HW_OTPFUSE_16BIT = 0x00,
    _HW_OTPFUSE_8BIT = 0x01,
} EnumOTPfuseBitMode;
#endif

#if(_HW_FUSE_TYPE == _EFUSE_TYPE)
//-------------------------------------------------
// Efuse Group
//-------------------------------------------------
typedef enum
{
    _EFUSE_GROUP0 = 0x00,
    _EFUSE_GROUP1 = 0x01,
} EnumEfuseGroup;

//-------------------------------------------------
// Efuse Bank
//-------------------------------------------------
typedef enum
{
    _EFUSE_BANK0 = 0x00,
    _EFUSE_BANK1 = 0x01,
    _EFUSE_BANK2 = 0x02,
    _EFUSE_BANK3 = 0x03,
    _EFUSE_BANK4 = 0x04,
    _EFUSE_BANK5 = 0x05,
    _EFUSE_BANK6 = 0x06,
} EnumEfuseBANK;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_FUSE_TYPE == _OTPFUSE_TYPE)
extern void ScalerOTPGetData(WORD usStrAddr, WORD usLength, BYTE *pucOTPfuseData);
extern void ScalerOTPBankRead(BYTE ucOTPfuseBankBitMode, WORD usOTPfuseBankStrAddr, WORD usLength, BYTE *pucOTPfuseData);
extern bit ScalerOTPFuseCheckDoneBit(void);
extern bit ScalerOTPFuseReadData(EnumOTPMemoryData enumOTPMemoryData, BYTE *pucOTPfuseGetData);

#if(_HW_FUSE_HDCP_1_4_RXKEY == _ON)
extern void ScalerOTPFuseGetHdcp14RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#if(_HW_FUSE_HDCP_1_4_TXKEY == _ON)
extern void ScalerOTPFuseGetHdcp14TxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#if(_HW_FUSE_HDCP_2_2_RXKEY == _ON)
extern void ScalerOTPFuseGetHdcp22RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif


#if(_HW_FUSE_TYPE == _EFUSE_TYPE)
extern bit ScalerOTPMemoryEfuseCheckDoneBit(void);
extern bit ScalerOTPMemoryEfuseReadData(EnumOTPMemoryData enumOTPfuseData, BYTE *pucOTPfuseGetData);

#if(_HW_FUSE_HDCP_1_4_RXKEY == _ON)
extern void ScalerOTPMemoryEfuseGetHdcp14RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#if(_HW_FUSE_HDCP_1_4_TXKEY == _ON)
extern void ScalerOTPMemoryEfuseGetHdcp14TxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#if(_HW_FUSE_HDCP_2_2_RXKEY == _ON)
extern void ScalerOTPMemoryEfuseGetHdcp2RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#endif // End of #ifndef __SCALER_OTP_H__
