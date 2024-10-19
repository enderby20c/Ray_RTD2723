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
// ID Code      : ScalerDpAuxRx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_AUX_RX2_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define RST_DP_AUX_RX2_FIFO_POINTER_T2INT()             {Scaler32SetBit_T2INT(PB1A006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX2_FIFO_POINTER_EXINT0()            {Scaler32SetBit_EXINT0(PB1A006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX2_INT_FIFO_POINTER_T2INT()         {Scaler32SetBit_T2INT(PB1A006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT22)}
#define RST_DP_AUX_RX2_INT_FIFO_POINTER_EXINT0()        {Scaler32SetBit_EXINT0(PB1A006_10_AUX_STATUS, ~(_BIT23 | _BIT22 | _BIT6 | _BIT1 | _BIT0), _BIT22)}
#else
#define RST_DP_AUX_RX2_FIFO_POINTER_T2INT()             {Scaler32SetBit_T2INT(PB1A002_10_AUX_STATUS, ~(_BIT23 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#define RST_DP_AUX_RX2_FIFO_POINTER_EXINT0()            {Scaler32SetBit_EXINT0(PB1A002_10_AUX_STATUS, ~(_BIT23 | _BIT6 | _BIT1 | _BIT0), _BIT23)}
#endif

#define GET_DP_AUX_RX2_LINK_TRAINING_STATUS()           (g_ucDpAuxRx2LTStatus)
#define SET_DP_AUX_RX2_LINK_TRAINING_STATUS(x)          (g_ucDpAuxRx2LTStatus = (x))

#define GET_DP_AUX_RX2_TOGGLE()                         (Scaler32GetBit(PB1A001_0C_AUX_IRQ_FLAG, _BIT12) == _BIT12)
#define CLR_DP_AUX_RX2_TOGGLE()                         {Scaler32SetDWord(PB1A001_0C_AUX_IRQ_FLAG, _BIT12);}

#define GET_DP_AUX_RX2_COMMAND_NO_REPLY()               (g_bDpAuxRx2CommandNoReply)
#define SET_DP_AUX_RX2_COMMAND_NO_REPLY()               (g_bDpAuxRx2CommandNoReply = _TRUE)
#define CLR_DP_AUX_RX2_COMMAND_NO_REPLY()               (g_bDpAuxRx2CommandNoReply = _FALSE)

#define GET_DP_AUX_RX2_MODE_T2INT()                     ((EnumDpAuxRxModeStatus)((Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define GET_DP_AUX_RX2_MODE_EXINT()                     ((EnumDpAuxRxModeStatus)((Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define GET_DP_AUX_RX2_MODE()                           ((EnumDpAuxRxModeStatus)((Scaler32GetBit(_REG_DP_AUX_RX2_MAC_CTRL, _BIT17) == _BIT17) ? _DP_RX_AUX_AUTO_MODE : _DP_RX_AUX_MANUAL_MODE))
#define SET_DP_AUX_RX2_MANUAL_MODE_T2INT()              {ScalerDpAuxRx2SetManualMode_T2INT();}
#define SET_DP_AUX_RX2_MANUAL_MODE_EXINT()              {ScalerDpAuxRx2SetManualMode_EXINT0();}
#define SET_DP_AUX_RX2_MANUAL_MODE()                    {ScalerDpAuxRx2SetManualMode();}
#define SET_DP_AUX_RX2_AUTO_MODE_T2INT()                {ScalerDpAuxRx2SetAutoMode_T2INT();}
#define SET_DP_AUX_RX2_AUTO_MODE_EXINT()                {ScalerDpAuxRx2SetAutoMode_EXINT0();}
#define SET_DP_AUX_RX2_AUTO_MODE()                      {ScalerDpAuxRx2SetAutoMode();}

#define GET_DP_AUX_RX2_VALID_VIDEO_CHECK()              (g_bDpAuxRx2Info)
#define SET_DP_AUX_RX2_VALID_VIDEO_CHECK()              (g_bDpAuxRx2Info = _TRUE)
#define CLR_DP_AUX_RX2_VALID_VIDEO_CHECK()              {\
                                                            ScalerDpAuxRxCancelValidSignalDetection(_D2_INPUT_PORT);\
                                                            (g_bDpAuxRx2Info = _FALSE);\
                                                        }
