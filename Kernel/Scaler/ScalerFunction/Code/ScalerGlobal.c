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
// ID Code      : ScalerGlobal.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GLOBAL__

#include "ScalerFunctionInclude.h"
#include "Global/ScalerGlobal.h"

#if((_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT) || (_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_IRQ_BACKGROUND))
#if((_MULTI_DISPLAY_MAX > 1) && (_EAGLE_SIGHT_SUPPORT == _OFF))
#warning "NOTE: _GARBAGE_PREVENT_BY_BACKLIGHT and _GARBAGE_PREVENT_BY_IRQ_BACKGROUND only work when _DISPLAY_1P_MODE !!!"
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructEnumGlobalLock g_stGlobalLock;

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
volatile StructGlobalIntFuncForIDomain g_pstGlobalIntFuncForIDomain[_HW_I_DOMAIN_PATH_COUNT];
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
volatile StructGlobalIntFuncForDDomain g_stGlobalIntFuncForDDomain;
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
EnumGlobalIDBApplyPoint g_enumGlobalIDBApplyPoint = _GLOBAL_APPLY_I;
#endif

#if(_FW_CPU32_USE_INT31_FOR_SCALER_INT == _OFF)
volatile bit g_bGlobalIrqEnableStatus;
#endif

//****************************************************************************
// IN-LINE FUNCTION DECLARATIONS
//****************************************************************************
extern inline bit ScalerGlobalGetFrontBackStatus(EnumFrontBackStatusPosition enumFrontBackStatusPosition);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Scaler Whole Chip Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalWholeChipReset(void)
{
    // Whole chip reset
    ScalerSetBit(P0_01_HOST_CTRL, ~_BIT0, _BIT0);

    // For Delay 10 ms
    ScalerTimerDelayXms(10);

    // Clear to 0
    ScalerSetBit(P0_01_HOST_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : Global display initial process
// Input Value  : enumDisplayMode --> display mode
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDisplayInitial(EnumDisplayMode enumDisplayMode)
{
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < _MULTI_DISPLAY_MAX; ++ucRegionIndex)
    {
#if(_FRC_SUPPORT == _ON)
        // Clear FRC Control Param Index
        CLR_MDOMAIN_FRC_CTRL_PARAM_INDEX(ucRegionIndex);
#endif
        CLR_MDOMAIN_REF_INPUT_HSTART(ucRegionIndex);
    }

#if(_FRC_SUPPORT == _ON)
#if(_HDMI21_ALLM_SUPPORT == _ON)
    CLR_FRC_ALLM_ON_STATUS();
    CLR_FRC_ALLM_INPUT_PORT();
#endif
#endif

    enumDisplayMode = enumDisplayMode;

    // Disable Sub Active for pbplr full screen mode
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
    if(ScalerDDomainGetPbplrFullStatus() == _TRUE)
    {
        ScalerDDomainSetPbplrSubDisable();
    }
#endif

#if(_HW_IMD_POWER_CUT_INDEPENDENT_SUPPORT == _ON)
    ScalerPowerDisplayInitialSetting(enumDisplayMode);
#endif
    // Set scaling initial setting
    ScalerScalingSetInitial();

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    ScalerScalingSetExtensionRecaptureInitial();
#endif

    // Use information form Frame-Sync Mode
    ScalerFRCSetSourceSelect(_INPUT_PATH_ALL, _DDOMAIN_SRC_FROM_FRAME_SYNC_MODE);

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        SET_MODE_DISPLAY_TARGET_INDEX(ucRegionIndex);
        ScalerFRCSetCapDispChannel(GET_MODE_DISPLAY_TARGET_REGION());
        ScalerFRCSetChannelClient(GET_MODE_DISPLAY_TARGET_REGION());
    }


#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
    ScalerMemoryBwAllocation();
    ScalerMemorySpaceAllocation();

    // Disable FRC
    ScalerFRCEn(_FRC_ALL_ONOFF, _INPUT_PATH_ALL, _DISABLE);
#if(_FRC_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    ScalerFRCEOtoFBControl(_INPUT_PATH_ALL, GET_MDOMAIN_INPUT_HWIDTH(), _DISABLE);
    ScalerFRCFBtoEOControl(_INPUT_PATH_ALL, GET_MDOMAIN_INPUT_HWIDTH() / 2, _DISABLE);
#endif
    // Set FRC Pre-Read
    ScalerFRCSetPreRead(_INPUT_PATH_ALL);
#if(_OD_FUNCTION == _ON)
    // Release all FRC bandwidth
    ScalerMDomainReleaseFRCMemoryBW(_INPUT_PATH_NONE);
#endif
#endif
#endif

#if(_OD_FUNCTION == _ON)
    ScalerMDomainODFlagInitial();
#endif

#if(_HW_GLOBAL_WD_MAPPING_SUPPORT == _ON)
    // Update watchdog mapping
    ScalerGlobalSetWatchDogMapping(enumDisplayMode);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Set DB sync mode
    ScalerGlobalSetDBSyncMode();
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    SET_I_DB_APPLY_POINT(_GLOBAL_APPLY_I);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    ScalerDDomainSetR2DenEnable(_ENABLE, _DB_APPLY_POLLING);
#endif
}

//--------------------------------------------------
// Description  : Set Scaler All IRQ(INT31) Enable Status
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetInt31EnableStatus(bit bEn)
{
#if(_FW_CPU32_USE_INT31_FOR_SCALER_INT == _ON)
    if(bEn == _ENABLE)
    {
        ScalerSetBit(P0_0C_IRQ_WATCH_DOG_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P0_0C_IRQ_WATCH_DOG_CTRL, ~_BIT0, 0x00);
    }
#else
    if(bEn == g_bGlobalIrqEnableStatus)
    {
        return;
    }
    g_bGlobalIrqEnableStatus = bEn;

    if(bEn == _ENABLE)
    {
        for(DWORD ulIdx = 0; ulIdx < _SCALER_ALL_IRQ_UNION_NUM; ulIdx++)
        {
            ScalerCpuHalEnableIRQ(tScalerAllIrqUnion[ulIdx]);
        }
    }
    else
    {
        for(DWORD ulIdx = 0; ulIdx < _SCALER_ALL_IRQ_UNION_NUM; ulIdx++)
        {
            ScalerCpuHalDisableIRQ(tScalerAllIrqUnion[ulIdx]);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Scaler All IRQ(INT31) Enable Status
// Input Value  : None
// Output Value : _ENABLE/_DISABLE
//--------------------------------------------------
bit ScalerGlobalGetInt31EnableStatus(void)
{
#if(_FW_CPU32_USE_INT31_FOR_SCALER_INT == _ON)
    return (((ScalerGetByte(P0_0C_IRQ_WATCH_DOG_CTRL) & _BIT0) == _BIT0) ? _ENABLE : _DISABLE);
#else
    return g_bGlobalIrqEnableStatus;
#endif
}

//--------------------------------------------------
// Description  : Add Input Port Mapping
// Input Value  : enumInputPort --> Input Port
//                enumDDomainRegion --> display data path
// Output Value : None
//--------------------------------------------------
void ScalerGlobalAddPortMapping(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion)
{
    enumDDomainRegion = enumDDomainRegion;

    DebugMessageSystem("Add: port mapping", (((WORD)enumInputPort << 8) | enumDDomainRegion));

    // Update source-data path mapping
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:

            break;
#endif


#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if(_D0_HDMI_SUPPORT == _ON)
            SET_TMDS_RX0_FORCE_BCKGRD_PATH(enumDDomainRegion);
#endif

#if(_D0_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxForceBckgrdPath(_D0_INPUT_PORT, enumDDomainRegion);
#endif
            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxForceBckgrdPath(_D1_INPUT_PORT, enumDDomainRegion);
#endif

#if(_D1_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxForceBckgrdPath(_D1_INPUT_PORT, enumDDomainRegion);
#endif
            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxForceBckgrdPath(_D2_INPUT_PORT, enumDDomainRegion);
#endif

#if(_D2_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxForceBckgrdPath(_D2_INPUT_PORT, enumDDomainRegion);
#endif
            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxForceBckgrdPath(_D3_INPUT_PORT, enumDDomainRegion);
#endif

            break;
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_D4_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxForceBckgrdPath(_D4_INPUT_PORT, enumDDomainRegion);
#endif

            break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if(_D5_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxForceBckgrdPath(_D5_INPUT_PORT, enumDDomainRegion);
#endif
            break;
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            ScalerDpMacStreamRxForceBckgrdPath(GET_DUAL_DP_PORT_SWITCH_SELECT(), enumDDomainRegion);

            break;
#endif // End of #if(_DUAL_DP_SUPPORT == _ON)

#if((_DP_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        case _D9_INPUT_PORT:

            ScalerDpMacStreamRxForceBckgrdPath(_D9_INPUT_PORT, enumDDomainRegion);

            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Remove Input Port Mapping
// Input Value  : enumInputPort --> Input Port
//                enumDisplayDataPath --> display data path
// Output Value : None
//--------------------------------------------------
void ScalerGlobalRemovePortMapping(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion)
{
    enumDDomainRegion = enumDDomainRegion;

    DebugMessageSystem("Remove: port mapping", (((WORD)enumInputPort << 8) | enumDDomainRegion));

    // Update source-data path mapping
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:

            break;
#endif


#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if(_D0_HDMI_SUPPORT == _ON)
            CLR_TMDS_RX0_FORCE_BCKGRD_PATH(enumDDomainRegion);
#endif

#if(_D0_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxClrForceBckgrdPath(_D0_INPUT_PORT, enumDDomainRegion);
#endif
            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxClrForceBckgrdPath(_D1_INPUT_PORT, enumDDomainRegion);
#endif

#if(_D1_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxClrForceBckgrdPath(_D1_INPUT_PORT, enumDDomainRegion);
#endif
            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxClrForceBckgrdPath(_D2_INPUT_PORT, enumDDomainRegion);
#endif

#if(_D2_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxClrForceBckgrdPath(_D2_INPUT_PORT, enumDDomainRegion);
#endif
            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxClrForceBckgrdPath(_D3_INPUT_PORT, enumDDomainRegion);
#endif

            break;
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_D4_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxClrForceBckgrdPath(_D4_INPUT_PORT, enumDDomainRegion);
#endif

            break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if(_D5_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxClrForceBckgrdPath(_D5_INPUT_PORT, enumDDomainRegion);
#endif
            break;
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            ScalerDpMacStreamRxClrForceBckgrdPath(_DUAL_DP_INPUT_PORT, enumDDomainRegion);

            break;
#endif // End of #if(_DUAL_DP_SUPPORT == _ON)

#if((_DP_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        case _D9_INPUT_PORT:

            ScalerDpMacStreamRxClrForceBckgrdPath(_D9_INPUT_PORT, enumDDomainRegion);

            break;
#endif // End of #if(_DP_MST_PXP_MODE_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Reset port mapping
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalResetPortMapping(void)
{
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#if(_D0_HDMI_SUPPORT == _ON)
    CLR_TMDS_RX0_FORCE_BCKGRD_PATH(_DDOMAIN_RGN_ALL);
#endif

#if(_D0_DP_SUPPORT == _ON)
    ScalerDpMacStreamRxClrForceBckgrdPath(_D0_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#if(_D1_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxClrForceBckgrdPath(_D1_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif

#if(_D1_DP_SUPPORT == _ON)
    ScalerDpMacStreamRxClrForceBckgrdPath(_D1_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#if(_D2_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxClrForceBckgrdPath(_D2_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif

#if(_D2_DP_SUPPORT == _ON)
    ScalerDpMacStreamRxClrForceBckgrdPath(_D2_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#if(_D3_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxClrForceBckgrdPath(_D3_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#if(_D4_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxClrForceBckgrdPath(_D4_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#if(_D5_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxClrForceBckgrdPath(_D5_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

#if(_DUAL_DP_SUPPORT == _ON)
    ScalerDpMacStreamRxClrForceBckgrdPath(_DUAL_DP_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif // End of #if(_DUAL_DP_SUPPORT == _ON)

#if((_DP_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    ScalerDpMacStreamRxClrForceBckgrdPath(_D9_INPUT_PORT, _DDOMAIN_RGN_ALL);
#endif // End of #if(_DP_MST_PXP_MODE_SUPPORT == _ON)

}

#if(_HW_GLOBAL_WD_MAPPING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set WD mapping between I/D domains
// Input Value  : display mode
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetWatchDogMapping(EnumDisplayMode enumDisplayMode)
{
    switch(enumDisplayMode)
    {
        case _DISPLAY_MODE_1P:
            // Map M1/M2 to R1_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
            // Map S1/S2 to R1_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                // Map S3/S4 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x48);
#endif
            }
            else
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x48);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            }
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                // Map S3/S4 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x48);
#endif
            }
            else
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x48);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            }
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                // Map S3/S4 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x48);
#endif
            }
            else
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x48);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            }
            break;

        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                // Map S3/S4 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x48);
#endif
            }
            else
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x48);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            }
            break;

        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                // Map S3/S4 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x48);
#endif
            }
            else
            {
                // Map M1/M2 to R1_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
                // Map S1/S2 to R2_a1
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x48);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            // Map M1/M2 to R1_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
            // Map S1/S2 to R1_a2
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x24);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            // Map M1/M2 to R2_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x48);
            // Map S1/S2 to R3_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x90);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            // Map S3/S4 to R1_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
            // Map M1/M2 to R1_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
            // Map S1/S2 to R2_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x48);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            // Map S3/S4 to R2_a2
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x6C);
#endif
            break;

        case _DISPLAY_MODE_3P_SKEW_R:
            // Map M1/M2 to R2_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x48);
            // Map S1/S2 to R1_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            // Map S3/S4 to R1_a2
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x24);
#endif
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
            // Map M1/M2 to R1_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
            // Map S1/S2 to R1_a2
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x24);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            // Map S3/S4 to R2_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x48);
#endif
            break;

        case _DISPLAY_MODE_3P_SKEW_B:
            // Map M1/M2 to R1_a2
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x24);
            // Map S1/S2 to R1_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            // Map S3/S4 to R2_a1
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x48);
#endif
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            // Map M1 to R1_a1, M2 to R1_a2
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x04);
            // Map S1 to R2_a1, S2 to R2_a2
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x4C);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            // S3/S4 default
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            break;
#endif

        default:
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_49_I_D_MAPPING_M1_M2, 0x00);
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4A_I_D_MAPPING_S1_S2, 0x00);

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_I_D_MAPPING_S3_S4, 0x00);
#endif
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Select internal oscillator Clock.
// Input Value  : IOSC/ Xtal
// Output Value : None
//--------------------------------------------------
void ScalerGlobalCrystalClkSel(EnumClkSel enumSel)
{
    if(enumSel == _IOSC_CLK)
    {
        // Select at internal Xtal.
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT3, _BIT3);
    }
    else if(enumSel == _EXT_XTAL_CLK)
    {
        // Select at external Xtal.
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Initialize OSD Position Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalOsdInitial(void)
{
    OSD_SET_INITIAL();

    ScalerOsdWriteAllByte(_OSD_SRAM, 0x00, 0x00, 0x00, 0x00);

    ScalerOsdGlobalDoubleBufferSel(_OSD_DB_DISABLE);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerOsdSetFBFirstBlock(_OSD_BACK, _OFF);
        ScalerOsdSetFBFirstStartAddr(_OSD_BACK, _PANEL_DH_WIDTH / 2);
    }
#endif

#if(_HW_FOSD_REFER_CAP_WIN_BACKGROUND_SUPPORT == _ON)
    ScalerOsdSetReferCapWinBackground(_ENABLE);
#endif

#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
    ScalerOsdSetOsdTimingGenDBEnable(_ENABLE);
#endif

#if(_D_DITHER_FUNCTION == _ON)
#if(_D_DITHER_FREERUN_EN_SUPPORT == _ENABLE)
    // Reset DDither By Enable Rising Edge Signal
    ScalerColorDDitherEnable(_FUNCTION_OFF);
    ScalerColorDDitherEnable(_FUNCTION_ON);
#endif
#endif

#if(_HW_GOSD_SUPPORT == _ON)
#if(_GOSD_SUPPORT == _OFF)
    ScalerOsdSubBlendingSetBypassFosdEnable(_ENABLE);
#else
    ScalerOsdSetTransparency(0xFF);
    ScalerGosdDispOsdClkSelect();
    ScalerOsdSubBlendingSetBypassFosdEnable(_DISABLE);
    ScalerOsdSubBlendingSetFosdMixerEnable(_ENABLE);
    ScalerOsdSubBlendingSetGosdMixerEnable(_ENABLE);
#endif
#endif

    ScalerSetBit(P3A_E0_OSD_TIMING_DUMMY, ~_BIT0, (_BIT0));
}

