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
// ID Code      : RL6952_Series_Measure.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_MEASURE__

#include "ScalerFunctionInclude.h"
#include "Measure/ScalerMeasure.h"


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
// Description  : Set for Sync Processor Measure Input HV
// Input Value  : enumInputPort --> Input port type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetOfflineMeasureSource(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _A0_INPUT_PORT:
            // Set off line measure source; Disable clock divider
            ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            break;

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

        case _D0_INPUT_PORT:

            // Select DP MAC0 or 1
            switch(ScalerFmtCnvConvertPortType(enumInputPort))
            {
                case _FC_SOURCE_DPMAC0:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _FC_SOURCE_DPMAC1:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _FC_SOURCE_DPMAC2:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _FC_SOURCE_DSC0:
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif
                    break;

                case _FC_SOURCE_DSC1:
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
                    break;

                default:
                    break;
            }

            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

        case _D1_INPUT_PORT:

            // Select DP MAC0 or 1
            switch(ScalerFmtCnvConvertPortType(enumInputPort))
            {
                case _FC_SOURCE_DPMAC0:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _FC_SOURCE_DPMAC1:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _FC_SOURCE_DPMAC2:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _FC_SOURCE_DSC0:
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif
                    break;

                case _FC_SOURCE_DSC1:
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
                    break;

                default:
                    break;
            }

            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

        case _D2_INPUT_PORT:

            // Select DP MAC0 or 1 or 2
            switch(ScalerFmtCnvConvertPortType(enumInputPort))
            {
                case _FC_SOURCE_DPMAC0:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _FC_SOURCE_DPMAC1:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _FC_SOURCE_DPMAC2:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _FC_SOURCE_DSC0:
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif
                    break;

                case _FC_SOURCE_DSC1:
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
                    break;

                default:
                    break;
            }

            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

        case _D3_INPUT_PORT:

            // Select TMDS MAC3 or 4
            switch(ScalerFmtCnvConvertPortType(enumInputPort))
            {
                case _FC_SOURCE_HDMI0:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _FC_SOURCE_HDMI1:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _FC_SOURCE_DSC0:
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif
                    break;

                case _FC_SOURCE_DSC1:
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
                    break;

                default:
                    break;
            }

            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

        case _D4_INPUT_PORT:

            // Select TMDS MAC3 or 4
            switch(ScalerFmtCnvConvertPortType(enumInputPort))
            {
                case _FC_SOURCE_HDMI0:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _FC_SOURCE_HDMI1:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _FC_SOURCE_DSC0:
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif
                    break;

                case _FC_SOURCE_DSC1:
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
                    break;

                default:
                    break;
            }

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            enumInputPort = (GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_SUB_PORT) ? _DUAL_DP_SUB_PORT : _DUAL_DP_MAIN_PORT;

            // Select DP MAC0 or 1
            if(ScalerFmtCnvConvertPortType(enumInputPort) == _FC_SOURCE_DPMAC0)
            {
                ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }
            else
            {
                ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }

            break;

#endif // End of #if(_DUAL_DP_SUPPORT == _ON)

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)

        case _D9_INPUT_PORT:

            // Select DP MAC0 or 1 or 2
            switch(ScalerFmtCnvConvertPortType(enumInputPort))
            {
                case _FC_SOURCE_DPMAC0:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _FC_SOURCE_DPMAC1:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _FC_SOURCE_DPMAC2:
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _FC_SOURCE_DSC0:
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif
                    break;

                case _FC_SOURCE_DSC1:
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
                    break;

                default:
                    break;
            }

            break;
#endif // End of #if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check for interface OOR in measure flow
// Input Value  : enumSourceSearchPort -> input port
// Output Value : _TRUE if not supported
//--------------------------------------------------
bit ScalerMeasureCheckInterfaceNoSupport(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    // Format conversion Path0/2 no support 4 Pixel mode
    if(ScalerFmtCnvGetPixelModeTargetFactor(GET_MEASURE_INPUT_PATH()) == _FC_4_PIXEL_MODE)
    {
        DebugMessageSystem("[warning] HW Format Conversion Path0/2 cannot support 4 pixel mode.", 0);
        return _TRUE;
    }
#endif
#endif

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    if(GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420)
    {
        WORD usPixelClock = ScalerSyncGetInputPixelClk(enumInputPort);

#if(_COLOR_IP_420_SUPPORT == _ON)
        // Fix timing factor from 420 mis-dection
        // That is, when 420 setting is already active in other path, but not this one.
        if((ScalerColor420To422GetStatusByPort(enumInputPort) == _TRUE) &&
           (ScalerColor420To422GetStatusByPath(GET_MEASURE_INPUT_PATH()) == _FALSE))
        {
            usPixelClock /= 2;
        }
#endif
        // 420 HW is not supported for (input timing <= panel)
        // - FC Path0~Path3, 1 pixel mode & pixel clock > 700
        if((ScalerFmtCnvGetPixelModeTargetFactor(GET_MEASURE_INPUT_PATH()) == _FC_1_PIXEL_MODE) &&
           (usPixelClock > ScalerFmtCnvGetPixelModeSpeedLimit(GET_MEASURE_INPUT_PATH(), _FC_1_PIXEL_MODE)))
        {
            DebugMessageSystem("[warning] HW 420 function cannot support 1 pixel mode & pixel clock over _HW_DATA_PATH_SPEED_LIMIT.", 0);
            return _TRUE;
        }

        // 420 HW is not supported for FC Path1/Path2, 2 pixel mode
        if(ScalerFmtCnvGetPixelModeTargetFactor(GET_MEASURE_INPUT_PATH()) > _FC_1_PIXEL_MODE)
        {
            DebugMessageSystem("[warning] HW 420 function only support input 1 pixel mode for FC Path0/2.", 0);
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get off line measure div2
// Input Value  : None
// Output Value : _TRUE: DIV2
//--------------------------------------------------
bit ScalerMeasureGetOfflineMeasureDiv2(void)
{
    return _FALSE;
}

