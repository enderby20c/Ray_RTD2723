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
// ID Code      : UserCommonDataExchangeInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
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
extern bit UserCommonDataExchangeSendEvent(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType);
extern bit UserCommonDataExchangeSendByte(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucWriteByte);
extern bit UserCommonDataExchangeSendData(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray);
extern bit UserCommonDataExchangeCheckSendEventDone(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucPollingInterval);
extern bit UserCommonDataExchangeCheckSendByteDone(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucWriteByte, BYTE ucPollingInterval);
extern bit UserCommonDataExchangeCheckSendDataDone(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucPollingInterval);
#endif
