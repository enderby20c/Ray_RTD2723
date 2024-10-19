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
// ID Code      : RTD2020UserInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include <Global.h>
#include <Project.h>

#include <ScalerFunctionInterface_User.h>
#include <SysInterface_User.h>
#include <UserCommonInterface_User.h>

#include <UserInterfaceFunction_Api.h>

#include _OSD_INCLUDE
#include _FACTORY_INCLUDE

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_USB_HUB_SUPPORT == _ON)
#define GET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX()        (g_enumUsbHubSwitchInputPortIndex)
#define SET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX(x)       (g_enumUsbHubSwitchInputPortIndex = (x))
#endif

//--------------------------------------------------
// Definitions of DCR THD Setting
//--------------------------------------------------
#define _DCR_THESHOLD1                                  0x20
#define _DCR_THESHOLD2                                  0x180

#define _IAPS_SOFTCLAMP_VALUE                           0xB0
#define _IAPS_SOFTCLAMP_REG_INV_VALUE                   0xB0
#define _IAPS_GAIN_VALUE                                0x2000
#define _IAPS_GAIN_REG_INV_VALUE                        0x2000

//--------------------------------------------------
// Definitions of DEMO Mode Setting
//--------------------------------------------------
#if(_COLOR_DEMO_FUNCTION == _ON)
#define _HLWIN_TYPE5_MOVE_TIME                          SEC(0.01)
#endif

//--------------------------------------------------
// Definitions of PIXEL SHIFT
//--------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
#define _PIXEL_SHIFT_NUM_H                              2
#define _PIXEL_SHIFT_NUM_V                              2
#define _PIXEL_SHIFT_TIME                               10
#endif

//--------------------------------------------------
// Definitions of MRCM Crosshair
//--------------------------------------------------
#if(_MRCM_SUPPORT == _ON)
#define _MRCM_CROSSHAIR_H_STEP                          20
#define _MRCM_CROSSHAIR_V_STEP                          18
#define _MRCM_CROSSHAIR_REGION_PIXEL_NUM                (_MRCM_CROSSHAIR_H_STEP * _MRCM_CROSSHAIR_V_STEP)
#endif

//--------------------------------------------------
// Macro of Crosshair
//--------------------------------------------------
#define SET_OSD_CROSSHAIR_SHOW()                        (g_bOsdCrosshairShow = _TRUE)
#define CLR_OSD_CROSSHAIR_SHOW()                        (g_bOsdCrosshairShow = _FALSE)
#define GET_OSD_CROSSHAIR_SHOW()                        (g_bOsdCrosshairShow)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_PIXEL_SHIFT_SUPPORT == _ON)
//  -2->
// ^    |
// |    3
// 1    |
// |    v
// < -0- <-7-
//      |     |
//      4     6
//      |     |
//      v -5->
typedef enum
{
    _PIXEL_SHIFT_DEFAULT = 0x00,

    _PIXEL_SHIFT_STEP0_TURN_LEFT = _BIT0,
    _PIXEL_SHIFT_STEP1_TURN_UP = _BIT1,
    _PIXEL_SHIFT_STEP2_TURN_RIGHT = _BIT2,
    _PIXEL_SHIFT_STEP3_TURN_DOWN = _BIT3,
    _PIXEL_SHIFT_STEP4_TURN_DOWN = _BIT4,
    _PIXEL_SHIFT_STEP5_TURN_RIGHT = _BIT5,
    _PIXEL_SHIFT_STEP6_TURN_UP = _BIT6,
    _PIXEL_SHIFT_STEP7_TURN_LEFT = _BIT7,

    _PIXEL_SHIFT_DONE = _PIXEL_SHIFT_STEP7_TURN_LEFT,
} EnumPixelShiftState;
#endif

#if(_OD_FUNCTION == _ON)
typedef enum
{
    _OD_COMMON_TABLE,
    _OD_FREESYNC_TABLE,
} EnumODTableGroup;
#endif

