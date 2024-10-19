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
// ID Code      : ScalerDDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDOMAIN__

#include "ScalerFunctionInclude.h"
#include "DDomain/ScalerDDomain.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PANEL_EXIST_MULTIPANEL == _ON)
BYTE g_ucDDomainPanelIndex;
#endif

StructDDomainRegionInfo g_pstDDomainRegionInfo[_HW_D_DOMAIN_PATH_COUNT] =
{
#if(_HW_D_DOMAIN_R1_A1_ACTIVE_SUPPORT == _ON)
    {_DDOMAIN_RGN_R1_A1, P0_32_SCALE_CONTROL_REG_R1_ACTIVE1, P0_33_SF_ADDR_PORT_R1_ACTIVE1},
#endif

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    {_DDOMAIN_RGN_R1_A2, P0_38_SCALE_CONTROL_REG_R1_ACTIVE2, P0_39_SF_ADDR_PORT_R1_ACTIVE2},
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    {_DDOMAIN_RGN_R2_A1, P80_32_SCALE_CONTROL_REG_R2_ACTIVE1, P80_33_SF_ADDR_PORT_R2_ACTIVE1},
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
    {_DDOMAIN_RGN_R2_A2, P80_38_SCALE_CONTROL_REG_R2_ACTIVE2, P80_39_SF_ADDR_PORT_R2_ACTIVE2},
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
    {_DDOMAIN_RGN_R3_A1, PC0_32_SCALE_CONTROL_REG_R3_ACTIVE1, PC0_33_SF_ADDR_PORT_R3_ACTIVE1},
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
    {_DDOMAIN_RGN_R3_A2, PC0_38_SCALE_CONTROL_REG_R3_ACTIVE2, PC0_39_SF_ADDR_PORT_R3_ACTIVE2},
#endif
};

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Convert output region to D-domain register page
// Input Value  : enumDDomainRegion -> Output region
// Output Value : D-domain register page recorded in #g_pstDDomainPathInfo
//--------------------------------------------------
WORD ScalerDDomainGetScalingUpPageAddr(EnumDDomainRegion enumDDomainRegion)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumDDomainRegion enumCurrRegion = GET_DDOMAIN_OUTPUT_REGION(ucIndex);

        if((enumDDomainRegion & enumCurrRegion) != 0x00)
        {
            return GET_DDOMAIN_SU_PAGE_ADDR(ucIndex);
        }
    }

    return GET_DDOMAIN_SU_PAGE_ADDR(0);
}

//--------------------------------------------------
// Description  : Convert output region to D-domain register page
// Input Value  : enumDDomainRegion -> Output region
// Output Value : D-domain register page recorded in #g_pstDDomainPathInfo
//--------------------------------------------------
WORD ScalerDDomainGetScalingFactorPageAddr(EnumDDomainRegion enumDDomainRegion)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumDDomainRegion enumCurrRegion = GET_DDOMAIN_OUTPUT_REGION(ucIndex);

        if((enumDDomainRegion & enumCurrRegion) != 0x00)
        {
            return GET_DDOMAIN_SF_PAGE_ADDR(ucIndex);
        }
    }

    return GET_DDOMAIN_SF_PAGE_ADDR(0);
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayFormat_R1a1(EnumDisplayFormatItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_TOTAL:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, _AUTOINC) + _PANEL_DHTOTAL_SETTING_COMPLEMENT;
            return (usData & _HW_DIS_TIMING_GEN_HTOTAL_BIT);

        case _DISPLAY_FORMAT_HS_WIDTH:
            usData = ScalerGetDataPortSingleByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END);
            return usData;

        case _DISPLAY_FORMAT_H_START:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R1_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_END:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_07_DISPLAY_HOR_ACT_END_H_R1_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_WIDTH:
            // H end - H start
            usData = (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_07_DISPLAY_HOR_ACT_END_H_R1_1, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R1_1, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_FORMAT_V_TOTAL:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_VTOTAL_BIT);

        case _DISPLAY_FORMAT_VS_WIDTH:
            usData = ScalerGetDataPortSingleByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0D_DISPLAY_VER_SYNC_END);
            return usData;

        case _DISPLAY_FORMAT_V_START:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H_R1_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_END:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H_R1_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_HEIGHT:
            usData = (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H_R1_1, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H_R1_1, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  :
//    enumItem --> target format item
//    usData --> data to be set
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayFormat_R1a1(EnumDisplayFormatItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_TOTAL:
            usData -= ((usData >= _PANEL_DHTOTAL_SETTING_COMPLEMENT) ? _PANEL_DHTOTAL_SETTING_COMPLEMENT : 0);
            usData &= _HW_DIS_TIMING_GEN_HTOTAL_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, usData);
            break;

        case _DISPLAY_FORMAT_HS_WIDTH:
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END, (BYTE)usData);
            break;

        case _DISPLAY_FORMAT_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R1_1, usData);
            break;

        case _DISPLAY_FORMAT_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_07_DISPLAY_HOR_ACT_END_H_R1_1, usData);
            break;

        case _DISPLAY_FORMAT_V_TOTAL:
            usData &= _HW_DIS_TIMING_GEN_VTOTAL_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H, usData);
            break;

        case _DISPLAY_FORMAT_VS_WIDTH:
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0D_DISPLAY_VER_SYNC_END, (BYTE)usData);
            break;

        case _DISPLAY_FORMAT_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H_R1_1, usData);
            break;

        case _DISPLAY_FORMAT_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H_R1_1, usData);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayBackground_R1(EnumDisplayBackgroundItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H_R1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_H_END:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H_R1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_H_WIDTH:
            usData = (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H_R1, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H_R1, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_BACKGROUND_V_START:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H_R1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_V_END:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H_R1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_V_HEIGHT:
            usData = (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H_R1, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H_R1, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// usData --> target value
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayBackground_R1(EnumDisplayBackgroundItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H_R1, usData);
            break;

        case _DISPLAY_BACKGROUND_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H_R1, usData);
            break;

        case _DISPLAY_BACKGROUND_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H_R1, usData);
            break;

        case _DISPLAY_BACKGROUND_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H_R1, usData);
            break;

        default:
            break;
    }
}

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayFormat_R1a2(EnumDisplayFormatItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R1_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_END:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_18_DISPLAY_HOR_ACT_END_H_R1_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_WIDTH:
            usData = (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_18_DISPLAY_HOR_ACT_END_H_R1_2, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R1_2, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_FORMAT_V_START:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R1_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_END:
            usData = ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1C_DISPLAY_VER_ACT_END_H_R1_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_HEIGHT:
            usData = (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1C_DISPLAY_VER_ACT_END_H_R1_2, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R1_2, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  :
//    enumItem --> target format item
//    usData --> data to be set
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayFormat_R1a2(EnumDisplayFormatItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R1_2, usData);
            break;

        case _DISPLAY_FORMAT_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_18_DISPLAY_HOR_ACT_END_H_R1_2, usData);
            break;

        case _DISPLAY_FORMAT_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R1_2, usData);
            break;

        case _DISPLAY_FORMAT_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1C_DISPLAY_VER_ACT_END_H_R1_2, usData);
            break;

        default:
            break;
    }
}
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayFormat_R2a1(EnumDisplayFormatItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R2_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_END:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_07_DISPLAY_HOR_ACT_END_H_R2_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_WIDTH:
            usData = (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_07_DISPLAY_HOR_ACT_END_H_R2_1, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R2_1, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_FORMAT_V_START:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_10_DISPLAY_VER_ACT_STA_H_R2_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_END:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_12_DISPLAY_VER_ACT_END_H_R2_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_HEIGHT:
            usData = (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_12_DISPLAY_VER_ACT_END_H_R2_1, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_10_DISPLAY_VER_ACT_STA_H_R2_1, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  :
//    enumItem --> target format item
//    usData --> data to be set
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayFormat_R2a1(EnumDisplayFormatItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R2_1, usData);
            break;

        case _DISPLAY_FORMAT_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_07_DISPLAY_HOR_ACT_END_H_R2_1, usData);
            break;

        case _DISPLAY_FORMAT_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_10_DISPLAY_VER_ACT_STA_H_R2_1, usData);
            break;

        case _DISPLAY_FORMAT_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_12_DISPLAY_VER_ACT_END_H_R2_1, usData);
            break;

        default:
            break;
    }
}
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayBackground_R2(EnumDisplayBackgroundItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_03_DISPLAY_HOR_BG_STA_H_R2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_H_END:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_09_DISPLAY_HOR_BG_END_H_R2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_H_WIDTH:
            usData = (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_09_DISPLAY_HOR_BG_END_H_R2, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_03_DISPLAY_HOR_BG_STA_H_R2, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_BACKGROUND_V_START:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_0E_DISPLAY_VER_BG_STA_H_S_R2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_V_END:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_14_DISPLAY_VER_BG_END_H_R2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_V_HEIGHT:
            usData = (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_14_DISPLAY_VER_BG_END_H_R2, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_0E_DISPLAY_VER_BG_STA_H_S_R2, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// usData --> target value
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayBackground_R2(EnumDisplayBackgroundItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_03_DISPLAY_HOR_BG_STA_H_R2, usData);
            break;

        case _DISPLAY_BACKGROUND_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_09_DISPLAY_HOR_BG_END_H_R2, usData);
            break;

        case _DISPLAY_BACKGROUND_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_0E_DISPLAY_VER_BG_STA_H_S_R2, usData);
            break;

        case _DISPLAY_BACKGROUND_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_14_DISPLAY_VER_BG_END_H_R2, usData);
            break;

        default:
            break;
    }
}
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayFormat_R2a2(EnumDisplayFormatItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R2_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_END:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_18_DISPLAY_HOR_ACT_END_H_R2_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_WIDTH:
            usData = (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_18_DISPLAY_HOR_ACT_END_H_R2_2, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R2_2, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_FORMAT_V_START:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R2_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_END:
            usData = ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_1C_DISPLAY_VER_ACT_END_H_R2_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_HEIGHT:
            usData = (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_1C_DISPLAY_VER_ACT_END_H_R2_2, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R2_2, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  :
//    enumItem --> target format item
//    usData --> data to be set
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayFormat_R2a2(EnumDisplayFormatItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R2_2, usData);
            break;

        case _DISPLAY_FORMAT_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_18_DISPLAY_HOR_ACT_END_H_R2_2, usData);
            break;

        case _DISPLAY_FORMAT_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R2_2, usData);
            break;

        case _DISPLAY_FORMAT_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_1C_DISPLAY_VER_ACT_END_H_R2_2, usData);
            break;

        default:
            break;
    }
}
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayBackground_R3(EnumDisplayBackgroundItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_03_DISPLAY_HOR_BG_STA_H_R3, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_H_END:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_09_DISPLAY_HOR_BG_END_H_R3, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_H_WIDTH:
            usData = (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_09_DISPLAY_HOR_BG_END_H_R3, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_03_DISPLAY_HOR_BG_STA_H_R3, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_BACKGROUND_V_START:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_0E_DISPLAY_VER_BG_STA_H_S_R3, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_V_END:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_14_DISPLAY_VER_BG_END_H_R3, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_BACKGROUND_V_HEIGHT:
            usData = (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_14_DISPLAY_VER_BG_END_H_R3, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_0E_DISPLAY_VER_BG_STA_H_S_R3, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// usData --> target value
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayBackground_R3(EnumDisplayBackgroundItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_03_DISPLAY_HOR_BG_STA_H_R3, usData);
            break;

        case _DISPLAY_BACKGROUND_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_09_DISPLAY_HOR_BG_END_H_R3, usData);
            break;

        case _DISPLAY_BACKGROUND_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_0E_DISPLAY_VER_BG_STA_H_S_R3, usData);
            break;

        case _DISPLAY_BACKGROUND_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_14_DISPLAY_VER_BG_END_H_R3, usData);
            break;

        default:
            break;
    }
}
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayFormat_R3a1(EnumDisplayFormatItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R3_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_END:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_07_DISPLAY_HOR_ACT_END_H_R3_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_WIDTH:
            usData = (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_07_DISPLAY_HOR_ACT_END_H_R3_1, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R3_1, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_FORMAT_V_START:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_10_DISPLAY_VER_ACT_STA_H_R3_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_END:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_12_DISPLAY_VER_ACT_END_H_R3_1, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_HEIGHT:
            usData = (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_12_DISPLAY_VER_ACT_END_H_R3_1, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_10_DISPLAY_VER_ACT_STA_H_R3_1, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  :
//    enumItem --> target format item
//    usData --> data to be set
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayFormat_R3a1(EnumDisplayFormatItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_05_DISPLAY_HOR_ACT_STA_H_R3_1, usData);
            break;

        case _DISPLAY_FORMAT_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_07_DISPLAY_HOR_ACT_END_H_R3_1, usData);
            break;

        case _DISPLAY_FORMAT_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_10_DISPLAY_VER_ACT_STA_H_R3_1, usData);
            break;

        case _DISPLAY_FORMAT_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_12_DISPLAY_VER_ACT_END_H_R3_1, usData);
            break;

        default:
            break;
    }
}
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD ScalerDDomainGetDisplayFormat_R3a2(EnumDisplayFormatItem enumItem)
{
    WORD usData = 0;

    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R3_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_END:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_18_DISPLAY_HOR_ACT_END_H_R3_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);

        case _DISPLAY_FORMAT_H_WIDTH:
            usData = (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_18_DISPLAY_HOR_ACT_END_H_R3_2, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R3_2, _AUTOINC) & _HW_DIS_TIMING_GEN_H_ACTIVE_BIT);
            return usData;

        case _DISPLAY_FORMAT_V_START:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R3_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_END:
            usData = ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1C_DISPLAY_VER_ACT_END_H_R3_2, _AUTOINC);
            return (usData & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);

        case _DISPLAY_FORMAT_V_HEIGHT:
            usData = (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1C_DISPLAY_VER_ACT_END_H_R3_2, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            usData -= (ScalerGetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R3_2, _AUTOINC) & _HW_DIS_TIMING_GEN_V_ACTIVE_BIT);
            return usData;

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  :
//    enumItem --> target format item
//    usData --> data to be set
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDisplayFormat_R3a2(EnumDisplayFormatItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_R3_2, usData);
            break;

        case _DISPLAY_FORMAT_H_END:
            usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_18_DISPLAY_HOR_ACT_END_H_R3_2, usData);
            break;

        case _DISPLAY_FORMAT_V_START:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_R3_2, usData);
            break;

        case _DISPLAY_FORMAT_V_END:
            usData &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;
            ScalerSetDataPortWord(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1C_DISPLAY_VER_ACT_END_H_R3_2, usData);
            break;

        default:
            break;
    }
}
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get FB None Seperate Mode R1a1 Active Hwidth
// Input Value  : None
// Output Value : R1a1 Active Hwidth
//--------------------------------------------------
WORD ScalerDDomainGetFBNoneSepR1a1ActiveHwidth(void)
{
    WORD usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END)) / 2;

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE)
    {
        return 0;
    }

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
        case _DISPLAY_MODE_2P_PBP_TB:
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            return usMidline - ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);

        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
            {
                return ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH);
            }
            else
            {
                return usMidline - ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
            }

        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
            {
                return 0;
            }
            else
            {
                return usMidline - ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
            }

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get FB None Seperate Mode R3a1 Active Hwidth
// Input Value  : None
// Output Value : R3a1 Active Hwidth
//--------------------------------------------------
WORD ScalerDDomainGetFBNoneSepR3a1ActiveHwidth(void)
{
    WORD usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END)) / 2;

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE)
    {
        return 0;
    }

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
        case _DISPLAY_MODE_2P_PBP_TB:
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            return ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END) - usMidline;

        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
            {
                return 0;
            }
            else
            {
                return ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END) - usMidline;
            }

        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
            {
                return ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH);
            }
            else
            {
                return ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END) - usMidline;
            }

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get FB None Seperate Mode R1a2 Active Hwidth
// Input Value  : None
// Output Value : R1a2 Active Hwidth
//--------------------------------------------------
WORD ScalerDDomainGetFBNoneSepR1a2ActiveHwidth(void)
{
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    WORD usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END)) / 2;
#endif

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE)
    {
        return 0;
    }

    switch(GET_DISPLAY_MODE())
    {
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
        case _DISPLAY_MODE_3P_SKEW_B:
            return usMidline - ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START);
