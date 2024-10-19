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
// ID Code      : RL6952_Series_IrqList.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// IRQ Mask Flag
#define _IRQ_MASK_CPU_NOTIFY                            (1UL << _IRQN_CPU_NOTIFY)
#define _IRQ_MASK_WDT                                   (1UL << _IRQN_WDT)
#define _IRQ_MASK_BW32                                  (1UL << _IRQN_BW32)
#define _IRQ_MASK_TIMER0                                (1UL << _IRQN_TIMER0)
#define _IRQ_MASK_TIMER1                                (1UL << _IRQN_TIMER1)
#define _IRQ_MASK_TIMER2                                (1UL << _IRQN_TIMER2)
#define _IRQ_MASK_DW_UART                               (1UL << _IRQN_DW_UART)
#define _IRQ_MASK_INT0_TIMER4                           (1UL << _IRQN_INT0_TIMER4)
#define _IRQ_MASK_INT1_TIMER5                           (1UL << _IRQN_INT1_TIMER5)
#define _IRQ_MASK_I2CM                                  (1UL << _IRQN_I2CM)
#define _IRQ_MASK_ADC                                   (1UL << _IRQN_ADC)
#define _IRQ_MASK_DDC                                   (1UL << _IRQN_DDC)
#define _IRQ_MASK_SCALER_OTHER                          (1UL << _IRQN_SCALER_OTHER)
#define _IRQ_MASK_RESERVED2                             (1UL << _IRQN_RESERVED2)
#define _IRQ_MASK_RESERVED3                             (1UL << _IRQN_RESERVED3)
#define _IRQ_MASK_RESERVED4                             (1UL << _IRQN_RESERVED4)
#define _IRQ_MASK_RESERVED5                             (1UL << _IRQN_RESERVED5)
#define _IRQ_MASK_IMD_EVENT                             (1UL << _IRQN_IMD_EVENT)
#define _IRQ_MASK_SCALER_ERROR                          (1UL << _IRQN_SCALER_ERROR)
#define _IRQ_MASK_TX                                    (1UL << _IRQN_TX)
#define _IRQ_MASK_VGA                                   (1UL << _IRQN_VGA)
#define _IRQ_MASK_MST_MSG                               (1UL << _IRQN_MST_MSG)
#define _IRQ_MASK_DP_HIGH                               (1UL << _IRQN_DP_HIGH)
#define _IRQ_MASK_DP_LOW                                (1UL << _IRQN_DP_LOW)
#define _IRQ_MASK_PDCC_HIGH                             (1UL << _IRQN_PDCC_HIGH)
#define _IRQ_MASK_PDCC_LOW                              (1UL << _IRQN_PDCC_LOW)
#define _IRQ_MASK_HDMI_HIGH                             (1UL << _IRQN_HDMI_HIGH)
#define _IRQ_MASK_HDMI_LOW                              (1UL << _IRQN_HDMI_LOW)
#define _IRQ_MASK_ECDSA_PMCI2C_BB                       (1UL << _IRQN_ECDSA_PMCI2C_BB)
#define _IRQ_MASK_REDRIVER                              (1UL << _IRQN_REDRIVER)
#define _IRQ_MASK_SYSTICK                               (1UL << _IRQN_SYSTICK)
#define _IRQ_MASK_SCALER_ALL                            (1UL << _IRQN_SCALER_ALL)

#define _SYSTICK_INT_PRIORITY                           (_CPU_IRQ_HW_LEVEL_5)   // Systick INT Priority
#define _SVC_INT_PRIORITY                               (_CPU_IRQ_HW_LEVEL_5)   // Fixed to Highest Priority (Higher than HW_INT5)
#define _PENDSV_INT_PRIORITY                            (_CPU_IRQ_SW_LEVEL_0)   // Fixed to Lowest Priority (SW_INT0)

// When _PROMOTE_DDC_INT_TO_HW4_INT_LVL is _OFF, DDC INT set to HW_INT1
// When _PROMOTE_DDC_INT_TO_HW4_INT_LVL is _ON, DDC INT set to HW_INT4 for aloowing debug below HW4 INT Level (Except in HW4/HW5 INT)
#define _DDC_INT_PRIORITY                               ((_PROMOTE_DDC_INT_TO_HW4_INT_LVL == _OFF) ? (_CPU_IRQ_HW_LEVEL_1) : (_CPU_IRQ_HW_LEVEL_4))



