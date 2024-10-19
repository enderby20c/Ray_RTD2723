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
// ID Code      : ScalerColorLocalContrast.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
BYTE code tCOLOR_LOCALCONTRAST_DEFAULT_SETTING_R3[] =
{
#include <Color/LocalContrast/LocalContrastDefaultTable_R3.h>
};
#endif
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
WORD g_pusColorLocalContrastYavgArray[(_LOCAL_CONTRAST_READYAVG_HBLKNUM * _LOCAL_CONTRAST_READYAVG_VBLKNUM)];
#endif
#endif
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
//--------------------------------------------------
// Description  : Check if LocalContrast support
// Input Value  : enumSelRegion
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerColorLocalContrastCheckRegionSupport(EnumSelRegion enumSelRegion)
{
    // LocalContrast only support 1P/ PIP/PBPLR, demo inside, Full region
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
        case _2P_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
        case _2P_PIP_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
#endif
            return _TRUE;

        case _FULL_REGION:
        case _DEMO_INSIDE:

            switch (GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    return _TRUE;

                default:
                    return _FALSE;
            }

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check if LocalContrast enumSelRegion,
// Input Value  : ucIndex, enumSelRegion
// Output Value : enumSelRegion
//--------------------------------------------------
EnumSelRegion ScalerColorLocalContrastGetRegionStatus(BYTE ucIndex, EnumSelRegion enumSelRegion)
{
    // _FULL_REGION & _DEMO_INSIDE case return Main in ucIndex = 0, return Sub in ucIndex = 1, not support demo_outside
    if((enumSelRegion == _FULL_REGION) || (enumSelRegion == _DEMO_INSIDE))
    {
        switch(ucIndex)
        {
            case 0:
                switch(GET_DISPLAY_MODE())
                {
                    case _DISPLAY_MODE_1P:
                        return _1P_NORMAL_REGION;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP:
                        return _2P_PIP_MAIN;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                        return _2P_PIP_EAGLE_SIGHT_MAIN;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                        return _2P_PBP_LR_EQUAL_L;

                    case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                        return _2P_PBP_LR_L_LARGE_L;

                    case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                        return _2P_PBP_LR_R_LARGE_R;
#endif

                    default:
                        return _NON_REGION;
                }

            case 1:
                switch(GET_DISPLAY_MODE())
                {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP:
                        return _2P_PIP_SUB;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                        return _2P_PIP_EAGLE_SIGHT_SUB;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                        return _2P_PBP_LR_EQUAL_R;

                    case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                        return _2P_PBP_LR_L_LARGE_R;

                    case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                        return _2P_PBP_LR_R_LARGE_L;
#endif

                    case _DISPLAY_MODE_1P:
                    default:
                        return _NON_REGION;
                }

            default:
                return _NON_REGION;
        }
    }
    else
    {
        switch(ucIndex)
        {
            case 0:
                return enumSelRegion;

            case 1:
            default:
                return _NON_REGION;
        }
    }
}

//--------------------------------------------------
// Description  : LocalContrast Adjust
// Input Value  : LocalContrast Table and ucBankNum
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastAdjust(EnumSelRegion enumSelRegion, BYTE *pucTable, BYTE ucBankNum, WORD usTableSize)
{
    BYTE ucIndex = 0;
    BYTE ucTempAddr = 0;
    BYTE ucTempPage = 0;
    WORD usShfitPage = 0;
    WORD usCurrentPage = 0;

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        if(pucTable != _NULL_POINTER)
        {
            ScalerFlashRead(ucBankNum, &pucTable[(_HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET - 1)], 1, &ucTempPage);
            ScalerFlashRead(ucBankNum, &pucTable[(_HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET + 2)], 1, &ucTempAddr);

            usCurrentPage = ((WORD)ucTempPage << 8);

            if(usCurrentPage == _LOCAL_CONTRAST_R1_PART1_PAGE)
            {
                usShfitPage = ScalerColorLocalContrastPagePart1Mapping(enumCurrRegion);
            }
            else
            {
                usShfitPage = ScalerColorLocalContrastPagePart2Mapping(enumCurrRegion);
            }

            ScalerBurstWrite(&pucTable[_HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET], (usTableSize - _HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET), ucBankNum, (usCurrentPage + usShfitPage + (WORD)ucTempAddr), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // R1 in FB mode, Set Back regs again
            if(ScalerColorLocalContrastCheckR1FBStatus(usShfitPage) == _TRUE)
            {
                // Mapping R1 CurrentPage to R3
                if(usCurrentPage == _LOCAL_CONTRAST_R1_PART1_PAGE)
                {
                    usCurrentPage = _LOCAL_CONTRAST_R3_PART1_PAGE;
                }
                else
                {
                    usCurrentPage = _LOCAL_CONTRAST_R3_PART2_PAGE;
                }

                ScalerBurstWrite(&pucTable[_HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET], (usTableSize - _HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET), ucBankNum, (usCurrentPage + (WORD)ucTempAddr), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
            }
#endif
        }
        else
        {
            // Disable Tone-mapping & Sharpness & Histogram calculation & Temporal Filter
            ScalerSetByte(P32_00_LC_GLOBAL_CTRL0_2_R1 + usShfitPage, 0x00);
            ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + usShfitPage, ~(_BIT1 | _BIT0), 0x00);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // R1 in FB mode, Set Back regs again
            if(ScalerColorLocalContrastCheckR1FBStatus(usShfitPage) == _TRUE)
            {
                // Disable Tone-mapping & Sharpness & Histogram calculation & Temporal Filter
                ScalerSetByte(P32_00_LC_GLOBAL_CTRL0_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x00);
                ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT1 | _BIT0), 0x00);
            }
#endif
        }
    }
}

//--------------------------------------------------
// Description  : LocalContrast Global scene change thd finetune
// Input Value  : LocalContrast Table and ucBankNum
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastGlobalSceneChangeThdAdjust(EnumSelRegion enumSelRegion)
{
    WORD usGlobalSCThd = 0;
    WORD usTargetGlobalSCThd = 0;
    WORD usHWidth = 0;
    WORD usVHeight = 0;
    BYTE ucHistMode = 0;
    BYTE ucIndex = 0;
    WORD usPage = 0;

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart1Mapping(enumCurrRegion);

        // Read Back Global Scene Change Value in Table
        usGlobalSCThd = ((ScalerGetByte(P32_75_LC_TEMPORAL_CTRL4_1_R1 + usPage)) << 8) + ScalerGetByte(P32_76_LC_TEMPORAL_CTRL4_0_R1 + usPage);

        // Panel size
        if(usPage == _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT)    // R1
        {
            usHWidth = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH);
            usVHeight = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT);
        }
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        else                    // R2
        {
            usHWidth = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_WIDTH);
            usVHeight = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_HEIGHT);
        }
#endif

        ucHistMode = (BYTE)(ScalerGetBit(P32_0F_LC_GLOBAL_CTRL3_2_R1 + usPage, (_BIT7 | _BIT6 | _BIT5))) >> 5;

        // Adjust Global scene change thd by current resolution, thd value in table is based on 1920 x 1080
        usTargetGlobalSCThd = (WORD)((((DWORD)usHWidth * (DWORD)usVHeight) >> (DWORD)ucHistMode) * (DWORD)usGlobalSCThd / _LOCAL_CONTRAST_GLOBALSC_HWIDTH / _LOCAL_CONTRAST_GLOBALSC_VHEIGHT);

        ScalerSetByte(P32_75_LC_TEMPORAL_CTRL4_1_R1 + usPage, ((usTargetGlobalSCThd >> 8) & 0xFF));

        ScalerSetByte(P32_76_LC_TEMPORAL_CTRL4_0_R1 + usPage, (usTargetGlobalSCThd  & 0xFF));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 in FB mode, Set Back regs again
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            ScalerSetByte(P32_75_LC_TEMPORAL_CTRL4_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((usTargetGlobalSCThd >> 8) & 0xFF));

            ScalerSetByte(P32_76_LC_TEMPORAL_CTRL4_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (usTargetGlobalSCThd  & 0xFF));
        }
#endif
    }
}

//--------------------------------------------------
// Description  : LocalContrast Block scene change thd finetune
// Input Value  : LocalContrast Table and ucBankNum
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastBlockSceneChangeThdAdjust(EnumSelRegion enumSelRegion)
{
    DWORD ulBlockSCThd = 0;
    DWORD ulTargetBlockSCThd = 0;
    BYTE ucHBlknum = 0;
    BYTE ucVBlknum = 0;
    WORD usPage = 0;
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart1Mapping(enumCurrRegion);

        // Read Back Global Scene Change Value in Table
        ulBlockSCThd = ((ScalerGetByte(P32_72_LC_TEMPORAL_CTRL4_4_R1 + usPage) & 0x03) << 16) + ((ScalerGetByte(P32_73_LC_TEMPORAL_CTRL4_3_R1 + usPage) & 0xFF) << 8) + (ScalerGetByte(P32_74_LC_TEMPORAL_CTRL4_2_R1 + usPage) & 0xFF);

        ucHBlknum = (ScalerGetByte(P32_03_LC_GLOBAL_CTRL1_5_R1 + usPage) & 0xFF) + 1;

        ucVBlknum = (ScalerGetByte(P32_04_LC_GLOBAL_CTRL1_4_R1 + usPage) & 0xFF) + 1;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // FB case ucHBlknum = ucHBlknum_FT + ucHBlknum_BK
        if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE) && (usPage == _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT))
        {
            ucHBlknum = ucHBlknum + ((ScalerGetByte(PDD_03_LC_GLOBAL_CTRL1_5_R3 + usPage) & 0xFF) + 1);
        }
#endif

        // Adjust Global scene change thd by current resolution, thd value in table is based on 1920 x 1080
        ulTargetBlockSCThd = (DWORD)((DWORD)ucHBlknum * (DWORD)ucVBlknum * ulBlockSCThd / _LOCAL_CONTRAST_BLOCKSC_HBLKNUM / _LOCAL_CONTRAST_BLOCKSC_VBLKNUM);

        ScalerSetByte(P32_72_LC_TEMPORAL_CTRL4_4_R1 + usPage, ((ulTargetBlockSCThd >> 16) & 0x03));

        ScalerSetByte(P32_73_LC_TEMPORAL_CTRL4_3_R1 + usPage, ((ulTargetBlockSCThd >> 8) & 0xFF));

        ScalerSetByte(P32_74_LC_TEMPORAL_CTRL4_2_R1 + usPage, (ulTargetBlockSCThd  & 0xFF));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 in FB mode, Set Back regs again
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            ScalerSetByte(P32_72_LC_TEMPORAL_CTRL4_4_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((ulTargetBlockSCThd >> 16) & 0x03));

            ScalerSetByte(P32_73_LC_TEMPORAL_CTRL4_3_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((ulTargetBlockSCThd >> 8) & 0xFF));

            ScalerSetByte(P32_74_LC_TEMPORAL_CTRL4_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (ulTargetBlockSCThd  & 0xFF));
        }
#endif
    }
}
#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Clear LocalContrast Global scene change flag
// Input Value  : EnuLocalContrastSceneChangeStatus
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastClearSceneChangeFlag(EnumSelRegion enumSelRegion, EnumLocalContrastSceneChangeStatus enumLocalContrastSceneChangeStatus)
{
    BYTE ucFlag = 0;

    // detect case not include FULL_REGION & demo inside
    WORD usPage = ScalerColorLocalContrastPagePart1Mapping(enumSelRegion);

    switch(enumLocalContrastSceneChangeStatus)
    {
        case _LOCAL_CONTRAST_SCENE_CHANGE_GLOBAL:
            ucFlag = _BIT7;
            break;

        case _LOCAL_CONTRAST_SCENE_CHANGE_BLOCK:
            ucFlag = _BIT6;
            break;

        case _LOCAL_CONTRAST_SCENE_CHANGE_BOTH_GLOBAL_BLOCK:
            ucFlag = (_BIT7 | _BIT6);
            break;

        default:
            break;
    }

    // Write 1 to clear flag
    ScalerSetBit(P32_71_LC_TEMPORAL_CTRL4_5_R1 + usPage, ~(_BIT7 | _BIT6), ucFlag);
}