//--------------------------------------------------
// Description  : Global Reset Event
// Input Value  : ucResetTarget --> Reset target action
// Output Value : None
//--------------------------------------------------
void ScalerGlobalResetProc(BYTE ucResetTarget)
{
    switch(ucResetTarget)
    {
        case _MODE_ACTION_RESET_TO_DISPLAY_INITIAL:

            // Set Background Color to Black
            ScalerDDomainBackgroundSetColor(_DDOMAIN_RGN_ALL, 0, 0, 0, _DB_APPLY_NO_POLLING);
            ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _ENABLE);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            ScalerColorPIPBlendingLevelAdjust(0x00, _DB_APPLY_NO_POLLING);
#endif

            // Disable WD
            ScalerGlobalDisableAllWatchDog();

            // Reset port mapping data path
            ScalerGlobalResetPortMapping();

            // Reset I-domain
            ScalerIDomainResetDataPath(_INPUT_PATH_ALL);

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, _INPUT_PATH_ALL, _DISABLE);
#endif

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING:

            // Set Background Color to Black
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            ScalerDDomainBackgroundSetColor(GET_MDOMAIN_OUTPUT_RGN(), 0, 0, 0, _DB_APPLY_NO_POLLING);
            ScalerDDomainBackgroundEnable(GET_MDOMAIN_OUTPUT_RGN(), _ENABLE);
            ScalerGlobalPathWatchDog(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
            ScalerGlobalDoubleBufferConfigReset();
#endif

#if(_FRC_SUPPORT == _ON)
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE) // for aspect ratio
            {
                ScalerFRCChannelMuteDTGEnable(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_OUTPUT_RGN(), GET_MODE_DISPLAY_TARGET_REGION(), _DISABLE);
                ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()), _DB_APPLY_POLLING);
            }
#endif

#if(_OD_FUNCTION == _ON)
            // Release FRC bandwidth
            ScalerMDomainReleaseFRCMemoryBW(GET_MDOMAIN_INPUT_DATA_PATH());
#endif
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
#endif

            break;


        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG:

            ScalerGlobalPathWatchDog(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);

#if((_FRC_SUPPORT == _ON) && (_OD_FUNCTION == _ON))
            // Release FRC bandwidth
            ScalerMDomainReleaseFRCMemoryBW(GET_MDOMAIN_INPUT_DATA_PATH());
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
#endif
#if(_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
            if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
            {
                EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));
                ScalerFRCSetChannelBlkNum(enumChannelSel, (_FRC_CAP | _FRC_DISP), _MEMORY_2_FRAME_BUFFER);
            }
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
            ScalerGlobalDoubleBufferSwitchtoIMDDB();
#endif

            break;

        case _MODE_ACTION_RESET_TO_POWER_SAVING:
        case _MODE_ACTION_RESET_TO_POWER_OFF:

            // Reset OSD Setting
            ScalerOsdReset();

            // Disable WD
            ScalerGlobalDisableAllWatchDog();

            // Reset all interface block WD/Irq/Timer Event....
            ScalerSyncResetAllProc();

            // Reset timing info
            ScalerMeasureResetAllTimingInfo();

            // Reset port mapping data path
            ScalerGlobalResetPortMapping();

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, _INPUT_PATH_ALL, _DISABLE);
#endif

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_CHECK:
            break;

        case _MODE_ACTION_RESET_TO_FACTORY_MODE:

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, _INPUT_PATH_ALL, _DISABLE);
#endif

            break;

        default:
            break;
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    ScalerRotationSetEnable(_DISABLE);
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
    ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_ALL_FUNCTION, _DISABLE);
#endif
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerGlobalFirstActiveProc(EnumSourceType enumSourceType, BYTE ucGetInputPort, EnumDisplayRegion enumDisplayRegion)
{
    // Add port mapping to display data path
    ScalerGlobalAddPortMapping(ucGetInputPort, GET_MDOMAIN_OUTPUT_RGN());

    // Enable Watch Dog
    ScalerGlobalPathWatchDog(ScalerRegionGetInputDataPath(enumDisplayRegion), _ENABLE);

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Enable Vga Top Double Buffer
            ScalerVgaTopDoubleBufferEnable(_ENABLE);

            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            switch(ucGetInputPort)
            {
#if(_D0_HDMI_SUPPORT == _ON)
                case _D0_INPUT_PORT:
                    ScalerTMDSRx0FirstActiveProc(enumSourceType);
                    break;
#endif


#if(_D1_HDMI_SUPPORT == _ON)
                case _D1_INPUT_PORT:
                    ScalerTmdsMacRxFirstActiveProc(_D1_INPUT_PORT, enumSourceType);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(_D1_INPUT_PORT) != _DSC_MAC_NONE)
                    {
                        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(_D1_INPUT_PORT);

                        // Enable DSC Fifo Under/OverFlow Watch Dog
                        ScalerDscDecoderSetFifoWD(ucDscMac, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow IRQ
                        ScalerDscDecoderSetFifoIRQ(ucDscMac, _ENABLE);
                    }
#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncHdmiGetEnable(_D1_INPUT_PORT) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif
                    break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
                case _D2_INPUT_PORT:
                    ScalerTmdsMacRxFirstActiveProc(_D2_INPUT_PORT, enumSourceType);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(_D2_INPUT_PORT) != _DSC_MAC_NONE)
                    {
                        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(_D2_INPUT_PORT);

                        // Enable DSC Fifo Under/OverFlow Watch Dog
                        ScalerDscDecoderSetFifoWD(ucDscMac, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow IRQ
                        ScalerDscDecoderSetFifoIRQ(ucDscMac, _ENABLE);
                    }
#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncHdmiGetEnable(_D2_INPUT_PORT) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif
                    break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
                case _D3_INPUT_PORT:
                    ScalerTmdsMacRxFirstActiveProc(_D3_INPUT_PORT, enumSourceType);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(_D3_INPUT_PORT) != _DSC_MAC_NONE)
                    {
                        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(_D3_INPUT_PORT);

                        // Enable DSC Fifo Under/OverFlow Watch Dog
                        ScalerDscDecoderSetFifoWD(ucDscMac, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow IRQ
                        ScalerDscDecoderSetFifoIRQ(ucDscMac, _ENABLE);
                    }
#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncHdmiGetEnable(_D3_INPUT_PORT) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif
                    break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
                case _D4_INPUT_PORT:
                    ScalerTmdsMacRxFirstActiveProc(_D4_INPUT_PORT, enumSourceType);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(_D4_INPUT_PORT) != _DSC_MAC_NONE)
                    {
                        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(_D4_INPUT_PORT);

                        // Enable DSC Fifo Under/OverFlow Watch Dog
                        ScalerDscDecoderSetFifoWD(ucDscMac, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow IRQ
                        ScalerDscDecoderSetFifoIRQ(ucDscMac, _ENABLE);
                    }
#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncHdmiGetEnable(_D4_INPUT_PORT) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif
                    break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
                case _D5_INPUT_PORT:
                    ScalerTmdsMacRxFirstActiveProc(_D5_INPUT_PORT, enumSourceType);

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncHdmiGetEnable(_D5_INPUT_PORT) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif
                    break;
#endif

                default:
                    break;
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            switch(ucGetInputPort)
            {
#if(_D0_DP_SUPPORT == _ON)

                case _D0_INPUT_PORT:

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(_D0_INPUT_PORT) != _DSC_MAC_NONE)
                    {
                        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(_D0_INPUT_PORT);

                        // Enable DSC VB-ID[6] Watch Dog and IRQ
                        ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D0_INPUT_PORT, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow Watch Dog
                        ScalerDscDecoderSetFifoWD(ucDscMac, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow IRQ
                        ScalerDscDecoderSetFifoIRQ(ucDscMac, _ENABLE);
                    }
                    else
#endif
                    {
                        // Enable DP Fifo Under/OverFlow Watch Dog
                        ScalerDpMacStreamRxSetFifoWD(_D0_INPUT_PORT, _ENABLE);

                        // Enable DP overflow/ underflow IRQ
                        ScalerDpMacStreamRxSetFifoIRQ(_D0_INPUT_PORT, _ENABLE);
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                        if(ScalerDpMacStreamRxDscGetFlagStatus(ScalerDpRxDxMacSourceMapping(_D0_INPUT_PORT)) == _TRUE)
                        {
                            // Enable DSC VB-ID[6] Watch Dog and IRQ
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D0_INPUT_PORT, _ENABLE);
                        }
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
                        if(ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck() == _TRUE)
                        {
                            ScalerDpMacStreamRxSetColorSpaceChangeWD(_D0_INPUT_PORT, _ENABLE);
                        }
                        else
                        {
                            if(ScalerDpMacStreamRxMsaMiscChangeSupportCheck(_D0_INPUT_PORT) == _ON)
                            {
                                // Enable DP Msa Change IRQ
                                ScalerDpMacStreamRxSstSetMsaChangeIRQ(_D0_INPUT_PORT, _ENABLE);
                            }
                        }
#endif
                    }

                    // Enable DP BS Miss Detect IRQ
                    ScalerDpMacStreamRxSetBsMissDetectIRQ(_D0_INPUT_PORT, _ENABLE);

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
#if(_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if(ScalerDpAuxRxGetCodingType(_D0_INPUT_PORT) == _CODING_TYPE_8B10B)
#endif
                    {
                        // Enable DP 8b10b Decoder Error WD
                        ScalerDpMacDphyRxSet8b10bDecErrorWD(_D0_INPUT_PORT, _ENABLE);
                    }
#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncDpGetEnable(_D0_INPUT_PORT) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif

                    break;
#endif

#if(_D1_DP_SUPPORT == _ON)
                case _D1_INPUT_PORT:

#if(_DP_PR_MODE_SUPPORT == _ON)
                    if(ScalerDpAuxRxGetDpcdBitInfo(_D1_INPUT_PORT, 0x00, 0x02, 0x05, _BIT0) == 0x00)
                    {
                        // Set DP Receive Port0 In Sync
                        ScalerDpAuxRxSinkStatusSet(_D1_INPUT_PORT, _DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
                    }
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(_D1_INPUT_PORT) != _DSC_MAC_NONE)
                    {
                        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(_D1_INPUT_PORT);

                        // Enable DSC VB-ID[6] Watch Dog and IRQ
                        ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D1_INPUT_PORT, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow Watch Dog
                        ScalerDscDecoderSetFifoWD(ucDscMac, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow IRQ
                        ScalerDscDecoderSetFifoIRQ(ucDscMac, _ENABLE);
                    }
                    else
#endif
                    {
                        // Enable DP Fifo Under/OverFlow Watch Dog
                        ScalerDpMacStreamRxSetFifoWD(_D1_INPUT_PORT, _ENABLE);

                        // Enable DP overflow/ underflow IRQ
                        ScalerDpMacStreamRxSetFifoIRQ(_D1_INPUT_PORT, _ENABLE);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                        if(ScalerDpMacStreamRxDscGetFlagStatus(ScalerDpRxDxMacSourceMapping(_D1_INPUT_PORT)) == _TRUE)
                        {
                            // Enable DSC VB-ID[6] Watch Dog and IRQ
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D1_INPUT_PORT, _ENABLE);
                        }
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
                        if(ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck() == _TRUE)
                        {
                            ScalerDpMacStreamRxSetColorSpaceChangeWD(_D1_INPUT_PORT, _ENABLE);
                        }
                        else
                        {
                            if(ScalerDpMacStreamRxMsaMiscChangeSupportCheck(_D1_INPUT_PORT) == _ON)
                            {
                                // Enable DP Msa Change IRQ
                                ScalerDpMacStreamRxSstSetMsaChangeIRQ(_D1_INPUT_PORT, _ENABLE);
                            }
                        }
#endif
                    }

                    // Enable DP BS Miss Detect IRQ
                    ScalerDpMacStreamRxSetBsMissDetectIRQ(_D1_INPUT_PORT, _ENABLE);

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
#if(_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if(ScalerDpAuxRxGetCodingType(_D1_INPUT_PORT) == _CODING_TYPE_8B10B)
#endif
                    {
                        // Enable DP 8b10b Decoder Error WD
                        ScalerDpMacDphyRxSet8b10bDecErrorWD(_D1_INPUT_PORT, _ENABLE);
                    }
#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncDpGetEnable(_D1_INPUT_PORT) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif

                    break;
#endif

#if(_D2_DP_SUPPORT == _ON)
                case _D2_INPUT_PORT:

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(_D2_INPUT_PORT) != _DSC_MAC_NONE)
                    {
                        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(_D2_INPUT_PORT);

                        // Enable DSC VB-ID[6] Watch Dog and IRQ
                        ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D2_INPUT_PORT, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow Watch Dog
                        ScalerDscDecoderSetFifoWD(ucDscMac, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow IRQ
                        ScalerDscDecoderSetFifoIRQ(ucDscMac, _ENABLE);
                    }
                    else
#endif
                    {
                        // Enable DP Fifo Under/OverFlow Watch Dog
                        ScalerDpMacStreamRxSetFifoWD(_D2_INPUT_PORT, _ENABLE);

                        // Enable DP overflow/ underflow IRQ
                        ScalerDpMacStreamRxSetFifoIRQ(_D2_INPUT_PORT, _ENABLE);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                        if(ScalerDpMacStreamRxDscGetFlagStatus(ScalerDpRxDxMacSourceMapping(_D2_INPUT_PORT)) == _TRUE)
                        {
                            // Enable DSC VB-ID[6] Watch Dog and IRQ
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D2_INPUT_PORT, _ENABLE);
                        }
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
                        if(ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck() == _TRUE)
                        {
                            ScalerDpMacStreamRxSetColorSpaceChangeWD(_D2_INPUT_PORT, _ENABLE);
                        }
                        else
                        {
                            if(ScalerDpMacStreamRxMsaMiscChangeSupportCheck(_D2_INPUT_PORT) == _ON)
                            {
                                // Enable DP Msa Change IRQ
                                ScalerDpMacStreamRxSstSetMsaChangeIRQ(_D2_INPUT_PORT, _ENABLE);
                            }
                        }
#endif
                    }

                    // Enable DP BS Miss Detect IRQ
                    ScalerDpMacStreamRxSetBsMissDetectIRQ(_D2_INPUT_PORT, _ENABLE);

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
#if(_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if(ScalerDpAuxRxGetCodingType(_D2_INPUT_PORT) == _CODING_TYPE_8B10B)
#endif
                    {
                        // Enable DP 8b10b Decoder Error WD
                        ScalerDpMacDphyRxSet8b10bDecErrorWD(_D2_INPUT_PORT, _ENABLE);
                    }

#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncDpGetEnable(_D2_INPUT_PORT) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif

                    break;
#endif


#if(_DUAL_DP_SUPPORT == _ON)
                case _DUAL_DP_INPUT_PORT:

                    // Enable DP Fifo Under/OverFlow Watch Dog
                    ScalerDpMacStreamRxSetFifoWD(GET_DUAL_DP_PORT_SWITCH_SELECT(), _ENABLE);

                    // Enable DP overflow/ underflow IRQ
                    ScalerDpMacStreamRxSetFifoIRQ(GET_DUAL_DP_PORT_SWITCH_SELECT(), _ENABLE);

                    // Enable DP BS Miss Detect IRQ
                    ScalerDpMacStreamRxSetBsMissDetectIRQ(GET_DUAL_DP_PORT_SWITCH_SELECT(), _ENABLE);

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if(ScalerDpAuxRxGetCodingType(GET_DUAL_DP_PORT_SWITCH_SELECT()) == _CODING_TYPE_8B10B)
#endif
                    {
                        // Enable DP 8b10b Decoder Error WD
                        ScalerDpMacDphyRxSet8b10bDecErrorWD(GET_DUAL_DP_PORT_SWITCH_SELECT(), _ENABLE);
                    }

#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
                    if(ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck() == _TRUE)
                    {
                        ScalerDpMacStreamRxSetColorSpaceChangeWD(GET_DUAL_DP_PORT_SWITCH_SELECT(), _ENABLE);
                    }
                    else
                    {
                        if(ScalerDpMacStreamRxMsaMiscChangeSupportCheck(GET_DUAL_DP_PORT_SWITCH_SELECT()) == _ON)
                        {
                            // Enable DP Msa Change IRQ
                            ScalerDpMacStreamRxSstSetMsaChangeIRQ(GET_DUAL_DP_PORT_SWITCH_SELECT(), _ENABLE);
                        }
                    }
#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
                    if(ScalerDrrFreeSyncDpGetEnable(GET_DUAL_DP_PORT_SWITCH_SELECT()) == _TRUE)
                    {
                        ScalerSyncDrrDataExchangeProc(_ENABLE);
                    }
#endif

                    break;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
                case _D9_INPUT_PORT:

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(_D9_INPUT_PORT) != _DSC_MAC_NONE)
                    {
                        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(_D9_INPUT_PORT);

                        // Enable DSC VB-ID[6] Watch Dog and IRQ
                        ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D9_INPUT_PORT, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow Watch Dog
                        ScalerDscDecoderSetFifoWD(ucDscMac, _ENABLE);

                        // Enable DSC Fifo Under/OverFlow IRQ
                        ScalerDscDecoderSetFifoIRQ(ucDscMac, _ENABLE);
                    }
                    else
