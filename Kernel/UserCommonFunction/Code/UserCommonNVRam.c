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
// ID Code      : UserCommonNVRam.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_NVRAM__

#include "UserCommonInclude.h"
#include "NVRam/UserCommonNVRam.h"

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#warning "NOTE: _WRITE_HDCP_TO_SYSTEM_EEPROM _ON!!"
#endif

#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
#warning "NOTE: _WRITE_EDID_TO_SYSTEM_EEPROM _ON!!"
#endif


//****************************************************************************
// CODE TABLES
//****************************************************************************
#ifdef _CUSTOM_SYSTEM_DEFAULT_DATA
StructSystemDataType code g_stNVRamSystemDefaultData = _CUSTOM_SYSTEM_DEFAULT_DATA;
#else
StructSystemDataType code g_stNVRamSystemDefaultData =
{
    _USER_DEFAULT_INPUT_PORT_0,        // BYTE b4SearchPort0
    _USER_DEFAULT_INPUT_PORT_1,        // BYTE b4SearchPort1

    _USER_DEFAULT_INPUT_PORT_2,        // BYTE b4SearchPort2
    _USER_DEFAULT_INPUT_PORT_3,        // BYTE b4SearchPort3

    _USER_DEFAULT_DISPLAY_MODE,        // BYTE ucDisplayMode
    0x00,                              // BYTE ucModeSlotIndex
    _DCLK_SPREAD_RANGE,                // BYTE ucSSC

    0x02,                              // BYTE b4HDMIHotPlugSupportTime
    _ON,                               // BYTE b1HDMIHotPlugSupport
    _USER_DEFAULT_AUTO_TARGET_INDEX,   // BYTE b2AutoTarget
    _ON,                               // BYTE b1DPHotPlugDCOffHigh

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    _USER_DEFAULT_SOURCE_SCAN_TYPE,    // BYTE b4SourceScanType
    _ON,                               // BYTE b1SourceHPAutoSearch
#else
    _USER_DEFAULT_SOURCE_SCAN_TYPE,    // BYTE b2SourceScanType
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    _SOURCE_BG_SWITCH_AUTO_WITHOUT_GROUP, // BYTE b1SourceBgScanType
#endif

    _D0_DP_MAIN_LINK_LANES,            // BYTE b3D0DpLanes;
    _D1_DP_MAIN_LINK_LANES,            // BYTE b3D1DpLanes;

    _D2_DP_MAIN_LINK_LANES,            // BYTE b3D2DpLanes;
    _D6_DP_MAIN_LINK_LANES,            // BYTE b3D6DpLanes;
    _DUAL_DP_EDID_5K3K_60HZ,           // BYTE b2DualDPEDIDSelect

    _ON,                               // BYTE b1PowerStatus
    _DP_EDID_1080P,                    // BYTE b3DPEDIDSelect
    _ON,                               // BYTE b1DPAuxDiffMode
    0,                                 // BYTE b4EdidD0

    0,                                 // WORD b4EdidD1
    0,                                 // WORD b4EdidD2
    0,                                 // WORD b4EdidD3
    0,                                 // WORD b4EdidD4
    0,                                 // WORD b4EdidD5
    _TRUE,                             // WORD b1ColorSeamlessChange

    75,                                // BYTE ucDpIrqTime_10us; (unit : 10us)
    0,                                 // BYTE b4EdidD6
    _OFF,                              // BYTE b1SyncDPIllegalIdlePatternCheck
    _DP_AUX_INITIAL_ADJR,              // BYTE b5DPAuxAdjrSetting
};
#endif

#if(_VGA_SUPPORT == _ON)
code StructAdcDataType g_stNVRamAdcRgbDefaultData =
{
    _ADC_RGB_DEFAULT_PGA_VALUE,
    {  _ADC_RGB_DEFAULT_RED_GAIN,   _ADC_RGB_DEFAULT_GREEN_GAIN,   _ADC_RGB_DEFAULT_BLUE_GAIN}, // Gain MSB
    {                       0x00,                          0x00,                         0x00}, // Gain LSB
    {_ADC_RGB_DEFAULT_RED_OFFSET, _ADC_RGB_DEFAULT_GREEN_OFFSET, _ADC_RGB_DEFAULT_BLUE_OFFSET}, // Offset MSB
    {                       0x00,                          0x00,                         0x00}, // Offset LSB
};


#if(_YPBPR_SUPPORT == _ON)
code StructAdcDataType g_stNVRamAdcYpbprDefaultData =
{
    _ADC_YPBPR_DEFAULT_PGA_VALUE,
    {_ADC_YPBPR_DEFAULT_PR_GAIN,     _ADC_YPBPR_DEFAULT_Y_GAIN,   _ADC_YPBPR_DEFAULT_PB_GAIN}, // Gain MSB
    {                       0x00,                         0x00,                         0x00}, // Gain LSB
    {_ADC_YPBPR_DEFAULT_PR_OFFSET, _ADC_YPBPR_DEFAULT_Y_OFFSET, _ADC_YPBPR_DEFAULT_PB_OFFSET}, // Offset MSB
    {                       0x00,                         0x00,                         0x00}, // Offset LSB
};
#endif

#endif  // End of #if(_VGA_SUPPORT == _ON)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSystemDataType g_stNVRamSystemData;

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
WORD g_pusFlashAddrArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
BYTE g_pucFlashPageArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get System Data Info
// Input Value  : enumDataType --> Data Type in StructSystemData
// Output Value : ucValue --> Value of the Input Data Type
//--------------------------------------------------
BYTE UserCommonNVRamGetSystemData(EnumSystemDataItemDataType enumDataType)
{
    BYTE ucValue = 0;

    switch(enumDataType)
    {
        case _MONITOR_POWER_STATUS:
            ucValue = (bit)(g_stNVRamSystemData.b1PowerStatus);
            break;

        case _DISPLAY_MODE:
            ucValue = g_stNVRamSystemData.ucDisplayMode;
            break;

        case _SEARCH_PORT_0:
            ucValue = g_stNVRamSystemData.b4SearchPort0;
            break;

        case _SEARCH_PORT_1:
            ucValue = g_stNVRamSystemData.b4SearchPort1;
            break;

        case _SEARCH_PORT_2:
            ucValue = g_stNVRamSystemData.b4SearchPort2;
            break;

        case _SEARCH_PORT_3:
            ucValue = g_stNVRamSystemData.b4SearchPort3;
            break;

        case _AUTO_SEARCH_TARGET:
            ucValue = g_stNVRamSystemData.b2AutoTarget;

            if(ucValue >= _MULTI_DISPLAY_MAX)
            {
                ucValue = 0;
            }
            break;

        case _SOURCE_SCAN_TYPE:
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
            ucValue = g_stNVRamSystemData.b4SourceScanType;
#else
            ucValue = g_stNVRamSystemData.b2SourceScanType;
#endif
            break;

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
        case _SOURCE_BG_SCAN_TYPE:
            ucValue = g_stNVRamSystemData.b1SourceBgScanType;
            break;
#endif

#if(_VGA_SUPPORT == _ON)
        case _MODE_SLOT_INDEX:
            ucValue = g_stNVRamSystemData.ucModeSlotIndex;
            break;
#endif

        case _SSC:
            ucValue = g_stNVRamSystemData.ucSSC;
            break;

        case _DP_HOT_PLUG_DC_OFF_HIGH:
            ucValue = g_stNVRamSystemData.b1DPHotPlugDCOffHigh;
            break;

        case _HDMI_HOT_PLUG_SUPPORT:
#if((_DIGITAL_PORT_SUPPORT == _ON) &&\
    ((_HDMI_FREESYNC_SUPPORT == _ON) || (_TMDS_HDCP_2_2_SUPPORT == _ON)))
            ucValue = _TRUE;
#else
            ucValue = g_stNVRamSystemData.b1HDMIHotPlugSupport;
#endif
            break;

        case _HDMI_HOT_PLUG_SUPPORT_TIME:
            ucValue = g_stNVRamSystemData.b4HDMIHotPlugSupportTime;

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_TMDS_HDCP_2_2_SUPPORT == _ON))
            if(ucValue == 0x00)
            {
                ucValue = 2;
            }
#endif
#endif
            break;

        case _DP_AUX_DIFF_MODE:
            ucValue = g_stNVRamSystemData.b1DPAuxDiffMode;
            break;

        case _DP_EDID_SELECT:
            ucValue = g_stNVRamSystemData.b3DPEDIDSelect;
            break;
        case _DUAL_DP_EDID_SELECT:
            ucValue = g_stNVRamSystemData.b2DualDPEDIDSelect;
            break;

        case _DP_AUX_ADJR_SETTING:
            ucValue = g_stNVRamSystemData.b5DPAuxAdjrSetting;
            break;

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _DP_D0_LANES:
            ucValue = g_stNVRamSystemData.b3D0DpLanes;
            break;
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _DP_D1_LANES:
            ucValue = g_stNVRamSystemData.b3D1DpLanes;
            break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _DP_D2_LANES:
            ucValue = g_stNVRamSystemData.b3D2DpLanes;
            break;
