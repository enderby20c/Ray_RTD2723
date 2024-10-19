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
// ID Code      : ScalerMcuInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
#define GET_D1_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D1TmdsDdcDetected)
#define SET_D1_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D1TmdsDdcDetected = _TRUE)
#define CLR_D1_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D1TmdsDdcDetected = _FALSE)

#define GET_D2_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D2TmdsDdcDetected)
#define SET_D2_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D2TmdsDdcDetected = _TRUE)
#define CLR_D2_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D2TmdsDdcDetected = _FALSE)

#define GET_D3_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D3TmdsDdcDetected)
#define SET_D3_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D3TmdsDdcDetected = _TRUE)
#define CLR_D3_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D3TmdsDdcDetected = _FALSE)

#define GET_D4_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D4TmdsDdcDetected)
#define SET_D4_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D4TmdsDdcDetected = _TRUE)
#define CLR_D4_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D4TmdsDdcDetected = _FALSE)

#define GET_D5_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D5TmdsDdcDetected)
#define SET_D5_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D5TmdsDdcDetected = _TRUE)
#define CLR_D5_TMDS_DDC_DETECTED()              (g_stMcuDxTmdsDdcDetected.b1D5TmdsDdcDetected = _FALSE)
#endif

//--------------------------------------------------
// Macros of HW IIC Setting
//--------------------------------------------------
#if(_HW_IIC_0_SUPPORT == _ON)
#define _HW_IIC0_SLPC_XTAL                      (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stXtal.ucSLPC)
#define _HW_IIC0_SHPC_XTAL                      (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stXtal.ucSHPC)
#define _HW_IIC0_STA_SUGPIO_C_XTAL              (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stXtal.ucSTA_SUGPIO_C)
#define _HW_IIC0_TOR_XTAL                       (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stXtal.ucTOR)
#define _HW_IIC0_FTPC_XTAL                      (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stXtal.ucFTPC)
#define _HW_IIC0_FD10_XTAL                      (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stXtal.ucFD10)
#if (_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
#define _HW_IIC0_THD_STA_C_XTAL                 (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stXtal.ucTHD_STA_C)
#endif

#define _HW_IIC0_SLPC_IOSC                      (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stIosc.ucSLPC)
#define _HW_IIC0_SHPC_IOSC                      (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stIosc.ucSHPC)
#define _HW_IIC0_STA_SUGPIO_C_IOSC              (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stIosc.ucSTA_SUGPIO_C)
#define _HW_IIC0_TOR_IOSC                       (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stIosc.ucTOR)
#define _HW_IIC0_FTPC_IOSC                      (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stIosc.ucFTPC)
#define _HW_IIC0_FD10_IOSC                      (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stIosc.ucFD10)
#if (_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
#define _HW_IIC0_THD_STA_C_IOSC                 (tHwI2cSetting[g_ucMcuHwI2c0SettingIndex].stIosc.ucTHD_STA_C)
#endif
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
#define _HW_IIC1_SLPC_XTAL                      (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stXtal.ucSLPC)
#define _HW_IIC1_SHPC_XTAL                      (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stXtal.ucSHPC)
#define _HW_IIC1_STA_SUGPIO_C_XTAL              (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stXtal.ucSTA_SUGPIO_C)
#define _HW_IIC1_TOR_XTAL                       (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stXtal.ucTOR)
#define _HW_IIC1_FTPC_XTAL                      (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stXtal.ucFTPC)
#define _HW_IIC1_FD10_XTAL                      (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stXtal.ucFD10)
#if (_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
#define _HW_IIC1_THD_STA_C_XTAL                 (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stXtal.ucTHD_STA_C)
#endif

