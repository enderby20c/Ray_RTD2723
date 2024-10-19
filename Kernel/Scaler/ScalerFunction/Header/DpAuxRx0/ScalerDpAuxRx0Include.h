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
// ID Code      : ScalerDpAuxRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_AUX_RX0_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define RST_DP_AUX_RX0_FIFO_POINTER_T2INT()             {Scaler32SetBit_T2INT(PB18006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX0_FIFO_POINTER_EXINT0()            {Scaler32SetBit_EXINT0(PB18006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX0_INT_FIFO_POINTER_T2INT()         {Scaler32SetBit_T2INT(PB18006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT22)}
#define RST_DP_AUX_RX0_INT_FIFO_POINTER_EXINT0()        {Scaler32SetBit_EXINT0(PB18006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT22)}
#else
#define RST_DP_AUX_RX0_FIFO_POINTER_T2INT()             {Scaler32SetBit_T2INT(PB18002_10_AUX_STATUS, ~(_BIT23 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX0_FIFO_POINTER_EXINT0()            {Scaler32SetBit_EXINT0(PB18002_10_AUX_STATUS, ~(_BIT23 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#endif

#define GET_DP_AUX_RX0_LINK_TRAINING_STATUS()           (g_ucDpAuxRx0LTStatus)
#define SET_DP_AUX_RX0_LINK_TRAINING_STATUS(x)          (g_ucDpAuxRx0LTStatus = (x))

#define GET_DP_AUX_RX0_TOGGLE()                         (Scaler32GetBit(PB18001_0C_AUX_IRQ_FLAG, _BIT12) == _BIT12)
#define CLR_DP_AUX_RX0_TOGGLE()                         {Scaler32SetDWord(PB18001_0C_AUX_IRQ_FLAG, _BIT12);}

#define GET_DP_AUX_RX0_COMMAND_NO_REPLY()               (g_bDpAuxRx0CommandNoReply)
#define SET_DP_AUX_RX0_COMMAND_NO_REPLY()               (g_bDpAuxRx0CommandNoReply = _TRUE)
#define CLR_DP_AUX_RX0_COMMAND_NO_REPLY()               (g_bDpAuxRx0CommandNoReply = _FALSE)

#define GET_DP_AUX_RX0_MODE_T2INT()                     ((EnumDpAuxRxModeStatus)((Scaler32GetBit_T2INT(_REG_DP_AUX_RX0_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define GET_DP_AUX_RX0_MODE_EXINT()                     ((EnumDpAuxRxModeStatus)((Scaler32GetBit_EXINT0(_REG_DP_AUX_RX0_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define GET_DP_AUX_RX0_MODE()                           ((EnumDpAuxRxModeStatus)((Scaler32GetBit(_REG_DP_AUX_RX0_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define SET_DP_AUX_RX0_MANUAL_MODE_T2INT()              {ScalerDpAuxRx0SetManualMode_T2INT();}
#define SET_DP_AUX_RX0_MANUAL_MODE_EXINT()              {ScalerDpAuxRx0SetManualMode_EXINT0();}
#define SET_DP_AUX_RX0_MANUAL_MODE()                    {ScalerDpAuxRx0SetManualMode();}
#define SET_DP_AUX_RX0_AUTO_MODE_T2INT()                {ScalerDpAuxRx0SetAutoMode_T2INT();}
#define SET_DP_AUX_RX0_AUTO_MODE_EXINT()                {ScalerDpAuxRx0SetAutoMode_EXINT0();}
#define SET_DP_AUX_RX0_AUTO_MODE()                      {ScalerDpAuxRx0SetAutoMode();}

#define GET_DP_AUX_RX0_VALID_VIDEO_CHECK()              (g_bDpAuxRx0Info)
#define SET_DP_AUX_RX0_VALID_VIDEO_CHECK()              (g_bDpAuxRx0Info = _TRUE)
#define CLR_DP_AUX_RX0_VALID_VIDEO_CHECK()              {\
                                                            ScalerDpAuxRxCancelValidSignalDetection(_D0_INPUT_PORT);\
                                                            (g_bDpAuxRx0Info = _FALSE);\
                                                        }
