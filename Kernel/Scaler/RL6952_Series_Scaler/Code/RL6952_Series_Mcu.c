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
// ID Code      : RL6952_Series_Mcu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_MCU__

#include "ScalerFunctionInclude.h"
#include "Mcu/ScalerMcu.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_CPU32_IP == _CPU32_IP_RX3081)
EnumCpuIrqPriority const tINTERRUPT_PRIORITY_RX3081[] =
{
    _CPU_IRQ_HW_LEVEL_0,        /*!< 00:CPU Notify Interrupt (From SCPU)            */
    _CPU_IRQ_DISABLE,           /*!< 01:CPU Watch Dog Interrupt (KCPU_WDT32)        */
    _CPU_IRQ_DISABLE,           /*!< 02:BW32/RBUS2DDR Interrupt                     */
#if(_INSTANT_TIMER_EVENT_0 == _ON)
    _CPU_IRQ_HW_LEVEL_1,        /*!< 03:Timer0 Interrupt                            */
#else
    _CPU_IRQ_DISABLE,           /*!< 03:Timer0 Interrupt                            */
#endif
#if(_INSTANT_TIMER_EVENT_1 == _ON)
    _CPU_IRQ_HW_LEVEL_1,        /*!< 04:Timer1 Interrupt                            */
#else
    _CPU_IRQ_DISABLE,           /*!< 04:Timer1 Interrupt                            */
#endif
    _CPU_IRQ_HW_LEVEL_0,        /*!< 05:Timer2 Interrupt                            */
#if(_UART_SUPPORT == _ON)
    _CPU_IRQ_HW_LEVEL_1,        /*!< 06:DW_UART Interrupt                           */
#else
    _CPU_IRQ_DISABLE,           /*!< 06:DW_UART Interrupt                           */
#endif
    _CPU_IRQ_DISABLE,           /*!< 07:Timer4/INT0 Interrupt                       */
    _CPU_IRQ_DISABLE,           /*!< 08:Timer5/INT1 Interrupt                       */
    _CPU_IRQ_HW_LEVEL_1,        /*!< 09:I2CM Interrupt                              */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 10:ADC Interrupt                               */
    _DDC_INT_PRIORITY,          /*!< 11:DDC Interrupt                               */
#if(_ENABLE_KCPU_SCALER_OTHER_INT == _ON)
    _CPU_IRQ_HW_LEVEL_2,        /*!< 12:Scaler Other Interrupt                      */
#else
    _CPU_IRQ_HW_LEVEL_2,        /*!< 12:Scaler Other Interrupt                      */
#endif
    _CPU_IRQ_DISABLE,           /*!< 13:Reserved Interrupt                          */
    _CPU_IRQ_DISABLE,           /*!< 14:Reserved Interrupt                          */
    _CPU_IRQ_DISABLE,           /*!< 15:Reserved Interrupt                          */
    _CPU_IRQ_DISABLE,           /*!< 16:Reserved Interrupt                          */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 17:I/M/D Event Interrupt                       */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 18:Scaler Error Interrupt                      */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 19:TX0 Interface Interrupt                     */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 20:VGA Interface Interrupt                     */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 21:MST_MSG Interface Interrupt                 */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 22:DP_HIGH Interface Interrupt                 */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 23:DP_LOW Interface Interrupt                  */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 24:PDCC_HIGH Interface Interrupt               */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 25:PDCC_LOW Interface Interrupt                */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 26:HDMI_HIGH Interface Interrupt               */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 27:HDMI_LOW Interface Interrupt                */
    _CPU_IRQ_HW_LEVEL_2,        /*!< 28:ECDSA_PMCI2C_BB Interface Interrupt         */
    _CPU_IRQ_HW_LEVEL_3,        /*!< 29:ReDriver Interface Interrupt                */
    _SYSTICK_INT_PRIORITY,      /*!< 30:Timer3(as SysTick) Interrupt                */
    _CPU_IRQ_DISABLE,           /*!< 31:All Scaler Interrupt                        */
};
#endif  // #if(_CPU32_IP == _CPU32_IP_RX3081)

