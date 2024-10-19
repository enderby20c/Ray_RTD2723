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
// ID Code      : ScalerDrr.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DRR__

#include "ScalerFunctionInclude.h"
#include "Drr/ScalerDrr.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
StructDrrFreeSyncDpEnableInfo g_stDrrFreeSyncDpInfo;
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
StructDrrDpAdaptiveSyncEnableInfo g_stDrrDpAdaptiveSyncInfo;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
StructDrrFreeSyncHdmiEnableInfo g_stDrrFreeSyncHdmiInfo;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
volatile BYTE g_ucDrrFreeSyncHdmiVcpReceive;
#endif

#if(_FREESYNC_SUPPORT == _ON)
bit g_bDrrFreeSyncSpdInfoReceive;
StructDrrFreesyncVerByEdid g_stDrrFreesyncVerbyEdid;
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
StructDrrAmdAupiInfo g_stDrrHdmiAmdAupiInfo;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
StructDrrAmdAupiInfo g_stDrrDpAmdAupiInfo;
#endif

#if(_DRR_SUPPORT == _ON)
bit g_bDrrGetIVFInfo;
WORD g_usDrrPanelVFreqMax;
WORD g_usDrrPanelVFreqMin;
DWORD g_ulDrrVFreqMax;
DWORD g_ulDrrVFreqMin;
#endif

#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
bit g_bDrrDscDecoder0Enable = _FALSE;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
bit g_bDrrDscDecoder1Enable = _FALSE;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Drr Enable Type
// Input Value  : EnumInputPort
// Output Value : Drr enable type
//--------------------------------------------------
EnumDrrType ScalerDrrGetType(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerDrrFreeSyncEnable(enumInputPort) == _DRR_FREESYNC_TYPE)
    {
        return _DRR_FREESYNC_TYPE;
    }
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
    // FW consider "VRR/ FVA only" & "VRR + FVA" as DRR case
    if(ScalerTmdsMacRxGetHdmi21VrrStatus(enumInputPort) == _TRUE)
    {
        return _DRR_HDMI21_VRR_TYPE;
    }
#endif

    return _DRR_NONE_TYPE;
}

//--------------------------------------------------
// Description  : Drr Vfreq Max Info Enable
// Input Value  : None
// Output Value : _TRUE, _FAIL
//--------------------------------------------------
bit ScalerDrrVfreqMaxInfoEnable(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    enumInputPort = enumInputPort;

#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerDrrGetType(enumInputPort) == _DRR_FREESYNC_TYPE)
    {
        // AMD ver 1 & 2
        if((ScalerDrrGetAmdVsdbVer(enumInputPort) == _AMD_VER1) ||
           (ScalerDrrGetAmdVsdbVer(enumInputPort) == _AMD_VER2))
        {
            if(GET_FREESYNC_SPD_INFO_FRAME_RECEIVED() == _TRUE)
            {
#if(_HDMI_FREESYNC_SUPPORT == _ON)
                if(enumPortType == _PORT_HDMI)
                {
                    return ScalerDrrFreeSyncHdmiGetEnable(enumInputPort);
                }
                else
#endif
                {
#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_DP_DRR_GET_IVF_TYPE == _DP_DRR_SPD_INFO)
                    if(enumPortType == _PORT_DP)
                    {
                        return ScalerDrrFreeSyncDpGetEnable(enumInputPort);
                    }
#endif
#endif
                }
            }
            else
            {
                // Gsync
            }
        }
        else
        {
            // Version 3 or _AMD_VER_NONE
        }
    }
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
    // VTEM received & qms/vrr_en = 1 => use IVF from Mac
    if((enumPortType == _PORT_HDMI) && (ScalerDrrGetType(enumInputPort) == _DRR_HDMI21_VRR_TYPE) &&
       ((ScalerTmdsMacRxGetVrrEnStatus(enumInputPort) == _TRUE) || (ScalerTmdsMacRxGetQmsEnStatus(enumInputPort) == _TRUE)))
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set Drr Panel Vfeq Info
// Input Value  : enumInputPort, enumDrrType
// Output Value : None
//--------------------------------------------------
void ScalerDrrSetPanelVfeqInfo(EnumInputPort enumInputPort)
{
    WORD usDrrPanelVfreqMax = _PANEL_MAX_FRAME_RATE;
    WORD usDrrPanelVfreqMin = _PANEL_MIN_FRAME_RATE;
    EnumDrrType enumDrrType = ScalerDrrGetType(enumInputPort);

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            if(enumDrrType == _DRR_FREESYNC_TYPE)
            {
#if((_D0_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_DP_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_DP_FREESYNC_MIN_FRAME_RATE;
#elif((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE;
#endif
            }
            else if(enumDrrType == _DRR_HDMI21_VRR_TYPE)
            {
#if((_D0_HDMI_SUPPORT == _ON) && (_HDMI21_VRR_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI21_VRR_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI21_VRR_MIN_FRAME_RATE;
#endif
            }

            break;


        case _D1_INPUT_PORT:
            if(enumDrrType == _DRR_FREESYNC_TYPE)
            {
#if((_D1_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_DP_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_DP_FREESYNC_MIN_FRAME_RATE;
#elif((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE;
#endif
            }
            else if(enumDrrType == _DRR_HDMI21_VRR_TYPE)
            {
#if((_D1_HDMI_SUPPORT == _ON) && (_HDMI21_VRR_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI21_VRR_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI21_VRR_MIN_FRAME_RATE;
#endif
            }

            break;


        case _D2_INPUT_PORT:
            if(enumDrrType == _DRR_FREESYNC_TYPE)
            {
#if((_D2_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_DP_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_DP_FREESYNC_MIN_FRAME_RATE;
#elif((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE;
#endif
            }
            else if(enumDrrType == _DRR_HDMI21_VRR_TYPE)
            {
#if((_D2_HDMI_SUPPORT == _ON) && (_HDMI21_VRR_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI21_VRR_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI21_VRR_MIN_FRAME_RATE;
#endif
            }

            break;


        case _D3_INPUT_PORT:
            if(enumDrrType == _DRR_FREESYNC_TYPE)
            {
#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE;
#endif
            }
            else if(enumDrrType == _DRR_HDMI21_VRR_TYPE)
            {
#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI21_VRR_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI21_VRR_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI21_VRR_MIN_FRAME_RATE;
#endif
            }

            break;


        case _D4_INPUT_PORT:
            if(enumDrrType == _DRR_FREESYNC_TYPE)
            {
#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE;
#endif
            }
            else if(enumDrrType == _DRR_HDMI21_VRR_TYPE)
            {
#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI21_VRR_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI21_VRR_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI21_VRR_MIN_FRAME_RATE;
#endif
            }

            break;


        case _D5_INPUT_PORT:
            if(enumDrrType == _DRR_FREESYNC_TYPE)
            {
#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE;
#endif
            }
            else if(enumDrrType == _DRR_HDMI21_VRR_TYPE)
            {
#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI21_VRR_SUPPORT == _ON))
                usDrrPanelVfreqMax = _PANEL_HDMI21_VRR_MAX_FRAME_RATE;
                usDrrPanelVfreqMin = _PANEL_HDMI21_VRR_MIN_FRAME_RATE;
#endif
            }

            break;


        default:

            break;
    }
    SET_DRR_PANEL_MAX_FRAME_RATE(usDrrPanelVfreqMax);
    SET_DRR_PANEL_MIN_FRAME_RATE(usDrrPanelVfreqMin);
}

