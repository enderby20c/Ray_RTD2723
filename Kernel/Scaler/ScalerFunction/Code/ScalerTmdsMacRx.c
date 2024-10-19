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
// ID Code      : ScalerTmdsMacRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSMAC__

#include "ScalerFunctionInclude.h"
#include "TmdsMacRx/ScalerTmdsMacRx.h"


#if(_HDMI_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HDMI21_FVA_SUPPORT == _ON)
bit g_bTmdsMacRxHdmi21FvaEnable;
bit g_bTmdsMacRxHdmi21FvaGetIVFInfo;
#endif

#if(_HDMI_ON_POWER_CONTROL == _ON)
EnumOnPowerSwitch g_enumTmdsMacRxOnPowerSwitchOn;
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
StructDpHdmiCompatibleHdmiPSWakeUp g_stTmdsMacRxDpHdmiCompatibleHdmiPsWakeup;
StructDpHdmiCompatible5VStatus g_stTmdsMacRxDpHdmiCompatible5VStatus;
#endif

#if(_HDMI20_SUPPORT == _ON)
Struct5vPinDetect g_stTmdsMacRx5vPinDetect;
StructScdcInfoSet g_stTmdsMacRxScdcInfoSet;

#if(_HDMI_5V_DETECT_BY_USER == _ON)
StructTMDS5vStatusByUser g_stTmdsMacRx5vStatusByUser;
#endif
#endif

StructHdmiZ0HpdInfo g_stTmdsMacRxHdmiZ0HpdInfo = {_HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME, 0, 0};

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
StructHdmiFreesyncReplayEnableInfo g_stTmdsMacRxHdmiFreesyncReplayEnableInfo;
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
BYTE g_ucTmdsMacRxHpdToggleResetArcTxEvent;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get HDMI Ver
// Input Value  : None
// Output Value : Input from which HDMI Mac
//--------------------------------------------------
EnumInputHdmiVer ScalerTmdsMacRxGetHdmiVer(EnumInputPort enumInputPort)
{
    EnumInputHdmiVer enumHdmiVer = _FROM_HDMI_TMDS_MAC;

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
                if(ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
                {
                    enumHdmiVer = _FROM_HDMI_FRL_DSC_MAC;
                }
                else
#endif
                {
                    enumHdmiVer = _FROM_HDMI_FRL_MAC;
                }
            }
            else
#endif
            {
                enumHdmiVer = _FROM_HDMI_TMDS_MAC;
            }
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
                if(ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
                {
                    enumHdmiVer = _FROM_HDMI_FRL_DSC_MAC;
                }
                else
#endif
                {
                    enumHdmiVer = _FROM_HDMI_FRL_MAC;
                }
            }
            else
#endif
            {
                enumHdmiVer = _FROM_HDMI_TMDS_MAC;
            }
            break;
#endif

        default:
            break;
    }

    return enumHdmiVer;
}

//--------------------------------------------------
// Description  : Set Config of TMDS Mac Deonly mode
// Input Value  : None
// Output Value : enumInputPort, enumDeonlyConfig
//--------------------------------------------------
void ScalerTmdsMacRxSetDeOnlyModeConfig(EnumInputPort enumInputPort, EnumDeOnlyConfig enumDeonlyConfig)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == 0x00)
#endif
            {
                ScalerTmdsMacRx3SetDeOnlyModeConfig(enumDeonlyConfig);
            }
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00)
#endif
            {
                ScalerTmdsMacRx4SetDeOnlyModeConfig(enumDeonlyConfig);
            }
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set Config of TMDS Mac Deonly mode
// Input Value  : None
// Output Value : enumInputPort, enumDeonlyConfig
//--------------------------------------------------
EnumDeOnlyConfig ScalerTmdsMacRxGetDeOnlyModeConfig(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == 0x00)
#endif
            {
                return ScalerTmdsMacRx3GetDeOnlyModeConfig();
            }
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00)
#endif
            {
                return ScalerTmdsMacRx4GetDeOnlyModeConfig();
            }
            break;
#endif

        default:
            break;
    }

    return _DE_ONLY_DISABLE;
}

//--------------------------------------------------
// Description  : ScalerTMDSMacForceBckgrdPath
// Input Value  : PORT & enumDDomainRegion
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxForceBckgrdPath(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            SET_TMDS_MAC_RX3_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            SET_TMDS_MAC_RX4_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ScalerTMDSMacForceBckgrdPath
// Input Value  : PORT & enumDDomainRegion
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxClrForceBckgrdPath(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_TMDS_MAC_RX3_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_TMDS_MAC_RX4_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

        default:
            break;
    }
}

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : ScalerTMDSClrPSWakeupPath
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxClrPSWakeupFlag(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_TMDS_MAC_RX3_PS_WAKEUP();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_TMDS_MAC_RX4_PS_WAKEUP();
            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Reset Hs/Vs Polarity
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHVPolarityReset(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerSetBit(P72_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerSetBit(P73_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);
            break;
#endif

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : TMDS Interlace preset for Measure
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxInterlaceCheckPreset(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                // Clear Interlace toggle and error flag
                ScalerSetBit(P68_4A_FRL_MEASURE_A, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT4 | _BIT2));
            }
            else
#endif
            {
                // Clear Interlace toggle and error flag
                ScalerGetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, 2, &pData[0], _AUTOINC);
                ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ((_BIT6 | _BIT5) | pData[0]));

                // Disable IHV delay control; inverted odd signal; odd from IHV delay
                ScalerSetBit(P72_70_IVHS_CTRL_0, ~(_BIT7 | _BIT2), _BIT2);
                ScalerSetByte(P72_72_IVHS_CTRL_2, (_BIT7 | _BIT6));
            }
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                // Clear Interlace toggle and error flag
                ScalerSetBit(P69_4A_FRL_MEASURE_A, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT4 | _BIT2));
            }
            else
#endif
            {
                // Clear Interlace toggle and error flag
                ScalerGetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, 2, &pData[0], _AUTOINC);
                ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ((_BIT6 | _BIT5) | pData[0]));

                // Disable IHV delay control; inverted odd signal; odd from IHV delay
                ScalerSetBit(P73_70_IVHS_CTRL_0, ~(_BIT7 | _BIT2), _BIT2);
                ScalerSetByte(P73_72_IVHS_CTRL_2, (_BIT7 | _BIT6));
            }
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : ScalerTMDSMacClrDDCDetect
// Input Value  : PORT
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetZ0Asserted(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            SET_TMDS_MAC_RX3_Z0_ASSERTED();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            SET_TMDS_MAC_RX4_Z0_ASSERTED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS HPD Toggle Process
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHpdToggleProc(void)
{
#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _OFF)
    ScalerTmdsMacRxDelayModeHpdToggleProc();
#else
    ScalerTmdsMacRxTimerModeHpdToggleProc();
#endif
}

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : TMDS HPD Toggle Process (Delay Mode)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxDelayModeHpdToggleProc(void)
{
    BYTE ucI = 0;
    BYTE ucPortNum = 0;

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    EnumInputPort enumDxFromMacRx3 = ScalerTmdsMacRxRxDxMapping(_RX3);
#endif
#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    EnumInputPort enumDxFromMacRx4 = ScalerTmdsMacRxRxDxMapping(_RX4);
#endif

    StructTmdsHpdSequence pstTmdsHpdSeq[] =
    {
        // dummy Input_Port, HPD_Time
        {_RX_MAP_NONE, _TMDS_HPD_TIME_NONE},

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        {_RX_MAP_NONE, _TMDS_HPD_TIME_NONE},
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        {_RX_MAP_NONE, _TMDS_HPD_TIME_NONE},
#endif

    };

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
    if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE)
#else
    if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) && (GET_HDMI_MAC_RX3_INTERFACE_SWITCHING() == _FALSE))
#endif
    {
        pstTmdsHpdSeq[1 + ucPortNum].ucRXx = _RX3;

        if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ARC_EARC_INITIATE)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _HDMI_ARC_EARC_PORT_HPD_LOW_DURATION;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        // D domain mute Proc
        if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22) || (GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            ScalerTmdsMacRx3ForceMDomainMuteBeforeHpdToggle();
        }

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        ScalerHdmiFrlMacRx3SaveScdcStatus();
#endif

        if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
        {
            ScalerTmdsMacRx3BeforeHotPlugEventProc(_FALSE);
        }
        else
        {
            ScalerTmdsMacRx3BeforeHotPlugEventProc(_TRUE);
        }

        ucPortNum ++;
        CLR_TMDS_MAC_RX3_HPD_TRIGGER_EVENT();
    }
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
    if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE)
#else
    if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) && (GET_HDMI_MAC_RX4_INTERFACE_SWITCHING() == _FALSE))
#endif
    {
        pstTmdsHpdSeq[1 + ucPortNum].ucRXx = _RX4;

        if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ARC_EARC_INITIATE)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _HDMI_ARC_EARC_PORT_HPD_LOW_DURATION;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        // D domain mute Proc
        if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22) || (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            ScalerTmdsMacRx4ForceMDomainMuteBeforeHpdToggle();
        }

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        ScalerHdmiFrlMacRx4SaveScdcStatus();
#endif

        if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
        {
            ScalerTmdsMacRx4BeforeHotPlugEventProc(_FALSE);
        }
        else
        {
            ScalerTmdsMacRx4BeforeHotPlugEventProc(_TRUE);
        }

        ucPortNum ++;
        CLR_TMDS_MAC_RX4_HPD_TRIGGER_EVENT();
    }
#endif

    if(ucPortNum == 0)
    {
        return;
    }

    // Bubble sort for reorder squence (HPD time short -> long)
    for(pData[0] = 1; pData[0] < ucPortNum; pData[0] ++)
    {
        for(pData[1] = 1; pData[1] <= (ucPortNum - pData[0]); pData[1] ++)
        {
            if(pstTmdsHpdSeq[pData[1]].usHpdTime > pstTmdsHpdSeq[pData[1] + 1].usHpdTime)
            {
                pstTmdsHpdSeq[0] = pstTmdsHpdSeq[pData[1]];
                pstTmdsHpdSeq[pData[1]] = pstTmdsHpdSeq[pData[1] + 1];
                pstTmdsHpdSeq[pData[1] + 1] = pstTmdsHpdSeq[0];
            }
        }
    }

    if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
    {
        // wait Z0 Low Period
        ScalerTimerDelayXms(GET_HDMI_Z0_LOW_PERIOD());

        // Z0 High Process
        for(ucI = 1; ucI <= ucPortNum; ucI ++)
        {
            if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
            {
                // Skip high process of this turn
                continue;
            }

            switch(pstTmdsHpdSeq[ucI].ucRXx)
            {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)

                case _RX3:

                    // Restore Z0 Status
                    ScalerTmdsPhyRxRestoreZ0Status(enumDxFromMacRx3, g_ucTmdsMacRx3Z0Status);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                    // Restore Main link related IRQ After Z0 on
                    ScalerHdmiFrlMacRx3IrqRestoreAfterZ0On();
#endif
                    break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)

                case _RX4:

                    // Restore Z0 Status
                    ScalerTmdsPhyRxRestoreZ0Status(enumDxFromMacRx4, g_ucTmdsMacRx4Z0Status);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                    // Restore Main link related IRQ After Z0 on
                    ScalerHdmiFrlMacRx4IrqRestoreAfterZ0On();
#endif
                    break;
#endif

                default:
                    break;
            }
        }

        // wait Z0 / HPD Interval
        ScalerTimerDelayXms(GET_HDMI_Z0_HPD_INTERVAL());
    }

    // Reset the dummy seq time for first HPD delay calculation
    pstTmdsHpdSeq[0].usHpdTime = 0;

    // HPD Low Process
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
        {
            // Skip low process of this turn
            continue;
        }

        switch(ScalerTmdsMacRxRxDxMapping(pstTmdsHpdSeq[ucI].ucRXx))
        {
#if(_D0_HDMI_SUPPORT == _ON)

            case _D0_INPUT_PORT:

                ScalerTmdsMacRxHotPlugLowProc(_D0_INPUT_PORT);

#if(_D0_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D0_INPUT_PORT);
#endif
                break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)

            case _D1_INPUT_PORT:

                ScalerTmdsMacRxHotPlugLowProc(_D1_INPUT_PORT);

