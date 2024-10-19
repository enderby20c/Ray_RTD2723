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
// ID Code      : ScalerTypeC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC/ScalerTypeC.h"


#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1))
#warning "NOTE: _TYPE_C_DPAM_VERSION < 2.1 when D0 is TypeC Port and DP Support 128/132B Coding, Cable ID Cannot Not Be Identified."
#endif
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#warning "NOTE: UserInterfaceUsbTypeCUserGetCableInfoForDpcd Should Be Implemented for Cable ID when DP Support UHBR."
#endif
#endif // End of #if(_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON)

#if(_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1))
#warning "NOTE: _TYPE_C_DPAM_VERSION < 2.1 when D1 is TypeC Port and DP Support 128/132B Coding, Cable ID Cannot Not Be Identified."
#endif
#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#warning "NOTE: UserInterfaceUsbTypeCUserGetCableInfoForDpcd Should Be Implemented for Cable ID when DP Support UHBR."
#endif
#endif  // End of #if(_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON)

#if(_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1))
#warning "NOTE: _TYPE_C_DPAM_VERSION < 2.1 when D2 is TypeC Port and DP Support 128/132B Coding, Cable ID Cannot Not Be Identified."
#endif
#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#warning "NOTE: UserInterfaceUsbTypeCUserGetCableInfoForDpcd Should Be Implemented for Cable ID when DP Support UHBR."
#endif
#endif  // End of #if(_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON)

// DP Tx Use P0
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1))
#warning "NOTE: _TYPE_C_DPAM_VERSION < 2.1 when P0 is TypeC Port and DP Support 128/132B Coding, Cable ID Cannot Not Be Identified."
#endif
#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#warning "NOTE: UserInterfaceUsbTypeCUserGetCableInfoForDpcd Should Be Implemented for Cable ID when DP Support UHBR."
#endif
#endif  // End of #if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif  // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
EnumTypeCPcbPort g_penumTypeCEmbeddedPort[_EMB_TYPE_C_PORT_VALID] =
{
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _D0_TYPE_C_PORT,
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _D1_TYPE_C_PORT,
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _D2_TYPE_C_PORT,
#endif

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _P0_TYPE_C_PORT,
#endif

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _P1_TYPE_C_PORT,
#endif

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _P2_TYPE_C_PORT,
#endif

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _P3_TYPE_C_PORT,
#endif

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _P4_TYPE_C_PORT,
#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    _ADAPTOR_TYPE_C_PORT,
#endif

    _VALUE_NO_TYPE_C_PORT,
};
#endif // End of #if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)

#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
EnumTypeCPcbPort g_penumTypeCTcpmPort[_TCPM_PORT_VALID] =
{
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _D0_TYPE_C_PORT,
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _D1_TYPE_C_PORT,
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _D2_TYPE_C_PORT,
#endif

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _P0_TYPE_C_PORT,
#endif

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _P1_TYPE_C_PORT,
#endif

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _P2_TYPE_C_PORT,
#endif

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _P3_TYPE_C_PORT,
#endif

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _P4_TYPE_C_PORT,
#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    _ADAPTOR_TYPE_C_PORT,
#endif
};
#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
volatile EnumSysModeStatusForUsb g_enumTypeCSysModeStatus;
StructTypeCInfo g_pstTypeCInfo[_TYPE_C_PORT_VALID];
volatile StructTypeCCableInfoForDpcd g_pstTypeCCableInfoForDpcd[_TYPE_C_PORT_VALID];

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
volatile StructTypeCPowerInfo g_stTypeC0PowerInfo;
StructTypeCPowerProtectInfo g_pstTypeC0PowerProtectInfo[_MAX_DATA_OBJ_CNT];
#endif
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
volatile StructTypeCPowerInfo g_stTypeC1PowerInfo;
StructTypeCPowerProtectInfo g_pstTypeC1PowerProtectInfo[_MAX_DATA_OBJ_CNT];
#endif

#if(_PORT_CTRL_RTS_SUPPORT == _ON)
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
bit g_bTypeCRtsLenovoAltModeUrgentEvent = _FALSE;
#endif
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Translate PCB Port into Type-C Port Index For Macro Usage
// Input Value  : enumTypeCPcbPort
// Output Value : Type-C Port Index
//--------------------------------------------------
BYTE ScalerTypeCGetTypeCIndex(EnumTypeCPcbPort enumTypeCPcbPort)
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

    // enumInputPort Invalid : Show Warning Message
    DebugMessageTypeC("8. [TYPE C] ==========X Invalid TypeC PCB Port For TypeC Index", enumTypeCPcbPort);

    return ucIndex;
}

//--------------------------------------------------
// Description  : Convert Dx Port to TypeC PCB Port
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
//--------------------------------------------------
EnumTypeCPcbPort ScalerTypeCDxConvertToPcbPort(EnumInputPort enumInputPort)
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
EnumTypeCPcbPort ScalerTypeCPxConvertToPcbPort(EnumOutputPort enumOutputPort)
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
EnumInputPort ScalerTypeCPcbPortConvertToDx(EnumTypeCPcbPort enumTypeCPcbPort)
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
EnumOutputPort ScalerTypeCPcbPortConvertToPx(EnumTypeCPcbPort enumTypeCPcbPort)
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
// Description  : Set System Mode Status to Scaler Level
// Input Value  : System Mode Staus
// Output Value : void
//--------------------------------------------------
void ScalerTypeCSetSysModeStatus(EnumSysModeStatusForUsb enumSysModeStatus)
{
    SET_TYPE_C_SYS_MODE_STATUS(enumSysModeStatus);
}

