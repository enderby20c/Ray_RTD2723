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
// ID Code      : ScalerMbr.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MBR__

#include "ScalerFunctionInclude.h"
#include "Mbr/ScalerMbr.h"

//--------------------------------------------------
// Note Message For RTK Adv MBR Enable
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#warning "NOTE: RTK Adv MBR support is ON, Memory BW may be affected. Please check with SD!!!"
#endif
#endif

//--------------------------------------------------
// Note Message For BFI 2x + Eagle Sight
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
#if((_EAGLE_SIGHT_SUPPORT == _ON) && (_EAGLE_SIGHT_MN_FRAME_SYNC_SUPPORT == _OFF))
#warning "_EAGLE_SIGHT_MN_FRAME_SYNC_SUPPORT Should Be _ON To Support BFI + Eagle Sight"
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
WORD g_usMbrDVTotal;
EnumMbrBacklightMode g_enumMbrBacklightMode = _BACKLIGHT_MODE_CONSTANT;

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
EnumMbrDrrBacklightMode g_enumMbrDrrBacklightMode = _MBR_DRR_MODE_OFF;
WORD g_pusMbrDrrVFreq[_MBR_DRR_AVG_IVF_FRAME_CNT];
volatile WORD g_usMbrDrrSafeCount;
volatile WORD g_usMbrDrrVFreq_avg;
BYTE g_ucMbrDrrStepChangeCnt;
BYTE g_ucMbrDrrTconToggleTime;
bit g_bMbrDrrHWSupport;
#endif
#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
EnumMbrBFIKernelMode g_enumMbrBFIAvailableMode = _BFI_KERNEL_OFF;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Kernel check/overwrite backlight mode if the mode
//                doesn't even support
// Input Value  : enumBacklightMode - user MBR backlight mode
// Output Value : altered backlight mode
//--------------------------------------------------
EnumMbrBacklightMode ScalerMbrCheckBacklightMode(EnumMbrBacklightMode enumBacklightMode, EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // If DRR enable but DRR MBR not supported, use constant backlight
#if((_DRR_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _OFF))
    if(enumBacklightMode != _BACKLIGHT_MODE_CONSTANT)
    {
        if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
    }
#endif

    // If DRR MBR is selected but FW/DRR status/HW do not support, use constant backlight
    if(enumBacklightMode == _BACKLIGHT_MODE_STROBE_DRR_MBR)
    {
#if((_DRR_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
        if((ScalerDrrGetType(enumInputPort) == _DRR_NONE_TYPE) || (GET_MBR_DRR_HW_SUPPORT() == _FALSE))
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
#else
        return _BACKLIGHT_MODE_CONSTANT;
#endif
    }

    // If RTK Adv MBR is selected but FW/kernel status do not support, use constant backlight
    if(enumBacklightMode == _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR)
    {
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        if(ScalerMbrAdvanceGetRtkAdvMbrStatus() == _DISABLE)
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
#else
        return _BACKLIGHT_MODE_CONSTANT;
#endif
    }

    return enumBacklightMode;
}

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate & Set TCON Parameters for DRR MBR
// Input Value  : ucTcon - TCON Number
//                ucBacklightDuty - User OSD Backlight Duty Setting(Ratio%)
//                ucBacklightPos - User OSD Backlight Position Setting(Ratio%)
//                bLightCtrl - Backlight ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        BYTE ucIndex = 0;
        WORD usDVTotal = GET_MBR_DVTOTAL() + 1; // to prevent compensation to pop-up too early
        WORD usStrobeVWidth = (WORD)((DWORD)ucBacklightDuty * usDVTotal / 100L);
        WORD usStrobeVPos = (WORD)((DWORD)ucBacklightPos * usDVTotal / 100L); // we dont want the strobe to exceed DEN Stop

        // Toggle Setting
        WORD usDHTotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);
        WORD usDuty = (WORD)ucBacklightDuty * 10 + _DRR_MOTION_BLUR_REDUCTION_COMP_DUTY_OFFSET; // compensation fine-tuned duty
        ScalerMbrSetTconToggleSequence(ucTcon - 2, usDuty, usDHTotal);

        // Check if current input VFreq is valid for strobe mode
        // DRR MBR is enable when 1P or Eagle Sight mode, reference to MAIN region
        ScalerMeasureSetRegionIndex(_REGION_INDEX_0);
        if(GET_INPUT_TIMING_VFREQ() >= _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO)
        {
            // Compensation Setting
            ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, usDVTotal);
            ScalerTconInvEnableByIndex(ucTcon - 1, _ENABLE);
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)(ucTcon - 1), _TCON_LOGICAL_OP_AND, _ENABLE);

            // Strobe Setting
            if(ucBacklightDuty == 100)
            {
                ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
            }
            else
            {
                ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth));
            }
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTcon, _TCON_LOGICAL_OP_OR, _ENABLE);

            // Enable control
            ScalerTconEnableByIndex(ucTcon - 1, _ENABLE);
            ScalerTconEnableByIndex(ucTcon, _ENABLE);

            SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_STROBE);
        }
        else // constant mode
        {
            // Compensation Setting
            ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, 0x0000);
            ScalerTconInvEnableByIndex(ucTcon - 1, _ENABLE);
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)(ucTcon - 1), _TCON_LOGICAL_OP_AND, _ENABLE);

            // Strobe Setting
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x0000);
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTcon, _TCON_LOGICAL_OP_OR, _ENABLE);

            // Enable control
            ScalerTconEnableByIndex(ucTcon - 1, _DISABLE);
            ScalerTconEnableByIndex(ucTcon, _DISABLE);

            SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_CONSTANT);
        }

        // Enable TCON DB
        ScalerTconDBEnable(_ENABLE);

        // Reset MBR global variables
        CLR_MBR_DRR_SAFE_CNT();
        SET_MBR_DRR_VFREQ_AVG(GET_INPUT_TIMING_VFREQ());
        SET_MBR_DRR_STEP_CHG_CNT(0);
        for(ucIndex = 0; ucIndex < _MBR_DRR_AVG_IVF_FRAME_CNT; ucIndex++)
        {
            SET_MBR_DRR_VFREQ(ucIndex, GET_MBR_DRR_VFREQ_AVG());
        }
    }
    else
    {
        // Setting in _LIGHT_CONTROL_OFF case
        ScalerTconEnableByIndex(ucTcon, _DISABLE);
        SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_OFF);

        // Disable TCON DB
        ScalerTconDBEnable(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : Calculate TCON Setting for Division of Frequency
// Input Value  : enumOutputTcon - Selected TCON Number
//                usDuty - Final Output Duty Ratio (x/1000)
//                usHTotal - Current Timing HTotal
//                usHFreq - Current Timing H-frequency
//                usMaxFreq - Current Timing(DRR) Max Frequency
// Output Value : None
//--------------------------------------------------
void ScalerMbrSetTconToggleSequence(BYTE ucTconEnd, WORD usDuty, WORD usHTotal)
{
    BYTE ucToggleTimeTotal = 0;
    BYTE ucToggleTime = 0;
    BYTE ucTconStart = ucTconEnd;

    ucToggleTimeTotal = GET_MBR_DRR_TCON_TOGGLE_TIME();

    // Calculate & Set Toggle Operation Sequence
    for(ucToggleTime = 0; ucToggleTime < ucToggleTimeTotal; ucToggleTime++)
    {
        if(usDuty == 500)
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_NORMAL, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
        }
        else if(usDuty < 500)
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_AND, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
            usDuty *= 2;
        }
        else // usDuty > 50%
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_OR, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
            usDuty = 2 * (usDuty - 500);
        }
        ScalerTconAdjustByIndex(ucTconStart, 0x0000, 0x0000, 0x0000, 0x0000);
        DebugMessageScaler("MBR: ucTconStart", ucTconStart);
        ucTconStart--;
    }

    // Set the Original TCON
    ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_NORMAL, _DISABLE);
    ScalerTconAdjustByIndex(ucTconStart, 0x0000, (DWORD)usHTotal * usDuty / 1000L, 0x0000, 0x3FFF);
    ScalerTconEnableByIndex(ucTconStart, _ENABLE);
}

