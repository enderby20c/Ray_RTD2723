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
// ID Code      : RTD2020NVRamOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_NVRAM_OSD__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//--------------------------------------------------
// Version Code of NVRam
//--------------------------------------------------
#define _CHECKSUM                                   LOBYTE(\
                                                        7 +\
                                                        _SYSTEM_DATA_ADDRESS_END +\
                                                        _OSD_REGION_ADDRESS_END\
                                                    )// 0xF2

#define _VERSION_CODE                               LOBYTE(\
                                                        7 +\
                                                        _SYSTEM_DATA_ADDRESS_END +\
                                                        _OSD_REGION_ADDRESS_END +\
                                                        _2P_PIP_DISPLAY_SUPPORT +\
                                                        _2P_PBP_LR_DISPLAY_SUPPORT +\
                                                        _2P_PBP_TB_DISPLAY_SUPPORT +\
                                                        _3P_FLAG_DISPLAY_SUPPORT +\
                                                        _3P_SKEW_LR_DISPLAY_SUPPORT +\
                                                        _3P_SKEW_TB_DISPLAY_SUPPORT +\
                                                        _4P_DISPLAY_SUPPORT +\
                                                        _PANEL_TYPE\
                                                    )

//--------------------------------------------------
// Brightness/Contrast Default Value
//--------------------------------------------------
#define _BRIGHTNESS_REGION                          0x200
#define _CONTRAST_REGION                            0x800

//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                            50
#define _SIX_COLOR_SATURATION_R                     100

#define _SIX_COLOR_HUE_Y                            50
#define _SIX_COLOR_SATURATION_Y                     100

#define _SIX_COLOR_HUE_G                            50
#define _SIX_COLOR_SATURATION_G                     100

#define _SIX_COLOR_HUE_C                            50
#define _SIX_COLOR_SATURATION_C                     100

#define _SIX_COLOR_HUE_B                            50
#define _SIX_COLOR_SATURATION_B                     100

#define _SIX_COLOR_HUE_M                            50
#define _SIX_COLOR_SATURATION_M                     100

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of PageInfo Address
//--------------------------------------------------
#define _FLASH_FW_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 16)
#define _FLASH_FW_VERSIONCODE_ADDR                  (_FLASH_PAGE_SIZE - 15)
#define _PAGEINFO_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 5)
#define _PAGEINFO_PAGEID_ADDR                       (_FLASH_PAGE_SIZE - 4)
#define _PAGEINFO_MOVECOUNT_ADDR                    (_FLASH_PAGE_SIZE - 3)

// This value is used to indicate the EEPROM emulaiton FW version
#define _EEPROM_EMULATION_VERSION                   0x01
#endif

// Attention: it is necessary for sizeof(StructOsdUserDataType) < ((_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START) * (_DATA_ITEM_LENGTH - 2))
// Please check it when add items in StructOsdUserDataType
code StructOsdUserDataType g_stOsdUserDataDefault = _USER_DATA_DEFAULT;

code StructColorProcDataType tColorTempDefaultData[] =
{
    {
        _CT9300_RED,
        _CT9300_GREEN,
        _CT9300_BLUE,
    },

    {
        _CT7500_RED,
        _CT7500_GREEN,
        _CT7500_BLUE,
    },

    {
        _CT6500_RED,
        _CT6500_GREEN,
        _CT6500_BLUE,
    },

    {
        _CT5800_RED,
        _CT5800_GREEN,
        _CT5800_BLUE,
    },

    {
        _CTSRGB_RED,
        _CTSRGB_GREEN,
        _CTSRGB_BLUE,
    },

    {
        _CTUSER_RED,
        _CTUSER_GREEN,
        _CTUSER_BLUE,
    },
};

code StructOsdInputPortDataType tOsdInputPortDataDefault[_OSD_INPUT_AMOUNT] =
{
    // _A0_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D0_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D1_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D2_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D3_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D4_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D5_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D6_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D7_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D8_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    // _D9_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D9_D0_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D9_D1_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
    // _D9_D2_INPUT_PORT
    _USER_PORT_DATA_DEFAULT,
#endif
};

code StructOsdRegionDataType tOsdRegionDataDefault[_REGION_AMOUNT] =
{
    // 1P
    _USER_REGION_DATA_DEFAULT,
    // 1P Demo Outside
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_2P_LR
    // PBP L
    _USER_REGION_DATA_DEFAULT,
    // PBP R
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_2P_TB
    // PBP T
    _USER_REGION_DATA_DEFAULT,
    // PBP B
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_2P_PIP
    // PIP MAIN
    _USER_REGION_DATA_DEFAULT,
    // PIP SUB
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_3P_Flag
    // Main inside
    _USER_REGION_DATA_DEFAULT,
    // outside
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_3P_Skew_L
    // Main inside
    _USER_REGION_DATA_DEFAULT,
    // outside
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_3P_Skew_R
    // Main inside
    _USER_REGION_DATA_DEFAULT,
    // outside
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_3P_Skew_T
    // Main inside
    _USER_REGION_DATA_DEFAULT,
    // outside
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_3P_Skew_B
    // Main inside
    _USER_REGION_DATA_DEFAULT,
    // outside
    _USER_REGION_DATA_DEFAULT,

    // _OSD_DM_4P
    // inside
    _USER_REGION_DATA_DEFAULT,
    // outside
    _USER_REGION_DATA_DEFAULT,
};

code StructOsdDisplayModeDataType tOsdDisplayModeDataDefault[_OSD_DM_AMOUNT] =
{
    { // _OSD_DM_1P
        _OSD_SR_1P_FULL,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1,       // BYTE ucAudioInputRegin;

    },

    { // _OSD_DM_2P_LR
        _OSD_SR_2P_LR_L,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },

    { // _OSD_DM_2P_TB
        _OSD_SR_2P_TB_T,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },

    { // _OSD_DM_2P_PIP
        _OSD_SR_2P_PIP_MAIN,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },
    { // _OSD_DM_3P_FLAG
        _OSD_SR_3P_FLAG_MAIN,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },

    { // _OSD_DM_3P_SKEW_L
        _OSD_SR_3P_SKEW_L_MAIN,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },

    { // _OSD_DM_3P_SKEW_R
        _OSD_SR_3P_SKEW_R_MAIN,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },
    { // _OSD_DM_3P_SKEW_T
        _OSD_SR_3P_SKEW_T_MAIN,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },
    { // _OSD_DM_3P_SKEW_B
        _OSD_SR_3P_SKEW_B_MAIN,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },

    { // _OSD_DM_4P
        _OSD_SR_4P_LT_INSIDE,
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        {
            _OSD_INPUT_AUTO,                // BYTE pucOsdInputPort[0];
            _OSD_INPUT_D1,                  // BYTE pucOsdInputPort[1];
            _OSD_INPUT_D2,                  // BYTE pucOsdInputPort[2];
            _OSD_INPUT_D3,                  // BYTE pucOsdInputPort[3];
        },
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1        // BYTE ucAudioInputRegin;
    },
};
#if(_DM_FUNCTION == _ON)
code StructOsdDVisionModeDataType tDVisionPictureModeDefault[_OSD_DVISION_PICTURE_AMOUNT] = _DVISION_DATA_DEFAULT;
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
code StructOsdUserDataArcDataType g_stAudioArcDataDefault = _USER_AUDIO_ARC_DATA_DEFAULT;
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructOsdUserDataType g_stOsdUserData;
StructColorProcDataType g_stColorProcData;
StructOsdInputPortDataType g_pstOsdInputPortData[_OSD_INPUT_AMOUNT];
StructOsdRegionDataType g_pstOsdRegionData[2];
StructOsdDisplayModeDataType g_stOsdDisplayModeData;
StructOsdItemDataType g_stOsdItemData;
#if(_AUDIO_ARC_SUPPORT == _ON)
StructOsdUserDataArcDataType g_stAudioArcData;
#endif


#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
DWORD g_ulFlashMoveCount;
BYTE g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
void RTDEepromStartup(void);
void RTDEepromWholeRestore(void);
void RTDEepromRestoreBacklight(void);
void RTDEepromLoadOsdUserData(void);
void RTDEepromSaveOsdUserData(void);
void RTDEepromRestoreOsdUserData(void);

void RTDEepromLoadColorSetting(BYTE ucRegion);
void RTDEepromSaveColorSetting(BYTE ucColorTempType);
void RTDEepromRestoreColorSetting(void);
void RTDEepromRestoreUserColorSetting(void);

void RTDEepromLoadOsdInputSourceData(BYTE ucSource);
void RTDEepromSaveOsdInputSourceData(BYTE ucSource);
void RTDEepromRestoreOsdInputSourceData(void);

void RTDEepromLoadOsdInputPortData(BYTE ucPort);
void RTDEepromSaveOsdInputPortData(BYTE ucPort);
void RTDEepromRestoreOsdInputPortData(void);

void RTDEepromLoadOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion);
void RTDEepromSaveOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion);
void RTDEepromRestoreOsdRegionData(void);