#endif
        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Get FB None Seperate Mode R3a2 Active Hwidth
// Input Value  : None
// Output Value : R1a2 Active Hwidth
//--------------------------------------------------
WORD ScalerDDomainGetFBNoneSepR3a2ActiveHwidth(void)
{
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    WORD usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END)) / 2;
#endif

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE)
    {
        return 0;
    }

    switch(GET_DISPLAY_MODE())
    {
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
        case _DISPLAY_MODE_3P_SKEW_B:
            return ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END) - usMidline;
#endif
        default:
            return 0;
    }
}
#endif
//--------------------------------------------------
// Description  : Get Display Background Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDDomainGetBackgroundStatus(EnumDDomainRegion enumDDomainRegion)
{
    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A1) == _DDOMAIN_RGN_R1_A1)
    {
        if(ScalerGetBit(P80_A1_BG_COLOR_CONTROL_R1, _BIT7) != 0)
        {
            return _TRUE;
        }

        return _FALSE;
    }

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A2) == _DDOMAIN_RGN_R1_A2)
    {
        if(ScalerGetBit(P80_A1_BG_COLOR_CONTROL_R1, _BIT6) != 0)
        {
            return _TRUE;
        }

        return _FALSE;
    }
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A1) == _DDOMAIN_RGN_R2_A1)
    {
        if(ScalerGetBit(P80_AB_BG_COLOR_CONTROL_R2, _BIT7) != 0)
        {
            return _TRUE;
        }

        return _FALSE;
    }
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A2) == _DDOMAIN_RGN_R2_A2)
    {
        if(ScalerGetBit(P80_AB_BG_COLOR_CONTROL_R2, _BIT6) != 0)
        {
            return _TRUE;
        }

        return _FALSE;
    }
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A1) == _DDOMAIN_RGN_R3_A1)
    {
        if(ScalerGetBit(P80_B5_FORCE_TO_BG_ENABLE_R3, _BIT7) != 0)
        {
            return _TRUE;
        }

        return _FALSE;
    }
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A2) == _DDOMAIN_RGN_R3_A2)
    {
        if(ScalerGetBit(P80_B5_FORCE_TO_BG_ENABLE_R3, _BIT6) != 0)
        {
            return _TRUE;
        }

        return _FALSE;
    }
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Display Force to Background Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundEnableByRegion(EnumDisplayRegion enumDisplayRegion, bit bEnable)
{
    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(enumDisplayRegion);
    ScalerDDomainBackgroundEnable(enumDDomainRegion, bEnable);
}

#if((_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set active1/2 boundary for different Background Color
// Input Value  : DisplayMode
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetBackgroundVerticalChange(EnumDisplayMode enumDisplayMode)
{
    WORD usMidline = 0;

    usMidline = usMidline;

    // Initial Vertical Change
    ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT5, 0x00);

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
    ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~_BIT5, 0x00);
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
    ScalerSetBit(P80_B5_FORCE_TO_BG_ENABLE_R3, ~_BIT5, 0x00);
#endif

    switch(enumDisplayMode)
    {
        case _DISPLAY_MODE_1P:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#endif
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
#endif
        default:
            break;

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            // Enable R1 Vertical Change
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT5, _BIT5);

            // Set Vertical Change Midline
            usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END)) / 2;
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usMidline) & 0x1F));
            ScalerSetByte(P80_A2_BG_COLOR_VC_START_L, LOBYTE(usMidline));
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_3P_SKEW_B:
            // Enable Vertical Change
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT5, _BIT5);

            // Set Vertical Change Midline
            usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END)) / 2;
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usMidline) & 0x1F));
            ScalerSetByte(P80_A2_BG_COLOR_VC_START_L, LOBYTE(usMidline));
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_R:
            // Enable R1 Vertical Change
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT5, _BIT5);

            // Set R1 Vertical Change Midline
            usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END)) / 2;
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usMidline) & 0x1F));
            ScalerSetByte(P80_A2_BG_COLOR_VC_START_L, LOBYTE(usMidline));
            break;

        case _DISPLAY_MODE_3P_SKEW_L:
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            // Enable R2 Vertical Change
            ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~_BIT5, _BIT5);

            // Set R2 Vertical Change Midline
            usMidline = (ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_START) + ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_END)) / 2;
            ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usMidline) & 0x1F));
            ScalerSetByte(P80_AC_BG_COLOR_VC_START_L_R2, LOBYTE(usMidline));
#endif
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            // Enable R1/R2 Vertical Change
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT5, _BIT5);
            ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~_BIT5, _BIT5);

            // Set R1 Vertical Change Midline
            usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END)) / 2;
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usMidline) & 0x1F));
            ScalerSetByte(P80_A2_BG_COLOR_VC_START_L, LOBYTE(usMidline));

            // Set R2 Vertical Change Midline
            usMidline = (ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_START) + ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_END)) / 2;
            ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usMidline) & 0x1F));
            ScalerSetByte(P80_AC_BG_COLOR_VC_START_L_R2, LOBYTE(usMidline));
#endif
            break;
#endif
    }
}
#endif

//--------------------------------------------------
// Description  : Display Force to Background Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundEnable(EnumDDomainRegion enumDDomainRegion, bit bEnable)
{
#if(_DM_FUNCTION == _ON)
    EnumDDomainRegion enumDMMuteDDomainRegion = ScalerDMGetDDomainRegionMuteStatus();
    if((bEnable == _DISABLE) && (enumDMMuteDDomainRegion != _DDOMAIN_RGN_NONE))
    {
        enumDDomainRegion &= (~enumDMMuteDDomainRegion & _DDOMAIN_RGN_ALL);
    }
#endif

    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A1) == _DDOMAIN_RGN_R1_A1)
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            // S1 Enable Force to Back Ground
            enumDDomainRegion |= _DDOMAIN_RGN_R2_A1;
        }
