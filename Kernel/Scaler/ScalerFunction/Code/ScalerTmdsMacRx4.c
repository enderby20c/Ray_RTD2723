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
// ID Code      : ScalerTmdsMacRx4.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSMACRX4__

#include "ScalerFunctionInclude.h"
#include "TmdsMacRx4/ScalerTmdsMacRx4.h"


#if(_TMDS_MAC_RX4_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructTMDSCtrlInfo g_stTmdsMacRx4CtrlInfo;

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
volatile StructHdmiSpdInfo g_stTmdsMacRx4SpdInfo;
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
volatile StructHdmiSpdFsInfo g_stTmdsMacRx4SpdFsInfo;
#endif
#endif

volatile WORD g_usTmdsMacRx4ClkCount;
WORD g_usTmdsMacRx4OffLineMeasureClk;

BYTE g_ucTmdsMacRx4DdcramNackStatus;

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
BYTE g_ucTmdsMacRx4AviInfo;
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
volatile StructHdmi21EmpInfo g_stTmdsMacRx4Hdmi21EmpInfo;
#if(_HDMI21_VRR_SUPPORT == _ON)
StructHdmi21EdidVrrCap g_stTmdsMacRx4Hdmi21EdidVrrCap;
#endif
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
StructHdmiSbtmInfo g_stTmdsMacRx4HdmiSbtmInfo;
#endif
#endif

EnumDDomainRegion g_enumTmdsMacRx4IrqForceBackgrd;

