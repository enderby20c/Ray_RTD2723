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
// ID Code      : RL6952_Series_Pinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_PINSHARE__

#include "ScalerFunctionInclude.h"
#include "Pinshare/ScalerPinshare.h"

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
// Description  : Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareInitial(void)
{
    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_J4);
    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_K4);
    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, _PIN_H4);
    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _PIN_G6);
    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON2, _PIN_AD4);
    ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4);
    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5);
    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON2, _PIN_T4);
    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON2, _PIN_AA4);
    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON2, _PIN_AA5);
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON2, _PIN_AB4);
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON2, _PIN_AB5);
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON3, _PIN_AE4);
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON3, _PIN_AE5);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON3, _PIN_AD5);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON3, _PIN_AF6);
    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON3, _PIN_AF7);
    ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6);
    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7);
    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON3, _PIN_AF12);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON3, _PIN_AF11);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON3, _PIN_AF10);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON3, _PIN_AF9);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON3, _PIN_AG12);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON3, _PIN_AG11);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON3, _PIN_AG10);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON3, _PIN_AG9);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__OFF2, _PIN_AG20_OFF_REGION);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__OFF2, _PIN_AF20_OFF_REGION);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__OFF2, _PIN_AF19_OFF_REGION);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL1E__OFF2, 0x03); // Always Audio_Vref Funtion
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__OFF2, _PIN_AG22_OFF_REGION);
    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__OFF2, _PIN_AF22_OFF_REGION);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__OFF2, _PIN_AG23_OFF_REGION);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__OFF2, _PIN_AE23_OFF_REGION);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__OFF2, _PIN_AA22_OFF_REGION);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_OFF_REGION);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_OFF_REGION);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_OFF_REGION);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_OFF_REGION);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__OFF2, _PIN_AB26_OFF_REGION);
    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__OFF2, _PIN_AC26_OFF_REGION);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__OFF2, _PIN_Y26_OFF_REGION);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__OFF2, _PIN_AA26_OFF_REGION);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__OFF2, _PIN_Y23_OFF_REGION);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__OFF2, _PIN_Y22_OFF_REGION);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_OFF_REGION);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_OFF_REGION);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__OFF2, _PIN_AA24_OFF_REGION);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__OFF2, _PIN_Y25_OFF_REGION);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__OFF2, _PIN_AA25_OFF_REGION);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__OFF2, _PIN_AC25_OFF_REGION);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__OFF2, _PIN_AB25_OFF_REGION);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL35__OFF1, _PIN_R28_OFF_REGION);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL36__OFF1, _PIN_R30_OFF_REGION);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL37__OFF1, _PIN_R29_OFF_REGION);
    ScalerSetByte(P10_38_PIN_SHARE_CTRL38__OFF1, _PIN_P28_OFF_REGION);
    ScalerSetByte(P10_39_PIN_SHARE_CTRL39__OFF1, _PIN_P29_OFF_REGION);
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL3A__OFF1, _PIN_N29_OFF_REGION);
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL3B__OFF1, _PIN_N30_OFF_REGION);
    ScalerSetByte(P10_3C_PIN_SHARE_CTRL3C__OFF1, _PIN_N28_OFF_REGION);
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL3D__OFF1, _PIN_L28_OFF_REGION);
    ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__OFF1, _PIN_L30_OFF_REGION);
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL3F__OFF1, _PIN_L29_OFF_REGION);
    ScalerSetByte(P10_40_PIN_SHARE_CTRL40__OFF1, _PIN_K28_OFF_REGION);
    ScalerSetByte(P10_41_PIN_SHARE_CTRL41__OFF1, _PIN_K29_OFF_REGION);
    ScalerSetByte(P10_42_PIN_SHARE_CTRL42__OFF1, _PIN_J29_OFF_REGION);
    ScalerSetByte(P10_43_PIN_SHARE_CTRL43__OFF1, _PIN_J30_OFF_REGION);
    ScalerSetByte(P10_44_PIN_SHARE_CTRL44__OFF1, _PIN_J28_OFF_REGION);
    ScalerSetByte(P10_45_PIN_SHARE_CTRL45__OFF1, _PIN_G28_OFF_REGION);
    ScalerSetByte(P10_46_PIN_SHARE_CTRL46__OFF1, _PIN_G30_OFF_REGION);
    ScalerSetByte(P10_47_PIN_SHARE_CTRL47__OFF1, _PIN_G29_OFF_REGION);
    ScalerSetByte(P10_48_PIN_SHARE_CTRL48__OFF1, _PIN_F28_OFF_REGION);
    ScalerSetByte(P10_49_PIN_SHARE_CTRL49__OFF1, _PIN_F29_OFF_REGION);
    ScalerSetByte(P10_4A_PIN_SHARE_CTRL4A__OFF1, _PIN_E29_OFF_REGION);
    ScalerSetByte(P10_4B_PIN_SHARE_CTRL4B__OFF1, _PIN_E30_OFF_REGION);
    ScalerSetByte(P10_4C_PIN_SHARE_CTRL4C__OFF1, _PIN_E28_OFF_REGION);
    ScalerSetByte(P10_4D_PIN_SHARE_CTRL4D__OFF1, _PIN_C28_OFF_REGION);
    ScalerSetByte(P10_4E_PIN_SHARE_CTRL4E__OFF1, _PIN_A28_OFF_REGION);
    ScalerSetByte(P10_4F_PIN_SHARE_CTRL4F__OFF1, _PIN_B28_OFF_REGION);
    ScalerSetByte(P10_50_PIN_SHARE_CTRL50__OFF1, _PIN_C27_OFF_REGION);
    ScalerSetByte(P10_51_PIN_SHARE_CTRL51__OFF1, _PIN_B27_OFF_REGION);
    ScalerSetByte(P10_52_PIN_SHARE_CTRL52__OFF1, _PIN_B26_OFF_REGION);
    ScalerSetByte(P10_53_PIN_SHARE_CTRL53__OFF1, _PIN_A26_OFF_REGION);
    ScalerSetByte(P10_54_PIN_SHARE_CTRL54__OFF1, _PIN_C26_OFF_REGION);
    ScalerSetByte(P10_55_PIN_SHARE_CTRL55__OFF1, _PIN_C24_OFF_REGION);
    ScalerSetByte(P10_56_PIN_SHARE_CTRL56__OFF1, _PIN_A24_OFF_REGION);
    ScalerSetByte(P10_57_PIN_SHARE_CTRL57__OFF1, _PIN_B24_OFF_REGION);
    ScalerSetByte(P10_58_PIN_SHARE_CTRL58__OFF1, _PIN_C23_OFF_REGION);
    ScalerSetByte(P10_59_PIN_SHARE_CTRL59__OFF1, _PIN_B23_OFF_REGION);
    ScalerSetByte(P10_5A_PIN_SHARE_CTRL5A__OFF1, _PIN_B22_OFF_REGION);
    ScalerSetByte(P10_5B_PIN_SHARE_CTRL5B__OFF1, _PIN_A22_OFF_REGION);
    ScalerSetByte(P10_5C_PIN_SHARE_CTRL5C__OFF1, _PIN_C22_OFF_REGION);
    ScalerSetByte(P10_5D_PIN_SHARE_CTRL5D__OFF1, _PIN_B20_OFF_REGION);
    ScalerSetByte(P10_5E_PIN_SHARE_CTRL5E__OFF1, _PIN_A20_OFF_REGION);
    ScalerSetByte(P10_5F_PIN_SHARE_CTRL5F__OFF1, _PIN_B19_OFF_REGION);
    ScalerSetByte(P10_60_PIN_SHARE_CTRL60__OFF1, _PIN_A19_OFF_REGION);
    ScalerSetByte(P10_61_PIN_SHARE_CTRL61__ON1, _PIN_K9);
    ScalerSetByte(P10_62_PIN_SHARE_CTRL62__ON1, _PIN_H13);
    ScalerSetByte(P10_63_PIN_SHARE_CTRL63__ON1, _PIN_H11);
    ScalerSetByte(P10_64_PIN_SHARE_CTRL64__ON1, _PIN_K8);
    ScalerSetByte(P10_65_PIN_SHARE_CTRL65__ON1, _PIN_H12);
    ScalerSetByte(P10_66_PIN_SHARE_CTRL66__ON1, _PIN_J8);
    ScalerSetByte(P10_67_PIN_SHARE_CTRL67__ON1, _PIN_F9);
    ScalerSetByte(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11);
    ScalerSetByte(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12);
    ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13);
    ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13);
    ScalerSetByte(P10_6C_PIN_SHARE_CTRL6C__ON1, _PIN_E12);
    ScalerSetByte(P10_6D_PIN_SHARE_CTRL6D__ON1, _PIN_G9);
    ScalerSetByte(P10_6E_PIN_SHARE_CTRL6E__ON1, _PIN_F8);
    ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__ON1, _PIN_E3);
    ScalerSetByte(P10_70_PIN_SHARE_CTRL70__ON1, _PIN_H8);
    ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5);
    ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4);
    ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3);
    ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7);
    ScalerSetByte(P10_75_PIN_SHARE_CTRL75__ON1, _PIN_C5);
    ScalerSetByte(P10_76_PIN_SHARE_CTRL76__ON1, _PIN_B5);
    ScalerSetByte(P10_77_PIN_SHARE_CTRL77__ON1, _PIN_B4);
    ScalerSetByte(P10_78_PIN_SHARE_CTRL78__ON1, _PIN_C4);
    ScalerSetByte(P10_79_PIN_SHARE_CTRL79__ON1, _PIN_C3);
    ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9);
    ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5);
    ScalerSetByte(P10_7C_PIN_SHARE_CTRL7C__ON1, _PIN_D12);
    ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13);
    ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9);
    ScalerSetByte(P10_7F_PIN_SHARE_CTRL7F__ON1, _PIN_A5);
    ScalerSetByte(P10_80_PIN_SHARE_CTRL80__ON1, _PIN_E11);
    ScalerSetByte(P10_81_PIN_SHARE_CTRL81__ON2, _PIN_V4);
    ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4);
    ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8);
    ScalerSetByte(P10_84_PIN_SHARE_CTRL84__ON1, _PIN_E4);
    ScalerSetByte(P10_85_PIN_SHARE_CTRL85__ON1, _PIN_G7);
    ScalerSetByte(P10_86_PIN_SHARE_CTRL86__ON1, _PIN_A2);
    ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _PIN_B3);
    ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _PIN_B2);
    ScalerSetByte(P10_89_PIN_SHARE_CTRL89__ON1, _PIN_A4);
    ScalerSetByte(P10_8A_PIN_SHARE_CTRL8A__ON1, _PIN_A3);
    ScalerSetByte(P10_8B_PIN_SHARE_CTRL8B__ON1, _PIN_G5);
    ScalerSetByte(P10_8C_PIN_SHARE_CTRL8C__ON1, _PIN_F4);
    ScalerSetByte(P10_8D_PIN_SHARE_CTRL8D__ON1, _PIN_H5);
    ScalerSetByte(P10_8E_PIN_SHARE_CTRL8E__ON1, _PIN_F3);

    // Set Pin configure to AC ON
    ScalerPinshareConfig(_POWER_STATUS_AC_ON);

    // Pin Config adjust sample (this is a ineffective configuration example aviod uncall worning)
    ScalerPinshareAdjustConfig(_CONFIG_PIN_START, _CONFIG_TYPE_GPI);
    ScalerPinshareGpioDdcPinSwitch(0xFF);

    // I2C_1 Slave Pinshare Setting
