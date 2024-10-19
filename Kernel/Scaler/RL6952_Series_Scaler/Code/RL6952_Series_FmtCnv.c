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
// ID Code      : RL6952_Series_FmtCnv.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "FmtCnv/ScalerFmtCnv.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Convert input data path to format conversion path
// Input Value  : enumInputDataPath --> input data path
// Output Value : format conversion path
//--------------------------------------------------
EnumFormatConversionPath ScalerFmtCnvPathMapping(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1:
            return _FORMAT_CONVERSION_P0;

        case _INPUT_PATH_S1:
            return _FORMAT_CONVERSION_P2;

        default:
            return _FORMAT_CONVERSION_P0;
    }
}

#if(_DUAL_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Assign source type for specific input data path
// Input Value  : enumInputDataPath --> target input path
//                enumFormatConversionSourceType --> target source type
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetDualDpSourceType(void)
{
#if((_D7_DP_SUPPORT == _ON) && (_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384))
    // Set sub to MAC0
    ScalerFmtCnvSetSourceType(_INPUT_PATH_M1_M2, _FC_SOURCE_DPMAC1);
    ScalerFmtCnvSetSourceType(_INPUT_PATH_S1, _FC_SOURCE_DPMAC0);
#else
    // Set sub to MAC1
    ScalerFmtCnvSetSourceType(_INPUT_PATH_M1_M2, _FC_SOURCE_DPMAC0);
    ScalerFmtCnvSetSourceType(_INPUT_PATH_S1, _FC_SOURCE_DPMAC1);
#endif

#if((_D8_DP_SUPPORT == _ON) && (_D8_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384))
    // Set sub to MAC1
    ScalerFmtCnvSetSourceType(_INPUT_PATH_M1_M2, _FC_SOURCE_DPMAC2);
    ScalerFmtCnvSetSourceType(_INPUT_PATH_S1, _FC_SOURCE_DPMAC1);
#else
    // Set sub to MAC2
    ScalerFmtCnvSetSourceType(_INPUT_PATH_M1_M2, _FC_SOURCE_DPMAC1);
    ScalerFmtCnvSetSourceType(_INPUT_PATH_S1, _FC_SOURCE_DPMAC2);
#endif
}
#endif

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
//--------------------------------------------------
// Description  : Set pixel mode
// Input Value  : enumInputDataPath --> input path
// Output Value : pixel mode (from register setting): 0x01, 0x02, 0x04
//--------------------------------------------------
EnumFmtCnvPixelMode ScalerFmtCnvGetPixelModeFactor(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1:
            // HW don't care _BIT7
            if((ScalerGetBit(P31_13_FC_PIXELMODE_CTRL, (_BIT7 | _BIT6)) & _BIT6) == _BIT6)
            {
                return _FC_2_PIXEL_MODE;
            }
            break;

        case _INPUT_PATH_S1:
            if(ScalerGetBit(P31_13_FC_PIXELMODE_CTRL, _BIT2) != 0)
            {
                return _FC_2_PIXEL_MODE;
            }
            break;

        default:
            break;
    }

    return _FC_1_PIXEL_MODE;
}

//--------------------------------------------------
// Description  : Set pixel mode
// Input Value  : enumInputDataPath --> input path
// Output Value : pixel mode (from other setting): 0x01, 0x02, 0x04
//--------------------------------------------------
EnumFmtCnvPixelMode ScalerFmtCnvGetPixelModeTargetFactor(EnumInputDataPath enumInputDataPath)
{
    EnumInputPort enumMappingPort = _NO_INPUT_PORT;
    EnumFormatConversionSourceType enumFcSourceType = ScalerFmtCnvGetSourceType(enumInputDataPath);

    switch(enumFcSourceType)
    {
#if(_DP_SUPPORT == _ON)
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _FC_SOURCE_DPMAC0:
            enumMappingPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0);
            break;
#endif
#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _FC_SOURCE_DPMAC1:
            enumMappingPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
            break;
#endif
#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _FC_SOURCE_DPMAC2:
            enumMappingPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_2);
            break;