BYTE g_ucTmdsMacRx4Z0Status;
BYTE g_ucTmdsMacRx4SlaveAddr;
BYTE g_ucTmdsMacRx4HdcpType;

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
BYTE g_pucTmdsMacRx4Caps[3];
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4GetFreeSyncIIData(BYTE *pucFreeSyncIIData)
{
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
    if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
    {
        ScalerHdmiFrlMacRx4GetFreeSyncIIData(pucFreeSyncIIData);
    }
    else
#endif
    {
        memcpy(&pucFreeSyncIIData[0], &g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[0], 11);
    }
}
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS SBTM Data
// Input Value  : pucSBTMData --> SBTM data
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4GetSBTMData(BYTE *pucSBTMData)
{
    memcpy(&pucSBTMData[0], &g_stTmdsMacRx4HdmiSbtmInfo, 8);
}
#endif // End of #if(_HDMI_SBTM_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4GetHDR10Data(BYTE *pucHDRData)
{
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
    if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
    {
        ScalerHdmiFrlMacRx4GetHDR10Data(pucHDRData);
    }
    else
#endif
    {
        BYTE ucAddressportBackup = 0x00;
        bit bBackupStatus = _FALSE;

        if(CPU32_IS_INSIDE_INTERRUPT() == _TRUE)
        {
            ucAddressportBackup = ScalerGetByte(P73_D0_HDMI_PSAP2);
            bBackupStatus = _TRUE;
        }

        ScalerGetDataPortByte(P73_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
        ScalerGetDataPortByte(P73_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
        ScalerGetDataPortByte(P73_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);

        if(bBackupStatus == _TRUE)
        {
            ScalerSetByte(P73_D0_HDMI_PSAP2, ucAddressportBackup);
        }
    }
}
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
DWORD ScalerTmdsMacRx4FreeSyncHDMIGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    WORD usFreesyncVfreqmax = 0;
    WORD usFreesyncVfreqmin = 0;
    DWORD ulTargetOutputPixelRate = 0;
    WORD usAmdVfreqMaxBit = 0;
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
    {
        usAmdVfreqMaxBit = _8_BIT;
    }
    else
    {
        usAmdVfreqMaxBit = _10_BIT;
    }

    if(GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6) // HDMI 21 Rx
        {
            return ScalerHdmiFrlMacRx4FreeSyncHDMIGetAmdSpdInfo(enumContent);
        }
        else
#endif
        {
            if(enumContent == _SPD_INFO_OUI)
            {
                return (TO_DWORD(0, g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[3], g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[2], g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[1]));
            }

            if((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[1] == 0x1A) && (g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[2] == 0x00) && (g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[3] == 0x00))
            {
                switch(enumContent)
                {
                    case _SPD_INFO_FREESYNC_SUPPORT:

                        return (((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x01) != 0x00) ? _ON : _OFF);

                    case _SPD_INFO_FREESYNC_ENABLE:

                        return ((((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x02) >> 1) != 0x00) ? _ON : _OFF);

                    case _SPD_INFO_FREESYNC_ACTIVE:

                        return ((((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x04) >> 2) != 0x00) ? _ON : _OFF);

                    case _SPD_INFO_FRAME_TYPE:

                        return (((ScalerGetBit(P73_D6_HDMI_SHDR_IE, (_BIT1 | _BIT0))) == ((ScalerGetBit(P73_D6_HDMI_SHDR_IE, (_BIT3 | _BIT2))) >> 2)) ? _ON : _OFF);

                    case _SPD_INFO_PQ_EOTF_ACTIVE:

                        return ((((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[9] & _BIT5) >> 5) != 0x00) ? _ON : _OFF);

                    case _SPD_INFO_GAMMA_2_2_EOTF_ACTIVE:

                        return ((((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[9] & 0x04) >> 2) != 0x00) ? _ON : _OFF);

                    case _SPD_INFO_FIXED_RATE_CONTENT_ACTIVE:

                        return (((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[16] & 0x01) != 0x00) ? _ON : _OFF);

                    case _SPD_INFO_TARGET_OUTPUT_PIXEL_RATE:

                        ulTargetOutputPixelRate = (((DWORD)g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[13] << 16) | ((DWORD)g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[14] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[15]);

                        return ulTargetOutputPixelRate;

                    case _SPD_INFO_FREESYNC_MIN_VFREQ:

                        if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
                        {
                            pData[1] = 0x00;
                            usFreesyncVfreqmin = (((WORD)pData[1] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[7]);
                        }
                        else
                        {
                            usFreesyncVfreqmin = (((WORD)g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[11] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[7]);
                        }

                        usFreesyncVfreqmin &= usAmdVfreqMaxBit;

                        if(((usFreesyncVfreqmin * 10) > _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE) || ((usFreesyncVfreqmin * 10) < _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE))
                        {
                            DebugMessageRx4("Freesync SPD info abnormal", 0);
                        }

                        return usFreesyncVfreqmin;

                    case _SPD_INFO_FREESYNC_MAX_VFREQ:

                        if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
                        {
                            pData[1] = 0x00;
                            usFreesyncVfreqmax = (((WORD)pData[1] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[8]);
                        }
                        else
                        {
                            usFreesyncVfreqmax = (((WORD)g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[12] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[8]);
                        }

                        usFreesyncVfreqmax &= usAmdVfreqMaxBit;

                        if(((usFreesyncVfreqmax * 10) > _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE) || ((usFreesyncVfreqmax * 10) < _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE))
                        {
                            DebugMessageRx4("Freesync SPD info abnormal", 0);
                        }

                        return usFreesyncVfreqmax;

                    default:
                        return 0x00;
                }
            }
        }
    }

    return 0x00;
}
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)

#if(_TMDS_MAC_RX4_CED_DEBUG == _ON)
//-------------------------------------------------
// Description  : TMDS Character Error Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4CEDCheck(void)
{
    WORD usCEDLane0ErrorCount = 0;
    WORD usCEDLane1ErrorCount = 0;
    WORD usCEDLane2ErrorCount = 0;

    // pop up Character Error Counter
    ScalerSetBit(P73_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

    usCEDLane0ErrorCount = (ScalerGetBit(P73_0C_HDMI_CTRL_0C, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) + ScalerGetByte(P73_0D_HDMI_CTRL_0D);
    usCEDLane1ErrorCount = (ScalerGetBit(P73_0E_HDMI_CTRL_0E, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) + ScalerGetByte(P73_0F_HDMI_CTRL_0F);
    usCEDLane2ErrorCount = (ScalerGetBit(P73_10_HDMI_CTRL_10, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) + ScalerGetByte(P73_11_HDMI_CTRL_11);

    DebugMessageRx4("Lane0 error count", usCEDLane0ErrorCount);
    DebugMessageRx4("Lane1 error count", usCEDLane1ErrorCount);
    DebugMessageRx4("Lane2 error count", usCEDLane2ErrorCount);


    if(usCEDLane0ErrorCount != 0)
    {
        ScalerSetBit(P73_0B_HDMI_CTRL_0B, ~_BIT7, 0x00);
        ScalerSetBit(P73_0B_HDMI_CTRL_0B, ~_BIT7, _BIT7);
    }

    if(usCEDLane1ErrorCount != 0)
    {
        ScalerSetBit(P73_0B_HDMI_CTRL_0B, ~_BIT6, 0x00);
        ScalerSetBit(P73_0B_HDMI_CTRL_0B, ~_BIT6, _BIT6);
    }

    if(usCEDLane2ErrorCount != 0)
    {
        ScalerSetBit(P73_0B_HDMI_CTRL_0B, ~_BIT5, 0x00);
        ScalerSetBit(P73_0B_HDMI_CTRL_0B, ~_BIT5, _BIT5);
    }
}
#endif
#endif

//--------------------------------------------------
// Description  : TMDS reset RX4 Timer Event
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4TimerEventReset(void)
{
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_TMDS_VIDEO_DETECT);

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_TMDS_HDMI_PACKET_DETECT);
    ScalerTmdsMacRx4HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
    ScalerTmdsMacRx4HdmiWatchDog(_TMDS_NO_CLK_WD, _DISABLE);
#endif

#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX4_HDMI_UNSTABLE_BED_CHECK);
    CLR_TMDS_MAC_RX4_BED_ERROR();
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI_ADVANCED_HDR10_DETECT);
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI2_FORMAT_RESET_WAIT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI2_SCRAMBLE_DETECT_TIMEOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX4_HDMI_RR_RETRY);
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_TMDS_EMP_DETECT);
#endif

#endif // End of #if(_HDMI_MAC_RX4_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : TMDS RX4 Check D domain mute before
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4ForceMDomainMuteBeforeHpdToggle(void)
{
    if(((ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00) && (ScalerGetBit(P73_A6_TMDS_OUTCTL, (_BIT6 | _BIT5 | _BIT4)) == (_BIT6 | _BIT5 | _BIT4))) ||
       ((ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6) && (ScalerGetBit(P69_A0_DPF_OUTPUT_0, (_BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4 | _BIT3))))
    {
        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_TMDS_MAC_RX4_FORCE_BCKGRD_PATH());
    }
}

//--------------------------------------------------
// Description  : TMDS Video Setting
// Input Value  : Source Type
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4DviVideoSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    // Manual Set Color Space and disable pixel repetition
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable Down Sampling
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Waiting for Down Sampling Effect
    ScalerTimerDelayXms(20);

    SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_RGB);

    SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_FULL_RANGE);

    ScalerTmdsMacRx4SetPorchColor(GET_COLOR_SPACE(enumMappingPort));
}

//--------------------------------------------------
// Description  : Set Back Ground Color
// Input Value  : Current Color Space
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4SetPorchColor(EnumColorSpace enumColorFormat)
{
    // Manual Set Background Color Enable
    ScalerSetBit(P73_B9_TMDS_OUT_CTRL, ~_BIT7, 0x00);

    if((enumColorFormat == _COLOR_SPACE_YCBCR444) || (enumColorFormat == _COLOR_SPACE_YCBCR422))
    {
        ScalerSetByte(P73_BA_TMDS_ROUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P73_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P73_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P73_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#if(_HDMI20_YCBCR420_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YCBCR420)
    {
        ScalerSetByte(P73_BA_TMDS_ROUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P73_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P73_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P73_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#endif
    else
    {
        ScalerSetByte(P73_BA_TMDS_ROUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P73_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BC_TMDS_GOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P73_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BE_TMDS_BOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P73_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
}

#if(_3DDI_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get Interlace 3DDI Available
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerTmdsMacRx4GetInterlace3ddiAvailable(void)
{
    DWORD ulTMDSClkValue = 0x00;
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if(g_usTmdsMacRx4ClkCount == 0)
    {
        return _FALSE;
    }

    // Cal TMDS Clk from On Clk Measure
    if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0, _BIT6) == _BIT6)
    {
        ulTMDSClkValue = (DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1024 * 2 / g_usTmdsMacRx4ClkCount;
    }
    else
    {
        ulTMDSClkValue = (DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1024 / g_usTmdsMacRx4ClkCount;
    }

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HIGH_SPEED_MODE() == _TRUE)
    {
        ulTMDSClkValue = (ulTMDSClkValue << 2);
    }
#endif

    // Cal Pixel Clk due to Deep Color
    if(GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422)
    {
        ulTMDSClkValue = ulTMDSClkValue * 8 / GET_COLOR_DEPTH(enumMappingPort);
    }

    if((ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, _BIT6) == _BIT6) && (ulTMDSClkValue < _3DDI_PCLK_LIMIT))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Rx4 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiVideoSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if(GET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

        pData[0] = ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx4("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx4("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx4("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx4("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx4("Get Pixel Repetition 0", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx4("Get Pixel Repetition 1", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx4("Get Pixel Repetition 2", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx4("Get Pixel Repetition 3", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx4("Get Pixel Repetition 4", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx4("Get Pixel Repetition 5", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx4("Get Pixel Repetition 6", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx4("Get Pixel Repetition 7", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx4("Get Pixel Repetition 8", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx4("Get Pixel Repetition 9", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx4("Get Pixel Repetition Error", 0x00);
                SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerTmdsMacRx4HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) || (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON))
        ScalerTmdsMacRx4HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
        SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_RGB);
        SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_RESERVED);

        // Manual Set Color Space to RGB and disable pixel repetition
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable down sampling
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTmdsMacRx4SetPorchColor(GET_COLOR_SPACE(enumMappingPort));
}

//--------------------------------------------------
// Description  : TMDS Rx4 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiColorimetrySetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx4("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx4("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx4("Get Colorimetry 709", 0x00);

                SET_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx4("Get Colorimetry Extended", 0x00);

                SET_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT);

                ScalerTmdsMacRx4HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX4_COLORIMETRY_PREVALUE(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_RX4_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx4("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx4("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT);

                ScalerTmdsMacRx4HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx4 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiColorimetryExtSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_RX4_COLORIMETRY_EXT_PREVALUE(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_RX4_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx4("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx4("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx4("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            case _AVI_COLORIMETRY_EXT_111:

                DebugMessageRx4("Get Colorimetry Additional Extended", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_ADD);

                ScalerTmdsMacRx4HdmiColorimetryAddExtSetting();

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX4_COLORIMETRY_EXT_PREVALUE(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_RX4_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx4("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx4("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            case _AVI_COLORIMETRY_EXT_111:

                DebugMessageRx4("Get Colorimetry Additional Extended", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_ADD);

                ScalerTmdsMacRx4HdmiColorimetryAddExtSetting();

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx4 Colorimetry Additional Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiColorimetryAddExtSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        // Get additional extended colorimetry
        SET_RX4_COLORIMETRY_ADD_EXT_PREVALUE(ScalerTmdsMacRx4HdmiRsv6GetAviInfo(_AVI_INFO_ADD_EXTENDED_COLORIMETRY));

        // Get additional extended colorimetry
        switch(GET_RX4_COLORIMETRY_ADD_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_ADD_EXT_0010:

                DebugMessageRx4("Get Colorimetry ADD_EXT_YCC_ITUR_BT2100", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_YCC_ITUR_BT2100);

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX4_COLORIMETRY_ADD_EXT_PREVALUE(ScalerTmdsMacRx4HdmiRsv6GetAviInfo(_AVI_INFO_ADD_EXTENDED_COLORIMETRY));

        switch(GET_RX4_COLORIMETRY_ADD_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_ADD_EXT_0000:

                DebugMessageRx4("Get Colorimetry ADD_EXT_RGB_SMPTE_ST2113_P3D65", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3D65);

                break;

            case _AVI_COLORIMETRY_ADD_EXT_0001:

                DebugMessageRx4("Get Colorimetry ADD_EXT_RGB_SMPTE_ST2113_P3DCI", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3DCI);

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RESERVED);

                break;
        }
    }
}

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) || (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON))
//--------------------------------------------------
// Description  : TMDS Rx4 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiQuantizationSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        SET_RX4_QUANTIZATION_PREVALUE(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_RX4_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx4("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx4("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx4("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        switch(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx4("Get RGB LIMIT RANGE", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx4("Get RGB FULL RANGE", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx4("Get RGB DEFAULT RANGE", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx4("Get RGB RESERVED RANGE", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx4("Get RGB RANGE Error", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx4 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerTmdsMacRx4HdmiColorInfoChanged(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    BYTE pucTemp[2] = {0};

    // Check Color Space
    if(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(enumMappingPort))
    {
        DebugMessageRx4("Color Space Changed", 0x00);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            return _TRUE;
        }
        else
        {
            if(ScalerTmdsMacRx4SeamlessReset() == _SOURCE_NONE)
            {
                return _TRUE;
            }
        }
#else
        return _TRUE;
#endif
    }

    // Check Colorimetry
    if(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_RX4_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx4("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_RX4_COLORIMETRY_PREVALUE();

            ScalerTmdsMacRx4HdmiColorimetrySetting();

            if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_RX4_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_RX4_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY(enumMappingPort) == _COLORIMETRY_EXT)
        {
            if(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_RX4_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx4("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_RX4_COLORIMETRY_EXT_PREVALUE();

                    ScalerTmdsMacRx4HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_RX4_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_RX4_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_RX4_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx4("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_RX4_QUANTIZATION_PREVALUE();

                ScalerTmdsMacRx4HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_RX4_QUANTIZATION_CHANGED();
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
    if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        if(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_RX4_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx4("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerTmdsMacRx4HdmiQuantizationSetting();

                SET_RX4_QUANTIZATION_CHANGED();
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if((_HDMI_MAC_RX4_SUPPORT == _ON) || (_3DDI_FUNCTION == _ON))
//--------------------------------------------------
// Description  : HDMI Deep Color Proc
// Input Value  : void
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTmdsMacRx4HdmiDeepColorProc(WORD usTmdsClkCnt)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    // Setting Deep Color PLL
    if(ScalerTmdsMacRx4HdmiSetDeepColorPll(usTmdsClkCnt, GET_COLOR_DEPTH(enumMappingPort)) == _FALSE)
    {
        return _FALSE;
    }

    // Wait for Phase lock
    if(ScalerTmdsMacRx4HdmiWaitDeepColorPllLock() == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Wait for Deep Color PLL Phase Lock
// Input Value  : None
// Output Value : _TRUE = > Phase Locked
//--------------------------------------------------
bit ScalerTmdsMacRx4HdmiWaitDeepColorPllLock(void)
{
    BYTE ucTemp = 0;

    do
    {
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_82_PORT_PAGE73_HDMI_DPC_SET2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // Delay for PLL Phase Lock
        ScalerTimerDelayXms(2);

        ucTemp++;
    }
    while((ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_82_PORT_PAGE73_HDMI_DPC_SET2, _BIT1) != 0) && (ucTemp <= 15));

    if(ucTemp > 15)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect HDMI Info Frame
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiPacketDetect(bit bWait)
{
#if(_DM_FUNCTION == _ON)
    EnumInputPort enumDx = ScalerTmdsMacRxRxDxMapping(_RX4);
#endif

    if(bWait == _WAIT)
    {
        BYTE ucRSVColorDepth = 0x00;

        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingFlagProc(130, P73_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0), _TRUE) == _TRUE)
        {
            // Both GCP & AVI infoframe packet have been received
            if(ScalerGetBit(P73_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
            {
                SET_TMDS_MAC_RX4_HDMI_GCP_RECEIVED();

                SET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED();

                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P73_CC_HDMI_GPVS, 0x01);
            }
            // Only AVI infoframe packet have been received
            else if(ScalerGetBit(P73_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT0)
            {
                SET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED();

                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P73_CC_HDMI_GPVS, 0x01);

                // Polling more time to wait GCP when AVI IF has been received.
                if(ScalerTimerPollingFlagProc(180, P73_D5_HDMI_RSV64_IE, _BIT1, _TRUE) == _TRUE)
                {
                    SET_TMDS_MAC_RX4_HDMI_GCP_RECEIVED();
                }
                else
                {
                    CLR_TMDS_MAC_RX4_HDMI_GCP_RECEIVED();
                }
            }
            // Only GCP Packet have been received
            else if(ScalerGetBit(P73_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT1)
            {
                SET_TMDS_MAC_RX4_HDMI_GCP_RECEIVED();

                // Polling more time to wait AVI IF when GCP has been received.
                if(ScalerTimerPollingFlagProc(180, P73_D5_HDMI_RSV64_IE, _BIT0, _TRUE) == _TRUE)
                {
                    SET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED();

                    // Clear AVI Info Frame Variation flag
                    ScalerSetByte(P73_CC_HDMI_GPVS, 0x01);
                }
                else
                {
                    CLR_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED();
                }
            }
        }
        // Neither AVI infoframe nor GCP packet received
        else
        {
            CLR_TMDS_MAC_RX4_HDMI_GCP_RECEIVED();

            CLR_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED();
        }

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
        ScalerTmdsMacRx4RoundRobinDetect(_WAIT);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingFlagProc(130, P73_D5_HDMI_RSV64_IE, (_BIT2), _TRUE) == _TRUE)
        {
            SET_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
#endif

        // Detect for Deep color
        ucRSVColorDepth = ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x42, (_BIT3 | _BIT2 | _BIT1 | _BIT0));  // 0x42: RSV5 GCP SB1

        if(((GET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) == _COLOR_SPACE_YCBCR422)) ||
           ((GET_TMDS_MAC_RX4_HDMI_GCP_RECEIVED() == _TRUE) && (ScalerGetBit(P73_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != ucRSVColorDepth)))
        {
            // Wait at least 3 frame for HW auto update color depth value
            if(GET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED() == _TRUE)
            {
                BYTE ucFrameRate = 0x00;

                if(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_VIC) != 0x00)
                {
                    ucFrameRate = ScalerTmdsMacRxGetVicVfreqParameter(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_VIC));
                }
                else if(ScalerTmdsMacRx4HdmiRsv6GetAviInfo(_AVI_INFO_FR) != 0x00)
                {
                    ucFrameRate = ScalerTmdsMacRxGetOvtVfreqParameter(ScalerTmdsMacRx4HdmiRsv6GetAviInfo(_AVI_INFO_FR));
                }

                if(ucFrameRate != 0x00)
                {
                    // 3ms to ensure HW apply
                    ScalerTimerDelayXms(3);
                    ScalerTimerDelayXms(3000 / (WORD)ucFrameRate);
                    if(ScalerGetBit(P73_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != ucRSVColorDepth)
                    {
                        // Wait 3 more frame for HW auto update color depth value
                        ScalerTimerDelayXms(3000 / (WORD)ucFrameRate);
                        DebugMessageRx4("More delay for GCP DPC HW update", ScalerGetBit(P73_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
                    }
                }
                else
                {
                    ScalerTimerDelayXms(130);
                }
            }
            else
            {
                ScalerTimerDelayXms(130);
            }
        }

        CLR_TMDS_MAC_RX4_HDMI_PACKET_DETECTING();

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        CLR_TMDS_MAC_RX4_ADVANCED_HDR10_DETECTING();
#endif

#if(_DM_FUNCTION == _ON)
        CLR_TMDS_MAC_RX4_DM_INFO_DETECTING();
        CLR_DRAM_RECEIVED_FROM_DM_DETECT(enumDx);
#endif
    }
    else
    {
        if(ScalerGetBit(P73_D5_HDMI_RSV64_IE, _BIT1) == _BIT1)
        {
            ScalerTmdsMacRx4HdmiWatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_TMDS_MAC_RX4_HDMI_GCP_RECEIVED();

            // Clear Detection Flag
            ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
        }
        else
        {
            ScalerTmdsMacRx4HdmiWatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_TMDS_MAC_RX4_HDMI_GCP_RECEIVED();
        }

        if(ScalerGetBit(P73_D5_HDMI_RSV64_IE, _BIT0) == _BIT0)
        {
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            ScalerTmdsMacRx4HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED();

            // Clear Detection Flag
            ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        }
        else
        {
            // Mannal Set Color Space and disable pixel  repetition
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerTmdsMacRx4HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED();
        }

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
        ScalerTmdsMacRx4RoundRobinDetect(_NOT_WAIT);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
#if(_DM_FUNCTION == _ON)
        if((ScalerGetBit(P73_D5_HDMI_RSV64_IE, _BIT2) == _BIT2) || (GET_DRAM_RECEIVED_FROM_DM_DETECT(enumDx) == _TRUE))
#else
        if(ScalerGetBit(P73_D5_HDMI_RSV64_IE, _BIT2) == _BIT2)
#endif
        {
            SET_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();

#if(_DM_FUNCTION == _ON)
            // if realtime OSD support DM
            if(ScalerTmdsMacRxGetOsdDmSupport(enumDx) == _ON)
            {
                // clear FW flag only, don't w1c rsv received bit due to DM Detecting need
                CLR_DRAM_RECEIVED_FROM_DM_DETECT(enumDx);
            }
            else
            {
                // w1c RSV received bit
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            }
#else
            // w1c RSV received bit
            ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
#endif
        }
        else
        {
            CLR_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
#endif

        SET_TMDS_MAC_RX4_HDMI_PACKET_DETECTING();

        // Activate Packet Detection Event
        ScalerTimerActiveTimerEvent(130, _SCALER_TIMER_EVENT_RX4_TMDS_HDMI_PACKET_DETECT);
    }
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiPacketDetectEvent(void)
{
    CLR_TMDS_MAC_RX4_HDMI_PACKET_DETECTING();
}

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
//--------------------------------------------------
// Description  : RoundRobin Detect
// Input Value  : bWait
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4RoundRobinDetect(bit bWait)
{
    if(bWait == _WAIT)
    {
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
        bit bFsPktRvd = _FALSE;
#endif

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
        //-----------------------------------------
        // Polling 3 frame for RSV resceive packet
        //-----------------------------------------
        if((ScalerTimerPollingFlagProc(130, P73_CC_HDMI_GPVS, (_BIT6 | _BIT5), _TRUE) == _TRUE) || (ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, (_BIT7 | _BIT6)) != 0x00))
        {
            // Check for RSV0
            if(ScalerGetBit(P73_CC_HDMI_GPVS, _BIT5) == _BIT5)
            {
                ScalerSetByte(P73_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P73_F8_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
                {
                    ScalerTmdsMacRx4RsvSpdHandler(_HDMI_RSV_0);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerTmdsMacRx4RsvVsifHandler(_HDMI_RSV_0);
#endif
                }
            }

            // Check for RSV1
            if(ScalerGetBit(P73_CC_HDMI_GPVS, _BIT6) == _BIT6)
            {
                ScalerSetByte(P73_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P73_F9_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
                {
                    ScalerTmdsMacRx4RsvSpdHandler(_HDMI_RSV_1);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerTmdsMacRx4RsvVsifHandler(_HDMI_RSV_1);
#endif
                }
            }

            // Check for RSV2
            if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT7) == _BIT7)
            {
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P73_FA_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
                {
                    ScalerTmdsMacRx4RsvSpdHandler(_HDMI_RSV_2);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerTmdsMacRx4RsvVsifHandler(_HDMI_RSV_2);
#endif
                }
            }

            // Check for RSV3
            if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT6) == _BIT6)
            {
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P73_FB_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
                {
                    ScalerTmdsMacRx4RsvSpdHandler(_HDMI_RSV_3);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerTmdsMacRx4RsvVsifHandler(_HDMI_RSV_3);
#endif
                }
            }
        }
#endif

        //-----------------------------------------
        // FS PR Flag setting
        //-----------------------------------------
#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        if(ScalerTimerPollingFlagProc(130, P73_D5_HDMI_RSV64_IE, _BIT3, _TRUE) == _TRUE)
        {
            SET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX4_FREESYNC_REPLAY_RECEIVED();
        }
#endif

        //-----------------------------------------
        // FS SPD INFO Flag setting
        //-----------------------------------------
#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
        bFsPktRvd = GET_TMDS_MAC_RX4_FS_VALUABLE();
#else
        for(BYTE ucCount = 0; ucCount < 65; ucCount++)
        {
            ScalerTimerDelayXms(2);

            if(GET_TMDS_MAC_RX4_FS_VALUABLE() == _TRUE)
            {
                bFsPktRvd = _TRUE;
                break;
            }
        }
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_II_SUPPORT == _OFF) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
        if((GET_FREESYNC_HDMI_VCP() == 0x01) && (bFsPktRvd == _TRUE))
#else
        if(bFsPktRvd == _TRUE)
#endif
        {
            SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
        }
#endif
    }
    else
    {
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
        //-----------------------------------------
        // RSV resceive packet
        //-----------------------------------------
        // Check for RSV0
        if(ScalerGetBit(P73_CC_HDMI_GPVS, _BIT5) == _BIT5)
        {
            ScalerSetByte(P73_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P73_F8_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
            {
                ScalerTmdsMacRx4RsvSpdHandler(_HDMI_RSV_0);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerTmdsMacRx4RsvVsifHandler(_HDMI_RSV_0);
#endif
            }
        }

        // Check for RSV1
        if(ScalerGetBit(P73_CC_HDMI_GPVS, _BIT6) == _BIT6)
        {
            ScalerSetByte(P73_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P73_F9_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
            {
                ScalerTmdsMacRx4RsvSpdHandler(_HDMI_RSV_1);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerTmdsMacRx4RsvVsifHandler(_HDMI_RSV_1);
#endif
            }
        }

        // Check for RSV2
        if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT7) == _BIT7)
        {
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P73_FA_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
            {
                ScalerTmdsMacRx4RsvSpdHandler(_HDMI_RSV_2);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerTmdsMacRx4RsvVsifHandler(_HDMI_RSV_2);
#endif
            }
        }

        // Check for RSV3
        if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT6) == _BIT6)
        {
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P73_FB_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
            {
                ScalerTmdsMacRx4RsvSpdHandler(_HDMI_RSV_3);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerTmdsMacRx4RsvVsifHandler(_HDMI_RSV_3);
#endif
            }
        }
#endif

        //-----------------------------------------
        // FS PR Flag setting
        //-----------------------------------------
#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        if(ScalerGetBit(P73_D5_HDMI_RSV64_IE, _BIT3) == _BIT3)
        {
            SET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX4_FREESYNC_REPLAY_RECEIVED();
        }
#endif

        //-----------------------------------------
        // FS SPD INFO Flag setting
        //-----------------------------------------
#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_II_SUPPORT == _OFF) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
        if((GET_FREESYNC_HDMI_VCP() == 0x01) && (GET_TMDS_MAC_RX4_FS_VALUABLE() == _TRUE))
#else
        if(GET_TMDS_MAC_RX4_FS_VALUABLE() == _TRUE)
#endif
        {
            SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
            CLR_TMDS_MAC_RX4_FS_VALUABLE();
        }
        else
        {
            CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
        }
#endif
    }
}

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
//--------------------------------------------------
// Description  : Get SPD Info Product Description
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4RsvSpdHandler(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucI = 0;
    BYTE ucVnCount = 0;
    BYTE pucHdmiVenderName[4] = {0};

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    for(ucVnCount = 0; ucVnCount < 4; ucVnCount++)
    {
        pucHdmiVenderName[ucVnCount] = ScalerGetByte(P73_CE_HDMI_PSDP);
    }

    if(((pucHdmiVenderName[0] == 'M') && (pucHdmiVenderName[1] == 'S') && (pucHdmiVenderName[2] == 'F') && (pucHdmiVenderName[3] == 'T')) ||
       ((pucHdmiVenderName[0] == 'S') && (pucHdmiVenderName[1] == 'C') && (pucHdmiVenderName[2] == 'E') && (pucHdmiVenderName[3] == 'I')) ||
       ((pucHdmiVenderName[0] == 'N') && (pucHdmiVenderName[1] == 'V') && (pucHdmiVenderName[2] == 'I') && (pucHdmiVenderName[3] == 'D')))
    {
        g_stTmdsMacRx4SpdInfo.b1StructValuable = 0x01;
        __real_memcpy(&g_stTmdsMacRx4SpdInfo.pucHdmiVendorName[0], pucHdmiVenderName, 4);

        switch(enumRsvNumber)
        {
            case _HDMI_RSV_0:
                ScalerSetByte(P73_CD_HDMI_PSAP, 0x5A);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte(P73_CD_HDMI_PSAP, 0x79);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte(P73_CD_HDMI_PSAP, 0x98);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte(P73_CD_HDMI_PSAP, 0xB7);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 16; ucI++)
        {
            g_stTmdsMacRx4SpdInfo.pucHdmiProductDescription[ucI] = ScalerGetByte(P73_CE_HDMI_PSDP);
        }
    }
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
    else if((pucHdmiVenderName[0] == 0x1A) && (pucHdmiVenderName[1] == 0x00) && (pucHdmiVenderName[2] == 0x00) && (GET_TMDS_MAC_RX4_FS_VALUABLE() == _FALSE))
    {
        SET_TMDS_MAC_RX4_FS_VALUABLE();

        switch(enumRsvNumber)
        {
            case _HDMI_RSV_0:
                ScalerSetByte(P73_CD_HDMI_PSAP, 0x51);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte(P73_CD_HDMI_PSAP, 0x70);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte(P73_CD_HDMI_PSAP, 0x8F);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte(P73_CD_HDMI_PSAP, 0xBF);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 28; ucI++)
        {
            g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[ucI] = ScalerGetByte(P73_CE_HDMI_PSDP);
        }
    }
#endif
}
#endif

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
//--------------------------------------------------
// Description  : RSVx into IRQ Handler
// Input Value  : ulOui, enumRsvNumber
// Output Value : void
//--------------------------------------------------
void ScalerTmdsMacRx4RsvVsifHandler(EnumHdmiRsvNumber enumRsvNumber)
{
    enumRsvNumber = enumRsvNumber;
    DWORD ulOui = 0;

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
    StructAdvancedHDR10MetaData stSyncAdvancedHDR10Metadata = {0};
#endif

#if(_DM_FUNCTION == _ON)
    BYTE pucDmMetaData[27] = {0};
    BYTE pucDmHb[3] = {0};
    BYTE ucStartAddr = 0;
#endif

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte_EXINT(P73_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P73_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P73_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P73_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    ulOui = ScalerGetByte_EXINT(P73_CE_HDMI_PSDP);
    ulOui = (ulOui << 8) + ScalerGetByte_EXINT(P73_CE_HDMI_PSDP);
    ulOui = (ulOui << 8) + ScalerGetByte_EXINT(P73_CE_HDMI_PSDP);

    switch(ulOui)
    {
#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
        case _HDMI_VSIF_OUI:

            SET_TMDS_MAC_RX4_HDMI_VSIF_RECEIVED();

            ScalerTmdsMacRx4HdmiVsif3dVideoProc(enumRsvNumber);

            break;
#endif

#if((_HDMI21_ALLM_SUPPORT == _ON) || (_HDMI21_CCBPC_SUPPORT == _ON) || (_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON))
        case _HF_VSIF_OUI:

            SET_TMDS_MAC_RX4_HF_VSIF_RECEIVED();

#if(_HDMI21_ALLM_SUPPORT == _ON)
            ScalerTmdsMacRx4AllmProc(enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
            ScalerTmdsMacRx4CcbpcProc(enumRsvNumber);
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
            ScalerTmdsMacRx4HfVsif3dVideoProc(enumRsvNumber);
#endif
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
// Description  : Parser 3D Video format from HDMI VSIF
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit b3dVideo = _FALSE;

    // Get HDMI Video Format (PB4)
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x55);
            b3dVideo = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x74);
            b3dVideo = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x93);
            b3dVideo = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0xB2);
            b3dVideo = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    if(b3dVideo == _TRUE)
    {
        SET_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
    }
    else
    {
        CLR_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
    }
}

//--------------------------------------------------
// Description  : Parser 3D Video format from HF VSIF
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HfVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit b3dVideo = _FALSE;

    // Get HDMI Video Format (PB5)
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x56);
            b3dVideo = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x75);
            b3dVideo = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x94);
            b3dVideo = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0xB3);
            b3dVideo = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    if(b3dVideo == _TRUE)
    {
        SET_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
    }
    else
    {
        CLR_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
    }
}
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable ALLM
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4AllmProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit bAllm = 0;

#if(_DM_FUNCTION == _ON)
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping(_RX4);
#endif

    // Get ALLM bit
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x56);
            bAllm = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x75);
            bAllm = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x94);
            bAllm = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0xB3);
            bAllm = (((ScalerGetByte(P73_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    // Enable/Disable ALLM
    if(bAllm == _TRUE)
    {
        SET_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();

#if(_DM_FUNCTION == _ON)
        ScalerTmdsMacRxSetDmAllmStatus(enumInputPort);
#endif
    }
    else
    {
        CLR_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();

#if(_DM_FUNCTION == _ON)
        ScalerTmdsMacRxClrDmAllmStatus(enumInputPort);
#endif
    }
}
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get CCBPC Value
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4CcbpcProc(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucCcbpcValue = 0;

    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x56);
            ucCcbpcValue = (ScalerGetByte(P73_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x75);
            ucCcbpcValue = (ScalerGetByte(P73_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0x94);
            ucCcbpcValue = (ScalerGetByte(P73_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P73_CD_HDMI_PSAP, 0xB3);
            ucCcbpcValue = (ScalerGetByte(P73_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        default:

            break;
    }

    if((ucCcbpcValue != 0) && ((ucCcbpcValue + 7) <= GET_COLOR_DEPTH(enumMappingPort)))
    {
        SET_COLOR_HDMI21_CCBPC_VALUE(enumMappingPort, ucCcbpcValue + 7);
    }
    else
    {
        SET_COLOR_HDMI21_CCBPC_VALUE(enumMappingPort, 0);
    }
}
#endif
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
//--------------------------------------------------
//--------------------------------------------------
// Description  : HDR10+ VSIF Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiAdvancedHdr10DetectEvent(void)
{
    CLR_TMDS_MAC_RX4_ADVANCED_HDR10_DETECTING();
}
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : DM Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiDmDetectEvent(void)
{
    CLR_TMDS_MAC_RX4_DM_INFO_DETECTING();
}
#endif

#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : HDMI2.1 EMP Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4EmpDetectEvent(void)
{
    CLR_TMDS_MAC_RX4_EMP_DETECTING();
}

//--------------------------------------------------
// Description  : Detect HDMI2.1 EMP
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4EmpPacketDetect(bit bWait)
{
#if(_HDMI_SBTM_SUPPORT == _ON)
    BYTE ucHdmiSbtmCheckTime = 0;
#endif

    if(bWait == _WAIT)
    {
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
#if(_HDMI21_VRR_SUPPORT == _ON)
        // Clear VRR flag
        CLR_TMDS_MAC_RX4_HDMI21_VRR_EN();
        CLR_TMDS_MAC_RX4_HDMI21_QMS_EN();
#endif
#if(_HDMI21_FVA_SUPPORT == _ON)
        SET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR(1);
#endif
        // CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
        CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG();
#if(_HDMI21_VRR_SUPPORT == _ON)
        CLR_TMDS_MAC_RX4_HDMI21_VRR_RECEIVE_CHG();
        CLR_TMDS_MAC_RX4_HDMI21_QMS_RECEIVE_CHG();
#endif

        // Wait at least 2 frames for HW auto update VTEM flag and Length not 0
        if((ScalerTimerPollingFlagProc(90, P73_54_PAGE73_EMP_CTRL_0, _BIT6, _TRUE) == _TRUE) && ((ScalerGetByte(P73_5B_PAGE73_HDMI_EMP_6) != 0x00) || (ScalerGetByte(P73_5C_PAGE73_HDMI_EMP_7) != 0x00)))
        {
            SET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
        }
        else
        {
            CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
        }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        CLR_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED();
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
        ucHdmiSbtmCheckTime = 18;

        while(ucHdmiSbtmCheckTime != 0)
        {
            if(g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive == _TRUE)
            {
                DebugMessageRx4("HDMI Rx4 SBTM Receive", 0x00);

                SET_TMDS_MAC_RX4_SBTM_RECEIVE();
                g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive = _FALSE;
                break;
            }
            ScalerTimerDelayXms(5);
            ucHdmiSbtmCheckTime--;
        }

        if((ucHdmiSbtmCheckTime == 0x00) && (g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive == _FALSE))
        {
            DebugMessageRx4("HDMI Rx4 SBTM not Receive", 0x00);

            CLR_TMDS_MAC_RX4_SBTM_RECEIVE();
        }
#endif

        CLR_TMDS_MAC_RX4_EMP_DETECTING();
    }
    else
    {
#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
        if((ScalerGetBit(P73_54_PAGE73_EMP_CTRL_0, _BIT6) == _BIT6) && ((ScalerGetByte(P73_5B_PAGE73_HDMI_EMP_6) != 0x00) || (ScalerGetByte(P73_5C_PAGE73_HDMI_EMP_7) != 0x00)))
        {
            // No Received / MLDS -> Received VTEM
            if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _FALSE)
            {
                SET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG();
            }

            SET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();

            // Clear VTEM flag
            ScalerSetBit(P73_54_PAGE73_EMP_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

#if(_HDMI21_VRR_SUPPORT == _ON)
            if((((bit)ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _ENABLE) && (GET_TMDS_MAC_RX4_HDMI21_VRR_EN() != _ENABLE))
            {
                DebugMessageRx4("TMDS Rx4: VRR_EN from 0 -> 1", 0x00);
                SET_TMDS_MAC_RX4_HDMI21_VRR_RECEIVE_CHG();
                SET_TMDS_MAC_RX4_HDMI21_VRR_EN();
            }
            else if((((bit)ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _DISABLE) && (GET_TMDS_MAC_RX4_HDMI21_VRR_EN() != _DISABLE))
            {
                DebugMessageRx4("TMDS Rx4: VRR_EN from 1 -> 0", 0x00);
                SET_TMDS_MAC_RX4_HDMI21_VRR_RECEIVE_CHG();
                CLR_TMDS_MAC_RX4_HDMI21_VRR_EN();
            }

            if((((bit)ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _ENABLE) && (GET_TMDS_MAC_RX4_HDMI21_QMS_EN() != _ENABLE))
            {
                DebugMessageRx4("TMDS Rx4: QMS_EN from 0 -> 1", 0x00);
                SET_TMDS_MAC_RX4_HDMI21_QMS_RECEIVE_CHG();
                SET_TMDS_MAC_RX4_HDMI21_QMS_EN();
            }
            else if((((bit)ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _DISABLE) && (GET_TMDS_MAC_RX4_HDMI21_QMS_EN() != _DISABLE))
            {
                DebugMessageRx4("TMDS Rx4: QMS_EN from 1 -> 0", 0x00);
                SET_TMDS_MAC_RX4_HDMI21_QMS_RECEIVE_CHG();
                CLR_TMDS_MAC_RX4_HDMI21_QMS_EN();
            }
#endif
        }
        else
        {
            // Received VTEM -> No Received / MLDS
            if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
            {
                SET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG();

#if(_HDMI21_VRR_SUPPORT == _ON)
                if(GET_TMDS_MAC_RX4_HDMI21_VRR_EN() == _TRUE)
                {
                    DebugMessageRx4("VTEM->No Received(VRR_EN from 1->0)", 0x00);
                    SET_TMDS_MAC_RX4_HDMI21_VRR_RECEIVE_CHG();
                    CLR_TMDS_MAC_RX4_HDMI21_VRR_EN();
                }

                if(GET_TMDS_MAC_RX4_HDMI21_QMS_EN() == _TRUE)
                {
                    DebugMessageRx4("VTEM->No Received(QMS_EN from 1->0)", 0x00);
                    SET_TMDS_MAC_RX4_HDMI21_QMS_RECEIVE_CHG();
                    CLR_TMDS_MAC_RX4_HDMI21_QMS_EN();
                }
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
                SET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR(1);
#endif
            }

            CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
        }
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
        if(g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive == _TRUE)
        {
            SET_TMDS_MAC_RX4_SBTM_RECEIVE();
            g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive = _FALSE;
        }
        else
        {
            CLR_TMDS_MAC_RX4_SBTM_RECEIVE();
        }
#endif

        SET_TMDS_MAC_RX4_EMP_DETECTING();

        // Activate EMP Detection Event 12 frames = 45ms * 12
        ScalerTimerActiveTimerEvent(540, _SCALER_TIMER_EVENT_RX4_TMDS_EMP_DETECT);
    }
}

#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
#if(_HDMI21_VRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set VRR Max Vf info from Spec Table
// Input Value  : usSourceBrr (unit: 0.1Hz)
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4SetVrrVfmaxFromTable(WORD usSourceBrr)
{
    // Check VRRmax > 100?
    // if yes, VFmax = VRRmax
    if(g_stTmdsMacRx4Hdmi21EdidVrrCap.usEdidVrrMax >= 100)
    {
        SET_DRR_VFREQ_MAX(g_stTmdsMacRx4Hdmi21EdidVrrCap.usEdidVrrMax * 10);

        return;
    }

    // Check QMS or Gaming
    if(g_stTmdsMacRx4Hdmi21EdidVrrCap.b1EdidQms == 1)
    {
        // QMS case
        if(g_stTmdsMacRx4Hdmi21EdidVrrCap.b1EdidQmsTfrMax == 1)
        {
            SET_DRR_VFREQ_MAX(usSourceBrr);
        }
        else
        {
            if(g_stTmdsMacRx4Hdmi21EdidVrrCap.ucEdidVrrMin > 0)
            {
                SET_DRR_VFREQ_MAX(MAXOF(usSourceBrr, 600));
            }
            else
            {
                SET_DRR_VFREQ_MAX(600);
            }
        }
    }
    else
    {
        // Gaming case
        if(g_stTmdsMacRx4Hdmi21EdidVrrCap.ucEdidVrrMin > 0)
        {
            SET_DRR_VFREQ_MAX(usSourceBrr);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Get HDMI21 VTEM Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
WORD ScalerTmdsMacRx4HdmiGetVtemInfo(EnumHdmi21VtemInfoContent enumContent)
{
    if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _HDMI21_VTEM_INFO_VRR_EN:

                return (((ScalerGetByte(P73_5D_PAGE73_HDMI_EMP_8) & _BIT0) == _BIT0) ? _ON : _OFF);

            case _HDMI21_VTEM_INFO_M_CONST:

                return (((ScalerGetByte(P73_5D_PAGE73_HDMI_EMP_8) & _BIT1) == _BIT1) ? _ON : _OFF);

            case _HDMI21_VTEM_INFO_FVA_FACTOR_M1:

                return ((ScalerGetByte(P73_5D_PAGE73_HDMI_EMP_8) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

            case _HDMI21_VTEM_INFO_BASE_VFRONT:

                return (ScalerGetByte(P73_5E_PAGE73_HDMI_EMP_9));


            case _HDMI21_VTEM_INFO_BASE_REFRESH_RATE:

                return (((WORD)(ScalerGetByte(P73_5F_PAGE73_HDMI_EMP_A) & 0x03) << 8) | (WORD)(ScalerGetByte(P73_60_PAGE73_HDMI_EMP_B)));

            case _HDMI21_VTEM_INFO_QMS_EN:

                return (((ScalerGetByte(P73_5D_PAGE73_HDMI_EMP_8) & _BIT2) == _BIT2) ? _ON : _OFF);

            case _HDMI21_VTEM_NEXT_TFR:

                return ((ScalerGetByte(P73_5F_PAGE73_HDMI_EMP_A) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

            default:

                break;
        }
    }

    return 0x00;
}
#endif
#endif

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTmdsMacRx4HdmiGetAVIInfo(EnumAviInfoContent enumContent)
{
    if(GET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x04, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x05, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x06, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x06, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x08, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:

                return ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x04, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x06, _BIT7) >> 7);

            case _AVI_INFO_CONTENT_TYPE:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x08, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_PIXEL_REPETITION:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x08, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x05, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:

                return ScalerGetDataPortSingleByte(P73_CD_HDMI_PSAP, 0x07);

            default:

                break;
        }
    }

    return 0xFF;
}

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents From RSV6
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTmdsMacRx4HdmiRsv6GetAviInfo(EnumAviInfoContent enumContent)
{
    if(GET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x61, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x62, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x63, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_ADD_EXTENDED_COLORIMETRY:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x6E, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x63, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x65, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:

                return ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x61, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x63, _BIT7) >> 7);

            case _AVI_INFO_CONTENT_TYPE:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x65, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_PIXEL_REPETITION:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x65, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:

                return (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x62, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:

                return ScalerGetDataPortSingleByte(P73_D0_HDMI_PSAP2, 0x64);

            case _AVI_INFO_FR:

                return ((ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x6F, _BIT6) >> 2) | (ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x6E, (_BIT3 | _BIT2 | _BIT1 | _BIT0))));

            case _AVI_INFO_RID:

                return ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x6F, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            default:

                break;
        }
    }

    return 0xFF;
}

//--------------------------------------------------
// Description  : Detect HDMI AVI pixel repetition
// Input Value  : None
// Output Value : _TRUE => Current Info is different from previous setting
//--------------------------------------------------
bit ScalerTmdsMacRx4HdmiAviPixelRepInfoChanged(void)
{
    // Check Tmds Pixel Repetition
    if(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION) != GET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION())
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Content Type
// Input Value  : None
// Output Value : EnumContentType
//--------------------------------------------------
EnumContentType ScalerTmdsMacRx4HdmiGetAviContentType(void)
{
    BYTE ucContentType = ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_CONTENT_TYPE);

    switch(ucContentType)
    {
        case 0x00:

            if(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_IT_CONTENT) == 0x01)
            {
                return _CONTENT_TYPE_GRAPHICS;
            }
            else
            {
                return _CONTENT_TYPE_N0_DATA;
            }

        case 0x01:

            return _CONTENT_TYPE_PHOTO;

        case 0x02:

            return _CONTENT_TYPE_CINEMA;

        case 0x03:

            return _CONTENT_TYPE_GAME;

        default:

            return _CONTENT_TYPE_N0_DATA;
    }
}

//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : None
// Output Value : Received Color Depth
//--------------------------------------------------
BYTE ScalerTmdsMacRx4HdmiGetColorDepth(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422)
    {
        return _COLOR_DEPTH_12_BITS;
    }

    if(GET_TMDS_MAC_RX4_HDMI_GCP_RECEIVED() == _TRUE)
    {
        if(ScalerGetBit(P73_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
        {
            return _COLOR_DEPTH_10_BITS;
        }
        else if(ScalerGetBit(P73_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1))
        {
            return _COLOR_DEPTH_12_BITS;
        }
        else if(ScalerGetBit(P73_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1 | _BIT0))
        {
            return _COLOR_DEPTH_16_BITS;
        }
    }

    return _COLOR_DEPTH_8_BITS;
}

//--------------------------------------------------
// Description  : Hdmi Enable Watch Dog
// Input Value  : ucWDType => Watch Dog type, bEnable => Enable watch dog flag
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiWatchDog(BYTE ucWDType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD) && (GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE))
        {
            if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_41_PORT_PAGE73_HDMI_VWDSR, _BIT0) == 0x00)
            {
                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P73_CC_HDMI_GPVS, _BIT0);

                // Enable Color Space/ Colorimetry Change Detection
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_45_PORT_PAGE73_HDMI_PVGCR0, ~(_BIT3 | _BIT0), (_BIT3 | _BIT0));
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_AA_PORT_PAGE73_HDMI_PVGCR3, ~_BIT7, _BIT7);

#if(_HW_HDMI_AVI_ACE_WD_SUPPORT == _ON)
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_AB_PORT_PAGE73_HDMI_PVGCR4, ~_BIT4, _BIT4);
#endif

                // Enable AVI Info Frame Variation Watch Dog
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_41_PORT_PAGE73_HDMI_VWDSR, ~_BIT0, _BIT0);
            }
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, _BIT7) == 0x00)
            {
                // CLR AVMute Flag
                ScalerSetBit(P73_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT7);

                // Enable AVMute WD
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~_BIT7, _BIT7);
            }
        }

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
        if((ucWDType & _TMDS_NO_CLK_WD) == _TMDS_NO_CLK_WD)
        {
            // clr NO CLK Flag
            ScalerSetBit(P73_B6_TMDS_UDC1, ~_BIT3, _BIT3);

            // Enable NO CLK video/audio WD
            ScalerSetBit(P73_B2_TMDS_DBB2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        }
#endif
    }
    else
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            // Disable packet variation Watch Dog
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_41_PORT_PAGE73_HDMI_VWDSR, ~_BIT0, 0x00);

            ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_45_PORT_PAGE73_HDMI_PVGCR0, 0x00);
            ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_AA_PORT_PAGE73_HDMI_PVGCR3, 0x00);

#if(_HW_HDMI_AVI_ACE_WD_SUPPORT == _ON)
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_AB_PORT_PAGE73_HDMI_PVGCR4, ~_BIT4, 0x00);
#endif

            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_46_PORT_PAGE73_HDMI_PVGCR1, ~_BIT0, 0x00);
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            // Disable AV Mute Watch Dog
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~_BIT7, 0x00);
        }

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
        if((ucWDType & _TMDS_NO_CLK_WD) == _TMDS_NO_CLK_WD)
        {
            // Disable NO CLK video/audio WD
            ScalerSetBit(P73_B2_TMDS_DBB2, ~(_BIT5 | _BIT4), 0x00);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : BCH Error Check
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRx4BchErrorCheck(EnumInputPort enumInputPort)
{
    BYTE ucBchErrorCount = 0x00;

    for(BYTE ucBchCheck = 0; ucBchCheck < 9; ucBchCheck++)
    {
        if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_02_PORT_PAGE73_HDMI_BCHCR, _BIT2) == _BIT2)
        {
            // Clr BCH Error Flag
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_02_PORT_PAGE73_HDMI_BCHCR, ~_BIT2, 0x00);

            ucBchErrorCount += 0x01;

            ScalerTimerDelayXms(3);
        }
        else
        {
            break;
        }
    }

    if(ucBchErrorCount == 0x09)
    {
        ScalerTmdsPhyRxUnstableFifoReset(enumInputPort);

        DebugMessageRx4("BCH Error Reset PHY FIFO", ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_02_PORT_PAGE73_HDMI_BCHCR, _BIT2));

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif // End of #if(_HDMI_MAC_RX4_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4PowerOffProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    // Disable EDID read/ SCL toggle IRQ
    ScalerMcuDdcSetSclToggleIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort), _DISABLE);
    ScalerMcuDdcSetEdidReadIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort), _DISABLE);

    ScalerTmdsMacRx4FreqDetectDisable();

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
    ScalerTmdsMacRx4ScrambleDetectDisable();
