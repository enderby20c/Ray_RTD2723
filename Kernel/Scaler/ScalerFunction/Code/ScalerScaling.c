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
// ID Code      : ScalerScaling.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_SCALING__

#include "ScalerFunctionInclude.h"
#include "Scaling/ScalerScaling.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// 128 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#if(_SD_TABLE_SEL_FUNCTION == _OFF)
BYTE code tSD_H_COEF_128_TAPS[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};
#endif

//----------------------------------------------------------------------------------------------------
// 64 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_V_COEF_64_TAPS[] =
{
    0x82, 0x0F, 0x97, 0x0F, 0xA4, 0x0F, 0xCE, 0x0F, 0xE8, 0x0F, 0x1A, 0x00, 0x3B, 0x00, 0x73, 0x00,
    0x98, 0x00, 0xD2, 0x00, 0xF8, 0x00, 0x32, 0x01, 0x58, 0x01, 0x91, 0x01, 0xB5, 0x01, 0xEE, 0x01,
    0x7E, 0x04, 0x69, 0x04, 0x5C, 0x04, 0x32, 0x04, 0x18, 0x04, 0xE6, 0x03, 0xC5, 0x03, 0x8D, 0x03,
    0x68, 0x03, 0x2E, 0x03, 0x08, 0x03, 0xCE, 0x02, 0xA8, 0x02, 0x6F, 0x02, 0x4B, 0x02, 0x12, 0x02,
};

#if(_SHARPNESS_FUNCTION == _OFF)
//----------------------------------------------------------------------------------------------------
// 128 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_SU_COEF_128_TAPS[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};
#endif

#if(((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON)) && (_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE) && (_SD_TABLE_SEL_FUNCTION == _OFF))
//----------------------------------------------------------------------------------------------------
// 64 taps bypass Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_V_COEF_64_TAPS_BYPASS[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04,
    0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04,
};
#endif
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
BYTE g_ucScalingDropExtension;
BYTE g_ucScalingIdomain4PathStatus;
#endif

StructScalingInfo g_stScalingInfo;
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set scaling initial settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetInitial(void)
{
    // Disable H/V SU
    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        ScalerSetBit(ScalerDDomainGetScalingUpPageAddr(GET_DDOMAIN_OUTPUT_REGION(ucIndex)), ~(_BIT5 | _BIT1 | _BIT0), _BIT5);
    }
}

//--------------------------------------------------
// Description  : Decide which scaling up function should be performed
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetScalingUp(const StructSDRAMDataInfo *pstFIFOScaling)
{
    WORD usRegPagedAddrSel = 0x00;

    if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_ALL)
    {
        usRegPagedAddrSel = _REG_MAIN1_PAGE;
    }
    else
    {
        switch(GET_MDOMAIN_OUTPUT_RGN())
        {
#if(_HW_D_DOMAIN_R1_A1_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R1_A1:
                usRegPagedAddrSel = _REG_MAIN1_PAGE;
                break;
#endif

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R1_A2:
                usRegPagedAddrSel = _REG_MAIN1_PAGE + _A1A2_REG_ADDR_OFFSET;
                break;
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R2_A1:
                usRegPagedAddrSel = _REG_SUB1_PAGE;
                break;
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R2_A2:
                usRegPagedAddrSel = _REG_SUB1_PAGE + _A1A2_REG_ADDR_OFFSET;
                break;
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R3_A1:
                usRegPagedAddrSel = _REG_SUB2_PAGE;
                break;
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R3_A2:
                usRegPagedAddrSel = _REG_SUB2_PAGE + _A1A2_REG_ADDR_OFFSET;
                break;
#endif

            default:
                break;
        }
    }

    CLR_V_SCALE_UP();
    CLR_H_SCALE_UP();

    // Initial Scaling Up register
    ScalerScalingSetScalingUpInitial(usRegPagedAddrSel);

    // VSU Setting
    ScalerScalingSetVScalingUp(pstFIFOScaling, usRegPagedAddrSel);

    // HSU Setting
    ScalerScalingSetHScalingUp(pstFIFOScaling, usRegPagedAddrSel);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // DDomain Extension related setting
    ScalerScalingSetDDomainExtension();
#endif

#if(_FRC_SUPPORT == _ON)
#if(_FW_DISPLAYTOP_AVG_REQ_SUPPORT == _ON)
    if(GET_MEMORY_CONFIG_SELECT() != _FRAME_SYNC_LINE_BUFFER)
    {
        ScalerDDomainSetDdmReqAvgReqFactor(GET_MODE_DISPLAY_TARGET_REGION(), pstFIFOScaling->usOutputHWidth, GET_MDOMAIN_OUTPUT_HWIDTH(), GET_MDOMAIN_OUTPUT_HTOTAL());
        ScalerDDomainSetDdmReqAvgReqEnable(GET_MODE_DISPLAY_TARGET_REGION(), _ENABLE);
    }
    else
    {
        ScalerDDomainSetDdmReqAvgReqEnable(GET_MODE_DISPLAY_TARGET_REGION(), _DISABLE);
    }
#endif
#endif

#if(_HW_ADJ_A1_LB_START_ADDR == _ON)
    ScalerDDomainSetDisplayTopLBStartAddr(GET_MODE_DISPLAY_TARGET_REGION(), pstFIFOScaling->usOutputHWidth);
#endif
}

//--------------------------------------------------
// Description  : Decide which scaling down function should be performed
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetScalingDown(const StructSDRAMDataInfo *pstFIFOScaling)
{
    WORD usRegPageSel = 0x0000;
    bit bEvenOdd = _FALSE;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    SET_IDOMAIN_4PATH_STATUS(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) == _INPUT_PATH_4);
#endif

    // Search for I-domain page
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((GET_MDOMAIN_INPUT_DATA_PATH() & enumCurrPath) != 0)
        {
            usRegPageSel = ((WORD)GET_IDOMAIN_REG_PAGE(ucIndex) << 8);
            break;
        }
    }

    // Check for E/O mode
    switch(GET_MDOMAIN_INPUT_DATA_PATH())
    {
#if(_HW_I_DOMAIN_M1_M2_PATH_SUPPORT == _ON)
        case _INPUT_PATH_M1_M2:
            bEvenOdd = _TRUE;
            break;
#endif
#if(_HW_I_DOMAIN_S1_S2_PATH_SUPPORT == _ON)
        case _INPUT_PATH_S1_S2:
            bEvenOdd = _TRUE;
            break;
#endif
#if(_HW_I_DOMAIN_S3_S4_PATH_SUPPORT == _ON)
        case _INPUT_PATH_S3_S4:
            bEvenOdd = _TRUE;
            break;
#endif
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        case _INPUT_PATH_M1_M2_S1_S2:
            bEvenOdd = _TRUE;
            break;
#endif
        default:
            break;
    }

    CLR_V_SCALE_DOWN();
    CLR_H_SCALE_DOWN();

    // Initial Scaling Down Register
    ScalerScalingSetScalingDownInitial(bEvenOdd, usRegPageSel);

    // HSD Setting
    ScalerScalingSetHScalingDown(pstFIFOScaling, bEvenOdd, usRegPageSel);

    // VSD Setting
    ScalerScalingSetVScalingDown(pstFIFOScaling, bEvenOdd, usRegPageSel);

    // SD Window Setting
    ScalerScalingSetScalingDownWindow(pstFIFOScaling, bEvenOdd, usRegPageSel);

    // Freesync Related Setting
#if(((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON)) && (_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE) && (_SD_TABLE_SEL_FUNCTION == _OFF))
    ScalerScalingSetFSScalingDown(usRegPageSel);
#endif
}

#if(_SD_TABLE_SEL_FUNCTION == _OFF)
//--------------------------------------------------
// Description  : Set Scale Down Coef
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingDownCoef(void)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        WORD usAddr = GET_PAGED_ADDR(ucIdomainPage, P0_27_SD_USER_FILTER_ACCESS_PORT_M1);

        SET_PAGED_BIT(ucIdomainPage, P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), _BIT7);
        ScalerBurstWrite(tSD_H_COEF_128_TAPS, _HSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), usAddr, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        SET_PAGED_BIT(ucIdomainPage, P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), usAddr, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
}
#else
//--------------------------------------------------
// Description  : Set Scale Down RegPageSel
// Input Value  : none
// Output Value : none
//--------------------------------------------------
WORD ScalerScalingCheckRegPageSel(EnumSelRegion enumSelRegion)
{
    BYTE ucIndex = 0;
    WORD usRegPageSel = 0x0000;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPathFromSelRegion(enumSelRegion);

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        // Search for I-domain page
        if((enumInputDataPath & enumCurrPath) != 0)
        {
            usRegPageSel = ((WORD)GET_IDOMAIN_REG_PAGE(ucIndex));
            break;
        }
    }
    return usRegPageSel;
}
//--------------------------------------------------
// Description  : Set Scale Down Coef flexibly
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetFlexibleScalingDownCoef(EnumSelRegion enumSelRegion, BYTE *pucAddressH, BYTE *pucAddressV)
{
    WORD usAddr = GET_PAGED_ADDR((WORD)ScalerScalingCheckRegPageSel(enumSelRegion), P0_27_SD_USER_FILTER_ACCESS_PORT_M1);
    SET_PAGED_BIT((WORD)ScalerScalingCheckRegPageSel(enumSelRegion), P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(pucAddressH, _HSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), usAddr, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    SET_PAGED_BIT((WORD)ScalerScalingCheckRegPageSel(enumSelRegion), P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(pucAddressV, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), usAddr, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
}
//--------------------------------------------------
// Description  : Check Bypass Free Sync enable of Scale Down
// Input Value  : none
// Output Value : none
//--------------------------------------------------
EnumByPassEnable ScalerScalingCheckFSBypassEnable(EnumSelRegion enumSelRegion)
{
    EnumByPassEnable enumBypassFSEnable = _BYPASS_DISABLE;

#if((((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON)) && (_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE)) == _TRUE)
    if((ScalerDrrIVSProduceByBE(GET_MDOMAIN_SOURCE_TYPE(), GET_MDOMAIN_INPUT_PORT()) == _TRUE) && (ScalerScalingGetVScalingDownBypass((WORD)ScalerScalingCheckRegPageSel(enumSelRegion)) == _TRUE))
    {
        enumBypassFSEnable = _BYPASS_ENABLE;
    }
#endif
    return enumBypassFSEnable;
}
#endif

//--------------------------------------------------
// Description  : Set Scale Down Initial
// Input Value  : I-DataPath E/O mode ; Select Page
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingDownInitial(bit bEvenOdd, WORD usRegPageSel)
{
    WORD usEOPage = 0x0000U;

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    usEOPage = ScalerScalingGetEOModePageMapping(usRegPageSel);
#endif

    bEvenOdd = bEvenOdd;
    // Disable Scale Down
    // M1
#if(_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE)
#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    bit bShiftOneLineEnable = ScalerMemoryGetShiftOneLineSupport();

    if((bShiftOneLineEnable == _TRUE) && (ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _DB_DISABLE))
    {
        // Keep VSD enabled under free-sync
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            // M2 or S2 or S4
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~(_BIT3 | _BIT2 | _BIT1), 0x00);
        }
#endif
    }
    else
#endif
#endif
    {
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            // M2 or S2 or S4
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
#endif
    }

#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_1)
    ScalerScalingSetHScalingDownVactRefInputWindow(_DISABLE, bEvenOdd, usRegPageSel, usEOPage);
    ScalerScalingSetVScalingDownVactRefInputWindowSelect(_DISABLE, bEvenOdd, usRegPageSel, usEOPage);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
    {
        // S1
        ScalerSetBit(P80_23_SCALE_DOWN_CTRL_S1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // S2
        ScalerSetBit(PC0_23_SCALE_DOWN_CTRL_S2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_1)
        // S1
        ScalerSetBit(P80_23_SCALE_DOWN_CTRL_S1, ~_BIT4, 0x00);

        // S2
        ScalerSetBit(PC0_23_SCALE_DOWN_CTRL_S2, ~_BIT4, 0x00);
#endif
    }

    // Clear Extension except for FB display mode
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _FALSE)
    {
        // Reset D extension
        SET_DDOMAIN_EXTENSION_LEN(0);
        SET_EXT_RECAP_EXTENSION_LEN_A1(0);
        SET_EXT_RECAP_EXTENSION_LEN_A2(0);

        // Display Extension
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_FRONT, ~0xFFU, 0x00);
        ScalerSetDataPortBit(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1F_DISPLAY_EXTENSION_FB_BACK, ~0xFFU, 0x00);

        // Display Conversion Extension
        ScalerSetByte(P39_1E_DISP_TIMING_CTRL0, 0x00);

        // OSD extension
        ScalerOsdSetExtension(0);
    }

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE)
    {
        // HSD extension = 0
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_3A_SD_OUT_EXTENSION_M1, 0x00);
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_3A_SD_OUT_EXTENSION_M2, 0x00);
        ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_3A_SD_OUT_EXTENSION_S1, 0x00);
        ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_3A_SD_OUT_EXTENSION_S2, 0x00);

        // Drop Extension disable
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, 0x00);
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, 0x00);
        ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, 0x00);
        ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, 0x00);
    }
#endif
}

#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_1)
//--------------------------------------------------
// Description  : Set HScaling Down Vact Ref Input Window or SD Output Window
// Input Value  : bit bEnable, bit bEvenOdd, WORD usRegPageSel, WORD usEOPage
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetHScalingDownVactRefInputWindow(bit bEnable, bit bEvenOdd, WORD usRegPageSel, WORD usEOPage)
{
    bEvenOdd = bEvenOdd;
    usEOPage = usEOPage;

    if(bEnable == _ENABLE)
    {
        // Scaling Down Output Vact Input Signal
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~_BIT4, _BIT4);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _ENABLE)
        {
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~_BIT4, _BIT4);
        }
#endif
    }
    else
    {
        // Scaling Down Output Vact Ref SD Out Window Setting
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~_BIT4, 0x00);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _ENABLE)
        {
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~_BIT4, 0x00);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Set HScaling Down Vact Ref Input Window or SD Output Window
// Input Value  : bit bEnable, bit bEvenOdd, WORD usRegPageSel, WORD usEOPage
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetVScalingDownVactRefInputWindowSelect(bit bEnable, bit bEvenOdd, WORD usRegPageSel, WORD usEOPage)
{
    bEvenOdd = bEvenOdd;
    usEOPage = usEOPage;

    if(bEnable == _ENABLE)
    {
        // Scaling Down Output Vact Input Signal
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~_BIT6, _BIT6);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _ENABLE)
        {
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~_BIT6, _BIT6);
        }
#endif
    }
    else
    {
        // Scaling Down Output Vact Ref SD Out Window Setting
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~_BIT6, 0x00);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _ENABLE)
        {
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~_BIT6, 0x00);
        }
#endif
    }
}
#endif

