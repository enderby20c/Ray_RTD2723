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
// ID Code      : RTD2020UserAdjust.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST__

#include "RTD2020UserInclude.h"
#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#include "./TTS/RTD2020UserTTSRecordList.h"
#endif
#endif

#if(_OSD_TYPE == _REALTEK_2020_OSD)
//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#if(_SHARPNESS_FUNCTION == _ON)
#if((_HW_HSU_128TAPS_SUPPORT == _ON) || (_HW_VSU_128TAPS_SUPPORT == _ON))
BYTE code tSU_COEF_128_TAPS_0[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable0.h"
};

BYTE code tSU_COEF_128_TAPS_2[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable2.h"
};

BYTE code tSU_COEF_128_TAPS_4[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable4.h"
};

BYTE code tSU_COEF_128_TAPS_6[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable6.h"
};

BYTE code tSU_COEF_128_TAPS_8[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable8.h"
};

BYTE * code tSCALE_128TAPS_NORMAL_COEF_TABLE[] =
{
    tSU_COEF_128_TAPS_0,
    tSU_COEF_128_TAPS_2,
    tSU_COEF_128_TAPS_4,
    tSU_COEF_128_TAPS_6,
    tSU_COEF_128_TAPS_8,
};
#endif // End of #if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))

#if(_HW_HSU_128TAPS_SUPPORT == _ON)
BYTE code tSU_1to1_COEF_128_TAPS_0[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table0.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_2[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table2.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_4[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table4.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_6[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table6.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_8[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table8.h"
};

BYTE * code tSCALE_128TAPS_1to1_COEF_TABLE[] =
{
    tSU_1to1_COEF_128_TAPS_0,
    tSU_1to1_COEF_128_TAPS_2,
    tSU_1to1_COEF_128_TAPS_4,
    tSU_1to1_COEF_128_TAPS_6,
    tSU_1to1_COEF_128_TAPS_8,
};
#endif // End of #if(_HSU_128TAPS_SUPPORT == _ON)

#if((_HW_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
BYTE code tSU_COEF_96_TAPS_0[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable0.h"
};

BYTE code tSU_COEF_96_TAPS_2[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable2.h"
};

BYTE code tSU_COEF_96_TAPS_4[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable4.h"
};

BYTE code tSU_COEF_96_TAPS_6[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable6.h"
};

BYTE code tSU_COEF_96_TAPS_8[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable8.h"
};

BYTE * code tSCALE_96TAPS_NORMAL_COEF_TABLE[] =
{
    tSU_COEF_96_TAPS_0,
    tSU_COEF_96_TAPS_2,
    tSU_COEF_96_TAPS_4,
    tSU_COEF_96_TAPS_6,
    tSU_COEF_96_TAPS_8,
};
#endif // End of #if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))

#if(_HW_HSU_96TAPS_SUPPORT == _ON)
BYTE code tSU_1to1_COEF_96_TAPS_0[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table0.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_2[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table2.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_4[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table4.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_6[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table6.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_8[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table8.h"
};

BYTE * code tSCALE_96TAPS_1to1_COEF_TABLE[] =
{
    tSU_1to1_COEF_96_TAPS_0,
    tSU_1to1_COEF_96_TAPS_2,
    tSU_1to1_COEF_96_TAPS_4,
    tSU_1to1_COEF_96_TAPS_6,
    tSU_1to1_COEF_96_TAPS_8,
};
#endif // End of #if(_HSU_96TAPS_SUPPORT == _ON)

#endif // End of #if(_SHARPNESS_SUPPORT == _ON)

//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (ScalingDown)
//----------------------------------------------------------------------------------------------------
#if(_SD_TABLE_SEL_FUNCTION == _ON)
BYTE code tSD_COEF_128_TAPS_0[] =
{
#include "./ScalingDown/ScalingDown128TapsNormalTable0.h"
};
BYTE code tSD_COEF_128_TAPS_1[] =
{
#include "./ScalingDown/ScalingDown128TapsNormalTable1.h"
};
BYTE code tSD_COEF_128_TAPS_2[] =
{
#include "./ScalingDown/ScalingDown128TapsNormalTable2.h"
};
BYTE code tSD_COEF_128_TAPS_3[] =
{
#include "./ScalingDown/ScalingDown128TapsNormalTable3.h"
};
BYTE code tSD_COEF_128_TAPS_4[] =
{
#include "./ScalingDown/ScalingDown128TapsNormalTable4.h"
};
BYTE * code tSCALEDOWN_128TAPS_NORMAL_COEF_TABLE[] =
{
    tSD_COEF_128_TAPS_0,
    tSD_COEF_128_TAPS_1,
    tSD_COEF_128_TAPS_2,
    tSD_COEF_128_TAPS_3,
    tSD_COEF_128_TAPS_4,
};
BYTE code tSD_COEF_64_TAPS_0[] =
{
#include "./ScalingDown/ScalingDown64TapsNormalTable0.h"
};
BYTE code tSD_COEF_64_TAPS_1[] =
{
#include "./ScalingDown/ScalingDown64TapsNormalTable1.h"
};
BYTE code tSD_COEF_64_TAPS_2[] =
{
#include "./ScalingDown/ScalingDown64TapsNormalTable2.h"
};
BYTE code tSD_COEF_64_TAPS_3[] =
{
#include "./ScalingDown/ScalingDown64TapsNormalTable3.h"
};
BYTE code tSD_COEF_64_TAPS_4[] =
{
#include "./ScalingDown/ScalingDown64TapsNormalTable4.h"
};
BYTE * code tSCALEDOWN_64TAPS_NORMAL_COEF_TABLE[] =
{
    tSD_COEF_64_TAPS_0,
    tSD_COEF_64_TAPS_1,
    tSD_COEF_64_TAPS_2,
    tSD_COEF_64_TAPS_3,
    tSD_COEF_64_TAPS_4,
};
//ByPassMode
BYTE code tSD_BYPASS_COEF_128_TAPS_0[] =
{
#include "./ScalingDown/ScalingDown128TapsByPassTable0.h"
};
BYTE code tSD_BYPASS_COEF_128_TAPS_1[] =
{
#include "./ScalingDown/ScalingDown128TapsByPassTable1.h"
};
BYTE code tSD_BYPASS_COEF_128_TAPS_2[] =
{
#include "./ScalingDown/ScalingDown128TapsByPassTable2.h"
};
BYTE code tSD_BYPASS_COEF_128_TAPS_3[] =
{
#include "./ScalingDown/ScalingDown128TapsByPassTable3.h"
};
BYTE code tSD_BYPASS_COEF_128_TAPS_4[] =
{
#include "./ScalingDown/ScalingDown128TapsByPassTable4.h"
};
BYTE * code tSCALEDOWN_128TAPS_BYPASS_COEF_TABLE[] =
{
    tSD_BYPASS_COEF_128_TAPS_0,
    tSD_BYPASS_COEF_128_TAPS_1,
    tSD_BYPASS_COEF_128_TAPS_2,
    tSD_BYPASS_COEF_128_TAPS_3,
    tSD_BYPASS_COEF_128_TAPS_4,
};
BYTE code tSD_BYPASS_COEF_64_TAPS_0[] =
{
#include "./ScalingDown/ScalingDown64TapsByPassTable0.h"
};
BYTE code tSD_BYPASS_COEF_64_TAPS_1[] =
{
#include "./ScalingDown/ScalingDown64TapsByPassTable1.h"
};
BYTE code tSD_BYPASS_COEF_64_TAPS_2[] =
{
#include "./ScalingDown/ScalingDown64TapsByPassTable2.h"
};
BYTE code tSD_BYPASS_COEF_64_TAPS_3[] =
{
#include "./ScalingDown/ScalingDown64TapsByPassTable3.h"
};
BYTE code tSD_BYPASS_COEF_64_TAPS_4[] =
{
#include "./ScalingDown/ScalingDown64TapsByPassTable4.h"
};
BYTE * code tSCALEDOWN_64TAPS_BYPASS_COEF_TABLE[] =
{
    tSD_BYPASS_COEF_64_TAPS_0,
    tSD_BYPASS_COEF_64_TAPS_1,
    tSD_BYPASS_COEF_64_TAPS_2,
    tSD_BYPASS_COEF_64_TAPS_3,
    tSD_BYPASS_COEF_64_TAPS_4,
};
#endif

//----------------------------------------------------------------------------------------------------
// IR TABLE
//----------------------------------------------------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE code tIR_INITIAL_TABLE[] =
{
#if(_IR_PROTOCAL == _IR_NEC_DTV328)
    #include "IRRemote/tIR_NEC_DTV328.h"

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
    #include "IRRemote/tIR_SONY_B102P.h"

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
    #include "IRRemote/tIR_PHILIPS_RC6.h"

#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)
};
#endif

#if(_ANTI_ALIASING_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// ANTIALIASING TABLE
//----------------------------------------------------------------------------------------------------
DWORD code tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_0[] =
{
#include "./AntiAliasing/AntiAliasingEdgeEnhanceTable0.h"
};
DWORD code tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_1[] =
{
#include "./AntiAliasing/AntiAliasingEdgeEnhanceTable1.h"
};

DWORD code tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_2[] =
{
#include "./AntiAliasing/AntiAliasingEdgeEnhanceTable2.h"
};

DWORD code tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_3[] =
{
#include "./AntiAliasing/AntiAliasingEdgeEnhanceTable3.h"
};

DWORD code tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_4[] =
{
#include "./AntiAliasing/AntiAliasingEdgeEnhanceTable4.h"
};

DWORD * code tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_TABLE[] =
{
    tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_0,
    tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_1,
    tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_2,
    tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_3,
    tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_4,
};

DWORD code tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_0[] =
{
#include "./AntiAliasing/AntiAliasingNoiseReductionTable0.h"
};

DWORD code tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_1[] =
{
#include "./AntiAliasing/AntiAliasingNoiseReductionTable1.h"
};

DWORD code tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_2[] =
{
#include "./AntiAliasing/AntiAliasingNoiseReductionTable2.h"
};

DWORD code tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_3[] =
{
#include "./AntiAliasing/AntiAliasingNoiseReductionTable3.h"
};

DWORD code tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_4[] =
{
#include "./AntiAliasing/AntiAliasingNoiseReductionTable4.h"
};

DWORD * code tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_TABLE[] =
{
    tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_0,
    tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_1,
    tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_2,
    tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_3,
    tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_4,
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PIXEL_SHIFT_SUPPORT == _ON)
EnumPixelShiftState g_enumPixelShiftState = _PIXEL_SHIFT_DEFAULT;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON)
#if((_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get the Modify Edid Task
// Input Value  : enumInputPort
// Output Value : EnumEdidModifyTarget
//--------------------------------------------------
EnumEdidModifyTarget UserAdjustGetEdidModifyTarget(EnumInputPort enumInputPort)
{
    EnumEdidModifyTarget enumEdidModifyTarget = _EDID_MODIFY_NONE;
    enumInputPort = enumInputPort;

#if(_HLG_SUPPORT == _ON)
    if((GET_OSD_HDR_MODE(enumInputPort) == _HDR10_HLG_MODE_FORCE_HLG) ||
       (GET_OSD_HDR_MODE(enumInputPort) == _HDR10_HLG_MODE_AUTO))
    {
        enumEdidModifyTarget |= _EDID_MODIFY_HLG;
    }
#endif

#if(_DSC_DECODER_SUPPORT == _ON)
    if(UserInterfaceDscDecoderGetEnable(enumInputPort) == _DSC_DECODER_SUPPORT_ON)
    {
        enumEdidModifyTarget |= _EDID_MODIFY_HDMI_DSC;
    }
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
    if(UserInterfaceFreeSyncGetEnable(enumInputPort) == _FREESYNC_SUPPORT_ON)
    {
        enumEdidModifyTarget |= _EDID_MODIFY_HDMI_FREESYNC_MCCS;
    }
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
    if(UserInterfaceArcTxEdidGetModifyEnable() == _EDID_AUDIO_CAP_NEED_TO_MODIFY)
    {
        enumEdidModifyTarget |= _EDID_MODIFY_AUDIO_CAPABILITY;
    }
#endif

    return enumEdidModifyTarget;
}
#endif
#endif

//--------------------------------------------------
// Description  : Get OSD display mode
// Input Value  : None
// Output Value : system display mode
//--------------------------------------------------
EnumDisplayMode UserAdjustGetMultiDisplayMode(void)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
        case _OSD_DM_1P:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            return _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT;
#else
            return _DISPLAY_MODE_1P;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:
            return _DISPLAY_MODE_2P_PIP;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:
            if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
            {
                return _DISPLAY_MODE_2P_PBP_LR_L_LARGE;
            }
            else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
            {
                return _DISPLAY_MODE_2P_PBP_LR_R_LARGE;
            }
            else
            {
                return _DISPLAY_MODE_2P_PBP_LR_EQUAL;
            }
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:
            return _DISPLAY_MODE_2P_PBP_TB;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_FLAG:
            return _DISPLAY_MODE_3P_FLAG;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_L:
            return _DISPLAY_MODE_3P_SKEW_L;

        case _OSD_DM_3P_SKEW_R:
            return _DISPLAY_MODE_3P_SKEW_R;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_T:
            return _DISPLAY_MODE_3P_SKEW_T;

        case _OSD_DM_3P_SKEW_B:
            return _DISPLAY_MODE_3P_SKEW_B;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:
            return _DISPLAY_MODE_4P;
#endif
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustResetDisplayByPort(EnumDisplayRegion enumDisplayRegion)
{
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(SysModeGetDisplayMode() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
#if(_BORDER_WINDOW_FUNCTION == _ON)
        UserCommonColorBorderWindowDisable(_DB_APPLY_NONE);
#endif
        UserCommonDDomainBackgroundSetColor(_DDOMAIN_RGN_ALL, 0, 0, 0, _DB_APPLY_POLLING);
        UserCommonDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _ENABLE);
        UserCommonColorHLWinTypeAdjust(_DB_APPLY_NO_POLLING);
        enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
    }
#endif

    if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
    {
        if((SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_ACTIVE) ||
           (SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_DISPLAY_READY))
        {
            SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
#else
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
        }
    }
    else
    {
        EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);
        EnumDisplayRegion enumIndexRegion = _DISPLAY_RGN_NONE;
        BYTE ucIndex = 0x00;

        for(ucIndex = 0x00; ucIndex < SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX); ++ucIndex)
        {
            enumIndexRegion = SysRegionGetDisplayRegion(ucIndex);

            if(SysRegionGetInputPort(enumIndexRegion) == enumInputPort)
            {
                if(enumIndexRegion == enumDisplayRegion)
                {
                    if((SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_ACTIVE) ||
                       (SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_DISPLAY_READY))
                    {
                        SysModeSetDisplayTarget(enumDisplayRegion);
                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                    }
                }
                else
                {
                    if((SysRegionGetDisplayState(enumIndexRegion) == _DISPLAY_STATE_ACTIVE) ||
                       (SysRegionGetDisplayState(enumIndexRegion) == _DISPLAY_STATE_DISPLAY_READY))
                    {
                        SysModeResetDisplayState(enumIndexRegion);
                    }
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Adjust backlight
// Input Value  : usBacklight(0 ~ _BACKLIGHT_MAX)
// Output Value : None
//--------------------------------------------------
void UserAdjustBacklight(WORD usBacklight)
{
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
    usBacklight = _BACKLIGHT_MIN + ((DWORD)(_BACKLIGHT_MAX - _BACKLIGHT_MIN) * usBacklight) / _BACKLIGHT_MAX;
#else
    usBacklight = ((DWORD)(usBacklight) * (_DEVICE_LED_DRIVER_PWM_MAX)) / _BACKLIGHT_MAX;
#endif

#if(_BACKLIGHT_PWM_INVERSE == _ON)
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
    usBacklight = _BACKLIGHT_MAX - usBacklight;
#endif
#endif

    // Adjust backlight by changing PWM duty
    PCB_BACKLIGHT_PWM(usBacklight);
}

#if((_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE) && ((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : Get Ext HDMI EDID Index
// Input Value  : enumInputPort
// Output Value : Edid Index Enum
//--------------------------------------------------
EnumEdidSelection UserAdjustGetHdmiExternalEdidIndex(EnumInputPort enumInputPort)
{
    EnumEdidSelection enumEdidIndex = _EDID_INDEX_0;

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    EnumEdidSelection enumLastIndexOfExternalEdid = _EDID_INDEX_2;
    enumEdidIndex = UserInterfaceEdidGetMultiHdmiEdidIndex(enumInputPort);

    // out of max external edid index will be embedded edid
    if(enumEdidIndex > enumLastIndexOfExternalEdid)
    {
        enumEdidIndex = enumLastIndexOfExternalEdid;
    }
#else
    enumEdidIndex = _EDID_INDEX_0;
#endif

    return enumEdidIndex;
}
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : enumInputPort
// Output Value : Edid Index
//--------------------------------------------------
EnumEdidSelection UserAdjustGetDpEdidIndex(EnumInputPort enumInputPort)
{
    BYTE ucIndex = 0;
    BYTE ucDpResolution = 0;
    BYTE ucOsdCount = 3;

// #if(ADD_NEW_SUPPORT == _ON)
//     if(GET_OSD_ENABLE == _ON)
//     {
//         ucIndex = (ucIndex << 1) + 1;
//     }
//     else
//     {
//         ucIndex = (ucIndex << 1);
//     }
// #endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    if(GET_OSD_DP_ADAPTIVE_SYNC() == _ON)
    {
        ucIndex = (ucIndex << 1) + 1;
    }
    else
    {
        ucIndex = (ucIndex << 1);
    }
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_OSD_FREE_SYNC_STATUS() == _ON)
    {
        ucIndex = (ucIndex << 1) + 1;
    }
    else
    {
        ucIndex = (ucIndex << 1);
    }
#endif

#if(_DP_HDR10_SUPPORT == _ON)
    if(UserInterfaceColorHDRGetHDR10ModeStatus(enumInputPort) != _HDR10_MODE_OFF)
    {
        ucIndex = (ucIndex << 1) + 1;
    }
    else
    {
        ucIndex = (ucIndex << 1);
    }
#endif

    ucIndex = ucIndex * ucOsdCount;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D0_SELECT);
            break;
        case _D1_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D1_SELECT);
            break;
        case _D2_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D2_SELECT);
            break;
        case _D6_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D6_SELECT);
            break;
        default:
            break;
    }

    switch(ucDpResolution)
    {
        case _DP_EDID_1080P:
#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
        case _DP_EDID_4K2K_240HZ:
#endif
            break;

        case _DP_EDID_2560_1440:
#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
        case _DP_EDID_5K_144HZ:
#endif
            ucIndex += 0x01;
            break;

        case _DP_EDID_4K2K_60HZ:
#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
        case _DP_EDID_8K_60HZ:
#endif
            ucIndex += 0x02;
            break;

        default:
            break;
    }

    return ucIndex;
}
#endif

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
//--------------------------------------------------
// Description  : Adjust TTS Play Event
// Input Value  : EnumAudioTtsEvent
// Output Value : None
//--------------------------------------------------
void UserAdjustAudioTtsPlayEvent(EnumAudioTtsEvent enumTtsEvent)
{
    BYTE ucIndex = 0;
    StructAudioTtsSegment pstTtsSegment[_AUDIO_TTS_DATA_SEGMENT_SIZE];
    EnumAudioTtsPlayStatus enumTtsPlayStatus = UserCommonAudioTtsGetPlaybackStatus();

    if(enumTtsPlayStatus == _TTS_PROCESSING)
    {
        DebugMessageAudio("[TTS] Playback Still Processing", 0x00);

        return;
    }
    else if(enumTtsPlayStatus == _TTS_PLAY_ERROR)
    {
        DebugMessageAudio("[TTS] Playback Error", 0x00);

        // Check Error Segment
        switch(UserCommonAudioTtsGetErrorSegment())
        {
            case 0x00:
                break;

            default:
                break;
        }

        return;
    }

    // TTS Event Judgment
    switch(enumTtsEvent)
    {
        case _AUDIO_TTS_EVENT_POWER_ON:

            DebugMessageAudio("[TTS] Set POWER_ON event", _AUDIO_TTS_EVENT_POWER_ON);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_POWER_ON;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_POWER_ON;
            ucIndex++;

            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DISPLAY_INFORMATION;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DISPLAY_INFORMATION;
            ucIndex++;

            // Check Input Port
            switch(SysSourceGetInputPort())
            {
                case _A0_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ANALOG_PORT_0;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ANALOG_PORT_0;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_VGA_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_VGA_PORT;
                    ucIndex++;

                    break;

                case _D0_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_0;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_0;
                    ucIndex++;

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D1_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_1;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_1;
                    ucIndex++;

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D2_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_2;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_2;
                    ucIndex++;

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D3_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_3;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_3;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
                    ucIndex++;

                    break;

                case _D4_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_4;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_4;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
                    ucIndex++;

                    break;

                default:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ERROR;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ERROR;
                    ucIndex++;

                    break;
            }

            // Resolution
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_1920_BY_1080_60_HZ;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_1920_BY_1080_60_HZ;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_POWER_OFF:
        case _AUDIO_TTS_EVENT_POWER_SAVING:

            DebugMessageAudio("[TTS] Set POWER_OFF event", _AUDIO_TTS_EVENT_POWER_OFF);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_POWER_OFF;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_POWER_OFF;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_KEY_MENU:

            DebugMessageAudio("[TTS] Set MENU event", _AUDIO_TTS_EVENT_KEY_MENU);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_MENU;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_MENU;
            ucIndex++;

            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_PICTURE;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_PICTURE;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_KEY_LEFT:

            DebugMessageAudio("[TTS] Set KEY_LEFT event", _AUDIO_TTS_EVENT_KEY_LEFT);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[0].ulDataAddress = _TTS_ADDRESS_DISPLAY_INFORMATION;
            pstTtsSegment[0].usDataLength = _TTS_LENGTH_DISPLAY_INFORMATION;
            ucIndex++;

            // Check Input Port
            switch(SysSourceGetInputPort())
            {
                case _A0_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ANALOG_PORT_0;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ANALOG_PORT_0;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_VGA_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_VGA_PORT;
                    ucIndex++;

                    break;

                case _D0_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_0;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_0;
                    ucIndex++;

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D1_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_1;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_1;
                    ucIndex++;

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D2_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_2;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_2;
                    ucIndex++;

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D3_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_3;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_3;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
                    ucIndex++;

                    break;

                case _D4_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_4;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_4;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
                    ucIndex++;

                    break;

                default:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ERROR;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ERROR;
                    ucIndex++;

                    break;
            }

            // Resolution
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_1920_BY_1080_60_HZ;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_1920_BY_1080_60_HZ;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_KEY_RIGHT:

            DebugMessageAudio("[TTS] Set KEY_RIGHT event", _AUDIO_TTS_EVENT_KEY_RIGHT);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_INPUT_SOURCE;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_INPUT_SOURCE;
            ucIndex++;

            // if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _A0_INPUT_PORT))
            if(SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT)
            {
                // Auto Search
                pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_AUTO_SEARCH;
                pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_AUTO_SEARCH;
                ucIndex++;
            }
            else
            {
                // Check Input Port
                switch(SysSourceGetInputPort())
                {
                    case _A0_INPUT_PORT:

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ANALOG_PORT_0;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ANALOG_PORT_0;
                        ucIndex++;

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_VGA_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_VGA_PORT;
                        ucIndex++;

                        break;

                    case _D0_INPUT_PORT:

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_0;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_0;
                        ucIndex++;

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                        ucIndex++;
#else
                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                        ucIndex++;
#endif

                        break;

                    case _D1_INPUT_PORT:

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_1;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_1;
                        ucIndex++;

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                        ucIndex++;
#else
                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                        ucIndex++;
#endif

                        break;

                    case _D2_INPUT_PORT:

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_2;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_2;
                        ucIndex++;

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                        ucIndex++;
#else
                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                        ucIndex++;
#endif

                        break;

                    case _D3_INPUT_PORT:

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_3;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_3;
                        ucIndex++;

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
                        ucIndex++;

                        break;

                    case _D4_INPUT_PORT:

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_4;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_4;
                        ucIndex++;

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
                        ucIndex++;

                        break;

                    default:

                        pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ERROR;
                        pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ERROR;
                        ucIndex++;

                        break;
                }
            }

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_KEY_ON:

            DebugMessageAudio("[TTS] Set ON event", _AUDIO_TTS_EVENT_KEY_ON);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ON;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ON;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_KEY_OFF:

            DebugMessageAudio("[TTS] Set OFF event", _AUDIO_TTS_EVENT_KEY_OFF);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_OFF;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_OFF;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_KEY_NUMBER:

            DebugMessageAudio("[TTS] Set NUMBER event", _AUDIO_TTS_EVENT_KEY_NUMBER);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_20;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_20;
            ucIndex++;

            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_3;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_3;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_KEY_DIGITAL:

            DebugMessageAudio("[TTS] Set DIGITAL event", _AUDIO_TTS_EVENT_KEY_DIGITAL);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_KEY_ANALOG:

            DebugMessageAudio("[TTS] Set ANALOG event", _AUDIO_TTS_EVENT_KEY_ANALOG);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ANALOG;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ANALOG;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_LOGO_SHOW:

            DebugMessageAudio("[TTS] Set OSD_LOGO_SHOW event", _AUDIO_TTS_EVENT_OSD_LOGO_SHOW);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_REALTEK;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_REALTEK;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_PICTURE:

            DebugMessageAudio("[TTS] Set PICTURE event", _AUDIO_TTS_EVENT_OSD_PICTURE);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_PICTURE;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_PICTURE;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_DISPLAY_CONFIG:

            DebugMessageAudio("[TTS] Set DISPLAY_CONFIG event", _AUDIO_TTS_EVENT_OSD_DISPLAY_CONFIG);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DISPLAY;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DISPLAY;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_COLOR:

            DebugMessageAudio("[TTS] Set COLOR event", _AUDIO_TTS_EVENT_OSD_COLOR);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_COLOR;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_COLOR;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_ADVANCE:

            DebugMessageAudio("[TTS] Set ADVANCE event", _AUDIO_TTS_EVENT_OSD_ADVANCE);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ADVANCE;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ADVANCE;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_SOURCE:

            DebugMessageAudio("[TTS] Set INPUT_SOURCE event", _AUDIO_TTS_EVENT_OSD_INPUT_SOURCE);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_INPUT_SOURCE;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_INPUT_SOURCE;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO:

            DebugMessageAudio("[TTS] Set AUDIO event", _AUDIO_TTS_EVENT_OSD_AUDIO);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_AUDIO;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_AUDIO;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_OTHER:

            DebugMessageAudio("[TTS] Set OTHER event", _AUDIO_TTS_EVENT_OSD_OTHER);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_OTHER;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_OTHER;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_DISPLAY_INFORMATION:

            DebugMessageAudio("[TTS] Set DISPLAY_INFORMATION event", _AUDIO_TTS_EVENT_OSD_DISPLAY_INFORMATION);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DISPLAY_INFORMATION;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DISPLAY_INFORMATION;
            ucIndex++;

            // Check Input Port
            switch(SysSourceGetInputPort())
            {
                case _A0_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ANALOG_PORT_0;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ANALOG_PORT_0;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_VGA_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_VGA_PORT;
                    ucIndex++;

                    break;

                case _D0_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_0;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_0;
                    ucIndex++;

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D1_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_1;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_1;
                    ucIndex++;

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D2_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_2;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_2;
                    ucIndex++;

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
                    ucIndex++;
#else
                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
                    ucIndex++;
#endif

                    break;

                case _D3_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_3;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_3;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
                    ucIndex++;

                    break;

                case _D4_INPUT_PORT:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_4;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_4;
                    ucIndex++;

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
                    ucIndex++;

                    break;

                default:

                    pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ERROR;
                    pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ERROR;
                    ucIndex++;

                    break;
            }

            // Resolution
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_1920_BY_1080_60_HZ;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_1920_BY_1080_60_HZ;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_FACTORY:

            DebugMessageAudio("[TTS] Set FACTORY event", _AUDIO_TTS_EVENT_OSD_FACTORY);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_FACTORY;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_FACTORY;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_VOLUME:

            DebugMessageAudio("[TTS] Set AUDIO_VOLUME event", _AUDIO_TTS_EVENT_OSD_AUDIO_VOLUME);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_VOLUME;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_VOLUME;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_MUTE:

            DebugMessageAudio("[TTS] Set AUDIO_MUTE event", _AUDIO_TTS_EVENT_OSD_AUDIO_MUTE);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_MUTE;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_MUTE;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_STAND_ALONG:

            DebugMessageAudio("[TTS] Set STAND_ALONG event", _AUDIO_TTS_EVENT_OSD_AUDIO_STAND_ALONG);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_STAND_ALONG;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_STAND_ALONG;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_SOURCE:

            DebugMessageAudio("[TTS] Set AUDIO_SOURCE event", _AUDIO_TTS_EVENT_OSD_AUDIO_SOURCE);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_AUDIO_SOURCE;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_AUDIO_SOURCE;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_MODE:

            DebugMessageAudio("[TTS] Set AUDIO_MODE event", _AUDIO_TTS_EVENT_OSD_AUDIO_MODE);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_SOUND_MODE;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_SOUND_MODE;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_TTS:

            DebugMessageAudio("[TTS] Set AUDIO_TTS event", _AUDIO_TTS_EVENT_OSD_AUDIO_TTS);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TTS;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TTS;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_SUPPORT:

            DebugMessageAudio("[TTS] Set AUDIO_TTS_SUPPORT event", _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_SUPPORT);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TTS_SUPPORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TTS_SUPPORT;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_TEXT_VOLUME:

            DebugMessageAudio("[TTS] Set AUDIO_TTS_TEXT_VOLUME event", _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_TEXT_VOLUME);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TTS_TEXT_VOLUME;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TTS_TEXT_VOLUME;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_MUSIC_VOLUME:

            DebugMessageAudio("[TTS] Set AUDIO_TTS_MUSIC_VOLUME event", _AUDIO_TTS_EVENT_OSD_AUDIO_TTS_MUSIC_VOLUME);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TTS_MUSIC_VOLUME;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TTS_MUSIC_VOLUME;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_AUTO:

            DebugMessageAudio("[TTS] Set INPUT_AUTO event", _AUDIO_TTS_EVENT_OSD_INPUT_AUTO);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_AUTO_SEARCH;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_AUTO_SEARCH;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_A0:

            DebugMessageAudio("[TTS] Set INPUT_A0 event", _AUDIO_TTS_EVENT_OSD_INPUT_A0);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ANALOG_PORT_0;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ANALOG_PORT_0;
            ucIndex++;

            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_VGA_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_VGA_PORT;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_D0:

            DebugMessageAudio("[TTS] Set INPUT_D0 event", _AUDIO_TTS_EVENT_OSD_INPUT_D0);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_0;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_0;
            ucIndex++;

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
            ucIndex++;
#else
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
            ucIndex++;
#endif

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_D1:

            DebugMessageAudio("[TTS] Set INPUT_D1 event", _AUDIO_TTS_EVENT_OSD_INPUT_D1);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_1;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_1;
            ucIndex++;

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
            ucIndex++;
#else
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
            ucIndex++;
#endif

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_D2:

            DebugMessageAudio("[TTS] Set INPUT_D2 event", _AUDIO_TTS_EVENT_OSD_INPUT_D2);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_2;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_2;
            ucIndex++;

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE)
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DP_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DP_PORT;
            ucIndex++;
#else
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_TYPE_C_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_TYPE_C_PORT;
            ucIndex++;
#endif

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_D3:

            DebugMessageAudio("[TTS] Set INPUT_D3 event", _AUDIO_TTS_EVENT_OSD_INPUT_D3);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_3;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_3;
            ucIndex++;

            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_D4:

            DebugMessageAudio("[TTS] Set INPUT_D4 event", _AUDIO_TTS_EVENT_OSD_INPUT_D4);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_4;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_4;
            ucIndex++;

            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_HDMI_PORT;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_HDMI_PORT;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_D5:

            DebugMessageAudio("[TTS] Set INPUT_D5 event", _AUDIO_TTS_EVENT_OSD_INPUT_D5);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_5;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_5;
            ucIndex++;

            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_OFF;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_OFF;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_OSD_INPUT_D6:

            DebugMessageAudio("[TTS] Set INPUT_D6 event", _AUDIO_TTS_EVENT_OSD_INPUT_D6);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_DIGITAL_PORT_6;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_DIGITAL_PORT_6;
            ucIndex++;

            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_OFF;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_OFF;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        case _AUDIO_TTS_EVENT_NONE:

            DebugMessageAudio("[TTS] Set NONE event", _AUDIO_TTS_EVENT_NONE);

            // Reset Index Counter
            ucIndex = 0;

            // Set TTS Data Info
            pstTtsSegment[ucIndex].ulDataAddress = _TTS_ADDRESS_ERROR;
            pstTtsSegment[ucIndex].usDataLength = _TTS_LENGTH_ERROR;
            ucIndex++;

            // Active TTS Data Play
            UserCommonAudioTtsSetPlaybackActiveEvent(pstTtsSegment, ucIndex, UserInterfaceAudioGetTtsPlayTextVolume(), UserInterfaceAudioGetTtsPlayAudioVolume());

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get OSD Aduio Volume
// Input Value  : None
// Output Value : ucVolume
//--------------------------------------------------
BYTE UserAdjustAudioGetOsdVolume(void)
{
    return GET_OSD_VOLUME();
}
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

//--------------------------------------------------
// Description  : Mute/Unmute Aduio Volume
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserAdjustAudioMuteSwitch(void)
{
    if(GET_OSD_VOLUME_MUTE() == _ENABLE)
    {
        SysAudioMuteProc(_ON);
    }
    else
    {
        SysAudioMuteProc(_OFF);
    }
}

//--------------------------------------------------
// Description  : Adjust Aduio Volume
// Input Value  : ucVolume
// Output Value : Node
//--------------------------------------------------
void UserAdjustAudioVolume(BYTE ucVolume)
{
    UserCommonAudioDigitalAdjustVolume(UserAdjustAudioVolumeMapping(ucVolume));
}

//--------------------------------------------------
// Description  : OSD Volume Mapping to Real Value
// Input Value  : usVolume
// Output Value : usVolume
//--------------------------------------------------
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(UserInterfaceAudioGetSource() == _LINE_IN_AUDIO)
    {
        return (UserCommonDisplayPercentToRealValueAdjust(ucVolume, _LINE_IN_VOLUME_MAX, _LINE_IN_VOLUME_MIN, _LINE_IN_VOLUME_CENTER));
    }
    else
#endif // End of #if(_LINE_IN_SUPPORT == _ON)
    {
        return (UserCommonDisplayPercentToRealValueAdjust(ucVolume, _DIGITAL_VOLUME_MAX, _DIGITAL_VOLUME_MIN, _DIGITAL_VOLUME_CENTER));
    }
}
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set FREESYNC OD Measure
// Input Value  : Current DHtotal(pixel)/ Current Dclk(kHz)/ Target Measure VFreq(0.1Hz)
// Output Value : None
//--------------------------------------------------
void UserAdjustFreeSyncODMeasure(void)
{
    // Set Backlight
    UserAdjustBacklight(100);

    // Enable Backlight
    UserCommonPowerPanelAction(_BACKLIGHT_ON);

    // Disable OSD
    UserCommonOsdDisableOsd();

    // Disable D-domain Pattern Gen.
    UserCommonDDomainPatternGenEnable(_DISABLE);

    if(SysSourceGetSourceType() == _SOURCE_DP)
    {
        // According FREESYNC setting to set accurate Htotal/ Dclk
        UserCommonFreeSyncODSetDisplayFormat(((WORD)_PANEL_DH_TOTAL), ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ), ((WORD)_PANEL_DP_FREESYNC_MIN_FRAME_RATE));
    }
    else if(SysSourceGetSourceType() == _SOURCE_HDMI)
    {
        // According FREESYNC setting to set accurate Htotal/ Dclk
        UserCommonFreeSyncODSetDisplayFormat(((WORD)_PANEL_DH_TOTAL), ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ), ((WORD)_PANEL_HDMI_FREESYNC_MIN_FRAME_RATE));
    }

    while(_TRUE)
    {
        ScalerDebug();
        UserCommonFreeSyncODSetBackgroundGrayLevel();
    }
}
#endif

//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustColorEffectMode(EnumSelRegion enumSelRegion)
{
    UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, _COLOR_FUNCTION_DCC | _COLOR_FUNCTION_ICM);

#if(_ICM_FUNCTION == _ON)
    UserCommonColorICMAdjust(enumSelRegion);
#endif

#if(_DCC_FUNCTION == _ON)
    UserCommonColorDCCAdjust(enumSelRegion);
#endif

    UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, _COLOR_FUNCTION_DCC | _COLOR_FUNCTION_ICM);
}

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set Night Sniper Settings
// Input Value  : enumSelRegion
// Output Value : None
//--------------------------------------------------
void UserAdjustNightSniper(EnumSelRegion enumSelRegion)
{
    UserCommonColorNightSniperAdjust(enumSelRegion);
}
#endif

