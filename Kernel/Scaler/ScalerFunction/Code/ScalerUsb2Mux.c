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
// ID Code      : ScalerUsb2Mux.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Usb2Mux/ScalerUsb2Mux.h"

#if(_HW_USB2_EMB_MUX_SUPPORT == _ON)

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
// Description  : U2 Mux Switch Control
// Input Value  : On or Off
// Output Value : None
//--------------------------------------------------
void ScalerUsb2MuxSwitchControl(EnumInputPort enumInputPort, EnumUSBHubPathEnable enumUSBHubPathEnable)
{
    enumUSBHubPathEnable = enumUSBHubPathEnable;
    switch(enumInputPort)
    {
#if(_D0_USB2_GO_THROUGH_SCALER == _ON)
        case _D0_INPUT_PORT:

            if(enumUSBHubPathEnable == _USB_PATH_ENABLE)
            {
                // Redriver Select Data Path U2 Mux From D0
                // 0xC180[5:4]= 2'b01 => UFP0 to DFP
                ScalerSetBit(PC1_80_U2MUX_SELECT, ~(_BIT5 | _BIT4), _BIT4);
            }
            else
            {
                // Redriver Select Data Path U2 Mux From None
                // 0xC180[5:4]= 2'b00 => None to DFP
                ScalerSetBit(PC1_80_U2MUX_SELECT, ~(_BIT5 | _BIT4), 0x00);
            }

            break;
#endif // End of #if(_D0_USB2_GO_THROUGH_SCALER == _ON)

#if(_D1_USB2_GO_THROUGH_SCALER == _ON)
        case _D1_INPUT_PORT:

            if(enumUSBHubPathEnable == _USB_PATH_ENABLE)
            {
                // Redriver Select Data Path U2 Mux From D1
                // 0xC180[5:4]= 2'b10 => UFP1 to DFP
                ScalerSetBit(PC1_80_U2MUX_SELECT, ~(_BIT5 | _BIT4), _BIT5);
            }
            else
            {
                // Redriver Select Data Path U2 Mux From None
                // 0xC180[5:4]= 2'b00 => None to DFP
                ScalerSetBit(PC1_80_U2MUX_SELECT, ~(_BIT5 | _BIT4), 0x00);
            }

            break;
#endif // End of #if(_D1_USB2_GO_THROUGH_SCALER == _ON)

        default:
            break;
    }
}
#endif