#endif
                    {
                        // Enable DP Fifo Under/OverFlow Watch Dog
                        ScalerDpMacStreamRxSetFifoWD(_D9_INPUT_PORT, _ENABLE);

                        // Enable DP overflow/ underflow IRQ
                        ScalerDpMacStreamRxSetFifoIRQ(_D9_INPUT_PORT, _ENABLE);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                        if(ScalerDpMacStreamRxDscGetFlagStatus(ScalerDpRxDxMacSourceMapping(_D9_INPUT_PORT)) == _TRUE)
                        {
                            // Enable DSC VB-ID[6] Watch Dog and IRQ
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D9_INPUT_PORT, _ENABLE);
                        }
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
                        if(ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck() == _TRUE)
                        {
                            ScalerDpMacStreamRxSetColorSpaceChangeWD(_D9_INPUT_PORT, _ENABLE);
                        }
                        else
                        {
                            if(ScalerDpMacStreamRxMsaMiscChangeSupportCheck(_D9_INPUT_PORT) == _ON)
                            {
                                // Enable DP Msa Change IRQ
                                ScalerDpMacStreamRxSstSetMsaChangeIRQ(_D9_INPUT_PORT, _ENABLE);
                            }
                        }
#endif
                    }

                    // Enable DP BS Miss Detect IRQ
                    ScalerDpMacStreamRxSetBsMissDetectIRQ(_D9_INPUT_PORT, _ENABLE);

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if(ScalerDpAuxRxGetCodingType(_D9_INPUT_PORT) == _CODING_TYPE_8B10B)
#endif
                    {
                        // Enable DP 8b10b Decoder Error WD
                        ScalerDpMacDphyRxSet8b10bDecErrorWD(_D9_INPUT_PORT, _ENABLE);
                    }

#endif

                    break;
#endif

                default:
                    break;
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Internal Clock Selection.
// Input Value  : bSel    --> _TRUE: Xtal, _FALSE: M2PLL.
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSystemClkSel(EnumClkSel enumClockSel)
{
    if(enumClockSel == _M2PLL_CLK)
    {
        // System clock select to M2PLL/div.
        ScalerM2PLLDiv(_M2PLL_SYS_DIV);

        // Bit2: Internal Xtal Freq. Select to M2PLL/div
        ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~_BIT2, _BIT2);

#if(_VGA_SUPPORT == _ON)
        // SyncProcessor Clock Select to M2PLL & Set Divider
        ScalerSetBit(P40_06_SYNCPROC_CLK_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _M2PLL_SYS_DIV));
#endif

        // Measure Block Clock Select to M2PLL & Set Divider
        ScalerSetBit(P40_07_MEASURE_CLK_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _M2PLL_MEASURE_DIV));

        // GDI Clock Select to M2PLL & Set Divider
        ScalerSetBit(P80_06_GDI_CLK_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _M2PLL_SYS_DIV));

        // SCDC Select to External Xtal
        ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT7, 0x00);

#if(_HW_MAC0_USB3_REPEATER_TYPE == _USB3_RETIMER)
        ScalerSetBit(P40_0E_RETIMER_CLK_DIVIDER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1));
#endif
    }
    else
    {
        // Internal Xtal Freq. Select to cystal.
        ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~_BIT2, 0x00);

#if(_VGA_SUPPORT == _ON)
        // Sync Processor Clock select to Xtal
        ScalerSetBit(P40_06_SYNCPROC_CLK_DIVIDER, ~_BIT4, 0x00);
#endif

        // Measure Block Clock Select to Xtal
        ScalerSetBit(P40_07_MEASURE_CLK_DIVIDER, ~_BIT4, 0x00);

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
        // Check USB3.0 P3 And Fake_PS Condition
        if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_NO_ACTION) && (ScalerPowerCheckFakeSavingClockControl() == _DISABLE))
#else
        // Check Fake_PS Clock Select
        if(ScalerPowerCheckFakeSavingClockControl() == _DISABLE)
#endif
        {
            // GDI Clock Select to Xtal
            ScalerSetBit(P80_06_GDI_CLK_DIVIDER, ~_BIT4, 0x00);
        }

        if(enumClockSel == _IOSC_CLK)
        {
            // SCDC Select to INOSC
            ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT7, _BIT7);
        }
        else
        {
            // SCDC Select to External Xtal
            ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT7, 0x00);
        }
    }
}

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV))
//--------------------------------------------------
// Description  : Enable/Disable I domain double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDomainDoubleBufferEnable(EnumInputDataPath enumSelectedDataPath, bit bEn)
{
    BYTE ucIDomainDBEnableBit = ScalerGetByte(P31_A4_I_DB_CTRL4);

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ucIndex++)
    {
        EnumInputDataPath enumChkPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumSelectedDataPath & enumChkPath) == enumChkPath)
        {
            if(bEn == _ENABLE)
            {
                ucIDomainDBEnableBit |= GET_I_DB_ENABLE_BIT(ucIndex);
            }
            else
            {
                ucIDomainDBEnableBit &= ~(GET_I_DB_ENABLE_BIT(ucIndex));
            }
        }
    }

    // Set I Domain Double Buffer Enable
    ScalerSetBit(P31_A4_I_DB_CTRL4, ~_I_DOMAIN_DB_EN_MASK, ucIDomainDBEnableBit);

    // Disable I-Domain apply bit
    ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, 0x00);
}

//--------------------------------------------------
// Description  : Enable/Disable D domain double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDDomainDoubleBufferEnable(bit bEn)
{
    if(bEn == _ENABLE)
    {
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), _BIT7);
    }
    else
    {
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Get D-Domain double buffer status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerGlobalGetDDomainDBStatus(void)
{
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get I-Domain double buffer status
// Input Value  : EnumInputDataPath
// Output Value : EnumIDomainDBEnableStatus
//--------------------------------------------------
EnumIDomainDBEnableStatus ScalerGlobalGetIDomainDBStatus(EnumInputDataPath enumSelectedDataPath)
{
    EnumIDomainDBEnableStatus enumDBEnableStatus = _I_DOMAIN_DB_DISABLE;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ucIndex++)
    {
        EnumInputDataPath enumChkPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIDomainDBEnableBit = GET_I_DB_ENABLE_BIT(ucIndex);

        if((enumSelectedDataPath & enumChkPath) == enumChkPath)
        {
            if(ScalerGetBit(P31_A4_I_DB_CTRL4, ucIDomainDBEnableBit) == ucIDomainDBEnableBit)
            {
                enumDBEnableStatus |= GET_I_DB_STATUS(ucIndex);
            }
        }
    }

    return enumDBEnableStatus;
}
#endif

//--------------------------------------------------
// Description  : Enable/Disable double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferEnable(EnumInputDataPath enumSelectedDataPath, bit bEn)
{
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
    ScalerGlobalDoubleBufferEnable_Gen1(enumSelectedDataPath, bEn);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    ScalerGlobalDoubleBufferEnable_Gen4(enumSelectedDataPath, bEn);
#endif

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
    ScalerFmtCnvEagleSightCaptureDoubleBufferEnable(bEn);
#endif
#endif
}

//--------------------------------------------------
// Description  : Set I domain double buffer trigger event initial
// Input Value  : DB path select, DB I domain trigger event
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetTriggerEventInitial(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent)
{
    enumSelectedDataPath = enumSelectedDataPath;
    enumTriggerEvent = enumTriggerEvent;

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
    ScalerGlobalIDDomainDBSetTriggerEvent_Gen1(enumSelectedDataPath, enumTriggerEvent);
#endif
}

//--------------------------------------------------
// Description  : Set I domain double buffer trigger event
// Input Value  : DB path select, DB I domain trigger event
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetTriggerEvent(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent)
{
    enumSelectedDataPath = enumSelectedDataPath;
    enumTriggerEvent = enumTriggerEvent;

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
    ScalerGlobalIDDomainDBSetTriggerEvent_Gen1(enumSelectedDataPath, enumTriggerEvent);
#endif
}

//--------------------------------------------------
// Description  : Set D domain double buffer apply
// Input Value  : DB apply region, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDDomainDBApply(EnumDDomainDBApplyRegion enumDDomainDBApplyRegion, EnumDBApply enumDBApply)
{
    enumDDomainDBApplyRegion = enumDDomainDBApplyRegion;

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    if((ScalerMDomainDisplayTimingGenGetDBStatus() == _DISABLE) && (ScalerGlobalGetDDomainDBStatus() == _DISABLE))
#else
    if(ScalerGlobalGetDDomainDBStatus() == _DISABLE)
#endif
    {
        return;
    }

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
    ScalerGlobalDDomainDBApply_Gen1(enumDBApply);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    ScalerGlobalDDomainDBApply_Gen4(enumDDomainDBApplyRegion, enumDBApply);
#endif
}

//--------------------------------------------------
// Description  : Set I domain double buffer apply
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDomainDBApply(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply)
{
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    if((ScalerGlobalGetDBStatus(enumInputDataPath) & (_VGIP_DB_ENABLE | _I_DB_ENABLE)) == 0x00)
#else
    if((ScalerGlobalGetDBStatus(enumInputDataPath) & _I_DB_ENABLE) == 0x00)
#endif
    {
        return;
    }

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
    ScalerGlobalIDomainDBApply_Gen1(enumInputDataPath, enumDBApply);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    ScalerGlobalIDomainDBApply_Gen4(enumInputDataPath, enumDBApply);
#endif
}

//--------------------------------------------------
// Description  : Get double buffer status
// Input Value  : EnumInputDataPath
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDBEnableStatus ScalerGlobalGetDBStatus(EnumInputDataPath enumInputDataPath)
{
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
    return ScalerGlobalGetDBStatus_Gen1(enumInputDataPath);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    return ScalerGlobalGetDBStatus_Gen4(enumInputDataPath);
#endif

    return _DB_DISABLE;
}

//--------------------------------------------------
// Description  : Set I and D domain double buffer apply
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBApply(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply)
{
    if(ScalerGlobalGetDBStatus(enumSelectedDataPath) == _DB_DISABLE)
    {
        return;
    }

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
    ScalerGlobalIDDomainDBApply_Gen1(enumSelectedDataPath, enumDBApply);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    ScalerGlobalIDDomainDBApply_Gen4(enumSelectedDataPath, enumDBApply);
#endif
}

//--------------------------------------------------
// Description  : Wait for D Domain DB apply Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalWaitDDomainDBApplyFinish(void)
{
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
    ScalerGlobalWaitDDomainDBApplyFinish_Gen1();
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    ScalerGlobalWaitDDomainDBApplyFinish_Gen4();
#endif
}

//--------------------------------------------------
// Description  : Get I Domain Double Buffer Apply Bit
// Input Value  : enumInputDataPath
// Output Value : I Domain Double Buffer Apply Bit
//--------------------------------------------------
BYTE ScalerGlobalGetIDomainDBApplyBit(EnumInputDataPath enumInputDataPath)
{
    BYTE ucDBctrl = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ucIndex++)
    {
        EnumInputDataPath enumChkPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumChkPath) == enumChkPath)
        {
            ucDBctrl |= GET_I_DB_APPLY_BIT(ucIndex);
        }
    }

    return ucDBctrl;
}

//--------------------------------------------------
// Description  : Global Double Buffer Reset when Reset state
// Input Value  : enumDBEnableStatus, bEn --> _ENABLE or _DISABLE
// Output Value : EnumDBEnableStatus
//--------------------------------------------------
void ScalerGlobalResetDoubleBuffer(EnumInputDataPath enumInputDataPath, EnumDBEnableStatus enumDBEnableStatus, bit bEn)
{
    if(enumDBEnableStatus == _DB_DISABLE)
    {
        return;
    }

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    enumInputDataPath = _INPUT_PATH_ALL;

    if((enumDBEnableStatus & _IMD_DB_ENABLE) == _IMD_DB_ENABLE)
    {
        ScalerGlobalDoubleBufferEnable_Gen4(enumInputDataPath, bEn);

        if(bEn == _DISABLE)
        {
            // D Domain Double Buffer Enable
            ScalerGlobalDDomainDoubleBufferEnable(_ENABLE);
        }
    }
    else
#endif
    {
        if((enumDBEnableStatus & _I_DB_ENABLE) == _I_DB_ENABLE)
        {
            ScalerGlobalIDomainDoubleBufferEnable(enumInputDataPath, bEn);
        }
    }
}

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
//--------------------------------------------------
// Description  : Enable/Disable double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferEnable_Gen1(EnumInputDataPath enumSelectedDataPath, bit bEn)
{
    ScalerGlobalIDomainDoubleBufferEnable(enumSelectedDataPath, bEn);
    ScalerGlobalDDomainDoubleBufferEnable(bEn);
}

//--------------------------------------------------
// Description  : Set I domain double buffer trigger event
// Input Value  : DB path select, DB I domain trigger event
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetTriggerEvent_Gen1(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent)
{
    BYTE ucCtrlBits31A1 = 0;
    BYTE ucCtrlBits31A2 = 0;
    BYTE ucDBTriggerEventCtrl31A1 = 0;
    BYTE ucDBTriggerEventCtrl31A2 = 0;
    BYTE ucTriggerEvent = ((enumTriggerEvent == _DB_TRIGGER_EVENT_IEN_STOP) ? 1 : 0);
    BYTE ucInputPathCount = ScalerMDomainGetInputPathCount(enumSelectedDataPath);

#if(_HW_I_DOMAIN_M1_PATH_SUPPORT == _ON)
    if((enumSelectedDataPath & _INPUT_PATH_M1) == _INPUT_PATH_M1)
    {
        ucDBTriggerEventCtrl31A1 |= (ucTriggerEvent << 3);
        ucCtrlBits31A1 |= (_BIT3 | _BIT7);

        if(ucInputPathCount == _INPUT_PATH_1)
        {
            ucDBTriggerEventCtrl31A1 &= (~_BIT7);
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl31A1 &= (~_BIT7);
            }
            else
            {
                ucDBTriggerEventCtrl31A1 |= _BIT7;
            }
        }
    }
#endif

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
    if((enumSelectedDataPath & _INPUT_PATH_M2) == _INPUT_PATH_M2)
    {
        ucDBTriggerEventCtrl31A1 |= (ucTriggerEvent << 2);
        ucCtrlBits31A1 |= (_BIT2 | _BIT6);

        if(ucInputPathCount == _INPUT_PATH_1)
        {
            ucDBTriggerEventCtrl31A1 |= _BIT6;
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl31A1 &= (~_BIT6);
            }
            else
            {
                ucDBTriggerEventCtrl31A1 |= _BIT6;
            }
        }
    }
#endif

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
    if((enumSelectedDataPath & _INPUT_PATH_S1) == _INPUT_PATH_S1)
    {
        ucDBTriggerEventCtrl31A1 |= (ucTriggerEvent << 1);
        ucCtrlBits31A1 |= (_BIT1 | _BIT5);

        if(ucInputPathCount == _INPUT_PATH_1)
        {
            ucDBTriggerEventCtrl31A1 &= (~_BIT5);
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl31A1 &= (~_BIT5);
            }
            else
            {
                ucDBTriggerEventCtrl31A1 |= _BIT5;
            }
        }
    }
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
    if((enumSelectedDataPath & _INPUT_PATH_S2) == _INPUT_PATH_S2)
    {
        ucDBTriggerEventCtrl31A1 |= ucTriggerEvent;
        ucCtrlBits31A1 |= (_BIT0 | _BIT4);

        if(ucInputPathCount == _INPUT_PATH_1)
        {
            ucDBTriggerEventCtrl31A1 |= _BIT4;
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl31A1 &= (~_BIT4);
            }
            else
            {
                ucDBTriggerEventCtrl31A1 |= _BIT4;
            }
        }
    }
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
    if((enumSelectedDataPath & _INPUT_PATH_S3) == _INPUT_PATH_S3)
    {
        ucDBTriggerEventCtrl31A2 |= (ucTriggerEvent << 3);
        ucCtrlBits31A2 |= (_BIT3 | _BIT5);

        if(ScalerMDomainGetInputPathCount(enumSelectedDataPath) == _INPUT_PATH_1)
        {
            ucDBTriggerEventCtrl31A2 &= (~_BIT5);
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl31A2 &= (~_BIT5);
            }
            else
            {
                ucDBTriggerEventCtrl31A2 |= _BIT5;
            }
        }
    }