//--------------------------------------------------
// Description  : Set System Level Attach Status to Scaler Level
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), Attach Status
// Output Value : void
//--------------------------------------------------
void ScalerTypeCSetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCAttachStatus enumAttachStatus)
{
    SET_TYPE_C_CC_ATTACH(enumTypeCPcbPort, enumAttachStatus);
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Attach Status
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCAttachStatus : _TYPE_C_UNATTACH / _TYPE_C_ATTACH
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCRxGetCcAttach(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_CC_ATTACH(enumTypeCPcbPort);
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
EnumTypeCAttachStatus ScalerTypeCTxGetCcAttach(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_CC_ATTACH(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Set System Level Orientation to Scaler Level
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), _TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP
// Output Value : void
//--------------------------------------------------
void ScalerTypeCSetOrientation(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCOrientation enumOrientation)
{
    SET_TYPE_C_ORIENTATION(enumTypeCPcbPort, enumOrientation);
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Orientation
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCOrientation : _TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP
//--------------------------------------------------
EnumTypeCOrientation ScalerTypeCRxGetOrientation(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_ORIENTATION(enumTypeCPcbPort);
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
EnumTypeCOrientation ScalerTypeCTxGetOrientation(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_ORIENTATION(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_ORIENTATION_UNFLIP;
    }
}

//--------------------------------------------------
// Description  : Set System Level Pin Assignment to Scaler Level
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), Pin Assignment
// Output Value : void
//--------------------------------------------------
void ScalerTypeCSetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment)
{
    SET_TYPE_C_PIN_ASSIGNMENT(enumTypeCPcbPort, enumPinAssignment);
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Pin Assignment
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCPinCfgType : _TYPE_C_PIN_ASSIGNMENT_C / _TYPE_C_PIN_ASSIGNMENT_D...
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeCRxGetPinAssignment(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_PIN_ASSIGNMENT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_PIN_ASSIGNMENT_NONE;
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Tx Port Pin Assignment
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : EnumTypeCPinCfgType : _TYPE_C_PIN_ASSIGNMENT_C / _TYPE_C_PIN_ASSIGNMENT_D...
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeCTxGetPinAssignment(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_PIN_ASSIGNMENT(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_PIN_ASSIGNMENT_NONE;
    }
}

//--------------------------------------------------
// Description  : Set System Level Alt Mode Ready to Scaler Level
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), Alt Mode Ready
// Output Value : void
//--------------------------------------------------
void ScalerTypeCSetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCAltModeStatus enumAltModeStatus)
{
    SET_TYPE_C_ALT_MODE_READY(enumTypeCPcbPort, enumAltModeStatus);
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Alt Mode Ready
// Input Value  : enumInputPort --> Inputput
// Output Value : EnumTypeCAltModeStatus : _TYPE_C_ALT_MODE_NOT_READY / _TYPE_C_ALT_MODE_READY
//--------------------------------------------------
EnumTypeCAltModeStatus ScalerTypeCRxGetAltModeReady(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_ALT_MODE_READY(enumTypeCPcbPort);
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
EnumTypeCAltModeStatus ScalerTypeCTxGetAltModeReady(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_ALT_MODE_READY(enumTypeCPcbPort);
    }
    else
    {
        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

//--------------------------------------------------
// Description  : Set System Level Explicit Contract to Scaler Level
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), Explicit Contract
// Output Value : void
//--------------------------------------------------
void ScalerTypeCSetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort, bit bGetExplicitContract)
{
    if(bGetExplicitContract == _TRUE)
    {
        SET_TYPE_C_EXPLICIT_CONTRACT(enumTypeCPcbPort);
    }
    else
    {
        CLR_TYPE_C_EXPLICIT_CONTRACT(enumTypeCPcbPort);
    }
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Explicit Contract
// Input Value  : enumInputPort --> Inputput
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCRxGetExplicitContract(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort(enumInputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_EXPLICIT_CONTRACT(enumTypeCPcbPort);
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
bit ScalerTypeCTxGetExplicitContract(EnumOutputPort enumOutputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCPxConvertToPcbPort(enumOutputPort);

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        return GET_TYPE_C_EXPLICIT_CONTRACT(enumTypeCPcbPort);
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set System Level Cable Info For DPCD to Scaler Level
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), stTypeCCableInfoForDpcd
// Output Value : void
//--------------------------------------------------
void ScalerTypeCSetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd)
{
    SET_TYPE_C_CBL_INFO_FOR_DPCD(enumTypeCPcbPort, stTypeCCableInfoForDpcd);
}

//--------------------------------------------------
// Description  : For Other Interface to Get Rx Port Cable Info For DPCD
// Input Value  : enumInputPort --> Inputput
// Output Value : StructTypeCCableInfoForDpcd
//--------------------------------------------------
StructTypeCCableInfoForDpcd ScalerTypeCRxGetCableInfoForDpcd(EnumInputPort enumInputPort)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort(enumInputPort);
    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};

    if(enumTypeCPcbPort != _NO_TYPE_C_PORT)
    {
        stTypeCCableInfoForDpcd = GET_TYPE_C_CBL_INFO_FOR_DPCD(enumTypeCPcbPort);
    }

    return stTypeCCableInfoForDpcd;
}

//--------------------------------------------------
// Description  : For Other Interface to Get if Rx Port (Extern Port Ctrl) Lane Mapping For Pin E is Swapped By Scaler
// Input Value  : enumInputPort --> Inputput
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCRxGetExtPinELaneSwapByScaler(EnumInputPort enumInputPort)
{
    bit bSwapByScaler = _FALSE;

    switch(enumInputPort)
    {
#if((_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
        case _D0_INPUT_PORT:

#if(_D0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E == _SWAP_BY_SCALER)
            bSwapByScaler = _TRUE;
#endif
            break;
#endif

#if((_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
        case _D1_INPUT_PORT:

#if(_D1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E == _SWAP_BY_SCALER)
            bSwapByScaler = _TRUE;
#endif
            break;
#endif

#if((_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
        case _D2_INPUT_PORT:

#if(_D2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E == _SWAP_BY_SCALER)
            bSwapByScaler = _TRUE;
#endif
            break;
#endif

        default:

            break;
    }

    return bSwapByScaler;
}

//--------------------------------------------------
// Description  : For Other Interface to Get if Tx Port (Extern Port Ctrl) Lane Mapping For Pin E is Swapped By Scaler
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCTxGetExtPinELaneSwapByScaler(EnumOutputPort enumOutputPort)
{
    bit bSwapByScaler = _FALSE;

    switch(enumOutputPort)
    {
#if((_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
        case _P0_OUTPUT_PORT:

#if(_P0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E == _SWAP_BY_SCALER)
            bSwapByScaler = _TRUE;
#endif
            break;
#endif

#if((_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
        case _P1_OUTPUT_PORT:

#if(_P1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E == _SWAP_BY_SCALER)
            bSwapByScaler = _TRUE;
#endif
            break;
#endif

#if((_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
        case _P2_OUTPUT_PORT:

#if(_P2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E == _SWAP_BY_SCALER)
            bSwapByScaler = _TRUE;
#endif
            break;
#endif

#if((_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
        case _P3_OUTPUT_PORT:

#if(_P3_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E == _SWAP_BY_SCALER)
            bSwapByScaler = _TRUE;
#endif
            break;
#endif

#if((_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
        case _P4_OUTPUT_PORT:

#if(_P4_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E == _SWAP_BY_SCALER)
            bSwapByScaler = _TRUE;
#endif
            break;
#endif

        default:

            break;
    }

    return bSwapByScaler;
}

//--------------------------------------------------
// Description  : For Other Interface to Check if Rx Port is Type-C Port Controller or Not
// Input Value  : enumInputPort --> Inputput
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCRxCheckTypeCSupportOn(EnumInputPort enumInputPort)
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
bit ScalerTypeCTxCheckTypeCSupportOn(EnumOutputPort enumOutputPort)
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
EnumTypeCPortCtrlType ScalerTypeCGetPortCtrlType(EnumTypeCPcbPort enumTypeCPcbPort)
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
EnumTypeCPortCtrlType ScalerTypeCRxGetPortCtrlType(EnumInputPort enumInputPort)
{
    EnumTypeCPortCtrlType enumPortCtrlType = _TYPE_C_PORT_CTRL_NONE;

    switch(enumInputPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_TCPM;
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTD;
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
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_TCPM;
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTD;
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
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_TCPM;
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTD;
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
EnumTypeCPortCtrlType ScalerTypeCTxGetPortCtrlType(EnumOutputPort enumOutputPort)
{
    EnumTypeCPortCtrlType enumPortCtrlType = _TYPE_C_PORT_CTRL_NONE;

    switch(enumOutputPort)
    {
#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P0_OUTPUT_PORT:

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_EMBEDDED;
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_TCPM;
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTD;
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
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_TCPM;
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTD;
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
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_TCPM;
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTD;
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
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_TCPM;
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTD;
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
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_TCPM;
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumPortCtrlType = _TYPE_C_PORT_CTRL_RTD;
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
#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
//--------------------------------------------------
// Description  : TypeC Vbus Powered Sink Initial Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCVbusPoweredSnkInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0CcVbusPoweredSnkInitial();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1CcVbusPoweredSnkInitial();

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Convert Pcb Port to Embedded TypeC HW
// Input Value  : PcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : TypeC Index (_EMB_TYPE_C_0 / _EMB_TYPE_C_1...)
//--------------------------------------------------
EnumTypeCEmbeddedList ScalerTypeCPcbxTypeCxMapping(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumTypeCIndex = _EMB_TYPE_C_NOT_EXIST;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _D0_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_D0_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_D0_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_D0_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_D0_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _D1_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_D1_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_D1_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_D1_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_D1_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _D2_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_D2_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_D2_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_D2_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_D2_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

/*
#if(_D3_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _D3_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _D3_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _D3_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _D3_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _D3_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_D3_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
*/

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P0_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_P0_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P0_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_P0_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_P0_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P1_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_P1_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P1_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_P1_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_P1_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P2_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_P2_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P2_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_P2_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_P2_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P3_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_P3_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P3_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_P3_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_P3_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _P4_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_P4_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P4_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_P4_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_P4_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

            break;
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        case _ADAPTOR_TYPE_C_PORT:

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_0;
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_1;
#elif(_EMB_TYPE_C_2_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_2;
#elif(_EMB_TYPE_C_3_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
            enumTypeCIndex = _EMB_TYPE_C_3;
#endif

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
EnumTypeCPcbPort ScalerTypeCxPcbxMapping(EnumTypeCEmbeddedList enumTypeCIndex)
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

#if((_EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING) ||\
    (_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
//--------------------------------------------------
// Description  : Get PMIC interrupt detect status
// Input Value  : enumTypeCPcbPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTypeCGetPmicInterruptDetectStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bPinCheck = _FALSE;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
            bPinCheck = (PCB_D0_PMIC_INTERRUPT_DETECT() == _D0_PMIC_INTERRUPT_ON);
            break;

        case _D1_TYPE_C_PORT:
            bPinCheck = (PCB_D1_PMIC_INTERRUPT_DETECT() == _D1_PMIC_INTERRUPT_ON);
            break;

        case _D2_TYPE_C_PORT:
            bPinCheck = (PCB_D2_PMIC_INTERRUPT_DETECT() == _D2_PMIC_INTERRUPT_ON);
            break;

        case _P0_TYPE_C_PORT:
            bPinCheck = (PCB_P0_PMIC_INTERRUPT_DETECT() == _P0_PMIC_INTERRUPT_ON);
            break;

        case _P1_TYPE_C_PORT:
            bPinCheck = (PCB_P1_PMIC_INTERRUPT_DETECT() == _P1_PMIC_INTERRUPT_ON);
            break;

        case _P2_TYPE_C_PORT:
            bPinCheck = (PCB_P2_PMIC_INTERRUPT_DETECT() == _P2_PMIC_INTERRUPT_ON);
            break;

        case _P3_TYPE_C_PORT:
            bPinCheck = (PCB_P3_PMIC_INTERRUPT_DETECT() == _P3_PMIC_INTERRUPT_ON);
            break;

        case _P4_TYPE_C_PORT:
            bPinCheck = (PCB_P4_PMIC_INTERRUPT_DETECT() == _P4_PMIC_INTERRUPT_ON);
            break;

        case _ADAPTOR_TYPE_C_PORT:
            bPinCheck = (PCB_ADAPTOR_PMIC_INTERRUPT_DETECT() == _ADAPTOR_PMIC_INTERRUPT_ON);
            break;

        default:
            break;
    }

    return bPinCheck;
}
#endif

//--------------------------------------------------
// Description  : Type C Handler Process
// Input Value  : EnumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCHandler(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // Convert TypeC Port (PCB) to IC TypeC HW Index
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0CcHandler();

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1CcHandler();

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Clock Setting (Always Use IOSC = 28MHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCClockSetting(BYTE ucClockSel)
{
    if(ucClockSel == _IOSC_CLK)
    {
#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN))
        ScalerTypeC0PmicHwIICSetFreqDiv(_IOSC_CLK);
#endif

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        ScalerTypeC0CcClkSel(_IOSC_CLK);
        ScalerTypeC0PdClkSel(_IOSC_CLK);

#endif

#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
        ScalerTypeC1PmicHwIICSetFreqDiv(_IOSC_CLK);
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        ScalerTypeC1CcClkSel(_IOSC_CLK);
        ScalerTypeC1PdClkSel(_IOSC_CLK);
#endif
    }
}

//--------------------------------------------------
// Description  : Return Embedded Port Ctrl CC Attached Status
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : CC Attach Status(_TYPE_C_ATTACH / _TYPE_C_UNATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCGetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAttachStatus enumCcAttach = _TYPE_C_UNATTACH;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            // Get CC Attach from TypeC 0
            enumCcAttach = (GET_TYPE_C_0_CC_ATTACHED() == _TRUE ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            // Get CC Attach from TypeC 1
            enumCcAttach = (GET_TYPE_C_1_CC_ATTACHED() == _TRUE ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
    return enumCcAttach;
}

//--------------------------------------------------
// Description  : Return Embedded Port Ctrl DP Alt Mode Ready Status
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : DP Alt Mode Ready Status (_TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAltModeStatus enumAltModeReady = _TYPE_C_ALT_MODE_NOT_READY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            // Get Alt Mode Ready from TypeC 0
            enumAltModeReady = (ScalerTypeC0PdGetAltModeReady() == _TRUE ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            // Get Alt Mode Ready from TypeC 1
            enumAltModeReady = (ScalerTypeC1PdGetAltModeReady() == _TRUE ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
    return enumAltModeReady;
}

//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Alt Mode Ready Status
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : Orientation (_TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP)
//--------------------------------------------------
EnumTypeCOrientation ScalerTypeCGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCOrientation enumOrientation = _TYPE_C_ORIENTATION_UNFLIP;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            // Get Alt Mode Ready from TypeC 0
            enumOrientation = GET_TYPE_C_0_CC_ORIENTATION();

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            // Get Alt Mode Ready from TypeC 1
            enumOrientation = GET_TYPE_C_1_CC_ORIENTATION();

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
    return enumOrientation;
}

//--------------------------------------------------
// Description  : Get Embedded Port Ctrl Pin Assignment and Return Result
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...) / penumPinAssignment pointer
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    bit bGetInfoResult = _FAIL;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    *penumPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            // Get Pin Assignment from TypeC 0
            *penumPinAssignment = ScalerTypeC0PdGetPinAssignment();
            bGetInfoResult = _SUCCESS;

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            // Get Pin Assignment from TypeC 1
            *penumPinAssignment = ScalerTypeC1PdGetPinAssignment();
            bGetInfoResult = _SUCCESS;

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
    return bGetInfoResult;
}

//--------------------------------------------------
// Description  : Get Embedded Port Ctrl Multi Function Change Process Done Result(Pin Assignment C <=> Pin Assignment D)
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...) / penumPinAssignment pointer
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCGetMultiFunctionChangeDone(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    bit bGetMultiFunctionChangeDone = _FALSE;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            // Get Multi Function Change Process Done Result from TypeC 0
            bGetMultiFunctionChangeDone = ScalerTypeC0PdGetMultiFunctionChangeDone();

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            // Get Multi Function Change Process Done Result from TypeC 1
            bGetMultiFunctionChangeDone = ScalerTypeC1PdGetMultiFunctionChangeDone();

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
    return bGetMultiFunctionChangeDone;
}

//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Cable Info For DPCD
// Input Value  : EnumTypeCPcbPort
// Output Value : StructTypeCCableInfoForDpcd
//--------------------------------------------------
StructTypeCCableInfoForDpcd ScalerTypeCGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            stTypeCCableInfoForDpcd = ScalerTypeC0PdGetCableInfoForDpcd();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            stTypeCCableInfoForDpcd = ScalerTypeC1PdGetCableInfoForDpcd();

            break;
#endif

        default:

            break;
    }

    return stTypeCCableInfoForDpcd;
}

//--------------------------------------------------
// Description  : System Set Unattach Reset Discharge Count
// Input Value  : enumInputPort
// Input Value  : ucDischargeCount
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetDischargeCount(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucDischargeCount)
{
    // Convert TypeC Port (PCB) to IC TypeC HW Index
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0CcSetDischargeCount(ucDischargeCount);

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1CcSetDischargeCount(ucDischargeCount);

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : System Set Event Request to PD/CC FW
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDSysEvent enumPdSysEvent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPdSysEvent = enumPdSysEvent;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetSystemEvent(enumPdSysEvent);

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetSystemEvent(enumPdSysEvent);

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Embedded Port Controller Event
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCPDPortCtrlEvent (_PD_PORT_CTRL_EVENT_POWER_OCP / _PD_PORT_CTRL_EVENT_POWER_OVP...)
//--------------------------------------------------
EnumTypeCPDPortCtrlEvent ScalerTypeCGetPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCPDPortCtrlEvent enumTypeCPortCtrlEvent = _PD_PORT_CTRL_EVENT_NONE;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            enumTypeCPortCtrlEvent = ScalerTypeC0PdGetPortCtrlEvent();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            enumTypeCPortCtrlEvent = ScalerTypeC1PdGetPortCtrlEvent();

            break;
#endif

        default:

            break;
    }

    return enumTypeCPortCtrlEvent;
}

//--------------------------------------------------
// Description  : Clear Embedded Port Controller Event
// Input Value  : enumTypeCPcbPort, enumPdPortCtrlEvent (_PD_PORT_CTRL_EVENT_POWER_OCP / _PD_PORT_CTRL_EVENT_POWER_OVP...)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCClrPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDPortCtrlEvent enumPdPortCtrlEvent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumPdPortCtrlEvent = enumPdPortCtrlEvent;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdClrPortCtrlEvent(enumPdPortCtrlEvent);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdClrPortCtrlEvent(enumPdPortCtrlEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Control Type-C Power Off/On
// Input Value  : enumTypeCPcbPort, enumPowerControlStatus
// Output Value : Control Power Result (_SUCCESS / _FAIL)
//--------------------------------------------------
bit ScalerTypeCPowerControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerControlStatus enumPowerControlStatus)
{
    EnumTypeCAttachStatus enumAttachStatus = _TYPE_C_UNATTACH;
    BYTE ucIndex = 0;
    bit bControlResult = _FAIL;
    enumTypeCPcbPort = enumTypeCPcbPort;

    if(enumPowerControlStatus == _TYPE_C_POWER_OFF)
    {
        // Judge All Embbeded TypeC Ports CC Attach Status
        for(ucIndex = 0; ucIndex < (_EMB_TYPE_C_PORT_VALID - 1); ++ucIndex)
        {
            enumAttachStatus |= ScalerTypeCGetCcAttach(g_penumTypeCEmbeddedPort[ucIndex]);
        }

        if(enumAttachStatus == _TYPE_C_ATTACH)
        {
            // Set All Embbeded TypeC Ports Disconnect Before Power Cut
            for(ucIndex = 0; ucIndex < (_EMB_TYPE_C_PORT_VALID - 1); ++ucIndex)
            {
                ScalerTypeCCcFunctionControl(g_penumTypeCEmbeddedPort[ucIndex], _TYPE_C_CC_FUNCTION_DISABLE);
            }
        }
        else
        {
            // Power Cut TypeC
#if(_HW_TYPE_C_POWER_DOMAIN_GEN_TYPE == _TYPE_C_POWER_DOMAIN_GEN_1)
            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_TYPE_C_TOTAL, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
#endif
            bControlResult = _SUCCESS;
        }
    }
    else if(enumPowerControlStatus == _TYPE_C_POWER_ON)
    {
        // Power On TypeC
#if(_HW_TYPE_C_POWER_DOMAIN_GEN_TYPE == _TYPE_C_POWER_DOMAIN_GEN_1)
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_TYPE_C_TOTAL, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
#endif
        bControlResult = _SUCCESS;
    }

    return bControlResult;
}

//--------------------------------------------------
// Description  : Control TypeC CC Function
// Input Value  : enumInputPort, enumCcFunction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumCcFunction = enumCcFunction;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0CcFunctionControl(enumCcFunction);

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1CcFunctionControl(enumCcFunction);

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Type-C Function Support Option to PD/CC FW
// Input Value  : enumTypeCPcbPort, enumFunctionSupport
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCFunctionSupport enumFunctionSupport)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumFunctionSupport = enumFunctionSupport;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0CcSetFunctionSupport(enumFunctionSupport);
            ScalerTypeC0PdSetFunctionSupport(enumFunctionSupport);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1CcSetFunctionSupport(enumFunctionSupport);
            ScalerTypeC1PdSetFunctionSupport(enumFunctionSupport);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Type-C Operation Mode to CC FW
// Input Value  : enumTypeCPcbPort, enumOperationMode
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetOperationMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCOperationMode enumOperationMode)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumOperationMode = enumOperationMode;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0CcSetOperationMode(enumOperationMode);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1CcSetOperationMode(enumOperationMode);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Error Recovery Flag to Trigger EMB Type C Reconnect
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCReconnect(EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bReconnectResult = _FAIL;

    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            SET_TYPE_C_0_CC_ERROR_RECOVERY();
            bReconnectResult = _SUCCESS;

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            SET_TYPE_C_1_CC_ERROR_RECOVERY();
            bReconnectResult = _SUCCESS;

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
    return bReconnectResult;
}

//--------------------------------------------------
// Description  : Ask Embedded PD to Wait for DP Config Update
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCWaitDpConfigUpdate(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdWaitDpConfig();

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdWaitDpConfig();

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Configuration Update
// Input Value  : enumInputPort
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCUpdateConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    bit bGetInfoResult = _FAIL;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumMultiFunc = enumMultiFunc;
    enumPinAssignmentCap = enumPinAssignmentCap;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetPinAssignmentCapability(enumPinAssignmentCap);
            ScalerTypeC0PdSetMultiFunctionBit(enumMultiFunc);
            bGetInfoResult = _SUCCESS;

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetPinAssignmentCapability(enumPinAssignmentCap);
            ScalerTypeC1PdSetMultiFunctionBit(enumMultiFunc);
            bGetInfoResult = _SUCCESS;

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }
    return bGetInfoResult;
}

//--------------------------------------------------
// Description  : Kernel Set Source/Sink Capability By Kernel
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
//                enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdoByKernel(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumPowerRole = enumPowerRole;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetPdoByKernel(enumPowerRole);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetPdoByKernel(enumPowerRole);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Source Max Power to PD FW
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    usMaxPower = usMaxPower;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetMaxPower(usMaxPower);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetMaxPower(usMaxPower);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Sink Information to PD FW
// Input Value  : enumTypeCPcbPort, stTypeCSnkInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo stTypeCSnkInfo)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    stTypeCSnkInfo = stTypeCSnkInfo;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetSnkInfo(stTypeCSnkInfo);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetSnkInfo(stTypeCSnkInfo);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Type-C Status Event to PD FW
// Input Value  : enumTypeCPcbPort, stTypeCStatusEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent stTypeCStatusEvent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    stTypeCStatusEvent = stTypeCStatusEvent;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetStatusEvent(stTypeCStatusEvent);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetStatusEvent(stTypeCStatusEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Type-C Alert Event to PD FW
// Input Value  : enumTypeCPcbPort, stTypeCAlertEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent stTypeCAlertEvent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    stTypeCAlertEvent = stTypeCAlertEvent;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetAlertEvent(stTypeCAlertEvent);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetAlertEvent(stTypeCAlertEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Number of SPR/EPR PDOs to PD FW
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucSPRPdoCnt, ucEPRPdoCnt
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucSPRPdoCnt, BYTE ucEPRPdoCnt)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumPowerRole = enumPowerRole;
    ucSPRPdoCnt = ucSPRPdoCnt;
    ucEPRPdoCnt = ucEPRPdoCnt;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetSPRPdoCnt(enumPowerRole, ucSPRPdoCnt);

#if(_EMB_TYPE_C_0_PD3_1_EPR_SUPPORT == _ON)
            ScalerTypeC0PdSetEPRPdoCnt(enumPowerRole, ucEPRPdoCnt);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetSPRPdoCnt(enumPowerRole, ucSPRPdoCnt);

#if(_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON)
            ScalerTypeC1PdSetEPRPdoCnt(enumPowerRole, ucEPRPdoCnt);
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Number of SPR/EPR PDOs in PD FW (May Be User/Kernel-Defined)
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), *pucSPRPdoCnt, *pucEPRPdoCnt
// Output Value : None
//--------------------------------------------------
void ScalerTypeCGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCnt, BYTE *pucEPRPdoCnt)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumPowerRole = enumPowerRole;
    *pucSPRPdoCnt = 0;
    *pucEPRPdoCnt = 0;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            *pucSPRPdoCnt = ScalerTypeC0PdGetSPRPdoCnt(enumPowerRole);

