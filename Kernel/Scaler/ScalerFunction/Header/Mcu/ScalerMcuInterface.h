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
// ID Code      : ScalerMcuInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Hardware IIC
//--------------------------------------------------
#define _HW_IIC_BUFFER_SIZE                         24

//--------------------------------------------------
// Macros of MCU Watch Dog
//--------------------------------------------------
#define CLR_MCU_WATCH_DOG()                         (ScalerWdtClearWDT())

//--------------------------------------------------
// Macros of DDC-CI0
//--------------------------------------------------
#define GET_DDCCI0_SLAVE_ADDRESS()                  (MCU_FF23_IIC_SET_SLAVE & 0xFE)
#define GET_DDCCI0_SUBADDRESS()                     (MCU_FF24_IIC_SUB_IN)
#define GET_DDCCI0_DATA_IN()                        (MCU_FF25_IIC_DATA_IN)
#define GET_DDCCI0_STATUS1()                        (MCU_FF27_IIC_STATUS)
#define GET_DDCCI0_STATUS2()                        (MCU_FF29_IIC_STATUS2)
#define GET_DDCCI0_IRQ_STATUS()                     (MCU_FF2A_IIC_IRQ_CONTROL2)

#define SET_DDCCI0_SLAVE_ADDRESS(x)                 (MCU_FF23_IIC_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI0_DATA_OUT(x)                      (MCU_FF26_IIC_DATA_OUT = (x))
#define CLR_DDCCI0_STATUS1(x)                       (MCU_FF27_IIC_STATUS &= ~(x))
#define SET_DDCCI0_STATUS2(x)                       (MCU_FF29_IIC_STATUS2 = (x))
#define SET_DDCCI0_IRQ_STATUS(x)                    (MCU_FF2A_IIC_IRQ_CONTROL2 = (x))
#define GET_DDCCI0_DDC_CHANNEL()                    (ScalerGetBit(PFF_22_IIC_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))

//--------------------------------------------------
// MACRO for RUN DDCCI Command Source
//--------------------------------------------------
#define GET_RUN_DDCCI_COMMAND_SRC(x)                (g_penumMcuDdcciCommandSrc[x])
#define SET_RUN_DDCCI_COMMAND_SRC(x, y)             (g_penumMcuDdcciCommandSrc[x] = (y))

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
#define GET_RECEIVE_DDCCI0_CMD_NOT_FINISH()         (g_ucMcuReceiveDdcci0CmdNotFinish)
#define SET_RECEIVE_DDCCI0_CMD_NOT_FINISH()         (g_ucMcuReceiveDdcci0CmdNotFinish = _TRUE)
#define CLR_RECEIVE_DDCCI0_CMD_NOT_FINISH()         (g_ucMcuReceiveDdcci0CmdNotFinish = _FALSE)
#endif

#if((_MULTI_DISPLAY_MAX >= 0x02) || ((_FW_UPDATE_PROCESS_SUPPORT == _ON) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)))
//--------------------------------------------------
// Macros of DDC-CI1
//--------------------------------------------------
#define GET_DDCCI1_SLAVE_ADDRESS()                  (MCU_FE87_IIC_1_SET_SLAVE & 0xFE)
#define GET_DDCCI1_SUBADDRESS()                     (MCU_FE88_IIC_1_SUB_IN)
#define GET_DDCCI1_DATA_IN()                        (MCU_FE89_IIC_1_DATA_IN)
#define GET_DDCCI1_STATUS1()                        (MCU_FE8B_IIC_1_STATUS)
#define GET_DDCCI1_STATUS2()                        (MCU_FE8D_IIC_1_STATUS2)
#define GET_DDCCI1_IRQ_STATUS()                     (MCU_FE8E_IIC_1_IRQ_CONTROL2)

