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
// ID Code      : ScalerSyncInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// CTA Extension General Definition
//--------------------------------------------------
#define _CTA_DB_MAX_LEN                                     31
#define _CTA_EXTENSION_TAG                                  0x02
#define _DID_EXTENSION_TAG                                  0x70

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Macros of Digital Color Change Reset Enable
//--------------------------------------------------
#define GET_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bSyncDigitalColorInfoChangeReset)
#define SET_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bSyncDigitalColorInfoChangeReset = _TRUE)
#define CLR_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bSyncDigitalColorInfoChangeReset = _FALSE)

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
//--------------------------------------------------
// Macros of Digital DM Color Change Reset Enable
//--------------------------------------------------
#define GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET()            (g_stSyncDigitalDMColorInfoChange.b1SyncDigitalDMColorInfoChangeReset)
#define SET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET()            (g_stSyncDigitalDMColorInfoChange.b1SyncDigitalDMColorInfoChangeReset = _TRUE)
#define CLR_DIGITAL_DM_COLOR_INFO_CHANGE_RESET()            (g_stSyncDigitalDMColorInfoChange.b1SyncDigitalDMColorInfoChangeReset = _FALSE)

#define GET_DIGITAL_DM_COLOR_INFO_CHANGE_BG_EN()            (g_stSyncDigitalDMColorInfoChange.b1SyncDigitalDMColorInfoChangeBGEnable)
#define SET_DIGITAL_DM_COLOR_INFO_CHANGE_BG_EN()            (g_stSyncDigitalDMColorInfoChange.b1SyncDigitalDMColorInfoChangeBGEnable = _TRUE)
#define CLR_DIGITAL_DM_COLOR_INFO_CHANGE_BG_EN()            (g_stSyncDigitalDMColorInfoChange.b1SyncDigitalDMColorInfoChangeBGEnable = _FALSE)
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Rx Mst Capability Switch
//--------------------------------------------------
#define GET_DP_RX_D0_PORT_TARGET_VERSION()                  (g_stSyncDpCapSwitch.ucD0Version)
#define SET_DP_RX_D0_PORT_TARGET_VERSION(x)                 (g_stSyncDpCapSwitch.ucD0Version = (x))

#define GET_DP_RX_D1_PORT_TARGET_VERSION()                  (g_stSyncDpCapSwitch.ucD1Version)
#define SET_DP_RX_D1_PORT_TARGET_VERSION(x)                 (g_stSyncDpCapSwitch.ucD1Version = (x))

#define GET_DP_RX_D2_PORT_TARGET_VERSION()                  (g_stSyncDpCapSwitch.ucD2Version)
#define SET_DP_RX_D2_PORT_TARGET_VERSION(x)                 (g_stSyncDpCapSwitch.ucD2Version = (x))

#define GET_DP_RX_D6_PORT_TARGET_VERSION()                  (g_stSyncDpCapSwitch.ucD6Version)
#define SET_DP_RX_D6_PORT_TARGET_VERSION(x)                 (g_stSyncDpCapSwitch.ucD6Version = (x))

#define GET_DP_RX_D0_PORT_TARGET_LANE_COUNT()               (g_stSyncDpCapSwitch.ucD0LaneCount)
#define SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(x)              (g_stSyncDpCapSwitch.ucD0LaneCount = (x))

#define GET_DP_RX_D1_PORT_TARGET_LANE_COUNT()               (g_stSyncDpCapSwitch.ucD1LaneCount)
#define SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(x)              (g_stSyncDpCapSwitch.ucD1LaneCount = (x))

#define GET_DP_RX_D2_PORT_TARGET_LANE_COUNT()               (g_stSyncDpCapSwitch.ucD2LaneCount)
#define SET_DP_RX_D2_PORT_TARGET_LANE_COUNT(x)              (g_stSyncDpCapSwitch.ucD2LaneCount = (x))

#define GET_DP_RX_D6_PORT_TARGET_LANE_COUNT()               (g_stSyncDpCapSwitch.ucD6LaneCount)
#define SET_DP_RX_D6_PORT_TARGET_LANE_COUNT(x)              (g_stSyncDpCapSwitch.ucD6LaneCount = (x))

#define GET_DP_RX_D0_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D0Edid)
#define SET_DP_RX_D0_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D0Edid = _TRUE)
#define CLR_DP_RX_D0_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D0Edid = _FALSE)

#define GET_DP_RX_D1_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D1Edid)
#define SET_DP_RX_D1_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D1Edid = _TRUE)
#define CLR_DP_RX_D1_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D1Edid = _FALSE)

#define GET_DP_RX_D2_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D2Edid)
#define SET_DP_RX_D2_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D2Edid = _TRUE)
#define CLR_DP_RX_D2_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D2Edid = _FALSE)

#define GET_DP_RX_D6_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D6Edid)
#define SET_DP_RX_D6_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D6Edid = _TRUE)
#define CLR_DP_RX_D6_EDID_SWITCH()                          (g_stSyncDpCapSwitch.b1D6Edid = _FALSE)

#define GET_DP_RX_TARGET_MST_PORT()                         (g_stSyncDpCapSwitch.enumMSTPort)
#define SET_DP_RX_TARGET_MST_PORT(x)                        (g_stSyncDpCapSwitch.enumMSTPort = (x))

#define GET_DP_RX_CAPABILITY_SWITCHED()                     (g_stSyncDpCapSwitch.b1MsgSwitched)
#define SET_DP_RX_CAPABILITY_SWITCHED()                     (g_stSyncDpCapSwitch.b1MsgSwitched = _TRUE)
#define CLR_DP_RX_CAPABILITY_SWITCHED()                     (g_stSyncDpCapSwitch.b1MsgSwitched = _FALSE)

#define GET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE()            (g_stSyncDpCapSwitch.ucD0MaxLinkRate)
#define SET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE(x)           (g_stSyncDpCapSwitch.ucD0MaxLinkRate = (x))

