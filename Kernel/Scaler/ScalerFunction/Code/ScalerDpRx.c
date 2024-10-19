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
// ID Code      : ScalerDpRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP__

#include "ScalerFunctionInclude.h"
#include "DpRx/ScalerDpRx.h"

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tValidDpPort[_DP_PORT_VALID] =
{
#if(_D0_DP_SUPPORT == _ON)
    _DP_D0_PORT,
#endif
#if(_D1_DP_SUPPORT == _ON)
    _DP_D1_PORT,
#endif
#if(_D2_DP_SUPPORT == _ON)
    _DP_D2_PORT,
#endif
#if(_D7_DP_SUPPORT == _ON)
    _DP_D7_PORT,
#endif
#if(_D8_DP_SUPPORT == _ON)
    _DP_D8_PORT,
#endif
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDpCableStatus g_stDpRxCableStatus;
StructDpRxHpdStatus g_stDpRxHpdStatus;

EnumInputPort g_enumDpRxMainPort = _NO_INPUT_PORT;

WORD g_usDpRxVcoCount1000RBR;
WORD g_usDpRxVcoCount1000HBR;
WORD g_usDpRxVcoCount1000HBR2;
WORD g_usDpRxVcoCount1000HBR3;
WORD g_usDpRxVcoCount1000HBR3_9G;

WORD g_usDpRxVcoCount2000RBR;
WORD g_usDpRxVcoCount2000HBR;
WORD g_usDpRxVcoCount2000HBR2;
WORD g_usDpRxVcoCount2000HBR3;
WORD g_usDpRxVcoCount2000HBR3_9G;

WORD g_usDpRxCountSSTUpperBound2000RBR;
WORD g_usDpRxCountSSTUpperBound2000HBR;
WORD g_usDpRxCountSSTUpperBound2000HBR2;
WORD g_usDpRxCountSSTUpperBound2000HBR3;
WORD g_usDpRxCountSSTUpperBound2000HBR3_9G;

WORD g_usDpRxCountSSTLowerBound2000RBR;
WORD g_usDpRxCountSSTLowerBound2000HBR;
WORD g_usDpRxCountSSTLowerBound2000HBR2;
WORD g_usDpRxCountSSTLowerBound2000HBR3;
WORD g_usDpRxCountSSTLowerBound2000HBR3_9G;

WORD g_usDpRxCountMSTUpperBound2000RBR;
WORD g_usDpRxCountMSTUpperBound2000HBR;
WORD g_usDpRxCountMSTUpperBound2000HBR2;
WORD g_usDpRxCountMSTUpperBound2000HBR3;
WORD g_usDpRxCountMSTUpperBound2000HBR3_9G;

WORD g_usDpRxCountMSTLowerBound2000RBR;
WORD g_usDpRxCountMSTLowerBound2000HBR;
WORD g_usDpRxCountMSTLowerBound2000HBR2;
WORD g_usDpRxCountMSTLowerBound2000HBR3;
WORD g_usDpRxCountMSTLowerBound2000HBR3_9G;

WORD g_usDpRxCountD10P2UpperBound1000RBR;
WORD g_usDpRxCountD10P2UpperBound1000HBR;
WORD g_usDpRxCountD10P2UpperBound1000HBR2;
WORD g_usDpRxCountD10P2UpperBound1000HBR3;
WORD g_usDpRxCountD10P2UpperBound1000HBR3_9G;

WORD g_usDpRxCountD10P2LowerBound1000RBR;
WORD g_usDpRxCountD10P2LowerBound1000HBR;
WORD g_usDpRxCountD10P2LowerBound1000HBR2;
WORD g_usDpRxCountD10P2LowerBound1000HBR3;
WORD g_usDpRxCountD10P2LowerBound1000HBR3_9G;

WORD g_usDpRxCountUpperBound1000RBR;
WORD g_usDpRxCountUpperBound1000HBR;
WORD g_usDpRxCountUpperBound1000HBR2;
WORD g_usDpRxCountUpperBound1000HBR3;
WORD g_usDpRxCountUpperBound1000HBR3_9G;

WORD g_usDpRxCountLowerBound1000RBR;
WORD g_usDpRxCountLowerBound1000HBR;
WORD g_usDpRxCountLowerBound1000HBR2;
WORD g_usDpRxCountLowerBound1000HBR3;
WORD g_usDpRxCountLowerBound1000HBR3_9G;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
WORD g_usDpRxVcoCount1000UHBR10;
WORD g_usDpRxVcoCount1000UHBR13_5;
WORD g_usDpRxVcoCount1000UHBR20;

WORD g_usDpRxVcoCount2000UHBR10;
WORD g_usDpRxVcoCount2000UHBR13_5;
WORD g_usDpRxVcoCount2000UHBR20;

WORD g_usDpRxCountSSTUpperBound2000UHBR10;
WORD g_usDpRxCountSSTUpperBound2000UHBR13_5;
WORD g_usDpRxCountSSTUpperBound2000UHBR20;

WORD g_usDpRxCountSSTLowerBound2000UHBR10;
WORD g_usDpRxCountSSTLowerBound2000UHBR13_5;
WORD g_usDpRxCountSSTLowerBound2000UHBR20;

WORD g_usDpRxCountMSTUpperBound2000UHBR10;
WORD g_usDpRxCountMSTUpperBound2000UHBR13_5;
WORD g_usDpRxCountMSTUpperBound2000UHBR20;

WORD g_usDpRxCountMSTLowerBound2000UHBR10;
WORD g_usDpRxCountMSTLowerBound2000UHBR13_5;
WORD g_usDpRxCountMSTLowerBound2000UHBR20;

WORD g_usDpRxCountD10P2UpperBound1000UHBR10;
WORD g_usDpRxCountD10P2UpperBound1000UHBR13_5;
WORD g_usDpRxCountD10P2UpperBound1000UHBR20;

WORD g_usDpRxCountD10P2LowerBound1000UHBR10;
WORD g_usDpRxCountD10P2LowerBound1000UHBR13_5;
WORD g_usDpRxCountD10P2LowerBound1000UHBR20;

WORD g_usDpRxCountUpperBound1000UHBR10;
WORD g_usDpRxCountUpperBound1000UHBR13_5;
WORD g_usDpRxCountUpperBound1000UHBR20;

WORD g_usDpRxCountLowerBound1000UHBR10;
WORD g_usDpRxCountLowerBound1000UHBR13_5;
WORD g_usDpRxCountLowerBound1000UHBR20;
#endif

StructDpPortHpdAssertType g_stDpRxHpdType =
{
#if(_D0_DP_SUPPORT == _ON)
    _DP_HPD_NONE,
#endif
#if(_D1_DP_SUPPORT == _ON)
    _DP_HPD_NONE,
#endif
#if(_D2_DP_SUPPORT == _ON)
    _DP_HPD_NONE,
#endif
};

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
volatile BYTE data g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter;
BYTE data g_ucDpRxHpdIrqAssertT2EventDelay5usI;
#endif

#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
EnumInputPort g_penumDpRxMacDphyEntityGroup[_DP_MAC_DPHY_ENTITY_MAX];
#endif

EnumDpMacStreamSourceType g_penumDpRxMacEntityGroup[_DP_MAC_ENTITY_MAX];

volatile EnumInputPort g_enumDpRxBaseInputPort;

#if(_DP_PR_MODE_SUPPORT == _ON)
volatile StructDpPRModeSupportInfo g_stDpRxPRModeInfo;
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
volatile StructDpAuxlessAlpmSupportInfo g_stDpRxAuxlessAlpmInfo;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
volatile StructDpHdrSupportInfo g_stDpRxHdrInfo;
#endif
#endif

#if(_DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
bit g_bDpRx0LongHpdAllowed = _TRUE;
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
bit g_bDpRx1LongHpdAllowed = _TRUE;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
bit g_bDpRx2LongHpdAllowed = _TRUE;
#endif
#endif

#if(_D9_EMBEDDED_XRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
BYTE g_pucDpRx0PxpEdid[_D9_EMBEDDED_XRAM_MAX_SIZE];
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
BYTE g_pucDpRx1PxpEdid[_D9_EMBEDDED_XRAM_MAX_SIZE];
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
BYTE g_pucDpRx2PxpEdid[_D9_EMBEDDED_XRAM_MAX_SIZE];
#endif
#else
BYTE g_pucDpRxPxpEdid[_D9_EMBEDDED_XRAM_MAX_SIZE];
#endif
#endif

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
EnumDpHpdToggleMode g_enumDpRxDcOnHpdToggleMode = _DP_HPD_TOGGLE_NORMAL;
#endif

#if(_DP_USER_INT0_SUPPORT == _ON)
volatile EnumDpUserIntEvent g_penumDpRxUserIntEvent[3];
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Global Parameter MeasureCount Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMeasureCountInitial(void)
{
    g_usDpRxVcoCount1000RBR = _DP_RX_VCO_TARGET_COUNT_1000_RBR;
    g_usDpRxVcoCount1000HBR = _DP_RX_VCO_TARGET_COUNT_1000_HBR;
    g_usDpRxVcoCount1000HBR2 = _DP_RX_VCO_TARGET_COUNT_1000_HBR2;
    g_usDpRxVcoCount1000HBR3 = _DP_RX_VCO_TARGET_COUNT_1000_HBR3;
    g_usDpRxVcoCount1000HBR3_9G = _DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G;

    g_usDpRxVcoCount2000RBR = _DP_RX_VCO_TARGET_COUNT_2000_RBR;
    g_usDpRxVcoCount2000HBR = _DP_RX_VCO_TARGET_COUNT_2000_HBR;
    g_usDpRxVcoCount2000HBR2 = _DP_RX_VCO_TARGET_COUNT_2000_HBR2;
    g_usDpRxVcoCount2000HBR3 = _DP_RX_VCO_TARGET_COUNT_2000_HBR3;
    g_usDpRxVcoCount2000HBR3_9G = _DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G;

    g_usDpRxCountSSTUpperBound2000RBR = _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_RBR;
    g_usDpRxCountSSTUpperBound2000HBR = _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR;
    g_usDpRxCountSSTUpperBound2000HBR2 = _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR2;
    g_usDpRxCountSSTUpperBound2000HBR3 = _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR3;
    g_usDpRxCountSSTUpperBound2000HBR3_9G = _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR3_9G;

    g_usDpRxCountSSTLowerBound2000RBR = _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_RBR;
    g_usDpRxCountSSTLowerBound2000HBR = _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR;
    g_usDpRxCountSSTLowerBound2000HBR2 = _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR2;
    g_usDpRxCountSSTLowerBound2000HBR3 = _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR3;
    g_usDpRxCountSSTLowerBound2000HBR3_9G = _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR3_9G;

    g_usDpRxCountMSTUpperBound2000RBR = _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_RBR;
    g_usDpRxCountMSTUpperBound2000HBR = _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR;
    g_usDpRxCountMSTUpperBound2000HBR2 = _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR2;
    g_usDpRxCountMSTUpperBound2000HBR3 = _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR3;
    g_usDpRxCountMSTUpperBound2000HBR3_9G = _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR3_9G;

    g_usDpRxCountMSTLowerBound2000RBR = _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_RBR;
    g_usDpRxCountMSTLowerBound2000HBR = _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR;
    g_usDpRxCountMSTLowerBound2000HBR2 = _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR2;
    g_usDpRxCountMSTLowerBound2000HBR3 = _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR3;
    g_usDpRxCountMSTLowerBound2000HBR3_9G = _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR3_9G;

    g_usDpRxCountD10P2UpperBound1000RBR = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_RBR;
    g_usDpRxCountD10P2UpperBound1000HBR = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR;
    g_usDpRxCountD10P2UpperBound1000HBR2 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR2;
    g_usDpRxCountD10P2UpperBound1000HBR3 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3;
    g_usDpRxCountD10P2UpperBound1000HBR3_9G = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3_9G;

    g_usDpRxCountD10P2LowerBound1000RBR = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_RBR;
    g_usDpRxCountD10P2LowerBound1000HBR = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR;
    g_usDpRxCountD10P2LowerBound1000HBR2 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR2;
    g_usDpRxCountD10P2LowerBound1000HBR3 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3;
    g_usDpRxCountD10P2LowerBound1000HBR3_9G = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3_9G;

    g_usDpRxCountUpperBound1000RBR = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_RBR;
    g_usDpRxCountUpperBound1000HBR = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR;
    g_usDpRxCountUpperBound1000HBR2 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR2;
    g_usDpRxCountUpperBound1000HBR3 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3;
    g_usDpRxCountUpperBound1000HBR3_9G = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3_9G;

    g_usDpRxCountLowerBound1000RBR = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_RBR;
    g_usDpRxCountLowerBound1000HBR = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR;
    g_usDpRxCountLowerBound1000HBR2 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR2;
    g_usDpRxCountLowerBound1000HBR3 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3;
    g_usDpRxCountLowerBound1000HBR3_9G = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3_9G;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    g_usDpRxVcoCount1000UHBR10 = _DP_RX_VCO_TARGET_COUNT_1000_UHBR10;
    g_usDpRxVcoCount1000UHBR13_5 = _DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5;
    g_usDpRxVcoCount1000UHBR20 = _DP_RX_VCO_TARGET_COUNT_1000_UHBR20;

    g_usDpRxVcoCount2000UHBR10 = _DP_RX_VCO_TARGET_COUNT_2000_UHBR10;
    g_usDpRxVcoCount2000UHBR13_5 = _DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5;
    g_usDpRxVcoCount2000UHBR20 = _DP_RX_VCO_TARGET_COUNT_2000_UHBR20;

    g_usDpRxCountSSTUpperBound2000UHBR10 = _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_UHBR10;
    g_usDpRxCountSSTUpperBound2000UHBR13_5 = _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_UHBR13_5;
    g_usDpRxCountSSTUpperBound2000UHBR20 = _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_UHBR20;

    g_usDpRxCountSSTLowerBound2000UHBR10 = _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_UHBR10;
    g_usDpRxCountSSTLowerBound2000UHBR13_5 = _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_UHBR13_5;
    g_usDpRxCountSSTLowerBound2000UHBR20 = _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_UHBR20;

    g_usDpRxCountMSTUpperBound2000UHBR10 = _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_UHBR10;
    g_usDpRxCountMSTUpperBound2000UHBR13_5 = _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_UHBR13_5;
    g_usDpRxCountMSTUpperBound2000UHBR20 = _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_UHBR20;

    g_usDpRxCountMSTLowerBound2000UHBR10 = _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_UHBR10;
    g_usDpRxCountMSTLowerBound2000UHBR13_5 = _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_UHBR13_5;
    g_usDpRxCountMSTLowerBound2000UHBR20 = _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_UHBR20;

    g_usDpRxCountD10P2UpperBound1000UHBR10 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR10;
    g_usDpRxCountD10P2UpperBound1000UHBR13_5 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR13_5;
    g_usDpRxCountD10P2UpperBound1000UHBR20 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR20;

    g_usDpRxCountD10P2LowerBound1000UHBR10 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR10;
    g_usDpRxCountD10P2LowerBound1000UHBR13_5 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR13_5;
    g_usDpRxCountD10P2LowerBound1000UHBR20 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR20;

    g_usDpRxCountUpperBound1000UHBR10 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR10;
    g_usDpRxCountUpperBound1000UHBR13_5 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR13_5;
    g_usDpRxCountUpperBound1000UHBR20 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR20;

    g_usDpRxCountLowerBound1000UHBR10 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR10;
    g_usDpRxCountLowerBound1000UHBR13_5 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR13_5;
    g_usDpRxCountLowerBound1000UHBR20 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR20;
#endif
}

//--------------------------------------------------
// Description  : Initial Setting for DP
// Input Value  : enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumDisplayMode, enumFreeSyncSupport
// Output Value : None
//--------------------------------------------------
void ScalerDpRxInitial(EnumInputPort enumInputPort)
{
    ScalerDpRxConfigPinInitial(enumInputPort);

    ScalerDpAuxRxSetLaneMapping(enumInputPort, _TYPE_C_PIN_ASSIGNMENT_C, _TYPE_C_ORIENTATION_UNFLIP);

    ScalerDpAuxRxInitial(enumInputPort);

    ScalerDpAuxRxSetFakeLinkTraining(enumInputPort);

    ScalerDpHdcpRxInitial(enumInputPort);

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpMacDphyRxInitial(enumInputPort);
#endif

    ScalerDpMacStreamRxSdpInitial(enumInputPort);

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpMstRxPowerOnInitial(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : Get Dp Port
// Input Value  : Dp Valid Port Num Index
// Output Value : Valid DP InputPort
//--------------------------------------------------
EnumDpInputPort ScalerDpRxGetDpPort(BYTE ucIndex)
{
    return tValidDpPort[ucIndex % _DP_PORT_VALID];
}

//--------------------------------------------------
// Description  : Check DP Into Power Saving
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxPowerSwitch(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            SET_DP_DC_OFF_HPD_TOGGLE_FLAG();

            ScalerSyncDpLowPowerProc();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            ScalerSyncDpLowPowerProc();

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            if(enumPowerAction == _POWER_ACTION_PS_TO_NORMAL)
            {
                ScalerSyncDpPowerSwitchHpdToggleProc(_POWER_ACTION_PS_TO_NORMAL);
            }

#if(_D0_DP_SUPPORT == _ON)

            ScalerDpAuxRxPowerOn(_D0_INPUT_PORT);

            ScalerDpMacStreamRxSdpInitial(_D0_INPUT_PORT);
#endif // End of #if(_D0_DP_SUPPORT == _ON)

#if(_D1_DP_SUPPORT == _ON)

            ScalerDpAuxRxPowerOn(_D1_INPUT_PORT);

            ScalerDpMacStreamRxSdpInitial(_D1_INPUT_PORT);
#endif // End of #if(_D1_DP_SUPPORT == _ON)

#if(_D2_DP_SUPPORT == _ON)

            ScalerDpAuxRxPowerOn(_D2_INPUT_PORT);

            ScalerDpMacStreamRxSdpInitial(_D2_INPUT_PORT);
#endif // End of #if(_D2_DP_SUPPORT == _ON)

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
            ScalerDpMacStreamRxSdpInitial(_D9_INPUT_PORT);
#endif

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
            ScalerDpMacMstToSstSdpInitial();

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerDpMstTx128b132bTo8b10bInitial();
#endif

#endif
            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

            SET_DP_DC_OFF_HPD_TOGGLE_FLAG();

            break;

        default:
            break;
    }
}

#if(_EMBEDDED_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP EDID Switch
// Input Value  : Input DP Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRxEdidSwitch(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_DP_RX_D0_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_DP_RX_D1_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_DP_RX_D2_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:
            SET_DP_RX_D0_EDID_SWITCH();
            SET_DP_RX_D1_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:
            SET_DP_RX_D1_EDID_SWITCH();
            SET_DP_RX_D2_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : DP input port, _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRxVersionSwitch(EnumInputPort enumInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_DP_RX_D2_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:
            SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:
            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D2_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check Dp Audio Stream VBID
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> Get Audio Stream
//--------------------------------------------------
bit ScalerDpRxGetAudioStream(EnumInputPort enumInputPort)
{
    if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return ScalerDpMacStreamRxGetAudioStream(enumInputPort);
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Video Stream VBID
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRxGetVideoStream(EnumInputPort enumInputPort)
{
    if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return ScalerDpMacStreamRxGetVideoStream(enumInputPort);
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp DSC Stream VBID
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> Get DSC Stream
//--------------------------------------------------
bit ScalerDpRxGetDscStream(EnumInputPort enumInputPort)
{
    if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return ScalerDpMacStreamRxGetDscStream(ScalerDpRxGetMacSwitch(enumInputPort));
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Read DP Rx Error Count
// Input Value  : DP Input Port
// Output Value : DP 4 Lane Error Count & Valid Flag
//--------------------------------------------------
StructDpRxErrorCount ScalerDpRxGetErrorCount(EnumInputPort enumInputPort)
{
    StructDpRxErrorCount stDpRxErrorCount;

    if((ScalerDpMacDphyRxCDRCheck(enumInputPort) == _FALSE) || (ScalerDpMacDphyRxSignalCheck(enumInputPort) == _FALSE))
    {
        DebugMessageDpRx("Rx Fail to Report Valid Error Counter", 0x00);

        switch(ScalerDpAuxRxGetLaneCount(enumInputPort))
        {
            case _DP_LINK_1_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            case _DP_LINK_2_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            default:
            case _DP_LINK_4_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0x7FFF;

                break;
        }
    }
    else
    {
        switch(ScalerDpAuxRxGetLaneCount(enumInputPort))
        {
            case _DP_LINK_1_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, _DP_LANE_0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            case _DP_LINK_2_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, _DP_LANE_0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, _DP_LANE_1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            default:
            case _DP_LINK_4_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, _DP_LANE_0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, _DP_LANE_1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, _DP_LANE_2);
                stDpRxErrorCount.usDpRxLane3ErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, _DP_LANE_3);

                break;
        }
    }

    // Reset Error Counter
    ScalerDpMacDphyRxDecodeErrorCountReset(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B);

    return stDpRxErrorCount;
}

//--------------------------------------------------
// Description  : Get DP Link Rate For PCB Limit
// Input Value  : Input Port
// Output Value : EnumDpLinkRate
//--------------------------------------------------
EnumDpLinkRate ScalerDpRxRGetPcbMaxLinkRate(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return _D0_DP_LINK_CLK_RATE;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return _D1_DP_LINK_CLK_RATE;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return _D2_DP_LINK_CLK_RATE;
#endif
        default:
            return _DP_LINK_SPEED_NONE;
    }
}

//--------------------------------------------------
// Description  : Set DP Pixel Clock
// Input Value  : DP Stream Clock(Unit is 0.1MHz)
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetInputPixelClock(EnumInputPort enumInputPort, DWORD ulStreamClk)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            SET_D0_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            SET_D1_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            SET_D2_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_DP_SUPPORT == _ON)

        case _D9_INPUT_PORT:

            SET_D9_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif
#endif

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : Get DP Pixel Clock
// Input Value  : None
// Output Value : DP Stream Clock(Unit is 0.1MHz)
//--------------------------------------------------
WORD ScalerDpRxGetInputPixelClock(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            return GET_D0_INPUT_PIXEL_CLK();
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            return GET_D1_INPUT_PIXEL_CLK();
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:
            return GET_D2_INPUT_PIXEL_CLK();
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_DP_SUPPORT == _ON)

        case _D9_INPUT_PORT:
            return GET_D9_INPUT_PIXEL_CLK();
#endif
#endif

        default:

            return 0x0000;
    }
}

