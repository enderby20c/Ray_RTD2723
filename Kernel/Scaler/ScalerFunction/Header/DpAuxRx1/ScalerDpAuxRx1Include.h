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
// ID Code      : ScalerDpAuxRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_AUX_RX1_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define RST_DP_AUX_RX1_FIFO_POINTER_T2INT()             {Scaler32SetBit_T2INT(PB19006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX1_FIFO_POINTER_EXINT0()            {Scaler32SetBit_EXINT0(PB19006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX1_INT_FIFO_POINTER_T2INT()         {Scaler32SetBit_T2INT(PB19006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT22)}
#define RST_DP_AUX_RX1_INT_FIFO_POINTER_EXINT0()        {Scaler32SetBit_EXINT0(PB19006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT22)}
#else
#define RST_DP_AUX_RX1_FIFO_POINTER_T2INT()             {Scaler32SetBit_T2INT(PB19002_10_AUX_STATUS, ~(_BIT23 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX1_FIFO_POINTER_EXINT0()            {Scaler32SetBit_EXINT0(PB19002_10_AUX_STATUS, ~(_BIT23 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#endif

#define GET_DP_AUX_RX1_LINK_TRAINING_STATUS()           (g_ucDpAuxRx1LTStatus)
#define SET_DP_AUX_RX1_LINK_TRAINING_STATUS(x)          (g_ucDpAuxRx1LTStatus = (x))

#define GET_DP_AUX_RX1_TOGGLE()                         (Scaler32GetBit(PB19001_0C_AUX_IRQ_FLAG, _BIT12) == _BIT12)
#define CLR_DP_AUX_RX1_TOGGLE()                         {Scaler32SetDWord(PB19001_0C_AUX_IRQ_FLAG, _BIT12);}

#define GET_DP_AUX_RX1_COMMAND_NO_REPLY()               (g_bDpAuxRx1CommandNoReply)
#define SET_DP_AUX_RX1_COMMAND_NO_REPLY()               (g_bDpAuxRx1CommandNoReply = _TRUE)
#define CLR_DP_AUX_RX1_COMMAND_NO_REPLY()               (g_bDpAuxRx1CommandNoReply = _FALSE)

#define GET_DP_AUX_RX1_MODE_T2INT()                     ((EnumDpAuxRxModeStatus)((Scaler32GetBit_T2INT(_REG_DP_AUX_RX1_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define GET_DP_AUX_RX1_MODE_EXINT()                     ((EnumDpAuxRxModeStatus)((Scaler32GetBit_EXINT0(_REG_DP_AUX_RX1_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define GET_DP_AUX_RX1_MODE()                           ((EnumDpAuxRxModeStatus)((Scaler32GetBit(_REG_DP_AUX_RX1_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define SET_DP_AUX_RX1_MANUAL_MODE_T2INT()              {ScalerDpAuxRx1SetManualMode_T2INT();}
#define SET_DP_AUX_RX1_MANUAL_MODE_EXINT()              {ScalerDpAuxRx1SetManualMode_EXINT0();}
#define SET_DP_AUX_RX1_MANUAL_MODE()                    {ScalerDpAuxRx1SetManualMode();}
#define SET_DP_AUX_RX1_AUTO_MODE_T2INT()                {ScalerDpAuxRx1SetAutoMode_T2INT();}
#define SET_DP_AUX_RX1_AUTO_MODE_EXINT()                {ScalerDpAuxRx1SetAutoMode_EXINT0();}
#define SET_DP_AUX_RX1_AUTO_MODE()                      {ScalerDpAuxRx1SetAutoMode();}

#define GET_DP_AUX_RX1_VALID_VIDEO_CHECK()              (g_bDpAuxRx1Info)
#define SET_DP_AUX_RX1_VALID_VIDEO_CHECK()              (g_bDpAuxRx1Info = _TRUE)
#define CLR_DP_AUX_RX1_VALID_VIDEO_CHECK()              {\
                                                            ScalerDpAuxRxCancelValidSignalDetection(_D1_INPUT_PORT);\
                                                            (g_bDpAuxRx1Info = _FALSE);\
                                                        }
