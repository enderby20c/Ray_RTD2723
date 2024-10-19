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
// ID Code      : UserCommonPower.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_POWER__

#include "UserCommonInclude.h"
#include "Power/UserCommonPower.h"

#if(_PANEL_STYLE == _PANEL_DPTX)
#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _OFF)
#warning "NOTE: _PANEL_DPTX_FORCE_OUTPUT_SUPPORT Should Be _ON when MP !!!"
#endif

#if(_PANEL_DPTX_FORCE_SSCG_SUPPORT == _ON)
#warning "NOTE: Please Confirm Panel Vendor Support SSCG When _PANEL_DPTX_FORCE_SSCG_SUPPORT Set On"
#endif
#endif

#if(_PANEL_EXIST_MULTIPANEL == _OFF)

#if(_PANEL_STYLE == _PANEL_LVDS)
#if(((_PANEL_LVDS_OUTPUT_PORT == _LVDS_4_PORT) && ((_PANEL_PIXEL_CLOCK_MAX_KHZ / 4) > 100000)) ||\
    ((_PANEL_LVDS_OUTPUT_PORT == _LVDS_2_PORT) && ((_PANEL_PIXEL_CLOCK_MAX_KHZ / 2) > 100000)) ||\
    ((_PANEL_LVDS_OUTPUT_PORT == _LVDS_1_PORT) && ((_PANEL_PIXEL_CLOCK_MAX_KHZ) > 100000)))
#warning "NOTE: Please Use BW Web Tool Calculate 1 Port LVDS Max Clk"
#endif

#if(_LVDS_SETTING_CONTROL_BY_USER == _ON)
#if(_HW_LVDS_DRIVE_TRIMMING_SUPPORT == _ON)
#warning "NOTE: If Use LVDS User Mode, Driving Current didnt trimming, There will be 13 percent variation"
#endif
#endif

#elif(_PANEL_STYLE == _PANEL_VBO)
#if((_PANEL_PIXEL_TYPE == _PANEL_PIXEL_OLED) && (_PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE == _PANEL_OLED_AC_DET_CTRL_WITH_SEQ))
#warning "NOTE: When _PANEL_OLED_AC_DET_CTRL_WITH_SEQ, _PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING Will Be Invalid, Causing the Backlight Control Can't Prevent Garbage When ESD or VBO Unlock"
#endif
#endif

#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPanelPowerInfo g_stPowerPanelInfo;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User initial LUT/Latch/SRAM tabled ata
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonPowerOnInitial(void)
{
    // User Power On Initial
    UserInterfacePowerOnInitial();

#if((_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE) && (_BACKLIGHT_DIMMING_SUPPORT == _ON))
    ExternalDeviceInterfaceLedDriverInitial();
#endif

#if(_COLOR_IP_DCR == _ON)
    ScalerColorDCRSetSource();
#endif

    // Adjust DCC Histogram Settings
#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
    ScalerColorDCCHistoSetting();
#endif

    // Adjust I Dither Table
#if(_I_DITHER_FUNCTION == _ON)
    UserCommonColorIDitherAdjust();
#endif

    // Adjust D Dither Table
#if(_D_DITHER_FUNCTION == _ON)
    UserCommonColorDDitherAdjust();
#endif

#if(_SD_TABLE_SEL_FUNCTION == _OFF)
    // Sharpness_Scaling
    ScalerScalingSetScalingDownCoef();
#endif

#if(_SHARPNESS_FUNCTION == _OFF)
    ScalerScalingSetScalingUpCoef();
#endif

    // Adjust Highlight Window Type & On/Off
#if(_COLOR_IP_HL_WIN == _ON)
    ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_NO_POLLING);
#endif

#if(_COLOR_IP_DCC == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorDCCSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#endif

#if(_COLOR_IP_ICM == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorICMSCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
    ScalerColorPCMInitial();
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorPostGammaSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorGammaSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#endif

#if(_COLOR_IP_SRGB == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorSRGBSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#if(_HW_SRGB_DB_GEN_SEL == _SRGB_GEN_1)
    ScalerColorSRGBInitial();
#endif
#endif

#if(_COLOR_IP_IAPS == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorIAPSGainSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#endif

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))

