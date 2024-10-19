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
// ID Code      : SysDp.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_DP__

#include "SysInclude.h"
#include "Dp/SysDp.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON) || ((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON)))
volatile BYTE g_ucDpRxCtrl;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Switch DP ports
// Input Value  : Current Input Port, Target Source Type, switch status
// Output Value : None
//--------------------------------------------------
void SysDpInterfaceSwitch(EnumInputPort enumInputPort, EnumPortType enumPortType, StructPortSwitchedStatus *pstPortStatus)
{
    enumInputPort = enumInputPort;
    enumPortType = enumPortType;
    pstPortStatus = pstPortStatus;

#if(_DP_SUPPORT == _ON)
#if(_DP_MAC_SWITCH_SUPPORT == _ON)
    SysDpMacUnjudgedMacMappingReset();
#endif

    if(enumPortType == _PORT_DP)
    {
        SysDpMacArbiter(enumInputPort);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
        {
            SysDpRxPxpInputPortSwitch(SysDpGetPxpInputTargetPort());
        }
#endif
    }

    // Set DP fake link-training
#if(_D0_DP_SUPPORT == _ON)
    if(((enumInputPort != _D0_INPUT_PORT) && (pstPortStatus->b1D0 == _FALSE)) ||
       (ScalerDpRxGetMacDphySwitch(_D0_INPUT_PORT) == _DP_MAC_DPHY_NONE))
    {
        ScalerDpAuxRxFakeLTProtect(_D0_INPUT_PORT);
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(((enumInputPort != _D1_INPUT_PORT) && (pstPortStatus->b1D1 == _FALSE)) ||
       (ScalerDpRxGetMacDphySwitch(_D1_INPUT_PORT) == _DP_MAC_DPHY_NONE))
    {
        ScalerDpAuxRxFakeLTProtect(_D1_INPUT_PORT);
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(((enumInputPort != _D2_INPUT_PORT) && (pstPortStatus->b1D2 == _FALSE)) ||
       (ScalerDpRxGetMacDphySwitch(_D2_INPUT_PORT) == _DP_MAC_DPHY_NONE))
    {
        ScalerDpAuxRxFakeLTProtect(_D2_INPUT_PORT);
    }
#endif
#endif // End of #if(_DP_SUPPORT == _ON)
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Ac On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpInitial(void)
{
    SysDpMacArbiterInitial();

    SysDpRxInitial();

    SysDpTxInitial();
}

//--------------------------------------------------
// Description  : DP Ac On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxInitial(void)
{
    BYTE ucIndex = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    UserCommonDpGetAmdAupiPanelInfo();
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    UserCommonDpMstRxPxpModeSwitch(UserInterfaceDpGetPxpMode());
#endif

    for(ucIndex = 0; ucIndex < _DP_PORT_VALID; ucIndex++)
    {
        EnumInputPort enumInputPort = SysDpGetInitialDpPort(ucIndex);

#if(_DUAL_DP_SUPPORT == _ON)
        if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (SysSourceGetInputPort() == _DUAL_DP_INPUT_PORT))
        {
            if((enumInputPort == _DUAL_DP_MAIN_PORT) || (enumInputPort == _DUAL_DP_SUB_PORT))
            {
                enumInputPort = _NO_INPUT_PORT;
            }
        }
        else
        {
            if(enumInputPort == _DUAL_DP_INPUT_PORT)
            {
                enumInputPort = _NO_INPUT_PORT;
            }
        }
#endif

        if(enumInputPort != _NO_INPUT_PORT)
        {
            SysDpGetUserDefineDpInfo(enumInputPort);

            ScalerDpRxInitial(enumInputPort);
        }
    }

    SysDpRxMainPortInitial();

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    SysDpRxPxpPortInitial();
#endif
    ScalerDpMstRxCapabilitySwitchProc();
#endif
}

//--------------------------------------------------
// Description  : DP Ac On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxInitial(void)
{
#if(_DP_TX_SUPPORT == _ON)

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpMacMstToSstSdpInitial();

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMstTx128b132bTo8b10bInitial();
#endif

#endif

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
    ScalerDpMacTxCloneModeSwitch(UserInterfaceDpGetCloneOutputStatus());
#endif

    ScalerDpHdcp14TxPowerOnInitial();
#endif // End of #if(_DP_TX_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Get Dp Port
// Input Value  : Dp Valid Port Num Index
// Output Value : Valid DP InputPort
//--------------------------------------------------
EnumInputPort SysDpGetInitialDpPort(BYTE ucIndex)
{
    // Get Initial Dp Input Port
    EnumDpInputPort enumDpInitialPort = ScalerDpRxGetDpPort(ucIndex);

    switch(enumDpInitialPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _DP_D0_PORT:
            return _D0_INPUT_PORT;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _DP_D1_PORT:
            return _D1_INPUT_PORT;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _DP_D2_PORT:
            return _D2_INPUT_PORT;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _DP_D7_PORT:
            return _D7_INPUT_PORT;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _DP_D8_PORT:
            return _D8_INPUT_PORT;
#endif

        default:
            return _NO_INPUT_PORT;
    }
}

//--------------------------------------------------
// Description  : Get Dp Port
// Input Value  : Dp Valid Port Num Index
// Output Value : Valid DP InputPort
//--------------------------------------------------
void SysDpGetUserDefineDpInfo(EnumInputPort enumInputPort)
{
    EnumDpVersionType enumDpVersion = UserCommonDpGetVersion(enumInputPort);
    EnumDpLinkRate enumDpLinkRate = UserCommonDpGetMaxLinkRate(enumInputPort);
    EnumDpLaneCount enumDpLaneCount = UserInterfaceDpGetLaneCount(enumInputPort);
#if(_AUDIO_SUPPORT == _ON)
    EnumAudioDpDpcdSupport enumDpAudioSupport = UserCommonAudioDpGetCapabilityInitialState(enumInputPort);
#endif // End of #if(_AUDIO_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
    EnumFreeSyncSupport enumDpFreeSyncSupport = UserInterfaceFreeSyncGetEnable(enumInputPort);
#endif
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    EnumDpAdaptiveSyncSupport enumDpAdaptiveSyncSupport = UserInterfaceDpAdaptiveSyncGetEnable(enumInputPort);
#endif
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    EnumDscDecoderSupport enumDpDscDecodeSupport = UserInterfaceDscDecoderGetEnable(enumInputPort);
#endif
#if(_DP_PR_MODE_SUPPORT == _ON)
    EnumDpPRModeSupport enumDpPRModeSupport = UserInterfaceDpPRModeGetEnable(enumInputPort);
#endif
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    EnumDpAuxlessAlpmSupport enumDpAuxlessAlpmSupport = UserInterfaceDpAuxlessAlpmGetEnable(enumInputPort);
#endif
#if(_DP_MST_SUPPORT == _ON)
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    EnumDscDecoderSupport enumDpMst2sstDscDecoderSupport = UserCommonDscDecoderMst2sstGetEnable();
#endif
    EnumDPMSTPort enumDpMstSelectPort = UserCommonDpGetMSTCapablePort();
#endif

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    SET_DSC_DP_MST2SST_BRANCH_SUPPORT(enumDpMst2sstDscDecoderSupport);
#endif
    SET_DP_RX_TARGET_MST_PORT(enumDpMstSelectPort);
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE(enumDpLinkRate);
            SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

#if(_AUDIO_SUPPORT == _ON)
            SET_AUDIO_DP_D0_SUPPORT(enumDpAudioSupport);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            SET_DSC_D0_SUPPORT(enumDpDscDecodeSupport);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
            SET_FREESYNC_DP_D0_SUPPORT(enumDpFreeSyncSupport);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            SET_ADAPTIVESYNC_DP_D0_SUPPORT(enumDpAdaptiveSyncSupport);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
            if(enumDpPRModeSupport == _DP_PR_MODE_SUPPORT_ON)
            {
                SET_DP_PR_MODE_D0_SUPPORT(_ON);
            }
            else
            {
                SET_DP_PR_MODE_D0_SUPPORT(_OFF);
            }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#if(_D0_DP_AUXLESS_ALPM_SUPPORT == _ON)
            if(enumDpAuxlessAlpmSupport == _DP_AUXLESS_ALPM_SUPPORT_ON)
            {
                SET_DP_AUXLESS_ALPM_D0_SUPPORT(_ON);
            }
            else
#endif
            {
                SET_DP_AUXLESS_ALPM_D0_SUPPORT(_OFF);
            }
#endif

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE(enumDpLinkRate);
            SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

#if(_AUDIO_SUPPORT == _ON)
            SET_AUDIO_DP_D1_SUPPORT(enumDpAudioSupport);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            SET_DSC_D1_SUPPORT(enumDpDscDecodeSupport);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
            SET_FREESYNC_DP_D1_SUPPORT(enumDpFreeSyncSupport);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            SET_ADAPTIVESYNC_DP_D1_SUPPORT(enumDpAdaptiveSyncSupport);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
            if(enumDpPRModeSupport == _DP_PR_MODE_SUPPORT_ON)
            {
                SET_DP_PR_MODE_D1_SUPPORT(_ON);
            }
            else
            {
                SET_DP_PR_MODE_D1_SUPPORT(_OFF);
            }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#if(_D1_DP_AUXLESS_ALPM_SUPPORT == _ON)
            if(enumDpAuxlessAlpmSupport == _DP_AUXLESS_ALPM_SUPPORT_ON)
            {
                SET_DP_AUXLESS_ALPM_D1_SUPPORT(_ON);
            }
            else
#endif
            {
                SET_DP_AUXLESS_ALPM_D1_SUPPORT(_OFF);
            }
#endif

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            SET_DP_RX_D2_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE(enumDpLinkRate);
            SET_DP_RX_D2_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

#if(_AUDIO_SUPPORT == _ON)
            SET_AUDIO_DP_D2_SUPPORT(enumDpAudioSupport);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            SET_DSC_D2_SUPPORT(enumDpDscDecodeSupport);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
            SET_FREESYNC_DP_D2_SUPPORT(enumDpFreeSyncSupport);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            SET_ADAPTIVESYNC_DP_D2_SUPPORT(enumDpAdaptiveSyncSupport);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
            if(enumDpPRModeSupport == _DP_PR_MODE_SUPPORT_ON)
            {
                SET_DP_PR_MODE_D2_SUPPORT(_ON);
            }
            else
            {
                SET_DP_PR_MODE_D2_SUPPORT(_OFF);
            }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#if(_D2_DP_AUXLESS_ALPM_SUPPORT == _ON)
            if(enumDpAuxlessAlpmSupport == _DP_AUXLESS_ALPM_SUPPORT_ON)
            {
                SET_DP_AUXLESS_ALPM_D2_SUPPORT(_ON);
            }
            else
#endif
            {
                SET_DP_AUXLESS_ALPM_D2_SUPPORT(_OFF);
            }
#endif

            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:

            SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

#if(_AUDIO_SUPPORT == _ON)
            SET_AUDIO_DP_D0_SUPPORT(enumDpAudioSupport);
            SET_AUDIO_DP_D1_SUPPORT(enumDpAudioSupport);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
#if((_DSC_MAC_DECODER_0_SUPPORT == _ON) && (_DSC_MAC_DECODER_1_SUPPORT == _ON))
            SET_DSC_D0_SUPPORT(_DSC_DECODER_SUPPORT_OFF);
            SET_DSC_D1_SUPPORT(_DSC_DECODER_SUPPORT_OFF);
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
            SET_FREESYNC_DP_D0_SUPPORT(enumDpFreeSyncSupport);
            SET_FREESYNC_DP_D1_SUPPORT(enumDpFreeSyncSupport);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            SET_ADAPTIVESYNC_DP_D0_SUPPORT(enumDpAdaptiveSyncSupport);
            SET_ADAPTIVESYNC_DP_D1_SUPPORT(enumDpAdaptiveSyncSupport);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
            if(enumDpPRModeSupport == _DP_PR_MODE_SUPPORT_ON)
            {
                SET_DP_PR_MODE_D0_SUPPORT(_ON);
                SET_DP_PR_MODE_D1_SUPPORT(_ON);
            }
            else
            {
                SET_DP_PR_MODE_D0_SUPPORT(_OFF);
                SET_DP_PR_MODE_D1_SUPPORT(_OFF);
            }
#endif

            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:

            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_D2_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D2_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

#if(_AUDIO_SUPPORT == _ON)
            SET_AUDIO_DP_D1_SUPPORT(enumDpAudioSupport);
            SET_AUDIO_DP_D2_SUPPORT(enumDpAudioSupport);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
#if((_DSC_MAC_DECODER_0_SUPPORT == _ON) && (_DSC_MAC_DECODER_1_SUPPORT == _ON))
            SET_DSC_D1_SUPPORT(_DSC_DECODER_SUPPORT_OFF);
            SET_DSC_D2_SUPPORT(_DSC_DECODER_SUPPORT_OFF);
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
            SET_FREESYNC_DP_D1_SUPPORT(enumDpFreeSyncSupport);
            SET_FREESYNC_DP_D2_SUPPORT(enumDpFreeSyncSupport);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            SET_ADAPTIVESYNC_DP_D1_SUPPORT(enumDpAdaptiveSyncSupport);
            SET_ADAPTIVESYNC_DP_D2_SUPPORT(enumDpAdaptiveSyncSupport);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
            if(enumDpPRModeSupport == _DP_PR_MODE_SUPPORT_ON)
            {
                SET_DP_PR_MODE_D0_SUPPORT(_ON);
                SET_DP_PR_MODE_D1_SUPPORT(_ON);
            }
            else
            {
                SET_DP_PR_MODE_D0_SUPPORT(_OFF);
                SET_DP_PR_MODE_D1_SUPPORT(_OFF);
            }
#endif

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Mac Arbiter Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpMacArbiterInitial(void)
{
#if(_DP_MAC_SWITCH_SUPPORT == _ON)

#if(_DP_MAC_RX0_SUPPORT == _ON)
#if(_DP_RX_MAC_STREAM_MST2SST_ASSIGN == _MAPPING_RX0)
    ScalerDpRxSetMacSwitch(_DP_MAC_0, _STREAM_SOURCE_MST2SST);
#else
    ScalerDpRxSetMacSwitch(_DP_MAC_0, _STREAM_SOURCE_NONE);
#endif
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
#if(_DP_RX_MAC_STREAM_MST2SST_ASSIGN == _MAPPING_RX1)
    ScalerDpRxSetMacSwitch(_DP_MAC_1, _STREAM_SOURCE_MST2SST);
#else
    ScalerDpRxSetMacSwitch(_DP_MAC_1, _STREAM_SOURCE_NONE);
#endif
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
#if(_DP_RX_MAC_STREAM_MST2SST_ASSIGN == _MAPPING_RX2)
    ScalerDpRxSetMacSwitch(_DP_MAC_2, _STREAM_SOURCE_MST2SST);
#else
    ScalerDpRxSetMacSwitch(_DP_MAC_2, _STREAM_SOURCE_NONE);
#endif
#endif

#else

#if(_DP_MAC_RX0_SUPPORT == _ON)
    ScalerDpRxSetMacSwitch(_DP_MAC_0, ScalerDpRxDxMacSourceMapping(_D0_INPUT_PORT));
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    ScalerDpRxSetMacSwitch(_DP_MAC_1, ScalerDpRxDxMacSourceMapping(_D1_INPUT_PORT));
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    ScalerDpRxSetMacSwitch(_DP_MAC_2, ScalerDpRxDxMacSourceMapping(_D2_INPUT_PORT));
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    ScalerDpRxSetMacSwitch(_DP_MAC_3, ScalerDpRxDxMacSourceMapping(_D9_INPUT_PORT));
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    ScalerDpRxSetMacSwitch(_DP_MAC_4, _STREAM_SOURCE_MST2SST);
#endif

#endif
}

//--------------------------------------------------
// Description  : DP Mac Arbitration For Dx Inputport
// Input Value  : EnumInputPort, ucRegionCount
// Output Value : None
//--------------------------------------------------
void SysDpMacArbiterInputPort(EnumInputPort enumInputPort, BYTE ucRegionCount)
{
    enumInputPort = enumInputPort;
    ucRegionCount = ucRegionCount;

#if(_DP_MAC_SWITCH_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch(enumInputPort);

    if(SysSourceGetPortTypeFromInputPort(enumInputPort) != _PORT_DP)
    {
        return;
    }

    // The Input Port Has Been Applied a Mac Resource
    if(enumDpMacSel != _DP_MAC_NONE)
    {
        return;
    }

    if(SysSourceCheckAllSourceJudged() != _TRUE)
    {
        if(ucRegionCount == 1)
        {
#if(_DP_MAC_RX0_SUPPORT == _ON)
            ScalerDpRxSetMacSwitchToInputPort(_DP_MAC_0, enumInputPort);
#endif
        }
#if(_MULTI_DISPLAY_MAX >= 0x02)
        else if(ucRegionCount == 2)
        {
#if(_DP_MAC_RX0_SUPPORT == _ON)
            EnumInputPort enumInputPortAssignMacStream0 = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0);

            if((enumInputPortAssignMacStream0 == _NO_INPUT_PORT) ||
               ((GET_SOURCE_JUDGE(SysSourceConvertSearchPort(enumInputPortAssignMacStream0)) == _FALSE) &&
                (SysDpRxFixedTargetPortCheck(enumInputPortAssignMacStream0) == _FALSE)))
            {
                ScalerDpRxSetMacSwitchToInputPort(_DP_MAC_0, enumInputPort);
            }
            else
#endif
            {
#if(_DP_MAC_RX1_SUPPORT == _ON)
                ScalerDpRxSetMacSwitchToInputPort(_DP_MAC_1, enumInputPort);
#endif
            }
        }
        else
        {
            // Plan again if there is demand in the future
        }
#endif
    }
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    else if(SysSourceBgJudgeDoDetect() == _TRUE)
    {
#if(_DP_RX_MAC_STREAM_BG_ASSIGN == _MAPPING_RX0)
        enumDpMacSel = _DP_MAC_0;
#elif(_DP_RX_MAC_STREAM_BG_ASSIGN == _MAPPING_RX1)
        enumDpMacSel = _DP_MAC_1;
#elif(_DP_RX_MAC_STREAM_BG_ASSIGN == _MAPPING_RX2)
        enumDpMacSel = _DP_MAC_2;
#else
        enumDpMacSel = _DP_MAC_NONE;
#endif

        ScalerDpRxSetMacSwitchToInputPort(enumDpMacSel, enumInputPort);
    }
#endif
#endif
}

#if(_DP_MAC_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Unjudged Mac Assign Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpMacUnjudgedMacMappingReset(void)
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_0;
#elif(_DP_MAC_RX1_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_1;
#elif(_DP_MAC_RX2_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_2;
#endif

    for(EnumDpMacSel enumDpMacSel = enumDpMacSelStart; enumDpMacSel < _DP_MAC_ENTITY_MAX; enumDpMacSel++)
    {
        EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);

        if((ScalerDpRxGetMacStreamSourceType(enumDpMacSel) != _STREAM_SOURCE_NONE) &&
           (ScalerDpRxGetMacStreamSourceType(enumDpMacSel) != _STREAM_SOURCE_MST2SST) &&
           (GET_SOURCE_JUDGE(SysSourceConvertSearchPort(enumInputPort)) == _FALSE))
        {
#if(_MULTI_DISPLAY_MAX >= 0x02)
            // Fixed Target Port Cannot Be Cleared
            if(SysDpRxFixedTargetPortCheck(enumInputPort) == _FALSE)
#endif
            {
                ScalerDpRxSetMacSwitch(enumDpMacSel, _STREAM_SOURCE_NONE);

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
                ScalerDpRxMacDphyToStreamMuxReset(enumDpMacSel);
#endif
            }
        }
    }
}

#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mac Arbitration For Dx Inputport
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void SysDpMacDphyArbiterInputPort(EnumInputPort enumInputPort)
{
    if(SysSourceGetPortTypeFromInputPort(enumInputPort) != _PORT_DP)
    {
        return;
    }

#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    ScalerDpRxSetMacDphySwitchToInputPort(_DP_MAC_DPHY_RX0, enumInputPort);
#endif
}
#endif
#endif

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : Dp Check Fix Target Port Or Not
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysDpRxFixedTargetPortCheck(EnumInputPort enumInputPort)
{
    EnumRegionIndex enumRegionIndex = SysRegionConvertPortToRegionIndex(enumInputPort);

    if((enumRegionIndex == _REGION_INDEX_NONE) ||
       ((GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_AUTO_IN_GROUP) && (enumRegionIndex == GET_SOURCE_AUTO_TARGET())))
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : DP Mac Arbitration
// Input Value  : EnumInputPort, EnumDpMacApplyType
// Output Value : None
//--------------------------------------------------
void SysDpMacArbiter(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DP_MAC_SWITCH_SUPPORT == _ON)
    DebugMessageDpRx("7. Mac Arbiter Apply Mac InputPort", enumInputPort);

#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
    SysDpMacDphyArbiterInputPort(enumInputPort);
#endif

    SysDpMacArbiterInputPort(enumInputPort, GET_RGN_MAX_DISPLAY_REGION());
#endif
}

//--------------------------------------------------
// Description  : DP connector
// Input Value  : enumInputPort
// Output Value : connector type
//--------------------------------------------------
BYTE SysDpGetConnectorType(EnumInputPort enumInputPort)
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
            return _DP_CONNECTOR_NORMAL;
    }
}

