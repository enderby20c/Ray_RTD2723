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
// ID Code      : ScalerDrrInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if(_DRR_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DRR Panel Vfreq MAX/MIN info
//--------------------------------------------------
#define GET_DRR_PANEL_MAX_FRAME_RATE()                      (g_usDrrPanelVFreqMax)
#define SET_DRR_PANEL_MAX_FRAME_RATE(x)                     (g_usDrrPanelVFreqMax = (x))
#define GET_DRR_PANEL_MIN_FRAME_RATE()                      (g_usDrrPanelVFreqMin)
#define SET_DRR_PANEL_MIN_FRAME_RATE(x)                     (g_usDrrPanelVFreqMin = (x))

//--------------------------------------------------
// Definitions of Drr info
//--------------------------------------------------
#define GET_DRR_IVF_INFO()                                  (g_bDrrGetIVFInfo)
#define SET_DRR_IVF_INFO(x)                                 (g_bDrrGetIVFInfo = (x))

#define GET_DRR_VFREQ_MAX()                                 (g_ulDrrVFreqMax)
#define SET_DRR_VFREQ_MAX(x)                                (g_ulDrrVFreqMax = (x))

#define GET_DRR_VFREQ_MIN()                                 (g_ulDrrVFreqMin)
#define SET_DRR_VFREQ_MIN(x)                                (g_ulDrrVFreqMin = (x))
#endif

//--------------------------------------------------
// Definitions of AdaptiveSync DP info
//--------------------------------------------------
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#define GET_ADAPTIVESYNC_DP_D0_SUPPORT()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD0Support)
#define SET_ADAPTIVESYNC_DP_D0_SUPPORT(x)                   (g_stDrrDpAdaptiveSyncInfo.b1DpD0Support = (x))

#define GET_ADAPTIVESYNC_DP_D1_SUPPORT()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD1Support)
#define SET_ADAPTIVESYNC_DP_D1_SUPPORT(x)                   (g_stDrrDpAdaptiveSyncInfo.b1DpD1Support = (x))

#define GET_ADAPTIVESYNC_DP_D2_SUPPORT()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD2Support)
#define SET_ADAPTIVESYNC_DP_D2_SUPPORT(x)                   (g_stDrrDpAdaptiveSyncInfo.b1DpD2Support = (x))

#define GET_ADAPTIVESYNC_DP_ENABLED()                       ((bit)(GET_ADAPTIVESYNC_DP_D0_ENABLED() || GET_ADAPTIVESYNC_DP_D1_ENABLED() || GET_ADAPTIVESYNC_DP_D2_ENABLED()))
#define CLR_ADAPTIVESYNC_DP_ENABLED()                       {\
                                                                CLR_ADAPTIVESYNC_DP_D0_ENABLED();\
                                                                CLR_ADAPTIVESYNC_DP_D1_ENABLED();\
                                                                CLR_ADAPTIVESYNC_DP_D2_ENABLED();\
                                                            }

#define GET_ADAPTIVESYNC_DP_D0_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD0Enable)
#define SET_ADAPTIVESYNC_DP_D0_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD0Enable = _ENABLE)
#define CLR_ADAPTIVESYNC_DP_D0_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD0Enable = _DISABLE)

#define GET_ADAPTIVESYNC_DP_D1_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD1Enable)
#define SET_ADAPTIVESYNC_DP_D1_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD1Enable = _ENABLE)
#define CLR_ADAPTIVESYNC_DP_D1_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD1Enable = _DISABLE)

#define GET_ADAPTIVESYNC_DP_D2_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD2Enable)
#define SET_ADAPTIVESYNC_DP_D2_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD2Enable = _ENABLE)
#define CLR_ADAPTIVESYNC_DP_D2_ENABLED()                    (g_stDrrDpAdaptiveSyncInfo.b1DpD2Enable = _DISABLE)
#endif // End of #if(_DP_ADAPTIVESYNC_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of FreeSync DP info
//--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_DP_D0_SUPPORT()                        (g_stDrrFreeSyncDpInfo.b1DpD0Support)
#define SET_FREESYNC_DP_D0_SUPPORT(x)                       (g_stDrrFreeSyncDpInfo.b1DpD0Support = (x))

#define GET_FREESYNC_DP_D1_SUPPORT()                        (g_stDrrFreeSyncDpInfo.b1DpD1Support)
#define SET_FREESYNC_DP_D1_SUPPORT(x)                       (g_stDrrFreeSyncDpInfo.b1DpD1Support = (x))

#define GET_FREESYNC_DP_D2_SUPPORT()                        (g_stDrrFreeSyncDpInfo.b1DpD2Support)
#define SET_FREESYNC_DP_D2_SUPPORT(x)                       (g_stDrrFreeSyncDpInfo.b1DpD2Support = (x))