#endif
        case _EDID_D0_SELECT:
            ucValue = g_stNVRamSystemData.b4EdidD0;
            break;
        case _EDID_D1_SELECT:
            ucValue = g_stNVRamSystemData.b4EdidD1;
            break;
        case _EDID_D2_SELECT:
            ucValue = g_stNVRamSystemData.b4EdidD2;
            break;
        case _EDID_D3_SELECT:
            ucValue = g_stNVRamSystemData.b4EdidD3;
            break;
        case _EDID_D4_SELECT:
            ucValue = g_stNVRamSystemData.b4EdidD4;
            break;
        case _EDID_D5_SELECT:
            ucValue = g_stNVRamSystemData.b4EdidD5;
            break;
        case _EDID_D6_SELECT:
            ucValue = g_stNVRamSystemData.b4EdidD6;
            break;

        case _COLORIMETRY_SEAMLESS_CHANGE:
            ucValue = g_stNVRamSystemData.b1ColorSeamlessChange;
            break;

        case _DP_IRQ_TIME:
            ucValue = g_stNVRamSystemData.ucDpIrqTime_10us;
            break;

        case _DP_ILLEGAL_IDLE_PATTERN_CHECK:
            ucValue = g_stNVRamSystemData.b1SyncDPIllegalIdlePatternCheck;
            break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        case _SOURCE_HP_AUTO_SEARCH:
            ucValue = g_stNVRamSystemData.b1SourceHPAutoSearch;
            break;
#endif

        default:
            break;
    }

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    if(UserCommonQCGetEnableStatus() == _TRUE)
    {
        // Over-write system data in QC
        return UserCommonQCNVRamGetData(enumDataType, ucValue);
    }
#endif

    return ucValue;
}

//--------------------------------------------------
// Description  : Set System Data Info
// Input Value  : enumDataType --> Data Type in StructSystemData
//                ucValue --> Value to be set for the Input Data Type
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamSetSystemData(EnumSystemDataItemDataType enumDataType, BYTE ucValue)
{
    switch(enumDataType)
    {
        case _MONITOR_POWER_STATUS:
            g_stNVRamSystemData.b1PowerStatus = (bit)ucValue;
            break;

        case _DISPLAY_MODE:
            g_stNVRamSystemData.ucDisplayMode = ucValue;
            break;

        case _SEARCH_PORT_0:
            g_stNVRamSystemData.b4SearchPort0 = ucValue;
            break;

        case _SEARCH_PORT_1:
            g_stNVRamSystemData.b4SearchPort1 = ucValue;
            break;

        case _SEARCH_PORT_2:
            g_stNVRamSystemData.b4SearchPort2 = ucValue;
            break;

        case _SEARCH_PORT_3:
            g_stNVRamSystemData.b4SearchPort3 = ucValue;
            break;

        case _AUTO_SEARCH_TARGET:
            g_stNVRamSystemData.b2AutoTarget = ucValue;
            break;

        case _SOURCE_SCAN_TYPE:

            if(ucValue == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
            {
                ucValue = _SOURCE_SWITCH_FIXED_PORT;
            }
            else if(ucValue == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
            {
                ucValue = _SOURCE_SWITCH_AUTO_IN_GROUP;
            }

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
            g_stNVRamSystemData.b4SourceScanType = ucValue;
#else
            g_stNVRamSystemData.b2SourceScanType = ucValue;
#endif

            break;

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
        case _SOURCE_BG_SCAN_TYPE:
            g_stNVRamSystemData.b1SourceBgScanType = ucValue;
            break;
#endif

#if(_VGA_SUPPORT == _ON)
        case _MODE_SLOT_INDEX:
            g_stNVRamSystemData.ucModeSlotIndex = ucValue;
            break;
#endif
        case _EDID_D0_SELECT:
            g_stNVRamSystemData.b4EdidD0 = ucValue;
            break;
        case _EDID_D1_SELECT:
            g_stNVRamSystemData.b4EdidD1 = ucValue;
            break;
        case _EDID_D2_SELECT:
            g_stNVRamSystemData.b4EdidD2 = ucValue;
            break;
        case _EDID_D3_SELECT:
            g_stNVRamSystemData.b4EdidD3 = ucValue;
            break;
        case _EDID_D4_SELECT:
            g_stNVRamSystemData.b4EdidD4 = ucValue;
            break;
        case _EDID_D5_SELECT:
            g_stNVRamSystemData.b4EdidD5 = ucValue;
            break;
        case _EDID_D6_SELECT:
            g_stNVRamSystemData.b4EdidD6 = ucValue;
            break;

        case _SSC:
            g_stNVRamSystemData.ucSSC = ucValue;
            break;

        case _DP_HOT_PLUG_DC_OFF_HIGH:
            g_stNVRamSystemData.b1DPHotPlugDCOffHigh = ucValue;

#if(_DIGITAL_PORT_SUPPORT == _ON)
            if(g_stNVRamSystemData.b1DPHotPlugDCOffHigh == _TRUE)
            {
                SET_DP_DC_OFF_HPD_HIGH();
            }
            else
            {
                CLR_DP_DC_OFF_HPD_HIGH();
            }
#endif
            break;

        case _HDMI_HOT_PLUG_SUPPORT:
            g_stNVRamSystemData.b1HDMIHotPlugSupport = ucValue;

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_TMDS_HDCP_2_2_SUPPORT == _ON))
            SET_HDMI_HOTPLUG_TOGGLE();
#else
            if(g_stNVRamSystemData.b1HDMIHotPlugSupport == _TRUE)
            {
                SET_HDMI_HOTPLUG_TOGGLE();
            }
            else
            {
                CLR_HDMI_HOTPLUG_TOGGLE();
            }
#endif
#endif
            break;

        case _HDMI_HOT_PLUG_SUPPORT_TIME:
            g_stNVRamSystemData.b4HDMIHotPlugSupportTime = ucValue;

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_TMDS_HDCP_2_2_SUPPORT == _ON))
            if(g_stNVRamSystemData.b4HDMIHotPlugSupportTime != 0x00)
            {
                SET_HDMI_HOTPLUG_TIME(g_stNVRamSystemData.b4HDMIHotPlugSupportTime);
            }
            else
            {
                // Default HPD TOGGLE TIME is 200ms
                SET_HDMI_HOTPLUG_TIME(2);
            }
#endif
#endif
            break;

        case _DP_AUX_DIFF_MODE:

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _TRUE)
            g_stNVRamSystemData.b1DPAuxDiffMode = ucValue;
#else
            g_stNVRamSystemData.b1DPAuxDiffMode = _TRUE;
#endif

#if(_DP_SUPPORT == _ON)
            if(g_stNVRamSystemData.b1DPAuxDiffMode == _TRUE)
            {
                SET_DP_AUX_DIFF_MODE();
            }
            else
            {
                CLR_DP_AUX_DIFF_MODE();
            }
#endif
            break;

        case _DP_AUX_ADJR_SETTING:

            g_stNVRamSystemData.b5DPAuxAdjrSetting = ucValue;

#if(_DP_SUPPORT == _ON)
            SET_DP_AUX_ADJR_SETTING(g_stNVRamSystemData.b5DPAuxAdjrSetting);
#endif
            break;

        case _DP_EDID_SELECT:
            g_stNVRamSystemData.b3DPEDIDSelect = ucValue;

            g_stNVRamSystemData.b4EdidD0 = ucValue;
            g_stNVRamSystemData.b4EdidD1 = ucValue;
            g_stNVRamSystemData.b4EdidD6 = ucValue;
            break;

        case _DUAL_DP_EDID_SELECT:
            g_stNVRamSystemData.b2DualDPEDIDSelect = ucValue;
            break;

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _DP_D0_LANES:
            g_stNVRamSystemData.b3D0DpLanes = ucValue;
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _DP_D1_LANES:
            g_stNVRamSystemData.b3D1DpLanes = ucValue;
            break;
#endif

        case _COLORIMETRY_SEAMLESS_CHANGE:
            g_stNVRamSystemData.b1ColorSeamlessChange = ucValue;

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
            if(ucValue == _ON)
            {
                CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
            }
            else
#endif
            {
                SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
            }
#endif
            break;

        case _DP_IRQ_TIME:

            g_stNVRamSystemData.ucDpIrqTime_10us = ucValue;

#if(_DP_SUPPORT == _ON)
            SET_DP_IRQ_TIME_10US(g_stNVRamSystemData.ucDpIrqTime_10us);
#endif

            break;

        case _DP_ILLEGAL_IDLE_PATTERN_CHECK:
            g_stNVRamSystemData.b1SyncDPIllegalIdlePatternCheck = ucValue;

#if(_DP_SUPPORT == _ON)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
            if(g_stNVRamSystemData.b1SyncDPIllegalIdlePatternCheck == _ON)
            {
                SET_DP_ILLEGAL_IDLE_PATTERN_CHECK();
            }
            else
#endif
            {
                CLR_DP_ILLEGAL_IDLE_PATTERN_CHECK();
            }
#endif

            break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        case _SOURCE_HP_AUTO_SEARCH:
            g_stNVRamSystemData.b1SourceHPAutoSearch = ucValue;
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get System Data Info
// Input Value  : enumDataType --> Data Type in StructSystemData
// Output Value : ucValue --> Value of the Input Data Type
//--------------------------------------------------
EnumSystemDataItemDataType UserCommonNVRamGetRegionPortItem(EnumDisplayRegion enumDisplayRegion)
{
    switch(ScalerRegionGetIndex(enumDisplayRegion))
    {
        default:
        case _REGION_INDEX_0:
            return _SEARCH_PORT_0;
        case _REGION_INDEX_1:
            return _SEARCH_PORT_1;
        case _REGION_INDEX_2:
            return _SEARCH_PORT_2;
        case _REGION_INDEX_3:
            return _SEARCH_PORT_3;
    }
}