//--------------------------------------------------
// Description  : Detect LocalContrast scene change flag
// Input Value  : None
// Output Value : EnuLocalContrastSceneChangeStatus
//--------------------------------------------------
bit ScalerColorLocalContrastDetectSceneChangeFlag(EnumSelRegion enumSelRegion, EnumLocalContrastSceneChangeStatus enumLocalContrastSceneChangeStatus)
{
    BYTE ucSCFlag = 0;
    BYTE ucMask = 0;

    // detect case not include FULL_REGION & demo inside
    WORD usPage = ScalerColorLocalContrastPagePart1Mapping(enumSelRegion);

    ucSCFlag = ScalerGetBit(P32_71_LC_TEMPORAL_CTRL4_5_R1 + usPage, (_BIT7 | _BIT6));

    switch(enumLocalContrastSceneChangeStatus)
    {
        case _LOCAL_CONTRAST_SCENE_CHANGE_GLOBAL:
            ucMask = _BIT7;
            break;

        case _LOCAL_CONTRAST_SCENE_CHANGE_BLOCK:
            ucMask = _BIT6;
            break;

        case _LOCAL_CONTRAST_SCENE_CHANGE_BOTH_GLOBAL_BLOCK:
            ucMask = (_BIT7 | _BIT6);
            break;

        case _LOCAL_CONTRAST_SCENE_CHANGE_NONE:
        default:
            break;
    }

    if((ucSCFlag & ucMask) == ucMask)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set Local Contrast Global/ Block Scene Change THD
// Input Value  : enumSelRegion
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastSetSceneChangeTHD(EnumSelRegion enumSelRegion)
{
    BYTE ucIndex = 0;
    WORD usPage = 0;

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart1Mapping(enumCurrRegion);

        // Set Block Scene Change THD
        ScalerSetByte(P32_72_LC_TEMPORAL_CTRL4_4_R1 + usPage, ((_LOCAL_CONTRAST_BLOCKSC_THD >> 16) & 0xFF));
        ScalerSetByte(P32_73_LC_TEMPORAL_CTRL4_3_R1 + usPage, ((_LOCAL_CONTRAST_BLOCKSC_THD >> 8) & 0xFF));
        ScalerSetByte(P32_74_LC_TEMPORAL_CTRL4_2_R1 + usPage, (_LOCAL_CONTRAST_BLOCKSC_THD & 0xFF));

        // Set Global Scene Change THD
        ScalerSetByte(P32_75_LC_TEMPORAL_CTRL4_1_R1 + usPage, ((_LOCAL_CONTRAST_GLOBALSC_THD >> 8) & 0xFF));
        ScalerSetByte(P32_76_LC_TEMPORAL_CTRL4_0_R1 + usPage, (_LOCAL_CONTRAST_GLOBALSC_THD & 0xFF));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 in FB mode, Set Back regs again
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Set Block Scene Change THD
            ScalerSetByte(P32_72_LC_TEMPORAL_CTRL4_4_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((_LOCAL_CONTRAST_BLOCKSC_THD >> 16) & 0xFF));
            ScalerSetByte(P32_73_LC_TEMPORAL_CTRL4_3_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((_LOCAL_CONTRAST_BLOCKSC_THD >> 8) & 0xFF));
            ScalerSetByte(P32_74_LC_TEMPORAL_CTRL4_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (_LOCAL_CONTRAST_BLOCKSC_THD & 0xFF));

            // Set Global Scene Change THD
            ScalerSetByte(P32_75_LC_TEMPORAL_CTRL4_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((_LOCAL_CONTRAST_GLOBALSC_THD >> 8) & 0xFF));
            ScalerSetByte(P32_76_LC_TEMPORAL_CTRL4_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (_LOCAL_CONTRAST_GLOBALSC_THD & 0xFF));
        }
#endif
    }
}
#endif
#endif
//--------------------------------------------------
// Description  : LocalContrast Setting Related to Histogram(Blk num/Blk Size/SU factor)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastBacklightDecision(EnumSelRegion enumSelRegion, EnumLocalContrastReadYavgData enumLocalContrastReadYavgData)
{
    WORD usHWidth_FT = 0;
    WORD usVHeight = 0;
    WORD usDHtotal = 0;
    BYTE ucHBlknum_total = 0;
    BYTE ucVBlknum = 0;
    BYTE ucHBlksize = 0;
    BYTE ucVBlksize = 0;
    BYTE ucLastVBlksize = 0;
    BYTE ucHistMode = 0;
    BYTE ucHistModeShift = 0;
    WORD usTargetTotalPorch = 0;
    WORD usTargetPredoLine = 0;
    WORD usTargetPredoStartLine = 0;
    WORD usFrontInitialPhase1 = 0;
    WORD usFrontInitialPhase2 = 0;
    DWORD ulFrontInitialPhase3 = 0;
    DWORD ulHfactor = 0;
    DWORD ulVfactor = 0;
    DWORD ulVInitialPhase = 0;
    BYTE ucIndex = 0;
    WORD usPage = 0;
    BYTE ucPathCount = 0;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    BYTE ucHBlknum_FT = 0;
    BYTE ucHBlknum_BK = 0;
    WORD usHWidth_BK = 0;
    WORD usHWidth_FB = 0;
    BYTE ucHblknumMax_FB = 0;
    BYTE ucVblknumMax_FB = 0;
    WORD usBackInitialPhase1 = 0;
    WORD usBackInitialPhase2 = 0;
    DWORD ulBackInitialPhase3 = 0;
    BYTE ucHistBlksize_over = 0;
    BYTE ucHistBlksize_left = 0;
#endif
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
    BYTE ucHblknum_Initial = 0;
    BYTE ucVblknum_Initial = 0;
#endif
    StructColorLocalContrastHblkSetting stLocalContrastHblkSetting = {0};
    StructColorLocalContrastVblkSetting stLocalContrastVblkSetting = {0};

    enumLocalContrastReadYavgData = enumLocalContrastReadYavgData;

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart1Mapping(enumCurrRegion);

        // Panel size
        if(usPage == _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT)    // R1
        {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // Judge Lcts FB Enable or not, FBPBPLREQUAL should disable FB mode
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                usHWidth_FT = ScalerDDomainGetFBNoneSepR1a1ActiveHwidth();
                usHWidth_BK = ScalerDDomainGetFBNoneSepR3a1ActiveHwidth();

                usHWidth_FB = usHWidth_FT + usHWidth_BK;

                // Enable FB mode
                ScalerSetBit(P32_02_LC_GLOBAL_CTRL0_0_R1, ~_BIT7, _BIT7);
            }
            else
#endif
            {
                usHWidth_FT = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH);

                // Disable FB mode
                ScalerSetBit(P32_02_LC_GLOBAL_CTRL0_0_R1, ~_BIT7, 0x00);
            }

            usVHeight = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT);

            ucPathCount = _HW_LOCAL_CONTRAST_PATH_COUNT_MAIN;
        }
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        else                    // R2
        {
            usHWidth_FT = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_WIDTH);
            usVHeight = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_HEIGHT);

            ucPathCount = _HW_LOCAL_CONTRAST_PATH_COUNT_SUB;
        }
#endif

        if((usHWidth_FT < _LOCAL_CONTRAST_MIN_HWIDTH) || (usVHeight < _LOCAL_CONTRAST_MIN_VHEIGHT))
        {
            ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
            continue;
        }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // if main is in FB mode, need check R3 Hwidth
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // FB mode need to check usHWidth_BK
            if(usHWidth_BK < _LOCAL_CONTRAST_MIN_HWIDTH)
            {
                ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                continue;
            }
        }
#endif

        // Always Judge DHtotal by R1
        usDHtotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);


        ScalerColorLocalContrastAdjustHtotal(usPage, &usDHtotal);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // check current status == main + FBmode
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
            if(enumLocalContrastReadYavgData == _LOCALCONTRAST_READYAVG_ENABLE)
            {
                ucHblknum_Initial = ScalerColorLocalContrastHBlkInitial(usPage);
                if(ucHblknum_Initial != 0)
                {
                    ucHblknumMax_FB = ucHblknum_Initial;
                }
                else
                {
                    ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                    continue;
                }
            }
            else
#endif
            {
                // check Hwidth size to decide Hblknum_Max
                if(usHWidth_FT == usHWidth_BK)   // 1P & PIP case
                {
                    if(usHWidth_FB > _LOCAL_CONTRAST_HBLKNUM_5K_HWIDTH)  // 8K case
                    {
                        ucHblknumMax_FB = _MAX_HBLKNUM;
                    }
                    else if(usHWidth_FB > _LOCAL_CONTRAST_HBLKNUM_4K_HWIDTH)  // 5k case
                    {
                        ucHblknumMax_FB = _MAX_HBLKNUM_5K / 2;
                    }
                    else
                    {
                        ucHblknumMax_FB = _MAX_HBLKNUM / 2;
                    }
                }
                else     // PBPLR,L !=R
                {
                    ucHblknumMax_FB = _MAX_HBLKNUM;
                }
            }


            // Decide Front/Back which dominate Hblknum
            if(usHWidth_FT >= usHWidth_BK)   // Front active >= Back active
            {
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
                if(enumLocalContrastReadYavgData == _LOCALCONTRAST_READYAVG_ENABLE)
                {
                    ScalerColorLocalContrastHBlkAdjust_Yavg(usHWidth_FT, ucHblknumMax_FB, _MIN_BLKSIZE_FB, &stLocalContrastHblkSetting);
                }
                else
#endif
                {
                    // Front Blk Calculate, need to return ucBlkSetting[2] to judge which case is (equal/over/left)
                    ScalerColorLocalContrastHBlkAdjust(usHWidth_FT, ucHblknumMax_FB, _MIN_BLKSIZE_FB, &stLocalContrastHblkSetting);
                }
                ucHBlknum_FT = stLocalContrastHblkSetting.ucHblknum;
                ucHBlksize = stLocalContrastHblkSetting.ucHblksize;
                ucHistBlksize_over = stLocalContrastHblkSetting.ucBlksize_over;

                ucHistBlksize_left = (usHWidth_FT - (WORD)ucHBlknum_FT * (WORD)ucHBlksize);

                // Setting Hblknum
                ScalerSetByte(P32_03_LC_GLOBAL_CTRL1_5_R1, (ucHBlknum_FT - 1));

                // Setting Hblksize
                ScalerSetByte(P32_06_LC_GLOBAL_CTRL1_2_R1, ucHBlksize);

#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
                if(ucHistBlksize_over != 0)   // over case
                {
                    ScalerSetByte(P32_0A_LC_GLOBAL_CTRL2_4_R1, ucHistBlksize_over);
                    ScalerSetByte(P32_0C_LC_GLOBAL_CTRL2_2_R1, 0x00);
                }
                else                          // left  & equal case
#endif
                {
                    ScalerSetByte(P32_0A_LC_GLOBAL_CTRL2_4_R1, 0x00);
                    ScalerSetByte(P32_0C_LC_GLOBAL_CTRL2_2_R1, ucHistBlksize_left);
                }

                // Calculate Back Blknum, blkHsize is fixed by Front(ucBlkSetting[1] is),
                ScalerColorLocalContrastHBlknumSpecialAdjust(usHWidth_BK, ucHBlksize, &stLocalContrastHblkSetting);

                ucHBlknum_BK = stLocalContrastHblkSetting.ucHblknum;

                // Setting Back Hblknum
                ScalerSetByte(PDD_03_LC_GLOBAL_CTRL1_5_R3, (ucHBlknum_BK - 1));

                // Setting Back Hblksize = Front Hsize
                ScalerSetByte(PDD_06_LC_GLOBAL_CTRL1_2_R3, ucHBlksize);
            }
            else    // Back active > Front active
            {
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
                if(enumLocalContrastReadYavgData == _LOCALCONTRAST_READYAVG_ENABLE)
                {
                    ScalerColorLocalContrastHBlkAdjust_Yavg(usHWidth_BK, ucHblknumMax_FB, _MIN_BLKSIZE_FB, &stLocalContrastHblkSetting);
                }
                else
#endif
                {
                    // Back Blk Calculate, Back width decide the Blksize, back not need to judge specific case(equal/over/left)
                    ScalerColorLocalContrastHBlkAdjust(usHWidth_BK, ucHblknumMax_FB, _MIN_BLKSIZE_FB, &stLocalContrastHblkSetting);
                }

                ucHBlknum_BK = stLocalContrastHblkSetting.ucHblknum;
                ucHBlksize = stLocalContrastHblkSetting.ucHblksize;

                // Setting Back Hblknum
                ScalerSetByte(PDD_03_LC_GLOBAL_CTRL1_5_R3, (ucHBlknum_BK - 1));

                // Setting Hblksize
                ScalerSetByte(PDD_06_LC_GLOBAL_CTRL1_2_R3, ucHBlksize);

                // Calculate Front Blknum
                ScalerColorLocalContrastHBlknumSpecialAdjust(usHWidth_FT, ucHBlksize, &stLocalContrastHblkSetting);

                ucHBlknum_FT = stLocalContrastHblkSetting.ucHblknum;
                ucHistBlksize_over = stLocalContrastHblkSetting.ucBlksize_over;

                ucHistBlksize_left = (usHWidth_FT - (WORD)ucHBlknum_FT * (WORD)ucHBlksize);

                // Setting Hblknum
                ScalerSetByte(P32_03_LC_GLOBAL_CTRL1_5_R1, (ucHBlknum_FT - 1));

                // Setting Front Hblksize, Hblksize is decide by Front
                ScalerSetByte(P32_06_LC_GLOBAL_CTRL1_2_R1, ucHBlksize);

#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
                if(ucHistBlksize_left != 0)   // over case
                {
                    ScalerSetByte(P32_0A_LC_GLOBAL_CTRL2_4_R1, ucHistBlksize_over);
                    ScalerSetByte(P32_0C_LC_GLOBAL_CTRL2_2_R1, 0x00);
                }
                else                        // left  & equal case
#endif
                {
                    ScalerSetByte(P32_0A_LC_GLOBAL_CTRL2_4_R1, 0x00);
                    ScalerSetByte(P32_0C_LC_GLOBAL_CTRL2_2_R1, ucHistBlksize_left);
                }
            }

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
            if(enumLocalContrastReadYavgData == _LOCALCONTRAST_READYAVG_ENABLE)
            {
                ucVblknum_Initial = ScalerColorLocalContrastVBlkInitial(usPage);

                if(ucVblknum_Initial != 0)
                {
                    ucVblknumMax_FB = ucVblknum_Initial;
                    ScalerColorLocalContrastVBlkAdjust_Yavg(usVHeight, ucVblknumMax_FB, _MIN_BLKSIZE, &stLocalContrastVblkSetting);
                }
                else
                {
                    ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                    continue;
                }
            }
            else
#endif
            {
                if(usVHeight > _LOCAL_CONTRAST_VBLKNUM_3K_VHEIGHT)
                {
                    ucVblknumMax_FB = _MAX_VBLKNUM_3K_OVER;
                }
                else if(usVHeight > _LOCAL_CONTRAST_VBLKNUM_2K_VHEIGHT)
                {
                    ucVblknumMax_FB = _MAX_VBLKNUM_2K_OVER;
                }
                else
                {
                    ucVblknumMax_FB = _MAX_VBLKNUM;
                }

                // Calculate Vblk Setting
                ScalerColorLocalContrastVBlkAdjust(usVHeight, ucVblknumMax_FB, _MIN_BLKSIZE, &stLocalContrastVblkSetting);
            }

            ucVBlknum = stLocalContrastVblkSetting.ucVblknum;
            ucVBlksize = stLocalContrastVblkSetting.ucVblksize;
            ucLastVBlksize = stLocalContrastVblkSetting.ucLastVblksize;

            // Setting Vblknum
            ScalerSetByte(P32_04_LC_GLOBAL_CTRL1_4_R1, (ucVBlknum - 1));

            // Setting Vblksize
            ScalerSetByte(P32_08_LC_GLOBAL_CTRL1_0_R1, ucVBlksize);

            // Setting LastBlk BlKsize
            ScalerSetByte(P32_0E_LC_GLOBAL_CTRL2_0_R1, ucLastVBlksize);

            // Setting Vblknum
            ScalerSetByte(P32_04_LC_GLOBAL_CTRL1_4_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (ucVBlknum - 1));

            // Setting Vblksize
            ScalerSetByte(P32_08_LC_GLOBAL_CTRL1_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ucVBlksize);

            // Setting LastBlk BlKsize
            ScalerSetByte(P32_0E_LC_GLOBAL_CTRL2_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ucLastVBlksize);

            ucHistMode = (((DWORD)(usHWidth_FT + usHWidth_BK) * (DWORD)usVHeight) >> 21);

            ucHBlknum_total = ucHBlknum_FT + ucHBlknum_BK;
        }
        else    // EO mode
