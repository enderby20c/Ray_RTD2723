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
// ID Code      : ScalerDpHdcp14Rx2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_HDCP_14_RX2_H__
#define __SCALER_DP_HDCP_14_RX2_H__


#if(_DP_HDCP14_RX2_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
extern volatile WORD g_usDpHdcp14Rx2KsvFifoOffset;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
extern void ScalerDpHdcp14Rx2EnableReadIrq(bit bEnable);
extern bit ScalerDpHdcp14Rx2CheckBinfo(void);
extern void ScalerDpHdcp14Rx2LoadKsvFifo(void);
extern void ScalerDpHdcp14Rx2SetKsvFifoFirst(void);
extern bit ScalerDpHdcp14Rx2DeviceCountChange(void);
#endif

#endif

#endif // End of #ifndef __SCALER_DP_HDCP_14_RX2_H__