#endif
}

//--------------------------------------------------
// Description  : TMDS Freq. Detection IRQ Disable and Clear Clock Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4FreqDetectDisable(void)
{
    // Disable TMDS Freq. Detect IRQ
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), 0x00);
    ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), 0x00);

    // Clear TMDS Clk Count
    g_usTmdsMacRx4ClkCount = 0;

    ScalerTmdsPhyRxFifoAutoResetEnable(ScalerTmdsMacRxRxDxMapping(_RX4), _DISABLE);

    // Clear PHY SET flag
    CLR_TMDS_MAC_RX4_PHY_SET();

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
    // clr Retry to Set Phy Flag
    CLR_TMDS_MAC_RX4_RETRY_SET_PHY();

    // Cancel WD Timer Event
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX4_TMDS_RETRY_SET_PHY);
#endif

    // Disable HDMI MAC Power
    ScalerSetBit(P73_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Power down PLL
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
    // Disable TMDS CED Function & Lock Transition
    ScalerTmdsMacRx4SetCedLockTransition(_DISABLE);

    // Set Read Request 1ms reference clock to internal OSC
    ScalerSetBit(P73_1A_HDMI_CTRL_1A, ~_BIT3, _BIT3);

    // Set time interval form bus free to Read Request(4.7us~500us)
    ScalerSetByte(P73_1B_HDMI_CTRL_1B, (_BIT4 | _BIT0));
#endif
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4FirstActiveProc(EnumSourceType enumSourceType)
{
    enumSourceType = enumSourceType;

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
    // Enable NO CLK WD
    ScalerTmdsMacRx4HdmiWatchDog(_TMDS_NO_CLK_WD, _ENABLE);
#endif
}

//--------------------------------------------------
// Description  : Set Config of TMDS Mac Deonly mode
// Input Value  : None
// Output Value : enumInputPort, enumDeonlyConfig
//--------------------------------------------------
void ScalerTmdsMacRx4SetDeOnlyModeConfig(EnumDeOnlyConfig enumDeonlyConfig)
{
    // De only enable?
    if((enumDeonlyConfig & _DE_ONLY_DISABLE) == _DE_ONLY_DISABLE)
    {
        ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
    }
    else if((enumDeonlyConfig & _DE_ONLY_ENABLE) == _DE_ONLY_ENABLE)
    {
        ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
    }

    // Set HS
    if((enumDeonlyConfig & _DE_ONLY_HS_8T) == _DE_ONLY_HS_8T)
    {
        ScalerSetBit(P73_AB_TMDS_ACC2, ~_BIT7, _BIT7);
    }
    else if((enumDeonlyConfig & _DE_ONLY_HS_72T) == _DE_ONLY_HS_72T)
    {
        ScalerSetBit(P73_AB_TMDS_ACC2, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get Config of TMDS Mac Deonly mode
// Input Value  : None
// Output Value : EnumDeOnlyConfig
//--------------------------------------------------
EnumDeOnlyConfig ScalerTmdsMacRx4GetDeOnlyModeConfig(void)
{
    EnumDeOnlyConfig enumDeConfig = _DE_NO_INDICATED;

    if(ScalerGetBit(P73_A7_TMDS_PWDCTL, _BIT7) == _BIT7)
    {
        enumDeConfig = _DE_ONLY_ENABLE;
    }
    else
    {
        enumDeConfig = _DE_ONLY_DISABLE;
    }

    if(ScalerGetBit(P73_AB_TMDS_ACC2, _BIT7) == _BIT7)
    {
        enumDeConfig |= _DE_ONLY_HS_8T;
    }
    else
    {
        enumDeConfig |= _DE_ONLY_HS_72T;
    }

    return enumDeConfig;
}

//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4TMDSScanInitial(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    ScalerTmdsMacRx4Initial(enumInputPort);

    ScalerTmdsMacRx4InterruptInitial();
}

//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTmdsMacRx4TMDSPSPreDetect(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    if(ScalerDebugCheckDebugPort(enumMappingPort) == _FALSE)
#endif
    {
        // DDC handshake Detected
        if(ScalerMcuDdcGetDdcDetectFlag(enumMappingPort) == _TRUE)
        {
            DebugMessageRx4("7. PowerSaving D4 DDC", 0);

            ScalerMcuDdcClrDdcDetectFlag(enumMappingPort);

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            SET_TMDS_MAC_RX4_PS_WAKEUP();
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
            SET_TMDS_MAC_RX4_TOGGLE_Z0();
#endif
            return _TRUE;
        }
    }

    // Enable DDC Toggle IRQ
    if((ScalerMcuDdcGetSclToggleIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort)) == _FALSE) && (ScalerMcuDdcGetDdcDetectFlag(enumMappingPort) != _TRUE))
    {
        ScalerMcuDdcSetSclToggleIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort), _ENABLE);
    }

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT2), 0x00);
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P73_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P73_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        SET_TMDS_MAC_RX4_PS_WAKEUP();
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_MAC_RX4_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), 0x00);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for TMDS(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTmdsMacRx4TMDSNormalPreDetect(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    if(ScalerDebugCheckDebugPort(enumMappingPort) == _FALSE)
#endif
    {
        // DDC handshake Detected
        if(ScalerMcuDdcGetDdcDetectFlag(enumMappingPort) == _TRUE)
        {
            DebugMessageRx4("7. Normal D4 DDC", 0);

            ScalerMcuDdcClrDdcDetectFlag(enumMappingPort);

            return _TRUE;
        }
    }

    // Enable DDC Toggle IRQ
    if((ScalerMcuDdcGetSclToggleIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort)) == _FALSE) && (ScalerMcuDdcGetDdcDetectFlag(enumMappingPort) != _TRUE))
    {
        ScalerMcuDdcSetSclToggleIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort), _ENABLE);

        ScalerMcuDdcClrDdcDetectFlag(enumMappingPort);
    }

    ScalerTimerDelayXms(6);

    if(GET_TMDS_MAC_RX4_PHY_SET() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerTmdsMacRx4HdcpEnabled(void)
{
    BYTE pucHDCPFrameCount[2] = {0};

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    if((ScalerGetBit(P73_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P6D_26_HDCP_I2C_CTRL_0, _BIT7) == 0x00))
#endif
    {
        pucHDCPFrameCount[0] = ScalerGetDataPortSingleByte(P73_C3_HDCP_AP, _P73_C4_PT_C0_PORT_PAGE73_HDCP_FCR);

        // Wait 2Vsync to make sure frame counter changing, and timeout 45ms (margin + 1/24 frame+rate)
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P73_A4_TMDS_CTRL, _BIT3, _TRUE);
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P73_A4_TMDS_CTRL, _BIT3, _TRUE);

        pucHDCPFrameCount[1] = ScalerGetDataPortSingleByte(P73_C3_HDCP_AP, _P73_C4_PT_C0_PORT_PAGE73_HDCP_FCR);

        if(pucHDCPFrameCount[0] != pucHDCPFrameCount[1])
        {
            return _TRUE;
        }

        return _FALSE;
    }
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    else if((ScalerGetBit(P73_C0_HDCP_CR, _BIT0) == 0x00) && (ScalerGetBit(P6D_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7))
    {
        if(ScalerGetByte(P6D_2C_HDCP_I2C_CTRL_6) == 0x10)
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _FALSE;
    }
#endif
}

