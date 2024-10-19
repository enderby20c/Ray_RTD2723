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
// ID Code      : ScalerScpuSyncInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Send SCPU Request IRQ to Notify KCPU
//--------------------------------------------------
#define SET_SCPU_REQUEST_IRQ_TO_KCPU()                      (ScalerMiscCtrlSetNotifyKCPU())

#define GET_KCPU_NOTIFY_INT_CMD_TYPE()                      (g_stCpuSyncToScpuCmd.stCmdHeader.ucCmdType)
#define ACK_KCPU_NOTIFY_INT_CMD()                           (g_stCpuSyncToScpuCmdReply.ucAckCmdSeqNum = g_stCpuSyncToScpuCmd.stCmdHeader.ucCmdSeqNum)

//--------------------------------------------------
// CPU Communication Command Setting
//--------------------------------------------------
#define CLR_KCPU_NOTIFY_INT_MORE_PROCESS_FLAG()             (g_stScpuSyncCmdInfo.b1CpuIntMoreProcessFlag = _FALSE)
#define SET_KCPU_NOTIFY_INT_MORE_PROCESS_FLAG()             (g_stScpuSyncCmdInfo.b1CpuIntMoreProcessFlag = _TRUE)
#define GET_KCPU_NOTIFY_INT_MORE_PROCESS_FLAG()             (g_stScpuSyncCmdInfo.b1CpuIntMoreProcessFlag)

// CPU Communication Command Format:
//
// CMD_BUF_0:
//    CMD_BUF_0[7:6]:Reserved
//    CMD_BUF_0[ 5 ]:0:8051->CPU32 , 1:CPU32->8051
//    CMD_BUF_0[4:0]:Main Cmd Index(CmdSeqNum)
//
// CMD_BUF_1:
//        SEND  :Cmd Sequantial Num
// CMD_BUF_2~CMD_BUF_9:sub cmd data....
//
// CMD_BUF_15: XXXExecCmdSeqNum

// DW8051 to CPU32 cmd
// #define _CPU_CMD_R_32B_REG      (0x00+1UL)
//    SEND:(KCPU -> SCPU)
//    MCU_SIDE_BUF_0:_CPU_CMD_R_32B_REG
//    MCU_SIDE_BUF_1:McuExecCmdSeqNum
//    MCU_SIDE_BUF_2:ADDR[31:24]
//    MCU_SIDE_BUF_3:ADDR[23:16]
//    MCU_SIDE_BUF_4:ADDR[15:8]
//    MCU_SIDE_BUF_5:ADDR[7:0]
//    MCU_SIDE_BUF_6~MCU_SIDE_BUF_9:0x00
//    ACK:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:R_DATA[31:24]
//    CPU32_SIDE_BUF_1:R_DATA[23:16]
//    CPU32_SIDE_BUF_2:R_DATA[15:8]
//    CPU32_SIDE_BUF_3:R_DATA[7:0]
//    CPU32_SIDE_BUF_15:McuExecCmdSeqNum

// #define _CPU_CMD_W_32B_REG      (0x00+2UL)
//    SEND:(KCPU -> SCPU)
//    MCU_SIDE_BUF_0:_CPU_CMD_W_32B_REG
//    MCU_SIDE_BUF_1:McuExecCmdSeqNum
//    MCU_SIDE_BUF_2:ADDR[31:24]
//    MCU_SIDE_BUF_3:ADDR[23:16]
//    MCU_SIDE_BUF_4:ADDR[15:8]
//    MCU_SIDE_BUF_5:ADDR[7:0]
//    MCU_SIDE_BUF_6:W_DATA[31:24]
//    MCU_SIDE_BUF_7:W_DATA[23:16]
//    MCU_SIDE_BUF_8:W_DATA[15:8]
//    MCU_SIDE_BUF_9:W_DATA[7:0]
//    ACK:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_15:McuExecCmdSeqNum

// #define _CPU_CMD_8051_OTHER     (0x10+0UL)
//    #define _8051_SUBCMD_SHUT_DOWN      (1UL)
//    SEND:(KCPU -> SCPU)
//    MCU_SIDE_BUF_0:_CPU_CMD_8051_OTHER
//    MCU_SIDE_BUF_1:McuExecCmdSeqNum
//    MCU_SIDE_BUF_2:_8051_SUBCMD_SHUT_DOWN
//    MCU_SIDE_BUF_3~MCU_SIDE_BUF_9:user define
//    ACK:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_15:McuExecCmdSeqNum

// #define _CPU_CMD_8051_COLOR
//    SEND:(KCPU -> SCPU)
//    MCU_SIDE_BUF_0:_CPU_CMD_8051_COLOR_XXXXX
//    MCU_SIDE_BUF_1:McuExecCmdSeqNum
//    MCU_SIDE_BUF_2~MCU_SIDE_BUF_14:user define
//    ACK:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_15:McuExecCmdSeqNum



