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
// ID Code      : SysDscDecoder.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_DSC__

#include "SysInclude.h"
#include "DscDecoder/SysDscDecoder.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC Decoder Mac Arbiter Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDscDecoderMacArbiterInitial(void)
{
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
#if(_D0_DP_SUPPORT == _ON)
    SET_DX_PORT_DSC_MAC_X_MAPPING(_D0_INPUT_PORT, _DSC_MAC_0);
#endif
#if(_D1_DP_SUPPORT == _ON)
    SET_DX_PORT_DSC_MAC_X_MAPPING(_D1_INPUT_PORT, _DSC_MAC_0);
#endif
#if(_D2_DP_SUPPORT == _ON)
    SET_DX_PORT_DSC_MAC_X_MAPPING(_D2_INPUT_PORT, _DSC_MAC_0);
#endif
#endif
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
#if(_D1_HDMI_SUPPORT == _ON)
    SET_DX_PORT_DSC_MAC_X_MAPPING(_D1_INPUT_PORT, _DSC_MAC_0);
#endif
#if(_D2_HDMI_SUPPORT == _ON)
    SET_DX_PORT_DSC_MAC_X_MAPPING(_D2_INPUT_PORT, _DSC_MAC_0);
#endif
#if(_D3_HDMI_SUPPORT == _ON)
    SET_DX_PORT_DSC_MAC_X_MAPPING(_D3_INPUT_PORT, _DSC_MAC_0);
#endif
#if(_D4_HDMI_SUPPORT == _ON)
    SET_DX_PORT_DSC_MAC_X_MAPPING(_D4_INPUT_PORT, _DSC_MAC_0);
#endif
#endif
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    SET_MST2SST_BRANCH_DSC_X_MAPPING(_DSC_MAC_1);

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
    SET_BG_DETECTION_DSC_X_MAPPING(_DSC_MAC_NONE);
#endif
#else
#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
    SET_BG_DETECTION_DSC_X_MAPPING(_DSC_MAC_1);
    SET_MST2SST_BRANCH_DSC_X_MAPPING(_DSC_MAC_NONE);
#endif
#endif
#endif
}