//--------------------------------------------------
// Enum for TTS Play Event
//--------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
typedef enum
{
    _AUDIO_TTS_EVENT_NONE = 0,

    // Power Action
    _AUDIO_TTS_EVENT_POWER_ON,
    _AUDIO_TTS_EVENT_POWER_OFF,
    _AUDIO_TTS_EVENT_POWER_SAVING,
    _AUDIO_TTS_EVENT_POWER_NORMAL,

    // Key Operation
    _AUDIO_TTS_EVENT_KEY_MENU,
    _AUDIO_TTS_EVENT_KEY_LEFT,
    _AUDIO_TTS_EVENT_KEY_RIGHT,
    _AUDIO_TTS_EVENT_KEY_ENTER,
    _AUDIO_TTS_EVENT_KEY_BACK,
    _AUDIO_TTS_EVENT_KEY_ON,
    _AUDIO_TTS_EVENT_KEY_OFF,
    _AUDIO_TTS_EVENT_KEY_INCREASE,
    _AUDIO_TTS_EVENT_KEY_DECREASE,
    _AUDIO_TTS_EVENT_KEY_NUMBER,
    _AUDIO_TTS_EVENT_KEY_ANALOG,
    _AUDIO_TTS_EVENT_KEY_DIGITAL,

    // OSD Page 1
    _AUDIO_TTS_EVENT_OSD_LOGO_SHOW,
    _AUDIO_TTS_EVENT_OSD_PICTURE,
    _AUDIO_TTS_EVENT_OSD_DISPLAY_CONFIG,
    _AUDIO_TTS_EVENT_OSD_COLOR,
    _AUDIO_TTS_EVENT_OSD_ADVANCE,
    _AUDIO_TTS_EVENT_OSD_INPUT_SOURCE,
    _AUDIO_TTS_EVENT_OSD_AUDIO,
    _AUDIO_TTS_EVENT_OSD_OTHER,
    _AUDIO_TTS_EVENT_OSD_DISPLAY_INFORMATION,
    _AUDIO_TTS_EVENT_OSD_FACTORY,

    // OSD Audio Page 2
    _AUDIO_TTS_EVENT_OSD_AUDIO_VOLUME,
    _AUDIO_TTS_EVENT_OSD_AUDIO_MUTE,
    _AUDIO_TTS_EVENT_OSD_AUDIO_STAND_ALONG,
    _AUDIO_TTS_EVENT_OSD_AUDIO_SOURCE,
    _AUDIO_TTS_EVENT_OSD_AUDIO_MODE,
    _AUDIO_TTS_EVENT_OSD_AUDIO_TTS,
    _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_SUPPORT,
    _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_TEXT_VOLUME,
    _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_MUSIC_VOLUME,

    // OSD Input Source Page
    _AUDIO_TTS_EVENT_OSD_INPUT_AUTO,
    _AUDIO_TTS_EVENT_OSD_INPUT_A0,
    _AUDIO_TTS_EVENT_OSD_INPUT_D0,
    _AUDIO_TTS_EVENT_OSD_INPUT_D1,
    _AUDIO_TTS_EVENT_OSD_INPUT_D2,
    _AUDIO_TTS_EVENT_OSD_INPUT_D3,
    _AUDIO_TTS_EVENT_OSD_INPUT_D4,
    _AUDIO_TTS_EVENT_OSD_INPUT_D5,
    _AUDIO_TTS_EVENT_OSD_INPUT_D6,
} EnumAudioTtsEvent;
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_USB_HUB_SUPPORT == _ON)
extern EnumInputPort g_enumUsbHubSwitchInputPortIndex;
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
extern EnumPixelShiftState g_enumPixelShiftState;
#endif


extern void (*code tOperationTable[])(void);

#if(_DCC_FUNCTION == _ON)
extern EnumSelRegion g_enumColorDCCMeasureRegion;
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
extern bit g_bColorLocalDimmingHdrBoost;
#endif
#endif

