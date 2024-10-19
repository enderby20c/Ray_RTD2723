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
// ID Code      : ScalerHdmiFrlMacRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIFRLMACRX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "HdmiFrlMacRx/ScalerHdmiFrlMacRx.h"


#if(_HDMI_FRL_SUPPORT == _ON)
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
// Description  : Measure CDR Clk
// Input Value  : CDR CLK to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerHdmiFrlMacRxCdrOffMeasureClk_EXINT0(EnumInputPort enumInputPort, BYTE ucLane)
{
    enumInputPort = enumInputPort;
    ucLane = ucLane;

    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerHdmiFrlMacRx3OffMeasureClk_EXINT0(ucLane);
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerHdmiFrlMacRx4OffMeasureClk_EXINT0(ucLane);
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set FRL Rate
// Input Value  : enumInputPort, ucFrlRate
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(EnumInputPort enumInputPort, BYTE ucFrlRate)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_HDMI_FRL_D1_FRL_RATE(ucFrlRate);
            break;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_HDMI_FRL_D2_FRL_RATE(ucFrlRate);
            break;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_HDMI_FRL_D3_FRL_RATE(ucFrlRate);
            break;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_HDMI_FRL_D4_FRL_RATE(ucFrlRate);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get FRL Rate
// Input Value  : enumInputPort
// Output Value : FRL Rate
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_HDMI_FRL_D1_FRL_RATE();
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_HDMI_FRL_D2_FRL_RATE();
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_HDMI_FRL_D3_FRL_RATE();
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_HDMI_FRL_D4_FRL_RATE();
#endif

        default:
            break;
    }

    return _HDMI_FRL_RATE_NONE;
}

//--------------------------------------------------
// Description  : Get Max FRL Rate
// Input Value  : enumInputPort
// Output Value : Max FRL Rate
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRxGetDxMaxFrlRate_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return _D1_HDMI_FRL_MAX_LINK_RATE;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return _D2_HDMI_FRL_MAX_LINK_RATE;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return _D3_HDMI_FRL_MAX_LINK_RATE;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return _D4_HDMI_FRL_MAX_LINK_RATE;
#endif

        default:
            break;
    }

    return _HDMI_FRL_RATE_NONE;
}

//--------------------------------------------------
// Description  : Set FRL Max FFE Level
// Input Value  : enumInputPort, ucFrlFfeLevel
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxSetDxFrlMaxFfeLevel_EXINT0(EnumInputPort enumInputPort, BYTE ucFrlFfeLevel)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_HDMI_FRL_D1_MAX_FFE_LEVEL(ucFrlFfeLevel);
            break;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_HDMI_FRL_D2_MAX_FFE_LEVEL(ucFrlFfeLevel);
            break;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_HDMI_FRL_D3_MAX_FFE_LEVEL(ucFrlFfeLevel);
            break;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_HDMI_FRL_D4_MAX_FFE_LEVEL(ucFrlFfeLevel);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get FRL Max FFE Level
// Input Value  : enumInputPort
// Output Value : FRL FFE Level
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRxGetDxFrlMaxFfeLevel_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_HDMI_FRL_D1_MAX_FFE_LEVEL();
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_HDMI_FRL_D2_MAX_FFE_LEVEL();
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_HDMI_FRL_D3_MAX_FFE_LEVEL();
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_HDMI_FRL_D4_MAX_FFE_LEVEL();
#endif

        default:
            break;
    }

    return _HDMI_FRL_FFE0;
}