#define GET_DP_AUX_RX2_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx2DpcdUpdateProtect.bDpAuxRxDpcdUpdate)
#define SET_DP_AUX_RX2_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx2DpcdUpdateProtect.bDpAuxRxDpcdUpdate = _TRUE)
#define CLR_DP_AUX_RX2_DPCD_UPDATE_PROTECT()            (g_stDpAuxRx2DpcdUpdateProtect.bDpAuxRxDpcdUpdate = _FALSE)
#define GET_DP_AUX_RX2_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx2DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate)
#define SET_DP_AUX_RX2_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx2DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate = _TRUE)
#define CLR_DP_AUX_RX2_DPCD_UPDATE_PROTECT_WDINT()      (g_stDpAuxRx2DpcdUpdateProtect_WDINT.bDpAuxRxDpcdUpdate = _FALSE)
#define GET_DP_AUX_RX2_MODE_BACKUP_EXINT0()             (g_enumDpAuxRx2ModeBackup_EXINT0)
#define SET_DP_AUX_RX2_MODE_BACKUP_EXINT0(x)            (g_enumDpAuxRx2ModeBackup_EXINT0 = (x))
#define CLR_DP_AUX_RX2_MODE_BACKUP_EXINT0()             (g_enumDpAuxRx2ModeBackup_EXINT0 = _DP_RX_AUX_AUTO_MODE)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define GET_DP_AUX_RX2_INT_PROTECT()                    (g_bDpAuxRx2IntProtect)
#define SET_DP_AUX_RX2_INT_PROTECT()                    (g_bDpAuxRx2IntProtect = _TRUE)
#define CLR_DP_AUX_RX2_INT_PROTECT()                    (g_bDpAuxRx2IntProtect = _FALSE)
#endif

//--------------------------------------------------
// Macro of Dp Clear CRC Value
//--------------------------------------------------
#define CLR_DP_AUX_RX2_CRC_VALUE_EXINT0()               {ScalerDpAuxRx2DpcdGroupReset_EXINT0(0x00, 0x02, 0x40, 6);}

#define CLR_DP_AUX_RX2_DSC_CRC_VALUE_EXINT0()           {ScalerDpAuxRx2DpcdGroupReset_EXINT0(0x00, 0x02, 0x62, 6);}

//--------------------------------------------------
// Macro of Dp Error Count Read Record
//--------------------------------------------------
#define GET_DP_AUX_RX2_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx2SourceRDErrorCount)
#define SET_DP_AUX_RX2_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx2SourceRDErrorCount = _TRUE)
#define CLR_DP_AUX_RX2_SOURCE_READ_ERROR_COUNT()        (g_bDpAuxRx2SourceRDErrorCount = _FALSE)

//--------------------------------------------------
// Definitions of AUX Power Status
//--------------------------------------------------
#define GET_DP_AUX_RX2_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx2PowerInfo.b1DpCheckAuxChNoPowerDebounce)
#define SET_DP_AUX_RX2_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx2PowerInfo.b1DpCheckAuxChNoPowerDebounce = _TRUE)
#define CLR_DP_AUX_RX2_CHECK_CH_NO_POWER_DEBOUNCE()     (g_stDpAuxRx2PowerInfo.b1DpCheckAuxChNoPowerDebounce = _FALSE)

#define GET_DP_AUX_RX2_CHECK_CH_POWER_STATUS()          (g_stDpAuxRx2PowerInfo.b2DpCheckAuxChPowerStatus)
#define SET_DP_AUX_RX2_CHECK_CH_POWER_STATUS(x)         (g_stDpAuxRx2PowerInfo.b2DpCheckAuxChPowerStatus = (x))
#define CLR_DP_AUX_RX2_CHECK_CH_POWER_STATUS()          (g_stDpAuxRx2PowerInfo.b2DpCheckAuxChPowerStatus = _DP_RX_AUX_POWER_STATUS_NONE)

#define GET_DP_AUX_RX2_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx2PowerInfo.b1DpAuxChPowerOnWakeUp)
#define SET_DP_AUX_RX2_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx2PowerInfo.b1DpAuxChPowerOnWakeUp = _TRUE)
#define CLR_DP_AUX_RX2_CH_POWER_ON_WAKE_UP()            (g_stDpAuxRx2PowerInfo.b1DpAuxChPowerOnWakeUp = _FALSE)

