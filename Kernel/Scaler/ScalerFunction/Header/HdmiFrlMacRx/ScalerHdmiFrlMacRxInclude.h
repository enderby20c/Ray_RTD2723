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
// ID Code      : ScalerHdmiFrlMacRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_FRL_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// HDMI FRL Option
//--------------------------------------------------
#define _HDMI_FRL_DPF_TRACKING_METHOD                       _HDMI_FRL_VIRTUAL_FIFO_TRACKING

//--------------------------------------------------
// HDMI DSC dec fail notify
//--------------------------------------------------
#define _HDMI_DSC_DEC_FAIL_NOTIFY                           _OFF

//--------------------------------------------------
// Definitions of Link Training State
//--------------------------------------------------
#define _HDMI_FRL_LT_NONE                                   0
#define _HDMI_FRL_LT_LTS1                                   1
#define _HDMI_FRL_LT_LTS2                                   2
#define _HDMI_FRL_LT_LTS3                                   3
#define _HDMI_FRL_LT_LTS3_LFSR                              4
#define _HDMI_FRL_LT_LTS4                                   5
#define _HDMI_FRL_LT_LTSP_GAP                               6
#define _HDMI_FRL_LT_LTSP_FRL_START                         7
#define _HDMI_FRL_LT_LTSL                                   8
#define _HDMI_FRL_LT_LTSEND                                 9

//--------------------------------------------------
// Definitions of FFE Level
//--------------------------------------------------
#define _HDMI_FRL_FFE0                                      0
#define _HDMI_FRL_FFE1                                      1
#define _HDMI_FRL_FFE2                                      2
#define _HDMI_FRL_FFE3                                      3

//--------------------------------------------------
// Definitions of HDMI Lane
//--------------------------------------------------
#define _HDMI_FRL_LANE0                                     0
#define _HDMI_FRL_LANE1                                     1
#define _HDMI_FRL_LANE2                                     2
#define _HDMI_FRL_LANE3                                     3

//--------------------------------------------------
// Definitions of DPF TRACKING METHOD
//--------------------------------------------------
#define _HDMI_FRL_LINE_TRACKING                             0
#define _HDMI_FRL_VIRTUAL_FIFO_TRACKING                     1

#if(_3DDI_FUNCTION == _ON)
#define _HDMI_FRL_3DDI_HACTIVE_LIMIT                        1920
#define _HDMI_FRL_3DDI_VACTIVE_LIMIT                        540
#endif

#if(_D1_HDMI_FRL_SUPPORT == _ON)
//--------------------------------------------------
// Macro of D1 FRL Link Rate
//--------------------------------------------------
#define GET_HDMI_FRL_D1_FRL_RATE()                          (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4FrlRate)
#define SET_HDMI_FRL_D1_FRL_RATE(x)                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4FrlRate = (x))
#define CLR_HDMI_FRL_D1_FRL_RATE()                          (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4FrlRate = 0)

//--------------------------------------------------
// Macro of D1 FFE Level
//--------------------------------------------------
#define GET_HDMI_FRL_D1_MAX_FFE_LEVEL()                     (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4MaxFfeLevel)
#define SET_HDMI_FRL_D1_MAX_FFE_LEVEL(x)                    (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4MaxFfeLevel = (x))
#define CLR_HDMI_FRL_D1_MAX_FFE_LEVEL()                     (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4MaxFfeLevel = 0)

#define GET_HDMI_FRL_D1_LANE0_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane0Ffe)
#define ADD_HDMI_FRL_D1_LANE0_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane0Ffe++)
#define CLR_HDMI_FRL_D1_LANE0_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane0Ffe = 0)

#define GET_HDMI_FRL_D1_LANE1_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane1Ffe)
#define ADD_HDMI_FRL_D1_LANE1_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane1Ffe++)
#define CLR_HDMI_FRL_D1_LANE1_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane1Ffe = 0)

#define GET_HDMI_FRL_D1_LANE2_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane2Ffe)
#define ADD_HDMI_FRL_D1_LANE2_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane2Ffe++)
#define CLR_HDMI_FRL_D1_LANE2_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane2Ffe = 0)