void RTDEepromLoadOsdDisplayModeData(BYTE ucDisplayMode);
void RTDEepromSaveOsdDisplayModeData(BYTE ucDisplayMode);
void RTDEepromRestoreOsdDisplayModeData(void);
#if(_AUDIO_ARC_SUPPORT == _ON)
void RTDEepromLoadAudioArcData(void);
void RTDEepromSaveAudioArcData(void);
void RTDEepromRestoreAudioArcData(void);
#endif
#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

BYTE RTDFlashGetFreePage(void);
bit RTDFlashIsPageInfoValid(BYTE ucPage);
void RTDFlashInitialDataPage(BYTE ucPageID);
WORD RTDFlashSearchPageAddr(BYTE ucPageID);
void RTDFlashInitialAddr(void);
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode);
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode);
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData);

void RTDFlashStartup(void);
void RTDFlashWholeRestore(void);
void RTDFlashRestoreBacklight(void);
void RTDFlashLoadOSDData(void);
void RTDFlashSaveOSDData(void);
void RTDFlashRestoreOSDData(void);
void RTDFlashLoadColorSetting(BYTE ucRegion);
void RTDFlashSaveColorSetting(BYTE ucColorTempType);
void RTDFlashRestoreColorSetting(void);
void RTDFlashRestoreUserColorSetting(void);
void RTDFlashLoadOsdInputSourceData(BYTE ucSource);
void RTDFlashSaveOsdInputSourceData(BYTE ucSource);
void RTDFlashRestoreOsdInputSourceData(void);
void RTDFlashLoadOsdInputPortData(BYTE ucPort);
void RTDFlashSaveOsdInputPortData(BYTE ucPort);
void RTDFlashRestoreOsdInputPortData(void);
void RTDFlashLoadOsdDisplayModeData(BYTE ucDisplayMode);
void RTDFlashSaveOsdDisplayModeData(BYTE ucDisplayMode);
void RTDFlashRestoreOsdDisplayModeData(void);
bit RTDFlashLoadOSDDataGroup(WORD usAddr, WORD usLength, BYTE *pucData);
void RTDFlashSaveOSDDataGroup(WORD usAddr, WORD usLength, BYTE *pucData);
void RTDFlashLoadOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion);
void RTDFlashSaveOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion);
void RTDFlashRestoreOsdRegionData(void);

#if(_PANEL_EXIST_MULTIPANEL == _ON)
void RTDFlashLoadPanelIndex(void);
void RTDFlashSavePanelIndex(void);
void RTDFlashRestorePanelIndex(void);
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)
#if(_AUDIO_ARC_SUPPORT == _ON)
void RTDFlashLoadAudioArcData(void);
void RTDFlashSaveAudioArcData(void);
void RTDFlashRestoreAudioArcData(void);
#endif
#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
BYTE RTDNVRamTransferOsdRegionType(BYTE ucDisplayMode, BYTE ucRegion);
BYTE RTDNVRamTransferOsdRegionIndex(BYTE ucDisplayMode, BYTE ucRegion);
#if(_DM_FUNCTION == _ON)
BYTE RTDNVRamGetDVisionModeData(WORD usOsdItemType, BYTE ucRegion);
void RTDNVRamSetDVisionModeData(WORD usOsdItemType, BYTE ucData, BYTE ucRegion);
void RTDNVRamRestoreOsdDVisionModeData(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Eeprom check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromStartup(void)
{
    BYTE ucCnt = 0;

    // Check twice if VERSION CODE matches
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        pData[0] = _CHECKSUM ^ 0xFF;
        pData[1] = _VERSION_CODE ^ 0xFF;
        UserCommonEepromRead(_EEPROM_CHECKSUM_ADDRESS, 2, pData);

        if((pData[0] == _CHECKSUM) && (pData[1] == _VERSION_CODE))
        {
            break;
        }
    }

/////////////////////////////////////////////
    // Force default value
//    pData[0] = ~_CHECKSUM;
/////////////////////////////////////////////


    if(pData[0] != _CHECKSUM)
    {
        BYTE pucData[3] = {0};

        // Load default value and save to EEPROM
        RTDEepromWholeRestore();

        // Save VERSION CODE to EEPROM
        pucData[0] = _CHECKSUM;
        pucData[1] = _VERSION_CODE;
        pucData[2] = 0; // _PANEL_INDEX_ADDRESS

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        SET_MDOMAIN_PANEL_INDEX(0);
#endif

        UserCommonEepromWrite(_EEPROM_CHECKSUM_ADDRESS, 2, pucData);
        UserCommonEepromWrite(_PANEL_INDEX_ADDRESS, 1, &pucData[2]);
    }
    else if(pData[1] != _VERSION_CODE)
    {
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        RTDEepromSaveColorSetting(_CT_USER);

        UserCommonEepromRestoreSystemData();
        RTDEepromRestoreOsdUserData();

#if(_VGA_SUPPORT == _ON)
        UserCommonEepromRestoreModeUserData();
#endif

        RTDEepromRestoreOsdInputSourceData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
        RTDEepromRestoreAudioArcData();
#endif

        pData[1] = _VERSION_CODE;
        UserCommonEepromWrite(_EEPROM_VERSION_CODE_ADDRESS, 1, &pData[1]);
    }
    else
    {
        UserCommonEepromLoadSystemData();
        RTDEepromLoadOsdUserData();

        RTDEepromLoadOsdDisplayModeData(GET_OSD_DISPLAY_MODE());

        RTDEepromLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());


#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), _PCM_OSD_NATIVE);
            RTDEepromSaveOsdUserData();
        }

#if(_AUDIO_ARC_SUPPORT == _ON)
        RTDEepromLoadAudioArcData();
#endif
    }