extern bit g_bOsdCrosshairShow;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void RTDOsdSystemFlowProc(void);
extern void RTDOsdEventMsgProc(void);
extern void RTDDdcciHandler(void);
extern void RTDDdcciGetInputMsg(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserAdjust.c
//----------------------------------------------------------------------------------------
#if(_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON)
#if((_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
extern EnumEdidModifyTarget UserAdjustGetEdidModifyTarget(EnumInputPort enumInputPort);
#endif
#endif

extern EnumDisplayMode UserAdjustGetMultiDisplayMode(void);
extern EnumDDCCIDebugMode UserAdjustDdcciGetStatus(void);
extern void UserAdjustResetDisplayByPort(EnumDisplayRegion enumDisplayRegion);

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
extern void UserAdjustDpVersionForceUpdate(EnumInputPort enumInputPort, bit bEnable, EnumOSDDpPortVersionDef enumOSDDpPortVersionDef);
#endif
//-------------------------------------------------------
// Adjust Backlight
//-------------------------------------------------------
extern void UserAdjustBacklight(WORD usBacklight);

//-------------------------------------------------------
// Get External HDMI Edid Index
//-------------------------------------------------------
#if((_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE) && ((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON)))
extern EnumEdidSelection UserAdjustGetHdmiExternalEdidIndex(EnumInputPort enumInputPort);
#endif

//-------------------------------------------------------
// Dp Load Edid Related
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
extern EnumEdidSelection UserAdjustGetDpEdidIndex(EnumInputPort enumInputPort);
#endif

//-------------------------------------------------------
// Audio Related
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
extern void UserAdjustAudioTtsPlayEvent(EnumAudioTtsEvent enumTtsEvent);
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
extern void UserAdjustAudioMuteSwitch(void);
extern void UserAdjustAudioVolume(BYTE ucVolume);
extern WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// ICM
//-------------------------------------------------------
extern void UserAdjustColorEffectMode(EnumSelRegion enumSelRegion);

//-------------------------------------------------------
// Night Sniper
//-------------------------------------------------------
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
extern void UserAdjustNightSniper(EnumSelRegion enumSelRegion);
#endif

//-------------------------------------------------------
// sRGB
//-------------------------------------------------------
#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
extern void UserAdjustGlobalHueSat(EnumSelRegion enumSelRegion);
#endif

//-------------------------------------------------------
// OD
//-------------------------------------------------------
#if(_OD_FUNCTION == _ON)
extern void UserAdjustODGetODLUTInfo(StructODTableInfo *pstTableInfo);
extern BYTE UserAdjustODGetODLUTBank(void);
extern bit UserAdjustGetOsdODStatus(void);
extern void UserAdjustODGetODUserInfo(StructODUserData *pstODUserData);

#if(_OD_BY_POSITION_SUPPORT == _ON)
extern void UserAdjustODGetODByPosTableInfo(StructODTableInfo *pstByPosTableInfo);
extern EnumODByPosRegionSize UserAdjustODGetODByPosRegionSize(WORD usPanelHeight);
extern void UserAdjustODGetODUserByPosInfo(StructODUserByPosData *pstODUserByPosData);
#endif

#endif

//-------------------------------------------------------
// IR
//-------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
extern void UserAdjustIR(void);
#endif

//-------------------------------------------------------
// SDRtoHDR
//-------------------------------------------------------
#if(_SDR_TO_HDR_FUNCTION == _ON)
extern void UserAdjustSDRToHDR(EnumSelRegion enumSelRegion, bit bOn);
#endif

//-------------------------------------------------------
// Highlight Window
//-------------------------------------------------------
#if(_COLOR_DEMO_FUNCTION == _ON)
extern void UserAdjustHLWinType(void);
extern void UserAdjustHLWinType5Move(void);
#endif

//-------------------------------------------------------
// Sharpness
//-------------------------------------------------------
#if(_COLOR_IP_SHARPNESS == _ON)
extern BYTE *UserAdjustGetSharpness1To1Coef(EnumSUCoefType enumSUCoefType, EnumSelRegion enumSelRegion, BYTE ucOsdSelSharpness);
extern BYTE *UserAdjustGetSharpnessNormalCoef(EnumSUCoefType enumSUCoefType, EnumSelRegion enumSelRegion, BYTE ucOsdSelSharpness);
extern BYTE UserAdjustGetSharpnessCoefBankNum(void);
extern bit UserAdjustSharpnessBypassCheck(void);
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
extern BYTE *UserAdjustGetScalingDownCoefH(EnumSDCoefType enumSDCoefType, EnumSelRegion enumSelRegion);
extern BYTE *UserAdjustGetScalingDownCoefV(EnumSDCoefType enumSDCoefType, EnumSelRegion enumSelRegion);
#endif

//-------------------------------------------------------
// HDR
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
extern void UserAdjustHdrCheckDpVersion(EnumInputPort enumInputPort, WORD usHdrMode);
#endif

//-------------------------------------------------------
// PIP Sub config
//-------------------------------------------------------
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)

#if(_PIP_TRANSPARENCY_SUPPORT == _ON)
extern void UserAdjustPipTransparency(WORD usAdjustData);
#endif

#endif

