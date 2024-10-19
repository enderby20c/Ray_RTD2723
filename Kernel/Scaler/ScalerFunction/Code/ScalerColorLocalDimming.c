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
// ID Code      : ScalerColorLocalDimming.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLDCTSTABLE[] =
{
    0xFF, 0xFF, 0xFF, 0xFF,
    0x80, 0x00, 0x55, 0x55,
    0x40, 0x00, 0x33, 0x33,
    0x2A, 0xAB, 0x24, 0x92,
    0x20, 0x00, 0x1C, 0x72,
    0x19, 0x9A, 0x17, 0x46,
    0x15, 0x55, 0x13, 0xB1,
    0x12, 0x49, 0x11, 0x11,
    0x10, 0x00, 0xF0, 0xF1,
    0xE3, 0x8E, 0xD7, 0x94,
    0xCC, 0xCD, 0xC3, 0x0C,
    0xBA, 0x2F, 0xB2, 0x16,
    0xAA, 0xAB, 0xA3, 0xD7,
    0x9D, 0x8A, 0x97, 0xB4,
    0x92, 0x49, 0x8D, 0x3E,
    0x88, 0x89, 0x84, 0x21,
    0x80, 0x00, 0x7C, 0x1F,
    0x78, 0x78, 0x75, 0x07,
    0x71, 0xC7, 0x6E, 0xB4,
    0x6B, 0xCA, 0x69, 0x07,
    0x66, 0x66, 0x63, 0xE7,
    0x61, 0x86, 0x5F, 0x41,
    0x5D, 0x17, 0x5B, 0x06,
    0x59, 0x0B, 0x57, 0x26,
    0x55, 0x55, 0x53, 0x98,
    0x51, 0xEC, 0x50, 0x50,
    0x4E, 0xC5, 0x4D, 0x48,
    0x4B, 0xDA, 0x4A, 0x79,
    0x49, 0x25, 0x47, 0xDC,
    0x46, 0x9F, 0x45, 0x6C,
    0x44, 0x44, 0x43, 0x26,
    0x42, 0x11, 0x41, 0x04,
    0x40, 0x00, 0x3F, 0x04,
    0x3E, 0x10, 0x3D, 0x22,
    0x3C, 0x3C, 0x3B, 0x5D,
    0x3A, 0x84, 0x39, 0xB1,
    0x38, 0xE4, 0x38, 0x1C,
    0x37, 0x5A, 0x36, 0x9D,
    0x35, 0xE5, 0x35, 0x32,
    0x34, 0x83, 0x33, 0xD9,
    0x33, 0x33, 0x32, 0x91,
    0x31, 0xF4, 0x31, 0x59,
    0x30, 0xC3, 0x30, 0x30,
    0x2F, 0xA1, 0x2F, 0x15,
    0x2E, 0x8C, 0x2E, 0x06,
    0x2D, 0x83, 0x2D, 0x03,
    0x2C, 0x86, 0x2C, 0x0B,
    0x2B, 0x93, 0x2B, 0x1E,
    0x2A, 0xAB, 0x2A, 0x3A,
    0x29, 0xCC, 0x29, 0x60,
    0x28, 0xF6, 0x28, 0x8E,
    0x28, 0x28, 0x27, 0xC4,
    0x27, 0x62, 0x27, 0x02,
    0x26, 0xA4, 0x26, 0x48,
    0x25, 0xED, 0x25, 0x94,
    0x25, 0x3D, 0x24, 0xE7,
    0x24, 0x92, 0x24, 0x3F,
    0x23, 0xEE, 0x23, 0x9E,
    0x23, 0x4F, 0x23, 0x02,
    0x22, 0xB6, 0x22, 0x6C,
    0x22, 0x22, 0x21, 0xDA,
    0x21, 0x93, 0x21, 0x4D,
    0x21, 0x08, 0x20, 0xC5,
    0x20, 0x82, 0x20, 0x41,
    0x20, 0x00, 0x1F, 0x82,
    0x1F, 0x08, 0x1E, 0x91,
    0x1E, 0x1E, 0x1D, 0xAE,
    0x1D, 0x42, 0x1C, 0xD8,
    0x1C, 0x72, 0x1C, 0x0E,
    0x1B, 0xAD, 0x1B, 0x4F,
    0x1A, 0xF3, 0x1A, 0x99,
    0x1A, 0x42, 0x19, 0xED,
    0x19, 0x9A, 0x19, 0x49,
    0x18, 0xFA, 0x18, 0xAD,
    0x18, 0x62, 0x18, 0x18,
    0x17, 0xD0, 0x17, 0x8A,
    0x17, 0x46, 0x17, 0x03,
    0x16, 0xC1, 0x16, 0x81,
    0x16, 0x43, 0x16, 0x06,
    0x15, 0xCA, 0x15, 0x8F,
    0x15, 0x55, 0x15, 0x1D,
    0x14, 0xE6, 0x14, 0xB0,
    0x14, 0x7B, 0x14, 0x47,
    0x14, 0x14, 0x13, 0xE2,
    0x13, 0xB1, 0x13, 0x81,
    0x13, 0x52, 0x13, 0x24,
    0x12, 0xF7, 0x12, 0xCA,
    0x12, 0x9E, 0x12, 0x73,
    0x12, 0x49, 0x12, 0x20,
    0x11, 0xF7, 0x11, 0xCF,
    0x11, 0xA8, 0x11, 0x81,
    0x11, 0x5B, 0x11, 0x36,
    0x11, 0x11, 0x10, 0xED,
    0x10, 0xC9, 0x10, 0xA7,
    0x10, 0x84, 0x10, 0x62,
    0x10, 0x41, 0x10, 0x20,
    0x10, 0x00, 0x0F, 0xC1,
    0x0F, 0x84, 0x0F, 0x49,
    0x0F, 0x0F, 0x0E, 0xD7,
    0x0E, 0xA1, 0x0E, 0x6C,
    0x0E, 0x39, 0x0E, 0x07,
    0x0D, 0xD6, 0x0D, 0xA7,
    0x0D, 0x79, 0x0D, 0x4C,
    0x0D, 0x21, 0x0C, 0xF6,
    0x0C, 0xCD, 0x0C, 0xA4,
    0x0C, 0x7D, 0x0C, 0x56,
    0x0C, 0x31, 0x0C, 0x0C,
    0x0B, 0xE8, 0x0B, 0xC5,
    0x0B, 0xA3, 0x0B, 0x81,
    0x0B, 0x61, 0x0B, 0x41,
    0x0B, 0x21, 0x0B, 0x03,
    0x0A, 0xE5, 0x0A, 0xC7,
    0x0A, 0xAB, 0x0A, 0x8F,
    0x0A, 0x73, 0x0A, 0x58,
    0x0A, 0x3D, 0x0A, 0x23,
    0x0A, 0x0A, 0x09, 0xF1,
    0x09, 0xD9, 0x09, 0xC1,
    0x09, 0xA9, 0x09, 0x92,
    0x09, 0x7B, 0x09, 0x65,
    0x09, 0x4F, 0x09, 0x3A,
    0x09, 0x25, 0x09, 0x10,
    0x08, 0xFC, 0x08, 0xE8,
    0x08, 0xD4, 0x08, 0xC1,
    0x08, 0xAE, 0x08, 0x9B,
    0x08, 0x89, 0x08, 0x76,
    0x08, 0x65, 0x08, 0x53,
    0x08, 0x42, 0x08, 0x31,
    0x08, 0x21, 0x08, 0x10,
    0x08, 0x00, 0x07, 0xC2,
    0x07, 0x88, 0x07, 0x50,
    0x07, 0x1C, 0x06, 0xEB,
    0x06, 0xBD, 0x06, 0x90,
    0x06, 0x66, 0x06, 0x3E,
    0x06, 0x18, 0x05, 0xF4,
    0x05, 0xD1, 0x05, 0xB0,
    0x05, 0x91, 0x05, 0x72,
    0x05, 0x55, 0x05, 0x39,
    0x05, 0x1F, 0x05, 0x05,
    0x04, 0xEC, 0x04, 0xD5,
    0x04, 0xBE, 0x04, 0xA8,
    0x04, 0x92, 0x04, 0x7E,
    0x04, 0x6A, 0x04, 0x57,
    0x04, 0x44, 0x04, 0x32,
    0x04, 0x21, 0x04, 0x10,
    0x04, 0x00, 0x03, 0xE1,
    0x03, 0xC4, 0x03, 0xA8,
    0x03, 0x8E, 0x03, 0x76,
    0x03, 0x5E, 0x03, 0x48,
    0x03, 0x33, 0x03, 0x1F,
    0x03, 0x0C, 0x02, 0xFA,
    0x02, 0xE9, 0x02, 0xD8,
    0x02, 0xC8, 0x02, 0xB9,
    0x02, 0xAB, 0x02, 0x9D,
    0x02, 0x8F, 0x02, 0x83,
    0x02, 0x76, 0x02, 0x6A,
    0x02, 0x5F, 0x02, 0x54,
    0x02, 0x49, 0x02, 0x3F,
    0x02, 0x35, 0x02, 0x2B,
    0x02, 0x22, 0x02, 0x19,
    0x02, 0x11, 0x02, 0x08,
    0x02, 0x00, 0x00, 0x00,
};
#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _OFF)
__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingLvMax[] =
{
#include _LOCAL_DIMMING_LVMAX_ADDR
};

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingPWMGain[] =
{
#include _LOCAL_DIMMING_PWMGAIN_ADDR
};

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingLvGain[] =
{
#include _LOCAL_DIMMING_LVGAIN_ADDR
};

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingLvLut[] =
{
#include _LOCAL_DIMMING_LVLUT_ADDR
};

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingLedSettingLut[] =
{
#include _LOCAL_DIMMING_LEDSETTING_ADDR
};

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingS1Lut[] =
{
#include _LOCAL_DIMMING_S1LUT_ADDR
};

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingS2Lut[] =
{
#include _LOCAL_DIMMING_S2LUT_ADDR
};
#endif

#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingSDRHistoLut[32] =
{
#include _LOCAL_DIMMING_HISTO_SDRLUT_ADDR
};

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
BYTE code tLocalDimmingHDRHistoLut[32] =
{
#include _LOCAL_DIMMING_HISTO_HDRLUT_ADDR
};
#else
__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
WORD code tLocalDimmingSDRHistoLut256Bin[256] =
{
#include _LOCAL_DIMMING_HISTO_SDRLUT_256_BIN_ADDR
};
__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
WORD code tLocalDimmingHDRHistoLut256Bin[256] =
{
#include _LOCAL_DIMMING_HISTO_HDRLUT_256_BIN_ADDR
};
__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
DWORD code tLocalDimmingHDRHistoDecisionTHD[255] =
{
#include _LOCAL_DIMMING_HISTO_HDRDECISION_THD_ADDR
};
__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
DWORD code tLocalDimmingSDRHistoDecisionTHD[255] =
{
#include _LOCAL_DIMMING_HISTO_SDRDECISION_THD_ADDR
};
#endif

StructLocalDimmingSmoothData code tLocalDimmingSmoothPara[] =
{
#include _LOCAL_DIMMING_SMOOTH_PARA
};

WORD code tPWMDereaseStepTable[256] =
{
#include _LOCAL_DIMMING_PWM_DECREASE_STEP_TABLE
};

WORD code tPWMInreaseStepTable[256] =
{
#include _LOCAL_DIMMING_PWM_INCREASE_STEP_TABLE
};

BYTE code tLocalDimmingPanelRegions[2] =
{
    _LOCAL_DIMMING_PANEL_REGION_VERTICAL,
    _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL,
};

