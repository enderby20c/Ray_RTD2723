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
// ID Code      : ScalerDpMacDphyRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX1_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of MAC DPHY Reset
//----------------------------------------------------------------------------
#define SET_DP_MAC_DPHY_RX1_DIGITAL_PHY_RESET_8B10B()               {\
                                                                        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);\
                                                                        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);\
                                                                    }

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_DPHY_RX1_DIGITAL_PHY_RESET_128B132B()            {\
                                                                        ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);\
                                                                        ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);\
                                                                    }
#endif

//----------------------------------------------------------------------------
// Macro of HDCP Information
//----------------------------------------------------------------------------
#define GET_DP_MAC_DPHY_RX1_HDCP_MODE_8B10B()                       ((ScalerGetBit(PB0_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

#define GET_DP_MAC_DPHY_RX1_HDCP_MODE_128B132B()                    (_HDCP_22)

#define GET_DP_MAC_DPHY_RX1_HDCP_MODE_8B10B_EXINT()                 ((ScalerGetBit_EXINT(PB0_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

#define GET_DP_MAC_DPHY_RX1_HDCP_MODE_128B132B_EXINT()              (_HDCP_22)

#define SET_DP_MAC_DPHY_RX1_LINK_INTEGRITY_128B132B()               {\
                                                                        ScalerSetBit(P1F_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);\
                                                                    }

#define SET_DP_MAC_DPHY_RX1_LINK_INTEGRITY_8B10B()                  {\
                                                                        ScalerSetBit(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);\
                                                                    }

//----------------------------------------------------------------------------
// Macro of Dp Hdcp 1.4 Information for M0_Prime
//----------------------------------------------------------------------------
#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX1_HDCP14_M0_0()                           (ScalerGetByte(PB0_2F_M0_BYTE_0) ^ 0x9D)
#define GET_DP_MAC_DPHY_RX1_HDCP14_M0_1()                           (~(ScalerGetByte(PB0_2E_M0_BYTE_1) ^ ScalerGetByte(PB0_2F_M0_BYTE_0)))
#define GET_DP_MAC_DPHY_RX1_HDCP14_M0_2()                           (ScalerGetByte(PB0_2D_M0_BYTE_2) ^ ScalerGetByte(PB0_2E_M0_BYTE_1))
#define GET_DP_MAC_DPHY_RX1_HDCP14_M0_3()                           (ScalerGetByte(PB0_2C_M0_BYTE_3) ^ ScalerGetByte(PB0_2D_M0_BYTE_2))
#define GET_DP_MAC_DPHY_RX1_HDCP14_M0_4()                           (ScalerGetByte(PB0_2B_M0_BYTE_4) ^ ScalerGetByte(PB0_2C_M0_BYTE_3))
#define GET_DP_MAC_DPHY_RX1_HDCP14_M0_5()                           (~(ScalerGetByte(PB0_2A_M0_BYTE_5) ^ ScalerGetByte(PB0_2B_M0_BYTE_4)))
#define GET_DP_MAC_DPHY_RX1_HDCP14_M0_6()                           (~(ScalerGetByte(PB0_29_M0_BYTE_6) ^ ScalerGetByte(PB0_2A_M0_BYTE_5)))
#define GET_DP_MAC_DPHY_RX1_HDCP14_M0_7()                           (~(ScalerGetByte(PB0_28_M0_BYTE_7) ^ ScalerGetByte(PB0_29_M0_BYTE_6)))
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of MST Stream Related Macro
//--------------------------------------------------
#define GET_DP_MAC_DPHY_RX1_STX_START_ADDRESS_8B10B(x)              (PB8_02_STHD_CTRL_2 + (2 * (x)))
#define GET_DP_MAC_DPHY_RX1_STX_END_ADDRESS_8B10B(x)                (PB8_02_STHD_CTRL_2 + (2 * (x)) + 1)

#define SET_DP_MAC_DPHY_RX1_LOAD_NEW_STREAM_PAYLOAD()               (ScalerDpMacDphyRx1LoadNewStreamPayload())
#define SET_DP_MAC_DPHY_RX1_LOAD_NEW_STREAM_PAYLOAD_EXINT()         (ScalerDpMacDphyRx1LoadNewStreamPayload_EXINT0())
#define SET_DP_MAC_DPHY_RX1_LOAD_NEW_STREAM_PAYLOAD_WDINT()         (ScalerDpMacDphyRx1LoadNewStreamPayload_WDINT())

