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
// ID Code      : RTD2020UserInterfaceSource.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_SOURCE__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceSource.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

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
// Description  : Get user defined auto-search target region
// Input Value  : None
// Output Value : select region
//--------------------------------------------------
EnumDisplayRegion UserInterfaceSourceGetAutoSearchTarget(void)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
        case _OSD_DM_1P:
            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                if(UserAdjustGetMultiDisplayMode() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
                {
                    return _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
                }
                else
#endif
                {
                    return _DISPLAY_RGN_1P;
                }
            }
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_PIP_MAIN;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_PIP_SUB;
            }

            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:
            if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
            {
                if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    return _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT;
                }
                else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    return _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT;
                }
            }
            else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
            {
                if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    return _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT;
                }
                else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    return _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT;
                }
            }
            else
            {
                if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    return _DISPLAY_RGN_PBP_LR_EQUAL_LEFT;
                }
                else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
                {
                    return _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT;
                }
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_TOP;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_BOTTOM;
            }

            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_FLAG:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_FLAG_MAIN;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_FLAG_LEFT;
            }
            else if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_FLAG_RIGHT;
            }

            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_L:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_L_MAIN;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_L_TOP;
            }
            else if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_L_BOTTOM;
            }

            break;

        case _OSD_DM_3P_SKEW_R:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_R_MAIN;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_R_TOP;
            }
            else if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_R_BOTTOM;
            }

            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_SKEW_T:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_T_MAIN;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_T_LEFT;
            }
            else if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_T_RIGHT;
            }

            break;

        case _OSD_DM_3P_SKEW_B:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_B_MAIN;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_B_LEFT;
            }
            else if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SKEW_B_RIGHT;
            }

            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_LT;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_LB;
            }
            else if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_RT;
            }
            else if(GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_RB;
            }

            break;
#endif
    }

    return _DISPLAY_RGN_NONE;
}

