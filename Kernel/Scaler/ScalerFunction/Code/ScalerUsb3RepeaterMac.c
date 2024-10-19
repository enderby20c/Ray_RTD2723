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
// ID Code      : ScalerUsb3RepeaterMac.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Usb3RepeaterMac/ScalerUsb3RepeaterMac.h"

#if(_USB3_REPEATER_MAC_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_pbUsb3RepeaterMacU3EnablePdNoResponse[_TYPE_C_PORT_VALID];
bit g_bUsb3RepeaterMacU3PinDEnterFakeSavingU3Late;
BYTE g_ucUsb3RepeaterMacU3SupportSpeed;
BYTE g_ucUsb3RepeaterMacU3SupportLane;
BYTE g_ucUsb3RepeaterMacPowerCutMode;
EnumUsbHubOSDResult g_enumUsb3RepeaterMacHubOSDResult;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : USB3 Repeater Initial
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacInitial(EnumTypeCOrientation enumOrientation, EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumOrientation = enumOrientation;

    switch(ScalerUsb3RepeaterMacDx2MacxMapping(enumTypeCPcbPort))
    {
        case _RX0:
#if(_USB3_REDRIVER_MAC0_SUPPORT == _ON)
            ScalerUsb3RedriverMac0Initial();
#elif(_USB3_RETIMER_MAC0_SUPPORT == _ON)
            ScalerUsb3RetimerMac0Initial(enumOrientation);
#endif
            break;

        case _RX1:
#if(_USB3_REDRIVER_MAC1_SUPPORT == _ON)
            ScalerUsb3RedriverMac1Initial();
#elif(_USB3_RETIMER_MAC1_SUPPORT == _ON)
            ScalerUsb3RetimerMac1Initial();
#endif
            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Repeater Enable
// Input Value  : enumInputPort , bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacEnable(EnumTypeCPcbPort enumTypeCPcbPort, bit bEnable)
{
    switch(ScalerUsb3RepeaterMacDx2MacxMapping(enumTypeCPcbPort))
    {
        case _RX0:
#if(_USB3_REDRIVER_MAC0_SUPPORT == _ON)
            ScalerUsb3RedriverMac0Enable(bEnable);
#elif(_USB3_RETIMER_MAC0_SUPPORT == _ON)
            ScalerUsb3RetimerMac0Enable(bEnable);
#endif
            break;

        case _RX1:
#if(_USB3_REDRIVER_MAC1_SUPPORT == _ON)
            ScalerUsb3RedriverMac1Enable(bEnable);
#elif(_USB3_RETIMER_MAC1_SUPPORT == _ON)
            ScalerUsb3RetimerMac1Enable(bEnable);
#endif
            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Repeater Set Support Hightest Speed Capability
// Input Value  : ucUsbHubU3Speed
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacSetU3GenSpeed(BYTE ucUsbHubU3Speed)
{
    SET_USB_HUB_U3_SPEED_SUPPORT(ucUsbHubU3Speed);
}

//--------------------------------------------------
// Description  : USB3 Repeater Set Support Hightest Lane Count Capability
// Input Value  : ucUsbHubU3Lane
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacSetU3LaneCount(BYTE ucUsbHubU3Lane)
{
    SET_USB_HUB_U3_LANE_SUPPORT(ucUsbHubU3Lane);
}

//--------------------------------------------------
// Description  : USB3 Repeater Clean Support Speed/Lane Capability to Gen1x1
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacCleanU3Capability(void)
{
    // Reset U3 Speed Support Capability to Gen1
    CLR_USB_HUB_U3_SPEED_SUPPORT();

    // Reset U3 Lane Support Capability to x1 Lane
    CLR_USB_HUB_U3_LANE_SUPPORT();
}

//--------------------------------------------------
// Description  : USB3 Set the Hub Switch Port Result
// Input Value  : enumUsbHubOSDResult
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacSetU3HubOSDResult(EnumUsbHubOSDResult enumUsbHubOSDResult)
{
    SET_USB_HUB_SWITCH_PORT_RESULT(enumUsbHubOSDResult);
}

//--------------------------------------------------
// Description  : PD No Reponse Status Set by TypeC Handler
// Input Value  : enumTypeCPcbPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacSetPdNoResponse(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            SET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D0_TYPE_C_PORT);

            break;
#endif  // End of #if(_D0_USB_HUB_SUPPORT == _ON)

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            SET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D1_TYPE_C_PORT);

            break;
#endif  // End of #if(_D1_USB_HUB_SUPPORT == _ON)

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            SET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D2_TYPE_C_PORT);

            break;
#endif  // End of #if(_D2_USB_HUB_SUPPORT == _ON)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : PD No Reponse Status Set by TypeC Handler
// Input Value  : enumTypeCPcbPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacSetPdNoResponse_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            SET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE_WDINT(_D0_TYPE_C_PORT);

            break;
#endif  // End of #if(_D0_USB_HUB_SUPPORT == _ON)

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            SET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE_WDINT(_D1_TYPE_C_PORT);

            break;
#endif  // End of #if(_D1_USB_HUB_SUPPORT == _ON)

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            SET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE_WDINT(_D2_TYPE_C_PORT);

            break;
#endif  // End of #if(_D2_USB_HUB_SUPPORT == _ON)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Repeater Get PD No Reponse Status
// Input Value  : enumTypeCPcbPort
// Output Value : bit
//--------------------------------------------------
bit ScalerUsb3RepeaterMacGetPdNoResponse(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            return GET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D0_TYPE_C_PORT);

            break;
#endif  // End of #if(_D0_USB_HUB_SUPPORT == _ON)

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            return GET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D1_TYPE_C_PORT);

            break;
#endif  // End of #if(_D1_USB_HUB_SUPPORT == _ON)

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            return GET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D2_TYPE_C_PORT);

            break;
