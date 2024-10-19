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
// ID Code      : ScalerColorICM.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_COLOR_IP_ICM == _ON)
//--------------------------------------------------
// Code Tables of SixColor
//--------------------------------------------------
#if(_SIX_COLOR_SUPPORT == _ON)
SWORD code tSIX_COLOR_U_MAX_8[][3] =
{
    { 313,  255,  -35},
    {-134, -255, -310},
    {-366, -512, -363},
    {-313, -255, -125},
    { -52,  255,  313},
    { 396,  512,  402},
};

SWORD code tSIX_COLOR_V_MAX_8[][3] =
{
    { 396,  512,  512},
    { 512,  512,  403},
    { 290,    0, -297},
    {-396, -512, -512},
    {-512, -512, -396},
    {-231,    0,  219},
};

SWORD code tSIX_COLOR_CTOC_DELTA_UV_DOWN[][2] =
{
    {-447,    0}, // R-->Y
    {-179, -361}, // Y-->G
    { 226, -449}, // G-->C
    { 348,    0}, // C-->B
    { 193,  390}, // B-->M
    {-226,  449}, // M-->R
};

SWORD code tSIX_COLOR_RTOR_DELTA_UV_DOWN[][4] =
{
    { -58,  116, -390,    0},
    {-122,    0, -111, -221},
    {-145, -291,  198, -396},
    {  58, -116,  203,    0},
    { 309,    0,  140,  280},
    { 116,  232, -198,  396},
};

SWORD code tSIX_COLOR_LTOL_DELTA_UV_DOWN[][2] =
{
    {-221,    0},
    {-202, -404},
    { 107, -215},
    { 382,    0},
    { 198,  396},
    {-146,  293},
};

SWORD code tSIX_COLOR_CTOC_DELTA_UV_UP[][2] =
{
    { 197, -397}, // R-->M
    { 358,    0}, // Y-->R
    { 229,  454}, // G-->Y
    {-177,  358}, // C-->G
    {-444,    0}, // B-->C
    {-227, -450}, // M-->B
};

SWORD code tSIX_COLOR_RTOR_DELTA_UV_UP[][2] =
{
    { 198, -396},
    { 390,    0},
    { 111,  221},
    {-198,  396},
    {-203,    0},
    {-140, -280},
};

SWORD code tSIX_COLOR_LTOL_DELTA_UV_UP[][4] =
{
    { 291,    0,  146, -293},
    {  54,  108,  221,    0},
    {-149,  297,  202,  404},
    {-130,    0, -107,  215},
    { -58, -116, -382,    0},
    { 110, -219, -198, -396},
};

//Osd Turning position to next CM
BYTE code tR_TURNING_POSITION_DOWN[] = {61, 66, 71, 68, 75, 69};
BYTE code tL_TURNING_POSITION_UP[] = {27, 34, 29, 33, 39, 32};

#if(_HW_ICM_TABLE_TYPE == _ICM_GEN_3)
code BYTE tICM_TABLE_GRAY_R[] =
{
    0xFC, 0xF8, 0xF8, 0xF0, 0xF4, 0xE8, 0xF0, 0xE0, 0xEC, 0xD8, 0xE8, 0xD0, 0xE4, 0xC8, 0xE0, 0xC0,
    0xFB, 0xF9, 0xF6, 0xF3, 0xF1, 0xED, 0xEC, 0xE7, 0xE7, 0xE1, 0xE2, 0xDA, 0xDD, 0xD4, 0xD8, 0xCE,
    0x00, 0xF8, 0x01, 0xF0, 0x01, 0xE8, 0x02, 0xE0, 0x02, 0xD8, 0x03, 0xD0, 0x03, 0xC8, 0x04, 0xC0,
    0xFB, 0xF9, 0xF6, 0xF3, 0xF1, 0xED, 0xEC, 0xE7, 0xE7, 0xE1, 0xE2, 0xDA, 0xDD, 0xD4, 0xD8, 0xCE,
    // LSB
    0x00, 0x00, 0x00, 0x00, 0x36, 0x69, 0x8B, 0xFE, 0x80, 0xC4, 0xC4, 0xC8, 0x36, 0x69, 0x8B, 0xFE,
};

code BYTE tICM_TABLE_GRAY_Y[] =
{
    0x04, 0xF8, 0x08, 0xF0, 0x0C, 0xE8, 0x10, 0xE0, 0x14, 0xD8, 0x18, 0xD0, 0x1C, 0xC8, 0x20, 0xC0,
    0x02, 0xF8, 0x04, 0xF0, 0x06, 0xE8, 0x08, 0xE0, 0x0A, 0xD8, 0x0C, 0xD0, 0x0E, 0xC8, 0x10, 0xC0,
    0x04, 0xF9, 0x09, 0xF3, 0x0E, 0xED, 0x13, 0xE6, 0x18, 0xE0, 0x1D, 0xDA, 0x22, 0xD3, 0x26, 0xCD,
    0x02, 0xF8, 0x04, 0xF0, 0x06, 0xE8, 0x08, 0xE0, 0x0A, 0xD8, 0x0C, 0xD0, 0x0E, 0xC8, 0x10, 0xC0,
    // LSB
    0x00, 0x00, 0x00, 0x00, 0x04, 0x48, 0x88, 0xCC, 0xFE, 0x8B, 0x61, 0x3E, 0x04, 0x48, 0x88, 0xCC,
};

code BYTE tICM_TABLE_GRAY_G[] =
{
    0x08, 0x00, 0x10, 0x00, 0x18, 0x00, 0x20, 0x00, 0x28, 0x00, 0x30, 0x00, 0x38, 0x00, 0x40, 0x00,
    0x05, 0xFB, 0x0B, 0xF7, 0x11, 0xF2, 0x17, 0xED, 0x1C, 0xE9, 0x22, 0xE4, 0x28, 0xE0, 0x2D, 0xDB,
    0x05, 0x04, 0x0B, 0x09, 0x11, 0x0E, 0x16, 0x12, 0x1C, 0x17, 0x22, 0x1B, 0x27, 0x20, 0x2D, 0x25,
    0x05, 0xFB, 0x0B, 0xF7, 0x11, 0xF2, 0x17, 0xED, 0x1C, 0xE9, 0x22, 0xE4, 0x28, 0xE0, 0x2D, 0xDB,
    // LSB
    0x00, 0x00, 0x00, 0x00, 0xE8, 0x53, 0xD7, 0x1F, 0xF5, 0x0E, 0x93, 0xE9, 0xE8, 0x53, 0xD7, 0x1F,
};

code BYTE tICM_TABLE_GRAY_C[] =
{
    0x04, 0x08, 0x08, 0x10, 0x0C, 0x18, 0x10, 0x20, 0x14, 0x28, 0x18, 0x30, 0x1C, 0x38, 0x20, 0x40,
    0x05, 0x06, 0x09, 0x0C, 0x0E, 0x12, 0x13, 0x18, 0x18, 0x1F, 0x1D, 0x25, 0x22, 0x2B, 0x27, 0x31,
    0x02, 0x08, 0x04, 0x10, 0x06, 0x18, 0x07, 0x20, 0x09, 0x28, 0x0B, 0x30, 0x0D, 0x38, 0x0F, 0x40,
    0x05, 0x06, 0x09, 0x0C, 0x0E, 0x12, 0x13, 0x18, 0x18, 0x1F, 0x1D, 0x25, 0x22, 0x2B, 0x27, 0x31,
    // LSB
    0x00, 0x00, 0x00, 0x00, 0x1E, 0xEB, 0x89, 0x56, 0x00, 0x0C, 0xCC, 0xCC, 0x1E, 0xEB, 0x89, 0x56,
};

code BYTE tICM_TABLE_GRAY_B[] =
{
    0xFC, 0x08, 0xF8, 0x10, 0xF4, 0x18, 0xF0, 0x20, 0xEC, 0x28, 0xE8, 0x30, 0xE4, 0x38, 0xE0, 0x40,
    0x00, 0x08, 0x01, 0x10, 0x02, 0x18, 0x03, 0x20, 0x04, 0x28, 0x05, 0x30, 0x05, 0x38, 0x06, 0x40,
    0xFB, 0x06, 0xF6, 0x0C, 0xF1, 0x12, 0xEC, 0x18, 0xE7, 0x1F, 0xE2, 0x25, 0xDD, 0x2B, 0xD8, 0x31,
    0x00, 0x08, 0x01, 0x10, 0x02, 0x18, 0x03, 0x20, 0x04, 0x28, 0x05, 0x30, 0x05, 0x38, 0x06, 0x40,
    // LSB
    0x00, 0x00, 0x00, 0x00, 0xCC, 0x84, 0x00, 0xC8, 0x16, 0x6B, 0x89, 0xDE, 0xCC, 0x84, 0x00, 0xC8,
};

