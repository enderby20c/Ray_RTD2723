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
// ID Code      : ScalerColorUltraVivid.c
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
#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
//--------------------------------------------------
// Description  : Initial Ultravivid Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorUltraVividInitial(void)
{
#if(_COLOR_IP_DSHP == _ON)
    // always Enable DSHP for eDP panel
    ScalerSetBit(P12_00_SR_SHP_CTRL_0_R1_A1, ~(_BIT7 | _BIT3), _BIT7);
    ScalerSetBit(P13_00_SR_SHP_CTRL_0_R1_A2, ~(_BIT7 | _BIT3), _BIT7);
    ScalerSetBit(P52_00_SR_SHP_CTRL_0_R2_A1, ~(_BIT7 | _BIT3), _BIT7);
    ScalerSetBit(P53_00_SR_SHP_CTRL_0_R2_A2, ~(_BIT7 | _BIT3), _BIT7);
    ScalerSetBit(P5B_00_SR_SHP_CTRL_0_R3_A1, ~(_BIT7 | _BIT3), _BIT7);
    ScalerSetBit(P5C_00_SR_SHP_CTRL_0_R3_A2, ~(_BIT7 | _BIT3), _BIT7);
#endif
}

//--------------------------------------------------
// Description  : Write UltraVivid Table
// Input Value  : EnumDDomainRegion, UltraVivid Table, Table Size, Bank Number
// Output Value : None
//--------------------------------------------------
void ScalerColorUltraVividLoadTable(EnumDDomainRegion enumDDomainRegion, BYTE *pucUltraVividSetting, WORD usUltraVividSize, BYTE ucBankNum)
{
    WORD usIndex = 0;
    BYTE ucTempLength = 0;
    BYTE ucTempAddr = 0;
    BYTE ucTempData = 0;
    BYTE ucTempPage = 0;
    BYTE ucReadWriteType = 0;
#if(_COLOR_IP_LSR == _ON)
    WORD usLSRPage = ScalerColorLSRPageMapping(enumDDomainRegion);
#endif
#if(_COLOR_IP_DSHP == _ON)
    WORD usDSHPPage = ScalerColorDSHPPageMapping(enumDDomainRegion);
#endif

    for(usIndex = 0; usIndex < usUltraVividSize; usIndex += ucTempLength)
    {
        ScalerFlashRead(ucBankNum, &pucUltraVividSetting[usIndex], 1, &ucTempLength);

        if(ucTempLength == 0)
        {
            return;
        }
        else if(ucTempLength == 4)
        {
            ScalerFlashRead(ucBankNum, &pucUltraVividSetting[usIndex + 2], 1, &ucTempAddr);
            ScalerFlashRead(ucBankNum, &pucUltraVividSetting[usIndex + 3], 1, &ucTempData);

            if(ucTempAddr == 0x9F)
            {
                ucTempPage = ucTempData;
            }
            else
            {
                switch(ucTempPage)
                {
#if(_COLOR_IP_LSR == _ON)
                    case 0x11:  // LSR
                        ScalerSetByte((usLSRPage + ((WORD)ucTempPage << 8) + (WORD)ucTempAddr), ucTempData);
                        break;
#endif
#if(_COLOR_IP_DSHP == _ON)
                    case 0x12:  // DSHP
                        ScalerSetByte((usDSHPPage + ((WORD)ucTempPage << 8) + (WORD)ucTempAddr), ucTempData);
                        break;
#endif
                    default:
                        break;
                }
            }
        }
        else
        {
            ScalerFlashRead(ucBankNum, &pucUltraVividSetting[usIndex + 1], 1, &ucReadWriteType);
            ScalerFlashRead(ucBankNum, &pucUltraVividSetting[usIndex + 2], 1, &ucTempAddr);

#if(_COLOR_IP_LSR == _ON)
            if((ucTempPage == 0x11) && (ucReadWriteType == _AUTOINC))  // Only LSR
            {
                switch(ucTempAddr)
                {
                    case 0x00:
                    case 0x06:
                    case 0x11:
                    case 0x2B:
                        ScalerBurstWrite(&pucUltraVividSetting[usIndex + 3], ucTempLength - 3, ucBankNum, (usLSRPage + ((WORD)ucTempData << 8) + (WORD)ucTempAddr), _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);
                        break;

                    default:
                        break;
                }
            }
#endif
#if(_COLOR_IP_DSHP == _ON)
            else if((ucTempPage == 0x12) && (ucReadWriteType == _AUTOINC))  // Only DSHP
            {
                switch(ucTempAddr)
                {
                    case 0x00:
                    case 0x3E:
                    case 0xD4:
                    case 0xA0:  // DSHP-CDS
                    case 0xB2:  // DSHP-CDS
                        ScalerBurstWrite(&pucUltraVividSetting[usIndex + 3], ucTempLength - 3, ucBankNum, (usDSHPPage + ((WORD)ucTempData << 8) + (WORD)ucTempAddr), _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);
                        break;

                    default:
                        break;
                }
            }
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Get SD Setting Page
// Input Value  : EnumSelRegion, EnumColorRegSel
// Output Value : Setting Page
//--------------------------------------------------
WORD ScalerColorUltraVividSDGetPage(EnumSelRegion enumSelRegion, EnumDDomainRegion enumDDomainRegion)
{
    enumSelRegion = enumSelRegion;

    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                default:
                    return _REG_MAIN1_PAGE;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    return _REG_MAIN1_PAGE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    return _REG_MAIN1_PAGE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    return _REG_MAIN1_PAGE;

                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    return _REG_SUB1_PAGE;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    return _REG_MAIN1_PAGE;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    return _REG_SUB3_PAGE;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_L:
                    return _REG_MAIN1_PAGE;

                case _DISPLAY_MODE_3P_SKEW_R:
                    return _REG_SUB1_PAGE;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                    return _REG_MAIN1_PAGE;

                case _DISPLAY_MODE_3P_SKEW_B:
                    return _REG_SUB1_PAGE;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    return _REG_MAIN1_PAGE;
#endif
            }

        case _DDOMAIN_RGN_R1_A2:
            switch(GET_DISPLAY_MODE())
            {
                default:
                    return _REG_MAIN1_PAGE;

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    return _REG_SUB1_PAGE;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_R:
                    return _REG_SUB3_PAGE;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                    return _REG_SUB1_PAGE;

                case _DISPLAY_MODE_3P_SKEW_B:
                    return _REG_MAIN1_PAGE;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    return _REG_MAIN2_PAGE;
#endif
            }

        case _DDOMAIN_RGN_R2_A1:
            switch(GET_DISPLAY_MODE())
            {
                default:
                    return _REG_MAIN1_PAGE;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    return _REG_SUB1_PAGE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    return _REG_SUB1_PAGE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    return _REG_SUB1_PAGE;

                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    return _REG_MAIN1_PAGE;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    return _REG_MAIN1_PAGE;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_L:
                    return _REG_SUB1_PAGE;

                case _DISPLAY_MODE_3P_SKEW_R:
                    return _REG_MAIN1_PAGE;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                case _DISPLAY_MODE_3P_SKEW_B:
                    return _REG_SUB3_PAGE;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    return _REG_SUB1_PAGE;
#endif
            }

        case _DDOMAIN_RGN_R2_A2:
            switch(GET_DISPLAY_MODE())
            {
                default:
                    return _REG_MAIN1_PAGE;

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_L:
                    return _REG_SUB3_PAGE;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    return _REG_SUB2_PAGE;
#endif
            }

        case _DDOMAIN_RGN_R3_A1:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                default:
                    return _REG_MAIN1_PAGE;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    return _REG_MAIN1_PAGE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    return _REG_MAIN1_PAGE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    return _REG_MAIN1_PAGE;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    return _REG_MAIN1_PAGE;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    return _REG_SUB1_PAGE;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                    return _REG_MAIN1_PAGE;
#endif
            }

        case _DDOMAIN_RGN_R3_A2:
            switch(GET_DISPLAY_MODE())
            {
                default:
                    return _REG_MAIN1_PAGE;

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    return _REG_SUB1_PAGE;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_B:
                    return _REG_MAIN1_PAGE;
#endif
            }

        default:
            return _REG_MAIN1_PAGE;
    }
}