//--------------------------------------------------
// Description  : Set Horizontal Scale Down
// Input Value  : Input/Output H/V Active Region;I-DataPath E/O mode ; Select Page
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetHScalingDown(const StructSDRAMDataInfo *pstFIFOScaling, bit bEvenOdd, WORD usRegPageSel)
{
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    WORD usEOPage = ScalerScalingGetEOModePageMapping(usRegPageSel);
#endif
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    BYTE ucDropExtension = 0;
#endif
    bEvenOdd = bEvenOdd;

    // Set H Scaling Down Factor
    if(GET_MDOMAIN_INPUT_HWIDTH() > pstFIFOScaling->usInputHWidth)
    {
        DWORD ulHSDF = 0;
        DWORD ulHSDI = 0;
        SET_H_SCALE_DOWN();

        // Calculate Scaling Factor
        ulHSDF = GET_DWORD_MUL_DIV((1UL << (_HSD_FACTOR_BIT)), GET_MDOMAIN_INPUT_HWIDTH(), pstFIFOScaling->usInputHWidth);

        // The rounding of hsd factor may cause frame sync line buffer error under specific resolution
        if(((((1UL << _HSD_FACTOR_BIT) % pstFIFOScaling->usInputHWidth) *
             (GET_MDOMAIN_INPUT_HWIDTH() % pstFIFOScaling->usInputHWidth)) % pstFIFOScaling->usInputHWidth) != 0)
        {
            ulHSDF += 1;
        }

        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_05_H_SD_FACTOR_H_M1, (BYTE)((ulHSDF >> 16) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_06_H_SD_FACTOR_M_M1, (BYTE)((ulHSDF >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_07_H_SD_FACTOR_L_M1, (BYTE)(ulHSDF & 0xFF));

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_05_H_SD_FACTOR_H_M1, (BYTE)((ulHSDF >> 16) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_06_H_SD_FACTOR_M_M1, (BYTE)((ulHSDF >> 8) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_07_H_SD_FACTOR_L_M1, (BYTE)(ulHSDF & 0xFF));
        }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
        {
            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_05_H_SD_FACTOR_H_M1, (BYTE)((ulHSDF >> 16) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_06_H_SD_FACTOR_M_M1, (BYTE)((ulHSDF >> 8) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_07_H_SD_FACTOR_L_M1, (BYTE)(ulHSDF & 0xFF));

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_05_H_SD_FACTOR_H_M2, (BYTE)((ulHSDF >> 16) & 0xFF));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_06_H_SD_FACTOR_M_M2, (BYTE)((ulHSDF >> 8) & 0xFF));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_07_H_SD_FACTOR_L_M2, (BYTE)(ulHSDF & 0xFF));
        }
#endif
        // Calculate Initial Phase keep accuracy 1.6
        // HSDI = (factor-1)/2 = ((HSDF >> 20) - 1)/2 * 2^6 = HSDF >> 15 - 2^5
        ulHSDI = (ulHSDF >> 15) - 32;

        if(ulHSDI > 0x7F)
        {
            ulHSDI = 0x7F;
        }

        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_04_H_SD_INIT_M1, (BYTE)ulHSDI);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_04_H_SD_INIT_M1, (BYTE)ulHSDI);
        }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
        {
            // set drop extension after HSD
            ucDropExtension = (BYTE)((DWORD)pstFIFOScaling->usInputHWidth * GET_FMTCNV_EXTENSION_LEN() / GET_MDOMAIN_INPUT_HWIDTH());

            if(ucDropExtension > 0x1F)
            {
                ucDropExtension = 0x1F;
            }

            if(ucDropExtension > 0)
            {
                // extension + FIFOWidth must be even number
                if(((pstFIFOScaling->usInputHWidth / 2 + ucDropExtension) % 2) != 0)
                {
                    ucDropExtension -= 1;
                }

#if(_HW_DROP_EXTENSION_GEN != _GEN_NONE)
#if(_HW_DROP_EXTENSION_GEN == _DROP_EXTENSION_GEN_1)
                // Drop Extension Gen1
                // M1/M2 drops extension of DEN END ; S1/S2 drops extension of DEN Start
                ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, ~0x1FU, (ucDropExtension & 0x1F));
                ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, ~0x1FU, (ucDropExtension & 0x1F));
                ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_61_DROP_EXTENSION_START_S1, ~0x1FU, (ucDropExtension & 0x1F));
                ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_61_DROP_EXTENSION_START_S2, ~0x1FU, (ucDropExtension & 0x1F));
#else
#warning "_HW_DROP_EXTENSION_GEN should be modified!!"
#endif
#endif
                // Drop Extension Enable
                ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, ~_BIT7, _BIT7);
                ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, ~_BIT7, _BIT7);
                ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, ~_BIT7, _BIT7);
                ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, ~_BIT7, _BIT7);
            }

            // back initial phase = FrontInitialPhase + InExtension for each OutExtension*SDFactor
            ulHSDI = (ulHSDI << 14) + ((DWORD)GET_FMTCNV_EXTENSION_LEN() << 20) - (ucDropExtension * ulHSDF);

            // S1  initialphase
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_45_H_SD_INIT_H_M1, (BYTE)((ulHSDI >> 22) & 0x03));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_04_H_SD_INIT_M1, (BYTE)(ulHSDI >> 14) & 0xFF);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_43_H_SD_INIT_M_M1, (BYTE)(ulHSDI >> 6) & 0xFF);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_44_H_SD_INIT_L_M_M1, (BYTE)((ulHSDI & 0x3F) << 2));

            // S2 initialphase
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_45_H_SD_INIT_H_M2, (BYTE)(ulHSDI >> 22) & 0x03);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_04_H_SD_INIT_M2, (BYTE)(ulHSDI >> 14) & 0xFF);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_43_H_SD_INIT_M_M2, (BYTE)(ulHSDI >> 6) & 0xFF);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_44_H_SD_INIT_L_M2, (BYTE)((ulHSDI & 0x3F) << 2));

            // HSD extension
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_3A_SD_OUT_EXTENSION_M1, ucDropExtension);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_3A_SD_OUT_EXTENSION_M2, ucDropExtension);
            ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_3A_SD_OUT_EXTENSION_S1, ucDropExtension);
            ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_3A_SD_OUT_EXTENSION_S2, ucDropExtension);
        }
        SET_DROP_EXTENSION_LENGTH(ucDropExtension);
#endif
    }
    else
    {
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_04_H_SD_INIT_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_05_H_SD_FACTOR_H_M1, 0x10);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_06_H_SD_FACTOR_M_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_07_H_SD_FACTOR_L_M1, 0x00);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_04_H_SD_INIT_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_05_H_SD_FACTOR_H_M1, 0x10);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_06_H_SD_FACTOR_M_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_07_H_SD_FACTOR_L_M1, 0x00);
        }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
        {
            // Set Drop Extension
            ucDropExtension = GET_FMTCNV_EXTENSION_LEN();

            if(ucDropExtension > 0x1F)
            {
                ucDropExtension = 0x1F;
            }

            if(ucDropExtension > 0)
            {
                // extension + FIFOWidth must be even number
                if(((pstFIFOScaling->usInputHWidth / 2 + ucDropExtension) % 2) != 0)
                {
                    ucDropExtension -= 1;
                }

#if(_HW_DROP_EXTENSION_GEN != _GEN_NONE)
#if(_HW_DROP_EXTENSION_GEN == _DROP_EXTENSION_GEN_1)
                // Drop Extension Gen1
                // M1/M2 drops extension of DEN END ; S1/S2 drops extension of DEN Start
                ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, ~0x1FU, (ucDropExtension & 0x1F));
                ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, ~0x1FU, (ucDropExtension & 0x1F));
                ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_61_DROP_EXTENSION_START_S1, ~0x1FU, (ucDropExtension & 0x1F));
                ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_61_DROP_EXTENSION_START_S2, ~0x1FU, (ucDropExtension & 0x1F));
#else
#warning "_HW_DROP_EXTENSION_GEN should be modified!!"
#endif
#endif
                // Drop Extension Enable
                ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, ~_BIT7, _BIT7);
                ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, ~_BIT7, _BIT7);
                ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, ~_BIT7, _BIT7);
                ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, ~_BIT7, _BIT7);
            }

            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_04_H_SD_INIT_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_05_H_SD_FACTOR_H_M1, 0x10);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_06_H_SD_FACTOR_M_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_07_H_SD_FACTOR_L_M1, 0x00);

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_04_H_SD_INIT_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_05_H_SD_FACTOR_H_M2, 0x10);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_06_H_SD_FACTOR_M_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_07_H_SD_FACTOR_L_M2, 0x00);

            // HSD extension
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_3A_SD_OUT_EXTENSION_M1, ucDropExtension);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_3A_SD_OUT_EXTENSION_M2, ucDropExtension);
            ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_3A_SD_OUT_EXTENSION_S1, ucDropExtension);
            ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_3A_SD_OUT_EXTENSION_S2, ucDropExtension);
        }
        SET_DROP_EXTENSION_LENGTH(ucDropExtension);
#endif
    }

    if(GET_H_SCALE_DOWN() == _TRUE)
    {
        // Enable H Scale Down
        // M1
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~(_BIT3 | _BIT1), _BIT1);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~(_BIT3 | _BIT1), _BIT1);
        }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
        {
            // S1
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0x8000, ~(_BIT3 | _BIT1), _BIT1);
            // S2
            ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2 + 0x8000, ~(_BIT3 | _BIT1), _BIT1);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Set Vertical Scale Down
// Input Value  : Input/Output H/V Active Region;I-DataPath E/O mode ; Select Page
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetVScalingDown(const StructSDRAMDataInfo *pstFIFOScaling, bit bEvenOdd, WORD usRegPageSel)
{
    bit bShiftOneLineEnable = _FALSE;

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    WORD usEOPage = ScalerScalingGetEOModePageMapping(usRegPageSel);
#endif
    bEvenOdd = bEvenOdd;

#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    bShiftOneLineEnable = ScalerMemoryGetShiftOneLineSupport();

    if(bShiftOneLineEnable == _TRUE)
    {
        SET_MDOMAIN_INPUT_VSTART(0);
    }
#endif

#if(_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE)
    // Set V Scaling Down Factor
    if((GET_MDOMAIN_INPUT_VHEIGHT() > pstFIFOScaling->usInputVHeight) || (bShiftOneLineEnable == _TRUE))
#else
    // Set V Scaling Down Factor
    if(GET_MDOMAIN_INPUT_VHEIGHT() > pstFIFOScaling->usInputVHeight)
#endif
    {
        DWORD ulVSDF = 0;
        DWORD ulVSDI = 0;
        SET_V_SCALE_DOWN();

        // Calculate Scaling Factor
        ulVSDF = GET_DWORD_MUL_DIV((1UL << (_VSD_FACTOR_BIT + 1)), GET_MDOMAIN_INPUT_VHEIGHT(), pstFIFOScaling->usInputVHeight);
        ulVSDF = (ulVSDF + 1) >> 1;

        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_01_V_SD_FACTOR_H_M1, (BYTE)((ulVSDF >> 19) & 0x1F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_02_V_SD_FACTOR_M_M1, (BYTE)((ulVSDF >> 11) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_03_V_SD_FACTOR_L_M1, (BYTE)((ulVSDF >> 3) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_42_V_SD_FACTOR_L1_M1, (BYTE)(((ulVSDF & 0x07) << 5) & 0xE0));

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_01_V_SD_FACTOR_H_M1, (BYTE)((ulVSDF >> 19) & 0x1F));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_02_V_SD_FACTOR_M_M1, (BYTE)((ulVSDF >> 11) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_03_V_SD_FACTOR_L_M1, (BYTE)((ulVSDF >> 3) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_42_V_SD_FACTOR_L1_M1, (BYTE)(((ulVSDF & 0x07) << 5) & 0xE0));
        }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
        {
            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_01_V_SD_FACTOR_H_M1, (BYTE)((ulVSDF >> 19) & 0x1F));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_02_V_SD_FACTOR_M_M1, (BYTE)((ulVSDF >> 11) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_03_V_SD_FACTOR_L_M1, (BYTE)((ulVSDF >> 3) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_42_V_SD_FACTOR_L1_M1, (BYTE)(((ulVSDF & 0x07) << 5) & 0xE0));

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_01_V_SD_FACTOR_H_M2, (BYTE)((ulVSDF >> 19) & 0x1F));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_02_V_SD_FACTOR_M_M2, (BYTE)((ulVSDF >> 11) & 0xFF));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_03_V_SD_FACTOR_L_M2, (BYTE)((ulVSDF >> 3) & 0xFF));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_42_V_SD_FACTOR_L1_M2, (BYTE)(((ulVSDF & 0x07) << 5) & 0xE0));
        }
#endif

        // Calculate Initial Phase
        ulVSDI = (ulVSDF >> 15) - 32;

        if(ulVSDI > 0x7F)
        {
            ulVSDI = 0x7F;
        }
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_00_V_SD_INIT_M1, (BYTE)ulVSDI);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_00_V_SD_INIT_M1, (BYTE)ulVSDI);
        }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
        {
            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_00_V_SD_INIT_M1, (BYTE)ulVSDI);

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_00_V_SD_INIT_M2, (BYTE)ulVSDI);
        }
#endif
    }
    else
    {
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_00_V_SD_INIT_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_01_V_SD_FACTOR_H_M1, 0x02);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_02_V_SD_FACTOR_M_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_03_V_SD_FACTOR_L_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 0x00);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_00_V_SD_INIT_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_01_V_SD_FACTOR_H_M1, 0x02);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_02_V_SD_FACTOR_M_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_03_V_SD_FACTOR_L_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 0x00);
        }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
        {
            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_00_V_SD_INIT_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_01_V_SD_FACTOR_H_M1, 0x02);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_02_V_SD_FACTOR_M_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_03_V_SD_FACTOR_L_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 0x00);

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_00_V_SD_INIT_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_01_V_SD_FACTOR_H_M2, 0x02);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_02_V_SD_FACTOR_M_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_03_V_SD_FACTOR_L_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_42_V_SD_FACTOR_L1_M2, 0x00);
        }
