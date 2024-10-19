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
// ID Code      : ScalerDisplayVboTx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_VBO_TX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DisplayVboTx/ScalerDisplayVboTx.h"

#if(_PANEL_STYLE == _PANEL_VBO)
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
// Description  : Vbyone Interrupt Handler: HTPDN, LOCKN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxIntHandler_EXINT0(void)
{
    bit bVboLockDetect = _FALSE;
    bit bVboUnLockDetect = _FALSE;

    bVboLockDetect = ScalerDisplayVboTxLockDetect_EXINT0();
    bVboUnLockDetect = ScalerDisplayVboTxUnLockDetect_EXINT0();

    // LOCKN: Glitch / Unlock / Lock
    if((bVboLockDetect == _TRUE) && (bVboUnLockDetect == _TRUE))
    {
        // LOCKN: lock status
        if(ScalerDisplayVboTxLockStatus_EXINT0() != _TRUE)
        {
#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _OFF)
#if(_PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE == _PANEL_OLED_AC_DET_CTRL_WITHOUT_SEQ)
            // Backlight Turn Off when CDR unlock
            PCB_BACKLIGHT_POWER_PIN_EXINT(_LIGHT_CONTROL_OFF);
#endif
#endif
            // Set UnLOCKN Status: Ripped off
            g_stDisplayVboTxInfo.b1VboLocknRippedOff = _TRUE;
        }
    }
    else if(bVboUnLockDetect == _TRUE)
    {
#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _OFF)
#if(_PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE == _PANEL_OLED_AC_DET_CTRL_WITHOUT_SEQ)
        // Backlight Turn Off when CDR unlock
        PCB_BACKLIGHT_POWER_PIN_EXINT(_LIGHT_CONTROL_OFF);
#endif
#endif
        // Set UnLOCKN Status: Ripped off
        g_stDisplayVboTxInfo.b1VboLocknRippedOff = _TRUE;
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCK Detect Exint
// Input Value  : None
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxLockDetect_EXINT0(void)
{
    // HTPDN: Plug-In Flag
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        return ((ScalerDisplayVboTxXLockDetect_EXINT0(_VBO_TX_PORT_0) == _TRUE) || (ScalerDisplayVboTxXLockDetect_EXINT0(_VBO_TX_PORT_1) == _TRUE));
    }
    else
#endif
    {
        return (ScalerDisplayVboTxXLockDetect_EXINT0(_VBO_TX_PORT_0) == _TRUE);
    }
}

//--------------------------------------------------
// Description  : Detect for Vbyone ALN Pattern
// Input Value  : None
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxLockStatus_EXINT0(void)
{
    // Lockn Status
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        return ((ScalerDisplayVboTxXLockStatus_EXINT0(_VBO_TX_PORT_0) == _TRUE) || (ScalerDisplayVboTxXLockStatus_EXINT0(_VBO_TX_PORT_1) == _TRUE));
    }
    else
#endif
    {
        return (ScalerDisplayVboTxXLockStatus_EXINT0(_VBO_TX_PORT_0) == _TRUE);
    }
}

//--------------------------------------------------
// Description  : Vbyone Un-LOCK Detect Exint
// Input Value  : None
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxUnLockDetect_EXINT0(void)
{
    // HTPDN: Plug-In Flag
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM == _VBO_32_DATA_LANE)
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)
    {
        return ((ScalerDisplayVboTxXUnLockDetect_EXINT0(_VBO_TX_PORT_0) == _TRUE) || (ScalerDisplayVboTxXUnLockDetect_EXINT0(_VBO_TX_PORT_1) == _TRUE));
    }
    else
#endif
    {
        return (ScalerDisplayVboTxXUnLockDetect_EXINT0(_VBO_TX_PORT_0) == _TRUE);
    }
}
#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)
