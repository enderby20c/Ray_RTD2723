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
// ID Code      : ScalerImgCmp.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_IMG_CMP__

#include "ScalerFunctionInclude.h"
#include "ImgCmp/ScalerImgCmp.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)

StructFRCImgCmpDecmpPathInfo code tFRCImgCmpDecmpPathInfo[_HW_M_DOMAIN_IMG_CMP_PATH_COUNT] =
{
    {_INPUT_PATH_M1, _MDOMAIN_DISP_PATH_M1, _REG_PAGE_M1_M_DOMAIN_IMG_CMP, _REG_PAGE_M1_M_DOMAIN_IMG_DECMP, _FRC_MAIN1_PAGE},
#if((_REG_PAGE_M2_M_DOMAIN_IMG_CMP != _PAGE_NONE) && (_REG_PAGE_M2_M_DOMAIN_IMG_DECMP != _PAGE_NONE))
    {_INPUT_PATH_M2, _MDOMAIN_DISP_PATH_M2, _REG_PAGE_M2_M_DOMAIN_IMG_CMP, _REG_PAGE_M2_M_DOMAIN_IMG_DECMP, _FRC_MAIN2_PAGE},
#endif
#if((_REG_PAGE_S1_M_DOMAIN_IMG_CMP != _PAGE_NONE) && (_REG_PAGE_S1_M_DOMAIN_IMG_DECMP != _PAGE_NONE))
    {_INPUT_PATH_S1, _MDOMAIN_DISP_PATH_S1, _REG_PAGE_S1_M_DOMAIN_IMG_CMP, _REG_PAGE_S1_M_DOMAIN_IMG_DECMP, _FRC_SUB1_PAGE},
#endif
#if((_REG_PAGE_S2_M_DOMAIN_IMG_CMP != _PAGE_NONE) && (_REG_PAGE_S2_M_DOMAIN_IMG_DECMP != _PAGE_NONE))
    {_INPUT_PATH_S2, _MDOMAIN_DISP_PATH_S2, _REG_PAGE_S2_M_DOMAIN_IMG_CMP, _REG_PAGE_S2_M_DOMAIN_IMG_DECMP, _FRC_SUB2_PAGE},
#endif
#if((_REG_PAGE_S3_M_DOMAIN_IMG_CMP != _PAGE_NONE) && (_REG_PAGE_S3_M_DOMAIN_IMG_DECMP != _PAGE_NONE))
    {_INPUT_PATH_S3, _MDOMAIN_DISP_PATH_S3, _REG_PAGE_S3_M_DOMAIN_IMG_CMP, _REG_PAGE_S3_M_DOMAIN_IMG_DECMP, _FRC_SUB3_PAGE},
#endif
#if((_REG_PAGE_S4_M_DOMAIN_IMG_CMP != _PAGE_NONE) && (_REG_PAGE_S4_M_DOMAIN_IMG_DECMP != _PAGE_NONE))
    {_INPUT_PATH_S4, _MDOMAIN_DISP_PATH_S4, _REG_PAGE_S4_M_DOMAIN_IMG_CMP, _REG_PAGE_S4_M_DOMAIN_IMG_DECMP, _FRC_SUB4_PAGE},
#endif
};
#endif


StructImgCmpParam g_pstImgCmpParam[] =
{
    // ENABLE
    // |   DATA_BIT_DEPTH       LLB
    // |   |                     |
    {_OFF, _OFF,                 _OFF},   // _IMG_CMP_PARAM_OFF
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    {_ON,  _COLOR_DEPTH_10_BITS,  12 },   // _IMG_CMP_PARAM_LLB_12
    {_ON,  _COLOR_DEPTH_10_BITS,  11 },   // _IMG_CMP_PARAM_LLB_11
    {_ON,  _COLOR_DEPTH_10_BITS,  10 },   // _IMG_CMP_PARAM_LLB_10
#if(_M_DOMAIN_IMG_CMP_10_BIT_SUPPORT == _ON)
    {_ON,  _COLOR_DEPTH_10_BITS,  9  },   // _IMG_CMP_PARAM_LLB_9
    {_ON,  _COLOR_DEPTH_10_BITS,  8  },   // _IMG_CMP_PARAM_LLB_8
#else
    {_ON,  _COLOR_DEPTH_8_BITS,   9  },   // _IMG_CMP_PARAM_LLB_9
    {_ON,  _COLOR_DEPTH_8_BITS,   8  },   // _IMG_CMP_PARAM_LLB_8
#endif
    {_ON,  _COLOR_DEPTH_8_BITS,   7  },   // _IMG_CMP_PARAM_LLB_7
    {_ON,  _COLOR_DEPTH_8_BITS,   6  },   // _IMG_CMP_PARAM_LLB_6
#endif
};


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
void ScalerImgCmpCtrl(WORD usHWidth, WORD usVHeight, EnumImgCmpParamIndex enumCmpParamIndex)
{
    if(GET_IMG_CMP_ENABLE(enumCmpParamIndex) == _FALSE)
    {
        return;
    }

    ScalerImgCmpCtrlGen1(usHWidth, usVHeight, enumCmpParamIndex);
}