#endif
        if(bEnable == _ENABLE)
        {
            // R1a1 Enable Force to Back Ground
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT7, _BIT7);
        }
        else
        {
            // R1a1 Disable Force to Back Ground
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT7, 0x00);
        }
    }

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A2) == _DDOMAIN_RGN_R1_A2)
    {
        if(bEnable == _ENABLE)
        {
            // R1a2 Enable Force to Back Ground
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT6, _BIT6);
        }
        else
        {
            // R1a2 Disable Force to Back Ground
            ScalerSetBit(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT6, 0x00);
        }
    }
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A1) == _DDOMAIN_RGN_R2_A1)
    {
        if(bEnable == _ENABLE)
        {
            // R2a1 Enable Force to Back Ground
            ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~_BIT7, _BIT7);
        }
        else
        {
            // R2a1 Disable Force to Back Ground
            ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~_BIT7, 0x00);
        }
    }
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A2) == _DDOMAIN_RGN_R2_A2)
    {
        if(bEnable == _ENABLE)
        {
            // R2a2 Enable Force to Back Ground
            ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~_BIT6, _BIT6);
        }
        else
        {
            // R2a1 Disable Force to Back Ground
            ScalerSetBit(P80_AB_BG_COLOR_CONTROL_R2, ~_BIT6, 0x00);
        }
    }
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A1) == _DDOMAIN_RGN_R3_A1)
    {
        if(bEnable == _ENABLE)
        {
            // R3a1 Enable Force to Back Ground
            ScalerSetBit(P80_B5_FORCE_TO_BG_ENABLE_R3, ~_BIT7, _BIT7);
        }
        else
        {
            // R3a1 Disable Force to Back Ground
            ScalerSetBit(P80_B5_FORCE_TO_BG_ENABLE_R3, ~_BIT7, 0x00);
        }
    }
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A2) == _DDOMAIN_RGN_R3_A2)
    {
        if(bEnable == _ENABLE)
        {
            // R3a2 Enable Force to Back Ground
            ScalerSetBit(P80_B5_FORCE_TO_BG_ENABLE_R3, ~_BIT6, _BIT6);
        }
        else
        {
            // R3a2 Disable Force to Back Ground
            ScalerSetBit(P80_B5_FORCE_TO_BG_ENABLE_R3, ~_BIT6, 0x00);
        }
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : Check Force Background
// Input Value  : enumSelRegion
// Output Value : none
//--------------------------------------------------
bit ScalerDDomainBackgroundCheck(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_1P)));

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PIP_MAIN)));
        case _2P_PIP_SUB:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PIP_SUB)));
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_EAGLE_SIGHT_MAIN)));
        case _2P_PIP_EAGLE_SIGHT_SUB:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_EAGLE_SIGHT_SUB)));
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT)));
        case _2P_PBP_LR_EQUAL_R:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT)));
        case _2P_PBP_LR_L_LARGE_L:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_L_LARGE_LEFT)));
        case _2P_PBP_LR_L_LARGE_R:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT)));
        case _2P_PBP_LR_R_LARGE_L:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT)));
        case _2P_PBP_LR_R_LARGE_R:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT)));
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_TOP)));
        case _2P_PBP_TB_B:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_BOTTOM)));
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_MAIN));
        case _3P_SKEW_L_T:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_TOP));
        case _3P_SKEW_L_B:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_BOTTOM));
        case _3P_SKEW_R_M:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_MAIN));
        case _3P_SKEW_R_T:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_TOP));
        case _3P_SKEW_R_B:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_BOTTOM));
        case _3P_SKEW_L_M_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_TOP)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_BOTTOM)));
        case _3P_SKEW_L_T_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_MAIN)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_BOTTOM)));
        case _3P_SKEW_L_B_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_TOP)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_MAIN)));
        case _3P_SKEW_R_M_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_TOP)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_BOTTOM)));
        case _3P_SKEW_R_T_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_MAIN)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_BOTTOM)));
        case _3P_SKEW_R_B_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_TOP)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_MAIN)));
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_MAIN));
        case _3P_SKEW_T_L:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_LEFT));
        case _3P_SKEW_T_R:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_RIGHT));
        case _3P_SKEW_B_M:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_MAIN));
        case _3P_SKEW_B_L:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_LEFT));
        case _3P_SKEW_B_R:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_RIGHT));
        case _3P_SKEW_T_M_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_LEFT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_RIGHT)));
        case _3P_SKEW_T_L_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_MAIN)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_RIGHT)));
        case _3P_SKEW_T_R_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_LEFT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_MAIN)));
        case _3P_SKEW_B_M_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_LEFT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_RIGHT)));
        case _3P_SKEW_B_L_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_MAIN)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_RIGHT)));
        case _3P_SKEW_B_R_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_LEFT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_MAIN)));
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_L:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_LEFT));
        case _3P_FLAG_M:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_MAIN));
        case _3P_FLAG_R:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_RIGHT));
        case _3P_FLAG_L_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_MAIN)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_RIGHT)));
        case _3P_FLAG_M_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_LEFT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_RIGHT)));
        case _3P_FLAG_R_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_LEFT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_MAIN)));
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LT));
        case _4P_LB:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LB));
        case _4P_RT:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RT));
        case _4P_RB:
            return ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RB));
        case _4P_LT_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LB)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RB)));
        case _4P_LB_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RB)));
        case _4P_RT_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LB)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RB)));
        case _4P_RB_OUTSIDE:
            return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LT)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LB)) &&
                    ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RT)));
#endif

        case _FULL_REGION:
            switch(GET_DISPLAY_MODE())
            {
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT)));
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_L_LARGE_LEFT)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT)));
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT)));
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PIP_MAIN)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PIP_SUB)));
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_EAGLE_SIGHT_MAIN)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_EAGLE_SIGHT_SUB)));
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_TOP)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_BOTTOM)));
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_MAIN)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_LEFT)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_FLAG_RIGHT)));
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_L:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_MAIN)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_TOP)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_L_BOTTOM)));
                case _DISPLAY_MODE_3P_SKEW_R:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_MAIN)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_TOP)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_R_BOTTOM)));
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_MAIN)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_LEFT)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_T_RIGHT)));
                case _DISPLAY_MODE_3P_SKEW_B:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_MAIN)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_LEFT)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_SKEW_B_RIGHT)));
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LT)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_LB)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RT)) &&
                            ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_RB)));
#endif
                case _DISPLAY_MODE_1P:
                default:
                    return (ScalerDDomainGetBackgroundStatus(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_1P)));
                    break;
            }
            break;
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
        default:
            break;
    }
    return _FALSE;
}
//--------------------------------------------------
// Description  : Set Display Background Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundSetColorByRegion(EnumDisplayRegion enumDisplayRegion, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply)
{
    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(enumDisplayRegion);
    ScalerDDomainBackgroundSetColor(enumDDomainRegion, ucRed, ucGreen, ucBlue, enumDBApply);
}

//--------------------------------------------------
// Description  : Set Display Background Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundSetColor(EnumDDomainRegion enumDDomainRegion, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply)
{
    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A1) == _DDOMAIN_RGN_R1_A1)
    {
        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P80_A3_BG_COLOR_R_R1_ACTIVE1, ucRed);
        ScalerSetByte(P80_A4_BG_COLOR_G_R1_ACTIVE1, ucGreen);
        ScalerSetByte(P80_A5_BG_COLOR_B_R1_ACTIVE1, ucBlue);
        ScalerSetByte(P80_A6_BG_COLOR_RGB_R1_ACTIVE1, 0x00);
    }

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A2) == _DDOMAIN_RGN_R1_A2)
    {
        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P80_A7_BG_COLOR_R_R1_ACTIVE2, ucRed);
        ScalerSetByte(P80_A8_BG_COLOR_G_R1_ACTIVE2, ucGreen);
        ScalerSetByte(P80_A9_BG_COLOR_B_R1_ACTIVE2, ucBlue);
        ScalerSetByte(P80_AA_BG_COLOR_RGB_R1_ACTIVE2, 0x00);
    }
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A1) == _DDOMAIN_RGN_R2_A1)
    {
        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P80_AD_BG_COLOR_R_R2_ACTIVE1, ucRed);
        ScalerSetByte(P80_AE_BG_COLOR_G_R2_ACTIVE1, ucGreen);
        ScalerSetByte(P80_AF_BG_COLOR_B_R2_ACTIVE1, ucBlue);
        ScalerSetByte(P80_B0_BG_COLOR_RGB_R2_ACTIVE1, 0x00);
    }
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A2) == _DDOMAIN_RGN_R2_A2)
    {
        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P80_B1_BG_COLOR_R_R2_ACTIVE2, ucRed);
        ScalerSetByte(P80_B2_BG_COLOR_G_R2_ACTIVE2, ucGreen);
        ScalerSetByte(P80_B3_BG_COLOR_B_R2_ACTIVE2, ucBlue);
        ScalerSetByte(P80_B4_BG_COLOR_RGB_R2_ACTIVE2, 0x00);
    }
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A1) == _DDOMAIN_RGN_R3_A1)
    {
        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P80_B7_BG_COLOR_R_R3_ACTIVE1, ucRed);
        ScalerSetByte(P80_B8_BG_COLOR_G_R3_ACTIVE1, ucGreen);
        ScalerSetByte(P80_B9_BG_COLOR_B_R3_ACTIVE1, ucBlue);
        ScalerSetByte(P80_BA_BG_COLOR_RGB_R3_ACTIVE1, 0x00);
    }
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A2) == _DDOMAIN_RGN_R3_A2)
    {
        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P80_BB_BG_COLOR_R_R3_ACTIVE2, ucRed);
        ScalerSetByte(P80_BC_BG_COLOR_G_R3_ACTIVE2, ucGreen);
        ScalerSetByte(P80_BD_BG_COLOR_B_R3_ACTIVE2, ucBlue);
        ScalerSetByte(P80_BE_BG_COLOR_RGB_R3_ACTIVE2, 0x00);
    }
#endif
#endif
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Display Pattern Gen Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable D Domain PG
        ScalerSetBit(P7_F0_DISP_PG_R_CTRL_R1, ~_BIT7, _BIT7);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            ScalerSetBit(P1A_F0_DISP_PG_R_CTRL_R3, ~_BIT7, _BIT7);
        }
#endif
    }
    else
    {
        // Disable D Domain PG
        ScalerSetBit(P7_F0_DISP_PG_R_CTRL_R1, ~_BIT7, 0x00);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            ScalerSetBit(P1A_F0_DISP_PG_R_CTRL_R3, ~_BIT7, 0x00);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Mode
// Input Value  : EnumDPatternGenMode
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenModeAdjust(EnumDPatternGenMode enumDPatternGenMode)
{
    switch(enumDPatternGenMode)
    {
        default:
        case _D_PATTERN_GEN_PROGRAMMABLE_MODE:
            ScalerSetBit(P7_F0_DISP_PG_R_CTRL_R1, ~_BIT6, 0x00);
            ScalerSetBit(P7_F1_DISP_PG_G_CTRL_R1, ~_BIT6, 0x00);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerSetBit(P1A_F0_DISP_PG_R_CTRL_R3, ~_BIT6, 0x00);
                ScalerSetBit(P1A_F1_DISP_PG_G_CTRL_R3, ~_BIT6, 0x00);
            }
#endif
            break;

        case _D_PATTERN_GEN_BOX_MODE:
            ScalerSetBit(P7_F0_DISP_PG_R_CTRL_R1, ~_BIT6, 0x00);
            ScalerSetBit(P7_F1_DISP_PG_G_CTRL_R1, ~_BIT6, _BIT6);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerSetBit(P1A_F0_DISP_PG_R_CTRL_R3, ~_BIT6, 0x00);
                ScalerSetBit(P1A_F1_DISP_PG_G_CTRL_R3, ~_BIT6, _BIT6);
            }
#endif
            break;
    }
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenAdjustColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL_R1, ucRed);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL_R1, ucGreen);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL_R1, ucBlue);
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L_R1, 0x00);
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL_R1, 0x00);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerSetByte(P1A_F3_DISP_PG_R_INITIAL_R3, ucRed);
        ScalerSetByte(P1A_F4_DISP_PG_G_INITIAL_R3, ucGreen);
        ScalerSetByte(P1A_F5_DISP_PG_B_INITIAL_R3, ucBlue);
        ScalerSetByte(P1A_FC_D_PG_INITIAL_M_STEP_L_R3, 0x00);
        ScalerSetByte(P1A_FD_D_PG_INITIAL_L_CTRL_R3, 0x00);
    }