#if(_EMB_TYPE_C_0_PD3_1_EPR_SUPPORT == _ON)
            *pucEPRPdoCnt = ScalerTypeC0PdGetEPRPdoCnt(enumPowerRole);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            *pucSPRPdoCnt = ScalerTypeC1PdGetSPRPdoCnt(enumPowerRole);

#if(_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON)
            *pucEPRPdoCnt = ScalerTypeC1PdGetEPRPdoCnt(enumPowerRole);
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Src/Snk PDO Info in PD FW
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCUserPDO stTypeCPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            stTypeCPdo = ScalerTypeC0PdGetPdo(enumPowerRole, ucPdoIndex);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            stTypeCPdo = ScalerTypeC1PdGetPdo(enumPowerRole, ucPdoIndex);

            break;
#endif

        default:

            break;
    }

    return stTypeCPdo;
}

//--------------------------------------------------
// Description  : Get Number of PDOs from Port Partner
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE ScalerTypeCGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    BYTE ucPdoCnt = 0;
    enumPowerRole = enumPowerRole;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ucPdoCnt = ScalerTypeC0PdGetPartnerPdoCnt(enumPowerRole);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ucPdoCnt = ScalerTypeC1PdGetPartnerPdoCnt(enumPowerRole);

            break;
#endif

        default:

            break;
    }

    return ucPdoCnt;
}

