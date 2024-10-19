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
// ID Code      : ScalerDpRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpRx/ScalerDpRx.h"



//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
EnumInputPort g_enumDpRxBasePortBackup = _NO_INPUT_PORT;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxIntHandler_EXINT0(void)
{
    if(GET_DP_RX_GLOBAL_INT_FLAG() == _TRUE)
    {
        ScalerDpRxHighPriorityIntHandler_EXINT0();

        ScalerDpRxLowPriorityIntHandler_EXINT0();
    }

#if(_DP_MST_SUPPORT == _ON)
    if(GET_DP_RX_GLOBAL_AUX_MSG_INT_FLAG() == _TRUE)
    {
        ScalerDpRxAuxMsgIntHandler_EXINT0();
    }
#endif
}

//--------------------------------------------------
// Description  : DP High Priority Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxHighPriorityIntHandler_EXINT0(void)
{
    if(GET_DP_RX_GLOBAL_HIGH_PRIORITY_INT_FLAG() == _TRUE)
    {
        ScalerDpAuxRxHighPriorityIntHandler_EXINT0();

        ScalerDpMacRxHighPriorityIntHandler_EXINT0();
    }
}

//--------------------------------------------------
// Description  : DP Low Priority Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxLowPriorityIntHandler_EXINT0(void)
{
    if(GET_DP_RX_GLOBAL_LOW_PRIORITY_INT_FLAG() == _TRUE)
    {
        ScalerDpAuxRxLowPriorityIntHandler_EXINT0();

        ScalerDpMacRxLowPriorityIntHandler_EXINT0();
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx Aux Msg Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxAuxMsgIntHandler_EXINT0(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    if(GET_DP_AUX_RX0_MSG_IRQ_FLAG() == _TRUE)
    {
        EnumInputPort enumInputPortRx0 = ScalerDpAuxRxRxDxMapping_EXINT0(_RX0);

        ScalerDpMstRxIntHandle_EXINT0(enumInputPortRx0);
    }
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    if(GET_DP_AUX_RX1_MSG_IRQ_FLAG() == _TRUE)
    {
        EnumInputPort enumInputPortRx1 = ScalerDpAuxRxRxDxMapping_EXINT0(_RX1);

        ScalerDpMstRxIntHandle_EXINT0(enumInputPortRx1);
    }
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    if(GET_DP_AUX_RX2_MSG_IRQ_FLAG() == _TRUE)
    {
        EnumInputPort enumInputPortRx2 = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

        ScalerDpMstRxIntHandle_EXINT0(enumInputPortRx2);
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Get InputPort according to enumMacSourceType
// Input Value  : enumMacSourceType
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDpRxGetInputPortMappingSourceType_EXINT0(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            enumInputPort = _D0_INPUT_PORT;
#endif
            break;

        case _STREAM_SOURCE_D1_DP:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            enumInputPort = _D1_INPUT_PORT;
#endif

            break;

        case _STREAM_SOURCE_D2_DP:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            enumInputPort = _D2_INPUT_PORT;
#endif

            break;

        case _STREAM_SOURCE_MST2SST:

#if(_DP_MST2SST_SUPPORT == _ON)
            enumInputPort = GET_DP_RX_MAIN_PORT();
#endif
            break;

        case _STREAM_SOURCE_PXP:

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            enumInputPort = _D9_INPUT_PORT;
#endif
            break;

        default:
            break;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : Get DP Mac Switch Status
// Input Value  : EnumDpMacEnum, SourceSearchPort
// Output Value : None
//--------------------------------------------------
EnumDpMacSel ScalerDpRxGetMacSwitch_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpMacSel enumMacIndex = 0;
    EnumDpMacSel enumMacSel = _DP_MAC_NONE;

#if((_D7_DP_SUPPORT == _ON) || (_D8_DP_SUPPORT == _ON))
    EnumDpMacSel enumDpMacSelMain = _DP_MAC_NONE;
    EnumDpMacSel enumDpMacSelSub = _DP_MAC_NONE;
#endif

    for(enumMacIndex = 0; enumMacIndex < _DP_MAC_ENTITY_MAX; enumMacIndex++)
    {
        if(g_penumDpRxMacEntityGroup[enumMacIndex] == _STREAM_SOURCE_NONE)
        {
            continue;
        }

#if((_D7_DP_SUPPORT == _ON) || (_D8_DP_SUPPORT == _ON))
        if((enumInputPort == _D7_INPUT_PORT) || (enumInputPort == _D8_INPUT_PORT))
        {
            if(g_penumDpRxMacEntityGroup[enumMacIndex] == ScalerDpRxDxMacSourceMapping_EXINT0(_DUAL_DP_MAIN_PORT))
            {
                enumDpMacSelMain = enumMacIndex;
            }

            if(g_penumDpRxMacEntityGroup[enumMacIndex] == ScalerDpRxDxMacSourceMapping_EXINT0(_DUAL_DP_SUB_PORT))
            {
                enumDpMacSelSub = enumMacIndex;
            }

            if((enumDpMacSelMain != _DP_MAC_NONE) && (enumDpMacSelSub != _DP_MAC_NONE))
            {
                enumMacSel = _DP_MAC_DUAL;
                break;
            }
        }
        else
#endif
        {
            if(g_penumDpRxMacEntityGroup[enumMacIndex] == ScalerDpRxDxMacSourceMapping_EXINT0(enumInputPort))
            {
                enumMacSel = enumMacIndex;
                break;
            }
        }
    }

    return enumMacSel;
}

//--------------------------------------------------
// Description  : Get Mac Switch according to enumMacSourceType
// Input Value  : enumMacSourceType
// Output Value : EnumDpMacSel
//--------------------------------------------------
EnumDpMacSel ScalerDpRxGetMacSwitchMappingSourceType_EXINT0(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumDpMacSel enumMacIndex = 0;

    if(enumDpMacStreamSourceType == _STREAM_SOURCE_NONE)
    {
        return _DP_MAC_NONE;
    }

    for(enumMacIndex = 0; enumMacIndex < _DP_MAC_ENTITY_MAX; enumMacIndex++)
    {
        if(g_penumDpRxMacEntityGroup[enumMacIndex] == enumDpMacStreamSourceType)
        {
            return enumMacIndex;
        }
    }

    return _DP_MAC_NONE;
}

//--------------------------------------------------
// Description  : Input Dx Port Mapping to Mac Source Index
// Input Value  : EnumDpMacEnum
// Output Value : EnumDpMacStreamSourceType
//--------------------------------------------------
EnumDpMacStreamSourceType ScalerDpRxDxMacSourceMapping_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpMacStreamSourceType enumMacSource = _STREAM_SOURCE_NONE;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumMacSource = _STREAM_SOURCE_D0_DP;
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumMacSource = _STREAM_SOURCE_D1_DP;
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumMacSource = _STREAM_SOURCE_D2_DP;
            break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _D9_INPUT_PORT:
            enumMacSource = _STREAM_SOURCE_PXP;
            break;
#endif

        default:
            break;
    }

    return enumMacSource;
}

//--------------------------------------------------
// Description  : Get InputPort Switch to Mac Status
// Input Value  : EnumDpMacEnum, SourceSearchPort
// Output Value : None
//--------------------------------------------------
EnumInputPort ScalerDpRxMacGetInputPortSwitch_EXINT0(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
        default:

#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            return ScalerDpRxGetInputPortMappingSourceType_EXINT0(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            return ScalerDpRxGetInputPortMappingSourceType_EXINT0(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            return ScalerDpRxGetInputPortMappingSourceType_EXINT0(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            return ScalerDpRxGetInputPortMappingSourceType_EXINT0(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            return ScalerDpRxGetInputPortMappingSourceType_EXINT0(g_penumDpRxMacEntityGroup[enumDpMacSel]);
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            if((g_penumDpRxMacEntityGroup[_DP_MAC_0] == _STREAM_SOURCE_D0_DP) &&
               (g_penumDpRxMacEntityGroup[_DP_MAC_1] == _STREAM_SOURCE_D1_DP))
            {
                return _D7_INPUT_PORT;
            }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            if((g_penumDpRxMacEntityGroup[_DP_MAC_1] == _STREAM_SOURCE_D1_DP) &&
               (g_penumDpRxMacEntityGroup[_DP_MAC_2] == _STREAM_SOURCE_D2_DP))
            {
                return _D8_INPUT_PORT;
            }
#endif
            break;
#endif
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : DP Port HotPlug Status
// Input Value  : enumInputPort
// Output Value : _HIGH / _LOW
//--------------------------------------------------
bit ScalerDpRxGetHotPlugStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return g_stDpRxHpdStatus.b1D0Status;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return g_stDpRxHpdStatus.b1D1Status;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return g_stDpRxHpdStatus.b1D2Status;
#endif

        default:
            break;
    }

    return _LOW;
}

//--------------------------------------------------
// Description  : DP Port Cable Pre-Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpRxCableStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return g_stDpRxCableStatus.b1D0Status;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return g_stDpRxCableStatus.b1D1Status;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return g_stDpRxCableStatus.b1D2Status;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxBasePortBackup_EXINT0(void)
{
    g_enumDpRxBasePortBackup = GET_DP_RX_BASE_PORT();
}

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup Restore
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxBasePortRestore_EXINT0(void)
{
    ScalerDpRxSetBaseInputPort_EXINT0(g_enumDpRxBasePortBackup);
}

//--------------------------------------------------
// Description  : Get Msg RX Base Address of Input Port
// Input Value  : enumOutputPort
// Output Value : WORD
//--------------------------------------------------
void ScalerDpRxSetBaseInputPort_EXINT0(EnumInputPort enumInputPort)
{
    SET_DP_RX_BASE_PORT(enumInputPort);

    ScalerDpAuxRxSetBase32AddressOffset_EXINT0(enumInputPort);
}
#endif
