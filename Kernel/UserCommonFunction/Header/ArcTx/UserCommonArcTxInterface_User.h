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
// ID Code      : UserCommonArcTxInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_ARC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _EDID_AUDIO_NORMAL = 0,
    _EDID_AUDIO_EARC,
    _EDID_AUDIO_ARC,
} EnumEdidAudioType;

typedef enum
{
    _CURRENT_EDID_WITHOUT_AUDIO_BLOCK = 0x00,
    _CURRENT_EDID_WITH_AUDIO_BLOCK,
} EnumEdidAudioBlockExistStatus;

typedef enum
{
    _ARC_COMPATIBLE_INVALID = 0x00,
    _ARC_COMPATIBLE_VALID,
} EnumArcCompatibleType;

typedef enum
{
    _ARC_OUTPUT_STREAM_NOT_READY = 0x00,
    _ARC_OUTPUT_STREAM_READY,
} EnumArcOutputStreamStatus;

typedef enum
{
    _ARC_OUTPUT_UNSTABLE = 0x00,
    _ARC_OUTPUT_STABLE,
} EnumArcOutputStableDetectResult;

typedef enum
{
    _EDID_AUDIO_CAP_NOT_CHANGED = 0x00,
    _EDID_AUDIO_CAP_CHANGED,
} EnumEdidAudioCapCheckResult;

typedef enum
{
    _EDID_AUDIO_CAP_MODIFY_FAIL = 0x00,
    _EDID_AUDIO_CAP_MODIFY_SUCCESS,
} EnumEdidAudioCapModifyResult;

typedef enum
{
    _EDID_AUDIO_CAP_DO_NOT_MODIFY = 0x00,
    _EDID_AUDIO_CAP_NEED_TO_MODIFY,
} EnumEdidAudioCapModifyEnable;

#if(_AUDIO_EARC_SUPPORT == _ON)
typedef enum
{
    _EARC_DISCOVERY_NOT_STARTED_OR_TIMEOUT = 0x00,
    _EARC_DISCOVERY_ENTER_EARC_MODE,
} EnumEarcDiscoveryResult;

typedef enum
{
    _EARC_DISCOVERY_NO_TIMEOUT = 0x00,
    _EARC_DISCOVERY_TIMEOUT,
} EnumEarcDiscoveryTimeoutStatus;

typedef enum
{
    _EARC_AUDIO_LATENCY_NO_UPDATE = 0x00,
    _EARC_AUDIO_LATENCY_IS_UPDATED,
} EnumEarcAudioLatencyUpdateStatus;

typedef enum
{
    _EARC_REQUEST_AUDIO_LATENCY_FAIL = 0x00,
    _EARC_REQUEST_AUDIO_LATENCY_SUCCESS,
} EnumEarcRequestAudioLatencyResult;

typedef enum
{
    _EARC_CDS_NO_UPDATE = 0x00,
    _EARC_CDS_IS_UPDATED,
} EnumEarcCdsUpdateStatus;

typedef enum
{
    _EARC_CDS_RELOAD_FAIL = 0x00,
    _EARC_CDS_RELOAD_SUCCESS,
} EnumEarcCdsReloadResult;
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumAudioArcMode UserCommonArcTxGetLinkMode(void);
extern EnumInputPort UserCommonArcTxGetArcInputPort(void);
extern EnumInputPort UserCommonArcTxGetArcOutputPort(void);
extern EnumAudioState UserCommonArcTxGetArcAudioState(void);
extern void UserCommonArcTxRetryArcEarcByHpdToggle(void);

#if(_AUDIO_EARC_SUPPORT == _ON)
extern void UserCommonArcTxEarcGetCdsInfo(StructArcTxEarcCdsInfo *pstEarcRxCdsInfo);
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)