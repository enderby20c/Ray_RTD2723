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
// ID Code      : ScalerRegion.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_REGION__

#include "ScalerFunctionInclude.h"
#include "Region/ScalerRegion.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
EnumDisplayMode g_enumRegionDisplayMode;
StructRegionIndexInfo g_stRegionIndexInfo;
StructPbplrRatio g_stRegionPbplrRatio;
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enabel Global Watch Dog by Region
// Input Value  : enumDisplayRegion --> system select region
//                bEnable -->_ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerRegionSetWatchDog(EnumDisplayRegion enumDisplayRegion, bit bEnable)
{
    ScalerGlobalPathWatchDog(ScalerRegionGetInputDataPath(enumDisplayRegion), bEnable);
}

//--------------------------------------------------
// Description  : Update maximum display region count: (1 ~ 4)
// Input Value  : None
// Output Value : region count
//--------------------------------------------------
BYTE ScalerRegionGetMaxRegionCount(void)
{
    switch(GET_DISPLAY_MODE())
    {
        default:
        case _DISPLAY_MODE_1P:
            return 1;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            return 2;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            return 2;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            return 2;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            return 2;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            return 3;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:
            return 3;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_3P_SKEW_B:
            return 3;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            return 4;
#endif
    }
}

//--------------------------------------------------
// Description  : Convert display region to region index
// Input Value  : enumDisplayRegion --> target region
// Output Value : region index (0 ~ 3) or _REGION_INDEX_NONE
//--------------------------------------------------
EnumRegionIndex ScalerRegionGetIndex(EnumDisplayRegion enumDisplayRegion)
{
    if(enumDisplayRegion == _DISPLAY_RGN_NONE)
    {
        return _REGION_INDEX_0;
    }
    else
    {
        EnumRegionIndex enumRegionIndex = (EnumRegionIndex)((enumDisplayRegion) & 0x03);

        if(enumRegionIndex >= _MULTI_DISPLAY_MAX)
        {
            enumRegionIndex = _REGION_INDEX_0;
        }

        return enumRegionIndex;
    }
}

//--------------------------------------------------
// Description  : Convert region index to DDomainDB apply region
// Input Value  : enumRegionIndex --> region index
// Output Value : DDomainDB apply region
//--------------------------------------------------
EnumDDomainDBApplyRegion ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            return _D_DOMAIN_DB_APPLY_REGION_INDEX_0;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            return _D_DOMAIN_DB_APPLY_REGION_INDEX_0;

        case _2P_PIP_SUB:
            return _D_DOMAIN_DB_APPLY_REGION_INDEX_1;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            return _D_DOMAIN_DB_APPLY_REGION_INDEX_0;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            return _D_DOMAIN_DB_APPLY_REGION_INDEX_1;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
            return _D_DOMAIN_DB_APPLY_REGION_INDEX_0;

        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_L:
            return _D_DOMAIN_DB_APPLY_REGION_INDEX_1;

#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
        case _2P_PBP_TB_B:
            return _D_DOMAIN_DB_APPLY_REGION_INDEX_0;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M:
        case _3P_FLAG_L:
        case _3P_FLAG_R:
        case _3P_FLAG_M_OUTSIDE:
        case _3P_FLAG_L_OUTSIDE:
        case _3P_FLAG_R_OUTSIDE:
            return _D_DOMAIN_DB_APPLY_REGION_EITHER;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
        case _3P_SKEW_L_T:
        case _3P_SKEW_L_B:
        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_L_T_OUTSIDE:
        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_M:
        case _3P_SKEW_R_T:
        case _3P_SKEW_R_B:
        case _3P_SKEW_R_M_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
            return _D_DOMAIN_DB_APPLY_REGION_EITHER;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
        case _3P_SKEW_T_L:
        case _3P_SKEW_T_R:
        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_B_M:
        case _3P_SKEW_B_L:
        case _3P_SKEW_B_R:
        case _3P_SKEW_B_M_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
            return _D_DOMAIN_DB_APPLY_REGION_EITHER;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
        case _4P_LB:
        case _4P_RT:
        case _4P_RB:
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
            return _D_DOMAIN_DB_APPLY_REGION_EITHER;
#endif

        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
        case _FULL_REGION:
        default:
            return _D_DOMAIN_DB_APPLY_REGION_EITHER;
    }
}