//--------------------------------------------------
// Description  : By step change the backlight parameters
// Input Value  : ucTcon - Output TCON number
//                enumMode - Backlight mode(change direction)
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrStepChange(BYTE ucTcon, WORD usStrobePeriod, BYTE ucDuty, BYTE ucPosition)
{
    WORD usStrobeVWidth = 0; // Backlight ON lines
    WORD usStrobeVPos = 0; // Backlight ON Position (lines)

    // Calculate parameters
    usStrobeVWidth = (WORD)((DWORD)ucDuty * usStrobePeriod / 100L);
    usStrobeVPos = (WORD)((DWORD)ucPosition * usStrobePeriod / 100L);

    // If duty = 100, then the whole backlight control signal is always high, no need to be adjusted
    if(ucDuty == 100)
    {
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        ScalerTconDBApply(_DB_APPLY_POLLING);
        return;
    }

    if(usStrobePeriod == 0) // going to constant this time
    {
        // We use TCON local enable/disable to turn on/off strobe/compensation
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x0000);
        ScalerTconEnableByIndex(ucTcon, _DISABLE);
        ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, 0x0000);
        ScalerTconEnableByIndex(ucTcon - 1, _DISABLE);
    }
    else
    {
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, usStrobeVPos + usStrobeVWidth);
        ScalerTconEnableByIndex(ucTcon, _ENABLE);
        ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, usStrobePeriod);
        ScalerTconEnableByIndex(ucTcon - 1, _ENABLE);
    }

    // Apply TCON Setting
    ScalerTconDBApply(_DB_APPLY_POLLING);
}