#define SET_DDCCI1_SLAVE_ADDRESS(x)                 (MCU_FE87_IIC_1_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI1_DATA_OUT(x)                      (MCU_FE8A_IIC_1_DATA_OUT = (x))
#define CLR_DDCCI1_STATUS1(x)                       (MCU_FE8B_IIC_1_STATUS &= ~(x))
#define SET_DDCCI1_STATUS2(x)                       (MCU_FE8D_IIC_1_STATUS2 = (x))
#define SET_DDCCI1_IRQ_STATUS(x)                    (MCU_FE8E_IIC_1_IRQ_CONTROL2 = (x))
#define GET_DDCCI1_DDC_CHANNEL()                    (ScalerGetBit(PFE_86_IIC_1_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || ((_FW_UPDATE_PROCESS_SUPPORT == _ON) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2)))
//--------------------------------------------------
// Macros of DDC-CI2
//--------------------------------------------------
#define GET_DDCCI2_SLAVE_ADDRESS()                  (MCU_FE95_IIC_2_SET_SLAVE & 0xFE)
#define GET_DDCCI2_SUBADDRESS()                     (MCU_FE96_IIC_2_SUB_IN)
#define GET_DDCCI2_DATA_IN()                        (MCU_FE97_IIC_2_DATA_IN)
#define GET_DDCCI2_STATUS1()                        (MCU_FE99_IIC_2_STATUS)
#define GET_DDCCI2_STATUS2()                        (MCU_FE9B_IIC_2_STATUS2)
#define GET_DDCCI2_IRQ_STATUS()                     (MCU_FE9C_IIC_2_IRQ_CONTROL2)

#define SET_DDCCI2_SLAVE_ADDRESS(x)                 (MCU_FE95_IIC_2_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI2_DATA_OUT(x)                      (MCU_FE98_IIC_2_DATA_OUT = (x))
#define CLR_DDCCI2_STATUS1(x)                       (MCU_FE99_IIC_2_STATUS &= ~(x))
#define SET_DDCCI2_STATUS2(x)                       (MCU_FE9B_IIC_2_STATUS2 = (x))
#define SET_DDCCI2_IRQ_STATUS(x)                    (MCU_FE9C_IIC_2_IRQ_CONTROL2 = (x))
#define GET_DDCCI2_DDC_CHANNEL()                    (ScalerGetBit(PFE_94_IIC_2_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || ((_FW_UPDATE_PROCESS_SUPPORT == _ON) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3)))
//--------------------------------------------------
// Macros of DDC-CI3
//--------------------------------------------------
#define GET_DDCCI3_SLAVE_ADDRESS()                  (MCU_FEA4_IIC_3_SET_SLAVE & 0xFE)
#define GET_DDCCI3_SUBADDRESS()                     (MCU_FEA5_IIC_3_SUB_IN)
#define GET_DDCCI3_DATA_IN()                        (MCU_FEA6_IIC_3_DATA_IN)
#define GET_DDCCI3_STATUS1()                        (MCU_FEA8_IIC_3_STATUS)
#define GET_DDCCI3_STATUS2()                        (MCU_FEAA_IIC_3_STATUS2)
#define GET_DDCCI3_IRQ_STATUS()                     (MCU_FEAB_IIC_3_IRQ_CONTROL2)

#define SET_DDCCI3_SLAVE_ADDRESS(x)                 (MCU_FEA4_IIC_3_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI3_DATA_OUT(x)                      (MCU_FEA7_IIC_3_DATA_OUT = (x))
#define CLR_DDCCI3_STATUS1(x)                       (MCU_FEA8_IIC_3_STATUS &= ~(x))
#define SET_DDCCI3_STATUS2(x)                       (MCU_FEAA_IIC_3_STATUS2 = (x))
#define SET_DDCCI3_IRQ_STATUS(x)                    (MCU_FEAB_IIC_3_IRQ_CONTROL2 = (x))
#define GET_DDCCI3_DDC_CHANNEL()                    (ScalerGetBit(PFE_A3_IIC_3_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
#define GET_DDCCI4_SLAVE_ADDRESS()                  (MCU_FD01_IIC_4_SET_SLAVE & 0xFE)
#define GET_DDCCI4_DDC_CHANNEL()                    (ScalerGetBit(PFD_00_IIC_4_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))
#endif

#if(_HW_ISP_SPEED_UP_SUPPORT == _ON)
#define GET_BG_ISP_SLAVE_ADDRESS()                  (MCU_FD92_BACKGROUND_ISP_SLAVE_ADDRESS & 0xFE)
#define GET_BG_ISP_SUBADDRESS()                     (MCU_FD93_BACKGROUND_ISP_SUB_ADDRESS)
#define GET_BG_ISP_ISP_CHANNEL()                    (MCU_FD90_BACKGROUND_ISP_CTRL & 0x0E)
#endif

