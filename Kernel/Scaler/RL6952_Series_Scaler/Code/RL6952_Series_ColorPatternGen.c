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
// ID Code      : RL6952_Series_ColorPatternGen.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

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
// Description  : Enable D Domain Pattern Generator
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorPatternGenDDomainControl(EnumPGType enumPGType, EnumPGBitNode enumPGBitNode, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set initial Value
        // R1 (Front) Setting
        ScalerSetByte(P7_F0_DISP_PG_R_CTRL_R1, 0xC0);
        ScalerSetByte(P7_F1_DISP_PG_G_CTRL_R1, 0x00);
        ScalerSetByte(P7_F2_DISP_PG_B_CTRL_R1, 0x00);
        ScalerSetByte(P7_F3_DISP_PG_R_INITIAL_R1, 0x00);
        ScalerSetByte(P7_F4_DISP_PG_G_INITIAL_R1, 0x00);
        ScalerSetByte(P7_F5_DISP_PG_B_INITIAL_R1, 0x00);

        if(enumPGBitNode == _PG_MODE_12)
        {
            ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L_R1, 0x00);
            ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL_R1, 0x95);
        }
        else
        {
            ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L_R1, 0x15);
            ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL_R1, 0x00);
        }

        if(enumPGType == _PG_MASS)
        {
            ScalerSetByte(P7_FB_D_PG_CTRL_0_R1, 0x40);    // R!=G!=B
        }
        else
        {
            ScalerSetByte(P7_FB_D_PG_CTRL_0_R1, 0x00);    // R=G=B
        }

        // R2 (Sub) Setting
        ScalerSetByte(P87_F0_DISP_PG_R_CTRL_R2, 0xC0);
        ScalerSetByte(P87_F1_DISP_PG_G_CTRL_R2, 0x00);
        ScalerSetByte(P87_F2_DISP_PG_B_CTRL_R2, 0x00);
        ScalerSetByte(P87_F3_DISP_PG_R_INITIAL_R2, 0x00);
        ScalerSetByte(P87_F4_DISP_PG_G_INITIAL_R2, 0x00);
        ScalerSetByte(P87_F5_DISP_PG_B_INITIAL_R2, 0x00);

        if(enumPGBitNode == _PG_MODE_12)
        {
            ScalerSetByte(P87_FC_D_PG_INITIAL_M_STEP_L_R2, 0x00);
            ScalerSetByte(P87_FD_D_PG_INITIAL_L_CTRL_R2, 0x95);
        }
        else
        {
            ScalerSetByte(P87_FC_D_PG_INITIAL_M_STEP_L_R2, 0x15);
            ScalerSetByte(P87_FD_D_PG_INITIAL_L_CTRL_R2, 0x00);
        }

        if(enumPGType == _PG_MASS)
        {
            ScalerSetByte(P87_FB_D_PG_CTRL_0_R2, 0x40);    // R!=G!=B
        }
        else
        {
            ScalerSetByte(P87_FB_D_PG_CTRL_0_R2, 0x00);    // R=G=B
        }
    }
    else
    {
        // Restore default value
        // R1 (Front)
        ScalerSetByte(P7_F0_DISP_PG_R_CTRL_R1, 0x00);
        ScalerSetByte(P7_FB_D_PG_CTRL_0_R1, 0x00);
        ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L_R1, 0x15);
        ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL_R1, 0x00);

        // R2 (Sub)
        ScalerSetByte(P87_F0_DISP_PG_R_CTRL_R2, 0x00);
        ScalerSetByte(P87_FB_D_PG_CTRL_0_R2, 0x00);
        ScalerSetByte(P87_FC_D_PG_INITIAL_M_STEP_L_R2, 0x15);
        ScalerSetByte(P87_FD_D_PG_INITIAL_L_CTRL_R2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable I Domain Random Generator
// Input Value  : bRandomSelect ---> 0: R = G = B, 1: R != G != B
// Output Value : None
//--------------------------------------------------
void ScalerColorPatternGenIDomainControl(EnumPGType enumPGType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(enumPGType == _PG_GRAY)
        {
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_10_I_PG_CTRL_0_M1, ~(_BIT7 | _BIT6), _BIT7);
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_10_I_PG_CTRL_0_M2, ~(_BIT7 | _BIT6), _BIT7);
            ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_10_I_PG_CTRL_0_S1, ~(_BIT7 | _BIT6), _BIT7);
        }
        else
        {
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_10_I_PG_CTRL_0_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_10_I_PG_CTRL_0_M2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_10_I_PG_CTRL_0_S1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
    }
    else
    {
        ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_10_I_PG_CTRL_0_M1, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_10_I_PG_CTRL_0_M2, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_10_I_PG_CTRL_0_S1, ~(_BIT7 | _BIT6), 0x00);
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable VGATOP Pattern Generator
// Input Value  : bRandomSelect ---> 0: R = G = B, 1: R != G != B
// Output Value : None
//--------------------------------------------------
void ScalerColorPatternGenVGATopControl(EnumPGType enumPGType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set default initial value
        ScalerSetByte(P30_DF_VGATOP_PAT_GEN_RED_INI_L, 0x01);
        ScalerSetByte(P30_E0_VGATOP_PAT_GEN_GRN_INI_L, 0x01);
        ScalerSetByte(P30_E1_VGATOP_PAT_GEN_BLU_INI_L, 0x01);

        if(enumPGType == _PG_GRAY)
        {
            ScalerSetBit(P30_DD_VGATOP_PAT_GEN_CTRL0, ~_BIT6, 0x00);
        }
        else
        {
            ScalerSetBit(P30_DD_VGATOP_PAT_GEN_CTRL0, ~_BIT6, _BIT6);
        }

        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT7, 0x00);
    }
}
#endif


