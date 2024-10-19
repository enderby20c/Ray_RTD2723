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
// ID Code      : ScalerPLLInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of NF M2PLL Clock Frequency Paramater
//--------------------------------------------------
#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)

#if(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
#define _M2PLL_CLK_KHZ                              (351000)
#define _M2PLL_CLK_MHZ                              (351)
#elif(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)
#define _M2PLL_CLK_KHZ                              (243000)
#define _M2PLL_CLK_MHZ                              (243)
#endif

#endif // End of #if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)

#if(_HW_EPLL_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of NF EMCUPLL Clock Frequency Paramater
//--------------------------------------------------
#if(_EXT_XTAL == _XTAL14318K)
#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_354M)
//*************************************************************************
//  Pll Parameters Setting
//  Vref = Crystal = 14.318M
//
//  EPLL Target Clock = 14.7456MHz*24 = 353.8944MHz = 14.318M*24.716748149182846766308143595474
//  24.716748149182846766308143595474 = 24 + 0.716748149182846766308143595474
//  N = 24 = 22 + 2
//  F = 0.716748149182846766308143595474 * (2**20) = 751564.90727755273082832797876775 => 751565
//  (N = 24 = 0x16 + 2, F = 751565 = 0xB77CD)
//*************************************************************************
#define _EMCUPLL_NF_N                               (22 + 2) // 0x230D[7:0] default value = 0x16
#define _EMCUPLL_NF_F                               (751565) // 0x230E[7:0]~0x2310[7:0] default value = 0x083BCD
#endif

#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_480M)
//*************************************************************************20200528
//  Pll Parameters Setting //EMCUPLL_480MHz_14.318M
//  Vref = Crystal = 14.318M
//
//  EPLL=480MHz (CURRENT USE)
//  EPLL Test Clock = 14.5455MHz*33 = 479.9999MHz = 14.318M*33.524235228383852493364995111049
//  33.524235228383852493364995111049 = 33 + 0.524235228383852493364995111049
//  N = 33 = 31 + 2
//  F = 0.524235228383852493364995111049 * (2**20) = 549700.47883782651208269311356332 => 549700
//  (N = 33 = 0x1F + 2, F = 549700 = 0x86344)
//*************************************************************************
#define _EMCUPLL_NF_N                               (31 + 2) // 0x230D[7:0] default value = 0x16
#define _EMCUPLL_NF_F                               (549700) // 0x230E[7:0]~0x2310[7:0] default value = 0x083BCD
#endif
#endif

#if(_EXT_XTAL == _XTAL27000K)
#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_354M)
//*************************************************************************
//  Pll Parameters Setting
//  Vref = Crystal = 27.000M
//
//  EPLL Target Clock = 14.7456MHz*24 = 353.8944MHz = 27.000M*13.1072
//  13.1072 = 13 + 0.1072
//  N = 13 = 11 + 2
//  F = 0.1072 * (2^20) = 112407.3472 => 112407
//  (N = 13 = 0x0B + 2, F = 112407 = 0x01B717)
//*************************************************************************
#define _EMCUPLL_NF_N                               (11 + 2) // 0x230D[7:0] default value = 0x16
#define _EMCUPLL_NF_F                               (112407) // 0x230E[7:0]~0x2310[7:0] default value = 0x083BCD
#endif

#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_480M)
//*************************************************************************20200528
//  Pll Parameters Setting //EMCUPLL_480MHz_27.000M
//  Vref = Crystal = 27.000M
//
//  EPLL=480MHz (CURRENT USE)
//  EPLL Test Clock = 14.5455MHz*33 = 479.9999MHz = 27.000M*17.777774074074074074074074074074
//  17.777774074074074074074074074074 = 17 + 0.777774074074074074074074074074
//  N = 17 = 15 + 2
//  F = 0.777774074074074074074074074074 * (2**20) = 815555.22749629629629629629629622 => 815555
//  (N = 17 = 0x0F + 2, F = 815555 = 0x0C71C3)
//*************************************************************************
#define _EMCUPLL_NF_N                               (15 + 2) // 0x230D[7:0] default value = 0x16
#define _EMCUPLL_NF_F                               (815555) // 0x230E[7:0]~0x2310[7:0] default value = 0x083BCD
#endif
#endif

#endif

//--------------------------------------------------
// Definitions of N.F PLL KVCO BAND
//--------------------------------------------------
#define _NFPLL_KVCO                                 (4000)

//--------------------------------------------------
// Definitions of DPLL power status
//--------------------------------------------------
#if(_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
#define GET_DPLL_POWER_STATUS()                     (ScalerGetBit(P1_D1_DPLL_ANALOG_SETTING_1, _BIT0) == 0)
#elif(_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
#define GET_DPLL_POWER_STATUS()                     (ScalerGetBit(P1_D1_DPLL_ANALOG_SETTING_1, _BIT0) == 0)
#else
#define GET_DPLL_POWER_STATUS()                     (ScalerGetBit(P1_C2_DPLL_WD, _BIT0) == 0)
#endif

#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#define GET_M2PLL_POWER_STATUS()                    (ScalerGetBit(P1_58_M2PLL_CONTROL, _BIT0) == 0)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern DWORD g_ulPLLFifoRateMode;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerM2PLLDiv(BYTE ucDiv);
extern void ScalerPLLSetDPLLReset(void);
extern DWORD ScalerPLLGetNewCount(DWORD ulCountNew, DWORD ulCountOld, DWORD ulValueOld, bit bProportion);

#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
extern void ScalerPLLMPLLPower(BYTE ucOn);
extern void ScalerPLLSetMPLLFreq(DWORD ulFreq);
#endif

#if(_PANEL_STYLE != _PANEL_VBO)
#if((_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
extern void ScalerPLLSetDPLLNFcode(DWORD ulNFcode);
#endif
#endif
extern void ScalerDPLLFineTuneFrameSyncLineBuffer(void);
#if(_FRC_SUPPORT == _ON)
#if(_PANEL_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
extern void ScalerDPLLFineTuneFrameSyncFrameBuffer(void);
#endif
#endif

#if(_VGA_SUPPORT == _ON)
extern bit ScalerAPLLAdjust(WORD usCurrHTotal, WORD usCurrHFreq);
extern WORD ScalerAPLLGetIHTotal(void);
#endif

#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
extern void ScalerPLLSetDPLLRefPLL(DWORD ulFreq);
#endif