#endif
        {
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
            if(enumLocalContrastReadYavgData == _LOCALCONTRAST_READYAVG_ENABLE)
            {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                if(ScalerColorLocalContrastBlksizeAdjustCheck(enumCurrRegion) == _FALSE)
                {
                    ScalerColorLocalContrastGetHblknumRefSize(&stLocalContrastHblkSetting);
                }
                else
#endif
                {
                    ucHblknum_Initial = ScalerColorLocalContrastHBlkInitial(usPage);
                    if(ucHblknum_Initial != 0)
                    {
                        ScalerColorLocalContrastHBlkAdjust_Yavg(usHWidth_FT, ucHblknum_Initial, _MIN_BLKSIZE, &stLocalContrastHblkSetting);

                        // if Hblksize smaller than _MIN_BLKSIZE, ucHblknum return 0, than disable LocalContrast
                        if(stLocalContrastHblkSetting.ucHblknum == 0)
                        {
                            ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                            continue;
                        }
                    }
                    else
                    {
                        ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                        continue;
                    }
                }
            }
            else
#endif
            {
                // Front Blk Calculate
                if(usHWidth_FT > _LOCAL_CONTRAST_HBLKNUM_4K_HWIDTH)    // 4K above, include 5K
                {
                    ScalerColorLocalContrastHBlkAdjust(usHWidth_FT, _MAX_HBLKNUM_5K, _MIN_BLKSIZE, &stLocalContrastHblkSetting);
                }
                else    // 4K below case
                {
                    if((_HW_LOCAL_CONTRAST_BY_REGION_PATH_DIFFERENT == _ON) && (usPage != _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT))
                    {
                        // For 6952 case , Sub blknum max limit to (_MAX_HBLKNUM / 2)
                        ScalerColorLocalContrastHBlkAdjust(usHWidth_FT, (_MAX_HBLKNUM / 2), _MIN_BLKSIZE, &stLocalContrastHblkSetting);
                    }
                    else
                    {
                        // Front Blk Calculate
                        ScalerColorLocalContrastHBlkAdjust(usHWidth_FT, _MAX_HBLKNUM, _MIN_BLKSIZE, &stLocalContrastHblkSetting);
                    }
                }
            }

            // EO mode, not need to set over/left pix, ucBlkSetting[2] is not use
            ucHBlknum_total = stLocalContrastHblkSetting.ucHblknum;
            ucHBlksize = stLocalContrastHblkSetting.ucHblksize;

            // Setting Hblknum
            ScalerSetByte(P32_03_LC_GLOBAL_CTRL1_5_R1 + usPage, (ucHBlknum_total - 1));

            // Setting Hblksize
            ScalerSetByte(P32_06_LC_GLOBAL_CTRL1_2_R1 + usPage, ucHBlksize);

            // EO mode not allow left left case
            ScalerSetByte(P32_0A_LC_GLOBAL_CTRL2_4_R1 + usPage, 0x00);
            ScalerSetByte(P32_0C_LC_GLOBAL_CTRL2_2_R1 + usPage, 0x00);

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
            if(enumLocalContrastReadYavgData == _LOCALCONTRAST_READYAVG_ENABLE)
            {
                if(ScalerColorLocalContrastBlksizeAdjustCheck(enumCurrRegion) == _TRUE)
                {
                    ucVblknum_Initial = ScalerColorLocalContrastVBlkInitial(usPage);
                    if(ucVblknum_Initial != 0)
                    {
                        ScalerColorLocalContrastVBlkAdjust_Yavg(usVHeight, ucVblknum_Initial, _MIN_BLKSIZE, &stLocalContrastVblkSetting);

                        // if Hblksize smaller than _MIN_BLKSIZE, pucBlkSetting[1] return 0, than disable LocalContrast
                        if(stLocalContrastVblkSetting.ucVblknum == 0)
                        {
                            ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                            continue;
                        }
                    }
                    else
                    {
                        ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                        continue;
                    }
                }
                else
                {
                    ScalerColorLocalContrastGetVblknumRefSize(&stLocalContrastVblkSetting);
                }
            }
            else
#endif
            {
                // Calculate Vblk Setting
                if(usVHeight > _LOCAL_CONTRAST_VBLKNUM_3K_VHEIGHT)    // 5K above, for 8KPBPLR(L = R) case
                {
                    ScalerColorLocalContrastVBlkAdjust(usVHeight, _MAX_VBLKNUM_3K_OVER, _MIN_BLKSIZE, &stLocalContrastVblkSetting);
                }
                else if(usVHeight > _LOCAL_CONTRAST_VBLKNUM_2K_VHEIGHT)    // 4K above, include 5K
                {
                    ScalerColorLocalContrastVBlkAdjust(usVHeight, _MAX_VBLKNUM_2K_OVER, _MIN_BLKSIZE, &stLocalContrastVblkSetting);
                }
                else        // 4K below case
                {
                    ScalerColorLocalContrastVBlkAdjust(usVHeight, _MAX_VBLKNUM, _MIN_BLKSIZE, &stLocalContrastVblkSetting);
                }
            }

            ucVBlknum = stLocalContrastVblkSetting.ucVblknum;
            ucVBlksize = stLocalContrastVblkSetting.ucVblksize;
            ucLastVBlksize = stLocalContrastVblkSetting.ucLastVblksize;

            // Setting Vblknum
            ScalerSetByte(P32_04_LC_GLOBAL_CTRL1_4_R1 + usPage, (ucVBlknum - 1));

            // Setting Vblksize
            ScalerSetByte(P32_08_LC_GLOBAL_CTRL1_0_R1 + usPage, ucVBlksize);

            // Setting LastBlk BlKsize
            ScalerSetByte(P32_0E_LC_GLOBAL_CTRL2_0_R1 + usPage, ucLastVBlksize);

            ucHistMode = (((DWORD)usHWidth_FT * (DWORD)usVHeight) >> 21);
        }

        // calculate ucHistMode  = 2^n, n = ucHistModeShift
        while(ucHistMode != 0)
        {
            ucHistMode = ucHistMode >> 1;
            ucHistModeShift = ucHistModeShift + 1;
        }

        // Global Hist Shift mode
        ScalerSetBit(P32_0F_LC_GLOBAL_CTRL3_2_R1 + usPage, ~(_BIT7 | _BIT6 | _BIT5), (ucHistModeShift << 5));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs gain
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Global Hist Shift mode for back regs
            ScalerSetBit(P32_0F_LC_GLOBAL_CTRL3_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT7 | _BIT6 | _BIT5), (ucHistModeShift << 5));
        }
#endif

#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
        if(ScalerColorLocalContrastMarginBlockControlAvailable() == _TRUE)
        {
            // Enable Interpolation Hstart new mode to support block over case, block left case will bot be effected by new mode
#if(_HW_LOCAL_CONTRAST_GEN_SEL == _LOCAL_CONTRAST_GEN_3)
            ScalerSetBit(P32_01_LC_GLOBAL_CTRL0_1_R1 + usPage, ~_BIT7, _BIT7);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // R1 FB mode, need to set backregs gain
            if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
            {
                // Enable Interpolation Hstart new mode to support block over case, block left case will bot be effected by new mode
                ScalerSetBit(P32_01_LC_GLOBAL_CTRL0_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~_BIT7, _BIT7);
            }
#endif
#else
            ScalerSetBit(P32_7F_LC_INTER_HCTRL1_4_R1 + usPage, ~_BIT7, _BIT7);
#endif
        }
#endif

        // HW Gen1 new added data ave to histogram
        ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + usPage, ~_BIT5, _BIT5);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs gain
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // HW Gen1 new added data ave to histogram
            ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~_BIT5, _BIT5);
        }
#endif

        // Set the Htabsize & Vtzbsize
        ScalerSetByte(P32_7B_LC_INTER_HCTRL0_3_R1 + usPage, (_BLK_TABHNUM - 1));
        ScalerSetByte(P32_84_LC_INTER_HCTRL2_3_R1 + usPage, (_BLK_TABVNUM - 1));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs gain
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Set the Htabsize & Vtzbsize
            ScalerSetByte(P32_7B_LC_INTER_HCTRL0_3_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (_BLK_TABHNUM - 1));
            ScalerSetByte(P32_84_LC_INTER_HCTRL2_3_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (_BLK_TABVNUM - 1));
        }
#endif
        //=====================================================
        // Decide H direction scaling up factor & initial phase
        //=====================================================
        // Calculate Scaling Factor
        // factor = (tab_num/blk_size)<<21
        ulHfactor = GET_DWORD_MUL_DIV((1UL << (_SU_FACTOR_BIT + 1)), _BLK_TABHNUM, ucHBlksize);
        ulHfactor = (ulHfactor + 1) >> 1;

        // Set the Hfactor
        ScalerSetByte(P32_7C_LC_INTER_HCTRL0_2_R1 + usPage, ((ulHfactor >> 16) & 0x1F));
        ScalerSetByte(P32_7D_LC_INTER_HCTRL0_1_R1 + usPage, ((ulHfactor >> 8) & 0xFF));
        ScalerSetByte(P32_7E_LC_INTER_HCTRL0_0_R1 + usPage, ((ulHfactor) & 0xFF));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs gain
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Set the Hfactor
            ScalerSetByte(P32_7C_LC_INTER_HCTRL0_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((ulHfactor >> 16) & 0x1F));
            ScalerSetByte(P32_7D_LC_INTER_HCTRL0_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((ulHfactor >> 8) & 0xFF));
            ScalerSetByte(P32_7E_LC_INTER_HCTRL0_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ((ulHfactor) & 0xFF));
        }
#endif

        // Calculate Front Hinital Phase
        // R = Input Height /Output Height = Tab size/Block size
        // ideal initial phase: (1+R)*(2^21)/2 = (blk size + tab size)/blocksize*(2^20)
        ulFrontInitialPhase3 = GET_DWORD_MUL_DIV((1UL << (_SU_FACTOR_BIT)), (_BLK_TABHNUM + ucHBlksize), ucHBlksize);
        ulFrontInitialPhase3 = (ulFrontInitialPhase3 + 1) >> 1;

        usFrontInitialPhase2 = (_BLK_TABHNUM - 1);
        usFrontInitialPhase1 = 0;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // FB mode need to modify H inital Phase if necessary(Front over & Front Left case)  & Setting Back Initial Phase
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            if(ucHistBlksize_over != 0)   // over case
            {
                ulFrontInitialPhase3 = ulFrontInitialPhase3 + ulHfactor * ucHistBlksize_over;

                usFrontInitialPhase2 = (WORD)(ulFrontInitialPhase3 >> _SU_FACTOR_BIT);

                ulFrontInitialPhase3 = (ulFrontInitialPhase3 - ((DWORD)usFrontInitialPhase2 << _SU_FACTOR_BIT));

                usFrontInitialPhase2 = usFrontInitialPhase2 + (_BLK_TABHNUM - 1);

                usFrontInitialPhase1 = usFrontInitialPhase2 / _BLK_TABHNUM;

                usFrontInitialPhase2 = usFrontInitialPhase2 - (usFrontInitialPhase1 * _BLK_TABHNUM);

                // Front Normal Hintial Phase1 = 0,
                usFrontInitialPhase1 = usFrontInitialPhase1 + 0;
            }
            else if(ucHistBlksize_left != 0)    // left size
            {
                ulFrontInitialPhase3 = ((DWORD)usFrontInitialPhase2 << _SU_FACTOR_BIT) - ulHfactor * ucHistBlksize_left + ulFrontInitialPhase3;

                usFrontInitialPhase2 = (WORD)(ulFrontInitialPhase3 >> _SU_FACTOR_BIT);

                ulFrontInitialPhase3 = (ulFrontInitialPhase3 - ((DWORD)usFrontInitialPhase2 << _SU_FACTOR_BIT));
            }

            ulBackInitialPhase3 = ulFrontInitialPhase3 + ulHfactor * (DWORD)usHWidth_FT;

            usBackInitialPhase2 = (ulBackInitialPhase3 >> (_SU_FACTOR_BIT));

            ulBackInitialPhase3 = ulBackInitialPhase3 - ((DWORD)usBackInitialPhase2 << (_SU_FACTOR_BIT));

            // Front Inital Phase2 = (_BLK_TABHNUM - 1)
            usBackInitialPhase2 = usBackInitialPhase2 + usFrontInitialPhase2;

            usBackInitialPhase1 = (usBackInitialPhase2 / _BLK_TABHNUM);

            usBackInitialPhase2 = usBackInitialPhase2 - (usBackInitialPhase1 * _BLK_TABHNUM);

            // Front InitalPhase1 = 0
            usBackInitialPhase1 = usBackInitialPhase1 + usFrontInitialPhase1 - (ucHBlknum_FT);

            // Set Front H Inital Phase
            ScalerSetByte(P32_81_LC_INTER_HCTRL1_2_R1 + usPage, (BYTE)(ulFrontInitialPhase3 >> 16) & 0x1F);
            ScalerSetByte(P32_82_LC_INTER_HCTRL1_1_R1 + usPage, (BYTE)(ulFrontInitialPhase3 >> 8) & 0xFF);
            ScalerSetByte(P32_83_LC_INTER_HCTRL1_0_R1 + usPage, (BYTE)(ulFrontInitialPhase3 & 0xFF));

            // Set Front HInitial Tab(Phase 2)
            ScalerSetByte(P32_80_LC_INTER_HCTRL1_3_R1 + usPage, (BYTE)usFrontInitialPhase2);

            // Set Front HInitial Block(Phase 1)
            ScalerSetByte(P32_7F_LC_INTER_HCTRL1_4_R1 + usPage, (BYTE)usFrontInitialPhase1);

            // Set Back HInitial Phase1
            ScalerSetByte(PDD_7F_LC_INTER_HCTRL1_4_R3, (BYTE)usBackInitialPhase1);

            // Set Back HInitial Phase2
            ScalerSetByte(PDD_80_LC_INTER_HCTRL1_3_R3, (BYTE)(usBackInitialPhase2));

            // Set Back H Inital Phase3
            ScalerSetByte(PDD_81_LC_INTER_HCTRL1_2_R3, (BYTE)((ulBackInitialPhase3 >> 16) & 0x1F));
            ScalerSetByte(PDD_82_LC_INTER_HCTRL1_1_R3, (BYTE)((ulBackInitialPhase3 >> 8) & 0xFF));
            ScalerSetByte(PDD_83_LC_INTER_HCTRL1_0_R3, (BYTE)(ulBackInitialPhase3 & 0xFF));
        }
        else    // EO mode
