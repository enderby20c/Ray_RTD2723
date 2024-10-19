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
// ID Code      : RTD2020NVRamOsd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2020_OSD)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
#define _PANEL_INDEX_ADDRESS                            (_VGA_MODE_DATA_ADDRESS_END + 1)
#else
#define _PANEL_INDEX_ADDRESS                            (_MODE_USER_DATA_ADDRESS + 1)
#endif

#define _PANEL_INDEX_ADDRESS_END                        (_PANEL_INDEX_ADDRESS + 1 - 1)

#define _OSD_USER_DATA_ADDRESS                          (_PANEL_INDEX_ADDRESS_END + 1)
#define _OSD_USER_DATA_ADDRESS_END                      (_OSD_USER_DATA_ADDRESS + sizeof(StructOsdUserDataType) - 1)

#define _COLORTEMP_DATA_ADDRESS                         (_OSD_USER_DATA_ADDRESS_END + 1)
#define _COLORTEMP_DATA_ADDRESS_END                     (_COLORTEMP_DATA_ADDRESS + (sizeof(StructColorProcDataType) * (_CT_COLORTEMP_AMOUNT + 1)) - 1)

#define _PORT_AMOUNT                                    (_OSD_INPUT_AMOUNT) // 1A 8D
#define _OSD_PORT_ADDRESS                               (_COLORTEMP_DATA_ADDRESS_END + 1)
#define _OSD_PORT_ADDRESS_END                           (_OSD_PORT_ADDRESS + (sizeof(StructOsdInputPortDataType) * _PORT_AMOUNT) - 1)

#define _REGION_AMOUNT                                  (_OSD_DM_AMOUNT * 2) // 1Px2 2Px6 3Px104Px2
#define _OSD_REGION_ADDRESS                             (_OSD_PORT_ADDRESS_END + 1)
#define _OSD_REGION_ADDRESS_END                         (_OSD_REGION_ADDRESS + (sizeof(StructOsdRegionDataType) * _REGION_AMOUNT) - 1)

#define _OSD_DISPLAY_MODE_ADDRESS                       (_OSD_REGION_ADDRESS_END + 1)
#define _OSD_DISPLAY_MODE_ADDRESS_END                   (_OSD_DISPLAY_MODE_ADDRESS + (sizeof(StructOsdDisplayModeDataType) * _OSD_DM_AMOUNT) - 1)

#if(_AUDIO_ARC_SUPPORT == _ON)
#define _OSD_AUDIO_ARC_ADDRESS                          (_OSD_DISPLAY_MODE_ADDRESS_END + 1)
#define _OSD_AUDIO_ARC_ADDRESS_END                      (_OSD_AUDIO_ARC_ADDRESS_END + sizeof(StructOsdUserDataArcDataType) - 1)
#endif

/** default value for StructOsdUserDataVgaType */
#define _USER_DATA_VGA_DEFAULT                          {\
                                                            _AUTO_COLOR_TYPE_EXTERNAL,  /* b1FactoryAutoColorType : 1;*/\
                                                        }

/** default value for StructOsdUserDataDpType */
#define _USER_DATA_DP_DEFAULT                           {\
                                                            _OSD_CLONE_FIX_OFF,             /* enumCloneModeMtP;*/\
                                                            _OSD_CLONE_FIX_OFF,             /* enumCloneMode1P;*/\
                                                            _MST_OFF,                   /* b3OsdDpMST : 3;*/\
                                                            _DP_VER_1_DOT_2,            /* b2OsdDpD0PortVersion : 2;*/\
                                                            _DP_VER_1_DOT_2,            /* b2OsdDpD1PortVersion : 2;*/\
                                                            _DP_VER_1_DOT_2,            /* b2OsdDpD2PortVersion : 2;*/\
                                                            _DP_VER_1_DOT_2,            /* b2OsdDpD6PortVersion : 2;*/\
                                                            _OFF,                       /* b1OsdDpAuxlessAlpm : 1;*/\
                                                            _OFF,                       /* b1OsdDpAdaptiveSync : 1;*/\
                                                            _OFF,                       /* b1OsdPanelReplay : 1;*/\
                                                            _OFF_PXP_MST,               /* b2PxPMst : 2;*/\
                                                        }

/** default value for StructOsdUserDataTypeCType */
#define _USER_DATA_TYPE_C_DEFAULT                       {\
                                                            _TYPE_C_U3_OFF,             /* BYTE b1D0TypeCU3Mode : 1;*/\
                                                            _TYPE_C_U3_OFF,             /* BYTE b1D1TypeCU3Mode : 1;*/\
                                                            _TYPE_C_U3_OFF,             /* BYTE b1D2TypeCU3Mode : 1;*/\
                                                            _TYPE_C_U3_OFF,             /* BYTE b1D6TypeCU3Mode : 1;*/\
                                                            _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,             /* BYTE b1D0TypeCPinAssignmentESupportSelect : 1;*/\
                                                            _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,             /* BYTE b1D1TypeCPinAssignmentESupportSelect : 1;*/\
                                                            _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,             /* BYTE b1D2TypeCPinAssignmentESupportSelect : 1;*/\
                                                            _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,             /* BYTE b1D6TypeCPinAssignmentESupportSelect : 1;*/\
                                                        }