//--------------------------------------------------
// Description  : Add FRL Each Lane's FFE Level
// Input Value  : enumInputPort, ucLane
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxAddDxFrlFfeLevel_EXINT0(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    ADD_HDMI_FRL_D1_LANE0_FFE();
                    break;

                case _HDMI_FRL_LANE1:
                    ADD_HDMI_FRL_D1_LANE1_FFE();
                    break;

                case _HDMI_FRL_LANE2:
                    ADD_HDMI_FRL_D1_LANE2_FFE();
                    break;

                case _HDMI_FRL_LANE3:
                    ADD_HDMI_FRL_D1_LANE3_FFE();
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    ADD_HDMI_FRL_D2_LANE0_FFE();
                    break;

                case _HDMI_FRL_LANE1:
                    ADD_HDMI_FRL_D2_LANE1_FFE();
                    break;

                case _HDMI_FRL_LANE2:
                    ADD_HDMI_FRL_D2_LANE2_FFE();
                    break;

                case _HDMI_FRL_LANE3:
                    ADD_HDMI_FRL_D2_LANE3_FFE();
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    ADD_HDMI_FRL_D3_LANE0_FFE();
                    break;

                case _HDMI_FRL_LANE1:
                    ADD_HDMI_FRL_D3_LANE1_FFE();
                    break;

                case _HDMI_FRL_LANE2:
                    ADD_HDMI_FRL_D3_LANE2_FFE();
                    break;

                case _HDMI_FRL_LANE3:
                    ADD_HDMI_FRL_D3_LANE3_FFE();
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    ADD_HDMI_FRL_D4_LANE0_FFE();
                    break;

                case _HDMI_FRL_LANE1:
                    ADD_HDMI_FRL_D4_LANE1_FFE();
                    break;

                case _HDMI_FRL_LANE2:
                    ADD_HDMI_FRL_D4_LANE2_FFE();
                    break;

                case _HDMI_FRL_LANE3:
                    ADD_HDMI_FRL_D4_LANE3_FFE();
                    break;

                default:
                    break;
            }
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get FRL Each Lane's FFE Level
// Input Value  : enumInputPort, ucLane
// Output Value : FRL FFE Level
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRxGetDxFrlFfeLevel_EXINT0(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    return GET_HDMI_FRL_D1_LANE0_FFE();

                case _HDMI_FRL_LANE1:
                    return GET_HDMI_FRL_D1_LANE1_FFE();

                case _HDMI_FRL_LANE2:
                    return GET_HDMI_FRL_D1_LANE2_FFE();

                case _HDMI_FRL_LANE3:
                    return GET_HDMI_FRL_D1_LANE3_FFE();

                default:
                    break;
            }
            break;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    return GET_HDMI_FRL_D2_LANE0_FFE();

                case _HDMI_FRL_LANE1:
                    return GET_HDMI_FRL_D2_LANE1_FFE();

                case _HDMI_FRL_LANE2:
                    return GET_HDMI_FRL_D2_LANE2_FFE();

                case _HDMI_FRL_LANE3:
                    return GET_HDMI_FRL_D2_LANE3_FFE();

                default:
                    break;
            }
            break;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    return GET_HDMI_FRL_D3_LANE0_FFE();

                case _HDMI_FRL_LANE1:
                    return GET_HDMI_FRL_D3_LANE1_FFE();

                case _HDMI_FRL_LANE2:
                    return GET_HDMI_FRL_D3_LANE2_FFE();

                case _HDMI_FRL_LANE3:
                    return GET_HDMI_FRL_D3_LANE3_FFE();

                default:
                    break;
            }
            break;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    return GET_HDMI_FRL_D4_LANE0_FFE();

                case _HDMI_FRL_LANE1:
                    return GET_HDMI_FRL_D4_LANE1_FFE();

                case _HDMI_FRL_LANE2:
                    return GET_HDMI_FRL_D4_LANE2_FFE();

                case _HDMI_FRL_LANE3:
                    return GET_HDMI_FRL_D4_LANE3_FFE();

                default:
                    break;
            }
            break;
#endif

        default:
            break;
    }

    return _HDMI_FRL_FFE0;
}

//--------------------------------------------------
// Description  : Clear FRL Each Lane's FFE Level
// Input Value  : enumInputPort, ucLane
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    CLR_HDMI_FRL_D1_LANE0_FFE();
                    break;

                case _HDMI_FRL_LANE1:
                    CLR_HDMI_FRL_D1_LANE1_FFE();
                    break;

                case _HDMI_FRL_LANE2:
                    CLR_HDMI_FRL_D1_LANE2_FFE();
                    break;

                case _HDMI_FRL_LANE3:
                    CLR_HDMI_FRL_D1_LANE3_FFE();
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    CLR_HDMI_FRL_D2_LANE0_FFE();
                    break;

                case _HDMI_FRL_LANE1:
                    CLR_HDMI_FRL_D2_LANE1_FFE();
                    break;

                case _HDMI_FRL_LANE2:
                    CLR_HDMI_FRL_D2_LANE2_FFE();
                    break;

                case _HDMI_FRL_LANE3:
                    CLR_HDMI_FRL_D2_LANE3_FFE();
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    CLR_HDMI_FRL_D3_LANE0_FFE();
                    break;

                case _HDMI_FRL_LANE1:
                    CLR_HDMI_FRL_D3_LANE1_FFE();
                    break;

                case _HDMI_FRL_LANE2:
                    CLR_HDMI_FRL_D3_LANE2_FFE();
                    break;

                case _HDMI_FRL_LANE3:
                    CLR_HDMI_FRL_D3_LANE3_FFE();
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            switch(ucLane)
            {
                case _HDMI_FRL_LANE0:
                    CLR_HDMI_FRL_D4_LANE0_FFE();
                    break;

                case _HDMI_FRL_LANE1:
                    CLR_HDMI_FRL_D4_LANE1_FFE();
                    break;

                case _HDMI_FRL_LANE2:
                    CLR_HDMI_FRL_D4_LANE2_FFE();
                    break;

                case _HDMI_FRL_LANE3:
                    CLR_HDMI_FRL_D4_LANE3_FFE();
                    break;

                default:
                    break;
            }
            break;
#endif

        default:
            break;
    }
}
#endif // End for #if(_HDMI_FRL_SUPPORT == _ON)