#if(_PANEL_EXIST_MULTIPANEL == _ON)
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    SET_MDOMAIN_PANEL_INDEX(ScalerQCGetMultiPanelIndex());
#endif
#endif

    // SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
    /*
    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    */

    // Load port settings
    {
        BYTE ucIndex = 0;
        for(ucIndex = 0; ucIndex < _OSD_INPUT_AMOUNT; ++ucIndex)
        {
            RTDEepromLoadOsdInputPortData(ucIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Load default data and save to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromWholeRestore(void)
{
    UserCommonEepromRestoreSystemData();

#if(_VGA_SUPPORT == _ON)
    UserCommonEepromRestoreModeUserData();
    UserCommonEepromRestoreADCSetting();
#endif

    // Osd user data
    RTDEepromRestoreOsdUserData();

    // color temp
    RTDEepromRestoreColorSetting();
    RTDEepromRestoreUserColorSetting();

    // osd input source
    RTDEepromRestoreOsdInputSourceData();

    // osd input port
    RTDEepromRestoreOsdInputPortData();

    // osd region data
    RTDEepromRestoreOsdRegionData();

    // osd display mode
    RTDEepromRestoreOsdDisplayModeData();

#if(_AUDIO_ARC_SUPPORT == _ON)
    RTDEepromRestoreAudioArcData();
#endif
}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreBacklight(void)
{
    SET_OSD_BACKLIGHT(g_stOsdUserDataDefault.usBackLight);
    RTDEepromSaveOsdUserData();
}

//--------------------------------------------------
// Description  : Load OSD data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdUserData(void)
{
    UserCommonEepromRead(_OSD_USER_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOsdUserData));
}

//--------------------------------------------------
// Description  : Save OSD data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOsdUserData(void)
{
    UserCommonEepromWrite(_OSD_USER_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOsdUserData));
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOsdUserData(void)
{
    g_stOsdUserData = g_stOsdUserDataDefault;
    RTDEepromSaveOsdUserData();
}

//--------------------------------------------------
// Description  : Load color settings from EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadColorSetting(BYTE ucRegion)
{
    BYTE pucData[6];
    memset(pucData, 0, sizeof(pucData));

#if(_OGC_FUNCTION == _ON)
    if(GET_OSD_GAMMA(ucRegion) != _GAMMA_OFF)
    {
        UserCommonColorGetOGCColorTempGain(GET_COLOR_TEMP_TYPE(ucRegion), (GET_OSD_GAMMA(ucRegion) - 1), pucData, _OGC_NORMAL_TYPE);
    }
    else
#elif(_OCC_PCM_GAMMA_SUPPORT == _ON)
    if(GET_OSD_GAMMA(ucRegion) != _GAMMA_OFF)
    {
        pucData[0] = 0x08;
        pucData[1] = 0x00;
        pucData[2] = 0x08;
        pucData[3] = 0x00;
        pucData[4] = 0x08;
        pucData[5] = 0x00;
    }
    else
#endif
    {
        UserCommonEepromRead(_COLORTEMP_DATA_ADDRESS + (GET_COLOR_TEMP_TYPE(ucRegion)) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), pucData);
    }

    g_stColorProcData.usColorTempR = TO_WORD(pucData[0], pucData[1]);
    g_stColorProcData.usColorTempG = TO_WORD(pucData[2], pucData[3]);
    g_stColorProcData.usColorTempB = TO_WORD(pucData[4], pucData[5]);
}

//--------------------------------------------------
// Description  : Save color settings to EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveColorSetting(BYTE ucColorTempType)
{
    BYTE pucData[6];
    memset(pucData, 0, sizeof(pucData));

    pucData[0] = HIBYTE(g_stColorProcData.usColorTempR);
    pucData[1] = LOBYTE(g_stColorProcData.usColorTempR);
    pucData[2] = HIBYTE(g_stColorProcData.usColorTempG);
    pucData[3] = LOBYTE(g_stColorProcData.usColorTempG);
    pucData[4] = HIBYTE(g_stColorProcData.usColorTempB);
    pucData[5] = LOBYTE(g_stColorProcData.usColorTempB);

    UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (ucColorTempType) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), pucData);
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreColorSetting(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = _CT_9300; ucTemp < _CT_USER; ucTemp++)
    {
        g_stColorProcData = tColorTempDefaultData[ucTemp];
        RTDEepromSaveColorSetting(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreUserColorSetting(void)
{
    g_stColorProcData = tColorTempDefaultData[_CT_USER];
    RTDEepromSaveColorSetting(_CT_USER);
}

//--------------------------------------------------
// Description  : Load brightness/contrast from EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdInputSourceData(BYTE ucSource)
{
    ucSource = ucSource;
}

//--------------------------------------------------
// Description  : Save brightness/contrast to EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOsdInputSourceData(BYTE ucSource)
{
    ucSource = ucSource;
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOsdInputSourceData(void)
{
}

//--------------------------------------------------
// Description  : Load input port data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdInputPortData(BYTE ucPort)
{
    if(ucPort >= _OSD_INPUT_AMOUNT)
    {
        ucPort = 0;
    }

    UserCommonEepromRead(_OSD_PORT_ADDRESS + ucPort * sizeof(StructOsdInputPortDataType), sizeof(StructOsdInputPortDataType), (BYTE *)(&(g_pstOsdInputPortData[ucPort])));
}

//--------------------------------------------------
// Description  : Save input port data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOsdInputPortData(BYTE ucPort)
{
    if(ucPort >= _OSD_INPUT_AMOUNT)
    {
        ucPort = 0;
    }

    UserCommonEepromWrite(_OSD_PORT_ADDRESS + ucPort * sizeof(StructOsdInputPortDataType), sizeof(StructOsdInputPortDataType), (BYTE *)(&(g_pstOsdInputPortData[ucPort])));
}

//--------------------------------------------------
// Description  : Load default input port data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOsdInputPortData(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _OSD_INPUT_AMOUNT; ucTemp++)
    {
        g_pstOsdInputPortData[ucTemp] = tOsdInputPortDataDefault[ucTemp];
        RTDEepromSaveOsdInputPortData(ucTemp);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion)
{
    WORD usAddr = 0;

    ucRegion = ucRegion;
    usAddr = _OSD_REGION_ADDRESS + ((ucDisplayModesel * 2) * sizeof(StructOsdRegionDataType));
/*
    switch(ucDisplayModesel)
    {
        case _OSD_DM_1P:
            usAddr = _OSD_REGION_ADDRESS;
            break;

        case _OSD_DM_2P_LR:
            usAddr = _OSD_REGION_ADDRESS + (2 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_TB:
            usAddr = _OSD_REGION_ADDRESS + (4 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_PIP:
            usAddr = _OSD_REGION_ADDRESS + (6 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_3P_FLAG:
            usAddr = _OSD_REGION_ADDRESS + (8 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_3P_SKEW_L:
            usAddr = _OSD_REGION_ADDRESS + (10 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_3P_SKEW_R:
            usAddr = _OSD_REGION_ADDRESS + (12 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_4P:
            usAddr = _OSD_REGION_ADDRESS + (14 * sizeof(StructOsdRegionDataType));
            break;

        default:
            break;
    }
*/
    UserCommonEepromRead(usAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_INSIDE]));

    if(ucDisplayModesel <= _OSD_DM_4P)
    {
        usAddr += sizeof(StructOsdRegionDataType);
        UserCommonEepromRead(usAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_OUTSIDE]));
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromSaveOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion)
{
    WORD usAddr = 0;

    ucRegion = ucRegion;
    usAddr = _OSD_REGION_ADDRESS + ((ucDisplayModesel * 2) * sizeof(StructOsdRegionDataType));
/*
    switch(ucDisplayModesel)
    {
        case _OSD_DM_1P:
            usAddr = _OSD_REGION_ADDRESS+ ((ucDisplayModesel*2) * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_LR:
            usAddr = _OSD_REGION_ADDRESS + (2 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_TB:
            usAddr = _OSD_REGION_ADDRESS + (4 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_PIP:
            usAddr = _OSD_REGION_ADDRESS + (6 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_3P_FLAG:
            usAddr = _OSD_REGION_ADDRESS + (8 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_3P_SKEW_L:
            usAddr = _OSD_REGION_ADDRESS + (10 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_3P_SKEW_R:
            usAddr = _OSD_REGION_ADDRESS + (12 * sizeof(StructOsdRegionDataType));
            break;
        case _OSD_DM_3P_SKEW_T:
            usAddr = _OSD_REGION_ADDRESS + (14 * sizeof(StructOsdRegionDataType));
            break;
        case _OSD_DM_3P_SKEW_B:
            usAddr = _OSD_REGION_ADDRESS + (16 * sizeof(StructOsdRegionDataType));
            break;
        case _OSD_DM_4P:
            usAddr = _OSD_REGION_ADDRESS + (18 * sizeof(StructOsdRegionDataType));
            break;

        default:
            break;
    }
*/
    UserCommonEepromWrite(usAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_INSIDE]));

    if(ucDisplayModesel <= _OSD_DM_4P)
    {
        usAddr += sizeof(StructOsdRegionDataType);
        UserCommonEepromWrite(usAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_OUTSIDE]));
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromRestoreOsdRegionData(void)
{
    BYTE ucDisplayModeTemp = 0;

    for(ucDisplayModeTemp = 0; ucDisplayModeTemp < _OSD_DM_AMOUNT; ucDisplayModeTemp++)
    {
        switch(ucDisplayModeTemp)
        {
            case _OSD_DM_1P:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_1P_FULL)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[(RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_1P_FULL) + 1)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_1P_FULL);
                break;

            case _OSD_DM_2P_LR:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_LR_L)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_LR_R)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_LR_L);
                break;

            case _OSD_DM_2P_TB:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_TB_T)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_TB_B)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_TB_T);
                break;

            case _OSD_DM_2P_PIP:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_PIP_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_PIP_SUB)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_PIP_MAIN);
                break;
            case _OSD_DM_3P_FLAG:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_FLAG_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_FLAG_MAIN_OUT)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_FLAG_MAIN);
                break;

            case _OSD_DM_3P_SKEW_L:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_L_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_L_MAIN_OUT)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_SKEW_L_MAIN);
                break;

            case _OSD_DM_3P_SKEW_R:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_R_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_R_MAIN_OUT)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_SKEW_R_MAIN);
                break;
            case _OSD_DM_3P_SKEW_T:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_T_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_T_MAIN_OUT)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_SKEW_T_MAIN);
                break;
            case _OSD_DM_3P_SKEW_B:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_B_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_B_MAIN_OUT)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_SKEW_B_MAIN);
                break;

            case _OSD_DM_4P:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_4P_LT_INSIDE)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_4P_LT_OUTSIDE)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_4P_LT_INSIDE);
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromLoadOsdDisplayModeData(BYTE ucDisplayMode)
{
    UserCommonEepromRead(_OSD_DISPLAY_MODE_ADDRESS + ucDisplayMode * sizeof(StructOsdDisplayModeDataType), sizeof(StructOsdDisplayModeDataType), (BYTE *)(&g_stOsdDisplayModeData));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromSaveOsdDisplayModeData(BYTE ucDisplayMode)
{
    UserCommonEepromWrite(_OSD_DISPLAY_MODE_ADDRESS + ucDisplayMode * sizeof(StructOsdDisplayModeDataType), sizeof(StructOsdDisplayModeDataType), (BYTE *)(&g_stOsdDisplayModeData));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromRestoreOsdDisplayModeData(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _OSD_DM_AMOUNT; ucTemp++)
    {
        g_stOsdDisplayModeData = tOsdDisplayModeDataDefault[ucTemp];
        RTDEepromSaveOsdDisplayModeData(ucTemp);
    }
}

//    void RTDEepromRestoreSixColorData(void);
//    {
//
//    }
//
//    void RTDEepromSavePanelUsedTimeData(void);
//    {
//
//    }
//
#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load Audio Arc Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadAudioArcData(void)
{
    UserCommonEepromRead(_OSD_AUDIO_ARC_ADDRESS, sizeof(StructOsdUserDataArcDataType), (BYTE *)(&g_stAudioArcData));
}

//--------------------------------------------------
// Description  : Save Audio Arc Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveAudioArcData(void)
{
    UserCommonEepromWrite(_OSD_AUDIO_ARC_ADDRESS, sizeof(StructOsdUserDataArcDataType), (BYTE *)(&g_stAudioArcData));
}

//--------------------------------------------------
// Description  : Restore Audio Arc Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreAudioArcData(void)
{
    g_stAudioArcData = g_stAudioArcDataDefault;
    RTDEepromSaveAudioArcData();
}
#endif

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Get the free page number of flash
// Input Value  : None
// Output Value : Free page index
//--------------------------------------------------
BYTE RTDFlashGetFreePage(void)
{
    BYTE ucPageID = _START_OF_PAGEID;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    // If the _END_PAGE page has the biggest move count, suppose first page is free page
    if(g_ulFlashMoveCount > 0)
    {
        if(g_ucFlashLastPage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
        {
            ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
        }
        else
        {
            ucFreePage = g_ucFlashLastPage + 1;
        }
    }

    // Check the supposed free page is actual free page which has not been used ever
    do
    {
        if(ucFreePage == g_pucFlashPageArr[ucPageID])
        {
            if(ucFreePage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
            {
                ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
            }
            else
            {
                ucFreePage += 1;
            }

            ucPageID = _START_OF_PAGEID;
        }
        else
        {
            ucPageID++;
        }
    }
    while(ucPageID <= _END_OF_PAGEID);

    return ucFreePage;
}

//--------------------------------------------------
// Description  : Check the page is vaild or not
// Input Value  : ucPage: The page to be check, must between 0 and (_END_PAGE - _START_PAGE)
// Output Value : _TRUE means the page is valid, _FLASE is invalid
//--------------------------------------------------
bit RTDFlashIsPageInfoValid(BYTE ucPage)
{
    WORD usPageInfoAddr = ucPage * _FLASH_PAGE_SIZE;
    BYTE ucPageInfoChecksum = 0;
    BYTE pucPageInfo[5] = {0};
    BYTE pucPageInfoTemp[4] = {0};

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageInfoAddr + _PAGEINFO_CHECKSUM_ADDR, 5, pucPageInfo);
    pucPageInfoTemp[0] = pucPageInfo[1];
    pucPageInfoTemp[1] = pucPageInfo[2];
    pucPageInfoTemp[2] = pucPageInfo[3];
    pucPageInfoTemp[3] = pucPageInfo[4];
    ucPageInfoChecksum = UserCommonFlashCalculateCheckSumData(pucPageInfoTemp, 4);
    ucPageInfoChecksum = (ucPageInfoChecksum & 0x7F);

    if(ucPageInfoChecksum == pucPageInfo[0])
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial data page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialDataPage(BYTE ucPageID)
{
    WORD usAddr = _SYSTEM_EEPROM_EMULATION_START_PAGE * _FLASH_PAGE_SIZE;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucVersionCode = 0;
    BYTE ucChecksum = 0;

    ucFreePage = RTDFlashGetFreePage();
    // Initial page index
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Initial address
    g_pusFlashAddrArr[ucPageID] = 0;
    // Initial move count
    if(g_ulFlashMoveCount == 0xFFFFFF)
    {
        g_ulFlashMoveCount = 0x01;
    }
    else
    {
        g_ulFlashMoveCount++;
    }

    g_ucFlashLastPage = ucFreePage;

    usAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;
    UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID]);

    {
        BYTE pucBuffer[5] = {0};
        pucBuffer[0] = ucPageID;
        pucBuffer[1] = (BYTE)(g_ulFlashMoveCount >> 16);
        pucBuffer[2] = (BYTE)(g_ulFlashMoveCount >> 8);
        pucBuffer[3] = (BYTE)g_ulFlashMoveCount;
        pucBuffer[4] = UserCommonFlashCalculateCheckSumData(pucBuffer, 4);
        pucBuffer[4] = (pucBuffer[4] & 0x7F);

        ucVersionCode = _VERSION_CODE;
        ucChecksum = _CHECKSUM;

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_PAGEID_ADDR, 4, pucBuffer);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_CHECKSUM_ADDR, 1, &pucBuffer[4]);
    }
}