#define GET_DP_AUX_RX2_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx2PowerInfo.b1DpSourceFirstPowerOn)
#define SET_DP_AUX_RX2_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx2PowerInfo.b1DpSourceFirstPowerOn = _TRUE)
#define CLR_DP_AUX_RX2_SOURCE_FIRST_POWER_ON()          (g_stDpAuxRx2PowerInfo.b1DpSourceFirstPowerOn = _FALSE)

#define GET_DP_AUX_RX2_SOURCE_WRITE_POWER_UP()          (g_stDpAuxRx2PowerInfo.enumDpSourceWritePowerUp)
#define SET_DP_AUX_RX2_SOURCE_WRITE_POWER_UP(x)         (g_stDpAuxRx2PowerInfo.enumDpSourceWritePowerUp = (x))
#define CLR_DP_AUX_RX2_SOURCE_WRITE_POWER_UP()          (g_stDpAuxRx2PowerInfo.enumDpSourceWritePowerUp = _DP_SOURCE_WRITE_POWER_UP_NONE)

#if(_DP_TX_SUPPORT == _ON)
#define CLR_DP_AUX_RX2_HDCP_KSV_FIFO_INT_FLAG()         {\
                                                            Scaler32SetDWord(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT10);\
                                                        }

#define CLR_DP_AUX_RX2_HDCP_KSV_FIFO_INT_FLAG_EXINT()   {\
                                                            Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT10);\
                                                        }

#define GET_DP_AUX_RX2_HDCP_REPEATER_SUPPORT()          ((ScalerDpAuxRx2GetDpcdInfo(0x06, 0x80, 0x28) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
#endif

//--------------------------------------------------
// Macro of AUX Reset Flag
//--------------------------------------------------
#define GET_DP_RX_AUX_RX2_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx2HpdLowResetFlag)
#define SET_DP_RX_AUX_RX2_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx2HpdLowResetFlag = _TRUE)
#define CLR_DP_RX_AUX_RX2_HPD_LOW_RESET_FLAG()\
                                                        (g_bDpAuxRx2HpdLowResetFlag = _FALSE)

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
//--------------------------------------------------
// Macro of DP IRQ Assert Timer2 Event
//--------------------------------------------------
#define GET_DP_AUX_RX2_HPD_IRQ_ASSERT_T2_EVENT()        (g_bDpAuxRx2HpdIrqAssertT2Event)
#define SET_DP_AUX_RX2_HPD_IRQ_ASSERT_T2_EVENT()        {\
                                                            g_bDpAuxRx2HpdIrqAssertT2Event = _TRUE;\
                                                            DP_RX_HPD_IRQ_ASSERT_T2_DELAY_INITIAL();\
                                                        }
#define CLR_DP_AUX_RX2_HPD_IRQ_ASSERT_T2_EVENT()        (g_bDpAuxRx2HpdIrqAssertT2Event = _FALSE)
#endif

//--------------------------------------------------
// Macro of DP PR DPCD Info
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
#define GET_DP_AUX_RX2_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx2PRModeCrcEnableFlag)
#define SET_DP_AUX_RX2_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx2PRModeCrcEnableFlag = _TRUE)
#define CLR_DP_AUX_RX2_PR_MODE_DPCD_CRC_ENABLE()        (g_bDpAuxRx2PRModeCrcEnableFlag = _FALSE)
#endif

#define GET_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx2MSTBackupLinkStatusFlg_INT)
#define SET_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx2MSTBackupLinkStatusFlg_INT = _TRUE)
#define CLR_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG()      (g_bDpAuxRx2MSTBackupLinkStatusFlg_INT = _FALSE)

//--------------------------------------------------
// Macro of DP RX2 Current DP Version
//--------------------------------------------------
#define GET_DP_AUX_RX2_CURRENT_VERSION()                (g_enumDpAuxRx2CurrentVersion)
#define SET_DP_AUX_RX2_CURRENT_VERSION(x)               (g_enumDpAuxRx2CurrentVersion = (x))

