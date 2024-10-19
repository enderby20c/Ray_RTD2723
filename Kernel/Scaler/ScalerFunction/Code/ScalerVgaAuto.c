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
// ID Code      : ScalerVgaAuto.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_VGA_AUTO__

#include "ScalerFunctionInclude.h"
#include "VgaAuto/ScalerVgaAuto.h"


#if(_VGA_SUPPORT == _ON)
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
// Description  : ADC AutoWhiteBalance
// Input Value  : enumAutoType -> auto color for RGB / YPbPr / Self-calibration
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoDoWhiteBalance(EnumAutoColorType enumAutoType)
{
    EnumAutoResult enumResult = 0;
    BYTE ucAdcSwapStatus = 0;
    BYTE ucClampEnd = 0;

#if(_VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT == _ON)
    // Disable SF bandwidth
    ScalerSetBit(P0_C8_ADC_SF_CTRL, ~_BIT5, 0x00);
#endif

    // Set measure index
    if(ScalerMeasureSetSourceResultIndex(_FC_SOURCE_ADC) == _FALSE)
    {
        return _AUTO_FAIL;
    }

    // Store ADC channel swapping, and clamp end
    ucAdcSwapStatus = ScalerGetBit(P30_A6_VGATOP_IPH_ACT_WID_H, (_BIT6 | _BIT5 | _BIT4));
    ucClampEnd = ScalerGetDataPortSingleByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_01_G_CLAMP_END);

    // Initialization for auto-color
    ScalerVgaAutoInitializeAutoColor(enumAutoType);

    // Perform auto-color process
    enumResult = ScalerVgaAutoBalanceHandler(enumAutoType);

#if(_ADC_SELF_CALIBRATION == _ON)
    ScalerVgaAutoResetCalibration();
#endif

    // Restore ADC channel swapping
    ScalerSetBit(P30_A6_VGATOP_IPH_ACT_WID_H, ~(_BIT6 | _BIT5 | _BIT4), ucAdcSwapStatus);

    // Restore ADC clamp end; Disable clamp before adjustment
    ScalerSetBit(P0_48_SYNC_INVERT, ~_BIT2, 0x00);
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_01_G_CLAMP_END, ucClampEnd);
    ScalerSetBit(P0_48_SYNC_INVERT, ~_BIT2, _BIT2);

    return enumResult;
}