#define GET_HDMI_FRL_D1_LANE3_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane3Ffe)
#define ADD_HDMI_FRL_D1_LANE3_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane3Ffe++)
#define CLR_HDMI_FRL_D1_LANE3_FFE()                         (g_stHdmiFrlMacRxD1LinkTrainingInfo.b4Lane3Ffe = 0)
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
//--------------------------------------------------
// Macro of D2 FRL Link Rate
//--------------------------------------------------
#define GET_HDMI_FRL_D2_FRL_RATE()                          (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4FrlRate)
#define SET_HDMI_FRL_D2_FRL_RATE(x)                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4FrlRate = (x))
#define CLR_HDMI_FRL_D2_FRL_RATE()                          (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4FrlRate = 0)

//--------------------------------------------------
// Macro of D2 FFE Level
//--------------------------------------------------
#define GET_HDMI_FRL_D2_MAX_FFE_LEVEL()                     (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4MaxFfeLevel)
#define SET_HDMI_FRL_D2_MAX_FFE_LEVEL(x)                    (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4MaxFfeLevel = (x))
#define CLR_HDMI_FRL_D2_MAX_FFE_LEVEL()                     (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4MaxFfeLevel = 0)

#define GET_HDMI_FRL_D2_LANE0_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane0Ffe)
#define ADD_HDMI_FRL_D2_LANE0_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane0Ffe++)
#define CLR_HDMI_FRL_D2_LANE0_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane0Ffe = 0)

#define GET_HDMI_FRL_D2_LANE1_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane1Ffe)
#define ADD_HDMI_FRL_D2_LANE1_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane1Ffe++)
#define CLR_HDMI_FRL_D2_LANE1_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane1Ffe = 0)

#define GET_HDMI_FRL_D2_LANE2_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane2Ffe)
#define ADD_HDMI_FRL_D2_LANE2_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane2Ffe++)
#define CLR_HDMI_FRL_D2_LANE2_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane2Ffe = 0)

#define GET_HDMI_FRL_D2_LANE3_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane3Ffe)
#define ADD_HDMI_FRL_D2_LANE3_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane3Ffe++)
#define CLR_HDMI_FRL_D2_LANE3_FFE()                         (g_stHdmiFrlMacRxD2LinkTrainingInfo.b4Lane3Ffe = 0)
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
//--------------------------------------------------
// Macro of D3 FRL Link Rate
//--------------------------------------------------
#define GET_HDMI_FRL_D3_FRL_RATE()                          (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4FrlRate)
#define SET_HDMI_FRL_D3_FRL_RATE(x)                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4FrlRate = (x))
#define CLR_HDMI_FRL_D3_FRL_RATE()                          (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4FrlRate = 0)

//--------------------------------------------------
// Macro of D3 FFE Level
//--------------------------------------------------
#define GET_HDMI_FRL_D3_MAX_FFE_LEVEL()                     (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4MaxFfeLevel)
#define SET_HDMI_FRL_D3_MAX_FFE_LEVEL(x)                    (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4MaxFfeLevel = (x))
#define CLR_HDMI_FRL_D3_MAX_FFE_LEVEL()                     (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4MaxFfeLevel = 0)

#define GET_HDMI_FRL_D3_LANE0_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane0Ffe)
#define ADD_HDMI_FRL_D3_LANE0_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane0Ffe++)
#define CLR_HDMI_FRL_D3_LANE0_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane0Ffe = 0)

#define GET_HDMI_FRL_D3_LANE1_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane1Ffe)
#define ADD_HDMI_FRL_D3_LANE1_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane1Ffe++)
#define CLR_HDMI_FRL_D3_LANE1_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane1Ffe = 0)

#define GET_HDMI_FRL_D3_LANE2_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane2Ffe)
#define ADD_HDMI_FRL_D3_LANE2_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane2Ffe++)
#define CLR_HDMI_FRL_D3_LANE2_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane2Ffe = 0)