//--------------------------------------------------
// Description  : UltraVivid Display Path mapping register Page
// Input Value  : enumDDomainRegion
// Output Value : usPage
//--------------------------------------------------
WORD ScalerColorUltraVividPageMapping(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            return 0x0000U;

        case _DDOMAIN_RGN_R1_A2:
            return 0x0006U;

        case _DDOMAIN_RGN_R2_A1:
            return 0x8000U;

        case _DDOMAIN_RGN_R2_A2:
            return 0x8006U;

        case _DDOMAIN_RGN_R3_A1:
            return 0xC000U;

        case _DDOMAIN_RGN_R3_A2:
            return 0xC006U;
    }
}

//--------------------------------------------------
// Description  : Get IDomain Page Register From enumDDomainRegion
// Input Value  : enumDDomainRegion
// Output Value : usPage
//--------------------------------------------------
WORD ScalerColorUltraVividGetIDomainRegisterPage(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            return _REG_MAIN1_PAGE;

        case _DDOMAIN_RGN_R1_A2:
            return _REG_MAIN2_PAGE;

        case _DDOMAIN_RGN_R2_A1:
            return _REG_SUB1_PAGE;

        case _DDOMAIN_RGN_R2_A2:
            return _REG_SUB2_PAGE;

        case _DDOMAIN_RGN_R3_A1:
            return _REG_SUB3_PAGE;

        case _DDOMAIN_RGN_R3_A2:
            return _REG_SUB4_PAGE;
    }
}