//--------------------------------------------------
// Description  : ADC Auto Balance for RGB / YPbPr color spaces
// Input Value  : enumAutoType: RGB / YPBPR / self-calibration
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoBalanceHandler(EnumAutoColorType enumAutoType)
{
    BYTE ucIndex = 0;
    BYTE ucTarget = 16;
    BYTE ucABLFrame = 2;
    BYTE ucGainBias = 5;
    BYTE ucStepRatio = 1;
    FUNC_PTR_UPDATE_GAIN pfnUpdateGain = &ScalerVgaAutoUpdateAdcGain;
    FUNC_PTR_COMPENSATE pfnCompensate = &ScalerVgaAutoCompensateRGB;

    // Select functions to update gain & compensate
    switch(enumAutoType)
    {
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        case _AUTO_TUNE_YPBPR:
            pfnUpdateGain = &ScalerVgaAutoUpdateAdcGain;
            pfnCompensate = &ScalerVgaAutoCompensateYPbPr;
            break;

        case _AUTO_TUNE_YPBPR_GAIN_ONLY:
            pfnUpdateGain = &ScalerVgaAutoUpdateAdcGainOnly;
            pfnCompensate = &ScalerVgaAutoCompensateYPbPr;
            break;
#endif
#if(_ADC_SELF_CALIBRATION == _ON)
        case _AUTO_CALIBRATE_RGB:
            pfnUpdateGain = &ScalerVgaAutoUpdateAdcGainCalibrationRGB;
            pfnCompensate = &ScalerVgaAutoCompensateCalibrationRGB;
            break;
#endif

        case _AUTO_TUNE_RGB_KNOWNWHITE:
            pfnUpdateGain = &ScalerVgaAutoCustomUpdateAdcGain;
            pfnCompensate = &ScalerVgaAutoCompensateRGB;
            break;

        case _AUTO_TUNE_RGB:
            break;

        case _AUTO_TUNE_RGB_GAIN_ONLY:
            pfnUpdateGain = &ScalerVgaAutoUpdateAdcGainOnly;
            pfnCompensate = &ScalerVgaAutoCompensateRGB;
            break;

        default:
            return _AUTO_FAIL;
    }

    for(ucIndex = 0; ucIndex < _AUTO_COLOR_END; ++ucIndex)
    {
        if((enumAutoType != _AUTO_TUNE_RGB_GAIN_ONLY) &&
           (enumAutoType != _AUTO_TUNE_YPBPR_GAIN_ONLY))
        {
            // Adjust offset by ABL
            if(ScalerVgaAutoHardwareAbl(ucTarget, ucABLFrame) == _AUTO_FAIL)
            {
                return _AUTO_FAIL;
            }
        }

        // Adjust gain by auto-function
        if(pfnUpdateGain(ucGainBias, ucStepRatio) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }

        // Auto-tuning process control
        switch(ucIndex)
        {
            case _AUTO_COLOR_TUNING:
                if(enumAutoType != _AUTO_TUNE_YPBPR)
                {
                    ucTarget = 4;
                }
                ucGainBias = 3;
                ucABLFrame = ((enumAutoType == _AUTO_CALIBRATE_RGB) ? 2 : 1);
                break;

            case _AUTO_COLOR_STAGE1:
            case _AUTO_COLOR_STAGE2:
                // Do nothing
                break;

            case _AUTO_COLOR_COMPENSTE:
            default:
                if(pfnCompensate(enumAutoType) == _AUTO_FAIL)
                {
                    return _AUTO_FAIL;
                }
                break;
        }
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Initialization for auto-color process
// Input Value  : enumAutoType: initialize type for auto-color
// Output Value : none
//--------------------------------------------------
void ScalerVgaAutoInitializeAutoColor(EnumAutoColorType enumAutoType)
{
    BYTE ucClampEnd = 0;

#if(_ADC_SELF_CALIBRATION == _ON)
    if(enumAutoType == _AUTO_CALIBRATE_RGB)
    {
        // Enable calibration related setting
        ScalerVgaAutoInitializeCalibration();
    }
    else
    {
        // Disable calibration voltage
        ScalerVgaAutoResetCalibration();
    }
#endif

    // Enlarge clamp end
    PDATA_WORD(0) = GET_INPUT_TIMING_HSYNCWIDTH();
    PDATA_WORD(1) = PDATA_WORD(0); // Record H-Sync Pulse Width
    PDATA_WORD(0) = ((GET_VGA_MODE_HSTART() - PDATA_WORD(0)) >> 1);
    ucClampEnd = MINOF(PDATA_WORD(0), 128);
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_01_G_CLAMP_END, ucClampEnd);

    // Load default ADC gain
    ScalerSetByte(P0_C0_ADC_GAI_RED_MSB, _DEFAULT_GAIN);
    ScalerSetByte(P0_C1_ADC_GAI_GRN_MSB, _DEFAULT_GAIN);
    ScalerSetByte(P0_C2_ADC_GAI_BLU_MSB, _DEFAULT_GAIN);
    ScalerSetBit(P0_BE_ADC_GAI_LSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Load default ADC offset
    if((enumAutoType != _AUTO_TUNE_RGB_GAIN_ONLY) && (enumAutoType != _AUTO_TUNE_YPBPR_GAIN_ONLY))
    {
        ScalerSetByte(P0_C3_ADC_OFF_RED_MSB, _DEFAULT_OFFSET);
        ScalerSetByte(P0_C4_ADC_OFF_GRN_MSB, _DEFAULT_OFFSET);
        ScalerSetByte(P0_C5_ADC_OFF_BLU_MSB, _DEFAULT_OFFSET);
        ScalerSetBit(P0_BF_ADC_OFF_LSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P0_D3_ADC_OFF_LSB2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }

    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);
    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

    // Disable ADC channel swapping
    ScalerSetBit(P30_A6_VGATOP_IPH_ACT_WID_H, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set ABL vertical start; Average 4 lines
    pData[0] = ((GET_VGA_MODE_VSTART() / 2) > 8) ? 8 : ((GET_VGA_MODE_VSTART() / 2) + 1);
    ScalerSetByte(P0_E3_AUTO_BLACK_LEVEL_CTRL2, (_BIT5 | (pData[0] & 0x1F)));

    // Select RGB or YPbPr mode; Off-line ABL; 64-pixels in each line; Clear status;
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((enumAutoType == _AUTO_TUNE_YPBPR) ? (_BIT7 | _BIT5) : (_BIT5)));

    // ABL starts at 4 pixels after the reference signal in each line
    ScalerSetByte(P0_E6_AUTO_BLACK_LEVEL_CTRL5, (PDATA_WORD(1) + ucClampEnd + 4));
    ScalerSetBit(P0_EF_AUTO_BLACK_LEVEL_CTRL8, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00); // EQ condition old mode

    // ABL old mode
    ScalerSetBit(P0_EC_AUTO_BLACK_LEVEL_R_NOISE_VALUE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Trigger status after max frame reached; Average value; HS trailing edge; EQ_MGN(0~3) = 0
    ScalerSetBit(P0_E8_AUTO_BLACK_LEVEL_CTRL7, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // Max frame/field count = 7; H width x1;
    ScalerSetBit(P0_E7_AUTO_BLACK_LEVEL_CTRL6, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
}

//--------------------------------------------------
// Description  : Update ADC gain for RGB / YPbPr color space
// Input Value  : ucGainBias: bias for RGB max level
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoUpdateAdcGain(BYTE ucGainBias, BYTE ucStepRatio)
{
    BYTE ucGain = 0;
    BYTE ucMax = 0;
    BYTE ucIndex = 0;

    // Set to R channel for auto-balance new mode
    SET_AUTO_ADC_CHANNEL(_AUTO_RED_CHANNEL);

    // Enable image auto-balance new mode
    ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~_BIT0, _BIT0);

    // Enable 121-LPF
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~_BIT5, _BIT5);

    if(ScalerVgaAutoCompareMeasure(_MEASURE_MAX) == _AUTO_FAIL)
    {
        ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~_BIT0, 0);
        return _AUTO_FAIL;
    }

    for(ucIndex = 0; ucIndex < 3; ++ucIndex)
    {
        ucGain = ScalerGetByte(P0_C0_ADC_GAI_RED_MSB + ucIndex);
        ucMax = ScalerGetByte(P30_D4_VGATOP_AUTO_PHASE_3 + ucIndex);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        if(GET_TUNE_YPBPR_STATUS() == _TRUE)
        {
            if(ucIndex == 1)
            {
                pData[0] = _AUTO_Y_MAX_LEVEL - ucGainBias; // Y max level
            }
            else
            {
                pData[0] = _AUTO_PBPR_MAX_LEVEL - ucGainBias; // Pb/Pr max level
            }
        }
        else
#endif
        {
            pData[0] = _AUTO_RGB_MAX_LEVEL - ucGainBias; // RGB max level
        }

        // Check source validity; More consider needed
        if(ucMax < _ADC_MAXIMUM_TOLERANCE)
        {
            return _AUTO_FAIL;
        }

        // Update ADC gain according to max level & measured maximum
        if(ucMax < pData[0])
        {
            // Calculate gain step
            pData[1] = ScalerVgaAutoConvertAdcGainStep(ucGain, pData[0], ucMax) / ucStepRatio;

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
            if((GET_TUNE_YPBPR_STATUS() == _TRUE) && (ucIndex != 1))
            {
                // Gain step = STEP(1.75) for Pb/Pr channels
                pData[1] = (BYTE)(((WORD)pData[1] << 1) - (pData[1] >> 2));
            }
#endif
            // Minimum gain step = 1
            if(pData[1] == 0)
            {
                pData[1] = 1;
            }

            // Decrease gain with underflow check
            if(ucGain >= pData[1])
            {
                ucGain -= pData[1];
            }
            else
            {
                ucGain = 0;
            }
        }
        else
        {
            // Target value exceeded. Rewind gain.
            pData[1] = (ucMax - pData[0]);

            // Increase gain with overflow check
            if(((WORD)ucGain + pData[1]) > 0xFF)
            {
                ucGain = 0xFF;
            }
            else
            {
                ucGain += pData[1];
            }
        }

        ScalerSetByte(P0_C0_ADC_GAI_RED_MSB + ucIndex, ucGain);
    }

    // Disaable image auto-balance new mode
    ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~_BIT0, 0);

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Update ADC gain only for RGB / YPbPr color space
// Input Value  : ucGainBias: bias for RGB max level
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoUpdateAdcGainOnly(BYTE ucGainBias, BYTE ucStepRatio)
{
    ucStepRatio *= 2;

    if((ScalerVgaAutoUpdateAdcGain(ucGainBias, ucStepRatio) == _AUTO_FAIL) ||
       (ScalerVgaAutoUpdateAdcGain(ucGainBias, ucStepRatio) == _AUTO_FAIL))
    {
        return _AUTO_FAIL;
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Color compensating for RGB channels
// Input Value  : enumAutoType -> auto-color type
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoCompensateRGB(EnumAutoColorType enumAutoType)
{
    if(ScalerVgaAutoCompensateChannel(_AUTO_RED_CHANNEL, enumAutoType) == _AUTO_SUCCESS)
    {
        if(ScalerVgaAutoCompensateChannel(_AUTO_GREEN_CHANNEL, enumAutoType) == _AUTO_SUCCESS)
        {
            if(ScalerVgaAutoCompensateChannel(_AUTO_BLUE_CHANNEL, enumAutoType) == _AUTO_SUCCESS)
            {
                return _AUTO_SUCCESS;
            }
        }
    }

    return _AUTO_FAIL;
}

//--------------------------------------------------
// Description  : Use ABL function to measure 256 pixels in the porch region and adjust offset accordingly
// Input Value  : ucTarget -> target value for ABL (1~16)
//                ucFrameCount -> total frame for ABL excution (1~7)
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoHardwareAbl(BYTE ucTarget, BYTE ucFrameCount)
{
    // Disable ABL
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set target value
    ScalerSetBit(P0_E4_AUTO_BLACK_LEVEL_CTRL3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((ucTarget - 1) << 4));

    // Reset ABL flag
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2 | _BIT1));

    // Start ABL
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // For frame count = 0, wait 1 IVS
    if(ucFrameCount == 0x00)
    {
        ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);
    }

    // Wait until target frame count reached
    pData[0] = 0; // Valid frame counter
    pData[1] = 0; // Total frame counter
    while(pData[0] < ucFrameCount)
    {
        if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) || ((++pData[1]) > 8))
        {
            return _AUTO_FAIL;
        }

        // Check target value status
        if((ScalerGetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, (_BIT3 | _BIT2 | _BIT1)) == (_BIT3 | _BIT2 | _BIT1)) ||
           (ScalerGetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, _BIT0) == 0x00))
        {
            break;
        }

        // Check black level saturation
        if((ScalerGetByte(P0_E9_AUTO_BLACK_LEVEL_RED_VALUE) == 0x00) || (ScalerGetByte(P0_EA_AUTO_BLACK_LEVEL_GREEN_VALUE) == 0x00) || (ScalerGetByte(P0_EB_AUTO_BLACK_LEVEL_BLUE_VALUE) == 0x00))
        {
            continue;
        }
        else
        {
            ++pData[0];
        }
    }

    // Wait additional 0.5 frame (for 60Hz)
    ScalerTimerDelayXms(9);

    // Stop ABL
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Wait until ABL stop
    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

    // Reset ADC offset LSB
    ScalerSetBit(P0_BF_ADC_OFF_LSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Further offset adjustment is needed only for RGB
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
    if(GET_TUNE_YPBPR_STATUS() == _FALSE)
#endif
    {
        --ucTarget;
        ScalerSetByte(P0_C3_ADC_OFF_RED_MSB, (ScalerGetByte(P0_C3_ADC_OFF_RED_MSB) + ucTarget));
        ScalerSetByte(P0_C5_ADC_OFF_BLU_MSB, (ScalerGetByte(P0_C5_ADC_OFF_BLU_MSB) + ucTarget));
        ScalerSetByte(P0_C4_ADC_OFF_GRN_MSB, (ScalerGetByte(P0_C4_ADC_OFF_GRN_MSB) + ucTarget));
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Calculate ADC gain/offset according to SHA gain
// Input Value  : ucGain    -> ADC gain value
//                ucTarget  -> target level
//                ucCurrent -> measured current status
// Output Value : converted gain step
//--------------------------------------------------
BYTE ScalerVgaAutoConvertAdcGainStep(BYTE ucGain, BYTE ucTarget, BYTE ucCurrent)
{
    BYTE ucResult = 0;

    if(ucTarget > ucCurrent)
    {
        ucResult = (BYTE)(((DWORD)(ucTarget - ucCurrent) * ((WORD)ucGain + 252)) / ucTarget);
    }

    return ucResult;
}

//--------------------------------------------------
// Description  : Color compensation for a particular ADC channel
// Input Value  : ucColor -> select a color channel
//                enumAutoType -> auto-color type
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoCompensateChannel(BYTE ucColor, EnumAutoColorType enumAutoType)
{
    BYTE ucMainTone = 0;
    BYTE ucGain = 0;

    // Set channel for image auto-function
    SET_AUTO_ADC_CHANNEL(ucColor);
    ucGain = GET_AUTO_ADC_GAIN();

    // Measure main-tone for max
    if(ScalerVgaAutoMainToneMeasure(255, &ucMainTone) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    if(enumAutoType == _AUTO_TUNE_RGB_GAIN_ONLY)
    {
        // Measure the average min value
        if(ScalerVgaAutoAccumulationMeasure(_MEASURE_RGB_MIN, 0) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }
    }
    else
    {
        // Compensate offset
        if(ScalerVgaAutoCompensateOffset(ucColor) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }
    }

    // Update gain from swing = main-tone for max - average min
    pData[0] = ScalerVgaAutoConvertAdcGainStep(ucGain, 255, HIBYTE(((WORD)ucMainTone << 8) - GET_AUTO_RESULT_WORD0()));

    // Decrease gain with underflow check
    if(ucGain >= pData[0])
    {
        ucGain -= pData[0];
    }
    else
    {
        ucGain = 0;
    }
    SET_AUTO_ADC_GAIN(ucGain);

    if(enumAutoType != _AUTO_TUNE_RGB_GAIN_ONLY)
    {
#if(_PANEL_ADC_OFFSET_BIAS < 0)
        BYTE ucOffsetBias = 0;
#elif(_PANEL_ADC_OFFSET_BIAS > _USER_ADJUST_OFFSET_RANGE)
        BYTE ucOffsetBias = _USER_ADJUST_OFFSET_RANGE;
#else
        BYTE ucOffsetBias = _PANEL_ADC_OFFSET_BIAS;
#endif

        // Double-check for offset
        if(ScalerVgaAutoCompensateOffset(ucColor) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }

        // Set gain bias level from current black level
        pData[9] = (GET_AUTO_RESULT_WORD0() > (WORD)_BLACK_LEVEL_THRESHOLD) + ucOffsetBias;

        // Adjust ADC offset by panel defined bias
        // Increase offset with overflow check
        if((WORD)GET_AUTO_ADC_OFFSET() + ucOffsetBias > 0xFF)
        {
            SET_AUTO_ADC_OFFSET(0xFF);
        }
        else
        {
            SET_AUTO_ADC_OFFSET(GET_AUTO_ADC_OFFSET() + ucOffsetBias);
        }

        // Adjust ADC gain by calculated bias
        pData[9] = ScalerVgaAutoConvertAdcGainStep(ucGain, 255, (255 - pData[9]));

        // Decrease gain with underflow check
        if(ucGain >= pData[9])
        {
            SET_AUTO_ADC_GAIN(ucGain - pData[9]);
        }
        else
        {
            SET_AUTO_ADC_GAIN(0);
        }
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Compensation for 0-level
// Input Value  : ucColor: select a color channel
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoCompensateOffset(BYTE ucColor)
{
    BYTE ucOffset = 0;
    WORD usResult = 0;

    SET_AUTO_ADC_CHANNEL(ucColor);
    ucOffset = GET_AUTO_ADC_OFFSET();

    // Measure the average min value
    if(ScalerVgaAutoAccumulationMeasure(_MEASURE_RGB_MIN, 0) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }
    usResult = GET_AUTO_RESULT_WORD0();

    if(HIBYTE(usResult) > 0)
    {
        // Increase offset by (minimum - 1)
        pData[0] = ((HIBYTE(usResult) == 1) ? 1 : (HIBYTE(usResult) - 1));
    }
    else if(usResult > (WORD)_BLACK_LEVEL_THRESHOLD)
    {
        pData[0] = 1;
    }
    else
    {
        pData[0] = 0;
    }

    // Increase offset with overflow check
    if((WORD)ucOffset + pData[0] > 0xFF)
    {
        ucOffset = 0xFF;
    }
    else
    {
        ucOffset += pData[0];
    }

    SET_AUTO_ADC_OFFSET(ucOffset);
    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Set boundary for image auto-function measure
// Input Value  : enumBoundary -> boundary type selection
// Output Value : None
//--------------------------------------------------
void ScalerVgaAutoSetBoundary(EnumMeasureBoundary enumBoundary)
{
    switch(enumBoundary)
    {
        case _MEASURE_PORCH_REGION:
            ScalerVgaTopAutoFuncHBoundInitial(GET_VGA_MODE_HSTART(), (GET_VGA_MODE_HSTART() + 127));

            PDATA_WORD(0) = ((GET_VGA_MODE_VSTART() / 2) > 8) ? 8 : ((GET_VGA_MODE_VSTART() / 2) + 1); // V start
            ScalerVgaTopAutoFuncVBoundInitial(PDATA_WORD(0), (PDATA_WORD(0) + 1));
            break;

        case _MEASURE_ACTIVE_REGION:
            ScalerVgaTopAutoFuncHBoundInitial(GET_VGA_MODE_HSTART(), (GET_VGA_MODE_HSTART() + GET_INPUT_TIMING_HWIDTH()));
            ScalerVgaTopAutoFuncVBoundInitial(GET_VGA_MODE_VSTART(), (GET_VGA_MODE_VSTART() + GET_INPUT_TIMING_VHEIGHT()));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Measure the maximum / minimum value using compare measure
// Input Value  : enumType -> measure for maximum / minimum value
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoCompareMeasure(EnumMeasureType enumType)
{
    BYTE ucMeasureType = 0;

    // Stop image auto-function measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Disable field select; Disable hardware acceleration;
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT7 | _BIT4), 0x00);

    switch(enumType)
    {
        case _MEASURE_RGB_MIN:
            pData[0] = _MEASURE_PORCH_REGION;
            ucMeasureType = 0;
            break;

        case _MEASURE_YPBPR_MIN:
            pData[0] = _MEASURE_ACTIVE_REGION;
            ucMeasureType = 0;
            break;

        case _MEASURE_MAX:
        default:
            pData[0] = _MEASURE_ACTIVE_REGION;
            ucMeasureType = _BIT5;
            break;
    }

    // Set measure boundary
    ScalerVgaAutoSetBoundary(pData[0]);

    // Normal boundary; Software mode; Measure maximum / minimum; Compare mode; Auto-balance; Start measure;
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (ucMeasureType | _BIT0));

    if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
    {
        return _AUTO_FAIL;
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Measure the maximum / minimum value using compare measure
// Input Value  : enumType -> maximum / minimum measure,
//                ucThreshold  -> threshold for accumulation samples
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoAccumulationMeasure(EnumMeasureType enumType, BYTE ucThreshold)
{
    // Stop image auto-function measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Disable field select; Disable LPF filter; Disable hardware acceleration;
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    switch(enumType)
    {
        case _MEASURE_YPBPR_MIN:
            // Measure the pixel number BELOW the threshold
            ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT5, 0x00);
            ucThreshold ^= 0xFF;
            pData[0] = _MEASURE_ACTIVE_REGION;
            break;

        case _MEASURE_RGB_MIN:
            pData[0] = _MEASURE_PORCH_REGION;
            break;

        case _MEASURE_MAX:
        default:
            pData[0] = _MEASURE_ACTIVE_REGION;
            break;
    }

    // Set measure boundary
    ScalerVgaAutoSetBoundary(pData[0]);

    // Set threshold
    ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, ucThreshold);

    // Normal boundary; Software mode; Measure maximum; Accumulation mode; Auto-balance; Start auto-function
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
    {
        return _AUTO_FAIL;
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Search for ADC main tone between (start_level - 4) & start_level
// Input Value  : ucStartLevel -> search start level (must >= 4)
//                ucMainTone   -> address for main tone within search levels
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoMainToneMeasure(BYTE ucStartLevel, BYTE *pucMainTone)
{
    BYTE ucIndex = 0;

    // Stop auto-function
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    ScalerVgaAutoSetBoundary(_MEASURE_ACTIVE_REGION);

    // Set default values
    *pucMainTone = 3;
    PDATA_DWORD(1) = 0; // Previous sum
    PDATA_DWORD(2) = 0; // Previous level
    PDATA_DWORD(3) = 0; // Max difference
    if(ucStartLevel != 255)
    {
        ++ucStartLevel;
    }

    // Default threshold at start_level
    ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, ucStartLevel);

    // Disable field select; Disable LPF filter; Disable hardware acceleration;
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    // HW auto for 5 steps; Step size = 1;
    ScalerSetByte(P30_CB_VGATOP_HW_AUTO_PHASE_CTRL0, 0x20);

    // Initial phase = current phase
    ScalerSetByte(P30_CC_VGATOP_HW_AUTO_PHASE_CTRL1, (ScalerGetByte(P1_B4_PLLPHASE_CTRL1) & ~(_BIT7)));

    // HW auto-phase; Max value; Accumulation; Auto-balance; Start auto-function;
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT0));

    if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FAIL)
    {
        return _AUTO_FAIL;
    }

    for(ucIndex = 0; ucIndex < 5; ++ucIndex)
    {
        if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FAIL)
        {
            return _AUTO_FAIL;
        }

        // Decrease threshold
        ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, (ScalerGetByte(P30_C9_VGATOP_DIFF_THRESHOLD) - 1));

        // Get pixel count for current level
        PDATA_DWORD(0) = (GET_AUTO_RESULT_DWORD() - PDATA_DWORD(1)) / (ucStartLevel - ucIndex);

        // Store current accumulation result
        PDATA_DWORD(1) = GET_AUTO_RESULT_DWORD();

        // If start-level != 255, skip the first iteration.
        if((ucIndex == 0) && (ucStartLevel != 255))
        {
            continue;
        }

        // If the measured pixels is less than 2 vertical line, ignore it.
        if(PDATA_DWORD(0) < (GET_INPUT_TIMING_VHEIGHT() << 1))
        {
            PDATA_DWORD(0) = 0;
        }

        if(PDATA_DWORD(0) < PDATA_DWORD(2))
        {
            // Pixel decreases. Stop main-tone search.
            break;
        }

        PDATA_DWORD(2) = PDATA_DWORD(0) - PDATA_DWORD(2);

        // Compare the difference between successive levels & the maximum difference
        if(PDATA_DWORD(2) > PDATA_DWORD(3))
        {
            PDATA_DWORD(3) = PDATA_DWORD(2);
            *pucMainTone = ucIndex;
        }

        // Store current level
        PDATA_DWORD(2) = PDATA_DWORD(0);
    }

    // Stop auto-function
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    *pucMainTone = (ucStartLevel - *pucMainTone);

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Return the auto-color result
// Input Value  : stAdcData -> ADC data structure pointer
// Output Value : None
//--------------------------------------------------
void ScalerVgaAutoGetAutoColorResult(StructAdcDataType *pstAdcData)
{
    ScalerRead(P0_C0_ADC_GAI_RED_MSB, 3, pstAdcData->pucAdcGainMSB, _AUTOINC);
    ScalerRead(P0_C3_ADC_OFF_RED_MSB, 3, pstAdcData->pucAdcOffsetMSB, _AUTOINC);
    pstAdcData->ucAdcPGA = 0;
    pstAdcData->pucAdcGainLSB[0] = 0;
    pstAdcData->pucAdcGainLSB[1] = 0;
    pstAdcData->pucAdcGainLSB[2] = 0;
    pstAdcData->pucAdcOffsetLSB[0] = 0;
    pstAdcData->pucAdcOffsetLSB[1] = 0;
    pstAdcData->pucAdcOffsetLSB[2] = 0;
}

//--------------------------------------------------
// Description  : Measure color min/max from specific channel
// Input Value  : ucColor --> R/G/B
//                pucResult --> memory to store measure result
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoMeasureColorValue(BYTE ucColor, bit bSelectMax, BYTE *pucResult)
{
    // Disable 121-LPF; Set to R channel for auto-balance new mode
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT5 | _BIT1 | _BIT0), _BIT1);

    // Enable image auto-balance new mode
    ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~_BIT0, _BIT0);

    // Start Measure
    if(ScalerVgaAutoCompareMeasure((bSelectMax == _TRUE) ? _MEASURE_MAX : _MEASURE_RGB_MIN) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    switch(ucColor)
    {
        case _AUTO_RED_CHANNEL:
            *pucResult = ScalerGetByte(P30_D4_VGATOP_AUTO_PHASE_3);
            break;

        case _AUTO_GREEN_CHANNEL:
            *pucResult = ScalerGetByte(P30_D5_VGATOP_AUTO_PHASE_2);
            break;

        case _AUTO_BLUE_CHANNEL:
            *pucResult = ScalerGetByte(P30_D6_VGATOP_AUTO_PHASE_1);
            break;

        default:
            return _AUTO_FAIL;
    }

    return _AUTO_SUCCESS;
}