#if(_D1_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D1_INPUT_PORT);
#endif
                break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)

            case _D2_INPUT_PORT:

                ScalerTmdsMacRxHotPlugLowProc(_D2_INPUT_PORT);

#if(_D2_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D2_INPUT_PORT);
#endif
                break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)

            case _D3_INPUT_PORT:

                ScalerTmdsMacRxHotPlugLowProc(_D3_INPUT_PORT);

#if(_D3_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D3_INPUT_PORT);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
                // HPD Low then Reset Hdmi2.1
                ScalerHdmiFrlMacRxResetProc(_D3_INPUT_PORT);
#endif
                break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)

            case _D4_INPUT_PORT:

                ScalerTmdsMacRxHotPlugLowProc(_D4_INPUT_PORT);

#if(_D4_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D4_INPUT_PORT);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
                // HPD Low then Reset Hdmi2.1
                ScalerHdmiFrlMacRxResetProc(_D4_INPUT_PORT);
#endif
                break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)

            case _D5_INPUT_PORT:

                ScalerTmdsMacRxHotPlugLowProc(_D5_INPUT_PORT);

#if(_D5_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D5_INPUT_PORT);
#endif
                break;
#endif
            default:
                break;
        }
    }

    // HPD High Process
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
        {
            // Skip high process of this turn
            continue;
        }

        switch(ScalerTmdsMacRxRxDxMapping(pstTmdsHpdSeq[ucI].ucRXx))
        {
#if(_D0_HDMI_SUPPORT == _ON)

            case _D0_INPUT_PORT:

                ScalerTmdsMacRxHotPlugHighProc(_D0_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D0_INPUT_PORT, _TRUE);
                }
                else
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D0_INPUT_PORT, _FALSE);
                }
                break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)

            case _D1_INPUT_PORT:

                ScalerTmdsMacRxHotPlugHighProc(_D1_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D1_INPUT_PORT, _TRUE);
                }
                else
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D1_INPUT_PORT, _FALSE);
                }
                break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)

            case _D2_INPUT_PORT:

                ScalerTmdsMacRxHotPlugHighProc(_D2_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D2_INPUT_PORT, _TRUE);
                }
                else
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D2_INPUT_PORT, _FALSE);
                }
                break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)

            case _D3_INPUT_PORT:

                ScalerTmdsMacRxHotPlugHighProc(_D3_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D3_INPUT_PORT, _TRUE);
                }
                else
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D3_INPUT_PORT, _FALSE);
                }
                break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)

            case _D4_INPUT_PORT:

                ScalerTmdsMacRxHotPlugHighProc(_D4_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D4_INPUT_PORT, _TRUE);
                }
                else
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D4_INPUT_PORT, _FALSE);
                }
                break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)

            case _D5_INPUT_PORT:

                ScalerTmdsMacRxHotPlugHighProc(_D5_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D5_INPUT_PORT, _TRUE);
                }
                else
                {
                    ScalerTmdsMacRxAfterHotPlugEventProc(_D5_INPUT_PORT, _FALSE);
                }
                break;
#endif
            default:
                break;
        }
    }

    if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
    {
        // wait Z0 / HPD Interval
        ScalerTimerDelayXms(GET_HDMI_Z0_HPD_INTERVAL());

        // Z0 Low Process
        for(ucI = 1; ucI <= ucPortNum; ucI ++)
        {
            if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
            {
                // Skip high process of this turn
                continue;
            }

            switch(pstTmdsHpdSeq[ucI].ucRXx)
            {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)

                case _RX3:

                    // Backup and Disable Main link related IRQ before Z0 off to prevetn FRL 8/10/12G signal unstable
                    ScalerHdmiFrlMacRx3IrqBackupBeforeZ0Off();
                    break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)

                case _RX4:

                    // Backup and Disable Main link related IRQ before Z0 off to prevetn FRL 8/10/12G signal unstable
                    ScalerHdmiFrlMacRx4IrqBackupBeforeZ0Off();
                    break;
#endif

                default:
                    break;
            }

            switch(ScalerTmdsMacRxRxDxMapping(pstTmdsHpdSeq[ucI].ucRXx))
            {
#if(_D0_HDMI_SUPPORT == _ON)

                case _D0_INPUT_PORT:

                    // Disable Z0
                    ScalerTmdsPhyRxSetZ0Status(_D0_INPUT_PORT, _DISABLE);
                    break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)

                case _D1_INPUT_PORT:

                    // Disable Z0
                    ScalerTmdsPhyRxSetZ0Status(_D1_INPUT_PORT, _DISABLE);
                    break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)

                case _D2_INPUT_PORT:

                    // Disable Z0
                    ScalerTmdsPhyRxSetZ0Status(_D2_INPUT_PORT, _DISABLE);
                    break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)

                case _D3_INPUT_PORT:

                    // Disable Z0
                    ScalerTmdsPhyRxSetZ0Status(_D3_INPUT_PORT, _DISABLE);
                    break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)

                case _D4_INPUT_PORT:

                    // Disable Z0
                    ScalerTmdsPhyRxSetZ0Status(_D4_INPUT_PORT, _DISABLE);
                    break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)

                case _D5_INPUT_PORT:

                    // Disable Z0
                    ScalerTmdsPhyRxSetZ0Status(_D5_INPUT_PORT, _DISABLE);
                    break;
#endif
                default:
                    break;
            }
        }

        // wait Z0 Low Period
        ScalerTimerDelayXms(GET_HDMI_Z0_LOW_PERIOD());

        // Z0 High Process
        for(ucI = 1; ucI <= ucPortNum; ucI ++)
        {
            if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
            {
                // Skip high process of this turn
                continue;
            }

            switch(pstTmdsHpdSeq[ucI].ucRXx)
            {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)

                case _RX3:

                    // Restore Z0 Status
                    ScalerTmdsPhyRxRestoreZ0Status(enumDxFromMacRx3, g_ucTmdsMacRx3Z0Status);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                    // Restore Main link related IRQ After Z0 on
                    ScalerHdmiFrlMacRx3IrqRestoreAfterZ0On();
#endif
                    break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)

                case _RX4:

                    // Restore Z0 Status
                    ScalerTmdsPhyRxRestoreZ0Status(enumDxFromMacRx4, g_ucTmdsMacRx4Z0Status);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                    // Restore Main link related IRQ After Z0 on
                    ScalerHdmiFrlMacRx4IrqRestoreAfterZ0On();
#endif
                    break;
#endif

                default:
                    break;
            }
        }
    }

#if(_HDMI_FRL_SUPPORT == _ON)
    // Restore SCDC FRL_Ready
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
        {
            // Skip process of this turn
            continue;
        }

        switch(pstTmdsHpdSeq[ucI].ucRXx)
        {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)

            case _RX3:

                ScalerHdmiFrlMacRx3RestoreScdcStatus();
                break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)

            case _RX4:

                ScalerHdmiFrlMacRx4RestoreScdcStatus();
                break;
#endif

            default:
                break;
        }
    }
#endif
}

#else
//--------------------------------------------------
// Description  : TMDS HPD Toggle Process (Timer Mode)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxTimerModeHpdToggleProc(void)
{
    BYTE ucI = 0;
    BYTE ucPortNum = 0;

    StructTmdsHpdSequence pstTmdsHpdSeq[] =
    {
        // dummy Input_Port, HPD_Time
        {_RX_MAP_NONE, _TMDS_HPD_TIME_NONE},

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        {_RX_MAP_NONE, _TMDS_HPD_TIME_NONE},
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        {_RX_MAP_NONE, _TMDS_HPD_TIME_NONE},
#endif

    };

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
    if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) && (GET_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING() == _FALSE))
#else
    if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) && (GET_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING() == _FALSE) && (GET_HDMI_MAC_RX3_INTERFACE_SWITCHING() == _FALSE))
#endif
    {
        SET_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING();

        pstTmdsHpdSeq[1 + ucPortNum].ucRXx = _RX3;

        if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ARC_EARC_INITIATE)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _HDMI_ARC_EARC_PORT_HPD_LOW_DURATION;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        // D domain mute Proc
        if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22) || (GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            ScalerTmdsMacRx3ForceMDomainMuteBeforeHpdToggle();
        }

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        ScalerHdmiFrlMacRx3SaveScdcStatus();
#endif

        if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
        {
            ScalerTmdsMacRx3BeforeHotPlugEventProc(_FALSE);
        }
        else
        {
            ScalerTmdsMacRx3BeforeHotPlugEventProc(_TRUE);
        }

        ucPortNum ++;
    }
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
    if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) && (GET_TMDS_MAC_RX4_ACTIVE_TYPE_HPD_TOGGLING() == _FALSE))
#else
    if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) && (GET_TMDS_MAC_RX4_ACTIVE_TYPE_HPD_TOGGLING() == _FALSE) && (GET_HDMI_MAC_RX4_INTERFACE_SWITCHING() == _FALSE))
#endif
    {
        SET_TMDS_MAC_RX4_ACTIVE_TYPE_HPD_TOGGLING();

        pstTmdsHpdSeq[1 + ucPortNum].ucRXx = _RX4;

        if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ARC_EARC_INITIATE)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _HDMI_ARC_EARC_PORT_HPD_LOW_DURATION;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        // D domain mute Proc
        if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22) || (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            ScalerTmdsMacRx4ForceMDomainMuteBeforeHpdToggle();
        }

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        ScalerHdmiFrlMacRx4SaveScdcStatus();
#endif

        if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
        {
            ScalerTmdsMacRx4BeforeHotPlugEventProc(_FALSE);
        }
        else
        {
            ScalerTmdsMacRx4BeforeHotPlugEventProc(_TRUE);
        }

        ucPortNum ++;
    }
