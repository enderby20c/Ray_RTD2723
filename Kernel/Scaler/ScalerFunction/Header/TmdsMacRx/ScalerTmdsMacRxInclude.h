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
// ID Code      : ScalerTmdsMacRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// meta data size
//--------------------------------------------------
#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
#define _ADVANCED_HDR10_DHDR_EMP_MD_SIZE                16 // Unit: 7Byte
#endif
#define _DM_VS_EMP_MD_SIZE                              8
#define _SBTM_VS_EMP_MD_SIZE                            1
#define _HDMI_DPC_FIFO_ERR_CHECK_SUPPORT                _ON

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
//--------------------------------------------------
// Define for VRR Packet Type
//--------------------------------------------------
#define _HDMI21_VTEM_TYPE                               0x7F
#endif

//--------------------------------------------------
// Define for EMP SRAM related
//--------------------------------------------------
#define _HDMI_EMP_SRAM_TOTAL_SIZE                       76 // Unit: 7Byte
#define _HDMI_EMP_SRAM_DHDR_SIZE                        40 // Unit: 7Byte
#define _HDMI_EMP_SRAM_VS_SIZE                          36 // Unit: 7Byte

//--------------------------------------------------
// Macro of Z0/HPD Period
//--------------------------------------------------
#define GET_HDMI_Z0_HPD_TYPE()                          (g_stTmdsMacRxHdmiZ0HpdInfo.enumHdmiZ0HpdType)
#define SET_HDMI_Z0_HPD_TYPE(x)                         (g_stTmdsMacRxHdmiZ0HpdInfo.enumHdmiZ0HpdType = (x))

#define GET_HDMI_Z0_LOW_PERIOD()                        (g_stTmdsMacRxHdmiZ0HpdInfo.usZ0LowPeriod)
#define SET_HDMI_Z0_LOW_PERIOD(x)                       (g_stTmdsMacRxHdmiZ0HpdInfo.usZ0LowPeriod = (x))

#define GET_HDMI_Z0_HPD_INTERVAL()                      (g_stTmdsMacRxHdmiZ0HpdInfo.usZ0HpdInterval)
#define SET_HDMI_Z0_HPD_INTERVAL(x)                     (g_stTmdsMacRxHdmiZ0HpdInfo.usZ0HpdInterval = (x))

//--------------------------------------------------
// Macro of RX3 Hpd Status Backup
//--------------------------------------------------
#define GET_HDMI_HPD_SWITCH_PORT_BACKUP()               (g_ucTmdsMacRxHpdSwitchPortBackup)
#define SET_HDMI_HPD_SWITCH_PORT_BACKUP(x)              (g_ucTmdsMacRxHpdSwitchPortBackup = (x))

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_NEW_MODE)
//--------------------------------------------------
// Macro of RX3 IRQ Flag
//--------------------------------------------------
#define GET_HDMI_RX3_MAC_HIGH_PRIORITY_IRQ_FLAG()       (ScalerGetBit_EXINT(P6F_1D_HDMIRX_CEC_ARC_IRQ, _BIT7) == _BIT7)
#define GET_HDMI_RX3_MAC_LOW_PRIORITY_IRQ_FLAG()        (ScalerGetBit_EXINT(P6F_1D_HDMIRX_CEC_ARC_IRQ, _BIT6) == _BIT6)
#endif
#endif // End of #if(_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Macro of HF VSIF OUI
//--------------------------------------------------
#define _HDMI_VSIF_OUI                                  0x030C00
#define _HF_VSIF_OUI                                    0xD85DC4

//--------------------------------------------------
// Macro of Panel Replay
//--------------------------------------------------
#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
#define GET_HDMI_FREESYNC_REPLAY_D0_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD0Enable)
#define SET_HDMI_FREESYNC_REPLAY_D0_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD0Enable = _ENABLE)
#define CLR_HDMI_FREESYNC_REPLAY_D0_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD0Enable = _DISABLE)

#define GET_HDMI_FREESYNC_REPLAY_D1_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD1Enable)
#define SET_HDMI_FREESYNC_REPLAY_D1_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD1Enable = _ENABLE)
#define CLR_HDMI_FREESYNC_REPLAY_D1_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD1Enable = _DISABLE)

#define GET_HDMI_FREESYNC_REPLAY_D2_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD2Enable)
#define SET_HDMI_FREESYNC_REPLAY_D2_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD2Enable = _ENABLE)
#define CLR_HDMI_FREESYNC_REPLAY_D2_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD2Enable = _DISABLE)

#define GET_HDMI_FREESYNC_REPLAY_D3_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD3Enable)
#define SET_HDMI_FREESYNC_REPLAY_D3_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD3Enable = _ENABLE)
#define CLR_HDMI_FREESYNC_REPLAY_D3_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD3Enable = _DISABLE)

