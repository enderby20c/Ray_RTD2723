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
// ID Code      : ScalerDpMacDphyRx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX2_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of MAC DPHY Reset
//----------------------------------------------------------------------------
#define SET_DP_MAC_DPHY_RX2_DIGITAL_PHY_RESET_8B10B()               {\
                                                                        ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);\
                                                                        ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);\
                                                                    }

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_DPHY_RX2_DIGITAL_PHY_RESET_128B132B()            {\
                                                                        ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);\
                                                                        ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);\
                                                                    }
#endif

//----------------------------------------------------------------------------
// Macro of HDCP Information
//----------------------------------------------------------------------------
#define GET_DP_MAC_DPHY_RX2_HDCP_MODE_8B10B()                       ((ScalerGetBit(PC5_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

#define GET_DP_MAC_DPHY_RX2_HDCP_MODE_128B132B()                    (_HDCP_22)

#define GET_DP_MAC_DPHY_RX2_HDCP_MODE_8B10B_EXINT()                 ((ScalerGetBit_EXINT(PC5_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

#define GET_DP_MAC_DPHY_RX2_HDCP_MODE_128B132B_EXINT()              (_HDCP_22)

#define SET_DP_MAC_DPHY_RX2_LINK_INTEGRITY_128B132B()               {\
                                                                        ScalerSetBit(PD2_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);\
                                                                    }

#define SET_DP_MAC_DPHY_RX2_LINK_INTEGRITY_8B10B()                  {\
                                                                        ScalerSetBit(PC5_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);\
                                                                    }

//----------------------------------------------------------------------------
// Macro of Dp Hdcp 1.4 Information for M0_Prime
//----------------------------------------------------------------------------
#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX2_HDCP14_M0_0()                           (ScalerGetByte(PC5_2F_M0_BYTE_0) ^ 0x9D)
#define GET_DP_MAC_DPHY_RX2_HDCP14_M0_1()                           (~(ScalerGetByte(PC5_2E_M0_BYTE_1) ^ ScalerGetByte(PC5_2F_M0_BYTE_0)))
#define GET_DP_MAC_DPHY_RX2_HDCP14_M0_2()                           (ScalerGetByte(PC5_2D_M0_BYTE_2) ^ ScalerGetByte(PC5_2E_M0_BYTE_1))
#define GET_DP_MAC_DPHY_RX2_HDCP14_M0_3()                           (ScalerGetByte(PC5_2C_M0_BYTE_3) ^ ScalerGetByte(PC5_2D_M0_BYTE_2))
#define GET_DP_MAC_DPHY_RX2_HDCP14_M0_4()                           (ScalerGetByte(PC5_2B_M0_BYTE_4) ^ ScalerGetByte(PC5_2C_M0_BYTE_3))
#define GET_DP_MAC_DPHY_RX2_HDCP14_M0_5()                           (~(ScalerGetByte(PC5_2A_M0_BYTE_5) ^ ScalerGetByte(PC5_2B_M0_BYTE_4)))
#define GET_DP_MAC_DPHY_RX2_HDCP14_M0_6()                           (~(ScalerGetByte(PC5_29_M0_BYTE_6) ^ ScalerGetByte(PC5_2A_M0_BYTE_5)))
#define GET_DP_MAC_DPHY_RX2_HDCP14_M0_7()                           (~(ScalerGetByte(PC5_28_M0_BYTE_7) ^ ScalerGetByte(PC5_29_M0_BYTE_6)))
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of MST Stream Related Macro
//--------------------------------------------------
#define GET_DP_MAC_DPHY_RX2_STX_START_ADDRESS_8B10B(x)              (PC6_02_STHD_CTRL_2 + (2 * (x)))
#define GET_DP_MAC_DPHY_RX2_STX_END_ADDRESS_8B10B(x)                (PC6_02_STHD_CTRL_2 + (2 * (x)) + 1)

