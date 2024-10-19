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
// ID Code      : ScalerDisplayVboTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_VBO_TX__

#include "ScalerFunctionInclude.h"
#include "DisplayVboTx/ScalerDisplayVboTx.h"

#if(_PANEL_STYLE == _PANEL_VBO)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile DWORD g_ulDisplayVboTxMacPort;
volatile DWORD g_ulDisplayVboTxPhyPort;
volatile StructDisplayVboTxInfo g_stDisplayVboTxInfo =
{
    _FALSE,
    _FALSE,
    _DISABLE,
};

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Vbyone HTPDN Interrupt Enable
// Input Value  : enumDisplayVboTxControlMode, _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxHtpdnControl(EnumDisplayVboTxControlMode enumDisplayVboTxControlMode, bit bValue)
{
    ScalerDisplayVboTxXHtpdnControl(_VBO_TX_PORT_0, enumDisplayVboTxControlMode, bValue);

#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        ScalerDisplayVboTxXHtpdnControl(_VBO_TX_PORT_1, enumDisplayVboTxControlMode, bValue);
    }
#endif
}

//--------------------------------------------------
// Description  : Vbyone Video Output Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxForceVideoOutput(bit bEnable)
{
    ScalerDisplayVboTxXForceVideoOutput(_VBO_TX_PORT_0, bEnable);

#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        ScalerDisplayVboTxXForceVideoOutput(_VBO_TX_PORT_1, bEnable);
    }
#endif

    if(bEnable == _DISABLE)
    {
        // LOCKN Ripped off status initial: False
        g_stDisplayVboTxInfo.b1VboLocknRippedOff = _FALSE;

        // Set Panel Fast Off Disable
        g_stDisplayVboTxInfo.b1PanelFastOffStatus = _DISABLE;
    }
}

#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
//--------------------------------------------------
// Description  : Vbyone Force Link Training Flow
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxForceLinkTraining(bit bEnable)
{
    ScalerDisplayVboTxXForceLinkTraining(_VBO_TX_PORT_0, bEnable);

#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        ScalerDisplayVboTxXForceLinkTraining(_VBO_TX_PORT_1, bEnable);
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Vbyone LOCKN Interrupt Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxSetLocknInterrupt(bit bEnable)
{
    ScalerDisplayVboTxXSetLocknInterrupt(_VBO_TX_PORT_0, bEnable);

#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        ScalerDisplayVboTxXSetLocknInterrupt(_VBO_TX_PORT_1, bEnable);
    }
#endif
}

//--------------------------------------------------
// Description  : Vbyone LOCKN_FAIL Interrupt Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxSetUnLocknInterrupt(bit bEnable)
{
    ScalerDisplayVboTxXSetUnLocknInterrupt(_VBO_TX_PORT_0, bEnable);

#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        ScalerDisplayVboTxXSetUnLocknInterrupt(_VBO_TX_PORT_1, bEnable);
    }
#endif
}

//--------------------------------------------------
// Description  : Wait for Vbyone Htpdn
// Input Value  : WORD usNum
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxPollingHotPlug(WORD usNum)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    usPreviousTime = g_usTimerCounter;

    do
    {
        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while((usTimeElapsed <= usNum) && (ScalerDisplayVboTxHpdnStatus() == _FALSE));

    DebugMessageCheck("VBO HPD Time", usTimeElapsed);
}

//--------------------------------------------------
// Description  : Vbyone Hot Plug Detect n Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxHtpdnHandler(void)
{
    // Set UnLOCKN Status: None
    g_stDisplayVboTxInfo.b1VboLocknRippedOff = _FALSE;

    // Check HPD Plug-In Status
    if(ScalerDisplayVboTxHpdnStatus() == _FALSE)
    {
        // Set HPDN Low Controlled By FW
        ScalerDisplayVboTxHtpdnControl(_VBO_FW_CONTROL, _LOW);
    }
}

//--------------------------------------------------
// Description  : Vbyone Lockn Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxLocknHandler(void)
{
    bit bLockStatus = ScalerDisplayVboTxLocknStatus();
    bit bAlnDetect = ((g_stDisplayVboTxInfo.b1VboLocknPinDetect == _TRUE) && (ScalerDisplayVboTxAlnPatternStatus() == _TRUE));

    DebugMessageCheck("Lockn Status", bLockStatus);
    DebugMessageCheck("ALN Status", bAlnDetect);

    // Check Vbyone Lockn status success
    if(!((bLockStatus == _SUCCESS) || (bAlnDetect == _TRUE)))
    {
        // Force transfer to ALN pattern, and enable video output
        ScalerDisplayVboTxForceVideoOutput(_ENABLE);

        // Wait Delay time for ALN patern
        ScalerTimerDelayXms(80);
    }

    // Set LOCKN Interrupt Enable
    ScalerDisplayVboTxSetLocknInterrupt(_ENABLE);

    // Set Detect UnLock Interrupt Enable
    ScalerDisplayVboTxSetUnLocknInterrupt(_ENABLE);
}