#endif
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue) // 10bit
{
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL_R1, (usRed >> 2));
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL_R1, (usGreen >> 2));
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL_R1, (usBlue >> 2));
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L_R1, ((usRed & 0x03) << 4) | ((usGreen & 0x03) << 2) | (usBlue & 0x03));
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL_R1, 0x00);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerSetByte(P1A_F3_DISP_PG_R_INITIAL_R3, (usRed >> 2));
        ScalerSetByte(P1A_F4_DISP_PG_G_INITIAL_R3, (usGreen >> 2));
        ScalerSetByte(P1A_F5_DISP_PG_B_INITIAL_R3, (usBlue >> 2));
        ScalerSetByte(P1A_FC_D_PG_INITIAL_M_STEP_L_R3, ((usRed & 0x03) << 4) | ((usGreen & 0x03) << 2) | (usBlue & 0x03));
        ScalerSetByte(P1A_FD_D_PG_INITIAL_L_CTRL_R3, 0x00);
    }
#endif
}

//--------------------------------------------------
// Description  : Set Display Inside Box Pattern Gen Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBoxPatternGenAdjustColor10bit_Inside(WORD usRed, WORD usGreen, WORD usBlue)
{
    ScalerSetByte(P7_C2_DISP_PG_BOX_COLOR_CODE_5_R1, ((usBlue >> 6) & 0x0F));
    ScalerSetByte(P7_C3_DISP_PG_BOX_COLOR_CODE_6_R1, (((usRed >> 6) & 0x0F) << 4) | ((usGreen >> 6) & 0x0F));
    ScalerSetByte(P7_C4_DISP_PG_BOX_COLOR_CODE_7_R1, ((usRed & 0x3F) << 2));
    ScalerSetByte(P7_C5_DISP_PG_BOX_COLOR_CODE_8_R1, ((usGreen & 0x3F) << 2));
    ScalerSetByte(P7_C6_DISP_PG_BOX_COLOR_CODE_9_R1, ((usBlue & 0x3F) << 2));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerSetByte(P1A_C2_DISP_PG_BOX_COLOR_CODE_5_R3, ((usBlue >> 6) & 0x0F));
        ScalerSetByte(P1A_C3_DISP_PG_BOX_COLOR_CODE_6_R3, (((usRed >> 6) & 0x0F) << 4) | ((usGreen >> 6) & 0x0F));
        ScalerSetByte(P1A_C4_DISP_PG_BOX_COLOR_CODE_7_R3, ((usRed & 0x3F) << 2));
        ScalerSetByte(P1A_C5_DISP_PG_BOX_COLOR_CODE_8_R3, ((usGreen & 0x3F) << 2));
        ScalerSetByte(P1A_C6_DISP_PG_BOX_COLOR_CODE_9_R3, ((usBlue & 0x3F) << 2));
    }
#endif
}

//--------------------------------------------------
// Description  : Set Display Outside Box Pattern Gen Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBoxPatternGenAdjustColor10bit_Outside(WORD usRed, WORD usGreen, WORD usBlue)
{
    ScalerSetByte(P7_C2_DISP_PG_BOX_COLOR_CODE_5_R1, (((usBlue >> 6) & 0x0F) << 4));
    ScalerSetByte(P7_C1_DISP_PG_BOX_COLOR_CODE_4_R1, (((usRed >> 6) & 0x0F) << 4) | ((usGreen >> 6) & 0x0F));
    ScalerSetByte(P7_BE_DISP_PG_BOX_COLOR_CODE_1_R1, ((usRed & 0x3F) << 2));
    ScalerSetByte(P7_BF_DISP_PG_BOX_COLOR_CODE_2_R1, ((usGreen & 0x3F) << 2));
    ScalerSetByte(P7_C0_DISP_PG_BOX_COLOR_CODE_3_R1, ((usBlue & 0x3F) << 2));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerSetByte(P1A_C2_DISP_PG_BOX_COLOR_CODE_5_R3, (((usBlue >> 6) & 0x0F) << 4));
        ScalerSetByte(P1A_C1_DISP_PG_BOX_COLOR_CODE_4_R3, (((usRed >> 6) & 0x0F) << 4) | ((usGreen >> 6) & 0x0F));
        ScalerSetByte(P1A_BE_DISP_PG_BOX_COLOR_CODE_1_R3, ((usRed & 0x3F) << 2));
        ScalerSetByte(P1A_BF_DISP_PG_BOX_COLOR_CODE_2_R3, ((usGreen & 0x3F) << 2));
        ScalerSetByte(P1A_C0_DISP_PG_BOX_COLOR_CODE_3_R3, ((usBlue & 0x3F) << 2));
    }
#endif
}

//--------------------------------------------------
// Description  : Setup Box Pattern Gen Width & Height
// Input Value  : usWidth1, usWidth2, usHeight1, usHeight2
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBoxPatternGenSetWidthHeight(WORD usWidth1, WORD usWidth2, WORD usHeight1, WORD usHeight2)
{
    if(((usWidth1 == 0) && (usWidth2 == 0)) || ((usHeight1 == 0) && (usHeight2 == 0)))
    {
        return;
    }

    ScalerSetByte(P7_E8_DISP_PG_BOX_SET_1_R1, (((usWidth1 >> 8) & 0x0F) << 4) | ((usWidth2 >> 8) & 0x0F));
    ScalerSetByte(P7_E9_DISP_PG_BOX_SET_2_R1, (usWidth1 & 0xFF));
    ScalerSetByte(P7_EA_DISP_PG_BOX_SET_3_R1, (usWidth2 & 0xFF));
    ScalerSetByte(P7_EB_DISP_PG_BOX_SET_4_R1, (((usHeight1 >> 8) & 0x0F) << 4) | ((usHeight2 >> 8) & 0x0F));
    ScalerSetByte(P7_EC_DISP_PG_BOX_SET_5_R1, (usHeight1 & 0xFF));
    ScalerSetByte(P7_ED_DISP_PG_BOX_SET_6_R1, (usHeight2 & 0xFF));
}

//--------------------------------------------------
// Description  : Setup Box Pattern Gen Region Inside/Outside
// Input Value  : bEnable enable box mode or not
//                pstDPatternGenBoxSetting->b1RegionX are Inside (_FALSE) or Outside (_TRUE)
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBoxPatternGenSetRegionInOut(bit bEnable, StructDPatternGenBoxSetting *pstDPatternGenBoxSetting)
{
    BYTE ucRegion = (((BYTE)pstDPatternGenBoxSetting->b1Region0 << 7) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region1 << 6) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region2 << 5) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region3 << 4) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region4 << 3) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region5 << 2) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region6 << 1) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region7));

    ScalerSetByte(P7_EE_DISP_PG_BOX_CTRL_1_R1, ucRegion);
    ScalerSetBit(P7_EF_DISP_PG_BOX_CTRL_2_R1, ~_BIT7, ((BYTE)pstDPatternGenBoxSetting->b1Region8 << 7));

    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P7_F0_DISP_PG_R_CTRL_R1, ~_BIT6, 0x00);
        ScalerSetBit(P7_F1_DISP_PG_G_CTRL_R1, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P7_F0_DISP_PG_R_CTRL_R1, ~_BIT6, 0x00);
        ScalerSetBit(P7_F1_DISP_PG_G_CTRL_R1, ~_BIT6, 0x00);
    }
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Setup Box Pattern Gen Back Width & Height
// Input Value  : usWidth1, usWidth2, usHeight1, usHeight2
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBoxPatternGenSetWidthHeight_Back(WORD usWidth1, WORD usWidth2, WORD usHeight1, WORD usHeight2)
{
    if(((usWidth1 == 0) && (usWidth2 == 0)) || ((usHeight1 == 0) && (usHeight2 == 0)))
    {
        return;
    }

    ScalerSetByte(P1A_E8_DISP_PG_BOX_SET_1_R3, (((usWidth1 >> 8) & 0x0F) << 4) | ((usWidth2 >> 8) & 0x0F));
    ScalerSetByte(P1A_E9_DISP_PG_BOX_SET_2_R3, (usWidth1 & 0xFF));
    ScalerSetByte(P1A_EA_DISP_PG_BOX_SET_3_R3, (usWidth2 & 0xFF));
    ScalerSetByte(P1A_EB_DISP_PG_BOX_SET_4_R3, (((usHeight1 >> 8) & 0x0F) << 4) | ((usHeight2 >> 8) & 0x0F));
    ScalerSetByte(P1A_EC_DISP_PG_BOX_SET_5_R3, (usHeight1 & 0xFF));
    ScalerSetByte(P1A_ED_DISP_PG_BOX_SET_6_R3, (usHeight2 & 0xFF));
}

//--------------------------------------------------
// Description  : Setup Box Pattern Gen Back Region Inside/Outside
// Input Value  : bEnable enable box mode or not
//                pstDPatternGenBoxSetting->b1RegionX are Inside (_FALSE) or Outside (_TRUE)
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBoxPatternGenSetRegionInOut_Back(bit bEnable, StructDPatternGenBoxSetting *pstDPatternGenBoxSetting)
{
    BYTE ucRegion = (((BYTE)pstDPatternGenBoxSetting->b1Region0 << 7) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region1 << 6) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region2 << 5) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region3 << 4) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region4 << 3) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region5 << 2) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region6 << 1) |
                     ((BYTE)pstDPatternGenBoxSetting->b1Region7));

    ScalerSetByte(P1A_EE_DISP_PG_BOX_CTRL_1_R3, ucRegion);
    ScalerSetBit(P1A_EF_DISP_PG_BOX_CTRL_2_R3, ~_BIT7, ((BYTE)pstDPatternGenBoxSetting->b1Region8 << 7));

    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P1A_F0_DISP_PG_R_CTRL_R3, ~_BIT6, 0x00);
        ScalerSetBit(P1A_F1_DISP_PG_G_CTRL_R3, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P1A_F0_DISP_PG_R_CTRL_R3, ~_BIT6, 0x00);
        ScalerSetBit(P1A_F1_DISP_PG_G_CTRL_R3, ~_BIT6, 0x00);
    }
}
#endif

#if((_2P_PIP_DISPLAY_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check R2 Den Enable or not
// Input Value  : None
// Output Value : _ENABLE: R2 Den Enable
//--------------------------------------------------
bit ScalerDDomainGetR2DenEnable(void)
{
    // Sub covers Main
    if(ScalerGetBit(P24_00_MULTI_PIC_BLENDING, _BIT7) == 0x00)
    {
        return _ENABLE;
    }

    return _DISABLE;
}