//--------------------------------------------------
// Description  : Adjust DRR MBR Parameters
// Input Value  : ucTcon - TCON Number
//                ucBacklightDuty - User OSD Backlight Duty Setting
//                ucBacklightPos - User OSD Backlight Position Setting
//                bLightCtrl - Backlight ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrAdjust(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        WORD usStrobeVWidth = (WORD)((DWORD)ucBacklightDuty * (GET_MBR_DVTOTAL() + 1) / 100L);
        WORD usStrobeVPos = (WORD)((DWORD)ucBacklightPos * (GET_MBR_DVTOTAL() + 1) / 100L);

        // Toggle Setting
        WORD usDHTotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);
        WORD usDuty = (WORD)ucBacklightDuty * 10 + _DRR_MOTION_BLUR_REDUCTION_COMP_DUTY_OFFSET; // compensation fine-tuned duty
        ScalerMbrSetTconToggleSequence(ucTcon - 2, usDuty, usDHTotal);

        // Adjust Strobe
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        if(ucBacklightDuty == 100)
        {
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        }
        else
        {
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth));
        }
    }
    else
    {
        ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x0000, 0x0000, 0x0000);
    }

    // Apply TCON Setting
    ScalerTconDBApply(_DB_APPLY_POLLING);
}

//--------------------------------------------------
// Description  : Disable DRR MBR unused setting
// Input Value  : ucTcon -> PCB output TCON pin
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrClearSetting(BYTE ucTcon)
{
    BYTE ucIndex = 0;

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
    // Disable interrupt to clear the shared variable
    ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_DRR_MBR_DVS, _DISABLE);
#endif
    // Disable TCON DB
    ScalerTconDBEnable(_DISABLE);

    // Reset Toggle Setting
    for(ucIndex = (ucTcon - 2 - GET_MBR_DRR_TCON_TOGGLE_TIME()); ucIndex < (ucTcon - 1); ucIndex++)
    {
        ScalerTconEnableByIndex(ucIndex, _DISABLE);
        ScalerTconAdjustByIndex(ucIndex, 0x0000, 0x0000, 0x0000, 0x0000);
        if(ucIndex >= _TCON3)
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucIndex, _TCON_TOGGLE_OP_NORMAL, _DISABLE);
        }
    }

    // Reset Compensation Setting
    ScalerTconEnableByIndex((ucTcon - 1), _DISABLE);
    ScalerTconAdjustByIndex((ucTcon - 1), 0x0000, 0x0000, 0x0000, 0x0000);
    ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)(ucTcon - 1), _TCON_LOGICAL_OP_AND, _DISABLE);
    ScalerTconInvEnableByIndex((ucTcon - 1), _DISABLE);

    // Reset Strobe Setting
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _OFF)
    ScalerTconEnableByIndex(ucTcon, _DISABLE);
    ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x0000, 0x0000, 0x0000);
