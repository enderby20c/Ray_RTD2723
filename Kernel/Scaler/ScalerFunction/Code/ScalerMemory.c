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
// ID Code      : ScalerMemory.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MEMORY__

#include "ScalerFunctionInclude.h"
#include "Memory/ScalerMemory.h"

#if(_M_DOMAIN_LSR_LINE_BUFFER_DT_FORCE_10_TO_8_BIT == _ON)
#if(_BW_CUSTOME_MODE == _ENABLE)
#warning "Note: The Timing enumMemoryBitSelect = _MEMORY_FORCE_10_BIT May Reduce to 8bit, Please Check by BW Tool!!!"
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
StructMemoryDtFineTune code tMemoryDtScalingDownFineTune[] =
{
    // IVh, DVh,  Dt_Minus, Dt_finetune
    {1600, 1440, _TRUE, 100}, // IVh=1600, DVh=1440, Dt-1

    {4320, 4320, _TRUE, 100}, // IVh=4320, DVh<4320, Dt-1

#if(_ULTRA_VIVID_FUNCTION == _OFF)
    {4320, 2160, _FALSE, 200}, // IVh=4320, DVh=2160, Dt+2
    {4320, 2880, _FALSE, 200}, // IVh=4320, DVh=2880, Dt+2
    {2880, 1440, _FALSE, 200}, // IVh=2880, DVh=1440, Dt+2
#endif

    {2880, 2160, _TRUE, 100}, // IVh=2880, DVh=2160, Dt-1
    {2160, 1440, _TRUE, 100}, // IVh=2160, DVh=1440, Dt-1

    {1200, 1080, _TRUE, 150}, // IVh=1200, DVh=1080, Dt-1.5
    {1440, 1080, _TRUE, 100}, // IVh=1440, DVh=1080, Dt-1
    {1600, 1080, _TRUE, 200}, // IVh=1600, DVh=1080, Dt-2
    {1392, 1080, _TRUE, 150}, // IVh=1392, DVh=1080, Dt-1.5
    {2160, 1080, _TRUE, 100}, // IVh=2160, DVh=1080, Dt-1
};
#endif

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
StructMemoryDtFineTune code tMemoryDtFixLastlineScalingUpFineTune[] =
{
    // IVh, DVh,  Dt_Minus, Dt_finetune
    { 350, 1080, _TRUE, 200}, // IVh=350, DVh=1080, Dt-2
    { 350, 1440, _TRUE, 200}, // IVh=350, DVh=1440, Dt-2
    { 480, 1080, _TRUE, 200}, // IVh=480, DVh=1080, Dt-2
    { 480, 1440, _TRUE, 200}, // IVh=480, DVh=1440, Dt-2
    { 480, 2160, _TRUE, 200}, // IVh=480, DVh=2160, Dt-2

    { 576, 1080, _TRUE, 100}, // IVh=576, DVh=1080, Dt-1
    { 576, 1440, _TRUE, 100}, // IVh=576, DVh=1440, Dt-1

    {1440, 2160, _TRUE,  60}, // IVh=1440, DVh=2160, Dt-0.6
    {1600, 2160, _TRUE,  50}, // IVh=1600, DVh=2160, Dt-0.5
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

BYTE g_ucMemoryPiece = (_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK);
DWORD g_ulMemoryFrcOdBw;
StructMemoryClientAddress g_stMemoryClientAddress;
StructMemoryClientBW g_stMemoryClientBW;

volatile bit g_bMemoryPowerStatus = _OFF;

#if(_DT_RANGE_TEST_SUPPORT == _ON)
bit g_bMemoryDtUpScan = 0;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set FIFO Clock
// Input Value  : Target FIFO Clock
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq)
{
#if(_HW_FIFO_CLK_SEL_TYPE == _FIFO_CLK_SEL_GEN_0)
    switch(enumFIFOFreq)
    {
        case _SCALER_FIFO_FREQ_M2PLL:
            ScalerSetBit(P33_03_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _SCALER_FIFO_FREQ_MPLL:
            ScalerSetBit(P33_03_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), 0x00);
            break;

        case _SCALER_FIFO_FREQ_DDRPLL:
            ScalerSetBit(P33_03_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), _BIT0);
            break;

        case _SCALER_FIFO_FREQ_DCLK:
            ScalerSetBit(P33_03_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), _BIT1);
            break;

        default:
            break;
    }
#elif(_HW_FIFO_CLK_SEL_TYPE == _FIFO_CLK_SEL_GEN_1)
    switch(enumFIFOFreq)
    {
        case _SCALER_FIFO_FREQ_M2PLL:
            ScalerSetBit(P33_03_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _SCALER_FIFO_FREQ_DDRPLL:
            ScalerSetBit(P33_03_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), 0x00);
            break;

        case _SCALER_FIFO_FREQ_MPLL:
        case _SCALER_FIFO_FREQ_DCLK:
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : M Domain Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryInitial(void)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    //------------------------------
    // DDR Initial
    //------------------------------

#endif

    //------------------------------
    // FRC Initial
    //------------------------------
    ScalerFRCInitial();

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    //------------------------------
    // Rotation Initial
    //------------------------------
    ScalerRotationInitial();
#endif

#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    //------------------------------
    // Drr Initial
    //------------------------------
    ScalerDrrUpdateVsyncSetting();
#endif
}

//--------------------------------------------------
// Description  : Get fifo width
// Input Value  : enumDDomainRegion
// Output Value : Fifo width
//--------------------------------------------------
WORD ScalerMemoryGetFifoWidth(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            pData[0] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_00_DISPLAY_READ_WID_BSU_H_R1_ACTIVE1);
            pData[1] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_01_DISPLAY_READ_WID_BSU_L_R1_ACTIVE1);
            pData[2] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R1_ACTIVE1);
            break;

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R1_A2:
            pData[0] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_04_DISPLAY_READ_WID_BSU_H_R1_ACTIVE2);
            pData[1] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_05_DISPLAY_READ_WID_BSU_L_R1_ACTIVE2);
            pData[2] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R1_ACTIVE2);
            break;
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A1:
            pData[0] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_00_DISPLAY_READ_WID_BSU_H_R2_ACTIVE1);
            pData[1] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_01_DISPLAY_READ_WID_BSU_L_R2_ACTIVE1);
            pData[2] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R2_ACTIVE1);
            break;
#endif
#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A2:
            pData[0] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_04_DISPLAY_READ_WID_BSU_H_R2_ACTIVE2);
            pData[1] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_05_DISPLAY_READ_WID_BSU_L_R2_ACTIVE2);
            pData[2] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R2_ACTIVE2);
            break;
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A1:
            pData[0] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_00_DISPLAY_READ_WID_BSU_H_R3_ACTIVE1);
            pData[1] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_01_DISPLAY_READ_WID_BSU_L_R3_ACTIVE1);
            pData[2] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R3_ACTIVE1);
            break;
#endif
#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A2:
            pData[0] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_04_DISPLAY_READ_WID_BSU_H_R3_ACTIVE2);
            pData[1] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_05_DISPLAY_READ_WID_BSU_L_R3_ACTIVE2);
            pData[2] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R3_ACTIVE2);
            break;
#endif
#endif
    }

    //-------------------------------------------------
    // Get FIFO Input Width: _HW_FIFO_GEN_HTOTAL_BIT
    //-------------------------------------------------
    PDATA_WORD(0) = ((((WORD)pData[2] << 8) & (_HW_FIFO_GEN_HTOTAL_BIT & 0xF000)) | (((WORD)pData[0] << 4) & 0xF00) | pData[1]);

    return PDATA_WORD(0);
}

//--------------------------------------------------
// Description  : Get fifo vheight
// Input Value  : enumDDomainRegion
// Output Value : Fifo vheight
//--------------------------------------------------
WORD ScalerMemoryGetFifoVheight(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            pData[0] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_00_DISPLAY_READ_WID_BSU_H_R1_ACTIVE1);
            pData[1] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_02_DISPLAY_READ_LEN_BSU_L_R1_ACTIVE1);
            pData[2] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R1_ACTIVE1);
            break;

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R1_A2:
            pData[0] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_04_DISPLAY_READ_WID_BSU_H_R1_ACTIVE2);
            pData[1] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_06_DISPLAY_READ_LEN_BSU_L_R1_ACTIVE2);
            pData[2] = ScalerGetDataPortSingleByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R1_ACTIVE2);
            break;
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A1:
            pData[0] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_00_DISPLAY_READ_WID_BSU_H_R2_ACTIVE1);
            pData[1] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_02_DISPLAY_READ_LEN_BSU_L_R2_ACTIVE1);
            pData[2] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R2_ACTIVE1);
            break;
#endif
#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A2:
            pData[0] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_04_DISPLAY_READ_WID_BSU_H_R2_ACTIVE2);
            pData[1] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_06_DISPLAY_READ_LEN_BSU_L_R2_ACTIVE2);
            pData[2] = ScalerGetDataPortSingleByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R2_ACTIVE2);
            break;
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A1:
            pData[0] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_00_DISPLAY_READ_WID_BSU_H_R3_ACTIVE1);
            pData[1] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_02_DISPLAY_READ_LEN_BSU_L_R3_ACTIVE1);
            pData[2] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R3_ACTIVE1);
            break;
#endif
#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A2:
            pData[0] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_04_DISPLAY_READ_WID_BSU_H_R3_ACTIVE2);
            pData[1] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_06_DISPLAY_READ_LEN_BSU_L_R3_ACTIVE2);
            pData[2] = ScalerGetDataPortSingleByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R3_ACTIVE2);
            break;
#endif
#endif
    }

    //-------------------------------------------------
    // Get FIFO Input Vheight: _HW_FIFO_GEN_VTOTAL_BIT
    //-------------------------------------------------
    PDATA_WORD(0) = ((((WORD)pData[2] << 12) & (_HW_FIFO_GEN_VTOTAL_BIT & 0xF000)) | (((WORD)pData[0] << 8) & 0x0F00) | pData[1]);

    return PDATA_WORD(0);
}