#define GET_DP_AUX_RX0_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx0DpcdUpdateProtect.bDpAuxRxDpcdUpdate)
#define SET_DP_AUX_RX0_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx0DpcdUpdateProtect.bDpAuxRxDpcdUpdate = _TRUE)
#define CLR_DP_AUX_RX0_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx0DpcdUpdateProtect.bDpAuxRxDpcdUpdate = _FALSE)
#define GET_DP_AUX_RX0_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx0DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate)
#define SET_DP_AUX_RX0_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx0DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate = _TRUE)
#define CLR_DP_AUX_RX0_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx0DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate = _FALSE)
#define GET_DP_AUX_RX0_MODE_BACKUP_EXINT0()             (g_enumDpAuxRx0ModeBackup_EXINT0)
#define SET_DP_AUX_RX0_MODE_BACKUP_EXINT0(x)            (g_enumDpAuxRx0ModeBackup_EXINT0 = (x))
#define CLR_DP_AUX_RX0_MODE_BACKUP_EXINT0()             (g_enumDpAuxRx0ModeBackup_EXINT0 = _DP_RX_AUX_AUTO_MODE)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define GET_DP_AUX_RX0_INT_PROTECT()                    (g_bDpAuxRx0IntProtect)
#define SET_DP_AUX_RX0_INT_PROTECT()                    (g_bDpAuxRx0IntProtect = _TRUE)
#define CLR_DP_AUX_RX0_INT_PROTECT()                    (g_bDpAuxRx0IntProtect = _FALSE)
#endif

//--------------------------------------------------
// Macro of Dp Clear CRC Value
//--------------------------------------------------
#define CLR_DP_AUX_RX0_CRC_VALUE_EXINT0()               {ScalerDpAuxRx0DpcdGroupReset_EXINT0(0x00, 0x02, 0x40, 6);}

#define CLR_DP_AUX_RX0_DSC_CRC_VALUE_EXINT0()           {ScalerDpAuxRx0DpcdGroupReset_EXINT0(0x00, 0x02, 0x62, 6);}

//--------------------------------------------------
// Macro of Dp Error Count Read Record
//--------------------------------------------------
#define GET_DP_AUX_RX0_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx0SourceRDErrorCount)
#define SET_DP_AUX_RX0_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx0SourceRDErrorCount = _TRUE)
#define CLR_DP_AUX_RX0_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx0SourceRDErrorCount = _FALSE)

//--------------------------------------------------
// Definitions of AUX Power Status
//--------------------------------------------------
#define GET_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx0PowerInfo.b1DpCheckAuxChNoPowerDebounce)
#define SET_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx0PowerInfo.b1DpCheckAuxChNoPowerDebounce = _TRUE)
#define CLR_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx0PowerInfo.b1DpCheckAuxChNoPowerDebounce = _FALSE)

#define GET_DP_AUX_RX0_CHECK_CH_POWER_STATUS()          (g_stDpAuxRx0PowerInfo.b2DpCheckAuxChPowerStatus)
#define SET_DP_AUX_RX0_CHECK_CH_POWER_STATUS(x)         (g_stDpAuxRx0PowerInfo.b2DpCheckAuxChPowerStatus = (x))
#define CLR_DP_AUX_RX0_CHECK_CH_POWER_STATUS()          (g_stDpAuxRx0PowerInfo.b2DpCheckAuxChPowerStatus = _DP_RX_AUX_POWER_STATUS_NONE)

#define GET_DP_AUX_RX0_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx0PowerInfo.b1DpAuxChPowerOnWakeUp)
#define SET_DP_AUX_RX0_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx0PowerInfo.b1DpAuxChPowerOnWakeUp = _TRUE)
#define CLR_DP_AUX_RX0_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx0PowerInfo.b1DpAuxChPowerOnWakeUp = _FALSE)