//--------------------------------------------------
// Description  : Get SU Setting Page
// Input Value  : EnumSelRegion, EnumColorRegSel
// Output Value : Setting Page
//--------------------------------------------------
WORD ScalerColorUltraVividSUGetPage(EnumSelRegion enumSelRegion, EnumDDomainRegion enumDDomainRegion)
{
    enumSelRegion = enumSelRegion;

    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            return ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A1);

        case _DDOMAIN_RGN_R1_A2:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A1);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A1);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A1);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A1);
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A1);
#endif
                default:
                    return ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R1_A2);
            }

        case _DDOMAIN_RGN_R2_A1:
            return ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A1);

        case _DDOMAIN_RGN_R2_A2:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A1);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A1);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A1);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A1);
#endif
                default:
                    return ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R2_A2);
            }

        case _DDOMAIN_RGN_R3_A1:
            return ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A1);

        case _DDOMAIN_RGN_R3_A2:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A1);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A1);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A1);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A1);
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    return (enumSelRegion == _DEMO_INSIDE) ? ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A2) : ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A1);
#endif
                default:
                    return ScalerColorUltraVividPageMapping(_DDOMAIN_RGN_R3_A2);
            }
    }
}

//--------------------------------------------------
// Description  : UltraVivid Adjust
// Input Value  : UltraVivid Table and ucBankNum
// Output Value : None
//--------------------------------------------------
void ScalerColorUltraVividAdjust(EnumSelRegion enumSelRegion, BYTE *pucUltraVividSetting, BYTE ucBankNum)
{
    BYTE *pucTable = 0x00;
    WORD usSDPage = 0x0000;
    WORD usSUPage = 0x0000;
    BYTE ucDDomainRegion = 0;
    BYTE ucPage = ScalerColorUltraVividGetDDomainRegion(enumSelRegion);

    for(ucDDomainRegion = 0; ucDDomainRegion < 6; ucDDomainRegion++)
    {
        usSDPage = ScalerColorUltraVividSDGetPage(enumSelRegion, (_DDOMAIN_RGN_R1_A1 << (BYTE)ucDDomainRegion));
        usSUPage = ScalerColorUltraVividSUGetPage(enumSelRegion, (_DDOMAIN_RGN_R1_A1 << (BYTE)ucDDomainRegion));

        if((ucPage & (_DDOMAIN_RGN_R1_A1 << (BYTE)ucDDomainRegion)) != 0x00)
        {
            // Get V Scaling Down
            if(ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1 + usSDPage, _BIT0) == _BIT0)
            {
                pucTable = pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 3;
            }
            // Get V Scaling Up
            else if(ScalerGetBit(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1 + usSUPage, _BIT1) == _BIT1)
            {
                ScalerGetDataPortByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1 + usSUPage, _P0_34_PT_03_VER_SCALE_FACTOR_H_R1_ACTIVE1, 2, pData, _AUTOINC);
                pData[0] = ((pData[0] << 4) | (pData[1] >> 4));

                if(pData[0] < 85)  // IVHeight/DVHeight <= 1/3
                {
                    pucTable = pucUltraVividSetting;
                }
                else if(pData[0] < 170)  // IVHeight/DVHeight < 2/3
                {
                    pucTable = pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 1;
                }
                else  // IVHeight/DVHeight <= 1
                {
                    pucTable = pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 2;
                }
            }
            // bypass
            else
            {
                pucTable = pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 4;
            }

            ScalerColorUltraVividLoadTable((EnumDDomainRegion)(_DDOMAIN_RGN_R1_A1 << ucDDomainRegion), pucTable, _ULTRAVIVID_TABLE_SIZE, ucBankNum);

            // CDS
            pucTable = pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 5;
            ScalerColorUltraVividLoadTable((EnumDDomainRegion)(_DDOMAIN_RGN_R1_A1 << ucDDomainRegion), pucTable, _ULTRAVIVID_TABLE_SIZE_CDS, ucBankNum);
        }
    }
}