#endif

    if(ucPortNum == 0)
    {
        return;
    }

    if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
    {
        // Actvie timer event to wait Z0 low
        for(ucI = 1; ucI <= ucPortNum; ucI ++)
        {
            if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
            {
                // Skip high process of this turn
                continue;
            }

            switch(pstTmdsHpdSeq[ucI].ucRXx)
            {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
                case _RX3:
                    ScalerTimerActiveTimerEvent(GET_HDMI_Z0_LOW_PERIOD(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_Z0_LOW_FINISH);
                    DebugMessageRx3("Z0 low time: ", GET_HDMI_Z0_LOW_PERIOD());
                    break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
                case _RX4:
                    ScalerTimerActiveTimerEvent(GET_HDMI_Z0_LOW_PERIOD(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_Z0_LOW_FINISH);
                    break;
#endif

                default:
                    break;
            }
        }
    }
    else // case of "HPD/Z0 at same time" or "HPD toggle before Z0"
    {
        // HPD Low Process
        for(ucI = 1; ucI <= ucPortNum; ucI ++)
        {
            if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
            {
                // Skip low process of this turn
                continue;
            }

            switch(pstTmdsHpdSeq[ucI].ucRXx)
            {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
                case _RX3:
                    ScalerTmdsMacRx3HotPlugLowProc();

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
                    ScalerTmdsMacRx3ScrambleStatusReset();
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                    // HPD Low then Reset Hdmi2.1
                    ScalerHdmiFrlMacRx3ResetProc();
#endif

                    // Active HPD Low timer event
                    ScalerTimerActiveTimerEvent(pstTmdsHpdSeq[ucI].usHpdTime, _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_LOW_FINISH);

                    break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
                case _RX4:
                    ScalerTmdsMacRx4HotPlugLowProc();

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
                    ScalerTmdsMacRx4ScrambleStatusReset();
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                    // HPD Low then Reset Hdmi2.1
                    ScalerHdmiFrlMacRx4ResetProc();
#endif

                    // Active HPD Low timer event
                    ScalerTimerActiveTimerEvent(pstTmdsHpdSeq[ucI].usHpdTime, _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_LOW_FINISH);
                    break;
#endif

                default:
                    break;
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : ScalerTMDSMacHdcp1p4AksvClear
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxHdcp14CableOutProc(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsMacRx3Hdcp1p4AksvClear();

            SET_TMDS_MAC_RX3_BACKUP_HDCP_TYPE(_HDCP_NONE);

            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsMacRx4Hdcp1p4AksvClear();

            SET_TMDS_MAC_RX4_BACKUP_HDCP_TYPE(_HDCP_NONE);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxScanInitial(EnumInputPort enumInputPort)
{
#if(_HDMI_FREESYNC_SUPPORT == _ON)
    ScalerTmdsMacRxSetFreesyncProc(enumInputPort, _DISABLE);
#endif

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
            CLR_TMDS_MAC_RX3_FS_VALUABLE();
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3ScanInitial(enumInputPort);
#endif
            ScalerTmdsMacRx3TMDSScanInitial(enumInputPort);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
            CLR_TMDS_MAC_RX4_FS_VALUABLE();
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4ScanInitial(enumInputPort);
#endif
            ScalerTmdsMacRx4TMDSScanInitial(enumInputPort);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS reset Timer Event
// Input Value  : enumInputPort  --> Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxTimerEventReset(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3TimerEventReset();
#endif
            ScalerTmdsMacRx3TimerEventReset();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4TimerEventReset();
#endif
            ScalerTmdsMacRx4TimerEventReset();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTmdsMacRxPSPreDetect(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            return (ScalerHdmiFrlMacRx3PSPreDetect() || ScalerTmdsMacRx3TMDSPSPreDetect());
#else
            return ScalerTmdsMacRx3TMDSPSPreDetect();
#endif
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            return (ScalerHdmiFrlMacRx4PSPreDetect() || ScalerTmdsMacRx4TMDSPSPreDetect());
#else
            return ScalerTmdsMacRx4TMDSPSPreDetect();
#endif

#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Signal PreDetection for TMDS(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTmdsMacRxNormalPreDetect(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if((_HDMI_RDC_TEST_TYPE_1_4 == _ON) || (_HDMI_RDC_TEST_TYPE_2_0 == _ON) || (_HDMI_RDC_TEST_TYPE_2_1 == _ON))
            ScalerTmdsPhyRx3RDCTestMode();
#endif
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            return (ScalerHdmiFrlMacRx3NormalPreDetect() || ScalerTmdsMacRx3TMDSNormalPreDetect());
#else
            return ScalerTmdsMacRx3TMDSNormalPreDetect();
#endif
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if((_HDMI_RDC_TEST_TYPE_1_4 == _ON) || (_HDMI_RDC_TEST_TYPE_2_0 == _ON) || (_HDMI_RDC_TEST_TYPE_2_1 == _ON))
            ScalerTmdsPhyRx4RDCTestMode();
#endif
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            return (ScalerHdmiFrlMacRx4NormalPreDetect() || ScalerTmdsMacRx4TMDSNormalPreDetect());
#else
            return ScalerTmdsMacRx4TMDSNormalPreDetect();
#endif
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
EnumSourceType ScalerTmdsMacRxScanInputPort(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                return ScalerHdmiFrlMacRx3ScanInputPort(enumPortType);
            }
            else
#endif
            {
                return ScalerTmdsMacRx3TMDSScanInputPort(enumPortType);
            }
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                return ScalerHdmiFrlMacRx4ScanInputPort(enumPortType);
            }
            else
#endif
            {
                return ScalerTmdsMacRx4TMDSScanInputPort(enumPortType);
            }
#endif

        default:
            return _SOURCE_NONE;
    }
}

//--------------------------------------------------
// Description  : TMDS Switch Slave Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSwitchHdcpSlaveAddr(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3SwitchHdcpSlaveAddr();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4SwitchHdcpSlaveAddr();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Freq. Detection IRQ Disable and Clear Clock Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxFreqDetectDisable(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3FreqDetectDisable();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4FreqDetectDisable();
            break;
#endif

        default:
            break;
    }
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Clr Colorimetry Changed
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerTmdsMacRxDigitalClrColorimetryChanged(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_RX3_COLORIMETRY_CHANGED();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_RX4_COLORIMETRY_CHANGED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clr ColorimetryExt Changed
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerTmdsMacRxDigitalClrColorimetryExtChanged(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_RX3_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_RX4_COLORIMETRY_EXT_CHANGED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clr ColorimetryChanged
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerTmdsMacRxDigitalClrQuantizationChanged(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_RX3_QUANTIZATION_CHANGED();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_RX4_QUANTIZATION_CHANGED();
            break;
#endif

        default:
            break;
    }
}
#endif
//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHdmiAVMuteProc(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                ScalerHdmiFrlMacRx3HdmiAVMuteProc();
            }
            else
#endif
            {
                ScalerTmdsMacRx3HdmiAVMuteProc();
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                ScalerHdmiFrlMacRx4HdmiAVMuteProc();
            }
            else
#endif
            {
                ScalerTmdsMacRx4HdmiAVMuteProc();
            }
            break;
#endif

        default:
            break;
    }
}

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
//--------------------------------------------------
// Description  : TMDS handle WD when no clk
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxNoClkWatchDogProc(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == 0x00)
            {
                ScalerTmdsMacRx3NoClkWatchDogProc();
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00)
            {
                ScalerTmdsMacRx4NoClkWatchDogProc();
            }
            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Hot Plug Low Process
// Input Value  : enumInputPort
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxHotPlugLowProc(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3HotPlugLowProc();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4HotPlugLowProc();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Hot Plug High Process
// Input Value  : enumInputPort, usHpdTime
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxHotPlugHighProc(EnumInputPort enumInputPort, WORD usHpdTime)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3HotPlugHighProc(usHpdTime);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4HotPlugHighProc(usHpdTime);
            break;
#endif

        default:
            break;
    }
}
//--------------------------------------------------
// Description  : TMDS After Hot Plug Event Process
// Input Value  : enumInputPort, bRestoreZ0
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxAfterHotPlugEventProc(EnumInputPort enumInputPort, bit bRestoreZ0)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3AfterHotPlugEventProc(bRestoreZ0);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4AfterHotPlugEventProc(bRestoreZ0);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Event Process
// Input Value  : None
// Output Value : Hot Plug time
//--------------------------------------------------
void ScalerTmdsMacRxHotPlugEvent(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3HotPlugEvent();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4HotPlugEvent();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : SET HPD EVENT
// Input Value  : RX Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetHPDTriggerEvent(EnumInputPort enumInputPort, EnumTMDSHpdEventType enumHpdEvent)
{
    enumHpdEvent = ((ScalerTmdsMacRxGetCableStatus(enumInputPort) == _TRUE) ? enumHpdEvent : _TMDS_MAC_RX_HPD_NONE);

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            SET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT(enumHpdEvent);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            SET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT(enumHpdEvent);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : GET HPD EVENT
// Input Value  : RX Port
// Output Value : None
//--------------------------------------------------
EnumTMDSHpdEventType ScalerTmdsMacRxGetHPDTriggerEvent(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT();
#endif

        default:
            return _TMDS_MAC_RX_HPD_NONE;
    }
}

//--------------------------------------------------
// Description  : CLR HPD EVENT
// Input Value  : RX Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxClrHPDTriggerEvent(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_TMDS_MAC_RX3_HPD_TRIGGER_EVENT();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_TMDS_MAC_RX4_HPD_TRIGGER_EVENT();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Freq Detect clock gating
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxFreqDetectClkGating(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3FreqDetectClkGating();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4FreqDetectClkGating();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxFirstActiveProc(EnumInputPort enumInputPort, EnumSourceType enumSourceType)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                ScalerHdmiFrlMacRx3FirstActiveProc(enumSourceType);
            }
            else
#endif
            {
                ScalerTmdsMacRx3FirstActiveProc(enumSourceType);
            }
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                ScalerHdmiFrlMacRx4FirstActiveProc(enumSourceType);
            }
            else
#endif
            {
                ScalerTmdsMacRx4FirstActiveProc(enumSourceType);
            }
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerTmdsMacRxHdcpEnabled(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerTmdsMacRx3HdcpEnabled();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerTmdsMacRx4HdcpEnabled();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : HDCP Bksv and Ri flag clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHdcpFlagClear(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3HdcpFlagClear();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4HdcpFlagClear();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : On Line Check TMDS stability
// Input Value  : enumSourceType --> Source Type
// Output Value : True --> TMDS Stable
//                False --> TMDS Unstable
//--------------------------------------------------
bit ScalerTmdsMacRxStableDetect(EnumInputPort enumInputPort, EnumSourceType enumSourceType)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
        case _RX3:
#if(_TMDS_MAC_RX3_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                return ScalerHdmiFrlMacRx3StableDetect(enumSourceType);
            }
            else
#endif
            {
                return ScalerTmdsMacRx3TMDSStableDetect(enumSourceType);
            }
#endif

        case _RX4:
#if(_TMDS_MAC_RX4_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                return ScalerHdmiFrlMacRx4StableDetect(enumSourceType);
            }
            else
#endif
            {
                return ScalerTmdsMacRx4TMDSStableDetect(enumSourceType);
            }
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : TMDS Power Saving Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPowerSavingProc(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3PowerSavingProc();
#endif
            ScalerTmdsMacRx3PowerSavingProc();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4PowerSavingProc();
#endif
            ScalerTmdsMacRx4PowerSavingProc();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPowerOffProc(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3PowerOffProc();
#endif
            ScalerTmdsMacRx3PowerOffProc();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4PowerOffProc();
#endif
            ScalerTmdsMacRx4PowerOffProc();
            break;
#endif

        default:
            break;
    }
}

#if((_HDMI_HDR10_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Get Current HDR data enable status
// Input Value  : D port
// Output Value : Rx status
//--------------------------------------------------
bit ScalerTmdsMacRxHDR10Status(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_HDMI_HDR10_INFO_FRAME_RECEIVED();
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxGetHDR10Data(EnumInputPort enumInputPort, BYTE *pucHDRData)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            GET_TMDSRX3_HDR10_DATA(pucHDRData);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            GET_TMDSRX4_HDR10_DATA(pucHDRData);
            break;
#endif

        default:
            break;
    }
}
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current HDR SBTM data enable status
// Input Value  : D port
// Output Value : Rx status
//--------------------------------------------------
bit ScalerTmdsMacRxHDR10SBTMStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_SBTM_RECEIVE();
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_SBTM_RECEIVE();
#endif
        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get TMDS HDR SBTM Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxGetHDR10SBTMData(EnumInputPort enumInputPort, BYTE *pucSBTMData)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            GET_TMDSRX3_HDR10_SBTM_DATA(pucSBTMData);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            GET_TMDSRX4_HDR10_SBTM_DATA(pucSBTMData);
            break;