#endif
    ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTcon, _TCON_LOGICAL_OP_OR, _DISABLE);

    // Reset MBR global variables
    CLR_MBR_DRR_SAFE_CNT();
    SET_MBR_DRR_VFREQ_AVG(_DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_HI);
    SET_MBR_DRR_STEP_CHG_CNT(0);
    for(ucIndex = 0; ucIndex < _MBR_DRR_AVG_IVF_FRAME_CNT; ucIndex++)
    {
        SET_MBR_DRR_VFREQ(ucIndex, _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_HI);
    }
}
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Prepare & set the necessary parameters for RTK Adv MBR
// Input Value  : ucTcon - TCON Number
//                ucBacklightDuty - User OSD Backlight Duty Setting
//                ucBacklightPos - User OSD Backlight Position Setting
//                bLightCtrl - Backlight ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerMbrRtkAdvMbrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    StructRtkAdvMbrTimingInfo stTimingInfo;

    stTimingInfo.usDclk = GET_D_CLK_FREQ();
    stTimingInfo.usHTotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);
    stTimingInfo.usVTotal = GET_MBR_DVTOTAL();
    stTimingInfo.usVFreq = GET_OUTPUT_VFREQ();

    ScalerMbrAdvanceRtkAdvMbrAdjust(&stTimingInfo, ucTcon, ucBacklightDuty, ucBacklightPos, (bLightCtrl == _LIGHT_CONTROL_ON));
}
#endif // End of #if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)


#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return if current BFI is enable
// Input Value  : None
// Output Value : BFI enable status
//--------------------------------------------------
EnumMbrBFIMode ScalerMbrGetBlackFrameInsertEnable(void)
{
    if(ScalerGetBit(P80_A0_OVERLAY_CTRL, _BIT1) == _BIT1)
    {
        return _BFI_MODE_ON;
    }
    else
    {
        return _BFI_MODE_OFF;
    }
}

//--------------------------------------------------
// Description  : Set BFI available mode from input conditions
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMbrSetBlackFrameInsertAvailableMode(void)
{
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    // check display mode available
    if(enumDisplayMode != _DISPLAY_MODE_1P)
    {
        SET_MBR_BFI_AVAILABLE_MODE(_BFI_KERNEL_OFF);
        return;
    }

    // check DRR mode
#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
    {
        SET_MBR_BFI_AVAILABLE_MODE(_BFI_KERNEL_OFF);
        return;
    }
#endif

    // check framerate
    if((GET_MDOMAIN_INPUT_VFREQ() <= _PANEL_MAX_FRAME_RATE / 2) && (GET_MDOMAIN_INPUT_VFREQ() >= _MOTION_BLUR_REDUCTION_FLICKER_IVF))
    {
        SET_MBR_BFI_AVAILABLE_MODE(_BFI_KERNEL_2X);
    }
#if(_MOTION_BLUR_REDUCTION_BFI_1_IVF_SUPPORT == _ON)
    else if((GET_MDOMAIN_INPUT_VFREQ() / 2) >= _MOTION_BLUR_REDUCTION_FLICKER_IVF)
    {
        SET_MBR_BFI_AVAILABLE_MODE(_BFI_KERNEL_1X);
    }
#endif
    else
    {
        SET_MBR_BFI_AVAILABLE_MODE(_BFI_KERNEL_OFF);
    }
}

//--------------------------------------------------
// Description  : Update BFI available mode from display conditions
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMbrUpdateBlackFrameInsertAvailableMode(void)
{
    EnumMbrBFIKernelMode enumMbrBFIKernelMode = GET_MBR_BFI_AVAILABLE_MODE();
    DebugMessageScaler("MBR: BFI Input Available Mode", enumMbrBFIKernelMode);

    // -------------------------------
    // update kernel available mode
    // -------------------------------
    // check M-domain match user setting
    if(enumMbrBFIKernelMode == _BFI_KERNEL_2X)
    {
        // if M-domain is not 1:2 MN FrameSync
        if(GET_FS_ACTIVE_INFO_DVF_SELECT() != _2_IVF)
        {
            enumMbrBFIKernelMode = _BFI_KERNEL_OFF;
            DebugMessageScaler("MBR: BFI Available Mode by FrameSync Mode", enumMbrBFIKernelMode);
        }
    }
#if(_MOTION_BLUR_REDUCTION_BFI_1_IVF_SUPPORT == _ON)
    else if(enumMbrBFIKernelMode == _BFI_KERNEL_1X)
    {
        // if M-domain is not FrameSync
        if(GET_FS_ACTIVE_INFO_DVF_SELECT() != _1_IVF)
        {
            enumMbrBFIKernelMode = _BFI_KERNEL_OFF;
            DebugMessageScaler("MBR: BFI Available Mode by FrameSync Mode", enumMbrBFIKernelMode);
        }
    }
#endif

    // update
    SET_MBR_BFI_AVAILABLE_MODE(enumMbrBFIKernelMode);
}
#endif