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
// ID Code      : ScalerColorLSR.c
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
#if(_COLOR_IP_LSR == _ON)
//--------------------------------------------------
// Description  : Get LSR HLW Status (Only Demo mode)
// Input Value  : EnumDDomainRegion
// Output Value : EnumColorLSRHLWType
// 1P or PIP or PBP_LR
// inside(SetB)  outside(SetA)  0x11B9  Bit7  Bit6  Bit5  Bit4    LSREnable
//    ON                 OFF             1     0     0      1          1
//    ON                 ON              1     1     1      0          1
//    OFF                OFF             1     0     0      0          0
//    OFF                ON              1     1     0      0          1
//--------------------------------------------------
EnumLSRHLWType ScalerColorLSRHLWGetStatus(EnumDDomainRegion enumDDomainRegion)
{
    WORD usLSRPage = ScalerColorLSRPageMapping(enumDDomainRegion);
    WORD usHLWPage = ScalerColorLSRHLWPageMapping(enumDDomainRegion);

    if((ScalerGetBit(P11_11_LSR_CTRL_R1_A1 + usLSRPage, _BIT7) == 0x00) ||
       (ScalerGetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, _BIT7) == 0x00))
    {
        return _LSR_HLW_TYPE_OFF_OFF;
    }
    else
    {
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
        switch(ScalerGetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, (_BIT6 | _BIT5 | _BIT4)))
        {
            case (_BIT6):
                return _LSR_HLW_TYPE_OFF_ON;
            case (_BIT4):
                return _LSR_HLW_TYPE_ON_OFF;
            case (_BIT6 | _BIT5):
                return _LSR_HLW_TYPE_ON_ON;
            default:
                return _LSR_HLW_TYPE_OFF_OFF;
        }
#else
        switch(ScalerGetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, (_BIT6)))
        {
            case (_BIT6):
                return _LSR_HLW_TYPE_OFF_ON;
            default:
                return _LSR_HLW_TYPE_ON_OFF;
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Set LSR HLW (Only Demo mode)
// Input Value  : EnumDDomainRegion, EnumColorLSRHLWType
// Output Value : None
//--------------------------------------------------
void ScalerColorLSRHLWSetting(EnumDDomainRegion enumDDomainRegion, EnumLSRHLWType enumLSRHLWType)
{
    WORD usLSRPage = ScalerColorLSRPageMapping(enumDDomainRegion);
    WORD usHLWPage = ScalerColorLSRHLWPageMapping(enumDDomainRegion);

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    switch(enumLSRHLWType)
    {
        case _LSR_HLW_TYPE_OFF_OFF:
        default:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usLSRPage, ~_BIT7, 0x00);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            break;

        case _LSR_HLW_TYPE_OFF_ON:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usLSRPage, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            break;

        case _LSR_HLW_TYPE_ON_OFF:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usLSRPage, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
            break;

        case _LSR_HLW_TYPE_ON_ON:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usLSRPage, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
            break;
    }
#else
    switch(enumLSRHLWType)
    {
        case _LSR_HLW_TYPE_OFF_ON:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usLSRPage, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, ~(_BIT6), _BIT6);
            break;

        case _LSR_HLW_TYPE_ON_OFF:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usLSRPage, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, ~(_BIT6), 0x00);
            break;

        case _LSR_HLW_TYPE_OFF_OFF:
        default:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usLSRPage, ~_BIT7, 0x00);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usHLWPage, ~(_BIT6), 0x00);
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Get LSR HLW Status at PBP_TB (Only Demo mode)
// Input Value  : None
// Output Value : EnumColorLSRHLWType
// PBP_TB
// inside(SetA)  outside(Bypass)  0x11B9  Bit7  Bit6  Bit5  Bit4    LSREnable
//    ON                 OFF               1     0     0      0          1
//    OFF                OFF               1     0     0      0          0
//    OFF                ON                1     1     0      0          1
//--------------------------------------------------
EnumLSRHLWType ScalerColorLSRHLWPBPTBGetStatus(void)
{
    WORD usM2Offset = ScalerColorLSRPageMapping(_DDOMAIN_RGN_R1_A2);

    if((ScalerGetBit(P11_11_LSR_CTRL_R1_A1, _BIT7) == 0x00) &&
       (ScalerGetBit(P11_11_LSR_CTRL_R1_A1 + usM2Offset, _BIT7) == 0x00))
    {
        return _LSR_HLW_TYPE_OFF_OFF;
    }
    else if((ScalerGetBit(P11_CB_SCALER_LSR_HLW_R1_A1, _BIT6) == _BIT6) &&
            (ScalerGetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usM2Offset, _BIT6) == _BIT6))
    {
        return _LSR_HLW_TYPE_ON_OFF;
    }
    else
    {
        return _LSR_HLW_TYPE_OFF_ON;
    }
}

