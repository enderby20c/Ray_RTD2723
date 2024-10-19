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
// ID Code      : SysCec.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_CEC__

#include "SysInclude.h"
#include "Cec/SysCec.h"

#if(_HDMI_CEC_SUPPORT == _ON)

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
// Description  : System Cec Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysCecHandler(void)
{
    // Receive part
    ScalerCecRxProcess();
    UserCommonCecReceiveNotify();

    // Transmit part
    UserCommonCecTransmitInfoPrepare();
    ScalerCecTxProcess();
}

#endif