/** default value for StructOsdUserDataUsbHubType */
#define _USER_DATA_USB_HUB_DEFAULT                      {\
                                                            _TRUE,                      /* BYTE b1OsdD0Usb3RetimerPDWakeUp: 1;*/\
                                                            _TRUE,                      /* BYTE b1OsdD0Usb3RetimerPSWakeUp: 1;*/\
                                                            _TRUE,                      /* BYTE b1OsdD1Usb3RetimerPDWakeUp: 1;*/\
                                                            _TRUE,                      /* BYTE b1OsdD1Usb3RetimerPDWakeUp: 1;*/\
                                                            _TRUE,                      /* BYTE b1OsdD2Usb3RetimerPDWakeUp: 1;*/\
                                                            _TRUE,                      /* BYTE b1OsdD2Usb3RetimerPDWakeUp: 1;*/\
                                                            _OSD_HUB_D0,                /* BYTE ucUSBHubUfpSwitchMode*/\
                                                        }
/** default value for StructOsdUserDataTmdsType */
#define _USER_DATA_TMDS_DEFAULT                         {\
                                                            _HDMI_1P4,                  /* BYTE b2OsdHdmiD0PortVersion : 2;*/\
                                                            _HDMI_1P4,                  /* BYTE b2OsdHdmiD1PortVersion : 2;*/\
                                                            _HDMI_1P4,                  /* BYTE b2OsdHdmiD2PortVersion : 2;*/\
                                                            _HDMI_1P4,                  /* BYTE b2OsdHdmiD3PortVersion : 2;*/\
                                                            _HDMI_1P4,                  /* BYTE b2OsdHdmiD4PortVersion : 2;*/\
                                                            _HDMI_1P4,                  /* BYTE b2OsdHdmiD5PortVersion : 2;*/\
                                                        }

/** default value for StructOsdUserDataAudioType */
#define _USER_DATA_AUDIO_DEFAULT                        {\
                                                            50,                         /* ucVolume;*/\
                                                            _OFF,                       /* b1VolumeMute : 1;*/\
                                                            _OFF,                       /* b1AudioStandAloneStatus : 1;*/\
                                                            _ON,                       /* BYTE b1TtsSupport: 1;*/\
                                                            80,                        /* BYTE ucTtsTextVolume;*/\
                                                            20,                        /* BYTE ucTtsAudioVolume;*/\
                                                        }

/** default value for StructOsdUserDataDisplayType */
#define _USER_DATA_DISPLAY_DEFAULT                      {\
                                                            _OSD_DM_1P,                 /* BYTE ucDisplayMode;*/\
                                                            _PIP_POSITON_RB,            /* BYTE ucPipSubPosType;*/\
                                                            _OSD_PIP_USER_POSITION_H_MAX,\
                                                                                        /* WORD usPipSubHPos;*/\
                                                            _OSD_PIP_USER_POSITION_V_MAX,\
                                                                                        /* WORD usPipSubVPos;*/\
                                                            _OSD_PIP_SIZE_MAX,          /* BYTE ucPipSubScaling;*/\
                                                            _OSD_PIP_TRANSPARENCY_MIN,  /* BYTE ucPipSubBlending;*/\
                                                            _OSD_PBP_LR_RATIO_CENTER,   /* BYTE ucPbpLrRatio;*/\
                                                            _OSD_3P_FLAG_RATIO_MIN,     /* BYTE uc3PFlagRatio;*/\
                                                            _OSD_3P_SKEW_LR_RATIO_CENTER,\
                                                                                        /* BYTE uc3PSkewLRRatio;*/\
                                                            _OFF,                       /* b1FreeSyncStatus : 1;*/\
                                                            _LATENCY_L,                 /* b2LatencyStatus : 2;*/\
                                                            _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,\
                                                                                        /* b2DispRotationSizeType : 2;*/\
                                                            0,                          /* b3OsdDispRotate : 3;*/\
                                                            _DSC_FROM_NO_PORT,          /* b3DscStatus :3;*/\
                                                            _DSC_OFF,                   /* b3Dsc1pStatus :3;*/\
                                                        }

/** default value for StructOsdUserDataColorType */
#define _USER_DATA_COLOR_DEFAULT                        {\
                                                            _COLOR_SPACE_RGB,           /* b3VGARGBYUV : 3;*/\
                                                            _COLOR_SPACE_RGB,           /* b3DVIRGBYUV :3;*/\
                                                            0,                          /* BYTE b1PCMSoftProftMode : 1;*/\
                                                            _OFF,                       /* BYTE b1GlobalDimming : 1;*/\
                                                            50,                         /* BYTE ucHdrLocalDimmingAdj;*/\
                                                            _OFF,                       /* BYTE b1HdrLocalDimming : 1;*/\
                                                            _OSD_HLW_INSIDE,            /* b2DemoSideIdx: 2;*/\
                                                            _OFF,                       /* b1OsdDcrStatus: 1;*/\
                                                            _OFF,                       /* b1ODStatus : 1;*/\
                                                            _OD_GAIN_CENTER,            /* ucODGain;*/\
                                                            0,                          /* BYTE ucSelectRegionWidth;*/\
                                                            _SELECT_REGION_COLOR_R,     /* BYTE ucSelectRegionColor;*/\
                                                            _HL_WIN_OFF,                /* ucHLWinType;*/\
                                                        }

/** default value for StructOsdUserDataAntiAlisingType */
#define _ANTIALIASING_DEFAULT                           {\
                                                            0,                          /*BYTE ucAntiAliasingMode;*/\
                                                            0,                          /*BYTE ucAntiAliasingLevel;*/\
                                                        }