#if(_YPBPR_SUPPORT == _ON)

#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE)
//--------------------------------------------------
// Description  : Compensate ADC gain / offset for YPbPr color space
// Input Value  : enumAutoType -> auto-color type
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoCompensateYPbPr(EnumAutoColorType enumAutoType)
{
    BYTE ucGain = 0;
    BYTE ucMainTone = 0;
    BYTE ucMaxLevel = 0;
    BYTE ucIndex = 0;

    if(enumAutoType != _AUTO_TUNE_YPBPR_GAIN_ONLY)
    {
        // Double check for offset
        if(ScalerVgaAutoHardwareAbl(16, 2) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }
    }

    // Compensate starts from Y channel
    SET_AUTO_ADC_CHANNEL(_AUTO_GREEN_CHANNEL);
    ucMaxLevel = _AUTO_Y_MAX_LEVEL;

    for(ucIndex = 0; ucIndex < 3; ++ucIndex)
    {
        ucGain = GET_AUTO_ADC_GAIN();

        // Measure main tone for each channel
        if(ScalerVgaAutoMainToneMeasure(ucMaxLevel, &ucMainTone) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }
        ucMaxLevel = ScalerVgaAutoConvertAdcGainStep(ucGain, ucMaxLevel, ucMainTone);

        SET_AUTO_ADC_GAIN(ucGain - ucMaxLevel);
        SET_AUTO_ADC_NEXT_CHANNEL();
        ucMaxLevel = _AUTO_PBPR_MAX_LEVEL;
    }

    return _AUTO_SUCCESS;
}
#endif // End of #if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE)

