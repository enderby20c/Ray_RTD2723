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
// ID Code      : ScalerTypeCAdc_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeCAdc/ScalerTypeCAdc.h"




#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Interrupt Handler For TypeC Power
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcIntHandler_EXINT0(void)
{
    // ===============================
    // Local Power INT Handler
    // ===============================
#if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)
    ScalerTypeCAdcLocalPowerIntHandler_EXINT0();
#endif

    // ===============================
    // Type-C 0 Vbus Handler
    // ===============================
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)

    // -------------------------------
    // OVP/UVP INT Handler
    // -------------------------------
#if((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
    // Check Comparator INT Flag
    if(ScalerTypeCAdcInOutCompIntCheck_EXINT0(_TYPE_C_CHANNEL_0_VMON) == _TRUE)
    {
#if(_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON)
        if(ScalerTypeC0PmicGetFwOvpUvpCheckFlag_EXINT0() == _TRUE)
        {
            ScalerTypeC0PmicOvpUvpIntHandler_EXINT0();
        }
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
        if(ScalerTypeC0PmicSic437aGetVbus5VCheckFlag_EXINT0() == _TRUE)
        {
            // Disable INT
            ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_0_VMON, _DISABLE);
            ScalerTypeC0PmicSic437aClrVbus5VCheckFlag_EXINT0();

            // [Eizo] SIC437A Customized Power Control : Vbus 5V Check
            ScalerTypeC0PmicSic437aVbusCheckProc_EXINT0(ScalerTypeC0PmicSic437aVbus5VReadyProc_EXINT0(ScalerTypeC0PdGetPowerRole_EXINT0()));
        }
        else if(ScalerTypeC0PmicSic437aGetVbus0VCheckFlag_EXINT0() == _TRUE)
        {
            // Disable INT
            ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_0_VMON, _DISABLE);
            ScalerTypeC0PmicSic437aClrVbus0VCheckFlag_EXINT0();

            // [Eizo] SIC437A Customized Power Control : Vbus 0V Check
            ScalerTypeC0PmicSic437aVbus0VReadyProc_EXINT0(ScalerTypeC0PdGetPowerRole_EXINT0());
        }
#endif
    }
#endif

    // -------------------------------
    // OCP INT Handler
    // -------------------------------
#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    ScalerTypeC0PmicOcpIntHandler_EXINT0();
#endif

#endif // End of #if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)

    // -------------------------------
    // PD INT Handler
    // -------------------------------
    // Check Type-C 0
#if((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3))
    // 5Bit LS_ADC Vbus On IRQ/IRQ_EN
    if(ScalerGetBit_EXINT(P7F_C3_ADC_VBUS_INT_5B, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
#else
    if((ScalerGetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)) == (_BIT0 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)) &&
       (ScalerGetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, (_BIT0 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)) == (_BIT0 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)))
#endif
    {   // Type-C 0 Vbus On Interrupt

        // Write 1 Clear Vbus On IRQ and Disable IRQ_EN
        ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_0_VMON, _ON, _DISABLE);

        // DRP Try Src FW Solution : When Detect Vbus 5V After tCCDebounce, Set HW State to Attached.SNK
        if(ScalerTypeC0CcGetTryWaitSNKState_EXINT0() == _TRUE)
        {
            ScalerTypeC0CcFWModeTrySrcAttached_EXINT0();
        }
        else if(ScalerTypeC0PdGetHardRstPowerOff_EXINT0() == _TRUE)
        {
            if(GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC)
            {
                ScalerTypeC0PdAttachedSetting_EXINT0(_PD_SRC_START_UP);
            }
            else
            {
                // Adjust Unattch Vth to 3.67V (Unit:10mV)
                ScalerTypeCAdcUnattachVthAdjust_EXINT0(_TYPE_C_CHANNEL_0_VMON, 500);

                ScalerTypeC0PdAttachedSetting_EXINT0(_PD_SNK_START_UP);

#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
                // Update Vbus Power Info to Support Sink OVP/UVP
                ScalerTypeC0PmicSetting_EXINT0(_ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_CHECK_SUPPORT == _ON))
                // Start PMIC Protection
                ScalerTypeC0PmicProtectStart_EXINT0(_TYPE_C_POWER_SNK);
#endif
            }
        }
    }