//--------------------------------------------------
// Description  : Set R2 Den Enable/ Disable
// Input Value  : _ENABLE/ _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetR2DenEnable(bit bEnable, EnumDBApply enumDBApply)
{
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P24_00_MULTI_PIC_BLENDING, ~_BIT7, 0x00);
    }
    else
    {
        ScalerSetBit(P24_00_MULTI_PIC_BLENDING, ~_BIT7, _BIT7);
    }

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#endif

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Set Display Background Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundSetColor10bit(WORD usRed, WORD usGreen, WORD usBlue, EnumDBApply enumDBApply) // 10bit
{
    ScalerSetByte(P80_A3_BG_COLOR_R_R1_ACTIVE1, (usRed >> 2));
    ScalerSetByte(P80_A4_BG_COLOR_G_R1_ACTIVE1, (usGreen >> 2));
    ScalerSetByte(P80_A5_BG_COLOR_B_R1_ACTIVE1, (usBlue >> 2));
    ScalerSetByte(P80_A6_BG_COLOR_RGB_R1_ACTIVE1, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    ScalerSetByte(P80_A7_BG_COLOR_R_R1_ACTIVE2, (usRed >> 2));
    ScalerSetByte(P80_A8_BG_COLOR_G_R1_ACTIVE2, (usGreen >> 2));
    ScalerSetByte(P80_A9_BG_COLOR_B_R1_ACTIVE2, (usBlue >> 2));
    ScalerSetByte(P80_AA_BG_COLOR_RGB_R1_ACTIVE2, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    ScalerSetByte(P80_AD_BG_COLOR_R_R2_ACTIVE1, (usRed >> 2));
    ScalerSetByte(P80_AE_BG_COLOR_G_R2_ACTIVE1, (usGreen >> 2));
    ScalerSetByte(P80_AF_BG_COLOR_B_R2_ACTIVE1, (usBlue >> 2));
    ScalerSetByte(P80_B0_BG_COLOR_RGB_R2_ACTIVE1, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
    ScalerSetByte(P80_B1_BG_COLOR_R_R2_ACTIVE2, (usRed >> 2));
    ScalerSetByte(P80_B2_BG_COLOR_G_R2_ACTIVE2, (usGreen >> 2));
    ScalerSetByte(P80_B3_BG_COLOR_B_R2_ACTIVE2, (usBlue >> 2));
    ScalerSetByte(P80_B4_BG_COLOR_RGB_R2_ACTIVE2, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
    ScalerSetByte(P80_B7_BG_COLOR_R_R3_ACTIVE1, (usRed >> 2));
    ScalerSetByte(P80_B8_BG_COLOR_G_R3_ACTIVE1, (usGreen >> 2));
    ScalerSetByte(P80_B9_BG_COLOR_B_R3_ACTIVE1, (usBlue >> 2));
    ScalerSetByte(P80_BA_BG_COLOR_RGB_R3_ACTIVE1, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
    ScalerSetByte(P80_BB_BG_COLOR_R_R3_ACTIVE2, (usRed >> 2));
    ScalerSetByte(P80_BC_BG_COLOR_G_R3_ACTIVE2, (usGreen >> 2));
    ScalerSetByte(P80_BD_BG_COLOR_B_R3_ACTIVE2, (usBlue >> 2));
    ScalerSetByte(P80_BE_BG_COLOR_RGB_R3_ACTIVE2, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));
#endif
#endif
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Set Display Box Pattern Gen Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBoxPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue) // 10bit
{
    ScalerSetByte(P7_C2_DISP_PG_BOX_COLOR_CODE_5_R1, ((usBlue >> 6) & 0x0F));
    ScalerSetByte(P7_C3_DISP_PG_BOX_COLOR_CODE_6_R1, (((usRed >> 6) & 0x0F) << 4) | ((usGreen >> 6) & 0x0F));
    ScalerSetByte(P7_C4_DISP_PG_BOX_COLOR_CODE_7_R1, ((usRed & 0x3F) << 2));
    ScalerSetByte(P7_C5_DISP_PG_BOX_COLOR_CODE_8_R1, ((usGreen & 0x3F) << 2));
    ScalerSetByte(P7_C6_DISP_PG_BOX_COLOR_CODE_9_R1, ((usBlue & 0x3F) << 2));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerSetByte(P1A_C2_DISP_PG_BOX_COLOR_CODE_5_R3, ((usBlue >> 6) & 0x0F));
        ScalerSetByte(P1A_C3_DISP_PG_BOX_COLOR_CODE_6_R3, (((usRed >> 6) & 0x0F) << 4) | ((usGreen >> 6) & 0x0F));
        ScalerSetByte(P1A_C4_DISP_PG_BOX_COLOR_CODE_7_R3, ((usRed & 0x3F) << 2));
        ScalerSetByte(P1A_C5_DISP_PG_BOX_COLOR_CODE_8_R3, ((usGreen & 0x3F) << 2));
        ScalerSetByte(P1A_C6_DISP_PG_BOX_COLOR_CODE_9_R3, ((usBlue & 0x3F) << 2));
    }
#endif
}

//--------------------------------------------------
// Description  : Setup Display Pattern Gen Front Box  (10bit)
// Input Value  : pucCommand, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenFrontSetBox(BYTE *pucCommand, bit bEnable) // 10bit
{
    ScalerSetByte(P7_E8_DISP_PG_BOX_SET_1_R1, pucCommand[0]);
    ScalerSetByte(P7_E9_DISP_PG_BOX_SET_2_R1, pucCommand[1]);
    ScalerSetByte(P7_EA_DISP_PG_BOX_SET_3_R1, pucCommand[2]);
    ScalerSetByte(P7_EB_DISP_PG_BOX_SET_4_R1, pucCommand[3]);
    ScalerSetByte(P7_EC_DISP_PG_BOX_SET_5_R1, pucCommand[4]);
    ScalerSetByte(P7_ED_DISP_PG_BOX_SET_6_R1, pucCommand[5]);
    ScalerSetByte(P7_EE_DISP_PG_BOX_CTRL_1_R1, pucCommand[6]);
    ScalerSetByte(P7_EF_DISP_PG_BOX_CTRL_2_R1, pucCommand[7]);

    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P7_F1_DISP_PG_G_CTRL_R1, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P7_F1_DISP_PG_G_CTRL_R1, ~_BIT6, 0x00);
    }
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Setup Display Pattern Gen Back Box  (10bit)
// Input Value  : pucCommand, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenBackSetBox(BYTE *pucCommand, bit bEnable) // 10bit
{
    ScalerSetByte(P1A_E8_DISP_PG_BOX_SET_1_R3, pucCommand[0]);
    ScalerSetByte(P1A_E9_DISP_PG_BOX_SET_2_R3, pucCommand[1]);
    ScalerSetByte(P1A_EA_DISP_PG_BOX_SET_3_R3, pucCommand[2]);
    ScalerSetByte(P1A_EB_DISP_PG_BOX_SET_4_R3, pucCommand[3]);
    ScalerSetByte(P1A_EC_DISP_PG_BOX_SET_5_R3, pucCommand[4]);
    ScalerSetByte(P1A_ED_DISP_PG_BOX_SET_6_R3, pucCommand[5]);
    ScalerSetByte(P1A_EE_DISP_PG_BOX_CTRL_1_R3, pucCommand[6]);
    ScalerSetByte(P1A_EF_DISP_PG_BOX_CTRL_2_R3, pucCommand[7]);

    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P1A_F1_DISP_PG_G_CTRL_R3, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P1A_F1_DISP_PG_G_CTRL_R3, ~_BIT6, 0x00);
    }
}
#endif
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set Background to Gray Level
//                Specified by OD Calibration Tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDomainFreeSyncODSetBackgroundGrayLevel(void)
{
    static BYTE sucSelectedBGGrayLevel = 0x00;
    static BYTE sucPreviousBGGrayLevel = 0x00;

    // This function borrows two registers from "D-domain pattern generator"
    // 1. P7_F3_DISP_PG_R_INITIAL served as "specified gray level"
    // 2. _BIT7 of P7_F4_DISP_PG_G_INITIAL served as "function enable" control bit
    // OD calibration tool will use these two registers to communicate with firmware

    // Enable Background
    ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_R1_A1, _ENABLE);

    if(ScalerGetBit(_FREESYNC_OD_MEASURE_GL_ENABLE_REG, _BIT7) == _BIT7)
    {
        sucPreviousBGGrayLevel = sucSelectedBGGrayLevel;
        sucSelectedBGGrayLevel = ScalerGetByte(_FREESYNC_OD_MEASURE_GL_VALUE_REG);

        if(sucPreviousBGGrayLevel != sucSelectedBGGrayLevel)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            ScalerDDomainBackgroundSetColor(_DDOMAIN_RGN_R1_A1, sucSelectedBGGrayLevel, sucSelectedBGGrayLevel, sucSelectedBGGrayLevel, _DB_APPLY_POLLING);
        }
    }
    else
    {
        // Enable Red Background
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        ScalerDDomainBackgroundSetColor(_DDOMAIN_RGN_R1_A1, 0xFF, 0x00, 0x00, _DB_APPLY_POLLING);
    }
}
#endif

#if(_FW_DISPLAYTOP_AVG_REQ_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set D domain average request
// Input Value  : D domain Region, Hwidth and Htotal
// Output Value : none
//--------------------------------------------------
void ScalerDDomainSetDdmReqAvgReqEnable(EnumDisplayRegion enumDisplayRegion, bit bEnable)
{
    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(enumDisplayRegion);
    EnumDBApply enumDBApply = ((ScalerMemoryCheckScreenCoverStatus() == _FALSE) ? _DB_APPLY_NONE : _DB_APPLY_NO_POLLING);

    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A1) == _DDOMAIN_RGN_R1_A1)
    {
        if(bEnable == _DISABLE)
        {
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_DISP_HOR_REQUEST_FACTOR_H_R1_A1, 0x0F);
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_DISP_HOR_REQUEST_FACTOR_M_R1_A1, 0xFF);
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_DISP_HOR_REQUEST_FACTOR_L_R1_A1, 0xFF);
            ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), enumDBApply);
        }
        else
        {
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_DISP_HOR_REQUEST_FACTOR_H_R1_A1, ~_BIT7, _BIT7);
        }
    }


#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A1) == _DDOMAIN_RGN_R2_A1)
    {
        if(bEnable == _DISABLE)
        {
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_40_DISP_HOR_REQUEST_FACTOR_H_R2_A1, 0x0F);
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_41_DISP_HOR_REQUEST_FACTOR_M_R2_A1, 0xFF);
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_42_DISP_HOR_REQUEST_FACTOR_L_R2_A1, 0xFF);
            ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), enumDBApply);
        }
        else
        {
            ScalerSetDataPortBit(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_40_DISP_HOR_REQUEST_FACTOR_H_R2_A1, ~_BIT7, _BIT7);
        }
    }
