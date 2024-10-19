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
// ID Code      : ScalerFmtCnv_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_FMT_CNV__

#include "ScalerFunctionInclude.h"
#include "FmtCnv/ScalerFmtCnv.h"



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
// Description  : Get even/odd enabled status for specified path
// Input Value  : enumInputDataPath --> target input data path
// Output Value : _TRUE if even/odd mode is enabled
//--------------------------------------------------
bit ScalerFmtCnvFtoPGetStatus_EXINT0(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    switch(enumInputDataPath)
    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        case _INPUT_PATH_M1_M2_S1_S2:
#endif
        case _INPUT_PATH_M1_M2:
            return (ScalerGetBit_EXINT(P31_06_FC_EO_LINE_CTRL, _BIT7) == _BIT7);

#if((_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON) &&\
    (_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON))
        case _INPUT_PATH_S1_S2:
            return (ScalerGetBit_EXINT(P31_06_FC_EO_LINE_CTRL, _BIT3) == _BIT3);
#endif

#if((_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON) &&\
    (_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON))
        case _INPUT_PATH_S3_S4:
            return (ScalerGetBit_EXINT(P31_16_FC_EO_LINE_CTRL1, _BIT7) == _BIT7);
#endif

        default:
            break;
    }
#endif

    return _FALSE;
}
