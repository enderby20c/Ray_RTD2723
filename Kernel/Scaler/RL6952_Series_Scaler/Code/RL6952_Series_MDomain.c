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
// ID Code      : RL6952_Series_MDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_MDOMAIN__

#include "ScalerFunctionInclude.h"
#include "MDomain/ScalerMDomain.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Display Timgin Gen: Display mode
// Input Value  : Display mode
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenDisplayMode(EnumDisplayMode enumDisplayMode)
{
    // P0_29 FrontBack Mode Related Setting
    // [4]: Frontback
    // [3]: Dtime Main mode: select even/ odd

    // P0_2C/P0_2D R1 Related Setting
    // P0_2C : Ddm Setting
    // [7]: Region enable
    // [6]: Region EO/Single mode
    // [5]: Active2 Enable
    // [4]: Active1 Enable
    // P0_2D : Mdm Src Info
    // [7]: Active1 Mdm Source mode(Single/EO)
    // [6:4]: Active1 Source from Which Mdm datapath
    // [3]: Active2 Mdm Source mode(Single/EO)
    // [2:0]: Active2 Source from Which Mdm datapath

    // P80_2C/P80_2D R2 Related Setting
    // P80_2C : Ddm Setting
    // [7]: Region enable
    // [6]: Region EO/Single mode
    // [5]: Active2 Enable
    // [4]: Active1 Enable
    // P80_2D : Mdm Src Info
    // [7]: Active1 Mdm Source mode(Single/EO)
    // [6:4]: Active1 Source from Which Mdm datapath
    // [3]: Active2 Mdm Source mode(Single/EO)
    // [2:0]: Active2 Source from Which Mdm datapath

    // PC0_2C/PC0_2D R3 Related Setting
    // PC0_2C : Ddm Setting
    // [7]: Region enable
    // [6]: Region EO/Single mode
    // [5]: Active2 Enable
    // [4]: Active1 Enable
    // PC0_2D : Mdm Src Info
    // [7]: Active1 Mdm Source mode(Single/EO)
    // [6:4]: Active1 Source from Which Mdm datapath
    // [3]: Active2 Mdm Source mode(Single/EO)
    // [2:0]: Active2 Source from Which Mdm datapath

    switch(enumDisplayMode)
    {
        case _DISPLAY_MODE_1P:
            ScalerSetBit(P0_2C_DISPLAY_CONTROL_R1, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7 | _BIT6));
            ScalerSetByte(P0_2D_SOURCE_INFO_FROM_M_R1, (_BIT7));
            ScalerSetBit(P80_2C_DISPLAY_CONTROL_R2, ~(_BIT7 | _BIT6 | _BIT4), 0x00);
            ScalerSetByte(P80_2D_SOURCE_INFO_FROM_M_R2, 0x00);
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            ScalerSetBit(P0_2C_DISPLAY_CONTROL_R1, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7 | _BIT6));
            ScalerSetByte(P0_2D_SOURCE_INFO_FROM_M_R1, (_BIT7));
            ScalerSetBit(P80_2C_DISPLAY_CONTROL_R2, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7));
            ScalerSetByte(P80_2D_SOURCE_INFO_FROM_M_R2, (_BIT5));
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            ScalerSetBit(P0_2C_DISPLAY_CONTROL_R1, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7 | _BIT6));
            ScalerSetByte(P0_2D_SOURCE_INFO_FROM_M_R1, (_BIT7));
            ScalerSetBit(P80_2C_DISPLAY_CONTROL_R2, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7));
            ScalerSetByte(P80_2D_SOURCE_INFO_FROM_M_R2, (_BIT5));
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            ScalerSetBit(P0_2C_DISPLAY_CONTROL_R1, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7 | _BIT6));
            ScalerSetByte(P0_2D_SOURCE_INFO_FROM_M_R1, (_BIT7));
            ScalerSetBit(P80_2C_DISPLAY_CONTROL_R2, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7));
            ScalerSetByte(P80_2D_SOURCE_INFO_FROM_M_R2, (_BIT5));
            break;
#endif
        default:
            break;
    }
}


//--------------------------------------------------
// Description  : Set Display Timgin Gen: Display Region Enable
// Input Value  : Display mode
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenActiveEnable(EnumDDomainRegion enumDDomainRegion, EnumDisplayRegion enumDisplayRegion, bit bEnable)
{
    enumDisplayRegion = enumDisplayRegion;

    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A1) == _DDOMAIN_RGN_R1_A1)
    {
        if(bEnable == _ENABLE)
        {
            // Enable R1 a1
            ScalerSetBit(P0_2C_DISPLAY_CONTROL_R1, ~_BIT4, _BIT4);
        }
        else
        {
            // Disable R1 a1
            ScalerSetBit(P0_2C_DISPLAY_CONTROL_R1, ~_BIT4, 0x00);
        }
    }

    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A1) == _DDOMAIN_RGN_R2_A1)
    {
        if(bEnable == _ENABLE)
        {
            // Enable R2 a1
            ScalerSetBit(P80_2C_DISPLAY_CONTROL_R2, ~_BIT4, _BIT4);
        }
        else
        {
            // Disable R2 a1
            ScalerSetBit(P80_2C_DISPLAY_CONTROL_R2, ~_BIT4, 0x00);
        }
    }
}

