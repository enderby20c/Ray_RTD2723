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
// ID Code      : UserCommonHdcp.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_HDCP__

#include "UserCommonInclude.h"
#include "Hdcp/UserCommonHdcp.h"

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE) ||\
    ((_HDCP_2_2_SUPPORT == _ON) && ((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE) || ((_DP_TX_SUPPORT == _ON) && (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)))))
#warning "NOTE: Please check HDCP KEY location!!"
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// HDCP KEY TABLE
//--------------------------------------------------
#if((_DIGITAL_PORT_SUPPORT == _ON) && ((_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON) ||\
    ((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE) || ((_HDCP_2_2_SUPPORT == _ON) && ((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE))))))

#include "Hdcp/HdcpRxKey.h"

#if(_DP_TX_SUPPORT == _ON)
#include "Hdcp/HdcpTxKey.h"
#endif

#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcpGetKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP_KEY_BKSV + ucSubAddr, ucLength);

#elif((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHDCPKeyBKsv(ucSubAddr, ucLength, pucReadArray);

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcpGetKeyBksvByUser(ucSubAddr, ucLength, pucReadArray);

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp14RxKey(_OTPMEMORY_HDCP14_RXKEYBKSV, (WORD)ucSubAddr, (WORD)ucLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcpGetKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP_KEY_TABLE + usSubAddr, usLength);

#elif((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHDCPKey(usSubAddr, usLength, pucReadArray);

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcpGetKeyByUser(usSubAddr, usLength, pucReadArray);

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp14RxKey(_OTPMEMORY_HDCP14_RXKEY, usSubAddr, usLength, pucReadArray);

#endif
}

//--------------------------------------------------
// Description  : Load HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcpLoadKey(void)
{
    SysPowerLoadHDCPKey();

#if(_DP_SUPPORT == _ON)
    // DPCD [0x68000 ~ 0x68004]
    ScalerDpAuxRxSetHdcp14DpcdBksv();
#endif
}

#if(_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetCertrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_Certrx + usSubAddr, usLength);
#elif((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2Certrx(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetCertrxByUser(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp22RxKey(_OTPFUSE_HDCP22_RXKEY_CERTRX, usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetRSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_DKey + usSubAddr, usLength);
#elif((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2RSADkey(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetRSADkeyByUser(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp22RxKey(_OTPFUSE_HDCP22_RXKEY_DKEY, usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetRSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_RRMODN + usSubAddr, usLength);
#elif((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2RSARRModN(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetRSARRModNByUser(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp22RxKey(_OTPFUSE_HDCP22_RXKEY_RRMODN, usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetRSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_KPriv + usSubAddr, usLength);
#elif((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2RSAKPriv(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetRSAKPrivByUser(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp22RxKey(_OTPFUSE_HDCP22_RXKEY_KPRIV, usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetRSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_NPINV + usSubAddr, usLength);
#elif((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2RSANpinv(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetRSANpinvByUser(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp22RxKey(_OTPFUSE_HDCP22_RXKEY_NPINV, usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetLCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tHDCP2_LCKey + usSubAddr, usLength);
#elif((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetHdcp2LCKey(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetLCKeyByUser(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp22RxKey(_OTPFUSE_HDCP22_RXKEY_LCKEY, usSubAddr, usLength, pucReadArray);
#endif
}

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetDpTxRRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, (tTX_HDCP2_RRMODN + (usSubAddr)), usLength);
#elif((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHdcp2RRMODN(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetDpTxRRMODNByUser(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_IROM)
    ScalerHdcp2GetTxHdcp2RRMODNFromIrom(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- DCP_LLC_N
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetDpTxDcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, (tTX_HDCP2_DCP_LLC_N + (usSubAddr)), usLength);
#elif((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHdcp2DcpLlcN(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetDpTxDcpLlcNByUser(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_IROM)
    ScalerHdcp2GetTxHdcp2DcpLlcNFromIrom(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- E_Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetDpTxEKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, (tTX_HDCP2_EKEY + (usSubAddr)), usLength);
#elif((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHdcp2EKey(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetDpTxEKeyByUser(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_IROM)
    ScalerHdcp2GetTxHdcp2EKeyFromIrom(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- NP_INV
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcp2GetDpTxNPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, (tTX_HDCP2_NPINV + (usSubAddr)), usLength);
#elif((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHdcp2NPinv(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcp2GetDpTxNPinvByUser(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_IROM)
    ScalerHdcp2GetTxHdcp2NPinvFromIrom(usSubAddr, usLength, pucReadArray);
#endif
}
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Aksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcpGetTxKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tTX_HDCP_KEY_AKSV + ucSubAddr, ucLength);

#elif((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHDCPKeyAKsv(ucSubAddr, ucLength, pucReadArray);

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcpGetTxKeyAksvByUser(ucSubAddr, ucLength, pucReadArray);

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp14TxKey(_OTPMEMORY_HDCP14_TXKEYBKSV, (WORD)ucSubAddr, (WORD)ucLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHdcpGetTxKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE)
    memcpy(pucReadArray, tTX_HDCP_KEY_TABLE + usSubAddr, usLength);

#elif((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    UserCommonNVRamGetTxHDCPKey(usSubAddr, usLength, pucReadArray);

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
    UserInterfaceHdcpGetTxKeyByUser(usSubAddr, usLength, pucReadArray);

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
    ScalerOTPMemoryGetHdcp14TxKey(_OTPFUSE_HDCP14_TXKEY, usSubAddr, usLength, pucReadArray);

#endif
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
//--------------------------------------------------
// Description  : Get HDCP Key Bksv Size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonHdcpGetKeyBksvSize(void)
{
    return sizeof(tHDCP_KEY_BKSV);
}
#endif // End of #if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))

#if(_HDCP_2_2_SUPPORT == _ON)
#if((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
//--------------------------------------------------
// Description  : Get HDCP2 Rx Npinv Size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonHdcp2GetRSANpinvSize(void)
{
    return sizeof(tHDCP2_NPINV);
}

//--------------------------------------------------
// Description  : Get HDCP2 LC Key Size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonHdcp2GetLCKeySize(void)
{
    return sizeof(tHDCP2_LCKey);
}
#endif // End of #if((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
//--------------------------------------------------
// Description  : Get HDCP2 Dp Tx Npinv Size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonHdcp2GetDpTxNPinvSize(void)
{
    return sizeof(tTX_HDCP2_NPINV);
}
#endif // End of #if((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)

#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
//--------------------------------------------------
// Description  : Get HDCP Tx Aksv Size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonHdcpGetTxAKsvSize(void)
{
    return sizeof(tTX_HDCP_KEY_AKSV);
}
#endif // End of #if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)
