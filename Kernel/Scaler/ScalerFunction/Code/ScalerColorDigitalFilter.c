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
// ID Code      : ScalerColorDigitalFilter.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
#if(_DIGITAL_FILTER_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
//-------------------------------------------------
// Description  : Set digital filter
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterAdjust(void)
{
    // Disable NR
    ScalerColorDigitalFilterNRDisableAdjust();

#if(_DIG_FILTER_NSMEAR_SUPPORT == _ON)
    // Set negative smear  parameter
    ScalerColorDigitalFilterNSmearAdjust(_DIG_FILTER_NSMEAR_THD, _DIG_FILTER_NSMEAR_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_NSMEAR_ENABLE == _ENABLE)

#if(_DIG_FILTER_PSMEAR_SUPPORT == _ON)
    // Set positive smear  parameter
    ScalerColorDigitalFilterPSmearAdjust(_DIG_FILTER_PSMEAR_THD, _DIG_FILTER_PSMEAR_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_PSMEAR_ENABLE == _ENABLE)

#if(_DIG_FILTER_NRING_SUPPORT == _ON)
    // Set negative ring  parameter
    ScalerColorDigitalFilterNRingAdjust(_DIG_FILTER_NRING_THD, _DIG_FILTER_NRING_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_NRING_ENABLE == _ENABLE)

#if(_DIG_FILTER_PRING_SUPPORT == _ON)
    // Set positive ring  parameter
    ScalerColorDigitalFilterPRingAdjust(_DIG_FILTER_PRING_THD, _DIG_FILTER_PRING_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_PRING_ENABLE == _ENABLE)

#if(_DIG_FILTER_EXTENSION_SUPPORT == _ON)
    // Use extension data
    ScalerColorDigitalFilterExtensionAdjust();
#endif  // End of #if(_DIG_FILTER_EXTENSION_ENABLE == _ENABLE)
}

//-------------------------------------------------
// Description  : Set digital filter Enable
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterEnable(EnumFunctionOnOFF enumOn)
{
    BYTE ucCtrlReg = 0;

    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));
        ucCtrlReg = ScalerGetByte(P0_99_DIGITAL_FILTER_PORT);

        // write extension data separately to avoid autoinc
        ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));
        ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, (ucCtrlReg | (_BIT7 | _BIT6 | _BIT5)));
    }
    else
    {
        ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));
        ucCtrlReg = ScalerGetByte(P0_99_DIGITAL_FILTER_PORT);

        // write extension data separately to avoid autoinc
        ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));
        ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, (ucCtrlReg & (~(_BIT7 | _BIT6 | _BIT5))));
    }
}

//--------------------------------------------------
// Description  : Set New Phase
// Input Value  : BGR Gain
// Output Value : None
//--------------------------------------------------
void ScalerColorDigitalFilterEnhancePhaseAdjust(BYTE *pucBGRGain)
{
    BYTE ucI = 0;
    BYTE ucTHD1 = 0;
    WORD usTHD2 = 0;

    for(ucI = _DIG_FILTER_BGAIN; ucI < _DIG_FILTER_RGB_CHANNEL; ucI++)
    {
        if(pucBGRGain[ucI] < _DIG_FILTER_DELTA)
        {
            pucBGRGain[ucI] = 0;
            ucTHD1 = 0xDF;
        }
        else
        {
            usTHD2 = (WORD)(_DIG_FILTER_DELTA) * 512 / pucBGRGain[ucI];

            if(usTHD2 > 250)
            {
                pucBGRGain[ucI] = 0;
                ucTHD1 = 0xDF;
            }
            else if(usTHD2 > (_DIG_FILTER_THRESHOLD1 + 32))
            {
                ucTHD1 = usTHD2 - 32;
            }
            else
            {
                ucTHD1 = _DIG_FILTER_THRESHOLD1;
            }
        }

        // Enable Port Access
        switch(ucI)
        {
            case _DIG_FILTER_BGAIN:

                ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

                break;

            case _DIG_FILTER_GGAIN:

                ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT4 | _BIT0));

                break;

            case _DIG_FILTER_RGAIN:

                ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));

                break;

            default:

                break;
        }

        // Set Threshold1
        ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, ucTHD1);

        // Set Offset for Threshold2
        ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, _DIG_FILTER_OFFSET);

        // Set Gain2
        ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, pucBGRGain[ucI]);

        // Disable Port Access
        ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
    }

    // Enable Phase Mode
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, 0x80);

    // Select New Phase Mode
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT4 | _BIT0));
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, 0x80);
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
}

