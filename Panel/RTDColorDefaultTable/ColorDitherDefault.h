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
// ID Code      : ColorDitherDefault.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#define _I_DITHER_TEMP                          _ENABLE

#if((_HW_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
#define _I_DITHER_VALUE_SIGN                    _DISABLE
#define _I_DITHER_V_FRAME_MOD                   _DISABLE
#define _I_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#if((_HW_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
#define _I_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _I_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#define _I_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _I_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _I_DITHER_SEQ_INV_MODE                  0
#endif

#if(_HW_IDITHER_SUPER_PIXEL_SUPPORT == _ON)
#define _I_DITHER_SUPER_PIXEL_SIZE              _IDITHER_SUPER_PIXEL_2X2
#endif

#define _I_DITHER_12_TO_10_TEMP                 _I_DITHER_TEMP
#define _I_DITHER_12_TO_10_VALUE_SIGN           _I_DITHER_VALUE_SIGN
#define _I_DITHER_12_TO_10_V_FRAME_MOD          _I_DITHER_V_FRAME_MOD
#define _I_DITHER_12_TO_10_H_FRAME_MOD          _I_DITHER_H_FRAME_MOD
#define _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE     _I_DITHER_MULTI_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE     _I_DITHER_SHARE_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE    _I_DITHER_SERIES_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_ENABLE       _I_DITHER_SEQ_INV_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_MODE         _I_DITHER_SEQ_INV_MODE // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#define _D_DITHER_TEMP                          _ENABLE

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#define _D_DITHER_V_FRAME_MOD                   _DISABLE
#define _D_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#define _D_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _D_DITHER_SEQ_INV_MODE                  0 // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#define _D_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _D_DITHER_ADVANCE_SETTING_ENABLE        _DISABLE
#endif

#if(_HW_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
#define _D_DITHER_FREERUN_EN_SUPPORT            _DISABLE // Enable DDither When Show Logo
#endif