#endif

#if(_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON)
    if((enumSelectedDataPath & _INPUT_PATH_S4) == _INPUT_PATH_S4)
    {
        ucDBTriggerEventCtrl31A2 |= (ucTriggerEvent << 4);
        ucCtrlBits31A2 |= (_BIT4 | _BIT6);

        if(ScalerMDomainGetInputPathCount(enumSelectedDataPath) == _INPUT_PATH_1)
        {
            ucDBTriggerEventCtrl31A2 |= _BIT6;
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl31A2 &= (~_BIT6);
            }
            else
            {
                ucDBTriggerEventCtrl31A2 |= _BIT6;
            }
        }
    }
#endif

    // Apply DB control bits
    if(ucCtrlBits31A1 != 0)
    {
        ScalerSetBit(P31_A1_I_DB_CTRL1, ~ucCtrlBits31A1, ucDBTriggerEventCtrl31A1);
    }

    if(ucCtrlBits31A2 != 0)
    {
        ScalerSetBit(P31_A2_I_DB_CTRL2, ~ucCtrlBits31A2, ucDBTriggerEventCtrl31A2);
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
    {
        if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
        {
            // I_main_sub_sync select sub reference main: M1 IVS in 4 path mode
            ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), _BIT2);
        }
        else if(enumTriggerEvent == _DB_TRIGGER_EVENT_IEN_STOP)
        {
            // I_main_sub_sync select main reference sub: S2 IEN stop in 4 path mode
            ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), _BIT1);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Set D domain double buffer apply
// Input Value  : DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDDomainDBApply_Gen1(EnumDBApply enumDBApply)
{
    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }

    // Set D-domain DB trigger event,1: DENA Stop
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);

    // Set D apply bit
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

    if(enumDBApply == _DB_APPLY_POLLING)
    {
        // Check D domain status before polling
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            return;
        }

        // Wait D double buffer
        if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, (_BIT6), 0) == _FALSE)
        {
            // Disable Display format gen when D domain double buffer timeout
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT0, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set I domain double buffer apply
//
// The actual I_DB-applied path will be determined
// by both selected path and display mode.
//
// * In 1P Mode:
//      I_DB apply on M1 & M2, regardless of selected path.
//
// * In PIP, PBP_LR and PBP_TB Mode:
//      I_DB apply on M1 & M2 as long as at least one of them is selected.
//      I_DB apply on S1 & S2 as long as at least one of them is selected.
//
// * In 4P Mode:
//      I_DB apply on each selected path.
//
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDomainDBApply_Gen1(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply)
{
    BYTE ucDBctrl = 0;
    BYTE ucIDomainPage = ScalerIDomainGetInputPathPage(enumInputDataPath);

    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }

    ucDBctrl = ScalerGlobalGetIDomainDBApplyBit(enumInputDataPath);

    // Set I apply bit
    ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    ScalerDMB05DoubleBufferApply(enumInputDataPath); // DM B05 apply bit
#endif
#endif

    if(enumDBApply == _DB_APPLY_POLLING)
    {
        // Check if VGIP is enabled before polling
        if(GET_PAGED_BIT(ucIDomainPage, P0_10_M1_VGIP_CTRL, _BIT0) == 0)
        {
            return;
        }

        // Wait I double buffer
        if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, ucDBctrl, 0) == _FALSE)
        {
            // Disable VGIP when I domain double buffer timeout
            SET_PAGED_BIT(ucIDomainPage, P0_10_M1_VGIP_CTRL, ~_BIT0, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Get double buffer status
// Input Value  : EnumInputDataPath
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDBEnableStatus ScalerGlobalGetDBStatus_Gen1(EnumInputDataPath enumInputDataPath)
{
    EnumDBEnableStatus enumDBEnableStatus = _DB_DISABLE;

    if((enumInputDataPath != _INPUT_PATH_NONE) && (ScalerGlobalGetIDomainDBStatus(enumInputDataPath) != _I_DOMAIN_DB_DISABLE))
    {
        enumDBEnableStatus |= _I_DB_ENABLE;
    }
    if(ScalerGlobalGetDDomainDBStatus() == _ENABLE)
    {
        enumDBEnableStatus |= _D_DB_ENABLE;
    }

    return enumDBEnableStatus;
}

//--------------------------------------------------
// Description  : Set I and D domain double buffer apply
//
// The actual I_DB-applied path will be determined
// by both selected path and display mode.
//
// * In 1P Mode:
//      I_DB apply on M1 & M2, regardless of selected path.
//
// * In PIP, PBP_LR and PBP_TB Mode:
//      I_DB apply on M1 & M2 as long as at least one of them is selected.
//      I_DB apply on S1 & S2 as long as at least one of them is selected.
//
// * In 4P Mode:
//      I_DB apply on each selected path.
//
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBApply_Gen1(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply)
{
    BYTE ucDBctrl = 0;

    // Set D-domain DB trigger event,1: DENA Stop
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);

    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }
    else
    {
        // Check I/D domain status
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            return;
        }
    }

    ucDBctrl = ScalerGlobalGetIDomainDBApplyBit(enumSelectedDataPath);

    if(enumDBApply == _DB_APPLY_POLLING)
    {
#if(_FRC_SUPPORT == _ON)
        if(ScalerGlobalIDDomainDBApplyFRCModeCheck(enumSelectedDataPath) == _TRUE)
        {
            ScalerGlobalIDDomainDBApplyFRCModeSetDB(enumSelectedDataPath);
        }
        else
#endif
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

            // Set I apply bit
            ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            ScalerDMB05DoubleBufferApply(enumSelectedDataPath); // DM B05 apply bit
#endif
#endif

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

            // Wait D double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);
        }
    }
    else if(enumDBApply == _DB_APPLY_NO_POLLING)
    {
        // Set I apply bit
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
        ScalerDMB05DoubleBufferApply(enumSelectedDataPath); // DM B05 apply bit
#endif
#endif

        // Set D apply bit
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));
    }
}

//--------------------------------------------------
// Description  : Wait for D Domain DB apply Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalWaitDDomainDBApplyFinish_Gen1(void)
{
    if(ScalerGlobalGetDDomainDBStatus() == _ENABLE)
    {
        if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT6) == _BIT6)
        {
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0) == _FALSE)
            {
                // Disable D domain double buffer enable when D domain double buffer timeout
                ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT7, 0x00);
            }
        }
    }
}
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
//--------------------------------------------------
// Description  : Enable/Disable double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferEnable_Gen4(EnumInputDataPath enumSelectedDataPath, bit bEn)
{
    // VGIP Double Buffer Disable
    ScalerVgipDoubleBufferEnable(enumSelectedDataPath, _DISABLE);

    // DTG Double Buffer Disable
    ScalerMDomainDisplayTimingGenDBEnable(_DISABLE);

    // I Domain Double Buffer Set new mode
    ScalerSetBit(P31_A3_I_DB_CTRL3, ~_BIT0, _BIT0);

    if(bEn == _ENABLE)
    {
        // I Domain Double Buffer Disable
        ScalerGlobalIDomainDoubleBufferEnable(enumSelectedDataPath, _ENABLE);

        // D Domain Double Buffer Disable
        ScalerGlobalDDomainDoubleBufferEnable(_ENABLE);
    }
    else
    {
        // I Domain Double Buffer Disable
        ScalerGlobalIDomainDoubleBufferEnable(enumSelectedDataPath, _DISABLE);

        // D Domain Double Buffer Disable
        ScalerGlobalDDomainDoubleBufferEnable(_DISABLE);
    }

    // IMD Double Buffer Disable
    ScalerGlobalIMDDBEnable(_DISABLE);
}

//--------------------------------------------------
// Description  : Set D domain double buffer apply
// Input Value  : DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDDomainDBApply_Gen4(EnumDDomainDBApplyRegion enumDDomainDBApplyRegion, EnumDBApply enumDBApply)
{
    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }

    // Check IMD Doube Buffer Enable
    if(ScalerGlobalGetIMDDBStatus() == _ENABLE)
    {
        EnumInputDataPath enumInputDataPath = _INPUT_PATH_NONE;

        switch(enumDDomainDBApplyRegion)
        {
            case _D_DOMAIN_DB_APPLY_REGION_INDEX_0:
                enumInputDataPath = _INPUT_PATH_M1_M2;
                break;

            case _D_DOMAIN_DB_APPLY_REGION_INDEX_1:
                enumInputDataPath = _HW_SUB_REGION_INPUT_PATH;
                break;

            case _D_DOMAIN_DB_APPLY_REGION_EITHER:
            default:

                // Check I domain status
                if((GET_PAGED_BIT(ScalerIDomainGetInputPathPage(_INPUT_PATH_M1_M2), P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0) &&
                   (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2) == _TRUE) &&
                   (GET_PAGED_BIT(_FRC_MAIN1_PAGE, P5_27_CAP_M1_DDR_CTRL1, _BIT7) == _BIT7) &&
                   (GET_PAGED_BIT(_FRC_MAIN1_PAGE, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == _BIT0))
                {
                    enumInputDataPath |= _INPUT_PATH_M1_M2;
                }
                else
                {
                    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
                    {
                        // Check I domain status
                        if((GET_PAGED_BIT(ScalerIDomainGetInputPathPage(_HW_SUB_REGION_INPUT_PATH), P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0) &&
                           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _HW_SUB_REGION_INPUT_PATH) == _TRUE) &&
                           (GET_PAGED_BIT(_FRC_SUB1_PAGE, P5_27_CAP_M1_DDR_CTRL1, _BIT7) == _BIT7) &&
                           (GET_PAGED_BIT(_FRC_SUB1_PAGE, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == _BIT0))
                        {
                            enumInputDataPath |= _HW_SUB_REGION_INPUT_PATH;
                        }
                    }
                }

                break;

            case _D_DOMAIN_DB_APPLY_REGION_ALL:

                // Check I domain status
                if((GET_PAGED_BIT(ScalerIDomainGetInputPathPage(_INPUT_PATH_M1_M2), P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0) &&
                   (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2) == _TRUE) &&
                   (GET_PAGED_BIT(_FRC_MAIN1_PAGE, P5_27_CAP_M1_DDR_CTRL1, _BIT7) == _BIT7) &&
                   (GET_PAGED_BIT(_FRC_MAIN1_PAGE, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == _BIT0))
                {
                    enumInputDataPath |= _INPUT_PATH_M1_M2;
                }

                if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
                {
                    // Check I domain status
                    if((GET_PAGED_BIT(ScalerIDomainGetInputPathPage(_HW_SUB_REGION_INPUT_PATH), P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0) &&
                       (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _HW_SUB_REGION_INPUT_PATH) == _TRUE) &&
                       (GET_PAGED_BIT(_FRC_SUB1_PAGE, P5_27_CAP_M1_DDR_CTRL1, _BIT7) == _BIT7) &&
                       (GET_PAGED_BIT(_FRC_SUB1_PAGE, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == _BIT0))
                    {
                        enumInputDataPath |= _HW_SUB_REGION_INPUT_PATH;
                    }
                }
                break;
        }

        ScalerGlobalIMDDBApply(enumInputDataPath, enumDBApply, _FALSE);
    }
    else if(ScalerMDomainDisplayTimingGenGetDBStatus() == _ENABLE)
    {
        ScalerMDomainDisplayTimingGenDBApply(enumDBApply);
    }
    else
    {
        // Check D-Domain Doube Buffer Enable
        if(ScalerGlobalGetDDomainDBStatus() == _ENABLE)
        {
            // Set D-domain DB trigger event,0: DENA Stop (_GLOBAL_DB_GEN_IV)
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, 0x00);

            // Wait DDen Start
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

            // Clr MD Double Buffer Happen Flag
            ScalerGlobalClrDDoubleBufferHappenFlag();

#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
            // Must before D apply bit
            ScalerOsdTimingGenGlobalDBApply(_DB_APPLY_NO_POLLING);
#endif

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

            if(enumDBApply == _DB_APPLY_POLLING)
            {
                // Check D domain status before polling
                if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
                   (GET_DPLL_POWER_STATUS() == _FALSE))
                {
                    // Clr D apply bit
                    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, 0x00);

                    return;
                }

                // Wait D double buffer
                if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, (_BIT6), 0) == _FALSE)
                {
                    // Disable Display format gen when D domain double buffer timeout
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT0, 0x00);

                    // Clr D apply bit
                    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, 0x00);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Set I domain double buffer apply
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDomainDBApply_Gen4(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply)
{
    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }

    // Check IMD Doube Buffer Enable
    if(ScalerGlobalGetIMDDBStatus() == _ENABLE)
    {
        ScalerGlobalIMDDBApply(enumInputDataPath, enumDBApply, _TRUE);
    }
    else if((ScalerGlobalGetDBStatus(enumInputDataPath) & _VGIP_DB_ENABLE) != 0x00)
    {
        ScalerVgipVgipDoubleBufferApply(enumDBApply);
    }
    else
    {
        // Check I-Domain Doube Buffer Enable
        if(ScalerGlobalGetIDomainDBStatus(enumInputDataPath) != _I_DOMAIN_DB_DISABLE)
        {
            BYTE ucIDomainPage = ScalerIDomainGetInputPathPage(enumInputDataPath);
            BYTE ucDBctrl = ScalerGlobalGetIDomainDBApplyBit(enumInputDataPath);

            // Check if VGIP is enabled before polling
            if(GET_PAGED_BIT(ucIDomainPage, P0_10_M1_VGIP_CTRL, _BIT0) == 0)
            {
                return;
            }

            // Wait Main IDen Start
            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, enumInputDataPath);

            // Clr I and MI Double Buffer Happen Flag
            ScalerGlobalClrIDoubleBufferHappenFlag();

            // I-domain double buffer apply
            ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);

            if(enumDBApply == _DB_APPLY_POLLING)
            {
                if(GET_I_DB_APPLY_POINT() == _GLOBAL_APPLY_I)
                {
                    // Polling VGIP DB Happen Falg
                    ScalerGlobalPollingVGIPDBHappen(enumInputDataPath);

                    // Clr I domain double buffer apply
                    ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, 0x00);
                }
                else
                {
                    // Wait I double buffer
                    if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, (ucDBctrl), 0) == _FALSE)
                    {
                        // Clr I domain double buffer apply
                        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, 0x00);
                    }
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get double buffer status
// Input Value  : EnumInputDataPath
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDBEnableStatus ScalerGlobalGetDBStatus_Gen4(EnumInputDataPath enumInputDataPath)
{
    EnumDBEnableStatus enumDBEnableStatus = _DB_DISABLE;

    if(ScalerGlobalGetIMDDBStatus() == _ENABLE)
    {
        enumDBEnableStatus |= _IMD_DB_ENABLE;
    }
    else
    {
        if(ScalerVgipGetVGIPDBStatus() != _VGIP_DB_DISABLE)
        {
            enumDBEnableStatus |= _VGIP_DB_ENABLE;
        }

        if(ScalerMDomainDisplayTimingGenGetDBStatus() == _ENABLE)
        {
            enumDBEnableStatus |= _DTG_DB_ENABLE;
        }

        if((enumInputDataPath != _INPUT_PATH_NONE) && (ScalerGlobalGetIDomainDBStatus(enumInputDataPath) != _I_DOMAIN_DB_DISABLE))
        {
            enumDBEnableStatus |= _I_DB_ENABLE;
        }

        if(ScalerGlobalGetDDomainDBStatus() == _ENABLE)
        {
            enumDBEnableStatus |= _D_DB_ENABLE;
        }
    }

    return enumDBEnableStatus;
}

