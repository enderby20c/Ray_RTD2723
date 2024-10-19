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
// ID Code      : ScalerFmtCnv.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_FMT_CNV__

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
// Description  : Initialize for format conversion
// Input Value  : enumInputPort --> input port
//                enumInputDataPath -> target input path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvInitialSetting(EnumSourceType enumSourceType, EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath)
{
    EnumFormatConversionSourceType enumFormatConversionSourceType = ScalerFmtCnvConvertPortType(enumInputPort);

    // Enable reset path
    ScalerFmtCnvResetPath(enumInputDataPath, _ENABLE);

    // Set format conversion source type
    ScalerFmtCnvSetSourceType(enumInputDataPath, enumFormatConversionSourceType);

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    // Disable pixel mode
    ScalerFmtCnvSetPixelMode(enumInputDataPath, _FC_1_PIXEL_MODE);
#endif

#if(_COLOR_IP_420_SUPPORT == _ON)
    ScalerColor420To422InitialByPath(enumInputDataPath);
#endif

    // Disable background
    ScalerFmtCnvSetBackgroundStatus(enumInputDataPath, _DISABLE);

    // Set VS edge align
    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:
            ScalerFmtCnvSetVsBypassEnable(enumInputDataPath, _ENABLE);
            break;
#endif

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_HDMI:
#if(_HDMI_FRL_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_FRL_MAC)
            {
                ScalerFmtCnvSetVsBypassEnable(enumInputDataPath, _ENABLE);
            }
            else
#endif
            {
                ScalerFmtCnvSetVsBypassEnable(enumInputDataPath, _DISABLE);
            }
            break;
#endif
#endif
        default:
            ScalerFmtCnvSetVsBypassEnable(enumInputDataPath, _DISABLE);
            break;
    }

    // Check input pixel rate
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)

#if(_DUAL_DP_SUPPORT == _ON)
    if((enumInputPort == _DUAL_DP_INPUT_PORT) &&
       (GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_INPUT_PORT) &&
       ((ScalerSyncGetInputPixelClk(_DUAL_DP_INPUT_PORT) / 2) > ScalerFmtCnvGetPixelModeSpeedLimit(enumInputDataPath, _FC_1_PIXEL_MODE)))
    {
        ScalerFmtCnvHalfSDSetFirstPixel(enumInputDataPath, 0);

        // Enable 1/2 scaling down
        ScalerFmtCnvHalfSDSetFactor(enumInputDataPath, 0x02);
    }
    else
#endif
    {
        WORD usPixelClock = ScalerSyncGetInputPixelClk(ScalerFmtCnvGetInputPortType(enumInputDataPath));

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
        // Apply pixel mode fix
        usPixelClock /= ScalerFmtCnvGetPixelModeTargetFactor(enumInputDataPath);
#endif

#if(_COLOR_IP_420_SUPPORT == _ON)
        // Fix timing factor from 420 mis-dection
        // That is, when 420 setting is already active in other path, but not this one.
        if((ScalerColor420To422GetStatusByPort(enumInputPort) == _TRUE) &&
           (ScalerColor420To422GetStatusByPath(enumInputDataPath) == _FALSE))
        {
            usPixelClock /= 2;
        }
#endif
        ScalerFmtCnvHalfSDSettingByClock(enumInputDataPath, usPixelClock);
    }
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    // Disable F-to-P
    ScalerFmtCnvFtoPControl(enumInputDataPath, _DISABLE);
#endif

    // Reset front/back setting for 1p/pip/pbp main, or any other display modes
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerFmtCnvResetFBModeStatus(enumInputDataPath) == _TRUE)
    {
        // Set extension length to 0
        SET_FMTCNV_EXTENSION_LEN(0);

        // Disable F/B
        ScalerFmtCnvFBSetStatus(_FB_OFF);
    }
#endif

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
    ScalerFmtCnvEagleSightEnable(_DISABLE);
#endif

    // Disable reset path
    ScalerFmtCnvResetPath(enumInputDataPath, _DISABLE);

    // Initialize CTS fifo
    ScalerFmtCnvCtsFifoInitSetting(enumInputDataPath);
}