#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust Global Hue Saturation
// Input Value  : Hue and Saturation
// Output Value : None
//--------------------------------------------------
void UserAdjustGlobalHueSat(EnumSelRegion enumSelRegion)
{
#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(UserAdjustGetOSDSelectRegion(enumSelRegion)) != _PCM_OSD_NATIVE)
    {
        UserCommonColorDColorConvertAdjust(enumSelRegion, _DB_APPLY_NO_POLLING);
    }
    else
#endif
    {
        UserCommonColorSRGBAdjust(enumSelRegion);
    }
}
#endif  // Enf of #if(_GLOBAL_HUE_SATURATION == _ON)

#if(_OD_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get OD ODLUT Info
// Input Value  : Pointer to OD ODLUT info
// Output Value : None
//--------------------------------------------------
void UserAdjustODGetODLUTInfo(StructODTableInfo *pstTableInfo)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(UserCommonDrrGetType() == _DRR_FREESYNC_TYPE)
    {
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
        pstTableInfo->ucTableGroup = _OD_FREESYNC_TABLE;
        pstTableInfo->ucTableIndex = 0;
#else
        pstTableInfo->ucBank = UserAdjustODGetODLUTBank();
        pstTableInfo->pucTable = tOD_FREESYNC_TABLE[0];
#endif
    }
    else
