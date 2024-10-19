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
// ID Code      : RL6952_Series_Region.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_REGION__

#include "ScalerFunctionInclude.h"
#include "Region/ScalerRegion.h"


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
// Description  : Get input data path for select region
// Input Value  : enumSelRegion --> select region
// Output Value : Scaler Data Path
//--------------------------------------------------
EnumInputDataPath ScalerRegionGetInputDataPath(EnumDisplayRegion enumDisplayRegion)
{
    WORD usDispRegionInfo = DISPLAY_REGION_INFO(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH), enumDisplayRegion);

    switch(usDispRegionInfo)
    {
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_1P):
        default:
            return _INPUT_PATH_M1_M2;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_PIP_MAIN):
            return _INPUT_PATH_M1_M2;
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_PIP_SUB):
            return _INPUT_PATH_S1;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_EAGLE_SIGHT_MAIN):
            return _INPUT_PATH_M1_M2;
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_EAGLE_SIGHT_SUB):
            return _INPUT_PATH_S1;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_PBP_LR_EQUAL_LEFT):
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT):
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT):
            return _INPUT_PATH_M1_M2;
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT):
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT):
        case DISPLAY_REGION_INFO(_OFF, _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT):
            return _INPUT_PATH_S1;
#endif
    }
    return _INPUT_PATH_NONE;
}

//--------------------------------------------------
// Description  : Get input data path for select region
// Input Value  : enumInputDataPath --> input path
// Output Value : region index
//--------------------------------------------------
EnumRegionIndex ScalerRegionGetIndexFromInputDataPath(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            return _REGION_INDEX_0;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            switch(enumInputDataPath)
            {
                case _INPUT_PATH_M1_M2:
                    return _REGION_INDEX_0;
                case _INPUT_PATH_S1:
                    return _REGION_INDEX_1;
                default:
                    break;
            }
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            switch(enumInputDataPath)
            {
                case _INPUT_PATH_M1_M2:
                    return _REGION_INDEX_0;
                case _INPUT_PATH_S1:
                    return _REGION_INDEX_1;
                default:
                    break;
            }
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            return (enumInputDataPath == _INPUT_PATH_M1_M2) ? _REGION_INDEX_0 : _REGION_INDEX_1;

        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            return (enumInputDataPath == _INPUT_PATH_M1_M2) ? _REGION_INDEX_1 : _REGION_INDEX_0;
#endif
        default:
            break;
    }

    return _REGION_INDEX_0;
}


//--------------------------------------------------
// Description  : Get D Domain Region from select region
// Input Value  : enumDisplayRegion --> Display region
// Output Value : D Domain Region
//--------------------------------------------------
EnumDDomainRegion ScalerRegionGetDDomainRegion(EnumDisplayRegion enumDisplayRegion)
{
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_1P:
            return _DDOMAIN_RGN_R1_A1;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PIP_MAIN:
            return _DDOMAIN_RGN_R1_A1;

        case _DISPLAY_RGN_PIP_SUB:
            return _DDOMAIN_RGN_R2_A1;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
            return _DDOMAIN_RGN_R1_A1;

        case _DISPLAY_RGN_EAGLE_SIGHT_SUB:
            return _DDOMAIN_RGN_R2_A1;
#endif


#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PBP_LR_EQUAL_LEFT:
        case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
        case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
            return _DDOMAIN_RGN_R1_A1;

        case _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT:
        case _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT:
        case _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT:
            return _DDOMAIN_RGN_R2_A1;
#endif

        default:
            return _DDOMAIN_RGN_NONE;
    }

    return _DDOMAIN_RGN_NONE;
}

#if(_HW_I_DOMAIN_PATH_COUNT > 1)
//--------------------------------------------------
// Description  : Get IDomain Page Register From enumSelRegion
// Input Value  : EnumSelRegion
// Output Value : Page Register
//--------------------------------------------------
WORD ScalerRegionGetIDomainRegisterPage(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_SUB:
            return _REG_SUB1_PAGE;

        case _2P_PIP_MAIN:
            return _REG_MAIN1_PAGE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_SUB:
            return _REG_SUB1_PAGE;


        case _2P_PIP_EAGLE_SIGHT_MAIN:
            return _REG_MAIN1_PAGE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
            return _REG_MAIN1_PAGE;

        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_L:
            return _REG_SUB1_PAGE;
#endif

        case _1P_NORMAL_REGION:
        case _FULL_REGION:
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
        default:

            return _REG_MAIN1_PAGE;
    }
}
#endif

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
//--------------------------------------------------
// Description  : Get DDomain Before Blending Page Register From enumSelRegion
// Input Value  : EnumSelRegion
// Output Value : Page Register
//--------------------------------------------------
WORD ScalerRegionGetDDomainBeforeBlendingRegisterPage(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            return _REG_MAIN1_PAGE;
        case _2P_PIP_SUB:
            return _REG_SUB1_PAGE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            return _REG_MAIN1_PAGE;
        case _2P_PIP_EAGLE_SIGHT_SUB:
            return _REG_SUB1_PAGE;
#endif


#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
            return _REG_MAIN1_PAGE;

        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_L:
            return _REG_SUB1_PAGE;
#endif
        case _1P_NORMAL_REGION:
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
        case _FULL_REGION:
        default:

            return _REG_MAIN1_PAGE;
    }
}
//--------------------------------------------------
// Description  : Get DDomain After Blending Page Register From enumSelRegion
// Input Value  : EnumSelRegion
// Output Value : Page Register
//--------------------------------------------------
WORD ScalerRegionGetDDomainAfterBlendingRegisterPage(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
        case _FULL_REGION:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_R_LARGE_L:
#endif
        case _DEMO_OUTSIDE:

            return _REG_MAIN1_PAGE;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_R:
#endif

        case _DEMO_INSIDE:
        default:

            return _REG_MAIN2_PAGE;
    }
}
#endif

//--------------------------------------------------
// Description  : Get input data path for select region
// Input Value  : enumSelRegion --> select region
// Output Value : Scaler Data Path
//--------------------------------------------------
EnumInputDataPath ScalerRegionGetInputDataPathFromSelRegion(EnumSelRegion enumSelRegion)
{
    EnumInputDataPath enumInputDataPath = _INPUT_PATH_NONE;

    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _2P_PIP_SUB:
            enumInputDataPath = _INPUT_PATH_S1;
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            enumInputDataPath = _INPUT_PATH_S1;
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_L:
            enumInputDataPath = _INPUT_PATH_S1;
            break;
#endif

        case _FULL_REGION:
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    enumInputDataPath = _INPUT_PATH_M1_M2;
                    break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1);
                    break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1);
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1);
                    break;
#endif
                default:
                    break;
            }
            break;

        default:
            break;
    }
    return enumInputDataPath;
}