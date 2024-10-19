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
// ID Code      : ScalerFRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_FRC__

#include "ScalerFunctionInclude.h"
#include "FRC/ScalerFRC.h"

#if(_BW_CUSTOME_MODE == _ENABLE)
#warning "NOTE: _BW_FIX_ORIGINAL_COLOR_DEPTH_TYPE is better to align with _MTP_MAIN_ACCEPT_MIN_COLOR_DEPTH / _MTP_SUB_ACCEPT_MIN_COLOR_DEPTH !!"
#if(_DOLBY_CERTIFICATION_SUPPORT == _ON)
#warning "NOTE: _BW_CUSTOME_MODE conflicts with _DOLBY_CERTIFICATION_SUPPORT"
#endif
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
#warning "NOTE: Please check UserInterfaceDisplayGetHDMIALLMOffLatencyRatio default display latency value!!!"
#endif

#if(_HW_FRC_LENGTH_TYPE == _FRC_LENGTH_7BIT)
#if(_BW_80_PERCENT_1P_SUPPORT == _ON)
#warning "NOTE: Please Check the ID Code(Contact with SDs) When _BW_80_PERCENT_1P_SUPPORT _ON!!!"
#endif
#endif

#if(_M_DOMAIN_FORCE_IMG_CMP == _ON)
#warning "NOTE: _M_DOMAIN_FORCE_IMG_CMP should be set to _OFF in normal case, Please contact SDs!!!"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_FRC_SUPPORT == _ON)

StructFRCRateCtrlParam code tFRCRateCtrlParam[] =
{
#if(_DOLBY_CERTIFICATION_SUPPORT == _ON)
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
    {_COLOR_DEPTH_12_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF},
#else
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_M_DOMAIN_IMG_CMP_10_BIT_SUPPORT == _ON)
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
#endif
#if(_M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT == _OFF)
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_MAX, _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_TYP, _MTP_OD_ACCEPT_MIN_PARAM},
#endif
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_MIN, _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_MIN, _OD_PARAM_OFF           },
    {_COLOR_DEPTH_10_BITS, _ON,  _IMG_CMP_PARAM_LLB_10B_MIN, _OD_PARAM_OFF           },
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
#else
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
#endif
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_LLB_8B_TYP,  _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_LLB_8B_TYP,  _OD_PARAM_OFF           },
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_LLB_8B_TYP,  _OD_PARAM_OFF           },
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
#endif
#else
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
#endif
};

#if(_BW_CUSTOME_MODE == _ENABLE)
StructFRCRateCtrlParam code tFRCRateCtrlParamCustomeFixColorDepth[] =
{
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_M_DOMAIN_IMG_CMP_10_BIT_SUPPORT == _ON)
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
#endif
#if(_M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT == _OFF)
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_MAX, _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_TYP, _MTP_OD_ACCEPT_MIN_PARAM},
#endif
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_MIN, _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _ON,  _IMG_CMP_PARAM_LLB_10B_MIN, _OD_PARAM_OFF           },
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
#else
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
#endif
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_LLB_8B_TYP,  _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_LLB_8B_TYP,  _OD_PARAM_OFF           },
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_LLB_8B_TYP,  _OD_PARAM_OFF           },
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
#endif
#else
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
};

StructFRCRateCtrlParam code tFRCRateCtrlParamCustomeODoffFirst[] =
{
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_M_DOMAIN_IMG_CMP_10_BIT_SUPPORT == _ON)
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
#endif
#if(_M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT == _OFF)
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_MAX, _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_TYP, _MTP_OD_ACCEPT_MIN_PARAM},
#endif
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_MIN, _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_LLB_10B_MIN, _OD_PARAM_OFF           },
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
#else
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
#endif
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_LLB_8B_TYP,  _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_LLB_8B_TYP,  _OD_PARAM_OFF           },
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_LLB_8B_TYP,  _OD_PARAM_OFF           },
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
#endif
#else
    // FIFO_BIT_DEPTH      HSD   ImgCmp                      OD Reserve
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_10_BITS, _OFF, _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
    {_COLOR_DEPTH_8_BITS,  _OFF, _IMG_CMP_PARAM_OFF,         _MTP_OD_ACCEPT_MIN_PARAM},
    {_COLOR_DEPTH_8_BITS,  _ON,  _IMG_CMP_PARAM_OFF,         _OD_PARAM_OFF           },
#endif
};
#endif

BYTE code tFRCRateCtrlbit[][2] =
{
    // FIFO_BIT_DEPTH            ImgCmp
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_M_DOMAIN_IMG_CMP_10_BIT_SUPPORT == _ON)
    {(_COLOR_DEPTH_10_BITS * 3), _IMG_CMP_PARAM_LLB_10B_MIN},
#if(_M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT == _OFF)
    {(_COLOR_DEPTH_10_BITS * 3), _IMG_CMP_PARAM_LLB_10B_TYP},
    {(_COLOR_DEPTH_10_BITS * 3), _IMG_CMP_PARAM_LLB_10B_MAX},
#endif
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {(_COLOR_DEPTH_10_BITS * 3), _IMG_CMP_PARAM_OFF        },
#endif
#else
    {(_COLOR_DEPTH_8_BITS * 3) , _IMG_CMP_PARAM_LLB_8B_TYP },
#if(_M_DOMAIN_FORCE_IMG_CMP == _OFF)
    {(_COLOR_DEPTH_8_BITS * 3) , _IMG_CMP_PARAM_OFF        },
    {(_COLOR_DEPTH_10_BITS * 3), _IMG_CMP_PARAM_OFF        },
#endif
#endif
#else
    {(_COLOR_DEPTH_8_BITS * 3) , _IMG_CMP_PARAM_OFF        },
    {(_COLOR_DEPTH_10_BITS * 3), _IMG_CMP_PARAM_OFF        },
#endif
};

EnumODParamIndex code tODParam[] =
{
    _OD_PARAM_OFF,
#if(_OD_FUNCTION == _ON)
    _OD_PARAM_4_5_BPP,
    _OD_PARAM_6_0_BPP,
    _OD_PARAM_7_5_BPP,
#endif
};
#endif

StructFRCDataPathInfo code tFRCDataPathInfo[] =
{
#if(_HW_M_DOMAIN_M1_PATH_SUPPORT == _ON)
    {_INPUT_PATH_M1,    _MDOMAIN_DISP_PATH_M1,  _FRC_M1, _FRC_MAIN1_PAGE},
#endif
#if(_HW_M_DOMAIN_M2_PATH_SUPPORT == _ON)
    {_INPUT_PATH_M2,    _MDOMAIN_DISP_PATH_M2,  _FRC_M2, _FRC_MAIN2_PAGE},
#endif
#if(_HW_M_DOMAIN_S1_PATH_SUPPORT == _ON)
    {_INPUT_PATH_S1,    _MDOMAIN_DISP_PATH_S1,  _FRC_S1, _FRC_SUB1_PAGE },
#endif
#if(_HW_M_DOMAIN_S2_PATH_SUPPORT == _ON)
    {_INPUT_PATH_S2,    _MDOMAIN_DISP_PATH_S2,  _FRC_S2, _FRC_SUB2_PAGE },
#endif
#if(_HW_M_DOMAIN_S3_PATH_SUPPORT == _ON)
    {_INPUT_PATH_S3,    _MDOMAIN_DISP_PATH_S3,  _FRC_S3, _FRC_SUB3_PAGE },
#endif
#if(_HW_M_DOMAIN_S4_PATH_SUPPORT == _ON)
    {_INPUT_PATH_S4,    _MDOMAIN_DISP_PATH_S4,  _FRC_S4, _FRC_SUB4_PAGE },
#endif
};

EnumFRCChannel code tFRCChannel[] =
{
    _FRC_CH0,
    _FRC_CH1,
    _FRC_CH2,
    _FRC_CH3,
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
bit g_bFRCCapEnRst;
DWORD g_ulFRCUseRow;
DWORD g_ulFRCMainBW;
DWORD g_ulFRCSubBW;
DWORD g_ulFRCRowForMain;
DWORD g_ulFRCRowForSub;
DWORD g_ulFRCSubAllocateIHtotal;
#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
bit g_bFRCModLenWtlvlStatus;
#endif
#if(_HDMI21_ALLM_SUPPORT == _ON)
StructFRCAllmInfo g_stFRCAllmInfo;
#endif
#endif
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
DWORD g_ulFRCRowForRotation;
DWORD g_ulFRCTotalRowForRotation;
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
BYTE g_ucFRCDispLatencyRatio;
#endif

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
WORD g_usFRCAspectRatioMinDVHeight;
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
BYTE g_ucFRCAllmInfoLatencyRatio;
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Map InputDataPath to FRC Index
// Input Value  : enumInputPath
// Output Value : EnumFRCIndex
//--------------------------------------------------
EnumFRCIndex ScalerFRCGetInputDataPathIndexMapping(EnumInputDataPath enumInputPath)
{
    switch(enumInputPath)
    {
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1_M2_S1_S2:
        default:
            return _FRC_INDEX_0;

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
        case _INPUT_PATH_M2:
            return _FRC_INDEX_1;

        case _INPUT_PATH_S1:
        case _INPUT_PATH_S1_S2:
            return _FRC_INDEX_2;
#else
        case _INPUT_PATH_S1:
        case _INPUT_PATH_S1_S2:
            return _FRC_INDEX_1;
#endif

#if(_HW_I_DOMAIN_PATH_COUNT > 3)
        case _INPUT_PATH_S2:
            return _FRC_INDEX_3;

        case _INPUT_PATH_S3_S4:
            return _FRC_INDEX_4;
#endif
    }
}

//--------------------------------------------------
// Description  : Get FRC Page From Index
// Input Value  : ucIndex
// Output Value : EnumFRCPageSelect
//--------------------------------------------------
EnumFRCPageSelect ScalerFRCCapGetPageSelect(EnumInputDataPath enumInputPath)
{
    for(BYTE ucIndex = 0; ucIndex < (sizeof(tFRCDataPathInfo) / sizeof(tFRCDataPathInfo[0])); ucIndex++)
    {
        if((enumInputPath  & GET_FRC_INPUT_DATA_PATH(ucIndex)) == GET_FRC_INPUT_DATA_PATH(ucIndex))
        {
            return GET_FRC_PAGE_SELECT(ucIndex);
        }
    }
    return _FRC_MAIN1_PAGE; // default
}

//--------------------------------------------------
// Description  : Get FRC Display Page From Index
// Input Value  : enumInputPath
// Output Value : EnumFRCPageSelect
//--------------------------------------------------
EnumFRCPageSelect ScalerFRCDispGetPageSelect(EnumInputDataPath enumInputPath)
{
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputPath);

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            return GET_FRC_PAGE_SELECT(ucIndex);
        }
    }

    return _FRC_MAIN1_PAGE; // default
}

//--------------------------------------------------
// Description  : Get Mdomain display path count
// Input Value  : EnumMDomainDisplayDataPath enumMDispPath
// Output Value : Path count
//--------------------------------------------------
BYTE ScalerFRCGetMDispPathCount(EnumMDomainDisplayDataPath enumMDispPath)
{
    BYTE ucPathCnt = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ucIndex++)
    {
        if((enumMDispPath & GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == GET_FRC_OUTPUT_DATA_PATH(ucIndex))
        {
            ucPathCnt += 1;
        }
    }
    return ((ucPathCnt == 0) ? 1 : ucPathCnt);
}

//--------------------------------------------------
// Description  : Get FRC MDomain Display Path
// Input Value  : EnumInputDataPath enumInputPath
// Output Value : EnumMDomainDisplayDataPath
//--------------------------------------------------
EnumMDomainDisplayDataPath ScalerFRCGetMDispPath(EnumInputDataPath enumInputPath)
{
    switch(enumInputPath)
    {
        case _INPUT_PATH_M1:
        default:
            return (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? _MDOMAIN_DISP_PATH_M1_M2 : _MDOMAIN_DISP_PATH_M1;

        case _INPUT_PATH_M1_M2:
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
            {
                return _MDOMAIN_DISP_PATH_M1_M2_S1_S2;
            }
            else
#endif
            {
                return _MDOMAIN_DISP_PATH_M1_M2;
            }

        case _INPUT_PATH_M1_M2_S1_S2:
            return _MDOMAIN_DISP_PATH_M1_M2_S1_S2;

        case _INPUT_PATH_M2:
            return (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? _MDOMAIN_DISP_PATH_M1_M2 : _MDOMAIN_DISP_PATH_M2;


        case _INPUT_PATH_S1:
            return (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? _MDOMAIN_DISP_PATH_S1_S2 : _MDOMAIN_DISP_PATH_S1;

        case _INPUT_PATH_S1_S2:
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
            {
                if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_TB)
                {
                    return _MDOMAIN_DISP_PATH_M1_M2_S1_S2;
                }
                return _MDOMAIN_DISP_PATH_M1_M2;
            }
            else
#endif
            {
                return _MDOMAIN_DISP_PATH_S1_S2;
            }

        case _INPUT_PATH_S2: // fb_4P, eo_3ddi 1->2; eo_4p 1->1
            return ((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE) && (GET_DISPLAY_MODE() == _DISPLAY_MODE_4P)) ? _MDOMAIN_DISP_PATH_S2 : _MDOMAIN_DISP_PATH_S1_S2;

        case _INPUT_PATH_S3_S4:
            return _MDOMAIN_DISP_PATH_S3_S4;

        case _INPUT_PATH_ALL:
            return _MDOMAIN_DISP_PATH_ALL;

        case _INPUT_PATH_NONE:
            return _MDOMAIN_DISP_PATH_NONE;
    }
}

//--------------------------------------------------
// Description  : Get FRC Channel From Input Path
// Input Value  : EnumInputDataPath enumInputPath
// Output Value : EnumFRCChannelIndex
//--------------------------------------------------
EnumFRCChannel ScalerFRCGetChannelFromInputpath(EnumInputDataPath enumInputPath)
{
    switch(enumInputPath)
    {
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1_M2_S1_S2:
        default:
            return _FRC_CH0;

        case _INPUT_PATH_M2:
            return _FRC_CH1;

        case _INPUT_PATH_S1:
            return (_HW_SUB_REGION_INPUT_PATH == _INPUT_PATH_S1) ? _FRC_CH1 : _FRC_CH2;

        case _INPUT_PATH_S1_S2:
            return _FRC_CH1;

        case _INPUT_PATH_S2:
            return (ScalerRegionGetMaxRegionCount() == 2) ? _FRC_CH1 : _FRC_CH3;

        case _INPUT_PATH_S3_S4:
            return (ScalerRegionGetMaxRegionCount() == 2) ? _FRC_CH1 : _FRC_CH2;
    }
}

//--------------------------------------------------
// Description  : Get FRC Page address
// Input Value  : usCurrentPage: Current Page Select
// Output Value : Next Page address
//--------------------------------------------------
EnumFRCChannelPageSelect ScalerFRCGetChannelPage(EnumFRCChannel enumFRCChannel)
{
    switch(enumFRCChannel)
    {
        case _FRC_CH0:
        default:
            return _FRC_CH0_PAGE;

        case _FRC_CH1:
            return _FRC_CH1_PAGE;

        case _FRC_CH2:
            return _FRC_CH2_PAGE;

        case _FRC_CH3:
            return _FRC_CH3_PAGE;
    }
}

//--------------------------------------------------
// Description  : FRC Power on initial
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCPowerOnInitial(void)
{
#if(_FRC_SUPPORT == _ON)
#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
    SET_MOD_FRC_LEN_WTLVL_STATUS(_FALSE);
#endif
#endif

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ucIndex++)
    {
        if(CHK_FRC_PATH(_MDOMAIN_DISP_PATH_ALL, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            // Set Number
            SET_PAGED_BYTE(enumPageSelect, P5_A8_DISP_M1_READ_NUM_TOP_H, 0x00);
            SET_PAGED_BYTE(enumPageSelect, P5_A9_DISP_M1_READ_NUM_TOP_L, 0x01);

            // Set Length, Remain
            SET_PAGED_BYTE(enumPageSelect, P5_AA_DISP_M1_READ_TOP_LEN, ScalerFRCGetAccessLength(_FRC_READ_LENGTH));
            SET_PAGED_BYTE(enumPageSelect, P5_AB_DISP_M1_READ_REMAIN_TOP, ScalerFRCGetAccessLength(_FRC_READ_LENGTH));

            FRC_DISP_LOCAL_DB_APPLY(enumPageSelect);
        }
    }

    ScalerFRCEn(_FRC_ALL_ONOFF, _INPUT_PATH_ALL, _DISABLE);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // Disable rotation
    ScalerRotationSetEnable(_DISABLE);
#endif
}

//--------------------------------------------------
// Description  : FRC function enable/disable
// Input Value  : ucSettingPath: path
// Input Value  : bEn: enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerFRCEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath enumInputPath, bit bEn)
{
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputPath);
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(enumInputPath));
    BYTE ucIndex = 0x00;

    if(bEn == _DISABLE)
    {
        if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
        {
            // Wait _EVENT_IEN_STOP before FRC Capture Disable; idomain path = frc capture path
            if((ScalerGlobalGetIDomainDBStatus(enumInputPath) == _I_DOMAIN_DB_DISABLE) &&
               (GET_PAGED_BIT(ScalerIDomainGetInputPathPage(enumInputPath), P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0) &&
               (enumInputPath != _INPUT_PATH_ALL))
            {
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, enumInputPath);
            }
        }
    }

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            if(bEn == _DISABLE)
            {
                if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
                {
                    // Wait _EVENT_IEN_STOP before FRC Capture Disable; idomain path = frc capture path
                    if((ScalerGlobalGetIDomainDBStatus(enumInputPath) == _I_DOMAIN_DB_DISABLE) &&
                       (GET_PAGED_BIT(GET_IDOMAIN_REG_PAGE(ucIndex), P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0) &&
                       (enumInputPath == _INPUT_PATH_ALL))
                    {
                        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, GET_FRC_INPUT_DATA_PATH(ucIndex));
                    }

                    // Disable Capture Block
                    SET_PAGED_BIT(enumPageSelect, P5_27_CAP_M1_DDR_CTRL1, ~(_BIT7), 0x00);

                    // Reset cap_block_sel
                    SET_PAGED_BIT(enumChannelSel, P46_03_M_CAP_BLOCK_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    SET_PAGED_BIT(enumChannelSel, P46_03_M_CAP_BLOCK_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                }
            }
            else
            {
                if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
                {
                    if(GET_PAGED_BIT(enumPageSelect, P5_27_CAP_M1_DDR_CTRL1, _BIT7) == 0x00)
                    {
                        // Enable Capture Block
                        SET_PAGED_BIT(enumPageSelect, P5_27_CAP_M1_DDR_CTRL1, ~(_BIT7), _BIT7);
                    }
                }
            } // End of if(bEn == _DISABLE)
        }
    }

    for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            // Enable FRC display stop burst en
            SET_PAGED_BIT(enumPageSelect, P5_AE_DISP_M1_DISP_CTRL2, ~(_BIT0), _BIT0);

            if(bEn == _DISABLE)
            {
                if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF)
                {
                    // Disable Display Block
                    SET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT0), 0x00);

                    // Reset cap_block_sel
                    SET_PAGED_BIT(enumChannelSel, P46_82_M_DISP_BLOCK_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    SET_PAGED_BIT(enumChannelSel, P46_82_M_DISP_BLOCK_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                }
            }
            else
            {
                if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF)
                {
                    if(GET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == 0x00)
                    {
                        // Enable Display block
                        SET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT0), _BIT0);
                    }
                }
            } // End of if(bEn == _DISABLE)

            FRC_DISP_LOCAL_DB_APPLY(enumPageSelect);
        }
    }

    if(((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) != 0) && (ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0))
    {
        // Wait double buffer
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Get D Domain Source Select
// Input Value  : EnumInputDataPath
// Output Value : EnumDDomainSourceSelect
//--------------------------------------------------
EnumDDomainSourceSelect ScalerFRCGetSourceSelect(EnumInputDataPath enumInputPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            // Get Frame sync with line buffer mode
            if(GET_PAGED_BIT(enumPageSelect, P5_32_CAP_M1_CTRL, _BIT2) == _BIT2)
            {
                return _DDOMAIN_SRC_FROM_FRAME_SYNC_MODE;
            }
            else
            {
                return _DDOMAIN_SRC_FROM_FRC;
            }
        }
    }

    return _DDOMAIN_SRC_FROM_FRAME_SYNC_MODE;
}

//--------------------------------------------------
// Description  : D Domain Source Select
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetSourceSelect(EnumInputDataPath enumInputPath, EnumDDomainSourceSelect enumSourceSelect)
{
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputPath);
    BYTE ucDisplaySource = ((enumSourceSelect == _DDOMAIN_SRC_FROM_FRAME_SYNC_MODE) ? _BIT2 : 0);

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            // Set Frame sync with line buffer mode
            SET_PAGED_BIT(enumPageSelect, P5_32_CAP_M1_CTRL, ~(_BIT2), ucDisplaySource);
        }
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            // Set Frame sync with line buffer mode
            SET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT2), ucDisplaySource);
            FRC_DISP_LOCAL_DB_APPLY(enumPageSelect);
        }
    }
}

//--------------------------------------------------
// Description  : FRC Initial
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCInitial(void)
{
#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    BYTE ucIndex = 0x00;
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH());
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));

#if(_FRC_SUPPORT == _ON)
    ScalerFRCSetInitialRegValue(GET_MDOMAIN_INPUT_DATA_PATH());
#endif

    if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
    {
        // mute channel will stop frc display from accessing data from fifo
        ScalerFRCMuteChannelControl(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
    }

    // Set Capture / Display Single Buffer Mode
    ScalerFRCSetChannelBlkNum(enumChannelSel, (_FRC_CAP | _FRC_DISP), _MEMORY_1_FRAME_BUFFER);

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

#if(_FRC_SUPPORT == _ON)
            ScalerFRCCalculateAddress(enumPageSelect, ScalerFRCGetShiftBankOffset(enumPageSelect));
#endif // End of #if(_FRC_SUPPORT == _ON)

            // Set Line Mode / Disable local db
            SET_PAGED_BIT(enumPageSelect, P5_28_CAP_M1_DDR_CTRL2, ~(_BIT4 | _BIT1 | _BIT0), 0x00);

            // Capture fifo from I domain
            SET_PAGED_BIT(enumPageSelect, P5_29_CAP_M1_DDR_CTRL3, ~(_BIT2), 0x00);
            SET_PAGED_BIT(enumPageSelect, P5_43_CAP_M1_4CH_CTRL1, ~(_BIT0), _BIT0);
        }
    }

    for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _FALSE)
#endif
            {
                // Set Display Capture data from I-Domain
                SET_PAGED_BIT(enumPageSelect, P5_AF_DISP_M1_DISP_CTRL3_TOP, ~(_BIT2), 0x00);
            }

            // ft prevention disable
            SET_PAGED_BYTE(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, 0x00);

            // Set Line Mode
            SET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT7), 0x00);

            if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
            {
                // need to set frc disp wtlvl = 0 when line buffer, hw bug
                SET_PAGED_BIT(enumPageSelect, P5_A0_DISP_M1_WTLVL_TOP_H, ~(_BIT0), 0);
                SET_PAGED_BYTE(enumPageSelect, P5_A1_DISP_M1_WTLVL_TOP_L, 0x00);
            }

            FRC_DISP_LOCAL_DB_APPLY(GET_FRC_PAGE_SELECT(ucIndex));
        }
    }

#if(_FRC_SUPPORT == _ON)
    // Disable M:N frame tracking
    if((GET_MEMORY_CONFIG_SELECT() != _MN_FRAME_SYNC_MEMORY) && (GET_FORCE_DISPLAY_1P_MODE() == _TRUE))
    {
        ScalerMemorySetFrameTrackingEnable(_DISABLE);
    }
#endif
#endif // end of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

    if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
    {
        ScalerFRCEn(_FRC_ALL_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
#if((_FRC_SUPPORT == _ON) && (_M_DOMAIN_IMG_CMP_SUPPORT == _ON))
        ScalerImgCmpEn(_FRC_ALL_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
#endif
        ScalerFRCSetSourceSelect(GET_MDOMAIN_INPUT_DATA_PATH(), _DDOMAIN_SRC_FROM_FRAME_SYNC_MODE);
    }

#if(_FRC_SUPPORT == _ON)

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    ScalerFRCEOtoFBControl(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_INPUT_HWIDTH(), _DISABLE);
    ScalerFRCFBtoEOControl(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_INPUT_HWIDTH() / 2, _DISABLE);
#endif

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
    // Disable HW auto block toggle
    ScalerFRCSetDisplayAutoBlkToggleEnable(_DISABLE);
#endif
#endif
    // Wait double buffer
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Calculate path line sum bit
// Input Value  : Path H width, FIFO color depth, ImgCmp index
// Output Value : Path line-sum-bit
//--------------------------------------------------
DWORD ScalerFRCGetLineSumBit(WORD usHorSize, BYTE ucFIFOMemBits, EnumImgCmpParamIndex enumImgCmpIndex)
{
    DWORD ulLineSumBit = 0;

    enumImgCmpIndex = enumImgCmpIndex;
#if(_FRC_SUPPORT == _ON)
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    if(GET_IMG_CMP_ENABLE(enumImgCmpIndex) == _TRUE)
    {
        ulLineSumBit = (DWORD)CEILING(usHorSize, _IMG_CMP_BLK_WIDTH) * GET_IMG_CMP_PARAM_LLB(enumImgCmpIndex) + _IMG_CMP_STREAM_END_DUMMY_LEN;
        ulLineSumBit = CEILING(ulLineSumBit, _IMG_CMP_MEM_RW_UNIT);
    }
    else
#endif
#endif
    {
        ulLineSumBit = ((DWORD)usHorSize) * ucFIFOMemBits;
    }

    return ulLineSumBit;
}

//--------------------------------------------------
// Description  : Get FRC Read/ Write Access Length
// Input Value  : EnumFRCReadWriteLength: Get Length Type, Read or Write Lenth
// Output Value : Length
//--------------------------------------------------
BYTE ScalerFRCGetAccessLength(EnumFRCReadWriteLength enumFRCReadWriteLength)
{
    switch(enumFRCReadWriteLength)
    {
        case _FRC_WRITE_LENGTH:
        default:
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
            if(ScalerRotationCheckVerticalStatus() == _TRUE)
            {
                return _FRC_ROTATION_VERTICAL_ACCESS_WRITE_LENGTH;
            }
            else
#endif
            {
#if(_FRC_SUPPORT == _ON)
#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
                if(GET_MOD_FRC_LEN_WTLVL_STATUS() == _TRUE)
                {
                    return _FRC_IMC_ACCESS_WRITE_LENGTH;
                }
                else
#endif
#endif
                {
#if(_FRC_LENGTH_ENLRGE_M1_M2_ONLY == _ON)
                    if(ScalerFRCGetLengthEnlargeM1M2Support() == _ON)
                    {
                        if(GET_1P_EO_STATUS() == _TRUE)
                        {
                            return _FRC_ACCESS_WRITE_LENGTH_ENLRGE;
                        }
                    }
                    else
                    {
                        DebugMessageScaler("FAIL!! Not support _BW_80_PERCENT_1P_SUPPORT, Please Check the ID Code(Contact with SDs)", 0x00);
                    }
#endif
                    return _FRC_ACCESS_WRITE_LENGTH;
                }
            }
            break;

        case _FRC_READ_LENGTH:
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
            if(ScalerRotationCheckVerticalStatus() == _TRUE)
            {
                return _FRC_ROTATION_VERTICAL_ACCESS_READ_LENGTH;
            }
            else
#endif
            {
#if(_FRC_SUPPORT == _ON)
#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
                if(GET_MOD_FRC_LEN_WTLVL_STATUS() == _TRUE)
                {
                    return _FRC_IMC_ACCESS_READ_LENGTH;
                }
                else
#endif
#endif
                {
#if(_FRC_LENGTH_ENLRGE_M1_M2_ONLY == _ON)
                    if(ScalerFRCGetLengthEnlargeM1M2Support() == _ON)
                    {
                        if(GET_1P_EO_STATUS() == _TRUE)
                        {
                            return _FRC_ACCESS_READ_LENGTH_ENLRGE;
                        }
                    }
                    else
                    {
                        DebugMessageScaler("FAIL!! Not support _BW_80_PERCENT_1P_SUPPORT, Please Check the ID Code(Contact with SDs)", 0x00);
                    }
#endif
                    return _FRC_ACCESS_READ_LENGTH;
                }
            }
            break;
    }
}

//--------------------------------------------------
// Description  : Get FRC Frame Buffer Mode or Line Buffer Mode
// Input Value  : enumSelectedDataPath
// Output Value : _TRUE: Line Buffer Mode, _FALSE: Frame Buffer Mode
//--------------------------------------------------
bit ScalerFRCGetLineBufferMode(EnumInputDataPath enumSelectedDataPath)
{
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;

    if((enumSelectedDataPath == _INPUT_PATH_NONE) ||
       (enumSelectedDataPath == _INPUT_PATH_ALL))
    {
        return _TRUE;
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumSelectedDataPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            if(GET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, _BIT2) == _BIT2)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Channel FRC Capture Block Num
// Input Value  : enumFRCChPage
// Output Value : Channel FRC Cap block number
//--------------------------------------------------
EnumFRCChannelCapBlk ScalerFRCGetChannelFRCCapBlkNum(EnumFRCChannelPageSelect enumFRCChPage)
{
    switch(GET_PAGED_BIT(enumFRCChPage, P46_00_M_CAP_BLOCK_CTRL, (_BIT1 | _BIT0)))
    {
        case 0x00:
        default:
            return _FRC_CH_1_BLK;

        case 0x01:
            return _FRC_CH_2_BLK;

        case 0x02:
            return _FRC_CH_3_BLK;

        case 0x03:
            return _FRC_CH_4_BLK;
    }
}

//--------------------------------------------------
// Description  : Set FRC Display Top number, length, remain
// Input Value  : usSelectedPage: FRC page, number and remain, length
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDispTopNumLengthRemain(EnumFRCPageSelect enumPageSelect, DWORD ulNumRemain, BYTE ucLen)
{
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        // Set Number, Length, Remain at ScalerRotationInputCtrl
    }
    else
#endif
    {
        // Set Number
        SET_PAGED_BYTE(enumPageSelect, P5_A8_DISP_M1_READ_NUM_TOP_H, ((ulNumRemain >> 8) & 0xFF));
        SET_PAGED_BYTE(enumPageSelect, P5_A9_DISP_M1_READ_NUM_TOP_L, (ulNumRemain & 0xFF));

        // Set Length, Remain
        SET_PAGED_BYTE(enumPageSelect, P5_AA_DISP_M1_READ_TOP_LEN, ucLen);
        SET_PAGED_BYTE(enumPageSelect, P5_AB_DISP_M1_READ_REMAIN_TOP, ((ulNumRemain >> 16) & 0xFF));
    }
}

//--------------------------------------------------
// Description  : Set FRC Capture number, length, remain
// Input Value  : usSelectedPage: FRC page, number and remain, length
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetCapNumLengthRemain(EnumFRCPageSelect enumPageSelect, DWORD ulNumRemain, BYTE ucLen)
{
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        // Set Number, Length, Remain at ScalerRotationInputCtrl
    }
    else
#endif
    {
        // Set Number
        SET_PAGED_BYTE(enumPageSelect, P5_23_CAP_M1_WR_NUM_H, ((ulNumRemain >> 8) & 0xFF));
        SET_PAGED_BYTE(enumPageSelect, P5_24_CAP_M1_WR_NUM_L, (ulNumRemain & 0xFF));

        // Set Length, Remain
        SET_PAGED_BYTE(enumPageSelect, P5_25_CAP_M1_WR_LEN, ucLen);
        SET_PAGED_BYTE(enumPageSelect, P5_26_CAP_M1_WR_REMAIN, ((ulNumRemain >> 16) & 0xFF));
    }
}

//--------------------------------------------------
// Description  : Set FRC Channel Client
// Input Value  : EnumFRCChannel enumFRCChannel
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetChannelClient(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucFirstClient = 0;
    WORD usClientSel = 0;
    EnumInputDataPath enumInputPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputPath);
    EnumFRCChannelPageSelect enumFRCChPage = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(enumInputPath));

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            ucFirstClient = GET_FRC_CHANNEL_PATH(ucIndex);
            break;
        }
    }

    SET_PAGED_BIT(enumFRCChPage, P46_00_M_CAP_BLOCK_CTRL, ~(_BIT6 | _BIT5 | _BIT4), (ucFirstClient << 4));
    SET_PAGED_BIT(enumFRCChPage, P46_05_M_CAP_DB_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucFirstClient);

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            usClientSel |= GET_FRC_INPUT_DATA_PATH(ucIndex);
        }
    }

    SET_PAGED_BIT(enumFRCChPage, P46_01_M_CAP_CLIENT_SEL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(usClientSel));

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ucIndex++)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            ucFirstClient = GET_FRC_CHANNEL_PATH(ucIndex);
            break;
        }
    }

    usClientSel = 0;
    SET_PAGED_BIT(enumFRCChPage, P46_86_M_DISP_DB_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucFirstClient);

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ucIndex++)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            usClientSel |= GET_FRC_OUTPUT_DATA_PATH(ucIndex);
        }
    }

    SET_PAGED_BIT(enumFRCChPage, P46_81_M_DISP_CLIENT_SEL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usClientSel));

