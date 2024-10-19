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
// ID Code      : ScalerColorIDither.c
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
#if(_COLOR_IP_I_DITHER == _ON)
//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//              enumIDitherConvType :  Conv Type
//              pucDitherTable : Dither Table Pointer
//              pucSeqTable : Seq Table Pointer
//              pucTempoTable : Temporal Table Pointer
//              ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherAdjust(WORD usPage, EnumIDitherConvType enumIDitherConvType, BYTE *pucDitherTable, BYTE *pucSeqTable, BYTE *pucTempoTable, BYTE ucBankAddress)
{
    WORD usAdjustOption = 0x0000;
    BYTE ucSeqLength = 0;

    ScalerColorIDitherLoadDitherTable(usPage, pucDitherTable, ucBankAddress);
    ScalerColorIDitherLoadTemporalTable(usPage, pucTempoTable, ucBankAddress);

    if(enumIDitherConvType == _IDITHER_12_TO_8)
    {
#if((_I_DITHER_MULTI_SEQ_ENABLE == _DISABLE) && (_I_DITHER_SERIES_SEQ_ENABLE == _DISABLE))
        ucSeqLength = 24;
#else
        ucSeqLength = 96;
#endif
        usAdjustOption = (_I_DITHER_SEQ_INV_ENABLE << 14) |
                         (_I_DITHER_SEQ_INV_MODE << 13) |
                         (_I_DITHER_SERIES_SEQ_ENABLE << 12) |
                         (_I_DITHER_SHARE_SEQ_ENABLE << 11) |
                         (_I_DITHER_MULTI_SEQ_ENABLE << 10) |
#if(_HW_IDITHER_SUPER_PIXEL_SUPPORT == _ON)
                         (_I_DITHER_SUPER_PIXEL_SIZE << 5) |
#endif
                         (_I_DITHER_TEMP << 4) |
                         (_I_DITHER_VALUE_SIGN << 3) |
                         (_I_DITHER_V_FRAME_MOD << 1) |
                         (_I_DITHER_H_FRAME_MOD << 0);
    }
    else
    {
#if((_I_DITHER_12_TO_10_MULTI_SEQ_ENABLE == _DISABLE) && (_I_DITHER_12_TO_10_SERIES_SEQ_ENABLE == _DISABLE))
        ucSeqLength = 24;
#else
        ucSeqLength = 96;
#endif
        usAdjustOption = (_I_DITHER_12_TO_10_SEQ_INV_ENABLE << 14) |
                         (_I_DITHER_12_TO_10_SEQ_INV_MODE << 13) |
                         (_I_DITHER_12_TO_10_SERIES_SEQ_ENABLE << 12) |
                         (_I_DITHER_12_TO_10_SHARE_SEQ_ENABLE << 11) |
                         (_I_DITHER_12_TO_10_MULTI_SEQ_ENABLE << 10) |
                         (_I_DITHER_12_TO_10_TEMP << 4) |
                         (_I_DITHER_12_TO_10_VALUE_SIGN << 3) |
                         (_I_DITHER_12_TO_10_V_FRAME_MOD << 1) |
                         (_I_DITHER_12_TO_10_H_FRAME_MOD << 0);
    }
    ScalerColorIDitherLoadSeqTable(usPage, pucSeqTable, ucSeqLength, ucBankAddress);
    ScalerColorIDitherLoadSetting(usPage, usAdjustOption);
}

