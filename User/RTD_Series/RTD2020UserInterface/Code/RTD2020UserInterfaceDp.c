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
// ID Code      : RTD2020UserInterfaceDp.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_DP__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceDp.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Version
// Input Value  : RCP Key Code
// Output Value : DP_VERSION_1_1 or DP_VERSION_1_2
//--------------------------------------------------
EnumDpVersionType UserInterfaceDpGetVersion(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D0)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_4)
            {
                return _DP_VERSION_1_4;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_2_DOT_0)
            {
                return _DP_VERSION_2_0;
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D1)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_4)
            {
                return _DP_VERSION_1_4;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_2_DOT_0)
            {
                return _DP_VERSION_2_0;
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D2)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_4)
            {
                return _DP_VERSION_1_4;
            }
            else if(GET_OSD_DP_D2_VERSION() == _DP_VER_2_DOT_0)
            {
                return _DP_VERSION_2_0;
            }

            break;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D6)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_4)
            {
                return _DP_VERSION_1_4;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_2_DOT_0)
            {
                return _DP_VERSION_2_0;
            }

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

#if((_D7_INPUT_PORT_TYPE == _D7_DP_PORT) && (_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            return _DP_VERSION_2_0;
#elif((_D8_INPUT_PORT_TYPE == _D8_DP_PORT) && (_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON))
            return _DP_VERSION_2_0;
#elif((_DP_AUXLESS_ALPM_SUPPORT == _ON) || (_DP_ADAPTIVESYNC_SUPPORT == _ON) || (_DP_PR_MODE_SUPPORT == _ON))
            return _DP_VERSION_2_0;
#else
            return _DP_VERSION_1_4;
#endif
#endif

        default:

            break;
    }

    return _DP_VERSION_1_1;
}

//--------------------------------------------------
// Description  : Get DP Link Rate For User Setting
// Input Value  : Input Port
// Output Value : EnumDpLinkRate
//--------------------------------------------------
EnumDpLinkRate UserInterfaceDpGetMaxLinkRate(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return _D0_DP_LINK_CLK_RATE;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return _D1_DP_LINK_CLK_RATE;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return _D2_DP_LINK_CLK_RATE;
#endif
        default:
            return _DP_LINK_SPEED_NONE;
    }
}

//--------------------------------------------------
// Description  : Get DP Lane Count
// Input Value  : InputPort
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount UserInterfaceDpGetLaneCount(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            return UserCommonNVRamGetSystemData(_DP_D0_LANES);

#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return UserCommonNVRamGetSystemData(_DP_D1_LANES);

#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            return UserCommonNVRamGetSystemData(_DP_D2_LANES);

#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            return UserCommonNVRamGetSystemData(_DP_D6_LANES);

#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            return _DP_LINK_4_LANE;

#endif

        default:

            break;
    }

    return _DP_LINK_4_LANE;
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Dp MST Capable Port
// Input Value  : None
// Output Value : _DP_MST_RX0 or _DP_MST_RX1
//--------------------------------------------------
EnumDPMSTPort UserInterfaceDpGetMSTCapablePort(void)
{
#if(_DUAL_DP_SUPPORT == _ON)
    if(SysSourceGetInputPort() == _DUAL_DP_INPUT_PORT)
    {
        return _DP_MST_NO_PORT;
    }
#endif

    switch(GET_OSD_DP_MST())
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        case _MST_D0:

            if(GET_OSD_DP_D0_VERSION() > _DP_VER_1_DOT_1)
            {
                return _DP_MST_RX0_PORT;
            }

            break;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        case _MST_D1:

            if(GET_OSD_DP_D1_VERSION() > _DP_VER_1_DOT_1)
            {
                return _DP_MST_RX1_PORT;
            }

            break;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_MST_PORT_SUPPORT == _ON))
        case _MST_D2:

            if(GET_OSD_DP_D2_VERSION() > _DP_VER_1_DOT_1)
            {
                return _DP_MST_RX2_PORT;
            }

            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
        case _MST_D6:

            if(GET_OSD_DP_D6_VERSION() > _DP_VER_1_DOT_1)
            {
                return _DP_MST_RX6_PORT;
            }

            break;
