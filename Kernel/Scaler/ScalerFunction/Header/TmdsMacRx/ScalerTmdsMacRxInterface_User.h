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
// ID Code      : ScalerTmdsMacRxInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of AVI Info Frame Contents
//--------------------------------------------------
typedef enum
{
    _AVI_INFO_COLOR_SPACE,
    _AVI_INFO_COLORIMETRY,
    _AVI_INFO_EXTENDED_COLORIMETRY,
    _AVI_INFO_ADD_EXTENDED_COLORIMETRY,
    _AVI_INFO_YCC_QUANTIZATION,
    _AVI_INFO_RGB_QUANTIZATION,
    _AVI_INFO_SCAN_INFO,
    _AVI_INFO_IT_CONTENT,
    _AVI_INFO_CONTENT_TYPE,
    _AVI_INFO_PIXEL_REPETITION,
    _AVI_INFO_AR,
    _AVI_INFO_VIC,
    _AVI_INFO_FR,
    _AVI_INFO_RID,
} EnumAviInfoContent;

//--------------------------------------------------
// Enumerations of VRR Support_F
//--------------------------------------------------
typedef enum
{
    _HDMI21_VRR_SUPPORT_OFF = 0x00,
    _HDMI21_VRR_SUPPORT_ON,
} EnumHdmi21VrrSupport;

//--------------------------------------------------
// Enumerations of Z0/HPD Type
//--------------------------------------------------
typedef enum
{
    _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME = 0x00,
    _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE,
    _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE,
} EnumHdmiZ0HpdType;

//--------------------------------------------------
// Enumerations of Z0 Status
//--------------------------------------------------
typedef enum
{
    _HDMI_Z0_LOW = 0x00,
    _HDMI_Z0_HIGH,
} EnumHdmiZ0Status;

//--------------------------------------------------
// Enumerations of HDCP Type
//--------------------------------------------------
typedef enum
{
    _HDCP_BY_PROJECT_DEFINE = 0x00,
    _TMDS_HDCP_14,
    _TMDS_HDCP_NONE,
} EnumTmdsHdcpType;

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
//--------------------------------------------------
// Structure of SPD Info(VN1-4,PD1-16)
//--------------------------------------------------
typedef struct
{
    BYTE pucHdmiVendorName[8];
    BYTE pucHdmiProductDescription[16];
    bit b1StructValuable;
} StructHdmiSpdInfo;

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
typedef struct
{
    BYTE pucHdmiFreesyncInfo[28];
    bit b1FreesyncValuable;
} StructHdmiSpdFsInfo;
#endif

//--------------------------------------------------
// Enumerations of GAME PRODUCT DESCRIPTION
//--------------------------------------------------
typedef enum
{
    _PRODUCT_DESCRIPTION_NONE = 0x00,
    _PRODUCT_DESCRIPTION_PS4,
    _PRODUCT_DESCRIPTION_PS5,
    _PRODUCT_DESCRIPTION_XBOX,
    _PRODUCT_DESCRIPTION_XBOX_ONE,
    _PRODUCT_DESCRIPTION_NVIDIA,
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
    _PRODUCT_DESCRIPTION_XBOX_SERIES,
    _PRODUCT_DESCRIPTION_PS_SERIES,
#endif
} EnumHdmiSpdProuductlInfo;
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of 3D Video status
//--------------------------------------------------
typedef enum
{
    _HDMI_2D_VIDEO_FORMAT,
    _HDMI_3D_VIDEO_FORMAT,
} EnumVideoDimensionType;
#endif

//--------------------------------------------------
// Enumerations of AVI Content Type
//--------------------------------------------------
typedef enum
{
    _CONTENT_TYPE_N0_DATA,
    _CONTENT_TYPE_PHOTO,
    _CONTENT_TYPE_CINEMA,
    _CONTENT_TYPE_GAME,
    _CONTENT_TYPE_GRAPHICS,
} EnumContentType;

#if(_HDMI_SUPPORT == _ON)
typedef enum
{
    _HDMI_5V_STATUS_LOW = 0x00,
    _HDMI_5V_STATUS_HIGH,
} EnumUserHdmi5vStatus;
#endif

#if(_DELL_HDMI_HPD_DDC_STYLE_SUPPORT == _ON)
typedef enum
{
    _DISABLE_WHEN_AC_ON = 0x00,
    _ENABLE_WHEN_AC_ON,
} EnumUserDdcStatus;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

