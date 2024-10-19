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
// ID Code      : RL6952_Series_DpRx_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpRx/ScalerDpRx.h"

#if(_DP_SUPPORT == _ON)
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
// Description  : Dp Mac Dphy Rxx Mapping to InputPort
// Input Value  : EnumDpMacDphySel
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDpRxMacDphyGetInputPortSwitch_WDINT(EnumDpMacDphySel enumDpMacDphySel)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumDpMacDphySel)
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

#if(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumInputPort = _D0_INPUT_PORT;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumInputPort = _D1_INPUT_PORT;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumInputPort = _D2_INPUT_PORT;
#endif

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

#if(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumInputPort = _D0_INPUT_PORT;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumInputPort = _D1_INPUT_PORT;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumInputPort = _D2_INPUT_PORT;
#endif

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

#if(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumInputPort = _D0_INPUT_PORT;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumInputPort = _D1_INPUT_PORT;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumInputPort = _D2_INPUT_PORT;
#endif

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_RX0RX1)
            enumInputPort = _D7_INPUT_PORT;
#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_RX1RX2)
            enumInputPort = _D8_INPUT_PORT;
#endif

            break;
#endif

        default:
            break;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : Get Mac Dphy Switch According to enumInputPort
// Input Value  : EnumInputPort
// Output Value : EnumDpMacDphySel
//--------------------------------------------------
EnumDpMacDphySel ScalerDpRxGetMacDphySwitch_WDINT(EnumInputPort enumInputPort)
{
    EnumDpMacDphySel enumDpMacDphySel = _DP_MAC_DPHY_NONE;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumDpMacDphySel = _DP_MAC_DPHY_RX0;
#elif(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumDpMacDphySel = _DP_MAC_DPHY_RX1;
#elif(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumDpMacDphySel = _DP_MAC_DPHY_RX2;
#endif

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumDpMacDphySel = _DP_MAC_DPHY_RX0;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumDpMacDphySel = _DP_MAC_DPHY_RX1;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumDpMacDphySel = _DP_MAC_DPHY_RX2;
#endif

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumDpMacDphySel = _DP_MAC_DPHY_RX0;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumDpMacDphySel = _DP_MAC_DPHY_RX1;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumDpMacDphySel = _DP_MAC_DPHY_RX2;
#endif

            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:

            enumDpMacDphySel = _DP_MAC_DPHY_DUAL;

            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:

            enumDpMacDphySel = _DP_MAC_DPHY_DUAL;

            break;
#endif

        default:
            break;
    }

    return enumDpMacDphySel;
}
#endif // #if(_DP_SUPPORT == _ON)