#endif

        case _MST_AUTO:

            return _DP_MST_AUTO_PORT;

        default:

            break;
    }

    return _DP_MST_NO_PORT;
}

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Dp MST Pxp Mode
// Input Value  : None
// Output Value : EnumDpMstPxpMode
//--------------------------------------------------
EnumDpMstPxpMode UserInterfaceDpGetPxpMode(void)
{
    return GET_OSD_PXP_MST();
}

//--------------------------------------------------
// Description  : Get Dp MST Pxp Input Target
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort UserInterfaceDpGetPxpInputTarget(void)
{
    EnumOSDInputPort enumOsdInputPort = _OSD_INPUT_A0;
    EnumInputPort enumInputTargetPort = _NO_INPUT_PORT;
    enumOsdInputPort = enumOsdInputPort;

    if(GET_OSD_PXP_MST() == _DP_MST_PXP_OFF)
    {
        enumInputTargetPort = _NO_INPUT_PORT;
    }
    else
    {
#if(_DP_MST_PXP_FIXED_MODE_SUPPORT == _ON)
        if(GET_OSD_PXP_MST() == _DP_MST_PXP_ON_FIXED_MODE)
        {
            if(GET_OSD_1P_INPUT_SOURCE() != _OSD_INPUT_AUTO)
            {
                enumInputTargetPort = GET_OSD_1P_INPUT_SOURCE();
            }
        }
#endif

#if(_DP_MST_PXP_SELECT_MODE_SUPPORT == _ON)
        if(GET_OSD_PXP_MST() == _DP_MST_PXP_ON_SELECT_MODE)
        {
            if((GET_OSD_1P_INPUT_SOURCE() >= _OSD_INPUT_D9_D0) && (GET_OSD_1P_INPUT_SOURCE() <= _OSD_INPUT_D9_D2))
            {
                enumOsdInputPort = GET_OSD_1P_INPUT_SOURCE();
            }
            else if((GET_OSD_2P_INPUT_SOURCE() >= _OSD_INPUT_D9_D0) && (GET_OSD_2P_INPUT_SOURCE() <= _OSD_INPUT_D9_D2))
            {
                enumOsdInputPort = GET_OSD_2P_INPUT_SOURCE();
            }

            switch(enumOsdInputPort)
            {
                case _OSD_INPUT_D9_D0:
                    enumInputTargetPort = _D0_INPUT_PORT;
                    break;

                case _OSD_INPUT_D9_D1:
                    enumInputTargetPort = _D1_INPUT_PORT;
                    break;

                case _OSD_INPUT_D9_D2:
                    enumInputTargetPort = _D2_INPUT_PORT;
                    break;

                default:
                    break;
            }
        }
#endif
    }

    return enumInputTargetPort;
}

//--------------------------------------------------
// Description  : Get Dp MST Pxp Port Num Swap Status
// Input Value  : None
// Output Value : EnumDpPxpPortNumSwapStatus
//--------------------------------------------------
EnumDpPxpPortNumSwapStatus UserInterfaceDpGetPxpPortNumSwapStatus(void)
{
    return _DP_PXP_PORT_NUM_SWAP_FALSE;
}
#endif
#endif // #if(_DP_MST_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Dp Clone Setting by User
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
EnumInputPort UserInterfaceDpGetCloneOutputUserInputPort(void)
{
    EnumOSDCloneModeFixDef enumCloneModeFixPort = _OSD_CLONE_FIX_OFF;

    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        enumCloneModeFixPort = GET_OSD_CLONE_MODE_1P();
    }
    else
    {
        enumCloneModeFixPort = GET_OSD_CLONE_MODE_MTP();
    }

    switch(enumCloneModeFixPort)
    {
        case _OSD_CLONE_FIX_A0:

            return _A0_INPUT_PORT;

        case _OSD_CLONE_FIX_D0:

            return _D0_INPUT_PORT;

        case _OSD_CLONE_FIX_D1:

            return _D1_INPUT_PORT;

        case _OSD_CLONE_FIX_D2:

            return _D2_INPUT_PORT;

        case _OSD_CLONE_FIX_D3:

            return _D3_INPUT_PORT;

        case _OSD_CLONE_FIX_D4:

            return _D4_INPUT_PORT;

        case _OSD_CLONE_FIX_D5:

            return _D5_INPUT_PORT;

        case _OSD_CLONE_FIX_D6:

            return _D6_INPUT_PORT;

        case _OSD_CLONE_FIX_OFF:
        default:

            return _NO_INPUT_PORT;
    }
}