#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _ON)
    if(ScalerMcuCheckHwBW32Avaiable() == _FALSE)
    {
        DebugMessageCpu32("warning!!! _LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT Should be _OFF!!!", 0);
    }
#endif
    ScalerSpiDimmingInit();

#endif
#if(_HW_LOCAL_DIMMING_EXTROINFO_SUPPORT == _ON)
    ScalerColorLDExtroInfoInitial();
#endif
    ScalerColorLDHistoInitial(_LOCAL_DIMMING_HISTO_COVERRATE);
    // ScalerColorLDAdjustInitial();
    ScalerColorLDPWMProcInitial();
    ScalerColorLDBLModelInitial();
#endif

#if((_COLOR_IP_RGB_3D_GAMMA == _ON) && (_HW_3D_GAMMA_TABLE_TYPE == _3D_GAMMA_GEN_2))
    ScalerColorRGB3DGammaInitial();
#endif

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
    ScalerColorUltraVividInitial();
#endif

    // Initialize Osd Position
    ScalerGlobalOsdInitial();
}

//--------------------------------------------------
// Description  : User related operation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonPowerAcOnInitial(void)
{
    // Call Uncalled Function for Compile Warning
    UserCommonOsdUncallFunction();

    // Flash write protect
#if(_FLASH_WR_PROTECT == _ON)
    UserCommonFlashWRProtect();
#endif

    UserInterfacePowerAcOnInitial();
}

//--------------------------------------------------
// Description  : User Check Into Power Saving
// Input Value  : None
// Output Value : _USER_INTO_POWER_SAVING_READY --> User Check Ready to Power Saving
//                _USER_INTO_POWER_SAVING_NOT_READY --> User Check Not Ready to Power Saving
//--------------------------------------------------
EnumPSPermissionStatus UserCommonPowerGetIntoPSStatus(void)
{
    return UserInterfacePowerGetIntoPSStatus();
}