#endif
    {
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
        pstTableInfo->ucTableGroup = _OD_COMMON_TABLE;
        pstTableInfo->ucTableIndex = 0;
#else
        pstTableInfo->ucBank = UserAdjustODGetODLUTBank();
        pstTableInfo->pucTable = tOD_TABLE[0];
#endif
    }
}

//--------------------------------------------------
// Description  : Get OD ODLUT Bank
// Input Value  : None
// Output Value : OD ODLUT bank
//--------------------------------------------------
BYTE UserAdjustODGetODLUTBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

//--------------------------------------------------
// Description  : Get OSD OD Enable Status
// Input Value  : None
// Output Value : OSD OD Enable Status
//--------------------------------------------------
bit UserAdjustGetOsdODStatus(void)
{
    return _ENABLE;
}

//--------------------------------------------------
// Description  : Get _OD_USER mode info
// Input Value  : Pointer to OD structure data
// Output Value : None
//--------------------------------------------------
void UserAdjustODGetODUserInfo(StructODUserData *pstODUserData)
{
    pstODUserData->ucDeltaGain = GET_OSD_OD_GAIN();
    UserAdjustODGetODLUTInfo(&(pstODUserData->stODTableInfo));
}

#if(_OD_BY_POSITION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OD By-Position Table Info
// Input Value  : Pointer to OD ODLUT info
// Output Value : None
//--------------------------------------------------
void UserAdjustODGetODByPosTableInfo(StructODTableInfo *pstByPosTableInfo)
{
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
    pstByPosTableInfo->ucTableIndex = 0;
#else
    pstByPosTableInfo->ucBank = UserAdjustODGetODLUTBank();
    pstByPosTableInfo->pucTable = tOD_BYPOS_TABLE[0];
#endif
}

//--------------------------------------------------
// Description  : Get OD By-Position Region Size
// Input Value  : None
// Output Value : OD ODLUT Address
//--------------------------------------------------
EnumODByPosRegionSize UserAdjustODGetODByPosRegionSize(WORD usPanelHeight)
{
    WORD usRegionSize = (usPanelHeight % 32) ? ((usPanelHeight / 32) + 1) : (usPanelHeight / 32);

    if(usRegionSize <= 16)
    {
        return _OD_BYPOS_REGION_16LINE;
    }
    else if(usRegionSize <= 32)
    {
        return _OD_BYPOS_REGION_32LINE;
    }
    else if(usRegionSize <= 64)
    {
        return _OD_BYPOS_REGION_64LINE;
    }
    else
    {
        return _OD_BYPOS_REGION_128LINE;
    }
}

//--------------------------------------------------
// Description  : Get _OD_USER_BYPOS mode info
// Input Value  : Pointer to OD structure data
// Output Value : None
//--------------------------------------------------
void UserAdjustODGetODUserByPosInfo(StructODUserByPosData *pstODUserByPosData)
{
    pstODUserByPosData->ucDeltaGain = GET_OSD_OD_GAIN();
    UserAdjustODGetODLUTInfo(&(pstODUserByPosData->stODTableInfo));

    // User should assign "correct" enable status and OD by-position table
    pstODUserByPosData->b1ODByPosEnable = _FALSE;
    pstODUserByPosData->b2RegionSize = UserAdjustODGetODByPosRegionSize(_PANEL_DV_HEIGHT);
    UserAdjustODGetODByPosTableInfo(&(pstODUserByPosData->stODByPosTableInfo));
}
#endif // End of #if(_OD_BY_POSITION_SUPPORT == _ON)
#endif // End of #if(_OD_SUPPORT == _ON)

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
#if(_PIP_TRANSPARENCY_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPipTransparency(WORD usAdjustData)
{
    if((SysModeGetDisplayMode() == _DISPLAY_MODE_2P_PIP) &&
       (SysRegionGetDisplayState(_DISPLAY_RGN_PIP_MAIN) == _DISPLAY_STATE_ACTIVE))
    {
        UserCommonColorPIPBlendingLevelAdjust(((usAdjustData * 51) >> 1), _DB_APPLY_NO_POLLING);
    }
}
#endif
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustOsdSelectRegionColorProc(void)
{
    EnumSelRegion enumSelRegion = GET_OSD_SYSTEM_SELECT_REGION();
    EnumSelRegion enumSelRegionInverse = UserCommonRegionGetInverse(enumSelRegion);
    WORD usColorFunction = (_COLOR_FUNCTION_ULTRA_VIVID |
                            _COLOR_FUNCTION_LOCAL_CONTRAST |
                            _COLOR_FUNCTION_DCC |
                            _COLOR_FUNCTION_ICM |
                            _COLOR_FUNCTION_CTS_BRI |
                            _COLOR_FUNCTION_3DGAMMA |
                            _COLOR_FUNCTION_SRGB |
                            _COLOR_FUNCTION_UNIFORMITY |
                            _COLOR_FUNCTION_GAMMA |
                            _COLOR_FUNCTION_PCM |
                            _COLOR_FUNCTION_LIGHT_ENHANCE |
                            _COLOR_FUNCTION_GLOBAL_HUE_SAT |
                            _COLOR_FUNCTION_NIGHT_SNIPER);

#if(_COLOR_DEMO_FUNCTION == _ON)
    switch(UserCommonColorGetDemoModeType())
    {
        case _DEMO_MODE_INSIDE:
        case _DEMO_MODE_OUTSIDE:
            UserCommonColorBypassHLWSelRegionColorFunction(enumSelRegionInverse);
            enumSelRegionInverse = _NON_REGION;
            break;
        case _DEMO_MODE_BOTH:
        case _DEMO_OFF:
        default:
            break;
    }
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() != _ADVANCED_HDR10_DISP_MODE_SUPPORT_OFF)
    {
        EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(SysModeGetDisplayMode() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
        }
#endif
        UserCommonColorHDRAdjust(enumDisplayRegion);
    }
#endif


    if(enumSelRegionInverse == _NON_REGION)
    {
        UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, usColorFunction);

#if(_ULTRA_VIVID_FUNCTION == _ON)
        UserCommonColorUltraVividAdjust(enumSelRegion);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
        UserCommonColorLocalContrastAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_DCC_FUNCTION == _ON)
        UserCommonColorDCCAdjust(enumSelRegion);
#endif

#if(_ICM_FUNCTION == _ON)
        UserCommonColorICMAdjust(enumSelRegion);
#endif

#if(_CONTRAST_FUNCTION == _ON)
        // Load for SelRegion adjust.
        RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
        UserCommonColorContrastAdjust(enumSelRegion);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
        UserCommonColorBrightnessAdjust(enumSelRegion);
#endif

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
        UserCommonColorHDRAdjustHDR10LightEnhance(enumSelRegion, _DB_APPLY_NONE);
#endif

#if((_RGB_3D_GAMMA_FUNCTION == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON))
        UserCommonColor3DGammaAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
        UserCommonColorDColorConvertAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_PCM_FUNCTION == _ON)
        UserCommonColorPCMAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
        UserCommonColorSRGBAdjust(enumSelRegion);
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
        UserCommonColorPanelUniformityAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_GAMMA_FUNCTION == _ON)
        UserCommonColorGammaAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        UserCommonColorNightSniperAdjust(enumSelRegion);
#endif

        UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, usColorFunction);
    }
    else
    {
        UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, usColorFunction);
        UserCommonColorMultiFunctionRegionEnableStart(enumSelRegionInverse, usColorFunction);

#if(_ULTRA_VIVID_FUNCTION == _ON)
        UserCommonColorUltraVividAdjust(enumSelRegion);
        UserCommonColorUltraVividAdjust(enumSelRegionInverse);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
        UserCommonColorLocalContrastAdjust(enumSelRegion, _DB_APPLY_NONE);
        UserCommonColorLocalContrastAdjust(enumSelRegionInverse, _DB_APPLY_NONE);
#endif

#if(_DCC_FUNCTION == _ON)
        UserCommonColorDCCAdjust(enumSelRegion);
        UserCommonColorDCCAdjust(enumSelRegionInverse);
#endif

#if(_ICM_FUNCTION == _ON)
        UserCommonColorICMAdjust(enumSelRegion);
        UserCommonColorICMAdjust(enumSelRegionInverse);
#endif

#if(_CONTRAST_FUNCTION == _ON)
        // Load for SelRegion adjust.
        RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
        UserCommonColorContrastAdjust(enumSelRegion);

        // Load for Inverse SeleRegion adjust.
        RTDNVRamLoadColorSetting(GET_OSD_INVERSE_REGION());
        UserCommonColorContrastAdjust(enumSelRegionInverse);

        // Reload data for current select region.
        RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
        UserCommonColorBrightnessAdjust(enumSelRegion);
        UserCommonColorBrightnessAdjust(enumSelRegionInverse);
#endif

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
        UserCommonColorHDRAdjustHDR10LightEnhance(enumSelRegion, _DB_APPLY_NONE);
        UserCommonColorHDRAdjustHDR10LightEnhance(enumSelRegionInverse, _DB_APPLY_NONE);
#endif

#if((_RGB_3D_GAMMA_FUNCTION == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON))
        UserCommonColor3DGammaAdjust(enumSelRegion, _DB_APPLY_NONE);
        UserCommonColor3DGammaAdjust(enumSelRegionInverse, _DB_APPLY_NONE);
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
        UserCommonColorDColorConvertAdjust(enumSelRegion, _DB_APPLY_NONE);
        UserCommonColorDColorConvertAdjust(enumSelRegionInverse, _DB_APPLY_NONE);
#endif

#if(_PCM_FUNCTION == _ON)
        UserCommonColorPCMAdjust(enumSelRegion, _DB_APPLY_NONE);
        UserCommonColorPCMAdjust(enumSelRegionInverse, _DB_APPLY_NONE);
#else

#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
        UserCommonColorSRGBAdjust(enumSelRegion);
        UserCommonColorSRGBAdjust(enumSelRegionInverse);
#endif

#if(_GAMMA_FUNCTION == _ON)
        UserCommonColorGammaAdjust(enumSelRegion, _DB_APPLY_NONE);
        UserCommonColorGammaAdjust(enumSelRegionInverse, _DB_APPLY_NONE);
#endif
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
        UserCommonColorPanelUniformityAdjust(enumSelRegion, _DB_APPLY_NONE);
        UserCommonColorPanelUniformityAdjust(enumSelRegionInverse, _DB_APPLY_NONE);
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        UserCommonColorNightSniperAdjust(enumSelRegion);
        UserCommonColorNightSniperAdjust(enumSelRegionInverse);
#endif

        UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, usColorFunction);
        UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegionInverse, usColorFunction);
    }

#if(_COLOR_DEMO_FUNCTION == _ON)
    UserAdjustHLWinType();
#else
#if(_COLOR_IP_HL_WIN == _ON)
    UserCommonColorHLWinTypeAdjust(_DB_APPLY_NO_POLLING);
#endif
#endif
}

//--------------------------------------------------
// Description  : User adjust display mode function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustDisplayMode(void)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(GET_OSD_LOCAL_DIMMING() == _ON)
    {
        SET_OSD_LOCAL_DIMMING(_OFF);
    }
#endif

    // Load user data
    RTDNVRamSaveOsdUserData();
    RTDNVRamLoadOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
    RTDNVRamLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());

    // Adjust display mode
    UserCommonDisplayModeAdjust(UserAdjustGetMultiDisplayMode());
}

//--------------------------------------------------
// Description  : User adjust display region function
// Input Value  : enumSelRegion --> target select region
//                enumInputPort --> target input port
// Output Value : None
//--------------------------------------------------
void UserAdjustRegionInputPort(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort)
{
    // Save user display mode data
    RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());

    // Adjust display region
    UserCommonDisplayRegionInputPortAdjust(enumDisplayRegion, enumInputPort);

    // Update LED status
    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) == 0X00)
    {
        RTDKeyPadLedControl(_LED_POWER_SEARCH);
    }
}

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Rx Pxp Mode Support Switch
// Input Value  : Check Status
// Output Value : None
//--------------------------------------------------
void UserAdjustDpMstRxPxpMode(EnumDpMstPxpMode enumDpMstPxpMode)
{
    BYTE uc1PSource = 0;
    BYTE uc2PSource = 0;

    UserCommonDpMstRxPxpModeSwitch(enumDpMstPxpMode);

    if(enumDpMstPxpMode == _DP_MST_PXP_OFF)
    {
        SET_FORCE_POW_SAV_STATUS(_FALSE);

        DebugMessageOsd("Pxp mode switch off case", enumDpMstPxpMode);

        uc1PSource = GET_OSD_1P_INPUT_SOURCE_BACK_UP();
        uc2PSource = GET_OSD_2P_INPUT_SOURCE_BACK_UP();

        SET_OSD_1P_INPUT_SOURCE(uc1PSource);
        SET_OSD_2P_INPUT_SOURCE(uc2PSource);

        switch(GET_OSD_DISPLAY_MODE())
        {
            case _OSD_DM_2P_LR:

                if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    // Set 1P Auto search target region
                    SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());

                    // Set 2P Region Input Port
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT, uc2PSource);
                }
                else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    // Set 2P Auto search target region
                    SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());

                    // Set 1P Region Input Port
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT, uc1PSource);
                }
                else
                {
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT, uc1PSource);
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT, uc2PSource);
                }

                break;

            case _OSD_DM_2P_TB:

                if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    // Set 1P Auto search target region
                    SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());

                    // Set 2P Region Input Port
                    UserAdjustRegionInputPort(_DISPLAY_RGN_BOTTOM, uc2PSource);
                }
                else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    // Set 2P Auto search target region
                    SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());

                    // Set 1P Region Input Port
                    UserAdjustRegionInputPort(_DISPLAY_RGN_TOP, uc1PSource);
                }
                else
                {
                    UserAdjustRegionInputPort(_DISPLAY_RGN_TOP, uc1PSource);
                    UserAdjustRegionInputPort(_DISPLAY_RGN_BOTTOM, uc2PSource);
                }

                break;

            case _OSD_DM_2P_PIP:

                if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    // Set 1P Auto search target region
                    SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());

                    // Set 2P Region Input Port
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_SUB, uc2PSource);
                }
                else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    // Set 2P Auto search target region
                    SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());

                    // Set 1P Region Input Port
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_MAIN, uc1PSource);
                }
                else
                {
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_MAIN, uc1PSource);
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_SUB, uc2PSource);
                }

                break;

            default:
                break;
        }

        DebugMessageOsd("Pxp mode switch 1P Source", uc1PSource);
        DebugMessageOsd("Pxp mode switch 2P Source", uc2PSource);
    }
    else
    {
        SET_FORCE_POW_SAV_STATUS(_FALSE);

        uc1PSource = GET_OSD_1P_INPUT_SOURCE();
        uc2PSource = GET_OSD_2P_INPUT_SOURCE();

#if(_DP_MST_PXP_FIXED_MODE_SUPPORT == _ON)
        if(enumDpMstPxpMode == _DP_MST_PXP_ON_FIXED_MODE)
        {
#if(_DP_MST_PXP_SELECT_MODE_SUPPORT == _ON)
            if((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_D9_D0) || (GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_D9_D1) || (GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_D9_D2))
            {
                SET_OSD_1P_INPUT_SOURCE(GET_OSD_1P_INPUT_SOURCE() - _OSD_INPUT_D9);

                switch(GET_OSD_DISPLAY_MODE())
                {
                    case _OSD_DM_2P_LR:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT, GET_OSD_1P_INPUT_SOURCE());

                        break;
                    case _OSD_DM_2P_TB:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_TOP, GET_OSD_1P_INPUT_SOURCE());
                        break;
                    case _OSD_DM_2P_PIP:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_MAIN, GET_OSD_1P_INPUT_SOURCE());
                        break;

                    default:
                        break;
                }
            }
