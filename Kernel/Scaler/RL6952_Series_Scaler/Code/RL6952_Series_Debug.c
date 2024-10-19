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
// ID Code      : RL6952_Series_Debug.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Debug/ScalerDebug.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_ASSERT_SUPPORT == _ON)
#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Check panel parameter by scaler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugCheckPanelParameter(void)
{
    switch(GET_D_DOMAIN_PATH())
    {
        case _D_DOMAIN_2_PATH:
            // _PANEL_PIXEL_CLOCK_MAX_KHZ > 600M (2 PATH)
            ASSERT(_PANEL_PIXEL_CLOCK_MAX_KHZ <= 600000);
            break;

        default:
            break;
    }

    // _PANEL_STYLE Can Not Be _PANEL_LVDS
    ASSERT(_PANEL_STYLE != _PANEL_LVDS);
}
#endif
#endif