#endif
        {
            // Set H Inital Phase
            ScalerSetByte(P32_81_LC_INTER_HCTRL1_2_R1 + usPage, (BYTE)(ulFrontInitialPhase3 >> 16) & 0x1F);
            ScalerSetByte(P32_82_LC_INTER_HCTRL1_1_R1 + usPage, (BYTE)(ulFrontInitialPhase3 >> 8) & 0xFF);
            ScalerSetByte(P32_83_LC_INTER_HCTRL1_0_R1 + usPage, (BYTE)(ulFrontInitialPhase3 & 0xFF));

            // Set HInitial Tab(Phase 2)
            ScalerSetByte(P32_80_LC_INTER_HCTRL1_3_R1 + usPage, (BYTE)usFrontInitialPhase2);

            // Set HInitial Block(Phase 1)
            ScalerSetByte(P32_7F_LC_INTER_HCTRL1_4_R1 + usPage, (BYTE)usFrontInitialPhase1);
        }

        //=====================================================
        // Decide V direction scaling up factor & initial phase
        //=====================================================
        // Calculate Scaling Factor
        // factor = (tab_num/blk_size)<<21
        ulVfactor = GET_DWORD_MUL_DIV((1UL << (_SU_FACTOR_BIT + 1)), _BLK_TABVNUM, ucVBlksize);
        ulVfactor = (ulVfactor + 1) >> 1;

        // Set the Vfactor
        ScalerSetByte(P32_85_LC_INTER_HCTRL2_2_R1 + usPage, (BYTE)((ulVfactor >> 16) & 0x1F));
        ScalerSetByte(P32_86_LC_INTER_HCTRL2_1_R1 + usPage, (BYTE)((ulVfactor >> 8) & 0xFF));
        ScalerSetByte(P32_87_LC_INTER_HCTRL2_0_R1 + usPage, (BYTE)(ulVfactor & 0xFF));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Set the Vfactor
            ScalerSetByte(P32_85_LC_INTER_HCTRL2_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (BYTE)((ulVfactor >> 16) & 0x1F));
            ScalerSetByte(P32_86_LC_INTER_HCTRL2_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (BYTE)((ulVfactor >> 8) & 0xFF));
            ScalerSetByte(P32_87_LC_INTER_HCTRL2_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (BYTE)(ulVfactor & 0xFF));
        }
#endif
        // Set Initial Phase & Initial Tab
        // R = Input Height /Output Height = Tab size/Block size
        // ideal initial phase: (1+R)*(2^21)/2 = (blk size + tab size)/blocksize*(2^20)
        ulVInitialPhase = GET_DWORD_MUL_DIV((1UL << (_SU_FACTOR_BIT)), (_BLK_TABVNUM + ucVBlksize), ucVBlksize);
        ulVInitialPhase = (ulVInitialPhase + 1) >> 1;

        // Set V Inital pHASE
        ScalerSetByte(P32_8A_LC_INTER_HCTRL3_2_R1 + usPage, (BYTE)((ulVInitialPhase >> 16) & 0x1F));
        ScalerSetByte(P32_8B_LC_INTER_HCTRL3_1_R1 + usPage, (BYTE)((ulVInitialPhase >> 8) & 0xFF));
        ScalerSetByte(P32_8C_LC_INTER_HCTRL3_0_R1 + usPage, (BYTE)(ulVInitialPhase & 0xFF));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Set V Inital pHASE
            ScalerSetByte(P32_8A_LC_INTER_HCTRL3_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (BYTE)((ulVInitialPhase >> 16) & 0x1F));
            ScalerSetByte(P32_8B_LC_INTER_HCTRL3_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (BYTE)((ulVInitialPhase >> 8) & 0xFF));
            ScalerSetByte(P32_8C_LC_INTER_HCTRL3_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (BYTE)(ulVInitialPhase & 0xFF));
        }
#endif

        // Set VInitial Tab
        ScalerSetByte(P32_89_LC_INTER_HCTRL3_3_R1 + usPage, (_BLK_TABVNUM - 1));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Set VInitial Tab
            ScalerSetByte(P32_89_LC_INTER_HCTRL3_3_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, (_BLK_TABVNUM - 1));
        }
#endif

        // Calaulate sfilter pre-do line start cnt
        usTargetPredoStartLine = ScalerColorLocalContrastSfilterPredoAdjust(ucPathCount, ucHBlknum_total, ucVBlknum, usDHtotal, usVHeight);

        // only usTargetPredoStartLine < usVHeight case can do sfilter predo
        if(usTargetPredoStartLine < usVHeight)
        {
            // Setting sfilter pre-do start line_cnt
            ScalerSetByte(P32_53_LC_SPATIAL_CTRL2_1_R1 + usPage, (BYTE)((usTargetPredoStartLine >> 8) & 0x1F));
            ScalerSetByte(P32_54_LC_SPATIAL_CTRL2_0_R1 + usPage, (BYTE)(usTargetPredoStartLine & 0xFF));

            // Enable sfilter pre-do
            ScalerSetBit(P32_53_LC_SPATIAL_CTRL2_1_R1 + usPage, ~_BIT7, _BIT7);

            usTargetPredoLine = usVHeight - usTargetPredoStartLine;
        }
        else
        {
            // Setting sfilter pre-do start line_cnt to 0
            ScalerSetByte(P32_53_LC_SPATIAL_CTRL2_1_R1 + usPage, 0x00);
            ScalerSetByte(P32_54_LC_SPATIAL_CTRL2_0_R1 + usPage, 0x00);

            // Disable sfilter pre-do
            ScalerSetBit(P32_53_LC_SPATIAL_CTRL2_1_R1 + usPage, ~_BIT7, 0x00);

            usTargetPredoLine = 0;
        }

        //-----------------------------------------------------------
        // LC Front Porch limit = cycle_num * reg_lc_hnum * reg_lc_vnum + Sram_shift + interpolation_predo + tfilter_shift
        // cycle_num = 22 ;
        // Sram_shift = reg_lc_hnum * reg_lc_vnum / 2 + 6
        // interpolation_predo = 80, tfilter_shift = 20
        //-----------------------------------------------------------
        usTargetTotalPorch = (_LOCAL_CONTRAST_CYCLE_NUM * ucHBlknum_total * ucVBlknum) + (ucHBlknum_total * ucVBlknum / 2 + _LOCAL_CONTRAST_SRAM_SHIFT_CONSTANT) + _LOCAL_CONTRAST_INTERPOLATION_PREDO + _LOCAL_CONTRAST_TFILTER_SHIFT;

        usTargetTotalPorch = usTargetTotalPorch - (usTargetPredoLine * usDHtotal / ucPathCount);

        // If LocalContrast Porch limit FAIL, disable LocalContrast
        if(ScalerColorLocalContrastCheckPorchStatus(usPage, usTargetTotalPorch, ucPathCount) == _FALSE)
        {
            // Full region demo mode need to transfer enumSelRegion to disable specific region
            ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
        }
        else
        {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // Both ucHBlknum_FT & ucHBlknum_BK has min Hblknum limit in FB mode
            if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
            {
                // Front Inital Phase = 0, ucHBlknum_FT & ucHBlknum_BK must > _LOCAL_CONTRAST_FB_MIN_BLKNUM
                if((usFrontInitialPhase1 == 0) && ((ucHBlknum_FT < _LOCAL_CONTRAST_FB_MIN_BLKNUM) || (ucHBlknum_BK < _LOCAL_CONTRAST_FB_MIN_BLKNUM)))
                {
                    ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                }
                else if((usFrontInitialPhase1 == 1) && ((ucHBlknum_FT < (_LOCAL_CONTRAST_FB_MIN_BLKNUM + 1)) || (ucHBlknum_BK < (_LOCAL_CONTRAST_FB_MIN_BLKNUM + 1))))
                {
                    ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
                }
                else
                {
                    // only when last state is _FUNCTION_OFF, Enable LocalContrast again
                    if(ScalerColorLocalContrastGetEnableStatus(enumCurrRegion) == _FALSE)
                    {
                        ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_ON);
                    }
                }
            }
            else
#endif
            {
                // only when last state is _FUNCTION_OFF, Enable LocalContrast again
                if(ScalerColorLocalContrastGetEnableStatus(enumCurrRegion) == _FALSE)
                {
                    // Full region demo mode need to transfer enumSelRegion to enable specific region
                    ScalerColorLocalContrastEnable(enumCurrRegion, _LOCAL_CONTRAST_ALL_FUNCTION_ON);
                }
            }
        }
    }


#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
    if(enumLocalContrastReadYavgData == _LOCALCONTRAST_READYAVG_ENABLE)
    {
        ScalerColorLocalContrastReadYavgProcEnable(_ENABLE);
    }
    else
    {
        ScalerColorLocalContrastReadYavgProcEnable(_DISABLE);
    }
#endif
}
//--------------------------------------------------
// Description  : Calculate Hblksetting by fixed ucBlkHnumMax
// Input Value  : usDHWidth, ucBlkHnumMax, ucBlkHSizeMin, *pucHBlkSetting
// Output Value : ucVBlkSetting : ucVBlknum, ucVBlksize, ucVLastBlksize
//--------------------------------------------------
void ScalerColorLocalContrastHBlkAdjust(WORD usDHWidth, BYTE ucBlkHnumMax, BYTE ucBlkHSizeMin, StructColorLocalContrastHblkSetting *pstLocalContrastHBlkSetting)
{
    BYTE ucBlksize = ucBlkHSizeMin;
    BYTE ucBlknum = 0;

#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
    BYTE ucRemainPix = 0;
    BYTE ucBlksize_over = 0;
#endif

    if((usDHWidth % (WORD)ucBlkHnumMax) == 0)   // equal case
    {
        ucBlksize = (BYTE)(usDHWidth / (WORD)ucBlkHnumMax);
    }
    else    // not equal case, try to set over case
    {
        ucBlksize = (BYTE)((usDHWidth / (WORD)ucBlkHnumMax) + 1);
    }

    ucBlknum = (BYTE)(usDHWidth / (WORD)MAXOF(ucBlksize, 1));

    // check if ucHBlksize is less than ucHBlksize_min(ucHBlksize_min is different between EO & FB), and recalculate ucBlknum by ucBlkHSizeMin
    if(ucBlksize < ucBlkHSizeMin)
    {
        ucBlksize = ucBlkHSizeMin;
        ucBlknum = usDHWidth / (WORD)ucBlksize;
    }

#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
    if(ScalerColorLocalContrastMarginBlockControlAvailable() == _TRUE)
    {
        ucRemainPix = usDHWidth - ((WORD)ucBlknum * (WORD)ucBlksize);

        // only ucRemainPix(!= 0) >= _MIN_BLKSIZE case, allow to over case; else, ucBlksize_over always = initial =  0
        if((ucRemainPix != 0) && (ucRemainPix >= _MIN_BLKSIZE))
        {
            // left_over_num = ucBlksize - ucRemainPix
            ucBlksize_over = ucBlksize - ucRemainPix;
            ucBlknum = ucBlknum + 1;
        }
    }

    pstLocalContrastHBlkSetting->ucBlksize_over = ucBlksize_over;
#else
    // force to left case
    pstLocalContrastHBlkSetting->ucBlksize_over = 0;
#endif

    pstLocalContrastHBlkSetting->ucHblknum = ucBlknum;
    pstLocalContrastHBlkSetting->ucHblksize = ucBlksize;
}

//--------------------------------------------------
// Description  : Calculate Hblksetting by fixed ucBlkHSize
// Input Value  : usDHWidth, ucBlkHSize, *pucHBlkSetting_sp
// Output Value : ucHBlkSetting_sp : ucBlknum, ucBlkHSize, (ucBlkHSize - ucBlksize_sp)
//--------------------------------------------------
void ScalerColorLocalContrastHBlknumSpecialAdjust(WORD usDHWidth, BYTE ucBlkHSize, StructColorLocalContrastHblkSetting *pstLocalContrastHBlkSetting)
{
    BYTE ucBlknum = 0;

#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
    BYTE ucRemainPix = 0;
    BYTE ucBlksize_over = 0;
#endif

    if(ucBlkHSize != 0)
    {
        // Calculate the ucBlknum by fixed ucBlkHSize
        ucBlknum = usDHWidth / (WORD)ucBlkHSize;
    }

#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
    if(ScalerColorLocalContrastMarginBlockControlAvailable() == _TRUE)
    {
        ucRemainPix = usDHWidth - (ucBlknum * ucBlkHSize);

        // only ucRemainPix(!= 0) >= _MIN_BLKSIZE case, allow to over case; else, ucBlksize_over always = initial =  0
        if((ucRemainPix != 0) && (ucRemainPix >= _MIN_BLKSIZE))
        {
            // left_over_num = ucBlksize - ucRemainPix
            ucBlksize_over = ucBlkHSize - ucRemainPix;
            ucBlknum = ucBlknum + 1;
        }
    }

    pstLocalContrastHBlkSetting->ucBlksize_over = ucBlksize_over;
#else
    // force to left case
    pstLocalContrastHBlkSetting->ucBlksize_over = 0;
#endif

    pstLocalContrastHBlkSetting->ucHblknum = ucBlknum;

    pstLocalContrastHBlkSetting->ucHblksize = ucBlkHSize;
}