#define GET_FREESYNC_DP_D0_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD0Enable)
#define SET_FREESYNC_DP_D0_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD0Enable = _ENABLE)
#define CLR_FREESYNC_DP_D0_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD0Enable = _DISABLE)

#define GET_FREESYNC_DP_D1_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD1Enable)
#define SET_FREESYNC_DP_D1_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD1Enable = _ENABLE)
#define CLR_FREESYNC_DP_D1_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD1Enable = _DISABLE)

#define GET_FREESYNC_DP_D2_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD2Enable)
#define SET_FREESYNC_DP_D2_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD2Enable = _ENABLE)
#define CLR_FREESYNC_DP_D2_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD2Enable = _DISABLE)

#define GET_FREESYNC_DP_D9_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD9Enable)
#define SET_FREESYNC_DP_D9_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD9Enable = _ENABLE)
#define CLR_FREESYNC_DP_D9_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpD9Enable = _DISABLE)

#define GET_FREESYNC_DP_AUPI_INFO()                         (g_stDrrFreeSyncDpInfo.b1DpRxGetAupiInfo)
#define SET_FREESYNC_DP_AUPI_INFO()                         (g_stDrrFreeSyncDpInfo.b1DpRxGetAupiInfo = _ENABLE)
#define CLR_FREESYNC_DP_AUPI_INFO()                         (g_stDrrFreeSyncDpInfo.b1DpRxGetAupiInfo = _DISABLE)
#endif // End of #if(_DP_FREESYNC_SUPPORT == _ON)

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
#define GET_FREESYNC_SUPPORT_TMDS_D0()                      (g_stDrrFreeSyncHdmiInfo.enumHdmiD0Support)
#define SET_FREESYNC_SUPPORT_TMDS_D0(x)                     (g_stDrrFreeSyncHdmiInfo.enumHdmiD0Support = (x))

#define GET_FREESYNC_SUPPORT_TMDS_D1()                      (g_stDrrFreeSyncHdmiInfo.enumHdmiD1Support)
#define SET_FREESYNC_SUPPORT_TMDS_D1(x)                     (g_stDrrFreeSyncHdmiInfo.enumHdmiD1Support = (x))

#define GET_FREESYNC_SUPPORT_TMDS_D2()                      (g_stDrrFreeSyncHdmiInfo.enumHdmiD2Support)
#define SET_FREESYNC_SUPPORT_TMDS_D2(x)                     (g_stDrrFreeSyncHdmiInfo.enumHdmiD2Support = (x))

#define GET_FREESYNC_SUPPORT_TMDS_D3()                      (g_stDrrFreeSyncHdmiInfo.enumHdmiD3Support)
#define SET_FREESYNC_SUPPORT_TMDS_D3(x)                     (g_stDrrFreeSyncHdmiInfo.enumHdmiD3Support = (x))

#define GET_FREESYNC_SUPPORT_TMDS_D4()                      (g_stDrrFreeSyncHdmiInfo.enumHdmiD4Support)
#define SET_FREESYNC_SUPPORT_TMDS_D4(x)                     (g_stDrrFreeSyncHdmiInfo.enumHdmiD4Support = (x))

#define GET_FREESYNC_SUPPORT_TMDS_D5()                      (g_stDrrFreeSyncHdmiInfo.enumHdmiD5Support)
#define SET_FREESYNC_SUPPORT_TMDS_D5(x)                     (g_stDrrFreeSyncHdmiInfo.enumHdmiD5Support = (x))
#endif // End of #if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_HDMI_D0_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD0Enable)
#define SET_FREESYNC_HDMI_D0_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD0Enable = _ENABLE)
#define CLR_FREESYNC_HDMI_D0_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD0Enable = _DISABLE)

#define GET_FREESYNC_HDMI_D1_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD1Enable)
#define SET_FREESYNC_HDMI_D1_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD1Enable = _ENABLE)
#define CLR_FREESYNC_HDMI_D1_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD1Enable = _DISABLE)

#define GET_FREESYNC_HDMI_D2_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD2Enable)
#define SET_FREESYNC_HDMI_D2_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD2Enable = _ENABLE)
#define CLR_FREESYNC_HDMI_D2_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD2Enable = _DISABLE)

#define GET_FREESYNC_HDMI_D3_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD3Enable)
#define SET_FREESYNC_HDMI_D3_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD3Enable = _ENABLE)
#define CLR_FREESYNC_HDMI_D3_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD3Enable = _DISABLE)

#define GET_FREESYNC_HDMI_D4_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD4Enable)
#define SET_FREESYNC_HDMI_D4_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD4Enable = _ENABLE)
#define CLR_FREESYNC_HDMI_D4_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD4Enable = _DISABLE)

