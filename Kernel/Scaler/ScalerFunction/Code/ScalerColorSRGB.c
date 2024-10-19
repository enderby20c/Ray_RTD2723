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
// ID Code      : ScalerColorSRGB.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"

#if(_COLOR_IP_SRGB == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tCosCurveAngle[] = {0, 6, 12, 18, 24, 30, 37, 44, 52, 60, 68, 78, 90};
WORD code tCosCurveValue[] = {4096, 4074, 4006, 3896, 3742, 3547, 3271, 2946, 2522, 2048, 1534, 852, 0}; // to be edit

BYTE code tSinCurveAngle[] = {0, 6, 12, 18, 24, 30, 37, 44, 52, 60, 68, 78, 90};
WORD code tSinCurveValue[] = {0, 428, 852, 1266, 1666, 2048, 2465, 2845, 3228, 3547, 3798, 4006, 4096}; // to be edit


// 1->1024
SWORD code tYUV2RGB[][3] =
{
    { 4096,       0,    5744,  },
    { 4096,   -1408,   -2924,  },
    { 4096,    7260,       0,  }
};


// 1->1024
SWORD code tRGB2YUV[][3] =
{
    {  1224,    2405,    467,  },
    {  -691,   -1357,   2048,  },
    {  2048,   -1715,   -333,  }
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Calculate Cos(x)
// Input Value  : shDegree x (in 360 unit)
// Output Value : SWORD Cos(x)
//--------------------------------------------------
SWORD ScalerColorSRGBCosine(SWORD shDegree)
{
    BYTE ucI = 0;
    BYTE ucQuadrant = 0;
    BYTE ucDegreeTemp = 0;
    BYTE ucDegreeSpan = 0;
    SWORD shCosValueSpan = 0;
    SWORD shCosValue = 0;

    if(shDegree < 0)
    {
        shDegree += 360;
    }

    shDegree = shDegree % 360;

    // Locate degree on which quadrant
    ucQuadrant = (BYTE)(shDegree / 90);
    ucQuadrant++;

    switch(ucQuadrant)
    {
        // First quadrant
        case 1:

            shDegree = shDegree;

            break;

        // Second quadrant
        case 2:

            shDegree = 180 - shDegree;

            break;

        // Third quadrant
        case 3:

            shDegree = shDegree - 180;

            break;

        // Forth quadrant
        case 4:

            shDegree = 360 - shDegree;

            break;

        default:

            break;
    }

    // Locate degree on which quadrant
    if(shDegree <= tCosCurveAngle[0])
    {
        shCosValue = tCosCurveValue[0];
    }
    else
    {
        for(ucI = 1; tCosCurveAngle[ucI] < shDegree; ucI++) {}

        ucI--;

        ucDegreeTemp = shDegree - tCosCurveAngle[ucI];
        ucDegreeSpan = tCosCurveAngle[ucI + 1] - tCosCurveAngle[ucI];
        shCosValueSpan = tCosCurveValue[ucI + 1] - tCosCurveValue[ucI];
        shCosValue = tCosCurveValue[ucI] + (SWORD)ucDegreeTemp * shCosValueSpan / ucDegreeSpan;
    }

    if((ucQuadrant == 2) || (ucQuadrant == 3))
    {
        shCosValue = shCosValue * (-1);
    }

    return shCosValue;
}

//--------------------------------------------------
// Description  : Calculate Sin(x)
// Input Value  : shDegree x (in 360 unit)
// Output Value : SWORD Sin(x)
//--------------------------------------------------
SWORD ScalerColorSRGBSine(SWORD shDegree)
{
    BYTE ucI = 0;
    BYTE ucQuadrant = 0;
    BYTE ucDegreeTemp = 0;
    BYTE ucDegreeSpan = 0;
    WORD usSinValueSpan = 0;
    SWORD shSinValue = 0;


    if(shDegree < 0)
    {
        shDegree += 360;
    }

    shDegree = shDegree % 360;

    // Locate degree on which quadrant
    ucQuadrant = (BYTE)(shDegree / 90);
    ucQuadrant++;

    switch(ucQuadrant)
    {
        // First quadrant
        case 1:

            shDegree = shDegree;

            break;

        // Second quadrant
        case 2:

            shDegree = 180 - shDegree;

            break;

        // Third quadrant
        case 3:

            shDegree = shDegree - 180;

            break;

        // Forth quadrant
        case 4:

            shDegree = 360 - shDegree;

            break;

        default:

            break;
    }

    // Locate degree on which quadrant
    if(shDegree <= tSinCurveAngle[0])
    {
        shSinValue = tSinCurveValue[0];
    }
    else
    {
        for(ucI = 1; tSinCurveAngle[ucI] < shDegree; ucI++) {}

        ucI--;

        ucDegreeTemp = shDegree - tSinCurveAngle[ucI];
        ucDegreeSpan = tSinCurveAngle[ucI + 1] - tSinCurveAngle[ucI];
        usSinValueSpan = tSinCurveValue[ucI + 1] - tSinCurveValue[ucI];
        shSinValue = tSinCurveValue[ucI] + (WORD)ucDegreeTemp * usSinValueSpan / ucDegreeSpan;
    }

    if((ucQuadrant == 3) || (ucQuadrant == 4))
    {
        shSinValue = shSinValue * (-1);
    }

    return shSinValue;
}

//--------------------------------------------------
// Description  : Do matrix multiply(3x3)  C = A*B
// Input Value  : shArrayA, shArrayB
// Output Value : shArrayC
//--------------------------------------------------
void ScalerColorSRGBMatrixMultiply(SWORD(*ppshArrayA)[3], SWORD(*ppshArrayB)[3], SWORD(*ppshArrayC)[3])
{
    BYTE ucI = 0;
    BYTE ucJ = 0;

    for(ucJ = 0; ucJ < 3; ucJ++)
    {
        for(ucI = 0; ucI < 3; ucI++)
        {
            PDATA_DWORD(ucI) = (((SDWORD)ppshArrayA[ucI][0] * ppshArrayB[0][ucJ] + 2) >> 4) +
                               (((SDWORD)ppshArrayA[ucI][1] * ppshArrayB[1][ucJ] + 2) >> 4) +
                               (((SDWORD)ppshArrayA[ucI][2] * ppshArrayB[2][ucJ] + 2) >> 4);
        }

        for(ucI = 0; ucI < 3; ucI++)
        {
            ppshArrayC[ucI][ucJ] = (SWORD)((PDATA_DWORD(ucI) + 128) >> 8);
        }
    }
}

//--------------------------------------------------
// Description  : Set global Hue&Sat
// Input Value  : SelRegion, DeltaHue(-180~180), DeltaSat(0-330)
// Default Value: Delta Hue = 0, Delta Sat = 100;
// Notice !! Rightnow the Hue/Sat value is saved to NVRAM as BYTE, if you
// want to expand the Range, please edit relative functions and parameters.
// Output Value : pColorMatrix(3x3, set to SRGB Matrix)
//--------------------------------------------------
void ScalerColorSRGBSetGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shDeltaHue, WORD usDeltaSat)
{
    SWORD ppshTempBuff[3][3] = {{0}};

    if(_TRUE)
    {
        SWORD ppshMATRIX[3][3] = {{0}};

        // 1->1024
        ppshMATRIX[0][0] = 4096;
        ppshMATRIX[0][1] = 0;
        ppshMATRIX[0][2] = 0;
        ppshMATRIX[1][0] = 0;
        ppshMATRIX[1][1] = (DWORD)usDeltaSat * 4096 / 100;
        ppshMATRIX[1][2] = 0;
        ppshMATRIX[2][0] = 0;
        ppshMATRIX[2][1] = 0;
        ppshMATRIX[2][2] = ppshMATRIX[1][1];

        ScalerColorSRGBMatrixMultiply(ppshMATRIX, tRGB2YUV, ppshTempBuff);

        ppshMATRIX[0][0] = 4096;
        ppshMATRIX[0][1] = 0;
        ppshMATRIX[0][2] = 0;
        ppshMATRIX[1][0] = 0;
        ppshMATRIX[1][1] = ScalerColorSRGBCosine(shDeltaHue);
        ppshMATRIX[1][2] = (-1) * ScalerColorSRGBSine(shDeltaHue);
        ppshMATRIX[2][0] = 0;
        ppshMATRIX[2][1] = (-1) * ppshMATRIX[1][2];
        ppshMATRIX[2][2] = ppshMATRIX[1][1];

        ScalerColorSRGBMatrixMultiply(ppshMATRIX, ppshTempBuff, ppshTempBuff);
    }

    ScalerColorSRGBMatrixMultiply(tYUV2RGB, ppshTempBuff, ppshTempBuff);

    if(_TRUE)
    {
        BYTE pucColorMatrix[24] = {0};

        // set 1+RR,  1+GG, 1+BB
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            for(pData[1] = 0; pData[1] < 3; pData[1]++)
            {
                if(pData[0] == pData[1])
                {
                    ppshTempBuff[pData[0]][pData[1]] -= 4096; // 12bit data = 4096; 6369
                }

                if(ppshTempBuff[pData[0]][pData[1]] >= 0)
                {
                    ppshTempBuff[pData[0]][pData[1]] = ((ppshTempBuff[pData[0]][pData[1]] + 4) / 8);
                }
                else
                {
                    ppshTempBuff[pData[0]][pData[1]] = ((ppshTempBuff[pData[0]][pData[1]] - 4) / 8);
                }

                if(ppshTempBuff[pData[0]][pData[1]] > 2047)
                {
                    ppshTempBuff[pData[0]][pData[1]] = 2047;
                }
                else if(ppshTempBuff[pData[0]][pData[1]] < -2048)  // 2.9 = 2048
                {
                    ppshTempBuff[pData[0]][pData[1]] = -2048;
                }

                // Set sign byteXXH
                pucColorMatrix[2 * (3 * pData[0] + pData[1])] = (ppshTempBuff[pData[0]][pData[1]] < 0) ? 1 : 0;  // [0] sign
                pucColorMatrix[2 * (3 * pData[0] + pData[1])] += (((WORD)ppshTempBuff[pData[0]][pData[1]] & 0x07) << 5); // [7:5] bit2~0

                // Set data byte XXL
                pucColorMatrix[2 * (3 * pData[0] + pData[1]) + 1] = ((WORD)ppshTempBuff[pData[0]][pData[1]] >> 3) & 0xFF;// [7:0] bit10~3

            }
        }

        for(pData[0] = 18; pData[0] < 24; pData[0]++)
        {
            pucColorMatrix[pData[0]] = 0;
        }

        ScalerColorSRGBAdjust(enumSelRegion, pucColorMatrix, _SRGB_3_BIT_SHIFT_LEFT);
    }
}