/** default value for StructOsdUserDataType */
#define _USER_DATA_DEFAULT                              {\
                                                            _BACKLIGHT_CENTER,          /* usBackLight;*/\
                                                            _OSD_H_POS_CENTER,          /* ucOsdHPos;*/\
                                                            _OSD_V_POS_CENTER,          /* ucOsdVPos;*/\
                                                            (_OSD_TIMEOUT_MIN + 1),     /* ucOsdTimeout;*/\
                                                            255,                        /* ucTransparency;*/\
                                                            0,                          /* BYTE ucOsdInputPort0;*/\
                                                            0,                          /* WORD usHour;*/\
                                                            0,                          /* BYTE ucMin;*/\
                                                            _ENGLISH,                   /* b4Language : 4;*/\
                                                            _ON,                        /* b1DDCCIStatus : 1;*/\
                                                            _OSD_ROTATE_DEGREE_0,       /* b2OsdRotate : 2;*/\
                                                            _OFF,                       /* b1EnergySave*/\
                                                            _OSD_OTHER_RESET,           /* BYTE ucExitHotKeyItem;*/\
                                                            _CROSSHAIR_OFF,             /* BYTE ucCrosshair;*/\
                                                            _USER_DATA_VGA_DEFAULT,\
                                                            _USER_DATA_DP_DEFAULT,\
                                                            _USER_DATA_TYPE_C_DEFAULT,\
                                                            _USER_DATA_USB_HUB_DEFAULT,\
                                                            _USER_DATA_TMDS_DEFAULT,\
                                                            _USER_DATA_AUDIO_DEFAULT,\
                                                            _USER_DATA_DISPLAY_DEFAULT,\
                                                            _USER_DATA_COLOR_DEFAULT,\
                                                            _USER_EAGLE_SIGHT_DATA_DEFAULT,\
                                                            _USER_MBR_DATA_DEFAULT,\
                                                            _ANTIALIASING_DEFAULT,\
                                                            _USER_EYE_PROTECT_DATA_DEFAULT,\
                                                        }

/** default value for StructOsdInputPortDataType */
#define _USER_PORT_DATA_DEFAULT                         {\
                                                            _HDR10_MODE_OFF,            /* BYTE ucHdrMode; */\
                                                            0,                          /* BYTE ucAspectOriginRatio*/\
                                                            2,                          /* BYTE b4Sharpness : 4;*/\
                                                            _OSD_ASPECT_RATIO_FULL,     /* BYTE b3AspectRatio : 3;*/\
                                                            _ON,                        /* BYTE b1OverScan : 1;*/\
                                                            _ON,                        /* BYTE b1DVisionNotification;*/\
                                                            _OFF,                       /* BYTE b7DVision;*/\
                                                        }

/** default value for StructOsdRegionDataSixColorType */
#define _USER_REGION_DATA_SIX_COLOR_DEFAULT             {\
                                                            _SIX_COLOR_HUE_R,           /* BYTE ucSixColorHueR;*/\
                                                            _SIX_COLOR_SATURATION_R,    /* BYTE ucSixColorSaturationR;*/\
                                                            _SIX_COLOR_HUE_Y,           /* BYTE ucSixColorHueY;*/\
                                                            _SIX_COLOR_SATURATION_Y,    /* BYTE ucSixColorSaturationY;*/\
                                                            _SIX_COLOR_HUE_G,           /* BYTE ucSixColorHueG;*/\
                                                            _SIX_COLOR_SATURATION_G,    /* BYTE ucSixColorSaturationG;*/\
                                                            _SIX_COLOR_HUE_C,           /* BYTE ucSixColorHueC;*/\
                                                            _SIX_COLOR_SATURATION_C,    /* BYTE ucSixColorSaturationC;*/\
                                                            _SIX_COLOR_HUE_B,           /* BYTE ucSixColorHueB;*/\
                                                            _SIX_COLOR_SATURATION_B,    /* BYTE ucSixColorSaturationB;*/\
                                                            _SIX_COLOR_HUE_M,           /* BYTE ucSixColorHueM;*/\
                                                            _SIX_COLOR_SATURATION_M,    /* BYTE ucSixColorSaturationM;*/\
                                                        }

#define _DVISION_DARK_DEFAULT                           {\
                                                            _OFF,                       /* stDVisionMode1.b1DVisionPictureModify : 1*/\
                                                            50,                         /* stDVisionMode1.b7DVisionBacklight :7;*/\
                                                            50,                         /* stDVisionMode1 ucDVisionBrightness;*/\
                                                            50,                         /* stDVisionMode1.ucDVisionContrast;*/\
                                                            50,                         /* stDVisionMode1.ucDVisionSaturation;*/\
                                                        }
#define _DVISION_BRIGHT_DEFAULT                         {\
                                                            _OFF,                       /* stDVisionMode1.b1DVisionPictureModify : 1*/\
                                                            50,                         /* stDVisionMode1.b7DVisionBacklight :7;*/\
                                                            50,                         /* stDVisionMode1 ucDVisionBrightness;*/\
                                                            50,                         /* stDVisionMode1.ucDVisionContrast;*/\
                                                            50,                         /* stDVisionMode1.ucDVisionSaturation;*/\
                                                        }
#define _DVISION_GAME_DEFAULT                           {\
                                                            _OFF,                       /* stDVisionMode1.b1DVisionPictureModify : 1*/\
                                                            50,                         /* stDVisionMode1.b7DVisionBacklight :7;*/\
                                                            50,                         /* stDVisionMode1 ucDVisionBrightness;*/\
                                                            50,                         /* stDVisionMode1.ucDVisionContrast;*/\
                                                            50,                         /* stDVisionMode1.ucDVisionSaturation;*/\
                                                        }
