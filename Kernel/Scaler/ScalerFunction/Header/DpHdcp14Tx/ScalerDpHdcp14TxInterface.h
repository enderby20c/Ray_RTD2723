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
// ID Code      : ScalerDpHdcp14TxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_TX_HDCP_RELOAD_KEY_EN()                      (bit)(g_ucDpHdcp14TxLoadKey & _BIT7)
#define SET_DP_TX_HDCP_RELOAD_KEY_EN()                      (g_ucDpHdcp14TxLoadKey |= _BIT7)
#define CLR_DP_TX_HDCP_RELOAD_KEY_EN()                      (g_ucDpHdcp14TxLoadKey &= ~_BIT7)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDpHdcp14TxLoadKey;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp14TxPowerOnInitial(void);
#endif // End of #if(_DP_TX_SUPPORT == _ON)

