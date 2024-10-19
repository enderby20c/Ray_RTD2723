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
// ID Code      : TypeC_Pmic_INTERSIL_RAA489800.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "../Header/TypeC_Pmic_INTERSIL_RAA489800.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_RAA489800_SUPPORT == _ON))

#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
#if(_D0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _OFF)
#warning "RAA489800 is set. _D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT should be ON!!!"
#endif
#endif // End of #if(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)

#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
#if(_D1_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D1_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D1_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D1_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _OFF)
#warning "RAA489800 is set. _D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT should be ON!!!"
#endif
#endif // End of #if(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)

#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
#if(_P0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _P0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_P0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _P0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _OFF)
#warning "RAA489800 is set. _P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT should be ON!!!"
#endif
#endif // End of #if(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)

#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
#if(_ADAPTOR_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _OFF)
#warning "RAA489800 is set. _ADAPTOR_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT should be ON!!!"
#endif
#endif // End of #if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)


//****************************************************************************
// CODE TABLES
//****************************************************************************
StructRAA489800SysCurrentLimitMap code tPmicRaa489800SysCurrLimitInitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_LB,
        _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_HB,
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_LB,
        _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_HB,
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_LB,
        _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_HB,
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_LB,
        _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_HB,
    },
};

StructRAA489800FRWRegulatingVoltMap code tPmicRaa489800FrwRegulatVoltInitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_15_FRW_REGULATING_VOLT_LB,
        _RAA489800_ADDR_15_FRW_REGULATING_VOLT_HB,
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_15_FRW_REGULATING_VOLT_LB,
        _RAA489800_ADDR_15_FRW_REGULATING_VOLT_HB,
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_15_FRW_REGULATING_VOLT_LB,
        _RAA489800_ADDR_15_FRW_REGULATING_VOLT_HB,
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_15_FRW_REGULATING_VOLT_LB,
        _RAA489800_ADDR_15_FRW_REGULATING_VOLT_HB,
    },
};

StructRAA489800FRWInputCurrentMap code tPmicRaa489800FrwInputCurrInitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_LB,
        _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_HB,
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_LB,
        _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_HB,
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_LB,
        _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_HB,
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_LB,
        _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_HB,
    },
};

StructRAA489800RVSRegulatingVoltMap code tPmicRaa489800RvsRegulatVoltInitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_49_RVS_REGULATING_VOLT_LB,
        _RAA489800_ADDR_49_RVS_REGULATING_VOLT_HB,
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_49_RVS_REGULATING_VOLT_LB,
        _RAA489800_ADDR_49_RVS_REGULATING_VOLT_HB,
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_49_RVS_REGULATING_VOLT_LB,
        _RAA489800_ADDR_49_RVS_REGULATING_VOLT_HB,
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_49_RVS_REGULATING_VOLT_LB,
        _RAA489800_ADDR_49_RVS_REGULATING_VOLT_HB,
    },
};

StructRAA489800RVSOutputCurrentMap code tPmicRaa489800RvsOutputCurrInitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_LB,
        _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_HB,
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_LB,
        _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_HB,
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_LB,
        _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_HB,
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_LB,
        _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_HB,
    },
};

StructRAA489800InputVoltLimitMap code tPmicRaa489800InputVoltLimitInitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_LB,
        _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_HB,
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_LB,
        _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_HB,
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_LB,
        _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_HB,
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_LB,
        _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_HB,
    },
};

StructRAA489800CR0RegisterMap code tPmicRaa489800CR0InitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_39_SysSideDischarge,            // Disable
        _RAA489800_ADDR_39_ADPSideDischarge,            // Disable
        _RAA489800_ADDR_39_VINRegulationLoop,           // Enable input voltage regulation loop
        0x00,                                           // Reserved
        _RAA489800_ADDR_39_FETShortTH,                  // 400mV
        _RAA489800_ADDR_39_RVSPhaseComparatorTH_1,      // 0mV

        _RAA489800_ADDR_39_RVSPhaseComparatorTH_2,      // 0mV
        _RAA489800_ADDR_39_FRWnRVSPhaseComparatorTH,    // 0mV
        _RAA489800_ADDR_39_FRWPhaseComparatorTH,        // 0mV
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_39_SysSideDischarge,            // Disable
        _RAA489800_ADDR_39_ADPSideDischarge,            // Disable
        _RAA489800_ADDR_39_VINRegulationLoop,           // Enable input voltage regulation loop
        0x00,                                           // Reserved
        _RAA489800_ADDR_39_FETShortTH,                  // 400mV
        _RAA489800_ADDR_39_RVSPhaseComparatorTH_1,      // 0mV

        _RAA489800_ADDR_39_RVSPhaseComparatorTH_2,      // 0mV
        _RAA489800_ADDR_39_FRWnRVSPhaseComparatorTH,    // 0mV
        _RAA489800_ADDR_39_FRWPhaseComparatorTH,        // 0mV
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_39_SysSideDischarge,            // Disable
        _RAA489800_ADDR_39_ADPSideDischarge,            // Disable
        _RAA489800_ADDR_39_VINRegulationLoop,           // Enable input voltage regulation loop
        0x00,                                           // Reserved
        _RAA489800_ADDR_39_FETShortTH,                  // 400mV
        _RAA489800_ADDR_39_RVSPhaseComparatorTH_1,      // 0mV

        _RAA489800_ADDR_39_RVSPhaseComparatorTH_2,      // 0mV
        _RAA489800_ADDR_39_FRWnRVSPhaseComparatorTH,    // 0mV
        _RAA489800_ADDR_39_FRWPhaseComparatorTH,        // 0mV
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_39_SysSideDischarge,            // Disable
        _RAA489800_ADDR_39_ADPSideDischarge,            // Disable
        _RAA489800_ADDR_39_VINRegulationLoop,           // Enable input voltage regulation loop
        0x00,                                           // Reserved
        _RAA489800_ADDR_39_FETShortTH,                  // 400mV
        _RAA489800_ADDR_39_RVSPhaseComparatorTH_1,      // 0mV

        _RAA489800_ADDR_39_RVSPhaseComparatorTH_2,      // 0mV
        _RAA489800_ADDR_39_FRWnRVSPhaseComparatorTH,    // 0mV
        _RAA489800_ADDR_39_FRWPhaseComparatorTH,        // 0mV
    },
};