code BYTE tICM_TABLE_GRAY_M[] =
{
    0xF8, 0x00, 0xF0, 0x00, 0xE8, 0x00, 0xE0, 0x00, 0xD8, 0x00, 0xD0, 0x00, 0xC8, 0x00, 0xC0, 0x00,
    0xF9, 0x03, 0xF3, 0x07, 0xED, 0x0A, 0xE7, 0x0E, 0xE1, 0x12, 0xDA, 0x15, 0xD4, 0x19, 0xCE, 0x1D,
    0xF9, 0xFC, 0xF3, 0xF9, 0xED, 0xF5, 0xE6, 0xF2, 0xE0, 0xEF, 0xDA, 0xEB, 0xD4, 0xE8, 0xCD, 0xE4,
    0xF9, 0x03, 0xF3, 0x07, 0xED, 0x0A, 0xE7, 0x0E, 0xE1, 0x12, 0xDA, 0x15, 0xD4, 0x19, 0xCE, 0x1D,
    // LSB
    0x00, 0x00, 0x00, 0x00, 0xE9, 0xB6, 0x0F, 0xD8, 0xE9, 0x7D, 0x86, 0x0E, 0xE9, 0xB6, 0x0F, 0xD8,
};
#endif

BYTE * code tICM_TABLE_GRAY[] =
{
    tICM_TABLE_GRAY_R,
    tICM_TABLE_GRAY_Y,
    tICM_TABLE_GRAY_G,
    tICM_TABLE_GRAY_C,
    tICM_TABLE_GRAY_B,
    tICM_TABLE_GRAY_M,
};

//--------------------------------------------------
// Code Tables of SixColor
//--------------------------------------------------
SWORD code tSIX_COLOR_U_MAX_8_BRI_COMPENSATE[] =
{
    256, -256, -512, -256, 256, 512,
};

SWORD code tSIX_COLOR_V_MAX_8_BRI_COMPENSATE[] =
{
    512, 512, 0, -512, -512, 0,
};

SWORD code tSIX_COLOR_CTOC_DELTA_UV_DOWN_BRI_COMPENSATE[][2] =
{
    {-512,    0},
    {-256, -512},
    { 256, -512},
    { 512,    0},
    { 256,  512},
    {-256,  512},
};

SWORD code tSIX_COLOR_CTOC_DELTA_UV_UP_BRI_COMPENSATE[][2] =
{
    { 256, -512},
    { 512,    0},
    { 256,  512},
    {-256,  512},
    {-512,    0},
    {-256, -512},
};

SWORD code tSIX_COLOR_CTOC_DELTA_Y_DOWN_BRI_COMPENSATE[] =
{
    143, -81, 49, -130, 80, -51,
};

SWORD code tSIX_COLOR_CTOC_DELTA_Y_UP_BRI_COMPENSATE[] =
{
    79, -131, 81, -46, 131, -80,
};

#if(_SIX_COLOR_ICM_GRAY_LEVEL_CONTROL == _ON)
SWORD code tSIX_COLOR_CTOC_DELTA_Y_DOWN_SAT0_COMPENSATE[] =
{
    -5, -24, -3, 17, 22, 1,
};

SWORD code tSIX_COLOR_CTOC_DELTA_Y_SAT0_COMPENSATE[] =
{
    4, -20, -23, -4, 19, 22,
};

SWORD code tSIX_COLOR_CTOC_DELTA_Y_UP_SAT0_COMPENSATE[] =
{
    53, 1, -20, -21, -1, 19,
};
#endif

//--------------------------------------------------
// Code Tables of SixColor
//--------------------------------------------------
WORD code tSIX_COLOR_DEFAULT_ANGLE[][5] =
{
    {587,  0, 135, 482,  604},
    {1191, 0, 135, 260,  420},
    {1611, 0, 437, 884,  1024},
    {2635, 0, 135, 280,  370},
    {3005, 0, 369, 504,  746},
    {3751, 0, 345, 670,  932}
};

WORD code tSIX_COLOR_U_MAX[][5] =
{
    {1256, 1256, 1024, 3955, 3560},
    {3560, 3560, 3072, 2856, 2630},
    {2630, 2630, 2048, 2643, 2841},
    {2841, 2841, 3072, 3594, 3885},
    {3885, 3885, 1024, 1256, 1584},
    {1584, 1584, 2047, 1609, 1256},
};

//--------------------------------------------------
// Code Tables of SixColor
//--------------------------------------------------
WORD code tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[][5] =
{
    {   0,    0,  722,  722,  722},
    { 722,    0,  604,  604,  604},
    {1326,    0,  722,  722,  722},
    {2048,    0,  722,  722,  722},
    {2770,    0,  604,  604,  604},
    {3374,    0,  722,  722,  722},
};

WORD code tSIX_COLOR_U_MAX_BRI_COMPENSATE[][5] =
{
    {2047, 2047, 1024, 1024, 1024},
    {1024, 1024, 3072, 3072, 3072},
    {3072, 3072, 2048, 2048, 2048},
    {2048, 2048, 3072, 3072, 3072},
    {3072, 3072, 1024, 1024, 1024},
    {1024, 1024, 2047, 2047, 2047},
};
#endif


#if(_ICM_CHAMELEON_FUNCTION == _ON)
//--------------------------------------------------
// Code Tables of SixColor
//--------------------------------------------------
SWORD code tCHAMELEON_U_MAX_8_BRI_COMPENSATE[] =
{
    256, -256, -512, -256, 256, 512,
};

SWORD code tCHAMELEON_V_MAX_8_BRI_COMPENSATE[] =
{
    512, 512, 0, -512, -512, 0,
};

SWORD code tCHAMELEON_Y_BRI_COMPENSATE_SAT[] =
{
    75, 226, 149, 179, 28, 104,
};

WORD code tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[][5] =
{
    {   0,    0,  722,  722,  722},
    { 722,    0,  604,  604,  604},
    {1326,    0,  722,  722,  722},
    {2048,    0,  722,  722,  722},
    {2770,    0,  604,  604,  604},
    {3374,    0,  722,  722,  722},
};

WORD code tCHAMELEON_U_MAX_BRI_COMPENSATE[][5] =
{
    {2047, 2047, 1024, 1024, 1024},
    {1024, 1024, 3072, 3072, 3072},
    {3072, 3072, 2048, 2048, 2048},
    {2048, 2048, 3072, 3072, 3072},
    {3072, 3072, 1024, 1024, 1024},
    {1024, 1024, 2047, 2047, 2047},
};
#endif
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description   : Fill ICM UVOffset/Brightness table
// Input Value   : pICMTable: ICM Table
//                 ucBankNum: Bank Number
//                 ucCMSel: ICM Select
// Output Value  : None
//--------------------------------------------------
void ScalerColorICMLoadTable(EnumSelRegion enumSelRegion, BYTE *pucICMTable, BYTE ucBankNum)
{
    BYTE pucTemp[2] = {0};
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if(pucICMTable != _NULL_POINTER)
    {
        ScalerFlashRead(ucBankNum, &pucICMTable[1], 2, pucTemp);
        ScalerColorICMAdjust(usPage, pucTemp[0], pucTemp[1]);
        ScalerColorICMUVOffsetLoadTable(usPage, pucICMTable, ucBankNum);
    }
    else
    {
        ScalerColorICMAdjust(usPage, 0x00, 0x00);
    }

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        usPage = _REG_MAIN2_PAGE;
        if(pucICMTable != _NULL_POINTER)
        {
            ScalerFlashRead(ucBankNum, &pucICMTable[1], 2, pucTemp);
            ScalerColorICMAdjust(usPage, pucTemp[0], pucTemp[1]);
            ScalerColorICMUVOffsetLoadTable(usPage, pucICMTable, ucBankNum);
        }
        else
        {
            ScalerColorICMAdjust(usPage, 0x00, 0x00);
        }
    }
#endif
}

