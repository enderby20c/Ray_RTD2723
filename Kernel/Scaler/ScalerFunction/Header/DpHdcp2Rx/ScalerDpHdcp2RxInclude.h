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
// ID Code      : ScalerDpHdcp2RxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_HDCP2_RX_SUPPORT == _ON)
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
extern void ScalerDpHdcp2RxCancelTimerEvent(EnumInputPort enumInputPort);
extern void ScalerDpHdcp2RxCancelTimerEvent_EXINT0(EnumInputPort enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpHdcp2RxGetStxType(BYTE ucStreamId);
extern bit ScalerDpHdcp2RxReAuthStatusCheck(EnumInputPort enumInputPort);
#endif

extern void ScalerDpHdcp2RxAkeInitProc_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpHdcp2RxSkeProc_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpHdcp2RxHPrimeProc_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpHdcp2RxDkeyCalculate_WDINT(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpHdcp2RxMPrimeProc_WDINT(EnumInputPort enumInputPort);
#endif

#endif