#define GET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D0MaxLinkRateSwitch)
#define SET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D0MaxLinkRateSwitch = _TRUE)
#define CLR_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D0MaxLinkRateSwitch = _FALSE)

#define GET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE()            (g_stSyncDpCapSwitch.ucD1MaxLinkRate)
#define SET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE(x)           (g_stSyncDpCapSwitch.ucD1MaxLinkRate = (x))

#define GET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D1MaxLinkRateSwitch)
#define SET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D1MaxLinkRateSwitch = _TRUE)
#define CLR_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D1MaxLinkRateSwitch = _FALSE)

#define GET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE()            (g_stSyncDpCapSwitch.ucD2MaxLinkRate)
#define SET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE(x)           (g_stSyncDpCapSwitch.ucD2MaxLinkRate = (x))

#define GET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D2MaxLinkRateSwitch)
#define SET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D2MaxLinkRateSwitch = _TRUE)
#define CLR_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE_SWITCH()     (g_stSyncDpCapSwitch.b1D2MaxLinkRateSwitch = _FALSE)

//--------------------------------------------------
// Definitions of DP DC OFF HPD Related
//--------------------------------------------------
#define GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(x)             (g_pbSyncDpMstDCOffHPDToggleHoldFlag[(x) - _D0_INPUT_PORT])
#define SET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(x)             (g_pbSyncDpMstDCOffHPDToggleHoldFlag[(x) - _D0_INPUT_PORT] = _TRUE)
#define CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(x)             (g_pbSyncDpMstDCOffHPDToggleHoldFlag[(x) - _D0_INPUT_PORT] = _FALSE)

#define GET_DP_DC_OFF_HPD_TOGGLE_FLAG()                     (g_bSyncDpDCOffHPDToggleFlag)
#define SET_DP_DC_OFF_HPD_TOGGLE_FLAG()                     (g_bSyncDpDCOffHPDToggleFlag = 1)
#define CLR_DP_DC_OFF_HPD_TOGGLE_FLAG()                     (g_bSyncDpDCOffHPDToggleFlag = 0)

//--------------------------------------------------
// Definitions of DP IRQ Time Setting
//--------------------------------------------------
#define GET_DP_IRQ_TIME_10US()                              (g_ucSyncDpIrqTime_10us)
#define SET_DP_IRQ_TIME_10US(x)                             (g_ucSyncDpIrqTime_10us = (x))
#endif
#endif

//--------------------------------------------------
// Definitions of DP Aux Listen Mode Adjr
//--------------------------------------------------
#define _DP_AUX_INITIAL_ADJR                                _DP_AUX_LISTEN_MODE_Z0

//--------------------------------------------------
// Macro of Cable Detect Flag
//--------------------------------------------------
#define GET_A0_CABLE_STATUS()                               (g_stSyncPortCableStatus.b1A0CableDetect)
#define SET_A0_CABLE_STATUS(x)                              (g_stSyncPortCableStatus.b1A0CableDetect = (x))

#define GET_D0_CABLE_STATUS()                               (g_stSyncPortCableStatus.b1D0CableDetect)
#define SET_D0_CABLE_STATUS(x)                              (g_stSyncPortCableStatus.b1D0CableDetect = (x))

#define GET_D1_CABLE_STATUS()                               (g_stSyncPortCableStatus.b1D1CableDetect)
#define SET_D1_CABLE_STATUS(x)                              (g_stSyncPortCableStatus.b1D1CableDetect = (x))

#define GET_D2_CABLE_STATUS()                               (g_stSyncPortCableStatus.b1D2CableDetect)
#define SET_D2_CABLE_STATUS(x)                              (g_stSyncPortCableStatus.b1D2CableDetect = (x))

#define GET_D3_CABLE_STATUS()                               (g_stSyncPortCableStatus.b1D3CableDetect)
#define SET_D3_CABLE_STATUS(x)                              (g_stSyncPortCableStatus.b1D3CableDetect = (x))

#define GET_D4_CABLE_STATUS()                               (g_stSyncPortCableStatus.b1D4CableDetect)
#define SET_D4_CABLE_STATUS(x)                              (g_stSyncPortCableStatus.b1D4CableDetect = (x))

#define GET_D5_CABLE_STATUS()                               (g_stSyncPortCableStatus.b1D5CableDetect)
#define SET_D5_CABLE_STATUS(x)                              (g_stSyncPortCableStatus.b1D5CableDetect = (x))

#define GET_D12_CABLE_STATUS()                              (g_stSyncPortCableStatus.b1D12CableDetect)
#define SET_D12_CABLE_STATUS(x)                             (g_stSyncPortCableStatus.b1D12CableDetect = (x))

#define GET_D13_CABLE_STATUS()                              (g_stSyncPortCableStatus.b1D13CableDetect)
#define SET_D13_CABLE_STATUS(x)                             (g_stSyncPortCableStatus.b1D13CableDetect = (x))

#define GET_D14_CABLE_STATUS()                              (g_stSyncPortCableStatus.b1D14CableDetect)
#define SET_D14_CABLE_STATUS(x)                             (g_stSyncPortCableStatus.b1D14CableDetect = (x))

#define GET_D15_CABLE_STATUS()                              (g_stSyncPortCableStatus.b1D15CableDetect)
#define SET_D15_CABLE_STATUS(x)                             (g_stSyncPortCableStatus.b1D15CableDetect = (x))

#define GET_D0_DP_TYPE_C_ALTMODE_STATUS()                   (g_stSyncPortCableStatus.b1D0AltModeStatus)
#define SET_D0_DP_TYPE_C_ALTMODE_STATUS(x)                  (g_stSyncPortCableStatus.b1D0AltModeStatus = (x))

#define GET_D1_DP_TYPE_C_ALTMODE_STATUS()                   (g_stSyncPortCableStatus.b1D1AltModeStatus)
#define SET_D1_DP_TYPE_C_ALTMODE_STATUS(x)                  (g_stSyncPortCableStatus.b1D1AltModeStatus = (x))

