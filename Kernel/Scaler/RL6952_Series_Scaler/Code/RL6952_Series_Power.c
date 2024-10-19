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
// ID Code      : RL6952_Series_Power.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Power/ScalerPower.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Power Group
//--------------------------------------------------
StructPowerCutGroup code tGroupPcbVcckOnDpMac[] =
{
    {_POWER_CUT_GROUP_RX0_DP14_MAC,             _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_MAC_RX0_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX0_DP20_MAC,             _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX1_DP14_MAC,             _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_MAC_RX1_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX1_DP20_MAC,             _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX2_DP14_MAC,             _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_MAC_RX2_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX2_DP20_MAC,             _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_DPTX_DP20_MAC,            _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_MST_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_DPTX_DP14_MAC,            _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_MST_SUPPORT == _ON)},
};

StructPowerCutGroup code tGroupPcbVcckOn[] =
{
    {_POWER_CUT_GROUP_HDCP_ECDSA,               _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON,  (EnumPowerDomainSupport)(_DP_HDCP_2_2_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX3_HDMI20_MAC,           _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_TMDS_MAC_RX3_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX3_HDMI21_MAC,           _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX4_HDMI20_MAC,           _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_TMDS_MAC_RX4_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX4_HDMI21_MAC,           _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_DSC_0,                    _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DSC_MAC_DECODER_0_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_DSC_1,                    _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DSC_MAC_DECODER_1_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_FORMAT_CONVERSION,        _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  _POWER_DOMAIN_PROJECT_SUPPORT_ENABLE},
    {_POWER_CUT_GROUP_TYPE_C_0_PD_MAC,          _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)},
    {_POWER_CUT_GROUP_TYPE_C_1_PD_MAC,          _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)},
    {_POWER_CUT_GROUP_10_BIT_SARADC,            _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON))},
    {_POWER_CUT_GROUP_THERMAL_SENSOR,           _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  _POWER_DOMAIN_PROJECT_SUPPORT_ENABLE},
};

StructPowerCutGroup code tGroupPcbVcckOff[] =
{
    {_POWER_CUT_GROUP_ANTI_ALIASING_M1M2,       _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_ANTI_ALIASING_FUNCTION == _ON)},
    {_POWER_CUT_GROUP_IMC_ENC_M1,               _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_IMC_ENC_M2,               _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_IMC_ENC_S1,               _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_IMC_DEC_M1,               _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_IMC_DEC_M2,               _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_IMC_DEC_S1,               _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)},
};

StructPowerCutGroup code tGroupPcbVcckOnPHY[] =
{
    {_POWER_CUT_GROUP_RX0_DP20_U32_APHY,        _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)((_DP_PHY_RX0_SUPPORT == _ON) || (_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON))},
    {_POWER_CUT_GROUP_RX0_DP_DPHY,              _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)((_DP_PHY_RX0_SUPPORT == _ON) || (_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON))},
    {_POWER_CUT_GROUP_RX0_DP_AUX,               (_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON) ? _POWER_DOMAIN_PSPD_MODE_USER_CONTROL : _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON,  (EnumPowerDomainSupport)(_DP_AUX_RX0_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX0_DP14_DPHY,            _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_DP_MAC_DPHY_RX0_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX0_DP20_DPHY,            _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_DP_MAC_DPHY_RX0_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX1_DP20_U32_APHY,        _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)((_DP_PHY_RX1_SUPPORT == _ON) || (_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON))},
    {_POWER_CUT_GROUP_RX1_DP_DPHY,              _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)((_DP_PHY_RX1_SUPPORT == _ON) || (_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON))},
    {_POWER_CUT_GROUP_RX1_DP_AUX,               (_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON) ? _POWER_DOMAIN_PSPD_MODE_USER_CONTROL : _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON,  (EnumPowerDomainSupport)(_DP_AUX_RX1_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX1_DP14_DPHY,            _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_DP_MAC_DPHY_RX1_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX1_DP20_DPHY,            _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_DP_MAC_DPHY_RX1_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX2_DP20_APHY,            _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_DP_PHY_RX2_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX2_DP_DPHY,              _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_DP_PHY_RX2_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX2_DP_AUX,               (_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON) ? _POWER_DOMAIN_PSPD_MODE_USER_CONTROL : _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON,  (EnumPowerDomainSupport)(_DP_AUX_RX2_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX2_DP14_DPHY,            _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_DP_MAC_DPHY_RX2_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX2_DP20_DPHY,            _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_DP_MAC_DPHY_RX2_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX3_HDMI21_APHY,          _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_HDMI_PHY_RX3_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX3_HDMI_DPHY,            _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_HDMI_PHY_RX3_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX4_HDMI21_APHY,          _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_HDMI_PHY_RX4_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_RX4_HDMI_DPHY,            _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_HDMI_PHY_RX4_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_PX0_DP20_APHY,            _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_PHY_TX_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_PX0_AUX,                  _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)(_DP_TX_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_TYPE_C_0_CC_MAC,          _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_TYPE_C_GPIO_MODE_SUPPORT == _ON))},
    {_POWER_CUT_GROUP_TYPE_C_1_CC_MAC,          _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)((_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_TYPE_C_GPIO_MODE_SUPPORT == _ON))},
    {_POWER_CUT_GROUP_USB_UFP,                  _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON,  (EnumPowerDomainSupport)((_USB2_HOST_SUPPORT == _ON) || (_BILLBOARD_SCALER_SUPPORT == _ON))},
    {_POWER_CUT_GROUP_JFM,                      _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_USB3_RETIMER_PHY_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_USB32_DFP_APHY,           _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_USB3_RETIMER_DFP_PHY_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_USB_DFP_DPHY,             _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_USB3_RETIMER_DFP_PHY_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_USB_UFP_RETIMER_MAC,      _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_USB3_RETIMER_DFP_PHY_SUPPORT == _ON)},
    {_POWER_CUT_GROUP_USB_DFP_RETIMER_MAC,      _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,    (EnumPowerDomainSupport)(_USB3_RETIMER_DFP_PHY_SUPPORT == _ON)},
};

StructPowerCutGroup code tGroupVcckOffTop[] =
{
    {_POWER_CUT_GROUP_TOPOFF,                   _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  _POWER_DOMAIN_PROJECT_SUPPORT_ENABLE},
};

StructPowerCutGroup code tGroupSubPowerDomain[] =
{
    {_POWER_CUT_GROUP_TYPE_C_0_BMC,             _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)},
    {_POWER_CUT_GROUP_TYPE_C_1_BMC,             _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)},
    {_POWER_CUT_GROUP_VBO_EDP_8_LANE,           _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL,  (EnumPowerDomainSupport)((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))},
};


//--------------------------------------------------
// Power ON/OFF Flow
//--------------------------------------------------
StructPowerFlow code tGroupPowerCutOn[] =
{
    {tGroupPcbVcckOnDpMac,      (sizeof(tGroupPcbVcckOnDpMac) / sizeof(tGroupPcbVcckOnDpMac[0]))},
    {tGroupPcbVcckOn,           (sizeof(tGroupPcbVcckOn) / sizeof(tGroupPcbVcckOn[0]))},
    {tGroupPcbVcckOff,          (sizeof(tGroupPcbVcckOff) / sizeof(tGroupPcbVcckOff[0]))},
    {tGroupPcbVcckOnPHY,        (sizeof(tGroupPcbVcckOnPHY) / sizeof(tGroupPcbVcckOnPHY[0]))},
    {tGroupVcckOffTop,          (sizeof(tGroupVcckOffTop) / sizeof(tGroupVcckOffTop[0]))},
};

StructPowerFlow code tGroupPowerCutOff[] =
{
    {tGroupVcckOffTop,          (sizeof(tGroupVcckOffTop) / sizeof(tGroupVcckOffTop[0]))},
    {tGroupPcbVcckOnPHY,        (sizeof(tGroupPcbVcckOnPHY) / sizeof(tGroupPcbVcckOnPHY[0]))},
    {tGroupPcbVcckOnDpMac,      (sizeof(tGroupPcbVcckOnDpMac) / sizeof(tGroupPcbVcckOnDpMac[0]))},
    {tGroupPcbVcckOn,           (sizeof(tGroupPcbVcckOn) / sizeof(tGroupPcbVcckOn[0]))},
    {tGroupPcbVcckOff,          (sizeof(tGroupPcbVcckOff) / sizeof(tGroupPcbVcckOff[0]))},
};

StructPowerFlow code tGroupPowerSubDomain[] =
{
    {tGroupSubPowerDomain,      (sizeof(tGroupSubPowerDomain) / sizeof(tGroupSubPowerDomain[0]))},
};


//--------------------------------------------------
// Clock Gating Group
//--------------------------------------------------
StructPowerClockGatingGroup code tGroupClockGating[] =
{
    {_CLOCK_GATING_GROUP_IR,                    _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)(_IR_SUPPORT != _IR_OFF)},
    {_CLOCK_GATING_GROUP_SPI_0_MASTER,          _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)(_SPI0_SUPPORT == _ON)},
    {_CLOCK_GATING_GROUP_SPI_1_MASTER,          _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)(_SPI1_SUPPORT == _ON)},
    {_CLOCK_GATING_GROUP_SPI_2_MASTER,          _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,   (EnumPowerDomainSupport)(_SPI2_SUPPORT == _ON)},
};


//--------------------------------------------------
// Clock Gating Flow
//--------------------------------------------------
StructClockGatingFlow code tGroupPowerClockGating[] =
{
    {tGroupClockGating,      (sizeof(tGroupClockGating) / sizeof(tGroupClockGating[0]))},
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Power Domain Enable
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerPowerDomainEnableStatus(void)
{
    return ((_DEBUG_POWER_DOMAIN_ENABLE == _ON) || (_FACTORY_RTD_QC_SUPPORT == _ON));
}

//--------------------------------------------------
// Description  : Get power domain support status by function
// Input Value  : enumPowerGroup -> target power group
// Output Value : support status
//--------------------------------------------------
EnumPowerDomainSupport ScalerPowerGetPowerDomainSupport(EnumPowerGroup enumPowerGroup)
{
    enumPowerGroup = enumPowerGroup;
    return _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE;
}

//--------------------------------------------------
// Description  : Get power domain PS/PD Mode by function
// Input Value  : enumPowerGroup -> target power group
// Output Value : support status
//--------------------------------------------------
EnumPowerPsPdMode ScalerPowerGetPowerDomainPsPdMode(EnumPowerGroup enumPowerGroup)
{
    switch(enumPowerGroup)
    {
        case _POWER_CUT_GROUP_RX0_DP20_U32_APHY:
        case _POWER_CUT_GROUP_RX0_DP_DPHY:

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
            if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() != _USB3_RETIMER_NO_ACTION) && (GET_USB_HUB_SWITCH_PORT_RESULT() == _HUB_D0_TYPE_C_PORT))
            {
                return _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON;
            }
#endif
            break;

        case _POWER_CUT_GROUP_RX1_DP20_U32_APHY:
        case _POWER_CUT_GROUP_RX1_DP_DPHY:

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
            if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() != _USB3_RETIMER_NO_ACTION) && (GET_USB_HUB_SWITCH_PORT_RESULT() == _HUB_D1_TYPE_C_PORT))
            {
                return _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON;
            }
