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
// ID Code      : ScalerRegInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Page Register
//--------------------------------------------------
#define _REG_MAIN1_PAGE                         0x0000U
#define _REG_MAIN2_PAGE                         0x4000U
#define _REG_SUB1_PAGE                          0x8000U
#define _REG_SUB2_PAGE                          0xC000U
#define _REG_SUB3_PAGE                          0x1700U
#define _REG_SUB4_PAGE                          0xDC00U

#define _REG_PAGE_OFFSET                        (_REG_MAIN2_PAGE - _REG_MAIN1_PAGE)

//--------------------------------------------------
// Macro of WORD/DWORD pData
//--------------------------------------------------
#define PDATA_WORD(x)                           (((WORD *)pData)[x])
#define PDATA_DWORD(x)                          (((DWORD *)pData)[x])

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE data pData[16];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

