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
// ID Code      : SysPower.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_POWER__

#include "SysInclude.h"
#include "Power/SysPower.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPowerInfoType g_stPowerInfo;
StructPowerLoadData g_stPowerPowerLoadData;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Source Switch Flags
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerInitial(void)
{
    // Scaler whole chip reset
    ScalerGlobalWholeChipReset();

    // Scaler LVR Threshold Voltage Setting
    ScalerPowerLvrThresholdVoltage();

    // Internal oscillator trimming and on
    ScalerIOSCTrimming();

    // Power on Xtal Clock
    ScalerPowerXtalPower(_ON);

    // Power on M2PLL
    ScalerPLLM2PLLPower(_ON);

    ////////////////////////////
    // TYPE-C Initial Setting //
    ////////////////////////////
#if(_USB_SUPPORT == _ON)
    SysUsbInitial();
#endif

#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
    ScalerTypeCGpioModeInitialSetting();
#endif

#if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)
    ScalerPinshareTypeCAdcInitial();
#endif

#if(_TYPEC_IIC_SUPPORT == _ON)
    ScalerMcuTypecIICConfigSetting();
#endif


    ///////////////////
    // Load EDID     //
    ///////////////////

#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
    UserCommonNVRamRestoreEDID();
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
    UserCommonEdidLoadEmbeddedEdidData();
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    // External Edid GPO Initial
    UserCommonEdidMultiHdmiEdidInitial();
#endif

#if((_HDMI_SUPPORT == _ON) && (_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE))
    // External Edid Parser
    UserCommonEdidHdmiAllPortExternalEdidParser();
#endif

#if(_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxPhyDdcMappingAlignInAcOnProc();
#endif

    ///////////////////
    // Load HDCP Key //
    ///////////////////

    // HDCP Initial
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
    UserCommonNVRamRestoreHDCP();
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)

#if(_DIGITAL_PORT_SUPPORT == _ON)
    SysPowerLoadHDCPKey();
#endif

#if(_DELL_HDMI_HPD_DDC_STYLE_SUPPORT == _ON)
    if(UserInterfaceTmdsSetHdcpScdcStatusWhenAcOn() == _DISABLE_WHEN_AC_ON)
    {
#if(_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxAllPortChangeHdcpCap(_TMDS_HDCP_NONE);
#endif

#if(_HDMI20_SUPPORT == _ON)
        ScalerTmdsMacRxAllPortScdcEnableSetting(_DISABLE);
#endif
    }
#endif

    //////////////////////////
    // TMDS Initial Setting //
    //////////////////////////
#if(_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxAcOnInitial();
#if(_HDMI20_SUPPORT == _ON)
    UserCommonTmdsGetVersionScdcInfo();
#endif
#endif

    //////////////////////////
    // CEC Initial Setting //
    //////////////////////////
#if(_HDMI_CEC_SUPPORT == _ON)
    ScalerCecInitial();
    UserCommonCecFunctionEnable(UserInterfaceCecGetCecActive());

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
    UserCommonCecHalAcOnInitial();
#endif
#endif

    ////////////////////////
    // DP Initial Setting //
    ////////////////////////
#if(_DP_SUPPORT == _ON)
    SysDpInitial();
#endif

    /////////////////////////
    // DSC Initial Setting //
    /////////////////////////
#if(_DSC_DECODER_SUPPORT == _ON)
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
    ScalerDscDecoderInitial(_DSC_MAC_0);
#endif
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
    ScalerDscDecoderInitial(_DSC_MAC_1);
#endif
    SysDscDecoderMacArbiterInitial();
#endif

    ////////////////////////////////////
    // Audio Setting  //
    ////////////////////////////////////
#if(_AUDIO_SUPPORT == _ON)
    SysAudioInitialSetting();
#endif

    ////////////////////////////////////
    // External UART Initial Setting  //
    ////////////////////////////////////
#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
    ScalerMcuUartExt0Initial();

    ScalerMcuUartExt0SetBaudRate(_EXT_XTAL_CLK, UserInterfaceUartExt0GetPowerNormalBaudRate());
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
    ScalerMcuUartExt1Initial();

    ScalerMcuUartExt1SetBaudRate(_EXT_XTAL_CLK, UserInterfaceUartExt1GetPowerNormalBaudRate());
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
    ScalerMcuUartExt2Initial();

    ScalerMcuUartExt2SetBaudRate(_EXT_XTAL_CLK, UserInterfaceUartExt2GetPowerNormalBaudRate());
#endif

    // Display Output Pad Power On
    ScalerDisplayPadPower(_ON);

    //////////////////////
    // Memory Power Off //
    //////////////////////

    ScalerMemoryPowerControl(_OFF);

    ///////////////////////////////////////
    // All Group Power Cut and Isolation //
    ///////////////////////////////////////

    // SWR Core Power Voltage Control
    PCB_SWR_CORE_POWER_SETTING_AC_ON();

    ScalerPowerClockGatingControl(_POWER_ACTION_AC_ON_INITIAL);

    ScalerPowerIsolation(_POWER_ACTION_AC_ON_INITIAL);
}

//--------------------------------------------------
// Description  : Power Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerHandler(void)
{
    // The process will deal with all kinds of power changing by power action flag.
    switch(GET_TARGET_POWER_STATUS())
    {
        case _POWER_STATUS_NORMAL:

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_OFF:

                    if(SysPowerCheckNormal() == _TRUE)
                    {
#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);
                        CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
#endif

                        SysPowerSwitch(_POWER_ACTION_OFF_TO_NORMAL);
                    }
                    else
                    {
                        SysPowerSwitch(_POWER_ACTION_OFF_TO_FAKE_OFF);
                    }

                    break;

                case _POWER_STATUS_SAVING:
#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_RETIMER_MAC0_SUPPORT == _ON))
                    if(ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_EXIT_P3_PS)
                    {
                        SysPowerSwitch(_POWER_ACTION_PS_TO_NORMAL);
                        ScalerUsb3RepeaterMacClearLowPowerStateStatus();
                    }
                    else
#endif
                    {
                        SysPowerSwitch(_POWER_ACTION_PS_TO_NORMAL);
                    }
                    break;

                case _POWER_STATUS_AC_ON:
                    SysPowerSwitch(_POWER_ACTION_AC_ON_TO_NORMAL);
                    break;

                case _POWER_STATUS_NORMAL:

                    if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) || (GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE))
                    {
                        CLR_POWER_SWITCH_TO_FAKE_OFF();
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
                        CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
#endif

                        SysPowerSwitch(_POWER_ACTION_FAKE_OFF_TO_NORMAL);
                    }
                    else if(GET_POWER_SWITCH_TO_FAKE_SAVING() == _TRUE)
                    {
                        CLR_POWER_SWITCH_TO_FAKE_SAVING();

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_SAVING_TO_SAVING);
                        CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
