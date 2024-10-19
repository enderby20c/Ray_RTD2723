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
// ID Code      : ScalerDpMacDphyRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX0_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of MAC DPHY Reset
//----------------------------------------------------------------------------
#define SET_DP_MAC_DPHY_RX0_DIGITAL_PHY_RESET_8B10B()               {\
                                                                        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);\
                                                                        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);\
                                                                    }

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_DPHY_RX0_DIGITAL_PHY_RESET_128B132B()            {\
                                                                        ScalerSetBit(PC_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);\
                                                                        ScalerSetBit(PC_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);\
                                                                    }
#endif

//----------------------------------------------------------------------------
// Macro of HDCP Information
//----------------------------------------------------------------------------
#define GET_DP_MAC_DPHY_RX0_HDCP_MODE_8B10B()                       ((ScalerGetBit(PB_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

#define GET_DP_MAC_DPHY_RX0_HDCP_MODE_128B132B()                    (_HDCP_22)

#define GET_DP_MAC_DPHY_RX0_HDCP_MODE_8B10B_EXINT()                 ((ScalerGetBit_EXINT(PB_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

#define GET_DP_MAC_DPHY_RX0_HDCP_MODE_128B132B_EXINT()              (_HDCP_22)

#define SET_DP_MAC_DPHY_RX0_LINK_INTEGRITY_128B132B()               {\
                                                                        ScalerSetBit(PC_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);\
                                                                    }

#define SET_DP_MAC_DPHY_RX0_LINK_INTEGRITY_8B10B()                  {\
                                                                        ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);\
                                                                    }

//----------------------------------------------------------------------------
// Macro of Dp Hdcp 1.4 Information for M0_Prime
//----------------------------------------------------------------------------
#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX0_HDCP14_M0_0()                           (ScalerGetByte(PB_2F_M0_BYTE_0) ^ 0x9D)
#define GET_DP_MAC_DPHY_RX0_HDCP14_M0_1()                           (~(ScalerGetByte(PB_2E_M0_BYTE_1) ^ ScalerGetByte(PB_2F_M0_BYTE_0)))
#define GET_DP_MAC_DPHY_RX0_HDCP14_M0_2()                           (ScalerGetByte(PB_2D_M0_BYTE_2) ^ ScalerGetByte(PB_2E_M0_BYTE_1))
#define GET_DP_MAC_DPHY_RX0_HDCP14_M0_3()                           (ScalerGetByte(PB_2C_M0_BYTE_3) ^ ScalerGetByte(PB_2D_M0_BYTE_2))
#define GET_DP_MAC_DPHY_RX0_HDCP14_M0_4()                           (ScalerGetByte(PB_2B_M0_BYTE_4) ^ ScalerGetByte(PB_2C_M0_BYTE_3))
#define GET_DP_MAC_DPHY_RX0_HDCP14_M0_5()                           (~(ScalerGetByte(PB_2A_M0_BYTE_5) ^ ScalerGetByte(PB_2B_M0_BYTE_4)))
#define GET_DP_MAC_DPHY_RX0_HDCP14_M0_6()                           (~(ScalerGetByte(PB_29_M0_BYTE_6) ^ ScalerGetByte(PB_2A_M0_BYTE_5)))
#define GET_DP_MAC_DPHY_RX0_HDCP14_M0_7()                           (~(ScalerGetByte(PB_28_M0_BYTE_7) ^ ScalerGetByte(PB_29_M0_BYTE_6)))
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of MST Stream Related Macro
//--------------------------------------------------
#define GET_DP_MAC_DPHY_RX0_STX_START_ADDRESS_8B10B(x)              (PB5_02_STHD_CTRL_2 + (2 * (x)))
#define GET_DP_MAC_DPHY_RX0_STX_END_ADDRESS_8B10B(x)                (PB5_02_STHD_CTRL_2 + (2 * (x)) + 1)

#define SET_DP_MAC_DPHY_RX0_LOAD_NEW_STREAM_PAYLOAD()               (ScalerDpMacDphyRx0LoadNewStreamPayload())
#define SET_DP_MAC_DPHY_RX0_LOAD_NEW_STREAM_PAYLOAD_EXINT()         (ScalerDpMacDphyRx0LoadNewStreamPayload_EXINT0())
#define SET_DP_MAC_DPHY_RX0_LOAD_NEW_STREAM_PAYLOAD_WDINT()         (ScalerDpMacDphyRx0LoadNewStreamPayload_WDINT())

