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
// ID Code      : RL6952_Series_TmdsPhyRx_EXINT1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_TMDSPHYRX_EXINT1__

#include "ScalerFunctionInclude.h"
#include "TmdsPhyRx/ScalerTmdsPhyRx.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx1 or Rx2 or Rx3
//--------------------------------------------------
EnumRx ScalerTmdsPhyRxDxRxMapping_EXINT1(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

    switch(enumInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumRx = _HW_D0_TMDS_PHY_RX_MAPPING;
            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumRx = _HW_D1_TMDS_PHY_RX_MAPPING;
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumRx = _HW_D2_TMDS_PHY_RX_MAPPING;
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            enumRx = _HW_D3_TMDS_PHY_RX_MAPPING;
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            enumRx = _HW_D4_TMDS_PHY_RX_MAPPING;
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            enumRx = _HW_D5_TMDS_PHY_RX_MAPPING;
            break;
#endif
        default:
            break;
    }
    return enumRx;
}
#endif