//--------------------------------------------------
// Description  : Clear All Received Status of Packet
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4ResetAllPacketReceiveStatus(void)
{
    // Clear AVI infoframe & GCP packet Detection Flag
    ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Clear RSV 0~3 detection Flag
    ScalerSetByte(P73_CC_HDMI_GPVS, (_BIT6 | _BIT5));
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Clear VSIF(RSV 7) & RSV 4 detection Flag
    ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // Clear VTEM flag
    ScalerSetBit(P73_54_PAGE73_EMP_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
}

//--------------------------------------------------
// Description  : Detect TMDS video mode
// Input Value  : bWait => Whether to wait then read
// Output Value : TMDS video type
//--------------------------------------------------
BYTE ScalerTmdsMacRx4TMDSVideoDetect(bit bWait)
{
    BYTE ucTemp = _TMDS_VIDEO_DATA_NONE;

    if(bWait == _WAIT)
    {
        // Wait at least 1 frame for HW auto update TMDS video RGBHV valid value
        ScalerTimerPollingFlagProc(45, P73_A4_TMDS_CTRL, _BIT3, _TRUE);

        // Wait for HW update DE flag
        if(ScalerTimerPollingFlagProc(20, P73_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // H/Vsync received
            if(ScalerGetBit(P73_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
            {
                ucTemp = _TMDS_VIDEO_DATA_RGBHV;
            }
            else
            {
                ucTemp = _TMDS_VIDEO_DATA_DE_ONLY;
            }
        }
        else
        {
            ucTemp = _TMDS_VIDEO_DATA_NONE;
        }

        CLR_TMDS_MAC_RX4_RGBHV_DETECTING();

        return ucTemp;
    }
    else
    {
        // R/G/B data detected
        if(ScalerGetBit(P73_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            // H/Vsync received
            if(ScalerGetBit(P73_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
            {
                ucTemp = _TMDS_VIDEO_DATA_RGBHV;
            }
            else
            {
                ucTemp = _TMDS_VIDEO_DATA_DE_ONLY;
            }
        }
        else
        {
            ucTemp = _TMDS_VIDEO_DATA_NONE;
        }

        // Clear video Detection Flag
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        SET_TMDS_MAC_RX4_RGBHV_DETECTING();

        // Activate TMDS video Detection Event
        ScalerTimerActiveTimerEvent(45, _SCALER_TIMER_EVENT_RX4_TMDS_VIDEO_DETECT);

        return ucTemp;
    }
}

//--------------------------------------------------
// Description  : TMDS video Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4TMDSVideoDetectEvent(void)
{
    CLR_TMDS_MAC_RX4_RGBHV_DETECTING();
}

//--------------------------------------------------
// Description  : Check CDR Locked
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
bit ScalerTmdsMacRx4CheckCDRStable(WORD usClkCount)
{
    BYTE ucStableIrq = 0;
    BYTE ucUnstableIrq = 0;

    // Backup Stable IRQ && Unstable IRQ enable bit status
    ucStableIrq = ScalerGetByte(P73_EF_HDMI_ERROR_TH);

    ucUnstableIrq = ScalerGetByte(P73_E6_HDMI_FREQDET_CTRL);

    // Disable INT Clock Check
    ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), 0x00);

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

    if(GET_TMDS_MAC_RX4_HIGH_SPEED_MODE() == _TRUE)
    {
        // Check Current Measured Freq. is the same as previously locked
        if(abs(usClkCount - (ScalerTmdsMacRx4MeasureClk(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
        {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) != _BIT6)
#endif
            {
                // Restore INT Clock Check
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6 | _BIT5), (ucStableIrq & _BIT7));

                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), (ucUnstableIrq & _BIT1));
            }

            return _FALSE;
        }

        if(abs(usClkCount - (ScalerTmdsMacRx4MeasureClk(_CLK_SOURCE_BLUE) * 4)) > (usClkCount >> 6))
        {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) != _BIT6)
#endif
            {
                // Restore INT Clock Check
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6 | _BIT5), (ucStableIrq & _BIT7));

                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), (ucUnstableIrq & _BIT1));
            }

            return _FALSE;
        }

        if(abs(usClkCount - (ScalerTmdsMacRx4MeasureClk(_CLK_SOURCE_GREEN) * 4)) > (usClkCount >> 6))
        {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) != _BIT6)
#endif
            {
                // Restore INT Clock Check
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6 | _BIT5), (ucStableIrq & _BIT7));

                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), (ucUnstableIrq & _BIT1));
            }

            return _FALSE;
        }
    }
    else
#endif
    {
        // Check Current Measured Freq. is the same as previously locked
        if(abs(usClkCount - ScalerTmdsMacRx4MeasureClk(_CLK_SOURCE_RED)) > (usClkCount >> 6))
        {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) != _BIT6)
#endif
            {
                // Restore INT Clock Check
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6 | _BIT5), (ucStableIrq & _BIT7));

                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), (ucUnstableIrq & _BIT1));
            }

            return _FALSE;
        }

        if(abs(usClkCount - ScalerTmdsMacRx4MeasureClk(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
        {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) != _BIT6)
#endif
            {
                // Restore INT Clock Check
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6 | _BIT5), (ucStableIrq & _BIT7));

                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), (ucUnstableIrq & _BIT1));
            }

            return _FALSE;
        }

        if(abs(usClkCount - ScalerTmdsMacRx4MeasureClk(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
        {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) != _BIT6)
#endif
            {
                // Restore INT Clock Check
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6 | _BIT5), (ucStableIrq & _BIT7));

                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), (ucUnstableIrq & _BIT1));
            }

            return _FALSE;
        }
    }

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
    if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) != _BIT6)
#endif
    {
        // Restore INT Clock Check
        ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6 | _BIT5), (ucStableIrq & _BIT7));

        ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), (ucUnstableIrq & _BIT1));
    }

    return _TRUE;
}

#if(_HDMI_DPC_FIFO_ERR_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Deep Color FIFO Error
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRx4HdmiCheckDeepColorFifo(void)
{
    BYTE ucmMax = 0;

    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_82_PORT_PAGE73_HDMI_DPC_SET2, ~(_BIT4 | _BIT3), _BIT3);

    ScalerTimerDelayXms(6);

    ucmMax = ((ScalerGetDataPortSingleByte(P73_C9_HDMI_AP, _P73_CA_PT_81_PORT_PAGE73_HDMI_DPC_SET1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

    if((ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_82_PORT_PAGE73_HDMI_DPC_SET2, _BIT0) == _BIT0) && (ucmMax < 0x09))
    {
        ucmMax = ucmMax + 1;

        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_81_PORT_PAGE73_HDMI_DPC_SET1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ucmMax << 4));
        DebugMessageRx4("RX4: Deep color fifo error", ucmMax);

        return _FALSE;
    }
    else if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_82_PORT_PAGE73_HDMI_DPC_SET2, _BIT0) == _BIT0)
    {
        DebugMessageRx4("RX4: Deep color fifo error, Full Notify Level:9", ucmMax);
    }

    return _TRUE;
}
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiAVMuteProc(void)
{
    // if AVMute Has been triggered
    if((ScalerGetBit(P73_CB_HDMI_SR, _BIT6) == 0x00) && (ScalerGetBit(P73_A6_TMDS_OUTCTL, (_BIT6 | _BIT5 | _BIT4)) == 0x00))
    {
        // Clear AVMute Flag
        ScalerSetBit(P73_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT7);

        // Disable AVMute Watch Dog
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~_BIT7, 0x00);

        // Enable Video/Audio Output
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~(_BIT6 | _BIT5 | _BIT3), (_BIT6 | _BIT5 | _BIT3));

        // Enable RGB Output
        ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

        // Enable AVMute Watch Dog
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~_BIT7, _BIT7);
    }
}
#endif

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
//--------------------------------------------------
// Description  : TMDS handle WD when no clk
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4NoClkWatchDogProc(void)
{
    if((ScalerGetBit(P73_B6_TMDS_UDC1, _BIT3) == _BIT3) && (ScalerGetBit(P73_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
        // clr Freq Stable Flag
        ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

        ScalerTimerDelayXms(5);

        if(ScalerGetBit(P73_EF_HDMI_ERROR_TH, _BIT6) == _BIT6)
        {
            // clr NO CLK Flag
            ScalerSetBit(P73_B6_TMDS_UDC1, ~_BIT3, _BIT3);

            // Disable NO CLK WD
            ScalerSetBit(P73_B2_TMDS_DBB2, ~(_BIT5 | _BIT4), 0x00);

            // Enable Video/Audio Output
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~(_BIT6 | _BIT5 | _BIT3), (_BIT6 | _BIT5 | _BIT3));

            // Enable RGB Output
            ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

            // Enable NO CLK WD
            ScalerSetBit(P73_B2_TMDS_DBB2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        }
    }
}

#endif

//--------------------------------------------------
// Description  : Detect TMDS Format
// Input Value  : None
// Output Value : Return DVI or HDMI format
//--------------------------------------------------
EnumSourceType ScalerTmdsMacRx4FormatDetect(void)
{
    // Polling at least 3 frame for HW auto detect TMDS format
    if(ScalerTimerPollingFlagProc(130, P73_CB_HDMI_SR, _BIT0, _TRUE) == _TRUE)
    {
        ScalerSetBit(P73_AF_TMDS_WDC, ~_BIT0, 0x00);

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

        // Check if HDMI 2.0 ON
        if(ScalerGetBit(P73_00_HDMI_CTRL_00, _BIT0) == _BIT0)
        {
            // Set Manual Format to HDMI
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Toggle HW Format Detect Flag Reset
            ScalerSetBit(P73_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
            ScalerSetBit(P73_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

            SET_TMDS_MAC_RX4_HDMI20_FORMAT_RESET_WAITING();

            ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX4_HDMI2_FORMAT_RESET_WAIT);
        }
#endif
        return _SOURCE_HDMI;
    }
    else
    {
        ScalerSetBit(P73_AF_TMDS_WDC, ~_BIT0, _BIT0);

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

        if(ScalerGetBit(P73_00_HDMI_CTRL_00, _BIT0) == _BIT0)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI2_FORMAT_RESET_WAIT);
        }

#endif
        // Set Format Detect HW Auto Mode
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

        return _SOURCE_DVI;
    }
}

//--------------------------------------------------
// Description  : TMDS After Hot Plug Event Process
// Input Value  : bRestoreZ0
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4AfterHotPlugEventProc(bit bRestoreZ0)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

#if((_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _OFF) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF))
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (ScalerTmdsMacRxGetCableStatus(enumMappingPort) == _TRUE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((ScalerTmdsMacRxGetCableStatus(enumMappingPort) == _TRUE) || (GET_TMDS_MAC_RX4_HPD_TIMER_EVENT_TOGGLING_CABLE_ON() == _TRUE)))
#endif
    {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)

#if(_HDMI_HDCP22_REAUTH_IN_RESET_PROC == _ON)
        // Set HDCP2.2 RE AUTH
        ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_71_PORT_PAGE73_HDCP2_STATUS2, ~(_BIT3 | _BIT1 | _BIT0), _BIT3);
#endif

#endif

        // Restore Slave Address
        ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_C2_PORT_PAGE73_HDCP_SLAVE_ADD, g_ucTmdsMacRx4SlaveAddr);

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        // Enable HDMI 2.0 SCDC Function
        ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

        ScalerTmdsMacRxHpd5vPinCheckEvent(ScalerTmdsMacRxRxDxMapping(_RX4), _ENABLE);
#endif

#if(_DELL_HDMI_HPD_DDC_STYLE_SUPPORT == _ON)
        if(g_ucTmdsMacRx4DdcramNackStatus == _FALSE)
        {
            // DDCRAM Force Nack off
            ScalerMcuDdcSetForceNack(enumMappingPort, _OFF);
        }

        // Restore DDCCI Slave Address
        ScalerMcuDdcciEnable(_ENABLE, enumMappingPort);
#endif

        if(bRestoreZ0 == _TRUE)
        {
            // Restore Z0 Status
            ScalerTmdsPhyRxRestoreZ0Status(enumMappingPort, g_ucTmdsMacRx4Z0Status);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            // Restore Main link related IRQ After Z0 on
            ScalerHdmiFrlMacRx4IrqRestoreAfterZ0On();
#endif
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Hot Plug High Process
// Input Value  : usHpdTime
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRx4HotPlugHighProc(WORD usHpdTime)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

#if((_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _OFF) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF))
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (ScalerTmdsMacRxGetCableStatus(enumMappingPort) == _TRUE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((ScalerTmdsMacRxGetCableStatus(enumMappingPort) == _TRUE) || (GET_TMDS_MAC_RX4_HPD_TIMER_EVENT_TOGGLING_CABLE_ON() == _TRUE)))
#endif
    {
        ScalerTimerDelayXms(usHpdTime);

#if(_AUDIO_SUPPORT == _ON)
#if((_AUDIO_EARC_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP))
        if((GET_AUDIO_ARC_TX_LINK_MODE() == _EARC_MODE) && (ScalerAudioGetArcDxPort() == enumMappingPort))
        {
            ScalerHdmiArcTxEarcSetHbHpdStatus(_HIGH);
        }
        else
#endif
#endif
        {
            ScalerTmdsMacRxSetDxHPD(enumMappingPort, _HIGH);
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Low Process
// Input Value  : enumInputPort
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRx4HotPlugLowProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

#if((_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _OFF) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF))
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (ScalerTmdsMacRxGetCableStatus(enumMappingPort) == _TRUE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((ScalerTmdsMacRxGetCableStatus(enumMappingPort) == _TRUE) || (GET_TMDS_MAC_RX4_HPD_TIMER_EVENT_TOGGLING_CABLE_ON() == _TRUE)))
#endif
    {
#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_ARC_SUPPORT == _ON))
        if(ScalerAudioGetArcDxPort() == enumMappingPort)
        {
#if((_AUDIO_EARC_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP))
            if(GET_AUDIO_ARC_TX_LINK_MODE() == _EARC_MODE)
            {
                ScalerHdmiArcTxEarcSetHbHpdStatus(_LOW);
            }
            else
#endif
            {
                ScalerTmdsMacRxSetDxHPD(enumMappingPort, _LOW);

                SET_TMDS_MAC_RX_HPD_TOGGLE_RESET_ARC_TX_EVENT();
            }
        }
        else
#endif
        {
            ScalerTmdsMacRxSetDxHPD(enumMappingPort, _LOW);
        }

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_EIZO_PS_WAKEUP)
#endif
        {
            ScalerTmdsMacRx4SwitchHdcpSlaveAddr();
        }

#if(_DELL_HDMI_HPD_DDC_STYLE_SUPPORT == _ON)
        g_ucTmdsMacRx4DdcramNackStatus = ScalerMcuDdcGetForceNackStatus(enumMappingPort);

        if(g_ucTmdsMacRx4DdcramNackStatus == _FALSE)
        {
            // DDCRAM Force Nack
            ScalerMcuDdcSetForceNack(enumMappingPort, _ON);
        }

        // Set DDCCI Force Nack
        ScalerMcuDdcciEnable(_DISABLE, enumMappingPort);
#endif
    }
}

//--------------------------------------------------
// Description  : TMDS Before Hot Plug Event Process
// Input Value  : bDisableZ0
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4BeforeHotPlugEventProc(bit bDisableZ0)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (ScalerTmdsMacRxGetCableStatus(enumMappingPort) == _TRUE))
    {
#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX4_ACTIVE_TYPE_HPD_TOGGLING() == _TRUE)
        {
            // Disable Freq Stable IRQ
            ScalerSetBit_EXINT(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), _BIT6);
        }
#endif

        // Save Z0 Status
        g_ucTmdsMacRx4Z0Status = ScalerTmdsPhyRxSaveZ0Status(enumMappingPort);

        // Backup Slave Address
        g_ucTmdsMacRx4SlaveAddr = ScalerGetDataPortSingleByte(P73_C3_HDCP_AP, _P73_C4_PT_C2_PORT_PAGE73_HDCP_SLAVE_ADD);

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
#if(_AUDIO_EARC_SUPPORT == _ON)
        // Only toggle virtual HPD_status in eARC Mode, physical HPD pin status remain high.
        if(GET_AUDIO_ARC_TX_LINK_MODE() != _EARC_MODE)
#endif
        {
            ScalerTmdsMacRxHpd5vPinCheckEvent(enumMappingPort, _DISABLE);
        }
#endif

        // User Option Proc for Before HPD Proc
        if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE)
        {
            // Video Mute
            ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

            if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NORMAL) && (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_ACER))
            {
                // Set Notify flag for sys reset mode
                SET_TMDS_MAC_RX4_HPD_RESET_TO_SEARCH_EVENT();
            }
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_EIZO_PS_WAKEUP)
#endif
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_MAC_RX4_SUPPORT == _ON))
                // Reset HDCP 2.2
                ScalerTmdsHdcp2Rx4ResetProc();
#endif
            }
        }

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_EIZO_PS_WAKEUP)
#endif
        {
#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
            // Disable HDMI 2.0 SCDC Function
            ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, 0x00);
#endif
            if(bDisableZ0 == _TRUE)
            {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                // Backup and Disable Main link related IRQ before Z0 off to prevetn FRL 8/10/12G signal unstable
                ScalerHdmiFrlMacRx4IrqBackupBeforeZ0Off();
#endif

                // Disable Z0
                ScalerTmdsPhyRxSetZ0Status(enumMappingPort, _DISABLE);
            }
        }

#if((_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON) || (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON))
        // Set if HPD Proc already toggled & Cable is ON in Before Proc
        SET_TMDS_MAC_RX4_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();
#endif
    }
    else if(ScalerTmdsMacRxGetCableStatus(enumMappingPort) == _FALSE)
    {
        // Reset DDC4
        ScalerMcuDdcReset(enumMappingPort);
    }
}