#if(_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO)

#endif
}

//--------------------------------------------------
// Description  : Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinsharePowerOnReset(void)
{
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__OFF2, _PIN_AG20_OFF_REGION);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__OFF2, _PIN_AF20_OFF_REGION);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__OFF2, _PIN_AF19_OFF_REGION);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL1E__OFF2, 0x03); // Always Audio_Vref Funtion
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__OFF2, _PIN_AG22_OFF_REGION);
    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__OFF2, _PIN_AF22_OFF_REGION);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__OFF2, _PIN_AG23_OFF_REGION);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__OFF2, _PIN_AE23_OFF_REGION);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__OFF2, _PIN_AA22_OFF_REGION);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_OFF_REGION);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_OFF_REGION);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_OFF_REGION);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_OFF_REGION);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__OFF2, _PIN_AB26_OFF_REGION);
    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__OFF2, _PIN_AC26_OFF_REGION);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__OFF2, _PIN_Y26_OFF_REGION);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__OFF2, _PIN_AA26_OFF_REGION);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__OFF2, _PIN_Y23_OFF_REGION);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__OFF2, _PIN_Y22_OFF_REGION);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_OFF_REGION);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_OFF_REGION);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__OFF2, _PIN_AA24_OFF_REGION);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__OFF2, _PIN_Y25_OFF_REGION);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__OFF2, _PIN_AA25_OFF_REGION);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__OFF2, _PIN_AC25_OFF_REGION);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__OFF2, _PIN_AB25_OFF_REGION);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL35__OFF1, _PIN_R28_OFF_REGION);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL36__OFF1, _PIN_R30_OFF_REGION);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL37__OFF1, _PIN_R29_OFF_REGION);
    ScalerSetByte(P10_38_PIN_SHARE_CTRL38__OFF1, _PIN_P28_OFF_REGION);
    ScalerSetByte(P10_39_PIN_SHARE_CTRL39__OFF1, _PIN_P29_OFF_REGION);
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL3A__OFF1, _PIN_N29_OFF_REGION);
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL3B__OFF1, _PIN_N30_OFF_REGION);
    ScalerSetByte(P10_3C_PIN_SHARE_CTRL3C__OFF1, _PIN_N28_OFF_REGION);
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL3D__OFF1, _PIN_L28_OFF_REGION);
    ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__OFF1, _PIN_L30_OFF_REGION);
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL3F__OFF1, _PIN_L29_OFF_REGION);
    ScalerSetByte(P10_40_PIN_SHARE_CTRL40__OFF1, _PIN_K28_OFF_REGION);
    ScalerSetByte(P10_41_PIN_SHARE_CTRL41__OFF1, _PIN_K29_OFF_REGION);
    ScalerSetByte(P10_42_PIN_SHARE_CTRL42__OFF1, _PIN_J29_OFF_REGION);
    ScalerSetByte(P10_43_PIN_SHARE_CTRL43__OFF1, _PIN_J30_OFF_REGION);
    ScalerSetByte(P10_44_PIN_SHARE_CTRL44__OFF1, _PIN_J28_OFF_REGION);
    ScalerSetByte(P10_45_PIN_SHARE_CTRL45__OFF1, _PIN_G28_OFF_REGION);
    ScalerSetByte(P10_46_PIN_SHARE_CTRL46__OFF1, _PIN_G30_OFF_REGION);
    ScalerSetByte(P10_47_PIN_SHARE_CTRL47__OFF1, _PIN_G29_OFF_REGION);
    ScalerSetByte(P10_48_PIN_SHARE_CTRL48__OFF1, _PIN_F28_OFF_REGION);
    ScalerSetByte(P10_49_PIN_SHARE_CTRL49__OFF1, _PIN_F29_OFF_REGION);
    ScalerSetByte(P10_4A_PIN_SHARE_CTRL4A__OFF1, _PIN_E29_OFF_REGION);
    ScalerSetByte(P10_4B_PIN_SHARE_CTRL4B__OFF1, _PIN_E30_OFF_REGION);
    ScalerSetByte(P10_4C_PIN_SHARE_CTRL4C__OFF1, _PIN_E28_OFF_REGION);
    ScalerSetByte(P10_4D_PIN_SHARE_CTRL4D__OFF1, _PIN_C28_OFF_REGION);
    ScalerSetByte(P10_4E_PIN_SHARE_CTRL4E__OFF1, _PIN_A28_OFF_REGION);
    ScalerSetByte(P10_4F_PIN_SHARE_CTRL4F__OFF1, _PIN_B28_OFF_REGION);
    ScalerSetByte(P10_50_PIN_SHARE_CTRL50__OFF1, _PIN_C27_OFF_REGION);
    ScalerSetByte(P10_51_PIN_SHARE_CTRL51__OFF1, _PIN_B27_OFF_REGION);
    ScalerSetByte(P10_52_PIN_SHARE_CTRL52__OFF1, _PIN_B26_OFF_REGION);
    ScalerSetByte(P10_53_PIN_SHARE_CTRL53__OFF1, _PIN_A26_OFF_REGION);
    ScalerSetByte(P10_54_PIN_SHARE_CTRL54__OFF1, _PIN_C26_OFF_REGION);
    ScalerSetByte(P10_55_PIN_SHARE_CTRL55__OFF1, _PIN_C24_OFF_REGION);
    ScalerSetByte(P10_56_PIN_SHARE_CTRL56__OFF1, _PIN_A24_OFF_REGION);
    ScalerSetByte(P10_57_PIN_SHARE_CTRL57__OFF1, _PIN_B24_OFF_REGION);
    ScalerSetByte(P10_58_PIN_SHARE_CTRL58__OFF1, _PIN_C23_OFF_REGION);
    ScalerSetByte(P10_59_PIN_SHARE_CTRL59__OFF1, _PIN_B23_OFF_REGION);
    ScalerSetByte(P10_5A_PIN_SHARE_CTRL5A__OFF1, _PIN_B22_OFF_REGION);
    ScalerSetByte(P10_5B_PIN_SHARE_CTRL5B__OFF1, _PIN_A22_OFF_REGION);
    ScalerSetByte(P10_5C_PIN_SHARE_CTRL5C__OFF1, _PIN_C22_OFF_REGION);
    ScalerSetByte(P10_5D_PIN_SHARE_CTRL5D__OFF1, _PIN_B20_OFF_REGION);
    ScalerSetByte(P10_5E_PIN_SHARE_CTRL5E__OFF1, _PIN_A20_OFF_REGION);
    ScalerSetByte(P10_5F_PIN_SHARE_CTRL5F__OFF1, _PIN_B19_OFF_REGION);
    ScalerSetByte(P10_60_PIN_SHARE_CTRL60__OFF1, _PIN_A19_OFF_REGION);
}

//--------------------------------------------------
// Description  : Soft Reset Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareSoftReset(void)
{
    return;
}