//--------------------------------------------------
// Description  : DRR Receive Source IVF
// Input Value  : enumInputPort/ IVF
// Output Value : _TRUE: Receive Source IVF
//--------------------------------------------------
bit ScalerDrrReceiveSourceIVF(EnumInputPort enumInputPort, EnumPortType enumPortType, WORD *pusIVfreq)
{
    if((GET_DRR_VFREQ_MAX() >= GET_DRR_PANEL_MIN_FRAME_RATE()) &&
       (GET_DRR_VFREQ_MAX() <= GET_DRR_PANEL_MAX_FRAME_RATE()) &&
       (ScalerDrrVfreqMaxInfoEnable(enumInputPort, enumPortType) == _TRUE))
    {
        DebugMessageScaler("DRR Get IVF from Source info", GET_DRR_VFREQ_MAX());
        *pusIVfreq = (WORD)GET_DRR_VFREQ_MAX();

        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Adaptivesync Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDrrDpAdaptiveSyncCapabilitySwitchProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_ADAPTIVESYNC_DP_D0_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_ADAPTIVESYNC_DP_D0_CAPABILITY_SWITCH();

                if(GET_ADAPTIVESYNC_DP_D0_SUPPORT() == _DP_ADAPTIVESYNC_SUPPORT_ON)
                {
                    ScalerDpAuxRxSetDpcdMirrorBitValue(_D0_INPUT_PORT, 0x00, 0x00, 0x07, ~_BIT6, _BIT6);

                    ScalerDpAuxRxSetDpcdBitValue(_D0_INPUT_PORT, 0x00, 0x22, 0x14, ~_BIT0, _BIT0);
                }
                else
                {
                    ScalerDpAuxRxSetDpcdMirrorBitValue(_D0_INPUT_PORT, 0x00, 0x00, 0x07, ~_BIT6, 0x00);

                    ScalerDpAuxRxSetDpcdBitValue(_D0_INPUT_PORT, 0x00, 0x22, 0x14, ~_BIT0, 0x00);
                }

                return _TRUE;
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_ADAPTIVESYNC_DP_D1_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_ADAPTIVESYNC_DP_D1_CAPABILITY_SWITCH();

                if(GET_ADAPTIVESYNC_DP_D1_SUPPORT() == _DP_ADAPTIVESYNC_SUPPORT_ON)
                {
                    ScalerDpAuxRxSetDpcdMirrorBitValue(_D1_INPUT_PORT, 0x00, 0x00, 0x07, ~_BIT6, _BIT6);

                    ScalerDpAuxRxSetDpcdBitValue(_D1_INPUT_PORT, 0x00, 0x22, 0x14, ~_BIT0, _BIT0);
                }
                else
                {
                    ScalerDpAuxRxSetDpcdMirrorBitValue(_D1_INPUT_PORT, 0x00, 0x00, 0x07, ~_BIT6, 0x00);

                    ScalerDpAuxRxSetDpcdBitValue(_D1_INPUT_PORT, 0x00, 0x22, 0x14, ~_BIT0, 0x00);
                }

                return _TRUE;
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_ADAPTIVESYNC_DP_D2_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_ADAPTIVESYNC_DP_D2_CAPABILITY_SWITCH();

                if(GET_ADAPTIVESYNC_DP_D2_SUPPORT() == _DP_ADAPTIVESYNC_SUPPORT_ON)
                {
                    ScalerDpAuxRxSetDpcdMirrorBitValue(_D2_INPUT_PORT, 0x00, 0x00, 0x07, ~_BIT6, _BIT6);

                    ScalerDpAuxRxSetDpcdBitValue(_D2_INPUT_PORT, 0x00, 0x22, 0x14, ~_BIT0, _BIT0);
                }
                else
                {
                    ScalerDpAuxRxSetDpcdMirrorBitValue(_D2_INPUT_PORT, 0x00, 0x00, 0x07, ~_BIT6, 0x00);

                    ScalerDpAuxRxSetDpcdBitValue(_D2_INPUT_PORT, 0x00, 0x22, 0x14, ~_BIT0, 0x00);
                }

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
// Description  : Switch DP ADAPTIVESYNC Support
// Input Value  : Hotplug Type and ADAPTIVESYNC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerDrrDpAdaptiveSyncSupportSwitch(EnumInputPort enumInputPort, EnumDpAdaptiveSyncSupport enumSupport)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_ADAPTIVESYNC_DP_D0_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_ADAPTIVESYNC_DP_D0_CAPABILITY_SWITCH();
                SET_ADAPTIVESYNC_DP_D0_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_ADAPTIVESYNC_DP_D1_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_ADAPTIVESYNC_DP_D1_CAPABILITY_SWITCH();
                SET_ADAPTIVESYNC_DP_D1_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_ADAPTIVESYNC_DP_D2_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_ADAPTIVESYNC_DP_D2_CAPABILITY_SWITCH();
                SET_ADAPTIVESYNC_DP_D2_SUPPORT(enumSupport);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP ADAPTIVESYNC Support
// Input Value  : EnumInputPort
// Output Value : EnumAdaptiveSyncSupport
//--------------------------------------------------
EnumDpAdaptiveSyncSupport ScalerDrrDpAdaptiveSyncGetSupport(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_ADAPTIVESYNC_DP_D0_SUPPORT();
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_ADAPTIVESYNC_DP_D1_SUPPORT();
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_ADAPTIVESYNC_DP_D2_SUPPORT();
#endif

        default:
            break;
    }

    return _DP_ADAPTIVESYNC_SUPPORT_OFF;
}

//--------------------------------------------------
// Description  : Set DP Mac AdaptivesyncEnable
// Input Value  : EnumInputPort, bENABLE
// Output Value : None
//--------------------------------------------------
void ScalerDrrDpAdaptiveSyncSetEnable(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_ADAPTIVESYNC_DP_D0_ENABLED();
            }
            else
            {
                CLR_ADAPTIVESYNC_DP_D0_ENABLED();
            }

            break;

#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_ADAPTIVESYNC_DP_D1_ENABLED();
            }
            else
            {
                CLR_ADAPTIVESYNC_DP_D1_ENABLED();
            }

            break;