//--------------------------------------------------
// Description  : Final format conversion setting
// Input Value  : enumInputPort --> input port
//                enumInputDataPath --> target input data path
//                bWait --> _TRUE to apply additional wait for I-domain to sattle
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath, bit bWait)
{
    BYTE ucIndex = 0;

#if((_HW_FORMAT_CONVERSION_EO_MODE == _ON) || (_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON))
    WORD usHwidth = GET_INPUT_TIMING_HWIDTH();
#endif

    enumInputPort = enumInputPort;

#if(_VGA_SUPPORT == _ON)
    // Enable VS edge align for VGA
    if(enumInputPort == _A0_INPUT_PORT)
    {
        ScalerFmtCnvSetVsBypassEnable(enumInputDataPath, _DISABLE);
    }
#endif
    ScalerFmtCnvCheckHsExpandEnable(enumInputDataPath, GET_INPUT_TIMING_HSYNCWIDTH());

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    // Update pixel mode
    ScalerFmtCnvSetPixelMode(enumInputDataPath, ScalerFmtCnvGetPixelModeTargetFactor(enumInputDataPath));
#endif

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    {
        // Apply path fix for pixel clock
        WORD usPixelClock = ScalerSyncGetInputPixelClk(ScalerFmtCnvGetInputPortType(enumInputDataPath));

//#if(3DDI_SUPPORT)
// usPixelClock *= ((GET_3DDI_STATUS() == _TRUE) ? 2 : 0);
//#endif

        if(ScalerFmtCnvPerformanceEqualCheck(enumInputDataPath) == _FALSE)
        {
            usPixelClock /= ScalerIDomainGetInputPathCount(enumInputDataPath);
        }

        ScalerFmtCnvHalfSDSettingByClock(enumInputDataPath, usPixelClock);
    }
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
#if(_COLOR_IP_420_SUPPORT == _ON)
    // Check 420 status; H width * 2 for 420 mode
    if(ScalerColor420To422GetStatusByPath(enumInputDataPath) == _TRUE)
    {
        usHwidth *= 2;
    }
#endif

#if(_DUAL_DP_SUPPORT == _ON)
    // Double H width for dual DP
    if((enumInputPort == _DUAL_DP_INPUT_PORT) &&
       (GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_INPUT_PORT))
    {
        usHwidth *= 2;
    }
#endif

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    // Check Width if lager than max,then set half sd.
    // No Check when Eagle Sight On
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
    if(ScalerFmtCnvEagleSightEffectStatus(enumInputDataPath) != _FC_EAGLE_SIGHT_ENABLE)
#endif
    {
        ScalerFmtCnvHalfSDSetFactorByWidth(enumInputDataPath, usHwidth);
    }

    // half scaling down
    usHwidth /= ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
    {
        ScalerFmtCnvFBFinalSetting(enumInputPort, enumInputDataPath);

        // Set E/O H width to half for front/back mode
        usHwidth /= 2;
    }
#endif
#endif

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
    switch(ScalerFmtCnvEagleSightEffectStatus(enumInputDataPath))
    {
        case _FC_EAGLE_SIGHT_ENABLE:
        {
            EnumFmtCnvPixelMode enumFmtCnvPixelMode = ScalerFmtCnvEagleSightGetPixelMode();

            // Must Set Pixel Mode Conv First.
            ScalerFmtCnvEagleSightSetPixelModeConv(enumFmtCnvPixelMode);

            ScalerFmtCnvEagleSightSetCaptureStart(0);
            ScalerFmtCnvEagleSightSetSyncDelay(0);

            if(enumFmtCnvPixelMode != _FC_1_PIXEL_MODE)
            {
                // Avoid capture den overlap capture hsync
                usHwidth /= 2;
            }

            if(usHwidth > _FC_CAPTURE_HWIDTH)
            {
                usHwidth = _FC_CAPTURE_HWIDTH;
            }

            ScalerFmtCnvEagleSightSetCaptureWidth(usHwidth);
            ScalerFmtCnvEagleSightEnable(_ENABLE);

            usHwidth = ScalerFmtCnvEagleSightGetCaptureWidth();

            break;
        }

        case _FC_EAGLE_SIGHT_DISABLE:
            ScalerFmtCnvEagleSightEnable(_DISABLE);
            break;

        case _FC_EAGLE_SIGHT_NONE:
        default:
            break;
    }
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    if((enumInputDataPath == _INPUT_PATH_M1_M2) ||
       (enumInputDataPath == _INPUT_PATH_S1_S2) ||
       (enumInputDataPath == _INPUT_PATH_S3_S4) ||
       (enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2))
    {
        ////////////////////////
        // multiple input path
        ////////////////////////

        // Set main F-to-P FIFO
        ScalerFmtCnvFtoPSetFifo(enumInputPort, enumInputDataPath, usHwidth, GET_INPUT_TIMING_VSTART());

        // Enable main F-to-P
        ScalerFmtCnvFtoPControl(enumInputDataPath, _ENABLE);
    }
#endif

    if(bWait == _WAIT)
    {
        // Wait 4 IVS after format conversion setting
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);
    }

    // Clear VGIP Interlace Toggle Flag
    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0)
        {
            BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);
            SET_PAGED_BIT(ucIdomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        }
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
    {
        // Clear S1/S2 SRAM overflow/underflow flags
        ScalerSetByte(P31_6F_FB_SRAM_CTRL, 0xFF);

        // Clear extension overflow/underflow flags
        ScalerSetByte(P31_72_FB_EXT_FIFO_CTRL, 0xFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Reset input data path in format conversion
// Input Value  : enumInputDataPath --> input data path
//                bEnable --> enable/disable after reset
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvResetPath(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);

    if(ScalerFmtCnvResetStatus(enumInputDataPath) == _FALSE)
    {
        return;
    }

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        if(bEnable == _TRUE)
        {
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT4, _BIT4);
        }
        else
        {
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT4, 0x00);
        }
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        if(bEnable == _TRUE)
        {
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT5, _BIT5);
        }
        else
        {
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT5, 0x00);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        if(bEnable == _TRUE)
        {
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT6, _BIT6);
        }
        else
        {
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT6, 0x00);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        if(bEnable == _TRUE)
        {
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT7, _BIT7);
        }
        else
        {
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT7, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Check if I-domain is affected during format conversion setting
// Input Value  : enumInputDataPath --> input data path
//                enumInputPort --> source port
// Output Value : _TRUE if I-domain timing is affected in format conversion adjust
//--------------------------------------------------
bit ScalerFmtCnvCheckIDomainTimingAffected(EnumInputDataPath enumInputDataPath, EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;
    enumInputDataPath = enumInputDataPath;

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_COLOR_IP_420_SUPPORT == _ON)
    if(ScalerColor420To422GetStatusByPath(enumInputDataPath) == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    if(ScalerFmtCnvGetPixelModeFactor(enumInputDataPath) != _FC_1_PIXEL_MODE)
    {
        return _TRUE;
    }
#endif

//#if(3DDI_SUPPORT)
//    return GET_3DDI_STATUS();
//#endif

    return _FALSE;
}

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
//--------------------------------------------------
// Description  : Control half scaling down factor
// Input Value  : enumInputDataPath --> target input data path
//                usPixelClock --> working pixel clock
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvHalfSDSettingByClock(EnumInputDataPath enumInputDataPath, WORD usPixelClock)
{
    WORD us1PixelLimit = ScalerFmtCnvGetPixelModeSpeedLimit(enumInputDataPath, _FC_1_PIXEL_MODE);
    WORD us2PixelLimit = ScalerFmtCnvGetPixelModeSpeedLimit(enumInputDataPath, _FC_2_PIXEL_MODE);
    WORD us4PixelLimit = ScalerFmtCnvGetPixelModeSpeedLimit(enumInputDataPath, _FC_4_PIXEL_MODE);

#if(_HW_FORMAT_CONVERSION_SD_MODE == _FORMAT_CONVERSION_SD_HALF_FOUR)
    // Update 1/2 SD setting
    if(usPixelClock > MAXOF((us4PixelLimit / 2), us2PixelLimit))
    {
        ScalerFmtCnvHalfSDSetFirstPixel(enumInputDataPath, 0);
        ScalerFmtCnvHalfSDSetFactor(enumInputDataPath, 0x04);
    }
    else
#endif
    {
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
        if(ScalerFmtCnvEagleSightEffectStatus(enumInputDataPath) == _FC_EAGLE_SIGHT_ENABLE)
        {
            ScalerFmtCnvHalfSDSetFactor(enumInputDataPath, 0x01);
        }
        else
#endif
        {
            if(usPixelClock > MAXOF3((us4PixelLimit / 4), (us2PixelLimit / 2), us1PixelLimit))
            {
                ScalerFmtCnvHalfSDSetFirstPixel(enumInputDataPath, 0);
                ScalerFmtCnvHalfSDSetFactor(enumInputDataPath, 0x02);
            }
            else
            {
                ScalerFmtCnvHalfSDSetFactor(enumInputDataPath, 0x01);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Control half scaling down factor
// Input Value  : enumInputDataPath --> target input data path
//                ucFactor --> SD factor: 1 or 2 or 4
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvHalfSDSetFactor(EnumInputDataPath enumInputDataPath, BYTE ucFactor)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);
    EnumFCHalfSDMode enumFCHalfSDMode = ScalerFmtCnvGetHalfSDModeSelect(enumInputDataPath, ucFactor);
    bit bEnable = _DISABLE;

    // Check scaling factor
    switch(ucFactor)
    {
#if(_HW_FORMAT_CONVERSION_SD_MODE == _FORMAT_CONVERSION_SD_HALF_FOUR)
        case 0x04:
            bEnable = _ENABLE;
            break;
#endif

        case 0x02:
            bEnable = _ENABLE;
            break;

        default:
        case 0x01:
            bEnable = _DISABLE;
            break;
    }

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            // Data select SD
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT7, 0x00);

            // Set SD ratio
            ScalerSetBit(P31_11_FC_SD4_CTRL0, ~(_BIT7 | _BIT6), (enumFCHalfSDMode << 6));
        }
        else
        {
            // Data select bypass
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT7, _BIT7);
        }
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            // Data select SD
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT6, 0x00);

            // Set SD ratio
            ScalerSetBit(P31_11_FC_SD4_CTRL0, ~(_BIT5 | _BIT4), (enumFCHalfSDMode << 4));
        }
        else
        {
            // Data select bypass
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT6, _BIT6);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            // Data select SD
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT5, 0x00);

            // Set SD ratio
            ScalerSetBit(P31_11_FC_SD4_CTRL0, ~(_BIT3 | _BIT2), (enumFCHalfSDMode << 2));
        }
        else
        {
            // Data select bypass
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT5, _BIT5);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            // Data select SD
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT4, 0x00);

            // Set SD ratio
            ScalerSetBit(P31_11_FC_SD4_CTRL0, ~(_BIT1 | _BIT0), (enumFCHalfSDMode));
        }
        else
        {
            // Data select bypass
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT4, _BIT4);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get half scaling down factor for specified data path
// Input Value  : enumInputDataPath --> input path
// Output Value : scaling down factor: 1 or 2 or 4
//--------------------------------------------------
BYTE ScalerFmtCnvHalfSDGetFactor(EnumInputDataPath enumInputDataPath)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);
    BYTE ucHalfSDSetting = 0x00;

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        if(ScalerGetBit(P31_05_FC_SD_CTRL, _BIT7) == 0x00)
        {
            ucHalfSDSetting = (ScalerGetBit(P31_11_FC_SD4_CTRL0, (_BIT7 | _BIT6)) >> 6);
            return ScalerFmtCnvHalfSDGetRegisterFactor(ucHalfSDSetting);
        }

        return 0x01;
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        if(ScalerGetBit(P31_05_FC_SD_CTRL, _BIT6) == 0x00)
        {
            ucHalfSDSetting = (ScalerGetBit(P31_11_FC_SD4_CTRL0, (_BIT5 | _BIT4)) >> 4);
            return ScalerFmtCnvHalfSDGetRegisterFactor(ucHalfSDSetting);
        }

        return 0x01;
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        if(ScalerGetBit(P31_05_FC_SD_CTRL, _BIT5) == 0x00)
        {
            ucHalfSDSetting = (ScalerGetBit(P31_11_FC_SD4_CTRL0, (_BIT3 | _BIT2)) >> 2);
            return ScalerFmtCnvHalfSDGetRegisterFactor(ucHalfSDSetting);
        }

        return 0x01;
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        if(ScalerGetBit(P31_05_FC_SD_CTRL, _BIT4) == 0x00)
        {
            ucHalfSDSetting = (ScalerGetBit(P31_11_FC_SD4_CTRL0, (_BIT1 | _BIT0)));
            return ScalerFmtCnvHalfSDGetRegisterFactor(ucHalfSDSetting);
        }

        return 0x01;
    }