//--------------------------------------------------
// Description  : Search the last saved item address, and next new item position
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD RTDFlashSearchPageAddr(BYTE ucPageID)
{
    WORD usItemAddr = 0;
    WORD usPageAddr = 0;

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the last data item address
    for(usItemAddr = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usItemAddr > 0; usItemAddr--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + (usItemAddr - 1) * _DATA_ITEM_LENGTH, 1, pData);
        if(pData[0] != 0xFF)
        {
            return usItemAddr;
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  : Flash address initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialAddr(void)
{
    BYTE ucCnt = 0;
    WORD usAddr = 0;
    DWORD ulMoveCount = 0;
    BYTE ucPageID = 0;
    BYTE pucData[4] = {0};
    DWORD ulMoveCountTemp = 0;

    g_ulFlashMoveCount = 0;
    g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        g_pucFlashPageArr[ucPageID] = 0xFF;
    }

    // Find the page whose move count is the biggest and get the max move count
    for(ucCnt = _SYSTEM_EEPROM_EMULATION_START_PAGE; ucCnt < (_SYSTEM_EEPROM_EMULATION_END_PAGE + 1); ucCnt++)
    {
        // Check the page is valid or not
        if(RTDFlashIsPageInfoValid(ucCnt) == _TRUE)
        {
            usAddr = ucCnt * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR;

            // Get the move count of current page
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 4, pucData);
            ulMoveCount = TO_DWORD(0, pucData[1], pucData[2], pucData[3]);

            // Get the max move count and its page index, ulMoveCount Only 3 Bytes, extra Judge 0xFFFFFF < 0x000001 Case
            if(((ulMoveCount >= g_ulFlashMoveCount) && (!((ulMoveCount == 0xFFFFFF) && (g_ulFlashMoveCount == 0x01)))) ||
               ((ulMoveCount < g_ulFlashMoveCount) && ((ulMoveCount == 0x01) && (g_ulFlashMoveCount == 0xFFFFFF))))
            {
                g_pucFlashPageArr[pucData[0]] = ucCnt;
                g_ulFlashMoveCount = ulMoveCount;
                g_ucFlashLastPage = ucCnt;
            }
            // Check Other vaild page index
            else
            {
                if(g_pucFlashPageArr[pucData[0]] == 0xFF)
                {
                    g_pucFlashPageArr[pucData[0]] = ucCnt;
                }
                else // Check which page have begger Movecount
                {
                    usAddr = g_pucFlashPageArr[pucData[0]] * _FLASH_PAGE_SIZE + _PAGEINFO_MOVECOUNT_ADDR;
                    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 3, &pucData[1]);
                    ulMoveCountTemp = TO_DWORD(0, pucData[1], pucData[2], pucData[3]);
                    if(((ulMoveCount >= ulMoveCountTemp) && (!((ulMoveCount == 0xFFFFFF) && (ulMoveCountTemp == 0x01)))) ||
                       ((ulMoveCount < ulMoveCountTemp) && ((ulMoveCount == 0x01) && (ulMoveCountTemp == 0xFFFFFF))))
                    {
                        g_pucFlashPageArr[pucData[0]] = ucCnt;
                    }
                }
            }
        }
    }

    // If this page is missing, intial this single page
    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        if(g_pucFlashPageArr[ucPageID] == 0xFF)
        {
            // This function will increase g_ulFlashMovePage,and now g_ucFlashLastPage is the page index which has the biggest move count value
            RTDFlashInitialDataPage(ucPageID);
            RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
        }
        else
        {
            // Initial g_pusFlashAddrArr
            g_pusFlashAddrArr[ucPageID] = RTDFlashSearchPageAddr(ucPageID);
        }
    }
}

//--------------------------------------------------
// Description  : Get the checksum and version code from flash
// Input Value  : pucChecksum: the checksum get from flash
//                pucVersionCode: the version code get from flash
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode)
{
    // Get the checksum and version code
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, pucChecksum);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, pucVersionCode);
}