//--------------------------------------------------
// Description  : Get Src/Snk PDO Info from Port Partner
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            stTypeCPartnerPdo = ScalerTypeC0PdGetPartnerPdo(enumPowerRole, ucPdoIndex);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            stTypeCPartnerPdo = ScalerTypeC1PdGetPartnerPdo(enumPowerRole, ucPdoIndex);

            break;
#endif

        default:

            break;
    }

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Get Status Info from Port Partner
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCStatusEvent
//--------------------------------------------------
StructTypeCStatusEvent ScalerTypeCGetPartnerStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCStatusEvent stTypeCPartnerStatusEvent = {0x00, 0x00};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            stTypeCPartnerStatusEvent = ScalerTypeC0PdGetPartnerStatusInfo();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            stTypeCPartnerStatusEvent = ScalerTypeC1PdGetPartnerStatusInfo();

            break;
#endif

        default:

            break;
    }

    return stTypeCPartnerStatusEvent;
}

//--------------------------------------------------
// Description  : Get Alert Info from Port Partner
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCAlertEvent
//--------------------------------------------------
StructTypeCAlertEvent ScalerTypeCGetPartnerAlertInfo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCAlertEvent stTypeCPartnerAlertEvent = {_TYPE_C_TYPE_OF_ALERT_NONE, _TYPE_C_BAT_NONE, _TYPE_C_EXT_ALERT_EVENT_NONE};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            stTypeCPartnerAlertEvent = ScalerTypeC0PdGetPartnerAlertInfo();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            stTypeCPartnerAlertEvent = ScalerTypeC1PdGetPartnerAlertInfo();

            break;