#if((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3))
    // 5Bit LS_ADC Vbus Off IRQ/IRQ_EN
    if(ScalerGetBit_EXINT(P7F_C3_ADC_VBUS_INT_5B, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
#else
    if((ScalerGetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)) == (_BIT4 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)) &&
       (ScalerGetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, (_BIT4 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)) == (_BIT4 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)))
#endif
    {   // Type-C 0 Vbus Off Interrupt

        // Write 1 Clear Vbus Off IRQ and Disable IRQ_EN
        ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_0_VMON, _OFF, _DISABLE);

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
        if(ScalerTypeC0CcGetHWState_EXINT0() == _TYPE_C_CC_HW_FSM_ATTACHED_SNK)
        {
            // Enable Vbus Detection For CC HW to Detect Unattach Event
            ScalerTypeC0CcVbusDetCtrl_EXINT0(_ENABLE);
        }
#endif
    }
#endif // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)


    // ===============================
    // Type-C 1 Vbus Handler
    // ===============================
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)

    // -------------------------------
    // OVP/UVP INT Handler
    // -------------------------------
#if((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
    // Check Comparator INT Flag
    if(ScalerTypeCAdcInOutCompIntCheck_EXINT0(_TYPE_C_CHANNEL_1_VMON) == _TRUE)
    {
#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
        if(ScalerTypeC1PmicGetFwOvpUvpCheckFlag_EXINT0() == _TRUE)
        {
            ScalerTypeC1PmicOvpUvpIntHandler_EXINT0();
        }
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
        if(ScalerTypeC1PmicSic437aGetVbus5VCheckFlag_EXINT0() == _TRUE)
        {
            // Disable INT
            ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _DISABLE);
            ScalerTypeC1PmicSic437aClrVbus5VCheckFlag_EXINT0();

            // [Eizo] SIC437A Customized Power Control : Vbus 5V Check
            ScalerTypeC1PmicSic437aVbusCheckProc_EXINT0(ScalerTypeC1PmicSic437aVbus5VReadyProc_EXINT0(ScalerTypeC1PdGetPowerRole_EXINT0()));
        }
        else if(ScalerTypeC1PmicSic437aGetVbus0VCheckFlag_EXINT0() == _TRUE)
        {
            // Disable INT
            ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _DISABLE);
            ScalerTypeC1PmicSic437aClrVbus0VCheckFlag_EXINT0();

            // [Eizo] SIC437A Customized Power Control : Vbus 0V Check
            ScalerTypeC1PmicSic437aVbus0VReadyProc_EXINT0(ScalerTypeC1PdGetPowerRole_EXINT0());
        }
#endif
    }
#endif

    // -------------------------------
    // OCP INT Handler
    // -------------------------------
#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    ScalerTypeC1PmicOcpIntHandler_EXINT0();
#endif

#endif // End of #if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)

    // -------------------------------
    // PD INT Handler
    // -------------------------------
    // Check Type-C 1
    if((ScalerGetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)) == (_BIT0 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)) &&
       (ScalerGetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, (_BIT0 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)) == (_BIT0 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)))
    {   // Type-C 1 Vbus On Interrupt

        // Write 1 Clear Vbus On IRQ and Disable IRQ_EN
        ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ON, _DISABLE);

        // DRP Try Src FW Solution : When Detect Vbus 5V After tCCDebounce, Set HW State to Attached.SNK
        if(ScalerTypeC1CcGetTryWaitSNKState_EXINT0() == _TRUE)
        {
            ScalerTypeC1CcFWModeTrySrcAttached_EXINT0();
        }
        else if(ScalerTypeC1PdGetHardRstPowerOff_EXINT0() == _TRUE)
        {
            if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
            {
                ScalerTypeC1PdAttachedSetting_EXINT0(_PD_SRC_START_UP);
            }
            else
            {
                // Adjust Unattch Vth to 3.67V (Unit:10mV)
                ScalerTypeCAdcUnattachVthAdjust_EXINT0(_TYPE_C_CHANNEL_1_VMON, 500);

                ScalerTypeC1PdAttachedSetting_EXINT0(_PD_SNK_START_UP);

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                // Update Vbus Power Info to Support Sink OVP/UVP
                ScalerTypeC1PmicSetting_EXINT0(_ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON))
                // Start PMIC Protection
                ScalerTypeC1PmicProtectStart_EXINT0(_TYPE_C_POWER_SNK);
#endif
            }
        }
    }

    if((ScalerGetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)) == (_BIT4 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)) &&
       (ScalerGetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, (_BIT4 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)) == (_BIT4 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)))
    {   // Type-C 1 Vbus Off Interrupt

        // Write 1 Clear Vbus Off IRQ and Disable IRQ_EN
        ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, _DISABLE);
    }