#define GET_D2_DP_TYPE_C_ALTMODE_STATUS()                   (g_stSyncPortCableStatus.b1D2AltModeStatus)
#define SET_D2_DP_TYPE_C_ALTMODE_STATUS(x)                  (g_stSyncPortCableStatus.b1D2AltModeStatus = (x))


#if(_DUAL_DP_SUPPORT == _ON)
#define GET_DUAL_DP_PORT_SWITCH_SELECT()                    (g_enumSyncDualDpPortSwitchSelect)
#define SET_DUAL_DP_PORT_SWITCH_SELECT(x)                   (g_enumSyncDualDpPortSwitchSelect = (x))
#endif

//--------------------------------------------------
// Macros of HDR Support
//--------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#define GET_RX0_HDR10_SUPPORT()                             (g_stSyncHDR10PortSettingInfo.enumHDR10RX0Support)
#define SET_RX0_HDR10_SUPPORT(x)                            (g_stSyncHDR10PortSettingInfo.enumHDR10RX0Support = (x))

#define GET_RX1_HDR10_SUPPORT()                             (g_stSyncHDR10PortSettingInfo.enumHDR10RX1Support)
#define SET_RX1_HDR10_SUPPORT(x)                            (g_stSyncHDR10PortSettingInfo.enumHDR10RX1Support = (x))

#define GET_RX2_HDR10_SUPPORT()                             (g_stSyncHDR10PortSettingInfo.enumHDR10RX2Support)
#define SET_RX2_HDR10_SUPPORT(x)                            (g_stSyncHDR10PortSettingInfo.enumHDR10RX2Support = (x))

#define GET_RX3_HDR10_SUPPORT()                             (g_stSyncHDR10PortSettingInfo.enumHDR10RX3Support)
#define SET_RX3_HDR10_SUPPORT(x)                            (g_stSyncHDR10PortSettingInfo.enumHDR10RX3Support = (x))

#define GET_RX4_HDR10_SUPPORT()                             (g_stSyncHDR10PortSettingInfo.enumHDR10RX4Support)
#define SET_RX4_HDR10_SUPPORT(x)                            (g_stSyncHDR10PortSettingInfo.enumHDR10RX4Support = (x))

#define GET_RX5_HDR10_SUPPORT()                             (g_stSyncHDR10PortSettingInfo.enumHDR10RX5Support)
#define SET_RX5_HDR10_SUPPORT(x)                            (g_stSyncHDR10PortSettingInfo.enumHDR10RX5Support = (x))

#define GET_RX6_HDR10_SUPPORT()                             (g_stSyncHDR10PortSettingInfo.enumHDR10RX6Support)
#define SET_RX6_HDR10_SUPPORT(x)                            (g_stSyncHDR10PortSettingInfo.enumHDR10RX6Support = (x))
#endif

//--------------------------------------------------
// Macros of Advanced HDR10 Support
//--------------------------------------------------
#if(_ADVANCED_HDR10_SUPPORT == _ON)
#define GET_ADVANCED_HDR10_INFO_DATA_STATUS()               ((g_stSyncAdvancedHDR10Metadata.pucOUICode[0] == _ADVANCED_HDR10_OUI_CODE_1) && (g_stSyncAdvancedHDR10Metadata.pucOUICode[1] == _ADVANCED_HDR10_OUI_CODE_2) && (g_stSyncAdvancedHDR10Metadata.pucOUICode[2] == _ADVANCED_HDR10_OUI_CODE_3))
#define GET_ADVANCED_HDR10_BACK_UP_INFO_DATA_STATUS()       ((g_stSyncAdvancedHDR10BackUpMetadata.pucOUICode[0] == _ADVANCED_HDR10_OUI_CODE_1) && (g_stSyncAdvancedHDR10BackUpMetadata.pucOUICode[1] == _ADVANCED_HDR10_OUI_CODE_2) && (g_stSyncAdvancedHDR10BackUpMetadata.pucOUICode[2] == _ADVANCED_HDR10_OUI_CODE_3))

#define CLR_ADVANCED_HDR10_INFO_DATA()                      (memset(&g_stSyncAdvancedHDR10Metadata, 0, sizeof(StructAdvancedHDR10MetaData)))
#define CLR_ADVANCED_HDR10_BACK_UP_INFO_DATA()              (memset(&g_stSyncAdvancedHDR10BackUpMetadata, 0, sizeof(StructAdvancedHDR10MetaData)))

#define CLR_ADVANCED_HDR10_YM_TABLE()                       (memset((BYTE *)&g_pucSyncAdvancedHDR10YmTable, 0, _YMAPPING_GAIN_TABLE_SIZE))

#define CLR_ADVANCED_HDR10_BACKUP_METADATA_CHANGE()         (g_stSyncAdvancedHDR10SettingInfo.ucBackUpMetadataChange = _FALSE)
#define GET_ADVANCED_HDR10_BACKUP_METADATA_CHANGE()         (g_stSyncAdvancedHDR10SettingInfo.ucBackUpMetadataChange)
#define SET_ADVANCED_HDR10_BACKUP_METADATA_CHANGE(x)        (g_stSyncAdvancedHDR10SettingInfo.ucBackUpMetadataChange = (x))

#define GET_ADVANCED_HDR10_DELAY_MODE()                     ((g_stSyncAdvancedHDR10Metadata.ucNoDelayFlag == 0x00) && ((g_stSyncAdvancedHDR10SettingInfo.enumFRCStatus == _ADVANCED_HDR10_FRAME_SYNC) ? (GET_ADVANCED_HDR10_ENLARGE_DELAY_STATUS() == _ADVANCED_HDR10_ENLARGE_DELAY_ON) : (_TRUE)))