//--------------------------------------------------
// Description  : Set DP Pixel Clock
// Input Value  : DP Stream Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetNativeInputPixelClock(EnumInputPort enumInputPort, DWORD ulStreamClk)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            SET_D0_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            SET_D1_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            SET_D2_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_DP_SUPPORT == _ON)

        case _D9_INPUT_PORT:

            SET_D9_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Pixel Clock
// Input Value  : None
// Output Value : DP Stream Clock
//--------------------------------------------------
WORD ScalerDpRxGetNativeInputPixelClock(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            return GET_D0_NATIVE_INPUT_PIXEL_CLK();
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            return GET_D1_NATIVE_INPUT_PIXEL_CLK();
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            return GET_D2_NATIVE_INPUT_PIXEL_CLK();
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_DP_SUPPORT == _ON)

        case _D9_INPUT_PORT:

            return GET_D9_NATIVE_INPUT_PIXEL_CLK();
#endif
#endif
        default:

            return 0x0000;
    }
}

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Margin Link Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetMarginLink(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            SET_DP_RX_D0_MARGIN_LINK();

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            SET_DP_RX_D1_MARGIN_LINK();

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            SET_DP_RX_D2_MARGIN_LINK();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear DP HBR2 Margin Link Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxClearMarginLink(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            CLR_DP_RX_D0_MARGIN_LINK();

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            CLR_DP_RX_D1_MARGIN_LINK();

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            CLR_DP_RX_D2_MARGIN_LINK();

            break;
#endif
        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : DP Lane Switch
// Input Value  : DP input port, DP Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRxLaneCountSwitch(EnumInputPort enumInputPort, EnumDpLaneCount enumDpLaneCount)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_DP_RX_D2_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Source MST enable (DPCD 00111h[0])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST enable, _FALSE --> SST
//--------------------------------------------------
bit ScalerDpRxGetSrcMstEnable(EnumInputPort enumInputPort)
{
    return (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT0) == _BIT0);
}

//--------------------------------------------------
// Description  : Get DP Source MST Up Request enable (DPCD 00111h[1])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST Up Request enable, _FALSE --> MST Up Request Disable
//--------------------------------------------------
bit ScalerDpRxGetSrcMstUpRequestEnable(EnumInputPort enumInputPort)
{
    return (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT1) == _BIT1);
}

