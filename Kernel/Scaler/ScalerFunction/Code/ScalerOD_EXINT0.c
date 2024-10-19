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
// ID Code      : ScalerOD_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_OD_EXINT0__

#include "ScalerFunctionInclude.h"
#include "OD/ScalerOD.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_OD_FUNCTION == _ON)

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dynamic OD handler interrupt process (EXINT0 only)
//                Dynamically enable/disable OD for memory bandwidth saving
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODIntHandler_EXINT0(void)
{
    BYTE ucBackupDataPortAddr = 0;
    BYTE ucFreerunDVSCount = 0;

    if(GET_OD_CURR_DYNAMIC_STATUS() == _DISABLE)
    {
        return;
    }
    //=======================================================
    // Get current serial number in repeated frame sequence
    //=======================================================
    // Backup data port address
    ucBackupDataPortAddr = ScalerGetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT);

    // Get current free run DVS counter
    ScalerSetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_28_FREE_RUN_DVS_CNT);
    ucFreerunDVSCount = ScalerGetByte_EXINT(P0_2B_DISPLAY_FORMAT_DATA_PORT);

    // Resume data port address
    ScalerSetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT, ucBackupDataPortAddr);

    //=======================================================
    // Set OD control registers according to current state
    //=======================================================
    switch(GET_FS_ACTIVE_INFO_DVF_SELECT())
    {
#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
        //====================================
        // DVF = 2 IVF, EX: 30 to 60Hz
        //====================================
        // I-domain frame:          |______F1_______|______F2_______|______F3_______|
        // D-domain frame:   |__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F3___|
        // <Free run DVS count>:     |___0___|___1___|___0___|___1___|___0___|___1___|
        // <OD control>:             |__off__|___on__|__off__|___on__|__off__|___on__|
        // OD actual(DB effective):  |_______|__OFF__|___ON__|__OFF__|___ON__|__OFF__|
        // OD memory access:         |_______|_______|___W___|___R___|___W___|___R___|
        case _2_IVF:
            switch(ucFreerunDVSCount)
            {
                case 0:
                    // Disable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                    break;

                case 1:
                    // Enable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;

                default:
                    break;
            }
            break;

        //====================================
        // DVF = 2.5 IVF, EX: 24 to 60Hz
        //====================================
        // I-domain frame:          |________F1_________|________F2_________|________F3_________|________F4_________|
        // D-domain frame:   |__F0___|__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F2___|__F3___|__F3___|__F4___|
        // <Free run DVS count>:     |___0___|___1___|___2___|___3___|___4___|___0___|___1___|___2___|___3___|___4___|
        // <OD control>:             |___on__|__off__|___on__|__off__|__off__|___on__|__off__|___on__|__off__|__off__|
        // OD actual(DB effective):  |_______|___ON__|__OFF__|___ON__|__OFF__|__OFF__|___ON__|__OFF__|___ON__|__OFF__|
        // OD memory access:         |_______|_______|___R___|___W___|___R___|_______|___W___|___R___|___W___|___R___|
        case _2_5_IVF:
            switch(ucFreerunDVSCount)
            {
                case 0:
                case 2:
                    // Switch OD memory address
                    if(ScalerGetBit_EXINT(P5_AD_DISP_M1_STATUS, (_BIT7 | _BIT6)) == 0x00)
                    {
                        ScalerSetBit_EXINT(P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((g_pulOD3BlkStartAddr[0] >> 24) & 0x0F));
                        ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, ((g_pulOD3BlkStartAddr[0] >> 16) & 0xFF));
                        ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, ((g_pulOD3BlkStartAddr[0] >> 8) & 0xFF));
                        ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, (g_pulOD3BlkStartAddr[0] & 0xFF));
                    }
                    else if(ScalerGetBit_EXINT(P5_AD_DISP_M1_STATUS, (_BIT7 | _BIT6)) == _BIT6)
                    {
                        ScalerSetBit_EXINT(P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((g_pulOD3BlkStartAddr[1] >> 24) & 0x0F));
                        ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, ((g_pulOD3BlkStartAddr[1] >> 16) & 0xFF));
                        ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, ((g_pulOD3BlkStartAddr[1] >> 8) & 0xFF));
                        ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, (g_pulOD3BlkStartAddr[1] & 0xFF));
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((g_pulOD3BlkStartAddr[2] >> 24) & 0x0F));
                        ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, ((g_pulOD3BlkStartAddr[2] >> 16) & 0xFF));
                        ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, ((g_pulOD3BlkStartAddr[2] >> 8) & 0xFF));
                        ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, (g_pulOD3BlkStartAddr[2] & 0xFF));
                    }

                    // Enable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;

                case 1:
                case 3:
                case 4:
                    // Disable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                    break;

                default:
                    break;
            }
            break;

        //====================================
        // DVF = 3 IVF, EX: 24 to 72Hz
        //====================================
        // I-domain frame:          |__________F1___________|__________F2___________|__________F3___________|
        // D-domain frame:   |__F0___|__F0___|__F0___|__F1___|__F1___|__F1___|__F2___|__F2___|__F2___|__F3___|
        // <Free run DVS count>:     |___0___|___1___|___2___|___0___|___1___|___2___|___0___|___1___|___2___|
        // <OD control>:             |___on__|__off__|__off__|___on__|__off__|__off__|___on__|__off__|__off__|
        // OD actual(DB effective):  |_______|___ON__|__OFF__|__OFF__|___ON__|__OFF__|__OFF__|___ON__|__OFF__|
        // OD memory access:         |_______|_______|___R___|_______|___W___|___R___|_______|___W___|___R___|
        case _3_IVF:
            switch(ucFreerunDVSCount)
            {
                case 0:
                    // Switch OD memory address
                    if(ScalerGetBit_EXINT(P5_AD_DISP_M1_STATUS, (_BIT7 | _BIT6)) == 0x00)
                    {
                        ScalerSetBit_EXINT(P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((g_pulOD3BlkStartAddr[0] >> 24) & 0x0F));
                        ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, ((g_pulOD3BlkStartAddr[0] >> 16) & 0xFF));
                        ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, ((g_pulOD3BlkStartAddr[0] >> 8) & 0xFF));
                        ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, (g_pulOD3BlkStartAddr[0] & 0xFF));
                    }
                    else if(ScalerGetBit_EXINT(P5_AD_DISP_M1_STATUS, (_BIT7 | _BIT6)) == _BIT6)
                    {
                        ScalerSetBit_EXINT(P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((g_pulOD3BlkStartAddr[1] >> 24) & 0x0F));
                        ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, ((g_pulOD3BlkStartAddr[1] >> 16) & 0xFF));
                        ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, ((g_pulOD3BlkStartAddr[1] >> 8) & 0xFF));
                        ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, (g_pulOD3BlkStartAddr[1] & 0xFF));
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((g_pulOD3BlkStartAddr[2] >> 24) & 0x0F));
                        ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, ((g_pulOD3BlkStartAddr[2] >> 16) & 0xFF));
                        ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, ((g_pulOD3BlkStartAddr[2] >> 8) & 0xFF));
                        ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, (g_pulOD3BlkStartAddr[2] & 0xFF));
                    }

                    // Enable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;

                case 1:
                case 2:
                    // Disable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                    break;

                default:
                    break;
            }
            break;