#endif

    return 0x01;
}

//--------------------------------------------------
// Description  : Get half scaling down factor from register value
// Input Value  : ucHalfSDSetting --> 1/2 SD register setting
// Output Value : scaling down factor: 2 or 4
//--------------------------------------------------
BYTE ScalerFmtCnvHalfSDGetRegisterFactor(BYTE ucHalfSDSetting)
{
    switch(ucHalfSDSetting)
    {
#if(_HW_FORMAT_CONVERSION_SD_MODE == _FORMAT_CONVERSION_SD_HALF_FOUR)
        case _BIT1:
        case (_BIT1 | _BIT0):
            return 0x04;
#endif

        default:
        case 0x00:
        case _BIT0:
            return 0x02;
    }
}

//--------------------------------------------------
// Description  : Set the first pixel for half scaling down
// Input Value  : enumInputDataPath --> target input data path
//                usHstart --> H start
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvHalfSDSetFirstPixel(EnumInputDataPath enumInputDataPath, WORD usHstart)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);
    bit bEnable = ((LOBYTE(usHstart) & _BIT0) == 0x00);

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            // Set first pixel = even
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT3, _BIT3);
        }
        else
        {
            // Set first pixel = odd
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT3, 0x00);
        }
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            // Set first pixel = even
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT2, _BIT2);
        }
        else
        {
            // Set first pixel = odd
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT2, 0x00);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            // Set first pixel = even
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT1, _BIT1);
        }
        else
        {
            // Set first pixel = odd
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT1, 0x00);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            // Set first pixel = even
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT0, _BIT0);
        }
        else
        {
            // Set first pixel = odd
            ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT0, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Half Scaling down status
// Input Value  : enumInputDataPath --> target input data path
// Output Value : _TRUE if the first pixel is skipped
//--------------------------------------------------
bit ScalerFmtCnvHalfSDGetFirstPixel(EnumInputDataPath enumInputDataPath)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        return (ScalerGetBit(P31_05_FC_SD_CTRL, _BIT3) != 0x00);
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        return (ScalerGetBit(P31_05_FC_SD_CTRL, _BIT2) != 0x00);
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        return (ScalerGetBit(P31_05_FC_SD_CTRL, _BIT1) != 0x00);
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        return (ScalerGetBit(P31_05_FC_SD_CTRL, _BIT0) != 0x00);
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set Half Scaling down by width
// Input Value  : enumInputDataPath --> target input data path
// Output Value : none
//--------------------------------------------------
void ScalerFmtCnvHalfSDSetFactorByWidth(EnumInputDataPath enumInputDataPath, WORD usWidth)
{
    BYTE ucFBSDRatio = 1;
    BYTE ucFactor = ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);

    ucFBSDRatio *= ucFactor;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
    {
        ucFBSDRatio *= 2;
    }
#endif

    if(usWidth > (_HW_FORMAT_CONVERSION_EO_MODE_BUFFER_WIDTH * ucFBSDRatio))
    {
        switch(ucFactor)
        {
#if(_HW_FORMAT_CONVERSION_SD_MODE == _FORMAT_CONVERSION_SD_HALF_FOUR)
            case 0x02:
                ucFactor = 4;
                break;
#endif

#if(_HW_FORMAT_CONVERSION_SD_MODE >= _FORMAT_CONVERSION_SD_HALF)
            case 0x01:
                ucFactor = 2;
                break;
#endif

            default:
                return;
        }

        ScalerFmtCnvHalfSDSetFactor(enumInputDataPath, ucFactor);
    }
}
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
//--------------------------------------------------
// Description  : Set V start line toggle in format conversion E/O mode
// Input Value  : enumInputDataPath --> target input path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPInterlaceSetting(EnumInputDataPath enumInputDataPath)
{
    if((enumInputDataPath & _INPUT_PATH_M1_M2) == _INPUT_PATH_M1_M2)
    {
        // Check V start changes by field
        if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT6) == 0x00)
        {
            // Disable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT7, 0x00);
        }
        else
        {
            // Enable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT7, _BIT7);

            // Check V start is even or odd
            if((GET_ACTIVE_V_START() & 0x0001) == 0x0001)
            {
                // Check the field with larger V start
                if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, 0x00);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, _BIT6);
                }

                // Disable VGIP odd delay 1 line
                ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT6, 0x00);
                ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~_BIT6, 0x00);
            }
            else
            {
                // Check the field with larger V start
                if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, _BIT6);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, 0x00);
                }
            }
        }
    }