#if((_FRC_SUPPORT == _ON) && (_TB_DISPLAY_MODE_SUPPORT == _ON))
    if(ScalerFRCGetBottomSettingStatusFromInputDataPath(enumInputPath) == _TRUE)
    {
        if((GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_T) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_B))
        {
            usClientSel = _MDOMAIN_DISP_PATH_M1_M2;
        }
        // else, use usClientSel
    }
    else
#endif
    {
        usClientSel = _MDOMAIN_DISP_PATH_NONE;
    }

    SET_PAGED_BIT(enumFRCChPage, P46_85_M_DISP_BOT_CH, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usClientSel));

#if(_FRC_SUPPORT == _ON)
#if((_FREEZE_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
    SET_PAGED_BIT(enumFRCChPage, P46_03_M_CAP_BLOCK_SEL, ~(_BIT4), 0x00);
    SET_PAGED_BIT(enumFRCChPage, P46_82_M_DISP_BLOCK_SEL, ~(_BIT4), 0x00);
#endif
#endif
}

//--------------------------------------------------
// Description  : Set FRC Channel Block number
// Input Value  : EnumFRCChannelPageSelect enumChannelSel, EnumFRCClient enumFRCClient, EnumMemoryFrameBufferType enumFrameBufferType
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetChannelBlkNum(EnumFRCChannelPageSelect enumChannelSel, EnumFRCClient enumFRCClient, EnumMemoryFrameBufferType enumFrameBufferType)
{
    BYTE ucBuffer = 0;

    switch(enumFrameBufferType)
    {
        case _MEMORY_1_FRAME_BUFFER:
        default:
            ucBuffer = 0x00;
            break;

#if(_FRC_SUPPORT == _ON)
        case _MEMORY_2_FRAME_BUFFER:
            ucBuffer = _BIT0;
            break;

        case _MEMORY_3_FRAME_BUFFER:
            ucBuffer = _BIT1;
            break;
#endif
    }

    if((enumFRCClient & _FRC_CAP) == _FRC_CAP)
    {
        SET_PAGED_BIT(enumChannelSel, P46_00_M_CAP_BLOCK_CTRL, ~(_BIT1 | _BIT0), ucBuffer);
    }

    if((enumFRCClient & _FRC_DISP) == _FRC_DISP)
    {
        SET_PAGED_BIT(enumChannelSel, P46_80_M_DISP_BLOCK_CTRL, ~(_BIT1 | _BIT0), ucBuffer);
    }
}

//--------------------------------------------------
// Description  : Set FRC Cap/Disp Channel
// Input Value  : EnumDisplayRegion enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetCapDispChannel(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucIndex = 0x00;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    EnumFRCChannel enumFRCCh = ScalerFRCGetChannelFromInputpath(enumInputDataPath);
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputDataPath);

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputDataPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            SET_PAGED_BIT(enumPageSelect, P5_27_CAP_M1_DDR_CTRL1, ~(_BIT5 | _BIT4), (enumFRCCh << 4));
            // mute channel
            ScalerFRCMuteChannelControl(enumInputDataPath, _ENABLE);
        }
    }

    for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

#if((_FRC_SUPPORT == _ON) && (_TB_DISPLAY_MODE_SUPPORT == _ON))
            SET_PAGED_BIT(enumPageSelect, P5_AE_DISP_M1_DISP_CTRL2, ~(_BIT5), 0x00);

            if(ScalerFRCGetBottomSettingStatusFromPage(enumInputDataPath, enumPageSelect) == _TRUE)
            {
                SET_PAGED_BIT(enumPageSelect, P5_FA_DISP_M1_DISP_CTRL3_BOT, ~(_BIT1 | _BIT0), enumFRCCh);
            }
            else
#endif
            {
                SET_PAGED_BIT(enumPageSelect, P5_AF_DISP_M1_DISP_CTRL3_TOP, ~(_BIT1 | _BIT0), enumFRCCh);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Mute/Unmute FRC Channel
// Input Value  : EnumInputDataPath enumInputPath, bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerFRCMuteChannelControl(EnumInputDataPath enumInputPath, bit bEnable)
{
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(enumInputPath));
    SET_PAGED_BIT(enumChannelSel, P46_F1_M_MISC, ~(_BIT0), bEnable);
}

//--------------------------------------------------
// Description  : Get Mute/Unmute FRC Channel Setting
// Input Value  : EnumInputDataPath enumInputPath
// Output Value : bit bEnable, P46_F1[0]=1: Mute (_DISABLE), P46_F1[0]=0: Normal (_ENABLE)
//--------------------------------------------------
bit ScalerFRCGetMuteChannelEnable(EnumInputDataPath enumInputPath)
{
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(enumInputPath));
    return ((GET_PAGED_BIT(enumChannelSel, P46_F1_M_MISC, _BIT0)) ? _DISABLE : _ENABLE);
}

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRC control
// Input Value  : stFIFOSize --> FIFO size
// Output Value : None
//--------------------------------------------------
void ScalerFRCControl(StructSDRAMDataInfo *pstFIFOSize)
{
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    // enable flow: enable i domain, d domain, m domain
    // eotofb -> imc enc -> imc dec -> fbtoeo -> frc

    if(ScalerFRCGetEOtoFBStatus() == _TRUE) // eotofb ihwidth reference to ScalerScalingUpdateFIFOScalingSize
    {
        ScalerFRCEOtoFBControl(GET_MDOMAIN_INPUT_DATA_PATH(), pstFIFOSize->usInputHWidth, _ENABLE);
    }
    else
    {
        ScalerFRCEOtoFBControl(GET_MDOMAIN_INPUT_DATA_PATH(), pstFIFOSize->usInputHWidth, _DISABLE);
    }
#endif

    ScalerFRCUpdateFifoScalingSize(pstFIFOSize);

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    // Set ImgCmp param
    ScalerImgCmpCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight, GET_IMG_CMP_PARAM());
#endif

    ScalerFRCSetMemoryBoundary(_FRC_BOUNDARY_DEFAULT);

    // -----------------------
    // Set FRC IVS2DVSDelay
    // -----------------------
    ScalerFRCAdjustIVS2DVSDelay();

    // -----------------------
    // Consider Input Faster Or Slower
    // -----------------------
    ScalerFRCCompareDenForFRCStyle();

    // -----------------------
    // Set Frame tracking function for VFreq < 30Hz
    // -----------------------
    if((GET_MEMORY_CONFIG_SELECT() == _MN_FRAME_SYNC_MEMORY) && (GET_FORCE_DISPLAY_1P_MODE() == _TRUE))
    {
        ScalerMemoryFrameTracking();
        ScalerMemorySetFrameTrackingEnable(_ENABLE);
    }

    // -----------------------
    // Set Up FRC Capture
    // -----------------------
    ScalerFRCInputCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Up FRC Display
    // -----------------------
    ScalerFRCDisplayCtrl(pstFIFOSize->usOutputHWidth, pstFIFOSize->usOutputVHeight);

    if((GET_MEMORY_CONFIG_SELECT() == _MN_FRAME_SYNC_MEMORY) && (GET_FORCE_DISPLAY_1P_MODE() == _TRUE))
    {
#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
        if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
        {
            ScalerFRCSetDisplayAutoBlkToggleEnable(_ENABLE);
        }
#endif
    }
    // -----------------------
    // Enable FRC
    // -----------------------

    // Wait I-domain Stable Before FRC enable
    if(ScalerGlobalGetIDomainDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _I_DOMAIN_DB_DISABLE)
    {
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE)
    {
        ScalerImgCmpEn(_FRC_ALL_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
    }
    else
    {
        ScalerImgCmpEn(_FRC_ALL_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
    }
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    if(ScalerFRCGetFBtoEOStatus() == _TRUE)
    {
        ScalerFRCFBtoEOControl(GET_MDOMAIN_INPUT_DATA_PATH(), pstFIFOSize->usInputHWidth, _ENABLE);
    }
    else
    {
        ScalerFRCFBtoEOControl(GET_MDOMAIN_INPUT_DATA_PATH(), pstFIFOSize->usInputHWidth, _DISABLE);
    }
#endif

    ScalerFRCSetFRCEnble();

    // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
    if(ScalerGlobalGetIDomainDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _I_DOMAIN_DB_DISABLE)
    {
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    // -----------------------
    // Set Double / Single Frame Buffer
    // -----------------------
    // Wait _EVENT_IEN_START Before Double Frame Buffer Setting
    if(ScalerGlobalGetIDomainDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _I_DOMAIN_DB_DISABLE)
    {
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    // ----------------------------------
    // Set Cap blk free to avoid deadlock
    // ----------------------------------
    SET_PAGED_BIT(enumChannelSel, P46_03_M_CAP_BLOCK_SEL, ~(_BIT3), _BIT3);

    ScalerFRCSetChannelBlkNum(enumChannelSel, (_FRC_CAP | _FRC_DISP), GET_MEMORY_FRAME_BUFFER());

    if((ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) & _I_DB_ENABLE) == 0x00)
    {
        ScalerFRCWaitIVSAdjust(GET_MEMORY_FRAME_BUFFER(), GET_MDOMAIN_INPUT_DATA_PATH());
    }

#if(_MDOMAIN_PR_MODE_SUPPORT == _OFF)
    // Prevent frame tear, only under memory work mode, doesn't support under one frame frc and 1.5 frame buffer
    if(((GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER) && (GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY)) || (GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER))
    {
        ScalerFRCSetFrameTearPrevent(GET_MDOMAIN_INPUT_DATA_PATH());
    }
#endif

    SET_PAGED_BIT(enumChannelSel, P46_03_M_CAP_BLOCK_SEL, ~(_BIT3), 0x00);

    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {
        // Wait double buffer
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }

    DebugMessageFRC("FRC-H", pstFIFOSize->usInputHWidth);
    DebugMessageFRC("FRC-V", pstFIFOSize->usInputVHeight);
}

//--------------------------------------------------
// Description  : IN1 FIFO Setting for FRC Mode
// Input Value  : ucSettingPath --> Path
//                ucHorSize --> Horizontal size
//                ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep = {0};
    DWORD ulTemp = 0;
    DWORD ulLinetotalpixel = 0;
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    BYTE ucLen = 0;

    stStep.usHorSize = usHorSize;
    stStep.usVerSize = usVerSize;

    if(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) != _INPUT_PATH_1)
    {
        // Let E/O setting complete in VSync period
        if(ScalerGlobalGetIDomainDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _I_DOMAIN_DB_DISABLE)
        {
            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, (GET_MDOMAIN_INPUT_DATA_PATH() & (_INPUT_PATH_M2 | _INPUT_PATH_S2)));
        }
    }
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON) // usHorSize need to divided by 2 before calculating num*len+remain under imc 2 slice mode
    if(ScalerImgCmpGetMultiSliceEn(GET_MODE_DISPLAY_TARGET_REGION()) == _ENABLE)
    {
        usHorSize /= 2;
    }
#endif
    ulLinetotalpixel = ScalerFRCGetLineSumBit(usHorSize, GET_MEMORY_DATA_BIT(), GET_IMG_CMP_PARAM());
    ulLinetotalpixel = CEILING_OF_INT_DIVISION(ulLinetotalpixel, _FRC_UNIT);

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON) // ulLinetotalpixel need to multiplied by 2 because of previous division
    if(ScalerImgCmpGetMultiSliceEn(GET_MODE_DISPLAY_TARGET_REGION()) == _ENABLE)
    {
        ulLinetotalpixel *= 2;
    }
#endif
    // Calculate Line Step and Block Step
    ScalerMemoryCalculateLineStepAndBlockStep(ulLinetotalpixel, &stStep);

#if((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) && (_FRC_CAPTURE_BW_CTRL_SUPPORT == _ON))
    // Update BW Ctrl client info
    StructBwCtrlClientInfo stBwCtrlInfo = {0};
    ScalerFRCBwCtrlGetCapClientInfo(&stBwCtrlInfo);
#endif

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
#if((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) && (_FRC_CAPTURE_BW_CTRL_SUPPORT == _ON))
            // FRC Cap BW Ctrl
            ScalerMemorySetBwCtrl(_MEM_CLIENT_FRC_CAP, ucIndex, &stBwCtrlInfo);
#endif

#if(_CHECK_ENOUGH_SPACE_SUPPORT == _ON)
            // Do not change address if HSD is caused by space/BW insufficient!!!
            if(GET_FRC_RCP_HSD_EN(GET_MDOMAIN_FRC_CTRL_PARAM_INDEX(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()))) == _FALSE)
            {
                if((enumPageSelect == _FRC_SUB1_PAGE) || (enumPageSelect == _FRC_SUB2_PAGE))
                {
                    // avoid sub grabage when reset to display setting without mute
                }
                else
                {
                    ScalerFRCSetCapAddress(enumPageSelect, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(enumPageSelect, _FRC_1ST_BLOCK) + stStep.ulBlockStep);
                }
            }
#endif
#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
            // Set M:N auto block toggle
            if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
            {
                ScalerFRCSetInputAutoBlkToggle();
            }
#endif

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
            SET_MOD_FRC_LEN_WTLVL_STATUS(ScalerFRCModLenWtlvl());
#endif
            // Set Cap FIFO source: I-Domain/PQC
            if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE)
            {
                SET_PAGED_BIT(enumPageSelect, P5_29_CAP_M1_DDR_CTRL3, ~(_BIT2), _BIT2);
            }
            else
#endif
            {
                SET_PAGED_BIT(enumPageSelect, P5_29_CAP_M1_DDR_CTRL3, ~(_BIT2), 0x00);
            }

            ucLen = ScalerFRCGetAccessLength(_FRC_WRITE_LENGTH);

            // Calculate Number of One Line and Remain of One Line
            ulTemp = ScalerMemoryCalculateNumberAndRemain(ulLinetotalpixel, ucLen, 1);

            // Set Line Mode
            SET_PAGED_BIT(enumPageSelect, P5_28_CAP_M1_DDR_CTRL2, ~(_BIT4), 0x00);

            // Set Water level
            SET_PAGED_BIT(enumPageSelect, P5_1D_CAP_M1_WATER_LEVEL_H, ~(_BIT0), ((((WORD)ucLen / 2) >> 8) & 0x01));
            SET_PAGED_BYTE(enumPageSelect, P5_1E_CAP_M1_WATER_LEVEL_L, (((WORD)ucLen / 2) & 0xFF));

            // Set Line Number
            ScalerFRCSetCapLinenum(enumPageSelect, usVerSize);

            // Set Number, Length, Remain
            ScalerFRCSetCapNumLengthRemain(enumPageSelect, ulTemp, ucLen);

            // Set Line step
            ScalerFRCSetCapLinestep(enumPageSelect, stStep.ulLineStep);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            ScalerRotationInputCtrl(enumPageSelect, &stStep);
#endif
            // Use IVS as synchronous reset
            SET_PAGED_BIT(enumPageSelect, P5_27_CAP_M1_DDR_CTRL1, ~(_BIT1), _BIT1);
        }
    }
}

//--------------------------------------------------
// Description  : MAIN FIFO Setting for FRC Mode
// Input Value  : usHorSize --> Horizontal size
//                usVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep = {0};
    DWORD ulTemp = 0;
    DWORD ulLinetotalpixel = 0;
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    WORD usPreReadLine = 0;
    BYTE ucIndex = 0x00;
    BYTE ucLen = ScalerFRCGetAccessLength(_FRC_READ_LENGTH);
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH());

    stStep.usHorSize = usHorSize;
    stStep.usVerSize = usVerSize;

    if(ScalerFRCGetMDispPathCount(enumMDispPath) != _DISPLAY_PATH_1)
    {
        // Let E/O setting complete in VSync period
        if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
        }
    }

    ulLinetotalpixel = ScalerFRCGetLineSumBit(usHorSize, GET_MEMORY_DATA_BIT(), GET_IMG_CMP_PARAM());
    ulLinetotalpixel = CEILING_OF_INT_DIVISION(ulLinetotalpixel, _FRC_UNIT);

    // Calculate Line Step And Block Step
    ScalerMemoryCalculateLineStepAndBlockStep(ulLinetotalpixel, &stStep);

    // Calculate Number of One Line and Remain of One Line
    ulTemp = ScalerMemoryCalculateNumberAndRemain(ulLinetotalpixel, ucLen, 1);

#if(_COLOR_IP_3DDI == _ON)
    // only for eo mode, s2 3ddi
    if((GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON) && (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2))
    {
        DWORD ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB2_PAGE);
        DWORD uleven_path_start_address = ((GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE) ? ulLinetotalpixel : ulLinestep);
        BYTE ucIMClinestep_factor = ((GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE) ? 1 : 2);

        ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetDispAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK));
        ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetDispAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK));
        ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK, (ScalerFRCGetDispAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK) + uleven_path_start_address));
        ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK, (ScalerFRCGetDispAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK) + uleven_path_start_address));
        stStep.ulLineStep = ulLinestep * ucIMClinestep_factor;
    }
#endif

    // Calculate total 128bits per frame
    ulLinetotalpixel = ScalerFRCGetLineSumBit(usHorSize, GET_MEMORY_DATA_BIT(), GET_IMG_CMP_PARAM());
    ulLinetotalpixel = CEILING_OF_INT_DIVISION(ulLinetotalpixel, _FRC_TOTAL_128BIT) * usVerSize;

#if((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) && (_FRC_DISPLAY_BW_CTRL_SUPPORT == _ON))
    // Update BW Ctrl client info
    StructBwCtrlClientInfo stBwCtrlInfo = {0};
    ScalerFRCBwCtrlGetDispClientInfo(&stBwCtrlInfo);
#endif

    for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

#if((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) && (_FRC_DISPLAY_BW_CTRL_SUPPORT == _ON))
            // FRC Disp BW Ctrl
            ScalerMemorySetBwCtrl(_MEM_CLIENT_FRC_DISP, ucIndex, &stBwCtrlInfo);
#endif

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
            {
                if((GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_T) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_B))
                {
                    if((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M1_M2) || (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2))
                    {
                        // set tb enable
                        ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2, ~(_BIT5), _BIT5);
                        ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~(_BIT5), _BIT5);
                    }
                }
                else if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_TB) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_4P))
                {
                    // set tb enable
                    SET_PAGED_BIT(enumPageSelect, P5_AE_DISP_M1_DISP_CTRL2, ~(_BIT5), _BIT5);
                }
            }
            if(ScalerFRCGetBottomSettingStatusFromPage(GET_MDOMAIN_INPUT_DATA_PATH(), enumPageSelect) == _TRUE)
            {
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
                // Set Disp FIFO output: D-Domain/PQC
                if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE)
                {
                    SET_PAGED_BIT(enumPageSelect, P5_FA_DISP_M1_DISP_CTRL3_BOT, ~(_BIT2), _BIT2);
                }
                else
#endif
                {
                    SET_PAGED_BIT(enumPageSelect, P5_FA_DISP_M1_DISP_CTRL3_BOT, ~(_BIT2), 0x00);
                }

                // Set Line Step
                SET_PAGED_BIT(enumPageSelect, P5_F0_DISP_M1_LINE_STEP_BOT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulLineStep >> 24) & 0x0F));
                SET_PAGED_BYTE(enumPageSelect, P5_F1_DISP_M1_LINE_STEP_BOT_H, ((stStep.ulLineStep >> 16) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_F2_DISP_M1_LINE_STEP_BOT_M, ((stStep.ulLineStep >> 8) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_F3_DISP_M1_LINE_STEP_BOT_L, (stStep.ulLineStep & 0xFF));

                // Set Water Level
                // Display Water Level < FIFO Depth (512) - Length / 2
                SET_PAGED_BIT(enumPageSelect, P5_F4_DISP_M1_WTLVL_BOT_H, ~(_BIT0), (_FRC_DISP_WTLVL >> 8));
                SET_PAGED_BYTE(enumPageSelect, P5_F5_DISP_M1_WTLVL_BOT_L, (BYTE)(_FRC_DISP_WTLVL & 0xFF));

                // Set Pixel Number
                SET_PAGED_BYTE(enumPageSelect, P5_F6_DISP_M1_PXL_NUM_BOT_H, HIBYTE(usHorSize));
                SET_PAGED_BYTE(enumPageSelect, P5_F7_DISP_M1_PXL_NUM_BOT_L, LOBYTE(usHorSize));

                // Set Line number
                SET_PAGED_BYTE(enumPageSelect, P5_F8_DISP_M1_LINE_NUM_BOT_H, HIBYTE(usVerSize));
                SET_PAGED_BYTE(enumPageSelect, P5_F9_DISP_M1_LINE_NUM_BOT_L, LOBYTE(usVerSize));

                usPreReadLine = ScalerFRCSetDiffPreReadByPath(enumPageSelect);
                SET_PAGED_BYTE(enumPageSelect, P5_D9_DISP_M1_PRRD_VST_H_BOT, HIBYTE(usPreReadLine));
                SET_PAGED_BYTE(enumPageSelect, P5_DA_DISP_M1_PRRD_VST_L_BOT, LOBYTE(usPreReadLine));

                // Set Number
                SET_PAGED_BYTE(enumPageSelect, P5_FB_DISP_M1_READ_NUM_BOT_H, ((ulTemp >> 8) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_FC_DISP_M1_READ_NUM_BOT_L, (ulTemp & 0xFF));

                // Set Length, Remain
                SET_PAGED_BYTE(enumPageSelect, P5_FD_DISP_M1_READ_BOT_LEN, ucLen);
                SET_PAGED_BYTE(enumPageSelect, P5_FE_DISP_M1_READ_REMAIN_BOT, ((ulTemp >> 16) & 0xFF));

                // Set total 128 bit
                SET_PAGED_BIT(enumPageSelect, P5_D5_DISP_M1_TOTAL_128_BOT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulLinetotalpixel >> 24) & 0x0F));
                SET_PAGED_BYTE(enumPageSelect, P5_D6_DISP_M1_TOTAL_128_BOT_H, ((ulLinetotalpixel >> 16) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_D7_DISP_M1_TOTAL_128_BOT_M, ((ulLinetotalpixel >> 8) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_D8_DISP_M1_TOTAL_128_BOTD_L, (ulLinetotalpixel & 0xFF));
            }
            else
#endif
            {
#if(_CHECK_ENOUGH_SPACE_SUPPORT == _ON)
                ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(enumPageSelect, _FRC_2ND_BLOCK));
#endif

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
                // Set Disp FIFO output: D-Domain/PQC
                if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE)
                {
                    SET_PAGED_BIT(enumPageSelect, P5_AF_DISP_M1_DISP_CTRL3_TOP, ~(_BIT2), _BIT2);
                }
                else
#endif
                {
                    SET_PAGED_BIT(enumPageSelect, P5_AF_DISP_M1_DISP_CTRL3_TOP, ~(_BIT2), 0x00);
                }

                // Set Line Step
                ScalerFRCSetDispTopLinestep(enumPageSelect, stStep.ulLineStep);

                // Set Water Level
                // Display Water Level < FIFO Depth (512) - Length / 2
                ScalerFRCSetDispTopWaterLevel(enumPageSelect, ucLen);

                // Set Pixel Number
                SET_PAGED_BYTE(enumPageSelect, P5_A2_DISP_M1_PXL_NUM_TOP_H, HIBYTE(usHorSize));
                SET_PAGED_BYTE(enumPageSelect, P5_A3_DISP_M1_PXL_NUM_TOP_L, LOBYTE(usHorSize));

                // Set Line number
                SET_PAGED_BYTE(enumPageSelect, P5_A4_DISP_M1_LINE_NUM_TOP_H, HIBYTE(usVerSize));
                SET_PAGED_BYTE(enumPageSelect, P5_A5_DISP_M1_LINE_NUM_TOP_L, LOBYTE(usVerSize));

                usPreReadLine = ScalerFRCSetDiffPreReadByPath(enumPageSelect);
                SET_PAGED_BYTE(enumPageSelect, _REG_FRC_DISP_PRRD_VST_TOP_H, HIBYTE(usPreReadLine));
                SET_PAGED_BYTE(enumPageSelect, _REG_FRC_DISP_PRRD_VST_TOP_L, LOBYTE(usPreReadLine));

                // Set Number, Length, Remain
                ScalerFRCSetDispTopNumLengthRemain(enumPageSelect, ulTemp, ucLen);

                // Set total 128 bit
                SET_PAGED_BIT(enumPageSelect, P5_D1_DISP_M1_TOTAL_128_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulLinetotalpixel >> 24) & 0x0F));
                SET_PAGED_BYTE(enumPageSelect, P5_D2_DISP_M1_TOTAL_128_TOP_H, ((ulLinetotalpixel >> 16) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_D3_DISP_M1_TOTAL_128_TOP_M, ((ulLinetotalpixel >> 8) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_D4_DISP_M1_TOTAL_128_TOP_L, (ulLinetotalpixel & 0xFF));
            }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            ScalerRotationDisplayCtrl(enumPageSelect, &stStep);
#endif
            // Set Line mode
            SET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, ~_BIT7, 0x00);
        }
    }

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
    if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
    {
        ScalerFRCTopBottomModeDisplaySetting(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));
    }
#endif

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
    if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
    {
        ScalerFRCSetDisplayAutoBlkToggle();
        ScalerFRCSetHWAutoBlockToggle();
    }
#endif

    if(ScalerFRCGetSourceSelect(GET_MDOMAIN_INPUT_DATA_PATH()) == _DDOMAIN_SRC_FROM_FRAME_SYNC_MODE)
    {
        SET_FRC_CAP_EN_RESET(_TRUE);
    }
    else
    {
        SET_FRC_CAP_EN_RESET(_FALSE);
    }

    // Set Using Information From FRC Capture
    ScalerFRCSetSourceSelect(GET_MDOMAIN_INPUT_DATA_PATH(), _DDOMAIN_SRC_FROM_FRC);

    // Wait double buffer apply
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {
        // Enable FRC Display double buffer
        for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
            {
                FRC_DISP_LOCAL_DB_APPLY(GET_FRC_PAGE_SELECT(ucIndex));
            }
        }

        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : FRC Capture and Display Enable Setting
// Input Value  : ON --> Freeze
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetFRCEnble(void)
{
    // -- 1 -- Enable FRC Capture
    ScalerFRCEn(_FRC_CAPTURE_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);

    // Wait _EVENT_DEN_START for FRC Display Enable At The Same Time
    if((ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) != _INPUT_PATH_1) && (ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0))
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
    }

    // -- 2 -- Enable FRC Display
    ScalerFRCEn(_FRC_DISPLAY_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
}

//--------------------------------------------------
// Description  : FRC Channel Mute and DTG Enable Setting
// Input Value  : bit bEn
// Output Value : None
//--------------------------------------------------
void ScalerFRCChannelMuteDTGEnable(EnumInputDataPath enumInputPath, EnumDDomainRegion enumDDomainRegion, EnumDisplayRegion enumDisplayRegion, bit bEn)
{
    bit bDDomainDBStatus = ScalerGlobalGetDDomainDBStatus();

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    bit bForceMomainApply = (((ScalerFRCGetMuteChannelEnable(enumInputPath) == _DISABLE) && (bEn == _ENABLE)) ? _TRUE : _FALSE);
#endif

    if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
    {
        return;
    }

    if(bDDomainDBStatus == _DISABLE)
    {
        ScalerGlobalDDomainDoubleBufferEnable(_ENABLE);
    }

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    if(bForceMomainApply == _TRUE)
    {
        ScalerGlobalDoubleBufferMdomainForceApplyEnable(_ENABLE);
    }
#endif

    // Enable Active Region after FRC Display Enable to avoid DDomain underflow temporarily
    ScalerMDomainSetDisplayTimingGenActiveEnable(enumDDomainRegion, enumDisplayRegion, bEn);
    ScalerFRCMuteChannelControl(enumInputPath, !(bEn));

    ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), _DB_APPLY_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    if(bForceMomainApply == _TRUE)
    {
        ScalerGlobalDoubleBufferMdomainForceApplyEnable(_DISABLE);
    }
#endif

    if(bDDomainDBStatus == _DISABLE)
    {
        ScalerGlobalDDomainDoubleBufferEnable(bDDomainDBStatus);
    }
}

//--------------------------------------------------
// Description  : FRC wait IVS by Frame buffer number
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCWaitIVSAdjust(EnumMemoryFrameBufferType enumMemoryFrameBufferType, EnumInputDataPath enumInputPath)
{
    switch(enumMemoryFrameBufferType)
    {
        case _MEMORY_1_FRAME_BUFFER:
        default:

            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            break;

        case _MEMORY_2_FRAME_BUFFER:

            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            break;

        case _MEMORY_3_FRAME_BUFFER:

            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
            break;
    }
}

//--------------------------------------------------
// Description  : Get FRC Capture address
// Input Value  : usSelectedPage: FRC page, ucBlock: Capture Block
// Output Value : address
//--------------------------------------------------
DWORD ScalerFRCGetCapAddress(WORD usSelectedPage, EnumFRCBlock enumBlock)
{
    // affect scaler.GLOBAL
    // to do
    switch(enumBlock)
    {
        case _FRC_1ST_BLOCK:
        default:

            PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_00_CAP_M1_MEM_ADDR_MSB, 0x0F) << 24) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_01_CAP_M1_MEM_ADDR_H) << 16) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_02_CAP_M1_MEM_ADDR_M) << 8) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_03_CAP_M1_MEM_ADDR_L)));
            break;

        case _FRC_2ND_BLOCK:

            PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_04_CAP_M1_BL2_ADDR_MSB, 0x0F) << 24) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_05_CAP_M1_BL2_ADDR_H) << 16) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_06_CAP_M1_BL2_ADDR_M) << 8) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_07_CAP_M1_BL2_ADDR_L)));
            break;

        case _FRC_3RD_BLOCK:

            PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_08_CAP_M1_BL3_ADDR_MSB, 0x0F) << 24) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_09_CAP_M1_BL3_ADDR_H) << 16) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_0A_CAP_M1_BL3_ADDR_M) << 8) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_0B_CAP_M1_BL3_ADDR_L)));
            break;

        case _FRC_4TH_BLOCK:

            PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_46_CAP_M1_BL4_ADDR_MSB, 0x0F) << 24) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_47_CAP_M1_BL4_ADDR_H) << 16) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_48_CAP_M1_BL4_ADDR_M) << 8) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_49_CAP_M1_BL4_ADDR_L)));
            break;
    }

    return PDATA_DWORD(0);
}

