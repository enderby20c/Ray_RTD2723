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
// ID Code      : ScalerVgip.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_VGIP__

#include "ScalerFunctionInclude.h"
#include "Vgip/ScalerVgip.h"



//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
EnumInputDataPath g_enumVgipInputPath = _INPUT_PATH_NONE;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialization for VGIP Input
// Input Value  : enumSourceType -> Input Source Type
// Output Value : None
//--------------------------------------------------
void ScalerVgipInputInitial(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    bit bRisingLatch = _FALSE;

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
    if(ScalerSyncGetVerticalTimingDataFromInterface(enumSourceType, enumInputPort) == _TRUE)
    {
        // Set VGIP Vsync latched by Hsync rising edge
        bRisingLatch = _TRUE;
    }
#endif

    enumSourceType = enumSourceType;
    enumInputPort = enumInputPort;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            // Set source from format conversion; Disable Double buffer, Analog Capture, and Stop generate DE
            SET_PAGED_BIT(ucIdomainPage, P0_10_M1_VGIP_CTRL, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

            // Reset field detect edge; Disable VGIP safe mode
            SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~(_BIT7 | _BIT5 | _BIT3), 0x00);

            // Disable Force ODD Toggle
            SET_PAGED_BIT(ucIdomainPage, P0_13_M1_VGIP_ODD_CTRL, ~_BIT4, 0x00);

            // Reset CTS fifo
            SET_PAGED_BIT(ucIdomainPage, P0_20_M1_DUMMY2, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            SET_PAGED_BIT(ucIdomainPage, P0_20_M1_DUMMY2, ~(_BIT2 | _BIT1 | _BIT0), (_BIT0));

            // Enable bypass Vsync
            ScalerVgipSetVsBypassEnable(GET_VGIP_INPUT_PATH(), _ENABLE);

            // HS Sync Edge select to Positive, Disable 1 clock Delay Mode
            SET_PAGED_BIT(ucIdomainPage, P0_12_M1_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), ((BYTE)bRisingLatch << 2));
        }
    }

    // Set to analog measure
    ScalerVgipSetDigitalCaptureStatus(_DISABLE);

    // Initial IVS/IHS Delay for Capture and Auto
    ScalerVgipSetCaptureHDelay(0x00);
    ScalerVgipSetCaptureVDelay(0x00);
    ScalerVgipSetCaptureHStartPosition(0x00);
    ScalerVgipSetCaptureVStartPosition(0x00);

    // Apply VGIP DB
    ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    if(ScalerDrrIVSProduceByBE(enumSourceType, enumInputPort) == _TRUE)
    {
    }
    else
#endif
    {
        for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

            if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
            {
                // Disable bypass Vsync
                ScalerVgipSetVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
            }
        }
    }

    // Set to digital measure
    ScalerVgipSetDigitalCaptureStatus(_ENABLE);
}

//--------------------------------------------------
// Description  : Set VGIP data path for specified display region
// Input Value  : enumDisplayRegion -> target display region
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetInputRegion(EnumDisplayRegion enumDisplayRegion)
{
    g_enumVgipInputPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Set VGIP data path for specified input path
// Input Value  : enumVgipInputPath -> target input data path
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetInputPath(EnumInputDataPath enumVgipInputPath)
{
    g_enumVgipInputPath = enumVgipInputPath;
}

#if(_FRAME_RATE_SLOW_DOWN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set VGIP safe mode, Drop IVS to Slow Down Input Frame Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgipSafeModeEnable(EnumDropIVFAction enumDropIVFAction, EnumInputDataPath enumVgipInputPath)
{
    BYTE ucIndex = 0;
    bit bEnable = (enumDropIVFAction == _DROP_IVF_ENABLE) ? _ENABLE : _DISABLE;

    if(ScalerVgipGetSafeModeStatus(enumVgipInputPath) == bEnable)
    {
        return;
    }

    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, enumVgipInputPath);

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            if(bEnable == _ENABLE)
            {
                SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT7, _BIT7);
                SET_PAGED_BIT(ucIdomainPage, P0_13_M1_VGIP_ODD_CTRL, ~_BIT4, _BIT4);
            }
            else
            {
                SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT7, 0x00);
                SET_PAGED_BIT(ucIdomainPage, P0_13_M1_VGIP_ODD_CTRL, ~_BIT4, 0x00);
            }
        }
    }

