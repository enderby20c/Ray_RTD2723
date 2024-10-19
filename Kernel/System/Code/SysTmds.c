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
// ID Code      : SysTmds.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_TMDS__

#include "SysInclude.h"
#include "Tmds/SysTmds.h"

#if(_HDMI_SUPPORT == _ON)
#if(_INPUTCLOCK_RANG_HDMI <= 3400)
#if(_INPUTCLOCK_RANG_DVI != _INPUTCLOCK_RANG_HDMI)
#warning "NOTE: _INPUTCLOCK_RANG_DVI should be same as _INPUTCLOCK_RANG_HDMI!!!"
#endif
#else
#if(_INPUTCLOCK_RANG_DVI != 3400)
#warning "NOTE: _INPUTCLOCK_RANG_DVI should be set 3400!!!"
#endif
#endif

#if(_HDMI20_SUPPORT == _ON)
#if((_HDMI_SINK_RTK_ID_STRING_H == 0x00) && (_HDMI_SINK_RTK_ID_STRING_L == 0x00))
#warning "NOTE: _HDMI_SINK_RTK_ID_STRING_H/_HDMI_SINK_RTK_ID_STRING_H Should Be Defined as RTD Number When VID = Realtek"
#endif
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
StructTMDSCableStatus g_stTmdsCablePreStatus;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Switch TMDS ports
// Input Value  : Current Input Port, Target Source Type, switch status
// Output Value : None
//--------------------------------------------------
void SysTmdsInterfaceSwitch(EnumInputPort enumInputPort, EnumPortType enumPortType, StructPortSwitchedStatus *pstPortStatus)
{
    enumInputPort = enumInputPort;
    pstPortStatus = pstPortStatus;

#if(_HDMI_SUPPORT == _ON)
    if(enumPortType == _PORT_HDMI)
    {
        // Set mapping of PHY to MAC
        ScalerTmdsMacRxMacSelection(enumInputPort);

        // Set mapping of ALL Dx to DDCx
        ScalerTmdsMacRxDDCSwitchCtrl(enumInputPort);
    }
#endif

    // Disable TMDS freq. detect
    switch(enumPortType)
    {
        case _PORT_HDMI:
            break;

        default:
#if(_D0_HDMI_SUPPORT == _ON)
            if(pstPortStatus->b1D0 == _FALSE)
            {
                ScalerTmdsMacRxFreqDetectDisable(_D0_INPUT_PORT);

#if(_D0_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleDetectDisable(_D0_INPUT_PORT);
#endif
            }
#endif

#if(_D1_HDMI_SUPPORT == _ON)
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
            if((pstPortStatus->b1D1 == _FALSE) && (ScalerTmdsMacRxGetDigitalPort(_D1_INPUT_PORT) == _FALSE))
#else
            if(pstPortStatus->b1D1 == _FALSE)
#endif
            {
                ScalerTmdsMacRxFreqDetectDisable(_D1_INPUT_PORT);

#if(_D1_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleDetectDisable(_D1_INPUT_PORT);
#endif

#if(_D1_HDMI_FRL_SUPPORT == _ON)
                ScalerHdmiFrlMacRxLinkTrainingDisable(_D1_INPUT_PORT);
#endif
            }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
            if((pstPortStatus->b1D2 == _FALSE) && (ScalerTmdsMacRxGetDigitalPort(_D2_INPUT_PORT) == _FALSE))
#else
            if(pstPortStatus->b1D2 == _FALSE)
#endif
            {
                ScalerTmdsMacRxFreqDetectDisable(_D2_INPUT_PORT);

#if(_D2_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleDetectDisable(_D2_INPUT_PORT);
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
                ScalerHdmiFrlMacRxLinkTrainingDisable(_D2_INPUT_PORT);
#endif
            }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
            if((pstPortStatus->b1D3 == _FALSE) && (ScalerTmdsMacRxGetDigitalPort(_D3_INPUT_PORT) == _FALSE))
#else
            if(pstPortStatus->b1D3 == _FALSE)
#endif
            {
                ScalerTmdsMacRxFreqDetectDisable(_D3_INPUT_PORT);

#if(_D3_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleDetectDisable(_D3_INPUT_PORT);
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
                ScalerHdmiFrlMacRxLinkTrainingDisable(_D3_INPUT_PORT);
#endif
            }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
            if((pstPortStatus->b1D4 == _FALSE) && (ScalerTmdsMacRxGetDigitalPort(_D4_INPUT_PORT) == _FALSE))
#else
            if(pstPortStatus->b1D4 == _FALSE)
#endif
            {
                ScalerTmdsMacRxFreqDetectDisable(_D4_INPUT_PORT);

#if(_D4_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleDetectDisable(_D4_INPUT_PORT);
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
                ScalerHdmiFrlMacRxLinkTrainingDisable(_D4_INPUT_PORT);
#endif
            }
#endif

#if(_D5_HDMI_SUPPORT == _ON)
            if(pstPortStatus->b1D5 == _FALSE)
            {
                ScalerTmdsMacRxFreqDetectDisable(_D5_INPUT_PORT);

#if(_D5_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleDetectDisable(_D5_INPUT_PORT);
#endif
            }
#endif
            break;
    }
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Port Cable Pre-Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysTmdsGetCablePreStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D1Status;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D2Status;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D3Status;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D4Status;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D5Status;
#endif

#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D12_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D12Status;
#endif

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D13_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D13Status;
#endif

#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D14_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D14Status;
#endif

#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D15_INPUT_PORT:

            return g_stTmdsCablePreStatus.b1D15Status;
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Set Cable Pre-Status
// Input Value  : enumInputPort, bStatus
// Output Value : None
//--------------------------------------------------
void SysTmdsSetCablePreStatus(EnumInputPort enumInputPort, bit bStatus)
{
    bStatus = bStatus;

    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D1Status = bStatus;

            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D2Status = bStatus;

            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D3Status = bStatus;

            break;
#endif
#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D4Status = bStatus;

            break;
#endif
#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D5Status = bStatus;

            break;
#endif
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D12_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D12Status = bStatus;

            break;
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D13_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D13Status = bStatus;

            break;
#endif
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D14_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D14Status = bStatus;

            break;
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D15_INPUT_PORT:

            g_stTmdsCablePreStatus.b1D15Status = bStatus;

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Cable Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTmdsCableDetection(void)
{
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D15vStatusByUser = UserInterfaceTmds5vPinDetect(_D1_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D1_INPUT_PORT) != GET_D1_CABLE_STATUS())
    {
        if(GET_D1_CABLE_STATUS() == _TRUE)
        {
#if((_D1_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
            ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D1_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
            ScalerTmdsMacRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D1_HDMI20_SUPPORT == _ON)
            ScalerTmdsMacRxHpd5vPinCheckEvent(_D1_INPUT_PORT, _ENABLE);
#endif
        }
        else
        {
#if((_D1_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
            ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D1_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            ScalerTmdsMacRxHdcp2ResetProc(_D1_INPUT_PORT);
#endif
            ScalerTmdsMacRxHdcp14CableOutProc(_D1_INPUT_PORT);

#if(_D1_HDMI20_SUPPORT == _ON)
            ScalerTmdsMacRxScrambleStatusReset(_D1_INPUT_PORT);

            ScalerTmdsMacRxHpd5vPinCheckEvent(_D1_INPUT_PORT, _DISABLE);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
            // Reset SCDC
            ScalerHdmiFrlMacRxResetProc(_D1_INPUT_PORT);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
            // Reset ARC/eARC Tx
            SysAudioArcTxCableUnplugResetProc(_D1_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
            if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
            {
                ScalerTmdsMacRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
            }
#endif
        }
        SysTmdsSetCablePreStatus(_D1_INPUT_PORT, GET_D1_CABLE_STATUS());
    }
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D25vStatusByUser = UserInterfaceTmds5vPinDetect(_D2_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D2_INPUT_PORT) != GET_D2_CABLE_STATUS())
    {
        if(GET_D2_CABLE_STATUS() == _TRUE)
        {
#if((_D2_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
            ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D2_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
            ScalerTmdsMacRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D2_HDMI20_SUPPORT == _ON)
            ScalerTmdsMacRxHpd5vPinCheckEvent(_D2_INPUT_PORT, _ENABLE);
#endif
        }
        else
        {
#if((_D2_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
            ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D2_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            ScalerTmdsMacRxHdcp2ResetProc(_D2_INPUT_PORT);
#endif
            ScalerTmdsMacRxHdcp14CableOutProc(_D2_INPUT_PORT);

#if(_D2_HDMI20_SUPPORT == _ON)
            ScalerTmdsMacRxScrambleStatusReset(_D2_INPUT_PORT);

            ScalerTmdsMacRxHpd5vPinCheckEvent(_D2_INPUT_PORT, _DISABLE);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
            // Reset SCDC
            ScalerHdmiFrlMacRxResetProc(_D2_INPUT_PORT);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
            // Reset ARC/eARC Tx
            SysAudioArcTxCableUnplugResetProc(_D2_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
            if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
            {
                ScalerTmdsMacRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
            }
#endif
        }
        SysTmdsSetCablePreStatus(_D2_INPUT_PORT, GET_D2_CABLE_STATUS());
    }
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D35vStatusByUser = UserInterfaceTmds5vPinDetect(_D3_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D3_INPUT_PORT) != GET_D3_CABLE_STATUS())
    {
        if(GET_D3_CABLE_STATUS() == _TRUE)
        {
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT))
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
#endif
            {
#if((_D3_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D3_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxHpd5vPinCheckEvent(_D3_INPUT_PORT, _ENABLE);
#endif
            }
        }
        else
        {
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT))
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)
#endif
            {
#if((_D3_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                ScalerTmdsMacRxHdcp2ResetProc(_D3_INPUT_PORT);
#endif
                ScalerTmdsMacRxHdcp14CableOutProc(_D3_INPUT_PORT);

#if(_D3_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D3_INPUT_PORT);

                ScalerTmdsMacRxHpd5vPinCheckEvent(_D3_INPUT_PORT, _DISABLE);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
                // Reset SCDC
                ScalerHdmiFrlMacRxResetProc(_D3_INPUT_PORT);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
                // Reset ARC/eARC Tx
                SysAudioArcTxCableUnplugResetProc(_D3_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
                {
                    ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif
            }
        }
        SysTmdsSetCablePreStatus(_D3_INPUT_PORT, GET_D3_CABLE_STATUS());
    }