#endif

        default:
            break;
    }
}

#endif
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync SDP Received Flag
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxGetSdpInfoFrameReceivedFlag(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxGetFreeSync2Data(EnumInputPort enumInputPort, BYTE *pucFreeSync2Data)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            GET_FREESYNC_II_TMDS_RX3_DATA(pucFreeSync2Data);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            GET_FREESYNC_II_TMDS_RX4_DATA(pucFreeSync2Data);
            break;
#endif

        default:
            break;
    }
}
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
DWORD ScalerTmdsMacRxFreeSyncHDMIGetAmdSpdInfo(EnumInputPort enumInputPort, EnumAmdSpdInfoContent enumContent)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_HDMI_RX3_AMD_SPD_INFO(enumContent);
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_HDMI_RX4_AMD_SPD_INFO(enumContent);
#endif

        default:
            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Backup HDCP Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxBackupHdcpType(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3BackupHdcpType();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4BackupHdcpType();
            break;
#endif

        default:
            break;
    }
}

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHdcp2ResetProc(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsHdcp2Rx3ResetProc();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsHdcp2Rx4ResetProc();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxHdcpMode(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_HDCP2_RX3_MODE();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_HDCP2_RX4_MODE();
#endif

        default:
            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Change HDCP Cap
// Input Value  : HDCP Type
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxAllPortChangeHdcpCap(EnumTmdsHdcpType enumTmdsHdcpType)
{
    switch(enumTmdsHdcpType)
    {
        case _HDCP_BY_PROJECT_DEFINE:

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
            // Set Rx3 Port HDCP Address is 0x74
            ScalerSetDataPortByte(P72_C3_HDCP_AP, _P72_C4_PT_C2_PORT_PAGE72_HDCP_SLAVE_ADD, 0x3A);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            // Set Support HDCP 2.2 Feature
            ScalerSetDataPortByte(P72_C3_HDCP_AP, _P72_C4_PT_50_PORT_PAGE72_HDCP2_VER, 0x04);
#endif
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
            // Set Rx4 Port HDCP Address is 0x74
            ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_C2_PORT_PAGE73_HDCP_SLAVE_ADD, 0x3A);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            // Set Support HDCP 2.2 Feature
            ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_50_PORT_PAGE73_HDCP2_VER, 0x04);
#endif
#endif
            break;

        case _TMDS_HDCP_14:

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
            // Set Rx3 Port HDCP Address is 0x74
            ScalerSetDataPortByte(P72_C3_HDCP_AP, _P72_C4_PT_C2_PORT_PAGE72_HDCP_SLAVE_ADD, 0x3A);

            // Set Not Support HDCP 2.2 Feature
            ScalerSetDataPortByte(P72_C3_HDCP_AP, _P72_C4_PT_50_PORT_PAGE72_HDCP2_VER, 0x00);
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
            // Set Rx4 Port HDCP Address is 0x74
            ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_C2_PORT_PAGE73_HDCP_SLAVE_ADD, 0x3A);

            // Set Not Support HDCP 2.2 Feature
            ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_50_PORT_PAGE73_HDCP2_VER, 0x00);
#endif
            break;

        case _TMDS_HDCP_NONE:

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
            ScalerTmdsMacRx3SwitchHdcpSlaveAddr();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
            ScalerTmdsMacRx4SwitchHdcpSlaveAddr();
#endif
            break;

        default:

            break;
    }
}

#if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS HPD IRQ Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHDMI2HPDRRIRQEnable(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3HDMI2HPDRRIRQEnable(bEnable);
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4HDMI2HPDRRIRQEnable(bEnable);
            break;
#endif

        default:
            break;
    }
}
#endif

#if(_HDMI20_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Scramble Status Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxScrambleStatusReset(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3ScrambleStatusReset();
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4ScrambleStatusReset();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Scramble Detection IRQ Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxScrambleDetectDisable(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3ScrambleDetectDisable();
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4ScrambleDetectDisable();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Set Scdc Info
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetScdcInfo(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3SetScdcInfo();
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4SetScdcInfo();
            break;
#endif
        default:
            break;
    }
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Set Scdc Info
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetAmdAupiScdcInfo(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsMacRx3SetAmdAupiScdcInfo(bEnable);
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsMacRx4SetAmdAupiScdcInfo(bEnable);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get HDMI FreeSync Support
// Input Value  : enumInputPort
// Output Value : _FREESYNC_SUPPORT_ON/ _FREESYNC_SUPPORT_OFF
//--------------------------------------------------
EnumFreeSyncSupport ScalerTmdsMacRxGetFreeSyncSupport(EnumInputPort enumInputPort)
{
    EnumFreeSyncSupport enumFreeSyncSupport = _FREESYNC_SUPPORT_OFF;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D0();
            break;

        case _D1_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D1();
            break;

        case _D2_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D2();
            break;

        case _D3_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D3();
            break;

        case _D4_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D4();
            break;

        case _D5_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D5();
            break;

        default:
            break;
    }

    return enumFreeSyncSupport;
}
#endif

//--------------------------------------------------
// Description  : TMDS Reset Scdc Info
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxResetScdcInfo(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            // Disable CED Lock Transition IRQ & Flag
            ScalerSetByte(P77_17_HDMI21_FRL_CED_15, 0xF0);

            // Disable CED Function and valid
            ScalerSetBit(P77_09_HDMI21_FRL_CED_1, ~_BIT6, 0x00);
            ScalerSetByte(P77_08_HDMI21_FRL_CED_0, 0x00);

            // Pop Up CED Error For Clear Error Counter
            ScalerSetByte(P77_0A_HDMI21_FRL_CED_2, 0x80);

            // Disable RSED update and clear RSED update flag
            ScalerSetBit(P68_13_HDMI21_RS_3, ~(_BIT7 | _BIT1), _BIT1);

            // Disable RSED Function and valid
            ScalerSetBit(P68_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
            ScalerSetBit(P68_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), 0x00);

            // Clear SCDC RS/CED Counter
            ScalerSetBit(P72_28_HDMI_CTRL_28, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
#endif

            // Disable TMDS CED Function & Lock Transition
            ScalerTmdsMacRx3SetCedLockTransition(_DISABLE);

            // Clear SCDC CED Counter
            ScalerSetBit(P72_28_HDMI_CTRL_28, ~(_BIT3 | _BIT1), _BIT1);

            // Reset SCDC
            ScalerSetBit(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            // Disable CED Lock Transition IRQ & Flag
            ScalerSetByte(P78_17_HDMI21_FRL_CED_15, 0xF0);

            // Disable CED Function and valid
            ScalerSetBit(P78_09_HDMI21_FRL_CED_1, ~_BIT6, 0x00);
            ScalerSetByte(P78_08_HDMI21_FRL_CED_0, 0x00);

            // Pop Up CED Error For Clear Error Counter
            ScalerSetByte(P78_0A_HDMI21_FRL_CED_2, 0x80);

            // Disable RSED update and clear RSED update flag
            ScalerSetBit(P69_13_HDMI21_RS_3, ~(_BIT7 | _BIT1), _BIT1);

            // Disable RSED Function and valid
            ScalerSetBit(P69_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
            ScalerSetBit(P69_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), 0x00);

            // Clear SCDC RS/CED Counter
            ScalerSetBit(P73_28_HDMI_CTRL_28, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
#endif

            // Disable TMDS CED Function & Lock Transition
            ScalerTmdsMacRx4SetCedLockTransition(_DISABLE);

            // Clear SCDC CED Counter
            ScalerSetBit(P73_28_HDMI_CTRL_28, ~(_BIT3 | _BIT1), _BIT1);

            // Reset SCDC
            ScalerSetBit(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Check Hpd 5V Pin
// Input Value  : enumInputPort, enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHpd5vPinCheckEvent(EnumInputPort enumInputPort, bit bEnable)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI20_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            if(bEnable == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_HDMI_D1_HPD_5VPIN_CHECK);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_D1_HPD_5VPIN_CHECK);

                CLR_D1_HDMI_5V_PIN_HIGH();
            }
            break;
#endif

#if(_D2_HDMI20_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            if(bEnable == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_HDMI_D2_HPD_5VPIN_CHECK);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_D2_HPD_5VPIN_CHECK);

                CLR_D2_HDMI_5V_PIN_HIGH();
            }
            break;
#endif

#if(_D3_HDMI20_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            if(bEnable == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_HDMI_D3_HPD_5VPIN_CHECK);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_D3_HPD_5VPIN_CHECK);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
                if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
                {
                    CLR_D3_HDMI_5V_PIN_HIGH();
                }
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
                {
                    CLR_D12_HDMI_5V_PIN_HIGH();
                }
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
                {
                    CLR_D13_HDMI_5V_PIN_HIGH();
                }
#endif
#else
                CLR_D3_HDMI_5V_PIN_HIGH();
#endif
            }
            break;
#endif

#if(_D4_HDMI20_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            if(bEnable == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_HDMI_D4_HPD_5VPIN_CHECK);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_D4_HPD_5VPIN_CHECK);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
                if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
                {
                    CLR_D4_HDMI_5V_PIN_HIGH();
                }
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
                {
                    CLR_D14_HDMI_5V_PIN_HIGH();
                }
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
                {
                    CLR_D15_HDMI_5V_PIN_HIGH();
                }
#endif
#else
                CLR_D4_HDMI_5V_PIN_HIGH();
#endif
            }
            break;
#endif

#if(_D5_HDMI20_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            if(bEnable == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_HDMI_D5_HPD_5VPIN_CHECK);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_D5_HPD_5VPIN_CHECK);

                CLR_D5_HDMI_5V_PIN_HIGH();
            }
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Check Hpd 5V Pin Check
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHpd5vPinCheck(EnumInputPort enumInputPort)
{
#if(_HDMI_5V_DETECT_BY_USER == _OFF)
    ScalerPinshareRxHpdPullDownSet(enumInputPort, _ENABLE);
#endif

    DELAY_XUS(500);

#if(_HDMI_5V_DETECT_BY_USER == _ON)
    if((ScalerTmdsMacRx5vPinDetectByUser(enumInputPort) == _HDMI_5V_STATUS_HIGH) && (ScalerTmdsMacRxGetHpd5vPinHighFlag(enumInputPort) == _FALSE))
#else
    if((ScalerTmdsMacRxHpd5vPinDetect(enumInputPort) == _HDMI_5V_STATUS_HIGH) && (ScalerTmdsMacRxGetHpd5vPinHighFlag(enumInputPort) == _FALSE))
#endif
    {
        if(ScalerTmdsMacRxGetCableStatus(enumInputPort) == _TRUE)
        {
            ScalerTmdsMacRxSetScdcInfo(enumInputPort);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
            if(ScalerTmdsMacRxGetFreeSyncSupport(enumInputPort) == _FREESYNC_SUPPORT_ON)
            {
                ScalerTmdsMacRxSetAmdAupiScdcInfo(enumInputPort, _ENABLE);
            }
            else
            {
                ScalerTmdsMacRxSetAmdAupiScdcInfo(enumInputPort, _DISABLE);
            }
#endif
        }

        ScalerTmdsMacRxSetHpd5vPinHighFlag(enumInputPort, _ON);
    }
#if(_HDMI_5V_DETECT_BY_USER == _ON)
    else if((ScalerTmdsMacRx5vPinDetectByUser(enumInputPort) == _HDMI_5V_STATUS_LOW) && (ScalerTmdsMacRxGetHpd5vPinHighFlag(enumInputPort) == _TRUE))
#else
    else if((ScalerTmdsMacRxHpd5vPinDetect(enumInputPort) == _HDMI_5V_STATUS_LOW) && (ScalerTmdsMacRxGetHpd5vPinHighFlag(enumInputPort) == _TRUE))
#endif
    {
        ScalerTmdsMacRxResetScdcInfo(enumInputPort);

        // 5V Low then Reset Scramble Status
        ScalerTmdsMacRxScrambleStatusReset(enumInputPort);

#if(_HDMI_FRL_SUPPORT == _ON)
        // 5V Low then Reset FRL Link Training
        ScalerHdmiFrlMacRxResetProc(enumInputPort);
#endif
        // Reload SCDC Info
        ScalerTmdsMacRxSetScdcInfo(enumInputPort);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
        if(ScalerTmdsMacRxGetFreeSyncSupport(enumInputPort) == _FREESYNC_SUPPORT_ON)
        {
            ScalerTmdsMacRxSetAmdAupiScdcInfo(enumInputPort, _ENABLE);
        }
        else
        {
            ScalerTmdsMacRxSetAmdAupiScdcInfo(enumInputPort, _DISABLE);
        }
#endif

        ScalerTmdsMacRxSetHpd5vPinHighFlag(enumInputPort, _OFF);
    }

    ScalerTmdsMacRxHpd5vPinCheckEvent(enumInputPort, _ENABLE);

#if(_HDMI_5V_DETECT_BY_USER == _OFF)
    ScalerPinshareRxHpdPullDownSet(enumInputPort, _DISABLE);
#endif
}

//--------------------------------------------------
// Description  : SET RX HPD 5V Pin Flag
// Input Value  : enumInputPort/_ON,_OFF
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetHpd5vPinHighFlag(EnumInputPort enumInputPort, bit bValue)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI20_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            if(bValue == _ON)
            {
                SET_D1_HDMI_5V_PIN_HIGH();
            }
            else
            {
                CLR_D1_HDMI_5V_PIN_HIGH();
            }
            break;
#endif

#if(_D2_HDMI20_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            if(bValue == _ON)
            {
                SET_D2_HDMI_5V_PIN_HIGH();
            }
            else
            {
                CLR_D2_HDMI_5V_PIN_HIGH();
            }
            break;
#endif

#if(_D3_HDMI20_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            if(bValue == _ON)
            {
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3)) || ((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))))
                if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
                {
                    SET_D3_HDMI_5V_PIN_HIGH();
                }
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
                {
                    SET_D12_HDMI_5V_PIN_HIGH();
                }
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
                {
                    SET_D13_HDMI_5V_PIN_HIGH();
                }