//--------------------------------------------------
// Description  : Calculate Vblksetting by fixed ucBlkVnumMax
// Input Value  : usDVHeight, ucBlkVnumMax, ucBlkVSizeMin, *pucVBlkSetting
// Output Value : ucVBlkSetting : ucVBlknum, ucVBlksize, ucVLastBlksize
//--------------------------------------------------
void ScalerColorLocalContrastVBlkAdjust(WORD usDVHeight, BYTE ucBlkVnumMax, BYTE ucBlkVSizeMin, StructColorLocalContrastVblkSetting *pstLocalContrastVBlkSetting)
{
    BYTE ucBlksize = ucBlkVSizeMin;
    BYTE ucBlknum = 0;
    BYTE ucRemainPix = 0;
    BYTE ucLastBlksize = 0;

    // Calculate the BlkHsize & BlkVsize by panel size & HBlknum & VBlknum
    ucBlksize = (BYTE)(usDVHeight / (WORD)ucBlkVnumMax);

    if((usDVHeight % (WORD)ucBlkVnumMax) != 0)
    {
        ucBlksize = ucBlksize + 1;
    }
    ucBlknum = usDVHeight / (WORD)ucBlksize;

    ucRemainPix = usDVHeight - (ucBlknum * ucBlksize);

    // chek if ucHBlksize is less than ucHBlksize_FB_min
    if(ucBlksize < ucBlkVSizeMin)
    {
        ucBlksize = ucBlkVSizeMin;
        ucBlknum = usDVHeight / ucBlksize;

        ucRemainPix = usDVHeight - (ucBlknum * ucBlksize);
    }

    if(ucRemainPix != 0)   // remainder !=0
    {
        // chek if ucBlksize_tmp
        if(ucRemainPix == 1)
        {
            ucLastBlksize = ucBlksize;
        }
        else
        {
            ucLastBlksize = ucRemainPix;
            ucBlknum = ucBlknum + 1;
        }
    }
    else                    // remainder = 0
    {
        // ucBlksize_sp
        ucLastBlksize = ucBlksize;
    }

    pstLocalContrastVBlkSetting->ucVblknum = ucBlknum;
    pstLocalContrastVBlkSetting->ucVblksize = ucBlksize;
    pstLocalContrastVBlkSetting->ucLastVblksize = ucLastBlksize;
}
//--------------------------------------------------
// Description  : Enable / Disable / Clock Gated LocalContrast Function
// Input Value  : enumFunctionOnOff -> _ENABLE or _DISABLE or _CLCOK_GATED
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastEnable(EnumSelRegion enumSelRegion, EnumLocalContrastEnableType enumLocalContrastEnableType)
{
    BYTE ucIndex = 0;
    WORD usPage = 0;

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart1Mapping(enumCurrRegion);

        if(enumLocalContrastEnableType == _LOCAL_CONTRAST_ALL_FUNCTION_ON)
        {
            // Enable Tone-mapping & Sharpness & Histogram Calculation
            ScalerSetBit(P32_00_LC_GLOBAL_CTRL0_2_R1 + usPage, ~(_BIT7 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));
            ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + usPage, ~_BIT0, _BIT0);

            // Default Enable temporal new mode,_BIT6 : (write 1 clear bit need to set for checker rule)
            ScalerSetBit(P32_7A_LC_TEMPORAL_CTRL5_0_R1 + usPage, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Default Enable sc mode on block & global, _BIT7/ _BIT6 : (write 1 clear bit need to set for checker rule)
            ScalerSetBit(P32_71_LC_TEMPORAL_CTRL4_5_R1 + usPage, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));

            // Default Enable spatial new mode
            ScalerSetBit(P32_57_LC_SPATIAL_CTRL3_0_R1 + usPage, ~_BIT1, _BIT1);
            ScalerSetByte(P32_3B_LC_DECISION_CTRL1_2_R1 + usPage, 0x20);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // R1 FB mode, need to set backregs
            if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
            {
                // Enable Tone-mapping & Sharpness & Histogram Calculation
                ScalerSetBit(P32_00_LC_GLOBAL_CTRL0_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT7 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));
                ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~_BIT0, _BIT0);

                // Default Enable temporal new mode,_BIT6 : (write 1 clear bit need to set for checker rule)
                ScalerSetBit(P32_7A_LC_TEMPORAL_CTRL5_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Default Enable sc mode on block & global, _BIT7/ _BIT6 : (write 1 clear bit need to set for checker rule)
                ScalerSetBit(P32_71_LC_TEMPORAL_CTRL4_5_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));

                // Default Enable spatial new mode
                ScalerSetBit(P32_57_LC_SPATIAL_CTRL3_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~_BIT1, _BIT1);
                ScalerSetByte(P32_3B_LC_DECISION_CTRL1_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x20);
            }
#endif
            // After 2 DVS, enable tfilter
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

            ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + usPage, ~_BIT1, _BIT1);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // R1 FB mode, need to set backregs
            if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
            {
                ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~_BIT1, _BIT1);
            }
#endif
        }
        else if(enumLocalContrastEnableType == _LOCAL_CONTRAST_ALL_FUNCTION_OFF)
        {
            // Disable Tone-mapping & Sharpness & Histogram Calculation & Temporal Filter
            ScalerSetBit(P32_00_LC_GLOBAL_CTRL0_2_R1 + usPage, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
            ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + usPage, ~(_BIT1 | _BIT0), 0x00);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // R1 FB mode, need to set backregs
            if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
            {
                // Disable Tone-mapping & Sharpness & Histogram Calculation & Temporal Filter
                ScalerSetBit(P32_00_LC_GLOBAL_CTRL0_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
                ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT1 | _BIT0), 0x00);
            }
#endif

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
            ScalerColorLocalContrastReadYavgProcEnable(_DISABLE);
#endif
        }
        else            // _LOCAL_CONTRAST_HIST_ONLY_ON
        {
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
            ScalerSetBit(P32_00_LC_GLOBAL_CTRL0_2_R1 + usPage, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
            ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + usPage, ~(_BIT1 | _BIT0), _BIT0);        // Disable temporal filter & Enable Hist
#if(_LOCAL_CONTRAST_YAVG_TYPE == _LOCAL_CONTRAST_YAVG_TYPE0)
            ScalerSetByte(P32_3B_LC_DECISION_CTRL1_2_R1 + usPage, 0x20);
            ScalerSetByte(P32_52_LC_SPATIAL_CTRL2_2_R1 + usPage, 0x02);
#else
            ScalerSetByte(P32_3B_LC_DECISION_CTRL1_2_R1 + usPage, 0x3F);
            ScalerSetByte(P32_52_LC_SPATIAL_CTRL2_2_R1 + usPage, 0x03);
#endif
            ScalerSetByte(P32_4D_LC_SPATIAL_CTRL1_3_R1 + usPage, 0x80);
            ScalerSetByte(P32_4E_LC_SPATIAL_CTRL1_2_R1 + usPage, 0x00);
            ScalerSetByte(P32_4F_LC_SPATIAL_CTRL1_1_R1 + usPage, 0x00);
            ScalerSetByte(P32_50_LC_SPATIAL_CTRL1_0_R1 + usPage, 0x00);
            ScalerSetByte(P32_51_LC_SPATIAL_CTRL2_3_R1 + usPage, 0x00);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
            {
                ScalerSetBit(P32_00_LC_GLOBAL_CTRL0_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
                ScalerSetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, ~(_BIT1 | _BIT0), _BIT0);        // Only Enable Hist
#if(_LOCAL_CONTRAST_YAVG_TYPE == _LOCAL_CONTRAST_YAVG_TYPE0)
                ScalerSetByte(P32_3B_LC_DECISION_CTRL1_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x20);
                ScalerSetByte(P32_52_LC_SPATIAL_CTRL2_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x02);
#else
                ScalerSetByte(P32_3B_LC_DECISION_CTRL1_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x3F);
                ScalerSetByte(P32_52_LC_SPATIAL_CTRL2_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x03);
#endif
                ScalerSetByte(P32_4D_LC_SPATIAL_CTRL1_3_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x80);
                ScalerSetByte(P32_4E_LC_SPATIAL_CTRL1_2_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x00);
                ScalerSetByte(P32_4F_LC_SPATIAL_CTRL1_1_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x00);
                ScalerSetByte(P32_50_LC_SPATIAL_CTRL1_0_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x00);
                ScalerSetByte(P32_51_LC_SPATIAL_CTRL2_3_R1 + _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT, 0x00);
            }
#endif
#endif
        }
    }
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable / Disable / Clock Gated LocalContrast Function
// Input Value  : enumFunctionOnOff -> _ENABLE or _DISABLE or _CLCOK_GATED
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastFBInital(void)
{
    // Judge Lcts FB Enable or not, FB mode should enable seperate at first
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
    {
        BYTE ucTempAddr = 0;
        WORD usCurrentPage = 0;

        ScalerSetBit(P32_02_LC_GLOBAL_CTRL0_0_R1, ~_BIT6, _BIT6);

        usCurrentPage = _LOCAL_CONTRAST_R3_PART2_PAGE;

        ScalerFlashRead(GET_CURRENT_BANK_NUMBER(), &tCOLOR_LOCALCONTRAST_DEFAULT_SETTING_R3[(_HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET + 2)], 1, &ucTempAddr);

        ScalerBurstWrite(&tCOLOR_LOCALCONTRAST_DEFAULT_SETTING_R3[_HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET], _HW_LOCAL_CONTRAST_DEFAULT_R3TABLE_PART2_SIZE, GET_CURRENT_BANK_NUMBER(), (usCurrentPage + (WORD)ucTempAddr), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        usCurrentPage = _LOCAL_CONTRAST_R3_PART1_PAGE;

        ScalerFlashRead(GET_CURRENT_BANK_NUMBER(), &tCOLOR_LOCALCONTRAST_DEFAULT_SETTING_R3[(_HW_LOCAL_CONTRAST_DEFAULT_R3TABLE_PART1_OFFSET + 2)], 1, &ucTempAddr);

        ScalerBurstWrite(&tCOLOR_LOCALCONTRAST_DEFAULT_SETTING_R3[_HW_LOCAL_CONTRAST_DEFAULT_R3TABLE_PART1_OFFSET], _HW_LOCAL_CONTRAST_DEFAULT_R3TABLE_PART1_SIZE, GET_CURRENT_BANK_NUMBER(), (usCurrentPage + (WORD)ucTempAddr), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // Double buffer apply
        ScalerSetBit(PDB_30_LC_TONEMAPPING_SRAM_ADDR_3_R3, ~_BIT6, _BIT6);

        // After 1 DVS, make sure default value setting PASS
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Chek current Region is R1 FB mode or not
// Input Value  : Current Region usShfitPage
// Output Value : ON/OFF
//--------------------------------------------------
bit ScalerColorLocalContrastCheckR1FBStatus(WORD usShfitPage)
{
    if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE) && (usShfitPage == _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif
//--------------------------------------------------
// Description  : Calculate Porch limit based on Hblknum & Vblknum
// Input Value  : usPage, usTargetTotalPorch, ucPathCount
// Output Value : ON/OFF
//--------------------------------------------------
bit ScalerColorLocalContrastCheckPorchStatus(WORD usPage, WORD usTargetTotalPorch, BYTE ucPathCount)
{
    WORD usVHeight = 0;
    WORD usDHtotal = 0;
    DWORD ulCurrentTotalPorch = 0;
    WORD usDVtotal = 0;

    // Both Main/Sub Porch size decide by main
    usVHeight = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT);
    usDHtotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);

    ScalerColorLocalContrastAdjustHtotal(usPage, &usDHtotal);

    // pulCurrentPorch = Current TotalPorch
    usDVtotal = ScalerMDomainLocalContrastGetVtotal();

    ulCurrentTotalPorch = ((DWORD)(usDVtotal - usVHeight - ucPathCount) * (DWORD)usDHtotal / ucPathCount);

    if(ulCurrentTotalPorch < (DWORD)usTargetTotalPorch)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : LocalContrast Setting Related to Histogram(Blk num/Blk Size/SU factor)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastAdjustHtotal(WORD usPage, WORD *pusDHtotal)
{
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
    {
        // Htotal need to /2 in FB mode
        *pusDHtotal = *pusDHtotal / 2;
    }
#endif

    if((usPage != _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT) && (_HW_LOCAL_CONTRAST_BY_REGION_PATH_DIFFERENT == _ON))
    {
        // 2M1S case, sub Htotal is 1/2 Hotal_R1
        *pusDHtotal = *pusDHtotal / 2;
    }
}

//-----------------------------------------------------------------------------------------
// Description  : Calculate Spatial Filter/Temporal Filter Predo Line on Hblknum & Vblknum
// Input Value  : ucPathCount, ucHBlknum, ucVBlknum, usDHtotal, usVHeight
// Output Value : ON/OFF
//-----------------------------------------------------------------------------------------
WORD ScalerColorLocalContrastSfilterPredoAdjust(BYTE ucPathCount, BYTE ucHBlknum, BYTE ucVBlknum, WORD usDHtotal, WORD usVHeight)
{
    DWORD ulTargetPredoCycle = 0;
    WORD usTargetPredoLine = 0;
    WORD usTargetPredoStartLine = 0;

    // ucVBlknum MUST >=4 to do pre-do, else usTargetPredoLine value keep = 0
    if(ucVBlknum >= 4)
    {
        ulTargetPredoCycle = ucHBlknum * (ucVBlknum - 3) * 22;

        // ulTargetPredoCycle MUST >= 2 line pix to do pre-do
        if(ulTargetPredoCycle >= (2 * usDHtotal))
        {
            // Keep one line for buffer
            usTargetPredoLine = (ulTargetPredoCycle / usDHtotal) - 1;
        }
    }

    usTargetPredoStartLine = usVHeight - usTargetPredoLine * ucPathCount;

    return usTargetPredoStartLine;
}
//--------------------------------------------------
// Description  : LocalContrast Display Path mapping register Page Part1
//                R1 Part1 Page is 32, R2 Part1 Page is C3
// Input Value  : enumDDomainRegion
// Output Value : usPage
//--------------------------------------------------
WORD ScalerColorLocalContrastPagePart1Mapping(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
#endif
            return 0x0000U;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_SUB:
            return 0x9100U;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_SUB:
            return 0x9100U;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
            return 0x9100U;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_R_LARGE_L:
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                // RL6952, RL6829 FB
                return 0x9100U;
            }
            else
            {
                // RL6829 EO, RL6978
                return 0x0000U;
            }

        case _2P_PBP_LR_R_LARGE_R:
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                // RL6952, RL6829 FB
                return 0x0000U;
            }
            else
            {
                // RL6829 EO, RL6978
                return 0x9100U;
            }
#endif

        default:
            return 0x0000U;
    }
}
//--------------------------------------------------
// Description  : LocalContrast Display Path mapping register Page Part2
//                R1 Part2 Page is 42, R2 Part2 Page is C4.
// Input Value  : enumDDomainRegion
// Output Value : usPage
//--------------------------------------------------
WORD ScalerColorLocalContrastPagePart2Mapping(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
#endif
            return 0x0000U;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_SUB:
            return 0x8200U;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_SUB:
            return 0x8200U;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
            return 0x8200U;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_R_LARGE_L:
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                // RL6952, RL6829 FB
                return 0x8200U;
            }
            else
            {
                // RL6829 EO, RL6978
                return 0x0000U;
            }

        case _2P_PBP_LR_R_LARGE_R:
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                // RL6952, RL6829 FB
                return 0x0000U;
            }
            else
            {
                // RL6829 EO, RL6978
                return 0x8200U;
            }
#endif

        default:
            return 0x0000U;
    }
}