//--------------------------------------------------
// Description  : Set UltraVivid HLW Region Enable and Set Select
// Input Value  : enumSelRegion, enumDBApply, and bOn
// Output Value : ON/OFF
//--------------------------------------------------
void ScalerColorUltraVividRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    EnumInputDataPath enumInputDataPath = _INPUT_PATH_NONE;

#if(_COLOR_IP_LSR == _ON)
    ScalerColorLSRRegionEnable(enumSelRegion, bOn);
#endif

#if(_COLOR_IP_DSHP == _ON)
    ScalerColorDSHPRegionEnable(enumSelRegion, bOn);
#endif

    // Not 1P Mode or 1P interlace Mode
    if((GET_DISPLAY_MODE() != _DISPLAY_MODE_1P) || (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE))
    {
        if(enumDBApply == _DB_APPLY_POLLING)
        {
            enumDBApply = _DB_APPLY_NO_POLLING;
        }
    }

    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_M1_M2_S1_S2;
            }
            else
            {
                enumInputDataPath = _INPUT_PATH_M1_M2;
            }
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_M1_M2_S1_S2;
            }
            else
            {
                enumInputDataPath = _INPUT_PATH_M1_M2;
            }
            break;

        case _2P_PIP_SUB:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_S3_S4;
            }
            else
            {
#if(_COLOR_IP_3DDI == _ON)
                if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                {
                    enumInputDataPath = _INPUT_PATH_S2;
                }
                else
#endif
                {
                    enumInputDataPath = _INPUT_PATH_S1_S2;
                }
            }
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_M1_M2_S1_S2;
            }
            else
            {
                enumInputDataPath = _INPUT_PATH_M1_M2;
            }
            break;

        case _2P_PIP_EAGLE_SIGHT_SUB:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_S3_S4;
            }
            else
            {
#if(_COLOR_IP_3DDI == _ON)
                if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                {
                    enumInputDataPath = _INPUT_PATH_S2;
                }
                else
#endif
                {
                    enumInputDataPath = _INPUT_PATH_S1_S2;
                }
            }
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _2P_PBP_LR_L_LARGE_L:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_M1_M2_S1_S2;
            }
            else
            {
                enumInputDataPath = _INPUT_PATH_M1_M2;
            }
            break;

        case _2P_PBP_LR_R_LARGE_L:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_S3_S4;
            }
            else
            {
                enumInputDataPath = _INPUT_PATH_M1_M2;
            }
            break;

        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_S3_S4;
            }
            else
            {
#if(_COLOR_IP_3DDI == _ON)
                if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                {
                    enumInputDataPath = _INPUT_PATH_S2;
                }
                else
#endif
                {
                    enumInputDataPath = _INPUT_PATH_S1_S2;
                }
            }
            break;

        case _2P_PBP_LR_R_LARGE_R:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                enumInputDataPath = _INPUT_PATH_M1_M2_S1_S2;
            }
            else
            {
#if(_COLOR_IP_3DDI == _ON)
                if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                {
                    enumInputDataPath = _INPUT_PATH_S2;
                }
                else
#endif
                {
                    enumInputDataPath = _INPUT_PATH_S1_S2;
                }
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _2P_PBP_TB_B:
#if(_COLOR_IP_3DDI == _ON)
            if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
            {
                enumInputDataPath = _INPUT_PATH_S2;
            }
            else
#endif
            {
                enumInputDataPath = _INPUT_PATH_S1_S2;
            }
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _3P_FLAG_L:
            enumInputDataPath = _INPUT_PATH_S3_S4;
            break;

        case _3P_FLAG_R:
            enumInputDataPath = _INPUT_PATH_S1_S2;
            break;

        case _3P_FLAG_M_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_S1_S2 | _INPUT_PATH_S3_S4);
            break;

        case _3P_FLAG_L_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2);
            break;

        case _3P_FLAG_R_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S3_S4);
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_T:
        case _3P_SKEW_R_T:
            enumInputDataPath = _INPUT_PATH_S1_S2;
            break;

        case _3P_SKEW_L_M:
        case _3P_SKEW_R_M:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _3P_SKEW_L_B:
        case _3P_SKEW_R_B:
            enumInputDataPath = _INPUT_PATH_S3_S4;
            break;

        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_R_M_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_S1_S2 | _INPUT_PATH_S3_S4);
            break;

        case _3P_SKEW_L_T_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S3_S4);
            break;

        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2);
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_L:
        case _3P_SKEW_B_L:
            enumInputDataPath = _INPUT_PATH_S1_S2;
            break;

        case _3P_SKEW_T_R:
        case _3P_SKEW_B_R:
            enumInputDataPath = _INPUT_PATH_S3_S4;
            break;

        case _3P_SKEW_T_M:
        case _3P_SKEW_B_M:
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S3_S4);
            break;

        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2);
            break;

        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_B_M_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_S1_S2 | _INPUT_PATH_S3_S4);
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LB:
            enumInputDataPath = _INPUT_PATH_M2;
            break;

        case _4P_RB:
            enumInputDataPath = _INPUT_PATH_S2;
            break;

        case _4P_RT:
            enumInputDataPath = _INPUT_PATH_S1;
            break;

        case _4P_LT:
            enumInputDataPath = _INPUT_PATH_M1;
            break;

        case _4P_LT_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M2 | _INPUT_PATH_S1 | _INPUT_PATH_S2);
            break;

        case _4P_LB_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1 | _INPUT_PATH_S1 | _INPUT_PATH_S2);
            break;

        case _4P_RT_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1 | _INPUT_PATH_M2 | _INPUT_PATH_S2);
            break;

        case _4P_RB_OUTSIDE:
            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1 | _INPUT_PATH_M2 | _INPUT_PATH_S1);
            break;
