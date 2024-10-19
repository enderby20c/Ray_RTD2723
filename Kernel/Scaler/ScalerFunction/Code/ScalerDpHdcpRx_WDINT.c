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
// ID Code      : ScalerDpHdcpRx_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcpRx/ScalerDpHdcpRx.h"




#if(_DP_HDCP_RX_SUPPORT == _ON)
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
// Description  : DP Port Rx mapping to Dx
// Input Value  : Rx
// Output Value : Dx
//--------------------------------------------------
EnumInputPort ScalerDpHdcpRxRxDxMapping_WDINT(EnumRx enumRx)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumRx)
    {
#if(_DP_HDCP_RX0_SUPPORT == _ON)

        case _RX0:

            if(_HW_D0_DP_HDCP_RX_MAPPING == _RX0)
            {
                enumInputPort = _D0_INPUT_PORT;
            }

            break;
#endif

#if(_DP_HDCP_RX1_SUPPORT == _ON)

        case _RX1:

            if(_HW_D1_DP_HDCP_RX_MAPPING == _RX1)
            {
                enumInputPort = _D1_INPUT_PORT;
            }

            break;
#endif

#if(_DP_HDCP_RX2_SUPPORT == _ON)

        case _RX2:

            if(_HW_D2_DP_HDCP_RX_MAPPING == _RX2)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

        default:

            break;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : DP Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx0 or Rx1 or Rx2
//--------------------------------------------------
EnumRx ScalerDpHdcpRxDxRxMapping_WDINT(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            enumRx = _HW_D0_DP_HDCP_RX_MAPPING;

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            enumRx = _HW_D1_DP_HDCP_RX_MAPPING;

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            enumRx = _HW_D2_DP_HDCP_RX_MAPPING;

            break;
#endif

        default:

            break;
    }

    return enumRx;
}
#endif // End of #if(_DP_HDCP_RX_SUPPORT == _ON)
