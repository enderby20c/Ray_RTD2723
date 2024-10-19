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
// ID Code      : ScalerFRCInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _PRE_READ_MEMORY                                    (4) // before DDEN line

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
#define GET_ASPECT_RATIO_MIN_DVH()                          (g_usFRCAspectRatioMinDVHeight)
#define SET_ASPECT_RATIO_MIN_DVH(x)                         (g_usFRCAspectRatioMinDVHeight = (x))
#endif

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
#define GET_FRC_TOP_BOTTOM_MODE_STATUS()                    ((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) && ((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_TB) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_T) ||\
                                                             (GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_B) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_4P)))
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of FRC on/off
//--------------------------------------------------
typedef enum
{
    _FRC_DISPLAY_ONOFF = _BIT0,
    _FRC_CAPTURE_ONOFF = _BIT2,
    _FRC_ALL_ONOFF = (_FRC_DISPLAY_ONOFF | _FRC_CAPTURE_ONOFF),
} EnumFRCOnOff;

typedef enum
{
    _DDOMAIN_SRC_FROM_FRC,
    _DDOMAIN_SRC_FROM_FRAME_SYNC_MODE,
} EnumDDomainSourceSelect;

typedef enum
{
    _IMG_CMP_PARAM_OFF = 0,
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
    _IMG_CMP_PARAM_LLB_12,
    _IMG_CMP_PARAM_LLB_11,
    _IMG_CMP_PARAM_LLB_10,
    _IMG_CMP_PARAM_LLB_9,
    _IMG_CMP_PARAM_LLB_8,
    _IMG_CMP_PARAM_LLB_7,
    _IMG_CMP_PARAM_LLB_6,
#endif
#endif
} EnumImgCmpParamIndex;

typedef enum
{
    _FRC_LATENCY_SMALL = (_REGION_INDEX_0 | (_ENABLE << 1)),
    _FRC_LATENCY_MEDIUM = (_REGION_INDEX_1 | (_ENABLE << 1)),
    _FRC_LATENCY_LARGE = (_REGION_INDEX_0 | (_DISABLE << 1)),
} EnumFRCLatency;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
extern WORD g_usFRCAspectRatioMinDVHeight;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerFRCGetMDispPathCount(EnumMDomainDisplayDataPath enumMDispPath);
extern EnumMDomainDisplayDataPath ScalerFRCGetMDispPath(EnumInputDataPath enumInputPath);
extern void ScalerFRCEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath enumInputPath, bit bEn);
extern void ScalerFRCSetSourceSelect(EnumInputDataPath enumInputPath, EnumDDomainSourceSelect enumSourceSelect);

#if(_FRC_SUPPORT == _ON)
extern void ScalerFRCChannelMuteDTGEnable(EnumInputDataPath enumInputPath, EnumDDomainRegion enumDDomainRegion, EnumDisplayRegion enumDisplayRegion, bit bEn);
extern void ScalerFRCWaitIVSAdjust(EnumMemoryFrameBufferType enumMemoryFrameBufferType, EnumInputDataPath enumInputPath);
extern void ScalerFRCSetPreRead(EnumInputDataPath enumInputPath);
extern void ScalerFRCWaitWriteFrameBufFinish(void);
extern EnumInputDataPath ScalerFRCDispSynchronizeCheck(EnumInputDataPath enumInputDataPath);
extern bit ScalerFRCGetImgCmpStatus(EnumDisplayRegion enumDisplayRegion);

#if((_FREEZE_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
extern void ScalerFRCFixSlowSideBlkSel(EnumInputDataPath enumInputPath, bit bEn);
#endif

extern EnumImgCmpParamIndex ScalerFRCImgCmpGetPara(BYTE ucRegionIndex);
extern bit ScalerFRCImgCmpGetActive(BYTE ucRegionIndex);

#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern EnumAdvancedHDR10FRCStatus ScalerFRCGetAdvancedHDR10FRCStatus(void);
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
extern bit ScalerFRC2PFrameSyncEnable(EnumDisplayMode enumDisplayMode);
extern bit ScalerFRC2PFrameSyncBypassFrameSyncRegion(void);
#endif
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
extern void ScalerFRCEOtoFBControl(EnumInputDataPath enumInputPath, WORD usHwidth, bit bEn);
extern void ScalerFRCFBtoEOControl(EnumInputDataPath enumInputPath, WORD usHwidth, bit bEn);
#endif
extern bit ScalerFRCGetEOtoFBStatus(void);
extern bit ScalerFRCGetFBtoEOStatus(void);

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern void ScalerFRCAdjustAllmDelay(EnumInputPort enumInputPort, EnumSourceType enumSourceType);
#endif

#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
extern void ScalerFRCSetInitialBoundaryforRotation(void);
#endif

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
extern void ScalerFRCResetFBTBDisplayModeParam(EnumInputDataPath enumInputDataPath);
#endif
#endif

extern void ScalerFRCCapFifoOvflWDDisable(EnumInputDataPath enumInputDataPath);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern void ScalerFRCEagleSightLowLatency(EnumFRCLatency enumFRCLatency);
#endif