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
// ID Code      : Led_Driver_Common.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include _USER_FUNCTION_INCLUDE

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of debug I2C command type
//--------------------------------------------------
#define _DEBUG_I2C_SLAVE                            2
#define _DEBUG_I2C_SUB                              1
#define _DEBUG_I2C_DATA                             3

//--------------------------------------------------
// Device Address
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_DEVICE_ADDRESS_DEBUG     0x1A

//--------------------------------------------------
// Adjust pwm
//--------------------------------------------------
#define _CONV_MATRIX_SIZE                           5
#define _Y_AVG_BLEND_RATIO                          200


//--------------------------------------------------
// extro info
//--------------------------------------------------
#define _INFO_1_LOW_THD                             230
#define _INFO_1_HIGH_THD                            254


//****************************************************************************
// MACROS
//****************************************************************************


//****************************************************************************
// STRUCT
//****************************************************************************


//****************************************************************************
// TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Backlight
// Input Value  : usBacklight: back-light level
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverBacklight(WORD usBacklight)
{
    UserCommonSpiDimmingSetPwmValueToAllZone(usBacklight);
    UserCommonSpiDimmingManualApplyUpdateSync();
}
//--------------------------------------------------
// Description  : For user adjust final PWM
// Input Value  :
// Output Value :
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverModifiedPWM(WORD *pusBlendPWM, WORD *pusHistogramPWM, WORD *pusSmoothPWM, WORD *pusYavg, WORD usMinBlendPWMValue)
{
    BYTE uckernelRadius = _CONV_MATRIX_SIZE / 2;
    BYTE ppucMatrix[_CONV_MATRIX_SIZE][_CONV_MATRIX_SIZE] =
    {
        {10,  10,  10,  10,  10,},
        {10,  10,  10,  10,  10,},
        {10,  10,  16,  10,  10,},
        {10,  10,  10,  10,  10,},
        {10,  10,  10,  10,  10,},
    };
    BYTE ppucMatrixDark[_CONV_MATRIX_SIZE][_CONV_MATRIX_SIZE] =
    {
        {0,  0,  0,  0,  0,},
        {0,  0,  14,  0,  0,},
        {0,  14,  200,  14,  0,},
        {0,  0,  14,  0,  0,},
        {0,  0,  0,  0,  0,},
    };
    BYTE (*ppucMatrixApply)[_CONV_MATRIX_SIZE] = ppucMatrix;
    WORD pusBackUpPWM[_LOCAL_DIMMING_TOTAL_REGION] = {0};
    DWORD ulSum = 0;
    pusSmoothPWM = pusSmoothPWM;
#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
    if(GET_LOCAL_DIMMING_CASE() != _LOCAL_DIMMING_ENERGYSAVER)
#endif
    {
        for(WORD usI = 0; usI < _LOCAL_DIMMING_TOTAL_REGION; usI++)
        {
            pusBlendPWM[usI] = (((DWORD)pusHistogramPWM[usI] * _Y_AVG_BLEND_RATIO) + ((DWORD)pusYavg[usI] * (1024 - _Y_AVG_BLEND_RATIO))) / 1024;
        }
    }
    memcpy(pusBackUpPWM, pusBlendPWM, sizeof(pusBackUpPWM));

    for(SBYTE chY = 0; chY < _LOCAL_DIMMING_PANEL_REGION_VERTICAL; chY++)
    {
        for(SBYTE chX = 0; chX < _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL; chX++)
        {
            if(pusBackUpPWM[chY * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + chX] <= usMinBlendPWMValue)
            {
                ppucMatrixApply = ppucMatrixDark;
            }
            else
            {
                ppucMatrixApply = ppucMatrix;
            }
            ulSum = 0;
            for(SBYTE chKY = -uckernelRadius; chKY <= uckernelRadius; chKY++)
            {
                for(SBYTE chKX = -uckernelRadius; chKX <= uckernelRadius; chKX++)
                {
                    BYTE ucCopyX = 0;
                    BYTE ucCopyY = 0;
                    if(((chY + chKY) >= 0) && ((chY + chKY) < _LOCAL_DIMMING_PANEL_REGION_VERTICAL) && ((chX + chKX) >= 0) && ((chX + chKX) < _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL))
                    {
                        ulSum += pusBackUpPWM[(chY + chKY) * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + (chX + chKX)] * ppucMatrixApply[chKY + uckernelRadius][chKX + uckernelRadius];
                    }
                    else
                    {
                        if((chX + chKX) < 0)
                        {
                            ucCopyX = 0;
                        }
                        else if((chX + chKX) >= _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL)
                        {
                            ucCopyX = _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL - 1;
                        }
                        else
                        {
                            ucCopyX = (chX + chKX);
                        }
                        if((chY + chKY) < 0)
                        {
                            ucCopyY = 0;
                        }
                        else if((chY + chKY) >= _LOCAL_DIMMING_PANEL_REGION_VERTICAL)
                        {
                            ucCopyY = _LOCAL_DIMMING_PANEL_REGION_VERTICAL - 1;
                        }
                        else
                        {
                            ucCopyY = (chY + chKY);
                        }
                        ulSum += pusBackUpPWM[ucCopyY * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + ucCopyX] * ppucMatrixApply[chKY + uckernelRadius][chKX + uckernelRadius];
                    }
                }
            }
            ulSum = ulSum / 256;
            pusBlendPWM[chY * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + chX] = ulSum;
        }
    }
}
//--------------------------------------------------
// Description  : For user adjust final PWM
// Input Value  :
// Output Value :
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverModifiedPWMExtroInfo(WORD *pusBlendPWM, WORD usHistogramPWM, WORD usExtroInfo0, WORD usExtroInfo1)
{
    BYTE ucMaxBlend = 0;
    BYTE ucMinBlend = 0;
    BYTE ucMaxBlendFactorHight = 64;
    BYTE ucMinBlendFactorHight = 64;
    WORD usMinBlendPWMValue = 32;
    if((usHistogramPWM == 0) && (usExtroInfo0 != 0))
    {
        if(usExtroInfo1 >= _INFO_1_HIGH_THD)
        {
            ucMaxBlend = ucMaxBlendFactorHight;
        }
        else if(usExtroInfo1 <= _INFO_1_LOW_THD)
        {
            ucMaxBlend = 0;
        }
        else
        {
            ucMaxBlend = (usExtroInfo1 - _INFO_1_LOW_THD) * ucMaxBlendFactorHight / (_INFO_1_HIGH_THD - _INFO_1_LOW_THD);
        }

        *pusBlendPWM = ((DWORD)(*pusBlendPWM) * (1000 - ucMaxBlend) + (DWORD)usExtroInfo0 * ucMaxBlend) / 1000;
    }
    else if(usHistogramPWM != 0)
    {
        if(usExtroInfo1 >= _INFO_1_HIGH_THD)
        {
            ucMinBlend = ucMinBlendFactorHight;
        }
        else if(usExtroInfo1 <= _INFO_1_LOW_THD)
        {
            ucMinBlend = 0;
        }
        else
        {
            ucMinBlend = (usExtroInfo1 - _INFO_1_LOW_THD) * ucMinBlendFactorHight / (_INFO_1_HIGH_THD - _INFO_1_LOW_THD);
        }
        *pusBlendPWM = ((DWORD)(*pusBlendPWM) * (1000 - ucMinBlend) + (DWORD)usMinBlendPWMValue * ucMinBlend) / 1000;
    }
}
#endif
