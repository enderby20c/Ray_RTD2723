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
// ID Code      : ScalerIRInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_IR_NEC_STATUS()                                 (g_enumIRNECStatus)
#define SET_IR_NEC_STATUS(x)                                (g_enumIRNECStatus = (x))
#define CLR_IR_NEC_STATUS()                                 (g_enumIRNECStatus = _NEC_IR_NONE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions for IR Status
//--------------------------------------------------
typedef enum
{
    _NEC_IR_NONE = 0x00,
    _NEC_IR_REPEAT = 0x01,
    _NEC_IR_DATA = 0x02,
}EnumNECIRStatus;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern EnumNECIRStatus g_enumIRNECStatus;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#endif