#endif
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
        case _FC_SOURCE_HDMI0:
            enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);
            break;
        case _FC_SOURCE_HDMI1:
            enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
            break;
#endif

        default:
            break;
    }

    // Get pixel mode status from interface
    switch(enumFcSourceType)
    {
#if(_DP_SUPPORT == _ON)
        case _FC_SOURCE_DPMAC0:
        case _FC_SOURCE_DPMAC1:
        case _FC_SOURCE_DPMAC2:
            switch(ScalerDpMacStreamRxInputPixelMode(enumMappingPort))
            {
                case _DP_RX_MAC_FOUR_PIXEL_MODE:
                    return _FC_4_PIXEL_MODE;
                case _DP_RX_MAC_TWO_PIXEL_MODE:
                    return _FC_2_PIXEL_MODE;
                default:
                    break;
            }
            break;
#endif

#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _FC_SOURCE_DSC0:
            switch(ScalerGetBit(P7_04_DSC_OUT_FORMAT, (_BIT1 | _BIT0)))
            {
                default:
                case 0x00:
                    break;
                case _BIT0:
                    return _FC_2_PIXEL_MODE;
                case _BIT1:
                case (_BIT1 | _BIT0):
                    return _FC_4_PIXEL_MODE;
            }
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _FC_SOURCE_DSC1:
            switch(ScalerGetBit(PF5_04_DSC_OUT_FORMAT, (_BIT1 | _BIT0)))
            {
                default:
                case 0x00:
                    break;
                case _BIT0:
                    return _FC_2_PIXEL_MODE;
                case _BIT1:
                case (_BIT1 | _BIT0):
                    return _FC_4_PIXEL_MODE;
            }
            break;
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
        case _FC_SOURCE_HDMI0:
        case _FC_SOURCE_HDMI1:
            if(ScalerTmdsMacRxGetHdmiVer(enumMappingPort) != _FROM_HDMI_TMDS_MAC)
            {
                switch(ScalerHdmiFrlMacRxGetDpfPixelMode(enumMappingPort))
                {
                    case _HDMI_FRL_MAC_RX_DPF_FOUR_PIXEL_MODE:
                        return _FC_4_PIXEL_MODE;
                    case _HDMI_FRL_MAC_RX_DPF_TWO_PIXEL_MODE:
                        return _FC_2_PIXEL_MODE;
                    default:
                        break;
                }
            }
            break;
#endif

        default:
#if(_VGA_SUPPORT == _ON)
        case _FC_SOURCE_ADC:
#endif
            break;
    }

    return _FC_1_PIXEL_MODE;
}

//--------------------------------------------------
// Description  : Set pixel mode
// Input Value  : enumInputDataPath --> input path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetPixelMode(EnumInputDataPath enumInputDataPath, EnumFmtCnvPixelMode enumFmtCnvPixelMode)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0)
    {
        switch(enumFmtCnvPixelMode)
        {
            case _FC_2_PIXEL_MODE:
                ScalerSetBit(P31_13_FC_PIXELMODE_CTRL, ~(_BIT7 | _BIT6), _BIT6);
                break;

            default:
            case _FC_1_PIXEL_MODE:
                ScalerSetBit(P31_13_FC_PIXELMODE_CTRL, ~(_BIT7 | _BIT6), 0);
                break;
        }
    }

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0)
    {
        switch(enumFmtCnvPixelMode)
        {
            case _FC_2_PIXEL_MODE:
                ScalerSetBit(P31_13_FC_PIXELMODE_CTRL, ~_BIT2, _BIT2);
                break;

            default:
            case _FC_1_PIXEL_MODE:
                ScalerSetBit(P31_13_FC_PIXELMODE_CTRL, ~_BIT2, 0);
                break;
        }
    }
}
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check if FB Mode can be reset.
// Input Value  : EnumInputDataPath enumInputDataPath
// Output Value : _TRUE: reset
//--------------------------------------------------
bit ScalerFmtCnvResetFBModeStatus(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

    if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) && (enumInputDataPath != _INPUT_PATH_M1_M2_S1_S2))
    {
        switch(GET_DISPLAY_MODE())
        {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
                return _FALSE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                return _FALSE;

            case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                return _FALSE;
#endif

            default:
                return _TRUE;
        }
    }

    return _TRUE;
}
#endif

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Eagle Sight Effect Status
// Input Value  : ucInPixelMode
// Output Value : void
//--------------------------------------------------
EnumFCEagleSightStatus ScalerFmtCnvEagleSightEffectStatus(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(enumInputDataPath == _INPUT_PATH_S1)
    {
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            return _FC_EAGLE_SIGHT_ENABLE;
        }
        else
        {
            return _FC_EAGLE_SIGHT_DISABLE;
        }
    }
