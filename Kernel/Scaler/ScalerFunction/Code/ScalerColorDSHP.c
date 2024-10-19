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
// ID Code      : ScalerColorDSHP.c
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
#if(_COLOR_IP_DSHP == _ON)
//--------------------------------------------------
// Description  : Set DSHP Effect Region
// Input Value  : enumDDomainRegion, enumSelRegion, bon
// Output Value : None
//--------------------------------------------------
void ScalerColorDSHPSetEffectRegion(EnumDDomainRegion enumDDomainRegion, EnumSelRegion enumSelRegion, bit bOn)
{
    EnumHLWType enumHLWType = ScalerRegionGetSelectRegionHLWArea(enumSelRegion);
    WORD usDSHPPage = ScalerColorDSHPPageMapping(enumDDomainRegion);
    BYTE ucCtrlInOutside = ScalerGetBit((P12_FC_SR_SETSEL0_R1_A1 + usDSHPPage), (_BIT7 | _BIT6));

    ScalerSetBit(P12_FC_SR_SETSEL0_R1_A1 + usDSHPPage, ~(_BIT5 | _BIT4), _BIT5);    // Set InB, OutA

    switch(enumHLWType)
    {
        case _HLW_INSIDE_WINDOW:
            ScalerSetBit((P12_FC_SR_SETSEL0_R1_A1 + usDSHPPage), ~(_BIT7 | _BIT6), (((BYTE)(!bOn) << 7) | (ucCtrlInOutside & _BIT6)));
            break;

        case _HLW_OUTSIDE_WINDOW:
            ScalerSetBit((P12_FC_SR_SETSEL0_R1_A1 + usDSHPPage), ~(_BIT7 | _BIT6), (((BYTE)(!bOn) << 6) | (ucCtrlInOutside & _BIT7)));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSHP Display Path mapping register Page
// Input Value  : enumDDomainRegion
// Output Value : usPage
//--------------------------------------------------
WORD ScalerColorDSHPPageMapping(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            return 0x0000U;

        case _DDOMAIN_RGN_R1_A2:
            return 0x0100U;

        case _DDOMAIN_RGN_R2_A1:
            return 0x4000U;

        case _DDOMAIN_RGN_R2_A2:
            return 0x4100U;

        case _DDOMAIN_RGN_R3_A1:
            return 0x4900U;

        case _DDOMAIN_RGN_R3_A2:
            return 0x4A00U;
    }
}

//--------------------------------------------------
// Description  : Set DSHP Function Enable/Disable
// Input Value  : enumDDomainRegion, enumSelRegion, bon
// Output Value : None
//--------------------------------------------------
void ScalerColorDSHPEnable(EnumDDomainRegion enumDDomainRegion, EnumSelRegion enumSelRegion, bit bOn)
{
    WORD usDSHPPage = ScalerColorDSHPPageMapping(enumDDomainRegion);

    if(bOn == _OFF)
    {
        ScalerSetBit((P12_00_SR_SHP_CTRL_0_R1_A1 + usDSHPPage), ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit((P12_01_SR_SHP_CTRL_1_R1_A1 + usDSHPPage), ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }

    if((enumSelRegion == _DEMO_INSIDE) || (enumSelRegion == _DEMO_OUTSIDE))
    {
        return;
    }
    else
    {
        switch(enumDDomainRegion)
        {
            case _DDOMAIN_RGN_R1_A1:
            case _DDOMAIN_RGN_R2_A1:
            case _DDOMAIN_RGN_R3_A1:
            default:
                ScalerSetByte((P12_FC_SR_SETSEL0_R1_A1 + usDSHPPage), 0x00);   // HLW InSetA, OutSetA
                break;

            case _DDOMAIN_RGN_R1_A2:
            case _DDOMAIN_RGN_R2_A2:
            case _DDOMAIN_RGN_R3_A2:
                ScalerSetByte((P12_FC_SR_SETSEL0_R1_A1 + usDSHPPage), 0x30);   // HLW InSetB, OutSetB
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Set DSHP Settings
// Input Value  : EnumSelRegion, bOn
// Output Value : None
//-----------------------------------------------------------------------------------
void ScalerColorDSHPRegionEnable(EnumSelRegion enumSelRegion, bit bOn)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            }
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            }
            break;

        case _2P_PIP_SUB:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            }
            break;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)

        case _2P_PBP_LR_EQUAL_L:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            break;

        case _2P_PBP_LR_L_LARGE_L:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                {
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, _OFF);
                }
                else
#endif
                {
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                }
            }
            break;

        case _2P_PBP_LR_R_LARGE_L:
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;

        case _2P_PBP_LR_R_LARGE_R:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                {
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, _OFF);
                }
                else
