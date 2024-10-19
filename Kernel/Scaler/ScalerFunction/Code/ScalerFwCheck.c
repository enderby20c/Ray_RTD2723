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
// ID Code      : ScalerFwCheck.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_FWCHECK__

#include "ScalerFunctionInclude.h"
#include "FwCheck/ScalerFwCheck.h"

#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************
__attribute__((section(".used_table.tFwProjectIDTable")))
BYTE code tFwProjectIDTable[] =
{
    _ISP_FW_CHECK_PROJECT_ID_DATA
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Verify Project ID
// Input Value  : Project ID Data Buffer
// Output Value : Verify Result
//--------------------------------------------------
EnumProjectIDVerifyResult ScalerFwCheckProjectIDVerify(BYTE *pucBuf)
{
    if(CHECK_FW_PROJECT_ID(pucBuf, tFwProjectIDTable, sizeof(tFwProjectIDTable)) == _TRUE)
    {
        return _ISP_FW_CHECK_VERIFY_SUCCESS;
    }

    return _ISP_FW_CHECK_VERIFY_FAIL;
}

//--------------------------------------------------
// Description  : Get Project ID Address
// Input Value  : None
// Output Value : Project ID Address
//--------------------------------------------------
void ScalerFwCheckGetProjectIDAddress(BYTE *pucArray)
{
    // 4 byte Flash Address
    pucArray[0] = 0x00;
    pucArray[1] = _ISP_FW_CHECK_PROJECT_ID_LOCATION_BANK;
    pucArray[2] = ((WORD)_ISP_FW_CHECK_PROJECT_ID_LOCATION_ADDRESS >> 8) & 0xFF;
    pucArray[3] = ((WORD)_ISP_FW_CHECK_PROJECT_ID_LOCATION_ADDRESS) & 0xFF;
    pucArray[4] = sizeof(tFwProjectIDTable);
}
#endif // End of #if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
