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
// ID Code      : ScalerDebugInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_ASSERT_SUPPORT == _ON)
#define ASSERT(expr)                                {\
                                                        if(!(expr))\
                                                        {\
                                                            ScalerDebugAssert(__FILE__, __LINE__);\
                                                        }\
                                                    }
#else
#define ASSERT(expr)                                ;
#endif

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
// True : DDCCI  Swicth to Debug Mode; Ignore OSD Falg.
// FALSE :  Refer to OSD Flag
#define GET_DDCCI_SWITCH_STATE()                    (g_bDebugDdcciSwitchState)
#define SET_DDCCI_SWITCH_STATE()                    (g_bDebugDdcciSwitchState = _TRUE)
#define CLR_DDCCI_SWITCH_STATE()                    (g_bDebugDdcciSwitchState = _FALSE)
#endif

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
// True : DDCCI  Swicth to Debug Mode; Ignore OSD Falg.
// FALSE :  Refer to OSD Flag
#define GET_CUSTOMER_CMD_REV_STATE()                (g_bDebugCustomerCmdRev)
#define SET_CUSTOMER_CMD_REV_STATE()                (g_bDebugCustomerCmdRev = _TRUE)
#define CLR_CUSTOMER_CMD_REV_STATE()                (g_bDebugCustomerCmdRev = _FALSE)
#endif

#define CPU32_DBG_MSG(str, value)                   (ScalerDebugMessage((SBYTE *)(str), (value)))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DDCCI or Debug Mode
//--------------------------------------------------
typedef enum
{
    _DEBUG_MODE,
    _DDCCI_MODE,
} EnumDDCCIDebugMode;

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
typedef struct
{
    BYTE ucRevDebugCmd;
    BYTE ucOpCode;
    BYTE ucSubOpCode;
}StructDualBankBootDebug;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_TIME_CURSOR_SUPPORT == _ON)
extern StructTimerSampleMS g_pstDebugTimerCursorMS[];
extern StructTimerSampleUS g_pstDebugTimerCursorUS[];

extern BYTE g_ucDebugTimerCursorUsedMS;
extern BYTE g_ucDebugTimerCursorUsedUS;
#endif

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
extern bit g_bDebugDdcciSwitchState;
#endif

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
extern bit g_bDebugCustomerCmdRev;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern void ScalerDebugMessage(SBYTE *pchMessage, DWORD ulValue);
#endif

#if(_TIME_CURSOR_SUPPORT == _ON)
extern WORD ScalerDebugGetTimerCursorMSDifference(EnumDebugTimeCursor enumIndex);
extern DWORD ScalerDebugGetTimerCursorUSDifference(EnumDebugTimeCursor enumIndex);
#endif

extern void ScalerDebug(void);

#if(_ASSERT_SUPPORT == _ON)
extern void ScalerDebugAssert(SBYTE *pchFileName, WORD usLine);
#endif

