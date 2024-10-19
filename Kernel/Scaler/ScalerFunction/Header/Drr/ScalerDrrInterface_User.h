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
// ID Code      : ScalerDrrInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DRR_SUPPORT == _ON)
typedef struct
{
    WORD usIHwidth;
    WORD usIVheight;
    WORD usIHtotal;
    WORD usPixelClk;
    WORD usIVfreq;
} StructDrrTimingInfo;

#if(_FREESYNC_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Enum for DP FreeSync IVF Max
//--------------------------------------------------
typedef enum
{
    _DP_FREESYNC_WITH_IVF_MAX = 0x00,
    _DP_FREESYNC_WITHOUT_IVF_MAX,
} EnumDrrFreeSyncDpGetIVF;
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Enum for HDMI FreeSync IVF Max
//--------------------------------------------------
typedef enum
{
    _HDMI_FREESYNC_WITH_IVF_MAX = 0x00,
    _HDMI_FREESYNC_WITHOUT_IVF_MAX,
} EnumDrrFreeSyncHdmiGetIVF;
#endif
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
//--------------------------------------------------
// Enum for HDMI VRR IVF Max
//--------------------------------------------------
typedef enum
{
    _HDMI21_VRR_WITH_IVF_MAX = 0x00,
    _HDMI21_VRR_WITHOUT_IVF_MAX,
} EnumDrrVrrHdmiGetIVF;
#endif
#endif

//--------------------------------------------------
// Enum for DRR Enable Type
//--------------------------------------------------
typedef enum
{
    _DRR_FREESYNC_TYPE = 0x00,
    _DRR_HDMI21_VRR_TYPE, // Both VRR & VRR+FVA
    _DRR_DP_AS_TYPE,
    _DRR_DP_BOTHFSAS_TYPE,
    _DRR_TYPE,
    _DRR_NONE_TYPE,
} EnumDrrType;
//--------------------------------------------------
// Enumerations of FREESYNC Support
//--------------------------------------------------
typedef enum
{
    _FREESYNC_SUPPORT_OFF = 0x00,
    _FREESYNC_SUPPORT_ON,
} EnumFreeSyncSupport;

//--------------------------------------------------
// Enumerations of DP ADAPTIVESYNC Support
//--------------------------------------------------
typedef enum
{
    _DP_ADAPTIVESYNC_SUPPORT_OFF = 0x00,
    _DP_ADAPTIVESYNC_SUPPORT_ON,
} EnumDpAdaptiveSyncSupport;

//--------------------------------------------------
// Enumerations of SPD Info
//--------------------------------------------------
typedef enum
{
    _SPD_INFO_OUI,
    _SPD_INFO_FREESYNC_SUPPORT,
    _SPD_INFO_FREESYNC_ENABLE,
    _SPD_INFO_FREESYNC_ACTIVE,
    _SPD_INFO_FRAME_TYPE,
    _SPD_INFO_FREESYNC_MIN_VFREQ,
    _SPD_INFO_FREESYNC_MAX_VFREQ,
    _SPD_INFO_SEAMLESS_LOCAL_DIMMING_DISABLE_CONTROL,
    _SPD_INFO_PQ_EOTF_ACTIVE,
    _SPD_INFO_GAMMA_2_2_EOTF_ACTIVE,
    _SPD_INFO_TARGET_OUTPUT_PIXEL_RATE,
    _SPD_INFO_FIXED_RATE_CONTENT_ACTIVE,
} EnumAmdSpdInfoContent;

//--------------------------------------------------
// Enumerations of HDMI21 VTEM(FVAVRR) Info
//--------------------------------------------------
typedef enum
{
    _HDMI21_VTEM_INFO_VRR_EN,
    _HDMI21_VTEM_INFO_M_CONST,
    _HDMI21_VTEM_INFO_FVA_FACTOR_M1,
    _HDMI21_VTEM_INFO_BASE_VFRONT,
    _HDMI21_VTEM_INFO_BASE_REFRESH_RATE,
    _HDMI21_VTEM_INFO_QMS_EN,
    _HDMI21_VTEM_NEXT_TFR,
} EnumHdmi21VtemInfoContent;

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Struct for AMD AUPI Info
//--------------------------------------------------
typedef struct
{
    BYTE ucPanelManufactureIdL;
    BYTE ucPanelManufactureIdM;
    BYTE ucPanelIdL;
    BYTE ucPanelIdM;
    BYTE ucFwCheckSumL;
    BYTE ucFwCheckSumM;
    BYTE ucScalerDeviceIdL;
    BYTE ucScalerDeviceIdM;
} StructDrrAmdAupiInfo;
#endif

//--------------------------------------------------
// Struct for Dt Scan Force Frame Buffer
//--------------------------------------------------
typedef struct
{
    WORD usIVheight;
    WORD usDVheight;
} StructDtScanForceFrameBuffer;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