#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
BYTE code tLocalDimmingPanelRegionsUp[2] =
{
    _LOCAL_DIMMING_PANEL_REGION_VERTICAL_UP,
    _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL_UP,
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucColorLDHistoLutMax;
BYTE g_ucColorLDHistoLutMin;

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
BYTE g_ucColorHistoTHdHigh;
BYTE g_ucColorHistoTHdLow;
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
BYTE g_ucColorCornerHorReg;
BYTE g_ucColorCornerRStart;
BYTE g_ucColorCornerCStart;
#endif

EnumColorPwm2SpiSramModeTxCallBackFuncId g_enumColorPwm2SpiSramModeTxCallBackFuncId = _COLOR_PWM2SPI_SRAM_TX_CALLBACK_NULL;

#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _ON)
StructLocalDimmingMultiBLModelTable g_stColorLocalDimmingMultiTable;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
//--------------------------------------------------
// Description  : Load Adjust Direct Mask Table
// Input Value  : Table point, Bank number
// Output Value : None
//--------------------------------------------------
void ScalerColorLDAdjustDirectMaskAdjust(BYTE *pucLDAdjDirectMaskTable, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucLDAdjDirectMaskTable, _LDADJUST_TABLE_SIZE_DIRECTMASK, ucBankAddress, PB00510_14_LD_PWM_ADJUST_GAIN, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Load Adjust Edge Mask Table
// Input Value  : Table point, Bank number
// Output Value : None
//--------------------------------------------------
void ScalerColorLDAdjustEdgeMaskAdjust(BYTE *pucLDAdjEdgeMaskTable, BYTE ucBankAddress, WORD usTableSize)
{
    Scaler32SetBit(PB00510_08_LD_PWM_ADJUST_CTRL, ~_BIT3, _BIT3);
    ScalerUtilBurstWrite32(pucLDAdjEdgeMaskTable, usTableSize, ucBankAddress, PB00511_00_LD_PWM_ADJUST_MASK, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
    Scaler32SetBit(PB00510_08_LD_PWM_ADJUST_CTRL, ~_BIT3, 0X00);
}

//--------------------------------------------------
// Description  : Enable/Disable LD Adjust Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDAdjustEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT1), _BIT1);
    }
    else
    {
        Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : LD Adjust Iinitial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDAdjustInitial(void)
{
    // Interate 5 times
    Scaler32SetBit(PB00510_08_LD_PWM_ADJUST_CTRL, ~_BIT0, 0x00);

    // Enable invert correct
    Scaler32SetBit(PB00510_08_LD_PWM_ADJUST_CTRL, ~_BIT1, _BIT1);

    // Enable last invert correct
    Scaler32SetBit(PB00510_08_LD_PWM_ADJUST_CTRL, ~_BIT2, _BIT2);

    // set adjust rate
    Scaler32SetByte(PB00510_10_LD_PWM_ADJUST_RATE, 0, _LDADJUST_ADJUST_RATE);

    // set correct rate
    Scaler32SetByte(PB00510_10_LD_PWM_ADJUST_RATE, 1, _LDADJUST_CORRECT_RATE);
}

//--------------------------------------------------
// Description  : LD Min PWM Adjust Function
// Input Value  : Min PWM
// Output Value : None
//--------------------------------------------------
void ScalerColorLDAdjustMinPWMAdjust(WORD usMinPWM)
{
    Scaler32SetWord(PB00510_0C_LD_PWM_ADJUST_MIN_PWM, 0, usMinPWM);
}
#endif

//--------------------------------------------------
// Description  : Check Sram Switch Permission
// Input Value  : bit Switch Permission Status
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelBlackTHAdjust(WORD usThValue)
{
    Scaler32SetWord(PB00550_60_LD_DEEP_BLACK_PARA, 0, usThValue);
}

//--------------------------------------------------
// Description  : Check Sram Switch Permission
// Input Value  : bit Switch Permission Status
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelBlackTHDelta(BYTE ucTHDelta)
{
    Scaler32SetByte(PB00550_60_LD_DEEP_BLACK_PARA, 3, ucTHDelta);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelCTSGainAdjust(void)
{
    ScalerUtilBurstWrite32(tLDCTSTABLE, 644, GET_CURRENT_BANK_NUMBER(), PB00615_00_LD_CTS_GAIN_LUT, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelDirectLEDSetting(BYTE *pucLedLutTable, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucLedLutTable, 16, ucBankAddress, PB00550_20_LD_DIRECT_BL_LED_OFFSET, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Enable Step Change
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~_BIT7, _BIT7);
    }
    else
    {
        Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Apply Sram Switch Permission
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelFWSwitchApply(void)
{
    Scaler32SetBit(PB00550_08_LD_BACKLIGHT_READ_CTRL, ~(_BIT5 | _BIT1 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : Check Sram Switch Permission
// Input Value  : bit Switch Permission Status
// Output Value : None
//--------------------------------------------------
bit ScalerColorLDBLModelFWSwitchStatus(void)
{
    return (Scaler32GetBit(PB00550_08_LD_BACKLIGHT_READ_CTRL, _BIT0) == _BIT0) ? _TRUE : _FALSE;
}

//-----------------------------------------------------
// Description  : Loca Dimming Backlight Model Enable Status
// Input Value  : None
// Output Value : None
//-----------------------------------------------------
bit ScalerColorLDBLModelGetEnableStatus(void)
{
    return (Scaler32GetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, _BIT7) == _BIT7) ? _TRUE : _FALSE;
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelLedGainAdjust(BYTE *pucLedGainTable, WORD usLength, BYTE ucBankAddress)
{
#if(_LOCAL_DIMMING_TOTAL_REGION > 2304)
    if(usLength > _LDBLM_GAIN_TABLE_LENGTH)
    {
        ScalerUtilBurstWrite32(pucLedGainTable, _LDBLM_GAIN_TABLE_LENGTH, ucBankAddress, PB00600_00_LD_DIRECT_BL_LED_GAIN, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
        ScalerUtilBurstWrite32(pucLedGainTable + _LDBLM_GAIN_TABLE_LENGTH, usLength - _LDBLM_GAIN_TABLE_LENGTH, ucBankAddress, PB00618_00_LD_DIRECT_BL_LED_GAIN_1, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
    }
    else
#endif
    {
        ScalerUtilBurstWrite32(pucLedGainTable, usLength, ucBankAddress, PB00600_00_LD_DIRECT_BL_LED_GAIN, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelBoostGainAdjust(BYTE *pucLedGainTable, WORD usLength, BYTE ucBankAddress)
{
#if(_LOCAL_DIMMING_TOTAL_REGION > 2304)
    if(usLength > _LDBLM_GAIN_TABLE_LENGTH)
    {
        ScalerUtilBurstWrite32(pucLedGainTable, _LDBLM_GAIN_TABLE_LENGTH, ucBankAddress, PB00600_00_LD_DIRECT_BL_LED_GAIN, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_XRAM, _ENDIAN_TYPE_LITTLE);
        ScalerUtilBurstWrite32(pucLedGainTable + _LDBLM_GAIN_TABLE_LENGTH, usLength - _LDBLM_GAIN_TABLE_LENGTH, ucBankAddress, PB00618_00_LD_DIRECT_BL_LED_GAIN_1, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_XRAM, _ENDIAN_TYPE_LITTLE);
    }
    else
#endif
    {
        ScalerUtilBurstWrite32(pucLedGainTable, usLength, ucBankAddress, PB00600_00_LD_DIRECT_BL_LED_GAIN, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_XRAM, _ENDIAN_TYPE_LITTLE);
    }
}
//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelBoostUniqueGainAdjust(DWORD ulUniqueGain)
{
    Scaler32SetDWord(PB00600_00_LD_DIRECT_BL_LED_GAIN, ulUniqueGain)
}
//--------------------------------------------------
// Description  : Set LED Unitque Gain
// Input Value  : Gain value
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelLedLutTableAdjust(BYTE *pucLedLutTable, WORD usLength, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucLedLutTable, usLength, ucBankAddress, PB005DE_00_LD_DIRECT_BL_LUT, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelLvTableAdjust(BYTE *pucBLLvTable, WORD usLength, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucBLLvTable, usLength, ucBankAddress, PB00550_E0_LD_LV_LUT, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Apply Sram Switch Permission
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelManualSwitchApply(void)
{
    Scaler32SetBit(PB00550_08_LD_BACKLIGHT_READ_CTRL, ~(_BIT5 | _BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : Check Sram Switch Permission
// Input Value  : bit Switch Permission Status
// Output Value : None
//--------------------------------------------------
bit ScalerColorLDBLModelManualSwitchStatus(void)
{
    return ScalerTimerPollingFlagProc32Bit(_BLM_TIMEOUT, PB00550_08_LD_BACKLIGHT_READ_CTRL, _BIT1, 1);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelMaxLvTableAdjust(BYTE *pucMaxLvTable, WORD usLength, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucMaxLvTable, usLength, ucBankAddress, PB00597_00_LD_MAX_LV_LUT, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelPWMGainAdjust(BYTE *pucPWMTable, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucPWMTable, 516, ucBankAddress, PB00612_00_LD_PWM_GAIN_LUT, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelSCurveThAdjust(BYTE *pucLDSCurveThTable, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucLDSCurveThTable, 32, ucBankAddress, PB00550_30_LD_1ST_S_CURVE_TH, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);

#if(_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL > 16)
    ScalerUtilBurstWrite32(pucLDSCurveThTable + 32, 32, ucBankAddress, PB00550_64_LD_9ST_S_CURVE_TH, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
#endif
}

//--------------------------------------------------
// Description  : Enable Step Change
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelSetEdgePWMOffset(BYTE ucPWMOffset)
{
    Scaler32SetBit(PB00550_54_LD_BACKLIGHT_MODEL_DUMMY, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucPWMOffset & 0x0F);
}

//--------------------------------------------------
// Description  : Check Sram Switch Permission
// Input Value  : bit Switch Permission Status
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelSetExtend(BYTE ucHStep, BYTE ucVStep)
{
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT6), _BIT6);
    Scaler32SetByte(PB00550_0C_LD_BACKLIGHT_EXTEND_STEPS, 0, (ucVStep << 4) | ucHStep);
}

//--------------------------------------------------
// Description  : Enable Step Change
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelSetMaxGain(WORD usMaxGain)
{
    Scaler32SetWord(PB00550_50_LD_LUT_GAIN_CTRL, 1, usMaxGain);
}

//--------------------------------------------------
// Description  : Enable Step Change
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelSetMinGain(WORD usMinGain)
{
    Scaler32SetWord(PB00550_50_LD_LUT_GAIN_CTRL, 0, usMinGain);
}
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDBLModelFrontBackEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT2), _BIT2);
    }
    else
    {
        Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT2), 0x00);
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerColorLDBLModelGetFrontBackEnable(void)
{
    return (Scaler32GetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, _BIT2) != 0);
}
#endif
//--------------------------------------------------
// Description  : Check Sram Switch Permission
// Input Value  : bit Switch Permission Status
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelSoftClampAdjust(BYTE ucSCSlop)
{
    Scaler32SetByte(PB00550_5C_LD_SOFT_CLAMP_PARA, 0, ucSCSlop);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerColorLDBLModelGainApplyDone(void)
{
    return (Scaler32GetBit(PB00550_08_LD_BACKLIGHT_READ_CTRL, _BIT5) == _BIT5) ? _TRUE : _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDBLModelGainApplyDoneClear(void)
{
    Scaler32SetBit(PB00550_08_LD_BACKLIGHT_READ_CTRL, ~(_BIT5 | _BIT1 | _BIT0), _BIT5);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDBLModelSetLvInterval(EnumLocalDimmingBLMInterval enumLocalDimmingBLMInterval)
{
    Scaler32SetByte(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, 0, ((DWORD)(enumLocalDimmingBLMInterval << 2) | enumLocalDimmingBLMInterval));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDBLModelDirectLEDLutStep(EnumLocalDimmingBLMDirectLutStep enumLocalDimmingBLMDirectLutStep)
{
    Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~(_BIT6), ((DWORD)enumLocalDimmingBLMDirectLutStep << 6));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDBLModelEdgeExtendMode(EnumFunctionOnOFF enumOn)
{
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT0), enumOn);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModelExtendSCurveThAdjust(BYTE *pucLDSCurveThTable, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucLDSCurveThTable, 32, ucBankAddress, PB00550_64_LD_9ST_S_CURVE_TH, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModeS1CurveTableAdjust(BYTE *pucBLLvTable, WORD usLength, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucBLLvTable, usLength, ucBankAddress, PB005DE_00_LD_DIRECT_BL_LUT + _BLM_S1LUTOFFSET, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDBLModeS2CurveTableAdjust(BYTE *pucBLLvTable, WORD usLength, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32(pucBLLvTable, usLength, ucBankAddress, PB005DE_00_LD_DIRECT_BL_LUT + _BLM_S2LUTOFFSET, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDBLModelUniqueGainEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00550_54_LD_BACKLIGHT_MODEL_DUMMY, ~_BIT5, _BIT5);
    }
    else
    {
        Scaler32SetBit(PB00550_54_LD_BACKLIGHT_MODEL_DUMMY, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDBLModelDeepBlackEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00550_58_LD_GAIN_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        Scaler32SetBit(PB00550_58_LD_GAIN_CTRL, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Backgroung Measure Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoBGEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB0050C_00_LD_HISTO_CONTROL_0, ~_BIT6, _BIT6);
    }
    else
    {
        Scaler32SetBit(PB0050C_00_LD_HISTO_CONTROL_0, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : LD Histogram Background Msb Adjust Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoBGMsbAdjust(BYTE ucBGMsb)
{
    Scaler32SetByte(PB0050C_18_LD_HISTO_BG_Y_MSB_0, 0, ucBGMsb);
}

//--------------------------------------------------
// Description  : Enable/Disable LDHisto Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB0050C_00_LD_HISTO_CONTROL_0, ~_BIT7, _BIT7);
    }
    else
    {
        Scaler32SetBit(PB0050C_00_LD_HISTO_CONTROL_0, ~_BIT7, 0x00);
    }
}
//--------------------------------------------------
// Description  : Write LD HistoLUT
// Input Value  : Table, Bank
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoLUTAdjust(BYTE *pucLDHistoTable, BYTE ucBankAddress)
{
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    ScalerUtilBurstWrite32(pucLDHistoTable, _LDHISTO_TABLE_SIZE_LUT, ucBankAddress, PB0050C_1C_LD_HISTO_LUT0_0, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_BIG);
#else
    WORD usIdx = 0;
    __attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
    DWORD pulApplyPWM[_LDHISTO_TABLE_SIZE_LUT / 2] = {0};

    while(usIdx < (_LDHISTO_TABLE_SIZE_LUT * 2))
    {
        pulApplyPWM[usIdx / 4] = (((DWORD)pucLDHistoTable[usIdx + 1]) << 24) | (((DWORD)pucLDHistoTable[usIdx]) << 16) |
                                 (((DWORD)pucLDHistoTable[usIdx + 3]) << 8) | (((DWORD)pucLDHistoTable[usIdx + 2]));
        usIdx += 4;
    }
    ScalerUtilBurstWrite32((BYTE *)pulApplyPWM, _LDHISTO_TABLE_SIZE_LUT * 2, ucBankAddress, PB0050D_00_LD_HISTO_LUT0_LOWLUT1, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_LITTLE);
#endif
}
//--------------------------------------------------
// Description  : Get Histogram lut value
// Input Value  : LUT Index
// Output Value : LUT 7 bits
//--------------------------------------------------
WORD ScalerColorLDHistoGetLUT(EnumLDLUTIndex enumLDLutInd)
{
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    return (WORD)Scaler32GetByte(PB0050C_1C_LD_HISTO_LUT0_0 + 4 * ((enumLDLutInd) / 4), ((enumLDLutInd) % 4));
#else
    return Scaler32GetWord(PB0050D_00_LD_HISTO_LUT0_LOWLUT1 + 4 * ((enumLDLutInd) / 2), (1 - (enumLDLutInd % 2)));
#endif
}
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN2)
//--------------------------------------------------
// Description  : Write LD Decision THD
// Input Value  : Table, Bank
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoDecisionAdjust(DWORD *pulLDDecisionTable, BYTE ucBankAddress)
{
    ScalerUtilBurstWrite32((BYTE *)pulLDDecisionTable, 1020, ucBankAddress, PB00508_00_LD_HISTO_DECISION_THD_0_0, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_FLASH, _ENDIAN_TYPE_LITTLE);
}
#endif
//--------------------------------------------------
// Description  : Enable PWM Proc
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT4 | _BIT0), (_BIT4 | _BIT0));
    }
    else
    {
        Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT4 | _BIT0), 0x00);
    }
}
//--------------------------------------------------
// Description  : Set PWM Proc Mode
// Input Value  : EnumPWMProcMode enumPWMProcMode
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcMode(EnumLDPWMProcMode enumPWMProcMode)
{
    switch(enumPWMProcMode)
    {
        case _LOCAL_DIMMING_HW_MODE:
            Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT9 | _BIT8), 0x00);
            break;
        case _LOCAL_DIMMING_ADJUST_FW_MODE:
            Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT9 | _BIT8), _BIT8);
            break;
        case _LOCAL_DIMMING_SMOOTH_FW_MODE:
            Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT9 | _BIT8), _BIT9);
            break;
        case _LOCAL_DIMMING_FW_MODE:
            Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT9 | _BIT8), (_BIT9 | _BIT8));
            break;
        default:
            break;
    };
}

//--------------------------------------------------
// Description  : Read PWM value
// Input Value  : WORD usIndex
// Output Value : usPWM
//--------------------------------------------------
WORD ScalerColorLDPWMProcReadPWM(WORD usIndex)
{
    BYTE ucAddrIndex = 0;
    WORD usPWM = 0;
    if(usIndex > (_LOCAL_DIMMING_TOTAL_REGION - 1))
    {
        usIndex = (_LOCAL_DIMMING_TOTAL_REGION - 1);
    }
    ucAddrIndex = (BYTE)((usIndex % 2) > 0 ? 0 : 1);
    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT12 | _BIT10), _BIT12);
    usPWM = Scaler32GetWord(PB00515_00_LD_PWM_TARGETPWM + (usIndex / 2), ucAddrIndex);
    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT12 | _BIT10), 0x00);

    return usPWM;
}

//--------------------------------------------------
// Description  : Read PWM Table
// Input Value  : WORD *pusPWMTable, WORD usPWMTableSize
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcReadPWMTable(WORD *pusPWMTable, WORD usPWMTableSize)
{
    WORD usTable0Size = MINOF(usPWMTableSize, _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE);

    // load table 0
    ScalerColorLDPWMProcReadPWMTableSub(pusPWMTable, usTable0Size, _LOCAL_DIMMING_PWM_SRAM0);

#if((_HW_LOCAL_DIMMING_TABLE1_SIZE != 0) || (_LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE != 0))
    // load table 1, if necessary
    if(usPWMTableSize > usTable0Size)
    {
        WORD *pusPWMTable1 = pusPWMTable + _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE;
        WORD usTable1Size = usPWMTableSize - usTable0Size;
        ScalerColorLDPWMProcReadPWMTableSub(pusPWMTable1, usTable1Size, _LOCAL_DIMMING_PWM_SRAM1);
    }
#endif
}

//--------------------------------------------------
// Description  : Read PWM Table Sub
// Input Value  : WORD *pusPWMTable, WORD usPWMTableSize, EnumLDPWMSRAMIndex enumLDPWMSRAMIndex
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcReadPWMTableSub(WORD *pusPWMTable, WORD usPWMTableSize, EnumLDPWMSRAMIndex enumLDPWMSRAMIndex)
{
    DWORD ulStartPWMTarget = PB00515_00_LD_PWM_TARGETPWM;
    WORD usMaxTableSize = _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE;
    enumLDPWMSRAMIndex = enumLDPWMSRAMIndex;
#if((_HW_LOCAL_DIMMING_TABLE1_SIZE != 0) || (_LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE != 0))
    if(enumLDPWMSRAMIndex == _LOCAL_DIMMING_PWM_SRAM1)
    {
        ulStartPWMTarget = PB006C0_00_LD_PWM_TARGETPWM_1;
        usMaxTableSize = _LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE;
    }
#endif

#if(_HW_LOCAL_DIMMING_PWM_TABLE_FORM_SEL != _HW_LOCAL_DIMMING_PWM_TABLE_FORM0)
    WORD uscnt = 0;
#endif
    if(usPWMTableSize > usMaxTableSize)
    {
        usPWMTableSize = usMaxTableSize;
    }

    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT12 | _BIT10), _BIT12);

    ScalerUtilReadWord(ulStartPWMTarget, usPWMTableSize, _AUTOINC, pusPWMTable);

#if(_HW_LOCAL_DIMMING_PWM_TABLE_FORM_SEL != _HW_LOCAL_DIMMING_PWM_TABLE_FORM0)
    for(uscnt = 0; uscnt < usPWMTableSize; uscnt++)
    {
        pusPWMTable[uscnt] = (pusPWMTable[uscnt] & 0xFFF);
    }
#endif
    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT12 | _BIT10), 0x00);
}