#endif

        default:

            break;
    }

    return stTypeCPartnerAlertEvent;
}

//--------------------------------------------------
// Description  : Get Embedded Port Ctrl Data Role
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCDataRole (_TYPE_C_DATA_ROLE_NONE / _TYPE_C_UFP_U / _TYPE_C_DFP_U)
//--------------------------------------------------
EnumTypeCDataRole ScalerTypeCGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCDataRole enumTypeCDataRole = _TYPE_C_DATA_ROLE_NONE;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            enumTypeCDataRole = ScalerTypeC0PdGetDataRole();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            enumTypeCDataRole = ScalerTypeC1PdGetDataRole();

            break;
#endif

        default:

            break;
    }

    return enumTypeCDataRole;
}

//--------------------------------------------------
// Description  : Get Embedded Port Ctrl Power Role
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_ROLE_NONE / _TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC)
//--------------------------------------------------
EnumTypeCPowerRole ScalerTypeCGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCPowerRole enumTypeCPowerRole = _TYPE_C_POWER_ROLE_NONE;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            enumTypeCPowerRole = ScalerTypeC0PdGetPowerRole();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            enumTypeCPowerRole = ScalerTypeC1PdGetPowerRole();

            break;
#endif

        default:

            break;
    }

    return enumTypeCPowerRole;
}

//--------------------------------------------------
// Description  : Get Embedded Port Ctrl Explicit Contract
// Input Value  : enumTypeCPcbPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCGetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bGetExplicitContract = _FALSE;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            bGetExplicitContract = ScalerTypeC0PdGetExplicitContract();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            bGetExplicitContract = ScalerTypeC1PdGetExplicitContract();

            break;
#endif

        default:

            break;
    }

    return bGetExplicitContract;
}

//--------------------------------------------------
// Description  : Get PDO Status
// Input Value  : enumTypeCPcbPort, *pusVoltage (Unit: 10mV), *pusCurrent (Unit: 10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdGetPdoStatus(enumTypeCPcbPort, pusVoltage, pusCurrent);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdGetPdoStatus(enumTypeCPcbPort, pusVoltage, pusCurrent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Current Source PDO that Sink Request
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            stTypeCSrcPdo = ScalerTypeC0PdGetRequestedSrcPdo(enumTypeCPcbPort);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            stTypeCSrcPdo = ScalerTypeC1PdGetRequestedSrcPdo(enumTypeCPcbPort);

            break;
#endif

        default:

            break;
    }

    return stTypeCSrcPdo;
}

//--------------------------------------------------
// Description  : Set User-Defined Fix Supply PDOs to PD FW
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, usVoltage(100mV), usMaxCur(10mA), enumPeakCur
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetFixPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumTypeCPDPeakCurType enumPeakCur)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;
    usVoltage = usVoltage;
    usMaxCur = usMaxCur;
    enumPeakCur = enumPeakCur;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetFixPdo(enumPowerRole, ucPdoIndex, usVoltage, usMaxCur, enumPeakCur);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetFixPdo(enumPowerRole, ucPdoIndex, usVoltage, usMaxCur, enumPeakCur);

            break;
#endif

        default:

            break;
    }
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set User-Defined PPS PDOs to PD FW
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, usMinVol(100mV), usMaxVol(100mV), ucMaxCur(50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPpsPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, BYTE ucMaxCur)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;
    usMinVol = usMinVol;
    usMaxVol = usMaxVol;
    ucMaxCur = ucMaxCur;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_PD3_PPS_SUPPORT == _ON)
            ScalerTypeC0PdSetArgumentedPdo(enumPowerRole, ucPdoIndex, usMinVol, usMaxVol, (WORD)ucMaxCur);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            ScalerTypeC1PdSetArgumentedPdo(enumPowerRole, ucPdoIndex, usMinVol, usMaxVol, (WORD)ucMaxCur);