//--------------------------------------------------
// Description  : Check Fake Saving Status
// Input Value  : None
// Output Value : _TRUE ==> POWER STATUS FAKE SAVING, _FALSE ==> POWER STATUS SAVING
//--------------------------------------------------
bit UserCommonPowerCheckFakeSaving(void)
{
    if(SysPowerCheckFakeSaving() == _TRUE)
    {
        if((UserInterfaceDisplayGetNoSupportStatus() != _NO_SUPPORT_TRUE) && (SysRegionCheckDisplayActiveState() != _TRUE))
        {
            if(SysSourceCheckAnySourceJudged() == _TRUE)
            {
                SysSourceInfoReset();
            }
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Fake Off Status
// Input Value  : None
// Output Value : _TRUE ==> POWER STATUS is Fake OFF
//--------------------------------------------------
bit UserCommonPowerCheckFakeOff(void)
{
    if(SysPowerCheckFakeOff() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Panel Power On/Off Sequence
// Input Value  : ucEvent --> _PANEL_ON
//                            _PANEL_OFF
//                            _BACKLIGHT_ON
//                            _BACKLIGHT_OFF
// Output Value : None
//--------------------------------------------------
void UserCommonPowerPanelAction(EnumPanelPowerSeq enumEvent)
{
#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)

    UserInterfacePowerPanelAction(enumEvent);

#else

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
    SET_PANELPOWERACTION(enumEvent);
#endif

    switch(enumEvent)
    {
        case _PANEL_ON:

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
            if(GET_PANELPOWERSTATUS() == _WAITING_FOR_PANEL_OFF)
            {
                return;
            }
#endif

            if(GET_PANELPOWERSTATUS() == _PANEL_POWER_OFF_STATE)
            {
#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _OFF)
                // Check T6
                ScalerTimerWaitForActiveTimerEvent(_SYSTEM_TIMER_EVENT_PANEL_POWER_OFF);
#endif

                // LCD Power on
                PCB_PANEL_POWER(_PANEL_CONTROL_ON);

                UserInterfacePowerPanelWaitT1();

#if(_PANEL_STYLE == _PANEL_VBO)

                // Set Vby1 PHY
                ScalerDisplayVboTxPhyControl(_ENABLE);

                // Set HTPDN control by H/W
                ScalerDisplayVboTxHtpdnControl(_VBO_HW_CONTROL, _DISABLE);

                UserInterfacePowerPanelWaitT2();

                ScalerDisplayVboTxHtpdnHandler();

#elif(_PANEL_STYLE == _PANEL_DPTX)

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_PANEL_ON);

                // Set Dptx Analog PHY Power
                ScalerDisplayDpTxAnalogPhyConrol(_ON);

                UserInterfacePowerPanelWaitT2();

                if(ScalerDisplayDpTxLinkSequence() == _FAIL)
                {
#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
                    ScalerDisplayDpTxLinkSignalForceOutput();
#endif
                }
#endif
            }

            if(GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY)
            {
#if(_PANEL_STYLE == _PANEL_LVDS)

                // LVDS Power On
                ScalerDisplayLvdsPower(_ON);

                UserInterfacePowerPanelWaitT2();

                // LVDS PLL(Data) On
                ScalerDisplayLvdsPLL(_ON);

                // Wait Event for Backlight On
                ScalerTimerActiveTimerEvent(_PANEL_POWER_ON_T3, _SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_WAITING_FOR_BACKLIGHT);

#elif(_PANEL_STYLE == _PANEL_VBO)

#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
                if(GET_PANELPOWERSTATUS() != _PANEL_POWER_OFF_STATE)
                {
                    ScalerDisplayVboTxForceLinkTraining(_DISABLE);
                }
#endif

                // Set Panel Fast Off Enable
                ScalerDisplayVboTxPanelSetFastOff(_ENABLE);

                // Wait Event for Backlight On
                ScalerTimerActiveTimerEvent(_PANEL_POWER_ON_T3, _SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_WAITING_FOR_BACKLIGHT);

#elif(_PANEL_STYLE == _PANEL_DPTX)

                ScalerDisplayDpTxStreamHanlder(_ENABLE);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_PANEL_ON);

                // Wait Event for Backlight On
                ScalerTimerActiveTimerEvent(_PANEL_POWER_ON_T3, _SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_WAITING_FOR_BACKLIGHT);

#endif  // #if(_PANEL_STYLE == _PANEL_LVDS)
            }

            break;

        case _PANEL_OFF:

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
            if((GET_PANELPOWERSTATUS() != _PANEL_POWER_OFF_STATE) &&
               (GET_PANELPOWERSTATUS() != _WAITING_FOR_PANEL_OFF))
#else
            if(GET_PANELPOWERSTATUS() != _PANEL_POWER_OFF_STATE)
#endif
            {
#if(_PANEL_STYLE == _PANEL_LVDS)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

                UserInterfacePowerPanelWaitT4();

                ScalerDisplayLvdsPLL(_OFF);

                ScalerDisplayLvdsPower(_OFF);

                UserInterfacePowerPanelWaitT5();

#elif(_PANEL_STYLE == _PANEL_VBO)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

                // HTDPN fail before CDR lock, or CDR fail during ALN training, then set panel fast off
                if(ScalerDisplayVboTxPanelFastOffCheck() != _ENABLE)
                {
                    UserInterfacePowerPanelWaitT4();
                }

                // Force disable video output
                ScalerDisplayVboTxForceVideoOutput(_DISABLE);

                // Vby1 Phy Disable
                ScalerDisplayVboTxPhyControl(_DISABLE);

                // Set HTPDN control by F/W, pull high
                ScalerDisplayVboTxHtpdnControl(_VBO_FW_CONTROL, _HIGH);

                UserInterfacePowerPanelWaitT5();

#elif(_PANEL_STYLE == _PANEL_DPTX)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_BACKLIGHT_OFF);

                UserInterfacePowerPanelWaitT4();

                // Set IDLE Pattern
                ScalerDisplayDpTxStreamHanlder(_DISABLE);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
                if(UserCommonDataExchangeCheckSendEventDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_PANEL_OFF, 50) == _TRUE)
                {
                    DebugMessageSystem("Front chip get back chip PANEL_OFF Done", 1);
                }
                else
                {
                    DebugMessageSystem("Front chip get back chip PANEL_OFF Fail", 1);
                }
#endif

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_IDLE_PATTERN);

                // Disable DPTx Spread Spectrum
                ScalerDisplayDpTxSSCSet(_DISABLE);

                ScalerDisplayDpTxAnalogPhyConrol(_DISABLE);

                UserInterfacePowerPanelWaitT5();

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

                PCB_PANEL_POWER(_PANEL_CONTROL_OFF);

                ScalerTimerActiveTimerEvent(_PANEL_POWER_OFF_T6, _SYSTEM_TIMER_EVENT_PANEL_POWER_OFF);

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
                SET_PANELPOWERSTATUS(_WAITING_FOR_PANEL_OFF);
#else
                SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);
#endif

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON);
            }

            break;

        case _BACKLIGHT_ON:

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
            if(GET_PANELPOWERSTATUS() == _WAITING_FOR_PANEL_OFF)
            {
                return;
            }
#endif

            if(GET_PANELPOWERSTATUS() == _BACKLIGHT_ON_ALREADY)
            {
                return;
            }

            if(GET_PANELPOWERSTATUS() == _PANEL_POWER_OFF_STATE)
            {
#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _OFF)
                // Check T6
                ScalerTimerWaitForActiveTimerEvent(_SYSTEM_TIMER_EVENT_PANEL_POWER_OFF);
#endif

                // LCD Power on
                PCB_PANEL_POWER(_PANEL_CONTROL_ON);

                UserInterfacePowerPanelWaitT1();

#if(_PANEL_STYLE == _PANEL_LVDS)

                // LVDS Power On
                ScalerDisplayLvdsPower(_ON);

                UserInterfacePowerPanelWaitT2();

                // LVDS PLL(Data) On
                ScalerDisplayLvdsPLL(_ON);

                // Wait Delay for Backlight On
                UserInterfacePowerPanelWaitT3();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#elif(_PANEL_STYLE == _PANEL_VBO)

                // Set Vby1 PHY
                ScalerDisplayVboTxPhyControl(_ENABLE);

                // Set HTPDN control by H/W
                ScalerDisplayVboTxHtpdnControl(_VBO_HW_CONTROL, _DISABLE);

                UserInterfacePowerPanelWaitT2();

                ScalerDisplayVboTxHtpdnHandler();

                UserInterfacePowerPanelWaitT3();

                ScalerDisplayVboTxLocknHandler();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

                // Set Panel Fast Off Disable
                ScalerDisplayVboTxPanelSetFastOff(_DISABLE);

#elif(_PANEL_STYLE == _PANEL_DPTX)

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_PANEL_ON);

                // Set Dptx Analog PHY Power
                ScalerDisplayDpTxAnalogPhyConrol(_ON);

                UserInterfacePowerPanelWaitT2();

                if(ScalerDisplayDpTxLinkSequence() == _FAIL)
                {
#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
                    ScalerDisplayDpTxLinkSignalForceOutput();
#endif
                }

                // Set Video Stream parameter
                ScalerDisplayDpTxStreamHanlder(_ENABLE);

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_VIDEO_PATTERN);

                // Wait Delay for Backlight On
                UserInterfacePowerPanelWaitT3();

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
                if(UserCommonDataExchangeCheckSendEventDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_BACKLIGHT_ON, 50) == _TRUE)
                {
                    DebugMessageSystem("Front chip get back chip Backlight on Done", 1);
                    PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);
                }
                else
                {
                    DebugMessageSystem("Front chip get back chip Backlight on Fail", 1);
                }
