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
// ID Code      : ScalerTypeC_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC/ScalerTypeC.h"




#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
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
// Description  : Translate PCB Port into Type-C Port Index For Macro Usage
// Input Value  : enumTypeCPcbPort
// Output Value : Type-C Port Index
//--------------------------------------------------
BYTE ScalerTypeCGetTypeCIndex_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
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

//--------------------------------------------------
// Description  : Convert Dx Port to TypeC PCB Port
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
//--------------------------------------------------
EnumTypeCPcbPort ScalerTypeCDxConvertToPcbPort_WDINT(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = _NO_TYPE_C_PORT;

    switch(enumInputPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            enumTypeCPcbPort = _D0_TYPE_C_PORT;

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            enumTypeCPcbPort = _D1_TYPE_C_PORT;

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            enumTypeCPcbPort = _D2_TYPE_C_PORT;

            break;
#endif

        default:

            break;
    }
    return enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : Convert Px Port to TypeC PCB Port
// Input Value  : enumOutputPort --> Output
// Output Value : EnumTypeCPcbPort --> _P0_TYPE_C_PORT / _P1_TYPE_C_PORT...
//--------------------------------------------------
EnumTypeCPcbPort ScalerTypeCPxConvertToPcbPort_WDINT(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = _NO_TYPE_C_PORT;

    switch(enumOutputPort)
    {
#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P0_OUTPUT_PORT:

            enumTypeCPcbPort = _P0_TYPE_C_PORT;

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P1_OUTPUT_PORT:

            enumTypeCPcbPort = _P1_TYPE_C_PORT;

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P2_OUTPUT_PORT:

            enumTypeCPcbPort = _P2_TYPE_C_PORT;

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P3_OUTPUT_PORT:

            enumTypeCPcbPort = _P3_TYPE_C_PORT;

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P4_OUTPUT_PORT:

            enumTypeCPcbPort = _P4_TYPE_C_PORT;

            break;
#endif

        default:

            break;
    }
    return enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : Convert TypeC PCB Port to Dx Port
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
//--------------------------------------------------
EnumInputPort ScalerTypeCPcbPortConvertToDx_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            enumInputPort = _D0_INPUT_PORT;

            break;

        case _D1_TYPE_C_PORT:

            enumInputPort = _D1_INPUT_PORT;

            break;

        case _D2_TYPE_C_PORT:

            enumInputPort = _D2_INPUT_PORT;

            break;

        case _D3_TYPE_C_PORT:

            enumInputPort = _D3_INPUT_PORT;

            break;

        case _D4_TYPE_C_PORT:

            enumInputPort = _D4_INPUT_PORT;

            break;

        case _D5_TYPE_C_PORT:

            enumInputPort = _D5_INPUT_PORT;

            break;

        case _D6_TYPE_C_PORT:

            enumInputPort = _D6_INPUT_PORT;

            break;

        default:
            break;
    }
    return enumInputPort;
}

