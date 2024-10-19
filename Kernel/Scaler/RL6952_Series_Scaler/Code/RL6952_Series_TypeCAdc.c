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
// ID Code      : RL6952_Series_TypeCAdc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_TYPECADC__

#include "ScalerFunctionInclude.h"
#include "TypeCAdc/ScalerTypeCAdc.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON)) || (_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check if default LDO voltage is 1.807V
// Input Value  : NA
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCAdcGetLdoBandgapCoverSupport(void)
{
    return _FALSE;
}
#endif