//--------------------------------------------------
// Description  : Set I and D domain double buffer apply
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBApply_Gen4(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply)
{
    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }

    // Check IMD Doube Buffer Enable
    switch(ScalerGlobalGetDBStatus(enumSelectedDataPath))
    {
        case _IMD_DB_ENABLE:
            ScalerGlobalIMDDBApply(enumSelectedDataPath, enumDBApply, _TRUE);
            break;

        case _I_D_DB_ENABLE:
        case _VGIP_DTG_DB_ENABLE:

            // I-domain double buffer apply
            ScalerGlobalIDomainDBApply(enumSelectedDataPath, enumDBApply);

            // Display timing gen double buffer apply
            ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Wait for D Domain DB apply Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalWaitDDomainDBApplyFinish_Gen4(void)
{
    if(ScalerGlobalGetIMDDBStatus() == _ENABLE)
    {
        if(ScalerGetBit(P46_D0_I_DB_CTRL, _BIT6) == _BIT6)
        {
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P46_D0_I_DB_CTRL, _BIT6, 0) == _FALSE)
            {
                // IMD Double Buffer Disable
                ScalerGlobalIMDDBEnable(_DISABLE);
            }
        }

        if(ScalerGetBit(PD7_D0_I_DB_CTRL, _BIT6) == _BIT6)
        {
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, PD7_D0_I_DB_CTRL, _BIT6, 0) == _FALSE)
            {
                // IMD Double Buffer Disable
                ScalerGlobalIMDDBEnable(_DISABLE);
            }
        }
    }
    else
    {
        if(ScalerGlobalGetDDomainDBStatus() == _ENABLE)
        {
            if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT6) == _BIT6)
            {
                if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0) == _FALSE)
                {
                    // Disable D domain double buffer enable when D domain double buffer timeout
                    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT7, 0x00);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Double Buffer Switch to IMD DB case
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferSwitchtoIMDDB(void)
{
    if((ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE) &&
       ((GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_MODE_1P) ||
        (GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)))
    {
        // Frame sync frame line buffer, frame sync frame buffer, ES main using I/ D DB
    }
    else
    {
        // IMD Double Buffer Enable
        ScalerGlobalIMDDBEnable(_ENABLE);

        // I Domain Double Buffer Disable
        ScalerGlobalIDomainDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);

        // D Domain Double Buffer Disable
        ScalerGlobalDDomainDoubleBufferEnable(_DISABLE);
    }

    // Disable Ch0 IMD DB apply bit
    ScalerSetBit(P46_D0_I_DB_CTRL, ~(_BIT6), 0x00);

    // Disable Ch1 IMD DB apply bit
    ScalerSetBit(PD7_D0_I_DB_CTRL, ~(_BIT6), 0x00);
}

//--------------------------------------------------
// Description  : Global Double Buffer Config Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferConfigReset(void)
{
    SET_I_DB_APPLY_POINT(_GLOBAL_APPLY_I);

    ScalerGlobalDoubleBufferEnable(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(GET_ROT_TYPE() == _ROT_CW180)
    {
        // Disable I-domain double buffer
        ScalerGlobalIDomainDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);

        // Disable D-domain double buffer
        ScalerGlobalDDomainDoubleBufferEnable(_DISABLE);

        // Enable VGIP double buffer
        ScalerVgipDoubleBufferEnable(GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);

        // Enable DTG double buffer
        ScalerMDomainDisplayTimingGenDBEnable(_ENABLE);
    }
    else
#endif
    {
        // Disable VGIP double buffer
        ScalerVgipDoubleBufferEnable(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);

        // Disable DTG double buffer
        ScalerMDomainDisplayTimingGenDBEnable(_DISABLE);

        // Enable I-domain double buffer
        ScalerGlobalIDomainDoubleBufferEnable(GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);

        // Disable D-domain double buffer
        ScalerGlobalDDomainDoubleBufferEnable(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : IMD DB apply
// Input Value  : enumInputDataPath, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIMDDBApply(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply, bit bCheckPath)
{
    // Check I domain status
    if(enumInputDataPath == _INPUT_PATH_NONE)
    {
        // IMD Double Buffer Disable
        ScalerGlobalIMDDBEnable(_DISABLE);
    }

    if(bCheckPath == _TRUE)
    {
        // Check I domain status
        if((enumInputDataPath == _INPUT_PATH_M1_M2) &&
           (GET_PAGED_BIT(ScalerIDomainGetInputPathPage(_INPUT_PATH_M1_M2), P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0) &&
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2) == _TRUE) &&
           (GET_PAGED_BIT(_FRC_MAIN1_PAGE, P5_27_CAP_M1_DDR_CTRL1, _BIT7) == _BIT7) &&
           (GET_PAGED_BIT(_FRC_MAIN1_PAGE, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == _BIT0))
        {
            enumInputDataPath |= _INPUT_PATH_M1_M2;
        }

        if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
        {
            // Check I domain status
            if((enumInputDataPath == _HW_SUB_REGION_INPUT_PATH) &&
               (GET_PAGED_BIT(ScalerIDomainGetInputPathPage(_HW_SUB_REGION_INPUT_PATH), P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0) &&
               (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _HW_SUB_REGION_INPUT_PATH) == _TRUE) &&
               (GET_PAGED_BIT(_FRC_SUB1_PAGE, P5_27_CAP_M1_DDR_CTRL1, _BIT7) == _BIT7) &&
               (GET_PAGED_BIT(_FRC_SUB1_PAGE, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == _BIT0))
            {
                enumInputDataPath |= _HW_SUB_REGION_INPUT_PATH;
            }
        }

        if(enumInputDataPath == _INPUT_PATH_NONE)
        {
            // IMD Double Buffer Disable
            ScalerGlobalIMDDBEnable(_DISABLE);
            return;
        }
    }
    else
    {
        BYTE ucIDomainPage = ScalerIDomainGetInputPathPage(enumInputDataPath);
        EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;

        for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            if(CHK_FRC_PATH(enumInputDataPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
            {
                enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
                break;
            }
        }

        if(ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath) == _FALSE)
        {
            // IMD Double Buffer Disable
            ScalerGlobalIMDDBEnable(_DISABLE);
            return;
        }

        if((GET_PAGED_BIT(ucIDomainPage, P0_10_M1_VGIP_CTRL, _BIT0) == 0x00) &&
           (GET_PAGED_BIT(enumPageSelect, P5_27_CAP_M1_DDR_CTRL1, _BIT7) == _BIT7) &&
           (GET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == _BIT0))
        {
            // IMD Double Buffer Disable
            ScalerGlobalIMDDBEnable(_DISABLE);
            return;
        }
    }

    // Check D domain status
    if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
       (GET_DPLL_POWER_STATUS() == _FALSE))
    {
        // IMD Double Buffer Disable
        ScalerGlobalIMDDBEnable(_DISABLE);
        return;
    }

    if(((enumInputDataPath & _INPUT_PATH_M1) == _INPUT_PATH_M1) ||
       ((enumInputDataPath & _INPUT_PATH_M1_M2) == _INPUT_PATH_M1_M2))
    {
        // Clr MI and MD DB flag
        ScalerSetBit(P46_D1_IMD_DB_STATUS, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Set DB apply
        ScalerSetBit(P46_D0_I_DB_CTRL, ~_BIT6, _BIT6);

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P46_D0_I_DB_CTRL, _BIT6, 0) == _FALSE)
            {
                // IMD Double Buffer Disable
                ScalerGlobalIMDDBEnable(_DISABLE);
            }
        }
    }

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
    if((enumInputDataPath & _HW_SUB_REGION_INPUT_PATH) == _HW_SUB_REGION_INPUT_PATH)
    {
        // Clr MI and MD DB flag
        ScalerSetBit(PD7_D1_IMD_DB_STATUS, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Set DB apply
        ScalerSetBit(PD7_D0_I_DB_CTRL, ~_BIT6, _BIT6);

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, PD7_D0_I_DB_CTRL, _BIT6, 0) == _FALSE)
            {
                // IMD Double Buffer Disable
                ScalerGlobalIMDDBEnable(_DISABLE);
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Polling VGIP Double Buffer Happen Flag
// Input Value  : enumInputDataPath
// Output Value : None
//--------------------------------------------------
bit ScalerGlobalPollingVGIPDBHappen(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1:
        default:
            // Wait M1 VGIP DB happen flag
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A5_I_DB_M1_STATUS, _BIT3, _TRUE);
            break;

        case _INPUT_PATH_M1_M2:
            // Wait M2 VGIP DB happen flag
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A6_I_DB_M2_STATUS, _BIT3, _TRUE);
            break;

        case _INPUT_PATH_S1:
            // Wait S1 VGIP DB happen flag
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A7_I_DB_S1_STATUS, _BIT3, _TRUE);
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Clr I and MI Double Buffer Happen Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalClrIDoubleBufferHappenFlag(void)
{
    // Clr I DB M1 happen flag
    ScalerSetBit(P31_A5_I_DB_M1_STATUS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_HW_D_DOMAIN_M2_PATH_SUPPORT == _ON)
    // Clr I DB M2 happen flag
    ScalerSetBit(P31_A6_I_DB_M2_STATUS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

    // Clr I DB S1 happen flag
    ScalerSetBit(P31_A7_I_DB_S1_STATUS, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2 | _BIT1));

#if(_HW_D_DOMAIN_M2_PATH_SUPPORT == _ON)
    // Clr MI DB M1 happen flag
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    ScalerSetBit(P31_C0_M_DB_STATUS_0, ~(0x3F), (_BIT5 | _BIT4 | _BIT3));
#else
    ScalerSetBit(P31_C0_M_DB_STATUS_0, ~(0x1E), (_BIT4 | _BIT3));
#endif

    // Clr MI DB M2 happen flag
    ScalerSetBit(P31_C1_M_DB_STATUS_1, ~(0x3F), (_BIT5 | _BIT4 | _BIT3));
#else
    // Clr MI DB M1 happen flag
    ScalerSetBit(P31_C0_M_DB_STATUS_0, ~(0x1E), (_BIT4 | _BIT3));
#endif

#if(_HW_D_DOMAIN_S1_PATH_SUPPORT == _ON)
    // Clr MI DB S1 happen flag
    ScalerSetBit(P31_C2_M_DB_STATUS_2, ~(0x1E), (_BIT4 | _BIT3));
#endif
}

//--------------------------------------------------
// Description  : Clr MD Double Buffer Happen Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalClrDDoubleBufferHappenFlag(void)
{
#if(_HW_D_DOMAIN_M2_PATH_SUPPORT == _ON)
    // Clr MD DB M1 happen flag
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    ScalerSetBit(P31_C0_M_DB_STATUS_0, ~(0x3F), (_BIT2 | _BIT1 | _BIT0));
#else
    ScalerSetBit(P31_C0_M_DB_STATUS_0, ~(0x1E), (_BIT2 | _BIT1));
#endif

    // Clr MD DB M2 happen flag
    ScalerSetBit(P31_C1_M_DB_STATUS_1, ~(0x3F), (_BIT2 | _BIT1 | _BIT0));
#else
    // Clr MD DB M1 happen flag
    ScalerSetBit(P31_C0_M_DB_STATUS_0, ~(0x1E), (_BIT2 | _BIT1));
#endif

#if(_HW_D_DOMAIN_S1_PATH_SUPPORT == _ON)
    // Clr MD DB S1 happen flag
    ScalerSetBit(P31_C2_M_DB_STATUS_2, ~(0x1E), (_BIT2 | _BIT1));
#endif
}

//--------------------------------------------------
// Description  : Set IMD DB Enable
// Input Value  : _ENABLE/ _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIMDDBEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Ch0 IMD DB Enable
        ScalerSetBit(P46_D0_I_DB_CTRL, ~(_BIT7), _BIT7);

        // Enable Ch1 IMD DB Enable
        ScalerSetBit(PD7_D0_I_DB_CTRL, ~(_BIT7), _BIT7);
    }
    else
    {
        // Disable Ch0 IMD DB Enable
        ScalerSetBit(P46_D0_I_DB_CTRL, ~(_BIT7), 0x00);

        // Disable Ch1 IMD DB Enable
        ScalerSetBit(PD7_D0_I_DB_CTRL, ~(_BIT7), 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable MI and MD Force apply, Only work when I and D domain double buffer enable
// Input Value  : _ENABLE/ _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferMdomainForceApplyEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable MD Force apply
        ScalerSetBit(P31_C6_M_DB_FORCE_APPLY, ~(_BIT7), _BIT7);
    }
    else
    {
        // Disable MD Force apply
        ScalerSetBit(P31_C6_M_DB_FORCE_APPLY, ~(_BIT7), 0x00);
    }
}

//--------------------------------------------------
// Description  : Set MI Force apply Frame end,
// Input Value  : Frame end reference Vact falling, enumInputPath
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferSetMIForceApplyFrameEnd(BYTE ucFrameend, EnumInputDataPath enumInputPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            SET_PAGED_BYTE(enumPageSelect, P5_53_CAP_M1_FORCE_FEND_DELAY, ucFrameend)
        }
    }
}

//--------------------------------------------------
// Description  : Set MD Force apply Frame end
// Input Value  : Frame end reference DVS
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferSetMDForceApplyFrameEnd(WORD usFrameend)
{
    ScalerSetByte(P31_C7_M_DB_DISP_FORCE_FEND_DELAY01, HIBYTE(usFrameend));
    ScalerSetByte(P31_C8_M_DB_DISP_FORCE_FEND_DELAY02, LOBYTE(usFrameend));
}

//--------------------------------------------------
// Description  : Get IMD double buffer status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerGlobalGetIMDDBStatus(void)
{
    if((ScalerGetBit(P46_D0_I_DB_CTRL, _BIT7) == _BIT7) &&
       (ScalerGetBit(PD7_D0_I_DB_CTRL, _BIT7) == _BIT7))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif // End of #if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)

//--------------------------------------------------
// Description  : M-Domain to I-Domain
//                Input Data Path conversion
// Input Value  : IRQ Event
//                Input Data Path
// Output Value : Register Page
//--------------------------------------------------
EnumInputDataPath ScalerGlobalGetIDomainInputDataPath(EnumWaitIDomainEventType enumEvent, EnumInputDataPath enumInputDataPath)
{
    switch(enumEvent)
    {
        case _EVENT_IVS:
        case _EVENT_IEN_START:
        case _EVENT_IEN_STOP:
            if(enumInputDataPath == _INPUT_PATH_ALL)
            {
                if(enumEvent != _EVENT_IEN_STOP)
                {
                    enumInputDataPath = _INPUT_PATH_M1;
                }
                else
                {
#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
                    enumInputDataPath = _INPUT_PATH_M2;
#else
                    enumInputDataPath = _INPUT_PATH_M1;
#endif
                }
            }
            else
            {
                switch(enumInputDataPath)
                {
#if(_HW_I_DOMAIN_M1_M2_PATH_SUPPORT == _ON)
                    case _INPUT_PATH_M1_M2_S1_S2:
                    case _INPUT_PATH_M1_M2:
                        if(enumEvent != _EVENT_IEN_STOP)
                        {
                            enumInputDataPath = _INPUT_PATH_M1;
                        }
                        else
                        {
                            enumInputDataPath = _INPUT_PATH_M2;
                        }
                        break;
#endif

#if(_HW_I_DOMAIN_S1_S2_PATH_SUPPORT == _ON)
                    case _INPUT_PATH_S1_S2:
                        if((enumEvent != _EVENT_IEN_STOP) ||
                           (ScalerFmtCnvFtoPGetStatus(_INPUT_PATH_S1_S2) != _TRUE))
                        {
                            // Wait for S1 when E/O not yet enabled, or not polling IEN stop
                            enumInputDataPath = _INPUT_PATH_S1;
                        }
                        else
                        {
                            enumInputDataPath = _INPUT_PATH_S2;
                        }
                        break;
#endif

#if(_HW_I_DOMAIN_S3_S4_PATH_SUPPORT == _ON)
                    case _INPUT_PATH_S3_S4:
                        if((enumEvent != _EVENT_IEN_STOP) ||
                           (ScalerFmtCnvFtoPGetStatus_EXINT0(_INPUT_PATH_S3_S4) != _TRUE))
                        {
                            // Wait for S3 when E/O not yet enabled, or not polling IEN stop
                            enumInputDataPath = _INPUT_PATH_S3;
                        }
                        else
                        {
                            enumInputDataPath = _INPUT_PATH_S4;
                        }
                        break;
#endif

                    default:
                        break;
                }
            }

            if(enumEvent != _EVENT_IVS)
            {
                // Check if VGIP is enabled before polling
                if(GET_PAGED_BIT(ScalerIDomainGetInputPathPage(enumInputDataPath), P0_10_M1_VGIP_CTRL, _BIT0) == 0)
                {
                    return _INPUT_PATH_NONE;
                }
            }

            break;

        default:
            return _INPUT_PATH_NONE;
    }

    return enumInputDataPath;
}

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set Flag for DM
// Input Value  : Input Data Path
//                En : Enable / Disable
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetDM(EnumInputDataPath enumInputDataPath, bit bEn)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0)
        {
            SET_GLOBAL_INT_DM(ucIndex, bEn);
        }
    }
}