#define _HW_IIC1_SLPC_IOSC                      (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stIosc.ucSLPC)
#define _HW_IIC1_SHPC_IOSC                      (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stIosc.ucSHPC)
#define _HW_IIC1_STA_SUGPIO_C_IOSC              (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stIosc.ucSTA_SUGPIO_C)
#define _HW_IIC1_TOR_IOSC                       (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stIosc.ucTOR)
#define _HW_IIC1_FTPC_IOSC                      (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stIosc.ucFTPC)
#define _HW_IIC1_FD10_IOSC                      (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stIosc.ucFD10)
#if (_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
#define _HW_IIC1_THD_STA_C_IOSC                 (tHwI2cSetting[g_ucMcuHwI2c1SettingIndex].stIosc.ucTHD_STA_C)
#endif
#endif

#if(_TYPEC_IIC_0_SUPPORT == _ON)
#define _TYPEC_IIC0_SLPC_XTAL                   (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stXtal.ucSLPC)
#define _TYPEC_IIC0_SHPC_XTAL                   (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stXtal.ucSHPC)
#define _TYPEC_IIC0_STA_SUGPIO_C_XTAL           (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stXtal.ucSTA_SUGPIO_C)
#define _TYPEC_IIC0_TOR_XTAL                    (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stXtal.ucTOR)
#define _TYPEC_IIC0_FTPC_XTAL                   (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stXtal.ucFTPC)
#define _TYPEC_IIC0_FD10_XTAL                   (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stXtal.ucFD10)
#define _TYPEC_IIC0_THD_STA_C_XTAL              (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stXtal.ucTHD_STA_C)

#define _TYPEC_IIC0_SLPC_IOSC                   (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stIosc.ucSLPC)
#define _TYPEC_IIC0_SHPC_IOSC                   (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stIosc.ucSHPC)
#define _TYPEC_IIC0_STA_SUGPIO_C_IOSC           (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stIosc.ucSTA_SUGPIO_C)
#define _TYPEC_IIC0_TOR_IOSC                    (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stIosc.ucTOR)
#define _TYPEC_IIC0_FTPC_IOSC                   (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stIosc.ucFTPC)
#define _TYPEC_IIC0_FD10_IOSC                   (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stIosc.ucFD10)
#define _TYPEC_IIC0_THD_STA_C_IOSC              (tHwI2cSetting[g_ucMcuTypecI2c0SettingIndex].stIosc.ucTHD_STA_C)
#endif


//--------------------------------------------------
// Macros of 5us Delay
//--------------------------------------------------
#define DELAY_10US()                            {\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                }

#define DELAY_10US_EXINT()                      {\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                }

#define DELAY_15US()                            {\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                }

#define DELAY_15US_EXINT()                      {\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                }

#define DELAY_20US()                            {\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                }

#define DELAY_20US_EXINT()                      {\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                }

#define DELAY_25US()                            {\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                }

#define DELAY_25US_EXINT()                      {\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                }

#define DELAY_30US()                            {\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                }

#define DELAY_30US_EXINT()                      {\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                }

#define DELAY_35US()                            {\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                }

#define DELAY_35US_EXINT()                      {\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                }

#define DELAY_40US()                            {\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                }

#define DELAY_40US_EXINT()                      {\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                }

#define DELAY_45US()                            {\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                    DELAY_5US();\
                                                }

#define DELAY_45US_EXINT()                      {\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                    DELAY_5US_EXINT();\
                                                }

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _SYSTICK_TIMER_US                       (250)   // 250us
#else
#define _SYSTICK_TIMER_US                       (1000)  // 1000us
#endif

// Delay 50~1000 us
#define DELAY_XUS(N)                            (ScalerMcuDelayXus(N))
#define DELAY_XUS_EXINT(N)                      (DELAY_XUS(N))

//--------------------------------------------------
// Macros of SW IIC Status
//--------------------------------------------------
#if(_SW_IIC_SUPPORT == _ON)