#define _DVISION_USER_DEFAULT                           {\
                                                            _OFF,                       /* stDVisionMode1.b1DVisionPictureModify : 1*/\
                                                            50,                         /* stDVisionMode1.b7DVisionBacklight :7;*/\
                                                            50,                         /* stDVisionMode1 ucDVisionBrightness;*/\
                                                            50,                         /* stDVisionMode1.ucDVisionContrast;*/\
                                                            50,                         /* stDVisionMode1.ucDVisionSaturation;*/\
                                                        }
#define _DVISION_DATA_DEFAULT                           {\
                                                            _DVISION_DARK_DEFAULT,\
                                                            _DVISION_BRIGHT_DEFAULT,\
                                                            _DVISION_GAME_DEFAULT,\
                                                            _DVISION_USER_DEFAULT,\
                                                        }
/** default value for StructOsdRegionDataType */
#define _USER_REGION_DATA_DEFAULT                       {\
                                                            _USER_REGION_DATA_SIX_COLOR_DEFAULT,\
                                                                                        /* StructOsdRegionDataType stSixColorData;*/\
                                                            _OSD_DVISION_PICTURE_BRIGHT,  /* BYTE b3DVisionPicture : 3;*/\
                                                            _DVISION_DARK_DEFAULT,\
                                                            _DVISION_BRIGHT_DEFAULT,\
                                                            _DVISION_GAME_DEFAULT,\
                                                            _DVISION_USER_DEFAULT,\
                                                            _DEFAULT_HUE,               /* BYTE ucHue;*/\
                                                            _DEFAULT_SATURATION,        /* BYTE ucSaturation;*/\
                                                            0x200,                      /* WORD usBrightness;*/\
                                                            0x800,                      /* WORD usContrast;*/\
                                                            _COLOREFFECT_STANDARD,      /* BYTE b4ColorEffect : 4;*/\
                                                            _CT_6500,                   /* BYTE b4ColorTempType : 4;*/\
                                                            _GAMMA_OFF,                 /* BYTE b3Gamma : 3;*/\
                                                            _PCM_OSD_NATIVE,            /* BYTE b3PCMStatus : 3;*/\
                                                            _ULTRA_VIVID_OFF,           /* BYTE b2UltraVividStatus : 2;*/\
                                                            0,                          /* BYTE b3PanelUniformityType :3;*/\
                                                            _OFF,                       /* BYTE b1PanelUniformity : 1;*/\
                                                            _OFF,                       /* BYTE b1Sdr2HdrStatus : 1;*/\
                                                            _OFF,                       /* BYTE b3LocalContrast : 3;*/\
                                                            _OFF,                       /* BYTE b1DarkEnhanceStatus : 1;*/\
                                                            _OFF,                       /* BYTE b1HdrSharpness : 1;*/\
                                                            0,                          /* BYTE ucHdrContrast;*/\
                                                            0,                          /* BYTE ucHdrColorEnhance;*/\
                                                            0,                          /* BYTE ucHdrLightEnhance;*/\
                                                            _HLG_OOTF_STANDARD_MODE,    /* BYTE ucHdrHlgOotf*/\
                                                            100,                        /* BYTE ucLocalContrastBlending;*/\
                                                            100,                        /* BYTE ucLocalContrastDiffGain;*/\
                                                            _OFF,                       /* b1SdrPlus : 1;*/\
                                                            50,                         /* b7SdrPlusSharp : 7;*/\
                                                            50,                         /* ucSdrPlusDark;*/\
                                                            _CHAMELEON_HUE_CENTER,      /* WORD usChameleonHue;*/\
                                                            _CHAMELEON_SAT_CENTER,      /* BYTE ucChameleonSat;*/\
                                                            _CHAMELEON_LIGHT_CENTER,    /* BYTE ucChameleonLightness*/\
                                                            _OFF,                       /* b1NightSniper : 1;*/\
                                                            50,                         /* b7NightSniperSat : 7;*/\
                                                            50,                         /* ucNightSniperLight;*/\
                                                        }
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
#define _USER_EAGLE_SIGHT_DATA_DEFAULT                  {\
                                                            _OFF,                       /*BYTE b1EagleSightEn: 1;*/\
                                                            1,                       /*BYTE b3EagleSightBorder: 3;*/\
                                                            _OFF,                       /*BYTE b1EagleSightCircleWin : 1; (_EAGLESIGHT_CIRCLE_WINDOW_FUNCTION == _ON)*/\
                                                            1,                          /*BYTE ucEagleSightTransparency ;*/\
                                                            _ES_1p5x,                   /*BYTE usEagleSightZo*/\
                                                            _POSITON_LT,                /*BYTE ucEagleSightCapPosition;*/\
                                                            _POSITON_LT,                /*BYTE ucEagleSightDiapPosition;*/\
                                                        }
#else
#define _USER_EAGLE_SIGHT_DATA_DEFAULT                  {\
                                                            _OFF,                       /*BYTE b1EagleSightEn: 1;*/\
                                                            1,                       /*BYTE b3EagleSightBorder: 3;*/\
                                                            1,                          /*BYTE ucEagleSightTransparency ;*/\
                                                            _ES_1p5x,                   /*BYTE usEagleSightZo*/\
                                                            _POSITON_LT,                /*BYTE ucEagleSightCapPosition;*/\
                                                            _POSITON_LT,                /*BYTE ucEagleSightDiapPosition;*/\
                                                        }
#endif

#define _USER_MBR_DATA_DEFAULT                          {\
                                                            _OSD_MBR_OFF,               /* b2MbrMode :2;*/\
                                                            40,                         /* b7MbrDuty :7;*/\
                                                            _MBR_POS_CENTER,            /* b7MbrPos :7;*/\
                                                        }
