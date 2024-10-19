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
// ID Code      : ScalerColorAntiAliasing.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_COLOR_IP_ANTI_ALIASING == _ON)
EnumAntiAliasingSupportStatus g_enumColorAntiAliasingTimingSupportInfo;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLOR_IP_ANTI_ALIASING == _ON)
//--------------------------------------------------
// Description  : Anti-Aliasing Initial Setting
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerColorAntiAliasingInitialSetting(void)
{
    // Get Input Path Support
    if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_M1_M2)
    {
        // Get Measure Timing Info Support
        g_enumColorAntiAliasingTimingSupportInfo = (EnumAntiAliasingSupportStatus)ScalerColorAntiAliasingGetMeasureTimingInfo();

        if(g_enumColorAntiAliasingTimingSupportInfo == _ANTI_ALIASING_SUPPORT)
        {
            StructColorAntiAliasingSetting stAntiAliasingData = {0};

            // Get Interface Inform
            ScalerColorAntiAliasingGetInterfaceInform(&stAntiAliasingData);

            // Timing & Region Support,
            ScalerColorAntiAliasingOnCtrlInitialSetting(&stAntiAliasingData);

            // if Timing & Region Support : power on
            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_ANTI_ALIASING_M1M2, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
        }
        else
        {
            // if Timing & Region Support : power off
            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_ANTI_ALIASING_M1M2, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
        }

        // Set AA bypass_en = ~(bInputTimingSupport)
        if(g_enumColorAntiAliasingTimingSupportInfo == _ANTI_ALIASING_SUPPORT)
        {
            ScalerColorAntiAliasingSetBypassEn(_FALSE);
        }
        else
        {
            ScalerColorAntiAliasingSetBypassEn(_TRUE);
        }
    }
}

//--------------------------------------------------
// Description  : Anti-Aliasing Clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorAntiAliasingClear(void)
{
    // set support info initial
    g_enumColorAntiAliasingTimingSupportInfo = _ANTI_ALIASING_NO_SUPPORT;

    // set aa_ip_en = disable
    Scaler32SetBit(PB00900_00_AA_CTRL_M1_000, ~_BIT0, 0x00);

    // set bypass_en, timing regen false
    Scaler32SetDWord(PB00900_E0_AA_ON_CTRL, 0x00000001UL);

    // set timing regen setting register = 0
    Scaler32SetDWord(PB00900_E4_AA_HOR_ACT_WID_L, 0x00000000UL);
    Scaler32SetDWord(PB00900_E8_AA_HOR_SYNC_WID_L, 0x00000000UL);

    // set power cut
    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_ANTI_ALIASING_M1M2, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
}

//--------------------------------------------------
// Description  : Anti-Aliasing Adjust
// Input Value  : StructUnionAntiAliasingSetting
// Output Value : None
//--------------------------------------------------
void ScalerColorAntiAliasingAdjust(DWORD *pulAntiAliasingSetting)
{
    WORD usTableSizeCnt = 0;

    for(usTableSizeCnt = 0; usTableSizeCnt < _ANTIALIASING_COEF_TABLE_SIZE; usTableSizeCnt++)
    {
        WORD usTableOffset = usTableSizeCnt * 2;
        Scaler32SetDWord(pulAntiAliasingSetting[usTableOffset], pulAntiAliasingSetting[usTableOffset + 1]);
    }
}

//--------------------------------------------------
// Description  : Anti-Aliasing Enable
// Input Value  : bit
// Output Value : None
//--------------------------------------------------
void ScalerColorAntiAliasingSetIPEnable(bit bOn)
{
    Scaler32SetBit(PB00900_00_AA_CTRL_M1_000, ~_BIT0, bOn);
}

//--------------------------------------------------
// Description  : Anti-Aliasing BypassEn Control
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerColorAntiAliasingSetBypassEn(bit bOn)
{
    Scaler32SetBit(PB00900_E0_AA_ON_CTRL, ~_BIT0, bOn);
}