#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_ADAPTIVESYNC_DP_D2_ENABLED();
            }
            else
            {
                CLR_ADAPTIVESYNC_DP_D2_ENABLED();
            }

            break;

#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP AdaptiveSync Enable
// Input Value  : EnumInputPort
// Output Value : _ENABLE/ _DISABLE
//--------------------------------------------------
bit ScalerDrrDpAdaptiveSyncGetEnable(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_ADAPTIVESYNC_DP_D0_ENABLED();
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_ADAPTIVESYNC_DP_D1_ENABLED();
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_ADAPTIVESYNC_DP_D2_ENABLED();
#endif
        default:
            break;
    }

    return _FALSE;
}

#endif

#if(_FREESYNC_SUPPORT == _ON)

#if((_DEBUG_MESSAGE_SUPPORT == _OFF) && (_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get HDMI FREESYNC VCP
// Input Value  : None
// Output Value : HDMI FREESYNC VCP
//                False --> Disabled
//--------------------------------------------------
BYTE ScalerDrrFreeSyncGetHdmiVcp(void)
{
    return GET_FREESYNC_HDMI_VCP();
}

//--------------------------------------------------
// Description  : Set HDMI FREESYNC VCP
// Input Value  : HDMI FREESYNC VCP
// Output Value : None
//--------------------------------------------------
void ScalerDrrFreeSyncSetHdmiVcp(BYTE ucVcpCode)
{
    g_ucDrrFreeSyncHdmiVcpReceive = ucVcpCode;
}
#endif
//--------------------------------------------------
// Description  : Set AMD VSDB Ver form Edid
// Input Value  : enumInputPort
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
void ScalerDrrSetAmdVsdbVer(EnumInputPort enumInputPort, EnumAmdVsdbVer enumAmdVer)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            SET_FREESYNC_VER_D0_BY_EDID(enumAmdVer);
            break;

        case _D1_INPUT_PORT:
            SET_FREESYNC_VER_D1_BY_EDID(enumAmdVer);
            break;

        case _D2_INPUT_PORT:
            SET_FREESYNC_VER_D2_BY_EDID(enumAmdVer);
            break;

        case _D3_INPUT_PORT:
            SET_FREESYNC_VER_D3_BY_EDID(enumAmdVer);
            break;

        case _D4_INPUT_PORT:
            SET_FREESYNC_VER_D4_BY_EDID(enumAmdVer);
            break;

        case _D5_INPUT_PORT:
            SET_FREESYNC_VER_D5_BY_EDID(enumAmdVer);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set AMD VSDB Ver form Edid
