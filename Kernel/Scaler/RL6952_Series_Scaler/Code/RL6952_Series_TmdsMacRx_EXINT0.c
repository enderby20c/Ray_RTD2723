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
// ID Code      : RL6952_Series_TmdsMacRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_TMDSMAC_EXINT0__

#include "ScalerFunctionInclude.h"
#include "TmdsMacRx/ScalerTmdsMacRx.h"



#if(_HDMI_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Mac mapping to Phy
// Input Value  : Mac Rx
// Output Value : Phy Rx
//--------------------------------------------------
EnumRx ScalerTmdsMacRxMacPhyMapping_EXINT0(EnumRx enumMacRxIndex)
{
    EnumRx enumPhyRxIndex = _RX_MAP_NONE;

    switch(enumMacRxIndex)
    {
        case _RX3:

            enumPhyRxIndex = _RX3;
            break;

        case _RX4:

            enumPhyRxIndex = _RX4;
            break;

        default:

            break;
    }

    return enumPhyRxIndex;
}

//--------------------------------------------------
// Description  : TMDS Phy mapping to Mac
// Input Value  : Phy Rx
// Output Value : Mac Rx
//--------------------------------------------------
EnumRx ScalerTmdsMacRxPhyMacMapping_EXINT0(EnumRx enumPhyRxIndex)
{
    EnumRx enumMacRxIndex = _RX_MAP_NONE;

    switch(enumPhyRxIndex)
    {
        case _RX3:

            enumMacRxIndex = _RX3;
            break;

        case _RX4:

            enumMacRxIndex = _RX4;
            break;

        default:

            break;
    }

    return enumMacRxIndex;
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHighIntHandler_EXINT0(EnumPowerStatus enumPowerStatus)
{
    if((enumPowerStatus != _POWER_STATUS_SAVING) && (enumPowerStatus != _POWER_STATUS_OFF))
    {
#if(_D0_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNHighIntHandler_EXINT0(_D0_INPUT_PORT);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNHighIntHandler_EXINT0(_D1_INPUT_PORT);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNHighIntHandler_EXINT0(_D2_INPUT_PORT);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNHighIntHandler_EXINT0(_D3_INPUT_PORT);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNHighIntHandler_EXINT0(_D4_INPUT_PORT);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNHighIntHandler_EXINT0(_D5_INPUT_PORT);
#endif
    }
    else
    {
#if(_D0_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSHighIntHandler_EXINT0(_D0_INPUT_PORT);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSHighIntHandler_EXINT0(_D1_INPUT_PORT);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSHighIntHandler_EXINT0(_D2_INPUT_PORT);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSHighIntHandler_EXINT0(_D3_INPUT_PORT);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSHighIntHandler_EXINT0(_D4_INPUT_PORT);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSHighIntHandler_EXINT0(_D5_INPUT_PORT);
#endif
    }
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxLowIntHandler_EXINT0(EnumPowerStatus enumPowerStatus)
{
    if((enumPowerStatus != _POWER_STATUS_SAVING) && (enumPowerStatus != _POWER_STATUS_OFF))
    {
#if(_D0_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNLowIntHandler_EXINT0(_D0_INPUT_PORT);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNLowIntHandler_EXINT0(_D1_INPUT_PORT);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNLowIntHandler_EXINT0(_D2_INPUT_PORT);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNLowIntHandler_EXINT0(_D3_INPUT_PORT);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNLowIntHandler_EXINT0(_D4_INPUT_PORT);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPNLowIntHandler_EXINT0(_D5_INPUT_PORT);
#endif
    }
    else
    {
#if(_D0_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSLowIntHandler_EXINT0(_D0_INPUT_PORT);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSLowIntHandler_EXINT0(_D1_INPUT_PORT);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSLowIntHandler_EXINT0(_D2_INPUT_PORT);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSLowIntHandler_EXINT0(_D3_INPUT_PORT);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSLowIntHandler_EXINT0(_D4_INPUT_PORT);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxPSLowIntHandler_EXINT0(_D5_INPUT_PORT);
#endif
    }
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In power normal
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPNHighIntHandler_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3HighPriorityIntHandler_EXINT0();
#endif

            ScalerTmdsMacRx3HighPriorityIntHandler_EXINT0();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4HighPriorityIntHandler_EXINT0();
#endif

            ScalerTmdsMacRx4HighPriorityIntHandler_EXINT0();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In power normal
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPNLowIntHandler_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3LowPriorityIntHandler_EXINT0();
#endif

            ScalerTmdsMacRx3LowPriorityIntHandler_EXINT0();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4LowPriorityIntHandler_EXINT0();
#endif

            ScalerTmdsMacRx4LowPriorityIntHandler_EXINT0();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPSHighIntHandler_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3PSHighPriorityIntHandler_EXINT0();
#endif
            ScalerTmdsMacRx3PSHighPriorityIntHandler_EXINT0();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4PSHighPriorityIntHandler_EXINT0();
#endif
            ScalerTmdsMacRx4PSHighPriorityIntHandler_EXINT0();
            break;

#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPSLowIntHandler_EXINT0(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3PSLowPriorityIntHandler_EXINT0();
#endif
            ScalerTmdsMacRx3PSLowPriorityIntHandler_EXINT0();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4PSLowPriorityIntHandler_EXINT0();
#endif
            ScalerTmdsMacRx4PSLowPriorityIntHandler_EXINT0();
            break;

#endif

        default:
            break;
    }
}

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI Set Audio N.F Code
// Input Value  : Mac Rx
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetAudioNfCode_EXINT0(EnumRx enumMacRxIndex)
{
    switch(enumMacRxIndex)
    {
#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerSetBit_EXINT(P72_8E_PORT_PAGE73_HDMI_NF_CODE_1, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX3_TARGET_SAMPLING_FREQ())) & 0x1F));
            ScalerSetByte_EXINT(P72_8F_PORT_PAGE72_HDMI_NF_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX3_TARGET_SAMPLING_FREQ()))));
            ScalerSetByte_EXINT(P72_90_PORT_PAGE72_HDMI_NF_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX3_TARGET_SAMPLING_FREQ()))));
            break;
#endif

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerSetBit_EXINT(P73_8E_PORT_PAGE73_HDMI_NF_CODE_1, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX4_TARGET_SAMPLING_FREQ())) & 0x1F));
            ScalerSetByte_EXINT(P73_8F_PORT_PAGE73_HDMI_NF_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX4_TARGET_SAMPLING_FREQ()))));
            ScalerSetByte_EXINT(P73_90_PORT_PAGE73_HDMI_NF_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX4_TARGET_SAMPLING_FREQ()))));
            break;
#endif
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Unstable Reset Phy channel FIFO
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPhyDrcrFifoReset_EXINT0(EnumInputPort enumInputPort)
{
    if((ScalerGlobalGetIDCode() < _RL6952_VER_A_ID_CODE) && (ScalerTmdsPhyRxCheckDcdr_EXINT0(enumInputPort) == _TRUE))
    {
        ScalerTmdsPhyRxUnstableFifoReset_EXINT0(enumInputPort);
    }
}
#endif