//--------------------------------------------------
// Description  : Save the checksum & version code to flash
// Input Value  : ucChecksum, checksum value
//                ucVersionCode, version code value
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode)
{
    BYTE ucVersionCodeRead = 0;
    BYTE ucChecksumRead = 0;

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCodeRead);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksumRead);

    // Do not need save checksum or version code
    if((ucVersionCode == ucVersionCodeRead) && (ucChecksum == ucChecksumRead))
    {
        return;
    }
    // Need to save version code and checksum in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save version code in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum == ucChecksumRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
    }
    // Need to save checksum in current page
    else if((ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF) && (ucVersionCode == ucVersionCodeRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save checksum and version code to free page
    else
    {
        memset(pData, 0xFF, _DATA_ITEM_LENGTH);
        RTDFlashMoveData(_CHECKSUM_VERSIONCODE_ID, pData);

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
}

//--------------------------------------------------
// Description  : Move data to another page of flash
// Input Value  : ucPageID: previous page ID
//                pucData: data to be saved
// Output Value : _FAIL/_SUCCESS
//--------------------------------------------------
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData)
{
    BYTE ucPrevPage = g_pucFlashPageArr[ucPageID];
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucItemIndex = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usPrevPageAddr = 0;
    WORD usMovedItemCount = 0;
    WORD usMovedAddrIndex = 0;
    BYTE ucItemID = 0;
    BYTE ucChecksum = 0xFF;
    BYTE ucVersioncode = 0xFF;

    // Load checksum and version code
    if(pucData[0] != 0xFF)
    {
        RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersioncode);
    }

    // Get free page data will move to
    ucFreePage = RTDFlashGetFreePage();

    // First sector erase the free page specified by g_ucFlashFreePage
    if(UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage) == _FALSE)
    {
        return _FALSE;
    }

    // Save the latest data item to the new page if need, when save checksum and version, it is not necessary
    // We do not save the item id at last because page info has not been saved
    if(pucData[0] != 0xFF)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage * _FLASH_PAGE_SIZE + ucItemIndex, _DATA_ITEM_LENGTH, pucData);

        // Clear Buffer
        memset(pucData, 0xFF, _DATA_ITEM_LENGTH);

        // And then load the latest data items which saved in the old full page to the new page from bottom to top
        usMovedItemCount = 1;
    }
    else
    {
        usMovedItemCount = 0;
    }

    // Update ucFlashPage
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Update move count value
    if(g_ulFlashMoveCount == 0xFFFFFF)
    {
        g_ulFlashMoveCount = 0x01;
    }
    else
    {
        g_ulFlashMoveCount++;
    }

    g_ucFlashLastPage = ucFreePage;

    usPrevPageAddr = ucPrevPage * _FLASH_PAGE_SIZE;
    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the valid item and move to new free page
    for(usAddrIndex = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usAddrIndex > 0; usAddrIndex--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, 1, &ucItemID);

        if(ucItemID != 0xFF)
        {
            // Check the item has been moved or not by item ID
            for(usMovedAddrIndex = 0; usMovedAddrIndex < usMovedItemCount; usMovedAddrIndex++)
            {
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedAddrIndex * _DATA_ITEM_LENGTH, 1, pData);
                if(pData[0] == ucItemID)
                {
                    break;
                }
            }

            if(usMovedAddrIndex >= usMovedItemCount)
            {
                // The item has not been moved, then check the item is valid or not
                pucData[15] = 0;
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, _DATA_ITEM_LENGTH - 1, pData);
                pucData[15] = UserCommonFlashCalculateCheckSumData(pData, (_DATA_ITEM_LENGTH - 1));
                pucData[15] = (pucData[15] & 0x7F);

                // Check the checksum
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + usAddrIndex * _DATA_ITEM_LENGTH - 1, 1, pData);
                if(pucData[15] != pData[0])
                {
                    // Checksum check fail, the item is invalid
                    continue;
                }

                // Move the item to new free page
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);
                UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedItemCount * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);

                usMovedItemCount++;
            }
        }
    }

    // Update the data item address in the new page
    g_pusFlashAddrArr[ucPageID] = usMovedItemCount;

    // Last update the new moved page info fields
    // Save checksum & version code
    if(ucPageID == _CHECKSUM_VERSIONCODE_ID)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersioncode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }

    // Save page info
    {
        BYTE pucBuffer[5] = {0};
        pucBuffer[0] = ucPageID;
        pucBuffer[1] = (BYTE)(g_ulFlashMoveCount >> 16);
        pucBuffer[2] = (BYTE)(g_ulFlashMoveCount >> 8);
        pucBuffer[3] = (BYTE)g_ulFlashMoveCount;
        pucBuffer[4] = UserCommonFlashCalculateCheckSumData(pucBuffer, 4);
        pucBuffer[4] = (pucBuffer[4] & 0x7F);

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR, 4, pucBuffer);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_CHECKSUM_ADDR, 1, &pucBuffer[4]);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Flash check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashStartup(void)
{
    BYTE ucChecksum = 0;
    BYTE ucVersionCode = 0;
    BYTE ucPageID = 0;
    BYTE pucBuffer[1] = {0};

    RTDFlashInitialAddr();

    // Get FW checksum and version code
    RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersionCode);

    if(ucChecksum != _CHECKSUM)
    {
        // Checksum is changed, load default value and save to flash
        for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
        {
            RTDFlashInitialDataPage(ucPageID);
        }

        RTDFlashWholeRestore();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashRestorePanelIndex();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
    else if(ucVersionCode != _VERSION_CODE)
    {
        // Restore CT User color setting
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + _CT_USER, pucBuffer, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(_CT_USER);
        }

        UserCommonFlashRestoreSystemData();
        RTDFlashRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
        UserCommonFlashRestoreModeUserData();
#endif

        RTDFlashRestoreOsdInputSourceData();
#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
        RTDFlashRestoreAudioArcData();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
    else
    {
        UserCommonFlashLoadSystemData();
        RTDFlashLoadOSDData();

        RTDFlashLoadOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
        RTDFlashLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), _PCM_OSD_NATIVE);
            RTDFlashSaveOSDData();
        }
#if(_AUDIO_ARC_SUPPORT == _ON)
        RTDFlashLoadAudioArcData();
