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
// ID Code      : UserCommonNVRamInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Flash Data Move Result
//--------------------------------------------------
typedef enum
{
    _MOVE_FAIL = _FALSE,
    _MOVE_SUCCESS = _TRUE,
} EnumFlashMoveDataResult;

//--------------------------------------------------
// Enumerations of Eeprom Write Size
//--------------------------------------------------
typedef enum
{
    _WRITE_SIZE_8 = 8,
    _WRITE_SIZE_16 = 16,
    _WRITE_SIZE_32 = 32,
} EnumEepromWriteSize;

//--------------------------------------------------
// Enumerations of NVRam
//--------------------------------------------------
typedef enum
{
    _CHECK_FAIL = _FALSE,
    _CHECK_SUCCESS = _TRUE,
} EnumNvramCheckResult;

//--------------------------------------------------
// Enumerations of NVRam Check Data Type
//--------------------------------------------------
typedef enum
{
    _CHECK_ADC_SAVE,
    _CHECK_ADC_LOAD,
    _CHECK_SYSTEM_DATA_SAVE,
    _CHECK_SYSTEM_DATA_LOAD,
    _CHECK_MODE_USER_DATA_SAVE,
    _CHECK_MODE_USER_DATA_LOAD,
    _CHECK_SYSTEM_ITEM_COUNT,
} EnumNvramCheckType;

//--------------------------------------------------
// Enumerations of System Data Info
//--------------------------------------------------
typedef enum
{
    _MONITOR_POWER_STATUS,
    _DP_HOT_PLUG_DC_OFF_HIGH,
    _HDMI_HOT_PLUG_SUPPORT_TIME,
    _HDMI_HOT_PLUG_SUPPORT,
    _DP_AUX_DIFF_MODE,
    _DP_AUX_ADJR_SETTING,
    _AUTO_SEARCH_TARGET,
    _SOURCE_SCAN_TYPE,
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    _SOURCE_BG_SCAN_TYPE,
#endif
    _SEARCH_PORT_0,
    _SEARCH_PORT_1,
    _SEARCH_PORT_2,
    _SEARCH_PORT_3,
    _DISPLAY_MODE,
    _MODE_SLOT_INDEX,
    _SSC,
    _DP_EDID_SELECT,
    _DUAL_DP_EDID_SELECT,
    _DP_D0_LANES,
    _DP_D1_LANES,
    _DP_D2_LANES,
    _DP_D6_LANES,
    _COLORIMETRY_SEAMLESS_CHANGE,
    _EDID_D0_SELECT,
    _EDID_D1_SELECT,
    _EDID_D2_SELECT,
    _EDID_D3_SELECT,
    _EDID_D4_SELECT,
    _EDID_D5_SELECT,
    _EDID_D6_SELECT,
    _DP_IRQ_TIME,
    _DP_ILLEGAL_IDLE_PATTERN_CHECK,
    _SOURCE_HP_AUTO_SEARCH,
} EnumSystemDataItemDataType;

typedef enum
{
    _DP_EDID_1080P = 0,
    _DP_EDID_2560_1440,
    _DP_EDID_4K2K_60HZ,
    _DP_EDID_4K2K_240HZ,
    _DP_EDID_5K_144HZ,
    _DP_EDID_8K_60HZ,
    _DP_EDID_AMOUNT = _DP_EDID_8K_60HZ,
}EnumDpEDIDSelection;

typedef enum
{
    _DUAL_DP_EDID_5K3K_60HZ = 0,
    _DUAL_DP_EDID_4K2K_144HZ,
    _DUAL_DP_EDID_8K4K_60HZ,
    _DUAL_DP_EDID_AMOUNT = _DUAL_DP_EDID_8K4K_60HZ,
}EnumDualDpEDIDSelection;