#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) == _DRR_NONE_TYPE)
#endif
    {
        // Set Frame Sync Watch Dog
        if(bEnable == _ENABLE)
        {
            SET_DIS_TIMING_GEN_WD_VTOTAL(GET_FREE_RUN_DVTOTAL() * 2 + 64);
        }
        else
        {
            SET_DIS_TIMING_GEN_WD_VTOTAL(GET_FREE_RUN_DVTOTAL() + 64);
        }

        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);
    }
}

//--------------------------------------------------
// Description  : Get VGIP safe mode enable or not
// Input Value  : enumVgipInputPath -> target input data path
// Output Value : _ture if VGIP safe mode is enable
//--------------------------------------------------
bit ScalerVgipGetSafeModeStatus(EnumInputDataPath enumVgipInputPath)
{
    if((GET_PAGED_BIT(ScalerIDomainGetInputPathPage(enumVgipInputPath), P0_11_M1_VGIP_SIGINV, _BIT7) == _BIT7) &&
       (GET_PAGED_BIT(ScalerIDomainGetInputPathPage(enumVgipInputPath), P0_13_M1_VGIP_ODD_CTRL, _BIT4) == _BIT4))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reset VGIP safe mode
// Input Value  : enumVgipInputPath -> target input data path
// Output Value : void
//--------------------------------------------------
void ScalerVgipResetSafeMode(EnumInputDataPath enumVgipInputPath)
{
    if(ScalerVgipGetSafeModeStatus(enumVgipInputPath) == _TRUE)
    {
        ScalerVgipSafeModeEnable(_DROP_IVF_DISABLE, enumVgipInputPath);
    }
}
#endif

//--------------------------------------------------
// Description  : Control VGIP capture enable status
// Input Value  : bEnable -> _TRUE to enable capture
// Output Value : None
//--------------------------------------------------
void ScalerVgipCaptureEnable(bit bEnable)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            SET_PAGED_BIT(ucIdomainPage, P0_10_M1_VGIP_CTRL, ~_BIT0, (bEnable & _BIT0));
        }
    }
}

//--------------------------------------------------
// Description  : Set VGIP VS bypass VGIP
// Input Value  : enumInputDataPath --> input data path
//                bEnable --> _ENABLE to bypass VS
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    BYTE ucSwitch = ((bEnable == _ENABLE) ? _BIT6 : 0x00);

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        // Switch VGIP VS bypass
        if((enumInputDataPath & enumCurrPath) != 0x00)
        {
            SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT6, ucSwitch);
        }
    }
}

//--------------------------------------------------
// Description  : Get VGIP VS bypass status
// Input Value  : void
// Output Value : _TRUE if VS by pass enable
//--------------------------------------------------
bit ScalerVgipGetVsBypassEnable(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        // Switch VGIP VS bypass
        if((enumInputDataPath & enumCurrPath) != 0x00)
        {
            return (GET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, _BIT6) == _BIT6);
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Modify VGIP HS/VS polarity according to measure result
// Input Value  : enumSourceType -> Input Source Type
// Output Value : None
//--------------------------------------------------
void ScalerVgipModifyPolarity(EnumSourceType enumSourceType)
{
#if(_VGA_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_VGA)
    {
        for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
            BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

            if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
            {
                // HS No Invert in VGIP
                SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT2, 0x00);

                // VS No Invert in VGIP
                SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT3, 0x00);
            }
        }
    }
    else