#endif

                        SysPowerSwitch(_POWER_ACTION_FAKE_PS_TO_NORMAL);
                    }

                    break;

                default:
                    break;
            }

            SET_POWER_STATUS(_POWER_STATUS_NORMAL);

            break;

        case _POWER_STATUS_OFF:

            CLR_POWER_SWITCH_TO_FAKE_SAVING();

            // Clear Mode change flag
            CLR_MODE_STATE_CHANGE_MODE();

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_SAVING:
                    SysPowerSwitch(_POWER_ACTION_PS_TO_OFF);
                    SET_POWER_STATUS(_POWER_STATUS_OFF);

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_SAVING_TO_SAVING);
                    CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
#endif

                    break;

                case _POWER_STATUS_AC_ON:
                    SysPowerSwitch(_POWER_ACTION_AC_ON_TO_OFF);
                    SET_POWER_STATUS(_POWER_STATUS_OFF);
                    break;

                case _POWER_STATUS_NORMAL:

                    if(SysPowerCheckFakeOff() == _FALSE)
                    {
#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
                        if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_ENTER_P3_PS) || (ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_AT_P3_PS))
                        {
                            CLR_POWER_SWITCH_TO_FAKE_OFF();
                            ScalerPowerSetFakeSavingClockControl(_DISABLE);
                            SysPowerSwitch(_POWER_ACTION_NORMAL_TO_OFF);
                            ScalerUsb3RepeaterMacSetAtLowPowerStateStatus();
                            SET_POWER_STATUS(_POWER_STATUS_OFF);
                        }
                        else
#endif
                        {
                            CLR_POWER_SWITCH_TO_FAKE_OFF();
                            ScalerPowerSetFakeSavingClockControl(_DISABLE);
                            SysPowerSwitch(_POWER_ACTION_NORMAL_TO_OFF);
                            SET_POWER_STATUS(_POWER_STATUS_OFF);
                        }

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_SAVING_TO_SAVING);
                        CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
#endif
                    }
                    else
                    {
                        SET_POWER_SWITCH_TO_FAKE_OFF();
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_FAKE_OFF);
                    }
                    break;

                default:
                    break;
            }

            break;

        case _POWER_STATUS_SAVING:

            CLR_POWER_SWITCH_TO_FAKE_SAVING();
            ScalerPowerSetFakeSavingClockControl(_DISABLE);

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_NORMAL:

                    if(UserCommonPowerCheckFakeSaving() == _TRUE)
                    {
                        SET_POWER_SWITCH_TO_FAKE_SAVING();
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_FAKE_PS);
                    }
                    else
                    {
#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
                        if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_ENTER_P3_PS) || (ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_AT_P3_PS))
                        {
                            SysPowerSwitch(_POWER_ACTION_NORMAL_TO_PS);
                            ScalerUsb3RepeaterMacSetAtLowPowerStateStatus();
                            SET_POWER_STATUS(_POWER_STATUS_SAVING);
                        }
                        else
#endif
                        {
                            SysPowerSwitch(_POWER_ACTION_NORMAL_TO_PS);
                            SET_POWER_STATUS(_POWER_STATUS_SAVING);
                        }

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_SAVING_TO_SAVING);
                        CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
                        CLR_DP_HDCP_POWER_OFF_HANDSHAKE_TIMEOUT_FLAG();
#endif
                    }

                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }

    // Clear power action to avoid repeat calls in next circle.
    SET_TARGET_POWER_STATUS(_POWER_STATUS_NONE);
}

//--------------------------------------------------
// Description  : Deal With Power Manage According To Input Pamater
// Input Value  : ucSwitch    --> Power action description.
// Output Value : None
//--------------------------------------------------
void SysPowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_NORMAL_TO_PS:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif
            // Mode Power Saving Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_SAVING);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            UserCommonDataExchangeSendByte(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_POWER_TARGET_STATUS, _POWER_STATUS_SAVING);
#else
            SET_PCB_BACK_CHIP_POWER_CONTROL(_OFF);
#endif
#endif

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
#if(_FW_CPU32_MAIN_PROCESS_CPU == _CPU_ID_KCPU)
#if(_SCPU_SUPPORT == _ON)
            // Shut Down && Power Off 32bit Platform
            ScalerCpuCtrlSystemOff();
#endif
#else
            // switch clk source to IOSC
            ScalerGlobalCtrlSetSys32ClkSrc(_IOSC_CLK);
#endif
#endif

            ScalerMemoryPowerControl(_OFF);

#if(_HW_EPLL_SUPPORT == _ON)
            // Disable EMCU PLL 354MHz
            ScalerPLLEMCUPLLPower(_OFF);
#endif

#if(_HDMI_SUPPORT == _ON)
            if((UserInterfacePowerGetForcePSStatus() == _TRUE) || (UserInterfaceTmdsForcePSWakeupHpdToggle() == _USER_FORCE_PS_TMDS_HPD_TOGGLE))
            {
                SysTmdsRxSetPsWakeupHpdToggle();
            }
#endif

#if(_DP_SUPPORT == _ON)
            // DP Fake LT Protect
#if(_D0_DP_SUPPORT == _ON)
            ScalerDpAuxRxFakeLTProtect(_D0_INPUT_PORT);
#endif
#if(_D1_DP_SUPPORT == _ON)
            ScalerDpAuxRxFakeLTProtect(_D1_INPUT_PORT);
#endif
#if(_D2_DP_SUPPORT == _ON)
            ScalerDpAuxRxFakeLTProtect(_D2_INPUT_PORT);
#endif
#endif

#if(_USB_SUPPORT == _ON)
            SysUsbPowerSwitch(enumSwitch);
#endif

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
            ScalerUsbU2HostPowerControl(GET_U2HOST_OWENER(), _OFF);
