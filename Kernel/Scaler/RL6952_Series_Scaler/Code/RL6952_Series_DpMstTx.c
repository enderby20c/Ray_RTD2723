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
// ID Code      : RL6952_Series_DpMstTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPTXMST__

#include "ScalerFunctionInclude.h"
#include "DpMstTx/ScalerDpMstTx.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Tx MST to SST Format Conversion Mux Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxToSstFCMuxSetting(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_0) == _DSC_MAC_0)
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_DSC0 << 4));
            }
            else if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_0) == _DSC_MAC_1)
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_DSC1 << 4));
            }
            else
#endif
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((_DPTX_OUTPUT_MAC_D0) << 4));
            }
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1) == _DSC_MAC_0)
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_DSC0 << 4));
            }
            else if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1) == _DSC_MAC_1)
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_DSC1 << 4));
            }
            else
#endif
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((_DPTX_OUTPUT_MAC_D1) << 4));
            }
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_2) == _DSC_MAC_0)
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_DSC0 << 4));
            }
            else if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_2) == _DSC_MAC_1)
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_DSC1 << 4));
            }
            else
#endif
            {
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((_DPTX_OUTPUT_MAC_D2) << 4));
            }
            break;
#endif

        default:
            break;
    }

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        // Disable DP Tx FC 1 to 2 Mux
        ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, 0x00);
    }
    else
#endif
    {
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
        BYTE ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST));

        if(ucDscMac != _DSC_MAC_NONE)
        {
            if(ScalerDscDecoderGetPixelMode(ucDscMac) == _1_PIXEL_MODE)
            {
                // Enable DP Tx FC 1 to 2 Mux
                ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, _BIT0);
            }
            else
            {
                // Disable DP Tx FC 1 to 2 Mux
                ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, 0x00);
            }
        }
        else
#endif
        {
            // Check Mst2Sst Input Pixel mode
            if(ScalerDpMacMstToSstGetInputPixelMode() == _DP_RX_MAC_ONE_PIXEL_MODE)
            {
                // Enable DP Tx FC 1 to 2 Mux
                ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, _BIT0);
            }
            else
            {
                // Disable DP Tx FC 1 to 2 Mux
                ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, 0x00);
            }
        }
    }
#else
    // Set FC_8KFB 2 pixel to 2 pixel mode
    ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, 0x00);
#endif
}

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP Mst Tx 128b132b To 8b10b Hblank No Sf Mode Support
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMstTx128b132bTo8b10bHblankNoSfModeSupport(void)
{
    return _TRUE;
}
#endif

#endif