#endif

            // PxP Fixed Mode 2P Source --> D9 PxP
            SET_OSD_2P_INPUT_SOURCE(_D9_INPUT_PORT);

            switch(GET_OSD_DISPLAY_MODE())
            {
                case _OSD_DM_2P_LR:
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT, GET_OSD_2P_INPUT_SOURCE());

                    break;
                case _OSD_DM_2P_TB:
                    UserAdjustRegionInputPort(_DISPLAY_RGN_BOTTOM, GET_OSD_2P_INPUT_SOURCE());
                    break;
                case _OSD_DM_2P_PIP:
                    UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_SUB, GET_OSD_2P_INPUT_SOURCE());
                    break;

                default:
                    break;
            }
        }
#endif

#if(_DP_MST_PXP_SELECT_MODE_SUPPORT == _ON)
        if(enumDpMstPxpMode == _DP_MST_PXP_ON_SELECT_MODE)
        {
            DebugMessageOsd("Pxp mode switch on Select case", 1);

#if(_DP_MST_PXP_FIXED_MODE_SUPPORT == _ON)
            if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_D9)
            {
                SET_OSD_2P_INPUT_SOURCE(GET_OSD_2P_INPUT_SOURCE_BACK_UP());

                switch(GET_OSD_DISPLAY_MODE())
                {
                    case _OSD_DM_2P_LR:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT, GET_OSD_2P_INPUT_SOURCE());

                        break;
                    case _OSD_DM_2P_TB:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_BOTTOM, GET_OSD_2P_INPUT_SOURCE());
                        break;
                    case _OSD_DM_2P_PIP:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_SUB, GET_OSD_2P_INPUT_SOURCE());
                        break;

                    default:
                        break;
                }
            }
#endif

            if((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_D9_D0) || (GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_D9_D1) || (GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_D9_D2))
            {
                switch(GET_OSD_DISPLAY_MODE())
                {
                    case _OSD_DM_2P_LR:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT, _D9_INPUT_PORT);
                        break;

                    case _OSD_DM_2P_TB:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_TOP, _D9_INPUT_PORT);
                        break;

                    case _OSD_DM_2P_PIP:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_MAIN, _D9_INPUT_PORT);
                        break;

                    default:
                        break;
                }
            }
            else if((GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_D9_D0) || (GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_D9_D1) || (GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_D9_D2))
            {
                switch(GET_OSD_DISPLAY_MODE())
                {
                    case _OSD_DM_2P_LR:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT, _D9_INPUT_PORT);
                        break;

                    case _OSD_DM_2P_TB:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_BOTTOM, _D9_INPUT_PORT);
                        break;

                    case _OSD_DM_2P_PIP:
                        UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_SUB, _D9_INPUT_PORT);
                        break;

                    default:
                        break;
                }
            }
        }
#endif
        DebugMessageOsd("Pxp mode switch 1P Source", GET_OSD_1P_INPUT_SOURCE());
        DebugMessageOsd("Pxp mode switch 2P Source", GET_OSD_2P_INPUT_SOURCE());
    }

    RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE UserAdjustGetInputPortValue(EnumRegionIndex enumRegionIdx)
{
    WORD usAdjustValue = 0;
    BYTE ucIndex = 0;

    ucIndex = ucIndex;

#if(_DP_MST_PXP_SELECT_MODE_SUPPORT == _ON)
    // Only one region can be D9 Port
    if((g_usAdjustValue >= _OSD_INPUT_D9_D0) && (g_usAdjustValue <= _OSD_INPUT_D9_D2))
    {
        usAdjustValue = _D9_INPUT_PORT;

        for(ucIndex = 0; ucIndex < _MULTI_DISPLAY_MAX; ++ucIndex)
        {
            if(ucIndex != enumRegionIdx)
            {
                if((GET_OSD_INPUT_SOURCE(ucIndex) >= _OSD_INPUT_D9_D0) && (GET_OSD_INPUT_SOURCE(ucIndex) <= _OSD_INPUT_D9_D2))
                {
                    SET_OSD_INPUT_SOURCE(ucIndex, _OSD_INPUT_D0 + (g_usAdjustValue - _OSD_INPUT_D9_D0));
                    UserAdjustRegionInputPort(SysRegionGetDisplayRegion(ucIndex), GET_OSD_INPUT_SOURCE(ucIndex));
                }
                else if(GET_OSD_INPUT_SOURCE(ucIndex) == _OSD_INPUT_AUTO)
                {
                    if(SysRegionGetInputPort(SysRegionGetDisplayRegion(ucIndex)) == _D9_INPUT_PORT)
                    {
                        UserAdjustRegionInputPort(SysRegionGetDisplayRegion(ucIndex), (_OSD_INPUT_D0 + (g_usAdjustValue - _OSD_INPUT_D9_D0)));
                    }
                }
            }
        }
    }
    else
#endif
    {
        usAdjustValue = g_usAdjustValue;
    }

    SysDpRxPxpInputPortSwitch(UserInterfaceDpGetPxpInputTarget());

    return usAdjustValue;
}
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Swap input port in 2P mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustSwapInputPort(void)
{
    EnumDisplayRegion enumAutoSearchTargetRegion = UserCommonSourceGetAutoSearchTarget();
    EnumDisplayRegion enumRegion0 = 0x00;
    EnumDisplayRegion enumRegion1 = 0x00;
    EnumInputPort enumPort0 = 0x00;
    EnumInputPort enumPort1 = 0x00;

    switch(SysModeGetDisplayMode())
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            enumRegion0 = _DISPLAY_RGN_PIP_MAIN;
            enumRegion1 = _DISPLAY_RGN_PIP_SUB;
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            enumRegion0 = _DISPLAY_RGN_PBP_LR_EQUAL_LEFT;
            enumRegion1 = _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT;
            break;

        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            enumRegion0 = _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT;
            enumRegion1 = _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT;
            break;

        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            enumRegion0 = _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT;
            enumRegion1 = _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT;
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            enumRegion0 = _DISPLAY_RGN_TOP;
            enumRegion1 = _DISPLAY_RGN_BOTTOM;
            break;
#endif

        default:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            return;
    }

    // Enable background
    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    UserCommonDDomainBackgroundEnableByRegion(enumRegion0, _ENABLE);
    UserCommonDDomainBackgroundEnableByRegion(enumRegion1, _ENABLE);

    // Reset data path for I/M/D domains
    SysModeResetDisplayState(enumRegion0);
    SysModeResetDisplayState(enumRegion1);
    UserCommonIDomainResetDataPath(UserCommonRegionGetInputDataPath(enumRegion0));
    UserCommonIDomainResetDataPath(UserCommonRegionGetInputDataPath(enumRegion1));

    // Set region input port
    enumPort0 = SysRegionGetInputPort(enumRegion0);
    enumPort1 = SysRegionGetInputPort(enumRegion1);

    // Swap region input ports in global variables
    SysRegionUpdateInterface(enumRegion0, _NO_INPUT_PORT);
    SysRegionUpdateInterface(enumRegion1, _NO_INPUT_PORT);
    SysRegionUpdateInterface(enumRegion0, enumPort1);
    SysRegionUpdateInterface(enumRegion1, enumPort0);

    // Swap region input ports in NVRAM
    UserCommonNVRamSetSystemRegionPortData(enumRegion0, enumPort1);
    UserCommonNVRamSetSystemRegionPortData(enumRegion1, enumPort0);

    // Update auto search target
    SysSourceSetMultiAutoSearchTarget(enumAutoSearchTargetRegion);

    if(enumAutoSearchTargetRegion != _DISPLAY_RGN_NONE)
    {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
        // If InputPort is D4, need to check it is D4, D14 or D15?
        if((SysRegionGetInputPort(enumAutoSearchTargetRegion) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)) // ACTIVE PORT = D14
        {
            // Switch to D14
            SysSourceSwitchInputPort(_D14_INPUT_PORT);
        }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        else if((SysRegionGetInputPort(enumAutoSearchTargetRegion) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)) // ACTIVE PORT = D15
        {
            // Switch to D15
            SysSourceSwitchInputPort(_D15_INPUT_PORT);
        }
#endif

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

        // If InputPort is D3, need to check it is D3, D12 or D13?
        if((SysRegionGetInputPort(enumAutoSearchTargetRegion) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)) // ACTIVE PORT = D12
        {
            // Switch to D12
            SysSourceSwitchInputPort(_D12_INPUT_PORT);
        }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        else if((SysRegionGetInputPort(enumAutoSearchTargetRegion) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)) // ACTIVE PORT = D13
        {
            // Switch to D13
            SysSourceSwitchInputPort(_D13_INPUT_PORT);
        }
#endif
#endif
        else
#endif
        {
            // Switch to auto target region
            SysSourceSwitchInputPort(SysRegionGetInputPort(enumAutoSearchTargetRegion));
        }
    }
    else
    {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
        // If InputPort is D4, need to check it is D4, D14 or D15?
        if((SysRegionGetInputPort(enumRegion0) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)) // ACTIVE PORT = D14
        {
            // Switch to D14
            SysSourceSwitchInputPort(_D14_INPUT_PORT);
        }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        else if((SysRegionGetInputPort(enumRegion0) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)) // ACTIVE PORT = D15
        {
            // Switch to D15
            SysSourceSwitchInputPort(_D15_INPUT_PORT);
        }
#endif

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

        // If InputPort is D3, need to check it is D3, D12 or D13?
        if((SysRegionGetInputPort(enumRegion0) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)) // ACTIVE PORT = D12
        {
            // Switch to D12
            SysSourceSwitchInputPort(_D12_INPUT_PORT);
        }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        else if((SysRegionGetInputPort(enumRegion0) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)) // ACTIVE PORT = D13
        {
            // Switch to D13
            SysSourceSwitchInputPort(_D13_INPUT_PORT);
        }
#endif
#endif
        else
#endif
        {
            // Switch to region 0
            SysSourceSwitchInputPort(SysRegionGetInputPort(enumRegion0));
        }
    }

    // Save system data
    UserCommonNVRamSaveSystemData();
}
#endif // End of #if(_2P_DISPLAY_SUPPORT == _ON)

#if(_COLOR_DEMO_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Osd Select Region Check Demo
// Input Value  : None
// Output Value : Select Region
//--------------------------------------------------
BYTE UserAdjustCheckOsdSelectRegion(void)
{
    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
        if(GET_OSD_HLWIN_SIDE() == _OSD_HLW_INSIDE)
        {
            return _OSD_HLW_INSIDE;
        }
        else
        {
            return _OSD_HLW_OUTSIDE;
        }
    }
    return (g_stOsdDisplayModeData.ucSelectRegion);
}

//--------------------------------------------------
// Description  : Osd Inverse Select Region Check Demo
// Input Value  : None
// Output Value : Select Region
//--------------------------------------------------
BYTE UserAdjustCheckOsdInverseSelectRegion(void)
{
    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
        if(GET_OSD_HLWIN_SIDE() == _OSD_HLW_INSIDE)
        {
            return _OSD_HLW_OUTSIDE;
        }
        else
        {
            return _OSD_HLW_INSIDE;
        }
    }
    return ((g_stOsdDisplayModeData.ucSelectRegion & 0xFE) | (~g_stOsdDisplayModeData.ucSelectRegion & 0x01));
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumSelRegion UserAdjustConvertSystemSelectRegion(BYTE ucRegion)
{
    ucRegion = ucRegion;

    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
        if(GET_OSD_HLWIN_SIDE() == _OSD_HLW_INSIDE)
        {
            return _DEMO_INSIDE;
        }
        else
        {
            return _DEMO_OUTSIDE;
        }
    }

    switch(GET_OSD_DISPLAY_MODE())
    {
        case _OSD_DM_1P:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(GET_EAGLE_SIGHT_STATUS() == _ON)
            {
                if(ucRegion == _OSD_SR_2P_PIP_EAGLE_SIGHT_MAIN)
                {
                    return _2P_PIP_EAGLE_SIGHT_MAIN;
                }
                else if(ucRegion == _OSD_SR_2P_PIP_EAGLE_SIGHT_SUB)
                {
                    return _2P_PIP_EAGLE_SIGHT_SUB;
                }
                else
                {
                    return _FULL_REGION;
                }
            }
            else
#endif
            {
                return _1P_NORMAL_REGION;
            }

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:
            if(ucRegion == _OSD_SR_2P_LR_L)
            {
                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _2P_PBP_LR_L_LARGE_L;
                }
                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _2P_PBP_LR_R_LARGE_L;
                }
                else
                {
                    return _2P_PBP_LR_EQUAL_L;
                }
            }
            else if(ucRegion == _OSD_SR_2P_LR_R)
            {
                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _2P_PBP_LR_L_LARGE_R;
                }
                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _2P_PBP_LR_R_LARGE_R;
                }
                else
                {
                    return _2P_PBP_LR_EQUAL_R;
                }
            }
            else
            {
                return _FULL_REGION;
            }
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:
            if(ucRegion == _OSD_SR_2P_PIP_MAIN)
            {
                return _2P_PIP_MAIN;
            }
            else if(ucRegion == _OSD_SR_2P_PIP_SUB)
            {
                return _2P_PIP_SUB;
            }
            else
            {
                return _FULL_REGION;
            }
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:
            if(ucRegion == _OSD_SR_2P_TB_T)
            {
                return _2P_PBP_TB_T;
            }
            else if(ucRegion == _OSD_SR_2P_TB_B)
            {
                return _2P_PBP_TB_B;
            }
            else
            {
                return _FULL_REGION;
            }
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_FLAG:
            switch(ucRegion)
            {
                case _OSD_SR_3P_FLAG_MAIN:
                    return _3P_FLAG_M;
                case _OSD_SR_3P_FLAG_L:
                    return _3P_FLAG_L;
                case _OSD_SR_3P_FLAG_R:
                    return _3P_FLAG_R;
                case _OSD_SR_3P_FLAG_MAIN_OUT:
                    return _3P_FLAG_M_OUTSIDE;
                case _OSD_SR_3P_FLAG_L_OUT:
                    return _3P_FLAG_L_OUTSIDE;
                case _OSD_SR_3P_FLAG_R_OUT:
                    return _3P_FLAG_R_OUTSIDE;
                case _OSD_SR_3P_FLAG_FULL:
                default:
                    return _FULL_REGION;
            }
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_L:
            switch(ucRegion)
            {
                case _OSD_SR_3P_SKEW_L_MAIN:
                    return _3P_SKEW_L_M;
                case _OSD_SR_3P_SKEW_L_UP:
                    return _3P_SKEW_L_T;
                case _OSD_SR_3P_SKEW_L_DOWN:
                    return _3P_SKEW_L_B;
                case _OSD_SR_3P_SKEW_L_MAIN_OUT:
                    return _3P_SKEW_L_M_OUTSIDE;
                case _OSD_SR_3P_SKEW_L_UP_OUT:
                    return _3P_SKEW_L_T_OUTSIDE;
                case _OSD_SR_3P_SKEW_L_DOWN_OUT:
                    return _3P_SKEW_L_B_OUTSIDE;
                case _OSD_SR_3P_SKEW_L_FULL:
                default:
                    return _FULL_REGION;
            }

        case _OSD_DM_3P_SKEW_R:
            switch(ucRegion)
            {
                case _OSD_SR_3P_SKEW_R_MAIN:
                    return _3P_SKEW_R_M;
                case _OSD_SR_3P_SKEW_R_UP:
                    return _3P_SKEW_R_T;
                case _OSD_SR_3P_SKEW_R_DOWN:
                    return _3P_SKEW_R_B;
                case _OSD_SR_3P_SKEW_R_MAIN_OUT:
                    return _3P_SKEW_R_M_OUTSIDE;
                case _OSD_SR_3P_SKEW_R_UP_OUT:
                    return _3P_SKEW_R_T_OUTSIDE;
                case _OSD_SR_3P_SKEW_R_DOWN_OUT:
                    return _3P_SKEW_R_B_OUTSIDE;

                case _OSD_SR_3P_SKEW_R_FULL:
                default:
                    return _FULL_REGION;
            }
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_T:
            switch(ucRegion)
            {
                case _OSD_SR_3P_SKEW_T_MAIN:
                    return _3P_SKEW_T_M;
                case _OSD_SR_3P_SKEW_T_LEFT:
                    return _3P_SKEW_T_L;
                case _OSD_SR_3P_SKEW_T_RIGHT:
                    return _3P_SKEW_T_R;
                case _OSD_SR_3P_SKEW_T_MAIN_OUT:
                    return _3P_SKEW_T_M_OUTSIDE;
                case _OSD_SR_3P_SKEW_T_LEFT_OUT:
                    return _3P_SKEW_T_L_OUTSIDE;
                case _OSD_SR_3P_SKEW_T_RIGHT_OUT:
                    return _3P_SKEW_T_R_OUTSIDE;
                case _OSD_SR_3P_SKEW_T_FULL:
                default:
                    return _FULL_REGION;
            }

        case _OSD_DM_3P_SKEW_B:
            switch(ucRegion)
            {
                case _OSD_SR_3P_SKEW_B_MAIN:
                    return _3P_SKEW_B_M;
                case _OSD_SR_3P_SKEW_B_LEFT:
                    return _3P_SKEW_B_L;
                case _OSD_SR_3P_SKEW_B_RIGHT:
                    return _3P_SKEW_B_R;
                case _OSD_SR_3P_SKEW_B_MAIN_OUT:
                    return _3P_SKEW_B_M_OUTSIDE;
                case _OSD_SR_3P_SKEW_B_LEFT_OUT:
                    return _3P_SKEW_B_L_OUTSIDE;
                case _OSD_SR_3P_SKEW_B_RIGHT_OUT:
                    return _3P_SKEW_B_R_OUTSIDE;
                case _OSD_SR_3P_SKEW_B_FULL:
                default:
                    return _FULL_REGION;
            }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:
            switch(ucRegion)
            {
                case _OSD_SR_4P_LT_INSIDE:
                    return _4P_LT;
                case _OSD_SR_4P_LT_OUTSIDE:
                    return _4P_LT_OUTSIDE;
                case _OSD_SR_4P_RT_INSIDE:
                    return _4P_RT;
                case _OSD_SR_4P_RT_OUTSIDE:
                    return _4P_RT_OUTSIDE;
                case _OSD_SR_4P_LB_INSIDE:
                    return _4P_LB;
                case _OSD_SR_4P_LB_OUTSIDE:
                    return _4P_LB_OUTSIDE;
                case _OSD_SR_4P_RB_INSIDE:
                    return _4P_RB;
                case _OSD_SR_4P_RB_OUTSIDE:
                    return _4P_RB_OUTSIDE;
                case _OSD_SR_4P_FULL:
                default:
                    return _FULL_REGION;
            }