#endif
#endif

            // Interface Power Saving Process
            ScalerSyncPowerProc(enumSwitch);

            // Set mcu module to power saving state
            ScalerMcuPwmControl(_POWER_STATUS_SAVING);

            // Set Pin configure to power saving state
            ScalerPinshareConfig(_POWER_STATUS_SAVING);

            // Some Case Power Fake Saving Proc

#if(_THERMAL_SENSOR_SUPPORT == _ON)
            // Thermal Sensor to power off state.
            ScalerThermalSensorControl(enumSwitch);
#endif

            // Display Output Pad Power Off
            ScalerDisplayPadPower(_OFF);

            // Enable all Clock Gating
            ScalerPowerClockGatingControl(enumSwitch);

            // Enable all power cut area.
            ScalerPowerIsolation(enumSwitch);

            // Select Internal Oscillator or EXT Xtal as System Clock.
            SysPowerSystemClockSelect(_SYS_PS_CLOCK_SOURCE);

#if(_HW_TOP_ON_POWER_DOMAIN_GEN != _TOP_ON_POWER_DOMAIN_GEN_0)
            // Misc IP in TOP_ON Domain Power Control
            ScalerPowerTopOnPowerControl(_POWER_CUT_ON);
#endif // End of #if(_HW_TOP_ON_POWER_DOMAIN_GEN != _TOP_ON_POWER_DOMAIN_GEN_0)

            // SWR Core Power Voltage Control
            PCB_SWR_CORE_POWER_SETTING_POWER_SAVING();

            // LDO low power control.
            ScalerLDOPowerControl(_POWER_STATUS_SAVING);

            // Set SI's powerboard to low power
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_ON);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            if(UserCommonDataExchangeCheckSendByteDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_POWER_TARGET_STATUS, _POWER_STATUS_SAVING, 50) == _TRUE)
            {
                DebugMessageSystem("Front chip send back chip power saving Done", 1);
            }
            else
            {
                DebugMessageSystem("Front chip send back chip power saving Fail", 1);
            }
#endif
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif
            SysSourcePowerOffProc();

            // Mode Power Off Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_OFF);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            UserCommonDataExchangeSendByte(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_POWER_TARGET_STATUS, _POWER_STATUS_OFF);
#else
            SET_PCB_BACK_CHIP_POWER_CONTROL(_OFF);
#endif
#endif

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
#if(_FW_CPU32_MAIN_PROCESS_CPU == _CPU_ID_KCPU)
#if(_SCPU_SUPPORT == _ON)
            // Shut Down && Power Off 32bit Platform
            ScalerCpuCtrlSystemOff();
#endif
#else
            // switch clk source to IOSC
            ScalerGlobalCtrlSetSys32ClkSrc(_IOSC_CLK);
#endif
#endif
            ScalerMemoryPowerControl(_OFF);

#if(_HW_EPLL_SUPPORT == _ON)
            // Disable EMCU PLL 354MHz
            ScalerPLLEMCUPLLPower(_OFF);
#endif

#if(_DP_SUPPORT == _ON)
            // DP Fake LT Protect
#if(_D0_DP_SUPPORT == _ON)
            ScalerDpAuxRxFakeLTProtect(_D0_INPUT_PORT);
#endif
#if(_D1_DP_SUPPORT == _ON)
            ScalerDpAuxRxFakeLTProtect(_D1_INPUT_PORT);
#endif
#if(_D2_DP_SUPPORT == _ON)
            ScalerDpAuxRxFakeLTProtect(_D2_INPUT_PORT);
#endif
#endif

#if(_USB_SUPPORT == _ON)
            SysUsbPowerSwitch(enumSwitch);
#endif

            // Interface Power Off Process
            ScalerSyncPowerProc(enumSwitch);

            // Set mcu module to power off state
            ScalerMcuPwmControl(_POWER_STATUS_OFF);

            // Set mcu module to power off state
            ScalerPinshareConfig(_POWER_STATUS_OFF);

#if(_THERMAL_SENSOR_SUPPORT == _ON)
            // Thermal Sensor to power off state.
            ScalerThermalSensorControl(enumSwitch);
#endif

            // Display Output Pad Power Off
            ScalerDisplayPadPower(_OFF);

            // Enable all Clock Gating
            ScalerPowerClockGatingControl(enumSwitch);

            // Enable all power cut area.
            ScalerPowerIsolation(enumSwitch);

            // Select internal oscillator as system clock.
            SysPowerSystemClockSelect(_IOSC_CLK);

#if(_HW_TOP_ON_POWER_DOMAIN_GEN != _TOP_ON_POWER_DOMAIN_GEN_0)
            // Misc IP in TOP_ON Domain Power Control
            ScalerPowerTopOnPowerControl(_POWER_CUT_ON);
#endif // End of #if(_HW_TOP_ON_POWER_DOMAIN_GEN != _TOP_ON_POWER_DOMAIN_GEN_0)

            // SWR Core Power Voltage Control
            PCB_SWR_CORE_POWER_SETTING_POWER_DOWN();

            // LDO low power control.
            ScalerLDOPowerControl(_POWER_STATUS_OFF);

            // Set SI's powerboard to low power
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_ON);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            if(UserCommonDataExchangeCheckSendByteDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_POWER_TARGET_STATUS, _POWER_STATUS_OFF, 20) == _TRUE)
            {
                DebugMessageSystem("Front chip send back chip power off Done", 1);
            }
            else
            {
                DebugMessageSystem("Front chip send back chip power off Fail", 1);
            }
#endif
#endif

            break;

        case _POWER_ACTION_PS_TO_OFF:

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            UserCommonDataExchangeSendByte(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_POWER_TARGET_STATUS, _POWER_STATUS_OFF);
#endif
#endif

            // User Power process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif

#if(_USB_SUPPORT == _ON)
            SysUsbPowerSwitch(enumSwitch);
#endif

            SysSourcePowerOffProc();

            // Interface Power Off Process
            ScalerSyncPowerProc(enumSwitch);

            // Set mcu module to power off state
            ScalerMcuPwmControl(_POWER_STATUS_OFF);

            // Pin configure to power off state.
            ScalerPinshareConfig(_POWER_STATUS_OFF);

#if(_THERMAL_SENSOR_SUPPORT == _ON)
            // Thermal Sensor to power off state.
            ScalerThermalSensorControl(enumSwitch);