#define GET_DP_AUX_RX0_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx0PowerInfo.b1DpSourceFirstPowerOn)
#define SET_DP_AUX_RX0_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx0PowerInfo.b1DpSourceFirstPowerOn = _TRUE)
#define CLR_DP_AUX_RX0_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx0PowerInfo.b1DpSourceFirstPowerOn = _FALSE)

#define GET_DP_AUX_RX0_SOURCE_WRITE_POWER_UP()          (g_stDpAuxRx0PowerInfo.enumDpSourceWritePowerUp)
#define SET_DP_AUX_RX0_SOURCE_WRITE_POWER_UP(x)         (g_stDpAuxRx0PowerInfo.enumDpSourceWritePowerUp = (x))
#define CLR_DP_AUX_RX0_SOURCE_WRITE_POWER_UP()          (g_stDpAuxRx0PowerInfo.enumDpSourceWritePowerUp = _DP_SOURCE_WRITE_POWER_UP_NONE)

#if(_DP_TX_SUPPORT == _ON)
#define CLR_DP_AUX_RX0_HDCP_KSV_FIFO_INT_FLAG()         {\
                                                            Scaler32SetDWord(PB18001_8C_AUX_HDCP_IRQ_FLAG, _BIT10);\
                                                        }

#define CLR_DP_AUX_RX0_HDCP_KSV_FIFO_INT_FLAG_EXINT()   {\
                                                            Scaler32SetDWord_EXINT0(PB18001_8C_AUX_HDCP_IRQ_FLAG, _BIT10);\
                                                        }

#define GET_DP_AUX_RX0_HDCP_REPEATER_SUPPORT()          ((ScalerDpAuxRx0GetDpcdInfo(0x06, 0x80, 0x28) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
#endif

//--------------------------------------------------
// Macro of AUX Reset Flag
//--------------------------------------------------
#define GET_DP_RX_AUX_RX0_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx0HpdLowResetFlag)
#define SET_DP_RX_AUX_RX0_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx0HpdLowResetFlag = _TRUE)
#define CLR_DP_RX_AUX_RX0_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx0HpdLowResetFlag = _FALSE)

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
//--------------------------------------------------
// Macro of DP IRQ Assert Timer2 Event
//--------------------------------------------------
#define GET_DP_AUX_RX0_HPD_IRQ_ASSERT_T2_EVENT()        (g_bDpAuxRx0HpdIrqAssertT2Event)
#define SET_DP_AUX_RX0_HPD_IRQ_ASSERT_T2_EVENT()        {\
                                                            g_bDpAuxRx0HpdIrqAssertT2Event = _TRUE;\
                                                            DP_RX_HPD_IRQ_ASSERT_T2_DELAY_INITIAL();\
                                                        }
#define CLR_DP_AUX_RX0_HPD_IRQ_ASSERT_T2_EVENT()        (g_bDpAuxRx0HpdIrqAssertT2Event = _FALSE)
#endif

//--------------------------------------------------
// Macro of DP PR DPCD Info
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
#define GET_DP_AUX_RX0_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx0PRModeCrcEnableFlag)
#define SET_DP_AUX_RX0_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx0PRModeCrcEnableFlag = _TRUE)
#define CLR_DP_AUX_RX0_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx0PRModeCrcEnableFlag = _FALSE)
#endif

#define GET_DP_AUX_RX0_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx0MSTBackupLinkStatusFlg_INT)
#define SET_DP_AUX_RX0_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx0MSTBackupLinkStatusFlg_INT = _TRUE)
#define CLR_DP_AUX_RX0_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx0MSTBackupLinkStatusFlg_INT = _FALSE)

//--------------------------------------------------
// Macro of DP RX0 Current DP Version
//--------------------------------------------------
#define GET_DP_AUX_RX0_CURRENT_VERSION()                (g_enumDpAuxRx0CurrentVersion)
#define SET_DP_AUX_RX0_CURRENT_VERSION(x)               (g_enumDpAuxRx0CurrentVersion = (x))