//--------------------------------------------------
// Description  : Calculate Dt Max/Min Value for Scale Up
// Input Value  : None
// Output Value : Calculated Max/Min Dt in 0.01 Lines
//--------------------------------------------------
DWORD ScalerMemoryGetDtMaxMin(WORD usVheight)
{
    BYTE ucMax = 0;
    BYTE ucMin = 100;
    BYTE ucCount = 0;
    BYTE ucPhase = 0;
    WORD usDtMin = 0;
    WORD usDtMax = 0;
    WORD usSUF = 0;
    WORD usFIFOHWidth = 0;
    WORD usDt = 0;
    DWORD ulVFCI = 0;

    // Get Ver filter coef initial value: VFCI * 128
    GET_VER_FILTER_COEF_INI(ulVFCI);

    DebugMessageFS("7.ulVFCI", ulVFCI);

    // Since MSB would be Eliminated by Mod, Only WORD is Required
    usSUF = (WORD)(((DWORD)usVheight << 13) / GET_MDOMAIN_OUTPUT_VHEIGHT());

    // Get Min and Max Value
    do
    {
        // (VFCI + n * VSF) mod 1
        ucPhase = (BYTE)(((WORD)ulVFCI + (((DWORD)ucCount * usSUF) >> 6)) & 0x7F);

        if(ucPhase > ucMax)
        {
            ucMax = ucPhase;
        }

        if(ucPhase < ucMin)
        {
            ucMin = ucPhase;
        }

        ucCount++;
    }
    while(ucCount < 255);
    DebugMessageFS("Calculated Max", ucMax);
    DebugMessageFS("Calculated Min", ucMin);

    //-------------------------------------------------
    // Get FIFO Input Width: 13 bit
    //-------------------------------------------------
    usFIFOHWidth = ScalerMemoryGetFifoWidth(ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION()));

    // VFCI * 100
    ulVFCI = (ulVFCI * 100) >> 7;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            usFIFOHWidth = usFIFOHWidth - GET_EXT_RECAP_EXTENSION_LEN_A1();

            // DtMin = 1  +(VFCI-min)/2+ VSF/2 - VSF*DHActiveEnd/DHTotal/2
            usDtMin = 100 + (ulVFCI >> 1) - (((WORD)ucMin * 100) >> 8) + (DWORD)GET_MDOMAIN_INPUT_VHEIGHT()  * 50 / GET_MDOMAIN_OUTPUT_VHEIGHT() - (DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH() / 2) / GET_MDOMAIN_OUTPUT_VHEIGHT() * 50 / (GET_MDOMAIN_OUTPUT_HWIDTH() / 2);
            usDtMin = usDtMin << 1;

            // DtMax = 1 + FIFODepth/FIFOHWidth each(max-VFCI)/2 each VSF*(DHActiveStart/DHTotal)
            usDtMax = 100 + (DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 100 / usFIFOHWidth + (ulVFCI >> 1) - ((WORD)ucMax * 100 >> 8) - (DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * GET_MDOMAIN_OUTPUT_HSTART() / GET_MDOMAIN_OUTPUT_VHEIGHT() * 50 / (GET_MDOMAIN_OUTPUT_HTOTAL() / 2);
            usDtMax = usDtMax << 1;
        }
        else
#endif
        {
            // DtMin = 1  +(VFCI-min)/2+ VSF/2 - VSF*DHActiveEnd/DHTotal/2
            usDtMin = 100 + (ulVFCI >> 1) - (((WORD)ucMin * 100) >> 8) + (DWORD)GET_MDOMAIN_INPUT_VHEIGHT()  * 50 / GET_MDOMAIN_OUTPUT_VHEIGHT() - (DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()) / GET_MDOMAIN_OUTPUT_VHEIGHT() * 50 / GET_MDOMAIN_OUTPUT_HWIDTH();
            usDtMin = usDtMin << 1;

            // DtMax = 1 + FIFODepth/FIFOHWidth each(max-VFCI)/2 each VSF*(DHActiveStart/DHTotal)
            usDtMax = 100 + (DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 100 / usFIFOHWidth + (ulVFCI >> 1) - (((WORD)ucMax * 100) >> 8) - (DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * GET_MDOMAIN_OUTPUT_HSTART() / GET_MDOMAIN_OUTPUT_VHEIGHT() * 50 / GET_MDOMAIN_OUTPUT_HTOTAL();
            usDtMax = usDtMax << 1;
        }
    }
    else
#endif
    {
        // Dt min = 2 + (VFCI - min - VSF * DHActiveEnd / DHTotal)
        usDtMin = 200 + ulVFCI - (((WORD)ucMin * 100) >> 7) - (DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()) / GET_MDOMAIN_OUTPUT_VHEIGHT() * 100 / GET_MDOMAIN_OUTPUT_HTOTAL();

        // Dt max = 2 + FIFODepth / FIFOWIDTH - max + VFCI - VSF * DHActiveSt / DHTotal
        usDtMax = 200 + (DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 100 / usFIFOHWidth - (((WORD)ucMax * 100) >> 7) + ulVFCI - (DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * GET_MDOMAIN_OUTPUT_HSTART() / GET_MDOMAIN_OUTPUT_VHEIGHT() * 100 / GET_MDOMAIN_OUTPUT_HTOTAL();
    }

    DebugMessageFS("2. DtMax", usDtMax);
    DebugMessageFS("2. DtMin", usDtMin);

    if(GET_D_DOMAIN_REQUEST() == _7_LINES_BEFORE_DEN)
    {
        usDt = ((DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 90 / usFIFOHWidth + (DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * 700 / GET_MDOMAIN_OUTPUT_VHEIGHT());

        if(usDtMax > usDt)
        {
            usDtMax = usDt;
            DebugMessageFS("7. dt max modifyed", usDtMax);
        }
    }

    return (((DWORD)usDtMax << 16) | usDtMin);
}

//--------------------------------------------------
// Description  : Get Scaling Down Dt Fine Tune
// Input Value  : Current Dt
// Output Value : Fine tune Dt
//--------------------------------------------------
WORD ScalerMemoryGetScalingDownDtFineTune(WORD usDt)
{
    WORD usDtTemp = usDt;

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    for(BYTE ucIndex = 0; ucIndex < (sizeof(tMemoryDtScalingDownFineTune) / sizeof(tMemoryDtScalingDownFineTune[0])); ucIndex++)
    {
        if(GET_INPUT_TIMING_VHEIGHT() == tMemoryDtScalingDownFineTune[ucIndex].usInputVheight)
        {
            switch(GET_INPUT_TIMING_VHEIGHT())
            {
#if(_ULTRA_VIVID_FUNCTION == _ON)
                case 4320:
                    if(_PANEL_DV_HEIGHT < tMemoryDtScalingDownFineTune[ucIndex].usPanelVheight)
                    {
                        if(tMemoryDtScalingDownFineTune[ucIndex].bMinusDt == _TRUE)
                        {
                            if(usDtTemp > tMemoryDtScalingDownFineTune[ucIndex].usDtFineTune)
                            {
                                usDtTemp -= tMemoryDtScalingDownFineTune[ucIndex].usDtFineTune;
                            }
                            else
                            {
                                DebugMessageScaler("Warning !!!! Dt Fine Tune would by Minus", 0);
                            }
                        }
                        else
                        {
                            usDtTemp += tMemoryDtScalingDownFineTune[ucIndex].usDtFineTune;
                        }
                    }
                    break;
#endif

                default:
                    if(_PANEL_DV_HEIGHT == tMemoryDtScalingDownFineTune[ucIndex].usPanelVheight)
                    {
                        if(tMemoryDtScalingDownFineTune[ucIndex].bMinusDt == _TRUE)
                        {
                            if(usDtTemp > tMemoryDtScalingDownFineTune[ucIndex].usDtFineTune)
                            {
                                usDtTemp -= tMemoryDtScalingDownFineTune[ucIndex].usDtFineTune;
                            }
                            else
                            {
                                DebugMessageScaler("Warning !!!! Dt Fine Tune would by Minus", 0);
                            }
                        }
                        else
                        {
                            usDtTemp += tMemoryDtScalingDownFineTune[ucIndex].usDtFineTune;
                        }
                    }
                    break;
            }
        }
    }
#endif

    return usDtTemp;
}

//--------------------------------------------------
// Description  : Get Scaling Down Dt Fine Tune
// Input Value  : Current Dt
// Output Value : Fine tune Dt
//--------------------------------------------------
WORD ScalerMemoryGetScalingUpDtFineTune(WORD usDt)
{
    WORD usDtTemp = usDt;

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
    if(ScalerMemoryGetFramesyncFixLastlinesStatus() == _TRUE)
    {
        for(BYTE ucIndex = 0; ucIndex < (sizeof(tMemoryDtFixLastlineScalingUpFineTune) / sizeof(tMemoryDtFixLastlineScalingUpFineTune[0])); ucIndex++)
        {
            if(_PANEL_DV_HEIGHT == tMemoryDtFixLastlineScalingUpFineTune[ucIndex].usPanelVheight)
            {
                if(GET_INPUT_TIMING_VHEIGHT() == tMemoryDtFixLastlineScalingUpFineTune[ucIndex].usInputVheight)
                {
                    if(tMemoryDtFixLastlineScalingUpFineTune[ucIndex].bMinusDt == _TRUE)
                    {
                        if(usDtTemp > tMemoryDtFixLastlineScalingUpFineTune[ucIndex].usDtFineTune)
                        {
                            usDtTemp -= tMemoryDtFixLastlineScalingUpFineTune[ucIndex].usDtFineTune;
                        }
                        else
                        {
                            DebugMessageScaler("Warning !!!! Dt Fine Tune would by Minus", 0);
                        }
                    }
                    else
                    {
                        usDtTemp += tMemoryDtFixLastlineScalingUpFineTune[ucIndex].usDtFineTune;
                    }
                }
            }
        }
    }
#endif

    return usDtTemp;
}

//--------------------------------------------------
// Description  : Calculate Dt Value for Scale Up
// Input Value  : None
// Output Value : Calculated Dt in 0.01 Lines
//--------------------------------------------------
WORD ScalerMemoryGetScaleUpDt(WORD usVheight)
{
    WORD usDtMin = 0;
    WORD usDtMax = 0;
    WORD usDt = 0;
    DWORD ulDtMaxMin = ScalerMemoryGetDtMaxMin(usVheight);

    usDtMin = LOWORD(ulDtMaxMin);
    usDtMax = HIWORD(ulDtMaxMin);

    usDt = (usDtMax + usDtMin) / 2;
    DebugMessageFS("2. Target Dt Value", usDt);

// VSD Dt compensation
#if(_ULTRA_VIVID_FUNCTION == _ON)
    if((GET_V_SCALE_DOWN() == _TRUE) && (ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT7) == _BIT7))
    {
        if(GET_MDOMAIN_INPUT_VHEIGHT() > GET_MDOMAIN_OUTPUT_VHEIGHT())
        {
            usDt = GET_DWORD_MUL_DIV(usDt, GET_MDOMAIN_INPUT_VHEIGHT(), GET_MDOMAIN_OUTPUT_VHEIGHT());
            DebugMessageFS("2. VSD Target Dt Value new", usDt);

            usDt = ScalerMemoryGetScalingDownDtFineTune(usDt);
        }
    }
#endif

    // Dt compensation for front back panel(4path)
    if(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) == _INPUT_PATH_4)
    {
        usDt += 200;
    }

    if(GET_MDOMAIN_INPUT_VHEIGHT() < GET_MDOMAIN_OUTPUT_VHEIGHT())
    {
        usDt = ScalerMemoryGetScalingUpDtFineTune(usDt);
    }

    // Calculat (I porch - 2)
    PDATA_WORD(0) = (GET_MDOMAIN_INPUT_VTOTAL() > (GET_MDOMAIN_INPUT_VHEIGHT() + 2)) ? (GET_MDOMAIN_INPUT_VTOTAL() - (GET_MDOMAIN_INPUT_VHEIGHT() + 2)) : 0;

    // Dt must small than (I portch - 2)
    if(usDt >= (PDATA_WORD(0) * 100))
    {
        usDt = ((PDATA_WORD(0) * 100) + usDtMin) / 2;
        DebugMessageFS("2. Target Dt Value new", usDt);
    }

    return usDt;
}

//--------------------------------------------------
// Description  : Set FIFO Capture
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFifoCapture(EnumInputDataPath enumInputDataPath, WORD usHWidth, WORD usVHeight)
{
    DWORD ulFrametotal128bits = 0;
    DWORD ulTemp = 0;
    BYTE ucLen = 0;
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;

    ScalerMemorySetFifoWindow(GET_MODE_DISPLAY_TARGET_REGION(), usHWidth, usVHeight);

    switch(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()))
    {
        case _INPUT_PATH_2:
            usVHeight = (usVHeight >> 1);
            break;

        case _INPUT_PATH_4:
            usHWidth = (usHWidth >> 1);
            usVHeight = (usVHeight >> 1);
            break;

        default:
            break;
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            ScalerMemorySetCapInputFormat(enumPageSelect);
        }
    }

    // Calculate total 128bits per frame, imc off for line buffer
    ulFrametotal128bits = ScalerFRCGetLineSumBit(usHWidth, GET_MEMORY_DATA_BIT(), _IMG_CMP_PARAM_OFF);
    ucLen = ScalerFRCGetAccessLength(_FRC_WRITE_LENGTH);
    ulTemp = ScalerMemoryCalculateNumberAndRemain(CEILING_OF_INT_DIVISION(ulFrametotal128bits, _FRC_UNIT), ucLen, 1);
    ulFrametotal128bits = CEILING_OF_INT_DIVISION(ulFrametotal128bits, _FRC_TOTAL_128BIT) * usVHeight;

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ucIndex++)
    {
        if(CHK_FRC_PATH(ScalerFRCGetMDispPath(enumInputDataPath), GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
            {
                // Set Pre-Read line
                SET_PAGED_BYTE(enumPageSelect, _REG_FRC_DISP_PRRD_VST_TOP_H, HIBYTE(_PRE_READ_LINE_BUFFER));
                SET_PAGED_BYTE(enumPageSelect, _REG_FRC_DISP_PRRD_VST_TOP_L, LOBYTE(_PRE_READ_LINE_BUFFER));

                // display pixel number
                SET_PAGED_BYTE(enumPageSelect, P5_A2_DISP_M1_PXL_NUM_TOP_H, HIBYTE(usHWidth));
                SET_PAGED_BYTE(enumPageSelect, P5_A3_DISP_M1_PXL_NUM_TOP_L, LOBYTE(usHWidth));

                // Set Display Line Number
                SET_PAGED_BYTE(enumPageSelect, P5_21_CAP_M1_LINE_NUM_H, HIBYTE(usVHeight));
                SET_PAGED_BYTE(enumPageSelect, P5_22_CAP_M1_LINE_NUM_L, LOBYTE(usVHeight));
                SET_PAGED_BYTE(enumPageSelect, P5_A4_DISP_M1_LINE_NUM_TOP_H, HIBYTE(usVHeight));
                SET_PAGED_BYTE(enumPageSelect, P5_A5_DISP_M1_LINE_NUM_TOP_L, LOBYTE(usVHeight));

                // Set total 128 bit
                SET_PAGED_BIT(enumPageSelect, P5_D1_DISP_M1_TOTAL_128_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulFrametotal128bits >> 24) & 0x0F));
                SET_PAGED_BYTE(enumPageSelect, P5_D2_DISP_M1_TOTAL_128_TOP_H, ((ulFrametotal128bits >> 16) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_D3_DISP_M1_TOTAL_128_TOP_M, ((ulFrametotal128bits >> 8) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_D4_DISP_M1_TOTAL_128_TOP_L, (ulFrametotal128bits & 0xFF));

                // Set Number, Length, Remain
                ScalerFRCSetCapNumLengthRemain(enumPageSelect, ulTemp, ucLen);
                ScalerFRCSetDispTopNumLengthRemain(enumPageSelect, ulTemp, ucLen);
            }

            ScalerMemorySetDispInputFormat(enumPageSelect);
            FRC_DISP_LOCAL_DB_APPLY(enumPageSelect);
        }
    }
}

//--------------------------------------------------
// Description  : Set FIFO Window
// Input Value  : Input Data Path,Hwidth,VHeight
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFifoWindow(EnumDisplayRegion enumDisplayRegion, WORD usHWidth, WORD usVHeight)
{
    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(enumDisplayRegion);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    WORD usLRLeftWidth = 0;
    WORD usLRRightWidth = 0;
#endif

    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerScalingGetFBFrameStatus((EnumSelRegion)enumDisplayRegion) == _TRUE)
            {
                switch(enumDisplayRegion)
                {
                    case _DISPLAY_RGN_1P:
                    case _DISPLAY_RGN_PIP_MAIN:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
#endif
                    case _DISPLAY_RGN_TOP:
                    case _DISPLAY_RGN_SKEW_T_MAIN:
                    default:
                        usHWidth = (usHWidth >> 1) + GET_EXT_RECAP_EXTENSION_LEN_A1();
                        SET_FIFO_WINDOW_R1_A1(usHWidth, usVHeight);
                        SET_FIFO_WINDOW_R3_A1(usHWidth, usVHeight);
                        break;

                    case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
                        if(ScalerScalingGetPBPLRSingleRegionStatus(GET_MDOMAIN_OUTPUT_HSTART(), GET_MDOMAIN_OUTPUT_HWIDTH()) == _TRUE)
                        {
                            SET_FIFO_WINDOW_R1_A1(usHWidth, usVHeight);
                            SET_FIFO_WINDOW_R3_A1(0, usVHeight);
                        }
                        else
                        {
                            usLRLeftWidth = (usHWidth >> 1) + GET_EXT_RECAP_MOVING_LEN() + GET_EXT_RECAP_EXTENSION_LEN_A1();
                            usLRRightWidth = (usHWidth >> 1) - GET_EXT_RECAP_MOVING_LEN() + GET_EXT_RECAP_EXTENSION_LEN_A1();
                            SET_FIFO_WINDOW_R1_A1(usLRLeftWidth, usVHeight);
                            SET_FIFO_WINDOW_R3_A1(usLRRightWidth, usVHeight);
                        }
                        break;

                    case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
                        if(ScalerScalingGetPBPLRSingleRegionStatus(GET_MDOMAIN_OUTPUT_HSTART(), GET_MDOMAIN_OUTPUT_HWIDTH()) == _TRUE)
                        {
                            SET_FIFO_WINDOW_R1_A1(0, usVHeight);
                            SET_FIFO_WINDOW_R3_A1(usHWidth, usVHeight);
                        }
                        else
                        {
                            usLRLeftWidth = (usHWidth >> 1) - GET_EXT_RECAP_MOVING_LEN() + GET_EXT_RECAP_EXTENSION_LEN_A1();
                            usLRRightWidth = (usHWidth >> 1) + GET_EXT_RECAP_MOVING_LEN() + GET_EXT_RECAP_EXTENSION_LEN_A1();
                            SET_FIFO_WINDOW_R1_A1(usLRLeftWidth, usVHeight);
                            SET_FIFO_WINDOW_R3_A1(usLRRightWidth, usVHeight);
                        }
                        break;
                }
            }
            else
#endif
            {
                SET_FIFO_WINDOW_R1_A1(usHWidth, usVHeight);
            }
            break;

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R1_A2:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerScalingGetFBFrameStatus((EnumSelRegion)enumDisplayRegion) == _TRUE)
            {
                switch(enumDisplayRegion)
                {
                    case _DISPLAY_RGN_BOTTOM:
                    case _DISPLAY_RGN_SKEW_B_MAIN:
                        usHWidth = (usHWidth >> 1) + GET_EXT_RECAP_EXTENSION_LEN_A2();
                        SET_FIFO_WINDOW_R1_A2(usHWidth, usVHeight);
                        SET_FIFO_WINDOW_R3_A2(usHWidth, usVHeight);
                        break;

                    default:
                        break;
                }
            }
            else