__attribute__((section(".fast_data.tScalerAllIrqUnion")))
EnumIRQnType const tScalerAllIrqUnion[] =
{
    _IRQN_SCALER_OTHER,         /*!< 12:Scaler Other Interrupt                      */
    _IRQN_IMD_EVENT,            /*!< 17:I/M/D Event Interrupt                       */
    _IRQN_SCALER_ERROR,         /*!< 18:Scaler Error Interrupt                      */
    _IRQN_TX,                   /*!< 19:TX0 Interface Interrupt                     */
    _IRQN_VGA,                  /*!< 20:VGA Interface Interrupt                     */
    _IRQN_MST_MSG,              /*!< 21:MST_MSG Interface Interrupt                 */
    _IRQN_DP_HIGH,              /*!< 22:DP_HIGH Interface Interrupt                 */
    _IRQN_DP_LOW,               /*!< 23:DP_LOW Interface Interrupt                  */
    /* _IRQN_PDCC_HIGH,           !< 24:PDCC_HIGH Interface Interrupt               */
    /* _IRQN_PDCC_LOW,            !< 25:PDCC_LOW Interface Interrupt                */
    _IRQN_HDMI_HIGH,            /*!< 26:HDMI_HIGH Interface Interrupt               */
    _IRQN_HDMI_LOW,             /*!< 27:HDMI_LOW Interface Interrupt                */
    /* _IRQN_ECDSA_PMCI2C_BB,     !< 28:ECDSA_PMCI2C_BB Interface Interrupt         */
    /* _IRQN_REDRIVER,            !< 29:ReDriver Interface Interrupt                */
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDCRAM Block Select
// Input Value  : usDdcramStartAddr
// Output Value : ucTemp for config
//--------------------------------------------------
BYTE ScalerMcuDdcramBlockSel(DWORD ulDdcramStartAddr)
{
    BYTE ucTemp = 0;

    switch(ulDdcramStartAddr)
    {
        case 0xA0100200:
            ucTemp = 0;
            break;

        case 0xA0100600:
            ucTemp = 1;
            break;

        case 0xA0100A00:
            ucTemp = 2;
            break;

        case 0xA0100E00:
            ucTemp = 3;
            break;

        case 0xA0101200:
            ucTemp = 4;
            break;

        // invalid address, return reserved
        default:
            ucTemp = 5;
            break;
    }

    return ucTemp;
}

#if(_CPU32_IP == _CPU32_IP_RX3081)
//--------------------------------------------------
// Description  : MCU Initial Settings
//                MCU initial function, must be called at first
//                Since code banking can not work correctly before this function is called,
//                this function should stay in bank0.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuInitial3081(void)
{
    static_assert((GET_TABLE_ELEMENT_NUM(tScalerAllIrqUnion) == _SCALER_ALL_IRQ_UNION_NUM), "_SCALER_ALL_IRQ_UNION_NUM not match tScalerAllIrqUnion size!!!");

    // Clear All Pending INT Flags
    write_c0_cause(0);

    // Init HW INT default Interrupt Priority Setting
    ScalerMcuIntPriorityInit();

    // Initialize the HAL Library; it must be the first function
    // to be executed before the call of any HAL function.
    ScalerSysTickInit(_SYSTICK_INT_PRIORITY);
    // Set BEV to 0xBFC00180 , Enable All INT , Disable Global IEc
    write_c0_status(0x0040ff00);

    // Enable WDT INT
    ScalerWdtInitial();
}
#endif  // #if(_CPU32_IP == _CPU32_IP_RX3081)

//--------------------------------------------------
// Description  : Check if can use HW BW32
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerMcuCheckHwBW32Avaiable(void)
{
    return _FALSE;
}
