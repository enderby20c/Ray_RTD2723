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
// ID Code      : ScalerTypeC1Cc.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TYPEC1_CC_H__
#define __SCALER_TYPEC1_CC_H__


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Type_C_1_CC Related Definition
//--------------------------------------------------
#define _TYPE_C_1_CC_CONNECT_MODE                               _TYPE_C_HW_MODE

//--------------------------------------------------
// Type_C_1_CC Related MACRO
//--------------------------------------------------
#define GET_TYPE_C_1_CC_HW_STATE()                              (ScalerGetByte(P6C_33_CC_HW_FSM) & (0x1F))

#define GET_TYPE_C_1_CC_FW_STATE()                              (g_stTypeC1CcInfo.b3AttachStatus)
#define SET_TYPE_C_1_CC_FW_STATE(x)                             (g_stTypeC1CcInfo.b3AttachStatus = (x))

#define GET_TYPE_C_1_CC_RA_EXIST()                              ((bit)(g_stTypeC1CcInfo.b1RaExist))
#define SET_TYPE_C_1_CC_RA_EXIST()                              (g_stTypeC1CcInfo.b1RaExist = _TRUE)
#define CLR_TYPE_C_1_CC_RA_EXIST()                              (g_stTypeC1CcInfo.b1RaExist = _FALSE)

#define GET_TYPE_C_1_CC_CONNECT_EN()                            ((bit)(g_stTypeC1CcInfo.b1ConnectEnable))
#define SET_TYPE_C_1_CC_CONNECT_EN()                            (g_stTypeC1CcInfo.b1ConnectEnable = _TRUE)
#define CLR_TYPE_C_1_CC_CONNECT_EN()                            (g_stTypeC1CcInfo.b1ConnectEnable = _FALSE)

#define GET_TYPE_C_1_CC_SRC_FRSWAP_STATUS()                     ((bit)(g_stTypeC1CcInfo.b1FRSrcEnable))
#define SET_TYPE_C_1_CC_SRC_FRSWAP_STATUS(x)                    (g_stTypeC1CcInfo.b1FRSrcEnable = (x))

#define GET_TYPE_C_1_CC_SNK_FRSWAP_STATUS()                     ((bit)(g_stTypeC1CcInfo.b1FRSnkEnable))
#define SET_TYPE_C_1_CC_SNK_FRSWAP_STATUS(x)                    (g_stTypeC1CcInfo.b1FRSnkEnable = (x))

#define GET_TYPE_C_1_CC_AC_ON_RECONNECT()                       ((bit)(g_stTypeC1CcInfo.b1AcOnReconnect))
#define SET_TYPE_C_1_CC_AC_ON_RECONNECT()                       (g_stTypeC1CcInfo.b1AcOnReconnect = _TRUE)
#define CLR_TYPE_C_1_CC_AC_ON_RECONNECT()                       (g_stTypeC1CcInfo.b1AcOnReconnect = _FALSE)

#define GET_TYPE_C_1_CC_DISCHARGE_COUNT()                       (g_stTypeC1CcInfo.ucDischargeCount)
#define SET_TYPE_C_1_CC_DISCHARGE_COUNT(x)                      (g_stTypeC1CcInfo.ucDischargeCount = (x))

#define GET_TYPE_C_1_CC_DRP_PREFER()                            (g_stTypeC1CcInfo.b2DrpPrefer)
#define SET_TYPE_C_1_CC_DRP_PREFER(x)                           (g_stTypeC1CcInfo.b2DrpPrefer = (x))

#define GET_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK()          ((bit)(g_stTypeC1CcInfo.b1AttachedSrcToTryWaitSnk))
#define SET_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK()          (g_stTypeC1CcInfo.b1AttachedSrcToTryWaitSnk = _TRUE)
#define CLR_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK()          (g_stTypeC1CcInfo.b1AttachedSrcToTryWaitSnk = _FALSE)

#define GET_TYPE_C_1_CC_TRY_WAIT_SNK_STATE()                    ((bit)(g_stTypeC1CcInfo.b1TryWaitSnkState))
#define SET_TYPE_C_1_CC_TRY_WAIT_SNK_STATE()                    (g_stTypeC1CcInfo.b1TryWaitSnkState = _TRUE)
#define CLR_TYPE_C_1_CC_TRY_WAIT_SNK_STATE()                    (g_stTypeC1CcInfo.b1TryWaitSnkState = _FALSE)

#define GET_TYPE_C_1_RESET_FLAG()                               ((bit)(g_stTypeC1CcInfo.b1ResetFlag))
#define SET_TYPE_C_1_RESET_FLAG()                               (g_stTypeC1CcInfo.b1ResetFlag = _TRUE)
#define CLR_TYPE_C_1_RESET_FLAG()                               (g_stTypeC1CcInfo.b1ResetFlag = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// Main Loop Funtions : ScalerTypeC1Cc.c
extern void ScalerTypeC1CcInitial(void);
extern void ScalerTypeC1CcSetDeglitch(EnumTypeCChannel enumTypeCChannel, BYTE ucTime, EnumTypeCDeglitchUnit enumUnit);
extern void ScalerTypeC1CcSetDebounce(bit bDbType, BYTE ucTime);
extern void ScalerTypeC1CcFWModeDisconnect(void);
extern void ScalerTypeC1CcUnattachReset(void);
extern void ScalerTypeC1CcConnectionSet(void);
extern void ScalerTypeC1CcConnectionStart(void);
extern bit ScalerTypeC1CcUnattachCheck(void);
extern void ScalerTypeC1CcSetBMC(bit bAction);

#if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
extern void ScalerTypeC1CcFastRoleSwapControl(bit bAction);
#endif

// EXINT Funtions : ScalerTypeC1Cc_EXINT.c
extern bit ScalerTypeC1CcAttachedSetting_EXINT0(EnumTypeCPDState *penumPdFwState);
extern void ScalerTypeC1CcSetBMC_EXINT0(bit bAction);
extern void ScalerTypeC1CcUnattachFlow_EXINT0(void);
extern void ScalerTypeC1CcUnattachReset_EXINT0(void);
extern void ScalerTypeC1CcConnectionSet_EXINT0(void);
extern void ScalerTypeC1CcConnectionStart_EXINT0(void);

#if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
extern void ScalerTypeC1CcFastRoleSwapControl_EXINT0(bit bAction);
#endif

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))


#endif // End of #ifndef __SCALER_TYPEC1_CC_H__
