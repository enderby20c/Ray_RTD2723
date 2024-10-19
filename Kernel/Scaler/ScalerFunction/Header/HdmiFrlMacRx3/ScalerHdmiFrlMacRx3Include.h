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
// ID Code      : ScalerHdmiFrlMacRx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// HDMI FRL RX3 Option
//--------------------------------------------------
#define _HDMI_FRL_MAC_RX3_LFSR_TEST_MODE                        _OFF
#define _HDMI_FRL_MAC_RX3_LINK_TRAINING_BYPASS                  _OFF

//--------------------------------------------------
// Macro of Link Training State
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE()              (g_stHdmiFrlMacRx3CtrlInfo.b4LtState)
#define SET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE(x)             (g_stHdmiFrlMacRx3CtrlInfo.b4LtState = (x))

//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_PHY_SET()                          (g_stHdmiFrlMacRx3CtrlInfo.b1FrlPhySet)
#define SET_HDMI_FRL_MAC_RX3_PHY_SET()                          (g_stHdmiFrlMacRx3CtrlInfo.b1FrlPhySet = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_PHY_SET()                          (g_stHdmiFrlMacRx3CtrlInfo.b1FrlPhySet = _FALSE)

//--------------------------------------------------
// Macro of Add Reactive Time after Link Training Pass
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_REACTIVE_SEARCH_TIME()             (g_stHdmiFrlMacRx3CtrlInfo.b1ReactiveSearchTime)
#define SET_HDMI_FRL_MAC_RX3_REACTIVE_SEARCH_TIME()             (g_stHdmiFrlMacRx3CtrlInfo.b1ReactiveSearchTime = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_REACTIVE_SEARCH_TIME()             (g_stHdmiFrlMacRx3CtrlInfo.b1ReactiveSearchTime = _FALSE)

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// DSC H/V Timing
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_CVTEM_HFRONT()                     ((ScalerGetByte(P67_81_DSC_HINFO_1) << 8) | ScalerGetByte(P67_80_DSC_HINFO_0))
#define GET_HDMI_FRL_MAC_RX3_CVTEM_HSYNC()                      ((ScalerGetByte(P67_83_DSC_HINFO_3) << 8) | ScalerGetByte(P67_82_DSC_HINFO_2))
#define GET_HDMI_FRL_MAC_RX3_CVTEM_HBACK()                      ((ScalerGetByte(P67_85_DSC_HIFO_5) << 8) | ScalerGetByte(P67_84_DSC_HINFO_4))
#define GET_HDMI_FRL_MAC_RX3_CVTEM_HCACTIVE_BYTES()             ((ScalerGetByte(P67_87_DSC_HINO_7) << 8) | ScalerGetByte(P67_86_DSC_HINFO_6))

// 0 is positive, 1 is negative
#define GET_HDMI_FRL_MAC_RX3_VSYNC_POLARITY()                   (ScalerGetBit(P68_26_HDMI21_DI_0, _BIT4) >> 4)
#endif

#define GET_HDMI_FRL_MAC_RX3_VFRONT()                           (g_usHdmiFrlMacRx3Vfront)
#define GET_HDMI_FRL_MAC_RX3_VSYNC()                            (g_usHdmiFrlMacRx3Vsync)
#define GET_HDMI_FRL_MAC_RX3_VBACK()                            (g_usHdmiFrlMacRx3Vback)
#define GET_HDMI_FRL_MAC_RX3_VACTIVE()                          (g_usHdmiFrlMacRx3Vactive)
#define GET_HDMI_FRL_MAC_RX3_VTOTAL()                           (g_usHdmiFrlMacRx3Vtotal)

//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION()             (g_ucHdmiFrlMacRx3AviInfo)

//--------------------------------------------------
// Macro of Native Htotal for EDID Table Analysis
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_NATIVE_HTOTAL()                    (g_usHdmiFrlMacRx3NativeHtotal)
#define SET_HDMI_FRL_MAC_RX3_NATIVE_HTOTAL(x)                   (g_usHdmiFrlMacRx3NativeHtotal = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructHdmiFrlCtrlInfo g_stHdmiFrlMacRx3CtrlInfo;

extern WORD g_usHdmiFrlMacRx3Hfront;
extern WORD g_usHdmiFrlMacRx3Hsync;
extern WORD g_usHdmiFrlMacRx3Hback;
extern WORD g_usHdmiFrlMacRx3Hactive;
extern WORD g_usHdmiFrlMacRx3Htotal;
extern WORD g_usHdmiFrlMacRx3Vfront;
extern WORD g_usHdmiFrlMacRx3Vsync;
extern WORD g_usHdmiFrlMacRx3Vback;
extern WORD g_usHdmiFrlMacRx3Vactive;
extern WORD g_usHdmiFrlMacRx3Vtotal;
extern BYTE g_ucHdmiFrlMacRx3AviInfo;