//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//                pucDitherTable : Dither Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherLoadDitherTable(WORD usPage, BYTE *pucDitherTable, BYTE ucBankAddress)
{
    if(pucDitherTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA + usPage, ~(_BIT7 | _BIT6), 0x80);
        ScalerBurstWrite(pucDitherTable, _IDITHER_DITHER_TABLE_LENGTH, ucBankAddress, P0_88_I_DITHER_DATA_ACCESS_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA + usPage, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//                pucDitherTable : Seq Table Pointer.
//                ucSeqLength : table len
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherLoadSeqTable(WORD usPage, BYTE *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress)
{
    if(pucSeqTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA + usPage, ~(_BIT7 | _BIT6), 0x40);
        ScalerBurstWrite(pucSeqTable, ucSeqLength, ucBankAddress, P0_88_I_DITHER_DATA_ACCESS_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA + usPage, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//                pucDitherTable : Temporal Table Pointer
//              ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherLoadTemporalTable(WORD usPage, BYTE *pucTempoTable, BYTE ucBankAddress)
{
    if(pucTempoTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA + usPage, ~(_BIT7 | _BIT6), 0xC0);
        ScalerBurstWrite(pucTempoTable, _IDITHER_TEMPORAL_TABLE_LENGTH, ucBankAddress, P0_88_I_DITHER_DATA_ACCESS_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA + usPage, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  : usAdjustOption->Adjust setting
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherLoadSetting(WORD usPage, WORD usAdjustOption)
{
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA + usPage, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), usAdjustOption & 0x001F);
    ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA + usPage, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usAdjustOption & 0x7E00) >> 8);
#if(_HW_IDITHER_SUPER_PIXEL_SUPPORT == _ON)
    ScalerSetBit(_REG_IDITHER_SUPERPIX_TYPE + usPage, ~(_BIT6 | _BIT5), usAdjustOption & 0x0060);
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable Idither function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
#if(_HW_IDITHER_M1_PATH_SUPPORT == _ON)
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, _BIT5);
#endif

#if(_HW_IDITHER_M2_PATH_SUPPORT == _ON)
        ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, _BIT5);
#endif

#if(_HW_IDITHER_S1_PATH_SUPPORT == _ON)
        ScalerSetBit(P80_89_I_DITHER_COMMON_CTRL1_SETB, ~_BIT5, _BIT5);
#endif

#if(_HW_IDITHER_S2_PATH_SUPPORT == _ON)
        ScalerSetBit(PC0_89_I_DITHER_COMMON_CTRL1_S2, ~_BIT5, _BIT5);
#endif

#if(_HW_IDITHER_S3_PATH_SUPPORT == _ON)
        ScalerSetBit(P17_89_I_DITHER_COMMON_CTRL1_S3, ~_BIT5, _BIT5);
#endif

#if(_HW_IDITHER_S4_PATH_SUPPORT == _ON)
        ScalerSetBit(PDC_89_I_DITHER_COMMON_CTRL1_S4, ~_BIT5, _BIT5);
#endif
    }
    else
    {
#if(_HW_IDITHER_M1_PATH_SUPPORT == _ON)
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, 0x00);
#endif

#if(_HW_IDITHER_M2_PATH_SUPPORT == _ON)
        ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, 0x00);
#endif

#if(_HW_IDITHER_S1_PATH_SUPPORT == _ON)
        ScalerSetBit(P80_89_I_DITHER_COMMON_CTRL1_SETB, ~_BIT5, 0x00);
#endif

#if(_HW_IDITHER_S2_PATH_SUPPORT == _ON)
        ScalerSetBit(PC0_89_I_DITHER_COMMON_CTRL1_S2, ~_BIT5, 0x00);
#endif

#if(_HW_IDITHER_S3_PATH_SUPPORT == _ON)
        ScalerSetBit(P17_89_I_DITHER_COMMON_CTRL1_S3, ~_BIT5, 0x00);
#endif

#if(_HW_IDITHER_S4_PATH_SUPPORT == _ON)
        ScalerSetBit(PDC_89_I_DITHER_COMMON_CTRL1_S4, ~_BIT5, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Idither function
// Input Value  : EnumDisplayRegion, EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherRegionEnable(EnumDisplayRegion enumDisplayRegion, EnumFunctionOnOFF enumOn)
{
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);

    if(enumOn == _FUNCTION_ON)
    {
        bit bFrontBackFrameCntAlign = _FALSE;

#if(_HW_IDITHER_M1_PATH_SUPPORT == _ON)
        if(((enumInputDataPath & _INPUT_PATH_M1) == _INPUT_PATH_M1) && (ScalerGetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, _BIT5) == 0x00))
        {
            ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, _BIT5);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
            {
                bFrontBackFrameCntAlign = _TRUE;
            }
        }
#endif

#if(_HW_IDITHER_M2_PATH_SUPPORT == _ON)
        if(((enumInputDataPath & _INPUT_PATH_M2) == _INPUT_PATH_M2) && (ScalerGetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, _BIT5) == 0x00))
        {
            ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, _BIT5);
        }
#endif

#if(_HW_IDITHER_S1_PATH_SUPPORT == _ON)
        if(((enumInputDataPath & _INPUT_PATH_S1) == _INPUT_PATH_S1) && (ScalerGetBit(P80_89_I_DITHER_COMMON_CTRL1_SETB, _BIT5) == 0x00))
        {
            ScalerSetBit(P80_89_I_DITHER_COMMON_CTRL1_SETB, ~_BIT5, _BIT5);
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
            {
                bFrontBackFrameCntAlign = _TRUE;
            }
        }
#endif

#if(_HW_IDITHER_S2_PATH_SUPPORT == _ON)
        if(((enumInputDataPath & _INPUT_PATH_S2) == _INPUT_PATH_S2) && (ScalerGetBit(PC0_89_I_DITHER_COMMON_CTRL1_S2, _BIT5) == 0x00))
        {
            ScalerSetBit(PC0_89_I_DITHER_COMMON_CTRL1_S2, ~_BIT5, _BIT5);
        }