#endif

        default:
            break;
    }

    return _NON_REGION;
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDisplayRegion UserAdjustConvertDisplayRegion(BYTE ucRegion)
{
    ucRegion = ucRegion;

    switch(GET_OSD_DISPLAY_MODE())
    {
        case _OSD_DM_1P:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(GET_EAGLE_SIGHT_STATUS() == _ON)
            {
                if(ucRegion == _OSD_SR_2P_PIP_EAGLE_SIGHT_MAIN)
                {
                    return _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
                }
                else if(ucRegion == _OSD_SR_2P_PIP_EAGLE_SIGHT_SUB)
                {
                    return _DISPLAY_RGN_EAGLE_SIGHT_SUB;
                }
                return _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
            }
            else
#endif
            {
                return _DISPLAY_RGN_1P;
            }
            break;

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:
            if(ucRegion == _OSD_SR_2P_LR_L)
            {
                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT;
                }
                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT;
                }
                else
                {
                    return _DISPLAY_RGN_PBP_LR_EQUAL_LEFT;
                }
            }
            else if(ucRegion == _OSD_SR_2P_LR_R)
            {
                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT;
                }
                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT;
                }
                else
                {
                    return _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT;
                }
            }
            else
            {
                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT;
                }
                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                {
                    return _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT;
                }
                else
                {
                    return _DISPLAY_RGN_PBP_LR_EQUAL_LEFT;
                }
            }
            break;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:
            if(ucRegion == _OSD_SR_2P_PIP_MAIN)
            {
                return _DISPLAY_RGN_PIP_MAIN;
            }
            else if(ucRegion == _OSD_SR_2P_PIP_SUB)
            {
                return _DISPLAY_RGN_PIP_SUB;
            }
            return _DISPLAY_RGN_PIP_MAIN;
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:
            if(ucRegion == _OSD_SR_2P_TB_T)
            {
                return _DISPLAY_RGN_TOP;
            }
            else if(ucRegion == _OSD_SR_2P_TB_B)
            {
                return _DISPLAY_RGN_BOTTOM;
            }
            return _DISPLAY_RGN_TOP;
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_FLAG:
            switch(ucRegion)
            {
                case _OSD_SR_3P_FLAG_MAIN:
                default:
                    return _DISPLAY_RGN_FLAG_MAIN;
                case _OSD_SR_3P_FLAG_L:
                    return _DISPLAY_RGN_FLAG_LEFT;
                case _OSD_SR_3P_FLAG_R:
                    return _DISPLAY_RGN_FLAG_RIGHT;
            }
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_L:
            switch(ucRegion)
            {
                case _OSD_SR_3P_SKEW_L_MAIN:
                default:
                    return _DISPLAY_RGN_SKEW_L_MAIN;
                case _OSD_SR_3P_SKEW_L_UP:
                    return _DISPLAY_RGN_SKEW_L_TOP;
                case _OSD_SR_3P_SKEW_L_DOWN:
                    return _DISPLAY_RGN_SKEW_L_BOTTOM;
            }
            break;

        case _OSD_DM_3P_SKEW_R:
            switch(ucRegion)
            {
                case _OSD_SR_3P_SKEW_R_MAIN:
                default:
                    return _DISPLAY_RGN_SKEW_R_MAIN;
                case _OSD_SR_3P_SKEW_R_UP:
                    return _DISPLAY_RGN_SKEW_R_TOP;
                case _OSD_SR_3P_SKEW_R_DOWN:
                    return _DISPLAY_RGN_SKEW_R_BOTTOM;
            }
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_T:
            switch(ucRegion)
            {
                case _OSD_SR_3P_SKEW_T_MAIN:
                default:
                    return _DISPLAY_RGN_SKEW_T_MAIN;
                case _OSD_SR_3P_SKEW_T_LEFT:
                    return _DISPLAY_RGN_SKEW_T_LEFT;
                case _OSD_SR_3P_SKEW_T_RIGHT:
                    return _DISPLAY_RGN_SKEW_T_RIGHT;
            }
            break;

        case _OSD_DM_3P_SKEW_B:
            switch(ucRegion)
            {
                case _OSD_SR_3P_SKEW_B_MAIN:
                default:
                    return _DISPLAY_RGN_SKEW_B_MAIN;
                case _OSD_SR_3P_SKEW_B_LEFT:
                    return _DISPLAY_RGN_SKEW_B_LEFT;
                case _OSD_SR_3P_SKEW_B_RIGHT:
                    return _DISPLAY_RGN_SKEW_B_RIGHT;
            }
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:
            switch(ucRegion)
            {
                case _OSD_SR_4P_LT_INSIDE:
                default:
                    return _DISPLAY_RGN_LT;
                case _OSD_SR_4P_RT_INSIDE:
                    return _DISPLAY_RGN_RT;
                case _OSD_SR_4P_LB_INSIDE:
                    return _DISPLAY_RGN_LB;
                case _OSD_SR_4P_RB_INSIDE:
                    return _DISPLAY_RGN_RB;
                    break;
            }
            break;
#endif

        default:
            break;
    }

    return _DISPLAY_RGN_NONE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumInputPort UserAdjustGetSelectRegionPort(void)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
        case _OSD_DM_1P:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(GET_EAGLE_SIGHT_STATUS() == _ON)
            {
                switch(GET_OSD_SELECT_REGION())
                {
                    default:
                    case _OSD_SR_2P_PIP_EAGLE_SIGHT_MAIN:
                        return SysRegionGetInputPort(_DISPLAY_RGN_EAGLE_SIGHT_MAIN);
                    case _OSD_SR_2P_PIP_EAGLE_SIGHT_SUB:
                        return SysRegionGetInputPort(_DISPLAY_RGN_EAGLE_SIGHT_SUB);
                }
            }
            else
#endif
            {
                return SysRegionGetInputPort(_DISPLAY_RGN_1P);
            }

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_2P_LR_L:
                    if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                    {
                        return SysRegionGetInputPort(_DISPLAY_RGN_PBP_LR_L_LARGE_LEFT);
                    }
                    else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                    {
                        return SysRegionGetInputPort(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT);
                    }
                    else
                    {
                        return SysRegionGetInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT);
                    }
                case _OSD_SR_2P_LR_R:
                    if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                    {
                        return SysRegionGetInputPort(_DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT);
                    }
                    else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                    {
                        return SysRegionGetInputPort(_DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT);
                    }
                    else
                    {
                        return SysRegionGetInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT);
                    }
            }
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_2P_TB_T:
                    return SysRegionGetInputPort(_DISPLAY_RGN_TOP);
                case _OSD_SR_2P_TB_B:
                    return SysRegionGetInputPort(_DISPLAY_RGN_BOTTOM);
            }
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_2P_PIP_MAIN:
                    return SysRegionGetInputPort(_DISPLAY_RGN_PIP_MAIN);
                case _OSD_SR_2P_PIP_SUB:
                    return SysRegionGetInputPort(_DISPLAY_RGN_PIP_SUB);
            }
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_FLAG:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_3P_FLAG_MAIN:
                    return SysRegionGetInputPort(_DISPLAY_RGN_FLAG_MAIN);
                case _OSD_SR_3P_FLAG_L:
                    return SysRegionGetInputPort(_DISPLAY_RGN_FLAG_LEFT);
                case _OSD_SR_3P_FLAG_R:
                    return SysRegionGetInputPort(_DISPLAY_RGN_FLAG_RIGHT);
            }
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_L:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_3P_SKEW_L_MAIN:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_L_MAIN);
                case _OSD_SR_3P_SKEW_L_UP:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_L_TOP);
                case _OSD_SR_3P_SKEW_L_DOWN:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_L_BOTTOM);
            }
        case _OSD_DM_3P_SKEW_R:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_3P_SKEW_R_MAIN:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_R_MAIN);
                case _OSD_SR_3P_SKEW_R_UP:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_R_TOP);
                case _OSD_SR_3P_SKEW_R_DOWN:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_R_BOTTOM);
            }
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_T:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_3P_SKEW_T_MAIN:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_T_MAIN);
                case _OSD_SR_3P_SKEW_T_LEFT:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_T_LEFT);
                case _OSD_SR_3P_SKEW_T_RIGHT:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_T_RIGHT);
            }
        case _OSD_DM_3P_SKEW_B:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_3P_SKEW_B_MAIN:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_B_MAIN);
                case _OSD_SR_3P_SKEW_B_LEFT:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_B_LEFT);
                case _OSD_SR_3P_SKEW_B_RIGHT:
                    return SysRegionGetInputPort(_DISPLAY_RGN_SKEW_B_RIGHT);
            }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_4P_LT_INSIDE:
                    return SysRegionGetInputPort(_DISPLAY_RGN_LT);
                case _OSD_SR_4P_LB_INSIDE:
                    return SysRegionGetInputPort(_DISPLAY_RGN_LB);
                case _OSD_SR_4P_RT_INSIDE:
                    return SysRegionGetInputPort(_DISPLAY_RGN_RT);
                case _OSD_SR_4P_RB_INSIDE:
                    return SysRegionGetInputPort(_DISPLAY_RGN_RB);
            }
#endif
    }
}

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
//--------------------------------------------------
// Description  : Get OSD Select Region
// Input Value  : EnumSelRegion
// Output Value : BYTE OSDSelRegion
//--------------------------------------------------
BYTE UserAdjustGetOSDSelectRegion(EnumSelRegion enumSelRegion)
{
#if((_3P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
    EnumSelRegion enumSelRegionInverse = UserCommonRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION());
#endif

    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
        case _OSD_DM_1P:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                return GET_OSD_INVERSE_REGION();
            }

#if(_2P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:
        case _OSD_DM_2P_LR:
        case _OSD_DM_2P_PIP:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                        return GET_OSD_INVERSE_REGION();
                }
            }
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_FLAG:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _3P_FLAG_M_OUTSIDE:
                    case _3P_FLAG_L_OUTSIDE:
                    case _3P_FLAG_R_OUTSIDE:

                        if(enumSelRegionInverse == enumSelRegion)
                        {
                            return GET_OSD_INVERSE_REGION();
                        }
                        else
                        {
                            return GET_OSD_SELECT_REGION();
                        }

                    case _FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                    case _3P_FLAG_M:
                    case _3P_FLAG_L:
                    case _3P_FLAG_R:
                    case _DEMO_INSIDE:
                    case _DEMO_OUTSIDE:
                        return GET_OSD_INVERSE_REGION();
                }
            }
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_L:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _3P_SKEW_L_M_OUTSIDE:
                    case _3P_SKEW_L_T_OUTSIDE:
                    case _3P_SKEW_L_B_OUTSIDE:

                        if(enumSelRegionInverse == enumSelRegion)
                        {
                            return GET_OSD_INVERSE_REGION();
                        }
                        else
                        {
                            return GET_OSD_SELECT_REGION();
                        }

                    case _FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                    case _3P_SKEW_L_M:
                    case _3P_SKEW_L_T:
                    case _3P_SKEW_L_B:
                    case _DEMO_INSIDE:
                    case _DEMO_OUTSIDE:
                        return GET_OSD_INVERSE_REGION();
                }
            }

        case _OSD_DM_3P_SKEW_R:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _3P_SKEW_R_M_OUTSIDE:
                    case _3P_SKEW_R_T_OUTSIDE:
                    case _3P_SKEW_R_B_OUTSIDE:

                        if(enumSelRegionInverse == enumSelRegion)
                        {
                            return GET_OSD_INVERSE_REGION();
                        }
                        else
                        {
                            return GET_OSD_SELECT_REGION();
                        }

                    case _FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                    case _3P_SKEW_R_M:
                    case _3P_SKEW_R_T:
                    case _3P_SKEW_R_B:
                    case _DEMO_INSIDE:
                    case _DEMO_OUTSIDE:
                        return GET_OSD_INVERSE_REGION();
                }
            }
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_T:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _3P_SKEW_T_M_OUTSIDE:
                    case _3P_SKEW_T_L_OUTSIDE:
                    case _3P_SKEW_T_R_OUTSIDE:

                        if(enumSelRegionInverse == enumSelRegion)
                        {
                            return GET_OSD_INVERSE_REGION();
                        }
                        else
                        {
                            return GET_OSD_SELECT_REGION();
                        }

                    case _FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                    case _3P_SKEW_T_M:
                    case _3P_SKEW_T_L:
                    case _3P_SKEW_T_R:
                    case _DEMO_INSIDE:
                    case _DEMO_OUTSIDE:
                        return GET_OSD_INVERSE_REGION();
                }
            }

        case _OSD_DM_3P_SKEW_B:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _3P_SKEW_B_M_OUTSIDE:
                    case _3P_SKEW_B_L_OUTSIDE:
                    case _3P_SKEW_B_R_OUTSIDE:

                        if(enumSelRegionInverse == enumSelRegion)
                        {
                            return GET_OSD_INVERSE_REGION();
                        }
                        else
                        {
                            return GET_OSD_SELECT_REGION();
                        }

                    case _FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                    case _3P_SKEW_B_M:
                    case _3P_SKEW_B_L:
                    case _3P_SKEW_B_R:
                    case _DEMO_INSIDE:
                    case _DEMO_OUTSIDE:
                        return GET_OSD_INVERSE_REGION();
                }
            }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _4P_LT_OUTSIDE:
                    case _4P_LB_OUTSIDE:
                    case _4P_RT_OUTSIDE:
                    case _4P_RB_OUTSIDE:

                        if(enumSelRegionInverse == enumSelRegion)
                        {
                            return GET_OSD_INVERSE_REGION();
                        }
                        else
                        {
                            return GET_OSD_SELECT_REGION();
                        }

                    case _FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                    case _4P_LT:
                    case _4P_LB:
                    case _4P_RT:
                    case _4P_RB:
                    case _DEMO_INSIDE:
                    case _DEMO_OUTSIDE:
                        return GET_OSD_INVERSE_REGION();
                }
            }
#endif
    }
}
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get User Define OSD region
// Input Value  : EnumDisplayRegion
// Output Value : BYTE OSDSelRegion
//--------------------------------------------------
BYTE UserAdjustGetOsdDisplaySelectRegion(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucOSDSelectRegion = 0;

    if(enumDisplayRegion == UserAdjustConvertDisplayRegion(GET_OSD_SELECT_REGION()))
    {
        ucOSDSelectRegion = GET_OSD_SELECT_REGION();
    }
    else
    {
        ucOSDSelectRegion = GET_OSD_INVERSE_REGION();
    }

    return ucOSDSelectRegion;
}