#define CLR_ADVANCED_HDR10_PANEL_MAX_LV()                   (g_stSyncAdvancedHDR10SettingInfo.usPanelMaxLv = 0)
#define GET_ADVANCED_HDR10_PANEL_MAX_LV()                   (g_stSyncAdvancedHDR10SettingInfo.usPanelMaxLv)
#define SET_ADVANCED_HDR10_PANEL_MAX_LV(x)                  (g_stSyncAdvancedHDR10SettingInfo.usPanelMaxLv = (x))

#define CLR_ADVANCED_HDR10_INITIAL_READY()                  (g_stSyncAdvancedHDR10SettingInfo.ucInitialReady = _FALSE)
#define GET_ADVANCED_HDR10_INITIAL_READY()                  (g_stSyncAdvancedHDR10SettingInfo.ucInitialReady)
#define SET_ADVANCED_HDR10_INITIAL_READY()                  (g_stSyncAdvancedHDR10SettingInfo.ucInitialReady = _TRUE)

#define GET_ADVANCED_HDR10_FRC_STATUS()                     (g_stSyncAdvancedHDR10SettingInfo.enumFRCStatus)
#define SET_ADVANCED_HDR10_FRC_STATUS(x)                    (g_stSyncAdvancedHDR10SettingInfo.enumFRCStatus = (x))

#define SET_ADVANCED_HDR10_METADATA_DETECT_TIME(x)          (g_stSyncAdvancedHDR10SettingInfo.usHDR10MetadataDetectTime = (x))
#define GET_ADVANCED_HDR10_METADATA_DETECT_TIME()           (g_stSyncAdvancedHDR10SettingInfo.usHDR10MetadataDetectTime)

#define GET_ADVANCED_HDR10_METADATA_SUPPORT()               (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10MetadataSupport)
#define SET_ADVANCED_HDR10_METADATA_SUPPORT(x)              (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10MetadataSupport = (x))
#define CLR_ADVANCED_HDR10_METADATA_SUPPORT()               (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10MetadataSupport = _ADVANCED_HDR10_SUPPORT_OFF)

#define SET_ADVANCED_HDR10_ENLARGE_DELAY_STATUS(x)          (g_stSyncAdvancedHDR10SettingInfo.enumColorAdvancedHDR10EnlargeDelayStatus = (x))
#define GET_ADVANCED_HDR10_ENLARGE_DELAY_STATUS()           (g_stSyncAdvancedHDR10SettingInfo.enumColorAdvancedHDR10EnlargeDelayStatus)
#define SET_ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT(x)         (g_stSyncAdvancedHDR10SettingInfo.enumColorAdvancedHDR10EnlargeDelaySupport = (x))
#define GET_ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT()          (g_stSyncAdvancedHDR10SettingInfo.enumColorAdvancedHDR10EnlargeDelaySupport)

#define CLR_ADVANCED_HDR10_COLOR_INITIAL_SETTING()          (g_stSyncAdvancedHDR10SettingInfo.ucColorInitialSetting = _FALSE)
#define SET_ADVANCED_HDR10_COLOR_INITIAL_SETTING()          (g_stSyncAdvancedHDR10SettingInfo.ucColorInitialSetting = _TRUE)
#define GET_ADVANCED_HDR10_COLOR_INITIAL_SETTING()          (g_stSyncAdvancedHDR10SettingInfo.ucColorInitialSetting)

#define CLR_ADVANCED_HDR10_YM_TABLE_READY()                 (g_stSyncAdvancedHDR10SettingInfo.ucYMTableReady = _FALSE)
#define SET_ADVANCED_HDR10_YM_TABLE_READY()                 (g_stSyncAdvancedHDR10SettingInfo.ucYMTableReady = _TRUE)
#define GET_ADVANCED_HDR10_YM_TABLE_READY()                 (g_stSyncAdvancedHDR10SettingInfo.ucYMTableReady)

#define CLR_ADVANCED_HDR10_COLOR_APPLY_A()                  (g_stSyncAdvancedHDR10SettingInfo.ucColorApplyFlagA = _FALSE)
#define SET_ADVANCED_HDR10_COLOR_APPLY_A()                  (g_stSyncAdvancedHDR10SettingInfo.ucColorApplyFlagA = _TRUE)
#define GET_ADVANCED_HDR10_COLOR_APPLY_A()                  (g_stSyncAdvancedHDR10SettingInfo.ucColorApplyFlagA)

#define CLR_ADVANCED_HDR10_COLOR_APPLY_B()                  (g_stSyncAdvancedHDR10SettingInfo.ucColorApplyFlagB = _FALSE)
#define SET_ADVANCED_HDR10_COLOR_APPLY_B()                  (g_stSyncAdvancedHDR10SettingInfo.ucColorApplyFlagB = _TRUE)
#define GET_ADVANCED_HDR10_COLOR_APPLY_B()                  (g_stSyncAdvancedHDR10SettingInfo.ucColorApplyFlagB)

#define CLR_ADVANCED_HDR10_NOTIFY_INT()                     (g_stSyncAdvancedHDR10SettingInfo.ucNotifyInt = _FALSE)
#define SET_ADVANCED_HDR10_NOTIFY_INT()                     (g_stSyncAdvancedHDR10SettingInfo.ucNotifyInt = _TRUE)
#define GET_ADVANCED_HDR10_NOTIFY_INT()                     (g_stSyncAdvancedHDR10SettingInfo.ucNotifyInt)

#define SET_ADVANCED_HDR10_PCM_HLW_DB_STATUS(x)             (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10PCMHLWDBStatus = (x))
#define GET_ADVANCED_HDR10_PCM_HLW_DB_STATUS()              (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10PCMHLWDBStatus)

#define SET_ADVANCED_HDR10_RESTORE_PCM_HLW_DB_STATUS(x)     (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10RestorePCMHLWDBStatus = (x))
#define GET_ADVANCED_HDR10_RESTORE_PCM_HLW_DB_STATUS()      (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10RestorePCMHLWDBStatus)

