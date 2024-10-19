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
// ID Code      : UserCommonArcTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_ARCTX__

#include "UserCommonInclude.h"
#include "ArcTx/UserCommonArcTx.h"

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
#warning "NOTE: _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST is Only Used for Test!!!"
#endif
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
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
// Description  : User Common ARC Tx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxHandler(void)
{
    // User behavior can be placed here
    UserInterfaceArcTxHandler();

    // Check if the EDID audio block needs to be replaced
    if(UserInterfaceArcTxEdidChangeCheck() == _EDID_AUDIO_CAP_CHANGED)
    {
        // Modify EDID audio block and toggle HPD
        UserInterfaceArcTxEdidAudioCapabilitySwitch();
    }
}

//--------------------------------------------------
// Description  : User Common ARC Tx Get Link Mode
// Input Value  : None
// Output Value : EnumAudioArcMode
//--------------------------------------------------
EnumAudioArcMode UserCommonArcTxGetLinkMode(void)
{
    return GET_AUDIO_ARC_TX_LINK_MODE();
}

//--------------------------------------------------
// Description  : User Common ARC Tx Get ARC Audio Inputport
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort UserCommonArcTxGetArcInputPort(void)
{
    return GET_AUDIO_PATH_INPUT_PORT(SysAudioGetAudioPath(_AUDIO_ARC_OUT));
}

//--------------------------------------------------
// Description  : User Common ARC Tx Get ARC Audio Inputport
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort UserCommonArcTxGetArcOutputPort(void)
{
    return ScalerAudioGetArcDxPort();
}

//--------------------------------------------------
// Description  : User Common eARC Tx Retry ARC/eARC By HPD Toggle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxRetryArcEarcByHpdToggle(void)
{
    SET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE();

    DebugMessageArcTx("[ARC Tx] Trigger ARC Port HPD Toggle by User!!!", 0x00);
}

//--------------------------------------------------
// Description  : User Common ARC Tx Get Arc Audio State
// Input Value  : None
// Output Value : EnumAudioState
//--------------------------------------------------
EnumAudioState UserCommonArcTxGetArcAudioState(void)
{
    return GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT));
}

//--------------------------------------------------
// Description  : User Common ARC Tx Modify EDID
// Input Value  : pucEdidAddr, pusCtaDataBlockAddr
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonArcTxEdidModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr)
{
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
    BYTE pucAudioDataBlock[31] = {0x23, 0x09, 0x07, 0x07};
    BYTE pucSpkAudioDataBlock[4] = {0x83, 0x01, 0x00, 0x00};

#if(_HDMI_CEC_SUPPORT == _ON)
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
    StructCecAudioDescriptorInfo stAudioDescriptorInfo;
#endif
#endif

#if(_AUDIO_EARC_SUPPORT == _ON)
    if(UserInterfaceArcTxEdidGetType() == _EDID_AUDIO_EARC)
    {
        UserInterfaceArcTxEarcGetCdsAudioCapability(pucAudioDataBlock, pucSpkAudioDataBlock);
    }
    else
#endif
    {
#if(_HDMI_CEC_SUPPORT == _ON)
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
        memset(&stAudioDescriptorInfo, 0, sizeof(stAudioDescriptorInfo));

        UserCommonCecHalGetSinkAudioDescriptorInfo(&stAudioDescriptorInfo);

        if((stAudioDescriptorInfo.ucAudioDescriptorLength > 0) && (stAudioDescriptorInfo.pucBufferPtr != NULL))
        {
            memset(pucAudioDataBlock, 0, sizeof(pucAudioDataBlock));

            pucAudioDataBlock[0] = (0x20 | (stAudioDescriptorInfo.ucAudioDescriptorLength & 0x1F));
            memcpy(&pucAudioDataBlock[1], stAudioDescriptorInfo.pucBufferPtr, stAudioDescriptorInfo.ucAudioDescriptorLength);
        }
        else
        {
            DebugMessageArcTx("[User][ARC Tx]: Sink Audio Descriptor Empty!!!", 0);
        }
#endif
#endif
    }

    // Remove Audio Capability
    UserCommonEdidRemoveCtaDataBlockProc(pucEdidAddr, pusCtaDataBlockAddr, _CTA_ADB);

    UserCommonEdidRemoveCtaDataBlockProc(pucEdidAddr, pusCtaDataBlockAddr, _CTA_SPK_ADB);
    // UserCommonEdidRemoveCtaDataBlockProc(pucEdidAddr, pusCtaDataBlockAddr, _CTA_SPK_LDB);
    // UserCommonEdidRemoveCtaDataBlockProc(pucEdidAddr, pusCtaDataBlockAddr, _CTA_RCDB);

    // Add Audio Capability
    if(UserCommonEdidAddCtaDataBlockProc(pucEdidAddr, pusCtaDataBlockAddr, _CTA_ADB, pucAudioDataBlock) == _FALSE)
    {
        return _FALSE;
    }

    if(UserCommonEdidAddCtaDataBlockProc(pucEdidAddr, pusCtaDataBlockAddr, _CTA_SPK_ADB, pucSpkAudioDataBlock) == _FALSE)
    {
        return _FALSE;
    }

    /*if(GET_ARC_TX_EDID_TYPE() == _EDID_AUDIO_EARC)
    {
        if(UserCommonEdidAddCtaExtTagDataBlockProc(pucEdidAddr, pusCtaDataBlockAddr, _CTA_SPK_LDB, g_pucEarcCdsSpkLdb) == _FALSE)
        {
            return _FALSE;
        }

        if(UserCommonEdidAddCtaExtTagDataBlockProc(pucEdidAddr, pusCtaDataBlockAddr, _CTA_RCDB, g_pucEarcCdsRcdb) == _FALSE)
        {
            return _FALSE;
        }
    }*/
#elif(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_USER)
    // Implement by user
    if(UserInterfaceArcTxEdidModify(pucEdidAddr, pusCtaDataBlockAddr) == _EDID_AUDIO_CAP_MODIFY_FAIL)
    {
        return _FALSE;
    }
#endif

    return _TRUE;
}