//--------------------------------------------------
// Description  : Get DP MST Capaility (DPCD 00021[0])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST enable, _FALSE --> SST
//--------------------------------------------------
bit ScalerDpRxGetMstCapability(EnumInputPort enumInputPort)
{
    return (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0);
}

//--------------------------------------------------
// Description  : Get DP Tx Clone enable
// Input Value  : DP Input Port
// Output Value : _TRUE --> Clone enable, _FALSE --> Clone disable
//--------------------------------------------------
bit ScalerDpRxGetTxCloneEnable(EnumInputPort enumInputPort)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
#if(_DP_MST_SUPPORT == _ON)
        // 00021[1:0] = 01 or 11 --> MST MODE = _DP_RX_MST_MODE_STATUS_NONE_MSG --> Clone
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0)
        {
            ScalerDpRxSetBaseInputPort(enumInputPort);

            return (GET_DP_MST_RX_MODE_STATE() == _DP_RX_MST_MODE_STATUS_NONE_MSG);
        }
        else
#endif
        {
            // 00021[1:0] = 10 or 00 --> Clone
            return _TRUE;
        }
    }
    else
#endif
    {
        return (ScalerDpRxGetSrcMstEnable(enumInputPort) == _FALSE);
    }
}

//--------------------------------------------------
// Description  : Set Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetHotPlugEvent(EnumInputPort enumInputPort, EnumDpHotPlugAssertType enumHpdType)
{
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    if((ScalerDebugCheckDebugPort(enumInputPort) == _TRUE) && (ScalerDpRxCableStatus(enumInputPort) == _TRUE))
    {
        if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
        {
            return;
        }
    }
#endif

    if((enumHpdType > _DP_HPD_LOW) && (ScalerDpRxCableStatus(enumInputPort) == _FALSE))
    {
        return;
    }

#if(_DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT == _ON)
    if(ScalerDpRxLongHpdGetAllowed(enumInputPort) == _FALSE)
    {
        if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
        {
            if((enumHpdType > _DP_HPD_LOW) && (enumHpdType < _DP_HPD_ASSERTED))
            {
                return;
            }
        }
    }
#endif

    // If the priority of enumHpdType is lower
    if(enumHpdType >= ScalerDpRxGetHotPlugEvent(enumInputPort))
    {
        return;
    }

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_DP_RX0_HOTPLUG_ASSERT_TYPE(enumHpdType);
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_DP_RX1_HOTPLUG_ASSERT_TYPE(enumHpdType);
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_DP_RX2_HOTPLUG_ASSERT_TYPE(enumHpdType);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : EnumDpHotPlugAssertType
//--------------------------------------------------
EnumDpHotPlugAssertType ScalerDpRxGetHotPlugEvent(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return GET_DP_RX0_HOTPLUG_ASSERT_TYPE();
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_DP_RX1_HOTPLUG_ASSERT_TYPE();
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_DP_RX2_HOTPLUG_ASSERT_TYPE();
#endif

        default:
            break;
    }

    return _DP_HPD_NONE;
}

//--------------------------------------------------
// Description  : Clear Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRxClearHotPlugEvent(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            CLR_DP_RX0_HOTPLUG_ASSERT_TYPE();
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            CLR_DP_RX1_HOTPLUG_ASSERT_TYPE();
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            CLR_DP_RX2_HOTPLUG_ASSERT_TYPE();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Hot Plug Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxHotPlugHandler(void)
{
    BYTE ucI = 0;
    BYTE ucPortNum = 0;
    EnumInputPort enumInputPort = _D0_INPUT_PORT;

    StructHpdSequence pstHpdSeq[] =
    {
        // dummy
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},

#if(_D0_DP_SUPPORT == _ON)
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},
#endif
#if(_D1_DP_SUPPORT == _ON)
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},
#endif
#if(_D2_DP_SUPPORT == _ON)
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},
#endif
    };

    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        EnumDpHotPlugAssertType enumHpdType = ScalerDpRxGetHotPlugEvent(enumInputPort);

        if(enumHpdType == _DP_HPD_NONE)
        {
            continue;
        }

#if(_DP_MST_SUPPORT == _ON)
        // Skip Long HPD if There's a MSG to Be Processed
        if((enumHpdType > _DP_HPD_LOW) && (enumHpdType < _DP_HPD_ASSERTED) &&
           (ScalerDpRxGetMstCapability(enumInputPort) == _TRUE) &&
           (ScalerDpMstRxCheckMsgTransition(enumInputPort) == _TRUE))
        {
            continue;
        }
#endif

        if((pstHpdSeq[1 + ucPortNum].enumHpdTime = ScalerDpAuxRxBeforeHpdToggleProc(enumInputPort, enumHpdType)) != _DP_HPD_TIME_NONE)
        {
            pstHpdSeq[1 + ucPortNum].enumInputPort = enumInputPort;
            ucPortNum ++;
        }

        ScalerDpRxClearHotPlugEvent(enumInputPort);
    }

    if(ucPortNum == 0)
    {
        return;
    }

#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_DELAY_MODE)
    // Bubble sort for reorder squence (HPD time short -> long)
    for(pData[0] = 1; pData[0] < ucPortNum; pData[0] ++)
    {
        for(pData[1] = 1; pData[1] <= (ucPortNum - pData[0]); pData[1] ++)
        {
            if(pstHpdSeq[pData[1]].enumHpdTime > pstHpdSeq[pData[1] + 1].enumHpdTime)
            {
                pstHpdSeq[0] = pstHpdSeq[pData[1]];
                pstHpdSeq[pData[1]] = pstHpdSeq[pData[1] + 1];
                pstHpdSeq[pData[1] + 1] = pstHpdSeq[0];
            }
        }
    }

    // Reset the dummy seq time for first HPD delay calculation
    pstHpdSeq[0].enumInputPort = _NO_INPUT_PORT;
    pstHpdSeq[0].enumHpdTime = 0;
