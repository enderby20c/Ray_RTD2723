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
// ID Code      : UserCommonEdidInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _EDID_TABLE_FLASH_PAGE                         (_EDID_ADDRESS_FLASH / _FLASH_PAGE_SIZE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
extern BYTE code tEDID_TABLE_A0[];
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
extern BYTE code tEDID_TABLE_D0[];
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern BYTE code tEDID_TABLE_D1[];
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern BYTE code tEDID_TABLE_D2[];
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
extern BYTE code tEDID_TABLE_D3[];
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
extern BYTE code tEDID_TABLE_D4[];
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
extern BYTE code tEDID_TABLE_D5[];
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
extern BYTE code tEDID_TABLE_D7[];
#endif

#if(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
extern BYTE code tEDID_TABLE_D8[];
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
extern BYTE code tEDID_TABLE_D9[];
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


