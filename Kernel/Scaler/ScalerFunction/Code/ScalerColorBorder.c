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
// ID Code      : ScalerColorBorder.c
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
#if(_COLOR_IP_BORDER_WIN == _ON)
//--------------------------------------------------
// Description  : Adjust PIPPBPBlending Border width and color
// Input Value  : enumBorderWin, ucBorderWidth, ucRed, ucGreen, ucBlue, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorBorderAdjust(EnumBorderWin enumBorderWin, BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply)
{
    // Set PIPPBPBlending's _BORDER_WIN1,_BORDER_WIN2   Border
    BYTE ucWinAddDelta = 0x00;

    if(enumBorderWin == _BORDER_WIN2)
    {
        ucWinAddDelta = 0x0D;
    }

    ScalerSetByte(P80_C8_BW1_BORDER_WIDTH + ucWinAddDelta, (ucBorderWidth & 0x1F));
    ScalerSetByte(P80_C9_BW1_BORDER_RED + ucWinAddDelta, (ucRed & 0xFF));
    ScalerSetByte(P80_CA_BW1_BORDER_GRN + ucWinAddDelta, (ucGreen & 0xFF));
    ScalerSetByte(P80_CB_BW1_BORDER_BLU + ucWinAddDelta, (ucBlue & 0xFF));

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust PIPPBPBlending Border enable
// Input Value  : enumBorderWin, bTopBorderEn, bBottomBorderEn, bLeftBorderEn, bRightBorderEn, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorBorderEnable(EnumBorderWin enumBorderWin, bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn, EnumDBApply enumDBApply)
{
    // Set PIPPBPBlending's_BORDER_WIN1,_BORDER_WIN2  enable
    BYTE ucWinAddDelta = 0x00;
    bit bEnable = ((bTopBorderEn == 1) || (bBottomBorderEn == 1) || (bLeftBorderEn == 1) || (bRightBorderEn == 1));

    if(enumBorderWin == _BORDER_WIN2)
    {
        ucWinAddDelta = 0x0D;
    }

    ScalerSetBit(P80_CC_BW1_BORDER_EN + ucWinAddDelta, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (bLeftBorderEn ? 0 : _BIT7) | (bRightBorderEn ? 0 : _BIT6) | (bTopBorderEn ? 0 : _BIT5) | (bBottomBorderEn ? 0 : _BIT4) | (bEnable ? _BIT0 : 0));

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust PIPPBPBlending Border Position
// Input Value  : enumBorderWin, usHPos, usHWidth, usVPos, usVHeight, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorBorderPositionAdjust(EnumBorderWin enumBorderWin, WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply)
{
    // Set PIPPBPBlending's _BORDER_WIN1,_BORDER_WIN2  Positon
    BYTE ucWinAddDelta = 0x00;

    if(enumBorderWin == _BORDER_WIN2)
    {
        ucWinAddDelta = 0x0D;
    }

    ScalerSetByte(P80_C0_BW1_HOR_START_H + ucWinAddDelta, (usHPos >> 8) & 0x3F);
    ScalerSetByte(P80_C1_BW1_HOR_START_L + ucWinAddDelta, usHPos & 0xFF);
    ScalerSetByte(P80_C2_BW1_HOR_END_H + ucWinAddDelta, ((usHPos + usHWidth) >> 8) & 0x3F);
    ScalerSetByte(P80_C3_BW1_HOR_END_L + ucWinAddDelta, (usHPos + usHWidth) & 0xFF);
    ScalerSetByte(P80_C4_BW1_VER_START_H + ucWinAddDelta, (usVPos >> 8) & 0x1F);
    ScalerSetByte(P80_C5_BW1_VER_START_L + ucWinAddDelta, usVPos & 0xFF);
    ScalerSetByte(P80_C6_BW1_VER_END_H + ucWinAddDelta, ((usVPos + usVHeight) >> 8) & 0x3F);
    ScalerSetByte(P80_C7_BW1_VER_END_L + ucWinAddDelta, (usVPos + usVHeight) & 0xFF);

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#endif  // End of #if(_COLOR_IP_BORDER_WIN == _ON)

