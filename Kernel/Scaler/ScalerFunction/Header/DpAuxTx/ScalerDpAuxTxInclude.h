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
// ID Code      : ScalerDpAuxTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DP_AUX_TX_RETRY_LIMIT                                  10

//--------------------------------------------------
// Macro of DP Tx Current AUX Receive Mode
//--------------------------------------------------
#define GET_DP_AUX_TX_RECEIVE_MODE()                            (g_enumDpAuxTxReceiveMode)
#define SET_DP_AUX_TX_RECEIVE_MODE(x)                           (g_enumDpAuxTxReceiveMode = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Aux Tx Timeout Value
//--------------------------------------------------
typedef enum
{
    _AUX_TIMEOUT_400US = 0x00,
    _AUX_TIMEOUT_800US,
    _AUX_TIMEOUT_1200US,
    _AUX_TIMEOUT_1600US,
    _AUX_TIMEOUT_2000US,
    _AUX_TIMEOUT_2400US,
    _AUX_TIMEOUT_2800US,
    _AUX_TIMEOUT_3200US,
    _AUX_TIMEOUT_3600US,
} EnumDpAuxTxTimeoutValue;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//extern BYTE data g_ucEDIDPreferTiming[18];
#if(_DP_PHY_TX_SUPPORT == _ON)
extern EnumDpAuxReceiveMode g_enumDpAuxTxReceiveMode;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_PHY_TX_SUPPORT == _ON)
extern bit ScalerDpAuxTxNativeWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDpAuxTxNativeRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern BYTE ScalerDpAuxTxNativeRead_EXINT0(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerDpAuxTxInitial(void);
extern void ScalerDpAuxTxPHYSet(BYTE ucMode);
extern void ScalerDpAuxTxPowerOffProc(void);
extern void ScalerDpAuxTxPNSwap(EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpAuxTxPNSwap_EXINT0(EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpAuxTxSetTimeout(EnumDpAuxTxTimeoutValue enumDpAuxTxTimeoutValue);
#endif