// Input Value  : enumInputPort
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
EnumAmdVsdbVer ScalerDrrGetAmdVsdbVer(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            return GET_FREESYNC_VER_D0_BY_EDID();

        case _D1_INPUT_PORT:
            return GET_FREESYNC_VER_D1_BY_EDID();

        case _D2_INPUT_PORT:
            return GET_FREESYNC_VER_D2_BY_EDID();

        case _D3_INPUT_PORT:
            return GET_FREESYNC_VER_D3_BY_EDID();

        case _D4_INPUT_PORT:
            return GET_FREESYNC_VER_D4_BY_EDID();

        case _D5_INPUT_PORT:
            return GET_FREESYNC_VER_D5_BY_EDID();

        default:
            break;
    }

    return _AMD_VER_NONE;
}

//--------------------------------------------------
// Description  : Get AMD SPD info
// Input Value  : enumContent -> enumInputPort -> Port Type, AMD Info Type
// Output Value : None
//--------------------------------------------------
DWORD ScalerDrrFreeSyncGetInfo(EnumInputPort enumInputPort, EnumAmdSpdInfoContent enumContent)
{
    DWORD ulFreeSyncInfo = 0;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
#if((_D0_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerDpMacStreamRxFreeSyncGetAmdSpdInfo(_D0_INPUT_PORT, enumContent);
#elif((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerTmdsMacRxFreeSyncHDMIGetAmdSpdInfo(_D0_INPUT_PORT, enumContent);
#endif
            break;


        case _D1_INPUT_PORT:
#if((_D1_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerDpMacStreamRxFreeSyncGetAmdSpdInfo(_D1_INPUT_PORT, enumContent);
#elif((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerTmdsMacRxFreeSyncHDMIGetAmdSpdInfo(_D1_INPUT_PORT, enumContent);
#endif
            break;


        case _D2_INPUT_PORT:
#if((_D2_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerDpMacStreamRxFreeSyncGetAmdSpdInfo(_D2_INPUT_PORT, enumContent);
#elif((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerTmdsMacRxFreeSyncHDMIGetAmdSpdInfo(_D2_INPUT_PORT, enumContent);
#endif
            break;


        case _D3_INPUT_PORT:
#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerTmdsMacRxFreeSyncHDMIGetAmdSpdInfo(_D3_INPUT_PORT, enumContent);
#endif
            break;


        case _D4_INPUT_PORT:
#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerTmdsMacRxFreeSyncHDMIGetAmdSpdInfo(_D4_INPUT_PORT, enumContent);
#endif
            break;


        case _D5_INPUT_PORT:
#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ulFreeSyncInfo = ScalerTmdsMacRxFreeSyncHDMIGetAmdSpdInfo(_D5_INPUT_PORT, enumContent);
#endif
            break;


        default:
            ulFreeSyncInfo = 0;
            break;
    }

    switch(enumContent)
    {
#if(_SPD_INFO_FREESYNC_ENABLE_REF == _REF_DRR_GET_TYPE)
        case _SPD_INFO_FREESYNC_ENABLE:
            ulFreeSyncInfo = (ScalerDrrGetType(enumInputPort) == _DRR_FREESYNC_TYPE);
            break;
#endif

        case _SPD_INFO_FREESYNC_MIN_VFREQ:
            break;

        case _SPD_INFO_FREESYNC_MAX_VFREQ:
            break;

        default:
            break;
    }

    return ulFreeSyncInfo;
}