#endif

#if(_HW_IDITHER_S3_PATH_SUPPORT == _ON)
        if(((enumInputDataPath & _INPUT_PATH_S3) == _INPUT_PATH_S3) && (ScalerGetBit(P17_89_I_DITHER_COMMON_CTRL1_S3, _BIT5) == 0x00))
        {
            ScalerSetBit(P17_89_I_DITHER_COMMON_CTRL1_S3, ~_BIT5, _BIT5);
        }
#endif

#if(_HW_IDITHER_S4_PATH_SUPPORT == _ON)
        if(((enumInputDataPath & _INPUT_PATH_S4) == _INPUT_PATH_S4) && (ScalerGetBit(PDC_89_I_DITHER_COMMON_CTRL1_S4, _BIT5) == 0x00))
        {
            ScalerSetBit(PDC_89_I_DITHER_COMMON_CTRL1_S4, ~_BIT5, _BIT5);
        }
#endif

#if(_HW_IDITHER_S1_PATH_SUPPORT == _ON)
        // To prevent front/back frame count mismatch
        if(bFrontBackFrameCntAlign == _TRUE)
        {
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2_S1_S2);

            // Reset M1/S1 frame count
            ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA, ~_BIT0, _BIT0);
            ScalerSetBit(P80_8A_I_DITHER_COMMON_CTRL2_SETB, ~_BIT0, _BIT0);
        }
#endif
    }
    else
    {
#if(_HW_IDITHER_M1_PATH_SUPPORT == _ON)
        if((enumInputDataPath & _INPUT_PATH_M1) == _INPUT_PATH_M1)
        {
            ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, 0x00);
        }
#endif

#if(_HW_IDITHER_M2_PATH_SUPPORT == _ON)
        if((enumInputDataPath & _INPUT_PATH_M2) == _INPUT_PATH_M2)
        {
            ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, 0x00);
        }
#endif

#if(_HW_IDITHER_S1_PATH_SUPPORT == _ON)
        if((enumInputDataPath & _INPUT_PATH_S1) == _INPUT_PATH_S1)
        {
            ScalerSetBit(P80_89_I_DITHER_COMMON_CTRL1_SETB, ~_BIT5, 0x00);
        }
#endif

#if(_HW_IDITHER_S2_PATH_SUPPORT == _ON)
        if((enumInputDataPath & _INPUT_PATH_S2) == _INPUT_PATH_S2)
        {
            ScalerSetBit(PC0_89_I_DITHER_COMMON_CTRL1_S2, ~_BIT5, 0x00);
        }
#endif

#if(_HW_IDITHER_S3_PATH_SUPPORT == _ON)
        if((enumInputDataPath & _INPUT_PATH_S3) == _INPUT_PATH_S3)
        {
            ScalerSetBit(P17_89_I_DITHER_COMMON_CTRL1_S3, ~_BIT5, 0x00);
        }
#endif

#if(_HW_IDITHER_S4_PATH_SUPPORT == _ON)
        if((enumInputDataPath & _INPUT_PATH_S4) == _INPUT_PATH_S4)
        {
            ScalerSetBit(PDC_89_I_DITHER_COMMON_CTRL1_S4, ~_BIT5, 0x00);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Select Idither table
// Input Value  : enumColorDepth
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherTableSelect(EnumSelRegion enumSelRegion, BYTE ucColorDepth)
{
    enumSelRegion = enumSelRegion;
    ucColorDepth = ucColorDepth;

#if(_HW_IDITHER_TABLE_SET_NUM > 1)
    {
        BYTE ucType = 0;
        WORD usPage = _REG_MAIN1_PAGE;
        ucType = ((ucColorDepth == _COLOR_DEPTH_8_BITS) || (ScalerColorIDitherGetTableSetNum() == 1)) ? 0 : _BIT7;

#if(_HW_I_DOMAIN_PATH_COUNT > 1)
        usPage = ScalerRegionGetIDomainRegisterPage(enumSelRegion);
#endif
        ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA + usPage, ~_BIT7, ucType);

        if((usPage == _REG_MAIN1_PAGE) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE))
        {
            ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA + _REG_SUB1_PAGE, ~_BIT7, ucType);

            // frame count reset, sync M1/S1 frame cnt in F/B 1P
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2_S1_S2);
            ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA + _REG_SUB1_PAGE, ~_BIT0, _BIT0);
        }
        ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA + usPage, ~_BIT0, _BIT0);
    }
#else
    ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA, ~_BIT0, _BIT0);
#endif // End of #if(_HW_IDITHER_TABLE_SET_NUM > 1)
}

#endif  // End of #if(_COLOR_IP_I_DITHER == _ON)