#if((_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON))
    if((enumInputDataPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S1_S2)
    {
        if(ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, _BIT6) == 0x00)
        {
            // Disable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT5, 0x00);
        }
        else
        {
            // Enable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT5, _BIT5);

            // Check V start is even or odd
            if((GET_ACTIVE_V_START() & 0x0001) == 0x0001)
            {
                // Check the field with larger V start
                if(ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT4, 0x00);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT4, _BIT4);
                }

                // Disable VGIP odd delay 1 line
                ScalerSetBit(P80_13_S1_VGIP_ODD_CTRL, ~_BIT6, 0x00);
                ScalerSetBit(PC0_13_S2_VGIP_ODD_CTRL, ~_BIT6, 0x00);
            }
            else
            {
                // Check the field with larger V start
                if(ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT4, _BIT4);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT4, 0x00);
                }
            }
        }
    }
#endif

#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
    if((enumInputDataPath & _INPUT_PATH_S3_S4) == _INPUT_PATH_S3_S4)
    {
        if(ScalerGetBit(P17_13_S3_VGIP_ODD_CTRL, _BIT6) == 0x00)
        {
            // Disable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT3, 0x00);
        }
        else
        {
            // Enable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT3, _BIT3);

            // Check V start is even or odd
            if((GET_ACTIVE_V_START() & 0x0001) == 0x0001)
            {
                // Check the field with larger V start
                if(ScalerGetBit(P17_13_S3_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT2, 0x00);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT2, _BIT2);
                }

                // Disable VGIP odd delay 1 line
                ScalerSetBit(P17_13_S3_VGIP_ODD_CTRL, ~_BIT6, 0x00);
                ScalerSetBit(PDC_13_S4_VGIP_ODD_CTRL, ~_BIT6, 0x00);
            }
            else
            {
                // Check the field with larger V start
                if(ScalerGetBit(P17_13_S3_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT2, _BIT2);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT2, 0x00);
                }
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Control for even/odd mode for specified path
// Input Value  : enumInputDataPath -> target input data path
//                bEnable -> _ENABLE to enable even/odd mode
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPControl(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    if((enumInputDataPath & _INPUT_PATH_M1_M2) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
#if(_VGA_SUPPORT == _ON)
            if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
            {
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
                if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x02))
                {
                    // Enable VS delay to enlarge front porch
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT1, _BIT1);

                    if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x08))
                    {
                        ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
                    }
                    else if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x06))
                    {
                        ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT5 | _BIT4), _BIT5);
                    }
                    else if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x04))
                    {
                        ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT5 | _BIT4), _BIT4);
                    }
                    else
                    {
                        ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT5 | _BIT4), 0x00);
                    }
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT1, 0x00);
                }