#endif // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
}

//--------------------------------------------------
// Description  : Get Local Power (Adaptor or Power Board) Status
// Input Value  : None
// Output Value : EnumTypeCLocalPowerExist (_TYPE_C_LOCAL_POWER_NOT_EXIST / _TYPE_C_LOCAL_POWER_EXIST)
//--------------------------------------------------
EnumTypeCLocalPowerExist ScalerTypeCAdcGetLocPowExist_EXINT0(void)
{
    return GET_TYPE_C_LOC_PW_EXIST();
}

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)
//--------------------------------------------------
// Description  : Interrupt Handler For TypeC Power
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLocalPowerIntHandler_EXINT0(void)
{
#if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))
    // Check Local Power
    if((ScalerGetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << _LOCAL_POWER_VBUS_ADC_CHANNEL)) == (_BIT4 << _LOCAL_POWER_VBUS_ADC_CHANNEL)) &&
       (ScalerGetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, (_BIT4 << _LOCAL_POWER_VBUS_ADC_CHANNEL)) == (_BIT4 << _LOCAL_POWER_VBUS_ADC_CHANNEL)))
    {
        // Local Power Off Interrupt
    }

    if((ScalerGetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << _LOCAL_POWER_VBUS_ADC_CHANNEL)) == (_BIT0 << _LOCAL_POWER_VBUS_ADC_CHANNEL)) &&
       (ScalerGetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, (_BIT0 << _LOCAL_POWER_VBUS_ADC_CHANNEL)) == (_BIT0 << _LOCAL_POWER_VBUS_ADC_CHANNEL)))
    {
        // Local Power On Interrupt
    }

#else
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3))
    // Check Local Power
    if((ScalerGetBit_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT4 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))) == (_BIT4 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))) &&
       (ScalerGetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, (_BIT4 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))) == (_BIT4 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))))
    {
        // Local Power Off Interrupt
    }

    if((ScalerGetBit_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT0 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))) == (_BIT0 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))) &&
       (ScalerGetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, (_BIT0 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))) == (_BIT0 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))))
    {
        // Local Power On Interrupt
    }
#endif // End of #if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3))
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#endif // End of #if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))
}
#endif // End of #if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)

//--------------------------------------------------
// Description  : Correction Raw Data to Ideal Data
// Input Value  : ADC_Code (0 ~ 1024)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcCorrectionToIdealData_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usRawData)
{
    DWORD ulResult = (DWORD)(usRawData);
    DWORD ulAx = 0;
    DWORD ulB = 0;
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:

            ulAx = (DWORD)(g_stTypeCAdcTrimming.usSlop) * ulResult / 1000;
            ulB = g_stTypeCAdcTrimming.ucOffset;

            // check offset is positive or negative
            if(g_stTypeCAdcTrimming.b1Sign == 0x01)
            {
                if(ulAx > ulB)
                {
                    ulResult = ((ulAx - ulB) * 512 / 1000);
                }
                else
                {
                    ulResult = 0;
                }
            }
            else
            {
                ulResult = ((ulAx + ulB) * 512 / 1000);
            }

            return (WORD)ulResult;

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return (WORD)ulResult;

            break;
#endif

        default:
            break;
    }

    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcCorrectionToRawData_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usIdealVoltage)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            return ScalerTypeCAdc10BitAdcCorrectionToRawData_EXINT0(usIdealVoltage);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return ScalerTypeCAdcLsAdcCorrectionToRawData_EXINT0(usIdealVoltage);

            break;
#endif

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            return ScalerTypeCAdcLsAdcCorrectionToRawData_EXINT0(usIdealVoltage);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)


        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Reset ADC UFP Vbus Channel (ch1/2) Threshold to Default Value and Disable IRQs