#define GET_HDMI_FREESYNC_REPLAY_D4_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD4Enable)
#define SET_HDMI_FREESYNC_REPLAY_D4_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD4Enable = _ENABLE)
#define CLR_HDMI_FREESYNC_REPLAY_D4_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD4Enable = _DISABLE)

#define GET_HDMI_FREESYNC_REPLAY_D5_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD5Enable)
#define SET_HDMI_FREESYNC_REPLAY_D5_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD5Enable = _ENABLE)
#define CLR_HDMI_FREESYNC_REPLAY_D5_ENABLED()           (g_stTmdsMacRxHdmiFreesyncReplayEnableInfo.b1HdmiD5Enable = _DISABLE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
typedef struct
{
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    BYTE b1HdmiRx3PSWakeUp : 1;
#endif
#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    BYTE b1HdmiRx4PSWakeUp : 1;
#endif
} StructDpHdmiCompatibleHdmiPSWakeUp;
#endif

#if(_HDMI_SUPPORT == _ON)
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
//--------------------------------------------------
// Struct of HDMI2.1 EMP Feature
//--------------------------------------------------
typedef struct
{
    BYTE b1EmpDetecting : 1;

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    BYTE b1CvtemReceived : 1;
#endif


#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
    BYTE b1VtemReceived : 1;
    BYTE b1VtemReceiveChanged : 1;
#if(_HDMI21_VRR_SUPPORT == _ON)
    BYTE b1VrrMconst : 1;
    BYTE b1VrrReceiveChanged : 1;
    BYTE b1QmsReceiveChanged : 1;
    BYTE b1VrrEnable : 1;
    BYTE b1QmsEnable : 1;
#endif
#if(_HDMI21_FVA_SUPPORT == _ON)
    BYTE b5FvaFactor : 5;
#endif
#endif
}StructHdmi21EmpInfo;
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
typedef struct
{
    WORD usFrmPbLimitInt;
    BYTE ucSbtmVer;
    BYTE ucSbtmType;
    BYTE ucSbtmMode;
    BYTE ucSbtmGrmdLum;
    BYTE ucSbtmGrmdMin;
    BYTE b1SbtmReceive : 1;
    BYTE b1SbtmInfoReceive : 1;
}StructHdmiSbtmInfo;
#endif
#endif

#if(_HDMI_SUPPORT == _ON)
typedef struct
{
    EnumHdmiZ0HpdType enumHdmiZ0HpdType;
    WORD usZ0LowPeriod;
    WORD usZ0HpdInterval;
} StructHdmiZ0HpdInfo;
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
typedef struct
{
    BYTE b1HdmiD0Enable : 1;
    BYTE b1HdmiD1Enable : 1;
    BYTE b1HdmiD2Enable : 1;
    BYTE b1HdmiD3Enable : 1;
    BYTE b1HdmiD4Enable : 1;
    BYTE b1HdmiD5Enable : 1;
} StructHdmiFreesyncReplayEnableInfo;
#endif

//--------------------------------------------------
// Enumerations of AVI Quantization
//--------------------------------------------------
typedef enum
{
    _AVI_RGB_QUANTIZATION_DEFAULT = 0x00,
    _AVI_RGB_QUANTIZATION_LIMITED = 0x01,
    _AVI_RGB_QUANTIZATION_FULL = 0x02,
    _AVI_RGB_QUANTIZATION_RESERVED = 0x03,
} EnumAviInfoRGBQuantization;

typedef enum
{
    _AVI_YCC_QUANTIZATION_LIMITED = 0x00,
    _AVI_YCC_QUANTIZATION_FULL = 0x01,
} EnumAviInfoYCCQuantization;

//--------------------------------------------------
// Enumerations of AVI Pixel Repetition
//--------------------------------------------------
typedef enum
{
    _AVI_PIXEL_REPETITION_0 = 0x00,
    _AVI_PIXEL_REPETITION_1 = 0x01,
    _AVI_PIXEL_REPETITION_2 = 0x02,
    _AVI_PIXEL_REPETITION_3 = 0x03,
    _AVI_PIXEL_REPETITION_4 = 0x04,
    _AVI_PIXEL_REPETITION_5 = 0x05,
    _AVI_PIXEL_REPETITION_6 = 0x06,
    _AVI_PIXEL_REPETITION_7 = 0x07,
    _AVI_PIXEL_REPETITION_8 = 0x08,
    _AVI_PIXEL_REPETITION_9 = 0x09,
} EnumAviInfoPixelRepetition;

//--------------------------------------------------
// Enumerations of HDMI RSV number
//--------------------------------------------------
typedef enum
{
    _HDMI_RSV_0 = 0x00,
    _HDMI_RSV_1 = 0x01,
    _HDMI_RSV_2 = 0x02,
    _HDMI_RSV_3 = 0x03,
    _HDMI_RSV_4 = 0x04,
    _HDMI_RSV_5 = 0x05,
    _HDMI_RSV_6 = 0x06,
    _HDMI_RSV_7 = 0x07,
} EnumHdmiRsvNumber;