#else
                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);
#endif

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)
            }
            else if(GET_PANELPOWERSTATUS() == _PANEL_BACKLIGHT_OFF)
            {
#if(_PANEL_STYLE == _PANEL_LVDS)

                // LVDS PLL(Data) On
                ScalerDisplayLvdsPLL(_ON);

#elif(_PANEL_STYLE == _PANEL_VBO)

#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
                ScalerDisplayVboTxForceLinkTraining(_DISABLE);

                ScalerDisplayVboTxLocknHandler();

                // Set Panel Fast Off Disable
                ScalerDisplayVboTxPanelSetFastOff(_DISABLE);
#endif

#elif(_PANEL_STYLE == _PANEL_DPTX)

#if(_PANEL_DPTX_HPD_DETECT == _ON)
                if(GET_DISPLAY_DP_TX_FORCE_TO_LT() == _TRUE)
                {
                    if(ScalerDisplayDpTxLinkSequence() == _FAIL)
                    {
#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
                        ScalerDisplayDpTxLinkSignalForceOutput();
#endif
                    }
                }
#endif
                ScalerDisplayDpTxStreamHanlder(_ENABLE);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

                // Wait Delay for Backlight On
                UserInterfacePowerPanelWaitT3();

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
                if(UserCommonDataExchangeCheckSendEventDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_BACKLIGHT_ON, 50) == _TRUE)
                {
                    DebugMessageSystem("Front chip get back chip Backlight on Done", 2);
                    PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);
                }
                else
                {
                    DebugMessageSystem("Front chip get back chip Backlight on Fail", 2);
                }