#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D45vStatusByUser = UserInterfaceTmds5vPinDetect(_D4_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D4_INPUT_PORT) != GET_D4_CABLE_STATUS())
    {
        if(GET_D4_CABLE_STATUS() == _TRUE)
        {
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT))
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
#endif
            {
#if((_D4_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D4_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxHpd5vPinCheckEvent(_D4_INPUT_PORT, _ENABLE);
#endif
            }
        }
        else
        {
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT))
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)
#endif
            {
#if((_D4_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                ScalerTmdsMacRxHdcp2ResetProc(_D4_INPUT_PORT);
#endif
                ScalerTmdsMacRxHdcp14CableOutProc(_D4_INPUT_PORT);

#if(_D4_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D4_INPUT_PORT);

                ScalerTmdsMacRxHpd5vPinCheckEvent(_D4_INPUT_PORT, _DISABLE);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
                // Reset SCDC
                ScalerHdmiFrlMacRxResetProc(_D4_INPUT_PORT);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
                // Reset ARC/eARC Tx
                SysAudioArcTxCableUnplugResetProc(_D4_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
                {
                    ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif
            }
        }
        SysTmdsSetCablePreStatus(_D4_INPUT_PORT, GET_D4_CABLE_STATUS());
    }
#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D55vStatusByUser = UserInterfaceTmds5vPinDetect(_D5_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D5_INPUT_PORT) != GET_D5_CABLE_STATUS())
    {
        if(GET_D5_CABLE_STATUS() == _TRUE)
        {
#if((_D5_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
            ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D5_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
            ScalerTmdsMacRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D5_HDMI20_SUPPORT == _ON)
            ScalerTmdsMacRxHpd5vPinCheckEvent(_D5_INPUT_PORT, _ENABLE);
#endif
        }
        else
        {
#if((_D5_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
            ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D5_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            ScalerTmdsMacRxHdcp2ResetProc(_D5_INPUT_PORT);
#endif
            ScalerTmdsMacRxHdcp14CableOutProc(_D5_INPUT_PORT);

#if(_D5_HDMI20_SUPPORT == _ON)
            ScalerTmdsMacRxScrambleStatusReset(_D5_INPUT_PORT);

            ScalerTmdsMacRxHpd5vPinCheckEvent(_D5_INPUT_PORT, _DISABLE);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
            // Reset ARC/eARC Tx
            SysAudioArcTxCableUnplugResetProc(_D5_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
            if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
            {
                ScalerTmdsMacRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
            }
#endif
        }
        SysTmdsSetCablePreStatus(_D5_INPUT_PORT, GET_D5_CABLE_STATUS());
    }