//--------------------------------------------------
// Description  : Decide whether to Clone output to DP Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumDPCloneOutputStatus UserInterfaceDpGetCloneOutputStatus(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        if(GET_OSD_CLONE_MODE_1P() == _OSD_CLONE_FIX_OFF)
        {
            return _DP_CLONE_OUTPUT_FALSE;
        }
    }
    else
    {
        if(GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_FIX_OFF)
        {
            return _DP_CLONE_OUTPUT_FALSE;
        }
    }

    return _DP_CLONE_OUTPUT_TRUE;
}
#endif // #if(_DP_TX_SUPPORT == _ON)

#if(_DUAL_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Using D7 Dp Dual Port as Default Port
// Input Value  : None
// Output Value : _TRUE -> Default D7 DP Port ; _FALSE -> D0/D1 DP Port
//--------------------------------------------------
EnumDPDualPortDefaultStatus UserInterfaceDpGetDualDefaultPort(void)
{
    return _DP_DUAL_PORT_USE_SINGLE_PORT;
}
#endif

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DC On DP HPD Toggle Mode Control By User
// Input Value  : None
// Output Value : EnumDpHpdToggleMode
//--------------------------------------------------
EnumDpHpdToggleMode UserInterfaceDpGetDcOnHpdMode(void)
{
    return _DP_HPD_TOGGLE_NORMAL;
}
#endif

#if(_DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP User Intel OUI Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDpSourceWriteOuiHandler_EXINT0(EnumInputPort enumInputPort)
{
    // WARNING: Please Make Sure The Process Time < 1ms

    enumInputPort = enumInputPort;
}
#endif
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : User Report HDMI +5V Status
// Input Value  : D0/D1/D2 Port
// Output Value : _TURE --> +5V exist
//--------------------------------------------------
EnumGetHdmi5VStatus UserInterfaceDpGetHdmi5VStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D1_INPUT_PORT:
            return _HDMI_5V_STATUS_ON;
        case _D2_INPUT_PORT:
            return _HDMI_5V_STATUS_ON;
        case _D3_INPUT_PORT:
            return _HDMI_5V_STATUS_ON;
        case _D4_INPUT_PORT:
            return _HDMI_5V_STATUS_ON;
        case _D5_INPUT_PORT:
            return _HDMI_5V_STATUS_ON;
        default:
            return _HDMI_5V_STATUS_ON;
    }
}
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide whether to Enable ADAPTIVESYNC Function
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumDpAdaptiveSyncSupport UserInterfaceDpAdaptiveSyncGetEnable(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    if(UserCommonDisplayGetFrameSyncSupport() == _FRAME_SYNC_SUPPORT_ON)
    {
        return GET_OSD_DP_ADAPTIVE_SYNC();
    }

    return _DP_ADAPTIVESYNC_SUPPORT_OFF;
}
#endif // #if(_DP_ADAPTIVESYNC_SUPPORT == _ON)

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide whether to Enable DP PR Mode Function
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumDpPRModeSupport UserInterfaceDpPRModeGetEnable(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    if(UserAdjustGetMultiDisplayMode() == _DISPLAY_MODE_1P)
    {
        return GET_OSD_PANEL_REPLAY();
    }

    return _DP_PR_MODE_SUPPORT_OFF;
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide whether to Enable DP AUXLESS ALPM Function
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumDpAuxlessAlpmSupport UserInterfaceDpAuxlessAlpmGetEnable(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    return GET_OSD_DP_AUXLESS_ALPM();
}
#endif
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