#endif
            {
                SET_FIFO_WINDOW_R1_A2(usHWidth, usVHeight);
            }
            break;
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A1:
            SET_FIFO_WINDOW_R2_A1(usHWidth, usVHeight);
            break;
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A2:
            SET_FIFO_WINDOW_R2_A2(usHWidth, usVHeight);
            break;
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A1:
            SET_FIFO_WINDOW_R3_A1(usHWidth, usVHeight);
            break;
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A2:
            SET_FIFO_WINDOW_R3_A2(usHWidth, usVHeight);
            break;
#endif
    }
}
//--------------------------------------------------
// Description  : Set Mdomain Input Format
// Input Value  : FRC Page
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetCapInputFormat(EnumFRCPageSelect enumPageSelect)
{
    switch(GET_MEMORY_DATA_BIT())
    {
#if(_M_DOMAIN_12BIT_SUPPORT == _ON)
        case (_COLOR_DEPTH_12_BITS * 3):
            // Set Input Format 36 Bit
            SET_PAGED_BIT(enumPageSelect, P5_4F_CAP_M1_MISC_0, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2));
            break;
#endif

        case (_COLOR_DEPTH_10_BITS * 3):
            // Set Input Format 30 Bit
            SET_PAGED_BIT(enumPageSelect, P5_4F_CAP_M1_MISC_0, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        default:
            SET_PAGED_BIT(enumPageSelect, P5_4F_CAP_M1_MISC_0, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1));
            // Set Input Format 24 Bit
            break;
    }
}

//--------------------------------------------------
// Description  : Set Mdomain Input Format
// Input Value  : FRC Page
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetDispInputFormat(EnumFRCPageSelect enumPageSelect)
{
    switch(GET_MEMORY_DATA_BIT())
    {
#if(_M_DOMAIN_12BIT_SUPPORT == _ON)
        case (_COLOR_DEPTH_12_BITS * 3):
            // Set Input Format 36 Bit
#if(_FRC_SUPPORT == _ON)
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(ScalerFRCGetBottomSettingStatusFromPage(GET_MDOMAIN_INPUT_DATA_PATH(), enumPageSelect) == _TRUE)
            {
                SET_PAGED_BIT(enumPageSelect, P5_FA_DISP_M1_DISP_CTRL3_BOT, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7));
            }
            else
#endif
#endif
            {
                SET_PAGED_BIT(enumPageSelect, P5_AF_DISP_M1_DISP_CTRL3_TOP, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7));
            }

            break;
#endif

        case (_COLOR_DEPTH_10_BITS * 3):
            // Set Input Format 30 Bit
#if(_FRC_SUPPORT == _ON)
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(ScalerFRCGetBottomSettingStatusFromPage(GET_MDOMAIN_INPUT_DATA_PATH(), enumPageSelect) == _TRUE)
            {
                SET_PAGED_BIT(enumPageSelect, P5_FA_DISP_M1_DISP_CTRL3_BOT, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
            }
            else
#endif
#endif
            {
                SET_PAGED_BIT(enumPageSelect, P5_AF_DISP_M1_DISP_CTRL3_TOP, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
            }

            break;

        default:
            // Set Input Format 24 Bit
#if(_FRC_SUPPORT == _ON)
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(ScalerFRCGetBottomSettingStatusFromPage(GET_MDOMAIN_INPUT_DATA_PATH(), enumPageSelect) == _TRUE)
            {
                SET_PAGED_BIT(enumPageSelect, P5_FA_DISP_M1_DISP_CTRL3_BOT, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6));
            }
            else
#endif
#endif
            {
                SET_PAGED_BIT(enumPageSelect, P5_AF_DISP_M1_DISP_CTRL3_TOP, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6));
            }

            break;
    }
}

#if(_PANEL_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
//--------------------------------------------------
// Description  : Compensate Last Line Fine Tune
// Input Value  : Target Last Line, Current Last Line
// Output Value : None
//--------------------------------------------------
void ScalerMemoryCompensateDtForLastLine(DWORD ulTargetLastLine, DWORD ulCurrentLastLine)
{
    DWORD ulCompsIVS2DVSpixel = 0;

    // Get Initial Dt Fine Tune Value
    PDATA_DWORD(0) = ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData);

    DebugMessageFS("Original Dt", PDATA_DWORD(0));

    // Compensate Dt = Original Dt + ((Target Last Line - Current Last Line) * DVHeight / DVTotal * IVHeight / DVHeight * IHTotal / DHTotal) / 2
    SDWORD lCompsIVS2DVSpixel = (SDWORD)PDATA_DWORD(0) + ((((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine) * GET_MDOMAIN_INPUT_VHEIGHT() / GET_MDOMAIN_OUTPUT_VTOTAL() * GET_MDOMAIN_INPUT_HTOTAL() / GET_MDOMAIN_OUTPUT_HTOTAL()) >> 1);

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
    if(ScalerMemoryGetFramesyncFixLastlinesStatus() == _TRUE)
    {
        lCompsIVS2DVSpixel -= (GET_MDOMAIN_INPUT_HTOTAL() >> 1);
    }
#endif

    if(lCompsIVS2DVSpixel >= 0)
    {
        ulCompsIVS2DVSpixel = (DWORD)lCompsIVS2DVSpixel;
    }
    else
    {
        DebugMessageFS("Compensated Dt can't be negative !!!!!", lCompsIVS2DVSpixel);
    }

    DebugMessageFS("Last Line Difference", ((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine));
    DebugMessageFS("Dt Compensate Value", (((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine) * GET_MDOMAIN_INPUT_VHEIGHT() / GET_MDOMAIN_OUTPUT_VTOTAL() * GET_MDOMAIN_INPUT_HTOTAL() / GET_MDOMAIN_OUTPUT_HTOTAL()) >> 1);

    DebugMessageFS("Compensated Dt", ulCompsIVS2DVSpixel);

    ScalerMemorySetIVS2DVSDelayPixel(ulCompsIVS2DVSpixel, &g_stMDomainInputData);
}
#endif // End of #if(_LAST_LINE_FINETUNE_ENABLE == _ENABLE)

//--------------------------------------------------
// Description  : Set IVS2DVS Delay (line)
// Input Value  : IVS2DVS delay, input path
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetIVS2DVSLineDelay(WORD usIVS2DVSDelay, EnumInputDataPath enumInputDataPath)
{
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
    {
        usIVS2DVSDelay = (usIVS2DVSDelay >> 1);
    }
#endif

    // IVS2DVS delay setting min=0x01
    if(usIVS2DVSDelay == 0)
    {
        usIVS2DVSDelay = 0x01;
    }

    ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (HIBYTE(usIVS2DVSDelay) & 0x1F));
    ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, LOBYTE(usIVS2DVSDelay));
}

//--------------------------------------------------
// Description  : IVS2DVS Delay Finetune when display setting
// Input Value  : Old IVS2DVS Delay/ New IVS2DVS Delay/ IVS2DVS Change limit
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFineTuneIVS2DVSDelay(WORD usOldIVS2DVSDelay, WORD usNewIVS2DVSDelay, WORD usIVS2DVSChgLimit)
{
    WORD usDVTotalFrameSync = 0;
    WORD usDVTotalFreeRun = 0;
    WORD usRemainIVS2DVSDelay = 0;
    BYTE ucTimeoutCounter = 255;

    if(usIVS2DVSChgLimit == 0)
    {
        usIVS2DVSChgLimit = 1;
    }

    ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, 0x00);
    ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, 0x00);

    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        // Avoid (Current_IVStart + IVHeight) > IVToal + New_IVSDelay in digital capture
        PDATA_WORD(0) = (GET_INPUT_TIMING_VSTART() + ScalerVgipGetCaptureVStartPosition() + GET_MDOMAIN_INPUT_VHEIGHT());
    }
    else
    {
        // Avoid (Current_IVSDelay + IVStart + IVHeight) > IVToal + New_IVSDelay in analog capture
        PDATA_WORD(0) = (ScalerVgipGetCaptureVDelay() + ScalerVgipGetCaptureVStartPosition() + GET_MDOMAIN_INPUT_VHEIGHT());
    }

    if(PDATA_WORD(0) > GET_MDOMAIN_INPUT_VTOTAL())
    {
        ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
        return;
    }

    // IVS2DVS delay from small to large
    if((usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay()) < (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()))
    {
        usRemainIVS2DVSDelay = (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()) - (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay());

        while(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
        {
            usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
            usOldIVS2DVSDelay += usIVS2DVSChgLimit;

            ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
            ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);

            if(ucTimeoutCounter == 0)
            {
                break;
            }

            ucTimeoutCounter--;
        }

        ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
    }
    else if ((usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay()) > (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()))
    {
        // Get Frame Sync DVtotal
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        usDVTotalFrameSync = ScalerMDomainGetDVtotalLastline();

        // IVS2DVS  diff (D_line)
        usRemainIVS2DVSDelay = (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay()) - (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY());
        usRemainIVS2DVSDelay = (DWORD)usRemainIVS2DVSDelay * GET_MDOMAIN_OUTPUT_VBHEIGHT() / GET_MDOMAIN_INPUT_VHEIGHT();

        // Select smaller between measure DVtotal & Calculate DVtotal
        PDATA_WORD(0) = (usDVTotalFrameSync < GET_MDOMAIN_OUTPUT_VTOTAL()) ? usDVTotalFrameSync : GET_MDOMAIN_OUTPUT_VTOTAL();

        // Display front porch
        PDATA_WORD(1) = (PDATA_WORD(0) > (GET_MDOMAIN_OUTPUT_VBHEIGHT() + GET_MDOMAIN_OUTPUT_VSTART())) ? (PDATA_WORD(0) - (GET_MDOMAIN_OUTPUT_VBHEIGHT() + GET_MDOMAIN_OUTPUT_VSTART())) : 0;

        // (IVS2DVS diff >= Display front porch) or (transient DVtotal < DVtotal min)
        if((usRemainIVS2DVSDelay >= PDATA_WORD(1)) || ((PDATA_WORD(0) - usRemainIVS2DVSDelay) <= _PANEL_DV_TOTAL_MIN))
        {
            // IVS2DVS delay from large to small --> small_IVS2DVS + IVtotal - large_IVS2DVS
            usRemainIVS2DVSDelay = (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()) + GET_MDOMAIN_INPUT_VTOTAL() - (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay());

            while((usRemainIVS2DVSDelay > usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) < GET_MDOMAIN_INPUT_VTOTAL()))
            {
                usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
                ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);

                if(ucTimeoutCounter == 0)
                {
                    break;
                }

                ucTimeoutCounter--;
            }

            // Back up Free run DVtotal
            usDVTotalFreeRun = GET_FREE_RUN_DVTOTAL();

            if((usRemainIVS2DVSDelay > usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) >= GET_MDOMAIN_INPUT_VTOTAL()))
            {
                usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                usOldIVS2DVSDelay = usOldIVS2DVSDelay + usIVS2DVSChgLimit - GET_MDOMAIN_INPUT_VTOTAL();

                PDATA_WORD(7) = ((DWORD)GET_MDOMAIN_INPUT_VTOTAL() + usIVS2DVSChgLimit) * usDVTotalFrameSync / GET_MDOMAIN_INPUT_VTOTAL() + 1;

                SET_FREE_RUN_DVTOTAL(PDATA_WORD(7));

                ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);

                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

                // Set to free-run mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                if(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
                {
                    usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                    usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                    ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
                    ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_NO_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
                    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
#endif
                    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                    // Set to frame-sync mode
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);

                    while(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
                    {
                        usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                        usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                        ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
                        ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);

                        if(ucTimeoutCounter == 0)
                        {
                            break;
                        }

                        ucTimeoutCounter--;
                    }

                    ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
                }
                else
                {
                    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                    ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
                    ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_NO_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
                    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
#endif
                    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                    // Set to frame-sync mode
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
                }
            }
            else if((usRemainIVS2DVSDelay <= usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) >= GET_MDOMAIN_INPUT_VTOTAL()))
            {
                PDATA_WORD(7) = ((DWORD)GET_MDOMAIN_INPUT_VTOTAL() * 2 - usOldIVS2DVSDelay + usNewIVS2DVSDelay) * usDVTotalFrameSync / GET_MDOMAIN_INPUT_VTOTAL() + 1;

                SET_FREE_RUN_DVTOTAL(PDATA_WORD(7));

                ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);

                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

                // Set to free-run mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());

                ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
                ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_NO_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
#endif
                ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                // Set to frame-sync mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
            }
            else
            {
                ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
                DebugMessageFS("Error condition", 0);
            }

            SET_FREE_RUN_DVTOTAL(usDVTotalFreeRun);
        }
        else
        {
            ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());
        }
    }

    DebugMessageFS("Timeout counter", ucTimeoutCounter);
}