//-------------------------------------------------
// Description  : Set Extension
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterExtensionAdjust(void)
{
    BYTE ucCtrlReg = 0;

    // Use extension data
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));
    ucCtrlReg = ScalerGetByte(P0_99_DIGITAL_FILTER_PORT);

    // write extension data separately to avoid autoinc
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, (ucCtrlReg | _BIT4));
}

//-------------------------------------------------
// Description  : Disable NR
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterNRDisableAdjust(void)
{
    // Disable NR
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT7);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, 0x00);
}

//-------------------------------------------------
// Description  : Set NRing
// Input Value  : THD,Div
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterNRingAdjust(BYTE ucTHD, BYTE ucDIV)
{
    // Set negative ring  parameter
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT6);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, ((ucTHD << 4) | (ucDIV << 2) | _BIT7));
}

//-------------------------------------------------
// Description  : Set NSmear
// Input Value  : THD,Div
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterNSmearAdjust(BYTE ucTHD, BYTE ucDIV)
{
    // Set negative smear  parameter
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT5);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, ((ucTHD << 4) | (ucDIV << 2) | _BIT7));
}

//-------------------------------------------------
// Description  : Set PRing
// Input Value  : THD,Div
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterPRingAdjust(BYTE ucTHD, BYTE ucDIV)
{
    // Set positive ring  parameter
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT4));
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, ((ucTHD << 4) | (ucDIV << 2) | _BIT7));
}

//-------------------------------------------------
// Description  : Set PSmear
// Input Value  : THD,Div
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterPSmearAdjust(BYTE ucTHD, BYTE ucDIV)
{
    // Set positive smear  parameter
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, ((ucTHD << 4) | (ucDIV << 2) | _BIT7));
}
#endif // #if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
#endif // #if(_DIGITAL_FILTER_SUPPORT == _ON)

#if(_RINGING_FILTER_FUNCTION == _ON)
#if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
//--------------------------------------------------
// Description  : Adjust Ringing Filter
// Input Value  : Offset Coef
// Output Value : None
//--------------------------------------------------
void ScalerColorRingingFilterAdjust(BYTE *pucOffsetCoef)
{
    BYTE ucTHD = 0;
    BYTE ucRFEn = 0;

    if(*pucOffsetCoef > 0)
    {
        ucTHD = (WORD)_RINGING_FILTER_DELTA * 128 / (*pucOffsetCoef);
    }
    else
    {
        ucTHD = 255;
    }

    if(ucTHD < _RINGING_FILTER_THRESHOLD)
    {
        ucTHD = _RINGING_FILTER_THRESHOLD;
    }
    else if(ucTHD > 255 - (1 << _RINGING_FILTER_THD_RANGE))
    {
        ucTHD = 255 - (1 << _RINGING_FILTER_THD_RANGE);
    }

    ucRFEn = 1;

    ScalerSetByte(P25_A1_RFILTER_THD, ucTHD);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, _RINGING_FILTER_THD_RANGE);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, (*pucOffsetCoef));
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, _RINGING_JUMP_DIFF_THD_UB);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, _RINGING_JUMP_DIFF_THD_LB);
    ScalerSetBit(P25_A0_RFILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5), ((ucRFEn << 7) | _BIT6 | (_RINGING_JUMP_JUDGEMENT_EN << 5)));
}

//--------------------------------------------------
// Description  : Adjust Ringing Filter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorRingingFilterOff(void)
{
    ScalerSetBit(P25_A0_RFILTER_CTRL, ~_BIT7, 0x00);
}
#endif // #if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
#endif // #if(_RINGING_FILTER_FUNCTION == _ON)
#endif // #if(_VGA_SUPPORT == _ON)