//--------------------------------------------------
// Description  : Set LSR HLW at PBP_TB (Only Demo mode)
// Input Value  : EnumColorLSRHLWType
// Output Value : None
//--------------------------------------------------
void ScalerColorLSRHLWPBPTBSetting(EnumLSRHLWType enumLSRHLWType)
{
    WORD usM2Offset = ScalerColorLSRPageMapping(_DDOMAIN_RGN_R1_A2);

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    switch(enumLSRHLWType)
    {
        case _LSR_HLW_TYPE_OFF_OFF:
        default:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1, ~_BIT7, 0x00);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usM2Offset, ~_BIT7, 0x00);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usM2Offset, ~(_BIT6), 0x00);
            break;

        case _LSR_HLW_TYPE_OFF_ON:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usM2Offset, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usM2Offset, ~(_BIT6), _BIT6);
            break;

        case _LSR_HLW_TYPE_ON_OFF:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usM2Offset, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usM2Offset, ~(_BIT6), 0x00);
            break;
    }
#else
    switch(enumLSRHLWType)
    {
        case _LSR_HLW_TYPE_OFF_ON:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1, ~(_BIT6), _BIT6);
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usM2Offset, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usM2Offset, ~(_BIT6), _BIT6);
            break;

        case _LSR_HLW_TYPE_ON_OFF:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1, ~(_BIT6), 0x00);
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usM2Offset, ~_BIT7, _BIT7);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usM2Offset, ~(_BIT6), 0x00);
            break;

        case _LSR_HLW_TYPE_OFF_OFF:
        default:
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1, ~_BIT7, 0x00);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1, ~(_BIT6), 0x00);
            ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + usM2Offset, ~_BIT7, 0x00);
            ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usM2Offset, ~(_BIT6), 0x00);
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Set LSR Function Enable/Disable
// Input Value  : EnumDDomainRegion, bOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLSREnable(EnumDDomainRegion enumDDomainRegion, bit bOn)
{
    ScalerSetBit(P11_11_LSR_CTRL_R1_A1 + ScalerColorLSRPageMapping(enumDDomainRegion), ~_BIT7, ((BYTE)bOn << 7));
}

//--------------------------------------------------
// Description  : Set LSR Settings
// Input Value  : EnumSelRegion, bOn
// Output Value : None
// 1P or PIP(under 4K) or PBP_LR
// inside(SetB)  outside(SetA)  0x11B9  Bit7  Bit6  Bit5  Bit4    LSREnable
//    ON                 OFF             1     0     0      1          1
//    ON                 ON              1     1     1      0          1
//    OFF                OFF             1     0     0      0          0
//    OFF                ON              1     1     0      0          1
//
// PBP_TB
// inside(SetA)  outside(Bypass)  0x11B9  Bit7  Bit6  Bit5  Bit4    LSREnable
//    ON                 OFF               1     0     0      0          1
//    OFF                OFF               1     0     0      0          0
//    OFF                ON                1     1     0      0          1
//-----------------------------------------------------------------------------------
void ScalerColorLSRRegionEnable(EnumSelRegion enumSelRegion, bit bOn)
{
    // LSR HLW Disable when display mode over 2P
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() >= _DISPLAY_MODE_3P_FLAG)
    {
        ScalerColorLSRHLWEnable(_FUNCTION_OFF);
    }
#endif

    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            }
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            }
            break;

        case _2P_PIP_SUB:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            }
            break;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);

            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)

        case _2P_PBP_LR_EQUAL_L:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            break;

        case _2P_PBP_LR_L_LARGE_L:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                {
                    ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, _OFF);
                }
                else
                {
                    ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                }
            }
#endif
            break;

        case _2P_PBP_LR_R_LARGE_L:
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;

        case _2P_PBP_LR_R_LARGE_R:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                {
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, _OFF);
                }
                else
                {
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                }
            }
            else