#endif

            // Enable all Clock Gating
            ScalerPowerClockGatingControl(enumSwitch);

            // Enable all power cut area.
            ScalerPowerIsolation(enumSwitch);

            // SWR Core Power Voltage Control
            PCB_SWR_CORE_POWER_SETTING_POWER_DOWN();

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            if(UserCommonDataExchangeCheckSendByteDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_POWER_TARGET_STATUS, _POWER_STATUS_OFF, 20) == _TRUE)
            {
                DebugMessageSystem("Front chip send back chip power off Done", 2);
            }
            else
            {
                DebugMessageSystem("Front chip send back chip power off Fail", 2);
            }
#endif
#endif

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            if(enumSwitch == _POWER_ACTION_OFF_TO_NORMAL)
            {
                UserCommonDataExchangeSendByte(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_POWER_TARGET_STATUS, _POWER_STATUS_NORMAL);
            }
#else
            if((enumSwitch == _POWER_ACTION_AC_ON_TO_NORMAL) ||
               (enumSwitch == _POWER_ACTION_OFF_TO_NORMAL) ||
               (enumSwitch == _POWER_ACTION_PS_TO_NORMAL))
            {
                SET_PCB_BACK_CHIP_POWER_CONTROL(_ON);
            }
#endif
#endif

            // Wake up SI's powerboard
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_OFF);

            // LDO to normal setting.
            ScalerLDOPowerControl(_POWER_STATUS_NORMAL);

            // SWR Core Power Voltage Control
            PCB_SWR_CORE_POWER_SETTING_POWER_NORMAL();

            // Disable all power cut area.
            ScalerPowerIsolation(enumSwitch);

#if(_HW_TOP_ON_POWER_DOMAIN_GEN != _TOP_ON_POWER_DOMAIN_GEN_0)
            // Misc IP in TOP_ON Domain Power Control
            ScalerPowerTopOnPowerControl(_POWER_CUT_OFF);
#endif // End of #if(_HW_TOP_ON_POWER_DOMAIN_GEN != _TOP_ON_POWER_DOMAIN_GEN_0)

            // Disable all Clock Gating
            ScalerPowerClockGatingControl(enumSwitch);

            if(enumSwitch != _POWER_ACTION_AC_ON_TO_NORMAL)
            {
                // Display Output Pad Power ON
                ScalerDisplayPadPower(_ON);
            }

#if(_THERMAL_SENSOR_SUPPORT == _ON)
            // Thermal Sensor to power on state.
            ScalerThermalSensorControl(enumSwitch);
#endif

            // Select M2PLL as system clock.
            SysPowerSystemClockSelect(_M2PLL_CLK);

            // Recovery data in all power cut area
            SysPowerRecoverIsolationAreaData();

#if(_AUDIO_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _ON)
            // Audio ADC initial
            ScalerAudioADCInitial();
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
            // Audio DAC initial, Initialize Audio DAC to Gain Depop Time
            ScalerAudioDACInitial();
#endif
#endif

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
            // U2Host Power On from EHCI Owener
            ScalerUsbU2HostPowerControl(_U2HOST_OWNER_EHCI, _ON);
#endif
#endif

            // Sync Power On Process
            ScalerSyncPowerProc(enumSwitch);

            // Pin configure to normal state.
            ScalerPinshareConfig(_POWER_STATUS_NORMAL);

            // Set mcu module to normal state
            ScalerMcuPwmControl(_POWER_STATUS_NORMAL);

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

#if(_HW_EPLL_SUPPORT == _ON)
#if(_SCPU_SUPPORT == _ON)
            // Enable EMCU PLL 354MHz
            ScalerPLLEMCUPLLPower(_ON);
#else
            // Disable EMCU PLL
            ScalerPLLEMCUPLLPower(_OFF);
#endif
#endif

            ScalerMemoryPowerControl(_ON);

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            __initialize_off_region_sections();
            ScalerCpuHalResetInstructionCache();
            ScalerCpuHalCleanDataCache();

#if((_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE) && (_HW_CPU32_ALLOCATE_DDR_SPACE == _TRUE))
            __initialize_ddr_sections();
            ScalerCpuHalResetInstructionCache();
            ScalerCpuHalCleanDataCache();
#endif
#if(_SCPU_SUPPORT == _ON)
            // Bootup CPU32 CPU
            ScalerCpuCtrlBootInit();
#endif
#endif

            // Clear Source Ready Flag
            SysSourceInfoReset();

            // Set Display to Free Run Mode
            SysModeSetFreeRun();

            // User initial LUT/Latch/SRAM tabled data
            UserCommonPowerOnInitial();

#if(_VGA_SUPPORT == _ON)
            // Calibrate sync processor HS delay
            ScalerVgaTopModifyHsLatchEdgeDelay();
#endif

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif

#if(_USB_SUPPORT == _ON)
            SysUsbPowerSwitch(enumSwitch);
#endif

#if(_DP_SUPPORT == _ON)
            SysDpDcOffHPDToggleProc(enumSwitch);
#endif

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
            ScalerIRHWModeClrNECStatus();
#endif

#if((_GOSD_SUPPORT == _ON) && (_GOSD_FW_MODE == _GOSD_FW_ONE_CPU_MODE))
            ScalerGosdPowerOnInitial();
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            if(enumSwitch == _POWER_ACTION_OFF_TO_NORMAL)
            {
                if(UserCommonDataExchangeCheckSendByteDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_POWER_TARGET_STATUS, _POWER_STATUS_NORMAL, 20) == _TRUE)
                {
                    DebugMessageSystem("Front chip send back chip power normal Done", 1);
                }
                else
                {
                    DebugMessageSystem("Front chip send back chip power normal Fail", 1);
                }
            }
#endif
#endif
            break;

        case _POWER_ACTION_FAKE_PS_TO_NORMAL:

            // User Power Process
            UserInterfacePowerSwitch(_POWER_ACTION_PS_TO_NORMAL);

            SysSourceSearchTimeReset();

#if(_USB_SUPPORT == _ON)
            SysUsbPowerSwitch(enumSwitch);