//--------------------------------------------------
// Description  : Get Flag for DM
// Input Value  : Input Data Path
// Output Value : DM Flag
//--------------------------------------------------
bit ScalerGlobalGetDM(EnumInputDataPath enumInputDataPath)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0)
        {
            return GET_GLOBAL_INT_DM(ucIndex);
        }
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Set IRQ
// Input Value  : IRQ Type
//                Input Data Path
//                En : Enable / Disable
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetInterruptForIDomainEvent(EnumIRQ enumIRQType, BYTE ucIRQPageOffset, bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable INT0
        SET_INTERRUPT_ENABLE_STATUS(_INT_IMD, _ENABLE);
    }

    switch(enumIRQType)
    {
        case _IRQ_IVS:
            // Clear IVS IRQ flag
            ScalerSetBit(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

            // Enable/Disable IVS IRQ
            ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT7, (bEn << 7));
            break;

        case _IRQ_IEN_START:
            // Clear IEN start IRQ flag
            ScalerSetBit(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT6);

            // Enable/Disable IEN start IRQ
            ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT6, (bEn << 6));
            break;

        case _IRQ_IEN_STOP:
            // Enable/Disable IEN stop IRQ
            ScalerSetBit(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);

            // Enable/Disable IEN stop IRQ
            ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT5, (bEn << 5));
            break;

        default:
            // For compiler warning
            bEn = bEn;
            break;
    }
}

//--------------------------------------------------
// Description  : Set IRQ I Domain
// Input Value  : enumGlobalIntFunction : Functions that use IRQ
//                Input Data Path
//                En : Enable / Disable
// Output Value : None
//--------------------------------------------------
void ScalerGlobalInterruptProcForIDomain(EnumGlobalIntFuncForIDomain enumGlobalIntFunction, EnumInputDataPath enumInputDataPath, bit bEn)
{
    EnumIRQ enumIRQType = _IRQ_NONE;
    bit bIRQIVS = _DISABLE;
    bit bIRQIENStart = _DISABLE;
    bit bIRQIENStop = _DISABLE;
    BYTE ucIRQPageOffset = 0;
    BYTE ucIndex = 0;

    switch(enumGlobalIntFunction)
    {
#if(_DM_FUNCTION == _ON)
        case _GLOBAL_INT_IDOMAIN_DM:
            enumIRQType = _IRQ_IEN_START;
            enumInputDataPath = ScalerGlobalGetIDomainInputDataPath(_EVENT_IEN_START, enumInputDataPath);
            ScalerGlobalSetDM(enumInputDataPath, bEn);
            ucIRQPageOffset = ScalerIDomainGetIRQPageOffset(enumInputDataPath);

            break;
#endif

        case _GLOBAL_INT_IDOMAIN_ALL_FUNCTION:
            if(bEn == _DISABLE)
            {
#if(_DM_FUNCTION == _ON)
                ScalerGlobalSetDM(enumInputDataPath, _DISABLE);
#endif

                for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
                {
                    EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

                    if((enumInputDataPath & enumCurrPath) != 0)
                    {
                        ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IVS, GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex), _DISABLE);
                        ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IEN_START, GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex), _DISABLE);
                        ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IEN_STOP, GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex), _DISABLE);
                    }
                }
            }

            return;
            break;

        default:
            enumInputDataPath = ScalerGlobalGetIDomainInputDataPath(_EVENT_IEN_STOP, enumInputDataPath);
            ucIRQPageOffset = ScalerIDomainGetIRQPageOffset(enumInputDataPath);
            break;
    }

    if(bEn == _ENABLE)
    {
        switch(enumIRQType)
        {
            case _IRQ_IVS:
                if((ScalerGetByte(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset) & _BIT7) == 0x00)
                {
                    ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IVS, ucIRQPageOffset, _ENABLE);
                }
                break;

            case _IRQ_IEN_START:
                if((ScalerGetByte(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset) & _BIT6) == 0x00)
                {
                    ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IEN_START, ucIRQPageOffset, _ENABLE);
                }
                break;

            case _IRQ_IEN_STOP:
                if((ScalerGetByte(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset) & _BIT5) == 0x00)
                {
                    ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IEN_STOP, ucIRQPageOffset, _ENABLE);
                }
                break;

            default:
                break;
        }
    }
    else
    {
        switch(enumIRQType)
        {
            case _IRQ_IVS:
                if(bIRQIVS == _DISABLE)
                {
                    ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IVS, ucIRQPageOffset, _DISABLE);
                }
                break;

            case _IRQ_IEN_START:
#if(_DM_FUNCTION == _ON)
                bIRQIENStart |= ScalerGlobalGetDM(enumInputDataPath);
#endif

                if(bIRQIENStart == _DISABLE)
                {
                    ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IEN_START, ucIRQPageOffset, _DISABLE);
                }
                break;

            case _IRQ_IEN_STOP:
                if(bIRQIENStop == _DISABLE)
                {
                    ScalerGlobalSetInterruptForIDomainEvent(_IRQ_IEN_STOP, ucIRQPageOffset, _DISABLE);
                }
                break;

            default:
                break;
        }
    }
}

#endif // End of #if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
//--------------------------------------------------
// Description  : Set IRQ
// Input Value  : IRQ Type
//                En : Enable / Disable
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetInterruptForDDomainEvent(EnumIRQ enumIRQType, BYTE ucEn)
{
    if(ucEn == _ENABLE)
    {
        // Enable INT0
        SET_INTERRUPT_ENABLE_STATUS(_INT_IMD, _ENABLE);
    }

    switch(enumIRQType)
    {
        case _IRQ_DEN_START:
            // Clear DEN start IRQ flag
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT2);

            // Enable/Disable DEN start IRQ
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (ucEn << 3));
            break;

        case _IRQ_DEN_STOP:
            // Clear DEN stop IRQ flag
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT4);

            // Enable/Disable DEN stop IRQ
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (ucEn << 5));
            break;

        case _IRQ_DVS:
            // Clear DVS IRQ flag
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT6);

            // Enable/Disable DVS IRQ
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0), (ucEn << 7));
            break;

#if(_HW_DVS_TIMEOUT_IRQ_SUPPORT == _ON)
        case _IRQ_DVS_TIMEOUT:
            // Clear DVS timeout flag
            ScalerGlobalClrDvsTimeoutFlag();

            // Enable/Disable DVS IRQ
            ScalerSetBit(PC0_03_EVENT_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), ucEn);
            break;
#endif
        default:
            // For compiler warning
            ucEn = ucEn;
            break;
    }
}

//--------------------------------------------------
// Description  : Set IRQ for D Domain
// Input Value  : enumGlobalIntFunction : Functions that use IRQ
//                Input Data Path
//                En : Enable / Disable
// Output Value : None
//--------------------------------------------------
void ScalerGlobalInterruptProcForDDomain(EnumGlobalIntFuncForDDomain enumGlobalIntFunction, BYTE ucEn)
{
    EnumIRQ enumIRQType = _IRQ_NONE;
    bit bIRQDVS = _DISABLE;
    bit bIRQDENStart = _DISABLE;
    bit bIRQDENStop = _DISABLE;

    switch(enumGlobalIntFunction)
    {
#if((_OD_FUNCTION == _ON) && (_FRC_SUPPORT == _ON))
        case _GLOBAL_INT_DDOMAIN_DYNAMIC_OD:
            SET_GLOBAL_INT_DYNAMIC_OD(ucEn);
            enumIRQType = _IRQ_DEN_START;
            break;
#endif

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
        case _GLOBAL_INT_DDOMAIN_LOCAL_CONTRAST:
            SET_GLOBAL_INT_LOCAL_CONTRAST(ucEn);
            enumIRQType = _IRQ_DEN_START;
            break;
#endif

#if((_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
        case _GLOBAL_INT_DDOMAIN_DRR_MBR_DVS:
            SET_GLOBAL_INT_DRR_MBR_DVS(ucEn);
            enumIRQType = _IRQ_DVS;
            break;
#endif

        case _GLOBAL_INT_DDOMAIN_ALL_FUNCTION:
            if(ucEn == _DISABLE)
            {
#if((_OD_FUNCTION == _ON) && (_FRC_SUPPORT == _ON))
                SET_GLOBAL_INT_DYNAMIC_OD(_DISABLE);
#endif
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
                SET_GLOBAL_INT_LOCAL_CONTRAST(_DISABLE);
#endif

#if((_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                SET_GLOBAL_INT_DRR_MBR_DVS(_DISABLE);
#endif

                ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DVS, _DISABLE);
                ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DEN_START, _DISABLE);
                ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DEN_STOP, _DISABLE);
#if(_HW_DVS_TIMEOUT_IRQ_SUPPORT == _ON)
                ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DVS_TIMEOUT, _DISABLE);
#endif
            }

            return;
            break;

        default:
            return;
            break;
    }

    if(ucEn == _ENABLE)
    {
        switch(enumIRQType)
        {
            case _IRQ_DEN_START:
                if((ScalerGetByte(PC0_02_DDOMAIN_IRQ_WD_CTRL1) & _BIT3) == 0x00)
                {
                    ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DEN_START, _ENABLE);
                }
                break;

            case _IRQ_DEN_STOP:
                if((ScalerGetByte(PC0_02_DDOMAIN_IRQ_WD_CTRL1) & _BIT5) == 0x00)
                {
                    ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DEN_STOP, _ENABLE);
                }
                break;

            case _IRQ_DVS:
                if((ScalerGetByte(PC0_02_DDOMAIN_IRQ_WD_CTRL1) & _BIT7) == 0x00)
                {
                    ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DVS, _ENABLE);
                }
                break;

#if(_HW_DVS_TIMEOUT_IRQ_SUPPORT == _ON)
            case _IRQ_DVS_TIMEOUT:
                if((ScalerGetByte(PC0_03_EVENT_FLAG) & _BIT0) == 0x00)
                {
                    ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DVS_TIMEOUT, _ENABLE);
                }
                break;
#endif
            default:
                break;
        }
    }
    else
    {
        switch(enumIRQType)
        {
            case _IRQ_DEN_START:
#if((_OD_FUNCTION == _ON) && (_FRC_SUPPORT == _ON))
                bIRQDENStart |= GET_GLOBAL_INT_DYNAMIC_OD();
#endif
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
                bIRQDENStart |= GET_GLOBAL_INT_LOCAL_CONTRAST();
#endif

                if(bIRQDENStart == _DISABLE)
                {
                    ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DEN_START, _DISABLE);
                }
                break;

            case _IRQ_DEN_STOP:
                // Add flag here to enable DEN Stop IRQ

                if(bIRQDENStop == _DISABLE)
                {
                    ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DEN_STOP, _DISABLE);
                }
                break;

            case _IRQ_DVS:
#if((_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                bIRQDVS |= GET_GLOBAL_INT_DRR_MBR_DVS();
#endif

                if(bIRQDVS == _DISABLE)
                {
                    ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DVS, _DISABLE);
                }
                break;

#if(_HW_DVS_TIMEOUT_IRQ_SUPPORT == _ON)
            case _IRQ_DVS_TIMEOUT:
                // Add flag here to enable DVS Timeout

                if(bIRQDENStop == _DISABLE)
                {
                    ScalerGlobalSetInterruptForDDomainEvent(_IRQ_DVS_TIMEOUT, _DISABLE);
                }
                break;
#endif
            default:
                break;
        }
    }
}
#endif // End of #if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)

//--------------------------------------------------
// Description  : Get IC ID Code
// Input Value  : None
// Output Value : ID Code
//--------------------------------------------------
BYTE ScalerGlobalGetIDCode(void)
{
    return ScalerGetByte(P0_0F_ID_REG_02);
}

#if((_FRC_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I))
//--------------------------------------------------
// Description  : Choose DB apply mode when _DB_APPLY_POLLING
// Input Value  : None
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
BYTE ScalerGlobalIDDomainDBApplyFRCModeCheck(EnumInputDataPath enumSelectedDataPath)
{
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
       (ScalerRotationCheckStatus(GET_ROT_TYPE(), GET_MDOMAIN_INPUT_PORT()) == _TRUE))
    {
        return _FALSE;
    }
#endif

    if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
    {
        EnumFRCChannelPageSelect enumChannelPage = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(enumSelectedDataPath));

        if((ScalerFRCGetLineBufferMode(enumSelectedDataPath) == _FALSE) &&
           (ScalerFRCGetChannelFRCCapBlkNum(enumChannelPage) == _FRC_CH_1_BLK))
        {
            return _FALSE;
        }

#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
        if(ScalerFRCGetLineBufferMode(enumSelectedDataPath) == _TRUE)
        {
            return _FALSE;
        }
#endif
    }


    return _TRUE;
}

//--------------------------------------------------
// Description  : Choose DB apply mode when _DB_APPLY_POLLING
// Input Value  : DBctrl, DataPathIndex, DB path select
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBApplyFRCModeSetDB(EnumInputDataPath enumSelectedDataPath)
{
    StructDBDataPathGroup structDataPathGroupInfo = {0};
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    BYTE ucGroupIndex = 0x00;

    // Divide input data path into several groups (e.g. (M1_M2, S1_S2) or (M2, M3, M4))
    ScalerGlobalIDDomainDBGetDataPathGroup(enumSelectedDataPath, &structDataPathGroupInfo);

    // Clear pending I/D domain DB ready bit
    ScalerGlobalIDDomainDBClearReadyBit(enumSelectedDataPath);

    // Set DB buffer start address
    ScalerGlobalIDDomainDBSetBufferAddress(&structDataPathGroupInfo);

    for(ucGroupIndex = 0; ucGroupIndex < (structDataPathGroupInfo.ucGroupNum); ucGroupIndex++)
    {
        BYTE ucDBctrl = ScalerGlobalGetIDomainDBApplyBit(structDataPathGroupInfo.penumGroup[ucGroupIndex]);
        EnumFRCChannelPageSelect enumFRCChPage = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(structDataPathGroupInfo.penumGroup[ucGroupIndex]));
        EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(structDataPathGroupInfo.penumGroup[ucGroupIndex]);

        structDataPathGroupInfo.pucFtearPrevent[ucGroupIndex] = (bit)GET_PAGED_BIT(ScalerFRCDispGetPageSelect(structDataPathGroupInfo.penumGroup[ucGroupIndex]), P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, _BIT6);

        for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
            {
                enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

                // Disable ftear prevent
                SET_PAGED_BYTE(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, 0x00);
            }
        }

        // Wait Iden_start event
        ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_START, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
        ScalerTimerDelayXms(2);

        // Set I apply bit
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
        ScalerDMB05DoubleBufferApply(enumSelectedDataPath); // DM B05 apply bit
