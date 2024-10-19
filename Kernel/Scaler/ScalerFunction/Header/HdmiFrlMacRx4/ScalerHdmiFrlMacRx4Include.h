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
// ID Code      : ScalerHdmiFrlMacRx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// HDMI FRL RX3 Option
//--------------------------------------------------
#define _HDMI_FRL_MAC_RX4_LFSR_TEST_MODE                        _OFF
#define _HDMI_FRL_MAC_RX4_LINK_TRAINING_BYPASS                  _OFF

//--------------------------------------------------
// Macro of Link Training State
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE()              (g_stHdmiFrlMacRx4CtrlInfo.b4LtState)
#define SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(x)             (g_stHdmiFrlMacRx4CtrlInfo.b4LtState = (x))

//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_PHY_SET()                          (g_stHdmiFrlMacRx4CtrlInfo.b1FrlPhySet)
#define SET_HDMI_FRL_MAC_RX4_PHY_SET()                          (g_stHdmiFrlMacRx4CtrlInfo.b1FrlPhySet = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_PHY_SET()                          (g_stHdmiFrlMacRx4CtrlInfo.b1FrlPhySet = _FALSE)

//--------------------------------------------------
// Macro of Add Reactive Time after Link Training Pass
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_REACTIVE_SEARCH_TIME()             (g_stHdmiFrlMacRx4CtrlInfo.b1ReactiveSearchTime)
#define SET_HDMI_FRL_MAC_RX4_REACTIVE_SEARCH_TIME()             (g_stHdmiFrlMacRx4CtrlInfo.b1ReactiveSearchTime = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_REACTIVE_SEARCH_TIME()             (g_stHdmiFrlMacRx4CtrlInfo.b1ReactiveSearchTime = _FALSE)

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// DSC H/V Timing
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_CVTEM_HFRONT()                     ((ScalerGetByte(P1E_81_DSC_HINFO_1) << 8) | ScalerGetByte(P1E_80_DSC_HINFO_0))
#define GET_HDMI_FRL_MAC_RX4_CVTEM_HSYNC()                      ((ScalerGetByte(P1E_83_DSC_HINFO_3) << 8) | ScalerGetByte(P1E_82_DSC_HINFO_2))
#define GET_HDMI_FRL_MAC_RX4_CVTEM_HBACK()                      ((ScalerGetByte(P1E_85_DSC_HIFO_5) << 8) | ScalerGetByte(P1E_84_DSC_HINFO_4))
#define GET_HDMI_FRL_MAC_RX4_CVTEM_HCACTIVE_BYTES()             ((ScalerGetByte(P1E_87_DSC_HINO_7) << 8) | ScalerGetByte(P1E_86_DSC_HINFO_6))

// 0 is positive, 1 is negative
#define GET_HDMI_FRL_MAC_RX4_VSYNC_POLARITY()                   (ScalerGetBit(P69_26_HDMI21_DI_0, _BIT4) >> 4)
#endif

#define GET_HDMI_FRL_MAC_RX4_VFRONT()                           (g_usHdmiFrlMacRx4Vfront)
#define GET_HDMI_FRL_MAC_RX4_VSYNC()                            (g_usHdmiFrlMacRx4Vsync)
#define GET_HDMI_FRL_MAC_RX4_VBACK()                            (g_usHdmiFrlMacRx4Vback)
#define GET_HDMI_FRL_MAC_RX4_VACTIVE()                          (g_usHdmiFrlMacRx4Vactive)
#define GET_HDMI_FRL_MAC_RX4_VTOTAL()                           (g_usHdmiFrlMacRx4Vtotal)

//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION()             (g_ucHdmiFrlMacRx4AviInfo)

//--------------------------------------------------
// Macro of Native Htotal for EDID Table Analysis
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_NATIVE_HTOTAL()                    (g_usHdmiFrlMacRx4NativeHtotal)
#define SET_HDMI_FRL_MAC_RX4_NATIVE_HTOTAL(x)                   (g_usHdmiFrlMacRx4NativeHtotal = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructHdmiFrlCtrlInfo g_stHdmiFrlMacRx4CtrlInfo;

extern WORD g_usHdmiFrlMacRx4Hfront;
extern WORD g_usHdmiFrlMacRx4Hsync;
extern WORD g_usHdmiFrlMacRx4Hback;
extern WORD g_usHdmiFrlMacRx4Hactive;
extern WORD g_usHdmiFrlMacRx4Htotal;
extern WORD g_usHdmiFrlMacRx4Vfront;
extern WORD g_usHdmiFrlMacRx4Vsync;
extern WORD g_usHdmiFrlMacRx4Vback;
extern WORD g_usHdmiFrlMacRx4Vactive;
extern WORD g_usHdmiFrlMacRx4Vtotal;
extern BYTE g_ucHdmiFrlMacRx4AviInfo;