//--------------------------------------------------
// Enumerations of TMDS DE-ONLY Mode Config
//--------------------------------------------------
typedef enum
{
    _DE_NO_INDICATED = 0x00,
    _DE_ONLY_DISABLE = _BIT0,
    _DE_ONLY_ENABLE = _BIT1,
    _DE_ONLY_HS_8T = _BIT2,
    _DE_ONLY_HS_72T = _BIT3,
} EnumDeOnlyConfig;

//--------------------------------------------------
// Enumerations of EMP Type
//--------------------------------------------------
typedef enum
{
    _NONE_EMP = 0x00,
    _DM_VSEMP,
    _DHDR_EMP,
} EnumHdmiEmpType;

//--------------------------------------------------
// Enumerations of EMP Vs Org ID
//--------------------------------------------------
typedef enum
{
    _VENDOR_SPECIFIC = 0x00,
    _HDMI21,
    _CTA_681_G,
    _VESA,
} EnumHdmiEmpVsOrgID;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern StructDpHdmiCompatibleHdmiPSWakeUp g_stTmdsMacRxDpHdmiCompatibleHdmiPsWakeup;
#endif

extern StructHdmiZ0HpdInfo g_stTmdsMacRxHdmiZ0HpdInfo;
extern BYTE g_ucTmdsMacRxHpdSwitchPortBackup;
#endif

//***************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
extern void ScalerTmdsMacRxHdmiAVMuteProc(EnumInputPort enumInputPort);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
extern void ScalerTmdsMacRxNoClkWatchDogProc(EnumInputPort enumInputPort);
#endif