#define GET_DP_AUX_RX1_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx1DpcdUpdateProtect.bDpAuxRxDpcdUpdate)
#define SET_DP_AUX_RX1_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx1DpcdUpdateProtect.bDpAuxRxDpcdUpdate = _TRUE)
#define CLR_DP_AUX_RX1_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx1DpcdUpdateProtect.bDpAuxRxDpcdUpdate = _FALSE)
#define GET_DP_AUX_RX1_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx1DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate)
#define SET_DP_AUX_RX1_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx1DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate = _TRUE)
#define CLR_DP_AUX_RX1_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx1DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate = _FALSE)
#define GET_DP_AUX_RX1_MODE_BACKUP_EXINT0()             (g_enumDpAuxRx1ModeBackup_EXINT0)
#define SET_DP_AUX_RX1_MODE_BACKUP_EXINT0(x)            (g_enumDpAuxRx1ModeBackup_EXINT0 = (x))
#define CLR_DP_AUX_RX1_MODE_BACKUP_EXINT0()             (g_enumDpAuxRx1ModeBackup_EXINT0 = _DP_RX_AUX_AUTO_MODE)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define GET_DP_AUX_RX1_INT_PROTECT()                    (g_bDpAuxRx1IntProtect)
#define SET_DP_AUX_RX1_INT_PROTECT()                    (g_bDpAuxRx1IntProtect = _TRUE)
#define CLR_DP_AUX_RX1_INT_PROTECT()                    (g_bDpAuxRx1IntProtect = _FALSE)
#endif

//--------------------------------------------------
// Macro of Dp Clear CRC Value
//--------------------------------------------------
#define CLR_DP_AUX_RX1_CRC_VALUE_EXINT0()               {ScalerDpAuxRx1DpcdGroupReset_EXINT0(0x00, 0x02, 0x40, 6);}

#define CLR_DP_AUX_RX1_DSC_CRC_VALUE_EXINT0()           {ScalerDpAuxRx1DpcdGroupReset_EXINT0(0x00, 0x02, 0x62, 6);}

//--------------------------------------------------
// Macro of Dp Error Count Read Record
//--------------------------------------------------
#define GET_DP_AUX_RX1_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx1SourceRDErrorCount)
#define SET_DP_AUX_RX1_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx1SourceRDErrorCount = _TRUE)
#define CLR_DP_AUX_RX1_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx1SourceRDErrorCount = _FALSE)

//--------------------------------------------------
// Definitions of AUX Power Status
//--------------------------------------------------
#define GET_DP_AUX_RX1_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx1PowerInfo.b1DpCheckAuxChNoPowerDebounce)
#define SET_DP_AUX_RX1_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx1PowerInfo.b1DpCheckAuxChNoPowerDebounce = _TRUE)
#define CLR_DP_AUX_RX1_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx1PowerInfo.b1DpCheckAuxChNoPowerDebounce = _FALSE)

#define GET_DP_AUX_RX1_CHECK_CH_POWER_STATUS()          (g_stDpAuxRx1PowerInfo.b2DpCheckAuxChPowerStatus)
#define SET_DP_AUX_RX1_CHECK_CH_POWER_STATUS(x)         (g_stDpAuxRx1PowerInfo.b2DpCheckAuxChPowerStatus = (x))
#define CLR_DP_AUX_RX1_CHECK_CH_POWER_STATUS()          (g_stDpAuxRx1PowerInfo.b2DpCheckAuxChPowerStatus = _DP_RX_AUX_POWER_STATUS_NONE)

#define GET_DP_AUX_RX1_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx1PowerInfo.b1DpAuxChPowerOnWakeUp)
#define SET_DP_AUX_RX1_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx1PowerInfo.b1DpAuxChPowerOnWakeUp = _TRUE)
#define CLR_DP_AUX_RX1_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx1PowerInfo.b1DpAuxChPowerOnWakeUp = _FALSE)

#define GET_DP_AUX_RX1_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx1PowerInfo.b1DpSourceFirstPowerOn)
#define SET_DP_AUX_RX1_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx1PowerInfo.b1DpSourceFirstPowerOn = _TRUE)
#define CLR_DP_AUX_RX1_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx1PowerInfo.b1DpSourceFirstPowerOn = _FALSE)

