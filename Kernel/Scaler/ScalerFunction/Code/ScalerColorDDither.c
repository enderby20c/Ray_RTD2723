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
// ID Code      : ScalerColorDDither.c
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
#if(_COLOR_IP_D_DITHER == _ON)
//--------------------------------------------------
// Description  : Adjust D Dither Common Setting
// Input Value  :
//                pucDitherTable : Dither Table Pointer
//                pucSeqTable : Seq Table Pointer
//                pucTempoTable : Temporal Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherAdjust(BYTE *pucDitherTable, BYTE *pucSeqTable, BYTE *pucTempoTable, BYTE ucBankAddress)
{
    DWORD ulSettingOption = 0x00000000;
    BYTE ucKeepNFrame = _DDITHER_KEEP_1_FRAME;

    ScalerColorDDitherLoadDitherTable(pucDitherTable, ucBankAddress);

#if((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SERIES_SEQ_ENABLE == _ENABLE) || (_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE))
    ScalerColorDDitherLoadSeqTable(pucSeqTable, 192, ucBankAddress);
#else
    ScalerColorDDitherLoadSeqTable(pucSeqTable, 48, ucBankAddress);
#endif

    ScalerColorDDitherLoadTempoTable(pucTempoTable, ucBankAddress);

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))

#if(((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) && (_D_DITHER_SERIES_SEQ_ENABLE == _DISABLE)) ||\
    (_D_DITHER_SHARE_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SEQ_INV_ENABLE == _ENABLE) ||\
    (_D_DITHER_V_FRAME_MOD == _ENABLE) || (_D_DITHER_H_FRAME_MOD == _ENABLE))

#if(_D_DITHER_SUPER_PIXEL_SIZE == _DDITHER_SUPER_PIXEL_2X2)
    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_30_BIT:
            ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
            break;
        case _PANEL_DISP_24_BIT:
            ucKeepNFrame = _DDITHER_KEEP_16_FRAME;
            break;
        default:
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
            ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
#else
            ucKeepNFrame = _DDITHER_KEEP_16_FRAME;
#endif
            break;
    }
#elif((_D_DITHER_SUPER_PIXEL_SIZE == _DDITHER_SUPER_PIXEL_2X4) ||\
      (_D_DITHER_SUPER_PIXEL_SIZE == _DDITHER_SUPER_PIXEL_4X2))
    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_30_BIT:
            ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
            break;
        case _PANEL_DISP_24_BIT:
            ucKeepNFrame = _DDITHER_KEEP_8_FRAME;
            break;
        default:
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
            ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
#else
            ucKeepNFrame = _DDITHER_KEEP_8_FRAME;
#endif
            break;
    }
#elif(_D_DITHER_SUPER_PIXEL_SIZE == _DDITHER_SUPER_PIXEL_4X4)
    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_30_BIT:
            ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            break;
        case _PANEL_DISP_24_BIT:
            ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
            break;
        default:
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
            ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
#else
            ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
#endif
            break;
    }
#elif((_D_DITHER_SUPER_PIXEL_SIZE == _DDITHER_SUPER_PIXEL_4X8) ||\
      (_D_DITHER_SUPER_PIXEL_SIZE == _DDITHER_SUPER_PIXEL_8X4))
    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_30_BIT:
            ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            break;
        case _PANEL_DISP_24_BIT:
            ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
            break;
        default:
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
            ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
#else
            ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
#endif
            break;
    }
#else
    ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
#endif

#endif

#else // else of #if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)

#if((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SHARE_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SEQ_INV_ENABLE == _ENABLE))
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
    {
        ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
    }
    else
    {
        ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
    }
#endif

#endif // end of #if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)

    ulSettingOption = (_DDITHER_TEMPORAL_ENABLE << 4) | (_D_DITHER_V_FRAME_MOD << 1) | _D_DITHER_H_FRAME_MOD;
    ulSettingOption |= (_D_DITHER_6BIT_PANEL_FUNC_ENABLE << 7);
    ulSettingOption |= (((DWORD)((ucKeepNFrame << 4) | _D_DITHER_SUPER_PIXEL_SIZE)) << 8);
    ulSettingOption |= (((DWORD)((_D_DITHER_SERIES_SEQ_ENABLE << 3) | (_D_DITHER_MULTI_SEQ_ENABLE << 2))) << 16);
    ulSettingOption |= (((DWORD)((_D_DITHER_SHARE_SEQ_ENABLE << 3) | (_D_DITHER_SEQ_INV_ENABLE << 1) | _D_DITHER_SEQ_INV_MODE)) << 24);

    ScalerColorDDitherLoadSetting(ulSettingOption);
}

