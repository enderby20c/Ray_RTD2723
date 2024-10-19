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
// ID Code      : ScalerDpMacRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
#if(_DP_MAC_RX0_SUPPORT == _ON)
#define GET_DP_MAC_RX0_COMBO_POWER_CUT_STATUS()                    (g_stDpMacRxComboPowerStatus.b1DpMacRx0PowerCutStatus)
#define SET_DP_MAC_RX0_COMBO_POWER_CUT_STATUS(x)                   (g_stDpMacRxComboPowerStatus.b1DpMacRx0PowerCutStatus = (x))
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
#define GET_DP_MAC_RX1_COMBO_POWER_CUT_STATUS()                    (g_stDpMacRxComboPowerStatus.b1DpMacRx1PowerCutStatus)
#define SET_DP_MAC_RX1_COMBO_POWER_CUT_STATUS(x)                   (g_stDpMacRxComboPowerStatus.b1DpMacRx1PowerCutStatus = (x))
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
#define GET_DP_MAC_RX2_COMBO_POWER_CUT_STATUS()                    (g_stDpMacRxComboPowerStatus.b1DpMacRx2PowerCutStatus)
#define SET_DP_MAC_RX2_COMBO_POWER_CUT_STATUS(x)                   (g_stDpMacRxComboPowerStatus.b1DpMacRx2PowerCutStatus = (x))
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulLinkClockHz;                // Link Clock
    DWORD ulMsaVfreqClk128b132b;        // Vfreq Clock
    DWORD ulMvid;                       // Mvid
    DWORD ulNvid;                       // Nvid
    DWORD ulStreamClockHz;              // Stream Clock
    DWORD ulInitStreamClockHz;          // Initial Stream Clock
    DWORD ulPllInputClockHz;            // PLL Input Clock
    DWORD ulVBsToBsCountN;              // V BS to BS Count of The Nth Frame
    DWORD ulVBsToBsCountN1;             // V BS to BS Count of The (N+1)th Frame
    WORD usHBsToBsCount;                // H BS to BS Count
    BYTE ucPixelMode;                   // Pixel Mode
    BYTE ucPllDivs;                     // PLL Div_s parameter
    BYTE ucPllDivo;                     // PLL Div_o parameter
    BYTE b1HwInterlaceDetect : 1;       // HW Detect Interlace Flag
    BYTE b1HwFakeInterlaceDetect : 1;   // HW Detect Fake Interlace Flag
    BYTE b1InterlaceFieldN : 1;         // VBID[1] Inerlace Field Flag of The Nth Frame
    BYTE b1InterlaceFieldN1 : 1;        // VBID[1] Inerlace Field Flag of The (N+1)th Frame
    BYTE b1InterlaceOddMode : 1;        // VBID[1] Inerlace Field Mode (Even or Odd)
    BYTE b1InterlaceStatus : 1;         // Final Judge Interlace Timing or Not
}StructDpLinkInfo;

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Hblanking Modify Mode
//--------------------------------------------------
typedef enum
{
    _NO_HBLANKING_MODIFY = 0x00,
    _HBE_MODE,
    _HBR_MODE,
} EnumDpMacRxHblankingModifyMode;

//--------------------------------------------------
// Struct for DPCP HBE/HBR Info
//--------------------------------------------------
typedef struct
{
    BYTE b1DpcdHSP : 1;
    WORD usDpcdHTotal;
    WORD usDpcdHStart;
    WORD usDpcdHSWidth;
    WORD usMsaHTotal;
    EnumDpMacRxHblankingModifyMode enumHblankingModifyMode;
}StructDpMacRxHblankingModifyInfo;
#endif

typedef struct
{
    StructTimingInfo stDpTimingInfo;
    StructDpLinkInfo stDpLinkInfo;

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    StructDpMacRxHblankingModifyInfo stDpHblankingModifyInfo;
#endif
}StructDpInfo;

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
typedef struct
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    BYTE b1DpMacRx0PowerCutStatus : 1;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    BYTE b1DpMacRx1PowerCutStatus : 1;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    BYTE b1DpMacRx2PowerCutStatus : 1;
#endif
}StructDpMacRxComboPowerStatus;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
extern StructDpMacRxComboPowerStatus g_stDpMacRxComboPowerStatus;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpMacRxLowPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacRxHighPriorityIntHandler_EXINT0(void);
// Special
extern void ScalerDpMacRxPowerDataRecover(void); // In DpMacRx top

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpMacRxSetTxCloneRxPortSel(EnumInputPort enumInputPort);
#endif

extern bit ScalerDpMacRxGetPowerCutFlagStatus(EnumInputPort enumInputPort);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
extern bit ScalerDpMacRxGetComboPowerCutFlagStatus(EnumInputPort enumInputPort);
#endif

extern bit ScalerDpMacRxGetPowerCutFlagStatus_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacRxPowerProc_EXINT0(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction);
extern EnumPowerCut ScalerDpMacRxGetPowerCutCurrentStatus_EXINT0(EnumInputPort enumInputPort);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
extern void ScalerDpMacRxPowerCutComboPowerProc_EXINT0(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction);
extern EnumPowerCut ScalerDpMacRxGetComboPowerCutCurrentStatus_EXINT0(EnumInputPort enumInputPort);
#endif
#endif