#if(_USB3_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Macros of USB Repeater IRQ Control
//--------------------------------------------------
#if((_USB3_RETIMER_MAC_SUPPORT == _ON) || (_USB3_REDRIVER_MAC_SUPPORT == _ON))
#define SET_REPEATER_GLOBAL_IRQ_ENABLE(x)           {\
                                                        if((x) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_REDRIVER);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_REDRIVER);\
                                                        }\
                                                    }
#endif
#endif  // End of #if(_USB3_REPEATER_SUPPORT == _ON)

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
//--------------------------------------------------
// Macros of USB Billboard IRQ Control
//--------------------------------------------------
#define SET_BILLBOARD_GLOBAL_IRQ_ENABLE(x)          {\
                                                        if((x) == _ENABLE)\
                                                        {\
                                                        ScalerCpuHalEnableIRQ(_IRQN_ECDSA_PMCI2C_BB);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_ECDSA_PMCI2C_BB);\
                                                        }\
                                                    }
#endif

#define SET_INTERRUPT_GLOBAL_ENABLE_STATUS(status)  {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            CPU32_ENABLE_GLOBAL_IRQ();\
                                                        }\
                                                        else\
                                                        {\
                                                            CPU32_DISABLE_GLOBAL_IRQ();\
                                                        }\
                                                    }

#define GET_INTERRUPT_GLOBAL_ENABLE_STATUS()        (CPU32_GET_GLOBAL_IRQ_STATUS())

#if(_FW_CPU32_USE_INT31_FOR_SCALER_INT == _ON)
#define SET_SCALER_INT_ENABLE_STATUS(status)        {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_SCALER_ALL);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_SCALER_ALL);\
                                                        }\
                                                    }
#else
#define SET_SCALER_INT_ENABLE_STATUS(status)        {\
                                                        ScalerGlobalSetInt31EnableStatus((status));\
                                                    }
#endif

#define SET_DDC_INT_ENABLE_STATUS(status)           {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_DDC);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_DDC);\
                                                        }\
                                                    }

#define SET_WDT_TIMER_INT_ENABLE_STATUS(status)     {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_TIMER2);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_TIMER2);\
                                                        }\
                                                    }

#if(_USB3_REPEATER_SUPPORT == _ON)
#define SET_USB3_INT_ENABLE_STATUS(status)          {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_REDRIVER);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_REDRIVER);\
                                                        }\
                                                    }
#else
#define SET_USB3_INT_ENABLE_STATUS(status)
#endif

#define SET_TIMER0_INT_ENABLE_STATUS(status)        {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_TIMER0);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_TIMER0);\
                                                        }\
                                                    }

#define SET_TIMER1_INT_ENABLE_STATUS(status)        {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_TIMER1);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_TIMER1);\
                                                        }\
                                                    }

#define SET_SYSTICK_INT_ENABLE_STATUS(status)       {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerSysTickResumeTick();\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerSysTickSuspendTick();\
                                                        }\
                                                    }

#if(_FW_CPU32_USE_INT31_FOR_SCALER_INT == _ON)
#define SET_DP_INT_ENABLE_STATUS(status)            {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerGlobalSetInt31EnableStatus(status);\
                                                        }\
                                                        SET_SCALER_INT_ENABLE_STATUS(status);\
                                                    }

#define SET_TMDS_INT_ENABLE_STATUS(status)          {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerGlobalSetInt31EnableStatus(status);\
                                                        }\
                                                        SET_SCALER_INT_ENABLE_STATUS(status);\
                                                    }

#define SET_IMD_INT_ENABLE_STATUS(status)           {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerGlobalSetInt31EnableStatus(status);\
                                                        }\
                                                        SET_SCALER_INT_ENABLE_STATUS(status);\
                                                    }

#define SET_TYPEC_INT_ENABLE_STATUS(status)         (SET_SCALER_INT_ENABLE_STATUS(status))
#else
#define SET_DP_INT_ENABLE_STATUS(status)            {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_DP_HIGH);\
                                                            ScalerCpuHalEnableIRQ(_IRQN_DP_LOW);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_DP_HIGH);\
                                                            ScalerCpuHalDisableIRQ(_IRQN_DP_LOW);\
                                                        }\
                                                    }