#endif
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            }
            break;

        case _2P_PBP_TB_B:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A2, bOn);
            }
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_L:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            break;

        case _3P_FLAG_R:
            ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            break;

        case _3P_FLAG_M:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;

        case _3P_FLAG_M_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            break;

        case _3P_FLAG_L_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            break;

        case _3P_FLAG_R_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
        case _3P_SKEW_R_T:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            break;

        case _3P_SKEW_L_T:
        case _3P_SKEW_R_M:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;

        case _3P_SKEW_R_B:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            break;

        case _3P_SKEW_L_B:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
            break;

        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;

        case _3P_SKEW_L_M_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
            break;

        case _3P_SKEW_L_T_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
            break;

        case _3P_SKEW_R_M_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            break;

        case _3P_SKEW_R_T_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            }
            break;

        case _3P_SKEW_T_L:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            break;

        case _3P_SKEW_T_R:
        case _3P_SKEW_B_R:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;

        case _3P_SKEW_B_M:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A2, bOn);
            }
            break;

        case _3P_SKEW_B_L:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            break;

        case _3P_SKEW_T_M_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;

        case _3P_SKEW_T_L_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            }
            break;

        case _3P_SKEW_T_R_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
            }
            break;

        case _3P_SKEW_B_M_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;

        case _3P_SKEW_B_L_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A2, bOn);
            }
            break;

        case _3P_SKEW_B_R_OUTSIDE:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerColorLSREnable(_DDOMAIN_RGN_R3_A2, bOn);
            }
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            break;

        case _4P_RT:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;

        case _4P_LB:
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            break;

        case _4P_RB:
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
            break;

        case _4P_LT_OUTSIDE: // Except M1
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
            break;

        case _4P_LB_OUTSIDE: // Except M2
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
            break;

        case _4P_RT_OUTSIDE: // Except S1
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
            break;

        case _4P_RB_OUTSIDE: // Except S2
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
            ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
            break;
#endif

        case _FULL_REGION:
            switch(GET_DISPLAY_MODE())
            {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                    }
                    break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                    }
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, _OFF);
                        }
                        else
                        {
                            ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                        }
                    }
#endif
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, _OFF);
                        }
                        else
                        {
                            ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                        }
                    }
                    else
#endif
                    {
                        ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    }
                    break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A2, bOn);
                    }
                    break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                    break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_L:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
                    break;

                case _DISPLAY_MODE_3P_SKEW_R:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, bOn);
                    }
                    break;

                case _DISPLAY_MODE_3P_SKEW_B:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A2, bOn);
                    }
                    break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A2, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A1, bOn);
                    ScalerColorLSREnable(_DDOMAIN_RGN_R2_A2, bOn);
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
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x01) | ((BYTE)bOn << 1)));
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x01) | ((BYTE)bOn << 1)));
                    }
                    break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x01) | ((BYTE)bOn << 1)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x01) | ((BYTE)bOn << 1)));
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x01) | ((BYTE)bOn << 1)));
                    }
                    break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x01) | ((BYTE)bOn << 1)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x01) | ((BYTE)bOn << 1)));
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x01) | ((BYTE)bOn << 1)));
                    }
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x01) | ((BYTE)bOn << 1)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x01) | ((BYTE)bOn << 1)));
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x01) | ((BYTE)bOn << 1)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x01) | ((BYTE)bOn << 1)));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, _LSR_HLW_TYPE_OFF_OFF);
                        }
                        else
                        {
                            ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x01) | ((BYTE)bOn << 1)));
                        }
                    }
#endif
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x01) | ((BYTE)bOn << 1)));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x01) | ((BYTE)bOn << 1)));
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, _LSR_HLW_TYPE_OFF_OFF);
                        }
                        else
                        {
                            ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x01) | ((BYTE)bOn << 1)));
                        }
                    }
                    else
#endif
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x01) | ((BYTE)bOn << 1)));
                    }
                    break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x01) | ((BYTE)bOn << 1)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A2, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A2) & 0x01) | ((BYTE)bOn << 1)));
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x01) | ((BYTE)bOn << 1)));
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A2, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A2) & 0x01) | ((BYTE)bOn << 1)));
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
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x02) | ((BYTE)bOn)));
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x02) | ((BYTE)bOn)));
                    }
                    break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x02) | ((BYTE)bOn)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x02) | ((BYTE)bOn)));
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x02) | ((BYTE)bOn)));
                    }
                    break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x02) | ((BYTE)bOn)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x02) | ((BYTE)bOn)));
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x02) | ((BYTE)bOn)));
                    }
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x02) | ((BYTE)bOn)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x02) | ((BYTE)bOn)));
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x02) | ((BYTE)bOn)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x02) | ((BYTE)bOn)));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, _LSR_HLW_TYPE_OFF_OFF);
                        }
                        else
                        {
                            ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x02) | ((BYTE)bOn)));
                        }
                    }