#if(_HW_SRGB_DB_GEN_SEL == _SRGB_GEN_1)
//--------------------------------------------------
// Description  : Initial SRGB Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSRGBInitial(void)
{
    ScalerSetBit(P0_62_SRGB_CTRL, ~(_BIT6 | _BIT0), _BIT0); // Enable sRGB coefficient & precision DB
    ScalerSetBit(P40_62_SRGB_CTRL_SETB, ~(_BIT6 | _BIT0), _BIT0); // Enable sRGB coefficient & precision DB
}
#endif

//--------------------------------------------------
// Description  : Adjust SRGB function
// Input Value  : SelRegion
//                SRGB Matrix
//                SRGB Precision
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerColorSRGBAdjust(EnumSelRegion enumSelRegion, BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif


    // Clear Waiting flag
    ScalerSetBit(P0_62_SRGB_CTRL + usPage, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P0_62_SRGB_CTRL + usPage, ~_BIT6, _BIT6); // Reset Port

    if(ScalerTimerPollingFlagProc(2, P0_62_SRGB_CTRL + usPage, _BIT6, 0) == _FALSE) // pollling till Reset port address finished
    {
        return _FALSE;
    }

    ScalerSetBit(P0_62_SRGB_CTRL + usPage, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00); // Write sequence

#if(_HW_SRGB_DB_GEN_SEL == _SRGB_GEN_0)
    if(ScalerGetBit(P9_A1_INPUT_GAMMA_CTRL_SETA + usPage, _BIT5) == _BIT5)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }
#endif

    ScalerBurstWrite(pucSRGBArray, _SRGB_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_63_SRGB_ACCESS_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    ScalerSetBit(P0_68_SRGB_PRECISION + usPage, ~(_BIT7 | _BIT6 | _BIT5), (enumPrecision << 5)); // Precision

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        // Clear Waiting flag
        ScalerSetBit(P40_62_SRGB_CTRL_SETB, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P40_62_SRGB_CTRL_SETB, ~_BIT6, _BIT6); // Reset Port

        if(ScalerTimerPollingFlagProc(2, P40_62_SRGB_CTRL_SETB, _BIT6, 0) == _FALSE) // pollling till Reset port address finished
        {
            return _FALSE;
        }

        ScalerSetBit(P40_62_SRGB_CTRL_SETB, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00); // Write sequence

#if(_HW_SRGB_DB_GEN_SEL == _SRGB_GEN_0)
        if(ScalerGetBit(P49_A1_INPUT_GAMMA_CTRL_SETB, _BIT5) == _BIT5)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        }
#endif

        ScalerBurstWrite(pucSRGBArray, _SRGB_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_63_SRGB_ACCESS_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

        ScalerSetBit(P40_68_SRGB_PRECISION_SETB, ~(_BIT7 | _BIT6 | _BIT5), (enumPrecision << 5)); // Precision

        ScalerSetBit(P40_62_SRGB_CTRL_SETB, ~(_BIT7 | _BIT6), _BIT7);   // no apply none, always effective on dvs
    }