//--------------------------------------------------
// Macro of DP RX0 Current AUX Receive Mode
//--------------------------------------------------
#define GET_DP_AUX_RX0_RECEIVE_MODE()                   (g_enumDpAuxRx0ReceiveMode)
#define SET_DP_AUX_RX0_RECEIVE_MODE(x)                  (g_enumDpAuxRx0ReceiveMode = (x))

//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_AUX_RX0_FAKE_LINK_TRAINING()             ((bit) g_bDpAuxRx0FakeLT)
#define SET_DP_AUX_RX0_FAKE_LINK_TRAINING()             (g_bDpAuxRx0FakeLT = _TRUE)
#define CLR_DP_AUX_RX0_FAKE_LINK_TRAINING()             (g_bDpAuxRx0FakeLT = _FALSE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bDpAuxRx0CommandNoReply;
extern DWORD g_ulDpAuxRx0Backup_EXINT0;
extern DWORD g_ulDpAuxRx0Backup_WDINT;
extern volatile StructDpAuxRxDpcdUpdateProtect g_stDpAuxRx0DpcdUpdateProtect;
extern volatile StructDpAuxRxDpcdUpdateProtect g_stDpAuxRx0DpcdUpdateProtect_WDINT;
extern bit g_bDpAuxRx0SourceRDErrorCount;
extern volatile BYTE g_ucDpAuxRx0LTStatus;
extern bit g_bDpAuxRx0Info;
extern bit g_bDpAuxRx0Tp1Initial;

#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
extern BYTE g_pucDpAuxRx0MaxSwing[4];
#endif
extern BYTE g_ucDpAuxRx0PreferPreset;
extern BYTE g_ucDpAuxRx0LinkStatus01;
extern BYTE g_ucDpAuxRx0LinkStatus23;
extern BYTE g_ucDpAuxRx0LinkRequest01;
extern BYTE g_ucDpAuxRx0LinkRequest23;
extern bit g_bDpAuxRx0FakeLT;
extern volatile EnumDpLinkRate g_enumDpAuxRx0LinkRate;
extern volatile EnumDpLaneCount g_enumDpAuxRx0LaneCount;

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern volatile EnumDpLinkChannelCodingType g_enumDpAuxRx0CodingType;
#endif
extern BYTE g_ucDpAuxRx0TrainingPatternSet;

extern BYTE g_ucDpAuxRx0LTPatternSet;
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern volatile StructDpAuxRxReceiveBackup g_stDpAuxRx0ReceiveBackup;
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern volatile WORD g_usDpAuxRx0StreamIdAddrEnd;
#endif
#if(_DP_RX_FEC_SUPPORT == _ON)
extern volatile bit g_bDpAuxRx0FecStatusW1cProtect;
#endif
#endif

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
extern BYTE g_ucDpAuxRx0AccessBackup_EXINT0;
extern BYTE g_ucDpAuxRx0AccessBackup_WDINT;
#endif
extern BYTE g_pucDpAuxRx0LinkStatusBackup_INT[3];
extern bit g_bDpAuxRx0HpdLowResetFlag;
extern EnumDpVersionType g_enumDpAuxRx0CurrentVersion;
extern EnumDpAuxRxModeStatus g_enumDpAuxRx0ModeBackup_EXINT0;
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern volatile bit g_bDpAuxRx0IntProtect;
#endif

extern volatile StructDpRxAuxPowerInfo g_stDpAuxRx0PowerInfo;

extern volatile bit g_bDpAuxRx0MSTBackupLinkStatusFlg_INT;

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern volatile bit g_bDpAuxRx0HpdIrqAssertT2Event;
extern EnumDpAuxRxModeStatus g_enumDpAuxRx0AutoModeBackup_T2INT;
#endif

#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
extern BYTE g_ucDpAuxRx0Tp1PermitSwingLevel0;
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern bit g_bDpAuxRx0PRModeCrcEnableFlag;
#endif