#endif
            break;

        case _POWER_CUT_GROUP_JFM:
        case _POWER_CUT_GROUP_USB32_DFP_APHY:
        case _POWER_CUT_GROUP_USB_DFP_DPHY:
        case _POWER_CUT_GROUP_USB_UFP_RETIMER_MAC:
        case _POWER_CUT_GROUP_USB_DFP_RETIMER_MAC:

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
            if(ScalerUsb3RepeaterMacGetLowPowerStateStatus() != _USB3_RETIMER_NO_ACTION)
            {
                return _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON;
            }
#endif
            break;

        case _POWER_CUT_GROUP_10_BIT_SARADC:

#if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)
            return _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON;
#else
            return _POWER_DOMAIN_PSPD_MODE_USER_CONTROL;
#endif

            break;

        default:
            break;
    }

    return _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL;
}

//--------------------------------------------------
// Description  : Power cut block flow
// Input Value  : enumPowerAction    --> Power action description.
// Output Value : return power group enter isolation area
//--------------------------------------------------
void ScalerPowerIsolation(EnumPowerAction enumPowerAction)
{
    BYTE ucIndex = 0x00;
    BYTE ucPowerGroup = 0x00;
    EnumPowerReset enumPowerReset = _POWER_RESET_DISABLE;

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_INITIAL:

            // Align all power domain state
            ScalerPowerGroupDefaultStateAlign();

            // Power off un-used power group
            ScalerPowerGroupPowerACOnSetting();

            // Set all flags
            SET_POWER_ISO_TOP_FLG();
            SET_POWER_ISO_GDITX_FLG();
            SET_POWER_LOAD_DPTX_HDCP_KEY_FLG();
            SET_POWER_ISO_DPMAC_FLG();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:

            // Start Power Cut
            for(ucPowerGroup = 0; ucPowerGroup < (sizeof(tGroupPowerCutOn) / sizeof(tGroupPowerCutOn[0])); ucPowerGroup++)
            {
                for(ucIndex = 0; ucIndex < tGroupPowerCutOn[ucPowerGroup].ucMaxSize; ucIndex++)
                {
                    EnumPowerGroup enumPowerGroup = tGroupPowerCutOn[ucPowerGroup].pstPowerCutGroup[ucIndex].enumPowerGroup;
                    EnumPowerPsPdMode enumPowerPsPdMode = tGroupPowerCutOn[ucPowerGroup].pstPowerCutGroup[ucIndex].b2PsPdModeOperation;
                    EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerCutOn[ucPowerGroup].pstPowerCutGroup[ucIndex].b2PowerDomainSupport;

                    // Power domain support_by_function judgment
                    if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
                    {
                        enumPowerDomainSupport = ScalerPowerGetPowerDomainSupport(enumPowerGroup);
                    }

                    // Power domain PSPD_mode_by_function judgment
                    if(enumPowerPsPdMode == _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION)
                    {
                        enumPowerPsPdMode = ScalerPowerGetPowerDomainPsPdMode(enumPowerGroup);
                    }

                    // Unused power domain judgment
                    if((ScalerPowerDomainEnableStatus() == _TRUE) ||
                       ((enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_ENABLE) &&
                        (enumPowerPsPdMode == _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL)))
                    {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                        if(ScalerPowerCutSwitchCheck(enumPowerGroup, _POWER_CUT_ON) == _FALSE)
                        {
                            continue;
                        }
#endif
                        ScalerPowerGroupPowerCut(enumPowerGroup, _POWER_CUT_ON, _POWER_RESET_DISABLE);
                    }
                }

                // Set Isolation Recovery Flag
                if(ucPowerGroup == _POWER_CUT_ON_GROUP_DPMAC)
                {
                    SET_POWER_ISO_DPMAC_FLG();
                }
                else if(ucPowerGroup == _POWER_CUT_ON_GROUP_PHY)
                {
                    SET_POWER_ISO_GDITX_FLG();
                    SET_POWER_LOAD_DPTX_HDCP_KEY_FLG();
                }
                else if(ucPowerGroup == _POWER_CUT_ON_GROUP_TOPOFF)
                {
                    SET_POWER_ISO_TOP_FLG();
                }
            }

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            // Reset Judgment
            if(enumPowerAction == _POWER_ACTION_AC_ON_TO_NORMAL)
            {
                enumPowerReset = _POWER_RESET_DISABLE;
            }
            else
            {
                enumPowerReset = _POWER_RESET_ENABLE;
            }

            // Start Power Up
            for(ucPowerGroup = 0; ucPowerGroup < (sizeof(tGroupPowerCutOff) / sizeof(tGroupPowerCutOff[0])); ucPowerGroup++)
            {
                for(ucIndex = 0; ucIndex < tGroupPowerCutOff[ucPowerGroup].ucMaxSize; ucIndex++)
                {
                    EnumPowerGroup enumPowerGroup = tGroupPowerCutOff[ucPowerGroup].pstPowerCutGroup[ucIndex].enumPowerGroup;
                    EnumPowerCut enumGroupPowerCut = _POWER_CUT_OFF;
                    EnumPowerReset enumGroupPowerReset = _POWER_RESET_ENABLE;

                    // Power domain ON/OFF judgment
                    if(ScalerPowerDomainEnableStatus() == _TRUE)
                    {
                        enumGroupPowerCut = _POWER_CUT_OFF;
                        enumGroupPowerReset = enumPowerReset;
                    }
                    else
                    {
                        EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerCutOff[ucPowerGroup].pstPowerCutGroup[ucIndex].b2PowerDomainSupport;

                        // Power domain support_by_function judgment
                        if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
                        {
                            enumPowerDomainSupport = ScalerPowerGetPowerDomainSupport(enumPowerGroup);
                        }

                        // Unused power domain judgment
                        if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_ENABLE)
                        {
                            EnumPowerPsPdMode enumPowerPsPdMode = tGroupPowerCutOff[ucPowerGroup].pstPowerCutGroup[ucIndex].b2PsPdModeOperation;

                            enumGroupPowerCut = _POWER_CUT_OFF;
                            enumGroupPowerReset = enumPowerReset;

                            // Power domain PSPD_mode_by_function judgment
                            if(enumPowerPsPdMode == _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION)
                            {
                                enumPowerPsPdMode = ScalerPowerGetPowerDomainPsPdMode(enumPowerGroup);
                            }

                            // Special Power Operation Mode Judgment
                            switch(enumPowerPsPdMode)
                            {
                                case _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON:

                                    enumGroupPowerReset = _POWER_RESET_DISABLE;

                                    break;

                                case _POWER_DOMAIN_PSPD_MODE_USER_CONTROL:

                                    if(enumPowerAction != _POWER_ACTION_AC_ON_TO_NORMAL)
                                    {
                                        // No operation
                                        continue;
                                    }

                                    break;

                                case _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL:
                                default:
                                    break;
                            }
                        }
                        else
                        {
                            enumGroupPowerCut = _POWER_CUT_ON;
                            enumGroupPowerReset = _POWER_RESET_DISABLE;
                        }
                    }

                    // Power Domain Final Control
                    ScalerPowerGroupPowerCut(enumPowerGroup, enumGroupPowerCut, enumGroupPowerReset);
                }
            }

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_PS:

            break;

        case _POWER_ACTION_PS_TO_OFF:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Recover The Data of LUT/Latch/SRAM In Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverIsolationAreaData(void)
{
    if(GET_POWER_ISO_TOP_FLG() == _TRUE)
    {
        CLR_POWER_ISO_TOP_FLG();

        // Power TOP Group Data Recovery
        ScalerPowerGroupRecoverData(_POWER_DATA_RECOVER_TOP);
    }

    if(GET_POWER_ISO_GDITX_FLG() == _TRUE)
    {
        CLR_POWER_ISO_GDITX_FLG();

        // Power GDI Tx Group Data Recovery
        ScalerPowerGroupRecoverData(_POWER_DATA_RECOVER_GDITX);
    }

    if(GET_POWER_ISO_DPMAC_FLG() == _TRUE)
    {
        CLR_POWER_ISO_DPMAC_FLG();

        // Power DP MAC Group Data Recovery
        ScalerPowerGroupRecoverData(_POWER_DATA_RECOVER_DPMAC);
    }
}

