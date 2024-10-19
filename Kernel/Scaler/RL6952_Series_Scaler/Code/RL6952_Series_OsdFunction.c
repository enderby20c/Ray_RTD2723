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
// ID Code      : RL6952_Series_OsdFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_OSDFUNCTION__

#include "ScalerFunctionInclude.h"
#include "Osd/ScalerOsd.h"


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
// Description  : Set OSD 2 bit font offset
// Input Value  : ucOffset -> 0 ~ 511
// Output Value :
//--------------------------------------------------
void ScalerOsd2BitFontOffset(WORD usOffset)
{
    ScalerSetBit(P3A_29_FRAME_CTRL_F_FONT_OFFSET_H, ~(HIBYTE(_HW_OSD_2_BIT_OFFSET_BIT)), HIBYTE(usOffset & _HW_OSD_2_BIT_OFFSET_BIT));
    ScalerSetByte(P3A_2A_FRAME_CTRL_F_2BIT_OFFSET_L, LOBYTE(usOffset));
}

//--------------------------------------------------
// Description  : Set OSD 4 bit font offset
// Input Value  : ucOffset -> 0 ~ 511
// Output Value :
//--------------------------------------------------
void ScalerOsd4BitFontOffset(WORD usOffset)
{
    ScalerSetBit(P3A_29_FRAME_CTRL_F_FONT_OFFSET_H, ~(HIBYTE(_HW_OSD_4_BIT_OFFSET_BIT) << 4), HIBYTE(usOffset & _HW_OSD_4_BIT_OFFSET_BIT) << 4);
    ScalerSetByte(P3A_2B_FRAME_CTRL_F_4BIT_OFFSRT_L, LOBYTE(usOffset));
}

//--------------------------------------------------
// Description  : Set write protection for SRAM when OSD is on
// Input Value  : bEnable          -> _ENABLE or _DISABLE
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
//                ucBitSelect      -> (_BIT7 | _BIT6 | _BIT5 |_BIT4 | _BIT3 |_BIT2 | _BIT1 | _BIT0)
// Output Value :
//--------------------------------------------------
void ScalerOsdWriteProtection(bit bEnable, EnumOsdWriteType enumOsdWriteType, BYTE ucBitSelect)
{
    BYTE ucTemp = 0;

    switch(enumOsdWriteType)
    {
        case _OSD_BYTE0:
            ucTemp = _BIT0;
            break;
        case _OSD_BYTE1:
            ucTemp = _BIT1;
            break;
        case _OSD_BYTE2:
            ucTemp = _BIT2;
            break;
        case _OSD_BYTE3:
            ucTemp = _BIT3;
            break;
        default:
            break;
    }

    // Set OSD Circuit Enable for Write-Protection Function effective in OSD enable.
    if((bEnable == _ENABLE) && (ScalerGetBit(P3A_00_FRAME_CTRL_F_OSD_EN, _BIT0) == 0x00))
    {
        if(ScalerOsdGetOsdEnable() == _TRUE)
        {
            ScalerOsdDisableOsd();
        }

        ScalerOsdCircuitActivated(_ENABLE);
    }

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerSetBit(P3A_35_FRAME_CTRL_F_WRI_PROTECT_BIT_EN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (bEnable == _ENABLE) ? (ucTemp) : (0x00));

    switch(enumOsdWriteType)
    {
        case _OSD_BYTE0:
            ScalerSetBit(P3A_36_FRAME_CTRL_F_WRI_PROTECT_BIT_BYTE0, ~ucBitSelect, (bEnable == _ENABLE) ? (ucBitSelect) : (0x00)); // bit_block_byte0
            break;

        case _OSD_BYTE1:
            ScalerSetBit(P3A_7C_FRAME_CTRL_F_WRI_PROTECT_BIT_BYTE1, ~ucBitSelect, (bEnable == _ENABLE) ? (ucBitSelect) : (0x00)); // bit_block_byte1
            break;

        case _OSD_BYTE2:
            ScalerSetBit(P3A_7D_FRAME_CTRL_F_WRI_PROTECT_BIT_BYTE2, ~ucBitSelect, (bEnable == _ENABLE) ? (ucBitSelect) : (0x00)); // bit_block_byte2
            break;

        case _OSD_BYTE3:
            ScalerSetBit(P3A_7E_FRAME_CTRL_F_WRI_PROTECT_BIT_BYTE3, ~ucBitSelect, (bEnable == _ENABLE) ? (ucBitSelect) : (0x00)); // bit_block_byte3
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerOsdSetOsdHPorchAdjust(void)
{
    // RL6952/RL6952 need to implement
}

