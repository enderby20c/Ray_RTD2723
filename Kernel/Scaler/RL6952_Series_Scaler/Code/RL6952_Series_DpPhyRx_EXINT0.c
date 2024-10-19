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
// ID Code      : RL6952_Series_DpPhyRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPPHYRX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx/ScalerDpPhyRx.h"

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
// Description  : DP Port Dx mapping to Rx
// Input Value  : Rx Port
// Output Value : Dx port
//--------------------------------------------------
EnumInputPort ScalerDpPhyRxRxDxMapping_EXINT0(EnumRx enumRx)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumRx)
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            if(_HW_D0_DP_PHY_RX_MAPPING == _RX0)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_PHY_RX_MAPPING == _RX0)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_PHY_RX_MAPPING == _RX0)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            if(_HW_D0_DP_PHY_RX_MAPPING == _RX1)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_PHY_RX_MAPPING == _RX1)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_PHY_RX_MAPPING == _RX1)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            if(_HW_D0_DP_PHY_RX_MAPPING == _RX2)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_PHY_RX_MAPPING == _RX2)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_PHY_RX_MAPPING == _RX2)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if((_DP_PHY_RX0_SUPPORT == _ON) && (_DP_PHY_RX1_SUPPORT == _ON))
        case _RX7:

            enumInputPort = _D7_INPUT_PORT;

            break;
#endif

#if((_DP_PHY_RX1_SUPPORT == _ON) && (_DP_PHY_RX2_SUPPORT == _ON))
        case _RX8:

            enumInputPort = _D8_INPUT_PORT;

            break;
#endif

        default:

            break;
    }

    return enumInputPort;
}
#endif