//--------------------------------------------------
// Description  : Adjust IVS2DVS Delay When Active State
// Input Value  : Old IVS2DVS Delay/ New IVS2DVS Delay/ IVS2DVS Change limit/ StructTimingInfo/ StructDisplayInfo
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFineTuneIVS2DVSDelayWhenActiveState(StructIVS2DVSDelayFineTune *pstFineTune, const StructTimingInfo *pstMdomainInputInfo, const StructDisplayInfo *pstMdomainOutputInfo)
{
    WORD usDVTotalFrameSync = 0;
    WORD usDVTotalFreeRun = 0;
    WORD usRemainIVS2DVSDelay = 0;
    BYTE ucTimeoutCounter = 255;

    if(pstFineTune->usIVS2DVSChgLimit == 0)
    {
        pstFineTune->usIVS2DVSChgLimit = 1;
    }

    ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, 0x00);
    ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, 0x00);

    // IVS2DVS delay from small to large
    if(pstFineTune->usOldIVS2DVSDelay < pstFineTune->usNewIVS2DVSDelay)
    {
        usRemainIVS2DVSDelay = pstFineTune->usNewIVS2DVSDelay - pstFineTune->usOldIVS2DVSDelay;

        while(usRemainIVS2DVSDelay > pstFineTune->usIVS2DVSChgLimit)
        {
            usRemainIVS2DVSDelay -= pstFineTune->usIVS2DVSChgLimit;
            pstFineTune->usOldIVS2DVSDelay += pstFineTune->usIVS2DVSChgLimit;

            ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usOldIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
            ScalerGlobalIDomainDBApply(pstMdomainInputInfo->enumInputDataPath, _DB_APPLY_POLLING);

            if(ucTimeoutCounter == 0)
            {
                break;
            }

            ucTimeoutCounter--;
        }

        ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usNewIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
    }
    else if (pstFineTune->usOldIVS2DVSDelay > pstFineTune->usNewIVS2DVSDelay)
    {
        // Get Frame Sync DVtotal
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        usDVTotalFrameSync = ScalerMDomainGetDVtotalLastline();

        // IVS2DVS  diff (D_line)
        usRemainIVS2DVSDelay = pstFineTune->usOldIVS2DVSDelay - pstFineTune->usNewIVS2DVSDelay;
        usRemainIVS2DVSDelay = (DWORD)usRemainIVS2DVSDelay * pstMdomainOutputInfo->usVBackHeight / pstMdomainInputInfo->usVHeight;

        // Select smaller between measure DVtotal & Calculate DVtotal
        PDATA_WORD(0) = (usDVTotalFrameSync < pstMdomainOutputInfo->usVTotal) ? usDVTotalFrameSync : pstMdomainOutputInfo->usVTotal;

        // Display front porch
        PDATA_WORD(1) = (PDATA_WORD(0) > (pstMdomainOutputInfo->usVBackHeight + pstMdomainOutputInfo->usVStart)) ? (PDATA_WORD(0) - (pstMdomainOutputInfo->usVBackHeight + pstMdomainOutputInfo->usVStart)) : 0;

        // (IVS2DVS diff >= Display front porch) or (transient DVtotal < DVtotal min)
        if((usRemainIVS2DVSDelay >= PDATA_WORD(1)) || ((PDATA_WORD(0) - usRemainIVS2DVSDelay) <= _PANEL_DV_TOTAL_MIN))
        {
            // IVS2DVS delay from large to small --> small_IVS2DVS + IVtotal - large_IVS2DVS
            usRemainIVS2DVSDelay = pstFineTune->usNewIVS2DVSDelay + pstMdomainInputInfo->usVTotal - pstFineTune->usOldIVS2DVSDelay;

            while((usRemainIVS2DVSDelay > pstFineTune->usIVS2DVSChgLimit) && ((pstFineTune->usOldIVS2DVSDelay + pstFineTune->usIVS2DVSChgLimit) < pstMdomainInputInfo->usVTotal))
            {
                usRemainIVS2DVSDelay -= pstFineTune->usIVS2DVSChgLimit;
                pstFineTune->usOldIVS2DVSDelay += pstFineTune->usIVS2DVSChgLimit;

                ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usOldIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
                ScalerGlobalIDomainDBApply(pstMdomainInputInfo->enumInputDataPath, _DB_APPLY_POLLING);

                if(ucTimeoutCounter == 0)
                {
                    break;
                }

                ucTimeoutCounter--;
            }

            // Back up Free run DVtotal
            usDVTotalFreeRun = GET_FREE_RUN_DVTOTAL();

            if((usRemainIVS2DVSDelay > pstFineTune->usIVS2DVSChgLimit) && ((pstFineTune->usOldIVS2DVSDelay + pstFineTune->usIVS2DVSChgLimit) >= pstMdomainInputInfo->usVTotal))
            {
                usRemainIVS2DVSDelay -= pstFineTune->usIVS2DVSChgLimit;
                pstFineTune->usOldIVS2DVSDelay = pstFineTune->usOldIVS2DVSDelay + pstFineTune->usIVS2DVSChgLimit - pstMdomainInputInfo->usVTotal;

                PDATA_WORD(7) = ((DWORD)pstMdomainInputInfo->usVTotal + pstFineTune->usIVS2DVSChgLimit) * usDVTotalFrameSync / pstMdomainInputInfo->usVTotal + 1;

                SET_FREE_RUN_DVTOTAL(PDATA_WORD(7));

                ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);

                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

                // Set to free-run mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                if(usRemainIVS2DVSDelay > pstFineTune->usIVS2DVSChgLimit)
                {
                    usRemainIVS2DVSDelay -= pstFineTune->usIVS2DVSChgLimit;
                    pstFineTune->usOldIVS2DVSDelay += pstFineTune->usIVS2DVSChgLimit;

                    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, pstMdomainInputInfo->enumInputDataPath);
                    ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usOldIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
                    ScalerGlobalIDomainDBApply(pstMdomainInputInfo->enumInputDataPath, _DB_APPLY_NO_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
                    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, pstMdomainInputInfo->enumInputDataPath);
#endif
                    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, pstMdomainInputInfo->enumInputDataPath);

                    // Set to frame-sync mode
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);

                    while(usRemainIVS2DVSDelay > pstFineTune->usIVS2DVSChgLimit)
                    {
                        usRemainIVS2DVSDelay -= pstFineTune->usIVS2DVSChgLimit;
                        pstFineTune->usOldIVS2DVSDelay += pstFineTune->usIVS2DVSChgLimit;

                        ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usOldIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
                        ScalerGlobalIDomainDBApply(pstMdomainInputInfo->enumInputDataPath, _DB_APPLY_POLLING);

                        if(ucTimeoutCounter == 0)
                        {
                            break;
                        }

                        ucTimeoutCounter--;
                    }

                    ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usNewIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
                }
                else
                {
                    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, pstMdomainInputInfo->enumInputDataPath);
                    ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usNewIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
                    ScalerGlobalIDomainDBApply(pstMdomainInputInfo->enumInputDataPath, _DB_APPLY_NO_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
                    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, pstMdomainInputInfo->enumInputDataPath);
#endif
                    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, pstMdomainInputInfo->enumInputDataPath);

                    // Set to frame-sync mode
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
                }
            }
            else if((usRemainIVS2DVSDelay <= pstFineTune->usIVS2DVSChgLimit) && ((pstFineTune->usOldIVS2DVSDelay + pstFineTune->usIVS2DVSChgLimit) >= pstMdomainInputInfo->usVTotal))
            {
                PDATA_WORD(7) = ((DWORD)pstMdomainInputInfo->usVTotal * 2 - pstFineTune->usOldIVS2DVSDelay + pstFineTune->usNewIVS2DVSDelay) * usDVTotalFrameSync / pstMdomainInputInfo->usVTotal + 1;

                SET_FREE_RUN_DVTOTAL(PDATA_WORD(7));

                ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);

                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

                // Set to free-run mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, pstMdomainInputInfo->enumInputDataPath);

                ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usNewIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
                ScalerGlobalIDomainDBApply(pstMdomainInputInfo->enumInputDataPath, _DB_APPLY_NO_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, pstMdomainInputInfo->enumInputDataPath);
#endif
                ScalerTimerWaitForIDomainEvent(_EVENT_IVS, pstMdomainInputInfo->enumInputDataPath);

                // Set to frame-sync mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
            }
            else
            {
                ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usNewIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
                DebugMessageFS("Error condition", 0);
            }

            SET_FREE_RUN_DVTOTAL(usDVTotalFreeRun);
        }
        else
        {
            ScalerMemorySetIVS2DVSLineDelay(pstFineTune->usNewIVS2DVSDelay, pstMdomainInputInfo->enumInputDataPath);
        }
    }

    DebugMessageFS("Timeout counter", ucTimeoutCounter);
}

//--------------------------------------------------
// Description  : Memory Power Control
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerMemoryPowerControl(bit bOnOff)
{
    if(bOnOff == _OFF)
    {
#if((_HW_CPU32_CPU_HAVE_DCACHE == _TRUE) && (_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE))
        CLEAN_D_CACHE();
#endif
        g_bMemoryPowerStatus = bOnOff;
    }
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    // DDR Power Control
    ScalerDDR3PowerControl(bOnOff);
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
    // DDR Power Control
    ScalerDDR2PowerControl(bOnOff);
#endif

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#if(_HW_MPLL_STRUCT_TYPE != _GEN_NONE)
#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
    // MPLL Power Control
    ScalerPLLMPLLPower(bOnOff);
#endif
#endif
#endif

    if(bOnOff == _ON)
    {
        ScalerFRCPowerOnInitial();
        g_bMemoryPowerStatus = bOnOff;
    }
}

//--------------------------------------------------
// Description  : Get Memory Power Control Status
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerMemoryGetPowerControlStatus(void)
{
    return g_bMemoryPowerStatus;
}

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Description  : Memory Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryReset(void)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerSdramControlReset();
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerDDR1ControlReset();
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
    // DDR Reset
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    // DDR Reset
#endif
}
#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get M:N frame tracking status
// Input Value  : None
// Output Value : _TRUE if enabled
//--------------------------------------------------
bit ScalerMemoryGetFrameTrackingEnable(void)
{
    if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, _BIT7) != 0)
    {
        return _ENABLE;
    }

    return _DISABLE;
}

//--------------------------------------------------
// Description  : M:N frame tracking
// Input Value  : bEn: enable / disable
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFrameTrackingEnable(bit bEn)
{
    // Enable/Disable M:N frame tracking function
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, (BYTE)bEn << 7);
}

//--------------------------------------------------
// Description  : Set M:N frame tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFrameTracking(void)
{
    StructMemoryMNTracking stMNTracking = {0};

    WORD usFreerunDVtotal = 0;
    WORD usFreerunLastline = 0;
    WORD usFramesyncDVtotal = 0;
    WORD usFramesyncLastline = 0;

    DWORD ulNFCodeOld = 0;
    DWORD ulNFCodeNew = 0;
    DWORD ulDtotalOld = 0;
    DWORD ulDtotalTarget = 0;
    DWORD ulDtotalMax = 0;
    DWORD ulDtotalMin = 0;
    bit bProportion = _TRUE;

    if(ScalerMemoryGetFrameTrackingEnable() == _ENABLE)
    {
        return;
    }

    // Measure DVtotal in frame sync mode
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

    // Wait IVS for get correct data
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

    ScalerMemoryGetMNRatio(&stMNTracking, GET_MEMORY_DVF_SELECT());

    // Read DVTotal result
    usFramesyncDVtotal = ScalerMDomainGetDVtotalLastline();

    // Set to read last line result
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);

    // Read Last line result
    usFramesyncLastline = ScalerMDomainGetDVtotalLastline();
    usFramesyncLastline = (usFramesyncLastline << GET_D_DOMAIN_PATH());

    // Calulate Display total pixel: DHtotal * DVtotal + last line
    PDATA_DWORD(1) = (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * usFramesyncDVtotal + usFramesyncLastline;

    ulDtotalOld = PDATA_DWORD(1) * stMNTracking.ucMcode;

#if(_PANEL_STYLE == _PANEL_VBO)
    // Get current NF CodeF
    ulNFCodeOld = ScalerDisplayVboTxGetNFCode(_DISPLAY_VBO_CMU_NF_CODE);
#else
    // Get current (N code + 2) * 2^20 + F code
    ulNFCodeOld = ((ScalerGetDWord(P1_C0_DPLL_N_F_CODE_1) & 0xFFFFFFF) + 0x200000);
#endif

    ulDtotalMax = GET_DWORD_MUL_DIV(ulDtotalOld, _PANEL_PIXEL_CLOCK_MAX_KHZ, GET_D_CLK_FREQ());
    ulDtotalMin = GET_DWORD_MUL_DIV(ulDtotalOld, _PANEL_PIXEL_CLOCK_MIN_KHZ, GET_D_CLK_FREQ());

    ulDtotalTarget = ((DWORD)GET_MDOMAIN_OUTPUT_VTOTAL() * GET_MDOMAIN_OUTPUT_HTOTAL() + _PANEL_LAST_LINE_TARGET) * stMNTracking.ucNcode;

    // Free run Dvtotal
    usFreerunDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL();

    // Free run Last line
    usFreerunLastline = _PANEL_LAST_LINE_TARGET;

    if((ulDtotalTarget > ulDtotalMax) || (ulDtotalTarget < ulDtotalMin))
    {
        if(ulDtotalTarget > ulDtotalMax)
        {
            // Free run DVtotal
            if((ulDtotalMax - ulDtotalMin) >= (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * stMNTracking.ucNcode)
            {
                PDATA_WORD(1) = 1;
            }
            else
            {
                if(((ulDtotalTarget - ulDtotalMax) % (GET_MDOMAIN_OUTPUT_HTOTAL() * stMNTracking.ucNcode)) == 0)
                {
                    PDATA_WORD(1) = 0;
                }
                else
                {
                    PDATA_WORD(1) = 1;
                }
            }

            // Decrease Dvtotal
            PDATA_WORD(1) += (ulDtotalTarget - ulDtotalMax) / GET_MDOMAIN_OUTPUT_HTOTAL() / stMNTracking.ucNcode;
            usFreerunDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL() - PDATA_WORD(1);
            if(usFreerunDVtotal < _PANEL_DV_TOTAL_MIN)
            {
                usFreerunDVtotal = _PANEL_DV_TOTAL_MIN;
            }
        }

        if(ulDtotalTarget < ulDtotalMin)
        {
            // Free run DVtotal
            if((ulDtotalMax - ulDtotalMin) >= (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * stMNTracking.ucNcode)
            {
                PDATA_WORD(1) = 1;
            }
            else
            {
                if(((ulDtotalMin - ulDtotalTarget) % (GET_MDOMAIN_OUTPUT_HTOTAL() * stMNTracking.ucNcode)) == 0)
                {
                    PDATA_WORD(1) = 0;
                }
                else
                {
                    PDATA_WORD(1) = 1;
                }
            }

            // Increase Dvtotal
            PDATA_WORD(1) += (ulDtotalMin - ulDtotalTarget) / GET_MDOMAIN_OUTPUT_HTOTAL() / stMNTracking.ucNcode;
            usFreerunDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL() + PDATA_WORD(1);
            if(usFreerunDVtotal > _PANEL_DV_TOTAL_MAX)
            {
                usFreerunDVtotal = _PANEL_DV_TOTAL_MAX;
            }
        }

        // DtotalTarget
        ulDtotalTarget = ((DWORD)usFreerunDVtotal * GET_MDOMAIN_OUTPUT_HTOTAL() + usFreerunLastline) * stMNTracking.ucNcode;
    }

    if((ulDtotalTarget >= ulDtotalMin) && (ulDtotalTarget <= ulDtotalMax))
    {
        // Calculate DCLK_new
        ulNFCodeNew = ScalerPLLGetNewCount(ulDtotalTarget, ulDtotalOld, ulNFCodeOld, bProportion);

        // Set Dclk
        SET_D_CLK_FREQ(ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, GET_D_CLK_FREQ(), bProportion));

#if(_PANEL_STYLE == _PANEL_VBO)
        ScalerPLLSetDPLLRefPLL(GET_D_CLK_FREQ());
#else
#if((_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
        // Apply N.F for last-line
        ScalerPLLSetDPLLNFcode(ulNFCodeNew - 0x200000);
#endif
#endif
    }
    else
    {
        // Panel can not support for equal distribution
        if((ulDtotalOld % GET_MDOMAIN_OUTPUT_HTOTAL()) > ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 90 / 100))
        {
            // Free run DVtotal
            usFreerunDVtotal = ulDtotalOld / GET_MDOMAIN_OUTPUT_HTOTAL() / stMNTracking.ucNcode + 1;

            // Free run Last line
            usFreerunLastline = (ulDtotalOld % GET_MDOMAIN_OUTPUT_HTOTAL()) / stMNTracking.ucNcode;
        }
        else if((ulDtotalOld % GET_MDOMAIN_OUTPUT_HTOTAL()) < ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 10 / 100))
        {
            // Free run DVtotal
            usFreerunDVtotal = (ulDtotalOld - GET_MDOMAIN_OUTPUT_HTOTAL()) / GET_MDOMAIN_OUTPUT_HTOTAL() / stMNTracking.ucNcode + 1;

            // Free run Last line
            usFreerunLastline = ((ulDtotalOld % GET_MDOMAIN_OUTPUT_HTOTAL()) + GET_MDOMAIN_OUTPUT_HTOTAL()) / stMNTracking.ucNcode;
        }
    }
    // Set DVTotal
    SET_FREE_RUN_DVTOTAL(usFreerunDVtotal);

    // Set Frame Sync Watch Dog
    SET_DIS_TIMING_GEN_WD_VTOTAL(usFreerunDVtotal + 64);

    usFreerunLastline = usFreerunLastline - (usFreerunLastline % _PANEL_DHTOTAL_MULTIPLE);

    // Set Last line
    SET_FREE_RUN_LAST_LINE(usFreerunLastline);

    // Set M:N frame tracking function
    // Set ivs skipped, M = register value +1
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_26_M_FOR_MN_FRAME_RATE);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (stMNTracking.ucMcode - 1));
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_27_N_FOR_MN_FRAME_RATE);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (stMNTracking.ucNcode - 1));
}