//--------------------------------------------------
// Description  : Backup HDCP Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4BackupHdcpType(void)
{
    if((ScalerGetBit(P73_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P73_A9_TMDS_ABC0, _BIT6) == _BIT6))
    {
        SET_TMDS_MAC_RX4_BACKUP_HDCP_TYPE(_HDCP_14);
    }
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    else if((ScalerGetBit(P6D_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7) && (ScalerGetByte(P6D_2C_HDCP_I2C_CTRL_6) == 0x10))
    {
        SET_TMDS_MAC_RX4_BACKUP_HDCP_TYPE(_HDCP_22);
    }
#endif
    else
    {
        SET_TMDS_MAC_RX4_BACKUP_HDCP_TYPE(_HDCP_NONE);
    }
}

//--------------------------------------------------
// Description  : HDCP 1.4 R0 IIC 20k issue Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4Hdcp1p4AksvClear(void)
{
    // Disable R0 ready bit
    ScalerSetBit(P73_AE_TMDS_RPS, ~_BIT1, 0x00);
}

//--------------------------------------------------
// Description  : HDCP Bksv and Ri flag clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdcpFlagClear(void)
{
    // Clear Bksv and Ri flag, protect Aksv and Slave hit flag
    ScalerSetBit(P73_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Event
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRx4HotPlugEvent(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    enumMappingPort = enumMappingPort;

    if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
    {
        ScalerTmdsMacRx4BeforeHotPlugEventProc(_TRUE);
    }
    else
    {
        ScalerTmdsMacRx4BeforeHotPlugEventProc(_FALSE);
    }

    if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
    {
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
        // wait Z0 / HPD Interval
        ScalerTimerDelayXms(GET_HDMI_Z0_HPD_INTERVAL());
#else
        ScalerTimerActiveTimerEvent(GET_HDMI_Z0_HPD_INTERVAL(), _SCALER_TIMER_EVENT_RX4_TMDS_HPD_Z0_INTERVAL_FINISH);
#endif
    }

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
    if(GET_HDMI_Z0_HPD_TYPE() != _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
#endif
    {
        // HPD Low
        ScalerTmdsMacRx4HotPlugLowProc();

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        // HPD Low then Reset Scramble Status
        ScalerTmdsMacRx4ScrambleStatusReset();
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        // HPD Low then Reset Hdmi2.1
        ScalerHdmiFrlMacRx4ResetProc();
#endif
    }

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
    // wait
    if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
    {
        ScalerTmdsMacRx4HotPlugHighProc(GET_HDMI_HOTPLUG_TIME());
    }
    else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
    {
        ScalerTmdsMacRx4HotPlugHighProc(_TMDS_HDCP_2_2_HPD_TIME);
    }
    else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ACER)
    {
        ScalerTmdsMacRx4HotPlugHighProc(_TMDS_ACER_HPD_TIME);
    }
    else if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
    {
        ScalerTmdsMacRx4HotPlugHighProc(_TMDS_EDID_SWITCH_HPD_TIME);
    }
    else
    {
        ScalerTmdsMacRx4HotPlugHighProc(GET_HDMI_HOTPLUG_TIME());
    }
#else
    if(GET_HDMI_Z0_HPD_TYPE() != _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
    {
        // wait
        if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
        {
            ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
        }
        else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
        {
            ScalerTimerActiveTimerEvent(_TMDS_HDCP_2_2_HPD_TIME, _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
        }
        else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ACER)
        {
            ScalerTimerActiveTimerEvent(_TMDS_ACER_HPD_TIME, _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
        }
        else if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
        {
            ScalerTimerActiveTimerEvent(_TMDS_EDID_SWITCH_HPD_TIME, _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
        }
        else
        {
            ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
        }
    }
#endif

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
    if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
    {
        // Restore Slave Address & Z0 Status
        ScalerTmdsMacRx4AfterHotPlugEventProc(_TRUE);
    }
    else
    {
        // Restore Slave Address
        ScalerTmdsMacRx4AfterHotPlugEventProc(_FALSE);
    }

    if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
    {
        // wait HPD / Z0 Interval
        ScalerTimerDelayXms(GET_HDMI_Z0_HPD_INTERVAL());

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        // Backup and Disable Main link related IRQ before Z0 off to prevetn FRL 8/10/12G signal unstable
        ScalerHdmiFrlMacRx4IrqBackupBeforeZ0Off();
#endif

        // Disable Z0
        ScalerTmdsPhyRxSetZ0Status(enumMappingPort, _DISABLE);

        // wait Z0 Low Period
        ScalerTimerDelayXms(GET_HDMI_Z0_LOW_PERIOD());
    }

    DebugMessageRx4("Rx4 HPD Toggle!!", 0);

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
    if(GET_TMDS_MAC_RX4_TOGGLE_Z0_EVENT() == _TRUE)
    {
        CLR_TMDS_MAC_RX4_TOGGLE_Z0();
        CLR_TMDS_MAC_RX4_TOGGLE_Z0_EVENT();
    }
#endif

    CLR_TMDS_MAC_RX4_HPD_TRIGGER_EVENT();
#endif // End of #if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
}

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Config EMP SRAM
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4EmpSramSetting(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // [7] VS Enable; [6] DHDR Enable; [4] Share mode
        BYTE ucEmpConfig = 0x00;

        // set share mode
        ucEmpConfig = _BIT4;

#if((_DM_FUNCTION == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
        // Enable VS IRQ & w1c all flag
        ScalerSetBit(P6D_70_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

#if(_HDMI_SBTM_SUPPORT == _ON)
        // Detect VS EMP w/ org_id and tag
        ScalerSetBit(P6D_8A_VS_EMP_1A, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // org id & tag
        ScalerSetByte(P6D_7C_VS_ORG_ID, _HDMI21);

        ScalerSetByte(P6D_8B_VS_EMP_1B, 0x00);
        ScalerSetByte(P6D_8C_VS_EMP_1C, 0x03);
#elif(_DM_FUNCTION == _ON)
        // Detect VS EMP w/ org_id only
        ScalerSetBit(P6D_8A_VS_EMP_1A, ~(_BIT7 | _BIT6), _BIT6);

        // org id
        ScalerSetByte(P6D_7C_VS_ORG_ID, _VENDOR_SPECIFIC);
#endif

        // Enable VS EMP stored
        ucEmpConfig |= _BIT7;
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
        // Enable D-HDR IRQ & w1c all flag
        ScalerSetBit(P6D_71_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Enable D-HDR EMP stored
        ucEmpConfig |= _BIT6;
#endif
        // Set EMP Config
        ScalerSetBit(P6D_88_HDMI_EMP_SRAM_CTRL0, ~(_BIT7 | _BIT6 | _BIT4), ucEmpConfig);
    }
    else
    {
        // Disable EMP stored
        ScalerSetBit(P6D_88_HDMI_EMP_SRAM_CTRL0, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P6D_8A_VS_EMP_1A, ~(_BIT7 | _BIT6), 0x00);

        // [7] Disable VS/ D-HDR IRQ
        ScalerSetBit(P6D_70_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit(P6D_71_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
}
#endif

/*
//--------------------------------------------------
// Description  : Enable/Disable HDMI Related IRQ_en
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HdmiIrqEnable(bit bEnable, StructHdmiIrqStatus *pstTmdsMacIrqStatus)
{
    if(bEnable == _ENABLE)
    {
        // HDCP 1.4 Write Aksv IRQ have been Received
        ScalerSetBit(P73_AA_TMDS_ABC1, ~_BIT4, (pstTmdsMacIrqStatus->b1HdcpAksvIrqBackup << 4));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P6D_35_HDCP_I2C_CTRL_7, ~_BIT0, pstTmdsMacIrqStatus->b1Hdcp2WrDoneIrqBackup);
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        // Enable SCDC 0x20 Change/Source Write Read Request Enable IRQ
        ScalerSetBit(P73_26_HDMI_CTRL_26, ~(_BIT4 | _BIT3), (pstTmdsMacIrqStatus->b2ScdcChangeIrqBackup << 3));

        // Read Request Done into IRQ
        ScalerSetBit(P73_1F_HDMI_CTRL_1F, ~_BIT3, (pstTmdsMacIrqStatus->b1ReadRequestIrqBackup << 3));
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
        {
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT0, pstTmdsMacIrqStatus->b1FrlRsv0IrqBackup);
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT1, (pstTmdsMacIrqStatus->b1FrlRsv1IrqBackup << 1));
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT2, (pstTmdsMacIrqStatus->b1FrlRsv2IrqBackup << 2));
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT3, (pstTmdsMacIrqStatus->b1FrlRsv3IrqBackup << 3));
#endif

            // Source set FRL rate, Source clear FLT_update, Source clear FRL_Start
            ScalerSetBit(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (pstTmdsMacIrqStatus->b1FrlRateIrqBackup << 6));
            ScalerSetBit(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (pstTmdsMacIrqStatus->b1FrlStartIrqBackup << 4));
            ScalerSetBit(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (pstTmdsMacIrqStatus->b1FltUpdateIrqBackup << 2));

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
            // "VS EMP" received into IRQ
            ScalerSetBit(P1E_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pstTmdsMacIrqStatus->b1FrlVsEmpIrqBackup << 7));
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
            // "D-HDR EMP" received into IRQ
            ScalerSetBit(P1E_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pstTmdsMacIrqStatus->b1FrlDhdrEmpIrqBackup << 7));
#endif

#if(_AUDIO_SUPPORT == _ON)
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_8A_PORT_PAGE78_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), (pstTmdsMacIrqStatus->b1FrlAudioIrqBackup << 3));
#endif
        }
        else
#endif
        {
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT0, pstTmdsMacIrqStatus->b1Rsv0IrqBackup);
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT1, (pstTmdsMacIrqStatus->b1Rsv1IrqBackup << 1));
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT2, (pstTmdsMacIrqStatus->b1Rsv2IrqBackup << 2));
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT3, (pstTmdsMacIrqStatus->b1Rsv3IrqBackup << 3));
#endif

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
            // "VS EMP" received into IRQ
            ScalerSetBit(P6D_70_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pstTmdsMacIrqStatus->b1VsEmpIrqBackup << 7));
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
            // "D-HDR EMP" received into IRQ
            ScalerSetBit(P6D_71_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pstTmdsMacIrqStatus->b1DhdrEmpIrqBackup << 7));
#endif

#if(_AUDIO_SUPPORT == _ON)
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8A_PORT_PAGE73_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), (pstTmdsMacIrqStatus->b1TmdsAudioIrqBackup << 3));
#endif
        }
    }
    else
    {
        // Backup/Disable HDCP 1.4 Write Aksv IRQ
        pstTmdsMacIrqStatus->b1HdcpAksvIrqBackup = (ScalerGetBit(P73_AA_TMDS_ABC1, _BIT4) >> 4);
        ScalerSetBit(P73_AA_TMDS_ABC1, ~_BIT4, 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Backup/Disable HDCP 2.2 IRQ
        pstTmdsMacIrqStatus->b1Hdcp2WrDoneIrqBackup = ScalerGetBit(P6D_35_HDCP_I2C_CTRL_7, _BIT0);
        ScalerSetBit(P6D_35_HDCP_I2C_CTRL_7, ~_BIT0, 0x00);
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        // Backup/Disable SCDC 0x20 Change/Source Write Read Request IRQ
        pstTmdsMacIrqStatus->b2ScdcChangeIrqBackup = (ScalerGetBit(P73_26_HDMI_CTRL_26, (_BIT4 | _BIT3)) >> 3);
        ScalerSetBit(P73_26_HDMI_CTRL_26, ~(_BIT4 | _BIT3), 0x00);

        // Backup/Disable Read Request IRQ
        pstTmdsMacIrqStatus->b1ReadRequestIrqBackup = (ScalerGetBit(P73_1F_HDMI_CTRL_1F, _BIT3) >> 3);
        ScalerSetBit(P73_1F_HDMI_CTRL_1F, ~_BIT3, 0x00);
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
        {
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
            pstTmdsMacIrqStatus->b1FrlRsv0IrqBackup = ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, _BIT0);
            pstTmdsMacIrqStatus->b1FrlRsv1IrqBackup = (ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, _BIT1) >> 1);
            pstTmdsMacIrqStatus->b1FrlRsv2IrqBackup = (ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, _BIT2) >> 2);
            pstTmdsMacIrqStatus->b1FrlRsv3IrqBackup = (ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, _BIT3) >> 3);

            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

            // Backup/Disable FRL rate, Source clear FLT_update, Source clear FRL_Start IRQ
            pstTmdsMacIrqStatus->b1FrlRateIrqBackup = (ScalerGetBit(P73_3D_HDMI21_LT_0, _BIT6) >> 6);
            pstTmdsMacIrqStatus->b1FrlStartIrqBackup = (ScalerGetBit(P73_3D_HDMI21_LT_0, _BIT4) >> 4);
            pstTmdsMacIrqStatus->b1FltUpdateIrqBackup = (ScalerGetBit(P73_3D_HDMI21_LT_0, _BIT2) >> 2);
            ScalerSetBit(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
            // Backup/Disable Vs EMP IRQ
            pstTmdsMacIrqStatus->b1FrlVsEmpIrqBackup = (ScalerGetBit(P1E_51_EMP_VS, _BIT7) >> 7);
            ScalerSetBit(P1E_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
            // Backup/Disable Dhdr EMP IRQ
            pstTmdsMacIrqStatus->b1FrlDhdrEmpIrqBackup = (ScalerGetBit(P1E_53_EMP_DHDR, _BIT7) >> 7);
            ScalerSetBit(P1E_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#if(_AUDIO_SUPPORT == _ON)
            // Backup/Disable Audio IRQ
            pstTmdsMacIrqStatus->b1FrlAudioIrqBackup = (ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_8A_PORT_PAGE78_AUDIO_FREQDET, _BIT3) >> 3);
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_8A_PORT_PAGE78_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
#endif
        }
        else
#endif
        {
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
            pstTmdsMacIrqStatus->b1Rsv0IrqBackup = ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, _BIT0);
            pstTmdsMacIrqStatus->b1Rsv1IrqBackup = (ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, _BIT1) >> 1);
            pstTmdsMacIrqStatus->b1Rsv2IrqBackup = (ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, _BIT2) >> 2);
            pstTmdsMacIrqStatus->b1Rsv3IrqBackup = (ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, _BIT3) >> 3);

            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
            // Backup/Disable Vs EMP IRQ
            pstTmdsMacIrqStatus->b1VsEmpIrqBackup = (ScalerGetBit(P6D_70_EMP_VS, _BIT7) >> 7);
            ScalerSetBit(P6D_70_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
            // Backup/Disable Dhdr EMP IRQ
            pstTmdsMacIrqStatus->b1DhdrEmpIrqBackup = (ScalerGetBit(P6D_71_EMP_DHDR, _BIT7) >> 7);
            ScalerSetBit(P6D_71_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#if(_AUDIO_SUPPORT == _ON)
            // Backup/Disable Audio IRQ
            pstTmdsMacIrqStatus->b1TmdsAudioIrqBackup = (ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8A_PORT_PAGE73_AUDIO_FREQDET, _BIT3) >> 3);
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8A_PORT_PAGE73_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
#endif
        }
    }
}
*/

//--------------------------------------------------
// Description  : Enable/Disable RSV IRQ_en
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4RoundRobinIrqEnable(bit bEnable)
{
    bEnable = bEnable;

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
    BYTE ucRsv = 0;

    for(ucRsv = 0; ucRsv < 4; ucRsv++)
    {
        ScalerTmdsMacRx4RsvIrqEnable(ucRsv, bEnable);
    }
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable RSV IRQ_en
// Input Value  : RSV Number, ENABLE/DISABLE bit
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4RsvIrqEnable(EnumHdmiRsvNumber enumRsvNumber, bit bEnable)
{
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            if(bEnable == _ENABLE)
            {
                ScalerSetByte(P73_CC_HDMI_GPVS, _BIT5);
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT0, _BIT0);
            }
            else
            {
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT0, 0x00);
                ScalerSetByte(P73_CC_HDMI_GPVS, _BIT5);
            }
            break;

        case _HDMI_RSV_1:
            if(bEnable == _ENABLE)
            {
                ScalerSetByte(P73_CC_HDMI_GPVS, _BIT6);
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT1, _BIT1);
            }
            else
            {
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT1, 0x00);
                ScalerSetByte(P73_CC_HDMI_GPVS, _BIT6);
            }
            break;

        case _HDMI_RSV_2:
            if(bEnable == _ENABLE)
            {
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT2, _BIT2);
            }
            else
            {
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT2, 0x00);
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
            }
            break;

        case _HDMI_RSV_3:
            if(bEnable == _ENABLE)
            {
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT3, _BIT3);
            }
            else
            {
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_B5_PORT_PAGE73_HDMI_BED_FUNC_6, ~_BIT3, 0x00);
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);
            }
            break;

        case _HDMI_RSV_4:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
            }
            else
            {
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            }
            break;

        case _HDMI_RSV_5:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }
            else
            {
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            break;

        case _HDMI_RSV_6:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }
            else
            {
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }
            break;

        case _HDMI_RSV_7:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
            }
            else
            {
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P73_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
            }
            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Initialize RSV for HDMI VSIF
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4RsvInitial(void)
{
#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
    memset(&g_stTmdsMacRx4SpdInfo, 0x00, sizeof(g_stTmdsMacRx4SpdInfo));
#endif

    // Specify Packet Detect Type
    ScalerSetByte(P73_D4_PORT_PAGE73_HDMI_PTRSV6, _HDMI_AVI_INFO_TYPE);

    ScalerSetByte(P73_D3_PORT_PAGE73_HDMI_PTRSV5, _HDMI_GENERAL_CONTROL_TYPE);

#if(_HDMI_HDR10_SUPPORT == _ON)
    ScalerSetByte(P73_D2_PORT_PAGE73_HDMI_PTRSV4, _HDR_INFO_TYPE);
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
    ScalerSetByte(P73_CF_HDMI_PTRSV7, _SPD_INFO_TYPE);
    ScalerSetBit(P73_D7_HDMI_SHDR_IE_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));

    // Freesync Replay disable
    ScalerSetBit(P73_D6_HDMI_SHDR_IE, ~_BIT4, 0x00);

    // PR6 = 2b'10 is Replay, Other is Live Capture
    ScalerSetBit(P73_D6_HDMI_SHDR_IE, ~(_BIT3 | _BIT2), _BIT3);
#endif

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) && (_HDMI_VSIF_RCV_BY_RR == _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_43_PORT_PAGE73_HDMI_PTRSV0, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_44_PORT_PAGE73_HDMI_PTRSV1, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_A4_PORT_PAGE73_HDMI_PTRSV_2, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_A5_PORT_PAGE73_HDMI_PTRSV_3, _SPD_INFO_TYPE);

    // write Round Robin tag
    ScalerSetByte(P73_DD_PKT_ROUND_ROBIN_PT0, _HDMI_VSIF_TYPE);
    ScalerSetByte(P73_DE_PKT_ROUND_ROBIN_PT1, _HDMI_VSIF_TYPE);
    ScalerSetByte(P73_DF_PKT_ROUND_ROBIN_PT2, _SPD_INFO_TYPE);
#elif((_HDMI_SPD_IF_RCV_BY_RR == _ON) && (_HDMI_VSIF_RCV_BY_RR != _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_43_PORT_PAGE73_HDMI_PTRSV0, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_44_PORT_PAGE73_HDMI_PTRSV1, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_A4_PORT_PAGE73_HDMI_PTRSV_2, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_A5_PORT_PAGE73_HDMI_PTRSV_3, _SPD_INFO_TYPE);

    // write Round Robin tag
    ScalerSetByte(P73_DD_PKT_ROUND_ROBIN_PT0, _SPD_INFO_TYPE);
    ScalerSetByte(P73_DE_PKT_ROUND_ROBIN_PT1, _SPD_INFO_TYPE);
    ScalerSetByte(P73_DF_PKT_ROUND_ROBIN_PT2, _SPD_INFO_TYPE);
#elif((_HDMI_SPD_IF_RCV_BY_RR != _ON) && (_HDMI_VSIF_RCV_BY_RR == _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_43_PORT_PAGE73_HDMI_PTRSV0, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_44_PORT_PAGE73_HDMI_PTRSV1, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_A4_PORT_PAGE73_HDMI_PTRSV_2, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_A5_PORT_PAGE73_HDMI_PTRSV_3, _HDMI_VSIF_TYPE);

    // write Round Robin tag
    ScalerSetByte(P73_DD_PKT_ROUND_ROBIN_PT0, _HDMI_VSIF_TYPE);
    ScalerSetByte(P73_DE_PKT_ROUND_ROBIN_PT1, _HDMI_VSIF_TYPE);
    ScalerSetByte(P73_DF_PKT_ROUND_ROBIN_PT2, _HDMI_VSIF_TYPE);
#endif

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
    // ENABLE Round Robin
    ScalerSetBit(P73_B2_TMDS_DBB2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
#endif
}

//--------------------------------------------------
// Description  : Initialize TMDS setting for search
// Input Value  : Current Search Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4Initial(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // Disable TMDS output
    ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Set HS Width(DE only) and HDCP Reference VS
    ScalerSetBit(P73_AB_TMDS_ACC2, ~(_BIT7 | _BIT6), 0x00);

    // Set TMDS Hsync/Vsync Polarity as Input Raw Polarity
    ScalerSetBit(P73_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);

    // Disable C9/CA Port Auto-Inc
    ScalerSetBit(P73_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_HDMI_MAC_RX4_SUPPORT == _ON)

    ScalerTmdsMacRx4RoundRobinIrqEnable(_DISABLE);

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
    // Inactive EMP SRAM
    ScalerTmdsMacRx4EmpSramSetting(_DISABLE);
#endif

    ScalerTmdsMacRx4HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
    ScalerTmdsMacRx4HdmiWatchDog(_TMDS_NO_CLK_WD, _DISABLE);
#endif

    // Deep Color Mode clock and detection auto
    ScalerSetBit(P73_B8_TMDS_DPC1, ~(_BIT3 | _BIT2), _BIT2);

    // Enable BCH Detection
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_02_PORT_PAGE73_HDMI_BCHCR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT3));

    // DVI mode don't disable Audio Clk
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // Set Video Watch Dog New Mode
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_32_PORT_PAGE73_HDMI_WDCR1, ~_BIT5, _BIT5);

#if(_HDMI_DPC_FIFO_ERR_CHECK_SUPPORT == _ON)
    // Set Deep Color Fifo Error Count
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_82_PORT_PAGE73_HDMI_DPC_SET2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5));

    // Set Deep Color Fifo Full/Empty Level
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_81_PORT_PAGE73_HDMI_DPC_SET1, 0x73);
#endif

    // Rsv Assignment
    ScalerTmdsMacRx4RsvInitial();

    // Packet Variation Detect Disable
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_45_PORT_PAGE73_HDMI_PVGCR0, 0x00);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_46_PORT_PAGE73_HDMI_PVGCR1, 0x00);
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_47_PORT_PAGE73_HDMI_PVGCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_AA_PORT_PAGE73_HDMI_PVGCR3, 0x00);