#endif

            // Fake_PS Clock Recover
            if(ScalerPowerCheckFakeSavingClockControl() == _ENABLE)
            {
                // Select M2PLL as system clock.
                SysPowerSystemClockSelect(_M2PLL_CLK);

                // Enable Memory
                ScalerMemoryPowerControl(_ON);

                // Set DClk
                ScalerPLLSetDPLLFreq(GET_D_CLK_FREQ());

#if(_AUDIO_SUPPORT == _ON)
                // Audio Power Control

#if(_LINE_IN_SUPPORT == _ON)
                // Audio ADC initial
                ScalerAudioADCInitial();
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
                // Audio DAC initial, Initialize Audio DAC to Gain Depop Time
                ScalerAudioDACInitial();
#endif

                // Audio Power Action to Normal
                SysAudioPowerProc(_POWER_ACTION_PS_TO_NORMAL);
#endif // End of #if(_AUDIO_SUPPORT == _ON)
            }

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_PS:

            // Color power fake off
            UserCommonPowerColorFakePowerSwitch(_POWER_ACTION_NORMAL_TO_FAKE_PS);
            // User Power Process
            UserInterfacePowerSwitch(_POWER_ACTION_NORMAL_TO_PS);

            // Reset I-domain
            ScalerIDomainResetDataPath(_INPUT_PATH_ALL);

#if((_USB_SUPPORT == _ON) && (_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON))
            SysUsbPowerSwitch(enumSwitch);
#endif

            // Fake_PS Clock Recover
            if(ScalerPowerCheckFakeSavingClockControl() == _ENABLE)
            {
#if(_AUDIO_SUPPORT == _ON)
                // Audio Power Action to PS
                SysAudioPowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif

                // Select Internal Oscillator or EXT Xtal as System Clock.
                SysPowerSystemClockSelect(_SYS_PS_CLOCK_SOURCE);
            }

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

            // Color power fake off
            UserCommonPowerColorFakePowerSwitch(_POWER_ACTION_NORMAL_TO_FAKE_OFF);
            // User Power Process
            UserInterfacePowerSwitch(_POWER_ACTION_NORMAL_TO_OFF);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif

#if(_USB_SUPPORT == _ON)
            SysUsbPowerSwitch(enumSwitch);
#endif

            SysSourcePowerOffProc();

            // Interface Power Process
            ScalerSyncPowerProc(enumSwitch);

            // Mode Power Off Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_OFF);

            // Reset I-domain
            ScalerIDomainResetDataPath(_INPUT_PATH_ALL);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            UserCommonDataExchangeSendByte(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_POWER_TARGET_STATUS, _POWER_STATUS_OFF);

            if(UserCommonDataExchangeCheckSendByteDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_POWER_TARGET_STATUS, _POWER_STATUS_OFF, 20) == _TRUE)
            {
                DebugMessageSystem("Front chip send back chip power off Done", 3);
            }
            else
            {
                DebugMessageSystem("Front chip send back chip power off Fail", 3);
            }

#else
            SET_PCB_BACK_CHIP_POWER_CONTROL(_OFF);
#endif
#endif

            break;

        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            UserCommonDataExchangeSendByte(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_POWER_TARGET_STATUS, _POWER_STATUS_NORMAL);
#else
            SET_PCB_BACK_CHIP_POWER_CONTROL(_ON);
#endif
#endif

#if(_AUDIO_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _ON)
            // Audio ADC initial
            ScalerAudioADCInitial();
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
            // Audio DAC initial, Initialize Audio DAC to Gain Depop Time
            ScalerAudioDACInitial();
#endif
#endif

            // User Power Process
            UserInterfacePowerSwitch(_POWER_ACTION_OFF_TO_NORMAL);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(_POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_USB_SUPPORT == _ON)
            SysUsbPowerSwitch(enumSwitch);
#endif

#if(_DP_SUPPORT == _ON)
            SysDpDcOffHPDToggleProc(enumSwitch);
#endif

            ScalerSyncPowerProc(enumSwitch);

            // Set Display to Free Run Mode
            SysModeSetFreeRun();

            // User initial LUT/Latch/SRAM tabled data
            UserCommonPowerOnInitial();

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _OFF)
            if(UserCommonDataExchangeCheckSendByteDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_POWER_TARGET_STATUS, _POWER_STATUS_NORMAL, 20) == _TRUE)
            {
                DebugMessageSystem("Front chip send back chip power normal Done", 2);
            }
            else
            {
                DebugMessageSystem("Front chip send back chip power normal Fail", 2);
            }
#endif
#endif

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Current System Power Status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE SysPowerGetPowerStatus(void)
{
    switch(GET_POWER_STATUS())
    {
        case _POWER_STATUS_NORMAL:

            if(GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE)
            {
                return _POWER_STATUS_OFF;
            }

            if(GET_POWER_SWITCH_TO_FAKE_SAVING() == _TRUE)
            {
                return _POWER_STATUS_SAVING;
            }

            return GET_POWER_STATUS();

            break;

        default:

            return GET_POWER_STATUS();

            break;
    }

    return GET_POWER_STATUS();
}