#endif
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R2_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R2_A1) & 0x02) | ((BYTE)bOn)));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x02) | ((BYTE)bOn)));
                        if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _TRUE)
                        {
                            ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, _LSR_HLW_TYPE_OFF_OFF);
                        }
                        else
                        {
                            ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x02) | ((BYTE)bOn)));
                        }
                    }
                    else
#endif
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x02) | ((BYTE)bOn)));
                    }
                    break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A1) & 0x02) | ((BYTE)bOn)));
                    ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R1_A2, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R1_A2) & 0x02) | ((BYTE)bOn)));
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A1, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A1) & 0x02) | ((BYTE)bOn)));
                        ScalerColorLSRHLWSetting(_DDOMAIN_RGN_R3_A2, (EnumLSRHLWType)(((BYTE)ScalerColorLSRHLWGetStatus(_DDOMAIN_RGN_R3_A2) & 0x02) | ((BYTE)bOn)));
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


//--------------------------------------------------
// Description  : LSR Display Path mapping register Page
// Input Value  : enumDDomainRegion
// Output Value : usPage
//--------------------------------------------------
WORD ScalerColorLSRPageMapping(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            return 0x0000U;

        case _DDOMAIN_RGN_R1_A2:
            return 0x0050U;

        case _DDOMAIN_RGN_R2_A1:
            return 0x4000U;

        case _DDOMAIN_RGN_R2_A2:
            return 0x4050U;

        case _DDOMAIN_RGN_R3_A1:
            return 0x8000U;

        case _DDOMAIN_RGN_R3_A2:
            return 0x8050U;
    }
}

//--------------------------------------------------
// Description  : LSR HLW Path mapping register Page
// Input Value  : enumDDomainRegion
// Output Value : usPage
//--------------------------------------------------
WORD ScalerColorLSRHLWPageMapping(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            return 0x0000U;

        case _DDOMAIN_RGN_R1_A2:
            return 0x0020U;

        case _DDOMAIN_RGN_R2_A1:
            return 0x4000U;

        case _DDOMAIN_RGN_R2_A2:
            return 0x4020U;

        case _DDOMAIN_RGN_R3_A1:
            return 0x8000U;

        case _DDOMAIN_RGN_R3_A2:
            return 0x8020U;
    }
}

//--------------------------------------------------
// Description  : Adjust UltraVivid highlight window region
// Input Value  : usHPos, usHWidth, usVPos, usVHeight
// Output Value : None
//--------------------------------------------------
void ScalerColorLSRHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    DWORD ulScale = 0;
    WORD usBGHStart = 0;
    WORD usBGVStart = 0;
    WORD usActHStart = 0;
    WORD usActHEnd = 0;
    WORD usActVStart = 0;
    WORD usActVEnd = 0;
    WORD usIHLWHStart = 0;
    WORD usIHLWHEnd = 0;
    WORD usIHLWVStart = 0;
    WORD usIHLWVEnd = 0;
    WORD usDScalePage = 0;
    WORD usLSRHLWRegPage = 0;
    WORD usDRegPage = 0;
    BYTE ucDExtension = 0;
    BYTE ucRegSel = 0;
    bit bHSU = _FALSE;
    BYTE pucRegionActive[6] = {_FALSE, _FALSE, _FALSE, _FALSE, _FALSE, _FALSE};

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
    WORD usMidline = 0;
#endif

    if((usHWidth == 0) || (usVHeight == 0))
    {
        return;
    }

    ucDExtension = ucDExtension;

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            pucRegionActive[0] = _TRUE;
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                pucRegionActive[4] = _TRUE;
            }
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            pucRegionActive[0] = _TRUE;
            pucRegionActive[2] = _TRUE;
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                pucRegionActive[4] = _TRUE;
            }
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            pucRegionActive[0] = _TRUE;
            pucRegionActive[2] = _TRUE;
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                pucRegionActive[4] = _TRUE;
            }
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            pucRegionActive[0] = _TRUE;
            pucRegionActive[2] = _TRUE;
            break;

        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            pucRegionActive[0] = _TRUE;
            pucRegionActive[2] = _TRUE;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _FALSE)
                {
                    pucRegionActive[4] = _TRUE;
                }
            }
