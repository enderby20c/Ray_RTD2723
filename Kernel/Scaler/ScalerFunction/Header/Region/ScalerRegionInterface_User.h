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
// ID Code      : ScalerRegionInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DISPLAY_MODE_1P = 0x00,

    _DISPLAY_MODE_2P_PIP = 0x10,
    _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT = 0x20,
    _DISPLAY_MODE_2P_PBP_LR_EQUAL = 0x30,
    _DISPLAY_MODE_2P_PBP_LR_L_LARGE = 0x40,
    _DISPLAY_MODE_2P_PBP_LR_R_LARGE = 0x50,
    _DISPLAY_MODE_2P_PBP_TB = 0x60,

    _DISPLAY_MODE_3P_FLAG = 0x70,
    _DISPLAY_MODE_3P_SKEW_L = 0x80,
    _DISPLAY_MODE_3P_SKEW_R = 0x90,
    _DISPLAY_MODE_3P_SKEW_T = 0xA0,
    _DISPLAY_MODE_3P_SKEW_B = 0xB0,

    _DISPLAY_MODE_4P = 0xC0,
    _DISPLAY_MODE_NONE = 0xF0,
} EnumDisplayMode;

typedef enum
{
    _INPUT_PATH_NONE = 0,
    _INPUT_PATH_M1 = 0x01,
    _INPUT_PATH_M2 = 0x02,
    _INPUT_PATH_S1 = 0x04,
    _INPUT_PATH_S2 = 0x08,
    _INPUT_PATH_S3 = 0x10,
    _INPUT_PATH_S4 = 0x20,
    _INPUT_PATH_M1_M2 = (_INPUT_PATH_M1 | _INPUT_PATH_M2),
    _INPUT_PATH_S1_S2 = (_INPUT_PATH_S1 | _INPUT_PATH_S2),
    _INPUT_PATH_S3_S4 = (_INPUT_PATH_S3 | _INPUT_PATH_S4),
    _INPUT_PATH_M1_M2_S1_S2 = (_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2),
    _INPUT_PATH_ALL = _HW_I_DOMAIN_INPUT_PATH_ALL,
} EnumInputDataPath;

typedef enum
{
    _DDOMAIN_RGN_NONE = 0x00,
    _DDOMAIN_RGN_R1_A1 = 0x01,
    _DDOMAIN_RGN_R1_A2 = 0x02,
    _DDOMAIN_RGN_R2_A1 = 0x04,
    _DDOMAIN_RGN_R2_A2 = 0x08,
    _DDOMAIN_RGN_R3_A1 = 0x10,
    _DDOMAIN_RGN_R3_A2 = 0x20,
    _DDOMAIN_RGN_ALL = _HW_D_DOMAIN_RGN_ALL,
} EnumDDomainRegion;

typedef enum
{
    _MDOMAIN_DISP_PATH_NONE = 0,
    _MDOMAIN_DISP_PATH_M1 = 0x0100,
    _MDOMAIN_DISP_PATH_M2 = 0x0200,
    _MDOMAIN_DISP_PATH_S1 = 0x0400,
    _MDOMAIN_DISP_PATH_S2 = 0x0800,
    _MDOMAIN_DISP_PATH_S3 = 0x1000,
    _MDOMAIN_DISP_PATH_S4 = 0x2000,
    _MDOMAIN_DISP_PATH_M1_M2 = (_MDOMAIN_DISP_PATH_M1 | _MDOMAIN_DISP_PATH_M2),
    _MDOMAIN_DISP_PATH_S1_S2 = (_MDOMAIN_DISP_PATH_S1 | _MDOMAIN_DISP_PATH_S2),
    _MDOMAIN_DISP_PATH_S3_S4 = (_MDOMAIN_DISP_PATH_S3 | _MDOMAIN_DISP_PATH_S4),
    _MDOMAIN_DISP_PATH_M1_M2_S1_S2 = (_MDOMAIN_DISP_PATH_M1_M2 | _MDOMAIN_DISP_PATH_S1_S2),
    _MDOMAIN_DISP_PATH_ALL = _HW_M_DOMAIN_DISP_PATH_ALL,
} EnumMDomainDisplayDataPath;


typedef enum
{
    _INPUT_PATH_1 = 0x01,
    _INPUT_PATH_2 = 0x02,
    _INPUT_PATH_4 = 0x04,
    _INPUT_PATH_TOTAL = _HW_I_DOMAIN_PATH_COUNT,
} EnumRegionInputPathCount;

typedef enum
{
    _DISPLAY_PATH_1 = 0x01,
    _DISPLAY_PATH_2 = 0x02,
    _DISPLAY_PATH_4 = 0x04,
    _DISPLAY_PATH_TOTAL = _HW_D_DOMAIN_PATH_COUNT,
} EnumRegionDisplayPathCount;