#if(_HW_HDMI_AVI_ACE_WD_SUPPORT == _ON)
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_AB_PORT_PAGE73_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#else
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_AB_PORT_PAGE73_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
    if((ScalerGetBit(P73_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00) && (ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00))
#else
    if(ScalerGetBit(P73_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
#endif
    {
        // Reset SCDC read only register to default value
        ScalerSetBit(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), _BIT2);

        CLR_TMDS_MAC_RX4_HIGH_SPEED_MODE();
    }

    // Set Scrambling detection SSCP Number = 8, Enable HW Auto Detect Scrambling Control Symbol
    ScalerSetBit(P73_01_HDMI_CTRL_01, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

    // Set SCDC Port not auto increase
    ScalerSetBit(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable Ignore Source Transimit Read Request Enable
    ScalerSetBit(P73_1C_HDMI_CTRL_1C, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);

    // Set Read Request 1ms reference clock to XTAL
    ScalerSetBit(P73_1A_HDMI_CTRL_1A, ~_BIT3, 0x00);

    // Set time interval form bus free to Read Request(4.7us~500us)
    ScalerSetByte(P73_1B_HDMI_CTRL_1B, (_BIT3 | _BIT0));

    // Enable HDMI 2.0 Function
    ScalerSetBit(P73_00_HDMI_CTRL_00, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), _BIT0);

    // Enable HDMI 2.0 SCDC Module
    ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

#else

    // Disable HDMI 2.0 Function
    ScalerSetBit(P73_00_HDMI_CTRL_00, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

    // Disable HDMI 2.0 SCDC Function
    ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, 0x00);
#endif

#endif // End of #if(_HDMI_MAC_RX4_SUPPORT == _ON)

    // Set HDCP DDC Debounce, TMDS Function
    ScalerSetBit(P73_AC_TMDS_Z0CC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Set Rx4 Port HDCP Address is 0x74
    ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_C2_PORT_PAGE73_HDCP_SLAVE_ADD, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3A);

    // Set HDCP Feature
#if(_HDMI_MAC_RX4_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, 0x81);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, 0x83);
#else
    ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, 0x81);
#endif

#else // Else of #if(_HDMI_MAC_RX4_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, 0x01);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, 0x03);
#else
    ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, 0x01);
#endif

#endif // End of #if(_HDMI_MAC_RX4_SUPPORT == _ON)

    // Set Starting offset address auto increase
    ScalerSetBit(P6D_26_HDCP_I2C_CTRL_0, ~_BIT4, 0x00);

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
    // Enable New Advance Cipher Mode
    ScalerSetBit(P73_C0_HDCP_CR, ~_BIT7, _BIT7);
#else
    // Disable HDMI 2.0 Function
    ScalerSetBit(P73_00_HDMI_CTRL_00, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

    // Enable New Advance Cipher Mode, Enable HDCP Module
    ScalerSetBit(P73_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));
#endif

    // Disable HDMI MAC Global Power Down
    ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT1, 0x00);

    // Enable MAC Input
    ScalerSetBit(P73_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTmdsMacRxBRSwap(enumInputPort);

    ScalerTmdsMacRxPNSwap(enumInputPort);

    // Auto switch to DVI when no signal
    ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT2, _BIT2);

    // Detect TMDS Format by Data Island Packet Preamble & Guard Band
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT1);

    // Enable TMDS MAC Error Correction
    ScalerSetBit(P73_B7_TMDS_UDC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

#if(_HDMI20_MAC_RX4_SUPPORT == _OFF)
    // Set HDMI/DVI switch to Auto Mode
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
#endif

    // Set 2x clk always from PLL
    ScalerSetBit(P73_B5_TMDS_UDC0, ~(_BIT6 | _BIT5), 0x00);

    // Turn Off 2x clk from PHY
    ScalerTmdsPhyRxCdr2xClkEnable(enumInputPort, _DISABLE);
}

//--------------------------------------------------
// Description  : Initialize TMDS Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4InterruptInitial(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    ScalerTmdsPhyRxPhyInitial(enumMappingPort);

    if(ScalerGetBit(P73_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        ScalerTmdsPhyRxFifoAutoResetEnable(enumMappingPort, _DISABLE);

        CLR_TMDS_MAC_RX4_PHY_SET();

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
        // clr Retry to Set Phy Flag
        CLR_TMDS_MAC_RX4_RETRY_SET_PHY();

        // Cancel WD Timer Event
        ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX4_TMDS_RETRY_SET_PHY);
#endif
    }

    // Choose Measure Clk to TMDS Clk
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT2), 0x00);

    // Set Freq. Reference Counter = 2000
    ScalerSetBit(P73_F6_HDMI_FREQDET_BOUND_H, ~(_BIT1 | _BIT0), _BIT0);

    // Set Online Measure Input Clock Divider = /2 (No Matter if Input Clock >300Mhz or <=300Mhz)
    ScalerSetBit(P73_E7_HDMI_FREQDET_OFFSET, ~_BIT6, _BIT6);

    // Settings for IRQ set PHY
    // Consider using table to fill all required initial settings
    // Set pre-set threshold (225MHz * 0.01 / 26.8KHz = 0x54)

    // Set TMDS Offset = 1/32
    ScalerSetBit(P73_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Set Upper Bound
    ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
    ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));

    // Set Lower Bound
    ScalerSetByte(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
    ScalerSetByte(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

    // Set Stable Time (0x3F = about 5ms)
    ScalerSetByte(P73_EC_HDMI_FREQDET_STABLE, 0x3F);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
    if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00)
#endif
    {
#if((_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON) || (_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON))
        if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NONE)
#endif
        {
            // Disable Freq. Unstable IRQ
            ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), 0x00);

            // Enable Freq. Stable IRQ
            ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        // Enable SCDC 0x20 Change IRQ
        ScalerSetBit(P73_26_HDMI_CTRL_26, ~_BIT4, _BIT4);
#endif

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
        // Clear IRQ Pending Flag
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_60_PORT_PAGE73_HDMI_INTCR, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
#endif

        SET_INTERRUPT_ENABLE_STATUS(_INT_TMDS, _ENABLE);

        // Start Freq. Detection
        ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);
    }
}

//--------------------------------------------------
// Description  : Measure Clk
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTmdsMacRx4MeasureClk(BYTE ucMeasureClk)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    BYTE ucDelayCount = 0;

    // Enable Rx_EN (Lane3)
    ScalerTmdsPhyRxSetRxEn(enumMappingPort, _ENABLE);

    // Disable Measure for Reset Measure Window
    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0);
    ScalerSetBit(P73_CA_HDMI_DP, ~(_BIT5 | _BIT3), 0x00);

    if(ucMeasureClk == _CLK_SOURCE_TMDS)
    {
        // Set ref clk = GDI clk & Switch TMDS Clk to be measure
        ScalerSetBit(P73_AD_TMDS_CPS, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
    }
    else
    {
        // Select CDR Clk to be measure from PHY
        ScalerTmdsPhyRxCdrMeasureClkSelect(enumMappingPort, ucMeasureClk);

        // Set ref clk = GDI clk & Switch CDR clk to be measure
        ScalerSetBit(P73_AD_TMDS_CPS, ~(_BIT6 | _BIT4), _BIT4);
    }

    // Start Measure
    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0);
    ScalerSetBit(P73_CA_HDMI_DP, ~(_BIT5 | _BIT3), _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US();

        ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0);
        if(ScalerGetBit(P73_CA_HDMI_DP, _BIT3) == 0x00)
        {
            break;
        }
    }

    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0);
    pData[0] = ScalerGetByte(P73_CA_HDMI_DP);

    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_29_PORT_PAGE73_HDMI_NTX1024TR1);
    pData[1] = ScalerGetByte(P73_CA_HDMI_DP);

    return ((WORD)(pData[0] & 0x07) << 8) | pData[1];
}

//--------------------------------------------------
// Description  : TMDS Power Saving Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4PowerSavingProc(void)
{
    ScalerTmdsMacRx4FreqDetectDisable();

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
    ScalerTmdsMacRx4ScrambleDetectDisable();
#endif

    // Switch TMDS Input/Output to Auto
    ScalerSetBit(P73_A6_TMDS_OUTCTL, ~_BIT7, _BIT7);
    ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

    // Set Freq. Stable Time: 5 times
    ScalerSetByte(P73_EC_HDMI_FREQDET_STABLE, 0x05);

    // Set Freq. Shift Offset to Max
    ScalerSetBit(P73_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Set Upper Bound
    ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
    ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));

    // Set Lower Bound
    ScalerSetByte(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
    ScalerSetByte(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
}

//--------------------------------------------------
// Description  : TMDS Switch Slave Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4SwitchHdcpSlaveAddr(void)
{
    ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_C2_PORT_PAGE73_HDCP_SLAVE_ADD, 0x7F);
}

//--------------------------------------------------
// Description  : On Line Check TMDS stability
// Input Value  : enumSourceType --> Source Type
// Output Value : True --> TMDS Stable
//                False --> TMDS Unstable
//--------------------------------------------------
bit ScalerTmdsMacRx4TMDSStableDetect(EnumSourceType enumSourceType)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    enumMappingPort = enumMappingPort;

    // CLR SCL/SDA Toggle Flag
    ScalerMcuDdcClrDdcDetectFlag(enumMappingPort);

#if(_HDMI_SUPPORT == _ON)
#if(_TMDS_MAC_RX4_CED_DEBUG == _ON)
    ScalerTmdsMacRx4CEDCheck(); // CED
#endif
#endif

    // Check Hpd Event happened
    if(GET_TMDS_MAC_RX4_HPD_RESET_TO_SEARCH_EVENT() == _TRUE)
    {
        DebugMessageRx4("HPD Toggle Event Occur!!", 0x00);
        CLR_TMDS_MAC_RX4_HPD_RESET_TO_SEARCH_EVENT();
        return _FALSE;
    }

    if(ScalerTmdsMacRx4CheckCDRStable(g_usTmdsMacRx4ClkCount) == _FALSE)
    {
        DebugMessageRx4("CDR Unstable!!", enumSourceType);
        return _FALSE;
    }

    // Check TMDS Clock Output Disable
    if(ScalerGetBit(P73_A6_TMDS_OUTCTL, _BIT3) == 0x00)
    {
        DebugMessageRx4("TMDS Clock Output has been disable", enumSourceType);
        return _FALSE;
    }

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

    if(ScalerGetBit(P73_00_HDMI_CTRL_00, _BIT0) == _BIT0)
    {
        if(enumSourceType == _SOURCE_HDMI)
        {
            if(GET_TMDS_MAC_RX4_HDMI20_FORMAT_RESET_WAITING() == _FALSE)
            {
                if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT3) != _BIT3)
                {
                    return _FALSE;
                }
                else
                {
                    if(ScalerGetBit(P73_CB_HDMI_SR, _BIT0) == 0x00)
                    {
                        DebugMessageRx4("TMDS Format Changed", enumSourceType);

                        return _FALSE;
                    }
                    else
                    {
                        // Toggle HW Format Detect Flag Reset
                        ScalerSetBit(P73_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                        ScalerSetBit(P73_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                        SET_TMDS_MAC_RX4_HDMI20_FORMAT_RESET_WAITING();

                        ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX4_HDMI2_FORMAT_RESET_WAIT);
                    }
                }
            }
        }
        else
        {
            if(ScalerGetBit(P73_CB_HDMI_SR, _BIT0) == _BIT0)
            {
                DebugMessageRx4("TMDS Format Changed", enumSourceType);
                return _FALSE;
            }
        }
    }
    else
#endif
    {
        if(enumSourceType == _SOURCE_HDMI)
        {
            if(ScalerGetBit(P73_CB_HDMI_SR, _BIT0) == 0x00)
            {
                DebugMessageRx4("TMDS Format Changed", enumSourceType);
                return _FALSE;
            }
        }
        else
        {
            if(ScalerGetBit(P73_CB_HDMI_SR, _BIT0) == _BIT0)
            {
                DebugMessageRx4("TMDS Format Changed", enumSourceType);
                return _FALSE;
            }
        }
    }

    if(GET_TMDS_MAC_RX4_Z0_ASSERTED() == _TRUE)
    {
        // Hdcp1.4 normal check
        if((ScalerGetBit(P73_C0_HDCP_CR, _BIT0) == _BIT0) && (GET_TMDS_MAC_RX4_BACKUP_HDCP_TYPE() == _HDCP_14))
        {
            if((ScalerGetBit(P73_A9_TMDS_ABC0, _BIT6) == _BIT6) && (!((ScalerGetBit(P73_AE_TMDS_RPS, _BIT1) == _BIT1) && (ScalerGetBit(P73_A9_TMDS_ABC0, _BIT5) == _BIT5))))
            {
                SET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT(_TMDS_MAC_RX_HPD_NORMAL);

                CLR_TMDS_MAC_RX4_Z0_ASSERTED();

                DebugMessageRx4("7. HDCP Abnormal !!!!!", 0);

                return _FALSE;
            }
            else if(((ScalerGetBit(P73_A9_TMDS_ABC0, _BIT7) == (_BIT7)) || (ScalerGetBit(P73_AE_TMDS_RPS, _BIT1) == (_BIT1))) && (ScalerGetBit(P73_A9_TMDS_ABC0, _BIT5) == (_BIT5)))
            {
                CLR_TMDS_MAC_RX4_Z0_ASSERTED();

                DebugMessageRx4("7. HDCP Normal", 0);
            }
        }
    }

#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_BED_ERROR() == _TRUE)
    {
        CLR_TMDS_MAC_RX4_BED_ERROR();

        DebugMessageRx4("BED Check Error", 0);

        return _FALSE;
    }
#endif

    if(enumSourceType == _SOURCE_DVI)
    {
        if(GET_TMDS_MAC_RX4_RGBHV_DETECTING() == _FALSE)
        {
            // TMDS Video Detected
#if(_DVI_DE_ONLY_SUPPORT == _OFF)
            if(ScalerTmdsMacRx4TMDSVideoDetect(_NOT_WAIT) != _TMDS_VIDEO_DATA_RGBHV)
#else
            if(ScalerTmdsMacRx4TMDSVideoDetect(_NOT_WAIT) == _TMDS_VIDEO_DATA_NONE)
#endif
            {
                DebugMessageRx4("TMDS Video format changed", enumSourceType);

                return _FALSE;
            }
        }
    }

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_HDMI)
    {
#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        if((GET_ADVANCED_HDR10_METADATA_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON) && (GET_ADVANCED_HDR10_INITIAL_READY() == _TRUE) && (GET_TMDS_MAC_RX4_ADVANCED_HDR10_DETECTING() == _FALSE))
        {
            bit bAdvancedHDR10VSIFReceive = GET_TMDS_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED();
            bit bAdvancedHDR10EMPReceive = _FALSE;

            if(bAdvancedHDR10VSIFReceive == _TRUE)
            {
                CLR_TMDS_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED();
            }
            else
            {
                // Clr HDR10+ data strucr if no received
                CLR_ADVANCED_HDR10_INFO_DATA();
                CLR_ADVANCED_HDR10_BACK_UP_INFO_DATA();
            }

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
            bAdvancedHDR10EMPReceive = GET_TMDS_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED();
            if(bAdvancedHDR10EMPReceive == _TRUE)
            {
                CLR_TMDS_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED();
            }
            else
            {
                CLR_ADVANCED_HDR10_DHDR_DATA();
            }
#endif

            if((bAdvancedHDR10VSIFReceive == _TRUE) || (bAdvancedHDR10EMPReceive == _TRUE))
            {
                // when continually receive, TimerEvent to detect HDR10+ (only VSIF/EMP -> No VSIF/EMP transition)
                ScalerTimerActiveTimerEvent(GET_ADVANCED_HDR10_METADATA_DETECT_TIME(), _SCALER_TIMER_EVENT_RX4_HDMI_ADVANCED_HDR10_DETECT);

                SET_TMDS_MAC_RX4_ADVANCED_HDR10_DETECTING();
            }
        }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
        if((GET_TMDS_MAC_RX4_DM_INFO_DETECTING() == _FALSE) && (ScalerDMGetMetadataSupport(enumMappingPort) == _TRUE))
        {
            if((GET_TMDS_MAC_RX4_DM_EMP_RECEIVED() == _TRUE) || (GET_TMDS_MAC_RX4_DM_VSIF_RECEIVED() == _TRUE))
            {
                CLR_TMDS_MAC_RX4_DM_EMP_RECEIVED();
                CLR_TMDS_MAC_RX4_DM_VSIF_RECEIVED();

                // when continually receive, TimerEvent to detect DM (only VSIF/EMP -> No VSIF/EMP transition)
                ScalerTimerActiveTimerEvent(100, _SCALER_TIMER_EVENT_RX4_HDMI_DM_DETECT);

                SET_TMDS_MAC_RX4_DM_INFO_DETECTING();
            }
            else
            {
                // case for DM packet -> no packet
            }
        }
#endif
#endif

        if(GET_TMDS_MAC_RX4_HDMI_PACKET_DETECTING() == _FALSE)
        {
            // HDMI Packet Detected
            ScalerTmdsMacRx4HdmiPacketDetect(_NOT_WAIT);

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
            // PRIORITY TOP to check 3D Video format if HDMI or HF VSIF from 1->0
            if((GET_TMDS_MAC_RX4_HDMI_VSIF_RECEIVED() == _FALSE) && (GET_TMDS_MAC_RX4_HF_VSIF_RECEIVED() == _FALSE))
            {
                CLR_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
            }

            if(GET_TMDS_MAC_RX4_HDMI_VSIF_RECEIVED() == _TRUE)
            {
                CLR_TMDS_MAC_RX4_HDMI_VSIF_RECEIVED();
            }
#endif

            if(GET_TMDS_MAC_RX4_HF_VSIF_RECEIVED() == _TRUE)
            {
                CLR_TMDS_MAC_RX4_HF_VSIF_RECEIVED();
            }
            else
            {
#if(_HDMI21_ALLM_SUPPORT == _ON)
                CLR_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();
#endif
            }

            if(GET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if(ScalerTmdsMacRx4HdmiColorInfoChanged() == _TRUE)
                {
                    DebugMessageRx4("Color Info Changed", enumSourceType);
                    return _FALSE;
                }

                if(ScalerTmdsMacRx4HdmiAviPixelRepInfoChanged() == _TRUE)
                {
                    DebugMessageRx4("Pixel Repetition Info Changed", enumSourceType);
                    return _FALSE;
                }
            }
            else
            {
                if(GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx4("HDMI Info Frame Not Received and not RGB", enumSourceType);
                    return _FALSE;
                }

#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
                if(GET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort) != _RGB_QUANTIZATION_RESERVED)
                {
                    DebugMessageRx4("No Quantization Range Specified", enumSourceType);
                    return _FALSE;
                }
#endif

                if(GET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
                {
                    DebugMessageRx4("Pixel Repetition Not Received and not Pixel repetition 0", enumSourceType);
                    return _FALSE;
                }
            }

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                if((ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_41_PORT_PAGE73_HDMI_VWDSR, _BIT0) == _BIT0) && (ScalerGetBit(P73_CC_HDMI_GPVS, _BIT0) == _BIT0))
                {
                    DebugMessageRx4("HDMI AVI info frame has changed", enumSourceType);
                    return _FALSE;
                }
            }

            if(GET_TMDS_MAC_RX4_HDMI_GCP_RECEIVED() == _TRUE)
            {
                if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) && (ScalerTmdsMacRx4HdmiGetColorDepth() != GET_COLOR_DEPTH(enumMappingPort)))
                {
                    DebugMessageRx4("Color Depth Has Changed", GET_COLOR_DEPTH(enumMappingPort));
                    return _FALSE;
                }
            }
            else
            {
                if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS))
                {
                    DebugMessageRx4("HDMI GCP PACKET Not Received and not 8 bit", enumSourceType);
                    return _FALSE;
                }
            }

#if(_HDMI_FORCE_FREESYNC_SUPPORT == _OFF)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if((bit)GET_HDMI_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) != ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort))
                {
                    DebugMessageRx4("HDMI Freesync Status Change", ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort));
                    return _FALSE;
                }
            }
            else
            {
                if(ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort) == _TRUE)
                {
                    DebugMessageRx4("HDMI Freesync Status Change", ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort));
                    return _FALSE;
                }
            }
#endif
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
            if(GET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED() != ScalerTmdsMacRxGetFreesyncReplayProc(enumMappingPort))
            {
                DebugMessageRx4("AMD SPD Infoframe Status Change", GET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED());
                return _FALSE;
            }
#endif
        }