#if(_SW_IIC_CLK_DIV == _DIV_1)
#define SW_IIC_DELAY_TIME()                     {DELAY_5US();}
#elif(_SW_IIC_CLK_DIV == _DIV_2)
#define SW_IIC_DELAY_TIME()                     {DELAY_10US();}
#elif(_SW_IIC_CLK_DIV == _DIV_3)
#define SW_IIC_DELAY_TIME()                     {DELAY_15US();}
#elif(_SW_IIC_CLK_DIV == _DIV_4)
#define SW_IIC_DELAY_TIME()                     {DELAY_20US();}
#elif(_SW_IIC_CLK_DIV == _DIV_5)
#define SW_IIC_DELAY_TIME()                     {DELAY_25US();}
#elif(_SW_IIC_CLK_DIV == _DIV_6)
#define SW_IIC_DELAY_TIME()                     {DELAY_30US();}
#else
#define SW_IIC_DELAY_TIME()                     {DELAY_35US();}
#endif

#endif

//--------------------------------------------------
// Define for interrupt priority
//--------------------------------------------------

//--------------------------------------------------
// MACRO for MCU Clock Setting
//--------------------------------------------------
#define GET_REG_MCU_CLK_SEL()                   ((ScalerGetBit(PFF_ED_MCU_CONTROL, _BIT1) == 0x00) ? GET_REG_XTAL_CLK_SEL() : _M2PLL_CLK)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Structure of TMDS DDC Detect Flag
//--------------------------------------------------
typedef struct
{
    BYTE b1D1TmdsDdcDetected : 1;
    BYTE b1D2TmdsDdcDetected : 1;
    BYTE b1D3TmdsDdcDetected : 1;
    BYTE b1D4TmdsDdcDetected : 1;
    BYTE b1D5TmdsDdcDetected : 1;
} StructDxTmdsDdcDetected;
#endif

//--------------------------------------------------
// Enumerations of DDCRAM Addr Select
//--------------------------------------------------
typedef enum
{
    _DDCRAM_TOP_ADDR,
    _DDCRAM_BOTTOM_ADDR,
} EnumDDCAddrType;

//--------------------------------------------------
// Enumerations of DDC0/1 Select
//--------------------------------------------------
typedef enum
{
    _D0_DDCRAM,
    _D1_DDCRAM,
} EnumD0D1DDCRAMSelect;


//--------------------------------------------------
// Enumerations of CPU Busy Loop CNT
//--------------------------------------------------
typedef enum
{
#if(_CPU32_IP == _CPU32_IP_RX3081)
    _IOSC_BUSY_LOOP_1US_CNT = 4,

#if(_EXT_XTAL == _XTAL14318K)
    _XTAL_BUSY_LOOP_1US_CNT = 2,
#endif
#if(_EXT_XTAL == _XTAL27000K)
    _XTAL_BUSY_LOOP_1US_CNT = 4,
#endif

    _M2PLL_BUSY_LOOP_1US_CNT = 29,
#endif

#if(_CPU32_IP == _CPU32_IP_KR4)
    _IOSC_BUSY_LOOP_1US_CNT = 5,

#if(_EXT_XTAL == _XTAL14318K)
    _XTAL_BUSY_LOOP_1US_CNT = 2,
#endif
#if(_EXT_XTAL == _XTAL27000K)
    _XTAL_BUSY_LOOP_1US_CNT = 4,
#endif

    _M2PLL_BUSY_LOOP_1US_CNT = 34,
#endif


#if(_CPU32_IP == _CPU32_IP_TR9)
    _IOSC_BUSY_LOOP_1US_CNT = 10,    // Using IOSC/XTAL/M2PLL CLK To Get base 1us delay on the counter
#if(_EXT_XTAL == _XTAL14318K)
    _XTAL_BUSY_LOOP_1US_CNT = 6,
#endif
#if(_EXT_XTAL == _XTAL27000K)
    _XTAL_BUSY_LOOP_1US_CNT = 10,
#endif

#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_354M)
    _M2PLL_BUSY_LOOP_1US_CNT = 125,
#endif
#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_480M)
    _M2PLL_BUSY_LOOP_1US_CNT = 170,
#endif
#endif
}EnumDelay1usTuneCnt;