#define SET_ADVANCED_HDR10_PCM_HLW_MODE(x)                  (g_stSyncAdvancedHDR10SettingInfo.enumPCMHLWMode = (x))
#define GET_ADVANCED_HDR10_PCM_HLW_MODE()                   (g_stSyncAdvancedHDR10SettingInfo.enumPCMHLWMode)

#define SET_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS()        (g_stSyncAdvancedHDR10SettingInfo.ucPCMHLWDBErrorStatus = _TRUE)
#define CLR_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS()        (g_stSyncAdvancedHDR10SettingInfo.ucPCMHLWDBErrorStatus = _FALSE)
#define GET_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS()        (g_stSyncAdvancedHDR10SettingInfo.ucPCMHLWDBErrorStatus)

#define SET_ADVANCED_HDR10_METADATA_REAPPLY()               (g_stSyncAdvancedHDR10SettingInfo.ucMetadataReApply = _TRUE)
#define CLR_ADVANCED_HDR10_METADATA_REAPPLY()               (g_stSyncAdvancedHDR10SettingInfo.ucMetadataReApply = _FALSE)
#define GET_ADVANCED_HDR10_METADATA_REAPPLY()               (g_stSyncAdvancedHDR10SettingInfo.ucMetadataReApply)

#define CLR_ADVANCED_HDR10_FAKE_APPLY_A()                   (g_stSyncAdvancedHDR10SettingInfo.ucFakeApplyFlagA = _FALSE)
#define SET_ADVANCED_HDR10_FAKE_APPLY_A()                   (g_stSyncAdvancedHDR10SettingInfo.ucFakeApplyFlagA = _TRUE)
#define GET_ADVANCED_HDR10_FAKE_APPLY_A()                   (g_stSyncAdvancedHDR10SettingInfo.ucFakeApplyFlagA)

#define CLR_ADVANCED_HDR10_FAKE_APPLY_B()                   (g_stSyncAdvancedHDR10SettingInfo.ucFakeApplyFlagB = _FALSE)
#define SET_ADVANCED_HDR10_FAKE_APPLY_B()                   (g_stSyncAdvancedHDR10SettingInfo.ucFakeApplyFlagB = _TRUE)
#define GET_ADVANCED_HDR10_FAKE_APPLY_B()                   (g_stSyncAdvancedHDR10SettingInfo.ucFakeApplyFlagB)

#define CLR_ADVANCED_HDR10_MAIN_CPU_IRQ_FLAG()              (g_stSyncAdvancedHDR10SettingInfo.ucMainCPUSW0IRQ = _FALSE)
#define GET_ADVANCED_HDR10_MAIN_CPU_IRQ_FLAG()              (g_stSyncAdvancedHDR10SettingInfo.ucMainCPUSW0IRQ)
#define SET_ADVANCED_HDR10_MAIN_CPU_IRQ_FLAG()              (g_stSyncAdvancedHDR10SettingInfo.ucMainCPUSW0IRQ = _TRUE)

#define CLR_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG()            (g_stSyncAdvancedHDR10SettingInfo.ucSecondCPUSW0IRQ = _FALSE)
#define GET_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG()            (g_stSyncAdvancedHDR10SettingInfo.ucSecondCPUSW0IRQ)
#define SET_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG()            (g_stSyncAdvancedHDR10SettingInfo.ucSecondCPUSW0IRQ = _TRUE)

#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
#define GET_ADVANCED_HDR10_DHDR_DATA_STATUS()               ((g_stSyncAdvancedHDR10DHDRMetaData.ucIdentifier == _ADVANCED_HDR10_DHDR_APP_IDENTIFIER) && (g_stSyncAdvancedHDR10DHDRMetaData.ucVersion == _ADVANCED_HDR10_DHDR_APP_VERSION))
#define CLR_ADVANCED_HDR10_DHDR_DATA()                      (memset(&g_stSyncAdvancedHDR10DHDRMetaData, 0, sizeof(StructAdvancedHDR10DHDRMetaData)))
#define SET_ADVANCED_HDR10_METADATA_TYPE(x)                 (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10HDRMetadataType = (x))
#define GET_ADVANCED_HDR10_METADATA_TYPE()                  (g_stSyncAdvancedHDR10SettingInfo.enumAdvancedHDR10HDRMetadataType)
#endif
#endif

//--------------------------------------------------
// Definitions of Advanced HDR10 Support
//--------------------------------------------------
#if(_ADVANCED_HDR10_SUPPORT == _ON)
#define _ADVANCED_HDR10_OUI_CODE_1                          0x8B
#define _ADVANCED_HDR10_OUI_CODE_2                          0x84
#define _ADVANCED_HDR10_OUI_CODE_3                          0x90
#define _ADVANCED_HDR10_NO_METADATA_DEBOUNCE_NUM            3
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Definitions of DM Port info
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#define GET_D0_DM_SUPPORT()                                 (g_stSyncDMSupportInfo.b1D0Support)
#define SET_D0_DM_SUPPORT(x)                                (g_stSyncDMSupportInfo.b1D0Support = (x))
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#define GET_D1_DM_SUPPORT()                                 (g_stSyncDMSupportInfo.b1D1Support)
#define SET_D1_DM_SUPPORT(x)                                (g_stSyncDMSupportInfo.b1D1Support = (x))
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#define GET_D2_DM_SUPPORT()                                 (g_stSyncDMSupportInfo.b1D2Support)
#define SET_D2_DM_SUPPORT(x)                                (g_stSyncDMSupportInfo.b1D2Support = (x))
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#define GET_D3_DM_SUPPORT()                                 (g_stSyncDMSupportInfo.b1D3Support)
#define SET_D3_DM_SUPPORT(x)                                (g_stSyncDMSupportInfo.b1D3Support = (x))
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#define GET_D4_DM_SUPPORT()                                 (g_stSyncDMSupportInfo.b1D4Support)
#define SET_D4_DM_SUPPORT(x)                                (g_stSyncDMSupportInfo.b1D4Support = (x))
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#define GET_D5_DM_SUPPORT()                                 (g_stSyncDMSupportInfo.b1D5Support)
#define SET_D5_DM_SUPPORT(x)                                (g_stSyncDMSupportInfo.b1D5Support = (x))
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of EDID DB Type
//--------------------------------------------------
typedef enum
{
    _CTA_VDB = 0,                        // Video Data Block
    _CTA_ADB,                            // Audio Data Block
    _CTA_SPK_ADB,                        // Speaker Allocation Data Block
    _CTA_SPK_LDB,                        // Speaker Location Data Block
    _CTA_RCDB,                           // Room Configuration Data Block
    _CTA_VCDB,                           // Video Capability Data Block
    _CTA_420VDB,                         // YCBCR 420 Video Data Block
    _CTA_420CMDB,                        // YCBCR 420 Capability Map Data Block
    _CTA_CDB,                            // Colorimetry Data Block
    _CTA_SHDR_DB,                        // Static HDR Data Block
    _CTA_DHDR_DB,                        // Dynamic HDR Data Block
    _CTA_FS_DB,                          // Freesync Data Block
    _CTA_HDMI_VSDB,                      // HDMI VSDB
    _CTA_HF_VSDB,                        // HF VSDB
    _CTA_T7_VTDB,                        // Video Timing7 Data block
    _CTA_HF_EEODB,                       // HF EEODB
    _FIRST_EXT_DTD_ADDR,                 // Dtd Timing Address

    _CTA_TOTAL_DB,
} EnumEdidCtaDataBlock;