#if(_AUDIO_ARC_SUPPORT == _ON)
#define _USER_AUDIO_ARC_DATA_DEFAULT                    {\
                                                            _ARC_DAC,                   /*BYTE b2ArcAudioOut :2;*/\
                                                            _OFF,                       /*BYTE b2ArcMute : 2;*/\
                                                            _ARC_2_CH,                  /*BYTE b3ArcChanel :3;*/\
                                                            _OSD_INPUT_D0,              /*BYTE ucInputport;*/\
                                                            _AUDIO_ARC_EARC_OFF,        /*ucArcType;*/\
                                                        }
#endif


#define _USER_EYE_PROTECT_DATA_DEFAULT                  {\
                                                            _EYEPROTECT_TIME_OFF,       /*enumNightModeTime;*/\
                                                            _LOWBLUE_OFF,               /*b3LowBlueMode;*/\
                                                            _EYEPROTECT_LEVEL_0,        /*b3ProtectLevel;*/\
                                                            _OFF,                       /*BYTE ucAmbientSenseMode;*/\
                                                        }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumFactoryAutoColorType b1FactoryAutoColorType : 1;
} StructOsdUserDataVgaType;

typedef struct
{
    EnumOSDCloneModeFixDef enumCloneModeMtP;
    EnumOSDCloneModeFixDef enumCloneMode1P;
    WORD b3OsdDpMST : 3;
    WORD b2OsdDpD0PortVersion : 2;
    WORD b2OsdDpD1PortVersion : 2;
    WORD b2OsdDpD2PortVersion : 2;
    WORD b2OsdDpD6PortVersion : 2;
    WORD b1OsdDpAuxlessAlpm : 1;
    WORD b1OsdDpAdaptiveSync : 1;
    WORD b1OsdPanelReplay : 1;
    WORD b2PxPMst : 2;
} StructOsdUserDataDpType;

typedef struct
{
    BYTE b1D0TypeCU3Mode : 1;
    BYTE b1D1TypeCU3Mode : 1;
    BYTE b1D2TypeCU3Mode : 1;
    BYTE b1D6TypeCU3Mode : 1;
    BYTE b1D0TypeCPinAssignmentESupportSelect : 1;
    BYTE b1D1TypeCPinAssignmentESupportSelect : 1;
    BYTE b1D2TypeCPinAssignmentESupportSelect : 1;
    BYTE b1D6TypeCPinAssignmentESupportSelect : 1;
} StructOsdUserDataTypeCType;

typedef struct
{
    BYTE b1OsdD0Usb3RetimerPDWakeUp : 1;
    BYTE b1OsdD0Usb3RetimerPSWakeUp : 1;
    BYTE b1OsdD1Usb3RetimerPDWakeUp : 1;
    BYTE b1OsdD1Usb3RetimerPSWakeUp : 1;
    BYTE b1OsdD2Usb3RetimerPDWakeUp : 1;
    BYTE b1OsdD2Usb3RetimerPSWakeUp : 1;
    BYTE ucUSBHubUfpSwitchMode;
} StructOsdUserDataUsbHubType;

typedef struct
{
    BYTE b2OsdHdmiD0PortVersion : 2;
    BYTE b2OsdHdmiD1PortVersion : 2;
    BYTE b2OsdHdmiD2PortVersion : 2;
    BYTE b2OsdHdmiD3PortVersion : 2;
    BYTE b2OsdHdmiD4PortVersion : 2;
    BYTE b2OsdHdmiD5PortVersion : 2;
} StructOsdUserDataTmdsType;

typedef struct
{
    BYTE ucVolume;
    BYTE b1VolumeMute : 1;
    BYTE b1AudioStandAloneStatus : 1;
    BYTE b1TtsSupport : 1;
    BYTE ucTtsTextVolume;
    BYTE ucTtsAudioVolume;
} StructOsdUserDataAudioType;

typedef struct
{
    BYTE ucDisplayMode;
    BYTE ucPipSubPosType;
    WORD usPipSubHPos;
    WORD usPipSubVPos;
    BYTE ucPipSubScaling;
    BYTE ucPipSubBlending;
    BYTE ucPbpLrRatio;
    BYTE uc3PFlagRatio;
    BYTE uc3PSkewLRRatio;
    BYTE b1FreeSyncStatus : 1;
    BYTE b2LatencyStatus : 2;
    BYTE b2DispRotationSizeType : 2;
    EnumOSDDispRotateDegree b3OsdDispRotate : 3;
    EnumDscSelectPort b3DscStatus : 3;
    EnumOSDDscTypeDef b3Dsc1PStatus : 3;
} StructOsdUserDataDisplayType;

typedef struct
{
    EnumColorSpace b3VGARGBYUV : 3;
    EnumColorSpace b3DVIRGBYUV : 3;
    BYTE b1PCMSoftProftMode : 1;
    BYTE b1GlobalDimming : 1;

    BYTE ucHdrLocalDimmingAdj;

    BYTE b1HdrLocalDimming : 1;
    EnumOSDHLWRegion b2DemoSideIdx : 2;
    BYTE b1OsdDcrStatus : 1;
    BYTE b1ODStatus : 1;

    BYTE ucODGain;
    BYTE ucSelectRegionWidth;
    BYTE ucSelectRegionColor;
    BYTE ucHLWinType;
} StructOsdUserDataColorType;

typedef struct
{
    BYTE b1EagleSightEn : 1;
    BYTE b3EagleSightBorder : 3;
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    BYTE b1EagleSightCircleWin : 1;
#endif
    BYTE ucEagleSightTransparency;
    BYTE ucEagleSightZoom;
    BYTE ucEagleSightCapPosition;
    BYTE ucEagleSightDispPosition;
} StructOsdUserDataEagleSightType;