//--------------------------------------------------
// Description  : Get M:N ratio
// Input Value  : pstMNTracking
// Output Value : None
//--------------------------------------------------
void ScalerMemoryGetMNRatio(StructMemoryMNTracking *pstMNTracking, EnumDVFSelect enumDVFSelect)
{
    pstMNTracking->ucMcode = 0x0F;
    pstMNTracking->ucNcode = 0x0F;

    switch(enumDVFSelect)
    {
        case _1_IVF:

            pstMNTracking->ucMcode = 1;
            pstMNTracking->ucNcode = 1;

            break;

        case _2_IVF:

            pstMNTracking->ucMcode = 1;
            pstMNTracking->ucNcode = 2;

            break;

        case _3_IVF:

            pstMNTracking->ucMcode = 1;
            pstMNTracking->ucNcode = 3;

            break;

        case _2_5_IVF:

            pstMNTracking->ucMcode = 2;
            pstMNTracking->ucNcode = 5;

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Calculate the Line Step and Block Step
// Input Value  : ulLinetotalpixel --> Horizontal size (unit : 64 bits)
//                pstMemoryLineBlockStep->usVerSize --> Vertical size
// Output Value : Line Step and Block Step
//--------------------------------------------------
void ScalerMemoryCalculateLineStepAndBlockStep(DWORD ulLinetotalpixel, StructMemoryLineBlockStep *pstMemoryLineBlockStep)
{
    // linestep need to be even number
    pstMemoryLineBlockStep->ulLineStep = ulLinetotalpixel;
    pstMemoryLineBlockStep->ulLineStep += (((pstMemoryLineBlockStep->ulLineStep & 0x03) != 0x00) ? (4 - (pstMemoryLineBlockStep->ulLineStep & 0x03)) : 0);
    pstMemoryLineBlockStep->ulBlockStep = (DWORD)pstMemoryLineBlockStep->usVerSize * pstMemoryLineBlockStep->ulLineStep;
}

//--------------------------------------------------
// Description  : Get Memory Frame Buffer Count
// Input Value  : usVheight: fifo Vheight
// Output Value : None
//--------------------------------------------------
BYTE ScalerMemoryGetFrameBufferCount(void)
{
    switch(GET_MEMORY_FRAME_BUFFER())
    {
        case _MEMORY_1_FRAME_BUFFER:
        case _MEMORY_1_5_FRAME_BUFFER:
        default:
            return 1;

        case _MEMORY_2_FRAME_BUFFER:
            return 2;

        case _MEMORY_3_FRAME_BUFFER:
            return 3;
    }
}
#endif

//--------------------------------------------------
// Description  : Calculate the number and remain
// Input Value  : ulTotalSize --> Image total size
//                ucLength --> Length of SDRAM access
// Output Value : Number and Remain
//--------------------------------------------------
DWORD ScalerMemoryCalculateNumberAndRemain(DWORD ulTotalSize, WORD usLength, bit bDummy)
{
    if(bDummy == _TRUE)
    {
#if(_MEMORY_NUM_LEN_REM_MULTIPLE == 2)
        // In 6193, System Bridge data bus is 128 bits,
        // but its burst length and address unit is still 64 bits.
        // So NUM, LEN, and REM must be a multiple of 2.
        ulTotalSize += (ulTotalSize % 2);
#else
        // Multiple of 4
        if((ulTotalSize & 0x03) != 0)
        {
            (ulTotalSize += 4 - (ulTotalSize & 0x03));
        }
#endif
    }

    if((ulTotalSize % usLength) != 0)
    {
        PDATA_WORD(0) = ulTotalSize / usLength; // Number
        PDATA_WORD(1) = ulTotalSize % usLength; // Remain
    }
    else
    {
        ulTotalSize = ulTotalSize - usLength;
        PDATA_WORD(0) = ulTotalSize / usLength; // Number
        PDATA_WORD(1) = usLength;               // Remain
    }

    return (((DWORD)PDATA_WORD(1) << 16) | PDATA_WORD(0));
}

//--------------------------------------------------
// Description  : Setup Frame Sync Dt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFrameSyncSetDt(BYTE ucNum, WORD usVheight)
{
    DWORD ulIVStoDVSPixels = 0;
    DWORD ulDtPercent = 0;
    DWORD ulIVstart = 0;
    DWORD ulDVstart = 0;
    WORD usSUPageAddr = ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN());

    // Calculate DVS to DH Active in ICLK
    ulDVstart = ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * GET_MDOMAIN_OUTPUT_VSTART()) + GET_MDOMAIN_OUTPUT_HSTART();
    ulDVstart = ScalerMemoryTransDDomainToIDomainPixel(ulDVstart);

    // Calculate IVS to IH Active in ICLK
    ulIVstart = GET_MDOMAIN_INPUT_VSTART();

    if((GET_V_SCALE_DOWN() == _TRUE) && (ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT7) == _BIT7))
    {
        switch (ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()))
        {
            case _INPUT_PATH_1:
            default:
                ulIVstart += 1;
                break;

            case _INPUT_PATH_2:
            case _INPUT_PATH_4:
                ulIVstart += 2;
                break;
        }
    }

    ulIVstart = ((DWORD)GET_MDOMAIN_INPUT_HTOTAL() * ulIVstart) + GET_MDOMAIN_INPUT_HSTART();

#if(_HW_FORMAT_CONVERSION_EO_MODE == _OFF)
#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    DWORD ulIVstartBackup = ulIVstart;
#endif
#endif

    // IVS2DVS line skip disable
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT3, _BIT3);

#if(_ULTRA_VIVID_FUNCTION == _ON)
    ulDtPercent = (DWORD)ScalerMemoryGetScaleUpDt(usVheight) * ucNum;
    ulIVstart += GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_HTOTAL(), ulDtPercent, 5000);
#else
    // Frame Sync Memory Settings
    if(GET_V_SCALE_UP() == _TRUE)    // Vertical Scaling Up
    {
        ulDtPercent = (DWORD)ScalerMemoryGetScaleUpDt(usVheight) * ucNum;
        ulIVstart += GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_HTOTAL(), ulDtPercent, 5000);
    }
    else
    {
        // unit: pixel
        DWORD ulDt = 0;

        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
        {
            // get FIFI Width
            PDATA_WORD(4) = (GET_MDOMAIN_INPUT_HWIDTH() > GET_MDOMAIN_OUTPUT_HWIDTH()) ? GET_MDOMAIN_OUTPUT_HWIDTH() : GET_MDOMAIN_INPUT_HWIDTH();

            if(GET_V_SCALE_DOWN() == _TRUE)    // Vertical Scaling Down
            {
                ulDt = GET_MDOMAIN_INPUT_HTOTAL() * 2 + ((DWORD)GET_MDOMAIN_INPUT_HTOTAL() * GET_MDOMAIN_INPUT_VHEIGHT() / GET_MDOMAIN_OUTPUT_VHEIGHT() * _M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() / PDATA_WORD(4));

                // VSD Dt Compensation
                ulDt = ScalerMemoryGetScalingDownDtFineTune(GET_DWORD_MUL_DIV(ulDt, 100, GET_MDOMAIN_INPUT_HTOTAL()));
                ulDt = GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_HTOTAL(), ulDt, 100);
            }
            else    // Vertical Scaling Bypass
            {
                ulDt = GET_MDOMAIN_INPUT_HTOTAL() * 2 + ((DWORD)GET_MDOMAIN_INPUT_HTOTAL() * _M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() / PDATA_WORD(4));
            }
        }
        else
        {
            if(GET_V_SCALE_DOWN() == _TRUE)    // Vertical Scaling Down
            {
                ulDt = GET_MDOMAIN_INPUT_HTOTAL() * 2 + ((DWORD)GET_MDOMAIN_INPUT_HTOTAL() * GET_MDOMAIN_INPUT_VHEIGHT() / (GET_MDOMAIN_OUTPUT_VHEIGHT() * 2));
            }
            else    // Vertical Scaling Bypass
            {
                ulDt = GET_MDOMAIN_INPUT_HTOTAL() * 2 + GET_MDOMAIN_INPUT_HTOTAL() / 2;
            }
        }

        // Dt compensation for front back panel(4path)
        if(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) == _INPUT_PATH_4)
        {
            ulDt += ((DWORD)GET_MDOMAIN_INPUT_HTOTAL() * 2);
        }

        ulDtPercent = (DWORD)ulDt * ucNum;
        ulIVstart += (ulDtPercent / 50);
    }
#endif

    // Digital capture
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        DWORD ulIVstartMargin = ulIVstart;

#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)))
        // EO mode, M2_IVS/S2_IVS need to lead DVS when select IVS reset
        if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
           (ScalerMemoryGetMdomainIVSReset(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE))
        {
            if(ulIVstartMargin > GET_MDOMAIN_INPUT_HTOTAL())
            {
                ulIVstartMargin -= GET_MDOMAIN_INPUT_HTOTAL();
            }
            else
            {
                DebugMessageScaler("[Warning!!!] IVst should be larger than 1 line in DP freesync", ulIVstartMargin);

                // Margine 0.5 line is for ScalerMemoryCompensateDtForLastLine
                if(ulIVstartMargin > (GET_MDOMAIN_INPUT_HTOTAL() >> 1))
                {
                    ulIVstartMargin -= (GET_MDOMAIN_INPUT_HTOTAL() >> 1);
                }
            }
        }
        else
#endif
        {
            // Margine 0.5 line is for ScalerMemoryCompensateDtForLastLine
            if(ulIVstartMargin > (GET_MDOMAIN_INPUT_HTOTAL() >> 1))
            {
                ulIVstartMargin -= (GET_MDOMAIN_INPUT_HTOTAL() >> 1);
            }
        }

        // If DVSt > (IVSt + Dt + margine line) means no further IVS2DVSDelay can be added!! --> Decrease DVst
        if(ulDVstart > ulIVstartMargin)
        {
            // (IVst + Dt) in D-line
            PDATA_DWORD(3) = ScalerMemoryTransIDomainToDDomainPixel(ulIVstartMargin) / GET_MDOMAIN_OUTPUT_HTOTAL();

            if(PDATA_DWORD(3) < _DVSYNC_HEIGHT_MIN)
            {
                PDATA_DWORD(3) = _DVSYNC_HEIGHT_MIN;
                DebugMessageFS("warning !!!!  DVst > (IVst + Dt)", 0);
            }

            // Update DVst
            SET_MDOMAIN_OUTPUT_VSTART(PDATA_DWORD(3));
            SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());
            DebugMessageFS("GET_MDOMAIN_OUTPUT_VSTART", GET_MDOMAIN_OUTPUT_VSTART());

            if(GET_MDOMAIN_OUTPUT_VSYNCHEIGHT() > GET_MDOMAIN_OUTPUT_VSTART())
            {
                SET_MDOMAIN_OUTPUT_VSYNCHEIGHT(GET_MDOMAIN_OUTPUT_VSTART());
            }

            // Calculate DVS to DH Active in ICLK
            ulDVstart = ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * GET_MDOMAIN_OUTPUT_VSTART()) + GET_MDOMAIN_OUTPUT_HSTART();
            ulDVstart = ScalerMemoryTransDDomainToIDomainPixel(ulDVstart);
        }
    }
    else
    {
        // If DVSt > (IVSt + Dt) means no further IVS2DVSDelay can be added!! --> Increase IVst
        // Preserve 2 line margin in advance
        PDATA_DWORD(3) = ulDVstart + 2 * GET_MDOMAIN_INPUT_HTOTAL();

        if(PDATA_DWORD(3) > ulIVstart)
        {
            // Calculate insufficient line number
            WORD usInsufficientLines = (PDATA_DWORD(3) - ulIVstart) / GET_MDOMAIN_INPUT_HTOTAL() + 1;

            DebugMessageFS("2. No Further IVS2DVSDelay Can Be Added", 0x00);

            if(ScalerVgipGetCaptureVDelay() > usInsufficientLines)
            {
                ScalerVgipSetCaptureVDelay(ScalerVgipGetCaptureVDelay() - usInsufficientLines);
            }
            else
            {
                usInsufficientLines = ScalerVgipGetCaptureVDelay();

                ScalerVgipSetCaptureVDelay(0);
            }

            // Enlarge IVSt for insufficient lines
            GET_MDOMAIN_INPUT_VSTART() += usInsufficientLines;

            // Set new IVSt under analog capture
            ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART());

            // Modify Original (IVSt + Dt) Value
            ulIVstart += (DWORD)usInsufficientLines * GET_MDOMAIN_INPUT_HTOTAL();
        }
    }

    // IVS2DVS delay
    ulIVStoDVSPixels = (ulIVstart > ulDVstart) ? (ulIVstart - ulDVstart) : 0;

    DebugMessageFS("Target IVS to DVS Delay Value", ulIVStoDVSPixels * 10 / GET_MDOMAIN_INPUT_HTOTAL());