#endif
#endif
}
//--------------------------------------------------
// Description  : Set D domain average request
// Input Value  : D domain Region, Hwidth and Htotal
// Output Value : none
//--------------------------------------------------
void ScalerDDomainSetDdmReqAvgReqFactor(EnumDisplayRegion enumDisplayRegion, WORD usFifoHwidth, WORD usDdmHwidth, WORD usHtotal)
{
    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(enumDisplayRegion);
    DWORD ulPreReadFactor = 0xFFFFF;

    if(enumDDomainRegion == _DDOMAIN_RGN_R1_A1)
    {
        if(usDdmHwidth < (usHtotal / 2))
        {
            ulPreReadFactor = GET_DWORD_MUL_DIV((1UL << (_DISPLAYTOP_AVG_REQ_FACTOR_BIT + 1)), usFifoHwidth + _DISPLAYTOP_AVG_REQ_HW_LIMIT, (usDdmHwidth + usHtotal / 2));
            ulPreReadFactor = (ulPreReadFactor + 1) >> 1;
        }
        else
        {
            ulPreReadFactor = GET_DWORD_MUL_DIV((1UL << (_DISPLAYTOP_AVG_REQ_FACTOR_BIT + 1)), usFifoHwidth + _DISPLAYTOP_AVG_REQ_HW_LIMIT, usHtotal);
            ulPreReadFactor = (ulPreReadFactor + 1) >> 1;
        }
    }
    else if(enumDDomainRegion == _DDOMAIN_RGN_R2_A1)
    {
        ulPreReadFactor = GET_DWORD_MUL_DIV((1UL << (_DISPLAYTOP_AVG_REQ_FACTOR_BIT + 1)), usFifoHwidth + _DISPLAYTOP_AVG_REQ_HW_LIMIT, (usHtotal / 2));
        ulPreReadFactor = (ulPreReadFactor + 1) >> 1;
    }

    // Keep some buffer for mdomain efficiency
    ulPreReadFactor = ulPreReadFactor * (100 + _DISPLAYTOP_AVG_REQ_BUFFER) / 100;

    if(ulPreReadFactor > 0xFFFFF)
    {
        ulPreReadFactor = 0xFFFFF;
    }

    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A1) == _DDOMAIN_RGN_R1_A1)
    {
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_DISP_HOR_REQUEST_FACTOR_H_R1_A1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulPreReadFactor >> 16) & 0x0F));
        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_DISP_HOR_REQUEST_FACTOR_M_R1_A1, ((ulPreReadFactor >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_DISP_HOR_REQUEST_FACTOR_L_R1_A1, (ulPreReadFactor & 0xFF));
    }

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A1) == _DDOMAIN_RGN_R2_A1)
    {
        ScalerSetDataPortBit(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_40_DISP_HOR_REQUEST_FACTOR_H_R2_A1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulPreReadFactor >> 16) & 0x0F));
        ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_41_DISP_HOR_REQUEST_FACTOR_M_R2_A1, ((ulPreReadFactor >> 8) & 0xFF));
        ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_42_DISP_HOR_REQUEST_FACTOR_L_R2_A1, (ulPreReadFactor & 0xFF));
    }
#endif
#endif
}
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin Enable
// Input Value  : Enable
// Output Value : NA
//--------------------------------------------------
void ScalerDDomainSetCaptureWindowEnable(bit bCapWinEnable)
{
    // Enable capture win
    ScalerSetBit(P24_1C_CW_EN, ~_BIT0, bCapWinEnable);
}

//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin Background
// Input Value  : EnumDisplayBackgroundItem, usData
// Output Value : NA
//--------------------------------------------------
void ScalerDDomainSetCaptureWindowBackground(EnumDisplayBackgroundItem enumItem, WORD usData)
{
    usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;

    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            ScalerSetByte(P24_26_CW_BG_HOR_START_H, HIBYTE(usData));
            ScalerSetByte(P24_27_CW_BG_HOR_START_L, LOBYTE(usData));
            break;

        case _DISPLAY_BACKGROUND_H_END:
            ScalerSetByte(P24_28_CW_BG_HOR_END_H, HIBYTE(usData));
            ScalerSetByte(P24_29_CW_BG_HOR_END_L, LOBYTE(usData));
            break;

        case _DISPLAY_BACKGROUND_V_START:
            ScalerSetByte(P24_2A_CW_BG_VER_START_H, HIBYTE(usData));
            ScalerSetByte(P24_2B_CW_BG_VER_START_L, LOBYTE(usData));
            break;

        case _DISPLAY_BACKGROUND_V_END:
            ScalerSetByte(P24_2C_CW_BG_VER_END_H, HIBYTE(usData));
            ScalerSetByte(P24_2D_CW_BG_VER_END_L, LOBYTE(usData));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get PIPBlending CaptureWin Background
// Input Value  : EnumDisplayBackgroundItem
// Output Value : Background Timing Info
//--------------------------------------------------
WORD ScalerDDomainGetCaptureWindowBackground(EnumDisplayBackgroundItem enumItem)
{
    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            return (((WORD)(ScalerGetByte(P24_26_CW_BG_HOR_START_H) << 8) | ScalerGetByte(P24_27_CW_BG_HOR_START_L)) & 0x3FFF);

        case _DISPLAY_BACKGROUND_H_END:
            return (((WORD)(ScalerGetByte(P24_28_CW_BG_HOR_END_H) << 8) | ScalerGetByte(P24_29_CW_BG_HOR_END_L)) & 0x3FFF);

        case _DISPLAY_BACKGROUND_V_START:
            return (((WORD)(ScalerGetByte(P24_2A_CW_BG_VER_START_H) << 8) | ScalerGetByte(P24_2B_CW_BG_VER_START_L)) & 0x3FFF);

        case _DISPLAY_BACKGROUND_V_END:
            return (((WORD)(ScalerGetByte(P24_2C_CW_BG_VER_END_H) << 8) | ScalerGetByte(P24_2D_CW_BG_VER_END_L)) & 0x3FFF);

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin Active Timing
// Input Value  : EnumDisplayFormatItem, usData
// Output Value : NA
//--------------------------------------------------
void ScalerDDomainSetCaptureWindowActiveRegion(EnumDisplayFormatItem enumItem, WORD usData)
{
    usData &= _HW_DIS_TIMING_GEN_H_ACTIVE_BIT;

    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            ScalerSetByte(P24_1D_CW_HOR_START_H, HIBYTE(usData));
            ScalerSetByte(P24_1E_CW_HOR_START_L, LOBYTE(usData));
            break;

        case _DISPLAY_FORMAT_H_END:
            ScalerSetByte(P24_1F_CW_HOR_END_H, HIBYTE(usData));
            ScalerSetByte(P24_20_CW_HOR_END_L, LOBYTE(usData));
            break;

        case _DISPLAY_FORMAT_V_START:
            ScalerSetByte(P24_21_CW_VER_START_H, HIBYTE(usData));
            ScalerSetByte(P24_22_CW_VER_START_L, LOBYTE(usData));
            break;

        case _DISPLAY_FORMAT_V_END:
            ScalerSetByte(P24_23_CW_VER_END_H, HIBYTE(usData));
            ScalerSetByte(P24_24_CW_VER_END_L, LOBYTE(usData));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get PIPBlending CaptureWin Active Timing
// Input Value  : EnumDisplayFormatItem
// Output Value : Active Timing Info
//--------------------------------------------------
WORD ScalerDDomainGetCaptureWindowActiveRegion(EnumDisplayFormatItem enumItem)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            return (((WORD)(ScalerGetByte(P24_1D_CW_HOR_START_H) << 8) | ScalerGetByte(P24_1E_CW_HOR_START_L)) & 0x3FFF);

        case _DISPLAY_FORMAT_H_END:
            return (((WORD)(ScalerGetByte(P24_1F_CW_HOR_END_H) << 8) | ScalerGetByte(P24_20_CW_HOR_END_L)) & 0x3FFF);

        case _DISPLAY_FORMAT_V_START:
            return (((WORD)(ScalerGetByte(P24_21_CW_VER_START_H) << 8) | ScalerGetByte(P24_22_CW_VER_START_L)) & 0x3FFF);

        case _DISPLAY_FORMAT_V_END:
            return (((WORD)(ScalerGetByte(P24_23_CW_VER_END_H) << 8) | ScalerGetByte(P24_24_CW_VER_END_L)) & 0x3FFF);

        default:
            return 0;
    }
}
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set PIPBlending Extension Extract
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetExtensionExtract(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P24_30_EXTENSION_EXTRA_WIN, ~_BIT0, _BIT0);
        ScalerSetBit(P5A_30_EXTENSION_EXTRA_WIN_BACK, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P24_30_EXTENSION_EXTRA_WIN, ~_BIT0, 0x00);
        ScalerSetBit(P5A_30_EXTENSION_EXTRA_WIN_BACK, ~_BIT0, 0x00);
    }
}
//--------------------------------------------------
// Description  : Set Dspc den delay
// Input Value  : Dspc den delay
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetDspcDenDelay(BYTE ucData)
{
    ScalerSetByte(P39_1E_DISP_TIMING_CTRL0, ucData);
}

//--------------------------------------------------
// Description  : Get Dspc den delay
// Input Value  : None
// Output Value : Dspc den delay
//--------------------------------------------------
BYTE ScalerDDomainGetDspcDenDelay(void)
{
    return ScalerGetByte(P39_1E_DISP_TIMING_CTRL0);
}
//--------------------------------------------------
// Description  : Set Back PIPBlending CaptureWin Enable
// Input Value  : Enable
// Output Value : NA
//--------------------------------------------------
void ScalerDDomainSetCaptureWindowEnable_Back(bit bCapWinEnable)
{
    // Enable capture win
    ScalerSetBit(P5A_1C_CW_EN_BACK, ~_BIT0, bCapWinEnable);
}