#if(_AUDIO_EARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Common eARC Tx notify user to check EDID audio block and decide whether change EDID or not
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxEarcCdsParseDoneNotify(void)
{
    UserInterfaceArcTxEarcCdsParseDoneNotify();
}

//--------------------------------------------------
// Description  : User Common eARC Tx Get CDS Info
// Input Value  : pstEarcRxCdsInfo
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxEarcGetCdsInfo(StructArcTxEarcCdsInfo *pstEarcRxCdsInfo)
{
    memcpy(pstEarcRxCdsInfo, &g_stAudioEarcRxCdsInfo, sizeof(StructArcTxEarcCdsInfo));
}

//--------------------------------------------------
// Description  : User Common eARC Tx Get Initiate Permission
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit UserCommonArcTxEarcGetInitiatePermission(void)
{
    if((UserInterfaceArcTxCheckInputPortEdidHasAudioCapability(ScalerAudioGetArcDxPort()) == _TRUE) &&
       (GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) != _AUDIO_STATUS_SETTING))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : User Common eARC Tx Get Downgrade to ARC Permission
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonArcTxEarcGetDowngradeToArcPermission(void)
{
    return UserInterfaceCecGetOsdCecEnable();
}
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
//--------------------------------------------------
// Description  : User Common ARC Tx Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxMuteProc(bit bMute)
{
    UserInterfaceArcTxMuteProc(bMute);
}

//--------------------------------------------------
// Description  : User Common Arc Tx ARC Mode Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxArcModeInitial(void)
{
    UserInterfaceArcTxArcModeInitial();
}

//--------------------------------------------------
// Description  : User Common ARC Tx ARC Mode Output Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxArcModeOutputReset(void)
{
    UserInterfaceArcTxArcModeOutputReset();
}

//--------------------------------------------------
// Description  : User Common ARC Tx Audio Output Format Setting
// Input Value  : EnumArcAudioChanelStatus, StructAudioInterfaceInfoForArc
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxAudioOutputFormatSetting(EnumArcAudioChanelStatus enumArcOsdChannelNum, StructAudioInterfaceInfoForArc stArcAudioSourceInfo)
{
    UserInterfaceArcTxAudioOutputFormatSetting(enumArcOsdChannelNum, stArcAudioSourceInfo);
}