#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_1)
//--------------------------------------------------
// Description  : Enable ICM double buffer function
// Input Value  : enumSelRegion, ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorICMLocalDBEable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit((P7_D5_ICM_SEL3), ~_BIT1, _BIT1);
        ScalerSetBit((P7_D5_ICM_SEL3 + _REG_MAIN2_PAGE), ~_BIT1, _BIT1);
    }
    else
    {
        ScalerSetBit((P7_D5_ICM_SEL3), ~(_BIT1), 0x00);
        ScalerSetBit((P7_D5_ICM_SEL3 + _REG_MAIN2_PAGE), ~(_BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable ICM double buffer function
// Input Value  : enumSelRegion, ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorICMDisableAllCM(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    // Disable CM0,CM1,CM2,CM3,CM4
    ScalerSetBit((P7_D0_ICM_CONTROL + usPage), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit((P7_D1_ICM_SEL + usPage), ~_BIT3, 0x00);

    ScalerColorICMLocalDBApply(enumSelRegion, enumDBApply);
}

//--------------------------------------------------
// Description  : ICM double buffer function apply
// Input Value  : ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorICMLocalDBApply(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }
    else
    {
        ScalerSetBit((P7_D5_ICM_SEL3 + usPage), ~_BIT0, _BIT0);

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            // Check D domain status before polling
            if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) || (GET_DPLL_POWER_STATUS() == _FALSE))
            {
                return;
            }

            // Wait double buffer apply bit to be cleared
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, (P7_D5_ICM_SEL3 + usPage), (_BIT0), 0) == _FALSE)
            {
                // Disable Display format gen when D domain double buffer timeout
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT0, 0x00);
            }
        }
    }
}
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorInitial(EnumSelRegion enumSelRegion)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_NORMAL_MODE)

    ScalerColorSixColorInitialNormal(usPage);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        usPage = _REG_MAIN2_PAGE;
        ScalerColorSixColorInitialNormal(usPage);
    }
#endif

#elif(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_BRI_COMPENSATE_MODE)

    ScalerColorSixColorInitialBriCompensate(usPage);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        usPage = _REG_MAIN2_PAGE;
        ScalerColorSixColorInitialBriCompensate(usPage);
    }
#endif

#endif
}

//--------------------------------------------------
// Description  : 6 Color ICM adjust
// Input Value  : ucColorIndex --> Color Adjusted Now
//                ucHuePosition --> Hue position after mapping
//                ucSatPosition --> Sat position after mapping
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorAdjust(EnumSelRegion enumSelRegion, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_NORMAL_MODE)

    ScalerColorSixColorAdjustNormal(usPage, ucColorIndex, ucHuePosition, ucSatPosition);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        usPage = _REG_MAIN2_PAGE;
        ScalerColorSixColorAdjustNormal(usPage, ucColorIndex, ucHuePosition, ucSatPosition);
    }
#endif

#elif(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_BRI_COMPENSATE_MODE)

    ScalerColorSixColorAdjustBriCompensate(usPage, ucColorIndex, ucHuePosition, ucSatPosition);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        usPage = _REG_MAIN2_PAGE;
        ScalerColorSixColorAdjustBriCompensate(usPage, ucColorIndex, ucHuePosition, ucSatPosition);
    }
#endif

#endif
}
#endif  // #if(_SIX_COLOR_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Adjust ICM Function
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void ScalerColorICMAdjust(WORD usPage, BYTE ucAdjustOption1, BYTE ucAdjustOption2)
{
//  WORD usPage = ScalerRegionGetRegisterPage(_REG_DDOMAIN_AFTER_BLENDING, enumSelRegion);

    ScalerSetBit(P7_D0_ICM_CONTROL + usPage, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0),
                 (((BYTE)((bit)(ucAdjustOption2 & _Y_CORRECTION_MODE)) << 6) |
                  ((BYTE)((bit)(ucAdjustOption2 & _UV_DELTA_RANGE)) << 5) |
                  ((BYTE)((bit)(ucAdjustOption2 & _CM0_ENABLE)) << 4) |
                  ((BYTE)((bit)(ucAdjustOption2 & _CM1_ENABLE)) << 3) |
                  ((BYTE)((bit)(ucAdjustOption2 & _CM2_ENABLE)) << 2) |
                  ((BYTE)((bit)(ucAdjustOption2 & _CM3_ENABLE)) << 1) |
                  ((BYTE)((bit)(ucAdjustOption2 & _CM4_ENABLE)))));

    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT4 | _BIT3), (((BYTE)((bit)(ucAdjustOption1 & _UV_DELTA_RANGE_EXTEND)) << 4) | ((BYTE)((bit)(ucAdjustOption2 & _CM5_ENABLE)) << 3)));

    // Enable ICM New Mode and UV Offset on Right/Left Buffer
    ScalerSetBit(P7_D4_ICM_SEL2 + usPage, ~_BIT1, _BIT1);
}

//--------------------------------------------------
// Description  : Enable/Disable ICM Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorICMEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P7_D0_ICM_CONTROL, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P7_D0_ICM_CONTROL, ~(_BIT7), 0x00);
    }

#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_1)
    // Enable/Disable ICM locall DB
    ScalerColorICMLocalDBEable(enumOn);
#endif
}

//--------------------------------------------------
// Description  : Adjust ICM Highlight Window Active Region
// Input Value  : enumSelRegion --> OSD Select region
//                enumDBApply
//                bOn --> Enable/Disable the ICM of the OSD select region
// Output Value : None
//--------------------------------------------------
void ScalerColorICMSCMRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    BYTE ucHlwSetting = 0;
    BYTE ucMask = 0;

    if(enumSelRegion == _NON_REGION)
    {
        return;
    }

    ucHlwSetting = ScalerGetByte(P7_D4_ICM_SEL2);

    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_INSIDE_WINDOW:
            ucMask = _BIT7;
            break;

        case _HLW_OUTSIDE_WINDOW:
            ucMask = _BIT6;
            break;

        case _HLW_FULL_WINDOW:
        default:
            ucMask = (_BIT7 | _BIT6);
            break;
    }

    if(bOn == _ON)
    {
        ucHlwSetting &= ~ucMask;
    }
    else
    {
        ucHlwSetting |= ucMask;
    }

    ScalerSetByte(P7_D4_ICM_SEL2, ucHlwSetting);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Adjust ICM Highlight Window SetA/SetB Region by Osd select region
// Input Value  : enumSelRegion --> OSD Select region
//                EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorICMSCMSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerSetBit(P7_D4_ICM_SEL2, ~(_BIT5 | _BIT4), ((BYTE)enumSetSel << 4));
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get ICM HLW Effective Region
// Input Value  : None
// Output Value : EnumHLWSetSel
//--------------------------------------------------
EnumHLWSetSel ScalerColorICMSCMGetEffectiveRegion(void)
{
    return (EnumHLWSetSel)(ScalerGetBit(P7_D4_ICM_SEL2, (_BIT5 | _BIT4)) >> 4);
}

#endif
//--------------------------------------------------
// Description   : Fill ICM table, Enable Local CM, Set adjust option
// Input Value   : pICMTable: ICM Table
//                 ucBankNum: Bank Number
//                 ucCMSel: ICM Select
// Output Value  : None
//--------------------------------------------------
void ScalerColorICMUVOffsetLoadTable(WORD usPage, BYTE *pucICMTable, BYTE ucBankNum)
{
    BYTE ucI = 0;
    BYTE ucCMSel = 0;
    BYTE ucTemp = 0;

    if(pucICMTable != _NULL_POINTER)
    {
        for(ucI = 0; ucI < 7; ucI++)
        {
            ScalerFlashRead(ucBankNum, &pucICMTable[_CMN_INDEX_OFFSET + ucI * _ONE_CM_TABLE_SIZE], 1, &ucTemp);

            switch(ucTemp)
            {
                case _ICM_0:
                    ucCMSel = 0;
                    break;

                case _ICM_1:
                    ucCMSel = 1;
                    break;

                case _ICM_2:
                    ucCMSel = 2;
                    break;

                case _ICM_3:
                    ucCMSel = 3;
                    break;

                case _ICM_4:
                    ucCMSel = 4;
                    break;

                case _ICM_5:
                    ucCMSel = 5;
                    break;

                default:
                    return;
            }

            ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_03_PORT_CMN_MST_00_DU_H);
            ScalerBurstWrite(&pucICMTable[_CMN_UV_TABLE_OFFSET + ucI * _ONE_CM_TABLE_SIZE], _ICM_UVOFFSET_TABLE_SIZE, ucBankNum, P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6F_PORT_CMN_MST_00_01_UV_OFFSET_L);
            ScalerBurstWrite(&pucICMTable[_CMN_UV_LSB_TABLE_OFFSET + ucI * _ONE_CM_TABLE_SIZE], _ICM_UVOFFSET_TABLE_SIZE_LSB, ucBankNum, P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        }
    }
}

//--------------------------------------------------
// Description  : Adjust SCM Function
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void ScalerColorSCMAdjust(WORD usPage, BYTE ucAdjustOption1, BYTE ucAdjustOption2)
{
    ScalerSetByte(P7_CC_SCM_BLOCK_ENABLE + usPage, (((BYTE)((bit)(ucAdjustOption2 & _SCM0_BLOCK0_ENABLE)) << 7) | ((BYTE)((bit)(ucAdjustOption2 & _SCM0_BLOCK1_ENABLE)) << 6) |
                                                    ((BYTE)((bit)(ucAdjustOption2 & _SCM1_BLOCK0_ENABLE)) << 5) | ((BYTE)((bit)(ucAdjustOption2 & _SCM1_BLOCK1_ENABLE)) << 4) |
                                                    ((BYTE)((bit)(ucAdjustOption2 & _SCM2_BLOCK0_ENABLE)) << 3) | ((BYTE)((bit)(ucAdjustOption2 & _SCM2_BLOCK1_ENABLE)) << 2) |
                                                    ((BYTE)((bit)(ucAdjustOption2 & _SCM3_BLOCK0_ENABLE)) << 1) | ((BYTE)((bit)(ucAdjustOption2 & _SCM3_BLOCK1_ENABLE)))));

    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~_BIT4, (BYTE)((bit)(ucAdjustOption1 & _SCMN_SHARE_REG)) << 4);
}