typedef enum
{
    _REGION_INDEX_0 = 0x00,
    _REGION_INDEX_1 = 0x01,
    _REGION_INDEX_2 = 0x02,
    _REGION_INDEX_3 = 0x03,
    _REGION_INDEX_NONE = 0x0F,
} EnumRegionIndex;

typedef enum
{
    _DISPLAY_RGN_1P = _DISPLAY_MODE_1P,

    _DISPLAY_RGN_PIP_MAIN = (_DISPLAY_MODE_2P_PIP | _REGION_INDEX_0),
    _DISPLAY_RGN_PIP_SUB = (_DISPLAY_MODE_2P_PIP | _REGION_INDEX_1),

    _DISPLAY_RGN_EAGLE_SIGHT_MAIN = (_DISPLAY_MODE_2P_PIP_EAGLE_SIGHT | _REGION_INDEX_0),
    _DISPLAY_RGN_EAGLE_SIGHT_SUB = (_DISPLAY_MODE_2P_PIP_EAGLE_SIGHT | _REGION_INDEX_1),

    _DISPLAY_RGN_PBP_LR_EQUAL_LEFT = (_DISPLAY_MODE_2P_PBP_LR_EQUAL | _REGION_INDEX_0),
    _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT = (_DISPLAY_MODE_2P_PBP_LR_EQUAL | _REGION_INDEX_1),

    _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT = (_DISPLAY_MODE_2P_PBP_LR_L_LARGE | _REGION_INDEX_0),
    _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT = (_DISPLAY_MODE_2P_PBP_LR_L_LARGE | _REGION_INDEX_1),

    _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT = (_DISPLAY_MODE_2P_PBP_LR_R_LARGE | _REGION_INDEX_0),
    _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT = (_DISPLAY_MODE_2P_PBP_LR_R_LARGE | _REGION_INDEX_1),

    _DISPLAY_RGN_TOP = (_DISPLAY_MODE_2P_PBP_TB | _REGION_INDEX_0),
    _DISPLAY_RGN_BOTTOM = (_DISPLAY_MODE_2P_PBP_TB | _REGION_INDEX_1),

    _DISPLAY_RGN_FLAG_MAIN = (_DISPLAY_MODE_3P_FLAG | _REGION_INDEX_0),
    _DISPLAY_RGN_FLAG_LEFT = (_DISPLAY_MODE_3P_FLAG | _REGION_INDEX_1),
    _DISPLAY_RGN_FLAG_RIGHT = (_DISPLAY_MODE_3P_FLAG | _REGION_INDEX_2),

    _DISPLAY_RGN_SKEW_L_MAIN = (_DISPLAY_MODE_3P_SKEW_L | _REGION_INDEX_0),
    _DISPLAY_RGN_SKEW_L_TOP = (_DISPLAY_MODE_3P_SKEW_L | _REGION_INDEX_1),
    _DISPLAY_RGN_SKEW_L_BOTTOM = (_DISPLAY_MODE_3P_SKEW_L | _REGION_INDEX_2),

    _DISPLAY_RGN_SKEW_R_MAIN = (_DISPLAY_MODE_3P_SKEW_R | _REGION_INDEX_0),
    _DISPLAY_RGN_SKEW_R_TOP = (_DISPLAY_MODE_3P_SKEW_R | _REGION_INDEX_1),
    _DISPLAY_RGN_SKEW_R_BOTTOM = (_DISPLAY_MODE_3P_SKEW_R | _REGION_INDEX_2),

    _DISPLAY_RGN_SKEW_T_MAIN = (_DISPLAY_MODE_3P_SKEW_T | _REGION_INDEX_0),
    _DISPLAY_RGN_SKEW_T_LEFT = (_DISPLAY_MODE_3P_SKEW_T | _REGION_INDEX_1),
    _DISPLAY_RGN_SKEW_T_RIGHT = (_DISPLAY_MODE_3P_SKEW_T | _REGION_INDEX_2),

    _DISPLAY_RGN_SKEW_B_MAIN = (_DISPLAY_MODE_3P_SKEW_B | _REGION_INDEX_0),
    _DISPLAY_RGN_SKEW_B_LEFT = (_DISPLAY_MODE_3P_SKEW_B | _REGION_INDEX_1),
    _DISPLAY_RGN_SKEW_B_RIGHT = (_DISPLAY_MODE_3P_SKEW_B | _REGION_INDEX_2),

    _DISPLAY_RGN_LT = (_DISPLAY_MODE_4P | _REGION_INDEX_0),
    _DISPLAY_RGN_LB = (_DISPLAY_MODE_4P | _REGION_INDEX_1),
    _DISPLAY_RGN_RT = (_DISPLAY_MODE_4P | _REGION_INDEX_2),
    _DISPLAY_RGN_RB = (_DISPLAY_MODE_4P | _REGION_INDEX_3),

    _DISPLAY_RGN_NONE = (_DISPLAY_MODE_NONE | _REGION_INDEX_NONE),
} EnumDisplayRegion;