#define GET_DP_MAC_DPHY_RX0_TIMESLOT_HDCP_ENC_VALUE_8B10B(x)        (((x) == 0) ? _FALSE : (ScalerGetBit((PB_6B_HDCP_ENC_CTRL7 - ((x) / 8)), (_BIT0 << ((x) % 8)))))
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX0_TIMESLOT_HDCP_ENC_VALUE_128B132B(x)     (ScalerGetBit((PC_17_HDCP_ENC_CTRL7 - ((x) / 8)), (_BIT0 << ((x) % 8))))
#endif
#endif // #if(_DP_MST_SUPPORT == _ON)

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX0_STX_START_ADDRESS_128B132B(x)           (P9D_02_STHD_CTRL_2 + (2 * (x)))
#define GET_DP_MAC_DPHY_RX0_STX_END_ADDRESS_128B132B(x)             (P9D_02_STHD_CTRL_2 + (2 * (x)) + 1)
#endif


#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Dp FEC
//--------------------------------------------------
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX0_FEC_DECODE_STATUS()                     ((ScalerGetBit_EXINT(PB_D0_FEC_DECODE_CTL, _BIT7) == _BIT7) || (ScalerGetBit_EXINT(PC_80_FEC_DECODE_CTL, _BIT7) == _BIT7))
#else
#define GET_DP_MAC_DPHY_RX0_FEC_DECODE_STATUS()                     (ScalerGetBit_EXINT(PB_D0_FEC_DECODE_CTL, _BIT7) == _BIT7)
#endif
#endif

#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
#define GET_DP_MAC_DPHY_RX0_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx0SignaldetectINTHappened)
#define SET_DP_MAC_DPHY_RX0_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx0SignaldetectINTHappened = _TRUE)
#define CLR_DP_MAC_DPHY_RX0_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx0SignaldetectINTHappened = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Auxless ALPM Occurred
//--------------------------------------------------
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX0_AUXLESS_ALPM_OCCURRED()                 (ScalerGetBit(PB_C3_ALPM_UFP_18, _BIT7) == _BIT7)
#define CLR_DP_MAC_DPHY_RX0_AUXLESS_ALPM_OCCURRED()                 {\
                                                                        ScalerSetBit(PB_C3_ALPM_UFP_18, ~_BIT6, _BIT6);\
                                                                        ScalerSetBit(PB_C3_ALPM_UFP_18, ~_BIT6, 0x00);\
                                                                    }
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
extern bit g_bDpMacDphyRx0SignaldetectINTHappened;
#endif

extern BYTE g_ucDpMacDphyRx0Temp;
extern BYTE g_ucDpMacDphyRx0EQCRC;

#if(_DP_MST_SUPPORT == _ON)
extern StructDPMacRxMiscInfo g_stDpMacDphyRx0MiscInfo;
#endif

extern StructDpMacDphyRxHdcpCipherBackupInfo g_stDpMacDphyRx0HdcpCipherBackupInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacDphyRx0PowerProc(EnumPowerAction enumPowerAction);
#endif

extern bit ScalerDpMacDphyRx0NormalPreDetect(void);
extern bit ScalerDpMacDphyRx0PSPreDetect(void);

