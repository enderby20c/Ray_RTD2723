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
// ID Code      : ScalerMbr_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MBR_EXINT0__

#include "ScalerFunctionInclude.h"
#include "Mbr/ScalerMbr.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
BYTE g_ucMbrDrrVFreqIndex;
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DRR MBR handler interrupt process (EXINT0 only)
//                Recording & calculating input & average framerate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMbrIntHandlerDVS_EXINT0(void)
{
    BYTE ucCnt = 0;
    WORD usMbrVFreq_avg = 0;

    // Calculate average framerate
    ucCnt = g_ucMbrDrrVFreqIndex % _MBR_DRR_AVG_IVF_FRAME_CNT;

    SET_MBR_DRR_VFREQ_EXINT0(ucCnt, GET_INPUT_TIMING_VFREQ());
    for(ucCnt = 0; ucCnt < _MBR_DRR_AVG_IVF_FRAME_CNT; ucCnt++)
    {
        usMbrVFreq_avg += GET_MBR_DRR_VFREQ_EXINT0(ucCnt);
    }
    SET_MBR_DRR_VFREQ_AVG_EXINT0(usMbrVFreq_avg / _MBR_DRR_AVG_IVF_FRAME_CNT);

    if(GET_MBR_DRR_VFREQ_AVG_EXINT0() < _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO)
    {
        CLR_MBR_DRR_SAFE_CNT_EXINT0();
    }
    else
    {
        SET_MBR_DRR_SAFE_CNT_EXINT0();
    }

    g_ucMbrDrrVFreqIndex++;
}
#endif
#endif

