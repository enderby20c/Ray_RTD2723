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
// ID Code      : UserCommonNVRamInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructSystemDataType g_stNVRamSystemData;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// EDID
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)))
extern void UserCommonEepromRestoreEDID(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
extern void UserCommonFlashRestoreEDID(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)

extern void UserCommonNVRamGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonNVRamRestoreHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonNVRamGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonNVRamRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_HDCP_2_2_SUPPORT == _ON)
extern void UserCommonNVRamGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonNVRamRestoreHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonNVRamGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonNVRamRestoreTxHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_FLASH_WR_PROTECT == _ON)
extern void UserCommonFlashWRProtect(void);
#endif