#define GET_DP_MAC_DPHY_RX1_TIMESLOT_HDCP_ENC_VALUE_8B10B(x)        (((x) == 0) ? _FALSE : (ScalerGetBit((PB0_6B_HDCP_ENC_CTRL7 - ((x) / 8)), (_BIT0 << ((x) % 8)))))
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX1_TIMESLOT_HDCP_ENC_VALUE_128B132B(x)     (ScalerGetBit((P1F_17_HDCP_ENC_CTRL7 - ((x) / 8)), (_BIT0 << ((x) % 8))))
#endif
#endif // #if(_DP_MST_SUPPORT == _ON)

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX1_STX_START_ADDRESS_128B132B(x)           (P9F_02_STHD_CTRL_2 + (2 * (x)))
#define GET_DP_MAC_DPHY_RX1_STX_END_ADDRESS_128B132B(x)             (P9F_02_STHD_CTRL_2 + (2 * (x)) + 1)
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Dp FEC
//--------------------------------------------------
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX1_FEC_DECODE_STATUS()                     ((ScalerGetBit_EXINT(PB0_D0_FEC_DECODE_CTL, _BIT7) == _BIT7) || (ScalerGetBit_EXINT(P1F_80_FEC_DECODE_CTL, _BIT7) == _BIT7))
#else
#define GET_DP_MAC_DPHY_RX1_FEC_DECODE_STATUS()                     (ScalerGetBit_EXINT(PB0_D0_FEC_DECODE_CTL, _BIT7) == _BIT7)
#endif
#endif

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
#define GET_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx1SignaldetectINTHappened)
#define SET_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx1SignaldetectINTHappened = _TRUE)
#define CLR_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx1SignaldetectINTHappened = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Auxless ALPM Occurred
//--------------------------------------------------
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX1_AUXLESS_ALPM_OCCURRED()                 (ScalerGetBit(PB0_C3_ALPM_UFP_18, _BIT7) == _BIT7)
#define CLR_DP_MAC_DPHY_RX1_AUXLESS_ALPM_OCCURRED()                 {\
                                                                        ScalerSetBit(PB0_C3_ALPM_UFP_18, ~_BIT6, _BIT6);\
                                                                        ScalerSetBit(PB0_C3_ALPM_UFP_18, ~_BIT6, 0x00);\
                                                                    }
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
extern bit g_bDpMacDphyRx1SignaldetectINTHappened;
#endif

extern BYTE g_ucDpMacDphyRx1Temp;
extern BYTE g_ucDpMacDphyRx1EQCRC;

#if(_DP_MST_SUPPORT == _ON)
extern StructDPMacRxMiscInfo g_stDpMacDphyRx1MiscInfo;
#endif

extern StructDpMacDphyRxHdcpCipherBackupInfo g_stDpMacDphyRx1HdcpCipherBackupInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacDphyRx1PowerProc(EnumPowerAction enumPowerAction);
#endif

extern bit ScalerDpMacDphyRx1NormalPreDetect(void);
extern bit ScalerDpMacDphyRx1PSPreDetect(void);