//--------------------------------------------------
// Description  : Get System Data Info
// Input Value  : enumDataType --> Data Type in StructSystemData
// Output Value : ucValue --> Value of the Input Data Type
//--------------------------------------------------
EnumInputPort UserCommonNVRamGetSystemRegionPortData(EnumDisplayRegion enumDisplayRegion)
{
    return (EnumInputPort)UserCommonNVRamGetSystemData(UserCommonNVRamGetRegionPortItem(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Set System Data Info
// Input Value  : enumDataType --> Data Type in StructSystemData
//                ucValue --> Value to be set for the Input Data Type
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamSetSystemRegionPortData(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort)
{
    UserCommonNVRamSetSystemData(UserCommonNVRamGetRegionPortItem(enumDisplayRegion), enumInputPort);
}

//--------------------------------------------------
// Description  : Read data to the NVRAM
// Input Value  : usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonNVRamRead(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    return UserCommonEepromRead(usSubAddr, usLength, pucReadArray);
#else
    return UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Save system data to NVRAM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamSaveSystemData(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromSaveSystemData();
#else
    UserCommonFlashSaveSystemData();
#endif
}

//--------------------------------------------------
// Description  : Load system data from NVRAM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamLoadSystemData(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromLoadSystemData();
#else
    UserCommonFlashLoadSystemData();
#endif
}

//--------------------------------------------------
// Description  : Restore default system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreSystemData(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRestoreSystemData();
#else
    UserCommonFlashRestoreSystemData();
#endif
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load mode user data from NVRAM
// Input Value  : ucSlotIndex
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamLoadModeUserData(BYTE ucSlotIndex)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromLoadModeUserData(ucSlotIndex);
#else
    UserCommonFlashLoadModeUserData(ucSlotIndex);
#endif
}
//--------------------------------------------------
// Description  : Save mode user data to NVRAM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamSaveModeUserData(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromSaveModeUserData();
#else
    UserCommonFlashSaveModeUserData();
#endif
}

//--------------------------------------------------
// Description  : Load mode user Mode Number data from NVRAM
// Input Value  : ucSlotIndex
// Output Value : Mode Number
//--------------------------------------------------
BYTE UserCommonNVRamLoadModeUserModeNumberData(BYTE ucSlotIndex)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    return UserCommonEepromLoadModeUserModeNumberData(ucSlotIndex);
#else
    return UserCommonFlashLoadModeUserModeNumberData(ucSlotIndex);
#endif
}

//--------------------------------------------------
// Description  : Restore default mode user data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreModeUserData(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRestoreModeUserData();
#else
    UserCommonFlashRestoreModeUserData();
#endif
}

//--------------------------------------------------
// Description  : Increase VGA Fifo mode index
// Input Value  : None
// Output Value : FIFO Mode Current Index
//--------------------------------------------------
BYTE UserCommonNVRamVGAFifoModeIndexOffsetInc(BYTE ucStep)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    return UserCommonEepromVGAFifoModeIndexOffsetInc(ucStep);
#else
    return UserCommonFlashVGAFifoModeIndexOffsetInc(ucStep);
#endif
}

//--------------------------------------------------
// Description  : Get VGA FIFO Mode Maximum No.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonNVRamGetMaxFifoGroupCnt(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    return UserCommonEepromGetMaxFifoGroupCnt();
#else
    return UserCommonFlashGetMaxFifoGroupCnt();
#endif
}

//--------------------------------------------------
// Description  : Save adc settings to NVRAM
// Input Value  : ucADCConfig
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamSaveADCSetting(EnumColorSpace enumColorFormat)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromSaveADCSetting(enumColorFormat);
#else
    UserCommonFlashSaveADCSetting(enumColorFormat);
#endif
}

//--------------------------------------------------
// Description  : Load adc settings from NVRAM
// Input Value  : ucADCConfig
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamLoadADCSetting(EnumColorSpace enumColorFormat)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromLoadADCSetting(enumColorFormat);
#else
    UserCommonFlashLoadADCSetting(enumColorFormat);
#endif
}

//--------------------------------------------------
// Description  : Restore default adc settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreADCSetting(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRestoreADCSetting();
#else
    UserCommonFlashRestoreADCSetting();