StructRAA489800CR1RegisterMap code tPmicRaa489800CR1InitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_3C_ForceVDAV,                   // Disable force 5.04V VDAC
        _RAA489800_ADDR_3C_FRWnRVSOVEn,                 // Enable OV
        _RAA489800_ADDR_3C_SwitchingInFWDMode,          // Enable switching
        _RAA489800_ADDR_3C_FastREFMode,                 // Disable
        _RAA489800_ADDR_3C_BypassMode,                  // Disable
        _RAA489800_ADDR_3C_SysSideCurrentAmp,           // Enable system side current amplifier
        _RAA489800_ADDR_3C_OutputCurrentLimitAlert,     // Alert# will be asserted
        _RAA489800_ADDR_3C_SwitchingFreq_1,             // 1000khz

        _RAA489800_ADDR_3C_SwitchingFreq_2,             // 1000khz
        _RAA489800_ADDR_3C_AudioFilter,                 // Disable
        _RAA489800_ADDR_3C_RVSModeFunction,             // Disable Force Reverse mode function
        _RAA489800_ADDR_3C_SkipAutozero,                // Autozero during restart
        _RAA489800_ADDR_3C_SkipTrim,                    // Read trim during restart
        _RAA489800_ADDR_3C_SinkingCurrent,              // Sinking current during negative DAC transition enabled
        _RAA489800_ADDR_3C_DiodeEmulationComparator,    // Diode-emulation comparator enabled
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_3C_ForceVDAV,                   // Disable force 5.04V VDAC
        _RAA489800_ADDR_3C_FRWnRVSOVEn,                 // Enable OV
        _RAA489800_ADDR_3C_SwitchingInFWDMode,          // Enable switching
        _RAA489800_ADDR_3C_FastREFMode,                 // Disable
        _RAA489800_ADDR_3C_BypassMode,                  // Disable
        _RAA489800_ADDR_3C_SysSideCurrentAmp,           // Enable system side current amplifier
        _RAA489800_ADDR_3C_OutputCurrentLimitAlert,     // Alert# will be asserted
        _RAA489800_ADDR_3C_SwitchingFreq_1,             // 1000khz

        _RAA489800_ADDR_3C_SwitchingFreq_2,             // 1000khz
        _RAA489800_ADDR_3C_AudioFilter,                 // Disable
        _RAA489800_ADDR_3C_RVSModeFunction,             // Disable Force Reverse mode function
        _RAA489800_ADDR_3C_SkipAutozero,                // Autozero during restart
        _RAA489800_ADDR_3C_SkipTrim,                    // Read trim during restart
        _RAA489800_ADDR_3C_SinkingCurrent,              // Sinking current during negative DAC transition enabled
        _RAA489800_ADDR_3C_DiodeEmulationComparator,    // Diode-emulation comparator enabled
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_3C_ForceVDAV,                   // Disable force 5.04V VDAC
        _RAA489800_ADDR_3C_FRWnRVSOVEn,                 // Enable OV
        _RAA489800_ADDR_3C_SwitchingInFWDMode,          // Enable switching
        _RAA489800_ADDR_3C_FastREFMode,                 // Disable
        _RAA489800_ADDR_3C_BypassMode,                  // Disable
        _RAA489800_ADDR_3C_SysSideCurrentAmp,           // Enable system side current amplifier
        _RAA489800_ADDR_3C_OutputCurrentLimitAlert,     // Alert# will be asserted
        _RAA489800_ADDR_3C_SwitchingFreq_1,             // 1000khz

        _RAA489800_ADDR_3C_SwitchingFreq_2,             // 1000khz
        _RAA489800_ADDR_3C_AudioFilter,                 // Disable
        _RAA489800_ADDR_3C_RVSModeFunction,             // Disable Force Reverse mode function
        _RAA489800_ADDR_3C_SkipAutozero,                // Autozero during restart
        _RAA489800_ADDR_3C_SkipTrim,                    // Read trim during restart
        _RAA489800_ADDR_3C_SinkingCurrent,              // Sinking current during negative DAC transition enabled
        _RAA489800_ADDR_3C_DiodeEmulationComparator,    // Diode-emulation comparator enabled
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_3C_ForceVDAV,                   // Disable force 5.04V VDAC
        _RAA489800_ADDR_3C_FRWnRVSOVEn,                 // Enable OV
        _RAA489800_ADDR_3C_SwitchingInFWDMode,          // Enable switching
        _RAA489800_ADDR_3C_FastREFMode,                 // Disable
        _RAA489800_ADDR_3C_BypassMode,                  // Disable
        _RAA489800_ADDR_3C_SysSideCurrentAmp,           // Enable system side current amplifier
        _RAA489800_ADDR_3C_OutputCurrentLimitAlert,     // Alert# will be asserted
        _RAA489800_ADDR_3C_SwitchingFreq_1,             // 1000khz

        _RAA489800_ADDR_3C_SwitchingFreq_2,             // 1000khz
        _RAA489800_ADDR_3C_AudioFilter,                 // Disable
        _RAA489800_ADDR_3C_RVSModeFunction,             // Disable Force Reverse mode function
        _RAA489800_ADDR_3C_SkipAutozero,                // Autozero during restart
        _RAA489800_ADDR_3C_SkipTrim,                    // Read trim during restart
        _RAA489800_ADDR_3C_SinkingCurrent,              // Sinking current during negative DAC transition enabled
        _RAA489800_ADDR_3C_DiodeEmulationComparator,    // Diode-emulation comparator enabled
    },
};