//--------------------------------------------------
// Description  : Get FRC Display address
// Input Value  : usSelectedPage: FRC page, ucBlock: Disp Block
// Output Value : address
//--------------------------------------------------
DWORD ScalerFRCGetDispAddress(WORD usSelectedPage, EnumFRCBlock enumBlock)
{
    // affect scaler.GLOBAL
    // to do
    switch(enumBlock)
    {
        case _FRC_1ST_BLOCK:
        default:

            PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_80_DISP_M1_BLK_ADDR_1ST_TOP_MSB, 0x0F) << 24) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_81_DISP_M1_BLK_ADDR_1ST_TOP_H) << 16) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_82_DISP_M1_BLK_ADDR_1ST_TOP_M) << 8) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_83_DISP_M1_BLK_ADDR_1ST_TOP_L)));
            break;

        case _FRC_2ND_BLOCK:

            PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_84_DISP_M1_BLK_ADDR_2ND_TOP_MSB, 0x0F) << 24) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_85_DISP_M1_BLK_ADDR_2ND_TOP_H) << 16) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_86_DISP_M1_BLK_ADDR_2ND_TOP_M) << 8) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_87_DISP_M1_BLK_ADDR_2ND_TOP_L)));
            break;

        case _FRC_3RD_BLOCK:

            PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_88_DISP_M1_BLK_ADDR_3RD_TOP_MSB, 0x0F) << 24) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_89_DISP_M1_BLK_ADDR_3RD_TOP_H) << 16) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_8A_DISP_M1_BLK_ADDR_3RD_TOP_M) << 8) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_8B_DISP_M1_BLK_ADDR_3RD_TOP_L)));
            break;

        case _FRC_4TH_BLOCK:

            PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_8C_DISP_M1_BLK_ADDR_4TH_TOP_MSB, 0x0F) << 24) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_8D_DISP_M1_BLK_ADDR_4TH_TOP_H) << 16) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_8E_DISP_M1_BLK_ADDR_4TH_TOP_M) << 8) |
                              ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_8F_DISP_M1_BLK_ADDR_4TH_TOP_L)));
            break;
    }

    return PDATA_DWORD(0);
}

//--------------------------------------------------
// Description  : Set FRC Capture address
// Input Value  : usSelectedPage: FRC page, ucBlock: Capture Block, ulCapAddress
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetCapAddress(WORD usSelectedPage, EnumFRCBlock enumBlock, DWORD ulCapAddress)
{
    // affect scaler.GLOBAL
    // to do
    switch(enumBlock)
    {
        case _FRC_1ST_BLOCK:
        default:
            SET_PAGED_BIT(usSelectedPage, P5_00_CAP_M1_MEM_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulCapAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_01_CAP_M1_MEM_ADDR_H, ((ulCapAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_02_CAP_M1_MEM_ADDR_M, ((ulCapAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_03_CAP_M1_MEM_ADDR_L, (ulCapAddress & 0xFE));
            break;

        case _FRC_2ND_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_04_CAP_M1_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulCapAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_05_CAP_M1_BL2_ADDR_H, ((ulCapAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_06_CAP_M1_BL2_ADDR_M, ((ulCapAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_07_CAP_M1_BL2_ADDR_L, (ulCapAddress & 0xFE));
            break;

        case _FRC_3RD_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_08_CAP_M1_BL3_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulCapAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_09_CAP_M1_BL3_ADDR_H, ((ulCapAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_0A_CAP_M1_BL3_ADDR_M, ((ulCapAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_0B_CAP_M1_BL3_ADDR_L, (ulCapAddress & 0xFE));
            break;

        case _FRC_4TH_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_46_CAP_M1_BL4_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulCapAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_47_CAP_M1_BL4_ADDR_H, ((ulCapAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_48_CAP_M1_BL4_ADDR_M, ((ulCapAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_49_CAP_M1_BL4_ADDR_L, (ulCapAddress & 0xFE));
            break;
    }
}

//--------------------------------------------------
// Description  : Set FRC Display address
// Input Value  : usSelectedPage: FRC page, ucBlock: Capture Block, ulCapAddress
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDispAddress(WORD usSelectedPage, EnumFRCBlock enumBlock, DWORD ulDispAddress)
{
    switch(enumBlock)
    {
        case _FRC_1ST_BLOCK:
        default:

            SET_PAGED_BIT(usSelectedPage, P5_80_DISP_M1_BLK_ADDR_1ST_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulDispAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_81_DISP_M1_BLK_ADDR_1ST_TOP_H, ((ulDispAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_82_DISP_M1_BLK_ADDR_1ST_TOP_M, ((ulDispAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_83_DISP_M1_BLK_ADDR_1ST_TOP_L, (ulDispAddress & 0xFE));
            break;

        case _FRC_2ND_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_84_DISP_M1_BLK_ADDR_2ND_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulDispAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_85_DISP_M1_BLK_ADDR_2ND_TOP_H, ((ulDispAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_86_DISP_M1_BLK_ADDR_2ND_TOP_M, ((ulDispAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_87_DISP_M1_BLK_ADDR_2ND_TOP_L, (ulDispAddress & 0xFE));
            break;

        case _FRC_3RD_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_88_DISP_M1_BLK_ADDR_3RD_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulDispAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_89_DISP_M1_BLK_ADDR_3RD_TOP_H, ((ulDispAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_8A_DISP_M1_BLK_ADDR_3RD_TOP_M, ((ulDispAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_8B_DISP_M1_BLK_ADDR_3RD_TOP_L, (ulDispAddress & 0xFE));
            break;

        case _FRC_4TH_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_8C_DISP_M1_BLK_ADDR_4TH_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulDispAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_8D_DISP_M1_BLK_ADDR_4TH_TOP_H, ((ulDispAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_8E_DISP_M1_BLK_ADDR_4TH_TOP_M, ((ulDispAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_8F_DISP_M1_BLK_ADDR_4TH_TOP_L, (ulDispAddress & 0xFE));
            break;
    }
}

//--------------------------------------------------
// Description  : Set FRC Display Top linestep
// Input Value  : usSelectedPage: FRC page, ulLinestep
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDispTopLinestep(WORD usSelectedPage, DWORD ulLinestep)
{
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        SET_PAGED_BIT(usSelectedPage, P5_99_DISP_M1_LINE_STEP_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        SET_PAGED_BYTE(usSelectedPage, P5_9A_DISP_M1_LINE_STEP_TOP_H, 0x00);
        SET_PAGED_BYTE(usSelectedPage, P5_9B_DISP_M1_LINE_STEP_TOP_M, 0x00);
        SET_PAGED_BYTE(usSelectedPage, P5_9C_DISP_M1_LINE_STEP_TOP_L, 0x00);
    }
    else
#endif
    {
        SET_PAGED_BIT(usSelectedPage, P5_99_DISP_M1_LINE_STEP_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulLinestep >> 24) & 0x0F));
        SET_PAGED_BYTE(usSelectedPage, P5_9A_DISP_M1_LINE_STEP_TOP_H, ((ulLinestep >> 16) & 0xFF));
        SET_PAGED_BYTE(usSelectedPage, P5_9B_DISP_M1_LINE_STEP_TOP_M, ((ulLinestep >> 8) & 0xFF));
        SET_PAGED_BYTE(usSelectedPage, P5_9C_DISP_M1_LINE_STEP_TOP_L, (ulLinestep & 0xFF));
    }
}

//--------------------------------------------------
// Description  : Set FRC Display Top WaterLev
// Input Value  : usSelectedPage: FRC page, usVerSize
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDispTopWaterLevel(EnumFRCPageSelect enumPageSelect, BYTE ucLen)
{
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        SET_PAGED_BIT(enumPageSelect, P5_A0_DISP_M1_WTLVL_TOP_H, ~(_BIT0), ((511 - ucLen / 2) >> 8));
        SET_PAGED_BYTE(enumPageSelect, P5_A1_DISP_M1_WTLVL_TOP_L, (BYTE)((511 - ucLen / 2) & 0xFF));
    }
    else
#endif
    {
        SET_PAGED_BIT(enumPageSelect, P5_A0_DISP_M1_WTLVL_TOP_H, ~(_BIT0), ((510 - ucLen / 2) >> 8));
        SET_PAGED_BYTE(enumPageSelect, P5_A1_DISP_M1_WTLVL_TOP_L, (BYTE)((510 - ucLen / 2) & 0xFF));
    }
}

//--------------------------------------------------
// Description  : Set FRC Capture linenum
// Input Value  : usSelectedPage: FRC page, usVerSize
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetCapLinenum(EnumFRCPageSelect enumPageSelect, WORD usVerSize)
{
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        // E/O mode: FRCCotnrol->ScalerFRCUpdateFifoScalingSize->vheight=vheight/2
        PDATA_WORD(0) = ((DWORD)(usVerSize * 2) * GET_MEMORY_DATA_BIT() / 128);
        PDATA_WORD(0) += ((((DWORD)(usVerSize * 2) * GET_MEMORY_DATA_BIT() % 128) == 0) ? (0) : (1));
        SET_PAGED_BYTE(enumPageSelect, P5_21_CAP_M1_LINE_NUM_H, HIBYTE(PDATA_WORD(0)));
        SET_PAGED_BYTE(enumPageSelect, P5_22_CAP_M1_LINE_NUM_L, LOBYTE(PDATA_WORD(0)));
    }
    else
#endif
    {
        SET_PAGED_BYTE(enumPageSelect, P5_21_CAP_M1_LINE_NUM_H, HIBYTE(usVerSize));
        SET_PAGED_BYTE(enumPageSelect, P5_22_CAP_M1_LINE_NUM_L, LOBYTE(usVerSize));
    }
}

//--------------------------------------------------
// Description  : Set FRC Capture linestep
// Input Value  : usSelectedPage: FRC page, ulLinestep
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetCapLinestep(EnumFRCPageSelect enumPageSelect, DWORD ulLineStep)
{
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        SET_PAGED_BIT(enumPageSelect, P5_19_CAP_M1_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        SET_PAGED_BYTE(enumPageSelect, P5_1A_CAP_M1_LINE_STEP_H, 0x00);
        SET_PAGED_BYTE(enumPageSelect, P5_1B_CAP_M1_LINE_STEP_M, 0x00);
        SET_PAGED_BYTE(enumPageSelect, P5_1C_CAP_M1_LINE_STEP_L, 0x00);
    }
    else
#endif
    {
        SET_PAGED_BIT(enumPageSelect, P5_19_CAP_M1_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((BYTE)(ulLineStep >> 24) & 0x0F));
        SET_PAGED_BYTE(enumPageSelect, P5_1A_CAP_M1_LINE_STEP_H, (BYTE)(ulLineStep >> 16));
        SET_PAGED_BYTE(enumPageSelect, P5_1B_CAP_M1_LINE_STEP_M, (BYTE)(ulLineStep >> 8));
        SET_PAGED_BYTE(enumPageSelect, P5_1C_CAP_M1_LINE_STEP_L, (BYTE)(ulLineStep >> 0));
    }
}

//--------------------------------------------------
// Description  : Get FRC Capture linestep
// Input Value  : usSelectedPage: FRC page
// Output Value : address
//--------------------------------------------------
DWORD ScalerFRCGetCapLinestep(WORD usSelectedPage)
{
    PDATA_DWORD(0) = (((DWORD)GET_PAGED_BIT(usSelectedPage, P5_19_CAP_M1_LINE_STEP_MSB, 0x0F) << 24) |
                      ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_1A_CAP_M1_LINE_STEP_H) << 16) |
                      ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_1B_CAP_M1_LINE_STEP_M) << 8) |
                      ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_1C_CAP_M1_LINE_STEP_L)));
    return PDATA_DWORD(0);
}

//--------------------------------------------------
// Description  : Get FRC line total pixel from register
// Input Value  : usSelectedPage: FRC page
// Output Value : line total pixel
//--------------------------------------------------
WORD ScalerFRCGetDispTopLineTotalPixel(WORD usSelectedPage)
{
    WORD usNum = (((WORD)GET_PAGED_BYTE(usSelectedPage, P5_A8_DISP_M1_READ_NUM_TOP_H) << 8) | ((DWORD)GET_PAGED_BYTE(usSelectedPage, P5_A9_DISP_M1_READ_NUM_TOP_L)));
    BYTE ucLen = GET_PAGED_BYTE(usSelectedPage, P5_AA_DISP_M1_READ_TOP_LEN);
    BYTE ucRem = GET_PAGED_BYTE(usSelectedPage, P5_AB_DISP_M1_READ_REMAIN_TOP);

    return (usNum * (WORD)ucLen + ucRem);
}

//--------------------------------------------------
// Description  : Adjust IVS2DVS Delay for Aspect Ratio Function
// Input Value  : usFRCVerSize : FRC Veritcal Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCAdjustIVS2DVSDelay(void)
{
    DWORD ulIVStoDVSPixels = 0;
    WORD usIVS2DVSDelay = 0;
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
    WORD usVstbk = GET_MDOMAIN_OUTPUT_VSTART();
    WORD usVHeightbk = GET_MDOMAIN_OUTPUT_VHEIGHT();
    WORD usVBHeightbk = GET_MDOMAIN_OUTPUT_VBHEIGHT();
#endif
    bit bCalculateIVS2DVS = GET_FORCE_DISPLAY_1P_MODE();
    EnumMemoryConfig enumMemoryConfig = GET_MEMORY_CONFIG_SELECT();

#if(_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
    if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
        bCalculateIVS2DVS = _TRUE;
        enumMemoryConfig = _FRAME_SYNC_MEMORY;
    }
#endif

    if(bCalculateIVS2DVS == _TRUE)
    {
        BYTE ucMargin = ScalerFRCIVS2DVSDelayMargin();
        WORD usPreReadLine = ScalerFRCSetDiffPreReadByPath(_FRC_MAIN1_PAGE);

        DWORD ulIHFreq = 0;
        DWORD ulDHFreq = 0;

        EnumFRCIDDenCompare enumFRCDenTime = _FRC_I_DEN_EAQUAL_D_DEN;
        WORD usInputVHeight = GET_MDOMAIN_INPUT_VHEIGHT();

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_SUPPORT == _ON))
        if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
           (enumMemoryConfig == _FRAME_SYNC_MEMORY))
        {
            switch(GET_ROT_TYPE())
            {
                case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
                case _ROT_VER_MIRROR:
#endif
                    // I_M2_DEN_stop should be finish before D_M1_preread
                    usInputVHeight = GET_MDOMAIN_INPUT_VHEIGHT() + 1;
                    break;

                default:
                    break;
            }
        }
#endif

        ulIHFreq = ScalerMeasureGetHFreq(GET_MDOMAIN_INPUT_DATA_PATH());
        DebugMessageFRC("FRC IHF 0.01k", ulIHFreq);

        // DHFreq, unit: 0.01kHz
        ulDHFreq = GET_DWORD_MUL_DIV(GET_D_CLK_FREQ(), 100, GET_MDOMAIN_OUTPUT_HTOTAL());

        enumFRCDenTime = ScalerFRCCompareDenTime(usInputVHeight);

        switch(enumMemoryConfig)
        {
            case _FRAME_SYNC_MEMORY:

                // IVS2DVS line skip disable
                ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT3, _BIT3);

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
                ScalerFRCSetAspectRatioDDomain();
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
                if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
#else
                if(GET_ROT_TYPE() == _ROT_CW180)
#endif
                {
                    // Consider IDEN period and (DDEN + pre-read) period
                    if((enumFRCDenTime == _FRC_I_DEN_EAQUAL_D_DEN) || (enumFRCDenTime == _FRC_I_DEN_LARGE_D_DEN))
                    {
                        // Roundup: (IVS2DVS_delay_min + IVS2DVS_delay_max) / 2
                        usIVS2DVSDelay = ((GET_MDOMAIN_INPUT_VSTART() + usInputVHeight) + GET_MDOMAIN_INPUT_VTOTAL());
                        usIVS2DVSDelay = (usIVS2DVSDelay >> 1) + (usIVS2DVSDelay % 2);
                    }
                    else
                    {
                        // IVS2DVS delay max
                        usIVS2DVSDelay = GET_MDOMAIN_INPUT_VTOTAL() + GET_MDOMAIN_INPUT_VSTART() + usInputVHeight -
                                         (GET_DWORD_MUL_DIV((GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()), ulIHFreq, ulDHFreq)) - 1;

                        if(usIVS2DVSDelay > GET_MDOMAIN_INPUT_VTOTAL())
                        {
                            usIVS2DVSDelay = GET_MDOMAIN_INPUT_VTOTAL();
                        }

                        // Rounddown (IVS2DVS_delay_min + IVS2DVS_delay_max) / 2
                        usIVS2DVSDelay = (((GET_MDOMAIN_INPUT_VSTART() + usInputVHeight) + usIVS2DVSDelay) / 2);
                    }

                    usIVS2DVSDelay -= GET_DWORD_MUL_DIV(usPreReadLine, ulIHFreq, ulDHFreq);
                    DebugMessageFRC("Rotation: usIVS2DVSDelay", usIVS2DVSDelay);
                }
                else
#endif
                {
                    WORD usIPeriod = 0;
                    WORD usDPeriod = 0;

                    // Consider IDEN period and (DDEN + pre-read) period
                    if((enumFRCDenTime == _FRC_I_DEN_EAQUAL_D_DEN) || (enumFRCDenTime == _FRC_I_DEN_LARGE_D_DEN))
                    {
                        // (IVStart + IDEN) Period
                        usIPeriod = (GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VHEIGHT());

                        // (DVStart + DDEN) Period
                        usDPeriod = GET_DWORD_MUL_DIV((GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()), ulIHFreq, ulDHFreq);
                    }
                    else
                    {
                        // IVStart Period
                        usIPeriod = GET_MDOMAIN_INPUT_VSTART();

                        // FRC_Display pre-read Period
                        usDPeriod = GET_DWORD_MUL_DIV(usPreReadLine, ulIHFreq, ulDHFreq);
                    }

#if (_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
                    if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
                    {
                        usIPeriod += ScalerVgipGetCaptureVDelay();
                    }
#endif
                    if(usIPeriod > usDPeriod)
                    {
                        usIVS2DVSDelay = usIPeriod - usDPeriod + ucMargin;
                    }
                    else
                    {
                        usIVS2DVSDelay = ucMargin;
                    }

                    PDATA_WORD(1) = ((GET_MDOMAIN_INPUT_VSTART() + ucMargin) > (GET_DWORD_MUL_DIV(usPreReadLine, ulIHFreq, ulDHFreq))) ? ((GET_MDOMAIN_INPUT_VSTART() + ucMargin) - (GET_DWORD_MUL_DIV(usPreReadLine, ulIHFreq, ulDHFreq))) : 0;

                    if(PDATA_WORD(1) > usIVS2DVSDelay)
                    {
                        usIVS2DVSDelay = PDATA_WORD(1);
                    }

#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_HDMI21_ALLM_SUPPORT == _ON))
                    WORD usDelayMax = ScalerFRCGetIVS2DVSDelayMax();
#if(_HDMI21_ALLM_SUPPORT == _ON)
                    SET_FRC_ALLM_INPUT_PORT(GET_MDOMAIN_INPUT_PORT());
                    SET_FRC_ALLM_DELAY_MAX(usDelayMax);
                    SET_FRC_ALLM_DELAY_MIN(usIVS2DVSDelay);
#endif
                    usIVS2DVSDelay = ScalerFRCLatencyControl(GET_MDOMAIN_INPUT_PORT(), GET_MDOMAIN_SOURCE_TYPE(), usDelayMax, usIVS2DVSDelay);
#endif
                    // ivs2dvsdelay must be smaller than IVTotal when frame sync
                    if(usIVS2DVSDelay >= GET_MDOMAIN_INPUT_VTOTAL())
                    {
                        usIVS2DVSDelay = GET_MDOMAIN_INPUT_VTOTAL() - 1;
                    }
                }

                break;

            case _FREE_RUN_MEMORY:

                usIVS2DVSDelay = (GET_MDOMAIN_INPUT_VTOTAL() + GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VHEIGHT());
                usIVS2DVSDelay -= (GET_DWORD_MUL_DIV((GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()), ulIHFreq, ulDHFreq));

                if(usIVS2DVSDelay > 255)
                {
                    usIVS2DVSDelay = 0xFE - 32;
                }
                else
                {
                    usIVS2DVSDelay -= 32;
                }

                break;

            default:
            case _MN_FRAME_SYNC_MEMORY:

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
                switch(GET_MEMORY_DVF_SELECT())
                {
                    case _6_5_IVF:
                    case _5_4_IVF:

                        usIVS2DVSDelay = GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VHEIGHT() - (GET_DWORD_MUL_DIV(usPreReadLine, ulIHFreq, ulDHFreq)) + 1;

                        break;

                    case _2_5_IVF:

                        // lower bound : dvtotal+dvstart+dvheight+ivs2dvsdelay > ivstart + ivheight
                        usIVS2DVSDelay = GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VHEIGHT();
                        usIVS2DVSDelay -= (GET_DWORD_MUL_DIV((GET_MDOMAIN_OUTPUT_VTOTAL() + GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()), ulIHFreq, ulDHFreq));

                        // upper bound : 3 * dvtotal+dvstart+ivs2dvsdelay < IVtotal + ivstart + ivheight/2
                        PDATA_WORD(1) = GET_MDOMAIN_INPUT_VTOTAL() + GET_MDOMAIN_INPUT_VSTART() + (GET_MDOMAIN_INPUT_VHEIGHT() / 2);
                        PDATA_WORD(1) -= (GET_DWORD_MUL_DIV(((GET_MDOMAIN_OUTPUT_VTOTAL() * 3) + GET_MDOMAIN_OUTPUT_VSTART()), ulIHFreq, ulDHFreq));

                        usIVS2DVSDelay = (usIVS2DVSDelay + PDATA_WORD(1)) / 2;

                        break;

                    default:

                        usIVS2DVSDelay = 0x01;
                        break;
                }
#else
                usIVS2DVSDelay = 0x01;
#endif


                break;
        }

        if((usIVS2DVSDelay > 0xF00) || (usIVS2DVSDelay == 0))
        {
            usIVS2DVSDelay = 0x01;
        }
    }
    else
    {
        // Multi-P ??
        usIVS2DVSDelay = 0x01;
    }

#if(_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        SET_MDOMAIN_IVS2DVSDELAY(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()), usIVS2DVSDelay);
    }
#endif

#if (_2P_FRAME_SYNC_SUPPORT == _ON)

    if(ScalerFRC2PFrameSyncBypassNonFrameSyncRegion() == _TRUE)
    {
        return;
    }
#endif

    // Disable Frame Sync Fine Tune
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);

    ulIVStoDVSPixels = ((DWORD)usIVS2DVSDelay * GET_MDOMAIN_INPUT_HTOTAL());

    if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY)
    {
        if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
        {
            // Convert DVline limit to IVline
            WORD usIVS2DVSChgLimit = ((DWORD)_PANEL_DV_LINE_CHG_LIMIT * GET_MDOMAIN_OUTPUT_HTOTAL() / GET_D_CLK_FREQ() * GET_MDOMAIN_INPUT_HFREQ() / 10) +
                                     ((DWORD)_PANEL_DV_LINE_CHG_LIMIT * GET_MDOMAIN_OUTPUT_HTOTAL() % GET_D_CLK_FREQ() * GET_MDOMAIN_INPUT_HFREQ() / 10 / GET_D_CLK_FREQ());

            // Get Old IVS2DVS + IVSdelay (I line)
            PDATA_WORD(0) = (ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData) / GET_MDOMAIN_INPUT_HTOTAL());

            ScalerMemoryFineTuneIVS2DVSDelay(PDATA_WORD(0), usIVS2DVSDelay, usIVS2DVSChgLimit);
        }

        ScalerMemorySetIVS2DVSDelayPixel(ulIVStoDVSPixels, &g_stMDomainInputData);
    }
    else
    {
        ScalerMemorySetIVS2DVSLineDelay(usIVS2DVSDelay, GET_MDOMAIN_INPUT_DATA_PATH());

        // Set Frame Sync Mode Delay Fine Tune = 0
        SET_IVS2DVS_DELAY_16ICLK1(0x0000);
        SET_IVS2DVS_DELAY_16ICLK2(0x0000);
    }

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
    SET_MDOMAIN_OUTPUT_VSTART(usVstbk);
    SET_MDOMAIN_OUTPUT_VHEIGHT(usVHeightbk);
    SET_MDOMAIN_OUTPUT_VBHEIGHT(usVBHeightbk);
#endif
}

//--------------------------------------------------
// Description  : Frame Sync Mode IVS2DVS When Active State
// Input Value  : usIVS2DVSDelay / StructTimingInfo/ StructDisplayInfo
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetFSIVS2DVSDelayWhenActiveState(WORD usIVS2DVSDelay, const StructTimingInfo *pstMdomainInputInfo, const StructDisplayInfo *pstMdomainOutputInfo)
{
    StructIVS2DVSDelayFineTune stFineTune;
    usIVS2DVSDelay = usIVS2DVSDelay;

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_WATCH_DOG)
    bit bDvsWDBackup = ScalerGlobalGetDvsTimeoutWatchDogEnable();
    ScalerGlobalSetDvsTimeoutWatchDog(_DISABLE);
#endif

    // ivs2dvsdelay must be smaller than IVTotal when frame sync
    if(usIVS2DVSDelay >= pstMdomainInputInfo->usVTotal)
    {
        usIVS2DVSDelay = pstMdomainInputInfo->usVTotal - 1;
    }

    if((usIVS2DVSDelay > 0xF00) || (usIVS2DVSDelay == 0))
    {
        usIVS2DVSDelay = 0x01;
    }

    // Convert DVline limit to IVline
    stFineTune.usIVS2DVSChgLimit = ((DWORD)_PANEL_DV_LINE_CHG_LIMIT * pstMdomainOutputInfo->usHTotal / GET_D_CLK_FREQ() * pstMdomainInputInfo->usHFreq / 10) +
                                   ((DWORD)_PANEL_DV_LINE_CHG_LIMIT * pstMdomainOutputInfo->usHTotal % GET_D_CLK_FREQ() * pstMdomainInputInfo->usHFreq / 10 / GET_D_CLK_FREQ());

    // Get Old IVS2DVS + IVSdelay (I line)
    stFineTune.usOldIVS2DVSDelay = (ScalerMemoryGetIVS2DVSDelayPixel(pstMdomainInputInfo) / pstMdomainInputInfo->usHTotal);
    stFineTune.usNewIVS2DVSDelay = usIVS2DVSDelay;

    ScalerMemoryFineTuneIVS2DVSDelayWhenActiveState(&stFineTune, pstMdomainInputInfo, pstMdomainOutputInfo);

    ScalerMemorySetIVS2DVSDelayPixel(((DWORD)usIVS2DVSDelay * pstMdomainInputInfo->usHTotal), pstMdomainInputInfo);

    ScalerGlobalIDomainDBApply(pstMdomainInputInfo->enumInputDataPath, _DB_APPLY_POLLING);

    // Avoid Display Vsync Timeout Flag
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    // Clear Display Vsync Timeout Flag
    ScalerGlobalClrDvsTimeoutFlag();

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_WATCH_DOG)
    if(bDvsWDBackup == _ENABLE)
    {
        ScalerGlobalSetDvsTimeoutWatchDog(bDvsWDBackup);
    }
#endif
}

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust IVS2DVS Delay for Allm
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerFRCAdjustAllmDelay(EnumInputPort enumInputPort, EnumSourceType enumSourceType)
{
    if((ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE) &&
       (GET_FRC_ALLM_INPUT_PORT() == enumInputPort) &&
       (GET_FRC_ALLM_ON_STATUS() != ScalerTmdsMacRxGetHdmi21AllmStatus(enumInputPort)))
    {
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            WORD usIVS2DVSDelay = ScalerFRCLatencyControl(enumInputPort, enumSourceType, GET_FRC_ALLM_DELAY_MAX(), GET_FRC_ALLM_DELAY_MIN());
            ScalerFRCSetFSIVS2DVSDelayWhenActiveState(usIVS2DVSDelay, &g_stMDomainFSActiveInfo.stMDomainFSActiveInputData, &g_stMDomainFSActiveInfo.stMDomainFSActiveOutputData);
        }
        else
        {
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
            if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
            {
                WORD usIVS2DVSDelay = ScalerFRCLatencyControl(enumInputPort, enumSourceType, GET_FRC_ALLM_DELAY_MAX(), GET_FRC_ALLM_DELAY_MIN());
                ScalerFRCSetFSIVS2DVSDelayWhenActiveState(usIVS2DVSDelay, &g_stMDomainFSActiveInfo.stMDomainFSActiveInputData, &g_stMDomainFSActiveInfo.stMDomainFSActiveOutputData);
            }
#endif
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Compare which one of IHF and DHF is bigger, and see if they are too similar
// Input Value  : ucSettingPath --> Path
//                stFIFOSize    --> FIFO size
// Output Value : output is true when they are too similar
//--------------------------------------------------
void ScalerFRCCompareDenForFRCStyle(void)
{
    EnumFRCStyle enumFRCInputSlow = _FRC_INPUT_SLOWER;
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));
    EnumFRCIDDenCompare enumFRCDenTime = _FRC_I_DEN_EAQUAL_D_DEN;

    // Get Previous FRC Style
    SET_MDOMAIN_FRC_STYLE(GET_MDOMAIN_INPUT_DATA_PATH(), (bit)((GET_PAGED_BIT(enumChannelSel, P46_84_M_DISP_CTRL_2, _BIT0) == _BIT0) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));

    enumFRCDenTime = ScalerFRCCompareDenTime(GET_MDOMAIN_INPUT_VHEIGHT());

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // two buffer rotation must set input slow
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER) && ((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR)))
#else
    if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER) && (GET_ROT_TYPE() == _ROT_CW180))
#endif
    {
        enumFRCInputSlow = _FRC_INPUT_SLOWER;
    }
    else
#endif
    {
        if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY)
        {
            enumFRCInputSlow = _FRC_INPUT_SLOWER;
        }
        else
        {
            // Set FRC Style
            if(enumFRCDenTime == _FRC_I_DEN_EAQUAL_D_DEN) // If IDEN period = DDEN period, compare IVF/ DVF
            {
                if(GET_MDOMAIN_INPUT_VFREQ() < GET_OUTPUT_VFREQ())
                {
                    enumFRCInputSlow = _FRC_INPUT_SLOWER;
                }
                else
                {
                    enumFRCInputSlow = _FRC_INPUT_FASTER;
                }
            }
            else if(enumFRCDenTime == _FRC_I_DEN_LARGE_D_DEN)
            {
                enumFRCInputSlow = _FRC_INPUT_SLOWER;
            }
            else
            {
                enumFRCInputSlow = _FRC_INPUT_FASTER;
            }
        }
    }

    if(ScalerMemoryCheckScreenCoverStatus() == _FALSE)
    {
        if(enumFRCInputSlow != GET_MDOMAIN_FRC_STYLE(GET_MDOMAIN_INPUT_DATA_PATH()))
        {
            ScalerDDomainBackgroundEnable(GET_MDOMAIN_OUTPUT_RGN(), _ENABLE);
        }
    }

    if(enumFRCInputSlow == _FRC_INPUT_SLOWER)
    {
        // Set Input slow Than Display
        SET_PAGED_BIT(enumChannelSel, P46_04_M_CAP_CTRL_2, ~_BIT0, 0x00);
        SET_PAGED_BIT(enumChannelSel, P46_84_M_DISP_CTRL_2, ~_BIT0, 0x00);
    }
    else
    {
        // Set Input Fast Than Display
        SET_PAGED_BIT(enumChannelSel, P46_04_M_CAP_CTRL_2, ~_BIT0, _BIT0);
        SET_PAGED_BIT(enumChannelSel, P46_84_M_DISP_CTRL_2, ~_BIT0, _BIT0);
    }

    SET_MDOMAIN_FRC_STYLE(GET_MDOMAIN_INPUT_DATA_PATH(), enumFRCInputSlow);
    FRC_DISP_LOCAL_DB_APPLY(ScalerFRCDispGetPageSelect(GET_MDOMAIN_INPUT_DATA_PATH()));

    if((GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY) || (GET_MEMORY_CONFIG_SELECT() == _MN_FRAME_SYNC_MEMORY))
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

        // Set Frame sync when FRC
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
    }
    else if(GET_MEMORY_CONFIG_SELECT() == _FREE_RUN_MEMORY)
    {
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
        if(ScalerFRC2PFrameSyncBypassNonFrameSyncRegion() == _TRUE)
        {
            // do nothing
            return;
        }
#endif

        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            ScalerFRCOneFrameCtrl();
        }
        else
        {
            // Set Free Run when FRC
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
        }
    }
}