extern void UserAdjustOsdSelectRegionColorProc(void);
extern void UserAdjustDisplayMode(void);
extern void UserAdjustRegionInputPort(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
extern void UserAdjustDpMstRxPxpMode(EnumDpMstPxpMode enumDpMstPxpMode);
extern BYTE UserAdjustGetInputPortValue(EnumRegionIndex enumRegionIdx);
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
extern void UserAdjustSwapInputPort(void);
#endif
#if(_COLOR_DEMO_FUNCTION == _ON)
extern BYTE UserAdjustCheckOsdSelectRegion(void);
extern BYTE UserAdjustCheckOsdInverseSelectRegion(void);
#endif
extern EnumSelRegion UserAdjustConvertSystemSelectRegion(BYTE ucRegion);
extern EnumDisplayRegion UserAdjustConvertDisplayRegion(BYTE ucRegion);
extern EnumInputPort UserAdjustGetSelectRegionPort(void);

#if((_COLOR_IP_LSR == _ON) ||\
    (_COLOR_IP_DSHP == _ON) ||\
    (_COLOR_IP_ICM == _ON) ||\
    (_COLOR_IP_DCC == _ON) ||\
    (_COLOR_IP_IAPS == _ON) ||\
    (_COLOR_IP_CONTRAST == _ON) ||\
    (_COLOR_IP_BRIGHTNESS == _ON) ||\
    (_COLOR_IP_I_GAMMA == _ON) ||\
    (_COLOR_IP_O_GAMMA == _ON) ||\
    (_COLOR_IP_SRGB == _ON) ||\
    (_COLOR_IP_RGB_3D_GAMMA == _ON) ||\
    (_COLOR_IP_UNIFORMITY == _ON) ||\
    (_COLOR_IP_SHARPNESS == _ON))
extern BYTE UserAdjustGetOSDSelectRegion(EnumSelRegion enumSelRegion);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern BYTE UserAdjustGetOsdDisplaySelectRegion(EnumDisplayRegion enumDisplayRegion);
extern BYTE *UserAdjustGetHDRUserTableAddress(EnumDisplayRegion enumDisplayRegion, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus);
extern BYTE UserAdjustGetHDRUserTableBank(EnumDisplayRegion enumDisplayRegion);
#endif

//-------------------------------------------------------
// Output Gamma
//-------------------------------------------------------
#if(_GAMMA_FUNCTION == _ON)
#if(_OGC_FUNCTION == _OFF)
extern BYTE *UserAdjustGetGammaTableAddress(BYTE ucGamma);
extern BYTE UserAdjustGetGammaTableBank(void);
#endif
extern void UserAdjustGamma(EnumSelRegion enumSelRegion);
#if(_OGC_FUNCTION == _ON)
extern EnumOGCType UserAdjustOGCOSDMapping(EnumGammaType enumGammaType);
#endif
#endif

//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
extern BYTE *UserAdjustGetPCMUserModeTableAddress(BYTE ucPCM);
extern BYTE UserAdjustGetPCMUserModeTableBank(void);
extern void UserAdjustPCM(EnumSelRegion enumSelRegion);
#if(_OCC_FUNCTION == _ON)
extern EnumPCMType UserAdjustPCMOSDMapping(EnumPCMTypeIndex enumPCMTypeIndex);
#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
extern void UserAdjustGetColorTransferUserModeTableAddress(EnumPCMType enumPCMType, EnumOSDColorTempDef enumOSDColorTempIndex, WORD *pusTable);
#endif
#endif
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
extern EnumOCCPCMGammaType UserAdjustOCCPCMGammaOSDMapping(EnumGammaType enumGammaType);
extern EnumOCCPCMGammaCTMatrix UserAdjustOCCPCMGammaCTOSDMapping(EnumOSDColorTempDef enumOSDColorTempDef);
#endif
#endif


//-------------------------------------------------------
// 3D Gamma
//-------------------------------------------------------
#if(_RGB_3D_GAMMA_FUNCTION == _ON)
extern BYTE *UserAdjustGet3DGammaTableAddress(void);
extern BYTE UserAdjustGet3DGammaTableBank(void);
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
extern Enum3DGammaTypeSelect UserAdjustGet3DGammaType(EnumSelRegion enumSelRegion);
#endif
#endif

//-------------------------------------------------------
// 3D Gamma Gamut Compression
//-------------------------------------------------------
#if((_RGB_3D_GAMMA_FUNCTION == _ON) && (_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON))
extern BYTE *UserAdjustGet3DGammaGamutCMPTableAddress(void);
extern BYTE UserAdjustGet3DGammaGamutCMPTableBank(void);
#endif