//--------------------------------------------------
// Description  : User Common ARC Tx Stream Handler
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonArcTxStreamHandler(void)
{
    if(UserInterfaceArcTxStreamHandler() == _ARC_OUTPUT_STREAM_READY)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common ARC Tx Stable Detect
// Input Value  : None
// Output Value : _STABLE/_UNSTABLE
//--------------------------------------------------
bit UserCommonArcTxStableDetect(void)
{
    if(UserInterfaceArcTxStableDetect() == _ARC_OUTPUT_STABLE)
    {
        return _STABLE;
    }

    return _UNSTABLE;
}

//----------------------------------------
// Description  : User Common ARC Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxInitial(EnumAudioArcMode enumArcMode)
{
    UserInterfaceArcTxInitial(enumArcMode);
}

//----------------------------------------
// Description  : User Common ARC Tx Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxDisable(void)
{
    UserInterfaceArcTxDisable();
}

//--------------------------------------------------
// Description  : User Common ARC Tx OSD Change Process(eARC/ARC/OFF)
// Input Value  : enumArcMode
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxOsdChangeProc(EnumAudioArcMode enumArcMode)
{
    UserInterfaceArcTxOsdChangeProc(enumArcMode);
}

#if(_AUDIO_EARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Common eARC Tx Output Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxEarcModeOutputReset(void)
{
    UserInterfaceArcTxEarcModeOutputReset();
}

//--------------------------------------------------
// Description  : User Common eARC Tx Check Discovery Pass
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit UserCommonArcTxEarcCheckDiscoveryPass(void)
{
    if(UserInterfaceArcTxEarcCheckDiscoveryPass() == _EARC_DISCOVERY_ENTER_EARC_MODE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common eARC Tx Check Discovery Timeout
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit UserCommonArcTxEarcCheckDiscoveryTimeout(void)
{
    if(UserInterfaceArcTxEarcCheckDiscoveryTimeout() == _EARC_DISCOVERY_TIMEOUT)
    {
        return _TRUE;
    }

    return _FALSE;
}


//--------------------------------------------------
// Description  : User Common eARC Tx Stream Handler
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit UserCommonArcTxEarcStreamHandler(void)
{
    if(UserInterfaceArcTxEarcStreamHandler() == _ARC_OUTPUT_STREAM_READY)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common eARC Tx Check Audio Latency Update
// Input Value  : pucAudioLatency
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit UserCommonArcTxEarcCheckAudioLatencyUpdate(BYTE *pucAudioLatency)
{
    if(UserInterfaceArcTxEarcCheckAudioLatencyUpdate(pucAudioLatency) == _EARC_AUDIO_LATENCY_IS_UPDATED)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common eARC Tx Set Request Audio Latency
// Input Value  : ucAudioLatency
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit UserCommonArcTxEarcSetRequestAudioLatency(BYTE ucAudioLatency)
{
    if(UserInterfaceArcTxEarcSetRequestAudioLatency(ucAudioLatency) == _EARC_REQUEST_AUDIO_LATENCY_SUCCESS)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common eARC Tx Check CDS Update
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit UserCommonArcTxEarcCheckCdsUpdate(void)
{
    if(UserInterfaceArcTxEarcCheckCdsUpdate() == _EARC_CDS_IS_UPDATED)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common eARC Tx CDS Reload
// Input Value  : pucEarcRxCdsTable
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonArcTxEarcCdsReload(BYTE *pucEarcRxCdsTable)
{
    if(UserInterfaceArcTxEarcCdsReload(pucEarcRxCdsTable) == _EARC_CDS_RELOAD_SUCCESS)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common eARC Tx Set Mute Flag
// Input Value  : EnumAudioMuteStatus
// Output Value : None
//--------------------------------------------------
void UserCommonArcTxEarcSetChStatusMuteFlag(EnumAudioMuteStatus enumArcMute)
{
    UserInterfaceArcTxEarcSetChStatusMuteFlag(enumArcMute);
}

//--------------------------------------------------
// Description  : User Common eARC Tx Get Mute Flag
// Input Value  : None
// Output Value : EnumAudioMuteStatus
//--------------------------------------------------
EnumAudioMuteStatus UserCommonArcTxEarcGetChStatusMuteFlag(void)
{
    return UserInterfaceArcTxEarcGetChStatusMuteFlag();
}
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)