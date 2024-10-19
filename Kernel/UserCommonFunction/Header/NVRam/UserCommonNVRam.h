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
// ID Code      : UserCommonNVRam.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_NVRAM_H__
#define __USER_COMMON_NVRAM_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _EEPROM_READ_SIZE                           24
#define _EEPROM_TIMEOUT_LIMIT                       50

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern DWORD __resource_info_region_start;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumSystemDataItemDataType UserCommonNVRamGetRegionPortItem(EnumDisplayRegion enumDisplayRegion);

#if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

extern void UserCommonEepromGetHDCPKeyBKsv(DWORD ulSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHDCPKey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreHDCP1P4(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonEepromGetTxHDCPKeyAKsv(DWORD ulSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHDCPKey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreTxHDCP1P4(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)

extern void UserCommonFlashGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreHDCP1P4(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif
#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonFlashGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_HDCP_2_2_SUPPORT == _ON)

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

extern void UserCommonEepromGetHdcp2Certrx(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSADkey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSARRModN(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSAKPriv(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSANpinv(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2LCKey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreHDCP2(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
extern void UserCommonEepromGetTxHdcp2RRMODN(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHdcp2DcpLlcN(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHdcp2EKey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHdcp2NPinv(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreTxHDCP2(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif
#endif

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)

extern void UserCommonFlashGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
extern void UserCommonFlashGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreTxHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif
#endif
#endif

#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)



#endif // End of #ifndef __USER_COMMON_NVRAM_H__