#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)

#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D125vStatusByUser = UserInterfaceTmds5vPinDetect(_D12_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D12_INPUT_PORT) != GET_D12_CABLE_STATUS())
    {
        if(GET_D12_CABLE_STATUS() == _TRUE)
        {
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
            {
#if((_D3_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D3_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxHpd5vPinCheckEvent(_D3_INPUT_PORT, _ENABLE);
#endif
            }
        }
        else
        {
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
            {
#if((_D3_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                ScalerTmdsMacRxHdcp2ResetProc(_D3_INPUT_PORT);
#endif
                ScalerTmdsMacRxHdcp14CableOutProc(_D3_INPUT_PORT);

#if(_D3_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D3_INPUT_PORT);

                ScalerTmdsMacRxHpd5vPinCheckEvent(_D3_INPUT_PORT, _DISABLE);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
                // Reset SCDC
                ScalerHdmiFrlMacRxResetProc(_D3_INPUT_PORT);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
                // Reset ARC/eARC Tx
                SysAudioArcTxCableUnplugResetProc(_D3_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
                {
                    ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif
            }
        }
        SysTmdsSetCablePreStatus(_D12_INPUT_PORT, GET_D12_CABLE_STATUS());
    }
#endif // End of #if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D135vStatusByUser = UserInterfaceTmds5vPinDetect(_D13_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D13_INPUT_PORT) != GET_D13_CABLE_STATUS())
    {
        if(GET_D13_CABLE_STATUS() == _TRUE)
        {
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
            {
#if((_D3_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D3_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxHpd5vPinCheckEvent(_D3_INPUT_PORT, _ENABLE);
#endif
            }
        }
        else
        {
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
            {
#if((_D3_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                ScalerTmdsMacRxHdcp2ResetProc(_D3_INPUT_PORT);
#endif
                ScalerTmdsMacRxHdcp14CableOutProc(_D3_INPUT_PORT);

#if(_D3_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D3_INPUT_PORT);

                ScalerTmdsMacRxHpd5vPinCheckEvent(_D3_INPUT_PORT, _DISABLE);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
                // Reset SCDC
                ScalerHdmiFrlMacRxResetProc(_D3_INPUT_PORT);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
                // Reset ARC/eARC Tx
                SysAudioArcTxCableUnplugResetProc(_D3_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
                {
                    ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif
            }
        }
        SysTmdsSetCablePreStatus(_D13_INPUT_PORT, GET_D13_CABLE_STATUS());
    }
#endif // End of #if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))

#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D145vStatusByUser = UserInterfaceTmds5vPinDetect(_D14_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D14_INPUT_PORT) != GET_D14_CABLE_STATUS())
    {
        if(GET_D14_CABLE_STATUS() == _TRUE)
        {
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
            {
#if((_D4_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D4_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxHpd5vPinCheckEvent(_D4_INPUT_PORT, _ENABLE);
#endif
            }
        }
        else
        {
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
            {
#if((_D4_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                ScalerTmdsMacRxHdcp2ResetProc(_D4_INPUT_PORT);
#endif
                ScalerTmdsMacRxHdcp14CableOutProc(_D4_INPUT_PORT);

#if(_D4_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D4_INPUT_PORT);

                ScalerTmdsMacRxHpd5vPinCheckEvent(_D4_INPUT_PORT, _DISABLE);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
                // Reset SCDC
                ScalerHdmiFrlMacRxResetProc(_D4_INPUT_PORT);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
                // Reset ARC/eARC Tx
                SysAudioArcTxCableUnplugResetProc(_D4_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
                {
                    ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif
            }
        }
        SysTmdsSetCablePreStatus(_D14_INPUT_PORT, GET_D14_CABLE_STATUS());
    }
#endif // End of #if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))

#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
#if((_HDMI20_SUPPORT == _ON) && (_HDMI_5V_DETECT_BY_USER == _ON))
    g_stTmdsMacRx5vStatusByUser.b1D155vStatusByUser = UserInterfaceTmds5vPinDetect(_D15_INPUT_PORT);
#endif

    if(SysTmdsGetCablePreStatus(_D15_INPUT_PORT) != GET_D15_CABLE_STATUS())
    {
        if(GET_D15_CABLE_STATUS() == _TRUE)
        {
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
            {
#if((_D4_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _ENABLE);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_D4_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxHpd5vPinCheckEvent(_D4_INPUT_PORT, _ENABLE);
#endif
            }
        }
        else
        {
            if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
            {
#if((_D4_HDMI20_SUPPORT == _ON) && (_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON))
                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                ScalerTmdsMacRxHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                ScalerTmdsMacRxHdcp2ResetProc(_D4_INPUT_PORT);
#endif
                ScalerTmdsMacRxHdcp14CableOutProc(_D4_INPUT_PORT);

#if(_D4_HDMI20_SUPPORT == _ON)
                ScalerTmdsMacRxScrambleStatusReset(_D4_INPUT_PORT);

                ScalerTmdsMacRxHpd5vPinCheckEvent(_D4_INPUT_PORT, _DISABLE);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
                // Reset SCDC
                ScalerHdmiFrlMacRxResetProc(_D4_INPUT_PORT);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
                // Reset ARC/eARC Tx
                SysAudioArcTxCableUnplugResetProc(_D4_INPUT_PORT);
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
                if((GET_POWER_STATUS() == _POWER_STATUS_OFF) || (GET_POWER_STATUS() == _POWER_STATUS_SAVING))
                {
                    ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif
            }
        }
        SysTmdsSetCablePreStatus(_D15_INPUT_PORT, GET_D15_CABLE_STATUS());
    }
#endif // End of #if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
}

//--------------------------------------------------
// Description  : TMDS Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTmdsRxHandler(void)
{
#if(_HDMI_ON_POWER_CONTROL == _ON)
    SysTmdsRxOnPowerControlByCableDetect();
#endif

    SysTmdsCableDetection();
    ScalerTmdsMacRxHpdToggleProc();
}

//--------------------------------------------------
// Description  : Scan & Set the relatived PS Wakeup HPD Toggle flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTmdsRxSetPsWakeupHpdToggle(void)
{
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        if((GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_HDMI) || (GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_DVI) || (GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_NONE))
        {
            ScalerTmdsMacRxSetPsWakeupHpdToggle(GET_RGN_INPUT_PORT(ucRegionIndex));
        }
    }
}

#if(_HDMI_ON_POWER_CONTROL == _ON)
//--------------------------------------------------
// Description  : HDMI MAC On power contral by cable detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTmdsRxOnPowerControlByCableDetect(void)
{
    ScalerTmdsMacRxOnPowerControlByCableDetect();

    if(GET_TMDS_MAC_RX_ON_POWER_SWITCH_ON() == _TRUE)
    {
        ScalerSyncHdcpEnableDownLoadKey(_ENABLE);
        SysPowerLoadHDCPKey();

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        ScalerTmdsHdcp2Rx3Initial();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        ScalerTmdsHdcp2Rx4Initial();
#endif
#endif

        CLR_TMDS_MAC_RX_ON_POWER_SWITCH_ON();
    }
}
#endif
#endif // End of #if(_HDMI_SUPPORT == _ON)