#endif

    return _FC_EAGLE_SIGHT_NONE;
}

//--------------------------------------------------
// Description  : Get Eagle Sight Pixel Mode
// Input Value  : ucInPixelMode
// Output Value : void
//--------------------------------------------------
EnumFmtCnvPixelMode ScalerFmtCnvEagleSightGetPixelMode(void)
{
    EnumFmtCnvPixelMode enumFmtCnvPixelMode = _FC_1_PIXEL_MODE;

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    if(ScalerGetBit(P31_13_FC_PIXELMODE_CTRL, _BIT2) != 0)
    {
        enumFmtCnvPixelMode = _FC_2_PIXEL_MODE;
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if(ScalerGetBit(P31_E0_YUV420TO422_CTL_PATH2_3, _BIT1) == _BIT1)
    {
        enumFmtCnvPixelMode *= 2;
    }
#endif

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    enumFmtCnvPixelMode /= ScalerFmtCnvHalfSDGetFactor(_INPUT_PATH_S1);

    if(enumFmtCnvPixelMode == 0)
    {
        enumFmtCnvPixelMode = _FC_1_PIXEL_MODE;
    }
#endif

    return enumFmtCnvPixelMode;
}

//--------------------------------------------------
// Description  : Set Eagle Sight Enable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerFmtCnvEagleSightEnable(bit bEnable)
{
    ScalerSetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, ~_BIT0, (bEnable == _ENABLE) ? _BIT0 : 0);
}

//--------------------------------------------------
// Description  : Set Eagle Sight Enable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
bit ScalerFmtCnvEagleSightEnableStatus(void)
{
    return (ScalerGetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, _BIT0) == _BIT0) ? _TRUE : _FALSE;
}

//--------------------------------------------------
// Description  : Set Eagle Sight Capture Double Buffer Enable
// Input Value  : bEn
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvEagleSightCaptureDoubleBufferEnable(bit bEn)
{
    if(ScalerFmtCnvEagleSightEnableStatus() == _TRUE)
    {
        if(bEn == _ENABLE)
        {
            ScalerSetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, ~_BIT1, _BIT1);
        }
        else
        {
            ScalerSetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, ~_BIT1, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set Eagle Sight Capture Double Buffer Enable
// Input Value  : bEn
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvEagleSightSetCaptureDBCtrl(EnumFmtCnvCapDBCtrl enumDBCtrl)
{
    // FC Eagle Sight Capture DB enable
    if(ScalerGetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, _BIT1) == _BIT1)
    {
        if(enumDBCtrl == _FC_CAPTURE_DB_APPLY)
        {
            ScalerSetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, ~_BIT5, _BIT5);
        }
        else
        {
            ScalerSetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, ~_BIT5, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set Eagle Sight Pixel Mode
// Input Value  : ucInPixelMode
// Output Value : void
//--------------------------------------------------
void ScalerFmtCnvEagleSightSetPixelModeConv(EnumFmtCnvPixelMode enumFmtCnvPixelMode)
{
    switch(enumFmtCnvPixelMode)
    {
        case _FC_2_PIXEL_MODE:
            ScalerSetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, ~(_BIT4 | _BIT3), _BIT3);
            break;

        default:
        case _FC_1_PIXEL_MODE:
            ScalerSetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, ~(_BIT4 | _BIT3), _BIT4 | _BIT3);
            break;
    }
}

//--------------------------------------------------
// Description  : Set Eagle Sight Capture Start
// Input Value  : usStart
// Output Value : void
//--------------------------------------------------
void ScalerFmtCnvEagleSightSetCaptureStart(WORD usStart)
{
    BYTE ucPixelMode = ScalerGetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, (_BIT4 | _BIT3));

    if(ucPixelMode == _BIT3)
    {
        usStart = (usStart / 2) * 2;
    }

    ScalerSetBit(P31_21_S1_FC_CAPTURE_HSTART_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usStart >> 8) & 0x0F);
    ScalerSetByte(P31_22_S1_FC_CAPTURE_HSTART_L, usStart & 0xFF);
}