//-------------------------------------------------
// Description  : Compare which one of IDen and DDen is larger
// Input Value  : None
// Output Value : usDVTotal
//-------------------------------------------------
EnumFRCIDDenCompare ScalerFRCCompareDenTime(WORD usInputVHeight)
{
    WORD usIDenPeriod = 0;
    WORD usDDenPeriod = 0;

    // IDEN Period (unit: us) = IVH / IHF
    usIDenPeriod = GET_DWORD_MUL_DIV(usInputVHeight, 10000, GET_MDOMAIN_INPUT_HFREQ());

    // DDEN Period (unit: us) = (DVH + Pre-read line) / DHF
    usDDenPeriod = GET_DWORD_MUL_DIV((GET_MDOMAIN_OUTPUT_VHEIGHT() + GET_FRC_PRE_READ(_FRC_MAIN1_PAGE)), 10000, ((DWORD)GET_D_CLK_FREQ() * 10 / GET_MDOMAIN_OUTPUT_HTOTAL()));

    if(usIDenPeriod == usDDenPeriod)
    {
        return _FRC_I_DEN_EAQUAL_D_DEN;
    }
    else if(usIDenPeriod > usDDenPeriod)
    {
        return _FRC_I_DEN_LARGE_D_DEN;
    }
    else
    {
        return _FRC_I_DEN_SMALL_D_DEN;
    }
}

//-------------------------------------------------
// Description  : Calculate DVTotal for OneFrame FRC
// Input Value  : None
// Output Value : usDVTotal
//-------------------------------------------------
WORD ScalerFRCSetOneFrameDVTotal(void)
{
    DWORD ulFrameDiff = 0;
    DWORD ulActiveRegionDiff = 0;
    WORD usIHF = 0;
    WORD usDHF = 0;
    WORD usDVTotal = 0;

    if((DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDHF = (DWORD)g_usMDomainDVFreq * _PANEL_DV_TOTAL / 1000;
    }
    else
    {
        usDHF = (DWORD)g_usMDomainDVFreq * (DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * 1066 / 1000 / 1000;
    }

    usIHF = (DWORD)GET_MDOMAIN_INPUT_VFREQ() * GET_MDOMAIN_INPUT_VTOTAL() / 1000;
    ulFrameDiff = (DWORD)1000 * ((DWORD)1000 * GET_MDOMAIN_INPUT_VFREQ() - (DWORD)1000 * g_usMDomainDVFreq) / ((DWORD)GET_MDOMAIN_INPUT_VFREQ() * g_usMDomainDVFreq);
    ulActiveRegionDiff = (DWORD) 1000 * ((DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * usIHF - (DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * usDHF) / ((DWORD)usIHF * usDHF);

    // If((Input frame ahead) < 0.8*(Conflict region)), Then DVT = DVH / ((Input Frame ahead)*0.8 + IVH/IHF) * (1/DVF).
    // Else if(DVH*1.66 < DVT), Then DVT = Panel_DVT.
    // Else DVT = DVH*1.66
    if((ulFrameDiff * 100 / ulActiveRegionDiff) < 125)
    {
        usDVTotal = (DWORD)1000 * GET_MDOMAIN_OUTPUT_VHEIGHT() / ((ulFrameDiff * 100 / 125) + ((DWORD)1000 * GET_MDOMAIN_INPUT_VHEIGHT() / usIHF)) * 1000 / g_usMDomainDVFreq;
    }
    else if((DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDVTotal = _PANEL_DV_TOTAL;
    }
    else
    {
        usDVTotal = (DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * 1066 / 1000;
    }

    if(usDVTotal > _PANEL_DV_TOTAL_MAX)
    {
        usDVTotal = _PANEL_DV_TOTAL_MAX;
    }
    else if(usDVTotal < _PANEL_DV_TOTAL_MIN)
    {
        usDVTotal = _PANEL_DV_TOTAL_MIN;
    }

    return usDVTotal;
}

//-------------------------------------------------
// Description  : Set FRC Display Pre-Read Line
// Input Value  : enumInputDataPath : Input path
//                usPreReadLine : Pre-Read Line
// Output Value : None
//-------------------------------------------------
void ScalerFRCSetPreRead(EnumInputDataPath enumInputPath)
{
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputPath);

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            WORD usPreRead = ScalerFRCSetDiffPreReadByPath(enumPageSelect);
            SET_PAGED_BYTE(enumPageSelect, _REG_FRC_DISP_PRRD_VST_TOP_H, HIBYTE(usPreRead));
            SET_PAGED_BYTE(enumPageSelect, _REG_FRC_DISP_PRRD_VST_TOP_L, LOBYTE(usPreRead));
            FRC_DISP_LOCAL_DB_APPLY(enumPageSelect);
        }
    }
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {        // Wait double buffer
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Set OneFrame FRC
// Input Value  : IHF, DHF
// Output Value : None
//--------------------------------------------------
void ScalerFRCOneFrameCtrl(void)
{
    SWORD shMargin = 0;
    WORD usPreRead = 0;
    WORD usLeadingLine = 0;
    bit bAutoMode = _ENABLE; // 1:auto mode; 0:manual mode
    WORD usLength = GET_MDOMAIN_INPUT_VHEIGHT();
    DWORD ulIHF = 0x00;
    DWORD ulDHF = 0x00;
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));

    shMargin = shMargin;
    bAutoMode = bAutoMode;
    /// 1. Only if meet the following check condition, Write data to Memory:
    /// (1) Input Faster :
    ///      1. When R-FIFO is working check:  (IHP' * Length) > (DHP' * (Remain + Line_Margin)) --> (DHF' * Length) > (IHF' * (Remain + LIne_Margin))
    ///      2. When R-FIFO is idle check:     [W-FIFO starts] before [R-FIFO starts + Margin]
    /// (2) Input Slower :
    ///      1. When R-FIFO is working:  ((IHP' !V DHP') * Length) < (DHP'* (Remain + LIne_Margin)) --> ((DHF' - IHF')* Length) < ((DHF' * (Remain + Line_Margin)))
    ///      2. When R-FIFO is idle: Porch > [(IHP' !V DHP') * Length ] / DHP'
    /// 2. Remain Value:
    /// (1) Input Faster :
    ///    if ( pre_read_trig | (pre_cnt > pre_read_margin) )
    ///       Remain = line_counter
    ///    else
    ///       Remain = 0
    /// (2) Input Slower :
    ///    if ( line_counter < (length-1) )
    ///       Remain = line_counter
    ///    else
    ///       Remain = 0

    if(GET_MDOMAIN_OUTPUT_VHEIGHT() > GET_MDOMAIN_INPUT_VHEIGHT())
    {
        // IHF'
        ulIHF = (DWORD)GET_MDOMAIN_INPUT_HFREQ();
        // DHF'
        ulDHF = GET_MDOMAIN_DHF_IN_IDOMAIN();
    }
    else
    {
        // IHF'
        ulIHF = GET_MDOMAIN_IHF_IN_DDOMAIN();
        // DHF'
        ulDHF = ((DWORD)GET_D_CLK_FREQ() * 10 / GET_MDOMAIN_OUTPUT_HTOTAL());
    }

    // Input Faster Case
    if(ulIHF > ulDHF)
    {
        usPreRead = GET_MDOMAIN_OUTPUT_VSTART() - _PRE_READ_MEMORY;

        // Assume IHF_M = 37.48KHz, if input faster, IHF_M set 38, else set 37.
        ulIHF = (ulIHF % 10) ? (ulIHF / 10 + 1) : (ulIHF / 10);

        /// Set Line Merge
        ///      Auto mode : margin to avoid frame tear, range from -2048 to 2047
        ///      Manual mode : decide whether write data to Memory or not
        shMargin = 0x02;

        // Input faster case : DHF * Length
        ulDHF = ulDHF * usLength / 10;
    }
    else
    {
        // Input Slower Case
        // forbidden lines (conflict region)
        usPreRead = ((DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * ulDHF / ulIHF - GET_MDOMAIN_OUTPUT_VHEIGHT());
        usPreRead = (usPreRead < 10) ? 10 : usPreRead;

        PDATA_WORD(0) = _PANEL_DV_TOTAL_MIN;
        // Input frame leading lines in display (Display Frame Ahead)(uint: display line)
        if(GET_MDOMAIN_INPUT_VFREQ() > _PANEL_MAX_FRAME_RATE)
        {
            usLeadingLine = (DWORD)(GET_MDOMAIN_INPUT_VFREQ() - g_usMDomainDVFreq) * PDATA_WORD(0) / GET_MDOMAIN_INPUT_VFREQ();
        }
        else if(GET_MDOMAIN_INPUT_VFREQ() < _PANEL_MIN_FRAME_RATE)
        {
            usLeadingLine = (DWORD)(g_usMDomainDVFreq - GET_MDOMAIN_INPUT_VFREQ()) * PDATA_WORD(0) / GET_MDOMAIN_INPUT_VFREQ();
        }

        if(usPreRead <= GET_MDOMAIN_OUTPUT_VSTART())
        {
            /// 1. Set OneFrameFRC control by Manual mode
            ///  --> Write data control by Manual mode:
            ///  * Only if meet the following check condition, Write data to Memory:
            ///      (1)Input Faster: Remain + Line-margin(CRE8, CRE9) < 0.
            ///      (2)Input Slower: Remain + Line-mergin(CRE8, CRE9) > 0.
            /// 2. Set Input Faster mode

            if((usPreRead * 15 / 10) < usLeadingLine)
            {
                if((usPreRead * 15 / 10) > GET_MDOMAIN_OUTPUT_VSTART())
                {
                    usPreRead = 0; // PRRD_Margin
                }
                else
                {
                    usPreRead = GET_MDOMAIN_OUTPUT_VSTART() - usPreRead * 15 / 10;
                }
            }
            else if((usPreRead * 13 / 10) < usLeadingLine)
            {
                if((usLeadingLine - 1) > GET_MDOMAIN_OUTPUT_VSTART())
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = GET_MDOMAIN_OUTPUT_VSTART() - (usLeadingLine - 1);
                }
            }
            else
            {
                if((usPreRead * 13 / 10) > GET_MDOMAIN_OUTPUT_VSTART())
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = GET_MDOMAIN_OUTPUT_VSTART() - usPreRead * 13 / 10;
                }
            }

            ulIHF = (GET_MDOMAIN_INPUT_HFREQ() % 10) ? (GET_MDOMAIN_INPUT_HFREQ() / 10 + 1) : (GET_MDOMAIN_INPUT_HFREQ() / 10);
            shMargin = (SWORD)0 - (GET_MDOMAIN_OUTPUT_VHEIGHT() - 1);

            // Input Slower Case : (DHF - IHF) * Length
            ulDHF = ulDHF * GET_MDOMAIN_INPUT_VHEIGHT() / 10;
            bAutoMode = _DISABLE;

            // Set Input Faster Mode
            SET_PAGED_BIT(enumChannelSel, P46_04_M_CAP_CTRL_2, ~_BIT0, _BIT0);
            SET_PAGED_BIT(enumChannelSel, P46_84_M_DISP_CTRL_2, ~_BIT0, _BIT0);
        }
        else
        {
            usPreRead = (DWORD)(PDATA_WORD(0) - GET_MDOMAIN_OUTPUT_VHEIGHT()) * usLength / GET_MDOMAIN_OUTPUT_VHEIGHT() - 3;
            shMargin = (usPreRead > 20) ? (usPreRead - 20) : 0;

            usPreRead = usLength;

            // Input Slower Case : (DHF - IHF) * Length
            ulDHF = (ulDHF - ulIHF) * usLength / 10;
            ulIHF = (DWORD)ulIHF / 10;

            SET_PAGED_BIT(enumChannelSel, P46_04_M_CAP_CTRL_2, ~_BIT0, 0x00);
            SET_PAGED_BIT(enumChannelSel, P46_84_M_DISP_CTRL_2, ~_BIT0, 0x00);
        }
    }

    // Set FRC M1/M2
    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH()), GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            /*EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            SET_PAGED_BYTE(enumPageSelect, P5_B1_DISP_M1_ONEF_DHF_H, ((ulDHF >> 16) | ((BYTE)bAutoMode << 6) | (_BIT7))); SET_PAGED_BYTE(enumPageSelect, P5_B2_DISP_M1_ONEF_DHF_M, (BYTE)(ulDHF >> 8));
            SET_PAGED_BYTE(enumPageSelect, P5_B3_DISP_M1_ONEF_DHF_L, (BYTE)ulDHF);
            SET_PAGED_BYTE(enumPageSelect, P5_B4_DISP_M1_ONEF_IHF, (BYTE)ulIHF);
            SET_PAGED_BYTE(enumPageSelect, P5_B5_DISP_M1_LINE_MAGN_L, LOBYTE(shMargin));
            SET_PAGED_BYTE(enumPageSelect, P5_B6_DISP_M1_ONEF_MAGN_H, (((HIBYTE(shMargin) << 4) & 0xF0) | (HIBYTE(usPreRead) & 0x0F)));
            SET_PAGED_BYTE(enumPageSelect, P5_B7_DISP_M1_ONEF_MAGN_L, LOBYTE(usPreRead));
            FRC_DISP_LOCAL_DB_APPLY(enumPageSelect);*/
        }
    }

    // Disable Osd Overlay In Case of Garbage
    pData[0] = ScalerGetByte(P80_A0_OVERLAY_CTRL);
    ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT0, 0x00);

    // Set Frame sync
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

    // Set Free Run
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

    // Enable Osd Overlay In Case of Garbage
    ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT0, (pData[0] & _BIT0));
}

//--------------------------------------------------
// Description  : Wait Capture Write Memory Block Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCWaitWriteFrameBufFinish(void)
{
    EnumFRCPageSelect enumPageSelect = ScalerFRCCapGetPageSelect(GET_MDOMAIN_INPUT_DATA_PATH());
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));

    if(GET_MEMORY_WORK_TYPE() == _MEMORY_WORK_MODE)
    {
        // Check Double Frame Buffer
        if(ScalerFRCGetChannelFRCCapBlkNum(enumChannelSel) == _FRC_CH_2_BLK)
        {
            // Get FRC Capture Block Index
            pData[0] = GET_PAGED_BIT(enumPageSelect, P5_2A_CAP_M1_STATUS, (_BIT7 | _BIT6));

            // Wait Write Data
            ScalerTimerPollingFlagProc(50, GET_PAGED_ADDR(enumPageSelect, P5_2A_CAP_M1_STATUS), _BIT6, ((~pData[0]) & _BIT6));
            ScalerTimerPollingFlagProc(50, GET_PAGED_ADDR(enumPageSelect, P5_2A_CAP_M1_STATUS), _BIT6, ((pData[0]) & _BIT6));

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
               ((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)))
#else
            if((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_DISPLAY_MODE() == _DISPLAY_MODE_1P))
#endif
            {
                ScalerTimerPollingFlagProc(50, GET_PAGED_ADDR(enumPageSelect, P5_2A_CAP_M1_STATUS), _BIT6, ((~pData[0]) & _BIT6));
            }
#endif

            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        }
    }
}

//--------------------------------------------------
// Description  : Calculate IVS2DVS delay margin
// Input Value  : N.A.
// Output Value : IVS2DVS delay margin
//--------------------------------------------------
BYTE ScalerFRCIVS2DVSDelayMargin(void)
{
    WORD usIHwidth = GET_MDOMAIN_INPUT_HWIDTH();
    BYTE ucDataBit = GET_MEMORY_DATA_BIT();
    BYTE ucIMCLatency = 0;
    BYTE ucIVS2DVSMargin = 0;
    BYTE ucFRCLatency = 0;

#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
    {
        // FRC frame tear prevent latency + freesync margin
        ucFRCLatency = _FRC_FRAME_TEAR_PREVENT_LINE + _FRC_IVS2DVSDELAY_MARGIN_DRR;
        ucIVS2DVSMargin = _FRC_IVS2DVSDELAY_LINE_BUFFER_MARGIN;
    }
    else
#endif
    {
        // FRC frame tear prevent latency
        ucFRCLatency = _FRC_FRAME_TEAR_PREVENT_LINE;
        ucIVS2DVSMargin = _FRC_IVS2DVSDELAY_MARGIN;
    }

    switch(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()))
    {
        case _INPUT_PATH_2:
            ucFRCLatency = (ucFRCLatency << 1);
            break;

        case _INPUT_PATH_4:
            ucFRCLatency = (ucFRCLatency << 2);
            usIHwidth = GET_MDOMAIN_INPUT_HWIDTH() / 2;
            break;

        default:
            break;
    }

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _ENABLE)
    {
        ucDataBit = GET_IMG_CMP_PARAM_LLB(GET_IMG_CMP_PARAM());
        ucIMCLatency = _IMC_LATENCY;
    }
#endif

    // Margin need to consider Fifo margin, line buffer margin and setting margin
    // Fifo margin: FIFO size/ format/ IHwidth * 2
    ucIVS2DVSMargin += (((DWORD)_M_DOMAMAIN_FIFO_BIT / ucDataBit / usIHwidth) + 1);

    ucIVS2DVSMargin += (ucIMCLatency + ucFRCLatency);

    return ucIVS2DVSMargin;
}

//--------------------------------------------------
// Description  : FRC 4P/ 3P Skew/ PBP_TB, Botten Display Need to Sync Top Display
// Input Value  : none
// Output Value : Input Data Path Sync of Top/ Botten Display
//--------------------------------------------------
EnumInputDataPath ScalerFRCDispSynchronizeCheck(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

    switch(GET_DISPLAY_MODE())
    {
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:

            switch(enumInputDataPath)
            {
                case _INPUT_PATH_M1:
                    return _INPUT_PATH_M2;

                case _INPUT_PATH_M2:
                    return _INPUT_PATH_M1;

                case _INPUT_PATH_S1:
                    return _INPUT_PATH_S2;

                case _INPUT_PATH_S2:
                    return _INPUT_PATH_S1;

                default:
                    return _INPUT_PATH_NONE;
            }
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:

            switch(enumInputDataPath)
            {
                case _INPUT_PATH_S1_S2:
                    return _INPUT_PATH_S3_S4;

                case _INPUT_PATH_S3_S4:
                    return _INPUT_PATH_S1_S2;

                default:
                    return _INPUT_PATH_NONE;
            }
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            switch(enumInputDataPath)
            {
                case _INPUT_PATH_M1_M2:
#if(_COLOR_IP_3DDI == _ON)
                    return ((GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) ? _INPUT_PATH_S2 : _INPUT_PATH_S1_S2);
#else
                    return _INPUT_PATH_S1_S2;
#endif

                case _INPUT_PATH_S1_S2:
                case _INPUT_PATH_S2:
                    return _INPUT_PATH_M1_M2;

                default:
                    return _INPUT_PATH_NONE;
            }
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_3P_SKEW_B:

            switch(enumInputDataPath)
            {
                case _INPUT_PATH_M1_M2:
                    return _INPUT_PATH_S1_S2;

                case _INPUT_PATH_S1_S2:
                    return _INPUT_PATH_M1_M2;

                default:
                    return _INPUT_PATH_NONE;
            }
#endif
        default:
            return _INPUT_PATH_NONE;
    }

    return _INPUT_PATH_NONE;
}

//--------------------------------------------------
// Description  : Check if current FRC data path has image compression HW
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerFRCGetImgCmpHWUsability(void)
{
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _OFF)

    return _FALSE;

#else // (_M_DOMAIN_IMG_CMP_SUPPORT == _ON)

    // Check if involved FRC data path is equipped with corresponding HW.
    if(CHK_EQUIP_IMG_CMP_DECMP(GET_MDOMAIN_INPUT_DATA_PATH(), ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH())) == _FALSE)
    {
        return _FALSE;
    }

    // IMGCMP GEN1 does not support rotation
#if((_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1) && (_DISPLAY_ROTATION_SUPPORT == _ON))
    if(GET_ROT_TYPE() != _ROT_DISABLE)
    {
        return _FALSE;
    }
#endif
    return _TRUE;
#endif
}

//--------------------------------------------------
// Description  : Check if run-time config is supported by image compression
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerFRCGetImgCmpRunTimeUsability(WORD usWidth, WORD usHeight)
{
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _OFF)
    usWidth = usWidth;
    usHeight = usHeight;

    return _FALSE;

#else // (_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    WORD usHPorch = 0x0000;
    WORD usHPorchLimit = 0x0000;
    DWORD ulTotalPixel = 0x00000000;

    // Check if rotation is enable
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
    if((GET_ROT_TYPE() != _ROT_DISABLE))
    {
        return _FALSE;
    }
#endif
#endif

    usHPorch = GET_MDOMAIN_INPUT_HTOTAL() - usWidth;
    ulTotalPixel = usWidth * usHeight;

    // F/B mode will halve HPorch
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE) && (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M1_M2_S1_S2))
    {
        usHPorch = usHPorch / 2;
        ulTotalPixel = ulTotalPixel / 2;
    }
#endif

    // EOtoFB will halve HPorch
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        usHPorch = usHPorch / 2;
        ulTotalPixel = ulTotalPixel / 2;
    }
#endif

    usHPorchLimit = (ScalerImgCmpGetMultiSliceEn(GET_MODE_DISPLAY_TARGET_REGION()) == _ENABLE) ? (_HW_M_DOMAIN_IMG_CMP_HPORCH_LIMIT * 2) : (_HW_M_DOMAIN_IMG_CMP_HPORCH_LIMIT);

    // Check input timing HPorch does not exceed HW contraint
    if(usHPorch < usHPorchLimit)
    {
        return _FALSE;
    }

    // Check total pixels > 15000
    if(ulTotalPixel < _IMG_CMP_MIN_PIXEL_NUMBER)
    {
        return _FALSE;
    }

    return _TRUE;

#endif
}

//--------------------------------------------------
// Description  : Get image compression Status
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerFRCGetImgCmpStatus(EnumDisplayRegion enumDisplayRegion)
{
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _OFF)
    enumDisplayRegion = enumDisplayRegion;

    return _DISABLE;

#else // (_M_DOMAIN_IMG_CMP_SUPPORT == _ON)

    bit bImgCmpStatus = _DISABLE;
    BYTE ucIndex = 0x00;
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputDataPath);

    for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
            if(ScalerFRCGetBottomSettingStatusFromPage(enumInputDataPath, enumPageSelect) == _TRUE)
            {
                if(GET_PAGED_BIT(enumPageSelect, P5_FA_DISP_M1_DISP_CTRL3_BOT, _BIT2) == _BIT2)
                {
                    bImgCmpStatus = _ENABLE;
                }
            }
            else
#endif
            {
                if(GET_PAGED_BIT(enumPageSelect, P5_AF_DISP_M1_DISP_CTRL3_TOP, _BIT2) == _BIT2)
                {
                    bImgCmpStatus = _ENABLE;
                }
            }
        }
    }

    return bImgCmpStatus;

#endif
}

//--------------------------------------------------
// Description  : Given granted BW -> get FRC path max line-sum-bit
// Input Value  : Granted BW (unit: 100K)
// Output Value : Max line-sum-bit (unit: bit)
//--------------------------------------------------
DWORD ScalerFRCGetPathMaxLineSumBitByBW(DWORD ulGrantBW, StructMemoryBWUsageParam *pstMemBWParam)
{
    DWORD ulIHFreqComp = pstMemBWParam->ulIHFreq;

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        DWORD ulPixelclk = (DWORD)GET_MDOMAIN_INPUT_HFREQ() * GET_MDOMAIN_INPUT_HTOTAL() / 10;
        DWORD ulGrantBWMargin = 0;

        // Consider normal FRC and Rotation CW90/270 FRC capture BW formula, need to update IHF to get accurate line sum bit
        ulIHFreqComp = GET_DWORD_MUL_DIV(pstMemBWParam->ulIHFreq, _ROTATION_VERTICAL_DDR_INPUT_BITS_MAX_NUM, _ROTATION_VERTICAL_DDR_INPUT_BITS_MARGIN_NUM);

        // BW margin for ScalerRotationCalculateCaptureBW rotation vertical factor will unconditional carry
        ulGrantBWMargin = ulPixelclk / 4 / _MEMORY_BUS_WIDTH / 100;

        if(ulGrantBW >= ulGrantBWMargin)
        {
            ulGrantBW = ulGrantBW - ulGrantBWMargin;
        }
        else
        {
            ulGrantBW = 0;
        }
    }
#endif

    // Max path line_sum_bit (unit: bit)
    PDATA_DWORD(0) = (ulGrantBW * 100000) /
                     (((ulIHFreqComp) + (pstMemBWParam->ulDHFreq) +
                       (pstMemBWParam->ulDHFreq * ((_DCLK_SPREAD_RANGE / _PANEL_DPLL_SSCG_DIV_MODE) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100)) / 10 + 1) *  _MEMORY_BUS_WIDTH;

    PDATA_DWORD(0) /= ((pstMemBWParam->ucFBCoopEn == _TRUE) ? 2 : 1);

    return PDATA_DWORD(0);
}

//--------------------------------------------------
// Description  : Decide PQC/OD/HSD Parameters
// Input Value  : pstRateCtrlInfo
// Output Value : Index of applicable FRC rate ctrl param
//--------------------------------------------------
BYTE ScalerFRCGetMemRateCtrlParamIndex(StructFRCRateCtrlInfo *pstRateCtrlInfo)
{
    BYTE ucIndex = 0;
    BYTE ucCnt = ScalerFRCGettFRCRateCtrlParamCnt();
    DWORD pulMaxPathLineSumBit[_OD_PARAM_LENGTH] = {0};
    bit bFBCoopEn = pstRateCtrlInfo->stMemBWParam.ucFBCoopEn ? _TRUE : _FALSE;
    WORD usPathFifoInputHWidth = pstRateCtrlInfo->usFifoHWidth / (bFBCoopEn ? 2 : 1);

    DebugMessageFRC("==FRC RC START==", 0xFF);

    //-------------------------------------------------
    // Get max path line sum bit in each case
    //-------------------------------------------------
    for(ucIndex = 0; ucIndex < _OD_PARAM_LENGTH; ucIndex++)
    {
        BYTE ucODBit10x = GET_OD_BIT_RATE(tODParam[ucIndex]);
        DWORD ulSpareBwForOD = ScalerMDomainGetCurODReservedBW(ucODBit10x, &(pstRateCtrlInfo->stMemBWParam));

#if(_HW_FRC_LENGTH_TYPE == _FRC_LENGTH_7BIT)
        if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
           (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE) &&
           (ucODBit10x == _OFF) &&
           (pstRateCtrlInfo->stMemBWParam.ulDHFreq >
            pstRateCtrlInfo->stMemBWParam.ulIHFreq * _MEMORY_EFFICIENCY_DROP_HFREQ_RATIO))
        {
            if(pstRateCtrlInfo->ulGrantBW > _MEMORY_TOTAL_BW_DROP)
            {
                pstRateCtrlInfo->ulGrantBW -= _MEMORY_TOTAL_BW_DROP;
            }
            else
            {
                pstRateCtrlInfo->ulGrantBW = 0;
            }
            DebugMessageFRC("FRC Drop BW", _MEMORY_TOTAL_BW_DROP);
        }
#endif

        PDATA_DWORD(0) = (pstRateCtrlInfo->ulGrantBW > ulSpareBwForOD) ? (pstRateCtrlInfo->ulGrantBW - ulSpareBwForOD) : 0;
        DebugMessageFRC("@ OD Bit", ucODBit10x);
        DebugMessageFRC("FRC Granted BW", PDATA_DWORD(0));

        pulMaxPathLineSumBit[ucIndex] = ScalerFRCGetPathMaxLineSumBitByBW(PDATA_DWORD(0), &(pstRateCtrlInfo->stMemBWParam));
        DebugMessageFRC("Path MAX LSB", pulMaxPathLineSumBit[ucIndex]);
    }

    //-------------------------------------------------
    // Check which FRC rate ctrl param is applicable
    //-------------------------------------------------
    for(ucIndex = 0; ucIndex < ucCnt; ucIndex++)
    {
        DWORD ulMaxLineSumBit = pulMaxPathLineSumBit[GET_FRC_RCP_OD_PARAM(ucIndex)];
        WORD usFifoInputHWidth = usPathFifoInputHWidth;
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
        DWORD ulIHFreqComp = pstRateCtrlInfo->stMemBWParam.ulIHFreq;
        WORD usFifoOutputHWidth = usFifoInputHWidth;

        if(ScalerRotationCheckVerticalStatus() == _TRUE)
        {
            ulIHFreqComp = GET_DWORD_MUL_DIV(pstRateCtrlInfo->stMemBWParam.ulIHFreq, _ROTATION_VERTICAL_DDR_INPUT_BITS_MAX_NUM, _ROTATION_VERTICAL_DDR_INPUT_BITS_MARGIN_NUM);
            usFifoOutputHWidth = pstRateCtrlInfo->usFifoVHeight;
        }
#endif

        if(ucIndex < (ucCnt - 1))
        {
            // Skip the rate ctrl param in following conditions:
            // 1. Insufficient line-sum-bit.
            if(ulMaxLineSumBit < _FRC_MIN_LINE_SUM_BIT)
            {
                continue;
            }
            // 2. Adopt ImgCmp, but it is not usable in such path
            if((GET_FRC_RCP_IMG_CMP_EN(ucIndex) == _TRUE) && (pstRateCtrlInfo->ucImgCmpUsable == _FALSE))
            {
                continue;
            }
            // 3. Adopt ImgCmp, but path input width less than minimum requirement
            // 1039 doesn't support 1frame frc & autoblk toggle

#if(_BW_CUSTOME_MODE == _ENABLE)
            if(g_stDisplayCustomizedData.structCustomizedMdomain.enumBWCustomeModeType == _BW_FIX_ORIGINAL_COLOR_DEPTH_TYPE)
            {
                if((GET_FRC_RCP_FIFO_COLOR_DEPTH(ucIndex) * 3) > GET_MEMORY_DATA_BIT())
                {
                    continue;
                }
            }
#endif
        }

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
        if(GET_FRC_RCP_IMG_CMP_EN(ucIndex) == _TRUE)
        {
            // Max line sum bit is trimmed to multiple of 128
            // Steam end dummy(256bit) is also deducted if necessary
            ulMaxLineSumBit = ulMaxLineSumBit - (ulMaxLineSumBit % _IMG_CMP_MEM_RW_UNIT) - _IMG_CMP_STREAM_END_DUMMY_LEN;
        }
#endif

        // HSD disabled cases
        if(GET_FRC_RCP_HSD_EN(ucIndex) == _FALSE)
        {
            DWORD ulFrameSize = 0;
            DWORD ulCompareBlock = (ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()) == ScalerRegionGet2PMainPathRegion()) ? GET_ROW_FOR_MAIN() : GET_ROW_FOR_SUB();
            BYTE ucIPathCount = ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH());

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
            if(GET_FRC_RCP_IMG_CMP_EN(ucIndex) == _TRUE)
            {
                // Path width is multiple of _IMG_CMP_BLK_WIDTH
                usFifoInputHWidth = CEILING(usFifoInputHWidth, _IMG_CMP_BLK_WIDTH);
            }
