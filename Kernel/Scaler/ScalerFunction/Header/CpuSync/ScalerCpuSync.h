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
// ID Code      : ScalerCpuSync.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_CPU_SYNC_H__
#define __SCALER_CPU_SYNC_H__

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Definitions of KCPU Reply SCPU Command Buffer Macro
//--------------------------------------------------
#define GET_SCPU_NOTIFY_INT_CMD_ADDR()                      ((g_stCpuSyncToKcpuCmd.unCmdBody.stReadCmd.pucAddr[0] << 8) + (g_stCpuSyncToKcpuCmd.unCmdBody.stReadCmd.pucAddr[1]))
#define GET_SCPU_NOTIFY_INT_WRITE_DATA(x)                   (g_stCpuSyncToKcpuCmd.unCmdBody.stFlashWriteCmd.pucWriteData[x])

#define SCPU_CMD_READ_DWORD_DATA()                          {\
                                                                g_stCpuSyncToKcpuCmdReply.unCmdBody.stReadReplyCmd.pucReadData[0] = ScalerGetByte(GET_SCPU_NOTIFY_INT_CMD_ADDR() + 3);\
                                                                g_stCpuSyncToKcpuCmdReply.unCmdBody.stReadReplyCmd.pucReadData[1] = ScalerGetByte(GET_SCPU_NOTIFY_INT_CMD_ADDR() + 2);\
                                                                g_stCpuSyncToKcpuCmdReply.unCmdBody.stReadReplyCmd.pucReadData[2] = ScalerGetByte(GET_SCPU_NOTIFY_INT_CMD_ADDR() + 1);\
                                                                g_stCpuSyncToKcpuCmdReply.unCmdBody.stReadReplyCmd.pucReadData[3] = ScalerGetByte(GET_SCPU_NOTIFY_INT_CMD_ADDR());\
                                                            }

#define SCPU_CMD_WRITE_DWORD_DATA()                         {\
                                                                ScalerSetByte(GET_SCPU_NOTIFY_INT_CMD_ADDR() + 3, GET_SCPU_NOTIFY_INT_WRITE_DATA(3));\
                                                                ScalerSetByte(GET_SCPU_NOTIFY_INT_CMD_ADDR() + 2, GET_SCPU_NOTIFY_INT_WRITE_DATA(2));\
                                                                ScalerSetByte(GET_SCPU_NOTIFY_INT_CMD_ADDR() + 1, GET_SCPU_NOTIFY_INT_WRITE_DATA(1));\
                                                                ScalerSetByte(GET_SCPU_NOTIFY_INT_CMD_ADDR(), GET_SCPU_NOTIFY_INT_WRITE_DATA(0));\
                                                            }

//--------------------------------------------------
// Definitions of KCPU Receive SCPU Command Buffer Macro
//--------------------------------------------------
#define GET_SCPU_NOTIFY_INT_WRITE_MASK_BIT()                (g_stCpuSyncToKcpuCmd.unCmdBody.stWriteXDataBitCmd.ucMaskBit)
#define GET_SCPU_NOTIFY_INT_WRITE_ASSERT_BIT()              (g_stCpuSyncToKcpuCmd.unCmdBody.stWriteXDataBitCmd.ucAssertBit)
#define GET_SCPU_NOTIFY_INT_FLASH_WRITE_BANK()              (g_stCpuSyncToKcpuCmd.unCmdBody.stFlashWriteCmd.pucAddr[0])
#define GET_SCPU_NOTIFY_INT_FLASH_WRITE_ADDR()              ((g_stCpuSyncToKcpuCmd.unCmdBody.stFlashWriteCmd.pucAddr[1] << 8) + (g_stCpuSyncToKcpuCmd.unCmdBody.stFlashWriteCmd.pucAddr[2]))
#define GET_SCPU_NOTIFY_INT_FLASH_WRITE_LENGTH()            ((WORD)(g_stCpuSyncToKcpuCmd.unCmdBody.stFlashWriteCmd.ucLength))
#define GET_SCPU_NOTIFY_INT_FLASH_WRITE_DATA_ADDR()         (g_stCpuSyncToKcpuCmd.unCmdBody.stFlashWriteCmd.pucWriteData)
#define GET_SCPU_NOTIFY_INT_FLASH_WRITE_EN_FLASH_SR()       (g_stCpuSyncToKcpuCmd.unCmdBody.stFlashWriteCmd.bEnFlashSR)
#define GET_SCPU_NOTIFY_INT_FLASH_WRITE_DIS_FLASH_SR()      (g_stCpuSyncToKcpuCmd.unCmdBody.stFlashWriteCmd.bDisFlashSR)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern void ScalerCpuSyncColorHandler(void);

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
extern void ScalerCpuSyncFlashWriteHandler(void);
extern void ScalerCpuSyncFlashPageEraseHandler(void);
#endif

#endif

#endif // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))


#endif // End of #ifndef __SCALER_CPU_SYNC_H__