#else
                // Enable VS delay 8 line to enlarge front porch
                if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x08))
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT1, _BIT1);
                }
#endif
            }

            // Enable Main F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, _BIT7);
        }
        else
        {
            // Disable E/O interlace Vst control; Disable VS delay 8 line; Disable extended DEN
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT7 | _BIT6 | _BIT1), 0x00);

            // Set E/O H width to 0
            ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, 0x00);

            // Disable Main F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, 0x00);
        }
    }

#if((_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON))
    if((enumInputDataPath & _INPUT_PATH_S1_S2) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
#if(_VGA_SUPPORT == _ON)
            if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
            {
                if(ScalerFmtCnvGetSub3VSyncDelayType() == _FC_SUB3_VS_DELAY_NONE)
                {
                    // Enable VS delay 8 line to enlarge front porch
                    if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x08))
                    {
                        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT0, _BIT0);
                    }
                }
            }

            // Enable Sub F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT3, _BIT3);
        }
        else
        {
            if(ScalerFmtCnvGetSub3VSyncDelayType() != _FC_SUB3_VS_DELAY_FROM_SUB1)
            {
                // Disable E/O interlace Vst control; Disable VS delay 8 line; Disable extended DEN
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT5 | _BIT4 | _BIT0), 0x00);
            }
            else
            {
                // Disable E/O interlace Vst control; Disable extended DEN; VS delay 8 line keep for S3 using
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT5 | _BIT4), 0x00);
            }

            // Set E/O H width to 0
            ScalerSetBit(P31_09_FC_FORMAT_PRO_SUB_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P31_0A_FC_FORMAT_PRO_SUB_1, 0x00);

            // Disable Sub F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT3, 0x00);
        }
    }
#endif

#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
    if((enumInputDataPath & _INPUT_PATH_S3_S4) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
#if(_VGA_SUPPORT == _ON)
            if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
            {
                if(ScalerFmtCnvGetSub3VSyncDelayType() == _FC_SUB3_VS_DELAY_FROM_SUB1)
                {
                    if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x08))
                    {
                        // Use S1 VS delay enable control S3
                        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT0, _BIT0);

                        // Enable S3 VS delay
                        ScalerSetBit(P31_12_FC_CLK_CTRL, ~_BIT7, _BIT7);
                    }
                }
                else if(ScalerFmtCnvGetSub3VSyncDelayType() == _FC_SUB3_VS_DELAY_NONE)
                {
                    if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x08))
                    {
                        // 3P mode S3S4 VS delay disable
                        ScalerSetBit(P31_12_FC_CLK_CTRL, ~_BIT7, _BIT7);
                    }
                }
            }

            // Enable Sub F-to-P
            ScalerSetBit(P31_16_FC_EO_LINE_CTRL1, ~_BIT7, _BIT7);
        }
        else
        {
            if(ScalerFmtCnvGetSub3VSyncDelayType() == _FC_SUB3_VS_DELAY_FROM_SUB1)
            {
                // Use S1 VS delay enable control S3
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT0, 0x00);
            }

            // Disable E/O interlace Vst control; Disable VS delay 8 line; Disable extended DEN
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetBit(P31_12_FC_CLK_CTRL, ~_BIT7, 0x00);

            // Set E/O H width to 0
            ScalerFmtCnvP4P5SetEvenOddHwidth(0);

            // Disable Sub F-to-P
            ScalerSetBit(P31_16_FC_EO_LINE_CTRL1, ~_BIT7, 0x00);
        }
    }
#endif

    if((bEnable == _ENABLE) && (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE))
    {
#if(_COLOR_IP_3DDI == _ON)
        if(GET_3DDI_STATUS(enumInputDataPath) == _OFF)
#endif
        {
            // Set interlace for E/O mode
            ScalerFmtCnvFtoPInterlaceSetting(enumInputDataPath);
        }
    }
}

//--------------------------------------------------
// Description  : Set even/odd resolution
// Input Value  : enumInputPort --> input port
//                enumInputDataPath --> target input path
//                usHwidth  --> H resolution for even/odd
//                usVstart  --> V resolution for even/odd
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPSetFifo(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath, WORD usHwidth, WORD usVstart)
{
    enumInputPort = enumInputPort;

    if((enumInputDataPath & _INPUT_PATH_M1_M2) != 0x00)
    {
        if((LOBYTE(usVstart) & _BIT0) == _BIT0)
        {
            // Set vertical start field = even
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT4, _BIT4);
        }
        else
        {
            // Set vertical start field = odd
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT4, 0x00);
        }

        // Toggle vertical start field for VS bypass
        if(ScalerGetBit(P0_11_M1_VGIP_SIGINV, _BIT6) == _BIT6)
        {
            ScalerSetByte(P31_06_FC_EO_LINE_CTRL, (ScalerGetByte(P31_06_FC_EO_LINE_CTRL) ^ _BIT4));
        }

        // Set horizontal width
        ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHwidth) & 0x1F));
        ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, LOBYTE(usHwidth));
    }

