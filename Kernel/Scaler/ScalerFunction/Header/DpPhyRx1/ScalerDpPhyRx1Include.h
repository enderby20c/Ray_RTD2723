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
// ID Code      : ScalerDpPhyRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX1_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of DP Lane Mapping
//--------------------------------------------------
#define GET_DP_PHY_RX1_PCB_LANE0_MAPPING()              (g_stDpPhyRx1LanesMapping.b2Lane0Mapping)
#define SET_DP_PHY_RX1_PCB_LANE0_MAPPING(x)             (g_stDpPhyRx1LanesMapping.b2Lane0Mapping = (x))

#define GET_DP_PHY_RX1_PCB_LANE1_MAPPING()              (g_stDpPhyRx1LanesMapping.b2Lane1Mapping)
#define SET_DP_PHY_RX1_PCB_LANE1_MAPPING(x)             (g_stDpPhyRx1LanesMapping.b2Lane1Mapping = (x))

#define GET_DP_PHY_RX1_PCB_LANE2_MAPPING()              (g_stDpPhyRx1LanesMapping.b2Lane2Mapping)
#define SET_DP_PHY_RX1_PCB_LANE2_MAPPING(x)             (g_stDpPhyRx1LanesMapping.b2Lane2Mapping = (x))

#define GET_DP_PHY_RX1_PCB_LANE3_MAPPING()              (g_stDpPhyRx1LanesMapping.b2Lane3Mapping)
#define SET_DP_PHY_RX1_PCB_LANE3_MAPPING(x)             (g_stDpPhyRx1LanesMapping.b2Lane3Mapping = (x))

#define GET_DP_PHY_RX1_PCB_LANE0_PN_SWAP()              (g_stDpPhyRx1LanesMapping.b1Lane0PNSwap)
#define SET_DP_PHY_RX1_PCB_LANE0_PN_SWAP(x)             (g_stDpPhyRx1LanesMapping.b1Lane0PNSwap = (x))

#define GET_DP_PHY_RX1_PCB_LANE1_PN_SWAP()              (g_stDpPhyRx1LanesMapping.b1Lane1PNSwap)
#define SET_DP_PHY_RX1_PCB_LANE1_PN_SWAP(x)             (g_stDpPhyRx1LanesMapping.b1Lane1PNSwap = (x))

#define GET_DP_PHY_RX1_PCB_LANE2_PN_SWAP()              (g_stDpPhyRx1LanesMapping.b1Lane2PNSwap)
#define SET_DP_PHY_RX1_PCB_LANE2_PN_SWAP(x)             (g_stDpPhyRx1LanesMapping.b1Lane2PNSwap = (x))

#define GET_DP_PHY_RX1_PCB_LANE3_PN_SWAP()              (g_stDpPhyRx1LanesMapping.b1Lane3PNSwap)
#define SET_DP_PHY_RX1_PCB_LANE3_PN_SWAP(x)             (g_stDpPhyRx1LanesMapping.b1Lane3PNSwap = (x))

//--------------------------------------------------
// Definitions of DP Lane Setting Ralation to Actual Lane Mapping
//--------------------------------------------------
#define _DP_PHY_RX1_D1_LANE0                            (GET_DP_PHY_RX1_PCB_LANE0_MAPPING())
#define _DP_PHY_RX1_D1_LANE1                            (GET_DP_PHY_RX1_PCB_LANE1_MAPPING())
#define _DP_PHY_RX1_D1_LANE2                            (GET_DP_PHY_RX1_PCB_LANE2_MAPPING())
#define _DP_PHY_RX1_D1_LANE3                            (GET_DP_PHY_RX1_PCB_LANE3_MAPPING())


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructDpLanesMapping g_stDpPhyRx1LanesMapping;
extern BYTE g_pucDpPhyRx1LE[4];
extern WORD g_pusDpPhyRx1ClockTarget[4];
extern WORD g_usDpPhyRx1VCOBandDiff;
extern BYTE g_ucDpPhyRx1CtsCtrl;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpPhyRx1PhyInitial(void);
extern void ScalerDpPhyRx1SetAltModeLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern bit ScalerDpPhyRx1DFECheck(void);
extern void ScalerDpPhyRx1RebuildPhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpPhyRx1SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
extern void ScalerDpPhyRx1SignalDetection(bit bEnable);
extern void ScalerDpPhyRx1PhyCts(void);
extern void ScalerDpPhyRx1PhyCtsAutoMode(void);
extern void ScalerDpPhyRx1SetPhyCtsFlag(bit bFlag);
extern bit ScalerDpPhyRx1GetPhyCtsFlag(void);
extern void ScalerDpPhyRx1EyeMonitor(void);
extern bit ScalerDpPhyRx1GetEyeMonitorEnableFlag(void);
extern BYTE ScalerDpPhyRx1Tp1SignalDetectCheck_EXINT0(BYTE ucDpLaneSel);
extern void ScalerDpPhyRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx1Tp2SetPhy_EXINT0(void);
extern void ScalerDpPhyRx1Tp3SetPhy_EXINT0(void);
extern void ScalerDpPhyRx1ResetCDR_EXINT0(BYTE ucTp2Result);
extern void ScalerDpPhyRx1PhyCtsTp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx1PhyCtsTp2SetPhy_EXINT0(void);
extern BYTE ScalerDpPhyRx1DFECheck_EXINT0(void);
extern void ScalerDpPhyRx1SignalDetection_EXINT0(bit bEnable);
extern void ScalerDpPhyRx1SetAltModeLaneMapping_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpPhyRx1RebuildPhy_WDINT(EnumDpLinkRate enumDpLinkRate);

#endif
