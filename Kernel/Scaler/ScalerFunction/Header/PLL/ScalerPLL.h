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
// ID Code      : ScalerPLL.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_PLL_H__
#define __SCALER_PLL_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX) || (_PANEL_STYLE == _PANEL_LVDS))
//--------------------------------------------------
// Definations of DPTX CLK Into DPLL Range
//--------------------------------------------------
#define _DPTX_CLK_IN_BOUNDRY_0                              60000UL
#define _DPTX_CLK_IN_BOUNDRY_1                              120000UL
#define _DPTX_CLK_IN_BOUNDRY_2                              240000UL

//--------------------------------------------------
// Definations of LVDS VCO Range, convert into Dclk frequency
//--------------------------------------------------
#define _LVDS_PLL_BOUNDRY_0                                 (250000  * (1 << _PANEL_LVDS_OUTPUT_PORT) / (7 << GET_D_DOMAIN_PATH()))
#define _LVDS_PLL_BOUNDRY_1                                 (500000  * (1 << _PANEL_LVDS_OUTPUT_PORT) / (7 << GET_D_DOMAIN_PATH()))
#define _LVDS_PLL_BOUNDRY_2                                 (1000000 * (1 << _PANEL_LVDS_OUTPUT_PORT) / (7 << GET_D_DOMAIN_PATH()))

#if(_HW_DISPLAY_DPTX_COMBO_TYPE == _DISPLAY_LVDS_COMBO_DPTX)
//--------------------------------------------------
// Definations of DPTX CMU CCO Range
//--------------------------------------------------
#define _DPTX_PLL_BOUNDRY_0                                 187500
#define _DPTX_PLL_BOUNDRY_1                                 375000
#define _DPTX_PLL_BOUNDRY_2                                 750000
#define _DPTX_PLL_BOUNDRY_3                                 1500000
#else
//--------------------------------------------------
// Definations of DPTX CMU CCO Range
//--------------------------------------------------
#define _DPTX_PLL_BOUNDRY_0                                 750000
#define _DPTX_PLL_BOUNDRY_1                                 1500000
#define _DPTX_PLL_BOUNDRY_2                                 2000000
#define _DPTX_PLL_BOUNDRY_3                                 3000000
#define _DPTX_PLL_BOUNDRY_4                                 6000000
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)
#define _DPTX_PHY_RATE_RBR                                  1620000
#define _DPTX_PHY_RATE_HBR                                  2700000
#define _DPTX_PHY_RATE_HBR2                                 5400000
#define _DPTX_PHY_RATE_HBR3                                 8100000
#define _DPTX_PHY_RATE_HBR3_9G                              9000000
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)
#endif // End of #if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))

//--------------------------------------------------
// Definitions of APLL VCO Divider Threshold
//--------------------------------------------------
#define _APLL_VCO_DEVIDER_4_2_THERSHOLD                     100000

//--------------------------------------------------
// Definitions of difference between measurement edge phase and calculation by mode edge phase
//--------------------------------------------------
#define _PHASE_DELAY_EDGEPHASE_THRESHOLD                    2

//----------------------------------------------------------------------------
// APLL Parameters
//----------------------------------------------------------------------------
#define _APLL_SUM_I_READ_COUNT                              3

//--------------------------------------------------
// Definations of APLL _G_VALUE_DIVIDER
//--------------------------------------------------
#define _G_VALUE_DIVIDER_0                                  4
#define _G_VALUE_DIVIDER_1                                  16
#define _G_VALUE_DIVIDER_2                                  64
#define _G_VALUE_DIVIDER_3                                  128
#define _G_VALUE_DIVIDER_4                                  256
#define _G_VALUE_DIVIDER_5                                  512

//--------------------------------------------------
// Definations of DPLL Range
//--------------------------------------------------
#define _DPLL_BOUNDRY_0                                     700000
#define _DPLL_BOUNDRY_1                                     1400000
#define _DPLL_BOUNDRY_2                                     2800000
#define _DPLL_BOUNDRY_3                                     5600000

#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
//--------------------------------------------------
// Definitions of MPLL PixelDiv2 Bypass
//--------------------------------------------------
// for 6493,Pixeldiv2 of MPLL circuit reserved
#define _MPLL_PIXELDIV2_DIV                                 _DIV_1// 1 -- > Pixeldiv2 is disable

//--------------------------------------------------
// Definitions of MPLL PreDiv Bypass
//--------------------------------------------------
#define _MPLL_PREDIV_BYPASS                                 _ON

#if(_MPLL_PREDIV_BYPASS == _ON)
#define _MPLL_PREDIV_DIV                                    _DIV_1
#else
#define _MPLL_PREDIV_DIV                                    _DIV_2
#endif
#endif

#if(_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
//--------------------------------------------------
// Definitions of DPLL PixelDiv2 Bypass
//--------------------------------------------------
// for 6493, Pixel2div2 of DPLL circuit reserved.
#define _DPLL_PIXELDIV2_DIV                                 _DIV_1// 1 -- > Pixeldiv2 is disable

//--------------------------------------------------
// Definitions of DPLL PreDiv Bypass
//--------------------------------------------------
#define _DPLL_PREDIV_BYPASS                                 _ON

#if(_DPLL_PREDIV_BYPASS == _ON)
#define _DPLL_PREDIV_DIV                                    _DIV_1
#else
#define _DPLL_PREDIV_DIV                                    _DIV_2
#endif
#endif

#if((_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F) || (_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F))
//--------------------------------------------------
// Definitions of NFPLL loop filter cap.
//--------------------------------------------------
#define _NFPLL_CS_SEL                                       0x3// reserved