#endif

    // ----------- Low Process -----------
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        if(pstHpdSeq[ucI].enumHpdTime == _DP_HPD_ASSERTED_TIME)
        {
            // Skip low process of this turn
            continue;
        }

        if(ScalerDpRxCableStatus(pstHpdSeq[ucI].enumInputPort) == _TRUE)
        {
            ScalerDpRxSetHotPlug(pstHpdSeq[ucI].enumInputPort, _LOW, pstHpdSeq[ucI].enumHpdTime);
        }
    }

    // ----------- High Process -----------
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        if(ScalerDpRxCableStatus(pstHpdSeq[ucI].enumInputPort) == _TRUE)
        {
#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_DELAY_MODE)
            if((pstHpdSeq[ucI].enumHpdTime != pstHpdSeq[ucI - 1].enumHpdTime))
            {
                ScalerTimerDelayXms(pstHpdSeq[ucI].enumHpdTime - pstHpdSeq[ucI - 1].enumHpdTime);
            }
            else
            {
#if(_DP_PHYSICAL_PORT_VALID > 1)
                // Avoid pulling high concurrently (solution of NVIDIA probably ignoring the sencond HPD high while 2 ports conneted)
                if(ucI >= 2)
                {
                    ScalerTimerDelayXms(20);
                }
#endif
            }
#endif

#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_TIMEREVENT_MODE)
            if(pstHpdSeq[ucI].enumHpdTime > 0)
            {
                // Set Assert High Timer Event
                ScalerDpRxReactiveTimerEventHotPlugAsserted(pstHpdSeq[ucI].enumInputPort, pstHpdSeq[ucI].enumHpdTime);
            }
            else
#endif
            {
                ScalerDpAuxRxAfterHpdToggleProc(pstHpdSeq[ucI].enumInputPort);

                ScalerDpRxSetHotPlug(pstHpdSeq[ucI].enumInputPort, _HIGH, 0);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Dp Hot Plug Set Assert High Timer Event
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxReactiveTimerEventHotPlugAsserted(EnumInputPort enumInputPort, WORD usTime)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            ScalerTimerReactiveTimerEvent(usTime, _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            ScalerTimerReactiveTimerEvent(usTime, _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            ScalerTimerReactiveTimerEvent(usTime, _SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Mac Stream Source Type
// Input Value  : enumMacSel
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
EnumDpMacStreamSourceType ScalerDpRxGetMacStreamSourceType(EnumDpMacSel enumMacSel)
{
    if(enumMacSel >= _DP_MAC_ENTITY_MAX)
    {
        return _STREAM_SOURCE_NONE;
    }

    return g_penumDpRxMacEntityGroup[enumMacSel];
}


//--------------------------------------------------
// Description  : Get Mac Switch according to enumMacSourceType
// Input Value  : enumMacSourceType
// Output Value : EnumDpMacSel
//--------------------------------------------------
EnumDpMacSel ScalerDpRxGetMacSwitchMappingSourceType(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumDpMacSel enumMacIndex = 0;

    if(enumDpMacStreamSourceType == _STREAM_SOURCE_NONE)
    {
        return _DP_MAC_NONE;
    }

    for(enumMacIndex = 0; enumMacIndex < _DP_MAC_ENTITY_MAX; enumMacIndex++)
    {
        if(g_penumDpRxMacEntityGroup[enumMacIndex] == enumDpMacStreamSourceType)
        {
            return enumMacIndex;
        }
    }

    return _DP_MAC_NONE;
}

//--------------------------------------------------
// Description  : Get InputPort according to enumMacSourceType
// Input Value  : enumMacSourceType
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDpRxGetInputPortMappingSourceType(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            enumInputPort = _D0_INPUT_PORT;
#endif
            break;

        case _STREAM_SOURCE_D1_DP:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            enumInputPort = _D1_INPUT_PORT;
#endif

            break;

        case _STREAM_SOURCE_D2_DP:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            enumInputPort = _D2_INPUT_PORT;
#endif

            break;

        case _STREAM_SOURCE_MST2SST:

#if(_DP_MST2SST_SUPPORT == _ON)
            enumInputPort = GET_DP_RX_MAIN_PORT();
#endif
            break;

        case _STREAM_SOURCE_PXP:

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            enumInputPort = _D9_INPUT_PORT;
#endif
            break;

        default:
            break;
    }

    return enumInputPort;
}

#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Mac Switch
// Input Value  : enumDpMacSel, enumMacSource
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpRxSetMacDphySwitch(EnumDpMacDphySel enumDpMacDphySel, EnumInputPort enumInputPort)
{
    if(enumDpMacDphySel >= _DP_MAC_DPHY_ENTITY_MAX)
    {
        return _FALSE;
    }

    g_penumDpRxMacDphyEntityGroup[enumDpMacDphySel] = enumInputPort;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Mac Dphy Switch to InputPort
// Input Value  : EnumDpMacEnum, enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetMacDphySwitchToInputPort(EnumDpMacDphySel enumDpMacDphySel, EnumInputPort enumInputPort)
{
    // Set Mux Register
    ScalerDpRxSetPhyToMacDphyMux(enumDpMacDphySel, enumInputPort);

    ScalerDpRxSetMacDphySwitch(enumDpMacDphySel, enumInputPort);
}
#endif

//--------------------------------------------------
// Description  : Set Mac Switch to InputPort
// Input Value  : EnumDpMacEnum, enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetMacSwitchToInputPort(EnumDpMacSel enumDpMacSel, EnumInputPort enumInputPort)
{
    enumDpMacSel = enumDpMacSel;
    enumInputPort = enumInputPort;

#if(_DP_MAC_SWITCH_SUPPORT == _ON)
#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
    // Set Mux Register
    ScalerDpRxSetMacDphyToStreamMux(enumDpMacSel, enumInputPort);
#endif

#if(_DUAL_DP_SUPPORT == _ON)
    // Backup To Mac Variable Data Group
    if(enumInputPort == _D7_INPUT_PORT)
    {
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
        ScalerDpRxSetMacSwitch(_DP_MAC_0, ScalerDpRxDxMacSourceMapping(_DUAL_DP_MAIN_PORT));
        ScalerDpRxSetMacSwitch(_DP_MAC_1, ScalerDpRxDxMacSourceMapping(_DUAL_DP_SUB_PORT));
#endif
    }
    else if(enumInputPort == _D8_INPUT_PORT)
    {
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
        ScalerDpRxSetMacSwitch(_DP_MAC_1, ScalerDpRxDxMacSourceMapping(_DUAL_DP_MAIN_PORT));
        ScalerDpRxSetMacSwitch(_DP_MAC_2, ScalerDpRxDxMacSourceMapping(_DUAL_DP_SUB_PORT));
#endif
    }
    else
#endif
    {
        ScalerDpRxSetMacSwitch(enumDpMacSel, ScalerDpRxDxMacSourceMapping(enumInputPort));
    }

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
    // Sync MST Mux
    ScalerDpMacDphyRxSyncSourceMux(enumDpMacSel, enumInputPort);
#endif
#endif

#endif
}

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Dphy to Stream MUX
// Input Value  : EnumDpMacSel, EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetMacDphyToStreamMux(EnumDpMacSel enumDpMacSel, EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

            switch(enumDpMacSel)
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    // Set Mac0 Switch to D0 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT7 | _BIT6), 0x00);
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    // Set Mac1 Switch to D0 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT5 | _BIT4), 0x00);
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    // Set Mac2 Switch to D0 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT3 | _BIT2), 0x00);
                    break;
#endif

                default:
                    break;
            }

            break;

        case _D1_INPUT_PORT:

            switch(enumDpMacSel)
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    // Set Mac0 Switch to D1 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT7 | _BIT6), _BIT6);
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    // Set Mac1 Switch to D1 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT5 | _BIT4), _BIT4);
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    // Set Mac2 Switch to D1 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT3 | _BIT2), _BIT2);
                    break;
#endif

                default:
                    break;
            }

            break;

        case _D2_INPUT_PORT:

            switch(enumDpMacSel)
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    // Set Mac0 Switch to D2 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT7 | _BIT6), _BIT7);
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    // Set Mac1 Switch to D2 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT5 | _BIT4), _BIT5);
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    // Set Mac2 Switch to D2 Port
                    ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT3 | _BIT2), _BIT3);
                    break;
#endif

                default:
                    break;
            }

            break;

        case _D7_INPUT_PORT:
            enumDpMacSel = enumDpMacSel;

#if(_DP_MAC_RX0_SUPPORT == _ON)
            // Set Mac0 Switch to D0 Port
            ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT7 | _BIT6), 0x00);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
            // Set Mac1 Switch to D1 Port
            ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT5 | _BIT4), _BIT4);
#endif

            break;

        case _D8_INPUT_PORT:
            enumDpMacSel = enumDpMacSel;

#if(_DP_MAC_RX1_SUPPORT == _ON)
            // Set Mac0 Switch to D1 Port
            ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT7 | _BIT6), _BIT6);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
            // Set Mac1 Switch to D2 Port
            ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT5 | _BIT4), _BIT5);
#endif

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Reset Dphy to Stream MUX
// Input Value  : enumDpMacSel
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMacDphyToStreamMuxReset(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            // Reset Mac0 Switch to D0 Port
            ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT7 | _BIT6), 0x00);
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            // Reset Mac1 Switch to D0 Port
            ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT5 | _BIT4), 0x00);
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            // Reset Mac2 Switch to D0 Port
            ScalerSetBit(P6F_09_MUX_DPRX_MAC, ~(_BIT3 | _BIT2), 0x00);
            break;
#endif

        default:
            break;
    }
}

#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Mac Arbitration For Mst2Sst
// Input Value  : enumMstMainPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMacStreamArbiterMst2Sst(EnumInputPort enumMstMainPort)
{
    enumMstMainPort = enumMstMainPort;

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

    // Set Mux Register
    ScalerDpRxSetMacDphyToStreamMux(enumDpMacSel, enumMstMainPort);

    // Sync MST Mux
    ScalerDpMacDphyRxSyncSourceMux(enumDpMacSel, enumMstMainPort);

    // Select DPTX Source from DPRX Mac
    ScalerSetBit(P6F_04_MUX_DPRX_OUT, ~(_BIT7 | _BIT6), enumDpMacSel << 6);
#endif
}
#endif


//--------------------------------------------------
// Description  : Get DP Mac Switch Status
// Input Value  : EnumDpMacEnum
// Output Value : None
//--------------------------------------------------
EnumDpMacSel ScalerDpRxGetMacSwitch(EnumInputPort enumInputPort)
{
    EnumDpMacSel enumMacIndex = 0;
    EnumDpMacSel enumMacSel = _DP_MAC_NONE;

#if((_D7_DP_SUPPORT == _ON) || (_D8_DP_SUPPORT == _ON))
    EnumDpMacSel enumDpMacSelMain = _DP_MAC_NONE;
    EnumDpMacSel enumDpMacSelSub = _DP_MAC_NONE;
#endif

    for(enumMacIndex = 0; enumMacIndex < _DP_MAC_ENTITY_MAX; enumMacIndex++)
    {
        if(g_penumDpRxMacEntityGroup[enumMacIndex] == _STREAM_SOURCE_NONE)
        {
            continue;
        }

#if((_D7_DP_SUPPORT == _ON) || (_D8_DP_SUPPORT == _ON))
        if((enumInputPort == _D7_INPUT_PORT) || (enumInputPort == _D8_INPUT_PORT))
        {
            if(g_penumDpRxMacEntityGroup[enumMacIndex] == ScalerDpRxDxMacSourceMapping(_DUAL_DP_MAIN_PORT))
            {
                enumDpMacSelMain = enumMacIndex;
            }

            if(g_penumDpRxMacEntityGroup[enumMacIndex] == ScalerDpRxDxMacSourceMapping(_DUAL_DP_SUB_PORT))
            {
                enumDpMacSelSub = enumMacIndex;
            }

            if((enumDpMacSelMain != _DP_MAC_NONE) && (enumDpMacSelSub != _DP_MAC_NONE))
            {
                enumMacSel = _DP_MAC_DUAL;
                break;
            }
        }
        else
#endif
        {
            if(g_penumDpRxMacEntityGroup[enumMacIndex] == ScalerDpRxDxMacSourceMapping(enumInputPort))
            {
                enumMacSel = enumMacIndex;
                break;
            }
        }
    }

    return enumMacSel;
}

//--------------------------------------------------
// Description  : Input Dx Port Mapping to Mac Source Index
// Input Value  : EnumDpMacEnum
// Output Value : EnumDpMacStreamSourceType
//--------------------------------------------------
EnumDpMacStreamSourceType ScalerDpRxDxMacSourceMapping(EnumInputPort enumInputPort)
{
    EnumDpMacStreamSourceType enumMacSource = _STREAM_SOURCE_NONE;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumMacSource = _STREAM_SOURCE_D0_DP;
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumMacSource = _STREAM_SOURCE_D1_DP;
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumMacSource = _STREAM_SOURCE_D2_DP;
            break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:
            enumMacSource = _STREAM_SOURCE_PXP;
            break;
#endif

        default:
            break;
    }

    return enumMacSource;
}