typedef struct
{
    BYTE b2MbrMode : 2;
    BYTE b7MbrDuty : 7;
    BYTE b7MbrPosition : 7;

} StructOsdUserDataMbrModeType;

typedef struct
{
    BYTE ucAntiAliasingMode;
    BYTE ucAntiAliasingLevel;

} StructOsdUserDataAntiAlisingType;

typedef struct
{
    EnumNightModeTimeType enumNightModeTime;
    EnumLowBlueType b3LowBlueMode : 3;
    EnumEyeProtectLevelType b3ProtectLevel : 3;
    bit bAmbientSenseMode;
} StructOsdUserDataEyeProtectType;

typedef struct
{
    WORD usBackLight;
    BYTE ucOsdHPos;
    BYTE ucOsdVPos;
    BYTE ucOsdTimeout;
    BYTE ucTransparency;
    BYTE ucOsdInputPort0;
    WORD usHour;
    BYTE ucMin;
    EnumOSDLanguageDef b4Language : 4;
    BYTE b1DDCCIStatus : 1;
    EnumOsdRotateType b2OsdRotate : 2;
    BYTE b1EnergySave : 1;
    BYTE ucExitHotKeyItem;
    BYTE ucCrosshair;
    StructOsdUserDataVgaType stVgaData;
    StructOsdUserDataDpType stDpData;
    StructOsdUserDataTypeCType stTypeCData;
    StructOsdUserDataUsbHubType stUsbHubData;
    StructOsdUserDataTmdsType stTmdsData;
    StructOsdUserDataAudioType stAudioData;
    StructOsdUserDataDisplayType stDisplayData;
    StructOsdUserDataColorType stColorData;
    StructOsdUserDataEagleSightType stEagleSightData;
    StructOsdUserDataMbrModeType stMbrData;
    StructOsdUserDataAntiAlisingType stAntiAliasingData;
    StructOsdUserDataEyeProtectType stEyeProtectData;
} StructOsdUserDataType;

typedef struct
{
    WORD usColorTempR;
    WORD usColorTempG;
    WORD usColorTempB;
} StructColorProcDataType;

typedef struct
{
    BYTE ucHdrMode;
    BYTE ucAspectOriginRatio;
    //-----------------------------------
    BYTE b4Sharpness : 4;
    EnumAspectRatioTypeIndex b3AspectRatio : 3;
    BYTE b1OverScan : 1;
    //-----------------------------------
    BYTE b1DVisionNotification : 1;
    BYTE b7DVision : 7;
} StructOsdInputPortDataType;

typedef struct
{
    BYTE ucSixColorHueR;
    BYTE ucSixColorSaturationR;
    BYTE ucSixColorHueY;
    BYTE ucSixColorSaturationY;
    BYTE ucSixColorHueG;
    BYTE ucSixColorSaturationG;
    BYTE ucSixColorHueC;
    BYTE ucSixColorSaturationC;
    BYTE ucSixColorHueB;
    BYTE ucSixColorSaturationB;
    BYTE ucSixColorHueM;
    BYTE ucSixColorSaturationM;
} StructOsdRegionDataSixColorType;

typedef struct
{
    BYTE b1DVisionPictureModify : 1;
    BYTE b7DVisionBacklight : 7;
    BYTE ucDVisionBrightness;
    BYTE ucDVisionContrast;
    BYTE ucDVisionSaturation;
} StructOsdDVisionModeDataType;

typedef struct
{
    StructOsdRegionDataSixColorType stSixColorData;
    BYTE b3DVisionPicture : 3;
    StructOsdDVisionModeDataType stDVisionMode1;
    StructOsdDVisionModeDataType stDVisionMode2;
    StructOsdDVisionModeDataType stDVisionMode3;
    StructOsdDVisionModeDataType stDVisionMode4;
    BYTE ucHue;
    BYTE ucSaturation;
    WORD usBrightness;
    WORD usContrast;
    //-----------------------------------
    EnumColorEffectType b4ColorEffect : 4;
    EnumOSDColorTempDef b4ColorTempType : 4;
    //-----------------------------------
    EnumGammaType b3Gamma : 3;
    EnumPCMTypeIndex b3PCMStatus : 3;
    BYTE b2UltraVividStatus : 2;
    //-----------------------------------
    BYTE b3PanelUniformityType : 3;
    BYTE b1PanelUniformity : 1;
    BYTE b1Sdr2HdrStatus : 1;
    BYTE b3LocalContrast : 3;
    BYTE b1HdrDarkEnhance : 1;
    BYTE b1HdrSharpnesse : 1;

    BYTE ucHdrContrast;
    BYTE ucHdrColorEnhance;
    BYTE ucHdrLightEnhance;
    BYTE ucHdrHlgOotf;
    BYTE ucLocalContrastBlending;
    BYTE ucLocalContrastDiffGain;
    BYTE b1SdrPlus : 1;
    BYTE b7SdrPlusSharp : 7;
    BYTE ucSdrPlusDark;
    WORD usChameleonHue;
    BYTE ucChameleonSat;
    BYTE ucChameleonLightness;
    BYTE b1NightSniper : 1;
    BYTE b7NightSniperSat : 7;
    BYTE ucNightSniperLight;
} StructOsdRegionDataType;

typedef struct
{
    BYTE ucSelectRegion;
    BYTE pucOsdInputPort[4];
    BYTE pucOsdInputPortBackup[4];
    BYTE ucAuidioInputRegion;
} StructOsdDisplayModeDataType;