//--------------------------------------------------
// Description  : Set Local Contrast Table DB Apply
// Input Value  : enumSelRegion, enumDBApplyType, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastTableDBApply(EnumSelRegion enumSelRegion, EnumLocalContrastDBApplyType enumDBApplyType, EnumDBApply enumDBApply)
{
    WORD usPage = ScalerColorLocalContrastPagePart2Mapping(enumSelRegion);
    BYTE ucDBApplyType = 0;


    switch(enumDBApplyType)
    {
        case _LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY:
            ucDBApplyType = _BIT6;
            break;

        case _LOCAL_CONTRAST_ALL_APPLY:
            ucDBApplyType = (_BIT7 | _BIT6);
            break;

        default:
            break;
    }

    if((enumSelRegion == _FULL_REGION) || (enumSelRegion == _DEMO_INSIDE))
    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
            {
                // Set R1/R3 LocalContrast DB apply bit.Trigger event is Not adjustable, always trigger by DVS.
                ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1, ~(_BIT7 | _BIT6), ucDBApplyType);
                ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, ~(_BIT7 | _BIT6), ucDBApplyType);
            }
            else    // PIP,PBPLR
            {
                // Set R1/R2/R3 LocalContrast DB apply bit.Trigger event is Not adjustable, always trigger by DVS.
                ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1, ~(_BIT7 | _BIT6), ucDBApplyType);
                ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, ~(_BIT7 | _BIT6), ucDBApplyType);
                ScalerSetBit(PC4_30_LC_TONEMAPPING_SRAM_ADDR_3_R2, ~(_BIT7 | _BIT6), ucDBApplyType);
            }
        }
        else
#endif
        {
            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
            {
                // Set R1 LocalContrast DB apply bit.Trigger event is Not adjustable, always trigger by DVS.
                ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1, ~(_BIT7 | _BIT6), ucDBApplyType);
            }
            else    // PIP,PBPLR
            {
                // Set R1/R2 LocalContrast DB apply bit.Trigger event is Not adjustable, always trigger by DVS.
                ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1, ~(_BIT7 | _BIT6), ucDBApplyType);
                ScalerSetBit(PC4_30_LC_TONEMAPPING_SRAM_ADDR_3_R2, ~(_BIT7 | _BIT6), ucDBApplyType);
            }
        }
    }
    else
    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to set backregs
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Set LocalCpntrast DB apply bit.Trigger event is Not adjustable, always trigger by DVS.
            ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1, ~(_BIT7 | _BIT6), ucDBApplyType);
            ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, ~(_BIT7 | _BIT6), ucDBApplyType);
        }
        else
#endif
        {
            // Set LocalContrast DB apply bit.Trigger event is Not adjustable, always trigger by DVS.
            ScalerSetBit(P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1 + usPage, ~(_BIT7 | _BIT6), ucDBApplyType);
        }
    }

    if(enumDBApply == _DB_APPLY_POLLING)
    {
        // Check D domain status before polling
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) || (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            return;
        }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 FB mode, need to check both R1 & R3 double buffer apply bit to be cleared
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            if((ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1, (_BIT6), 0) == _FALSE) ||
               (ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, (_BIT6), 0) == _FALSE))
            {
                // Disable Display format gen when D domain double buffer timeout
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT0, 0x00);
            }
        }
        else
#endif
        {
            // Wait double buffer apply bit to be cleared
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P42_30_LC_TONEMAPPING_SRAM_ADDR_3_R1 + usPage, (_BIT6), 0) == _FALSE)
            {
                // Disable Display format gen when D domain double buffer timeout
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT0, 0x00);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get LocalContrast Status
// Input Value  : enumSelRegion
// Output Value : ON/OFF
//--------------------------------------------------
bit ScalerColorLocalContrastGetEnableStatus(EnumSelRegion enumSelRegion)
{
    BYTE ucIndex = 0;
    WORD usPage = 0;
    bit bEnable = _FALSE;

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart1Mapping(enumCurrRegion);

        // when meet the rescrict, kernel will disable Tone-mapping/Sharpness/CDM/Temporal Filter/ lc_valid at the same time
        if((ScalerGetBit(P32_00_LC_GLOBAL_CTRL0_2_R1 + usPage, (_BIT7 | _BIT5 | _BIT4)) == 0x00) &&
           (ScalerGetBit(P32_10_LC_GLOBAL_CTRL3_1_R1 + usPage, (_BIT1 | _BIT0)) == 0x00))
        {
            bEnable = _FALSE;
            break;
        }
        else
        {
            bEnable = _TRUE;
        }
    }

    return bEnable;
}

//--------------------------------------------------
// Description  : Adjust Local Contrast Highlight Window Active Region
// Input Value  : enumSelRegion --> OSD Select region
//                enumDBApply
//                bOn --> Enable/Disable the Local Contrast of the OSD select region
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    BYTE ucHlwSetting = 0;
    BYTE ucMask = 0;
    WORD usPage = 0;
    BYTE ucIndex = 0;

    // LocalContrast only one set for per region
    if((enumSelRegion == _NON_REGION) || (enumSelRegion == _DEMO_OUTSIDE))
    {
        return;
    }

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart1Mapping(enumCurrRegion);

        ucHlwSetting = ScalerGetByte(P32_02_LC_GLOBAL_CTRL0_0_R1 + usPage);

        switch(enumSelRegion)
        {
            case _1P_NORMAL_REGION:
            case _FULL_REGION:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _2P_PIP_MAIN:
            case _2P_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _2P_PIP_EAGLE_SIGHT_MAIN:
            case _2P_PIP_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _2P_PBP_LR_EQUAL_R:
            case _2P_PBP_LR_EQUAL_L:
            case _2P_PBP_LR_L_LARGE_R:
            case _2P_PBP_LR_L_LARGE_L:
            case _2P_PBP_LR_R_LARGE_R:
            case _2P_PBP_LR_R_LARGE_L:
#endif
                ucMask = (_BIT1 | _BIT0);
                break;

            // INSIDE
            case _DEMO_INSIDE:
                if(bOn == _OFF)
                {
                    // _DEMO_INSIDE OFF case MUST Bypass Region
                    ucMask = (_BIT1 | _BIT0);
                }
                else
                {
                    ucMask = _BIT1;
                }
                break;

            // ALL MASK
            default:
                ucMask = (_BIT1 | _BIT0);
                bOn = _OFF;
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

        ScalerSetByte(P32_02_LC_GLOBAL_CTRL0_0_R1 + usPage, ucHlwSetting);
    }

    ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion(enumSelRegion), enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust Local Contrast Highlight Window Active Region
// Input Value  : enumSelRegion --> OSD Select region
//                enumDBApply
//                bOn --> Enable/Disable the Local Contrast of the OSD select region
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastBypass(EnumSelRegion enumSelRegion)
{
    WORD usPage = 0;
    BYTE ucIndex = 0;
    BYTE pucYGain_bypass[33] = {0};

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart2Mapping(enumCurrRegion);

        // Tone-mapping bypass
        ScalerSetByte((P42_3B_LC_TONEMAPPING_BLENDING_0_R1 + usPage), 0x00);

        // Yin_gain bypass, Load Yin_gain = 0
        ScalerBurstWrite(pucYGain_bypass, 33, GET_CURRENT_BANK_NUMBER(), P42_40_LC_LOCAL_SHPNR_1ST_GAIN_0_3_R1 + usPage, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_XRAM);

        // Ydiff_gain bypass, Load Ydiff gain = 0
        ScalerBurstWrite(pucYGain_bypass, 33, GET_CURRENT_BANK_NUMBER(), P42_70_LC_LOCAL_SHPNR_2ND_GAIN_0_3_R1 + usPage, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_XRAM);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 in FB mode, Set Back regs again
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Tone-mapping bypass
            ScalerSetByte((P42_3B_LC_TONEMAPPING_BLENDING_0_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT), 0x00);

            // Yin_gain bypass, Load Yin_gain = 0
            ScalerBurstWrite(pucYGain_bypass, 33, GET_CURRENT_BANK_NUMBER(), P42_40_LC_LOCAL_SHPNR_1ST_GAIN_0_3_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_XRAM);

            // Ydiff_gain bypass, Load Ydiff gain = 0
            ScalerBurstWrite(pucYGain_bypass, 33, GET_CURRENT_BANK_NUMBER(), P42_70_LC_LOCAL_SHPNR_2ND_GAIN_0_3_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_XRAM);
        }
#endif
    }
}
#if((_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON) || (_SDR_PLUS_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Adjust LocalContrast Sharpness Ydiff Gain
// Input Value  : Table address, Table bank, YdiffGainFactor
// Output Value : Ydiffdevisor
//--------------------------------------------------
void ScalerColorLocalContrastYdiffGainAdjust(EnumSelRegion enumSelRegion, BYTE *pucLocalContrastTable, BYTE ucBankNum, BYTE ucYdiffGainFactor, BYTE ucYdiffdevisorAdjust)
{
    BYTE pucYdiffGain[33] = {0};
    BYTE ucYdiffdevisor = 0;
    BYTE ucTemp = 0;
    BYTE ucgainshift = 0;
    WORD usPage = 0;
    BYTE ucIndex = 0;

    // Read Ydiffdevisor from flash
    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[_LOCAL_CONTRAST_YDIFFDEVISOR_START], 1, &ucYdiffdevisor);

    // Read Ydiff gain from flash
    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[_LOCAL_CONTRAST_YDIFF_CURVE_TABLE_START], 16, &pucYdiffGain[0]);
    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[(_LOCAL_CONTRAST_YDIFF_CURVE_TABLE_START + _LOCAL_CONTRAST_YDIFF_CURVE_TABLE_OFFSET)], 16, &pucYdiffGain[16]);
    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[(_LOCAL_CONTRAST_YDIFF_CURVE_TABLE_START + _LOCAL_CONTRAST_YDIFF_CURVE_TABLE_OFFSET * 2)], 1, &pucYdiffGain[32]);

    // Adjust ucgainshift Only in case of (ucYdiffdevisorAdjust > ucYdiffdevisor), else do noting.
    if(ucYdiffdevisorAdjust > ucYdiffdevisor)
    {
        ucgainshift = ucYdiffdevisorAdjust - ucYdiffdevisor;
    }

    for(ucTemp = 0; ucTemp < 33; ucTemp++)
    {
        pucYdiffGain[ucTemp] = ((((WORD)pucYdiffGain[ucTemp] * (WORD)ucYdiffGainFactor) << ucgainshift) / 100);
    }

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart2Mapping(enumCurrRegion);

        // Load Ydiff gain param
        ScalerBurstWrite(pucYdiffGain, 33, GET_CURRENT_BANK_NUMBER(), P42_70_LC_LOCAL_SHPNR_2ND_GAIN_0_3_R1 + usPage, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_XRAM);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 in FB mode, Set Back regs again
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            // Load Ydiff gain param
            ScalerBurstWrite(pucYdiffGain, 33, GET_CURRENT_BANK_NUMBER(), P42_70_LC_LOCAL_SHPNR_2ND_GAIN_0_3_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_XRAM);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Check LocalContrast Sharpness Ydiff devisor need to modify or not
// Input Value  : Table address, Table bank, YdiffGainFactor
// Output Value : Ydiffdevisor
//--------------------------------------------------
BYTE ScalerColorLocalContrastYdiffDevisorAdjust(EnumSelRegion enumSelRegion, BYTE *pucLocalContrastTable, BYTE ucBankNum)
{
    BYTE pucYdiffGain[33] = {0};
    BYTE ucYdiffGain_Max = 0;
    BYTE ucYdiffdevisor = 0;
    BYTE ucTemp = 0;
    BYTE ucgainshift = 1;
    WORD usPage = 0;
    BYTE ucIndex = 0;

    // Read Ydiffdevisor from flash
    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[_LOCAL_CONTRAST_YDIFFDEVISOR_START], 1, &ucYdiffdevisor);

    // Read Ydiff gain from flash
    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[_LOCAL_CONTRAST_YDIFF_CURVE_TABLE_START], 16, &pucYdiffGain[0]);
    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[(_LOCAL_CONTRAST_YDIFF_CURVE_TABLE_START + _LOCAL_CONTRAST_YDIFF_CURVE_TABLE_OFFSET)], 16, &pucYdiffGain[16]);
    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[(_LOCAL_CONTRAST_YDIFF_CURVE_TABLE_START + _LOCAL_CONTRAST_YDIFF_CURVE_TABLE_OFFSET * 2)], 1, &pucYdiffGain[32]);

    for(ucTemp = 0; ucTemp < 33; ucTemp++)
    {
        if(pucYdiffGain[ucTemp] > ucYdiffGain_Max)
        {
            ucYdiffGain_Max = pucYdiffGain[ucTemp];
        }
    }

    if(ucYdiffGain_Max < 128)
    {
        // Check Max Vlue lower than 128, Adust ucYdiffGain_Max to larger than 127
        for(ucgainshift = 1; ucgainshift < 8; ucgainshift++)
        {
            if((ucYdiffGain_Max << ucgainshift) >= 128)
            {
                ucYdiffdevisor += ucgainshift;
                break;
            }
        }
    }

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart2Mapping(enumCurrRegion);

        ScalerSetByte(P42_93_LC_LOCAL_SHPNR_2ND_GAIN_8_0_R1 + usPage, ucYdiffdevisor);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 in FB mode, Set Back regs again
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            ScalerSetByte(P42_93_LC_LOCAL_SHPNR_2ND_GAIN_8_0_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, ucYdiffdevisor);
        }
#endif
    }

    return ucYdiffdevisor;
}
//--------------------------------------------------
// Description  : Adjust LocalContrast Tone-mapping  Gain
// Input Value  : Table address, Table bank, YdiffGainFactor
// Output Value : Tone-Mapping Factor
//--------------------------------------------------
void ScalerColorLocalContrastToneMappingGainAdjust(EnumSelRegion enumSelRegion, BYTE *pucLocalContrastTable, BYTE ucBankNum, BYTE ucTMFactorGain)
{
    BYTE ucOrigin_TMFactor = 0;
    BYTE ucOutput_TMFactor = 0;
    BYTE ucIndex = 0;
    WORD usPage = 0;

    ScalerFlashRead(ucBankNum, &pucLocalContrastTable[_HW_LOCAL_CONTRAST_TM_BLENDINGFACTOR_START], 1, &ucOrigin_TMFactor);

    ucOutput_TMFactor = ((WORD)ucTMFactorGain * (WORD)ucOrigin_TMFactor / 100);

    // Clamp, blending factor max  = 128
    if(ucOutput_TMFactor > 128)
    {
        ucOutput_TMFactor = 128;
    }

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        EnumSelRegion enumCurrRegion = ScalerColorLocalContrastGetRegionStatus(ucIndex, enumSelRegion);

        if(enumCurrRegion == _NON_REGION)
        {
            break;
        }

        usPage = ScalerColorLocalContrastPagePart2Mapping(enumCurrRegion);

        ScalerSetByte(P42_3B_LC_TONEMAPPING_BLENDING_0_R1 + usPage, ucOutput_TMFactor);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // R1 in FB mode, Set Back regs again
        if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
        {
            ScalerSetByte(P42_3B_LC_TONEMAPPING_BLENDING_0_R1 + _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT, ucOutput_TMFactor);
        }
#endif
    }
}
#endif  // End of #if(_ADVANCED_LOCAL_CONTRAST_SUPPORT  == _ON)