#define SET_TMDS_INT_ENABLE_STATUS(status)          {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_HDMI_HIGH);\
                                                            ScalerCpuHalEnableIRQ(_IRQN_HDMI_LOW);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_HDMI_HIGH);\
                                                            ScalerCpuHalDisableIRQ(_IRQN_HDMI_LOW);\
                                                        }\
                                                    }

#define SET_IMD_INT_ENABLE_STATUS(status)           {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_IMD_EVENT);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_IMD_EVENT);\
                                                        }\
                                                    }

#if((_HW_EMB_TYPE_C_0_SUPPORT == _ON) || (_HW_EMB_TYPE_C_1_SUPPORT == _ON) || (_HW_EMB_TYPE_C_2_SUPPORT == _ON) || (_HW_EMB_TYPE_C_3_SUPPORT == _ON))
#define SET_TYPEC_INT_ENABLE_STATUS(status)         {\
                                                        if((status) == _ENABLE)\
                                                        {\
                                                            ScalerCpuHalEnableIRQ(_IRQN_PDCC_HIGH);\
                                                            ScalerCpuHalEnableIRQ(_IRQN_PDCC_LOW);\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerCpuHalDisableIRQ(_IRQN_PDCC_HIGH);\
                                                            ScalerCpuHalDisableIRQ(_IRQN_PDCC_LOW);\
                                                        }\
                                                    }
#else
#define SET_TYPEC_INT_ENABLE_STATUS(status)         {}
#endif
#endif

#define SET_INTERRUPT_ENABLE_STATUS(id, status)     {\
                                                        if(((id) & _INT_EXINT_0) != 0) {SET_SCALER_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_EXINT_1) != 0) {SET_DDC_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_EXINT_2) != 0) {SET_WDT_TIMER_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_EXINT_3) != 0) {SET_USB3_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_EXINT_4) != 0) {}\
                                                        if(((id) & _INT_EXINT_5) != 0) {}\
                                                        if(((id) & _INT_TIMER_0) != 0) {SET_TIMER0_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_TIMER_1) != 0) {SET_TIMER1_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_TIMER_2) != 0) {SET_SYSTICK_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_DP) != 0) {SET_DP_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_TMDS) != 0) {SET_TMDS_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_IMD) != 0) {SET_IMD_INT_ENABLE_STATUS(status);}\
                                                        if(((id) & _INT_TYPEC) != 0) {SET_TYPEC_INT_ENABLE_STATUS(status);}\
                                                    }

#define CLEAR_INTERRUPT_FLAG(enumInterruptId)

#define CLR_MCU_TIMER_OVERFLOW_STATUS(id)           {\
                                                        if((id) == _TIMER_0) {ScalerTimerAckINTFlag(_CPU_TIMER_0);}\
                                                        if((id) == _TIMER_1) {ScalerTimerAckINTFlag(_CPU_TIMER_1);}\
                                                        if((id) == _TIMER_2) {ScalerSysTickAckFlag();}\
                                                    }
//--------------------------------------------------
// Macros of timer
//--------------------------------------------------
#define GET_MCU_TIMER_RANDOM_BYTE()                 ((BYTE)(SYSTICK_GET_CURRENT_VALUE() & 0xFF))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of interrupts
//--------------------------------------------------
typedef enum
{
    _INT_EXINT_0 = _BIT0,
    _INT_EXINT_1 = _BIT1,
    _INT_EXINT_2 = _BIT2,
    _INT_EXINT_3 = _BIT3,
    _INT_EXINT_4 = _BIT4,
    _INT_EXINT_5 = _BIT5,

    _INT_TIMER_0 = _BIT6,
    _INT_TIMER_1 = _BIT7,
    _INT_TIMER_2 = _BIT8,

    _INT_SERIAL_0 = _BIT9,
    _INT_SERIAL_1 = _BIT10,

    _INT_DP = _BIT11,
    _INT_TMDS = _BIT12,
    _INT_IMD = _BIT13,
    _INT_TYPEC = _BIT14,

    _INT_ALL = 0xFFFF,
} EnumInterruptType;