#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA)
//--------------------------------------------------
// Description  : Calculate ADC gain/offset for YPbPr from RGB auto-color result
// Input Value  : stAdcData: balanced gain/offset for RGB
// Output Value : balanced gain/offset for YPbPr from calculation
//--------------------------------------------------
StructAdcDataType ScalerVgaAutoBalanceYPbPrFromFormula(StructAdcDataType *pstAdcData)
{
    StructAdcDataType stYPbPrData = {0};

    stYPbPrData = *pstAdcData;

    // Check for B/R swap. Assume default: Pr, Y, Pb
    stYPbPrData.pucAdcOffsetMSB[0] = pstAdcData->pucAdcOffsetMSB[0] + _AUTO_PR_OFFSET_BIAS; // Pr
    stYPbPrData.pucAdcOffsetMSB[2] = pstAdcData->pucAdcOffsetMSB[2] + _AUTO_PB_OFFSET_BIAS; // Pb
    stYPbPrData.pucAdcGainMSB[0] += (BYTE)(((DWORD)stYPbPrData.pucAdcGainMSB[0] + 64) * 31 / 224) + _AUTO_PR_GAIN_BIAS; // Pr
    stYPbPrData.pucAdcGainMSB[2] += (BYTE)(((DWORD)stYPbPrData.pucAdcGainMSB[2] + 64) * 31 / 224) + _AUTO_PB_GAIN_BIAS; // Pb

    stYPbPrData.pucAdcOffsetMSB[1] = stYPbPrData.pucAdcOffsetMSB[1] + _AUTO_Y_OFFSET_BIAS;// Y
    stYPbPrData.pucAdcGainMSB[1] += (BYTE)(((DWORD)stYPbPrData.pucAdcGainMSB[1] + 64) * 36 / 219) + _AUTO_Y_GAIN_BIAS; // Y

    return stYPbPrData;
}
#endif
#endif // End of #if(_YPBPR_SUPPORT == _ON)