#endif
    }

    if(GET_V_SCALE_DOWN() == _TRUE)
    {
        // Enable V Scale Down
        // M1
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~_BIT0, _BIT0);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        if(bEvenOdd == _TRUE)
        {
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~_BIT0, _BIT0);
        }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
        {
            // S1
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0x8000, ~_BIT0, _BIT0);
            // S2
            ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2 + 0x8000, ~_BIT0, _BIT0);

            // VGIP GEN EXTRA LINE HSTART modify in fb mode
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_46_EXTRA_DEN_SETTING_M1, (HIBYTE(GET_MDOMAIN_INPUT_HSTART() / 2 - 2) & 0x0F));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_47_EXTRA_DEN_SETTING2_M1, (LOBYTE(GET_MDOMAIN_INPUT_HSTART() / 2 - 2) & 0xFF));
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_46_EXTRA_DEN_SETTING_M1, ~_BIT4, _BIT4);

            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_46_EXTRA_DEN_SETTING_M1, (HIBYTE(GET_MDOMAIN_INPUT_HSTART() / 2 - 2) & 0x0F));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_47_EXTRA_DEN_SETTING2_M1, (LOBYTE(GET_MDOMAIN_INPUT_HSTART() / 2 - 2) & 0xFF));
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_46_EXTRA_DEN_SETTING_M1, ~_BIT4, _BIT4);

            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_46_EXTRA_DEN_SETTING_M1, (HIBYTE(GET_MDOMAIN_INPUT_HSTART() / 2 - 2) & 0x0F));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_47_EXTRA_DEN_SETTING2_M1, (LOBYTE(GET_MDOMAIN_INPUT_HSTART() / 2 - 2) & 0xFF));
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_46_EXTRA_DEN_SETTING_M1, ~_BIT4, _BIT4);

            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_46_EXTRA_DEN_SETTING_M2, (HIBYTE(GET_MDOMAIN_INPUT_HSTART() / 2 - 2) & 0x0F));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_47_EXTRA_DEN_SETTING2_M2, (LOBYTE(GET_MDOMAIN_INPUT_HSTART() / 2 - 2) & 0xFF));
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_46_EXTRA_DEN_SETTING_M2, ~_BIT4, _BIT4);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Set Scale Down Window
// Input Value  : Input/Output H/V Active Region;I-DataPath E/O mode ; Select Page
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingDownWindow(const StructSDRAMDataInfo *pstFIFOScaling, bit bEvenOdd, WORD usRegPageSel)
{
    WORD usFIFOWidth = 0;
    WORD usFIFOHeight = 0;
    WORD usEOPage = 0x0000U;

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    usEOPage = ScalerScalingGetEOModePageMapping(usRegPageSel);
#endif
    bEvenOdd = bEvenOdd;

    usFIFOHeight = pstFIFOScaling->usInputVHeight;

#if((_HW_FORMAT_CONVERSION_EO_MODE == _ON) && (_HW_FORMAT_CONVERSION_SUPPORT == _ON))
    // Interlaced mode, Idomain Single Mode
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        usFIFOHeight = usFIFOHeight >> (WORD)bEvenOdd;
    }
#endif

    usFIFOWidth = pstFIFOScaling->usInputHWidth;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
    {
        usFIFOWidth = pstFIFOScaling->usInputHWidth >> 1;
    }
#endif

#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_1)
    // Set HSD Vact Output Ref Input Window
    if(GET_H_SCALE_DOWN() == _TRUE)
    {
        ScalerScalingSetHScalingDownVactRefInputWindow(_ENABLE, bEvenOdd, usRegPageSel, usEOPage);
    }
    if(GET_V_SCALE_DOWN() == _TRUE)
    {
        ScalerScalingSetVScalingDownVactRefInputWindowSelect(_ENABLE, bEvenOdd, usRegPageSel, usEOPage);
    }
#endif

    // Enable SD Out Window Set
    // M1
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_36_SD_OUT_WID_M_M1, (HIBYTE(usFIFOWidth) & 0x1F));
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_37_SD_OUT_WID_L_M1, LOBYTE(usFIFOWidth));

    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_38_SD_OUT_LEN_M_M1, (HIBYTE(usFIFOHeight) & 0x1F));
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_39_SD_OUT_LEN_L_M1, LOBYTE(usFIFOHeight));

    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~_BIT3, 0x00);

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    if(bEvenOdd == _TRUE)
    {
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_36_SD_OUT_WID_M_M1, (HIBYTE(usFIFOWidth) & 0x1F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_37_SD_OUT_WID_L_M1, LOBYTE(usFIFOWidth));

        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_38_SD_OUT_LEN_M_M1, (HIBYTE(usFIFOHeight) & 0x1F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usEOPage, _P0_25_PT_39_SD_OUT_LEN_L_M1, LOBYTE(usFIFOHeight));

        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usEOPage, ~_BIT3, 0x00);
    }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(GET_IDOMAIN_4PATH_STATUS() == _TRUE)
    {
#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_1)
        // Set HSD Vact Output Ref Input Window
        // S1
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0x8000, ~_BIT4, _BIT4);
        // S2
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0xC000, ~_BIT4, _BIT4);
#endif

        // S1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_36_SD_OUT_WID_M_M1, (HIBYTE(usFIFOWidth) & 0x0F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_37_SD_OUT_WID_L_M1, LOBYTE(usFIFOWidth));

        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_38_SD_OUT_LEN_M_M1, (HIBYTE(usFIFOHeight) & 0x0F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_39_SD_OUT_LEN_L_M1, LOBYTE(usFIFOHeight));

        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0x8000, ~_BIT3, 0x00);

        // S2
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_36_SD_OUT_WID_M_M2, (HIBYTE(usFIFOWidth) & 0x0F));
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_37_SD_OUT_WID_L_M2, LOBYTE(usFIFOWidth));

        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_38_SD_OUT_LEN_M_M2, (HIBYTE(usFIFOHeight) & 0x0F));
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_39_SD_OUT_LEN_L_M2, LOBYTE(usFIFOHeight));

        ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2 + 0x8000, ~_BIT3, 0x00);
    }
#endif
}

//--------------------------------------------------
// Description  : Get fifo scaling size
// Input Value  : Input/Output H/V Active Region
// Output Value : _FAIL /_SUCCESS
//--------------------------------------------------
bit ScalerScalingGetFIFOScalingSize(StructSDRAMDataInfo *pstData)
{
    // Update fifo scaling size
    ScalerScalingUpdateFIFOScalingSize(pstData);

#if(_FRC_SUPPORT == _ON)
    // Check HSD Ratio
    if((GET_MDOMAIN_INPUT_HWIDTH() > pstData->usInputHWidth) &&
       (GET_MDOMAIN_OUTPUT_HWIDTH() > pstData->usInputHWidth))
    {
        if(pstData->usInputHWidth > 0)
        {
            if((GET_MDOMAIN_INPUT_HWIDTH() / pstData->usInputHWidth) > _HW_HSD_MAX_RATIO)
            {
                DebugMessageFRC("Fail : HSD > Max HSD Ratio", pstData->usInputHWidth);
                return _FAIL;
            }
        }
        else
        {
            DebugMessageFRC("Fail : Hwidht = 0", pstData->usInputHWidth);
            return _FAIL;
        }
    }

    SET_FIFO_INPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH(), pstData->usInputHWidth);
    SET_FIFO_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH(), pstData->usOutputHWidth);

    // Clear Mdomain Bandwidth
    CLR_PATH_MEMORY_BW_CONFIG(GET_MDOMAIN_INPUT_DATA_PATH());

    if(GET_MEMORY_WORK_TYPE() == _MEMORY_WORK_MODE)
    {
        // get mdomain input pixel clk
        PDATA_DWORD(0) = (DWORD)GET_MDOMAIN_INPUT_HFREQ() * GET_MDOMAIN_INPUT_HTOTAL() / 10; // kHz

        // get frc real-used bw
        PDATA_DWORD(0) = ScalerFRCBWCalUsage(GET_FIFO_INPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH()), GET_FIFO_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH()), GET_MEMORY_DATA_BIT(), GET_IMG_CMP_PARAM(), PDATA_DWORD(0), GET_MDOMAIN_INPUT_DATA_PATH(), _FALSE);
#if(_COLOR_IP_3DDI == _ON)
        if((GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON) && (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2))
        {
            PDATA_DWORD(0) += Scaler3DDICalMaxMemoryBW();
        }
#endif
        // Set using bandwidth
        SET_MEMORY_BW(GET_MDOMAIN_INPUT_DATA_PATH(), PDATA_DWORD(0));
    }

    ScalerFRCUpdateCurrentBW();
#else
    SET_FIFO_INPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH(), pstData->usInputHWidth);
    SET_FIFO_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH(), pstData->usOutputHWidth);
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
    ScalerScalingUpdatePBPTopDVHeight(pstData);
#endif

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Set Scale Up Initial
// Input Value  : Select PagedAddr
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingUpInitial(WORD usRegPagedAddrSel)
{
    usRegPagedAddrSel = usRegPagedAddrSel;

    // Disable Scale Up
    ScalerSetBit(ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN()), ~(_BIT5 | _BIT1 | _BIT0), _BIT5);

#if(_SHARPNESS_FUNCTION == _OFF)
    // Disable Scale Up FixCoef
    ScalerSetDataPortBit(ScalerDDomainGetScalingFactorPageAddr(GET_MDOMAIN_OUTPUT_RGN()), _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~(_BIT7 | _BIT6), 0x00);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Ddomain FB mode
    if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
    {
        ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, ~(_BIT5 | _BIT1 | _BIT0), _BIT5);

#if(_SHARPNESS_FUNCTION == _OFF)
        ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~(_BIT7 | _BIT6), 0x00);
#endif
    }
#endif
}

//--------------------------------------------------
// Description  : Set Vertical Scale Up
// Input Value  : Input/Output H/V Active Region;I-DataPath E/O mode ; Select Page
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetVScalingUp(const StructSDRAMDataInfo *pstFIFOScaling, WORD usRegPagedAddrSel)
{
    bit bVideo_Compensation = _FALSE;

    if(pstFIFOScaling->usOutputVHeight < GET_MDOMAIN_OUTPUT_VHEIGHT())
    {
        DWORD ulVSUF = 0;
        BYTE ucVSUI = 0;
        SET_V_SCALE_UP();

        // Calculate Scaling Factor
        ulVSUF = GET_DWORD_MUL_DIV((1UL << (_VSU_FACTOR_BIT + 1)), pstFIFOScaling->usOutputVHeight, GET_MDOMAIN_OUTPUT_VHEIGHT());
        ulVSUF = (ulVSUF + 1) >> 1;

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_03_VER_SCALE_FACTOR_H_R1_ACTIVE1, ((ulVSUF >> 16) & 0x0F));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_04_VER_SCALE_FACTOR_M_R1_ACTIVE1, ((ulVSUF >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_05_VER_SCALE_FACTOR_L_R1_ACTIVE1, (ulVSUF & 0xFF));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_03_VER_SCALE_FACTOR_H_R1_ACTIVE1, ((ulVSUF >> 16) & 0x0F));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_04_VER_SCALE_FACTOR_M_R1_ACTIVE1, ((ulVSUF >> 8) & 0xFF));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_05_VER_SCALE_FACTOR_L_R1_ACTIVE1, (ulVSUF & 0xFF));
        }
#endif
        // Set V Initial Phase(total accuracy 0.20), and keep MSB 8bits accuracy
        // ideal initial phase: for 4line SU = (1+SUF)/2 * 2^8 = (1+SUF)*16*8
        PDATA_DWORD(0) = (DWORD)(pstFIFOScaling->usOutputVHeight + GET_MDOMAIN_OUTPUT_VHEIGHT()) * 16 * 8 / GET_MDOMAIN_OUTPUT_VHEIGHT();
        ucVSUI = (BYTE)PDATA_DWORD(0);

        // 1080i->1080P  no video compensation
        if((GET_MDOMAIN_INPUT_INTERLACE_FLG() == _FALSE) ||
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
           (ScalerRotationCheckVerticalStatus() == _TRUE) ||
#endif
#if(_VGA_SUPPORT == _ON)
           (ScalerFmtCnvGetSourceType(GET_MDOMAIN_INPUT_DATA_PATH()) == _FC_SOURCE_ADC) ||
#endif
#if(_COLOR_IP_3DDI == _ON)
           (GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON) ||
#endif
           (GET_PANEL_BYPASS_INTERLACE_COMPENSATION(pstFIFOScaling->usOutputVHeight, GET_MDOMAIN_OUTPUT_VHEIGHT()) == _TRUE))
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_11_VER_FILTER_COEF_INI_R1_ACTIVE1, ucVSUI);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
            {
                ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_11_VER_FILTER_COEF_INI_R1_ACTIVE1, ucVSUI);
            }
#endif
        }
        else
        {
            // interlace mode :initial phase + 0.25(0x40)
            if(ucVSUI > 0xBF)
            {
                ucVSUI = 0xFF;
            }
            else
            {
                ucVSUI += 0x40;
            }

            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_11_VER_FILTER_COEF_INI_R1_ACTIVE1, ucVSUI);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
            {
                ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_11_VER_FILTER_COEF_INI_R1_ACTIVE1, ucVSUI);
            }
#endif
        }
    }
    else
    {
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_03_VER_SCALE_FACTOR_H_R1_ACTIVE1, 0x0F);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_04_VER_SCALE_FACTOR_M_R1_ACTIVE1, 0xFF);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_05_VER_SCALE_FACTOR_L_R1_ACTIVE1, 0xFF);

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_11_VER_FILTER_COEF_INI_R1_ACTIVE1, 0xFF);

#if(_SHARPNESS_FUNCTION == _OFF)
        // Enable V Scale Up FixCoef
        ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~_BIT6, _BIT6);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_03_VER_SCALE_FACTOR_H_R1_ACTIVE1, 0x0F);
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_04_VER_SCALE_FACTOR_M_R1_ACTIVE1, 0xFF);
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_05_VER_SCALE_FACTOR_L_R1_ACTIVE1, 0xFF);

            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_11_VER_FILTER_COEF_INI_R1_ACTIVE1, 0xFF);

#if(_SHARPNESS_FUNCTION == _OFF)
            ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~_BIT6, _BIT6);
#endif
        }
#endif
    }

    if(GET_V_SCALE_UP() == _TRUE)
    {
        // Enable V Scale Up
        ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
        }
#endif
        if(GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE)
        {
            // VGA Input or Prefered Timing
            bVideo_Compensation = (GET_PANEL_BYPASS_INTERLACE_COMPENSATION(pstFIFOScaling->usOutputVHeight, GET_MDOMAIN_OUTPUT_VHEIGHT()) == _TRUE);
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
            bVideo_Compensation |= (ScalerRotationCheckVerticalStatus() == _TRUE);
#endif
#if(_VGA_SUPPORT == _ON)
            bVideo_Compensation |= (ScalerFmtCnvGetSourceType(GET_MDOMAIN_INPUT_DATA_PATH()) == _FC_SOURCE_ADC);
#endif

#if(_COLOR_IP_3DDI == _ON)
            bVideo_Compensation |= (GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE);
#endif

            if(bVideo_Compensation == _TRUE)
            {
                // Disable Video Compensation
                ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel, ~(_BIT7 | _BIT5), _BIT5);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
                {
                    ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, ~(_BIT7 | _BIT5), _BIT5);
                }
#endif
            }
            else
            {
                // Enable Video Compensation According to Odd Field Delay One Line
                ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
                {
                    ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
                }
#endif
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
                // Check video compensation polarity for rotation
                ScalerRotationCheckVideoCompensation();
#endif
            }
        }
        else
        {
            // Disable Video Compensation
            ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel, ~(_BIT7 | _BIT5), _BIT5);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
            {
                ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, ~(_BIT7 | _BIT5), _BIT5);
            }
#endif
        }
    }
    else
    {
        // Disable Video Compensation
        ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel, ~(_BIT7 | _BIT5), _BIT5);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, ~(_BIT7 | _BIT5), _BIT5);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Set Horizontal Scale Up
