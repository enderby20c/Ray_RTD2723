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
// ID Code      : UserCommonHdcpInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _RX_HDCP_1_4_TABLE_FLASH_PAGE                  (_RX_HDCP_1_4_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _RX_HDCP_2_2_TABLE_FLASH_PAGE                  (_RX_HDCP_2_2_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _TX_HDCP_1_4_TABLE_FLASH_PAGE                  (_TX_HDCP_1_4_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _TX_HDCP_2_2_TABLE_FLASH_PAGE                  (_TX_HDCP_2_2_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE code tHDCP_KEY_BKSV[];
extern BYTE code tHDCP_KEY_TABLE[];

#if(_HDCP_2_2_SUPPORT == _ON)
extern BYTE code tHDCP2_Certrx[];
extern BYTE code tHDCP2_KPriv[];
extern BYTE code tHDCP2_NPINV[];
extern BYTE code tHDCP2_KpubKm[];
extern BYTE code tHDCP2_DKey[];
extern BYTE code tHDCP2_RRMODN[];
extern BYTE code tHDCP2_LCKey[];
#endif

extern BYTE code tTX_HDCP_KEY_AKSV[];
extern BYTE code tTX_HDCP_KEY_TABLE[];

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern BYTE code tTX_HDCP2_DCP_LLC_N[];
extern BYTE code tTX_HDCP2_EKEY[];
extern BYTE code tTX_HDCP2_RRMODN[];
extern BYTE code tTX_HDCP2_NPINV[];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
extern BYTE UserCommonHdcpGetKeyBksvSize(void);
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
#if((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
extern BYTE UserCommonHdcp2GetRSANpinvSize(void);
extern BYTE UserCommonHdcp2GetLCKeySize(void);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
extern BYTE UserCommonHdcp2GetDpTxNPinvSize(void);
#endif
#endif

#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
extern BYTE UserCommonHdcpGetTxAKsvSize(void);
#endif
#endif
#endif
#endif
