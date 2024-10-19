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
// ID Code      : ScalerTmdsMacRxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_HDMI_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDMI21_FVA_SUPPORT == _ON)
#define GET_HDMI21_FVA_ENABLE()                            (g_bTmdsMacRxHdmi21FvaEnable)
#define SET_HDMI21_FVA_ENABLE(x)                           (g_bTmdsMacRxHdmi21FvaEnable = (x))

#define GET_HDMI21_FVA_IVF_INFO()                          (g_bTmdsMacRxHdmi21FvaGetIVFInfo)
#define SET_HDMI21_FVA_IVF_INFO(x)                         (g_bTmdsMacRxHdmi21FvaGetIVFInfo = (x))
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Macros of Dx HDM 5V Status
//--------------------------------------------------
#define GET_D1_HDMI_5V_STATUS()                            ((bit)(g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D1Hdmi5VStatus))
#define SET_D1_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D1Hdmi5VStatus = 1)
#define CLR_D1_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D1Hdmi5VStatus = 0)

#define GET_D2_HDMI_5V_STATUS()                            ((bit)(g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D2Hdmi5VStatus))
#define SET_D2_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D2Hdmi5VStatus = 1)
#define CLR_D2_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D2Hdmi5VStatus = 0)

#define GET_D3_HDMI_5V_STATUS()                            ((bit)(g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D3Hdmi5VStatus))
#define SET_D3_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D3Hdmi5VStatus = 1)
#define CLR_D3_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D3Hdmi5VStatus = 0)

#define GET_D4_HDMI_5V_STATUS()                            ((bit)(g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D4Hdmi5VStatus))
#define SET_D4_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D4Hdmi5VStatus = 1)
#define CLR_D4_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D4Hdmi5VStatus = 0)

#define GET_D5_HDMI_5V_STATUS()                            ((bit)(g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D5Hdmi5VStatus))
#define SET_D5_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D5Hdmi5VStatus = 1)
#define CLR_D5_HDMI_5V_STATUS()                            (g_stTmdsMacRxDpHdmiCompatible5VStatus.b1D5Hdmi5VStatus = 0)
#endif

#if(_HDMI20_SUPPORT == _ON)
#define GET_D1_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D1Hdmi5vPinDetect)
#define SET_D1_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D1Hdmi5vPinDetect = _TRUE)
#define CLR_D1_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D1Hdmi5vPinDetect = _FALSE)

#define GET_D2_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D2Hdmi5vPinDetect)
#define SET_D2_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D2Hdmi5vPinDetect = _TRUE)
#define CLR_D2_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D2Hdmi5vPinDetect = _FALSE)

#define GET_D3_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D3Hdmi5vPinDetect)
#define SET_D3_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D3Hdmi5vPinDetect = _TRUE)
#define CLR_D3_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D3Hdmi5vPinDetect = _FALSE)

#define GET_D4_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D4Hdmi5vPinDetect)
#define SET_D4_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D4Hdmi5vPinDetect = _TRUE)
#define CLR_D4_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D4Hdmi5vPinDetect = _FALSE)

#define GET_D5_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D5Hdmi5vPinDetect)
#define SET_D5_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D5Hdmi5vPinDetect = _TRUE)
#define CLR_D5_HDMI_5V_PIN_HIGH()                          (g_stTmdsMacRx5vPinDetect.b1D5Hdmi5vPinDetect = _FALSE)

#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
#define GET_D12_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D12Hdmi5vPinDetect)
#define SET_D12_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D12Hdmi5vPinDetect = _TRUE)
#define CLR_D12_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D12Hdmi5vPinDetect = _FALSE)
#endif

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
#define GET_D13_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D13Hdmi5vPinDetect)
#define SET_D13_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D13Hdmi5vPinDetect = _TRUE)
#define CLR_D13_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D13Hdmi5vPinDetect = _FALSE)
#endif

#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
#define GET_D14_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D14Hdmi5vPinDetect)
#define SET_D14_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D14Hdmi5vPinDetect = _TRUE)
#define CLR_D14_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D14Hdmi5vPinDetect = _FALSE)
#endif

