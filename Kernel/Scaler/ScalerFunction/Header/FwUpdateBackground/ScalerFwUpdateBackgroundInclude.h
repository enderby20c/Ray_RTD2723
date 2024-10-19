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
// ID Code      : ScalerFwUpdateBackgroundInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
#if(_DP_TX_SUPPORT == _ON)
    BYTE b1DpTxBusyStatus : 1;
#endif
#if(_DP_SUPPORT == _ON)
    BYTE b1DpRxBusyStatus : 1;
#endif
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    BYTE b1TypeCBusyStatus : 1;
#endif
#if(_DIGITAL_PORT_SUPPORT == _ON)
    BYTE b1MCCSBusyStatus : 1;
#endif
    BYTE b1HdcpBusyStatus : 1;
} StructSysBusyStatusInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructSysBusyStatusInfo g_stFwUpdateBackgroundSysStatusInfo;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#endif