//--------------------------------------------------
// Description  : Set DP Mac Switch
// Input Value  : enumDpMacSel, enumMacSource
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpRxSetMacSwitch(EnumDpMacSel enumDpMacSel, EnumDpMacStreamSourceType enumMacSource)
{
    if(enumDpMacSel >= _DP_MAC_ENTITY_MAX)
    {
        return _FALSE;
    }

    g_penumDpRxMacEntityGroup[enumDpMacSel] = enumMacSource;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get InputPort Switch According to enumDpMacSel
// Input Value  : EnumDpMacEnum
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDpRxMacGetInputPortSwitch(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
        default:
            break;

#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            return ScalerDpRxGetInputPortMappingSourceType(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            return ScalerDpRxGetInputPortMappingSourceType(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            return ScalerDpRxGetInputPortMappingSourceType(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            return ScalerDpRxGetInputPortMappingSourceType(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            return ScalerDpRxGetInputPortMappingSourceType(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            if((g_penumDpRxMacEntityGroup[_DP_MAC_0] == _STREAM_SOURCE_D0_DP) &&
               (g_penumDpRxMacEntityGroup[_DP_MAC_1] == _STREAM_SOURCE_D1_DP))
            {
                return _D7_INPUT_PORT;
            }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            if((g_penumDpRxMacEntityGroup[_DP_MAC_1] == _STREAM_SOURCE_D1_DP) &&
               (g_penumDpRxMacEntityGroup[_DP_MAC_2] == _STREAM_SOURCE_D2_DP))
            {
                return _D8_INPUT_PORT;
            }
#endif
            break;
#endif
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : DP Port Cable Pre-Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpRxCableStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return g_stDpRxCableStatus.b1D0Status;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return g_stDpRxCableStatus.b1D1Status;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return g_stDpRxCableStatus.b1D2Status;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Port Set Cable Pre-Status
// Input Value  : enumInputPort, bStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetCableStatus(EnumInputPort enumInputPort, bit bStatus)
{
    bStatus = bStatus;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            g_stDpRxCableStatus.b1D0Status = bStatus;

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            g_stDpRxCableStatus.b1D1Status = bStatus;

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            g_stDpRxCableStatus.b1D2Status = bStatus;

            break;
#endif

        default:
            break;
    }
}

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Port CableID Pre-Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerDpRxCableIdCtoDpMapping(StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd)
{
    BYTE ucDpCableIDAttribute = 0;

    // Link rate mapping for 13.5G
    if(stTypeCCableInfoForDpcd.b1CableUhbr13p5Support == _TRUE)
    {
        ucDpCableIDAttribute = ucDpCableIDAttribute | _DP_CABLE_UHBR135_CAPABLE;
    }

    // Link rate mapping for 10G & 20G
    if(stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate == _PD_CBL_MAX_UHBR20)
    {
        ucDpCableIDAttribute = ucDpCableIDAttribute | _DP_CABLE_UHBR20_AND_UHBR10_CAPABLE;
    }
    else if(stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate == _PD_CBL_MAX_UHBR10)
    {
        ucDpCableIDAttribute = ucDpCableIDAttribute | _DP_CABLE_UHBR10_CAPABLE;
    }

    // Cable Type mapping
    if(stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent == _PD_CBL_COMPONENT_PASSIVE)
    {
        ucDpCableIDAttribute = ucDpCableIDAttribute | _DP_CABLE_PASSIVE_TYPE;
    }
    else if(stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)
    {
        ucDpCableIDAttribute = ucDpCableIDAttribute | _DP_CABLE_ACTIVE_LRD_TYPE;
    }
    else if(stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent == _PD_CBL_COMPONENT_ACTIVE_RETIMER)
    {
        ucDpCableIDAttribute = ucDpCableIDAttribute | _DP_CABLE_ACCTIVE_RETIMER_TYPE;
    }

    return ucDpCableIDAttribute;
}
#endif

//--------------------------------------------------
// Description  : DP Port Cable Pre-Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
void ScalerDpRxCableIdProc(EnumInputPort enumInputPort)
{
    EnumDpCableIDResult enumDpCableIDResult = _DP_CABLE_ID_RESULT_LOW;

#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};
#endif

    enumDpCableIDResult = enumDpCableIDResult;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

            // Get Cable Infor from typeC
            stTypeCCableInfoForDpcd = ScalerTypeCRxGetCableInfoForDpcd(enumInputPort);

            if(stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate == _PD_CBL_MAX_DP_RATE_UNCONFIRMED)
            {
                // Not Vconn Source or didn't receive DP Config
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x22, 0x17, 0x00);

#if((_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF) && (_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON))
                // Enable Int to update DPCD
                ScalerDpAuxRx0SetDpcdWildCardIntEnable(_AUX_RX_CABLE_ID_UPDATE, _ENABLE);
#endif
            }
            else
            {
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x22, 0x17, ScalerDpRxCableIdCtoDpMapping(stTypeCCableInfoForDpcd));

#if((_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF) && (_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON))
                // Disable Int to update DPCD
                ScalerDpAuxRx0SetDpcdWildCardIntEnable(_AUX_RX_CABLE_ID_UPDATE, _DISABLE);
#endif
            }
#else
            // Pull-up Config1
            PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1(_D0_CABLEID_DET_CONFIG1_HIGH);

            // Delay For Cable ID Detect Config 1 Pull High
            DELAY_XUS(_PINSHARE_DP_UHBR_CABLE_ID_DETECT_STABLE_DELAY_TIME);

            // Get SARADC Value
            enumDpCableIDResult = ScalerMcuSarAdcDpCableIdDetect(enumInputPort);

            // Pull-down Config1
            PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1(_D0_CABLEID_DET_CONFIG1_LOW);

            // Update DPCD Cable Status
            switch(enumDpCableIDResult)
            {
                case _DP_CABLE_ID_RESULT_MID:

                    // UHBR10-capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), _DP_CABLE_UHBR10_CAPABLE);

                    break;

                case _DP_CABLE_ID_RESULT_HIGH:

                    // UHBR20-capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), (_DP_CABLE_UHBR135_CAPABLE | _DP_CABLE_UHBR20_AND_UHBR10_CAPABLE));

                    break;

                case _DP_CABLE_ID_RESULT_LOW:
                default:

                    // Non-UHBR capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), _DP_CABLE_NON_UHBR_CAPABLE);

                    break;
            }
#endif
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

            // Get Cable Infor from typeC
            stTypeCCableInfoForDpcd = ScalerTypeCRxGetCableInfoForDpcd(enumInputPort);

            if(stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate == _PD_CBL_MAX_DP_RATE_UNCONFIRMED)
            {
                // Not Vconn Source or didn't receive DP Config
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x22, 0x17, 0x00);

#if((_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF) && (_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON))
                // Enable Int to update DPCD
                ScalerDpAuxRx1SetDpcdWildCardIntEnable(_AUX_RX_CABLE_ID_UPDATE, _ENABLE);
#endif
            }
            else
            {
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x22, 0x17, ScalerDpRxCableIdCtoDpMapping(stTypeCCableInfoForDpcd));

#if((_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF) && (_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON))
                // Disable Int to update DPCD
                ScalerDpAuxRx1SetDpcdWildCardIntEnable(_AUX_RX_CABLE_ID_UPDATE, _DISABLE);
#endif
            }
#else
            // Pull-up Config1
            PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1(_D1_CABLEID_DET_CONFIG1_HIGH);

            // Delay For Cable ID Detect Config 1 Pull High
            DELAY_XUS(_PINSHARE_DP_UHBR_CABLE_ID_DETECT_STABLE_DELAY_TIME);

            // Get SARADC Value
            enumDpCableIDResult = ScalerMcuSarAdcDpCableIdDetect(enumInputPort);

            // Pull-down Config1
            PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1(_D1_CABLEID_DET_CONFIG1_LOW);

            // Update DPCD Cable Status
            switch(enumDpCableIDResult)
            {
                case _DP_CABLE_ID_RESULT_MID:

                    // UHBR10-capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), _DP_CABLE_UHBR10_CAPABLE);

                    break;

                case _DP_CABLE_ID_RESULT_HIGH:

                    // UHBR20-capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), (_DP_CABLE_UHBR135_CAPABLE | _DP_CABLE_UHBR20_AND_UHBR10_CAPABLE));

                    break;

                case _DP_CABLE_ID_RESULT_LOW:
                default:

                    // Non-UHBR capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), _DP_CABLE_NON_UHBR_CAPABLE);

                    break;
            }
#endif
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

            // Get Cable Infor from typeC
            stTypeCCableInfoForDpcd = ScalerTypeCRxGetCableInfoForDpcd(enumInputPort);

            if(stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate == _PD_CBL_MAX_DP_RATE_UNCONFIRMED)
            {
                // Not Vconn Source or didn't receive DP Config
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x22, 0x17, 0x00);

#if((_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF) && (_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON))
                // Enable Int to update DPCD
                ScalerDpAuxRx2SetDpcdWildCardIntEnable(_AUX_RX_CABLE_ID_UPDATE, _ENABLE);
#endif
            }
            else
            {
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x22, 0x17, ScalerDpRxCableIdCtoDpMapping(stTypeCCableInfoForDpcd));

#if((_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF) && (_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON))
                // Disable Int to update DPCD
                ScalerDpAuxRx2SetDpcdWildCardIntEnable(_AUX_RX_CABLE_ID_UPDATE, _DISABLE);
#endif
            }
#else
            // Pull-up Config1
            PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1(_D2_CABLEID_DET_CONFIG1_HIGH);

            // Delay For Cable ID Detect Config 1 Pull High
            DELAY_XUS(_PINSHARE_DP_UHBR_CABLE_ID_DETECT_STABLE_DELAY_TIME);

            // Get SARADC Value
            enumDpCableIDResult = ScalerMcuSarAdcDpCableIdDetect(enumInputPort);

            // Pull-down Config1
            PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1(_D2_CABLEID_DET_CONFIG1_LOW);

            // Update DPCD Cable Status
            switch(enumDpCableIDResult)
            {
                case _DP_CABLE_ID_RESULT_MID:

                    // UHBR10-capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), _DP_CABLE_UHBR10_CAPABLE);

                    break;

                case _DP_CABLE_ID_RESULT_HIGH:

                    // UHBR20-capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), (_DP_CABLE_UHBR135_CAPABLE | _DP_CABLE_UHBR20_AND_UHBR10_CAPABLE));

                    break;

                case _DP_CABLE_ID_RESULT_LOW:
                default:

                    // Non-UHBR capable
                    ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x22, 0x17, ~(_BIT2 | _BIT1 | _BIT0), _DP_CABLE_NON_UHBR_CAPABLE);

                    break;
            }
#endif
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : DP Port HotPlug Status
// Input Value  : enumInputPort
// Output Value : _HIGH / _LOW
//--------------------------------------------------
bit ScalerDpRxGetHotPlugStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return g_stDpRxHpdStatus.b1D0Status;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return g_stDpRxHpdStatus.b1D1Status;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return g_stDpRxHpdStatus.b1D2Status;
#endif

        default:
            break;
    }

    return _LOW;
}

//--------------------------------------------------
// Description  : Set Dp Rx HPD
// Input Value  : EnumInputPort, _HIGH / _LOW
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetHotPlug(EnumInputPort enumInputPort, bit bHighLow, WORD usLongHpdDuration)
{
    usLongHpdDuration = usLongHpdDuration;

    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            DebugMessageRx0("Set DP Rx0 HPD:", bHighLow);

#if((_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))

            if(ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(_D0_INPUT_PORT)) != _EMB_TYPE_C_NOT_EXIST)
            {
                ScalerTypeCPdPushHpd(_D0_INPUT_PORT, bHighLow ? _PD_HPD_HIGH : _PD_HPD_LOW, usLongHpdDuration);
            }
            else
#elif((_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM))

            if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
            {
                ScalerTypeCTcpmPdPushHpd(_D0_TYPE_C_PORT, bHighLow ? _PD_HPD_HIGH : _PD_HPD_LOW, usLongHpdDuration);
            }
            else