#else
                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);
#endif

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);
            }
            else
            {
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON);
#else
                ScalerTimerWaitForActiveTimerEvent(_SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON);
#endif

#if(_PANEL_STYLE == _PANEL_LVDS)

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#elif(_PANEL_STYLE == _PANEL_VBO)

                ScalerDisplayVboTxLocknHandler();

                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

                // Set Panel Fast Off Disable
                ScalerDisplayVboTxPanelSetFastOff(_DISABLE);

#elif(_PANEL_STYLE == _PANEL_DPTX)

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
                if(UserCommonDataExchangeCheckSendEventDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_BACKLIGHT_ON, 50) == _TRUE)
                {
                    DebugMessageSystem("Front chip get back chip Backlight on Done", 3);
                    PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);
                }
                else
                {
                    DebugMessageSystem("Front chip get back chip Backlight on Fail", 3);
                }
#else
                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_ON);
#endif
                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxPowerSequenceProc(_DPTX_POWER_SEQUENCE_BACKLIGHT_ON);

                SET_PANELPOWERSTATUS(_BACKLIGHT_ON_ALREADY);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)
            }

            break;

        case _BACKLIGHT_OFF:

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
            if((GET_PANELPOWERSTATUS() != _PANEL_POWER_OFF_STATE) &&
               (GET_PANELPOWERSTATUS() != _PANEL_BACKLIGHT_OFF) &&
               (GET_PANELPOWERSTATUS() != _WAITING_FOR_PANEL_OFF))
#else
            if((GET_PANELPOWERSTATUS() != _PANEL_POWER_OFF_STATE) &&
               (GET_PANELPOWERSTATUS() != _PANEL_BACKLIGHT_OFF))
#endif
            {
                PCB_BACKLIGHT_POWER(_LIGHT_CONTROL_OFF);

#if(_PANEL_STYLE == _PANEL_LVDS)

                UserInterfacePowerPanelWaitT4();

                ScalerDisplayLvdsPLL(_OFF);

#elif(_PANEL_STYLE == _PANEL_VBO)

#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
                UserInterfacePowerPanelWaitT4();

                ScalerDisplayVboTxForceLinkTraining(_ENABLE);
#endif

#elif(_PANEL_STYLE == _PANEL_DPTX)

                UserInterfacePowerPanelWaitT4();

                ScalerDisplayDpTxStreamHanlder(_DISABLE);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
                if(UserCommonDataExchangeCheckSendEventDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_BACKLIGHT_OFF, 50) == _TRUE)
                {
                    DebugMessageSystem("Front chip get back chip Backlight off Done", 1);
                }
                else
                {
                    DebugMessageSystem("Front chip get back chip Backlight off Fail", 1);
                }
#endif
#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

                SET_PANELPOWERSTATUS(_PANEL_BACKLIGHT_OFF);
            }

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON);

            break;

        default:

            break;
    }
#endif
}
//--------------------------------------------------
// Description  : Power fake off color process
// Input Value  : EnumPowerAction
// Output Value : None
//--------------------------------------------------
void UserCommonPowerColorFakePowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_PS:
#if(_LOCAL_DIMMING_FUNCTION == _ON)
            UserCommonColorLocalDimmingEnable(_FUNCTION_OFF);
#endif
#if(_GOSD_SUPPORT == _ON)
            UserCommonOsdDisableGosd();
#endif
            break;
        default:
            break;
    }
}