#endif
            break;

        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            pucRegionActive[2] = _TRUE;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                pucRegionActive[4] = _TRUE;
                if(ScalerScalingGetPBPLRSingleRegionStatus(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH)) == _FALSE)
                {
                    pucRegionActive[0] = _TRUE;
                }
            }
            else
#endif
            {
                pucRegionActive[0] = _TRUE;
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            pucRegionActive[0] = _TRUE;
            pucRegionActive[1] = _TRUE;
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                pucRegionActive[4] = _TRUE;
                pucRegionActive[5] = _TRUE;
            }
            break;
#endif

// 3P & 4P mode can not enable Demo mode
        default:
            return;
    }

    // change HLW position reference to DH/V Sync!A(Tile mode: Active size bigger than Background size!)
    // get HLW region in four Active region HLW !Areference to active
    // by HSU Factor!Aget LSR HLW region
    // Set LSR HLW regs
    // by SU/D Factor!Aget IDLTI HLW region
    // Set IDLTI HLW regs
    // if one path is without HLW!Athan disable this path's HLW

    // border width
    pData[0] = ScalerGetDataPortSingleByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_08_HLW_BORDER_WIDTH);

    if((bit)ScalerGetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, _BIT6) == 0x00)
    {
        usHWidth = usHWidth + (pData[0] & 0x1F);
    }

    if((bit)ScalerGetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, _BIT4) == 0x00)
    {
        usVHeight = usVHeight + (pData[0] & 0x1F);
    }

    usBGHStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START);
    usBGVStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);

    usHPos = usHPos + usBGHStart;
    usVPos = usVPos + usBGVStart;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ucDExtension = ScalerGetDataPortSingleByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_FRONT);
    }
#endif

    for(ucRegSel = 0; ucRegSel < 6; ucRegSel++)
    {
        if(pucRegionActive[ucRegSel] == _FALSE)
        {
            continue;
        }

        usDScalePage = ScalerColorUltraVividPageMapping((_DDOMAIN_RGN_R1_A1 << (BYTE)ucRegSel));
        usDRegPage = ScalerColorUltraVividGetIDomainRegisterPage((_DDOMAIN_RGN_R1_A1 << (BYTE)ucRegSel));

        pData[0] = ScalerGetByte(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usDScalePage);
        bHSU = ((pData[0] & _BIT0) == _BIT0) ? _TRUE : _FALSE;

        // Get Active Region
        switch(usDRegPage)
        {
            case _REG_MAIN1_PAGE: // M1
                usLSRHLWRegPage = ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R1_A1);
                usActHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                usActHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                usActVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                usActVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);
                break;

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
            case _REG_MAIN2_PAGE: // M2
                usLSRHLWRegPage = ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R1_A2);
                usActHStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START);
                usActHEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END);
                usActVStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_START);
                usActVEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END);
                break;
#endif
            case _REG_SUB1_PAGE: // S1
                usLSRHLWRegPage = ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R2_A1);
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                    usActHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usActHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usActVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usActVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);
#endif
                }
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                else
                {
                    usActHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usActHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usActVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usActVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);
                }
#endif
                break;

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
            case _REG_SUB2_PAGE: // S2
                usLSRHLWRegPage = ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R2_A2);
                usActHStart = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_H_START);
                usActHEnd = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_H_END);
                usActVStart = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_START);
                usActVEnd = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_END);
                break;
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
            case _REG_SUB3_PAGE:
                usLSRHLWRegPage = ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R3_A1);
                usActHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                usActHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                usActVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                usActVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);
                usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END)) / 2;

                switch(GET_DISPLAY_MODE())
                {
                    case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                        usActHStart = usMidline - ucDExtension;
                        break;

                    default:
                        usActHStart = ((usActHStart + usActHEnd) >> 1) - ucDExtension;
                        break;
                }
                break;
#endif

#if((_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON) && (_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON))
            case _REG_SUB4_PAGE:
                usLSRHLWRegPage = ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R3_A2);

                usActHStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START);
                usActHEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END);
                usActVStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_START);
                usActVEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END);
                usActHStart = ((usActHStart + usActHEnd) >> 1) - ucDExtension;
                break;