//--------------------------------------------------
// Description   : Fill SCM table
// Input Value   : None
// Output Value  : None
//--------------------------------------------------
void ScalerColorSCMLoadTable(EnumSelRegion enumSelRegion, BYTE *pucSCMTable, BYTE ucBankNum)
{
    BYTE ucI = 0;
    BYTE ucSCMSel = 0;
    BYTE pucTemp[2] = {0};
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if(pucSCMTable != _NULL_POINTER)
    {
        ScalerFlashRead(ucBankNum, &pucSCMTable[1], 2, pucTemp);
        ScalerColorSCMAdjust(usPage, pucTemp[0], pucTemp[1]);

        for(ucI = 0; ucI < 9; ucI++)
        {
            ScalerFlashRead(ucBankNum, &pucSCMTable[_SCMN_INDEX_OFFSET + ucI * (_SCM_TABLE_SIZE + 1)], 1, &pucTemp[0]);

            switch(pucTemp[0])
            {
                case _SCM_0:
                    ucSCMSel = 0;
                    break;

                case _SCM_1:
                    ucSCMSel = 1;
                    break;

                case _SCM_2:
                    ucSCMSel = 2;
                    break;

                case _SCM_3:
                    ucSCMSel = 3;
                    break;

                case _SCM_4:
                    ucSCMSel = 4;
                    break;

                case _SCM_5:
                    ucSCMSel = 5;
                    break;

                case _SCM_6:
                    ucSCMSel = 6;
                    break;

                case _SCM_7:
                    ucSCMSel = 7;
                    break;

                default:
                    return;
            }

            ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucSCMSel);
            ScalerSetByte(P7_CE_SCM_ACCESS_PORT_CONTROL + usPage, 0x00);
            ScalerBurstWrite(&pucSCMTable[_SCMN_TABLE_OFFSET + ucI * (_SCM_TABLE_SIZE + 1)], _SCM_TABLE_SIZE, ucBankNum, P7_CF_SCM_ACCESS_PORT_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        }
    }
    else
    {
        ScalerColorSCMAdjust(usPage, 0x00, 0x00);
    }

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        if(pucSCMTable != _NULL_POINTER)
        {
            usPage = _REG_MAIN2_PAGE;
            ScalerFlashRead(ucBankNum, &pucSCMTable[1], 2, pucTemp);
            ScalerColorSCMAdjust(usPage, pucTemp[0], pucTemp[1]);
            for(ucI = 0; ucI < 9; ucI++)
            {
                ScalerFlashRead(ucBankNum, &pucSCMTable[_SCMN_INDEX_OFFSET + ucI * (_SCM_TABLE_SIZE + 1)], 1, &pucTemp[0]);
                switch(pucTemp[0])
                {
                    case _SCM_0:
                        ucSCMSel = 0;
                        break;
                    case _SCM_1:
                        ucSCMSel = 1;
                        break;
                    case _SCM_2:
                        ucSCMSel = 2;
                        break;
                    case _SCM_3:
                        ucSCMSel = 3;
                        break;
                    case _SCM_4:
                        ucSCMSel = 4;
                        break;
                    case _SCM_5:
                        ucSCMSel = 5;
                        break;
                    case _SCM_6:
                        ucSCMSel = 6;
                        break;
                    case _SCM_7:
                        ucSCMSel = 7;
                        break;
                    default:
                        return;
                }
                ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucSCMSel);
                ScalerSetByte(P7_CE_SCM_ACCESS_PORT_CONTROL + usPage, 0x00);
                ScalerBurstWrite(&pucSCMTable[_SCMN_TABLE_OFFSET + ucI * (_SCM_TABLE_SIZE + 1)], _SCM_TABLE_SIZE, ucBankNum, P7_CF_SCM_ACCESS_PORT_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
            }
        }
        else
        {
            ScalerColorSCMAdjust(usPage, 0x00, 0x00);
        }
    }
#endif
}

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Enable ICM Night Sniper function
// Input Value  : enumSelRegion, ucSaturation, ucLightness, ucDarkOffset
// Output Value : None
//--------------------------------------------------
void ScalerColorICMNightSniperAdjust(EnumSelRegion enumSelRegion, BYTE ucSaturation, BYTE ucLightness, BYTE ucDarkOffset)
{
    BYTE ucIndex = 0;
    WORD usPage = _REG_MAIN1_PAGE;
    WORD usHueByAxis = 0;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        // Every axis hue = 0 start with its color. Change every axis to the same Color, need to calculate equivalent deltaHue
        // ex. when Raxis hue change to usHuePosition; Because Yaxis hue delay (_CHAMELEON_HUE_MAX - (_CHAMELEON_HUE_MAX / 6) * 1) = 250 from Raxis
        // Yaxis deltaHue = (_CHAMELEON_HUE_MAX - (_CHAMELEON_HUE_MAX / 6) * 1) + usHuePosition
        usHueByAxis = (_ICM_NIGHT_SNIPER_HUE_MAX - (_ICM_NIGHT_SNIPER_HUE_MAX / 6) * (WORD)ucIndex) + _ICM_NIGHT_SNIPER_HUE;

        if(usHueByAxis > _ICM_NIGHT_SNIPER_HUE_MAX)
        {
            usHueByAxis = usHueByAxis - _ICM_NIGHT_SNIPER_HUE_MAX;
        }

        ScalerColorChameleonAdjustByAxis(usPage, ucIndex, usHueByAxis, ucSaturation, ucLightness, ucDarkOffset);
    }

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if((enumSelRegion == _FULL_REGION) && (usPage != _REG_MAIN2_PAGE))
    {
        usPage = _REG_MAIN2_PAGE;

        for(ucIndex = 0; ucIndex < 6; ucIndex++)
        {
            // Every axis hue = 0 start with its color. Change every axis to the same Color, need to calculate equivalent deltaHue
            // ex. when Raxis hue change to usHuePosition; Because Yaxis hue delay (_CHAMELEON_HUE_MAX - (_CHAMELEON_HUE_MAX / 6) * 1) = 250 from Raxis
            // Yaxis deltaHue = (_CHAMELEON_HUE_MAX - (_CHAMELEON_HUE_MAX / 6) * 1) + usHuePosition
            usHueByAxis = (_ICM_NIGHT_SNIPER_HUE_MAX - (_ICM_NIGHT_SNIPER_HUE_MAX / 6) * (WORD)ucIndex) + _ICM_NIGHT_SNIPER_HUE;

            if(usHueByAxis > _ICM_NIGHT_SNIPER_HUE_MAX)
            {
                usHueByAxis = usHueByAxis - _ICM_NIGHT_SNIPER_HUE_MAX;
            }

            ScalerColorChameleonAdjustByAxis(usPage, ucIndex, usHueByAxis, ucSaturation, ucLightness, ucDarkOffset);
        }
    }
#endif

    ScalerColorChameleonInitial(enumSelRegion);
}
#endif

#if(_ICM_CHAMELEON_FUNCTION == _ON)
//--------------------------------------------------
// Description  : 6 Color ICM adjust
// Input Value  : ucColorIndex --> Color Adjusted Now
//                ucHuePosition --> Hue position after mapping
//                ucSatPosition --> Sat position after mapping
// Output Value : None
//--------------------------------------------------
void ScalerColorChameleonAdjust(EnumSelRegion enumSelRegion, BYTE ucColorIndex, StructICMChameleonAxisData *pstAxisData, BYTE ucDarkOffset)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerColorChameleonAdjustByAxis(usPage, ucColorIndex, pstAxisData->usICMChameleonHue, pstAxisData->ucICMChameleonSat, pstAxisData->ucICMChameleonLightness, ucDarkOffset);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        usPage = _REG_MAIN2_PAGE;
        ScalerColorChameleonAdjustByAxis(usPage, ucColorIndex, pstAxisData->usICMChameleonHue, pstAxisData->ucICMChameleonSat, pstAxisData->ucICMChameleonLightness, ucDarkOffset);
    }
#endif
}