//--------------------------------------------------
// Description  : Get Inverse SelRegion from SelRegion
// Input Value  : EnumSelRegion
// Output Value : EnumSelRegion
//--------------------------------------------------
EnumSelRegion ScalerRegionGetInverse(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
        case _FULL_REGION:
            return _NON_REGION;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            return _2P_PIP_SUB;

        case _2P_PIP_SUB:
            return _2P_PIP_MAIN;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            return _2P_PIP_EAGLE_SIGHT_SUB;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            return _2P_PIP_EAGLE_SIGHT_MAIN;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
            return _2P_PBP_LR_EQUAL_R;

        case _2P_PBP_LR_EQUAL_R:
            return _2P_PBP_LR_EQUAL_L;

        case _2P_PBP_LR_L_LARGE_L:
            return _2P_PBP_LR_L_LARGE_R;

        case _2P_PBP_LR_L_LARGE_R:
            return _2P_PBP_LR_L_LARGE_L;

        case _2P_PBP_LR_R_LARGE_L:
            return _2P_PBP_LR_R_LARGE_R;

        case _2P_PBP_LR_R_LARGE_R:
            return _2P_PBP_LR_R_LARGE_L;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            return _2P_PBP_TB_B;

        case _2P_PBP_TB_B:
            return _2P_PBP_TB_T;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M:
            return _3P_FLAG_M_OUTSIDE;

        case _3P_FLAG_L:
            return _3P_FLAG_L_OUTSIDE;

        case _3P_FLAG_R:
            return _3P_FLAG_R_OUTSIDE;

        case _3P_FLAG_M_OUTSIDE:
            return _3P_FLAG_M;

        case _3P_FLAG_L_OUTSIDE:
            return _3P_FLAG_L;

        case _3P_FLAG_R_OUTSIDE:
            return _3P_FLAG_R;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
            return _3P_SKEW_L_M_OUTSIDE;

        case _3P_SKEW_L_T:
            return _3P_SKEW_L_T_OUTSIDE;

        case _3P_SKEW_L_B:
            return _3P_SKEW_L_B_OUTSIDE;

        case _3P_SKEW_L_M_OUTSIDE:
            return _3P_SKEW_L_M;

        case _3P_SKEW_L_T_OUTSIDE:
            return _3P_SKEW_L_T;

        case _3P_SKEW_L_B_OUTSIDE:
            return _3P_SKEW_L_B;

        case _3P_SKEW_R_M:
            return _3P_SKEW_R_M_OUTSIDE;

        case _3P_SKEW_R_T:
            return _3P_SKEW_R_T_OUTSIDE;

        case _3P_SKEW_R_B:
            return _3P_SKEW_R_B_OUTSIDE;

        case _3P_SKEW_R_M_OUTSIDE:
            return _3P_SKEW_R_M;

        case _3P_SKEW_R_T_OUTSIDE:
            return _3P_SKEW_R_T;

        case _3P_SKEW_R_B_OUTSIDE:
            return _3P_SKEW_R_B;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
            return _3P_SKEW_T_M_OUTSIDE;

        case _3P_SKEW_T_L:
            return _3P_SKEW_T_L_OUTSIDE;

        case _3P_SKEW_T_R:
            return _3P_SKEW_T_R_OUTSIDE;

        case _3P_SKEW_T_M_OUTSIDE:
            return _3P_SKEW_T_M;

        case _3P_SKEW_T_L_OUTSIDE:
            return _3P_SKEW_T_L;

        case _3P_SKEW_T_R_OUTSIDE:
            return _3P_SKEW_T_R;

        case _3P_SKEW_B_M:
            return _3P_SKEW_B_M_OUTSIDE;

        case _3P_SKEW_B_L:
            return _3P_SKEW_B_L_OUTSIDE;

        case _3P_SKEW_B_R:
            return _3P_SKEW_B_R_OUTSIDE;

        case _3P_SKEW_B_M_OUTSIDE:
            return _3P_SKEW_B_M;

        case _3P_SKEW_B_L_OUTSIDE:
            return _3P_SKEW_B_L;

        case _3P_SKEW_B_R_OUTSIDE:
            return _3P_SKEW_B_R;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
            return _4P_LT_OUTSIDE;

        case _4P_LB:
            return _4P_LB_OUTSIDE;

        case _4P_RT:
            return _4P_RT_OUTSIDE;

        case _4P_RB:
            return _4P_RB_OUTSIDE;

        case _4P_LT_OUTSIDE:
            return _4P_LT;

        case _4P_LB_OUTSIDE:
            return _4P_LB;

        case _4P_RT_OUTSIDE:
            return _4P_RT;

        case _4P_RB_OUTSIDE:
            return _4P_RB;
#endif

        case _DEMO_INSIDE:
            return _DEMO_OUTSIDE;

        case _DEMO_OUTSIDE:
            return _DEMO_INSIDE;

        default:
            return _1P_NORMAL_REGION;
    }

    return _1P_NORMAL_REGION;
}