#endif

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Set User-Defined AVS PDOs to PD FW
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, usMinVol(100mV), usMaxVol(100mV), enumPeakCur
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetAvsPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, EnumTypeCPDPeakCurType enumPeakCur)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;
    usMinVol = usMinVol;
    usMaxVol = usMaxVol;
    enumPeakCur = enumPeakCur;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetAdjustablePdo(enumPowerRole, ucPdoIndex, usMinVol, usMaxVol, enumPeakCur);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetAdjustablePdo(enumPowerRole, ucPdoIndex, usMinVol, usMaxVol, enumPeakCur);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Initial Request RDO to PD FW
// Input Value  : enumTypeCPcbPort, StructTypeCUserInitRDO(Initial Request Option, Target Voltage)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetInitRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO stTypeCUserInitRdo)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    stTypeCUserInitRdo = stTypeCUserInitRdo;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetInitRdo(stTypeCUserInitRdo);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetInitRdo(stTypeCUserInitRdo);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Request RDO to PD FW
// Input Value  : enumTypeCPcbPort, StructTypeCUserRDO(Object Position, ReqInfo1, ReqInfo2, Cap Mismatch)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    stTypeCUserRdo = stTypeCUserRdo;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetRdo(stTypeCUserRdo);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetRdo(stTypeCUserRdo);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Unconstrained Power to PD FW
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCUnconstrainPowerExist enumTypeCUnconstrainPowerExist)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    enumTypeCUnconstrainPowerExist = enumTypeCUnconstrainPowerExist;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetUnconstrainedPow(enumTypeCUnconstrainPowerExist);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetUnconstrainedPow(enumTypeCUnconstrainPowerExist);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Set Vbus Protect Info
// Input Value  : enumTypeCPcbPort, ucPdoIndex, StructTypeCUserProtectInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetVbusProtectInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCVbusProtectInfo stTypeCVbusProtectInfo)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    ucPdoIndex = ucPdoIndex;
    stTypeCVbusProtectInfo = stTypeCVbusProtectInfo;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdSetVbusProtectInfo(ucPdoIndex, stTypeCVbusProtectInfo);

#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
            // PMIC Related Vbus Portect Info
            ScalerTypeC0PmicSetVbusProtectInfo(stTypeCVbusProtectInfo);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdSetVbusProtectInfo(ucPdoIndex, stTypeCVbusProtectInfo);

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            // PMIC Related Vbus Portect Info
            ScalerTypeC1PmicSetVbusProtectInfo(stTypeCVbusProtectInfo);
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get TypeC Cable PD Capability
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : TypeC Cable PD Capability (_TYPE_C_CABLE_PD_CAP_UNCONFIRMED / _TYPE_C_CABLE_NON_PD_CAPABLE / _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED)
//--------------------------------------------------
EnumTypeCCablePdCapability ScalerTypeCGetCablePdCapability(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCCablePdCapability enumTypeCCablePdCap = _TYPE_C_CABLE_PD_CAP_UNCONFIRMED;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            enumTypeCCablePdCap = ScalerTypeC0PdGetCablePdCapability();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            enumTypeCCablePdCap = ScalerTypeC1PdGetCablePdCapability();

            break;
#endif

        default:

            break;
    }

    return enumTypeCCablePdCap;
}

//--------------------------------------------------
// Description  : Get TypeC Product Type when in UFP Data Role
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : TypeC Product Type UFP (_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_UFP_PRODUCT_TYPE_HUB / _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
//--------------------------------------------------
EnumTypeCUFPProductType ScalerTypeCGetUFPProductType(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCUFPProductType enumTypeCUFPProductType = _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            enumTypeCUFPProductType = ScalerTypeC0PdGetUFPProductType();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            enumTypeCUFPProductType = ScalerTypeC1PdGetUFPProductType();

            break;
#endif

        default:

            break;
    }

    return enumTypeCUFPProductType;
}

//--------------------------------------------------
// Description  : Get TypeC Product Type when in DFP Data Role
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : TypeC Product Type DFP (_TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_DFP_PRODUCT_TYPE_HUB / _TYPE_C_DFP_PRODUCT_TYPE_HOST / _TYPE_C_DFP_PRODUCT_TYPE_BRICK)
//--------------------------------------------------
EnumTypeCDFPProductType ScalerTypeCGetDFPProductType(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCDFPProductType enumTypeCDFPProductType = _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            enumTypeCDFPProductType = ScalerTypeC0PdGetDFPProductType();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            enumTypeCDFPProductType = ScalerTypeC1PdGetDFPProductType();

            break;
#endif

        default:

            break;
    }

    return enumTypeCDFPProductType;
}

//--------------------------------------------------
// Description  : Get TypeC Cable Max Current
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : TypeC Cable Max Current (Unit: 10mA)
//--------------------------------------------------
WORD ScalerTypeCGetCableMaxCurrent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    WORD usCableMaxCurrent = 0;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            usCableMaxCurrent = ScalerTypeC0PdGetCableMaxCurrent();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            usCableMaxCurrent = ScalerTypeC1PdGetCableMaxCurrent();

            break;
#endif

        default:

            break;
    }

    return usCableMaxCurrent;
}

//--------------------------------------------------
// Description  : Type C Power Switch Process
// Input Value  : enumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction)
{
    enumPowerAction = enumPowerAction;

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    ScalerTypeC0CcPowerSwitch(enumPowerAction);
    ScalerTypeC0PdPowerSwitch(enumPowerAction);
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    ScalerTypeC1CcPowerSwitch(enumPowerAction);
    ScalerTypeC1PdPowerSwitch(enumPowerAction);
#endif
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue
// Input Value  : enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., HPD Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPdPushHpd(EnumInputPort enumInputPort, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort));
    enumHpdType = enumHpdType;
    usHpdSpaceTime = usHpdSpaceTime;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ScalerTypeC0PdPushHpd(enumHpdType, usHpdSpaceTime);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ScalerTypeC1PdPushHpd(enumHpdType, usHpdSpaceTime);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Force Sending HPD IRQ for DP CTS
// Input Value  : enumInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPdDpCTSForceHpdIrq(EnumInputPort enumInputPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort));

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if((_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON) && (_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX))
            ScalerTypeC0PdDpCTSForceHpdIrq();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if((_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) && (_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX))
            ScalerTypeC1PdDpCTSForceHpdIrq();
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Kernel Get Rx HPD Queue Info
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT..., HPD Queue Index
// Output Value : EnumTypeCPDHpdType : PD HPD Status (_PD_HPD_LOW / _PD_HPD_HIGH)
//--------------------------------------------------
EnumTypeCPDHpdType ScalerTypeCRxGetHPDQueue(EnumInputPort enumInputPort, BYTE ucIndex)
{
    EnumTypeCPDHpdType enumHpdType = _PD_HPD_NONE;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort));
    ucIndex = ucIndex;

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            enumHpdType = ScalerTypeC0PdRxGetHPDQueue(ucIndex);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            enumHpdType = ScalerTypeC1PdRxGetHPDQueue(ucIndex);

            break;
#endif

        default:

            break;
    }

    return enumHpdType;
}

//--------------------------------------------------
// Description  : Kernel Get Rx HPD Queue Read Pointer
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : HPD Queue Read Pointer
//--------------------------------------------------
BYTE ScalerTypeCRxGetHPDQueueReadPointer(EnumInputPort enumInputPort)
{
    BYTE ucQueuePointer = 0x00;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort));

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            ucQueuePointer = ScalerTypeC0PdRxGetHPDQueReadPointer();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            ucQueuePointer = ScalerTypeC1PdRxGetHPDQueReadPointer();

            break;
#endif

        default:

            break;
    }

    return ucQueuePointer;
}

//--------------------------------------------------
// Description  : Get PD HPD Status
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : PD HPD Status
//--------------------------------------------------
bit ScalerTypeCRxGetHPDStatus(EnumInputPort enumInputPort)
{
    bit bHPDStatus = _LOW;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort));

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            bHPDStatus = ScalerTypeC0PdRxGetHPDStatus();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            bHPDStatus = ScalerTypeC1PdRxGetHPDStatus();

            break;