//--------------------------------------------------
// Description  : Set Eagle Sight Capture Start
// Input Value  : usWidth
// Output Value : void
//--------------------------------------------------
WORD ScalerFmtCnvEagleSightGetCaptureStart(void)
{
    return TO_WORD(ScalerGetBit(P31_21_S1_FC_CAPTURE_HSTART_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(P31_22_S1_FC_CAPTURE_HSTART_L));
}

//--------------------------------------------------
// Description  : Set Eagle Sight Capture Width
// Input Value  : usWidth
// Output Value : void
//--------------------------------------------------
void ScalerFmtCnvEagleSightSetCaptureWidth(WORD usWidth)
{
    BYTE ucPixelMode = ScalerGetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, (_BIT4 | _BIT3));

    if(ucPixelMode == _BIT3)
    {
        usWidth = (usWidth / 2) * 2;
    }

    ScalerSetBit(P31_23_S1_FC_CAPTURE_HWIDTH_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usWidth >> 8) & 0x0F);
    ScalerSetByte(P31_24_S1_FC_CAPTURE_HWIDTH_L, usWidth & 0xFF);
}

//--------------------------------------------------
// Description  : Set Eagle Sight Capture Width
// Input Value  : usWidth
// Output Value : void
//--------------------------------------------------
WORD ScalerFmtCnvEagleSightGetCaptureWidth(void)
{
    return TO_WORD(ScalerGetBit(P31_23_S1_FC_CAPTURE_HWIDTH_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(P31_24_S1_FC_CAPTURE_HWIDTH_L));
}

//--------------------------------------------------
// Description  : Set Eagle Sight Sync Delay
// Input Value  : usStart
// Output Value : void
//--------------------------------------------------
void ScalerFmtCnvEagleSightSetSyncDelay(WORD usDelay)
{
    BYTE ucPixelMode = ScalerGetBit(P31_20_S1_FC_CAPTURE_DATA_CTRL, (_BIT4 | _BIT3));

    if(ucPixelMode == _BIT3)
    {
        usDelay = usDelay / 2;
    }

    ScalerSetBit(P31_25_S1_FC_CAP_SYNC_DELAY_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usDelay >> 8) & 0x1F);
    ScalerSetByte(P31_26_S1_FC_CAP_SYNC_DELAY_L, usDelay & 0xFF);
}
#endif

