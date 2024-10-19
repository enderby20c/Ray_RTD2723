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
// ID Code      : ScalerColorPanelUniformity.c
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
#if(_COLOR_IP_UNIFORMITY == _ON)
//--------------------------------------------------
// Description  : Initial Panel Uniformity Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityInitial(void)
{
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (((_PANEL_UNIFORMITY_HOR_INTERVAL / 64) << 5) | ((_PANEL_UNIFORMITY_VER_INTERVAL / 64) << 3)));
    ScalerSetByte(P34_02_UN_GAIN_LUT_HOR_GRIDS, _PANEL_UNIFORMITY_HOR_GRIDS);
    ScalerSetByte(P34_03_UN_GAIN_LUT_VER_GRIDS, _PANEL_UNIFORMITY_VER_GRIDS);
    ScalerSetByte(P34_04_UN_GAIN_LUT_HOR_OFFSET, _PANEL_UNIFORMITY_HOR_OFFSET);
    ScalerSetByte(P34_05_UN_GAIN_LUT_VER_OFFSET, _PANEL_UNIFORMITY_VER_OFFSET);
#if(_HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT == _ON)
    // disable uniformity db enable bit
    ScalerColorPanelUniformityDBModeEnable(_DISABLE);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        // change to setbit
        ScalerSetByte(P34_0B_UN_FRONT_BACK_MODE, _BIT7);
        if(_PANEL_UNIFORMITY_HOR_GRIDS % 2 == 0)
        {
            ScalerSetByte(P34_0C_UN_GAIN_LUT_HOR_BACK_OFFSET, (_PANEL_UNIFORMITY_HOR_INTERVAL / 2));
        }
        else
        {
            ScalerSetByte(P34_0C_UN_GAIN_LUT_HOR_BACK_OFFSET, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Load Panel Uniformity LUT
// Input Value  : LUT, Bank number, EnumUniformityModeSelect
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityAdjust(BYTE *pucUNILUT, DWORD ulUNILUTSize, BYTE ucBankNum, EnumUniformityModeSelect enumUniformityMode, EnumUniformityLevelSelect enumUniformityLevel)
{
    BYTE ucMultiLUTMode = 0;
    WORD usLUTAddr = (WORD)(DWORD)pucUNILUT;

#if(_PCM_FULL_TIME_FUNCTION == _ON)
    enumUniformityMode = _UNIFORMITY_PCM_MODE;
#endif

    switch(enumUniformityLevel)
    {
        default:
            break;

        case _UNIFORMITY_1LEVEL:

            ucMultiLUTMode = 0;
            break;

        case _UNIFORMITY_4LEVEL:

            ucMultiLUTMode = 2;
            break;

        case _UNIFORMITY_5LEVEL:

            ucMultiLUTMode = 3;
            break;
    }

    ScalerSetBit(P34_01_UN_MULTI_LUT_CTRL, ~(_BIT1 | _BIT0), (ucMultiLUTMode & 0x03));

    // Set uniformity mode
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT1, (enumUniformityMode << 1));

    // Enable uniformity access
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, _BIT2);

    // Load uniformity gain LUT
    if(ulUNILUTSize > 65536)
    {
        if(usLUTAddr == 0) // burstwrite maximum length is 65535. if burstwite length > 65535, dividing in two parts, 1 byte and 65535 bytes.
        {
            ScalerBurstWrite(pucUNILUT, 1, ucBankNum, P34_08_UN_GAIN_LUT_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
            ScalerBurstWrite(pucUNILUT + 1, 65536 - usLUTAddr - 1, ucBankNum, P34_08_UN_GAIN_LUT_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        }
        else
        {
            ScalerBurstWrite(pucUNILUT, 65536 - usLUTAddr, ucBankNum, P34_08_UN_GAIN_LUT_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        }
        ScalerBurstWrite(0x00, ulUNILUTSize - (65536 - usLUTAddr), ucBankNum + 1, P34_08_UN_GAIN_LUT_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
    else
    {
        ScalerBurstWrite(pucUNILUT, ulUNILUTSize, ucBankNum, P34_08_UN_GAIN_LUT_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
    // Disable uniformity access
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, 0x00);
}

//--------------------------------------------------
// Description  : Load Panel Uniformity LUT
// Input Value  : LUT, Bank number, EnumUniformityModeSelect
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityDecayAdjust(BYTE *pucUNILUT, WORD usUNILUTSize, BYTE ucBankNum, EnumUniformityModeSelect enumUniformityMode, BYTE ucDecayDegree)
{
#if(_PCM_FULL_TIME_FUNCTION == _ON)
    enumUniformityMode = _UNIFORMITY_PCM_MODE;
#endif

    // Set degree of decay
    if(enumUniformityMode == _UNIFORMITY_PCM_MODE)
    {
        if(ucDecayDegree == _UNIFORMITY_5LEVEL)
        {
            ScalerSetBit(P34_01_UN_MULTI_LUT_CTRL, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        }
        else
        {
            ScalerSetBit(P34_01_UN_MULTI_LUT_CTRL, ~(_BIT5 | _BIT4), ((ucDecayDegree / 2) << 4));
        }
    }
    else
    {
        // Enable uniformity access
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, _BIT2);

        // Load uniformity gain LUT
        ScalerBurstWrite(pucUNILUT, usUNILUTSize, ucBankNum, P34_14_UN_DECAY_LUT_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable uniformity access
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Panel Uniformity
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Load Panel Uniformity LUT
// Input Value  : LUT, Bank number, EnumUniformityModeSelect
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityOffsetAdjust(BYTE *pucUNILUT, WORD usUNILUTSize, BYTE ucBankNum)
{
    // Enable uniformity access
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, _BIT2);

    // Load uniformity offset LUT
    ScalerBurstWrite(pucUNILUT, usUNILUTSize, ucBankNum, P34_0F_UN_OFFSET_LUT_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable uniformity access
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, 0x00);
}

//--------------------------------------------------
// Description  : Enable/Disable Panel Uniformity Level0
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityOffsetEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Panel Uniformity Region Enable
// Input Value  : EnumSelRegion, EnumDBApply, Enable bit
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    BYTE ucHlwSetting = 0;
    BYTE ucMask = 0;

    if(enumSelRegion == _NON_REGION)
    {
        return;
    }

    ucHlwSetting = ScalerGetByte(P34_18_UN_HLW_CONTROL);

    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_INSIDE_WINDOW:
            ucMask = _BIT1;
            break;

        case _HLW_OUTSIDE_WINDOW:
            ucMask = _BIT0;
            break;

        case _HLW_FULL_WINDOW:
        default:
            ucMask = (_BIT1 | _BIT0);
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
    ScalerSetByte(P34_18_UN_HLW_CONTROL, ucHlwSetting);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

#if(_HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Uniformity DB sram mode enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityDBModeEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P34_17_UN_GAIN_DB_CONTROL, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P34_17_UN_GAIN_DB_CONTROL, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Uniformity DB sram mode apply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityDBModeApply(void)
{
    ScalerSetBit(P34_17_UN_GAIN_DB_CONTROL, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : Uniformity DB sram mode sram select
// Input Value  : bSramSelect
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityDBModeSetSram(bit bSramSelect)
{
    ScalerSetBit(P34_17_UN_GAIN_DB_CONTROL, ~_BIT1, (bSramSelect << 1));
}

//--------------------------------------------------
// Description  : Uniformity DB sram mode check apply bit done
// Input Value  : None
// Output Value : apply done true/false
//--------------------------------------------------
bit ScalerColorPanelUniformityDBModeApplyDone(void)
{
    return (bit)(ScalerGetBit(P34_17_UN_GAIN_DB_CONTROL, _BIT2) == 0);
}

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Initial Panel Uniformity Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityLowBlueLightInitial(void)
{
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (((_DYNAMIC_LOWBLUE_UNIFORMITY_HOR_INTERVAL / 64) << 5) | ((_DYNAMIC_LOWBLUE_UNIFORMITY_VER_INTERVAL / 64) << 3)));
    ScalerSetByte(P34_02_UN_GAIN_LUT_HOR_GRIDS, _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_GRIDS);
    ScalerSetByte(P34_03_UN_GAIN_LUT_VER_GRIDS, _DYNAMIC_LOWBLUE_UNIFORMITY_VER_GRIDS);
    ScalerSetByte(P34_04_UN_GAIN_LUT_HOR_OFFSET, _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_OFFSET);
    ScalerSetByte(P34_05_UN_GAIN_LUT_VER_OFFSET, _DYNAMIC_LOWBLUE_UNIFORMITY_VER_OFFSET);
    // enable uniformity db enable bit
    ScalerColorPanelUniformityDBModeEnable(_ENABLE);
}

//--------------------------------------------------
// Description  : Dyanmic Low Blue write bytes to uniformity
// Input Value  : LUT, length, rGain, gGain, bGain,  Bank number, EnumUniformityModeSelect, level
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityLowBlueAdjust(StructColorDynamicLowBluePara stColorDynamicLowBluePara)
{
    WORD usI = 0;
    BYTE pucArray[5] = {0};
    BYTE ucMultiLUTMode = 0;
    WORD usRedGain = 0;
    WORD usGreenGain = 0;
    WORD usBlueGain = 0;
    bit bColorPanelUniformitySramIndex = 0;
    if(!ScalerColorPanelUniformityDBModeApplyDone())
    {
        return;
    }

    ScalerSetBit(P34_01_UN_MULTI_LUT_CTRL, ~(_BIT1 | _BIT0), (ucMultiLUTMode & 0x03));

    // Set uniformity mode
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT1, (_UNIFORMITY_PCM_MODE << 1));

    // Enable uniformity access
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, _BIT2);

    // Load uniformity gain LUT
    for(usI = 0; usI < stColorDynamicLowBluePara.usLength; usI++)
    {
        if(stColorDynamicLowBluePara.pusGainArray[usI] != 0)
        {
            usRedGain = (DWORD)(stColorDynamicLowBluePara.usLowBlueGainR * stColorDynamicLowBluePara.pusGainArray[usI]) / stColorDynamicLowBluePara.usLowBlueGainB;
            usGreenGain = (DWORD)(stColorDynamicLowBluePara.usLowBlueGainG * stColorDynamicLowBluePara.pusGainArray[usI]) / stColorDynamicLowBluePara.usLowBlueGainB;
            usBlueGain = stColorDynamicLowBluePara.pusGainArray[usI];
            if(stColorDynamicLowBluePara.pusGainArray[usI] > stColorDynamicLowBluePara.usLowBlueGainB)
            {
                usRedGain = stColorDynamicLowBluePara.usLowBlueGainR;
                usGreenGain = stColorDynamicLowBluePara.usLowBlueGainG;
            }
            pucArray[0] = (((usRedGain >> 12) & 0x01) << 6) | (((usGreenGain >> 12) & 0x01) << 5) | (((usBlueGain >> 12) & 0x01) << 4) | ((usRedGain >> 8) & 0x0F);
            pucArray[1] = (usRedGain & 0xFF);
            pucArray[2] = (((usGreenGain >> 8) & 0x0F) << 4) | ((usBlueGain >> 8) & 0x0F);
            pucArray[3] = (usGreenGain & 0xFF);
            pucArray[4] = (usBlueGain & 0xFF);
        }
        else
        {
            memset(pucArray, 0, 5);
        }
        ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, pucArray[0]);
        ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, pucArray[1]);
        ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, pucArray[2]);
        ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, pucArray[3]);
        ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, pucArray[4]);
    }
    // Disable uniformity access
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, 0x00);

    // get current sram index, 0: HW use sram1, FW update sram2, 1: HW use sram2, FW update sram1
    bColorPanelUniformitySramIndex = (ScalerGetBit(P34_17_UN_GAIN_DB_CONTROL, _BIT1)) >> 1;
    // set swap uniformity sram
    ScalerColorPanelUniformityDBModeSetSram(!bColorPanelUniformitySramIndex);
    // apply db sram
    ScalerColorPanelUniformityDBModeApply();
}

//--------------------------------------------------
// Description  : Dyanmic Low Blue clear bytes
// Input Value  : LUT, length, rGain, gGain, bGain,  Bank number, EnumUniformityModeSelect, level
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityLowBlueClearSram(WORD usLength)
{
    WORD usI = 0;
    BYTE ucMultiLUTMode = 0;
    bit bColorPanelUniformitySramIndex = 0;
    BYTE ucI = 0;
    for(ucI = 0; ucI < 2; ucI++)
    {
        if(!ScalerColorPanelUniformityDBModeApplyDone())
        {
            return;
        }
        ScalerSetBit(P34_01_UN_MULTI_LUT_CTRL, ~(_BIT1 | _BIT0), (ucMultiLUTMode & 0x03));

        // Set uniformity mode
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT1, (_UNIFORMITY_PCM_MODE << 1));
        // Enable uniformity access
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, _BIT2);

        // Load uniformity gain LUT
        for(usI = 0; usI < usLength; usI++)
        {
            ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, 0x00);
            ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, 0x00);
            ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, 0x00);
            ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, 0x00);
            ScalerSetByte(P34_08_UN_GAIN_LUT_ACCESS_PORT, 0x00);
        }
        // Disable uniformity access
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT2, 0x00);

        // get current sram index, 0: HW use sram1, FW update sram2, 1: HW use sram2, FW update sram1
        bColorPanelUniformitySramIndex = (ScalerGetBit(P34_17_UN_GAIN_DB_CONTROL, _BIT1)) >> 1;
        // set swap uniformity sram
        ScalerColorPanelUniformityDBModeSetSram(!bColorPanelUniformitySramIndex);
        // apply db sram
        ScalerColorPanelUniformityDBModeApply();

        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }
}
#endif
#endif
#endif