//--------------------------------------------------
// Description  : Vbyone Htpdn Check
// Input Value  : None
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxHpdnStatus(void)
{
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        return ((ScalerDisplayVboTxXHpdnStatus(_VBO_TX_PORT_0) == _TRUE) || (ScalerDisplayVboTxXHpdnStatus(_VBO_TX_PORT_1) == _TRUE));
    }
    else
#endif
    {
        return (ScalerDisplayVboTxXHpdnStatus(_VBO_TX_PORT_0) == _TRUE);
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Check
// Input Value  : None
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxLocknStatus(void)
{
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        return ((ScalerDisplayVboTxXLocknStatus(_VBO_TX_PORT_0) == _TRUE) || (ScalerDisplayVboTxXLocknStatus(_VBO_TX_PORT_1) == _TRUE));
    }
    else
#endif
    {
        return (ScalerDisplayVboTxXLocknStatus(_VBO_TX_PORT_0) == _TRUE);
    }
}

//--------------------------------------------------
// Description  : Detect for Vbyone Lockn Voltage Level
// Input Value  : None
// Output Value : High, Low
//--------------------------------------------------
bit ScalerDisplayVboTxGetLocknVoltageLevel(void)
{
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        return ((ScalerDisplayVboTxXGetLocknVoltageLevel(_VBO_TX_PORT_0) == _TRUE) || (ScalerDisplayVboTxXGetLocknVoltageLevel(_VBO_TX_PORT_1) == _TRUE));
    }
    else
#endif
    {
        return (ScalerDisplayVboTxXGetLocknVoltageLevel(_VBO_TX_PORT_0) == _TRUE);
    }
}
//--------------------------------------------------
// Description  : Detect for Vbyone ALN Pattern
// Input Value  : None
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxAlnPatternStatus(void)
{
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        return ((ScalerDisplayVboTxXAlnPatternStatus(_VBO_TX_PORT_0) == _TRUE) || (ScalerDisplayVboTxXAlnPatternStatus(_VBO_TX_PORT_1) == _TRUE));
    }
    else
#endif
    {
        return (ScalerDisplayVboTxXAlnPatternStatus(_VBO_TX_PORT_0) == _TRUE);
    }
}

//--------------------------------------------------
// Description  : Vbyone Panel Fast Off Setting
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxPanelSetFastOff(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        g_stDisplayVboTxInfo.b1PanelFastOffStatus = _ENABLE;
    }
    else
    {
        g_stDisplayVboTxInfo.b1PanelFastOffStatus = _DISABLE;
    }
}

//--------------------------------------------------
// Description  : Vbyone Panel Fast Off Check
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerDisplayVboTxPanelFastOffCheck(void)
{
    return g_stDisplayVboTxInfo.b1PanelFastOffStatus;
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Re Lock, Re-Turn on Backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxPanelBacklightReTurnOn(void)
{
    // When CDR Re-Lock: Backlight Re-Turn on
    if(g_stDisplayVboTxInfo.b1VboLocknRippedOff == _TRUE)
    {
        if((ScalerDisplayVboTxLocknStatus() == _SUCCESS) || (ScalerDisplayVboTxAlnPatternStatus() == _TRUE))
        {
            ScalerTimerDelayXms(_PANEL_POWER_ON_T3);

            // Check Vby1 ALN_En flag, when Vby1 CDR locked, this flag will be triggered
            if(ScalerDisplayVboTxAlnPatternStatus() == _TRUE)
            {
                // Backlight Turn On
                PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_ON);

                // Set CDR re-lock Status: None
                g_stDisplayVboTxInfo.b1VboLocknRippedOff = _FALSE;
            }
            else
            {
#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _ON)
#if(_PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE == _PANEL_OLED_AC_DET_CTRL_WITHOUT_SEQ)
                // Backlight Turn Off
                PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
#endif
#endif
            }
        }
#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _ON)
#if(_PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE == _PANEL_OLED_AC_DET_CTRL_WITHOUT_SEQ)
        else
        {
            // Backlight Turn Off
            PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
        }
#endif
#endif
    }
}

//--------------------------------------------------
// Description  : Get Vby1 Pll Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayVboTxGetPllPowerStatus(void)
{
    if(Scaler32GetBit(PB58050_00_DP14_TX_CMU0, _BIT15) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Set Display Interface Lane Power
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxPowerSwitch(void)
{
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_VBO_EDP_16_LANE_1, ((_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE) ? _POWER_CUT_OFF : _POWER_CUT_ON), _POWER_ON_DELAY_5_MS);
#endif

    // Set Vby1 PHY
    ScalerDisplayVboTxPhyControl(_ENABLE);
}
#endif

#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)
