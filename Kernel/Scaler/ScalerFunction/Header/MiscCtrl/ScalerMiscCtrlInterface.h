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
// ID Code      : ScalerMiscCtrlInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// CPU Misc Control Related Enum
//--------------------------------------------------
typedef enum
{
    _CPU_CLK_DIV_1 = 0x01,   /*!< cpu_clk = sys32_clk / 1        */
    _CPU_CLK_DIV_2 = 0x02,   /*!< cpu_clk = sys32_clk / 2        */
    _CPU_CLK_DIV_3 = 0x03,   /*!< cpu_clk = sys32_clk / 3        */
    _CPU_CLK_DIV_4 = 0x04,   /*!< cpu_clk = sys32_clk / 4        */
    _CPU_CLK_DIV_5 = 0x05,   /*!< cpu_clk = sys32_clk / 5        */
    _CPU_CLK_DIV_6 = 0x06,   /*!< cpu_clk = sys32_clk / 6        */
    _CPU_CLK_DIV_7 = 0x07,   /*!< cpu_clk = sys32_clk / 7        */
    _CPU_CLK_DIV_8 = 0x08,   /*!< cpu_clk = sys32_clk / 8        */
    _CPU_CLK_DIV_9 = 0x09,   /*!< cpu_clk = sys32_clk / 9        */
    _CPU_CLK_DIV_10 = 0x0A,  /*!< cpu_clk = sys32_clk / 10        */
    _CPU_CLK_DIV_11 = 0x0B,  /*!< cpu_clk = sys32_clk / 11        */
    _CPU_CLK_DIV_12 = 0x0C,  /*!< cpu_clk = sys32_clk / 12        */
    _CPU_CLK_DIV_13 = 0x0D,  /*!< cpu_clk = sys32_clk / 13        */
    _CPU_CLK_DIV_14 = 0x0E,  /*!< cpu_clk = sys32_clk / 14        */
    _CPU_CLK_DIV_15 = 0x0F,  /*!< cpu_clk = sys32_clk / 15        */
}EnumCpuMiscCtrlCpuClkDivider;


typedef enum
{
    _INT_TEST0 = ((1UL) << 0),  /*!< INT Test0 bit    */
    _INT_TEST1 = ((1UL) << 1),  /*!< INT Test1 bit    */
    _INT_TEST2 = ((1UL) << 2),  /*!< INT Test2 bit    */
    _INT_TEST3 = ((1UL) << 3),  /*!< INT Test3 bit    */
}EnumCpuMiscCtrlIntTestIdx;

typedef enum
{
    _BIST_I = 0x00,  /*!< I BIST Test    */
    _BIST_D = 0x01,  /*!< D BIST Test    */
    _BIST_BP = 0x02,  /*!< BP BIST Test    */
}EnumCpuMiscCtrlBistType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

/* CPU1 CLK DIV */
extern void ScalerMiscCtrlCpuSetClkDivider(EnumCpuMiscCtrlCpuClkDivider enumTargetDiv);
extern EnumCpuMiscCtrlCpuClkDivider ScalerMiscCtrlCpuGetClkDivider(void);

/* Notidy INT Control */
#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
extern void ScalerMiscCtrlSetNotifyKCPU(void);
extern DWORD ScalerMiscCtrlChkNotifyFromKCPU(void);
extern void ScalerMiscCtrlAckNotifyFromKCPU(void);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern void ScalerMiscCtrlSetNotifySCPU(void);
extern DWORD ScalerMiscCtrlChkNotifyFromSCPU(void);
extern void ScalerMiscCtrlAckNotifyFromSCPU(void);
#endif
#endif

/* INT Test Control */
extern void ScalerMiscCtrlIntTestxSetEnable(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx);
extern void ScalerMiscCtrlIntTestxSetDisable(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx);
extern void ScalerMiscCtrlIntTestxSetTriggered(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx);
extern void ScalerMiscCtrlIntTestxClearTrigger(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx);
extern DWORD ScalerMiscCtrlIntTestxGetStatus(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx);
extern void ScalerMiscCtrlIntTestxAckStatus(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx);