//--------------------------------------------------
// Description  : Check HW Selec Area From SelRegion
// Input Value  : SelRegion
// Output Value : HW Sellect Area Inside/Outside/Full
//--------------------------------------------------
EnumHLWType ScalerRegionGetSelectRegionHLWArea(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
        case _FULL_REGION:
        default:
            return _HLW_FULL_WINDOW;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            return _HLW_OUTSIDE_WINDOW;

        case _2P_PIP_SUB:
            return _HLW_INSIDE_WINDOW;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            return _HLW_OUTSIDE_WINDOW;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            return _HLW_INSIDE_WINDOW;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
            return _HLW_OUTSIDE_WINDOW;

        case _2P_PBP_LR_EQUAL_R:
            return _HLW_INSIDE_WINDOW;

        case _2P_PBP_LR_L_LARGE_L:
            return _HLW_OUTSIDE_WINDOW;

        case _2P_PBP_LR_L_LARGE_R:
            return _HLW_INSIDE_WINDOW;

        case _2P_PBP_LR_R_LARGE_L:
            return _HLW_OUTSIDE_WINDOW;

        case _2P_PBP_LR_R_LARGE_R:
            return _HLW_INSIDE_WINDOW;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            return _HLW_OUTSIDE_WINDOW;

        case _2P_PBP_TB_B:
            return _HLW_INSIDE_WINDOW;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M:
        case _3P_FLAG_L:
        case _3P_FLAG_R:
            return _HLW_INSIDE_WINDOW;

        case _3P_FLAG_M_OUTSIDE:
        case _3P_FLAG_L_OUTSIDE:
        case _3P_FLAG_R_OUTSIDE:
            return _HLW_OUTSIDE_WINDOW;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
        case _3P_SKEW_L_T:
        case _3P_SKEW_L_B:
        case _3P_SKEW_R_M:
        case _3P_SKEW_R_T:
        case _3P_SKEW_R_B:
            return _HLW_INSIDE_WINDOW;

        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_L_T_OUTSIDE:
        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_M_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
            return _HLW_OUTSIDE_WINDOW;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
        case _3P_SKEW_T_R:
        case _3P_SKEW_T_L:
        case _3P_SKEW_B_M:
        case _3P_SKEW_B_R:
        case _3P_SKEW_B_L:
            return _HLW_INSIDE_WINDOW;

        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_B_M_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
            return _HLW_OUTSIDE_WINDOW;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
        case _4P_LB:
        case _4P_RT:
        case _4P_RB:
            return _HLW_INSIDE_WINDOW;

        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
            return _HLW_OUTSIDE_WINDOW;
#endif

        case _DEMO_INSIDE:
            return _HLW_INSIDE_WINDOW;

        case _DEMO_OUTSIDE:
            return _HLW_OUTSIDE_WINDOW;
    }
}

#if(_2P_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get 2P Region Equal Info
// Input Value  : EnumDisplayMode enumDisplayMode
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerRegion2PRegionEqual(EnumDisplayMode enumDisplayMode)
{
    switch(enumDisplayMode)
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            return _FALSE;
#endif
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            return _FALSE;
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            if(ScalerMDomainGetInputPathCount(ScalerRegionGetInputDataPath(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT)) !=
               ScalerMDomainGetInputPathCount(ScalerRegionGetInputDataPath(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT)))
            {
                return _FALSE;
            }
            return _TRUE;
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            if(ScalerMDomainGetInputPathCount(ScalerRegionGetInputDataPath(_DISPLAY_RGN_TOP)) !=
               ScalerMDomainGetInputPathCount(ScalerRegionGetInputDataPath(_DISPLAY_RGN_BOTTOM)))
            {
                return _FALSE;
            }
            return _TRUE;
#endif
        default:
            return _FALSE;
    }
}
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Transfer Eagle Sight Display Mode
// Input Value  : enumEagleSightSupport, enumDisplayMode
// Output Value : enumDisplayMode
//--------------------------------------------------
EnumDisplayMode ScalerRegionEagleSightTransDisplayMode(EnumDisplayMode enumDisplayMode)
{
    if(enumDisplayMode == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        return _DISPLAY_MODE_1P;
    }

    return enumDisplayMode;
}
#endif

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get 2P Display Mode Main Path Region
// Input Value  : None
// Output Value : _REGION_INDEX_0/ _REGION_INDEX_1
//--------------------------------------------------
EnumRegionIndex ScalerRegionGet2PMainPathRegion(void)
{
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_R_LARGE)
    {
        if(ScalerDDomainPbpLRLargeFrameMappingRegion() == _PBP_LR_LARGE_FRAME_R1A1)
        {
            return _REGION_INDEX_1;
        }
        else
        {
            return _REGION_INDEX_0;
        }
    }
#endif

    return _REGION_INDEX_0;
}
#endif