#if(_HW_FORMAT_CONVERSION_EO_MODE == _OFF)
#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    if(ScalerDrrIVSProduceByBE(GET_MDOMAIN_SOURCE_TYPE(), GET_MDOMAIN_INPUT_PORT()) == _TRUE)
    {
        DWORD ulPrereadPosPixel = ulIVStoDVSPixels + (DWORD)g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * _PRE_READ_LINE_BUFFER_ACCESS_DATA;

        if(ulPrereadPosPixel > ulIVstartBackup)
        {
            WORD usPrereadPos = (ulPrereadPosPixel - ulIVstartBackup) / g_stMDomainInputData.usHTotal + 1;
            DWORD ulPrereadFinetune = (usPrereadPos > 1) ? ((usPrereadPos - 2) * g_stMDomainInputData.usHTotal + GET_MDOMAIN_INPUT_HSTART() + GET_MDOMAIN_INPUT_HWIDTH() + ulIVstartBackup) : 0;
            DWORD ulLineData = (DWORD)GET_MEMORY_DATA_BIT() * usPrereadPos * GET_FIFO_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH());

#if(_DT_RANGE_TEST_SUPPORT == _ON)
            if(GET_DT_UPPER_SCAN_FLAG() == _TRUE)
            {
                StructDtCalInfo stDtCalInfo;

                stDtCalInfo.ulDVstart = ulDVstart;
                stDtCalInfo.ulIVStoDVSPixels = ulIVStoDVSPixels;

                ScalerMemoryDtUpperScanForSinglePath(ulLineData, ulIVstart, &stDtCalInfo);

                ulIVStoDVSPixels = stDtCalInfo.ulIVStoDVSPixels;
                ulDVstart = stDtCalInfo.ulDVstart;
            }
            else
#endif
            {
                if(g_stMDomainInputData.usVHeight > g_stMDomainOutputData.usVHeight)
                {
                    ulIVStoDVSPixels = 0;
                }
                else
                {
                    if(ulLineData > _M_DOMAMAIN_FIFO_BIT)
                    {
                        if(ulIVStoDVSPixels > (ulPrereadPosPixel - ulPrereadFinetune))
                        {
                            ulIVStoDVSPixels -= (ulPrereadPosPixel - ulPrereadFinetune);
                        }
                        else
                        {
                            ulIVStoDVSPixels = 0;
                        }
                    }
                }
            }
        }
    }
#endif
#endif

    // DVS Reset, Need to check DVS and Iden can not overlap
    if(ScalerMemoryGetMdomainIVSReset(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE)
    {
        BYTE ucMargin = 1;
        WORD usDVsyncWidthPixel = ((DWORD)GET_MDOMAIN_OUTPUT_VSYNCHEIGHT() * GET_MDOMAIN_OUTPUT_HTOTAL());
        WORD usDVstCom = (ulIVStoDVSPixels + ScalerMemoryTransDDomainToIDomainPixel(usDVsyncWidthPixel)) / GET_MDOMAIN_INPUT_HTOTAL() + 1;

        // Get Current IVS2DVS Delay + DVS Width in Input Lines (Get Ceiling Value) + 1 line for margin
        usDVstCom &= _HW_DIS_TIMING_GEN_V_ACTIVE_BIT;

        // Enlarge DVSt if IVS2DVS Delay + DVS Width is larger than IVSt
        if(usDVstCom >= (GET_MDOMAIN_INPUT_VSTART()))
        {
            DebugMessageFS("2. Target IVS2DVS Delay too Large", usDVstCom);

            // Get the difference between IVS2DVS Delay and IVSt (unit: I line)
            usDVstCom = usDVstCom - GET_MDOMAIN_INPUT_VSTART() + ucMargin;
            DebugMessageFS("difference", usDVstCom);

            // Get Required Increment of DVSt (unit: D line)
            usDVstCom = (DWORD)usDVstCom * GET_MDOMAIN_OUTPUT_VHEIGHT() / GET_MDOMAIN_INPUT_VHEIGHT() + 1;

            if((GET_MDOMAIN_OUTPUT_VSTART() + usDVstCom + GET_MDOMAIN_OUTPUT_VHEIGHT() + _PANEL_FRONT_PORCH_LIMIT) > GET_MDOMAIN_OUTPUT_VTOTAL())
            {
                usDVstCom = GET_MDOMAIN_OUTPUT_VTOTAL() - (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT() + _PANEL_FRONT_PORCH_LIMIT);
                DebugMessageFS("!!! DVstCom too Large, Reduce DVstCom, Need to Check DVS reset & _PANEL_FRONT_PORCH_LIMIT", usDVstCom);
            }

            // Modify DVSt & background DVSt
            SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + usDVstCom);
            SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());

            // Compare IVS2DVS & DVst increase (unit: I pixel)
            if(ulIVStoDVSPixels > (DWORD)usDVstCom * GET_MDOMAIN_INPUT_HTOTAL() * GET_MDOMAIN_INPUT_VHEIGHT() / GET_MDOMAIN_OUTPUT_VHEIGHT())
            {
                // Modify IVS2DVS Delay
                ulIVStoDVSPixels -= (DWORD)usDVstCom * GET_MDOMAIN_INPUT_HTOTAL() * GET_MDOMAIN_INPUT_VHEIGHT() / GET_MDOMAIN_OUTPUT_VHEIGHT();
            }
            else
            {
                ulIVStoDVSPixels = 0;
                DebugMessageFS("IVS2DVS delay too small", ulIVStoDVSPixels);
            }

            if(GET_MDOMAIN_INPUT_VSTART() >= 1)
            {
                // Check DVS rising and Iden > 0.1 I line
                if(ulIVStoDVSPixels > ((DWORD)GET_MDOMAIN_INPUT_VSTART() * GET_MDOMAIN_INPUT_HTOTAL() - (GET_MDOMAIN_INPUT_HTOTAL() / 10)))
                {
                    ulIVStoDVSPixels = ((DWORD)GET_MDOMAIN_INPUT_VSTART() * GET_MDOMAIN_INPUT_HTOTAL() - (GET_MDOMAIN_INPUT_HTOTAL() / 10));
                    DebugMessageFS("Warnning!!!! Check DVS rising to Iden start > 0.1 I line.", ulIVStoDVSPixels);
                }
            }
        }
    }

    // Before is frame sync mode, current is frame sync mode, check IVS2DVS delay change
    if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
    {
        // Get Old IVS2DVS + IVSdelay (I line)
        PDATA_WORD(0) = (ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData) / GET_MDOMAIN_INPUT_HTOTAL());

        // Calculate current frame sync fine-tune value
        PDATA_WORD(1) = (ulIVStoDVSPixels / GET_MDOMAIN_INPUT_HTOTAL());

        // IVS2DVS Change Limit (Convert DVline limit to IVline)
        PDATA_WORD(2) = (DWORD)_PANEL_DV_LINE_CHG_LIMIT * GET_MDOMAIN_INPUT_VHEIGHT() / GET_MDOMAIN_OUTPUT_VHEIGHT();

        ScalerMemoryFineTuneIVS2DVSDelay(PDATA_WORD(0), PDATA_WORD(1), PDATA_WORD(2));
    }

    if(GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE)
    {
        // Video Compensation on Even Field
        if(ScalerGetBit(usSUPageAddr, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Enable Frame Sync Fine Tune on Odd Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        // Video Compensation on Odd Field
        else if(ScalerGetBit(usSUPageAddr, (_BIT7 | _BIT6)) == _BIT7)
        {
            // Enable Frame Sync Fine Tune on Even Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT1 | _BIT0), _BIT1);
        }
        else
        {
            // Disable Frame Sync Fine Tune
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);
        }
    }
    else
    {
        // Disable Frame Sync Fine Tune
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);
    }

    ScalerMemorySetIVS2DVSDelayPixel(ulIVStoDVSPixels, &g_stMDomainInputData);
}