extern void ScalerDpMacDphyRx0DigitalPhyInitial(void);
extern bit ScalerDpMacDphyRx0PhyCtsTp1Check(void);
extern bit ScalerDpMacDphyRx0PhyCtsTp2Check(void);
extern void ScalerDpMacDphyRx0ScrambleSetting(void);
extern bit ScalerDpMacDphyRx0DecodeErrorCountReset(EnumDpMacDecodeMethod enumDpMacDecodeMethod);
extern bit ScalerDpMacDphyRx0DecodeErrorCountLaneMeasure(WORD usErrorCriteria, BYTE ucDpMacRx0LaneNumber);
extern WORD ScalerDpMacDphyRx0GetDecodeErrorCount(BYTE ucDpMacRx0LaneNumber);
extern void ScalerDpMacDphyRx0LaneSwapSelect(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern BYTE ScalerDpMacDphyRx0GetLaneMuxMapping(EnumDpLane enumDpLane);
extern void ScalerDpMacDphyRx0LaneCountSet(BYTE ucDpLaneCount);
extern void ScalerDpMacDphyRx0SetCommaDetect(bit bEn);
extern void ScalerDpMacDphyRx0ClkSelect(EnumDpMacClkSelect enumClkSelect);
extern void ScalerDpMacDphyRx0ChannelFifoReset(void);

extern bit ScalerDpMacDphyRx0AlignCheck(void);
extern bit ScalerDpMacDphyRx0DecodeCheck(void);

extern void ScalerDpMacDphyRx0Hdcp14ResetProc(void);
extern void ScalerDpMacDphyRx0HDCPUnplugReset(void);
extern void ScalerDpMacDphyRx0CheckHdcpCpirqStatus(void);
extern bit ScalerDpMacDphyRx0HdcpReAuthStatusCheck(void);
extern void ScalerDpMacDphyRx0CpIRQ(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx0HdcpCheckValid(void);
extern bit ScalerDpMacDphyRx0HdcpCheckEnabled(void);
extern void ScalerDpMacDphyRx0HdcpDownLoadKey(bit bEnable);
extern void ScalerDpMacDphyRx0HdcpDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray);
extern void ScalerDpMacDphyRx0HdcpModeRestore(void);
extern void ScalerDpMacDphyRx0SetHdcpMode(EnumHDCPType enumHDCPType);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0FecDecode(BYTE ucFECDecode);
extern bit ScalerDpMacDphyRx0FecDecodeCheck(void);
extern void ScalerDpMacDphyRx0FecDetectStart(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRx0FecDetectEnd(EnumInputPort enumInputPort);
#endif

extern DWORD ScalerDpMacDphyRx0SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
extern bit ScalerDpMacDphyRx0SignalCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
extern bit ScalerDpMacDphyRx0CDRCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);

#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpMacDphyRx0MstReset(void);
#endif
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0LoadNewStreamPayload(void);
#endif // #if(_DP_MST_SUPPORT == _ON)

extern void ScalerDpMacDphyRx0ConfigMstOrSstMode(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2ResetProc(void);
extern void ScalerDpMacDphyRx0Hdcp2CipherDataRestore(void);
extern void ScalerDpMacDphyRx0ClrHdcp2CipherBackupInfo(void);

extern bit ScalerDpMacDphyRx0HdcpDetectLvp(void);
#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx0Hdcp2GetStxType(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp14Sha1DataWrite(void);
extern bit ScalerDpMacDphyRx0Hdcp14Auth1Check(void);
extern void ScalerDpMacDphyRx0Hdcp14WriteShaInput(void);
extern void ScalerDpMacDphyRx0Hdcp14LoadShaToDpcd(void);
extern void ScalerDpMacDphyRx0Hdcp14FakeAuthenProc(void);
extern void ScalerDpMacDphyRx0HDCPAuthShaRun(bit bIsFirst);
extern bit ScalerDpMacDphyRx0HdcpCheckLvp(void);
#endif

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Set8b10bDecErrorWD(bit bEn);
extern bit ScalerDpMacDphyRx0Check8b10bDecErrorStatus(void);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0AuxlessAlpmEnable(EnumInputPort enumInputPort, bit bEn);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacDphyRx0PowerProc_EXINT0(EnumPowerAction enumPowerAction);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0FecDecode_EXINT0(BYTE ucFECDecode);
extern bit ScalerDpMacDphyRx0FecDecodeCheck_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx0ConfigMstOrSstMode_EXINT0(void);
extern BYTE ScalerDpMacDphyRx0Tp1Detect_EXINT0(EnumDpLane enumDpLane);
extern BYTE ScalerDpMacDphyRx0Tp1DecodeCheck_EXINT0(BYTE ucDpLane);
extern BYTE ScalerDpMacDphyRx0Tp2DecodeCheck_EXINT0(EnumDpLane enumDpLane);
extern void ScalerDpMacDphyRx0LaneSwapSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern void ScalerDpMacDphyRx0LaneCountSet_EXINT0(BYTE ucDpLaneCount);
extern void ScalerDpMacDphyRx0SetCommaDetect_EXINT0(bit bEn);
extern void ScalerDpMacDphyRx0ClkSelect_EXINT0(EnumDpMacClkSelect enumClkSelect);
extern void ScalerDpMacDphyRx0Reset_EXINT0(void);
extern void ScalerDpMacDphyRx0ChannelFifoReset_EXINT0(void);
extern void ScalerDpMacDphyRx0DeSkewReset_EXINT0(void);
extern void ScalerDpMacDphyRx0EnhancementControlMode_EXINT0(bit bEn);
extern void ScalerDpMacDphyRx0Scramble_EXINT0(bit bEn);
extern DWORD ScalerDpMacDphyRx0SignalDetectMeasureCount_EXINT0(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);

extern void ScalerDpMacDphyRx0DigitalPhyHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacDphyRx0DigitalPhyLowPriorityIntHandler_EXINT0(void);

extern void ScalerDpMacDphyRx0MacResetProc_EXINT0(void);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0LoadNewStreamPayload_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx0SetHdcpMode_EXINT0(EnumHDCPType enumHDCPType);
extern void ScalerDpMacDphyRx0SetHdcp14Info_EXINT0(void);
extern BYTE ScalerDpMacDphyRx0GetHdcp14R0_EXINT0(EnumDpHdcp14R0Type enumDpHdcp14R0Type);
extern void ScalerDpMacDphyRx0PowerDataRecover_EXINT0(void);
extern void ScalerDpMacDphyRx0DecodeErrorCountReset_EXINT0(EnumDpMacDecodeMethod enumDpMacDecodeMethod);
extern void ScalerDpMacDphyRx0DecodeErrorCountOff_EXINT0(void);
extern void ScalerDpMacDphyRx0ErrorCounterUpdate_EXINT0(void);
extern void ScalerDpMacDphyRx0PhyCtsErrorCounterUpdate_EXINT0(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2ResetProc_EXINT0(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2EnableDecryption_EXINT0(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2SetAESType_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx0PrbsReverse_EXINT0(BYTE ucEnable);

//--------------------------------------------------
// WDINT For NONE Postfix
//--------------------------------------------------
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx0LaneValidCheck_WDINT(void);
#endif
extern bit ScalerDpMacDphyRx0DecodeCheck_WDINT(void);
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0AuxlessAlpmEnable_WDINT(EnumInputPort enumInputPort, bit bEn);
#endif

extern void ScalerDpMacDphyRx0WDTimerEventRebuildPhyProc_WDINT(void);

extern void ScalerDpMacDphyRx0SetCommaDetect_WDINT(bit bEn);
extern void ScalerDpMacDphyRx0ClkSelect_WDINT(EnumDpMacClkSelect enumClkSelect);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0LoadNewStreamPayload_WDINT(void);
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2EnableDecryption_WDINT(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_WDINT(void);
#endif
#endif


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern void ScalerDpMacDphyRx0CpIRQ_8b10b(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx0HdcpCheckEnabled_8b10b(void);
extern bit ScalerDpMacDphyRx0HdcpCheckValid_8b10b(void);
extern bit ScalerDpMacDphyRx0HdcpCheck_8b10b(void);
extern bit ScalerDpMacDphyRx0HdcpDetectLvp_8b10b(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2ResetProc_8b10b(void);
extern void ScalerDpMacDphyRx0Hdcp2CipherDataRestore_8b10b(void);

#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx0Hdcp2GetStxType_8b10b(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx0HdcpCheckLvp_8b10b(void);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2ResetProc_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2EnableDecryption_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2SetAESType_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx0Hdcp2SetStxType_8b10b_EXINT0(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0AuxlessAlpmHanlder_8b10b_EXINT0(void);
#endif

//--------------------------------------------------
// WDINT For 8B10B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_8b10b_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2EnableDecryption_8b10b_WDINT(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_8b10b_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_8b10b_WDINT(void);
extern void ScalerDpMacDphyRx0Hdcp2SetStxType_8b10b_WDINT(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif
#endif


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0PowerDataRecover_128b132b(void);
extern bit ScalerDpMacDphyRx0HdcpCheck_128b132b(void);
extern void ScalerDpMacDphyRx0CpIRQ_128b132b(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx0HdcpCheckEnabled_128b132b(void);
extern bit ScalerDpMacDphyRx0HdcpCheckValid_128b132b(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2ResetProc_128b132b(void);
extern void ScalerDpMacDphyRx0Hdcp2CipherDataRestore_128b132b(void);

extern bit ScalerDpMacDphyRx0HdcpDetectLvp_128b132b(void);
#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx0Hdcp2GetStxType_128b132b(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx0HdcpCheckLvp_128b132b(void);
#endif

extern BYTE ScalerDpMacDphyRx0Tp3DecodeCheck_EXINT0(EnumDpLane enumDpLane);

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2ResetProc_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2EnableDecryption_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2SetAESType_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx0Hdcp2SetStxType_128b132b_EXINT0(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0AuxlessAlpmHanlder_128b132b_EXINT0(void);
#endif

//--------------------------------------------------
// WDINT For 128B132B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_128b132b_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx0Hdcp2EnableDecryption_128b132b_WDINT(void);
extern void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_128b132b_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_128b132b_WDINT(void);
extern void ScalerDpMacDphyRx0Hdcp2SetStxType_128b132b_WDINT(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif
#endif // End of (_DP_HDCP2_RX_SUPPORT == _ON)
#endif // End of (_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)


///////////////////////////////////////////
// NNNNNeed special treatment
///////////////////////////////////////////

extern void ScalerDpMacDphyRx0HdcpSramClkGate(bit bEn);
extern void ScalerDpMacDphyRx0PowerDataRecover(void);
extern void ScalerDpMacDphyRx0PowerDataRecover_8b10b(void);
#endif
