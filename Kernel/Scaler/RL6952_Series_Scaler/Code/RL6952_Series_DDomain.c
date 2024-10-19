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
// ID Code      : RL6952_Series_DDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DDOMAIN__

#include "ScalerFunctionInclude.h"
#include "DDomain/ScalerDDomain.h"

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
// Description  : Set D domain average request
// Input Value  : D domain Region, Hwidth and Htotal
// Output Value : none
//--------------------------------------------------
void ScalerDDomainSetDspcLineLength(void)
{
    WORD usBGWidth = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH);

    // Set Dspc Line Length
    ScalerSetBit(P39_1B_DSPC_LINE_LENGTH_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usBGWidth) & 0x1F));
    ScalerSetByte(P39_1C_BACK_DSPC_LINE_LENGTH_L, LOBYTE(usBGWidth));
}