#endif
#endif

        // Wait I double buffer
        ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, ucDBctrl, 0);

        // Enable FRC display freeze mode
        SET_PAGED_BIT(enumFRCChPage, P46_82_M_DISP_BLOCK_SEL, ~(_BIT4), _BIT4);

        // Enable FRC cap block free
        SET_PAGED_BIT(enumFRCChPage, P46_03_M_CAP_BLOCK_SEL, ~(_BIT3), _BIT3);

        ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);

        switch(GET_MEMORY_FRAME_BUFFER())
        {
            case _MEMORY_1_FRAME_BUFFER:
                ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                break;

            case _MEMORY_2_FRAME_BUFFER:
            default:
                ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                break;

            case _MEMORY_3_FRAME_BUFFER:
                ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                break;
        }

        // Disable FRC cap block free
        SET_PAGED_BIT(enumFRCChPage, P46_03_M_CAP_BLOCK_SEL, ~(_BIT3), 0x00);
    }

    // Check D domain status
    if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == _BIT0) &&
       (GET_DPLL_POWER_STATUS() == _TRUE))
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

        // Set D apply bit
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

        // Wait D double buffer
        ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);

        // Disable FRC disp freeze
        ScalerFRCDisplayFreezeDisable();

        // Wait Iden_stop event
        ScalerFRCDBWaitForIDomainEvent(_EVENT_IEN_STOP, enumSelectedDataPath);
    }

    for(ucGroupIndex = 0; ucGroupIndex < (structDataPathGroupInfo.ucGroupNum); ucGroupIndex++)
    {
        EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(structDataPathGroupInfo.penumGroup[ucGroupIndex]);

        if(structDataPathGroupInfo.pucFtearPrevent[ucGroupIndex] == _TRUE)
        {
            for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
                {
                    enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
                    SET_PAGED_BYTE(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, (_BIT6 | _FRC_FRAME_TEAR_PREVENT_LINE)); // margin = 2
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Set DB Cap/Disp buffer start address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetBufferAddress(StructDBDataPathGroup *pstDataPathGroupInfo)
{
    DWORD ulStartAddrBlk1 = 0x00000000;
    DWORD ulStartAddrBlk2 = 0x00000000;
    DWORD ulStartAddrBlk3 = 0x00000000;
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    EnumMDomainDisplayDataPath enumMDispPath = _MDOMAIN_DISP_PATH_M1;
    BYTE ucGroupIndex = 0x00;
    BYTE ucIndex = 0x00;

    for(ucGroupIndex = 0; ucGroupIndex < (pstDataPathGroupInfo->ucGroupNum); ucGroupIndex++)
    {
        enumMDispPath = ScalerFRCGetMDispPath(pstDataPathGroupInfo->penumGroup[ucGroupIndex]);

        for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ucIndex++)
        {
            if(CHK_FRC_PATH(pstDataPathGroupInfo->penumGroup[ucGroupIndex], GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
            {
                enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

                // Fetch current start address of block 1 & block 2
                switch(GET_MEMORY_FRAME_BUFFER())
                {
                    case _MEMORY_1_FRAME_BUFFER:
                    default:
                        ulStartAddrBlk1 = ScalerFRCGetCapAddress(enumPageSelect, _FRC_1ST_BLOCK);
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
                        if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
                        {
                            ulStartAddrBlk2 = ScalerFRCGetCapAddress(enumPageSelect, _FRC_2ND_BLOCK);
                        }
#endif
                        ulStartAddrBlk3 = 0;
                        break;
                    case _MEMORY_2_FRAME_BUFFER:
                        ulStartAddrBlk1 = ScalerFRCGetCapAddress(enumPageSelect, _FRC_1ST_BLOCK);
                        ulStartAddrBlk2 = ScalerFRCGetCapAddress(enumPageSelect, _FRC_2ND_BLOCK);
                        ulStartAddrBlk3 = 0;
                        break;
                    case _MEMORY_3_FRAME_BUFFER:
                        ulStartAddrBlk1 = ScalerFRCGetCapAddress(enumPageSelect, _FRC_1ST_BLOCK);
                        ulStartAddrBlk2 = ScalerFRCGetCapAddress(enumPageSelect, _FRC_2ND_BLOCK);
                        ulStartAddrBlk3 = ScalerFRCGetCapAddress(enumPageSelect, _FRC_3RD_BLOCK);
                        break;
                }

                // Toggle block start address
                if(ulStartAddrBlk1 < GET_FRC_START_ADDRESS() + GET_FRC_USE_ROW())
                {
                    switch(GET_MEMORY_FRAME_BUFFER())
                    {
                        case _MEMORY_1_FRAME_BUFFER:
                        default:
                            ulStartAddrBlk1 += GET_FRC_USE_ROW();
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
                            if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
                            {
                                ulStartAddrBlk2 += GET_FRC_USE_ROW();
                            }
#endif
                            ulStartAddrBlk3 = 0;
                            break;
                        case _MEMORY_2_FRAME_BUFFER:
                            ulStartAddrBlk1 += GET_FRC_USE_ROW();
                            ulStartAddrBlk2 += GET_FRC_USE_ROW();
                            ulStartAddrBlk3 = 0;
                            break;
                        case _MEMORY_3_FRAME_BUFFER:
                            ulStartAddrBlk1 += GET_FRC_USE_ROW();
                            ulStartAddrBlk2 += GET_FRC_USE_ROW();
                            ulStartAddrBlk3 += GET_FRC_USE_ROW();
                            break;
                    }
                }
                else
                {
                    switch(GET_MEMORY_FRAME_BUFFER())
                    {
                        case _MEMORY_1_FRAME_BUFFER:
                        default:
                            ulStartAddrBlk1 -= GET_FRC_USE_ROW();
                            ulStartAddrBlk2 = 0;
                            ulStartAddrBlk3 = 0;
                            break;
                        case _MEMORY_2_FRAME_BUFFER:
                            ulStartAddrBlk1 -= GET_FRC_USE_ROW();
                            ulStartAddrBlk2 -= GET_FRC_USE_ROW();
                            ulStartAddrBlk3 = 0;
                            break;
                        case _MEMORY_3_FRAME_BUFFER:
                            ulStartAddrBlk1 -= GET_FRC_USE_ROW();
                            ulStartAddrBlk2 -= GET_FRC_USE_ROW();
                            ulStartAddrBlk3 -= GET_FRC_USE_ROW();
                            break;
                    }
                }

                // Set capture block 1 address
                ScalerFRCSetCapAddress(enumPageSelect, _FRC_1ST_BLOCK, ulStartAddrBlk1);
                // Set capture block 2 address
                ScalerFRCSetCapAddress(enumPageSelect, _FRC_2ND_BLOCK, ulStartAddrBlk2);
                // Set capture block 3 address
                ScalerFRCSetCapAddress(enumPageSelect, _FRC_3RD_BLOCK, ulStartAddrBlk3);
            }
        }

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
        if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
        {
            ScalerFRCTopBottomModeDisplaySetting(ScalerFRCGetChannelFromInputpath(pstDataPathGroupInfo->penumGroup[ucGroupIndex]));
        }
        else
#endif
        {
#if(_COLOR_IP_3DDI == _ON)
            // only for eo mode, s2 3ddi
            if((GET_3DDI_STATUS(pstDataPathGroupInfo->penumGroup[ucGroupIndex]) == _ON) && (pstDataPathGroupInfo->penumGroup[ucGroupIndex] == _INPUT_PATH_S2))
            {
                WORD ustotalpixel = ScalerFRCGetDispTopLineTotalPixel(_FRC_SUB2_PAGE);
                // if imc on, use linetotalpixel; else, use s2 cap linestep
                ustotalpixel = ((GET_IMG_CMP_ENABLE((ScalerFRCImgCmpGetPara(ScalerRegionGetIndexFromInputDataPath(pstDataPathGroupInfo->penumGroup[ucGroupIndex])))) == _TRUE) ? ustotalpixel : ScalerFRCGetCapLinestep(_FRC_SUB2_PAGE));

                ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK));
                ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK));
                ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK, (ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK) + ustotalpixel));
                ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK, (ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK) + ustotalpixel));
            }
            else
#endif
            {
                for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ucIndex++)
                {
                    if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
                    {
                        enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
                        ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(enumPageSelect, _FRC_1ST_BLOCK));
                        ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(enumPageSelect, _FRC_2ND_BLOCK));
                    }
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Divide input data path into several groups
//                (e.g. (M1_M2, S1_S2) or (M2, M3, M4))
// Input Value  : DB path select, pointer to struct of group info
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBGetDataPathGroup(EnumInputDataPath enumSelectedDataPath, StructDBDataPathGroup *pstDataPathGroupInfo)
{
    enumSelectedDataPath = enumSelectedDataPath;

    pstDataPathGroupInfo->ucGroupNum = 0;

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2_S1_S2;
            }
            else
#endif
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
            }
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
            {
                if((enumSelectedDataPath & _INPUT_PATH_M1_M2_S1_S2) != 0x00)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2_S1_S2;
                }
                if((enumSelectedDataPath & _INPUT_PATH_S3_S4) != 0x00)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S3_S4;
                }
            }
            else
#endif
            {
                if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
                }

                if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
                {
#if(_COLOR_IP_3DDI == _ON)
                    if(((enumSelectedDataPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S2) && (GET_3DDI_STATUS(enumSelectedDataPath) == _ON))
                    {
                        pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S2;
                    }
                    else
#endif
                    {
                        pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S1_S2;
                    }
                }
            }
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
            {
                if((enumSelectedDataPath & _INPUT_PATH_M1_M2_S1_S2) != 0x00)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2_S1_S2;
                }
                if((enumSelectedDataPath & _INPUT_PATH_S3_S4) != 0x00)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S3_S4;
                }
            }
            else
#endif
            {
                if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
                }

                if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
                {
#if(_COLOR_IP_3DDI == _ON)
                    if(((enumSelectedDataPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S2) && (GET_3DDI_STATUS(enumSelectedDataPath) == _ON))
                    {
                        pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S2;
                    }
                    else
#endif
                    {
                        pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S1_S2;
                    }
                }
            }
            break;

        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:

            if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
            }
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                if((enumSelectedDataPath & _INPUT_PATH_S3_S4) != 0x00)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S3_S4;
                }
            }
            else
#endif
            {
                if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
                {
#if(_COLOR_IP_3DDI == _ON)
                    if(((enumSelectedDataPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S2) && (GET_3DDI_STATUS(enumSelectedDataPath) == _ON))
                    {
                        pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S2;
                    }
                    else
#endif
                    {
                        pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S1_S2;
                    }
                }
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
            }

            if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
            {
#if(_COLOR_IP_3DDI == _ON)
                if(((enumSelectedDataPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S2) && (GET_3DDI_STATUS(enumSelectedDataPath) == _ON))
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S2;
                }
                else
#endif
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S1_S2;
                }
            }
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
            }
            if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S1_S2;
            }
            if((enumSelectedDataPath & _INPUT_PATH_S3_S4) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S3_S4;
            }
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:
            if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
            }
            if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S1_S2;
            }
            if((enumSelectedDataPath & _INPUT_PATH_S3_S4) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S3_S4;
            }
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_3P_SKEW_B:
            if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
            }
            if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S1_S2;
            }
            if((enumSelectedDataPath & _INPUT_PATH_S3_S4) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S3_S4;
            }
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            for(BYTE ucDataPathIndex = 0; ucDataPathIndex < 4; ucDataPathIndex++)
            {
                EnumInputDataPath enumDataPath = ((BYTE)_BIT0 << ucDataPathIndex);

                if((enumSelectedDataPath & enumDataPath) == enumDataPath)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = enumDataPath;
                }
            }
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clear I/D domain DB ready bit of selected path
// Input Value  : DB path selection
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBClearReadyBit(EnumInputDataPath enumSelectedDataPath)
{
    BYTE ucIDomainDBCtrl = 0x00;

    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_M1) == _INPUT_PATH_M1) ? _BIT3 : 0x00);
    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_M2) == _INPUT_PATH_M2) ? _BIT2 : 0x00);
    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_S1) == _INPUT_PATH_S1) ? _BIT1 : 0x00);
    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_S2) == _INPUT_PATH_S2) ? _BIT0 : 0x00);
    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_S3) == _INPUT_PATH_S3) ? _BIT4 : 0x00);

    // Wait for finish of I-domain DB
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, ucIDomainDBCtrl) != 0x00)
    {
        ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, ucIDomainDBCtrl, 0);
    }

    // Wait for finish of D-domain DB
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT6) != 0x00)
    {
        // Check D domain status
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == _BIT0) &&
           (GET_DPLL_POWER_STATUS() == _TRUE))
        {
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);
        }
    }

    // Clear I-domain DB ready bit after timeout
    ScalerSetBit(P31_A0_I_DB_CTRL0, ~ucIDomainDBCtrl, 0x00);

    // Clear D-domain DB ready bit after timeout
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, 0x00);
}

#endif

//--------------------------------------------------
// Description  : Disable all Global Watch Dog
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDisableAllWatchDog(void)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        ScalerGlobalALLPathWatchDogDisable(enumCurrPath);
    }
}

//--------------------------------------------------
// Description  : Disable Global Watch Dog All Path
// Input Value  : enumInputDataPath --> input data path
// Output Value : None
//--------------------------------------------------
void ScalerGlobalALLPathWatchDogDisable(EnumInputDataPath enumInputDataPath)
{
    BYTE ucMeasurePage = ScalerMeasureGetOnlineMeasurePage(enumInputDataPath);
    EnumInputDataPath enumVgipPath = enumInputDataPath;

    // Set I-domain
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumVgipPath & enumCurrPath) != 0)
        {
            BYTE ucIRQPageOffset = GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex);
            BYTE ucOvfUdfOffset = GET_OVF_UDF_OFFSET(ucIndex);

#if((_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT) || (_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_IRQ_BACKGROUND))
            // Disable Input HVsync error IRQ
            ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT4, 0x00);

            // Disable Buffer under/overflow IRQ
            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
            // Disable WD freerun en
            ScalerSetBit(P0_0C_IRQ_WATCH_DOG_CTRL, ~_BIT7, 0x00);

            // Disable WD dvs timeout en
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable WD m1m2s1s2s3s4 bg en
            ScalerSetByte(P0_0D_BG_CTRL, 0x00);

            // Disable WD hv error en
            ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT3, 0x00);

            // Disable WD Buffer under/overflow en
            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
    }

    // Disable Input H/V Error WD & Enable Frame Sync WD & Input H/Vsync overflow WD
    SET_PAGED_BIT(ucMeasurePage, P3_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    SET_PAGED_BIT(ucMeasurePage, P3_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), 0x00);
    SET_PAGED_BIT(ucMeasurePage, P3_1C_M1_MEASURE_DUMMY0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Enabel Global Watch Dog by Path
// Input Value  : enumInputDataPath --> input data path
//                bEnable -->_ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalPathWatchDog(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    BYTE ucMeasurePage = ScalerMeasureGetOnlineMeasurePage(enumInputDataPath);
    EnumInputDataPath enumVgipPath = enumInputDataPath;

#if((_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT) || (_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_IRQ_BACKGROUND))
    bit bGarbageByIRQHandle = _FALSE;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        bGarbageByIRQHandle = _TRUE;
    }
    else
#endif
    {
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            bGarbageByIRQHandle = _TRUE;
        }
    }
#endif

    if(bEnable == _ENABLE)
    {
#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _OFF)
        if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
        {
#if(_DRR_SUPPORT == _ON)
            if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) == _DRR_NONE_TYPE)
#endif
            {
                // Set Free Run DVTotal = WD-Triggering DVTotal + 1 to Prevent DVTotal Too Long
                SET_FREE_RUN_DVTOTAL(GET_DIS_TIMING_GEN_WD_VTOTAL() + 1);

                ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);
            }
        }
#endif
    }

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    // Enable M1 & S1 WD only for even/odd mode
    if(enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
    {
        if(bEnable == _ENABLE)
        {
            enumVgipPath = _INPUT_PATH_M1;
        }
    }
    else if(enumInputDataPath == _INPUT_PATH_M1_M2)
    {
        enumVgipPath = _INPUT_PATH_M1;
    }
    else if(enumInputDataPath == _INPUT_PATH_S1_S2)
    {
        enumVgipPath = _INPUT_PATH_S1;
    }
    else if(enumInputDataPath == _INPUT_PATH_S3_S4)
    {
        enumVgipPath = _INPUT_PATH_S3;
    }
#endif

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_WATCH_DOG)
    if(ScalerGlobalGetDvsTimoutWDStatus(enumVgipPath) == _TRUE)
    {
        ScalerGlobalSetDvsTimeoutWatchDog(bEnable);
    }
#endif

    // Set I-domain
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumVgipPath & enumCurrPath) != 0)
        {
            BYTE ucIRQPageOffset = GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex);
            BYTE ucOvfUdfOffset = GET_OVF_UDF_OFFSET(ucIndex);
            BYTE ucBGCtrlBit = GET_BG_CTRL_BIT(ucIndex);

            if(bEnable == _ENABLE)
            {
                if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
                {
                    SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
                    SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
                }

#if((_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT) || (_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_IRQ_BACKGROUND))
                if(bGarbageByIRQHandle == _TRUE)
                {
                    // Clear Input HVsync error flag
                    ScalerSetBit(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

                    // Clear Buffer Status error flag
                    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // Enable Input HVsync error IRQ
                    ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT4, _BIT4);

                    // Enable Buffer Status IRQ
                    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
                }
                else
#endif
                {
                    // Disable Input H/V Error WD
                    ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT3, 0x00);

                    // Disable Buffer ovf/udf WD
                    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    // Disable WD Action: Free run
                    ScalerSetBit(P0_0C_IRQ_WATCH_DOG_CTRL, ~_BIT7, 0x00);

                    // Disable WD Action: Background
                    ScalerSetBit(P0_0D_BG_CTRL, ~ucBGCtrlBit, 0x00);

                    // Clear Input H/V Error flag
                    ScalerSetBit(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

                    // Clear Buffer Status error flag
                    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // Enable Input H/V Error WD
                    ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT3, _BIT3);

                    // Enable Buffer ovf/udf WD
                    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));

                    // WD Action: Free run
                    ScalerSetBit(P0_0C_IRQ_WATCH_DOG_CTRL, ~_BIT7, _BIT7);

                    // WD Action: Background
                    ScalerSetBit(P0_0D_BG_CTRL, ~ucBGCtrlBit, ucBGCtrlBit);
                }
            }
            else
            {
#if((_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT) || (_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_IRQ_BACKGROUND))
                if(bGarbageByIRQHandle == _TRUE)
                {
                    // Disable Input HVsync error IRQ
                    ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT4, 0x00);

                    // Disable Buffer Status IRQ
                    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                }
                else