#endif
            {
                // Aux Reset Process
                ScalerDpAuxRxHpdTogglePhyResetProc(_D0_INPUT_PORT, bHighLow);

                PCB_D0_HOTPLUG(bHighLow ? _D0_HOT_PLUG_HIGH : _D0_HOT_PLUG_LOW);
            }

            g_stDpRxHpdStatus.b1D0Status = bHighLow;

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            DebugMessageRx1("Set DP Rx1 HPD:", bHighLow);

#if((_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))

            if(ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(_D1_INPUT_PORT)) != _EMB_TYPE_C_NOT_EXIST)
            {
                ScalerTypeCPdPushHpd(_D1_INPUT_PORT, bHighLow ? _PD_HPD_HIGH : _PD_HPD_LOW, usLongHpdDuration);
            }
            else
#elif((_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM))

            if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
            {
                ScalerTypeCTcpmPdPushHpd(_D1_TYPE_C_PORT, bHighLow ? _PD_HPD_HIGH : _PD_HPD_LOW, usLongHpdDuration);
            }
            else
#endif
            {
                // Aux Reset Process
                ScalerDpAuxRxHpdTogglePhyResetProc(_D1_INPUT_PORT, bHighLow);

                PCB_D1_HOTPLUG(bHighLow ? _D1_HOT_PLUG_HIGH : _D1_HOT_PLUG_LOW);
            }

            g_stDpRxHpdStatus.b1D1Status = bHighLow;

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            DebugMessageRx2("Set DP Rx2 HPD:", bHighLow);

#if((_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))

            if(ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(_D2_INPUT_PORT)) != _EMB_TYPE_C_NOT_EXIST)
            {
                ScalerTypeCPdPushHpd(_D2_INPUT_PORT, bHighLow ? _PD_HPD_HIGH : _PD_HPD_LOW, usLongHpdDuration);
            }
            else
#elif((_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM))

            if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
            {
                ScalerTypeCTcpmPdPushHpd(_D2_TYPE_C_PORT, bHighLow ? _PD_HPD_HIGH : _PD_HPD_LOW, usLongHpdDuration);
            }
            else
#endif
            {
                // Aux Reset Process
                ScalerDpAuxRxHpdTogglePhyResetProc(_D2_INPUT_PORT, bHighLow);

                PCB_D2_HOTPLUG(bHighLow ? _D2_HOT_PLUG_HIGH : _D2_HOT_PLUG_LOW);
            }

            g_stDpRxHpdStatus.b1D2Status = bHighLow;

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Port HotPlug Pin Detection
// Input Value  : enumInputPort
// Output Value : _HIGH / _LOW
//--------------------------------------------------
bit ScalerDpRxGetHotPlugPinDetect(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return (PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH);
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH);
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return (PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH);
#endif

        default:
            break;
    }

    return _LOW;
}

//--------------------------------------------------
// Description  : Get DP Power Status (DPCD 00600h)
// Input Value  : DP Input Port
// Output Value : DP Power Status
//--------------------------------------------------
EnumDpPowerState ScalerDpRxGetPowerStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)))
    {
        case _BIT0:

            return _DP_POWER_NORMAL;

        case _BIT1:

            return _DP_POWER_DOWN;

        case (_BIT2 | _BIT0):

            return _DP_POWER_DOWN_WITH_AUX;

        default:

            break;
    }

    return _DP_POWER_NORMAL;
}

//--------------------------------------------------
// Description  : DP Rx Main Port Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMainPortInitial(EnumInputPort enumInputPort)
{
#if(_DP_TX_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
    // Set Daisy InputPort Mux
    ScalerDpMstTxSetDaisyInputPortMux(enumInputPort);
#endif

    ScalerSyncDpTxHdcpUpstreamSwitchProc(enumInputPort);
#endif

    SET_DP_RX_MAIN_PORT(enumInputPort);

    DebugMessageDpRx("DP Main Port Initial", enumInputPort);
}

//--------------------------------------------------
// Description  : DP Rx Main Port Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMainPortSwitch(EnumInputPort enumInputPort)
{
#if(_DP_MST_SUPPORT == _ON)
    ScalerDpMstRxMainPortSwitchProc(enumInputPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
    ScalerSyncDpTxHdcpUpstreamSwitchProc(enumInputPort);

    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        SET_DP_MAC_TX_DOWNSTREAM_SINK_COUNT_CHANGE();
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    SET_DP_MAC_TX_MAIN_PORT_CHANGE();
#endif
#endif

    SET_DP_RX_MAIN_PORT(enumInputPort);

    DebugMessageDpRx("DP Main Port Swtich", enumInputPort);
}

//--------------------------------------------------
// Description  : Get DP Main Port
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDpRxGetMainPort(void)
{
    return ((GET_DP_RX_MAIN_PORT() < _NO_INPUT_PORT) ? GET_DP_RX_MAIN_PORT() : _NO_INPUT_PORT);
}

//--------------------------------------------------
// Description  : DP Rx Stream Info Setting
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxStreamExternInfoSetting(EnumInputPort enumInputPort)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxDxMacSourceMapping(enumInputPort);

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerDrrFreeSyncDpSetEnable(enumInputPort, ScalerDpMacStreamRxGetFreeSyncEnable(enumDpMacStreamSourceType));
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    ScalerDpRxPRModeSetEnable(enumInputPort, ScalerDpMacStreamRxGetPRModeEnable(enumDpMacStreamSourceType));
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpRxAuxlessAlpmSetEnable(enumInputPort, ScalerDpMacStreamRxGetAuxlessAlpmEnable(enumDpMacStreamSourceType));
#endif

    // Recoed Input Pixel Clock For Format Conversion (Unit is 0.1MHz)
    ScalerDpRxSetInputPixelClock(enumInputPort, ScalerDpMacStreamRxGetPredectStreamClock(enumDpMacStreamSourceType));

    // Record Native Input Pixel Clock (Unit is 0.1MHz) For Lut and OSD Pixel Clock Info
    ScalerDpRxSetNativeInputPixelClock(enumInputPort, ScalerDpMacStreamRxGetNativePixelClock(enumDpMacStreamSourceType));

    SET_CONTENT_TYPE(enumInputPort, ScalerDpMacStreamRxGetContentType(enumDpMacStreamSourceType));

    // Set Intput Port Color Space Macro
    SET_COLOR_SPACE(enumInputPort, ScalerDpMacStreamRxGetColorSpace(enumDpMacStreamSourceType));

    SET_COLOR_DEPTH(enumInputPort, ScalerDpMacStreamRxGetColorDepth(enumDpMacStreamSourceType));
}

//--------------------------------------------------
// Description  : DP Rx Stream Info Setting
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxStreamAfterJudgeSetting(EnumInputPort enumInputPort)
{
#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
    ScalerDpMacStreamRxSetBsMissDetectPeriod(enumInputPort);
#endif

    // Clear Bs Miss Flag Before Stable Detect
    ScalerDpMacStreamRxBsMissFlagClear(enumInputPort);

    ScalerDpMacStreamRxSinkStatusSetting(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Rx Stream Colorimetry Info Setting
// Input Value  : enumDpMacStreamSourceType
// Output Value : None
//--------------------------------------------------
void ScalerDpRxStreamColorimetryInfoSetting(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = ScalerDpRxGetInputPortMappingSourceType(enumDpMacStreamSourceType);

    if(enumInputPort != _NO_INPUT_PORT)
    {
#if(_DP_MST2SST_SUPPORT == _ON)
        if(enumDpMacStreamSourceType != _STREAM_SOURCE_MST2SST)
#endif
        {
            SET_COLORIMETRY(enumInputPort, ScalerDpMacStreamRxGetColorimetry(enumDpMacStreamSourceType));
        }
    }
}

//--------------------------------------------------
// Description  : DP Rx Stream Colorimetry Ext Info Setting
// Input Value  : enumDpMacStreamSourceType
// Output Value : None
//--------------------------------------------------
void ScalerDpRxStreamColorimetryExtInfoSetting(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = ScalerDpRxGetInputPortMappingSourceType(enumDpMacStreamSourceType);

    if(enumInputPort != _NO_INPUT_PORT)
    {
#if(_DP_MST2SST_SUPPORT == _ON)
        if(enumDpMacStreamSourceType != _STREAM_SOURCE_MST2SST)
#endif
        {
            SET_EXT_COLORIMETRY(enumInputPort, ScalerDpMacStreamRxGetExtColorimetry(enumDpMacStreamSourceType));
        }
    }
}

//--------------------------------------------------
// Description  : DP Rx Stream Quantization Info Setting
// Input Value  : enumDpMacStreamSourceType
// Output Value : None
//--------------------------------------------------
void ScalerDpRxStreamQuantizationInfoSetting(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = ScalerDpRxGetInputPortMappingSourceType(enumDpMacStreamSourceType);

    if(enumInputPort != _NO_INPUT_PORT)
    {
#if(_DP_MST2SST_SUPPORT == _ON)
        if(enumDpMacStreamSourceType != _STREAM_SOURCE_MST2SST)
#endif
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(enumInputPort, ScalerDpMacStreamRxGetYCCQuantizationRange(enumDpMacStreamSourceType));
            SET_COLOR_RGB_QUANTIZATION_RANGE(enumInputPort, ScalerDpMacStreamRxGetRGBQuantizationRange(enumDpMacStreamSourceType));
        }
    }
}

//--------------------------------------------------
// Description  : Initial Setting for DP GPIO Port
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxConfigPinInitial(EnumInputPort enumInputPort)
{
    // TypeC Config1/2 connect to ground (1Mohm)
    // Normal DP but support 128B132B:
    // ----(1). Config1/2 shall be set to low (Default High)
    // ----(2). Config2 will be set to ADC# type to detect voltage
    // Normal DP and not support 128B132B:
    // ----(1). Config1/2 shall be pull down to ground (No PP GPIO)
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if((_D0_TYPE_C_PORT_CTRL_SUPPORT == _PORT_CTRL_NONE) && (_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1(_D0_CABLEID_DET_CONFIG1_LOW);
#endif
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if((_D1_TYPE_C_PORT_CTRL_SUPPORT == _PORT_CTRL_NONE) && (_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1(_D1_CABLEID_DET_CONFIG1_LOW);
#endif
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if((_D2_TYPE_C_PORT_CTRL_SUPPORT == _PORT_CTRL_NONE) && (_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1(_D2_CABLEID_DET_CONFIG1_LOW);
#endif
            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:

#if((_D0_TYPE_C_PORT_CTRL_SUPPORT == _PORT_CTRL_NONE) && (_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1(_D0_CABLEID_DET_CONFIG1_LOW);
#endif

#if((_D1_TYPE_C_PORT_CTRL_SUPPORT == _PORT_CTRL_NONE) && (_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1(_D1_CABLEID_DET_CONFIG1_LOW);
#endif
            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:

#if((_D1_TYPE_C_PORT_CTRL_SUPPORT == _PORT_CTRL_NONE) && (_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1(_D1_CABLEID_DET_CONFIG1_LOW);
#endif

#if((_D2_TYPE_C_PORT_CTRL_SUPPORT == _PORT_CTRL_NONE) && (_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1(_D2_CABLEID_DET_CONFIG1_LOW);
#endif
            break;
#endif

        default:
            break;
    }
}

#if(_HW_DP_MAC_DPHY_CTS_FIFO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Dx Cts Fifo Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMacDphyCtsFifoReset(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            ScalerSetBit(P6F_05_CTS_FIFO_D0D1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT6);
            ScalerSetBit(P6F_05_CTS_FIFO_D0D1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            ScalerSetBit(P6F_05_CTS_FIFO_D0D1, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(P6F_05_CTS_FIFO_D0D1, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            ScalerSetBit(P6F_06_CTS_FIFO_D2, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(P6F_06_CTS_FIFO_D2, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get DP Connector Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRxGetConnectorType(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
            return _D0_DP_CONNECTOR_TYPE;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            return _D1_DP_CONNECTOR_TYPE;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:
            return _D2_DP_CONNECTOR_TYPE;
#endif

        default:
            break;
    }

    return _DP_CONNECTOR_NORMAL;
}

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
//--------------------------------------------------
// Description  : Irq Assert Timer2 Event Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------

void ScalerDpRxHpdIrqAssertTimer2EventProc_T2INT(void)
{
    //=======================================================
    // 1. HPD High Process
    //=======================================================

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    if(g_ucTimerQuarterCount == 0)
#endif
    {
#if(_D0_DP_SUPPORT == _ON)
        if(GET_DP_AUX_RX0_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_LOW)
            {
                PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);

                CLR_DP_AUX_RX0_HPD_IRQ_ASSERT_T2_EVENT();
            }
        }
#endif

#if(_D1_DP_SUPPORT == _ON)
        if(GET_DP_AUX_RX1_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_LOW)
            {
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

                CLR_DP_AUX_RX1_HPD_IRQ_ASSERT_T2_EVENT();
            }
        }
#endif

#if(_D2_DP_SUPPORT == _ON)
        if(GET_DP_AUX_RX2_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_LOW)
            {
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);

                CLR_DP_AUX_RX2_HPD_IRQ_ASSERT_T2_EVENT();
            }
        }
#endif
    }

    //=======================================================
    // 2. HPD Low Process
    //=======================================================

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    if(g_ucTimerQuarterCount == 1)
#endif
    {
#if(_D0_DP_SUPPORT == _ON)
        if(GET_DP_AUX_RX0_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
            {
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)
                DP_RX_HPD_IRQ_ASSERT_T2_DELAY();
#endif

                PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
            }
        }
#endif

#if(_D1_DP_SUPPORT == _ON)
        if(GET_DP_AUX_RX1_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
            {
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)
                DP_RX_HPD_IRQ_ASSERT_T2_DELAY();
#endif

                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
            }
        }
#endif

#if(_D2_DP_SUPPORT == _ON)
        if(GET_DP_AUX_RX2_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH)
            {
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)
                DP_RX_HPD_IRQ_ASSERT_T2_DELAY();
#endif

                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
            }
        }
#endif
    }
}

#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx Port1 Dsc Dec Support Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstToSstDscCapSwitchProc(void)
{
    if(GET_DP_RX_MAIN_PORT() == _NO_INPUT_PORT)
    {
        ScalerDscDecoderSetMstToSstCapSwitch(_DISABLE);

        return;
    }

    if(ScalerDscDecoderGetMstToSstCapSwitch() == _ENABLE)
    {
        ScalerDscDecoderSetMstToSstCapSwitch(_DISABLE);

        ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_UNPLUG);
        ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_PLUG);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        ScalerDpMstRxVirtualDpInitial(GET_DP_RX_MAIN_PORT(), ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT));