#define GET_HDMI_FRL_D3_LANE3_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane3Ffe)
#define ADD_HDMI_FRL_D3_LANE3_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane3Ffe++)
#define CLR_HDMI_FRL_D3_LANE3_FFE()                         (g_stHdmiFrlMacRxD3LinkTrainingInfo.b4Lane3Ffe = 0)
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
//--------------------------------------------------
// Macro of D4 FRL Link Rate
//--------------------------------------------------
#define GET_HDMI_FRL_D4_FRL_RATE()                          (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4FrlRate)
#define SET_HDMI_FRL_D4_FRL_RATE(x)                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4FrlRate = (x))
#define CLR_HDMI_FRL_D4_FRL_RATE()                          (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4FrlRate = 0)

//--------------------------------------------------
// Macro of D4 FFE Level
//--------------------------------------------------
#define GET_HDMI_FRL_D4_MAX_FFE_LEVEL()                     (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4MaxFfeLevel)
#define SET_HDMI_FRL_D4_MAX_FFE_LEVEL(x)                    (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4MaxFfeLevel = (x))
#define CLR_HDMI_FRL_D4_MAX_FFE_LEVEL()                     (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4MaxFfeLevel = 0)

#define GET_HDMI_FRL_D4_LANE0_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane0Ffe)
#define ADD_HDMI_FRL_D4_LANE0_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane0Ffe++)
#define CLR_HDMI_FRL_D4_LANE0_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane0Ffe = 0)

#define GET_HDMI_FRL_D4_LANE1_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane1Ffe)
#define ADD_HDMI_FRL_D4_LANE1_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane1Ffe++)
#define CLR_HDMI_FRL_D4_LANE1_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane1Ffe = 0)

#define GET_HDMI_FRL_D4_LANE2_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane2Ffe)
#define ADD_HDMI_FRL_D4_LANE2_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane2Ffe++)
#define CLR_HDMI_FRL_D4_LANE2_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane2Ffe = 0)

#define GET_HDMI_FRL_D4_LANE3_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane3Ffe)
#define ADD_HDMI_FRL_D4_LANE3_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane3Ffe++)
#define CLR_HDMI_FRL_D4_LANE3_FFE()                         (g_stHdmiFrlMacRxD4LinkTrainingInfo.b4Lane3Ffe = 0)
#endif

//--------------------------------------------------
// HDMI 2.1 DPF FIFO Half Length
//--------------------------------------------------
#define _HDMI_FRL_DPF_FIFO_HALF_LENGTH                      1472 // Total = 368 * 2 * 4


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Struct of HDMI2.1
//--------------------------------------------------
typedef struct
{
    BYTE b4LtState : 4;
    BYTE b1FrlPhySet : 1;
    BYTE b1FrlRateEvent : 1;
    BYTE b1FrlStartEvent : 1;

    BYTE b1Lane0Lock : 1;
    BYTE b1Lane1Lock : 1;
    BYTE b1Lane2Lock : 1;
    BYTE b1Lane3Lock : 1;
    BYTE b1PacketDetecting : 1;
    BYTE b1FrlAdvancedHdr10Detecting : 1;

    BYTE b1HFVsifReceived : 1;
    BYTE b1FrlAdvancedHdr10VsifReceived : 1;
    BYTE b1FrlDhdrEmpType40Received : 1;
    BYTE b1AVIInfoFrameReceived : 1;
    BYTE b1GCPReceived : 1;
    BYTE b1ReactiveSearchTime : 1;
    BYTE b1RebuildPhyEvent : 1;
    BYTE b1DpfPixelModeMismatch : 1;

#if(_DM_FUNCTION == _ON)
    BYTE b1DmVsifReceived : 1;
    BYTE b1DmInfoDetecting : 1;
    BYTE b1DmEmpReceived : 1;
#endif

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
    BYTE b1SignalDetecting : 1;
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
    BYTE b1HdmiVsifReceived : 1;
#endif
} StructHdmiFrlCtrlInfo;

typedef struct
{
    BYTE b4FrlRate : 4;
    BYTE b4MaxFfeLevel : 4;

    BYTE b4Lane0Ffe : 4;
    BYTE b4Lane1Ffe : 4;

    BYTE b4Lane2Ffe : 4;
    BYTE b4Lane3Ffe : 4;
} StructHdmiFrlLinkTrainingInfo;

typedef struct
{
    BYTE b4CedLockIrqBackup : 4;
    BYTE b4RsvIrqBackup : 4;
    BYTE b1VsEmpIrqBackup : 1;
    BYTE b1DhdrEmpIrqBackup : 1;
    BYTE b1TransitionDetectIrqBackup : 1;
} StructHdmiFrlIrqStatus;

