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
// ID Code      : ScalerGlobal_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GLOBAL_EXINT0__

#include "ScalerFunctionInclude.h"
#include "Global/ScalerGlobal.h"



//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT) || (_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_IRQ_BACKGROUND))
//--------------------------------------------------
// Description  : Check if IHV error and fifo under/ overflow, turn off backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalPreventGarbageByBacklight_EXINT0(void)
{
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        BYTE ucIHVErrorOffset = 0x06;
        BYTE ucFifoErrorOffset = 0x02;

        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            ucIHVErrorOffset = 0x0C;
            ucFifoErrorOffset = 0x04;
        }

        if(((ScalerGetBit_EXINT(PC0_04_M1_OVF_UDF_CTRL, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(PC0_04_M1_OVF_UDF_CTRL, (_BIT5 | _BIT4)) != 0x00)) ||
           ((ScalerGetBit_EXINT(P0_A1_M1_IRQ_FLAG, (_BIT4 | _BIT3)) != 0x00) && (ScalerGetBit_EXINT(P0_A0_M1_IRQ_WD_CTRL, _BIT4) == _BIT4)) ||
           ((ScalerGetBit_EXINT((PC0_04_M1_OVF_UDF_CTRL + ucFifoErrorOffset), (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT((PC0_04_M1_OVF_UDF_CTRL + ucFifoErrorOffset), (_BIT5 | _BIT4)) != 0x00)) ||
           ((ScalerGetBit_EXINT((P0_A1_M1_IRQ_FLAG + ucIHVErrorOffset), (_BIT4 | _BIT3)) != 0x00) && (ScalerGetBit_EXINT((P0_A0_M1_IRQ_WD_CTRL + ucIHVErrorOffset), _BIT4) == _BIT4)))
        {
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
#if(_PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE == _PANEL_OLED_AC_DET_CTRL_WITHOUT_SEQ)
            PCB_BACKLIGHT_POWER_PIN_EXINT(_LIGHT_CONTROL_OFF);
#endif
#endif

            // Set free run mode
            ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

            // Set force to background
            ScalerSetBit_EXINT(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(P80_AB_BG_COLOR_CONTROL_R2, ~_BIT7, _BIT7);

            // Disable buffer underflow/overflow IRQ
            ScalerSetBit_EXINT(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT((PC0_04_M1_OVF_UDF_CTRL + ucFifoErrorOffset), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable Input HVsync error IRQ
            ScalerSetBit_EXINT(P0_A0_M1_IRQ_WD_CTRL, ~(_BIT4), 0x00);
            ScalerSetBit_EXINT((P0_A0_M1_IRQ_WD_CTRL + ucIHVErrorOffset), ~(_BIT4), 0x00);
        }
    }
    else
#endif
    {
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            if(((ScalerGetBit_EXINT(PC0_04_M1_OVF_UDF_CTRL, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(PC0_04_M1_OVF_UDF_CTRL, (_BIT5 | _BIT4)) != 0x00)) ||
               ((ScalerGetBit_EXINT(P0_A1_M1_IRQ_FLAG, (_BIT4 | _BIT3)) != 0x00) && (ScalerGetBit_EXINT(P0_A0_M1_IRQ_WD_CTRL, _BIT4) == _BIT4)))
            {
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
#if(_PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE == _PANEL_OLED_AC_DET_CTRL_WITHOUT_SEQ)
                PCB_BACKLIGHT_POWER_PIN_EXINT(_LIGHT_CONTROL_OFF);
#endif
#endif

                // Set free run mode
                ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                // Set force to background
                ScalerSetBit_EXINT(P80_A1_BG_COLOR_CONTROL_R1, ~_BIT7, _BIT7);

                // Disable buffer underflow/overflow IRQ
                ScalerSetBit_EXINT(PC0_04_M1_OVF_UDF_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Disable Input HVsync error IRQ
                ScalerSetBit_EXINT(P0_A0_M1_IRQ_WD_CTRL, ~(_BIT4), 0x00);
            }
        }
    }
}
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
//--------------------------------------------------
// Description  : Global Interrupt Handler for I Domain IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDomainIntHandler_EXINT0(void)
{
    BYTE ucIndex = 0;
    BYTE ucIRQPageOffset = 0;

    // IVS Event
    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        ucIRQPageOffset = GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex);

        if((ScalerGetBit_EXINT(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, _BIT7) == _BIT7))
        {
            // Record IVS Event
            SET_EVENT_IVS_INT(ucIndex, _TRUE);

            // Clear IVS IRQ Flag
            ScalerSetBit_EXINT(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);
        }
    }

    // IEN_START Event
    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        ucIRQPageOffset = GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex);

        if((ScalerGetBit_EXINT(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, _BIT6) == _BIT6) &&
           (ScalerGetBit_EXINT(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, _BIT6) == _BIT6))
        {
            // Record IEN_START Event
            SET_EVENT_IEN_START_INT(ucIndex, _TRUE);

            // Clear IEN_START IRQ Flag
            ScalerSetBit_EXINT(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT6);

#if(_DM_FUNCTION == _ON)
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
            if(GET_GLOBAL_INT_DM(ucIndex) == _ENABLE)
            {
                ScalerDMIDenStartHandler_EXINT0(GET_IDOMAIN_DATA_PATH(ucIndex));
            }
#endif
#endif
        }
    }

    // IEN_STOP Event
    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        ucIRQPageOffset = GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex);

        if((ScalerGetBit_EXINT(P0_A0_M1_IRQ_WD_CTRL + ucIRQPageOffset, _BIT5) == _BIT5) &&
           (ScalerGetBit_EXINT(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, _BIT5) == _BIT5))
        {
            // Record IEN_STOP Event
            SET_EVENT_IEN_STOP_INT(ucIndex, _TRUE);

            // Clear IEN_STOP IRQ Flag
            ScalerSetBit_EXINT(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
        }
    }
}
#endif // End of #if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
//--------------------------------------------------
// Description  : Global Interrupt Handler for D Domain IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDDomainIntHandler_EXINT0(void)
{
    // DEN_START Event
    if(ScalerGetBit_EXINT(PC0_02_DDOMAIN_IRQ_WD_CTRL1, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        // Record DEN_START Event
        SET_EVENT_DEN_START_INT(_TRUE);

        // Clear DEN_START IRQ flag
        ScalerSetBit_EXINT(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT2);

#if((_OD_FUNCTION == _ON) && (_FRC_SUPPORT == _ON))
        if(GET_GLOBAL_INT_DYNAMIC_OD() == _ENABLE)
        {
            ScalerODIntHandler_EXINT0();
        }
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
        if(GET_GLOBAL_INT_LOCAL_CONTRAST() == _ENABLE)
        {
            ScalerColorLocalContrastIntHandler_EXINT0();
        }
#endif
#endif
    }

    // DEN Stop Event
    if(ScalerGetBit_EXINT(PC0_02_DDOMAIN_IRQ_WD_CTRL1, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        // Record DEN_STOP Event
        SET_EVENT_DEN_STOP_INT(_TRUE);

        // Clear DEN_STOP IRQ flag
        ScalerSetBit_EXINT(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT4);
    }

    // DVS Event
    if(ScalerGetBit_EXINT(PC0_02_DDOMAIN_IRQ_WD_CTRL1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // Clear DVS IRQ flag
        ScalerSetBit_EXINT(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT6);

#if((_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
        if(GET_GLOBAL_INT_DRR_MBR_DVS() == _ENABLE)
        {
            ScalerMbrIntHandlerDVS_EXINT0();
        }
#endif
    }

#if(_HW_DVS_TIMEOUT_IRQ_SUPPORT == _ON)
    // DVS Timeout
    if((ScalerGetBit_EXINT(PC0_02_DDOMAIN_IRQ_WD_CTRL1, _BIT0) == (_BIT0)) && (ScalerGetBit_EXINT(PC0_03_EVENT_FLAG, _BIT0) == (_BIT0)))
    {
        // Clear DVS Timeout flag
        ScalerSetBit_EXINT(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT0);
    }
#endif
}
#endif