#endif
                {
                    // Disable Input H/V Error WD
                    ScalerSetBit(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, ~_BIT3, 0x00);

                    // Disable Buffer ovf/udf WD
                    ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    // Disable WD Action: Free run
                    ScalerSetBit(P0_0C_IRQ_WATCH_DOG_CTRL, ~_BIT7, 0x00);

                    // Disable WD Action: Background
                    ScalerSetBit(P0_0D_BG_CTRL, ~ucBGCtrlBit, 0x00);
                }
            }
        }
    }

    // Set measure WD
    if(bEnable == _ENABLE)
    {
        // Disable WD First
        SET_PAGED_BIT(ucMeasurePage, P3_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        SET_PAGED_BIT(ucMeasurePage, P3_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), 0x00);
        SET_PAGED_BIT(ucMeasurePage, P3_1C_M1_MEASURE_DUMMY0, ~_BIT7, 0x00);

        // Clear flag
        SET_PAGED_BIT(ucMeasurePage, P3_16_MEAS_HS_VS_DELTA_IRQ, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

        // Enable measure overrange WD
#if(_VGA_SUPPORT == _ON)
        if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
        {
            SET_PAGED_BIT(ucMeasurePage, P3_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        }

        // Enable Input H/Vsync overflow WD (analog)
        SET_PAGED_BIT(ucMeasurePage, P3_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

#if((_DP_SUPPORT == _ON) && (_FW_ONESHOT_MODE_SUPPORT == _OFF))
        if((ScalerSyncGetPortType(ScalerFmtCnvGetInputPortType(enumInputDataPath)) == _PORT_DP) &&
           (ScalerDpMacStreamRxGetDPFRegenMode(ScalerFmtCnvGetInputPortType(enumInputDataPath)) != _DPF_MODE_FRAME_SYNC_BE))
#endif
        {
            // Enable Input Vsync timeout WD
            SET_PAGED_BIT(ucMeasurePage, P3_1C_M1_MEASURE_DUMMY0, ~_BIT7, _BIT7);
        }
    }
    else
    {
        // Disable Input H/V Error WD & Enable Frame Sync WD & Input H/Vsync overflow WD
        SET_PAGED_BIT(ucMeasurePage, P3_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        SET_PAGED_BIT(ucMeasurePage, P3_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), 0x00);
        SET_PAGED_BIT(ucMeasurePage, P3_1C_M1_MEASURE_DUMMY0, ~_BIT7, 0x00);
    }

#if((_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT) || (_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_IRQ_BACKGROUND))
    if(bGarbageByIRQHandle == _TRUE)
    {
        SET_INTERRUPT_ENABLE_STATUS(_INT_IMD, _ENABLE);
    }
#endif

    // Disable "WD disable overlay" in multi-display mode
#if(_OSD_WD_RESET_OVERLAY_DISABLE == _OFF)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT7, 0x00);
    }
    else
#endif
    {
        ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Get Fifo under/ overflow Watch Dog Setting
// Input Value  : none
// Output Value : EnumGlobalLineBufferFifoWDIrqStatus
//--------------------------------------------------
EnumGlobalLineBufferFifoWDIrqStatus ScalerGlobalGetFrameSyncLinebufferFifoWatchDogStatus(void)
{
    EnumGlobalLineBufferFifoWDIrqStatus enumGlobalLineBufferFifoStatus = _FRAME_BUFFER_NO_NEED_TO_CHK;

    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
       (ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE))
    {
        if(ScalerFRCGetLineBufferMode(_INPUT_PATH_M1) == _TRUE)
        {
            if(ScalerGetBit(PC0_04_M1_OVF_UDF_CTRL, (_BIT7 | _BIT6)) != 0x00)
            {
                enumGlobalLineBufferFifoStatus |= _LINE_BUFFER_FIFO_WD_EBABLE;
            }

            if(ScalerGetBit(PC0_04_M1_OVF_UDF_CTRL, (_BIT5 | _BIT4)) != 0x00)
            {
                enumGlobalLineBufferFifoStatus |= _LINE_BUFFER_FIFO_IRQ_EBABLE;
            }
        }
    }
    return enumGlobalLineBufferFifoStatus;
}

//--------------------------------------------------
// Description  : Enable/ Disable Mdomain Fifo Watch Dog when Frame sync line buffer
// Input Value  : EnumGlobalLineBufferFifoWDIrqStatus, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetFrameSyncLinebufferFifoWDIrq(EnumGlobalLineBufferFifoWDIrqStatus enumWDIrqStatus, bit bEnable)
{
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
       (ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE))
    {
        EnumInputDataPath enumInputDataPath = _INPUT_PATH_NONE;

        switch(GET_D_DOMAIN_PATH())
        {
            case _D_DOMAIN_1_PATH:
                enumInputDataPath = _INPUT_PATH_M1;
                break;

            case _D_DOMAIN_2_PATH:
            default:
                enumInputDataPath = _INPUT_PATH_M1_M2;
                break;

            case _D_DOMAIN_4_PATH:
                enumInputDataPath = _INPUT_PATH_M1_M2_S1_S2;
                break;
        }

        if(ScalerFRCGetLineBufferMode(enumInputDataPath) == _TRUE)
        {
            // Set I-domain
            for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

                if((enumInputDataPath & enumCurrPath) != 0)
                {
                    BYTE ucOvfUdfOffset = GET_OVF_UDF_OFFSET(ucIndex);

                    if((enumWDIrqStatus & _LINE_BUFFER_FIFO_WD_EBABLE) == _LINE_BUFFER_FIFO_WD_EBABLE)
                    {
                        if(bEnable == _ENABLE)
                        {
                            // Disable Buffer ovf/udf WD
                            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                            // Clear Buffer Status error flag
                            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                            // Enable Buffer ovf/udf WD
                            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                        }
                        else
                        {
                            // Disable Buffer ovf/udf WD
                            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                        }
                    }

                    if((enumWDIrqStatus & _LINE_BUFFER_FIFO_IRQ_EBABLE) == _LINE_BUFFER_FIFO_IRQ_EBABLE)
                    {
                        if(bEnable == _ENABLE)
                        {
                            // Clear Buffer Status error flag
                            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                            // Enable Buffer Status IRQ
                            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
                        }
                        else
                        {
                            // Disable Buffer Status IRQ
                            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                        }
                    }
                }
            }
        }
    }
}

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_WATCH_DOG)
//--------------------------------------------------
// Description  : Get DVS Timeout Watch Dog Status
// Input Value  : EnumInputDataPath
// Output Value : _TRUE: Setting DVS Timeout Watch Dog
//--------------------------------------------------
bit ScalerGlobalGetDvsTimoutWDStatus(EnumInputDataPath enumVgipPath)
{
    enumVgipPath = enumVgipPath;

    if(ScalerMDomainGetFrameSyncMode() == _FREE_RUN_MODE)
    {
        return _FALSE;
    }
    else
    {
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            return _TRUE;
        }
        else
        {
#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
            if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
            {
                if((GET_2P_FRAME_SYNC_MAIN() == _TRUE) &&
                   (enumVgipPath == _INPUT_PATH_M1))
                {
                    return _TRUE;
                }
                else if((GET_2P_FRAME_SYNC_MAIN() == _FALSE) &&
                        ((enumVgipPath == _INPUT_PATH_S1) || (enumVgipPath == _INPUT_PATH_S3)))
                {
                    return _TRUE;
                }
            }
#endif
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DVS Timeout Watch Dog Setting
// Input Value  : none
// Output Value : _ENABLE: DVS Timeout Watch Dog Enable
//--------------------------------------------------
bit ScalerGlobalGetDvsTimeoutWatchDogEnable(void)
{
    return (ScalerGetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, _BIT1) == _BIT1) ? _ENABLE : _DISABLE;
}

//--------------------------------------------------
// Description  : Get DVS Timeout Watch Dog Setting
// Input Value  : bEnable
// Output Value : none
//--------------------------------------------------
void ScalerGlobalSetDvsTimeoutWatchDog(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Disable Display Vsync Timeout WD
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Clear Display Vsync Timeout Flag
        ScalerGlobalClrDvsTimeoutFlag();

        // Enable Display Vsync Timeout WD
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Disable Display Vsync Timeout WD
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Clear Display Vsync Timeout Flag
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerGlobalClrDvsTimeoutFlag(void)
{
    ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT0);
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set I and D domain double buffer sync mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetDBSyncMode(void)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
    {
        // Set DB main/sub sync mode
        if(ScalerGetBit(P31_A1_I_DB_CTRL1, _BIT3) == 0x00)
        {
            // I_main_sub_sync select sub reference main: M1 IVS in 4 path mode
            ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), _BIT2);
        }
        else
        {
            // I_main_sub_sync select main reference sub: S2 IEN stop in 4 path mode
            ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), _BIT1);
        }

        ScalerSetBit(P31_A2_I_DB_CTRL2, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), 0x00);
        ScalerSetBit(P31_A2_I_DB_CTRL2, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Reset extension size to default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalResetExtension(void)
{
    // Reset format conversion extension
    ScalerSetBit(P31_63_FB_MASK_CTRL, ~_BIT0, 0x00);
    ScalerSetByte(P31_64_FRONT_MASK_NUM, 0x00);
    ScalerSetByte(P31_65_BACK_MASK_NUM, 0x00);
    ScalerSetBit(P31_66_EXTENSION_NUM, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset SD extension
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_3A_SD_OUT_EXTENSION_M1, 0x00);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_3A_SD_OUT_EXTENSION_M2, 0x00);
    ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_3A_SD_OUT_EXTENSION_S1, 0x00);
    ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_3A_SD_OUT_EXTENSION_S2, 0x00);

    // Reset I-domain drop extension
#if(_HW_DROP_EXTENSION_GEN != _GEN_NONE)
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, 0x00);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, 0x00);
    ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, 0x00);
    ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, 0x00);
#if(_HW_DROP_EXTENSION_GEN == _DROP_EXTENSION_GEN_1)
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_61_DROP_EXTENSION_START_M1, 0x00);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_61_DROP_EXTENSION_START_M2, 0x00);
    ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_61_DROP_EXTENSION_START_S1, 0x00);
    ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_61_DROP_EXTENSION_START_S2, 0x00);
#endif
#endif

    // Reset D-domain extension
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_FRONT, 0x00);
    ScalerSetDataPortByte(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_1F_DISPLAY_EXTENSION_FB_BACK, 0x00);

    // Reset D-domain extension extract
    ScalerSetBit(P24_30_EXTENSION_EXTRA_WIN, ~_BIT0, 0x00);
    ScalerSetBit(P5A_30_EXTENSION_EXTRA_WIN_BACK, ~_BIT0, 0x00);

    // Reset display conversion extension
    ScalerSetByte(P39_1E_DISP_TIMING_CTRL0, 0x00);

    // Reset OSD extension
    ScalerOsdSetExtension(0);
}
#endif

//--------------------------------------------------
// Description  : Division for (A * 2^pow) / ulB
// Input Value  : A, ucPow, ulB
// Output Value : (A * 2^pow) / B ratio in 32-bit precision
//--------------------------------------------------
DWORD ScalerGlobalComputeDwordPowDiv(DWORD ulA, BYTE ucPow, DWORD ulB)
{
    DWORD ulResult = 0;

    do
    {
        ulResult <<= 1;

        if(ulA >= ulB)
        {
            ulResult += (ulA / ulB);
            ulA %= ulB;
        }

        ulA <<= 1;
    }
    while(ucPow-- != 0);

    return (ulA >= ulB) ? (ulResult + 1) : ulResult;
}

//--------------------------------------------------
// Description  : Multiplication and Division for DWORD
// Input Value  : A, B, C
// Output Value : A * B / C in 32-bit precision
//--------------------------------------------------
DWORD ScalerGlobalComputeDwordMulDiv(DWORD ulA, DWORD ulB, DWORD ulC)
{
    return (DWORD)((QWORD)ulA * ulB / ulC);
}

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerGlobalEnableUnderflowMonitor(bit bEnable, EnumDDomainRegion enumDDomainRegion)
{
    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A1) == _DDOMAIN_RGN_R1_A1)
    {
        if(bEnable == _ENABLE)
        {
            // Threshold frame cnt: 2 display frames
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_53_UNDERFLOW_MONITOR_R1_A1_1, 0x02);

            // Enable underflow monitor and monitor frame cnt: 2 frame
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_52_UNDERFLOW_MONITOR_R1_A1_0, 0x80);
        }
        else
        {
            // Disable underflow monitor
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_52_UNDERFLOW_MONITOR_R1_A1_0, 0x00);
        }
    }

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R1_A2) == _DDOMAIN_RGN_R1_A2)
    {
        if(bEnable == _ENABLE)
        {
            // Threshold frame cnt: 2 display frames
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_56_UNDERFLOW_MONITOR_R1_A2_1, 0x02);

            // Enable underflow monitor and monitor frame cnt: 2 frame
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_55_UNDERFLOW_MONITOR_R1_A2_0, 0x80);
        }
        else
        {
            // Disable underflow monitor
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_55_UNDERFLOW_MONITOR_R1_A2_0, 0x00);
        }
    }
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A1) == _DDOMAIN_RGN_R2_A1)
    {
        if(bEnable == _ENABLE)
        {
            // Threshold frame cnt: 2 display frames
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_53_UNDERFLOW_MONITOR_R2_A1_1, 0x02);

            // Enable underflow monitor and monitor frame cnt: 2 frame
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_52_UNDERFLOW_MONITOR_R2_A1_0, 0x80);
        }
        else
        {
            // Disable underflow monitor
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_52_UNDERFLOW_MONITOR_R2_A1_0, 0x00);
        }
    }
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R2_A2) == _DDOMAIN_RGN_R2_A2)
    {
        if(bEnable == _ENABLE)
        {
            // Threshold frame cnt: 2 display frames
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_56_UNDERFLOW_MONITOR_R2_A2_1, 0x02);

            // Enable underflow monitor and monitor frame cnt: 2 frame
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_55_UNDERFLOW_MONITOR_R2_A2_0, 0x80);
        }
        else
        {
            // Disable underflow monitor
            ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_R2, _P80_2B_PT_55_UNDERFLOW_MONITOR_R2_A2_0, 0x00);
        }
    }
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A1) == _DDOMAIN_RGN_R3_A1)
    {
        if(bEnable == _ENABLE)
        {
            // Threshold frame cnt: 2 display frames
            ScalerSetDataPortByte(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_53_UNDERFLOW_MONITOR_R3_A1_1, 0x02);

            // Enable underflow monitor and monitor frame cnt: 2 frame
            ScalerSetDataPortByte(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_52_UNDERFLOW_MONITOR_R3_A1_0, 0x80);
        }
        else
        {
            // Disable underflow monitor
            ScalerSetDataPortByte(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_52_UNDERFLOW_MONITOR_R3_A1_0, 0x00);
        }
    }
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
    if((enumDDomainRegion & _DDOMAIN_RGN_R3_A2) == _DDOMAIN_RGN_R3_A2)
    {
        if(bEnable == _ENABLE)
        {
            // Threshold frame cnt: 2 display frames
            ScalerSetDataPortByte(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_56_UNDERFLOW_MONITOR_R3_A2_1, 0x02);

            // Enable underflow monitor and monitor frame cnt: 2 frame
            ScalerSetDataPortByte(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_55_UNDERFLOW_MONITOR_R3_A2_0, 0x80);
        }
        else
        {
            // Disable underflow monitor
            ScalerSetDataPortByte(PC0_2A_DISPLAY_FORMAT_ADDR_PORT_R3, _PC0_2B_PT_55_UNDERFLOW_MONITOR_R3_A2_0, 0x00);
        }
    }
#endif
#endif
}
#endif
#endif // End of #if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)