//--------------------------------------------------
// Enumerations of HDMI2.1 DPF Mode
//--------------------------------------------------
typedef enum
{
    _HDMI_FRL_MAC_RX_DPF_LINE_SYNC,
    _HDMI_FRL_MAC_RX_DPF_FRAME_SYNC,
    _HDMI_FRL_MAC_RX_DPF_FULL_LAST_LINE,
    _HDMI_FRL_MAC_RX_DPF_NONE,
} EnumHdmiFrlMacRxDpfDisplayMode;

//--------------------------------------------------
// Enumerations of HDMI2.1 DPF Pixel Mode
//--------------------------------------------------
typedef enum
{
    _HDMI_FRL_MAC_RX_DPF_ONE_PIXEL_MODE,
    _HDMI_FRL_MAC_RX_DPF_TWO_PIXEL_MODE,
    _HDMI_FRL_MAC_RX_DPF_FOUR_PIXEL_MODE,
    _HDMI_FRL_MAC_RX_DPF_PIXEL_MODE_NONE,
} EnumHdmiFrlMacRxDpfPixelMode;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_D1_HDMI_FRL_SUPPORT == _ON)
extern volatile StructHdmiFrlLinkTrainingInfo g_stHdmiFrlMacRxD1LinkTrainingInfo;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
extern volatile StructHdmiFrlLinkTrainingInfo g_stHdmiFrlMacRxD2LinkTrainingInfo;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
extern volatile StructHdmiFrlLinkTrainingInfo g_stHdmiFrlMacRxD3LinkTrainingInfo;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
extern volatile StructHdmiFrlLinkTrainingInfo g_stHdmiFrlMacRxD4LinkTrainingInfo;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumHdmiFrlMacRxDpfPixelMode ScalerHdmiFrlMacRxGetDpfPixelMode(EnumInputPort enumInputPort);
extern bit ScalerHdmiFrlMacRxInterlaceModeCheck(EnumInputPort enumInputPort);
extern WORD ScalerHdmiFrlMacRxCdrOffMeasureClk_EXINT0(EnumInputPort enumInputPort, BYTE ucLane);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRxClrCvtemReceived(EnumInputPort enumInputPort);
#if(_HDMI_DSC_DEC_FAIL_NOTIFY == _ON)
extern void ScalerHdmiFrlMacRxSetDscDecodeFailStatus(EnumInputPort enumInputPort);
#endif
extern bit ScalerHdmiFrlMacRxGetCvtemReceived(EnumInputPort enumInputPort);
#endif

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
extern WORD ScalerHdmiFrlMacRxCdrOffMeasureClk(EnumInputPort enumInputPort, BYTE ucLane);
#endif

extern void ScalerHdmiFrlMacRxSetDxFrlRate(EnumInputPort enumInputPort, BYTE ucFrlRate);
extern BYTE ScalerHdmiFrlMacRxGetDxFrlRate(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRxClrDxFrlRate(EnumInputPort enumInputPort);

extern BYTE ScalerHdmiFrlMacRxGetDxMaxFrlRate(EnumInputPort enumInputPort);

extern void ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(EnumInputPort enumInputPort, BYTE ucFrlRate);
extern BYTE ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerHdmiFrlMacRxGetDxMaxFrlRate_EXINT0(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRxSetDxFrlMaxFfeLevel_EXINT0(EnumInputPort enumInputPort, BYTE ucFrlFfeLevel);
extern BYTE ScalerHdmiFrlMacRxGetDxFrlMaxFfeLevel_EXINT0(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRxAddDxFrlFfeLevel_EXINT0(EnumInputPort enumInputPort, BYTE ucLane);
extern BYTE ScalerHdmiFrlMacRxGetDxFrlFfeLevel_EXINT0(EnumInputPort enumInputPort, BYTE ucLane);
extern void ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(EnumInputPort enumInputPort, BYTE ucLane);
extern void ScalerHdmiFrlMacRxIrqRestoreAfterZ0On(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRxScdcReset(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRxInitial(void);
#endif // End of #if(_HDMI_FRL_SUPPORT == _ON)