//--------------------------------------------------
// Macro of DP RX2 Current AUX Receive Mode
//--------------------------------------------------
#define GET_DP_AUX_RX2_RECEIVE_MODE()                   (g_enumDpAuxRx2ReceiveMode)
#define SET_DP_AUX_RX2_RECEIVE_MODE(x)                  (g_enumDpAuxRx2ReceiveMode = (x))

//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_AUX_RX2_FAKE_LINK_TRAINING()             ((bit) g_bDpAuxRx2FakeLT)
#define SET_DP_AUX_RX2_FAKE_LINK_TRAINING()             (g_bDpAuxRx2FakeLT = _TRUE)
#define CLR_DP_AUX_RX2_FAKE_LINK_TRAINING()             (g_bDpAuxRx2FakeLT = _FALSE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _AUX_RX2_DPCD_WILDCARD_MASK_NONE = 0x00,
    _AUX_RX2_DPCD_WILDCARD_MASK_BIT3_0 = 0x10,                                 // discard DPCD[3:0] : 0x0000x
    _AUX_RX2_DPCD_WILDCARD_MASK_BIT7_0 = 0x30,                                 // discard DPCD[7:0] : 0x000xx
    _AUX_RX2_DPCD_WILDCARD_MASK_BIT11_0 = 0x70,                                // discard DPCD[11:0] : 0x00xxx
    _AUX_RX2_DPCD_WILDCARD_MASK_BIT15_0 = 0xF0,                                // discard DPCD[15:12] : 0x0xxxx
    _AUX_RX2_DPCD_WILDCARD_MASK_END,
} EnumDpAuxRx2DpcdWildCardBitMask;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDpAuxRx2PSToggle;
extern volatile bit g_bDpAuxRx2CommandNoReply;
extern DWORD g_ulDpAuxRx2Backup_EXINT0;
extern DWORD g_ulDpAuxRx2Backup_WDINT;
extern volatile StructDpAuxRxDpcdUpdateProtect g_stDpAuxRx2DpcdUpdateProtect;
extern volatile StructDpAuxRxDpcdUpdateProtect g_stDpAuxRx2DpcdUpdateProtect_WDINT;
extern bit g_bDpAuxRx2SourceRDErrorCount;
extern volatile BYTE g_ucDpAuxRx2LTStatus;
extern bit g_bDpAuxRx2Info;
extern bit g_bDpAuxRx2Tp1Initial;

#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
extern BYTE g_pucDpAuxRx2MaxSwing[4];
#endif
extern BYTE g_ucDpAuxRx2PreferPreset;
extern BYTE g_ucDpAuxRx2LinkStatus01;
extern BYTE g_ucDpAuxRx2LinkStatus23;
extern BYTE g_ucDpAuxRx2LinkRequest01;
extern BYTE g_ucDpAuxRx2LinkRequest23;
extern bit g_bDpAuxRx2FakeLT;
extern volatile EnumDpLinkRate g_enumDpAuxRx2LinkRate;
extern volatile EnumDpLaneCount g_enumDpAuxRx2LaneCount;

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
extern volatile EnumDpLinkChannelCodingType g_enumDpAuxRx2CodingType;
#endif
extern BYTE g_ucDpAuxRx2TrainingPatternSet;

extern BYTE g_ucDpAuxRx2LTPatternSet;
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern volatile StructDpAuxRxReceiveBackup g_stDpAuxRx2ReceiveBackup;
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern volatile WORD g_usDpAuxRx2StreamIdAddrEnd;
#endif
#if(_DP_RX_FEC_SUPPORT == _ON)
extern volatile bit g_bDpAuxRx2FecStatusW1cProtect;
#endif
#endif

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
extern BYTE g_ucDpAuxRx2AccessBackup_EXINT0;
extern BYTE g_ucDpAuxRx2AccessBackup_WDINT;
#endif
extern BYTE g_pucDpAuxRx2LinkStatusBackup_INT[3];
extern bit g_bDpAuxRx2HpdLowResetFlag;
extern EnumDpVersionType g_enumDpAuxRx2CurrentVersion;
extern EnumDpAuxRxModeStatus g_enumDpAuxRx2ModeBackup_EXINT0;
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern volatile bit g_bDpAuxRx2IntProtect;
#endif