// Input Value  : Input/Output H/V Active Region; Select Page
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetHScalingUp(const StructSDRAMDataInfo *pstFIFOScaling, WORD usRegPagedAddrSel)
{
    SET_H_SCALE_UP();

    if(pstFIFOScaling->usOutputHWidth < GET_MDOMAIN_OUTPUT_HWIDTH())
    {
        DWORD ulHSUF = 0;
        DWORD ulHSUI = 0;

        // Calculate Scaling Factor & Set HSUF
        ulHSUF = GET_DWORD_MUL_DIV((1UL << (_HSU_FACTOR_BIT + 1)), pstFIFOScaling->usOutputHWidth, GET_MDOMAIN_OUTPUT_HWIDTH());
        ulHSUF = (ulHSUF + 1) >> 1;

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_00_HOR_SCALE_FACTOR_H_R1_ACTIVE1, (BYTE)((ulHSUF >> 16) & 0x0F));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_01_HOR_SCALE_FACTOR_M_R1_ACTIVE1, (BYTE)((ulHSUF >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_02_HOR_SCALE_FACTOR_L_R1_ACTIVE1, (BYTE)(ulHSUF & 0xFF));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // F/B mode Set Back Region HSUF
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_00_HOR_SCALE_FACTOR_H_R1_ACTIVE1, (BYTE)((ulHSUF >> 16) & 0x0F));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_01_HOR_SCALE_FACTOR_M_R1_ACTIVE1, (BYTE)((ulHSUF >> 8) & 0xFF));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_02_HOR_SCALE_FACTOR_L_R1_ACTIVE1, (BYTE)(ulHSUF & 0xFF));
        }
#endif
        // Set H Initial Phase(total accuracy: 2.20)
        // ideal initial phase = (1+SUF)/2 * 2^8 = (1+R)*16*8 keep LSB8 bit
        ulHSUI = (DWORD)(pstFIFOScaling->usOutputHWidth + GET_MDOMAIN_OUTPUT_HWIDTH()) * 16 * 8 / GET_MDOMAIN_OUTPUT_HWIDTH();

        ScalerScalingSetHScalingUpInitialPhase(usRegPagedAddrSel, ((ulHSUI << 12) & 0xFF000));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // F/B mode: set extension, back initial phase
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            BYTE ucDDomainExtension = 0;

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_TB)
            {
                // When recap_ext calculate, Ddomain_ext has been decided.
                ucDDomainExtension = GET_DDOMAIN_EXTENSION_LEN();
            }
            else
#endif
            {
                // Ddomain_ext = recap_ext / HSUF
                ucDDomainExtension = (BYTE)((((DWORD)GET_MDOMAIN_OUTPUT_HWIDTH() * GET_MDOMAIN_EXT_RECAP_EXTENSION_LEN() << 1) / pstFIFOScaling->usOutputHWidth + 1) >> 1);
                SET_DDOMAIN_EXTENSION_LEN(ucDDomainExtension);
            }

            // back initial phase = FrontInitialPhase + InExtension for each OutExtension*SUFactor
            ulHSUI = (ulHSUI << 12) + ((DWORD)GET_MDOMAIN_EXT_RECAP_EXTENSION_LEN() << 20) - ucDDomainExtension * ulHSUF;

            ScalerScalingSetHScalingUpInitialPhase(usRegPagedAddrSel + 0xC000, ulHSUI);
        }
#endif
    }
    else
    {
        // 1:1 set HSUF == 0xFFFFF, HSUI == 0xFF000
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_00_HOR_SCALE_FACTOR_H_R1_ACTIVE1, 0x0F);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_01_HOR_SCALE_FACTOR_M_R1_ACTIVE1, 0xFF);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_02_HOR_SCALE_FACTOR_L_R1_ACTIVE1, 0xFF);

        // Set Back HSUI
        ScalerScalingSetHScalingUpInitialPhase(usRegPagedAddrSel, 0xFFFF0);
#if(_SHARPNESS_FUNCTION == _OFF)
        // Enable H Scale Up FixCoef
        ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~_BIT7, _BIT7);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // F/B mode: set extension, back HSUF,HSUI
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            // SU 1:1 case Set D-domain Extension == recap Extension
            SET_DDOMAIN_EXTENSION_LEN(GET_MDOMAIN_EXT_RECAP_EXTENSION_LEN());

            // Set Back HSUF
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_00_HOR_SCALE_FACTOR_H_R1_ACTIVE1, 0x0F);
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_01_HOR_SCALE_FACTOR_M_R1_ACTIVE1, 0xFF);
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_02_HOR_SCALE_FACTOR_L_R1_ACTIVE1, 0xFF);

            // Set Back HSUI
            ScalerScalingSetHScalingUpInitialPhase(usRegPagedAddrSel + 0xC000, 0xFFFF0);

#if(_SHARPNESS_FUNCTION == _OFF)
            // Back Region Enable H Scale Up FixCoef
            ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~_BIT7, _BIT7);
#endif
        }
        else
        {
            ScalerScalingSetHScalingUpInitialPhase(usRegPagedAddrSel + 0xC000, 0xFFFF0);
        }
#endif
    }

    //===============================
    // Set H direction scaling up
    //===============================
    if(GET_H_SCALE_UP() == _TRUE)
    {
        // Enable H Scale Up
        ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            ScalerSetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usRegPagedAddrSel + 0xC000, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
        }
#endif
    }
}
//--------------------------------------------------
// Description  : Set Horizontal Scale Up
// Input Value  : Input/Output H/V Active Region; Select Page
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetHScalingUpInitialPhase(WORD usRegPagedAddrSel, DWORD ulHSUI)
{
#if(_HW_SCALING_UP_HSUI_GEN_TYPE == _SU_HSUI_GEN_0)
    // HSUI: 22bit
    ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_18_HOR_FILTER_COEF_INI_H_R1_ACTIVE1, ~(_BIT7 | _BIT6), (BYTE)(((ulHSUI >> 20) & 0x03) << 6));
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_10_HOR_FILTER_COEF_INI_R1_ACTIVE1, (BYTE)((ulHSUI >> 12) & 0xFF));
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_14_HOR_FILTER_COEF_INI_M_R1_ACTIVE1, (BYTE)((ulHSUI >> 4) & 0xFF));
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_15_HOR_FILTER_COEF_INI_L_R1_ACTIVE1, (BYTE)((ulHSUI & 0x0F) << 4));
#else
    // HSUI: 20bit
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_10_HOR_FILTER_COEF_INI_R1_ACTIVE1, (BYTE)((ulHSUI >> 12) & 0xFF));
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_14_HOR_FILTER_COEF_INI_M_R1_ACTIVE1, (BYTE)((ulHSUI >> 4) & 0xFF));
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_15_HOR_FILTER_COEF_INI_L_R1_ACTIVE1, (BYTE)((ulHSUI & 0x0F) << 4));
#endif
}
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Extension DDomain related setting
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetDDomainExtension(void)
{
    if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
    {
        bit bDDomainDBStatus = _FALSE;

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV))
        // backup ddomain db status for P24_30_EXTENSION_EXTRA_WIN, DTG db only control 0x002A, 0x002B
        bDDomainDBStatus = ScalerGlobalGetDDomainDBStatus();
#endif
        if(bDDomainDBStatus == _FALSE)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        }
        // SET DTG Extension
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_FRONT, ~0xFFU, ((BYTE)(GET_DDOMAIN_EXTENSION_LEN()) & 0xFF));
        ScalerSetDataPortBit(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1F_DISPLAY_EXTENSION_FB_BACK, ~0xFFU, ((BYTE)(GET_DDOMAIN_EXTENSION_LEN()) & 0xFF));

        // Set D-domain PIPBlending extension extract
        ScalerSetBit(P24_30_EXTENSION_EXTRA_WIN, ~_BIT0, ((GET_DDOMAIN_EXTENSION_LEN() != 0) ? _BIT0 : 0x00));
        ScalerSetBit(P5A_30_EXTENSION_EXTRA_WIN_BACK, ~_BIT0, ((GET_DDOMAIN_EXTENSION_LEN() != 0) ? _BIT0 : 0x00));

        // Display Conversion Extension
        ScalerSetByte(P39_1E_DISP_TIMING_CTRL0, GET_DDOMAIN_EXTENSION_LEN());

        // OSD extension
        ScalerOsdSetExtension(GET_DDOMAIN_EXTENSION_LEN());
    }
}
#endif

//--------------------------------------------------
// Description  : Scaling Up Using Bypass Table
// Input Value  : DisplayRegion; _Enable:Using bypass table, _DISABLE: Using Normal Table
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingUpBypassTable(EnumDDomainRegion enumDDomainRegion, bit bEnable, EnumDBApply enumDBApply)
{
    WORD usRegPagedAddrSel = 0x00;

    if(enumDDomainRegion == _DDOMAIN_RGN_ALL)
    {
        usRegPagedAddrSel = _REG_MAIN1_PAGE;
    }
    else
    {
        switch(enumDDomainRegion)
        {
#if(_HW_D_DOMAIN_R1_A1_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R1_A1:
                usRegPagedAddrSel = _REG_MAIN1_PAGE;
                break;
#endif

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R1_A2:
                usRegPagedAddrSel = _REG_MAIN1_PAGE + _A1A2_REG_ADDR_OFFSET;
                break;
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R2_A1:
                usRegPagedAddrSel = _REG_SUB1_PAGE;
                break;
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R2_A2:
                usRegPagedAddrSel = _REG_SUB1_PAGE + _A1A2_REG_ADDR_OFFSET;
                break;
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R3_A1:
                usRegPagedAddrSel = _REG_SUB2_PAGE;
                break;
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
            case _DDOMAIN_RGN_R3_A2:
                usRegPagedAddrSel = _REG_SUB2_PAGE + _A1A2_REG_ADDR_OFFSET;
                break;
#endif

            default:
                break;
        }
    }
    ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usRegPagedAddrSel, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~(_BIT7 | _BIT6), ((bEnable == _ENABLE) ? (_BIT7 | _BIT6) : 0x00));

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Extension Recapture setting
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetExtensionRecapture(WORD usMdmInputHWidth, WORD usMdmInputVHeight)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE)
    {
        return;
    }

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
#endif
            if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1)
            {
                BYTE ucExtensionRecaptureLen = ScalerScalingCalculateExtensionRecaptureExtNum(usMdmInputHWidth);

                // Set A1 Extension Width
                ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, ucExtensionRecaptureLen);
                SET_EXT_RECAP_EXTENSION_LEN_A1(ucExtensionRecaptureLen);

                // Set A1 FIFO Width
                ScalerSetByte(P92_81_SRC_A1_WIDTH_MSB, (HIBYTE(usMdmInputHWidth / 2) & 0x1F));
                ScalerSetByte(P92_82_SRC_A1_WIDTH_LSB, LOBYTE(usMdmInputHWidth / 2));
                ScalerSetByte(P92_83_SRC_A1_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                ScalerSetByte(P92_84_SRC_A1_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                // Set Extension mode
                ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), 0x00);
            }
            break;


