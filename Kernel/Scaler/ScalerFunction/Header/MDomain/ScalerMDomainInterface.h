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
// ID Code      : ScalerMDomainInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of Input Info.
//--------------------------------------------------
#define SET_MEMORY_CONFIG_SELECT(x)                    (g_stMDomainInfo.enumMemoryConfig = (x))
#define CLR_MEMORY_CONFIG_SELECT()                     (g_stMDomainInfo.enumMemoryConfig = 0)

//--------------------------------------------------
// Macros of Input Port
//--------------------------------------------------
#define SET_MDOMAIN_INPUT_PORT(x)                      (g_stMDomainInfo.enumInputPort = (x))

//--------------------------------------------------
// Macros of Source Type
//--------------------------------------------------
#define SET_MDOMAIN_SOURCE_TYPE(x)                     (g_stMDomainInfo.enumSourceType = (x))

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------
#define SET_MDOMAIN_INPUT_VFREQ(x)                     {\
                                                           g_stMDomainInputData.usVFreq = (x);\
                                                           g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVFreqAdjusted = (x);\
                                                       }
#define SET_MDOMAIN_INPUT_HFREQ(x)                     {\
                                                           g_stMDomainInputData.usHFreq = (x);\
                                                           g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHFreqAdjusted = (x);\
                                                       }
#define GET_MDOMAIN_INPUT_DATA_PATH()                  (g_stMDomainInputData.enumInputDataPath)

//--------------------------------------------------
// Macros of MDomain Output Info.
//--------------------------------------------------
#define SET_MDOMAIN_OUTPUT_RGN(x)                      (g_stMDomainOutputData.enumDDomainRegion = (x))

//--------------------------------------------------
// Macros of MDomain Color Space
//--------------------------------------------------
#define GET_MDOMAIN_COLOR_SPACE()                      (g_stMDomainInfo.b3ColorSpace)
#define SET_MDOMAIN_COLOR_SPACE(x)                     (g_stMDomainInfo.b3ColorSpace = (x))
#define CLR_MDOMAIN_COLOR_SPACE()                      (g_stMDomainInfo.b3ColorSpace = 0)

//--------------------------------------------------
// Macros of DVF
//--------------------------------------------------
#define GET_MEMORY_DVF_SELECT()                        (g_stMDomainInfo.enumDVFSelect)
#define SET_MEMORY_DVF_SELECT(x)                       {\
                                                            g_stMDomainInfo.enumDVFSelect = (x);\
                                                            if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)\
                                                            {\
                                                                SET_FS_ACTIVE_INFO_DVF_SELECT(GET_MEMORY_DVF_SELECT());\
                                                            }\
                                                       }

#define CLR_MEMORY_DVF_SELECT()                        (g_stMDomainInfo.enumDVFSelect = 0)

//--------------------------------------------------
// Macros of D Clock Freq. Info.
//--------------------------------------------------
#define SET_OUTPUT_VFREQ(x)                            (g_usMDomainDVFreq = (x))

#define GET_DISPLAY_SETTING_DB_ENABLE()                (bit)(g_stMDomainInfo.b1DisplaySettingDBEnable)
#define SET_DISPLAY_SETTING_DB_ENABLE()                (g_stMDomainInfo.b1DisplaySettingDBEnable = _TRUE)
#define CLR_DISPLAY_SETTING_DB_ENABLE()                (g_stMDomainInfo.b1DisplaySettingDBEnable = _FALSE)

//--------------------------------------------------
// Macros of Reference Input Hstart
//--------------------------------------------------
#define GET_MDOMAIN_REF_INPUT_HSTART(x)                (g_pstMDomainBackupInfo[x].b1RefIHst)
#define SET_MDOMAIN_REF_INPUT_HSTART(x)                (g_pstMDomainBackupInfo[x].b1RefIHst = _TRUE)
#define CLR_MDOMAIN_REF_INPUT_HSTART(x)                (g_pstMDomainBackupInfo[x].b1RefIHst = _FALSE)

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
//--------------------------------------------------
// Macros of 2P frame sync Info.
//--------------------------------------------------
#define GET_MTP_MEMORY_SELECT()                        (g_stMDomainInfo.enumMtPMemorySelect)
#define SET_MTP_MEMORY_SELECT(x)                       (g_stMDomainInfo.enumMtPMemorySelect = (x))

