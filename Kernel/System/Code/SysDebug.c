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
// ID Code      : SysDebug.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "SysInclude.h"
#include "Debug/SysDebug.h"

#if(_ASSERT_SUPPORT == _ON)
#warning "NOTE: ASSERT SUPPORT ON!!"
#endif

#if(_UNITY_BUILD_SUPPORT == _ON)
#warning "NOTE: _UNITY_BUILD_SUPPORT ON!!"
#endif

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
// Description  : system debug handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDebugHandler(void)
{
    ScalerDebug();
}

#if(_ASSERT_SUPPORT == _ON)
#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Check panel parameter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDebugCheckPanelParameter(void)
{
    ScalerDebugCheckPanelParameter();

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        // Rotation/ Mirror not supported under 5k3k panel!! _DISPLAY_ROTATION_SUPPORT Set _OFF
        ASSERT(_DISPLAY_ROTATION_SUPPORT != _ON);

        // Mirror not supported under 5k3k panel!! _DISPLAY_VER_MIRROR_SUPPORT/ _DISPLAY_HOR_MIRROR_SUPPORT Set _OFF
        ASSERT(_DISPLAY_VER_MIRROR_SUPPORT != _ON);
        ASSERT(_DISPLAY_HOR_MIRROR_SUPPORT != _ON);
    }

    //--------------------------------------------------
    // Modification of Panel Parameters
    //--------------------------------------------------
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        // _PANEL_DH_SYNC_WIDTH Should Be Multiple of 4 in Front_Back Mode
        ASSERT((_PANEL_DH_SYNC_WIDTH % 4) == 0);

        // _PANEL_DH_START Should Be Larger than 72 in Front_Back Mode
        ASSERT(_PANEL_DH_START >= 72);

        // _PANEL_DH_START Should Be Multiple of 8 in Front_Back Mode
        ASSERT((_PANEL_DH_START % 8) == 0);

        // _PANEL_DH_WIDTH Should Be Multiple of 4 in Front_Back Mode
        ASSERT((_PANEL_DH_WIDTH % 4) == 0);

        // _PANEL_DH_END Should Be Multiple of 4 in Front_Back Mode
        ASSERT((_PANEL_DH_END % 4) == 0);

        // _PANEL_DH_TOTAL Should Be Multiple of 8 in Front_Back Mode
        ASSERT((_PANEL_DH_TOTAL % 8) == 0);

        // _PANEL_DH_TOTAL_MAX Should Be Multiple of 8 in Front_Back Mode
        ASSERT((_PANEL_DH_TOTAL_MAX % 8) == 0);

        // _PANEL_DH_TOTAL_MIN Should Be Multiple of 8 in Front_Back Mode
        ASSERT((_PANEL_DH_TOTAL_MIN % 8) == 0);
    }
    else if(GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH)
    {
        // _PANEL_DH_SYNC_WIDTH Should Be Multiple of 2 in Even_Odd Mode
        ASSERT((_PANEL_DH_SYNC_WIDTH % 2) == 0);

        // _PANEL_DH_START Should Be Larger than 36 in Even_Odd Mode
        ASSERT(_PANEL_DH_START >= 36);

        // _PANEL_DH_START Should Be Multiple of 2 in Even_Odd Mode
        ASSERT((_PANEL_DH_START % 2) == 0);

        // _PANEL_DH_WIDTH Should Be Multiple of 2 in Even_Odd Mode
        ASSERT((_PANEL_DH_WIDTH % 2) == 0);

        // _PANEL_DH_END Should Be Multiple of 2 in Even_Odd Mode
        ASSERT((_PANEL_DH_END % 2) == 0);

        // _PANEL_DH_TOTAL Should Be Multiple of 4 in Even_Odd Mode
        ASSERT((_PANEL_DH_TOTAL % 4) == 0);

        // _PANEL_DH_TOTAL_MAX Should Be Multiple of 4 in Even_Odd Mode
        ASSERT((_PANEL_DH_TOTAL_MAX % 4) == 0);

        // _PANEL_DH_TOTAL_MIN Should Be Multiple of 4 in Even_Odd Mode
        ASSERT((_PANEL_DH_TOTAL_MIN % 4) == 0);
    }
    else
    {
        // _PANEL_DH_START Should Be Larger than 18 in Single Mode
        ASSERT(_PANEL_DH_START >= 18);

        // _PANEL_DH_TOTAL Should Be Multiple of 2 in Single Mode
        ASSERT((_PANEL_DH_TOTAL % 2) == 0);

        // _PANEL_DH_TOTAL_MAX Should Be Multiple of 2 in Single Mode
        ASSERT((_PANEL_DH_TOTAL_MAX % 2) == 0);

        // _PANEL_DH_TOTAL_MIN Should Be Multiple of 2 in Single Mode
        ASSERT((_PANEL_DH_TOTAL_MIN % 2) == 0);
    }

    // _PANEL_DV_SYNC_HEIGHT Should Be Larger than 2
    ASSERT(_PANEL_DV_SYNC_HEIGHT >= 2);

    // _PANEL_DV_START Should Be Larger than 2
    ASSERT(_PANEL_DV_START >= 2);

    if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) &&
       ((_3P_FLAG_DISPLAY_SUPPORT == _ON) ||
        (_2P_PIP_DISPLAY_SUPPORT == _ON)))
    {
        // _PANEL_DV_START Should be larger than 16 in order to tune preread when GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_FLAG or _2P_PIP_DISPLAY_SUPPORT
        ASSERT(_PANEL_DV_START >= 16);
    }

    // _PANEL_DH_TOTAL_MIN Should Be Large Than (_PANEL_DH_START + _PANEL_DH_WIDTH) + H front porch, Check Panel H front porch limit !!
    ASSERT(_PANEL_DH_TOTAL_MIN > (_PANEL_DH_START + _PANEL_DH_WIDTH));

    // _PANEL_DH_SYNC_WIDTH Should Be Less Than _PANEL_DH_START
    ASSERT(_PANEL_DH_SYNC_WIDTH < _PANEL_DH_START);

    // _PANEL_DV_TOTAL_MIN Should Be Large Than (_PANEL_DV_START + _PANEL_DV_HEIGHT) + V front porch, Check Panel V front porch limit !!
    ASSERT(_PANEL_DV_TOTAL_MIN > (_PANEL_DV_START + _PANEL_DV_HEIGHT));

    // _PANEL_DV_SYNC_HEIGHT Should Be Less Than _PANEL_DV_START
    ASSERT(_PANEL_DV_SYNC_HEIGHT < _PANEL_DV_START);

    // _PANEL_DV_TOTAL_MAX Should Be Less Than DVtotal max count
    ASSERT(_PANEL_DV_TOTAL_MAX <= _HW_DIS_TIMING_GEN_VTOTAL_BIT);

    // DHTotal Should Be Multiple of Dispaly Outport
    ASSERT((_PANEL_DH_TOTAL % _PANEL_OUTPUT_NUM) == 0);

    // DHTotal Max Should Be Multiple of Dispaly Outport
    ASSERT((_PANEL_DH_TOTAL_MAX % _PANEL_OUTPUT_NUM) == 0);

    // DHTotal Min Should Be Multiple of Dispaly Outport
    ASSERT((_PANEL_DH_TOTAL_MIN % _PANEL_OUTPUT_NUM) == 0);

    // DHStart Should Be Multiple of Dispaly Outport
    ASSERT((_PANEL_DH_START % _PANEL_OUTPUT_NUM) == 0);

    // DHWidth Should Be Multiple of Dispaly Outport
    ASSERT((_PANEL_DH_WIDTH % _PANEL_OUTPUT_NUM) == 0);

    // DHWidth End Should Be Multiple of Dispaly Outport
    ASSERT((_PANEL_DH_END % _PANEL_OUTPUT_NUM) == 0);

    // _PANEL_DV_TOTAL should be in the range from _PANEL_DV_TOTAL_MIN to _PANEL_DV_TOTAL_MAX
    ASSERT(_PANEL_DV_TOTAL <= _PANEL_DV_TOTAL_MAX);
    ASSERT(_PANEL_DV_TOTAL >= _PANEL_DV_TOTAL_MIN);

    // _PANEL_DH_TOTAL should be in the range from _PANEL_DH_TOTAL_MIN to _PANEL_DH_TOTAL_MAX
    ASSERT(_PANEL_DH_TOTAL <= _PANEL_DH_TOTAL_MAX);
    ASSERT(_PANEL_DH_TOTAL >= _PANEL_DH_TOTAL_MIN);

    // _PANEL_PIXEL_CLOCK should be in the range from _PANEL_PIXEL_CLOCK_MIN to _PANEL_PIXEL_CLOCK_MAX
    ASSERT(_PANEL_PIXEL_CLOCK <= _PANEL_PIXEL_CLOCK_MAX);
    ASSERT(_PANEL_PIXEL_CLOCK >= _PANEL_PIXEL_CLOCK_MIN);

    if(_PANEL_STYLE == _PANEL_LVDS)
    {
        // _PANEL_LVDS_PANEL_SECTION Should Be Less than or Equal to _PANEL_LVDS_OUTPUT_PORT
        ASSERT(_PANEL_LVDS_PANEL_SECTION <= _PANEL_LVDS_OUTPUT_PORT);
    }
    else if(_PANEL_STYLE == _PANEL_VBO)
    {
        // _PANEL_VBO_PANEL_SECTION Should Be Less than or Equal to _PANEL_VBO_OUTPUT_PORT
        ASSERT(_PANEL_VBO_PANEL_SECTION <= _PANEL_VBO_OUTPUT_PORT);

        // _PANEL_POW_SEQ_FAST_MODE Should Be Off When Panel Style As VBy1
        ASSERT(_PANEL_POW_SEQ_FAST_MODE == _OFF);
    }

    // _PANEL_LAST_LINE_MAX should be less than _PANEL_DH_TOTAL_MIN
    ASSERT(_PANEL_LAST_LINE_MAX < _PANEL_DH_TOTAL_MIN);

    // Enlarge _PANEL_PIXEL_CLOCK_MAX_KHZ/ _PANEL_PIXEL_CLOCK_MIN_KHZ Range, or _DPLL_JITTER_MARGIN Select _DPLL_NO_JITTER_MARGIN
    ASSERT(_PANEL_PIXEL_CLOCK_MAX_SPREAD > _PANEL_PIXEL_CLOCK_MIN_SPREAD);

    // (_PANEL_DH_TOTAL * _PANEL_DV_TOTAL * _PANEL_TYP_FRAME_RATE) should be less than Pixel clk max with SSCG
    ASSERT((_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000) <= _PANEL_PIXEL_CLOCK_MAX_SPREAD);

    // (_PANEL_DH_TOTAL * _PANEL_DV_TOTAL * _PANEL_TYP_FRAME_RATE) should be larger than Pixel clk min with SSCG
    ASSERT((_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000) >= _PANEL_PIXEL_CLOCK_MIN_SPREAD);

    // _PANEL_FRAME_SYNC_MARGIN Suggest Larger than 20
    if(_PANEL_FRAME_SYNC_MARGIN < 20)
    {
        // margin suggest larger than 20 for narrow range frequency
        ASSERT((_PANEL_MAX_FRAME_RATE - _PANEL_MIN_FRAME_RATE) >= (_PANEL_TYP_FRAME_RATE >> 4));
    }

    //--------------------------------------------------
    // Definitions for FREESYNC Panel Parameters
    //--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
    // _PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * FreeSync Vfreq Ratio)!
    ASSERT(_PANEL_DV_TOTAL_MAX >= ((_PANEL_DV_TOTAL * _PANEL_DP_FREESYNC_MAX_FRAME_RATE) / _PANEL_DP_FREESYNC_MIN_FRAME_RATE));
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    // _PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * FreeSync Vfreq Ratio)!
    ASSERT(_PANEL_DV_TOTAL_MAX >= ((_PANEL_DV_TOTAL * _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE) / _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE));
