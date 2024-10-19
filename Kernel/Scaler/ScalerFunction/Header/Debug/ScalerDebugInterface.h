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
// ID Code      : ScalerDebugInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of ISP Result
//--------------------------------------------------
typedef enum
{
    _ISP_SUCCESS = 0x00,
    _ISP_FAIL = 0xEE,
} EnumISPBundleVerResult;

//--------------------------------------------------
// Enum Def in MultiCpu Handshake Command Type
//--------------------------------------------------
typedef enum
{
    _DBG_SYSBUS_ERR_KCPU_HARD_FAULT = 1,
    _DBG_SYSBUS_ERR_KCPU_USAGE_FAULT = 2,
    _DBG_SYSBUS_ERR_RXI300_RW_FAIL = 3,
    _DBG_SYSBUS_ERR_RXI300_TIMEOUT = 4,
    _DBG_SYSBUS_ERR_SB2_KCPU_DEBUG_TRAP = 5,
    _DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_SECURE_REGION = 6,
    _DBG_SYSBUS_ERR_SB2_BUS_TIMEOUT = 7,
    _DBG_SYSBUS_ERR_SB2_KCPU_ACCESS_INVALID_ADDR = 8,
    _DBG_SYSBUS_ERR_SCPU_WRAPPER_MEM_TRASH = 9,
    _DBG_SYSBUS_ERR_SCPU_WDT_TIMEOUT = 10,
    _DBG_SYSBUS_ERR_KCPU_MEI = 11,

    _DBG_SYSBUS_ERR_SCPU_HARD_FAULT = 17,
    _DBG_SYSBUS_ERR_SCPU_USAGE_FAULT = 18,
    _DBG_SYSBUS_ERR_SCPU_MEI = 19,
    _DBG_SYSBUS_ERR_SB2_ACCESS_WRT_PROTECT_SECTION = 20,
    _DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_INVALID_ADDR = 21,
    _DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_DBG_TRAP_ADDR = 22,
    _DBG_SYSBUS_ERR_BW32_DEST_ADDR = 23,
    _DBG_SYSBUS_ERR_RBUS2DDR_SRC_ADDR = 24,
} EnumDebugSysBusErrorType;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumDDCCIDebugMode ScalerDebugGetDDCCIDebugMode(void);

extern void ScalerDebugIntProc(void);
extern void ScalerDebugSendData(BYTE ucLen, BYTE *pucSendArray);

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
extern BYTE ScalerDebugGetDdcciSwitchState(void);
extern void ScalerDebugSetDdcciSwitchState(void);
extern void ScalerDebugDualBankSetDebugInfo(BYTE ucRevCmd, BYTE ucOpCode, BYTE ucSubOpCode);
extern BYTE ScalerDebugDualBankGetDebugInfo(BYTE *pucOpCode, BYTE *pucSubOpCode);

#endif

#if(_ASSERT_SUPPORT == _ON)
#if(_PANEL_EXIST_MULTIPANEL == _ON)
extern void ScalerDebugCheckPanelParameter(void);
#endif
#endif

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
extern BYTE *ScalerDebugGetCustomerDebugRevData(void);
#endif

#if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)
extern EnumISPBundleVerResult ScalerDebugUpdateBundleVersion(void);
#endif