#if((_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON))
    if((enumInputDataPath & _INPUT_PATH_S1_S2) != 0x00)
    {
        if((LOBYTE(usVstart) & _BIT0) == _BIT0)
        {
            // Set vertical start field = even
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT0, _BIT0);
        }
        else
        {
            // Set vertical start field = odd
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT0, 0x00);
        }

        // Toggle vertical start field for VS bypass
        if(ScalerGetBit(P80_11_S1_VGIP_SIGINV, _BIT6) == _BIT6)
        {
            ScalerSetByte(P31_06_FC_EO_LINE_CTRL, (ScalerGetByte(P31_06_FC_EO_LINE_CTRL) ^ _BIT0));
        }

        // Set horizontal width
        ScalerSetBit(P31_09_FC_FORMAT_PRO_SUB_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHwidth) & 0x1F));
        ScalerSetByte(P31_0A_FC_FORMAT_PRO_SUB_1, LOBYTE(usHwidth));
    }
#endif

#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
    if((enumInputDataPath & _INPUT_PATH_S3_S4) != 0x00)
    {
        if((LOBYTE(usVstart) & _BIT0) == _BIT0)
        {
            // Set vertical start field = even
            ScalerSetBit(P31_16_FC_EO_LINE_CTRL1, ~_BIT4, _BIT4);
        }
        else
        {
            // Set vertical start field = odd
            ScalerSetBit(P31_16_FC_EO_LINE_CTRL1, ~_BIT4, 0x00);
        }

        // Toggle vertical start field for VS bypass
        if(ScalerGetBit(P17_11_S3_VGIP_SIGINV, _BIT6) == _BIT6)
        {
            ScalerSetByte(P31_16_FC_EO_LINE_CTRL1, (ScalerGetByte(P31_16_FC_EO_LINE_CTRL1) ^ _BIT4));
        }

        // Set horizontal width
        ScalerFmtCnvP4P5SetEvenOddHwidth(usHwidth);
    }
#endif
}

#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Path4 & Path5 Even/ Odd Hwidth
// Input Value  : usHwidth  --> H resolution for even/odd
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvP4P5SetEvenOddHwidth(WORD usHwidth)
{
    ScalerSetBit(P31_17_FC_FORMAT_PRO_S3_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHwidth) & 0x1F));
    ScalerSetByte(P31_18_FC_FORMAT_PRO_S3_1, LOBYTE(usHwidth));
}
#endif
#endif

//--------------------------------------------------
// Description  : Check conditions for E/O mode or single path mode
// Input Value  : enumInputDataPath --> input data path
// Output Value : _FALSE to enter even/odd mode setting flow; _TRUE to skip even/odd.
//--------------------------------------------------
bit ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;
    return _FALSE;
}

//--------------------------------------------------
// Description  : Show format conversion input port type
// Input Value  : enumInputDataPath -> input data path
// Output Value : input port
//--------------------------------------------------
EnumInputPort ScalerFmtCnvGetInputPortType(EnumInputDataPath enumInputDataPath)
{
    EnumInputPort penumPortTable[] =
    {
        _A0_INPUT_PORT,
        _D0_INPUT_PORT,
        _D1_INPUT_PORT,
        _D2_INPUT_PORT,
        _D3_INPUT_PORT,
        _D4_INPUT_PORT,
        _D5_INPUT_PORT,
        _D7_INPUT_PORT,
        _D8_INPUT_PORT,
    };

    EnumFormatConversionSourceType enumSourceType = ScalerFmtCnvGetSourceType(enumInputDataPath);
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < sizeof(penumPortTable) / sizeof(penumPortTable[0]); ++ucIndex)
    {
        // Matching FC source type with each port
        if(ScalerFmtCnvConvertPortType(penumPortTable[ucIndex]) == enumSourceType)
        {
            return penumPortTable[ucIndex];
        }
    }

    // No match source type found
    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Initialize CTS fifo for format conversion
// Input Value  : enumInputDataPath -> target input data path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvCtsFifoInitSetting(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

    // Enable read-index reset automatically for CTS fifo; Clear unstable bits
#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    ScalerSetBit(P31_76_CTS_FIFO_CTRL, ~(_BIT4 | _BIT2 | _BIT0), (_BIT2 | _BIT0));
#endif
    ScalerSetBit(P31_10_FC_EXT_CTRL, ~(_BIT1 | _BIT0), _BIT0);
#else
    ScalerSetBit(P31_76_CTS_FIFO_CTRL, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));
    ScalerSetBit(P31_76_CTS_FIFO_CTRL, ~(_BIT5 | _BIT4 | _BIT0), (_BIT0));
    ScalerSetBit(P31_10_FC_EXT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT0);
    ScalerSetBit(P31_10_FC_EXT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
#endif
}

//--------------------------------------------------
// Description  : Set background color status for format conversion
// Input Value  : enumInputDataPath --> input path
//                bEnable -> _TRUE to enable format conversion background
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetBackgroundStatus(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    bEnable = bEnable;

#if(_HW_I_DOMAIN_M1_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_M1) != 0)
    {
        // M1 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT3, ((bEnable == _TRUE) ? _BIT3 : 0x00));
    }
#endif

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_M2) != 0)
    {
        // M2 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT2, ((bEnable == _TRUE) ? _BIT2 : 0x00));
    }
#endif

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_S1) != 0)
    {
        // S1 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT1, ((bEnable == _TRUE) ? _BIT1 : 0x00));
    }
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_S2) != 0)
    {
        // S2 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT0, ((bEnable == _TRUE) ? _BIT0 : 0x00));
    }
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_S3) != 0)
    {
        // S3 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT4, ((bEnable == _TRUE) ? _BIT4 : 0x00));
    }
#endif

#if(_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_S4) != 0)
    {
        // S3 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT5, ((bEnable == _TRUE) ? _BIT5 : 0x00));
    }
#endif
}