//--------------------------------------------------
// Description  : Adjust D Dither Setting
// Input Value  :
//                pucDitherTable : Dither Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherLoadDitherTable(BYTE *pucDitherTable, BYTE ucBankAddress)
{
    if(pucDitherTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x80);
        ScalerBurstWrite(pucDitherTable, _DDITHER_DITHER_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust D Dither Setting
// Input Value  :
//                pucSeqTable : Seq Table Pointer
//                ucSeqLength : Seq Table Length
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherLoadSeqTable(BYTE *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress)
{
    if(pucSeqTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x40);
        ScalerBurstWrite(pucSeqTable, ucSeqLength, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust D Dither Setting
// Input Value  :
//                pucTempoTable : Temporal Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherLoadTempoTable(BYTE *pucTempoTable, BYTE ucBankAddress)
{
    if(pucTempoTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0xC0);
        ScalerBurstWrite(pucTempoTable, _DDITHER_TEMPORAL_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust D Dither Common Setting
// Input Value  : D Dither Setting Option
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherLoadSetting(DWORD ulSettingOption)
{
    BYTE ucData = 0;
    ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1 | _BIT0), ulSettingOption & 0x0000003F);
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_00_D_DITHER_COMMON_SET0);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, (ulSettingOption & 0x0000FF00) >> 8);
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_02_D_DITHER_COMMON_SET2);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, (ulSettingOption & 0x00FF0000) >> 16);
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_03_D_DITHER_COMMON_SET3);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, (ulSettingOption & 0x00000080) >> 7);
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_0D_D_DITHER_COMMON_CTRL2);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, (ulSettingOption & 0xFF000000) >> 24);

    // reset frame counter
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_01_D_DITHER_COMMON_SET1);
    ucData = ScalerGetByte(P0_69_D_DITHER_DATA_ACCESS) | _BIT7;
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_01_D_DITHER_COMMON_SET1);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, ucData);
}

//--------------------------------------------------
// Description  : Adjust Advance Setting
// Input Value  :
//                pucReAlignTable : ReAlign Table Pointer
//                pucReAlignTempoTable : ReAlign Temporal Table Pointer
//                pucLsbTable : LSB Judge Table Pointer
//                pucAdvanceSettingTable : Advance Setting Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherAdvanceSettingAdjust(BYTE *pucReAlignTable, BYTE *pucReAlignTempoTable, BYTE *pucLsbTable, BYTE *pucAdvanceSettingTable, BYTE ucBankAddress)
{
    BYTE ucData = 0;

    ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x00);

    if(pucReAlignTable != _NULL_POINTER)
    {
        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_80_D_DITHER_REALIGN_SET_R0);
        ScalerBurstWrite(pucReAlignTable, _DDITHER_REALIGN_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    if(pucReAlignTempoTable != _NULL_POINTER)
    {
        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_B0_D_DITHER_REALIGN_OFFSET0);
        ScalerBurstWrite(pucReAlignTempoTable, _DDITHER_REALIGN_TEMPO_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    if(pucLsbTable != _NULL_POINTER)
    {
        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_C0_D_DITHER_LSB_TABLE0);
        ScalerBurstWrite(pucLsbTable, _DDITHER_LSB_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    if(pucAdvanceSettingTable != _NULL_POINTER)
    {
        ucData = ScalerGetByte(P0_6A_D_DITHER_COMMON_CTRL1) & _BIT5;
        ScalerBurstWrite(pucAdvanceSettingTable, 1, ucBankAddress, P0_6A_D_DITHER_COMMON_CTRL1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6 | _BIT5), ucData);

        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_00_D_DITHER_COMMON_SET0);
        ScalerBurstWrite(pucAdvanceSettingTable + 1, _DDITHER_ADVANCESETTING_TABLE_LENGTH - 1, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    // reset frame counter
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_01_D_DITHER_COMMON_SET1);
    ucData = ScalerGetByte(P0_69_D_DITHER_DATA_ACCESS) | _BIT7;
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_01_D_DITHER_COMMON_SET1);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, ucData);
}

//--------------------------------------------------
// Description  : Enable/Disable DDither function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~_BIT5, _BIT5);
    }
    else
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~_BIT5, 0x00);
    }
}
#endif  // End of #if(_COLOR_IP_D_DITHER == _ON)