#endif
#else
                SET_D3_HDMI_5V_PIN_HIGH();
#endif
            }
            else
            {
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3)) || ((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))))
                if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
                {
                    CLR_D3_HDMI_5V_PIN_HIGH();
                }
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
                {
                    CLR_D12_HDMI_5V_PIN_HIGH();
                }
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
                {
                    CLR_D13_HDMI_5V_PIN_HIGH();
                }
#endif
#else
                CLR_D3_HDMI_5V_PIN_HIGH();
#endif
            }
            break;
#endif

#if(_D4_HDMI20_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            if(bValue == _ON)
            {
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4)) || ((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))))
                if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
                {
                    SET_D4_HDMI_5V_PIN_HIGH();
                }
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
                {
                    SET_D14_HDMI_5V_PIN_HIGH();
                }
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
                {
                    SET_D15_HDMI_5V_PIN_HIGH();
                }
#endif
#else
                SET_D4_HDMI_5V_PIN_HIGH();
#endif
            }
            else
            {
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4)) || ((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))))
                if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
                {
                    CLR_D4_HDMI_5V_PIN_HIGH();
                }
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
                {
                    CLR_D14_HDMI_5V_PIN_HIGH();
                }
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
                {
                    CLR_D15_HDMI_5V_PIN_HIGH();
                }
#endif
#else
                CLR_D4_HDMI_5V_PIN_HIGH();
#endif
            }
            break;
#endif

#if(_D5_HDMI20_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            if(bValue == _ON)
            {
                SET_D5_HDMI_5V_PIN_HIGH();
            }
            else
            {
                CLR_D5_HDMI_5V_PIN_HIGH();
            }
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : GET RX HPD 5V Pin Flag
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxGetHpd5vPinHighFlag(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI20_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_D1_HDMI_5V_PIN_HIGH();
            break;
#endif

#if(_D2_HDMI20_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_D2_HDMI_5V_PIN_HIGH();
            break;
#endif

#if(_D3_HDMI20_SUPPORT == _ON)
        case _D3_INPUT_PORT:
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3)) || ((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))))
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
            {
                return GET_D3_HDMI_5V_PIN_HIGH();
            }
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
            {
                return GET_D12_HDMI_5V_PIN_HIGH();
            }
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
            {
                return GET_D13_HDMI_5V_PIN_HIGH();
            }
#endif
#else
            return GET_D3_HDMI_5V_PIN_HIGH();
#endif
            break;
#endif

#if(_D4_HDMI20_SUPPORT == _ON)
        case _D4_INPUT_PORT:
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4)) || ((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))))
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
            {
                return GET_D4_HDMI_5V_PIN_HIGH();
            }
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
            {
                return GET_D14_HDMI_5V_PIN_HIGH();
            }
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
            {
                return GET_D15_HDMI_5V_PIN_HIGH();
            }
#endif
#else
            return GET_D4_HDMI_5V_PIN_HIGH();
#endif
            break;
#endif

#if(_D5_HDMI20_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return GET_D5_HDMI_5V_PIN_HIGH();
            break;
#endif
        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Detect HPD 5V Pin
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
EnumUserHdmi5vStatus ScalerTmdsMacRxHpd5vPinDetect(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            // Check Hot Plug 5V
            if(ScalerGetBit(P72_23_HDMI_CTRL_23, _BIT0) == _BIT0)
            {
                return _HDMI_5V_STATUS_HIGH;
            }
            else
            {
                return _HDMI_5V_STATUS_LOW;
            }
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            // Check Hot Plug 5V
            if(ScalerGetBit(P73_23_HDMI_CTRL_23, _BIT0) == _BIT0)
            {
                return _HDMI_5V_STATUS_HIGH;
            }
            else
            {
                return _HDMI_5V_STATUS_LOW;
            }
            break;
#endif
        default:
            return _HDMI_5V_STATUS_LOW;
    }
}

//--------------------------------------------------
// Description  : Scdc Enable Setting
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxAllPortScdcEnableSetting(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable HDMI 2.0 SCDC Function
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        ScalerSetBit(P72_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
#endif
#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
#endif
    }
    else
    {
        // Disable HDMI 2.0 SCDC Function
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        ScalerSetBit(P72_19_HDMI_CTRL_19, ~_BIT7, 0x00);
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, 0x00);
#endif
    }
}

#if(_HDMI_5V_DETECT_BY_USER == _ON)
//--------------------------------------------------
// Description  : TMDS Detect 5V Pin
// Input Value  : enumInputPort
// Output Value : _High/_low
//--------------------------------------------------
EnumUserHdmi5vStatus ScalerTmdsMacRx5vPinDetectByUser(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return g_stTmdsMacRx5vStatusByUser.b1D15vStatusByUser;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return g_stTmdsMacRx5vStatusByUser.b1D25vStatusByUser;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
            {
                return g_stTmdsMacRx5vStatusByUser.b1D35vStatusByUser;
            }
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
            {
                return g_stTmdsMacRx5vStatusByUser.b1D125vStatusByUser;
            }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
            {
                return g_stTmdsMacRx5vStatusByUser.b1D135vStatusByUser;
            }
#endif
#else
            return g_stTmdsMacRx5vStatusByUser.b1D35vStatusByUser;
#endif
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
            {
                return g_stTmdsMacRx5vStatusByUser.b1D45vStatusByUser;
            }
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
            {
                return g_stTmdsMacRx5vStatusByUser.b1D145vStatusByUser;
            }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
            {
                return g_stTmdsMacRx5vStatusByUser.b1D155vStatusByUser;
            }
#endif
#else
            return g_stTmdsMacRx5vStatusByUser.b1D45vStatusByUser;
#endif
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return g_stTmdsMacRx5vStatusByUser.b1D55vStatusByUser;
#endif
        default:
            return 0x00;
    }
}
#endif

#if((_AUDIO_EARC_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP))
//--------------------------------------------------
// Description  : eARC Tx Enable HPD Detect Rising IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxEnableHpdDetectRisingIrq(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : eARC Tx Enable HPD Detect Falling IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxEnableHpdDetectFallingIrq(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : eARC Tx Disable HPD Detect IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxDisableHpdDetectIrq(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            // Disable HPD Detect IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT1);
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            // Disable HPD Detect IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT1);
            break;
#endif
        default:
            break;
    }
}
#endif
#endif

//--------------------------------------------------
// Description  : SET RX port PIXEL CLK
// Input Value  : RX Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetInputPixel(EnumInputPort enumInputPort, WORD usPixel)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_D1_INPUT_PIXEL_CLK(usPixel);
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_D2_INPUT_PIXEL_CLK(usPixel);
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_D3_INPUT_PIXEL_CLK(usPixel);
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_D4_INPUT_PIXEL_CLK(usPixel);
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            SET_D5_INPUT_PIXEL_CLK(usPixel);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : WORD  (0.1 MHz)
//--------------------------------------------------
WORD ScalerTmdsMacRxGetInputPixel(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_D1_INPUT_PIXEL_CLK();
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_D2_INPUT_PIXEL_CLK();
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_D3_INPUT_PIXEL_CLK();
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_D4_INPUT_PIXEL_CLK();
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return GET_D5_INPUT_PIXEL_CLK();
#endif
        default:
            return 0x00;
    }
}

//--------------------------------------------------
// Description  : SET RX port HPD
// Input Value  : RX Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetDxHPD(EnumInputPort enumInputPort, BYTE ucValue)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            if(ucValue == _HIGH)
            {
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
            }
            else
            {
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
            }
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            if(ucValue == _HIGH)
            {
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
            }
            else
            {
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
            }
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            if(ucValue == _HIGH)
            {
                PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
            }
            else
            {
                PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
            }
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            if(ucValue == _HIGH)
            {
                PCB_D4_HOTPLUG(_D4_HOT_PLUG_HIGH);
            }
            else
            {
                PCB_D4_HOTPLUG(_D4_HOT_PLUG_LOW);
            }
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            if(ucValue == _HIGH)
            {
                PCB_D5_HOTPLUG(_D5_HOT_PLUG_HIGH);
            }
            else
            {
                PCB_D5_HOTPLUG(_D5_HOT_PLUG_LOW);
            }
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : SET RX port HPD
// Input Value  : RX Port
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxGetCableStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return GET_D0_CABLE_STATUS();
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_D1_CABLE_STATUS();
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_D2_CABLE_STATUS();
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT))
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
            {
                return GET_D3_CABLE_STATUS();
            }
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
            {
                return GET_D12_CABLE_STATUS();
            }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
            {
                return GET_D13_CABLE_STATUS();
            }