#endif

            ulFrameSize = ScalerFRCGetLineSumBit(usFifoInputHWidth, GET_FRC_RCP_BPP(ucIndex), GET_FRC_RCP_IMG_CMP_PARAM(ucIndex)) * pstRateCtrlInfo->usFifoVHeight;
            ulFrameSize = CEILING_OF_INT_DIVISION(GET_DEFAULT_FRAME_USE_MEMORY_ROW(ulFrameSize), ucIPathCount);
#if(_COLOR_IP_3DDI == _ON)
            // only for eo mode, s2 3ddi
            if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE) &&
               (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2) && (GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON))
            {
                ulCompareBlock = GET_ROW_FOR_SUB() * 2;
            }
#endif

            if(((ulCompareBlock >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) < ulFrameSize) || ((ulFrameSize * ScalerMemoryGetFrameBufferCount()) > _MEMORY_ROW))
            {
                continue;
            }

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
            if(ScalerRotationCheckVerticalStatus() == _TRUE)
            {
                DWORD ulInputLineSumBitRatio = GET_DWORD_MUL_DIV(((DWORD)usFifoInputHWidth * GET_FRC_RCP_BPP(ucIndex)), ulIHFreqComp, (ulIHFreqComp + pstRateCtrlInfo->stMemBWParam.ulDHFreq));
                DWORD ulOutputLineSumBitRatio = GET_DWORD_MUL_DIV(((DWORD)usFifoOutputHWidth * GET_FRC_RCP_BPP(ucIndex)), pstRateCtrlInfo->stMemBWParam.ulDHFreq, (ulIHFreqComp + pstRateCtrlInfo->stMemBWParam.ulDHFreq));

                if((ulInputLineSumBitRatio + ulOutputLineSumBitRatio) <= ulMaxLineSumBit)
                {
                    break;
                }
            }
            else
#endif
            {
                if(((DWORD)usFifoInputHWidth * GET_FRC_RCP_BPP(ucIndex)) <= ulMaxLineSumBit)
                {
                    break;
                }
            }
        }
        // HSD enabled cases
        else
        {
            DWORD ulhsdblk = (ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()) == ScalerRegionGet2PMainPathRegion()) ? GET_ROW_FOR_MAIN() : GET_ROW_FOR_SUB();
            DWORD ulSpaceMaxLineSumBit = 0;
            DWORD ulHSDTargetHwidth = 0;

            // consider bank shift for address, -2 row for margin
            ulhsdblk = ((ulhsdblk >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) - 2) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM;
            // HSD considering to size
            ulSpaceMaxLineSumBit = (DWORD)(ulhsdblk >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) * ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) *
                                   (DWORD)_FW_MEM_CLIENT_MEMORY_BIT_NUM * _MEMORY_COL_PER_BANK * _MEMORY_BANK / pstRateCtrlInfo->usFifoVHeight;

            DebugMessageFRC("Space MaxLineSumBit", ulSpaceMaxLineSumBit);
            DebugMessageFRC("BW MaxLineSumBit", ulMaxLineSumBit);

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
            if(ScalerRotationCheckVerticalStatus() == _TRUE)
            {
                DWORD ulHSDSpaceHwidth = 0;
                SDWORD lHSDBWHwidth = 0;
                SDWORD lFifoInputHwidthDiff = (SDWORD)usFifoInputHWidth - ((SDWORD)ulMaxLineSumBit / GET_FRC_RCP_BPP(ucIndex));
                SDWORD lFifoOutputHwidthDiff = (SDWORD)GET_DWORD_MUL_DIV((DWORD)usFifoOutputHWidth, pstRateCtrlInfo->stMemBWParam.ulDHFreq, ulIHFreqComp) -
                                               (SDWORD)GET_DWORD_MUL_DIV((ulMaxLineSumBit / GET_FRC_RCP_BPP(ucIndex)), pstRateCtrlInfo->stMemBWParam.ulDHFreq, ulIHFreqComp);

                // Memory BW dominant
                lHSDBWHwidth = (SDWORD)usFifoInputHWidth - (lFifoInputHwidthDiff + lFifoOutputHwidthDiff);

                if(lHSDBWHwidth < 0)
                {
                    DebugMessageFRC("[Warning]!!!!!! No more FIFO Input Hwidth for HSD (CW90/270 Memory BW insufficient)", lHSDBWHwidth);
                    lHSDBWHwidth = 0;
                }

                // Memory Space dominant
                ulHSDSpaceHwidth = ulSpaceMaxLineSumBit / GET_FRC_RCP_BPP(ucIndex);

                ulHSDTargetHwidth = MINOF((DWORD)lHSDBWHwidth, ulHSDSpaceHwidth);
            }
            else
#endif
            {
                // Memory BW dominant or Space dominant
                ulMaxLineSumBit = MINOF(ulMaxLineSumBit, ulSpaceMaxLineSumBit);

                ulHSDTargetHwidth = ulMaxLineSumBit / GET_FRC_RCP_BPP(ucIndex);
            }

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
            // Path HWidth is scale down to multiple of _IMG_CMP_BLK_WIDTH
            if(GET_FRC_RCP_IMG_CMP_EN(ucIndex) == _TRUE)
            {
                ulHSDTargetHwidth -= (ulHSDTargetHwidth % _IMG_CMP_BLK_WIDTH);

                // If extension is necessary, reserve some quota for PQC input padding process
                ulHSDTargetHwidth -= (bFBCoopEn ? _IMG_CMP_BLK_WIDTH : 0);
            }
#endif

            // HWidth need to be multiple of _FRC_UNIT * 4 (complement of linestep)
            ulHSDTargetHwidth *= GET_FRC_RCP_BPP(ucIndex);
            ulHSDTargetHwidth -= (ulHSDTargetHwidth % (_FRC_UNIT * 4));
            ulHSDTargetHwidth /= GET_FRC_RCP_BPP(ucIndex);

            // Let path HWidth be an even number
            ulHSDTargetHwidth -= (((ulHSDTargetHwidth & 0x01) == 0x01) ? 1 : 0);

            // Given granted memory usage & BPP, the max (full frame)HWidth available:
            DebugMessageFRC("4. FRC max SD width", ulHSDTargetHwidth * (bFBCoopEn ? 2 : 1));

            DebugMessageFRC("4. FRC current SD width", pstRateCtrlInfo->usFifoHWidth);

            // Update (full frame)HWidth if scaling is necessary
            if(usFifoInputHWidth > ulHSDTargetHwidth)
            {
                pstRateCtrlInfo->usFifoHWidth = ulHSDTargetHwidth * (bFBCoopEn ? 2 : 1);
            }

            // Result of HSD assessment
            DebugMessageFRC("4.usHSDBW", pstRateCtrlInfo->usFifoHWidth);
            break;
        }
    }

    DebugMessageFRC("==FRC RC END==", ucIndex);
    return ucIndex;
}

//--------------------------------------------------
// Description  : Apply FRC Rate Ctrl Parameter
// Input Value  : Parameter Index
// Output Value : None
//--------------------------------------------------
void ScalerFRCApplyMemRateCtrlParam(BYTE ucRateCtrlParamIndex)
{
    SET_MDOMAIN_FRC_CTRL_PARAM_INDEX(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()), ucRateCtrlParamIndex);

    // Set FIFO bit num
    ScalerMDomainSetMemoryDataBit(GET_FRC_RCP_FIFO_COLOR_DEPTH(ucRateCtrlParamIndex));
    DebugMessageFRC("4. FIFO Color Depth", GET_FRC_RCP_FIFO_COLOR_DEPTH(ucRateCtrlParamIndex));
}

//--------------------------------------------------
// Description  : Set Capture And Display Memory Boundary
// Input Value  : enumFRCBoundary
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetMemoryBoundary(EnumFRCBoundary enumFRCBoundary)
{
    BYTE ucIndex = 0x00;
    DWORD ulUpLimit = 0;
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH());

    if(enumFRCBoundary == _FRC_BOUNDARY_DEFAULT)
    {
        // Set Memory Boundary initial value
        ulUpLimit = 0x0FFFFFFE;
    }
    else
    {
#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
        // Set M:N auto block toggle
        if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
        {
            ulUpLimit = 0x0FFFFFFE;
        }
        else
#endif
        {
            // Set Up limit , Rotation start from _MEMORY_BOTTOM_ADDRESS, so up limit = _MEMORY_BOTTOM_ADDRESS + 1
            ulUpLimit = _MEMORY_BOTTOM_ADDRESS;
        }
    }

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            // Set Up limit , Rotation start from _MEMORY_BOTTOM_ADDRESS, so up limit = _MEMORY_BOTTOM_ADDRESS + 1
            SET_PAGED_BIT(enumPageSelect, P5_10_CAP_M1_BOUNDARY_ADDR2_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulUpLimit >> 24) & 0x0F));
            SET_PAGED_BYTE(enumPageSelect, P5_11_CAP_M1_BOUNDARY_ADDR2_H, ((ulUpLimit >> 16) & 0xFF));
            SET_PAGED_BYTE(enumPageSelect, P5_12_CAP_M1_BOUNDARY_ADDR2_M, ((ulUpLimit >> 8) & 0xFF));
            SET_PAGED_BYTE(enumPageSelect, P5_13_CAP_M1_BOUNDARY_ADDR2_L, (ulUpLimit & 0xFE));
        }
    }

    for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            // Set Up limit , Rotation start from _MEMORY_BOTTOM_ADDRESS, so up limit = _MEMORY_BOTTOM_ADDRESS + 1
            SET_PAGED_BIT(enumPageSelect, P5_90_DISP_M1_BOUNDARY_ADDR2_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulUpLimit >> 24) & 0x0F));
            SET_PAGED_BYTE(enumPageSelect, P5_91_DISP_M1_BOUNDARY_ADDR2_H, ((ulUpLimit >> 16) & 0xFF));
            SET_PAGED_BYTE(enumPageSelect, P5_92_DISP_M1_BOUNDARY_ADDR2_M, ((ulUpLimit >> 8) & 0xFF));
            SET_PAGED_BYTE(enumPageSelect, P5_93_DISP_M1_BOUNDARY_ADDR2_L, (ulUpLimit & 0xFE));
        }
    }

    if((enumFRCBoundary == _FRC_BOUNDARY_NORMAL) && (ScalerGlobalGetDDomainDBStatus() == _ENABLE))
    {
        ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()), _DB_APPLY_POLLING);
    }
    else
    {
        // Enable FRC Display double buffer
        for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
            {
                FRC_DISP_LOCAL_DB_APPLY(enumPageSelect);
            }
        }

        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }
}

#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_HDMI21_ALLM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get IVS2DVSDelay Max Value in Frame Sync Mode
// Input Value  : usFRCVerSize : Input VHeight
// Output Value : IVS2DVSDelay Max Value
//--------------------------------------------------
WORD ScalerFRCGetIVS2DVSDelayMax(void)
{
    WORD usDHF = 0x00;
    WORD usIPeriod = 0x00;
    WORD usDStartPeriod = 0x00;

    if(ScalerMDomainMemorySelectConfirm() == _FRAME_SYNC_MEMORY)
    {
        // DHFreq
        usDHF = ((DWORD)GET_D_CLK_FREQ() * 10 / GET_MDOMAIN_OUTPUT_HTOTAL());

        // (IVStart + IDEN) Period
        usIPeriod = (GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VHEIGHT());

        // Pre-read Period
        usDStartPeriod = ((DWORD)ScalerFRCSetDiffPreReadByPath(_FRC_MAIN1_PAGE) * GET_MDOMAIN_INPUT_HFREQ() / usDHF);

        return (usIPeriod - (usDStartPeriod + _FRC_IVS2DVSDELAY_MARGIN));
    }

    return 0;
}
#endif // End of #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
//--------------------------------------------------
// Description  : Set Dvst, Dvheight when aspect ratio wothout mute
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetAspectRatioDDomain(void)
{
    WORD usAspNewDVst = 0;
    if(GET_ASPECT_RATIO_MIN_DVH() != 0)
    {
        if(GET_MDOMAIN_OUTPUT_VHEIGHT() > GET_ASPECT_RATIO_MIN_DVH())
        {
            usAspNewDVst = GET_MDOMAIN_OUTPUT_VHEIGHT() - GET_ASPECT_RATIO_MIN_DVH();
            usAspNewDVst &= 0xFFFC;
            usAspNewDVst = GET_MDOMAIN_OUTPUT_VSTART() + (usAspNewDVst / 2);
        }
        else
        {
            usAspNewDVst = GET_ASPECT_RATIO_MIN_DVH() - GET_MDOMAIN_OUTPUT_VHEIGHT();
            usAspNewDVst &= 0xFFFC;
            usAspNewDVst = GET_MDOMAIN_OUTPUT_VSTART() - (usAspNewDVst / 2);
        }

        SET_MDOMAIN_OUTPUT_VSTART(usAspNewDVst);
        SET_MDOMAIN_OUTPUT_VHEIGHT(GET_ASPECT_RATIO_MIN_DVH());
        SET_MDOMAIN_OUTPUT_VBHEIGHT(GET_ASPECT_RATIO_MIN_DVH());
    }
}
#endif // End of #if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)

#if((_FREEZE_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
//--------------------------------------------------
// Description  : FRC fix block select of slow side
// Input Value  : ON --> Freeze
// Output Value : None
//--------------------------------------------------
void ScalerFRCFixSlowSideBlkSel(EnumInputDataPath enumInputPath, bit bEn)
{
    EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(enumInputPath));

    // use freeze mode to fix blk_sel of slow side; display freeze for input fast, capture freeze for input slow
    if(GET_PAGED_BIT(enumChannelSel, P46_04_M_CAP_CTRL_2, _BIT0) == _BIT0) // input fast
    {
        if(bEn == _ON)
        {
            SET_PAGED_BIT(enumChannelSel, P46_82_M_DISP_BLOCK_SEL, ~(_BIT4), _BIT4);
        }
        else
        {
            SET_PAGED_BIT(enumChannelSel, P46_82_M_DISP_BLOCK_SEL, ~(_BIT4), 0x00);
        }
    }
    else // input slow
    {
        if(bEn == _ON)
        {
            SET_PAGED_BIT(enumChannelSel, P46_03_M_CAP_BLOCK_SEL, ~(_BIT4), _BIT4);
        }
        else
        {
            SET_PAGED_BIT(enumChannelSel, P46_03_M_CAP_BLOCK_SEL, ~(_BIT4), 0x00);
        }
    }
}
#endif // End of #if(_FREEZE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set FRC Address Index
// Input Value  : FRC Page
// Output Value : FRC address index
//--------------------------------------------------
EnumFRCIndex ScalerFRCCalculateAddressMapping(EnumFRCPageSelect enumPageSelect)
{
    switch(enumPageSelect)
    {
        case _FRC_MAIN1_PAGE:
        default:
            return _FRC_INDEX_0;

        case _FRC_MAIN2_PAGE:
            return _FRC_INDEX_1;

        case _FRC_SUB1_PAGE:
#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
            return _FRC_INDEX_2;
#else
            return _FRC_INDEX_1;
#endif

#if(_HW_I_DOMAIN_PATH_COUNT > 3)
        case _FRC_SUB2_PAGE:
#if(_COLOR_IP_3DDI == _ON)
            // only for eo mode, s2 3ddi
            if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE) &&
               (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2) && (GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON))
            {
                return _FRC_INDEX_2;
            }
            else
#endif
            {
                return _FRC_INDEX_3;
            }

        case _FRC_SUB3_PAGE:
            return ((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_EQUAL) ? _FRC_INDEX_2 : _FRC_INDEX_4);

        case _FRC_SUB4_PAGE:
            return ((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_EQUAL) ? _FRC_INDEX_3 : _FRC_INDEX_5);
#endif
    }
}

//--------------------------------------------------
// Description  : Calculate FRC Address
// Input Value  : FRC Page
// Output Value : None
//--------------------------------------------------
void ScalerFRCCalculateAddress(EnumFRCPageSelect enumPageSelect, WORD usOffset)
{
    DWORD ulBlkSpace = GET_ROW_FOR_MAIN();
    DWORD ulAddress1 = 0;
    DWORD ulAddress2 = 0;
    DWORD ulAddress3 = 0;
    EnumFRCIndex enumFRCIndex = ScalerFRCCalculateAddressMapping(enumPageSelect);
    DWORD ulBase = ScalerFRCGetBaseAddress(enumFRCIndex);

    switch(GET_RGN_MAX_DISPLAY_REGION())
    {
#if(_3P_DISPLAY_SUPPORT == _ON)
        case 0x03:
            if(enumFRCIndex >= _FRC_INDEX_2)
            {
                ulBlkSpace = GET_ROW_FOR_SUB();
            }

            break;
#endif
#if(_2P_DISPLAY_SUPPORT == _ON)
        case 0x02:
            if(ScalerRegion2PRegionEqual(GET_DISPLAY_MODE()) == _FALSE)
            {
#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
                if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE) && (enumFRCIndex >= _FRC_INDEX_2))
                {
                    ulBlkSpace = GET_ROW_FOR_SUB();
                }
#if(_HW_I_DOMAIN_PATH_COUNT > 3)
                else if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) && (enumFRCIndex >= _FRC_INDEX_4))
                {
                    ulBlkSpace = GET_ROW_FOR_SUB();
                }
#endif
#else
                if(enumFRCIndex >= _FRC_INDEX_1)
                {
                    ulBlkSpace = GET_ROW_FOR_SUB();
                }
#endif
            }
#if(_COLOR_IP_3DDI == _ON)
            // only for eo mode, s2 3ddi
            if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE) &&
               (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2) && (GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON))
            {
                ulBlkSpace = GET_ROW_FOR_SUB() * 2;
            }
#endif
            break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
        case 0x04:
#endif
        case 0x01:
        default:
            break;
    }

    ulAddress1 = ulBase + usOffset;
    ulAddress2 = ulAddress1 + ulBlkSpace;
    ulAddress3 = ulAddress2 + ulBlkSpace;

    switch(GET_MEMORY_FRAME_BUFFER())
    {
        case _MEMORY_1_FRAME_BUFFER:
        default:
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_1ST_BLOCK, ulAddress1);
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
            if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
            {
                ScalerFRCSetCapAddress(enumPageSelect, _FRC_2ND_BLOCK, ulAddress2);
            }
#endif
            break;

        case _MEMORY_2_FRAME_BUFFER:
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_1ST_BLOCK, ulAddress1);
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_2ND_BLOCK, ulAddress2);
            break;

        case _MEMORY_3_FRAME_BUFFER:
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_1ST_BLOCK, ulAddress1);
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_2ND_BLOCK, ulAddress2);
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_3RD_BLOCK, ulAddress3);
            break;
    }

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
    if (GET_FRC_TOP_BOTTOM_MODE_STATUS() == _FALSE)
#endif
    {
        switch(GET_MEMORY_FRAME_BUFFER())
        {
            case _MEMORY_1_FRAME_BUFFER:
            default:
                ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, ulAddress1);
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
                if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
                {
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ulAddress2);
                }
#endif
                break;

            case _MEMORY_2_FRAME_BUFFER:
                ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, ulAddress1);
                ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ulAddress2);
                break;

            case _MEMORY_3_FRAME_BUFFER:
                ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, ulAddress1);
                ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ulAddress2);
                ScalerFRCSetDispAddress(enumPageSelect, _FRC_3RD_BLOCK, ulAddress3);
                break;
        }
    }

    DebugMessageFRC("ulBlkSpace", ulBlkSpace);
    DebugMessageFRC("PAGE", enumPageSelect);
    DebugMessageFRC("FRC_1ST_BLOCK", ScalerFRCGetCapAddress(enumPageSelect, _FRC_1ST_BLOCK));
    DebugMessageFRC("FRC_2ND_BLOCK", ScalerFRCGetCapAddress(enumPageSelect, _FRC_2ND_BLOCK));
    DebugMessageFRC("FRC_3RD_BLOCK", ScalerFRCGetCapAddress(enumPageSelect, _FRC_3RD_BLOCK));
}


//--------------------------------------------------
// Description  : Calculate FRC Address
// Input Value  : EnumFRCIndex enumFRCIndex
// Output Value : DWORD ulBase
//--------------------------------------------------
DWORD ScalerFRCGetBaseAddress(EnumFRCIndex enumFRCIndex)
{
    DWORD ulStartAddress = GET_FRC_START_ADDRESS();
    BYTE ucIndex = enumFRCIndex * GET_BLK_NUM();

    switch(GET_RGN_MAX_DISPLAY_REGION())
    {
        case 0x01:
#if(_4P_DISPLAY_SUPPORT == _ON)
        case 0x04:
#endif
        default:
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            if(GET_ROT_TYPE() != _ROT_DISABLE)
            {
                ucIndex = enumFRCIndex * ScalerMemoryGetFrameBufferCount();
            }
#endif
            return ulStartAddress + (GET_ROW_FOR_MAIN() * ucIndex);

#if(_3P_DISPLAY_SUPPORT == _ON)
        case 0x03:

            if(enumFRCIndex >= _FRC_INDEX_2)
            {
                return ulStartAddress + (GET_ROW_FOR_MAIN() * (_FRC_INDEX_2 * GET_BLK_NUM())) + (GET_ROW_FOR_SUB() * (ucIndex - (_FRC_INDEX_2 * GET_BLK_NUM())));
            }
            else
            {
                return ulStartAddress + (GET_ROW_FOR_MAIN() * ucIndex);
            }
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
        case 0x02:

            if(ScalerRegion2PRegionEqual(GET_DISPLAY_MODE()) == _TRUE)
            {
                return ulStartAddress + (GET_ROW_FOR_MAIN() * ucIndex);
            }
            else
            {
                if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE) && (enumFRCIndex >= _FRC_INDEX_2))
                {
                    return ulStartAddress + (GET_ROW_FOR_MAIN() * (_FRC_INDEX_2 * 2)) + (GET_ROW_FOR_SUB() * (ucIndex - (_FRC_INDEX_2 * 2)));
                }
#if(_HW_I_DOMAIN_PATH_COUNT > 3)
                else if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) && (enumFRCIndex >= _FRC_INDEX_4))
                {
                    return ulStartAddress + (GET_ROW_FOR_MAIN() * (_FRC_INDEX_4 * 2)) + (GET_ROW_FOR_SUB() * (ucIndex - (_FRC_INDEX_4 * 2)));
                }
#endif
                else
                {
                    return ulStartAddress + (GET_ROW_FOR_MAIN() * ucIndex);
                }
            }
#endif
    }
}

//--------------------------------------------------
// Description  : Get FRC Bottom Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCGetFRCBottomAddress(void)
{
    DWORD ulFRCUseRow = 0;
    BYTE ucMainInputPathCount = ScalerMDomainGetInputPathCount(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(ScalerRegionGet2PMainPathRegion())));

#if((_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
    BYTE ucSubInputPathCount = ScalerMDomainGetInputPathCount(_HW_SUB_REGION_INPUT_PATH);
#endif

    // path count * (GET_ROW_FOR_MAIN or GET_ROW_FOR_SUB) * block number
    switch(GET_RGN_MAX_DISPLAY_REGION())
    {
#if(_2P_DISPLAY_SUPPORT == _ON)
        case 0x02:
            if(ScalerRegion2PRegionEqual(GET_DISPLAY_MODE()) == _TRUE)
            {
                ulFRCUseRow = ucMainInputPathCount * GET_ROW_FOR_MAIN() * GET_BLK_NUM() * 2;
            }
            else
            {
                // eo mode, s2 3ddi use the same space as non-3ddi(input s1s2)
                ulFRCUseRow = (ucMainInputPathCount * GET_ROW_FOR_MAIN() + ucSubInputPathCount * GET_ROW_FOR_SUB()) * GET_BLK_NUM();
            }
            break;
#endif
#if(_3P_DISPLAY_SUPPORT == _ON)
        case 0x03:
            ulFRCUseRow = (ucMainInputPathCount * GET_ROW_FOR_MAIN() + ucSubInputPathCount * GET_ROW_FOR_SUB() * 2) * GET_BLK_NUM();
            break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
        case 0x04:
            ulFRCUseRow = 4 * GET_ROW_FOR_MAIN() * GET_BLK_NUM();
            break;
#endif
        default:
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            if(GET_ROT_TYPE() != _ROT_DISABLE)
            {
                ulFRCUseRow = ucMainInputPathCount * GET_ROW_FOR_MAIN() * ScalerMemoryGetFrameBufferCount();
            }
            else
#endif
            {
                ulFRCUseRow = ucMainInputPathCount * GET_ROW_FOR_MAIN() * GET_BLK_NUM();
            }
            break;
    }

    SET_FRC_USE_ROW(ulFRCUseRow);
}

#if(_FW_FRC_DYNAMIC_SPACE_ALLOCATION == _ON)
//--------------------------------------------------
// Description  : Calculate frc main, sub, od memory usage
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCCalculateBlockRowSpace(DWORD ulRemainSize)
{
#if((_2P_PBP_LR_DISPLAY_SUPPORT == _ON) || (_3P_FLAG_DISPLAY_SUPPORT == _ON) || (_3P_SKEW_LR_DISPLAY_SUPPORT == _ON))
    StructTimingFormat stTimingFormat;
#endif

    DWORD uldiff = 0;
    DWORD ulRowForMain = 0;
    bit bSizeEqual = _FALSE;

    BYTE ucIndex = 0;
    BYTE ucFramenum = GET_BLK_NUM() * ((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) ? 2 : 1);

#if(_OD_FUNCTION == _ON)
    DWORD ulODSize = 0;
    EnumODParamIndex enumODBlkParam = _OD_PARAM_OFF;
#endif

    BYTE ucMainInputPathCount = ScalerMDomainGetInputPathCount(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(ScalerRegionGet2PMainPathRegion())));
    DWORD ulMainFrameSize = 0;
    WORD usMainhwidth = _PANEL_DH_WIDTH;
    WORD usMainvheight = _PANEL_DV_HEIGHT;

#if(_MULTI_DISPLAY_MAX != 0x01)
    BYTE ucSubInputPathCount = ScalerMDomainGetInputPathCount(_HW_SUB_REGION_INPUT_PATH);
    DWORD ulSubFrameSize = 0;
    WORD usSubhwidth = 0;
    WORD usSubvheight = 0;
#endif

    switch(GET_DISPLAY_MODE())
    {
        default: // 1P
            break;

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:

            memset(&stTimingFormat, 0x00, sizeof(stTimingFormat));
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            ScalerMDomainGetBackground_R2(&stTimingFormat);
#endif
            usSubhwidth = stTimingFormat.usHWidth;
            usSubvheight = usMainvheight;
            usMainhwidth = usMainhwidth - usSubhwidth;

            if(usMainhwidth == usSubhwidth)
            {
                bSizeEqual = ScalerRegion2PRegionEqual(GET_DISPLAY_MODE());
            }
            break;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            usSubhwidth = usMainhwidth / 2;
            usSubvheight = usMainvheight / 2;
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:

            usMainvheight /= 2;
            bSizeEqual = ScalerRegion2PRegionEqual(GET_DISPLAY_MODE());
            break;
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
            memset(&stTimingFormat, 0x00, sizeof(stTimingFormat));
            // region from left to right: R1(whole bg)->R2->R3

            ScalerMDomainGetBackground_R3(&stTimingFormat);

            usSubhwidth = stTimingFormat.usHWidth;
            usSubvheight = usMainvheight;
            if(usMainhwidth > (usSubhwidth * 2))
            {
                usMainhwidth = usMainhwidth - (usSubhwidth * 2);
            }
            else // set 1:1:1
            {
                DebugMessageFRC("3p_flag size error", usSubhwidth);
                usSubhwidth = (((usMainhwidth / 3) % 2) == 0) ? (usMainhwidth / 3) : (usMainhwidth / 3) - 1;
                usMainhwidth = usMainhwidth - (usSubhwidth * 2);
            }
#endif
            break;

#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
            memset(&stTimingFormat, 0x00, sizeof(stTimingFormat));
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            ScalerMDomainGetBackground_R2(&stTimingFormat);
#endif
            usSubhwidth = stTimingFormat.usHWidth;
            usMainhwidth = usMainhwidth - usSubhwidth;
            usSubvheight = usMainvheight / 2;
            break;


        case _DISPLAY_MODE_3P_SKEW_R:

            memset(&stTimingFormat, 0x00, sizeof(stTimingFormat));
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            ScalerMDomainGetBackground_R2(&stTimingFormat);
#endif
            usMainhwidth = stTimingFormat.usHWidth;

            usSubhwidth = _PANEL_DH_WIDTH - usMainhwidth;
            usSubvheight = usMainvheight / 2;
            break;

#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_3P_SKEW_B:

            usMainvheight /= 2;
            usSubhwidth = usMainhwidth / 2;
            usSubvheight = usMainvheight;
            break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:

            usMainhwidth /= 2;
            usMainvheight /= 2;
            bSizeEqual = _TRUE;
            break;
#endif
    }

    // initialization, replace SET_ROW_FOR_MAIN(0) with ulRowForMain

#if(_MULTI_DISPLAY_MAX != 0x01)
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
    {
        SET_ROW_FOR_SUB(0);
    }
#endif

    ucFramenum = ucFramenum * ((bSizeEqual == _TRUE) ? GET_RGN_MAX_DISPLAY_REGION() : 1);
    for(ucIndex = 0; ucIndex < (sizeof(tFRCRateCtrlbit) / sizeof(tFRCRateCtrlbit[0])); ucIndex++)
    {
        BYTE ucFactor = 1;
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
        ucFactor = ScalerFRCGetImgCmpHwidthDivisor(ScalerFRCGetMDispPath(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(ScalerRegionGet2PMainPathRegion()))), tFRCRateCtrlbit[ucIndex][1]);