//--------------------------------------------------
// Description  : Apply Sram Switch Permission
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcSramSwitchApply(void)
{
    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10), _BIT10);
}

//--------------------------------------------------
// Description  : Check Sram Switch Permission
// Input Value  : bit Switch Permission Status
// Output Value : None
//--------------------------------------------------
bit ScalerColorLDPWMProcSramSwitchStatus(bit bWaitPolling)
{
    if(bWaitPolling == _NOT_WAIT)
    {
        return (Scaler32GetBit(PB00510_00_LD_PWM_PROCESS_CTRL, _BIT10) == _BIT10);
    }
    else
    {
        return ScalerTimerPollingFlagProc32Bit(_SMOOTH_TIMEOUT, PB00510_00_LD_PWM_PROCESS_CTRL, _BIT10, 1);
    }
}

//--------------------------------------------------
// Description  : Write PWM value
// Input Value  : WORD usPWM, WORD usIndex
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcWritePWM(WORD usPWM, WORD usIndex)
{
    BYTE ucAddrIndex = 0;
    if(usIndex > (_LOCAL_DIMMING_TOTAL_REGION - 1))
    {
        usIndex = (_LOCAL_DIMMING_TOTAL_REGION - 1);
    }
    ucAddrIndex = (BYTE)((usIndex % 2) > 0 ? 0 : 1);
    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT12 | _BIT10), _BIT12);
    Scaler32SetWord(PB00515_00_LD_PWM_TARGETPWM + (usIndex / 2), ucAddrIndex, usPWM);
    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT12 | _BIT10), 0x00);
}

//--------------------------------------------------
// Description  : Write PWM table
// Input Value  : WORD *pusPWMTable, WORD usPWMTableSize, BYTE ucBankNum
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcWritePWMTable(WORD *pusPWMTable, WORD usPWMTableSize, BYTE ucBankNum)
{
    WORD usSubTableSize = usPWMTableSize;

    if(usSubTableSize <= _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE)
    {
        ScalerColorLDPWMProcWritePWMTableSub(pusPWMTable, usSubTableSize, ucBankNum, _LOCAL_DIMMING_PWM_SRAM0);
    }
#if((_HW_LOCAL_DIMMING_TABLE1_SIZE != 0) || (_LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE != 0))
    else
    {
        ScalerColorLDPWMProcWritePWMTableSub(pusPWMTable, _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE, ucBankNum, _LOCAL_DIMMING_PWM_SRAM0);
        ScalerColorLDPWMProcWritePWMTableSub(pusPWMTable + _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE, usSubTableSize - _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE, ucBankNum, _LOCAL_DIMMING_PWM_SRAM1);
    }
#endif
}

//--------------------------------------------------
// Description  : Write PWM table
// Input Value  : WORD *pusPWMTable, WORD usPWMTableSize, BYTE ucBankNum
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcWritePWMTableSub(WORD *pusPWMTable, WORD usPWMTableSize, BYTE ucBankNum, EnumLDPWMSRAMIndex enumLDPWMSRAMIndex)
{
    WORD us4MultipleSize = 0;
    DWORD ulIdx = 0;
    DWORD ulStartPWMTarget = PB00515_00_LD_PWM_TARGETPWM;
    WORD usMaxTableSize = _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE;
    enumLDPWMSRAMIndex = enumLDPWMSRAMIndex;
#if((_HW_LOCAL_DIMMING_TABLE1_SIZE != 0) || (_LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE != 0))
    if(enumLDPWMSRAMIndex == _LOCAL_DIMMING_PWM_SRAM1)
    {
        ulStartPWMTarget = PB006C0_00_LD_PWM_TARGETPWM_1;
        usMaxTableSize = _LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE;
    }
#endif
    __attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
    DWORD pulApplyPWM[((_LOCAL_DIMMING_MAX_TABLE_BLOCK_SIZE / 2) + (_LOCAL_DIMMING_MAX_TABLE_BLOCK_SIZE % 2))];

    if(usPWMTableSize > usMaxTableSize)
    {
        usPWMTableSize = usMaxTableSize;
    }

    // Calculate table size with multiple of 4
    us4MultipleSize = (((usPWMTableSize * 2) + 3) & 0xFFFC);

    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT12 | _BIT10), _BIT12);

    while(ulIdx < usPWMTableSize)
    {
        pulApplyPWM[ulIdx / 2] = (((DWORD)pusPWMTable[ulIdx]) << 16) | (pusPWMTable[(ulIdx + 1)]);
        ulIdx += 2;
    }
    if((usPWMTableSize % 2) != 0)
    {
        if((usPWMTableSize / 2) < GET_TABLE_ELEMENT_NUM(pulApplyPWM))
        {
            pulApplyPWM[(usPWMTableSize / 2)] = pulApplyPWM[(usPWMTableSize / 2)] & 0xFFFF0000;
        }
        else
        {
            DebugMessageHDR("ScalerColorLDPWMProcWritePWMTable : (usPWMTableSize/2) > pulApplyPWM size", (usPWMTableSize / 2));
        }
    }

    ScalerUtilBurstWrite32((BYTE *)pulApplyPWM, us4MultipleSize, ucBankNum, ulStartPWMTarget, _BURSTWRITE32_DATA_AUTO_INC, _BURSTWRITE_FROM_XRAM, _ENDIAN_TYPE_LITTLE);
    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT12 | _BIT10), 0x00);
}