#if(_HDR10_USER_MASTERING_LV_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDR Table Address
// Input Value  : EnumDisplayRegion, EnumHDR10DarkEnhanceStatus
// Output Value : BYTE Address
//--------------------------------------------------
BYTE *UserAdjustGetHDRUserTableAddress(EnumDisplayRegion enumDisplayRegion, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus)
{
    WORD usMaxDisplayLv = UserCommonColorHDRGetHDR10MaxDisplayLv(enumDisplayRegion); // Mastering lv from source
    WORD usMaxPanelLv = UserCommonColorHDRUserGetPanelMaxLv(enumDisplayRegion); // Max Panel Lv from OCC Calibration
    StructHDR10UserData stHDR10Data = {0};

    UserInterfaceColorHDRGetHDR10UserData(enumDisplayRegion, &stHDR10Data);
    if(stHDR10Data.enumHDR10UserForceMasteringLvStatus == _USER_FORCE_MASTERING_LV_ON)
    {
        EnumHDR10MaxMasteringLvType enumUserForceMaxMasteringLvType = stHDR10Data.enumHDR10UserForceMaxMasteringLvType;
        return (BYTE *)(DWORD)UserCommonColorHDRGetHDR10IGLUTAddr(enumUserForceMaxMasteringLvType, enumHDR10DarkEnhanceStatus, _HDR10_FIXED_POINT_TM_OFF);
    }
    else
    {
        // It is an example code demo how to apply EOTF curve.
        if(usMaxDisplayLv > 0)
        {
            if(usMaxDisplayLv <= usMaxPanelLv)
            {
                return tusHDR10_IG_USER_ADDRESS_INDEX[_HDR10_USER_MAX_MASTERING_LV_TYPE_NOTM * 2 + enumHDR10DarkEnhanceStatus];
            }
            else if(usMaxDisplayLv <= 540)
            {
                return tusHDR10_IG_USER_ADDRESS_INDEX[_HDR10_USER_MAX_MASTERING_LV_TYPE_540 * 2 + enumHDR10DarkEnhanceStatus];
            }
            else if(usMaxDisplayLv <= 1200)
            {
                return tusHDR10_IG_USER_ADDRESS_INDEX[_HDR10_USER_MAX_MASTERING_LV_TYPE_1200 * 2 + enumHDR10DarkEnhanceStatus];
            }
            else if(usMaxDisplayLv <= 4000)
            {
                return tusHDR10_IG_USER_ADDRESS_INDEX[_HDR10_USER_MAX_MASTERING_LV_TYPE_4000 * 2 + enumHDR10DarkEnhanceStatus];
            }
            else // 10000
            {
                return tusHDR10_IG_USER_ADDRESS_INDEX[_HDR10_USER_MAX_MASTERING_LV_TYPE_10000 * 2 + enumHDR10DarkEnhanceStatus];
            }
        }
        else // usMaxDisplayLv == 0
        {
            return tusHDR10_IG_USER_ADDRESS_INDEX[_HDR10_USER_MAX_MASTERING_LV_TYPE_540 * 2 + enumHDR10DarkEnhanceStatus];
        }
    }
}

//--------------------------------------------------
// Description  : Get HDR Table Bank
// Input Value  : EnumDisplayRegion
// Output Value : BYTE Bank
//--------------------------------------------------
BYTE UserAdjustGetHDRUserTableBank(EnumDisplayRegion enumDisplayRegion)
{
    StructHDR10UserData stHDR10Data = {0};

    UserInterfaceColorHDRGetHDR10UserData(enumDisplayRegion, &stHDR10Data);
    if(stHDR10Data.enumHDR10UserForceMasteringLvStatus == _USER_FORCE_MASTERING_LV_ON)
    {
        return _OGC_FLASH_BANK;
    }
    else
    {
        return GET_CURRENT_BANK_NUMBER();
    }
}
#endif
#endif

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : Set IR Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustIR(void)
{
    UserCommonIRHWModeDecoder(tIR_INITIAL_TABLE, GET_CURRENT_BANK_NUMBER());
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

#if(_PIXEL_SHIFT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Resume Orbiting Active
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustPixelOrbiting(void)
{
    if((GET_OSD_PIXELSHIFT_STATUS() == _ON) && (GET_PIXEL_ORBITING_CAPABILITY() == _ON))
    {
#if(_INSTANT_TIMER_EVENT_1 == _ON)
        UserCommonTimer1SetTimerCount(30000);
#endif
    }
    else
    {
#if(_INSTANT_TIMER_EVENT_1 == _ON)
        UserCommonTimer1SetTimerCount(0);
#endif
        UserAdjustPixelOrbitingActiveResume();
    }
}

//--------------------------------------------------
// Description  : Resume Orbiting Active
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveResume(void)
{
#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
    UserAdjustPixelOrbitingActiveResumeDDomain();
#endif

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
    UserAdjustPixelOrbitingActiveResumeIDomain();
#endif
}

//--------------------------------------------------
// Description  : Pixel orbiting step as following
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPixelOrbitingActive(void)
{
#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
    UserAdjustPixelOrbitingActiveDDomain();
#endif

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
    UserAdjustPixelOrbitingActiveIDomain();
#endif
}

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
//--------------------------------------------------
// Description  : Resume Orbiting Active
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveResumeDDomain(void)
{
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(UserCommonRegionGetFrontBackModeSupport() == _TRUE)
    {
        UserAdjustPixelOrbitingActiveResumeDDomainFBmode();
    }
    else
#endif
    {
        UserAdjustPixelOrbitingActiveResumeDDomainEOmode();
    }
}

//--------------------------------------------------
// Description  : Resume Orbiting Active
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveResumeDDomainEOmode(void)
{
    // Check move H or V position
    WORD usDisplay_HSTART = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_START);
    WORD usDisplay_HEND = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_END);
    WORD usDisplay_BGVSTART = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_START);
    WORD usDisplay_BGVEND = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_END);
    WORD usDisplay_VSTART = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_START);

    // Load default value
    // not need execute of center
    if(g_enumPixelShiftState == _PIXEL_SHIFT_DEFAULT)
    {
        return;
    }

    switch(g_enumPixelShiftState)
    {
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
            usDisplay_HSTART += _PIXEL_SHIFT_NUM_H;
            usDisplay_HEND += _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP1_TURN_UP:
            usDisplay_HSTART += _PIXEL_SHIFT_NUM_H;
            usDisplay_HEND += _PIXEL_SHIFT_NUM_H;
            usDisplay_BGVSTART -= _PIXEL_SHIFT_NUM_V;
            usDisplay_BGVEND -= _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
            usDisplay_BGVSTART -= _PIXEL_SHIFT_NUM_V;
            usDisplay_BGVEND -= _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
            break;

        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
            usDisplay_VSTART -= _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
            usDisplay_VSTART -= _PIXEL_SHIFT_NUM_V;
            usDisplay_HSTART -= _PIXEL_SHIFT_NUM_H;
            usDisplay_HEND -= _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP6_TURN_UP:
            usDisplay_HSTART -= _PIXEL_SHIFT_NUM_H;
            usDisplay_HEND -= _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            break;

        default:
            break;
    }

    switch(g_enumPixelShiftState)
    {
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
        case _PIXEL_SHIFT_STEP1_TURN_UP:
        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP6_TURN_UP:
        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            // Display H active start setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_START, usDisplay_HSTART, _DB_APPLY_NONE);

            // Display H active end setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_END, usDisplay_HEND, _DB_APPLY_NONE);

            // Display V Active start setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_START, usDisplay_VSTART, _DB_APPLY_NONE);

            // Display V BG start setting
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_START, usDisplay_BGVSTART, _DB_APPLY_NONE);

            // Display V BG end setting
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_END, usDisplay_BGVEND, _DB_APPLY_NONE);

            // capture H start/end
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START, 0x00, _DB_APPLY_NONE);

            // capture V start/end
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_END, 0x00, _DB_APPLY_NONE);

            // capture V start/end
            UserCommonDDomainSetCaptureWindowEnable(_DISABLE, _DB_APPLY_NO_POLLING);

            break;
        default:
            break;
    }
    g_enumPixelShiftState = _PIXEL_SHIFT_DEFAULT;
}

//--------------------------------------------------
// Description  : Pixel orbiting step in M-domain
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveDDomain(void)
{
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(UserCommonRegionGetFrontBackModeSupport() == _TRUE)
    {
        UserAdjustPixelOrbitingActiveDDomainFBmode();
    }
    else
#endif
    {
        UserAdjustPixelOrbitingActiveDDomainEOmode();
    }
}