// Input Value  : enumTypeCIndex: _EMB_TYPE_C_0 / _EMB_TYPE_C_1
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcUnattachReset_EXINT0(EnumTypeCEmbeddedList enumTypeCIndex)
{
    if(enumTypeCIndex == _EMB_TYPE_C_0)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // Reset Local Power Digital Comparator On/Off Detection Threshold to 4.6V
        ScalerTypeCAdcOnOffCompIntSetting_EXINT0(_TYPE_C_CHANNEL_0_VMON, _ON, GET_TYPE_C_0_5V_LOW_BND());

        // [WS116] Lecroy TD.4.7.2 Try.SNK DRP Connect DRP Test, We shall not Check vSafe0V(0.8V) from Unattached.SRC to AttachWait.SRC
        // HW Solution, Directly Use Optional Bit [0x6637[1]/0x6C37[1]] to Disable Checking vSafe0V(0.8V)
        ScalerTypeCAdcOnOffCompIntSetting_EXINT0(_TYPE_C_CHANNEL_0_VMON, _OFF, GET_TYPE_C_0_0V_UP_BND());
#endif
    }
    else if(enumTypeCIndex == _EMB_TYPE_C_1)
    {
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // Reset Local Power Digital Comparator On/Off Detection Threshold to 4.6V
        ScalerTypeCAdcOnOffCompIntSetting_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ON, GET_TYPE_C_1_5V_LOW_BND());

        // [WS116] Lecroy TD.4.7.2 Try.SNK DRP Connect DRP Test, We shall not Check vSafe0V(0.8V) from Unattached.SRC to AttachWait.SRC
        // HW Solution, Directly Use Optional Bit [0x6637[1]/0x6C37[1]] to Disable Checking vSafe0V(0.8V)
        ScalerTypeCAdcOnOffCompIntSetting_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, GET_TYPE_C_1_0V_UP_BND());
#endif
    }
}

//--------------------------------------------------
// Description  : Set Vbus Threshold When Attached
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3 (_TYPE_C_DFP_VMON)
//                usVoltage : Negotiated Voltage in 10mV
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcUnattachVthAdjust_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usVoltage)
{
    // Sink Unattach Voltage "Refer to CC Spec Table 4-3" (Unit:10mV)
    if(usVoltage == 500)
    {
        // When PD Contract = 5V or No PD : Use 3.67V (367 * 10mV)
        // Adjust Sink Unattach Vth (usVoltage * 10 / 100 = usVoltage / 10)
        // TD 4.5.4 : Adjust Threshold to ((3.67V + 0.8V) / 2 = 2.24V) Lower than 3.67V to Cover Unexpected Unattach Caused by Tester Vbus Undershoot and IC Variation in ADC Detection. (MM1AE-4460)
        usVoltage = ScalerTypeCAdcCorrectionToRawData_EXINT0(enumChannel, 22);
    }
    else
    {
        // When PD Contract Above 5V : [(Vnew * 0.95) - 1250mV] * 0.9
        // Adjust Sink Unattach Vth (usVoltage * 10 / 100 = usVoltage / 10)
        usVoltage = ScalerTypeCAdcCorrectionToRawData_EXINT0(enumChannel, (((usVoltage * 19 / 20) - 125) * 9 / 10) / 10);
    }

    // Adjust Sink Unattach Vth
    ScalerTypeCAdcOnOffCompIntSetting_EXINT0(enumChannel, _ON, usVoltage);

    // Only Need to Adjust Vbus_On_Thr(Vbus Detect) for SNK CC HW FSM When [0x6634[2]/0x6C34[2]]=1(Vbus Detect has 2 Threshold)
    // ScalerTypeCAdcOnOffCompIntSetting_EXINT0(enumChannel, _OFF, usVoltage);
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcOnOffCompIntControl_EXINT0(EnumTypeCAdcChannel enumChannel, bit bType, bit bAction)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcOnOffCompIntControl_EXINT0((Enum10BitAdcChannel)enumChannel, bType, bAction);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            ScalerTypeCAdcLsAdcOnOffCompIntControl_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bType, bAction);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcOnOffCompIntSetting_EXINT0(EnumTypeCAdcChannel enumChannel, bit bType, WORD usThreshold)
{
    BYTE ucAdcMapping = enumChannel;

    // Clip Threshold to Valid Value (Not More than 10-bit)
    usThreshold = usThreshold & (0x03FF);

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcOnOffCompIntSetting_EXINT0((Enum10BitAdcChannel)enumChannel, bType, usThreshold);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            ScalerTypeCAdcLsAdcOnOffCompIntSetting_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bType, usThreshold);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        default:
            break;
    }
}