StructRAA489800CR2RegisterMap code tPmicRaa489800CR2InitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_3D_FaultLatchOff,               // Controller latches off after WOC, UV, ADPOV or OTP fault
        _RAA489800_ADDR_3D_WOCFault,                    // Enable WOC
        0x00,                                           // Reserved
        _RAA489800_ADDR_3D_FRWFastSwap,                 // Disable forward fast swap
        _RAA489800_ADDR_3D_RVSFastSwap,                 // Disable reverse fast swap
        0x00,                                           // Reserved
        _RAA489800_ADDR_3D_ALERTDuration_1,             // 10ms

        _RAA489800_ADDR_3D_ALERTDuration_2,             // 10ms
        _RAA489800_ADDR_3D_ALERTDebounce,               // 7us
        _RAA489800_ADDR_3D_FRWRestartDebounce,          // Debounce time is 1.3s
        _RAA489800_ADDR_3D_FaultRestartDebounce,        // Debounce time is 1.3s or 150ms, depends on bit<13> setting
        _RAA489800_ADDR_3D_FaultRestartRVSEn,           // Debounce time is 1.3s
        _RAA489800_ADDR_3D_UVControl,                   // Enable UV
        _RAA489800_ADDR_3D_OVControl,                   // Enable OV
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_3D_FaultLatchOff,               // Controller latches off after WOC, UV, ADPOV or OTP fault
        _RAA489800_ADDR_3D_WOCFault,                    // Enable WOC
        0x00,                                           // Reserved
        _RAA489800_ADDR_3D_FRWFastSwap,                 // Disable forward fast swap
        _RAA489800_ADDR_3D_RVSFastSwap,                 // Disable reverse fast swap
        0x00,                                           // Reserved
        _RAA489800_ADDR_3D_ALERTDuration_1,             // 10ms

        _RAA489800_ADDR_3D_ALERTDuration_2,             // 10ms
        _RAA489800_ADDR_3D_ALERTDebounce,               // 7us
        _RAA489800_ADDR_3D_FRWRestartDebounce,          // Debounce time is 1.3s
        _RAA489800_ADDR_3D_FaultRestartDebounce,        // Debounce time is 1.3s or 150ms, depends on bit<13> setting
        _RAA489800_ADDR_3D_FaultRestartRVSEn,           // Debounce time is 1.3s
        _RAA489800_ADDR_3D_UVControl,                   // Enable UV
        _RAA489800_ADDR_3D_OVControl,                   // Enable OV
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_3D_FaultLatchOff,               // Controller latches off after WOC, UV, ADPOV or OTP fault
        _RAA489800_ADDR_3D_WOCFault,                    // Enable WOC
        0x00,                                           // Reserved
        _RAA489800_ADDR_3D_FRWFastSwap,                 // Disable forward fast swap
        _RAA489800_ADDR_3D_RVSFastSwap,                 // Disable reverse fast swap
        0x00,                                           // Reserved
        _RAA489800_ADDR_3D_ALERTDuration_1,             // 10ms

        _RAA489800_ADDR_3D_ALERTDuration_2,             // 10ms
        _RAA489800_ADDR_3D_ALERTDebounce,               // 7us
        _RAA489800_ADDR_3D_FRWRestartDebounce,          // Debounce time is 1.3s
        _RAA489800_ADDR_3D_FaultRestartDebounce,        // Debounce time is 1.3s or 150ms, depends on bit<13> setting
        _RAA489800_ADDR_3D_FaultRestartRVSEn,           // Debounce time is 1.3s
        _RAA489800_ADDR_3D_UVControl,                   // Enable UV
        _RAA489800_ADDR_3D_OVControl,                   // Enable OV
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_3D_FaultLatchOff,               // Controller latches off after WOC, UV, ADPOV or OTP fault
        _RAA489800_ADDR_3D_WOCFault,                    // Enable WOC
        0x00,                                           // Reserved
        _RAA489800_ADDR_3D_FRWFastSwap,                 // Disable forward fast swap
        _RAA489800_ADDR_3D_RVSFastSwap,                 // Disable reverse fast swap
        0x00,                                           // Reserved
        _RAA489800_ADDR_3D_ALERTDuration_1,             // 10ms

        _RAA489800_ADDR_3D_ALERTDuration_2,             // 10ms
        _RAA489800_ADDR_3D_ALERTDebounce,               // 7us
        _RAA489800_ADDR_3D_FRWRestartDebounce,          // Debounce time is 1.3s
        _RAA489800_ADDR_3D_FaultRestartDebounce,        // Debounce time is 1.3s or 150ms, depends on bit<13> setting
        _RAA489800_ADDR_3D_FaultRestartRVSEn,           // Debounce time is 1.3s
        _RAA489800_ADDR_3D_UVControl,                   // Enable UV
        _RAA489800_ADDR_3D_OVControl,                   // Enable OV
    },
};

StructRAA489800CR3RegisterMap code tPmicRaa489800CR3InitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_4C_PGOODSetting,                // PGGOD assert condition
        _RAA489800_ADDR_4C_BBDCMConductionTime,         // Shorter conduction time to reduce ripple
        _RAA489800_ADDR_4C_DigitalReset,                // Idle
        _RAA489800_ADDR_4C_REFAmplifier,                // Enable REF amplifier
        0x00,                                           // Reserved
        _RAA489800_ADDR_4C_INCurrentLimitLoop,          // Enable input current limit loop
        _RAA489800_ADDR_4C_CurrentLoopFBGain,           // Gain x 1
        0x00,                                           // Reserved

        _RAA489800_ADDR_4C_ForceOpMode,                 // No effect
        _RAA489800_ADDR_4C_FRWStartupDebounceTime,      // Debounce time is 200us
        _RAA489800_ADDR_4C_RVSStartupDebounceTime,      // Debounce time is 200us
        0x00,                                           // Reserved
        0x00,                                           // Reserved
        _RAA489800_ADDR_4C_ReReadPROGPinResistor,       // Re-read PROG pin resistor
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_4C_PGOODSetting,                // PGGOD assert condition
        _RAA489800_ADDR_4C_BBDCMConductionTime,         // Shorter conduction time to reduce ripple
        _RAA489800_ADDR_4C_DigitalReset,                // Idle
        _RAA489800_ADDR_4C_REFAmplifier,                // Enable REF amplifier
        0x00,                                           // Reserved
        _RAA489800_ADDR_4C_INCurrentLimitLoop,          // Enable input current limit loop
        _RAA489800_ADDR_4C_CurrentLoopFBGain,           // Gain x 1
        0x00,                                           // Reserved

        _RAA489800_ADDR_4C_ForceOpMode,                 // No effect
        _RAA489800_ADDR_4C_FRWStartupDebounceTime,      // Debounce time is 200us
        _RAA489800_ADDR_4C_RVSStartupDebounceTime,      // Debounce time is 200us
        0x00,                                           // Reserved
        0x00,                                           // Reserved
        _RAA489800_ADDR_4C_ReReadPROGPinResistor,       // Re-read PROG pin resistor
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_4C_PGOODSetting,                // PGGOD assert condition
        _RAA489800_ADDR_4C_BBDCMConductionTime,         // Shorter conduction time to reduce ripple
        _RAA489800_ADDR_4C_DigitalReset,                // Idle
        _RAA489800_ADDR_4C_REFAmplifier,                // Enable REF amplifier
        0x00,                                           // Reserved
        _RAA489800_ADDR_4C_INCurrentLimitLoop,          // Enable input current limit loop
        _RAA489800_ADDR_4C_CurrentLoopFBGain,           // Gain x 1
        0x00,                                           // Reserved

        _RAA489800_ADDR_4C_ForceOpMode,                 // No effect
        _RAA489800_ADDR_4C_FRWStartupDebounceTime,      // Debounce time is 200us
        _RAA489800_ADDR_4C_RVSStartupDebounceTime,      // Debounce time is 200us
        0x00,                                           // Reserved
        0x00,                                           // Reserved
        _RAA489800_ADDR_4C_ReReadPROGPinResistor,       // Re-read PROG pin resistor
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_4C_PGOODSetting,                // PGGOD assert condition
        _RAA489800_ADDR_4C_BBDCMConductionTime,         // Shorter conduction time to reduce ripple
        _RAA489800_ADDR_4C_DigitalReset,                // Idle
        _RAA489800_ADDR_4C_REFAmplifier,                // Enable REF amplifier
        0x00,                                           // Reserved
        _RAA489800_ADDR_4C_INCurrentLimitLoop,          // Enable input current limit loop
        _RAA489800_ADDR_4C_CurrentLoopFBGain,           // Gain x 1
        0x00,                                           // Reserved

        _RAA489800_ADDR_4C_ForceOpMode,                 // No effect
        _RAA489800_ADDR_4C_FRWStartupDebounceTime,      // Debounce time is 200us
        _RAA489800_ADDR_4C_RVSStartupDebounceTime,      // Debounce time is 200us
        0x00,                                           // Reserved
        0x00,                                           // Reserved
        _RAA489800_ADDR_4C_ReReadPROGPinResistor,       // Re-read PROG pin resistor
    },
};