//--------------------------------------------------
// Description  : Get input port 0
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserInterfaceSourceGetInputPort0(void)
{
    if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
    {
        switch(GET_OSD_DISPLAY_MODE())
        {
            default:
            case _OSD_DM_1P:
                return _INPUT_PORT_SEARCH_PRI_0;

#if(_MULTI_DISPLAY_MAX >= 0x02)
            case _OSD_DM_2P_PIP:
            case _OSD_DM_2P_LR:
            case _OSD_DM_2P_TB:
                if(GET_OSD_2P_INPUT_SOURCE() == _INPUT_PORT_SEARCH_PRI_0)
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
            case _OSD_DM_3P_FLAG:
            case _OSD_DM_3P_SKEW_L:
            case _OSD_DM_3P_SKEW_R:
            case _OSD_DM_3P_SKEW_T:
            case _OSD_DM_3P_SKEW_B:
                if((GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
                else if((GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_2;
                }
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
            case _OSD_DM_4P:
                if((GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
                else if((GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else if((GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2))
                {
                    return _INPUT_PORT_SEARCH_PRI_2;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_3;
                }
#endif
        }
    }
    else
    {
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        if(GET_OSD_PXP_MST() == _ON_SELECT_MODE)
        {
            if((GET_OSD_1P_INPUT_SOURCE() >= _OSD_INPUT_D9_D0) && (GET_OSD_1P_INPUT_SOURCE() <= _OSD_INPUT_D9_D2))
            {
                return _D9_INPUT_PORT;
            }
        }
#endif
        return GET_OSD_1P_INPUT_SOURCE();
    }
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : Get input port 1
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserInterfaceSourceGetInputPort1(void)
{
    if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
    {
        switch(GET_OSD_DISPLAY_MODE())
        {
            default:
            case _OSD_DM_2P_PIP:
            case _OSD_DM_2P_LR:
            case _OSD_DM_2P_TB:
                if(GET_OSD_1P_INPUT_SOURCE() == _INPUT_PORT_SEARCH_PRI_0)
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }

#if(_MULTI_DISPLAY_MAX >= 0x03)
            case _OSD_DM_3P_FLAG:
            case _OSD_DM_3P_SKEW_L:
            case _OSD_DM_3P_SKEW_R:
            case _OSD_DM_3P_SKEW_T:
            case _OSD_DM_3P_SKEW_B:
                if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
                else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_2;
                }
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
            case _OSD_DM_4P:
                if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
                else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2))
                {
                    return _INPUT_PORT_SEARCH_PRI_2;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_3;
                }
#endif
        }
    }
    else
    {
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        if(GET_OSD_PXP_MST() == _ON_SELECT_MODE)
        {
            if((GET_OSD_2P_INPUT_SOURCE() >= _OSD_INPUT_D9_D0) && (GET_OSD_2P_INPUT_SOURCE() <= _OSD_INPUT_D9_D2))
            {
                return _D9_INPUT_PORT;
            }
        }
#endif
        return GET_OSD_2P_INPUT_SOURCE();
    }
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
//--------------------------------------------------
// Description  : Get input port 2
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserInterfaceSourceGetInputPort2(void)
{
    if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
    {
        switch(GET_OSD_DISPLAY_MODE())
        {
            default:
            case _OSD_DM_3P_FLAG:
            case _OSD_DM_3P_SKEW_L:
            case _OSD_DM_3P_SKEW_R:
            case _OSD_DM_3P_SKEW_T:
            case _OSD_DM_3P_SKEW_B:
                if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
                else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_2;
                }

#if(_MULTI_DISPLAY_MAX >= 0x04)
            case _OSD_DM_4P:
                if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
                else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2))
                {
                    return _INPUT_PORT_SEARCH_PRI_2;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_3;
                }
#endif
        }
    }
    else
    {
        return GET_OSD_3P_INPUT_SOURCE();
    }
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Description  : Get input port 3
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserInterfaceSourceGetInputPort3(void)
{
    if(GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
    {
        if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
           (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
           (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
        {
            return _INPUT_PORT_SEARCH_PRI_0;
        }
        else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
        {
            return _INPUT_PORT_SEARCH_PRI_1;
        }
        else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2))
        {
            return _INPUT_PORT_SEARCH_PRI_2;
        }
        else
        {
            return _INPUT_PORT_SEARCH_PRI_3;
        }
    }
    else
    {
        return GET_OSD_4P_INPUT_SOURCE();
    }
}
#endif

//--------------------------------------------------
// Description  : User Define Whether Cable Status Should Reset
// Input Value  : None
// Output Value : _CABLE_RESET_TRUE => Reset
//--------------------------------------------------
EnumCableResetStatus UserInterfaceSourceGetCableResetStatus(EnumDisplayRegion enumDisplayRegion)
{
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_1P:
            if((SysSourceGetCableStatusChange(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)) == _TRUE) &&
               ((!((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_NONE))) ||
                (SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)) == _TRUE)))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);

                if(SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT)
                {
                    SysSourceSwitchInputPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
                }

                return _CABLE_RESET_TRUE;
            }
            break;

        default:
            if(SysSourceGetCableStatusChange(SysRegionGetInputPort(enumDisplayRegion)) == _TRUE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                // If InputPort is D4, need to check it is D4, D14 or D15?
                if((SysRegionGetInputPort(enumDisplayRegion) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)) // ACTIVE PORT = D14
                {
                    // Switch to D14
                    SysSourceSwitchInputPort(_D14_INPUT_PORT);
                }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if((SysRegionGetInputPort(enumDisplayRegion) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)) // ACTIVE PORT = D15
                {
                    // Switch to D15
                    SysSourceSwitchInputPort(_D15_INPUT_PORT);
                }
#endif

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

                // If InputPort is D3, need to check it is D3, D12 or D13?
                if((SysRegionGetInputPort(enumDisplayRegion) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)) // ACTIVE PORT = D12
                {
                    // Switch to D12
                    SysSourceSwitchInputPort(_D12_INPUT_PORT);
                }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if((SysRegionGetInputPort(enumDisplayRegion) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)) // ACTIVE PORT = D13
                {
                    // Switch to D13
                    SysSourceSwitchInputPort(_D13_INPUT_PORT);
                }
#endif
#endif
                else
#endif
                {
                    // Switch to auto target region
                    SysSourceSwitchInputPort(SysRegionGetInputPort(enumDisplayRegion));
                }
                return _CABLE_RESET_TRUE;
            }
            break;
    }

    return _CABLE_RESET_FALSE;
}

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Check whether a specific port can be auto-searched or not
// Input Value  : enumSelRegion --> select region
//                enumInputPort  --> search port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumAutoSearchStatus UserInterfaceSourceGetRegionAutoSearchStatus(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:

            switch(UserCommonRegionGetIndex(enumDisplayRegion))
            {
                case _REGION_INDEX_0:
                    if((GET_OSD_2P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_3P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_4P_INPUT_SOURCE() != enumInputPort))
                    {
                        return _AUTO_SEARCH_TRUE;
                    }
                    break;

                case _REGION_INDEX_1:
                    if((GET_OSD_1P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_3P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_4P_INPUT_SOURCE() != enumInputPort))
                    {
                        return _AUTO_SEARCH_TRUE;
                    }
                    break;

                case _REGION_INDEX_2:
                    if((GET_OSD_1P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_2P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_4P_INPUT_SOURCE() != enumInputPort))
                    {
                        return _AUTO_SEARCH_TRUE;
                    }
                    break;

                case _REGION_INDEX_3:
                    if((GET_OSD_1P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_2P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_3P_INPUT_SOURCE() != enumInputPort))
                    {
                        return _AUTO_SEARCH_TRUE;
                    }
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_3P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_3P_FLAG:
        case _OSD_DM_3P_SKEW_L:
        case _OSD_DM_3P_SKEW_R:
        case _OSD_DM_3P_SKEW_T:
        case _OSD_DM_3P_SKEW_B:

            switch(UserCommonRegionGetIndex(enumDisplayRegion))
            {
                case _REGION_INDEX_0:
                    if((GET_OSD_2P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_3P_INPUT_SOURCE() != enumInputPort))
                    {
                        return _AUTO_SEARCH_TRUE;
                    }
                    break;

                case _REGION_INDEX_1:
                    if((GET_OSD_1P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_3P_INPUT_SOURCE() != enumInputPort))
                    {
                        return _AUTO_SEARCH_TRUE;
                    }
                    break;

                case _REGION_INDEX_2:
                    if((GET_OSD_1P_INPUT_SOURCE() != enumInputPort) &&
                       (GET_OSD_2P_INPUT_SOURCE() != enumInputPort))
                    {
                        return _AUTO_SEARCH_TRUE;
                    }
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:
        case _OSD_DM_2P_TB:
        case _OSD_DM_2P_PIP:

            switch(UserCommonRegionGetIndex(enumDisplayRegion))
            {
                case _REGION_INDEX_0:
                    if(GET_OSD_2P_INPUT_SOURCE() != enumInputPort)
                    {
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
                        if((GET_OSD_2P_INPUT_SOURCE() >= _OSD_INPUT_D9_D0) && (GET_OSD_2P_INPUT_SOURCE() <= _OSD_INPUT_D9_D2))
                        {
                            if(enumInputPort != _D9_INPUT_PORT)
                            {
                                return _AUTO_SEARCH_TRUE;
                            }
                        }
                        else
#endif
                        {
                            return _AUTO_SEARCH_TRUE;
                        }
                    }
                    break;

                default:
                    if(GET_OSD_1P_INPUT_SOURCE() != enumInputPort)
                    {
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
                        if((GET_OSD_1P_INPUT_SOURCE() >= _OSD_INPUT_D9_D0) && (GET_OSD_1P_INPUT_SOURCE() <= _OSD_INPUT_D9_D2))
                        {
                            if(enumInputPort != _D9_INPUT_PORT)
                            {
                                return _AUTO_SEARCH_TRUE;
                            }
                        }
                        else
#endif
                        {
                            return _AUTO_SEARCH_TRUE;
                        }
                    }
                    break;
            }
            break;
#endif

        default:
        case _OSD_DM_1P:
            break;
    }

    return _AUTO_SEARCH_FALSE;
}
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
//--------------------------------------------------
// Description  : User check search is finish or not
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumAutoSearchStatus UserInterfaceSourceAdjustOsdCheckTotalSearchFinish(void)
{
    return _AUTO_SEARCH_TRUE;
}

