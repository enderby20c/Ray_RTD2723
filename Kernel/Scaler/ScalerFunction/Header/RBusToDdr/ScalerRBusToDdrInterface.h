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
// ID Code      : ScalerRBusToDdrInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _MAX_RBUS2DDR_LEN                   124
#define _MAX_RBUS2DDR_NUM_CMD               ((1UL << 12) - 1)    // 4095

#define _RBUS2DDR_CMD_CIRCULAR_QUEUE_SIZE   8


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of RBus To DDR callback functions
//--------------------------------------------------
typedef enum
{
    _RBUS_TO_DDR_CALLBACK_NULL,
} EnumRBusToDdrCallbackFuncId;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************



//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerRBusToDdr_IRQHandler(void);
extern bit ScalerRBusToDdrError_Handler(void);

extern bit ScalerRBusToDdrLaunchCmdX(BYTE ucTotalCmdXcnt, StructRBus2DdrCmdInfo *pstRbus2DdrCmdInfo, WORD usWaitResourceLockTimeoutMS, bit bWaitExecuteDone, WORD usWaitExeTimeoutMS, EnumRBusToDdrCallbackFuncId enumCallbackFuncId);
extern bit ScalerRBusToDdrLaunchCmdXAfterIDomainEvent(StructRBus2DdrIDomainCmdInfo *pstRBus2DdrIDomainCmdInfo, WORD usWaitResourceLockTimeoutMS, WORD usWaitExeTimeoutMS);

extern DWORD ScalerRBusToDdrCmdQueueGetSize(void);
extern void ScalerRBusToDdrCmdQueueReset(void);

extern void ScalerRBusToDdrEnableFinishINT(void);
extern void ScalerRBusToDdrDisableFinishINT(void);
extern DWORD ScalerRBusToDdrGetFinishINTFlag(void);
extern void ScalerRBusToDdrAckFinishINTFlag(void);

extern void ScalerRBusToDdrSetCmdTriggerSource(EnumRBus2DdrCmdX enumRBus2DdrCmdX, EnumRBus2DdrTriggerSource enumRBus2DdrTriggerSource);

extern DWORD ScalerRBusToDdrChkCmdXManualDone(EnumRBus2DdrCmdX enumRBus2DdrCmdX);
extern DWORD ScalerRBusToDdrChkCmdXDomainEventDone(EnumRBus2DdrCmdX enumRbus2DdrCmdX);
extern DWORD ScalerRBusToDdrChkAllDone(void);

extern DWORD ScalerRBusToDdrGetDdrWriteOnceNumSetting(void);

#endif
