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
// ID Code      : ScalerIDomain_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IDOMAIN__

#include "ScalerFunctionInclude.h"
#include "IDomain/ScalerIDomain.h"



//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get I domain double buffer apply bit
// Input Value  : enumInputDataPath --> input data path
// Output Value : Register page
//--------------------------------------------------
BYTE ScalerIDomainGetInputPathPage_EXINT0(EnumInputDataPath enumInputDataPath)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0)
        {
            return GET_IDOMAIN_REG_PAGE(ucIndex);
        }
    }

    return 0x00;
}