//--------------------------------------------------
// Description  : Pixel orbiting step in M-domain
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveDDomainEOmode(void)
{
    // Check move H or V position
    // (bit0,bit2,bit5,bit7 is H position) |_|
    // (bit1,bit3,bit4,bit6 is V position) |-|
    // PIP/PBP no need orbiting
    WORD usDHstart = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_START);
    WORD usDHend = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_END);
    WORD usDVstart = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_START);
    WORD usDVend = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_END);
    WORD usDVBGstart = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_START);
    WORD usDVBGend = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_END);
    WORD usDisplayHstart = UserCommonDDomainGetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START);
    WORD usDisplayHend = UserCommonDDomainGetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_END);
    WORD usDisplayVstart = UserCommonDDomainGetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START);

    if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
    {
        UserCommonDDomainSetCaptureWindowEnable(_DISABLE, _DB_APPLY_NO_POLLING);
        return;
    }
    if(g_enumPixelShiftState == _PIXEL_SHIFT_DEFAULT)
    {
        // capture H start/end
        UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START, usDHstart, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_END, usDHend, _DB_APPLY_NONE);

        // capture V start/end
        UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START, usDVstart, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_END, usDVend, _DB_APPLY_NONE);

        usDisplayHend = usDHend;
        usDisplayHstart = usDHstart;
        usDisplayVstart = usDVstart;
    }

    // Enable Capture Window
    UserCommonDDomainSetCaptureWindowEnable(_ENABLE, _DB_APPLY_POLLING);

    if(g_enumPixelShiftState != _PIXEL_SHIFT_DEFAULT)
    {
        g_enumPixelShiftState <<= 1;
    }
    else
    {
        g_enumPixelShiftState = _PIXEL_SHIFT_STEP0_TURN_LEFT;
    }

    switch(g_enumPixelShiftState)
    {
        // H <-
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
            usDisplayHend -= _PIXEL_SHIFT_NUM_H; // CW
            usDHstart -= _PIXEL_SHIFT_NUM_H; // DTG
            usDHend -= _PIXEL_SHIFT_NUM_H; // DTG
            break;

        // V up
        case _PIXEL_SHIFT_STEP1_TURN_UP:
            usDisplayVstart += _PIXEL_SHIFT_NUM_V; // CW
            usDVBGstart += _PIXEL_SHIFT_NUM_V; // DTG
            usDVBGend += _PIXEL_SHIFT_NUM_V; // DTG
            break;

        // H ->
        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
            usDisplayHend += _PIXEL_SHIFT_NUM_H; // CW
            usDHstart += _PIXEL_SHIFT_NUM_H; // DTG
            usDHend += _PIXEL_SHIFT_NUM_H; // DTG
            break;

        // V down
        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
            usDisplayVstart -= _PIXEL_SHIFT_NUM_V; // CW
            usDVBGstart -= _PIXEL_SHIFT_NUM_V; // DTG
            usDVBGend -= _PIXEL_SHIFT_NUM_V; // DTG
            break;

        // V down
        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
            usDisplayVstart += _PIXEL_SHIFT_NUM_V;
            usDVstart += _PIXEL_SHIFT_NUM_V;

            break;

        // H ->
        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
            usDisplayHstart += _PIXEL_SHIFT_NUM_H; // CW
            usDHstart += _PIXEL_SHIFT_NUM_H; // DTG
            usDHend += _PIXEL_SHIFT_NUM_H; // DTG
            break;

        // V up
        case _PIXEL_SHIFT_STEP6_TURN_UP:
            usDisplayVstart -= _PIXEL_SHIFT_NUM_V;
            usDVstart -= _PIXEL_SHIFT_NUM_V;
            break;

        // H <-
        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            usDisplayHstart -= _PIXEL_SHIFT_NUM_H; // CW
            usDHstart -= _PIXEL_SHIFT_NUM_H; // DTG
            usDHend -= _PIXEL_SHIFT_NUM_H; // DTG
            break;

        default:
            break;
    }

    switch(g_enumPixelShiftState)
    {
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            // Display H active start setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_START, usDHstart, _DB_APPLY_NONE);
            // Display H active end setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_END, usDHend, _DB_APPLY_NONE);
            // Capture window H start setting
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START, usDisplayHstart, _DB_APPLY_NONE);
            // Capture window H end setting
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_END, usDisplayHend, _DB_APPLY_POLLING);
            if(g_enumPixelShiftState == _PIXEL_SHIFT_DONE)
            {
                // 0x00 is final move process so setting to default
                g_enumPixelShiftState = _PIXEL_SHIFT_DEFAULT;
            }
            break;

        case _PIXEL_SHIFT_STEP1_TURN_UP:
        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
        case _PIXEL_SHIFT_STEP6_TURN_UP:
            // Capture window V start setting
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START, usDisplayVstart, _DB_APPLY_NONE);

            // Display V active start setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_START, usDVstart, _DB_APPLY_NONE);

            // Display V background start setting
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_START, usDVBGstart, _DB_APPLY_NONE);

            // Display V background end setting
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_END, usDVBGend, _DB_APPLY_POLLING);

            break;

        default:
            break;
    }
    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Pixel orbiting step in M-domain
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveDDomainFBmode(void)
{
    // Check move H or V position
    // (bit0,bit2,bit5,bit7 is H position) |_|
    // (bit1,bit3,bit4,bit6 is V position) |-|
    // PIP/PBP no need orbiting

    // DisplayTimingGen
    // Active
    WORD usDHstart = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_START);
    WORD usDHend = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_END);
    WORD usDHwidth = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_WIDTH) / 2;
    WORD usDVstart = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_START);
    WORD usDVend = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_END);

    // Background
    WORD usDHBGStart = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_START);
    WORD usDHBGEnd = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_END);
    WORD usDVBGstart = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_START);
    WORD usDVBGend = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_END);
    WORD usDHBGWidth = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_WIDTH) / 2;

    // Capture Window
    WORD usCWActiveHstart = UserCommonDDomainGetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START);
    WORD usCWActiveHend = UserCommonDDomainGetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_END);
    WORD usCWActiveVstart = UserCommonDDomainGetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START);
    WORD usCWBGHstart = UserCommonDDomainGetCaptureWindowBackground(_DISPLAY_BACKGROUND_H_START);
    WORD usCWBGHend = UserCommonDDomainGetCaptureWindowBackground(_DISPLAY_BACKGROUND_H_END);

    // Capture Window Back Part
    WORD usCWActiveHstart_Back = 0;
    WORD usCWActiveHend_Back = 0;
    WORD usCWActiveVstart_Back = 0;
    WORD usCWBGHstart_Back = 0;
    WORD usCWBGHend_Back = 0;

    // Midline
    WORD usMidline = 0;
    WORD usBGMidline = 0;

    // DSPC Extension
    BYTE ucDspcExt = UserCommonDDomainGetDspcDenDelay();

    if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
    {
        UserCommonDDomainSetCaptureWindowEnable(_DISABLE, _DB_APPLY_NO_POLLING);
        return;
    }

    // Enable FB Serparate & Disable Extension Extract
    UserCommonDDomainSetExtensionExtract(_DISABLE, _DB_APPLY_NONE);

    // Get CW Timing Format Backpart
    usCWActiveHstart_Back = UserCommonDDomainGetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_H_START);
    usCWActiveHend_Back = UserCommonDDomainGetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_H_END);
    usCWActiveVstart_Back = UserCommonDDomainGetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_V_START);
    usCWBGHstart_Back = UserCommonDDomainGetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_H_START);
    usCWBGHend_Back = UserCommonDDomainGetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_H_END);

    if(g_enumPixelShiftState == _PIXEL_SHIFT_DEFAULT)
    {
        usMidline = usDHstart + usDHwidth;
        usBGMidline = usDHBGStart + usDHBGWidth;

        usCWActiveHstart = usDHstart;
        usCWActiveHend = usMidline;
        usCWActiveVstart = usDVstart;

        usCWActiveHstart_Back = usMidline;
        usCWActiveHend_Back = usMidline + usDHwidth;
        usCWActiveVstart_Back = usDVstart;

        usCWBGHstart = usDHBGStart;
        usCWBGHend = usBGMidline;
        usCWBGHstart_Back = usBGMidline;
        usCWBGHend_Back = usBGMidline + usDHBGWidth;

        // capture Active H start/end
        UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START, usCWActiveHstart, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_END, usCWActiveHend, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_H_START, usCWActiveHstart_Back, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_H_END, usCWActiveHend_Back, _DB_APPLY_NONE);

        // capture Background H start/end
        UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_H_START, usDHBGStart, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_H_END, usBGMidline, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_H_START, usBGMidline, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_H_END, usCWBGHend_Back, _DB_APPLY_NONE);

        // capture Active V start/end
        UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START, usDVstart, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_END, usDVend, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_V_START, usDVstart, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_V_END, usDVend, _DB_APPLY_NONE);

        // capture Background V start/end
        UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_V_START, usDVBGstart, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_V_END, usDVBGend, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_V_START, usDVBGstart, _DB_APPLY_NONE);
        UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_V_END, usDVBGend, _DB_APPLY_NONE);
    }

    // Enable Capture Window
    UserCommonDDomainSetCaptureWindowEnable(_ENABLE, _DB_APPLY_POLLING);

    if(g_enumPixelShiftState != _PIXEL_SHIFT_DEFAULT)
    {
        g_enumPixelShiftState <<= 1;
    }
    else
    {
        g_enumPixelShiftState = _PIXEL_SHIFT_STEP0_TURN_LEFT;
    }

    switch(g_enumPixelShiftState)
    {
        // H <-
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
            usDHBGStart += _PIXEL_SHIFT_NUM_H; // DTG
            usDHBGEnd += _PIXEL_SHIFT_NUM_H; // DTG
            usDHend += _PIXEL_SHIFT_NUM_H; // DTG
            usCWActiveHstart += _PIXEL_SHIFT_NUM_H; // CW
            usCWActiveHend += _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHstart += _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHend += _PIXEL_SHIFT_NUM_H; // CW
            usCWActiveHstart_Back += _PIXEL_SHIFT_NUM_H * 2; // CW
            usCWActiveHend_Back += _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHstart_Back += _PIXEL_SHIFT_NUM_H * 2; // CW
            usCWBGHend_Back += _PIXEL_SHIFT_NUM_H * 2; // CW
            ucDspcExt += _PIXEL_SHIFT_NUM_H; // Ext
            break;

        // V up
        case _PIXEL_SHIFT_STEP1_TURN_UP:
            usCWActiveVstart += _PIXEL_SHIFT_NUM_V; // CW
            usCWActiveVstart_Back += _PIXEL_SHIFT_NUM_V; // CW
            usDVBGstart += _PIXEL_SHIFT_NUM_V; // DTG
            usDVBGend += _PIXEL_SHIFT_NUM_V; // DTG
            break;

        // H ->
        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
            usDHBGStart -= _PIXEL_SHIFT_NUM_H; // DTG
            usDHBGEnd -= _PIXEL_SHIFT_NUM_H; // DTG
            usDHend -= _PIXEL_SHIFT_NUM_H; // DTG
            usCWActiveHstart -= _PIXEL_SHIFT_NUM_H; // CW
            usCWActiveHend -= _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHstart -= _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHend -= _PIXEL_SHIFT_NUM_H; // CW
            usCWActiveHstart_Back -= _PIXEL_SHIFT_NUM_H * 2; // CW
            usCWActiveHend_Back -= _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHstart_Back -= _PIXEL_SHIFT_NUM_H * 2; // CW
            usCWBGHend_Back -= _PIXEL_SHIFT_NUM_H * 2; // CW
            ucDspcExt -= _PIXEL_SHIFT_NUM_H; // Ext
            break;

        // V down
        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
            usCWActiveVstart -= _PIXEL_SHIFT_NUM_V; // CW
            usCWActiveVstart_Back -= _PIXEL_SHIFT_NUM_V; // CW
            usDVBGstart -= _PIXEL_SHIFT_NUM_V; // DTG
            usDVBGend -= _PIXEL_SHIFT_NUM_V; // DTG
            break;

        // V down
        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
            usCWActiveVstart -= _PIXEL_SHIFT_NUM_V; // CW
            usCWActiveVstart_Back -= _PIXEL_SHIFT_NUM_V; // CW
            usDVBGstart -= _PIXEL_SHIFT_NUM_V; // DTG
            usDVBGend -= _PIXEL_SHIFT_NUM_V; // DTG
            break;

        // H ->
        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
            usDHstart += _PIXEL_SHIFT_NUM_H; // DTG
            usDHend += _PIXEL_SHIFT_NUM_H; // DTG
            usCWActiveHstart += _PIXEL_SHIFT_NUM_H; // CW
            usCWActiveHstart_Back -= _PIXEL_SHIFT_NUM_H; // CW
            usCWActiveHend_Back -= _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHstart_Back -= _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHend_Back -= _PIXEL_SHIFT_NUM_H; // CW
            ucDspcExt -= _PIXEL_SHIFT_NUM_H; // Ext
            break;

        // V up
        case _PIXEL_SHIFT_STEP6_TURN_UP:
            usCWActiveVstart += _PIXEL_SHIFT_NUM_V; // CW
            usCWActiveVstart_Back += _PIXEL_SHIFT_NUM_V; // CW
            usDVBGstart += _PIXEL_SHIFT_NUM_V; // DTG
            usDVBGend += _PIXEL_SHIFT_NUM_V; // DTG
            break;

        // H <-
        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            usDHstart -= _PIXEL_SHIFT_NUM_H; // DTG
            usDHend -= _PIXEL_SHIFT_NUM_H; // DTG
            usCWActiveHstart -= _PIXEL_SHIFT_NUM_H; // CW
            usCWActiveHstart_Back += _PIXEL_SHIFT_NUM_H; // CW
            usCWActiveHend_Back += _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHstart_Back += _PIXEL_SHIFT_NUM_H; // CW
            usCWBGHend_Back += _PIXEL_SHIFT_NUM_H; // CW
            ucDspcExt += _PIXEL_SHIFT_NUM_H; // Ext
            break;

        default:
            break;
    }

    switch(g_enumPixelShiftState)
    {
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            // Display Timing Gen Horizontal Timing Setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_START, usDHstart, _DB_APPLY_NONE);
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_END, usDHend, _DB_APPLY_NONE);
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_START, usDHBGStart, _DB_APPLY_NONE);
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_END, usDHBGEnd, _DB_APPLY_NONE);

            // Capture window Active Horizontal Timing Setting
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START, usCWActiveHstart, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_END, usCWActiveHend, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_H_START, usCWActiveHstart_Back, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_H_END, usCWActiveHend_Back, _DB_APPLY_NONE);

            // Capture window Background Horizontal Timing Setting
            UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_H_START, usCWBGHstart, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_H_END, usCWBGHend, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_H_START, usCWBGHstart_Back, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_H_END, usCWBGHend_Back, _DB_APPLY_NONE);

            // Set dspc extension
            UserCommonDDomainSetDspcDenDelay(ucDspcExt, _DB_APPLY_POLLING);

            if(g_enumPixelShiftState == _PIXEL_SHIFT_DONE)
            {
                // 0x00 is final move process so setting to default
                g_enumPixelShiftState = _PIXEL_SHIFT_DEFAULT;
            }
            break;

        case _PIXEL_SHIFT_STEP1_TURN_UP:
        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
        case _PIXEL_SHIFT_STEP6_TURN_UP:
            // Capture window V start setting
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START, usCWActiveVstart, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_V_START, usCWActiveVstart_Back, _DB_APPLY_NONE);

            // Display V active start setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_START, usDVstart, _DB_APPLY_NONE);

            // Display V background start setting
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_START, usDVBGstart, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_V_START, usDVBGstart, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_V_START, usDVBGstart, _DB_APPLY_NONE);

            // Display V background end setting
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_END, usDVBGend, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_V_END, usDVBGend, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_V_END, usDVBGend, _DB_APPLY_POLLING);
            break;

        default:
            break;
    }

    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
}
//--------------------------------------------------
// Description  : Resume Orbiting Active in FB mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveResumeDDomainFBmode(void)
{
    // Check move H or V position
    WORD usDisplay_HSTART = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_START);
    WORD usDisplay_HEND = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_END);
    WORD usDisplay_BGHSTART = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_START);
    WORD usDisplay_BGHEND = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_END);
    WORD usDisplay_VSTART = UserCommonDDomainGetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_START);
    WORD usDisplay_BGVSTART = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_START);
    WORD usDisplay_BGVEND = UserCommonDDomainGetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_END);

    BYTE ucExt = UserCommonDDomainGetExtension();

    // Load default value
    // not need execute of center
    if(g_enumPixelShiftState == _PIXEL_SHIFT_DEFAULT)
    {
        return;
    }

    switch(g_enumPixelShiftState)
    {
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
            usDisplay_BGHSTART -= _PIXEL_SHIFT_NUM_H;
            usDisplay_BGHEND -= _PIXEL_SHIFT_NUM_H;
            usDisplay_HEND -= _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP1_TURN_UP:
            usDisplay_BGHSTART -= _PIXEL_SHIFT_NUM_H;
            usDisplay_BGHEND -= _PIXEL_SHIFT_NUM_H;
            usDisplay_HEND -= _PIXEL_SHIFT_NUM_H;
            usDisplay_BGVSTART -= _PIXEL_SHIFT_NUM_V;
            usDisplay_BGVEND -= _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
            usDisplay_BGVSTART -= _PIXEL_SHIFT_NUM_V;
            usDisplay_BGVEND -= _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
            break;

        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
            usDisplay_BGVSTART += _PIXEL_SHIFT_NUM_V;
            usDisplay_BGVEND += _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
            usDisplay_BGVSTART += _PIXEL_SHIFT_NUM_V;
            usDisplay_BGVEND += _PIXEL_SHIFT_NUM_V;
            usDisplay_HSTART -= _PIXEL_SHIFT_NUM_H;
            usDisplay_HEND -= _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP6_TURN_UP:
            usDisplay_HSTART -= _PIXEL_SHIFT_NUM_H;
            usDisplay_HEND -= _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            break;

        default:
            break;
    }

    switch(g_enumPixelShiftState)
    {
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
        case _PIXEL_SHIFT_STEP1_TURN_UP:
        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP6_TURN_UP:
        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            // Display H active start setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_START, usDisplay_HSTART, _DB_APPLY_NONE);
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_H_END, usDisplay_HEND, _DB_APPLY_NONE);
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_START, usDisplay_BGHSTART, _DB_APPLY_NONE);
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_H_END, usDisplay_BGHEND, _DB_APPLY_NONE);

            // Display V Active start setting
            UserCommonDDomainSetDisplayTimingGenActiveRegion(_DISPLAY_FORMAT_V_START, usDisplay_VSTART, _DB_APPLY_NONE);

            // Display V BG start setting
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_START, usDisplay_BGVSTART, _DB_APPLY_NONE);
            UserCommonDDomainSetDisplayTimingGenBackground(_DISPLAY_BACKGROUND_V_END, usDisplay_BGVEND, _DB_APPLY_NONE);

            // capture H start/end
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_END, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_H_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_H_END, 0x00, _DB_APPLY_NONE);

            // capture V start/end
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_END, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_V_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowActiveRegion_Back(_DISPLAY_FORMAT_V_END, 0x00, _DB_APPLY_NONE);

            // capture H Background start/end
            UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_H_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_H_END, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_H_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_H_END, 0x00, _DB_APPLY_NONE);

            // capture V Background start/end
            UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_V_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground(_DISPLAY_BACKGROUND_V_END, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_V_START, 0x00, _DB_APPLY_NONE);
            UserCommonDDomainSetCaptureWindowBackground_Back(_DISPLAY_BACKGROUND_V_END, 0x00, _DB_APPLY_NONE);

            // capture V start/end
            UserCommonDDomainSetCaptureWindowEnable(_DISABLE, _DB_APPLY_NONE);

            // Enable Extension Extract
            UserCommonDDomainSetExtensionExtract(_ENABLE, _DB_APPLY_NONE);

            // Set dspc extension
            UserCommonDDomainSetDspcDenDelay(ucExt, _DB_APPLY_POLLING);

            break;
        default:
            break;
    }
    g_enumPixelShiftState = _PIXEL_SHIFT_DEFAULT;
}
#endif // End of #if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#endif // End of #if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
//--------------------------------------------------
// Description  : Resume Orbiting Active
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveResumeIDomain(void)
{
    WORD usHshift = 0;
    WORD usVdelay = 0;
    EnumDisplayRegion enumDisplayRegion = ((_EAGLE_SIGHT_SUPPORT == _ON) ? _DISPLAY_RGN_EAGLE_SIGHT_MAIN : _DISPLAY_RGN_1P);
    EnumInputDataPath enumInputPath = UserCommonRegionGetInputDataPath(enumDisplayRegion);

    UserCommonIDomainSetCaptureInputRegion(enumDisplayRegion);

    // Load default value
    // not need execute of center
    if(g_enumPixelShiftState == _PIXEL_SHIFT_DEFAULT)
    {
        return;
    }

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetInputPort(enumDisplayRegion) == _A0_INPUT_PORT)
    {
        usHshift = UserCommonVgaGetCaptureHDelay();
        usVdelay = UserCommonVgaGetCaptureVDelay();
    }
    else
#endif
    {
        usHshift = UserCommonIDomainGetCaptureHStartPosition();
        usVdelay = UserCommonIDomainGetCaptureVDelay();
    }

    switch(g_enumPixelShiftState)
    {
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
            usHshift -= _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP1_TURN_UP:
            usHshift -= _PIXEL_SHIFT_NUM_H;
            usVdelay -= _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
            usVdelay -= _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
            break;

        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
            usVdelay += _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
            usHshift += _PIXEL_SHIFT_NUM_H;
            usVdelay += _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP6_TURN_UP:
            usHshift += _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            break;

        default:
            break;
    }

    UserCommonRegionSetWatchDog(enumDisplayRegion, _DISABLE);

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetInputPort(enumDisplayRegion) == _A0_INPUT_PORT)
    {
        UserCommonVgaSetCaptureHDelay(usHshift);
        UserCommonVgaSetCaptureVDelay(usVdelay);
        UserCommonVgaDoubleBufferApply();
    }
    else
#endif
    {
        UserCommonIDomainSetCaptureHStartPosition(usHshift);
        UserCommonIDomainSetCaptureVDelay(usVdelay);

        UserCommonDisplayGlobalIDomainDBApply(enumDisplayRegion, _DB_APPLY_POLLING);
    }

    UserCommonTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);

    UserCommonRegionSetWatchDog(enumDisplayRegion, _ENABLE);

    g_enumPixelShiftState = _PIXEL_SHIFT_DEFAULT;
}

//--------------------------------------------------
// Description  : Pixel orbiting step in M-domain
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPixelOrbitingActiveIDomain(void)
{
    WORD usHshift = 0;
    WORD usVdelay = 0;
    EnumDisplayRegion enumDisplayRegion = ((_EAGLE_SIGHT_SUPPORT == _ON) ? _DISPLAY_RGN_EAGLE_SIGHT_MAIN : _DISPLAY_RGN_1P);
    EnumInputDataPath enumInputPath = UserCommonRegionGetInputDataPath(enumDisplayRegion);

    UserCommonIDomainSetCaptureInputRegion(enumDisplayRegion);

    if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
    {
        return;
    }

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetInputPort(enumDisplayRegion) == _A0_INPUT_PORT)
    {
        usHshift = UserCommonVgaGetCaptureHDelay();
        usVdelay = UserCommonVgaGetCaptureVDelay();
    }
    else
#endif
    {
        usHshift = UserCommonIDomainGetCaptureHStartPosition();
        usVdelay = UserCommonIDomainGetCaptureVDelay();
    }

    if((g_enumPixelShiftState == _PIXEL_SHIFT_DEFAULT) ||
       (g_enumPixelShiftState == _PIXEL_SHIFT_DONE))
    {
        g_enumPixelShiftState = _PIXEL_SHIFT_STEP0_TURN_LEFT;
    }
    else
    {
        g_enumPixelShiftState <<= 1;
    }

    switch(g_enumPixelShiftState)
    {
        case _PIXEL_SHIFT_STEP0_TURN_LEFT:
        case _PIXEL_SHIFT_STEP7_TURN_LEFT:
            usHshift += _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP1_TURN_UP:
        case _PIXEL_SHIFT_STEP6_TURN_UP:
            usVdelay += _PIXEL_SHIFT_NUM_V;
            break;

        case _PIXEL_SHIFT_STEP2_TURN_RIGHT:
        case _PIXEL_SHIFT_STEP5_TURN_RIGHT:
            usHshift -= _PIXEL_SHIFT_NUM_H;
            break;

        case _PIXEL_SHIFT_STEP3_TURN_DOWN:
        case _PIXEL_SHIFT_STEP4_TURN_DOWN:
            usVdelay -= _PIXEL_SHIFT_NUM_V;
            break;

        default:
            break;
    }

    UserCommonRegionSetWatchDog(enumDisplayRegion, _DISABLE);

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetInputPort(enumDisplayRegion) == _A0_INPUT_PORT)
    {
        UserCommonVgaSetCaptureHDelay(usHshift);
        UserCommonVgaSetCaptureVDelay(usVdelay);
        UserCommonVgaDoubleBufferApply();
    }
    else
#endif
    {
        UserCommonIDomainSetCaptureHStartPosition(usHshift);
        UserCommonIDomainSetCaptureVDelay(usVdelay);

        UserCommonDisplayGlobalIDomainDBApply(enumDisplayRegion, _DB_APPLY_POLLING);
    }

    UserCommonTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);

    UserCommonRegionSetWatchDog(enumDisplayRegion, _ENABLE);
}
#endif // End of #if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)

#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set SDRToHDR parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustSDRToHDR(EnumSelRegion enumSelRegion, bit bOn)
{
    UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, _COLOR_FUNCTION_3DGAMMA | _COLOR_FUNCTION_CTS_BRI | _COLOR_FUNCTION_SDRTOHDR);

    if(bOn == _ON)
    {
#if(_CONTRAST_FUNCTION == _ON)
        UserCommonColorContrastAdjust(enumSelRegion);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
        UserCommonColorBrightnessAdjust(enumSelRegion);
#endif
        UserCommonColorSDRToHDRAdjust(enumSelRegion);
    }
    else
    {
        UserCommonColorICMAdjust(enumSelRegion);
        UserCommonColorDCCAdjust(enumSelRegion);
        UserCommonColorPCMAdjust(enumSelRegion, _DB_APPLY_NONE);

#if(_CONTRAST_FUNCTION == _ON)
        if(GET_OSD_PCM_STATUS(UserAdjustGetOSDSelectRegion(enumSelRegion)) == _PCM_OSD_NATIVE)
        {
            RTDNVRamLoadColorSetting(UserAdjustGetOSDSelectRegion(enumSelRegion));
        }
        UserCommonColorContrastAdjust(enumSelRegion);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
        UserCommonColorBrightnessAdjust(enumSelRegion);
#endif

#if((_RGB_3D_GAMMA_FUNCTION == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON))
        UserCommonColor3DGammaAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif
    }

    UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, _COLOR_FUNCTION_3DGAMMA | _COLOR_FUNCTION_CTS_BRI | _COLOR_FUNCTION_SDRTOHDR);
}
#endif // End of #if(_SDR_TO_HDR_SUPPORT == _ON)