StructRAA489800CR4RegisterMap code tPmicRaa489800CR4InitData[] =
{
    // D0 Port Setting
    {
        _RAA489800_ADDR_4E_ALERTLatch,                  // ALERT# signal auto-clear
        _RAA489800_ADDR_4E_ALERTClear,                  // Idle
        0x00,                                           // Reserved
        _RAA489800_ADDR_4E_FRWSleepMode,                // if FWREN=1 then controller is enabled, if FWREN=0 controller is disabled
        _RAA489800_ADDR_4E_RVSModeCurrentALERT,         // Enable

        0x00,                                           // Reserved
    },
    // D1 Port Setting
    {
        _RAA489800_ADDR_4E_ALERTLatch,                  // ALERT# signal auto-clear
        _RAA489800_ADDR_4E_ALERTClear,                  // Idle
        0x00,                                           // Reserved
        _RAA489800_ADDR_4E_FRWSleepMode,                // if FWREN=1 then controller is enabled, if FWREN=0 controller is disabled
        _RAA489800_ADDR_4E_RVSModeCurrentALERT,         // Enable

        0x00,                                           // Reserved
    },
    // P0 Port Setting
    {
        _RAA489800_ADDR_4E_ALERTLatch,                  // ALERT# signal auto-clear
        _RAA489800_ADDR_4E_ALERTClear,                  // Idle
        0x00,                                           // Reserved
        _RAA489800_ADDR_4E_FRWSleepMode,                // if FWREN=1 then controller is enabled, if FWREN=0 controller is disabled
        _RAA489800_ADDR_4E_RVSModeCurrentALERT,         // Enable

        0x00,                                           // Reserved
    },
    // Adaptor Setting
    {
        _RAA489800_ADDR_4E_ALERTLatch,                  // ALERT# signal auto-clear
        _RAA489800_ADDR_4E_ALERTClear,                  // Idle
        0x00,                                           // Reserved
        _RAA489800_ADDR_4E_FRWSleepMode,                // if FWREN=1 then controller is enabled, if FWREN=0 controller is disabled
        _RAA489800_ADDR_4E_RVSModeCurrentALERT,         // Enable

        0x00,                                           // Reserved
    },
};