//--------------------------------------------------
// Description  : DP Port Cable Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysDpCableStatus(EnumInputPort enumInputPort)
{
#if(_DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW == _ON)
    if(SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT)
    {
        if((UserCommonDpGetMSTCapablePort() != _DP_MST_NO_PORT) &&
           (enumInputPort != SysSourceGetInputPort()))
        {
            return _FALSE;
        }
    }
#endif

#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
    if(ScalerSyncGetTypeCSupportStatus(enumInputPort) == _TRUE)
    {
        return SysUsbTypeCRxGetAltModeReady(enumInputPort);
    }
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
#endif

    return ScalerSyncGetCableStatus(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Cable Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpCableDetection(void)
{
    EnumInputPort enumInputPort = _D0_INPUT_PORT;

    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
    {
        if(SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_DP)
        {
            bit bCableStatus = SysDpCableStatus(enumInputPort);

            if(ScalerDpRxCableStatus(enumInputPort) != bCableStatus)
            {
                ScalerDpRxSetCableStatus(enumInputPort, bCableStatus);

                if(bCableStatus == _TRUE)
                {
                    if((GET_DP_DC_OFF_HPD_HIGH() == _ON) || (SysPowerGetPowerStatus() != _POWER_STATUS_OFF))
                    {
#if(_DP_MST_SUPPORT == _ON)
                        if(!((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (ScalerDpRxGetMstCapability(enumInputPort) == _TRUE)))
#endif
                        {
                            if(ScalerDpRxGetConnectorType(enumInputPort) == _DP_CONNECTOR_EMBEDDED)
                            {
                                ScalerDpRxReactiveTimerEventHotPlugAsserted(enumInputPort, 0);
                            }
                            else
                            {
                                ScalerDpRxReactiveTimerEventHotPlugAsserted(enumInputPort, SEC(0.1));
                            }
                        }

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                        ScalerDpMacRxPowerProc(enumInputPort, _POWER_ACTION_OFF_TO_NORMAL);
#endif
                    }
                }
                else
                {
#if(_DP_MST_SUPPORT == _ON)
                    // Cable Unplug Reset
                    ScalerDpMstRxCableUnplugReset(enumInputPort);

                    // Reset MST Backup
                    ScalerDpMacDphyRxMstInfoBackup(enumInputPort, _DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AUDIO_SUPPORT == _ON)
                    SysAudioDpAudioSecDataResetProc(enumInputPort);
#else
                    ScalerDpMacStreamRxSecDataReset(enumInputPort);
#endif

                    ScalerDpMacDphyRxHDCPUnplugReset(enumInputPort);

                    ScalerDpRxSetHotPlugEvent(enumInputPort, _DP_HPD_LOW);

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                    if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
                    {
                        ScalerDpMacRxPowerProc(enumInputPort, _POWER_ACTION_NORMAL_TO_OFF);
                    }
#endif
                }
            }

            ScalerDpAuxRxChPowerStatusCheck(enumInputPort, ScalerDpRxCableStatus(enumInputPort));
        }
    }
}

//--------------------------------------------------
// Description  : DP Power Check Target
// Input Value  : enumPowerStatus
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysDpPowerTargetCheck(EnumPowerStatus enumPowerStatus)
{
    // Only DP IP Trigger Into Fake Off / Fake Saving Need Power Target Check
    bit bNeedPowerTargetCheck = _FALSE;

    switch(enumPowerStatus)
    {
        case _POWER_STATUS_OFF:

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
            if(GET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK() == _TRUE)
            {
                bNeedPowerTargetCheck = _TRUE;

                // Check If Any One Dp Cable Plugged, DO NOT Switch Power to Off or Saving
                for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
                {
                    if(SysSourceGetPortTypeFromInputPort(enumInputPort) != _PORT_DP)
                    {
                        continue;
                    }

                    if(ScalerDpRxCableStatus(enumInputPort) == _TRUE)
                    {
                        return _FALSE;
                    }
                }
            }
#endif

#if(_DP_MST_SUPPORT == _ON)
            for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
            {
                if(SysSourceGetPortTypeFromInputPort(enumInputPort) != _PORT_DP)
                {
                    continue;
                }

                if(GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(enumInputPort) == _TRUE)
                {
                    bNeedPowerTargetCheck = _TRUE;

                    // Check If Any One MST Port Cable Plugged, DO NOT Switch Power to Off
                    if(ScalerDpRxCableStatus(enumInputPort) == _TRUE)
                    {
                        return _FALSE;
                    }
                }
            }
#endif

            break;


        case _POWER_STATUS_SAVING:

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
            if(GET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK() == _TRUE)
            {
                bNeedPowerTargetCheck = _TRUE;

                // Check If Any One Dp Cable Plugged, DO NOT Switch Power to Off or Saving
                for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
                {
                    if(ScalerDpRxCableStatus(enumInputPort) == _TRUE)
                    {
                        return _FALSE;
                    }
                }
            }
#endif

            break;

        default:

            break;
    }

    if(bNeedPowerTargetCheck == _FALSE)
    {
        // No Need Check (NOT DP IP Trigger Into Fake OFF/Fake Saving)
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Power Power Handler
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void SysDpPowerHandler(void)
{
    // Only In Fake Off Or Fake Saving Need Power Proc
    if(GET_POWER_STATUS() != _POWER_STATUS_NORMAL)
    {
        return;
    }

    if(GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE)
    {
#if((_DP_MST_SUPPORT == _ON) || (_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON))
        // Check Fake Off to Off
        if(SysDpPowerTargetCheck(_POWER_STATUS_OFF) == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

            SysDpPowerFakeOffToOffProc();

            SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
        }
#endif
    }
#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
    else if(GET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK() == _TRUE)
    {
        // Check Fake Saving to Saving
        if(SysDpPowerTargetCheck(_POWER_STATUS_SAVING) == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_SAVING_TO_SAVING);

            SysDpPowerFakeSavingToSavingProc();
        }
    }
#endif
}

//--------------------------------------------------
// Description  : DP Power Fake Off To Off Reset
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void SysDpPowerFakeOffToOffProc(void)
{
#if(_DP_MST_SUPPORT == _ON)
    ScalerSyncDpMstFakeOffDoneProc();
#endif

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
    CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
#endif
}

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Power Fake Saving To Saving Reset
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void SysDpPowerFakeSavingToSavingProc(void)
{
    CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();

    if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
    {
        SET_DP_HDCP_POWER_OFF_HANDSHAKE_TIMEOUT_FLAG();
    }
}
#endif

//--------------------------------------------------
// Description  : DP Rx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxHandler(void)
{
    SysDpCableDetection();

#if(_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON)
    SysDpAuxRxPowerOnJudge();
#endif

    SysDpPowerHandler();

    // Dp Stream Judge Data Path Handler
    ScalerDpStreamJudgeHandler();

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
    {
        // For Dp Rx MTP Format Stream: 128b132b SST or MST
        ScalerDpMacDphyRxStreamChangeHandler();
    }
#endif

    SysDpRxMainPortJudgeHandler();

#if(_DP_TX_SUPPORT == _ON)
    ScalerDpRxSinkCountUpdateProc();
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    ScalerDpRxMstToSstDscCapSwitchProc();
#endif

    ScalerSyncDpCapabilitySwitchProc();

    // DP Judge HPD Toggle
    SysDpJudgeHPDToggle();

#if(_DP_TX_SUPPORT == _ON)
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        ScalerSyncDpHdcpRepeaterSupportProc();
    }
#endif

    ScalerDpRxHotPlugHandler();

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
    ScalerDpMacTxSetSleepAudioState(UserInterfaceAudioGetStandAloneStatus());
#endif // End of #if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))

#endif // End of #if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

#if(_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON)
    SysDpAuxRxPowerOffJudge();
#endif
}

//--------------------------------------------------
// Description  : Decide DP Rx Judge HPD Toggle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpJudgeHPDToggle(void)
{
    if(GET_DP_DC_OFF_HPD_TOGGLE_FLAG() == _TRUE)
    {
        CLR_DP_DC_OFF_HPD_TOGGLE_FLAG();

        switch(GET_POWER_STATUS())
        {
            case _POWER_STATUS_OFF:

                ScalerSyncDpPowerSwitchHpdToggleProc(_POWER_ACTION_NORMAL_TO_OFF);
                break;

            case _POWER_STATUS_NORMAL:

                if(GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE)
                {
                    ScalerSyncDpPowerSwitchHpdToggleProc(_POWER_ACTION_NORMAL_TO_FAKE_OFF);
                }
                else
                {
                    ScalerSyncDpPowerSwitchHpdToggleProc(_POWER_ACTION_OFF_TO_NORMAL);
                }

                break;

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Decide DP Rx Dc Off Set HPD Toggle Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpDcOffHPDToggleProc(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

            SET_DP_DC_OFF_HPD_TOGGLE_FLAG();

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
            SET_DP_DC_ON_HPD_TOGGLE_MODE(UserInterfaceDpGetDcOnHpdMode());
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check DP Source Keep Detecting or Not
// Input Value  : None
// Output Value : _TRUE: keep detecting, _FALSE: stop detecting
//--------------------------------------------------
bit SysDpSourceKeepDetectingCheck(void)
{
#if(_AUDIO_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
    if((SysAudioPlayingAloneStatus() == _TRUE) &&
       (UserInterfaceAudioGetSource() == _DIGITAL_AUDIO))
    {
        return _TRUE;
    }
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
    if((GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT) &&
       (GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE) &&
       (ScalerDpRxGetMstCapability(SysSourceGetInputPort()) == _TRUE))
    {
        if((ScalerDpRxGetSrcMstUpRequestEnable(SysSourceGetInputPort()) == _TRUE) &&
           (ScalerDpRxGetPowerStatus(SysSourceGetInputPort()) == _DP_POWER_NORMAL))
        {
            return _TRUE;
        }
    }
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
#if(_SOURCE_PXP_MAIN_PORT_SEARCH_STYLE == _DP_MST_PXP_MAIN_PORT_FIXED)
    if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
    {
        if(SysSourceGetInputPort() == GET_DP_MST_RX_PXP_INPUT_PORT())
        {
            if((GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE) &&
               (ScalerDpRxGetMstCapability(SysSourceGetInputPort()) == _TRUE))
            {
                if((ScalerDpRxGetSrcMstUpRequestEnable(SysSourceGetInputPort()) == _TRUE) &&
                   (ScalerDpRxGetPowerStatus(SysSourceGetInputPort()) == _DP_POWER_NORMAL))
                {
                    return _TRUE;
                }
            }
        }
    }
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Rx Main Port Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxMainPortInitial(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

#if(_DP_TX_SUPPORT == _ON)
    enumInputPort = SysDpTxCloneGetInputPort();
#endif

    ScalerDpRxMainPortInitial(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Rx Main Port Judge Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxMainPortJudgeHandler(void)
{
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        EnumInputPort enumInputPort = _NO_INPUT_PORT;

#if(_DP_TX_SUPPORT == _ON)
        enumInputPort = SysDpTxCloneGetInputPort();
#endif

        if(ScalerDpRxGetMainPort() == enumInputPort)
        {
            return;
        }

        if(SysDpRxMainPortSwitchCheck(enumInputPort) == _TRUE)
        {
            ScalerDpRxMainPortSwitch(enumInputPort);
        }
    }
}

//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysDpRxMainPortSwitchCheck(EnumInputPort enumInputPort)
{
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
    if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
    {
        return _FALSE;
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    // Always Return _TRUE in Fixed Port Mode
    if(ScalerDpMacTxCloneGetSourceSwitchFixedMode(enumDisplayMode) == _TRUE)
    {
        return _TRUE;
    }
#endif

    if(enumInputPort == _NO_INPUT_PORT)
    {
#if(_DP_TX_CLONE_FROM_HDMI_SUPPORT == _ON)
        return _TRUE;
#else
        return _FALSE;
#endif
    }

    if((enumInputPort == SysSourceGetInputPort()) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE))
    {
        return _FALSE;
    }

    if(GET_SOURCE_JUDGE(SysSourceConvertSearchPort(enumInputPort)) == _TRUE)
    {
        return _TRUE;
    }

    if(enumDisplayMode == _DISPLAY_MODE_1P)
    {
#if(_DP_MST_SUPPORT == _ON)
        if((ScalerDpRxGetMstCapability(enumInputPort) == _TRUE) &&
           (ScalerDpRxGetSrcMstUpRequestEnable(enumInputPort) == _TRUE))
        {
            return _TRUE;
        }
#endif
    }

    return _FALSE;
}

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Rx Pxp Port Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxPxpPortInitial(void)
{
    ScalerDpMacStreamRxSdpInitial(_D9_INPUT_PORT);
}

//--------------------------------------------------
// Description  : Set Dp Rx Pxp Input Port
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void SysDpRxPxpInputPortSwitch(EnumInputPort enumInputPort)
{
    if(enumInputPort == GET_DP_MST_RX_PXP_INPUT_PORT())
    {
        if(ScalerDpRxGetPxpInputPortMux() == enumInputPort)
        {
            return;
        }
    }

    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
            SET_DP_MST_RX_PXP_INPUT_PORT(enumInputPort);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            SET_DP_MST_RX_PXP_INPUT_PORT(enumInputPort);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:
            SET_DP_MST_RX_PXP_INPUT_PORT(enumInputPort);
            break;
#endif

        default:
            SET_DP_MST_RX_PXP_INPUT_PORT(_NO_INPUT_PORT);
            break;
    }

    ScalerDpRxSetPxpInputPortMux(enumInputPort);

    DebugMessageSystem("Pxp mode Input Target", GET_DP_MST_RX_PXP_INPUT_PORT());
}

//--------------------------------------------------
// Description  : Dp Get Pxp Input TargetPort
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort SysDpGetPxpInputTargetPort(void)
{
    EnumInputPort enumPxpInputTargetPort = _NO_INPUT_PORT;
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    if(ScalerDpMstRxGetPxpMode() == _DP_MST_PXP_ON_FIXED_MODE)
    {
        enumPxpInputTargetPort = GET_RGN_INPUT_PORT(_REGION_INDEX_0);

        if(enumPxpInputTargetPort == _D9_INPUT_PORT)
        {
            enumPxpInputTargetPort = GET_RGN_INPUT_PORT(_REGION_INDEX_1);
        }
    }
    else if(ScalerDpMstRxGetPxpMode() == _DP_MST_PXP_ON_SELECT_MODE)
    {
        if(GET_DP_MST_RX_PXP_INPUT_PORT() == _NO_INPUT_PORT)
        {
            if(GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT)
            {
                for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ucRegionIndex++)
                {
                    if(ucRegionIndex != GET_SOURCE_AUTO_TARGET())
                    {
                        enumPxpInputTargetPort = GET_RGN_INPUT_PORT(ucRegionIndex);
                        break;
                    }
                }
            }
        }
        else
        {
            enumPxpInputTargetPort = GET_DP_MST_RX_PXP_INPUT_PORT();
        }
    }

    DebugMessageSystem("Pxp fixed mode Get Input Target Port", enumPxpInputTargetPort);

    return enumPxpInputTargetPort;
}

//--------------------------------------------------
// Description  : Dp Rx Pxp Port Num Swap Judge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxPxpPortNumSwapJudge(void)
{
    if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
    {
#if(_DP_MST_PXP_FIXED_MODE_SUPPORT == _ON)
        if(GET_DP_MST_RX_PXP_MODE() == _DP_MST_PXP_ON_FIXED_MODE)
        {
            SET_DP_MST_RX_PXP_PORT_NUM_SWAP(UserInterfaceDpGetPxpPortNumSwapStatus());
        }
        else
#endif
        {
            // case: _DP_MST_PXP_ON_SELECT_MODE
            SET_DP_MST_RX_PXP_PORT_NUM_SWAP(_DP_PXP_PORT_NUM_SWAP_FALSE);
        }
    }
    else
    {
        SET_DP_MST_RX_PXP_PORT_NUM_SWAP(_DP_PXP_PORT_NUM_SWAP_FALSE);
    }
}
#endif

#if(_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON)
//--------------------------------------------------
// Description  : Dp AUX Rx Power On Judge
// Input Value  : EnumInputPort enumInputPort
// Output Value : None
//--------------------------------------------------
void SysDpAuxRxPowerOnJudge(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
    {
        if(SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_DP)
        {
            if((ScalerDpRxCableStatus(enumInputPort) == _TRUE) && (SysDpAuxRxGetPowerStatus(enumInputPort) == _POWER_CUT_ON))
            {
                SysDpAuxRxPowerOn(enumInputPort);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Dp AUX Rx Power On Control
// Input Value  : EnumInputPort enumInputPort
// Output Value : None
//--------------------------------------------------
void SysDpAuxRxPowerOffJudge(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
    {
        if(SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_DP)
        {
            if((ScalerDpRxCableStatus(enumInputPort) == _FALSE) && (SysDpAuxRxGetPowerStatus(enumInputPort) == _POWER_CUT_OFF))
            {
                SysDpAuxRxPowerOff(enumInputPort);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Dp AUX Rx Power On
// Input Value  : EnumInputPort enumInputPort
// Output Value : None
//--------------------------------------------------
void SysDpAuxRxPowerOn(EnumInputPort enumInputPort)
{
    ScalerDpAuxRxPowerControl(enumInputPort, _POWER_ON);

    DebugMessageDpRx("DP Aux Rx : Power Switch On", enumInputPort);
}

//--------------------------------------------------
// Description  : Dp AUX Rx Power Off
// Input Value  : EnumInputPort enumInputPort
// Output Value : None
//--------------------------------------------------
void SysDpAuxRxPowerOff(EnumInputPort enumInputPort)
{
    ScalerDpAuxRxPowerControl(enumInputPort, _POWER_OFF);

    DebugMessageDpRx("DP Aux Rx : Power Switch Off", enumInputPort);
}

//--------------------------------------------------
// Description  : Dp AUX Rx Get Power Status
// Input Value  : EnumInputPort enumInputPort
// Output Value : EnumPowerCut
//--------------------------------------------------
EnumPowerCut SysDpAuxRxGetPowerStatus(EnumInputPort enumInputPort)
{
    return ScalerDpAuxRxGetPowerStatus(enumInputPort);
}
#endif
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxHandler(void)
{
    SysDpTxSyncPowerStatusProc();

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacTxLinkEstablishManagement();
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpMacTxDaisyChangeHandler();
#endif

    // HPD Detection Function
    ScalerDpMacTxHPDProc();

    ScalerDpMacTxJudgeHandler();

    ScalerDpMacTxModeHandler();

    ScalerDpMacTxSinkCountProc();

    if(SysDpTxCloneOutputStatus(_CHECK_DISPLAY_STATUS) == _TRUE)
    {
        EnumInputPort enumInputPort = SysDpTxCloneGetInputPort();
        EnumPortType enumPortType = SysSourceGetPortTypeFromInputPort(enumInputPort);
        ScalerDpMacTxCloneOutputProc(enumInputPort, enumPortType, SysDpTxCloneOutputStatus(_CHECK_SUPPORT_STATUS));
    }

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
    SysDpTxHdcp2Handler();
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
    SysDpTxHdcp14Handler();
#endif

#if(_DP_HDCP_RX_SUPPORT == _ON)
    ScalerDpRxHdcpHandler();
#endif
}

//--------------------------------------------------
// Description  : System Dp Tx Port Cable Detect
// Input Value  : enumOutputPort
// Output Value : _TRUE => Cable Detected, _FASLE => Cable Undetected
//--------------------------------------------------
bit SysDpTxCableDetect(EnumOutputPort enumOutputPort)
{
    enumOutputPort = enumOutputPort;

    return ScalerDpMacTxCableDetect();
}

//--------------------------------------------------
// Description  : DP Rx Handler
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
EnumInputPort SysDpTxCloneGetInputPort(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    // Source Switch Fixed Port Mode
    if(ScalerDpMacTxCloneGetSourceSwitchFixedMode(enumDisplayMode) == _TRUE)
    {
        enumInputPort = UserInterfaceDpGetCloneOutputUserInputPort();
    }
    // Source Switch Auto Mode
    else
    {
        if(enumDisplayMode == _DISPLAY_MODE_1P)
        {
            enumInputPort = SysSourceGetInputPort();
        }
        else
        {
            enumInputPort = SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0));

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
            if(enumInputPort == _D9_INPUT_PORT)
            {
                enumInputPort = SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_1));
            }
#endif
        }
    }

#if(_DP_TX_CLONE_FROM_HDMI_SUPPORT == _OFF)
    // Only DP Port Can Be Cloned
    if((enumInputPort != _NO_INPUT_PORT) && (SysSourceGetPortTypeFromInputPort(enumInputPort) != _PORT_DP))
    {
        enumInputPort = _NO_INPUT_PORT;
    }
#endif

    return enumInputPort;
}

//--------------------------------------------------
// Description  : DP Tx Sync Power Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxSyncPowerStatusProc(void)
{
    SET_DP_TX_POWER_STATUS(GET_POWER_STATUS());
}

//--------------------------------------------------
// Description  : Decide whether supported/execute Clone output to DP Tx
// Input Value  : enumMode = _CHECK_SUPPORT_STATUS : decide Clone Mode is supported or not
//                enumMode = _CHECK_DISPLAY_STATUS : decide Clone Mode is executed or not
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysDpTxCloneOutputStatus(EnumDpTxCloneModeStatus enumMode)
{
    BYTE ucDisplayStartRegion = _DISPLAY_RGN_NONE;
    BYTE ucDisplayEndRegion = _DISPLAY_RGN_NONE;

    if(enumMode == _CHECK_SUPPORT_STATUS)
    {
        if(UserInterfaceDpGetCloneOutputStatus() == _DP_CLONE_OUTPUT_FALSE)
        {
            return _FALSE;
        }
    }

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            ucDisplayStartRegion = _DISPLAY_RGN_1P;
            ucDisplayEndRegion = _DISPLAY_RGN_1P;
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            ucDisplayStartRegion = _DISPLAY_RGN_PIP_MAIN;
            ucDisplayEndRegion = _DISPLAY_RGN_PIP_SUB;
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            ucDisplayStartRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
            ucDisplayEndRegion = _DISPLAY_RGN_EAGLE_SIGHT_SUB;
            break;
#endif


#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            ucDisplayStartRegion = _DISPLAY_RGN_PBP_LR_EQUAL_LEFT;
            ucDisplayEndRegion = _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT;
            break;
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            ucDisplayStartRegion = _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT;
            ucDisplayEndRegion = _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT;
            break;
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            ucDisplayStartRegion = _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT;
            ucDisplayEndRegion = _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT;
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            ucDisplayStartRegion = _DISPLAY_RGN_TOP;
            ucDisplayEndRegion = _DISPLAY_RGN_BOTTOM;
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            ucDisplayStartRegion = _DISPLAY_RGN_FLAG_MAIN;
            ucDisplayEndRegion = _DISPLAY_RGN_FLAG_RIGHT;
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
            ucDisplayStartRegion = _DISPLAY_RGN_SKEW_L_MAIN;
            ucDisplayEndRegion = _DISPLAY_RGN_SKEW_L_BOTTOM;
            break;
        case _DISPLAY_MODE_3P_SKEW_R:
            ucDisplayStartRegion = _DISPLAY_RGN_SKEW_R_MAIN;
            ucDisplayEndRegion = _DISPLAY_RGN_SKEW_R_BOTTOM;
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
            ucDisplayStartRegion = _DISPLAY_RGN_SKEW_T_MAIN;
            ucDisplayEndRegion = _DISPLAY_RGN_SKEW_T_RIGHT;
            break;
        case _DISPLAY_MODE_3P_SKEW_B:
            ucDisplayStartRegion = _DISPLAY_RGN_SKEW_B_MAIN;
            ucDisplayEndRegion = _DISPLAY_RGN_SKEW_B_RIGHT;
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            ucDisplayStartRegion = _DISPLAY_RGN_LT;
            ucDisplayEndRegion = _DISPLAY_RGN_RB;
            break;
#endif

        default:
            break;
    }

    while(ucDisplayStartRegion <= ucDisplayEndRegion)
    {
        if(SysRegionGetInputPort(ucDisplayStartRegion) == SysDpTxCloneGetInputPort())
        {
            if(enumMode == _CHECK_SUPPORT_STATUS)   // decide Clone Mode is supported or not
            {
                if(ScalerSyncDpTxCloneOutputPortCheck(SysDpTxCloneGetInputPort(), SysSourceGetPortTypeFromInputPort(SysDpTxCloneGetInputPort())) == _FALSE)
                {
                    return _FALSE;
                }

                return _TRUE;
            }
            else if(enumMode == _CHECK_DISPLAY_STATUS)   // decide Clone Mode is executed or not
            {
                if(SysRegionGetDisplayState(ucDisplayStartRegion) == _DISPLAY_STATE_ACTIVE)
                {
                    return _TRUE;
                }
            }
        }

        ucDisplayStartRegion++;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxHdcp14Handler(void)
{
    if(GET_DP_TX_HDCP_RELOAD_KEY_EN() == _TRUE)
    {
        CLR_DP_TX_HDCP_RELOAD_KEY_EN();

#if(_DIGITAL_PORT_SUPPORT == _ON)
        SysPowerLoadDPTxHDCPKey();
#endif
    }
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxHdcp2Handler(void)
{
    BYTE pucDpTxHdcp2Key[384];

    if(GET_DP_HDCP2_TX_LOAD_KEY_EN() == _TRUE)
    {
        CLR_DP_HDCP2_TX_LOAD_KEY_EN();

        ScalerDpHdcp2TxDcpLlcRsaInit();

        UserCommonHdcp2GetDpTxRRMODN(0, 0x180, pucDpTxHdcp2Key);
        ScalerDpHdcp2TxLoadKeyProc(_DP_TX_HDCP2_KEY_RRMODN, pucDpTxHdcp2Key);

        UserCommonHdcp2GetDpTxDcpLlcN(0, 0x180, pucDpTxHdcp2Key);
        ScalerDpHdcp2TxLoadKeyProc(_DP_TX_HDCP2_KEY_DCP_LLC_N, pucDpTxHdcp2Key);

        ScalerDpHdcp2TxLoadKeyProc(_DP_TX_HDCP2_KEY_EKEY1, pucDpTxHdcp2Key);

        UserCommonHdcp2GetDpTxEKey(0, 0x80, pucDpTxHdcp2Key);
        ScalerDpHdcp2TxLoadKeyProc(_DP_TX_HDCP2_KEY_EKEY2, pucDpTxHdcp2Key);

        UserCommonHdcp2GetDpTxNPinv(0, 0x04, pucDpTxHdcp2Key);
        ScalerDpHdcp2TxLoadKeyProc(_DP_TX_HDCP2_KEY_NPINV, pucDpTxHdcp2Key);

        SET_DP_HDCP2_TX_LOAD_KEY_FINISH();
    }
}
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpMstHandler(void)
{
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        ScalerDpMstRxHandler();

        ScalerDpAuxRxSourceWritePowerUpProc();

#if(_DP_TX_SUPPORT == _ON)
        if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
        {
            ScalerDpMacMstToSstStreamsHandler();

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerDpMstTx128b132bTo8b10bStreamHandler();
#endif
        }
#endif
    }
}

#endif