//--------------------------------------------------
// Definitions of DID DB Type
//--------------------------------------------------
typedef enum
{
    _DID_T1_DB = 0,                      // Type 1 Timing Data Block
    _DID_T7_DB,                          // Type 7 Timing Data Block
    _DID_T10_DB,                         // Type 10 Timing Data Block
    _DID_AS_DB,                          // Adpative Sync Data Block
    _DID_CTA_DB,                         // CTA encapsulation in DID Ext Data Block
    _DID_TOTAL_DB,
} EnumEdidDidDataBlock;

// ----------------------------------------------------------
// CTA Extension Block Tag
// ----------------------------------------------------------
typedef enum
{
    _CTA_DBTAG_NONE = 0,
    _CTA_DBTAG_ADB = 1,
    _CTA_DBTAG_VDB,
    _CTA_DBTAG_VSDB,
    _CTA_DBTAG_SADB,
    _CTA_DBTAG_VESADTC,
    _CTA_DBTAG_EXTTAG = 7,
}EnumEdidCtaDbTagCode;

typedef enum
{
    _CTA_EXTDBTAG_VCDB = 0,
    _CTA_EXTDBTAG_VSVDB,
    _CTA_EXTDBTAG_VESADD,
    _CTA_EXTDBTAG_VESAVDB,
    _CTA_EXTDBTAG_HDMIVDB,
    _CTA_EXTDBTAG_COLORDB,
    _CTA_EXTDBTAG_SHDR_DB,
    _CTA_EXTDBTAG_DHDR_DB,

    _CTA_EXTDBTAG_VFPDB = 13,
    _CTA_EXTDBTAG_420VDB,
    _CTA_EXTDBTAG_420CMDB,

    _CTA_EXTDBTAG_VSADB = 17,
    _CTA_EXTDBTAG_HDMIADB,
    _CTA_EXTDBTAG_RCDB,
    _CTA_EXTDBTAG_SLDB,

    _CTA_EXTDBTAG_T7_VTDB = 34,
    _CTA_EXTDBTAG_T8_VTDB,

    _CTA_EXTDBTAG_T10_VTDB = 42,

    _CTA_EXTDBTAG_HFEEODB = 120,
    _CTA_EXTDBTAG_HFSCDB,
}EnumEdidCtaExtDbTagCode;

// ----------------------------------------------------------
// DID Extension Block Tag
// ----------------------------------------------------------
typedef enum
{
    _DID13_TAG_PRODUCT_ID_DB = 0x00,
    _DID13_TAG_DISP_PAR_DB,

    _DID13_TAG_T1DB = 0x03,
    _DID13_TAG_T2DB,
    _DID13_TAG_T3DB,
    _DID13_TAG_T4DB,

    _DID2_TAG_PRODUCT_ID_DB = 0x20,
    _DID2_TAG_DISP_ID_DB,

    _DID2_TAG_T7DB = 0x22,
    _DID2_TAG_T8DB,
    _DID2_TAG_T9DB,

    _DID2_TAG_T10DB = 0x2A,
    _DID2_TAG_ASDB,

    _DID2_TAG_VSDB = 0x7E,
    _DID13_TAG_VSDB = 0x7F,

    _DID_TAG_CTADB = 0x81,
}EnumEdidDidDbTagCode;

//--------------------------------------------------
// Enumerations of HDR RSV0 info
//--------------------------------------------------
typedef enum
{
    _DP_GET_RSV0_INFO_INITIAL,
    _DP_GET_RSV0_INFO_ACTIVE,
}EnumDPGetRSV0InfoStatus;

//--------------------------------------------------
// Structure of Input Port Cable Status
//--------------------------------------------------
typedef struct
{
    BYTE b1A0CableDetect : 1;
    BYTE b1D0CableDetect : 1;
    BYTE b1D1CableDetect : 1;
    BYTE b1D2CableDetect : 1;
    BYTE b1D3CableDetect : 1;
    BYTE b1D4CableDetect : 1;
    BYTE b1D5CableDetect : 1;
    BYTE b1D6CableDetect : 1;
    BYTE b1D12CableDetect : 1;
    BYTE b1D13CableDetect : 1;
    BYTE b1D14CableDetect : 1;
    BYTE b1D15CableDetect : 1;
    BYTE b1D0AltModeStatus : 1;
    BYTE b1D1AltModeStatus : 1;
    BYTE b1D2AltModeStatus : 1;
    BYTE b1D6AltModeStatus : 1;
} StructPortCableStatus;