#endif  // End of #if(_D2_USB_HUB_SUPPORT == _ON)

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : USB3 Repeater Clean PD No Reponse Status
// Input Value  : enumTypeCPcbPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacCleanPdNoResponse(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            CLR_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D0_TYPE_C_PORT);

            break;
#endif  // End of #if(_D0_USB_HUB_SUPPORT == _ON)

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            CLR_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D1_TYPE_C_PORT);

            break;
#endif  // End of #if(_D1_USB_HUB_SUPPORT == _ON)

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            CLR_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(_D2_TYPE_C_PORT);

            break;
#endif  // End of #if(_D2_USB_HUB_SUPPORT == _ON)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Repeater Dx to Macx Mapping
// Input Value  : EnumTypeCPcbPort
// Output Value : Macx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterMacDx2MacxMapping(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_USB3_REPEATER_SUPPORT == _ON)
    return ScalerUsb3RepeaterMacUfpPhyx2MacxMapping(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort));
#endif
}

//--------------------------------------------------
// Description  : USB3 Repeater Dx to Macx Mapping
// Input Value  : EnumTypeCPcbPort
// Output Value : Macx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterMacDx2MacxMapping_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_USB3_REPEATER_SUPPORT == _ON)
    return ScalerUsb3RepeaterMacUfpPhyx2MacxMapping_EXINT3(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping_EXINT3(enumTypeCPcbPort));
#endif
}

//--------------------------------------------------
// Description  : USB3 Repeater Macx to Dx Mapping
// Input Value  : Macx
// Output Value : EnumTypeCPcbPort(Dx)
//--------------------------------------------------
EnumTypeCPcbPort ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(EnumRx enumMacxIndex)
{
#if(_USB3_REPEATER_SUPPORT == _ON)
    return ScalerUsb3RepeaterPhyUfpPhyx2DxMapping_EXINT3(ScalerUsb3RepeaterPhyMacx2UfpPhyxMapping_EXINT3(enumMacxIndex));
#endif
}

//--------------------------------------------------
// Description  : Translate PCB Port into Type-C Port Index For Macro Usage
// Input Value  : enumTypeCPcbPort
// Output Value : Type-C Port Index
//--------------------------------------------------
BYTE ScalerUsb3RepeaterMacGetTypeCIndex_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucIndex = 0x00;

#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _D2_TYPE_C_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _P1_TYPE_C_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _P2_TYPE_C_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _P3_TYPE_C_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _P4_TYPE_C_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        return ucIndex;
    }

#endif

    return ucIndex;
}

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
//-----------------------------------------------------------------
// Description  : Clear USB3 Retimer P3 Status
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsb3RepeaterMacClearLowPowerStateStatus(void)
{
#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
    ScalerUsb3RetimerMac0ClearLowPowerStateStatus();
#endif
}

//-----------------------------------------------------------------
// Description  : USB3 Retimer P3 Status
// Input Value  : None
// Output Value : GET_USB3_RETIMER_P3_STATUS
//-----------------------------------------------------------------
EnumUsb3RetimerP3State ScalerUsb3RepeaterMacGetLowPowerStateStatus(void)
{
#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
    return ScalerUsb3RetimerMac0GetLowPowerStateStatus();
#else
    return _USB3_RETIMER_NO_ACTION;
#endif
}

//-----------------------------------------------------------------
// Description  : Set USB3 Retimer P3 Status
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsb3RepeaterMacSetAtLowPowerStateStatus(void)
{
#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
    ScalerUsb3RetimerMac0SetAtLowPowerStateStatus();
#endif
}

//--------------------------------------------------
// Description  : USB3 Repeater Set Power Cut Mode
// Input Value  : ucUsbPowerCutMode
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacSetPowerCutMode(BYTE ucUsbPowerCutMode)
{
    SET_USB_REPEATER_POWER_CUT_MODE(ucUsbPowerCutMode);
}

//-----------------------------------------------------------------
// Description  : USB3 Retimer Detect NSQ at P3 state
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
bit ScalerUsb3RepeaterMacGetDetectNSQFlag(void)
{
#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
    return ScalerUsb3RetimerMac0GetDetectNSQFlag();
#endif
}

//----------------------------------------------------------------------------------
// Description  : USB3 Repeater Enter Fake Saving but RTSSM still at U0 State in PinD
// Input Value  : void
// Output Value : _TRUE / _FALSE
//----------------------------------------------------------------------------------
bit ScalerUsb3RepeaterMacGetPinDEnterFakeSavingU3Late(void)
{
    return GET_USB_REPEATER_PIND_FAKE_SAVING_U3_LATE();
}

//----------------------------------------------------------------------------------
// Description  : USB3 Repeater Enter Fake Saving but RTSSM still at U0 State in PinD
// Input Value  : void
// Output Value : void
//----------------------------------------------------------------------------------
void ScalerUsb3RepeaterMacClearPinDEnterFakeSavingU3Late(void)
{
    CLR_USB_REPEATER_PIND_FAKE_SAVING_U3_LATE();
}

//------------------------------------------------------------------------------
// Description  : USB3 Repeater Disable U3 IRQ Enable to avoid unexpected power off
// Input Value  : void
// Output Value : void
//------------------------------------------------------------------------------
void ScalerUsb3RepeaterMacDisableU3IRQ(void)
{
    ScalerUsb3RetimerMac0DisableU3IRQ();
}
#endif

#endif // End of #if(_USB3_REPEATER_MAC_SUPPORT == _ON)