#endif
        PDATA_DWORD(0) = (DWORD)ScalerFRCGetLineSumBit((usMainhwidth / ucFactor), tFRCRateCtrlbit[ucIndex][0], tFRCRateCtrlbit[ucIndex][1]) * usMainvheight;
        ulMainFrameSize = (GET_DEFAULT_FRAME_USE_MEMORY_ROW(PDATA_DWORD(0)) + _FRAME_SIZE_MARGIN) * ucFramenum * ucFactor;

        uldiff = (ucIndex == 0) ? ulMainFrameSize : ulMainFrameSize - ((ulRowForMain >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) * ucFramenum * ucMainInputPathCount);

        if(ulRemainSize >= uldiff)
        {
            ulRowForMain = (((ulMainFrameSize / ucFramenum) / ucMainInputPathCount) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
            ulRemainSize -= uldiff;

            if(bSizeEqual == _TRUE)
            {
                SET_ROW_FOR_SUB(ulRowForMain);
            }
            else
            {
#if(_MULTI_DISPLAY_MAX != 0x01)
                if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
                {
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
                    // considering of 3ddi (_INPUT_PATH_S2), do not use any macro related to current status
                    ucFactor = ScalerFRCGetImgCmpHwidthDivisor(_HW_M_DOMAIN_DISP_SUB_PATH, tFRCRateCtrlbit[ucIndex][1]);
#endif
                    PDATA_DWORD(0) = (DWORD)ScalerFRCGetLineSumBit((usSubhwidth / ucFactor), tFRCRateCtrlbit[ucIndex][0], tFRCRateCtrlbit[ucIndex][1]) * usSubvheight;
                    ulSubFrameSize = (GET_DEFAULT_FRAME_USE_MEMORY_ROW(PDATA_DWORD(0)) + _FRAME_SIZE_MARGIN) * ucFramenum * ucFactor * (GET_RGN_MAX_DISPLAY_REGION() - 1);
                    uldiff = (ucIndex == 0) ? ulSubFrameSize : ulSubFrameSize - ((GET_ROW_FOR_SUB() >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) * ucFramenum * ucSubInputPathCount * (GET_RGN_MAX_DISPLAY_REGION() - 1));

                    if(ulRemainSize >= uldiff)
                    {
                        SET_ROW_FOR_SUB((ulSubFrameSize / ucFramenum / ucSubInputPathCount / (GET_RGN_MAX_DISPLAY_REGION() - 1)) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
                        ulRemainSize -= uldiff;
                    }
                    else
                    {
                        break;
                    }
                }
#endif
            }

#if(_OD_FUNCTION == _ON)
            PDATA_DWORD(0) = (DWORD)_PANEL_DH_WIDTH * _PANEL_DV_HEIGHT * GET_OD_BIT_RATE(_MTP_OD_ACCEPT_MIN_PARAM);
            ulODSize = CEILING_OF_INT_DIVISION(GET_DEFAULT_FRAME_USE_MEMORY_ROW(PDATA_DWORD(0)), 10); // od bit unit was 0.1bit
            ulODSize = ulODSize + _FRAME_SIZE_MARGIN;

            if((enumODBlkParam == _OD_PARAM_OFF) && (ulRemainSize >= ulODSize))
            {
                enumODBlkParam = _MTP_OD_ACCEPT_MIN_PARAM;
                ulRemainSize -= ulODSize;
            }
#endif
        }
        else
        {
            break;
        }
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON) // rotation only support eo mode
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        PDATA_DWORD(0) = ((ulRowForMain >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) * ucFramenum * ucMainInputPathCount) + ulRemainSize;
        PDATA_DWORD(0) = PDATA_DWORD(0) / ((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) ? 2 : 1) / ucMainInputPathCount;
        SET_TOTAL_ROW_FOR_ROTATION_SINGLE_PATH(PDATA_DWORD(0) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
        SET_ROW_FOR_ROTATION((PDATA_DWORD(0) / 3) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
    }
#endif

    SET_ROW_FOR_MAIN(ulRowForMain);

#if(_MULTI_DISPLAY_MAX != 0x01)
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P) // fool proof
    {
        if((ulRowForMain == 0) || (GET_ROW_FOR_SUB() == 0))
        {
            ulRowForMain = ((DWORD)(_MEMORY_ROW / (_HW_I_DOMAIN_PATH_COUNT * ucFramenum)) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
            SET_ROW_FOR_MAIN(ulRowForMain);
            SET_ROW_FOR_SUB(ulRowForMain);
            DebugMessageFRC("_M_DOMAIN_IMG_CMP_SUPPORT should be on!", 0);
        }
    }
    else
#endif
    {
        if(ulRowForMain == 0)
        {
            SET_ROW_FOR_MAIN(_MEMORY_BOTTOM_ADDRESS >> 1);
            DebugMessageFRC("_M_DOMAIN_IMG_CMP_SUPPORT should be on!", 0);
        }
    }

    DebugMessageFRC("GET_ROW_FOR_MAIN", ulRowForMain);
    DebugMessageFRC("GET_ROW_FOR_SUB", GET_ROW_FOR_SUB());
}

#endif

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Bank Offset By FRC Page
// Input Value  : EnumMDomainDisplayDataPath enumMDispPath, EnumImgCmpParamIndex enumImgCmpIndex
// Output Value : BYTE ucFactor
//--------------------------------------------------
BYTE ScalerFRCGetImgCmpHwidthDivisor(EnumMDomainDisplayDataPath enumMDispPath, EnumImgCmpParamIndex enumImgCmpIndex)
{
    if(GET_IMG_CMP_ENABLE(enumImgCmpIndex) == _TRUE)
    {
        return ScalerFRCGetMDispPathCount(enumMDispPath);
    }
    return 1;
}
#endif

//--------------------------------------------------
// Description  : Get Bank Offset By FRC Page
// Input Value  : EnumFRCPageSelect enumPageSelect
// Output Value : WORD bankoffset
//--------------------------------------------------
WORD ScalerFRCGetShiftBankOffset(EnumFRCPageSelect enumPageSelect)
{
    // 1P, imc off, extension/recapture on
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) && (GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _FALSE))
    {
        switch(enumPageSelect)
        {
            default:
            case _FRC_MAIN1_PAGE:
                return _M1_BANK_OFFSET_HSD;

            case _FRC_MAIN2_PAGE:
                return _M2_BANK_OFFSET_HSD;

            case _FRC_SUB1_PAGE:
                return _S1_BANK_OFFSET_HSD;

            case _FRC_SUB2_PAGE:
                return _S2_BANK_OFFSET_HSD;
        }
    }
    else
#endif
    {
        switch(enumPageSelect)
        {
            default:
            case _FRC_MAIN1_PAGE:
                return _M1_BANK_OFFSET;

            case _FRC_MAIN2_PAGE:
                return _M2_BANK_OFFSET;

            case _FRC_SUB1_PAGE:
                return _S1_BANK_OFFSET;

            case _FRC_SUB2_PAGE:
                return _S2_BANK_OFFSET;

            case _FRC_SUB3_PAGE:
                return _S3_BANK_OFFSET;

            case _FRC_SUB4_PAGE:
                return _S4_BANK_OFFSET;
        }
    }
}

//--------------------------------------------------
// Description  : Set different preread by path
// Input Value  : EnumFRCPageSelect enumPageSelect
// Output Value : usPreReadLine
//--------------------------------------------------
WORD ScalerFRCSetDiffPreReadByPath(EnumFRCPageSelect enumPageSelect)
{
    BYTE ucDenPreReadDist = 0;
    BYTE ucDenPreReadDistDynamic = 0;
    WORD usDVstart = GET_MDOMAIN_OUTPUT_VSTART() - 1;
    bit bDynamic = (_HW_FRC_LENGTH_TYPE == _FRC_LENGTH_8BIT);

#if(_FRC_LENGTH_ENLRGE_M1_M2_ONLY == _ON)
    if((ScalerFRCGetLengthEnlargeM1M2Support() == _ON) &&
       (GET_1P_EO_STATUS() == _TRUE))
    {
        bDynamic = _ON;
    }
#endif

    switch(enumPageSelect)
    {
        case _FRC_MAIN1_PAGE:
        default:
            ucDenPreReadDist = 12;
            ucDenPreReadDistDynamic = 5;
            break;

        case _FRC_MAIN2_PAGE:
            ucDenPreReadDist = 10;
            ucDenPreReadDistDynamic = 3;
            break;

        case _FRC_SUB1_PAGE:
#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
            ucDenPreReadDist = 8;
            ucDenPreReadDistDynamic = 4;
#else
            ucDenPreReadDist = 10;
            ucDenPreReadDistDynamic = 3;
#endif
            break;

        case _FRC_SUB2_PAGE:
            ucDenPreReadDist = 6;
            ucDenPreReadDistDynamic = 4;
            break;

        case _FRC_SUB3_PAGE:
            ucDenPreReadDist = 16;
            ucDenPreReadDistDynamic = 4;
            break;

        case _FRC_SUB4_PAGE:
            ucDenPreReadDist = 14;
            ucDenPreReadDistDynamic = 4;
            break;
    }

    if((bDynamic == _ON) && (usDVstart >= 5))
    {
        return (usDVstart - ucDenPreReadDistDynamic);
    }
    else
    {
        return ((usDVstart < ucDenPreReadDist) ? 0 : (usDVstart - ucDenPreReadDist));
    }
}

//--------------------------------------------------
// Description  : Allocate BW for Main and Sub
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCBWInitialAllocation(void)
{
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        SET_FRC_MAIN_BW(GET_MEMORY_FRC_OD_BW());
        return;
    }
#if(_MULTI_DISPLAY_MAX > 0x01)
    else
    {
        BYTE ucRegionCnt = ScalerRegionGetMaxRegionCount();

        WORD usMainhwidth = 0;
        WORD usSubCaphwidth = _PANEL_DH_WIDTH;
        WORD usSubDisphwidth = 0;
        WORD usMainFramerate = _MTP_MAIN_PREFER_TIMING_FRAME_RATE;

        DWORD ulMainBW = 0;
        DWORD ulMainBWCal = 0;
        DWORD ulSubBW = 0;
        DWORD ulODUseBW = 0;
        DWORD ulODAcceptMinBW = 0;
        DWORD ulTotalBW = GET_MEMORY_FRC_OD_BW();

        DWORD ulSubMaxClk = (ScalerFmtCnvGetDataPathMaxSpeedLimit() * 100) * ScalerMDomainGetInputPathCount(_HW_SUB_REGION_INPUT_PATH); // kHz

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        WORD usLwidth = 0;
        WORD usRwidth = 0;
#endif

        StructMemoryBWUsageParam stMemBWParam;
        StructTimingFormat stTimingFormat;
        EnumInputDataPath enumMainInputPath = _INPUT_PATH_M1_M2_S1_S2;
        EnumInputDataPath enumSubInputPath = _INPUT_PATH_S3;

        ScalerMDomainGetMemBWParam(&stMemBWParam);
        memset(&stTimingFormat, 0x00, sizeof(stTimingFormat));

        //////////////////////////////////////////////////////////////////////////
        //    If the size of display regions are equal, BW is divided equally   //
        //    Otherwise, follow the new flow                                    //
        //    BW for Main No HSD -> BW for Sub -> BW for OD                     //
        //////////////////////////////////////////////////////////////////////////

        for(BYTE uccnt = 0; uccnt < _MULTI_DISPLAY_MAX; uccnt++) // _MULTI_DISPLAY_MAX for change display mode
        {
            CLR_PATH_MEMORY_BW_CONFIG(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(uccnt)));
        }

        switch(GET_DISPLAY_MODE())
        {
            default: // 1P, pbp_tb, 4p
                SET_FRC_MAIN_BW(ulTotalBW / ucRegionCnt);
                return;

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:

                ScalerMDomainGetBackground_R1(&stTimingFormat);
                usLwidth = stTimingFormat.usHWidth;
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
                ScalerMDomainGetBackground_R2(&stTimingFormat);
#endif
                usRwidth = stTimingFormat.usHWidth;

                if((usRwidth * 2) == usLwidth)
                {
                    // if L hwidth == R hwidth, BW/2
                    SET_FRC_MAIN_BW(ulTotalBW / ucRegionCnt);
                    SET_FRC_SUB_BW(ulTotalBW / ucRegionCnt);
                    return;
                }
                else
                {
                    // if L hwidth > R hwidth, continue
                    if(ScalerDDomainPbpLRLargeFrameMappingRegion() == _PBP_LR_LARGE_FRAME_R1A1)
                    {
                        usMainhwidth = ((usLwidth >= usRwidth) ? (usLwidth - usRwidth) : 0);
                        usSubDisphwidth = usRwidth;
                    }
                    else // _PBP_LR_LARGE_FRAME_R2A1
                    {
                        usMainhwidth = usRwidth;
                        usSubDisphwidth = ((usLwidth >= usRwidth) ? (usLwidth - usRwidth) : 0);
                    }

#if(_2P_PBP_LR_PERFORMANCE_TYPE == _MAIN_EQUAL_TO_SUB)
                    SET_FRC_MAIN_BW(ulTotalBW * usMainhwidth / usLwidth);
                    SET_FRC_SUB_BW(ulTotalBW * usSubDisphwidth / usLwidth);
                    return;
#else

                    enumMainInputPath = _INPUT_PATH_M1_M2;
                    enumSubInputPath = _HW_SUB_REGION_INPUT_PATH;
#endif
                }
                break;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
                usMainhwidth = _PANEL_DH_WIDTH;
                usSubDisphwidth = _PANEL_DH_WIDTH / 2;

                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE)
                {
                    enumMainInputPath = _INPUT_PATH_M1_M2;
                }
                else
                {
                    enumMainInputPath = _INPUT_PATH_M1_M2_S1_S2;
                }

                enumSubInputPath = _HW_SUB_REGION_INPUT_PATH;
                ScalerFRCBWAllocateForSubOption(&usSubCaphwidth, &usSubDisphwidth, &ulSubMaxClk);
                break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_3P_FLAG:
#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
                // 3P flag may be 1:2:1 or 1:1:1
                ScalerMDomainGetBackground_R3(&stTimingFormat);
#endif
                usSubDisphwidth = stTimingFormat.usHWidth;
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
                ScalerMDomainGetBackground_R2(&stTimingFormat);
#endif
                usMainhwidth = stTimingFormat.usHWidth;

                SET_FRC_MAIN_BW(ulTotalBW * usMainhwidth / (usMainhwidth + (2 * usSubDisphwidth)));
                SET_FRC_SUB_BW(ulTotalBW * usSubDisphwidth / (usMainhwidth + (2 * usSubDisphwidth)));
                return;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_3P_SKEW_L:
            case _DISPLAY_MODE_3P_SKEW_R:
                SET_FRC_MAIN_BW(ulTotalBW / 2);
                SET_FRC_SUB_BW(ulTotalBW / 4);
                return;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_3P_SKEW_T:
            case _DISPLAY_MODE_3P_SKEW_B:

                usMainhwidth = _PANEL_DH_WIDTH;
                usSubDisphwidth = _PANEL_DH_WIDTH / 2;
                enumMainInputPath = _INPUT_PATH_M1_M2; // SkewT is the same as SkewB, Left is the same as Right, take SkewT as example
                enumSubInputPath = _INPUT_PATH_S1_S2;
                SET_SUB_ALLOCATION_IHTOTAL(_PANEL_DH_TOTAL);
                break;
#endif
        }

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
        if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
        {
            usMainFramerate = _PANEL_MAX_FRAME_RATE;
        }
#endif
        // FRC Main Use BW, use Panel default value to calculate BW
        PDATA_DWORD(0) = GET_D_CLK_FROM_VFREQ((DWORD)_PANEL_DH_TOTAL * ((_PANEL_DV_HEIGHT) + GET_CVT_MIN_VPORCH((_PANEL_DV_HEIGHT), usMainFramerate)), usMainFramerate); // kHz

        ulMainBWCal = ScalerFRCBWCalUsage(usMainhwidth, usMainhwidth, (_MTP_MAIN_ACCEPT_MIN_COLOR_DEPTH * 3), _IMG_CMP_PARAM_LLB_8B_TYP, PDATA_DWORD(0), enumMainInputPath, _TRUE);
        ulMainBW = ulMainBWCal + (ulMainBWCal / 20);

        // FRC Sub Use BW, use _HW_DATA_PATH_SPEED_LIMIT for Sub to calculate BW
        pData[0] = (_M_DOMAIN_IMG_CMP_SUPPORT == _ON) ? _IMG_CMP_PARAM_LLB_8B_TYP : _IMG_CMP_PARAM_OFF;
        ulSubBW = ScalerFRCBWCalUsage(usSubCaphwidth, usSubDisphwidth, (_MTP_SUB_ACCEPT_MIN_COLOR_DEPTH * 3), pData[0], ulSubMaxClk, enumSubInputPath, _TRUE);

#if(_OD_FUNCTION == _ON)
        stMemBWParam.ulDHFreq = (DWORD)usMainFramerate * _PANEL_DV_TOTAL;
        ulODAcceptMinBW = ScalerMDomainODCalculateMemoryUseBW(GET_OD_BIT_RATE(_MTP_OD_ACCEPT_MIN_PARAM), &stMemBWParam);
#endif

        // In 3P mode, ulSubBW need to miltiply by 2 for two sub regions
        PDATA_DWORD(0) = (ucRegionCnt == 3) ? (ulSubBW * 2) : ulSubBW;

        if(ulTotalBW > (ulMainBW + PDATA_DWORD(0) + ulODAcceptMinBW))
        {
            ulMainBW += ulTotalBW - (ulMainBW + PDATA_DWORD(0) + ulODAcceptMinBW);
            ulODUseBW = ulODAcceptMinBW;
        }
        else if(ulTotalBW > (ulMainBW + PDATA_DWORD(0)))
        {
            ulODUseBW = ulTotalBW - (ulMainBW + PDATA_DWORD(0));
        }
        else if(ulTotalBW > ulMainBW)
        {
            PDATA_DWORD(0) = ulTotalBW - ulMainBW;

            // ulSubBW is divided by to for GET_FRC_SUB_BW()
            ulSubBW = (ucRegionCnt == 3) ? (PDATA_DWORD(0) / 2) : PDATA_DWORD(0);
            ulODUseBW = 0;
        }
        else // (ulTotalBW < ulMainBW)
        {
            ulMainBW = ulTotalBW - ((ulTotalBW / 20) * (ucRegionCnt - 1));
            ulSubBW = (ulTotalBW / 20);
            ulODUseBW = 0;
        }

        ulMainBW += ulODUseBW; // 1P, PBP_LR L!=R, PIP

        SET_FRC_MAIN_BW(ulMainBW);
        SET_FRC_SUB_BW(ulSubBW);

        DebugMessageFRC("FRC ALLOCATE MAIN BW", GET_FRC_MAIN_BW());
        DebugMessageFRC("FRC ALLOCATE SUB BW", GET_FRC_SUB_BW());

#if(_OD_FUNCTION == _ON)
        DebugMessageFRC("FRC ALLOCATE OD BW", ulODUseBW);
        if(ulMainBW < ulMainBWCal + ulODAcceptMinBW)
        {
            DebugMessageFRC("[Warning]!!!!!! OD May Be Disabled", ulODAcceptMinBW);
        }
#endif
    }
#endif
}

//--------------------------------------------------
// Description  : Get FRC BW Usage from parameter
// Input Value  : WORD ushwidth, WORD usColorDepth, WORD usLLB, DWORD ulPixelclk(unit: kHz), EnumInputDataPath enumInputPath, bit bDefaultMode
// Output Value : BW
//--------------------------------------------------
DWORD ScalerFRCBWCalUsage(WORD usCaphwidth, WORD usDisphwidth, WORD usColorDepth, EnumImgCmpParamIndex enumLLB, DWORD ulPixelclk, EnumInputDataPath enumInputPath, bit bDefaultMode)
{
    DWORD ulLineSumBit = 0;
    DWORD ulFRCWriteBw = 0;
    DWORD ulFRCReadBw = 0;
    // panel typ frame rate = ((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) ? _PANEL_TYP_FRAME_RATE : _MTP_MAIN_PREFER_TIMING_FRAME_RATE)
    // only mtp allocation need to calculate bw usage
    WORD usFramerate = _MTP_MAIN_PREFER_TIMING_FRAME_RATE;
    DWORD ulDclk = GET_D_CLK_FREQ();

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
    {
        usFramerate = _PANEL_MAX_FRAME_RATE;
    }
#endif

    if(bDefaultMode == _TRUE)
    {
        ulDclk = GET_D_CLK_FROM_VFREQ((DWORD)_PANEL_DH_TOTAL * _PANEL_DV_TOTAL, usFramerate);
    }

    if(ulDclk > GET_PANEL_PIXEL_CLOCK_MAX_SPREAD())
    {
        ulDclk = GET_PANEL_PIXEL_CLOCK_MAX_SPREAD();
    }

    enumInputPath = enumInputPath;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerMDomainGetInputPathCount(enumInputPath) == _INPUT_PATH_4)
    {
        usCaphwidth = (usCaphwidth / 2);
        usDisphwidth = (usDisphwidth / 2);
    }
#endif

    // Calculate FRC write BW
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        ulFRCWriteBw = ScalerRotationCalculateCaptureBW(ulPixelclk, usCaphwidth);
    }
    else
#endif
    {
        // Capture LLB
        ulLineSumBit = ScalerFRCGetLineSumBit(usCaphwidth, usColorDepth, enumLLB);

        // FRC write BW
        ulFRCWriteBw = GET_DWORD_MUL_DIV(ulPixelclk, ulLineSumBit, ((bDefaultMode == _TRUE) ? GET_BW_ALLOCATION_IHTOTAL(enumInputPath) : GET_MDOMAIN_INPUT_HTOTAL())) / _MEMORY_BUS_WIDTH / 100;
    }

    // Display LLB
    ulLineSumBit = ScalerFRCGetLineSumBit(usDisphwidth, usColorDepth, enumLLB);

    // FRC read BW
    ulFRCReadBw = GET_DWORD_MUL_DIV((DWORD)ulDclk, ulLineSumBit, GET_MDOMAIN_OUTPUT_HTOTAL()) / _MEMORY_BUS_WIDTH / 100;
    ulFRCReadBw += ulFRCReadBw * ((_DCLK_SPREAD_RANGE / _PANEL_DPLL_SSCG_DIV_MODE) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerMDomainGetInputPathCount(enumInputPath) == _INPUT_PATH_4)
    {
        ulFRCWriteBw *= 2;
        ulFRCReadBw *= 2;
    }
#endif

    if(bDefaultMode == _FALSE)
    {
        SET_CAPTURE_BW(GET_MDOMAIN_INPUT_DATA_PATH(), ulFRCWriteBw);
        SET_DISPLAY_BW(GET_MDOMAIN_INPUT_DATA_PATH(), ulFRCReadBw);
    }

    // FRC total BW
    ulFRCWriteBw = ulFRCWriteBw + ulFRCReadBw;

    DebugMessageFRC("FRC ALLOCATE BW", ulFRCWriteBw);

    return ulFRCWriteBw;
}

//--------------------------------------------------
// Description  : FRC BW Allocation for PIP/Eagle Sight
// Input Value  : pusSubCaphwidth, pusSubDisphwidth, pulSubMaxClk
// Output Value : pusSubCaphwidth, pusSubDisphwidth, pulSubMaxClk
//--------------------------------------------------
void ScalerFRCBWAllocateForSubOption(WORD *pusSubCaphwidth, WORD *pusSubDisphwidth, DWORD *pulSubMaxClk)
{
    WORD usSubMaxHwidth = 0;
    WORD usFramerate = 0;
    WORD usVtotal = 0;
    usFramerate = usFramerate;
    usVtotal = usVtotal;

    switch(GET_DISPLAY_MODE())
    {
        default:
        case _DISPLAY_MODE_2P_PIP:
            usSubMaxHwidth = _PIP_SUB_BW_RESERVE_MAX_HWIDTH;
            if(usSubMaxHwidth % _MEMORY_BUS_WIDTH != 0)
            {
                usSubMaxHwidth = ((usSubMaxHwidth / _MEMORY_BUS_WIDTH) + 1) * _MEMORY_BUS_WIDTH;
            }
            usSubMaxHwidth = MINOF(usSubMaxHwidth + _SUB_BW_HWIDTH_MARGIN, _PANEL_DH_WIDTH / 2);
#if(_PIP_SUB_BW_RESERVE_TYPE == _SUB_SINGLE_PATH_HW_LIMIT_SPEED)

            *pusSubCaphwidth = usSubMaxHwidth;
            *pusSubDisphwidth = usSubMaxHwidth;
            *pulSubMaxClk = (ScalerFmtCnvGetDataPathMaxSpeedLimit() * 100) * ScalerMDomainGetInputPathCount(_HW_SUB_REGION_INPUT_PATH);
            SET_SUB_ALLOCATION_IHTOTAL(_PANEL_DH_TOTAL);

#elif(_PIP_SUB_BW_RESERVE_TYPE == _SUB_FHD_60)

            *pusSubCaphwidth = 1920;
            *pusSubDisphwidth = 1920;
            *pulSubMaxClk = GET_D_CLK_FROM_VFREQ((DWORD)2100 * 1150, 600);
            SET_SUB_ALLOCATION_IHTOTAL(2100);

#elif(_PIP_SUB_BW_RESERVE_TYPE == _SUB_QUARTER_RESOLUTION)
            usFramerate = _MTP_SUB_PREFER_TIMING_FRAME_RATE;
            usVtotal = ((_PANEL_DV_HEIGHT / 2) + GET_CVT_MIN_VPORCH((_PANEL_DV_HEIGHT / 2), usFramerate));

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
            if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
            {
                usFramerate = _PANEL_MAX_FRAME_RATE;
                usVtotal = (_PANEL_DV_HEIGHT + GET_CVT_MIN_VPORCH(_PANEL_DV_HEIGHT, usFramerate));
            }
#endif

            *pusSubCaphwidth = usSubMaxHwidth;
            *pusSubDisphwidth = usSubMaxHwidth;
            *pulSubMaxClk = GET_D_CLK_FROM_VFREQ((DWORD)(_PANEL_DH_TOTAL / 2) * usVtotal, usFramerate);
            SET_SUB_ALLOCATION_IHTOTAL(_PANEL_DH_TOTAL / 2);
#endif
            break;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            usFramerate = _PANEL_MAX_FRAME_RATE;
            usVtotal = (_PANEL_DV_HEIGHT + GET_CVT_MIN_VPORCH(_PANEL_DV_HEIGHT, usFramerate));

            usSubMaxHwidth = _EAGLE_SIGHT_SUB_BW_RESERVE_MAX_HWIDTH;
            if(usSubMaxHwidth % _MEMORY_BUS_WIDTH != 0)
            {
                usSubMaxHwidth = ((usSubMaxHwidth / _MEMORY_BUS_WIDTH) + 1) * _MEMORY_BUS_WIDTH;
            }
            usSubMaxHwidth = MINOF(usSubMaxHwidth + _SUB_BW_HWIDTH_MARGIN, _PANEL_DH_WIDTH / 2);
            *pusSubCaphwidth = usSubMaxHwidth;
            *pusSubDisphwidth = usSubMaxHwidth;
            *pulSubMaxClk = GET_D_CLK_FROM_VFREQ((DWORD)_PANEL_DH_TOTAL * usVtotal, usFramerate);
            SET_SUB_ALLOCATION_IHTOTAL(_PANEL_DH_TOTAL);
            break;
#endif
    }
}

//--------------------------------------------------
// Description  : Update FRC Current BW Usage
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCUpdateCurrentBW(void)
{
    if(GET_MEMORY_WORK_TYPE() == _MEMORY_WORK_MODE)
    {
        BYTE uccnt = 0;
        DWORD ulPathBwSum = 0;

        // sum of all region's capture bw
        for(uccnt = 0; uccnt < ScalerRegionGetMaxRegionCount(); uccnt++)
        {
            ulPathBwSum += GET_CAPTURE_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(uccnt)));
        }

        if((GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_L) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_R) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_TB) ||
           (GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_T) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_SKEW_B) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_4P))

        {
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_3P_SKEW_L:
                case _DISPLAY_MODE_3P_SKEW_R:
                default:
                    // display bw of _REGION_INDEX_1 / _REGION_INDEX_2 only need to add once
                    ulPathBwSum += GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0)));
                    ulPathBwSum += MAXOF(GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_1))), GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_2))));
                    break;

                case _DISPLAY_MODE_2P_PBP_TB:
                    // display bw of _REGION_INDEX_0(2) only need to add once
                    ulPathBwSum += MAXOF(GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0))), GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_1))));
                    break;

                case _DISPLAY_MODE_4P:
                    // display bw of _REGION_INDEX_0(2) / _REGION_INDEX_1(3) only need to add once
                    ulPathBwSum += MAXOF(GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0))), GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_1))));
                    ulPathBwSum += MAXOF(GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_2))), GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_3))));
                    break;

                case _DISPLAY_MODE_3P_SKEW_T:
                case _DISPLAY_MODE_3P_SKEW_B:
                    // display bw of _REGION_INDEX_0 / _REGION_INDEX_1 only need to add the max one
                    ulPathBwSum += MAXOF(GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0))), GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_1))));
                    ulPathBwSum += GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_2)));
                    break;
            }
        }
        else
        {
            for(uccnt = 0; uccnt < ScalerRegionGetMaxRegionCount(); uccnt++)
            {
                ulPathBwSum += GET_DISPLAY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(uccnt)));
            }
#if(_COLOR_IP_3DDI == _ON)
            if((GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON) && (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2))
            {
                ulPathBwSum += Scaler3DDICalMaxMemoryBW();
            }
#endif
        }
#if(_OD_FUNCTION == _ON)
        // Update FRC remaining bandwidth
        PDATA_DWORD(0) = ((GET_MEMORY_FRC_OD_BW() > ulPathBwSum) ? (GET_MEMORY_FRC_OD_BW() - ulPathBwSum) : 0);
        SET_MEMORY_REMAIN_BW(PDATA_DWORD(0));
#endif
    }
}

//--------------------------------------------------
// Description  : Get Image Compression parameter
// Input Value  : Region
// Output Value : Img cmp parameter
//--------------------------------------------------
EnumImgCmpParamIndex ScalerFRCImgCmpGetPara(BYTE ucRegionIndex)
{
    return GET_FRC_RCP_IMG_CMP_PARAM(GET_MDOMAIN_FRC_CTRL_PARAM_INDEX(ucRegionIndex));
}

//--------------------------------------------------
// Description  : Get Image Compression Active
// Input Value  : RegionIndex
// Output Value : _TRUE Img cmp active, _FALSE Img cmp inactive
//--------------------------------------------------
bit ScalerFRCImgCmpGetActive(BYTE ucRegionIndex)
{
    if((ScalerFRCImgCmpGetPara(ucRegionIndex) != _IMG_CMP_PARAM_OFF) &&
       (ScalerFRCGetSourceSelect(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(ucRegionIndex))) == _DDOMAIN_SRC_FROM_FRC))
    {
        return _TRUE;
    }
    return _FALSE;
}

#if((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) && (_FRC_CAPTURE_BW_CTRL_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get BW Ctrl info - FRC Cap
// Input Value  : Pointer to BW ctrl client info
// Output Value : None
//--------------------------------------------------
void ScalerFRCBwCtrlGetCapClientInfo(StructBwCtrlClientInfo *pstInfo)
{
    BYTE code ucTimeThdPercent = 90; // For fine tune usage
    BYTE code ucReqThdFixedValue = 0x01U;
    WORD usHActive = 0;
    WORD usHTotal = GET_MDOMAIN_INPUT_HTOTAL();
    WORD usBitRate10x = 0;
    DWORD ulPixClk_KHz = 0;
    DWORD ulMPll_MHz = _MEMORY_PLL_CLOCK;
    DWORD ulLineTotalLen = 0;
    WORD usLineRWNum = 0;
    DWORD ulTValue = 0;
    DWORD ulDenominator = 0;
    WORD usFullHWidth = GET_FIFO_INPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH());
    WORD code usVHeightDummy = 1080;
    StructSDRAMDataInfo stFIFOSize = {usFullHWidth, usVHeightDummy, usFullHWidth, usVHeightDummy};
    DWORD ulLineSumBit = 0;
    DWORD ulFullPixClk_KHz = (DWORD)GET_MDOMAIN_INPUT_HFREQ() * GET_MDOMAIN_INPUT_HTOTAL() / 10;
    WORD usRWLen_64bit = ScalerFRCGetAccessLength(_FRC_WRITE_LENGTH);

    pstInfo->bEnable = (_FRC_CAPTURE_BW_CTRL_SUPPORT == _ON);
    pstInfo->enumMode = _BW_CTRL_REQ_MODE;
    pstInfo->ulReqThd = ucReqThdFixedValue;

    ScalerFRCUpdateFifoScalingSize(&stFIFOSize);
    usHActive = stFIFOSize.usInputHWidth;

    ulLineSumBit = ScalerFRCGetLineSumBit(usHActive, GET_MEMORY_DATA_BIT(), GET_IMG_CMP_PARAM());
    ulLineTotalLen = CEILING_OF_INT_DIVISION(ulLineSumBit, 64);
    usLineRWNum = LOWORD(ScalerMemoryCalculateNumberAndRemain(ulLineTotalLen, usRWLen_64bit, 1));

    usBitRate10x = ulLineSumBit * 10 / usHActive;
    ulPixClk_KHz = ulFullPixClk_KHz / ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()); // Path PixClk

    // A (unit: request) & T (unit: mclk_cycle)
    // A = 1,
    //
    // T
    // = (line_total_len * 64 * MPLL_freq) / ((HActive / HTotal) * pixel_rate * bit) / (line_rw_num + 1)
    // = (line_total_len * 64 * MPLL_freq) / ((HActive * bit) * pixel_rate / HTotal) / (line_rw_num + 1)
    ulDenominator = ScalerGlobalComputeDwordMulDiv(((DWORD)usHActive * usBitRate10x), ulPixClk_KHz, usHTotal) / 1000 / 10;
    ulTValue = ScalerGlobalComputeDwordMulDiv(((DWORD)ulLineTotalLen * 64 * ulMPll_MHz), ucTimeThdPercent, ulDenominator) / (usLineRWNum + 1) / 100;

    pstInfo->ulTimeThd = ulTValue; // Reg = ulTValue/16
}
#endif

