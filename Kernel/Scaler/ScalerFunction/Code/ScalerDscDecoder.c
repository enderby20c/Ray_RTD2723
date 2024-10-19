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
// ID Code      : ScalerDscDecoder.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DSC__

#include "ScalerFunctionInclude.h"
#include "DscDecoder/ScalerDscDecoder.h"

#if(_DSC_DECODER_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructDscSupport g_stDscDecoderEnableSupport;
StructDscCapSwitch g_stDscDecoderCapSwitch;

StructDscDecoderMacMapping g_stDscDecoderMacMapping;
StructDscDecoderStreamSourceDscMacUsage g_stDscDecoderStreamSourceDscMacUsage;
StructDscDecoderStreamChange g_stDscDecoderStreamChange;

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
StructDscSupportChangeForBG g_stDscDecoderSupportChangeForBG;
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
bit g_bDscDecoderMstToSstEnable = _FALSE;
bit g_bDscDecoderMstToSstEnableChange = _FALSE;
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DSC Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderInitial(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            ScalerDscDecoder0Initial();
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            ScalerDscDecoder1Initial();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable DSC Fifo Under/OverFlow IRQ
// Input Value  : ucDscMac, bEn
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetFifoIRQ(BYTE ucDscMac, bit bEn)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            ScalerDscDecoder0SetFifoIRQ(bEn);
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            ScalerDscDecoder1SetFifoIRQ(bEn);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check DSC Fifo Under/OverFlow IRQ Status
// Input Value  : ucDscMac
// Output Value : True, False
//--------------------------------------------------
bit ScalerDscDecoderCheckFifoIRQ(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0CheckFifoIRQ();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1CheckFifoIRQ();
#endif

        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check DSC Fifo Under/OverFlow IRQ Status
// Input Value  : ucDscMac
// Output Value : True, False
//--------------------------------------------------
BYTE ScalerDscDecoderGetFifoStatus(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0GetFifoStatus();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1GetFifoStatus();
#endif

        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : ucDscMac, bEn
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetFifoWD(BYTE ucDscMac, bit bEn)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            ScalerDscDecoder0SetFifoWD(bEn);
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            ScalerDscDecoder1SetFifoWD(bEn);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set DSC Force To BackGround Colors
// Input Value  : ucDscMac, bEn
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetForceToBackGround(BYTE ucDscMac, bit bEn)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            ScalerDscDecoder0SetForceToBackGround(bEn);
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            ScalerDscDecoder1SetForceToBackGround(bEn);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Initial Setting for DSC Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : Source Type
//--------------------------------------------------
EnumSourceType ScalerDscDecoderMacRxScanInputPort(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    EnumSourceType enumSourceType = _SOURCE_NONE;
    BYTE ucDscMac = GET_DX_PORT_DSC_MAC_X_MAPPING(enumInputPort);

    DebugMessageDSC("DSC Scan Input Type", ucDscMac);

    // EnumInput Port Mapping Rx DSC Reset
    ScalerDscDecoderDxMacReset(enumInputPort);

    switch(enumPortType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            enumSourceType = ScalerTmdsMacRxScanInputPort(enumInputPort, enumPortType);
#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            enumSourceType = ScalerDpMacStreamRxScanInputPort(enumInputPort, enumPortType);
#endif
            break;
#endif

        default:
            break;
    }

    // Check Source Type
    if(enumSourceType == _SOURCE_NONE)
    {
        DebugMessageDSC("Dx SOURCE NONE", 0x00);

        return _SOURCE_NONE;
    }

    // DSC Disable, Return Dp/ HDMI;
    if(ScalerDscDecoderPreCheck(enumInputPort, enumPortType, ucDscMac) == _FALSE)
    {
        DebugMessageDSC("Dx Stream Source DP/HDMI, DSC Disable", enumInputPort);

        ScalerDscDecoderPowerCutControl(ucDscMac, _DSC_POWER_CUT_ON);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        ScalerDpRxDscCancelPpsTimerEvent(enumInputPort);
#endif
        return enumSourceType;
    }

    // DSC Enable, Power Cut Off
    ScalerDscDecoderPowerCutControl(ucDscMac, _DSC_POWER_CUT_OFF);

    // DSC Mac Initial
    ScalerDscDecoderInitial(ucDscMac);

    // Set DSC Input Stream Source
    SET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(ScalerDscDecoderGetDscMacStreamSource(ucDscMac), ucDscMac);

    // Dsc Decoder ScanInput Port
    if(ScalerDscDecoderMacScanInputPort(ucDscMac) == _TRUE)
    {
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(enumPortType == _PORT_DP)
        {
            // DP Inner Info Setting After DP Rx Stream Judge
            ScalerDpMacDscStreamAfterJudgeSetting(ScalerDpRxGetMacSwitch(enumInputPort));
        }
#endif
        DebugMessageDSC("Dx Stream Source DP/HDMI, DSC Enable", enumInputPort);

        return enumSourceType;
    }
    else
    {
        CLR_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(ScalerDscDecoderGetDscMacStreamSource(ucDscMac));

        return _SOURCE_NONE;
    }
}
//--------------------------------------------------
// Description  : Dsc Decoder Mac ScanInputport
// Input Value  : Input Port
// Output Value : Source Type
//--------------------------------------------------
bit ScalerDscDecoderMacScanInputPort(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0MacScanInputPort();
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1MacScanInputPort();
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC Pre Check
// Input Value  : ucInputPortType
// Output Value : True / False
//--------------------------------------------------
bit ScalerDscDecoderPreCheck(EnumInputPort enumInputPort, EnumPortType enumPortType, BYTE ucDscMac)
{
    enumInputPort = enumInputPort;

    if(ucDscMac == _DSC_MAC_NONE)
    {
        return _FALSE;
    }

    switch(enumPortType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if((ScalerHdmiFrlMacRxGetCvtemReceived(enumInputPort) == _FALSE) || (ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_TMDS_MAC))
            {
                DebugMessageDSC("0. HDMI DSC Not Support yet", 0x00);
                return _FALSE;
            }
#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDpMacDscGetDscFlagStatus(ScalerDscDecoderGetDpMacRxxInput(ucDscMac)) == _FALSE)
            {
                DebugMessageDSC("0. DP DSC No Support", 0x00);
                return _FALSE;
            }

            if(ScalerDpMacDscRxDscStreamCheck(ScalerDscDecoderGetDpMacRxxInput(ucDscMac)) == _FALSE)
            {
                DebugMessageDSC("0.DSC Stream NOT ready", 0x00);
                return _FALSE;
            }
#endif
            break;
#endif
        default:
            return _FALSE;
            break;
    }

    DebugMessageDSC("0. DSC Start", 0x00);

    return _TRUE;
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Check
// Input Value  : enumInputPort, enumPortType
// Output Value : False --> CompressionStream_Flag VB-ID[6] Changed and Video Stream without Compression
//--------------------------------------------------
bit ScalerDscDecoderStreamCheck(BYTE ucDscMac)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = ScalerDscDecoderGetDscMacStreamSource(ucDscMac);

    switch(enumDscDecoderMacStreamSourceType)
    {
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        case _DSC_STREAM_SOURCE_DP_MAC_RX0:
        case _DSC_STREAM_SOURCE_DP_MAC_RX1:
        case _DSC_STREAM_SOURCE_DP_MAC_RX2:
            return ScalerDpMacDscRxDscStreamCheck(ScalerDscDecoderGetDpMacRxxInput(ucDscMac));
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX3:
            return ScalerHdmiFrlMacRxGetCvtemReceived(ScalerTmdsMacRxRxDxMapping(_RX3));

        case _DSC_STREAM_SOURCE_HDMI_MAC_RX4:
            return ScalerHdmiFrlMacRxGetCvtemReceived(ScalerTmdsMacRxRxDxMapping(_RX4));
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC Fifo Check
// Input Value  : enumInputPort
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDscDecoderFifoCheck(BYTE ucDscMac, EnumDscFifoCheckCondition enumDscFifoCheckCondition)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0FifoCheck(enumDscFifoCheckCondition);
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1FifoCheck(enumDscFifoCheckCondition);
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC PPS Change Check
// Input Value  : None
// Output Value : True --> DSC PPS Not Change
//--------------------------------------------------
bit ScalerDscDecoderPpsChangeCheck(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0PpsChangeCheck();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1PpsChangeCheck();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC0 Decode Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderDecEnable(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            ScalerDscDecoder0DecEnable();
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            ScalerDscDecoder1DecEnable();
            break;
#endif

        default:
            break;
    }
    return;
}

//--------------------------------------------------
// Description  : Dx Port DSC Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderReset(EnumInputPort enumInputPort)
{
    BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort);

    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            ScalerDscDecoder0MacReset();
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            ScalerDscDecoder1MacReset();
            break;
#endif

        default:
            break;
    }

#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
    ScalerDpRxDscCancelPpsTimerEvent(enumInputPort);
#endif

    ScalerDscDecoderDxMacReset(enumInputPort);

#if((_DP_MAC_TX_SUPPORT == _ON) && (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
    if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) && (ScalerDpMacTxCloneGetCurrentInputPort() == enumInputPort))
    {
        CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
    }
#endif
}

//--------------------------------------------------
// Description  : DSC Dx Mac Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderDxMacReset(EnumInputPort enumInputPort)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = ScalerDscDecoderDxInputPortDscMacStreamSourceMapping(enumInputPort);

#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
    ScalerDpMacStreamRxDscSetStreamIRQAndWD(enumInputPort, _DISABLE);
#endif

    ScalerDscDecoderSetChange(enumDscDecoderMacStreamSourceType, _DISABLE);

    CLR_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(enumDscDecoderMacStreamSourceType);
}

//--------------------------------------------------
// Description  : DSC Get Stream Timing Frame Rate
// Input Value  : enumInputPort
// Output Value : Frame Rate (Hz)
//--------------------------------------------------
WORD ScalerDscDecoderGetStreamFrameRate(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ((GET_DSC0_STREAM_FRAME_RATE() == 0) ? 1 : GET_DSC0_STREAM_FRAME_RATE());
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ((GET_DSC1_STREAM_FRAME_RATE() == 0) ? 1 : GET_DSC1_STREAM_FRAME_RATE());
#endif
        default:
            break;
    }
    return 1;
}