typedef enum
{
    _TYPE_C_INT_0 = 0x00,
    _TYPE_C_INT_1 = 0x01,
    _TYPE_C_INT_2 = 0x02,
    _TYPE_C_INT_3 = 0x03,
    _TYPE_C_INT_4 = 0x04,
    _TYPE_C_INT_5 = 0x05,
}EnumTypeCIntGroup;

typedef enum
{
    _REPEATER_INT_0 = 0x00,
    _REPEATER_INT_1 = 0x01,
    _REPEATER_INT_2 = 0x02,
    _REPEATER_INT_3 = 0x03,
    _REPEATER_INT_4 = 0x04,
    _REPEATER_INT_5 = 0x05,
}EnumRepeaterIntGroup;

typedef enum
{
    _BILLBOARD_INT_0 = 0x00,
    _BILLBOARD_INT_1 = 0x01,
    _BILLBOARD_INT_2 = 0x02,
    _BILLBOARD_INT_3 = 0x03,
    _BILLBOARD_INT_4 = 0x04,
    _BILLBOARD_INT_5 = 0x05,
}EnumBillboardIntGroup;

//--------------------------------------------------
// Definitions of DDCCI Command Source Type
//--------------------------------------------------
typedef enum
{
    _DDCCI_CMD_SRC_I2C = 0x00,
    _DDCCI_CMD_SRC_MST = 0x01,
} EnumDdcciCmdSrc;

//-------------------------------------------------
// Enum Timer
//-------------------------------------------------
typedef enum
{
    _TIMER_0,
    _TIMER_1,
    _TIMER_2,
} EnumTimerId;

typedef struct
{
    WORD usCounter;
    WORD usReloadCounter;
} StructTimerData;


//--------------------------------------------------
// Enumerations of Timer Operation
//--------------------------------------------------
typedef enum
{
    _TIMER_OPERATION_INITIAL_MODE,
    _TIMER_OPERATION_POWER_NORMAL_MODE,
    _TIMER_OPERATION_POWER_SAVING_MODE,
    _TIMER_OPERATION_POWER_SAVING_FAST_MODE,
    _TIMER_OPERATION_POWER_IDLE_MODE,
    _TIMER_OPERATION_OSD_MODE,
} EnumScalerTimerOperationMode;

//-------------------------------------------------
// Enum Data Exchange Kernel Type Group
//-------------------------------------------------
typedef enum
{
    //--------------------------------------------------
    // Data Exchange Command None
    //--------------------------------------------------
    _DATA_EXCHANGE_KERNEL_DATA_NONE = 0x00,
    _DATA_EXCHANGE_KERNEL_DATA_TIMING_INFO_0,
    _DATA_EXCHANGE_KERNEL_DATA_TIMING_INFO_1,
    _DATA_EXCHANGE_KERNEL_DATA_TIMING_INFO_2,
    _DATA_EXCHANGE_KERNEL_DATA_TIMING_INFO_3,
    _DATA_EXCHANGE_KERNEL_DATA_FREESYNC_ENABLE,
} EnumDataExchangeKernelDataType;

typedef enum
{
    //--------------------------------------------------
    // Data Exchange Command None
    //--------------------------------------------------
    _DATA_EXCHANGE_KERNEL_EVENT_NONE = 0x00,
    _DATA_EXCHANGE_KERNEL_EVENT_POWER_TARGET_STATUS,
    _DATA_EXCHANGE_KERNEL_EVENT_CHECK_POWER_TARGET_STATUS,
    _DATA_EXCHANGE_KERNEL_EVENT_CHECK_BACKLIGHT_ON,
    _DATA_EXCHANGE_KERNEL_EVENT_BACKLIGHT_OFF,
    _DATA_EXCHANGE_KERNEL_EVENT_CHECK_BACKLIGHT_OFF,
    _DATA_EXCHANGE_KERNEL_EVENT_PANEL_OFF,
    _DATA_EXCHANGE_KERNEL_EVENT_CHECK_PANEL_OFF,
    _DATA_EXCHANGE_KERNEL_EVENT_ADJUST_OD_GAIN,
    _DATA_EXCHANGE_KERNEL_EVENT_CHECK_ADJUST_OD_GAIN,
    _DATA_EXCHANGE_KERNEL_EVENT_ADJUST_OD_ENABLE,
    _DATA_EXCHANGE_KERNEL_EVENT_CHECK_ADJUST_OD_ENABLE,
} EnumDataExchangeKernelEventType;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile EnumDdcciCmdSrc g_penumMcuDdcciCommandSrc[];

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
extern volatile BYTE g_ucMcuReceiveDdcci0CmdNotFinish;
#endif