//--------------------------------------------------
// Description  : Get AMD SPD info
// Input Value  : enumInputPort -> Port Type
// Output Value : None
//--------------------------------------------------
void ScalerDrrFreeSyncSpdInfoReceive(EnumInputPort enumInputPort)
{
    bit bReceived = _FALSE;

    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            bReceived = ScalerDpMacStreamRxFreeSyncGetAmdSpdInfoReceive(_D0_INPUT_PORT);
#elif((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            bReceived = GET_FREESYNC_HDMI_D0_ENABLED();
#endif

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            bReceived = ScalerDpMacStreamRxFreeSyncGetAmdSpdInfoReceive(_D1_INPUT_PORT);
#elif((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            bReceived = GET_FREESYNC_HDMI_D1_ENABLED();
#endif

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            bReceived = ScalerDpMacStreamRxFreeSyncGetAmdSpdInfoReceive(_D2_INPUT_PORT);
#elif((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            bReceived = GET_FREESYNC_HDMI_D2_ENABLED();
#endif

            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            bReceived = GET_FREESYNC_HDMI_D3_ENABLED();
#endif

            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            bReceived = GET_FREESYNC_HDMI_D4_ENABLED();
#endif

            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            bReceived = GET_FREESYNC_HDMI_D5_ENABLED();
#endif

            break;
#endif

        default:
            break;
    }

    SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(bReceived);
}