extern EnumDpAuxReceiveMode g_enumDpAuxRx0ReceiveMode;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAuxRx0Initial(void);
extern void ScalerDpAuxRx0AuxIntInitial(void);
extern void ScalerDpAuxRx0ChangeDpcdVersion(void);
extern void ScalerDpAuxRx0TypeCPinAssert(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpAuxRx0SetSinkDeviceSpecificField(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx0SetBranchDeviceSpecificField(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx0ClrBranchDeviceSpecificField(void);

extern void ScalerDpAuxRx0SwitchDpcdAddrIrqSetting(void);
#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpAuxRx0SwitchMstProtocolIrq(void);
#endif

extern void ScalerDpAuxRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
extern EnumDpHotPlugTime ScalerDpAuxRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpAuxRx0DisconnectReset(void);
extern void ScalerDpAuxRx0AfterHpdToggleProc(void);
extern void ScalerDpAuxRx0LinkStatusIRQ(void);
extern bit ScalerDpAuxRx0VersionChange(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx0PowerOn(void);
extern void ScalerDpAuxRx0HpdIrqAssert(void);
extern void ScalerDpAuxRx0FakeLTProtect(void);
extern void ScalerDpAuxRx0SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpAuxRx0SetManualMode(void);
extern void ScalerDpAuxRx0SetAutoMode(void);
extern void ScalerDpAuxRx0SetDpcdAccessAddr(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx0SetDpcdAccessByteData(BYTE ucDpcdData);
extern void ScalerDpAuxRx0SetDpcdAccessBitData(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx0GetDpcdAccessData(void);
extern void ScalerDpAuxRx0DpcdAutoIncEnable(bit bEnable);
extern BYTE ScalerDpAuxRx0GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx0GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdBitWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorBitWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0DpcdWildCardSetting(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask);
extern void ScalerDpAuxRx0SetDpcdWildCardForceDeferEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx0GetDpcdWildCardForceDeferEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx0SetDpcdWildCardIntEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx0GetDpcdWildCardIntEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern bit ScalerDpAuxRx0DpcdWildCardIntCheck(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx0DpcdWildCardIntClr(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx0AccessSelect(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
extern void ScalerDpAuxRx0SetDpcdAttribute(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx0SetDpcdIntEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable);
extern bit ScalerDpAuxRx0GetDpcdIntEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern void ScalerDpAuxRx0SetDpcdForceDeferEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, bit bEnable);
extern bit ScalerDpAuxRx0GetDpcdForceDeferEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern void ScalerDpAuxRx0RequestReset(void);
extern void ScalerDpAuxRx0DpcdWrite1ClearInitial(void);
extern void ScalerDpAuxRx0DpcdReadClearInitial(void);
extern void ScalerDpAuxRx0DpcdWildCardInitial(void);
extern void ScalerDpAuxRx0DpcdRemapInitial(void);
extern void ScalerDpAuxRx0DpcdRemapSetting(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen);
extern bit ScalerDpAuxRx0GetDpcdRemapEnable(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx0DpcdRemapReset(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx0DpcdRemapIntCheck(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx0DpcdRemapIntClr(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx0InitialDpcdAttribute(void);
#else
extern void ScalerDpAuxRx0DpcdForceNack(void);
extern void ScalerDpAuxRx0DpcdRemap32BSetting(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx0DpcdRemap16BSetting(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx0DpcdRemap8BSetting(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern bit ScalerDpAuxRx0GetDpcdRemap32BEnable(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx0GetDpcdRemap16BEnable(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx0GetDpcdRemap8BEnable(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx0DpcdRemap32BReset(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx0DpcdRemap16BReset(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx0DpcdRemap8BReset(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx0DpcdRemap32BIntEnable(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx0DpcdRemap16BIntEnable(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx0DpcdRemap8BIntEnable(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern bit ScalerDpAuxRx0DpcdRemap32BIntCheck(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx0DpcdRemap16BIntCheck(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx0DpcdRemap8BIntCheck(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx0DpcdRemap32BIntClr(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx0DpcdRemap16BIntClr(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx0DpcdRemap8BIntClr(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
#endif
extern void ScalerDpAuxRx0SetDpcdLinkRate(EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpAuxRx0SetDpcdMaxLinkRateCapability(EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate);
extern EnumDpLinkRate ScalerDpAuxRx0GetDpcdMaxLinkRateCapability(void);
extern void ScalerDpAuxRx0HpdTogglePhyResetProc(bit bHpdHighLow);
extern void ScalerDpAuxRx0DpcdGroupReset(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, WORD usLen);
extern void ScalerDpAuxRx0DpcdLinkConfigReset(void);
extern void ScalerDpAuxRx0DpcdSourceOUIReset(void);
extern void ScalerDpAuxRx0DpcdProtocolConverterReset(void);

#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpAuxRx0DscDpcdSetting(void);
extern void ScalerDpAuxRx0DscDpcdExtendedCapSetting(void);
extern void ScalerDpAuxRx0DscIrqCtrl(bit bEnable);
extern void ScalerDpAuxRx0DscEnable_EXINT0(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpAuxRx0MstReset(void);
#endif
extern bit ScalerDpAuxRx0ChSourcePowerCheck(void);
extern void ScalerDpAuxRx0AuxChPowerStatusCheck(bit bCableStatus);

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
extern void ScalerDpAuxRx0MarginLinkCapabilitySwitchProc(BYTE ucDPPhyLinkRate);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpAuxRx0Hdcp2LoadCertRrxKey(void);
#endif

extern void ScalerDpAuxRx0TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern BYTE ScalerDpAuxRx0TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx0TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpAuxRx0TrainingPatternEnd_EXINT0(void);
extern BYTE ScalerDpAuxRx0PhyCtsTrainingPattern1_EXINT0(void);
extern BYTE ScalerDpAuxRx0PhyCtsTrainingPattern2_EXINT0(void);
extern void ScalerDpAuxRx0PhyCtsTrainingPatternEnd_EXINT0(void);
extern BYTE ScalerDpAuxRx0Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx0Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE ScalerDpAuxRx0Tp3Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpAuxRx0SetCodingType(EnumDpLinkChannelCodingType enumCodingType);
#endif
extern BYTE ScalerDpAuxRx0PhyCtsTp1Check_EXINT0(void);
extern BYTE ScalerDpAuxRx0PhyCtsTp2Check_EXINT0(void);
extern bit ScalerDpAuxRx0PreIntHandler_EXINT0(void);
extern void ScalerDpAuxRx0HighPriorityIntHandler_EXINT0(void);
extern void ScalerDpAuxRx0LowPriorityIntHandler_EXINT0(void);
extern void ScalerDpAuxRx0SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpAuxRx0SetManualMode_EXINT0(void);
extern void ScalerDpAuxRx0SetAutoMode_EXINT0(void);
extern void ScalerDpAuxRx0SetDpcdAccessAddr_EXINT0(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx0SetDpcdAccessByteData_EXINT0(BYTE ucDpcdData);
extern void ScalerDpAuxRx0SetDpcdAccessBitData_EXINT0(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx0GetDpcdAccessData_EXINT0(void);
extern void ScalerDpAuxRx0DpcdAutoIncEnable_EXINT0(bit bEnable);
extern BYTE ScalerDpAuxRx0GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx0GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdBitWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdBitWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorBitWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0DpcdGroupReset_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, WORD usLen);
extern void ScalerDpAuxRx0SetDpcdLinkStatusForceDefer_EXINT0(bit bEnable);
extern void ScalerDpAuxRx0WaitRcv_EXINT0(void);
extern void ScalerDpAuxRx0DpcdWildCardSetting_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask);
extern void ScalerDpAuxRx0SetDpcdWildCardForceDeferEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx0GetDpcdWildCardForceDeferEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx0SetDpcdWildCardIntEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx0GetDpcdWildCardIntEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern bit ScalerDpAuxRx0DpcdWildCardIntCheck_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx0DpcdWildCardIntClr_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern bit ScalerDpAuxRx0DpcdWildCardIntHandler_EXINT0(DWORD ulDpcdWildCardFlag);
extern void ScalerDpAuxRx0AccessSelect_EXINT0(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
extern void ScalerDpAuxRx0SetDpcdAttribute_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx0SetDpcdIntEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable);
extern bit ScalerDpAuxRx0GetDpcdIntEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern void ScalerDpAuxRx0SetDpcdForceDeferEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, bit bEnable);
extern bit ScalerDpAuxRx0GetDpcdForceDeferEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern void ScalerDpAuxRx0ClrDpcdIntFlag_EXINT0(void);
extern void ScalerDpAuxRx0RequestReset_EXINT0(void);
extern void ScalerDpAuxRx0RequestAnalyze_EXINT0(void);
extern void ScalerDpAuxRx0WriteIntRequestDataBackup_EXINT0(void);
extern bit ScalerDpAuxRx0ScanReqDpcdAddr_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern bit ScalerDpAuxRx0ScanLinkTrainingAddr_EXINT0(void);
extern bit ScalerDpAuxRx0ScanLinkStatusAddr_EXINT0(void);
extern void ScalerDpAuxRx0DpcdIrqProtect_T2INT(void);
extern bit ScalerDpAuxRx0DpcdIntCaseHandler_EXINT0(void);
extern bit ScalerDpAuxRx0I2cIntCaseHandler_EXINT0(void);
extern bit ScalerDpAuxRx0DpcdWrite1ClearHandler_EXINT0(void);
extern bit ScalerDpAuxRx0DpcdReadClearHandler_EXINT0(void);
extern void ScalerDpAuxRx0DpcdRemapSetting_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen);
extern bit ScalerDpAuxRx0GetDpcdRemapEnable_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx0DpcdRemapReset_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx0DpcdRemapIntCheck_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx0DpcdRemapIntClr_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx0DpcdRemapIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
#else
extern void ScalerDpAuxRx0DpcdRemap32BSetting_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx0DpcdRemap16BSetting_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx0DpcdRemap8BSetting_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern bit ScalerDpAuxRx0GetDpcdRemap32BEnable_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx0GetDpcdRemap16BEnable_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx0GetDpcdRemap8BEnable_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx0DpcdRemap32BReset_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx0DpcdRemap16BReset_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx0DpcdRemap8BReset_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx0DpcdRemap32BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx0DpcdRemap16BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx0DpcdRemap8BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern bit ScalerDpAuxRx0DpcdRemap32BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx0DpcdRemap16BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx0DpcdRemap8BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx0DpcdRemap32BIntClr_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx0DpcdRemap16BIntClr_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx0DpcdRemap8BIntClr_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern bit ScalerDpAuxRx0DpcdRemap32BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
extern bit ScalerDpAuxRx0DpcdRemap16BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
extern bit ScalerDpAuxRx0DpcdRemap8BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
#endif
extern void ScalerDpAuxRx0SetManualMode_T2INT(void);
extern void ScalerDpAuxRx0SetAutoMode_T2INT(void);
extern void ScalerDpAuxRx0EdidReadAddrOnlyProtect_EXINT0(void);
extern void ScalerDpAuxRx0DpcdSymbolErrorCountHandler_EXINT0(void);
#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRx0DpcdFecErrorCount_EXINT0(void);
extern void ScalerDpAuxRx0DpcdFecStatusW1cProtectHandler_EXINT0(void);
extern void ScalerDpAuxRx0SetFecStatusW1cProtectEnable_EXINT0(bit bEnable);
extern bit ScalerDpAuxRx0GetFecStatusW1cProtectEnable_EXINT0(void);
#endif
extern void ScalerDpAuxRx0DpcdLinkTrainingHandler_EXINT0(void);
extern void ScalerDpAuxRx0DpcdPowerStateHandler_EXINT0(void);
extern void ScalerDpAuxRx0DpcdHdcp14AksvHandler_EXINT0(void);
extern void ScalerDpAuxRx0DpcdTestCRCHandler_EXINT0(void);
#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpAuxRx0DpcdPrModeHandler_EXINT0(void);
#endif
#if((_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
extern void ScalerDpAuxRx0DpcdCableIDSyncHandler_EXINT0(void);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRx0FecDpcdSetting(void);
extern void ScalerDpAuxRx0SetFecStatusW1cProtectEnable(bit bEnable);
extern bit ScalerDpAuxRx0GetFecStatusW1cProtectEnable(void);
extern void ScalerDpAuxRx0FecHanlder_EXINT0(void);
#endif

extern void ScalerDpAuxRx0DpcdPortAccessBackup_WDINT(void);
extern void ScalerDpAuxRx0DpcdPortAccessBackupRestore_WDINT(void);
extern void ScalerDpAuxRx0SetDpcdAccessAddr_WDINT(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx0SetDpcdAccessByteData_WDINT(BYTE ucDpcdData);
extern void ScalerDpAuxRx0SetDpcdAccessBitData_WDINT(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx0GetDpcdAccessData_WDINT(void);
extern void ScalerDpAuxRx0DpcdAutoIncEnable_WDINT(bit bEnable);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx0AccessSelect_WDINT(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
#endif
extern BYTE ScalerDpAuxRx0GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx0GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdBitValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdBitWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdBitWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx0SetDpcdMirrorBitValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorBitWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx0HpdIrqAssert_WDINT(void);
extern void ScalerDpAuxRx0DpcdLinkStatusReset_WDINT(EnumDpResetStatus enumDpResetStatus);

#if((_D0_DP_MST_PORT_SUPPORT == _ON) || (_DP_HDCP2_RX_SUPPORT == _ON))
extern void ScalerDpAuxRx0HdcpResetDpcdInfo_EXINT0(void);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpAuxRx0CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
extern void ScalerDpAuxRx0SetMPrimeReadDefer(bit bEnable);
extern void ScalerDpAuxRx0SetMPrimeReadDefer_EXINT0(bit bEnable);
#endif

extern void ScalerDpAuxRx0HpdIrqAssert_EXINT0(void);
extern void ScalerDpAuxRx0DpcdPortAccessBackup_EXINT0(void);
extern void ScalerDpAuxRx0DpcdPortAccessBackupRestore_EXINT0(void);

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpAuxRx0SetAuxReadInterval_EXINT0(void);
extern BYTE ScalerDpAuxRx0TrainingPattern3_EXINT0(EnumDpLinkTrainingType enumDpLtType);
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpAuxRx0Hdcp2TypeValueReset(void);
extern void ScalerDpAuxRx0Hdcp2TypeValueReset_EXINT0(void);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx0Hdcp2StreamIDTypeReset(void);
extern void ScalerDpAuxRx0Hdcp2StreamIDTypeReset_EXINT0(void);
#endif
extern BYTE ScalerDpAuxRx0Hdcp2GetMessageID_EXINT0(void);
extern void ScalerDpAuxRx0Hdcp2HandshakeIRQ(bit bEnable);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpAuxRx0PRModeDpcdSetting(void);
extern bit ScalerDpAuxRx0PRModeFlagStatus(void);
extern void ScalerDpAuxRx0DpcdPRModeErrorStateUpdate(EnumPRModeErrorStatus enumPRModeErrorStatus);
extern void ScalerDpAuxRx0DpcdPRModeStatusUpdate(EnumPRModeStatus enumPRModeStatus);
extern void ScalerDpAuxRx0DpcdPRModeErrorStateUpdate_EXINT0(EnumPRModeErrorStatus enumPRModeErrorStatus);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpAuxRx0AuxlessAlpmDpcdSetting(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
extern void ScalerDpAuxRx0HdrDpcdSetting(void);
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern void ScalerDpAuxRx0FreesyncDpcdSetting(void);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void ScalerDpAuxRx0AdaptiveSyncDpcdSetting(void);
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpAuxRx0MstProtocolDpcdReset(void);
#endif

#endif // End of #if(_DP_AUX_RX0_SUPPORT == _ON)