//--------------------------------------------------
// Description  : 6 Color ICM adjust
// Input Value  : ucColorIndex --> Color Adjusted Now
//                ucHuePosition --> Hue position after mapping
//                ucSatPosition --> Sat position after mapping
// Output Value : None
//--------------------------------------------------
void ScalerColorChameleonAdjustByAxis(WORD usPage, BYTE ucColorIndex, WORD usHuePosition, BYTE ucSatPosition, BYTE ucLightnessPosition, BYTE ucDarkOffset)
{
    BYTE pucCentDeltaUV[16] = {0};
    BYTE ucTargetIndex = 0;
    BYTE ucTargetNextIndex = 0;
    BYTE ucNextIndex = (ucColorIndex == 5) ? 0 : (ucColorIndex + 1);
    BYTE ucPointIndex = 0;
    SWORD shDeltaSat = 0;
    SWORD shDeltaUmax1 = 0;
    SWORD shDeltaVmax1 = 0;
    SWORD shDeltaUmax = 0;
    SWORD shDeltaVmax = 0;
    SWORD shDeltaY = 0;
    SWORD shDeltaY_SAT01 = 0;
    SWORD shDeltaU = 0;
    SWORD shDeltaV = 0;
    BYTE ucIndex = 0;
    WORD usIndex_Left = 0;
    WORD usIndex_Right = 0;
    SWORD shDeltaUmax_Target = 0;
    SWORD shDeltaVmax_Target = 0;
    WORD ustemp_R = 0;
    WORD ustemp_B = 0;
    WORD ustemp_G = 0;
    WORD ustemp_G_modify = 0;
    SWORD shdeltaG = 0;
    WORD usRaw_R = 0;
    WORD usRaw_B = 0;
    WORD usRaw_G = 0;

    // Not Use SCM
    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~_BIT4, 0x00);

    // ucSatPosition : 0~ 100 mapping shDeltaSat: -512 ~ 512
    shDeltaSat = ((SDWORD)-51200 + ((SDWORD)ucSatPosition << 10)) / 100;

    ucIndex = (BYTE)(usHuePosition / _CHAMELEON_HUE_DELTA_STEP);
    usIndex_Left = usHuePosition - ((WORD)ucIndex * _CHAMELEON_HUE_DELTA_STEP);
    usIndex_Right = _CHAMELEON_HUE_DELTA_STEP - usIndex_Left;
    ucTargetIndex = (ucIndex + ucColorIndex) % 6;
    ucTargetNextIndex = (ucIndex + ucColorIndex + 1) % 6;

    shDeltaUmax_Target = (((SDWORD)tCHAMELEON_U_MAX_8_BRI_COMPENSATE[ucTargetIndex] * usIndex_Right) + ((SDWORD)tCHAMELEON_U_MAX_8_BRI_COMPENSATE[ucTargetNextIndex] * usIndex_Left)) / _CHAMELEON_HUE_DELTA_STEP;
    shDeltaVmax_Target = (((SDWORD)tCHAMELEON_V_MAX_8_BRI_COMPENSATE[ucTargetIndex] * usIndex_Right) + ((SDWORD)tCHAMELEON_V_MAX_8_BRI_COMPENSATE[ucTargetNextIndex] * usIndex_Left)) / _CHAMELEON_HUE_DELTA_STEP;
    shDeltaY_SAT01 = (((SDWORD)tCHAMELEON_Y_BRI_COMPENSATE_SAT[ucTargetIndex] * usIndex_Right) + ((SDWORD)tCHAMELEON_Y_BRI_COMPENSATE_SAT[ucTargetNextIndex] * usIndex_Left)) / _CHAMELEON_HUE_DELTA_STEP;

    shDeltaUmax = shDeltaUmax_Target - tCHAMELEON_U_MAX_8_BRI_COMPENSATE[ucColorIndex];
    shDeltaVmax = shDeltaVmax_Target - tCHAMELEON_V_MAX_8_BRI_COMPENSATE[ucColorIndex];

    shDeltaUmax1 = (SDWORD)shDeltaSat * shDeltaUmax_Target >> 9;
    shDeltaVmax1 = (SDWORD)shDeltaSat * shDeltaVmax_Target >> 9;

    shDeltaUmax = (shDeltaUmax1 + shDeltaUmax);
    shDeltaVmax = (shDeltaVmax1 + shDeltaVmax);

    shDeltaUmax_Target = tCHAMELEON_U_MAX_8_BRI_COMPENSATE[ucColorIndex] + shDeltaUmax;
    shDeltaVmax_Target = tCHAMELEON_V_MAX_8_BRI_COMPENSATE[ucColorIndex] + shDeltaVmax;

    // R = (2* u + v) / 4, R = (2* u - v) / 4, G = 255 - max(R,G,B),
    ustemp_R = MAXOF((shDeltaUmax_Target * 2 + shDeltaVmax_Target), 0);
    ustemp_B = MAXOF((shDeltaUmax_Target * 2 - shDeltaVmax_Target), 0);

    ustemp_G = 4 *  MAXOF(((255 * 4) - MAXOF(ustemp_R, ustemp_B)), 0);

    // ucLightnessPosition range 0 ~ 100
    ustemp_G_modify = ustemp_G - (DWORD)(100 - ucLightnessPosition) * ucDarkOffset;

    usRaw_R = MAXOF((tCHAMELEON_U_MAX_8_BRI_COMPENSATE[ucColorIndex] * 2 + tCHAMELEON_V_MAX_8_BRI_COMPENSATE[ucColorIndex]), 0);
    usRaw_B = MAXOF((tCHAMELEON_U_MAX_8_BRI_COMPENSATE[ucColorIndex] * 2 - tCHAMELEON_V_MAX_8_BRI_COMPENSATE[ucColorIndex]), 0);

    usRaw_G = 4 *  MAXOF((255 * 4) - MAXOF(usRaw_R, usRaw_B), 0);

    // compensate = -1 * 4 * (8 * du + dv) / 8
    shdeltaG = ((((SDWORD)shDeltaUmax * 8 + shDeltaVmax) * 4 / 8) + ((SWORD)ustemp_G_modify - usRaw_G));

    shDeltaY = (shdeltaG) >> 4;

    // shDelatY range -255 ~ 255
    shDeltaY = MAXOF(-255, MINOF(255, shDeltaY));

    if(ucSatPosition < 50)
    {
        shDeltaY = (shDeltaY - ((255 - shDeltaY_SAT01) * (50 - ucSatPosition) / 50));
    }

    shDeltaY = MAXOF(-255, MINOF(255, shDeltaY));

    shDeltaUmax = (shDeltaUmax) >> 3;
    shDeltaVmax = (shDeltaVmax) >> 3;


    for(ucPointIndex = 0; ucPointIndex < 8; ucPointIndex++)
    {
        shDeltaU = (shDeltaUmax * (ucPointIndex + 1)) >> 3;
        shDeltaV = (shDeltaVmax * (ucPointIndex + 1)) >> 3;

        shDeltaU = MAXOF(-128, MINOF(127, shDeltaU));
        shDeltaV = MAXOF(-128, MINOF(127, shDeltaV));

        pucCentDeltaUV[ucPointIndex << 1] = shDeltaU & 0xFF;
        pucCentDeltaUV[(ucPointIndex << 1) + 1] = shDeltaV & 0xFF;
    }

    ScalerColorChameleonLoad(usPage, shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_CENTER_BRI_COMPENSATE);
    ScalerColorChameleonLoad(usPage, shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE);
    ScalerColorChameleonLoad(usPage, shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE);
    ScalerColorChameleonLoad(usPage, shDeltaY, pucCentDeltaUV, ucNextIndex, _SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE);
    ScalerColorChameleonLoad(usPage, shDeltaY, pucCentDeltaUV, ucNextIndex, _SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE);

#if(_HW_ICM_TABLE_TYPE == _ICM_GEN_3)
    // Set LSB to 0
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucColorIndex);
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6F_PORT_CMN_MST_00_01_UV_OFFSET_L);

    for(ucIndex = 0; ucIndex < _SIXCOLOR_TO_GRAY_TABLE_SIZE_LSB_BRI_COMPENSATE; ucIndex++)
    {
        ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
    }

    // Set dy LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_87_PORT_CMN_AXIS_DELY_L);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
#endif
}