#define GET_DP_AUX_RX1_SOURCE_WRITE_POWER_UP()          (g_stDpAuxRx1PowerInfo.enumDpSourceWritePowerUp)
#define SET_DP_AUX_RX1_SOURCE_WRITE_POWER_UP(x)         (g_stDpAuxRx1PowerInfo.enumDpSourceWritePowerUp = (x))
#define CLR_DP_AUX_RX1_SOURCE_WRITE_POWER_UP()          (g_stDpAuxRx1PowerInfo.enumDpSourceWritePowerUp = _DP_SOURCE_WRITE_POWER_UP_NONE)

#if(_DP_TX_SUPPORT == _ON)
#define CLR_DP_AUX_RX1_HDCP_KSV_FIFO_INT_FLAG()         {\
                                                            Scaler32SetDWord(PB19001_8C_AUX_HDCP_IRQ_FLAG, _BIT10);\
                                                        }

#define CLR_DP_AUX_RX1_HDCP_KSV_FIFO_INT_FLAG_EXINT()   {\
                                                            Scaler32SetDWord_EXINT0(PB19001_8C_AUX_HDCP_IRQ_FLAG, _BIT10);\
                                                        }

#define GET_DP_AUX_RX1_HDCP_REPEATER_SUPPORT()          ((ScalerDpAuxRx1GetDpcdInfo(0x06, 0x80, 0x28) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
#endif

//--------------------------------------------------
// Macro of AUX Reset Flag
//--------------------------------------------------
#define GET_DP_RX_AUX_RX1_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx1HpdLowResetFlag)
#define SET_DP_RX_AUX_RX1_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx1HpdLowResetFlag = _TRUE)
#define CLR_DP_RX_AUX_RX1_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx1HpdLowResetFlag = _FALSE)

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
//--------------------------------------------------
// Macro of DP IRQ Assert Timer2 Event
//--------------------------------------------------
#define GET_DP_AUX_RX1_HPD_IRQ_ASSERT_T2_EVENT()        (g_bDpAuxRx1HpdIrqAssertT2Event)
#define SET_DP_AUX_RX1_HPD_IRQ_ASSERT_T2_EVENT()        {\
                                                            g_bDpAuxRx1HpdIrqAssertT2Event = _TRUE;\
                                                            DP_RX_HPD_IRQ_ASSERT_T2_DELAY_INITIAL();\
                                                        }
#define CLR_DP_AUX_RX1_HPD_IRQ_ASSERT_T2_EVENT()        (g_bDpAuxRx1HpdIrqAssertT2Event = _FALSE)
#endif

//--------------------------------------------------
// Macro of DP PR DPCD Info
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
#define GET_DP_AUX_RX1_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx1PRModeCrcEnableFlag)
#define SET_DP_AUX_RX1_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx1PRModeCrcEnableFlag = _TRUE)
#define CLR_DP_AUX_RX1_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx1PRModeCrcEnableFlag = _FALSE)
#endif

#define GET_DP_AUX_RX1_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx1MSTBackupLinkStatusFlg_INT)
#define SET_DP_AUX_RX1_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx1MSTBackupLinkStatusFlg_INT = _TRUE)
#define CLR_DP_AUX_RX1_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx1MSTBackupLinkStatusFlg_INT = _FALSE)

//--------------------------------------------------
// Macro of DP RX1 Current DP Version
//--------------------------------------------------
#define GET_DP_AUX_RX1_CURRENT_VERSION()                (g_enumDpAuxRx1CurrentVersion)
#define SET_DP_AUX_RX1_CURRENT_VERSION(x)               (g_enumDpAuxRx1CurrentVersion = (x))

//--------------------------------------------------
// Macro of DP RX1 Current AUX Receive Mode
//--------------------------------------------------
#define GET_DP_AUX_RX1_RECEIVE_MODE()                   (g_enumDpAuxRx1ReceiveMode)
#define SET_DP_AUX_RX1_RECEIVE_MODE(x)                  (g_enumDpAuxRx1ReceiveMode = (x))