//--------------------------------------------------
// Description  : Reset input data path in format conversion
// Input Value  : enumInputDataPath --> input data path
//                bEnable --> enable/disable after reset
// Output Value : None
//--------------------------------------------------
bit ScalerFmtCnvResetStatus(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

    // RL6952 don't have to avoid reset shared path
    return _TRUE;
}
#endif // End of #if(_FORMAT_CONVERSION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Convert enumeration from source port type to format conversion source type
// Input Value  : source port type
// Output Value : format conversion source type
//--------------------------------------------------
EnumFormatConversionSourceType ScalerFmtCnvConvertPortType(EnumInputPort enumInputPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    if(enumInputPort == _DUAL_DP_INPUT_PORT)
    {
        enumInputPort = (GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_SUB_PORT) ? _DUAL_DP_SUB_PORT : _DUAL_DP_MAIN_PORT;
    }
#endif

    switch(enumInputPort)
    {
#if(_VGA_SUPPORT == _ON)
        case _A0_INPUT_PORT:
            return _FC_SOURCE_ADC;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if(_DP_SUPPORT == _ON)
            // Check which MAC selects D0 port
            switch(ScalerDpRxGetMacSwitch(_D0_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC0;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_0))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC0;
                    }
#endif
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC1;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC1;
                    }
#endif
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC2;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_2))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC2;
                    }
#endif
#endif
                default:
                    break;
            }
#endif

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if(_DP_SUPPORT == _ON)
            // Check which MAC selects D1 port
            switch(ScalerDpRxGetMacSwitch(_D1_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC0;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_0))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC0;
                    }
#endif
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC1;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC1;
                    }
#endif
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC2;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_2))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC2;
                    }
#endif
#endif
                default:
                    break;
            }
#endif

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_DP_SUPPORT == _ON)
            // Check which MAC selects D2 port
            switch(ScalerDpRxGetMacSwitch(_D2_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC0;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_0))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC0;
                    }
#endif
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC1;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC1;
                    }
#endif
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC2;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_2))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC2;
                    }
#endif
#endif
                default:
                    break;
            }
#endif

            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_HDMI_SUPPORT == _ON)
            // Check which MAC selects D3 port
            switch(ScalerTmdsMacRxDxRxMapping(_D3_INPUT_PORT))
            {
                case _RX3:
#if(_HDMI_FRL_MAC_RX3_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_HDMI0;
#else
                    switch(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_HDMI0;
                    }
#endif
                case _RX4:
#if(_HDMI_FRL_MAC_RX4_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_HDMI1;
#else
                    switch(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_HDMI1;
                    }
#endif
                default:
                    break;
            }
#endif // End of #if(_HDMI_SUPPORT == _ON)

            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_HDMI_SUPPORT == _ON)
            // Check which MAC selects D4 port
            switch(ScalerTmdsMacRxDxRxMapping(_D4_INPUT_PORT))
            {
                case _RX3:
#if(_HDMI_FRL_MAC_RX3_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_HDMI0;
#else
                    switch(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_HDMI0;
                    }
#endif
                case _RX4:
#if(_HDMI_FRL_MAC_RX4_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_HDMI1;
#else
                    switch(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_HDMI1;
                    }
#endif
                default:
                    break;
            }
#endif // End of #if(_HDMI_SUPPORT == _ON)

            break;
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
        case _D9_INPUT_PORT:

#if(_DP_SUPPORT == _ON)
            // Check which MAC selects D9 port
            switch(ScalerDpRxGetMacSwitch(_D9_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC0;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_0))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC0;
                    }
#endif
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC1;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC1;
                    }
#endif
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _OFF)
                    return _FC_SOURCE_DPMAC2;
#else
                    switch(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_2))
                    {
                        case _DSC_MAC_0:
                            return _FC_SOURCE_DSC0;

                        case _DSC_MAC_1:
                            return _FC_SOURCE_DSC1;

                        default:
                            return _FC_SOURCE_DPMAC2;
                    }
#endif
#endif
                default:
                    break;
            }
#endif

            break;
#endif

        default:
            break;
    }

    return _FC_SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Check if want to set Equal Performance by half sd
// Input Value  : EnumInputDataPath enumInputDataPath
// Output Value : _TRUE: Equal
//--------------------------------------------------
bit ScalerFmtCnvPerformanceEqualCheck(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

#if((_2P_PBP_LR_PERFORMANCE_TYPE == _MAIN_EQUAL_TO_SUB) && (_2P_PBP_LR_DISPLAY_SUPPORT == _ON))
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_EQUAL) &&
       (enumInputDataPath == _INPUT_PATH_M1_M2))
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get FC Sub3 Vsync Delay Type
// Input Value  : void
// Output Value : enumFCSub3VsDelayType
//--------------------------------------------------
EnumFCSub3VsDelayType ScalerFmtCnvGetSub3VSyncDelayType(void)
{
    // RL6952 don't have sub3 path
    return _FC_SUB3_VS_DELAY_NONE;
}