#endif
    {
        if(GET_SYNC_H_POLARITY() == _POSITIVE)
        {
            for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
                BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

                if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
                {
                    // HS No Invert
                    SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT2, 0x00);
                }
            }
        }
        else
        {
            for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
                BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

                if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
                {
                    // HS Invert
                    SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT2, _BIT2);
                }
            }
        }

        if((enumSourceType == _SOURCE_DP) ||
           (GET_SYNC_V_POLARITY() == _POSITIVE))
        {
            for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
                BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

                if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
                {
                    // VS No Invert
                    SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT3, 0x00);
                }
            }
        }
        else
        {
            for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
                BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

                if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
                {
                    // VS Invert
                    SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT3, _BIT3);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Set VGIP digital capture status
// Input Value  : bEnable --> _TRUE to enable digital capture
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetDigitalCaptureStatus(bit bEnable)
{
    BYTE ucEnableOption = ((bEnable == _ENABLE) ? _BIT1 : 0);

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        // Set Digital Capture
        if((GET_VGIP_INPUT_PATH() & enumCurrPath) != 0x00)
        {
            SET_PAGED_BIT(ucIdomainPage, P0_10_M1_VGIP_CTRL, ~_BIT1, ucEnableOption);
        }
    }
}

//--------------------------------------------------
// Description  : Get VGIP digital capture status
// Input Value  : None
// Output Value : _TRUE if digital capture is enabled
//--------------------------------------------------
bit ScalerVgipGetDigitalCaptureStatus(void)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if((GET_VGIP_INPUT_PATH() & enumCurrPath) != 0x00)
        {
            return (GET_PAGED_BIT(ucIdomainPage, P0_10_M1_VGIP_CTRL, _BIT1) == _BIT1);
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get VGIP Capture H Width
// Input Value  : None
// Output Value : H capture Width
//--------------------------------------------------
WORD ScalerVgipGetCaptureHWidth(void)
{
    WORD usHwidth = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            usHwidth = (((WORD)GET_PAGED_BIT(ucIdomainPage, P0_16_M1_IPH_ACT_WID_H, _BIT0) << 12) |
                        ((WORD)GET_PAGED_BIT(ucIdomainPage, P0_14_M1_IPH_ACT_STA_H, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) |
                        ((WORD)GET_PAGED_BYTE(ucIdomainPage, P0_17_M1_IPH_ACT_WID_L)));
            break;
        }
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        if(GET_VGIP_INPUT_PATH() == _INPUT_PATH_M1_M2_S1_S2)
        {
            usHwidth = (usHwidth - GET_FMTCNV_EXTENSION_LEN()) * 2;
        }
    }
#endif

    return usHwidth;
}

//--------------------------------------------------
// Description  : Set VGIP Capture H Width
// Input Value  : usIHwidth --> H capture width
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHWidth(WORD usIHwidth)
{
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(GET_VGIP_INPUT_PATH() == _INPUT_PATH_M1_M2_S1_S2)
    {
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
        {
            usIHwidth = usIHwidth / 2 + GET_FMTCNV_EXTENSION_LEN();
        }
    }
#endif

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            // Set M1 H capture width
            SET_PAGED_BIT(ucIdomainPage, P0_14_M1_IPH_ACT_STA_H, ~0xF0, ((HIBYTE(usIHwidth) & 0x0F) << 4));
            SET_PAGED_BIT(ucIdomainPage, P0_16_M1_IPH_ACT_WID_H, ~_BIT0, ((HIBYTE(usIHwidth) & 0x10) >> 4));
            SET_PAGED_BYTE(ucIdomainPage, P0_17_M1_IPH_ACT_WID_L, LOBYTE(usIHwidth));
        }
    }
}

//--------------------------------------------------
// Description  : Get VGIP Capture H-Start Position
// Input Value  : None
// Output Value : Capture H Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureHStartPosition(void)
{
    WORD usHstart = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            usHstart = (((GET_PAGED_BYTE(ucIdomainPage, P0_14_M1_IPH_ACT_STA_H) & 0x0F) << 8) |
                        (GET_PAGED_BYTE(ucIdomainPage, P0_15_M1_IPH_ACT_STA_L)));
            break;
        }
    }

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndexFromInputDataPath(GET_VGIP_INPUT_PATH());

    if((ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE) &&
       (GET_MDOMAIN_REF_INPUT_HSTART(enumRegionIndex) == _TRUE))
    {
        WORD usInputHstart = (g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.usHStart);
        WORD usInputVGIPHstart = usInputHstart / 2; // eo mode

        // H-start in analog capture starts from 2
        if(usInputVGIPHstart >= 2)
        {
            usInputVGIPHstart -= 2;
        }

        if(usHstart >= usInputVGIPHstart)
        {
            usHstart = usInputHstart + (usHstart - usInputVGIPHstart); // capture window move to the right
        }
        else
        {
            if(usInputHstart > ((usInputVGIPHstart - usHstart) << GET_D_DOMAIN_PATH()))
            {
                usHstart = usInputHstart - ((usInputVGIPHstart - usHstart) << GET_D_DOMAIN_PATH()); // capture window move to the left
            }
            else
            {
                usHstart = 0;
            }
        }
    }
    else
