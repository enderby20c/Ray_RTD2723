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
// ID Code      : RTD2020UserInterfaceArcTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_ARCTX__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceArcTx.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
#if(_AUDIO_ARC_SUPPORT == _ON)
StructArcTxUserInfo g_stArcTxUserInfo;

#if(_AUDIO_EARC_SUPPORT == _ON)
BYTE g_pucArcTxEarcCdsAdb[_CDS_AUDIO_DESCRIPTOR_LENGTH];
BYTE g_pucArcTxEarcCdsSpkAdb[_CDS_SPEAKER_ADB_LENGTH];
// BYTE g_pucEarcCdsSpkLdb[_CDS_SPEAKER_LDB_LENGTH];
// BYTE g_pucEarcCdsRcdb[CDS_RCDB_LENGTH];
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Interface ARC Tx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxHandler(void)
{
    // Implement by user
}

//--------------------------------------------------
// Description  : User Interface ARC Tx EDID Change Check
// Input Value  : None
// Output Value : EnumEdidAudioCapCheckResult
//--------------------------------------------------
EnumEdidAudioCapCheckResult UserInterfaceArcTxEdidChangeCheck(void)
{
    EnumEdidAudioCapCheckResult enumEdidCheckResult = _EDID_AUDIO_CAP_NOT_CHANGED;

#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
    EnumAudioArcMode enumArcLinkStatus = _EARC_ARC_OFF;
    EnumEdidAudioType enumTempEdidType = _EDID_AUDIO_NORMAL;

    /***************************************************************************************/
    // Check Link Mode Change Event
    /***************************************************************************************/

    enumArcLinkStatus = UserCommonArcTxGetLinkMode();

    if(enumArcLinkStatus != GET_ARC_TX_LINK_STATUS())
    {
        // Non ARC(_OFF) -> ARC
        if((enumArcLinkStatus == _ARC_MODE) && (GET_ARC_TX_LINK_STATUS() == _EARC_ARC_OFF))
        {
#if(_HDMI_CEC_SUPPORT == _ON)
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
            UserCommonCecHalStartPollingAudioDescriptor();

            DebugMessageArcTx("[User][ARC Tx]: Start Polling CEC Audio Descriptor", 0);
#endif
#endif
        }
        // ARC -> Non-ARC(_OFF)
        else if((enumArcLinkStatus == _EARC_ARC_OFF) && (GET_ARC_TX_LINK_STATUS() == _ARC_MODE))
        {
#if(_HDMI_CEC_SUPPORT == _ON)
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
            UserCommonCecHalStopPollingAudioDescriptor();

            DebugMessageArcTx("[User][ARC Tx]: Stop Polling CEC Audio Descriptor", 0);
#endif
#endif
        }

        SET_ARC_TX_LINK_STATUS(enumArcLinkStatus);

        DebugMessageArcTx("[User][ARC Tx]: ARC Link Status Change", enumArcLinkStatus);
    }

    // Polling Sink Audio Descriptors
#if(_HDMI_CEC_SUPPORT == _ON)
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
    UserCommonCecHalPollingAudioDescriptorHandler();
#endif
#endif

    /***************************************************************************************/
    // If change event happened, decide edid type according to current status
    /***************************************************************************************/

    if(GET_ARC_TX_LINK_STATUS() == _ARC_MODE)
    {
#if(_HDMI_CEC_SUPPORT == _ON)
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
        if(UserCommonCecHalGetPollingAudioDescriptorResult() == _SINK_AUDIO_DESCRIPTOR_RECEIVED)
        {
            enumTempEdidType = _EDID_AUDIO_ARC;  // ARC connected, ARC output
        }
#endif
#endif
    }
#if(_AUDIO_EARC_SUPPORT == _ON)
    else if((GET_ARC_TX_LINK_STATUS() == _EARC_MODE) && (GET_ARC_TX_EARC_CDS_PARSE_DONE_EVER() == _TRUE))
    {
        enumTempEdidType = _EDID_AUDIO_EARC;  // eARC connected, eARC output
    }
#endif
    else // Link Mode == _OFF
    {
        enumTempEdidType = _EDID_AUDIO_NORMAL;
    }

    /***************************************************************************************/
    // Check if we need to change edid
    /***************************************************************************************/

    // if edid type change
    if(enumTempEdidType != GET_ARC_TX_EDID_TYPE())
    {
        SET_ARC_TX_EDID_TYPE(enumTempEdidType);

#if(_AUDIO_EARC_SUPPORT == _ON)
        if(GET_ARC_TX_EDID_TYPE() == _EDID_AUDIO_EARC)
        {
            CLR_ARC_TX_EARC_CDS_PARSE_DONE();

            UserAdjustArcTxEarcCdsAudioCapabilityInitial(g_pucArcTxEarcCdsAdb, g_pucArcTxEarcCdsSpkAdb);

            DebugMessageArcTx("[User][ARC Tx]: eARC CDS Initial", 0);
        }
        else
        {
            CLR_ARC_TX_EARC_CDS_PARSE_DONE_EVER();
            CLR_ARC_TX_EARC_CDS_PARSE_DONE();
        }
#endif

        DebugMessageArcTx("[User][ARC Tx]: EDID Type Change", enumTempEdidType);

        enumEdidCheckResult = _EDID_AUDIO_CAP_CHANGED;
    }

#if(_AUDIO_EARC_SUPPORT == _ON)
    // eARC CDS change, Highest priority
    if(GET_ARC_TX_EARC_CDS_PARSE_DONE() == _TRUE)
    {
        CLR_ARC_TX_EARC_CDS_PARSE_DONE();

        if(UserAdjustArcTxEarcCheckCdsCapChange(g_pucArcTxEarcCdsAdb, g_pucArcTxEarcCdsSpkAdb) == _TRUE)
        {
            DebugMessageArcTx("[User][ARC Tx]: eARC CDS Change", 0);

            enumEdidCheckResult = _EDID_AUDIO_CAP_CHANGED;
        }
    }
#endif
#elif(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_USER)
    // Implement by user
#endif

    return enumEdidCheckResult;
}

