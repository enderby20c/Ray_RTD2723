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
// ID Code      : RL6952_Series_Drr.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DRR__

#include "ScalerFunctionInclude.h"
#include "Drr/ScalerDrr.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable Freesync Test Pin
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDrrTestPinEnable(void)
{
    // Set DVS test pin (TestOut0) and DHS test pin (TestOut1)
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_48_D_DOMAIN_TESTOUT, 0x01);
    ScalerSetDataPortBit(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_00_TEST_MODE, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    ScalerSetDataPortBit(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_06_TST_CLK_CTRL5, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    ScalerSetDataPortBit(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_0A_TST_CLK_CTRL9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Test signal select D domain
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_01_TEST_MODE_CTRL, 0x02);

    // Force output test signal
    ScalerSetDataPortBit(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_01_TEST_MODE_CTRL, ~_BIT7, _BIT7);

    // Test 0: DVS
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_20_TESTOUT_SEL0, 0x41);

    // Test 1: DHS
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_21_TESTOUT_SEL1, 0x40);
}
#endif