//--------------------------------------------------
// Definitions for DP Capability Switch
//--------------------------------------------------
typedef struct
{
    BYTE ucD0Version;
    BYTE ucD1Version;
    BYTE ucD2Version;
    BYTE ucD6Version;
    BYTE ucD0LaneCount;
    BYTE ucD1LaneCount;
    BYTE ucD2LaneCount;
    BYTE ucD6LaneCount;
    BYTE b1D0Edid : 1;
    BYTE b1D1Edid : 1;
    BYTE b1D2Edid : 1;
    BYTE b1D6Edid : 1;
    EnumDPMSTPort enumMSTPort;
    BYTE b1MsgSwitched : 1;
    BYTE b1D0MaxLinkRateSwitch : 1;
    BYTE b1D1MaxLinkRateSwitch : 1;
    BYTE b1D2MaxLinkRateSwitch : 1;
    BYTE ucD0MaxLinkRate;
    BYTE ucD1MaxLinkRate;
    BYTE ucD2MaxLinkRate;
}StructDPCapSwitchInfo;

//--------------------------------------------------
// Structure of Advanced HDR10 Static Metadata
//--------------------------------------------------
typedef struct
{
    BYTE ucVersion;
    BYTE pucOUICode[3];
    BYTE ucDistribution50;
    BYTE ucDistribution99;
    BYTE pucBezierAnchor[9];
    WORD pusKneePoint[2];
    BYTE ucTargetDisplayLv;
    BYTE ucGraphicOverlayFlag;
    BYTE ucNoDelayFlag;
} StructAdvancedHDR10MetaData;

//--------------------------------------------------
// Structure of Advanced HDR10 DHDR Metadata
//--------------------------------------------------
typedef struct
{
    BYTE ucVersion;
    BYTE ucIdentifier;
    WORD pusBezierAnchor[9];
    WORD pusKneePoint[2];
    WORD usTargetDisplayLv;
    DWORD ulDistribution50;
    DWORD ulDistribution99;
} StructAdvancedHDR10DHDRMetaData;

//--------------------------------------------------
// Enumerations of Advanced HDR10 Metadata Type
//--------------------------------------------------
typedef enum
{
    _ADVANDED_HDR10_VSIF_METADATA = 0,
    _ADVANDED_HDR10_DHDR_METADATA,
} EnumAdvancedHDR10HDRMetadataType;

//--------------------------------------------------
// Structure of Advanced HDR10 Setting Info
//--------------------------------------------------
typedef struct
{
    // The bit data below could be accessed by different CPUs or Main loop & IRQ at same time
    // Byte is assigned to avoid read-modify-write accidentially change
    BYTE ucInitialReady;
    BYTE ucColorInitialSetting; // Judge if HDR10+ initial setting is ready
    BYTE ucBackUpMetadataChange;
    BYTE ucYMTableReady; // Judge if HDR10+ YM LUT is prepared ready
    BYTE ucColorApplyFlagA;
    BYTE ucColorApplyFlagB;
    BYTE ucNotifyInt;
    BYTE ucFakeApplyFlagA; // app;y bit that is active by normal process, not pcm hlw process
    BYTE ucFakeApplyFlagB;
    BYTE ucPCMHLWDBErrorStatus;
    BYTE ucMetadataReApply; // Metadata Should be re appled when (1).PCM HLW DB ReInitial due to Error state ,(2) Metadata Resorce conflict
    BYTE ucMainCPUSW0IRQ;
    BYTE ucSecondCPUSW0IRQ;
    WORD usHDR10MetadataDetectTime;
    WORD usPanelMaxLv;
    EnumAdvancedHDR10PCMHLWDBStatus enumAdvancedHDR10PCMHLWDBStatus;
    EnumAdvancedHDR10PCMHLWDBStatus enumAdvancedHDR10RestorePCMHLWDBStatus;
    EnumAdvancedHDR10FRCStatus enumFRCStatus;
    EnumAdvancedHDR10Support enumAdvancedHDR10MetadataSupport;
    EnumAdvancedHDR10EnlargeDelaySupport enumColorAdvancedHDR10EnlargeDelaySupport;
    EnumAdvancedHDR10EnlargeDelayStatus enumColorAdvancedHDR10EnlargeDelayStatus;
    EnumAdvancedHDR10HDRMetadataType enumAdvancedHDR10HDRMetadataType;
    EnumHLWMode enumPCMHLWMode;
} StructAdvancedHDR10SettingInfo;

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Struct for DM Port Support
//--------------------------------------------------
typedef struct
{
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    BYTE b1D0Support : 1;
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    BYTE b1D1Support : 1;
#endif
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
    BYTE b1D2Support : 1;
#endif
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
    BYTE b1D3Support : 1;
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
    BYTE b1D4Support : 1;
#endif
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
    BYTE b1D5Support : 1;
#endif
} StructDMSupportInfo;
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DM Color format Info Change
//--------------------------------------------------
typedef  struct
{
    BYTE b1SyncDigitalDMColorInfoChangeReset : 1;
    BYTE b1SyncDigitalDMColorInfoChangeBGEnable : 1;
} StructDigitalDMColorInfoChange;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern StructPortCableStatus g_stSyncPortCableStatus;

#if(_DUAL_DP_SUPPORT == _ON)
extern EnumInputPort g_enumSyncDualDpPortSwitchSelect;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern volatile bit g_bSyncDigitalColorInfoChangeReset;

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern volatile StructDigitalDMColorInfoChange g_stSyncDigitalDMColorInfoChange;
#endif
#endif

#if(_DP_SUPPORT == _ON)
extern bit g_pbSyncDpMstDCOffHPDToggleHoldFlag[3];
extern bit g_bSyncDpDCOffHPDToggleFlag;
extern BYTE g_ucSyncDpIrqTime_10us;
extern StructDPCapSwitchInfo g_stSyncDpCapSwitch;
#endif