#endif
                {
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                }
            }
            else
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            }
            break;

        case _2P_PBP_TB_B:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
            }
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_L:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            break;

        case _3P_FLAG_R:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            break;

        case _3P_FLAG_M:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;

        case _3P_FLAG_M_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            break;

        case _3P_FLAG_L_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            break;

        case _3P_FLAG_R_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
        case _3P_SKEW_R_T:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            break;

        case _3P_SKEW_L_T:
        case _3P_SKEW_R_M:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;

        case _3P_SKEW_R_B:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            break;

        case _3P_SKEW_L_B:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
            break;

        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;

        case _3P_SKEW_L_M_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
            break;

        case _3P_SKEW_L_T_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
            break;

        case _3P_SKEW_R_M_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            break;

        case _3P_SKEW_R_T_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            }
            break;

        case _3P_SKEW_T_L:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            break;

        case _3P_SKEW_T_R:
        case _3P_SKEW_B_R:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;

        case _3P_SKEW_B_M:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
            }
            break;

        case _3P_SKEW_B_L:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            break;

        case _3P_SKEW_T_M_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;

        case _3P_SKEW_T_L_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            }
            break;

        case _3P_SKEW_T_R_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
            }
            break;

        case _3P_SKEW_B_M_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;

        case _3P_SKEW_B_L_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
            }
            break;

        case _3P_SKEW_B_R_OUTSIDE:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
            }
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            break;

        case _4P_RT:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;

        case _4P_LB:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            break;

        case _4P_RB:
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
            break;

        case _4P_LT_OUTSIDE: // Except M1
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
            break;

        case _4P_LB_OUTSIDE: // Except M2
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
            break;

        case _4P_RT_OUTSIDE: // Except S1
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
            break;

        case _4P_RB_OUTSIDE: // Except S2
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
            ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
            break;
#endif

        case _FULL_REGION:
            switch(GET_DISPLAY_MODE())
            {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, _OFF);
                        }
                        else
#endif
                        {
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        }
                    }
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, _OFF);
                        }
                        else
#endif
                        {
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                        }
                    }
                    else
                    {
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                    break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_L:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
                    break;

                case _DISPLAY_MODE_3P_SKEW_R:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                    }
                    break;

                case _DISPLAY_MODE_3P_SKEW_B:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
                    break;
#endif

                default:
                    break;
            }
            break;

        case _DEMO_INSIDE:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                    }
                    break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, _OFF);
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, _OFF);
                        }
                        else
#endif
                        {
                            ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                        }
                    }
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A2, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, _OFF);
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, _OFF);
                        }
                        else
#endif
                        {
                            ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                        }
                    }
                    else
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                    }
                    break;
#endif

                default:
                    break;
            }
            break;

        case _DEMO_OUTSIDE:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                    }
                    break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, _OFF);
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, _OFF);
                        }
                        else
#endif
                        {
                            ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        }
                    }
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R2_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, _OFF);
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, _OFF);
                        }
                        else
#endif
                        {
                            ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                            ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                        }
                    }
                    else
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    }
                    break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R1_A2, enumSelRegion, bOn);
                    ScalerColorDSHPEnable(_DDOMAIN_RGN_R1_A1, enumSelRegion, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                        ScalerColorDSHPSetEffectRegion(_DDOMAIN_RGN_R3_A2, enumSelRegion, bOn);
                        ScalerColorDSHPEnable(_DDOMAIN_RGN_R3_A1, enumSelRegion, bOn);
                    }
                    break;
#endif
                default:
                    break;
            }
            break;

        default:
            break;
    }
}

#endif // End of #if(_COLOR_IP_DSHP == _ON)
