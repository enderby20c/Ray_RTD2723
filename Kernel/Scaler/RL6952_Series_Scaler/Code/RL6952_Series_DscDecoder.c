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
// ID Code      : RL6952_Series_DscDecoder.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DSCDECODER__

#include "ScalerFunctionInclude.h"
#include "DscDecoder/ScalerDscDecoder.h"

#if(_DSC_DECODER_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DSC Mac Power Control
// Input Value  : ucDscMac
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoderPowerCutControl(BYTE ucDscMac, EnumDscPowerCut enumDscPowerCut)
{
    switch(ucDscMac)
    {
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
        case _DSC_MAC_0:

            if(enumDscPowerCut == _DSC_POWER_CUT_ON)
            {
                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_DSC_0, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
            }
            else
            {
                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_DSC_0, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
            }
            break;
#endif

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
        case _DSC_MAC_1:

            if(enumDscPowerCut == _DSC_POWER_CUT_ON)
            {
                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_DSC_1, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
            }
            else
            {
                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_DSC_1, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
            }
            break;
#endif

        default:
            break;
    }
}
#endif // End of #if(_DSC_DECODER_SUPPORT == _ON)