#endif
    {
        // H-start in analog capture starts from 2
        if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
        {
            usHstart += 2;
        }
    }

    return usHstart;
}

//--------------------------------------------------
// Description  : Set VGIP Capture H-Start Position
// Input Value  : usIHstart --> Capture H start
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHStartPosition(WORD usIHstart)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndexFromInputDataPath(GET_VGIP_INPUT_PATH());
    WORD usInputHstart = (g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.usHStart);
    WORD usHdelta = (usIHstart >= usInputHstart) ? (usIHstart - usInputHstart) : (usInputHstart - usIHstart);

    // Modify H start under analog capture
    if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
    {
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
        if((ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE) &&
           (GET_MDOMAIN_REF_INPUT_HSTART(enumRegionIndex) == _TRUE))
        {
            if(usIHstart >= usInputHstart)
            {
                usIHstart = (usInputHstart >> GET_D_DOMAIN_PATH()) + usHdelta; // capture window move to the right
            }
            else
            {
                if(usInputHstart > usHdelta)
                {
                    usIHstart = ((usInputHstart - usHdelta) >> GET_D_DOMAIN_PATH()); // capture window move to the left
                }
                else
                {
                    usIHstart = 0;
                }
            }
        }
#endif
        if(usIHstart >= 2)
        {
            usIHstart -= 2;
        }
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        WORD usCurrIHStart = usIHstart;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
        {
            switch(enumCurrPath)
            {
                case _INPUT_PATH_S1:
                case _INPUT_PATH_S2:
                    // VGIP H start = 0 for S1/S2
                    usCurrIHStart = 0;
                    break;

                default:
                    break;
            }
        }
#endif
        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            // Set M1 H capture start
            SET_PAGED_BIT(GET_IDOMAIN_REG_PAGE(ucIndex), P0_14_M1_IPH_ACT_STA_H, ~0x0F, (HIBYTE(usCurrIHStart) & 0x0F));
            SET_PAGED_BYTE(GET_IDOMAIN_REG_PAGE(ucIndex), P0_15_M1_IPH_ACT_STA_L, LOBYTE(usCurrIHStart));
        }
    }
}

//--------------------------------------------------
// Description  : Get VGIP Capture H Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD ScalerVgipGetCaptureHDelay(void)
{
    WORD usHdelay = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            usHdelay = (((WORD)GET_PAGED_BIT(ucIdomainPage, P0_1E_M1_VGIP_HV_DELAY, _BIT2) << 7) |
                        ((WORD)GET_PAGED_BIT(ucIdomainPage, P0_1E_M1_VGIP_HV_DELAY, _BIT0) << 8) |
                        (GET_PAGED_BYTE(ucIdomainPage, P0_1D_M1_IHS_DELAY)));
            break;
        }
    }

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usHdelay << 1);
    }
    else
#endif
    {
        return usHdelay;
    }
}

//--------------------------------------------------
// Description  : Set VGIP Capture V Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHDelay(WORD usIHSDelay)
{
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        usIHSDelay = 0;
    }
    else
    {
        if(usIHSDelay > _VGIP_IH_DELAY_MAX_VALUE)
        {
            ScalerIDomainFineTuneHCaptureStart(usIHSDelay - _VGIP_IH_DELAY_MAX_VALUE);

            usIHSDelay = _VGIP_IH_DELAY_MAX_VALUE;
        }
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            // Set M1 capture H delay
            SET_PAGED_BIT(ucIdomainPage, P0_1E_M1_VGIP_HV_DELAY, ~(_BIT2 | _BIT0), (((HIBYTE(usIHSDelay) & _BIT1) << 1) | (HIBYTE(usIHSDelay) & _BIT0)));
            SET_PAGED_BYTE(ucIdomainPage, P0_1D_M1_IHS_DELAY, LOBYTE(usIHSDelay));
        }
    }
}