#endif

        case _FULL_REGION:
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        enumInputDataPath = _INPUT_PATH_M1_M2_S1_S2;
                    }
                    else
                    {
                        enumInputDataPath = _INPUT_PATH_M1_M2;
                    }
                    break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        enumInputDataPath = _INPUT_PATH_ALL;
                    }
                    else
                    {
#if(_COLOR_IP_3DDI == _ON)
                        if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                        {
                            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S2);
                        }
                        else
#endif
                        {
                            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2);
                        }
                    }
                    break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        enumInputDataPath = _INPUT_PATH_ALL;
                    }
                    else
                    {
#if(_COLOR_IP_3DDI == _ON)
                        if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                        {
                            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S2);
                        }
                        else
#endif
                        {
                            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2);
                        }
                    }
                    break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S3_S4);
                    }
                    else
                    {
#if(_COLOR_IP_3DDI == _ON)
                        if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                        {
                            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S2);
                        }
                        else
#endif
                        {
                            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2);
                        }
                    }
                    break;

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        enumInputDataPath = _INPUT_PATH_ALL;
                    }
                    else
                    {
#if(_COLOR_IP_3DDI == _ON)
                        if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                        {
                            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S2);
                        }
                        else
#endif
                        {
                            enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2);
                        }
                    }
                    break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
