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
// ID Code      : ScalerCec.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_CEC_H__
#define __SCALER_CEC_H__


#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _CEC_BOARDCAST_LA                      0xF
#define _CEC_RX_BACKUP_FIFO_SIZE               68
#define _CEC_RX_BACKUP_FIFO_OVERFLOW_BUFFER    3

// CEC receiver duration setting
#define _CEC_RX_START_LOW_TIME                 0x74
#define _CEC_RX_START_PERIOD_TIME              0xBD  // 0xBC
#define _CEC_RX_DATA_SAMPLE_TIME               0x2A
#define _CEC_RX_DATA_PERIOD_TIME               0x51  // 0x52
#define _CEC_RX_START_HIGH_TIME                0xA0

// CEC transmitter duration setting
#define _CEC_TX_START_LOW_TIME                 0x94
#define _CEC_TX_START_HIGH_TIME                0x20
#define _CEC_TX_DATA_LOW_TIME                  0x18
#define _CEC_TX_DATA_WIDTH_TIME                0x24
#define _CEC_TX_DATA_HIGH_TIME                 0x24

#define _CEC_RX_LINE_ERR_NOTIFY_TIME           0x90

#define _CEC_LANG_ENGLISH                      "eng"
#define _CEC_LANG_FRENCH                       "fre"
#define _CEC_LANG_GERMAN                       "ger"
#define _CEC_LANG_SPANISH                      "spa"
#define _CEC_LANG_CHINESE                      "chi"
#define _CEC_LANG_JAPANESE                     "jpn"

#define GET_CEC_RX_READ_FROM_BACKUP_FIFO()     (g_stCecGeneralCtrl.b1ReadFromBackupFifo)
#define SET_CEC_RX_READ_FROM_BACKUP_FIFO()     (g_stCecGeneralCtrl.b1ReadFromBackupFifo = _TRUE)
#define CLR_CEC_RX_READ_FROM_BACKUP_FIFO()     (g_stCecGeneralCtrl.b1ReadFromBackupFifo = _FALSE)

#define GET_CEC_TX_DEST_LA_TO_SEND()           ((g_stCecTxTransmitInfo.ucTransmitHb) & 0x0F)
#define GET_CEC_TX_INIT_LA_TO_SEND()           (((g_stCecTxTransmitInfo.ucTransmitHb) & 0xF0) >> 4)

#define GET_CEC_TX_DEST_LA_TO_SEND()           ((g_stCecTxTransmitInfo.ucTransmitHb) & 0x0F)
#define GET_CEC_TX_INIT_LA_TO_SEND()           (((g_stCecTxTransmitInfo.ucTransmitHb) & 0xF0) >> 4)

#define GET_EDID_CEC_PHY_ADDRESS()             (g_stCecGeneralCtrl.usCecPhyAddr)
#define SET_EDID_CEC_PHY_ADDRESS(x)            (g_stCecGeneralCtrl.usCecPhyAddr = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile BYTE g_ucCecRxBackupFifoWaterLevel;
extern BYTE g_pucCecRxBackupFifo[_CEC_RX_BACKUP_FIFO_SIZE];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerCecRxReadOutFromBackupFifo(void);
extern void ScalerCecRxWriteIntoBackupFifo(void);
#if(_CEC_RX_INT_SUPPORT == _OFF)
extern void ScalerCecRxMsgReceiving(void);
extern bit ScalerCecCheckRxSituation(void);
#endif

#if((_CEC_RX_INT_SUPPORT == _ON) && ((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_0) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)))
extern void ScalerCecPollingMsgReceiving(void);
#endif

#if(_CEC_RX_INT_SUPPORT == _ON)
extern BYTE ScalerCecCheckRxSituation_EXINT0(void);
extern void ScalerCecRxMsgReceiving_EXINT0(void);
extern void ScalerCecRxWriteIntoBackupFifo_EXINT0(void);
extern void ScalerCecRxWriteIntoRxInfoStruct_EXINT0(void);
#endif
extern void ScalerCecRxWriteIntoRxInfoStruct(void);
extern void ScalerCecVariableReset(void);
extern void ScalerCecSendNewFx(void);
extern bit ScalerCecIsSending(void);
#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_CEC_H__