#endif

        default:

            break;
    }

    return bHPDStatus;
}

//--------------------------------------------------
// Description  : Kernel Get Tx HPD Queue Info
// Input Value  : enumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT...
// Output Value : StructTypeCTxHpdQueue
//--------------------------------------------------
StructTypeCTxHpdQueue ScalerTypeCTxGetHPDQueue(EnumOutputPort enumOutputPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(ScalerTypeCPxConvertToPcbPort(enumOutputPort));
    StructTypeCTxHpdQueue stTxHpdQueue = {0};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            stTxHpdQueue = ScalerTypeC0PdTxGetHPDQueue();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            stTxHpdQueue = ScalerTypeC1PdTxGetHPDQueue();

            break;
#endif

        default:

            break;
    }

    return stTxHpdQueue;
}

//--------------------------------------------------
// Description  : Get TypeC PD DP Status Info
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCDpStatusInfo (enumPartnerDpConnectStatus / b1PartnerMultiFunctionBit...)
//--------------------------------------------------
StructTypeCDpStatusInfo ScalerTypeCGetDpStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)
    StructTypeCDpStatusInfo stDpStatusInfo = {_PD_DP_CONNECT_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, _PD_HPD_NONE};
#else
    StructTypeCDpStatusInfo stDpStatusInfo = {_PD_DP_CONNECT_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, _PD_HPD_NONE, 0x00};
#endif
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            stDpStatusInfo = ScalerTypeC0PdGetDpStatusInfo();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            stDpStatusInfo = ScalerTypeC1PdGetDpStatusInfo();

            break;
#endif

        default:

            break;
    }

    return stDpStatusInfo;
}

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Lenovo Alt Mode Ready Status
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus ScalerTypeCGetLenovoAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCLenovoAltModeStatus enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumLenovoAltModeStatus = (ScalerTypeC0PdGetLenovoAltModeReady() == _TRUE ? _TYPE_C_LENOVO_ALT_MODE_READY : _TYPE_C_LENOVO_ALT_MODE_NOT_READY);
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumLenovoAltModeStatus = (ScalerTypeC1PdGetLenovoAltModeReady() == _TRUE ? _TYPE_C_LENOVO_ALT_MODE_READY : _TYPE_C_LENOVO_ALT_MODE_NOT_READY);
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }

    return enumLenovoAltModeStatus;
}

//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Port Partner Lenovo Device Type
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType ScalerTypeCGetLenovoDeviceType(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCLenovoDeviceType enumLenovoDeviceType = _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumLenovoDeviceType = ScalerTypeC0PdGetLenovoDeviceType();
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumLenovoDeviceType = ScalerTypeC1PdGetLenovoDeviceType();
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }

    return enumLenovoDeviceType;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent ScalerTypeCGetLenovoSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            stLenovoSysEvent = ScalerTypeC0PdGetLenovoSystemEvent();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            stLenovoSysEvent = ScalerTypeC1PdGetLenovoSystemEvent();
#endif

            break;
#endif

        default:

            break;
    }

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC0PdSetLenovoDockingEvent(stLenovoDockEvent);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC1PdSetLenovoDockingEvent(stLenovoDockEvent);
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : Docking Event Check Busy Result (_TYPE_C_LENOVO_DOCK_EVENT_BUSY / _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCLenovoCheckBusyResult ScalerTypeCCheckLenovoDockingEventBusy(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCLenovoCheckBusyResult enumCheckBusyResult = _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumCheckBusyResult = ScalerTypeC0PdCheckLenovoDockingEventBusy();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumCheckBusyResult = ScalerTypeC1PdCheckLenovoDockingEventBusy();
#endif

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Acer Alt Mode Ready Status
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : Acer Alt Mode Ready Status (_TYPE_C_ACER_ALT_MODE_READY / _TYPE_C_ACER_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAcerAltModeStatus ScalerTypeCGetAcerAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAcerAltModeStatus enumAcerAltModeStatus = _TYPE_C_ACER_ALT_MODE_NOT_READY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumAcerAltModeStatus = (ScalerTypeC0PdGetAcerAltModeReady() == _TRUE ? _TYPE_C_ACER_ALT_MODE_READY : _TYPE_C_ACER_ALT_MODE_NOT_READY);
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumAcerAltModeStatus = (ScalerTypeC1PdGetAcerAltModeReady() == _TRUE ? _TYPE_C_ACER_ALT_MODE_READY : _TYPE_C_ACER_ALT_MODE_NOT_READY);
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }

    return enumAcerAltModeStatus;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Get System Event
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : StructTypeCAcerSysEvent
//--------------------------------------------------
StructTypeCAcerSysEvent ScalerTypeCGetAcerSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCAcerSysEvent stAcerSysEvent = {_TYPE_C_ACER_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            stAcerSysEvent = ScalerTypeC0PdGetAcerSystemEvent();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            stAcerSysEvent = ScalerTypeC1PdGetAcerSystemEvent();
#endif

            break;
#endif

        default:

            break;
    }

    return stAcerSysEvent;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Set User Event
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), stAcerUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetAcerUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerUserEvent stAcerUserEvent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC0PdSetAcerUserEvent(stAcerUserEvent);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC1PdSetAcerUserEvent(stAcerUserEvent);
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Check if Last User Event has been Sent
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : User Event Busy Status (_TYPE_C_ACER_USER_EVENT_BUSY / _TYPE_C_ACER_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCAcerBusyStatus ScalerTypeCCheckAcerUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAcerBusyStatus enumCheckBusyResult = _TYPE_C_ACER_USER_EVENT_NOT_BUSY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumCheckBusyResult = ScalerTypeC0PdCheckAcerUserEventBusy();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumCheckBusyResult = ScalerTypeC1PdCheckAcerUserEventBusy();
#endif

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Hp Alt Mode Ready Status
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : Hp Alt Mode Ready Status (_TYPE_C_HP_ALT_MODE_READY / _TYPE_C_HP_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCHpAltModeStatus ScalerTypeCGetHpAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCHpAltModeStatus enumHpAltModeStatus = _TYPE_C_HP_ALT_MODE_NOT_READY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumHpAltModeStatus = (ScalerTypeC0PdGetHpAltModeReady() == _TRUE ? _TYPE_C_HP_ALT_MODE_READY : _TYPE_C_HP_ALT_MODE_NOT_READY);
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumHpAltModeStatus = (ScalerTypeC1PdGetHpAltModeReady() == _TRUE ? _TYPE_C_HP_ALT_MODE_READY : _TYPE_C_HP_ALT_MODE_NOT_READY);
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }

    return enumHpAltModeStatus;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Get System Event
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : StructTypeCHpSysEvent
//--------------------------------------------------
StructTypeCHpSysEvent ScalerTypeCGetHpSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            stHpSysEvent = ScalerTypeC0PdGetHpSystemEvent();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            stHpSysEvent = ScalerTypeC1PdGetHpSystemEvent();
#endif

            break;
#endif

        default:

            break;
    }

    return stHpSysEvent;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Set User Event
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), stHpUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetHpUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpUserEvent stHpUserEvent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC0PdSetHpUserEvent(stHpUserEvent);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC1PdSetHpUserEvent(stHpUserEvent);
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Check if Last User Event has been Sent
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : User Event Busy Status (_TYPE_C_HP_USER_EVENT_BUSY / _TYPE_C_HP_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCHpBusyStatus ScalerTypeCCheckHpUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCHpBusyStatus enumCheckBusyResult = _TYPE_C_HP_USER_EVENT_NOT_BUSY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumCheckBusyResult = ScalerTypeC0PdCheckHpUserEventBusy();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumCheckBusyResult = ScalerTypeC1PdCheckHpUserEventBusy();
#endif

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Dell Alt Mode Ready Status
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...)
// Output Value : Dell Alt Mode Ready Status (_TYPE_C_DELL_ALT_MODE_READY / _TYPE_C_DELL_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCDellAltModeStatus ScalerTypeCGetDellAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCDellAltModeStatus enumDellAltModeStatus = _TYPE_C_DELL_ALT_MODE_NOT_READY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumDellAltModeStatus = (ScalerTypeC0PdGetDellAltModeReady() == _TRUE ? _TYPE_C_DELL_ALT_MODE_READY : _TYPE_C_DELL_ALT_MODE_NOT_READY);
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumDellAltModeStatus = (ScalerTypeC1PdGetDellAltModeReady() == _TRUE ? _TYPE_C_DELL_ALT_MODE_READY : _TYPE_C_DELL_ALT_MODE_NOT_READY);
#endif

            break;