//--------------------------------------------------
// Description  : Set background color for format conversion
// Input Value  : enumInputDataPath --> input path
//                ucR --> R color
//                ucG --> G color
//                ucB --> B color
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetBackgroundColor(EnumInputDataPath enumInputDataPath, BYTE ucR, BYTE ucG, BYTE ucB)
{
    enumInputDataPath = enumInputDataPath;
    ucR = ucR;
    ucG = ucG;
    ucB = ucB;

#if(_HW_I_DOMAIN_M1_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_M1) != 0)
    {
        ScalerSetByte(P31_51_PORCH_COLOR_R_M1, ucR);
        ScalerSetByte(P31_52_PORCH_COLOR_G_M1, ucG);
        ScalerSetByte(P31_53_PORCH_COLOR_B_M1, ucB);
    }
#endif

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_M2) != 0)
    {
        ScalerSetByte(P31_54_PORCH_COLOR_R_M2, ucR);
        ScalerSetByte(P31_55_PORCH_COLOR_G_M2, ucG);
        ScalerSetByte(P31_56_PORCH_COLOR_B_M2, ucB);
    }
#endif

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_S1) != 0)
    {
        ScalerSetByte(P31_57_PORCH_COLOR_R_S1, ucR);
        ScalerSetByte(P31_58_PORCH_COLOR_G_S1, ucG);
        ScalerSetByte(P31_59_PORCH_COLOR_B_S1, ucB);
    }
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_S2) != 0)
    {
        ScalerSetByte(P31_5A_PORCH_COLOR_R_S2, ucR);
        ScalerSetByte(P31_5B_PORCH_COLOR_G_S2, ucG);
        ScalerSetByte(P31_5C_PORCH_COLOR_B_S2, ucB);
    }
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_S3) != 0)
    {
        ScalerSetByte(P31_5D_PORCH_COLOR_R_S3, ucR);
        ScalerSetByte(P31_5E_PORCH_COLOR_G_S3, ucG);
        ScalerSetByte(P31_5F_PORCH_COLOR_B_S3, ucB);
    }
#endif

#if(_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _INPUT_PATH_S4) != 0)
    {
        ScalerSetByte(P31_4D_PORCH_COLOR_R_S4, ucR);
        ScalerSetByte(P31_4E_PORCH_COLOR_G_S4, ucG);
        ScalerSetByte(P31_4F_PORCH_COLOR_B_S4, ucB);
    }
#endif
}

//--------------------------------------------------
// Description  : Assign source type for specific input data path
// Input Value  : enumInputDataPath --> target input path
//                enumFormatConversionSourceType --> target source type
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetSourceType(EnumInputDataPath enumInputDataPath, EnumFormatConversionSourceType enumFormatConversionSourceType)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        // Set path 0
        ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumFormatConversionSourceType << 4));

#if(_HW_FORMAT_CONVERSION_CLK_GATED_SUPPORT == _ON)
        // Disable clock gating
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT0, _BIT0);
#endif
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        // Set path 1
        ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumFormatConversionSourceType);

#if(_HW_FORMAT_CONVERSION_CLK_GATED_SUPPORT == _ON)
        // Disable clock gating
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT1, _BIT1);
#endif
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        // Set path 2
        ScalerSetBit(P31_01_FC_INPUT_SEL_P23, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumFormatConversionSourceType << 4));

#if(_HW_FORMAT_CONVERSION_CLK_GATED_SUPPORT == _ON)
        // Disable clock gating
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT2, _BIT2);
#endif
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        // Set path 3
        ScalerSetBit(P31_01_FC_INPUT_SEL_P23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumFormatConversionSourceType);

#if(_HW_FORMAT_CONVERSION_CLK_GATED_SUPPORT == _ON)
        // Disable clock gating
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT3, _BIT3);
#endif
    }
#endif
}

//--------------------------------------------------
// Description  : Enable/disable format conversion VS latch
// Input Value  : enumInputDataPath --> selected path
//                bEnable --> _ENABLE to enable VS bypass
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT0, 0x00);
        }
        else
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT0, _BIT0);
        }
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT1, 0x00);
        }
        else
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT1, _BIT1);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT2, 0x00);
        }
        else
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT2, _BIT2);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        if(bEnable == _ENABLE)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT3, 0x00);
        }
        else
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT3, _BIT3);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Check format conversion HS Pulse expand
// Input Value  : enumInputDataPath --> selected path
//                usHSwidth --> input hsync pulse width
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvCheckHsExpandEnable(EnumInputDataPath enumInputDataPath, WORD usHSwidth)
{
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        if(usHSwidth < _FMTCNV_HS_PULSE_WIDTH_MIN_VALUE)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT4, _BIT4);
            SET_INPUT_TIMING_HSYNCWIDTH(_FMTCNV_HS_PULSE_WIDTH_MIN_VALUE);
        }
        else
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT4, 0x00);
        }
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        if(usHSwidth < _FMTCNV_HS_PULSE_WIDTH_MIN_VALUE)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT5, _BIT5);
            SET_INPUT_TIMING_HSYNCWIDTH(_FMTCNV_HS_PULSE_WIDTH_MIN_VALUE);
        }
        else
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT5, 0x00);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        if(usHSwidth < _FMTCNV_HS_PULSE_WIDTH_MIN_VALUE)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT6, _BIT6);
            SET_INPUT_TIMING_HSYNCWIDTH(_FMTCNV_HS_PULSE_WIDTH_MIN_VALUE);
        }
        else
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT6, 0x00);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        if(usHSwidth < _FMTCNV_HS_PULSE_WIDTH_MIN_VALUE)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT7, _BIT7);
            SET_INPUT_TIMING_HSYNCWIDTH(_FMTCNV_HS_PULSE_WIDTH_MIN_VALUE);
        }
        else
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT7, 0x00);
        }
    }
#endif
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get format conversion F/B Full to FB status
// Input Value  : None
// Output Value : _TRUE if format full-to-FB mode is enabled
//--------------------------------------------------
bit ScalerFmtCnvFBGetFullToFBStatus(void)
{
    return (ScalerGetBit(P31_60_FRONT_BACK_CTRL, _BIT6) == _BIT6);
}