#if(_COLOR_IP_3DDI == _ON)
                    if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
                    {
                        enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S2);
                    }
                    else
#endif
                    {
                        enumInputDataPath = (EnumInputDataPath)(_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2);
                    }
                    break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    enumInputDataPath = _INPUT_PATH_ALL;
                    break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_L:
                case _DISPLAY_MODE_3P_SKEW_R:
                    enumInputDataPath = _INPUT_PATH_ALL;
                    break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                case _DISPLAY_MODE_3P_SKEW_B:
                    enumInputDataPath = _INPUT_PATH_ALL;
                    break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    enumInputDataPath = _INPUT_PATH_M1_M2_S1_S2;
                    break;
#endif
                default:
                    break;
            }
            break;

        default:
            break;
    }

    if(enumInputDataPath != _INPUT_PATH_NONE)
    {
        ScalerGlobalIDDomainDBApply(enumInputDataPath, enumDBApply);
    }
}

//--------------------------------------------------
// Description  : Get UltraVivid D Domain Region
// Input Value  : EnumSelRegion
// Output Value : D Domain Region
//--------------------------------------------------
BYTE ScalerColorUltraVividGetDDomainRegion(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A1;
            }

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A1;
            }

        case _2P_PIP_SUB:
            return _DDOMAIN_RGN_R2_A1;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A1;
            }

        case _2P_PIP_EAGLE_SIGHT_SUB:
            return _DDOMAIN_RGN_R2_A1;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A1;
            }

        case _2P_PBP_TB_B:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R3_A2);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A2;
            }
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
            return _DDOMAIN_RGN_R1_A1;

        case _2P_PBP_LR_L_LARGE_L:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A1;
            }

        case _2P_PBP_LR_R_LARGE_L:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_EQUAL_R:
            return _DDOMAIN_RGN_R2_A1;

        case _2P_PBP_LR_R_LARGE_R:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A1;
            }
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_L:
            return _DDOMAIN_RGN_R1_A1;

        case _3P_FLAG_R:
            return _DDOMAIN_RGN_R3_A1;

        case _3P_FLAG_M:
            return _DDOMAIN_RGN_R2_A1;

        case _3P_FLAG_L_OUTSIDE:
            return (_DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1);

        case _3P_FLAG_R_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);

        case _3P_FLAG_M_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
        case _3P_SKEW_R_T:
            return _DDOMAIN_RGN_R1_A1;

        case _3P_SKEW_L_T:
        case _3P_SKEW_R_M:
            return _DDOMAIN_RGN_R2_A1;

        case _3P_SKEW_L_B:
            return _DDOMAIN_RGN_R2_A2;

        case _3P_SKEW_R_B:
            return _DDOMAIN_RGN_R1_A2;

        case _3P_SKEW_L_M_OUTSIDE:
            return (_DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R2_A2);

        case _3P_SKEW_R_T_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1);

        case _3P_SKEW_L_T_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A2);

        case _3P_SKEW_R_M_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2);

        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A1;
            }

        case _3P_SKEW_T_L:
            return _DDOMAIN_RGN_R1_A2;

        case _3P_SKEW_T_R:
        case _3P_SKEW_B_R:
            return _DDOMAIN_RGN_R2_A1;

        case _3P_SKEW_B_L:
            return _DDOMAIN_RGN_R1_A1;

        case _3P_SKEW_B_M:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R3_A2);
            }
            else
            {
                return _DDOMAIN_RGN_R1_A2;
            }

        case _3P_SKEW_T_M_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1);

        case _3P_SKEW_T_L_OUTSIDE:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1 | _DDOMAIN_RGN_R2_A1);
            }
            else
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);
            }

        case _3P_SKEW_T_R_OUTSIDE:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1 | _DDOMAIN_RGN_R1_A2);
            }
            else
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2);
            }

        case _3P_SKEW_B_L_OUTSIDE:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R3_A2 | _DDOMAIN_RGN_R2_A1);
            }
            else
            {
                return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1);
            }

        case _3P_SKEW_B_M_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);

        case _3P_SKEW_B_R_OUTSIDE:
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R3_A2);
            }
            else
            {
                return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2);
            }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
            return _DDOMAIN_RGN_R1_A1;

        case _4P_LB:
            return _DDOMAIN_RGN_R1_A2;

        case _4P_RT:
            return _DDOMAIN_RGN_R2_A1;

        case _4P_RB:
            return _DDOMAIN_RGN_R2_A2;

        case _4P_LT_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R2_A2);

        case _4P_LB_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R2_A2);

        case _4P_RT_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A2);

        case _4P_RB_OUTSIDE:
            return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1);
