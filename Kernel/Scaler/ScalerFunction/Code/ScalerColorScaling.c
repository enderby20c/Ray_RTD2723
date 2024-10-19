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
// ID Code      : ScalerColorScaling.c
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

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Scaling By pass
// Input Value  : enumSelRegion
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerColorScalingByPassTableSel(EnumSelRegion enumSelRegion)
{
    if((ScalerColorScalingGetScalingUpBypassStatus(enumSelRegion) == _TRUE) && (ScalerColorScalingGetScalingDownBypassStatus(enumSelRegion) == _TRUE))
    {
        return _TRUE;
    }
    return _FALSE;
}

#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_0)
//--------------------------------------------------
// Description  : Set Scale Down Mask LSB
// Input Value  : input data path
// Output Value : none
//--------------------------------------------------
void ScalerColorScalingDownSetMaskLSB(EnumInputDataPath enumInputDataPath)
{
    BYTE ucColorDepth = ScalerMDomainGetColorDepth();

    switch(enumInputDataPath)
    {
#if(_HW_I_DOMAIN_M1_M2_PATH_SUPPORT == _ON)
        case _INPUT_PATH_M1_M2:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_HW_I_DOMAIN_S1_S2_PATH_SUPPORT == _ON)
        case _INPUT_PATH_S1_S2:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_HW_I_DOMAIN_S3_S4_PATH_SUPPORT == _ON)
        case _INPUT_PATH_S3_S4:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(P17_26_SD_FILTER_CONTROL_REG_S3, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    ScalerSetBit(PDC_26_SD_FILTER_CONTROL_REG_S4, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(P17_26_SD_FILTER_CONTROL_REG_S3, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    ScalerSetBit(PDC_26_SD_FILTER_CONTROL_REG_S4, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(P17_26_SD_FILTER_CONTROL_REG_S3, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    ScalerSetBit(PDC_26_SD_FILTER_CONTROL_REG_S4, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_HW_I_DOMAIN_M1_PATH_SUPPORT == _ON)
        case _INPUT_PATH_M1:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
        case _INPUT_PATH_M2:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
        case _INPUT_PATH_S1:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
        case _INPUT_PATH_S2:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
        case _INPUT_PATH_S3:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(P17_26_SD_FILTER_CONTROL_REG_S3, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(P17_26_SD_FILTER_CONTROL_REG_S3, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(P17_26_SD_FILTER_CONTROL_REG_S3, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON)
        case _INPUT_PATH_S4:
            switch(ucColorDepth)
            {
                case _COLOR_DEPTH_8_BITS:
                    ScalerSetBit(PDC_26_SD_FILTER_CONTROL_REG_S4, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                    break;

                case _COLOR_DEPTH_10_BITS:
                    ScalerSetBit(PDC_26_SD_FILTER_CONTROL_REG_S4, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                    break;

                case _COLOR_DEPTH_6_BITS:
                    ScalerSetBit(PDC_26_SD_FILTER_CONTROL_REG_S4, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                    break;

                default:
                    break;
            }
            break;
#endif

#if((_HW_I_DOMAIN_M1_M2_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S1_S2_PATH_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON))
        case _INPUT_PATH_M1_M2_S1_S2:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
            {
                switch(ucColorDepth)
                {
                    case _COLOR_DEPTH_8_BITS:
                        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                        ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                        ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                        ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT0));
                        break;

                    case _COLOR_DEPTH_10_BITS:
                        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                        ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                        ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                        ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), 0x00);
                        break;

                    case _COLOR_DEPTH_6_BITS:
                        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                        ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                        ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                        ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);
                        break;

                    default:
                        break;
                }
            }
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get Scaling up By pass Page
// Input Value  : EnumSelRegion
// Output Value : EnumSUBypassPage
//--------------------------------------------------
EnumSUBypassPage ScalerColorScalingGetByPassTableRegPage(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            return _SU_BYPASS_R1_A1_PAGE;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            return _SU_BYPASS_R1_A1_PAGE;

        case _2P_PIP_SUB:
            return _SU_BYPASS_R2_A1_PAGE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            return _SU_BYPASS_R1_A1_PAGE;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            return _SU_BYPASS_R2_A1_PAGE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
            return _SU_BYPASS_R1_A1_PAGE;

        case _2P_PBP_LR_R_LARGE_L:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return _SU_BYPASS_R2_A1_PAGE;
            }
            else
            {
                return _SU_BYPASS_R1_A1_PAGE;
            }

        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
            return _SU_BYPASS_R2_A1_PAGE;

        case _2P_PBP_LR_R_LARGE_R:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return _SU_BYPASS_R1_A1_PAGE;
            }
            else
            {
                return _SU_BYPASS_R2_A1_PAGE;
            }
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            return _SU_BYPASS_R1_A1_PAGE;

        case _2P_PBP_TB_B:
            return _SU_BYPASS_R1_A2_PAGE;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_L:
            return _SU_BYPASS_R1_A1_PAGE;

        case _3P_FLAG_R:
            return _SU_BYPASS_R3_A1_PAGE;

        case _3P_FLAG_M:
            return _SU_BYPASS_R2_A1_PAGE;

        case _3P_FLAG_L_OUTSIDE:
        case _3P_FLAG_R_OUTSIDE:
        case _3P_FLAG_M_OUTSIDE:
            return _SU_BYPASS_NONE_PAGE;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
        case _3P_SKEW_R_T:
            return _SU_BYPASS_R1_A1_PAGE;

        case _3P_SKEW_L_T:
        case _3P_SKEW_R_M:
            return _SU_BYPASS_R2_A1_PAGE;

        case _3P_SKEW_L_B:
            return _SU_BYPASS_R2_A2_PAGE;

        case _3P_SKEW_R_B:
            return _SU_BYPASS_R1_A2_PAGE;

        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
        case _3P_SKEW_L_T_OUTSIDE:
        case _3P_SKEW_R_M_OUTSIDE:
        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
            return _SU_BYPASS_NONE_PAGE;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
        case _3P_SKEW_B_L:
            return _SU_BYPASS_R1_A1_PAGE;

        case _3P_SKEW_T_L:
        case _3P_SKEW_B_M:
            return _SU_BYPASS_R1_A2_PAGE;

        case _3P_SKEW_T_R:
        case _3P_SKEW_B_R:
            return _SU_BYPASS_R2_A1_PAGE;

        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_B_M_OUTSIDE:
        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
            return _SU_BYPASS_NONE_PAGE;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
            return _SU_BYPASS_R1_A1_PAGE;

        case _4P_LB:
            return _SU_BYPASS_R1_A2_PAGE;

        case _4P_RT:
            return _SU_BYPASS_R2_A1_PAGE;

        case _4P_RB:
            return _SU_BYPASS_R2_A2_PAGE;

        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
            return _SU_BYPASS_NONE_PAGE;
#endif

        case _FULL_REGION:
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
        default:
            return _SU_BYPASS_NONE_PAGE;
    }
}

//--------------------------------------------------
// Description  : Get Scaling By pass
// Input Value  : enumSelRegion
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerColorScalingGetScalingUpBypassStatus(EnumSelRegion enumSelRegion)
{
    EnumSUBypassPage enumPage = 0;
    enumPage = ScalerColorScalingGetByPassTableRegPage(enumSelRegion);

    switch(enumPage)
    {
        case _SU_BYPASS_R1_A1_PAGE:
        case _SU_BYPASS_R1_A2_PAGE:
        case _SU_BYPASS_R2_A1_PAGE:
        case _SU_BYPASS_R2_A2_PAGE:
        case _SU_BYPASS_R3_A1_PAGE:
        case _SU_BYPASS_R3_A2_PAGE:
            ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + enumPage, _P0_34_PT_03_VER_SCALE_FACTOR_H_R1_ACTIVE1, 3, &pData[0], _AUTOINC);
            ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + enumPage, _P0_34_PT_00_HOR_SCALE_FACTOR_H_R1_ACTIVE1, 3, &pData[3], _AUTOINC);

            if(((pData[0] & 0x0F) == 0x0F) && (pData[1] == 0xFF) && (pData[2] == 0xFF) &&
               ((pData[3] & 0x0F) == 0x0F) && (pData[4] == 0xFF) && (pData[5] == 0xFF))
            {
                return _TRUE;
            }
            break;

        case _SU_BYPASS_NONE_PAGE:
        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Scale Down Bypass Status
// Input Value  : enumSelRegion
// Output Value : TRUE, FALSE
//--------------------------------------------------
bit ScalerColorScalingGetScalingDownBypassStatus(EnumSelRegion enumSelRegion)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_I_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetIDomainRegisterPage(enumSelRegion);
#endif

    ScalerGetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usPage, _P0_25_PT_05_H_SD_FACTOR_H_M1, 3, &pData[0], _AUTOINC);
    ScalerGetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usPage, _P0_25_PT_01_V_SD_FACTOR_H_M1, 3, &pData[3], _AUTOINC);
    ScalerGetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usPage, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 1, &pData[6], _AUTOINC);

    if((pData[0] == 0x10) && (pData[1] == 0x00) && (pData[2] == 0x00) &&
       ((pData[3] == 0x02) && (pData[4] == 0x00) && (pData[5] == 0x00) && ((pData[6] & 0xE0) == 0x00)))
    {
        return _TRUE;
    }
    return _FALSE;
}
