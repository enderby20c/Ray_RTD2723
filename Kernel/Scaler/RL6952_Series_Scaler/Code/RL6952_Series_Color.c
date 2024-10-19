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
// ID Code      : RL6952_Series_Color.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_COLOR__

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
#if(_COLOR_IP_420_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable / Disable 420To422 for P0 source
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P0Enable(EnumFunctionOnOFF enumFunctionOnOFF)
{
    if(enumFunctionOnOFF == _FUNCTION_ON)
    {
        ScalerSetBit(P31_D0_YUV420TO422_CTL_PATH0_1, ~_BIT6, _BIT6);
        ScalerSetBit(P31_D1_YUV420TO422_PATH0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0)); // Set FIFO start point = 7

        // FC path reset
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT4, _BIT4);
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT4, 0x00);

        ScalerSetBit(P31_D1_YUV420TO422_PATH0, ~(_BIT7 | _BIT5 | _BIT4), _BIT7); // Enable 420 function
        ScalerSetBit(P31_D1_YUV420TO422_PATH0, ~(_BIT6 | _BIT5 | _BIT4), _BIT6); // Enable FIFO
        ScalerSetBit(P31_D1_YUV420TO422_PATH0, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4)); // Clear underflow/overflow flag
    }
    else // _FUNCTION_OFF
    {
        ScalerSetBit(P31_D0_YUV420TO422_CTL_PATH0_1, ~_BIT1, 0x00); // Disable double pixel mode
        ScalerSetBit(P31_D1_YUV420TO422_PATH0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00); // Disable 420 function & FIFO
    }
}

//--------------------------------------------------
// Description  : Enable / Disable 420To422 for P2 source
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P2Enable(EnumFunctionOnOFF enumFunctionOnOFF)
{
    if(enumFunctionOnOFF == _FUNCTION_ON)
    {
        ScalerSetBit(P31_E0_YUV420TO422_CTL_PATH2_3, ~_BIT6, _BIT6);
        ScalerSetBit(P31_E1_YUV420TO422_PATH2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0)); // Set FIFO start point = 7

        // FC path reset
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT6, _BIT6);
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT6, 0x00);

        ScalerSetBit(P31_E1_YUV420TO422_PATH2, ~(_BIT7 | _BIT5 | _BIT4), _BIT7); // Enable 420 function
        ScalerSetBit(P31_E1_YUV420TO422_PATH2, ~(_BIT6 | _BIT5 | _BIT4), _BIT6); // Enable FIFO
        ScalerSetBit(P31_E1_YUV420TO422_PATH2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4)); // Clear underflow/overflow flag
    }
    else
    {
        ScalerSetBit(P31_E0_YUV420TO422_CTL_PATH2_3, ~_BIT1, 0x00);
        ScalerSetBit(P31_E1_YUV420TO422_PATH2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00); // Disable 420 function & FIFO
    }
}

//--------------------------------------------------
// Description  : Enable / Disable 420To422 double pixel for P0 source
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P0DoublePixelEnable(EnumFunctionOnOFF enumFunctionOnOFF)
{
    if(enumFunctionOnOFF == _FUNCTION_ON)
    {
        // Enable 420 double pixel mode
        ScalerSetBit(P31_D0_YUV420TO422_CTL_PATH0_1, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable 420 double pixel mode
        ScalerSetBit(P31_D0_YUV420TO422_CTL_PATH0_1, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable / Disable 420To422 double pixel for P2 source
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P2DoublePixelEnable(EnumFunctionOnOFF enumFunctionOnOFF)
{
    if(enumFunctionOnOFF == _FUNCTION_ON)
    {
        // Enable 420 double pixel mode
        ScalerSetBit(P31_E0_YUV420TO422_CTL_PATH2_3, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable 420 double pixel mode
        ScalerSetBit(P31_E0_YUV420TO422_CTL_PATH2_3, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : 420To422 parameter setting for P0 source
// Input Value  : enumInputPort -> target input port
//                usHStart --> target H start
//                usHWidth --> target H width
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P0Setting(WORD usHStart, WORD usHWidth)
{
    // set 420 HStart and HWidth
    ScalerSetBit(P31_D3_YUV420TO422_HSTM0_PATH0_1, ~(_BIT5 | _BIT4 | _BIT3), (HIBYTE(usHStart) & 0x07) << 3);
    ScalerSetByte(P31_D4_YUV420TO422_HSTL0_PATH0_1, LOBYTE(usHStart));
    ScalerSetBit(P31_D6_YUV420TO422_HWIDM0_PATH0_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (HIBYTE(usHWidth) & 0x0F) << 4);
    ScalerSetByte(P31_D7_YUV420TO422_HWIDL0_PATH0_1, LOBYTE(usHWidth));
}

//--------------------------------------------------
// Description  : 420To422 parameter setting for P2 source
// Input Value  : enumInputPort -> target input port
//                usHStart --> target H start
//                usHWidth --> target H width
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P2Setting(WORD usHStart, WORD usHWidth)
{
    // set 420 HStart and HWidth
    ScalerSetBit(P31_E3_YUV420TO422_HSTM0_PATH2_3, ~(_BIT5 | _BIT4 | _BIT3), (HIBYTE(usHStart) & 0x07) << 3);
    ScalerSetByte(P31_E4_YUV420TO422_HSTL0_PATH2_3, LOBYTE(usHStart));
    ScalerSetBit(P31_E6_YUV420TO422_HWIDM0_PATH2_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (HIBYTE(usHWidth) & 0x0F) << 4);
    ScalerSetByte(P31_E7_YUV420TO422_HWIDL0_PATH2_3, LOBYTE(usHWidth));
}
#endif

#if(_COLOR_IP_I_DITHER == _ON)
//--------------------------------------------------
// Description  : Get IDither Table Set Num
// Input Value  : None
// Output Value : Table Set Num
//--------------------------------------------------
BYTE ScalerColorIDitherGetTableSetNum(void)
{
    if(_HW_IDITHER_TABLE_SET_NUM == 2)
    {
        return (ScalerPowerGetIDomainS1PowerCutStatus() == _POWER_CUT_ON) ? 1 : 2;
    }

    return 1;
}
#endif // End of #if(_COLOR_IP_I_DITHER == _ON)

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
//--------------------------------------------------
// Description  : Check if can use Margin Block Control, allow block over case
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerColorLocalContrastMarginBlockControlAvailable(void)
{
    return _TRUE;
}
#endif
#endif // End of #if(_COLOR_IP_LOCAL_CONTRAST == _ON)