#if(_M_DOMAIN_LSR_LINE_BUFFER_DT_FORCE_10_TO_8_BIT == _ON)
//--------------------------------------------------
// Description  : Set Memory Data Bit 10 to 8
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryForceMemoryDataBit10to8(void)
{
    WORD usVFactor = ((DWORD)GET_INPUT_TIMING_VHEIGHT() * 100) / _PANEL_DV_HEIGHT;

    // Check if DHtotal/DHwidth > 2.1
    if(((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 10) > ((DWORD)GET_MDOMAIN_OUTPUT_HWIDTH() * 21))
    {
        // Check if 0.95 < IVHeight/DVHeight < 2, Dt margin is not enough, need to force memory 8bit.
        if((usVFactor > 95) && (usVFactor < 200))
        {
            if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
            {
                ScalerMDomainSetMemoryDataBit(_COLOR_DEPTH_8_BITS);
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Set IVS2DVS Delay (line & pixel)
// Input Value  : ulIVStoDVSPixels, StructTimingInfo *pstMdomainInputInfo
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetIVS2DVSDelayPixel(DWORD ulIVStoDVSPixels, const StructTimingInfo *pstMdomainInputInfo)
{
    BYTE ucEOshift = 0;
    BYTE ucFBshift = 0;

    switch(ScalerMDomainGetInputPathCount(pstMdomainInputInfo->enumInputDataPath))
    {
        case _INPUT_PATH_2:
            ucEOshift = 1;
            break;

        case _INPUT_PATH_4:
            ucEOshift = 1;
            ucFBshift = 1;
            break;

        default:
            break;
    }

    ulIVStoDVSPixels = (ulIVStoDVSPixels >> ucEOshift);

    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
       (ScalerGetBit(P0_43_FS_DELAY_FINE_TUNE, _BIT1) == _BIT1) &&
       (ulIVStoDVSPixels >= ((DWORD)((pstMdomainInputInfo->usHTotal >> 1) + 64) >> ucEOshift)))
    {
        // Preserve 0.5 lines + 64 pixel in Fine Tune Byte
        PDATA_WORD(2) = (ulIVStoDVSPixels - (((pstMdomainInputInfo->usHTotal >> 1) + 64) >> ucEOshift)) / pstMdomainInputInfo->usHTotal;
        PDATA_WORD(3) = (ulIVStoDVSPixels - ((DWORD)pstMdomainInputInfo->usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
        PDATA_WORD(4) = (ulIVStoDVSPixels - (pstMdomainInputInfo->usHTotal >> (1 + ucEOshift)) - ((DWORD)pstMdomainInputInfo->usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
        pData[10] = (ulIVStoDVSPixels - ((DWORD)pstMdomainInputInfo->usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << (4 + ucFBshift))) >> ucFBshift;
        pData[11] = (ulIVStoDVSPixels - ((DWORD)pstMdomainInputInfo->usHTotal * PDATA_WORD(2)) - (PDATA_WORD(4) << (4 + ucFBshift))) >> ucFBshift;
    }

    else
    {
        PDATA_WORD(2) = ulIVStoDVSPixels / pstMdomainInputInfo->usHTotal;
        PDATA_WORD(3) = (ulIVStoDVSPixels - ((DWORD)pstMdomainInputInfo->usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
        PDATA_WORD(4) = 0x0000;
        pData[10] = (ulIVStoDVSPixels - ((DWORD)pstMdomainInputInfo->usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << (4 + ucFBshift))) >> ucFBshift;
        pData[11] = 0x00;
    }

    //-------------------------------------------------
    // Apply updated Delay
    //-------------------------------------------------
    // IVS2DVS line delay, unit: line
    ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (HIBYTE(PDATA_WORD(2)) & 0x1F));
    ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, LOBYTE(PDATA_WORD(2)));

    // IVS2DVS 16iclk1 delay, unit: 16 pixel
    PDATA_WORD(3) -= (PDATA_WORD(3) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK1(PDATA_WORD(3));

    // IVS2DVS 16iclk2 delay, unit: 16 pixel
    PDATA_WORD(4) -= (PDATA_WORD(4) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK2(PDATA_WORD(4));

    // IVS2DVS iclk1 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0xF0, ((pData[10] & 0x0F) << 4));

    // IVS2DVS iclk2 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0x0F, (pData[11] & 0x0F));
}

//--------------------------------------------------
// Description  : Get IVS2DVS delay, unit: pixel
// Input Value  : StructTimingInfo *pstMdomainInputInfo
// Output Value : IVS2DVS delay, unit: pixel
//--------------------------------------------------
DWORD ScalerMemoryGetIVS2DVSDelayPixel(const StructTimingInfo *pstMdomainInputInfo)
{
    DWORD ulIVS2DVSDelayPixel = 0;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerMDomainGetInputPathCount(pstMdomainInputInfo->enumInputDataPath) == _INPUT_PATH_4)
    {
        ulIVS2DVSDelayPixel = (((((DWORD)ScalerGetByte(P0_3E_IVS2DVS_DLY_LINE_H) << 8) & 0x1F00) | ScalerGetByte(P0_40_IVS2DVS_DLY_LINE_L)) * pstMdomainInputInfo->usHTotal) +
                              ((((((DWORD)ScalerGetByte(P0_3F_DISPLAY_ALIGN_CONTROL) << 4) & 0x300) | ScalerGetByte(P0_41_IVS2DVS_DLY_TUNE_ODD)) + 1) * 16 * 2) +
                              (((ScalerGetByte(P0_3D_IV_DV_DELAY_CLK_FINE) >> 4) & 0x0F) * 2);

        ulIVS2DVSDelayPixel = (ulIVS2DVSDelayPixel << 1);
    }
    else
#endif
    {
        ulIVS2DVSDelayPixel = (((((DWORD)ScalerGetByte(P0_3E_IVS2DVS_DLY_LINE_H) << 8) & 0x1F00) | ScalerGetByte(P0_40_IVS2DVS_DLY_LINE_L)) * pstMdomainInputInfo->usHTotal) +
                              ((((((DWORD)ScalerGetByte(P0_3F_DISPLAY_ALIGN_CONTROL) << 4) & 0x300) | ScalerGetByte(P0_41_IVS2DVS_DLY_TUNE_ODD)) + 1) * 16) +
                              ((ScalerGetByte(P0_3D_IV_DV_DELAY_CLK_FINE) >> 4) & 0x0F);

        if(ScalerFmtCnvFtoPGetStatus(pstMdomainInputInfo->enumInputDataPath) == _TRUE)
        {
            ulIVS2DVSDelayPixel = (ulIVS2DVSDelayPixel << 1);
        }
    }

    return ulIVS2DVSDelayPixel;
}

//--------------------------------------------------
// Description  : Get IVS reset
// Input Value  : Input data path
// Output Value : _TRUE: IVS reset, _FALSE: DVS reset
//--------------------------------------------------
bit ScalerMemoryGetMdomainIVSReset(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputDataPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            if(GET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), P5_AE_DISP_M1_DISP_CTRL2, _BIT4) == _BIT4)
            {
                return _TRUE;
            }
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Transfer D domain pixel to I domain pixel
// Input Value  : D domain pixel
// Output Value : I domain pixel
//--------------------------------------------------
DWORD ScalerMemoryTransDDomainToIDomainPixel(DWORD ulDDomainPixel)
{
    PDATA_DWORD(0) = GET_DWORD_MUL_DIV(ulDDomainPixel, GET_MDOMAIN_INPUT_VHEIGHT(), GET_MDOMAIN_OUTPUT_VHEIGHT());
    PDATA_DWORD(0) = GET_DWORD_MUL_DIV(PDATA_DWORD(0), GET_MDOMAIN_INPUT_HTOTAL(), GET_MDOMAIN_OUTPUT_HTOTAL());

    return PDATA_DWORD(0);
}

//--------------------------------------------------
// Description  : Transfer I domain pixel to D domain pixel
// Input Value  : I domain pixel
// Output Value : D domain pixel
//--------------------------------------------------
DWORD ScalerMemoryTransIDomainToDDomainPixel(DWORD ulIDomainPixel)
{
    PDATA_DWORD(0) = GET_DWORD_MUL_DIV(ulIDomainPixel, GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT());
    PDATA_DWORD(0) = GET_DWORD_MUL_DIV(PDATA_DWORD(0), GET_MDOMAIN_OUTPUT_HTOTAL(), GET_MDOMAIN_INPUT_HTOTAL());

    return PDATA_DWORD(0);
}

//--------------------------------------------------
// Description  : Check Screen Cover Status, Background or Blending
// Input Value  : None
// Output Value : _TRUE: Scaren Cover by Background or Blending
//--------------------------------------------------
bit ScalerMemoryCheckScreenCoverStatus(void)
{
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) &&
       (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R2_A1))
    {
        // Blending status
        if(ScalerDDomainGetR2DenEnable() == _DISABLE)
        {
            return _TRUE;
        }
    }
#endif

    // Background status
    if(ScalerDDomainGetBackgroundStatus(GET_MDOMAIN_OUTPUT_RGN()) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get Shift One Line support
// Input Value  : NA
// Output Value : _ENABLE: shift one line support
//--------------------------------------------------
bit ScalerMemoryGetShiftOneLineSupport(void)
{
    if(ScalerDrrIVSProduceByBE(GET_MDOMAIN_SOURCE_TYPE(), GET_MDOMAIN_INPUT_PORT()) == _TRUE)
    {
        // IVst = 0, normal case, enable shift one line
        if(ScalerVgipGetCaptureVStartPosition() == 0x00)
        {
            return _ENABLE;
        }

#if((_HW_FORMAT_CONVERSION_EO_MODE == _ON) && (_FRC_SUPPORT == _ON))
        // If EOtoFB is enabled, VS Bypass is enabled, enable shift one line
        if((ScalerFRCGetEOtoFBStatus() == _TRUE) &&
           (GET_MDOMAIN_VGIP_VSYNC_BY_PASS() == _ENABLE))
        {
            return _ENABLE;
        }
#endif
        // Ivst != 0, overscan case, disable shift one line
        return _DISABLE;
    }
    return _DISABLE;
}
//--------------------------------------------------
// Description  : Set Shift One Line ON/OFF and Fifo reset for Free Sync
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerMemorySetShiftOneLine(bit bEnable, EnumInputDataPath enumInputDataPath)
{
    BYTE ucValue = 0x00;

    enumInputDataPath = enumInputDataPath;

#if(_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE)
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            if(bEnable == _ENABLE)
            {
                // Enable Scale Down FREESYNC Mode
                SET_PAGED_BIT(ucIdomainPage, P0_26_SD_FILTER_CONTROL_REG_M1, ~_BIT1, _BIT1);
            }
            else
            {
                // Disable Scale Down FREESYNC Mode
                SET_PAGED_BIT(ucIdomainPage, P0_26_SD_FILTER_CONTROL_REG_M1, ~_BIT1, 0x00);
            }
        }
    }
#endif

    if((bEnable == _ENABLE) && (GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER))
    {
        // Set IVS Reset M-Domain FIFO
        ucValue = _BIT4;
    }
    else
    {
        // Set DVS Reset M-Domain FIFO
        ucValue = 0;
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(ScalerFRCGetMDispPath(enumInputDataPath), GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), P5_AE_DISP_M1_DISP_CTRL2, ~_BIT4, ucValue);
        }
    }
}
#endif

#if(_DT_RANGE_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initialize for Dt Scan
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryDtRangeInitial(void)
{
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

    // Clear HV error Status
    ScalerSetBit(P0_A1_M1_IRQ_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
        }
    }

    // Clear Buffer Status
    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    if(ScalerGetBit(PC0_04_M1_OVF_UDF_CTRL, (_BIT1 | _BIT0)) != 0x00)
    {
        DebugMessageAutoTest(" Frame sync ERROR ", 0);
        DebugMessageAutoTest("---- Dt Scan Fail -----", 0);
        return;
    }

    // Disable Watch Dog
    ScalerGlobalPathWatchDog(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);

    // Disable Double Buffer
    ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);

    // Disable video compensation
    ScalerSetBit(ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN()), ~(_BIT7 | _BIT5), _BIT5);
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    DebugMessageAutoTest("3. IHFreq", GET_MDOMAIN_INPUT_HFREQ());
    DebugMessageAutoTest("3. IHTotal", GET_MDOMAIN_INPUT_HTOTAL());
    DebugMessageAutoTest("3. IHStart", GET_MDOMAIN_INPUT_HSTART());
    DebugMessageAutoTest("3. IHWidth", GET_MDOMAIN_INPUT_HWIDTH());

    DebugMessageAutoTest("3. IVFreq", GET_MDOMAIN_INPUT_VFREQ());
    DebugMessageAutoTest("3. IVTotal", GET_MDOMAIN_INPUT_VTOTAL());
    DebugMessageAutoTest("3. IVStart", GET_MDOMAIN_INPUT_VSTART());
    DebugMessageAutoTest("3. IVHeight", GET_MDOMAIN_INPUT_VHEIGHT());

    DebugMessageAutoTest("3. DHtotal", ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL));
    DebugMessageAutoTest("3. DHWidth", ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH));
    DebugMessageAutoTest("3. DVheight", ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT));
}

//--------------------------------------------------
// Description  : Test the Upper/Lower Bound for Dt
// Input Value  : usVheight: fifo Vheight
// Output Value : None
//--------------------------------------------------
void ScalerMemoryDtRangeTest(WORD usVheight)
{
    DebugMessageAutoTest("3. ========================START========================", 0);

#if(_COLOR_IP_LSR == _ON)
    // Enable LSR
    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, _ON);
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, _ON);
    }
#endif

    ScalerMDomainControlDBApply();

    DebugMessageAutoTest("3. LSR_ENABLE", ScalerGetByte(P11_11_LSR_CTRL_R1_A1));
    DebugMessageAutoTest("3. MEMORY_BIT", GET_MEMORY_DATA_BIT());

    ScalerMemoryDtRangeScan(usVheight);
    DebugMessageAutoTest("3. ========================END========================", 0);

    DebugMessageAutoTest("3. ========================START========================", 0);

#if(_COLOR_IP_LSR == _ON)
    // Disable LSR
    ScalerColorLSREnable(_DDOMAIN_RGN_R1_A1, _OFF);
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerColorLSREnable(_DDOMAIN_RGN_R3_A1, _OFF);
    }
#endif

    ScalerMDomainControlDBApply();


    DebugMessageAutoTest("3. LSR_ENABLE", ScalerGetByte(P11_11_LSR_CTRL_R1_A1));
    DebugMessageAutoTest("3. MEMORY_BIT", GET_MEMORY_DATA_BIT());

    ScalerMemoryDtRangeScan(usVheight);
    DebugMessageAutoTest("3. ========================END========================", 0);
}

//--------------------------------------------------
// Description  : Test the Upper/Lower Bound for Dt
// Input Value  : usVheight: fifo Vheight
// Output Value : None
//--------------------------------------------------
void ScalerMemoryDtRangeScan(WORD usVheight)
{
    BYTE ucNum = 50;
    WORD usBackupIVst = GET_MDOMAIN_INPUT_VSTART();
    WORD usBackupIvsDelay = ScalerVgipGetCaptureVDelay();
    WORD usBackupDVst = GET_MDOMAIN_OUTPUT_VSTART();
    WORD usSUPageAddr = ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN());
    WORD usRealDt = 0;
    WORD usDtLower = 0;
    WORD usDtUpper = 0;

    if(GET_MEMORY_WORK_TYPE() == _MEMORY_WORK_MODE)
    {
        DebugMessageAutoTest("Frame Buffer", ScalerMemoryDtRangeRealDt());
        return;
    }

    ScalerMemoryDtRangeInitial();
    ScalerMemoryDtRangePrintFWDt(usVheight);

    usRealDt = ScalerMemoryDtRangeRealDt();
    DebugMessageAutoTest("3. RealDt", usRealDt);
    DebugMessageAutoTest("3. -------------------------", 0);

    if(ScalerGetBit(PC0_04_M1_OVF_UDF_CTRL, (_BIT1 | _BIT0)) != 0x00)
    {
        DebugMessageAutoTest("Fail", 0);
        return;
    }

    ucNum = 50;
    while((ScalerGetBit(PC0_04_M1_OVF_UDF_CTRL, (_BIT1 | _BIT0)) == 0x00) && (ucNum > 0))
    {
        ucNum -= 1;
        ScalerMemoryFrameSyncSetDt(ucNum, usVheight);
        ScalerMDomainSetDisplayTimingGen(GET_MDOMAIN_OUTPUT_RGN());

        for(BYTE ucIndex = 0; ucIndex < _DT_RANGE_TEST_FRAMENUM; ucIndex++)
        {
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        }

        // clear overflow/unferflow flags
        for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
            {
                SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
                SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
            }
        }

        ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // clear display line buffer busy flag
        ScalerSetBit(usSUPageAddr, ~_BIT5, _BIT5);

        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }

    ucNum += 1;
    ScalerMemoryFrameSyncSetDt(ucNum, usVheight);
    ScalerMDomainSetDisplayTimingGen(GET_MDOMAIN_OUTPUT_RGN());

    // Clear HV error Status
    ScalerSetBit(P0_A1_M1_IRQ_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
        }
    }

    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    usDtLower = ScalerMemoryDtRangeRealDt();
    DebugMessageAutoTest("3. Dt_lower", usDtLower);
    DebugMessageAutoTest("3. -------------------------", 0);

    // restore original ivst, dvst
    SET_MDOMAIN_INPUT_VSTART(usBackupIVst);
    SET_MDOMAIN_OUTPUT_VSTART(usBackupDVst);
    SET_MDOMAIN_OUTPUT_VBSTART(usBackupDVst);

    if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
    {
        // Set new IVSt under analog capture
        ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART());
        ScalerVgipSetCaptureVDelay(usBackupIvsDelay);
    }

    ucNum = 50;
    ScalerMemoryFrameSyncSetDt(ucNum, usVheight);
    ScalerMDomainSetDisplayTimingGen(GET_MDOMAIN_OUTPUT_RGN());

    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

    // clear overflow/unferflow flags
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
        }
    }

    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    SET_DT_UPPER_SCAN_FLAG();

    while((ScalerGetBit(PC0_04_M1_OVF_UDF_CTRL, (_BIT1 | _BIT0)) == 0x00) && (ucNum < 100))
    {
        ucNum += 1;
        ScalerMemoryFrameSyncSetDt(ucNum, usVheight);
        ScalerMDomainSetDisplayTimingGen(GET_MDOMAIN_OUTPUT_RGN());

        for(BYTE ucIndex = 0; ucIndex < _DT_RANGE_TEST_FRAMENUM; ucIndex++)
        {
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        }

        // clear overflow/unferflow flags
        for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
            {
                SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
                SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
            }
        }

        ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // clear display line buffer busy flag
        ScalerSetBit(usSUPageAddr, ~_BIT5, _BIT5);

        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }

    ucNum -= 1;
    ScalerMemoryFrameSyncSetDt(ucNum, usVheight);
    ScalerMDomainSetDisplayTimingGen(GET_MDOMAIN_OUTPUT_RGN());

    CLR_DT_UPPER_SCAN_FLAG();

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
        }
    }

    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    usDtUpper = ScalerMemoryDtRangeRealDt();
    DebugMessageAutoTest("3. Dt_upper", usDtUpper);
    DebugMessageAutoTest("3. -------------------------", 0);

    // restore original ivst, dvst
    SET_MDOMAIN_INPUT_VSTART(usBackupIVst);
    SET_MDOMAIN_OUTPUT_VSTART(usBackupDVst);
    SET_MDOMAIN_OUTPUT_VBSTART(usBackupDVst);

    if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
    {
        // Set new IVSt under analog capture
        ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART());
        ScalerVgipSetCaptureVDelay(usBackupIvsDelay);
    }

    ScalerMemoryFrameSyncSetDt(50, usVheight);
    ScalerMDomainSetDisplayTimingGen(GET_MDOMAIN_OUTPUT_RGN());

    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
        }
    }

    // clear overflow/unferflow flags
    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Clear Display Vsync timeout flag
    ScalerGlobalClrDvsTimeoutFlag();

    // clear display line buffer busy flag
    ScalerSetBit(usSUPageAddr, ~_BIT5, _BIT5);

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    DebugMessageAutoTest("3. Dt Scan Result: Dt Lower Bound (unit: 0.01 line)", (usRealDt - usDtLower));
    DebugMessageAutoTest("3. Dt Scan Result: Dt Upper Bound (unit: 0.01 line)", (usDtUpper - usRealDt));

    if(((usRealDt - usDtLower) < 50) ||
       ((usDtUpper - usRealDt) < 50))
    {
        DebugMessageAutoTest("3. Dt Warning!!! Dt margin is insufficient!!!", 0);
    }
}