//--------------------------------------------------
// Description  : Get format conversion FB mode status
// Input Value  : None
// Output Value : _TRUE if format conversion FB mode is enabled
//--------------------------------------------------
bit ScalerFmtCnvFBGetFBModeStatus(void)
{
    return (ScalerGetBit(P31_60_FRONT_BACK_CTRL, _BIT7) == _BIT7);
}

//--------------------------------------------------
// Description  : Final format conversion setting
// Input Value  : enumInputPort --> input port
//                enumInputDataPath --> input path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFBFinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath)
{
    WORD usHstart = 0;
    BYTE ucHwidthRatio = 0x04;

    enumInputPort = enumInputPort;
    enumInputDataPath = enumInputDataPath;

#if(_DUAL_DP_SUPPORT == _ON)
    if((enumInputPort == _DUAL_DP_INPUT_PORT) &&
       (GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_INPUT_PORT))
    {
        ScalerFmtCnvSetDualDpSourceType();

        // Enable F/B
        ScalerFmtCnvFBSetStatus(_FB_ON);

        // H start limit = H blanking / 2
        usHstart = (GET_INPUT_TIMING_HTOTAL() - GET_INPUT_TIMING_HWIDTH()) / 2;
    }
    else
#endif
    {
        // Enable full-to-F/B
        ScalerFmtCnvFBSetStatus(_FB_FULL_TO_FB);

        // H start limit = H blanking / 4
        usHstart = (GET_INPUT_TIMING_HTOTAL() - GET_INPUT_TIMING_HWIDTH()) / 4;
    }

    // Set max H start to 0x1E
    if(usHstart > 0x1E)
    {
        usHstart = 0x1E;
    }

#if(_COLOR_IP_420_SUPPORT == _ON)
    // Double H width for 420 format
    if(ScalerColor420To422GetStatusByPath(enumInputDataPath) == _TRUE)
    {
        ucHwidthRatio *= 2;
    }
#endif

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    // Apply 1/2 SD factor
    ucHwidthRatio /= ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif

    // Set F/B format
    ScalerFmtCnvFBSetOutputFormat(GET_INPUT_TIMING_HWIDTH() * ucHwidthRatio / 0x04, usHstart, usHstart - 2);
}

//--------------------------------------------------
// Description  : Set initial format conversion extension value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFBSetInitialExtension(void)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
    {
        SET_FMTCNV_EXTENSION_LEN(ScalerFmtCnvAdjustExtensionLen());
    }
    else
    {
        // Reset format conversion extension
        SET_FMTCNV_EXTENSION_LEN(0);
    }
}

//--------------------------------------------------
// Description  : Set format conversion output format
// Input Value  : usHwidth --> target H width
//                ucHstart --> target H start
//                ucHSwidth --> target HS width
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFBSetOutputFormat(WORD usHwidth, BYTE ucHstart, BYTE ucHSwidth)
{
    ScalerSetBit(P31_61_FULLTOFB_HWIDTH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHwidth) & 0x3F));
    ScalerSetByte(P31_62_FULLTOFB_HWIDTH_L, LOBYTE(usHwidth));

    ScalerSetByte(P31_67_FB_OUT_HSYNC_WIDTH, ucHSwidth);
    ScalerSetByte(P31_68_FB_OUT_HSTART, ucHstart);
}

//--------------------------------------------------
// Description  : Set format conversion F/B status
// Input Value  : enumFrontBackMode -> F/B mode setting
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFBSetStatus(EnumFrontBackMode enumFrontBackMode)
{
    ScalerSetBit(P31_60_FRONT_BACK_CTRL, ~(_BIT7 | _BIT6), enumFrontBackMode);
}

//--------------------------------------------------
// Description  : Adjust extension by Input/display hwidth
// Input Value  : none
// Output Value : Extension number
//--------------------------------------------------
BYTE ScalerFmtCnvAdjustExtensionLen(void)
{
    BYTE ucExtension = _FMTCNV_EXTENSION_DEFAULT;

    if(((GET_MDOMAIN_INPUT_HWIDTH() / 2) % 2) == 0) // Input Hwidth + Extention must be even.
    {
        return ucExtension;
    }
    else
    {
        return (ucExtension - 1);
    }
}
#endif
#endif // End of #if(_FORMAT_CONVERSION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get even/odd enabled status for specified path
// Input Value  : enumInputDataPath --> target input data path
// Output Value : _TRUE if even/odd mode is enabled
//--------------------------------------------------
bit ScalerFmtCnvFtoPGetStatus(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    switch(enumInputDataPath)
    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        case _INPUT_PATH_M1_M2_S1_S2:
#endif
        case _INPUT_PATH_M1_M2:
            return (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT7) == _BIT7);

#if((_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON) &&\
    (_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON))
        case _INPUT_PATH_S1_S2:
            return (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT3) == _BIT3);
#endif

#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) &&\
    (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
        case _INPUT_PATH_S3_S4:
            return (ScalerGetBit(P31_16_FC_EO_LINE_CTRL1, _BIT7) == _BIT7);
#endif


        default:
            break;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Show format conversion input source
// Input Value  : enumInputDataPath --> target input data path
// Output Value : format conversino source
//--------------------------------------------------
EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(EnumInputDataPath enumInputDataPath)
{
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(enumInputDataPath);

    if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
    {
        return (EnumFormatConversionSourceType)(ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
    {
        return (EnumFormatConversionSourceType)(ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
    {
        return (EnumFormatConversionSourceType)(ScalerGetBit(P31_01_FC_INPUT_SEL_P23, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
    if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
    {
        return (EnumFormatConversionSourceType)(ScalerGetBit(P31_01_FC_INPUT_SEL_P23, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
    }
#endif
#endif

    enumInputDataPath = enumInputDataPath;

    return _FC_SOURCE_NONE;
}