#endif
            else
            {
                return _FALSE;
            }
#else
            return GET_D3_CABLE_STATUS();
#endif
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT))
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
            {
                return GET_D4_CABLE_STATUS();
            }
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
            {
                return GET_D14_CABLE_STATUS();
            }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
            {
                return GET_D15_CABLE_STATUS();
            }
#endif
            else
            {
                return _FALSE;
            }
#else
            return GET_D4_CABLE_STATUS();
#endif
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return GET_D5_CABLE_STATUS();
#endif
        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : SET RX port HPD
// Input Value  : RX Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetDigitalPort(EnumInputPort enumInputPort, BYTE ucHL)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            if(ucHL == _HIGH)
            {
                SET_DIGITAL_PORT_SWITCH_TO_D1();
            }
            else if (ucHL == _LOW)
            {
                CLR_DIGITAL_PORT_SWITCH_TO_D1();
            }
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            if(ucHL == _HIGH)
            {
                SET_DIGITAL_PORT_SWITCH_TO_D2();
            }
            else if (ucHL == _LOW)
            {
                CLR_DIGITAL_PORT_SWITCH_TO_D2();
            }
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            if(ucHL == _HIGH)
            {
                SET_DIGITAL_PORT_SWITCH_TO_D3();
            }
            else if (ucHL == _LOW)
            {
                CLR_DIGITAL_PORT_SWITCH_TO_D3();
            }
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            if(ucHL == _HIGH)
            {
                SET_DIGITAL_PORT_SWITCH_TO_D4();
            }
            else if (ucHL == _LOW)
            {
                CLR_DIGITAL_PORT_SWITCH_TO_D4();
            }
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            if(ucHL == _HIGH)
            {
                SET_DIGITAL_PORT_SWITCH_TO_D5();
            }
            else if (ucHL == _LOW)
            {
                CLR_DIGITAL_PORT_SWITCH_TO_D5();
            }
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : GET RX port Digital port status(z0)
// Input Value  : Inputport
// Output Value : bit
//--------------------------------------------------
bit ScalerTmdsMacRxGetDigitalPort(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_DIGITAL_PORT_SWITCH_TO_D1();
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_DIGITAL_PORT_SWITCH_TO_D2();
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_DIGITAL_PORT_SWITCH_TO_D3();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_DIGITAL_PORT_SWITCH_TO_D4();
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return GET_DIGITAL_PORT_SWITCH_TO_D5();
            break;
#endif

        default:
            return _FALSE;
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx1 or Rx2 or Rx3
//--------------------------------------------------
EnumRx ScalerTmdsMacRxDxRxMapping(EnumInputPort enumInputPort)
{
    return ScalerTmdsMacRxPhyMacMapping(ScalerTmdsPhyRxDxRxMapping(enumInputPort));
}

//--------------------------------------------------
// Description  : TMDS Port Dx mapping to Rx
// Input Value  : Rx Port
// Output Value : Dx port
//--------------------------------------------------
EnumInputPort ScalerTmdsMacRxRxDxMapping(EnumRx enumRx)
{
    return ScalerTmdsPhyRxRxDxMapping(ScalerTmdsMacRxMacPhyMapping(enumRx));
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HDMI Rx FreesyncEnable
// Input Value  : Dx Port, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetFreesyncProc(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_HDMI_D0_ENABLED();
            }
            else
            {
                CLR_FREESYNC_HDMI_D0_ENABLED();
            }

            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_HDMI_D1_ENABLED();
            }
            else
            {
                CLR_FREESYNC_HDMI_D1_ENABLED();
            }

            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_HDMI_D2_ENABLED();
            }
            else
            {
                CLR_FREESYNC_HDMI_D2_ENABLED();
            }

            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_HDMI_D3_ENABLED();
            }
            else
            {
                CLR_FREESYNC_HDMI_D3_ENABLED();
            }

            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_HDMI_D4_ENABLED();
            }
            else
            {
                CLR_FREESYNC_HDMI_D4_ENABLED();
            }

            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_HDMI_D5_ENABLED();
            }
            else
            {
                CLR_FREESYNC_HDMI_D5_ENABLED();
            }

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get HDMI Rx FreesyncEnable
// Input Value  : Rx port
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxGetFreesyncEnableFlag(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_FREESYNC_HDMI_D0_ENABLED();
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_FREESYNC_HDMI_D1_ENABLED();
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_FREESYNC_HDMI_D2_ENABLED();
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            return GET_FREESYNC_HDMI_D3_ENABLED();
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            return GET_FREESYNC_HDMI_D4_ENABLED();
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            return GET_FREESYNC_HDMI_D5_ENABLED();
#endif
        default:

            return 0x00;
    }
}
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get DM Support flag
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxGetOsdDmSupport(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_D3_DM_SUPPORT();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_D4_DM_SUPPORT();
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get ALLM feature Enable Status
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxGetHdmi21AllmStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED();
            break;
#endif
#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();
            break;
#endif
        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : CLR ALLM feature Enable Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxClrHdmi21AllmStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED();
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();
            break;
#endif

        default:
            break;
    }
}

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set ALLM feature Enable Status (DM use)
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetDmAllmStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_D3_DM_ALLM_ENABLED();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_D4_DM_ALLM_ENABLED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clear ALLM feature Enable Status (DM use)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxClrDmAllmStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            CLR_D3_DM_ALLM_ENABLED();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            CLR_D4_DM_ALLM_ENABLED();
            break;
#endif

        default:
            break;
    }
}
#endif
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get 3D Video valid
// Input Value  : enumInputPort
// Output Value : Bit
//--------------------------------------------------
bit ScalerTmdsMacRxGet3dVideoValid(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID();
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS EDID Switch
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxEdidSwitch(EnumInputPort enumInputPort, EnumTMDSHpdEventType enumHpdEventType)
{
    enumHpdEventType = enumHpdEventType;

    switch(enumInputPort)
    {
        // For User, DVI and DUAL_DVI Port can not pull HPD
#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
        case _D0_INPUT_PORT:
            ScalerTmdsMacRxSetHPDTriggerEvent(_D0_INPUT_PORT, enumHpdEventType);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
        case _D1_INPUT_PORT:
            ScalerTmdsMacRxSetHPDTriggerEvent(_D1_INPUT_PORT, enumHpdEventType);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
        case _D2_INPUT_PORT:
            ScalerTmdsMacRxSetHPDTriggerEvent(_D2_INPUT_PORT, enumHpdEventType);
            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
        case _D3_INPUT_PORT:
            ScalerTmdsMacRxSetHPDTriggerEvent(_D3_INPUT_PORT, enumHpdEventType);
            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
        case _D4_INPUT_PORT:
            ScalerTmdsMacRxSetHPDTriggerEvent(_D4_INPUT_PORT, enumHpdEventType);
            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
        case _D5_INPUT_PORT:
            ScalerTmdsMacRxSetHPDTriggerEvent(_D5_INPUT_PORT, enumHpdEventType);
            break;
#endif
        default:

            break;
    }
}
#endif // End of #if(_HDMI_MULTI_EDID_SUPPORT == _ON)

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
//--------------------------------------------------
// Description  : Check DDC channel Idle
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxDdcCheckBusy(EnumInputPort enumInputPort, EnumTMDSDdcDebounceType enumTmdsDdcDebounceType, BYTE ucDebounceTimeScale, WORD usDebounceTimePeriod)
{
    WORD ustemp = 0;

    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable(_DDC0, _DISABLE);

            if(enumTmdsDdcDebounceType == _DELAY_20US_TIMESCALE)
            {
                // Set a Polling Duration: 20us*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay Time us [25,x] for IIC 100k
                    DELAY_25US();

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC0) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC0);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
            {
                // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay (ucDebounceTimeScale) ms for IIC 100k
                    ScalerTimerDelayXms(ucDebounceTimeScale);

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC0) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC0);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _TRUE;
            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable(_DDC1, _DISABLE);

            if(enumTmdsDdcDebounceType == _DELAY_20US_TIMESCALE)
            {
                // Set a Polling Duration: 20us*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay Time us [25,x] for IIC 100k
                    DELAY_25US();

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC1) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC1);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
            {
                // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay (ucDebounceTimeScale) ms for IIC 100k
                    ScalerTimerDelayXms(ucDebounceTimeScale);

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC1) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC1);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _TRUE;
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable(_DDC2, _DISABLE);

            if(enumTmdsDdcDebounceType == _DELAY_20US_TIMESCALE)
            {
                // Set a Polling Duration: 20us*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay Time us [25,x] for IIC 100k
                    DELAY_25US();

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC2) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC2);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
            {
                // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay (ucDebounceTimeScale) ms for IIC 100k
                    ScalerTimerDelayXms(ucDebounceTimeScale);

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC2) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC2);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _TRUE;
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable(_DDC3, _DISABLE);

            if(enumTmdsDdcDebounceType == _DELAY_20US_TIMESCALE)
            {
                // Set a Polling Duration: 20us*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay Time us [25,x] for IIC 100k
                    DELAY_25US();

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC3) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC3);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
            {
                // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay (ucDebounceTimeScale) ms for IIC 100k
                    ScalerTimerDelayXms(ucDebounceTimeScale);

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC3) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC3);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _TRUE;
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable(_DDC4, _DISABLE);

            if(enumTmdsDdcDebounceType == _DELAY_20US_TIMESCALE)
            {
                // Set a Polling Duration: 20us*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay Time us [25,x] for IIC 100k
                    DELAY_25US();

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC4) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC4);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
            {
                // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay (ucDebounceTimeScale) ms for IIC 100k
                    ScalerTimerDelayXms(ucDebounceTimeScale);

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC4) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC4);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _TRUE;
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable(_DDC5, _DISABLE);

            if(enumTmdsDdcDebounceType == _DELAY_20US_TIMESCALE)
            {
                // Set a Polling Duration: 20us*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay Time us [25,x] for IIC 100k
                    DELAY_25US();

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC5) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC5);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
            {
                // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                {
                    // Delay (ucDebounceTimeScale) ms for IIC 100k
                    ScalerTimerDelayXms(ucDebounceTimeScale);

                    if(ScalerMcuDdcGetSclToggleIrqStatus(_DDC5) == _TRUE)
                    {
                        ScalerMcuDdcClearSclToggleIrqStatus(_DDC5);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _TRUE;
            break;
#endif
        default:

            return _TRUE;
            break;
    }
    return _TRUE;
}
#endif // End of #if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : InputPort and Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTmdsMacRxHdmiGetAVIInfo(EnumInputPort enumInputPort, EnumAviInfoContent enumContent)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                if(enumContent == _AVI_INFO_ADD_EXTENDED_COLORIMETRY)
                {
                    return ScalerHdmiFrlMacRx3Rsv6GetAviInfo(enumContent);
                }
                else
                {
                    return ScalerHdmiFrlMacRx3GetAVIInfo(enumContent);
                }
            }
            else
#endif
            {
                if(enumContent == _AVI_INFO_ADD_EXTENDED_COLORIMETRY)
                {
                    return ScalerTmdsMacRx3HdmiRsv6GetAviInfo(enumContent);
                }
                else
                {
                    return ScalerTmdsMacRx3HdmiGetAVIInfo(enumContent);
                }
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                if(enumContent == _AVI_INFO_ADD_EXTENDED_COLORIMETRY)
                {
                    return ScalerHdmiFrlMacRx4Rsv6GetAviInfo(enumContent);
                }
                else
                {
                    return ScalerHdmiFrlMacRx4GetAVIInfo(enumContent);
                }
            }
            else