#endif  // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

        default:

            break;
    }

    return enumDellAltModeStatus;
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Get System Event
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : StructTypeCDellSysEvent
//--------------------------------------------------
StructTypeCDellSysEvent ScalerTypeCGetDellSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);
    StructTypeCDellSysEvent stDellSysEvent = {_TYPE_C_DELL_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            stDellSysEvent = ScalerTypeC0PdGetDellSystemEvent();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            stDellSysEvent = ScalerTypeC1PdGetDellSystemEvent();
#endif

            break;
#endif

        default:

            break;
    }

    return stDellSysEvent;
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Set User Event
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), stDellUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetDellUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellUserEvent stDellUserEvent)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC0PdSetDellUserEvent(stDellUserEvent);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC1PdSetDellUserEvent(stDellUserEvent);
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Set Initial Complete Status
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), enumDellInitCompleteStatus (_TYPE_C_DELL_INIT_COMPLETE / _TYPE_C_DELL_INIT_NOT_COMPLETE)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetDellAltModeInitComplete(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC0PdSetDellAltModeInitComplete(enumDellInitCompleteStatus);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC1PdSetDellAltModeInitComplete(enumDellInitCompleteStatus);
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Check if Last User Event has been Sent
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : User Event Busy Status (_TYPE_C_DELL_USER_EVENT_BUSY / _TYPE_C_DELL_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCDellBusyStatus ScalerTypeCCheckDellUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCDellBusyStatus enumCheckBusyResult = _TYPE_C_DELL_USER_EVENT_NOT_BUSY;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumCheckBusyResult = ScalerTypeC0PdCheckDellUserEventBusy();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumCheckBusyResult = ScalerTypeC1PdCheckDellUserEventBusy();
#endif

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}

//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Enter Dell Alt Mode Time Out Result
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...),
// Output Value : Enter Dell Alt Mode Time Out Result (_TYPE_C_ENTER_DELL_ALT_MODE_TIMEOUT/ _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT)
//--------------------------------------------------
EnumTypeCEnterDellAltModeTimeOut ScalerTypeCGetEnterDellAltModeTimeOut(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCEnterDellAltModeTimeOut enumEnterDellAMTimeOutResult = _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            enumEnterDellAMTimeOutResult = ScalerTypeC0PdGetEnterDellAltModeTimeOut();
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            enumEnterDellAMTimeOutResult = ScalerTypeC1PdGetEnterDellAltModeTimeOut();
#endif

            break;
#endif

        default:

            break;
    }

    return enumEnterDellAMTimeOutResult;
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type C Alt Mode Related Info for Billboard Display
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), Pointer of Billboard Info
// Output Value : None
//--------------------------------------------------
void ScalerTypeCGetAltModeBillboardInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE *pucBillboardAltModeInfo)
{
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC0PdGetAltModeBillboardInfo(pucBillboardAltModeInfo);
#endif

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeC1PdGetAltModeBillboardInfo(pucBillboardAltModeInfo);
#endif

            break;
#endif

        default:

            break;
    }
}
#endif

#if(_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return Port Controller Power role Swap Processing to SysUsb
// Input Value  : EnumTypeCPcbPort
// Output Value : PR_Swap Processing (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeCGetPdPRSwapProcessing(EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bPrsProcessing = _FALSE;

    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            bPrsProcessing = ScalerTypeC0PdGetPRSwapProcesing();

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            bPrsProcessing = ScalerTypeC1PdGetPRSwapProcesing();

            break;
#endif

        default:
            break;
    }

    return bPrsProcessing;
}

//--------------------------------------------------
// Description  : Return Port Controller VBus Status to SysUsb
// Input Value  : EnumTypeCPcbPort
// Output Value : VBus Status (_ENABLE / _DISABLE)
//--------------------------------------------------
bit ScalerTypeCGetVbusStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bVbusStatus = _DISABLE;
    EnumTypeCEmbeddedList enumEmbTypeCIndex = ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort);

    switch(enumEmbTypeCIndex)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_0:

            if(ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) > 150)
            {
                bVbusStatus = _ENABLE;
            }
            else
            {
                bVbusStatus = _DISABLE;
            }

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _EMB_TYPE_C_1:

            if(ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) > 150)
            {
                bVbusStatus = _ENABLE;
            }
            else
            {
                bVbusStatus = _DISABLE;
            }

            break;
#endif

        default:
            break;
    }

    return bVbusStatus;
}
#endif  // End of #if(_USB_HUB_SUPPORT == _ON)

#endif // End of #if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TypeC GPIO Mode Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCGpioModeInitialSetting(void)
{
#if(_HW_EMB_TYPE_C_0_SUPPORT == _ON)
    // Load Trimming Value From E-fuse/Experienced Trimmed Value, and Set up AIF Registers
    ScalerTypeC0CcLoadTrimming();

    // TypeC0 GPIO Mode Initial Setting
    ScalerTypeC0CcGpioModeInitialSetting();
#endif

#if(_HW_EMB_TYPE_C_1_SUPPORT == _ON)
    // Set CC1/2 Vref 2.6V to Experienced Trimmed Value
    ScalerTypeC1CcLoadTrimming();

    // TypeC1 GPIO Mode Initial Setting
    ScalerTypeC1CcGpioModeInitialSetting();
#endif
}

//--------------------------------------------------
// Description  : Return CC Pin Status to SysUsb
// Input Value  : enumEmbTypeCIndex (_EMB_TYPE_C_0, _EMB_TYPE_C_1), enumTypeCChannel (_TYPE_C_CC1, _TYPE_C_CC2)
// Output Value : EnumTypeCCcDetectStatus : _TYPE_C_CC_DETECT_HIGH (if CC Voltage >= 2.6V) / _TYPE_C_CC_DETECT_LOW (if CC Voltage < 2.6V)
//--------------------------------------------------
EnumTypeCCcDetectStatus ScalerTypeCGetCcPinStatus(EnumTypeCEmbeddedList enumEmbTypeCIndex, EnumTypeCChannel enumTypeCChannel)
{
    EnumTypeCCcDetectStatus enumTypeCCcDetectStatus = _TYPE_C_CC_DETECT_LOW;
    enumTypeCChannel = enumTypeCChannel;

    switch(enumEmbTypeCIndex)
    {
#if(_HW_EMB_TYPE_C_0_SUPPORT == _ON)
        case _EMB_TYPE_C_0:

            enumTypeCCcDetectStatus = ScalerTypeC0CcGetCcPinStatus(enumTypeCChannel);

            break;
#endif

#if(_HW_EMB_TYPE_C_1_SUPPORT == _ON)
        case _EMB_TYPE_C_1:

            enumTypeCCcDetectStatus = ScalerTypeC1CcGetCcPinStatus(enumTypeCChannel);

            break;
#endif

        default:
            break;
    }

    return enumTypeCCcDetectStatus;
}
#endif  // End of #if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