//--------------------------------------------------
// Description  : Anti-Aliasing Get Measure Timing Inform
// Input Value  :
// Output Value : bit
//--------------------------------------------------
bit ScalerColorAntiAliasingGetMeasureTimingInfo(void)
{
    WORD usVTotal = GET_MDOMAIN_INPUT_VTOTAL();
    WORD usVHeight = GET_MDOMAIN_INPUT_VHEIGHT();
    WORD usVStart = GET_MDOMAIN_INPUT_VSTART();
    WORD usVBlank = (usVTotal > usVHeight) ? (usVTotal - usVHeight) : 0;
    WORD usVFront = (usVBlank > usVStart) ? (usVBlank - usVStart) : 0;

    // aa support : v front porch >= 4
    if(usVFront >= 4)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Anti-Aliasing Get Select Region & Timing Support
// Input Value  : EnumSelRegion
// Output Value : bit
//--------------------------------------------------
bit ScalerColorAntiAliasingGetSupport(EnumSelRegion enumSelRegion)
{
    if(g_enumColorAntiAliasingTimingSupportInfo == _ANTI_ALIASING_NONE)
    {
        return _FALSE;
    }

    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            return g_enumColorAntiAliasingTimingSupportInfo;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            return g_enumColorAntiAliasingTimingSupportInfo;

        case _2P_PIP_SUB:
            return _FALSE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            return g_enumColorAntiAliasingTimingSupportInfo;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            return _FALSE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
            return g_enumColorAntiAliasingTimingSupportInfo;

        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_L:
        case _2P_PBP_LR_EQUAL_R:
            return _FALSE;
#endif

        case _FULL_REGION:
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
            return g_enumColorAntiAliasingTimingSupportInfo;

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Anti-Aliasing Get Interface Information
// Input Value  : StructColorAntiAliasingSetting
// Output Value : None
//--------------------------------------------------
void ScalerColorAntiAliasingGetInterfaceInform(StructColorAntiAliasingSetting *pstAntiAliasingData)
{
    // Get V Scaling Down
    bit bM1VSDEn = (ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT0) == _BIT0);
    bit bM2VSDEn = (ScalerGetBit(P40_23_SCALE_DOWN_CTRL_M2, _BIT0) == _BIT0);

    // Get Drr Type
#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
    {
        pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.bDrrFlag = _TRUE;
    }
    else
#endif
    {
        pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.bDrrFlag = _FALSE;
    }

    // Get Inut Timing
    pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.usHTotal = GET_MDOMAIN_INPUT_HTOTAL();
    pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.usHWidth = GET_MDOMAIN_INPUT_HWIDTH();
    pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.usHSyncWidth = GET_MDOMAIN_INPUT_HSYNCWIDTH();
    pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.usVHeight = GET_MDOMAIN_INPUT_VHEIGHT();
    pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.bVsdEn = (bM1VSDEn | bM2VSDEn);
}

//--------------------------------------------------
// Description  : Anti-Aliasing Initial Setting
// Input Value  : StructColorAntiAliasingSetting
// Output Value : None
//--------------------------------------------------
void ScalerColorAntiAliasingOnCtrlInitialSetting(StructColorAntiAliasingSetting *pstAntiAliasingData)
{
    WORD usHTotal = pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.usHTotal;
    WORD usHWidth = pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.usHWidth;
    WORD usHSyncWidth = pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.usHSyncWidth;
    WORD usVHeight = pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.usVHeight;
    bit bVsdEn = pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.bVsdEn;
    bit bDrrFlag = pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.bDrrFlag;
    bit bVsRegenEn = !pstAntiAliasingData->stAntiAliasingSetting.stAntiAliasingOnSpecKernelData.bDrrFlag;
    BYTE ucDelayLine = ((bDrrFlag == _TRUE) ? (0x00) : (0x03));

    // read interface inform
    WORD usHW_L = ((usHWidth & 0x00FF) >> 0);
    WORD usHW_H = ((usHWidth & 0xFF00) >> 8);
    WORD usVH_L = ((usVHeight & 0x00FF) >> 0);
    WORD usVH_H = ((usVHeight & 0xFF00) >> 8);

    DWORD ulValueE0 = ((DWORD)bVsRegenEn << 15) | ((DWORD)ucDelayLine << 12) | (_BIT11) | ((DWORD)bVsdEn << 10);
    DWORD ulValueE4 = ((DWORD)usVH_H << 24) | ((DWORD)usVH_L << 16) | ((DWORD)usHW_H << 8) | ((DWORD)usHW_L);
    DWORD ulValueE8 = ((DWORD)usHTotal << 16) | ((DWORD)usHSyncWidth);

    // set B00900E8
    Scaler32SetDWord(PB00900_E8_AA_HOR_SYNC_WID_L, ulValueE8);

    // set B00900E4
    Scaler32SetDWord(PB00900_E4_AA_HOR_ACT_WID_L, ulValueE4);

    // wait ien_stop
    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);

    // Set B00900E0
    Scaler32SetDWord(PB00900_E0_AA_ON_CTRL, ulValueE0);
}
#endif