#endif
            {
                if(enumContent == _AVI_INFO_ADD_EXTENDED_COLORIMETRY)
                {
                    return ScalerTmdsMacRx4HdmiRsv6GetAviInfo(enumContent);
                }
                else
                {
                    return ScalerTmdsMacRx4HdmiGetAVIInfo(enumContent);
                }
            }
            break;
#endif

        default:

            break;
    }

    return 0xFF;
}

//--------------------------------------------------
// Description  : Get HDMI AVI Content Type
// Input Value  : InputPort
// Output Value : Content Type Info
//--------------------------------------------------
EnumContentType ScalerTmdsMacRxHdmiGetAviContentTypeInfo(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                ScalerHdmiFrlMacRx3GetAviContentType();
            }
            else
#endif
            {
                ScalerTmdsMacRx3HdmiGetAviContentType();
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                ScalerHdmiFrlMacRx4GetAviContentType();
            }
            else
#endif
            {
                ScalerTmdsMacRx4HdmiGetAviContentType();
            }
            break;
#endif

        default:

            break;
    }

    return 0x00;
}

#if(_HDMI_IDENTIFY_GAME_SRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI SPD Info Contents
// Input Value  : InputPort
// Output Value : Content Value
//--------------------------------------------------
StructHdmiSpdInfo ScalerTmdsMacRxHdmiGetSpdInfo(EnumInputPort enumInputPort)
{
    StructHdmiSpdInfo stSpdInfo = {0};

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:

            return g_stTmdsMacRx3SpdInfo;
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:

            return g_stTmdsMacRx4SpdInfo;
            break;
#endif

        default:
            break;
    }

    return stSpdInfo;
}
#endif

#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get HDMI2.1 VTEM PKT Receive
// Input Value  : None
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
bit ScalerTmdsMacRxGetHdmi21VtemReceived(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            if(GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED() == _TRUE)
            {
                return _TRUE;
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
            {
                return _TRUE;
            }
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

#if(_HDMI21_VRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI2.1 VTEM's VRR feature
// Input Value  : None
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
bit ScalerTmdsMacRxGetHdmi21VrrStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            if(GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED() == _TRUE)
            {
                return _TRUE;
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
            {
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
// Description  : Get VTEM VRR_EN status
// Input Value  : None
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
bit ScalerTmdsMacRxGetVrrEnStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            if(GET_TMDS_MAC_RX3_HDMI21_VRR_EN() == _TRUE)
            {
                return _TRUE;
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            if(GET_TMDS_MAC_RX4_HDMI21_VRR_EN() == _TRUE)
            {
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
// Description  : Get VTEM QMS_EN status
// Input Value  : None
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
bit ScalerTmdsMacRxGetQmsEnStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            if(GET_TMDS_MAC_RX3_HDMI21_QMS_EN() == _TRUE)
            {
                return _TRUE;
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            if(GET_TMDS_MAC_RX4_HDMI21_QMS_EN() == _TRUE)
            {
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
// Description  : Set EDID VRR Capability
// Input Value  : EnumInputPort, StructHdmi21EdidVrrCap
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetEdidVrrCapability(EnumInputPort enumInputPort, StructHdmi21EdidVrrCap stEdidVrrCap)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            memcpy(&g_stTmdsMacRx3Hdmi21EdidVrrCap, &stEdidVrrCap, sizeof(StructHdmi21EdidVrrCap));
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            memcpy(&g_stTmdsMacRx4Hdmi21EdidVrrCap, &stEdidVrrCap, sizeof(StructHdmi21EdidVrrCap));
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clr EDID VRR Capability
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxClrEdidVrrCapability(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            memset(&g_stTmdsMacRx3Hdmi21EdidVrrCap, 0, sizeof(StructHdmi21EdidVrrCap));
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            memset(&g_stTmdsMacRx4Hdmi21EdidVrrCap, 0, sizeof(StructHdmi21EdidVrrCap));
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Clear HDMI2.1 VTEM PKT Receive
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxClrHdmi21VtemReceived(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED();
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
            break;
#endif

        default:
            break;
    }
}

#if(_HDMI21_FVA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI21 FVA Factor from VTEM
// Input Value  : enumInputPort
// Output Value : BYTE
//--------------------------------------------------
BYTE ScalerTmdsMacRxHdmi21GetFvaFactor(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:

            return GET_TMDS_MAC_RX3_HDMI21_FVA_FACTOR();

            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:

            return GET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR();

            break;
#endif

        default:

            break;
    }

    return 0x01;
}

//--------------------------------------------------
// Description  : Cal the Max IVf may sent
// Input Value  : pucReadArray: EDID address, usPixelClk: Input pixel clk(0.1M)
// Output Value : _TRUE: Get IVF, unit: 0.1Hz
//--------------------------------------------------
WORD ScalerTmdsMacRxCalFvaVfreqMax(StructEdidInfo *pstCatchEdidInfo, BYTE ucFavFactor)
{
    // ------------------------------------------------------------------------------------------------------
    // IVf_max = Pixel Rate * FVA_Factor / (Htotal * ((Vtotal * FVA_Factor) - Vactive * (FVA_Factor - 1)))
    // ------------------------------------------------------------------------------------------------------
    WORD usVfreq = 0x00;
    WORD usMinVtotal = (pstCatchEdidInfo->usVtotal * ucFavFactor) - (pstCatchEdidInfo->usVheight * (ucFavFactor - 1));

    usVfreq = ((GET_DWORD_MUL_DIV(pstCatchEdidInfo->usPixelClk, 1000000, usMinVtotal) + (pstCatchEdidInfo->usHtotal / 2)) / pstCatchEdidInfo->usHtotal);
    usVfreq *= ucFavFactor;

    return usVfreq;
}
#endif
#endif

//--------------------------------------------------
// Description  : Get Vfreq from VIC Field of AVI IF
// Input Value  : Vic Index
// Output Value : Vfreq
//--------------------------------------------------
BYTE ScalerTmdsMacRxGetVicVfreqParameter(BYTE ucVicIndex)
{
    BYTE  ucVicVfreq = 0x00;

    if(ucVicIndex != 0x00)
    {
        ucVicVfreq = tVIC_VFREQ_TABLE[ucVicIndex - 1];
    }

    return ucVicVfreq;
}

//--------------------------------------------------
// Description  : Get Vfreq from FR Field of AVI IF
// Input Value  : Vic Index
// Output Value : Vfreq
//--------------------------------------------------
WORD ScalerTmdsMacRxGetOvtVfreqParameter(BYTE ucFrIndex)
{
    if(ucFrIndex == 0)
    {
        return 0;
    }

    ucFrIndex -= 1;

    if(ucFrIndex >= 24)
    {
        return 0;
    }

    return tOVT_FR_TABLE[ucFrIndex].usFramRate;
}

//--------------------------------------------------
// Description  : Set Ps Wakeup HPD Flag due to DDCCI PS Case
// Input Value  : enumInputPort
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxSetPsWakeupHpdToggle(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            SET_TMDS_MAC_RX3_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            SET_TMDS_MAC_RX4_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Ps Wakeup HPD Flag due to DDCCI PS Case
// Input Value  : enumInputPort
// Output Value : bit
//--------------------------------------------------
bit ScalerTmdsMacRxGetPsWakeupHpdStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

        default:

            return _FALSE;
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear Ps Wakeup HPD Flag due to DDCCI PS Case
// Input Value  : enumInputPort
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxClrPsWakeupHpdStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_TMDS_MAC_RX3_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_TMDS_MAC_RX4_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

        default:
            break;
    }
}

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
//--------------------------------------------------
// Description  : Clear Ps Wakeup HPD Flag due to DDCCI PS Case
// Input Value  : enumInputPort
// Output Value :
//--------------------------------------------------
bit ScalerTmdsMacRxGetToggleZ0Event(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_TOGGLE_Z0_EVENT();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_TOGGLE_Z0_EVENT();
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Check Hdmi2.1 Add Reactive Time after Link Training Pass
// Input Value  :
// Output Value : _TRUE to add reactive time
//--------------------------------------------------
bit ScalerTmdsMacRxReactiveSearchTimeCheck(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
            if(GET_HDMI_MAC_RX3_INTERFACE_SWITCHING() == _TRUE)
            {
                return _TRUE;
            }
#endif

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING() == _TRUE)
            {
                return _TRUE;
            }
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_FRL_MAC_RX3_REACTIVE_SEARCH_TIME() == _TRUE)
            {
                CLR_HDMI_FRL_MAC_RX3_REACTIVE_SEARCH_TIME();
                return _TRUE;
            }
            return _FALSE;
#endif
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
            if(GET_HDMI_MAC_RX4_INTERFACE_SWITCHING() == _TRUE)
            {
                return _TRUE;
            }
#endif

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_ACTIVE_TYPE_HPD_TOGGLING() == _TRUE)
            {
                return _TRUE;
            }
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(GET_HDMI_FRL_MAC_RX4_REACTIVE_SEARCH_TIME() == _TRUE)
            {
                CLR_HDMI_FRL_MAC_RX4_REACTIVE_SEARCH_TIME();
                return _TRUE;
            }
            return _FALSE;
#endif
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Reactive Time
// Input Value  : EnumInputPort
// Output Value : Reactive time
//--------------------------------------------------
WORD ScalerTmdsMacRxGetReactiveSearchTime(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_HDMI_FRL_SUPPORT == _ON)
    if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC)
    {
        return _SOURCE_DEFAULT_SEARCH_TIME_HDMI_FRL;
    }
    else
#endif
    {
        return SEC(4.5);
    }
}

//--------------------------------------------------
// Description  : TMDS MAC power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPowerProc(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
#if((_AUDIO_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Ignore Power Control when in Audio Pattern Gen
    if(ScalerAudioGetInternalAudioGenEnable(enumInputPort) == _ENABLE)
    {
        return;
    }
#endif

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
        case _RX_MAP_NONE:

            return;

            break;

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            switch(enumPowerAction)
            {
                case _POWER_ACTION_NORMAL_TO_OFF:
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX3_HDMI20_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX3_HDMI21_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
#endif
                    break;

                case _POWER_ACTION_OFF_TO_NORMAL:
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX3_HDMI20_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
                    CLR_TMDS_MAC_RX3_RETRY_SET_PHY();
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX3_HDMI21_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

#if(_AUDIO_SUPPORT == _ON)
                    // Choose HDMI2.0 Mac as Default
                    SET_HDMI_AUDIO_RX3_VERSION(_AUDIO_INPUT_FROM_TMDS);
#endif
#endif

#if((_HDMI_MAC_RX3_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
#if(_EMBEDDED_DAC_SUPPORT == _ON)
                    // Avoid Audio DAC Pop Noise
                    ScalerAudioDACNormalToDepopCheck(_AUDIO_FROM_RX3_PORT);
#endif

                    ScalerHdmiAudioRx3Initial();

                    // Avoid Audio Phase Delay Between L Channel and R Channel
                    ScalerAudioDVCResetProcCheck(_AUDIO_FROM_RX3_PORT);
#endif
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            switch(enumPowerAction)
            {
                case _POWER_ACTION_NORMAL_TO_OFF:
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX4_HDMI20_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX4_HDMI21_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
#endif
                    break;

                case _POWER_ACTION_OFF_TO_NORMAL:
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX4_HDMI20_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
                    CLR_TMDS_MAC_RX4_RETRY_SET_PHY();
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX4_HDMI21_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

#if(_AUDIO_SUPPORT == _ON)
                    // Choose HDMI2.0 Mac as Default
                    SET_HDMI_AUDIO_RX4_VERSION(_AUDIO_INPUT_FROM_TMDS);
#endif
#endif

#if((_HDMI_MAC_RX4_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
#if(_EMBEDDED_DAC_SUPPORT == _ON)
                    // Avoid Audio DAC Pop Noise
                    ScalerAudioDACNormalToDepopCheck(_AUDIO_FROM_RX4_PORT);
#endif

                    ScalerHdmiAudioRx4Initial();

                    // Avoid Audio Phase Delay Between L Channel and R Channel
                    ScalerAudioDVCResetProcCheck(_AUDIO_FROM_RX4_PORT);
#endif
                    break;

                default:
                    break;
            }
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Port PHY and DDC Selection
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPhyDdcSelection(EnumInputPort enumInputPort)
{
    // Set mapping of PHY to MAC
    ScalerTmdsMacRxMacSelection(enumInputPort);

    // Set mapping of ALL Dx to DDCx
    ScalerTmdsMacRxDDCSwitchCtrl(enumInputPort);
}

//--------------------------------------------------
// Description  : check if B/R swap is required
// Input Value  : Input Port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTmdsMacRxCheckBRSwap(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return ((_HW_TMDS_LANE_MAPPING == _TMDS_LANE_SWAP_NONE) ? (_D0_TMDS_BR_SWAP == _OFF) : (_D0_TMDS_BR_SWAP == _ON));
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return ((_HW_TMDS_LANE_MAPPING == _TMDS_LANE_SWAP_NONE) ? (_D1_TMDS_BR_SWAP == _OFF) : (_D1_TMDS_BR_SWAP == _ON));
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return ((_HW_TMDS_LANE_MAPPING == _TMDS_LANE_SWAP_NONE) ? (_D2_TMDS_BR_SWAP == _OFF) : (_D2_TMDS_BR_SWAP == _ON));
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return ((_HW_TMDS_LANE_MAPPING == _TMDS_LANE_SWAP_NONE) ? (_D3_TMDS_BR_SWAP == _OFF) : (_D3_TMDS_BR_SWAP == _ON));
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return ((_HW_TMDS_LANE_MAPPING == _TMDS_LANE_SWAP_NONE) ? (_D4_TMDS_BR_SWAP == _OFF) : (_D4_TMDS_BR_SWAP == _ON));
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return ((_HW_TMDS_LANE_MAPPING == _TMDS_LANE_SWAP_NONE) ? (_D5_TMDS_BR_SWAP == _OFF) : (_D5_TMDS_BR_SWAP == _ON));
#endif

        default:
            return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : B/R swap or not
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxBRSwap(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
        case _RX_MAP_NONE:

            break;

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

            if(ScalerTmdsMacRxCheckBRSwap(enumInputPort) == _TRUE)
            {
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT6, _BIT6);
            }
            else
            {
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT6, 0x00);
            }

            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

            if(ScalerTmdsMacRxCheckBRSwap(enumInputPort) == _TRUE)
            {
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT6, _BIT6);
            }
            else
            {
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT6, 0x00);
            }

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : check if P/N swap is required
// Input Value  : Input Port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTmdsMacRxCheckPNSwap(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return (_D0_TMDS_PN_SWAP == _ON);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return (_D1_TMDS_PN_SWAP == _ON);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return (_D2_TMDS_PN_SWAP == _ON);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return (_D3_TMDS_PN_SWAP == _ON);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return (_D4_TMDS_PN_SWAP == _ON);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return (_D5_TMDS_PN_SWAP == _ON);
#endif

        default:
            return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : P/N swap or not
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPNSwap(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
        case _RX_MAP_NONE:

            break;

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

            if(ScalerTmdsMacRxCheckPNSwap(enumInputPort) == _TRUE)
            {
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT5, _BIT5);
            }
            else
            {
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT5, 0x00);
            }

            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

            if(ScalerTmdsMacRxCheckPNSwap(enumInputPort) == _TRUE)
            {
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT5, _BIT5);
            }
            else
            {
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT5, 0x00);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Mac AC On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxAcOnInitial(void)
{
    // DDC Select set default value when AC on
    ScalerTmdsMacRxDDCSwitchWhenAcOnProc();

    // On Measure Initial to prevent stable flag need twice the time
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    SET_HDMI_MAC_RX3_AC_ON_HPD_TOGGLE_EVENT();
#endif
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    SET_HDMI_MAC_RX4_AC_ON_HPD_TOGGLE_EVENT();
#endif
#endif
}