#if(_COLOR_DEMO_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set HIGHLIGHT WINDOW
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType(void)
{
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_MOVE)
    {
        UserCommonTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
    }

#if(_COLOR_IP_HL_WIN == _ON)
    UserCommonColorHLWinTypeAdjust(_DB_APPLY_NO_POLLING);
#endif
}

//--------------------------------------------------
// Description  : High Light Window Type5 Move
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType5Move(void)
{
    EnumDBApply enumDBApply = ((SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING) ? _DB_APPLY_NONE : _DB_APPLY_NO_POLLING);

    if(g_bColorHLWinRLMove == _RIGHT)
    {
        g_usColorHLWinHPos++;

        if(_PANEL_DH_WIDTH <= (g_usColorHLWinHPos + g_usColorHLWinHWidth + _HL_WIN_BORDER_SIZE))
        {
            g_bColorHLWinRLMove = _LEFT;
            g_usColorHLWinHPos = _PANEL_DH_WIDTH - (g_usColorHLWinHWidth + _HL_WIN_BORDER_SIZE);
        }
    }
    else // _LEFT
    {
        g_usColorHLWinHPos--;

        if(g_usColorHLWinHPos == 0)
        {
            g_bColorHLWinRLMove = _RIGHT;
            g_usColorHLWinHPos = 0;
        }
    }

    UserCommonColorHLWBorderAdjust(_HL_WIN_BORDER_SIZE, 255, 0, 0, _DB_APPLY_NONE);
    UserCommonColorHLWBorderEnable(_ON, _ON, _ON, _ON, _DB_APPLY_NONE);
    UserCommonColorHLWAdjust(g_usColorHLWinHPos, g_usColorHLWinHWidth, g_usColorHLWinVPos, g_usColorHLWinVHeight, enumDBApply);

    UserCommonTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
}
#endif // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#if(_SHARPNESS_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set SHP 1:1 Coef
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
BYTE *UserAdjustGetSharpness1To1Coef(EnumSUCoefType enumSUCoefType, EnumSelRegion enumSelRegion, BYTE ucOsdSelSharpness)
{
    enumSelRegion = enumSelRegion;

    switch(enumSUCoefType)
    {
#if(_HW_HSU_128TAPS_SUPPORT == _ON)
        case _H_SU_128TAPS_1_TO_1:
            return tSCALE_128TAPS_1to1_COEF_TABLE[ucOsdSelSharpness];
#endif

#if(_HW_HSU_96TAPS_SUPPORT == _ON)
        case _H_SU_96TAPS_1_TO_1:
            return tSCALE_96TAPS_1to1_COEF_TABLE[ucOsdSelSharpness];
#endif
        default:
            return _NULL_POINTER;
    }
}
//--------------------------------------------------
// Description  : Set SHP Normal Coef
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
BYTE *UserAdjustGetSharpnessNormalCoef(EnumSUCoefType enumSUCoefType, EnumSelRegion enumSelRegion, BYTE ucOsdSelSharpness)
{
    enumSelRegion = enumSelRegion;

    switch(enumSUCoefType)
    {
#if((_HW_HSU_128TAPS_SUPPORT == _ON) || (_HW_VSU_128TAPS_SUPPORT == _ON))
        case _H_V_SU_128TAPS_NORMAL:
            return tSCALE_128TAPS_NORMAL_COEF_TABLE[ucOsdSelSharpness];
#endif

#if((_HW_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
        case _H_V_SU_96TAPS_NORMAL:
            return tSCALE_96TAPS_NORMAL_COEF_TABLE[ucOsdSelSharpness];
#endif
        default:
            return _NULL_POINTER;
    }
}

//--------------------------------------------------
// Description  : User Bypass Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserAdjustSharpnessBypassCheck(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Sharpness Coef BankNum
// Input Value  : None
// Output Value : BankNum
//--------------------------------------------------
BYTE UserAdjustGetSharpnessCoefBankNum(void)
{
    return GET_CURRENT_BANK_NUMBER();
}
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set SD_H Normal Coef
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
BYTE *UserAdjustGetScalingDownCoefH(EnumSDCoefType enumSDCoefType, EnumSelRegion enumSelRegion)
{
    enumSelRegion = enumSelRegion;
    switch(enumSDCoefType)
    {
        case _H_SD_128TAPS_NORMAL_0:
            return tSCALEDOWN_128TAPS_NORMAL_COEF_TABLE[0];
        case _H_SD_128TAPS_NORMAL_1:
            return tSCALEDOWN_128TAPS_NORMAL_COEF_TABLE[1];
        case _H_SD_128TAPS_NORMAL_2:
            return tSCALEDOWN_128TAPS_NORMAL_COEF_TABLE[2];
        case _H_SD_128TAPS_NORMAL_3:
            return tSCALEDOWN_128TAPS_NORMAL_COEF_TABLE[3];
        case _H_SD_128TAPS_NORMAL_4:
            return tSCALEDOWN_128TAPS_NORMAL_COEF_TABLE[4];
        case _H_SD_128TAPS_BYPASS_0:
            return tSCALEDOWN_128TAPS_BYPASS_COEF_TABLE[0];
        case _H_SD_128TAPS_BYPASS_1:
            return tSCALEDOWN_128TAPS_BYPASS_COEF_TABLE[1];
        case _H_SD_128TAPS_BYPASS_2:
            return tSCALEDOWN_128TAPS_BYPASS_COEF_TABLE[2];
        case _H_SD_128TAPS_BYPASS_3:
            return tSCALEDOWN_128TAPS_BYPASS_COEF_TABLE[3];
        case _H_SD_128TAPS_BYPASS_4:
            return tSCALEDOWN_128TAPS_BYPASS_COEF_TABLE[4];
        default:
            return tSCALEDOWN_128TAPS_NORMAL_COEF_TABLE[2];
    }
}
//--------------------------------------------------
// Description  : Set SD_V Normal Coef
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
BYTE *UserAdjustGetScalingDownCoefV(EnumSDCoefType enumSDCoefType, EnumSelRegion enumSelRegion)
{
    enumSelRegion = enumSelRegion;
    switch(enumSDCoefType)
    {
        case _V_SD_64TAPS_NORMAL_0:
            return tSCALEDOWN_64TAPS_NORMAL_COEF_TABLE[0];
        case _V_SD_64TAPS_NORMAL_1:
            return tSCALEDOWN_64TAPS_NORMAL_COEF_TABLE[1];
        case _V_SD_64TAPS_NORMAL_2:
            return tSCALEDOWN_64TAPS_NORMAL_COEF_TABLE[2];
        case _V_SD_64TAPS_NORMAL_3:
            return tSCALEDOWN_64TAPS_NORMAL_COEF_TABLE[3];
        case _V_SD_64TAPS_NORMAL_4:
            return tSCALEDOWN_64TAPS_NORMAL_COEF_TABLE[4];
        case _V_SD_64TAPS_BYPASS_0:
            return tSCALEDOWN_64TAPS_BYPASS_COEF_TABLE[0];
        case _V_SD_64TAPS_BYPASS_1:
            return tSCALEDOWN_64TAPS_BYPASS_COEF_TABLE[1];
        case _V_SD_64TAPS_BYPASS_2:
            return tSCALEDOWN_64TAPS_BYPASS_COEF_TABLE[2];
        case _V_SD_64TAPS_BYPASS_3:
            return tSCALEDOWN_64TAPS_BYPASS_COEF_TABLE[3];
        case _V_SD_64TAPS_BYPASS_4:
            return tSCALEDOWN_64TAPS_BYPASS_COEF_TABLE[4];
        default:
            return tSCALEDOWN_64TAPS_NORMAL_COEF_TABLE[2];
    }
}
#endif

#if(_ANTI_ALIASING_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get Anti-Aliasing Coef Table
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
DWORD *UserAdjustGetAntiAliasingCoefTableAddress(EnumAntiAliasingModeType enumAntiAliasingModeType, BYTE ucOsdSelAntiAliasing)
{
    switch(enumAntiAliasingModeType)
    {
        case _ANTI_ALIASING_EDGE_ENHANCE:
            return tCOLOR_ANTIALIASING_EDGE_ENHANCE_SETTING_TABLE[ucOsdSelAntiAliasing];

        case _ANTI_ALIASING_NOISE_REDUCTION:
            return tCOLOR_ANTIALIASING_NOISE_REDUCTION_SETTING_TABLE[ucOsdSelAntiAliasing];

        default:
            return _NULL_POINTER;
    }
}
#endif

//--------------------------------------------------
// Description  : Get DDC-CI Status
// Input Value  : None
// Output Value : _DDCCI_MODE / _DEBUG_MODE
//--------------------------------------------------
EnumDDCCIDebugMode UserAdjustDdcciGetStatus(void)
{
    if(GET_OSD_DDCCI_STATUS() == _TRUE)
    {
        return _DDCCI_MODE;
    }
    else
    {
        return _DEBUG_MODE;
    }
}

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch Dp Version to 1.4, if HDR On
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHdrCheckDpVersion(EnumInputPort enumInputPort, WORD usHdrMode)
{
    // Switch Dp Version to 1.4, if HDR Function Support
    if(usHdrMode != _HDR10_MODE_OFF)
    {
        switch(enumInputPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            case _D0_INPUT_PORT:

                if(GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2)
                {
                    SET_OSD_DP_D0_VERSION(_DP_VER_1_DOT_4);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                    UserCommonDpRxVersionSwitch(_D0_INPUT_PORT, UserInterfaceDpGetVersion(_D0_INPUT_PORT), UserCommonDpGetMSTCapablePort());
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            case _D1_INPUT_PORT:

                if(GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2)
                {
                    SET_OSD_DP_D1_VERSION(_DP_VER_1_DOT_4);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                    UserCommonDpRxVersionSwitch(_D1_INPUT_PORT, UserInterfaceDpGetVersion(_D1_INPUT_PORT), UserCommonDpGetMSTCapablePort());
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            case _D2_INPUT_PORT:

                if(GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2)
                {
                    SET_OSD_DP_D2_VERSION(_DP_VER_1_DOT_4);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                    UserCommonDpRxVersionSwitch(_D2_INPUT_PORT, UserInterfaceDpGetVersion(_D2_INPUT_PORT), UserCommonDpGetMSTCapablePort());
                }

                break;
#endif

            default:
                break;
        }
    }
}
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Version Force Update
// Input Value  : enumInputPort, bEnable, enumDpVersionType
// Output Value : None
//--------------------------------------------------
void UserAdjustDpVersionForceUpdate(EnumInputPort enumInputPort, bit bEnable, EnumOSDDpPortVersionDef enumOSDDpPortVersionDef)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            if((GET_OSD_DP_D0_VERSION() < enumOSDDpPortVersionDef) && (bEnable == _ENABLE))
            {
                SET_OSD_DP_D0_VERSION(enumOSDDpPortVersionDef);

                UserCommonDpRxVersionSwitch(_D0_INPUT_PORT, UserInterfaceDpGetVersion(_D0_INPUT_PORT), UserCommonDpGetMSTCapablePort());
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            if((GET_OSD_DP_D1_VERSION() < enumOSDDpPortVersionDef) && (bEnable == _ENABLE))
            {
                SET_OSD_DP_D1_VERSION(enumOSDDpPortVersionDef);

                UserCommonDpRxVersionSwitch(_D1_INPUT_PORT, UserInterfaceDpGetVersion(_D1_INPUT_PORT), UserCommonDpGetMSTCapablePort());
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            if((GET_OSD_DP_D2_VERSION() < enumOSDDpPortVersionDef) && (bEnable == _ENABLE))
            {
                SET_OSD_DP_D2_VERSION(enumOSDDpPortVersionDef);

                UserCommonDpRxVersionSwitch(_D2_INPUT_PORT, UserInterfaceDpGetVersion(_D2_INPUT_PORT), UserCommonDpGetMSTCapablePort());
            }

            break;
#endif

        default:
            break;
    }
}
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))

#if(_AUDIO_EARC_SUPPORT == _ON)
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
//--------------------------------------------------
// Description  : User eARC Tx Check CDS Capability Change
// Input Value  : pucCurrentArcTxEarcCdsAdb, pucCurrentArcTxEarcCdsSpkAdb
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserAdjustArcTxEarcCheckCdsCapChange(BYTE *pucCurrentArcTxEarcCdsAdb, BYTE *pucCurrentArcTxEarcCdsSpkAdb)
{
    WORD usDbLength = 0;
    WORD usChangeLength = 0;
    StructArcTxEarcCdsInfo stEarcRxCdsInfo;

    UserCommonArcTxEarcGetCdsInfo(&stEarcRxCdsInfo);

    usDbLength = stEarcRxCdsInfo.pucEarcCdsAdb[0] & 0x1F;

    if(memcmp(pucCurrentArcTxEarcCdsAdb, stEarcRxCdsInfo.pucEarcCdsAdb, sizeof(stEarcRxCdsInfo.pucEarcCdsAdb)) != 0)
    {
        memset(pucCurrentArcTxEarcCdsAdb, 0, sizeof(pucCurrentArcTxEarcCdsAdb));

        memcpy(pucCurrentArcTxEarcCdsAdb, stEarcRxCdsInfo.pucEarcCdsAdb, sizeof(stEarcRxCdsInfo.pucEarcCdsAdb));

        usChangeLength = usDbLength;
    }
    else
    {
        usChangeLength = 0;
    }

    if(memcmp(pucCurrentArcTxEarcCdsSpkAdb, stEarcRxCdsInfo.pucEarcCdsSpkAdb, 3) != 0)
    {
        memset(pucCurrentArcTxEarcCdsSpkAdb, 0, 4);

        memcpy(pucCurrentArcTxEarcCdsSpkAdb, stEarcRxCdsInfo.pucEarcCdsSpkAdb, 4);

        usChangeLength += 3;
    }

    /*usDbLength = stEarcRxCdsInfo.pucEarcCdsSpkLdb[0] & 0x1F;

    if(memcmp(pucCurrentEarcCdsSpkLdb, stEarcRxCdsInfo.pucEarcCdsSpkLdb, sizeof(stEarcRxCdsInfo.pucEarcCdsSpkLdb)) != 0)
    {
        memset(pucCurrentEarcCdsSpkLdb, 0, sizeof(pucCurrentEarcCdsSpkLdb));

        memcpy(pucCurrentEarcCdsSpkLdb, stEarcRxCdsInfo.pucEarcCdsSpkLdb, sizeof(stEarcRxCdsInfo.pucEarcCdsSpkLdb));

        usChangeLength += usDbLength;
    }

    usDbLength = stEarcRxCdsInfo.pucEarcCdsRcdb[0] & 0x1F;

    if(memcmp(pucCurrentEarcCdsRcdb, stEarcRxCdsInfo.pucEarcCdsRcdb, sizeof(stEarcRxCdsInfo.pucEarcCdsRcdb)) != 0)
    {
        memset(pucCurrentEarcCdsRcdb, 0, sizeof(pucCurrentEarcCdsRcdb));

        memcpy(pucCurrentEarcCdsRcdb, stEarcRxCdsInfo.pucEarcCdsRcdb, sizeof(stEarcRxCdsInfo.pucEarcCdsRcdb));

        usChangeLength += usDbLength;
    }*/

    if(usChangeLength > 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User eARC Tx CDS Audio Capability Initial
// Input Value  : pucCurrentArcTxEarcCdsAdb, pucCurrentArcTxEarcCdsSpkAdb
// Output Value : None
//--------------------------------------------------
void UserAdjustArcTxEarcCdsAudioCapabilityInitial(BYTE *pucCurrentArcTxEarcCdsAdb, BYTE *pucCurrentArcTxEarcCdsSpkAdb)
{
    StructArcTxEarcCdsInfo stEarcRxCdsInfo;

    memset(&stEarcRxCdsInfo, 0, sizeof(stEarcRxCdsInfo));

    UserCommonArcTxEarcGetCdsInfo(&stEarcRxCdsInfo);

    memset(pucCurrentArcTxEarcCdsAdb, 0, sizeof(pucCurrentArcTxEarcCdsAdb));
    memset(pucCurrentArcTxEarcCdsSpkAdb, 0, sizeof(pucCurrentArcTxEarcCdsSpkAdb));
    // memset(pucCurrentEarcCdsSpkLdb, 0, sizeof(pucCurrentEarcCdsSpkLdb));
    // memset(pucCurrentEarcCdsRcdb, 0, sizeof(pucCurrentEarcCdsRcdb));

    memcpy(pucCurrentArcTxEarcCdsAdb, stEarcRxCdsInfo.pucEarcCdsAdb, sizeof(stEarcRxCdsInfo.pucEarcCdsAdb));
    memcpy(pucCurrentArcTxEarcCdsSpkAdb, stEarcRxCdsInfo.pucEarcCdsSpkAdb, sizeof(stEarcRxCdsInfo.pucEarcCdsSpkAdb));
    // memset(pucCurrentEarcCdsSpkLdb, stEarcRxCdsInfo.pucEarcCdsSpkLdb, sizeof(stEarcRxCdsInfo.pucEarcCdsSpkLdb));
    // memset(pucCurrentEarcCdsRcdb, stEarcRxCdsInfo.pucEarcCdsRcdb, sizeof(stEarcRxCdsInfo.pucEarcCdsRcdb));
}
#endif // End of #if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif// #if(_OSD_TYPE == _REALTEK_2020_OSD)