//--------------------------------------------------
// Description  : Image Compression on/off
// Input Value  : enumOn --> _FUNCTION_ON/_FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerImgCmpEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath enumSelFrcCapPath, bit bEn)
{
    BYTE ucCmpPathIndex = 0;
    EnumMDomainDisplayDataPath enumSelFrcDispPath = ScalerFRCGetMDispPath(enumSelFrcCapPath);

    // For each encoder path
    for(ucCmpPathIndex = 0; ucCmpPathIndex < _HW_M_DOMAIN_IMG_CMP_PATH_COUNT; ucCmpPathIndex++)
    {
        // Map IMC Encoder path# to input (FRC) path enum
        EnumInputDataPath enumCurrCmpPath = GET_IMG_CMP_DATA_PATH(ucCmpPathIndex);

        if((enumSelFrcCapPath & enumCurrCmpPath) == enumCurrCmpPath)
        {
            BYTE ucDecmpPathIndex1 = 0x00;
            BYTE ucDecmpPathIndex2 = 0x00;
            ScalerImgCmpRemapDecoderIndex(GET_DISPLAY_MODE(), ucCmpPathIndex, &ucDecmpPathIndex1, &ucDecmpPathIndex2);

            //===================================
            // FRC Capture - Image Compression
            //===================================
            if(((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF) &&
               ((_HW_M_DOMAIN_IMG_CMP_ALL_PATH & enumSelFrcCapPath) != _INPUT_PATH_NONE))
            {
                ScalerImgCmpEncEn(GET_IMG_CMP_REG_PAGE(ucCmpPathIndex), bEn);
            }

            // ===================================
            // FRC Display - Image Decompression
            // ===================================
            if(((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF) &&
               ((_HW_M_DOMAIN_IMG_DECMP_ALL_PATH & enumSelFrcDispPath) != _MDOMAIN_DISP_PATH_NONE))
            {
                if(ucDecmpPathIndex1 != 0xFF)
                {
                    ScalerImgCmpDecEn(GET_IMG_DECMP_REG_PAGE(ucDecmpPathIndex1), bEn);
                }

                if(ucDecmpPathIndex2 != 0xFF)
                {
                    ScalerImgCmpDecEn(GET_IMG_DECMP_REG_PAGE(ucDecmpPathIndex2), bEn);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : IMC multi-slice status for current region
// Input Value  : Display target regionn
// Output Value : IMC multi-slice ON or OFF
//--------------------------------------------------
bit ScalerImgCmpGetMultiSliceEn(EnumDisplayRegion enumDisplayRegion)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        switch(enumDisplayRegion)
        {
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_TOP:
            case _DISPLAY_RGN_BOTTOM:
                return _ENABLE;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_SKEW_T_MAIN:
            case _DISPLAY_RGN_SKEW_B_MAIN:
                return _ENABLE;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_LT:
            case _DISPLAY_RGN_LB:
            case _DISPLAY_RGN_RT:
            case _DISPLAY_RGN_RB:
                return _ENABLE;
#endif
            default:
                return _DISABLE;
        }
    }
#if(_COLOR_IP_3DDI == _ON)
    else if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
    {
        // if 3DDI case and S2 input, trans to S1/S2
        switch(enumDisplayRegion)
        {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_PIP_SUB:
                return _ENABLE;
#endif
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _DISPLAY_RGN_EAGLE_SIGHT_SUB:
                return _ENABLE;
#endif
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT:
            case _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT:
            case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
                return _ENABLE;
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_BOTTOM:
                return _ENABLE;
#endif
            default:
                return _DISABLE;
        }
    }
#endif
    else
    {
        return _DISABLE;
    }
}

//--------------------------------------------------
// Description  : Remapping encoder path to a decoder path in Top/Bottom swtich mode
// Input Value  : Display target regionn, current input(compression) path
// Output Value : Decoder path index (0x00 - M1; 0x01 - M2; 0x02 - S1; 0x03 - S2; 0x04 - S3; 0x05 - S4)
//--------------------------------------------------
void ScalerImgCmpRemapDecoderIndex(EnumDisplayMode enumDisplayMode, BYTE ucCmpIndex, BYTE *pucDecmpIndex1, BYTE *pucDecmpIndex2)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        switch(enumDisplayMode)
        {
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PBP_TB:
                // M1 Enc Reg set to M1 Dec Reg for M1/M2 HW on Top
                // M2 Enc Reg set to S1 Dec Reg for S1/S2 HW on Top
                // S1 Enc Reg set to M2 Dec Reg for M1/M2 HW on Bot
                // S2 Enc Reg set to S2 Dec Reg for S1/S2 HW on Bot
                if(ucCmpIndex == 0x00)
                {
                    *pucDecmpIndex1 = 0x00;
                }
                else if(ucCmpIndex == 0x01)
                {
                    *pucDecmpIndex1 = 0x02;
                }
                else if(ucCmpIndex == 0x02)
                {
                    *pucDecmpIndex1 = 0x01;
                }
                else if(ucCmpIndex == 0x03)
                {
                    *pucDecmpIndex1 = 0x03;
                }
                else
                {
                    *pucDecmpIndex1 = ucCmpIndex;
                }
                *pucDecmpIndex2 = 0xFF;
                break;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_3P_SKEW_T:
                // M1 Enc Reg set to M1 Dec Reg for M1/M2 HW on Top
                // M2 Enc Reg set to S1/S2 Dec Reg for S1/S2 HW
                // S1 Enc Reg set to M2 Dec Reg for M1/M2 HW on Bot
                // S2 Enc Reg should be the same as S1 Enc Reg (no use)
                // S3/S4 Enc Reg is equal to S3/S4 Dec Reg
                if(ucCmpIndex == 0x00)
                {
                    *pucDecmpIndex1 = 0x00;
                    *pucDecmpIndex2 = 0xFF;
                }
                else if(ucCmpIndex == 0x01)
                {
                    *pucDecmpIndex1 = 0x02;
                    *pucDecmpIndex2 = 0x03;
                }
                else if(ucCmpIndex == 0x02)
                {
                    *pucDecmpIndex1 = 0x01;
                    *pucDecmpIndex2 = 0xFF;
                }
                else if(ucCmpIndex == 0x03)
                {
                    *pucDecmpIndex1 = 0xFF;
                    *pucDecmpIndex2 = 0xFF;
                }
                else
                {
                    *pucDecmpIndex1 = ucCmpIndex;
                    *pucDecmpIndex2 = 0xFF;
                }
                break;

            case _DISPLAY_MODE_3P_SKEW_B:
                // M1 Enc Reg set to M2 Dec Reg for M1/M2 HW on Bot
                // M2 Enc Reg set to S1/S2 Dec Reg for S1/S2 HW
                // S1 Enc Reg set to M1 Dec Reg for M1/M2 HW on Top
                // S2 Enc Reg should be the same as S1 Enc Reg (no use)
                // S3/S4 Enc Reg is equal to S3/S4 Dec Reg
                if(ucCmpIndex == 0x00)
                {
                    *pucDecmpIndex1 = 0x01;
                    *pucDecmpIndex2 = 0xFF;
                }
                else if(ucCmpIndex == 0x01)
                {
                    *pucDecmpIndex1 = 0x02;
                    *pucDecmpIndex2 = 0x03;
                }
                else if(ucCmpIndex == 0x02)
                {
                    *pucDecmpIndex1 = 0x00;
                    *pucDecmpIndex2 = 0xFF;
                }
                else if(ucCmpIndex == 0x03)
                {
                    *pucDecmpIndex1 = 0xFF;
                    *pucDecmpIndex2 = 0xFF;
                }
                else
                {
                    *pucDecmpIndex1 = ucCmpIndex;
                    *pucDecmpIndex2 = 0xFF;
                }
                break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_4P:
                // M1 Enc Reg set to M1 Dec Reg for M1/M2 HW on Top
                // M2 Enc Reg set to M2 Dec Reg for M1/M2 HW on Bot
                // S1 Enc Reg set to S1 Dec Reg for S1/S2 HW on Top
                // S2 Enc Reg set to S2 Dec Reg for S1/S2 HW on Bot
#endif
            default:
                *pucDecmpIndex1 = ucCmpIndex;
                *pucDecmpIndex2 = 0xFF;
                break;
        }
    }
    else
    {
#if(_COLOR_IP_3DDI == _ON)
        // if 3DDI case and S2 input, trans to S1/S2
        if((ucCmpIndex == 0x03) && (enumDisplayMode != _DISPLAY_MODE_4P) && (GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON))
        {
            *pucDecmpIndex1 = 0x02;
            *pucDecmpIndex2 = 0x03;
        }
        else
#endif
        {
            *pucDecmpIndex1 = ucCmpIndex;
            *pucDecmpIndex2 = 0xFF;
        }
    }
}
#endif // End of #if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)