//--------------------------------------------------
// Description  : Set Back PIPBlending CaptureWin Background
// Input Value  : EnumDisplayBackgroundItem, usData
// Output Value : NA
//--------------------------------------------------
void ScalerDDomainSetCaptureWindowBackground_Back(EnumDisplayBackgroundItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            ScalerSetByte(P5A_26_CW_BG_HOR_START_H_BACK, (HIBYTE(usData) & 0x1F));
            ScalerSetByte(P5A_27_CW_BG_HOR_START_L_BACK, LOBYTE(usData));
            break;

        case _DISPLAY_BACKGROUND_H_END:
            ScalerSetByte(P5A_28_CW_BG_HOR_END_H_BACK, (HIBYTE(usData) & 0x1F));
            ScalerSetByte(P5A_29_CW_BG_HOR_END_L_BACK, LOBYTE(usData));
            break;

        case _DISPLAY_BACKGROUND_V_START:
            ScalerSetByte(P5A_2A_CW_BG_VER_START_H_BACK, (HIBYTE(usData) & 0x1F));
            ScalerSetByte(P5A_2B_CW_BG_VER_START_L_BACK, LOBYTE(usData));
            break;

        case _DISPLAY_BACKGROUND_V_END:
            ScalerSetByte(P5A_2C_CW_BG_VER_END_H_BACK, (HIBYTE(usData) & 0x1F));
            ScalerSetByte(P5A_2D_CW_BG_VER_END_L_BACK, LOBYTE(usData));
            break;

        case _DISPLAY_BACKGROUND_H_WIDTH:
        case _DISPLAY_BACKGROUND_V_HEIGHT:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Back PIPBlending CaptureWin Background
// Input Value  : EnumDisplayBackgroundItem
// Output Value : Background Timing Info
//--------------------------------------------------
WORD ScalerDDomainGetCaptureWindowBackground_Back(EnumDisplayBackgroundItem enumItem)
{
    switch(enumItem)
    {
        case _DISPLAY_BACKGROUND_H_START:
            return (((WORD)(ScalerGetByte(P5A_26_CW_BG_HOR_START_H_BACK) << 8) | ScalerGetByte(P5A_27_CW_BG_HOR_START_L_BACK)) & 0x1FFF);

        case _DISPLAY_BACKGROUND_H_END:
            return (((WORD)(ScalerGetByte(P5A_28_CW_BG_HOR_END_H_BACK) << 8) | ScalerGetByte(P5A_29_CW_BG_HOR_END_L_BACK)) & 0x1FFF);

        case _DISPLAY_BACKGROUND_V_START:
            return (((WORD)(ScalerGetByte(P5A_2A_CW_BG_VER_START_H_BACK) << 8) | ScalerGetByte(P5A_2B_CW_BG_VER_START_L_BACK)) & 0x1FFF);

        case _DISPLAY_BACKGROUND_V_END:
            return (((WORD)(ScalerGetByte(P5A_2C_CW_BG_VER_END_H_BACK) << 8) | ScalerGetByte(P5A_2D_CW_BG_VER_END_L_BACK)) & 0x1FFF);

        case _DISPLAY_BACKGROUND_H_WIDTH:
        case _DISPLAY_BACKGROUND_V_HEIGHT:
        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Set Back PIPBlending CaptureWin Active Timing
// Input Value  : EnumDisplayFormatItem, usData
// Output Value : NA
//--------------------------------------------------
void ScalerDDomainSetCaptureWindowActiveRegion_Back(EnumDisplayFormatItem enumItem, WORD usData)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            ScalerSetByte(P5A_1D_CW_HOR_START_H_BACK, (HIBYTE(usData) & 0x1F));
            ScalerSetByte(P5A_1E_CW_HOR_START_L_BACK, LOBYTE(usData));
            break;

        case _DISPLAY_FORMAT_H_END:
            ScalerSetByte(P5A_1F_CW_HOR_END_H_BACK, (HIBYTE(usData) & 0x1F));
            ScalerSetByte(P5A_20_CW_HOR_END_L_BACK, LOBYTE(usData));
            break;

        case _DISPLAY_FORMAT_V_START:
            ScalerSetByte(P5A_21_CW_VER_START_H_BACK, (HIBYTE(usData) & 0x1F));
            ScalerSetByte(P5A_22_CW_VER_START_L_BACK, LOBYTE(usData));
            break;

        case _DISPLAY_FORMAT_V_END:
            ScalerSetByte(P5A_23_CW_VER_END_H_BACK, (HIBYTE(usData) & 0x1F));
            ScalerSetByte(P5A_24_CW_VER_END_L_BACK, LOBYTE(usData));
            break;

        case _DISPLAY_FORMAT_H_TOTAL:
        case _DISPLAY_FORMAT_HS_WIDTH:
        case _DISPLAY_FORMAT_H_WIDTH:
        case _DISPLAY_FORMAT_V_TOTAL:
        case _DISPLAY_FORMAT_VS_WIDTH:
        case _DISPLAY_FORMAT_V_HEIGHT:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Back PIPBlending CaptureWin Active Timing
// Input Value  : EnumDisplayFormatItem
// Output Value : Active Timing Info
//--------------------------------------------------
WORD ScalerDDomainGetCaptureWindowActiveRegion_Back(EnumDisplayFormatItem enumItem)
{
    switch(enumItem)
    {
        case _DISPLAY_FORMAT_H_START:
            return (((WORD)(ScalerGetByte(P5A_1D_CW_HOR_START_H_BACK) << 8) | ScalerGetByte(P5A_1E_CW_HOR_START_L_BACK)) & 0x1FFF);

        case _DISPLAY_FORMAT_H_END:
            return (((WORD)(ScalerGetByte(P5A_1F_CW_HOR_END_H_BACK) << 8) | ScalerGetByte(P5A_20_CW_HOR_END_L_BACK)) & 0x1FFF);

        case _DISPLAY_FORMAT_V_START:
            return (((WORD)(ScalerGetByte(P5A_21_CW_VER_START_H_BACK) << 8) | ScalerGetByte(P5A_22_CW_VER_START_L_BACK)) & 0x1FFF);

        case _DISPLAY_FORMAT_V_END:
            return (((WORD)(ScalerGetByte(P5A_23_CW_VER_END_H_BACK) << 8) | ScalerGetByte(P5A_24_CW_VER_END_L_BACK)) & 0x1FFF);

        case _DISPLAY_FORMAT_H_TOTAL:
        case _DISPLAY_FORMAT_HS_WIDTH:
        case _DISPLAY_FORMAT_H_WIDTH:
        case _DISPLAY_FORMAT_V_TOTAL:
        case _DISPLAY_FORMAT_VS_WIDTH:
        case _DISPLAY_FORMAT_V_HEIGHT:
        default:
            return 0;
    }
}
//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin Enable
// Input Value  : Enable
// Output Value : NA
//--------------------------------------------------
void ScalerDDomainSetCaptureWindowRefBG(bit bEnable)
{
    // Enable capture win
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P24_25_CW_BG_EN, ~_BIT0, _BIT0);
        ScalerSetBit(P5A_25_CW_BG_EN_BACK, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P24_25_CW_BG_EN, ~_BIT0, 0x00);
        ScalerSetBit(P5A_25_CW_BG_EN_BACK, ~_BIT0, 0x00);
    }
}
//--------------------------------------------------
// Description  : Get DDomain Extension
// Input Value  : NA
// Output Value : DDomain Extension
//--------------------------------------------------
WORD ScalerDDomainGetExtension(void)
{
    return GET_DDOMAIN_EXTENSION_LEN();
}
#endif // End of #if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#endif // End of #if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
#endif // End of #if(_PIXEL_SHIFT_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set D domain Reset flow
// Input Value  : EnumDDomainRegion, EnumDisplayRegion
// Output Value : none
//--------------------------------------------------
void ScalerDDomainSetResetDdmRegion(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _ON)
    {
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        if(enumDisplayRegion == _DISPLAY_RGN_SKEW_T_MAIN)
        {
#if(_HW_ADJ_A1_LB_START_ADDR == _ON)
            // Disable LB Start Address
            ScalerDDomainSetDisplayTopLBStartAddr(enumDisplayRegion, 0);
#endif
            // Display Extension
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_FRONT, 0x00);
            ScalerSetDataPortByte(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1F_DISPLAY_EXTENSION_FB_BACK, 0x00);

            // Display Conversion Extension
            ScalerSetByte(P39_1E_DISP_TIMING_CTRL0, 0x00);

            // Disable OSD Extension
            ScalerOsdSetExtension(0);
        }
        else
#endif
        {
#if(_HW_ADJ_A1_LB_START_ADDR == _ON)
            // Disable LB Start Address
            ScalerDDomainSetDisplayTopLBStartAddr(enumDisplayRegion, 0);
#endif
        }
    }
    else
#endif
    {
#if(_HW_ADJ_A1_LB_START_ADDR == _ON)
        // Disable LB Start Address
        ScalerDDomainSetDisplayTopLBStartAddr(enumDisplayRegion, 0);
#endif
    }
}

//--------------------------------------------------
// Description  : Get Display Timing Gen HV Background Active Diff
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDomainGetHVBActiveDiff(EnumDisplayRegion enumDisplayRegion, StructHVBActiveDiff *pstData)
{
    EnumDisplayMode enumDisplayMode = (EnumDisplayMode)((enumDisplayRegion) & _DISPLAY_MODE_NONE);

    pstData->b1VBHeightDiff = _FALSE;
    pstData->b1HBWidthDiff = _FALSE;

    // Set Up Display Timing According to display mode
    switch(enumDisplayMode)
    {
        case _DISPLAY_MODE_1P:
#if(_PANEL_ASYMMETRIC == _ON)
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_LEFT != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT != 0))
            pstData->b1HBWidthDiff = _TRUE;
#endif
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_TOP != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM != 0))
            pstData->b1VBHeightDiff = _TRUE;
#endif
#endif
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_PANEL_ASYMMETRIC == _ON)
            if(enumDisplayRegion == _DISPLAY_RGN_PIP_MAIN)
            {
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_LEFT != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT != 0))
                pstData->b1HBWidthDiff = _TRUE;
#endif
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_TOP != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM != 0))
                pstData->b1VBHeightDiff = _TRUE;
#endif
            }

#endif
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#if(_PANEL_ASYMMETRIC == _ON)
            if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)
            {
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_LEFT != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT != 0))
                pstData->b1HBWidthDiff = _TRUE;
#endif
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_TOP != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM != 0))
                pstData->b1VBHeightDiff = _TRUE;
#endif
            }
#endif
            break;
#endif


#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            if(ScalerRegionGetDDomainRegion(enumDisplayRegion) == _DDOMAIN_RGN_R1_A1)
            {
                pstData->b1HBWidthDiff = _TRUE;
            }
            else
            {
                pstData->b1HBWidthDiff = _FALSE;
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:

            pstData->b1VBHeightDiff = _TRUE;

            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            if(enumDisplayRegion == _DISPLAY_RGN_FLAG_LEFT)
            {
                pstData->b1HBWidthDiff = _TRUE;
            }
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:

            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_SKEW_L_MAIN:
                    pstData->b1HBWidthDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_SKEW_L_TOP:
                case _DISPLAY_RGN_SKEW_L_BOTTOM:
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_SKEW_R_TOP:
                case _DISPLAY_RGN_SKEW_R_BOTTOM:
                    pstData->b1HBWidthDiff = _TRUE;
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_SKEW_R_MAIN:
                default:
                    break;
            }
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:

            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_SKEW_T_MAIN:
                    // MAIN
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_SKEW_T_LEFT:
                    // L
                    pstData->b1HBWidthDiff = _TRUE;
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_SKEW_T_RIGHT:
                default:
                    break;
            }
            break;

        case _DISPLAY_MODE_3P_SKEW_B:
            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_SKEW_B_MAIN:
                    // MAIN
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_SKEW_B_LEFT:
                    // L
                    pstData->b1HBWidthDiff = _TRUE;
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_SKEW_B_RIGHT:
                default:
                    break;
            }
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_LT:
                    pstData->b1HBWidthDiff = _TRUE;
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_LB:
                    pstData->b1VBHeightDiff = _TRUE;
                    pstData->b1HBWidthDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_RT:
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                case _DISPLAY_RGN_RB:
                    pstData->b1VBHeightDiff = _TRUE;
                    break;

                default:
                    break;
            }
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Reset D Domain Region, free run/ force to BG
// Input Value  : enumDDomainRegion --> target region
// Output Value : None
//--------------------------------------------------
void ScalerDDomainResetDDomainRgn(EnumDDomainRegion enumDDomainRegion)
{
    EnumDDomainRegion enumChkDDomainRegion = _DDOMAIN_RGN_R1_A1;

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if(GET_2P_FRAME_SYNC_MAIN() == _FALSE)
    {
        enumChkDDomainRegion = _DDOMAIN_RGN_R2_A1;
    }
#endif

    if(enumDDomainRegion != _DDOMAIN_RGN_NONE)
    {
        if((enumDDomainRegion & enumChkDDomainRegion) == enumChkDDomainRegion)
        {
            ScalerMDomainFrameSyncSwitchtoFreeRunMode();
        }

        // Enable D-domain force-to-background
        ScalerDDomainBackgroundEnable(enumDDomainRegion, _ENABLE);
    }
}