#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
//--------------------------------------------------
// Description  : Read LocalContrast block avg Enable
// Input Value  : enumOn
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastReadYavgProcEnable(EnumFunctionOnOFF enumOn)
{
    enumOn = enumOn;

    // initial
    CLR_LOCAL_CONTRAST_READY_TOREAD();

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
    if(enumOn == _FUNCTION_ON)
    {
        ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_LOCAL_CONTRAST, _ENABLE);
    }
    else
    {
        ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_LOCAL_CONTRAST, _DISABLE);
        ScalerColorLocalContrastDisableYavgSWmode();
    }
#endif
}

#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
//----------------------------------------------------------------------------
// Description  : Read LocalContrast block avg and Mapping to specicifc array
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------
void ScalerColorLocalContrastReadYavg(void)
{
    WORD usData0_MSB = 0;
    WORD usData0_LSB = 0;
    WORD usData1_MSB = 0;
    WORD usData1_LSB = 0;
    WORD usPage = 0;
    BYTE ucHblknum = 0;
    BYTE ucVblknum = 0;
    BYTE ucHblknumStart = 0;
    BYTE ucVblknumStart = 0;
    WORD usI = 0;
    WORD usJ = 0;
    WORD pusLocalContrastYavgArray_tmp[(_LOCAL_CONTRAST_READYAVG_HBLKNUM * _LOCAL_CONTRAST_READYAVG_VBLKNUM) + 1] = {0};
    WORD usArrayCount = 0;
    EnumSelRegion enumSelRegion = _NON_REGION;
    BYTE ucExtension_Hblknum = 0;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    BYTE ucHblknumR3Start = 0;
#endif
    StructColorLocalContrastBlknumStartPosition stLocalContrastBlknumStartPosition = {0};

    for(BYTE ucRegionIndex = 0; ucRegionIndex < _LOCAL_CONTRAST_MAX_REGION_COUT; ucRegionIndex++)
    {
        enumSelRegion = (EnumSelRegion)GET_RGN_DISPLAY_REGION(ucRegionIndex);

        // reset data to 0
        memset(pusLocalContrastYavgArray_tmp, 0, sizeof(pusLocalContrastYavgArray_tmp));

        // Not Force to back groud case
        if(ScalerColorLocalContrastGetReadYavgSupport(enumSelRegion) == _TRUE)
        {
            usPage = ScalerColorLocalContrastPagePart1Mapping(enumSelRegion);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // Judge Lcts FB Enable or not, FBPBPLREQUAL should disable FB mode
            if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
            {
                ucExtension_Hblknum = _LOCAL_CONTRAST_FB_EXTENSION_HBLKNUM;
            }
            else
#endif
            {
                // in EO mode, do not need to concern Extension_Hblknum
                ucExtension_Hblknum = 0;
            }

            //-------Front--------//
            ucHblknum = ScalerGetByte(P32_03_LC_GLOBAL_CTRL1_5_R1 + usPage) + 1;
            ucVblknum = ScalerGetByte(P32_04_LC_GLOBAL_CTRL1_4_R1 + usPage) + 1;

            // set addr start from 0
            ScalerSetByte(P32_9A_LC_BLIGHT_AP_1_R1 + usPage, 0x00);
            ScalerSetByte(P32_9B_LC_BLIGHT_AP_0_R1 + usPage, 0x00);

            // FB mode, R1 include 3 Hblknum extension
            usArrayCount = (((ucHblknum + ucExtension_Hblknum) * ucVblknum / 2) + ((((ucHblknum + ucExtension_Hblknum) * ucVblknum % 2) != 0) ? 1 : 0));

            // size of blknum must less than size of pusLocalContrastYavgArray_tmp
            if(((usArrayCount - 1) * 2 + 1) < ((_LOCAL_CONTRAST_READYAVG_HBLKNUM * _LOCAL_CONTRAST_READYAVG_VBLKNUM) + 1))
            {
                for(WORD usL = 0; usL < usArrayCount; usL++)
                {
                    usData1_MSB = ScalerGetByte(P32_9C_LC_BLIGHT_DP_3_R1 + usPage);
                    usData1_LSB = ScalerGetByte(P32_9D_LC_BLIGHT_DP_2_R1 + usPage);
                    usData0_MSB = ScalerGetByte(P32_A0_LC_BLIGHT_DP_1_R1 + usPage);
                    usData0_LSB = ScalerGetByte(P32_A1_LC_BLIGHT_DP_0_R1 + usPage);

                    // sram data origin = 0~1023, use _LOCAL_CONTRAST_YAVG_GAIN to mapping to 0~4095 for LD use
                    pusLocalContrastYavgArray_tmp[usL * 2] = _LOCAL_CONTRAST_YAVG_GAIN * (usData0_MSB * 256 + usData0_LSB);
                    pusLocalContrastYavgArray_tmp[usL * 2 + 1] = _LOCAL_CONTRAST_YAVG_GAIN * (usData1_MSB * 256 + usData1_LSB);
                }
            }

            ScalerColorLocalContrastReadYavgPosMapping(enumSelRegion, &stLocalContrastBlknumStartPosition);
            ucHblknumStart = stLocalContrastBlknumStartPosition.ucHblknumStart;
            ucVblknumStart = stLocalContrastBlknumStartPosition.ucVblknumStart;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            ucHblknumR3Start = stLocalContrastBlknumStartPosition.ucR3HblknumStart;
#endif

            // Mapping Back to g_pusColorLocalContrastYavgArray
            for(usJ = 0; usJ < ucVblknum; usJ++)
            {
                for(usI = 0; usI < (ucHblknum + ucExtension_Hblknum); usI++)
                {
                    // Front 3 extension Hblknum Not include
                    if(usI < ucHblknum)
                    {
                        g_pusColorLocalContrastYavgArray[(usI + ucHblknumStart) + ((usJ + ucVblknumStart) * _LOCAL_CONTRAST_READYAVG_HBLKNUM)] = pusLocalContrastYavgArray_tmp[usI + usJ * (ucHblknum + ucExtension_Hblknum)];
                    }
                }
            }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // Judge Lcts FB Enable or not, FBPBPLREQUAL should disable FB mode
            if(ScalerColorLocalContrastCheckR1FBStatus(usPage) == _TRUE)
            {
                //-------Back--------//
                ucHblknum = ScalerGetByte(PDD_03_LC_GLOBAL_CTRL1_5_R3) + 1;
                ucVblknum = ScalerGetByte(PDD_04_LC_GLOBAL_CTRL1_4_R3) + 1;
                usArrayCount = (((ucHblknum + _LOCAL_CONTRAST_FB_EXTENSION_HBLKNUM) * ucVblknum / 2) + (((ucHblknum * ucVblknum % 2) != 0) ? 1 : 0));

                ScalerSetByte(PDD_9A_LC_BLIGHT_AP_1_R3, 0x00);
                ScalerSetByte(PDD_9B_LC_BLIGHT_AP_0_R3, 0x00);

                // size of blknum must less than size of pusLocalContrastYavgArray_tmp
                if(((usArrayCount - 1) * 2 + 1) < ((_LOCAL_CONTRAST_READYAVG_HBLKNUM * _LOCAL_CONTRAST_READYAVG_VBLKNUM) + 1))
                {
                    for(WORD usL = 0; usL < usArrayCount; usL++)
                    {
                        usData1_MSB = ScalerGetByte(PDD_9C_LC_BLIGHT_DP_3_R3);
                        usData1_LSB = ScalerGetByte(PDD_9D_LC_BLIGHT_DP_2_R3);
                        usData0_MSB = ScalerGetByte(PDD_A0_LC_BLIGHT_DP_1_R3);
                        usData0_LSB = ScalerGetByte(PDD_A1_LC_BLIGHT_DP_0_R3);

                        // sram data origin = 0~1023, use _LOCAL_CONTRAST_YAVG_GAIN to mapping to 0~4095 for LD use
                        pusLocalContrastYavgArray_tmp[usL * 2] = _LOCAL_CONTRAST_YAVG_GAIN * (usData0_MSB * 256 + usData0_LSB);
                        pusLocalContrastYavgArray_tmp[usL * 2 + 1] = _LOCAL_CONTRAST_YAVG_GAIN * (usData1_MSB * 256 + usData1_LSB);
                    }
                }

                // Mapping Back to g_pusColorLocalContrastYavgArray
                for(usJ = 0; usJ < ucVblknum; usJ++)
                {
                    for(usI = 0; usI < (ucHblknum + _LOCAL_CONTRAST_FB_EXTENSION_HBLKNUM); usI++)
                    {
                        // Back 3 extension Hblknum Not include
                        if(usI < ucHblknum)
                        {
                            g_pusColorLocalContrastYavgArray[(usI + ucHblknumR3Start) + ((usJ + ucVblknumStart) * _LOCAL_CONTRAST_READYAVG_HBLKNUM)] = pusLocalContrastYavgArray_tmp[usI + usJ * (ucHblknum + _LOCAL_CONTRAST_FB_EXTENSION_HBLKNUM)];
                        }
                    }
                }
            }
#endif
        }
    }
}

#endif
//--------------------------------------------------
// Description  : LocalContrast block avg Start addrMapping
// Input Value  : enumSelRegion, stLocalContrastBlknumStartPosition
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastReadYavgPosMapping(EnumSelRegion enumSelRegion, StructColorLocalContrastBlknumStartPosition *pstLocalContrastBlknumStartPosition)
{
    BYTE ucHblknum_Start = 0;
    BYTE ucVblknum_Start = 0;
    BYTE ucHblknum_R3Start = 0;

    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
#endif
            ucHblknum_Start = 0;
            ucVblknum_Start = 0;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                ucHblknum_R3Start = ScalerGetByte(P32_03_LC_GLOBAL_CTRL1_5_R1) + 1;
            }
#endif
            break;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_SUB:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_SUB:
#endif
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                WORD usDHstart_R2 = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START) - ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                WORD usDVstart_R2 = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START) - ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
#else
                WORD usDHstart_R2 = 0;
                WORD usDVstart_R2 = 0;
#endif
                BYTE ucHblksize = ScalerGetByte(PC3_06_LC_GLOBAL_CTRL1_2_R2);
                BYTE ucVblksize = ScalerGetByte(PC3_08_LC_GLOBAL_CTRL1_0_R2);

                ucHblknum_Start = (usDHstart_R2 / ucHblksize);
                ucVblknum_Start = (usDVstart_R2 / ucVblksize);
            }
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_R_LARGE_L:
            ucHblknum_Start = 0;
            ucVblknum_Start = 0;
            break;

        case _2P_PBP_LR_L_LARGE_L:
            ucHblknum_Start = 0;
            ucVblknum_Start = 0;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                ucHblknum_R3Start = ScalerGetByte(P32_03_LC_GLOBAL_CTRL1_5_R1) + 1;
            }
#endif
            break;

        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                ucHblknum_Start = (ScalerGetByte(P32_03_LC_GLOBAL_CTRL1_5_R1) + 1) + (ScalerGetByte(PDD_03_LC_GLOBAL_CTRL1_5_R3) + 1);
            }
            else
#endif
            {
                ucHblknum_Start = ScalerGetByte(P32_03_LC_GLOBAL_CTRL1_5_R1) + 1;
            }
            ucVblknum_Start = 0;
            break;

        case _2P_PBP_LR_R_LARGE_R:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                ucHblknum_Start = ScalerGetByte(PC3_03_LC_GLOBAL_CTRL1_5_R2) + 1;
                ucVblknum_Start = 0;
                ucHblknum_R3Start = ucHblknum_Start + ScalerGetByte(P32_03_LC_GLOBAL_CTRL1_5_R1) + 1;
            }
            else
#endif
            {
                if(_HW_SUB_REGION_INPUT_PATH == _INPUT_PATH_S1)
                {
                    ucHblknum_Start = ScalerGetByte(PC3_03_LC_GLOBAL_CTRL1_5_R2) + 1;
                }
                else
                {
                    ucHblknum_Start = ScalerGetByte(P32_03_LC_GLOBAL_CTRL1_5_R1) + 1;
                }
                ucVblknum_Start = 0;
            }
            break;
#endif

        default:
            break;
    }

    pstLocalContrastBlknumStartPosition->ucHblknumStart = ucHblknum_Start;
    pstLocalContrastBlknumStartPosition->ucVblknumStart = ucVblknum_Start;
    pstLocalContrastBlknumStartPosition->ucR3HblknumStart = ucHblknum_R3Start;
}

//----------------------------------------------------------------------------------
// Description  : Check current enumSelRegion REGION support LocalContrast block avg or not
// Input Value  : None
// Output Value : _TRUE, _FALSE
//----------------------------------------------------------------------------------
bit ScalerColorLocalContrastGetReadYavgRegionSupport(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
        case _2P_PIP_SUB:
#endif
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
#endif
            return _TRUE;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_SUB:
            // Blending status
            if(ScalerDDomainGetR2DenEnable() == _ENABLE)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif

        default:
            return _FALSE;
    }
}