//--------------------------------------------------
// Structure of System Data
//--------------------------------------------------
typedef struct
{
    BYTE b4SearchPort0 : 4;                     // Search Port 0
    BYTE b4SearchPort1 : 4;                     // Search Port 1

    BYTE b4SearchPort2 : 4;                     // Search Port 2
    BYTE b4SearchPort3 : 4;                     // Search Port 3

    BYTE ucDisplayMode;                         // Display Mode
    BYTE ucModeSlotIndex;                       // Mode Slot Index
    BYTE ucSSC;                                 // SSC

    BYTE b4HDMIHotPlugSupportTime : 4;          // HDMIHotPlugSupportTime(Unit : 100ms)
    BYTE b1HDMIHotPlugSupport : 1;              // HDMIHotPlugSupport
    BYTE b2AutoTarget : 2;                      // Auto Search Target
    BYTE b1DPHotPlugDCOffHigh : 1;              // DPHotPlugDCOffHigh

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    BYTE b4SourceScanType : 4;                  // Source Scan Type
    BYTE b1SourceHPAutoSearch : 1;
#else
    BYTE b2SourceScanType : 2;                  // Source Scan Type
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    BYTE b1SourceBgScanType : 1;                // Source Bg Scan Type
#endif

    BYTE b3D0DpLanes : 3;
    BYTE b3D1DpLanes : 3;

    BYTE b3D2DpLanes : 3;
    BYTE b3D6DpLanes : 3;
    BYTE b2DualDPEDIDSelect : 2;                // Dual DP Select

    BYTE b1PowerStatus : 1;                     // Monitor Power Status
    BYTE b3DPEDIDSelect : 3;                    // DP EDID Select
    BYTE b1DPAuxDiffMode : 1;                   // DPAuxDiffMode
    BYTE b4EdidD0 : 4;                          // DP EDID Select by Port

    WORD b4EdidD1 : 4;
    WORD b4EdidD2 : 4;
    WORD b4EdidD3 : 4;
    WORD b4EdidD4 : 4;
    WORD b4EdidD5 : 4;
    WORD b1ColorSeamlessChange : 1;             // Colorimetry Seamless Change

    BYTE ucDpIrqTime_10us;                      // DP MST IRQ HPD time (unit : 10us)
    BYTE b4EdidD6 : 4;
    BYTE b1SyncDPIllegalIdlePatternCheck : 1;
    BYTE b5DPAuxAdjrSetting : 5;                // DpAuxAdjrSetting
}StructSystemDataType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
extern WORD g_pusFlashAddrArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
extern BYTE g_pucFlashPageArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE UserCommonNVRamGetSystemData(EnumSystemDataItemDataType enumDataType);
extern void UserCommonNVRamSetSystemData(EnumSystemDataItemDataType enumDataType, BYTE ucValue);

extern EnumInputPort UserCommonNVRamGetSystemRegionPortData(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonNVRamSetSystemRegionPortData(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort);

extern bit UserCommonNVRamRead(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonNVRamSaveSystemData(void);
extern void UserCommonNVRamLoadSystemData(void);
extern void UserCommonNVRamRestoreSystemData(void);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonNVRamLoadModeUserData(BYTE ucSlotIndex);
extern void UserCommonNVRamSaveModeUserData(void);
extern BYTE UserCommonNVRamLoadModeUserModeNumberData(BYTE ucSlotIndex);
extern void UserCommonNVRamRestoreModeUserData(void);
extern BYTE UserCommonNVRamVGAFifoModeIndexOffsetInc(BYTE ucStep);
extern BYTE UserCommonNVRamGetMaxFifoGroupCnt(void);
extern void UserCommonNVRamSaveADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonNVRamLoadADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonNVRamRestoreADCSetting(void);
#endif

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit UserCommonEepromIICRead(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
extern bit UserCommonEepromIICWrite(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize);
#endif

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern bit UserCommonEepromRead(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit UserCommonEepromWrite(DWORD ulSubAddr, WORD usLength, BYTE *pucWriteArray);
extern void UserCommonEepromSaveSystemData(void);
extern void UserCommonEepromLoadSystemData(void);
extern void UserCommonEepromRestoreSystemData(void);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonEepromLoadModeUserData(DWORD ulSlotIndex);
extern void UserCommonEepromSaveModeUserData(void);
extern BYTE UserCommonEepromLoadModeUserModeNumberData(DWORD ulSlotIndex);
extern void UserCommonEepromRestoreModeUserData(void);
extern BYTE UserCommonEepromVGAFifoModeIndexOffsetInc(BYTE ucStep);
extern BYTE UserCommonEepromGetMaxFifoGroupCnt(void);
extern void UserCommonEepromLoadADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonEepromSaveADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonEepromRestoreADCSetting(void);
#endif

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

extern bit UserCommonFlashLoadItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength);
extern bit UserCommonFlashSaveItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength);
extern BYTE UserCommonFlashCalculateCheckSumData(BYTE *pucData, BYTE ucLength);
extern void UserCommonFlashSaveSystemData(void);
extern void UserCommonFlashLoadSystemData(void);
extern void UserCommonFlashRestoreSystemData(void);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonFlashLoadModeUserData(BYTE ucSlotIndex);
extern void UserCommonFlashSaveModeUserData(void);
extern BYTE UserCommonFlashLoadModeUserModeNumberData(BYTE ucSlotIndex);
extern void UserCommonFlashRestoreModeUserData(void);
extern BYTE UserCommonFlashVGAFifoModeIndexOffsetInc(BYTE ucStep);
extern BYTE UserCommonFlashGetMaxFifoGroupCnt(void);
extern void UserCommonFlashLoadADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonFlashSaveADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonFlashRestoreADCSetting(void);
#endif

#endif // Else of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
extern bit UserCommonFlashErasePage(WORD usBank, BYTE ucPage);
extern bit UserCommonFlashWrite(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData);
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _ON)
extern bit UserCommonFlashRead(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData);
#endif

extern DWORD UserCommonNVRamGetFlashBankOffset(void);

#if(_EMBEDDED_RESOURCE_FILE_SUPPORT == _ON)
extern DWORD UserCommonNVRamGetResourceAddress(DWORD ulResourceIndex);
extern DWORD UserCommonNVRamGetResourceSize(DWORD ulResourceIndex);
#endif