#define GET_FREESYNC_HDMI_D5_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD5Enable)
#define SET_FREESYNC_HDMI_D5_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD5Enable = _ENABLE)
#define CLR_FREESYNC_HDMI_D5_ENABLED()                      (g_stDrrFreeSyncHdmiInfo.b1HdmiD5Enable = _DISABLE)

#define GET_FREESYNC_HDMI_AUPI_INFO()                       (g_stDrrFreeSyncHdmiInfo.b1HdmiRxGetAupiInfo)
#define SET_FREESYNC_HDMI_AUPI_INFO()                       (g_stDrrFreeSyncHdmiInfo.b1HdmiRxGetAupiInfo = _ENABLE)
#define CLR_FREESYNC_HDMI_AUPI_INFO()                       (g_stDrrFreeSyncHdmiInfo.b1HdmiRxGetAupiInfo = _DISABLE)
#endif

#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
#define GET_DRR_DSC0_ENABLED()                              (g_bDrrDscDecoder0Enable)
#define SET_DRR_DSC0_ENABLED(x)                             (g_bDrrDscDecoder0Enable = (x))
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
#define GET_DRR_DSC1_ENABLED()                              (g_bDrrDscDecoder1Enable)
#define SET_DRR_DSC1_ENABLED(x)                             (g_bDrrDscDecoder1Enable = (x))
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#define CLR_FREESYNC_II_INFO_DATA(region)                   (memset(&g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(region)], 0, sizeof(StructFreeSyncIIInfo)))
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON))
//--------------------------------------------------
// Definitions of Small Vsync Height (DP Freesync or DSC HDMI2.1)
//--------------------------------------------------
#define _DP_SMALL_DV_SYNC_HEIGHT                            (1)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DP ADAPTIVESYNC Support
//--------------------------------------------------
typedef struct
{
    BYTE b1DpD0Enable : 1;
    BYTE b1DpD1Enable : 1;
    BYTE b1DpD2Enable : 1;
    BYTE b1DpTxEnable : 1;

    BYTE b1DpD0Support : 1;
    BYTE b1DpD1Support : 1;
    BYTE b1DpD2Support : 1;

    BYTE b1DpRx0SpdInfoFrameReceived : 1;
    BYTE b1DpRx1SpdInfoFrameReceived : 1;

    BYTE b1DpD0CapabilitySwitch : 1;
    BYTE b1DpD1CapabilitySwitch : 1;
    BYTE b1DpD2CapabilitySwitch : 1;
} StructDrrDpAdaptiveSyncEnableInfo;
#endif

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DP FREESYNC Support
//--------------------------------------------------
typedef struct
{
    BYTE b1DpD0Enable : 1;
    BYTE b1DpD1Enable : 1;
    BYTE b1DpD2Enable : 1;
    BYTE b1DpD9Enable : 1;
    BYTE b1DpTxEnable : 1;
    BYTE b1DpPxpEnable : 1;

    BYTE b1DpD0Support : 1;
    BYTE b1DpD1Support : 1;
    BYTE b1DpD2Support : 1;

    BYTE b1DpRx0SpdInfoFrameReceived : 1;
    BYTE b1DpRx1SpdInfoFrameReceived : 1;

    BYTE b1DpD0CapabilitySwitch : 1;
    BYTE b1DpD1CapabilitySwitch : 1;
    BYTE b1DpD2CapabilitySwitch : 1;


    BYTE b1DpRxGetAupiInfo : 1;
} StructDrrFreeSyncDpEnableInfo;

//--------------------------------------------------
// Struct for HDMI FREESYNC Support
//--------------------------------------------------
typedef struct
{
    BYTE b1HdmiD0Enable : 1;
    BYTE b1HdmiD1Enable : 1;
    BYTE b1HdmiD2Enable : 1;
    BYTE b1HdmiD3Enable : 1;
    BYTE b1HdmiD4Enable : 1;
    BYTE b1HdmiD5Enable : 1;

    BYTE b1HdmiRx0SpdInfoFrameReceived : 1;
    BYTE b1HdmiRx1SpdInfoFrameReceived : 1;
    BYTE b1HdmiRx2SpdInfoFrameReceived : 1;
    BYTE b1HdmiRx3SpdInfoFrameReceived : 1;
    BYTE b1HdmiRx4SpdInfoFrameReceived : 1;
    BYTE b1HdmiRx5SpdInfoFrameReceived : 1;

    BYTE b1HdmiRx3FreesyncReplayReceived : 1;
    BYTE b1HdmiRx4FreesyncReplayReceived : 1;

    BYTE b1HdmiRxGetAupiInfo : 1;

    EnumFreeSyncSupport enumHdmiD0Support;
    EnumFreeSyncSupport enumHdmiD1Support;
    EnumFreeSyncSupport enumHdmiD2Support;
    EnumFreeSyncSupport enumHdmiD3Support;
    EnumFreeSyncSupport enumHdmiD4Support;
    EnumFreeSyncSupport enumHdmiD5Support;
} StructDrrFreeSyncHdmiEnableInfo;

