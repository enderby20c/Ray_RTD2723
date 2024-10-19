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
// ID Code      : ScalerFwInfo.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_FW_INFO__
#include "ScalerFunctionInclude.h"
#include "FwInfo/ScalerFwInfo.h"

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
__attribute__((section(".used_table.tFwVersionTable")))
BYTE code tFwVersionTable[] =
{
    _CUSTOMER_FW_VERSION,
    _CUSTOMER_FW_SUB_VERSION,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Currten Fw Version
// Input Value  : None
// Output Value : Version Info
//--------------------------------------------------
void ScalerFwInfoGetCurrentVersion(BYTE *pucArray)
{
    // Set FW Version
    pucArray[0] = tFwVersionTable[0];
    pucArray[1] = tFwVersionTable[1];
}

//--------------------------------------------------
// Description  : Get Fw Version locate in Bin File
// Input Value  : None
// Output Value : Version Info
//--------------------------------------------------
void ScalerFwInfoGetFwVersionAddress(BYTE *pucArray)
{
    // 4 byte Flash Address
    pucArray[0] = 0x00;
    pucArray[1] = _CUSTOMER_FW_VERSION_LOCATE_BANK;
    pucArray[2] = ((WORD)_CUSTOMER_FW_VERSION_LOCATE_ADDRESS >> 8) & 0xFF;
    pucArray[3] = ((WORD)_CUSTOMER_FW_VERSION_LOCATE_ADDRESS) & 0xFF;
    pucArray[4] = sizeof(tFwVersionTable);
}
#endif