//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_AUX_RX1_FAKE_LINK_TRAINING()             ((bit) g_bDpAuxRx1FakeLT)
#define SET_DP_AUX_RX1_FAKE_LINK_TRAINING()             (g_bDpAuxRx1FakeLT = _TRUE)
#define CLR_DP_AUX_RX1_FAKE_LINK_TRAINING()             (g_bDpAuxRx1FakeLT = _FALSE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _AUX_RX1_DPCD_WILDCARD_MASK_NONE = 0x00,
    _AUX_RX1_DPCD_WILDCARD_MASK_BIT3_0 = 0x10,                                 // discard DPCD[3:0] : 0x0000x
    _AUX_RX1_DPCD_WILDCARD_MASK_BIT7_0 = 0x30,                                 // discard DPCD[7:0] : 0x000xx
    _AUX_RX1_DPCD_WILDCARD_MASK_BIT11_0 = 0x70,                                // discard DPCD[11:0] : 0x00xxx
    _AUX_RX1_DPCD_WILDCARD_MASK_BIT15_0 = 0xF0,                                // discard DPCD[15:12] : 0x0xxxx
    _AUX_RX1_DPCD_WILDCARD_MASK_END,
} EnumDpAuxRx1DpcdWildCardBitMask;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDpAuxRx1PSToggle;
extern volatile bit g_bDpAuxRx1CommandNoReply;
extern DWORD g_ulDpAuxRx1Backup_EXINT0;
extern DWORD g_ulDpAuxRx1Backup_WDINT;
extern volatile StructDpAuxRxDpcdUpdateProtect g_stDpAuxRx1DpcdUpdateProtect;
extern volatile StructDpAuxRxDpcdUpdateProtect g_stDpAuxRx1DpcdUpdateProtect_WDINT;
extern bit g_bDpAuxRx1SourceRDErrorCount;
extern volatile BYTE g_ucDpAuxRx1LTStatus;
extern bit g_bDpAuxRx1Info;
extern bit g_bDpAuxRx1Tp1Initial;

#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
extern BYTE g_pucDpAuxRx1MaxSwing[4];
#endif
extern BYTE g_ucDpAuxRx1PreferPreset;
extern BYTE g_ucDpAuxRx1LinkStatus01;
extern BYTE g_ucDpAuxRx1LinkStatus23;
extern BYTE g_ucDpAuxRx1LinkRequest01;
extern BYTE g_ucDpAuxRx1LinkRequest23;
extern bit g_bDpAuxRx1FakeLT;
extern volatile EnumDpLinkRate g_enumDpAuxRx1LinkRate;
extern volatile EnumDpLaneCount g_enumDpAuxRx1LaneCount;

#if(_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
extern volatile EnumDpLinkChannelCodingType g_enumDpAuxRx1CodingType;
#endif
extern BYTE g_ucDpAuxRx1TrainingPatternSet;

extern BYTE g_ucDpAuxRx1LTPatternSet;
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern volatile StructDpAuxRxReceiveBackup g_stDpAuxRx1ReceiveBackup;
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern volatile WORD g_usDpAuxRx1StreamIdAddrEnd;
#endif
#if(_DP_RX_FEC_SUPPORT == _ON)
extern volatile bit g_bDpAuxRx1FecStatusW1cProtect;
#endif
#endif

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
extern BYTE g_ucDpAuxRx1AccessBackup_EXINT0;
extern BYTE g_ucDpAuxRx1AccessBackup_WDINT;
#endif
extern BYTE g_pucDpAuxRx1LinkStatusBackup_INT[3];
extern bit g_bDpAuxRx1HpdLowResetFlag;
extern EnumDpVersionType g_enumDpAuxRx1CurrentVersion;
extern EnumDpAuxRxModeStatus g_enumDpAuxRx1ModeBackup_EXINT0;
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern volatile bit g_bDpAuxRx1IntProtect;
#endif

extern volatile StructDpRxAuxPowerInfo g_stDpAuxRx1PowerInfo;