#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDPWMProcFrontBackEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        Scaler32SetBit(PB00510_AC_LD_PWM_PROCESS_FB_CTRL, ~(_BIT0), _BIT0);
    }
    else
    {
        Scaler32SetBit(PB00510_AC_LD_PWM_PROCESS_FB_CTRL, ~(_BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerColorLDPWMProcGetFrontBackEnable(void)
{
    return (Scaler32GetBit(PB00510_AC_LD_PWM_PROCESS_FB_CTRL, _BIT0) != 0);
}
#endif

//--------------------------------------------------
// Description  : PWM2SPI Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiEnable(EnumFunctionOnOFF enumOn)
{
    DWORD ultmpData = Scaler32GetDWord(PB00537_00_PWM2SPI_CONTROL1);

    if(enumOn == _FUNCTION_ON)
    {
        // Enable PWM2SPI IP
        Scaler32SetDWord(PB00537_00_PWM2SPI_CONTROL1, ((ultmpData & ~_BIT30) | _BIT31));

        ScalerSpiDimmingToggleUpdateSync();
    }
    else
    {
        // Disable PWM2SPI IP
        Scaler32SetDWord(PB00537_00_PWM2SPI_CONTROL1, (ultmpData & ~_BIT31));
        // Clear Transmit && UpdateSync flag
        Scaler32SetDWord(PB00537_04_PWM2SPI_CONTROL2, 0);
    }
}

//--------------------------------------------------
// Description  : Check if PWM2SPI SRam Mode is Enable now
// Input Value  : None
// Output Value : Sram Mode Enable Status
//--------------------------------------------------
bit ScalerColorLDPwmToSpiCheckSramModeEnable(void)
{
    if((Scaler32GetBit(PB00537_00_PWM2SPI_CONTROL1, _BIT31) == _BIT31) && (Scaler32GetBit(PB00538_00_SRAM_MODE_CONTROL1, _BIT31) == _BIT31))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check if PwmToSpi SPI Transmission already done
// Input Value  : None
// Output Value : _TRUE:finish ; _FALSE:not yet
//--------------------------------------------------
bit ScalerColorLDPwmToSpiCheckSpiTransmitStatus(void)
{
    return ((Scaler32GetDWord(PB00538_0C_SRAM_MODE_STATUS) & _BIT2) ? _TRUE : _FALSE);
}

//--------------------------------------------------
// Description  : Ack PwmToSpi SPI Transmission finish Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiAckSpiTransmitStatus(void)
{
    Scaler32SetBit(PB00538_0C_SRAM_MODE_STATUS, ~((DWORD)_BIT2), _BIT2);
}

//--------------------------------------------------
// Description  : Set PwmToSpi Update_Sync pin Trigger Source
// Input Value  : enumUpdSyncTriggerSrc --> PwmToSpi Upd_Sync Trigger Source
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetUpdateSyncTriggerSource(EnumUpdSyncTriggerSrc enumUpdSyncTriggerSrc)
{
    if(enumUpdSyncTriggerSrc == _UPD_SYNC_BY_LOCAL_DIMMING_GAIN_SYNC)
    {
        // BY LD Gain Sync
        Scaler32SetBit(PB00538_00_SRAM_MODE_CONTROL1, ~((DWORD)_BIT7), _BIT7);
    }
    else
    {
        // BY Manual
        Scaler32SetBit(PB00538_00_SRAM_MODE_CONTROL1, ~((DWORD)_BIT7), 0);
    }
}

//--------------------------------------------------
// Description  : Get PwmToSpi Update_Sync Trigger Source
// Input Value  : None
// Output Value : PwmToSpi Upd_Sync Trigger Source
//--------------------------------------------------
EnumUpdSyncTriggerSrc ScalerColorLDPwmToSpiGetUpdateSyncTriggerSource(void)
{
    if(Scaler32GetBit(PB00538_00_SRAM_MODE_CONTROL1, _BIT7) == _BIT7)
    {
        // BY LD Gain Sync
        return _UPD_SYNC_BY_LOCAL_DIMMING_GAIN_SYNC;
    }
    else
    {
        // By Manual
        return _UPD_SYNC_BY_MANUAL;
    }
}

//--------------------------------------------------
// Description  : Set Pwm2Spi Init Common Part
// Input Value  : ulValue --> value of Control Register
// Output Value : none
//--------------------------------------------------
void ScalerColorLDPwmToSpiInitCommon(EnumUpdSyncTriggerSrc enumUpdSyncTriggerSrc)
{
    DWORD ulCtrl1Value = 0;

    // Init PWMToSPI MOdule (disable PWM2SPI , enable remap table access)
    ulCtrl1Value = (_BIT30 |
                    (_LOCAL_DIMMING_PWM2SPI_PATTERN_OF_DUMMY_BYTE ? _BIT23 : 0) |
                    (_LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT ? _BIT20 : 0) |
                    (_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM ? _BIT19 : 0) |
                    (((DWORD)(enumUpdSyncTriggerSrc & 0x07)) << 16) |
                    (_BIT15 | _BIT14) |
                    (_BIT12) |
                    (_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PIN_INVERT ? _BIT11 : 0) |
                    (_LOCAL_DIMMING_PWM2SPI_APPEND_NUM_OF_BYTES ? _BIT8 : 0) |
                    ((BYTE)(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM)));

    Scaler32SetDWord(PB00537_00_PWM2SPI_CONTROL1, ulCtrl1Value);

    g_stSpiDimmingPwmToSpiInfo.ulDclkValue = GET_D_CLK_FREQ();
    ScalerColorLDPwmToSpiSetSyncPulseWidth(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS);
}

//--------------------------------------------------
// Description  : Set Pwm2Spi Sync Pulse Width Value
// Input Value  : ulValue --> value of Sync Pulse Width Register
// Output Value : none
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetSyncPulseWidth(DWORD ulValue)
{
    Scaler32SetDWord(PB00537_98_PWM2SPI_CONTROL3, ((ulValue * g_stSpiDimmingPwmToSpiInfo.ulDclkValue) / 2000));
}

//--------------------------------------------------
// Description  : Enable PwmToSpi Spi Output Swap
// Input Value  : bit bSwap
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSwapSpiOutput(bit bSwap)
{
    Scaler32SetBit(PB00537_A0_PWM2SPI_DUMMY1, ~((DWORD)(_BIT2 | _BIT1)), ((DWORD)bSwap << 1));
}

//--------------------------------------------------
// Description  : Check if PwmToSpi UpdSync Apply Done
// Input Value  : None
// Output Value : _TRUE:finish ; _FALSE:not yet
//--------------------------------------------------
bit ScalerColorLDPwmToSpiCheckUpdSyncApplyDone(void)
{
    return ((Scaler32GetDWord(PB00537_A0_PWM2SPI_DUMMY1) & _BIT2) ? _TRUE : _FALSE);
}

//--------------------------------------------------
// Description  : Ack PwmToSpi UpdSync Apply Done Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiAckUpdSyncApplyDone(void)
{
    Scaler32SetBit(PB00537_A0_PWM2SPI_DUMMY1, ~((DWORD)_BIT2), _BIT2);
}

//--------------------------------------------------
// Description  : Ack PwmToSpi UpdSync Apply Done Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerColorLDStepHWDone(void)
{
    return (Scaler32GetBit(PB00510_00_LD_PWM_PROCESS_CTRL, _BIT14) != 0);
}

//--------------------------------------------------
// Description  : Ack PwmToSpi UpdSync Apply Done Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDStepHWDoneClear(void)
{
    Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10), _BIT14);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiRunCallbackFunction(void)
{
    EnumColorPwm2SpiSramModeTxCallBackFuncId enumColorPwm2SpiSramModeTxCallBackFuncId = g_enumColorPwm2SpiSramModeTxCallBackFuncId;
    g_enumColorPwm2SpiSramModeTxCallBackFuncId = _COLOR_PWM2SPI_SRAM_TX_CALLBACK_NULL;

    switch(enumColorPwm2SpiSramModeTxCallBackFuncId)
    {
        case _COLOR_PWM2SPI_SRAM_TX_CALLBACK_LD:
            ScalerSpiDimmingLDSramModeSpiTxDoneCallBack();
            break;

        case _COLOR_PWM2SPI_SRAM_TX_CALLBACK_NULL:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : SRAM Mode SPI TX done CallBack function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSramModeTxDone_Handler(void)
{
    if(ScalerColorLDPwmToSpiCheckSpiTransmitStatus() == _TRUE)
    {
        // SRAM Mode SPI TX Done
        // Ack TX Done Status Flag
        ScalerColorLDPwmToSpiAckSpiTransmitStatus();

        // Call Back Function Process
        if(g_enumColorPwm2SpiSramModeTxCallBackFuncId != _COLOR_PWM2SPI_SRAM_TX_CALLBACK_NULL)
        {
            ScalerColorLDPwmToSpiRunCallbackFunction();
        }
    }
}

//--------------------------------------------------
// Description  : Init PwmToSpi SRAM Mode
// Input Value  : bEnable --> Enable PwmToSpi SRAM Mode
//                enumSModeClkSrc --> PwmToSpi SRAM Mode IP clk Source (0:dclk ; 1:iosc/ext_crystal)
//                enumSModeIntEn --> Enable Pwm2Spi SRAM Mode SPI TX Done INT
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetSramModeControl(bit bEnable, EnumSModeClkSrc enumSModeClkSrc, EnumSModeIntEn enumSModeIntEn, EnumSModeTxTiming enumSModeTxTiming, bit bSModeUpdSyncApplyFromLDGainSync, bit bSModeUpdSyncApplyMethod, EnumSModeUpdSyncApplyTiming enumSModeUpdSyncApplyTiming)
{
    DWORD ulValue = ((DWORD)bEnable << 31) | ((DWORD)enumSModeClkSrc << 30) | ((DWORD)enumSModeIntEn << 29) | ((DWORD)enumSModeTxTiming << 16) | ((DWORD)bSModeUpdSyncApplyFromLDGainSync << 7) | ((DWORD)enumSModeUpdSyncApplyTiming);

    if(bSModeUpdSyncApplyMethod == _SMODE_UPDSYNC_USE_SPI)
    {
#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
        if(GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_CONSTANT)
#endif
        {
#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM != 0)
            ulValue |= (_BIT4);
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
            ulValue |= (_BIT5);
#endif
#if((_HW_LOCAL_DIMMING_PWM2SPI_MAX_SPI > 2) && (_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0))
            ulValue |= (_BIT8);
#endif
        }
    }
    Scaler32SetDWord(PB00538_00_SRAM_MODE_CONTROL1, ulValue);
}

//--------------------------------------------------
// Description  : Pwm2Spi SPI TX for Dimming Data(trigger by 0xB0053804[0])
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiTxForDimming(void)
{
    Scaler32SetBit(PB00538_00_SRAM_MODE_CONTROL1, ~_BIT6, 0);
}

//--------------------------------------------------
// Description  : Pwm2Spi SPI TX for SPI UpdSync(trigger by 0xB0053808[0])
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiTxForUpdSync(void)
{
    Scaler32SetBit(PB00538_00_SRAM_MODE_CONTROL1, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Pwm2Spi SRAM Mode Start SPI Transmit
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiStartTX(void)
{
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX == _ON)
    ScalerColorLDPwmToSpiAckUpdSyncApplyDone();
    // Manual Apply UpdSync
    ScalerColorLDPwmToSpiManualApplyUpdSync();
    // Busy Delay UpdSync done
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_ALIGN_DVS == _ON)
    // check until 20ms timeout
    for(WORD usCnt = 0; usCnt < 2000; usCnt++)
    {
        if(ScalerColorLDPwmToSpiCheckUpdSyncApplyDone() == _TRUE)
        {
            break;
        }
        DELAY_10US();
    }
#else
    DELAY_XUS(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS);
#endif
#if(_LOCAL_DIMMING_PWM2SPI_DELAY_AFTER_UPD_SYNC_XUS != 0)
    DELAY_XUS(_LOCAL_DIMMING_PWM2SPI_DELAY_AFTER_UPD_SYNC_XUS);
#endif
#endif

    ScalerColorLDPwmToSpiTxForDimming();
    Scaler32SetDWord(PB00538_04_SRAM_MODE_CONTROL2, _BIT0);
}

//--------------------------------------------------
// Description  : Wait for HW SPI and Valid By CS to avoid conflit of SPI
// Input Value  : None
// Output Value : Polling SUCCESS or FAIL
//--------------------------------------------------
bit ScalerColorLDPwmToSpiWaitToIdle(void)
{
    if(Scaler32GetBit(PB00538_00_SRAM_MODE_CONTROL1, _BIT6) == 0)
    {
        // wait pwm2spi tx done
        if(ScalerTimerPollingFlagProc32Bit(_LOCAL_DIMMING_SPI_FW_WAIT_TIMEOUT, PB00538_04_SRAM_MODE_CONTROL2, _BIT0, 0) == _FALSE)
        {
            return _FAIL;
        }
    }
    else
    {
        // wait pwmspi valid by cs done
        if(ScalerTimerPollingFlagProc32Bit(_LOCAL_DIMMING_SPI_FW_WAIT_TIMEOUT, PB00538_08_SRAM_MODE_CONTROL3, _BIT0, 0) == _FALSE)
        {
            return _FAIL;
        }
    }
    return _SUCCESS;
}


//--------------------------------------------------
// Description  : Pwm2Spi SRAM Mode Manual Apply UpdSync
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiManualApplyUpdSync(void)
{
#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)
    ScalerColorLDPwmToSpiTxForUpdSync();
#endif
    Scaler32SetDWord(PB00538_08_SRAM_MODE_CONTROL3, _BIT0);
}

//--------------------------------------------------
// Description  : Pwm2Spi SRAM Mode Notify BLModel Spi Tx is done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiNotifyBLModelSpiTxDone(void)
{
    Scaler32SetBit(PB00538_0C_SRAM_MODE_STATUS, ~(_BIT2 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : Get Pwm2Spi SRAM Mode New Spi Tx Done Flag status
// Input Value  : None
// Output Value : Pwm2Spi SRAM Mode New Spi Tx Done Flag status
//--------------------------------------------------
bit ScalerColorLDPwmToSpiGetNewSpiTxDoneFlag(void)
{
    return ((Scaler32GetBit(PB00538_0C_SRAM_MODE_STATUS, _BIT0) == _BIT0) ? _TRUE : _FALSE);
}

//--------------------------------------------------
// Description  : Polling Pwm2Spi SRAM Mode New Spi Tx Done Flag
// Input Value  : None
// Output Value : Polling Result
//--------------------------------------------------
bit ScalerColorLDPwmToSpiPollingNewSpiTxDoneFlag(void)
{
    return ScalerTimerPollingXRAMFlagProc(_BLM_TIMEOUT, (DWORD)(&g_bSpiDimmingSramModeTxDoneFlag), _BIT0, 1);
}

//--------------------------------------------------
// Description  : Ack Pwm2Spi SRAM Mode Notify BLModel Spi Tx done Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiAckNewSpiTxDoneFlag(void)
{
    Scaler32SetBit(PB00538_0C_SRAM_MODE_STATUS, ~(_BIT2 | _BIT0), 0);
}

//--------------------------------------------------
// Description  : Pwm2Spi SRAM Mode Check if Spi is busy
// Input Value  : None
// Output Value : _TRUE:Busy , _FALSE:Idle
//--------------------------------------------------
bit ScalerColorLDPwmToSpiCheckSpiIsBusy(void)
{
    return (Scaler32GetBit(PB00538_0C_SRAM_MODE_STATUS, _BIT1) != 0x00);
}

//--------------------------------------------------
// Description  : Set PwmToSpi SRAM Mode UpdSync delay counter(count by dclk)
// Input Value  : ulDclkCnt --> UpdSync delay counter(count by dclk)
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetUpdSyncDeferCnt(DWORD ulDclkCnt)
{
    Scaler32SetDWord(PB00538_10_SRAM_MODE_UPD_SYNC_APPLY_DELAY, ulDclkCnt);
}

//--------------------------------------------------
// Description  : Set PwmToSpi SRAM Mode Command Entry Config
// Input Value  : enumPwmToSpiInterface --> Cmd Entry Pwm2Spi Interface
//                ulConfigValue --> Config Value
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetCmdEntryConfig(EnumPwmToSpiInterface enumPwmToSpiInterface, DWORD ulConfigValue)
{
    Scaler32SetDWord(PB00538_14_SRAM_MODE_SPI0_CMD_ENTRY_CFG + (enumPwmToSpiInterface << 2), ulConfigValue);
}

//--------------------------------------------------
// Description  : Set PwmToSpi SRAM Mode Specified Command Entry's Dummy Byte Number
// Input Value  : ucCmdEntryIdx --> Cmd Entry Index
//                ucCmdEntryDummyByteNum --> Dummy Byte Number(count by Byte) of specified Cmd Entry
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetCmdEntryDummyByteNum(BYTE ucCmdEntryIdx, BYTE ucCmdEntryDummyByteNum)
{
    Scaler32SetByte((PB00538_30_SRAM_MODE_CMD_ENTRY_DUMMY_CFG0 + ((DWORD)ucCmdEntryIdx >> 2)), (ucCmdEntryIdx & 0x03), ucCmdEntryDummyByteNum);
}

//--------------------------------------------------
// Description  : Set PwmToSpi SRAM Mode Specified Command Entry's Data Byte Range
// Input Value  : ucCmdEntryIdx --> Cmd Entry Index
//                usCmdEntryDataStartIndex --> Data Byte Start Index of specified Cmd Entry
//                usCmdEntryDataByteNumber --> Total Data Byte Number of specified Cmd Entry
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetCmdEntryDataRange(BYTE ucCmdEntryIdx, WORD usCmdEntryDataStartIndex, WORD usCmdEntryDataByteNumber)
{
    Scaler32SetDWord(PB00539_00_PWM2SPI_NEW_CMD_ENTRY + ((DWORD)ucCmdEntryIdx << 2), ((((DWORD)usCmdEntryDataByteNumber) << 16) | usCmdEntryDataStartIndex));
}

//--------------------------------------------------
// Description  : Get PwmToSpi SRAM Mode Specified Command Entry's Data Byte Range
// Input Value  : ucCmdEntryIdx --> Cmd Entry Index
//                pusCmdEntryDataStartIndex --> pointer of specified Cmd Entry's Data Byte Start Index
//                pusCmdEntryDataByteNumber --> pointer of specified Cmd Entry's Total Data Byte Number
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiGetCmdEntryDataRange(BYTE ucCmdEntryIdx, WORD *pusCmdEntryDataStartIndex, WORD *pusCmdEntryDataByteNumber)
{
    DWORD ulData = Scaler32GetDWord(PB00539_00_PWM2SPI_NEW_CMD_ENTRY + ((DWORD)ucCmdEntryIdx << 2));
    pusCmdEntryDataStartIndex[0] = (WORD)(ulData & 0x0000FFFF);
    pusCmdEntryDataByteNumber[0] = (WORD)((ulData >> 16) & 0x0000FFFF);
}

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
//--------------------------------------------------
// Description  : Set PwmToSpi UpdSync Signal Align PWM Period Count
// Input Value  : bAlignePwm0PeriodCnt: Align PWM Period Count
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiAlignPwm0PeriodCnt(bit bAlignePwm0PeriodCnt)
{
    Scaler32SetBit(PB00537_A0_PWM2SPI_DUMMY1, ~((DWORD)(_BIT3 | _BIT2)), ((DWORD)bAlignePwm0PeriodCnt << 3));

    if(bAlignePwm0PeriodCnt == _TRUE)
    {
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM0)
        DWORD ulData = (0 << 16);
#endif
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM1)
        DWORD ulData = (1 << 16);
#endif
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM2)
        DWORD ulData = (2 << 16);
#endif
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM3)
        DWORD ulData = (3 << 16);
#endif
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM4)
        DWORD ulData = (4 << 16);
#endif
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM5)
        DWORD ulData = (5 << 16);
#endif
        Scaler32SetDWord(PA40020_00_DIMMING_PWM0_CONTROL, (ulData | _BIT31 | ((DWORD)0xF << 8)));
    }
}

//--------------------------------------------------
// Description  : Set PwmToSpi Align PWM Period Count Value
// Input Value  : usPwm0PeriodCnt: Align PWM Period Count Value
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetPwm0PeriodCnt(WORD usPwm0PeriodCnt)
{
    Scaler32SetDWord(PA40020_04_DIMMING_PWM0_PERIOD_CNT, usPwm0PeriodCnt);
}

//--------------------------------------------------
// Description  : Set PwmToSpi Align PWM Period Count Pulse Adjust Delay(count by dimmingPwm Clk)
// Input Value  : usPwm0PeriodCntPulseDelayCnt: PWM Period Count Pulse Adjust Delay(count by dimmingPwm Clk)
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPwmToSpiSetPwm0PeriodCntPulseDelay(WORD usPwm0PeriodCntPulseDelayCnt)
{
    Scaler32SetDWord(PA40020_08_DIMMING_PWM0_PERIOD_DELAY_CNT, usPwm0PeriodCntPulseDelayCnt);
}
#endif

//--------------------------------------------------
// Description  : Enable Smooth filter
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDSmoothEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT2), _BIT2);
    }
    else
    {
        Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT10 | _BIT2), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust gain value