//--------------------------------------------------
// Description  : User Interface ARC Tx EDID Audio Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxEdidAudioCapabilitySwitch(void)
{
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
    BYTE ucTemp = 0;
    BYTE ucInputPort = _NO_INPUT_PORT;
    EnumPortType enumPortType = _PORT_NONE;

    for(ucTemp = 0; ucTemp < _INPUT_PORT_VALID; ucTemp++)
    {
        ucInputPort = SysSourceGetSpecificInputPort(ucTemp);
        enumPortType = SysSourceGetPortTypeFromInputPort(ucInputPort);

#if((_DP_SUPPORT == _ON) && (_EMBEDDED_EDID_SUPPORT == _ON))
        if(enumPortType == _PORT_DP)
        {
            UserCommonEdidSwitchDpEdid(ucInputPort);
        }
#endif

#if((_HDMI_SUPPORT == _ON) && (_HDMI_MULTI_EDID_SUPPORT == _ON))
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
        // Non-ARC port toggle physcial HPD pin, ARC port in eARC mode toggle pseudo HPD_Status
        if((enumPortType == _PORT_HDMI) &&
           ((UserCommonArcTxGetArcOutputPort() != ucInputPort) || ((UserCommonArcTxGetArcOutputPort() == ucInputPort) && (GET_ARC_TX_EDID_TYPE() == _EDID_AUDIO_EARC))))
#else
        // ITE don't support pseudo HPD_Status Toggle, only toggle Non-ARC port physical HPD pin
        if((enumPortType == _PORT_HDMI) && (UserCommonArcTxGetArcOutputPort() != ucInputPort))
#endif
        {
            UserCommonEdidSwitchHdmiEdid(ucInputPort, UserInterfaceEdidGetMultiHdmiEdidIndex(ucInputPort));
        }
#endif
    }
#elif(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_USER)
    // Implement by user
#endif
}

#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_USER)
//--------------------------------------------------
// Description  : User Interface ARC Tx Modify EDID
// Input Value  : pucEdidAddr, pusCtaDataBlockAddr
// Output Value : EnumEdidAudioCapModifyResult
//--------------------------------------------------
EnumEdidAudioCapModifyResult UserInterfaceArcTxEdidModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr)
{
    pucEdidAddr = pucEdidAddr;
    pusCtaDataBlockAddr = pusCtaDataBlockAddr;

    return _EDID_AUDIO_CAP_MODIFY_FAIL;
}
#endif // End of #if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_USER)

//--------------------------------------------------
// Description  : Get Modify EDID Enable
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
EnumEdidAudioCapModifyEnable UserInterfaceArcTxEdidGetModifyEnable(void)
{
    EnumEdidAudioCapModifyEnable enumEdidAudioCapModifyEnable = _EDID_AUDIO_CAP_DO_NOT_MODIFY;

#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
    if(GET_ARC_TX_EDID_TYPE() != _EDID_AUDIO_NORMAL)
    {
        enumEdidAudioCapModifyEnable = _EDID_AUDIO_CAP_NEED_TO_MODIFY;
    }
#elif(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_USER)
    // Implement by user
#endif

    return enumEdidAudioCapModifyEnable;
}