#if((_HW_IIC_SUPPORT == _ON) || (_TYPEC_IIC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set HW IIC Pin Out
// Input Value  : ucHwIICPinNum --> PinD13_H9/E3_H8/E3_H8/D5_D4/H12_J8/D3_H7/D13_H9/W23_W22/U4_G8/J9_E5/D3_H7/AE26_AD26/D5_D4/AA23_Y24/U4_G8/W23_W22/AA23_Y24/AE26_AD26/AG6_AG7/J9_E5/H12_J8
// Output Value : None
//--------------------------------------------------
void ScalerPinshareHwIICPin(BYTE ucHwIICPinNum)
{
    // Set the selected HwIICPinNum to IIC output
    // Set the others as GPI
    switch(ucHwIICPinNum)
    {
        case _HW_IIC_PIN_D13_H9_0_3:

            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_IICSCL_0_3);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_IICSDA_0_3);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            break;

        case _HW_IIC_PIN_D5_D4_0_0:

            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_IICSCL_0_0);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_IICSDA_0_0);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            break;

        case _HW_IIC_PIN_D3_H7_0_1:

            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_IICSCL_0_1);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_IICSDA_0_1);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            break;

        case _HW_IIC_PIN_D13_H9_1_3:

            if((_PIN_D13 == _PIN_D13_IICSCL_1_3) && (_PIN_H9 == _PIN_H9_IICSDA_1_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_IICSCL_1_3);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_IICSDA_1_3);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_1_2) && (_PIN_E5 == _PIN_E5_IICSDA_1_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_1_1) && (_PIN_H7 == _PIN_H7_IICSDA_1_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_1_0) && (_PIN_D4 == _PIN_D4_IICSDA_1_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_1_7) && (_PIN_G8 == _PIN_G8_IICSDA_1_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_1_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_1_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_1_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_1_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_1_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_1_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            break;

        case _HW_IIC_PIN_W23_W22_0_6:

            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_IICSCL_0_6);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_IICSDA_0_6);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            break;

        case _HW_IIC_PIN_U4_G8_0_7:

            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_IICSCL_0_7);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_IICSDA_0_7);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            break;

        case _HW_IIC_PIN_J9_E5_1_2:

            if((_PIN_J9 == _PIN_J9_IICSCL_1_2) && (_PIN_E5 == _PIN_E5_IICSDA_1_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_IICSCL_1_2);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_IICSDA_1_2);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_1_3) && (_PIN_H9 == _PIN_H9_IICSDA_1_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_1_1) && (_PIN_H7 == _PIN_H7_IICSDA_1_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_1_0) && (_PIN_D4 == _PIN_D4_IICSDA_1_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_1_7) && (_PIN_G8 == _PIN_G8_IICSDA_1_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_1_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_1_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_1_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_1_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_1_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_1_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            break;

        case _HW_IIC_PIN_D3_H7_1_1:

            if((_PIN_D3 == _PIN_D3_IICSCL_1_1) && (_PIN_H7 == _PIN_H7_IICSDA_1_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_IICSCL_1_1);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_IICSDA_1_1);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_1_3) && (_PIN_H9 == _PIN_H9_IICSDA_1_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_1_2) && (_PIN_E5 == _PIN_E5_IICSDA_1_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_1_0) && (_PIN_D4 == _PIN_D4_IICSDA_1_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_1_7) && (_PIN_G8 == _PIN_G8_IICSDA_1_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_1_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_1_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_1_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_1_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_1_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_1_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            break;

        case _HW_IIC_PIN_AE26_AD26_0_4:

            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_IICSCL_0_4);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_IICSDA_0_4);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            break;

        case _HW_IIC_PIN_D5_D4_1_0:

            if((_PIN_D5 == _PIN_D5_IICSCL_1_0) && (_PIN_D4 == _PIN_D4_IICSDA_1_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_IICSCL_1_0);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_IICSDA_1_0);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_1_3) && (_PIN_H9 == _PIN_H9_IICSDA_1_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_1_2) && (_PIN_E5 == _PIN_E5_IICSDA_1_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_1_1) && (_PIN_H7 == _PIN_H7_IICSDA_1_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_1_7) && (_PIN_G8 == _PIN_G8_IICSDA_1_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_1_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_1_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_1_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_1_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_1_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_1_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            break;

        case _HW_IIC_PIN_AA23_Y24_0_5:

            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_IICSCL_0_5);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_IICSDA_0_5);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            break;

        case _HW_IIC_PIN_U4_G8_1_7:

            if((_PIN_U4 == _PIN_U4_IICSCL_1_7) && (_PIN_G8 == _PIN_G8_IICSDA_1_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_IICSCL_1_7);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_IICSDA_1_7);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_1_3) && (_PIN_H9 == _PIN_H9_IICSDA_1_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_1_2) && (_PIN_E5 == _PIN_E5_IICSDA_1_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_1_1) && (_PIN_H7 == _PIN_H7_IICSDA_1_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_1_0) && (_PIN_D4 == _PIN_D4_IICSDA_1_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_1_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_1_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_1_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_1_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_1_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_1_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            break;

        case _HW_IIC_PIN_W23_W22_1_6:

            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_1_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_1_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_IICSCL_1_6);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_IICSDA_1_6);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_1_3) && (_PIN_H9 == _PIN_H9_IICSDA_1_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_1_2) && (_PIN_E5 == _PIN_E5_IICSDA_1_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_1_1) && (_PIN_H7 == _PIN_H7_IICSDA_1_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_1_0) && (_PIN_D4 == _PIN_D4_IICSDA_1_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_1_7) && (_PIN_G8 == _PIN_G8_IICSDA_1_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_1_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_1_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_1_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_1_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            break;

        case _HW_IIC_PIN_AA23_Y24_1_5:

            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_1_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_1_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_IICSCL_1_5);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_IICSDA_1_5);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_1_3) && (_PIN_H9 == _PIN_H9_IICSDA_1_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_1_2) && (_PIN_E5 == _PIN_E5_IICSDA_1_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_1_1) && (_PIN_H7 == _PIN_H7_IICSDA_1_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_1_0) && (_PIN_D4 == _PIN_D4_IICSDA_1_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_1_7) && (_PIN_G8 == _PIN_G8_IICSDA_1_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_1_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_1_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_1_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_1_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            break;

        case _HW_IIC_PIN_AE26_AD26_1_4:

            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_1_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_1_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_IICSCL_1_4);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_IICSDA_1_4);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_1_3) && (_PIN_H9 == _PIN_H9_IICSDA_1_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_1_2) && (_PIN_E5 == _PIN_E5_IICSDA_1_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_1_1) && (_PIN_H7 == _PIN_H7_IICSDA_1_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_1_0) && (_PIN_D4 == _PIN_D4_IICSDA_1_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_1_7) && (_PIN_G8 == _PIN_G8_IICSDA_1_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_1_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_1_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_1_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_1_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            break;

        case _HW_IIC_PIN_AG6_AG7:

            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_EEIICSCL);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_EEIICSDA);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
            }
            break;

        case _HW_IIC_PIN_J9_E5_0_2:

            if((_PIN_J9 == _PIN_J9_IICSCL_0_2) && (_PIN_E5 == _PIN_E5_IICSDA_0_2))
            {
                ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_IICSCL_0_2);
                ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_IICSDA_0_2);
            }
            if((_PIN_D13 == _PIN_D13_IICSCL_0_3) && (_PIN_H9 == _PIN_H9_IICSDA_0_3))
            {
                ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
            }
            if((_PIN_D5 == _PIN_D5_IICSCL_0_0) && (_PIN_D4 == _PIN_D4_IICSDA_0_0))
            {
                ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
            }
            if((_PIN_D3 == _PIN_D3_IICSCL_0_1) && (_PIN_H7 == _PIN_H7_IICSDA_0_1))
            {
                ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
            }
            if((_PIN_W23_OFF_REGION == _PIN_W23_IICSCL_0_6) && (_PIN_W22_OFF_REGION == _PIN_W22_IICSDA_0_6))
            {
                ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
            }
            if((_PIN_U4 == _PIN_U4_IICSCL_0_7) && (_PIN_G8 == _PIN_G8_IICSDA_0_7))
            {
                ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
            }
            if((_PIN_AE26_OFF_REGION == _PIN_AE26_IICSCL_0_4) && (_PIN_AD26_OFF_REGION == _PIN_AD26_IICSDA_0_4))
            {
                ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
            }
            if((_PIN_AA23_OFF_REGION == _PIN_AA23_IICSCL_0_5) && (_PIN_Y24_OFF_REGION == _PIN_Y24_IICSDA_0_5))
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
            }
            if((_PIN_AG6 == _PIN_AG6_EEIICSCL) && (_PIN_AG7 == _PIN_AG7_EEIICSDA))
            {
                ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
            }
            break;

        case _TYPEC_IIC_PIN_H12_J8_0_1:

            if((_PIN_H12 == _PIN_H12_TPC_IICSCL_0_1) && (_PIN_J8 == _PIN_J8_TPC_IICSDA_0_1))
            {
                ScalerSetByte(P10_65_PIN_SHARE_CTRL65__ON1, _PIN_H12_TPC_IICSCL_0_1);
                ScalerSetByte(P10_66_PIN_SHARE_CTRL66__ON1, _PIN_J8_TPC_IICSDA_0_1);
            }
            if((_PIN_E3 == _PIN_E3_TPC_IICSCL_0_0) && (_PIN_H8 == _PIN_H8_TPC_IICSDA_0_0))
            {
                ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__ON1, _PIN_E3_GPI);
                ScalerSetByte(P10_70_PIN_SHARE_CTRL70__ON1, _PIN_H8_GPI);
            }
            break;

        case _TYPEC_IIC_PIN_H12_J8_1_1:

            if((_PIN_H12 == _PIN_H12_TPC_IICSCL_1_1) && (_PIN_J8 == _PIN_J8_TPC_IICSDA_1_1))
            {
                ScalerSetByte(P10_65_PIN_SHARE_CTRL65__ON1, _PIN_H12_TPC_IICSCL_1_1);
                ScalerSetByte(P10_66_PIN_SHARE_CTRL66__ON1, _PIN_J8_TPC_IICSDA_1_1);
            }
            if((_PIN_E3 == _PIN_E3_TPC_IICSCL_1_0) && (_PIN_H8 == _PIN_H8_TPC_IICSDA_1_0))
            {
                ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__ON1, _PIN_E3_GPI);
                ScalerSetByte(P10_70_PIN_SHARE_CTRL70__ON1, _PIN_H8_GPI);
            }
            break;

        case _TYPEC_IIC_PIN_E3_H8_0_0:

            if((_PIN_E3 == _PIN_E3_TPC_IICSCL_0_0) && (_PIN_H8 == _PIN_H8_TPC_IICSDA_0_0))
            {
                ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__ON1, _PIN_E3_TPC_IICSCL_0_0);
                ScalerSetByte(P10_70_PIN_SHARE_CTRL70__ON1, _PIN_H8_TPC_IICSDA_0_0);
            }
            if((_PIN_H12 == _PIN_H12_TPC_IICSCL_0_1) && (_PIN_J8 == _PIN_J8_TPC_IICSDA_0_1))
            {
                ScalerSetByte(P10_65_PIN_SHARE_CTRL65__ON1, _PIN_H12_GPI);
                ScalerSetByte(P10_66_PIN_SHARE_CTRL66__ON1, _PIN_J8_GPI);
            }
            break;

        case _TYPEC_IIC_PIN_E3_H8_1_0:

            if((_PIN_E3 == _PIN_E3_TPC_IICSCL_1_0) && (_PIN_H8 == _PIN_H8_TPC_IICSDA_1_0))
            {
                ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__ON1, _PIN_E3_TPC_IICSCL_1_0);
                ScalerSetByte(P10_70_PIN_SHARE_CTRL70__ON1, _PIN_H8_TPC_IICSDA_1_0);
            }
            if((_PIN_H12 == _PIN_H12_TPC_IICSCL_1_1) && (_PIN_J8 == _PIN_J8_TPC_IICSDA_1_1))
            {
                ScalerSetByte(P10_65_PIN_SHARE_CTRL65__ON1, _PIN_H12_GPI);
                ScalerSetByte(P10_66_PIN_SHARE_CTRL66__ON1, _PIN_J8_GPI);
            }
            break;

        default:
            break;
    }
}
#endif  // End of #if(_HW_IIC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Switch DDC pin to GPIO or viceversa
// Input Value  : ucPinType --> PinD5_D4/C4_C3/B3_B2
// Output Value : None
//--------------------------------------------------
void ScalerPinshareGpioDdcPinSwitch(BYTE ucPinType)
{
    switch(ucPinType)
    {
        case _DDCISP_SWITCH_GPIO:
            ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPO_OD);
            ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPO_OD);
            break;

        case _DDCISP_SWITCH_DDC:
            ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_DDCSCL_ISP);
            ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_DDCSDA_ISP);
            break;

        case _DDC3_SWITCH_GPIO:
            ScalerSetByte(P10_78_PIN_SHARE_CTRL78__ON1, _PIN_C4_GPO_OD);
            ScalerSetByte(P10_79_PIN_SHARE_CTRL79__ON1, _PIN_C3_GPO_OD);
            break;

        case _DDC3_SWITCH_DDC:
            ScalerSetByte(P10_78_PIN_SHARE_CTRL78__ON1, _PIN_C4_DDCSCL_3);
            ScalerSetByte(P10_79_PIN_SHARE_CTRL79__ON1, _PIN_C3_DDCSDA_3);
            break;

        case _DDC4_SWITCH_GPIO:
            ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _PIN_B3_GPO_OD);
            ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _PIN_B2_GPO_OD);
            break;

        case _DDC4_SWITCH_DDC:
            ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _PIN_B3_DDCSCL_4);
            ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _PIN_B2_DDCSDA_4);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust pin share config