typedef struct
{
    WORD usStringIdx;
    WORD usAdjValue;
    WORD usAdjValueMin;
    WORD usAdjValueMax;
    WORD usAdjValueCenter;
    WORD usSubOsdState;
    WORD usSubStringIdx;
    EnumAdjType b3ShowType : 3;
} StructOsdItemDataType;

#if(_AUDIO_ARC_SUPPORT == _ON)
typedef struct
{
    BYTE b2ArcAudioOut : 2;
    BYTE b2ArcMute : 2;
    BYTE b3ArcChanel : 3;
    BYTE ucInputport;
    BYTE ucArcType;
} StructOsdUserDataArcDataType;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern Tables for DVision
//----------------------------------------------------------------------------------------
#if(_DM_FUNCTION == _ON)
extern code StructOsdDVisionModeDataType tDVisionPictureModeDefault[_OSD_DVISION_PICTURE_AMOUNT];
#endif

extern StructOsdUserDataType g_stOsdUserData;
extern StructColorProcDataType g_stColorProcData;
extern StructOsdInputPortDataType g_pstOsdInputPortData[_OSD_INPUT_AMOUNT];
extern StructOsdRegionDataType g_pstOsdRegionData[2];
extern StructOsdDisplayModeDataType g_stOsdDisplayModeData;
extern StructOsdItemDataType g_stOsdItemData;

#if(_AUDIO_ARC_SUPPORT == _ON)
extern StructOsdUserDataArcDataType g_stAudioArcData;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern void RTDEepromStartup(void);
extern void RTDEepromWholeRestore(void);
extern void RTDEepromRestoreBacklight(void);

extern void RTDEepromLoadOsdUserData(void);
extern void RTDEepromSaveOsdUserData(void);
extern void RTDEepromRestoreOsdUserData(void);

extern void RTDEepromLoadColorSetting(BYTE ucRegion);
extern void RTDEepromSaveColorSetting(BYTE ucColorTempType);
extern void RTDEepromRestoreColorSetting(void);
extern void RTDEepromRestoreUserColorSetting(void);

extern void RTDEepromLoadOsdInputSourceData(BYTE ucSource);
extern void RTDEepromSaveOsdInputSourceData(BYTE ucSource);
extern void RTDEepromRestoreOsdInputSourceData(void);

extern void RTDEepromLoadOsdInputPortData(BYTE ucPort);
extern void RTDEepromSaveOsdInputPortData(BYTE ucPort);
extern void RTDEepromRestoreOsdInputPortData(void);

//extern BYTE RTDNVRamTransferOsdRegionIndex(BYTE ucDisplayMode, BYTE ucRegion);
//extern BYTE RTDEepromTransferOsdRegionType(BYTE ucDisplayMode, BYTE ucRegion);
extern void RTDEepromLoadOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion);
extern void RTDEepromSaveOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion);
extern void RTDEepromRestoreOsdRegionData(void);

extern void RTDEepromLoadOsdDisplayModeData(BYTE ucDisplayMode);
extern void RTDEepromSaveOsdDisplayModeData(BYTE ucDisplayMode);
extern void RTDEepromRestoreOsdDisplayModeData(void);
#if(_AUDIO_ARC_SUPPORT == _ON)
extern void RTDEepromLoadAudioArcData(void);
extern void RTDEepromSaveAudioArcData(void);
extern void RTDEepromRestoreAudioArcData(void);
#endif

//extern void RTDEepromRestoreSixColorData(void);
//extern void RTDEepromSavePanelUsedTimeData(void);

#define RTDNVRamStartup()                               RTDEepromStartup()
#define RTDNVRamWholeRestore()                          RTDEepromWholeRestore()
#define RTDNVRamRestoreBacklight()                      RTDEepromRestoreBacklight()
#define RTDNVRamSaveOsdUserData()                       RTDEepromSaveOsdUserData()
#define RTDNVRamRestoreOsdUserData()                    RTDEepromRestoreOsdUserData()
#define RTDNVRamLoadColorSetting(x)                     RTDEepromLoadColorSetting(x)
#define RTDNVRamSaveColorSetting(x)                     RTDEepromSaveColorSetting(x)
#define RTDNVRamRestoreColorSetting()                   RTDEepromRestoreColorSetting()
#define RTDNVRamRestoreUserColorSetting()               RTDEepromRestoreUserColorSetting()
#define RTDNVRamLoadOsdInputSourceData(x)               RTDEepromLoadOsdInputSourceData(x)
#define RTDNVRamSaveOsdInputSourceData(x)               RTDEepromSaveOsdInputSourceData(x)
#define RTDNVRamRestoreOsdInputSourceData()             RTDEepromRestoreOsdInputSourceData()

#define RTDNVRamLoadOsdInputPortData(x)                 RTDEepromLoadOsdInputPortData(x)
#define RTDNVRamSaveOsdInputPortData(x)                 RTDEepromSaveOsdInputPortData(x)
#define RTDNVRamRestoreOsdInputPortData()               RTDEepromRestoreOsdInputPortData()

//#define RTDNVRamTransferOsdRegionType(x, y)             RTDEepromTransferOsdRegionType(x, y)
#define RTDNVRamLoadOsdRegionData(x, y)                 RTDEepromLoadOsdRegionData((x), (y))
#define RTDNVRamSaveOsdRegionData(x, y)                 RTDEepromSaveOsdRegionData((x), (y))
#define RTDNVRamRestoreOsdRegionData()                  RTDEepromRestoreOsdRegionData()