#if((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) && (_FRC_DISPLAY_BW_CTRL_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get BW Ctrl info - FRC Disp
// Input Value  : Pointer to BW ctrl client info
// Output Value : None
//--------------------------------------------------
void ScalerFRCBwCtrlGetDispClientInfo(StructBwCtrlClientInfo *pstInfo)
{
    BYTE code ucTimeThdPercent = 90; // For fine tune usage
    BYTE code ucReqThdFixedValue = 0x01U;
    WORD usHActive = 0;
    WORD usHTotal = GET_MDOMAIN_OUTPUT_HTOTAL(); // Full HTotal
    WORD usBitRate10x = 0;
    DWORD ulPixClk_KHz = GET_D_CLK_FREQ() / (ScalerFRCGetMDispPathCount(ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH())));
    DWORD ulMPll_MHz = _MEMORY_PLL_CLOCK;
    DWORD ulLineTotalLen = 0;
    WORD usLineRWNum = 0;
    DWORD ulTValue = 0;
    DWORD ulDenominator = 0;
    WORD usFullHWidth = GET_FIFO_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH());
    WORD code usVHeightDummy = 1080;
    StructSDRAMDataInfo stFIFOSize = {usFullHWidth, usVHeightDummy, usFullHWidth, usVHeightDummy};
    DWORD ulLineSumBit = 0;
    WORD usRWLen_64bit = ScalerFRCGetAccessLength(_FRC_READ_LENGTH);

    pstInfo->bEnable = (_FRC_DISPLAY_BW_CTRL_SUPPORT == _ON);
    pstInfo->enumMode = _BW_CTRL_REQ_MODE;
    pstInfo->ulReqThd = ucReqThdFixedValue;

    ScalerFRCUpdateFifoScalingSize(&stFIFOSize);
    usHActive = stFIFOSize.usOutputHWidth;

    ulLineSumBit = ScalerFRCGetLineSumBit(usHActive, GET_MEMORY_DATA_BIT(), GET_IMG_CMP_PARAM());
    ulLineTotalLen = CEILING_OF_INT_DIVISION(ulLineSumBit, 64);
    usLineRWNum = LOWORD(ScalerMemoryCalculateNumberAndRemain(ulLineTotalLen, usRWLen_64bit, 1));

    usBitRate10x = ulLineSumBit * 10 / usHActive;

    // A (unit: request) & T (unit: mclk_cycle)
    // A = 1,
    //
    // T
    // = (line_total_len * 64 * MPLL_freq) / ((HActive / HTotal) * pixel_rate * bit) / (line_rw_num + 1)
    // = (line_total_len * 64 * MPLL_freq) / ((HActive * bit) * pixel_rate / HTotal) / (line_rw_num + 1)
    ulDenominator = ScalerGlobalComputeDwordMulDiv(((DWORD)usHActive * usBitRate10x), ulPixClk_KHz, usHTotal) / 1000 / 10;
    ulTValue = ScalerGlobalComputeDwordMulDiv(((DWORD)ulLineTotalLen * 64 * ulMPll_MHz), ucTimeThdPercent, ulDenominator) / (usLineRWNum + 1) / 100;

    pstInfo->ulTimeThd = ulTValue; // Reg = ulTValue/16
}
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get FRC Status for Advanced HDR10
// Input Value  : None
// Output Value : EnumAdvancedHDR10FRCStatus
//--------------------------------------------------
EnumAdvancedHDR10FRCStatus ScalerFRCGetAdvancedHDR10FRCStatus(void)
{
    switch(GET_MEMORY_CONFIG_SELECT())
    {
        case  _MN_FRAME_SYNC_MEMORY:
        case  _FREE_RUN_NO_INPUT:
        case  _FREE_RUN_MEMORY:
            if(GET_PAGED_BIT(_FRC_CH0_PAGE, P46_04_M_CAP_CTRL_2, _BIT0) == 0x00)
            {
                return _ADVANCED_HDR10_IN_SLOW;
            }
            else
            {
                return _ADVANCED_HDR10_IN_FAST;
            }

        case  _FRAME_SYNC_LINE_BUFFER:
        case  _FRAME_SYNC_MEMORY:
        default:
            return _ADVANCED_HDR10_FRAME_SYNC;
    }
}
#endif

#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
//--------------------------------------------------
// Description  : Set initail boundary for gen IV rotation
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerFRCSetInitialBoundaryforRotation(void)
{
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH());

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            // Set Up limit , Rotation start from _MEMORY_BOTTOM_ADDRESS, so up limit = _MEMORY_BOTTOM_ADDRESS + 1
            SET_PAGED_BIT(enumPageSelect, P5_10_CAP_M1_BOUNDARY_ADDR2_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
            SET_PAGED_BYTE(enumPageSelect, P5_11_CAP_M1_BOUNDARY_ADDR2_H, 0xFF);
            SET_PAGED_BYTE(enumPageSelect, P5_12_CAP_M1_BOUNDARY_ADDR2_M, 0xFF);
            SET_PAGED_BYTE(enumPageSelect, P5_13_CAP_M1_BOUNDARY_ADDR2_L, 0xFE);
        }
    }

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            // Set Up limit , Rotation start from _MEMORY_BOTTOM_ADDRESS, so up limit = _MEMORY_BOTTOM_ADDRESS + 1
            SET_PAGED_BIT(enumPageSelect, P5_90_DISP_M1_BOUNDARY_ADDR2_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
            SET_PAGED_BYTE(enumPageSelect, P5_91_DISP_M1_BOUNDARY_ADDR2_H, 0xFF);
            SET_PAGED_BYTE(enumPageSelect, P5_92_DISP_M1_BOUNDARY_ADDR2_M, 0xFF);
            SET_PAGED_BYTE(enumPageSelect, P5_93_DISP_M1_BOUNDARY_ADDR2_L, 0xFE);
        }
    }
}
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : According Display mode decide 2P frame sync enable
// Input Value  : Display mode
// Output Value : _ENABLE: 2P frame sync mode
//--------------------------------------------------
bit ScalerFRC2PFrameSyncEnable(EnumDisplayMode enumDisplayMode)
{
    enumDisplayMode = enumDisplayMode;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(enumDisplayMode == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        return _ENABLE;
    }
#endif

#if(_PIP_FRAME_SYNC_SUPPORT == _ON)
    if(enumDisplayMode == _DISPLAY_MODE_2P_PIP)
    {
        return _ENABLE;
    }
#endif
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
#if(_PBP_LR_FRAME_SYNC_SUPPORT == _ON)
    if((enumDisplayMode == _DISPLAY_MODE_2P_PBP_LR_EQUAL) || (enumDisplayMode == _DISPLAY_MODE_2P_PBP_LR_R_LARGE) || (enumDisplayMode == _DISPLAY_MODE_2P_PBP_LR_L_LARGE))
    {
        return _ENABLE;
    }
#endif
#endif

    return _DISABLE;
}

//--------------------------------------------------
// Description  : 2P Frame Sync Mode, Frame sync Region Reset, if(GET_2P_FRAME_SYNC_MAIN() == _TRUE) --> reset main
// Input Value  : None
// Output Value : _TRUE: Bypass, e.g. aspect ratio case
//--------------------------------------------------
bit ScalerFRC2PFrameSyncBypassFrameSyncRegion(void)
{
    if((ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE) &&
       (GET_FORCE_DISPLAY_1P_MODE() == _TRUE))
    {
        // 2P frame sync display region do aspect ratio
        if(((GET_2P_FRAME_SYNC_MAIN() == _TRUE) && (GET_MTP_MEMORY_SELECT() == _MAIN_DISPLAY_SETTING_SUB_READY)) ||
           ((GET_2P_FRAME_SYNC_MAIN() == _FALSE) && (GET_MTP_MEMORY_SELECT() == _SUB_DISPLAY_SETTING_MAIN_READY)))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : 2P Frame Sync Mode, Frame sync region is ready, Non frame sync region display setting need to bypass some process
// Input Value  : None
// Output Value : _TRUE: Bypass
//--------------------------------------------------
bit ScalerFRC2PFrameSyncBypassNonFrameSyncRegion(void)
{
    if((ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE) &&
       (GET_FORCE_DISPLAY_1P_MODE() == _FALSE))
    {
        // Frame sync region is ready, free run region display setting need to bypass some process
        if(((GET_2P_FRAME_SYNC_MAIN() == _TRUE) && (GET_MTP_MEMORY_SELECT() == _SUB_DISPLAY_SETTING_MAIN_READY)) ||
           ((GET_2P_FRAME_SYNC_MAIN() == _FALSE) && (GET_MTP_MEMORY_SELECT() == _MAIN_DISPLAY_SETTING_SUB_READY)))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Auto Block Toggle Enable
// Input Value  : None
// Output Value : True, False
//--------------------------------------------------
bit ScalerFRCGetAutoBlkToggleEn(void)
{
    return _FALSE;
    // return (ScalerGetBit(P5_4B_CAP_M1_MN, _BIT5) == _BIT5); // RL6829 & RL6952 not support AUTO_3BLOCK_TOGGLE => mark
}

//--------------------------------------------------
// Description  : Set display adderss for auto block toggle
// Input Value  : ulBlockStep --> block step(single frame input and display)
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDisplayAutoBlkToggle(void)
{
    BYTE ucIndex = 0;
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH());

    for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, _FRC_R_1ST_BLOCK_STA_ADDR);
            ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, _FRC_R_2ND_BLOCK_STA_ADDR);
            ScalerFRCSetDispAddress(enumPageSelect, _FRC_3RD_BLOCK, _FRC_R_3RD_BLOCK_STA_ADDR);
        }
    }
}

//--------------------------------------------------
// Description  : Set display adderss for auto block toggle
// Input Value  : En: enable / disable
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDisplayAutoBlkToggleEnable(bit bEn)
{
    bEn = bEn;

/*  RL6829 & RL6952 not support AUTO_3BLOCK_TOGGLE => mark
    // Enable M:N HW auto toggle's double buffer
    ScalerSetBit(P5_4B_CAP_M1_MN, ~_BIT1, _BIT1);

    if(bEn == _ENABLE)
    {
        ScalerSetBit(P5_4B_CAP_M1_MN, ~_BIT5, _BIT5);

        // Input Hardware auto toggle address enable
        ScalerSetBit(P5_4B_CAP_M1_MN, ~_BIT0, _BIT0);

        // Display Hardware auto toggle among address enable
        ScalerSetBit(P5_E4_DISP_M1_MN_TOG_EN, ~_BIT3, _BIT3);
    }
    else
    {
        ScalerSetBit(P5_4B_CAP_M1_MN, ~_BIT5, 0x00);

        // Input Hardware auto toggle address disable
        ScalerSetBit(P5_4B_CAP_M1_MN, ~_BIT0, 0x00);

        // Display Hardware auto toggle among address disable
        ScalerSetBit(P5_E4_DISP_M1_MN_TOG_EN, ~_BIT3, 0x00);
    }

    // Hardware auto toggle M:N double buffer ready
    ScalerSetBit(P5_4B_CAP_M1_MN, ~_BIT2, _BIT2);

    // FRC_DISP_LOCAL_DB_APPLY(GET_FRC_PAGE_SELECT(ucIndex));

    // Wait dobule buffer
    ScalerTimerPollingFlagProc(_M_N_AUTO_BLK_TOGGLE_STABLE_TIME, P5_4B_CAP_M1_MN, _BIT2, 0);
*/
}

//--------------------------------------------------
// Description  : Set auto block toggle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetHWAutoBlockToggle(void)
{
    StructMemoryMNTracking stMNTracking = {0};

    ScalerMemoryGetMNRatio(&stMNTracking, GET_MEMORY_DVF_SELECT());


/*  RL6829 & RL6952 not support AUTO_3BLOCK_TOGGLE => mark
    // IVS to DVS shift value for hardware auto toggle among three initial read address
    // Set Shift = 2 _3_IVF, _2_5_IVF
    ScalerSetBit(P5_E3_DISP_M1_MN_TOG_SHIFT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((GET_MEMORY_DVF_SELECT() == _3_IVF) ? 2 : 0)); // _2_5_IVF: 0

    // Multiple of hardware auto toggle among three initial read address, it is (N/M - 1)
    PDATA_WORD(0) = ucN / ucM - 1;

    ScalerSetBit(P5_E3_DISP_M1_MN_TOG_SHIFT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (PDATA_WORD(0) << 4));

    // Remain of hardware auto toggle among three initial read address, and it is (N%M)/N * 2^10.(11bit in total)
    PDATA_WORD(0) = ((ucN % ucM) << 10) / ucN;
    PDATA_WORD(0) += 1;

    ScalerSetBit(P5_E4_DISP_M1_MN_TOG_EN, ~(_BIT2 | _BIT1 | _BIT0), (HIBYTE(PDATA_WORD(0)) & 0xFF));
    ScalerSetByte(P5_E5_DISP_M1_MN_TOG_REM, (LOBYTE(PDATA_WORD(0)) & 0xFF));
*/
}

//--------------------------------------------------
// Description  : Set Input adderss for auto block toggle
// Input Value  : ulBlockStep --> block step(single frame input and display)
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetInputAutoBlkToggle(void)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_1ST_BLOCK, _FRC_R_2ND_BLOCK_STA_ADDR);
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_2ND_BLOCK, _FRC_R_3RD_BLOCK_STA_ADDR);
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_3RD_BLOCK, _FRC_R_1ST_BLOCK_STA_ADDR);
        }
    }
}
#endif // End of #if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : FRC 4P/ 3P Skew/ PBP_TB, Botten Display Need to Sync Top Display
// Input Value  : Input Data Path Sync of Top
// Output Value : none
//--------------------------------------------------
void ScalerFRCSetInitialRegValue(EnumInputDataPath enumFRCSyncDataPath)
{
    BYTE ucIndex = 0;
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;

    BYTE ucLen = ScalerFRCGetAccessLength(_FRC_WRITE_LENGTH);
    WORD usHorSize = 200;
    WORD usVerSize = 200; // 20X20 MAY FAIL
    DWORD ulLinetotalpixel = ScalerFRCGetLineSumBit(usHorSize, GET_MEMORY_DATA_BIT(), GET_IMG_CMP_PARAM());
    DWORD ulTemp = ScalerMemoryCalculateNumberAndRemain(ulLinetotalpixel, ucLen, 1);

    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumFRCSyncDataPath);

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumFRCSyncDataPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            if(GET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == 0x00)
            {
                // ======== Capture ========

                // Set Water level
                SET_PAGED_BIT(enumPageSelect, P5_1D_CAP_M1_WATER_LEVEL_H, ~(_BIT0), ((((WORD)ucLen / 2) >> 8) & 0x01));
                SET_PAGED_BYTE(enumPageSelect, P5_1E_CAP_M1_WATER_LEVEL_L, (((WORD)ucLen / 2) & 0xFF));

                // Set Line Number
                SET_PAGED_BYTE(enumPageSelect, P5_21_CAP_M1_LINE_NUM_H, HIBYTE(usVerSize));
                SET_PAGED_BYTE(enumPageSelect, P5_22_CAP_M1_LINE_NUM_L, LOBYTE(usVerSize));

                // Set Number
                SET_PAGED_BYTE(enumPageSelect, P5_23_CAP_M1_WR_NUM_H, ((ulTemp >> 8) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_24_CAP_M1_WR_NUM_L, (ulTemp & 0xFF));

                // Set Length, Remain
                SET_PAGED_BYTE(enumPageSelect, P5_25_CAP_M1_WR_LEN, ucLen);
                SET_PAGED_BYTE(enumPageSelect, P5_26_CAP_M1_WR_REMAIN, ((ulTemp >> 16) & 0xFF));

                // Set Capture Line Step
                SET_PAGED_BIT(enumPageSelect, P5_19_CAP_M1_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                SET_PAGED_BYTE(enumPageSelect, P5_1A_CAP_M1_LINE_STEP_H, 0x00);
                SET_PAGED_BYTE(enumPageSelect, P5_1B_CAP_M1_LINE_STEP_M, 0x00);
                SET_PAGED_BYTE(enumPageSelect, P5_1C_CAP_M1_LINE_STEP_L, 0x20);
            }
        }
    }

    for(ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            if(GET_PAGED_BIT(enumPageSelect, P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == 0x00)
            {
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
                if(ScalerFRCGetBottomSettingStatusFromPage(GET_MDOMAIN_INPUT_DATA_PATH(), enumPageSelect) == _TRUE)
                {
                    // ======== Display ========

                    // Set Water Level, Display Water Level < FIFO Depth (512) - Length / 2
                    SET_PAGED_BIT(enumPageSelect, P5_F4_DISP_M1_WTLVL_BOT_H, ~(_BIT0), ((510 - ucLen / 2) >> 8));
                    SET_PAGED_BYTE(enumPageSelect, P5_F5_DISP_M1_WTLVL_BOT_L, (BYTE)((510 - ucLen / 2) & 0xFF));

                    // Set Pixel Number
                    SET_PAGED_BYTE(enumPageSelect, P5_F6_DISP_M1_PXL_NUM_BOT_H, HIBYTE(usHorSize));
                    SET_PAGED_BYTE(enumPageSelect, P5_F7_DISP_M1_PXL_NUM_BOT_L, LOBYTE(usHorSize));

                    // Set Line number
                    SET_PAGED_BYTE(enumPageSelect, P5_F8_DISP_M1_LINE_NUM_BOT_H, HIBYTE(usVerSize));
                    SET_PAGED_BYTE(enumPageSelect, P5_F9_DISP_M1_LINE_NUM_BOT_L, LOBYTE(usVerSize));

                    // Set Number
                    SET_PAGED_BYTE(enumPageSelect, P5_FB_DISP_M1_READ_NUM_BOT_H, ((ulTemp >> 8) & 0xFF));
                    SET_PAGED_BYTE(enumPageSelect, P5_FC_DISP_M1_READ_NUM_BOT_L, (ulTemp & 0xFF));

                    // Set Length, Remain
                    SET_PAGED_BYTE(enumPageSelect, P5_FD_DISP_M1_READ_BOT_LEN, ucLen);
                    SET_PAGED_BYTE(enumPageSelect, P5_FE_DISP_M1_READ_REMAIN_BOT, ((ulTemp >> 16) & 0xFF));

                    // Set Display Line Step
                    SET_PAGED_BIT(enumPageSelect, P5_F0_DISP_M1_LINE_STEP_BOT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    SET_PAGED_BYTE(enumPageSelect, P5_F1_DISP_M1_LINE_STEP_BOT_H, 0x00);
                    SET_PAGED_BYTE(enumPageSelect, P5_F2_DISP_M1_LINE_STEP_BOT_M, 0x00);
                    SET_PAGED_BYTE(enumPageSelect, P5_F3_DISP_M1_LINE_STEP_BOT_L, usHorSize);
                }
                else
#endif
                {
                    // Set Water Level, Display Water Level < FIFO Depth (512) - Length / 2
                    SET_PAGED_BIT(enumPageSelect, P5_A0_DISP_M1_WTLVL_TOP_H, ~(_BIT0), ((510 - ucLen / 2) >> 8));
                    SET_PAGED_BYTE(enumPageSelect, P5_A1_DISP_M1_WTLVL_TOP_L, (BYTE)((510 - ucLen / 2) & 0xFF));

                    // Set Pixel Number
                    SET_PAGED_BYTE(enumPageSelect, P5_A2_DISP_M1_PXL_NUM_TOP_H, HIBYTE(usHorSize));
                    SET_PAGED_BYTE(enumPageSelect, P5_A3_DISP_M1_PXL_NUM_TOP_L, LOBYTE(usHorSize));

                    // Set Line number
                    SET_PAGED_BYTE(enumPageSelect, P5_A4_DISP_M1_LINE_NUM_TOP_H, HIBYTE(usVerSize));
                    SET_PAGED_BYTE(enumPageSelect, P5_A5_DISP_M1_LINE_NUM_TOP_L, LOBYTE(usVerSize));

                    // Set Number
                    SET_PAGED_BYTE(enumPageSelect, P5_A8_DISP_M1_READ_NUM_TOP_H, ((ulTemp >> 8) & 0xFF));
                    SET_PAGED_BYTE(enumPageSelect, P5_A9_DISP_M1_READ_NUM_TOP_L, (ulTemp & 0xFF));

                    // Set Length, Remain
                    SET_PAGED_BYTE(enumPageSelect, P5_AA_DISP_M1_READ_TOP_LEN, ucLen);
                    SET_PAGED_BYTE(enumPageSelect, P5_AB_DISP_M1_READ_REMAIN_TOP, ((ulTemp >> 16) & 0xFF));

                    // Set Display Line Step
                    SET_PAGED_BIT(enumPageSelect, P5_99_DISP_M1_LINE_STEP_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    SET_PAGED_BYTE(enumPageSelect, P5_9A_DISP_M1_LINE_STEP_TOP_H, 0x00);
                    SET_PAGED_BYTE(enumPageSelect, P5_9B_DISP_M1_LINE_STEP_TOP_M, 0x00);
                    SET_PAGED_BYTE(enumPageSelect, P5_9C_DISP_M1_LINE_STEP_TOP_L, usHorSize);
                }
            }
        }
    }
}

#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
//--------------------------------------------------
// Description  : Modify frc cap/disp len, disp wtlvl under certain condition
// Input Value  : none
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerFRCModLenWtlvl(void)
{
#if(_OD_FUNCTION == _ON)
    StructMemoryBWUsageParam stMemBWParam;
    DWORD ulODUseBW = 0;
    BYTE ucODBit10x = GET_OD_BIT_RATE(ScalerODGetParamSet(((GET_OD_END_ADDRESS() - GET_OD_START_ADDRESS()) >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM), GET_MEMORY_REMAIN_BW()));

    ScalerMDomainGetMemBWParam(&stMemBWParam);
    ulODUseBW = ScalerMDomainODCalculateMemoryUseBW(ucODBit10x, &stMemBWParam);

    // when imc, 1:1/enlarge/reduce, od bw usage > frc bw usage, need to modify frc cap/disp len, disp wtlvl
    return ((GET_MDOMAIN_OUTPUT_VBHEIGHT() > GET_MDOMAIN_OUTPUT_VHEIGHT()) &&
            (GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE) &&
            (ulODUseBW > GET_MEMORY_BW(GET_MDOMAIN_INPUT_DATA_PATH())));
#else
    return _FALSE;
#endif
}
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
//--------------------------------------------------
// Description  : FRC Display Freeze Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayFreezeDisable(void)
{
    // if FRC disp freeze --> disable FRC disp freeze
    for(BYTE ucIndex = 0; ucIndex < (sizeof(tFRCChannel) / sizeof(tFRCChannel[0])); ucIndex ++)
    {
        EnumFRCChannelPageSelect enumFRCChPage = ScalerFRCGetChannelPage(tFRCChannel[ucIndex]);
        if(GET_PAGED_BIT(enumFRCChPage, P46_82_M_DISP_BLOCK_SEL, _BIT4) != 0x00)
        {
            SET_PAGED_BIT(enumFRCChPage, P46_82_M_DISP_BLOCK_SEL, ~(_BIT4), 0x00);
        }
    }
}
#endif // End of #if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
//--------------------------------------------------
// Description  : EOtoFB setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCEOtoFBControl(EnumInputDataPath enumInputPath, WORD usHwidth, bit bEn)
{
    if(bEn == _DISABLE)
    {
        if(((enumInputPath & _INPUT_PATH_M1) == _INPUT_PATH_M1) || ((enumInputPath & _INPUT_PATH_M2) == _INPUT_PATH_M2)) // 1P -> 4P
        {
            ScalerSetBit(P92_00_M1M2_EO2FB_CTRL, ~_BIT7, 0x00);
        }

#if(_HW_I_DOMAIN_S1_S2_PATH_SUPPORT == _ON)
        if(((enumInputPath & _INPUT_PATH_S1) == _INPUT_PATH_S1) || ((enumInputPath & _INPUT_PATH_S2) == _INPUT_PATH_S2))
        {
            ScalerSetBit(P92_10_S1S2_EO2FB_CTRL, ~_BIT7, 0x00);
        }
#endif

#if(_HW_I_DOMAIN_S3_S4_PATH_SUPPORT == _ON)
        if((enumInputPath & _INPUT_PATH_S3_S4) == _INPUT_PATH_S3_S4)
        {
            ScalerSetBit(P92_20_S3S4_EO2FB_CTRL, ~_BIT7, 0x00);
        }
#endif
    }
    else
    {
        if(ScalerFRCGetEOtoFBStatus() == _TRUE)
        {
            // Get Hsync width/ Hstart for 1 path, divided by 2 for down conversion
            WORD usHswidth = GET_MDOMAIN_INPUT_HSYNCWIDTH() / 2;
            WORD usHstart = GET_MDOMAIN_INPUT_HSTART() / 2;
            WORD usHtotal = GET_MDOMAIN_INPUT_HTOTAL();
            WORD usInputhwidth = GET_MDOMAIN_INPUT_HWIDTH();
            WORD usHbporch = (usHstart > usHswidth) ? (usHstart - usHswidth) : 0;
            WORD usHfporch = 0;
            bit bFBmode = _FALSE;

            bFBmode = bFBmode;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if((ScalerFmtCnvFBGetFBModeStatus() == _TRUE) && (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M1_M2_S1_S2))
            {
                usHswidth = ScalerGetByte(P31_67_FB_OUT_HSYNC_WIDTH);
                usHstart = ScalerGetByte(P31_68_FB_OUT_HSTART);
                usHtotal /= 2;
                usHwidth /= 2;
                usInputhwidth /= 2;
                usHbporch = usHstart - usHswidth;
                bFBmode = _TRUE;
            }
#endif

            usHfporch = usHtotal - usInputhwidth - usHbporch - usHswidth;

#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_0)
            usHfporch = ScalerScalingGetHFrontPorchAfterHSD(enumInputPath, usHwidth, usInputhwidth, usHfporch, bFBmode);
            usHbporch = ScalerScalingGetHBackPorchAfterHSD(enumInputPath, usHbporch, bFBmode);
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            switch(GET_ROT_TYPE())
            {
                case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
                case _ROT_HOR_MIRROR:
#endif

                    // Rotation will regen DEN to keep Hfporch size, need to recalculate Hbporch
                    usHbporch = usHtotal - usHwidth - usHfporch - usHswidth;

                    break;

                default:

                    break;
            }
#endif

            if((enumInputPath & _INPUT_PATH_M1_M2) == _INPUT_PATH_M1_M2)
            {
                ScalerSetBit(P92_01_M1M2_EO2FB_HTOTAL_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHtotal >> 8));
                ScalerSetByte(P92_02_M1M2_EO2FB_HTOTAL_L, LOBYTE(usHtotal));
                ScalerSetBit(P92_03_M1M2_EO2FB_HWIDTH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHwidth >> 8));
                ScalerSetByte(P92_04_M1M2_EO2FB_HWIDTH_L, LOBYTE(usHwidth));
                ScalerSetBit(P92_05_M1M2_EO2FB_HBPORCH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHbporch >> 8));
                ScalerSetByte(P92_06_M1M2_EO2FB_HBPORCH_L, LOBYTE(usHbporch));
                ScalerSetByte(P92_07_M1M2_EO2FB_HSWIDTH, usHswidth);
                ScalerSetBit(P92_08_M1M2_EO2FB_HFPORCH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHfporch >> 8));
                ScalerSetByte(P92_09_M1M2_EO2FB_HFPORCH_L, LOBYTE(usHfporch));

                ScalerSetBit(P92_00_M1M2_EO2FB_CTRL, ~_BIT7, _BIT7);
            }

#if(_HW_I_DOMAIN_S1_S2_PATH_SUPPORT == _ON)
            if((enumInputPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S1_S2)
            {
                ScalerSetBit(P92_11_S1S2_EO2FB_HTOTAL_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHtotal >> 8));
                ScalerSetByte(P92_12_S1S2_EO2FB_HTOTAL_L, LOBYTE(usHtotal));
                ScalerSetBit(P92_13_S1S2_EO2FB_HWIDTH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHwidth >> 8));
                ScalerSetByte(P92_14_S1S2_EO2FB_HWIDTH_L, LOBYTE(usHwidth));
                ScalerSetBit(P92_15_S1S2_EO2FB_HBPORCH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHbporch >> 8));
                ScalerSetByte(P92_16_S1S2_EO2FB_HBPORCH_L, LOBYTE(usHbporch));
                ScalerSetByte(P92_17_S1S2_EO2FB_HSWIDTH, usHswidth);
                ScalerSetBit(P92_18_S1S2_EO2FB_HFPORCH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHfporch >> 8));
                ScalerSetByte(P92_19_S1S2_EO2FB_HFPORCH_L, LOBYTE(usHfporch));

                ScalerSetBit(P92_10_S1S2_EO2FB_CTRL, ~_BIT7, _BIT7);
            }
#endif

#if(_HW_I_DOMAIN_S3_S4_PATH_SUPPORT == _ON)
            if((enumInputPath & _INPUT_PATH_S3_S4) == _INPUT_PATH_S3_S4)
            {
                ScalerSetBit(P92_21_S3S4_EO2FB_HTOTAL_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHtotal >> 8));
                ScalerSetByte(P92_22_S3S4_EO2FB_HTOTAL_L, LOBYTE(usHtotal));
                ScalerSetBit(P92_23_S3S4_EO2FB_HWIDTH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHwidth >> 8));
                ScalerSetByte(P92_24_S3S4_EO2FB_HWIDTH_L, LOBYTE(usHwidth));
                ScalerSetBit(P92_25_S3S4_EO2FB_HBPORCH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHbporch >> 8));
                ScalerSetByte(P92_26_S3S4_EO2FB_HBPORCH_L, LOBYTE(usHbporch));
                ScalerSetByte(P92_27_S3S4_EO2FB_HSWIDTH, usHswidth);
                ScalerSetBit(P92_28_S3S4_EO2FB_HFPORCH_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHfporch >> 8));
                ScalerSetByte(P92_29_S3S4_EO2FB_HFPORCH_L, LOBYTE(usHfporch));

                ScalerSetBit(P92_20_S3S4_EO2FB_CTRL, ~_BIT7, _BIT7);
            }
#endif
        }
    }
}

//--------------------------------------------------
// Description  : FBtoEO set enable
// Input Value  : bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerFRCFBtoEOControl(EnumInputDataPath enumInputPath, WORD usHwidth, bit bEn)
{
    BYTE ucEnable = 0;
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputPath);
    usHwidth = usHwidth;

    if(((enumMDispPath & _MDOMAIN_DISP_PATH_M1) == _MDOMAIN_DISP_PATH_M1) || ((enumMDispPath & _MDOMAIN_DISP_PATH_M2) == _MDOMAIN_DISP_PATH_M2)) // 1P -> 4P
    {

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
        if(ScalerFRCGetBottomSettingStatusFromInputDataPath(enumInputPath) == _TRUE)
        {
            ucEnable |= _BIT3;
        }
        else
#endif
        {
            ucEnable |= _BIT7;
        }
    }

    if(((enumMDispPath & _MDOMAIN_DISP_PATH_S1) == _MDOMAIN_DISP_PATH_S1) || ((enumMDispPath & _MDOMAIN_DISP_PATH_S2) == _MDOMAIN_DISP_PATH_S2))
    {
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
        if((ScalerFRCGetBottomSettingStatusFromInputDataPath(enumInputPath) == _TRUE) && ((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_TB) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_4P)))
        {
            ucEnable |= (_BIT2);
        }
        else
