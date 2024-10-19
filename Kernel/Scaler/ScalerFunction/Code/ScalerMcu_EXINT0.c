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
// ID Code      : ScalerMcu_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MCU_EXINT0__

#include "ScalerFunctionInclude.h"
#include "Mcu/ScalerMcu.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Clear DDC SCL Toggle IRQ Status
// Input Value  : ucDDCx
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcClearSclToggleIrqStatus_EXINT0(BYTE ucDDCx)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit_EXINT(PFF_E7_VGA_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit_EXINT(PFF_E4_DDC0_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit_EXINT(PFF_E5_DDC1_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit_EXINT(PFE_69_DDC2_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit_EXINT(PFE_72_DDC3_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit_EXINT(PFE_7B_DDC4_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit_EXINT(PFE_84_DDC5_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DDC SCL Toggle IRQ Status
// Input Value  : ucDDCx
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuDdcGetSclToggleIrqStatus_EXINT0(BYTE ucDDCx)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            return ((bit)ScalerGetBit_EXINT(PFF_E7_VGA_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            return ((bit)ScalerGetBit_EXINT(PFF_E4_DDC0_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            return ((bit)ScalerGetBit_EXINT(PFF_E5_DDC1_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            return ((bit)ScalerGetBit_EXINT(PFE_69_DDC2_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            return ((bit)ScalerGetBit_EXINT(PFE_72_DDC3_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            return ((bit)ScalerGetBit_EXINT(PFE_7B_DDC4_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            return ((bit)ScalerGetBit_EXINT(PFE_84_DDC5_EDID_IRQ, _BIT2));
#endif

        default:
            return _FALSE;
    }
}
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
//--------------------------------------------------
// Description  : ADC Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuAdcLsAdcDetectIntHandler_EXINT0(void)
{
    // ====================================================
    // Check Comparator INT Flag
    // ====================================================
    if(ScalerMcuAdcLsAdcInOutCompIntCheck_EXINT0(_ADC_DETECT_INT_BY_ADC_CHANNEL) == _FALSE)
    {
        return;
    }

    // PCB GPIO Control
    PCB_ADC_INTERRUPT_CONTROL(_ADC_INTERRUPT_CONTROL_PIN_OFF);

    // Disable INT & Clear INT Flag
    ScalerMcuAdcLsAdcInOutCompIntControl_EXINT0(_ADC_DETECT_INT_BY_ADC_CHANNEL, _ADC_INT_DISABLE);
}

//--------------------------------------------------
// Description  : LS ADC Range Detection IRQ Control
// Input Value  : ucChannel : _ADC_DETECT_INT_BY_ADC_CHANNEL
//                enumAdcIntControl : _ADC_INT_ENABLE / _ADC_INT_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerMcuAdcLsAdcInOutCompIntControl_EXINT0(BYTE ucChannel, EnumAdcIntControl enumAdcIntControl)
{
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    if(enumAdcIntControl == _ADC_INT_ENABLE)
    {
        // [0xFF0E] ADC0: Clear Flag & Enable INT
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0))), ((_BIT4 | _BIT0) << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0)));
    }
    else
    {
        // [0xFF0E] ADC0: Reset Threshold
        ScalerMcuAdcLsAdcInOutCompIntSetting_EXINT0(ucChannel, 0x0000, 0x03FF);

        // [0xFF0E] ADC0: Disable INT, but don't clear flag
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0))), 0x00);
    }

    // Clear INT Flag
    ScalerMcuAdcLsAdcInOutCompIntClearFlag_EXINT0(ucChannel);

    // ADC Start Scan
    ScalerSetBit_EXINT(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
    if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
    {
        if(enumAdcIntControl == _ADC_INT_ENABLE)
        {
            // [0xFD40] ADC0: Clear Flag & Enable INT
            ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0))), ((_BIT4 | _BIT0) << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0)));
        }
        else
        {
            // [0xFD40] ADC0: Reset Threshold
            ScalerMcuAdcLsAdcInOutCompIntSetting_EXINT0(ucChannel, 0x0000, 0x03FF);

            // [0xFD40] ADC0: Disable INT, but don't clear flag
            ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0))), 0x00);
        }
    }
    else if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
    {
        if(enumAdcIntControl == _ADC_INT_ENABLE)
        {
            // [0xFF0E] ADC0: Clear Flag & Enable INT
            ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0))), ((_BIT4 | _BIT0) << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0)));
        }
        else
        {
            // [0xFF0E] ADC0: Reset Threshold
            ScalerMcuAdcLsAdcInOutCompIntSetting_EXINT0(ucChannel, 0x0000, 0x03FF);

            // [0xFF0E] ADC0: Disable INT, but don't clear flag
            ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0))), 0x00);
        }
    }

    // Clear INT Flag
    ScalerMcuAdcLsAdcInOutCompIntClearFlag_EXINT0(ucChannel);

    // ADC Start Scan
    ScalerSetBit_EXINT(PFD_3A_ADC_ACONTROL, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : ucChannel : _ADC_DETECT_INT_BY_ADC_CHANNEL
//                usHigh / usLow : High / Low Threshold
//                bRange : IRQ Triggered When Within / Without Range
// Output Value : None
//--------------------------------------------------
void ScalerMcuAdcLsAdcInOutCompIntSetting_EXINT0(BYTE ucChannel, WORD usHigh, WORD usLow)
{
    // Must be In-Range

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 5;
    usHigh = ((usHigh >= 0x001F) ? 0x001F : (usHigh & 0x001F));

    usLow = usLow >> 5;
    usLow = ((usLow >= 0x001E) ? 0x001E : (usLow & 0x001F));

    // Set High/Low Threshold (250mA/bit for max current 8A)
    ScalerSetByte_EXINT((PFF_0F_ADC0_THRESHOLD_H + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0) * 2)), (BYTE)(usHigh << 3));
    ScalerSetByte_EXINT((PFF_10_ADC0_THRESHOLD_L + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0) * 2)), (BYTE)(usLow << 3));

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 2;
    usHigh = ((usHigh >= 0x00FF) ? 0x00FF : (usHigh & 0x00FF));

    usLow = usLow >> 2;
    usLow = ((usLow >= 0x00FE) ? 0x00FE : (usLow & 0x00FF));

    // Set High/Low Threshold (31mA/bit for max current 8A)
    if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
    {
        ScalerSetByte_EXINT((PFD_F7_ADC0_THRESHOLD_H + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) * 2)), (BYTE)(usHigh));
        ScalerSetByte_EXINT((PFD_F8_ADC0_THRESHOLD_L + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) * 2)), (BYTE)(usLow));
    }
    else if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
    {
        ScalerSetByte_EXINT((PFF_0F_ADC0_THRESHOLD_H + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) * 2)), (BYTE)(usHigh));
        ScalerSetByte_EXINT((PFF_10_ADC0_THRESHOLD_L + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) * 2)), (BYTE)(usLow));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : ucChannel : _ADC_DETECT_INT_BY_ADC_CHANNEL
// Output Value : None
//--------------------------------------------------
void ScalerMcuAdcLsAdcInOutCompIntClearFlag_EXINT0(BYTE ucChannel)
{
    // Clear Flag
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0)), (_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0)));

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
    if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
    {
        ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0)), (_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0)));
    }
    else if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
    {
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0)), (_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0)));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : ADC INT Check
// Input Value  : ucChannel : _ADC_DETECT_INT_BY_ADC_CHANNEL
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerMcuAdcLsAdcInOutCompIntCheck_EXINT0(BYTE ucChannel)
{
    // Check INT Flag
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    BYTE ucValue = ScalerGetByte_EXINT(PFF_0E_AUTO_MODE_CTRL01) >> (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0);

    return ((ucValue & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0));

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
    if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
    {
        BYTE ucValue = ScalerGetByte_EXINT(PFD_40_AUTO_MODE_CTRL01) >> (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0);

        return ((ucValue & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0));
    }
    else if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
    {
        BYTE ucValue = ScalerGetByte_EXINT(PFF_0E_AUTO_MODE_CTRL01) >> (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0);

        return ((ucValue & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    return _FALSE;
}
#endif
#endif // End of #if(_LOW_SPEED_ADC_SUPPORT == _ON)