#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
#define GET_D15_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D15Hdmi5vPinDetect)
#define SET_D15_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D15Hdmi5vPinDetect = _TRUE)
#define CLR_D15_HDMI_5V_PIN_HIGH()                         (g_stTmdsMacRx5vPinDetect.b1D15Hdmi5vPinDetect = _FALSE)
#endif
#endif

#if(_HDMI_ON_POWER_CONTROL == _ON)
//--------------------------------------------------
// Macros of On power control by cable detect
//--------------------------------------------------
#define GET_TMDS_MAC_RX_ON_POWER_SWITCH_ON()               (g_enumTmdsMacRxOnPowerSwitchOn)
#define SET_TMDS_MAC_RX_ON_POWER_SWITCH_ON()               (g_enumTmdsMacRxOnPowerSwitchOn = _POWER_SWITCH_ON)
#define CLR_TMDS_MAC_RX_ON_POWER_SWITCH_ON()               (g_enumTmdsMacRxOnPowerSwitchOn = _POWER_SWITCH_OFF)
#endif

//--------------------------------------------------
// Macro of Scaler Rx HPD Toggle Reset ARC Tx Event
//--------------------------------------------------
#if(_AUDIO_ARC_SUPPORT == _ON)
#define GET_TMDS_MAC_RX_HPD_TOGGLE_RESET_ARC_TX_EVENT()    (g_ucTmdsMacRxHpdToggleResetArcTxEvent)
#define SET_TMDS_MAC_RX_HPD_TOGGLE_RESET_ARC_TX_EVENT()    (g_ucTmdsMacRxHpdToggleResetArcTxEvent = _TRUE)
#define CLR_TMDS_MAC_RX_HPD_TOGGLE_RESET_ARC_TX_EVENT()    (g_ucTmdsMacRxHpdToggleResetArcTxEvent = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
typedef struct
{
    BYTE b1D1Hdmi5VStatus : 1;
    BYTE b1D2Hdmi5VStatus : 1;
    BYTE b1D3Hdmi5VStatus : 1;
    BYTE b1D4Hdmi5VStatus : 1;
    BYTE b1D5Hdmi5VStatus : 1;
} StructDpHdmiCompatible5VStatus;
#endif

#if(_HDMI20_SUPPORT == _ON)
typedef struct
{
    BYTE b1D1Hdmi5vPinDetect : 1;
    BYTE b1D2Hdmi5vPinDetect : 1;
    BYTE b1D3Hdmi5vPinDetect : 1;
    BYTE b1D4Hdmi5vPinDetect : 1;
    BYTE b1D5Hdmi5vPinDetect : 1;
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    BYTE b1D12Hdmi5vPinDetect : 1;
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    BYTE b1D13Hdmi5vPinDetect : 1;
#endif
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    BYTE b1D14Hdmi5vPinDetect : 1;
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    BYTE b1D15Hdmi5vPinDetect : 1;
#endif
} Struct5vPinDetect;

typedef struct
{
    BYTE ucManufactureOuiH;
    BYTE ucManufactureOuiM;
    BYTE ucManufactureOuiL;
    BYTE pucIdstring[8];
    BYTE ucHdmiHwVersion;
    BYTE ucHdmiFwVersionMajor;
    BYTE ucHdmiFwVersionMinor;
} StructScdcInfoSet;