// Input Value  : enumConfigPin  --> Pin num
//                enumConfigType --> Pin type(GPIO/PWM..Etc.)
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType)
{
    switch(enumConfigPin)
    {
        case _CONFIG_PIN_J4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_J4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_J4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_J4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_K4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_K4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_K4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, _PIN_H4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, _PIN_H4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, _PIN_H4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_G6:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _PIN_G6_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _PIN_G6_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _PIN_G6_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AD4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON2, _PIN_AD4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON2, _PIN_AD4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON2, _PIN_AD4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_W4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_W5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_T4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON2, _PIN_T4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON2, _PIN_T4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON2, _PIN_T4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AA4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON2, _PIN_AA4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON2, _PIN_AA4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON2, _PIN_AA4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AA5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON2, _PIN_AA5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON2, _PIN_AA5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON2, _PIN_AA5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AB4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON2, _PIN_AB4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON2, _PIN_AB4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON2, _PIN_AB4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AB5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON2, _PIN_AB5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON2, _PIN_AB5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON2, _PIN_AB5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AE4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON3, _PIN_AE4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON3, _PIN_AE4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON3, _PIN_AE4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AE5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON3, _PIN_AE5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON3, _PIN_AE5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON3, _PIN_AE5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AD5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON3, _PIN_AD5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON3, _PIN_AD5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON3, _PIN_AD5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF6:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON3, _PIN_AF6_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON3, _PIN_AF6_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON3, _PIN_AF6_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF7:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON3, _PIN_AF7_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON3, _PIN_AF7_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON3, _PIN_AF7_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG6:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON3, _PIN_AG6_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG7:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON3, _PIN_AG7_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF12:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON3, _PIN_AF12_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON3, _PIN_AF12_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON3, _PIN_AF12_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF11:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON3, _PIN_AF11_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON3, _PIN_AF11_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON3, _PIN_AF11_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF10:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON3, _PIN_AF10_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON3, _PIN_AF10_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON3, _PIN_AF10_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF9:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON3, _PIN_AF9_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON3, _PIN_AF9_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON3, _PIN_AF9_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG12:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON3, _PIN_AG12_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON3, _PIN_AG12_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON3, _PIN_AG12_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG11:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON3, _PIN_AG11_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON3, _PIN_AG11_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON3, _PIN_AG11_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG10:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON3, _PIN_AG10_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON3, _PIN_AG10_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON3, _PIN_AG10_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG9:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON3, _PIN_AG9_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON3, _PIN_AG9_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON3, _PIN_AG9_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG20:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__OFF2, _PIN_AG20_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__OFF2, _PIN_AG20_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__OFF2, _PIN_AG20_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF20:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__OFF2, _PIN_AF20_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__OFF2, _PIN_AF20_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__OFF2, _PIN_AF20_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF19:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__OFF2, _PIN_AF19_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__OFF2, _PIN_AF19_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__OFF2, _PIN_AF19_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG22:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__OFF2, _PIN_AG22_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__OFF2, _PIN_AG22_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__OFF2, _PIN_AG22_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF22:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__OFF2, _PIN_AF22_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__OFF2, _PIN_AF22_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__OFF2, _PIN_AF22_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG23:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__OFF2, _PIN_AG23_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__OFF2, _PIN_AG23_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__OFF2, _PIN_AG23_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AE23:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__OFF2, _PIN_AE23_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__OFF2, _PIN_AE23_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__OFF2, _PIN_AE23_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AA22:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__OFF2, _PIN_AA22_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__OFF2, _PIN_AA22_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__OFF2, _PIN_AA22_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_W23:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF2, _PIN_W23_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_W22:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF2, _PIN_W22_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AE26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF2, _PIN_AE26_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AD26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF2, _PIN_AD26_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AB26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__OFF2, _PIN_AB26_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__OFF2, _PIN_AB26_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__OFF2, _PIN_AB26_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AC26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__OFF2, _PIN_AC26_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__OFF2, _PIN_AC26_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__OFF2, _PIN_AC26_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_Y26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__OFF2, _PIN_Y26_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__OFF2, _PIN_Y26_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__OFF2, _PIN_Y26_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AA26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__OFF2, _PIN_AA26_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__OFF2, _PIN_AA26_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__OFF2, _PIN_AA26_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_Y23:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__OFF2, _PIN_Y23_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__OFF2, _PIN_Y23_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__OFF2, _PIN_Y23_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_Y22:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__OFF2, _PIN_Y22_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__OFF2, _PIN_Y22_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__OFF2, _PIN_Y22_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AA23:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PIN_AA23_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_Y24:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PIN_Y24_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AA24:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__OFF2, _PIN_AA24_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__OFF2, _PIN_AA24_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__OFF2, _PIN_AA24_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_Y25:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__OFF2, _PIN_Y25_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__OFF2, _PIN_Y25_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__OFF2, _PIN_Y25_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AA25:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__OFF2, _PIN_AA25_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__OFF2, _PIN_AA25_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__OFF2, _PIN_AA25_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AC25:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__OFF2, _PIN_AC25_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__OFF2, _PIN_AC25_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__OFF2, _PIN_AC25_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AB25:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__OFF2, _PIN_AB25_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__OFF2, _PIN_AB25_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__OFF2, _PIN_AB25_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_R28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_35_PIN_SHARE_CTRL35__OFF1, _PIN_R28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_R30:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_36_PIN_SHARE_CTRL36__OFF1, _PIN_R30_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_R29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_37_PIN_SHARE_CTRL37__OFF1, _PIN_R29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_P28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_38_PIN_SHARE_CTRL38__OFF1, _PIN_P28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_P29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_39_PIN_SHARE_CTRL39__OFF1, _PIN_P29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_N29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_3A_PIN_SHARE_CTRL3A__OFF1, _PIN_N29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_N30:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_3B_PIN_SHARE_CTRL3B__OFF1, _PIN_N30_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_N28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_3C_PIN_SHARE_CTRL3C__OFF1, _PIN_N28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_L28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_3D_PIN_SHARE_CTRL3D__OFF1, _PIN_L28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_L30:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__OFF1, _PIN_L30_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_L29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_3F_PIN_SHARE_CTRL3F__OFF1, _PIN_L29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_40_PIN_SHARE_CTRL40__OFF1, _PIN_K28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_41_PIN_SHARE_CTRL41__OFF1, _PIN_K29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_J29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_42_PIN_SHARE_CTRL42__OFF1, _PIN_J29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_J30:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_43_PIN_SHARE_CTRL43__OFF1, _PIN_J30_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_J28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_44_PIN_SHARE_CTRL44__OFF1, _PIN_J28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_G28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_45_PIN_SHARE_CTRL45__OFF1, _PIN_G28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_G30:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_46_PIN_SHARE_CTRL46__OFF1, _PIN_G30_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_G29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_47_PIN_SHARE_CTRL47__OFF1, _PIN_G29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_48_PIN_SHARE_CTRL48__OFF1, _PIN_F28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_49_PIN_SHARE_CTRL49__OFF1, _PIN_F29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E29:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_4A_PIN_SHARE_CTRL4A__OFF1, _PIN_E29_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E30:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_4B_PIN_SHARE_CTRL4B__OFF1, _PIN_E30_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_4C_PIN_SHARE_CTRL4C__OFF1, _PIN_E28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_4D_PIN_SHARE_CTRL4D__OFF1, _PIN_C28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_4E_PIN_SHARE_CTRL4E__OFF1, _PIN_A28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B28:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_4F_PIN_SHARE_CTRL4F__OFF1, _PIN_B28_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C27:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_50_PIN_SHARE_CTRL50__OFF1, _PIN_C27_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B27:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_51_PIN_SHARE_CTRL51__OFF1, _PIN_B27_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_52_PIN_SHARE_CTRL52__OFF1, _PIN_B26_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_53_PIN_SHARE_CTRL53__OFF1, _PIN_A26_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C26:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_54_PIN_SHARE_CTRL54__OFF1, _PIN_C26_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C24:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_55_PIN_SHARE_CTRL55__OFF1, _PIN_C24_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A24:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_56_PIN_SHARE_CTRL56__OFF1, _PIN_A24_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B24:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_57_PIN_SHARE_CTRL57__OFF1, _PIN_B24_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C23:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_58_PIN_SHARE_CTRL58__OFF1, _PIN_C23_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B23:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_59_PIN_SHARE_CTRL59__OFF1, _PIN_B23_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B22:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_5A_PIN_SHARE_CTRL5A__OFF1, _PIN_B22_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A22:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_5B_PIN_SHARE_CTRL5B__OFF1, _PIN_A22_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C22:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_5C_PIN_SHARE_CTRL5C__OFF1, _PIN_C22_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B20:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_5D_PIN_SHARE_CTRL5D__OFF1, _PIN_B20_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A20:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_5E_PIN_SHARE_CTRL5E__OFF1, _PIN_A20_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B19:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_5F_PIN_SHARE_CTRL5F__OFF1, _PIN_B19_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A19:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_60_PIN_SHARE_CTRL60__OFF1, _PIN_A19_GPI);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K9:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_61_PIN_SHARE_CTRL61__ON1, _PIN_K9_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_61_PIN_SHARE_CTRL61__ON1, _PIN_K9_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_61_PIN_SHARE_CTRL61__ON1, _PIN_K9_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H13:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_62_PIN_SHARE_CTRL62__ON1, _PIN_H13_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_62_PIN_SHARE_CTRL62__ON1, _PIN_H13_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_62_PIN_SHARE_CTRL62__ON1, _PIN_H13_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H11:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_63_PIN_SHARE_CTRL63__ON1, _PIN_H11_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_63_PIN_SHARE_CTRL63__ON1, _PIN_H11_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_63_PIN_SHARE_CTRL63__ON1, _PIN_H11_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K8:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_64_PIN_SHARE_CTRL64__ON1, _PIN_K8_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_64_PIN_SHARE_CTRL64__ON1, _PIN_K8_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_64_PIN_SHARE_CTRL64__ON1, _PIN_K8_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H12:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_65_PIN_SHARE_CTRL65__ON1, _PIN_H12_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_65_PIN_SHARE_CTRL65__ON1, _PIN_H12_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_65_PIN_SHARE_CTRL65__ON1, _PIN_H12_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_J8:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_66_PIN_SHARE_CTRL66__ON1, _PIN_J8_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_66_PIN_SHARE_CTRL66__ON1, _PIN_J8_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_66_PIN_SHARE_CTRL66__ON1, _PIN_J8_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F9:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_67_PIN_SHARE_CTRL67__ON1, _PIN_F9_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_67_PIN_SHARE_CTRL67__ON1, _PIN_F9_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_67_PIN_SHARE_CTRL67__ON1, _PIN_F9_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F11:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F12:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E13:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F13:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E12:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_6C_PIN_SHARE_CTRL6C__ON1, _PIN_E12_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_6C_PIN_SHARE_CTRL6C__ON1, _PIN_E12_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_6C_PIN_SHARE_CTRL6C__ON1, _PIN_E12_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_G9:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_6D_PIN_SHARE_CTRL6D__ON1, _PIN_G9_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_6D_PIN_SHARE_CTRL6D__ON1, _PIN_G9_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_6D_PIN_SHARE_CTRL6D__ON1, _PIN_G9_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F8:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_6E_PIN_SHARE_CTRL6E__ON1, _PIN_F8_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_6E_PIN_SHARE_CTRL6E__ON1, _PIN_F8_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_6E_PIN_SHARE_CTRL6E__ON1, _PIN_F8_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E3:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__ON1, _PIN_E3_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__ON1, _PIN_E3_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__ON1, _PIN_E3_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H8:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_70_PIN_SHARE_CTRL70__ON1, _PIN_H8_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_70_PIN_SHARE_CTRL70__ON1, _PIN_H8_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_70_PIN_SHARE_CTRL70__ON1, _PIN_H8_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_D5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_71_PIN_SHARE_CTRL71__ON1, _PIN_D5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_D4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_72_PIN_SHARE_CTRL72__ON1, _PIN_D4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_D3:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_73_PIN_SHARE_CTRL73__ON1, _PIN_D3_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H7:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_75_PIN_SHARE_CTRL75__ON1, _PIN_C5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_75_PIN_SHARE_CTRL75__ON1, _PIN_C5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_75_PIN_SHARE_CTRL75__ON1, _PIN_C5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_76_PIN_SHARE_CTRL76__ON1, _PIN_B5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_76_PIN_SHARE_CTRL76__ON1, _PIN_B5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_76_PIN_SHARE_CTRL76__ON1, _PIN_B5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_77_PIN_SHARE_CTRL77__ON1, _PIN_B4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_77_PIN_SHARE_CTRL77__ON1, _PIN_B4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_77_PIN_SHARE_CTRL77__ON1, _PIN_B4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_78_PIN_SHARE_CTRL78__ON1, _PIN_C4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_78_PIN_SHARE_CTRL78__ON1, _PIN_C4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_78_PIN_SHARE_CTRL78__ON1, _PIN_C4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C3:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_79_PIN_SHARE_CTRL79__ON1, _PIN_C3_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_79_PIN_SHARE_CTRL79__ON1, _PIN_C3_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_79_PIN_SHARE_CTRL79__ON1, _PIN_C3_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_J9:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__ON1, _PIN_J9_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__ON1, _PIN_E5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_D12:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_7C_PIN_SHARE_CTRL7C__ON1, _PIN_D12_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_7C_PIN_SHARE_CTRL7C__ON1, _PIN_D12_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_7C_PIN_SHARE_CTRL7C__ON1, _PIN_D12_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_D13:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__ON1, _PIN_D13_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H9:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_7F_PIN_SHARE_CTRL7F__ON1, _PIN_A5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_7F_PIN_SHARE_CTRL7F__ON1, _PIN_A5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_7F_PIN_SHARE_CTRL7F__ON1, _PIN_A5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E11:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_80_PIN_SHARE_CTRL80__ON1, _PIN_E11_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_80_PIN_SHARE_CTRL80__ON1, _PIN_E11_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_80_PIN_SHARE_CTRL80__ON1, _PIN_E11_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_V4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_81_PIN_SHARE_CTRL81__ON2, _PIN_V4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_81_PIN_SHARE_CTRL81__ON2, _PIN_V4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_81_PIN_SHARE_CTRL81__ON2, _PIN_V4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_U4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON2, _PIN_U4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_G8:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PIN_G8_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_E4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_84_PIN_SHARE_CTRL84__ON1, _PIN_E4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_84_PIN_SHARE_CTRL84__ON1, _PIN_E4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_84_PIN_SHARE_CTRL84__ON1, _PIN_E4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_G7:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_85_PIN_SHARE_CTRL85__ON1, _PIN_G7_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_85_PIN_SHARE_CTRL85__ON1, _PIN_G7_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_85_PIN_SHARE_CTRL85__ON1, _PIN_G7_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A2:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_86_PIN_SHARE_CTRL86__ON1, _PIN_A2_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_86_PIN_SHARE_CTRL86__ON1, _PIN_A2_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_86_PIN_SHARE_CTRL86__ON1, _PIN_A2_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B3:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _PIN_B3_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _PIN_B3_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _PIN_B3_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_B2:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _PIN_B2_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _PIN_B2_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _PIN_B2_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_89_PIN_SHARE_CTRL89__ON1, _PIN_A4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_89_PIN_SHARE_CTRL89__ON1, _PIN_A4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_89_PIN_SHARE_CTRL89__ON1, _PIN_A4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_A3:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_8A_PIN_SHARE_CTRL8A__ON1, _PIN_A3_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_8A_PIN_SHARE_CTRL8A__ON1, _PIN_A3_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_8A_PIN_SHARE_CTRL8A__ON1, _PIN_A3_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_G5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_8B_PIN_SHARE_CTRL8B__ON1, _PIN_G5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_8B_PIN_SHARE_CTRL8B__ON1, _PIN_G5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_8B_PIN_SHARE_CTRL8B__ON1, _PIN_G5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F4:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_8C_PIN_SHARE_CTRL8C__ON1, _PIN_F4_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_8C_PIN_SHARE_CTRL8C__ON1, _PIN_F4_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_8C_PIN_SHARE_CTRL8C__ON1, _PIN_F4_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H5:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_8D_PIN_SHARE_CTRL8D__ON1, _PIN_H5_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_8D_PIN_SHARE_CTRL8D__ON1, _PIN_H5_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_8D_PIN_SHARE_CTRL8D__ON1, _PIN_H5_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F3:

            switch(enumConfigType)
            {
                case _CONFIG_TYPE_GPI:
                    ScalerSetByte(P10_8E_PIN_SHARE_CTRL8E__ON1, _PIN_F3_GPI);
                    break;

                case _CONFIG_TYPE_GPO_PP:
                    ScalerSetByte(P10_8E_PIN_SHARE_CTRL8E__ON1, _PIN_F3_GPO_PP);
                    break;

                case _CONFIG_TYPE_GPO_OD:
                    ScalerSetByte(P10_8E_PIN_SHARE_CTRL8E__ON1, _PIN_F3_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Flash SPI Drive config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustFlashDrive(void)
{
    // Setting Flash SPI SI/SO/CEB Pin Current Control
    ScalerSetBit(P10_E8_PIN_DRIVING_CTRL00__ON3, ~(_BIT7 | _BIT6 | _BIT5), (_FLASH_SI_SO_CEB_DRIVE_CURRENT & 0x07) << 5);

    // Setting Flash SPI Clk Pin Current Control
    ScalerSetBit(P10_E8_PIN_DRIVING_CTRL00__ON3, ~(_BIT4 | _BIT3 | _BIT2), (_FLASH_CLK_DRIVE_CURRENT & 0x07) << 2);
}

//--------------------------------------------------
// Description  : Adjust Flash SPI Slew-Rate Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustFlashSlewRate(void)
{
    // Setting Flash SPI SI/SO/CEB Pin Slew-Rate Control
    ScalerSetBit(P10_A0_PIN_SLEW_RATE_CTRL00__ON3, ~(_BIT7), (_FLASH_SI_SO_CEB_SLEW_RATE_CONTROL & 0x01) << 7);

    // Setting Flash SPI Clk Pin Slew-Rate Control
    ScalerSetBit(P10_A0_PIN_SLEW_RATE_CTRL00__ON3, ~(_BIT6), (_FLASH_CLK_SLEW_RATE_CONTROL & 0x01) << 6);
}

#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
    (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
    (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
//--------------------------------------------------
// Description  : Type-C Get DP Source Power
// Input Value  : Input Port
// Output Value : Type-C AUX PIN Connect
//--------------------------------------------------
bit ScalerPinshareGetTypeCDPSourcePower(EnumInputPort enumInputPort)
{
    EnumTypeCPinCfgType enumPinAssignment = ScalerTypeCRxGetPinAssignment(enumInputPort);
    EnumTypeCOrientation enumTypeCOrientation = ScalerTypeCRxGetOrientation(enumInputPort);

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            // Pin-Share for AUX Setting TBD
            switch(enumPinAssignment)
            {
                case _TYPE_C_PIN_ASSIGNMENT_C:
                case _TYPE_C_PIN_ASSIGNMENT_D:

                    if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
                    {
                        // DP_SINK_ASS_N0_int1M
                        return GET_GPIO_PIN_F4();
                    }
                    else
                    {
                        // DP_SINK_ASS_P0_int1M
                        return GET_GPIO_PIN_G5();
                    }

                case _TYPE_C_PIN_ASSIGNMENT_E:

                    if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
                    {
                        // DP_SINK_ASS_P0_int1M
                        return GET_GPIO_PIN_G5();
                    }
                    else
                    {
                        // DP_SINK_ASS_N0_int1M
                        return GET_GPIO_PIN_F4();
                    }

                case _TYPE_C_PIN_ASSIGNMENT_NONE:

                    return _FALSE;

                default:
                    return _FALSE;
            }
        case _D1_INPUT_PORT:
            switch(enumPinAssignment)
            {
                case _TYPE_C_PIN_ASSIGNMENT_C:
                case _TYPE_C_PIN_ASSIGNMENT_D:

                    if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
                    {
                        // DP_SINK_ASS_N1_int1M
                        return GET_GPIO_PIN_F3();
                    }
                    else
                    {
                        // DP_SINK_ASS_P1_int1M
                        return GET_GPIO_PIN_H5();
                    }

                case _TYPE_C_PIN_ASSIGNMENT_E:

                    if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
                    {
                        // DP_SINK_ASS_P1_int1M
                        return GET_GPIO_PIN_H5();
                    }
                    else
                    {
                        // DP_SINK_ASS_N1_int1M
                        return GET_GPIO_PIN_F3();
                    }

                case _TYPE_C_PIN_ASSIGNMENT_NONE:

                    return _FALSE;

                default:
                    return _FALSE;
            }
        default:
            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Aux Pin-Share and Aux PN Pull High/Low Setting
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRx0TypeCPinAssert(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation)
{
    enumTypeCOrientation = enumTypeCOrientation;

    // Aux Pin-Share Setting
    if(enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        // Pinshare Config : GPI Mode
        ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_GPI);

        // Pinshare Config : GPI Mode
        ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_GPI);
    }
    else
    {
        // Pinshare Config : AUX_P Mode
        ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_DPRX_AUX_P_0);

        // Pinshare Config : AUX_N Mode
        ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_DPRX_AUX_N_0);
    }

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    // Aux PN Pull High/Low Setting
    switch(enumTypeCPinCfgType)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:
        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // AUX-P Pull High
                ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), _BIT2);

                // AUX-N Pull Low
                ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // AUX-P Pull Low
                ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), _BIT3);

                // AUX-N Pull High
                ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), _BIT0);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // AUX-P Pull Low
                ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), _BIT3);

                // AUX-N Pull High
                ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), _BIT0);
            }
            else
            {
                // AUX-P Pull High
                ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), _BIT2);

                // AUX-N Pull Low
                ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), _BIT1);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // AUX-P Pull High/Low Disable
            ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), 0x00);

            // AUX-N Pull High/Low Disable
            ScalerSetBit(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), 0x00);

            break;

        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Aux Pin-Share and Aux PN Pull High/Low Setting
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRx0TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation)
{
    enumTypeCOrientation = enumTypeCOrientation;

    // Aux Pin-Share Setting
    if(enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        // Pinshare Config : GPI Mode
        ScalerSetByte_EXINT(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_GPI);

        // Pinshare Config : GPI Mode
        ScalerSetByte_EXINT(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_GPI);
    }
    else
    {
        // Pinshare Config : AUX_P Mode
        ScalerSetByte_EXINT(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_DPRX_AUX_P_0);

        // Pinshare Config : AUX_N Mode
        ScalerSetByte_EXINT(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_DPRX_AUX_N_0);
    }

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    // Aux PN Pull High/Low Setting
    switch(enumTypeCPinCfgType)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:
        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // AUX-P Pull High
                ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), _BIT2);

                // AUX-N Pull Low
                ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // AUX-P Pull Low
                ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), _BIT3);

                // AUX-N Pull High
                ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), _BIT0);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // AUX-P Pull Low
                ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), _BIT3);

                // AUX-N Pull High
                ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), _BIT0);
            }
            else
            {
                // AUX-P Pull High
                ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), _BIT2);

                // AUX-N Pull Low
                ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), _BIT1);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // AUX-P Pull High/Low Disable
            ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT3 | _BIT2), 0x00);

            // AUX-N Pull High/Low Disable
            ScalerSetBit_EXINT(P10_D6_PIN_PULLUP_CTRL16__ON1, ~(_BIT1 | _BIT0), 0x00);

            break;

        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Aux Pin-Share and Aux PN Pull High/Low Setting
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRx1TypeCPinAssert(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation)
{
    enumTypeCOrientation = enumTypeCOrientation;

    // Aux Pin-Share Setting
    if(enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        // Pinshare Config : GPI Mode
        ScalerSetByte(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_GPI);

        // Pinshare Config : GPI Mode
        ScalerSetByte(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_GPI);
    }
    else
    {
        // Pinshare Config : AUX_P Mode
        ScalerSetByte(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_DPRX_AUX_P_1);

        // Pinshare Config : AUX_N Mode
        ScalerSetByte(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_DPRX_AUX_N_1);
    }

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    // Aux PN Pull High/Low Setting
    switch(enumTypeCPinCfgType)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:
        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // AUX-P Pull High
                ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), _BIT6);

                // AUX-N Pull Low
                ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), _BIT5);
            }
            else
            {
                // AUX-P Pull Low
                ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), _BIT7);

                // AUX-N Pull High
                ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), _BIT4);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // AUX-P Pull Low
                ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), _BIT7);

                // AUX-N Pull High
                ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), _BIT4);
            }
            else
            {
                // AUX-P Pull High
                ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), _BIT6);

                // AUX-N Pull Low
                ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), _BIT5);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // AUX-P Pull High/Low Disable
            ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), 0x00);

            // AUX-N Pull Low/Low Disable
            ScalerSetBit(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), 0x00);

            break;

        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Aux Pin-Share and Aux PN Pull High/Low Setting
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRx1TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation)
{
    enumTypeCOrientation = enumTypeCOrientation;

    // Aux Pin-Share Setting
    if(enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        // Pinshare Config : GPI Mode
        ScalerSetByte_EXINT(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_GPI);

        // Pinshare Config : GPI Mode
        ScalerSetByte_EXINT(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_GPI);
    }
    else
    {
        // Pinshare Config : AUX_P Mode
        ScalerSetByte_EXINT(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_DPRX_AUX_P_1);

        // Pinshare Config : AUX_N Mode
        ScalerSetByte_EXINT(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_DPRX_AUX_N_1);
    }

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    // Aux PN Pull High/Low Setting
    switch(enumTypeCPinCfgType)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:
        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // AUX-P Pull High
                ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), _BIT6);

                // AUX-N Pull Low
                ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), _BIT5);
            }
            else
            {
                // AUX-P Pull Low
                ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), _BIT7);

                // AUX-N Pull High
                ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), _BIT4);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // AUX-P Pull Low
                ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), _BIT7);

                // AUX-N Pull High
                ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), _BIT4);
            }
            else
            {
                // AUX-P Pull High
                ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), _BIT6);

                // AUX-N Pull Low
                ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), _BIT5);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // AUX-P Pull High/Low Disable
            ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT7 | _BIT6), 0x00);

            // AUX-N Pull Low/Low Disable
            ScalerSetBit_EXINT(P10_D7_PIN_PULLUP_CTRL17__ON1, ~(_BIT5 | _BIT4), 0x00);

            break;

        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Aux Pin-Share and Aux PN Pull High/Low Setting
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRx2TypeCPinAssert(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation)
{
    enumTypeCOrientation = enumTypeCOrientation;

    // Aux Pin-Share Setting
    if(enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        // Pinshare Config : GPI Mode
        ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_GPI);

        // Pinshare Config : GPI Mode
        ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_GPI);
    }
    else
    {
        // Pinshare Config : AUX_P Mode
        ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_DPRX_AUX_P_2);

        // Pinshare Config : AUX_N Mode
        ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_DPRX_AUX_N_2);
    }
}