//--------------------------------------------------
// Description   : Fill 6 Color ICM Data
// Input Value   : pucICMData --> Point to ICM uvoffset
//                 ucCMSel --> Color selected
//                   ucLoadSelect --> Axis selected
// Output Value  : None
//--------------------------------------------------
void ScalerColorChameleonLoad(WORD usPage, SWORD shDeltaY, BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect)
{
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);

    switch(ucLoadSelect)
    {
        case _SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_33_PORT_CMN_RBUF_00_DU_H);
            break;

        case _SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_13_PORT_CMN_RWID_00_DU_H);
            break;

        case _SIX_COLOR_CENTER_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_03_PORT_CMN_MST_00_DU_H);
            break;

        case _SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;

        case _SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_43_PORT_CMN_LBUF_00_DU_H);
            break;

        default:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;
    }

    ScalerBurstWrite(pucICMData, _SIXCOLOR_TABLE_SIZE_AXIS_BRI_COMPENSATE, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    switch(ucLoadSelect)
    {
        case _SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE:
            return;

        case _SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6B_PORT_CMN_R_AXIS_DELY_H);
            break;

        case _SIX_COLOR_CENTER_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_69_PORT_CMN_M_AXIS_DELY_H);
            break;

        case _SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6D_PORT_CMN_L_AXIS_DELY_H);
            break;

        case _SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE:
            return;

        default:
            return;
    }

    ScalerSetByte(P7_D3_ICM_DATA + usPage, (BYTE)((shDeltaY >> 8) & 0xFF));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, (BYTE)(shDeltaY & 0xFF));
}

//--------------------------------------------------
// Description  : Set range for one CM
// Input Value  : ucCMSel --> Color selected
//                shRBuffer --> Right buffer hue
//                shRWidth --> Right range
//                shAngle --> Master Range
//                shLWidth --> Left Range
//                shLBuffer --> Left Buffer Range
// Output Value : None
//--------------------------------------------------
void ScalerColorChameleonSetAngleRB(WORD usPage, BYTE ucCMSel)
{
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_53_PORT_CMN_MST_UMAX_H);

    // Master Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_CENTER_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_CENTER_BRI_COMPENSATE]) & 0xFF));

    // Rightwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE]) & 0xFF));

    // Leftwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE]) & 0xFF));

    // Rightbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE]) & 0xFF));

    // Leftbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tCHAMELEON_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE]) & 0xFF));

    // Right Buffer Hue
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE] & 0xFF);

    // Right Width Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE] & 0xFF);

    // Master Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_CENTER_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_CENTER_BRI_COMPENSATE] & 0xFF);

    // Left Width Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE] & 0xFF);

    // Left Buffer Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tCHAMELEON_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE] & 0xFF);

#if(_HW_ICM_TABLE_TYPE == _ICM_GEN_3)
    // Set Master/Rightwidth/Leftwidth/Rightbuffer/Leftbuffer LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_83_PORT_CMN_MST_WID_UMAX_L);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);

    // Set Right Buffer Hue/Right Width Range/Master Range/Left Width Range/Left Buffer Range LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_85_PORT_CMN_HUE_SET1_L);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorChameleonInitial(EnumSelRegion enumSelRegion)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerColorChameleonInitialAdjust(usPage);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        usPage = _REG_MAIN2_PAGE;
        ScalerColorChameleonInitialAdjust(usPage);
    }
#endif
}
//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorChameleonInitialAdjust(WORD usPage)
{
    BYTE ucCmIndex = 0;

    // Enable ICM
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT4 | _BIT3), _BIT4 | _BIT3);

    // Enable New ICM mode
    ScalerSetBit(P7_D4_ICM_SEL2 + usPage, ~_BIT1, _BIT1);

    // Enable ICM function
    ScalerSetByte(P7_D0_ICM_CONTROL + usPage, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Close SCM
    ScalerSetByte(P7_CC_SCM_BLOCK_ENABLE + usPage, 0x00);
    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~_BIT4, 0x00);

    for(ucCmIndex = 0; ucCmIndex < 6; ucCmIndex++)
    {
        // Enable ICM Brightness
        ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCmIndex);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
        ScalerSetByte(P7_D3_ICM_DATA + usPage, 0xBF);
        ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x0E);

        ScalerColorChameleonSetAngleRB(usPage, ucCmIndex);
    }
}
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : 6 Color ICM adjust
// Input Value  : ucColorIndex --> Color Adjusted Now
//                ucHuePosition --> Hue position after mapping
//                ucSatPosition --> Sat position after mapping
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorAdjustNormal(WORD usPage, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition)
{
    BYTE pucCentDeltaUV[16];
    BYTE ucLastIndex = 0;
    BYTE ucAxis = 0;
    BYTE ucPointIndex = 0;
    SWORD shDeltaSat = 0;
    SWORD shDeltaUmax1 = 0;
    SWORD shDeltaVmax1 = 0;
    SWORD shDeltaUmax = 0;
    SWORD shDeltaVmax = 0;
    SWORD shDeltaU = 0;
    SWORD shDeltaV = 0;
    BYTE ucTurningPositiongUp = 0;
    BYTE ucTurningPositiongDown = 0;
    BYTE ucLSBDataIndex = 0;
//  WORD usPage = ScalerRegionGetRegisterPage(_REG_DDOMAIN_AFTER_BLENDING, enumSelRegion);

    ucLastIndex = (ucColorIndex == 0) ? 5 : (ucColorIndex - 1);
    // Not Use SCM
    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~_BIT4, 0x00);

    if(ucSatPosition != 0)
    {
        ucTurningPositiongUp = tL_TURNING_POSITION_UP[ucColorIndex];
        ucTurningPositiongDown = tR_TURNING_POSITION_DOWN[ucColorIndex];

        // Delta Saturation = (-512 * 200 + ((512 - (-512)) * ucSatPosition)) / 200
        shDeltaSat = ((SDWORD)-102400 + ((SDWORD)ucSatPosition << 10)) / 200;

        for(ucAxis = 1; ucAxis < 4; ucAxis++)
        {
            // Calculate Delta Hue of one Axis

            if(ucAxis == _SIX_COLOR_RIGHTWIDTH)
            {
                if((ucHuePosition > 50) && (ucHuePosition <= ucTurningPositiongDown))
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][0] * (ucHuePosition - 50) / (ucTurningPositiongDown - 50);
                    shDeltaVmax = (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][1] * (ucHuePosition - 50) / (ucTurningPositiongDown - 50);
                }
                else if(ucHuePosition > ucTurningPositiongDown)
                {
                    shDeltaUmax = tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][0] + (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][2] * (ucHuePosition - ucTurningPositiongDown) / (100 - ucTurningPositiongDown);
                    shDeltaVmax = tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][1] + (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][3] * (ucHuePosition - ucTurningPositiongDown) / (100 - ucTurningPositiongDown);
                }
                else if(ucHuePosition < 50)
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_UP[ucColorIndex][0] * (50 - ucHuePosition) / 50;
                    shDeltaVmax = (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_UP[ucColorIndex][1] * (50 - ucHuePosition) / 50;
                }
                else
                {
                    shDeltaUmax = 0;
                    shDeltaVmax = 0;
                }
            }
            else if(ucAxis == _SIX_COLOR_CENTER)
            {
                if(ucHuePosition > 50)
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_DOWN[ucColorIndex][0] * (ucHuePosition - 50) / 50;
                    shDeltaVmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_DOWN[ucColorIndex][1] * (ucHuePosition - 50) / 50;
                }
                else if(ucHuePosition < 50)
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_UP[ucColorIndex][0] * (50 - ucHuePosition) / 50;
                    shDeltaVmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_UP[ucColorIndex][1] * (50 - ucHuePosition) / 50;
                }
                else
                {
                    shDeltaUmax = 0;
                    shDeltaVmax = 0;
                }
            }
            else
            {
                if(ucHuePosition > 50)
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_DOWN[ucColorIndex][0] * (ucHuePosition - 50) / 50;
                    shDeltaVmax = (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_DOWN[ucColorIndex][1] * (ucHuePosition - 50) / 50;
                }
                else if((ucHuePosition < 50) && (ucHuePosition >= ucTurningPositiongUp))
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][0] * (50 - ucHuePosition) / (50 - ucTurningPositiongUp);
                    shDeltaVmax = (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][1] * (50 - ucHuePosition) / (50 - ucTurningPositiongUp);
                }
                else if(ucHuePosition < ucTurningPositiongUp)
                {
                    shDeltaUmax = tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][0] + (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][2] * (ucTurningPositiongUp - ucHuePosition) / ucTurningPositiongUp;
                    shDeltaVmax = tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][1] + (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][3] * (ucTurningPositiongUp - ucHuePosition) / ucTurningPositiongUp;
                }
                else
                {
                    shDeltaUmax = 0;
                    shDeltaVmax = 0;
                }
            }

            shDeltaUmax1 = tSIX_COLOR_U_MAX_8[ucColorIndex][ucAxis - 1] + shDeltaUmax;
            shDeltaVmax1 = tSIX_COLOR_V_MAX_8[ucColorIndex][ucAxis - 1] + shDeltaVmax;

            shDeltaUmax1 = ((SDWORD)shDeltaSat * shDeltaUmax1) >> 9;
            shDeltaVmax1 = ((SDWORD)shDeltaSat * shDeltaVmax1) >> 9;

            shDeltaUmax = (shDeltaUmax1 + shDeltaUmax) >> 3;
            shDeltaVmax = (shDeltaVmax1 + shDeltaVmax) >> 3;

            for(ucPointIndex = 0; ucPointIndex < 8; ucPointIndex++)
            {
                shDeltaU = (shDeltaUmax * (ucPointIndex + 1)) >> 3;
                shDeltaV = (shDeltaVmax * (ucPointIndex + 1)) >> 3;

                shDeltaU = MAXOF(-128, MINOF(127, shDeltaU));
                shDeltaV = MAXOF(-128, MINOF(127, shDeltaV));

                pucCentDeltaUV[ucPointIndex << 1] = shDeltaU & 0xFF;
                pucCentDeltaUV[(ucPointIndex << 1) + 1] = shDeltaV & 0xFF;
            }

            ScalerColorSixColorICMLoad(usPage, pucCentDeltaUV, ucColorIndex, ucAxis);

            if(ucAxis == _SIX_COLOR_RIGHTWIDTH)
            {
                ScalerColorSixColorICMLoad(usPage, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_RIGHTBUFFER);
                ScalerColorSixColorICMLoad(usPage, pucCentDeltaUV, ucLastIndex, _SIX_COLOR_LEFTBUFFER);
            }
        }

        // Set LSB to 0
        ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucColorIndex);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6F_PORT_CMN_MST_00_01_UV_OFFSET_L);

        for(ucLSBDataIndex = 0; ucLSBDataIndex < 16; ucLSBDataIndex++)
        {
            ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
        }

        ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucLastIndex);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_7F_PORT_CMN_LBUF_00_01_UV_OFFSET_L);

        for(ucLSBDataIndex = 0; ucLSBDataIndex < 4; ucLSBDataIndex++)
        {
            ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
        }
    }
    else
    {
        // Load Code Table
        ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucColorIndex);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_03_PORT_CMN_MST_00_DU_H);
        ScalerBurstWrite(tICM_TABLE_GRAY[ucColorIndex], _SIXCOLOR_TABLE_SIZE_MSB, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6F_PORT_CMN_MST_00_01_UV_OFFSET_L);
        ScalerBurstWrite(&tICM_TABLE_GRAY[ucColorIndex][_SIXCOLOR_TABLE_SIZE_MSB], _SIXCOLOR_TABLE_SIZE_LSB, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucLastIndex);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_43_PORT_CMN_LBUF_00_DU_H);
        ScalerBurstWrite(&tICM_TABLE_GRAY[ucColorIndex][16], 16, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_7F_PORT_CMN_LBUF_00_01_UV_OFFSET_L);
        ScalerBurstWrite(&tICM_TABLE_GRAY[ucColorIndex][68], 4, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
}