//----------------------------------------------------------------------------------
// Description  : Check current enumSelRegion support LocalContrast block avg or not
// Input Value  : None
// Output Value : _TRUE, _FALSE
//----------------------------------------------------------------------------------
bit ScalerColorLocalContrastGetReadYavgSupport(EnumSelRegion enumSelRegion)
{
    if((ScalerDDomainBackgroundCheck(enumSelRegion) == _FALSE) &&
       (ScalerColorLocalContrastGetReadYavgRegionSupport(enumSelRegion) == _TRUE) &&
       (ScalerColorLocalContrastGetEnableStatus(enumSelRegion) == _TRUE))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
//--------------------------------------------------
// Description  : Get HBlknum initial Value
// Input Value  : usPage
// Output Value : ucHblknum
//--------------------------------------------------
BYTE ScalerColorLocalContrastHBlkInitial(WORD usPage)
{
    BYTE ucHblknum = 0;
    usPage = usPage;

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                ucHblknum = _LOCAL_CONTRAST_READYAVG_HBLKNUM / 2;
            }
            else
#endif
            {
                ucHblknum = _LOCAL_CONTRAST_READYAVG_HBLKNUM;
            }
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            if(usPage == _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT)
            {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
                {
                    ucHblknum = _LOCAL_CONTRAST_READYAVG_HBLKNUM / 2;
                }
                else
#endif
                {
                    ucHblknum = _LOCAL_CONTRAST_READYAVG_HBLKNUM;
                }
            }
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
        {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
            WORD usDHWidth_R2 = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_WIDTH);
#endif
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                BYTE ucHblknum_FT = 0;
                BYTE ucHblksize_FT = 0;
                BYTE ucHblknum_BK = 0;
                BYTE ucHblknum_R2 = 0;
                WORD usHWidth_FT = ScalerDDomainGetFBNoneSepR1a1ActiveHwidth();
                WORD usHWidth_BK = ScalerDDomainGetFBNoneSepR3a1ActiveHwidth();

                // R1 + R3 Hblknum
                ucHblknum = (usHWidth_FT + usHWidth_BK) * _LOCAL_CONTRAST_READYAVG_HBLKNUM / ((usHWidth_FT + usHWidth_BK) + usDHWidth_R2);

                // R1 Hblknum
                ucHblknum_FT = usHWidth_FT * ucHblknum / (usHWidth_FT + usHWidth_BK);

                ucHblksize_FT = usHWidth_FT / ucHblknum_FT;

                ucHblknum_BK = usHWidth_BK / ucHblksize_FT;

                ucHblknum_R2 = _LOCAL_CONTRAST_READYAVG_HBLKNUM - ucHblknum_FT - ucHblknum_BK;

                if(usPage == _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT)
                {
                    if(usHWidth_FT > usHWidth_BK)
                    {
                        ucHblknum = ucHblknum_FT;
                    }
                    else
                    {
                        ucHblknum = ucHblknum_BK;
                    }
                }
                else
                {
                    ucHblknum = ucHblknum_R2;
                }
            }
            else
#endif
            {
                WORD usDHWidth_R1 = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH);

                if(usPage == _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT)
                {
                    ucHblknum = usDHWidth_R1 * _LOCAL_CONTRAST_READYAVG_HBLKNUM / (usDHWidth_R1 + usDHWidth_R2);
                }
                else
                {
                    // setting R2 Hblksize = R1 Hblksize
                    ucHblknum = _LOCAL_CONTRAST_READYAVG_HBLKNUM - (usDHWidth_R1 * _LOCAL_CONTRAST_READYAVG_HBLKNUM / (usDHWidth_R1 + usDHWidth_R2));
                }
            }
        }
        break;
#endif

        default:
            break;
    }

    return ucHblknum;
}


//--------------------------------------------------
// Description  : Get VBlknum initial Value
// Input Value  : usPage
// Output Value : ucVblknum
//--------------------------------------------------
BYTE ScalerColorLocalContrastVBlkInitial(WORD usPage)
{
    BYTE ucVblknum = 0;
    usPage = usPage;

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif
            ucVblknum = _LOCAL_CONTRAST_READYAVG_VBLKNUM;
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            if(usPage == _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT)
            {
                ucVblknum = _LOCAL_CONTRAST_READYAVG_VBLKNUM;
            }
            break;
#endif

        default:
            break;
    }

    return ucVblknum;
}

//--------------------------------------------------
// Description  : Check current enumSelRegion need to consider inverse enumSelRegion case
//                PIP sub and ES sub case, Main & Sub blksize need to be the same
// Input Value  : enumSelRegion
// Output Value : _FALSE, _TRUE
//--------------------------------------------------
bit ScalerColorLocalContrastBlksizeAdjustCheck(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_SUB:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_SUB:
#endif
            return _FALSE;
            break;
#endif

        default:
            return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Calculate Hblknum based on specific blksize
//                PIP sub and ES sub need to make sure blksize same as Main
// Input Value  : stLocalContrastHBlkSetting
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastGetHblknumRefSize(StructColorLocalContrastHblkSetting *pstLocalContrastHBlkSetting)
{
    BYTE ucHblksize = 0;
    BYTE ucHblknum = 0;
    WORD usDHWidth_R1 = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH);
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    WORD usDHWidth_R2 = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_WIDTH);
#else
    WORD usDHWidth_R2 = 0;
#endif

    // setting R2 Hblksize = R1 Hblksize
    ucHblksize = usDHWidth_R1 / _LOCAL_CONTRAST_READYAVG_HBLKNUM;
    ucHblknum = usDHWidth_R2 / ucHblksize;

    pstLocalContrastHBlkSetting->ucHblknum = ucHblknum;
    pstLocalContrastHBlkSetting->ucHblksize = ucHblksize;
    pstLocalContrastHBlkSetting->ucBlksize_over = 0;
}

//--------------------------------------------------
// Description  : Calculate Vblknum based on specific blksize
//                PIP sub and ES sub need to make sure blksize same as Main
// Input Value  : stLocalContrastVBlkSetting
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastGetVblknumRefSize(StructColorLocalContrastVblkSetting *pstLocalContrastVBlkSetting)
{
    BYTE ucVblknum = 0;
    WORD usVHeight_R1 = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT);
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
    WORD usVHeight_R2 = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_HEIGHT);
#else
    WORD usVHeight_R2 = 0;
#endif
    BYTE ucVblksize_R1 = usVHeight_R1 / _LOCAL_CONTRAST_READYAVG_VBLKNUM;

    // keep R1 Vblksize  = R2
    ucVblknum = usVHeight_R2 / ucVblksize_R1;

    pstLocalContrastVBlkSetting->ucVblknum = ucVblknum;
    pstLocalContrastVBlkSetting->ucVblksize = ucVblksize_R1;
    pstLocalContrastVBlkSetting->ucLastVblksize = ucVblksize_R1;
}

//--------------------------------------------------
// Description  : Calculate Hblknum based on Specific ucBlkHnumMax
// Input Value  : usDHWidth, ucBlkHnumMax, ucBlkHSizeMin, *stLocalContrastHBlkSetting
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastHBlkAdjust_Yavg(WORD usDHWidth, BYTE ucBlkHnumMax, BYTE ucBlkHSizeMin, StructColorLocalContrastHblkSetting *pstLocalContrastHBlkSetting)
{
    BYTE ucBlksize = ucBlkHSizeMin;
    BYTE ucBlknum = 0;

    ucBlksize = (BYTE)(usDHWidth / (WORD)ucBlkHnumMax);
    ucBlknum = (BYTE)(usDHWidth / (WORD)MAXOF(ucBlksize, 1));

    if(ucBlksize < ucBlkHSizeMin)
    {
        // ucBlksize smaller than ucBlkVSizeMin, return 0
        pstLocalContrastHBlkSetting->ucHblknum = 0;
        pstLocalContrastHBlkSetting->ucHblksize = 0;
        pstLocalContrastHBlkSetting->ucBlksize_over = 0;
    }
    else
    {
        pstLocalContrastHBlkSetting->ucHblknum = ucBlknum;
        pstLocalContrastHBlkSetting->ucHblksize = ucBlksize;
        pstLocalContrastHBlkSetting->ucBlksize_over = 0;
    }
}

//--------------------------------------------------
// Description  : Calculate Vblknum based on Specific ucBlkVnumMax
// Input Value  : usDHWidth, ucBlkHnumMax, ucBlkHSizeMin, *stLocalContrastVBlkSetting
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastVBlkAdjust_Yavg(WORD usDVHeight, BYTE ucBlkVnumMax, BYTE ucBlkVSizeMin, StructColorLocalContrastVblkSetting *pstLocalContrastVBlkSetting)
{
    BYTE ucBlksize = ucBlkVSizeMin;

    ucBlksize = (BYTE)(usDVHeight / (WORD)ucBlkVnumMax);

    if(ucBlksize < ucBlkVSizeMin)
    {
        // ucBlksize smaller than ucBlkVSizeMin, return 0
        pstLocalContrastVBlkSetting->ucVblknum = 0;
        pstLocalContrastVBlkSetting->ucVblksize = 0;
        pstLocalContrastVBlkSetting->ucLastVblksize = 0;
    }
    else
    {
        pstLocalContrastVBlkSetting->ucVblknum = ucBlkVnumMax;
        pstLocalContrastVBlkSetting->ucVblksize = ucBlksize;
        pstLocalContrastVBlkSetting->ucLastVblksize = ucBlksize;
    }
}

//--------------------------------------------------
// Description  : Get Yavg SWmode Enable Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerColorLocalContrastGetYavgSWmodeStatus(void)
{
    // R1/R2 SW mode will enable the same time, here check R1 is enough
    return (ScalerGetBit(P32_99_LC_SRAM_CTRL_0_R1, _BIT1) == _BIT1);
}

//--------------------------------------------------
// Description  : Disable Yavg SWmode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastDisableYavgSWmode(void)
{
    if(ScalerColorLocalContrastGetYavgSWmodeStatus() == _TRUE)
    {
        ScalerSetBit(P32_99_LC_SRAM_CTRL_0_R1, ~_BIT1, 0x00);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // Judge Lcts FB Enable or not, FBPBPLREQUAL should disable FB mode
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
        {
            // Enable R3 SW mode
            ScalerSetBit_EXINT(PDD_99_LC_SRAM_CTRL_0_R3, ~_BIT1, 0x00);
        }
#endif

        // Disable R2 SW mode
        if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
        {
            ScalerSetBit_EXINT(PC3_99_LC_SRAM_CTRL_0_R2, ~_BIT1, 0x00);
        }
    }

    CLR_LOCAL_CONTRAST_READY_TOREAD();
}
//--------------------------------------------------
// Description  : Check Current Displaymode is aspect ratio or not
// Input Value  : None
// Output Value : EnumLocalContrastAspectRatioStatus
//--------------------------------------------------
EnumLocalContrastAspectRatioStatus ScalerColorLocalContrastCheckAspectRatioStatus(void)
{
    BYTE ucMaxRegionCount = GET_RGN_MAX_DISPLAY_REGION();
    if(ucMaxRegionCount <= _LOCAL_CONTRAST_MAX_REGION_COUT)
    {
        for(BYTE ucRegionIndex = 0; ucRegionIndex < ucMaxRegionCount; ucRegionIndex++)
        {
            EnumDisplayRegion enumDisplayRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);

            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_1P:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_PIP_MAIN:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
#endif
#endif
                    {
                        WORD usActiveHWidth = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH);
                        WORD usActiveVHeight = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT);
                        WORD usBackgroundHwidth = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH);
                        WORD usBackgroundVHeight = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT);

                        // Check if Active HWidth/VHeight == Background HWidth/VHeight
                        if((usActiveHWidth != usBackgroundHwidth) || (usActiveVHeight != usBackgroundVHeight))
                        {
                            return _LOCALCONTRAST_ASPECT_RATIO_ON;
                        }
                    }
                    break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_PIP_SUB:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_RGN_EAGLE_SIGHT_SUB:
#endif
                    {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                        WORD usActiveHWidth = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_WIDTH);
                        WORD usActiveVHeight = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_HEIGHT);
#endif
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
                        WORD usBackgroundHwidth = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_WIDTH);
                        WORD usBackgroundVHeight = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_HEIGHT);
#endif
                        // Check if Active HWidth/VHeight == Background HWidth/VHeight
                        if((usActiveHWidth != usBackgroundHwidth) || (usActiveVHeight != usBackgroundVHeight))
                        {
                            return _LOCALCONTRAST_ASPECT_RATIO_ON;
                        }
                    }
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_RGN_PBP_LR_EQUAL_LEFT:
                case _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT:
                case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
                case _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT:
                case _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT:
                {
                    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(GET_RGN_DISPLAY_REGION(ucRegionIndex));
                    WORD usActiveHstart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    WORD usActiveVstart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    WORD usBackgroundHstart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START);
                    WORD usBackgroundVstart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);

                    if(enumDDomainRegion == _DDOMAIN_RGN_R2_A1)
                    {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                        usActiveHstart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                        usActiveVstart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
#endif
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
                        usBackgroundHstart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_START);
                        usBackgroundVstart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_START);
#endif
                    }

                    // Check if Active Hstart/Vstart == Background Hstart/Vstart
                    if((usActiveHstart != usBackgroundHstart) || (usActiveVstart != usBackgroundVstart))
                    {
                        return _LOCALCONTRAST_ASPECT_RATIO_ON;
                    }
                }
                break;

                case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)    // 6829 FB mode R > L -> R1
                    {
                        WORD usActiveHend = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                        WORD usActiveVstart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                        WORD usBackgroundHend = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END);
                        WORD usBackgroundVstart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);

                        // Check if Active Hend/Vsend == Background Hend/Vend
                        if((usActiveHend != usBackgroundHend) || (usActiveVstart != usBackgroundVstart))
                        {
                            return _LOCALCONTRAST_ASPECT_RATIO_ON;
                        }
                    }
#endif

                    if(_HW_SUB_REGION_INPUT_PATH == _INPUT_PATH_S1)    // 6952 R > L -> R1
                    {
                        WORD usActiveHend = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                        WORD usActiveVstart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                        WORD usBackgroundHend = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END);
                        WORD usBackgroundVstart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);

                        // Check if Active Hend/Vsend == Background Hend/Vend
                        if((usActiveHend != usBackgroundHend) || (usActiveVstart != usBackgroundVstart))
                        {
                            return _LOCALCONTRAST_ASPECT_RATIO_ON;
                        }
                    }
                    else if(_HW_SUB_REGION_INPUT_PATH == _INPUT_PATH_S1_S2)    // 6829 EO R > L -> R2
                    {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                        WORD usActiveHstart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                        WORD usActiveVstart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
#endif
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
                        WORD usBackgroundHstart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_START);
                        WORD usBackgroundVstart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_START);
#endif

                        // Check if Active Hstart/Vsend == Background Hstart/Vend
                        if((usActiveHstart != usBackgroundHstart) || (usActiveVstart != usBackgroundVstart))
                        {
                            return _LOCALCONTRAST_ASPECT_RATIO_ON;
                        }
                    }
                    break;

#endif
                default:
                    break;
            }
        }
        return _LOCALCONTRAST_ASPECT_RATIO_OFF;
    }

    return _LOCALCONTRAST_ASPECT_RATIO_NONE;
}
#endif  // End of #if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
#endif  // End of #if(_COLOR_IP_LOCAL_CONTRAST == _ON)

