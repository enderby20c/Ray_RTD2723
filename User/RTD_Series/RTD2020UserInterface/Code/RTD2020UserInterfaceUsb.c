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
// ID Code      : RTD2020UserInterfaceUsb.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_USB__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceUsb.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

#if(_USB_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OSD Type-C U3 Mode Selection
// Input Value  : enumInputPort --> Input Port
// Output Value :  _USB_HUB_MODE_U3 / _USB_HUB_MODE_U2 / _USB_HUB_MODE_NONE
//--------------------------------------------------
EnumUsbHubMode UserInterfaceUsbGetOsdU3Mode(EnumInputPort enumInputPort)
{
    EnumUsbHubMode enumUsbMode = _USB_HUB_MODE_NONE;

    switch(enumInputPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            enumUsbMode = (GET_OSD_D0_TYPE_C_U3_MODE() == _TYPE_C_U3_ON ? _USB_HUB_MODE_U3 : _USB_HUB_MODE_U2);

            break;
#endif

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            enumUsbMode = (GET_OSD_D1_TYPE_C_U3_MODE() == _TYPE_C_U3_ON ? _USB_HUB_MODE_U3 : _USB_HUB_MODE_U2);

            break;
#endif

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            enumUsbMode = (GET_OSD_D2_TYPE_C_U3_MODE() == _TYPE_C_U3_ON ? _USB_HUB_MODE_U3 : _USB_HUB_MODE_U2);

            break;
#endif
        default:
            break;
    }

    return enumUsbMode;
}
#endif  // End of #if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)

#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OSD Type-C Tx U3 Mode Selection
// Input Value  : enumOutputPort --> Output Port
// Output Value :  _USB_HUB_MODE_U3 / _USB_HUB_MODE_U2 / _USB_HUB_MODE_NONE
//--------------------------------------------------
EnumUsbHubMode UserInterfaceUsbGetOsdTxU3Mode(EnumOutputPort enumOutputPort)
{
    EnumUsbHubMode enumUsbMode = _USB_HUB_MODE_NONE;

    switch(enumOutputPort)
    {
#if(_P0_USB_SUPPORT == _ON)
        case _P0_OUTPUT_PORT:

            // For Kernel to Get OSD Tx U3 Mode Selection,
            // Example:
            // enumUsbMode = (GET_OSD_P0_TYPE_C_U3_MODE() == _TYPE_C_U3_ON ? _USB_HUB_MODE_U3 : _USB_HUB_MODE_U2);

            break;
#endif

#if(_P1_USB_SUPPORT == _ON)
        case _P1_OUTPUT_PORT:

            break;
#endif

#if(_P2_USB_SUPPORT == _ON)
        case _P2_OUTPUT_PORT:

            break;
#endif

#if(_P3_USB_SUPPORT == _ON)
        case _P3_OUTPUT_PORT:

            break;
#endif

#if(_P4_USB_SUPPORT == _ON)
        case _P4_OUTPUT_PORT:

            break;
#endif

        default:
            break;
    }

    return enumUsbMode;
}
#endif  // End of #if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)

#endif // End of #if(_USB_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