#else // #if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _OFF)

        //====================================
        // DVF = 2 IVF, EX: 30 to 60Hz
        //====================================
        // I-domain frame:          |______F1_______|______F2_______|______F3_______|
        // D-domain frame:           |__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|
        // <Free run DVS count>:     |___0___|___1___|___0___|___1___|___0___|___1___|
        // <OD control>:             |___on__|__off__|___on__|__off__|___on__|__off__|
        // OD actual(DB effective):  |_______|___ON__|__OFF__|___ON__|__OFF__|___ON__|
        // OD memory access:         |_______|_______|___R___|___W___|___R___|___W___|
        case _2_IVF:
            switch(ucFreerunDVSCount)
            {
                case 0:
                    // Enable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;

                case 1:
                    // Disable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                    break;

                default:
                    break;
            }
            break;

        //====================================
        // DVF = 2.5 IVF, EX: 24 to 60Hz
        //====================================
        // I-domain frame:          |________F1_________|________F2_________|________F3_________|________F4_________|
        // D-domain frame:           |__F0___|__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F2___|__F3___|__F3___|
        // <Free run DVS count>:     |___0___|___1___|___2___|___3___|___4___|___0___|___1___|___2___|___3___|___4___|
        // <OD control>:             |__off__|___on__|__off__|___on__|__off__|__off__|___on__|__off__|___on__|__off__|
        // OD actual(DB effective):  |_______|__OFF__|___ON__|__OFF__|___ON__|__OFF__|__OFF__|___ON__|__OFF__|___ON__|
        // OD memory access:         |_______|_______|___W___|___R___|___W___|___R___|_______|___W___|___R___|___W___|
        case _2_5_IVF:
            switch(ucFreerunDVSCount)
            {
                case 0:
                case 2:
                case 4:
                    // Disable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                    break;

                case 1:
                case 3:
                    // Enable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;

                default:
                    break;
            }
            break;

        //====================================
        // DVF = 3 IVF, EX: 24 to 72Hz
        //====================================
        // I-domain frame:          |__________F1___________|__________F2___________|__________F3___________|
        // D-domain frame:           |__F0___|__F0___|__F0___|__F1___|__F1___|__F1___|__F2___|__F2___|__F2___|
        // <Free run DVS count>:     |___0___|___1___|___2___|___0___|___1___|___2___|___0___|___1___|___2___|
        // <OD control>:             |__off__|___on__|__off__|__off__|___on__|__off__|__off__|___on__|__off__|
        // OD actual(DB effective):  |_______|__OFF__|___ON__|__OFF__|__OFF__|___ON__|__OFF__|__OFF__|___ON__|
        // OD memory access:         |_______|_______|___W___|___R___|_______|___W___|___R___|_______|___W___|
        case _3_IVF:
            switch(ucFreerunDVSCount)
            {
                case 0:
                case 2:
                    // Disable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                    break;

                case 1:
                    // Enable OD
                    ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;

                default:
                    break;
            }
            break;

#endif // End of #if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
        //====================================
        // Other cases
        //====================================
        default:
            break;
    }// End of switch(GET_FS_ACTIVE_INFO_DVF_SELECT())
} // End of void ScalerODIntHandler_EXINT0()
#endif // End of #if(_FRC_SUPPORT == _ON)

#endif // End of #if(_OD_SUPPORT == _ON)