//--------------------------------------------------
// Description  : Group Power on/off
// Input Value  : enumPowerGroup : _POWER_CUT_GROUP_DPMAC0 ~ _POWER_CUT_GROUP_TOPOFF
// Input Value  : ucOn: ON(Low Power) / OFF(Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupPowerCut(EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut, EnumPowerReset enumPowerReset)
{
    BYTE ucCounter = 0;

    switch(enumPowerGroup)
    {
        case _POWER_CUT_GROUP_RX0_DP20_U32_APHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_41_VCCKOFF_CONTROL41, ~_BIT0, 0x00);

                // Digital to analog isolation on
                ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT3, 0x00);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP14_MAC) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP20_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT7, _BIT7);
            }
            else
            {
                // Digital power on
                ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT7, 0x00);

                // Check D0 DPHY Power Enable or Not
                if(ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP_DPHY) == _POWER_CUT_ON)
                {
                    if(enumPowerReset == _POWER_RESET_ENABLE)
                    {
                        // Power Cut block Reset
                        ScalerSetBit(P6F_61_PD2_POWER_CTRL, ~_BIT0, _BIT0);
                    }

                    // Digital power on
                    ScalerSetBit(P6F_61_PD2_POWER_CTRL, ~_BIT5, 0x00);

                    // Wait for digital power on flag
                    ucCounter = 50;

                    while((ScalerGetBit(P6F_61_PD2_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                    {
                        DELAY_5US();
                    }
                }

                // Power on bandgap
                ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital to analog isolation on
                ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT3, _BIT3);

                // Analog isolation off
                ScalerSetBit(P40_41_VCCKOFF_CONTROL41, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_61_PD2_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_61_PD2_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                // Check D0 DPHY Power Enable or Not
                if(ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP_DPHY) == _POWER_CUT_ON)
                {
                    if(enumPowerReset == _POWER_RESET_ENABLE)
                    {
                        // Power Cut block Reset
                        ScalerSetBit(P6F_61_PD2_POWER_CTRL, ~_BIT0, _BIT0);
                    }

                    // Digital power on
                    ScalerSetBit(P6F_61_PD2_POWER_CTRL, ~_BIT5, 0x00);

                    // Wait for digital power on flag
                    ucCounter = 50;

                    while((ScalerGetBit(P6F_61_PD2_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                    {
                        DELAY_5US();
                    }
                }

                // Digital isolation off
                ScalerSetBit(P6F_61_PD2_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_61_PD2_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP_AUX:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_46_VCCKOFF_CONTROL46, ~_BIT0, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_62_PD3_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_62_PD3_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_62_PD3_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_62_PD3_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_62_PD3_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_62_PD3_POWER_CTRL, ~_BIT1, 0x00);

                // Analog isolation off
                ScalerSetBit(P40_46_VCCKOFF_CONTROL46, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_62_PD3_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP20_U32_APHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_42_VCCKOFF_CONTROL42, ~_BIT0, 0x00);

                // Digital to analog isolation on
                ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT3, 0x00);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP14_MAC) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP20_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT7, _BIT7);
            }
            else
            {
                // Digital power on
                ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT7, 0x00);

                // Check D1 DPHY Power Enable or Not
                if(ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP_DPHY) == _POWER_CUT_ON)
                {
                    if(enumPowerReset == _POWER_RESET_ENABLE)
                    {
                        // Power Cut block Reset
                        ScalerSetBit(P6F_66_PD7_POWER_CTRL, ~_BIT0, _BIT0);
                    }

                    // Digital power on
                    ScalerSetBit(P6F_66_PD7_POWER_CTRL, ~_BIT5, 0x00);

                    // Wait for digital power on flag
                    ucCounter = 50;

                    while((ScalerGetBit(P6F_66_PD7_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                    {
                        DELAY_5US();
                    }
                }

                // Power on bandgap
                ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital to analog isolation on
                ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT3, _BIT3);

                // Analog isolation off
                ScalerSetBit(P40_42_VCCKOFF_CONTROL42, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_66_PD7_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_66_PD7_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                // Check D1 DPHY Power Enable or Not
                if(ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP_DPHY) == _POWER_CUT_ON)
                {
                    if(enumPowerReset == _POWER_RESET_ENABLE)
                    {
                        // Power Cut block Reset
                        ScalerSetBit(P6F_66_PD7_POWER_CTRL, ~_BIT0, _BIT0);
                    }

                    // Digital power on
                    ScalerSetBit(P6F_66_PD7_POWER_CTRL, ~_BIT5, 0x00);

                    // Wait for digital power on flag
                    ucCounter = 50;

                    while((ScalerGetBit(P6F_66_PD7_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                    {
                        DELAY_5US();
                    }
                }

                // Digital isolation off
                ScalerSetBit(P6F_66_PD7_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_66_PD7_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP_AUX:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_47_VCCKOFF_CONTROL47, ~_BIT0, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_67_PD8_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_67_PD8_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_67_PD8_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_67_PD8_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_67_PD8_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_67_PD8_POWER_CTRL, ~_BIT1, 0x00);

                // Analog isolation off
                ScalerSetBit(P40_47_VCCKOFF_CONTROL47, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_67_PD8_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP20_APHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_43_VCCKOFF_CONTROL43, ~_BIT0, 0x00);

                // Digital to analog isolation on
                ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT3, 0x00);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP14_MAC) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP20_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT7, _BIT7);
            }
            else
            {
                // Digital power on
                ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT7, 0x00);

                // Power on bandgap
                ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital to analog isolation on
                ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT3, _BIT3);

                // Analog isolation off
                ScalerSetBit(P40_43_VCCKOFF_CONTROL43, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_6B_PD12_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_6B_PD12_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_6B_PD12_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_6B_PD12_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_6B_PD12_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_6B_PD12_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_6B_PD12_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP_AUX:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_48_VCCKOFF_CONTROL48, ~_BIT0, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_6C_PD13_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_6C_PD13_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_6C_PD13_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_6C_PD13_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_6C_PD13_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_6C_PD13_POWER_CTRL, ~_BIT1, 0x00);

                // Analog isolation off
                ScalerSetBit(P40_48_VCCKOFF_CONTROL48, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_6C_PD13_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX3_HDMI21_APHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_44_VCCKOFF_CONTROL44, ~_BIT0, 0x00);

                // Digital isolation on
                ScalerSetBit(P7C_16_GDI_CTRL1, ~_BIT0, 0x00);

                // Digital power off
                ScalerSetBit(P7C_16_GDI_CTRL1, ~_BIT1, _BIT1);
            }
            else
            {
                // Digital power on
                ScalerSetBit(P7C_16_GDI_CTRL1, ~_BIT1, 0x00);

                // Digital isolation off
                ScalerSetBit(P7C_16_GDI_CTRL1, ~_BIT0, _BIT0);

                // Analog isolation off
                ScalerSetBit(P40_44_VCCKOFF_CONTROL44, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_RX3_HDMI_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P67_04_PD17_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P67_04_PD17_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P67_04_PD17_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P67_04_PD17_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P67_04_PD17_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P67_04_PD17_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P67_04_PD17_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX3_HDMI20_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P67_03_PD18_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P67_03_PD18_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P67_03_PD18_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P67_03_PD18_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P67_03_PD18_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P67_03_PD18_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P67_03_PD18_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX3_HDMI21_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P67_02_PD19_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P67_02_PD19_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P67_02_PD19_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P67_02_PD19_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P67_02_PD19_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P67_02_PD19_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P67_02_PD19_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX4_HDMI21_APHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_45_VCCKOFF_CONTROL45, ~_BIT0, 0x00);

                // Digital isolation on
                ScalerSetBit(P7D_16_GDI_CTRL1, ~_BIT0, 0x00);

                // Digital power off
                ScalerSetBit(P7D_16_GDI_CTRL1, ~_BIT1, _BIT1);
            }
            else
            {
                // Digital power on
                ScalerSetBit(P7D_16_GDI_CTRL1, ~_BIT1, 0x00);

                // Digital isolation off
                ScalerSetBit(P7D_16_GDI_CTRL1, ~_BIT0, _BIT0);

                // Analog isolation off
                ScalerSetBit(P40_45_VCCKOFF_CONTROL45, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_RX4_HDMI_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P1E_04_PD21_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P1E_04_PD21_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P1E_04_PD21_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P1E_04_PD21_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P1E_04_PD21_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P1E_04_PD21_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P1E_04_PD21_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX4_HDMI20_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P1E_03_PD22_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P1E_03_PD22_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P1E_03_PD22_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P1E_03_PD22_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P1E_03_PD22_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P1E_03_PD22_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P1E_03_PD22_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX4_HDMI21_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P1E_02_PD23_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P1E_02_PD23_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P1E_02_PD23_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P1E_02_PD23_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P1E_02_PD23_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P1E_02_PD23_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P1E_02_PD23_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_DSC_0:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_21_PD24_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_21_PD24_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_21_PD24_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_21_PD24_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_21_PD24_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_21_PD24_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_21_PD24_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_FORMAT_CONVERSION:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_26_PD25_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_26_PD25_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_26_PD25_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_26_PD25_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_26_PD25_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_26_PD25_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_26_PD25_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_0_PD_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_20_PD29_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_20_PD29_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_20_PD29_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_20_PD29_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_20_PD29_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_20_PD29_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_20_PD29_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_USB_UFP:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_4D_VCCKOFF_CONTROL5A, ~_BIT0, 0x00);

                // internal DVDD isolation on
                ScalerSetBit(P6F_83_PD30_POWER_CTRL, ~_BIT2, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_83_PD30_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_83_PD30_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_83_PD30_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_83_PD30_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_83_PD30_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_83_PD30_POWER_CTRL, ~_BIT1, 0x00);

                // internal DVDD isolation off
                ScalerSetBit(P6F_83_PD30_POWER_CTRL, ~_BIT2, _BIT2);

                // Analog isolation off
                ScalerSetBit(P40_4D_VCCKOFF_CONTROL5A, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_83_PD30_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_JFM:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on of APHY
                ScalerSetBit(P40_4F_VCCKOFF_CONTROL4F, ~_BIT0, 0x00);

                // Digital isolation on of APHY
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~(_BIT3 | _BIT2), 0x00);

                // Digital isolation on of DPHY
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off of DPHY
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~_BIT5, _BIT5);

                // Digital power off of APHY
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~_BIT7, _BIT7);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on of APHY
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~_BIT7, 0x00);

                // Digital power on of DPHY
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_23_PD31_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off of DPHY
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~_BIT1, 0x00);

                // Digital isolation on of APHY
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Analog isolation on of APHY
                ScalerSetBit(P40_4F_VCCKOFF_CONTROL4F, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_23_PD31_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_USB_DFP_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_27_PD32_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_27_PD32_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_27_PD32_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_27_PD32_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_27_PD32_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_27_PD32_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_27_PD32_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_DPTX_DP20_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_28_PD33_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_28_PD33_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_28_PD33_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_28_PD33_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_28_PD33_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_28_PD33_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_28_PD33_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_DPTX_DP14_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_29_PD34_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_29_PD34_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_29_PD34_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_29_PD34_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_29_PD34_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_29_PD34_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_29_PD34_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_PX0_DP20_APHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_4A_VCCKOFF_CONTROL4A, ~_BIT0, 0x00);

                // Digital to analog isolation on
                ScalerSetBit(P6F_2A_PD35_POWER_CTRL, ~(_BIT3 | _BIT2), 0x00);

                // Digital power off
                ScalerSetBit(P6F_2A_PD35_POWER_CTRL, ~_BIT7, _BIT7);
            }
            else
            {
                // Digital power on
                ScalerSetBit(P6F_2A_PD35_POWER_CTRL, ~_BIT7, 0x00);

                // Digital to analog isolation on
                ScalerSetBit(P6F_2A_PD35_POWER_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Analog isolation off
                ScalerSetBit(P40_4A_VCCKOFF_CONTROL4A, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_PX0_AUX:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_4B_VCCKOFF_CONTROL4B, ~_BIT0, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_2B_PD36_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_2B_PD36_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_2B_PD36_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_2B_PD36_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_2B_PD36_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_2B_PD36_POWER_CTRL, ~_BIT1, 0x00);

                // Analog isolation off
                ScalerSetBit(P40_4B_VCCKOFF_CONTROL4B, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_2B_PD36_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_TOPOFF:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // DDR PAD output lock
                ScalerSetBit(P40_49_VCCKOFF_CONTROL49, ~_BIT0, 0x00);

                // Analog isolation on
                ScalerSetBit(P40_4E_VCCKOFF_CONTROL4E, ~_BIT0, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_80_PD39_POWER_CTRL, ~_BIT1, _BIT1);

                // RX_LV Power cut
                PCB_SET_RX_LV_POWER(_RX_LV_POWER_OFF);

                // USB_LV Power cut
#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_RETIMER_MAC0_SUPPORT == _ON))
                if(ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_NO_ACTION)
                {
                    PCB_USB_LV_POWER(_USB_LV_POWER_OFF);
                }
#else
                PCB_USB_LV_POWER(_USB_LV_POWER_OFF);
#endif

                // VCCKOFF Power cut
                PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_OFF);

                // DDR Power cut
                PCB_DDR_POWER(_DDR_POWER_OFF);

                PCB_DDR_POWER_RELEASE_TIME(_DDR_POWER_OFF_TIME);
            }
            else
            {
                // Power block power cut on
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_80_PD39_POWER_CTRL, ~_BIT0, _BIT0);

                    // DDR Power on
                    PCB_DDR_POWER(_DDR_POWER_ON);

                    // Wait for DDR stable, can't delete
                    ScalerTimerDelayXms(10);

                    // VCCKOFF Power on
                    PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_ON);

                    // USB_LV Power cut