extern BYTE g_pucMcuDdcciRetry[_MULTI_DISPLAY_MAX];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMcuInitial(void);
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
extern void ScalerMcuDdcci0ClearWrongIntFlag(void);
#endif
#endif

extern EnumInputPort ScalerMcuDdcciGetInputPort(EnumDDCCIPort enumDdcciChannel);

extern void ScalerMcuDdcciSelectDdcChannel(EnumDDCCIPort enumDdcciChannel, EnumInputPort enumInputPort);

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern BYTE ScalerMcuDdcci0IntGetData(BYTE *pucReadArray, BYTE ucBufLength);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern BYTE ScalerMcuDdcci1IntGetData(BYTE *pucReadArray);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
extern BYTE ScalerMcuDdcci2IntGetData(BYTE *pucReadArray);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
extern BYTE ScalerMcuDdcci3IntGetData(BYTE *pucReadArray);
#endif

#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
extern bit ScalerMcuDdcciColorCalibrationCheckDisplayMode(void);
extern void ScalerMcuDdcciReleaseScl(void);
#endif

extern BYTE ScalerMcuDdcciGetBufferSize(void);

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
extern void ScalerMcuDdcciAutoSwitchEnableChannel(void);
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if((_OGC_FUNCTION == _OFF) && (_OGC_DICOM_FUNCTION == _OFF) && (_OCC_FUNCTION == _OFF))
extern void ScalerMcuDdcciAutoSwitchDisableInactiveChannel(void);
#endif
#endif
#endif
extern void ScalerMcuFlashClockGroupSetting(EnumClkSel enumClock);


#if(_LOW_SPEED_ADC_SUPPORT == _ON)
extern void ScalerMcuSarAdcClkSel(EnumClkSel enumClock);
#if(_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT == _ON)
extern void ScalerMcuSarAdcPowerControl(EnumAdcPowerControl enumAdcPowerControl, EnumAdcPowerDelay enumAdcPowerDelay);
#endif

#if((_DP_SUPPORT == _ON) && (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern EnumDpCableIDResult ScalerMcuSarAdcDpCableIdDetect(EnumInputPort enumInputPort);
#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))

#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
extern void ScalerMcuAdcLsAdcDetectIntInitial(void);
extern void ScalerMcuAdcLsAdcInOutCompIntControl(BYTE ucChannel, EnumAdcIntControl enumAdcIntControl);
extern void ScalerMcuAdcLsAdcInOutCompIntSetting(BYTE ucChannel, WORD usHigh, WORD usLow);
extern void ScalerMcuAdcLsAdcDetectIntHandler_EXINT0(void);
#endif
#endif // End of #if(_LOW_SPEED_ADC_SUPPORT == _ON)

#if(_PWM_FUNCTION_SUPPORT == _ON)
extern void ScalerMcuPwmClockSel(EnumClkSel enumClock);
#endif

#if(_SW_IIC_SUPPORT == _ON)
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuIICWritePolling(BYTE ucSlaveAddr);
#endif
extern bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif

#if(_HW_IIC_SUPPORT == _ON)
extern void ScalerMcuHwIICSetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuHwIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
extern bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
extern void ScalerMcuHwIIC1SlaveEnableIrq(bit bEn);
extern void ScalerMcuHwIIC1SlaveHandler_EXINT1(void);
extern void ScalerMcuHwIIC1SlaveIntGetData_EXINT1(BYTE *pucReadArray);
extern void ScalerMcuHwIIC1SlaveProc_EXINT1(void);
#endif // End of #if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
#endif // End of #if(_HW_IIC_1_SUPPORT == _ON)