#define GET_2P_FRAME_SYNC_MAIN()                       (g_stMDomainInfo.b1FrameSyncMain)
#define SET_2P_FRAME_SYNC_MAIN(x)                      (g_stMDomainInfo.b1FrameSyncMain = (x))
#endif

#define SET_FORCE_DISPLAY_1P_MODE(x)                   (g_stMDomainInfo.b1ForceDisplay1PMode = (x))
#define GET_FORCE_DISPLAY_1P_MODE()                    (g_stMDomainInfo.b1ForceDisplay1PMode)


//--------------------------------------------------
// Macros of Memory Work Type
//--------------------------------------------------
#define GET_MEMORY_WORK_TYPE()                         (g_stMDomainInfo.enumMemoryWorkMode)

//--------------------------------------------------
// Macros of scaling setting
//--------------------------------------------------
#define GET_H_SCALE_UP()                               (g_stMDomainInfo.b1HSU)
#define GET_H_SCALE_DOWN()                             (g_stMDomainInfo.b1HSD)
#define GET_V_SCALE_UP()                               (g_stMDomainInfo.b1VSU)
#define GET_V_SCALE_DOWN()                             (g_stMDomainInfo.b1VSD)


//--------------------------------------------------
// Macros of Force 1P Mdomain Info. Using when Active state
//--------------------------------------------------
#define SET_FS_ACTIVE_INFO_DVF_SELECT(x)               (g_stMDomainFSActiveInfo.enumDVFSelect = (x))
#define GET_FS_ACTIVE_INFO_DVF_SELECT()                (g_stMDomainFSActiveInfo.enumDVFSelect)

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Macros of FRC Control Clear Param Index
//--------------------------------------------------
#define CLR_MDOMAIN_FRC_CTRL_PARAM_INDEX(x)            (g_pstMDomainBackupInfo[x].ucFRCCtrlParamIndex = 0)
#endif

#if(_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
//--------------------------------------------------
// Macros of mdomain ivs2dvs delay
//--------------------------------------------------
#define GET_MDOMAIN_IVS2DVSDELAY(x)                    (g_pstMDomainBackupInfo[x].usIVStoDVSPixels)
#define SET_MDOMAIN_IVS2DVSDELAY(x, y)                 (g_pstMDomainBackupInfo[x].usIVStoDVSPixels = (y))
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
//--------------------------------------------------
// Enumerations of Iden and Dden Relation
//--------------------------------------------------
typedef enum
{
    _IDEN_DDEN_RELATION_CHANGE = 0x00,
    _IDEN_START_LEAD_DDEN_STOP = _BIT0,
    _IDEN_START_LAG_DDEN_STOP = _BIT1,
    _IDEN_STOP_LEAD_DDEN_START = _BIT2,
    _IDEN_STOP_LAG_DDEN_START = _BIT3,
} EnumMDomainIdenDdenRelation;

#endif
//--------------------------------------------------
// Structure of MDomain Backup
//--------------------------------------------------
typedef struct
{
    BYTE ucFRCCtrlParamIndex;
    BYTE b1RefIHst : 1;
#if(_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
    WORD usIVStoDVSPixels;
#endif
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    WORD usbksubvstart;
#endif
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    EnumMDomainIdenDdenRelation enumMDomainIdenDdenRelation;
#endif
}StructMDomainBackupInfo;

typedef struct
{
    EnumDVFSelect enumDVFSelect;

#if(_M_DOMAIN_FRAMESYNC_ACTIVE_TIMING_INFO_SUPPORT == _ON)
    StructTimingInfo stMDomainFSActiveInputData;
    StructDisplayInfo stMDomainFSActiveOutputData;
#endif
}StructMDomainFSActiveInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructMDomainBackupInfo g_pstMDomainBackupInfo[_MULTI_DISPLAY_MAX];
extern StructMDomainFSActiveInfo g_stMDomainFSActiveInfo;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerMDomainControl(void);
extern void ScalerMDomainClearStatus(EnumInputDataPath enumInputDataPath);
extern void ScalerMDomainUpdateInputInfo(void);