#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
        {
            WORD usExtensionRecaptureLen = 0;
            BYTE ucDdmExtensionLen = ScalerGetDataPortSingleByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_FRONT);

            if(ucDdmExtensionLen == 0)
            {
                WORD usMaxDExtensionLen = 0;
                WORD usHFrontPorch = 0;
                BYTE ucDExtensionLimit = 0;

                // Get DDomain HPorch & Extension Recapture Length
                usHFrontPorch = ((ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL)) / 2) - (GET_MDOMAIN_OUTPUT_HBWIDTH() / 2) - (GET_MDOMAIN_OUTPUT_HSTART() / 4);
                usMaxDExtensionLen = usHFrontPorch - _DDOMAIN_MIN_HFRONT_PORCH_SIZE;

                // For Application, Maximum of DDomain Extension is 31.(800x600 to 8192x430)
                if(usMaxDExtensionLen >= _DDOMAIN_MAX_EXTENSION)
                {
                    ucDExtensionLimit = _DDOMAIN_MAX_EXTENSION;
                }
                else
                {
                    ucDExtensionLimit = LOBYTE(usMaxDExtensionLen);
                }
                SET_DDOMAIN_EXTENSION_LEN(ucDExtensionLimit);
            }
            else
            {
                SET_DDOMAIN_EXTENSION_LEN(ucDdmExtensionLen);
            }

            if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1)
            {
                // Set A1 Extension Width
                usExtensionRecaptureLen = GET_DWORD_MUL_DIV(GET_DDOMAIN_EXTENSION_LEN(), usMdmInputHWidth, GET_MDOMAIN_OUTPUT_HWIDTH());
                ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, usExtensionRecaptureLen);
                SET_EXT_RECAP_EXTENSION_LEN_A1(usExtensionRecaptureLen);

                // Set A1 FIFO Width
                ScalerSetByte(P92_81_SRC_A1_WIDTH_MSB, (HIBYTE(usMdmInputHWidth / 2) & 0x1F));
                ScalerSetByte(P92_82_SRC_A1_WIDTH_LSB, LOBYTE(usMdmInputHWidth / 2));
                ScalerSetByte(P92_83_SRC_A1_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                ScalerSetByte(P92_84_SRC_A1_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                // Set Extension mode
                ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), 0x00);
            }
            else if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A2)
            {
                // Set A2 Extension Width
                usExtensionRecaptureLen = GET_DWORD_MUL_DIV(GET_DDOMAIN_EXTENSION_LEN(), usMdmInputHWidth, GET_MDOMAIN_OUTPUT_HWIDTH());
                ScalerSetByte(P92_90_EXTENSION_WIDTH_A2, usExtensionRecaptureLen);
                SET_EXT_RECAP_EXTENSION_LEN_A2(usExtensionRecaptureLen);

                // Set A2 FIFO Width
                ScalerSetByte(P92_8C_SRC_A2_WIDTH_MSB, (HIBYTE(usMdmInputHWidth / 2) & 0x1F));
                ScalerSetByte(P92_8D_SRC_A2_WIDTH_LSB, LOBYTE(usMdmInputHWidth / 2));
                ScalerSetByte(P92_8E_SRC_A2_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                ScalerSetByte(P92_8F_SRC_A2_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                // Set Extension mode
                ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), 0x00);
            }
            break;
        }
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1)
            {
                WORD usMovingLen = ScalerScalingGetExtRecapMovingLength(usMdmInputHWidth);

                if(ScalerDDomainGetPbplrFullStatus() == _TRUE) // full
                {
                    BYTE ucExtensionRecaptureLen = ScalerScalingCalculateExtensionRecaptureExtNum(usMdmInputHWidth);

                    // Set A1 Extension Width
                    ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, ucExtensionRecaptureLen);
                    SET_EXT_RECAP_EXTENSION_LEN_A1(ucExtensionRecaptureLen);

                    // Set A1 FIFO Width
                    ScalerSetByte(P92_81_SRC_A1_WIDTH_MSB, (HIBYTE(usMdmInputHWidth / 2) & 0x1F));
                    ScalerSetByte(P92_82_SRC_A1_WIDTH_LSB, LOBYTE(usMdmInputHWidth / 2));
                    ScalerSetByte(P92_83_SRC_A1_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                    ScalerSetByte(P92_84_SRC_A1_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                    // Set Moving Length
                    ScalerSetByte(P92_86_SRC_A1_MOVING_MSB, (HIBYTE(usMovingLen) & 0x1F));
                    ScalerSetByte(P92_87_SRC_A1_MOVING_LSB, LOBYTE(usMovingLen));
                    SET_EXT_RECAP_MOVING_LEN(usMovingLen);

                    // Set Extension mode
                    ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), 0x00);
                }
                else
                {
                    if(ScalerScalingGetPBPLRSingleRegionStatus(GET_MDOMAIN_OUTPUT_HSTART(), GET_MDOMAIN_OUTPUT_HWIDTH()) == _TRUE)
                    {
                        // All of Active is in R1a1, without R3a1
                        // Set A1 Extension Width
                        ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, 0);
                        SET_EXT_RECAP_EXTENSION_LEN_A1(0);
                    }
                    else
                    {
                        BYTE ucExtensionRecaptureLen = ScalerScalingCalculateExtensionRecaptureExtNum(usMdmInputHWidth);

                        // Check Extension Recapture HW Limit
                        if(((usMdmInputHWidth / 2) - usMovingLen) < _FB_PBPLR_MINIMUM_LEN)
                        {
                            DebugMessageScaler("Warning: PBP LR Ratio is too close, Please Modify usStep of UserInterfaceDisplayGetPbpTimingFormat to increase LR Ratio!", usMovingLen);
                        }

                        // Active is included R1a1 & R3a1
                        // Set A1 Extension Width
                        ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, ucExtensionRecaptureLen);
                        SET_EXT_RECAP_EXTENSION_LEN_A1(ucExtensionRecaptureLen);
                    }

                    // Set A1 FIFO Width
                    ScalerSetByte(P92_81_SRC_A1_WIDTH_MSB, (HIBYTE(usMdmInputHWidth / 2) & 0x1F));
                    ScalerSetByte(P92_82_SRC_A1_WIDTH_LSB, LOBYTE(usMdmInputHWidth / 2));
                    ScalerSetByte(P92_83_SRC_A1_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                    ScalerSetByte(P92_84_SRC_A1_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                    // Set Moving Length
                    ScalerSetByte(P92_86_SRC_A1_MOVING_MSB, (HIBYTE(usMovingLen) & 0x1F));
                    ScalerSetByte(P92_87_SRC_A1_MOVING_LSB, LOBYTE(usMovingLen));
                    SET_EXT_RECAP_MOVING_LEN(usMovingLen);

                    // Set Left Larger Mode
                    ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), _BIT5);
                }
            }
            break;

        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1)
            {
                WORD usMovingLen = ScalerScalingGetExtRecapMovingLength(usMdmInputHWidth);

                if(ScalerDDomainGetPbplrFullStatus() == _TRUE)
                {
                    BYTE ucExtensionRecaptureLen = ScalerScalingCalculateExtensionRecaptureExtNum(usMdmInputHWidth);

                    // Set A1 Extension Width
                    ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, ucExtensionRecaptureLen);
                    SET_EXT_RECAP_EXTENSION_LEN_A1(ucExtensionRecaptureLen);

                    // Set A1 FIFO Width
                    ScalerSetByte(P92_81_SRC_A1_WIDTH_MSB, (HIBYTE(usMdmInputHWidth / 2) & 0x1F));
                    ScalerSetByte(P92_82_SRC_A1_WIDTH_LSB, LOBYTE(usMdmInputHWidth / 2));
                    ScalerSetByte(P92_83_SRC_A1_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                    ScalerSetByte(P92_84_SRC_A1_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                    // Set Moving Length
                    ScalerSetByte(P92_86_SRC_A1_MOVING_MSB, (HIBYTE(usMovingLen) & 0x1F));
                    ScalerSetByte(P92_87_SRC_A1_MOVING_LSB, LOBYTE(usMovingLen));
                    SET_EXT_RECAP_MOVING_LEN(usMovingLen);


                    // Set Extension mode
                    ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), 0x00);
                }
                else
                {
                    if(ScalerScalingGetPBPLRSingleRegionStatus(GET_MDOMAIN_OUTPUT_HSTART(), GET_MDOMAIN_OUTPUT_HWIDTH()) == _TRUE)
                    {
                        // Set A1 Extension Width
                        ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, 0);
                        SET_EXT_RECAP_EXTENSION_LEN_A1(0);
                    }
                    else
                    {
                        BYTE ucExtensionRecaptureLen = ScalerScalingCalculateExtensionRecaptureExtNum(usMdmInputHWidth);

                        // Check Extension Recapture HW Limit
                        if(((usMdmInputHWidth / 2) - usMovingLen) < _FB_PBPLR_MINIMUM_LEN)
                        {
                            DebugMessageScaler("Warning: PBP LR Ratio is too close, Please Modify usStep of UserInterfaceDisplayGetPbpTimingFormat to increase LR Ratio!", usMovingLen);
                        }

                        // Set A1 Extension Width
                        ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, ucExtensionRecaptureLen);
                        SET_EXT_RECAP_EXTENSION_LEN_A1(ucExtensionRecaptureLen);
                    }
                    // Set A1 FIFO Width
                    ScalerSetByte(P92_81_SRC_A1_WIDTH_MSB, (HIBYTE(usMdmInputHWidth / 2) & 0x1F));
                    ScalerSetByte(P92_82_SRC_A1_WIDTH_LSB, LOBYTE(usMdmInputHWidth / 2));
                    ScalerSetByte(P92_83_SRC_A1_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                    ScalerSetByte(P92_84_SRC_A1_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                    // Set Moving Length
                    ScalerSetByte(P92_86_SRC_A1_MOVING_MSB, (HIBYTE(usMovingLen) & 0x1F));
                    ScalerSetByte(P92_87_SRC_A1_MOVING_LSB, LOBYTE(usMovingLen));
                    SET_EXT_RECAP_MOVING_LEN(usMovingLen);


                    // Set Right Larger Mode
                    ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), _BIT4);
                }
            }
            break;

        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_B:
            if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A2)
            {
                BYTE ucExtensionRecaptureLen = ScalerScalingCalculateExtensionRecaptureExtNum(usMdmInputHWidth);

                // Set A2 Extension Width
                ScalerSetByte(P92_90_EXTENSION_WIDTH_A2, ucExtensionRecaptureLen);
                SET_EXT_RECAP_EXTENSION_LEN_A2(ucExtensionRecaptureLen);

                // Set A2 FIFO Width
                ScalerSetByte(P92_8C_SRC_A2_WIDTH_MSB, (HIBYTE(usMdmInputHWidth / 2) & 0x1F));
                ScalerSetByte(P92_8D_SRC_A2_WIDTH_LSB, LOBYTE(usMdmInputHWidth / 2));
                ScalerSetByte(P92_8E_SRC_A2_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                ScalerSetByte(P92_8F_SRC_A2_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                // Set Extension mode
                ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), 0x00);
            }
            else if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1)
            {
                // Set A1 FIFO Width
                ScalerSetByte(P92_81_SRC_A1_WIDTH_MSB, (HIBYTE(usMdmInputHWidth) & 0x1F));
                ScalerSetByte(P92_82_SRC_A1_WIDTH_LSB, LOBYTE(usMdmInputHWidth));
                ScalerSetByte(P92_83_SRC_A1_HEIGHT_MSB, (HIBYTE(usMdmInputVHeight) & 0x1F));
                ScalerSetByte(P92_84_SRC_A1_HEIGHT_LSB, LOBYTE(usMdmInputVHeight));

                // Set Extension mode
                ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT5 | _BIT4), 0x00);
            }
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
#endif
        default:
            break;
    }
}
//--------------------------------------------------
// Description  : Extension Recapture Enable
// Input Value  : bEn
// Output Value : none
//--------------------------------------------------
BYTE ScalerScalingCalculateExtensionRecaptureExtNum(WORD usMdmInputHWidth)
{
    BYTE ucDExt = 0;
    WORD usBGHWidth = GET_MDOMAIN_OUTPUT_HBWIDTH();
    WORD usBGHStart = GET_MDOMAIN_OUTPUT_HBSTART();
    DWORD ulExtLimit = 0;
    DWORD ulHFrontporch = (DWORD)(GET_MDOMAIN_OUTPUT_HTOTAL() - usBGHStart / 2 - usBGHWidth) / 2;

    // Check Maximum Ddomain Extension Could Be Set
    ulExtLimit = ulHFrontporch - _DDOMAIN_MIN_HFRONT_PORCH_SIZE;

    // Calculate Extension Before Scaling Up
    ulExtLimit = ulExtLimit * usMdmInputHWidth / GET_MDOMAIN_OUTPUT_HWIDTH();

    // Check Extension Before Scaling Up Should not larger than _DDOMAIN_IN_EXTENSION_DEFAULT.
    if(ulExtLimit >= _DDOMAIN_IN_EXTENSION_DEFAULT)
    {
        ulExtLimit = _DDOMAIN_IN_EXTENSION_DEFAULT;
    }

    // Calculate Extension After Scaling Up
    ucDExt = ulExtLimit * GET_MDOMAIN_OUTPUT_HWIDTH() / usMdmInputHWidth;

    // Calculate Extension After Scaling Up Should not larger than _DDOMAIN_EXTENSION_MAX.
    if(ucDExt >= _DDOMAIN_MAX_EXTENSION)
    {
        ulExtLimit = _DDOMAIN_MAX_EXTENSION * usMdmInputHWidth / GET_MDOMAIN_OUTPUT_HWIDTH();
    }

    if(((usMdmInputHWidth / 2 + ulExtLimit) % 2) != 0)
    {
        ulExtLimit -= 1;
    }

    return (BYTE)ulExtLimit;
}
//--------------------------------------------------
// Description  : Extension Recapture Enable
// Input Value  : bEn
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetExtensionRecaptureEnable(EnumDDomainRegion enumDDomainRegion, bit bEn)
{
    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif
            if(enumDDomainRegion == _DDOMAIN_RGN_R1_A1)
            {
                ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT7 | _BIT1), ((bEn == _ENABLE) ? (_BIT7 | _BIT1) : 0x00));
            }
            break;

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_B:
            if(enumDDomainRegion == _DDOMAIN_RGN_R1_A2)
            {
                ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT7 | _BIT0), ((bEn == _ENABLE) ? (_BIT7 | _BIT0) : 0x00));
            }
            else if(enumDDomainRegion == _DDOMAIN_RGN_R1_A1)
            {
                ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT2 | _BIT1), ((bEn == _ENABLE) ? (_BIT2 | _BIT1) : 0x00));
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            if(enumDDomainRegion == _DDOMAIN_RGN_R1_A2)
            {
                // Check A1 Extension Recapture Enable Status
                if(ScalerGetBit(P92_80_DISP_EXT_RECAP_CTRL, _BIT1) == _BIT1)
                {
                    ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~_BIT0, (bEn == _ENABLE) ? _BIT0 : 0x00);
                }
                else
                {
                    ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT7 | _BIT0), ((bEn == _ENABLE) ? (_BIT7 | _BIT0) : 0x00));
                }
            }
            else if(enumDDomainRegion == _DDOMAIN_RGN_R1_A1)
            {
                // Check A2 Extension Recapture Enable Status
                if(ScalerGetBit(P92_80_DISP_EXT_RECAP_CTRL, _BIT0) == _BIT0)
                {
                    ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~_BIT1, (bEn == _ENABLE) ? _BIT1 : 0x00);
                }
                else
                {
                    ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT7 | _BIT1), ((bEn == _ENABLE) ? (_BIT7 | _BIT1) : 0x00));
                }
            }
            break;

#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
#endif
        default:
            ScalerSetBit(P92_80_DISP_EXT_RECAP_CTRL, ~(_BIT7 | _BIT1 | _BIT0), 0x00);
            break;
    }
}
//--------------------------------------------------
// Description  : Extension Recapture Initial
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetExtensionRecaptureInitial(void)
{
    // Initial Extension Recpature Setting
    // Disable Extension Recpature and Clear Control Setting
    ScalerSetByte(P92_80_DISP_EXT_RECAP_CTRL, 0x00);

    // Clear A1 FIFO Width
    ScalerSetByte(P92_81_SRC_A1_WIDTH_MSB, 0x00);
    ScalerSetByte(P92_82_SRC_A1_WIDTH_LSB, 0x00);
    ScalerSetByte(P92_83_SRC_A1_HEIGHT_MSB, 0x00);
    ScalerSetByte(P92_84_SRC_A1_HEIGHT_LSB, 0x00);

    // Clear A1 Extension Width
    ScalerSetByte(P92_85_EXTENSION_WIDTH_A1, 0x00);

    // Clear A1 FB PBPLR Moving Width
    ScalerSetByte(P92_86_SRC_A1_MOVING_MSB, 0x00);
    ScalerSetByte(P92_87_SRC_A1_MOVING_LSB, 0x00);

    // Clear A2 FIFO Width
    ScalerSetByte(P92_8C_SRC_A2_WIDTH_MSB, 0x00);
    ScalerSetByte(P92_8D_SRC_A2_WIDTH_LSB, 0x00);
    ScalerSetByte(P92_8E_SRC_A2_HEIGHT_MSB, 0x00);
    ScalerSetByte(P92_8F_SRC_A2_HEIGHT_LSB, 0x00);

    // Clear A2 Extension Width
    ScalerSetByte(P92_90_EXTENSION_WIDTH_A2, 0x00);

    // Clear A1 FB PBPLR Moving Width
    ScalerSetByte(P92_91_SRC_A2_MOVING_MSB, 0x00);
    ScalerSetByte(P92_92_SRC_A2_MOVING_LSB, 0x00);
}

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Extension Recapture Moving Length Calculate
// Input Value  : usMdmInputHWidth
// Output Value : Moving Length
//--------------------------------------------------
WORD ScalerScalingGetExtRecapMovingLength(WORD usMdmInputHWidth)
{
    if(ScalerScalingGetPBPLRSingleRegionStatus(GET_MDOMAIN_OUTPUT_HSTART(), GET_MDOMAIN_OUTPUT_HWIDTH()) == _TRUE)
    {
        return (usMdmInputHWidth / 2);
    }
    else
    {
        WORD usLarger_InHwidth = 0;
        WORD usLarger_OutHwidth = 0;
        WORD usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END)) / 2;

        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_L_LARGE)
        {
            usLarger_OutHwidth = usMidline - GET_MDOMAIN_OUTPUT_HSTART();
        }
        else
        {
            usLarger_OutHwidth = GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH() - usMidline;
        }

        usLarger_InHwidth = GET_DWORD_MUL_DIV(usMdmInputHWidth, usLarger_OutHwidth, GET_MDOMAIN_OUTPUT_HWIDTH());
        return (usLarger_InHwidth - (usMdmInputHWidth / 2));
    }
}
#endif
//--------------------------------------------------
// Description  : Get FB PBP L!=R Active Region is only in R1 or R3
// Input Value  : none
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerScalingGetPBPLRSingleRegionStatus(WORD usActiveHstart, WORD usActiveHwidth)
{
    WORD usMidline = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END)) / 2;

    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_L_LARGE)
    {
        if(usActiveHstart + usActiveHwidth > usMidline)
        {
            // Active Region is included R1 & R3
            return _FALSE;
        }
        else
        {
            // Active Region is only included R1
            return _TRUE;
        }
    }
    else if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_R_LARGE)
    {
        if(usActiveHstart < usMidline)
        {
            // Active Region is included R1 & R3
            return _FALSE;
        }
        else
        {
            // Active Region is only included R3
            return _TRUE;
        }
    }
    else
    {
        return _FALSE;
    }
}
#endif