//--------------------------------------------------
// Definitions of NFPLL loop filter resistor
//--------------------------------------------------
#if(_HW_NF_PLL_STRUCT_TYPE == _NF_PLL_GEN_0)
#define _NFPLL_RS_SEL                                       0x1// 6.5k
#elif(_HW_NF_PLL_STRUCT_TYPE == _NF_PLL_GEN_1)
#define _NFPLL_RS_SEL                                       0x4// 9k
#endif
#endif

//--------------------------------------------------
// Definitions of NF M2PLL Clock Frequency Paramater
//--------------------------------------------------
#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#if(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
#if(_EXT_XTAL == _XTAL14318K)
#if(_FW_M2PLL_FVCO_SEL == _M2PLL_FVCO_351M)
#define _M2PLL_NF_N                                         (22 + 2) // 0x015D[7:0] default value = 0x16
#define _M2PLL_NF_F                                         (539597) // 0x015E[3:0] ~ 0x0160[7:0] default value = 0x083BCD
#if(_HW_NF_PLL_STRUCT_TYPE == _NF_PLL_GEN_0)
#define _M2PLL_ICP                                          (2) // 0x0156[2:0]=3'b010=7.5uA
#elif(_HW_NF_PLL_STRUCT_TYPE == _NF_PLL_GEN_1)
#define _M2PLL_ICP                                          (1) // 0x0156[2:0]=3'b001=5uA
#endif
#define _M2PLL_IPI                                          (0) // 0x0157[1:0]=2'b00=315~400Mhz
#define _M2PLL_POSTDIV                                      (0) // 0x0155[1:0]=2'b00=Div1
#define _M2PLL_PIXELDIV                                     (0) // 0x0152[1:0]=2'b00=Div1

#elif(_FW_M2PLL_FVCO_SEL == _M2PLL_FVCO_702M)
#define _M2PLL_NF_N                                         (47 + 2) // 0x015D[7:0] default value = 0x2F
#define _M2PLL_NF_F                                         (30612) // 0x015E[3:0] ~ 0x0160[7:0] default value = 0x07794
#if(_HW_NF_PLL_STRUCT_TYPE == _NF_PLL_GEN_0)
#define _M2PLL_ICP                                          (6) // 0x0156[2:0]=3'b110=17.5uA
#elif(_HW_NF_PLL_STRUCT_TYPE == _NF_PLL_GEN_1)
#define _M2PLL_ICP                                          (4) // 0x0156[2:0]=3'b100=12.5uA
#endif
#define _M2PLL_IPI                                          (3) // 0x0157[1:0]=2'b11=600~770Mhz
#define _M2PLL_POSTDIV                                      (0) // 0x0155[1:0]=2'b00=Div1
#define _M2PLL_PIXELDIV                                     (1) // 0x0152[1:0]=2'b01=Div2
#endif
#endif
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
typedef struct
{
    WORD usPEValue;
    WORD usPreHTotal;
    DWORD ulDivider;
} StructAdjustApllData;
#endif

#if(_VGA_SUPPORT == _ON)
typedef enum
{
    _ADCPLL_PHASE_METHOD_MANUAL,
    _ADCPLL_PHASE_METHOD_LOOKUPTABLE
} EnumADCPLLPhaseMethod;
#endif // End of #if(_VGA_SUPPORT == _ON)

typedef enum
{
    _PLL_FREQ_CHG_OVER_10PER = 0x00,
    _PLL_FREQ_CHG_UNDER_10PER,
} EnumDclkChg;

typedef enum
{
    _MPLL_NF_PLL = 0x00,
    _DPLL_NF_PLL,
} EnumPLLSel;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
extern void ScalerPLLSetM2PLLOffProc(void);
extern void ScalerPLLSetM2PLLOnProc(void);
#endif


#if(_HW_EPLL_SUPPORT == _ON)
extern void ScalerPLLSetEMCUPLLOffProc(void);
extern void ScalerPLLSetEMCUPLLOnProc(void);
#endif

#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
extern void ScalerPLLSetMPLLOffProc(DWORD ulFreq, DWORD ulRefClk);
extern void ScalerPLLSetMPLLOnProc(DWORD ulFreq, DWORD ulRefClk);
#endif

#if((_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
extern DWORD ScalerPLLCalNFCode(DWORD ulFreq, DWORD ulRefClk, BYTE ucPreDiv, BYTE ucPixelDiv2_DIV, EnumPLLSel enumPLLSel, EnumDclkChg enumDclkChg);
extern DWORD ScalerPLLCalPLLParameter(DWORD ulFreq, DWORD ulRefClk, BYTE ucPreDiv, BYTE ucPixelDiv2_DIV, EnumPLLSel enumPLLSel, EnumDclkChg enumDclkChg);
#endif

#if(_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
extern void ScalerPLLSetDPLLOffProc(DWORD ulFreq, DWORD ulRefClk);
extern void ScalerPLLSetDPLLOnProc(DWORD ulFreq, DWORD ulRefClk, EnumDclkChg enumDclkChg);
extern void ScalerPLLSetDPLLFreqNf(DWORD ulFreq);
#endif

#if(_VGA_SUPPORT == _ON)
extern void ScalerAPLLLockThdSet(WORD usHFreq);
extern BYTE ScalerAPLLGetAPLLGValue(WORD *pusDelta);
extern bit ScalerAPLLGetSumI(DWORD *pulDiv);
#endif

extern DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq);

#if(_PANEL_STYLE == _PANEL_LVDS)
extern void ScalerPLLSetDisplayPLL(DWORD ulFreq);
#endif



#endif // End of #ifndef __SCALER_PLL_H__