//--------------------------------------------------
// Struct for FREESYNC Ver from Edid
//--------------------------------------------------
typedef struct
{
    BYTE b3D0FreeSyncVerbyEdid : 3;
    BYTE b3D1FreeSyncVerbyEdid : 3;
    BYTE b3D2FreeSyncVerbyEdid : 3;
    BYTE b3D3FreeSyncVerbyEdid : 3;
    BYTE b3D4FreeSyncVerbyEdid : 3;
    BYTE b3D5FreeSyncVerbyEdid : 3;
} StructDrrFreesyncVerByEdid;

//--------------------------------------------------
// Enum for AMD VSDB Ver
//--------------------------------------------------
typedef enum
{
    _AMD_VER_NONE = 0x00,
    _AMD_VER1,
    _AMD_VER2,
    _AMD_VER3,
} EnumAmdVsdbVer;
#endif

#if(_DRR_SUPPORT == _ON)
//--------------------------------------------------
// Enum for DRR Enable Type
//--------------------------------------------------
typedef enum
{
    _DP_FREESYNC_ENABLE = 0x00,
    _HDMI_FREESYNC_ENABLE,
    _HDMI21_VRR_ENABLE,
    _DRR_TYPE_DISABLE,
} EnumDrrTypeEnable;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern StructDrrDpAdaptiveSyncEnableInfo g_stDrrDpAdaptiveSyncInfo;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern StructDrrFreeSyncDpEnableInfo g_stDrrFreeSyncDpInfo;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
extern StructDrrFreeSyncHdmiEnableInfo g_stDrrFreeSyncHdmiInfo;
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern StructDrrAmdAupiInfo g_stDrrHdmiAmdAupiInfo;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern StructDrrAmdAupiInfo g_stDrrDpAmdAupiInfo;
#endif

#if(_DRR_SUPPORT == _ON)
extern bit g_bDrrGetIVFInfo;

extern WORD g_usDrrPanelVFreqMax;
extern WORD g_usDrrPanelVFreqMin;

extern DWORD g_ulDrrVFreqMax;
extern DWORD g_ulDrrVFreqMin;
#endif

#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
extern bit g_bDrrDscDecoder0Enable;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
extern bit g_bDrrDscDecoder1Enable;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DRR_SUPPORT == _ON)
extern bit ScalerDrrVfreqMaxInfoEnable(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern void ScalerDrrSetPanelVfeqInfo(EnumInputPort enumInputPort);
extern EnumDrrType ScalerDrrGetType(EnumInputPort enumInputPort);
extern bit ScalerDrrReceiveSourceIVF(EnumInputPort enumInputPort, EnumPortType enumPortType, WORD *pusIVfreq);

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void ScalerDrrDpAdaptiveSyncSupportSwitch(EnumInputPort enumInputPort, EnumDpAdaptiveSyncSupport enumSupport);
extern EnumDpAdaptiveSyncSupport ScalerDrrDpAdaptiveSyncGetSupport(EnumInputPort enumInputPort);
#endif

#if(_FREESYNC_SUPPORT == _ON)

#if((_DEBUG_MESSAGE_SUPPORT == _OFF) && (_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE ScalerDrrFreeSyncGetHdmiVcp(void);
extern void ScalerDrrFreeSyncSetHdmiVcp(BYTE ucVcpCode);
#endif

extern void ScalerDrrFreeSyncSupportSwitch(EnumInputPort enumInputPort, EnumFreeSyncSupport enumSupport, EnumInputPort enumFreesyncTargetPort);
extern void ScalerDrrFreeSyncSpdInfoReceive(EnumInputPort enumInputPort);

extern void ScalerDrrSetAmdVsdbVer(EnumInputPort enumInputPort, EnumAmdVsdbVer enumAmdVer);
extern DWORD ScalerDrrFreeSyncGetInfo(EnumInputPort enumInputPort, EnumAmdSpdInfoContent enumContent);

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) &&\
    (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern EnumFreeSyncSupport ScalerDrrFreeSyncHdmiGetFreeSyncSupport(EnumInputPort enumInputPort);
#endif
#endif
#endif

#endif
#endif

#if((_FREESYNC_II_SUPPORT == _ON) && (_ULTRA_HDR_SUPPORT == _ON))
extern void ScalerDrrFreeSyncIIGetCurrentStatus(EnumInputPort enumInputPort, EnumDisplayRegion enumDisplayRegion, EnumHDRInfoChgPolling enumFreeSyncIIInfoChgPolling);
#endif

#if((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
extern bit ScalerDrrIVSProduceByBE(EnumSourceType enumSourceType, EnumInputPort enumInputPort);
#endif