#if(_HDR10_SUPPORT == _ON)
extern StructHDR10StaticMetaData g_pstSyncHDR10SaticMetadata[_HDR_METADATA_PORT_VALID];
extern StructHDR10PortSettingInfo g_stSyncHDR10PortSettingInfo;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
extern StructFreeSyncIIInfo g_pstSyncFreeIIMetadata[_MULTI_DISPLAY_MAX];
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
extern StructHDR10SBTMInfo g_pstSyncHDR10SBTMMetadata[_HDR_METADATA_PORT_VALID];
#endif

// Advanced HDR10
#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern volatile StructAdvancedHDR10SettingInfo g_stSyncAdvancedHDR10SettingInfo;
extern volatile StructAdvancedHDR10MetaData g_stSyncAdvancedHDR10Metadata;
extern volatile StructAdvancedHDR10MetaData g_stSyncAdvancedHDR10BackUpMetadata;
#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
extern volatile StructAdvancedHDR10DHDRMetaData g_stSyncAdvancedHDR10DHDRMetaData;
#endif
extern volatile BYTE g_pucSyncAdvancedHDR10YmTable[710];
#endif

#if(_DM_FUNCTION == _ON)
extern StructDMSupportInfo g_stSyncDMSupportInfo;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerSyncGetCtaExtDbAddress(WORD *pusCtaDataBlockAddr, BYTE *pucDdcRamAddr);
extern void ScalerSyncGetDidExtDbAddress(WORD *pusDidDataBlockAddr, BYTE *pucDdcRamAddr);

#if(_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerSyncUpdateSecData(EnumInputPort enumInputPort, EnumDisplayRegion enumDisplayRegion, EnumHDRInfoChgPolling enumHDRInfoChgPolling);
#endif

#if(_DP_SUPPORT == _ON)
extern void ScalerSyncDpScanInitial(EnumInputPort enumInputPort);
extern bit ScalerSyncDpFakePowerSavingCheck(void);
extern void ScalerSyncDpCapabilitySwitchProc(void);
#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
extern void ScalerSyncDpCalculateLinkRate(EnumInputPort enumInputPort);
#endif
extern void ScalerSyncDpPowerSwitchHpdToggleProc(EnumPowerAction enumPowerAction);

#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerSyncDpFakePowerOffCheck(void);
extern void ScalerSyncDpMstFakeOffDoneProc(void);
#endif

extern WORD ScalerSyncGetDpRxPortEdidBw(EnumDpEdidPort enumDpEdidPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerSyncDpTxCloneOutputPortCheck(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern void ScalerSyncDpHdcpRepeaterSupportProc(void);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
extern void ScalerSyncHdcpEnableDownLoadDPTxKey(bit bEnable);
extern void ScalerSyncHdcpDownLoadDPTxAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerSyncHdcpDownLoadDPTxAKey(WORD usLength, BYTE *pucReadArray);
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern void ScalerSyncCompatibleModeConfigAllSwitchToDxFlag(EnumInputPort enumInputPort);
#endif
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
extern bit ScalerSyncCheckUrgentEvent(void);
extern bit ScalerSyncGetUrgentEventFlg(void);
extern void ScalerSyncClrUrgentEventFlg(void);
#endif

extern bit ScalerSyncGetCableStatus(EnumInputPort enumInputPort);
extern void ScalerSyncSetCableStatus(EnumInputPort enumInputPort, bit bStatus);
extern bit ScalerSyncGetCablePinStatus(EnumInputPort enumInputPort);

#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
extern bit ScalerSyncGetTypeCAltModeStatus(EnumInputPort enumInputPort);
extern void ScalerSyncSetTypeCAltModeStatus(EnumInputPort enumInputPort, bit bStatus);
extern bit ScalerSyncGetTypeCSupportStatus(EnumInputPort enumInputPort);
#endif

extern void ScalerSyncActiveProc(EnumSourceType enumSourceType);
extern void ScalerSyncResetProc(EnumInputPort enumInputPort);
extern void ScalerSyncPowerProc(EnumPowerAction enumPowerAction);

#if(_HW_VGA_ADC_SUPPORT == _ON)
extern void ScalerSyncAdcApllPowerDown(void);
#endif

extern void ScalerSyncInterfaceProc(EnumInputPort enumInputPort, bit bEnable);

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern void ScalerSyncHdcpDownLoadBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerSyncHdcpDownLoadKey(WORD usLength, BYTE *pucReadArray);
extern void ScalerSyncHdcpEnableDownLoadKey(bit bEnable);
extern EnumHDCPType ScalerSyncHdcpCheckEnabled(EnumInputPort enumInputPort);

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
extern EnumHDCPType ScalerSyncHdcpCheckEnabledUnderPowerOff(EnumInputPort enumInputPort);
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _ON)
extern BYTE ScalerSyncDxHDRMetadataIndexMapping(EnumInputPort enumInputPort);
extern void ScalerSyncHDR10GetCurrentStatus(EnumInputPort enumInputPort, EnumHDRInfoChgPolling enumHDRInfoChgPolling);
#endif
#if(_HDMI_SBTM_SUPPORT == _ON)
extern void ScalerSyncHDR10SBTMGetCurrentStatus(EnumInputPort enumInputPort, EnumHDRInfoChgPolling enumHDRInfoChgPolling);
#endif
#endif

extern WORD ScalerSyncGetInputPixelClk(EnumInputPort enumInputPort);
extern WORD ScalerSyncGetNativeInputPixelClk(EnumInputPort enumInputPort);

#if(((_DP_SUPPORT == _ON) && (_DP_PR_MODE_SUPPORT == _ON)) || ((_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)))
extern void ScalerSyncPRModeCheckProc(EnumInputPort enumInputPort);
#endif

#if(_DM_FUNCTION == _ON)
extern void ScalerSyncDMSetSupport(EnumInputPort enumInputPort, EnumDMSupport enumDMSupport);
#endif