//--------------------------------------------------
// Description  : Convert TypeC PCB Port to Px Port
// Input Value  : enumTypeCPcbPort --> _P0_TYPE_C_PORT / _P1_TYPE_C_PORT...
// Output Value : enumOutputPort  --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
//--------------------------------------------------
EnumOutputPort ScalerTypeCPcbPortConvertToPx_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumOutputPort enumOutputPort = _NO_OUTPUT_PORT;

    switch(enumTypeCPcbPort)
    {
        case _P0_TYPE_C_PORT:

            enumOutputPort = _P0_OUTPUT_PORT;

            break;

        case _P1_TYPE_C_PORT:

            enumOutputPort = _P1_OUTPUT_PORT;

            break;

        case _P2_TYPE_C_PORT:

            enumOutputPort = _P2_OUTPUT_PORT;

            break;

        case _P3_TYPE_C_PORT:

            enumOutputPort = _P3_OUTPUT_PORT;

            break;

        case _P4_TYPE_C_PORT:

            enumOutputPort = _P4_OUTPUT_PORT;

            break;

        default:
            break;
    }
    return enumOutputPort;
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Attach Status
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCAttachStatus : _TYPE_C_UNATTACH / _TYPE_C_ATTACH
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCRxGetCcAttach_WDINT(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort_WDINT(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_CC_ATTACH_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Tx Port Attach Status
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : EnumTypeCAttachStatus : _TYPE_C_UNATTACH / _TYPE_C_ATTACH
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCTxGetCcAttach_WDINT(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort_WDINT(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_CC_ATTACH_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Orientation
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCOrientation : _TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP
//--------------------------------------------------
EnumTypeCOrientation ScalerTypeCRxGetOrientation_WDINT(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort_WDINT(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_ORIENTATION_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_ORIENTATION_UNFLIP;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Tx Port Orientation
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : EnumTypeCOrientation : _TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP
//--------------------------------------------------
EnumTypeCOrientation ScalerTypeCTxGetOrientation_WDINT(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort_WDINT(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_ORIENTATION_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_ORIENTATION_UNFLIP;
    }
}

//--------------------------------------------------
// Description  : Set Other Interface to Get Rx Port Pin Assignment
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCPinCfgType : _TYPE_C_PIN_ASSIGNMENT_C / _TYPE_C_PIN_ASSIGNMENT_D...
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeCRxGetPinAssignment_WDINT(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort_WDINT(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_PIN_ASSIGNMENT_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_PIN_ASSIGNMENT_NONE;
    }
}

//--------------------------------------------------
// Description  : Set Other Interface to Get Tx Port Pin Assignment
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : EnumTypeCPinCfgType : _TYPE_C_PIN_ASSIGNMENT_C / _TYPE_C_PIN_ASSIGNMENT_D...
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeCTxGetPinAssignment_WDINT(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort_WDINT(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_PIN_ASSIGNMENT_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_PIN_ASSIGNMENT_NONE;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Alt Mode Ready
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCAltModeStatus : _TYPE_C_ALT_MODE_NOT_READY / _TYPE_C_ALT_MODE_READY
//--------------------------------------------------
EnumTypeCAltModeStatus ScalerTypeCRxGetAltModeReady_WDINT(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort_WDINT(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_ALT_MODE_READY_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Tx Port Alt Mode Ready
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : EnumTypeCAltModeStatus : _TYPE_C_ALT_MODE_NOT_READY / _TYPE_C_ALT_MODE_READY
//--------------------------------------------------
EnumTypeCAltModeStatus ScalerTypeCTxGetAltModeReady_WDINT(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort_WDINT(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_ALT_MODE_READY_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Explicit Contract
// Input Value  : enumInputPort --> Inputput
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCRxGetExplicitContract_WDINT(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort_WDINT(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_EXPLICIT_CONTRACT_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Tx Port Explicit Contract
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCTxGetExplicitContract_WDINT(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort_WDINT(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_EXPLICIT_CONTRACT_WDINT(enumTypeCPcbPort);
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Cable Info For DPCD
// Input Value  : enumInputPort --> Inputput
// Output Value : StructTypeCCableInfoForDpcd
//--------------------------------------------------
StructTypeCCableInfoForDpcd ScalerTypeCRxGetCableInfoForDpcd_WDINT(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort_WDINT(enumInputPort);
    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        stTypeCCableInfoForDpcd = GET_TYPE_C_CBL_INFO_FOR_DPCD_WDINT(enumTypeCPcbPort);
    }

    return stTypeCCableInfoForDpcd;
}

//--------------------------------------------------
// Description  : For Other Interface to Check if Rx Port is Type-C Port Controller or Not
// Input Value  : enumInputPort --> Inputput
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCRxCheckTypeCSupportOn_WDINT(EnumInputPort enumInputPort)
{
    bit bTypeCSupportOn = _FALSE;

    switch(enumInputPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            bTypeCSupportOn = _TRUE;

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            bTypeCSupportOn = _TRUE;

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            bTypeCSupportOn = _TRUE;

            break;
#endif

        default:

            break;
    }

    return bTypeCSupportOn;
}

//--------------------------------------------------
// Description  : For Other Interface to Check if Rx Port is Type-C Port Controller or Not
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCTxCheckTypeCSupportOn_WDINT(EnumOutputPort enumOutputPort)
{
    bit bTypeCSupportOn = _FALSE;

    switch(enumOutputPort)
    {
#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P0_OUTPUT_PORT:

            bTypeCSupportOn = _TRUE;

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P1_OUTPUT_PORT:

            bTypeCSupportOn = _TRUE;

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P2_OUTPUT_PORT:

            bTypeCSupportOn = _TRUE;

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P3_OUTPUT_PORT:

            bTypeCSupportOn = _TRUE;

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P4_OUTPUT_PORT:

            bTypeCSupportOn = _TRUE;

            break;
#endif

        default:

            break;
    }

    return bTypeCSupportOn;
}

//--------------------------------------------------
// Description  : For Other Interface to Get Type-C Port Controller Type
// Input Value  : enumTypeCPcbPort
// Output Value : Type-C Port Controller Type
//--------------------------------------------------
EnumTypeCPortCtrlType ScalerTypeCGetPortCtrlType_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCPortCtrlType enumPortCtrlType = _TYPE_C_PORT_CTRL_NONE;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P0_TYPE_C_PORT:

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P1_TYPE_C_PORT:

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P2_TYPE_C_PORT:

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P3_TYPE_C_PORT:

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P4_TYPE_C_PORT:

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _ADAPTOR_TYPE_C_PORT:

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }

    return enumPortCtrlType;
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Type-C Port Controller Type
// Input Value  : enumInputPort --> Inputput
// Output Value : Type-C Port Controller Type
//--------------------------------------------------
EnumTypeCPortCtrlType ScalerTypeCRxGetPortCtrlType_WDINT(EnumInputPort enumInputPort)
{
    EnumTypeCPortCtrlType enumPortCtrlType = _TYPE_C_PORT_CTRL_NONE;

    switch(enumInputPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }

    return enumPortCtrlType;
}

//--------------------------------------------------
// Description  : For Other Interface to Get Tx Port Type-C Port Controller Type
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : Type-C Port Controller Type
//--------------------------------------------------
EnumTypeCPortCtrlType ScalerTypeCTxGetPortCtrlType_WDINT(EnumOutputPort enumOutputPort)
{
    EnumTypeCPortCtrlType enumPortCtrlType = _TYPE_C_PORT_CTRL_NONE;

    switch(enumOutputPort)
    {
#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P0_OUTPUT_PORT:

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P1_OUTPUT_PORT:

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P2_OUTPUT_PORT:

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P3_OUTPUT_PORT:

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P4_OUTPUT_PORT:

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTS;
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_USER;
#endif
            break;
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }

    return enumPortCtrlType;
}

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Convert Pcb Port to Embedded TypeC HW
// Input Value  : PcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : TypeC Index (_EMB_TYPE_C_0 / _EMB_TYPE_C_1...)
//--------------------------------------------------
EnumTypeCEmbeddedList ScalerTypeCPcbxTypeCxMapping_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumTypeCIndex = _EMB_TYPE_C_NOT_EXIST;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _D0_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _D0_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _D0_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _D0_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _D0_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _D1_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _D1_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _D1_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _D1_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _D1_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _D2_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _D2_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _D2_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _D2_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _D2_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

/*
#if(_D3_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _D3_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _D3_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _D3_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _D3_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _D3_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_D3_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
*/

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P0_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _P0_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _P0_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _P0_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _P0_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P1_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _P1_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _P1_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _P1_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _P1_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P2_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _P2_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _P2_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _P2_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _P2_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P3_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _P3_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _P3_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _P3_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _P3_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P4_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _P4_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _P4_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _P4_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _P4_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _ADAPTOR_TYPE_C_PORT:

            if(_EMB_TYPE_C_0_MAPPING == _ADAPTOR_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_0;
            }
            else if(_EMB_TYPE_C_1_MAPPING == _ADAPTOR_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_1;
            }
            else if(_EMB_TYPE_C_2_MAPPING == _ADAPTOR_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_2;
            }
            else if(_EMB_TYPE_C_3_MAPPING == _ADAPTOR_TYPE_C_PORT)
            {
                enumTypeCIndex = _EMB_TYPE_C_3;
            }

            break;
#endif  // End of #if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

        case _NO_TYPE_C_PORT:
        default:
            // Invalid Option : Trying to Get TypeC HW on No Port
            break;
    }

    return enumTypeCIndex;
}

//--------------------------------------------------
// Description  : Convert TypeC Index to Pcb Port
// Input Value  : TypeC Index (_TYPE_C_EMB_0 / _TYPE_C_EMB_1...)
// Output Value : PcbPort (D0_INPUT_PORT / D1_INPUT_PORT...)
//--------------------------------------------------
EnumTypeCPcbPort ScalerTypeCxPcbxMapping_WDINT(EnumTypeCEmbeddedList enumTypeCIndex)
{
    EnumTypeCPcbPort enumTypeCPcbPort = _NO_TYPE_C_PORT;

    switch(enumTypeCIndex)
    {
#if(_HW_EMB_TYPE_C_0_SUPPORT == _ON)
        case _EMB_TYPE_C_0:

            enumTypeCPcbPort = _EMB_TYPE_C_0_MAPPING;

            break;
#endif  // End of #if(_HW_EMB_TYPE_C_0_SUPPORT == _ON)

#if(_HW_EMB_TYPE_C_1_SUPPORT == _ON)
        case _EMB_TYPE_C_1:

            enumTypeCPcbPort = _EMB_TYPE_C_1_MAPPING;

            break;
#endif  // End of #if(_HW_EMB_TYPE_C_1_SUPPORT == _ON)

#if(_HW_EMB_TYPE_C_2_SUPPORT == _ON)
        case _EMB_TYPE_C_2:

            enumTypeCPcbPort = _EMB_TYPE_C_2_MAPPING;

            break;
#endif  // End of #if(_HW_EMB_TYPE_C_2_SUPPORT == _ON)

#if(_HW_EMB_TYPE_C_3_SUPPORT == _ON)
        case _EMB_TYPE_C_3:

            enumTypeCPcbPort = _EMB_TYPE_C_3_MAPPING;

            break;
#endif  // End of #if(_HW_EMB_TYPE_C_3_SUPPORT == _ON)

        case _EMB_TYPE_C_NOT_EXIST:
        default:
            // Invalid Option : Trying to Get PCB Port use Not Exist TypeC HW
            break;
    }

    return enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : Force Sending HPD IRQ for DP CTS
// Input Value  : enumInputPort --> Inputput, pucActiveWDID, pucActiveWDTime
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPdDpCTSForceHpdIrq_WDINT(EnumInputPort enumInputPort, BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping_WDINT(ScalerTypeCDxConvertToPcbPort_WDINT(enumInputPort));
    pucActiveWDID = pucActiveWDID;
    pucActiveWDTime = pucActiveWDTime;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if((_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON) && (_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX))
            ScalerTypeC0PdDpCTSForceHpdIrq_WDINT(pucActiveWDID, pucActiveWDTime);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if((_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) && (_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX))
            ScalerTypeC1PdDpCTSForceHpdIrq_WDINT(pucActiveWDID, pucActiveWDTime);
#endif

            break;
#endif

        default:

            break;
    }
}
#endif // End of #if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