//--------------------------------------------------
// Description  : Aux Pin-Share and Aux PN Pull High/Low Setting
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRx2TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation)
{
    enumTypeCOrientation = enumTypeCOrientation;

    // Aux Pin-Share Setting
    if(enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        // Pinshare Config : GPI Mode
        ScalerSetByte_EXINT(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_GPI);

        // Pinshare Config : GPI Mode
        ScalerSetByte_EXINT(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_GPI);
    }
    else
    {
        // Pinshare Config : AUX_P Mode
        ScalerSetByte_EXINT(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_DPRX_AUX_P_2);

        // Pinshare Config : AUX_N Mode
        ScalerSetByte_EXINT(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_DPRX_AUX_N_2);
    }
}

//--------------------------------------------------
// Description  : PWM UpDatat Sync use of Switch Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinsharePwmUpdSyncSwitch(void)
{
    // Set the PWM UPD Sync Num
    // Set the PIN Orientation
    if(_PIN_H9 == _PIN_H9_PWM_UPD_SYNC_0_1_PP)
    {
        ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_GPO_PP);

#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PIN_INVERT == 0)
        SET_GPIO_PIN_H9(_LOW);
        DELAY_5US();
        SET_GPIO_PIN_H9(_HIGH);
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS != 0)
        DELAY_XUS(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS);
