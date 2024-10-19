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
// ID Code      : ScalerDpPhyRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Structure of DP Lanes Mapping
//--------------------------------------------------
typedef struct
{
    BYTE b2Lane0Mapping : 2;
    BYTE b2Lane1Mapping : 2;
    BYTE b2Lane2Mapping : 2;
    BYTE b2Lane3Mapping : 2;
    BYTE b1Lane0PNSwap : 1;
    BYTE b1Lane1PNSwap : 1;
    BYTE b1Lane2PNSwap : 1;
    BYTE b1Lane3PNSwap : 1;
} StructDpLanesMapping;

//--------------------------------------------------
// Structure of DP ACDR Setting
//--------------------------------------------------
typedef struct
{
    BYTE ucDpPhyRxIcpKp_RBR;
    BYTE ucDpPhyRxIcpKp_HBR;
    BYTE ucDpPhyRxIcpKp_HBR2;
    BYTE ucDpPhyRxIcpKp_HBR3;
    BYTE ucDpPhyRxIcpKp_UHBR10;
    BYTE ucDpPhyRxIcpKp_UHBR13p5;
    BYTE ucDpPhyRxIcpKp_UHBR20;
} StructDpPhyRxIcpKp;

typedef struct
{
    BYTE ucDpPhyRxIcp_RBR;
    BYTE ucDpPhyRxIcp_HBR;
    BYTE ucDpPhyRxIcp_HBR2;
    BYTE ucDpPhyRxIcp_HBR3;
    BYTE ucDpPhyRxIcp_UHBR10;
    BYTE ucDpPhyRxIcp_UHBR13p5;
    BYTE ucDpPhyRxIcp_UHBR20;
} StructDpPhyRxIcp;

typedef struct
{
    BYTE ucDpPhyRxKvco_RBR;
    BYTE ucDpPhyRxKvco_HBR;
    BYTE ucDpPhyRxKvco_HBR2;
    BYTE ucDpPhyRxKvco_HBR3;
    BYTE ucDpPhyRxKvco_UHBR10;
    BYTE ucDpPhyRxKvco_UHBR13p5;
    BYTE ucDpPhyRxKvco_UHBR20;
} StructDpPhyRxKvco;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundRBR;
extern WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR;
extern WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR2;
extern WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR3;
extern WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR3_9G;

extern WORD g_usDpPhyRxVCOCountCriteriaUpperBoundRBR;
extern WORD g_usDpPhyRxVCOCountCriteriaUpperBoundHBR;
extern WORD g_usDpPhyRxVCOCountCriteriaUpperBoundHBR2;
extern WORD g_usDpPhyRxVCOCountCriteriaUpperBoundHBR3;
extern WORD g_usDpPhyRxVCOCountCriteriaUpperBoundHBR3_9G;

extern WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundRBR;
extern WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR;
extern WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR2;
extern WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR3;
extern WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR3_9G;

extern WORD g_usDpPhyRxVCOCountCriteriaLowerBoundRBR;
extern WORD g_usDpPhyRxVCOCountCriteriaLowerBoundHBR;
extern WORD g_usDpPhyRxVCOCountCriteriaLowerBoundHBR2;
extern WORD g_usDpPhyRxVCOCountCriteriaLowerBoundHBR3;
extern WORD g_usDpPhyRxVCOCountCriteriaLowerBoundHBR3_9G;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR10;
extern WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR13_5;
extern WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR20;

extern WORD g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR10;
extern WORD g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR13_5;
extern WORD g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR20;

extern WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR10;
extern WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR13_5;
extern WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR20;

extern WORD g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR10;
extern WORD g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR13_5;
extern WORD g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR20;

extern BYTE code tDpPhyRxDP2PresetSelTable[16];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumInputPort ScalerDpPhyRxRxDxMapping(EnumRx enumRx);
extern EnumRx ScalerDpPhyRxDxRxMapping(EnumInputPort enumInputPort);
extern WORD ScalerDpPhyRxTargetClock(EnumInputPort enumInputPort, BYTE ucNumber);
extern BYTE ScalerDpPhyRxGetPhyCtsFlag(EnumInputPort enumInputPort);

extern BYTE ScalerDpPhyRxGetLaneMapping(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern BYTE ScalerDpPhyRxGetLanePNSwap(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern BYTE ScalerDpPhyRxGetPCBLaneMapping(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern BYTE ScalerDpPhyRxGetPCBLanePNSwap(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern void ScalerDpPhyRxSetLaneMux(EnumInputPort enumInputPort, EnumDpLane enumDpLane, BYTE ucLaneMapping);
extern void ScalerDpPhyRxSetLanePNSwap(EnumInputPort enumInputPort, EnumDpLane enumDpLane, BYTE ucPNSwap);
extern BYTE ScalerDpPhyRxCtsCtrl(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxPhyCts(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxPhyCtsAutoMode(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxPhyInitial(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxSetAltModeLaneMapping(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpPhyRxRebuildPhy(EnumInputPort enumInputPort, EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpPhyRxSignalDetectInitial(EnumInputPort enumInputPort, BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
extern void ScalerDpPhyRxSignalDetection(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerDpPhyRxDFECheck(EnumInputPort enumInputPort);

extern EnumInputPort ScalerDpPhyRxRxDxMapping_EXINT0(EnumRx enumRx);
extern EnumRx ScalerDpPhyRxDxRxMapping_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern BYTE ScalerDpPhyRxGetPhyCtsTestLane_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxSetPhyCtsTestLinkRate_EXINT0(EnumInputPort enumInputPort, EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpPhyRxSetPhyCtsTestLane_EXINT0(EnumInputPort enumInputPort, BYTE ucTestLane);

extern BYTE ScalerDpPhyRxGetLaneMapping_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern BYTE ScalerDpPhyRxGetLanePNSwap_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern BYTE ScalerDpPhyRxGetPCBLaneMapping_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern BYTE ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern void ScalerDpPhyRxSetLaneMux_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane, BYTE ucLaneMapping);
extern void ScalerDpPhyRxSetLanePNSwap_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane, BYTE ucPNSwap);
extern void ScalerDpPhyRxTp1SetPhy_EXINT0(EnumInputPort enumInputPort, EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRxTp2SetPhy_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxTp3SetPhy_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxResetCDR_EXINT0(EnumInputPort enumInputPort, BYTE ucTp2Result);
extern void ScalerDpPhyRxPhyCtsTp1SetPhy_EXINT0(EnumInputPort enumInputPort, EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRxPhyCtsTp2SetPhy_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpPhyRxDFECheck_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpPhyRxGetTp2LE_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLaneSel);
extern BYTE ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLaneSel);
extern void ScalerDpPhyRxSignalDetection_EXINT0(EnumInputPort enumInputPort, bit bEnable);

extern EnumInputPort ScalerDpPhyRxRxDxMapping_WDINT(EnumRx enumRx);
extern EnumRx ScalerDpPhyRxDxRxMapping_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxRebuildPhy_WDINT(EnumInputPort enumInputPort, EnumDpLinkRate enumDpLinkRate);
extern bit ScalerDpPhyRxEnableEyeMonitor(EnumInputPort enumInputPort);
extern void ScalerDpPhyRxEyeMonitor(EnumInputPort enumInputPort);
#endif