//--------------------------------------------------
// Description  : HDMI freesync initial
// Input Value  : support or not
// Output Value :
//--------------------------------------------------
void ScalerDrrFreeSyncSupportSwitch(EnumInputPort enumInputPort, EnumFreeSyncSupport enumSupport, EnumInputPort enumFreesyncTargetPort)
{
    enumSupport = enumSupport;
    enumFreesyncTargetPort = enumFreesyncTargetPort;

    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if((_D0_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncDpSupportSwitch(enumInputPort, enumSupport);
#elif((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncHdmiSupportSwitch(enumInputPort, enumSupport, enumFreesyncTargetPort);
#endif

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if((_D1_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncDpSupportSwitch(enumInputPort, enumSupport);
#elif((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncHdmiSupportSwitch(enumInputPort, enumSupport, enumFreesyncTargetPort);
#endif

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if((_D2_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncDpSupportSwitch(enumInputPort, enumSupport);
#elif((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncHdmiSupportSwitch(enumInputPort, enumSupport, enumFreesyncTargetPort);
#endif

            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncHdmiSupportSwitch(enumInputPort, enumSupport, enumFreesyncTargetPort);
#endif

            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncHdmiSupportSwitch(enumInputPort, enumSupport, enumFreesyncTargetPort);
#endif

            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerDrrFreeSyncHdmiSupportSwitch(enumInputPort, enumSupport, enumFreesyncTargetPort);
#endif

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Freesync Enable
// Input Value  : enumInputPort
// Output Value : EnumDrrType
//--------------------------------------------------
EnumDrrType ScalerDrrFreeSyncEnable(EnumInputPort enumInputPort)
{
    EnumDrrType enumDrrType = _DRR_NONE_TYPE;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

#if((_D0_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_DP_D0_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#elif((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_HDMI_D0_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#endif

            break;


        case _D1_INPUT_PORT:

#if((_D1_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_DP_D1_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#elif((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_HDMI_D1_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#endif

            break;


        case _D2_INPUT_PORT:

#if((_D2_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_DP_D2_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#elif((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_HDMI_D2_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#endif

            break;


        case _D3_INPUT_PORT:

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_HDMI_D3_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#endif

            break;


        case _D4_INPUT_PORT:

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_HDMI_D4_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#endif

            break;


        case _D5_INPUT_PORT:

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            enumDrrType = (GET_FREESYNC_HDMI_D5_ENABLED() == _ENABLE) ? _DRR_FREESYNC_TYPE : _DRR_NONE_TYPE;
#endif

            break;


        default:

            break;
    }

    return enumDrrType;
}

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Freesync Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDrrFreeSyncDpCapabilitySwitchProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_FREESYNC_DP_D0_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_FREESYNC_DP_D0_CAPABILITY_SWITCH();

                ScalerDpAuxRxFreesyncDpcdSetting(_D0_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_FREESYNC_DP_D1_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_FREESYNC_DP_D1_CAPABILITY_SWITCH();

                ScalerDpAuxRxFreesyncDpcdSetting(_D1_INPUT_PORT);

                return _TRUE;
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_FREESYNC_DP_D2_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_FREESYNC_DP_D2_CAPABILITY_SWITCH();

                ScalerDpAuxRxFreesyncDpcdSetting(_D2_INPUT_PORT);

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
// Description  : Switch DP FREESYNC Support
// Input Value  : Hotplug Type and FREESYNC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerDrrFreeSyncDpSupportSwitch(EnumInputPort enumInputPort, EnumFreeSyncSupport enumSupport)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_FREESYNC_DP_D0_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_FREESYNC_DP_D0_CAPABILITY_SWITCH();
                SET_FREESYNC_DP_D0_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_FREESYNC_DP_D1_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_FREESYNC_DP_D1_CAPABILITY_SWITCH();
                SET_FREESYNC_DP_D1_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_FREESYNC_DP_D2_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_FREESYNC_DP_D2_CAPABILITY_SWITCH();
                SET_FREESYNC_DP_D2_SUPPORT(enumSupport);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP FREESYNC Support
// Input Value  : EnumInputPort
// Output Value : EnumFreeSyncSupport
//--------------------------------------------------
EnumFreeSyncSupport ScalerDrrFreeSyncDpGetSupport(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_FREESYNC_DP_D0_SUPPORT();
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_FREESYNC_DP_D1_SUPPORT();
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_FREESYNC_DP_D2_SUPPORT();
#endif

        default:
            break;
    }

    return _FREESYNC_SUPPORT_OFF;
}

//--------------------------------------------------
// Description  : Get DP Mac FreesyncEnable
// Input Value  : EnumInputPort
// Output Value : bENABLE
//--------------------------------------------------
bit ScalerDrrFreeSyncDpGetStreamConfig(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return ScalerDpMacStreamRxFreeSyncGetStreamConfig(_STREAM_SOURCE_D0_DP);
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return ScalerDpMacStreamRxFreeSyncGetStreamConfig(_STREAM_SOURCE_D1_DP);
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return ScalerDpMacStreamRxFreeSyncGetStreamConfig(_STREAM_SOURCE_D2_DP);
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            return ScalerDpMacStreamRxFreeSyncGetStreamConfig(_STREAM_SOURCE_PXP);
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP Mac FreesyncEnable
// Input Value  : EnumInputPort, bENABLE
// Output Value : None
//--------------------------------------------------
void ScalerDrrFreeSyncDpSetEnable(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_DP_D0_ENABLED();
            }
            else
            {
                CLR_FREESYNC_DP_D0_ENABLED();
            }

            break;

#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_DP_D1_ENABLED();
            }
            else
            {
                CLR_FREESYNC_DP_D1_ENABLED();
            }

            break;

#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_DP_D2_ENABLED();
            }
            else
            {
                CLR_FREESYNC_DP_D2_ENABLED();
            }

            break;

#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            if(bEnable == _ENABLE)
            {
                SET_FREESYNC_DP_D9_ENABLED();
            }
            else
            {
                CLR_FREESYNC_DP_D9_ENABLED();
            }

            break;

#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Freesync Enable
// Input Value  : EnumInputPort
// Output Value : _ENABLE/ _DISABLE
//--------------------------------------------------
bit ScalerDrrFreeSyncDpGetEnable(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_FREESYNC_DP_D0_ENABLED();
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_FREESYNC_DP_D1_ENABLED();
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_FREESYNC_DP_D2_ENABLED();
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            return GET_FREESYNC_DP_D9_ENABLED();
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif // End of #if(_DP_FREESYNC_SUPPORT == _ON)

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) &&\
    (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get HDMI FreeSync Support
// Input Value  : enumInputPort
// Output Value : _FREESYNC_SUPPORT_ON/ _FREESYNC_SUPPORT_OFF
//--------------------------------------------------
EnumFreeSyncSupport ScalerDrrFreeSyncHdmiGetFreeSyncSupport(EnumInputPort enumInputPort)
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
// Description  : Switch DP FREESYNC Support
// Input Value  : Hotplug Type and FREESYNC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerDrrFreeSyncHdmiSupportSwitch(EnumInputPort enumInputPort, EnumFreeSyncSupport enumSupport, EnumInputPort enumFreesyncTargetPort)
{
    enumFreesyncTargetPort = enumFreesyncTargetPort;

    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_FREESYNC_SUPPORT_TMDS_D1() != enumSupport)
            {
#if(_TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT == _ON)
                if(enumFreesyncTargetPort == _D1_INPUT_PORT)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D1_INPUT_PORT, _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH);
                }

                SET_FREESYNC_SUPPORT_TMDS_D1(enumSupport);

#if(_HDMI20_SUPPORT == _ON)
                if(enumSupport == _FREESYNC_SUPPORT_ON)
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D1_INPUT_PORT, _ENABLE);
                }
                else
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D1_INPUT_PORT, _DISABLE);
                }
#endif
            }

            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_FREESYNC_SUPPORT_TMDS_D2() != enumSupport)
            {
#if(_TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT == _ON)
                if(enumFreesyncTargetPort == _D2_INPUT_PORT)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D2_INPUT_PORT, _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH);
                }

                SET_FREESYNC_SUPPORT_TMDS_D2(enumSupport);

#if(_HDMI20_SUPPORT == _ON)
                if(enumSupport == _FREESYNC_SUPPORT_ON)
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D2_INPUT_PORT, _ENABLE);
                }
                else
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D2_INPUT_PORT, _DISABLE);
                }
#endif
            }

            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            if(GET_FREESYNC_SUPPORT_TMDS_D3() != enumSupport)
            {
#if(_TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT == _ON)
                if(enumFreesyncTargetPort == _D3_INPUT_PORT)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D3_INPUT_PORT, _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH);
                }

                SET_FREESYNC_SUPPORT_TMDS_D3(enumSupport);

#if(_HDMI20_SUPPORT == _ON)
                if(enumSupport == _FREESYNC_SUPPORT_ON)
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D3_INPUT_PORT, _ENABLE);
                }
                else
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D3_INPUT_PORT, _DISABLE);
                }