StructRAA489800CompensationOffset code tPmicRaa489800CompensationOffset[] =
{
    // D0 Port Setting
    {
        _RAA489800_PMIC_0_OFFSET_VOLTAGE,               // Voltage Offset
        _RAA489800_PMIC_0_OFFSET_VOLTAGE_SIGN,          // Voltage Offset Sign
        _RAA489800_PMIC_0_OFFSET_CURRENT,               // Current Offset
        _RAA489800_PMIC_0_OFFSET_CURRENT_SIGN,          // Current Offset Sign
    },
    // D1 Port Setting
    {
        _RAA489800_PMIC_1_OFFSET_VOLTAGE,               // Voltage Offset
        _RAA489800_PMIC_1_OFFSET_VOLTAGE_SIGN,          // Voltage Offset Sign
        _RAA489800_PMIC_1_OFFSET_CURRENT,               // Current Offset
        _RAA489800_PMIC_1_OFFSET_CURRENT_SIGN,          // Current Offset Sign
    },
    // P0 Port Setting
    {
        _RAA489800_PMIC_2_OFFSET_VOLTAGE,               // Voltage Offset
        _RAA489800_PMIC_2_OFFSET_VOLTAGE_SIGN,          // Voltage Offset Sign
        _RAA489800_PMIC_2_OFFSET_CURRENT,               // Current Offset
        _RAA489800_PMIC_2_OFFSET_CURRENT_SIGN,          // Current Offset Sign
    },
    // Adaptor Setting
    {
        _RAA489800_PMIC_3_OFFSET_VOLTAGE,               // Voltage Offset
        _RAA489800_PMIC_3_OFFSET_VOLTAGE_SIGN,          // Voltage Offset Sign
        _RAA489800_PMIC_3_OFFSET_CURRENT,               // Current Offset
        _RAA489800_PMIC_3_OFFSET_CURRENT_SIGN,          // Current Offset Sign
    },
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructRAA489800SysCurrentLimitMap g_pstPmicRaa489800SysCurrLimit[4];
StructRAA489800FRWRegulatingVoltMap g_pstPmicRaa489800FrwRegulatVolt[4];
StructRAA489800FRWInputCurrentMap g_pstPmicRaa489800FrwInputCurrData[4];
StructRAA489800RVSRegulatingVoltMap g_pstPmicRaa489800RvsRegulatVolt[4];
StructRAA489800RVSOutputCurrentMap g_pstPmicRaa489800RvsOutputCurr[4];
StructRAA489800InputVoltLimitMap g_pstPmicRaa489800InputVoltLimit[4];

StructRAA489800CR0RegisterMap g_pstPmicRaa489800CR0Data[4];
StructRAA489800CR1RegisterMap g_pstPmicRaa489800CR1Data[4];
StructRAA489800CR2RegisterMap g_pstPmicRaa489800CR2Data[4];
StructRAA489800CR3RegisterMap g_pstPmicRaa489800CR3Data[4];
StructRAA489800CR4RegisterMap g_pstPmicRaa489800CR4Data[4];

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
StructRAA489800Info1RegisterMap g_pstPmicRaa489800Info1Data[4];
StructRAA489800Info2RegisterMap g_pstPmicRaa489800Info2Data[4];
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC Data initial value
    // CR0 default value
    g_pstPmicRaa489800CR0Data[ucDataIndex] = tPmicRaa489800CR0InitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL0, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR0Data[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write CR0 Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write CR0 Success", 0x00);

    // CR1 default value
    g_pstPmicRaa489800CR1Data[ucDataIndex] = tPmicRaa489800CR1InitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL1, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR1Data[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write CR1 Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write CR1 Success", 0x00);

    // CR2 default value
    g_pstPmicRaa489800CR2Data[ucDataIndex] = tPmicRaa489800CR2InitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL2, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR2Data[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write CR2 Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write CR2 Success", 0x00);


    // CR3 default value
    g_pstPmicRaa489800CR3Data[ucDataIndex] = tPmicRaa489800CR3InitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL3, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR3Data[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write CR3 Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write CR3 Success", 0x00);


    // CR4 default value
    g_pstPmicRaa489800CR4Data[ucDataIndex] = tPmicRaa489800CR4InitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL4, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR4Data[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write CR4 Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write CR4 Success", 0x00);

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_FOWARD_CONTROL(_D0_PMIC_FOWARD_CONTROL_ON);
        PCB_D0_PMIC_REVERSE_CONTROL(_D0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_FOWARD_CONTROL(_D1_PMIC_FOWARD_CONTROL_ON);
        PCB_D1_PMIC_REVERSE_CONTROL(_D1_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_FOWARD_CONTROL(_P0_PMIC_FOWARD_CONTROL_ON);
        PCB_P0_PMIC_REVERSE_CONTROL(_P0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_FOWARD_CONTROL(_ADAPTOR_PMIC_FOWARD_CONTROL_ON);
        PCB_ADAPTOR_PMIC_REVERSE_CONTROL(_ADAPTOR_PMIC_REVERSE_CONTROL_OFF);
    }

    // 0x14: 1.5A
    g_pstPmicRaa489800SysCurrLimit[ucDataIndex] = tPmicRaa489800SysCurrLimitInitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800SysCurrLimit[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write Current Limit Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write Current Limit LB", g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB);
    DebugMessageTypeC("Write Current Limit HB", g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB);


    // 0x15: 5.004V
    g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex] = tPmicRaa489800FrwRegulatVoltInitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write FWR Regualting Volt Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write FWR Regualting Volt LB", g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB);
    DebugMessageTypeC("Write FWR Regualting Volt HB", g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB);

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_FOWARD_CONTROL(_D0_PMIC_FOWARD_CONTROL_OFF);
        PCB_D0_PMIC_REVERSE_CONTROL(_D0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_FOWARD_CONTROL(_D1_PMIC_FOWARD_CONTROL_OFF);
        PCB_D1_PMIC_REVERSE_CONTROL(_D1_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_FOWARD_CONTROL(_P0_PMIC_FOWARD_CONTROL_OFF);
        PCB_P0_PMIC_REVERSE_CONTROL(_P0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_FOWARD_CONTROL(_ADAPTOR_PMIC_FOWARD_CONTROL_OFF);
        PCB_ADAPTOR_PMIC_REVERSE_CONTROL(_ADAPTOR_PMIC_REVERSE_CONTROL_OFF);
    }

    // 0x49:5.004V
    g_pstPmicRaa489800RvsRegulatVolt[ucDataIndex] = tPmicRaa489800RvsRegulatVoltInitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_RVS_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800RvsRegulatVolt[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write RVS REGULATING VOLTAGE Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write RVS REGULATING VOLTAGE LB", g_pstPmicRaa489800RvsRegulatVolt[ucDataIndex].ucRVSRegulatingVolt_LB);
    DebugMessageTypeC("Write RVS REGULATING VOLTAGE HB", g_pstPmicRaa489800RvsRegulatVolt[ucDataIndex].ucRVSRegulatingVolt_HB);

    // 0x4A:0.512A
    g_pstPmicRaa489800RvsOutputCurr[ucDataIndex] = tPmicRaa489800RvsOutputCurrInitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_RVS_OUTPUT_CURRENT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800RvsOutputCurr[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write RVS Output Current Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write RVS Output Current LB", g_pstPmicRaa489800RvsOutputCurr[ucDataIndex].ucRVSOutputCurrent_LB);
    DebugMessageTypeC("Write RVS Output Current HB", g_pstPmicRaa489800RvsOutputCurr[ucDataIndex].ucRVSOutputCurrent_HB);

    // 0x4B:4.096V
    g_pstPmicRaa489800InputVoltLimit[ucDataIndex] = tPmicRaa489800InputVoltLimitInitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_INPUT_VOLTAGE_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800InputVoltLimit[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write Input Voltage Limit Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write Input Voltage Limit LB", g_pstPmicRaa489800InputVoltLimit[ucDataIndex].ucInputVoltLimit_LB);
    DebugMessageTypeC("Write Input Voltage Limit HB", g_pstPmicRaa489800InputVoltLimit[ucDataIndex].ucInputVoltLimit_HB);

    // 0x3F: 5A
    // Must set at the final
    g_pstPmicRaa489800FrwInputCurrData[ucDataIndex] = tPmicRaa489800FrwInputCurrInitData[ucDataIndex];
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_FRW_INPUT_CURRENT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800FrwInputCurrData[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("Write FWR Regualting Volt Fail", 0x00);
        return;
    }

    DebugMessageTypeC("Write FWR Input Current LB", g_pstPmicRaa489800FrwInputCurrData[ucDataIndex].ucFRWInputCurrent_LB);
    DebugMessageTypeC("Write FWR Input Current HB", g_pstPmicRaa489800FrwInputCurrData[ucDataIndex].ucFRWInputCurrent_HB);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE pucTempData[2];
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;
    WORD usTemp = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    if(enumPowerDirection == _RAA489800_PMIC_SOURCE)
    {
        // Enable FWREN GPIO & Disable RVSEN GPIO
        if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
        {
            PCB_D0_PMIC_FOWARD_CONTROL(_D0_PMIC_FOWARD_CONTROL_ON);
            PCB_D0_PMIC_REVERSE_CONTROL(_D0_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
        {
            PCB_D1_PMIC_FOWARD_CONTROL(_D1_PMIC_FOWARD_CONTROL_ON);
            PCB_D1_PMIC_REVERSE_CONTROL(_D1_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
        {
            PCB_P0_PMIC_FOWARD_CONTROL(_P0_PMIC_FOWARD_CONTROL_ON);
            PCB_P0_PMIC_REVERSE_CONTROL(_P0_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
        {
            PCB_ADAPTOR_PMIC_FOWARD_CONTROL(_ADAPTOR_PMIC_FOWARD_CONTROL_ON);
            PCB_ADAPTOR_PMIC_REVERSE_CONTROL(_ADAPTOR_PMIC_REVERSE_CONTROL_OFF);
        }

        // Maximum Voltage Judgment
        if((usVoltage > 2100) || (usVoltage < 300))   // 3V ~ 21V
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Voltage Offset Compensation
        if(tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffsetSign == _RAA489800_PMIC_OFFSET_PLUS)
        {
            usVoltage = ((usVoltage + tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset) > 2100 ? 2100 : (usVoltage + tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset));
        }
        else
        {
            usVoltage = ((usVoltage - tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset) < 300 ? 300 : (usVoltage - tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset));
        }

        // Set VOUT Voltage
        usTemp = ((usVoltage * 10) + 6) / 12; // Round off
        usTemp = usTemp << 3;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB != pucTempData[0]) ||
           (g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB != pucTempData[1]))
        {
            g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB = pucTempData[0];
            g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB = pucTempData[1];

            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex])) == _FAIL)
            {
                DebugMessageTypeC("Write_FRW_REGULATING_VOLTAGE Fail", 0x00);
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }

            DebugMessageTypeC("usVoltage_LB", g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB);
            DebugMessageTypeC("usVoltage_HB", g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB);
        }


        // Maximum Current Judgment
        if(usCurrent > 1200)    // 12A
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Current Offset Compensation
        if(tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffsetSign == _RAA489800_PMIC_OFFSET_PLUS)
        {
            usCurrent = ((usCurrent + tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) < 1200 ? (usCurrent + tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) : 1200);
        }
        else
        {
            usCurrent = (usCurrent >= tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset ? (usCurrent - tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) : 0);
        }

        // Set VBUS Current Limit
        usTemp = ((usCurrent * 10) + 2) / 4; // Round off
        usTemp = usTemp << 2;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB != pucTempData[0]) ||
           (g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB != pucTempData[1]))
        {
            g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB = pucTempData[0];
            g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB = pucTempData[1];

            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800SysCurrLimit[ucDataIndex])) == _FAIL)
            {
                DebugMessageTypeC("Write_SYS_CURRENT_LIMIT Fail", 0x00);
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }

            DebugMessageTypeC("usCurrent_LB", g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB);
            DebugMessageTypeC("usCurrent_HB", g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE pucTempData[2];
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;
    WORD usTemp = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    if(enumPowerDirection == _RAA489800_PMIC_SOURCE)
    {
        // Enable FWREN GPIO & Disable RVSEN GPIO
        if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
        {
            PCB_D0_PMIC_FOWARD_CONTROL(_D0_PMIC_FOWARD_CONTROL_ON);
            PCB_D0_PMIC_REVERSE_CONTROL(_D0_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
        {
            PCB_D1_PMIC_FOWARD_CONTROL(_D1_PMIC_FOWARD_CONTROL_ON);
            PCB_D1_PMIC_REVERSE_CONTROL(_D1_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
        {
            PCB_P0_PMIC_FOWARD_CONTROL(_P0_PMIC_FOWARD_CONTROL_ON);
            PCB_P0_PMIC_REVERSE_CONTROL(_P0_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
        {
            PCB_ADAPTOR_PMIC_FOWARD_CONTROL(_ADAPTOR_PMIC_FOWARD_CONTROL_ON);
            PCB_ADAPTOR_PMIC_REVERSE_CONTROL(_ADAPTOR_PMIC_REVERSE_CONTROL_OFF);
        }

        // Maximum Voltage Judgment
        if((usVoltage > 2100) || (usVoltage < 300))   // 3V ~ 21V
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Voltage Offset Compensation
        if(tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffsetSign == _RAA489800_PMIC_OFFSET_PLUS)
        {
            usVoltage = ((usVoltage + tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset) > 2100 ? 2100 : (usVoltage + tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset));
        }
        else
        {
            usVoltage = ((usVoltage - tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset) < 300 ? 300 : (usVoltage - tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset));
        }

        // Set VOUT Voltage
        usTemp = ((usVoltage * 10) + 6) / 12; // Round off
        usTemp = usTemp << 3;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB != pucTempData[0]) ||
           (g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB != pucTempData[1]))
        {
            g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB = pucTempData[0];
            g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB = pucTempData[1];

            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex])) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }


        // Maximum Current Judgment
        if(usCurrent > 1200)    // 12A
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Current Offset Compensation
        if(tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffsetSign == _RAA489800_PMIC_OFFSET_PLUS)
        {
            usCurrent = ((usCurrent + tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) < 1200 ? (usCurrent + tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) : 1200);
        }
        else
        {
            usCurrent = (usCurrent >= tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset ? (usCurrent - tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) : 0);
        }

        // Set VBUS Current Limit
        usTemp = ((usCurrent * 10) + 2) / 4; // Round off
        usTemp = usTemp << 2;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB != pucTempData[0]) ||
           (g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB != pucTempData[1]))
        {
            g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB = pucTempData[0];
            g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB = pucTempData[1];

            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800SysCurrLimit[ucDataIndex])) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE pucTempData[2];
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;
    WORD usTemp = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    if(enumPowerDirection == _RAA489800_PMIC_SOURCE)
    {
        // Enable FWREN GPIO & Disable RVSEN GPIO
        if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
        {
            PCB_D0_PMIC_FOWARD_CONTROL(_D0_PMIC_FOWARD_CONTROL_ON);
            PCB_D0_PMIC_REVERSE_CONTROL(_D0_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
        {
            PCB_D1_PMIC_FOWARD_CONTROL(_D1_PMIC_FOWARD_CONTROL_ON);
            PCB_D1_PMIC_REVERSE_CONTROL(_D1_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
        {
            PCB_P0_PMIC_FOWARD_CONTROL(_P0_PMIC_FOWARD_CONTROL_ON);
            PCB_P0_PMIC_REVERSE_CONTROL(_P0_PMIC_REVERSE_CONTROL_OFF);
        }
        else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
        {
            PCB_ADAPTOR_PMIC_FOWARD_CONTROL(_ADAPTOR_PMIC_FOWARD_CONTROL_ON);
            PCB_ADAPTOR_PMIC_REVERSE_CONTROL(_ADAPTOR_PMIC_REVERSE_CONTROL_OFF);
        }

        // Maximum Voltage Judgment
        if((usVoltage > 2100) || (usVoltage < 300))   // 3V ~ 21V
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Voltage Offset Compensation
        if(tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffsetSign == _RAA489800_PMIC_OFFSET_PLUS)
        {
            usVoltage = ((usVoltage + tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset) > 2100 ? 2100 : (usVoltage + tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset));
        }
        else
        {
            usVoltage = ((usVoltage - tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset) < 300 ? 300 : (usVoltage - tPmicRaa489800CompensationOffset[ucDataIndex].ucVoltageOffset));
        }

        // Set VOUT Voltage
        usTemp = ((usVoltage * 10) + 6) / 12; // Round off
        usTemp = usTemp << 3;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB != pucTempData[0]) ||
           (g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB != pucTempData[1]))
        {
            g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB = pucTempData[0];
            g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB = pucTempData[1];

            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex])) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }


        // Maximum Current Judgment
        if(usCurrent > 1200)    // 12A
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Current Offset Compensation
        if(tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffsetSign == _RAA489800_PMIC_OFFSET_PLUS)
        {
            usCurrent = ((usCurrent + tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) < 1200 ? (usCurrent + tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) : 1200);
        }
        else
        {
            usCurrent = (usCurrent >= tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset ? (usCurrent - tPmicRaa489800CompensationOffset[ucDataIndex].ucCurrentOffset) : 0);
        }

        // Set VBUS Current Limit
        usTemp = ((usCurrent * 10) + 2) / 4; // Round off
        usTemp = usTemp << 2;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB != pucTempData[0]) ||
           (g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB != pucTempData[1]))
        {
            g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB = pucTempData[0];
            g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB = pucTempData[1];

            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800SysCurrLimit[ucDataIndex])) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
    }

    // Clear Voltage & Current Register
    g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB = 0;
    g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB = 0;
    g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB = 0;
    g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB = 0;

    // Disable FWREN & RVSEN GPIO
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_FOWARD_CONTROL(_D0_PMIC_FOWARD_CONTROL_OFF);
        PCB_D0_PMIC_REVERSE_CONTROL(_D0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_FOWARD_CONTROL(_D1_PMIC_FOWARD_CONTROL_OFF);
        PCB_D1_PMIC_REVERSE_CONTROL(_D1_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_FOWARD_CONTROL(_P0_PMIC_FOWARD_CONTROL_OFF);
        PCB_P0_PMIC_REVERSE_CONTROL(_P0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_FOWARD_CONTROL(_ADAPTOR_PMIC_FOWARD_CONTROL_OFF);
        PCB_ADAPTOR_PMIC_REVERSE_CONTROL(_ADAPTOR_PMIC_REVERSE_CONTROL_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
    }

    // Clear Voltage & Current Register
    g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB = 0;
    g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB = 0;
    g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB = 0;
    g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB = 0;

    // Disable FWREN & RVSEN GPIO
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_FOWARD_CONTROL(_D0_PMIC_FOWARD_CONTROL_OFF);
        PCB_D0_PMIC_REVERSE_CONTROL(_D0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_FOWARD_CONTROL(_D1_PMIC_FOWARD_CONTROL_OFF);
        PCB_D1_PMIC_REVERSE_CONTROL(_D1_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_FOWARD_CONTROL(_P0_PMIC_FOWARD_CONTROL_OFF);
        PCB_P0_PMIC_REVERSE_CONTROL(_P0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_FOWARD_CONTROL(_ADAPTOR_PMIC_FOWARD_CONTROL_OFF);
        PCB_ADAPTOR_PMIC_REVERSE_CONTROL(_ADAPTOR_PMIC_REVERSE_CONTROL_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
    }

    // Clear Voltage & Current Register
    g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_LB = 0;
    g_pstPmicRaa489800FrwRegulatVolt[ucDataIndex].ucFRWRegulatingVolt_HB = 0;
    g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_LB = 0;
    g_pstPmicRaa489800SysCurrLimit[ucDataIndex].ucSysCurrentLimit_HB = 0;

    // Disable FWREN & RVSEN GPIO
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_FOWARD_CONTROL(_D0_PMIC_FOWARD_CONTROL_OFF);
        PCB_D0_PMIC_REVERSE_CONTROL(_D0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_FOWARD_CONTROL(_D1_PMIC_FOWARD_CONTROL_OFF);
        PCB_D1_PMIC_REVERSE_CONTROL(_D1_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_FOWARD_CONTROL(_P0_PMIC_FOWARD_CONTROL_OFF);
        PCB_P0_PMIC_REVERSE_CONTROL(_P0_PMIC_REVERSE_CONTROL_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_FOWARD_CONTROL(_ADAPTOR_PMIC_FOWARD_CONTROL_OFF);
        PCB_ADAPTOR_PMIC_REVERSE_CONTROL(_ADAPTOR_PMIC_REVERSE_CONTROL_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Sys Discharge status
    g_pstPmicRaa489800CR0Data[ucDataIndex].b1CR0SysSideDischarge = enumEn;

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL0, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR0Data[ucDataIndex])) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}


//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Sys Discharge status
    g_pstPmicRaa489800CR0Data[ucDataIndex].b1CR0SysSideDischarge = enumEn;

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL0, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR0Data[ucDataIndex])) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Sys Discharge status
    g_pstPmicRaa489800CR0Data[ucDataIndex].b1CR0SysSideDischarge = enumEn;

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL0, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR0Data[ucDataIndex])) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
            PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE pucTempData[2];
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Read Operating Mode Status
    if(UserCommonUsbTypeCPmicIICRead_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_INFORMATION1, _RAA489800_SUBADDR_LENGTH, 2, pucTempData) == _FAIL)
    {
        return _TYPE_C_PMIC_NONE_MODE_OPERATION;
    }

    // Clear ALERT#
    g_pstPmicRaa489800CR4Data[ucDataIndex].b1CR4ALERTClear = 1;
    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_CONTROL4, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800CR4Data[ucDataIndex])) == _FAIL)
    {
        return _TYPE_C_PMIC_NONE_MODE_OPERATION;
    }

    // Return PMIC Operating Mode
    if((pucTempData[1] & 0x60) == 0x00)
    {
        return _TYPE_C_PMIC_CV_MODE_OPERATION;
    }
    else if((pucTempData[1] & 0x60) == 0x20)
    {
        return _TYPE_C_PMIC_CC_MODE_OPERATION;
    }
    else
    {
        return _TYPE_C_PMIC_TRANSITION_MODE;
    }

    return _TYPE_C_PMIC_NONE_MODE_OPERATION;
}
#endif // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
//--------------------------------------------------
// Description  : PMIC Status
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE pucTempData[2];
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    if(UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_DEVICE_ID, _RAA489800_SUBADDR_LENGTH, 1, pucTempData) == _FAIL)
    {
        DebugMessageTypeC("5.Pmic:Read DEVICE_ID Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    DebugMessageTypeC("5.Pmic:DEVICE_ID", pucTempData[0]);


    if(UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_MANUFACTURER_ID, _RAA489800_SUBADDR_LENGTH, 1, pucTempData) == _FAIL)
    {
        DebugMessageTypeC("5.Pmic:MANUFACTURER_ID Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    DebugMessageTypeC("5.Pmic:MANUFACTURER_ID", pucTempData[0]);


    if(UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, pucTempData) == _FAIL)
    {
        DebugMessageTypeC("5.Pmic:SYS_CURRENT_LIMIT Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    DebugMessageTypeC("5.Pmic:SYS_CURRENT_LIMIT_LB", pucTempData[0]);
    DebugMessageTypeC("5.Pmic:SYS_CURRENT_LIMIT_HB", pucTempData[1]);


    if(UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, pucTempData) == _FAIL)
    {
        DebugMessageTypeC("5.Pmic:FRW_REGULATING_VOLTAGE Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    DebugMessageTypeC("5.Pmic:FRW_REGULATING_VOLTAGE_LB", pucTempData[0]);
    DebugMessageTypeC("5.Pmic:FRW_REGULATING_VOLTAGE_HB", pucTempData[1]);


    if(UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_INFORMATION1, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800Info1Data[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("5.Pmic:Info1 Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    DebugMessageTypeC("5.Pmic:CCModeChange", g_pstPmicRaa489800Info1Data[ucDataIndex].b1INFO1CCModeChange);
    DebugMessageTypeC("5.Pmic:ADPsideOVP", g_pstPmicRaa489800Info1Data[ucDataIndex].b1INFO1ADPsideOV);
    DebugMessageTypeC("5.Pmic:OTP", g_pstPmicRaa489800Info1Data[ucDataIndex].b1INFO1OTP);
    DebugMessageTypeC("5.Pmic:SYSsideUVP", g_pstPmicRaa489800Info1Data[ucDataIndex].b1INFO1SYSsideUV);
    DebugMessageTypeC("5.Pmic:SYSsideOVP", g_pstPmicRaa489800Info1Data[ucDataIndex].b1INFO1SYSsideOV);
    DebugMessageTypeC("5.Pmic:WOCP", g_pstPmicRaa489800Info1Data[ucDataIndex].b1INFO1WOCP);
    DebugMessageTypeC("5.Pmic:ActiveControlLoop", g_pstPmicRaa489800Info1Data[ucDataIndex].b2INFO1ActiveControlLoop);
    DebugMessageTypeC("5.Pmic:ActiveReferenceCircuit", g_pstPmicRaa489800Info1Data[ucDataIndex].b1INFO1ActiveReferenceCircuit);


    if(UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _RAA489800_INFORMATION2, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicRaa489800Info2Data[ucDataIndex])) == _FAIL)
    {
        DebugMessageTypeC("5.Pmic:Info2 Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    DebugMessageTypeC("5.Pmic:PROGResistor", g_pstPmicRaa489800Info2Data[ucDataIndex].b5INFO2PROGResistor);
    DebugMessageTypeC("5.Pmic:OperationMode", g_pstPmicRaa489800Info2Data[ucDataIndex].b3INFO2OperationMode);
    DebugMessageTypeC("5.Pmic:StateMachineStatus", g_pstPmicRaa489800Info2Data[ucDataIndex].b4INFO2StateMachineStatus);
    DebugMessageTypeC("5.Pmic:FWRSwitchEn", g_pstPmicRaa489800Info2Data[ucDataIndex].b1INFO2FWRSwitchEn);


    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_EMB_TYPE_C_PMIC_DEBUG == _ON)

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC VBUS Current Reading
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : usCurrent : 0 ~ 500 (Unit = 10mA)
//--------------------------------------------------
WORD ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    return 0;
}
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
//--------------------------------------------------
// Description  : PMIC Vbus Force Off Config
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPinControl = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucPinControl = _D0_PMIC_FOWARD_CONTROL_OFF;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucPinControl = _D1_PMIC_FOWARD_CONTROL_OFF;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucPinControl = _P0_PMIC_FOWARD_CONTROL_OFF;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucPinControl = _ADAPTOR_PMIC_FOWARD_CONTROL_OFF;
    }

    // Set Vbus Force Off Type
    UserCommonUsbTypeCPmicSetForceOffControlType(enumTypeCPcbPort, _TYPE_C_PMIC_FORCE_OFF_BY_GPIO);

    // Set PMIC GPIO value
    UserCommonUsbTypeCPmicSetForceOffGpio(enumTypeCPcbPort, _CONFIG_TYPE_GPO_PP, ucPinControl);

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_RAA489800_SUPPORT == _ON))