extern void ScalerDpMacDphyRx1DigitalPhyInitial(void);
extern bit ScalerDpMacDphyRx1PhyCtsTp1Check(void);
extern bit ScalerDpMacDphyRx1PhyCtsTp2Check(void);
extern void ScalerDpMacDphyRx1ScrambleSetting(void);
extern bit ScalerDpMacDphyRx1DecodeErrorCountReset(EnumDpMacDecodeMethod enumDpMacDecodeMethod);
extern bit ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(WORD usErrorCriteria, BYTE ucDpMacRx1LaneNumber);
extern WORD ScalerDpMacDphyRx1GetDecodeErrorCount(BYTE ucDpMacRx1LaneNumber);
extern void ScalerDpMacDphyRx1LaneSwapSelect(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern BYTE ScalerDpMacDphyRx1GetLaneMuxMapping(EnumDpLane enumDpLane);
extern void ScalerDpMacDphyRx1LaneCountSet(BYTE ucDpLaneCount);
extern void ScalerDpMacDphyRx1SetCommaDetect(bit bEn);
extern void ScalerDpMacDphyRx1ClkSelect(EnumDpMacClkSelect enumClkSelect);
extern void ScalerDpMacDphyRx1ChannelFifoReset(void);

extern bit ScalerDpMacDphyRx1AlignCheck(void);
extern bit ScalerDpMacDphyRx1DecodeCheck(void);

extern void ScalerDpMacDphyRx1Hdcp14ResetProc(void);
extern void ScalerDpMacDphyRx1HDCPUnplugReset(void);
extern void ScalerDpMacDphyRx1CheckHdcpCpirqStatus(void);
extern bit ScalerDpMacDphyRx1HdcpReAuthStatusCheck(void);
extern void ScalerDpMacDphyRx1CpIRQ(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx1HdcpCheckValid(void);
extern bit ScalerDpMacDphyRx1HdcpCheckEnabled(void);
extern void ScalerDpMacDphyRx1HdcpDownLoadKey(bit bEnable);
extern void ScalerDpMacDphyRx1HdcpDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray);
extern void ScalerDpMacDphyRx1HdcpModeRestore(void);
extern void ScalerDpMacDphyRx1SetHdcpMode(EnumHDCPType enumHDCPType);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1FecDecode(BYTE ucFECDecode);
extern bit ScalerDpMacDphyRx1FecDecodeCheck(void);
extern void ScalerDpMacDphyRx1FecDetectStart(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRx1FecDetectEnd(EnumInputPort enumInputPort);
#endif

extern DWORD ScalerDpMacDphyRx1SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
extern bit ScalerDpMacDphyRx1SignalCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
extern bit ScalerDpMacDphyRx1CDRCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);

#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpMacDphyRx1MstReset(void);
#endif
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1LoadNewStreamPayload(void);
#endif // #if(_DP_MST_SUPPORT == _ON)

extern void ScalerDpMacDphyRx1ConfigMstOrSstMode(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2ResetProc(void);
extern void ScalerDpMacDphyRx1Hdcp2CipherDataRestore(void);
extern void ScalerDpMacDphyRx1ClrHdcp2CipherBackupInfo(void);

extern bit ScalerDpMacDphyRx1HdcpDetectLvp(void);
#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx1Hdcp2GetStxType(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp14Sha1DataWrite(void);
extern bit ScalerDpMacDphyRx1Hdcp14Auth1Check(void);
extern void ScalerDpMacDphyRx1Hdcp14WriteShaInput(void);
extern void ScalerDpMacDphyRx1Hdcp14LoadShaToDpcd(void);
extern void ScalerDpMacDphyRx1Hdcp14FakeAuthenProc(void);
extern void ScalerDpMacDphyRx1HDCPAuthShaRun(bit bIsFirst);
extern bit ScalerDpMacDphyRx1HdcpCheckLvp(void);
#endif

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Set8b10bDecErrorWD(bit bEn);
extern bit ScalerDpMacDphyRx1Check8b10bDecErrorStatus(void);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1AuxlessAlpmEnable(EnumInputPort enumInputPort, bit bEn);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacDphyRx1PowerProc_EXINT0(EnumPowerAction enumPowerAction);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1FecDecode_EXINT0(BYTE ucFECDecode);
extern bit ScalerDpMacDphyRx1FecDecodeCheck_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx1ConfigMstOrSstMode_EXINT0(void);
extern BYTE ScalerDpMacDphyRx1Tp1Detect_EXINT0(EnumDpLane enumDpLane);
extern BYTE ScalerDpMacDphyRx1Tp1DecodeCheck_EXINT0(BYTE ucDpLane);
extern BYTE ScalerDpMacDphyRx1Tp2DecodeCheck_EXINT0(EnumDpLane enumDpLane);
extern void ScalerDpMacDphyRx1LaneSwapSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern void ScalerDpMacDphyRx1LaneCountSet_EXINT0(BYTE ucDpLaneCount);
extern void ScalerDpMacDphyRx1SetCommaDetect_EXINT0(bit bEn);
extern void ScalerDpMacDphyRx1ClkSelect_EXINT0(EnumDpMacClkSelect enumClkSelect);
extern void ScalerDpMacDphyRx1Reset_EXINT0(void);
extern void ScalerDpMacDphyRx1ChannelFifoReset_EXINT0(void);
extern void ScalerDpMacDphyRx1DeSkewReset_EXINT0(void);
extern void ScalerDpMacDphyRx1EnhancementControlMode_EXINT0(bit bEn);
extern void ScalerDpMacDphyRx1Scramble_EXINT0(bit bEn);
extern DWORD ScalerDpMacDphyRx1SignalDetectMeasureCount_EXINT0(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);

extern void ScalerDpMacDphyRx1DigitalPhyHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacDphyRx1DigitalPhyLowPriorityIntHandler_EXINT0(void);

extern void ScalerDpMacDphyRx1MacResetProc_EXINT0(void);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1LoadNewStreamPayload_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx1SetHdcpMode_EXINT0(EnumHDCPType enumHDCPType);
extern void ScalerDpMacDphyRx1SetHdcp14Info_EXINT0(void);
extern BYTE ScalerDpMacDphyRx1GetHdcp14R0_EXINT0(EnumDpHdcp14R0Type enumDpHdcp14R0Type);
extern void ScalerDpMacDphyRx1PowerDataRecover_EXINT0(void);
extern void ScalerDpMacDphyRx1DecodeErrorCountReset_EXINT0(EnumDpMacDecodeMethod enumDpMacDecodeMethod);
extern void ScalerDpMacDphyRx1DecodeErrorCountOff_EXINT0(void);
extern void ScalerDpMacDphyRx1ErrorCounterUpdate_EXINT0(void);
extern void ScalerDpMacDphyRx1PhyCtsErrorCounterUpdate_EXINT0(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2ResetProc_EXINT0(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2EnableDecryption_EXINT0(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2SetAESType_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx1PrbsReverse_EXINT0(BYTE ucEnable);

//--------------------------------------------------
// WDINT For NONE Postfix
//--------------------------------------------------
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx1LaneValidCheck_WDINT(void);
#endif
extern bit ScalerDpMacDphyRx1DecodeCheck_WDINT(void);
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1AuxlessAlpmEnable_WDINT(EnumInputPort enumInputPort, bit bEn);
#endif

extern void ScalerDpMacDphyRx1WDTimerEventRebuildPhyProc_WDINT(void);

extern void ScalerDpMacDphyRx1SetCommaDetect_WDINT(bit bEn);
extern void ScalerDpMacDphyRx1ClkSelect_WDINT(EnumDpMacClkSelect enumClkSelect);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1LoadNewStreamPayload_WDINT(void);
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2EnableDecryption_WDINT(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2SetRepeaterAESType_WDINT(void);
#endif
#endif


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern void ScalerDpMacDphyRx1CpIRQ_8b10b(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx1HdcpCheckEnabled_8b10b(void);
extern bit ScalerDpMacDphyRx1HdcpCheckValid_8b10b(void);
extern bit ScalerDpMacDphyRx1HdcpCheck_8b10b(void);
extern bit ScalerDpMacDphyRx1HdcpDetectLvp_8b10b(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2ResetProc_8b10b(void);
extern void ScalerDpMacDphyRx1Hdcp2CipherDataRestore_8b10b(void);

#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx1Hdcp2GetStxType_8b10b(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx1HdcpCheckLvp_8b10b(void);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2ResetProc_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2EnableDecryption_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2SetAESType_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx1Hdcp2SetStxType_8b10b_EXINT0(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1AuxlessAlpmHanlder_8b10b_EXINT0(void);
#endif

//--------------------------------------------------
// WDINT For 8B10B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_8b10b_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2EnableDecryption_8b10b_WDINT(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_8b10b_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2SetRepeaterAESType_8b10b_WDINT(void);
extern void ScalerDpMacDphyRx1Hdcp2SetStxType_8b10b_WDINT(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif
#endif


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1PowerDataRecover_128b132b(void);
extern bit ScalerDpMacDphyRx1HdcpCheck_128b132b(void);
extern void ScalerDpMacDphyRx1CpIRQ_128b132b(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx1HdcpCheckEnabled_128b132b(void);
extern bit ScalerDpMacDphyRx1HdcpCheckValid_128b132b(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2ResetProc_128b132b(void);
extern void ScalerDpMacDphyRx1Hdcp2CipherDataRestore_128b132b(void);

extern bit ScalerDpMacDphyRx1HdcpDetectLvp_128b132b(void);
#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx1Hdcp2GetStxType_128b132b(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx1HdcpCheckLvp_128b132b(void);
#endif

extern BYTE ScalerDpMacDphyRx1Tp3DecodeCheck_EXINT0(EnumDpLane enumDpLane);

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2ResetProc_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2EnableDecryption_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2SetAESType_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx1Hdcp2SetStxType_128b132b_EXINT0(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1AuxlessAlpmHanlder_128b132b_EXINT0(void);
#endif

//--------------------------------------------------
// WDINT For 128B132B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_128b132b_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx1Hdcp2EnableDecryption_128b132b_WDINT(void);
extern void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_128b132b_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx1Hdcp2SetRepeaterAESType_128b132b_WDINT(void);
extern void ScalerDpMacDphyRx1Hdcp2SetStxType_128b132b_WDINT(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif
#endif // End of (_DP_HDCP2_RX_SUPPORT == _ON)
#endif // End of (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)


///////////////////////////////////////////
// NNNNNeed special treatment
///////////////////////////////////////////

extern void ScalerDpMacDphyRx1HdcpSramClkGate(bit bEn);
extern void ScalerDpMacDphyRx1PowerDataRecover(void);
extern void ScalerDpMacDphyRx1PowerDataRecover_8b10b(void);
#endif