#if(((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON)) && (_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE) && (_SD_TABLE_SEL_FUNCTION == _OFF))
//--------------------------------------------------
// Description  : Set SD Register Related Freesync
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetFSScalingDown(WORD usRegPageSel)
{
    BYTE *pucVSDTable = NULL;

    if((ScalerDrrIVSProduceByBE(GET_MDOMAIN_SOURCE_TYPE(), GET_MDOMAIN_INPUT_PORT()) == _TRUE) && (ScalerScalingGetVScalingDownBypass(usRegPageSel) == _TRUE))
    {
        pucVSDTable = tSD_V_COEF_64_TAPS_BYPASS;
    }
    else
    {
        pucVSDTable = tSD_V_COEF_64_TAPS;
    }
    if((GET_MDOMAIN_INPUT_DATA_PATH() & _INPUT_PATH_M1) == _INPUT_PATH_M1)
    {
        // Set M1 Coefficient table 2
        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(pucVSDTable, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
    if((GET_MDOMAIN_INPUT_DATA_PATH() & _INPUT_PATH_M2) == _INPUT_PATH_M2)
    {
        // Set M2 Coefficient table 2
        ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(pucVSDTable, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
#endif

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
    if((GET_MDOMAIN_INPUT_DATA_PATH() & _INPUT_PATH_S1) == _INPUT_PATH_S1)
    {
        // Set Coefficient table 2
        ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(pucVSDTable, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P80_27_SD_USER_FILTER_ACCESS_PORT_S1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
    if((GET_MDOMAIN_INPUT_DATA_PATH() & _INPUT_PATH_S2) == _INPUT_PATH_S2)
    {
        // Set Coefficient table 2
        ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(pucVSDTable, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), PC0_27_SD_USER_FILTER_ACCESS_PORT_S2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
    if((GET_MDOMAIN_INPUT_DATA_PATH() & _INPUT_PATH_S3) == _INPUT_PATH_S3)
    {
        // Set Coefficient table 2
        ScalerSetBit(P17_26_SD_FILTER_CONTROL_REG_S3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(pucVSDTable, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P17_27_SD_USER_FILTER_ACCESS_PORT_S3, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
#endif

#if(_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON)
    if((GET_MDOMAIN_INPUT_DATA_PATH() & _INPUT_PATH_S4) == _INPUT_PATH_S4)
    {
        // Set Coefficient table 2
        ScalerSetBit(PDC_26_SD_FILTER_CONTROL_REG_S4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(pucVSDTable, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), PDC_27_SD_USER_FILTER_ACCESS_PORT_S4, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
#endif
}
#endif


#if(_SHARPNESS_FUNCTION == _OFF)
//--------------------------------------------------
// Description  : Set ScaleUp Coef
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetScalingUpCoef(void)
{
#if(_HW_D_DOMAIN_R1_A1_ACTIVE_SUPPORT == _ON)
    // R1A1
    // Set Coefficient table 1
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _HSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Set Coefficient table 2
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _VSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable Coefficient Access
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);
#endif

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    // R1A2
    // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetDataPortBit(P0_39_SF_ADDR_PORT_R1_ACTIVE2, _P0_3A_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    // R2A1
    // Set Coefficient table 1
    ScalerSetBit(P80_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _HSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P80_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Set Coefficient table 2
    ScalerSetBit(P80_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _VSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P80_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable Coefficient Access
    ScalerSetBit(P80_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetDataPortBit(P80_33_SF_ADDR_PORT_R2_ACTIVE1, _P80_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R2_ACTIVE1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
    // R2A2
    // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetDataPortBit(P80_39_SF_ADDR_PORT_R2_ACTIVE2, _P80_3A_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R2_ACTIVE2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);
#endif

    if((_D_DOMAIN_M3_M4_PATH_SUPPORT == _ON) || (_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON))
    {
        // R3A1
        // Set Coefficient table 1
        ScalerSetBit(PC0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
        ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _HSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), PC0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Set Coefficient table 2
        ScalerSetBit(PC0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));
        ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _VSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), PC0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Coefficient Access
        ScalerSetBit(PC0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
        ScalerSetDataPortBit(PC0_33_SF_ADDR_PORT_R3_ACTIVE1, _PC0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R3_ACTIVE1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);
    }
    if((_D_DOMAIN_M3_M4_PATH_SUPPORT == _ON) || (_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON))
    {
        // R3A2
        // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
        ScalerSetDataPortBit(PC0_39_SF_ADDR_PORT_R3_ACTIVE2, _PC0_3A_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R3_ACTIVE2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);
    }
}
#endif

//--------------------------------------------------
// Description  : Decide which scaling size
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingUpdateFIFOScalingSize(StructSDRAMDataInfo *pstData)
{
#if(_DOLBY_CERTIFICATION_SUPPORT == _ON)
    SET_MEMORY_FRAME_BUFFER(_MEMORY_1_FRAME_BUFFER);

    pstData->usInputHWidth = GET_MDOMAIN_INPUT_HWIDTH();
    pstData->usInputVHeight = GET_MDOMAIN_INPUT_VHEIGHT();

    pstData->usOutputHWidth = pstData->usInputHWidth;
    pstData->usOutputVHeight = pstData->usInputVHeight;

    // Apply rate ctrl parameter
    ScalerFRCApplyMemRateCtrlParam(0);

    return;
#endif

#if(_FRC_SUPPORT == _ON)
    if((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) && ((GET_MEMORY_DVF_SELECT() == _1_IVF)))
    {
        SET_MEMORY_FRAME_BUFFER(_MEMORY_1_FRAME_BUFFER);
    }
    else
    {
#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
        if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
        {
            SET_MEMORY_FRAME_BUFFER(_MEMORY_1_5_FRAME_BUFFER);
        }
        else
#endif
        {
            SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);
        }
    }

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    ScalerMbrAdvanceUpdateRtkAdvMbrMDomainInfo();
#endif

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
    if((ScalerFRCGetTBMode2BlkSupport() == _OFF) && (GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE))
    {
        SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
    }
#endif
#endif

    //-----------------------------------------------
    // Consider FIFO Input / Output H width
    //-----------------------------------------------
    if(GET_MDOMAIN_INPUT_HWIDTH() > GET_MDOMAIN_OUTPUT_HWIDTH())
    {
        pstData->usInputHWidth = GET_MDOMAIN_OUTPUT_HWIDTH();
    }
    else
    {
        pstData->usInputHWidth = GET_MDOMAIN_INPUT_HWIDTH();
    }

    //-----------------------------------------------
    // Consider FIFO Input / Output V Height
    //-----------------------------------------------
    if(GET_MDOMAIN_INPUT_VHEIGHT() > GET_MDOMAIN_OUTPUT_VHEIGHT())
    {
        pstData->usInputVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT();
    }
    else
    {
        pstData->usInputVHeight = GET_MDOMAIN_INPUT_VHEIGHT();
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        if(GET_MDOMAIN_INPUT_HWIDTH() > GET_MDOMAIN_OUTPUT_VHEIGHT())
        {
            pstData->usInputHWidth = GET_MDOMAIN_OUTPUT_VHEIGHT();
        }
        else
        {
            pstData->usInputHWidth = GET_MDOMAIN_INPUT_HWIDTH();
        }

        if(GET_MDOMAIN_INPUT_VHEIGHT() > GET_MDOMAIN_OUTPUT_HWIDTH())
        {
            pstData->usInputVHeight = GET_MDOMAIN_OUTPUT_HWIDTH();
        }
        else
        {
            pstData->usInputVHeight = GET_MDOMAIN_INPUT_VHEIGHT();
        }
    }
#endif

    if(GET_ROT_TYPE() != _ROT_DISABLE)
    {
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
        if(ScalerRotationCheckVerticalStatus() == _TRUE)
        {
            SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
        }
        else
#endif
        {
            if(ScalerScalingGetRotation3FrameBufferHSDstatus(pstData->usInputHWidth, pstData->usInputVHeight) == _FALSE)
            {
                SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
            }
            else
            {
                ScalerScalingSetRotationFrameBuffer();
            }
        }

        // Reallocate row for rotation, depend on frame buffer count
        PDATA_DWORD(0) = (GET_TOTAL_ROW_FOR_ROTATION_SINGLE_PATH() >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) / ScalerMemoryGetFrameBufferCount();
        SET_ROW_FOR_ROTATION(PDATA_DWORD(0) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
    }
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
    ScalerMemoryAdjustFRCODBoundary();
#endif

#if(_FRC_SUPPORT == _ON)
    //-----------------------------------------------
    // Consider FIFO Input / Output H width in FRC
    //-----------------------------------------------
    if(GET_MEMORY_WORK_TYPE() == _MEMORY_WORK_MODE)
    {
        bit bHwidthmultipleof4 = (ScalerFRCGetMDispPathCount(ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH())) == _DISPLAY_PATH_4);
        BYTE ucRateCtrlParamIndex = 0;
        StructFRCRateCtrlInfo stFRCRateCtrlInfo;

        // Prepare necessary info for rate ctrl decision
        stFRCRateCtrlInfo.ucImgCmpUsable = ScalerFRCGetImgCmpHWUsability();
        stFRCRateCtrlInfo.ucImgCmpUsable &= ScalerFRCGetImgCmpRunTimeUsability(pstData->usInputHWidth, pstData->usInputVHeight);
        stFRCRateCtrlInfo.usInputHWidth = GET_MDOMAIN_INPUT_HWIDTH();
        stFRCRateCtrlInfo.usFifoHWidth = pstData->usInputHWidth;
        stFRCRateCtrlInfo.usFifoVHeight = pstData->usInputVHeight;
        stFRCRateCtrlInfo.ulGrantBW = ScalerMDomainGetCurBW();
        ScalerMDomainGetMemBWParam(&stFRCRateCtrlInfo.stMemBWParam);

        ucRateCtrlParamIndex = ScalerFRCGetMemRateCtrlParamIndex(&stFRCRateCtrlInfo);

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
        // Ensure hwith to be multiple of 4 for imc 2 slice mode or m-display path = 4
        bHwidthmultipleof4 |= (ScalerImgCmpGetMultiSliceEn(GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE);
#endif
        if(bHwidthmultipleof4 == _TRUE)
        {
            stFRCRateCtrlInfo.usFifoHWidth -= (stFRCRateCtrlInfo.usFifoHWidth % 4);
        }

        // Update HSD result
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
        if(ScalerRotationCheckVerticalStatus() == _TRUE)
        {
            if(stFRCRateCtrlInfo.usFifoHWidth > _ROTATION_VERTICAL_MAX_SUPPORT_HWIDTH)
            {
                DebugMessageScaler("[Warning]!!!!!! FIFO Input Hwidth exceed Rotation CW90/270 max support hwidth 2560", stFRCRateCtrlInfo.usFifoHWidth);
                stFRCRateCtrlInfo.usFifoHWidth = _ROTATION_VERTICAL_MAX_SUPPORT_HWIDTH;
            }
        }
#endif
        pstData->usInputHWidth = stFRCRateCtrlInfo.usFifoHWidth;

        // Apply rate ctrl parameter
        ScalerFRCApplyMemRateCtrlParam(ucRateCtrlParamIndex);
    } // End of if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)
#endif // End of #if(_FRC_SUPPORT == _ON)

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        pstData->usOutputHWidth = pstData->usInputVHeight;
        pstData->usOutputVHeight = pstData->usInputHWidth;
    }
    else
#endif
    {
        pstData->usOutputHWidth = pstData->usInputHWidth;
        pstData->usOutputVHeight = pstData->usInputVHeight;
    }
}

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide number of frame buffer for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetRotationFrameBuffer(void)
{
    BYTE ucMargin = 2;

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    // if path > 1, need to consider VSD factor
    ucMargin += (ScalerGetDataPortSingleByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_01_V_SD_FACTOR_H_M1) >> 1);
#endif

    if(GET_MEMORY_DVF_SELECT() == _1_IVF)
    {
        SET_MEMORY_FRAME_BUFFER(_MEMORY_1_FRAME_BUFFER);
    }
    else
    {
#if(_FORCE_TO_FREE_RUN_SUPPORT == _ON)
        if((GET_MEMORY_DVF_SELECT() == _PANEL_TYP_FRAME_RATE_FREE_RUN) &&
           (GET_MDOMAIN_INPUT_VFREQ() <= (GET_OUTPUT_VFREQ() + (GET_OUTPUT_VFREQ() / 10))) &&
           (GET_MDOMAIN_INPUT_VFREQ() >= (GET_OUTPUT_VFREQ() - (GET_OUTPUT_VFREQ() / 10))))
        {
            SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
        }
        else
#endif
        {
#if(_DISPLAY_ROTATION_FORCE_3_BUFFER == _ON)
            SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
#else
            // Consider Input Faster Case
            if(ScalerFRCCompareDenTime(GET_MDOMAIN_INPUT_VHEIGHT()) == _FRC_I_DEN_SMALL_D_DEN)
            {
                // IVTotal Period = IVTotal / IHF
                PDATA_WORD(4) = ((DWORD)GET_MDOMAIN_INPUT_VTOTAL() * 100 / GET_MDOMAIN_INPUT_HFREQ());

                // DDEN Period = (DVH + Pre-read line) / DHF
                PDATA_WORD(5) = GET_DWORD_MUL_DIV((DWORD)(GET_MDOMAIN_OUTPUT_VHEIGHT() + GET_FRC_PRE_READ(_FRC_MAIN1_PAGE)) * 100, GET_MDOMAIN_OUTPUT_HTOTAL(), (DWORD)GET_D_CLK_FREQ() * 10);

                // DVTotal Period(strict) = (DVTotal - DVStart - margin) / DHF
                PDATA_WORD(6) = GET_DWORD_MUL_DIV((DWORD)(GET_MDOMAIN_OUTPUT_VTOTAL() - GET_MDOMAIN_OUTPUT_VSTART() - ucMargin) * 100, GET_MDOMAIN_OUTPUT_HTOTAL(), (DWORD)GET_D_CLK_FREQ() * 10);

                // DVTotal Period(strict) > IVTotal Period > DDEN Period
                if((PDATA_WORD(6) > PDATA_WORD(4)) && (PDATA_WORD(4) > PDATA_WORD(5)))
                {
                    SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);
                }
                else
                {
                    SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
                }
            }
            else
            {
                SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);
            }
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Get 3 buffer HSD status for rotation
// Input Value  : WORD usWidth, WORD usVheight
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerScalingGetRotation3FrameBufferHSDstatus(WORD usWidth, WORD usVheight)
{
    // imc is off when rotation is on, use 24bit for famesize to compare with GET_ROW_FOR_MAIN
    DWORD ulFrameSize = ScalerFRCGetLineSumBit(usWidth, (_COLOR_DEPTH_8_BITS * 3), _IMG_CMP_PARAM_OFF) * usVheight;
    ulFrameSize = CEILING_OF_INT_DIVISION(GET_DEFAULT_FRAME_USE_MEMORY_ROW(ulFrameSize), _INPUT_PATH_2);

    if((ulFrameSize * 3) > (GET_TOTAL_ROW_FOR_ROTATION_SINGLE_PATH() >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM))
    {
        return _TRUE;
    }
    return _FALSE;
}
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide which scaling size
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingUpdatePBPTopDVHeight(StructSDRAMDataInfo *pstData)
{
    pstData = pstData;
}
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
//--------------------------------------------------
// Description  : Set Scale Up coef
// Input Value  : H/V coef table, length
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingCoef(EnumSelRegion enumSelRegion, BYTE *pucAddress1, BYTE *pucAddress2, BYTE ucBankNum)
{
    WORD usCoefWritePage = 0x00;
    WORD usCoefAddress = 0x00;
    BYTE ucTableHorUseSel = 0;
    BYTE ucTableVerUseSel = 0;
    bit bCoexist_A1 = _FALSE;
    bit bCoexist_A2 = _FALSE;

    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            usCoefWritePage = _REG_MAIN1_PAGE;
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            usCoefWritePage = _REG_MAIN1_PAGE;
            break;

        case _2P_PIP_SUB:
            usCoefWritePage = _REG_SUB1_PAGE;
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            usCoefWritePage = _REG_MAIN1_PAGE;
            break;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            usCoefWritePage = _REG_SUB1_PAGE;
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
            usCoefWritePage = _REG_MAIN1_PAGE;
            break;

        case _2P_PBP_LR_R_LARGE_L:
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                // RL6952, RL6829 FB
                usCoefWritePage = _REG_SUB1_PAGE;
            }
            else
            {
                // RL6829 EO, RL6978
                usCoefWritePage = _REG_MAIN1_PAGE;
            }
            break;

        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
            usCoefWritePage = _REG_SUB1_PAGE;
            break;

        case _2P_PBP_LR_R_LARGE_R:
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                // RL6952, RL6829 FB
                usCoefWritePage = _REG_MAIN1_PAGE;
            }
            else
            {
                // RL6829 EO, RL6978
                usCoefWritePage = _REG_SUB1_PAGE;
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A1 = _TRUE;
            break;

        case _2P_PBP_TB_B:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A2 = _TRUE;
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A1 = _TRUE;
            break;

        case _4P_LB:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A2 = _TRUE;
            break;

        case _4P_RT:
            usCoefWritePage = _REG_SUB1_PAGE;
            bCoexist_A1 = _TRUE;
            break;

        case _4P_RB:
            usCoefWritePage = _REG_SUB1_PAGE;
            bCoexist_A2 = _TRUE;
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M:
            usCoefWritePage = _REG_SUB1_PAGE;
            break;

        case _3P_FLAG_L:
            usCoefWritePage = _REG_MAIN1_PAGE;
            break;

        case _3P_FLAG_R:
            usCoefWritePage = _REG_SUB2_PAGE;
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
            usCoefWritePage = _REG_MAIN1_PAGE;
            break;

        case _3P_SKEW_L_T:
            usCoefWritePage = _REG_SUB1_PAGE;
            bCoexist_A1 = _TRUE;
            break;

        case _3P_SKEW_L_B:
            usCoefWritePage = _REG_SUB1_PAGE;
            bCoexist_A2 = _TRUE;
            break;

        case _3P_SKEW_R_M:
            usCoefWritePage = _REG_SUB1_PAGE;
            break;

        case _3P_SKEW_R_T:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A1 = _TRUE;
            break;

        case _3P_SKEW_R_B:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A2 = _TRUE;
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A1 = _TRUE;
            break;

        case _3P_SKEW_T_L:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A2 = _TRUE;
            break;

        case _3P_SKEW_T_R:
            usCoefWritePage = _REG_SUB1_PAGE;
            break;

        case _3P_SKEW_B_M:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A2 = _TRUE;
            break;

        case _3P_SKEW_B_L:
            usCoefWritePage = _REG_MAIN1_PAGE;
            bCoexist_A1 = _TRUE;
            break;

        case _3P_SKEW_B_R:
            usCoefWritePage = _REG_SUB1_PAGE;
            break;
#endif

        case _FULL_REGION:

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_R_B_OUTSIDE:
        case _3P_SKEW_R_M_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_L_T_OUTSIDE:
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_L_OUTSIDE:
        case _3P_FLAG_M_OUTSIDE:
        case _3P_FLAG_R_OUTSIDE:
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
        case _3P_SKEW_B_M_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
#endif

        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:

        default:
            break;
    }

#if((_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON))
    usCoefAddress = bCoexist_A2 * _A1A2_REG_ADDR_OFFSET;
#endif

    // get current coef sel in use
    ucTableHorUseSel = ScalerGetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usCoefWritePage + usCoefAddress, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, (_BIT5 | _BIT4));
    ucTableVerUseSel = ScalerGetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usCoefWritePage + usCoefAddress, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, (_BIT3 | _BIT2));

    // switch to spare sel
    if((bCoexist_A1 == _FALSE) && (bCoexist_A2 == _FALSE))
    {
        // H switch sel between set 0 & 2
        if((ucTableHorUseSel >> 4) != 0x00)
        {
            ucTableHorUseSel = 0x00;
        }
        else
        {
            ucTableHorUseSel = 0x02;
        }

        // V switch sel between set 1 & 3
        if((ucTableVerUseSel >> 2) != 0x01)
        {
            ucTableVerUseSel = 0x01;
        }
        else
        {
            ucTableVerUseSel = 0x03;
        }
    }

    // Region A1&A2 Coexist in these display mode: PBP_TB,3P_SKEW_T/B,3P_SKEW_L/R,4P
    else if((bCoexist_A1 == _TRUE) && (bCoexist_A2 == _FALSE))
    {
        // SelRegion A1: H&V use the same sel, switch between set 0 or 2
        if((ucTableHorUseSel >> 4) != 0x00)
        {
            ucTableHorUseSel = 0x00;
        }
        else
        {
            ucTableHorUseSel = 0x02;
        }
        ucTableVerUseSel = ucTableHorUseSel;
    }
    else if((bCoexist_A1 == _FALSE) && (bCoexist_A2 == _TRUE))
    {
        // SelRegion A2: H&V use the same, switch between set 1 or 3
        if((ucTableHorUseSel >> 4) != 0x01)
        {
            ucTableHorUseSel = 0x01;
        }
        else
        {
            ucTableHorUseSel = 0x03;
        }
        ucTableVerUseSel = ucTableHorUseSel;
    }

    // Set filter_control_reg, write Hsel table
    ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | (ucTableHorUseSel << 5)));
    ScalerBurstWrite(pucAddress1, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT + usCoefWritePage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    if(ucTableVerUseSel != ucTableHorUseSel)
    {
        // Set filter_control_reg, write Vsel table
        ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | (ucTableVerUseSel << 5)));
        ScalerBurstWrite(pucAddress2, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT + usCoefWritePage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    // Disable Coefficient Access,
    ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Set h_coef_sel & v_coef_sel
    ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usCoefWritePage + usCoefAddress, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), ((ucTableHorUseSel << 4) | (ucTableVerUseSel << 2)));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerScalingGetFBFrameStatus(enumSelRegion) == _TRUE)
    {
        // Set back region filter_control_reg, write Hsel table
        ScalerSetBit(P0_35_FILTER_CONTROL_REG + 0xC000, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | (ucTableHorUseSel << 5)));
        ScalerBurstWrite(pucAddress1, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT + 0xC000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        if(ucTableVerUseSel != ucTableHorUseSel)
        {
            // Write Vsel table
            ScalerSetBit(P0_35_FILTER_CONTROL_REG + 0xC000, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | (ucTableVerUseSel << 5)));
            ScalerBurstWrite(pucAddress2, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT + 0xC000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        }

        // Disable Coefficient Access,
        ScalerSetBit(P0_35_FILTER_CONTROL_REG + 0xC000, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // Set h_coef_sel & v_coef_sel
        ScalerSetDataPortBit(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usCoefWritePage + usCoefAddress + 0xC000, _P0_34_PT_19_SCALE_UP_FOR_LINE_INTERLEAVE_R1_ACTIVE1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), ((ucTableHorUseSel << 4) | (ucTableVerUseSel << 2)));
    }
#endif
}
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
//--------------------------------------------------
// Description  : Get Scaling down EO page mapping
// Input Value  : Select Page
// Output Value : Mapping page
//--------------------------------------------------
WORD ScalerScalingGetEOModePageMapping(WORD usRegPageSel)
{
    switch(usRegPageSel)
    {
        case _REG_MAIN1_PAGE:
            return _REG_MAIN2_PAGE;

        case _REG_SUB1_PAGE:
            return _REG_SUB2_PAGE;

        case _REG_SUB3_PAGE:
            return _REG_SUB4_PAGE;

        default:
            return usRegPageSel;
    }
}
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get FB frame status from select region
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerScalingGetFBFrameStatus(EnumSelRegion enumSelRegion)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
    {
        switch(enumSelRegion)
        {
            case _1P_NORMAL_REGION:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _2P_PIP_MAIN:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _2P_PIP_EAGLE_SIGHT_MAIN:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _2P_PBP_LR_L_LARGE_L:
            case _2P_PBP_LR_R_LARGE_R:
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _2P_PBP_TB_T:
            case _2P_PBP_TB_B:
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _3P_SKEW_B_M:
            case _3P_SKEW_T_M:
#endif
                return _TRUE;

            case _FULL_REGION:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _2P_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _2P_PIP_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _2P_PBP_LR_EQUAL_L:
            case _2P_PBP_LR_EQUAL_R:
            case _2P_PBP_LR_L_LARGE_R:
            case _2P_PBP_LR_R_LARGE_L:
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
            case _3P_FLAG_M:
            case _3P_FLAG_L:
            case _3P_FLAG_R:
            case _3P_FLAG_M_OUTSIDE:
            case _3P_FLAG_L_OUTSIDE:
            case _3P_FLAG_R_OUTSIDE:
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            case _3P_SKEW_L_M:
            case _3P_SKEW_L_T:
            case _3P_SKEW_L_B:
            case _3P_SKEW_L_M_OUTSIDE:
            case _3P_SKEW_L_T_OUTSIDE:
            case _3P_SKEW_L_B_OUTSIDE:
            case _3P_SKEW_R_M:
            case _3P_SKEW_R_T:
            case _3P_SKEW_R_B:
            case _3P_SKEW_R_M_OUTSIDE:
            case _3P_SKEW_R_T_OUTSIDE:
            case _3P_SKEW_R_B_OUTSIDE:
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _3P_SKEW_T_L:
            case _3P_SKEW_T_R:
            case _3P_SKEW_T_M_OUTSIDE:
            case _3P_SKEW_T_L_OUTSIDE:
            case _3P_SKEW_T_R_OUTSIDE:
            case _3P_SKEW_B_L:
            case _3P_SKEW_B_R:
            case _3P_SKEW_B_M_OUTSIDE:
            case _3P_SKEW_B_L_OUTSIDE:
            case _3P_SKEW_B_R_OUTSIDE:
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
            case _4P_LT:
            case _4P_LB:
            case _4P_RT:
            case _4P_RB:
            case _4P_LT_OUTSIDE:
            case _4P_LB_OUTSIDE:
            case _4P_RT_OUTSIDE:
            case _4P_RB_OUTSIDE:
#endif
            case _DEMO_INSIDE:
            case _DEMO_OUTSIDE:
            default:
                return _FALSE;
        }
    }
    else
    {
        return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : VScalingDown BYPASS CHECK
// Input Value  : Select Page
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerScalingGetVScalingDownBypass(WORD usRegPageSel)
{
    DWORD ulVSDF = 0;

    ScalerGetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_01_V_SD_FACTOR_H_M1, 3, &pData[0], _AUTOINC);
    pData[3] = ScalerGetDataPortSingleByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_42_V_SD_FACTOR_L1_M1);

    ulVSDF = (((DWORD)(pData[0] & 0x1F) << 19) | ((DWORD)pData[1] << 11) | ((DWORD)pData[2] << 3) | ((pData[3] & 0xE0) >> 5));

    if(ulVSDF == _SD_BYPASS_FACTOR)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_FRC_SUPPORT == _ON)
#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_0)
//--------------------------------------------------
// Description  : Get HFrontPorch after HScalingDown
// Input Value  : EnumInputDataPath, sd_out_width, inwidth, Hfporch before HSD, bFBmode
// Output Value : Hfporch After HSD
//--------------------------------------------------
WORD ScalerScalingGetHFrontPorchAfterHSD(EnumInputDataPath enumInputPath, WORD usOutWidth, WORD usInWidth, WORD usHfporch, bit bFBmode)
{
    DWORD ulHSDF = 0;
    DWORD ulHSDI = 0;
    WORD usLastPixelPosition = 0;

    if((enumInputPath & _INPUT_PATH_M1_M2) == _INPUT_PATH_M1_M2)
    {
        if((ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT1) == 0x00) || (ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT4) == _BIT4))
        {
            return usHfporch;
        }

        ScalerGetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_05_H_SD_FACTOR_H_M1, 3, &pData[0], _AUTOINC);
        ScalerGetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_43_H_SD_INIT_M_M1, 3, &pData[3], _AUTOINC);
        pData[6] = ScalerGetDataPortSingleByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_04_H_SD_INIT_M1);

        ulHSDF = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | (pData[2]));
        ulHSDI = (((DWORD)(pData[5] & 0x03) << 22) | (DWORD)(pData[6] << 14) | (DWORD)(pData[3] << 6) | ((pData[4] & 0xFC) >> 2));

        usLastPixelPosition = (WORD)(((QWORD)ulHSDF * (usOutWidth - 1) + ulHSDI) >> 20);

        if(bFBmode == _TRUE)
        {
            usHfporch = usHfporch + GET_FMTCNV_EXTENSION_LEN() - (WORD)(ulHSDI >> 20);
            return usHfporch;
        }
        else
        {
            if(usInWidth < (usLastPixelPosition + 1))
            {
                if(usHfporch + usInWidth < (usLastPixelPosition + 1))
                {
                    DebugMessageScaler("Warning!!! last pixel position out of range", usLastPixelPosition);
                    return usHfporch;
                }
            }

            return usHfporch + (usInWidth - 1) - usLastPixelPosition;
        }
    }

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
    if((enumInputPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S1_S2)
    {
        if((ScalerGetBit(P80_23_SCALE_DOWN_CTRL_S1, _BIT1) == 0x00) || (ScalerGetBit(P80_23_SCALE_DOWN_CTRL_S1, _BIT4) == _BIT4))
        {
            return usHfporch;
        }

        ScalerGetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_05_H_SD_FACTOR_H_S1, 3, &pData[0], _AUTOINC);
        ScalerGetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_43_H_SD_INIT_M_S1, 3, &pData[3], _AUTOINC);
        pData[6] = ScalerGetDataPortSingleByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_04_H_SD_INIT_S1);

        ulHSDF = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | (pData[2]));
        ulHSDI = (((DWORD)(pData[5] & 0x03) << 22) | (DWORD)(pData[6] << 14) | (DWORD)(pData[3] << 6) | ((pData[4] & 0xFC) >> 2));

        usLastPixelPosition = (WORD)(((QWORD)ulHSDF * (usOutWidth - 1) + ulHSDI) >> 20);

        if(usInWidth < (usLastPixelPosition + 1))
        {
            if(usHfporch + usInWidth < (usLastPixelPosition + 1))
            {
                DebugMessageScaler("Warning!!! last pixel position out of range", usLastPixelPosition);
                return usHfporch;
            }
        }

        return usHfporch + (usInWidth - 1) - usLastPixelPosition;
    }
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
    if((enumInputPath & _INPUT_PATH_S3_S4) == _INPUT_PATH_S3_S4)
    {
        if((ScalerGetBit(P17_23_SCALE_DOWN_CTRL_S3, _BIT1) == 0x00) || (ScalerGetBit(P17_23_SCALE_DOWN_CTRL_S3, _BIT4) == _BIT4))
        {
            return usHfporch;
        }

        ScalerGetDataPortByte(P17_24_SD_ADDRESS_PORT_S3, _P17_25_PT_05_H_SD_FACTOR_H_S3, 3, &pData[0], _AUTOINC);
        ScalerGetDataPortByte(P17_24_SD_ADDRESS_PORT_S3, _P17_25_PT_43_H_SD_INIT_M_S3, 3, &pData[3], _AUTOINC);
        pData[6] = ScalerGetDataPortSingleByte(P17_24_SD_ADDRESS_PORT_S3, _P17_25_PT_04_H_SD_INIT_S3);

        ulHSDF = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | (pData[2]));
        ulHSDI = (((DWORD)(pData[5] & 0x03) << 22) | (DWORD)(pData[6] << 14) | (DWORD)(pData[3] << 6) | ((pData[4] & 0xFC) >> 2));

        usLastPixelPosition = (WORD)(((QWORD)ulHSDF * (usOutWidth - 1) + ulHSDI) >> 20);

        if(usInWidth < (usLastPixelPosition + 1))
        {
            if(usHfporch + usInWidth < (usLastPixelPosition + 1))
            {
                DebugMessageScaler("Warning!!! last pixel position out of range", usLastPixelPosition);
                return usHfporch;
            }
        }

        return usHfporch + (usInWidth - 1) - usLastPixelPosition;
    }
