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
// ID Code      : ScalerTmdsMacRx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TMDS_MAC_RX_H__
#define __SCALER_TMDS_MAC_RX_H__


#if(_HDMI_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//--------------------------------------------------
// Struct of TMDS HPD Sequence
//--------------------------------------------------
typedef struct
{
    BYTE ucRXx;
    WORD usHpdTime;
} StructTmdsHpdSequence;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTmdsMacRxPNHighIntHandler_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxPNLowIntHandler_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxPSHighIntHandler_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxPSLowIntHandler_EXINT0(EnumInputPort enumInputPort);
extern EnumRx ScalerTmdsMacRxDxRxMapping_EXINT1(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxHotPlugLowProc(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxHotPlugHighProc(EnumInputPort enumInputPort, WORD usHpdTime);
extern void ScalerTmdsMacRxAfterHotPlugEventProc(EnumInputPort enumInputPort, bit bRestoreZ0);
extern void ScalerTmdsMacRxDdcDetectDebounce_EXINT1(void);

extern EnumRx ScalerTmdsMacRxMacPhyMapping(EnumRx enumMacRxIndex);
extern EnumRx ScalerTmdsMacRxPhyMacMapping(EnumRx enumPhyRxIndex);

extern EnumRx ScalerTmdsMacRxMacPhyMapping_EXINT0(EnumRx enumMacRxIndex);
extern EnumRx ScalerTmdsMacRxPhyMacMapping_EXINT0(EnumRx enumPhyRxIndex);

extern EnumRx ScalerTmdsMacRxMacPhyMapping_EXINT1(EnumRx enumMacRxIndex);
extern EnumRx ScalerTmdsMacRxPhyMacMapping_EXINT1(EnumRx enumPhyRxIndex);


#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _OFF)
extern void ScalerTmdsMacRxDelayModeHpdToggleProc(void);
#else
extern void ScalerTmdsMacRxTimerModeHpdToggleProc(void);
#endif

extern bit ScalerTmdsMacRxCheckBRSwap(EnumInputPort enumInputPort);
#endif

#endif // End of #ifndef __SCALER_TMDS_MAC_RX_H__
