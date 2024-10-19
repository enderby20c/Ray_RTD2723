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
// ID Code      : ScalerMcu_EXINT1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MCU_EXINT1__

#include "ScalerFunctionInclude.h"
#include "Mcu/ScalerMcu.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DDC SCL Toggle IRQ Enable
// Input Value  : ucDDCx
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(BYTE ucDDCx)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            return ((bit)ScalerGetBit_EXINT(PFF_E7_VGA_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            return ((bit)ScalerGetBit_EXINT(PFF_E4_DDC0_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            return ((bit)ScalerGetBit_EXINT(PFF_E5_DDC1_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            return ((bit)ScalerGetBit_EXINT(PFE_69_DDC2_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            return ((bit)ScalerGetBit_EXINT(PFE_72_DDC3_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            return ((bit)ScalerGetBit_EXINT(PFE_7B_DDC4_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            return ((bit)ScalerGetBit_EXINT(PFE_84_DDC5_EDID_IRQ, _BIT3));
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set DDC SCL Toggle IRQ Enable
// Input Value  : ucDDCx
// Input Value  : ucEnable
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcSetSclToggleIrqEnable_EXINT1(BYTE ucDDCx, BYTE ucEnable)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit_EXINT(PFF_E7_VGA_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit_EXINT(PFF_E4_DDC0_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit_EXINT(PFF_E5_DDC1_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit_EXINT(PFE_69_DDC2_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit_EXINT(PFE_72_DDC3_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit_EXINT(PFE_7B_DDC4_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit_EXINT(PFE_84_DDC5_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clear DDC SCL Toggle IRQ Status
// Input Value  : ucDDCx
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcClearSclToggleIrqStatus_EXINT1(BYTE ucDDCx)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit_EXINT(PFF_E7_VGA_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit_EXINT(PFF_E4_DDC0_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit_EXINT(PFF_E5_DDC1_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit_EXINT(PFE_69_DDC2_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit_EXINT(PFE_72_DDC3_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit_EXINT(PFE_7B_DDC4_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit_EXINT(PFE_84_DDC5_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DDC SCL Toggle IRQ Status
// Input Value  : ucDDCx
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(BYTE ucDDCx)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            return ((bit)ScalerGetBit_EXINT(PFF_E7_VGA_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            return ((bit)ScalerGetBit_EXINT(PFF_E4_DDC0_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            return ((bit)ScalerGetBit_EXINT(PFF_E5_DDC1_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            return ((bit)ScalerGetBit_EXINT(PFE_69_DDC2_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            return ((bit)ScalerGetBit_EXINT(PFE_72_DDC3_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            return ((bit)ScalerGetBit_EXINT(PFE_7B_DDC4_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            return ((bit)ScalerGetBit_EXINT(PFE_84_DDC5_EDID_IRQ, _BIT2));
#endif

        default:
            return _FALSE;
    }
}
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
//--------------------------------------------------
// Description  : Get IIC 1 Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC1SlaveHandler_EXINT1(void)
{
    // Write cmd finish status IRQ
    if(((MCU_FF8B_I2CS_CTRL2 & _BIT7) == _BIT7) && ((MCU_FF8D_I2CS_STATUS1 & _BIT7) == _BIT7))
    {
        // Reset Retimer I2C Data
        __real_memset(g_pucMcuHwI2c1Data, 0x00, sizeof(g_pucMcuHwI2c1Data));

        // Process I2C Slave Received Command
        ScalerMcuHwIIC1SlaveIntGetData_EXINT1(g_pucMcuHwI2c1Data);

        // Proccess Master Command
        ScalerMcuHwIIC1SlaveProc_EXINT1();

        // Clear Host Write Finished & Busy Bit
        MCU_FF8D_I2CS_STATUS1 |= (_BIT7 | _BIT3);
    }
}

//--------------------------------------------------
// Description  : Get IIC_1 Slave Data in Interrupt Process
// Input Value  : pReadArray --> Data received
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC1SlaveIntGetData_EXINT1(BYTE *pucReadArray)
{
    BYTE ucTemp = 0;
    WORD usTimeOutCnt = 600;

    BYTE ucLen = ScalerGetBit_EXINT(PFF_8E_I2CS_BUFLEN, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Reset data point
    ScalerSetBit_EXINT(PFF_8E_I2CS_BUFLEN, ~_BIT7, 0);
    ScalerSetBit_EXINT(PFF_8E_I2CS_BUFLEN, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while(ScalerGetBit_EXINT(PFF_CD_I2CM_SR, _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC 1 module
            ScalerSetBit_EXINT(PFF_C5_I2CM_CR0, ~_BIT7, 0);
            ScalerSetBit_EXINT(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

            return;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US_EXINT();
        }
    }

    // Read out data
    for(ucTemp = 0; ucTemp < ucLen; ucTemp++)
    {
        pucReadArray[ucTemp] = MCU_FFCE_I2CM_TD;
    }
}

//--------------------------------------------------
// Description  : IIC 1 Slave Data Proccess
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC1SlaveProc_EXINT1(void)
{
    BYTE ucIndex = 0x00;
    BYTE ucLength = 0x00;
    BYTE ucTableData = 0x00;
    BYTE ucRcvData = 0x00;
    WORD usTimeOutCnt = 600;

    switch(GET_HW_IIC_1_SLAVE_CMD())
    {
        case _HW_I2C_SLAVE_CMD_WRITE_BYTE:

            ucLength = (GET_HW_IIC_1_SLAVE_SUB_CMD() & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            for(ucIndex = 0; ucIndex < ucLength; ucIndex++)
            {
                // Write Table Data
                // ScalerGlobalMainChipSetConfigData_EXINT1((GET_HW_IIC_1_SLAVE_START_ADDR() + ucIndex), GET_HW_IIC_1_SLAVE_DATA(ucIndex));
            }

            break;

        case _HW_I2C_SLAVE_CMD_WRITE_BIT:

            // Get Table Data
            // ucTableData = ScalerGlobalMainChipGetConfigData_EXINT1(GET_HW_IIC_1_SLAVE_START_ADDR());
            ucTableData = ucTableData & (~(GET_HW_IIC_1_SLAVE_SUB_CMD()));

            // Check Bit Changing
            ucRcvData = GET_HW_IIC_1_SLAVE_DATA(0);
            ucRcvData = ucRcvData & (GET_HW_IIC_1_SLAVE_SUB_CMD());

            // Write Table Data
            // ScalerGlobalMainChipSetConfigData_EXINT1(GET_HW_IIC_1_SLAVE_START_ADDR(), (ucTableData | ucRcvData));

            break;

        case _HW_I2C_SLAVE_CMD_READ_BYTE:

            ucLength = (GET_HW_IIC_1_SLAVE_SUB_CMD() & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // Reset data point
            ScalerSetBit_EXINT(PFF_8E_I2CS_BUFLEN, ~_BIT7, 0);
            ScalerSetBit_EXINT(PFF_8E_I2CS_BUFLEN, ~_BIT7, _BIT7);

            // Wait I2C Fifo Clk Switch to Mcu Clk
            while(ScalerGetBit_EXINT(PFF_CD_I2CM_SR, _BIT5) != _BIT5)
            {
                if(usTimeOutCnt == 0)
                {
                    // Reset(Block) IIC 1 module
                    ScalerSetBit_EXINT(PFF_C5_I2CM_CR0, ~_BIT7, 0);
                    ScalerSetBit_EXINT(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

                    return;
                }
                else
                {
                    usTimeOutCnt--;

                    DELAY_5US_EXINT();
                }
            }

            // Get first data from 0xFFA1
            // MCU_FFA1_I2CS_STATUS_BYTE = ScalerGlobalMainChipGetConfigData_EXINT1(GET_HW_IIC_1_SLAVE_START_ADDR());
            MCU_FFA1_I2CS_STATUS_BYTE = 0xAB; // Test!!!


            for(ucIndex = 1; ucIndex < ucLength; ucIndex++)
            {
                // Get Remain Table Data
                // MCU_FFCE_I2CM_TD = ScalerGlobalMainChipGetConfigData_EXINT1(GET_HW_IIC_1_SLAVE_START_ADDR() + ucIndex);
            }

            break;

        default:
            break;
    }
}
#endif // End of #if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
#endif // End of #if(_HW_IIC_1_SUPPORT == _ON)