#endif

    return usHfporch;
}

//--------------------------------------------------
// Description  : Get HBackPorch after HScalingDown
// Input Value  : EnumInputDataPath, sd_out_width, inwidth, Hbporch before HSD, bFBmode
// Output Value : Hbporch After HSD
//--------------------------------------------------
WORD ScalerScalingGetHBackPorchAfterHSD(EnumInputDataPath enumInputPath, WORD usHbporch, bit bFBmode)
{
    DWORD ulHSDF = 0;
    DWORD ulHSDI = 0;

    if((enumInputPath & _INPUT_PATH_M1_M2) == _INPUT_PATH_M1_M2)
    {
        if((ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT1) == 0x00) || (ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT4) == _BIT4) || (bFBmode == _FALSE))
        {
            return usHbporch;
        }

        ScalerGetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_43_H_SD_INIT_M_M1, 3, &pData[0], _AUTOINC);
        pData[3] = ScalerGetDataPortSingleByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_04_H_SD_INIT_M1);
        ulHSDI = (((DWORD)(pData[2] & 0x03) << 22) | (DWORD)(pData[3] << 14) | (DWORD)(pData[0] << 6) | ((pData[1] & 0xFC) >> 2));

        return usHbporch + (WORD)(ulHSDI >> 20);
    }

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
    if((enumInputPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S1_S2)
    {
        if((ScalerGetBit(P80_23_SCALE_DOWN_CTRL_S1, _BIT1) == 0x00) || (ScalerGetBit(P80_23_SCALE_DOWN_CTRL_S1, _BIT4) == _BIT4) || (bFBmode == _FALSE))
        {
            return usHbporch;
        }
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        ScalerGetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_05_H_SD_FACTOR_H_S1, 3, &pData[0], _AUTOINC);
        ScalerGetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_43_H_SD_INIT_M_S1, 3, &pData[3], _AUTOINC);
        pData[6] = ScalerGetDataPortSingleByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_04_H_SD_INIT_S1);

        ulHSDF = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | (pData[2]));
        ulHSDI = (((DWORD)(pData[5] & 0x03) << 22) | (DWORD)(pData[6] << 14) | (DWORD)(pData[3] << 6) | ((pData[4] & 0xFC) >> 2));

        return usHbporch + (WORD)((ulHSDF * GET_DROP_EXTENSION_LENGTH() + ulHSDI) >> 20);