// Input Value  : BYTE ucGain
// Output Value : None
//--------------------------------------------------
void ScalerColorLDSmoothGainAdjust(BYTE ucGain)
{
    Scaler32SetByte(PB00510_84_LD_PWM_SMOOTH_PARA0, 0, ucGain);
}

//--------------------------------------------------
// Description  : Enable smooth gain stage
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDSmoothGainEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~(_BIT1), _BIT1);
    }
    else
    {
        Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~(_BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust Moving average matrix
// Input Value  : BYTE ucMatrixLevel, BYTE ucLocalDimmingSmoothParaSel
// Output Value : None
//--------------------------------------------------
void ScalerColorLDSmoothMatrixAdjust(BYTE ucMatrixLevel, BYTE ucLocalDimmingSmoothParaSel)
{
    BYTE ucI = 0;
    WORD pusMatrix[25] = {0};
    BYTE ucSmoothParaNum = 0;
    WORD usSum = 0;
    StructLocalDimmingSmoothData *pstCurrentPara;

    ucSmoothParaNum = (sizeof(tLocalDimmingSmoothPara) / sizeof(tLocalDimmingSmoothPara[0]));
    pstCurrentPara = &tLocalDimmingSmoothPara[(ucLocalDimmingSmoothParaSel % ucSmoothParaNum)];
    if(ucLocalDimmingSmoothParaSel != (ucLocalDimmingSmoothParaSel % ucSmoothParaNum))
    {
        pstCurrentPara = &tLocalDimmingSmoothPara[0];
    }

    memcpy(pusMatrix, pstCurrentPara->pusSmoothTable, sizeof(pusMatrix));
    ucMatrixLevel = MINOF(50, ucMatrixLevel); // 0~50 : smooth effect

    for(ucI = 0; ucI < 25; ucI++)
    {
        if(ucI == 12)
        {
            continue;
        }
        pusMatrix[ucI] = ((DWORD)pusMatrix[ucI] * ucMatrixLevel) / 50;
        usSum += pusMatrix[ucI];
    }

    pusMatrix[12] = MINOF(8192 - usSum, 8191);

    for(ucI = 0; ucI < 12; ucI++)
    {
        Scaler32SetDWord(PB00510_50_LD_PWM_SMOOTH_M0 + 4 * ucI, ((DWORD)pusMatrix[ucI * 2] << 16) | pusMatrix[(ucI * 2) + 1]);
    }
    Scaler32SetDWord(PB00510_50_LD_PWM_SMOOTH_M0 + 4 * ucI, ((DWORD)pusMatrix[24] << 16));
}

//--------------------------------------------------
// Description  : Adjust tuning parameter
// Input Value  : WORD usThresholdS, WORD usThresholdL
// Output Value : None
//--------------------------------------------------
void ScalerColorLDSmoothTuningAdjust(WORD usThresholdS, WORD usThresholdL)
{
    Scaler32SetDWord(PB00510_8C_LD_PWM_SMOOTH_PARA2, ((DWORD)usThresholdL << 16) | usThresholdS);
}

//--------------------------------------------------
// Description  : Enable SmoothTuning stage
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDSmoothTuningEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~(_BIT0), _BIT0);
    }
    else
    {
        Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~(_BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable Step Change
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDStepEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT13 | _BIT10 | _BIT3), (_BIT13 | _BIT3));
    }
    else
    {
        Scaler32SetBit(PB00510_00_LD_PWM_PROCESS_CTRL, ~(_BIT14 | _BIT13 | _BIT10 | _BIT3), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust Fix PWM
// Input Value  : WORD usFixPWM
// Output Value : None
//--------------------------------------------------
void ScalerColorLDStepFixPWMAdjust(WORD usFixPWM)
{
    Scaler32SetDWord(PB00510_A4_LD_PWM_SC_FIX_PWM_TARGET, usFixPWM);
}

//--------------------------------------------------
// Description  : Enable Fix PWM
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDStepFixPWMEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_90_LD_PWM_SC_CTRL, ~(_BIT2 | _BIT1), _BIT1);
    }
    else
    {
        Scaler32SetBit(PB00510_90_LD_PWM_SC_CTRL, ~(_BIT2 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust Initial PWM
// Input Value  : WORD usInitialPWM
// Output Value : None
//--------------------------------------------------
void ScalerColorLDStepInitilalPWMAdjust(WORD usInitialPWM)
{
    Scaler32SetDWord(PB00510_A8_LD_PWM_SC_STEP_INITIAL_PWM, usInitialPWM);
    Scaler32SetBit(PB00510_90_LD_PWM_SC_CTRL, ~(_BIT2), _BIT2);
}

//--------------------------------------------------
// Description  : Set Step Change Mode
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLDStepMode(EnumLDStepMode enumStepChangeMode)
{
    if(enumStepChangeMode == _LOCAL_DIMMING_TIMER_MODE)
    {
        Scaler32SetBit(PB00510_90_LD_PWM_SC_CTRL, ~(_BIT2 | _BIT0), 0x00);
    }
    else
    {
        Scaler32SetBit(PB00510_90_LD_PWM_SC_CTRL, ~(_BIT2 | _BIT0), _BIT0);
    }
}

//--------------------------------------------------
// Description  : Adjust Step mode parameter
// Input Value  : WORD usMaxStep
// Output Value : None
//--------------------------------------------------
void ScalerColorLDStepStepAdjust(WORD usMaxStep)
{
    Scaler32SetDWord(PB00510_A0_LD_PWM_SC_STEP_MODE_MAX_STEP, usMaxStep);
}

//--------------------------------------------------
// Description  : Adjust timer mode parameter
// Input Value  : WORD usMaxStep, WORD usMinStep, BYTE ucTimer
// Output Value : None
//--------------------------------------------------
void ScalerColorLDStepTimerAdjust(WORD usMaxStep, WORD usMinStep, BYTE ucTimer)
{
    Scaler32SetByte(PB00510_94_LD_PWM_SC_TIMER_MODE_PARA, 0, ucTimer);
    Scaler32SetDWord(PB00510_98_LD_PWM_SC_TIMER_MODE_MIN_STEP, usMinStep);
    Scaler32SetDWord(PB00510_9C_LD_PWM_SC_TIMER_MODE_MAX_STEP, usMaxStep);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDSmoothModify(WORD *pusApplyPWM, WORD *pusHistoPWM, BYTE ucLocalDimmingSmoothParaSel)
{
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    WORD uscnt = 0;
    WORD usSmoothPWMMax = 0;
    WORD usSmoothPWMMin = 4095;
    DWORD ulTempPWM = 0;
#else
    pusApplyPWM = pusApplyPWM;
    pusHistoPWM = pusHistoPWM;
#endif
    WORD usSmoothParaGain = 0;
    BYTE ucSmoothParaNum = 0;
    StructLocalDimmingSmoothData *pstCurrentPara;
    ucSmoothParaNum = (sizeof(tLocalDimmingSmoothPara) / sizeof(tLocalDimmingSmoothPara[0]));
    pstCurrentPara = &tLocalDimmingSmoothPara[(ucLocalDimmingSmoothParaSel % ucSmoothParaNum)];

    if(ucLocalDimmingSmoothParaSel != (ucLocalDimmingSmoothParaSel % ucSmoothParaNum))
    {
        pstCurrentPara = &tLocalDimmingSmoothPara[0];
    }

#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_DIRECT_BACKLIGHT)
    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        pusApplyPWM[uscnt] = MAXOF(pusHistoPWM[uscnt], pusApplyPWM[uscnt]);
    }
#endif
    usSmoothParaGain = MINOF(pstCurrentPara->usSmoothGain, 1280);
    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        if(pusApplyPWM[uscnt] > usSmoothPWMMax)
        {
            usSmoothPWMMax = pusApplyPWM[uscnt];
        }
        if(pusApplyPWM[uscnt] < usSmoothPWMMin)
        {
            usSmoothPWMMin = pusApplyPWM[uscnt];
        }
    }

    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        if(pusApplyPWM[uscnt] < (pusHistoPWM[uscnt]))
        {
            pusApplyPWM[uscnt] = pusHistoPWM[uscnt];
        }
        if(pusApplyPWM[uscnt] > usSmoothPWMMin)
        {
            ulTempPWM = (pusApplyPWM[uscnt] * (256 + (DWORD)usSmoothParaGain)) >> 8;
            pusApplyPWM[uscnt] = (WORD)MINOF(usSmoothPWMMax, ulTempPWM);
        }
        if(pusApplyPWM[uscnt] > 4095)
        {
            pusApplyPWM[uscnt] = 4095;
        }
    }
#else
    usSmoothParaGain = MINOF(pstCurrentPara->usSmoothGain, 16128);
    ScalerColorLDSmoothSetShiftGain(usSmoothParaGain);
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDStepChangeModify(WORD *pusApplyPWM, WORD *pusLastApplyPWM, WORD *pusHistoPWM, BYTE ucStepLevel, BYTE ucColorLDHistoLutMin, StructLocalDimmingBLMSoftClampPara stColorLocalDimmingBLMSoftClampPara, StructLocalDimmingPWMType *pstColorLocalDimmingPWMType)
{
    WORD uscnt = 0;
    WORD usStepLevelTemp = 0;
    WORD usMaxDeltaPWM = 0;
    WORD usMaxDeltaTargetPWM = 0;


    usStepLevelTemp = (((100 - ucStepLevel) < 1) ? 1 : (100 - ucStepLevel));
    ucColorLDHistoLutMin = ucColorLDHistoLutMin;
    pusHistoPWM = pusHistoPWM;
    stColorLocalDimmingBLMSoftClampPara = stColorLocalDimmingBLMSoftClampPara;



    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        // fit smooth effect
        switch(pstColorLocalDimmingPWMType->enumSmoothType)
        {
            case _LOCAL_DIMMING_SMOOTH_TYPE_OFF:
                pusApplyPWM[uscnt] = pusHistoPWM[uscnt];
                break;

            case _LOCAL_DIMMING_SMOOTH_TYPE_EXCEPT_BLACK:
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
                if(pusHistoPWM[uscnt] <= (((ucColorLDHistoLutMin + 1) * 4095 + 64) >> 7))
#elif(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN2)
                if(pusHistoPWM[uscnt] <= (ScalerColorLDHistoGetLUT(_LOCAL_DIMMING_HISTO_LUT00)))
#endif
                {
                    pusApplyPWM[uscnt] = pusHistoPWM[uscnt];
                }
                break;

            case _LOCAL_DIMMING_SMOOTH_TYPE_ON:
            default:
                break;
        }

        // calculate final Apply PWM based on the mode of step change (one step mode will skip this process)
        if(pstColorLocalDimmingPWMType->enumStepChangeType == _LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL)
        {
            if((tPWMDereaseStepTable[0] == 1024) && (tPWMInreaseStepTable[0] == 1024))
            {
                WORD usDeltaPWM = 0;
                WORD usTempPWM = 0;
                usDeltaPWM = abs(pusApplyPWM[uscnt] - pusLastApplyPWM[uscnt]) / usStepLevelTemp;
                usDeltaPWM = (usDeltaPWM > 16) ? usDeltaPWM : 16;
                if(abs(pusApplyPWM[uscnt] - pusLastApplyPWM[uscnt]) > usDeltaPWM)
                {
                    if(pusApplyPWM[uscnt] > pusLastApplyPWM[uscnt])
                    {
                        usTempPWM = pusApplyPWM[uscnt];
                        pusApplyPWM[uscnt] = pusLastApplyPWM[uscnt] + usDeltaPWM;
                        if((usTempPWM - pusApplyPWM[uscnt]) > usMaxDeltaPWM)
                        {
                            usMaxDeltaPWM = usMaxDeltaTargetPWM - pusApplyPWM[uscnt];
                            usMaxDeltaTargetPWM = usTempPWM;
                        }
                    }
                    else
                    {
                        pusApplyPWM[uscnt] = pusLastApplyPWM[uscnt] - usDeltaPWM;
                    }
                }
            }
            else
            {
                WORD usTargetPWM = pusApplyPWM[uscnt];
                WORD usStepR = 30;
                if(pusLastApplyPWM[uscnt] > usTargetPWM)
                {
                    usStepR = tPWMDereaseStepTable[((DWORD)(pusLastApplyPWM[uscnt] - usTargetPWM) * 255 + 2047) / 4095];
                    usStepR = usStepR * 50 / usStepLevelTemp;
                    if(usStepR > 1024)
                    {
                        usStepR = 1024;
                    }
                    pusApplyPWM[uscnt] = ((((DWORD)usStepR * usTargetPWM) + ((DWORD)(1024 - usStepR) * pusLastApplyPWM[uscnt])) + 512) / 1024;
                }
                else if(pusLastApplyPWM[uscnt] < usTargetPWM)
                {
                    usStepR = tPWMInreaseStepTable[((DWORD)(usTargetPWM - pusLastApplyPWM[uscnt]) * 255 + 2047) / 4095];
                    usStepR = usStepR * 50 / usStepLevelTemp;
                    if(usStepR > 1024)
                    {
                        usStepR = 1024;
                    }

                    pusApplyPWM[uscnt] = ((((DWORD)usStepR * usTargetPWM) + ((DWORD)(1024 - usStepR) * pusLastApplyPWM[uscnt])) + 512) / 1024;
                    if((usTargetPWM - pusApplyPWM[uscnt]) > usMaxDeltaPWM)
                    {
                        usMaxDeltaPWM = usTargetPWM - pusApplyPWM[uscnt];
                        usMaxDeltaTargetPWM = usTargetPWM;
                    }
                }
            }
        }

        // clamp
        if(pusApplyPWM[uscnt] > 4095)
        {
            pusApplyPWM[uscnt] = 4095;
        }
        stColorLocalDimmingBLMSoftClampPara.usMaxDeltaPWM = MINOF(4095, usMaxDeltaPWM);
        stColorLocalDimmingBLMSoftClampPara.usMaxDeltaTargetPWM = MINOF(4095, usMaxDeltaTargetPWM);
        // DebugMessageHDR("PWM", pusApplyPWM[uscnt]);
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDStepChangeModifyDirectType(WORD *pusApplyPWM, WORD *pusLastApplyPWM, WORD *pusHistoPWM, WORD *pusLastHistoPWM, BYTE ucStepLevel, EnumLDStepChangeType enumLDStepChangeType)
{
    WORD uscnt = 0;
    WORD usStepLevelTemp = 0;
    usStepLevelTemp = (((100 - ucStepLevel) < 1) ? 1 : (100 - ucStepLevel));

    if(enumLDStepChangeType == _LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL)
    {
        for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
        {
            WORD usTargetPWM = pusApplyPWM[uscnt];
            WORD usStepR = 30;
            WORD usHisDelta = abs(pusHistoPWM[uscnt] - pusLastHistoPWM[uscnt]);
            if(pusLastApplyPWM[uscnt] > usTargetPWM)
            {
                usStepR = tPWMDereaseStepTable[((DWORD)usHisDelta * 255 + 2047) / 4095];
                usStepR = usStepR * 50 / usStepLevelTemp;
                if(usStepR > 1024)
                {
                    usStepR = 1024;
                }
                pusApplyPWM[uscnt] = ((((DWORD)usStepR * usTargetPWM) + ((DWORD)(1024 - usStepR) * pusLastApplyPWM[uscnt])) + 512) / 1024;

                if((pusApplyPWM[uscnt] == pusLastApplyPWM[uscnt]) && (pusApplyPWM[uscnt] > usTargetPWM) && (pusApplyPWM[uscnt] > 1))
                {
                    pusApplyPWM[uscnt] = pusApplyPWM[uscnt] - 1;
                }
            }
            else if(pusLastApplyPWM[uscnt] < usTargetPWM)
            {
                usStepR = tPWMInreaseStepTable[((DWORD)usHisDelta * 255 + 2047) / 4095];
                usStepR = usStepR * 50 / usStepLevelTemp;
                if(usStepR > 1024)
                {
                    usStepR = 1024;
                }
                pusApplyPWM[uscnt] = ((((DWORD)usStepR * usTargetPWM) + ((DWORD)(1024 - usStepR) * pusLastApplyPWM[uscnt])) + 512) / 1024;
                if((pusApplyPWM[uscnt] == pusLastApplyPWM[uscnt]) && (pusApplyPWM[uscnt] < usTargetPWM))
                {
                    pusApplyPWM[uscnt] = pusApplyPWM[uscnt] + 1;
                }
            }
            if(pusApplyPWM[uscnt] > 4095)
            {
                pusApplyPWM[uscnt] = 4095;
            }
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDOSDStepChange(WORD *pusApplyPWM, WORD *pusLastApplyPWM, BYTE ucOSDStepLevel)
{
    WORD uscnt = 0;
    WORD usDeltaPWM = 0;
    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        usDeltaPWM = abs(4095 - pusLastApplyPWM[uscnt]) / (((100 - ucOSDStepLevel) < 1) ? 1 : (100 - ucOSDStepLevel));
        usDeltaPWM = (usDeltaPWM > 16) ? usDeltaPWM : 16;
        if(abs(4095 - pusLastApplyPWM[uscnt]) > usDeltaPWM)
        {
            pusApplyPWM[uscnt] = pusLastApplyPWM[uscnt] + usDeltaPWM;
        }
        else
        {
            pusApplyPWM[uscnt] = 4095;
        }
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerColorLDPWMAbilityRatio(WORD *pusApplyPWM, WORD usRegion)
{
    DWORD ulTotalRatio = 0;
    BYTE ucRatio = 0;
    for(usRegion = 0; usRegion < _LOCAL_DIMMING_TOTAL_REGION; usRegion++)
    {
        ulTotalRatio = ulTotalRatio + ((DWORD)pusApplyPWM[usRegion] * 100 + 2048) / 4095;
    }

    ucRatio = ulTotalRatio / _LOCAL_DIMMING_TOTAL_REGION;

    if(ucRatio > 100)
    {
        ucRatio = 100;
    }
    return ucRatio;
}
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerColorLDGetFrontBackStatus(void)
{
    return ((ScalerColorLDBLModelGetFrontBackEnable() == _TRUE) &&
            (ScalerColorLDPWMProcGetFrontBackEnable() == _TRUE));
}
#endif
//--------------------------------------------------
// Description  : Disable SmoothToMax function and turn on Inverse Protect
// Input Value  : EnumFunctionOnOFF
// Output Value : none
//--------------------------------------------------
void ScalerColorLDSmoothToMaxDisable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_C0_LD_DUMMY, ~(_BIT8), _BIT8);
#if(_HW_LOCAL_DIMMING_GEN_SEL != _HW_LOCAL_DIMMING_GEN1)
        Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~_BIT3, _BIT3);
#endif
    }
    else
    {
        Scaler32SetBit(PB00510_C0_LD_DUMMY, ~(_BIT8), 0x00);
#if(_HW_LOCAL_DIMMING_GEN_SEL != _HW_LOCAL_DIMMING_GEN1)
        Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~_BIT3, 0);
#endif
    }
}

//--------------------------------------------------
// Description  : Adjust Shift gain
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerColorLDSmoothShiftGain(void)
{
    Scaler32SetByte(PB00510_4C_LD_PWM_SMOOTH_CTRL, 1, 0);
}
//--------------------------------------------------
// Description  : Adjust Shrink gain
// Input Value  : ucMatrixLevel
// Output Value : none
//--------------------------------------------------
void ScalerColorLDSmoothShrinkGain(BYTE ucMatrixLevel)
{
    if(ucMatrixLevel < 50)
    {
        ucMatrixLevel = 50;
    }
    WORD usShrinkGainValue = ((100 - (WORD)ucMatrixLevel) * 256) / 50;
    Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~_BIT(24, 16), ((DWORD)(usShrinkGainValue & 0x1FF) << 16));
}
//--------------------------------------------------
// Description  : SmoothRerangeEnable
// Input Value  : EnumFunctionOnOFF
// Output Value : none
//--------------------------------------------------
void ScalerColorLDSmoothRerangeEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~(_BIT2), _BIT2);
    }
    else
    {
        Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~(_BIT2), 0x00);
    }
}

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Local Histogram THD setting
// Input Value  : CoverRate
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoSetTHD(BYTE ucTHD)
{
    Scaler32SetByte(PB0050C_10_LD_HISTO_THD_0, 0, ucTHD);
}
#endif