#endif
            default:
                break;
        }

        if((usHPos > usActHEnd) ||
           (usHPos + usHWidth <= usActHStart) ||
           (usVPos > usActVEnd) ||
           (usVPos + usVHeight <= usActVStart))
        {
            pData[0] = (BYTE)((usActHEnd >> 8) & 0x1F);
            pData[1] = (BYTE)(usActHEnd & 0xFF);
            pData[2] = (BYTE)(((usActHEnd + 1) >> 8) & 0x1F);
            pData[3] = (BYTE)((usActHEnd + 1) & 0xFF);
            pData[4] = 0x00;
            pData[5] = 0x00;
            pData[6] = 0x00;
            pData[7] = 0x00;

            ScalerWrite(P11_CC_LSR_HLW_H_START_HIGH_R1_A1 + usLSRHLWRegPage, 8, pData, _AUTOINC);

            continue;
        }

        if(usHPos >= usActHStart)
        {
            usIHLWHStart = usHPos;
        }
        else
        {
            usIHLWHStart = usActHStart;
        }

        if(usHPos + usHWidth < usActHEnd)
        {
            usIHLWHEnd = usHPos + usHWidth;
        }
        else
        {
            usIHLWHEnd = usActHEnd;
        }

        if(usVPos >= usActVStart)
        {
            usIHLWVStart = usVPos;
        }
        else
        {
            usIHLWVStart = usActVStart;
        }

        if(usVPos + usVHeight < usActVEnd)
        {
            usIHLWVEnd = usVPos + usVHeight;
        }
        else
        {
            usIHLWVEnd = usActVEnd;
        }

        usIHLWHStart = usIHLWHStart - usActHStart;
        usIHLWHEnd = usIHLWHEnd - usActHStart;
        usIHLWVStart = usIHLWVStart - usActVStart;
        usIHLWVEnd = usIHLWVEnd - usActVStart;

        if(bHSU == _TRUE)
        {
            ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usDScalePage, _P0_34_PT_00_HOR_SCALE_FACTOR_H_R1_ACTIVE1, 3, &pData[0], _AUTOINC);

            ulScale = (((DWORD)(pData[0] & 0x0F) << 16) | ((DWORD)pData[1] << 8) | (pData[2]));

            if(ulScale != 0xFFFFF)
            {
                usIHLWHStart = (((ulScale * usIHLWHStart) >> 19) + 1) >> 1;
                usIHLWHEnd = (((ulScale * usIHLWHEnd) >> 19) + 1) >> 1;
            }
        }

        // (LSR) H refers to M domain V refers to D domain
        pData[0] = (BYTE)((usIHLWHStart >> 8) & 0x1F);
        pData[1] = (BYTE)(usIHLWHStart & 0xFF);
        pData[2] = (BYTE)((usIHLWHEnd >> 8) & 0x1F);
        pData[3] = (BYTE)(usIHLWHEnd & 0xFF);
        pData[4] = (BYTE)((usIHLWVStart >> 8) & 0x1F);
        pData[5] = (BYTE)(usIHLWVStart & 0xFF);
        pData[6] = (BYTE)((usIHLWVEnd >> 8) & 0x1F);
        pData[7] = (BYTE)(usIHLWVEnd & 0xFF);

        ScalerWrite(P11_CC_LSR_HLW_H_START_HIGH_R1_A1 + usLSRHLWRegPage, 8, pData, _AUTOINC);
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + usLSRHLWRegPage, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable IDLTI, LSR,
// Input Value  : EnumFunctionOnOFF
// Output Value : none
//--------------------------------------------------
void ScalerColorLSRHLWEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
#if(_HW_D_DOMAIN_R1_A1_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1, ~_BIT7, _BIT7);
#endif

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R1_A2), ~_BIT7, _BIT7);
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R2_A1), ~_BIT7, _BIT7);
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R2_A2), ~_BIT7, _BIT7);
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R3_A1), ~_BIT7, _BIT7);
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R3_A2), ~_BIT7, _BIT7);
#endif
    }
    else
    {
        // LSR
#if(_HW_D_DOMAIN_R1_A1_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1, ~_BIT7, 0x00);
#endif

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R1_A2), ~_BIT7, 0x00);
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R2_A1), ~_BIT7, 0x00);
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R2_A2), ~_BIT7, 0x00);
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R3_A1), ~_BIT7, 0x00);
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
        ScalerSetBit(P11_CB_SCALER_LSR_HLW_R1_A1 + ScalerColorLSRHLWPageMapping(_DDOMAIN_RGN_R3_A2), ~_BIT7, 0x00);
#endif
    }
}
#endif // End of #if(_COLOR_IP_LSR == _ON)

