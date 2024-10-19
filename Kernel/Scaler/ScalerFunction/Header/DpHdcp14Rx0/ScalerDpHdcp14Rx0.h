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
// ID Code      : ScalerDpHdcp14Rx0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_HDCP_14_RX0_H__
#define __SCALER_DP_HDCP_14_RX0_H__


#if(_DP_HDCP14_RX0_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
extern volatile WORD g_usDpHdcp14Rx0KsvFifoOffset;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
extern void ScalerDpHdcp14Rx0EnableReadIrq(bit bEnable);
extern bit ScalerDpHdcp14Rx0CheckBinfo(void);
extern void ScalerDpHdcp14Rx0LoadKsvFifo(void);
extern void ScalerDpHdcp14Rx0SetKsvFifoFirst(void);
extern bit ScalerDpHdcp14Rx0DeviceCountChange(void);
#endif

#endif

#endif // End of #ifndef __SCALER_DP_HDCP_14_RX0_H__