#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
//--------------------------------------------------
// Description  : Local Histogram white THD setting
// Input Value  : CoverRate
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoSetWhiteTHD(BYTE ucTHD)
{
    Scaler32SetByte(PB0050C_10_LD_HISTO_THD_0, 1, ucTHD);
}
//--------------------------------------------------
// Description  : Local Histogram white code value
// Input Value  : code value 10 bits
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoSetWhiteValue(WORD usWhiteValue)
{
    Scaler32SetWord(PB0050C_10_LD_HISTO_THD_0, 1, usWhiteValue);
}
//--------------------------------------------------
// Description  : Local Histogram Black THD setting
// Input Value  : CoverRate
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoSetBlackTHD(BYTE ucTHD)
{
    Scaler32SetByte(PB0050C_14_LD_HISTO_TRUNC_BIT_0, 1, ucTHD);
}
//--------------------------------------------------
// Description  : Local Histogram black code value
// Input Value  : code value 10 bits
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoSetBlackValue(WORD usBlackValue)
{
    Scaler32SetWord(PB0050C_14_LD_HISTO_TRUNC_BIT_0, 1, usBlackValue);
}
//--------------------------------------------------
// Description  : Local Histogram black LUT
// Input Value  : LUT: 7 bits
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoSetBlackLUT(BYTE ucBlackLUT)
{
    Scaler32SetByte(PB0050C_3C_LD_HISTO_LUT_BLACK_WHITE_0, 0, ucBlackLUT);
}
//--------------------------------------------------
// Description  : Get Local Histogram black LUT
// Input Value  : None
// Output Value : LUT 7 bits
//--------------------------------------------------
BYTE ScalerColorLDHistoGetBlackLUT(void)
{
    return Scaler32GetByte(PB0050C_3C_LD_HISTO_LUT_BLACK_WHITE_0, 0);
}
//--------------------------------------------------
// Description  : Local Histogram White LUT
// Input Value  : LUT: 7 bits
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoSetWhiteLUT(BYTE ucWhiteLUT)
{
    Scaler32SetByte(PB0050C_3C_LD_HISTO_LUT_BLACK_WHITE_0, 1, ucWhiteLUT);
}
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumLDPWMSmoothPattern ScalerColorLDGetAdaptiveSmoothPattern(WORD *pusHistoPWM)
{
    WORD uscnt = 0;
    EnumLDPWMSmoothPattern enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    WORD usColorLDHistoLutMax = (WORD)((((DWORD)(Scaler32GetByte(PB0050C_3C_LD_HISTO_LUT_BLACK_WHITE_0, 1) + 1)) * 4095 + 64) >> 7);
    WORD usColorLDHistoLutMin = (WORD)((((DWORD)(Scaler32GetByte(PB0050C_3C_LD_HISTO_LUT_BLACK_WHITE_0, 0) + 1)) * 4095 + 64) >> 7);
#else
    WORD usColorLDHistoLutMax = ScalerColorLDHistoGetLUT(_LOCAL_DIMMING_HISTO_LUT255);
    WORD usColorLDHistoLutMin = ScalerColorLDHistoGetLUT(_LOCAL_DIMMING_HISTO_LUT00);
#endif

    // DebugMessageSystem("MAX", usColorLDHistoLutMax);
    // DebugMessageSystem("MIN", usColorLDHistoLutMin);

    if ((g_ucColorCornerHorReg == 0) || (g_ucColorCornerRStart == 0) || (g_ucColorCornerCStart == 0)) // unusual resolution ratio
    {
        return _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
    }
#if(_LOCAL_DIMMING_PANEL_REGION_VERTICAL < 2)
    // left
    for(uscnt = 0; uscnt < g_ucColorCornerHorReg; uscnt++)
    {
        if(pusHistoPWM[uscnt] == usColorLDHistoLutMax)
        {
            enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN;
        }
        else
        {
            enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
            break;
        }
    }
    // right
    if(enumLDPWMSmoothPattern == _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN)
    {
        for(uscnt = g_ucColorCornerRStart; uscnt < _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL; uscnt++)
        {
            if(pusHistoPWM[uscnt] == usColorLDHistoLutMax)
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN;
            }
            else
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
                break;
            }
        }
    }
    // center
    if(enumLDPWMSmoothPattern == _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN)
    {
        for(uscnt = g_ucColorCornerCStart; uscnt <= (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL / 2); uscnt++)
        {
            if(pusHistoPWM[uscnt] == usColorLDHistoLutMin)
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN;
            }
            else
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
                break;
            }
        }
    }
#else
    // top right
    for(uscnt = g_ucColorCornerRStart; uscnt < _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL; uscnt++)
    {
        if(pusHistoPWM[uscnt] == usColorLDHistoLutMax)
        {
            enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN;
        }
        else
        {
            enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
            break;
        }
    }
    // bottom left
    if(enumLDPWMSmoothPattern == _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN)
    {
        for(uscnt = _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL; uscnt < (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + g_ucColorCornerHorReg); uscnt++)
        {
            if(pusHistoPWM[uscnt] == usColorLDHistoLutMax)
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN;
            }
            else
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
                break;
            }
        }
    }
    // center top
    if(enumLDPWMSmoothPattern == _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN)
    {
        for(uscnt = g_ucColorCornerCStart; uscnt <= (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL / 2); uscnt++)
        {
            if(pusHistoPWM[uscnt] == usColorLDHistoLutMin)
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN;
            }
            else
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
                break;
            }
        }
    }
    // center bottom
    if(enumLDPWMSmoothPattern == _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN)
    {
        for(uscnt = (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + g_ucColorCornerCStart); uscnt <= (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL / 2)); uscnt++)
        {
            if(pusHistoPWM[uscnt] == usColorLDHistoLutMin)
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN;
            }
            else
            {
                enumLDPWMSmoothPattern = _LOCAL_DIMMING_SMOOTH_NORMAL_PATTERN;
                break;
            }
        }
    }
#endif

    // DebugMessageSystem("Enum Pattern", enumLDPWMSmoothPattern);
    // DebugMessageSystem("CornerHorReg",g_ucColorCornerHorReg);
    // DebugMessageSystem("ColorCornerRStart",g_ucColorCornerRStart);
    // DebugMessageSystem("ColorCornerCStart",g_ucColorCornerCStart);
    return enumLDPWMSmoothPattern;
}