#define RTDNVRamLoadOsdDisplayModeData(x)               RTDEepromLoadOsdDisplayModeData(x)
#define RTDNVRamSaveOsdDisplayModeData(x)               RTDEepromSaveOsdDisplayModeData(x)
#define RTDNVRamRestoreOsdDisplayModeData()             RTDEepromRestoreOsdDisplayModeData()

//#define RTDNVRamRestoreSixColorData()                  RTDEepromRestoreSixColorData()
//#define RTDNVRamSavePanelUsedTimeData()                RTDEepromSavePanelUsedTimeData()
#if(_AUDIO_ARC_SUPPORT == _ON)
#define RTDNVRamLoadAudioArcData()                      RTDEepromLoadAudioArcData()
#define RTDNVRamSaveAudioArcData()                      RTDEepromSaveAudioArcData()
#define RTDNVRamRestoreAudioArcData()                   RTDEepromRestoreAudioArcData()
#endif
#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

extern bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData);

extern void RTDFlashStartup(void);
extern void RTDFlashWholeRestore(void);
extern void RTDFlashRestoreBacklight(void);
extern void RTDFlashSaveOSDData(void);
extern void RTDFlashRestoreOSDData(void);
extern void RTDFlashLoadColorSetting(BYTE ucRegion);
extern void RTDFlashSaveColorSetting(BYTE ucColorTempType);
extern void RTDFlashRestoreColorSetting(void);
extern void RTDFlashRestoreUserColorSetting(void);
extern void RTDFlashLoadOsdInputSourceData(BYTE ucSource);
extern void RTDFlashSaveOsdInputSourceData(BYTE ucSource);
extern void RTDFlashRestoreOsdInputSourceData(void);
extern void RTDFlashLoadOsdInputPortData(BYTE ucPort);
extern void RTDFlashSaveOsdInputPortData(BYTE ucPort);
extern void RTDFlashRestoreOsdInputPortData(void);
extern void RTDFlashLoadOsdDisplayModeData(BYTE ucDisplayMode);
extern void RTDFlashSaveOsdDisplayModeData(BYTE ucDisplayMode);
extern void RTDFlashRestoreOsdDisplayModeData(void);
extern void RTDFlashLoadOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion);
extern void RTDFlashSaveOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion);
extern void RTDFlashRestoreOsdRegionData(void);
#if(_AUDIO_ARC_SUPPORT == _ON)
extern void RTDFlashLoadAudioArcData(void);
extern void RTDFlashSaveAudioArcData(void);
extern void RTDFalshRestoreAudioArcData(void);
#endif

#define RTDNVRamStartup()                               RTDFlashStartup()
#define RTDNVRamWholeRestore()                          RTDFlashWholeRestore()
#define RTDNVRamRestoreBacklight()                      RTDFlashRestoreBacklight()
#define RTDNVRamSaveOsdUserData()                       RTDFlashSaveOSDData()
#define RTDNVRamRestoreOsdUserData()                    RTDFlashRestoreOSDData()
#define RTDNVRamLoadColorSetting(x)                     RTDFlashLoadColorSetting(x)
#define RTDNVRamSaveColorSetting(x)                     RTDFlashSaveColorSetting(x)
#define RTDNVRamRestoreColorSetting()                   RTDFlashRestoreColorSetting()
#define RTDNVRamRestoreUserColorSetting()               RTDFlashRestoreUserColorSetting()
#define RTDNVRamLoadOsdInputSourceData(x)               RTDFlashLoadOsdInputSourceData(x)
#define RTDNVRamSaveOsdInputSourceData(x)               RTDFlashSaveOsdInputSourceData(x)
#define RTDNVRamRestoreOsdInputSourceData()             RTDFlashRestoreOsdInputSourceData()

#define RTDNVRamLoadOsdInputPortData(x)                 RTDFlashLoadOsdInputPortData(x)
#define RTDNVRamSaveOsdInputPortData(x)                 RTDFlashSaveOsdInputPortData(x)
#define RTDNVRamRestoreOsdInputPortData()               RTDFlashRestoreOsdInputPortData()

#define RTDNVRamLoadOsdDisplayModeData(x)               RTDFlashLoadOsdDisplayModeData(x)
#define RTDNVRamSaveOsdDisplayModeData(x)               RTDFlashSaveOsdDisplayModeData(x)
#define RTDNVRamRestoreOsdDisplayModeData()             RTDFlashRestoreOsdDisplayModeData()

#define RTDNVRamLoadOsdRegionData(x, y)                 RTDFlashLoadOsdRegionData((x), (y))
#define RTDNVRamSaveOsdRegionData(x, y)                 RTDFlashSaveOsdRegionData((x), (y))
#define RTDNVRamRestoreOsdRegionData()                  RTDFlashRestoreOsdRegionData()
#if(_AUDIO_ARC_SUPPORT == _ON)
#define RTDNVRamLoadAudioArcData()                      RTDFlashLoadAudioArcData()
#define RTDNVRamSaveAudioArcData()                      RTDFlashSaveAudioArcData()
#define RTDNVRamRestoreAudioArcData()                   RTDFalshRestoreAudioArcData()
#endif
#endif // End of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

extern BYTE RTDNVRamTransferOsdRegionType(BYTE ucDisplayMode, BYTE ucRegion);
extern BYTE RTDNVRamTransferOsdRegionIndex(BYTE ucDisplayMode, BYTE ucRegion);
#if(_DM_FUNCTION == _ON)
extern BYTE RTDNVRamGetDVisionModeData(WORD usOsdItemType, BYTE ucRegion);
extern void RTDNVRamSetDVisionModeData(WORD usOsdItemType, BYTE ucData, BYTE ucRegion);
extern void RTDNVRamRestoreOsdDVisionModeData(void);
#endif

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
