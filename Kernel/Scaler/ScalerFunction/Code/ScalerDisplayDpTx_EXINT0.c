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
// ID Code      : ScalerDisplayDpTx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_DP_TX__

#include "ScalerFunctionInclude.h"
#include "DisplayDpTx/ScalerDisplayDpTx.h"

#if(_DISPLAY_DP_TX_SUPPORT == _ON)
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
// Description  : Get Display Dp Tx Mac Switch Status
// Input Value  : EnumDisplayDpTxOutputPort
// Output Value : EnumDisplayDpMacSel
//--------------------------------------------------
EnumDisplayDpMacSel ScalerDisplayDpTxGetMacSwitch_EXINT0(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    enumDisplayDpTxOutputPort = enumDisplayDpTxOutputPort;

    if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16)
    {
        switch(enumDisplayDpTxOutputPort)
        {
            case _DISPLAY_DP_TX_PORT_0:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC0 : _DISPLAY_DP_TX_MAC3);

            case _DISPLAY_DP_TX_PORT_1:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC1 : _DISPLAY_DP_TX_MAC2);

            case _DISPLAY_DP_TX_PORT_2:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC2 : _DISPLAY_DP_TX_MAC1);

            case _DISPLAY_DP_TX_PORT_3:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC3 : _DISPLAY_DP_TX_MAC0);

            default:
                break;
        }
        return _DISPLAY_DP_TX_NO_MAC;
    }
    else if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)
    {
        switch(enumDisplayDpTxOutputPort)
        {
            case _DISPLAY_DP_TX_PORT_1:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC0 : _DISPLAY_DP_TX_MAC1);

            case _DISPLAY_DP_TX_PORT_2:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC1 : _DISPLAY_DP_TX_MAC0);

            case _DISPLAY_DP_TX_PORT_0:
            case _DISPLAY_DP_TX_PORT_3:
            default:
                break;
        }
        return _DISPLAY_DP_TX_NO_MAC;
    }
    else
    {
        return _DISPLAY_DP_TX_MAC0;
    }
}

#if(_PANEL_DPTX_HPD_DETECT == _ON)
#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
//--------------------------------------------------
// Description  : Dp Tx Int Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxIrqIntHandler_EXINT0(void)
{
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxIrqHpdHandler_EXINT0(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxIrqHpdHandler_EXINT0(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxIrqHpdHandler_EXINT0(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxIrqHpdHandler_EXINT0(_DISPLAY_DP_TX_PORT_3);
    }
}

//--------------------------------------------------
// Description  : Dp Tx Irq Hpd Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxIrqHpdHandler_EXINT0(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    EnumDisplayDpTxOutputPort enumDisplayDpTxPortBackup = GET_DISPLAY_DP_TX_PORT();

    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    ScalerDisplayDpTxXIrqHpdHandler_EXINT0(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxPortBackup);
}
#endif
#endif
#endif // End of #if(_DISPLAY_DP_TX_SUPPORT == _ON)