#endif
            }

            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            if(GET_FREESYNC_SUPPORT_TMDS_D4() != enumSupport)
            {
#if(_TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT == _ON)
                if(enumFreesyncTargetPort == _D4_INPUT_PORT)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D4_INPUT_PORT, _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH);
                }

                SET_FREESYNC_SUPPORT_TMDS_D4(enumSupport);

#if(_HDMI20_SUPPORT == _ON)
                if(enumSupport == _FREESYNC_SUPPORT_ON)
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D4_INPUT_PORT, _ENABLE);
                }
                else
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D4_INPUT_PORT, _DISABLE);
                }
#endif
            }

            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            if(GET_FREESYNC_SUPPORT_TMDS_D5() != enumSupport)
            {
#if(_TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT == _ON)
                if(enumFreesyncTargetPort == _D5_INPUT_PORT)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D5_INPUT_PORT, _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH);
                }

                SET_FREESYNC_SUPPORT_TMDS_D5(enumSupport);

#if(_HDMI20_SUPPORT == _ON)
                if(enumSupport == _FREESYNC_SUPPORT_ON)
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D5_INPUT_PORT, _ENABLE);
                }
                else
                {
                    ScalerTmdsMacRxSetAmdAupiScdcInfo(_D5_INPUT_PORT, _DISABLE);
                }
#endif
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get HDMI Freesync Enable
// Input Value  : enumInputPort
// Output Value : _ENABLE/ _DISABLE
//--------------------------------------------------
bit ScalerDrrFreeSyncHdmiGetEnable(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
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
            return _DISABLE;
    }
}
#endif
#endif

#endif
#endif

#if((_FREESYNC_II_SUPPORT == _ON) && (_ULTRA_HDR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get Current FreeSync II data enable status
// Input Value  : enumInputPort --> Input port
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDrrFreeSyncIICheckPortStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D0_DP_SUPPORT == _ON)
            if(_DP_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D1_DP_SUPPORT == _ON)
            if(_DP_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif

            break;

        case _D2_INPUT_PORT:
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D2_DP_SUPPORT == _ON)
            if(_DP_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        default:
            return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Current FreeSync II data
// Input Value  : enumDisplayRegion --> Current Display Region
//                enumInputPort --> Input port
// Output Value : None
//--------------------------------------------------
void ScalerDrrFreeSyncIIGetCurrentStatus(EnumInputPort enumInputPort, EnumDisplayRegion enumDisplayRegion, EnumHDRInfoChgPolling enumFreeSyncIIInfoChgPolling)
{
    StructFreeSyncIIInfo stFreeSyncIIData = {0};

    if(ScalerDrrFreeSyncIICheckPortStatus(enumInputPort) == _TRUE)
    {
        BYTE pucSdpInfoData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};
        BYTE ucFreeSyncIIInfoReceive = _FALSE;
        BYTE ucFreeSyncIIInfoChange = _FALSE;

        switch(enumInputPort)
        {
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#if(_D0_DP_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                ScalerDpMacStreamRxFreeSyncIIGetCurrentStatus(_D0_INPUT_PORT, &ucFreeSyncIIInfoReceive, &ucFreeSyncIIInfoChange, pucSdpInfoData);

                break;
#endif

#if(_D1_DP_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                ScalerDpMacStreamRxFreeSyncIIGetCurrentStatus(_D1_INPUT_PORT, &ucFreeSyncIIInfoReceive, &ucFreeSyncIIInfoChange, pucSdpInfoData);

                break;
#endif

#if(_D2_DP_SUPPORT == _ON)
            case _D2_INPUT_PORT:

                ScalerDpMacStreamRxFreeSyncIIGetCurrentStatus(_D2_INPUT_PORT, &ucFreeSyncIIInfoReceive, &ucFreeSyncIIInfoChange, pucSdpInfoData);

                break;
#endif
#endif

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#if(_D1_HDMI_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                ucFreeSyncIIInfoReceive = ScalerTmdsMacRxGetSdpInfoFrameReceivedFlag(_D1_INPUT_PORT);
                ucFreeSyncIIInfoChange = _TRUE;

                if((ucFreeSyncIIInfoReceive == _TRUE) && (ucFreeSyncIIInfoChange == _TRUE))
                {
                    ScalerTmdsMacRxGetFreeSync2Data(_D1_INPUT_PORT, pucSdpInfoData);
                }

                break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
            case _D2_INPUT_PORT:

                ucFreeSyncIIInfoReceive = ScalerTmdsMacRxGetSdpInfoFrameReceivedFlag(_D2_INPUT_PORT);
                ucFreeSyncIIInfoChange = _TRUE;

                if((ucFreeSyncIIInfoReceive == _TRUE) && (ucFreeSyncIIInfoChange == _TRUE))
                {
                    ScalerTmdsMacRxGetFreeSync2Data(_D2_INPUT_PORT, pucSdpInfoData);
                }

                break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
            case _D3_INPUT_PORT:

                ucFreeSyncIIInfoReceive = ScalerTmdsMacRxGetSdpInfoFrameReceivedFlag(_D3_INPUT_PORT);
                ucFreeSyncIIInfoChange = _TRUE;

                if((ucFreeSyncIIInfoReceive == _TRUE) && (ucFreeSyncIIInfoChange == _TRUE))
                {
                    ScalerTmdsMacRxGetFreeSync2Data(_D3_INPUT_PORT, pucSdpInfoData);
                }

                break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
            case _D4_INPUT_PORT:

                ucFreeSyncIIInfoReceive = ScalerTmdsMacRxGetSdpInfoFrameReceivedFlag(_D4_INPUT_PORT);
                ucFreeSyncIIInfoChange = _TRUE;

                if((ucFreeSyncIIInfoReceive == _TRUE) && (ucFreeSyncIIInfoChange == _TRUE))
                {
                    ScalerTmdsMacRxGetFreeSync2Data(_D4_INPUT_PORT, pucSdpInfoData);
                }

                break;
#endif
#endif
            default:
                break;
        }

        // Check Version/ Length & InfoFrame receive bit
        if((ucFreeSyncIIInfoReceive == _SDP_STATE_RECEIVED) && (pucSdpInfoData[1] == 0x1A) && (pucSdpInfoData[2] == 0x00) && (pucSdpInfoData[3] == 0x00))
        {
            if((ucFreeSyncIIInfoChange == _TRUE) || (enumFreeSyncIIInfoChgPolling == _HDR_INFO_CHG_POLLING_CHECK_DISABLE))
            {
                stFreeSyncIIData.b1NativeColorSpaceEnable = (bit)(pucSdpInfoData[6] & _BIT3);
                stFreeSyncIIData.b1BacklightControlEnable = (bit)(pucSdpInfoData[6] & _BIT4);
                stFreeSyncIIData.b1LocalDimmingDisable = (bit)(pucSdpInfoData[6] & _BIT5);
                stFreeSyncIIData.b5EOTFType = (pucSdpInfoData[9] & 0x1F);
                stFreeSyncIIData.ucBacklightControlRatio = pucSdpInfoData[10];
                SET_FREESYNC_II_INFO_DATA(enumDisplayRegion, stFreeSyncIIData);
            }
        }
        else
        {
            memset(&stFreeSyncIIData, 0, sizeof(stFreeSyncIIData));

            SET_FREESYNC_II_INFO_DATA(enumDisplayRegion, stFreeSyncIIData);
        }
    }
    else
    {
        SET_FREESYNC_II_INFO_DATA(enumDisplayRegion, stFreeSyncIIData);
    }
}
#endif // End of #if((_FREESYNC_II_SUPPORT == _ON) && (_ULTRA_HDR_SUPPORT == _ON))