#endif

    ScalerSetBit(P0_62_SRGB_CTRL + usPage, ~(_BIT7 | _BIT6), _BIT7);   // no apply none, always effective on dvs

    return _TRUE;
}

//--------------------------------------------------
// Description  : Enable/Disable SRGB function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorSRGBEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P0_62_SRGB_CTRL, ~(_BIT6 | _BIT2), _BIT2);
    }
    else
    {
        ScalerSetBit(P0_62_SRGB_CTRL, ~(_BIT6 | _BIT2), 0x00);
    }
}

//--------------------------------------------------
// Description  : Turn On/Off SRGB Region
// Input Value  : EnumSelRegion enumSelRegion, EnumDBApply DBApply, bit bOn
// Output Value : None
//--------------------------------------------------
void ScalerColorSRGBRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)  // Mask
{
    BYTE ucHlwSetting = ScalerGetByte(P0_68_SRGB_PRECISION);
    BYTE ucMask = 0;

    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_INSIDE_WINDOW:
            ucMask = _BIT3;
            break;

        case _HLW_OUTSIDE_WINDOW:
            ucMask = _BIT2;
            break;

        default:
            ucMask = (_BIT3 | _BIT2);
            break;
    }

    if(bOn == _TRUE)
    {
        ucHlwSetting &= ~ucMask;
    }
    else
    {
        ucHlwSetting |= ucMask;
    }

    ScalerSetByte(P0_68_SRGB_PRECISION, ucHlwSetting);

    // HLW Double Buffer
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Set SRGB HLW Effective window
// Input Value  : EnumSelRegion enumSelRegion, EnumDBApply DBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorSRGBSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerSetBit(P0_68_SRGB_PRECISION, ~(_BIT7 | _BIT1 | _BIT0), (BYTE)enumSetSel);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#endif
//--------------------------------------------------
// Description  : Get SRGB current precision
// Input Value  : EnumSelRegion enumSelRegion
// Output Value : EnumSrgbPrecision
//--------------------------------------------------
EnumSrgbPrecision ScalerColorSRGBGetPrecision(EnumSelRegion enumSelRegion)
{
    EnumSrgbPrecision enumPrecision = _SRGB_1_BIT_SHIFT_LEFT;
    WORD usPage = _REG_MAIN1_PAGE;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif
    enumPrecision = ScalerGetBit((P0_68_SRGB_PRECISION + usPage), (_BIT6 | _BIT5)) >> 5;
    return enumPrecision;
}
#endif  // End of #if(_COLOR_IP_SRGB == _ON)