#if(_ADC_SELF_CALIBRATION == _ON)
//--------------------------------------------------
// Description  : Update ADC gain for RGB self-calibration
// Input Value  : ucBias: bias level from max level
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoUpdateAdcGainCalibrationRGB(BYTE ucGainBias, BYTE ucStepRatio)
{
    BYTE ucIndex = 0;
    BYTE ucGain = 0;

    // Measure maximum value for RGB
    if(ScalerVgaAutoAblMeasure() == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    // Update gain for each channel
    for(ucIndex = 0; ucIndex < 3; ++ucIndex)
    {
        ucGain = ScalerGetByte(P0_C0_ADC_GAI_RED_MSB + ucIndex);
        pData[0] = ScalerGetByte(P0_E9_AUTO_BLACK_LEVEL_RED_VALUE + ucIndex); // RGB max value
        pData[1] = _AUTO_RGB_MAX_LEVEL - ucGainBias; // RGB target value

        // Update ADC gain according to max level & measured maximum
        if(pData[0] < pData[1])
        {
            // Calculate gain step
            pData[2] = ScalerVgaAutoConvertAdcGainStep(ucGain, pData[1], pData[0]) / ucStepRatio;

            if(pData[2] == 0x00)
            {
                --ucGain;
            }
            else
            {
                ucGain -= pData[2];
            }
        }
        else
        {
            // Target value exceeded. Rewind gain.
            ucGain += (pData[0] - pData[1]);
        }

        // Apply gain step
        ScalerSetByte((P0_C0_ADC_GAI_RED_MSB + ucIndex), ucGain);
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Compensate ADC gain / offset for RGB self-calibration
// Input Value  : enumAutoType -> auto-color type
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoCompensateCalibrationRGB(EnumAutoColorType enumAutoType)
{
    enumAutoType = enumAutoType;

    // Apply gain bias
    ScalerSetByte(P0_C0_ADC_GAI_RED_MSB, (ScalerGetByte(P0_C0_ADC_GAI_RED_MSB) + _CALIBRATION_R_GAIN_BIAS));
    ScalerSetByte(P0_C1_ADC_GAI_GRN_MSB, (ScalerGetByte(P0_C1_ADC_GAI_GRN_MSB) + _CALIBRATION_G_GAIN_BIAS));
    ScalerSetByte(P0_C2_ADC_GAI_BLU_MSB, (ScalerGetByte(P0_C2_ADC_GAI_BLU_MSB) + _CALIBRATION_B_GAIN_BIAS));

    // Check offset original signal level
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);
    if(ScalerVgaAutoHardwareAbl(4, 4) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    // Apply R & B offset bias
    ScalerSetByte(P0_C3_ADC_OFF_RED_MSB, (ScalerGetByte(P0_C3_ADC_OFF_RED_MSB) - _CALIBRATION_R_OFFSET_BIAS));
    ScalerSetByte(P0_C4_ADC_OFF_GRN_MSB, (ScalerGetByte(P0_C4_ADC_OFF_GRN_MSB) - _CALIBRATION_G_OFFSET_BIAS));
    ScalerSetByte(P0_C5_ADC_OFF_BLU_MSB, (ScalerGetByte(P0_C5_ADC_OFF_BLU_MSB) - _CALIBRATION_B_OFFSET_BIAS));

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Initialization for ADC self-calibration
// Input Value  : none
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
void ScalerVgaAutoInitializeCalibration(void)
{
    // Initial VGA data path
    ScalerVgaSyncProcScanInitial(_A0_INPUT_PORT);
    ScalerVgaAdcClampMode(_COLOR_SPACE_RGB);

    // Enable calibration mode; Enable calibration voltage; Set new-mode; Voltage from 3.3V
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(P0_D9_ADC_REG1, ~(_BIT1 | _BIT0), 0x00);

    // Set DPLL free-run
    ScalerMDomainSetDisplayFormat(_FREE_RUN_NO_INPUT);

    // Disable DPLL spread spectrum
    ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _OFF);

    // Switch sync-processor HS/VS source from D-domain
    ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT1, _BIT1);
    ScalerSetBit(P0_47_SYNC_SELECT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT2));
    ScalerSetBit(P0_48_SYNC_INVERT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
    ScalerSetBit(P0_49_SYNC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    DebugMessageAnalog("Self-Calibration clock(MHz)", _SELF_CALIBRATION_CLK);

    // Set APLL H total = Display H total
    ScalerAPLLAdjust(_SELF_CALIBRATION_HTOTAL, _SELF_CALIBRATION_HFREQ);

    // Set ADC bandwidth according to DPLL rate
    ScalerVgaAdcBandWidthSetting(_SELF_CALIBRATION_CLK);

    // Disable double buffer; Input ADC pixel format; Enable input sampling;
    ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : Reset for ADC self-calibration
// Input Value  : none
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
void ScalerVgaAutoResetCalibration(void)
{
    // Turn off calibration signal
    ScalerSetByte(P0_D2_ADC_GAIN_CALI, 0x00);

    // Set sync processsor HS/VS source from ADC
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT2, 0x00);
}

//--------------------------------------------------
// Description  : Measure the average value using ABL
// Input Value  : none
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoAblMeasure(void)
{
    // Set calibration voltage to high
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Enable ABL offset adjust new mode
    ScalerSetBit(P0_EC_AUTO_BLACK_LEVEL_R_NOISE_VALUE, ~_BIT3, _BIT3);

    // Measure RGB max using ABL
    if(ScalerVgaAutoHardwareAbl(16, 0) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    // Disable ABL offset adjust new mode
    ScalerSetBit(P0_EC_AUTO_BLACK_LEVEL_R_NOISE_VALUE, ~_BIT3, 0x00);

    // Set calibration voltage to low
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    return _AUTO_SUCCESS;
}
#endif // End of #if(_ADC_SELF_CALIBRATION == _ON)

//--------------------------------------------------
// Description  : Update ADC gain for RGB color space in custom mode
// Input Value  : ucGainBias: bias for RGB max level
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoCustomUpdateAdcGain(BYTE ucGainBias, BYTE ucStepRatio)
{
    if(ScalerVgaAutoCustomUpdateAdcGainChannel(_AUTO_RED_CHANNEL, ucGainBias, ucStepRatio) == _AUTO_SUCCESS)
    {
        if(ScalerVgaAutoCustomUpdateAdcGainChannel(_AUTO_BLUE_CHANNEL, ucGainBias, ucStepRatio) == _AUTO_SUCCESS)
        {
            if(ScalerVgaAutoCustomUpdateAdcGainChannel(_AUTO_GREEN_CHANNEL, ucGainBias, ucStepRatio) == _AUTO_SUCCESS)
            {
                return _AUTO_SUCCESS;
            }
        }
    }

    return _AUTO_FAIL;
}

//--------------------------------------------------
// Description  : Update ADC gain for R/G/B color space in custom mode
// Input Value  : enumAutoType -->
//                ucGainBias: bias for RGB max level
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
EnumAutoResult ScalerVgaAutoCustomUpdateAdcGainChannel(BYTE ucColor, BYTE ucGainBias, BYTE ucStepRatio)
{
    BYTE ucGain = 0;
    BYTE ucTarget = (255 - ucGainBias);
    BYTE ucMax = 0;

    SET_AUTO_ADC_CHANNEL(ucColor);
    ucGain = GET_AUTO_ADC_GAIN();

    // Stop image auto-function measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Disable field select; Enable LPF filter; Disable hardware acceleration;
    ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, 0x00);
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT7 | _BIT4), 0x00);

    // Set measure boundary
    ScalerVgaTopAutoFuncHBoundInitial(_AUTO_CUSTOM_WHITE_HSTART, _AUTO_CUSTOM_WHITE_HEND);
    ScalerVgaTopAutoFuncVBoundInitial(_AUTO_CUSTOM_WHITE_VSTART, _AUTO_CUSTOM_WHITE_VEND);

    // Normal boundary; Software mode; Measure maximum / minimum; Compare mode; Auto-balance; Start measure;
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
    {
        return _AUTO_FAIL;
    }

    ucMax = (GET_AUTO_RESULT_DWORD()) /
            (_AUTO_CUSTOM_WHITE_VEND - _AUTO_CUSTOM_WHITE_VSTART + 1) /
            (_AUTO_CUSTOM_WHITE_HEND - _AUTO_CUSTOM_WHITE_HSTART + 1);

    // Update ADC gain according to max level & measured maximum
    if(ucMax < ucTarget)
    {
        // Calculate gain step
        pData[1] = ScalerVgaAutoConvertAdcGainStep(ucGain, ucTarget, ucMax) / ucStepRatio;

        // Minimum gain step = 1
        if(pData[1] == 0)
        {
            pData[1] = 1;
        }

        // Decrease gain with underflow check
        if(ucGain >= pData[1])
        {
            ucGain -= pData[1];
        }
        else
        {
            ucGain = 0;
        }
    }
    else
    {
        // Target value exceeded. Rewind gain.
        pData[1] = (ucMax - ucTarget);

        // Increase gain with overflow check
        if(((WORD)ucGain + pData[1]) > 0xFF)
        {
            ucGain = 0xFF;
        }
        else
        {
            ucGain += pData[1];
        }
    }

    SET_AUTO_ADC_GAIN(ucGain);

    return _AUTO_SUCCESS;
}

#endif // End of #if(_VGA_SUPPORT == _ON)