//--------------------------------------------------
// Description   : Fill 6 Color ICM Data
// Input Value   : pucICMData --> Point to ICM uvoffset
//                 ucCMSel --> Color selected
//                   ucLoadSelect --> Axis selected
// Output Value  : None
//--------------------------------------------------
void ScalerColorSixColorICMLoad(WORD usPage, BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect)
{
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);

    switch(ucLoadSelect)
    {
        // Rightbuffer
        case _SIX_COLOR_RIGHTBUFFER:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_33_PORT_CMN_RBUF_00_DU_H);
            break;

        // Rightwidth
        case _SIX_COLOR_RIGHTWIDTH:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_13_PORT_CMN_RWID_00_DU_H);
            break;

        // Center
        case _SIX_COLOR_CENTER:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_03_PORT_CMN_MST_00_DU_H);
            break;

        // Leftwidth
        case _SIX_COLOR_LEFTWIDTH:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;

        // Leftbuffer
        case _SIX_COLOR_LEFTBUFFER:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_43_PORT_CMN_LBUF_00_DU_H);
            break;

        default:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;
    }

    ScalerBurstWrite(pucICMData, _SIXCOLOR_TABLE_SIZE_AXIS, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
}

//--------------------------------------------------
// Description  : 6 Color ICM adjust
// Input Value  : ucColorIndex --> Color Adjusted Now
//                ucHuePosition --> Hue position after mapping
//                ucSatPosition --> Sat position after mapping
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorAdjustBriCompensate(WORD usPage, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition)
{
    BYTE pucCentDeltaUV[16] = {0};
    BYTE ucNextIndex = (ucColorIndex == 5) ? 0 : (ucColorIndex + 1);
    BYTE ucPointIndex = 0;
    SWORD shDeltaSat = 0;
    SWORD shDeltaUmax1 = 0;
    SWORD shDeltaVmax1 = 0;
    SWORD shDeltaUmax = 0;
    SWORD shDeltaVmax = 0;
    SWORD shDeltaY = 0;
    SWORD shDeltaU = 0;
    SWORD shDeltaV = 0;
#if(_SIX_COLOR_ICM_GRAY_LEVEL_CONTROL == _ON)
    SWORD shDeltaYSat0 = 0;
#endif

    // Not Use SCM
    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~_BIT4, 0x00);


    // Delta Saturation = (-512 * 200 + ((512 - (-512)) * ucSatPosition)) / 200
    shDeltaSat = ((SDWORD)-102400 + ((SDWORD)ucSatPosition << 10)) / 200;

    if(ucHuePosition > 50)
    {
        shDeltaUmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_DOWN_BRI_COMPENSATE[ucColorIndex][0] * (ucHuePosition - 50) / 50;
        shDeltaVmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_DOWN_BRI_COMPENSATE[ucColorIndex][1] * (ucHuePosition - 50) / 50;
        shDeltaY = (SDWORD)tSIX_COLOR_CTOC_DELTA_Y_DOWN_BRI_COMPENSATE[ucColorIndex] * (ucHuePosition - 50) / 50;
    }
    else if(ucHuePosition < 50)
    {
        shDeltaUmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_UP_BRI_COMPENSATE[ucColorIndex][0] * (50 - ucHuePosition) / 50;
        shDeltaVmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_UP_BRI_COMPENSATE[ucColorIndex][1] * (50 - ucHuePosition) / 50;
        shDeltaY = (SDWORD)tSIX_COLOR_CTOC_DELTA_Y_UP_BRI_COMPENSATE[ucColorIndex] * (50 - ucHuePosition) / 50;
    }
    else
    {
        shDeltaUmax = 0;
        shDeltaVmax = 0;
        shDeltaY = 0;
    }

#if(_SIX_COLOR_ICM_GRAY_LEVEL_CONTROL == _ON)
    // ucSatPosition range = 0 ~ 200, when sat < 100, start to proggressive change shDeltaY to make (ucSatPosition = 0) match specific lightness
    if(ucSatPosition < 100)
    {
        if(ucHuePosition > 50)
        {
            shDeltaYSat0 = (((SDWORD)tSIX_COLOR_CTOC_DELTA_Y_DOWN_SAT0_COMPENSATE[ucColorIndex] * (ucHuePosition - 50)) + ((SDWORD)tSIX_COLOR_CTOC_DELTA_Y_SAT0_COMPENSATE[ucColorIndex] * (100 - ucHuePosition))) / 50;
        }
        else if(ucHuePosition < 50)
        {
            shDeltaYSat0 = (((SDWORD)tSIX_COLOR_CTOC_DELTA_Y_UP_SAT0_COMPENSATE[ucColorIndex] * (50 - ucHuePosition)) + ((SDWORD)tSIX_COLOR_CTOC_DELTA_Y_SAT0_COMPENSATE[ucColorIndex] * ucHuePosition)) / 50;
        }
        else
        {
            shDeltaYSat0 = tSIX_COLOR_CTOC_DELTA_Y_SAT0_COMPENSATE[ucColorIndex];
        }

        shDeltaY = shDeltaY + ((SDWORD)shDeltaYSat0 * shDeltaSat >> 9);

        shDeltaY = MAXOF(-255, MINOF(255, shDeltaY));
    }