#if(_HDMI_5V_DETECT_BY_USER == _ON)
typedef struct
{
#if(_D0_HDMI_SUPPORT == _ON)
    EnumUserHdmi5vStatus b1D05vStatusByUser : 1;
#endif
#if(_D1_HDMI_SUPPORT == _ON)
    EnumUserHdmi5vStatus b1D15vStatusByUser : 1;
#endif
#if(_D2_HDMI_SUPPORT == _ON)
    EnumUserHdmi5vStatus b1D25vStatusByUser : 1;
#endif
#if(_D3_HDMI_SUPPORT == _ON)
    EnumUserHdmi5vStatus b1D35vStatusByUser : 1;
#endif
#if(_D4_HDMI_SUPPORT == _ON)
    EnumUserHdmi5vStatus b1D45vStatusByUser : 1;
#endif
#if(_D5_HDMI_SUPPORT == _ON)
    EnumUserHdmi5vStatus b1D55vStatusByUser : 1;
#endif
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    EnumUserHdmi5vStatus b1D125vStatusByUser : 1;
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    EnumUserHdmi5vStatus b1D135vStatusByUser : 1;
#endif
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    EnumUserHdmi5vStatus b1D145vStatusByUser : 1;
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    EnumUserHdmi5vStatus b1D155vStatusByUser : 1;
#endif
} StructTMDS5vStatusByUser;
#endif
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
typedef struct
{
    WORD usEdidVrrMax;
    BYTE ucEdidVrrMin;
    BYTE b1EdidQms : 1;
    BYTE b1EdidQmsTfrMin : 1;
    BYTE b1EdidQmsTfrMax : 1;
}StructHdmi21EdidVrrCap;
#endif

//--------------------------------------------------
// Enumerations of TMDS HPD Type
//--------------------------------------------------
typedef enum
{
    _TMDS_MAC_RX_HPD_NONE,
    _TMDS_MAC_RX_HPD_NORMAL,
    _TMDS_MAC_RX_HPD_HDCP22,
    _TMDS_MAC_RX_HPD_ACER,
    _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE,
    _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH,
    _TMDS_MAC_RX_HPD_LOW,
    _TMDS_MAC_RX_HPD_HIGH_ASSERT,
    _TMDS_MAC_RX_HPD_EIZO_PS_WAKEUP,
    _TMDS_MAC_RX_HPD_ARC_EARC_INITIATE,
} EnumTMDSHpdEventType;

//--------------------------------------------------
// Enumerations of DCC Busy Check Type
//--------------------------------------------------
typedef enum
{
    _DELAY_20US_TIMESCALE = 0x00,
    _DELAY_XMS_TIMESCALE,
} EnumTMDSDdcDebounceType;

//--------------------------------------------------
// Enumerations of HDMI Ver
//--------------------------------------------------
typedef enum
{
    _FROM_HDMI_TMDS_MAC = 0x00,
    _FROM_HDMI_FRL_MAC,
    _FROM_HDMI_FRL_DSC_MAC,
} EnumInputHdmiVer;

typedef struct
{
    BYTE b1Rsv0IrqBackup : 1;
    BYTE b1Rsv1IrqBackup : 1;
    BYTE b1Rsv2IrqBackup : 1;
    BYTE b1Rsv3IrqBackup : 1;
#if(_HDMI20_SUPPORT == _ON)
    BYTE b2ScdcChangeIrqBackup : 2;
    BYTE b1ReadRequestIrqBackup : 1;
#endif
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    BYTE b1Hdcp2WrDoneIrqBackup : 1;
#endif
#if(_AUDIO_SUPPORT == _ON)
    BYTE b1TmdsAudioIrqBackup : 1;
#endif
    BYTE b1HdcpAksvIrqBackup : 1;
#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    BYTE b1VsEmpIrqBackup : 1;
#endif
#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
    BYTE b1DhdrEmpIrqBackup : 1;
#endif
#if(_HDMI_FRL_SUPPORT == _ON)
    BYTE b1FrlRsv0IrqBackup : 1;
    BYTE b1FrlRsv1IrqBackup : 1;
    BYTE b1FrlRsv2IrqBackup : 1;
    BYTE b1FrlRsv3IrqBackup : 1;
    BYTE b1FrlRateIrqBackup : 1;
    BYTE b1FrlStartIrqBackup : 1;
    BYTE b1FltUpdateIrqBackup : 1;
#if(_AUDIO_SUPPORT == _ON)
    BYTE b1FrlAudioIrqBackup : 1;
#endif
#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    BYTE b1FrlVsEmpIrqBackup : 1;
#endif
#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
    BYTE b1FrlDhdrEmpIrqBackup : 1;
#endif
#endif
#if(_HDMI_CEC_SUPPORT == _ON)
    BYTE b1CecIrqBackup : 1;
#endif
} StructHdmiIrqStatus;