#define SET_DP_MAC_DPHY_RX2_LOAD_NEW_STREAM_PAYLOAD()               (ScalerDpMacDphyRx2LoadNewStreamPayload())
#define SET_DP_MAC_DPHY_RX2_LOAD_NEW_STREAM_PAYLOAD_EXINT()         (ScalerDpMacDphyRx2LoadNewStreamPayload_EXINT0())
#define SET_DP_MAC_DPHY_RX2_LOAD_NEW_STREAM_PAYLOAD_WDINT()         (ScalerDpMacDphyRx2LoadNewStreamPayload_WDINT())

#define GET_DP_MAC_DPHY_RX2_TIMESLOT_HDCP_ENC_VALUE_8B10B(x)        (((x) == 0) ? _FALSE : (ScalerGetBit((PC5_6B_HDCP_ENC_CTRL7 - ((x) / 8)), (_BIT0 << ((x) % 8)))))
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX2_TIMESLOT_HDCP_ENC_VALUE_128B132B(x)     (ScalerGetBit((PD2_17_HDCP_ENC_CTRL7 - ((x) / 8)), (_BIT0 << ((x) % 8))))
#endif
#endif // #if(_DP_MST_SUPPORT == _ON)

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX2_STX_START_ADDRESS_128B132B(x)           (PE4_02_STHD_CTRL_2 + (2 * (x)))
#define GET_DP_MAC_DPHY_RX2_STX_END_ADDRESS_128B132B(x)             (PE4_02_STHD_CTRL_2 + (2 * (x)) + 1)
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Dp FEC
//--------------------------------------------------
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX2_FEC_DECODE_STATUS()                     ((ScalerGetBit_EXINT(PC5_D0_FEC_DECODE_CTL, _BIT7) == _BIT7) || (ScalerGetBit_EXINT(PD2_80_FEC_DECODE_CTL, _BIT7) == _BIT7))
#else
#define GET_DP_MAC_DPHY_RX2_FEC_DECODE_STATUS()                     (ScalerGetBit_EXINT(PC5_D0_FEC_DECODE_CTL, _BIT7) == _BIT7)
#endif
#endif

#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
#define GET_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx2SignaldetectINTHappened)
#define SET_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx2SignaldetectINTHappened = _TRUE)
#define CLR_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED()             (g_bDpMacDphyRx2SignaldetectINTHappened = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Auxless ALPM Occurred
//--------------------------------------------------
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX2_AUXLESS_ALPM_OCCURRED()                 (ScalerGetBit(PC5_C3_ALPM_UFP_18, _BIT7) == _BIT7)
#define CLR_DP_MAC_DPHY_RX2_AUXLESS_ALPM_OCCURRED()                 {\
                                                                        ScalerSetBit(PC5_C3_ALPM_UFP_18, ~_BIT6, _BIT6);\
                                                                        ScalerSetBit(PC5_C3_ALPM_UFP_18, ~_BIT6, 0x00);\
                                                                    }
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
extern bit g_bDpMacDphyRx2SignaldetectINTHappened;
#endif

extern BYTE g_ucDpMacDphyRx2Temp;
extern BYTE g_ucDpMacDphyRx2EQCRC;

#if(_DP_MST_SUPPORT == _ON)
extern StructDPMacRxMiscInfo g_stDpMacDphyRx2MiscInfo;
#endif

extern StructDpMacDphyRxHdcpCipherBackupInfo g_stDpMacDphyRx2HdcpCipherBackupInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacDphyRx2PowerProc(EnumPowerAction enumPowerAction);
#endif

extern bit ScalerDpMacDphyRx2NormalPreDetect(void);
extern bit ScalerDpMacDphyRx2PSPreDetect(void);