#if(_TYPEC_IIC_SUPPORT == _ON)
extern void ScalerMcuTypecIICConfigSetting(void);
extern void ScalerMcuTypecIICSetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuTypecIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
extern bit ScalerMcuTypecIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
#endif

extern void ScalerMcuPwmControl(EnumPowerStatus enumPowStatus);

extern void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode);
extern void ScalerMcuDdcDebounceSel(EnumClkSel enumClock);
extern void ScalerMcuDdcDebounceSelByPort(EnumInputPort enumInputPort, EnumDdcDbnSelMode enumDdcDbnSelMode);
extern void ScalerMcuDdcRamEnable(void);
extern void ScalerMcuSetISPChannel(WORD usISPChannel);
extern void ScalerMcuSetISPSlaveAddr(BYTE ucISPStatus);

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void ScalerMcuDdcSetSegmentSwitch(EnumInputPort enumInputPort, bit bSelect);
#endif

extern void ScalerMcuDdcSetForceNack(EnumInputPort enumInputPort, bit bSelect);

#if(_HDMI_SUPPORT == _ON)
extern bit ScalerMcuDdcGetForceNackStatus(EnumInputPort enumInputPort);
#endif

extern void ScalerMcuDdcciSendData(EnumDDCCIPort enumDdcciChannel, BYTE *pucWriteArray);

#if(_PWM_FUNCTION_SUPPORT == _ON)
extern void ScalerMcuPwmAdjustResetByDvs(BYTE ucPwmType, bit bStatus);
extern bit ScalerMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency);
#if(_PWM_BYPASS_MODE_SUPPORT == _ON)
extern void ScalerMcuPwmByPassModeSettingFrequency(BYTE ucPwmType, WORD usTotalcont);
#endif
#endif

#if(_UART_SUPPORT == _ON)
extern EnumClkSel ScalerMcuUartGetUartClkSource(void);
#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
extern void ScalerMcuUartExt0SetBaudRate(EnumClkSel enumClock, DWORD ulBaudRate);
extern void ScalerMcuUartExt0Initial(void);
extern bit ScalerMcuUartExt0CheckReceiveStatus(void);
extern EnumMcuExtUartIntID ScalerMcuUartExt0CheckIntID(void);
extern BYTE ScalerMcuUartExt0GetByte(void);
extern bit ScalerMcuUartExt0SetByte(BYTE ucValue);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
extern void ScalerMcuUartExt1SetBaudRate(EnumClkSel enumClock, DWORD ulBaudRate);
extern void ScalerMcuUartExt1Initial(void);
extern bit ScalerMcuUartExt1CheckReceiveStatus(void);
extern EnumMcuExtUartIntID ScalerMcuUartExt1CheckIntID(void);
extern BYTE ScalerMcuUartExt1GetByte(void);
extern bit ScalerMcuUartExt1SetByte(BYTE ucValue);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
extern void ScalerMcuUartExt2SetBaudRate(EnumClkSel enumClock, DWORD ulBaudRate);
extern void ScalerMcuUartExt2Initial(void);
extern bit ScalerMcuUartExt2CheckReceiveStatus(void);
extern EnumMcuExtUartIntID ScalerMcuUartExt2CheckIntID(void);
extern BYTE ScalerMcuUartExt2GetByte(void);
extern bit ScalerMcuUartExt2SetByte(BYTE ucValue);
#endif
#endif

extern void ScalerMcuIromAccess(DWORD ulStartAddr, WORD usLength, BYTE *pucArray);
extern bit ScalerMcuFlashCRCCal(DWORD ulStartAddr, DWORD ulEndAddr, BYTE *pucCRCResult);

extern void ScalerMcu1usDelayCalc(EnumClkSel enumClock);
extern void ScalerMcuIntPriorityInit(void);
extern WORD ScalerMcuGetIspChannelEnableStatus(void);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
extern bit ScalerMcuDataExchangeSendData(BYTE ucCmdTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray);
extern bit ScalerMcuDataCheckSendDataDone(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucPollingInterval);
#endif

extern bit ScalerMcuCheckHwBW32Avaiable(void);

__attribute__((section(".itcm_section.ScalerMcuSetInterruptGlobalEnableStatus")))
extern void ScalerMcuSetInterruptGlobalEnableStatus(bit bEnable);