//--------------------------------------------------
// Description  : Determine the search time of each source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceSourceAdjustSourceSearchTime(void)
{
}

//--------------------------------------------------
// Description  : User Report Eizo Search Finish Time
// Input Value  : None
// Output Value : Search Finish Time
//--------------------------------------------------
WORD UserInterfaceSourceGetEizoSearchFinishTime(void)
{
    return 0;
}
#endif

//--------------------------------------------------
// Description  : User decide bypass Source Handler
// Input Value  : None
// Output Value : _SOURCE_DETECTION_NORMAL/_SOURCE_DETECTION_BYPASS
//--------------------------------------------------
EnumSourceDetectionInfo UserInterfaceSourceBypassDetection(void)
{
    return _SOURCE_DETECTION_NORMAL;
}

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Select Default Externel HDMI Switch Port
// Input Value  : None
// Output Value : Only Return _D3_INPUT_PORT or _D12_INPUT_PORT or _D13_INPUT_PORT
//--------------------------------------------------
EnumInputPort UserInterfaceSourceHdmiExternalSwitchDefaultPort(void)
{
    if(UserAdjustGetMultiDisplayMode() == _DISPLAY_MODE_1P)
    {
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
        return _D4_INPUT_PORT;
#else
        return _D3_INPUT_PORT;
#endif
    }
#if(_MULTI_DISPLAY_MAX != 0x01)
    else
    {
        return _NO_INPUT_PORT;
    }
#endif

    return _NO_INPUT_PORT;
}
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HP Source Switch Event Time
// Input Value  : Source Scan Type
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceSourceGetHpSwitchOsdEventTime(BYTE ucSourceScanType)
{
    ucSourceScanType = ucSourceScanType;
    return 0;
}

//--------------------------------------------------
// Description  : Get HP PXP Sub auto scan flag
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumSourceHpPxpSubScanType UserInterfaceSourceGetHpPxpSubAutoScan(void)
{
    return _HP_PXP_SUB_FIX_PORT;
}

#endif
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