#endif
    }

    // Load port settings
    {
        BYTE ucIndex = 0;
        for(ucIndex = 0; ucIndex < _OSD_INPUT_AMOUNT; ++ucIndex)
        {
            RTDFlashLoadOsdInputPortData(ucIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Load default data and save to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashWholeRestore(void)
{
    UserCommonFlashRestoreSystemData();

#if(_VGA_SUPPORT == _ON)
    UserCommonFlashRestoreModeUserData();
    UserCommonFlashRestoreADCSetting();
#endif

    // Osd user data
    RTDFlashRestoreOSDData();

    // color temp
    RTDFlashRestoreColorSetting();
    RTDFlashRestoreUserColorSetting();

    // osd input source
    RTDFlashRestoreOsdInputSourceData();

    // osd input port
    RTDFlashRestoreOsdInputPortData();

    // osd region data
    RTDFlashRestoreOsdRegionData();

    // osd display mode
    RTDFlashRestoreOsdDisplayModeData();

#if(_AUDIO_ARC_SUPPORT == _ON)
    RTDFlashRestoreAudioArcData();
#endif
}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreBacklight(void)
{
    BYTE ucItemOffset = 0;
    BYTE pucBuffer[1] = {0};

    SET_OSD_BACKLIGHT(g_stOsdUserDataDefault.usBackLight);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pucBuffer, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);
    BYTE pucBuffer[_DATA_ITEM_LENGTH - 2];

    memset(pucBuffer, 0, sizeof(pucBuffer));

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pucBuffer, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            g_stOsdUserData = g_stOsdUserDataDefault;
            return;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((((BYTE *)(&g_stOsdUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pucBuffer, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((((BYTE *)(&g_stOsdUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pucBuffer, ucStructLen);
            break;
        }
    }
}


//--------------------------------------------------
// Description  : Save OSD data to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOSDData(void)
{
    // check flash size for user data
    static_assert(((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)) <= (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1),
                  "sizeof(StructOsdUserDataType) too large");

    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOsdUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOsdUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE pucBuffer[1] = {0};

    g_stOsdUserData = g_stOsdUserDataDefault;

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pucBuffer, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load color settings from Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadColorSetting(BYTE ucRegion)
{
    BYTE pucData[6];
    memset(pucData, 0, sizeof(pucData));

#if(_OGC_FUNCTION == _ON)
    if(GET_OSD_GAMMA(ucRegion) != _GAMMA_OFF)
    {
        UserCommonColorGetOGCColorTempGain(GET_COLOR_TEMP_TYPE(ucRegion), (GET_OSD_GAMMA(ucRegion) - 1), pucData, _OGC_NORMAL_TYPE);

        g_stColorProcData.usColorTempR = TO_WORD(pucData[0], pucData[1]);
        g_stColorProcData.usColorTempG = TO_WORD(pucData[2], pucData[3]);
        g_stColorProcData.usColorTempB = TO_WORD(pucData[4], pucData[5]);
    }
    else
#elif(_OCC_PCM_GAMMA_SUPPORT == _ON)
    if(GET_OSD_GAMMA(ucRegion) != _GAMMA_OFF)
    {
        g_stColorProcData.usColorTempR = 0x800;
        g_stColorProcData.usColorTempG = 0x800;
        g_stColorProcData.usColorTempB = 0x800;
    }
    else
#endif
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + GET_COLOR_TEMP_TYPE(ucRegion), pucData, sizeof(StructColorProcDataType)) == _TRUE)
        {
            g_stColorProcData.usColorTempR = TO_WORD(pucData[0], pucData[1]);
            g_stColorProcData.usColorTempG = TO_WORD(pucData[2], pucData[3]);
            g_stColorProcData.usColorTempB = TO_WORD(pucData[4], pucData[5]);
        }
        else
        {
            g_stColorProcData = tColorTempDefaultData[GET_COLOR_TEMP_TYPE(ucRegion)];
        }
    }
}

//--------------------------------------------------
// Description  : Save color settings to Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveColorSetting(BYTE ucColorTempType)
{
    static_assert(sizeof(StructColorProcDataType) <= (_DATA_ITEM_LENGTH - 2), "sizeof(StructColorProcDataType) too large");

    BYTE pucBuffer[sizeof(StructColorProcDataType)];
    memset(pucBuffer, 0, sizeof(pucBuffer));

    pucBuffer[0] = HIBYTE(g_stColorProcData.usColorTempR);
    pucBuffer[1] = LOBYTE(g_stColorProcData.usColorTempR);
    pucBuffer[2] = HIBYTE(g_stColorProcData.usColorTempG);
    pucBuffer[3] = LOBYTE(g_stColorProcData.usColorTempG);
    pucBuffer[4] = HIBYTE(g_stColorProcData.usColorTempB);
    pucBuffer[5] = LOBYTE(g_stColorProcData.usColorTempB);

    UserCommonFlashSaveItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempType, pucBuffer, sizeof(StructColorProcDataType));
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreColorSetting(void)
{
    BYTE ucColorTempIndex = 0;
    BYTE pucBuffer[1] = {0};

    for(ucColorTempIndex = 0; ucColorTempIndex < _CT_COLORTEMP_AMOUNT; ucColorTempIndex++)
    {
        g_stColorProcData = tColorTempDefaultData[ucColorTempIndex];

        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempIndex, pucBuffer, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(ucColorTempIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreUserColorSetting(void)
{
    StructColorProcDataType stUserColorTemp = {0};
    BYTE pucBuffer[1] = {0};

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC5_USER, pucBuffer, 1) == _TRUE)
    {
        stUserColorTemp = g_stColorProcData;
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        RTDFlashSaveColorSetting(_CT_USER);
        g_stColorProcData = stUserColorTemp;
    }
}

//--------------------------------------------------
// Description  : Load Input Source from Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOsdInputSourceData(BYTE ucSource)
{
    ucSource = ucSource;
}

//--------------------------------------------------
// Description  : Save Input Source from Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOsdInputSourceData(BYTE ucSource)
{
    ucSource = ucSource;
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOsdInputSourceData(void)
{
}

//--------------------------------------------------
// Description  : Load Input Port Data
// Input Value  : ucPort --> Input Port
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOsdInputPortData(BYTE ucPort)
{
    if(ucPort >= _OSD_INPUT_AMOUNT)
    {
        ucPort = 0;
    }

    BYTE pucBuffer[sizeof(StructOsdInputPortDataType)];
    memset(pucBuffer, 0, sizeof(pucBuffer));

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_INPUT_A_PORT + ucPort, pucBuffer, sizeof(StructOsdInputPortDataType)) == _TRUE)
    {
        memcpy(&(g_pstOsdInputPortData[ucPort]), pucBuffer, sizeof(StructOsdInputPortDataType));
    }
    else
    {
        g_pstOsdInputPortData[ucPort] = tOsdInputPortDataDefault[ucPort];
    }
}

//--------------------------------------------------
// Description  : Save Input Port Data
// Input Value  : ucPort --> Input Port
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOsdInputPortData(BYTE ucPort)
{
    static_assert(sizeof(StructOsdInputPortDataType) <= (_DATA_ITEM_LENGTH - 2), "sizeof(StructOsdInputPortDataType) too large");

    if(ucPort >= _OSD_INPUT_AMOUNT)
    {
        ucPort = 0;
    }

    UserCommonFlashSaveItem(_FLASH_ITEMID_INPUT_A_PORT + ucPort, (BYTE *)(&(g_pstOsdInputPortData[ucPort])), sizeof(StructOsdInputPortDataType));
}

//--------------------------------------------------
// Description  : Retore Input Port Data
// Input Value  : ucPort --> Input Port
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOsdInputPortData(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _OSD_INPUT_AMOUNT; ucTemp++)
    {
        g_pstOsdInputPortData[ucTemp] = tOsdInputPortDataDefault[ucTemp];
        RTDFlashSaveOsdInputPortData(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Load Display Mode Data
// Input Value  : ucDisplayMode --> Display mode
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOsdDisplayModeData(BYTE ucDisplayMode)
{
    BYTE pucBuffer[sizeof(StructOsdDisplayModeDataType)];
    memset(pucBuffer, 0, sizeof(pucBuffer));

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_OSD_DM_1P + ucDisplayMode, pucBuffer, sizeof(StructOsdDisplayModeDataType)) == _TRUE)
    {
        memcpy(&g_stOsdDisplayModeData, pucBuffer, sizeof(StructOsdDisplayModeDataType));
    }
    else
    {
        g_stOsdDisplayModeData = tOsdDisplayModeDataDefault[ucDisplayMode];
    }
}

//--------------------------------------------------
// Description  : Save Display Mode Data
// Input Value  : ucDisplayMode --> Display mode
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOsdDisplayModeData(BYTE ucDisplayMode)
{
    static_assert(sizeof(StructOsdDisplayModeDataType) <= (_DATA_ITEM_LENGTH - 2), "sizeof(StructOsdDisplayModeDataType) too large");
    UserCommonFlashSaveItem(_FLASH_ITEMID_OSD_DM_1P + ucDisplayMode, (BYTE *)(&g_stOsdDisplayModeData), sizeof(StructOsdDisplayModeDataType));
}

//--------------------------------------------------
// Description  : Restore Display Mode Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOsdDisplayModeData(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _OSD_DM_AMOUNT; ucTemp++)
    {
        g_stOsdDisplayModeData = tOsdDisplayModeDataDefault[ucTemp];
        RTDFlashSaveOsdDisplayModeData(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Load One Group OSD data from Flash
// Input Value  : usAddr: address in ucBank
//                ucLength: the data length to save
//                pucData: data buffer to save
// Output Value : return _TRUE if load success, else return _FALSE
//--------------------------------------------------
bit RTDFlashLoadOSDDataGroup(WORD usAddr, WORD usLength, BYTE *pucData)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = usLength;
    BYTE pucBuffer[_DATA_ITEM_LENGTH - 2];

    memset(pucBuffer, 0, sizeof(pucBuffer));

    for(ucItemOffset = 0; ucItemOffset < ((usLength + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // 2 expression the Flash date item ID length for one group data stucture
        if(ucItemOffset > 2)
        {
            break;
        }

        if(UserCommonFlashLoadItem((usAddr + ucItemOffset), pucBuffer, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            // g_stOSDUserData = g_stOSDDefaultData;
            return _FALSE;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((pucData + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pucBuffer, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((pucData + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pucBuffer, ucStructLen);
            break;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Save One Group OSD data to Flash
// Input Value  : usAddr: address in ucBank
//                pucData: data buffer to save
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOSDDataGroup(WORD usAddr, WORD usLength, BYTE *pucData)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = usLength;

    for(ucItemOffset = 0; ucItemOffset < ((usLength + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        if(ucItemOffset > 2)
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((usAddr + ucItemOffset), (pucData + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((usAddr + ucItemOffset), (pucData + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Load Osd Region Type
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : _INSIDE / _OUTSIDE
//--------------------------------------------------
void RTDFlashLoadOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion)
{
    BYTE ucItemAddr = 0;
    BYTE ucRegionInx = 0;

    ucRegion = ucRegion;

    switch(ucDisplayMode)
    {
        case _OSD_DM_1P:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START;
            ucRegionInx = 0;
            break;

        case _OSD_DM_2P_LR:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 4;
            ucRegionInx = 2;
            break;

        case _OSD_DM_2P_TB:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 8;
            ucRegionInx = 4;
            break;

        case _OSD_DM_2P_PIP:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 12;
            ucRegionInx = 6;
            break;

        case _OSD_DM_3P_FLAG:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 16;
            ucRegionInx = 8;
            break;

        case _OSD_DM_3P_SKEW_L:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 20;
            ucRegionInx = 10;
            break;

        case _OSD_DM_3P_SKEW_R:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 24;
            ucRegionInx = 12;
            break;
        case _OSD_DM_3P_SKEW_T:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 28;
            ucRegionInx = 14;
            break;

        case _OSD_DM_3P_SKEW_B:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 32;
            ucRegionInx = 16;
            break;

        case _OSD_DM_4P:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 36;
            ucRegionInx = 18;
            break;

        default:
            break;
    }

    if(RTDFlashLoadOSDDataGroup(ucItemAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_INSIDE])) == _FALSE)
    {
        g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[ucRegionInx];
    }

    if(ucDisplayMode <= _OSD_DM_4P)
    {
        ucItemAddr += 2;

        if(RTDFlashLoadOSDDataGroup(ucItemAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_OUTSIDE])) == _FALSE)
        {
            g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[ucRegionInx + 1];
        }
    }
}

//--------------------------------------------------
// Description  : Save Osd Region Type
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion)
{
    // check flash size for region data
    static_assert(((sizeof(StructOsdRegionDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)) <= 4,
                  "sizeof(StructOsdRegionDataType) too large");

    BYTE ucItemAddr = 0;

    ucRegion = ucRegion;

    switch(ucDisplayMode)
    {
        case _OSD_DM_1P:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START;
            break;

        case _OSD_DM_2P_LR:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 4;
            break;

        case _OSD_DM_2P_TB:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 8;
            break;

        case _OSD_DM_2P_PIP:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 12;
            break;

        case _OSD_DM_3P_FLAG:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 16;
            break;

        case _OSD_DM_3P_SKEW_L:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 20;
            break;

        case _OSD_DM_3P_SKEW_R:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 24;
            break;

        case _OSD_DM_3P_SKEW_T:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 28;
            break;

        case _OSD_DM_3P_SKEW_B:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 32;
            break;

        case _OSD_DM_4P:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 36;
            break;

        default:
            break;
    }

    RTDFlashSaveOSDDataGroup(ucItemAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_INSIDE]));

    if(ucDisplayMode <= _OSD_DM_4P)
    {
        ucItemAddr += 2;
        RTDFlashSaveOSDDataGroup(ucItemAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_OUTSIDE]));
    }
}

//--------------------------------------------------
// Description  : Retore Osd Region Type
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : _INSIDE / _OUTSIDE
//--------------------------------------------------
void RTDFlashRestoreOsdRegionData(void)
{
    BYTE ucDisplayModeTemp = 0;

    for(ucDisplayModeTemp = 0; ucDisplayModeTemp < _OSD_DM_AMOUNT; ucDisplayModeTemp++)
    {
        switch(ucDisplayModeTemp)
        {
            case _OSD_DM_1P:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_1P_FULL)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[(RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_1P_FULL) + 1)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_1P_FULL);
                break;

            case _OSD_DM_2P_LR:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_LR_L)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_LR_R)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_LR_L);
                break;

            case _OSD_DM_2P_TB:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_TB_T)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_TB_B)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_TB_T);
                break;

            case _OSD_DM_2P_PIP:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_PIP_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_PIP_SUB)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_PIP_MAIN);
                break;

            case _OSD_DM_3P_FLAG:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_FLAG_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_FLAG_MAIN_OUT)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_FLAG_MAIN);
                break;

            case _OSD_DM_3P_SKEW_L:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_L_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_L_MAIN_OUT)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_SKEW_L_MAIN);
                break;

            case _OSD_DM_3P_SKEW_R:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_R_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_R_MAIN_OUT)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_SKEW_R_MAIN);
                break;
            case _OSD_DM_3P_SKEW_T:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_T_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_T_MAIN_OUT)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_SKEW_T_MAIN);
                break;

            case _OSD_DM_3P_SKEW_B:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_B_MAIN)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_3P_SKEW_B_MAIN_OUT)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_3P_SKEW_B_MAIN);
                break;

            case _OSD_DM_4P:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_4P_LT_INSIDE)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_4P_LT_OUTSIDE)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_4P_LT_INSIDE);
                break;

            default:
                break;
        }
    }
}

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Load panel index from flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadPanelIndex(void)
{
    BYTE pucBuffer[1] = {0};

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pucBuffer, 1) == _TRUE)
    {
        SET_MDOMAIN_PANEL_INDEX(pucBuffer[0]);
    }
    else
    {
        SET_MDOMAIN_PANEL_INDEX(0);
    }
}