#if(((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcInOutCompIntControl_EXINT0(EnumTypeCAdcChannel enumChannel, bit bAction)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
#if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcInOutCompIntControl_EXINT0((Enum10BitAdcChannel)enumChannel, bAction);

            break;

#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            ScalerTypeCAdcLsAdcInOutCompIntControl_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0), bAction);

            break;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3:

            ScalerTypeCAdcLsAdcInOutCompIntControl_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bAction);

            break;
#endif

#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcInOutCompIntSetting_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
#if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcInOutCompIntSetting_EXINT0((Enum10BitAdcChannel)enumChannel, usHigh, usLow, bRange);

            break;

#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            ScalerTypeCAdcLsAdcInOutCompIntSetting_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0), usHigh, usLow, bRange);

            break;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3:

            ScalerTypeCAdcLsAdcInOutCompIntSetting_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), usHigh, usLow, bRange);

            break;
#endif

#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ADC INT Check
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCAdcInOutCompIntCheck_EXINT0(EnumTypeCAdcChannel enumChannel)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
#if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            return ScalerTypeCAdc10BitAdcInOutCompIntCheck_EXINT0((Enum10BitAdcChannel)enumChannel);

            break;

#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return ScalerTypeCAdcLsAdcInOutCompIntCheck_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0));

            break;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3:

            return ScalerTypeCAdcLsAdcInOutCompIntCheck_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0));

            break;
#endif