typedef enum
{
    _1P_NORMAL_REGION = _DISPLAY_RGN_1P,

    _2P_PIP_MAIN = _DISPLAY_RGN_PIP_MAIN,
    _2P_PIP_SUB = _DISPLAY_RGN_PIP_SUB,

    _2P_PIP_EAGLE_SIGHT_MAIN = _DISPLAY_RGN_EAGLE_SIGHT_MAIN,
    _2P_PIP_EAGLE_SIGHT_SUB = _DISPLAY_RGN_EAGLE_SIGHT_SUB,

    _2P_PBP_LR_EQUAL_L = _DISPLAY_RGN_PBP_LR_EQUAL_LEFT,
    _2P_PBP_LR_EQUAL_R = _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT,

    _2P_PBP_LR_L_LARGE_L = _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT,
    _2P_PBP_LR_L_LARGE_R = _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT,

    _2P_PBP_LR_R_LARGE_L = _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT,
    _2P_PBP_LR_R_LARGE_R = _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT,

    _2P_PBP_TB_T = _DISPLAY_RGN_TOP,
    _2P_PBP_TB_B = _DISPLAY_RGN_BOTTOM,

    _3P_FLAG_M = _DISPLAY_RGN_FLAG_MAIN,
    _3P_FLAG_L = _DISPLAY_RGN_FLAG_LEFT,
    _3P_FLAG_R = _DISPLAY_RGN_FLAG_RIGHT,
    _3P_FLAG_M_OUTSIDE,
    _3P_FLAG_L_OUTSIDE,
    _3P_FLAG_R_OUTSIDE,

    _3P_SKEW_L_M = _DISPLAY_RGN_SKEW_L_MAIN,
    _3P_SKEW_L_T = _DISPLAY_RGN_SKEW_L_TOP,
    _3P_SKEW_L_B = _DISPLAY_RGN_SKEW_L_BOTTOM,
    _3P_SKEW_L_M_OUTSIDE,
    _3P_SKEW_L_T_OUTSIDE,
    _3P_SKEW_L_B_OUTSIDE,

    _3P_SKEW_R_M = _DISPLAY_RGN_SKEW_R_MAIN,
    _3P_SKEW_R_T = _DISPLAY_RGN_SKEW_R_TOP,
    _3P_SKEW_R_B = _DISPLAY_RGN_SKEW_R_BOTTOM,
    _3P_SKEW_R_M_OUTSIDE,
    _3P_SKEW_R_T_OUTSIDE,
    _3P_SKEW_R_B_OUTSIDE,

    _3P_SKEW_T_M = _DISPLAY_RGN_SKEW_T_MAIN,
    _3P_SKEW_T_L = _DISPLAY_RGN_SKEW_T_LEFT,
    _3P_SKEW_T_R = _DISPLAY_RGN_SKEW_T_RIGHT,
    _3P_SKEW_T_M_OUTSIDE,
    _3P_SKEW_T_L_OUTSIDE,
    _3P_SKEW_T_R_OUTSIDE,

    _3P_SKEW_B_M = _DISPLAY_RGN_SKEW_B_MAIN,
    _3P_SKEW_B_L = _DISPLAY_RGN_SKEW_B_LEFT,
    _3P_SKEW_B_R = _DISPLAY_RGN_SKEW_B_RIGHT,
    _3P_SKEW_B_M_OUTSIDE,
    _3P_SKEW_B_L_OUTSIDE,
    _3P_SKEW_B_R_OUTSIDE,

    _4P_LT = _DISPLAY_RGN_LT,
    _4P_LB = _DISPLAY_RGN_LB,
    _4P_RT = _DISPLAY_RGN_RT,
    _4P_RB = _DISPLAY_RGN_RB,
    _4P_LT_OUTSIDE,
    _4P_LB_OUTSIDE,
    _4P_RT_OUTSIDE,
    _4P_RB_OUTSIDE,

    _FULL_REGION,
    _DEMO_INSIDE,
    _DEMO_OUTSIDE,

    _NON_REGION = _DISPLAY_RGN_NONE,
} EnumSelRegion;

typedef enum
{
    _BYPASS_DISABLE = 0,
    _BYPASS_ENABLE = 1,
}EnumByPassEnable;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