#endif

        case _FULL_REGION:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return _DDOMAIN_RGN_R1_A1;
                    }

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);
                    }
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);
                    }
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1 | _DDOMAIN_RGN_R2_A1);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);
                    }
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R3_A1 | _DDOMAIN_RGN_R3_A2);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2);
                    }
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1);
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_L:
                    return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R2_A2);

                case _DISPLAY_MODE_3P_SKEW_R:
                    return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1);
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_T:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1);
                    }

                case _DISPLAY_MODE_3P_SKEW_B:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A2);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1);
                    }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R2_A2);
#endif
                default:
                    break;
            }
            break;

        case _DEMO_INSIDE:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R3_A2);
                    }
                    else
                    {
                        return _DDOMAIN_RGN_R1_A2;
                    }
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A2 | _DDOMAIN_RGN_R3_A2);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A2);
                    }
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A2 | _DDOMAIN_RGN_R3_A2);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A2);
                    }
#endif


#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A2);

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A2 | _DDOMAIN_RGN_R3_A2);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A2);
                    }
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R3_A2);
                    }
                    else
                    {
                        return _DDOMAIN_RGN_R1_A2;
                    }
#endif

                default:
                    return _DDOMAIN_RGN_R1_A1;
            }
            break;

        case _DEMO_OUTSIDE:
            switch(GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return _DDOMAIN_RGN_R1_A1;
                    }

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);
                    }
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);
                    }
#endif


#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);

                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1);
                    }
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                    {
                        return (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R3_A1);
                    }
                    else
                    {
                        return _DDOMAIN_RGN_R1_A1;
                    }
#endif

                default:
                    return _DDOMAIN_RGN_R1_A1;
            }
            break;

        default:
            return _DDOMAIN_RGN_R1_A1;
    }
    return _DDOMAIN_RGN_R1_A1;
}
#endif // End of #if(_COLOR_IP_LSR == _ON)