#endif

    shDeltaUmax1 = tSIX_COLOR_U_MAX_8_BRI_COMPENSATE[ucColorIndex] + shDeltaUmax;
    shDeltaVmax1 = tSIX_COLOR_V_MAX_8_BRI_COMPENSATE[ucColorIndex] + shDeltaVmax;

    shDeltaUmax1 = (SDWORD)shDeltaSat * shDeltaUmax1 >> 9;
    shDeltaVmax1 = (SDWORD)shDeltaSat * shDeltaVmax1 >> 9;

    shDeltaUmax = (shDeltaUmax1 + shDeltaUmax) >> 3;
    shDeltaVmax = (shDeltaVmax1 + shDeltaVmax) >> 3;

    for(ucPointIndex = 0; ucPointIndex < 8; ucPointIndex++)
    {
        shDeltaU = (shDeltaUmax * (ucPointIndex + 1)) >> 3;
        shDeltaV = (shDeltaVmax * (ucPointIndex + 1)) >> 3;

        shDeltaU = MAXOF(-128, MINOF(127, shDeltaU));
        shDeltaV = MAXOF(-128, MINOF(127, shDeltaV));

        pucCentDeltaUV[ucPointIndex << 1] = shDeltaU & 0xFF;
        pucCentDeltaUV[(ucPointIndex << 1) + 1] = shDeltaV & 0xFF;
    }

    ScalerColorSixColorICMLoadBriCompensate(usPage, shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_CENTER_BRI_COMPENSATE);
    ScalerColorSixColorICMLoadBriCompensate(usPage, shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE);
    ScalerColorSixColorICMLoadBriCompensate(usPage, shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE);
    ScalerColorSixColorICMLoadBriCompensate(usPage, shDeltaY, pucCentDeltaUV, ucNextIndex, _SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE);
    ScalerColorSixColorICMLoadBriCompensate(usPage, shDeltaY, pucCentDeltaUV, ucNextIndex, _SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE);

#if(_HW_ICM_TABLE_TYPE == _ICM_GEN_3)
    // Set LSB to 0
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucColorIndex);
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6F_PORT_CMN_MST_00_01_UV_OFFSET_L);

    for(BYTE ucIndex = 0; ucIndex < _SIXCOLOR_TO_GRAY_TABLE_SIZE_LSB_BRI_COMPENSATE; ucIndex++)
    {
        ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
    }

    // Set dy LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_87_PORT_CMN_AXIS_DELY_L);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
#endif
}

//--------------------------------------------------
// Description   : Fill 6 Color ICM Data
// Input Value   : pucICMData --> Point to ICM uvoffset
//                 ucCMSel --> Color selected
//                   ucLoadSelect --> Axis selected
// Output Value  : None
//--------------------------------------------------
void ScalerColorSixColorICMLoadBriCompensate(WORD usPage, SWORD shDeltaY, BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect)
{
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);

    switch(ucLoadSelect)
    {
        case _SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_33_PORT_CMN_RBUF_00_DU_H);
            break;

        case _SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_13_PORT_CMN_RWID_00_DU_H);
            break;

        case _SIX_COLOR_CENTER_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_03_PORT_CMN_MST_00_DU_H);
            break;

        case _SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;

        case _SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_43_PORT_CMN_LBUF_00_DU_H);
            break;

        default:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;
    }

    ScalerBurstWrite(pucICMData, _SIXCOLOR_TABLE_SIZE_AXIS_BRI_COMPENSATE, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    switch(ucLoadSelect)
    {
        case _SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE:
            return;

        case _SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6B_PORT_CMN_R_AXIS_DELY_H);
            break;

        case _SIX_COLOR_CENTER_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_69_PORT_CMN_M_AXIS_DELY_H);
            break;

        case _SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE:
            ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_6D_PORT_CMN_L_AXIS_DELY_H);
            break;

        case _SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE:
            return;

        default:
            return;
    }

    ScalerSetByte(P7_D3_ICM_DATA + usPage, (BYTE)((shDeltaY >> 8) & 0xFF));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, (BYTE)(shDeltaY & 0xFF));
}

//--------------------------------------------------
// Description  : Set range for one CM
// Input Value  : ucCMSel --> Color selected
//                shRBuffer --> Right buffer hue
//                shRWidth --> Right range
//                shAngle --> Master Range
//                shLWidth --> Left Range
//                shLBuffer --> Left Buffer Range
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorSetAngleRB(WORD usPage, BYTE ucCMSel)
{
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_53_PORT_CMN_MST_UMAX_H);

    // Master Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_CENTER]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_CENTER]) & 0xFF));

    // Rightwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_RIGHTWIDTH]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_RIGHTWIDTH]) & 0xFF));

    // Leftwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_LEFTWIDTH]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_LEFTWIDTH]) & 0xFF));

    // Rightbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_RIGHTBUFFER]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_RIGHTBUFFER]) & 0xFF));

    // Leftbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_LEFTBUFFER]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_LEFTBUFFER]) & 0xFF));

    // Right Buffer Hue
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_RIGHTBUFFER] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_RIGHTBUFFER] & 0xFF);

    // Right Width Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_RIGHTWIDTH] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_RIGHTWIDTH] & 0xFF);

    // Master Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_CENTER] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_CENTER] & 0xFF);

    // Left Width Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_LEFTWIDTH] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_LEFTWIDTH] & 0xFF);

    // Left Buffer Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_LEFTBUFFER] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_LEFTBUFFER] & 0xFF);

#if(_HW_ICM_TABLE_TYPE == _ICM_GEN_3)
    // Set Master/Rightwidth/Leftwidth/Rightbuffer/Leftbuffer LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_83_PORT_CMN_MST_WID_UMAX_L);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);

    // Set Right Buffer Hue/Right Width Range/Master Range/Left Width Range/Left Buffer Range LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_85_PORT_CMN_HUE_SET1_L);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorInitialNormal(WORD usPage)
{
    BYTE ucCmIndex = 0;

    // Enable ICM
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT4 | _BIT3), _BIT4 | _BIT3);

    // Enable New ICM mode
    ScalerSetBit(P7_D4_ICM_SEL2 + usPage, ~_BIT1, _BIT1);

    // Enable ICM function
    ScalerSetByte(P7_D0_ICM_CONTROL + usPage, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Close SCM
    ScalerSetByte(P7_CC_SCM_BLOCK_ENABLE + usPage, 0x00);
    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~_BIT4, 0x00);

    for(ucCmIndex = 0; ucCmIndex < 6; ucCmIndex++)
    {
        // Disable ICM Brightness
        ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCmIndex);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
        ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);

        ScalerColorSixColorSetAngleRB(usPage, ucCmIndex);
    }
}

//--------------------------------------------------
// Description  : Set range for one CM
// Input Value  : ucCMSel --> Color selected
//                shRBuffer --> Right buffer hue
//                shRWidth --> Right range
//                shAngle --> Master Range
//                shLWidth --> Left Range
//                shLBuffer --> Left Buffer Range
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorSetAngleRBBriCompensate(WORD usPage, BYTE ucCMSel)
{
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_53_PORT_CMN_MST_UMAX_H);

    // Master Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_CENTER_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_CENTER_BRI_COMPENSATE]) & 0xFF));

    // Rightwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE]) & 0xFF));

    // Leftwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE]) & 0xFF));

    // Rightbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE]) & 0xFF));

    // Leftbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA + usPage, ((tSIX_COLOR_U_MAX_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE]) & 0xFF));

    // Right Buffer Hue
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE] & 0xFF);

    // Right Width Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE] & 0xFF);

    // Master Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_CENTER_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_CENTER_BRI_COMPENSATE] & 0xFF);

    // Left Width Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE] & 0xFF);

    // Left Buffer Range
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, tSIX_COLOR_DEFAULT_ANGLE_BRI_COMPENSATE[ucCMSel][_SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE] & 0xFF);

#if(_HW_ICM_TABLE_TYPE == _ICM_GEN_3)
    // Set Master/Rightwidth/Leftwidth/Rightbuffer/Leftbuffer LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_83_PORT_CMN_MST_WID_UMAX_L);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);

    // Set Right Buffer Hue/Right Width Range/Master Range/Left Width Range/Left Buffer Range LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_85_PORT_CMN_HUE_SET1_L);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
    ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorInitialBriCompensate(WORD usPage)
{
    BYTE ucCmIndex = 0;

    // Enable ICM
    ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT4 | _BIT3), _BIT4 | _BIT3);

    // Enable New ICM mode
    ScalerSetBit(P7_D4_ICM_SEL2 + usPage, ~_BIT1, _BIT1);

    // Enable ICM function
    ScalerSetByte(P7_D0_ICM_CONTROL + usPage, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Close SCM
    ScalerSetByte(P7_CC_SCM_BLOCK_ENABLE + usPage, 0x00);
    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT + usPage, ~_BIT4, 0x00);

    for(ucCmIndex = 0; ucCmIndex < 6; ucCmIndex++)
    {
        // Enable ICM Brightness
        ScalerSetBit(P7_D1_ICM_SEL + usPage, ~(_BIT2 | _BIT1 | _BIT0), ucCmIndex);
        ScalerSetByte(P7_D2_ICM_ADDR + usPage, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
        ScalerSetByte(P7_D3_ICM_DATA + usPage, 0xBF);
        ScalerSetByte(P7_D3_ICM_DATA + usPage, 0x0E);

        ScalerColorSixColorSetAngleRBBriCompensate(usPage, ucCmIndex);
    }
}
#endif  // End of #if(_SIX_COLOR_SUPPORT == _ON)
#endif  // End of #if(_COLOR_IP_ICM == _ON)