extern volatile bit g_bDpAuxRx1MSTBackupLinkStatusFlg_INT;

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern volatile bit g_bDpAuxRx1HpdIrqAssertT2Event;
extern EnumDpAuxRxModeStatus g_enumDpAuxRx1AutoModeBackup_T2INT;
#endif

#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
extern BYTE g_ucDpAuxRx1Tp1PermitSwingLevel0;
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern bit g_bDpAuxRx1PRModeCrcEnableFlag;
#endif

extern EnumDpAuxReceiveMode g_enumDpAuxRx1ReceiveMode;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAuxRx1Initial(void);
extern void ScalerDpAuxRx1AuxIntInitial(void);
extern void ScalerDpAuxRx1ChangeDpcdVersion(void);
extern void ScalerDpAuxRx1TypeCPinAssert(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpAuxRx1SetSinkDeviceSpecificField(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx1SetBranchDeviceSpecificField(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx1ClrBranchDeviceSpecificField(void);

extern void ScalerDpAuxRx1SwitchDpcdAddrIrqSetting(void);
#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpAuxRx1SwitchMstProtocolIrq(void);
#endif

extern void ScalerDpAuxRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
extern EnumDpHotPlugTime ScalerDpAuxRx1BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpAuxRx1DisconnectReset(void);
extern void ScalerDpAuxRx1AfterHpdToggleProc(void);
extern void ScalerDpAuxRx1LinkStatusIRQ(void);
extern bit ScalerDpAuxRx1VersionChange(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx1PowerOn(void);
extern void ScalerDpAuxRx1HpdIrqAssert(void);
extern void ScalerDpAuxRx1FakeLTProtect(void);
extern void ScalerDpAuxRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpAuxRx1SetManualMode(void);
extern void ScalerDpAuxRx1SetAutoMode(void);
extern void ScalerDpAuxRx1SetDpcdAccessAddr(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx1SetDpcdAccessByteData(BYTE ucDpcdData);
extern void ScalerDpAuxRx1SetDpcdAccessBitData(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx1GetDpcdAccessData(void);
extern void ScalerDpAuxRx1DpcdAutoIncEnable(bit bEnable);
extern BYTE ScalerDpAuxRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdBitWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdBitWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorBitWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1DpcdWildCardSetting(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask);
extern void ScalerDpAuxRx1SetDpcdWildCardForceDeferEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx1GetDpcdWildCardForceDeferEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx1SetDpcdWildCardIntEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx1GetDpcdWildCardIntEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern bit ScalerDpAuxRx1DpcdWildCardIntCheck(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx1DpcdWildCardIntClr(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx1AccessSelect(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
extern void ScalerDpAuxRx1SetDpcdAttribute(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx1SetDpcdIntEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable);
extern bit ScalerDpAuxRx1GetDpcdIntEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern void ScalerDpAuxRx1SetDpcdForceDeferEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, bit bEnable);
extern bit ScalerDpAuxRx1GetDpcdForceDeferEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern void ScalerDpAuxRx1RequestReset(void);
extern void ScalerDpAuxRx1DpcdWrite1ClearInitial(void);
extern void ScalerDpAuxRx1DpcdReadClearInitial(void);
extern void ScalerDpAuxRx1DpcdWildCardInitial(void);
extern void ScalerDpAuxRx1DpcdRemapInitial(void);
extern void ScalerDpAuxRx1DpcdRemapSetting(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen);
extern bit ScalerDpAuxRx1GetDpcdRemapEnable(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx1DpcdRemapReset(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx1DpcdRemapIntCheck(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx1DpcdRemapIntClr(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx1InitialDpcdAttribute(void);
#else
extern void ScalerDpAuxRx1DpcdForceNack(void);
extern void ScalerDpAuxRx1DpcdRemap32BSetting(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx1DpcdRemap16BSetting(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx1DpcdRemap8BSetting(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern bit ScalerDpAuxRx1GetDpcdRemap32BEnable(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx1GetDpcdRemap16BEnable(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx1GetDpcdRemap8BEnable(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx1DpcdRemap32BReset(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx1DpcdRemap16BReset(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx1DpcdRemap8BReset(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx1DpcdRemap32BIntEnable(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx1DpcdRemap16BIntEnable(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx1DpcdRemap8BIntEnable(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern bit ScalerDpAuxRx1DpcdRemap32BIntCheck(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx1DpcdRemap16BIntCheck(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx1DpcdRemap8BIntCheck(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx1DpcdRemap32BIntClr(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx1DpcdRemap16BIntClr(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx1DpcdRemap8BIntClr(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
#endif
extern void ScalerDpAuxRx1SetDpcdLinkRate(EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpAuxRx1SetDpcdMaxLinkRateCapability(EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate);
extern EnumDpLinkRate ScalerDpAuxRx1GetDpcdMaxLinkRateCapability(void);
extern void ScalerDpAuxRx1HpdTogglePhyResetProc(bit bHpdHighLow);
extern void ScalerDpAuxRx1DpcdGroupReset(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, WORD usLen);
extern void ScalerDpAuxRx1DpcdLinkConfigReset(void);
extern void ScalerDpAuxRx1DpcdSourceOUIReset(void);
extern void ScalerDpAuxRx1DpcdProtocolConverterReset(void);

#if(_DP_AUX_RX1_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpAuxRx1DscDpcdSetting(void);
extern void ScalerDpAuxRx1DscDpcdExtendedCapSetting(void);
extern void ScalerDpAuxRx1DscIrqCtrl(bit bEnable);
extern void ScalerDpAuxRx1DscEnable_EXINT0(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpAuxRx1MstReset(void);
#endif
extern bit ScalerDpAuxRx1ChSourcePowerCheck(void);
extern void ScalerDpAuxRx1AuxChPowerStatusCheck(bit bCableStatus);

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
extern void ScalerDpAuxRx1MarginLinkCapabilitySwitchProc(BYTE ucDPPhyLinkRate);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpAuxRx1Hdcp2LoadCertRrxKey(void);
#endif

extern void ScalerDpAuxRx1TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern BYTE ScalerDpAuxRx1TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx1TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpAuxRx1TrainingPatternEnd_EXINT0(void);
extern BYTE ScalerDpAuxRx1PhyCtsTrainingPattern1_EXINT0(void);
extern BYTE ScalerDpAuxRx1PhyCtsTrainingPattern2_EXINT0(void);
extern void ScalerDpAuxRx1PhyCtsTrainingPatternEnd_EXINT0(void);
extern BYTE ScalerDpAuxRx1Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx1Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
#if(_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE ScalerDpAuxRx1Tp3Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpAuxRx1SetCodingType(EnumDpLinkChannelCodingType enumCodingType);
#endif
extern BYTE ScalerDpAuxRx1PhyCtsTp1Check_EXINT0(void);
extern BYTE ScalerDpAuxRx1PhyCtsTp2Check_EXINT0(void);
extern bit ScalerDpAuxRx1PreIntHandler_EXINT0(void);
extern void ScalerDpAuxRx1HighPriorityIntHandler_EXINT0(void);
extern void ScalerDpAuxRx1LowPriorityIntHandler_EXINT0(void);
extern void ScalerDpAuxRx1SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpAuxRx1SetManualMode_EXINT0(void);
extern void ScalerDpAuxRx1SetAutoMode_EXINT0(void);
extern void ScalerDpAuxRx1SetDpcdAccessAddr_EXINT0(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx1SetDpcdAccessByteData_EXINT0(BYTE ucDpcdData);
extern void ScalerDpAuxRx1SetDpcdAccessBitData_EXINT0(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx1GetDpcdAccessData_EXINT0(void);
extern void ScalerDpAuxRx1DpcdAutoIncEnable_EXINT0(bit bEnable);
extern BYTE ScalerDpAuxRx1GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx1GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdBitWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdBitWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorBitWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1DpcdGroupReset_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, WORD usLen);
extern void ScalerDpAuxRx1SetDpcdLinkStatusForceDefer_EXINT0(bit bEnable);
extern void ScalerDpAuxRx1WaitRcv_EXINT0(void);
extern void ScalerDpAuxRx1DpcdWildCardSetting_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask);
extern void ScalerDpAuxRx1SetDpcdWildCardForceDeferEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx1GetDpcdWildCardForceDeferEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx1SetDpcdWildCardIntEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx1GetDpcdWildCardIntEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern bit ScalerDpAuxRx1DpcdWildCardIntCheck_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx1DpcdWildCardIntClr_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern bit ScalerDpAuxRx1DpcdWildCardIntHandler_EXINT0(DWORD ulDpcdWildCardFlag);
extern void ScalerDpAuxRx1AccessSelect_EXINT0(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
extern void ScalerDpAuxRx1SetDpcdAttribute_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx1SetDpcdIntEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable);
extern bit ScalerDpAuxRx1GetDpcdIntEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern void ScalerDpAuxRx1SetDpcdForceDeferEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, bit bEnable);
extern bit ScalerDpAuxRx1GetDpcdForceDeferEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern void ScalerDpAuxRx1ClrDpcdIntFlag_EXINT0(void);
extern void ScalerDpAuxRx1RequestReset_EXINT0(void);
extern void ScalerDpAuxRx1RequestAnalyze_EXINT0(void);
extern void ScalerDpAuxRx1WriteIntRequestDataBackup_EXINT0(void);
extern bit ScalerDpAuxRx1ScanReqDpcdAddr_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern bit ScalerDpAuxRx1ScanLinkTrainingAddr_EXINT0(void);
extern bit ScalerDpAuxRx1ScanLinkStatusAddr_EXINT0(void);
extern void ScalerDpAuxRx1DpcdIrqProtect_T2INT(void);
extern bit ScalerDpAuxRx1DpcdIntCaseHandler_EXINT0(void);
extern bit ScalerDpAuxRx1I2cIntCaseHandler_EXINT0(void);
extern bit ScalerDpAuxRx1DpcdWrite1ClearHandler_EXINT0(void);
extern bit ScalerDpAuxRx1DpcdReadClearHandler_EXINT0(void);
extern void ScalerDpAuxRx1DpcdRemapSetting_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen);
extern bit ScalerDpAuxRx1GetDpcdRemapEnable_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx1DpcdRemapReset_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx1DpcdRemapIntCheck_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx1DpcdRemapIntClr_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx1DpcdRemapIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
#else
extern void ScalerDpAuxRx1DpcdRemap32BSetting_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx1DpcdRemap16BSetting_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx1DpcdRemap8BSetting_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern bit ScalerDpAuxRx1GetDpcdRemap32BEnable_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx1GetDpcdRemap16BEnable_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx1GetDpcdRemap8BEnable_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx1DpcdRemap32BReset_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx1DpcdRemap16BReset_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx1DpcdRemap8BReset_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx1DpcdRemap32BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx1DpcdRemap16BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx1DpcdRemap8BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern bit ScalerDpAuxRx1DpcdRemap32BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx1DpcdRemap16BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx1DpcdRemap8BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx1DpcdRemap32BIntClr_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx1DpcdRemap16BIntClr_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx1DpcdRemap8BIntClr_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern bit ScalerDpAuxRx1DpcdRemap32BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
extern bit ScalerDpAuxRx1DpcdRemap16BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
extern bit ScalerDpAuxRx1DpcdRemap8BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
#endif
extern void ScalerDpAuxRx1SetManualMode_T2INT(void);
extern void ScalerDpAuxRx1SetAutoMode_T2INT(void);
extern void ScalerDpAuxRx1EdidReadAddrOnlyProtect_EXINT0(void);
extern void ScalerDpAuxRx1DpcdSymbolErrorCountHandler_EXINT0(void);
#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRx1DpcdFecErrorCount_EXINT0(void);
extern void ScalerDpAuxRx1DpcdFecStatusW1cProtectHandler_EXINT0(void);
extern void ScalerDpAuxRx1SetFecStatusW1cProtectEnable_EXINT0(bit bEnable);
extern bit ScalerDpAuxRx1GetFecStatusW1cProtectEnable_EXINT0(void);
#endif
extern void ScalerDpAuxRx1DpcdLinkTrainingHandler_EXINT0(void);
extern void ScalerDpAuxRx1DpcdPowerStateHandler_EXINT0(void);
extern void ScalerDpAuxRx1DpcdHdcp14AksvHandler_EXINT0(void);
extern void ScalerDpAuxRx1DpcdTestCRCHandler_EXINT0(void);
#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpAuxRx1DpcdPrModeHandler_EXINT0(void);
#endif
#if((_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
extern void ScalerDpAuxRx1DpcdCableIDSyncHandler_EXINT0(void);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRx1FecDpcdSetting(void);
extern void ScalerDpAuxRx1SetFecStatusW1cProtectEnable(bit bEnable);
extern bit ScalerDpAuxRx1GetFecStatusW1cProtectEnable(void);
extern void ScalerDpAuxRx1FecHanlder_EXINT0(void);
#endif

extern void ScalerDpAuxRx1DpcdPortAccessBackup_WDINT(void);
extern void ScalerDpAuxRx1DpcdPortAccessBackupRestore_WDINT(void);
extern void ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx1SetDpcdAccessByteData_WDINT(BYTE ucDpcdData);
extern void ScalerDpAuxRx1SetDpcdAccessBitData_WDINT(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx1GetDpcdAccessData_WDINT(void);
extern void ScalerDpAuxRx1DpcdAutoIncEnable_WDINT(bit bEnable);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx1AccessSelect_WDINT(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
#endif
extern BYTE ScalerDpAuxRx1GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx1GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdBitValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdBitWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdBitWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx1SetDpcdMirrorBitValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorBitWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx1HpdIrqAssert_WDINT(void);
extern void ScalerDpAuxRx1DpcdLinkStatusReset_WDINT(EnumDpResetStatus enumDpResetStatus);

#if((_D1_DP_MST_PORT_SUPPORT == _ON) || (_DP_HDCP2_RX_SUPPORT == _ON))
extern void ScalerDpAuxRx1HdcpResetDpcdInfo_EXINT0(void);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpAuxRx1CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
extern void ScalerDpAuxRx1SetMPrimeReadDefer(bit bEnable);
extern void ScalerDpAuxRx1SetMPrimeReadDefer_EXINT0(bit bEnable);
#endif

extern void ScalerDpAuxRx1HpdIrqAssert_EXINT0(void);
extern void ScalerDpAuxRx1DpcdPortAccessBackup_EXINT0(void);
extern void ScalerDpAuxRx1DpcdPortAccessBackupRestore_EXINT0(void);

#if(_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpAuxRx1SetAuxReadInterval_EXINT0(void);
extern BYTE ScalerDpAuxRx1TrainingPattern3_EXINT0(EnumDpLinkTrainingType enumDpLtType);
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpAuxRx1Hdcp2TypeValueReset(void);
extern void ScalerDpAuxRx1Hdcp2TypeValueReset_EXINT0(void);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx1Hdcp2StreamIDTypeReset(void);
extern void ScalerDpAuxRx1Hdcp2StreamIDTypeReset_EXINT0(void);
#endif
extern BYTE ScalerDpAuxRx1Hdcp2GetMessageID_EXINT0(void);
extern void ScalerDpAuxRx1Hdcp2HandshakeIRQ(bit bEnable);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpAuxRx1PRModeDpcdSetting(void);
extern bit ScalerDpAuxRx1PRModeFlagStatus(void);
extern void ScalerDpAuxRx1DpcdPRModeErrorStateUpdate(EnumPRModeErrorStatus enumPRModeErrorStatus);
extern void ScalerDpAuxRx1DpcdPRModeStatusUpdate(EnumPRModeStatus enumPRModeStatus);
extern void ScalerDpAuxRx1DpcdPRModeErrorStateUpdate_EXINT0(EnumPRModeErrorStatus enumPRModeErrorStatus);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpAuxRx1AuxlessAlpmDpcdSetting(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
extern void ScalerDpAuxRx1HdrDpcdSetting(void);
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern void ScalerDpAuxRx1FreesyncDpcdSetting(void);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void ScalerDpAuxRx1AdaptiveSyncDpcdSetting(void);
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpAuxRx1MstProtocolDpcdReset(void);
#endif

#endif // End of #if(_DP_AUX_RX1_SUPPORT == _ON)
