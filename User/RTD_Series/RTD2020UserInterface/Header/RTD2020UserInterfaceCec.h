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
// ID Code      : RTD2020UserInterfaceCec.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2020_OSD)

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _CEC_RX_DATA_HB                                 0
#define _CEC_RX_DATA_DB_0                               1
#define _CEC_RX_DATA_DB_1                               2
#define _CEC_RX_DATA_DB_2                               3
#define _CEC_RX_DATA_COUNT                              4

#define _CEC_TX_DATA_HB                                 0
#define _CEC_TX_DATA_DB_0                               1
#define _CEC_TX_DATA_DB_1                               2
#define _CEC_TX_DATA_DB_2                               3
#define _CEC_TX_DATA_DB_3                               4
#define _CEC_TX_DATA_DB_4                               5
#define _CEC_TX_DATA_LENGTH                             6
#define _CEC_TX_DATA_RETRY                              7
#define _CEC_TX_DATA_COUNT                              8

#define GET_CEC_TX_SEND()                               (g_stCecUserInfo.b1CecTxSend)
#define SET_CEC_TX_SEND()                               (g_stCecUserInfo.b1CecTxSend = _TRUE)
#define CLR_CEC_TX_SEND()                               (g_stCecUserInfo.b1CecTxSend = _FALSE)

#define GET_CEC_TX_DATA(x)                              (g_stCecUserInfo.pucCecTxData[x])
#define SET_CEC_TX_DATA(x, y)                           (g_stCecUserInfo.pucCecTxData[x] = (y))
#define CLR_CEC_TX_DATA()                               (memset(g_stCecUserInfo.pucCecTxData, 0, sizeof(g_stCecUserInfo.pucCecTxData)))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1CecTxSend : 1;
    BYTE pucCecTxData[_CEC_TX_DATA_COUNT];
}StructCecUserInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)