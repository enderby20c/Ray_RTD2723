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
// ID Code      : ScalerDisplayDpTxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
#if(_DISPLAY_DP_TX_SUPPORT == _ON)
extern bit ScalerDisplayDpTxLinkSequence(void);
extern void ScalerDisplayDpTxPollingHotPlug(WORD usNum);

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
extern void ScalerDisplayDpTxLinkSignalForceOutput(void);
#endif

extern void ScalerDisplayDpTxInitial(void);
extern void ScalerDisplayDpTxPhyInitial(void);
extern void ScalerDisplayDpTxPowerSequenceProc(bit bLevel);
extern void ScalerDisplayDpTxSSCSet(bit bSscEn);
extern void ScalerDisplayDpTxStreamHanlder(bit bOutput);
extern void ScalerDisplayDpTxAnalogPhyConrol(bit bOn);

#if(_PANEL_DPTX_HPD_DETECT == _ON)
extern bit ScalerDisplayDpTxStableDetect(void);
#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
extern void ScalerDisplayDpTxIrqIntHandler_EXINT0(void);
#endif
#endif

extern bit ScalerDisplayDpTxAuxI2CoverWrite(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT);
extern bit ScalerDisplayDpTxAuxI2CoverRead(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT);

#endif

