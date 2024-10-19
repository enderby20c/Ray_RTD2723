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
// ID Code      : ScalerDscDecoder_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DscDecoder/ScalerDscDecoder.h"




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
// Description  : DSC Set Change Status
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderSetChange_EXINT0(EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType, bit bEnable)
{
    switch(enumDscDecoderMacStreamSourceType)
    {
        case _DSC_STREAM_SOURCE_DP_MAC_RX0:
        case _DSC_STREAM_SOURCE_DP_MAC_RX1:
        case _DSC_STREAM_SOURCE_DP_MAC_RX2:
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX3:
        case _DSC_STREAM_SOURCE_HDMI_MAC_RX4:
            SET_DSC_STREAM_CHANGE(enumDscDecoderMacStreamSourceType, bEnable);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC Decode Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderIntHandler_EXINT0(void)
{
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
    ScalerDscDecoder0IntHandler_EXINT0();
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
    ScalerDscDecoder1IntHandler_EXINT0();
#endif
}

#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Dp Mac Rxx Mapping to Dsc Stream Source
// Input Value  : EnumDpMacSel
// Output Value : ucDscMac
//--------------------------------------------------
EnumDscDecoderMacStreamSourceType ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping_EXINT0(EnumDpMacSel enumDpMacSel)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_NONE;

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_DP_MAC_RX0;
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_DP_MAC_RX1;
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_DP_MAC_RX2;
#endif
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_DP_MAC_RX4;
#endif
            break;
#endif

        default:
            break;
    }

    return enumDscDecoderMacStreamSourceType;
}

//--------------------------------------------------
// Description  : DP MAC RXx Get Dsc Decoder Mac Index
// Input Value  : EnumDpMacSel
// Output Value : ucDscMac
//--------------------------------------------------
BYTE ScalerDscDecoderDpMacRxxGetDscDecoderMac_EXINT0(EnumDpMacSel enumDpMacSel)
{
    EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType = _DSC_STREAM_SOURCE_NONE;

    enumDscDecoderMacStreamSourceType = ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping_EXINT0(enumDpMacSel);

    return GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(enumDscDecoderMacStreamSourceType);
}
#endif
#endif // End of #if(_DSC_DECODER_SUPPORT == _ON)