// CPU32 to DW8051 cmd
// #define _CPU_CMD_R_XDATA_BYTE
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_R_XDATA_BYTE
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2:ADDR[15:8]
//    CPU32_SIDE_BUF_3:ADDR[7:0]
//    CPU32_SIDE_BUF_4:0x00
//    CPU32_SIDE_BUF_5:0x00
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_0:DATA
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

// #define _CPU_CMD_W_XDATA_BYTE    (0x20+2UL)
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_W_XDATA_BYTE
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2:ADDR[15:8]
//    CPU32_SIDE_BUF_3:ADDR[7:0]
//    CPU32_SIDE_BUF_4:DATA
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

// #define _CPU_CMD_R_XDATA_WORD    (0x20+3UL)
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_R_XDATA_WORD
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2:ADDR[15:8]
//    CPU32_SIDE_BUF_3:ADDR[7:0]
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_0:DATA[15:8]
//    MCU_SIDE_BUF_1:DATA[7:0]
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

// #define _CPU_CMD_W_XDATA_WORD    (0x20+4UL)
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_W_XDATA_WORD
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2:ADDR[15:8]
//    CPU32_SIDE_BUF_3:ADDR[7:0]
//    CPU32_SIDE_BUF_4:DATA[15:8]
//    CPU32_SIDE_BUF_5:DATA[7:0]
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

// #define _CPU_CMD_R_XDATA_DWORD    (0x20+5UL)
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_R_XDATA_DWORD
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2:ADDR[15:8]
//    CPU32_SIDE_BUF_3:ADDR[7:0]
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_0:DATA[31:24]
//    MCU_SIDE_BUF_1:DATA[23:16]
//    MCU_SIDE_BUF_2:DATA[15:8]
//    MCU_SIDE_BUF_3:DATA[7:0]
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

// #define _CPU_CMD_W_XDATA_DWORD    (0x20+6UL)
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_W_XDATA_DWORD
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2:ADDR[15:8]
//    CPU32_SIDE_BUF_3:ADDR[7:0]
//    CPU32_SIDE_BUF_4:DATA[31:24]
//    CPU32_SIDE_BUF_5:DATA[23:16]
//    CPU32_SIDE_BUF_6:DATA[15:8]
//    CPU32_SIDE_BUF_7:DATA[7:0]
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

// #define _CPU_CMD_SET_BIT_XDATA_REG    (0x20+3UL)
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_SET_BIT_XDATA_REG
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2:ADDR[15:8]
//    CPU32_SIDE_BUF_3:ADDR[7:0]
//    CPU32_SIDE_BUF_4:AND_MASK
//    CPU32_SIDE_BUF_5:OR_MASK
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

//#define _CPU_CMD_CPU32_COLOR      (0x30+1UL)
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_CPU32_COLOR_XXXXXX
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2~CPU32_SIDE_BUF_14:user define
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

//#define _CPU_CMD_CPU32_FLASH_WRITE  (0x30+2UL)
//    SEND:(SCPU -> KCPU)
//    CPU32_SIDE_BUF_0:_CPU_CMD_CPU32_FLASH_WRITE
//    CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
//    CPU32_SIDE_BUF_2:FlashBank
//    CPU32_SIDE_BUF_3:FlashADDR[15:8]
//    CPU32_SIDE_BUF_4:FlashADDR[7:0]
//    CPU32_SIDE_BUF_5:Length(1~9)
//    CPU32_SIDE_BUF_6:Data0
//    CPU32_SIDE_BUF_7:Data1
//    CPU32_SIDE_BUF_8:Data2
//    CPU32_SIDE_BUF_9:Data3
//    CPU32_SIDE_BUF_10:Data4
//    CPU32_SIDE_BUF_11:Data5
//    CPU32_SIDE_BUF_12:Data6
//    CPU32_SIDE_BUF_13:Data7
//    CPU32_SIDE_BUF_14:Data8
//    ACK:(KCPU -> SCPU)
//    MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructCpuSyncRequestCmd *const g_pstScpuSyncToKcpuCmd;
extern volatile StructCpuCmdSyncInfo g_stScpuSyncCmdInfo;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
__attribute__((section(".itcm_section.ScalerScpuSyncIntFastCommHandler")))
extern bit ScalerScpuSyncIntFastCommHandler(void);
extern void ScalerScpuSyncHandler(void);
extern void ScalerScpuSyncInitial(void);
extern bit ScalerScpuSyncSendCmd(EnumCpuSyncCommand enumScalerSyncCmdType, EnumCpuSyncCommandTimeOut enumScalerSyncCmdTypeTimeOut, UnionCpuSyncReplyCmdBody *punScpuSyncToKcpuCmdReplyBody);
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
extern BYTE ScalerScpuSyncIntFlashWriteCmd(DWORD ulFlash24BitAddr, BYTE ucLength, BYTE *pucFlashData, bit bEnFlashSR, bit bDisFlashSR);
extern BYTE ScalerScpuSyncIntErasePageCmd(WORD usBank, BYTE ucPage);
#endif
extern bit ScalerScpuSyncPollingByteProc(DWORD ulWaitTimeout);


#endif  // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
