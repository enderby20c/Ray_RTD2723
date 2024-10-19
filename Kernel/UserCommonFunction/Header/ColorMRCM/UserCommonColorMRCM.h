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
// ID Code      : UserCommonColorMRCM.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_COLOR_MRCM_H__
#define __USER_COMMON_COLOR_MRCM_H__

#if(_COLOR_IP_MRCM == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define CLR_MRCM_READ_RESULT_DONE()         (g_bColorMRCMReadResultDone = 0)

#define SET_MRCM_USER_DATA_LOOP_NUM(x)      (g_stColorMRCMLoopUserData.ucMRCMLoopNum = (x))
#define GET_MRCM_USER_DATA_LOOP_NUM()       (g_stColorMRCMLoopUserData.ucMRCMLoopNum)

#define SET_MRCM_KERNEL_DATA_LOOP_NUM(x)    (g_stColorMRCMLoopKernelData.ucMRCMLoopNum = (x))
#define GET_MRCM_KERNEL_DATA_LOOP_NUM()     (g_stColorMRCMLoopKernelData.ucMRCMLoopNum)

#define SET_MRCM_READY_SET(x)               (g_enumColorMRCMDataReadySet = (EnumMRCMSet)(x))
#define SET_MRCM_READY_KERNEL_SET(x)        (g_enumColorMRCMKernelDataReadySet = (EnumMRCMKernelSet)(x))
#define GET_MRCM_READY_KERNEL_SET()         (g_enumColorMRCMKernelDataReadySet)

#define SET_MRCM_CURRENT_LOOP_NUM(x)        (g_ucColorMRCMCurrentLoopNum = (x))
#define GET_MRCM_CURRENT_LOOP_NUM()         (g_ucColorMRCMCurrentLoopNum)

#define SET_MRCM_SRAM_NOT_EMPTY()           (g_bColorMRCMSramNotEmpty = 1)
#define CLR_MRCM_SRAM_NOT_EMPTY()           (g_bColorMRCMSramNotEmpty = 0)
#define GET_MRCM_SRAM_NOT_EMPTY()           (g_bColorMRCMSramNotEmpty)

#define SET_MRCM_CASE(x)                    (g_enumColorMRCMCase = (x))
#define GET_MRCM_CASE()                     (g_enumColorMRCMCase)

#define SET_MRCM_READ_RESULT_DONE()         (g_bColorMRCMReadResultDone = 1)
#define GET_MRCM_READ_RESULT_DONE()         (g_bColorMRCMReadResultDone)


#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
#define _AVE_FILTER_FRAME_NUM               4
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _MRCM_KERNEL_SET_0 = 0x00,
    _MRCM_KERNEL_SET_1,
    _MRCM_KERNEL_SET_2,
    _MRCM_KERNEL_SET_3,
    _MRCM_KERNEL_SET_4,
    _MRCM_KERNEL_SET_5,
    _MRCM_KERNEL_SET_NONE = 0xFF,
}EnumMRCMKernelSet;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucColorMRCMCurrentLoopNum;
extern bit g_bColorMRCMSramNotEmpty;
extern EnumMRCMCase g_enumColorMRCMCase;
extern StructMRCMLoopData g_stColorMRCMLoopUserData;
extern StructMRCMLoopData g_stColorMRCMLoopKernelData;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonColorMRCMLoopSetting(void);
extern void UserCommonColorMRCMSetting(StructMRCMData *pstMRCMData);
extern void UserCommonColorMRCMApplication(void);
extern void UserCommonColorMRCMCaseReadResult(void);
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
extern void UserCommonColorLowBlueHandler(void);
extern void UserCommonColorMRCMLowBlueReadResult(void);
#endif
#endif // End of #if(_MRCM_SUPPORT == _ON)
#endif // End of #ifndef __USER_COMMON_COLOR_MRCM_H__