//--------------------------------------------------
// Description  : Get speed limit by diffenent pixel mode
// Input Value  : enumInputDataPath -> input data path
//                enumFmtCnvPixelMode -> input pixel mode
// Output Value : pixel mode speed boundary (Unit: 0.1MHz)
//--------------------------------------------------
DWORD ScalerFmtCnvGetPixelModeSpeedLimit(EnumInputDataPath enumInputDataPath, EnumFmtCnvPixelMode enumFmtCnvPixelMode)
{
    switch(ScalerFmtCnvGetSourceType(enumInputDataPath))
    {
        default:
            break;

#if(_HDMI_SUPPORT == _ON)
        case _FC_SOURCE_HDMI0:
        case _FC_SOURCE_HDMI1:

            if(ScalerTmdsMacRxGetHdmiVer(ScalerFmtCnvGetInputPortType(enumInputDataPath)) == _FROM_HDMI_FRL_MAC)
            {
                switch(enumFmtCnvPixelMode)
                {
                    case _FC_1_PIXEL_MODE:
                        return _HW_HDMI_FRL_DPF_2P_MODE_FREQ;

                    case _FC_2_PIXEL_MODE:
                        return _HW_HDMI_FRL_DPF_4P_MODE_FREQ;

                    default:
                    case _FC_4_PIXEL_MODE:
                        break;
                }
            }
            else if(ScalerTmdsMacRxGetHdmiVer(ScalerFmtCnvGetInputPortType(enumInputDataPath)) == _FROM_HDMI_TMDS_MAC)
            {
                switch(enumFmtCnvPixelMode)
                {
                    case _FC_1_PIXEL_MODE:
                    case _FC_2_PIXEL_MODE:
                        return _HW_HDMI_VIDEO_PLL_CLK_LIMIT * enumFmtCnvPixelMode;

                    default:
                        break;
                }
            }
            break;
#endif
    }

    return GET_DWORD_MUL_DIV((_HW_DATA_PATH_SPEED_LIMIT * enumFmtCnvPixelMode), 101, 100);
}

//--------------------------------------------------
// Description  : Get data path max speed limit
// Input Value  :
// Output Value : Data path max speed limit (Unit: 0.1MHz)
//--------------------------------------------------
DWORD ScalerFmtCnvGetDataPathMaxSpeedLimit(void)
{
    // DP & DSC source pix mode boundary are equal to (HW data path limit * pix mode)
#if(_HDMI_FRL_SUPPORT == _ON)
    // Max of 1, 2, 4 pixel mode single path limit
    return MAXOF3(_HW_HDMI_FRL_DPF_2P_MODE_FREQ, _HW_HDMI_FRL_DPF_4P_MODE_FREQ / 2, _HW_DATA_PATH_SPEED_LIMIT);
#else
    return _HW_DATA_PATH_SPEED_LIMIT;
#endif
}

//--------------------------------------------------
// Description  : Get HalfSD Mode Select
// Input Value  : enumInputDataPath --> target input data path
//                ucFactor --> SD factor: 1 or 2 or 4
// Output Value : EnumFCHalfSDMode
//--------------------------------------------------
EnumFCHalfSDMode ScalerFmtCnvGetHalfSDModeSelect(EnumInputDataPath enumInputDataPath, BYTE ucFactor)
{
    enumInputDataPath = enumInputDataPath;

    switch(ucFactor)
    {
        case 2:
            return _FC_HALFSD_AVERAGE_MODE;

        default:
        case 1:
            return _FC_HALFSD_DROP_MODE;
    }
}