//--------------------------------------------------
// Description  : Get Real Dt From Register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryDtRangePrintFWDt(WORD usVheight)
{
    WORD usDtMin = 0;
    WORD usDtMax = 0;
    DWORD ulDtMaxMin = ScalerMemoryGetDtMaxMin(usVheight);

    usDtMin = (WORD)(ulDtMaxMin & 0xFFFF);
    usDtMax = (WORD)((ulDtMaxMin >> 16) & 0xFFFF);

    if((usDtMax == 0) || (usDtMin == 0))
    {
        usDtMax = 0;
        usDtMin = 0;
    }

    DebugMessageAutoTest("3. Dtmax", usDtMax);
    DebugMessageAutoTest("3. Dtmin", usDtMin);
    DebugMessageAutoTest("5. DtTarget", (usDtMin + usDtMax) / 2);
}
//--------------------------------------------------
// Description  : Get Real Dt From Register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ScalerMemoryDtRangeRealDt(void)
{
    DWORD ulIVStoDVSPixels = 0;
    WORD usIVS2DVSdelayP0_40 = 0;
    WORD usIVS2DVSdelayP0_41 = 0;
    DWORD ulIVstartPixel = 0;
    DWORD ulDVstartPixel = 0;
    WORD usDHst = 0;
    WORD usDVst = 0;
    WORD usDVheight = 0;
    WORD usDHtotal = 0;
    WORD usIVstartAfterVSD = 0;

    usDHtotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);

    usDHst = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
    usDVst = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
    usDVheight = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT);

    usIVS2DVSdelayP0_40 = (((WORD)ScalerGetByte(P0_3E_IVS2DVS_DLY_LINE_H) << 8) & 0x1F00) | ScalerGetByte(P0_40_IVS2DVS_DLY_LINE_L);
    usIVS2DVSdelayP0_41 = (((WORD)ScalerGetByte(P0_3F_DISPLAY_ALIGN_CONTROL) << 4) & 0x300) | ScalerGetByte(P0_41_IVS2DVS_DLY_TUNE_ODD);
    ulIVStoDVSPixels = ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData);

    usIVstartAfterVSD = g_stMDomainInputData.usVStart;

    if((GET_V_SCALE_DOWN() == _TRUE) && (ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT7) == _BIT7))
    {
        switch (ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()))
        {
            case _INPUT_PATH_1:
            default:
                usIVstartAfterVSD += 1;
                break;

            case _INPUT_PATH_2:
            case _INPUT_PATH_4:
                usIVstartAfterVSD += 2;
                break;
        }
    }

    DebugMessageAutoTest("3. -------------------------", 0);
    DebugMessageAutoTest("3. P0_40", usIVS2DVSdelayP0_40);
    DebugMessageAutoTest("3. P0_41", usIVS2DVSdelayP0_41);

    DebugMessageAutoTest("3. Dvst_line", usDVst);
    DebugMessageAutoTest("3. IVst_line", usIVstartAfterVSD);

    DebugMessageAutoTest("3. IVS_delay", ScalerGetByte(P0_1C_M1_IVS_DELAY));

    DebugMessageAutoTest("3. ulIVStoDVSPixels", ulIVStoDVSPixels);

    ulDVstartPixel = ((DWORD)usDHtotal * usDVst) + usDHst;
    ulDVstartPixel = ulDVstartPixel * g_stMDomainInputData.usVHeight / usDVheight * g_stMDomainInputData.usHTotal / usDHtotal;
    DebugMessageAutoTest("3. ulDVstartPixel", ulDVstartPixel);

    // Calculate IVS to IH Active in ICLK
    ulIVstartPixel = ((DWORD)g_stMDomainInputData.usHTotal * usIVstartAfterVSD) + g_stMDomainInputData.usHStart;
    DebugMessageAutoTest("3. ulIVstartPixel", ulIVstartPixel);

    return ((DWORD)(ulDVstartPixel + ulIVStoDVSPixels - ulIVstartPixel) * 100 / g_stMDomainInputData.usHTotal);
}

#if(_HW_FORMAT_CONVERSION_EO_MODE == _OFF)
//--------------------------------------------------
// Description  : modify dt upper scan flow for single path
// Input Value  : ulPrereadPosPixel, ulLineData, ulIVstart, ulPrereadFinetune, *pstDtCalInfo
// Output Value : None
//--------------------------------------------------
void ScalerMemoryDtUpperScanForSinglePath(DWORD ulLineData, DWORD ulIVstart, StructDtCalInfo *pstDtCalInfo)
{
    if(g_stMDomainInputData.usVHeight > g_stMDomainOutputData.usVHeight)
    {
        g_stMDomainOutputData.usVStart += 1;

        // Calculate DVS to DH Active in ICLK
        pstDtCalInfo->ulDVstart = ((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainOutputData.usVStart) + g_stMDomainOutputData.usHStart;
        pstDtCalInfo->ulDVstart = pstDtCalInfo->ulDVstart * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal;

        // IVS2DVS delay
        pstDtCalInfo->ulIVStoDVSPixels = 0;
    }
    else
    {
        if(ulLineData > _M_DOMAMAIN_FIFO_BIT)
        {
            g_stMDomainOutputData.usVStart += 1;

            // Calculate DVS to DH Active in ICLK
            pstDtCalInfo->ulDVstart = ((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainOutputData.usVStart) + g_stMDomainOutputData.usHStart;
            pstDtCalInfo->ulDVstart = pstDtCalInfo->ulDVstart * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal;

            // IVS2DVS delay
            pstDtCalInfo->ulIVStoDVSPixels = (ulIVstart > pstDtCalInfo->ulDVstart) ? (ulIVstart - pstDtCalInfo->ulDVstart) : 0;
        }
    }
}
#endif
#endif // End of #if(_DT_RANGE_TEST_SUPPORT == _ON)

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Framesync Fix lastline
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFramesyncFixLastlineEnable(bit bEnable)
{
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT2, ((bEnable == _ENABLE) ? _BIT2 : 0x00))
}
//--------------------------------------------------
// Description  : Get Framesync Fix lastline
// Input Value  : None
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerMemoryGetFramesyncFixLastlinesStatus(void)
{
    if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT2) != 0)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif // End of #if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Description  : Allocate Initial BW
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryBwAllocation(void)
{
    DWORD ulTotalBw = ((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) ? _MEMORY_TOTAL_BW : _MEMORY_TOTAL_BW_MTP);
    DWORD ulRemainBw = ((_SCPU_SUPPORT == _ON) ? GET_DWORD_MUL_DIV(ulTotalBw, 99, 100) : ulTotalBw);
#if(_GOSD_SUPPORT == _ON)
    DWORD ulGosdBw = GET_DWORD_MUL_DIV(_MEMORY_DATA_RATE_SPEED * 10, ScalerGosdCalMaxMemoryBw(), 100);

    if(ulGosdBw > ulRemainBw)
    {
        ulRemainBw = 0;
    }
    else
    {
        ulRemainBw -= ulGosdBw;
    }
#endif
    SET_MEMORY_FRC_OD_BW(ulRemainBw);

#if(_OD_FUNCTION == _ON)
    SET_MEMORY_REMAIN_BW(GET_MEMORY_FRC_OD_BW());
#endif

#if(_FRC_SUPPORT == _ON)
    ScalerFRCBWInitialAllocation();
#endif
}

//--------------------------------------------------
// Description  : Allocate Initial Space
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemorySpaceAllocation(void)
{
    // vertical order: cpu -> 3ddi -> gosd  -> frc -> od
#if((_GOSD_SUPPORT == _ON) || (_COLOR_IP_3DDI == _ON) || (_FRC_SUPPORT == _ON) || (_OD_FUNCTION == _ON))
    DWORD ulStartAddr = ((_HW_CPU32_ALLOCATE_DDR_SPACE == _ON) ? _FW_CPU32_DDR_MEMORY_SIZE : 0);
    DWORD ulEndAddr = (_MEMORY_ROW << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
#endif
#if((_GOSD_SUPPORT == _ON) || (_COLOR_IP_3DDI == _ON))
    DWORD ulUsedSpace = 0;
#endif

#if(_GOSD_SUPPORT == _ON)
    SET_GOSD_START_ADDRESS(ulStartAddr);
    ulUsedSpace = ulStartAddr + (ScalerGosdCalMaxMemorySize() << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
    SET_GOSD_END_ADDRESS(ulUsedSpace);
    ulStartAddr = ulUsedSpace;

    if((ulStartAddr != 0) && (ulStartAddr >= ulEndAddr))
    {
        DebugMessageMemory("[ERROR] CHECK GOSD START ADDRESS / GOSD MEMORY SIZE", ulStartAddr);
        SET_GOSD_START_ADDRESS(ulEndAddr);
        SET_GOSD_END_ADDRESS(ulEndAddr);
    }
    DebugMessageMemory("GOSD start", GET_GOSD_START_ADDRESS());
    DebugMessageMemory("GOSD end", GET_GOSD_END_ADDRESS());
#endif

#if(_COLOR_IP_3DDI == _ON)
    SET_3DDI_START_ADDRESS(ulStartAddr);
    ulUsedSpace = ulStartAddr + (Scaler3DDICalMaxMemorySize() << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
    SET_3DDI_END_ADDRESS(ulUsedSpace);
    ulStartAddr = ulUsedSpace;

    if(ulStartAddr >= ulEndAddr)
    {
        DebugMessageMemory("[ERROR] CHECK 3DDI START ADDRESS / 3DDI MEMORY SIZE", ulStartAddr);
        SET_3DDI_START_ADDRESS(ulEndAddr);
        SET_3DDI_END_ADDRESS(ulEndAddr);
    }
    DebugMessageMemory("3ddi start", GET_3DDI_START_ADDRESS());
    DebugMessageMemory("3ddi end", GET_3DDI_END_ADDRESS());
#endif

#if(_FRC_SUPPORT == _ON)
    if((ulStartAddr != 0) && (ulStartAddr >= ulEndAddr))
    {
        DebugMessageMemory("[ERROR] CHECK FRC START ADDRESS", ulStartAddr);
        SET_FRC_START_ADDRESS(ulEndAddr);
        SET_FRC_END_ADDRESS(ulEndAddr);
    }
    else
    {
        ScalerFRCCalculateBlockRowSpace((ulEndAddr - ulStartAddr) >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM); // remain row
        SET_FRC_START_ADDRESS(ulStartAddr);
        SET_FRC_END_ADDRESS(ulEndAddr); // * 2 for double buffer without mute
    }
    DebugMessageMemory("FRC start", GET_FRC_START_ADDRESS());
    DebugMessageMemory("FRC end", GET_FRC_END_ADDRESS());
#endif

#if(_OD_FUNCTION == _ON)
    if((ulStartAddr != 0) && (ulStartAddr >= ulEndAddr))
    {
        DebugMessageMemory("[ERROR] CHECK OD START ADDRESS", ulStartAddr);
        SET_OD_START_ADDRESS(ulEndAddr);
        SET_OD_END_ADDRESS(ulEndAddr);
    }
    else
    {
        SET_OD_START_ADDRESS(ulStartAddr);
        SET_OD_END_ADDRESS(ulEndAddr);
    }
    DebugMessageMemory("OD start", GET_OD_START_ADDRESS());
    DebugMessageMemory("OD end", GET_OD_END_ADDRESS());
#endif
}

//--------------------------------------------------
// Description  : Get FRC End address and OD Start address
// Input Value  : None
// Output Value : address
//--------------------------------------------------
DWORD ScalerMemoryGetFRCODBoundary(void)
{
#if(_FRC_SUPPORT == _ON)

    ScalerFRCGetFRCBottomAddress();
    return GET_FRC_START_ADDRESS() + (GET_FRC_USE_ROW() * ((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) ? 2 : 1));

#elif(_COLOR_IP_3DDI == _ON)

    return GET_3DDI_END_ADDRESS();

#elif(_GOSD_SUPPORT == _ON)

    return GET_GOSD_END_ADDRESS();

#elif(_HW_CPU32_ALLOCATE_DDR_SPACE == _ON)

    return _FW_CPU32_DDR_MEMORY_SIZE;

#endif

    return 0;
}

//--------------------------------------------------
// Description  : Adjust FRC End address and OD Start address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryAdjustFRCODBoundary(void)
{
#if((_FRC_SUPPORT == _ON) || (_OD_FUNCTION == _ON))
    DWORD ulStartAddr = ScalerMemoryGetFRCODBoundary();
#endif

#if(_FRC_SUPPORT == _ON)
    SET_FRC_END_ADDRESS(ulStartAddr);
#endif

#if(_OD_FUNCTION == _ON)
    SET_OD_START_ADDRESS(ulStartAddr);
#endif
}

#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set BW Ctrl Enable/Disable
// Input Value  : client type, client index, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetBwCtrlEnable(EnumMemoryClientType enumClientType, BYTE ucClientIndex, bit bEnable)
{
    enumClientType = enumClientType;
    ucClientIndex = ucClientIndex;
    bEnable = bEnable;

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    ScalerDDR3SetBwCtrlEnable(enumClientType, ucClientIndex, bEnable);
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
    ScalerDDR2SetBwCtrlEnable(enumClientType, ucClientIndex, bEnable);
#endif
}

//--------------------------------------------------
// Description  : Set memory BW ctrl
// Input Value  : client type, client index, client info function pointer
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetBwCtrl(EnumMemoryClientType enumClientType, BYTE ucClientIndex, StructBwCtrlClientInfo *pstClientInfo)
{
    enumClientType = enumClientType;
    ucClientIndex = ucClientIndex;
    pstClientInfo = pstClientInfo;

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    ScalerDDR3SetBwCtrl(enumClientType, ucClientIndex, pstClientInfo);
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
    ScalerDDR2SetBwCtrl(enumClientType, ucClientIndex, pstClientInfo);
#endif
}
#endif // End of #if(_MEMORY_BW_CTRL_SUPPORT == _ON)
#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