#endif
        SET_GPIO_PIN_H9(_LOW);
#else
        SET_GPIO_PIN_H9(_HIGH);
        DELAY_5US();
        SET_GPIO_PIN_H9(_LOW);
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS != 0)
        DELAY_XUS(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS);
#endif
        SET_GPIO_PIN_H9(_HIGH);
#endif

        ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__ON1, _PIN_H9_PWM_UPD_SYNC_0_1_PP);
    }
    else if(_PIN_H7 == _PIN_H7_PWM_UPD_SYNC_0_0_PP)
    {
        ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_GPO_PP);

#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PIN_INVERT == 0)
        SET_GPIO_PIN_H7(_LOW);
        DELAY_5US();
        SET_GPIO_PIN_H7(_HIGH);
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS != 0)
        DELAY_XUS(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS);
#endif
        SET_GPIO_PIN_H7(_LOW);
#else
        SET_GPIO_PIN_H7(_HIGH);
        DELAY_5US();
        SET_GPIO_PIN_H7(_LOW);
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS != 0)
        DELAY_XUS(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS);
#endif
        SET_GPIO_PIN_H7(_HIGH);
#endif

        ScalerSetByte(P10_74_PIN_SHARE_CTRL74__ON1, _PIN_H7_PWM_UPD_SYNC_0_0_PP);
    }
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Pinshare Hpd Pull Down Setting
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRxHpdPullDownSet(EnumInputPort enumInputPort, bit bEnable)
{
    enumInputPort = enumInputPort;

    switch(enumInputPort)
    {
#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P10_CC_PIN_PULLUP_CTRL0C__ON1, ~(_BIT5 | _BIT4), _BIT5);
            }
            else
            {
                ScalerSetBit(P10_CC_PIN_PULLUP_CTRL0C__ON1, ~(_BIT5 | _BIT4), 0x00);
            }
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P10_CC_PIN_PULLUP_CTRL0C__ON1, ~(_BIT1 | _BIT0), _BIT1);
            }
            else
            {
                ScalerSetBit(P10_CC_PIN_PULLUP_CTRL0C__ON1, ~(_BIT1 | _BIT0), 0x00);
            }
            break;