//-------------------------------------------------------
// 3D Gamma HDR10 Remap
//-------------------------------------------------------
#if((_RGB_3D_GAMMA_FUNCTION == _ON) && (_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON))
extern BYTE *UserAdjustGet3DGammaHDR10RemapTableAddress(BYTE uc3DGammaType);
extern BYTE UserAdjustGet3DGammaHDR10RemapTableBank(void);
#endif

//-------------------------------------------------------
// Dynamic Low Blue
//-------------------------------------------------------
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
extern BYTE *UserAdjustGetLowBlueUserParaAddress(void);
extern BYTE *UserAdjustGetLowBlueMatrixAddress(EnumEyeProtectLevel enumEyeProtectLevel);
extern BYTE UserAdjustGetLowBlueTableBank(void);
#endif

//-------------------------------------------------------
// Unifomity
//-------------------------------------------------------
#if(_UNIFORMITY_FUNCTION == _ON)
extern void UserAdjustPanelUniformityMode(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
extern void UserAdjustFreeSyncODMeasure(void);
#endif

//-------------------------------------------------------
// MRCM
//-------------------------------------------------------
#if(_MRCM_SUPPORT == _ON)
extern void UserAdjustMRCM(void);
#endif // End of #if(_MRCM_SUPPORT == _ON)

//-------------------------------------------------------
// LocalContrast
//-------------------------------------------------------
#if((_LOCAL_CONTRAST_FUNCTION == _ON) || (_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON) || (_IP_LOCAL_CONTRAST_ON == _ON) || (_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _ON))
extern BYTE UserAdjustGetLocalContrastTableBank(void);
extern BYTE *UserAdjustGetLocalContrastTemporalTableAddress(EnumLocalContrastTemporalType enumLocalContrastTemporalType);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
extern void UserAdjustLocalContrast(EnumSelRegion enumSelRegion);

#if(_HDR10_SUPPORT == _ON)
extern BYTE *UserAdjustGetLocalContrastHDR10TableAddress(EnumSelRegion enumSelRegion, BYTE ucLCStatus, EnumHDR10StaticMasteringLvType enumHDR10StaticMasteringLvType);
#endif
extern BYTE *UserAdjustGetLocalContrastTableAddress(BYTE ucLCStatus);

#if(_SDR_PLUS_FUNCTION)
extern BYTE *UserAdjustGetLocalContrastSDRPlusAddress(void);
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
extern BYTE *UserAdjustGetLocalContrastNightSniperAddress(void);
#endif
#endif

//-------------------------------------------------------
// Pixel Shift
//-------------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
extern void UserAdjustPixelOrbiting(void);
extern void UserAdjustPixelOrbitingActive(void);
extern void UserAdjustPixelOrbitingActiveResume(void);

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
extern void UserAdjustPixelOrbitingActiveDDomain(void);
extern void UserAdjustPixelOrbitingActiveResumeDDomain(void);
extern void UserAdjustPixelOrbitingActiveDDomainEOmode(void);
extern void UserAdjustPixelOrbitingActiveResumeDDomainEOmode(void);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void UserAdjustPixelOrbitingActiveDDomainFBmode(void);
extern void UserAdjustPixelOrbitingActiveResumeDDomainFBmode(void);
#endif
#endif

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
extern void UserAdjustPixelOrbitingActiveIDomain(void);
extern void UserAdjustPixelOrbitingActiveResumeIDomain(void);
#endif

#endif

//-------------------------------------------------------
// DM
//-------------------------------------------------------
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern BYTE UserAdjustDMPQMeasure(EnumSelRegion enumSelRegion);
#endif
#endif

//-------------------------------------------------------
// Anti-Aliasing
//-------------------------------------------------------
#if(_COLOR_IP_ANTI_ALIASING == _ON)
extern DWORD *UserAdjustGetAntiAliasingCoefTableAddress(EnumAntiAliasingModeType enumAntiAliasingModeType, BYTE ucOsdSelAntiAliasing);
#endif

#if(_AUDIO_EARC_SUPPORT == _ON)
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
//-------------------------------------------------------
// Audio eARC Tx
//-------------------------------------------------------
extern bit UserAdjustArcTxEarcCheckCdsCapChange(BYTE *pucCurrentArcTxEarcCdsAdb, BYTE *pucCurrentArcTxEarcCdsSpkAdb);
extern void UserAdjustArcTxEarcCdsAudioCapabilityInitial(BYTE *pucCurrentArcTxEarcCdsAdb, BYTE *pucCurrentArcTxEarcCdsSpkAdb);
#endif // End of #if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

