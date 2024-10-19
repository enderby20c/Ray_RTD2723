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
// ID Code      : UserCommonDualBankUserInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_ISP_CHANNEL_PROTECT_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of ISP Slave Project Enbale or disable
//--------------------------------------------------
typedef enum
{
    _ISP_SLAVE_DISABLE = 0,
    _ISP_SLAVE_ENABLE = 1,
} EnumIspSlaveAddrState;
#endif

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
#if(_DUAL_BANK_USER_FLAG_CUSTOMER_TYPE != _DUAL_BANK_KERNEL_TYPE)
//--------------------------------------------------
// Enumerations of WriteDone Flag
//--------------------------------------------------
typedef enum
{
    _FWUPDATE_WRITE_FLAG_FAIL = _FALSE,
    _FWUPDATE_WRITE_FLAG_SUCCESS = _TRUE,
} EnumFwUpdateWriteFlagResult;
#endif
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_ISP_CHANNEL_PROTECT_SUPPORT == _ON)
extern void UserCommonDualBankUserSetISPChannel(WORD usISPChannel);
extern void UserCommonDualBankUserSetISPSlaveAddr(EnumIspSlaveAddrState enumISPStatus);
#endif

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
extern WORD UserCommonDualBankUserGetKCPUBankOffset(void);
#endif