#endif
}
#endif // End of #if(_VGA_SUPPORT == _ON)

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetHDCPKeyBKsv(ucSubAddr, ucLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetHDCPKeyBKsv(ucSubAddr, ucLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetHDCPKey(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetHDCPKey(usSubAddr, usLength, pucReadArray);
#endif
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    usOffset = usOffset;
    ucLength = ucLength;
    pucBuf = pucBuf;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromRestoreHDCP1P4(usOffset, ucLength, pucBuf);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashRestoreHDCP1P4(usOffset, ucLength, pucBuf);
#endif
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Aksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetTxHDCPKeyAKsv(ucSubAddr, ucLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetTxHDCPKeyAKsv(ucSubAddr, ucLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get TxHDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetTxHDCPKey(usSubAddr, usLength, pucReadArray);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetTxHDCPKey(usSubAddr, usLength, pucReadArray);
#endif
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    usOffset = usOffset;
    ucLength = ucLength;
    pucBuf = pucBuf;

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromRestoreTxHDCP1P4(usOffset, ucLength, pucBuf);
#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashRestoreTxHDCP1P4(usOffset, ucLength, pucBuf);
#endif
}
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetHdcp2Certrx(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetHdcp2Certrx(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetHdcp2RSADkey(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetHdcp2RSADkey(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetHdcp2RSARRModN(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetHdcp2RSARRModN(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetHdcp2RSAKPriv(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetHdcp2RSAKPriv(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetHdcp2RSANpinv(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetHdcp2RSANpinv(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetHdcp2LCKey(usSubAddr, usLength, pucReadArray);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetHdcp2LCKey(usSubAddr, usLength, pucReadArray);
#endif
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    usOffset = usOffset;
    ucLength = ucLength;
    pucBuf = pucBuf;

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromRestoreHDCP2(usOffset, ucLength, pucBuf);
#elif(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashRestoreHDCP2(usOffset, ucLength, pucBuf);
#endif
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetTxHdcp2RRMODN(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetTxHdcp2RRMODN(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetTxHdcp2DcpLlcN(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetTxHdcp2DcpLlcN(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetTxHdcp2EKey(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetTxHdcp2EKey(usSubAddr, usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromGetTxHdcp2NPinv(usSubAddr, usLength, pucReadArray);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashGetTxHdcp2NPinv(usSubAddr, usLength, pucReadArray);
#endif
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreTxHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    usOffset = usOffset;
    ucLength = ucLength;
    pucBuf = pucBuf;

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
    UserCommonEepromRestoreTxHDCP2(usOffset, ucLength, pucBuf);
#elif(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
    UserCommonFlashRestoreTxHDCP2(usOffset, ucLength, pucBuf);
#endif
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data to the External EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonEepromIICRead(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    ucSWIICStatus = ucSWIICStatus;

    while(ulLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0x0000FF00) >> 7);
        }
        else if(ucSubAddrLength == 2)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0x00FF0000) >> 15);
        }

        // Receive 24 bytes each time
        ucDataCnt = _EEPROM_READ_SIZE;

        // Check if more than 24 bytes are needed to be received
        if(ulLength > ucDataCnt)
        {
            ulLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = ulLength;
            ulLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            if(ScalerMcuIICRead(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucReadArray) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICRead(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucReadArray, ucHwIICPinNum) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        ulSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the System EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
//                enumWriteSize --> 8 or 16 or 32
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------

bit UserCommonEepromIICWrite(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE ucTimeOutCnt = _EEPROM_TIMEOUT_LIMIT;
    BYTE pucTempData[32];

    ucSWIICStatus = ucSWIICStatus;

    if(ulLength == 0)
    {
        return _FAIL;
    }

    while(ulLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0xFF00) >> 7);
        }
        else if(ucSubAddrLength == 2)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0x00FF0000) >> 15);
        }

        // Transmit 8, 16 or 32 bytes each time
        ucDataCnt = enumWriteSize;

        // Check if more than 8, 16 or 32 bytes are needed to be transmitted
        if(enumWriteSize == _WRITE_SIZE_32)
        {
            if(((ulSubAddr & 0x001F) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x001F);
            }
        }
        else if(enumWriteSize == _WRITE_SIZE_16)
        {
            if(((ulSubAddr & 0x000F) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x000F);
            }
        }
        else if(enumWriteSize == _WRITE_SIZE_8)
        {
            if(((ulSubAddr & 0x0007) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x0007);
            }
        }

        if(ulLength > ucDataCnt)
        {
            ulLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = ulLength;
            ulLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Disable EEPROM Write Protect
        PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);

        // Execute Hardware IIC Write Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            if(ScalerMcuIICWrite(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucTempData) == _FAIL)
            {
                // Enable EEPROM Write Protect
                PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICWrite(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucTempData, ucHwIICPinNum) == _FAIL)
            {
                // Enable EEPROM Write Protect
                PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        // Increment Sub-Addr for next Write
        ulSubAddr += ucDataCnt;

        // Need to delay until internal write cycle is finished
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            while(ScalerMcuIICWritePolling(ucSlaveAddress) == _FAIL)
            {
                ucTimeOutCnt--;

                ScalerMcuDelay5us();

                if(ucTimeOutCnt == 0x00)
                {
                    // Enable EEPROM Write Protect
                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                    return _FAIL;
                }
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            while(ScalerMcuHwIICWritePolling(ucSlaveAddress, ucSubAddrLength, ucHwIICPinNum) == _FAIL)
            {
                ucTimeOutCnt--;

                ScalerMcuDelay5us();

                if(ucTimeOutCnt == 0x00)
                {
                    // Enable EEPROM Write Protect
                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                    return _FAIL;
                }
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        ucTimeOutCnt = _EEPROM_TIMEOUT_LIMIT;

        // Enable EEPROM Write Protect
        PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
    }
    return _SUCCESS;
}


#endif // End of #if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Read data to the System EEPROM by IIC
// Input Value  : usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonEepromRead(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
    ulSubAddr = ulSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)

    if(UserInterfaceNVRamSystemEepromReadCustomProc(ulSubAddr, usLength, pucReadArray) != _CHECK_SUCCESS)
    {
        return _FAIL;
    }

#else

    if(ulSubAddr > _EEPROM_SIZE_RANGE)
    {
        return _FAIL;
    }

    // Execute Hardware IIC Read Command
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
    if(UserCommonEepromIICRead(_EEPROM_SLAVE_ADDRESS, ulSubAddr, 1, usLength, pucReadArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC) == _FAIL)
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
    if(UserCommonEepromIICRead(_EEPROM_SLAVE_ADDRESS, ulSubAddr, 2, usLength, pucReadArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC) == _FAIL)
#endif

    {
        return _FAIL;
    }

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN)   // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
    if(UserCommonEepromIICRead(_EEPROM_SLAVE_ADDRESS, ulSubAddr, 1, usLength, pucReadArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC) == _FAIL)
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
    if(UserCommonEepromIICRead(_EEPROM_SLAVE_ADDRESS, ulSubAddr, 2, usLength, pucReadArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC) == _FAIL)
#endif

    {
        return _FAIL;
    }
#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#endif // End of #if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the System EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------

bit UserCommonEepromWrite(DWORD ulSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    ulSubAddr = ulSubAddr;
    usLength = usLength;
    pucWriteArray = pucWriteArray;

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)

    if(UserInterfaceNVRamSystemEepromWriteCustomProc(ulSubAddr, usLength, pucWriteArray) == _CHECK_SUCCESS)
    {
        return _FAIL;
    }

#else
    if(ulSubAddr > _EEPROM_SIZE_RANGE)
    {
        return _FAIL;
    }

    // Execute Hardware IIC Write Command
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
    if(UserCommonEepromIICWrite(_EEPROM_SLAVE_ADDRESS, ulSubAddr, 1, usLength, pucWriteArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC, _WRITE_SIZE_16) == _FAIL)
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
    if(UserCommonEepromIICWrite(_EEPROM_SLAVE_ADDRESS, ulSubAddr, 2, usLength, pucWriteArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC, _WRITE_SIZE_32) == _FAIL)
#endif

    {
        return _FAIL;
    }

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN)   // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
    if(UserCommonEepromIICWrite(_EEPROM_SLAVE_ADDRESS, ulSubAddr, 1, usLength, pucWriteArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC, _WRITE_SIZE_16) == _FAIL)
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
    if(UserCommonEepromIICWrite(_EEPROM_SLAVE_ADDRESS, ulSubAddr, 2, usLength, pucWriteArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC, _WRITE_SIZE_32) == _FAIL)
#endif
    {
        return _FAIL;
    }
#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#endif // End of #if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)

    return _SUCCESS;
}


//--------------------------------------------------
// Description  : Save system data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromSaveSystemData(void)
{
    if(UserInterfaceNVRamGetDataStatus(_CHECK_SYSTEM_DATA_SAVE) == _CHECK_FAIL)
    {
        return;
    }

    UserCommonEepromWrite(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), (BYTE *)(&g_stNVRamSystemData));
}

//--------------------------------------------------
// Description  : Load system data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromLoadSystemData(void)
{
    UserCommonEepromRead(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), (BYTE *)(&g_stNVRamSystemData));

    UserInterfaceNVRamGetDataStatus(_CHECK_SYSTEM_DATA_LOAD);
}

//--------------------------------------------------
// Description  : Restore default system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreSystemData(void)
{
    g_stNVRamSystemData = g_stNVRamSystemDefaultData;
    UserCommonEepromSaveSystemData();
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load mode user data from EEPROM
// Input Value  : ucSlotIndex
// Output Value : None
//--------------------------------------------------
void UserCommonEepromLoadModeUserData(DWORD ulSlotIndex)
{
    UserCommonEepromRead((DWORD)_MODE_USER_DATA_ADDRESS + (ulSlotIndex % _MODE_SLOT_AMOUNT) * sizeof(StructVgaModeUserDataType),
                         sizeof(StructVgaModeUserDataType),
                         (BYTE *)(&g_stVgaModeUserData));

    UserInterfaceNVRamGetDataStatus(_CHECK_MODE_USER_DATA_LOAD);
}

//--------------------------------------------------
// Description  : Save mode user data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromSaveModeUserData(void)
{
    BYTE ucFIFOInx = 0;
    BYTE ucSlotIndex = UserCommonEepromGetMaxFifoGroupCnt() + 1;

    if(UserInterfaceNVRamGetDataStatus(_CHECK_MODE_USER_DATA_SAVE) == _CHECK_FAIL)
    {
        return;
    }

    for(ucFIFOInx = 0; ucFIFOInx < UserCommonEepromGetMaxFifoGroupCnt(); ucFIFOInx++)
    {
        if(UserCommonEepromLoadModeUserModeNumberData(ucFIFOInx) == g_stVgaModeUserData.ucModeNumber)
        {
            ucSlotIndex = ucFIFOInx;
            break;
        }
    }

    if(ucSlotIndex == (UserCommonEepromGetMaxFifoGroupCnt() + 1))
    {
        // Add FIFO mode index number by step
        ucSlotIndex = UserCommonEepromVGAFifoModeIndexOffsetInc(1);
    }

    UserCommonEepromWrite(_MODE_USER_DATA_ADDRESS + (ucSlotIndex % _MODE_SLOT_AMOUNT) * sizeof(StructVgaModeUserDataType),
                          sizeof(StructVgaModeUserDataType),
                          (BYTE *)(&g_stVgaModeUserData));
}

//--------------------------------------------------
// Description  : Load mode user Mode Number data from EEPROM
// Input Value  : ucSlotIndex
// Output Value : Mode Number
//--------------------------------------------------
BYTE UserCommonEepromLoadModeUserModeNumberData(DWORD ulSlotIndex)
{
    BYTE ucModeNumber = 0xFF;

    UserCommonEepromRead((DWORD)_MODE_USER_DATA_ADDRESS + (ulSlotIndex % _MODE_SLOT_AMOUNT) * sizeof(StructVgaModeUserDataType) + 1,
                         1, &ucModeNumber);

    return ucModeNumber;
}
//--------------------------------------------------
// Description  : Restore default mode user data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreModeUserData(void)
{
    StructVgaModeUserDataType stVGAModeUserData;

    // g_stVgaModeUserData will be clear
    memset(&stVGAModeUserData, 0xFF, sizeof(StructVgaModeUserDataType));

    for(g_stNVRamSystemData.ucModeSlotIndex = 0; g_stNVRamSystemData.ucModeSlotIndex < _MODE_SLOT_AMOUNT; g_stNVRamSystemData.ucModeSlotIndex++)
    {
        UserCommonEepromWrite(_MODE_USER_DATA_ADDRESS + (g_stNVRamSystemData.ucModeSlotIndex * sizeof(StructVgaModeUserDataType)),
                              sizeof(StructVgaModeUserDataType), (BYTE *)(&stVGAModeUserData));
    }

    g_stNVRamSystemData.ucModeSlotIndex = 0;
}

//--------------------------------------------------
// Description  : Increase VGA Fifo mode index
// Input Value  : None
// Output Value : FIFO Mode Current Index
//--------------------------------------------------
BYTE UserCommonEepromVGAFifoModeIndexOffsetInc(BYTE ucStep)
{
    StructVgaModeUserDataType stVGAModeUserData;
    BYTE ucMNumber = 0xFF;
    BYTE ucInx = 0;

    // g_stVgaModeUserData will be clear
    memset(&stVGAModeUserData, 0xFF, sizeof(StructVgaModeUserDataType));

    for(ucInx = 0; ucInx < _MODE_SLOT_AMOUNT; ucInx++)
    {
        g_stNVRamSystemData.ucModeSlotIndex = (g_stNVRamSystemData.ucModeSlotIndex + ucStep) % _MODE_SLOT_AMOUNT;

        ucMNumber = UserCommonEepromLoadModeUserModeNumberData(g_stNVRamSystemData.ucModeSlotIndex);

        if(UserCommonModeSearchCheckPresetModeTable(ucMNumber) == _TRUE)
        {
            UserCommonEepromRead(_MODE_USER_DATA_ADDRESS + (g_stNVRamSystemData.ucModeSlotIndex) * sizeof(StructVgaModeUserDataType),
                                 1, (BYTE *)(&stVGAModeUserData));

            if(stVGAModeUserData.b1IsPresetMode == _PRESET_MODE_TYPE)
            {
                DebugMessageAnalog("4. Match presetmode", ucMNumber);

                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return g_stNVRamSystemData.ucModeSlotIndex;
}

//--------------------------------------------------
// Description  : Get VGA FIFO Mode Maximum No.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonEepromGetMaxFifoGroupCnt(void)
{
    return _MODE_SLOT_AMOUNT;
}

//--------------------------------------------------
// Description  : Load adc settings from EEPROM
// Input Value  : ucADCConfig
// Output Value : None
//--------------------------------------------------
void UserCommonEepromLoadADCSetting(EnumColorSpace enumColorFormat)
{
    if(enumColorFormat == _COLOR_SPACE_RGB)

    {
        UserCommonEepromRead(_ADC_SETTING_ADDRESS, sizeof(StructAdcDataType),
                             &g_stVgaAdcData.ucAdcPGA);
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        UserCommonEepromRead(_ADC_SETTING_ADDRESS + sizeof(StructAdcDataType),
                             sizeof(StructAdcDataType),
                             &g_stVgaAdcData.ucAdcPGA);
    }
#endif

    UserInterfaceNVRamGetDataStatus(_CHECK_ADC_LOAD);
}

//--------------------------------------------------
// Description  : Save adc settings to EEPROM
// Input Value  : ucADCConfig
// Output Value : None
//--------------------------------------------------
void UserCommonEepromSaveADCSetting(EnumColorSpace enumColorFormat)
{
    if(UserInterfaceNVRamGetDataStatus(_CHECK_ADC_SAVE) == _CHECK_FAIL)
    {
        return;
    }

    if(enumColorFormat == _COLOR_SPACE_RGB)
    {
        UserCommonEepromWrite(_ADC_SETTING_ADDRESS, sizeof(StructAdcDataType),
                              &g_stVgaAdcData.ucAdcPGA);
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        UserCommonEepromWrite(_ADC_SETTING_ADDRESS + sizeof(StructAdcDataType),
                              sizeof(StructAdcDataType),
                              &g_stVgaAdcData.ucAdcPGA);
    }
#endif
}

//--------------------------------------------------
// Description  : Restore default adc settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreADCSetting(void)
{
    g_stVgaAdcData = g_stNVRamAdcRgbDefaultData;

    UserCommonEepromSaveADCSetting(_COLOR_SPACE_RGB);

#if(_YPBPR_SUPPORT == _ON)
    g_stVgaAdcData = g_stNVRamAdcYpbprDefaultData;
    UserCommonEepromSaveADCSetting(_COLOR_SPACE_YPBPR);
#endif
}
#endif // End of #if(_VGA_SUPPORT == _ON)


#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Load one iterm from flash
// Input Value  : enumItemID: flash item id
//                pucData: buf to save data loaded
//                ucLength: buf length
// Output Value : return _TRUE if load success, else return _FALSE
//--------------------------------------------------
bit UserCommonFlashLoadItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength)
{
    BYTE ucItemChecksum = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usItemAddr = 0;
    BYTE pucDataArry[_DATA_ITEM_LENGTH] = {0};
    BYTE ucPageID = HIBYTE(enumItemID);

    if(ucLength > (_DATA_ITEM_LENGTH - 2))
    {
        return _FALSE;
    }

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the data item which item index is ucIndex in the ucPage page from bottom to top
    for(usAddrIndex = g_pusFlashAddrArr[ucPageID]; usAddrIndex > 0; usAddrIndex--)
    {
        usItemAddr = (usAddrIndex - 1) * _DATA_ITEM_LENGTH;

        // If data item index matches
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, 1, pucDataArry);
        if(pucDataArry[0] == LOBYTE(enumItemID))
        {
            ucItemChecksum = 0;

            // Calculate the checksum of the data item
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, _DATA_ITEM_LENGTH, pucDataArry);
            ucItemChecksum = UserCommonFlashCalculateCheckSumData(pucDataArry, (_DATA_ITEM_LENGTH - 1));
            ucItemChecksum = (ucItemChecksum & 0x7F);

            // Check checksum value matches or not
            if(pucDataArry[_DATA_ITEM_LENGTH - 1] != ucItemChecksum)
            {
                return _FALSE;
            }

            // Load the found data item to the buffer
            memcpy(pucData, pucDataArry + 1, ucLength);

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Save one iterm to flash
// Input Value  : enumItemID: flash item id
//                pucData: data to save
//                ucLength: buf length
// Output Value : return _TRUE if save success, else return _FALSE
//--------------------------------------------------

bit UserCommonFlashSaveItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength)
{
    bit bNeedSave = _TRUE;
    BYTE ucItemIndex = 0;
    BYTE ucChecksum = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usItemAddr = 0;
    BYTE pucDataArry[_DATA_ITEM_LENGTH] = {0};
    BYTE pucWholeItem[_DATA_ITEM_LENGTH] = {0};
    BYTE ucPageID = HIBYTE(enumItemID);

    if(ucLength > (_DATA_ITEM_LENGTH - 2))
    {
        return _FALSE;
    }

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Check all saved items
    for(usAddrIndex = g_pusFlashAddrArr[ucPageID]; usAddrIndex > 0; usAddrIndex--)
    {
        usItemAddr = (usAddrIndex - 1) * _DATA_ITEM_LENGTH;

        // Check item ID index and item checksum to make sure that this item which has the same ID index is valid
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, 1, pucDataArry);
        if(pucDataArry[0] == LOBYTE(enumItemID))
        {
            ucChecksum = 0;

            // Calculate the item checksum
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, _DATA_ITEM_LENGTH, pucDataArry);
            ucChecksum = UserCommonFlashCalculateCheckSumData(pucDataArry, (_DATA_ITEM_LENGTH - 1));
            ucChecksum = (ucChecksum & 0x7F);

            // Compare the calculate checksum and flash data
            if(ucChecksum == pucDataArry[_DATA_ITEM_LENGTH - 1])
            {
                // Check data item in buffer is equal to the existed data item in page or not
                for(ucItemIndex = 0; ucItemIndex < ucLength; ucItemIndex++)
                {
                    if(pucDataArry[ucItemIndex + 1] != pucData[ucItemIndex])
                    {
                        break;
                    }
                }

                // Same item has been saved last time
                if(ucItemIndex >= ucLength)
                {
                    bNeedSave = _FALSE;
                }

                break;
            }
        }
    }

    // Same item is saved last time, do not need save again here
    if(bNeedSave == _FALSE)
    {
        return _TRUE;
    }

    // Get the whole item
    memset(pucWholeItem, 0xFFU, _DATA_ITEM_LENGTH);
    pucWholeItem[0] = LOBYTE(enumItemID);
    memcpy(pucWholeItem + 1, pucData, ucLength);
    pucWholeItem[_DATA_ITEM_LENGTH - 1] = 0x00;
    pucWholeItem[_DATA_ITEM_LENGTH - 1] = UserCommonFlashCalculateCheckSumData(pucWholeItem, (_DATA_ITEM_LENGTH - 1));
    pucWholeItem[_DATA_ITEM_LENGTH - 1] = (pucWholeItem[_DATA_ITEM_LENGTH - 1] & 0x7F);

    // Find an available Item space address which is 0xFF for Item all fields
    // Use this mechanism to avoid save Item to the wrong address which update data exception happens
    for(usAddrIndex = g_pusFlashAddrArr[ucPageID]; usAddrIndex <= ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usAddrIndex++)
    {
        if(usAddrIndex == ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH))
        {
            UserInterfaceFlashMoveData(ucPageID, pucWholeItem);
            return _TRUE;
        }

        usItemAddr = usAddrIndex * _DATA_ITEM_LENGTH;

        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, _DATA_ITEM_LENGTH, pucDataArry);
        for(ucItemIndex = 0; ucItemIndex < _DATA_ITEM_LENGTH; ucItemIndex++)
        {
            if((pucDataArry[ucItemIndex]) != 0xFF)
            {
                break;
            }
        }

        if(ucItemIndex >= _DATA_ITEM_LENGTH)
        {
            g_pusFlashAddrArr[ucPageID] = usAddrIndex;
            break;
        }
    }

    // Write item data
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH, _DATA_ITEM_LENGTH - 1, pucWholeItem);
    // Write checksum
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH + _DATA_ITEM_LENGTH - 1, 1, pucWholeItem + _DATA_ITEM_LENGTH - 1);

    g_pusFlashAddrArr[ucPageID]++;

    return _TRUE;
}


//--------------------------------------------------
// Description  : Calculate item data or page info checksum
// Input Value  : pucData: buf to item data or page info data
//                ucLength: buf length
// Output Value : checksum value
//--------------------------------------------------
BYTE UserCommonFlashCalculateCheckSumData(BYTE *pucData, BYTE ucLength)
{
    BYTE ucIndex = 0;
    BYTE ucResult = 0;
    BYTE ucData = 0;

    bit bDataBit0 = 0;
    bit bDataBit1 = 0;
    bit bDataBit2 = 0;
    bit bDataBit3 = 0;
    bit bDataBit4 = 0;
    bit bDataBit5 = 0;
    bit bDataBit6 = 0;
    bit bDataBit7 = 0;

    bit bTempCRC0 = 0;
    bit bTempCRC1 = 0;
    bit bTempCRC2 = 0;
    bit bTempCRC3 = 0;
    bit bTempCRC4 = 0;
    bit bTempCRC5 = 0;
    bit bTempCRC6 = 0;
    bit bTempCRC7 = 0;

    bit bLastCRC0 = 0;
    bit bLastCRC1 = 0;
    bit bLastCRC2 = 0;
    bit bLastCRC3 = 0;
    bit bLastCRC4 = 0;
    bit bLastCRC5 = 0;
    bit bLastCRC6 = 0;
    bit bLastCRC7 = 0;

    for(ucIndex = 0; ucIndex < ucLength; ucIndex++)
    {
        ucData = pucData[ucIndex];
        bDataBit0 = (bit)(ucData & _BIT0);
        bDataBit1 = (bit)(ucData & _BIT1);
        bDataBit2 = (bit)(ucData & _BIT2);
        bDataBit3 = (bit)(ucData & _BIT3);
        bDataBit4 = (bit)(ucData & _BIT4);
        bDataBit5 = (bit)(ucData & _BIT5);
        bDataBit6 = (bit)(ucData & _BIT6);
        bDataBit7 = (bit)(ucData & _BIT7);

        bTempCRC0 = bDataBit7 ^ bDataBit6 ^ bDataBit0 ^ bLastCRC7 ^ bLastCRC6 ^ bLastCRC0;
        bTempCRC1 = bDataBit6 ^ bDataBit1 ^ bDataBit0 ^ bLastCRC6 ^ bLastCRC1 ^ bLastCRC0;
        bTempCRC2 = bDataBit6 ^ bDataBit2 ^ bDataBit1 ^ bDataBit0 ^ bLastCRC6 ^ bLastCRC2 ^ bLastCRC1 ^ bLastCRC0;
        bTempCRC3 = bDataBit7 ^ bDataBit3 ^ bDataBit2 ^ bDataBit1 ^ bLastCRC7 ^ bLastCRC3 ^ bLastCRC2 ^ bLastCRC1;
        bTempCRC4 = bDataBit4 ^ bDataBit3 ^ bDataBit2 ^ bLastCRC4 ^ bLastCRC3 ^ bLastCRC2;
        bTempCRC5 = bDataBit5 ^ bDataBit4 ^ bDataBit3 ^ bLastCRC5 ^ bLastCRC4 ^ bLastCRC3;
        bTempCRC6 = bDataBit6 ^ bDataBit5 ^ bDataBit4 ^ bLastCRC6 ^ bLastCRC5 ^ bLastCRC4;
        bTempCRC7 = bDataBit7 ^ bDataBit6 ^ bDataBit5 ^ bLastCRC7 ^ bLastCRC6 ^ bLastCRC5;

        bLastCRC0 = bTempCRC0;
        bLastCRC1 = bTempCRC1;
        bLastCRC2 = bTempCRC2;
        bLastCRC3 = bTempCRC3;
        bLastCRC4 = bTempCRC4;
        bLastCRC5 = bTempCRC5;
        bLastCRC6 = bTempCRC6;
        bLastCRC7 = bTempCRC7;
    }

    ucResult = (((BYTE)bLastCRC0) + (((BYTE)bLastCRC1) << 1) + (((BYTE)bLastCRC2) << 2) + (((BYTE)bLastCRC3) << 3) + (((BYTE)bLastCRC4) << 4) + (((BYTE)bLastCRC5) << 5) + (((BYTE)bLastCRC6) << 6) + (((BYTE)bLastCRC7) << 7));

    return ucResult;
}

//--------------------------------------------------
// Description  : Save system data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashSaveSystemData(void)
{
    // check flash size for system data
    static_assert(((sizeof(StructSystemDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)) <= (_FLASH_ITEMID_SYSTEM_DATA_END - _FLASH_ITEMID_SYSTEM_DATA + 1),
                  "sizeof(StructSystemDataType) too large");

    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructSystemDataType);

    for(ucItemOffset = 0; ucItemOffset < (_FLASH_ITEMID_SYSTEM_DATA_END - _FLASH_ITEMID_SYSTEM_DATA + 1); ucItemOffset++)
    {
        EnumFlashItemIDType enumItemID = (_FLASH_ITEMID_SYSTEM_DATA + ucItemOffset);
        BYTE *pucSystemData = (((BYTE *)(&g_stNVRamSystemData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2));

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem(enumItemID, pucSystemData, (_DATA_ITEM_LENGTH - 2));
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem(enumItemID, pucSystemData, ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Load system data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashLoadSystemData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructSystemDataType);
    BYTE pucBuffer[_DATA_ITEM_LENGTH - 2] = {0};

    for(ucItemOffset = 0; ucItemOffset < (_FLASH_ITEMID_SYSTEM_DATA_END - _FLASH_ITEMID_SYSTEM_DATA + 1); ucItemOffset++)
    {
        EnumFlashItemIDType enumItemID = (_FLASH_ITEMID_SYSTEM_DATA + ucItemOffset);
        BYTE *pucSystemData = (((BYTE *)(&g_stNVRamSystemData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2));

        if(UserCommonFlashLoadItem(enumItemID, pucBuffer, (_DATA_ITEM_LENGTH - 2)) == _FALSE)
        {
            g_stNVRamSystemData = g_stNVRamSystemDefaultData;
            return;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy(pucSystemData, pucBuffer, (_DATA_ITEM_LENGTH - 2));
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy(pucSystemData, pucBuffer, ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Restore system data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreSystemData(void)
{
    BYTE pucBuffer[1] = {0};

    g_stNVRamSystemData = g_stNVRamSystemDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SYSTEM_DATA, pucBuffer, 1) == _TRUE)
    {
        UserCommonFlashSaveSystemData();
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Save mode data to flash
// Input Value  : ucSlotIndex
// Output Value : None
//--------------------------------------------------
void UserCommonFlashLoadModeUserData(BYTE ucSlotIndex)
{
    BYTE pucBuffer[sizeof(StructVgaModeUserDataType)] = {0};

    ucSlotIndex = ucSlotIndex % _MODE_SLOT_AMOUNT;

    if(UserCommonFlashLoadItem(UserInterfaceVgaGetModeFlashIdBase() + ucSlotIndex, pucBuffer, sizeof(StructVgaModeUserDataType)) == _TRUE)
    {
        memcpy(&g_stVgaModeUserData, pucBuffer, sizeof(StructVgaModeUserDataType));
    }
    else
    {
        memset(&g_stVgaModeUserData, 0xFF, sizeof(StructVgaModeUserDataType));
    }
}

//--------------------------------------------------
// Description  : Save mode data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashSaveModeUserData(void)
{
    static_assert(sizeof(StructVgaModeUserDataType) <= (_DATA_ITEM_LENGTH - 2), "sizeof(StructVgaModeUserDataType) too large");

    BYTE ucFifoIndex = 0;
    BYTE ucSlotIndex = 0;

    for(ucFifoIndex = 0; ucFifoIndex < UserCommonFlashGetMaxFifoGroupCnt(); ucFifoIndex++)
    {
        if(UserCommonFlashLoadModeUserModeNumberData(ucFifoIndex) == g_stVgaModeUserData.ucModeNumber)
        {
            ucSlotIndex = ucFifoIndex;
            break;
        }
    }

    if(ucFifoIndex >= UserCommonFlashGetMaxFifoGroupCnt())
    {
        ucSlotIndex = UserCommonFlashVGAFifoModeIndexOffsetInc(1);
    }

    // Save mode user data
    UserCommonFlashSaveItem(UserInterfaceVgaGetModeFlashIdBase() + ucSlotIndex, (BYTE *)(&g_stVgaModeUserData), sizeof(StructVgaModeUserDataType));
}

//--------------------------------------------------
// Description  : Load mode data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonFlashLoadModeUserModeNumberData(BYTE ucSlotIndex)
{
    BYTE ucModeNumber = 0xFF;
    StructVgaModeUserDataType stVGAModeUserData = {0};

    if(UserCommonFlashLoadItem(UserInterfaceVgaGetModeFlashIdBase() + ucSlotIndex, (BYTE *)(&stVGAModeUserData), sizeof(StructVgaModeUserDataType)) == _TRUE)
    {
        ucModeNumber = stVGAModeUserData.ucModeNumber;
    }

    return ucModeNumber;
}

//--------------------------------------------------
// Description  : Restore mode data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreModeUserData(void)
{
    BYTE pucBuffer[1] = {0};
    WORD usFlashIdBase = UserInterfaceVgaGetModeFlashIdBase();
    StructVgaModeUserDataType stVGAModeUserData = {0};

    // Default mode user data is all 0xFF
    for(g_stNVRamSystemData.ucModeSlotIndex = 0; g_stNVRamSystemData.ucModeSlotIndex < _MODE_SLOT_AMOUNT; g_stNVRamSystemData.ucModeSlotIndex++)
    {
        if(UserCommonFlashLoadItem(usFlashIdBase + g_stNVRamSystemData.ucModeSlotIndex, pucBuffer, 1) == _TRUE)
        {
            memset(&stVGAModeUserData, 0xFF, _DATA_ITEM_LENGTH - 2);
            UserCommonFlashSaveItem(usFlashIdBase + g_stNVRamSystemData.ucModeSlotIndex, (BYTE *)(&stVGAModeUserData), sizeof(StructVgaModeUserDataType));
        }
    }

    // Restore slot index
    g_stNVRamSystemData.ucModeSlotIndex = 0;
}

//--------------------------------------------------
// Description  : Increase mode index offset for VGA fifo
// Input Value  : step
// Output Value : mode fifo
//--------------------------------------------------
BYTE UserCommonFlashVGAFifoModeIndexOffsetInc(BYTE ucStep)
{
    BYTE ucMNumber = 0xFF;
    BYTE ucInx = 0;
    StructVgaModeUserDataType stVGAModeUserData;
    memset(&stVGAModeUserData, 0xFF, sizeof(StructVgaModeUserDataType));

    for(ucInx = 0; ucInx < _MODE_SLOT_AMOUNT; ucInx++)
    {
        g_stNVRamSystemData.ucModeSlotIndex = (g_stNVRamSystemData.ucModeSlotIndex + ucStep) % _MODE_SLOT_AMOUNT;

        ucMNumber = UserCommonFlashLoadModeUserModeNumberData(g_stNVRamSystemData.ucModeSlotIndex);

        if(UserCommonModeSearchCheckPresetModeTable(ucMNumber) == _TRUE)
        {
            if(UserCommonFlashLoadItem(UserInterfaceVgaGetModeFlashIdBase() + g_stNVRamSystemData.ucModeSlotIndex, (BYTE *)(&stVGAModeUserData), sizeof(StructVgaModeUserDataType)) == _TRUE)
            {
                if(stVGAModeUserData.b1IsPresetMode == _PRESET_MODE_TYPE)
                {
                    DebugMessageAnalog("4. Match presetmode", ucMNumber);
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    return g_stNVRamSystemData.ucModeSlotIndex;
}

//--------------------------------------------------
// Description  : Get max fifo count
// Input Value  : None
// Output Value : slot amount
//--------------------------------------------------
BYTE UserCommonFlashGetMaxFifoGroupCnt(void)
{
    return _MODE_SLOT_AMOUNT;
}

//--------------------------------------------------
// Description  : Load VGA setting
// Input Value  : color format
// Output Value : None
//--------------------------------------------------
void UserCommonFlashLoadADCSetting(EnumColorSpace enumColorFormat)
{
    BYTE pucBuffer[sizeof(StructAdcDataType)] = {0};

    if(enumColorFormat == _COLOR_SPACE_RGB)
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_VGA_ADC_DATA, pucBuffer, sizeof(StructAdcDataType)) == _TRUE)
        {
            memcpy(&g_stVgaAdcData, pucBuffer, sizeof(StructAdcDataType));
        }
        else
        {
            g_stVgaAdcData = g_stNVRamAdcRgbDefaultData;
        }
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_YPBPR_ADC_DATA, pucBuffer, sizeof(StructAdcDataType)) == _TRUE)
        {
            memcpy(&g_stVgaAdcData, pucBuffer, sizeof(StructAdcDataType));
        }
        else
        {
            g_stVgaAdcData = g_stNVRamAdcYpbprDefaultData;
        }
    }
#endif

    UserInterfaceNVRamGetDataStatus(_CHECK_ADC_LOAD);
}

//--------------------------------------------------
// Description  : Save VGA setting
// Input Value  : color format
// Output Value : None
//--------------------------------------------------
void UserCommonFlashSaveADCSetting(EnumColorSpace enumColorFormat)
{
    static_assert(sizeof(StructAdcDataType) <= (_DATA_ITEM_LENGTH - 2), "sizeof(StructAdcDataType) too large");

    if(UserInterfaceNVRamGetDataStatus(_CHECK_ADC_SAVE) == _CHECK_FAIL)
    {
        return;
    }

    if(enumColorFormat == _COLOR_SPACE_RGB)
    {
        UserCommonFlashSaveItem(_FLASH_ITEMID_VGA_ADC_DATA, (BYTE *)(&g_stVgaAdcData), sizeof(StructAdcDataType));
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        UserCommonFlashSaveItem(_FLASH_ITEMID_YPBPR_ADC_DATA, (BYTE *)(&g_stVgaAdcData), sizeof(StructAdcDataType));
    }
#endif
}

//--------------------------------------------------
// Description  : Restore VGA setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreADCSetting(void)
{
    BYTE pucBuffer[1] = {0};
    g_stVgaAdcData = g_stNVRamAdcRgbDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_VGA_ADC_DATA, pucBuffer, 1) == _TRUE)
    {
        UserCommonFlashSaveADCSetting(_COLOR_SPACE_RGB);
    }

#if(_YPBPR_SUPPORT == _ON)
    g_stVgaAdcData = g_stNVRamAdcYpbprDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_YPBPR_ADC_DATA, pucBuffer, 1) == _TRUE)
    {
        UserCommonFlashSaveADCSetting(_COLOR_SPACE_YPBPR);
    }
#endif
}
#endif // End of #if(_VGA_SUPPORT == _ON)

#endif // End of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)


#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)))
//--------------------------------------------------
// Description  : Restore EDID EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreEDID(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonEepromWrite(ulOffset, ucLength, pucBuf);
}
#endif


#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
//--------------------------------------------------
// Description  : Restore EDID EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreEDID(WORD usAddr, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_EDID_FLASH_BANK, usAddr, ucLength, pucBuf);
}
#endif


#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHDCPKeyBKsv(DWORD ulSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    UserCommonEepromRead(((DWORD)_RX_HDCP_1_4_KEY_ADDRESS_EEPROM + ulSubAddr), ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHDCPKey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead(((DWORD)_RX_HDCP_1_4_KEY_ADDRESS_EEPROM + 5 + (ulSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreHDCP1P4(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonEepromWrite((DWORD)_RX_HDCP_1_4_KEY_ADDRESS_EEPROM + ulOffset, ucLength, pucBuf);
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Aksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHDCPKeyAKsv(DWORD ulSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    UserCommonEepromRead(((DWORD)_TX_HDCP_1_4_KEY_ADDRESS_EEPROM + ulSubAddr), ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get TxHDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHDCPKey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead(((DWORD)_TX_HDCP_1_4_KEY_ADDRESS_EEPROM + 5 + (ulSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreTxHDCP1P4(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonEepromWrite((DWORD)_TX_HDCP_1_4_KEY_ADDRESS_EEPROM + ulOffset, ucLength, pucBuf);
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)


#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_1_4_KEY_FLASH_BANK, (_RX_HDCP_1_4_KEY_ADDRESS_FLASH + ucSubAddr), ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_1_4_KEY_FLASH_BANK, (_RX_HDCP_1_4_KEY_ADDRESS_FLASH + 5 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP 1.4 Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreHDCP1P4(WORD usAddr, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_RX_HDCP_1_4_KEY_FLASH_BANK, _RX_HDCP_1_4_KEY_ADDRESS_FLASH + usAddr, ucLength, pucBuf);
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Aksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_1_4_KEY_FLASH_BANK, (_TX_HDCP_1_4_KEY_ADDRESS_FLASH + ucSubAddr), ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get TxHDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_1_4_KEY_FLASH_BANK, (_TX_HDCP_1_4_KEY_ADDRESS_FLASH + 5 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_TX_HDCP_1_4_KEY_FLASH_BANK, _TX_HDCP_1_4_KEY_ADDRESS_FLASH + usOffset, ucLength, pucBuf);
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_HDCP_2_2_SUPPORT == _ON)
#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2Certrx(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + (ulSubAddr)), usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2RSAKPriv(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 522 + (ulSubAddr)), usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2RSARRModN(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 842 + (ulSubAddr)), usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2RSANpinv(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 970 + (ulSubAddr)), usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2RSADkey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 974 + (ulSubAddr)), usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2LCKey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 1102 + (ulSubAddr)), usLength, pucReadArray);
#endif
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreHDCP2(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromWrite((DWORD)_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + ulOffset, ucLength, pucBuf);
#endif
}
#endif
#endif // End of #if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_DP_TX_SUPPORT == _ON)
#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHdcp2RRMODN(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + (ulSubAddr)), usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHdcp2DcpLlcN(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + 384 + (ulSubAddr)), usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHdcp2EKey(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + 772 + (ulSubAddr)), usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHdcp2NPinv(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(((DWORD)_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + 768 + (ulSubAddr)), usLength, pucReadArray);
#endif
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreTxHDCP2(DWORD ulOffset, BYTE ucLength, BYTE *pucBuf)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromWrite((DWORD)_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + ulOffset, ucLength, pucBuf);
#endif
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)

#endif // End of #if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 522 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 842 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 970 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 974 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 1102 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP 2.0 key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_RX_HDCP_2_2_KEY_FLASH_BANK, _RX_HDCP_2_2_KEY_ADDRESS_FLASH + usAddr, ucLength, pucBuf);
}
#endif
#endif // End of #if(_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)

#if(_DP_TX_SUPPORT == _ON)
#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_2_2_KEY_FLASH_BANK, (_TX_HDCP_2_2_KEY_ADDRESS_FLASH + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_2_2_KEY_FLASH_BANK, (_TX_HDCP_2_2_KEY_ADDRESS_FLASH + 384 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_2_2_KEY_FLASH_BANK, (_TX_HDCP_2_2_KEY_ADDRESS_FLASH + 772 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_2_2_KEY_FLASH_BANK, (_TX_HDCP_2_2_KEY_ADDRESS_FLASH + 768 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP 2.0 key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreTxHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_TX_HDCP_2_2_KEY_FLASH_BANK, _TX_HDCP_2_2_KEY_ADDRESS_FLASH + usAddr, ucLength, pucBuf);
}
#endif
#endif // End of #if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
#endif

#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Erase page
// Input Value  : usBank: bank index
//                ucPage: page index (0 ~ 15)
// Output Value : _TRUE for erase success and _FALSE for erase fail
//--------------------------------------------------
bit UserCommonFlashErasePage(WORD usBank, BYTE ucPage)
{
    return ScalerFlashErasePage(usBank, ucPage, _TRUE, _TRUE);
}

//--------------------------------------------------
// Description  : Save data to flash
// Input Value  : usBank: bank index
//                usAddr: address in usBank
//                ucLength: the data length to save
//                pucData: data buffer to save
// Output Value : _TRUE for save success and _FALSE for save fail
//--------------------------------------------------
bit UserCommonFlashWrite(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData)
{
    return ScalerFlashWrite(usBank, usAddr, usLength, pucData);
}
#endif // End of #if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)

#if(_FLASH_READ_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load data from flash
// Input Value  : usBank: bank index
//                usAddr: address in usBank
//                ucLength: the data length to load
//                pucData: data buffer to save the load data
// Output Value : _TRUE for load success and _FALSE for load fail
//--------------------------------------------------
bit UserCommonFlashRead(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData)
{
    return ScalerFlashRead(usBank, (BYTE *)(DWORD)usAddr, usLength, pucData);
}
#endif // End of #if(_FLASH_READ_FUNCTION_SUPPORT == _ON)

#if(_FLASH_WR_PROTECT == _ON)
//--------------------------------------------------
// Description  : Set SR to protect flash
// Input Value  : None
// Output Value : Return _TURE if succeed, else return _FALSE
//--------------------------------------------------
void UserCommonFlashWRProtect(void)
{
    ScalerFlashWRProtect();
}
#endif

#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore default EDID
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreEDID(void)
{
    BYTE ucCount = 0;
    BYTE pucBuffer[16] = {0};

    ucCount = ucCount;

#if(_EDID_TABLE_LOCATED_IN_FLASH == _ON)
    UserCommonFlashErasePage(_EDID_FLASH_BANK, _EDID_TABLE_FLASH_PAGE);
#endif

// A0 EDID-----------------------------------------------------------------------------------------------------------
#if((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_A0_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_A0 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_A0_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_A0_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D0 EDID-----------------------------------------------------------------------------------------------------------
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D0_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D0 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D0_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D0_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D1 EDID-----------------------------------------------------------------------------------------------------------
#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D1_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D1 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D1_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D1_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D2 EDID-----------------------------------------------------------------------------------------------------------
#if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D2_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D2 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D2_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D2_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D3 EDID-----------------------------------------------------------------------------------------------------------
#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D3_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D3 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D3_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D3_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D4 EDID-----------------------------------------------------------------------------------------------------------
#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D4_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D4 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D4_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D4_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif

// D5 EDID-----------------------------------------------------------------------------------------------------------
#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && ((_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) || (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
    for(ucCount = 0; ucCount < (_D5_EMBEDDED_DDCRAM_MAX_SIZE / sizeof(pucBuffer)); ucCount++)
    {
        memcpy(pucBuffer, tEDID_TABLE_D5 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
#if(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
        UserCommonEepromRestoreEDID(_EDID_D5_ADDRESS_EEPROM + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#elif(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
        UserCommonFlashRestoreEDID(_EDID_D5_ADDRESS_FLASH + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
#endif
    }
#endif
}
#endif // End of #if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore default HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamRestoreHDCP(void)
{
    BYTE ucCount = 0;
    BYTE pucBuffer[16] = {0};

#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    if((_RX_HDCP_1_4_KEY_FLASH_BANK != _EDID_FLASH_BANK) || (_RX_HDCP_1_4_TABLE_FLASH_PAGE != _EDID_TABLE_FLASH_PAGE))
    {
        UserCommonFlashErasePage(_RX_HDCP_1_4_KEY_FLASH_BANK, _RX_HDCP_1_4_TABLE_FLASH_PAGE);
    }
#endif

    // Dump BKSV into NVRAM
    memcpy(pucBuffer, tHDCP_KEY_BKSV, UserCommonHdcpGetKeyBksvSize());
    UserCommonNVRamRestoreHDCP1P4(0, UserCommonHdcpGetKeyBksvSize(), pucBuffer);

    // Dump HDCP Key into NVRAM
    for(ucCount = 0; ucCount < 20; ucCount++)
    {
        memcpy(pucBuffer, tHDCP_KEY_TABLE + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));

        UserCommonNVRamRestoreHDCP1P4(5 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }
#endif // End of #if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))

#if((_HDCP_2_2_SUPPORT == _ON) && ((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)))
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    if((_RX_HDCP_2_2_KEY_FLASH_BANK != _EDID_FLASH_BANK) || (_RX_HDCP_2_2_TABLE_FLASH_PAGE != _EDID_TABLE_FLASH_PAGE))
    {
        UserCommonFlashErasePage(_RX_HDCP_2_2_KEY_FLASH_BANK, _RX_HDCP_2_2_TABLE_FLASH_PAGE);
    }
#endif

    // Restore Certrx to NVRAM
    for(ucCount = 0; ucCount < 33; ucCount++)
    {
        if(ucCount < 32)
        {
            memcpy(pucBuffer, tHDCP2_Certrx + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
            UserCommonNVRamRestoreHDCP2(ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
        }
        else
        {
            memcpy(pucBuffer, tHDCP2_Certrx + ucCount * sizeof(pucBuffer), 10);
            UserCommonNVRamRestoreHDCP2(512, 10, pucBuffer);
        }
    }

    // Restore Kpriv to NVRAM
    for(ucCount = 0; ucCount < 20; ucCount++)
    {
        memcpy(pucBuffer, tHDCP2_KPriv + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreHDCP2(522 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore RRMODN to NVRAM
    for(ucCount = 0; ucCount < 8; ucCount++)
    {
        memcpy(pucBuffer, tHDCP2_RRMODN + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreHDCP2(842 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore Npinv to NVRAM
    memcpy(pucBuffer, tHDCP2_NPINV, UserCommonHdcp2GetRSANpinvSize());
    UserCommonNVRamRestoreHDCP2(970, UserCommonHdcp2GetRSANpinvSize(), pucBuffer);

    // Restore RSA D key to NVRAM
    for(ucCount = 0; ucCount < 8; ucCount++)
    {
        memcpy(pucBuffer, tHDCP2_DKey + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreHDCP2(974 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore LC key to NVRAM
    memcpy(pucBuffer, tHDCP2_LCKey, UserCommonHdcp2GetLCKeySize());
    UserCommonNVRamRestoreHDCP2(1102, UserCommonHdcp2GetLCKeySize(), pucBuffer);

#endif // End of #if((_HDCP_2_2_SUPPORT == _ON) && ((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)))

#if(_DP_TX_SUPPORT == _ON)

#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    if(((_TX_HDCP_1_4_KEY_FLASH_BANK != _EDID_FLASH_BANK) || (_TX_HDCP_1_4_TABLE_FLASH_PAGE != _EDID_TABLE_FLASH_PAGE)) &&
       ((_TX_HDCP_1_4_KEY_FLASH_BANK != _RX_HDCP_1_4_KEY_FLASH_BANK) || (_TX_HDCP_1_4_TABLE_FLASH_PAGE != _RX_HDCP_1_4_TABLE_FLASH_PAGE)))
    {
        UserCommonFlashErasePage(_TX_HDCP_1_4_KEY_FLASH_BANK, _TX_HDCP_1_4_TABLE_FLASH_PAGE);
    }
#endif

    // Dump BKSV into NVRam
    memcpy(pucBuffer, tTX_HDCP_KEY_AKSV, UserCommonHdcpGetTxAKsvSize());
    UserCommonNVRamRestoreTxHDCP1P4(0, UserCommonHdcpGetTxAKsvSize(), pucBuffer);

    // Dump HDCP Key into NVRam
    for(ucCount = 0; ucCount < 20; ucCount++)
    {
        memcpy(pucBuffer, tTX_HDCP_KEY_TABLE + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreTxHDCP1P4(5 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }
#endif // End of #if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM))

#if((_HDCP_2_2_SUPPORT == _ON) && ((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)))
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
    if(((_TX_HDCP_2_2_KEY_FLASH_BANK != _EDID_FLASH_BANK) || (_TX_HDCP_2_2_TABLE_FLASH_PAGE != _EDID_TABLE_FLASH_PAGE)) &&
       ((_TX_HDCP_2_2_KEY_FLASH_BANK != _RX_HDCP_2_2_KEY_FLASH_BANK) || (_TX_HDCP_2_2_TABLE_FLASH_PAGE != _RX_HDCP_2_2_TABLE_FLASH_PAGE)))
    {
        UserCommonFlashErasePage(_TX_HDCP_2_2_KEY_FLASH_BANK, _TX_HDCP_2_2_TABLE_FLASH_PAGE);
    }
#endif

    // Restore RRMODN to NVRAM (384-Bytes)
    for(ucCount = 0; ucCount < 24; ucCount++)
    {
        memcpy(pucBuffer, tTX_HDCP2_RRMODN + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreTxHDCP2(ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore DCPLLCN to NVRAM (384-Bytes)
    for(ucCount = 0; ucCount < 24; ucCount++)
    {
        memcpy(pucBuffer, tTX_HDCP2_DCP_LLC_N + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreTxHDCP2(384 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore EKEY to NVRAM (128-Bytes)
    for(ucCount = 0; ucCount < 8; ucCount++)
    {
        memcpy(pucBuffer, tTX_HDCP2_EKEY + ucCount * sizeof(pucBuffer), sizeof(pucBuffer));
        UserCommonNVRamRestoreTxHDCP2(772 + ucCount * sizeof(pucBuffer), sizeof(pucBuffer), pucBuffer);
    }

    // Restore Npinv to NVRAM (4-Bytes)
    memcpy(pucBuffer, tTX_HDCP2_NPINV, UserCommonHdcp2GetDpTxNPinvSize());
    UserCommonNVRamRestoreTxHDCP2(768, UserCommonHdcp2GetDpTxNPinvSize(), pucBuffer);

#endif // End of #if((_HDCP_2_2_SUPPORT == _ON) && ((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)))

#endif // End of #if(_DP_TX_SUPPORT == _ON)
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)

//--------------------------------------------------
// Description  : Get flash bank offset
// Input Value  : None
// Output Value : GET_FLASH_BANK_OFFSET
//--------------------------------------------------
DWORD UserCommonNVRamGetFlashBankOffset(void)
{
    return ScalerNVRamGetFlashBankOffset();
}

#if(_EMBEDDED_RESOURCE_FILE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get resource address in flash
// Input Value  : ulResourceIndex -> target resource
// Output Value : relative address in flash
//--------------------------------------------------
DWORD UserCommonNVRamGetResourceAddress(DWORD ulResourceIndex)
{
    DWORD ulResourceInfoAddress = __resource_info_region_start + _DEVICE_FLASH_BASE_ADDR;
    DWORD ulAddress = ((DWORD *)ulResourceInfoAddress)[ulResourceIndex * 2];

#if(_SCPU_SUPPORT == _ON)
    ulAddress -= _SCPU_FLASH_BASE_ADDR;
#else
    ulAddress -= _KCPU_FLASH_BASE_ADDR;
#endif

    return ulAddress;
}

//--------------------------------------------------
// Description  : Get resource size
// Input Value  : ulResourceIndex -> target resource
// Output Value : resource size
//--------------------------------------------------
DWORD UserCommonNVRamGetResourceSize(DWORD ulResourceIndex)
{
    DWORD ulResourceInfoAddress = __resource_info_region_start + _DEVICE_FLASH_BASE_ADDR;
    return ((DWORD *)ulResourceInfoAddress)[ulResourceIndex * 2 + 1];
}
#endif