//-----------------------------------------------------
// Description  : calculate the parameters of corner pattern
// Input Value  : void
// Output Value : void
//-----------------------------------------------------
void ScalerColorLDAdaptiveSmoothInit(void)
{
    WORD usColorCornerWidPer = 0;
    WORD usPanelHVRatio = (WORD)(((DWORD)_PANEL_DH_WIDTH * 100) / _PANEL_DV_HEIGHT);

    if(usPanelHVRatio <= 160)
    {
        usColorCornerWidPer = 1767;
    }
    else if(usPanelHVRatio <= 178)
    {
        usColorCornerWidPer = 1677;
    }
    else if(usPanelHVRatio <= 234)
    {
        usColorCornerWidPer = 1463;
    }
    else if(usPanelHVRatio <= 356)
    {
        usColorCornerWidPer = 1185;
    }
    else
    {
        g_ucColorCornerHorReg = 0;  // fail : ScalerColorLDAdaptiveSmoothPattern return normal type
        g_ucColorCornerRStart = 0;
        g_ucColorCornerCStart = 0;
        return;
    }

    g_ucColorCornerHorReg = ((usColorCornerWidPer * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL) / 10000) + (usColorCornerWidPer % (10000 / _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL) > 0 ? 1 : 0);
    g_ucColorCornerRStart = _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL - g_ucColorCornerHorReg;
    g_ucColorCornerCStart = _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL / 2 - (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL % 2 > 0 ? 0 : 1);

    // DebugMessageSystem("ColorCornerWidPer",usColorCornerWidPer);
    // DebugMessageSystem("CornerHorReg",g_ucColorCornerHorReg);
    // DebugMessageSystem("ColorCornerRStart",g_ucColorCornerRStart);
    // DebugMessageSystem("ColorCornerCStart",g_ucColorCornerCStart);
}
#endif

//--------------------------------------------------
// Description  : Local Dimming Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDPWMProcInitial(void)
{
    WORD usMaxStep = 0xFFF;
    WORD usMinStep = 0xFFF;
    BYTE ucTimer = 0xFF;
    BYTE ucMatrixLevel = 0;
    WORD usInitialPWM = 0xFFF;
    EnumLDStepMode enumStepChangeMode = _LOCAL_DIMMING_TIMER_MODE;
    EnumLDPWMProcMode enumPWMProcMode = _LOCAL_DIMMING_FW_MODE;
    BYTE ucLocalDimmingSmoothParaSel = 0;

    Scaler32SetDWord(PB00510_04_LD_PWM_PROCESS_BACKLIGHT_TYPE,
                     (((DWORD)tLocalDimmingPanelRegions[1] - 1) << 16) |
                     ((tLocalDimmingPanelRegions[0] - 1) << 8) |
                     _LOCAL_DIMMING_BACKLIGHT_TYPE);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerColorLDPWMProcFrontBackEnable(_ENABLE);
    }
    else
    {
        ScalerColorLDPWMProcFrontBackEnable(_DISABLE);
    }
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
    ScalerColorLDAdaptiveSmoothInit();
#endif

    ScalerColorLDPWMProcMode(enumPWMProcMode);
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    ScalerColorLDAdjustInitial();
#endif
    // ScalerColorLDAdjustDirectMaskAdjust(tLocalDimmingAdjustDirectMask, GET_CURRENT_BANK_NUMBER());
    ScalerColorLDSmoothMatrixAdjust(ucMatrixLevel, ucLocalDimmingSmoothParaSel);
    ScalerColorLDSmoothShiftGain();
    ScalerColorLDStepMode(enumStepChangeMode);
    ScalerColorLDStepTimerAdjust(usMaxStep, usMinStep, ucTimer);
    ScalerColorLDStepInitilalPWMAdjust(usInitialPWM);
}

//--------------------------------------------------
// Description  : Local Histogram set threshold
// Input Value  : CoverRate
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoSetCoverRate(WORD usCoverRate)
{
    // Get V height
    WORD usVHeight = _PANEL_DV_HEIGHT;

    // Get H width
    WORD usHWidth = _PANEL_DH_WIDTH;

#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
    BYTE ucVnum = tLocalDimmingPanelRegionsUp[0];

    // Get H Area Num
    BYTE ucHnum = tLocalDimmingPanelRegionsUp[1];

#else
    // Get V Area Num
    BYTE ucVnum = tLocalDimmingPanelRegions[0];
    // Get H Area Num
    BYTE ucHnum = tLocalDimmingPanelRegions[1];
#endif
    // cal V step
    DWORD ulVStep = (DWORD)usVHeight * 256 / ucVnum;

    // cal H step
    DWORD ulHStep = (DWORD)usHWidth * 256 / ucHnum;

    DWORD ulAreaSize = 0;
    BYTE ucTruncateNum = 0;
    BYTE ucHistoThd = 0;

    // Set V step
    Scaler32SetDWord(PB0050C_0C_LD_HISTO_V_STEP_0, ulVStep);
    // Set H step
    Scaler32SetDWord(PB0050C_08_LD_HISTO_H_STEP_0, ulHStep);

    // Set Truncate bit num
    if((usHWidth % ucHnum) == 0)
    {
        usHWidth = usHWidth / ucHnum;
    }
    else
    {
        usHWidth = usHWidth / ucHnum + 1;
    }

    if((usVHeight % ucVnum) == 0)
    {
        usVHeight = usVHeight / ucVnum;
    }
    else
    {
        usVHeight = usVHeight / ucVnum + 1;
    }

    ulAreaSize = ((DWORD)usVHeight) * usHWidth;

    for(ucTruncateNum = 0; ucTruncateNum <= 14; ucTruncateNum++)
    {
        if((ulAreaSize >> ucTruncateNum) < 256)
        {
            break;
        }
    }

    Scaler32SetByte(PB0050C_14_LD_HISTO_TRUNC_BIT_0, 0, ucTruncateNum);

    // Set THD
    ucHistoThd = (BYTE)((((ulHStep >> 8) * (ulVStep >> 8)) >> ucTruncateNum) * usCoverRate / 1000);
    Scaler32SetByte(PB0050C_10_LD_HISTO_THD_0, 0, ucHistoThd);

#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    ScalerColorLDHistoSetWhiteTHD(ucHistoThd);
    ScalerColorLDHistoSetBlackTHD(ucHistoThd);
#endif

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
    g_ucColorHistoTHdHigh = ucHistoThd;
    g_ucColorHistoTHdLow = (BYTE)((((ulHStep >> 8) * (ulVStep >> 8)) >> ucTruncateNum) * _LOCAL_DIMMING_HISTO_LOW / 1000);
#endif
}


//--------------------------------------------------
// Description  : Local Histogram Initial
// Input Value  : CoverRate
// Output Value : None
//--------------------------------------------------
void ScalerColorLDHistoInitial(WORD usCoverRate)
{
#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
    BYTE ucVnum = tLocalDimmingPanelRegionsUp[0] - 1;

    // Get H Area Num
    BYTE ucHnum = tLocalDimmingPanelRegionsUp[1];
#else
    // Get V Area Num
    BYTE ucVnum = tLocalDimmingPanelRegions[0] - 1;

    // Get H Area Num
    BYTE ucHnum = tLocalDimmingPanelRegions[1];
#endif
    // set V num
    Scaler32SetByte(PB0050C_04_LD_HISTO_AREA_NUM_0, 1, ucVnum);

    // Set H num
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ucHnum = ucHnum / 2 - 1;
    }
    else
#endif
    {
        ucHnum = ucHnum - 1;
    }

    Scaler32SetByte(PB0050C_04_LD_HISTO_AREA_NUM_0, 0, ucHnum);

    // set THD
    ScalerColorLDHistoSetCoverRate(usCoverRate);

    // Set LUT
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    ScalerColorLDHistoLUTAdjust((BYTE *)tLocalDimmingHDRHistoLut, GET_CURRENT_BANK_NUMBER());
    // white and black setting
    ScalerColorLDHistoSetNewBlackMode();
    ScalerColorLDHistoSetBlackValue(_LOCAL_DIMMING_LINEAR_BLACK_COLOR_CODE);
    ScalerColorLDHistoSetWhiteValue(_LOCAL_DIMMING_LINEAR_WHITE_COLOR_CODE);
    ScalerColorLDHistoSetWhiteLUT(tLocalDimmingHDRHistoLut[28]);
    ScalerColorLDHistoSetBlackLUT(tLocalDimmingHDRHistoLut[3]);
#else
    ScalerColorLDHistoLUTAdjust((BYTE *)tLocalDimmingHDRHistoLut256Bin, GET_CURRENT_BANK_NUMBER());
    ScalerColorLDHistoDecisionAdjust(tLocalDimmingHDRHistoDecisionTHD, GET_CURRENT_BANK_NUMBER());
#endif

    // Set Region Initial
    ScalerColorLDInitial();
}

//-----------------------------------------------------
// Description  : Local Dimming Backlight Model Initial
// Input Value  : None
// Output Value : None
//-----------------------------------------------------
void ScalerColorLDBLModelInitial(void)
{
    Scaler32SetBit(PB00550_54_LD_BACKLIGHT_MODEL_DUMMY, ~(_BIT5 | _BIT4), _BIT5 | _BIT4); // unique gain

    if(_LOCAL_DIMMING_HOR_INTERVAL == 32) // 32 step
    {
        // Set Local Dimming Mode
        Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~(_BIT6 | _BIT5 | _BIT4), _BIT6 | _BIT4);

        // Set Local Dimming H Step
        Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~(_BIT3 | _BIT2), _BIT3);

        // Set Local Dimming V Step
        Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Set Local Dimming Mode
        Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

        // Set Local Dimming H Step
        Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~(_BIT3 | _BIT2), 0x00);

        // Set Local Dimming V Step
        Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~(_BIT1 | _BIT0), 0x00);
    }

    ScalerColorLDBLModelSetExtend(2, 2);

    // Set Led Backlight Type
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
    // Eage Backlight Setting
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT7 | _BIT1), _BIT1);
#if(_LOCAL_DIMMING_PANEL_REGION_VERTICAL > 1)
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT4), _BIT4);
#else
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT4), 0x00);
#endif

#if(_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL > 16)
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT3 | _BIT0), _BIT3 | _BIT0);
    ScalerColorLDBLModelSetEdgePWMOffset(((_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL % 16) == 0) ? (0) : (16 - (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL % 16)));
#elif(_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL > 8)
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT3 | _BIT0), _BIT3);
    ScalerColorLDBLModelSetEdgePWMOffset(((_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL % 8) == 0) ? (0) : (8 - (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL % 8)));
#else
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT3 | _BIT0), 0x00);
#endif

#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _OFF)
    ScalerColorLDBLModelSCurveThAdjust(tLocalDimmingLedSettingLut, GET_CURRENT_BANK_NUMBER());
#else
    ScalerColorLDBLModelSCurveThAdjust(g_stColorLocalDimmingMultiTable.pucLedSettingTableAddress, g_stColorLocalDimmingMultiTable.ucTableBank);
#endif

#else
    // Direct Backlight Setting
    Scaler32SetBit(PB00550_04_LD_BACKLIGHT_EDGE_CTRL, ~(_BIT7 | _BIT1), _BIT7 | _BIT1);
    Scaler32SetByte(PB00550_1C_LD_BACKLIGHT_DB_NUM, 1, tLocalDimmingPanelRegions[0]);
    Scaler32SetByte(PB00550_1C_LD_BACKLIGHT_DB_NUM, 0, tLocalDimmingPanelRegions[1]);
#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _OFF)
    ScalerColorLDBLModelDirectLEDSetting(tLocalDimmingLedSettingLut, GET_CURRENT_BANK_NUMBER());
#else
    ScalerColorLDBLModelDirectLEDSetting(g_stColorLocalDimmingMultiTable.pucLedSettingTableAddress, g_stColorLocalDimmingMultiTable.ucTableBank);
#endif

#endif
    // Set Manual Model Start From Step Change
    Scaler32SetBit(PB00550_08_LD_BACKLIGHT_READ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT4);

    // Set V Active Pixel
    Scaler32SetWord(PB00550_10_LD_LV_LUT_PANEL_PIXEL, 1, (WORD)(_LOCAL_DIMMING_VER_GRIDS - 1) * _LOCAL_DIMMING_VER_INTERVAL);
    // Set H Active Pixel
    Scaler32SetWord(PB00550_10_LD_LV_LUT_PANEL_PIXEL, 0, (WORD)(_LOCAL_DIMMING_HOR_GRIDS - 1) * _LOCAL_DIMMING_HOR_INTERVAL);

    // Set V Grids
    Scaler32SetByte(PB00550_14_LD_LV_LUT_GRIDS, 1, _LOCAL_DIMMING_VER_GRIDS);
    // Set H Grids
    Scaler32SetByte(PB00550_14_LD_LV_LUT_GRIDS, 0, _LOCAL_DIMMING_HOR_GRIDS);

    // Set V Offset
    Scaler32SetByte(PB00550_18_LD_LV_LUT_OFFSET, 1, _LOCAL_DIMMING_VER_OFFSET);
    // Set H Offset
    Scaler32SetByte(PB00550_18_LD_LV_LUT_OFFSET, 0, _LOCAL_DIMMING_HOR_OFFSET);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerColorLDBLModelFrontBackEnable(_ENABLE);
    }
    Scaler32SetByte(PB00550_14_LD_LV_LUT_GRIDS, 2, (_LOCAL_DIMMING_HOR_GRIDS - 1) / 2);
    Scaler32SetByte(PB00550_18_LD_LV_LUT_OFFSET, 2, ((_LOCAL_DIMMING_HOR_GRIDS % 2) == 1) ? (0) : (_LOCAL_DIMMING_HOR_INTERVAL / 2));