extern void ScalerDpMacDphyRx2DigitalPhyInitial(void);
extern bit ScalerDpMacDphyRx2PhyCtsTp1Check(void);
extern bit ScalerDpMacDphyRx2PhyCtsTp2Check(void);
extern void ScalerDpMacDphyRx2ScrambleSetting(void);
extern bit ScalerDpMacDphyRx2DecodeErrorCountReset(EnumDpMacDecodeMethod enumDpMacDecodeMethod);
extern bit ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(WORD usErrorCriteria, BYTE ucDpMacRx2LaneNumber);
extern WORD ScalerDpMacDphyRx2GetDecodeErrorCount(BYTE ucDpMacRx2LaneNumber);
extern void ScalerDpMacDphyRx2LaneSwapSelect(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern BYTE ScalerDpMacDphyRx2GetLaneMuxMapping(EnumDpLane enumDpLane);
extern void ScalerDpMacDphyRx2LaneCountSet(BYTE ucDpLaneCount);
extern void ScalerDpMacDphyRx2SetCommaDetect(bit bEn);
extern void ScalerDpMacDphyRx2ClkSelect(EnumDpMacClkSelect enumClkSelect);
extern void ScalerDpMacDphyRx2ChannelFifoReset(void);

extern bit ScalerDpMacDphyRx2AlignCheck(void);
extern bit ScalerDpMacDphyRx2DecodeCheck(void);

extern void ScalerDpMacDphyRx2Hdcp14ResetProc(void);
extern void ScalerDpMacDphyRx2HDCPUnplugReset(void);
extern void ScalerDpMacDphyRx2CheckHdcpCpirqStatus(void);
extern bit ScalerDpMacDphyRx2HdcpReAuthStatusCheck(void);
extern void ScalerDpMacDphyRx2CpIRQ(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx2HdcpCheckValid(void);
extern bit ScalerDpMacDphyRx2HdcpCheckEnabled(void);
extern void ScalerDpMacDphyRx2HdcpDownLoadKey(bit bEnable);
extern void ScalerDpMacDphyRx2HdcpDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray);
extern void ScalerDpMacDphyRx2HdcpModeRestore(void);
extern void ScalerDpMacDphyRx2SetHdcpMode(EnumHDCPType enumHDCPType);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2FecDecode(BYTE ucFECDecode);
extern bit ScalerDpMacDphyRx2FecDecodeCheck(void);
extern void ScalerDpMacDphyRx2FecDetectStart(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRx2FecDetectEnd(EnumInputPort enumInputPort);
#endif

extern DWORD ScalerDpMacDphyRx2SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
extern bit ScalerDpMacDphyRx2SignalCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
extern bit ScalerDpMacDphyRx2CDRCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);

#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpMacDphyRx2MstReset(void);
#endif
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2LoadNewStreamPayload(void);
#endif // #if(_DP_MST_SUPPORT == _ON)

extern void ScalerDpMacDphyRx2ConfigMstOrSstMode(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2ResetProc(void);
extern void ScalerDpMacDphyRx2Hdcp2CipherDataRestore(void);
extern void ScalerDpMacDphyRx2ClrHdcp2CipherBackupInfo(void);

extern bit ScalerDpMacDphyRx2HdcpDetectLvp(void);
#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx2Hdcp2GetStxType(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp14Sha1DataWrite(void);
extern bit ScalerDpMacDphyRx2Hdcp14Auth1Check(void);
extern void ScalerDpMacDphyRx2Hdcp14WriteShaInput(void);
extern void ScalerDpMacDphyRx2Hdcp14LoadShaToDpcd(void);
extern void ScalerDpMacDphyRx2Hdcp14FakeAuthenProc(void);
extern void ScalerDpMacDphyRx2HDCPAuthShaRun(bit bIsFirst);
extern bit ScalerDpMacDphyRx2HdcpCheckLvp(void);
#endif

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Set8b10bDecErrorWD(bit bEn);
extern bit ScalerDpMacDphyRx2Check8b10bDecErrorStatus(void);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2AuxlessAlpmEnable(EnumInputPort enumInputPort, bit bEn);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacDphyRx2PowerProc_EXINT0(EnumPowerAction enumPowerAction);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2FecDecode_EXINT0(BYTE ucFECDecode);
extern bit ScalerDpMacDphyRx2FecDecodeCheck_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx2ConfigMstOrSstMode_EXINT0(void);
extern BYTE ScalerDpMacDphyRx2Tp1Detect_EXINT0(EnumDpLane enumDpLane);
extern BYTE ScalerDpMacDphyRx2Tp1DecodeCheck_EXINT0(BYTE ucDpLane);
extern BYTE ScalerDpMacDphyRx2Tp2DecodeCheck_EXINT0(EnumDpLane enumDpLane);
extern void ScalerDpMacDphyRx2LaneSwapSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern void ScalerDpMacDphyRx2LaneCountSet_EXINT0(BYTE ucDpLaneCount);
extern void ScalerDpMacDphyRx2SetCommaDetect_EXINT0(bit bEn);
extern void ScalerDpMacDphyRx2ClkSelect_EXINT0(EnumDpMacClkSelect enumClkSelect);
extern void ScalerDpMacDphyRx2Reset_EXINT0(void);
extern void ScalerDpMacDphyRx2ChannelFifoReset_EXINT0(void);
extern void ScalerDpMacDphyRx2DeSkewReset_EXINT0(void);
extern void ScalerDpMacDphyRx2EnhancementControlMode_EXINT0(bit bEn);
extern void ScalerDpMacDphyRx2Scramble_EXINT0(bit bEn);
extern DWORD ScalerDpMacDphyRx2SignalDetectMeasureCount_EXINT0(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);

extern void ScalerDpMacDphyRx2DigitalPhyHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacDphyRx2DigitalPhyLowPriorityIntHandler_EXINT0(void);

extern void ScalerDpMacDphyRx2MacResetProc_EXINT0(void);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2LoadNewStreamPayload_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx2SetHdcpMode_EXINT0(EnumHDCPType enumHDCPType);
extern void ScalerDpMacDphyRx2SetHdcp14Info_EXINT0(void);
extern BYTE ScalerDpMacDphyRx2GetHdcp14R0_EXINT0(EnumDpHdcp14R0Type enumDpHdcp14R0Type);
extern void ScalerDpMacDphyRx2PowerDataRecover_EXINT0(void);
extern void ScalerDpMacDphyRx2DecodeErrorCountReset_EXINT0(EnumDpMacDecodeMethod enumDpMacDecodeMethod);
extern void ScalerDpMacDphyRx2DecodeErrorCountOff_EXINT0(void);
extern void ScalerDpMacDphyRx2ErrorCounterUpdate_EXINT0(void);
extern void ScalerDpMacDphyRx2PhyCtsErrorCounterUpdate_EXINT0(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2ResetProc_EXINT0(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableLinkIntegrityCheck_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2EnableDecryption_EXINT0(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableAuthDone_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2SetAESType_EXINT0(void);
#endif

extern void ScalerDpMacDphyRx2PrbsReverse_EXINT0(BYTE ucEnable);

//--------------------------------------------------
// WDINT For NONE Postfix
//--------------------------------------------------
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx2LaneValidCheck_WDINT(void);
#endif
extern bit ScalerDpMacDphyRx2DecodeCheck_WDINT(void);
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2AuxlessAlpmEnable_WDINT(EnumInputPort enumInputPort, bit bEn);
#endif

extern void ScalerDpMacDphyRx2WDTimerEventRebuildPhyProc_WDINT(void);

extern void ScalerDpMacDphyRx2SetCommaDetect_WDINT(bit bEn);
extern void ScalerDpMacDphyRx2ClkSelect_WDINT(EnumDpMacClkSelect enumClkSelect);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2LoadNewStreamPayload_WDINT(void);
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2EnableLinkIntegrityCheck_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2EnableDecryption_WDINT(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableAuthDone_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2SetRepeaterAESType_WDINT(void);
#endif
#endif


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern void ScalerDpMacDphyRx2CpIRQ_8b10b(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx2HdcpCheckEnabled_8b10b(void);
extern bit ScalerDpMacDphyRx2HdcpCheckValid_8b10b(void);
extern bit ScalerDpMacDphyRx2HdcpCheck_8b10b(void);
extern bit ScalerDpMacDphyRx2HdcpDetectLvp_8b10b(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2ResetProc_8b10b(void);
extern void ScalerDpMacDphyRx2Hdcp2CipherDataRestore_8b10b(void);

#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx2Hdcp2GetStxType_8b10b(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx2HdcpCheckLvp_8b10b(void);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2ResetProc_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableLinkIntegrityCheck_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2EnableDecryption_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableAuthDone_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2SetAESType_8b10b_EXINT0(void);
extern void ScalerDpMacDphyRx2Hdcp2SetStxType_8b10b_EXINT0(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2AuxlessAlpmHanlder_8b10b_EXINT0(void);
#endif

//--------------------------------------------------
// WDINT For 8B10B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2EnableLinkIntegrityCheck_8b10b_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2EnableDecryption_8b10b_WDINT(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableAuthDone_8b10b_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2SetRepeaterAESType_8b10b_WDINT(void);
extern void ScalerDpMacDphyRx2Hdcp2SetStxType_8b10b_WDINT(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif
#endif


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2PowerDataRecover_128b132b(void);
extern bit ScalerDpMacDphyRx2HdcpCheck_128b132b(void);
extern void ScalerDpMacDphyRx2CpIRQ_128b132b(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRx2HdcpCheckEnabled_128b132b(void);
extern bit ScalerDpMacDphyRx2HdcpCheckValid_128b132b(void);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2ResetProc_128b132b(void);
extern void ScalerDpMacDphyRx2Hdcp2CipherDataRestore_128b132b(void);

extern bit ScalerDpMacDphyRx2HdcpDetectLvp_128b132b(void);
#if(_DP_TX_SUPPORT == _ON)
extern EnumDpHdcp2AESType ScalerDpMacDphyRx2Hdcp2GetStxType_128b132b(BYTE ucStreamId);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx2HdcpCheckLvp_128b132b(void);
#endif

extern BYTE ScalerDpMacDphyRx2Tp3DecodeCheck_EXINT0(EnumDpLane enumDpLane);

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2ResetProc_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableLinkIntegrityCheck_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2EnableDecryption_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableAuthDone_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2SetAESType_128b132b_EXINT0(void);
extern void ScalerDpMacDphyRx2Hdcp2SetStxType_128b132b_EXINT0(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2AuxlessAlpmHanlder_128b132b_EXINT0(void);
#endif

//--------------------------------------------------
// WDINT For 128B132B Postfix
//--------------------------------------------------
#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2EnableLinkIntegrityCheck_128b132b_WDINT(bit bEnable);
extern void ScalerDpMacDphyRx2Hdcp2EnableDecryption_128b132b_WDINT(void);
extern void ScalerDpMacDphyRx2Hdcp2EnableAuthDone_128b132b_WDINT(bit bEnable);

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx2Hdcp2SetRepeaterAESType_128b132b_WDINT(void);
extern void ScalerDpMacDphyRx2Hdcp2SetStxType_128b132b_WDINT(EnumDpStreamNum enumDpStreamNum, BYTE ucType);
#endif
#endif // End of (_DP_HDCP2_RX_SUPPORT == _ON)
#endif // End of (_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)


///////////////////////////////////////////
// NNNNNeed special treatment
///////////////////////////////////////////

extern void ScalerDpMacDphyRx2HdcpSramClkGate(bit bEn);
extern void ScalerDpMacDphyRx2PowerDataRecover(void);
extern void ScalerDpMacDphyRx2PowerDataRecover_8b10b(void);
#endif
