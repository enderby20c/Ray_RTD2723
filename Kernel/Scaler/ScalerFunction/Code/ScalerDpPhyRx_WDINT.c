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
// ID Code      : ScalerDpPhyRx_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPPHY_WDINT__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx/ScalerDpPhyRx.h"



//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx1 or Rx2 or Rx3
//--------------------------------------------------
EnumRx ScalerDpPhyRxDxRxMapping_WDINT(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumRx = _HW_D0_DP_PHY_RX_MAPPING;
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumRx = _HW_D1_DP_PHY_RX_MAPPING;
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumRx = _HW_D2_DP_PHY_RX_MAPPING;
            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:
            enumRx = _HW_D7_DP_PHY_RX_MAPPING;
            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:
            enumRx = _HW_D8_DP_PHY_RX_MAPPING;
            break;
#endif

        default:

            break;
    }

    return enumRx;
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxRebuildPhy_WDINT(EnumInputPort enumInputPort, EnumDpLinkRate enumDpLinkRate)
{
    switch(ScalerDpPhyRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0RebuildPhy_WDINT(enumDpLinkRate);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1RebuildPhy_WDINT(enumDpLinkRate);

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2RebuildPhy_WDINT(enumDpLinkRate);

            break;
#endif

        default:

            break;
    }
}
#endif