#endif

    //--------------------------------------------------
    // Definitions for VRR Panel Parameters
    //--------------------------------------------------
#if(_HDMI21_VRR_SUPPORT == _ON)
    // _PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * FreeSync Vfreq Ratio)!
    ASSERT(_PANEL_DV_TOTAL_MAX >= ((_PANEL_DV_TOTAL * _PANEL_HDMI21_VRR_MAX_FRAME_RATE) / _PANEL_HDMI21_VRR_MIN_FRAME_RATE));
#endif

    //--------------------------------------------------
    // I Dither Option
    //--------------------------------------------------
#if(_I_DITHER_FUNCTION == _ON)
#if((_HW_IDITHER_TYPE != _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) &&\
    (_HW_IDITHER_TYPE != _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) &&\
    (_HW_IDITHER_TYPE != _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
    // IDither Multi, Share, Series, Inv Function can't be used by this Gen!
    ASSERT((_I_DITHER_MULTI_SEQ_ENABLE != _ENABLE) &&
           (_I_DITHER_SHARE_SEQ_ENABLE != _ENABLE) &&
           (_I_DITHER_SERIES_SEQ_ENABLE != _ENABLE) &&
           (_I_DITHER_SEQ_INV_ENABLE != _ENABLE));
#endif

#if(_HW_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT)
    // IDither Sign, VModu, HModu Function can't be used by this Gen!
    ASSERT((_I_DITHER_VALUE_SIGN != _ENABLE) &&
           (_I_DITHER_V_FRAME_MOD != _ENABLE) &&
           (_I_DITHER_H_FRAME_MOD != _ENABLE));
#endif

#endif

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#if(_D_DITHER_FUNCTION == _ON)
#if((_HW_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL) &&\
    (_HW_DDITHER_TYPE != _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) &&\
    (_HW_DDITHER_TYPE != _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
    // DDither Series,Advance Function can't be used by this Gen!
    ASSERT((_D_DITHER_SERIES_SEQ_ENABLE != _ENABLE) &&
           (_D_DITHER_ADVANCE_SETTING_ENABLE != _ENABLE));
#endif

#if(_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
    // _DDITHER_GEN_1_6BIT_DITHERTBL don't support 6bit panel!
    ASSERT(_PANEL_DISP_BIT_MODE != _PANEL_DISP_18_BIT);
#endif

#if(_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL)
    // DDither H/V Modulation Function can't be used by this Gen!
    ASSERT((_D_DITHER_V_FRAME_MOD != _ENABLE) &&
           (_D_DITHER_H_FRAME_MOD != _ENABLE));
#endif

#if(_D_DITHER_FREERUN_EN_SUPPORT == _ENABLE)
    // DDither _D_DITHER_FREERUN_EN_SUPPORT can't be used by this Gen or when Panel is not 18 bit!
    ASSERT((_HW_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL) &&
           (_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT));
#endif

#endif
}
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)
#endif