#endif

        default:
            break;
    }
}
#endif

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Pin GPIO Pinshare Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAudioPinGPIOCheck(void)
{
#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
    static_assert((_PIN_AG23_OFF_REGION == _PIN_AG23_AUDIO_HOUTL) && (_PIN_AE23_OFF_REGION == _PIN_AE23_AUDIO_HOUTR),
                  "Pinshare Setting Should be Set to Audio HPOUT R/L When _DAC_HP_OUTPUT_SUPPORT Support _ON");
#else
    static_assert((_PIN_AG23_OFF_REGION != _PIN_AG23_AUDIO_HOUTL) && (_PIN_AE23_OFF_REGION != _PIN_AE23_AUDIO_HOUTR),
                  "Pinshare Setting Should Not be Set to Audio HPOUT R/L When _DAC_HP_OUTPUT_SUPPORT Support _OFF");
#endif

#if(_LINE_IN_SUPPORT == _ON)
    static_assert((_PIN_AG20_OFF_REGION == _PIN_AG20_LINE_INL) && (_PIN_AF20_OFF_REGION == _PIN_AF20_LINE_INR),
                  "Pinshare Setting Should be Set to Audio LINE_IN R/L When _LINE_IN_SUPPORT Support _ON");
#else
    static_assert((_PIN_AG20_OFF_REGION != _PIN_AG20_LINE_INL) && (_PIN_AF20_OFF_REGION != _PIN_AF20_LINE_INR),
                  "Pinshare Setting Should Not be Set to Audio LINE_IN R/L When _LINE_IN_SUPPORT Support _OFF");
#endif

#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
    static_assert((_PIN_AG22_OFF_REGION == _PIN_AG22_AUDIO_SOUTL) && (_PIN_AF22_OFF_REGION == _PIN_AF22_AUDIO_SOUTR),
                  "Pinshare Setting Should be Set to Audio SPEAKER_OUTPUT R/L When _DAC_SPEAKER_OUTPUT_SUPPORT Support _ON");
#else
    static_assert((_PIN_AG22_OFF_REGION != _PIN_AG22_AUDIO_SOUTL) && (_PIN_AF22_OFF_REGION != _PIN_AF22_AUDIO_SOUTR),
                  "Pinshare Setting Should Not be Set to Audio SPEAKER_OUTPUT R/L When _DAC_SPEAKER_OUTPUT_SUPPORT Support _OFF");
#endif
}
#endif

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
//--------------------------------------------------
// Description  : Type-C 0 Adc Pin GPIO Pinshare Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareTypeC0AdcPinGPIOCheck(void)
{
    // 10-Bit ADC Pinshare Check
#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0)
    static_assert((_PIN_AB5 == _PIN_AB5_10B_ADC_0),
                  "_PIN_10B_ADC_0 pinshare should be switched to _ADC_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1)
    static_assert((_PIN_AB4 == _PIN_AB4_10B_ADC_1),
                  "_PIN_10B_ADC_1 pinshare should be switched to _ADC_1!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2)
    static_assert((_PIN_AA5 == _PIN_AA5_10B_ADC_2),
                  "_PIN_10B_ADC_2 pinshare should be switched to _ADC_2!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3)
    static_assert((_PIN_AA4 == _PIN_AA4_10B_ADC_3),
                  "_PIN_10B_ADC_3 pinshare should be switched to _ADC_3!!!");
#endif

    // LSADC Pinshare Check
#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0)
    static_assert((_PIN_AF12 == _PIN_AF12_A_ADC0_0_0),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_0_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1)
    static_assert((_PIN_AF11 == _PIN_AF11_A_ADC1_0_0),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_0_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2)
    static_assert((_PIN_AF10 == _PIN_AF10_A_ADC2_0_0),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_0_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)
    static_assert((_PIN_AF9 == _PIN_AF9_A_ADC3_0_0),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_0_0!!!");
#endif
}
#endif // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
//--------------------------------------------------
// Description  : Type-C 0 Pmic Pin GPIO Pinshare Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareTypeC0PmicPinGPIOCheck(void)
{
    // 10-Bit ADC Pinshare Check
#if(((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) && ((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) && (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))) ||\
    (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0)
    static_assert((_PIN_AB5 == _PIN_AB5_10B_ADC_0),
                  "_PIN_10B_ADC_0 pinshare should be switched to _ADC_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1)
    static_assert((_PIN_AB4 == _PIN_AB4_10B_ADC_1),
                  "_PIN_10B_ADC_1 pinshare should be switched to _ADC_1!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2)
    static_assert((_PIN_AA5 == _PIN_AA5_10B_ADC_2),
                  "_PIN_10B_ADC_2 pinshare should be switched to _ADC_2!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3)
    static_assert((_PIN_AA4 == _PIN_AA4_10B_ADC_3),
                  "_PIN_10B_ADC_3 pinshare should be switched to _ADC_3!!!");
#endif

#endif // End of #if((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))

    // LSADC Pinshare Check
#if(((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) && ((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3))) ||\
    (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0)
    static_assert((_PIN_AF12 == _PIN_AF12_A_ADC0_0_0),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_0_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1)
    static_assert((_PIN_AF11 == _PIN_AF11_A_ADC1_0_0),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_0_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2)
    static_assert((_PIN_AF10 == _PIN_AF10_A_ADC2_0_0),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_0_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)
    static_assert((_PIN_AF9 == _PIN_AF9_A_ADC3_0_0),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_0_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0)
    static_assert((_PIN_AG12 == _PIN_AG12_A_ADC0_1_0),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_1_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1)
    static_assert((_PIN_AG11 == _PIN_AG11_A_ADC1_1_0),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_1_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2)
    static_assert((_PIN_AG10 == _PIN_AG10_A_ADC2_1_0),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_1_0!!!");
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)
    static_assert((_PIN_AG9 == _PIN_AG9_A_ADC3_1_0),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_1_0!!!");
#endif

#endif // End of #if((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))
}
#endif // End of #if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
//--------------------------------------------------
// Description  : Type-C 1 Adc Pin GPIO Pinshare Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareTypeC1AdcPinGPIOCheck(void)
{
    // 10-Bit ADC Pinshare Check
#if(_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0)
    static_assert((_PIN_AB5 == _PIN_AB5_10B_ADC_0),
                  "_PIN_10B_ADC_0 pinshare should be switched to _ADC_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1)
    static_assert((_PIN_AB4 == _PIN_AB4_10B_ADC_1),
                  "_PIN_10B_ADC_1 pinshare should be switched to _ADC_1!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2)
    static_assert((_PIN_AA5 == _PIN_AA5_10B_ADC_2),
                  "_PIN_10B_ADC_2 pinshare should be switched to _ADC_2!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3)
    static_assert((_PIN_AA4 == _PIN_AA4_10B_ADC_3),
                  "_PIN_10B_ADC_3 pinshare should be switched to _ADC_3!!!");
#endif

    // LSADC Pinshare Check
#if(_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0)
    static_assert((_PIN_AF12 == _PIN_AF12_A_ADC0_0_0),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_0_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1)
    static_assert((_PIN_AF11 == _PIN_AF11_A_ADC1_0_0),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_0_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2)
    static_assert((_PIN_AF10 == _PIN_AF10_A_ADC2_0_0),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_0_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)
    static_assert((_PIN_AF9 == _PIN_AF9_A_ADC3_0_0),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_0_0!!!");
#endif
}
#endif // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
//--------------------------------------------------
// Description  : Type-C 1 Pmic Pin GPIO Pinshare Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareTypeC1PmicPinGPIOCheck(void)
{
    // 10-Bit ADC Pinshare Check
#if(((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) && ((_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) && (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))) ||\
    (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0)
    static_assert((_PIN_AB5 == _PIN_AB5_10B_ADC_0),
                  "_PIN_10B_ADC_0 pinshare should be switched to _ADC_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1)
    static_assert((_PIN_AB4 == _PIN_AB4_10B_ADC_1),
                  "_PIN_10B_ADC_1 pinshare should be switched to _ADC_1!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2)
    static_assert((_PIN_AA5 == _PIN_AA5_10B_ADC_2),
                  "_PIN_10B_ADC_2 pinshare should be switched to _ADC_2!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3)
    static_assert((_PIN_AA4 == _PIN_AA4_10B_ADC_3),
                  "_PIN_10B_ADC_3 pinshare should be switched to _ADC_3!!!");
#endif

#endif // End of #if((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))

    // LSADC Pinshare Check
#if(((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) && ((_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3))) ||\
    (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0)
    static_assert((_PIN_AF12 == _PIN_AF12_A_ADC0_0_0),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_0_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1)
    static_assert((_PIN_AF11 == _PIN_AF11_A_ADC1_0_0),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_0_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2)
    static_assert((_PIN_AF10 == _PIN_AF10_A_ADC2_0_0),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_0_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)
    static_assert((_PIN_AF9 == _PIN_AF9_A_ADC3_0_0),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_0_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0)
    static_assert((_PIN_AG12 == _PIN_AG12_A_ADC0_1_0),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_1_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1)
    static_assert((_PIN_AG11 == _PIN_AG11_A_ADC1_1_0),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_1_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2)
    static_assert((_PIN_AG10 == _PIN_AG10_A_ADC2_1_0),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_1_0!!!");
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)
    static_assert((_PIN_AG9 == _PIN_AG9_A_ADC3_1_0),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_1_0!!!");
#endif

#endif // End of #if((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))
}
#endif // End of #if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)

//--------------------------------------------------
// Description  : Local Power Adc Pin GPIO Pinshare Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareLocPowAdcPinGPIOCheck(void)
{
    // 10-Bit ADC Pinshare Check
#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0)
    static_assert((_PIN_AB5 == _PIN_AB5_10B_ADC_0),
                  "_PIN_10B_ADC_0 pinshare should be switched to _ADC_0!!!");
#endif

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1)
    static_assert((_PIN_AB4 == _PIN_AB4_10B_ADC_1),
                  "_PIN_10B_ADC_1 pinshare should be switched to _ADC_1!!!");
#endif

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2)
    static_assert((_PIN_AA5 == _PIN_AA5_10B_ADC_2),
                  "_PIN_10B_ADC_2 pinshare should be switched to _ADC_2!!!");
#endif

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3)
    static_assert((_PIN_AA4 == _PIN_AA4_10B_ADC_3),
                  "_PIN_10B_ADC_3 pinshare should be switched to _ADC_3!!!");
#endif

    // LSADC Pinshare Check
#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0)
    static_assert((_PIN_AF12 == _PIN_AF12_A_ADC0_0_0),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_0_0!!!");
#endif

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1)
    static_assert((_PIN_AF11 == _PIN_AF11_A_ADC1_0_0),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_0_0!!!");
#endif

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2)
    static_assert((_PIN_AF10 == _PIN_AF10_A_ADC2_0_0),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_0_0!!!");
#endif

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)
    static_assert((_PIN_AF9 == _PIN_AF9_A_ADC3_0_0),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_0_0!!!");
#endif
}

#endif // End of #if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
//--------------------------------------------------
// Description  : LSADC Pin GPIO Pinshare Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdcDetectIntPinGPIOCheck(void)
{
    static_assert(((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) || (_PIN_AF12 == _PIN_AF12_A_ADC0_0_0)),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_0_0!!!");

    static_assert(((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_1) || (_PIN_AF11 == _PIN_AF11_A_ADC1_0_0)),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_0_0!!!");

    static_assert(((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_2) || (_PIN_AF10 == _PIN_AF10_A_ADC2_0_0)),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_0_0!!!");

    static_assert(((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3) || (_PIN_AF9 == _PIN_AF9_A_ADC3_0_0)),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_0_0!!!");

    static_assert(((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) || (_PIN_AG12 == _PIN_AG12_A_ADC0_1_0)),
                  "_PIN_LSADC_0 pinshare should be switched to _ADC0_1_0!!!");

    static_assert(((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_1) || (_PIN_AG11 == _PIN_AG11_A_ADC1_1_0)),
                  "_PIN_LSADC_1 pinshare should be switched to _ADC1_1_0!!!");

    static_assert(((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_2) || (_PIN_AG10 == _PIN_AG10_A_ADC2_1_0)),
                  "_PIN_LSADC_2 pinshare should be switched to _ADC2_1_0!!!");

    static_assert(((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3) || (_PIN_AG9 == _PIN_AG9_A_ADC3_1_0)),
                  "_PIN_LSADC_3 pinshare should be switched to _ADC3_1_0!!!");
}
#endif
#endif

//--------------------------------------------------
// Description  : HW_IIC_1 Pin GPIO Pinshare Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareHWIIC1PinGPIOCheck(void)
{
    static_assert(((_PIN_D5 != _PIN_D5_IICSCL_1_0) &&
                   (_PIN_D4 != _PIN_D4_IICSDA_1_0) &&
                   (_PIN_D3 != _PIN_D3_IICSCL_1_1) &&
                   (_PIN_H7 != _PIN_H7_IICSDA_1_1) &&
                   (_PIN_J9 != _PIN_J9_IICSCL_1_2) &&
                   (_PIN_E5 != _PIN_E5_IICSDA_1_2) &&
                   (_PIN_D13 != _PIN_D13_IICSCL_1_3) &&
                   (_PIN_H9 != _PIN_H9_IICSDA_1_3) &&
                   (_PIN_AE26_OFF_REGION != _PIN_AE26_IICSCL_1_4) &&
                   (_PIN_AD26_OFF_REGION != _PIN_AD26_IICSDA_1_4) &&
                   (_PIN_AA23_OFF_REGION != _PIN_AA23_IICSCL_1_5) &&
                   (_PIN_Y24_OFF_REGION != _PIN_Y24_IICSDA_1_5) &&
                   (_PIN_W23_OFF_REGION != _PIN_W23_IICSCL_1_6) &&
                   (_PIN_W22_OFF_REGION != _PIN_W22_IICSDA_1_6) &&
                   (_PIN_U4 != _PIN_U4_IICSCL_1_7) &&
                   (_PIN_G8 != _PIN_G8_IICSDA_1_7)),
                  "Pinshare HW_IIC_1 should be switched to HW_IIC_0!!!");
}

#if(_DP_SUPPORT == _ON)
#if(_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx Pin Share Setting
// Input Value  : enumInputPort
//                enumPowerTarget
// Output Value : None
//--------------------------------------------------
void ScalerPinshareDpAuxRxConfig(EnumInputPort enumInputPort, EnumPowerTarget enumPowerTarget)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            if(enumPowerTarget == _POWER_ON)
            {
                // Pinshare Config : AUX_P Mode
                ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_DPRX_AUX_P_0);

                // Pinshare Config : AUX_N Mode
                ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_DPRX_AUX_N_0);
            }
            else
            {
                // Pinshare Config : GPI Mode
                ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON2, _PIN_W4_GPI);

                // Pinshare Config : GPI Mode
                ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON2, _PIN_W5_GPI);
            }
            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            if(enumPowerTarget == _POWER_ON)
            {
                // Pinshare Config : AUX_P Mode
                ScalerSetByte(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_DPRX_AUX_P_1);

                // Pinshare Config : AUX_N Mode
                ScalerSetByte(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_DPRX_AUX_N_1);
            }
            else
            {
                // Pinshare Config : GPI Mode
                ScalerSetByte(P10_68_PIN_SHARE_CTRL68__ON1, _PIN_F11_GPI);

                // Pinshare Config : GPI Mode
                ScalerSetByte(P10_69_PIN_SHARE_CTRL69__ON1, _PIN_F12_GPI);
            }
            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            if(enumPowerTarget == _POWER_ON)
            {
                // Pinshare Config : AUX_P Mode
                ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_DPRX_AUX_P_2);

                // Pinshare Config : AUX_N Mode
                ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_DPRX_AUX_N_2);
            }
            else
            {
                // Pinshare Config : GPI Mode
                ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__ON1, _PIN_E13_GPI);

                // Pinshare Config : GPI Mode
                ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__ON1, _PIN_F13_GPI);
            }
            break;
#endif
        default:
            break;
    }
}
#endif
#endif