#endif

    // Set Deep Black Gain
    ScalerColorLDBLModelBlackTHAdjust(_LOCAL_DIMMING_DEEP_BLACK_TH1);
    ScalerColorLDBLModelBlackTHDelta(_LOCAL_DIMMING_DEEP_BLACK_DELTA);
    ScalerColorLDBLModelSetMaxGain((WORD)_LOCAL_DIMMING_BLMODEL_MAX_GAIN * 1024);
    ScalerColorLDBLModelSetMinGain(1024);
    ScalerColorLDBLModelSoftClampAdjust(_LOCAL_DIMMING_SOFTCLAMP_SLOP);
    Scaler32SetBit(PB00550_58_LD_GAIN_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Set Backlight Model Table
    ScalerColorLDBLModelCTSGainAdjust();
#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _OFF)
    ScalerColorLDBLModelLedGainAdjust(tLocalDimmingLvGain, sizeof(tLocalDimmingLvGain), GET_CURRENT_BANK_NUMBER());
    ScalerColorLDBLModelLedLutTableAdjust(tLocalDimmingLvLut, sizeof(tLocalDimmingLvLut), GET_CURRENT_BANK_NUMBER());
    ScalerColorLDBLModelLvTableAdjust(tLocalDimmingLvMax, sizeof(tLocalDimmingLvMax), GET_CURRENT_BANK_NUMBER());
    ScalerColorLDBLModelMaxLvTableAdjust(tLocalDimmingLvMax, sizeof(tLocalDimmingLvMax), GET_CURRENT_BANK_NUMBER());
    ScalerColorLDBLModelPWMGainAdjust(tLocalDimmingPWMGain, GET_CURRENT_BANK_NUMBER());
#else
    ScalerColorLDBLModelLedGainAdjust(g_stColorLocalDimmingMultiTable.pucLVGainTableAddress,
                                      g_stColorLocalDimmingMultiTable.usLVGainTableLength,
                                      g_stColorLocalDimmingMultiTable.ucTableBank);

    ScalerColorLDBLModelLedLutTableAdjust(g_stColorLocalDimmingMultiTable.pucLVLUTTableAddress,
                                          g_stColorLocalDimmingMultiTable.usLVLUTTableLength,
                                          g_stColorLocalDimmingMultiTable.ucTableBank);

    ScalerColorLDBLModelLvTableAdjust(g_stColorLocalDimmingMultiTable.pucLvMaxTableAddress,
                                      g_stColorLocalDimmingMultiTable.usLvMaxTableLength,
                                      g_stColorLocalDimmingMultiTable.ucTableBank);

    ScalerColorLDBLModelMaxLvTableAdjust(g_stColorLocalDimmingMultiTable.pucLvMaxTableAddress,
                                         g_stColorLocalDimmingMultiTable.usLvMaxTableLength,
                                         g_stColorLocalDimmingMultiTable.ucTableBank);

    ScalerColorLDBLModelPWMGainAdjust(g_stColorLocalDimmingMultiTable.pucPWMGainTableAddress,
                                      g_stColorLocalDimmingMultiTable.ucTableBank);
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _OFF)
    ScalerColorLDBLModeS1CurveTableAdjust(tLocalDimmingS1Lut, sizeof(tLocalDimmingS1Lut), GET_CURRENT_BANK_NUMBER());
    ScalerColorLDBLModeS2CurveTableAdjust(tLocalDimmingS2Lut, sizeof(tLocalDimmingS2Lut), GET_CURRENT_BANK_NUMBER());
#else
    ScalerColorLDBLModeS1CurveTableAdjust(g_stColorLocalDimmingMultiTable.pucS1CurveTableAddress,
                                          g_stColorLocalDimmingMultiTable.usS1CurveTableLength,
                                          g_stColorLocalDimmingMultiTable.ucTableBank);
    ScalerColorLDBLModeS2CurveTableAdjust(g_stColorLocalDimmingMultiTable.pucS2CurveTableAddress,
                                          g_stColorLocalDimmingMultiTable.usS2CurveTableLength,
                                          g_stColorLocalDimmingMultiTable.ucTableBank);
#endif
#endif
}

//-----------------------------------------------------
// Description  : Local Dimming Backlight Model Lv Lut Initial
// Input Value  : None
// Output Value : None
//-----------------------------------------------------
void ScalerColorLDBLModelLVLutInitial(void)
{
#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _OFF)
    ScalerColorLDBLModelLvTableAdjust(tLocalDimmingLvMax, sizeof(tLocalDimmingLvMax), GET_CURRENT_BANK_NUMBER());
#else
    ScalerColorLDBLModelLvTableAdjust(g_stColorLocalDimmingMultiTable.pucLvMaxTableAddress, g_stColorLocalDimmingMultiTable.usLvMaxTableLength, g_stColorLocalDimmingMultiTable.ucTableBank);
#endif
}

//-----------------------------------------------------
// Description  : Local Dimming Histo Lut Change
// Input Value  : EnumLocalDimmingType
// Output Value : None
//-----------------------------------------------------
void ScalerColorLDHistoLutChangeType(EnumLocalDimmingType enumLocalDimmingType)
{
    if(enumLocalDimmingType == _LOCAL_DIMMING_SDR)
    {
        g_ucColorLDHistoLutMax = _LOCAL_DIMMING_WHITE_LUT_VALUE_SDR;
        g_ucColorLDHistoLutMin = _LOCAL_DIMMING_BLACK_LUT_VALUE_SDR;
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
        ScalerColorLDHistoLUTAdjust((BYTE *)tLocalDimmingSDRHistoLut, GET_CURRENT_BANK_NUMBER());
#elif(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN2)
        ScalerColorLDHistoLUTAdjust((BYTE *)tLocalDimmingSDRHistoLut256Bin, GET_CURRENT_BANK_NUMBER());
        ScalerColorLDHistoDecisionAdjust(tLocalDimmingSDRHistoDecisionTHD, GET_CURRENT_BANK_NUMBER());
#endif
    }
    else
    {
        g_ucColorLDHistoLutMax = _LOCAL_DIMMING_WHITE_LUT_VALUE_HDR;
        g_ucColorLDHistoLutMin = _LOCAL_DIMMING_BLACK_LUT_VALUE_HDR;
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
        ScalerColorLDHistoLUTAdjust((BYTE *)tLocalDimmingHDRHistoLut, GET_CURRENT_BANK_NUMBER());
#elif(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN2)
        ScalerColorLDHistoLUTAdjust((BYTE *)tLocalDimmingHDRHistoLut256Bin, GET_CURRENT_BANK_NUMBER());
        ScalerColorLDHistoDecisionAdjust(tLocalDimmingHDRHistoDecisionTHD, GET_CURRENT_BANK_NUMBER());
#endif
    }
}

#if(_HW_LOCAL_DIMMING_GEN_SEL != _HW_LOCAL_DIMMING_GEN1)
//--------------------------------------------------
// Description  : Set Shift Gain Value
// Input Value  : ideal Shift Gain Value
// Output Value :
//--------------------------------------------------
void ScalerColorLDSmoothSetShiftGain(WORD usSmoothParaGain)
{
    Scaler32SetBit(PB00510_4C_LD_PWM_SMOOTH_CTRL, ~(_BIT(31, 26) | _BIT(15, 8)), (HIBYTE(usSmoothParaGain) << 26) | (LOBYTE(usSmoothParaGain) << 8));
}
#endif
#if(_HW_LOCAL_DIMMING_EXTROINFO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : extro info enable
// Input Value  : on/ off
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInforEnable(bit bEnable)
{
    if(bEnable == _ON)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT0), 0x00000001);
    }
    else
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT0), 0x00000000);
    }
}
//--------------------------------------------------
// Description  : select extro info
// Input Value  : extro info type
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfo0Select(EnumExtroInfo enumExtroInfo)
{
    if(enumExtroInfo == _EXTRO_INFO_Y_AVG)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT3 | _BIT2 | _BIT1), 0x00000000);
    }
    else if(enumExtroInfo == _EXTRO_INFO_Y_MAX)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT3 | _BIT2 | _BIT1), 0x00000002);
    }
    else if(enumExtroInfo == _EXTRO_INFO_Y_MIN)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT3 | _BIT2 | _BIT1), 0x00000004);
    }
    else if(enumExtroInfo == _EXTRO_INFO_BIN0PER)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT3 | _BIT2 | _BIT1), 0x00000006);
    }
    else if(enumExtroInfo == _EXTRO_INFO_PERTILE)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT3 | _BIT2 | _BIT1), 0x00000008);
    }
}
//--------------------------------------------------
// Description  : select extro info
// Input Value  : extro info0, extro info1
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfo1Select(EnumExtroInfo enumExtroInfo)
{
    if(enumExtroInfo == _EXTRO_INFO_Y_AVG)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00000000);
    }
    else if(enumExtroInfo == _EXTRO_INFO_Y_MAX)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00000010);
    }
    else if(enumExtroInfo == _EXTRO_INFO_Y_MIN)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00000020);
    }
    else if(enumExtroInfo == _EXTRO_INFO_BIN0PER)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00000030);
    }
    else if(enumExtroInfo == _EXTRO_INFO_PERTILE)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00000040);
    }
}
//--------------------------------------------------
// Description  : select extro info type
// Input Value  : extro info format type
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfo0TypeSelect(EnumLDExtroInfoType enumExtroInfotype)
{
    if(enumExtroInfotype == _LOCAL_DIMMING_EXTRO_INOF_TYPE_BIN_IND)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT8), 0x00000000);
    }
    else
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT8), 0x00000100);
    }
}
//--------------------------------------------------
// Description  : select extro info type
// Input Value  : extro info format type
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfo1TypeSelect(EnumLDExtroInfoType enumExtroInfotype)
{
    if(enumExtroInfotype == _LOCAL_DIMMING_EXTRO_INOF_TYPE_BIN_IND)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT9), 0x00000000);
    }
    else
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT9), 0x00000200);
    }
}
//--------------------------------------------------
// Description  : select extro info type
// Input Value  : extro info format type
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfoUpdateMode(EnumLDExtroInfoUpdMode enumExtroUPDMode)
{
    if(enumExtroUPDMode == _LOCAL_DIMMING_EXTRO_INOF_UPD_LD_SYNC)
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT10), 0x00000000);
    }
    else
    {
        Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT10), 0x00000400);
    }
}
//--------------------------------------------------
// Description  : Get info 0 permission switch
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerColorLDExtroInfo0GetPermissionSwitch(void)
{
    if(Scaler32GetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, _BIT11) == _BIT11)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
//--------------------------------------------------
// Description  : apply info 0 permission switch
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfo0PermissionSwitchApply(void)
{
    Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT11), 0x00000800);
}
//--------------------------------------------------
// Description  : Get info 0 permission switch
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerColorLDExtroInfo1GetPermissionSwitch(void)
{
    if(Scaler32GetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, _BIT12) == _BIT12)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
//--------------------------------------------------
// Description  : apply info 0 permission switch
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfo1PermissionSwitchApply(void)
{
    Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT12), 0x00001000);
}
//--------------------------------------------------
// Description  : apply Group epresentation ind
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfoSetGroupRep(BYTE ucRepresentation)
{
    Scaler32SetBit(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, ~(_BIT15 | _BIT14 | _BIT13), (ucRepresentation << 13));
}
//--------------------------------------------------
// Description  : Region divisor
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfoSetRegionDivisor(WORD usDivisor)
{
    Scaler32SetWord(PB0050C_80_LD_EXTRA_INFO_CONTROL_0, 1, usDivisor);
}
//--------------------------------------------------
// Description  : extro info thd
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDExtroInfoSetPercentileTHD(BYTE ucTHD)
{
    Scaler32SetByte(PB0050C_84_LD_EXTRA_INFO_CONTROL_4, 0, ucTHD);
}
//--------------------------------------------------
// Description  : Read Extro Info 0
// Input Value  : WORD *pusExtroInfoTable, WORD usTableSize
// Output Value : None
//--------------------------------------------------
void ScalerColorLDExtroInfoReadInfo0(WORD *pusExtroInfoTable, WORD usTableSize)
{
    ScalerUtilReadWord(PB00527_00_LD_HISTOGRAM_EXTRAINFO0, usTableSize, _AUTOINC, pusExtroInfoTable);
}
//--------------------------------------------------
// Description  : Read Extro Info 0
// Input Value  : WORD *pusExtroInfoTable, WORD usTableSize
// Output Value : None
//--------------------------------------------------
void ScalerColorLDExtroInfoReadInfo1(WORD *pusExtroInfoTable, WORD usTableSize)
{
    ScalerUtilReadWord(PB0052C_00_LD_HISTOGRAM_EXTRAINFO1, usTableSize, _AUTOINC, pusExtroInfoTable);
}
//--------------------------------------------------
// Description  : extro info initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLDExtroInfoInitial(void)
{
    DWORD ulAreaPixel = (_PANEL_DV_HEIGHT * _PANEL_DH_WIDTH) / _LOCAL_DIMMING_TOTAL_REGION;
    WORD usDiviSor = (DWORD)33554432 / ulAreaPixel;
    if(usDiviSor == 0)
    {
        usDiviSor = 1;
    }

    ScalerColorLDExtroInfo0Select(_EXTRO_INFO_Y_MAX);
    ScalerColorLDExtroInfo1Select(_EXTRO_INFO_BIN0PER);
    ScalerColorLDExtroInfo0TypeSelect(_LOCAL_DIMMING_EXTRO_INOF_TYPE_LUT_VALUE);
    ScalerColorLDExtroInfo1TypeSelect(_LOCAL_DIMMING_EXTRO_INOF_TYPE_BIN_IND);
    ScalerColorLDExtroInfoUpdateMode(_LOCAL_DIMMING_EXTRO_INOF_UPD_LD_SYNC);
    ScalerColorLDExtroInfoSetGroupRep(4);
    ScalerColorLDExtroInfoSetRegionDivisor(usDiviSor);
}
#endif
//--------------------------------------------------
// Description  : Set BL Model Mode
// Input Value  : BL Model Mode
// Output Value :
//--------------------------------------------------
void ScalerColorLDBLModelSetMode(EnumLDBLModelMode enumLDBLModelMode)
{
    Scaler32SetBit(PB00550_00_LD_BACKLIGHT_MODEL_CTRL, ~(_BIT5 | _BIT4), enumLDBLModelMode << 4);
}
#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerColorLDPWMProcChangeHVRegionType(EnumPWMProcRegionType enumPWMProcRegionType)
{
    if(enumPWMProcRegionType == _LOCAL_DIMMING_REGION_TYPE_NORMAL)
    {
        Scaler32SetDWord(PB00510_04_LD_PWM_PROCESS_BACKLIGHT_TYPE,
                         (((DWORD)tLocalDimmingPanelRegions[1] - 1) << 16) |
                         ((tLocalDimmingPanelRegions[0] - 1) << 8) |
                         _LOCAL_DIMMING_BACKLIGHT_TYPE);
    }
    else
    {
        Scaler32SetDWord(PB00510_04_LD_PWM_PROCESS_BACKLIGHT_TYPE,
                         (((DWORD)tLocalDimmingPanelRegionsUp[1] - 1) << 16) |
                         ((tLocalDimmingPanelRegionsUp[0] - 1) << 8) |
                         _LOCAL_DIMMING_BACKLIGHT_TYPE);
    }
}
#endif
#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)