#if(_HDMI_FORCE_VRR_SUPPORT == _OFF)
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
        if(GET_TMDS_MAC_RX4_EMP_DETECTING() == _FALSE)
        {
            // EMP Packet Detect
            ScalerTmdsMacRx4EmpPacketDetect(_NOT_WAIT);

#if(_HDMI21_VRR_SUPPORT == _ON)
            if((GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG() == _TRUE) && (GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE))
            {
                DebugMessageRx4("Tmds Rx4: VTEM from NA(or MLDS) to received", 0x00);
                CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG();

                return _FALSE;
            }
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
            {
                // FVA factor change
                if(GET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR() != (ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_FVA_FACTOR_M1) + 1))
                {
                    return _FALSE;
                }
            }
#endif
        }
#endif
#endif
    }
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)

    if(GET_TMDS_MAC_RX4_TOGGLE_Z0() == _TRUE)
    {
        SET_TMDS_MAC_RX4_TOGGLE_Z0_EVENT();

        return _FALSE;
    }

#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(GET_TMDS_MAC_RX4_PS_WAKEUP() == _TRUE)
        {
            CLR_TMDS_MAC_RX4_PS_WAKEUP();

            SET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT(_TMDS_MAC_RX_HPD_EIZO_PS_WAKEUP);

            return _FALSE;
        }
    }
    else
    {
        CLR_TMDS_MAC_RX4_PS_WAKEUP();
    }

#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : TMDS Freq Detect clock gating
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4FreqDetectClkGating(void)
{
    // HDMI Clock Gating to Measure Block
    ScalerSetBit(P73_E1_AUX_PS_REPLY, ~_BIT7, _BIT7);
}

#if(_HDMI_MAC_RX4_SUPPORT == _ON)

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

#if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS HPD IRQ Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4HDMI2HPDRRIRQEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set HPD Debounce = 700 Clock Cycle
        // Set HPD IRQ Detect Rising to Falling Edge IRQ
        ScalerSetBit(P73_23_HDMI_CTRL_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT5 | _BIT4 | _BIT3 | _BIT1));

        // Enable HDMI HPD IRQ Enable
        ScalerSetBit(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);

        // Write 1 Clear Read Request
        ScalerSetByte(P73_25_HDMI_CTRL_25, _BIT3);

        // Enable HDMI 2.0 SCDC IIC Module
        ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

        // Clear HDMI 2.0 Read Request Enable
        CLR_TMDS_MAC_RX4_HDMI20_RR_ENABLE();

        // Enable HDMI 2.0 Read Request Enable Detect IRQ
        ScalerSetBit(P73_26_HDMI_CTRL_26, ~_BIT3, _BIT3);
    }
    else
    {
        // Write 1 Clear Read Request
        ScalerSetByte(P73_25_HDMI_CTRL_25, _BIT3);

        // Clear HDMI 2.0 Read Request Enable
        CLR_TMDS_MAC_RX4_HDMI20_RR_ENABLE();

        // Disable HDMI 2.0 Read Request Enable Detect IRQ
        ScalerSetBit(P73_26_HDMI_CTRL_26, ~_BIT3, 0x00);
    }
}
#endif


//--------------------------------------------------
// Description  : Scramble Status Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4ScrambleStatusReset(void)
{
    // Set Scramble Detect Manual Mode
    ScalerSetBit(P73_38_HDMI_CTRL_38, ~(_BIT4 | _BIT2 | _BIT1), 0x00);

    // Disable Scrambling Status
    ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_21_PORT_PAGE73_HDMI_SCDC_21, ~_BIT0, 0x00);

    // Clear Scrambling Detection Flag
    ScalerSetBit(P73_01_HDMI_CTRL_01, ~_BIT3, _BIT3);

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI2_SCRAMBLE_DETECT_TIMEOUT);
}

//--------------------------------------------------
// Description  : Scramble Detect timeout event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4ScrambleDetectTimeoutTimerEvent(void)
{
    // Set Scramble Detect Auto Mode
    ScalerSetBit(P73_38_HDMI_CTRL_38, ~(_BIT4 | _BIT2 | _BIT1), _BIT4);

    ScalerTmdsMacRx4ScrambleDetectDisable();
}

//--------------------------------------------------
// Description  : TMDS Scramble Detection IRQ Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4ScrambleDetectDisable(void)
{
    // Disable SCDC 0x20 Change IRQ
    ScalerSetBit(P73_26_HDMI_CTRL_26, ~_BIT4, 0x00);
}

//--------------------------------------------------
// Description  : TMDS Set SCDC Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4SetScdcInfo(void)
{
    // Set SCDC Info
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D0_PORT_PAGE73_HDMI_SCDC_D0, g_stTmdsMacRxScdcInfoSet.ucManufactureOuiL);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D1_PORT_PAGE73_HDMI_SCDC_D1, g_stTmdsMacRxScdcInfoSet.ucManufactureOuiM);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D2_PORT_PAGE73_HDMI_SCDC_D2, g_stTmdsMacRxScdcInfoSet.ucManufactureOuiH);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D3_PORT_PAGE73_HDMI_SCDC_D3, g_stTmdsMacRxScdcInfoSet.pucIdstring[0]);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D4_PORT_PAGE73_HDMI_SCDC_D4, g_stTmdsMacRxScdcInfoSet.pucIdstring[1]);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D5_PORT_PAGE73_HDMI_SCDC_D5, g_stTmdsMacRxScdcInfoSet.pucIdstring[2]);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D6_PORT_PAGE73_HDMI_SCDC_D6, g_stTmdsMacRxScdcInfoSet.pucIdstring[3]);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D7_PORT_PAGE73_HDMI_SCDC_D7, g_stTmdsMacRxScdcInfoSet.pucIdstring[4]);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D8_PORT_PAGE73_HDMI_SCDC_D8, g_stTmdsMacRxScdcInfoSet.pucIdstring[5]);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_D9_PORT_PAGE73_HDMI_SCDC_D9, g_stTmdsMacRxScdcInfoSet.pucIdstring[6]);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_DA_PORT_PAGE73_HDMI_SCDC_DA, g_stTmdsMacRxScdcInfoSet.pucIdstring[7]);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_DB_PORT_PAGE73_HDMI_SCDC_DB, g_stTmdsMacRxScdcInfoSet.ucHdmiHwVersion);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_DC_PORT_PAGE73_HDMI_SCDC_DC, g_stTmdsMacRxScdcInfoSet.ucHdmiFwVersionMajor);
    ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_DD_PORT_PAGE73_HDMI_SCDC_DD, g_stTmdsMacRxScdcInfoSet.ucHdmiFwVersionMinor);

    DebugMessageRx4("Set Rx4 SCDC Version Info", 0x00);
}

//--------------------------------------------------
// Description  : TMDS Set CED Lock Transition
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4SetCedLockTransition(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Clear CED Lock Transition Flag
        ScalerSetBit(P73_17_HDMI_CTRL_17, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Enable Character Error Detction Function Lock Transition IRQ
        ScalerSetBit(P73_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Enable Character Error Detection Function & Valid Flag
        ScalerSetBit(P73_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
    }
    else
    {
        // Disable CED Function
        ScalerSetBit(P73_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

        // Pop Up CED Error For Clear Error Counter
        ScalerSetBit(P73_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

        // Disable CED Lock Transition IRQ & Flag
        ScalerSetBit(P73_17_HDMI_CTRL_17, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P73_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Set AMD AUPI SCDC Info
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4SetAmdAupiScdcInfo(bit bEnable)
{
    if(GET_FREESYNC_HDMI_AUPI_INFO() != _TRUE)
    {
        return;
    }

    if(bEnable == _ENABLE)
    {
        // Set SCDC Info
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E0_PORT_PAGE73_HDMI_SCDC_E0, g_stDrrHdmiAmdAupiInfo.ucPanelManufactureIdL);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E1_PORT_PAGE73_HDMI_SCDC_E1, g_stDrrHdmiAmdAupiInfo.ucPanelManufactureIdM);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E2_PORT_PAGE73_HDMI_SCDC_E2, g_stDrrHdmiAmdAupiInfo.ucPanelIdL);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E3_PORT_PAGE73_HDMI_SCDC_E3, g_stDrrHdmiAmdAupiInfo.ucPanelIdM);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E4_PORT_PAGE73_HDMI_SCDC_E4, g_stDrrHdmiAmdAupiInfo.ucFwCheckSumL);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E5_PORT_PAGE73_HDMI_SCDC_E5, g_stDrrHdmiAmdAupiInfo.ucFwCheckSumM);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E6_PORT_PAGE73_HDMI_SCDC_E6, g_stDrrHdmiAmdAupiInfo.ucScalerDeviceIdL);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E7_PORT_PAGE73_HDMI_SCDC_E7, g_stDrrHdmiAmdAupiInfo.ucScalerDeviceIdM);

        DebugMessageRx4("Set Rx4 AMD AUPI SCDC Info", 0x00);
    }
    else
    {
        // Set SCDC Info
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E0_PORT_PAGE73_HDMI_SCDC_E0, 0x00);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E1_PORT_PAGE73_HDMI_SCDC_E1, 0x00);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E2_PORT_PAGE73_HDMI_SCDC_E2, 0x00);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E3_PORT_PAGE73_HDMI_SCDC_E3, 0x00);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E4_PORT_PAGE73_HDMI_SCDC_E4, 0x00);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E5_PORT_PAGE73_HDMI_SCDC_E5, 0x00);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E6_PORT_PAGE73_HDMI_SCDC_E6, 0x00);
        ScalerSetDataPortByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_E7_PORT_PAGE73_HDMI_SCDC_E7, 0x00);
    }
}
#endif
#endif
#endif // End of #if(_HDMI_MAC_RX4_SUPPORT == _ON)

#if((_HDMI_MAC_RX4_SUPPORT == _ON) || (_3DDI_FUNCTION == _ON))
#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check seamless video format that is avaiable for SRC
// Input Value  : None
// Output Value : _TRUE(seamless case)
//--------------------------------------------------
bit ScalerTmdsMacRx4CheckSeamlessCondition(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    switch(GET_COLOR_SPACE(enumMappingPort))
    {
        case _COLOR_SPACE_RGB:
        case _COLOR_SPACE_YCBCR444:

            // check GCP CD field to ensure 8bpc
            if(ScalerGetDataPortBit(P73_D0_HDMI_PSAP2, 0x42, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) < 0x05)
            {
                return _TRUE;
            }

            break;

        case _COLOR_SPACE_YCBCR422:

            return _TRUE;
            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : seamless fast setting
// Input Value  : NA
// Output Value : Source DVI --> DVI Format
//--------------------------------------------------
EnumSourceType ScalerTmdsMacRx4SeamlessReset(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    EnumSourceType enumSourceType = _SOURCE_NONE;

    BYTE ucTMDSVideoDataType = _TMDS_VIDEO_DATA_NONE;

    DebugMessageRx4("===== TMDS Rx4 SDR_DM Seamless flow =====", 0x00);

    // reset for AVI IF WD
    ScalerTmdsMacRx4HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

    if(GET_TMDS_MAC_RX4_PHY_SET() == _TRUE)
    {
        // Clear RGBHV Flag
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // w1c interface flag
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        // Disable Reset HDMI/DVI Format
        ScalerSetBit(P73_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);
#endif

        if(ScalerTmdsMacRx4FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx4("Format Detect HDMI", 0x00);

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, _BIT1);
#endif
            enumSourceType = _SOURCE_HDMI;
        }
        else
        {
#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, 0x00);
#endif
            enumSourceType = _SOURCE_DVI;

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            ScalerTmdsMacRx4RoundRobinIrqEnable(_DISABLE);
#endif
        }

        ucTMDSVideoDataType = ScalerTmdsMacRx4TMDSVideoDetect(_WAIT);

        if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
        {
            DebugMessageRx4("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(enumSourceType == _SOURCE_DVI)
            {
                // Enable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
            }
            else
            {
                return _SOURCE_NONE;
            }
#else
            return _SOURCE_NONE;
#endif
        }
        else if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_RGBHV)
        {
            // Enable DE Only Mode
            ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
        }
        else
        {
            return _SOURCE_NONE;
        }

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        if(enumSourceType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTmdsMacRx4HdmiPacketDetect(_NOT_WAIT);

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
            // Get EMP packet
            ScalerTmdsMacRx4EmpPacketDetect(_NOT_WAIT);
#endif
            ScalerTmdsMacRx4HdmiVideoSetting();

            SET_COLOR_DEPTH(enumMappingPort, ScalerTmdsMacRx4HdmiGetColorDepth());

            // Precheck for (422, 12bpc) <-> (RGB, 8bpc) case
            if(ScalerTmdsMacRx4CheckSeamlessCondition() == _FALSE)
            {
                DebugMessageRx4("TMDS Rx4: NOT Seamless condition", 0x00);
                return _SOURCE_NONE;
            }

            // RGB/YUV444 10/12bits use PLL to generate pixel clk
            // YUV420 8/10/12bits use PLL to generate pixel clk
            // 3DDI 8/10/12bits use PLL to generate pixel clk
            if(((GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422)) ||
               (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420))
            {
                // Backup Input Pixel clk (no DC impact)
                WORD usBackupInputPixelClk = ScalerTmdsMacRxGetInputPixel(enumMappingPort);

                DebugMessageRx4("Color Depth", GET_COLOR_DEPTH(enumMappingPort));

                ScalerTmdsMacRxSetInputPixel(enumMappingPort, (usBackupInputPixelClk << 3) / GET_COLOR_DEPTH(enumMappingPort));

                // Disable Deep color FIFO Output
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, 0x00);

                if(ScalerTmdsMacRx4HdmiDeepColorProc(g_usTmdsMacRx4ClkCount) == _FALSE)
                {
                    // Restore Input Pixel clk
                    ScalerTmdsMacRxSetInputPixel(enumMappingPort, usBackupInputPixelClk);

                    // Enable Deep color FIFO Output
                    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

                    return _SOURCE_NONE;
                }

                // Switch PLL before turn on Deep color block
                if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)
                {
                    // If Pixel clk > _HW_HDMI_VIDEO_PLL_CLK_LIMIT --> Video PLL = 1x clk for Mac & 420 mudule (use Double Pixel mode)
                    if((ScalerTmdsMacRxGetInputPixel(enumMappingPort) * 2) > _HW_HDMI_VIDEO_PLL_CLK_LIMIT)
                    {
                        // HDMI output Div2 Disable
                        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, 0x00);
                    }
                    else
                    {
                        // HDMI Output Div2 Enable
                        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, _BIT7);
                    }
                }
                else
                {
                    // HDMI Output Div2 Disable
                    ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, 0x00);
                }

                // Turn On Deep Color Block and PLL
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block, before switch PLL
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);

                // HDMI Output Div2 Disable
                ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, 0x00);

                // Power down PLL
                ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
                ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);
            }
        }
#endif

        // Enable Video Output
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        return enumSourceType;
    }

    return _SOURCE_NONE;
}
#endif

//--------------------------------------------------
// Description  : Set Deep Color PLL
// Input Value  : usTMDSClkCount, ucColorDepth
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRx4HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    DWORD ulTMDSClkValue = 0;
    WORD usVCOFreq = 0;
    BYTE ucPreDiv = 0;
    BYTE ucNcode = 0;
    BYTE ucOutputDiv = 0;

#if(((_HDMI20_MAC_RX4_SUPPORT == _ON) && (_HDMI20_YCBCR420_SUPPORT == _ON)) || (_3DDI_FUNCTION == _ON))
    BYTE ucRatio = 1;
#endif

    enumMappingPort = enumMappingPort;

    if(usTMDSClkCount == 0)
    {
        return _FALSE;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Fin = TMDS_clk
    // Fref = Fin / Pre-Div
    // Fvco = Fin * N-code, F-code = 0
    // Freq = Fvco / Output-Div
    //
    // Restriction
    // A. 14.318MHz < Fin < 600MHz
    // B. 270MHz < Fvco < _HW_HDMI_VIDEO_PLL_CLK_LIMIT
    // C. 14MHz < Fref < 28MHz
    // D. YCbCr 420, Ratio = 2, other case Ratio = 1
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // If Measure Divider = /2 then TMDS_CLK x 2, unit:kHz
    if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0, _BIT6) == _BIT6)
    {
        ulTMDSClkValue = (DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1024 * 2 / usTMDSClkCount;
    }
    else
    {
        ulTMDSClkValue = (DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1024 / usTMDSClkCount;
    }

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

    if(GET_TMDS_MAC_RX4_HIGH_SPEED_MODE() == _TRUE)
    {
        ulTMDSClkValue = (ulTMDSClkValue << 2);
    }

#if(_HDMI20_YCBCR420_SUPPORT == _ON)
    if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)
    {
        ucRatio = 2;
    }
#endif

#endif

#if(_3DDI_FUNCTION == _ON)
    // Check 2x clk need?
    if(ScalerTmdsMacRx4GetInterlace3ddiAvailable() == _TRUE)
    {
        ucRatio = 2;
    }
#endif

    DebugMessageRx4("TMDS clk", ulTMDSClkValue);
    DebugMessageRx4("Color Depth", ucColorDepth);
    DebugMessageRx4("usTMDSClkCount", usTMDSClkCount);

    ///////////////////////////
    // Calculate Pre-Divider //
    // 10bit: div2,4,5,10,20 //
    // 12bit: div2,3,6,12,24 //
    // 16bit: div2,4,8,16,32 //
    ///////////////////////////

    // TMDS_CLK : 25~600MHz
    // 14MHz <= Fref = TMDS_CLK / Pre-Div <= 28MHz
    if((ucColorDepth == _COLOR_DEPTH_10_BITS) || (ucColorDepth == _COLOR_DEPTH_16_BITS))
    {
        if((ulTMDSClkValue / (ucColorDepth * 4)) > 14000)
        {
            ucPreDiv = ucColorDepth * 4;
        }
        else if((ulTMDSClkValue / (ucColorDepth * 2)) > 14000)
        {
            ucPreDiv = ucColorDepth * 2;
        }
        else if((ulTMDSClkValue / ucColorDepth) > 14000)
        {
            ucPreDiv = ucColorDepth;
        }
        else if((ulTMDSClkValue / (ucColorDepth / 2)) > 14000)
        {
            ucPreDiv = ucColorDepth / 2;
        }
        else if((ulTMDSClkValue / 4) > 14000)
        {
            ucPreDiv = 4;
        }
        else if((ulTMDSClkValue / 2) > 14000)
        {
            ucPreDiv = 2;
        }
        else if(ulTMDSClkValue > 14000)
        {
            ucPreDiv = 1;
        }
    }
    else if(ucColorDepth == _COLOR_DEPTH_12_BITS)
    {
        if((ulTMDSClkValue / (ucColorDepth * 2)) > 14000)
        {
            ucPreDiv = ucColorDepth * 2;
        }
        else if((ulTMDSClkValue / ucColorDepth) > 14000)
        {
            ucPreDiv = ucColorDepth;
        }
        else if((ulTMDSClkValue / (ucColorDepth / 2)) > 14000)
        {
            ucPreDiv = ucColorDepth / 2;
        }
        else if((ulTMDSClkValue / 3) > 14000)
        {
            ucPreDiv = 3;
        }
        else if((ulTMDSClkValue / 2) > 14000)
        {
            ucPreDiv = 2;
        }
        else if(ulTMDSClkValue > 14000)
        {
            ucPreDiv = 1;
        }
    }
    else if(ucColorDepth == _COLOR_DEPTH_8_BITS)
    {
        if((ulTMDSClkValue / (ucColorDepth * 4)) > 14000)
        {
            ucPreDiv = ucColorDepth * 4;
        }
        else if((ulTMDSClkValue / (ucColorDepth * 2)) > 14000)
        {
            ucPreDiv = ucColorDepth * 2;
        }
        else if((ulTMDSClkValue / ucColorDepth) > 14000)
        {
            ucPreDiv = ucColorDepth;
        }
        else if((ulTMDSClkValue / (ucColorDepth / 2)) > 14000)
        {
            ucPreDiv = ucColorDepth / 2;
        }
        else if((ulTMDSClkValue / 2) > 14000)
        {
            ucPreDiv = 2;
        }
        else if(ulTMDSClkValue > 14000)
        {
            ucPreDiv = 1;
        }
    }

    DebugMessageRx4("Pre-Divider", ucPreDiv);

    if(ucPreDiv == 0)
    {
        return _FALSE;
    }


    //////////////////////
    // Calculate N Code //
    //////////////////////
    if((ulTMDSClkValue / ucPreDiv) >= 20000)
    {
        ucNcode = 16;
    }
    else
    {
        ucNcode = 32;
    }

    DebugMessageRx4("N code", ucNcode);


    //////////////////////////////
    // Calculate Output Divider //
    //////////////////////////////
#if(((_HDMI20_MAC_RX4_SUPPORT == _ON) && (_HDMI20_YCBCR420_SUPPORT == _ON)) || (_3DDI_FUNCTION == _ON))
    // if pixel clk over _HW_HDMI_VIDEO_PLL_CLK_LIMIT, set PLL = 1x clk, else set PLL = 2x clk
    // ulTMDSClkValue unit is TMDS clk(KHz), _HW_HDMI_VIDEO_PLL_CLK_LIMIT unit is pixel clk(0.1 MHz)
    if(((ulTMDSClkValue * 8 / ucColorDepth) * 2 / 100) > _HW_HDMI_VIDEO_PLL_CLK_LIMIT)
    {
        ucOutputDiv = ucNcode / 8 * ucColorDepth / ucPreDiv;
    }
    else
    {
        ucOutputDiv = ucNcode / 8 * ucColorDepth / ucPreDiv / ucRatio;

        if(ucOutputDiv == 0)
        {
            ucOutputDiv = 1;
            ucNcode *= 2;
            DebugMessageRx4("Modify N x2 due to OutputDiv 0", ucNcode);
        }
    }
#else
    ucOutputDiv = ucNcode / 8 * ucColorDepth / ucPreDiv;
#endif

    DebugMessageRx4("Outpur Divider", ucOutputDiv);

    if(ucOutputDiv == 0)
    {
        return _FALSE;
    }


    //////////////
    // Set DPLL //
    //////////////
    // PLL Input Clock select to HDMI2.0_VCLK, [7:6] = 11
    ScalerSetBit(P69_C2_PLL_IN_CONTROL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Interger PLL
    ScalerSetBit(P69_C6_M2PLL_1, ~_BIT2, _BIT2);

    // Bypass PI
    ScalerSetBit(P6D_BC_SDM_0, ~_BIT7, _BIT7);

    usVCOFreq = (WORD)(ulTMDSClkValue / ucPreDiv * ucNcode / 100);

    // Set Ncode clamp, Max/Min = +/- 2 code
    if(ucNcode == 16)
    {
        // Max = 16 + 2 - 2(reg = actual Ncode - 2), Min = 16 - 2 - 2
        ScalerSetByte(P6D_B6_N_F_MAX, 16);
        ScalerSetByte(P6D_B7_N_F_MIN, 12);
    }
    else
    {
        // Max = 32 + 2 - 2(reg = actual Ncode - 2), Min = 32 - 2 - 2
        ScalerSetByte(P6D_B6_N_F_MAX, 32);
        ScalerSetByte(P6D_B7_N_F_MIN, 28);
    }

    ScalerTmdsMacRx4DPLLOffProc(usVCOFreq, ucPreDiv, ucOutputDiv, ucNcode);

    ScalerTmdsMacRx4DPLLOnProc(ucNcode);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Deep Color PLL On COntrol.
// Input Value  : ucNcode
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx4DPLLOnProc(BYTE ucNcode)
{
    // Power On DPLL
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, 0x00);
    DELAY_XUS(200);

    // Set VCO/4 Enable
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, _BIT7);

    // Set N.F Code
    ScalerSetByte(P6D_B2_N_F_CODE_1, (ucNcode - 2));
    ScalerSetByte(P6D_B3_N_F_CODE_2, 0x00);
    ScalerSetByte(P6D_B4_N_F_CODE_3, 0x00);
    ScalerSetByte(P6D_B5_N_F_CODE_4, 0x00);

    // Set N.F Double Buffer
    ScalerSetBit(P6D_B1_N_F_CODE_0, ~_BIT0, _BIT0);

    // Wait for DPLL Stable (300us)
    DELAY_XUS(300);
}
#endif // End of #if((_HDMI_MAC_RX4_SUPPORT == _ON) || (_3DDI_FUNCTION == _ON))