extern volatile StructDpRxAuxPowerInfo g_stDpAuxRx2PowerInfo;

extern volatile bit g_bDpAuxRx2MSTBackupLinkStatusFlg_INT;

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern volatile bit g_bDpAuxRx2HpdIrqAssertT2Event;
extern EnumDpAuxRxModeStatus g_enumDpAuxRx2AutoModeBackup_T2INT;
#endif

#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
extern BYTE g_ucDpAuxRx2Tp1PermitSwingLevel0;
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern bit g_bDpAuxRx2PRModeCrcEnableFlag;
#endif

extern EnumDpAuxReceiveMode g_enumDpAuxRx2ReceiveMode;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAuxRx2Initial(void);
extern void ScalerDpAuxRx2AuxIntInitial(void);
extern void ScalerDpAuxRx2ChangeDpcdVersion(void);
extern void ScalerDpAuxRx2TypeCPinAssert(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpAuxRx2SetSinkDeviceSpecificField(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx2SetBranchDeviceSpecificField(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx2ClrBranchDeviceSpecificField(void);

extern void ScalerDpAuxRx2SwitchDpcdAddrIrqSetting(void);
#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpAuxRx2SwitchMstProtocolIrq(void);
#endif

extern void ScalerDpAuxRx2DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
extern EnumDpHotPlugTime ScalerDpAuxRx2BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpAuxRx2DisconnectReset(void);
extern void ScalerDpAuxRx2AfterHpdToggleProc(void);
extern void ScalerDpAuxRx2LinkStatusIRQ(void);
extern bit ScalerDpAuxRx2VersionChange(EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRx2PowerOn(void);
extern void ScalerDpAuxRx2HpdIrqAssert(void);
extern void ScalerDpAuxRx2FakeLTProtect(void);
extern void ScalerDpAuxRx2SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpAuxRx2SetManualMode(void);
extern void ScalerDpAuxRx2SetAutoMode(void);
extern void ScalerDpAuxRx2SetDpcdAccessAddr(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx2SetDpcdAccessByteData(BYTE ucDpcdData);
extern void ScalerDpAuxRx2SetDpcdAccessBitData(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx2GetDpcdAccessData(void);
extern void ScalerDpAuxRx2DpcdAutoIncEnable(bit bEnable);
extern BYTE ScalerDpAuxRx2GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx2GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdBitWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdBitWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorBitWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2DpcdWildCardSetting(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask);
extern void ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx2GetDpcdWildCardForceDeferEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx2SetDpcdWildCardIntEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx2GetDpcdWildCardIntEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern bit ScalerDpAuxRx2DpcdWildCardIntCheck(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx2DpcdWildCardIntClr(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx2AccessSelect(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
extern void ScalerDpAuxRx2SetDpcdAttribute(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx2SetDpcdIntEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable);
extern bit ScalerDpAuxRx2GetDpcdIntEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern void ScalerDpAuxRx2SetDpcdForceDeferEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, bit bEnable);
extern bit ScalerDpAuxRx2GetDpcdForceDeferEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern void ScalerDpAuxRx2RequestReset(void);
extern void ScalerDpAuxRx2DpcdWrite1ClearInitial(void);
extern void ScalerDpAuxRx2DpcdReadClearInitial(void);
extern void ScalerDpAuxRx2DpcdWildCardInitial(void);
extern void ScalerDpAuxRx2DpcdRemapInitial(void);
extern void ScalerDpAuxRx2DpcdRemapSetting(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen);
extern bit ScalerDpAuxRx2GetDpcdRemapEnable(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx2DpcdRemapReset(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx2DpcdRemapIntCheck(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx2DpcdRemapIntClr(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx2InitialDpcdAttribute(void);
#else
extern void ScalerDpAuxRx2DpcdForceNack(void);
extern void ScalerDpAuxRx2DpcdRemap32BSetting(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx2DpcdRemap16BSetting(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx2DpcdRemap8BSetting(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern bit ScalerDpAuxRx2GetDpcdRemap32BEnable(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx2GetDpcdRemap16BEnable(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx2GetDpcdRemap8BEnable(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx2DpcdRemap32BReset(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx2DpcdRemap16BReset(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx2DpcdRemap8BReset(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx2DpcdRemap32BIntEnable(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx2DpcdRemap16BIntEnable(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx2DpcdRemap8BIntEnable(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern bit ScalerDpAuxRx2DpcdRemap32BIntCheck(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx2DpcdRemap16BIntCheck(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx2DpcdRemap8BIntCheck(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx2DpcdRemap32BIntClr(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx2DpcdRemap16BIntClr(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx2DpcdRemap8BIntClr(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
#endif
extern void ScalerDpAuxRx2SetDpcdLinkRate(EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpAuxRx2SetDpcdMaxLinkRateCapability(EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate);
extern EnumDpLinkRate ScalerDpAuxRx2GetDpcdMaxLinkRateCapability(void);
extern void ScalerDpAuxRx2HpdTogglePhyResetProc(bit bHpdHighLow);
extern void ScalerDpAuxRx2DpcdGroupReset(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, WORD usLen);
extern void ScalerDpAuxRx2DpcdLinkConfigReset(void);
extern void ScalerDpAuxRx2DpcdSourceOUIReset(void);
extern void ScalerDpAuxRx2DpcdProtocolConverterReset(void);

#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpAuxRx2DscDpcdSetting(void);
extern void ScalerDpAuxRx2DscDpcdExtendedCapSetting(void);
extern void ScalerDpAuxRx2DscIrqCtrl(bit bEnable);
extern void ScalerDpAuxRx2DscEnable_EXINT0(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpAuxRx2MstReset(void);
#endif
extern bit ScalerDpAuxRx2ChSourcePowerCheck(void);
extern void ScalerDpAuxRx2AuxChPowerStatusCheck(bit bCableStatus);

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
extern void ScalerDpAuxRx2MarginLinkCapabilitySwitchProc(BYTE ucDPPhyLinkRate);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpAuxRx2Hdcp2LoadCertRrxKey(void);
#endif

extern void ScalerDpAuxRx2TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern BYTE ScalerDpAuxRx2TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx2TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpAuxRx2TrainingPatternEnd_EXINT0(void);
extern BYTE ScalerDpAuxRx2PhyCtsTrainingPattern1_EXINT0(void);
extern BYTE ScalerDpAuxRx2PhyCtsTrainingPattern2_EXINT0(void);
extern void ScalerDpAuxRx2PhyCtsTrainingPatternEnd_EXINT0(void);
extern BYTE ScalerDpAuxRx2Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx2Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE ScalerDpAuxRx2Tp3Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpAuxRx2SetCodingType(EnumDpLinkChannelCodingType enumCodingType);
#endif
extern BYTE ScalerDpAuxRx2PhyCtsTp1Check_EXINT0(void);
extern BYTE ScalerDpAuxRx2PhyCtsTp2Check_EXINT0(void);
extern bit ScalerDpAuxRx2PreIntHandler_EXINT0(void);
extern void ScalerDpAuxRx2HighPriorityIntHandler_EXINT0(void);
extern void ScalerDpAuxRx2LowPriorityIntHandler_EXINT0(void);
extern void ScalerDpAuxRx2SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpAuxRx2SetManualMode_EXINT0(void);
extern void ScalerDpAuxRx2SetAutoMode_EXINT0(void);
extern void ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx2SetDpcdAccessByteData_EXINT0(BYTE ucDpcdData);
extern void ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx2GetDpcdAccessData_EXINT0(void);
extern void ScalerDpAuxRx2DpcdAutoIncEnable_EXINT0(bit bEnable);
extern BYTE ScalerDpAuxRx2GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdBitWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorBitWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2DpcdGroupReset_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, WORD usLen);
extern void ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(bit bEnable);
extern void ScalerDpAuxRx2WaitRcv_EXINT0(void);
extern void ScalerDpAuxRx2DpcdWildCardSetting_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask);
extern void ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx2GetDpcdWildCardForceDeferEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx2SetDpcdWildCardIntEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRx2GetDpcdWildCardIntEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern bit ScalerDpAuxRx2DpcdWildCardIntCheck_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern bit ScalerDpAuxRx2DpcdWildCardIntHandler_EXINT0(DWORD ulDpcdWildCardFlag);
extern void ScalerDpAuxRx2AccessSelect_EXINT0(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
extern void ScalerDpAuxRx2SetDpcdAttribute_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx2SetDpcdIntEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable);
extern bit ScalerDpAuxRx2GetDpcdIntEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern void ScalerDpAuxRx2SetDpcdForceDeferEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, bit bEnable);
extern bit ScalerDpAuxRx2GetDpcdForceDeferEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern void ScalerDpAuxRx2ClrDpcdIntFlag_EXINT0(void);
extern void ScalerDpAuxRx2RequestReset_EXINT0(void);
extern void ScalerDpAuxRx2RequestAnalyze_EXINT0(void);
extern void ScalerDpAuxRx2WriteIntRequestDataBackup_EXINT0(void);
extern bit ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
extern bit ScalerDpAuxRx2ScanLinkTrainingAddr_EXINT0(void);
extern bit ScalerDpAuxRx2ScanLinkStatusAddr_EXINT0(void);
extern void ScalerDpAuxRx2DpcdIrqProtect_T2INT(void);
extern bit ScalerDpAuxRx2DpcdIntCaseHandler_EXINT0(void);
extern bit ScalerDpAuxRx2I2cIntCaseHandler_EXINT0(void);
extern bit ScalerDpAuxRx2DpcdWrite1ClearHandler_EXINT0(void);
extern bit ScalerDpAuxRx2DpcdReadClearHandler_EXINT0(void);
extern void ScalerDpAuxRx2DpcdRemapSetting_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen);
extern bit ScalerDpAuxRx2GetDpcdRemapEnable_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx2DpcdRemapReset_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx2DpcdRemapIntCheck_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern void ScalerDpAuxRx2DpcdRemapIntClr_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId);
extern bit ScalerDpAuxRx2DpcdRemapIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
#else
extern void ScalerDpAuxRx2DpcdRemap32BSetting_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx2DpcdRemap16BSetting_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern void ScalerDpAuxRx2DpcdRemap8BSetting_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr);
extern bit ScalerDpAuxRx2GetDpcdRemap32BEnable_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx2GetDpcdRemap16BEnable_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx2GetDpcdRemap8BEnable_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx2DpcdRemap32BReset_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx2DpcdRemap16BReset_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx2DpcdRemap8BReset_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx2DpcdRemap32BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx2DpcdRemap16BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern void ScalerDpAuxRx2DpcdRemap8BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable);
extern bit ScalerDpAuxRx2DpcdRemap32BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern bit ScalerDpAuxRx2DpcdRemap16BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern bit ScalerDpAuxRx2DpcdRemap8BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern void ScalerDpAuxRx2DpcdRemap32BIntClr_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId);
extern void ScalerDpAuxRx2DpcdRemap16BIntClr_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId);
extern void ScalerDpAuxRx2DpcdRemap8BIntClr_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId);
extern bit ScalerDpAuxRx2DpcdRemap32BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
extern bit ScalerDpAuxRx2DpcdRemap16BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
extern bit ScalerDpAuxRx2DpcdRemap8BIntHandler_EXINT0(DWORD ulDpcdRemapFlag);
#endif
extern void ScalerDpAuxRx2SetManualMode_T2INT(void);
extern void ScalerDpAuxRx2SetAutoMode_T2INT(void);
extern void ScalerDpAuxRx2EdidReadAddrOnlyProtect_EXINT0(void);
extern void ScalerDpAuxRx2DpcdSymbolErrorCountHandler_EXINT0(void);
#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRx2DpcdFecErrorCount_EXINT0(void);
extern void ScalerDpAuxRx2DpcdFecStatusW1cProtectHandler_EXINT0(void);
extern void ScalerDpAuxRx2SetFecStatusW1cProtectEnable_EXINT0(bit bEnable);
extern bit ScalerDpAuxRx2GetFecStatusW1cProtectEnable_EXINT0(void);
#endif
extern void ScalerDpAuxRx2DpcdLinkTrainingHandler_EXINT0(void);
extern void ScalerDpAuxRx2DpcdPowerStateHandler_EXINT0(void);
extern void ScalerDpAuxRx2DpcdHdcp14AksvHandler_EXINT0(void);
extern void ScalerDpAuxRx2DpcdTestCRCHandler_EXINT0(void);
#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpAuxRx2DpcdPrModeHandler_EXINT0(void);
#endif
#if((_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
extern void ScalerDpAuxRx2DpcdCableIDSyncHandler_EXINT0(void);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRx2FecDpcdSetting(void);
extern void ScalerDpAuxRx2SetFecStatusW1cProtectEnable(bit bEnable);
extern bit ScalerDpAuxRx2GetFecStatusW1cProtectEnable(void);
extern void ScalerDpAuxRx2FecHanlder_EXINT0(void);
#endif

extern void ScalerDpAuxRx2DpcdPortAccessBackup_WDINT(void);
extern void ScalerDpAuxRx2DpcdPortAccessBackupRestore_WDINT(void);
extern void ScalerDpAuxRx2SetDpcdAccessAddr_WDINT(DWORD ulDpcdAddr);
extern void ScalerDpAuxRx2SetDpcdAccessByteData_WDINT(BYTE ucDpcdData);
extern void ScalerDpAuxRx2SetDpcdAccessBitData_WDINT(WORD usNotDpcdBit, WORD usDpcdBit);
extern WORD ScalerDpAuxRx2GetDpcdAccessData_WDINT(void);
extern void ScalerDpAuxRx2DpcdAutoIncEnable_WDINT(bit bEnable);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx2AccessSelect_WDINT(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess);
#endif
extern BYTE ScalerDpAuxRx2GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRx2GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdBitValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdBitWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRx2SetDpcdMirrorBitValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorBitWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRx2HpdIrqAssert_WDINT(void);
extern void ScalerDpAuxRx2DpcdLinkStatusReset_WDINT(EnumDpResetStatus enumDpResetStatus);

#if((_D2_DP_MST_PORT_SUPPORT == _ON) || (_DP_HDCP2_RX_SUPPORT == _ON))
extern void ScalerDpAuxRx2HdcpResetDpcdInfo_EXINT0(void);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpAuxRx2CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
extern void ScalerDpAuxRx2SetMPrimeReadDefer(bit bEnable);
extern void ScalerDpAuxRx2SetMPrimeReadDefer_EXINT0(bit bEnable);
#endif

extern void ScalerDpAuxRx2HpdIrqAssert_EXINT0(void);
extern void ScalerDpAuxRx2DpcdPortAccessBackup_EXINT0(void);
extern void ScalerDpAuxRx2DpcdPortAccessBackupRestore_EXINT0(void);

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpAuxRx2SetAuxReadInterval_EXINT0(void);
extern BYTE ScalerDpAuxRx2TrainingPattern3_EXINT0(EnumDpLinkTrainingType enumDpLtType);
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpAuxRx2Hdcp2TypeValueReset(void);
extern void ScalerDpAuxRx2Hdcp2TypeValueReset_EXINT0(void);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx2Hdcp2StreamIDTypeReset(void);
extern void ScalerDpAuxRx2Hdcp2StreamIDTypeReset_EXINT0(void);
#endif
extern BYTE ScalerDpAuxRx2Hdcp2GetMessageID_EXINT0(void);
extern void ScalerDpAuxRx2Hdcp2HandshakeIRQ(bit bEnable);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpAuxRx2PRModeDpcdSetting(void);
extern bit ScalerDpAuxRx2PRModeFlagStatus(void);
extern void ScalerDpAuxRx2DpcdPRModeErrorStateUpdate(EnumPRModeErrorStatus enumPRModeErrorStatus);
extern void ScalerDpAuxRx2DpcdPRModeStatusUpdate(EnumPRModeStatus enumPRModeStatus);
extern void ScalerDpAuxRx2DpcdPRModeErrorStateUpdate_EXINT0(EnumPRModeErrorStatus enumPRModeErrorStatus);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpAuxRx2AuxlessAlpmDpcdSetting(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
extern void ScalerDpAuxRx2HdrDpcdSetting(void);
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern void ScalerDpAuxRx2FreesyncDpcdSetting(void);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void ScalerDpAuxRx2AdaptiveSyncDpcdSetting(void);
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpAuxRx2MstProtocolDpcdReset(void);
#endif

#endif // End of #if(_DP_AUX_RX2_SUPPORT == _ON)
