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
// ID Code      : RL6952_Series_TmdsMacRx_EXINT1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_TMDSMAC_EXINT1__

#include "ScalerFunctionInclude.h"
#include "TmdsMacRx/ScalerTmdsMacRx.h"



#if(_HDMI_SUPPORT == _ON)
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
// Description  : TMDS Mac mapping to Phy
// Input Value  : Mac Rx
// Output Value : Phy Rx
//--------------------------------------------------
EnumRx ScalerTmdsMacRxMacPhyMapping_EXINT1(EnumRx enumMacRxIndex)
{
    EnumRx enumPhyRxIndex = _RX_MAP_NONE;

    switch(enumMacRxIndex)
    {
        case _RX3:

            enumPhyRxIndex = _RX3;
            break;

        case _RX4:

            enumPhyRxIndex = _RX4;
            break;

        default:

            break;
    }

    return enumPhyRxIndex;
}

//--------------------------------------------------
// Description  : TMDS Phy mapping to Mac
// Input Value  : Phy Rx
// Output Value : Mac Rx
//--------------------------------------------------
EnumRx ScalerTmdsMacRxPhyMacMapping_EXINT1(EnumRx enumPhyRxIndex)
{
    EnumRx enumMacRxIndex = _RX_MAP_NONE;

    switch(enumPhyRxIndex)
    {
        case _RX3:

            enumMacRxIndex = _RX3;
            break;

        case _RX4:

            enumMacRxIndex = _RX4;
            break;

        default:

            break;
    }

    return enumMacRxIndex;
}

#endif

