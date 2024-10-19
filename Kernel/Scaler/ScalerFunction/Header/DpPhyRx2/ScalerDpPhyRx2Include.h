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
// ID Code      : ScalerDpPhyRx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX2_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of DP Lane Mapping
//--------------------------------------------------
#define GET_DP_PHY_RX2_PCB_LANE0_MAPPING()              (g_stDpPhyRx2LanesMapping.b2Lane0Mapping)
#define SET_DP_PHY_RX2_PCB_LANE0_MAPPING(x)             (g_stDpPhyRx2LanesMapping.b2Lane0Mapping = (x))

#define GET_DP_PHY_RX2_PCB_LANE1_MAPPING()              (g_stDpPhyRx2LanesMapping.b2Lane1Mapping)
#define SET_DP_PHY_RX2_PCB_LANE1_MAPPING(x)             (g_stDpPhyRx2LanesMapping.b2Lane1Mapping = (x))

#define GET_DP_PHY_RX2_PCB_LANE2_MAPPING()              (g_stDpPhyRx2LanesMapping.b2Lane2Mapping)
#define SET_DP_PHY_RX2_PCB_LANE2_MAPPING(x)             (g_stDpPhyRx2LanesMapping.b2Lane2Mapping = (x))

#define GET_DP_PHY_RX2_PCB_LANE3_MAPPING()              (g_stDpPhyRx2LanesMapping.b2Lane3Mapping)
#define SET_DP_PHY_RX2_PCB_LANE3_MAPPING(x)             (g_stDpPhyRx2LanesMapping.b2Lane3Mapping = (x))

#define GET_DP_PHY_RX2_PCB_LANE0_PN_SWAP()              (g_stDpPhyRx2LanesMapping.b1Lane0PNSwap)
#define SET_DP_PHY_RX2_PCB_LANE0_PN_SWAP(x)             (g_stDpPhyRx2LanesMapping.b1Lane0PNSwap = (x))

#define GET_DP_PHY_RX2_PCB_LANE1_PN_SWAP()              (g_stDpPhyRx2LanesMapping.b1Lane1PNSwap)
#define SET_DP_PHY_RX2_PCB_LANE1_PN_SWAP(x)             (g_stDpPhyRx2LanesMapping.b1Lane1PNSwap = (x))

#define GET_DP_PHY_RX2_PCB_LANE2_PN_SWAP()              (g_stDpPhyRx2LanesMapping.b1Lane2PNSwap)
#define SET_DP_PHY_RX2_PCB_LANE2_PN_SWAP(x)             (g_stDpPhyRx2LanesMapping.b1Lane2PNSwap = (x))

#define GET_DP_PHY_RX2_PCB_LANE3_PN_SWAP()              (g_stDpPhyRx2LanesMapping.b1Lane3PNSwap)
#define SET_DP_PHY_RX2_PCB_LANE3_PN_SWAP(x)             (g_stDpPhyRx2LanesMapping.b1Lane3PNSwap = (x))

//--------------------------------------------------
// Definitions of DP Lane Setting Ralation to Actual Lane Mapping
//--------------------------------------------------
#define _DP_PHY_RX2_D2_LANE0                            (GET_DP_PHY_RX2_PCB_LANE0_MAPPING())
#define _DP_PHY_RX2_D2_LANE1                            (GET_DP_PHY_RX2_PCB_LANE1_MAPPING())
#define _DP_PHY_RX2_D2_LANE2                            (GET_DP_PHY_RX2_PCB_LANE2_MAPPING())
#define _DP_PHY_RX2_D2_LANE3                            (GET_DP_PHY_RX2_PCB_LANE3_MAPPING())


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructDpLanesMapping g_stDpPhyRx2LanesMapping;
extern BYTE g_pucDpPhyRx2LE[4];
extern WORD g_pusDpPhyRx2ClockTarget[4];
extern WORD g_usDpPhyRx2VCOBandDiff;
extern BYTE g_ucDpPhyRx2CtsCtrl;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpPhyRx2PhyInitial(void);
extern bit ScalerDpPhyRx2DFECheck(void);
extern void ScalerDpPhyRx2RebuildPhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpPhyRx2SignalDetectInitial(EnumDpLinkRate enumDpLinkRate, BYTE ucDpLEQScanValue);
extern void ScalerDpPhyRx2SignalDetection(bit bEnable);
extern void ScalerDpPhyRx2PhyCts(void);
extern void ScalerDpPhyRx2PhyCtsAutoMode(void);
extern bit ScalerDpPhyRx2GetPhyCtsFlag(void);
extern void ScalerDpPhyRx2EyeMonitor(void);
extern bit ScalerDpPhyRx2GetEyeMonitorEnableFlag(void);
extern BYTE ScalerDpPhyRx2Tp1SignalDetectCheck_EXINT0(BYTE ucDpLaneSel);
extern void ScalerDpPhyRx2Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx2Tp2SetPhy_EXINT0(void);
extern void ScalerDpPhyRx2Tp3SetPhy_EXINT0(void);
extern void ScalerDpPhyRx2ResetCDR_EXINT0(BYTE ucTp2Result);
extern void ScalerDpPhyRx2PhyCtsTp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx2PhyCtsTp2SetPhy_EXINT0(void);
extern BYTE ScalerDpPhyRx2DFECheck_EXINT0(void);
extern void ScalerDpPhyRx2SignalDetection_EXINT0(bit bEnable);

extern void ScalerDpPhyRx2RebuildPhy_WDINT(EnumDpLinkRate enumDpLinkRate);

#endif