//--------------------------------------------------
// Description  : Get EDID Audio Type
// Input Value  : None
// Output Value : EnumEdidAudioType
//--------------------------------------------------
EnumEdidAudioType UserInterfaceArcTxEdidGetType(void)
{
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
    return GET_ARC_TX_EDID_TYPE();
#elif(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_USER)
    // Implement by user
    return _EDID_AUDIO_NORMAL;
#endif
}

//--------------------------------------------------
// Description  : User Interface ARC Tx OSD Change Process(eARC/ARC/OFF)
// Input Value  : enumArcMode
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxOsdChangeProc(EnumAudioArcMode enumArcMode)
{
    enumArcMode = enumArcMode;

    return;
}

#if(_AUDIO_EARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Interface eARC Tx Get Input Port Edid Has Audio Capability
// Input Value  : enumInputPort
// Output Value : EnumEdidAudioBlockExistStatus
//--------------------------------------------------
EnumEdidAudioBlockExistStatus UserInterfaceArcTxCheckInputPortEdidHasAudioCapability(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    return _CURRENT_EDID_WITH_AUDIO_BLOCK;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx Get Downgrade to ARC Permission
// Input Value  : None
// Output Value : EnumArcCompatibleType
//--------------------------------------------------
EnumArcCompatibleType UserInterfaceArcTxEarcGetDowngradeToArcPermission(void)
{
    if(UserInterfaceCecGetOsdCecEnable() == _CEC_OSD_ENABLE)
    {
        return _ARC_COMPATIBLE_VALID;
    }

    return _ARC_COMPATIBLE_INVALID;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx notify user to check EDID audio block and decide whether change EDID or not
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxEarcCdsParseDoneNotify(void)
{
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
    SET_ARC_TX_EARC_CDS_PARSE_DONE_EVER();
    SET_ARC_TX_EARC_CDS_PARSE_DONE();
#elif(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_USER)
    // Implement by user
#endif
}

#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
//--------------------------------------------------
// Description  : User Interface eARC Tx CDS Audio Capability Initial
// Input Value  : pucCurrentArcTxEarcCdsAdb, pucCurrentArcTxEarcCdsSpkAdb
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxEarcGetCdsAudioCapability(BYTE *pucCurrentArcTxEarcCdsAdb, BYTE *pucCurrentArcTxEarcCdsSpkAdb)
{
    memset(pucCurrentArcTxEarcCdsAdb, 0, sizeof(pucCurrentArcTxEarcCdsAdb));
    memset(pucCurrentArcTxEarcCdsSpkAdb, 0, sizeof(pucCurrentArcTxEarcCdsSpkAdb));
    // memset(pucCurrentEarcCdsSpkLdb, 0, sizeof(pucCurrentEarcCdsSpkLdb));
    // memset(pucCurrentEarcCdsRcdb, 0, sizeof(pucCurrentEarcCdsRcdb));

    memcpy(pucCurrentArcTxEarcCdsAdb, &g_pucArcTxEarcCdsAdb, sizeof(g_pucArcTxEarcCdsAdb));
    memcpy(pucCurrentArcTxEarcCdsSpkAdb, &g_pucArcTxEarcCdsSpkAdb, sizeof(g_pucArcTxEarcCdsSpkAdb));
    // memcpy(pucCurrentEarcCdsSpkLdb, &g_pucArcTxEarcCdsSpkLdb, sizeof(g_pucAg_pucArcTxEarcCdsSpkLdbrcTxEarcCdsAdb));
    // memcpy(pucCurrentEarcCdsRcdb, &g_pucArcTxEarcCdsRcdb, sizeof(g_pucArcTxEarcCdsRcdb));
}
#endif // #if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
#endif // #if(_AUDIO_EARC_SUPPORT == _ON)

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
//--------------------------------------------------
// Description  : User Interface ARC Tx Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxMuteProc(bit bMute)
{
    bMute = bMute;

    return;
}

//--------------------------------------------------
// Description  : User Interface Arc Tx ARC Mode Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxArcModeInitial(void)
{
    return;
}

//--------------------------------------------------
// Description  : User Interface ARC Tx ARC Mode Output Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxArcModeOutputReset(void)
{
    return;
}

//--------------------------------------------------
// Description  : User Interface ARC Tx Audio Output Format Setting
// Input Value  : EnumArcAudioChanelStatus, StructAudioInterfaceInfoForArc
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxAudioOutputFormatSetting(EnumArcAudioChanelStatus enumArcOsdChannelNum, StructAudioInterfaceInfoForArc stArcAudioSourceInfo)
{
    enumArcOsdChannelNum = enumArcOsdChannelNum;
    stArcAudioSourceInfo = stArcAudioSourceInfo;

    return;
}

//--------------------------------------------------
// Description  : User Interface ARC Tx Stream Handler
// Input Value  : None
// Output Value : EnumArcOutputStreamStatus
//--------------------------------------------------
EnumArcOutputStreamStatus UserInterfaceArcTxStreamHandler(void)
{
    return _ARC_OUTPUT_STREAM_NOT_READY;
}

//--------------------------------------------------
// Description  : User Interface ARC Tx Stable Detect
// Input Value  : None
// Output Value : EnumArcOutputStableDetectResult
//--------------------------------------------------
EnumArcOutputStableDetectResult UserInterfaceArcTxStableDetect(void)
{
    return _ARC_OUTPUT_UNSTABLE;
}

//----------------------------------------
// Description  : User Interface ARC Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxInitial(EnumAudioArcMode enumArcMode)
{
    enumArcMode = enumArcMode;

    return;
}

//----------------------------------------
// Description  : User Interface ARC Tx Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxDisable(void)
{
    return;
}

#if(_AUDIO_EARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Interface eARC Tx Output Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxEarcModeOutputReset(void)
{
    return;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx Check Discovery Pass
// Input Value  : None
// Output Value : EnumEarcDiscoveryResult
//--------------------------------------------------
EnumEarcDiscoveryResult UserInterfaceArcTxEarcCheckDiscoveryPass(void)
{
    return _EARC_DISCOVERY_NOT_STARTED_OR_TIMEOUT;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx Check Discovery Timeout
// Input Value  : None
// Output Value : EnumEarcDiscoveryTimeoutStatus
//--------------------------------------------------
EnumEarcDiscoveryTimeoutStatus UserInterfaceArcTxEarcCheckDiscoveryTimeout(void)
{
    return _EARC_DISCOVERY_NO_TIMEOUT;
}


//--------------------------------------------------
// Description  : User Interface eARC Tx Stream Handler
// Input Value  : None
// Output Value : EnumArcOutputStreamStatus
//--------------------------------------------------
EnumArcOutputStreamStatus UserInterfaceArcTxEarcStreamHandler(void)
{
    return _ARC_OUTPUT_STREAM_NOT_READY;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx Check Audio Latency Update
// Input Value  : pucAudioLatency
// Output Value : EnumEarcAudioLatencyUpdateStatus
//--------------------------------------------------
EnumEarcAudioLatencyUpdateStatus UserInterfaceArcTxEarcCheckAudioLatencyUpdate(BYTE *pucAudioLatency)
{
    pucAudioLatency = pucAudioLatency;

    return _EARC_AUDIO_LATENCY_NO_UPDATE;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx Set Request Audio Latency
// Input Value  : ucAudioLatency
// Output Value : EnumEarcRequestAudioLatencyResult
//--------------------------------------------------
EnumEarcRequestAudioLatencyResult UserInterfaceArcTxEarcSetRequestAudioLatency(BYTE ucAudioLatency)
{
    ucAudioLatency = ucAudioLatency;

    return _EARC_REQUEST_AUDIO_LATENCY_FAIL;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx Check CDS Update
// Input Value  : None
// Output Value : EnumEarcCdsUpdateStatus
//--------------------------------------------------
EnumEarcCdsUpdateStatus UserInterfaceArcTxEarcCheckCdsUpdate(void)
{
    return _EARC_CDS_NO_UPDATE;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx CDS Reload
// Input Value  : pucEarcRxCdsTable
// Output Value : EnumEarcCdsReloadResult
//--------------------------------------------------
EnumEarcCdsReloadResult UserInterfaceArcTxEarcCdsReload(BYTE *pucEarcRxCdsTable)
{
    pucEarcRxCdsTable = pucEarcRxCdsTable;

    return _EARC_CDS_RELOAD_FAIL;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx Set Mute Flag
// Input Value  : EnumAudioMuteStatus
// Output Value : None
//--------------------------------------------------
void UserInterfaceArcTxEarcSetChStatusMuteFlag(EnumAudioMuteStatus enumArcMute)
{
    enumArcMute = enumArcMute;

    return;
}

//--------------------------------------------------
// Description  : User Interface eARC Tx Get Mute Flag
// Input Value  : None
// Output Value : EnumAudioMuteStatus
//--------------------------------------------------
EnumAudioMuteStatus UserInterfaceArcTxEarcGetChStatusMuteFlag(void)
{
    return _AUDIO_MUTE_OFF;
}
#endif // #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