//--------------------------------------------------
// Description  : Set Z0 HPD Period
// Input Value  : HPD type, Z0LowPeriod(ms), usHpdLowPeriod(ms), usZ0HpdInterval(ms)
// Output Value : None
// --|______________|----------------|______________|-----
//    usZ0LowPeriod  usZ0HpdInterval  usHpdLowPeriod
//--------------------------------------------------
void ScalerTmdsMacRxSetHdmiZ0HpdType(EnumHdmiZ0HpdType enumHdmiZ0HpdType, WORD usZ0LowPeriod, WORD usZ0HpdInterval)
{
    SET_HDMI_Z0_HPD_TYPE(enumHdmiZ0HpdType);
    SET_HDMI_Z0_LOW_PERIOD(usZ0LowPeriod);
    SET_HDMI_Z0_HPD_INTERVAL(usZ0HpdInterval);
}

/*
//--------------------------------------------------
// Description  : Enable/Disable HDMI Related IRQ_en
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHdmiIrqEnable(EnumInputPort enumInputPort, bit bEnable, StructHdmiIrqStatus *pstTmdsMacIrqStatus)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3HdmiIrqEnable(bEnable, pstTmdsMacIrqStatus);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4HdmiIrqEnable(bEnable, pstTmdsMacIrqStatus);
            break;
#endif

        default:
            break;
    }

#if(_HDMI_CEC_SUPPORT == _ON)
    ScalerCecIrqEnable(bEnable, pstTmdsMacIrqStatus);
#endif
}
*/

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Interface is Switching
// Input Value  : Input Port
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxSetInterfaceSwitching(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            SET_HDMI_MAC_RX3_INTERFACE_SWITCHING();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            SET_HDMI_MAC_RX4_INTERFACE_SWITCHING();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Interface is Switching or not?
// Input Value  : Input Port
// Output Value : TRUE(switching), FALSE(not switching)
//--------------------------------------------------
bit ScalerTmdsMacRxGetInterfaceSwitching(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_HDMI_MAC_RX3_INTERFACE_SWITCHING();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_HDMI_MAC_RX4_INTERFACE_SWITCHING();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear Interface is Switching Flag
// Input Value  : Input Port
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxClrInterfaceSwitching(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_HDMI_MAC_RX3_INTERFACE_SWITCHING();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_HDMI_MAC_RX4_INTERFACE_SWITCHING();
            break;
#endif

        default:
            break;
    }
}
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HDMI Freesync Replay Enable/Disable
// Input Value  : Dx Port, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetFreesyncReplayProc(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_HDMI_FREESYNC_REPLAY_D0_ENABLED();
            }
            else
            {
                CLR_HDMI_FREESYNC_REPLAY_D0_ENABLED();
            }

            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_HDMI_FREESYNC_REPLAY_D1_ENABLED();
            }
            else
            {
                CLR_HDMI_FREESYNC_REPLAY_D1_ENABLED();
            }

            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_HDMI_FREESYNC_REPLAY_D2_ENABLED();
            }
            else
            {
                CLR_HDMI_FREESYNC_REPLAY_D2_ENABLED();
            }

            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_HDMI_FREESYNC_REPLAY_D3_ENABLED();
            }
            else
            {
                CLR_HDMI_FREESYNC_REPLAY_D3_ENABLED();
            }

            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_HDMI_FREESYNC_REPLAY_D4_ENABLED();
            }
            else
            {
                CLR_HDMI_FREESYNC_REPLAY_D4_ENABLED();
            }

            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_HDMI_FREESYNC_REPLAY_D5_ENABLED();
            }
            else
            {
                CLR_HDMI_FREESYNC_REPLAY_D5_ENABLED();
            }

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get HDMI Freesync Replay Enable/Disable
// Input Value  : Dx Port, bEnable
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxGetFreesyncReplayProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_HDMI_FREESYNC_REPLAY_D0_ENABLED();
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_HDMI_FREESYNC_REPLAY_D1_ENABLED();
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_HDMI_FREESYNC_REPLAY_D2_ENABLED();
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            return GET_HDMI_FREESYNC_REPLAY_D3_ENABLED();
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            return GET_HDMI_FREESYNC_REPLAY_D4_ENABLED();
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            return GET_HDMI_FREESYNC_REPLAY_D5_ENABLED();
#endif
        default:
            break;
    }

    return _FALSE;
}
#endif

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
//--------------------------------------------------
// Description  : Get Ac On HPD Toggle EVENT
// Input Value  : Input Port
// Output Value : TRUE(do HPD Toggle), FALSE(no HPD Toggle)
//--------------------------------------------------
bit ScalerTmdsMacRxGetAcOnHpdToggleEvent(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_HDMI_MAC_RX3_AC_ON_HPD_TOGGLE_EVENT();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_HDMI_MAC_RX4_AC_ON_HPD_TOGGLE_EVENT();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear Ac On HPD Toggle EVENT
// Input Value  : Input Port
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxClrAcOnHpdToggleEvent(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_HDMI_MAC_RX3_AC_ON_HPD_TOGGLE_EVENT();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_HDMI_MAC_RX4_AC_ON_HPD_TOGGLE_EVENT();
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Detect HPD Detect
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
EnumUserHdmi5vStatus ScalerTmdsMacRxHpdDetect(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            // Check Hot Plug 5V
            if(ScalerGetBit(P72_23_HDMI_CTRL_23, _BIT0) == _BIT0)
            {
                return _HDMI_5V_STATUS_HIGH;
            }
            else
            {
                return _HDMI_5V_STATUS_LOW;
            }
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            // Check Hot Plug 5V
            if(ScalerGetBit(P73_23_HDMI_CTRL_23, _BIT0) == _BIT0)
            {
                return _HDMI_5V_STATUS_HIGH;
            }
            else
            {
                return _HDMI_5V_STATUS_LOW;
            }
            break;
#endif
        default:
            return 0x00;
    }
}

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Detect HPD Detect
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
EnumInputPort ScalerTmdsMacRxExternalHdmiPortMapping(EnumInputPort enumInputPort)
{
    if(enumInputPort == _D3_INPUT_PORT)
    {
#if(((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3)) || ((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3)))
        if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
        {
            return _D3_INPUT_PORT;
        }
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
        {
            return _D12_INPUT_PORT;
        }
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
        {
            return _D13_INPUT_PORT;
        }
        else
#endif
#endif
        {
            return _D3_INPUT_PORT;
        }
    }

    if(enumInputPort == _D4_INPUT_PORT)
    {
#if(((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4)) || ((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4)))
        if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
        {
            return _D4_INPUT_PORT;
        }
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
        {
            return _D14_INPUT_PORT;
        }
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
        {
            return _D15_INPUT_PORT;
        }
        else
#endif
#endif
        {
            return _D4_INPUT_PORT;
        }
    }

    return enumInputPort;
}
#endif
#endif
