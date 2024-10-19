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
// ID Code      : ScalerColorContrast.c
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
#if(_COLOR_IP_CONTRAST == _ON)
//--------------------------------------------------
// Description  : Adjust Contrast
// Input Value  : enumSelRegion, Coefficient
//                12 bit input, old 8 bit contrast input value must left shift 4 bit
//                0 (00h) ~ 1(800h) ~  2(FFFh)
// Output Value : void
//--------------------------------------------------
void ScalerColorContrastAdjust(EnumSelRegion enumSelRegion, WORD *pusData)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#else
    if(enumSelRegion == _DEMO_INSIDE)
    {
        usPage = _REG_MAIN2_PAGE;
    }
#endif

    switch(usPage)
    {
        case _REG_MAIN1_PAGE:
            ScalerColorContrastCoefAdjust(_CONTRAST_COEF_A, pusData);

            if(enumSelRegion == _FULL_REGION)
            {
                ScalerColorContrastCoefAdjust(_CONTRAST_COEF_B, pusData);
            }

            break;

        case _REG_MAIN2_PAGE:
            ScalerColorContrastCoefAdjust(_CONTRAST_COEF_B, pusData);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Contrast
// Input Value  : enumSelRegion, Coefficient
//                12 bit input, old 8 bit contrast input value must left shift 4 bit
//                0 (00h) ~ 1(800h) ~  2(FFFh)
// Output Value : void
//--------------------------------------------------
void ScalerColorContrastCoefAdjust(EnumCtsCoefType enumCtsCoefType, WORD *pusData)
{
    switch(enumCtsCoefType)
    {
        case _CONTRAST_COEF_A:
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_03_CTS_RED_COE_SETA_H, (pusData[0] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_04_CTS_GRN_COE_SETA_H, (pusData[1] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_05_CTS_BLU_COE_SETA_H, (pusData[2] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_21_CTS_COE_SETA_RG_L, ((pusData[0] & 0x000F) << 4) | ((pusData[1] & 0x000F)));
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_22_CTS_COE_SETA_B_L, (pusData[2] & 0x000F) << 4);
            break;

        case _CONTRAST_COEF_B:
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_09_CTS_RED_COE_SETB_H, (pusData[0] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_0A_CTS_GRN_COE_SETB_H, (pusData[1] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_0B_CTS_BLU_COE_SETB_H, (pusData[2] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_24_CTS_COE_SETB_RG_L, ((pusData[0] & 0x000F) << 4) | ((pusData[1] & 0x000F)));
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_25_CTS_COE_SETB_B_L, (pusData[2] & 0x000F) << 4);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Contrast function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorContrastEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
#if(_HW_CTS_ENABLE_BIT_ADDR_TYPE == _CTS_EN_ADDR_P0_62)
        ScalerSetBit(P0_62_SRGB_CTRL, ~(_BIT6 | _BIT1), _BIT1);
#else
        ScalerSetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, ~_BIT1, _BIT1);
#endif
    }
    else
    {
#if(_HW_CTS_ENABLE_BIT_ADDR_TYPE == _CTS_EN_ADDR_P0_62)
        ScalerSetBit(P0_62_SRGB_CTRL, ~(_BIT6 | _BIT1), 0x00);
#else
        ScalerSetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, ~_BIT1, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Get Contrast Setting
// Input Value  : EnumBriConCoefType, Coefficient
// Output Value : Contrast Setting
//--------------------------------------------------
void ScalerColorContrastGetSetting(EnumCtsCoefType enumCtsCoefType, WORD *pusData)
{
    BYTE ucTempH = 0;
#if(_HW_CTS_TYPE == _CTS_GEN_1_12BIT)
    BYTE ucTempL = 0;
#endif

    switch(enumCtsCoefType)
    {
        case _CONTRAST_COEF_A:
            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_03_CTS_RED_COE_SETA_H);
#if(_HW_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[0] = ucTempH;
#elif(_HW_CTS_TYPE == _CTS_GEN_1_12BIT)
            ucTempL = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_21_CTS_COE_SETA_RG_L);
            pusData[0] = (((WORD)ucTempH) << 4) | ((ucTempL & 0xF0) >> 4);
#endif

            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_04_CTS_GRN_COE_SETA_H);
#if(_HW_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[1] = ucTempH;
#elif(_HW_CTS_TYPE == _CTS_GEN_1_12BIT)
            pusData[1] = (((WORD)ucTempH) << 4) | ((ucTempL & 0x0F));
#endif

            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_05_CTS_BLU_COE_SETA_H);
#if(_HW_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[2] = ucTempH;
#elif(_HW_CTS_TYPE == _CTS_GEN_1_12BIT)
            ucTempL = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_22_CTS_COE_SETA_B_L);
            pusData[2] = (((WORD)ucTempH) << 4) | ((ucTempL & 0xF0) >> 4);
#endif
            break;

        case _CONTRAST_COEF_B:
            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_09_CTS_RED_COE_SETB_H);
#if(_HW_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[0] = ucTempH;
#elif(_HW_CTS_TYPE == _CTS_GEN_1_12BIT)
            ucTempL = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_24_CTS_COE_SETB_RG_L);
            pusData[0] = (((WORD)ucTempH) << 4) | ((ucTempL & 0xF0) >> 4);
#endif

            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_0A_CTS_GRN_COE_SETB_H);
#if(_HW_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[1] = ucTempH;
#elif(_HW_CTS_TYPE == _CTS_GEN_1_12BIT)
            pusData[1] = (((WORD)ucTempH) << 4) | ((ucTempL & 0x0F));
#endif

            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_0B_CTS_BLU_COE_SETB_H);
#if(_HW_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[2] = ucTempH;
#elif(_HW_CTS_TYPE == _CTS_GEN_1_12BIT)
            ucTempL = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_25_CTS_COE_SETB_B_L);
            pusData[2] = (((WORD)ucTempH) << 4) | ((ucTempL & 0xF0) >> 4);
#endif
            break;

        default:
            break;
    }
}
#endif  // End of #if(_COLOR_IP_CONTRAST == _ON)