//--------------------------------------------------
// Description  : DSC Decoder Mac Arbiter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDscDecoderMacArbiter(EnumInputPort enumInputPort, EnumPortType enumPortType, EnumDscDecoderMacApplyType enumDscDecoderMacApplyType)
{
    switch(enumDscDecoderMacApplyType)
    {
        case _DSC_MAC_APPLY_DX_PORT:

            SysDscDecoderMacArbiterDxPort(enumInputPort, enumPortType);
            break;

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
        case _DSC_MAC_APPLY_MST2SST:

            ScalerDscDecoderMacArbiterDpMstToSst(enumInputPort);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC Decoder Mac Arbiter Dx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDscDecoderMacArbiterDxPort(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    BYTE ucDscMac = _DSC_MAC_NONE;

    if(ScalerDscDecoderGetSupport(enumInputPort) == _FALSE)
    {
        SET_DX_PORT_DSC_MAC_X_MAPPING(enumInputPort, _DSC_MAC_NONE);
        return;
    }

    if(GET_RGN_MAX_DISPLAY_REGION() == 0x01)
    {
        // 1P Mode
        if(GET_RGN_INPUT_PORT(_REGION_INDEX_0) == enumInputPort)
        {
            // Region Input Port -> Unused DSC Mac
            ucDscMac = SysDscDecoderGetUnusedDscDecoderMac();
        }
#if((_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON) && (_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON))
        else
        {
            // 1P BG Port -> BG Fixed DSC MAC X
            if(ScalerDscDecoderGetDscDecoderMacEnable(GET_BG_DETECTION_DSC_X_MAPPING()) == _FALSE)
            {
                ucDscMac = GET_BG_DETECTION_DSC_X_MAPPING();
            }
        }
#endif
    }
#if(_MULTI_DISPLAY_MAX != 0X01)
    else
    {
        if(SysRegionConvertPortToRegionIndex(enumInputPort) != _REGION_INDEX_NONE)
        {
            // Region Input Port -> Unused DSC Mac
            ucDscMac = SysDscDecoderGetUnusedDscDecoderMac();
        }
        else
        {
            // 2P BG DSC Not Support
            ucDscMac = _DSC_MAC_NONE;
        }
    }
#endif

    if(ucDscMac == _DSC_MAC_NONE)
    {
        DebugMessageDSC("DSC Decoder Mac Arbiter - No DSC MAC Unused, Return False", 0);

        SET_DX_PORT_DSC_MAC_X_MAPPING(enumInputPort, _DSC_MAC_NONE);

        return;
    }

    SET_DX_PORT_DSC_MAC_X_MAPPING(enumInputPort, ucDscMac);

    DebugMessageDSC("DSC Decoder Mac Arbiter - Dx Input Port", enumInputPort);

    DebugMessageDSC("DSC Decoder Mac Arbiter - DSC MAC Used", ucDscMac);

    ScalerDscDecoderMacSetDscStreamSource(enumInputPort, enumPortType, ucDscMac, _DSC_MAC_APPLY_DX_PORT);

    ScalerDscDecoderPowerCutControl(ucDscMac, _DSC_POWER_CUT_ON);
}

//--------------------------------------------------
// Description  : Get DSC Decoder Unused Mac
// Input Value  : None
// Output Value : ucDscMac
//--------------------------------------------------
BYTE SysDscDecoderGetUnusedDscDecoderMac(void)
{
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
    if((ScalerDscDecoderGetDscDecoderMacEnable(_DSC_MAC_0) == _FALSE) || (GET_SOURCE_JUDGE(SysSourceConvertSearchPort(ScalerDscDecoderGetDxInputPort(_DSC_MAC_0))) == _FALSE))
    {
        return _DSC_MAC_0;
    }
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
    if((ScalerDscDecoderGetDscDecoderMacEnable(_DSC_MAC_1) == _FALSE) || (GET_SOURCE_JUDGE(SysSourceConvertSearchPort(ScalerDscDecoderGetDxInputPort(_DSC_MAC_1))) == _FALSE))
    {
        return _DSC_MAC_1;
    }
#endif

    return _DSC_MAC_NONE;
}

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC Decoder Support Judge
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void SysDscDecoderDxSupportJudge(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
    if(enumPortType == _PORT_DP)
    {
        if((GET_RGN_INPUT_PORT(_REGION_INDEX_0) == enumInputPort) || (GET_RGN_INPUT_PORT(_REGION_INDEX_1) == enumInputPort))
        {
            if(GET_DX_DSC_DECODER_SUPPORT_CHANGE_FOR_BG(enumInputPort) == _TRUE)
            {
                CLR_DX_DSC_DECODER_SUPPORT_CHANGE_FOR_BG(enumInputPort);

                ScalerDscDecoderSyncDpSupportSwitch(enumInputPort, UserInterfaceDscDecoderGetEnable(enumInputPort));

                DebugMessageDSC("Dsc Decoder Support Change to Initial Settings", 0);
            }
        }
        else
        {
            if((GET_DX_PORT_DSC_MAC_X_MAPPING(enumInputPort) == _DSC_MAC_NONE) && (ScalerDscDecoderGetSupport(enumInputPort) == _DSC_DECODER_SUPPORT_ON))
            {
                ScalerDscDecoderSyncDpSupportSwitch(enumInputPort, _DSC_DECODER_SUPPORT_OFF);

                SET_DX_DSC_DECODER_SUPPORT_CHANGE_FOR_BG(enumInputPort);

                DebugMessageDSC("Dsc Decoder Support Change from ON to OFF for BG Detect", 0);
            }
        }
    }
#endif
}
#endif
#endif