#endif
        {
            ucEnable |= (_BIT6);
        }
    }

    if((enumMDispPath & _MDOMAIN_DISP_PATH_S3_S4) == _MDOMAIN_DISP_PATH_S3_S4)
    {
        ucEnable |= (_BIT5);
    }

    if((enumMDispPath & _MDOMAIN_DISP_PATH_ALL) == _MDOMAIN_DISP_PATH_ALL) // for _INPUT_PATH_ALL _DISABLE
    {
        ucEnable |= (_BIT3 | _BIT2 | _BIT1);
    }

    if((bEn == _ENABLE) && (ScalerFRCGetFBtoEOStatus() == _TRUE))
    {
        ScalerSetBit(P92_30_FB2EO_CTRL_0, ~(ucEnable), ucEnable);

#if(_HW_FB2EO_HWIDTH_SETTING_TYPE == _FB2EO_HWIDTH_SETTING_GEN_1)
        if((enumMDispPath & _MDOMAIN_DISP_PATH_M1_M2) == _MDOMAIN_DISP_PATH_M1_M2)
        {
            ScalerSetByte(P92_37_M1M2_FB2EO_HWIDTH_H, (((HIBYTE(usHwidth) & 0x0F) << 4) | (HIBYTE(usHwidth) & 0x0F)));
            ScalerSetByte(P92_38_M1_FB2EO_HWIDTH_L, LOBYTE(usHwidth));
            ScalerSetByte(P92_39_M2_FB2EO_HWIDTH_L, LOBYTE(usHwidth));
        }
#endif
    }
    else
    {
        ScalerSetBit(P92_30_FB2EO_CTRL_0, ~(ucEnable), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : set frc fifo scaling size
// Input Value  : StructSDRAMDataInfo *pstFIFOSize
// Output Value : None
//--------------------------------------------------
void ScalerFRCUpdateFifoScalingSize(StructSDRAMDataInfo *pstFIFOSize)
{
#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) ||\
    (_COLOR_IP_3DDI == _ON) ||\
    (_TB_DISPLAY_MODE_SUPPORT == _ON))
    BYTE ucMDispPathCnt = (ScalerFRCGetMDispPathCount(ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH())));
#endif

    if(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) != _INPUT_PATH_1)
    {
        if(ScalerFRCGetEOtoFBStatus() == _TRUE)
        {
            pstFIFOSize->usInputHWidth /= ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH());
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
            if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE)
            {
                pstFIFOSize->usOutputHWidth /= ucMDispPathCnt;
            }
            else
#endif
            {
                pstFIFOSize->usOutputHWidth = pstFIFOSize->usInputHWidth;
#if(_HW_FB2EO_INDEPENDENT_OF_IMC_DEC == _TRUE)
                if(ScalerFRCGetFBtoEOStatus() == _TRUE)
                {
                    // for RL6952 case: fb2eo on + imc off
                    pstFIFOSize->usOutputVHeight = pstFIFOSize->usInputVHeight;
                }
                else
#endif
                {
                    // for RL6829 8k pbptb case: eo2fb on + imc off + fb2eo off
                    pstFIFOSize->usOutputVHeight = pstFIFOSize->usInputVHeight / 2;
                }
            }
        }
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        else if(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) == _INPUT_PATH_4)
        {
            pstFIFOSize->usInputHWidth = pstFIFOSize->usInputHWidth / 2;
            pstFIFOSize->usInputVHeight = pstFIFOSize->usInputVHeight / 2;
            pstFIFOSize->usOutputHWidth = pstFIFOSize->usOutputHWidth / 2;
            pstFIFOSize->usOutputVHeight = pstFIFOSize->usOutputVHeight / 2;
        }
#endif
        else
        {
            pstFIFOSize->usInputVHeight = pstFIFOSize->usInputVHeight / 2;
            pstFIFOSize->usOutputVHeight = pstFIFOSize->usOutputVHeight / 2;
        }
    }
    else
    {
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
        if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE)
        {
            pstFIFOSize->usOutputHWidth = pstFIFOSize->usInputHWidth / ucMDispPathCnt;
        }
        else
#endif
        {
#if(_COLOR_IP_3DDI == _ON)
            // only for eo mode, s2 3ddi
            if((GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON) && (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2))
            {
                pstFIFOSize->usOutputVHeight = pstFIFOSize->usInputVHeight / ucMDispPathCnt;
            }
            else
#endif
            {
#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
                if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
                {
                    pstFIFOSize->usOutputVHeight = pstFIFOSize->usInputVHeight / ucMDispPathCnt;
                }
                else
#endif
                {
                    pstFIFOSize->usOutputVHeight = pstFIFOSize->usInputVHeight;
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get Frame Tear Prevention status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetFrameTearPrevent(EnumInputDataPath enumInputDataPath)
{
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumInputDataPath);
    bit bft_prevent = GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM());

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
    if((GET_IMG_CMP_ENABLE(ScalerFRCImgCmpGetPara(ScalerRegionGetIndexFromInputDataPath(enumInputDataPath))) == _TRUE) && (GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE))
    {
        EnumInputDataPath enumSyncDataPath = ScalerFRCDispSynchronizeCheck(enumInputDataPath);

        // if any region of tb mode is input fast, need to enable ft prevention
        // disable ft prevention when both tb mode are input slow
        bft_prevent = ((enumSyncDataPath != _INPUT_PATH_NONE) && ((GET_MDOMAIN_FRC_STYLE(enumSyncDataPath) == _FRC_INPUT_FASTER) || (GET_MDOMAIN_FRC_STYLE(enumInputDataPath) == _FRC_INPUT_FASTER)));
    }
#endif

    for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            EnumFRCPageSelect enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

            if(bft_prevent == _TRUE)
            {
                SET_PAGED_BYTE(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, (_BIT6 | _FRC_FRAME_TEAR_PREVENT_LINE)); // margin = 2
            }
            else
            {
                SET_PAGED_BYTE(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, 0x00);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get EOtoFB status
// Input Value  : None
// Output Value : _TRUE, FALSE
//--------------------------------------------------
bit ScalerFRCGetEOtoFBStatus(void)
{
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _ENABLE)
        {
            return _TRUE;
        }

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
        // special without imc
        if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
        {
            return (GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_TB) ? _TRUE : ((ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()) == ScalerRegionGet2PMainPathRegion()) ? _TRUE : _FALSE);
        }
#endif
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Get FBtoEO status
// Input Value  : None
// Output Value : _TRUE, FALSE
//--------------------------------------------------
bit ScalerFRCGetFBtoEOStatus(void)
{
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        return (GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _ENABLE) ? _TRUE : _FALSE;
    }

#if(_COLOR_IP_3DDI == _ON)
    // only for eo mode, s2 3ddi
    if((GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON) && (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2))
    {
        return (GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _ENABLE) ? _TRUE : _FALSE;
    }
#endif

    // fb_4p
    return ((GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _ENABLE) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)) ? _TRUE : _FALSE;
}

//--------------------------------------------------
// Description  : Get tFRCRateCtrlParam Table Count
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
BYTE ScalerFRCGettFRCRateCtrlParamCnt(void)
{
    switch(g_stDisplayCustomizedData.structCustomizedMdomain.enumBWCustomeModeType)
    {
        case _BW_DEFAULT_TYPE:
        default:
            return (sizeof(tFRCRateCtrlParam) / sizeof(tFRCRateCtrlParam[0]));

#if(_BW_CUSTOME_MODE == _ENABLE)
        case _BW_FIX_ORIGINAL_COLOR_DEPTH_TYPE:
            return (sizeof(tFRCRateCtrlParamCustomeFixColorDepth) / sizeof(tFRCRateCtrlParamCustomeFixColorDepth[0]));

        case _BW_DECIDE_OD_OFF_FIRST_TYPE:
            return (sizeof(tFRCRateCtrlParamCustomeODoffFirst) / sizeof(tFRCRateCtrlParamCustomeODoffFirst[0]));
#endif
    }
}

//--------------------------------------------------
// Description  : Get BW decide Parameter From Index
// Input Value  : Index
// Output Value : EnumImgCmpParamIndex
//--------------------------------------------------
EnumImgCmpParamIndex ScalerFRCGetRcpImcCmpParamFromIndex(BYTE ucIndex)
{
    switch(g_stDisplayCustomizedData.structCustomizedMdomain.enumBWCustomeModeType)
    {
        case _BW_DEFAULT_TYPE:
        default:
            if(ucIndex < (sizeof(tFRCRateCtrlParam) / sizeof(tFRCRateCtrlParam[0])))
            {
                return tFRCRateCtrlParam[ucIndex].enumImgCmpParamIndex;
            }
            break;

#if(_BW_CUSTOME_MODE == _ENABLE)
        case _BW_FIX_ORIGINAL_COLOR_DEPTH_TYPE:
            if(ucIndex < (sizeof(tFRCRateCtrlParamCustomeFixColorDepth) / sizeof(tFRCRateCtrlParamCustomeFixColorDepth[0])))
            {
                return tFRCRateCtrlParamCustomeFixColorDepth[ucIndex].enumImgCmpParamIndex;
            }
            break;

        case _BW_DECIDE_OD_OFF_FIRST_TYPE:
            if(ucIndex < (sizeof(tFRCRateCtrlParamCustomeODoffFirst) / sizeof(tFRCRateCtrlParamCustomeODoffFirst[0])))
            {
                return tFRCRateCtrlParamCustomeODoffFirst[ucIndex].enumImgCmpParamIndex;
            }
            break;
#endif
    }

    return _IMG_CMP_PARAM_OFF;
}

//--------------------------------------------------
// Description  : Get Fifo Color Depth From Index
// Input Value  : Index
// Output Value : Color Depth
//--------------------------------------------------
BYTE ScalerFRCGetRcpFifoColorDepthFromIndex(BYTE ucIndex)
{
    switch(g_stDisplayCustomizedData.structCustomizedMdomain.enumBWCustomeModeType)
    {
        case _BW_DEFAULT_TYPE:
        default:
            if(ucIndex < (sizeof(tFRCRateCtrlParam) / sizeof(tFRCRateCtrlParam[0])))
            {
                return tFRCRateCtrlParam[ucIndex].b5FifoColorDepth;
            }
            break;

#if(_BW_CUSTOME_MODE == _ENABLE)
        case _BW_FIX_ORIGINAL_COLOR_DEPTH_TYPE:
            if(ucIndex < (sizeof(tFRCRateCtrlParamCustomeFixColorDepth) / sizeof(tFRCRateCtrlParamCustomeFixColorDepth[0])))
            {
                return tFRCRateCtrlParamCustomeFixColorDepth[ucIndex].b5FifoColorDepth;
            }
            break;

        case _BW_DECIDE_OD_OFF_FIRST_TYPE:
            if(ucIndex < (sizeof(tFRCRateCtrlParamCustomeODoffFirst) / sizeof(tFRCRateCtrlParamCustomeODoffFirst[0])))
            {
                return tFRCRateCtrlParamCustomeODoffFirst[ucIndex].b5FifoColorDepth;
            }
            break;
#endif
    }

    return _COLOR_DEPTH_8_BITS;
}

//--------------------------------------------------
// Description  : Get H Scaling Down Enable From Index
// Input Value  : Index
// Output Value : HSD en
//--------------------------------------------------
bit ScalerFRCGetRcpHsdEnFromIndex(BYTE ucIndex)
{
    switch(g_stDisplayCustomizedData.structCustomizedMdomain.enumBWCustomeModeType)
    {
        case _BW_DEFAULT_TYPE:
        default:
            if(ucIndex < (sizeof(tFRCRateCtrlParam) / sizeof(tFRCRateCtrlParam[0])))
            {
                return (tFRCRateCtrlParam[ucIndex].b1AllowHSD == _ON);
            }
            break;

#if(_BW_CUSTOME_MODE == _ENABLE)
        case _BW_FIX_ORIGINAL_COLOR_DEPTH_TYPE:
            if(ucIndex < (sizeof(tFRCRateCtrlParamCustomeFixColorDepth) / sizeof(tFRCRateCtrlParamCustomeFixColorDepth[0])))
            {
                return (tFRCRateCtrlParamCustomeFixColorDepth[ucIndex].b1AllowHSD == _ON);
            }
            break;

        case _BW_DECIDE_OD_OFF_FIRST_TYPE:
            if(ucIndex < (sizeof(tFRCRateCtrlParamCustomeODoffFirst) / sizeof(tFRCRateCtrlParamCustomeODoffFirst[0])))
            {
                return (tFRCRateCtrlParamCustomeODoffFirst[ucIndex].b1AllowHSD == _ON);
            }
            break;
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get OD Parameter From Index
// Input Value  : Index
// Output Value : EnumODParamIndex
//--------------------------------------------------
EnumODParamIndex ScalerFRCGetRcpODParamFromIndex(BYTE ucIndex)
{
    switch(g_stDisplayCustomizedData.structCustomizedMdomain.enumBWCustomeModeType)
    {
        case _BW_DEFAULT_TYPE:
        default:
            if(ucIndex < (sizeof(tFRCRateCtrlParam) / sizeof(tFRCRateCtrlParam[0])))
            {
                return tFRCRateCtrlParam[ucIndex].enumExpectODParamIndex;
            }
            break;

#if(_BW_CUSTOME_MODE == _ENABLE)
        case _BW_FIX_ORIGINAL_COLOR_DEPTH_TYPE:
            if(ucIndex < (sizeof(tFRCRateCtrlParamCustomeFixColorDepth) / sizeof(tFRCRateCtrlParamCustomeFixColorDepth[0])))
            {
                return tFRCRateCtrlParamCustomeFixColorDepth[ucIndex].enumExpectODParamIndex;
            }
            break;

        case _BW_DECIDE_OD_OFF_FIRST_TYPE:
            if(ucIndex < (sizeof(tFRCRateCtrlParamCustomeODoffFirst) / sizeof(tFRCRateCtrlParamCustomeODoffFirst[0])))
            {
                return tFRCRateCtrlParamCustomeODoffFirst[ucIndex].enumExpectODParamIndex;
            }
            break;
#endif
    }

    return _OD_PARAM_OFF;
}

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set FRC Display address
// Input Value  : usSelectedPage: FRC page, ucBlock: Capture Block, ulCapAddress
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDispBotAddress(WORD usSelectedPage, EnumFRCBlock enumBlock, DWORD ulDispAddress)
{
    switch(enumBlock)
    {
        case _FRC_1ST_BLOCK:
        default:

            SET_PAGED_BIT(usSelectedPage, P5_E0_DISP_M1_BLK_ADDR_1ST_BOT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulDispAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_E1_DISP_M1_BLK_ADDR_1ST_BOT_H, ((ulDispAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_E2_DISP_M1_BLK_ADDR_1ST_BOT_M, ((ulDispAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_E3_DISP_M1_BLK_ADDR_1ST_BOT_L, (ulDispAddress & 0xFE));
            break;

        case _FRC_2ND_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_E4_DISP_M1_BLK_ADDR_2ND_BOT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulDispAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_E5_DISP_M1_BLK_ADDR_2ND_BOT_H, ((ulDispAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_E6_DISP_M1_BLK_ADDR_2ND_BOT_M, ((ulDispAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_E7_DISP_M1_BLK_ADDR_2ND_BOT_L, (ulDispAddress & 0xFE));
            break;

        case _FRC_3RD_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_E8_DISP_M1_BLK_ADDR_3RD_BOT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulDispAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_E9_DISP_M1_BLK_ADDR_3RD_BOT_H, ((ulDispAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_EA_DISP_M1_BLK_ADDR_3RD_BOT_M, ((ulDispAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_EB_DISP_M1_BLK_ADDR_3RD_BOT_L, (ulDispAddress & 0xFE));
            break;

        case _FRC_4TH_BLOCK:

            SET_PAGED_BIT(usSelectedPage, P5_EC_DISP_M1_BLK_ADDR_4TH_BOT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulDispAddress >> 24) & 0x0F));
            SET_PAGED_BYTE(usSelectedPage, P5_ED_DISP_M1_BLK_ADDR_4TH_BOT_H, ((ulDispAddress >> 16) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_EE_DISP_M1_BLK_ADDR_4TH_BOT_M, ((ulDispAddress >> 8) & 0xFF));
            SET_PAGED_BYTE(usSelectedPage, P5_EF_DISP_M1_BLK_ADDR_4TH_BOT_L, (ulDispAddress & 0xFE));
            break;
    }
}

//--------------------------------------------------
// Description  : Set FRC Display Bottom linestep
// Input Value  : usSelectedPage: FRC page, ulLinestep
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDispBotLinestep(WORD usSelectedPage, DWORD ulLinestep)
{
    SET_PAGED_BIT(usSelectedPage, P5_F0_DISP_M1_LINE_STEP_BOT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulLinestep >> 24) & 0x0F));
    SET_PAGED_BYTE(usSelectedPage, P5_F1_DISP_M1_LINE_STEP_BOT_H, ((ulLinestep >> 16) & 0xFF));
    SET_PAGED_BYTE(usSelectedPage, P5_F2_DISP_M1_LINE_STEP_BOT_M, ((ulLinestep >> 8) & 0xFF));
    SET_PAGED_BYTE(usSelectedPage, P5_F3_DISP_M1_LINE_STEP_BOT_L, (ulLinestep & 0xFF));
}

//--------------------------------------------------
// Description  : Set FRC Top Bottom mode linestep, display address
// Input Value  : EnumFRCChannel enumFRCCh
// Output Value : None
//--------------------------------------------------
void ScalerFRCTopBottomModeDisplaySetting(EnumFRCChannel enumFRCCh)
{
    BYTE ucIMCaddress_factor = 1;
    BYTE ucIMClinestep_factor = 2;
    DWORD ulLinestep = 0;
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    // Set Disp FIFO output: D-Domain/PQC
    if(GET_IMG_CMP_ENABLE(GET_IMG_CMP_PARAM()) == _TRUE)
    {
        ucIMCaddress_factor = 2;
        ucIMClinestep_factor = 1;
    }
#endif
    switch(enumFRCCh)
    {
        case _FRC_CH0:
        default:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_4P:
                default:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_MAIN1_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_MAIN1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispTopLinestep(_FRC_MAIN2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }
                    break;

                case _DISPLAY_MODE_3P_SKEW_T:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_MAIN1_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_MAIN1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispTopLinestep(_FRC_MAIN2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }

                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_MAIN2_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }
                    break;

                case _DISPLAY_MODE_3P_SKEW_B:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_MAIN1_PAGE);
                    ScalerFRCSetDispBotLinestep(_FRC_MAIN1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispBotLinestep(_FRC_MAIN2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }

                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_MAIN2_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }
                    break;

                case _DISPLAY_MODE_2P_PBP_TB:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_MAIN1_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_MAIN1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispTopLinestep(_FRC_MAIN2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }

                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_MAIN2_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }
                    break;
            }
            break;

        case _FRC_CH1:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_4P:
                default:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_MAIN2_PAGE);
                    ScalerFRCSetDispBotLinestep(_FRC_MAIN1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispBotLinestep(_FRC_MAIN2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }
                    break;

                case _DISPLAY_MODE_3P_SKEW_T:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB1_PAGE);
                    ScalerFRCSetDispBotLinestep(_FRC_MAIN1_PAGE, ulLinestep);

                    ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK));

                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB2_PAGE);
                    ScalerFRCSetDispBotLinestep(_FRC_MAIN2_PAGE, ulLinestep);

                    ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK));
                    }
                    break;

                case _DISPLAY_MODE_3P_SKEW_B:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB1_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_MAIN1_PAGE, ulLinestep);

                    ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK));

                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB2_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_MAIN2_PAGE, ulLinestep);

                    ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK));
                    }
                    break;

                case _DISPLAY_MODE_2P_PBP_TB:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB1_PAGE);
                    ScalerFRCSetDispBotLinestep(_FRC_MAIN1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispBotLinestep(_FRC_MAIN2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispBotAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispBotAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }

                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB2_PAGE);
                    ScalerFRCSetDispBotLinestep(_FRC_SUB1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispBotLinestep(_FRC_SUB2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispBotAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispBotAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispBotAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispBotAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }
                    break;
            }
            break;

        case _FRC_CH2:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_4P:
                default:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB1_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }
                    break;

                case _DISPLAY_MODE_3P_SKEW_T:
                case _DISPLAY_MODE_3P_SKEW_B:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB3_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB3_PAGE, ulLinestep);

                    ScalerFRCSetDispAddress(_FRC_SUB3_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB3_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB3_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB3_PAGE, _FRC_2ND_BLOCK));

                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB4_PAGE);
                    ScalerFRCSetDispTopLinestep(_FRC_SUB4_PAGE, ulLinestep);

                    ScalerFRCSetDispAddress(_FRC_SUB4_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB4_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(_FRC_SUB4_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB4_PAGE, _FRC_2ND_BLOCK));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispAddress(_FRC_SUB3_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB3_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispAddress(_FRC_SUB4_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB4_PAGE, _FRC_3RD_BLOCK));
                    }
                    break;
            }
            break;

        case _FRC_CH3:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_4P:
                default:
                    ulLinestep = ScalerFRCGetCapLinestep(_FRC_SUB2_PAGE);
                    ScalerFRCSetDispBotLinestep(_FRC_SUB1_PAGE, ulLinestep * ucIMClinestep_factor);
                    ScalerFRCSetDispBotLinestep(_FRC_SUB2_PAGE, ulLinestep * ucIMClinestep_factor);

                    ScalerFRCSetDispBotAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_SUB1_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispBotAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    ScalerFRCSetDispBotAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_2ND_BLOCK) + (ulLinestep / ucIMCaddress_factor));

                    if(ScalerFRCGetTBMode2BlkSupport() == _OFF)
                    {
                        ScalerFRCSetDispBotAddress(_FRC_SUB1_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK));
                        ScalerFRCSetDispBotAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_3RD_BLOCK) + (ulLinestep / ucIMCaddress_factor));
                    }
                    break;
            }
            break;
    }
}

//--------------------------------------------------
// Description  : Set FRC Top Bottom mode linestep, display address
// Input Value  : EnumFRCChannel enumFRCCh
// Output Value : None
//--------------------------------------------------
bit ScalerFRCGetBottomSettingStatusFromPage(EnumInputDataPath enumInputPath, EnumFRCPageSelect enumPageSelect)
{
    enumPageSelect = enumPageSelect;
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        switch(GET_DISPLAY_MODE())
        {
            case _DISPLAY_MODE_2P_PBP_TB:
            case _DISPLAY_MODE_3P_SKEW_T:
                return (enumInputPath == _INPUT_PATH_S1_S2) ? _TRUE : _FALSE;

            case _DISPLAY_MODE_3P_SKEW_B:
                return (enumInputPath == _INPUT_PATH_M1_M2) ? (((enumPageSelect == _FRC_MAIN1_PAGE) || (enumPageSelect == _FRC_MAIN2_PAGE)) ? _TRUE : _FALSE) : _FALSE;

            case _DISPLAY_MODE_4P:
                return ((enumInputPath == _INPUT_PATH_M2) || (enumInputPath == _INPUT_PATH_S2)) ? _TRUE : _FALSE;
            default:
                return _FALSE;
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Set FRC Top Bottom mode linestep, display address
// Input Value  : EnumFRCChannel enumFRCCh
// Output Value : None
//--------------------------------------------------
bit ScalerFRCGetBottomSettingStatusFromInputDataPath(EnumInputDataPath enumInputPath)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        switch(GET_DISPLAY_MODE())
        {
            case _DISPLAY_MODE_2P_PBP_TB:
            case _DISPLAY_MODE_3P_SKEW_T:
                return (enumInputPath == _INPUT_PATH_S1_S2) ? _TRUE : _FALSE;

            case _DISPLAY_MODE_3P_SKEW_B:
                return (enumInputPath == _INPUT_PATH_M1_M2) ? _TRUE : _FALSE;

            case _DISPLAY_MODE_4P:
                return ((enumInputPath == _INPUT_PATH_M2) || (enumInputPath == _INPUT_PATH_S2)) ? _TRUE : _FALSE;
            default:
                return _FALSE;
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Reset Mdm Parameter
// Input Value  : EnumInputDataPath enumInputDataPath
// Output Value : none
//--------------------------------------------------
void ScalerFRCResetFBTBDisplayModeParam(EnumInputDataPath enumInputDataPath)
{
    SET_MDOMAIN_FRC_STYLE(enumInputDataPath, _FRC_INPUT_SLOWER);
    ScalerFRCSetFrameTearPrevent(enumInputDataPath);
}
#endif  // End of #if(_TB_DISPLAY_MODE_SUPPORT == _ON)
#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Disable FRC Capture Overflow Watchdog Enable
// Input Value  : EnumInputDataPath enumInputDataPath
// Output Value : none
//--------------------------------------------------
void ScalerFRCCapFifoOvflWDDisable(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(enumInputDataPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), P5_43_CAP_M1_4CH_CTRL1, ~(_BIT0), 0x00);
        }
    }
}

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Eagle Sight Low Latency
// Input Value  : _FRC_LATENCY_SMALL = low latency on, set _REGION_INDEX_0's ivs2dvs delay
//                _FRC_LATENCY_MEDIUM = low latency on, set _REGION_INDEX_1's ivs2dvs delay
//                _FRC_LATENCY_LARGE = low latency off
// Output Value : None
//--------------------------------------------------
void ScalerFRCEagleSightLowLatency(EnumFRCLatency enumFRCLatency)
{
    if((enumFRCLatency == _FRC_LATENCY_MEDIUM) || (enumFRCLatency == _FRC_LATENCY_SMALL))
    {
#if(_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
        EnumRegionIndex enumRegionIndex = (enumFRCLatency == _FRC_LATENCY_MEDIUM) ? _REGION_INDEX_1 : _REGION_INDEX_0;
        EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));

        if((enumFRCLatency == _FRC_LATENCY_MEDIUM) && (GET_MDOMAIN_IVS2DVSDELAY(_REGION_INDEX_1) < GET_MDOMAIN_IVS2DVSDELAY(_REGION_INDEX_0)))
        {
            enumRegionIndex = _REGION_INDEX_0;
        }

        ScalerFRCSetFSIVS2DVSDelayWhenActiveState(GET_MDOMAIN_IVS2DVSDELAY(enumRegionIndex), &g_stMDomainFSActiveInfo.stMDomainFSActiveInputData, &g_stMDomainFSActiveInfo.stMDomainFSActiveOutputData);
        ScalerFRCSetChannelBlkNum(enumChannelSel, (_FRC_CAP | _FRC_DISP), _MEMORY_1_FRAME_BUFFER);
#else
        // FRC is double frame buffer mode
        if(ScalerFRCGetChannelFRCCapBlkNum(_FRC_CH0_PAGE) == _FRC_CH_2_BLK)
        {
            DebugMessageScaler("Eagle Sight switch to FRC 1 frame buffer", 0);

            // Set Channel_0 capture / display 1 frame buffer mode
            ScalerFRCSetChannelBlkNum(_FRC_CH0_PAGE, (_FRC_CAP | _FRC_DISP), _MEMORY_1_FRAME_BUFFER);

            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

            // Wait for FRC cap block index is 1
            if(ScalerGetBit(P5_2A_CAP_M1_STATUS, (_BIT7 | _BIT6)) == 0x00)
            {
                ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
            }
        }
#endif
    }
    else // _FRC_LATENCY_LARGE
    {
        // FRC is single frame buffer mode
        if(ScalerFRCGetChannelFRCCapBlkNum(_FRC_CH0_PAGE) == _FRC_CH_1_BLK)
        {
            DebugMessageScaler("Eagle Sight switch to FRC 2 frame buffer", 0);

            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0)));

            // Set Channel_0 capture 2 frame buffer mode
            ScalerFRCSetChannelBlkNum(_FRC_CH0_PAGE, _FRC_CAP, _MEMORY_2_FRAME_BUFFER);

            // Enable FRC cap block free
            SET_PAGED_BIT(_FRC_CH0_PAGE, P46_03_M_CAP_BLOCK_SEL, ~(_BIT3), _BIT3);

            // Wait for FRC cap write 2 frame buffer data
            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0)));
            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0)));
            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0)));

            // Disable FRC cap block free
            SET_PAGED_BIT(_FRC_CH0_PAGE, P46_03_M_CAP_BLOCK_SEL, ~(_BIT3), 0x00);

            // Set Channel_0 display 2 buffer mode
            ScalerFRCSetChannelBlkNum(_FRC_CH0_PAGE, _FRC_DISP, _MEMORY_2_FRAME_BUFFER);
        }
    }
}
#endif // End of #if(_EAGLE_SIGHT_SUPPORT == _ON)

#if ((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_HDMI21_ALLM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Adjust Latency For FRC
// Input Value  : enumInputPort, usDelayMax, usIVS2DVSDelay
// Output Value : usIVS2DVSDelay
//--------------------------------------------------
WORD ScalerFRCLatencyControl(EnumInputPort enumInputPort, EnumSourceType enumSourceType, WORD usDelayMax, WORD usIVS2DVSDelay)
{
    enumInputPort = enumInputPort;
    enumSourceType = enumSourceType;
    usDelayMax = usDelayMax;
    usIVS2DVSDelay = usIVS2DVSDelay;

#if(_HDMI21_ALLM_SUPPORT == _ON)

    SET_FRC_ALLM_ON_STATUS();

    if ((enumSourceType == _SOURCE_HDMI) &&
        (ScalerTmdsMacRxGetHdmi21AllmStatus(enumInputPort) == _FALSE))
    {
        // Set allm off latency
        PDATA_WORD(1) = ((DWORD)usDelayMax - usIVS2DVSDelay) * GET_FRC_ALLM_LATENCY_RATIO() / 100;
        usIVS2DVSDelay += PDATA_WORD(1);
        CLR_FRC_ALLM_ON_STATUS();
    }
    else
#endif
    {
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
        PDATA_WORD(1) = ((DWORD)usDelayMax - usIVS2DVSDelay) * GET_DISP_LATENCY_RATIO() / 100;
        usIVS2DVSDelay += PDATA_WORD(1);

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        if(GET_ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT() == _ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT)
        {
            if(GET_DISP_LATENCY_RATIO() == 100)
            {
                SET_ADVANCED_HDR10_ENLARGE_DELAY_STATUS(_ADVANCED_HDR10_ENLARGE_DELAY_ON);
            }
        }
#endif
#elif(_ADVANCED_HDR10_SUPPORT == _ON)
#if(_FREESYNC_SUPPORT == _ON)
        if(ScalerDrrGetType(enumInputPort) != _DRR_FREESYNC_TYPE)
#endif
        {
            if(GET_ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT() == _ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT)
            {
                SET_ADVANCED_HDR10_ENLARGE_DELAY_STATUS(_ADVANCED_HDR10_ENLARGE_DELAY_ON);
                usIVS2DVSDelay = usDelayMax;
            }
        }
#endif
    }
    return usIVS2DVSDelay;
}
#endif

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
//                enumInputDataPath --> I-domain data path
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerFRCDBWaitForIDomainEvent(EnumWaitIDomainEventType enumEvent, EnumInputDataPath enumInputDataPath)
{
    if(ScalerGlobalGetIDomainDBStatus(enumInputDataPath) == _I_DOMAIN_DB_DISABLE)
    {
        return _FALSE;
    }

    if(ScalerTimerWaitForIDomainEvent(enumEvent, enumInputDataPath) == _FALSE)
    {
        ScalerGlobalIDomainDoubleBufferEnable(enumInputDataPath, _DISABLE);
        return _FALSE;
    }
    return _TRUE;
}
