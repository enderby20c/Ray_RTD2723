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
// ID Code      : ScalerColorGamma.c
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
#if(_COLOR_IP_O_GAMMA == _ON)
//--------------------------------------------------
// Description  : Set Output Gamma Enable Region
// Input Value  : SelRegion and EnumDBApply, and _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    BYTE ucHlwSetting = ScalerGetByte(P9_C3_GAMMA_OGC_HLW);
    BYTE ucMask = 0;

    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_INSIDE_WINDOW:
            ucMask = _BIT3;
            break;

        case _HLW_OUTSIDE_WINDOW:
            ucMask = _BIT2;
            break;

        case _HLW_FULL_WINDOW:
        default:
            ucMask = (_BIT3 | _BIT2);
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

    ScalerSetByte(P9_C3_GAMMA_OGC_HLW, ucHlwSetting);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Output Gamma Highlight Window Status
// Input Value  : EnumSelRegion
// Output Value : EnumHLWStatus - Output Gamma Highlight Window ON/OFF Status
//--------------------------------------------------
EnumHLWStatus ScalerColorGammaGetHLWRegionStatus(EnumSelRegion enumSelRegion)
{
    EnumHLWType enumHLWType = ScalerRegionGetSelectRegionHLWArea(enumSelRegion);
    EnumHLWStatus enumHLWStatus = _HLW_ON;

    switch(enumHLWType)
    {
        case _HLW_INSIDE_WINDOW:
            if((ScalerGetBit(P9_C3_GAMMA_OGC_HLW, (_BIT3 | _BIT2)) & _BIT3) == _BIT3)
            {
                enumHLWStatus = _HLW_OFF;
            }
            break;

        case _HLW_OUTSIDE_WINDOW:
            if((ScalerGetBit(P9_C3_GAMMA_OGC_HLW, (_BIT3 | _BIT2)) & _BIT2) == _BIT2)
            {
                enumHLWStatus = _HLW_OFF;
            }
            break;

        default:
            if(ScalerGetBit(P9_C3_GAMMA_OGC_HLW, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
            {
                enumHLWStatus = _HLW_OFF;
            }
            break;
    }

    return enumHLWStatus;
}
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Set Output Gamma Effect Region
// Input Value  : SelRegion and EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorGammaSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerSetBit(P9_C3_GAMMA_OGC_HLW, ~(_BIT1 | _BIT0), (BYTE)enumSetSel);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Output Gamma HLW Effective Region
// Input Value  : None
// Output Value : EnumHLWSetSel
//--------------------------------------------------
EnumHLWSetSel ScalerColorGammaGetEffectiveRegion(void)
{
    return (EnumHLWSetSel)(ScalerGetBit(P9_C3_GAMMA_OGC_HLW, (_BIT1 | _BIT0)));
}
#endif

//--------------------------------------------------
// Description  : Switch Gamma Channel
// Input Value  : ucColorChannel: 0- Red, 1- Green, 2- Blue;
//                ucOffset: Offset
//                bLocation: 0-Write to SDRAM, 1- Write to LATCH
// Output Value : None
//--------------------------------------------------
void ScalerColorOutputGammaChannelCtrl(WORD usPage, BYTE ucColorChannel, WORD usOffset, bit bLocation)
{
    // Select Channel
    ScalerSetBit(P9_C1_GAMMA_CTRL_SETA + usPage, ~(_BIT7 | _BIT5 | _BIT4 | _BIT2), ((ucColorChannel << 4) | ((BYTE)bLocation << 2)));

    // Specify address
    ScalerSetBit(P9_C1_GAMMA_CTRL_SETA + usPage, ~_BIT3, _BIT3);
    ScalerSetByte(P9_C0_GAMMA_PORT_SETA + usPage, HIBYTE(usOffset));
    ScalerSetByte(P9_C0_GAMMA_PORT_SETA + usPage, LOBYTE(usOffset));
    ScalerSetBit(P9_C1_GAMMA_CTRL_SETA + usPage, ~(_BIT7 | _BIT3), _BIT7);
}

//--------------------------------------------------
// Description  : Adjust output gamma
// Input Value  : SelRegion ans Gamma Table and Gamma Table Banks and Table Length
// Output Value : None
//--------------------------------------------------
void ScalerColorOutputGammaAdjust(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE ucBankNum)
{
    EnumHLWStatus enumHLWStatus = ScalerColorGammaGetHLWRegionStatus(enumSelRegion);
    WORD usPage = _REG_MAIN1_PAGE;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if((ScalerGetBit(P9_C1_GAMMA_CTRL_SETA, _BIT6) == _BIT6) && (enumHLWStatus == _HLW_ON)) // Gamma On && No Bypass
    {
        ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);

        // Load gamma table of R Channel
        ScalerColorOutputGammaChannelCtrl(usPage, _GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P9_C0_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        ScalerColorOutputGammaChannelCtrl(usPage, _GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P9_C0_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        ScalerColorOutputGammaChannelCtrl(usPage, _GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P9_C0_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P9_C1_GAMMA_CTRL_SETA + usPage, ~_BIT7, 0x00);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        if(enumSelRegion == _FULL_REGION)
        {
            // Load gamma table of R Channel
            ScalerColorOutputGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P49_C0_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Load gamma table of G Channel
            ScalerColorOutputGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P49_C0_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Load gamma table of B Channel
            ScalerColorOutputGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P49_C0_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Disable Port Access
            ScalerSetBit(P49_C1_GAMMA_CTRL_SETB, ~_BIT7, 0x00);
        }
#endif

        ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
    }
    else
    {
        // Load gamma table of R Channel
        ScalerColorOutputGammaChannelCtrl(usPage, _GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P9_C0_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        ScalerColorOutputGammaChannelCtrl(usPage, _GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P9_C0_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        ScalerColorOutputGammaChannelCtrl(usPage, _GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P9_C0_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P9_C1_GAMMA_CTRL_SETA + usPage, ~_BIT7, 0x00);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        if(enumSelRegion == _FULL_REGION)
        {
            // Load gamma table of R Channel
            ScalerColorOutputGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P49_C0_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Load gamma table of G Channel
            ScalerColorOutputGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P49_C0_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Load gamma table of B Channel
            ScalerColorOutputGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P49_C0_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Disable Port Access
            ScalerSetBit(P49_C1_GAMMA_CTRL_SETB, ~_BIT7, 0x00);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Write OG LUT for False Color Function
// Input Value  : EnumGammaChannel enumChannel: Gamma Channel:R/G/B
//                BYTE *pucGammaTableArray: OG LUT
//                WORD usStartAddr: Write Start Address
//                WORD usLength: LUT Length
//                BYTE ucBankNum: LUT's Bank Number
// Output Value : None
//--------------------------------------------------
void ScalerColorOutputGammaAdjustSector(EnumSelRegion enumSelRegion, EnumGammaChannel enumChannel, BYTE *pucGammaTableArray, WORD usStartAddr, WORD usLength, BYTE ucBankNum)
{
    EnumHLWType enumHLWType = ScalerRegionGetSelectRegionHLWArea(enumSelRegion);
    BYTE ucBypass = _OFF;
    WORD usPage = _REG_MAIN1_PAGE;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    switch(enumHLWType)
    {
        case _HLW_INSIDE_WINDOW:
            if((ScalerGetBit(P9_C3_GAMMA_OGC_HLW, (_BIT3 | _BIT2)) & _BIT3) == _BIT3)
            {
                ucBypass = _ON;
            }
            break;

        case _HLW_OUTSIDE_WINDOW:
            if((ScalerGetBit(P9_C3_GAMMA_OGC_HLW, (_BIT3 | _BIT2)) & _BIT2) == _BIT2)
            {
                ucBypass = _ON;
            }
            break;

        default:
            if(ScalerGetBit(P9_C3_GAMMA_OGC_HLW, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
            {
                ucBypass = _ON;
            }
            break;
    }

    if((ScalerGetBit(P9_C1_GAMMA_CTRL_SETA, _BIT6) == _BIT6) && (ucBypass == _OFF)) // Gamma On && No Bypass
    {
        ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);

        ScalerColorOutputGammaChannelCtrl(usPage, enumChannel, usStartAddr, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, usLength, ucBankNum, P9_C0_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

        // Disable Port Access
        ScalerSetBit(P9_C1_GAMMA_CTRL_SETA + usPage, ~_BIT7, 0x00);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        if(enumSelRegion == _FULL_REGION)
        {
            ScalerColorOutputGammaChannelCtrl(_REG_MAIN2_PAGE, enumChannel, usStartAddr, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray, usLength, ucBankNum, P49_C0_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

            // Disable Port Access
            ScalerSetBit(P49_C1_GAMMA_CTRL_SETB, ~_BIT7, 0x00);
        }
#endif

        ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
    }
    else
    {
        ScalerColorOutputGammaChannelCtrl(usPage, enumChannel, usStartAddr, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, usLength, ucBankNum, P9_C0_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        // Disable Port Access
        ScalerSetBit(P9_C1_GAMMA_CTRL_SETA + usPage, ~_BIT7, 0x00);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        if(enumSelRegion == _FULL_REGION)
        {
            ScalerColorOutputGammaChannelCtrl(_REG_MAIN2_PAGE, enumChannel, usStartAddr, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray, usLength, ucBankNum, P49_C0_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

            // Disable Port Access
            ScalerSetBit(P49_C1_GAMMA_CTRL_SETB, ~_BIT7, 0x00);
        }
#endif
    }
}


//--------------------------------------------------
// Description  : Enable/Disable Output Gamma
// Input Value  : _FUNCTION_ON / _FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorOutputGammaEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P9_C1_GAMMA_CTRL_SETA, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P9_C1_GAMMA_CTRL_SETA, ~_BIT6, 0x00);
    }
}

#endif  // End of #if(_COLOR_IP_O_GAMMA == _ON)

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
//--------------------------------------------------
// Description  : Set 3D Gamma Enable Region
// Input Value  : SelRegion and EnumDBApply, and _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerColor3DGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    BYTE ucHlwSetting = ScalerGetByte(P9_B0_RGB_3D_GAMMA_CTRL);
    BYTE ucMask = 0;

    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_INSIDE_WINDOW:
            ucMask = _BIT4;
            break;

        case _HLW_OUTSIDE_WINDOW:
            ucMask = _BIT3;
            break;

        case _HLW_FULL_WINDOW:
        default:
            ucMask = (_BIT4 | _BIT3);
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

    ScalerSetByte(P9_B0_RGB_3D_GAMMA_CTRL, ucHlwSetting);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}


//--------------------------------------------------
// Description  : Adjust 3D gamma
// Input Value  : 3D Gamma Table and 3D Gamma Table Banks
// Output Value : None
//--------------------------------------------------
void ScalerColorRGB3DGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum)
{
    if(ScalerGetBit(P9_B0_RGB_3D_GAMMA_CTRL, _BIT7) == _BIT7) // 3D Gamma On
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);

        // Enable Gamma access
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT6, _BIT6);

        // Initial Table Address
        ScalerSetByte(P9_B1_RGB_3D_GAMMA_ADDRESS_H, 0x00);
        ScalerSetByte(P9_B2_RGB_3D_GAMMA_ADDRESS_L, 0x00);

        // Load gamma table of 3D Gamma
        ScalerBurstWrite(pucGammaTableArray, _3DGAMMA_TABLE_SIZE, ucBankNum, P9_B3_RGB_3D_GAMMA_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT6, 0x00);

        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
    }
    else
    {
        // Enable Gamma access
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT6, _BIT6);

        // Initial Table Address
        ScalerSetByte(P9_B1_RGB_3D_GAMMA_ADDRESS_H, 0x00);
        ScalerSetByte(P9_B2_RGB_3D_GAMMA_ADDRESS_L, 0x00);

        // Load gamma table of 3D Gamma
        ScalerBurstWrite(pucGammaTableArray, _3DGAMMA_TABLE_SIZE, ucBankNum, P9_B3_RGB_3D_GAMMA_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable 3D Gamma
// Input Value  : _FUNCTION_ON / _FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorRGB3DGammaEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable 3D Gamma swap
// Input Value  : _FUNCTION_ON / _FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorRGBGamma3DGammaSwapEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT5, 0x00);
    }
}

#if(_HW_3D_GAMMA_TABLE_TYPE == _3D_GAMMA_GEN_2)
//--------------------------------------------------
// Description  : Initial 3DGamma Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorRGB3DGammaInitial(void)
{
    ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT2, _BIT2); // set 3DGamma interpolation method to tetrahedral interpolation
}
#endif
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
//--------------------------------------------------
// Description  : Switch Gamma Channel
// Input Value  : ucColorChannel: 0- Red, 1- Green, 2- Blue;
//                ucOffset: Offset
//                bLocation: 0-Write to SDRAM, 1- Write to LATCH
// Output Value : None
//--------------------------------------------------
void ScalerColorPostGammaChannelCtrl(WORD usPage, BYTE ucColorChannel, WORD usOffset, bit bLocation)
{
    // Select Channel
    ScalerSetBit(P9_D9_POST_GAMMA_CTRL_SETA + usPage, ~(_BIT7 | _BIT5 | _BIT4 | _BIT2), ((ucColorChannel << 4) | ((BYTE)bLocation << 2)));

    // Specify address
    ScalerSetBit(P9_D9_POST_GAMMA_CTRL_SETA + usPage, ~_BIT3, _BIT3);
    ScalerSetByte(P9_D8_POST_GAMMA_PORT_SETA + usPage, HIBYTE(usOffset));
    ScalerSetByte(P9_D8_POST_GAMMA_PORT_SETA + usPage, LOBYTE(usOffset));
    ScalerSetBit(P9_D9_POST_GAMMA_CTRL_SETA + usPage, ~(_BIT7 | _BIT3), _BIT7);
}

//--------------------------------------------------
// Description  : Adjust post gamma
// Input Value  : SelRegion ans Gamma Table and Gamma Table Banks and Table Length
// Output Value : None
//--------------------------------------------------
void ScalerColorPostGammaAdjust(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE ucBankNum)
{
    EnumHLWStatus enumHLWStatus = ScalerColorPostGammaGetHLWRegionStatus(enumSelRegion);
    WORD usPage = _REG_MAIN1_PAGE;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if((ScalerGetBit(P9_D9_POST_GAMMA_CTRL_SETA, _BIT6) == _BIT6) && (enumHLWStatus == _HLW_ON)) // Gamma On && No Bypass
    {
        ScalerColorPostGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);

        // Load gamma table of R Channel
        ScalerColorPostGammaChannelCtrl(usPage, _GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, _POST_GAMMA_TABLE_SIZE, ucBankNum, P9_D8_POST_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        ScalerColorPostGammaChannelCtrl(usPage, _GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + _POST_GAMMA_TABLE_SIZE, _POST_GAMMA_TABLE_SIZE, ucBankNum, P9_D8_POST_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        ScalerColorPostGammaChannelCtrl(usPage, _GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + (_POST_GAMMA_TABLE_SIZE * 2), _POST_GAMMA_TABLE_SIZE, ucBankNum, P9_D8_POST_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P9_D9_POST_GAMMA_CTRL_SETA + usPage, ~_BIT7, 0x00);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        if(enumSelRegion == _FULL_REGION)
        {
            // Load gamma table of R Channel
            ScalerColorPostGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray, _POST_GAMMA_TABLE_SIZE, ucBankNum, P49_D8_POST_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Load gamma table of G Channel
            ScalerColorPostGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray + _POST_GAMMA_TABLE_SIZE, _POST_GAMMA_TABLE_SIZE, ucBankNum, P49_D8_POST_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Load gamma table of B Channel
            ScalerColorPostGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray + (_POST_GAMMA_TABLE_SIZE * 2), _POST_GAMMA_TABLE_SIZE, ucBankNum, P49_D8_POST_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Disable Port Access
            ScalerSetBit(P49_D9_GAMMA_CTRL_SETB, ~_BIT7, 0x00);
        }
#endif
        ScalerColorPostGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
    }
    else
    {
        // Load gamma table of R Channel
        ScalerColorPostGammaChannelCtrl(usPage, _GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, _POST_GAMMA_TABLE_SIZE, ucBankNum, P9_D8_POST_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        ScalerColorPostGammaChannelCtrl(usPage, _GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + _POST_GAMMA_TABLE_SIZE, _POST_GAMMA_TABLE_SIZE, ucBankNum, P9_D8_POST_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        ScalerColorPostGammaChannelCtrl(usPage, _GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + (_POST_GAMMA_TABLE_SIZE * 2), _POST_GAMMA_TABLE_SIZE, ucBankNum, P9_D8_POST_GAMMA_PORT_SETA + usPage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P9_D9_POST_GAMMA_CTRL_SETA + usPage, ~_BIT7, 0x00);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        if(enumSelRegion == _FULL_REGION)
        {
            // Load gamma table of R Channel
            ScalerColorPostGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray, _POST_GAMMA_TABLE_SIZE, ucBankNum, P49_D8_POST_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Load gamma table of G Channel
            ScalerColorPostGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray + _POST_GAMMA_TABLE_SIZE, _POST_GAMMA_TABLE_SIZE, ucBankNum, P49_D8_POST_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Load gamma table of B Channel
            ScalerColorPostGammaChannelCtrl(_REG_MAIN2_PAGE, _GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
            ScalerBurstWrite(pucGammaTableArray + (_POST_GAMMA_TABLE_SIZE * 2), _POST_GAMMA_TABLE_SIZE, ucBankNum, P49_D8_POST_GAMMA_PORT_SETB, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Disable Port Access
            ScalerSetBit(P49_D9_GAMMA_CTRL_SETB, ~_BIT7, 0x00);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Post Gamma
// Input Value  : _FUNCTION_ON / _FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorPostGammaEnable(EnumSelRegion enumSelRegion, EnumFunctionOnOFF enumOn)
{
    WORD usPage = _REG_MAIN1_PAGE;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P9_D9_POST_GAMMA_CTRL_SETA + usPage, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P9_D9_POST_GAMMA_CTRL_SETA + usPage, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Output Gamma Enable Region
// Input Value  : SelRegion and EnumDBApply, and _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorPostGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    BYTE ucHlwSetting = ScalerGetByte(P9_DB_POST_GAMMA_OGC_HLW_CONTROL);
    BYTE ucMask = 0;

    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_INSIDE_WINDOW:
            ucMask = _BIT3;
            break;

        case _HLW_OUTSIDE_WINDOW:
            ucMask = _BIT2;
            break;

        case _HLW_FULL_WINDOW:
        default:
            ucMask = (_BIT3 | _BIT2);
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

    ScalerSetByte(P9_DB_POST_GAMMA_OGC_HLW_CONTROL, ucHlwSetting);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Output Gamma Highlight Window Status
// Input Value  : EnumSelRegion
// Output Value : EnumHLWStatus - Output Gamma Highlight Window ON/OFF Status
//--------------------------------------------------
EnumHLWStatus ScalerColorPostGammaGetHLWRegionStatus(EnumSelRegion enumSelRegion)
{
    EnumHLWType enumHLWType = ScalerRegionGetSelectRegionHLWArea(enumSelRegion);
    EnumHLWStatus enumHLWStatus = _HLW_ON;

    switch(enumHLWType)
    {
        case _HLW_INSIDE_WINDOW:
            if((ScalerGetBit(P9_DB_POST_GAMMA_OGC_HLW_CONTROL, (_BIT3 | _BIT2)) & _BIT3) == _BIT3)
            {
                enumHLWStatus = _HLW_OFF;
            }
            break;

        case _HLW_OUTSIDE_WINDOW:
            if((ScalerGetBit(P9_DB_POST_GAMMA_OGC_HLW_CONTROL, (_BIT3 | _BIT2)) & _BIT2) == _BIT2)
            {
                enumHLWStatus = _HLW_OFF;
            }
            break;

        default:
            if(ScalerGetBit(P9_DB_POST_GAMMA_OGC_HLW_CONTROL, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
            {
                enumHLWStatus = _HLW_OFF;
            }
            break;
    }

    return enumHLWStatus;
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Set Post Gamma Effect Region
// Input Value  : SelRegion and EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorPostGammaSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerSetBit(P9_DB_POST_GAMMA_OGC_HLW_CONTROL, ~(_BIT1 | _BIT0), (BYTE)enumSetSel);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#endif
#endif  // End of #if(_COLOR_IP_P_GAMMA == _ON)