//--------------------------------------------------
// Description  : Save panel index to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSavePanelIndex(void)
{
    BYTE ucPanelIndex = 0;

    ucPanelIndex = GET_MDOMAIN_PANEL_INDEX();

    UserCommonFlashSaveItem(_FLASH_ITEMID_PANEL_INDEX, &ucPanelIndex, 1);
}

//--------------------------------------------------
// Description  : Restore panel index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestorePanelIndex(void)
{
    BYTE pucBuffer[1] = {0};

    SET_MDOMAIN_PANEL_INDEX(0);

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pucBuffer, 1) == _TRUE)
    {
        RTDFlashSavePanelIndex();
    }
}
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load Audio Arc Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadAudioArcData(void)
{
    BYTE pucBuffer[sizeof(StructOsdInputPortDataType)];
    memset(pucBuffer, 0, sizeof(pucBuffer));

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_AUDIO_ARC, pucBuffer, sizeof(StructOsdUserDataArcDataType)) == _TRUE)
    {
        memcpy(&(g_stAudioArcData), pucBuffer, sizeof(StructOsdUserDataArcDataType));
    }
    else
    {
        g_pstOsdInputPortData = g_stAudioArcDataDefault;
    }
}

//--------------------------------------------------
// Description  : Save Audio Arc Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveAudioArcData(void)
{
    static_assert(sizeof(StructOsdUserDataArcDataType) <= (_DATA_ITEM_LENGTH - 2), "sizeof(StructOsdUserDataArcDataType) too large");

    UserCommonFlashSaveItem(_FLASH_ITEMID_AUDIO_ARC, (BYTE *)(&(g_stAudioArcData)), sizeof(StructOsdUserDataArcDataType));
}

//--------------------------------------------------
// Description  : Restore Audio Arc Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreAudioArcData(void)
{
    BYTE pucBuffer[1] = {0};

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_AUDIO_ARC, pucBuffer, 1) == _TRUE)
    {
        g_stAudioArcData = g_stAudioArcDataDefault;
        RTDFlashSaveAudioArcData();
    }
}
#endif
#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Transfer Osd Region Type
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : _INSIDE / _OUTSIDE
//--------------------------------------------------
BYTE RTDNVRamTransferOsdRegionType(BYTE ucDisplayMode, BYTE ucRegion)
{
    BYTE ucType = 0;

    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
        ucType = ucRegion % 2;
    }
    else
    {
        switch(ucDisplayMode)
        {
            case _OSD_DM_1P:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                if(GET_EAGLE_SIGHT_STATUS() == _ON)
                {
                    if(ucRegion == _OSD_SR_EAGLESIGHT_SUB)
                    {
                        ucType = _INSIDE;
                    }
                    else
                    {
                        ucType = _OUTSIDE;
                    }
                }
                else
#endif
                {
                    ucType = _INSIDE;
                }
                break;

            case _OSD_DM_2P_LR:
                if(ucRegion == _OSD_SR_2P_LR_R)
                {
                    ucType = _INSIDE;
                }
                else
                {
                    ucType = _OUTSIDE;
                }
                break;

            case _OSD_DM_2P_TB:
                if(ucRegion == _OSD_SR_2P_TB_B)
                {
                    ucType = _INSIDE;
                }
                else
                {
                    ucType = _OUTSIDE;
                }
                break;

            case _OSD_DM_2P_PIP:
                if(ucRegion == _OSD_SR_2P_PIP_SUB)
                {
                    ucType = _INSIDE;
                }
                else
                {
                    ucType = _OUTSIDE;
                }
                break;

            case _OSD_DM_3P_FLAG:
                switch(ucRegion)
                {
                    case _OSD_SR_3P_FLAG_MAIN:
                    case _OSD_SR_3P_FLAG_L:
                    case _OSD_SR_3P_FLAG_R:
                        ucType = _INSIDE;
                        break;

                    default:
                        ucType = _OUTSIDE;
                        break;
                }
                break;

            case _OSD_DM_3P_SKEW_L:
                switch(ucRegion)
                {
                    case _OSD_SR_3P_SKEW_L_MAIN:
                    case _OSD_SR_3P_SKEW_L_UP:
                    case _OSD_SR_3P_SKEW_L_DOWN:
                        ucType = _INSIDE;
                        break;

                    default:
                        ucType = _OUTSIDE;
                        break;
                }
                break;

            case _OSD_DM_3P_SKEW_R:
                switch(ucRegion)
                {
                    case _OSD_SR_3P_SKEW_R_MAIN:
                    case _OSD_SR_3P_SKEW_R_UP:
                    case _OSD_SR_3P_SKEW_R_DOWN:
                        ucType = _INSIDE;
                        break;

                    default:
                        ucType = _OUTSIDE;
                        break;
                }
                break;
            case _OSD_DM_3P_SKEW_T:
                switch(ucRegion)
                {
                    case _OSD_SR_3P_SKEW_T_MAIN:
                    case _OSD_SR_3P_SKEW_T_LEFT:
                    case _OSD_SR_3P_SKEW_T_RIGHT:
                        ucType = _INSIDE;
                        break;

                    default:
                        ucType = _OUTSIDE;
                        break;
                }
                break;
            case _OSD_DM_3P_SKEW_B:
                switch(ucRegion)
                {
                    case _OSD_SR_3P_SKEW_B_MAIN:
                    case _OSD_SR_3P_SKEW_B_LEFT:
                    case _OSD_SR_3P_SKEW_B_RIGHT:
                        ucType = _INSIDE;
                        break;

                    default:
                        ucType = _OUTSIDE;
                        break;
                }
                break;
            case _OSD_DM_4P:
                switch(ucRegion)
                {
                    case _OSD_SR_4P_LT_INSIDE:
                    case _OSD_SR_4P_LB_INSIDE:
                    case _OSD_SR_4P_RT_INSIDE:
                    case _OSD_SR_4P_RB_INSIDE:
                        ucType = _INSIDE;
                        break;

                    default:
                        ucType = _OUTSIDE;
                        break;
                }
                break;

            default:
                break;
        }
    }

    return ucType;
}