#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
extern EnumGetIVFFromTableSearch ScalerMDomainEdidTimingInfoComparison(BYTE *pucReadArray, const StructTableSearchingSourceInfo *pstSourceInfo, StructEdidInfo *pstCatchEdidInfo, EnumInputPort enumInputPort, StructTimingInfo *pstTimingInfo);
extern void ScalerMDomainGetSourceInfoForTableSearch(EnumInputPort enumInputPort, StructTableSearchingSourceInfo *pstSourceInfo, StructTimingInfo *pstTimingInfo);
extern void ScalerMDomainEdidAnalysisGetRefInfo(StructEdidRefInfo *pstEdidRefInfo, const StructTableSearchingSourceInfo *pstSourceInfo, EnumInputPort enumInputPort, StructTimingInfo *pstTimingInfo);
extern bit ScalerMDomainEdidAnalysisCheckBoundry(const StructEdidInfo *pstEdidInfo, const StructEdidRefInfo *pstEdidRefInfo);
extern EnumGetIVFFromTableSearch ScalerMDomainCalculateIVFmaxFromCVT(WORD *pusVfreqMax, const StructTableSearchingSourceInfo *pstSourceInfo, EnumInputPort enumInputPort, StructTimingInfo *pstTimingInfo);
#endif

extern void ScalerMDomainSetDisplayFormat(EnumMemoryConfig enumMemoryConfig);
extern void ScalerMDomainCheckDisplayFormat(EnumDisplayRegion enumDisplayRegion);
extern void ScalerMDomainSetDisplayTimingGenBackground(EnumDisplayRegion enumDisplayRegion);
extern void ScalerMDomainSetDisplayTimingGenDisplayMode(EnumDisplayMode enumDisplayMode);

extern void ScalerMDomainSetDisplayTimingGenActiveEnable(EnumDDomainRegion enumDDomainRegion, EnumDisplayRegion enumDisplayRegion, bit bEnable);
extern EnumFrameSyncModeType ScalerMDomainGetFrameSyncMode(void);
extern WORD ScalerMDomainGetDVtotalLastline(void);

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
extern void ScalerMDomainSetBackground_R2(void);
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
extern void ScalerMDomainSetBackground_R3(void);
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
extern void ScalerMDomainSetActiveRegion_R2a1(void);
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
extern void ScalerMDomainSetActiveRegion_R2a2(void);
#endif

extern void ScalerMDomainSetMemoryDataBit(BYTE ucColorDepth);
extern WORD ScalerMDomainGetVerticalAdjustLimit(EnumSourceType enumSourceType);
extern bit ScalerMDomainDisplayTimingGenCheck(EnumInputPort enumInputPort);

extern BYTE ScalerMDomainGetColorDepth(void);

#if(_OD_FUNCTION == _ON)
#if(_FRC_SUPPORT == _ON)
extern void ScalerMDomainReleaseFRCMemoryBW(EnumInputDataPath enumInputPath);
#endif
#endif

extern bit ScalerMDomainMemoryCheck(EnumInputDataPath enumInputDataPath);
extern void ScalerMDomainSetDisplayTimingGenActiveRegion(EnumDDomainRegion enumDDomainRegion);

#if(_DEBUG_MESSAGE_CHECK_MDOMAIN == _ON)
extern void ScalerMDomainCheckDisplaySetting(void);
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
extern void ScalerMDomainGetBackground_R2(StructTimingFormat *pstTimingFormat);
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
extern void ScalerMDomainGetActiveRegion_R2a1(StructTimingFormat *pstTimingFormat);
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
extern void ScalerMDomainGetBackground_R3(StructTimingFormat *pstTimingFormat);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern void ScalerMDomainAspectOriginMode(bit bOn);
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
extern void ScalerMDomainFreeSyncODSetDisplayFormat(WORD usDHtotal, DWORD ulDclk, WORD usTarFreq);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern EnumEagleSightMainSubSynchronous ScalerMDomainGetEagleSightMainSubSync(void);
#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
extern void ScalerMDomainSetESOriginalModeHVStart(EnumDisplayRegion enumDisplayRegion);
#endif
#endif

#if(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
extern void ScalerMDomainBlackFrameInsertEnable(EnumFunctionOnOFF enumFunctionOnOFF, EnumMbrBFIKernelMode enumMbrBFIKernelMode);
#endif

extern bit ScalerMDomainCheckMTPFreerunFinetune(void);