//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
#if(_CPU32_IP == _CPU32_IP_RX3081)
    // RX3081 Processor Exceptions Numbers
    _IRQN_ADDRESS_ERROR_I_FETCH = -5,           // Instruction Fetch Address unaligned Exception
    _IRQN_BREAK_POINT_INST = -4,                // BREAK Instruction Exception for Debug
    _IRQN_RESERVED_INST = -3,                   // Reserved Instruction Exception
    _IRQN_SV_CALL = -3,                         // Syscall Software Interrupt (impl. by using RI)
    _IRQN_ADDRESS_ERROR_D_FETCH = -2,           // Data Fetch Address unaligned Exception
    _IRQN_ADDRESS_ERROR_D_STORE = -1,           // Data Store Address unaligned Exception
#endif

    // Specific Interrupt Numbers
    _IRQN_CPU_NOTIFY = 0,               // CPU Notify Interrupt
    _IRQN_WDT = 1,                      // CPU Watch Dog Timer Interrupt
    _IRQN_BW32 = 2,                     // BW32 Controller Interrupt
    _IRQN_TIMER0 = 3,                   // Timer0 Interrupt
    _IRQN_TIMER1 = 4,                   // Timer1 Interrupt
    _IRQN_TIMER2 = 5,                   // Timer2 Interrupt (as WDT Timer INT)
    _IRQN_DW_UART = 6,                  // DW_UART Interrupt
    _IRQN_INT0_TIMER4 = 7,              // INT0/Timer4 Interrupt
    _IRQN_INT1_TIMER5 = 8,              // INT1/Timer5 Interrupt
    _IRQN_I2CM = 9,                     // DW8051 I2CM Interrupt
    _IRQN_ADC = 10,                     // DW8051 ADC Interrupt
    _IRQN_DDC = 11,                     // DW8051 DDC Interrupt
    _IRQN_SCALER_OTHER = 12,            // Scaler Other Interrupt
    _IRQN_RESERVED2 = 13,               // Reserved Interrupt
    _IRQN_RESERVED3 = 14,               // Reserved Interrupt
    _IRQN_RESERVED4 = 15,               // Reserved Interrupt
    _IRQN_RESERVED5 = 16,               // Reserved Interrupt
    _IRQN_IMD_EVENT = 17,               // I/M/D Event Interrupt
    _IRQN_SCALER_ERROR = 18,            // Scaler Error Interrupt
    _IRQN_TX = 19,                      // TX0 Interface Interrupt
    _IRQN_VGA = 20,                     // VGA Interface Interrupt
    _IRQN_MST_MSG = 21,                 // MST_MSG Interface Interrupt
    _IRQN_DP_HIGH = 22,                 // DP_HIGH Interface Interrupt
    _IRQN_DP_LOW = 23,                  // DP_LOW Interface Interrupt
    _IRQN_PDCC_HIGH = 24,               // PDCC_HIGH Interface Interrupt
    _IRQN_PDCC_LOW = 25,                // PDCC_LOW Interface Interrupt
    _IRQN_HDMI_HIGH = 26,               // HDMI_HIGH Interface Interrupt
    _IRQN_HDMI_LOW = 27,                // HDMI_LOW Interface Interrupt
    _IRQN_ECDSA_PMCI2C_BB = 28,         // ECDSA_PMCI2C_BB Interface Interrupt
    _IRQN_REDRIVER = 29,                // ReDriver Interface Interrupt
    _IRQN_SYSTICK = 30,                 // Timer3(as SysTick) Interrupt
    _IRQN_SCALER_ALL = 31,              // All Scaler Interrupt
} EnumIRQnType;

typedef enum
{
#if(_CPU32_IP == _CPU32_IP_RX3081)
    _TRAP_INT = 0,                      // Normal Interrupt
    _TRAP_ADDRESS_READ_UNALIGN = 4,     // Inst/data Read Address Unaligned
    _TRAP_ADDRESS_STORE_UNALIGN = 5,    // data Store Address Unaligned
    _TRAP_BREAK_INST = 9,               // BREAK Instruction
    _TRAP_UNKNOWN_INST = 10,            // Reserved(Unknown) Instruction
#endif
} EnumCpuTrapType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