#endif
    }
}
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Cancel PPS Timeout Event
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxDscCancelPpsTimerEvent(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX0_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX1_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX2_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX3_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX4_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

        default:
            break;
    }
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx Sink count Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSinkCountUpdateProc(void)
{
    EnumInputPort enumInputPort = _D0_INPUT_PORT;

    if(GET_DP_MAC_TX_DOWNSTREAM_SINK_COUNT_CHANGE() == _TRUE)
    {
        CLR_DP_MAC_TX_DOWNSTREAM_SINK_COUNT_CHANGE();

        for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
        {
            if(ScalerSyncGetPortType(enumInputPort) != _PORT_DP)
            {
                continue;
            }

#if(_DP_DPCD_DFP_PRESENT_REF_TO == _DP_MST_CAPABILITY)
            if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
            {
                continue;
            }
#endif
            if(ScalerDpRxGetSrcMstUpRequestEnable(enumInputPort) == _FALSE)
            {
                if(enumInputPort == GET_DP_RX_MAIN_PORT())
                {
                    ScalerDpAuxRxSinkCountUpdate(enumInputPort, (GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT() + 1), _TRUE);
                }
                else
                {
                    ScalerDpAuxRxSinkCountUpdate(enumInputPort, 1, _TRUE);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Set DP Rx DPCD DFP Detail Cap Reset
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRxDfpDeviceDetailConfigReset(EnumInputPort enumInputPort)
{
    BYTE ucDpcdIndex = 0;

    ScalerDpAuxRxSetDpcdMirrorBitValue(enumInputPort, 0x00, 0x00, 0x07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    for(ucDpcdIndex = 0; ucDpcdIndex <= 3; ucDpcdIndex++)
    {
        // DPCD [0x00080 ~ 0x00083]
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, (0x80 + ucDpcdIndex), 0x00);
    }
}

//--------------------------------------------------
// Description  : Set DP Rx DPCD DFP Detail Set
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRxDfpDeviceDetailConfig(EnumInputPort enumInputPort)
{
    ScalerDpAuxRxSetDpcdMirrorBitValue(enumInputPort, 0x00, 0x00, 0x07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

    // DP Type
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x80, (_BIT6 | _BIT4 | _BIT3));

    // Pixel Rate
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x81, 0x00);

    // Depth Color
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x82, 0x00);

    // Misc, This Field set for HDMI DFP, for DP DFP, YCBCR 422/420 or YCBCR 444to422 or YCBCR 444to420 support should be Not support
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x83, 0x00);
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx HDCP Auth Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpRxHdcpHandler(void)
{
    ScalerDpRxHdcpResetUpstreamEventProc();

#if(_D0_DP_SUPPORT == _ON)
    ScalerDpHdcp14Rx0RepeaterHandler();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpHdcp2Rx0RepeaterHandler();
#endif
#endif

#if(_D1_DP_SUPPORT == _ON)
    ScalerDpHdcp14Rx1RepeaterHandler();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpHdcp2Rx1RepeaterHandler();
#endif
#endif

#if(_D2_DP_SUPPORT == _ON)
    ScalerDpHdcp14Rx2RepeaterHandler();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpHdcp2Rx2RepeaterHandler();
#endif
#endif

    ScalerDpHdcp14TxHandler();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpHdcp2TxHandler();
#endif
}

//--------------------------------------------------
// Description  : Dp Rx HDCP Auth Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpRxHdcpResetUpstreamEventProc(void)
{
#if(_D0_DP_SUPPORT == _ON)
    CLR_DP_HDCP14_RX0_UPSTREAM_EVENT();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    CLR_DP_HDCP2_RX0_UPSTREAM_EVENT();
#endif
#endif

#if(_D1_DP_SUPPORT == _ON)
    CLR_DP_HDCP14_RX1_UPSTREAM_EVENT();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    CLR_DP_HDCP2_RX1_UPSTREAM_EVENT();
#endif
#endif

#if(_D2_DP_SUPPORT == _ON)
    CLR_DP_HDCP14_RX2_UPSTREAM_EVENT();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    CLR_DP_HDCP2_RX2_UPSTREAM_EVENT();
#endif
#endif
}
#endif

//--------------------------------------------------
// Description  : User Target Dx Link Rate mapping to Rx Link Rate
// Input Value  : Input Port
// Output Value : EnumDpLinkRate
//--------------------------------------------------
EnumDpLinkRate ScalerDpRxGetTargetMaxLinkRate(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return GET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE();
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE();
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE();
#endif
        default:
            return _DP_LINK_SPEED_NONE;
    }
}

//--------------------------------------------------
// Description  : Get Msg RX Base Address of Input Port
// Input Value  : enumOutputPort
// Output Value : WORD
//--------------------------------------------------
void ScalerDpRxSetBaseInputPort(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        if(GET_DP_MST_RX_PXP_INPUT_PORT() != _NO_INPUT_PORT)
        {
            enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
        }
    }
#endif

    if(enumInputPort == GET_DP_RX_BASE_PORT())
    {
        return;
    }

    SET_DP_RX_BASE_PORT(enumInputPort);

    ScalerDpAuxRxSetBase32AddressOffset(enumInputPort);
}

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
//--------------------------------------------------
// Description  : Switch DP Hdr Support
// Input Value  : enumInputPort, enumHDR10ModeDef
// Output Value : None
//--------------------------------------------------
void ScalerDpRxHdrSupportSwitch(EnumInputPort enumInputPort, EnumDpHdrSupport enumDpHdrSupport)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(ScalerDpRxHdrGetSupport(_D0_INPUT_PORT) != enumDpHdrSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_HDR_D0_CAPABILITY_SWITCH();

                if(enumDpHdrSupport == _DP_HDR_SUPPORT_ON)
                {
                    SET_DP_HDR_D0_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_HDR_D0_SUPPORT(_OFF);
                }
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(ScalerDpRxHdrGetSupport(_D1_INPUT_PORT) != enumDpHdrSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_HDR_D1_CAPABILITY_SWITCH();

                if(enumDpHdrSupport == _DP_HDR_SUPPORT_ON)
                {
                    SET_DP_HDR_D1_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_HDR_D1_SUPPORT(_OFF);
                }
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(ScalerDpRxHdrGetSupport(_D2_INPUT_PORT) != enumDpHdrSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_HDR_D2_CAPABILITY_SWITCH();

                if(enumDpHdrSupport == _DP_HDR_SUPPORT_ON)
                {
                    SET_DP_HDR_D2_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_HDR_D2_SUPPORT(_OFF);
                }
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Port Hdr Support
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
EnumDpHdrSupport ScalerDpRxHdrGetSupport(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_DP_HDR_D0_SUPPORT() == _ON)
            {
                return _DP_HDR_SUPPORT_ON;
            }
            else
            {
                return _DP_HDR_SUPPORT_OFF;
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_DP_HDR_D1_SUPPORT() == _ON)
            {
                return _DP_HDR_SUPPORT_ON;
            }
            else
            {
                return _DP_HDR_SUPPORT_OFF;
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_DP_HDR_D2_SUPPORT() == _ON)
            {
                return _DP_HDR_SUPPORT_ON;
            }
            else
            {
                return _DP_HDR_SUPPORT_OFF;
            }

            break;
#endif
        default:
            break;
    }

    return _DP_HDR_SUPPORT_OFF;
}

//--------------------------------------------------
// Description  : Dp Hdr Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRxHdrCapabilitySwitchProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_DP_HDR_D0_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_HDR_D0_CAPABILITY_SWITCH();

                ScalerDpAuxRxHdrDpcdSetting(_D0_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_DP_HDR_D1_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_HDR_D1_CAPABILITY_SWITCH();

                ScalerDpAuxRxHdrDpcdSetting(_D1_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_DP_HDR_D2_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_HDR_D2_CAPABILITY_SWITCH();

                ScalerDpAuxRxHdrDpcdSetting(_D2_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}
#endif
#endif

#if(_DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Long HPD Set Allowed or Not
// Input Value  : ucInputPort, bAllowed = _TRUE/_FALSE
// Output Value : None
//--------------------------------------------------
void ScalerDpRxLongHpdSetAllowed(EnumInputPort enumInputPort, bit bAllowed)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
        case _D0_INPUT_PORT:

            g_bDpRx0LongHpdAllowed = bAllowed;

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            g_bDpRx1LongHpdAllowed = bAllowed;

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            g_bDpRx2LongHpdAllowed = bAllowed;

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Long HPD Get Allowed
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpRxLongHpdGetAllowed(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            return g_bDpRx0LongHpdAllowed;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return g_bDpRx1LongHpdAllowed;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            return g_bDpRx2LongHpdAllowed;
#endif

        default:
            return _TRUE;
    }
}
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch DP PR Mode Support
// Input Value  : Hotplug Type and PR Mode Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerDpRxPRModeSupportSwitch(EnumInputPort enumInputPort, EnumDpPRModeSupport enumSupport)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(ScalerDpRxPRModeGetSupport(_D0_INPUT_PORT) != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_PR_MODE_D0_CAPABILITY_SWITCH();

                if(enumSupport == _DP_PR_MODE_SUPPORT_ON)
                {
                    SET_DP_PR_MODE_D0_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_PR_MODE_D0_SUPPORT(_OFF);
                }
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(ScalerDpRxPRModeGetSupport(_D1_INPUT_PORT) != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_PR_MODE_D1_CAPABILITY_SWITCH();

                if(enumSupport == _DP_PR_MODE_SUPPORT_ON)
                {
                    SET_DP_PR_MODE_D1_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_PR_MODE_D1_SUPPORT(_OFF);
                }
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(ScalerDpRxPRModeGetSupport(_D2_INPUT_PORT) != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_PR_MODE_D2_CAPABILITY_SWITCH();

                if(enumSupport == _DP_PR_MODE_SUPPORT_ON)
                {
                    SET_DP_PR_MODE_D2_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_PR_MODE_D2_SUPPORT(_OFF);
                }
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Port PR Mode Support
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
EnumDpPRModeSupport ScalerDpRxPRModeGetSupport(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_DP_PR_MODE_D0_SUPPORT() == _ON)
            {
                return _DP_PR_MODE_SUPPORT_ON;
            }
            else
            {
                return _DP_PR_MODE_SUPPORT_OFF;
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_DP_PR_MODE_D1_SUPPORT() == _ON)
            {
                return _DP_PR_MODE_SUPPORT_ON;
            }
            else
            {
                return _DP_PR_MODE_SUPPORT_OFF;
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_DP_PR_MODE_D2_SUPPORT() == _ON)
            {
                return _DP_PR_MODE_SUPPORT_ON;
            }
            else
            {
                return _DP_PR_MODE_SUPPORT_OFF;
            }

            break;
#endif
        default:
            break;
    }

    return _DP_PR_MODE_SUPPORT_OFF;
}

//--------------------------------------------------
// Description  : Dp PR Mode Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRxPRModepCapabilitySwitchProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_DP_PR_MODE_D0_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_PR_MODE_D0_CAPABILITY_SWITCH();

                ScalerDpAuxRxPRModeDpcdSetting(_D0_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_DP_PR_MODE_D1_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_PR_MODE_D1_CAPABILITY_SWITCH();

                ScalerDpAuxRxPRModeDpcdSetting(_D1_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_DP_PR_MODE_D2_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_PR_MODE_D2_CAPABILITY_SWITCH();

                ScalerDpAuxRxPRModeDpcdSetting(_D2_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP PR Enable
// Input Value  : enumInputPort Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpRxPRModeSetEnable(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_DP_PR_MODE_D0_ENABLE();
            }
            else
            {
                CLR_DP_PR_MODE_D0_ENABLE();
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_DP_PR_MODE_D1_ENABLE();
            }
            else
            {
                CLR_DP_PR_MODE_D1_ENABLE();
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_DP_PR_MODE_D2_ENABLE();
            }
            else
            {
                CLR_DP_PR_MODE_D2_ENABLE();
            }

            break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_DP_PR_MODE_D9_ENABLE();
            }
            else
            {
                CLR_DP_PR_MODE_D9_ENABLE();
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP PR Enable
// Input Value  : enumInputPort
// Output Value : Enable/Disable
//--------------------------------------------------
bit ScalerDpRxPRModeGetEnable(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_DP_PR_MODE_D0_ENABLE();

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_DP_PR_MODE_D1_ENABLE();

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_DP_PR_MODE_D2_ENABLE();

            break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            return GET_DP_PR_MODE_D9_ENABLE();

            break;
#endif

        default:
            break;
    }
    return _FALSE;
}

#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch DP Auxless APLM Support
// Input Value  : enumInputPort and enumSupport
// Output Value : None
//--------------------------------------------------
void ScalerDpRxAuxlessAlpmSupportSwitch(EnumInputPort enumInputPort, EnumDpAuxlessAlpmSupport enumSupport)
{
    switch(enumInputPort)
    {
#if(_D0_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(ScalerDpRxAuxlessAlpmGetSupport(_D0_INPUT_PORT) != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_AUXLESS_ALPM_D0_CAPABILITY_SWITCH();

                if(enumSupport == _DP_AUXLESS_ALPM_SUPPORT_ON)
                {
                    SET_DP_AUXLESS_ALPM_D0_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_AUXLESS_ALPM_D0_SUPPORT(_OFF);
                }
            }

            break;
#endif

#if(_D1_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(ScalerDpRxAuxlessAlpmGetSupport(_D1_INPUT_PORT) != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_AUXLESS_ALPM_D1_CAPABILITY_SWITCH();

                if(enumSupport == _DP_AUXLESS_ALPM_SUPPORT_ON)
                {
                    SET_DP_AUXLESS_ALPM_D1_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_AUXLESS_ALPM_D1_SUPPORT(_OFF);
                }
            }

            break;
#endif

#if(_D2_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(ScalerDpRxAuxlessAlpmGetSupport(_D2_INPUT_PORT) != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_AUXLESS_ALPM_D2_CAPABILITY_SWITCH();

                if(enumSupport == _DP_AUXLESS_ALPM_SUPPORT_ON)
                {
                    SET_DP_AUXLESS_ALPM_D2_SUPPORT(_ON);
                }
                else
                {
                    SET_DP_AUXLESS_ALPM_D2_SUPPORT(_OFF);
                }
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Port Auxless ALPM Support
// Input Value  : enumInputPort
// Output Value : enumDpAuxlessAlpmSupport
//--------------------------------------------------
EnumDpAuxlessAlpmSupport ScalerDpRxAuxlessAlpmGetSupport(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return ((GET_DP_AUXLESS_ALPM_D0_SUPPORT() == _ON) ? _DP_AUXLESS_ALPM_SUPPORT_ON : _DP_AUXLESS_ALPM_SUPPORT_OFF);
#endif

#if(_D1_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return ((GET_DP_AUXLESS_ALPM_D1_SUPPORT() == _ON) ? _DP_AUXLESS_ALPM_SUPPORT_ON : _DP_AUXLESS_ALPM_SUPPORT_OFF);
#endif

#if(_D2_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return ((GET_DP_AUXLESS_ALPM_D2_SUPPORT() == _ON) ? _DP_AUXLESS_ALPM_SUPPORT_ON : _DP_AUXLESS_ALPM_SUPPORT_OFF);
#endif
        default:
            return _DP_AUXLESS_ALPM_SUPPORT_OFF;
    }
}

//--------------------------------------------------
// Description  : Dp Auxless ALPM Capability Switch
// Input Value  : enumInputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRxAuxlessAlpmCapabilitySwitchProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_DP_AUXLESS_ALPM_D0_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_AUXLESS_ALPM_D0_CAPABILITY_SWITCH();

                ScalerDpAuxRxAuxlessAlpmDpcdSetting(_D0_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

#if(_D1_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_DP_AUXLESS_ALPM_D1_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_AUXLESS_ALPM_D1_CAPABILITY_SWITCH();

                ScalerDpAuxRxAuxlessAlpmDpcdSetting(_D1_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

#if(_D2_DP_AUXLESS_ALPM_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_DP_AUXLESS_ALPM_D2_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_AUXLESS_ALPM_D2_CAPABILITY_SWITCH();

                ScalerDpAuxRxAuxlessAlpmDpcdSetting(_D2_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP Aux Less Alpm Enable
// Input Value  : enumInputPort Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpRxAuxlessAlpmSetEnable(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_DP_AUXLESS_ALPM_D0_ENABLE();
            }
            else
            {
                CLR_DP_AUXLESS_ALPM_D0_ENABLE();
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_DP_AUXLESS_ALPM_D1_ENABLE();
            }
            else
            {
                CLR_DP_AUXLESS_ALPM_D1_ENABLE();
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_DP_AUXLESS_ALPM_D2_ENABLE();
            }
            else
            {
                CLR_DP_AUXLESS_ALPM_D2_ENABLE();
            }

            break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_DP_AUXLESS_ALPM_D9_ENABLE();
            }
            else
            {
                CLR_DP_AUXLESS_ALPM_D9_ENABLE();
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Aux Less Alpm Enable
// Input Value  : enumInputPort
// Output Value : Enable/Disable
//--------------------------------------------------
bit ScalerDpRxAuxlessAlpmGetEnable(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_DP_AUXLESS_ALPM_D0_ENABLE();

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_DP_AUXLESS_ALPM_D1_ENABLE();

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_DP_AUXLESS_ALPM_D2_ENABLE();

            break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            return GET_DP_AUXLESS_ALPM_D9_ENABLE();

            break;
#endif

        default:
            break;
    }
    return _FALSE;
}
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get DM Support flag
// Input Value  : enumInputPort
// Output Value : InputPort DM Support
//--------------------------------------------------
bit ScalerDpRxGetOsdDmSupport(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_D0_DM_SUPPORT();

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_D1_DM_SUPPORT();

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_D2_DM_SUPPORT();

            break;
#endif
        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Dram Receive From Dm Detect
// Input Value  : enumInputPort
// Output Value : Receive From Dm Detect Flag
//--------------------------------------------------
bit ScalerDpRxGetDramReceiveFromDmDetect(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_DRAM_RECEIVED_FROM_DM_DETECT(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_DRAM_RECEIVED_FROM_DM_DETECT(_D1_INPUT_PORT);

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_DRAM_RECEIVED_FROM_DM_DETECT(_D2_INPUT_PORT);

            break;
#endif
        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Clr Dram Receive From Dm Detect
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxClrDramReceiveFromDmDetect(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            CLR_DRAM_RECEIVED_FROM_DM_DETECT(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            CLR_DRAM_RECEIVED_FROM_DM_DETECT(_D1_INPUT_PORT);

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            CLR_DRAM_RECEIVED_FROM_DM_DETECT(_D2_INPUT_PORT);

            break;
#endif
        default:
            break;
    }
}
#endif
#endif

