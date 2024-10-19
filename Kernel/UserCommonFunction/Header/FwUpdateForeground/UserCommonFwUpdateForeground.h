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
// ID Code      : UserCommonFwUpdateForeground.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_FW_UPDATE_FOREGROUND_H__
#define __USER_COMMON_FW_UPDATE_FOREGROUND_H__

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

// Sub Address
#define _FW_UPDATE_FOREGROUND_CMD_SUB_ADDREESS                  0x33
/// Op Code
#define _FW_UPDATE_FOREGROUND_OPCODE_SET_HIGH_PRI_REQ           0x01
#define _FW_UPDATE_FOREGROUND_OPCODE_GET_PROJECT_ID_ADDR_REQ    0x02
#define _FW_UPDATE_FOREGROUND_OPCODE_VERIFY_PROJECT_ID_REQ      0x03
#define _FW_UPDATE_FOREGROUND_OPCODE_GET_ACFWVER_REQ            0x04
#define _FW_UPDATE_FOREGROUND_OPCODE_START_REQ                  0x05
#define _FW_UPDATE_FOREGROUND_OPCODE_FINISH_REQ                 0x06
#define _FW_UPDATE_FOREGROUND_OPCODE_EXIT_REQ                   0x07
#define _FW_UPDATE_FOREGROUND_OPCODE_CHANGE_MODE_REQ            0x08
#define _FW_UPDATE_FOREGROUND_OPCODE_CHANGE_BANK_REQ            0x09

#define _FW_UPDATE_FOREGROUND_SUBADDRESS_INDEX                  0
#define _FW_UPDATE_FOREGROUND_DATA_START_INDEX                  1
#define _FW_UPDATE_FOREGROUND_OPCODE_INDEX                      1

#define GET_FW_UPDATE_FOREGROUND_STATUS()                       (g_stFwUpdateForegroundInfo.enumFwUpdateStatus)
#define SET_FW_UPDATE_FOREGROUND_STATUS(x)                      (g_stFwUpdateForegroundInfo.enumFwUpdateStatus = (x))

#define GET_FW_UPDATE_FOREGROUND_HIGH_PRIORITY()                (g_stFwUpdateForegroundInfo.b1HighPriority)
#define SET_FW_UPDATE_FOREGROUND_HIGH_PRIORITY(x)               (g_stFwUpdateForegroundInfo.b1HighPriority = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Foreground Fw Update State
//--------------------------------------------------
typedef enum
{
    _IDLE_STATUS = 0,
    _VERIFY_STATUS,
    _FW_UPDATE_STATUS,
} EnumFwUpdateForegroundStatus;

//--------------------------------------------------
// Struct of FwUpdate
//--------------------------------------------------
typedef struct
{
    BYTE b1HighPriority : 1;
    EnumFwUpdateForegroundStatus enumFwUpdateStatus;
} StructFwUpdateForgroundScalerInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructFwUpdateForgroundScalerInfo g_stFwUpdateForegroundInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonFwUpdateForegroundSetHighPriProcess(void);
extern void UserCommonFwUpdateForegroundStartProcess(void);
extern void UserCommonFwUpdateForegroundWriteDataProcess(void);
extern void UserCommonFwUpdateForegroundFinishProcess(void);
extern void UserCommonFwUpdateForegroundGetFwVersionProcess(void);
extern void UserCommonFwUpdateForegroundExitProcess(void);
extern void UserCommonFwUpdateForegroundSetUpdateMode(void);
extern bit UserCommonFwUpdateForegroundCheckProcess(void);
extern bit UserCommonFwUpdateForegroundGetHighPriority(void);
extern void UserCommonFwUpdateForegroundGetProjectIDAddrProcess(void);
extern void  UserCommonFwUpdateForegroundVerifyProjectIDProcess(void);
extern void UserCommonFwUpdateForegroundSendReply(BYTE ucResult);
extern void UserCommonFwUpdateForegroundExitBeforeProgramData(void);
extern void UserCommonFwUpdateForegroundChangeModeProcess(void);
extern bit UserCommonFwUpdateForegroundWriteFwData(WORD usProgramLength);

#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
extern bit UserCommonFwUpdateForegroundWriteKeyAndSignatureData(void);
#endif

#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)
extern void UserCommonFwUpdateForegroundReset(void);
#endif

#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE)
extern void UserCommonFwUpdateForegroundSceneBackup(void);
extern void UserCommonFwUpdateForegroundRestoreScene(void);
#endif

#endif

#endif // End of #ifndef __USER_COMMON_FW_UPDATE_FOREGROUND_H__