//--------------------------------------------------
// Description  : Get VGIP Capture V-Height Position
// Input Value  : None
// Output Value : Capture Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureVHeight(void)
{
    WORD usIVheight = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            usIVheight = (((WORD)(GET_PAGED_BIT(ucIdomainPage, P0_16_M1_IPH_ACT_WID_H, _BIT7)) << 5) |
                          ((WORD)(GET_PAGED_BIT(ucIdomainPage, P0_18_M1_IPV_ACT_STA_H, 0xF0) << 4)) |
                          (GET_PAGED_BYTE(ucIdomainPage, P0_1B_M1_IPV_ACT_LEN_L)));
            break;
        }
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usIVheight << 1);
    }
    else
    {
        return usIVheight;
    }
}

//--------------------------------------------------
// Description  : Set VGIP Capture V-Height Position
// Input Value  : usIVheight --> Capture Height
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVHeight(WORD usIVheight)
{
    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        usIVheight = (usIVheight >> 1);
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            // Set M1 V capture height
            SET_PAGED_BIT(ucIdomainPage, P0_16_M1_IPH_ACT_WID_H, ~_BIT7, ((HIBYTE(usIVheight) & 0x10) << 3));
            SET_PAGED_BIT(ucIdomainPage, P0_18_M1_IPV_ACT_STA_H, ~0xF0, ((HIBYTE(usIVheight) & 0x0F) << 4));
            SET_PAGED_BYTE(ucIdomainPage, P0_1B_M1_IPV_ACT_LEN_L, LOBYTE(usIVheight));
        }
    }
}

//--------------------------------------------------
// Description  : Get VGIP Capture V-Start Position
// Input Value  : None
// Output Value : Capture Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureVStartPosition(void)
{
    WORD usIVstart = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            usIVstart = (((WORD)(GET_PAGED_BIT(ucIdomainPage, P0_16_M1_IPH_ACT_WID_H, _BIT6)) << 6) |
                         ((WORD)(GET_PAGED_BIT(ucIdomainPage, P0_18_M1_IPV_ACT_STA_H, 0x0F)) << 8) |
                         (GET_PAGED_BYTE(ucIdomainPage, P0_19_M1_IPV_ACT_STA_L)));
            break;
        }
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usIVstart << 1);
    }
    else
    {
        return usIVstart;
    }
}

//--------------------------------------------------
// Description  : Set VGIP Capture V-Start Position
// Input Value  : usIVstart --> V capture start
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVStartPosition(WORD usIVstart)
{
    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        usIVstart = (usIVstart >> 1);
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            // Set M1 V capture start
            SET_PAGED_BIT(ucIdomainPage, P0_16_M1_IPH_ACT_WID_H, ~_BIT6, ((HIBYTE(usIVstart) & 0x10) << 2));
            SET_PAGED_BIT(ucIdomainPage, P0_18_M1_IPV_ACT_STA_H, ~0x0F, (HIBYTE(usIVstart) & 0x0F));
            SET_PAGED_BYTE(ucIdomainPage, P0_19_M1_IPV_ACT_STA_L, LOBYTE(usIVstart));
        }
    }
}

//--------------------------------------------------
// Description  : Get VGIP Capture V Delay
// Input Value  : None
// Output Value : Capture V Delay
//--------------------------------------------------
WORD ScalerVgipGetCaptureVDelay(void)
{
    WORD usIVSDelay = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            usIVSDelay = (((WORD)(GET_PAGED_BIT(ucIdomainPage, P0_16_M1_IPH_ACT_WID_H, _BIT5)) << 4) |
                          ((WORD)(GET_PAGED_BIT(ucIdomainPage, P0_1E_M1_VGIP_HV_DELAY, _BIT1)) << 7) |
                          (GET_PAGED_BYTE(ucIdomainPage, P0_1C_M1_IVS_DELAY)));
            break;
        }
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usIVSDelay << 1);
    }
    else
    {
        return usIVSDelay;
    }
}