#if(_HDMI_ON_POWER_CONTROL == _ON)
typedef enum
{
    _POWER_SWITCH_OFF = 0x00,
    _POWER_SWITCH_ON = 0x01,
} EnumOnPowerSwitch;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HDMI21_FVA_SUPPORT == _ON)
extern bit g_bTmdsMacRxHdmi21FvaEnable;
extern bit g_bTmdsMacRxHdmi21FvaGetIVFInfo;
#endif

#if(_HDMI_ON_POWER_CONTROL == _ON)
extern EnumOnPowerSwitch g_enumTmdsMacRxOnPowerSwitchOn;
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern StructDpHdmiCompatible5VStatus g_stTmdsMacRxDpHdmiCompatible5VStatus;
#endif

#if(_HDMI20_SUPPORT == _ON)
extern Struct5vPinDetect g_stTmdsMacRx5vPinDetect;
extern StructScdcInfoSet g_stTmdsMacRxScdcInfoSet;

#if(_HDMI_5V_DETECT_BY_USER == _ON)
extern StructTMDS5vStatusByUser g_stTmdsMacRx5vStatusByUser;
#endif
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
extern BYTE g_ucTmdsMacRxHpdToggleResetArcTxEvent;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumInputHdmiVer ScalerTmdsMacRxGetHdmiVer(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxHpdToggleProc(void);
extern void ScalerTmdsMacRxHdcp14CableOutProc(EnumInputPort enumInputPort);

extern void ScalerTmdsMacRxScanInitial(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRxPSPreDetect(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRxNormalPreDetect(EnumInputPort enumInputPort);
extern EnumSourceType ScalerTmdsMacRxScanInputPort(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern void ScalerTmdsMacRxHighIntHandler_EXINT0(EnumPowerStatus enumPowerStatus);
extern void ScalerTmdsMacRxLowIntHandler_EXINT0(EnumPowerStatus enumPowerStatus);
extern void ScalerTmdsMacRxFreqDetectDisable(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxClrHPDTriggerEvent(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRxStableDetect(EnumInputPort enumInputPort, EnumSourceType enumSourceType);
extern void ScalerTmdsMacRxPhyDdcSelection(EnumInputPort enumInputPort);
extern EnumRx ScalerTmdsMacRxDxRxMapping(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxFreqDetectClkGating(EnumInputPort enumInputPort);
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
extern void ScalerTmdsMacRxHdcp2ResetProc(EnumInputPort enumInputPort);
#endif

extern void ScalerTmdsMacRxAllPortChangeHdcpCap(EnumTmdsHdcpType enumTmdsHdcpType);

#if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
extern void ScalerTmdsMacRxHDMI2HPDRRIRQEnable(EnumInputPort enumInputPort, bit bEnable);
#endif

#if(_HDMI20_SUPPORT == _ON)
extern void ScalerTmdsMacRxScrambleStatusReset(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxScrambleDetectDisable(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetScdcInfo(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxResetScdcInfo(EnumInputPort enumInputPort);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern void ScalerTmdsMacRxSetAmdAupiScdcInfo(EnumInputPort enumInputPort, bit bEnable);
extern EnumFreeSyncSupport ScalerTmdsMacRxGetFreeSyncSupport(EnumInputPort enumInputPort);
#endif

extern void ScalerTmdsMacRxHpd5vPinCheckEvent(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerTmdsMacRxHpd5vPinCheck(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxSetHpd5vPinHighFlag(EnumInputPort enumInputPort, bit bValue);
extern bit ScalerTmdsMacRxGetHpd5vPinHighFlag(EnumInputPort enumInputPort);
extern EnumUserHdmi5vStatus ScalerTmdsMacRxHpd5vPinDetect(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxAllPortScdcEnableSetting(bit bEnable);

#if(_HDMI_5V_DETECT_BY_USER == _ON)
extern EnumUserHdmi5vStatus ScalerTmdsMacRx5vPinDetectByUser(EnumInputPort enumInputPort);
#endif

#if((_AUDIO_EARC_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP))
extern void ScalerTmdsMacRxEnableHpdDetectRisingIrq(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxEnableHpdDetectFallingIrq(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxDisableHpdDetectIrq(EnumInputPort enumInputPort);
#endif
#endif

extern bit ScalerTmdsMacRxGetDigitalPort(EnumInputPort enumInputPort);

extern BYTE ScalerTmdsMacRxDdcDetect(void);

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
extern bit ScalerTmdsMacRxGet3dVideoValid(EnumInputPort enumInputPort);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern void ScalerTmdsMacRxEdidSwitch(EnumInputPort enumInputPort, EnumTMDSHpdEventType enumHpdEventType);
#endif

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
extern bit ScalerTmdsMacRxDdcCheckBusy(EnumInputPort enumInputPort, EnumTMDSDdcDebounceType enumTmdsDdcDebounceType, BYTE ucDebounceTimeScale, WORD usDebounceTimePeriod);
#endif

extern BYTE ScalerTmdsMacRxHdmiGetAVIInfo(EnumInputPort enumInputPort, EnumAviInfoContent enumContent);
extern EnumContentType ScalerTmdsMacRxHdmiGetAviContentTypeInfo(EnumInputPort enumInputPort);

#if(_HDMI_IDENTIFY_GAME_SRC_SUPPORT == _ON)
extern StructHdmiSpdInfo ScalerTmdsMacRxHdmiGetSpdInfo(EnumInputPort enumInputPort);
#endif

#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
extern bit ScalerTmdsMacRxGetHdmi21VtemReceived(EnumInputPort enumInputPort);
#if(_HDMI21_VRR_SUPPORT == _ON)
extern void ScalerTmdsMacRxSetEdidVrrCapability(EnumInputPort enumInputPort, StructHdmi21EdidVrrCap stEdidVrrCap);
extern void ScalerTmdsMacRxClrEdidVrrCapability(EnumInputPort enumInputPort);
#endif
#if(_HDMI21_FVA_SUPPORT == _ON)
extern BYTE ScalerTmdsMacRxHdmi21GetFvaFactor(EnumInputPort enumInputPort);
extern WORD ScalerTmdsMacRxCalFvaVfreqMax(StructEdidInfo *pstCatchEdidInfo, BYTE ucFavFactor);
#endif
#endif

extern void ScalerTmdsMacRxSetPsWakeupHpdToggle(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRxGetPsWakeupHpdStatus(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxClrPsWakeupHpdStatus(EnumInputPort enumInputPort);
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
extern bit ScalerTmdsMacRxGetToggleZ0Event(EnumInputPort enumInputPort);
#endif
extern bit ScalerTmdsMacRxReactiveSearchTimeCheck(EnumInputPort enumInputPort);
extern WORD ScalerTmdsMacRxGetReactiveSearchTime(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxPowerProc(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction);

extern void ScalerTmdsMacRxMacSelection(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRxDDCSwitchCtrl(EnumInputPort enumInputPort);

#if(_HDMI20_SUPPORT == _ON)
extern BYTE ScalerTmdsMacRxGetHwVersion(void);
#endif

extern void ScalerTmdsMacRxPhyDdcMappingAlignInAcOnProc(void);
extern void ScalerTmdsMacRxDDCSwitchWhenAcOnProc(void);

#if(_HDMI_ON_POWER_CONTROL == _ON)
extern void ScalerTmdsMacRxOnPowerControlByCableDetect(void);
#endif

extern void ScalerTmdsMacRxAcOnInitial(void);
extern void ScalerTmdsMacRxSetHdmiZ0HpdType(EnumHdmiZ0HpdType enumHdmiZ0HpdType, WORD usZ0LowPeriod, WORD usZ0HpdInterval);
// extern void ScalerTmdsMacRxHdmiIrqEnable(EnumInputPort enumInputPort, bit bEnable, StructHdmiIrqStatus *pstTmdsMacIrqStatus);
extern EnumUserHdmi5vStatus ScalerTmdsMacRxHpdDetect(EnumInputPort enumInputPort);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
extern EnumInputPort ScalerTmdsMacRxExternalHdmiPortMapping(EnumInputPort enumInputPort);
#endif
#endif