//--------------------------------------------------
// Description  : Transfer Osd Region index
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : _INSIDE / _OUTSIDE
//--------------------------------------------------
BYTE RTDNVRamTransferOsdRegionIndex(BYTE ucDisplayMode, BYTE ucRegion)
{
    BYTE ucIndex = 0;

    switch(ucDisplayMode)
    {
        case _OSD_DM_1P:
            ucIndex = 0;
            break;

        case _OSD_DM_2P_LR:
            if(ucRegion >= _OSD_SR_2P_LR_FULL)
            {
                ucRegion = _OSD_SR_2P_LR_L;
            }
            ucIndex = 2 + ucRegion;
            break;

        case _OSD_DM_2P_TB:
            if(ucRegion >= _OSD_SR_2P_TB_FULL)
            {
                ucRegion = _OSD_SR_2P_TB_T;
            }
            ucIndex = 4 + ucRegion;
            break;

        case _OSD_DM_2P_PIP:
            if(ucRegion >= _OSD_SR_2P_PIP_FULL)
            {
                ucRegion = _OSD_SR_2P_PIP_MAIN;
            }
            ucIndex = 6 + ucRegion;
            break;

        case _OSD_DM_3P_FLAG:
            if(ucRegion >= _OSD_SR_3P_FLAG_FULL)
            {
                ucRegion = _OSD_SR_3P_FLAG_MAIN;
            }
            ucIndex = 8 + (ucRegion % 2);
            break;

        case _OSD_DM_3P_SKEW_L:
            if(ucRegion >= _OSD_SR_3P_SKEW_L_FULL)
            {
                ucRegion = _OSD_SR_3P_SKEW_L_MAIN;
            }
            ucIndex = 10 + (ucRegion % 2);
            break;

        case _OSD_DM_3P_SKEW_R:
            if(ucRegion >= _OSD_SR_3P_SKEW_R_FULL)
            {
                ucRegion = _OSD_SR_3P_SKEW_R_MAIN;
            }
            ucIndex = 12 + (ucRegion % 2);
            break;
        case _OSD_DM_3P_SKEW_T:
            if(ucRegion >= _OSD_SR_3P_SKEW_T_FULL)
            {
                ucRegion = _OSD_SR_3P_SKEW_T_MAIN;
            }
            ucIndex = 14 + (ucRegion % 2);
            break;
        case _OSD_DM_3P_SKEW_B:
            if(ucRegion >= _OSD_SR_3P_SKEW_B_FULL)
            {
                ucRegion = _OSD_SR_3P_SKEW_B_MAIN;
            }
            ucIndex = 16 + (ucRegion % 2);
            break;
        case _OSD_DM_4P:
            if(ucRegion >= _OSD_SR_4P_FULL)
            {
                ucRegion = _OSD_SR_4P_LT_OUTSIDE;
            }
            ucIndex = 18 + (ucRegion % 2);
            break;

        default:
            break;
    }

    return ucIndex;
}
#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : get DVision mode data
// Input Value  : enumOSDDVisionDefDVisionMode --> DVision Picture mode
//                     enumOsdItemType --> DVision Mode parameters
// Output Value :value
//--------------------------------------------------
BYTE RTDNVRamGetDVisionModeData(WORD usOsdItemType, BYTE ucRegion)
{
    switch(GET_DVISION_PICTURE(GET_OSD_SELECT_REGION()))
    {
        default:
        case _OSD_DVISION_PICTURE_DARK:
            if(usOsdItemType == _OSD_DVISION_PICTURE)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.b1DVisionPictureModify);
            }
            if(usOsdItemType == _OSD_DVISION_BACKLIGHT)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.b7DVisionBacklight);
            }
            if(usOsdItemType == _OSD_DVISION_BRIGHTNESS)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.ucDVisionBrightness);
            }
            if(usOsdItemType == _OSD_DVISION_CONTRAST)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.ucDVisionContrast);
            }
            if(usOsdItemType == _OSD_DVISION_SATURATION)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.ucDVisionSaturation);
            }
            break;
        case _OSD_DVISION_PICTURE_BRIGHT:
            if(usOsdItemType == _OSD_DVISION_PICTURE)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.b1DVisionPictureModify);
            }
            if(usOsdItemType == _OSD_DVISION_BACKLIGHT)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.b7DVisionBacklight);
            }
            if(usOsdItemType == _OSD_DVISION_BRIGHTNESS)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.ucDVisionBrightness);
            }
            if(usOsdItemType == _OSD_DVISION_CONTRAST)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.ucDVisionContrast);
            }
            if(usOsdItemType == _OSD_DVISION_SATURATION)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.ucDVisionSaturation);
            }
            break;
        case _OSD_DVISION_PICTURE_GAME:
            if(usOsdItemType == _OSD_DVISION_PICTURE)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.b1DVisionPictureModify);
            }
            if(usOsdItemType == _OSD_DVISION_BACKLIGHT)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.b7DVisionBacklight);
            }
            if(usOsdItemType == _OSD_DVISION_BRIGHTNESS)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.ucDVisionBrightness);
            }
            if(usOsdItemType == _OSD_DVISION_CONTRAST)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.ucDVisionContrast);
            }
            if(usOsdItemType == _OSD_DVISION_SATURATION)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.ucDVisionSaturation);
            }
            break;
        case _OSD_DVISION_PICTURE_USER:
            if(usOsdItemType == _OSD_DVISION_PICTURE)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.b1DVisionPictureModify);
            }
            if(usOsdItemType == _OSD_DVISION_BACKLIGHT)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.b7DVisionBacklight);
            }
            if(usOsdItemType == _OSD_DVISION_BRIGHTNESS)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.ucDVisionBrightness);
            }
            if(usOsdItemType == _OSD_DVISION_CONTRAST)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.ucDVisionContrast);
            }
            if(usOsdItemType == _OSD_DVISION_SATURATION)
            {
                return (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.ucDVisionSaturation);
            }
            break;
    }
    return 0;
}
//--------------------------------------------------
// Description  : get DVision mode data
// Input Value  : enumOSDDVisionDefDVisionMode --> DVision Picture mode
//                     enumOsdItemType --> DVision Mode parameters
// Output Value :value
//--------------------------------------------------
void RTDNVRamSetDVisionModeData(WORD usOsdItemType, BYTE ucData, BYTE ucRegion)
{
    switch(GET_DVISION_PICTURE(GET_OSD_SELECT_REGION()))
    {
        default:
        case _OSD_DVISION_PICTURE_DARK:
            if(usOsdItemType == _OSD_DVISION_PICTURE)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.b1DVisionPictureModify = (bit)ucData);
            }
            if(usOsdItemType == _OSD_DVISION_BACKLIGHT)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.b7DVisionBacklight = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_BRIGHTNESS)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.ucDVisionBrightness = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_CONTRAST)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.ucDVisionContrast = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_SATURATION)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode1.ucDVisionSaturation = ucData);
            }
            break;
        case _OSD_DVISION_PICTURE_BRIGHT:
            if(usOsdItemType == _OSD_DVISION_PICTURE)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.b1DVisionPictureModify = (bit)ucData);
            }
            if(usOsdItemType == _OSD_DVISION_BACKLIGHT)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.b7DVisionBacklight = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_BRIGHTNESS)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.ucDVisionBrightness = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_CONTRAST)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.ucDVisionContrast = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_SATURATION)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode2.ucDVisionSaturation = ucData);
            }
            break;
        case _OSD_DVISION_PICTURE_GAME:
            if(usOsdItemType == _OSD_DVISION_PICTURE)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.b1DVisionPictureModify = (bit)ucData);
            }
            if(usOsdItemType == _OSD_DVISION_BACKLIGHT)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.b7DVisionBacklight = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_BRIGHTNESS)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.ucDVisionBrightness = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_CONTRAST)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.ucDVisionContrast = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_SATURATION)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode3.ucDVisionSaturation = ucData);
            }
            break;
        case _OSD_DVISION_PICTURE_USER:
            if(usOsdItemType == _OSD_DVISION_PICTURE)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.b1DVisionPictureModify = (bit)ucData);
            }
            if(usOsdItemType == _OSD_DVISION_BACKLIGHT)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.b7DVisionBacklight = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_BRIGHTNESS)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.ucDVisionBrightness = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_CONTRAST)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.ucDVisionContrast = ucData);
            }
            if(usOsdItemType == _OSD_DVISION_SATURATION)
            {
                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (ucRegion))].stDVisionMode4.ucDVisionSaturation = ucData);
            }
            break;
    }
}


//--------------------------------------------------
// Description  : restore DVision mode data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamRestoreOsdDVisionModeData(void)
{
    switch(GET_DVISION_PICTURE(GET_OSD_SELECT_REGION()))
    {
        default:
        case _OSD_DVISION_PICTURE_DARK:
            SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[0].b1DVisionPictureModify);
            SET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[0].b7DVisionBacklight);
            SET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[0].ucDVisionBrightness);
            SET_DVISION_CONTRAST(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[0].ucDVisionContrast);
            SET_DVISION_SATURATION(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[0].ucDVisionSaturation);
            break;
        case _OSD_DVISION_PICTURE_BRIGHT:
            SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[1].b1DVisionPictureModify);
            SET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[1].b7DVisionBacklight);
            SET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[1].ucDVisionBrightness);
            SET_DVISION_CONTRAST(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[1].ucDVisionContrast);
            SET_DVISION_SATURATION(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[1].ucDVisionSaturation);
            break;
        case _OSD_DVISION_PICTURE_GAME:
            SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[2].b1DVisionPictureModify);
            SET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[2].b7DVisionBacklight);
            SET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[2].ucDVisionBrightness);
            SET_DVISION_CONTRAST(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[2].ucDVisionContrast);
            SET_DVISION_SATURATION(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[2].ucDVisionSaturation);
            break;
        case _OSD_DVISION_PICTURE_USER:
            SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[3].b1DVisionPictureModify);
            SET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[3].b7DVisionBacklight);
            SET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[3].ucDVisionBrightness);
            SET_DVISION_CONTRAST(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[3].ucDVisionContrast);
            SET_DVISION_SATURATION(GET_OSD_SELECT_REGION(), tDVisionPictureModeDefault[3].ucDVisionSaturation);
            break;
    }
    RTDNVRamSaveOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());
}
#endif
#endif // #if(_OSD_TYPE == _REALTEK_2020_OSD)