#if(_HW_ADJ_A1_LB_START_ADDR == _ON)
//--------------------------------------------------
// Description  : Set D domain A1 Linebuffer Start Address
// Input Value  : D domain Region, Hwidth
// Output Value : none
//--------------------------------------------------
void ScalerDDomainSetDisplayTopLBStartAddr(EnumDisplayRegion enumDisplayRegion, WORD usHorSize)
{
    BYTE ucStartAddr = 0x00;
    bit bStartAddr = _FALSE;
    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(enumDisplayRegion);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerDDomainSetExtRecapLBStartAddr(enumDisplayRegion, usHorSize);
    }
#endif

    if(usHorSize == 0)
    {
        ucStartAddr = 0;
    }
    else
    {
        // bStartAddr
        switch(enumDisplayRegion)
        {
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_TOP:
                bStartAddr = _TRUE;
                break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_SKEW_L_TOP:
            case _DISPLAY_RGN_SKEW_R_TOP:
                bStartAddr = _TRUE;
                break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_SKEW_T_MAIN:
            case _DISPLAY_RGN_SKEW_B_LEFT:
                bStartAddr = _TRUE;
                break;
#endif


#if(_4P_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_LT:
            case _DISPLAY_RGN_RT:
                bStartAddr = _TRUE;
                break;
#endif

            case _DISPLAY_RGN_1P:
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_BOTTOM:
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_PIP_MAIN:
            case _DISPLAY_RGN_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
            case _DISPLAY_RGN_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_PBP_LR_EQUAL_LEFT:
            case _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT:
            case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
            case _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT:
            case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
            case _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT:
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_SKEW_L_MAIN:
            case _DISPLAY_RGN_SKEW_L_BOTTOM:
            case _DISPLAY_RGN_SKEW_R_MAIN:
            case _DISPLAY_RGN_SKEW_R_BOTTOM:
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_SKEW_B_MAIN:
            case _DISPLAY_RGN_SKEW_B_RIGHT:
            case _DISPLAY_RGN_SKEW_T_RIGHT:
            case _DISPLAY_RGN_SKEW_T_LEFT:
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_FLAG_MAIN:
            case _DISPLAY_RGN_FLAG_LEFT:
            case _DISPLAY_RGN_FLAG_RIGHT:
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_LB:
            case _DISPLAY_RGN_RB:
#endif
            default:
                bStartAddr = _FALSE;
                break;
        }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            switch(enumDisplayRegion)
            {
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_TOP:
                    usHorSize = (usHorSize / 2) + GET_EXT_RECAP_EXTENSION_LEN_A1();
                    break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_SKEW_T_MAIN:
                    usHorSize = (usHorSize / 2) + GET_EXT_RECAP_EXTENSION_LEN_A1();
                    break;
#endif

                case _DISPLAY_RGN_1P:
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_BOTTOM:
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_PIP_MAIN:
                case _DISPLAY_RGN_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
                case _DISPLAY_RGN_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_PBP_LR_EQUAL_LEFT:
                case _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT:
                case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
                case _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT:
                case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
                case _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT:
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_SKEW_L_MAIN:
                case _DISPLAY_RGN_SKEW_L_BOTTOM:
                case _DISPLAY_RGN_SKEW_R_MAIN:
                case _DISPLAY_RGN_SKEW_R_BOTTOM:
                case _DISPLAY_RGN_SKEW_L_TOP:
                case _DISPLAY_RGN_SKEW_R_TOP:
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_SKEW_B_MAIN:
                case _DISPLAY_RGN_SKEW_B_RIGHT:
                case _DISPLAY_RGN_SKEW_B_LEFT:
                case _DISPLAY_RGN_SKEW_T_RIGHT:
                case _DISPLAY_RGN_SKEW_T_LEFT:

#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_FLAG_MAIN:
                case _DISPLAY_RGN_FLAG_LEFT:
                case _DISPLAY_RGN_FLAG_RIGHT:
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_LB:
                case _DISPLAY_RGN_RB:
                case _DISPLAY_RGN_LT:
                case _DISPLAY_RGN_RT:
#endif
                default:
                    break;
            }
        }
#endif
    }

    if(bStartAddr == _TRUE)
    {
        if(usHorSize > _HW_SU_LINE_BUFFER_SIZE)
        {
            ucStartAddr = 0;
        }
        else
        {
            ucStartAddr = (_HW_SU_LINE_BUFFER_SIZE - usHorSize) / 128;
        }
    }
    else
    {
        ucStartAddr = 0;
    }

    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A1) == _DDOMAIN_RGN_R1_A1)
    {
        ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_08_DISPLAY_READ_WID_OFFSET_R1, (ucStartAddr & 0x3F));
    }

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A1) == _DDOMAIN_RGN_R2_A1)
    {
        ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_08_DISPLAY_READ_WID_OFFSET_R2, (ucStartAddr & 0x3F));
    }
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A1) == _DDOMAIN_RGN_R3_A1)
    {
        ScalerSetDataPortByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_08_DISPLAY_READ_WID_OFFSET_R3, (ucStartAddr & 0x3F));
    }
#endif
#endif
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Extension Recapture A1 Linebuffer Start Address
// Input Value  : D domain Region, Hwidth
// Output Value : none
//--------------------------------------------------
void ScalerDDomainSetExtRecapLBStartAddr(EnumDisplayRegion enumDisplayRegion, WORD usHorSize)
{
    BYTE ucStartAddr = 0x00;
    bit bStartAddr = _FALSE;

    enumDisplayRegion = enumDisplayRegion;

    switch(GET_DISPLAY_MODE())
    {
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            if(enumDisplayRegion == _DISPLAY_RGN_TOP)
            {
                bStartAddr = _TRUE;
                usHorSize = usHorSize / 2;
            }
            else
            {
                bStartAddr = _FALSE;
            }
            break;
#endif

        default:
            bStartAddr = _TRUE;
            usHorSize = 0;
            break;
    }

    if(bStartAddr == _TRUE)
    {
        if(usHorSize == 0)
        {
            ScalerSetByte(P92_96_DISPLAY_READ_WID_OFFSET_A1, (0x00 & 0x3F));
        }
        else
        {
            if(usHorSize > _HW_SU_LINE_BUFFER_SIZE)
            {
                ucStartAddr = 0;
            }
            else
            {
                ucStartAddr = (_HW_SU_LINE_BUFFER_SIZE - usHorSize) / 128;
            }
            ScalerSetByte(P92_96_DISPLAY_READ_WID_OFFSET_A1, ucStartAddr);
        }
    }
}
#endif
#endif // END OF #if(_HW_ADJ_A1_LB_START_ADDR == _ON)

//--------------------------------------------------
// Description  : Set Framesync Lastline Multiple
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetFsyncLastlineMultiple(void)
{
    BYTE ucLastlineMultiple = 0;

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        if(_PANEL_OUTPUT_NUM > 8)
        {
            ucLastlineMultiple = ((_PANEL_OUTPUT_NUM / 8) >> 1);
        }
    }
    else
    {
        if(_PANEL_OUTPUT_NUM > 4)
        {
            ucLastlineMultiple = ((_PANEL_OUTPUT_NUM / 4) >> 1);
        }
    }

    ScalerSetBit(P0_46_LAST_LINE_H1, ~(_BIT6 | _BIT5 | _BIT4), (ucLastlineMultiple << 4));
}

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get PBPLR Large Frame Mapping D domain Region
// Input Value  : None
// Output Value : _PBP_LR_LARGE_FRAME_R1A1/ _PBP_LR_LARGE_FRAME_R2A1
//--------------------------------------------------
EnumPBPLRLargeFrameMappingDDomainRegion ScalerDDomainPbpLRLargeFrameMappingRegion(void)
{
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_L_LARGE) ||
       (GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_R_LARGE) ||
       (GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_EQUAL))
    {
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_L_LARGE)
        {
            return _PBP_LR_LARGE_FRAME_R1A1;
        }
        else // _DISPLAY_MODE_2P_PBP_LR_R_LARGE
        {
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                return _PBP_LR_LARGE_FRAME_R1A1;
            }
            else
            {
                return _PBP_LR_LARGE_FRAME_R2A1;
            }
        }
    }

    return _PBP_LR_LARGE_FRAME_NONE;
}

//--------------------------------------------------
// Description  : Set PBPLR Sub Status
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDDomainSetPbplrSubDisable(void)
{
    if((GET_DISPLAY_MODE() != _DISPLAY_MODE_2P_PBP_LR_L_LARGE) && (GET_DISPLAY_MODE() != _DISPLAY_MODE_2P_PBP_LR_R_LARGE))
    {
        return;
    }

    if(ScalerDDomainPbpLRLargeFrameMappingRegion() == _PBP_LR_LARGE_FRAME_R1A1)
    {
        ScalerSetBit(P80_2C_DISPLAY_CONTROL_R2, ~(_BIT7 | _BIT4), 0x00);
    }
    else
    {
        ScalerSetBit(P0_2C_DISPLAY_CONTROL_R1, ~(_BIT4), 0x00);
    }
}

//--------------------------------------------------
// Description  : Get PBPLR Full screen Status
// Input Value  : None
// Output Value : _TRUE: Full Mode, _FALSE: Normal mode
//--------------------------------------------------
bit ScalerDDomainGetPbplrFullStatus(void)
{
    if((GET_DISPLAY_MODE() != _DISPLAY_MODE_2P_PBP_LR_L_LARGE) && (GET_DISPLAY_MODE() != _DISPLAY_MODE_2P_PBP_LR_R_LARGE))
    {
        return _FALSE;
    }

    if(ScalerDDomainPbpLRLargeFrameMappingRegion() == _PBP_LR_LARGE_FRAME_R1A1)
    {
        return (ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_WIDTH) == 0);
    }
    else
    {
        return (ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH) == 0);
    }
}
#endif

#if(_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_2)
//--------------------------------------------------
// Description  : Set Display Background Insert Color
// Input Value  : enable, RGB Color, cyclecnt, blackmask, DBapply
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundSetColorInsert(bit bEn, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, BYTE ucCycleCnt, BYTE ucBlackmask, EnumDBApply enumDBApply)
{
    if(bEn == _DISABLE)
    {
        // Set Insert disable
        ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT1, 0x00);
    }
    else
    {
        // Set Insert color, 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P80_B3_BG_COLOR_INSERT_R, ucRed);
        ScalerSetByte(P80_B4_BG_COLOR_INSERT_G, ucGreen);
        ScalerSetByte(P80_B5_BG_COLOR_INSERT_B, ucBlue);
        ScalerSetByte(P80_B6_BG_COLOR_INSERT_RGB, 0x00);

        // Set Insert cycle
        if(ucCycleCnt >= 8)
        {
            ScalerSetBit(P80_B1_BG_COLOR_INSERT_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x07);
        }
        else if(ucCycleCnt == 0)
        {
            ScalerSetBit(P80_B1_BG_COLOR_INSERT_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        }
        else
        {
            ScalerSetBit(P80_B1_BG_COLOR_INSERT_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), (ucCycleCnt - 1));
        }

        // Set Insert flag black frame mask
        ScalerSetByte(P80_B2_BG_COLOR_INSERT_CTRL_2, ucBlackmask);

        // Set Insert enable
        ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT1, _BIT1);
    }

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#endif