//--------------------------------------------------
// Description  : DSC Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderResetAllPort(void)
{
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    ScalerDscDecoderReset(_D0_INPUT_PORT);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    ScalerDscDecoderReset(_D1_INPUT_PORT);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
    ScalerDscDecoderReset(_D2_INPUT_PORT);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
    ScalerDscDecoderReset(_D3_INPUT_PORT);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
    ScalerDscDecoderReset(_D4_INPUT_PORT);
#endif
}

//--------------------------------------------------
// Description  : DSC force background
// Input Value  : enumInputPort,Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderForceBackgroundSetting(BYTE ucDscMac, bit bEnable)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            ScalerDscDecoder0ForceBackgroundSetting(bEnable);
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            ScalerDscDecoder1ForceBackgroundSetting(bEnable);
            break;
#endif

        default:
            break;
    }
}

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI DSC Flag Status
// Input Value  : None
// Output Value : None
//------------------------------------------------
bit ScalerDscDecoderGetHdmiDscFlagStatus(EnumInputPort enumHdmiInputPort)
{
#if(_HDMI_SUPPORT == _ON)
    switch(ScalerTmdsMacRxDxRxMapping(enumHdmiInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
            {
                DebugMessageDSC("Rx3 Hdmi DSC Flag Enable", 0x00);
                return _TRUE;
            }
#endif
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
            {
                DebugMessageDSC("Rx4 Hdmi DSC Flag Enable", 0x00);
                return _TRUE;
            }
#endif
            break;
#endif


        default:
            break;
    }
#endif

    return _FALSE;
}
#endif

#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Dp DSC Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoderDpCapabilitySwitchProc(EnumInputPort enumInputPort)
{
    if(ScalerDscDecoderGetCapSwitch(enumInputPort) == _TRUE)
    {
        ScalerDscDecoderSetCapSwitch(enumInputPort, _DISABLE);

        ScalerDpAuxRxDscDpcdSetting(enumInputPort);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        ScalerDpMstRxDscVirtualDpcdSetting(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort));
#endif

        if(ScalerDscDecoderGetSupport(enumInputPort) == _DSC_DECODER_SUPPORT_ON)
        {
            DebugMessageDSC("DSC sync cap change on", 0x00);

            ScalerDpAuxRxDscIrqCtrl(enumInputPort, _ENABLE);
        }
        else
        {
            DebugMessageDSC("DSC sync cap change off", 0x00);

            ScalerDpAuxRxDscIrqCtrl(enumInputPort, _DISABLE);
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Switch DP DSC Support
// Input Value  : Hotplug Type and DSC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSyncDpSupportSwitch(EnumInputPort enumInputPort, EnumDscDecoderSupport enumDscDecoderSupport)
{
    if(ScalerDscDecoderGetSupport(enumInputPort) != enumDscDecoderSupport)
    {
        SET_DP_RX_CAPABILITY_SWITCHED();
        ScalerDscDecoderSetCapSwitch(enumInputPort, _ENABLE);
        ScalerDscDecoderSetSupport(enumInputPort, enumDscDecoderSupport);
    }
}

//--------------------------------------------------
// Description  : DSC DP CRC Calculate
// Input Value  : NenumInputPortone
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoderDpCrcCalculate(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0DpCrcCalculate();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1DpCrcCalculate();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDscDecoderCheckVgipVsBypass(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0CheckVgipVsBypass();
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1CheckVgipVsBypass();
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DSC Get Change Status
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoderGetChange(EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType)
{
    switch(enumDscDecoderMacStreamSourceType)
    {
        case _DSC_STREAM_SOURCE_DP_MAC_RX0:
        case _DSC_STREAM_SOURCE_DP_MAC_RX1:
        case _DSC_STREAM_SOURCE_DP_MAC_RX2:
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX3:
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX4:
        case _DSC_STREAM_SOURCE_DP_MAC_RX4:
            return (bit)GET_DSC_STREAM_CHANGE(enumDscDecoderMacStreamSourceType);

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC Set Change Status
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetChange(EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType, bit bEnable)
{
    switch(enumDscDecoderMacStreamSourceType)
    {
        case _DSC_STREAM_SOURCE_DP_MAC_RX0:
        case _DSC_STREAM_SOURCE_DP_MAC_RX1:
        case _DSC_STREAM_SOURCE_DP_MAC_RX2:
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX3:
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX4:
        case _DSC_STREAM_SOURCE_DP_MAC_RX4:

            SET_DSC_STREAM_CHANGE(enumDscDecoderMacStreamSourceType, bEnable);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC Get Support Status
// Input Value  : enumInputPort, enumPortType
// Output Value : enumDscDecoderSupport
//--------------------------------------------------
EnumDscDecoderSupport ScalerDscDecoderGetSupport(EnumInputPort enumInputPort)
{
    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);

    if(enumPortType == _PORT_HDMI)
    {
#if((_HDMI_SUPPORT == _ON) && (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON))
        switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
        {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            case _RX3:
#if(_HDMI_FRL_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
                return _TRUE;
#endif
                break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            case _RX4:
#if(_HDMI_FRL_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
                return _TRUE;
#endif
                break;
#endif

            default:
                break;
        }
#endif
    }
    else if(enumPortType == _PORT_DP)
    {
#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
        switch(enumInputPort)
        {
            case _D0_INPUT_PORT:
                return GET_DSC_D0_SUPPORT();

            case _D1_INPUT_PORT:
                return GET_DSC_D1_SUPPORT();

            case _D2_INPUT_PORT:
                return GET_DSC_D2_SUPPORT();

            case _D3_INPUT_PORT:
                return GET_DSC_D3_SUPPORT();

            case _D4_INPUT_PORT:
                return GET_DSC_D4_SUPPORT();

            case _D5_INPUT_PORT:
                return GET_DSC_D5_SUPPORT();

            default:
                break;
        }
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC Set Support Status
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetSupport(EnumInputPort enumInputPort, EnumDscDecoderSupport enumDscDecoderSupport)
{
    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);

    if(enumPortType == _PORT_HDMI)
    {
        return;
    }
    else if(enumPortType == _PORT_DP)
    {
#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
        switch(enumInputPort)
        {
            case _D0_INPUT_PORT:
                SET_DSC_D0_SUPPORT(enumDscDecoderSupport);
                break;

            case _D1_INPUT_PORT:
                SET_DSC_D1_SUPPORT(enumDscDecoderSupport);
                break;

            case _D2_INPUT_PORT:
                SET_DSC_D2_SUPPORT(enumDscDecoderSupport);
                break;

            case _D3_INPUT_PORT:
                SET_DSC_D3_SUPPORT(enumDscDecoderSupport);
                break;

            case _D4_INPUT_PORT:
                SET_DSC_D4_SUPPORT(enumDscDecoderSupport);
                break;

            case _D5_INPUT_PORT:
                SET_DSC_D5_SUPPORT(enumDscDecoderSupport);
                break;

            default:
                break;
        }
#endif
    }
}

//--------------------------------------------------
// Description  : DSC Get Capability Switch
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoderGetCapSwitch(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return GET_DSC_D0_CAPABILITY_SWITCH();
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return GET_DSC_D1_CAPABILITY_SWITCH();
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return GET_DSC_D2_CAPABILITY_SWITCH();
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            return GET_DSC_D3_CAPABILITY_SWITCH();
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            return GET_DSC_D4_CAPABILITY_SWITCH();
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            return GET_DSC_D5_CAPABILITY_SWITCH();
            break;
#endif

        default:
            break;
    }

    return _DISABLE;
}

//--------------------------------------------------
// Description  : DSC Set Capability Switch
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetCapSwitch(EnumInputPort enumInputPort, bit bEnable)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            SET_DSC_D0_CAPABILITY_SWITCH(bEnable);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            SET_DSC_D1_CAPABILITY_SWITCH(bEnable);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            SET_DSC_D2_CAPABILITY_SWITCH(bEnable);
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            SET_DSC_D3_CAPABILITY_SWITCH(bEnable);
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            SET_DSC_D4_CAPABILITY_SWITCH(bEnable);
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            SET_DSC_D5_CAPABILITY_SWITCH(bEnable);
            break;
#endif

        default:
            break;
    }
}

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC Decoder Mac Arbiter Mst2sst
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderMacArbiterDpMstToSst(EnumInputPort enumInputPort)
{
    BYTE ucDscMac = _DSC_MAC_NONE;

    ucDscMac = GET_MST2SST_BRANCH_DSC_X_MAPPING();

    ScalerDscDecoderMacSetDscStreamSource(enumInputPort, _PORT_DP, ucDscMac, _DSC_MAC_APPLY_MST2SST);

    ScalerDscDecoderPowerCutControl(ucDscMac, _DSC_POWER_CUT_ON);
}

//--------------------------------------------------
// Description  : Switch DP DSC Support
// Input Value  : Hotplug Type and DSC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSyncDpMstToSstSupportSwitch(EnumDscDecoderSupport enumDscDecoderSupport)
{
    if(ScalerDscDecoderDpMstToSstGetSupport() != enumDscDecoderSupport)
    {
        ScalerDscDecoderDpMstToSstSetSupport(enumDscDecoderSupport);

        ScalerDscDecoderSetMstToSstCapSwitch(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : DSC Get MST2SST Support Status
// Input Value  : None
// Output Value : enumDscDecoderSupport
//--------------------------------------------------
EnumDscDecoderSupport ScalerDscDecoderDpMstToSstGetSupport(void)
{
    return GET_DSC_DP_MST2SST_BRANCH_SUPPORT();
}

//--------------------------------------------------
// Description  : DSC Set MST2SST Support Status
// Input Value  : None
// Output Value : enumDscDecoderSupport
//--------------------------------------------------
void ScalerDscDecoderDpMstToSstSetSupport(EnumDscDecoderSupport enumDscDecoderSupport)
{
    SET_DSC_DP_MST2SST_BRANCH_SUPPORT(enumDscDecoderSupport);
}

//--------------------------------------------------
// Description  : DSC Set MST2SST Port1 Capability Switch
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetMstToSstCapSwitch(bit bEnable)
{
    SET_DSC_DP_MST2SST_CAPABILITY_SWITCH(bEnable);
}

//--------------------------------------------------
// Description  : DSC Set MST2SST Port1 Capability Switch
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoderGetMstToSstCapSwitch(void)
{
    return GET_DSC_DP_MST2SST_CAPABILITY_SWITCH();
}

#endif

//--------------------------------------------------
// Description  : Set DP Pixel Clock
// Input Value  : DP Stream Clock
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetNativeInputPixelClock(EnumInputPort enumInputPort, DWORD ulStreamClk)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

        case _D0_INPUT_PORT:

            SET_D0_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

        case _D1_INPUT_PORT:

            SET_D1_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

        case _D2_INPUT_PORT:

            SET_D2_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

        case _D3_INPUT_PORT:

            SET_D3_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

        case _D4_INPUT_PORT:

            SET_D4_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

        case _D5_INPUT_PORT:

            SET_D5_NATIVE_INPUT_PIXEL_CLK(ulStreamClk / 100000);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DSC Htotal
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Htotal
//--------------------------------------------------
WORD ScalerDscDecoderGetDscHtotal(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_HTOTAL();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_HTOTAL();
#endif

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DSC Version
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Version
//--------------------------------------------------
BYTE ScalerDscDecoderGetDscVersion(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_VERSION();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_VERSION();
#endif

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DSC Slice Height
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Slice Height
//--------------------------------------------------
WORD ScalerDscDecoderGetDscSliceHeight(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_SLICE_HEIGHT();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_SLICE_HEIGHT();
#endif

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DSC Slice Width
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Slice Width
//--------------------------------------------------
WORD ScalerDscDecoderGetDscSliceWidth(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_SLICE_WIDTH();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_SLICE_WIDTH();
#endif

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DSC Chunk Size
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Chunk Size
//--------------------------------------------------
WORD ScalerDscDecoderGetDscChunkSize(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_CHUNK_SIZE_CURRENT();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_CHUNK_SIZE_CURRENT();
#endif

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DSC Bit Per Component Value
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Bit Per Component Value
//--------------------------------------------------
WORD ScalerDscDecoderGetDscBpc(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_COLOR_BPC();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_COLOR_BPC();
#endif

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DSC Bit Per Pixel Value
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Bit Per Pixel Value
//--------------------------------------------------
WORD ScalerDscDecoderGetDscBitPerPixel(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_COLOR_BPP_CURRENT();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_COLOR_BPP_CURRENT();
#endif

        default:
            break;
    }

    return 0x00;
}

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DSC HCactive
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC HCactive
//--------------------------------------------------
WORD ScalerDscDecoderGetDscHCActive(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_HC_ACTIVE();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_HC_ACTIVE();
#endif

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DSC HCblank
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC HCblank
//--------------------------------------------------
WORD ScalerDscDecoderGetDscHCBlank(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_HC_BLANK();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_HC_BLANK();
#endif

        default:
            break;
    }

    return 0x00;
}
#endif

//--------------------------------------------------
// Description  : Get DSC Pic Width
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Hwidth
//--------------------------------------------------
WORD ScalerDscDecoderGetDscPicWidth(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_PIC_WIDTH();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_PIC_WIDTH();
#endif

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DSC Native 420 Mode
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Native 420
//--------------------------------------------------
bit ScalerDscDecoderGetNative420Mode(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return (bit)(GET_DSC0_COLOR_NATIVE_420());
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return (bit)(GET_DSC1_COLOR_NATIVE_420());
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DSC Native Mode
// Input Value  : enumInputPort -> input port for DSC
// Output Value : DSC Native Mode
//--------------------------------------------------
bit ScalerDscDecoderGetNativeMode(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return (bit)(GET_DSC0_COLOR_NATIVE_MODE());
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return (bit)(GET_DSC1_COLOR_NATIVE_MODE());
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DSC PPS Color Space Info
// Input Value  : ucDscMac
// Output Value : DSC PPS Color Space Info
//--------------------------------------------------
EnumColorSpace ScalerDscDecoderGetPpsColorSpaceInfo(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:

            if(GET_DSC0_COLOR_RGB_CURRENT() == _TRUE)
            {
                return _COLOR_SPACE_RGB;
            }

            if(GET_DSC0_COLOR_NATIVE_420_CURRENT() == _TRUE)
            {
                return _COLOR_SPACE_YCBCR420;
            }

            if((GET_DSC0_COLOR_NATIVE_422_CURRENT() == _TRUE) || (GET_DSC0_COLOR_SIMPLE_422_CURRENT() == _TRUE))
            {
                return _COLOR_SPACE_YCBCR422;
            }

            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            if(GET_DSC1_COLOR_RGB_CURRENT() == _TRUE)
            {
                return _COLOR_SPACE_RGB;
            }

            if(GET_DSC1_COLOR_NATIVE_420_CURRENT() == _TRUE)
            {
                return _COLOR_SPACE_YCBCR420;
            }

            if((GET_DSC1_COLOR_NATIVE_422_CURRENT() == _TRUE) || (GET_DSC1_COLOR_SIMPLE_422_CURRENT() == _TRUE))
            {
                return _COLOR_SPACE_YCBCR422;
            }

            break;
#endif

        default:
            break;
    }

    return _COLOR_SPACE_YCBCR444;
}

//--------------------------------------------------
// Description  : Get DSC MAC Pixel Mode
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
BYTE ScalerDscDecoderGetPixelMode(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0GetPixelMode();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1GetPixelMode();
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get DSC Chunk Size
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
WORD ScalerDscDecoderGetChunkSizeCurrent(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_CHUNK_SIZE_CURRENT();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_CHUNK_SIZE_CURRENT();
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get DSC Horizontal Slice Count
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
BYTE ScalerDscDecoderGetHorSliceCount(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return GET_DSC0_HOR_SLICE_CNT();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return GET_DSC1_HOR_SLICE_CNT();
#endif

        default:
            break;
    }

    return 0;
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC Decoder Get Element
// Input Value  : enumType --> Type
// Output Value : Conetent
//--------------------------------------------------
WORD ScalerDscDecoderGetElement(BYTE ucDscMac, EnumDpStreamPpsElement enumElement)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            return ScalerDscDecoder0GetElement(enumElement);
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            return ScalerDscDecoder1GetElement(enumElement);
#endif

        default:
            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : DSC Decoder Mac Set Stream Source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderMacSetDscStreamSource(EnumInputPort enumInputPort, EnumPortType enumPortType, BYTE ucDscMac, EnumDscDecoderMacApplyType enumDscDecoderMacApplyType)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_NONE;
    EnumDpMacSel enumDpMacSel = _DP_MAC_NONE;

    switch(enumPortType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(ScalerTmdsMacRxDxRxMapping(enumInputPort));
#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            if(enumDscDecoderMacApplyType == _DSC_MAC_APPLY_DX_PORT)
            {
                enumDpMacSel = ScalerDpRxGetMacSwitch(enumInputPort);
            }
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            else
            {
                enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);
            }
#endif
            enumDscDecoderMacStreamSourceType = ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(enumDpMacSel);
#endif
            break;
#endif
        default:
            break;
    }


    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:
            SET_DSC_DECODER_MAC_0_STREAM_SOURCE(enumDscDecoderMacStreamSourceType);
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:
            SET_DSC_DECODER_MAC_1_STREAM_SOURCE(enumDscDecoderMacStreamSourceType);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC Decoder Mac Get Enable
// Input Value  : ucDscMac
// Output Value : _true or _false
//--------------------------------------------------
bit ScalerDscDecoderGetDscDecoderMacEnable(BYTE ucDscMac)
{
    if(GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(_DSC_STREAM_SOURCE_DP_MAC_RX0) == ucDscMac)
    {
        return _TRUE;
    }

    if(GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(_DSC_STREAM_SOURCE_DP_MAC_RX1) == ucDscMac)
    {
        return _TRUE;
    }

    if(GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(_DSC_STREAM_SOURCE_DP_MAC_RX2) == ucDscMac)
    {
        return _TRUE;
    }

    if(GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(_DSC_STREAM_SOURCE_DP_MAC_RX4) == ucDscMac)
    {
        return _TRUE;
    }

    if(GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(_DSC_STREAM_SOURCE_HDMI_MAC_RX3) == ucDscMac)
    {
        return _TRUE;
    }

    if(GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(_DSC_STREAM_SOURCE_HDMI_MAC_RX4) == ucDscMac)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC Decoder Mac Get Input Port
// Input Value  : ucDscMac
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDscDecoderGetDxInputPort(BYTE ucDscMac)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = ScalerDscDecoderGetDscMacStreamSource(ucDscMac);

    switch(enumDscDecoderMacStreamSourceType)
    {
#if(_DP_SUPPORT == _ON)
        case _DSC_STREAM_SOURCE_DP_MAC_RX0:
#if(_DP_MAC_RX0_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0);
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX1:
#if(_DP_MAC_RX1_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX2:
#if(_DP_MAC_RX2_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_2);
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX4:
#if(_DP_MAC_RX4_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_4);
#endif
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX3:
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
            return ScalerTmdsMacRxRxDxMapping(_RX3);
#endif
            break;

        case _DSC_STREAM_SOURCE_HDMI_MAC_RX4:
#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            return ScalerTmdsMacRxRxDxMapping(_RX4);
#endif
            break;
#endif
        default:
            return _NO_INPUT_PORT;
    }

    return _NO_INPUT_PORT;
}

#if((_HDMI_SUPPORT == _ON) && (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DSC Decoder Mac Get Hdmi Rxx
// Input Value  : ucDscMac
// Output Value : EnumInputPort
//--------------------------------------------------
EnumRx ScalerDscDecoderGetHdmiMacRxxInput(BYTE ucDscMac)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = ScalerDscDecoderGetDscMacStreamSource(ucDscMac);

    switch(enumDscDecoderMacStreamSourceType)
    {
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX3:
            return _RX3;

        case _DSC_STREAM_SOURCE_HDMI_MAC_RX4:
            return _RX4;

        default:
            return _RX_MAP_NONE;
    }

    return _RX_MAP_NONE;
}

//--------------------------------------------------
// Description  : DP MAC RXx Get Dsc Decoder Mac Index
// Input Value  : EnumDpMacSel
// Output Value : ucDscMac
//--------------------------------------------------
BYTE ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(EnumRx enumRx)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_NONE;

    enumDscDecoderMacStreamSourceType = ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(enumRx);

    return GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(enumDscDecoderMacStreamSourceType);
}

//--------------------------------------------------
// Description  : HDMI Mac Rxx Mapping to Dsc Stream Source
// Input Value  : EnumRx
// Output Value : ucDscMac
//--------------------------------------------------
EnumDscDecoderMacStreamSourceType ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(EnumRx enumRx)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_NONE;

    switch(enumRx)
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_HDMI_MAC_RX3;
#endif
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_HDMI_MAC_RX4;
#endif
            break;
#endif
        default:
            break;
    }

    return enumDscDecoderMacStreamSourceType;
}
#endif

#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DSC Decoder Mac Get Dp Mac Rxx
// Input Value  : ucDscMac
// Output Value : EnumInputPort
//--------------------------------------------------
EnumDpMacSel ScalerDscDecoderGetDpMacRxxInput(BYTE ucDscMac)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = ScalerDscDecoderGetDscMacStreamSource(ucDscMac);

    switch(enumDscDecoderMacStreamSourceType)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DSC_STREAM_SOURCE_DP_MAC_RX0:
            return _DP_MAC_0;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DSC_STREAM_SOURCE_DP_MAC_RX1:
            return _DP_MAC_1;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DSC_STREAM_SOURCE_DP_MAC_RX2:
            return _DP_MAC_2;
#endif

        default:
            return _DP_MAC_NONE;
    }

    return _DP_MAC_NONE;
}

//--------------------------------------------------
// Description  : DP MAC RXx Get Dsc Decoder Mac Index
// Input Value  : EnumDpMacSel
// Output Value : ucDscMac
//--------------------------------------------------
BYTE ScalerDscDecoderDpMacRxxGetDscDecoderMac(EnumDpMacSel enumDpMacSel)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_NONE;

    enumDscDecoderMacStreamSourceType = ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(enumDpMacSel);

    return GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(enumDscDecoderMacStreamSourceType);
}

//--------------------------------------------------
// Description  : Dp Mac Rxx Mapping to Dsc Stream Source
// Input Value  : EnumDpMacSel
// Output Value : ucDscMac
//--------------------------------------------------
EnumDscDecoderMacStreamSourceType ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(EnumDpMacSel enumDpMacSel)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_NONE;

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_DP_MAC_RX0;
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_DP_MAC_RX1;
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_DP_MAC_RX2;
#endif
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_DP_MAC_RX4;
#endif
            break;
#endif

        default:
            break;
    }

    return enumDscDecoderMacStreamSourceType;
}

//--------------------------------------------------
// Description  : Dsc Stream Source Mapping to DpMac MAC RXX
// Input Value  : EnumDscDecoderMacStreamSourceType
// Output Value : EnumDpMacSel
//--------------------------------------------------
EnumDpMacSel ScalerDscDecoderDscMacStreamSourceDpMacRxxMapping(EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType)
{
    EnumDpMacSel enumDpMacSel = _DP_MAC_NONE;

    switch(enumDscDecoderMacStreamSourceType)
    {
        case _DSC_STREAM_SOURCE_DP_MAC_RX0:
#if(_DP_MAC_RX0_SUPPORT == _ON)
            enumDpMacSel = _DP_MAC_0;
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX1:
#if(_DP_MAC_RX1_SUPPORT == _ON)
            enumDpMacSel = _DP_MAC_1;
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX2:
#if(_DP_MAC_RX2_SUPPORT == _ON)
            enumDpMacSel = _DP_MAC_2;
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX4:
#if(_DP_MAC_RX4_SUPPORT == _ON)
            enumDpMacSel = _DP_MAC_4;
#endif
            break;

        default:
            break;
    }

    return enumDpMacSel;
}
#endif
//--------------------------------------------------
// Description  : Dx Mapping to Dsc Stream Source
// Input Value  : EnumInputPort
// Output Value : EnumDpMacSel
//--------------------------------------------------
EnumDscDecoderMacStreamSourceType ScalerDscDecoderDxInputPortDscMacStreamSourceMapping(EnumInputPort enumInputPort)
{
    switch(ScalerSyncGetPortType(enumInputPort))
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            return ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(ScalerTmdsMacRxDxRxMapping(enumInputPort));
#endif
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            return ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(ScalerDpRxGetMacSwitch(enumInputPort));
#endif
            break;
#endif
        default:
            break;
    }

    return _DSC_STREAM_SOURCE_NONE;
}
//--------------------------------------------------
// Description  : Input Port Get Dsc Decoder Mac Index
// Input Value  : EnumDpMacSel
// Output Value : ucDscMac
//--------------------------------------------------
BYTE ScalerDscDecoderDxInputPortGetDscDecoderMac(EnumInputPort enumInputPort)
{
    BYTE ucDscMac = _DSC_MAC_NONE;
    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);

    switch(enumPortType)
    {
#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(ScalerDpRxGetMacSwitch(enumInputPort));
#endif
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            ucDscMac = ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(ScalerTmdsMacRxDxRxMapping(enumInputPort));
#endif
            break;
#endif
        default:
            break;
    }

    return ucDscMac;
}

//--------------------------------------------------
// Description  : Get Dsc Decoder Mac Stream Source
// Input Value  : EnumDpMacSel
// Output Value : ucDscMac
//--------------------------------------------------
EnumDscDecoderMacStreamSourceType ScalerDscDecoderGetDscMacStreamSource(BYTE ucDscMac)
{
    switch(ucDscMac)
    {
        case _DSC_MAC_0:
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
            return GET_DSC_DECODER_MAC_0_STREAM_SOURCE();
#endif
            break;

        case _DSC_MAC_1:
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
            return GET_DSC_DECODER_MAC_1_STREAM_SOURCE();
#endif
            break;

        default:
            break;
    }

    return _DSC_STREAM_SOURCE_NONE;
}

//--------------------------------------------------
// Description  : DSC Decoder Mac Get Input Port
// Input Value  : ucDscMac
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDscDecoderGetDxInputPort_EXINT0(BYTE ucDscMac)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = ScalerDscDecoderGetDscMacStreamSource(ucDscMac);

    switch(enumDscDecoderMacStreamSourceType)
    {
#if(_DP_SUPPORT == _TRUE)
        case _DSC_STREAM_SOURCE_DP_MAC_RX0:
#if(_DP_MAC_RX0_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_0);
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX1:
#if(_DP_MAC_RX1_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_1);
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX2:
#if(_DP_MAC_RX2_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_2);
#endif
            break;

        case _DSC_STREAM_SOURCE_DP_MAC_RX4:
#if(_DP_MAC_RX4_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_4);
#endif
            break;
#endif

#if(_HDMI_SUPPORT == _TRUE)
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX3:
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
            return ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);
#endif
            break;

        case _DSC_STREAM_SOURCE_HDMI_MAC_RX4:
#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            return ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4);
#endif
            break;
#endif

        default:
            return _NO_INPUT_PORT;
    }

    return _NO_INPUT_PORT;
}
#endif