#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_RETIMER_MAC0_SUPPORT == _ON))
                    if(ScalerUsb3RepeaterMacGetLowPowerStateStatus() != _USB3_RETIMER_EXIT_P3_PS)
                    {
                        PCB_USB_LV_POWER(_USB_LV_POWER_ON);
                    }
#else
                    PCB_USB_LV_POWER(_USB_LV_POWER_ON);
#endif

                    // RX_LV Power on
                    PCB_SET_RX_LV_POWER(_RX_LV_POWER_ON);

                    // Wait for 1.5V stable, can't delete
                    ScalerTimerDelayXms(10);
                }

                ScalerPinshareSoftReset();

                // Digital isolation off
                ScalerSetBit(P6F_80_PD39_POWER_CTRL, ~_BIT1, 0x00);

                // Analog isolation off
                ScalerSetBit(P40_4E_VCCKOFF_CONTROL4E, ~_BIT0, _BIT0);

                // DDR PAD output unlock
                ScalerSetBit(P40_49_VCCKOFF_CONTROL49, ~_BIT0, _BIT0);

                // Wait for VCCK_OFF Power On Stable
                POLLING_VCCK_OFF_STATUS(_VCCK_OFF_TIME_POLLING_POWER_ON);

                // Power Cut block Release
                ScalerSetBit(P6F_80_PD39_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_IMC_ENC_M1:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_32_PD42_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_32_PD42_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_32_PD42_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_32_PD42_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_32_PD42_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_32_PD42_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_32_PD42_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_IMC_DEC_M1:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_33_PD43_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_33_PD43_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_33_PD43_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_33_PD43_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_33_PD43_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_33_PD43_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_33_PD43_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_IMC_ENC_M2:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_34_PD44_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_34_PD44_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_34_PD44_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_34_PD44_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_34_PD44_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_34_PD44_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_34_PD44_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_IMC_DEC_M2:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_35_PD45_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_35_PD45_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_35_PD45_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_35_PD45_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_35_PD45_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_35_PD45_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_35_PD45_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_IMC_ENC_S1:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_3C_PD53_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_3C_PD53_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_3C_PD53_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_3C_PD53_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_3C_PD53_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_3C_PD53_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_3C_PD53_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_IMC_DEC_S1:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_3D_PD54_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_3D_PD54_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_3D_PD54_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_3D_PD54_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_3D_PD54_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_3D_PD54_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_3D_PD54_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_USB32_DFP_APHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_4C_VCCKOFF_CONTROL4C, ~_BIT0, 0x00);

                // Digital to analog isolation on
                ScalerSetBit(P6F_72_PD93_POWER_CTRL, ~_BIT1, _BIT1);

                // High voltage power off
                ScalerSetBit(P6F_72_PD93_POWER_CTRL, ~_BIT7, _BIT7);

                // OOBS High voltage power off
                ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT5, 0x00);

                // Low voltage analog power off
                ScalerSetBit(P6F_72_PD93_POWER_CTRL, ~_BIT6, _BIT6);

                // OOBS Low voltage power off
                ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT6, 0x00);

                // Low voltage digital power off
                ScalerSetBit(P6F_72_PD93_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                // Low voltage digital power on
                ScalerSetBit(P6F_72_PD93_POWER_CTRL, ~_BIT5, 0x00);

                // OOBS Low voltage power on
                ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT6, _BIT6);

                // Low voltage analog power on
                ScalerSetBit(P6F_72_PD93_POWER_CTRL, ~_BIT6, 0x00);

                // OOBS High voltage power on
                ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT5, _BIT5);

                // High voltage power on
                ScalerSetBit(P6F_72_PD93_POWER_CTRL, ~_BIT7, 0x00);

                // Digital to analog isolation off
                ScalerSetBit(P6F_72_PD93_POWER_CTRL, ~_BIT1, 0x00);

                // Analog isolation off
                ScalerSetBit(P40_4C_VCCKOFF_CONTROL4C, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_THERMAL_SENSOR:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // LV-to-HV isolation on
                ScalerSetBit(P5F_30_TSENSOR_POWER_00, ~_BIT1, _BIT1);

                // LV-to-LV isolation on
                ScalerSetBit(P40_5E_VCCKOFF_CONTROL5E, ~_BIT0, 0x00);

                // Low voltage analog power off
                ScalerSetBit(P5F_30_TSENSOR_POWER_00, ~(_BIT6 | _BIT5), 0x00);
            }
            else
            {
                // Low voltage analog power on
                ScalerSetBit(P5F_30_TSENSOR_POWER_00, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

                // LV-to-LV isolation off
                ScalerSetBit(P40_5E_VCCKOFF_CONTROL5E, ~_BIT0, _BIT0);

                // LV-to-HV isolation off
                ScalerSetBit(P5F_30_TSENSOR_POWER_00, ~_BIT1, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_0_BMC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_52_VCCKOFF_CONTROL52, ~_BIT0, 0x00);

                // Digital power off
                ScalerSetBit(P66_89_BMC_GENERAL_SETTING, ~_BIT2, 0x00);
            }
            else
            {
                // Digital power on
                ScalerSetBit(P66_89_BMC_GENERAL_SETTING, ~_BIT2, _BIT2);

                // Analog isolation off
                ScalerSetBit(P40_52_VCCKOFF_CONTROL52, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_1_BMC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_53_VCCKOFF_CONTROL53, ~_BIT0, 0x00);

                // Digital power off
                ScalerSetBit(P6C_89_BMC_GENERAL_SETTING, ~_BIT2, 0x00);
            }
            else
            {
                // Digital power on
                ScalerSetBit(P6C_89_BMC_GENERAL_SETTING, ~_BIT2, _BIT2);

                // Analog isolation off
                ScalerSetBit(P40_53_VCCKOFF_CONTROL53, ~_BIT0, _BIT0);
            }

            break;

        case _POWER_CUT_GROUP_VBO_EDP_8_LANE:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog to digital isolation on
                Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT31 | _BIT13 | _BIT10 | _BIT9 | _BIT8), 0x00);

                // Digital to analog isolation on
                Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT30 | _BIT13 | _BIT10 | _BIT9 | _BIT8), 0x00);

                // Digital power off
                Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT29 | _BIT13 | _BIT10 | _BIT9 | _BIT8), _BIT29);
            }
            else
            {
                // Digital power on
                Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT29 | _BIT13 | _BIT10 | _BIT9 | _BIT8), 0x00);

                // Digital to analog isolation off
                Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT30 | _BIT13 | _BIT10 | _BIT9 | _BIT8), _BIT30);

                // Analog to digital isolation off
                Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT31 | _BIT13 | _BIT10 | _BIT9 | _BIT8), _BIT31);
            }

            break;

        case _POWER_CUT_GROUP_DSC_1:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_85_PD102_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_85_PD102_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_85_PD102_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_85_PD102_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_85_PD102_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_85_PD102_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_85_PD102_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_0_CC_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_50_VCCKOFF_CONTROL50, ~_BIT0, 0x00);

                // Analog isolation on
                ScalerSetBit(P40_52_VCCKOFF_CONTROL52, ~_BIT0, 0x00);

                // Digital power off
                ScalerSetBit(P66_89_BMC_GENERAL_SETTING, ~_BIT2, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_86_PD103_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_86_PD103_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_86_PD103_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_86_PD103_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_86_PD103_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_86_PD103_POWER_CTRL, ~_BIT1, 0x00);

                // Digital power on
                ScalerSetBit(P66_89_BMC_GENERAL_SETTING, ~_BIT2, _BIT2);

                // Analog isolation off
                ScalerSetBit(P40_52_VCCKOFF_CONTROL52, ~_BIT0, _BIT0);

                // Analog isolation off
                ScalerSetBit(P40_50_VCCKOFF_CONTROL50, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_86_PD103_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_1_CC_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Analog isolation on
                ScalerSetBit(P40_51_VCCKOFF_CONTROL51, ~_BIT0, 0x00);

                // Analog isolation on
                ScalerSetBit(P40_53_VCCKOFF_CONTROL53, ~_BIT0, 0x00);

                // Digital power off
                ScalerSetBit(P6C_89_BMC_GENERAL_SETTING, ~_BIT2, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_87_PD104_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_87_PD104_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_87_PD104_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_87_PD104_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_87_PD104_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_87_PD104_POWER_CTRL, ~_BIT1, 0x00);

                // Digital power on
                ScalerSetBit(P6C_89_BMC_GENERAL_SETTING, ~_BIT2, _BIT2);

                // Analog isolation off
                ScalerSetBit(P40_53_VCCKOFF_CONTROL53, ~_BIT0, _BIT0);

                // Analog isolation off
                ScalerSetBit(P40_51_VCCKOFF_CONTROL51, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_87_PD104_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_1_PD_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_88_PD105_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_88_PD105_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_88_PD105_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_88_PD105_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_88_PD105_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_88_PD105_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_88_PD105_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_10_BIT_SARADC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Disable SARADC Auto Mode & Conversion
                ScalerSetBit(P7F_00_10B_ADC_CTL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

                // Disable SARADC VREF Enable
                ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT7, 0x00);

                // Disable SARADC LDO
                ScalerSetBit(P7F_00_10B_ADC_CTL, ~_BIT4, 0x00);

                // Analog isolation on
                ScalerSetBit(P40_5F_VCCKOFF_CONTROL5F, ~_BIT0, 0x00);

                // Digital isolation on
                ScalerSetBit(P6F_89_PD106_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_89_PD106_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_89_PD106_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_89_PD106_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_89_PD106_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_89_PD106_POWER_CTRL, ~_BIT1, 0x00);

                // Analog isolation off
                ScalerSetBit(P40_5F_VCCKOFF_CONTROL5F, ~_BIT0, _BIT0);

                // Power Cut block Release
                ScalerSetBit(P6F_89_PD106_POWER_CTRL, ~_BIT0, 0x00);

                // Enable SARADC LDO
                ScalerSetBit(P7F_00_10B_ADC_CTL, ~_BIT4, _BIT4);

                // Enable SARADC VREF Enable
                ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT7, _BIT7);

                ScalerTimerDelayXms(2);

                // Enable SARADC Auto Mode & Conversion
                ScalerSetBit(P7F_00_10B_ADC_CTL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
            }

            break;

        case _POWER_CUT_GROUP_HDCP_ECDSA:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_8A_PD107_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_8A_PD107_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_8A_PD107_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_8A_PD107_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_8A_PD107_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_8A_PD107_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_8A_PD107_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP14_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A0_PD108_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_A0_PD108_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A0_PD108_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A0_PD108_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A0_PD108_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_A0_PD108_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A0_PD108_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP14_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A1_PD109_POWER_CTRL, ~_BIT1, _BIT1);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP20_U32_APHY) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP20_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_A1_PD109_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A1_PD109_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A1_PD109_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A1_PD109_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Power on bandgap
                ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital isolation off
                ScalerSetBit(P6F_A1_PD109_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A1_PD109_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP20_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A2_PD110_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_A2_PD110_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A2_PD110_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A2_PD110_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A2_PD110_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_A2_PD110_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A2_PD110_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP20_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A3_PD111_POWER_CTRL, ~_BIT1, _BIT1);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP20_U32_APHY) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP14_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_A3_PD111_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A3_PD111_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A3_PD111_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A3_PD111_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Power on bandgap
                ScalerSetBit(P6F_60_PD1_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital isolation off
                ScalerSetBit(P6F_A3_PD111_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A3_PD111_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP14_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A4_PD112_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_A4_PD112_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A4_PD112_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A4_PD112_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A4_PD112_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_A4_PD112_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A4_PD112_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP14_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A5_PD113_POWER_CTRL, ~_BIT1, _BIT1);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP20_U32_APHY) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP20_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_A5_PD113_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A5_PD113_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A5_PD113_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A5_PD113_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Power on bandgap
                ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital isolation off
                ScalerSetBit(P6F_A5_PD113_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A5_PD113_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP20_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A6_PD114_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_A6_PD114_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A6_PD114_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A6_PD114_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A6_PD114_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_A6_PD114_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A6_PD114_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP20_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A7_PD115_POWER_CTRL, ~_BIT1, _BIT1);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP20_U32_APHY) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP14_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_A7_PD115_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A7_PD115_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A7_PD115_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A7_PD115_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Power on bandgap
                ScalerSetBit(P6F_65_PD6_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital isolation off
                ScalerSetBit(P6F_A7_PD115_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A7_PD115_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP14_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A8_PD116_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_A8_PD116_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A8_PD116_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A8_PD116_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A8_PD116_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_A8_PD116_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A8_PD116_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP14_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_A9_PD117_POWER_CTRL, ~_BIT1, _BIT1);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP20_APHY) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP20_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_A9_PD117_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_A9_PD117_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_A9_PD117_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_A9_PD117_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Power on bandgap
                ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital isolation off
                ScalerSetBit(P6F_A9_PD117_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_A9_PD117_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP20_DPHY:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_AA_PD118_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_AA_PD118_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_AA_PD118_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_AA_PD118_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_AA_PD118_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_AA_PD118_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_AA_PD118_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP20_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_AB_PD119_POWER_CTRL, ~_BIT1, _BIT1);

                // Power off bandgap
                if((ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP20_APHY) == _POWER_CUT_ON) &&
                   (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP14_MAC) == _POWER_CUT_ON))
                {
                    ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT0, 0x00);
                }

                // Digital power off
                ScalerSetBit(P6F_AB_PD119_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_AB_PD119_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_AB_PD119_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_AB_PD119_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Power on bandgap
                ScalerSetBit(P6F_6A_PD11_POWER_CTRL, ~_BIT0, _BIT0);

                // Digital isolation off
                ScalerSetBit(P6F_AB_PD119_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_AB_PD119_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_USB_UFP_RETIMER_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_8C_PD121_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_8C_PD121_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_8C_PD121_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_8C_PD121_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_8C_PD121_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_8C_PD121_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_8C_PD121_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_USB_DFP_RETIMER_MAC:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_8D_PD122_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_8D_PD122_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_8D_PD122_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_8D_PD122_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_8D_PD122_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_8D_PD122_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_8D_PD122_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        case _POWER_CUT_GROUP_ANTI_ALIASING_M1M2:

            if(enumPowerCut == _POWER_CUT_ON)
            {
                // Digital isolation on
                ScalerSetBit(P6F_8E_PD123_POWER_CTRL, ~_BIT1, _BIT1);

                // Digital power off
                ScalerSetBit(P6F_8E_PD123_POWER_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                if(enumPowerReset == _POWER_RESET_ENABLE)
                {
                    // Power Cut block Reset
                    ScalerSetBit(P6F_8E_PD123_POWER_CTRL, ~_BIT0, _BIT0);
                }

                // Digital power on
                ScalerSetBit(P6F_8E_PD123_POWER_CTRL, ~_BIT5, 0x00);

                // Wait for digital power on flag
                ucCounter = 50;

                while((ScalerGetBit(P6F_8E_PD123_POWER_CTRL, _BIT4) != 0x00) && (ucCounter-- > 0))
                {
                    DELAY_5US();
                }

                // Digital isolation off
                ScalerSetBit(P6F_8E_PD123_POWER_CTRL, ~_BIT1, 0x00);

                // Power Cut block Release
                ScalerSetBit(P6F_8E_PD123_POWER_CTRL, ~_BIT0, 0x00);
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Group Power on/off
// Input Value  : enumPowerGroup : _POWER_CUT_GROUP_DPMAC0 ~ _POWER_CUT_GROUP_TOPOFF
// Output Value : _POWER_CUT_ON / _POWER_CUT_OFF
//--------------------------------------------------
EnumPowerCut ScalerPowerGroupGetPowerCutStatus(EnumPowerGroup enumPowerGroup)
{
    switch(enumPowerGroup)
    {
        case _POWER_CUT_GROUP_RX0_DP20_U32_APHY:

            if((ScalerGetBit(P6F_60_PD1_POWER_CTRL, (_BIT7 | _BIT3)) == _BIT7) && (ScalerGetBit(P40_41_VCCKOFF_CONTROL41, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP_DPHY:

            if(ScalerGetBit(P6F_61_PD2_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP_AUX:

            if((ScalerGetBit(P6F_62_PD3_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1)) && (ScalerGetBit(P40_46_VCCKOFF_CONTROL46, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP20_U32_APHY:

            if((ScalerGetBit(P6F_65_PD6_POWER_CTRL, (_BIT7 | _BIT3)) == _BIT7) && (ScalerGetBit(P40_42_VCCKOFF_CONTROL42, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP_DPHY:

            if(ScalerGetBit(P6F_66_PD7_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP_AUX:

            if((ScalerGetBit(P6F_67_PD8_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1)) && (ScalerGetBit(P40_47_VCCKOFF_CONTROL47, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP20_APHY:

            if((ScalerGetBit(P6F_6A_PD11_POWER_CTRL, (_BIT7 | _BIT3)) == _BIT7) && (ScalerGetBit(P40_43_VCCKOFF_CONTROL43, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP_DPHY:

            if(ScalerGetBit(P6F_6B_PD12_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP_AUX:

            if((ScalerGetBit(P6F_6C_PD13_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1)) && (ScalerGetBit(P40_48_VCCKOFF_CONTROL48, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX3_HDMI21_APHY:

            if((ScalerGetBit(P7C_16_GDI_CTRL1, (_BIT1 | _BIT0)) == _BIT1) && (ScalerGetBit(P40_44_VCCKOFF_CONTROL44, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX3_HDMI_DPHY:

            if(ScalerGetBit(P67_04_PD17_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX3_HDMI20_MAC:

            if(ScalerGetBit(P67_03_PD18_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX3_HDMI21_MAC:

            if(ScalerGetBit(P67_02_PD19_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX4_HDMI21_APHY:

            if((ScalerGetBit(P7D_16_GDI_CTRL1, (_BIT1 | _BIT0)) == _BIT1) && (ScalerGetBit(P40_45_VCCKOFF_CONTROL45, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX4_HDMI_DPHY:

            if(ScalerGetBit(P1E_04_PD21_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX4_HDMI20_MAC:

            if(ScalerGetBit(P1E_03_PD22_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX4_HDMI21_MAC:

            if(ScalerGetBit(P1E_02_PD23_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_DSC_0:

            if(ScalerGetBit(P6F_21_PD24_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_FORMAT_CONVERSION:

            if(ScalerGetBit(P6F_26_PD25_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_0_PD_MAC:

            if(ScalerGetBit(P6F_20_PD29_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_USB_UFP:

            if((ScalerGetBit(P6F_83_PD30_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1)) &&
               (ScalerGetBit(P40_4D_VCCKOFF_CONTROL5A, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_JFM:

            if((ScalerGetBit(P6F_23_PD31_POWER_CTRL, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1)) == (_BIT7 | _BIT5 | _BIT4 | _BIT1)) &&
               (ScalerGetBit(P40_4F_VCCKOFF_CONTROL4F, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_USB_DFP_DPHY:

            if(ScalerGetBit(P6F_27_PD32_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_DPTX_DP20_MAC:

            if(ScalerGetBit(P6F_28_PD33_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_DPTX_DP14_MAC:

            if(ScalerGetBit(P6F_29_PD34_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_PX0_DP20_APHY:

            if((ScalerGetBit(P6F_2A_PD35_POWER_CTRL, (_BIT7 | _BIT3 | _BIT2)) == _BIT7) && (ScalerGetBit(P40_4A_VCCKOFF_CONTROL4A, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_PX0_AUX:

            if((ScalerGetBit(P6F_2B_PD36_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1)) && (ScalerGetBit(P40_4B_VCCKOFF_CONTROL4B, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_TOPOFF:

            if((ScalerGetBit(P6F_80_PD39_POWER_CTRL, _BIT1) == _BIT1) &&
               (ScalerGetBit(P40_49_VCCKOFF_CONTROL49, _BIT0) == 0x00) &&
               (ScalerGetBit(P40_4E_VCCKOFF_CONTROL4E, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_IMC_ENC_M1:

            if(ScalerGetBit(P6F_32_PD42_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_IMC_DEC_M1:

            if(ScalerGetBit(P6F_33_PD43_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_IMC_ENC_M2:

            if(ScalerGetBit(P6F_34_PD44_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_IMC_DEC_M2:

            if(ScalerGetBit(P6F_35_PD45_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_IMC_ENC_S1:

            if(ScalerGetBit(P6F_3C_PD53_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_IMC_DEC_S1:

            if(ScalerGetBit(P6F_3D_PD54_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_USB32_DFP_APHY:

            if((ScalerGetBit(P6F_72_PD93_POWER_CTRL, (_BIT7 | _BIT6 | _BIT5 | _BIT1)) == (_BIT7 | _BIT6 | _BIT5 | _BIT1)) && (ScalerGetBit(P40_4C_VCCKOFF_CONTROL4C, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_THERMAL_SENSOR:

            if((ScalerGetBit(P5F_30_TSENSOR_POWER_00, (_BIT6 | _BIT5 | _BIT1)) == _BIT1) && (ScalerGetBit(P40_5E_VCCKOFF_CONTROL5E, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }
            break;

        case _POWER_CUT_GROUP_TYPE_C_0_BMC:

            if((ScalerGetBit(P66_89_BMC_GENERAL_SETTING, _BIT2) == 0x00) && (ScalerGetBit(P40_52_VCCKOFF_CONTROL52, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_1_BMC:

            if((ScalerGetBit(P6C_89_BMC_GENERAL_SETTING, _BIT2) == 0x00) && (ScalerGetBit(P40_53_VCCKOFF_CONTROL53, _BIT0) == 0x00))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_VBO_EDP_8_LANE:

            if(Scaler32GetBit(PB58050_00_DP14_TX_CMU0, (_BIT31 | _BIT30)) == 0x00)
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_DSC_1:

            if(ScalerGetBit(P6F_85_PD102_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_0_CC_MAC:

            if((ScalerGetBit(P66_89_BMC_GENERAL_SETTING, _BIT2) == 0x00) &&
               (ScalerGetBit(P40_50_VCCKOFF_CONTROL50, _BIT0) == 0x00) &&
               (ScalerGetBit(P40_52_VCCKOFF_CONTROL52, _BIT0) == 0x00) &&
               (ScalerGetBit(P6F_86_PD103_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1)))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_1_CC_MAC:

            if((ScalerGetBit(P6C_89_BMC_GENERAL_SETTING, _BIT2) == 0x00) &&
               (ScalerGetBit(P40_51_VCCKOFF_CONTROL51, _BIT0) == 0x00) &&
               (ScalerGetBit(P40_53_VCCKOFF_CONTROL53, _BIT0) == 0x00) &&
               (ScalerGetBit(P6F_87_PD104_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1)))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_1_PD_MAC:

            if(ScalerGetBit(P6F_88_PD105_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_10_BIT_SARADC:

            if((ScalerGetBit(P7F_00_10B_ADC_CTL, _BIT4) == 0x00) &&
               (ScalerGetBit(P7F_55_10B_ADC_LDO_CTRL, _BIT7) == 0x00) &&
               (ScalerGetBit(P40_5F_VCCKOFF_CONTROL5F, _BIT0) == 0x00) &&
               (ScalerGetBit(P6F_89_PD106_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1)))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_HDCP_ECDSA:

            if(ScalerGetBit(P6F_8A_PD107_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP14_DPHY:

            if(ScalerGetBit(P6F_A0_PD108_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;



        case _POWER_CUT_GROUP_RX0_DP14_MAC:

            if(ScalerGetBit(P6F_A1_PD109_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP20_DPHY:

            if(ScalerGetBit(P6F_A2_PD110_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX0_DP20_MAC:

            if(ScalerGetBit(P6F_A3_PD111_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP14_DPHY:

            if(ScalerGetBit(P6F_A4_PD112_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP14_MAC:

            if(ScalerGetBit(P6F_A5_PD113_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP20_DPHY:

            if(ScalerGetBit(P6F_A6_PD114_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX1_DP20_MAC:

            if(ScalerGetBit(P6F_A7_PD115_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP14_DPHY:

            if(ScalerGetBit(P6F_A8_PD116_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP14_MAC:

            if(ScalerGetBit(P6F_A9_PD117_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP20_DPHY:

            if(ScalerGetBit(P6F_AA_PD118_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_RX2_DP20_MAC:

            if(ScalerGetBit(P6F_AB_PD119_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_USB_UFP_RETIMER_MAC:

            if(ScalerGetBit(P6F_8C_PD121_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_USB_DFP_RETIMER_MAC:

            if(ScalerGetBit(P6F_8D_PD122_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        case _POWER_CUT_GROUP_ANTI_ALIASING_M1M2:

            if(ScalerGetBit(P6F_8E_PD123_POWER_CTRL, (_BIT5 | _BIT4 | _BIT1)) == (_BIT5 | _BIT4 | _BIT1))
            {
                return _POWER_CUT_ON;
            }
            else
            {
                return _POWER_CUT_OFF;
            }

            break;

        default:

            break;
    }

    return _POWER_CUT_ON;
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : enumPowerRecoverGroup : _POWER_DATA_RECOVER_TOP ~ _POWER_DATA_RECOVER_DPMAC
// Output Value : None
//-------------------------------------------------
void ScalerPowerGroupRecoverData(EnumPowerRecoverGroup enumPowerRecoverGroup)
{
    switch(enumPowerRecoverGroup)
    {
        case _POWER_DATA_RECOVER_TOP:

            //////////////////////// Pin Share Start /////////////////////////////////////

            PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON();

            ScalerPinsharePowerOnReset();

            //////////////////////// Pin Share End /////////////////////////////////////

            //////////////////////// LVDS + LVDSPLL and VBO block start //////////////////

#if(_PANEL_STYLE == _PANEL_LVDS)
            // LVDS Port Power On recover
            ScalerDisplayLvdsInitialTable();
#elif(_PANEL_STYLE == _PANEL_VBO)
            // VBO Power On recover
            ScalerDisplayVboTxInitialTable();
#elif(_PANEL_STYLE == _PANEL_DPTX)
            // eDptx Power On recover
            ScalerDisplayDpTxPhyInitial();
#endif
            // Set Framesync Lastline Multiple According Tx Port Number
            ScalerDDomainSetFsyncLastlineMultiple();

            //////////////////////// LVDS + LVDSPLL and VBO block End ////////////////////


            //////////////////////// DPLL/MPLL/DDR PLL block start ///////////////////////

            // DPLL power up
            ScalerPLLSetDPLLReset();

            //////////////////////// DPLL/MPLL/DDR PLL  block End ////////////////////////


            //////////////////////// DDR DLL + DDR Delaychain start //////////////////////

            //////////////////////// DDR DLL + DDR Delaychain End ////////////////////////

            //////////////////////// HDCP 2.2 start //////////////////////

#if(_HDCP_2_2_SUPPORT == _ON)
            ScalerHdcp2Initial();
#endif

            //////////////////////// HDCP 2.2 End ////////////////////////

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
            ScalerTypeCInitial();
#endif

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
            ScalerHdmiArcTxInitial();
#endif

            break;

        case _POWER_DATA_RECOVER_GDITX:

            //////////////////////// GDI Tx (eDP)block start /////////////////////////////

#if(_DP_TX_SUPPORT == _ON)
            // AC_ON_TO_NORMAL or OFF_TO_NORMAL or PS_TO_NORMAL
            ScalerSyncDpTxPowerProc(_POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)
            ScalerDisplayDpTxInitial();
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

            //////////////////////// GDI Tx (eDP) block End //////////////////////////////

            break;

        case _POWER_DATA_RECOVER_DPMAC:

#if(_DP_SUPPORT == _ON)
            // Recover Data from Power Cut State
            ScalerDpMacRxPowerDataRecover();
#endif

            //////////////////////// DPLL video GDI0~1 block start ///////////////////////

#if(_DSC_DECODER_SUPPORT == _ON)
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
            ScalerDscDecoderInitial(_DSC_MAC_0);
#endif
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
            ScalerDscDecoderInitial(_DSC_MAC_1);
#endif
            ScalerDscDecoderDataRecover();
#endif

#if(_DP_SUPPORT == _ON)
            ScalerDpRxPhyInitial();
#endif

            //////////////////////// DPLL video GDI0~1 block End /////////////////////////


            //////////////////////// DPLL audio GDI0~1 block start ///////////////////////

            //////////////////////// DPLL audio GDI0~1 block End /////////////////////////


            //////////////////////// DPLL MST to SST0/1 block start //////////////////////

            //////////////////////// DPLL MST to SST0/1 block End /////////////////////////


            //////////////////////// HDMI2.0/DP1.2 Phy GDI0~1 block start /////////////////

            //////////////////////// HDMI2.0/DP1.2 Phy GDI0~1 block End ///////////////////


            //////////////////////// HDMI2.0/DP1.2 Phy DFE GDI2~5 block start /////////////

            //////////////////////// HDMI2.0/DP1.2 Phy DFE GDI2~5 block End ///////////////

#if(_HDMI_FRL_SUPPORT == _ON)
            ScalerHdmiFrlMacRxInitial();
#endif

            //////////////////////// Format Conversion block start ////////////////////////

            //////////////////////// Format Conversion block End //////////////////////////

#if((_DP_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
            ScalerDpMstRxInitialSetting();
#endif

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Group Power Align Default State when AC ON
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupDefaultStateAlign(void)
{
    // Main Domain power on if default register is mismatch
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_TOPOFF, _POWER_CUT_OFF, _POWER_RESET_DISABLE);
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_PX0_DP20_APHY, _POWER_CUT_OFF, _POWER_RESET_DISABLE);
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_USB_UFP, _POWER_CUT_OFF, _POWER_RESET_DISABLE);
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_THERMAL_SENSOR, _POWER_CUT_OFF, _POWER_RESET_DISABLE);

    // Sub-Domain power on if default register is mismatch
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_VBO_EDP_8_LANE, _POWER_CUT_OFF, _POWER_RESET_DISABLE);
}

//--------------------------------------------------
// Description  : Group Power Setting when AC ON
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupPowerACOnSetting(void)
{
    BYTE ucIndex = 0x00;
    BYTE ucPowerGroup = 0x00;

    // Return when power domain force enable
    if(ScalerPowerDomainEnableStatus() == _TRUE)
    {
        return;
    }

    // Scanning all power domain
    for(ucPowerGroup = 0; ucPowerGroup < (sizeof(tGroupPowerCutOn) / sizeof(tGroupPowerCutOn[0])); ucPowerGroup++)
    {
        for(ucIndex = 0; ucIndex < tGroupPowerCutOn[ucPowerGroup].ucMaxSize; ucIndex++)
        {
            EnumPowerGroup enumPowerGroup = tGroupPowerCutOn[ucPowerGroup].pstPowerCutGroup[ucIndex].enumPowerGroup;
            EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerCutOn[ucPowerGroup].pstPowerCutGroup[ucIndex].b2PowerDomainSupport;

            if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
            {
                enumPowerDomainSupport = ScalerPowerGetPowerDomainSupport(enumPowerGroup);
            }

            // Unused power domain judgment
            if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE)
            {
                ScalerPowerGroupPowerCut(enumPowerGroup, _POWER_CUT_ON, _POWER_RESET_DISABLE);
            }
        }
    }

    // Scanning all power sub-domain
    for(ucPowerGroup = 0; ucPowerGroup < (sizeof(tGroupPowerSubDomain) / sizeof(tGroupPowerSubDomain[0])); ucPowerGroup++)
    {
        for(ucIndex = 0; ucIndex < tGroupPowerSubDomain[ucPowerGroup].ucMaxSize; ucIndex++)
        {
            EnumPowerGroup enumPowerGroup = tGroupPowerSubDomain[ucPowerGroup].pstPowerCutGroup[ucIndex].enumPowerGroup;
            EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerSubDomain[ucPowerGroup].pstPowerCutGroup[ucIndex].b2PowerDomainSupport;

            if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
            {
                enumPowerDomainSupport = ScalerPowerGetPowerDomainSupport(enumPowerGroup);
            }

            // Unused power domain judgment
            if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE)
            {
                ScalerPowerGroupPowerCut(enumPowerGroup, _POWER_CUT_ON, _POWER_RESET_DISABLE);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Sub-Group Power Ready for Control
// Input Value  : enumPowerGroup
//                enumPowerCut: _POWER_CUT_ON(Low Power) / _POWER_CUT_OFF(Normal Operation)
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerPowerSubGroupGetControlReady(EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut)
{
    switch(enumPowerGroup)
    {
        case _POWER_CUT_GROUP_TYPE_C_0_BMC:

            // Power enable control judgment
            if((enumPowerCut == _POWER_CUT_OFF) && (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_TYPE_C_0_CC_MAC) == _POWER_CUT_ON))
            {
                return _FAIL;
            }

            break;

        case _POWER_CUT_GROUP_TYPE_C_1_BMC:

            // Power enable control judgment
            if((enumPowerCut == _POWER_CUT_OFF) && (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_TYPE_C_1_CC_MAC) == _POWER_CUT_ON))
            {
                return _FAIL;
            }

            break;

        case _POWER_CUT_GROUP_VBO_EDP_8_LANE:

            // Power enable control judgment
            if((enumPowerCut == _POWER_CUT_OFF) && (ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_TOPOFF) == _POWER_CUT_ON))
            {
                return _FAIL;
            }

            break;

        default:

            break;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Group Power on/off for other IP
// Input Value  : enumPowerGroup
//                enumPowerCut: _POWER_CUT_ON(Low Power) / _POWER_CUT_OFF(Normal Operation)
//                enumPowerOnDelay
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerPowerDomainEnableControl(EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut, EnumPowerOnDelay enumPowerOnDelay)
{
    BYTE ucIndex = 0x00;
    BYTE ucPowerGroup = 0x00;
    EnumPowerReset enumPowerReset = _POWER_RESET_ENABLE;

    // Return when power domain force enable
    if(ScalerPowerDomainEnableStatus() == _TRUE)
    {
        return _FAIL;
    }

    // Scanning all power domain
    for(ucPowerGroup = 0; ucPowerGroup < (sizeof(tGroupPowerCutOn) / sizeof(tGroupPowerCutOn[0])); ucPowerGroup++)
    {
        for(ucIndex = 0; ucIndex < tGroupPowerCutOn[ucPowerGroup].ucMaxSize; ucIndex++)
        {
            EnumPowerGroup enumCurrentPowerGroup = tGroupPowerCutOn[ucPowerGroup].pstPowerCutGroup[ucIndex].enumPowerGroup;

            // If power domain matches
            if(enumCurrentPowerGroup == enumPowerGroup)
            {
                EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerCutOn[ucPowerGroup].pstPowerCutGroup[ucIndex].b2PowerDomainSupport;

                // Get Power Domain Support
                if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
                {
                    enumPowerDomainSupport = ScalerPowerGetPowerDomainSupport(enumPowerGroup);
                }

                // Unused power domain judgment
                if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE)
                {
                    enumPowerCut = _POWER_CUT_ON;
                }

                // Check Power Status
                if(ScalerPowerGroupGetPowerCutStatus(enumPowerGroup) == enumPowerCut)
                {
                    return _SUCCESS;
                }

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if(ScalerPowerCutSwitchCheck(enumPowerGroup, enumPowerCut) == _FALSE)
                {
                    return _FAIL;
                }
#endif

                // Reset control
                if(enumPowerCut == _POWER_CUT_OFF)
                {
                    enumPowerReset = _POWER_RESET_ENABLE;
                }
                else
                {
                    enumPowerReset = _POWER_RESET_DISABLE;
                }

                // Power Control
                ScalerPowerGroupPowerCut(enumPowerGroup, enumPowerCut, enumPowerReset);

                if(enumPowerCut == _POWER_CUT_OFF)
                {
                    // Delay when Power Domain Power ON
                    ScalerPowerDomainEnableDelay(enumPowerOnDelay);
                }

                return _SUCCESS;
            }
        }
    }

    // Scanning all power sub-domain
    for(ucPowerGroup = 0; ucPowerGroup < (sizeof(tGroupPowerSubDomain) / sizeof(tGroupPowerSubDomain[0])); ucPowerGroup++)
    {
        for(ucIndex = 0; ucIndex < tGroupPowerSubDomain[ucPowerGroup].ucMaxSize; ucIndex++)
        {
            EnumPowerGroup enumCurrentPowerGroup = tGroupPowerSubDomain[ucPowerGroup].pstPowerCutGroup[ucIndex].enumPowerGroup;

            // If power domain matches
            if(enumCurrentPowerGroup == enumPowerGroup)
            {
                EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerSubDomain[ucPowerGroup].pstPowerCutGroup[ucIndex].b2PowerDomainSupport;

                // Get Power Domain Support
                if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
                {
                    enumPowerDomainSupport = ScalerPowerGetPowerDomainSupport(enumPowerGroup);
                }

                // Unused power domain judgment
                if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE)
                {
                    enumPowerCut = _POWER_CUT_ON;
                }

                // Check power sub-domain ready for control or not
                if(ScalerPowerSubGroupGetControlReady(enumPowerGroup, enumPowerCut) == _FAIL)
                {
                    return _FAIL;
                }

                // Check Power Status
                if(ScalerPowerGroupGetPowerCutStatus(enumPowerGroup) == enumPowerCut)
                {
                    return _SUCCESS;
                }

                // Reset control
                if(enumPowerCut == _POWER_CUT_OFF)
                {
                    enumPowerReset = _POWER_RESET_ENABLE;
                }
                else
                {
                    enumPowerReset = _POWER_RESET_DISABLE;
                }

                // Power Control
                ScalerPowerGroupPowerCut(enumPowerGroup, enumPowerCut, enumPowerReset);

                if(enumPowerCut == _POWER_CUT_OFF)
                {
                    // Delay when Power Domain Power ON
                    ScalerPowerDomainEnableDelay(enumPowerOnDelay);
                }

                return _SUCCESS;
            }
        }
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Get I Domain S1 Power Cut Status
// Input Value  : None
// Output Value : _POWER_CUT_ON / _POWER_CUT_OFF
//--------------------------------------------------
EnumPowerCut ScalerPowerGetIDomainS1PowerCutStatus(void)
{
/*
    return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_I_DOMAIN_S1S2);
*/
    // for compile
    return _POWER_CUT_ON;
}

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : Power Cut Switch Check
// Input Value  : EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerPowerCutSwitchCheck(EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut)
{
    switch(enumPowerGroup)
    {
#if(_DP_SUPPORT == _ON)
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX0_DP14_MAC:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX0_DP20_MAC:
#endif
            if((GET_DP_DC_OFF_HPD_HIGH() == _ON) && (enumPowerCut == _POWER_CUT_ON))
            {
#if(_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON)
                if(ScalerDpRxCableStatus(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _TRUE)
#endif
                {
                    return _FALSE;
                }
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX1_DP14_MAC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX1_DP20_MAC:
#endif
            if((GET_DP_DC_OFF_HPD_HIGH() == _ON) && (enumPowerCut == _POWER_CUT_ON))
            {
#if(_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON)
                if(ScalerDpRxCableStatus(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _TRUE)
#endif
                {
                    return _FALSE;
                }
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX2_DP14_MAC:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX2_DP20_MAC:
#endif
            if((GET_DP_DC_OFF_HPD_HIGH() == _ON) && (enumPowerCut == _POWER_CUT_ON))
            {
#if(_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON)
                if(ScalerDpRxCableStatus(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_2)) == _TRUE)
#endif
                {
                    return _FALSE;
                }
            }

            break;
#endif
#endif

#if((_HDMI_SUPPORT == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX3_HDMI20_MAC:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX3_HDMI21_MAC:
#endif
            if(enumPowerCut == _POWER_CUT_ON)
            {
                if(ScalerTmdsMacRxGetCableStatus(ScalerTmdsMacRxRxDxMapping(_RX3)) == _TRUE)
                {
                    return _FALSE;
                }
            }

            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX4_HDMI20_MAC:

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _POWER_CUT_GROUP_RX4_HDMI21_MAC:
#endif
            if(enumPowerCut == _POWER_CUT_ON)
            {
                if(ScalerTmdsMacRxGetCableStatus(ScalerTmdsMacRxRxDxMapping(_RX4)) == _TRUE)
                {
                    return _FALSE;
                }
            }

            break;
#endif
#endif // End if #if((_HDMI_SUPPORT == _ON) && (_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON))

        default:
            break;
    }

    return _TRUE;
}
#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

//--------------------------------------------------
// Description  : Get power domain clock gating support status by function
// Input Value  : enumPowerClockGatingGroup -> target clock gating group
// Output Value : support status
//--------------------------------------------------
EnumPowerDomainSupport ScalerPowerGetPowerDomainClockGatingSupport(EnumPowerClockGatingGroup enumPowerClockGatingGroup)
{
    enumPowerClockGatingGroup = enumPowerClockGatingGroup;
    return _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE;
}

//--------------------------------------------------
// Description  : Get power domain clock gating PS/PD Mode by function
// Input Value  : enumPowerClockGatingGroup -> target clock gating group
// Output Value : PS/PD Mode
//--------------------------------------------------
EnumPowerPsPdMode ScalerPowerGetPowerDomainClockGatingPsPdMode(EnumPowerClockGatingGroup enumPowerClockGatingGroup)
{
    enumPowerClockGatingGroup = enumPowerClockGatingGroup;
    return _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL;
}

//--------------------------------------------------
// Description  : Clock Gating block flow
// Input Value  : enumPowerAction    --> Power action description.
// Output Value : None
//--------------------------------------------------
void ScalerPowerClockGatingControl(EnumPowerAction enumPowerAction)
{
    BYTE ucIndex = 0x00;
    BYTE ucClockGatingGroup = 0x00;

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_INITIAL:

            // Clock Gating un-used clock-gating group
            ScalerPowerGroupClockGatingACOnSetting();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:

            // Start Clock Gating
            for(ucClockGatingGroup = 0; ucClockGatingGroup < (sizeof(tGroupPowerClockGating) / sizeof(tGroupPowerClockGating[0])); ucClockGatingGroup++)
            {
                for(ucIndex = 0; ucIndex < tGroupPowerClockGating[ucClockGatingGroup].ucMaxSize; ucIndex++)
                {
                    EnumPowerClockGatingGroup enumPowerClockGatingGroup = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].enumPowerClockGatingGroup;
                    EnumPowerPsPdMode enumPowerPsPdMode = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].b2PsPdModeOperation;
                    EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].b2PowerDomainSupport;

                    // Clock Gating Domain support_by_function judgment
                    if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
                    {
                        enumPowerDomainSupport = ScalerPowerGetPowerDomainClockGatingSupport(enumPowerClockGatingGroup);
                    }

                    // Clock Gating Domain PSPD_mode_by_function judgment
                    if(enumPowerPsPdMode == _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION)
                    {
                        enumPowerPsPdMode = ScalerPowerGetPowerDomainClockGatingPsPdMode(enumPowerClockGatingGroup);
                    }

                    // Unused Clock Gating Domain judgment
                    if((ScalerPowerDomainEnableStatus() == _TRUE) ||
                       ((enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_ENABLE) &&
                        (enumPowerPsPdMode == _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL)))
                    {
                        ScalerPowerGroupClockGating(enumPowerClockGatingGroup, _CLOCK_GATING_ON);
                    }
                }
            }

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            // Start Clock run
            for(ucClockGatingGroup = 0; ucClockGatingGroup < (sizeof(tGroupPowerClockGating) / sizeof(tGroupPowerClockGating[0])); ucClockGatingGroup++)
            {
                for(ucIndex = 0; ucIndex < tGroupPowerClockGating[ucClockGatingGroup].ucMaxSize; ucIndex++)
                {
                    EnumPowerClockGatingGroup enumPowerClockGatingGroup = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].enumPowerClockGatingGroup;
                    EnumPowerClockGating enumPowerClockGating = _CLOCK_GATING_ON;

                    // Clock Gating Domain ON/OFF judgment
                    if(ScalerPowerDomainEnableStatus() == _TRUE)
                    {
                        enumPowerClockGating = _CLOCK_GATING_OFF;
                    }
                    else
                    {
                        EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].b2PowerDomainSupport;

                        // Clock Gating Domain support_by_function judgment
                        if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
                        {
                            enumPowerDomainSupport = ScalerPowerGetPowerDomainClockGatingSupport(enumPowerClockGatingGroup);
                        }

                        // Unused Clock Gating Domain judgment
                        if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_ENABLE)
                        {
                            EnumPowerPsPdMode enumPowerPsPdMode = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].b2PsPdModeOperation;

                            enumPowerClockGating = _CLOCK_GATING_OFF;

                            // Clock Gating Domain PSPD_mode_by_function judgment
                            if(enumPowerPsPdMode == _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION)
                            {
                                enumPowerPsPdMode = ScalerPowerGetPowerDomainClockGatingPsPdMode(enumPowerClockGatingGroup);
                            }

                            // Special Power Operation Mode Judgment
                            switch(enumPowerPsPdMode)
                            {
                                case _POWER_DOMAIN_PSPD_MODE_USER_CONTROL:

                                    if(enumPowerAction != _POWER_ACTION_AC_ON_TO_NORMAL)
                                    {
                                        // No operation
                                        continue;
                                    }

                                    break;

                                case _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON:
                                case _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL:
                                default:
                                    break;
                            }
                        }
                        else
                        {
                            enumPowerClockGating = _CLOCK_GATING_ON;
                        }
                    }

                    // Clock Gating Domain Final Control
                    ScalerPowerGroupClockGating(enumPowerClockGatingGroup, enumPowerClockGating);
                }
            }

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_PS:

            break;

        case _POWER_ACTION_PS_TO_OFF:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Group Clock Gating on/off
// Input Value  : enumPowerClockGatingGroup : _CLOCK_GATING_GROUP_IR ~ _CLOCK_GATING_GROUP_TYPE_C_TCPM
//                enumPowerClockGating: _CLOCK_GATING_ON(Low Power) / _CLOCK_GATING_OFF(Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupClockGating(EnumPowerClockGatingGroup enumPowerClockGatingGroup, EnumPowerClockGating enumPowerClockGating)
{
    switch(enumPowerClockGatingGroup)
    {
        case _CLOCK_GATING_GROUP_IR:

            if(enumPowerClockGating == _CLOCK_GATING_ON)
            {
                ScalerSetBit(P23_F0_IR_CLK_GAT, ~_BIT0, _BIT0)
            }
            else
            {
                ScalerSetBit(P23_F0_IR_CLK_GAT, ~_BIT0, 0x00)
            }

            break;

        case _CLOCK_GATING_GROUP_SPI_0_MASTER:

            if(enumPowerClockGating == _CLOCK_GATING_ON)
            {
                ScalerSetBit(P22_A2_SPI_MODULE_CTRL, ~(_BIT1 | _BIT0), _BIT1)
            }
            else
            {
                ScalerSetBit(P22_A2_SPI_MODULE_CTRL, ~(_BIT1 | _BIT0), 0x00)
            }

            break;

        case _CLOCK_GATING_GROUP_SPI_1_MASTER:

            if(enumPowerClockGating == _CLOCK_GATING_ON)
            {
                ScalerSetBit(P48_A2_SPI_MODULE_CTRL, ~(_BIT1 | _BIT0), _BIT1)
            }
            else
            {
                ScalerSetBit(P48_A2_SPI_MODULE_CTRL, ~(_BIT1 | _BIT0), 0x00)
            }

            break;

        case _CLOCK_GATING_GROUP_SPI_2_MASTER:

            if(enumPowerClockGating == _CLOCK_GATING_ON)
            {
                ScalerSetBit(P4A_A2_SPI_MODULE_CTRL, ~(_BIT1 | _BIT0), _BIT1)
            }
            else
            {
                ScalerSetBit(P4A_A2_SPI_MODULE_CTRL, ~(_BIT1 | _BIT0), 0x00)
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Group Clock Gating on/off Status
// Input Value  : enumPowerClockGatingGroup : _CLOCK_GATING_GROUP_IR ~ _CLOCK_GATING_GROUP_TYPE_C_TCPM
// Output Value : enumPowerClockGating: _CLOCK_GATING_ON / _CLOCK_GATING_OFF
//--------------------------------------------------
EnumPowerClockGating ScalerPowerGroupGetClockGatingStatus(EnumPowerClockGatingGroup enumPowerClockGatingGroup)
{
    switch(enumPowerClockGatingGroup)
    {
        case _CLOCK_GATING_GROUP_IR:

            if(ScalerGetBit(P23_F0_IR_CLK_GAT, _BIT0) == _BIT0)
            {
                return _CLOCK_GATING_ON;
            }
            else
            {
                return _CLOCK_GATING_OFF;
            }

            break;

        case _CLOCK_GATING_GROUP_SPI_0_MASTER:

            if(ScalerGetBit(P22_A2_SPI_MODULE_CTRL, _BIT1) == _BIT1)
            {
                return _CLOCK_GATING_ON;
            }
            else
            {
                return _CLOCK_GATING_OFF;
            }

            break;

        case _CLOCK_GATING_GROUP_SPI_1_MASTER:

            if(ScalerGetBit(P48_A2_SPI_MODULE_CTRL, _BIT1) == _BIT1)
            {
                return _CLOCK_GATING_ON;
            }
            else
            {
                return _CLOCK_GATING_OFF;
            }

            break;

        case _CLOCK_GATING_GROUP_SPI_2_MASTER:

            if(ScalerGetBit(P4A_A2_SPI_MODULE_CTRL, _BIT1) == _BIT1)
            {
                return _CLOCK_GATING_ON;
            }
            else
            {
                return _CLOCK_GATING_OFF;
            }

            break;

        default:

            break;
    }

    return _CLOCK_GATING_ON;
}

//--------------------------------------------------
// Description  : Group Power Clock Gating when AC ON
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupClockGatingACOnSetting(void)
{
    BYTE ucIndex = 0x00;
    BYTE ucClockGatingGroup = 0x00;

    // Return when power domain force enable
    if(ScalerPowerDomainEnableStatus() == _TRUE)
    {
        return;
    }

    // Scanning all clock gating domain
    for(ucClockGatingGroup = 0; ucClockGatingGroup < (sizeof(tGroupPowerClockGating) / sizeof(tGroupPowerClockGating[0])); ucClockGatingGroup++)
    {
        for(ucIndex = 0; ucIndex < tGroupPowerClockGating[ucClockGatingGroup].ucMaxSize; ucIndex++)
        {
            EnumPowerClockGatingGroup enumPowerClockGatingGroup = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].enumPowerClockGatingGroup;
            EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].b2PowerDomainSupport;

            if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
            {
                enumPowerDomainSupport = ScalerPowerGetPowerDomainClockGatingSupport(enumPowerClockGatingGroup);
            }

            // Unused clock gating domain judgment
            if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE)
            {
                ScalerPowerGroupClockGating(enumPowerClockGatingGroup, _CLOCK_GATING_ON);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Clock Gating Ready for Control
// Input Value  : enumPowerClockGatingGroup
//                enumPowerClockGating: _CLOCK_GATING_ON(Low Power) / _CLOCK_GATING_OFF(Normal Operation)
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerPowerGroupGetClockGatingControlReady(EnumPowerClockGatingGroup enumPowerClockGatingGroup, EnumPowerClockGating enumPowerClockGating)
{
    enumPowerClockGatingGroup = enumPowerClockGatingGroup;
    enumPowerClockGating = enumPowerClockGating;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Group clock gating on/off for other IP
// Input Value  : enumPowerClockGatingGroup
//                enumPowerClockGating: _CLOCK_GATING_ON(Low Power) / _CLOCK_GATING_OFF(Normal Operation)
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerPowerDomainClockGatingControl(EnumPowerClockGatingGroup enumPowerClockGatingGroup, EnumPowerClockGating enumPowerClockGating)
{
    BYTE ucIndex = 0x00;
    BYTE ucClockGatingGroup = 0x00;

    // Return when power domain force enable
    if(ScalerPowerDomainEnableStatus() == _TRUE)
    {
        return _FAIL;
    }

    // Scanning all clock gating domain
    for(ucClockGatingGroup = 0; ucClockGatingGroup < (sizeof(tGroupPowerClockGating) / sizeof(tGroupPowerClockGating[0])); ucClockGatingGroup++)
    {
        for(ucIndex = 0; ucIndex < tGroupPowerClockGating[ucClockGatingGroup].ucMaxSize; ucIndex++)
        {
            EnumPowerClockGatingGroup enumCurrentClockGatingGroup = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].enumPowerClockGatingGroup;

            // If clock gating domain matches
            if(enumCurrentClockGatingGroup == enumPowerClockGatingGroup)
            {
                EnumPowerDomainSupport enumPowerDomainSupport = tGroupPowerClockGating[ucClockGatingGroup].pstPowerClockGatingGroup[ucIndex].b2PowerDomainSupport;

                // Get Power Domain Support
                if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION)
                {
                    enumPowerDomainSupport = ScalerPowerGetPowerDomainClockGatingSupport(enumPowerClockGatingGroup);
                }

                // Unused clock gating domain judgment
                if(enumPowerDomainSupport == _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE)
                {
                    enumPowerClockGating = _CLOCK_GATING_ON;
                }

                // Check clock gating domain ready for control or not
                if(ScalerPowerGroupGetClockGatingControlReady(enumPowerClockGatingGroup, enumPowerClockGating) == _FAIL)
                {
                    return _FAIL;
                }

                // Check clock gating Status
                if(ScalerPowerGroupGetClockGatingStatus(enumPowerClockGatingGroup) == enumPowerClockGating)
                {
                    return _SUCCESS;
                }

                // Clock Gating Control
                ScalerPowerGroupClockGating(enumPowerClockGatingGroup, enumPowerClockGating);

                return _SUCCESS;
            }
        }
    }

    return _FAIL;
}

