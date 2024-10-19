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
// ID Code      : ScalerBW32Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HW_CPU32_BW32_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

// BW32_MBIST_MODE reg bit define
#define _BW32BUF_DRF_TEST_RESUME        _BIT12
#define _BW32BUF_DRF_BIST_MODE          _BIT11
#define _BW32BUF_DRF_START_PAUSE        _BIT10
#define _BW32BUF_DRF_BIST_DONE          _BIT9
#define _BW32BUF_DRF_BIST_FAIL          _BIT8
#define _BIST_RESETN                    _BIT7
#define _BIST_CLK_EN                    _BIT6
#define _BW32BUF_BIST_MODE              _BIT2
#define _BW32BUF_BIST_DONE              _BIT1
#define _BW32BUF_BIST_FAIL              _BIT0

#define _MAX_BW32_LEN                   124
#define _MAX_BW32_NUM_CMD               ((1UL << 12) - 1)    // 4095

#define _BW32_CMD_CIRCULAR_QUEUE_SIZE   8

#define WAIT_BW32_IDLE()                {\
                                            while(ScalerBW32ChkAllDone() != 0){};\
                                        }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of BW32 callback functions
//--------------------------------------------------
typedef enum
{
    _BW32_CALLBACK_NULL,
    _BW32_CALLBACK_SPI_DIMMING_LD_SRAM,
} EnumBW32CallBackFuncId;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************



//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerBW32_IRQHandler(void);
extern bit ScalerBW32Error_Handler(void);

extern bit ScalerBW32LaunchCmdX(BYTE ucTotalCmdXcnt, StructBW32CmdInfo *pstBW32CmdInfo, WORD usWaitResourceLockTimeoutMS, bit bWaitExecuteDone, WORD usWaitExeTimeoutMS, EnumBW32CallBackFuncId enumCallBackFuncId);

extern bit ScalerBW32LaunchCmdXAfterIDomainEvent(StructBW32IDomainCmdInfo *pstBW32IDomainCmdInfo, WORD usWaitResourceLockTimeoutMS, WORD usWaitExeTimeoutMS);

extern void ScalerBW32EnableFinishINT(void);
extern void ScalerBW32DisableFinishINT(void);
extern DWORD ScalerBW32GetFinishINTFlag(void);
extern void ScalerBW32AckFinishINTFlag(void);

extern void ScalerBW32SetCmdTriggerSource(EnumBW32CmdX enumBW32CmdX, EnumBW32TriggerSource enumBW32TriggerSource);
extern void ScalerBW32SetLastBlockValidCmdNum(EnumBW32CmdX enumBW32CmdX, EnumBW32CmdFormat enumBW32CmdFormat, DWORD ulLastBlockValidCmdNum);

extern DWORD ScalerBW32ChkCmdXManualDone(EnumBW32CmdX enumBW32CmdX);
extern DWORD ScalerBW32ChkCmdXDomainEventDone(EnumBW32CmdX enumBW32CmdX);
extern DWORD ScalerBW32ChkAllDone(void);

extern DWORD ScalerBW32GetFifoWaterLevelSetting(void);
extern DWORD ScalerBW32GetDdrReadOnceNumSetting(void);

#endif  // End of #if(_HW_CPU32_BW32_SUPPORT == _ON)
