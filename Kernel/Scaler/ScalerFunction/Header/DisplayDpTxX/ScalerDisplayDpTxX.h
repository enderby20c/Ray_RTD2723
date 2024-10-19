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
// ID Code      : ScalerDisplayDpTxX.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DISPLAY_DP_TXX_H__
#define __SCALER_DISPLAY_DP_TXX_H__

#if(_DISPLAY_DP_TXX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DISPLAY_DP_TXX_TU_SIZE                          32

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
extern BYTE g_pucDisplayDpTxXAuxPVth[_DISPLAY_DP_TX_PORT_MAX];
extern BYTE g_pucDisplayDpTxXAuxNVth[_DISPLAY_DP_TX_PORT_MAX];
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayDpTxXCtsFifoReset(void);
extern void ScalerDisplayDpTxXDisplayFormatSetting(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, EnumDisplayDpMacSel enumDisplayDpMacSel);
extern void ScalerDisplayDpTxXDisplayMSASetting(EnumDisplayDpMacSel enumDisplayDpMacSel);
extern void ScalerDisplayDpTxXTPInitialSet(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern BYTE ScalerDisplayDpTxXTrainPattern1(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern BYTE ScalerDisplayDpTxXTrainPattern2(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXTrainPatternEnd(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXSetTpsPattern(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, EnumDisplayDPTxMainLinkPattern enumDisplayDPTxMainLinkPattern);
extern void ScalerDisplayDpTxXSetScrambleSeed(bit bEnable, EnumDisplayDPTxScrambleSeedType enumDisplayDPTxScrambleSeedType);
extern bit ScalerDisplayDpTxXTP1Lane0Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern bit ScalerDisplayDpTxXTP1Lane1Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern bit ScalerDisplayDpTxXTP1Lane2Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern bit ScalerDisplayDpTxXTP1Lane3Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXTP2Lane0Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXTP2Lane1Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXTP2Lane2Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXTP2Lane3Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);

extern void ScalerDisplayDpTxXSignalReset(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXEnhanceFramingMode(bit bEnable);
extern bit ScalerDisplayDpTxXMeasureInputInfo(EnumDisplayDpMacSel enumDisplayDpMacSel);
extern void ScalerDisplayDpTxXMLPHYSet(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);

extern void ScalerDisplayDpTxXAuxInitial(void);
extern void ScalerDisplayDpTxXAuxPHYSet(BYTE ucMode);
extern bit ScalerDisplayDpTxXNativeAuxRead_EXINT0(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern bit ScalerDisplayDpTxXAuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern bit ScalerDisplayDpTxXAuxRead_EXINT0(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern bit ScalerDisplayDpTxXAuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern void ScalerDisplayDpTxXMacInitial(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);

extern void ScalerDisplayDpTxXSetSignalLevel(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
extern void ScalerDisplayDpTxXSignalInitialSetting(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern EnumDisplayDPTxTrainPattern ScalerDisplayDpTxXSetTp2PatternType(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXSetLaneAndPNSwap(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXSetLaneOutputEnable(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXSetAphyOutputEnable(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);

#if(_PANEL_DPTX_HPD_DETECT == _ON)
extern bit ScalerDisplayDpTxXHpdDetect(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
#endif

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
extern void ScalerDisplayDpTxXAuxAutoCalibration(void);
#endif

#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)


#endif // End of #ifndef __SCALER_DISPLAY_DP_TXX_H__
