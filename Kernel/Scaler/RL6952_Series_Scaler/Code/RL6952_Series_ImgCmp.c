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
// ID Code      : RL6952_Series_ImgCmp.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_IMG_CMP__

#include "ScalerFunctionInclude.h"
#include "ImgCmp/ScalerImgCmp.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set up Image Compression from decided parameters
// Input Value  : usHWidth/usVHeight - Real Width/Height before Image Compression
//                enumCmpParamIndex - Selected compression setting
// Output Value : None
//--------------------------------------------------
void ScalerImgCmpCtrlGen1(WORD usHWidth, WORD usVHeight, EnumImgCmpParamIndex enumCmpParamIndex)
{
    BYTE ucCmpPathIndex = 0;
    BYTE ucSliceNum = 0;
    WORD usHTotal = 0;
    DWORD ulLineSumBit = 0;
    StructImgCmpGen1Param stImgCmpGen1Param = {0};
    EnumInputDataPath enumSelFrcCapPath = GET_MDOMAIN_INPUT_DATA_PATH();

    stImgCmpGen1Param.usWidth = usHWidth;
    stImgCmpGen1Param.usHeight = usVHeight;

    stImgCmpGen1Param.b1MultiSliceEn = ScalerImgCmpGetMultiSliceEn(GET_MODE_DISPLAY_TARGET_REGION());

    stImgCmpGen1Param.b4BitPerComponent = GET_IMG_CMP_PARAM_DATA_DEPTH(enumCmpParamIndex);
    stImgCmpGen1Param.b10BitPerPixel = ((WORD)(GET_IMG_CMP_PARAM_LLB(enumCmpParamIndex)) << _IMG_CMP_GEN1_BPP_SHIFT) & 0x03FF;
    stImgCmpGen1Param.b4LineBufDepth = 11;
    stImgCmpGen1Param.b1YCCModeEn = _ENABLE; // always input YCC

    // Enc stream period - assume constant bitrate output
    stImgCmpGen1Param.ucSteamPeriodEnc = (BYTE)CEILING_OF_INT_DIVISION(stImgCmpGen1Param.b10BitPerPixel * 2, (1 << _IMG_CMP_GEN1_BPP_SHIFT)) - 1;

    // Dec stream period - assume constant bitrate input, use HTotal to share BW
    usHTotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        usHTotal = usHTotal / 2;
    }

    if(stImgCmpGen1Param.b1MultiSliceEn == _TRUE) // get 1-slice LSB
    {
        ulLineSumBit = ScalerFRCGetLineSumBit(stImgCmpGen1Param.usWidth / 2, GET_MEMORY_DATA_BIT(), enumCmpParamIndex);
    }
    else
    {
        ulLineSumBit = ScalerFRCGetLineSumBit(stImgCmpGen1Param.usWidth, GET_MEMORY_DATA_BIT(), enumCmpParamIndex);
    }

    // RL6952 M1/M2 use E/O Mode, LSB * 2
    // RL6952 S1 use HTotal/2, effectively LSB*2
    // Thus the formula remains the same
    ulLineSumBit = ulLineSumBit * 2;

    // Period = ((LineSumBit / 128) / HTotal) * 256 - 1
    stImgCmpGen1Param.ucSteamPeriodDec = (BYTE)CEILING_OF_INT_DIVISION(ulLineSumBit * 2, usHTotal) - 1;

    // Slice Height Calculation
    // Try to divide vertical slices height under 512 lines if possible
    // if pic_height cannot be divided by any slice_height under 512, remain the original pic_height as slice_height
    stImgCmpGen1Param.usSliceHeight = stImgCmpGen1Param.usHeight;
    for(ucSliceNum = 1; ucSliceNum <= 10; ucSliceNum++)
    {
        // try 1~10 slices, should be enough for our application
        if((stImgCmpGen1Param.usHeight / ucSliceNum < 512) && ((stImgCmpGen1Param.usHeight % ucSliceNum) == 0))
        {
            stImgCmpGen1Param.usSliceHeight = stImgCmpGen1Param.usHeight / ucSliceNum;
            break;
        }
    }

    ScalerGlobalEnableUnderflowMonitor(_ENABLE, ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION()));

    //=========================
    // IMC / Encoder + Decoder
    //=========================
    for(ucCmpPathIndex = 0; ucCmpPathIndex < _HW_M_DOMAIN_IMG_CMP_PATH_COUNT; ucCmpPathIndex++)
    {
        // Map IMC path# to input (FRC) path enum
        EnumInputDataPath enumCurrCmpPath = GET_IMG_CMP_DATA_PATH(ucCmpPathIndex);

        if((enumSelFrcCapPath & enumCurrCmpPath) == enumCurrCmpPath)
        {
            BYTE ucDecmpPathIndex1 = 0x00;
            BYTE ucDecmpPathIndex2 = 0x00;
            ScalerImgCmpRemapDecoderIndex(GET_DISPLAY_MODE(), ucCmpPathIndex, &ucDecmpPathIndex1, &ucDecmpPathIndex2);
            ScalerImgCmpGen1CommonCtrl(GET_IMG_CMP_REG_PAGE(ucCmpPathIndex), GET_IMG_DECMP_REG_PAGE(ucDecmpPathIndex1), GET_IMG_DECMP_REG_PAGE(ucDecmpPathIndex2), &stImgCmpGen1Param);
        }
    }
}

//--------------------------------------------------
// Description  : Image Compression Power Cut Control
// Input Value  : Input data path/ _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerImgCmpDecmpPowerControl(EnumInputDataPath enumInputDataPath, bit bPowerOn)
{
    EnumPowerGroup penumEncPowerGroup[] =
    {
        _POWER_CUT_GROUP_IMC_ENC_M1,
        _POWER_CUT_GROUP_IMC_ENC_M2,
        _POWER_CUT_GROUP_IMC_ENC_S1,

    };
    EnumPowerGroup penumDecPowerGroup[] =
    {
        _POWER_CUT_GROUP_IMC_DEC_M1,
        _POWER_CUT_GROUP_IMC_DEC_M2,
        _POWER_CUT_GROUP_IMC_DEC_S1,
    };

    if(bPowerOn == _ON)
    {
        for(BYTE ucIndex = 0; ucIndex < _HW_M_DOMAIN_IMG_CMP_PATH_COUNT; ucIndex++)
        {
            ScalerPowerDomainEnableControl(penumEncPowerGroup[ucIndex], _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
            ScalerPowerDomainEnableControl(penumDecPowerGroup[ucIndex], _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
        }
    }
    else
    {
        if(enumInputDataPath == _INPUT_PATH_NONE)
        {
            for(BYTE ucIndex = 0; ucIndex < _HW_M_DOMAIN_IMG_CMP_PATH_COUNT; ucIndex++)
            {
                ScalerPowerDomainEnableControl(penumEncPowerGroup[ucIndex], _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
                ScalerPowerDomainEnableControl(penumDecPowerGroup[ucIndex], _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
            }
        }
    }
}
#endif