typedef enum
{
#if(_CPU32_IP == _CPU32_IP_RX3081)
    _M2PLL_BUSY_LOOP_DOT2US_CNT = ((_SCPU_SUPPORT == _OFF) ? 6 : 11),
#endif

#if(_CPU32_IP == _CPU32_IP_KR4)
    _M2PLL_BUSY_LOOP_DOT2US_CNT = 6,
#endif

#if(_CPU32_IP == _CPU32_IP_TR9)
    _M2PLL_BUSY_LOOP_DOT2US_CNT = 67,
#endif
} EnumDelayDot2usTuneCnt;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
extern volatile StructDxTmdsDdcDetected g_stMcuDxTmdsDdcDetected;
#endif

#if(_HW_IIC_0_SUPPORT == _ON)
extern BYTE g_ucMcuHwI2c0SettingIndex;
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
extern BYTE g_ucMcuHwI2c1SettingIndex;
#endif

extern EnumIRQnType const tScalerAllIrqUnion[];
extern volatile BYTE g_ucMcuSrcReadDdcciAlready;
extern BYTE g_ppucMcuDdcciGroupRxBackBuf[_MULTI_DISPLAY_MAX][_DDCCI_RXBUF_LENGTH];
extern BYTE g_pucMcuDdcciCmdLengthBack[_MULTI_DISPLAY_MAX];
extern BYTE g_ppucMcuDdcciGroupTxBackBuf[_MULTI_DISPLAY_MAX][_DDCCI_TXBUF_LENGTH];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerMcuGet1usDelayCnt(void);
extern void ScalerMcuDdcciEnable(bit bEn, EnumInputPort enumInputPort);
extern BYTE ScalerMcuGetDdcChannelFromInputPort(EnumInputPort enumInputPort);

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern void ScalerMcuDdcReset(EnumInputPort enumInputPort);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
extern void ScalerMcuDdcClearSclToggleIrqStatus_EXINT0(BYTE ucDDCx);
extern BYTE ScalerMcuDdcGetSclToggleIrqStatus_EXINT0(BYTE ucDDCx);
#endif

#if(_HDMI_SUPPORT == _ON)
extern bit ScalerMcuDdcGetDdcDetectFlag(EnumInputPort enumInputPort);
extern void ScalerMcuDdcClrDdcDetectFlag(EnumInputPort enumInputPort);
extern BYTE ScalerMcuDdcGetSclToggleIrqEnable(BYTE ucDDCx);
extern void ScalerMcuDdcSetSclToggleIrqEnable(BYTE ucDDCx, BYTE ucEnable);
extern BYTE ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(BYTE ucDDCx);
extern void ScalerMcuDdcSetSclToggleIrqEnable_EXINT1(BYTE ucDDCx, BYTE ucEnable);
extern void ScalerMcuDdcClearSclToggleIrqStatus_EXINT1(BYTE ucDDCx);
extern BYTE ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(BYTE ucDDCx);
extern void ScalerMcuDdcSetEdidReadIrqEnable(BYTE ucDDCx, BYTE ucEnable);
#endif

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
extern void ScalerMcuDdcClearSclToggleIrqStatus(BYTE ucDDCx);
#endif

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON) || (_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON))
extern BYTE ScalerMcuDdcGetSclToggleIrqStatus(BYTE ucDDCx);
#endif

extern BYTE ScalerMcuDdcramBlockSel(DWORD ulDdcramStartAddr);

#if(_CPU32_IP == _CPU32_IP_RX3081)
extern void ScalerMcuInitial3081(void);
#endif

#if(_CPU32_IP == _CPU32_IP_KR4)
extern void ScalerMcuInitialKR4(void);
#endif

#if(_CPU32_IP == _CPU32_IP_TR9)
extern void ScalerMcuInitialTR9(void);
#endif

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
extern void ScalerMcuFlashHighByteSet(BYTE ucHighByte);
#endif

__attribute__((section(".itcm_section.ScalerMcuDelayDot2usPN")))
extern void ScalerMcuDelayDot2usPN(void);