//--------------------------------------------------
// Description  : Set VGIP Capture V Delay
// Input Value  : usIVSDelay --> V Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVDelay(WORD usIVSDelay)
{
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        usIVSDelay = 0;
    }
    else
    {
        if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
        {
            usIVSDelay = (usIVSDelay >> 1);
        }
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(CHK_VGIP_INPUT_PATH(enumCurrPath) == _TRUE)
        {
            // Set M1 capture V delay
            SET_PAGED_BIT(ucIdomainPage, P0_16_M1_IPH_ACT_WID_H, ~_BIT5, ((HIBYTE(usIVSDelay) & _BIT1) << 4));
            SET_PAGED_BIT(ucIdomainPage, P0_1E_M1_VGIP_HV_DELAY, ~_BIT1, ((HIBYTE(usIVSDelay) & _BIT0) << 1));
            SET_PAGED_BYTE(ucIdomainPage, P0_1C_M1_IVS_DELAY, LOBYTE(usIVSDelay));
        }
    }
}

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Clear VGIP Interlace flag
// Input Value  : enumInputDataPath -> target input path
// Output Value : None
//--------------------------------------------------
void ScalerVgipClearInterlaceFlag(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if((enumCurrPath & enumInputDataPath) != 0)
        {
            // Clear VGIP Interlace Toggle Flag
            SET_PAGED_BIT(ucIdomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        }
    }
}
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
//--------------------------------------------------
// Description  : Set VGIP Double Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgipDoubleBufferEnable(EnumInputDataPath enumSelectedDataPath, bit bEnable)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ucIndex++)
    {
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);
        EnumInputDataPath enumChkPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumSelectedDataPath & enumChkPath) == enumChkPath)
        {
            if(bEnable == _ENABLE)
            {
                SET_PAGED_BIT(ucIdomainPage, P0_10_M1_VGIP_CTRL, ~(_BIT5 | _BIT4), _BIT4);
            }
            else
            {
                SET_PAGED_BIT(ucIdomainPage, P0_10_M1_VGIP_CTRL, ~(_BIT5 | _BIT4), 0x00);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Apply VGIP Double Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgipVgipDoubleBufferApply(EnumDBApply enumDBApply)
{
    if(enumDBApply != _DB_APPLY_NONE)
    {
        DWORD ulVgipPage = P0_10_M1_VGIP_CTRL;
        BYTE uccnt = 0;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        BYTE ucmaxpage = 4;
#else
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        BYTE ucmaxpage = 2;
#else
        BYTE ucmaxpage = 1;
#endif
#endif
        for(uccnt = 0; uccnt < ucmaxpage; ulVgipPage += _REG_PAGE_OFFSET)
        {
            // Check if VGIP DB is enabled
            if(ScalerGetBit(ulVgipPage, _BIT4) == 0x00)
            {
                return;
            }

            // Check I domain status
            if(ScalerGetBit(ulVgipPage, _BIT0) == 0x00)
            {
                // Disable Double Buffer
                ScalerSetBit(ulVgipPage, ~_BIT4, 0x00);
                return;
            }

            // Apply VGIP Double Buffer
            ScalerSetBit(ulVgipPage, ~_BIT5, _BIT5);

            if(enumDBApply == _DB_APPLY_POLLING)
            {
                // Wait VGIP double buffer
                if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, ulVgipPage, _BIT5, 0) == _FALSE)
                {
                    // Disable Double Buffer
                    ScalerSetBit(ulVgipPage, ~_BIT4, 0x00);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get VGIP Double Buffer Status
// Input Value  : None
// Output Value : EnumVGIPDBEnableStatus
//--------------------------------------------------
EnumVGIPDBEnableStatus ScalerVgipGetVGIPDBStatus(void)
{
    EnumVGIPDBEnableStatus enumDBEnableStatus = _VGIP_DB_DISABLE;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ucIndex++)
    {
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if(GET_PAGED_BIT(ucIdomainPage, P0_10_M1_VGIP_CTRL, _BIT4) == _BIT4)
        {
            enumDBEnableStatus |= GET_VGIP_DB_STATUS(ucIndex);
        }
    }

    return enumDBEnableStatus;
}
#endif