//--------------------------------------------------
// Description  : Clock Select For System.
// Input Value  : ucClockSel    --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void SysPowerSystemClockSelect(BYTE ucClockSel)
{
    bit bInt31ScalerAllIrqTemp = _DISABLE;

#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
    DWORD ulUartExt0PNBaudRate = UserInterfaceUartExt0GetPowerNormalBaudRate();
    DWORD ulUartExt0PSBaudRate = UserInterfaceUartExt0GetPowerSavingBaudRate();
#endif
#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
    DWORD ulUartExt1PNBaudRate = UserInterfaceUartExt1GetPowerNormalBaudRate();
    DWORD ulUartExt1PSBaudRate = UserInterfaceUartExt1GetPowerSavingBaudRate();
#endif
#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
    DWORD ulUartExt2PNBaudRate = UserInterfaceUartExt2GetPowerNormalBaudRate();
    DWORD ulUartExt2PSBaudRate = UserInterfaceUartExt2GetPowerSavingBaudRate();
#endif

    if(ucClockSel == _M2PLL_CLK)
    {
        // Normal Mode Clock Setting
        if(ScalerPowerCheckFakeSavingClockControl() == _DISABLE)
        {
            // Power on Xtal Clock.
            ScalerPowerXtalPower(_ON);

            // Power on M2PLL.
            ScalerPLLM2PLLPower(_ON);
        }

        // Backup Global IRQ Control Status
        bInt31ScalerAllIrqTemp = ScalerGlobalGetInt31EnableStatus();

        ScalerGlobalSetInt31EnableStatus(_DISABLE);

        // Set Mcu/Flash Clock to M2PLL
        ScalerMcuFlashClockGroupSetting(_M2PLL_CLK);

        ScalerTimerWDRefClkChange();

        // Restore Global IRQ Control Status
        ScalerGlobalSetInt31EnableStatus(bInt31ScalerAllIrqTemp);

        // Set 10 seconds timeout count for WD CLK = 14.318M/27M
        ScalerWdtSetWdtOV(10000, _EXT_XTAL_CLK);

#if(_PWM_FUNCTION_SUPPORT == _ON)
        // PWM clock select to M2PLL.
        ScalerMcuPwmClockSel(_M2PLL_CLK);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
        // ADC clock select to external Xtal.
        ScalerMcuSarAdcClkSel(_EXT_XTAL_CLK);
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
        // Type-C Select to Internal Crystal
        ScalerTypeCAdcClkSel(_IOSC_CLK);
        ScalerTypeCClockSetting(_IOSC_CLK);
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
        // TCPM Select to Internal Crystal
        ScalerTypeCTcpmClockSetting(_IOSC_CLK);
#endif

        // Modify debounce settings for Xtal clock.
        ScalerMcuDdcDebounceSel(_EXT_XTAL_CLK);

        // Xtal CLK Select to external crystal clock.
        ScalerGlobalCrystalClkSel(_EXT_XTAL_CLK);

#if(_HW_IIC_SUPPORT == _ON)
        // Modify Hardware IIC frequency divisor for Xtal clock.
        ScalerMcuHwIICSetFreqDiv(_EXT_XTAL_CLK);
#endif

#if(_TYPEC_IIC_SUPPORT == _ON)
        // Modify Hardware IIC frequency divisor for Xtal clock.
        ScalerMcuTypecIICSetFreqDiv(_EXT_XTAL_CLK);
#endif

        // Modify 1us delay for Flash CLK = 24.3M
        ScalerMcu1usDelayCalc(_M2PLL_CLK);

        // Internal CLK Select to M2PLL.
        ScalerGlobalSystemClkSel(_M2PLL_CLK);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        // IRDA clock Select Xtal
        ScalerIRHWModeClockSel(_EXT_XTAL_CLK);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
        ScalerMcuUartExt0SetBaudRate(_M2PLL_CLK, ulUartExt0PNBaudRate);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
        ScalerMcuUartExt1SetBaudRate(_M2PLL_CLK, ulUartExt1PNBaudRate);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
        ScalerMcuUartExt2SetBaudRate(_M2PLL_CLK, ulUartExt2PNBaudRate);
#endif

#if(_SPI_SUPPORT == _ON)
        ScalerSpiSclkSel(_M2PLL_CLK);
#endif
    }
    else if(ucClockSel == _IOSC_CLK)
    {
        // Xtal CLK Select to INOSC
        ScalerGlobalCrystalClkSel(_IOSC_CLK);

        // Modify debounce settings for INOSC clock.
        ScalerMcuDdcDebounceSel(_IOSC_CLK);

#if(_HW_IIC_SUPPORT == _ON)
        // Modify Hardware IIC frequency divisor for IOSC clock.
        ScalerMcuHwIICSetFreqDiv(_IOSC_CLK);
#endif

#if(_TYPEC_IIC_SUPPORT == _ON)
        // Modify Type-C IIC frequency divisor for IOSC clock.
        ScalerMcuTypecIICSetFreqDiv(_IOSC_CLK);
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
        // Type-C Select to Internal Crystal
        ScalerTypeCAdcClkSel(_IOSC_CLK);
        ScalerTypeCClockSetting(_IOSC_CLK);
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
        // TCPM Select to Internal Crystal
        ScalerTypeCTcpmClockSetting(_IOSC_CLK);
#endif

        // Internal CLK Select to Internal Crystal.
        ScalerGlobalSystemClkSel(_IOSC_CLK);

#if(_PWM_FUNCTION_SUPPORT == _ON)
        // PWM clock select to Xtal.
        ScalerMcuPwmClockSel(_IOSC_CLK);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
        // ADC clock select to Internal Crystal.
        ScalerMcuSarAdcClkSel(_IOSC_CLK);
#endif
        // Set Mcu/Flash Clock to IOSC
        ScalerMcuFlashClockGroupSetting(_IOSC_CLK);

        ScalerTimerWDRefClkChange();

        // Set 10 seconds timeout count for WD CLK = 28M
        ScalerWdtSetWdtOV(10000, _IOSC_CLK);

        // Modify 1us delay for Flash CLK = 7M
        ScalerMcu1usDelayCalc(_IOSC_CLK);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        // IRDA clock Select IOSC
        ScalerIRHWModeClockSel(_IOSC_CLK);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
        ScalerMcuUartExt0SetBaudRate(_IOSC_CLK, ulUartExt0PSBaudRate);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
        ScalerMcuUartExt1SetBaudRate(_IOSC_CLK, ulUartExt1PSBaudRate);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
        ScalerMcuUartExt2SetBaudRate(_IOSC_CLK, ulUartExt2PSBaudRate);
#endif

#if(_SPI_SUPPORT == _ON)
        ScalerSpiSclkSel(_IOSC_CLK);
#endif

        // Check Fake_PS Clock Setting
        if(ScalerPowerCheckFakeSavingClockControl() == _ENABLE)
        {
            // PLL Control in Fake_PS Mode
            ScalerPLLFakePowerSavingControl();
        }
        else
        {
#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
            if(ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_NO_ACTION)
#endif
            {
                // Power down M2PLL.
                ScalerPLLM2PLLPower(_OFF);

                // Power down Xtal.
                ScalerPowerXtalPower(_OFF);
            }
        }
    }
    else
    {
        // Xtal CLK Select to External Xtal
        ScalerGlobalCrystalClkSel(_EXT_XTAL_CLK);

        // Modify debounce settings for External Xtal clock.
        ScalerMcuDdcDebounceSel(_EXT_XTAL_CLK);

#if(_HW_IIC_SUPPORT == _ON)
        // Modify Hardware IIC frequency divisor for External Xtal clock.
        ScalerMcuHwIICSetFreqDiv(_EXT_XTAL_CLK);
#endif

#if(_TYPEC_IIC_SUPPORT == _ON)
        // Modify Type-C IIC frequency divisor for IOSC clock.
        ScalerMcuTypecIICSetFreqDiv(_EXT_XTAL_CLK);
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
        // Type-C Select to Internal Crystal
        ScalerTypeCAdcClkSel(_IOSC_CLK);
        ScalerTypeCClockSetting(_IOSC_CLK);
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
        // TCPM Select to Internal Crystal
        ScalerTypeCTcpmClockSetting(_IOSC_CLK);
#endif

        // Internal CLK Select to External Xtal.
        ScalerGlobalSystemClkSel(_EXT_XTAL_CLK);

#if(_PWM_FUNCTION_SUPPORT == _ON)
        // PWM clock select to External Xtal.
        ScalerMcuPwmClockSel(_EXT_XTAL_CLK);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
        // ADC clock select to External Xtal.
        ScalerMcuSarAdcClkSel(_EXT_XTAL_CLK);
#endif
        // Set Mcu/Flash Clock to External Xtal
        ScalerMcuFlashClockGroupSetting(_EXT_XTAL_CLK);

        ScalerTimerWDRefClkChange();

        // Set 10 seconds timeout count for WD CLK = 14.318M/27M
        ScalerWdtSetWdtOV(10000, _EXT_XTAL_CLK);

        // Modify 1us delay for Flash CLK = 7M
        ScalerMcu1usDelayCalc(_EXT_XTAL_CLK);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        // IRDA clock Select External Xtal
        ScalerIRHWModeClockSel(_EXT_XTAL_CLK);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
        ScalerMcuUartExt0SetBaudRate(_EXT_XTAL_CLK, ulUartExt0PNBaudRate);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
        ScalerMcuUartExt1SetBaudRate(_EXT_XTAL_CLK, ulUartExt1PNBaudRate);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
        ScalerMcuUartExt2SetBaudRate(_EXT_XTAL_CLK, ulUartExt2PNBaudRate);
#endif

#if(_SPI_SUPPORT == _ON)
        ScalerSpiSclkSel(_EXT_XTAL_CLK);
#endif
    }
}
//--------------------------------------------------
// Description  : Set Power Action for other layer
// Input Value  : ucAction    --> Power Action
// Output Value : None
//--------------------------------------------------
void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus)
{
    // When OFF to Fake OFF & DC Key ON in One Main Loop, Clr Fake OFF Flag
    if((GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE) && (enumPorStatus == _POWER_STATUS_NORMAL))
    {
        CLR_POWER_SWITCH_TO_FAKE_OFF();
    }

    SET_TARGET_POWER_STATUS(enumPorStatus);
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Recover The Data of HDCP In Gdi Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerLoadHDCPKey(void)
{
    BYTE ucI = 0;
    BYTE pucTemp[64];

    // Enable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadKey(_ENABLE);

    for(ucI = 0; ucI < 20; ucI++)
    {
        UserCommonHdcpGetKey((ucI * 16), 16, pucTemp);
        ScalerSyncHdcpDownLoadKey(16, pucTemp);
    }

    // Get Hdcp Key
    UserCommonHdcpGetKeyBKsv(0, 5, pucTemp);

    // Write Hdcp Key To SDRAM
    ScalerSyncHdcpDownLoadBKsv(0, 5, pucTemp);

#if(_HDCP_2_2_SUPPORT == _ON)

    for(ucI = 0; ucI < 33; ucI++)
    {
        // Load HDCP 2.2 Key Certrx
        if(ucI < 32)
        {
            UserCommonHdcp2GetCertrx((ucI * 16), 16, pucTemp);
            ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP22_CERT_RX);
        }
        else
        {
            UserCommonHdcp2GetCertrx((ucI * 16), 10, pucTemp);
            ScalerHdcp2DownLoadCalculateKey((ucI * 16), 10, pucTemp, _HDCP22_CERT_RX);
        }
    }

    for(ucI = 0; ucI < 8; ucI++)
    {
        // d key, Npinv, RRmodN, public key n
        UserCommonHdcp2GetRSADkey((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP22_RSA_D_KEY);

        UserCommonHdcp2GetRSARRModN((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP22_RSA_RRMODN_KEY);
    }

    UserCommonHdcp2GetRSANpinv(0, 4, pucTemp);
    ScalerHdcp2DownLoadCalculateKey(0, 4, pucTemp, _HDCP22_RSA_N_PINV);

    UserCommonHdcp2GetLCKey(0, 16, pucTemp);
    ScalerHdcp2DownLoadCalculateKey(0, 16, pucTemp, _HDCP22_LC);

    for(ucI = 0; ucI < 5; ucI++)
    {
        UserCommonHdcp2GetRSAKPriv(ucI * 64, 64, pucTemp);
        ScalerHdcp2RxPairingCalculate(pucTemp, ucI);
    }
    ScalerHdcp2RxPairingCalculate(pucTemp, 5);

#endif

    // Disable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadKey(_DISABLE);
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Recover The Data of HDCP for DPTX
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerLoadDPTxHDCPKey(void)
{
    BYTE ucI = 0;
    BYTE pucTemp[16];

    // Enable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadDPTxKey(_ENABLE);

    for(ucI = 0; ucI < 20; ucI++)
    {
        UserCommonHdcpGetTxKey((ucI * 16), 16, pucTemp);
        ScalerSyncHdcpDownLoadDPTxAKey(16, pucTemp);
    }

    // Get Hdcp Key
    UserCommonHdcpGetTxKeyAKsv(0, 5, &pucTemp[5]);

    // Write Hdcp Key To SDRAM
    ScalerSyncHdcpDownLoadDPTxAKsv(0, 5, &pucTemp[5]);

    // Disable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadDPTxKey(_DISABLE);
}
#endif
#endif

//--------------------------------------------------
// Description  : Recover The Data after Power Cut.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerRecoverIsolationAreaData(void)
{
    ScalerPowerRecoverIsolationAreaData();

    if(GET_POWER_LOAD_DPTX_HDCP_KEY_FLG() == _TRUE)
    {
        CLR_POWER_LOAD_DPTX_HDCP_KEY_FLG();

#if((_DIGITAL_PORT_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
        SysPowerLoadDPTxHDCPKey();
#endif
    }
}

//--------------------------------------------------
// Description  : Check Whther go to Fake Saving Mode
// Input Value  : None
// Output Value : _TRUE => Fake Saving
//--------------------------------------------------
bit SysPowerCheckFakeSaving(void)
{
    DebugMessageMst("SysPower Check Fake Saving", 0x00);

    if(UserInterfacePowerGetFakePSStatus() == _FORCE_FAKE_POWER_SAVING)
    {
        return _TRUE;
    }

    if(UserInterfaceDisplayGetNoSupportStatus() == _NO_SUPPORT_TRUE)
    {
        return _TRUE;
    }

#if(_DP_SUPPORT == _ON)
    if(ScalerSyncDpFakePowerSavingCheck() == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_AUDIO_SUPPORT == _ON)
#if(_SLEEP_AUDIO_SUPPORT == _ON)
    if(SysAudioPlayingAloneStatus() == _TRUE)
    {
        return _TRUE;
    }
#endif
#endif

#if((_AUDIO_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    if(ScalerAudioGetInternalAudioGenEnable(_NO_INPUT_PORT) == _ENABLE)
    {
        return _TRUE;
    }
#endif

#if((_USB_HUB_SUPPORT == _ON) && (_USB3_REPEATER_SUPPORT == _ON))
    // Updata & Judge USB Hub Power Saving Status
    if(SysUsbHubJudgeUsbPSStatus() == _PS_USB3_ENABLE)
    {
#if(_FAKE_POWER_SAVING_CONTROL_U3_SUPPORT == _ON)
        // Enable Fake_PS PLL Control
        ScalerPowerSetFakeSavingClockControl(_ENABLE);
#endif

        return _TRUE;
    }
#endif

#if((_DP_HDCP_RX_SUPPORT == _ON) && (_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON))
    if(GET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK() == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        if(ScalerDpHdcpRxHandshakeStartCheck() == _TRUE)
        {
            // In Power Switch From Normal To Saving Flow, Check If Handshake Start and No Done, Switch To Fake Saving
            ScalerTimerReactiveTimerEvent(_POWER_OFF_HDCP_HANDSHAKE_TIMEOUT, _SYSTEM_TIMER_EVENT_POWER_FAKE_SAVING_TO_SAVING);

            SET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();

            return _TRUE;
        }
    }
#endif

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
#if((_TYPE_C_EMB_CTS_FLOW == _ON) && (_TYPE_C_EMB_CTS_FORCE_POWER_NORMAL == _ON))
    return _TRUE;
#endif
#endif

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    if(ScalerFwUpdateForegroundGetStatus() == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
    if(SysUsbU2HostWorkOnCommunication() == _TRUE)
    {
        return _TRUE;
    }
#endif
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
    if(ScalerHdmiFrlMacRxEnterFakePowerSavingCheck() == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
    if(g_bUsbBillboardIspProcessing == _TRUE)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Whether go to Fake Off Mode
// Input Value  : None
// Output Value : _TRUE => Fake Off
//--------------------------------------------------
bit SysPowerCheckFakeOff(void)
{
    if(UserInterfacePowerGetFakeOffStatus() == _FORCE_FAKE_POWER_OFF)
    {
        return _TRUE;
    }

    // If Power Action Switch Normal to Fake OFF, Else Power Action Switch Fake Off to OFF
    if(GET_POWER_SWITCH_TO_FAKE_OFF() != _TRUE)
    {
#if(_DP_MST_SUPPORT == _ON)
        if(ScalerSyncDpFakePowerOffCheck() == _TRUE)
        {
            ScalerTimerActiveTimerEvent(_POWER_FAKE_OFF_TO_OFF_TIMEOUT, _SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

            return _TRUE;
        }
#endif

#if((_USB_HUB_SUPPORT == _ON) && (_USB3_REPEATER_SUPPORT == _ON))
        // Updata & Judge USB Hub Power Down Status
        if(SysUsbHubJudgeUsbPDStatus() == _PD_USB3_ENABLE)
        {
            return _TRUE;
        }
#endif

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
        if(g_bUsbBillboardIspProcessing == _TRUE)
        {
            return _TRUE;
        }
#endif

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
        if(SysUsbU2HostWorkOnCommunication() == _TRUE)
        {
            return _TRUE;
        }
#endif
#endif

#if((_DP_HDCP_RX_SUPPORT == _ON) && (_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON))
        if(GET_DP_DC_OFF_HPD_HIGH() == _TRUE)
        {
            if(ScalerDpHdcpRxHandshakeStartCheck() == _TRUE)
            {
                // In Power Switch From Normal To Off Flow, Check If Handshake Start and No Done, Switch To Fake Off
                ScalerTimerReactiveTimerEvent(_POWER_OFF_HDCP_HANDSHAKE_TIMEOUT, _SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

                SET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();

                return _TRUE;
            }
            else
            {
                CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
            }
        }
#endif
    }
    else
    {
#if(_DP_MST_SUPPORT == _ON)
        if(ScalerSyncDpFakePowerOffCheck() == _TRUE)
        {
            ScalerTimerActiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

            return _TRUE;
        }
        else
#endif
        {
#if((_USB_HUB_SUPPORT == _ON) && (_USB3_REPEATER_SUPPORT == _ON))
            // Updata & Judge USB Hub Power Down Status
            if(SysUsbHubJudgeUsbPDStatus() == _PD_USB3_ENABLE)
            {
                return _TRUE;
            }
#endif

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
            if(g_bUsbBillboardIspProcessing == _TRUE)
            {
                return _TRUE;
            }
#endif

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
            if(SysUsbU2HostWorkOnCommunication() == _TRUE)
            {
                return _TRUE;
            }
#endif
#endif
        }

#if((_DP_HDCP_RX_SUPPORT == _ON) && (_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON))
        if(GET_DP_DC_OFF_HPD_HIGH() == _TRUE)
        {
            if(GET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK() == _TRUE)
            {
                return _TRUE;
            }
            else if(ScalerDpHdcpRxHandshakeStartCheck() == _TRUE)
            {
                ScalerTimerReactiveTimerEvent(_POWER_OFF_HDCP_HANDSHAKE_TIMEOUT, _SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

                SET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();

                return _TRUE;
            }
        }
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Whther go to Power Normal Mode
// Input Value  : None
// Output Value : _TRUE => Power Normal
//--------------------------------------------------
bit SysPowerCheckNormal(void)
{
    return (!GET_POWER_SWITCH_TO_FAKE_OFF());
}