extern DWORD g_ulHdmiFrlMacRx4PixelClkValue;

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern DWORD g_ulHdmiFrlMacRx4DSCClkValue;
#endif

extern WORD g_usHdmiFrlMacRx4NativeHtotal;

extern BYTE g_ucHdmiFrlMacRx4ScdcStatusFlag;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdmiFrlMacRx4ScanInitial(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRx4RoundRobinIrqEnable(bit bEnable);
extern bit ScalerHdmiFrlMacRx4NormalPreDetect(void);
extern void ScalerHdmiFrlMacRx4FirstActiveProc(EnumSourceType enumSourceType);
extern void ScalerHdmiFrlMacRx4HdmiAVMuteProc(void);
extern EnumSourceType ScalerHdmiFrlMacRx4ScanInputPort(EnumPortType enumPortType);
extern bit ScalerHdmiFrlMacRx4StableDetect(EnumSourceType enumSourceType);
extern WORD ScalerHdmiFrlMacRx4OffMeasureClk(BYTE ucMeasureClk);
extern void ScalerHdmiFrlMacRx4PacketDetectEvent(void);
extern void ScalerHdmiFrlMacRx4TimerEventReset(void);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
extern void ScalerHdmiFrlMacRx4HdmiSpdInfoPacketDetect(bit bWait);
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
extern void ScalerHdmiFrlMacRx4AdvancedHdr10DetectEvent(void);
#endif

#if(_DM_FUNCTION == _ON)
extern void ScalerHdmiFrlMacRx4HdmiDmDetectEvent(void);
#endif
extern BYTE ScalerHdmiFrlMacRx4GetAVIInfo(EnumAviInfoContent enumContent);
extern BYTE ScalerHdmiFrlMacRx4Rsv6GetAviInfo(EnumAviInfoContent enumContent);
extern EnumContentType ScalerHdmiFrlMacRx4GetAviContentType(void);
extern void ScalerHdmiFrlMacRx4ResetProc(void);
extern void ScalerHdmiFrlMacRx4PowerSavingProc(void);
extern void ScalerHdmiFrlMacRx4PowerOffProc(void);
extern bit ScalerHdmiFrlMacRx4EnterPowerSavingCheck(void);
extern void ScalerHdmiFrlMacRx4ClrFltReady(void);
extern void ScalerHdmiFrlMacRx4SaveScdcStatus(void);
extern void ScalerHdmiFrlMacRx4RestoreScdcStatus(void);
extern EnumHdmiFrlMacRxDpfPixelMode ScalerHdmiFrlMacRx4GetDpfPixelMode(void);
extern bit ScalerHdmiFrlMacRx4InterlaceModeCheck(void);
extern bit ScalerHdmiFrlMacRx4PSPreDetect(void);
extern void ScalerHdmiFrlMacRx4LinkTrainingDisable(void);

#if(_HDMI_HDR10_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4GetHDR10Data(BYTE *pucHDRData);
#endif

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4GetFreeSyncIIData(BYTE *pucFreeSyncIIData);
#endif


#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
extern DWORD ScalerHdmiFrlMacRx4FreeSyncHDMIGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
extern void ScalerHdmiFrlMacRx4EmpDetectEvent(void);
#endif

extern void ScalerHdmiFrlMacRx4HighPriorityIntHandler_EXINT0(void);
extern void ScalerHdmiFrlMacRx4LowPriorityIntHandler_EXINT0(void);
extern WORD ScalerHdmiFrlMacRx4OffMeasureClk_EXINT0(BYTE ucMeasureClk);
extern void ScalerHdmiFrlMacRx4PSHighPriorityIntHandler_EXINT0(void);
extern void ScalerHdmiFrlMacRx4PSLowPriorityIntHandler_EXINT0(void);

#if(_DM_FUNCTION == _ON)
extern bit ScalerHdmiFrlMacRx4GetDMDramReceived_EXINT0(void);
extern void ScalerHdmiFrlMacRx4DMPacketReCheck_EXINT0(void);
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4GetTimingInfo(StructDscTimingInfo *pstDscTimingInfo);
#if(_HDMI_DSC_DEC_FAIL_NOTIFY == _ON)
extern void ScalerHdmiFrlMacRx4SetDscDecodeFailStatus(void);
#endif
#endif

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4SignalDetectEvent(void);
#endif

extern void ScalerHdmiFrlMacRx4IrqBackupBeforeZ0Off(void);
extern void ScalerHdmiFrlMacRx4IrqRestoreAfterZ0On(void);
extern void ScalerHdmiFrlMacRx4DPLLOffProc(WORD usVCOFreq, WORD usPLLinClkFreq, BYTE ucOutputDiv);

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4SetAudioNCode(BYTE ucNcode);
extern void ScalerHdmiFrlMacRx4SetAudioFCode(WORD usFcode);
extern void ScalerHdmiFrlMacRx4SetAudioClampNCode(void);
#endif
#endif // End of #if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)