extern DWORD g_ulHdmiFrlMacRx3PixelClkValue;

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern DWORD g_ulHdmiFrlMacRx3DSCClkValue;
#endif

extern WORD g_usHdmiFrlMacRx3NativeHtotal;

extern BYTE g_ucHdmiFrlMacRx3ScdcStatusFlag;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdmiFrlMacRx3ScanInitial(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRx3RoundRobinIrqEnable(bit bEnable);
extern bit ScalerHdmiFrlMacRx3NormalPreDetect(void);
extern void ScalerHdmiFrlMacRx3FirstActiveProc(EnumSourceType enumSourceType);
extern void ScalerHdmiFrlMacRx3HdmiAVMuteProc(void);
extern EnumSourceType ScalerHdmiFrlMacRx3ScanInputPort(EnumPortType enumPortType);
extern bit ScalerHdmiFrlMacRx3StableDetect(EnumSourceType enumSourceType);
extern WORD ScalerHdmiFrlMacRx3OffMeasureClk(BYTE ucMeasureClk);
extern void ScalerHdmiFrlMacRx3PacketDetectEvent(void);
extern void ScalerHdmiFrlMacRx3TimerEventReset(void);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
extern void ScalerHdmiFrlMacRx3HdmiSpdInfoPacketDetect(bit bWait);
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
extern void ScalerHdmiFrlMacRx3AdvancedHdr10DetectEvent(void);
#endif

#if(_DM_FUNCTION == _ON)
extern void ScalerHdmiFrlMacRx3HdmiDmDetectEvent(void);
#endif
extern BYTE ScalerHdmiFrlMacRx3GetAVIInfo(EnumAviInfoContent enumContent);
extern BYTE ScalerHdmiFrlMacRx3Rsv6GetAviInfo(EnumAviInfoContent enumContent);
extern EnumContentType ScalerHdmiFrlMacRx3GetAviContentType(void);
extern void ScalerHdmiFrlMacRx3ResetProc(void);
extern void ScalerHdmiFrlMacRx3PowerSavingProc(void);
extern void ScalerHdmiFrlMacRx3PowerOffProc(void);
extern bit ScalerHdmiFrlMacRx3EnterPowerSavingCheck(void);
extern void ScalerHdmiFrlMacRx3ClrFltReady(void);
extern void ScalerHdmiFrlMacRx3SaveScdcStatus(void);
extern void ScalerHdmiFrlMacRx3RestoreScdcStatus(void);
extern EnumHdmiFrlMacRxDpfPixelMode ScalerHdmiFrlMacRx3GetDpfPixelMode(void);
extern bit ScalerHdmiFrlMacRx3InterlaceModeCheck(void);
extern bit ScalerHdmiFrlMacRx3PSPreDetect(void);
extern void ScalerHdmiFrlMacRx3LinkTrainingDisable(void);

#if(_HDMI_HDR10_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3GetHDR10Data(BYTE *pucHDRData);
#endif

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3GetFreeSyncIIData(BYTE *pucFreeSyncIIData);
#endif


#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
extern DWORD ScalerHdmiFrlMacRx3FreeSyncHDMIGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
extern void ScalerHdmiFrlMacRx3EmpDetectEvent(void);
#endif

extern void ScalerHdmiFrlMacRx3HighPriorityIntHandler_EXINT0(void);
extern void ScalerHdmiFrlMacRx3LowPriorityIntHandler_EXINT0(void);
extern WORD ScalerHdmiFrlMacRx3OffMeasureClk_EXINT0(BYTE ucMeasureClk);
extern void ScalerHdmiFrlMacRx3PSHighPriorityIntHandler_EXINT0(void);
extern void ScalerHdmiFrlMacRx3PSLowPriorityIntHandler_EXINT0(void);

#if(_DM_FUNCTION == _ON)
extern bit ScalerHdmiFrlMacRx3GetDMDramReceived_EXINT0(void);
extern void ScalerHdmiFrlMacRx3DMPacketReCheck_EXINT0(void);
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3GetTimingInfo(StructDscTimingInfo *pstDscTimingInfo);
#if(_HDMI_DSC_DEC_FAIL_NOTIFY == _ON)
extern void ScalerHdmiFrlMacRx3SetDscDecodeFailStatus(void);
#endif
#endif

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3SignalDetectEvent(void);
#endif

extern void ScalerHdmiFrlMacRx3IrqBackupBeforeZ0Off(void);
extern void ScalerHdmiFrlMacRx3IrqRestoreAfterZ0On(void);
extern void ScalerHdmiFrlMacRx3DPLLOffProc(WORD usVCOFreq, WORD usPLLinClkFreq, BYTE ucOutputDiv);

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3SetAudioNCode(BYTE ucNcode);
extern void ScalerHdmiFrlMacRx3SetAudioFCode(WORD usFcode);
extern void ScalerHdmiFrlMacRx3SetAudioClampNCode(void);
#endif
#endif // End of #if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