#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        default:
            break;
    }

    return _FALSE;
}
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data for 10B SAR_ADC
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdc10BitAdcCorrectionToRawData_EXINT0(WORD usIdealVoltage)
{
    DWORD ulCorrectionCompThr = (DWORD)usIdealVoltage;

    // Transition V to mV (*100)
    // Transition Voltage to ADC input domain
    ulCorrectionCompThr = ulCorrectionCompThr * 100 / _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO;

    // Ident offset is positive or negative
    if(g_stTypeCAdcTrimming.b1Sign == 0x01)
    {
        ulCorrectionCompThr = (ulCorrectionCompThr + g_stTypeCAdcTrimming.ucOffset) * 1000 / g_stTypeCAdcTrimming.usSlop;
    }
    else
    {
        if(ulCorrectionCompThr > g_stTypeCAdcTrimming.ucOffset)
        {
            ulCorrectionCompThr = (ulCorrectionCompThr - g_stTypeCAdcTrimming.ucOffset) * 1000 / g_stTypeCAdcTrimming.usSlop;
        }
        else
        {
            ulCorrectionCompThr = (ulCorrectionCompThr - 0) * 1000 / 1953;
        }
    }

    return (WORD)ulCorrectionCompThr;
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control for 10B SAR_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcOnOffCompIntControl_EXINT0(Enum10BitAdcChannel enumChannel, bit bType, bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(bType == _ON)
        {
            ScalerSetByte_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
        }
        else
        {
            ScalerSetByte_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
        }
    }
    else
    {
        if(bType == _ON)
        {
            ScalerSetByte_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), 0x00);
        }
        else
        {
            ScalerSetByte_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting for 10B SAR_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcOnOffCompIntSetting_EXINT0(Enum10BitAdcChannel enumChannel, bit bType, WORD usThreshold)
{
    if(bType == _ON)
    {
        // [0x7F40-41 + ucChannel*2] A0/A1/A2 Vbus On Comparator Threshold
        // [0x7F40] = adc_a0_vbus_on_thr[9:2] = usThreshold[9:2]
        // [0x7F41] = adc_a0_vbus_on_thr[1:0] = usThreshold[1:0]
        ScalerSetByte_EXINT(P7F_40_10B_ADC_A0_VBUS_ON_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit_EXINT(P7F_41_10B_ADC_A0_VBUS_ON_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
    else
    {
        // [0x7F48-49 + ucChannel*2] A0/A2/A4 Vbus Off Comparator Threshold
        // [0x7F48] = adc_a0_vbus_off_thr[9:2] = ucValue[9:2]
        // [0x7F49] = adc_a0_vbus_off_thr[1:0] = ucValue[1:0]
        ScalerSetByte_EXINT(P7F_48_10B_ADC_A0_VBUS_OFF_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit_EXINT(P7F_49_10B_ADC_A0_VBUS_OFF_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
}

#if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntControl_EXINT0(Enum10BitAdcChannel enumChannel, bit bAction)
{
    // Clear IRQ Flag
    ScalerTypeCAdc10BitAdcInOutCompIntClearFlag_EXINT0(enumChannel);

    // Control Judgment
    if(bAction == _ENABLE)
    {
        // [0x7F1B] Enable Channel INT
        ScalerSetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }
    else
    {
        // [0x7F1B] Disable Channel INT
        ScalerSetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), 0x00);
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntSetting_EXINT0(Enum10BitAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    // [0x7F1C] Set INT Triggered Condition (INT Triggered when IN/OUT of Range)
    if(bRange == _TYPE_C_ADC_WITHIN_RANGE)
    {
        ScalerSetBit_EXINT(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }

    // Clip High/Low Threshold to Valid Range
    usHigh = ((usHigh >= 0x03FF) ? 0x03FF : (usHigh & 0x03FF));
    usLow = ((usLow >= 0x03FC) ? 0x03FC : (usLow & 0x03FF));

    // [0x7F20-29] Set High Threshold
    // [0x7F20] adc_a0_hi_thr[9:2] = ucHigh[9:2]
    // [0x7F21] adc_a0_hi_thr[1:0] = ucHigh[1:0]
    ScalerSetByte_EXINT((P7F_20_10B_ADC_A0_HIGH_THR1 + (enumChannel * 2)), (BYTE)(usHigh >> 2));
    ScalerSetBit_EXINT((P7F_21_10B_ADC_A0_HIGH_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usHigh & (_BIT1 | _BIT0)));

    // [0x7F30-39] Set Low Threshold
    // [0x7F30] adc_a0_low_thr[9:2] = ucLow[9:2]
    // [0x7F31] adc_a0_low_thr[1:0] = ucLow[1:0]
    ScalerSetByte_EXINT((P7F_30_10B_ADC_A0_LOW_THR1 + (enumChannel * 2)), (BYTE)(usLow >> 2));
    ScalerSetBit_EXINT((P7F_31_10B_ADC_A0_LOW_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usLow & (_BIT1 | _BIT0)));
}

//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntClearFlag_EXINT0(Enum10BitAdcChannel enumChannel)
{
    // [0x7F1A] Clear Channel Range Detection IRQ Flag
    ScalerSetBit_EXINT(P7F_1A_10B_ADC_COMP_INT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));
}

//--------------------------------------------------
// Description  : ADC INT Check
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCAdc10BitAdcInOutCompIntCheck_EXINT0(Enum10BitAdcChannel enumChannel)
{
    return ((ScalerGetBit_EXINT(P7F_1A_10B_ADC_COMP_INT, (_BIT0 << enumChannel)) == (_BIT0 << enumChannel)) && (ScalerGetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, (_BIT0 << enumChannel)) == (_BIT0 << enumChannel)));
}
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcGetAdcOutput_EXINT0(EnumTypeCAdcChannel enumChannel)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            return ScalerTypeCAdc10BitAdcGetAdcOutput_EXINT0((Enum10BitAdcChannel)enumChannel);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return ScalerTypeCAdcLsAdcGetAdcOutput_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0));

            break;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3:

            return ScalerTypeCAdcLsAdcGetAdcOutput_EXINT0((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0));

            break;
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdc10BitAdcGetAdcOutput_EXINT0(Enum10BitAdcChannel enumChannel)
{
    DWORD ulResult = 0;

    // [0x7F02] [4:0] Write Valid Output Bit to Get New Value From ADC
    ScalerSetBit_EXINT(P7F_02_10B_ADC_OUTPUT, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));

    // Polling Valid Output Bit (will be 1 when the New Output is Put into Register [0x7F10-19])
    if(ScalerTimerPollingFlagProc_EXINT0(_ADC_OUTPUT_MAX_TIME, P7F_02_10B_ADC_OUTPUT, (_BIT0 << enumChannel), (_BIT0 << enumChannel)) == _TRUE)
    {
        BYTE ucResult_h = (ScalerGetByte_EXINT(P7F_10_10B_ADC_A0_RSLT_H + (enumChannel * 2)));
        BYTE ucResult_l = (ScalerGetByte_EXINT(P7F_11_10B_ADC_A0_RSLT_L + (enumChannel * 2))) & (_BIT1 | _BIT0);

        // usResult [9:0] = {RSLT_H[7:0] | RSLT[1:0]}
        ulResult = ((ucResult_h << 2) | (ucResult_l));
    }
    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcLsAdcGetAdcOutput_EXINT0(EnumLsAdcChannel enumChannel)
{
    DWORD ulResult = 0;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    // Transfer 5-bit ADC to 10-bit result
    ulResult = (WORD)(ScalerGetBit_EXINT(PFF_09_ADC_A0_CONVERT_RESULT + enumChannel, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3))) << 2;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    // Transfer 8-bit ADC to 10-bit result
    if(enumChannel <= _LS_ADC_0_3)
    {
        ulResult = (WORD)(ScalerGetByte_EXINT(PFD_3B_ADC_A0_CONVERT_RESULT + enumChannel)) << 2;
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ulResult = (WORD)(ScalerGetByte_EXINT(PFF_09_ADC_A0_CONVERT_RESULT + (enumChannel - _LS_ADC_1_0))) << 2;
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data for LS_ADC
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcLsAdcCorrectionToRawData_EXINT0(WORD usIdealVoltage)
{
    // ADC_Code = (usIdealVoltage / 10)(Unit:V) * (256 Code / Max Voltage)
    DWORD ulCorrectionCompThr = (DWORD)(usIdealVoltage * 256 / _LOCAL_POWER_VBUS_MAX_VOLTAGE / 10) << 2;

    return (WORD)ulCorrectionCompThr;
}

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))
//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control for LS_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcOnOffCompIntControl_EXINT0(EnumLsAdcChannel enumChannel, bit bType, bit bAction)
{
    if(enumChannel >= _LS_ADC_1_0)
    {
        return;
    }

    if(bAction == _ENABLE)
    {
        if(bType == _ON)
        {
            ScalerSetByte_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
        }
        else
        {
            ScalerSetByte_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
        }
    }
    else
    {
        if(bType == _ON)
        {
            ScalerSetByte_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), 0x00);
        }
        else
        {
            ScalerSetByte_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting for LS_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcOnOffCompIntSetting_EXINT0(EnumLsAdcChannel enumChannel, bit bType, WORD usThreshold)
{
    if(bType == _ON)
    {
        // [0x7FC4] adc_a0/a1/a2/a3_vbus_on_thr = usThreshold[9:2]
        ScalerSetByte_EXINT(P7F_C4_ADC_A0_VBUS_ON_THR + (enumChannel * 2), (BYTE)(usThreshold >> 2));
    }
    else
    {
        // [0x7FC5] adc_a0/a1/a2/a3_vbus_off_thr = usThreshold[9:2]
        ScalerSetByte_EXINT(P7F_C5_ADC_A0_VBUS_OFF_THR + (enumChannel * 2), (BYTE)(usThreshold >> 2));
    }
}
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||\
    ((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntControl_EXINT0(EnumLsAdcChannel enumChannel, bit bAction)
{
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    if(bAction == _ENABLE)
    {
        // [0xFF0E] ADC0: Clear Flag & Enable INT
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), ((_BIT4 | _BIT0) << enumChannel));
    }
    else
    {
        // [0xFF0E] ADC0: Reset Threshold
        ScalerTypeCAdcLsAdcInOutCompIntSetting_EXINT0(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

        // [0xFF0E] ADC0: Disable INT, but don't clear flag
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), 0x00);
    }

    // Clear INT Flag
    ScalerTypeCAdcLsAdcInOutCompIntClearFlag_EXINT0(enumChannel);

    // ADC Start Scan
    ScalerSetBit_EXINT(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    if(enumChannel <= _LS_ADC_0_3)
    {
        if(bAction == _ENABLE)
        {
            // [0xFD40] ADC0: Clear Flag & Enable INT
            ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), ((_BIT4 | _BIT0) << enumChannel));
        }
        else
        {
            // [0xFD40] ADC0: Reset Threshold
            ScalerTypeCAdcLsAdcInOutCompIntSetting_EXINT0(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

            // [0xFD40] ADC0: Disable INT, but don't clear flag
            ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), 0x00);
        }
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        if(bAction == _ENABLE)
        {
            // [0xFF0E] ADC0: Clear Flag & Enable INT
            ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (enumChannel - _LS_ADC_1_0))), ((_BIT4 | _BIT0) << (enumChannel - _LS_ADC_1_0)));
        }
        else
        {
            // [0xFF0E] ADC0: Reset Threshold
            ScalerTypeCAdcLsAdcInOutCompIntSetting_EXINT0(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

            // [0xFF0E] ADC0: Disable INT, but don't clear flag
            ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (enumChannel - _LS_ADC_1_0))), 0x00);
        }
    }

    // Clear INT Flag
    ScalerTypeCAdcLsAdcInOutCompIntClearFlag_EXINT0(enumChannel);

    // ADC Start Scan
    ScalerSetBit_EXINT(PFD_3A_ADC_ACONTROL, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntSetting_EXINT0(EnumLsAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    // Must be In-Range
    bRange = bRange;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 5;
    usHigh = ((usHigh >= 0x001F) ? 0x001F : (usHigh & 0x001F));

    usLow = usLow >> 5;
    usLow = ((usLow >= 0x001E) ? 0x001E : (usLow & 0x001F));

    // Set High/Low Threshold for 5-Bit LS_ADC
    ScalerSetByte_EXINT((PFF_0F_ADC0_THRESHOLD_H + (enumChannel * 2)), (BYTE)(usHigh << 3));
    ScalerSetByte_EXINT((PFF_10_ADC0_THRESHOLD_L + (enumChannel * 2)), (BYTE)(usLow << 3));

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 2;
    usHigh = ((usHigh >= 0x00FF) ? 0x00FF : (usHigh & 0x00FF));

    usLow = usLow >> 2;
    usLow = ((usLow >= 0x00FE) ? 0x00FE : (usLow & 0x00FF));

    // Set High/Low Threshold for 8-Bit LS_ADC
    if(enumChannel <= _LS_ADC_0_3)
    {
        ScalerSetByte_EXINT((PFD_F7_ADC0_THRESHOLD_H + (enumChannel * 2)), (BYTE)(usHigh));
        ScalerSetByte_EXINT((PFD_F8_ADC0_THRESHOLD_L + (enumChannel * 2)), (BYTE)(usLow));
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ScalerSetByte_EXINT((PFF_0F_ADC0_THRESHOLD_H + ((enumChannel - _LS_ADC_1_0) * 2)), (BYTE)(usHigh));
        ScalerSetByte_EXINT((PFF_10_ADC0_THRESHOLD_L + ((enumChannel - _LS_ADC_1_0) * 2)), (BYTE)(usLow));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntClearFlag_EXINT0(EnumLsAdcChannel enumChannel)
{
    // Clear Flag
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    if(enumChannel <= _LS_ADC_0_3)
    {
        ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << (enumChannel - _LS_ADC_1_0)), (_BIT4 << (enumChannel - _LS_ADC_1_0)));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : ADC INT Check
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCAdcLsAdcInOutCompIntCheck_EXINT0(EnumLsAdcChannel enumChannel)
{
    // Check INT Flag
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    BYTE ucValue = ScalerGetByte_EXINT(PFF_0E_AUTO_MODE_CTRL01) >> enumChannel;

    return ((ucValue & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0));

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    if(enumChannel <= _LS_ADC_0_3)
    {
        BYTE ucValue = ScalerGetByte_EXINT(PFD_40_AUTO_MODE_CTRL01) >> enumChannel;

        return ((ucValue & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0));
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        BYTE ucValue = ScalerGetByte_EXINT(PFF_0E_AUTO_MODE_CTRL01) >> (enumChannel - _LS_ADC_1_0);

        return ((ucValue & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    return _FALSE;
}
#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))

