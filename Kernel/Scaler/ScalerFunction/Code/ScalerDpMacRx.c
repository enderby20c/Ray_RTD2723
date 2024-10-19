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
// ID Code      : ScalerDpMacRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP__

#include "ScalerFunctionInclude.h"
#include "DpMacRx/ScalerDpMacRx.h"

#if(_DP_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
StructDpMacRxComboPowerStatus g_stDpMacRxComboPowerStatus;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP MAC power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacRxPowerProc(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
    // DP MAC DPHY and MAC Stream Combo Power Domain
    ScalerDpMacRxPowerCutComboPowerProc(enumInputPort, enumPowerAction);
#else

    if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
    {
        ScalerDpMacDphyRxPowerProc(enumInputPort, _POWER_ACTION_OFF_TO_NORMAL);

        ScalerDpMacStreamRxPowerProc(ScalerDpRxGetMacSwitch(enumInputPort), _POWER_ACTION_OFF_TO_NORMAL);
    }
    else
    {
        ScalerDpMacStreamRxPowerProc(ScalerDpRxGetMacSwitch(enumInputPort), _POWER_ACTION_NORMAL_TO_OFF);

        ScalerDpMacDphyRxPowerProc(enumInputPort, _POWER_ACTION_NORMAL_TO_OFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Get DP Mac RX Power Cut Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacRxGetPowerCutFlagStatus(EnumInputPort enumInputPort)
{
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
    // DP MAC DPHY and MAC Stream Combo Power Domain
    return ScalerDpMacRxGetComboPowerCutFlagStatus(enumInputPort);
#else

    return ScalerDpMacDphyRxGetPowerCutFlagStatus(enumInputPort);
#endif
}

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
//--------------------------------------------------
// Description  : DP MAC power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacRxPowerCutComboPowerProc(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch(enumInputPort);

#if((_AUDIO_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Ignore Power Control when in Audio Pattern Gen
    if(ScalerAudioGetInternalAudioGenEnable(enumInputPort) == _ENABLE)
    {
        return;
    }
#endif

    if(enumDpMacSel == _DP_MAC_NONE)
    {
        return;
    }

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            switch(enumPowerAction)
            {
                case _POWER_ACTION_NORMAL_TO_OFF:

                    if(GET_DP_MAC_RX0_COMBO_POWER_CUT_STATUS() == _OFF)
                    {
                        DebugMessageDpRx("MAC0 Power Off", 0);

                        ScalerDpAuxRxSetManualMode(enumInputPort);

                        // Set DPRX SRAM CLK Gate Disable
                        ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

                        // DP MAC0 Power Cut Enable
                        if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX0_DP14_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE) == _SUCCESS)
                        {
                            SET_DP_MAC_RX0_COMBO_POWER_CUT_STATUS(_ON);

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
                            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX0_DP20_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
#endif
                        }
                        else
                        {
                            // Set DPRX SRAM CLK Gate Enable
                            ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _ENABLE);
                        }

                        ScalerDpAuxRxSetAutoMode(enumInputPort);
                    }

                    break;

                case _POWER_ACTION_OFF_TO_NORMAL:

                    if(GET_DP_MAC_RX0_COMBO_POWER_CUT_STATUS() == _ON)
                    {
                        DebugMessageDpRx("MAC0 Power On", 0);

                        // DP MAC0 Power Cut Disable
                        if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX0_DP14_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS) == _SUCCESS)
                        {
                            SET_DP_MAC_RX0_COMBO_POWER_CUT_STATUS(_OFF);

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
                            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX0_DP20_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
#endif

                            // Recover Data from Power Cut State
                            ScalerDpMacDphyRxPowerDataRecover(enumInputPort);
                            ScalerDpMacStreamRxPowerDataRecover(enumInputPort);

#if(_AUDIO_SUPPORT == _ON)
#if(_EMBEDDED_DAC_SUPPORT == _ON)
                            // Avoid Audio DAC Pop Noise
                            ScalerAudioDACNormalToDepopCheck(_AUDIO_FROM_RX0_PORT);
#endif

                            // Audio Re-Initial from Power Cut State
                            ScalerDpAudioRx0AudioInitial();

                            // Avoid Audio Phase Delay Between L Channel and R Channel
                            ScalerAudioDVCResetProcCheck(_AUDIO_FROM_RX0_PORT);
#endif
                        }
                    }

                    break;

                default:
                    break;
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            switch(enumPowerAction)
            {
                case _POWER_ACTION_NORMAL_TO_OFF:

                    if(GET_DP_MAC_RX1_COMBO_POWER_CUT_STATUS() == _OFF)
                    {
                        DebugMessageDpRx("MAC1 Power off", 0);

                        ScalerDpAuxRxSetManualMode(enumInputPort);

                        // Set DPRX SRAM CLK Gate Disable
                        ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

                        // DP MAC1 Power Cut Enable
                        if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP14_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE) == _SUCCESS)
                        {
                            SET_DP_MAC_RX1_COMBO_POWER_CUT_STATUS(_ON);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP20_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
#endif
                        }
                        else
                        {
                            // Set DPRX SRAM CLK Gate Enable
                            ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _ENABLE);
                        }

                        ScalerDpAuxRxSetAutoMode(enumInputPort);
                    }

                    break;

                case _POWER_ACTION_OFF_TO_NORMAL:

                    if(GET_DP_MAC_RX1_COMBO_POWER_CUT_STATUS() == _ON)
                    {
                        DebugMessageDpRx("MAC1 Power On", 0);

                        // DP MAC1 Power Cut Disable
                        if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP14_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS) == _SUCCESS)
                        {
                            SET_DP_MAC_RX1_COMBO_POWER_CUT_STATUS(_OFF);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP20_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
#endif

                            // Recover Data from Power Cut State
                            ScalerDpMacDphyRxPowerDataRecover(enumInputPort);
                            ScalerDpMacStreamRxPowerDataRecover(enumInputPort);

#if(_AUDIO_SUPPORT == _ON)
#if(_EMBEDDED_DAC_SUPPORT == _ON)
                            // Avoid Audio DAC Pop Noise
                            ScalerAudioDACNormalToDepopCheck(_AUDIO_FROM_RX1_PORT);
#endif

                            // Audio Re-Initial from Power Cut State
                            ScalerDpAudioRx1AudioInitial();

                            // Avoid Audio Phase Delay Between L Channel and R Channel
                            ScalerAudioDVCResetProcCheck(_AUDIO_FROM_RX1_PORT);
#endif
                        }
                    }

                    break;

                default:
                    break;
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            switch(enumPowerAction)
            {
                case _POWER_ACTION_NORMAL_TO_OFF:

                    if(GET_DP_MAC_RX2_COMBO_POWER_CUT_STATUS() == _OFF)
                    {
                        DebugMessageDpRx("MAC2 Power off", 0);

                        ScalerDpAuxRxSetManualMode(enumInputPort);

                        // Set DPRX SRAM CLK Gate Disable
                        ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

                        // DP MAC2 Power Cut Enable
                        if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP14_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE) == _SUCCESS)
                        {
                            SET_DP_MAC_RX2_COMBO_POWER_CUT_STATUS(_ON);

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP20_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
#endif
                        }
                        else
                        {
                            // Set DPRX SRAM CLK Gate Enable
                            ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _ENABLE);
                        }

                        ScalerDpAuxRxSetAutoMode(enumInputPort);
                    }

                    break;

                case _POWER_ACTION_OFF_TO_NORMAL:

                    if(GET_DP_MAC_RX2_COMBO_POWER_CUT_STATUS() == _ON)
                    {
                        DebugMessageDpRx("MAC2 Power On", 0);

                        // DP MAC1 Power Cut Disable
                        if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP14_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS) == _SUCCESS)
                        {
                            SET_DP_MAC_RX2_COMBO_POWER_CUT_STATUS(_OFF);

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP20_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
#endif

                            // Recover Data from Power Cut State
                            ScalerDpMacDphyRxPowerDataRecover(enumInputPort);
                            ScalerDpMacStreamRxPowerDataRecover(enumInputPort);

#if(_AUDIO_SUPPORT == _ON)
#if(_EMBEDDED_DAC_SUPPORT == _ON)
                            // Avoid Audio DAC Pop Noise
                            ScalerAudioDACNormalToDepopCheck(_AUDIO_FROM_RX2_PORT);
#endif

                            // Audio Re-Initial from Power Cut State
                            ScalerDpAudioRx2AudioInitial();

                            // Avoid Audio Phase Delay Between L Channel and R Channel
                            ScalerAudioDVCResetProcCheck(_AUDIO_FROM_RX2_PORT);
#endif
                        }
                    }

                    break;

                default:
                    break;
            }

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Mac RX Power Cut Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacRxGetComboPowerCutFlagStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_RX0_COMBO_POWER_CUT_STATUS();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_RX1_COMBO_POWER_CUT_STATUS();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_RX2_COMBO_POWER_CUT_STATUS();
#endif

        default:

            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void  ScalerDpMacRxPowerDataRecover(void)
{
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    ScalerDpMacDphyRx0PowerDataRecover();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
    ScalerDpMacDphyRx1PowerDataRecover();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
    ScalerDpMacDphyRx2PowerDataRecover();
#endif

#if(_DP_MAC_RX0_SUPPORT == _ON)
    ScalerDpMacStreamRx0SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
    ScalerDpMacStreamRx0SetSdpMetaSramRcvInitial();
#endif
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    ScalerDpMacStreamRx1SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpMetaSramRcvInitial();
#endif
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    ScalerDpMacStreamRx2SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
    ScalerDpMacStreamRx2SetSdpMetaSramRcvInitial();
#endif
#endif
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx Set Tx Clone Rx Port Select
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacRxSetTxCloneRxPortSel(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            ScalerSetBit(P6F_04_MUX_DPRX_OUT, ~(_BIT5 | _BIT4), 0x00 << 4);
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerSetBit(P6F_04_MUX_DPRX_OUT, ~(_BIT5 | _BIT4), 0x01 << 4);
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerSetBit(P6F_04_MUX_DPRX_OUT, ~(_BIT5 | _BIT4), 0x02 << 4);
            break;
#endif

        default:

            break;
    }
}
#endif
#endif