extern void ScalerTmdsMacRxHotPlugEvent(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxFirstActiveProc(EnumInputPort enumInputPort, EnumSourceType enumSourceType);
extern bit ScalerTmdsMacRxHdcpEnabled(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxHdcpFlagClear(EnumInputPort enumInputPort);

extern void ScalerTmdsMacRxSetInputPixel(EnumInputPort enumInputPort, WORD usPixel);
extern void ScalerTmdsMacRxSetInputPixel_EXINT0(EnumInputPort enumInputPort, WORD usPixel);
extern WORD ScalerTmdsMacRxGetInputPixel(EnumInputPort enumInputPort);
extern WORD ScalerTmdsMacRxGetInputPixel_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetDxHPD(EnumInputPort enumInputPort, BYTE ucValue);
extern bit ScalerTmdsMacRxGetCableStatus(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetDigitalPort(EnumInputPort enumInputPort, BYTE ucHL);

extern void ScalerTmdsMacRxResetMacInput_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetDeOnlyModeConfig(EnumInputPort enumInputPort, EnumDeOnlyConfig enumDeonlyConfig);
extern EnumDeOnlyConfig ScalerTmdsMacRxGetDeOnlyModeConfig(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxForceBckgrdPath(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion);
extern void ScalerTmdsMacRxClrForceBckgrdPath(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion);
extern void ScalerTmdsMacRxHVPolarityReset(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxInterlaceCheckPreset(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetZ0Asserted(EnumInputPort enumInputPort);

extern WORD ScalerTmdsMacRxOnMeasureClk_EXINT0(EnumInputPort enumInputPort, BYTE ucLane);
extern BYTE ScalerTmdsMacRxSaveOnMeasureSettings_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxRestoreOnMeasureSettings_EXINT0(EnumInputPort enumInputPort, BYTE ucStableTimes);

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern void ScalerTmdsMacRxDigitalClrColorimetryChanged(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxDigitalClrColorimetryExtChanged(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxDigitalClrQuantizationChanged(EnumInputPort enumInputPort);
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern void ScalerTmdsMacRxClrPSWakeupFlag(EnumInputPort enumInputPort);
#endif

extern void ScalerTmdsMacRxPowerSavingProc(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxPowerOffProc(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetHPDTriggerEvent(EnumInputPort enumInputPort, EnumTMDSHpdEventType enumHpdEvent);
extern EnumTMDSHpdEventType ScalerTmdsMacRxGetHPDTriggerEvent(EnumInputPort enumInputPort);

extern EnumInputPort ScalerTmdsMacRxRxDxMapping_EXINT0(EnumRx enumRx);
extern EnumInputPort ScalerTmdsMacRxRxDxMapping(EnumRx enumRx);
extern void ScalerTmdsMacRxTimerEventReset(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSwitchHdcpSlaveAddr(EnumInputPort enumInputPort);

#if((_HDMI_HDR10_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
extern bit ScalerTmdsMacRxHDR10Status(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxGetHDR10Data(EnumInputPort enumInputPort, BYTE *pucHDRData);
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
extern bit ScalerTmdsMacRxHDR10SBTMStatus(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxGetHDR10SBTMData(EnumInputPort enumInputPort, BYTE *pucSBTMData);
#endif

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
extern bit ScalerTmdsMacRxGetSdpInfoFrameReceivedFlag(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxGetFreeSync2Data(EnumInputPort enumInputPort, BYTE *pucFreeSync2Data);
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern DWORD ScalerTmdsMacRxFreeSyncHDMIGetAmdSpdInfo(EnumInputPort enumInputPort, EnumAmdSpdInfoContent enumContent);
extern void ScalerTmdsMacRxSetFreesyncProc(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerTmdsMacRxGetFreesyncEnableFlag(EnumInputPort enumInputPort);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
extern bit ScalerTmdsMacRxHdcpMode(EnumInputPort enumInputPort);
#endif

extern EnumRx ScalerTmdsMacRxDxRxMapping_EXINT0(EnumInputPort enumInputPort);

#if(_DM_FUNCTION == _ON)
extern bit ScalerTmdsMacRxGetOsdDmSupport(EnumInputPort enumInputPort);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern bit ScalerTmdsMacRxGetHdmi21AllmStatus(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxClrHdmi21AllmStatus(EnumInputPort enumInputPort);
#if(_DM_FUNCTION == _ON)
extern void ScalerTmdsMacRxSetDmAllmStatus(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxClrDmAllmStatus(EnumInputPort enumInputPort);
#endif
#endif

#if(_HDMI20_SUPPORT == _ON)
extern void ScalerTmdsMacRxHdmiReadRequestTimerEnable_WDINT(void);
extern BYTE ScalerTmdsMacRxGetHighSpeedMode_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetScdcInfo_EXINT0(EnumInputPort enumInputPort);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern void ScalerTmdsMacRxSetAmdAupiScdcInfo_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern EnumFreeSyncSupport ScalerTmdsMacRxGetFreeSyncSupport_EXINT0(EnumInputPort enumInputPort);
#endif
#endif

#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
extern void ScalerTmdsMacRxHdmiUnstableBedCheck_WDINT(EnumRx enumRx);
#endif

extern void ScalerTmdsMacRxBackupHdcpType(EnumInputPort enumInputPort);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
extern void ScalerTmdsMacRxWaitSclStatusIntoIdle_EXINT0(EnumInputPort enumInputPort);
#endif

#if(_DM_FUNCTION == _ON)
#if(_HDMI21_ALLM_SUPPORT == _ON)
extern bit ScalerTmdsMacRxGetDmAllmStatus_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetDmAllmStatus_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxClrDmAllmStatus_EXINT0(EnumInputPort enumInputPort);
#endif
extern bit ScalerTmdsMacRxGetDMDramReceived_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxDMPacketReCheck_EXINT0(EnumInputPort enumInputPort);
#endif

#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
#if(_HDMI21_VRR_SUPPORT == _ON)
extern bit ScalerTmdsMacRxGetHdmi21VrrStatus(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRxGetVrrEnStatus(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRxGetQmsEnStatus(EnumInputPort enumInputPort);
#endif
extern void ScalerTmdsMacRxClrHdmi21VtemReceived(EnumInputPort enumInputPort);
#endif

extern BYTE ScalerTmdsMacRxGetVicVfreqParameter(BYTE ucVicIndex);
extern WORD ScalerTmdsMacRxGetOvtVfreqParameter(BYTE ucFrIndex);
extern void ScalerTmdsMacRxBRSwap(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRxCheckPNSwap(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxPNSwap(EnumInputPort enumInputPort);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
extern void ScalerTmdsMacRxSetInterfaceSwitching(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRxGetInterfaceSwitching(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxClrInterfaceSwitching(EnumInputPort enumInputPort);
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
extern void ScalerTmdsMacRxSetFreesyncReplayProc(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerTmdsMacRxGetFreesyncReplayProc(EnumInputPort enumInputPort);
#endif

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
extern bit ScalerTmdsMacRxGetAcOnHpdToggleEvent(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxClrAcOnHpdToggleEvent(EnumInputPort enumInputPort);
#endif

#if(_HW_HDMI_SCDC_RESET == _ON)
extern void ScalerTmdsMacRxHwScdcReset(void);
#endif

#if(_AUDIO_SUPPORT == _ON)
extern void ScalerTmdsMacRxSetAudioNfCode_EXINT0(EnumRx enumMacRxIndex);
#endif

extern void ScalerTmdsMacRxPhyDrcrFifoReset_EXINT0(EnumInputPort enumInputPort);
#endif // End of #if(_HDMI_SUPPORT == _ON)