#endif
    }
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
    if((enumInputPath & _INPUT_PATH_S3_S4) == _INPUT_PATH_S3_S4)
    {
        return usHbporch;
    }
#endif

    return usHbporch;
}
#endif
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get ES Original Mode Status
// Input Value  : WORD usInputHWidth, WORD usInputVHeight
// Output Value : bStatus
//--------------------------------------------------
bit ScalerScalingGetESOriginalModeStatus(WORD usInputHWidth, WORD usInputVHeight)
{
    bit bStatus = _FALSE;
    DWORD ulHSUF_M = 0;
    DWORD ulHSUF_S = 0;
    DWORD ulVSUF_M = 0;
    DWORD ulVSUF_S = 0;

    // Check HSUF Same as ES Main
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_00_HOR_SCALE_FACTOR_H_R1_ACTIVE1, 3, &pData[0], _AUTOINC);
    ulHSUF_M = TO_DWORD(0, pData[0], pData[1], pData[2]);

    // Calculate Scaling Factor & Set HSUF
    ulHSUF_S = GET_DWORD_MUL_DIV((1UL << (_HSU_FACTOR_BIT + 1)), usInputHWidth, GET_MDOMAIN_OUTPUT_HWIDTH());
    ulHSUF_S = (ulHSUF_S + 1) >> 1;

    // Check VSUF Same as ES Main
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_03_VER_SCALE_FACTOR_H_R1_ACTIVE1, 3, &pData[6], _AUTOINC);
    ulVSUF_M = TO_DWORD(0, pData[6], pData[7], pData[8]);

    // Calculate Scaling Factor
    ulVSUF_S = GET_DWORD_MUL_DIV((1UL << (_VSU_FACTOR_BIT + 1)), usInputVHeight, GET_MDOMAIN_OUTPUT_VHEIGHT());
    ulVSUF_S = (ulVSUF_S + 1) >> 1;

    if((ulHSUF_M == ulHSUF_S) && (ulVSUF_M == ulVSUF_S))
    {
        DWORD ulDiff_Hstart_Idm = 0;
        DWORD ulDiff_Hstart_Ddm = 0;
        DWORD ulDiff_Vstart_Idm = 0;
        DWORD ulDiff_Vstart_Ddm = 0;

        // Check I/D Hstart
        ulDiff_Hstart_Idm = ScalerScalingGetESOriginalModeMainSubDiffHstart();

        ulDiff_Hstart_Ddm = GET_DWORD_MUL_DIV(ulDiff_Hstart_Idm, GET_MDOMAIN_OUTPUT_HWIDTH(), usInputHWidth) + (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START));

        // Check I/D Vstart
        ulDiff_Vstart_Idm = ScalerScalingGetESOriginalModeMainSubDiffVstart();

        ulDiff_Vstart_Ddm = GET_DWORD_MUL_DIV(ulDiff_Vstart_Idm, GET_MDOMAIN_OUTPUT_VHEIGHT(), usInputVHeight) + (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START));

        if(abs(ulDiff_Hstart_Ddm - GET_MDOMAIN_OUTPUT_HSTART()) <= _ES_ORIGINAL_MODE_ADJUST_TOLERANCE)
        {
            if(abs(ulDiff_Vstart_Ddm - GET_MDOMAIN_OUTPUT_VSTART()) <= _ES_ORIGINAL_MODE_ADJUST_TOLERANCE)
            {
                bStatus = _TRUE;
            }
        }
    }

    return bStatus;
}

//--------------------------------------------------
// Description  : Modift H/VSUFI On ES Original mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerScalingModifyESOriginalModeSUFI(void)
{
    BYTE ucHSUFI = 0;
    BYTE ucVSUFI = 0;
    DWORD ulHSUF = 0;
    DWORD ulVSUF = 0;
    DWORD ulDiff_Hstart_Idm = 0;
    DWORD ulDiff_Hstart_Ddm = 0;
    DWORD ulDiff_Vstart_Idm = 0;
    DWORD ulDiff_Vstart_Ddm = 0;
    WORD usFIFOHWidth = 0;
    WORD usFIFOVHeight = 0;

    // Get HSUFI
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_10_HOR_FILTER_COEF_INI_R1_ACTIVE1, 1, &ucHSUFI, _AUTOINC);

    // Get VSUFI
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_11_VER_FILTER_COEF_INI_R1_ACTIVE1, 1, &ucVSUFI, _AUTOINC);

    // Get HSUF
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_00_HOR_SCALE_FACTOR_H_R1_ACTIVE1, 3, &pData[0], _AUTOINC);
    ulHSUF = TO_DWORD(0, pData[0], pData[1], pData[2]);

    // Get VSUF
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_03_VER_SCALE_FACTOR_H_R1_ACTIVE1, 3, &pData[3], _AUTOINC);
    ulVSUF = TO_DWORD(0, pData[3], pData[4], pData[5]);

    // Get FIFO Hwidth
    usFIFOHWidth = ScalerMemoryGetFifoWidth(_DDOMAIN_RGN_R2_A1);

    // Get FIFO VHeight
    usFIFOVHeight = ScalerMemoryGetFifoVheight(_DDOMAIN_RGN_R2_A1);

    // Set New HSUFI
    ulDiff_Hstart_Idm = ScalerScalingGetESOriginalModeMainSubDiffHstart();

    ulDiff_Hstart_Ddm = GET_DWORD_MUL_DIV(ulDiff_Hstart_Idm, GET_MDOMAIN_OUTPUT_HWIDTH(), usFIFOHWidth);

    if(((ulDiff_Hstart_Idm * GET_MDOMAIN_OUTPUT_HWIDTH()) % usFIFOHWidth) == 0)
    {
        ucHSUFI = ((ucHSUFI << 12) + (((DWORD)ulDiff_Hstart_Idm << _HSU_FACTOR_BIT) - (ulDiff_Hstart_Ddm * ulHSUF))) >> 12;
    }
    else
    {
        ucHSUFI = ((ucHSUFI << 12) + (ulDiff_Hstart_Ddm * ulHSUF) - (((DWORD)ulDiff_Hstart_Idm << _HSU_FACTOR_BIT))) >> 12;
    }

    ScalerScalingSetHScalingUpInitialPhase(_REG_SUB1_PAGE, (((DWORD)ucHSUFI << 12) & 0xFF000));

    // Set New VSUFI
    ulDiff_Vstart_Idm = ScalerScalingGetESOriginalModeMainSubDiffVstart();

    ulDiff_Vstart_Ddm = GET_DWORD_MUL_DIV(ulDiff_Vstart_Idm, GET_MDOMAIN_OUTPUT_VHEIGHT(), usFIFOVHeight);

    if(((ulDiff_Vstart_Idm * GET_MDOMAIN_OUTPUT_VHEIGHT()) % usFIFOVHeight) == 0)
    {
        ucVSUFI = ((ucVSUFI << 12) + (((DWORD)ulDiff_Vstart_Idm << _VSU_FACTOR_BIT) - (ulDiff_Vstart_Ddm * ulVSUF))) >> 12;
    }
    else
    {
        ucVSUFI = ((ucVSUFI << 12) + (ulDiff_Vstart_Ddm * ulVSUF) - (((DWORD)ulDiff_Vstart_Idm << _VSU_FACTOR_BIT))) >> 12;
    }
    ScalerSetDataPortByte(P80_33_SF_ADDR_PORT_R2_ACTIVE1, _P80_34_PT_11_VER_FILTER_COEF_INI_R2_ACTIVE1, ucVSUFI);
}

//--------------------------------------------------
// Description  : Get Original mode Main/Sub DiffHstart
// Input Value  : None
// Output Value : DiffHstart
//--------------------------------------------------
DWORD ScalerScalingGetESOriginalModeMainSubDiffHstart(void)
{
    DWORD ulDiff_Hstart_Idm = 0;

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
    if(ScalerFmtCnvEagleSightEnableStatus() == _TRUE)
    {
        ulDiff_Hstart_Idm = (DWORD)ScalerFmtCnvEagleSightGetCaptureStart();
    }
    else
#endif
    {
        ulDiff_Hstart_Idm = (GET_MDOMAIN_INPUT_HSTART() > GET_INPUT_TIMING_HSTART()) ? (GET_MDOMAIN_INPUT_HSTART() - GET_INPUT_TIMING_HSTART()) : 0;
    }

    return ulDiff_Hstart_Idm;
}

//--------------------------------------------------
// Description  : Get Original mode Main/Sub DiffVstart
// Input Value  : None
// Output Value : DiffVstart
//--------------------------------------------------
DWORD ScalerScalingGetESOriginalModeMainSubDiffVstart(void)
{
    DWORD ulDiff_Vstart_Idm = 0;

    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        ulDiff_Vstart_Idm = ScalerVgipGetCaptureVStartPosition();
    }
    else
    {
        if((ScalerVgipGetCaptureVStartPosition() + ScalerVgipGetCaptureVDelay() + ((ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT0) == _BIT0) ? 0 : 1)) > GET_INPUT_TIMING_VSTART())
        {
            ulDiff_Vstart_Idm = (ScalerVgipGetCaptureVStartPosition() + ScalerVgipGetCaptureVDelay() + ((ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT0) == _BIT0) ? 0 : 1)) - GET_INPUT_TIMING_VSTART();
        }
        else
        {
            ulDiff_Vstart_Idm = 0;
        }
    }

    return ulDiff_Vstart_Idm;
}

#endif
#endif