#if((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check IVS is Produced by BE, It means IVS falling to Iden only some pixels
// Input Value  : enumInputPort
// Output Value : _TRUE
//--------------------------------------------------
bit ScalerDrrIVSProduceByBE(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    enumSourceType = enumSourceType;
    enumInputPort = enumInputPort;

#if((_DP_SUPPORT == _ON) && (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    if((enumSourceType == _SOURCE_DP) && (ScalerDpRxAuxlessAlpmGetEnable(enumInputPort) == _TRUE))
    {
        return _TRUE;
    }
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((enumSourceType == _SOURCE_DP) && (ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE))
    {
        return _TRUE;
    }
    else
#endif
    {
#if(_HDMI_FRL_SUPPORT == _ON)
        if((enumSourceType == _SOURCE_HDMI) && (ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_FRL_DSC_MAC))
        {
#if(_FW_DSC_FRL_IVS_PRODUCE_BE == _ON)
            return _TRUE;
#endif

#if(_DRR_SUPPORT == _ON)
            if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
            {
                return _TRUE;
            }
#endif
        }
#endif
    }

    return _FALSE;
}
#endif

#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Drr Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDrrUpdateVsyncSetting(void)
{
    // Set VGIP Vsync By Pass
    ScalerDrrSetVsyncBypassWhenIVSProduceByBE();

    // Set Shift one line
    ScalerMemorySetShiftOneLine(ScalerMemoryGetShiftOneLineSupport(), GET_MDOMAIN_INPUT_DATA_PATH());

    // Clr Vsync By pass After I domain Double buffer
    SET_MDOMAIN_VGIP_VSYNC_BY_PASS_AFTER_I_DB(_DISABLE);
}

//--------------------------------------------------
// Description  : Set VGIP Vsync by pass when IVS Produce By BE
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDrrSetVsyncBypassWhenIVSProduceByBE(void)
{
    if(ScalerDrrIVSProduceByBE(GET_MDOMAIN_SOURCE_TYPE(), GET_MDOMAIN_INPUT_PORT()) == _TRUE)
    {
        if(GET_MDOMAIN_VGIP_VSYNC_BY_PASS() == _ENABLE)
        {
            ScalerVgipSetVsBypassEnable(GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
        }
        else
        {
            ScalerVgipSetVsBypassEnable(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
        }
    }
}
#endif