#if((_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_1_4) || (_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_0))
//--------------------------------------------------
// Description  : TMDS Port RDC test 1 lane mode
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerTmdsMacRx4RDCCheck(void)
{
#if(_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_0) // HDMI 2.0 setting
    // DVI Mode
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3), _BIT3);

    // Seed
    ScalerSetByte(P73_04_HDMI_CTRL_04, 0x00);
    ScalerSetByte(P73_05_HDMI_CTRL_05, 0x00);
    ScalerSetByte(P73_06_HDMI_CTRL_06, 0x00);
    ScalerSetByte(P73_07_HDMI_CTRL_07, 0x00);

#endif
    while(1)
    {
        ScalerDebug();
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
EnumSourceType ScalerTmdsMacRx4TMDSScanInputPort(EnumPortType enumPortType)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    EnumSourceType enumSourceType = _SOURCE_NONE;

    BYTE ucTMDSVideoDataType = _TMDS_VIDEO_DATA_NONE;

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
    WORD usBackupInputPixelClk = 0;  // unit: 0.1 MHz
#endif

#if(_HDMI_FORCE_FREESYNC_SUPPORT == _ON)
    bit bFreeSyncReceive = _TRUE;
#endif

    enumPortType = enumPortType;

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
    if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE)
#else
    if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) || (GET_HDMI_MAC_RX4_INTERFACE_SWITCHING() == _TRUE))
#endif
    {
        return _SOURCE_NONE;
    }

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    if((ScalerGetBit(P6D_40_HDCP_2PX_ENCRYP_STS, (_BIT7 | _BIT6)) == _BIT7) && (GET_TMDS_HDCP2_RX4_AUTHENTICATION_DONE() != _TRUE) && (GET_TMDS_MAC_RX4_BACKUP_HDCP_TYPE() == _HDCP_22))
    {
        SET_TMDS_MAC_RX4_BACKUP_HDCP_TYPE(_HDCP_NONE);

        // Set RxStatus REAUTH_REQ
        ScalerSetBit(P6D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
        ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_71_PORT_PAGE73_HDCP2_STATUS2, ~_BIT3, _BIT3);
        ScalerSetBit(P6D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

        // Active HDCP 2.2 Re-Auth Timer Event for HPD Trigger Event Usage
        ScalerTimerActiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_RX4_HDCP2_REAUTH);

        return _SOURCE_NONE;
    }
#endif

    if(GET_TMDS_MAC_RX4_PHY_SET() == _TRUE)
    {
        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

#if((_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_1_4) || (_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_0))
        ScalerTmdsMacRx4RDCCheck();
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        if((ScalerTmdsMacRx4CheckCDRStable(g_usTmdsMacRx4ClkCount) == _FALSE) || (ScalerTmdsPhyRxCheckDFE(enumMappingPort) == _FALSE) || (ScalerTmdsMacRx4TMDSVideoDetect(_WAIT) == _TMDS_VIDEO_DATA_NONE))
#else
        if((ScalerTmdsMacRx4CheckCDRStable(g_usTmdsMacRx4ClkCount) == _FALSE) || (ScalerTmdsPhyRxCheckDFE(enumMappingPort) == _FALSE))
#endif
        {
            // Set Upper Bound
            ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
            ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));

            // Set Lower Bound
            ScalerSetByte(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Set Stable Time (0x3F = about 5ms)
            ScalerSetByte(P73_EC_HDMI_FREQDET_STABLE, 0x3F);

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

            if((GET_TMDS_MAC_RX4_HIGH_SPEED_MODE() == _FALSE) && ((ScalerTmdsMacRxGetInputPixel(enumMappingPort) >= 850) && (ScalerTmdsMacRxGetInputPixel(enumMappingPort) <= 1500))) // HDMI mode
            {
                DebugMessageRx4("TMDS Rx4 First 1:10 set phy not success", 1);

                SET_TMDS_MAC_RX4_HIGH_SPEED_MODE();
            }
            else if(ScalerTmdsMacRxGetInputPixel(enumMappingPort) >= 3400)
            {
                CLR_TMDS_MAC_RX4_HIGH_SPEED_MODE();
            }
#endif
            ScalerTmdsPhyRxFifoAutoResetEnable(enumMappingPort, _DISABLE);

            CLR_TMDS_MAC_RX4_PHY_SET();

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
            // clr Retry to Set Phy Flag
            CLR_TMDS_MAC_RX4_RETRY_SET_PHY();

            // Cancel WD Timer Event
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX4_TMDS_RETRY_SET_PHY);
#endif

            // Disable Freq. Unstable IRQ
            ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), 0x00);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00)
#endif
            {
                // Reset Freq. Detect Counter
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), 0x00);
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

                // Enable Freq. Stable IRQ
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            }

            return _SOURCE_NONE;
        }

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        if(ScalerGetBit(P73_38_HDMI_CTRL_38, _BIT4) == 0x00)
        {
            ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_RX4_HDMI2_SCRAMBLE_DETECT_TIMEOUT);
        }
#endif

        // Clear RGBHV Flag
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Info Packet SRAM (PKT related reg NEED TO BE SET after reset Packet SRAM)
        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Reset All Pkt Received Flag (VTEM & RSV)
        ScalerTmdsMacRx4ResetAllPacketReceiveStatus();

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        ScalerTmdsMacRx4RoundRobinIrqEnable(_ENABLE);
#endif

        // w1c interface flag
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        // Clear DRR flag
        ScalerTmdsMacRxSetFreesyncProc(enumMappingPort, _DISABLE);
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        // Clear Freesync replay flag
        ScalerTmdsMacRxSetFreesyncReplayProc(enumMappingPort, _DISABLE);

        // Set Freesync Replay disable
        ScalerSetBit(P73_D6_HDMI_SHDR_IE, ~_BIT4, 0x00);
#endif

        DebugMessageRx4("9. Freq Check Pass => Pixel Clock", ScalerTmdsMacRxGetInputPixel(enumMappingPort));

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)

        // Disable Reset HDMI/DVI Format
        ScalerSetBit(P73_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

        DebugMessageRx4("HDMI 2.0 Error Boundary set High Byte", ScalerGetByte(P73_14_HDMI_CTRL_14));
        DebugMessageRx4("HDMI 2.0 Error Boundary set Low Byte", ScalerGetByte(P73_15_HDMI_CTRL_15));
#endif

        if(ScalerTmdsMacRx4FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx4("Format Detect HDMI", 0x00);

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, _BIT1);
#endif
            enumSourceType = _SOURCE_HDMI;
        }
        else
        {
#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, 0x00);
#endif
            enumSourceType = _SOURCE_DVI;

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            ScalerTmdsMacRx4RoundRobinIrqEnable(_DISABLE);
#endif
        }

        ucTMDSVideoDataType = ScalerTmdsMacRx4TMDSVideoDetect(_WAIT);

        if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
        {
            DebugMessageRx4("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(enumSourceType == _SOURCE_DVI)
            {
                // Enable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
            }
            else
            {
                return _SOURCE_NONE;
            }
#else
            return _SOURCE_NONE;
#endif
        }
        else if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_RGBHV)
        {
            // Enable DE Only Mode
            ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
        }
        else
        {
            return _SOURCE_NONE;
        }

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        if(enumSourceType == _SOURCE_HDMI)
        {
            bit bInterlace3ddi = _FALSE;

            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTmdsMacRx4HdmiPacketDetect(_WAIT);

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
            // Active EMP SRAM
            ScalerTmdsMacRx4EmpSramSetting(_ENABLE);
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
            // Get EMP packet
            ScalerTmdsMacRx4EmpPacketDetect(_WAIT);
#endif

            if((ScalerTmdsPhyRxCheckDcdr(enumMappingPort) == _TRUE) && (ScalerTmdsMacRx4BchErrorCheck(enumMappingPort) == _TRUE))
            {
                return _SOURCE_NONE;
            }

            ScalerTmdsMacRx4HdmiVideoSetting();

            SET_COLOR_DEPTH(enumMappingPort, ScalerTmdsMacRx4HdmiGetColorDepth());

#if(_3DDI_FUNCTION == _ON)
            if(ScalerTmdsMacRx4GetInterlace3ddiAvailable() == _TRUE)
            {
                bInterlace3ddi = _TRUE;

                // Disable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
            }
#endif

            // Backup Input Pixel clk (no DC impact)
            usBackupInputPixelClk = ScalerTmdsMacRxGetInputPixel(enumMappingPort);

            // RGB/YUV444 10/12bits use PLL to generate pixel clk
            // YUV420 8/10/12bits use PLL to generate pixel clk
            // 3DDI 8/10/12bits use PLL to generate pixel clk
            if(((GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422)) ||
               (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (bInterlace3ddi == _TRUE))
            {
                DebugMessageRx4("Color Depth", GET_COLOR_DEPTH(enumMappingPort));

                ScalerTmdsMacRxSetInputPixel(enumMappingPort, (usBackupInputPixelClk << 3) / GET_COLOR_DEPTH(enumMappingPort));

                // Disable Deep color FIFO Output
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, 0x00);

                if(ScalerTmdsMacRx4HdmiDeepColorProc(g_usTmdsMacRx4ClkCount) == _FALSE)
                {
                    // Restore Input Pixel clk
                    ScalerTmdsMacRxSetInputPixel(enumMappingPort, usBackupInputPixelClk);

                    // Enable Deep color FIFO Output
                    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

                    return _SOURCE_NONE;
                }

                // Switch PLL before turn on Deep color block
                if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (bInterlace3ddi == _TRUE))
                {
                    // If Pixel clk > _HW_HDMI_VIDEO_PLL_CLK_LIMIT --> Video PLL = 1x clk for Mac & 420 mudule (use Double Pixel mode)
                    if((ScalerTmdsMacRxGetInputPixel(enumMappingPort) * 2) > _HW_HDMI_VIDEO_PLL_CLK_LIMIT)
                    {
                        // HDMI output Div2 Disable
                        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, 0x00);
                    }
                    else
                    {
                        // HDMI Output Div2 Enable
                        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, _BIT7);
                    }
                }
                else
                {
                    // HDMI Output Div2 Disable
                    ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, 0x00);
                }

                // Turn On Deep Color Block and PLL
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block, before switch PLL
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);

                // HDMI Output Div2 Disable
                ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, 0x00);

                // Power down PLL
                ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
                ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)

#if(_HDMI_FORCE_FREESYNC_SUPPORT == _ON)
            if(bFreeSyncReceive == _TRUE)
#else
            if(GET_HDMI_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
#endif
            {
                ScalerTmdsMacRxSetFreesyncProc(enumMappingPort, _ENABLE);

                // Get SPD Free Sync Vfreq Max
                SET_DRR_VFREQ_MAX(GET_HDMI_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10);
                SET_DRR_VFREQ_MIN(GET_HDMI_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10);

                // Disable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
            }
            else
#endif
            {
#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
                if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
                {
#if(_HDMI21_VRR_SUPPORT == _ON)
                    WORD usSourceBrr = 0x00;

                    // Get Base Frame Rate from SRC
                    if((GET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_VIC) != 0x00))
                    {
                        usSourceBrr = ((WORD)ScalerTmdsMacRxGetVicVfreqParameter(ScalerTmdsMacRx4HdmiGetAVIInfo(_AVI_INFO_VIC)) * 10);
                        DebugMessageRx4("VRR BRR (AVI IF VIC)", usSourceBrr);
                    }
                    else if((GET_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerTmdsMacRx4HdmiRsv6GetAviInfo(_AVI_INFO_FR) != 0x00))
                    {
                        usSourceBrr = (ScalerTmdsMacRxGetOvtVfreqParameter(ScalerTmdsMacRx4HdmiRsv6GetAviInfo(_AVI_INFO_FR)) * 10);
                        DebugMessageRx4("VRR BRR (AVI IF OVT)", usSourceBrr);
                    }
                    else if(ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_BASE_REFRESH_RATE) != 0x00)
                    {
                        usSourceBrr = ((WORD)ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_BASE_REFRESH_RATE) * 10);
                        DebugMessageRx4("VRR BRR (VTEM)", usSourceBrr);
                    }
                    else
                    {
                        DebugMessageRx4("VRR BRR Error!!", 0x00);
                    }

                    // Get max Vfmax from SRC BRR
                    SET_DRR_VFREQ_MAX(usSourceBrr);

                    if(((bit)ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _ENABLE)
                    {
                        SET_TMDS_MAC_RX4_HDMI21_VRR_EN();
                        DebugMessageRx4("VRR_EN", 0x00);
                    }
                    else
                    {
                        CLR_TMDS_MAC_RX4_HDMI21_VRR_EN();
                        DebugMessageRx4("VRR_DIS", 0x00);
                    }

                    if(((bit)ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _ENABLE)
                    {
                        SET_TMDS_MAC_RX4_HDMI21_QMS_EN();
                        DebugMessageRx4("QMS_EN", 0x00);
                    }
                    else
                    {
                        CLR_TMDS_MAC_RX4_HDMI21_QMS_EN();
                        DebugMessageRx4("QMS_DIS", 0x00);
                    }

#if(_HDMI_FORCE_VRR_SUPPORT == _ON)
                    // Get SPD Free Sync Vfreq Max
                    SET_DRR_VFREQ_MAX(0);
                    SET_DRR_VFREQ_MIN(0);
#endif
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
                    SET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR(ScalerTmdsMacRx4HdmiGetVtemInfo(_HDMI21_VTEM_INFO_FVA_FACTOR_M1) + 1);
#endif
                    // Disable DE Only Mode
                    ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
                }
#endif
            }

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
            if(GET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED() == _TRUE)
            {
                ScalerTmdsMacRxSetFreesyncReplayProc(enumMappingPort, _ENABLE);

                // Set Freesync Replay enable
                ScalerSetBit(P73_D6_HDMI_SHDR_IE, ~_BIT4, _BIT4);
            }
#endif
        }
        else
        {
            CLR_TMDS_MAC_RX4_HDMI_AVI_INFO_FRAME_RECEIVED();

            CLR_TMDS_MAC_RX4_HDMI_GCP_RECEIVED();

            // Disable All WD when DVI
            ScalerTmdsMacRx4HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            ScalerTmdsMacRx4DviVideoSetting();

            SET_COLOR_DEPTH(enumMappingPort, _COLOR_DEPTH_8_BITS);

#if(_3DDI_FUNCTION == _ON)
            ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR);
            if((ScalerTimerPollingFlagProc(130, P73_CA_HDMI_DP, _BIT6, _TRUE) == _TRUE) && (ScalerTmdsMacRx4GetInterlace3ddiAvailable() == _TRUE))
            {
                // Disable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, 0x00);

                // Disable Deep color FIFO Output
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, 0x00);

                if(ScalerTmdsMacRx4HdmiDeepColorProc(g_usTmdsMacRx4ClkCount) == _FALSE)
                {
                    // Enable Deep color FIFO Output
                    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

                    return _SOURCE_NONE;
                }

                // HDMI Output Div2 Enable
                ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, _BIT7);

                // Turn On Deep Color Block and PLL
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
#endif
            {
                // Turn off Deep Color Block, before switch PLL
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);

                // HDMI Output Div2 Disable
                ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, 0x00);

                // Power down PLL
                ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
                ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);
            }
        }
#else

        ScalerTmdsMacRx4DviVideoSetting();

        SET_COLOR_DEPTH(enumMappingPort, _COLOR_DEPTH_8_BITS);

#if(_3DDI_FUNCTION == _ON)
        ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR);
        if((ScalerTimerPollingFlagProc(130, P73_CA_HDMI_DP, _BIT6, _TRUE) == _TRUE) && (ScalerTmdsMacRx4GetInterlace3ddiAvailable() == _TRUE))
        {
            // Disable DE Only Mode
            ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, 0x00);

            // Disable Deep color FIFO Output
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, 0x00);

            if(ScalerTmdsMacRx4HdmiDeepColorProc(g_usTmdsMacRx4ClkCount) == _FALSE)
            {
                // Enable Deep color FIFO Output
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

                return _SOURCE_NONE;
            }

            // HDMI Output Div2 Enable
            ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, _BIT7);

            // Turn On Deep Color Block and PLL
            ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, _BIT7);
        }
        else
#endif
        {
            // Turn off Deep Color Block, before switch PLL
            ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);

            // HDMI Output Div2 Disable
            ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT7, 0x00);

            // Power down PLL
            ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
            ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);
        }
#endif

#if(_HDMI_DPC_FIFO_ERR_CHECK_SUPPORT == _ON)
        if((ScalerGetBit(P73_B5_TMDS_UDC0, _BIT7) == _BIT7) && (ScalerTmdsMacRx4HdmiCheckDeepColorFifo() == _FALSE))
        {
            return _SOURCE_NONE;
        }
#endif

        // Enable Video Output
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        return enumSourceType;
    }

    return _SOURCE_NONE;
}

#endif // End of #if(_TMDS_MAC_RX4_SUPPORT == _ON)

