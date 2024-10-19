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
// ID Code      : RL6829_Series_IOToggle.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_IO_TOGGLE_TEST_SUPPORT == _ON)
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#define _INPUT                                  0
#define _PUSH_PULL                              1
#define _OPEN_DRAIN                             2

// IO Toggle TEST Config
#define _IO_TEST_A                              0
#define _IO_TEST_B                              1
#define _IO_TEST_OD                             2

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_uc_IO_TEST_RESULT00 = 0xFF;
BYTE g_uc_IO_TEST_RESULT01 = 0xFF;
BYTE g_uc_IO_TEST_RESULT02 = 0xFF;
BYTE g_uc_IO_TEST_RESULT03 = 0xFF;
BYTE g_uc_IO_TEST_RESULT04 = 0xFF;
BYTE g_uc_IO_TEST_RESULT05 = 0xFF;
BYTE g_uc_IO_TEST_RESULT06 = 0xFF;
BYTE g_uc_IO_TEST_RESULT07 = 0xFF;
BYTE g_uc_IO_TEST_RESULT08 = 0xFF;
BYTE g_uc_IO_TEST_RESULT09 = 0xFF;
BYTE g_uc_IO_TEST_RESULT0A = 0xFF;
BYTE g_uc_IO_TEST_RESULT0B = 0xFF;
BYTE g_uc_IO_TEST_RESULT0C = 0x1F;
BYTE g_uc_IO_TEST_RESULT10 = 0xFF;
BYTE g_uc_IO_TEST_RESULT11 = 0xFF;
BYTE g_uc_IO_TEST_RESULT12 = 0xFF;
BYTE g_uc_IO_TEST_RESULT13 = 0xFF;
BYTE g_uc_IO_TEST_RESULT14 = 0xFF;
BYTE g_uc_IO_TEST_RESULT15 = 0xFF;
BYTE g_uc_IO_TEST_RESULT16 = 0xFF;
BYTE g_uc_IO_TEST_RESULT17 = 0x01;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void IOToggleTest(void);
void ScalerIOToggleIOConfigInitial(void);
void ScalerIOToggleLvdsInitial(void);
void ScalerIOTogglePushPullInitial(void);
void ScalerIOToggleIOConfigTestAtoB(void);
void ScalerIOToggleIOConfigTestBtoA(void);
void ScalerIOToggleIOCheckAtoB(void);
void ScalerIOToggleIOCheckBtoA(void);
void ScalerIOToggleIOTESTModus(BYTE *pucIOTestAPortNum, BYTE ucIOTestApin, BYTE *pucIOTestBPortNum, BYTE ucIOTestBpin, BYTE *pucResult, BYTE ucNum, BYTE ucIOtype);
void ScalerIOToggleXFRtoXFRTest(BYTE *pucIOTestAaddr, BYTE *pucIOTestBaddr, BYTE *pucResult, BYTE ucNum, BYTE ucIOtype);
void ScalerIOToggleIOPullUp(void);
void ScalerIOToggleIOPullDown(void);
void ScalerIOToggleSetLED(void);
void ScalerIOToggleSetDDC(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : GPIO IO toggle verification
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void IOToggleTest(void)
{
    DebugMessageAutoTest("5. IO Test Start", 0x00);

    // Initial: Set All GPIO As GPI Config
    ScalerIOToggleIOConfigInitial();

    // Set LVDS Enviroment
    ScalerIOToggleLvdsInitial();

    // Disable pull-up or pull-down
    ScalerIOTogglePushPullInitial();

    ScalerIOToggleIOConfigTestAtoB();
    ScalerIOToggleIOCheckAtoB();

    ScalerIOToggleIOConfigTestBtoA();
    ScalerIOToggleIOCheckBtoA();

    // Set All GPIO As GPI Config
    ScalerIOToggleIOConfigInitial();

    // Display LED Light
    ScalerIOToggleSetLED();


    // Enable VGA Cable DDC Function
    ScalerIOToggleSetDDC();

    DebugMessageAutoTest("5. =IIC setting compeleted=", 0x00);
    DebugMessageAutoTest("5. =====Result00======", g_uc_IO_TEST_RESULT00);
    DebugMessageAutoTest("5. =====Result01======", g_uc_IO_TEST_RESULT01);
    DebugMessageAutoTest("5. =====Result02======", g_uc_IO_TEST_RESULT02);
    DebugMessageAutoTest("5. =====Result03======", g_uc_IO_TEST_RESULT03);
    DebugMessageAutoTest("5. =====Result04======", g_uc_IO_TEST_RESULT04);
    DebugMessageAutoTest("5. =====Result05======", g_uc_IO_TEST_RESULT05);
    DebugMessageAutoTest("5. =====Result06======", g_uc_IO_TEST_RESULT06);
    DebugMessageAutoTest("5. =====Result07======", g_uc_IO_TEST_RESULT07);
    DebugMessageAutoTest("5. =====Result08======", g_uc_IO_TEST_RESULT08);
    DebugMessageAutoTest("5. =====Result09======", g_uc_IO_TEST_RESULT09);
    DebugMessageAutoTest("5. =====Result0A======", g_uc_IO_TEST_RESULT0A);
    DebugMessageAutoTest("5. =====Result0B======", g_uc_IO_TEST_RESULT0B);
    DebugMessageAutoTest("5. =====Result0C======", g_uc_IO_TEST_RESULT0C);

    DebugMessageAutoTest("5. =====Result10======", g_uc_IO_TEST_RESULT10);
    DebugMessageAutoTest("5. =====Result11======", g_uc_IO_TEST_RESULT11);
    DebugMessageAutoTest("5. =====Result12======", g_uc_IO_TEST_RESULT12);
    DebugMessageAutoTest("5. =====Result13======", g_uc_IO_TEST_RESULT13);
    DebugMessageAutoTest("5. =====Result14======", g_uc_IO_TEST_RESULT14);
    DebugMessageAutoTest("5. =====Result15======", g_uc_IO_TEST_RESULT15);
    DebugMessageAutoTest("5. =====Result16======", g_uc_IO_TEST_RESULT16);
    DebugMessageAutoTest("5. =====Result17======", g_uc_IO_TEST_RESULT17);

    if((g_uc_IO_TEST_RESULT00 | g_uc_IO_TEST_RESULT01 | g_uc_IO_TEST_RESULT02 |
        g_uc_IO_TEST_RESULT03 | g_uc_IO_TEST_RESULT04 | g_uc_IO_TEST_RESULT05 |
        g_uc_IO_TEST_RESULT06 | g_uc_IO_TEST_RESULT07 | g_uc_IO_TEST_RESULT08 |
        g_uc_IO_TEST_RESULT09 | g_uc_IO_TEST_RESULT0A | g_uc_IO_TEST_RESULT0B |
        g_uc_IO_TEST_RESULT0C |
        g_uc_IO_TEST_RESULT10 | g_uc_IO_TEST_RESULT11 | g_uc_IO_TEST_RESULT12 |
        g_uc_IO_TEST_RESULT13 | g_uc_IO_TEST_RESULT14 | g_uc_IO_TEST_RESULT15 |
        g_uc_IO_TEST_RESULT16 | g_uc_IO_TEST_RESULT17) == 0x00)
    {
        DebugMessageAutoTest("5. ======PASS=======", 0x00);
        while(1)
        {
            PCB_LED_ON();
            ScalerTimerDelayXms(10);
            ScalerDebug();
        }
    }
    else
    {
        DebugMessageAutoTest("5. ======FAIL=======", 0x00);
        while(1)
        {
            PCB_LED_ON();
            ScalerTimerDelayXms(100);
            PCB_LED_OFF();
            ScalerTimerDelayXms(100);
            ScalerDebug();
        }
    }
}


//--------------------------------------------------
// Description  : Pinshare Settings for GPIO Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleIOConfigInitial(void)
{
    // Set A Group
    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _INPUT);
    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, _INPUT);
    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON1, _INPUT);
    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON1, _INPUT);
    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON1, _INPUT);
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON1, _INPUT);
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON1, _INPUT);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON1, _INPUT);
    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON1, _INPUT);
    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON1, _INPUT);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON1, _INPUT);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, _INPUT);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON2, _INPUT);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON2, _INPUT);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__ON2, _INPUT);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL1E__ON2, _INPUT);
    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__ON2, _INPUT);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__ON2, _INPUT);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__ON2, _INPUT);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__ON2, _INPUT);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__ON2, _INPUT);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__ON2, _INPUT);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__ON2, _INPUT);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _INPUT);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__ON4, _INPUT);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON4, _INPUT);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__OFF2, _INPUT);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL36__OFF2, _INPUT);
    ScalerSetByte(P10_38_PIN_SHARE_CTRL38__OFF2, _INPUT);
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL3A__OFF2, _INPUT);
    ScalerSetByte(P10_68_PIN_SHARE_CTRL68__OFF1, _INPUT);
    ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__OFF1, _INPUT);
    ScalerSetByte(P10_6C_PIN_SHARE_CTRL6C__OFF1, _INPUT);
    ScalerSetByte(P10_6E_PIN_SHARE_CTRL6E__OFF1, _INPUT);
    ScalerSetByte(P10_70_PIN_SHARE_CTRL70__OFF2, _INPUT);
    ScalerSetByte(P10_72_PIN_SHARE_CTRL72__OFF2, _INPUT);
    ScalerSetByte(P10_74_PIN_SHARE_CTRL74__OFF2, _INPUT);
    ScalerSetByte(P10_76_PIN_SHARE_CTRL76__OFF2, _INPUT);
    ScalerSetByte(P10_78_PIN_SHARE_CTRL78__OFF2, _INPUT);
    ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__OFF2, _INPUT);
    ScalerSetByte(P10_7C_PIN_SHARE_CTRL7C__OFF2, _INPUT);
    ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__OFF2, _INPUT);
    ScalerSetByte(P10_80_PIN_SHARE_CTRL80__OFF2, _INPUT);
    ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON1, _INPUT);
    ScalerSetByte(P10_84_PIN_SHARE_CTRL84__ON1, _INPUT);
    ScalerSetByte(P10_86_PIN_SHARE_CTRL86__ON1, _INPUT);
    ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _INPUT);
    ScalerSetByte(P10_8A_PIN_SHARE_CTRL8A__ON1, _INPUT);
    ScalerSetByte(P10_8C_PIN_SHARE_CTRL8C__ON1, _INPUT);
    ScalerSetByte(P10_8E_PIN_SHARE_CTRL8E__ON1, _INPUT);
    ScalerSetByte(P10_90_PIN_SHARE_CTRL90__ON1, _INPUT);
    ScalerSetByte(P10_93_PIN_SHARE_CTRL93__ON1, _INPUT);
    ScalerSetByte(P10_94_PIN_SHARE_CTRL94__ON1, _INPUT);
    ScalerSetByte(P10_96_PIN_SHARE_CTRL96__ON1, _INPUT);
    ScalerSetByte(P10_98_PIN_SHARE_CTRL98__ON1, _INPUT);
    ScalerSetByte(P10_9A_PIN_SHARE_CTRL9A__ON1, _INPUT);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _INPUT);

    // Set B Group
    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _INPUT);
    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _INPUT);
    ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON1, _INPUT);
    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON1, _INPUT);
    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON1, _INPUT);
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON1, _INPUT);
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON1, _INPUT);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON1, _INPUT);
    ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON1, _INPUT);
    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON1, _INPUT);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON1, _INPUT);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON1, _INPUT);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON2, _INPUT);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__ON2, _INPUT);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__ON2, _INPUT);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__ON2, _INPUT);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__ON2, _INPUT);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__ON2, _INPUT);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__ON2, _INPUT);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__ON2, _INPUT);
    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__ON2, _INPUT);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__ON2, _INPUT);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__ON2, _INPUT);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _INPUT);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__ON4, _INPUT);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__ON4, _INPUT);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL35__OFF2, _INPUT);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL37__OFF2, _INPUT);
    ScalerSetByte(P10_39_PIN_SHARE_CTRL39__OFF2, _INPUT);
    ScalerSetByte(P10_67_PIN_SHARE_CTRL67__OFF1, _INPUT);
    ScalerSetByte(P10_69_PIN_SHARE_CTRL69__OFF1, _INPUT);
    ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__OFF1, _INPUT);
    ScalerSetByte(P10_6D_PIN_SHARE_CTRL6D__OFF1, _INPUT);
    ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__OFF2, _INPUT);
    ScalerSetByte(P10_71_PIN_SHARE_CTRL71__OFF2, _INPUT);
    ScalerSetByte(P10_73_PIN_SHARE_CTRL73__OFF2, _INPUT);
    ScalerSetByte(P10_75_PIN_SHARE_CTRL75__OFF2, _INPUT);
    ScalerSetByte(P10_77_PIN_SHARE_CTRL77__OFF2, _INPUT);
    ScalerSetByte(P10_79_PIN_SHARE_CTRL79__OFF2, _INPUT);
    ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__OFF2, _INPUT);
    ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__OFF2, _INPUT);
    ScalerSetByte(P10_7F_PIN_SHARE_CTRL7F__OFF2, _INPUT);
    ScalerSetByte(P10_81_PIN_SHARE_CTRL81__ON1, _INPUT);
    ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _INPUT);
    ScalerSetByte(P10_85_PIN_SHARE_CTRL85__ON1, _INPUT);
    ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _INPUT);
    ScalerSetByte(P10_89_PIN_SHARE_CTRL89__ON1, _INPUT);
    ScalerSetByte(P10_8B_PIN_SHARE_CTRL8B__ON1, _INPUT);
    ScalerSetByte(P10_8D_PIN_SHARE_CTRL8D__ON1, _INPUT);
    ScalerSetByte(P10_8F_PIN_SHARE_CTRL8F__ON1, _INPUT);
    ScalerSetByte(P10_91_PIN_SHARE_CTRL91__ON1, _INPUT);
    ScalerSetByte(P10_92_PIN_SHARE_CTRL92__ON1, _INPUT);
    ScalerSetByte(P10_95_PIN_SHARE_CTRL95__ON1, _INPUT);
    ScalerSetByte(P10_97_PIN_SHARE_CTRL97__ON1, _INPUT);
    ScalerSetByte(P10_99_PIN_SHARE_CTRL99__ON1, _INPUT);
    ScalerSetByte(P10_9B_PIN_SHARE_CTRL9B__ON1, _INPUT);
    ScalerSetByte(P10_9D_PIN_SHARE_CTRL9D__ON1, _INPUT);
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL3B__OFF1, _INPUT + 1);
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL3D__OFF1, _INPUT + 1);
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL3F__OFF1, _INPUT + 1);
    ScalerSetByte(P10_41_PIN_SHARE_CTRL41__OFF1, _INPUT + 1);
    ScalerSetByte(P10_43_PIN_SHARE_CTRL43__OFF1, _INPUT + 1);
    ScalerSetByte(P10_45_PIN_SHARE_CTRL45__OFF1, _INPUT + 1);
    ScalerSetByte(P10_47_PIN_SHARE_CTRL47__OFF1, _INPUT + 1);
    ScalerSetByte(P10_49_PIN_SHARE_CTRL49__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4B_PIN_SHARE_CTRL4B__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4D_PIN_SHARE_CTRL4D__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4F_PIN_SHARE_CTRL4F__OFF1, _INPUT + 1);
    ScalerSetByte(P10_51_PIN_SHARE_CTRL51__OFF1, _INPUT + 1);
    ScalerSetByte(P10_53_PIN_SHARE_CTRL53__OFF1, _INPUT + 1);
    ScalerSetByte(P10_55_PIN_SHARE_CTRL55__OFF1, _INPUT + 1);
    ScalerSetByte(P10_57_PIN_SHARE_CTRL57__OFF1, _INPUT + 1);
    ScalerSetByte(P10_59_PIN_SHARE_CTRL59__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5B_PIN_SHARE_CTRL5B__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5D_PIN_SHARE_CTRL5D__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5F_PIN_SHARE_CTRL5F__OFF1, _INPUT + 1);
    ScalerSetByte(P10_61_PIN_SHARE_CTRL61__OFF1, _INPUT + 1);
    ScalerSetByte(P10_63_PIN_SHARE_CTRL63__OFF1, _INPUT + 1);
    ScalerSetByte(P10_65_PIN_SHARE_CTRL65__OFF1, _INPUT + 1);
    ScalerSetByte(P10_66_PIN_SHARE_CTRL66__OFF1, _INPUT + 1);
    ScalerSetByte(P10_3C_PIN_SHARE_CTRL3C__OFF1, _INPUT + 1);
    ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__OFF1, _INPUT + 1);
    ScalerSetByte(P10_40_PIN_SHARE_CTRL40__OFF1, _INPUT + 1);
    ScalerSetByte(P10_42_PIN_SHARE_CTRL42__OFF1, _INPUT + 1);
    ScalerSetByte(P10_44_PIN_SHARE_CTRL44__OFF1, _INPUT + 1);
    ScalerSetByte(P10_46_PIN_SHARE_CTRL46__OFF1, _INPUT + 1);
    ScalerSetByte(P10_48_PIN_SHARE_CTRL48__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4A_PIN_SHARE_CTRL4A__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4C_PIN_SHARE_CTRL4C__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4E_PIN_SHARE_CTRL4E__OFF1, _INPUT + 1);
    ScalerSetByte(P10_50_PIN_SHARE_CTRL50__OFF1, _INPUT + 1);
    ScalerSetByte(P10_52_PIN_SHARE_CTRL52__OFF1, _INPUT + 1);
    ScalerSetByte(P10_54_PIN_SHARE_CTRL54__OFF1, _INPUT + 1);
    ScalerSetByte(P10_56_PIN_SHARE_CTRL56__OFF1, _INPUT + 1);
    ScalerSetByte(P10_58_PIN_SHARE_CTRL58__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5A_PIN_SHARE_CTRL5A__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5C_PIN_SHARE_CTRL5C__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5E_PIN_SHARE_CTRL5E__OFF1, _INPUT + 1);
    ScalerSetByte(P10_60_PIN_SHARE_CTRL60__OFF1, _INPUT + 1);
    ScalerSetByte(P10_62_PIN_SHARE_CTRL62__OFF1, _INPUT + 1);
    ScalerSetByte(P10_64_PIN_SHARE_CTRL64__OFF1, _INPUT + 1);
}

//--------------------------------------------------
// Description  : Pinshare Settings for LVDS Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleLvdsInitial(void)
{
    // Set LVDS: TTL type
    ScalerSetByte(P39_00_DISP_TYPE, 0x00);

    // Enable LVDS Power
    ScalerSetByte(P15_00_LVDS_COMMON_AB_CTRL0, 0xE0);
    ScalerSetByte(P55_00_LVDS_COMMON_AB_CTRL0, 0xE0);

    // Set LVDS: Diable Pull Down
    ScalerSetByte(P15_26_LVDS_PORTA_CTRL6, 0x00);
    ScalerSetByte(P15_36_LVDS_PORTB_CTRL6, 0x00);
    ScalerSetByte(P55_26_LVDS_PORTA_CTRL6, 0x00);
    ScalerSetByte(P55_36_LVDS_PORTB_CTRL6, 0x00);
}

//--------------------------------------------------
// Description  : Pinshare Settings PushPull Ajust Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOTogglePushPullInitial(void)
{
    // Set Pull up/down disable: D6[1:0]/D7[7:6]/D9[7:4]
    ScalerSetByte(P10_D6_PIN_PULLUP_CTRL16__ON1, 0x00);
    ScalerSetByte(P10_D7_PIN_PULLUP_CTRL17__ON1, 0x00);
    ScalerSetByte(P10_D9_PIN_PULLUP_CTRL19__ON1, 0x00);
}

//--------------------------------------------------
// Description  : Pinshare Settings A for IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleIOConfigTestAtoB(void)
{
    // Set A Group
    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PUSH_PULL);
    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, _PUSH_PULL);
    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON1, _PUSH_PULL);
    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON1, _PUSH_PULL);
    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON1, _PUSH_PULL);
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON1, _PUSH_PULL);
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON1, _PUSH_PULL);
    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON1, _PUSH_PULL);
    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON1, _PUSH_PULL);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON1, _PUSH_PULL);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, _PUSH_PULL);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON2, _PUSH_PULL);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON2, _PUSH_PULL);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__ON2, _PUSH_PULL);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL1E__ON2, _PUSH_PULL);
    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__ON2, _PUSH_PULL);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__ON2, _PUSH_PULL);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__ON2, _PUSH_PULL);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__ON2, _PUSH_PULL);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__ON2, _PUSH_PULL);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__ON2, _PUSH_PULL);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__ON2, _PUSH_PULL);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__ON4, _PUSH_PULL);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON4, _PUSH_PULL);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL36__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_38_PIN_SHARE_CTRL38__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL3A__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_68_PIN_SHARE_CTRL68__OFF1, _PUSH_PULL);
    ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__OFF1, _PUSH_PULL);
    ScalerSetByte(P10_6C_PIN_SHARE_CTRL6C__OFF1, _PUSH_PULL);
    ScalerSetByte(P10_6E_PIN_SHARE_CTRL6E__OFF1, _PUSH_PULL);
    ScalerSetByte(P10_70_PIN_SHARE_CTRL70__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_72_PIN_SHARE_CTRL72__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_74_PIN_SHARE_CTRL74__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_76_PIN_SHARE_CTRL76__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_78_PIN_SHARE_CTRL78__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_7C_PIN_SHARE_CTRL7C__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_80_PIN_SHARE_CTRL80__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON1, _PUSH_PULL);
    ScalerSetByte(P10_84_PIN_SHARE_CTRL84__ON1, _PUSH_PULL);
    ScalerSetByte(P10_86_PIN_SHARE_CTRL86__ON1, _PUSH_PULL);
    ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _PUSH_PULL);
    ScalerSetByte(P10_8A_PIN_SHARE_CTRL8A__ON1, _PUSH_PULL);
    ScalerSetByte(P10_8C_PIN_SHARE_CTRL8C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_8E_PIN_SHARE_CTRL8E__ON1, _PUSH_PULL);
    ScalerSetByte(P10_90_PIN_SHARE_CTRL90__ON1, _PUSH_PULL);
    ScalerSetByte(P10_93_PIN_SHARE_CTRL93__ON1, _PUSH_PULL);
    ScalerSetByte(P10_94_PIN_SHARE_CTRL94__ON1, _PUSH_PULL);
    ScalerSetByte(P10_96_PIN_SHARE_CTRL96__ON1, _PUSH_PULL);
    ScalerSetByte(P10_98_PIN_SHARE_CTRL98__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9A_PIN_SHARE_CTRL9A__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _PUSH_PULL);


    // Set B Group
    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _INPUT);
    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _INPUT);
    ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON1, _INPUT);
    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON1, _INPUT);
    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON1, _INPUT);
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON1, _INPUT);
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON1, _INPUT);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON1, _INPUT);
    ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON1, _INPUT);
    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON1, _INPUT);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON1, _INPUT);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON1, _INPUT);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON2, _INPUT);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__ON2, _INPUT);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__ON2, _INPUT);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__ON2, _INPUT);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__ON2, _INPUT);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__ON2, _INPUT);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__ON2, _INPUT);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__ON2, _INPUT);
    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__ON2, _INPUT);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__ON2, _INPUT);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__ON2, _INPUT);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _INPUT);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__ON4, _INPUT);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__ON4, _INPUT);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL35__OFF2, _INPUT);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL37__OFF2, _INPUT);
    ScalerSetByte(P10_39_PIN_SHARE_CTRL39__OFF2, _INPUT);
    ScalerSetByte(P10_67_PIN_SHARE_CTRL67__OFF1, _INPUT);
    ScalerSetByte(P10_69_PIN_SHARE_CTRL69__OFF1, _INPUT);
    ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__OFF1, _INPUT);
    ScalerSetByte(P10_6D_PIN_SHARE_CTRL6D__OFF1, _INPUT);
    ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__OFF2, _INPUT);
    ScalerSetByte(P10_71_PIN_SHARE_CTRL71__OFF2, _INPUT);
    ScalerSetByte(P10_73_PIN_SHARE_CTRL73__OFF2, _INPUT);
    ScalerSetByte(P10_75_PIN_SHARE_CTRL75__OFF2, _INPUT);
    ScalerSetByte(P10_77_PIN_SHARE_CTRL77__OFF2, _INPUT);
    ScalerSetByte(P10_79_PIN_SHARE_CTRL79__OFF2, _INPUT);
    ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__OFF2, _INPUT);
    ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__OFF2, _INPUT);
    ScalerSetByte(P10_7F_PIN_SHARE_CTRL7F__OFF2, _INPUT);
    ScalerSetByte(P10_81_PIN_SHARE_CTRL81__ON1, _INPUT);
    ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _INPUT);
    ScalerSetByte(P10_85_PIN_SHARE_CTRL85__ON1, _INPUT);
    ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _INPUT);
    ScalerSetByte(P10_89_PIN_SHARE_CTRL89__ON1, _INPUT);
    ScalerSetByte(P10_8B_PIN_SHARE_CTRL8B__ON1, _INPUT);
    ScalerSetByte(P10_8D_PIN_SHARE_CTRL8D__ON1, _INPUT);
    ScalerSetByte(P10_8F_PIN_SHARE_CTRL8F__ON1, _INPUT);
    ScalerSetByte(P10_91_PIN_SHARE_CTRL91__ON1, _INPUT);
    ScalerSetByte(P10_92_PIN_SHARE_CTRL92__ON1, _INPUT);
    ScalerSetByte(P10_95_PIN_SHARE_CTRL95__ON1, _INPUT);
    ScalerSetByte(P10_97_PIN_SHARE_CTRL97__ON1, _INPUT);
    ScalerSetByte(P10_99_PIN_SHARE_CTRL99__ON1, _INPUT);
    ScalerSetByte(P10_9B_PIN_SHARE_CTRL9B__ON1, _INPUT);
    ScalerSetByte(P10_9D_PIN_SHARE_CTRL9D__ON1, _INPUT);
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL3B__OFF1, _INPUT + 1);
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL3D__OFF1, _INPUT + 1);
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL3F__OFF1, _INPUT + 1);
    ScalerSetByte(P10_41_PIN_SHARE_CTRL41__OFF1, _INPUT + 1);
    ScalerSetByte(P10_43_PIN_SHARE_CTRL43__OFF1, _INPUT + 1);
    ScalerSetByte(P10_45_PIN_SHARE_CTRL45__OFF1, _INPUT + 1);
    ScalerSetByte(P10_47_PIN_SHARE_CTRL47__OFF1, _INPUT + 1);
    ScalerSetByte(P10_49_PIN_SHARE_CTRL49__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4B_PIN_SHARE_CTRL4B__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4D_PIN_SHARE_CTRL4D__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4F_PIN_SHARE_CTRL4F__OFF1, _INPUT + 1);
    ScalerSetByte(P10_51_PIN_SHARE_CTRL51__OFF1, _INPUT + 1);
    ScalerSetByte(P10_53_PIN_SHARE_CTRL53__OFF1, _INPUT + 1);
    ScalerSetByte(P10_55_PIN_SHARE_CTRL55__OFF1, _INPUT + 1);
    ScalerSetByte(P10_57_PIN_SHARE_CTRL57__OFF1, _INPUT + 1);
    ScalerSetByte(P10_59_PIN_SHARE_CTRL59__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5B_PIN_SHARE_CTRL5B__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5D_PIN_SHARE_CTRL5D__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5F_PIN_SHARE_CTRL5F__OFF1, _INPUT + 1);
    ScalerSetByte(P10_61_PIN_SHARE_CTRL61__OFF1, _INPUT + 1);
    ScalerSetByte(P10_63_PIN_SHARE_CTRL63__OFF1, _INPUT + 1);
    ScalerSetByte(P10_65_PIN_SHARE_CTRL65__OFF1, _INPUT + 1);
    ScalerSetByte(P10_66_PIN_SHARE_CTRL66__OFF1, _INPUT + 1);
    ScalerSetByte(P10_3C_PIN_SHARE_CTRL3C__OFF1, _INPUT + 1);
    ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__OFF1, _INPUT + 1);
    ScalerSetByte(P10_40_PIN_SHARE_CTRL40__OFF1, _INPUT + 1);
    ScalerSetByte(P10_42_PIN_SHARE_CTRL42__OFF1, _INPUT + 1);
    ScalerSetByte(P10_44_PIN_SHARE_CTRL44__OFF1, _INPUT + 1);
    ScalerSetByte(P10_46_PIN_SHARE_CTRL46__OFF1, _INPUT + 1);
    ScalerSetByte(P10_48_PIN_SHARE_CTRL48__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4A_PIN_SHARE_CTRL4A__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4C_PIN_SHARE_CTRL4C__OFF1, _INPUT + 1);
    ScalerSetByte(P10_4E_PIN_SHARE_CTRL4E__OFF1, _INPUT + 1);
    ScalerSetByte(P10_50_PIN_SHARE_CTRL50__OFF1, _INPUT + 1);
    ScalerSetByte(P10_52_PIN_SHARE_CTRL52__OFF1, _INPUT + 1);
    ScalerSetByte(P10_54_PIN_SHARE_CTRL54__OFF1, _INPUT + 1);
    ScalerSetByte(P10_56_PIN_SHARE_CTRL56__OFF1, _INPUT + 1);
    ScalerSetByte(P10_58_PIN_SHARE_CTRL58__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5A_PIN_SHARE_CTRL5A__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5C_PIN_SHARE_CTRL5C__OFF1, _INPUT + 1);
    ScalerSetByte(P10_5E_PIN_SHARE_CTRL5E__OFF1, _INPUT + 1);
    ScalerSetByte(P10_60_PIN_SHARE_CTRL60__OFF1, _INPUT + 1);
    ScalerSetByte(P10_62_PIN_SHARE_CTRL62__OFF1, _INPUT + 1);
    ScalerSetByte(P10_64_PIN_SHARE_CTRL64__OFF1, _INPUT + 1);
}

//--------------------------------------------------
// Description  : Pinshare Settings B for IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleIOConfigTestBtoA(void)
{
    // Set A Group
    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _INPUT);
    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, _INPUT);
    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON1, _INPUT);
    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON1, _INPUT);
    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON1, _INPUT);
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON1, _INPUT);
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON1, _INPUT);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON1, _INPUT);
    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON1, _INPUT);
    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON1, _INPUT);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON1, _INPUT);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, _INPUT);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON2, _INPUT);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON2, _INPUT);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__ON2, _INPUT);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL1E__ON2, _INPUT);
    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__ON2, _INPUT);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__ON2, _INPUT);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__ON2, _INPUT);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__ON2, _INPUT);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__ON2, _INPUT);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__ON2, _INPUT);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__ON2, _INPUT);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__OFF2, _INPUT);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__ON4, _INPUT);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON4, _INPUT);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__OFF2, _INPUT);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL36__OFF2, _INPUT);
    ScalerSetByte(P10_38_PIN_SHARE_CTRL38__OFF2, _INPUT);
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL3A__OFF2, _INPUT);
    ScalerSetByte(P10_68_PIN_SHARE_CTRL68__OFF1, _INPUT);
    ScalerSetByte(P10_6A_PIN_SHARE_CTRL6A__OFF1, _INPUT);
    ScalerSetByte(P10_6C_PIN_SHARE_CTRL6C__OFF1, _INPUT);
    ScalerSetByte(P10_6E_PIN_SHARE_CTRL6E__OFF1, _INPUT);
    ScalerSetByte(P10_70_PIN_SHARE_CTRL70__OFF2, _INPUT);
    ScalerSetByte(P10_72_PIN_SHARE_CTRL72__OFF2, _INPUT);
    ScalerSetByte(P10_74_PIN_SHARE_CTRL74__OFF2, _INPUT);
    ScalerSetByte(P10_76_PIN_SHARE_CTRL76__OFF2, _INPUT);
    ScalerSetByte(P10_78_PIN_SHARE_CTRL78__OFF2, _INPUT);
    ScalerSetByte(P10_7A_PIN_SHARE_CTRL7A__OFF2, _INPUT);
    ScalerSetByte(P10_7C_PIN_SHARE_CTRL7C__OFF2, _INPUT);
    ScalerSetByte(P10_7E_PIN_SHARE_CTRL7E__OFF2, _INPUT);
    ScalerSetByte(P10_80_PIN_SHARE_CTRL80__OFF2, _INPUT);
    ScalerSetByte(P10_82_PIN_SHARE_CTRL82__ON1, _INPUT);
    ScalerSetByte(P10_84_PIN_SHARE_CTRL84__ON1, _INPUT);
    ScalerSetByte(P10_86_PIN_SHARE_CTRL86__ON1, _INPUT);
    ScalerSetByte(P10_87_PIN_SHARE_CTRL87__ON1, _INPUT);
    ScalerSetByte(P10_8A_PIN_SHARE_CTRL8A__ON1, _INPUT);
    ScalerSetByte(P10_8C_PIN_SHARE_CTRL8C__ON1, _INPUT);
    ScalerSetByte(P10_8E_PIN_SHARE_CTRL8E__ON1, _INPUT);
    ScalerSetByte(P10_90_PIN_SHARE_CTRL90__ON1, _INPUT);
    ScalerSetByte(P10_93_PIN_SHARE_CTRL93__ON1, _INPUT);
    ScalerSetByte(P10_94_PIN_SHARE_CTRL94__ON1, _INPUT);
    ScalerSetByte(P10_96_PIN_SHARE_CTRL96__ON1, _INPUT);
    ScalerSetByte(P10_98_PIN_SHARE_CTRL98__ON1, _INPUT);
    ScalerSetByte(P10_9A_PIN_SHARE_CTRL9A__ON1, _INPUT);
    ScalerSetByte(P10_9C_PIN_SHARE_CTRL9C__ON1, _INPUT);

    // Set B Group
    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PUSH_PULL);
    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _PUSH_PULL);
    ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON1, _PUSH_PULL);
    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON1, _PUSH_PULL);
    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON1, _PUSH_PULL);
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON1, _PUSH_PULL);
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON1, _PUSH_PULL);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON1, _PUSH_PULL);
    ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON1, _PUSH_PULL);
    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON1, _PUSH_PULL);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON1, _PUSH_PULL);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON1, _PUSH_PULL);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON2, _PUSH_PULL);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__ON2, _PUSH_PULL);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__ON2, _PUSH_PULL);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__ON2, _PUSH_PULL);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__ON2, _PUSH_PULL);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__ON2, _PUSH_PULL);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__ON2, _PUSH_PULL);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__ON2, _PUSH_PULL);
    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__ON2, _PUSH_PULL);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__ON2, _PUSH_PULL);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__ON2, _PUSH_PULL);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__ON4, _PUSH_PULL);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__ON4, _PUSH_PULL);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL35__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL37__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_39_PIN_SHARE_CTRL39__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_67_PIN_SHARE_CTRL67__OFF1, _PUSH_PULL);
    ScalerSetByte(P10_69_PIN_SHARE_CTRL69__OFF1, _PUSH_PULL);
    ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__OFF1, _PUSH_PULL);
    ScalerSetByte(P10_6D_PIN_SHARE_CTRL6D__OFF1, _PUSH_PULL);
    ScalerSetByte(P10_6F_PIN_SHARE_CTRL6F__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_71_PIN_SHARE_CTRL71__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_73_PIN_SHARE_CTRL73__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_75_PIN_SHARE_CTRL75__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_77_PIN_SHARE_CTRL77__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_79_PIN_SHARE_CTRL79__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_7B_PIN_SHARE_CTRL7B__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_7D_PIN_SHARE_CTRL7D__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_7F_PIN_SHARE_CTRL7F__OFF2, _PUSH_PULL);
    ScalerSetByte(P10_81_PIN_SHARE_CTRL81__ON1, _PUSH_PULL);
    ScalerSetByte(P10_83_PIN_SHARE_CTRL83__ON1, _PUSH_PULL);
    ScalerSetByte(P10_85_PIN_SHARE_CTRL85__ON1, _PUSH_PULL);
    ScalerSetByte(P10_88_PIN_SHARE_CTRL88__ON1, _OPEN_DRAIN);
    ScalerSetByte(P10_89_PIN_SHARE_CTRL89__ON1, _OPEN_DRAIN);
    ScalerSetByte(P10_8B_PIN_SHARE_CTRL8B__ON1, _PUSH_PULL);
    ScalerSetByte(P10_8D_PIN_SHARE_CTRL8D__ON1, _PUSH_PULL);
    ScalerSetByte(P10_8F_PIN_SHARE_CTRL8F__ON1, _PUSH_PULL);
    ScalerSetByte(P10_91_PIN_SHARE_CTRL91__ON1, _OPEN_DRAIN);
    ScalerSetByte(P10_92_PIN_SHARE_CTRL92__ON1, _OPEN_DRAIN);
    ScalerSetByte(P10_95_PIN_SHARE_CTRL95__ON1, _PUSH_PULL);
    ScalerSetByte(P10_97_PIN_SHARE_CTRL97__ON1, _PUSH_PULL);
    ScalerSetByte(P10_99_PIN_SHARE_CTRL99__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9B_PIN_SHARE_CTRL9B__ON1, _PUSH_PULL);
    ScalerSetByte(P10_9D_PIN_SHARE_CTRL9D__ON1, _PUSH_PULL);
}

//--------------------------------------------------
// Description  : IO Test A
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleIOCheckAtoB(void)
{
    ScalerIOToggleIOTESTModus(&MCU_FE00_PORT40_PIN_REG, _BIT0, &MCU_FE01_PORT41_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT00, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE02_PORT42_PIN_REG, _BIT0, &MCU_FE03_PORT43_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT00, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE04_PORT44_PIN_REG, _BIT0, &MCU_FE05_PORT45_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT00, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE06_PORT46_PIN_REG, _BIT0, &MCU_FE07_PORT47_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT00, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE08_PORT50_PIN_REG, _BIT0, &MCU_FE09_PORT51_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT00, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE0A_PORT52_PIN_REG, _BIT0, &MCU_FE0B_PORT53_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT00, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE0C_PORT54_PIN_REG, _BIT0, &MCU_FE0D_PORT55_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT00, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE0E_PORT56_PIN_REG, _BIT0, &MCU_FE0F_PORT57_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT00, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE10_PORT60_PIN_REG, _BIT0, &MCU_FE11_PORT61_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT01, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE12_PORT62_PIN_REG, _BIT0, &MCU_FE13_PORT63_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT01, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE14_PORT64_PIN_REG, _BIT0, &MCU_FE15_PORT65_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT01, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE16_PORT66_PIN_REG, _BIT0, &MCU_FE17_PORT67_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT01, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE18_PORT70_PIN_REG, _BIT0, &MCU_FE19_PORT71_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT01, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE1A_PORT72_PIN_REG, _BIT0, &MCU_FE1B_PORT73_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT01, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE1C_PORT74_PIN_REG, _BIT0, &MCU_FE1D_PORT75_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT01, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE1E_PORT76_PIN_REG, _BIT0, &MCU_FE1F_PORT77_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT01, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE20_PORT80_PIN_REG, _BIT0, &MCU_FE21_PORT81_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT02, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE22_PORT82_PIN_REG, _BIT0, &MCU_FE23_PORT83_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT02, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE24_PORT84_PIN_REG, _BIT0, &MCU_FE25_PORT85_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT02, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE26_PORT86_PIN_REG, _BIT0, &MCU_FE27_PORT87_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT02, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE28_PORT90_PIN_REG, _BIT0, &MCU_FE29_PORT91_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT02, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE2A_PORT92_PIN_REG, _BIT0, &MCU_FE2B_PORT93_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT02, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE2C_PORT94_PIN_REG, _BIT0, &MCU_FE2D_PORT95_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT02, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE2E_PORT96_PIN_REG, _BIT0, &MCU_FE2F_PORT97_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT02, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE30_PORTA0_PIN_REG, _BIT0, &MCU_FE31_PORTA1_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT03, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE32_PORTA2_PIN_REG, _BIT0, &MCU_FE33_PORTA3_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT03, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE34_PORTA4_PIN_REG, _BIT0, &MCU_FE35_PORTA5_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT03, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE36_PORTA6_PIN_REG, _BIT0, &MCU_FE37_PORTA7_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT03, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE38_PORTB0_PIN_REG, _BIT0, &MCU_FE39_PORTB1_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT03, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_FE3A_PORTB2_PIN_REG, _BIT0, &MCU_2207_PORT107_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT03, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2208_PORT110_PIN_REG, _BIT0, &MCU_2209_PORT111_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT03, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_220A_PORT112_PIN_REG, _BIT0, &MCU_220B_PORT113_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT03, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_220C_PORT114_PIN_REG, _BIT0, &MCU_220D_PORT115_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT04, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_220E_PORT116_PIN_REG, _BIT0, &MCU_220F_PORT117_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT04, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2210_PORT120_PIN_REG, _BIT0, &MCU_2211_PORT121_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT04, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2212_PORT122_PIN_REG, _BIT0, &MCU_2213_PORT123_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT04, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2214_PORT124_PIN_REG, _BIT0, &MCU_2215_PORT125_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT04, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2216_PORT126_PIN_REG, _BIT0, &MCU_2217_PORT127_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT04, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2218_PORT130_PIN_REG, _BIT0, &MCU_2219_PORT131_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT04, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_221A_PORT132_PIN_REG, _BIT0, &MCU_221B_PORT133_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT04, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_221C_PORT134_PIN_REG, _BIT0, &MCU_221D_PORT135_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT05, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_221E_PORT136_PIN_REG, _BIT0, &MCU_221F_PORT137_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT05, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2220_PORT140_PIN_REG, _BIT0, &MCU_2221_PORT141_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT05, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2222_PORT142_PIN_REG, _BIT0, &MCU_2223_PORT143_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT05, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2224_PORT144_PIN_REG, _BIT0, &MCU_2225_PORT145_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT05, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2226_PORT146_PIN_REG, _BIT0, &MCU_2228_PORT150_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT05, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2227_PORT147_PIN_REG, _BIT0, &MCU_2229_PORT151_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT05, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_222A_PORT152_PIN_REG, _BIT0, &MCU_222B_PORT153_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT05, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_222C_PORT154_PIN_REG, _BIT0, &MCU_222D_PORT155_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT06, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_222E_PORT156_PIN_REG, _BIT0, &MCU_222F_PORT157_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT06, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2230_PORT160_PIN_REG, _BIT0, &MCU_2231_PORT161_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT06, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2233_PORT163_PIN_REG, _BIT0, &MCU_2232_PORT162_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT06, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2234_PORT164_PIN_REG, _BIT0, &MCU_2235_PORT165_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT06, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2236_PORT166_PIN_REG, _BIT0, &MCU_2237_PORT167_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT06, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_2238_PORT170_PIN_REG, _BIT0, &MCU_2239_PORT171_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT06, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223A_PORT172_PIN_REG, _BIT0, &MCU_223B_PORT173_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT06, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_223D_PORT175_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT07, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE3B_PORTB3_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT07, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE3D_PORTB5_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT07, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE3F_PORTB7_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT07, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE41_PORTC1_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT07, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE43_PORTC3_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT07, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE45_PORTC5_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT07, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE47_PORTC7_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT07, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE49_PORTD1_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT08, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE4B_PORTD3_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT08, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE4D_PORTD5_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT08, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE4F_PORTD7_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT08, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE51_PORTE1_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT08, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE53_PORTE3_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT08, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE55_PORTE5_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT08, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE57_PORTE7_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT08, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE59_PORTF1_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT09, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE5B_PORTF3_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT09, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE5D_PORTF5_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT09, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE5F_PORTF7_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT09, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_2201_PORT101_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT09, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_2203_PORT103_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT09, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_2205_PORT105_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT09, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_2206_PORT106_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT09, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE3C_PORTB4_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0A, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE3E_PORTB6_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0A, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE40_PORTC0_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0A, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE42_PORTC2_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0A, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE44_PORTC4_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0A, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE46_PORTC6_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0A, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE48_PORTD0_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0A, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE4A_PORTD2_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0A, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE4C_PORTD4_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0B, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE4E_PORTD6_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0B, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE50_PORTE0_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0B, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE52_PORTE2_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0B, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE54_PORTE4_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0B, _BIT4, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE56_PORTE6_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0B, _BIT5, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE58_PORTF0_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0B, _BIT6, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE5A_PORTF2_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0B, _BIT7, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE5C_PORTF4_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0C, _BIT0, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_FE5E_PORTF6_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0C, _BIT1, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_2200_PORT100_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0C, _BIT2, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_2202_PORT102_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0C, _BIT3, _IO_TEST_A);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_2204_PORT104_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT0C, _BIT4, _IO_TEST_A);
}

//--------------------------------------------------
// Description  : IO Test B
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleIOCheckBtoA(void)
{
    ScalerIOToggleIOTESTModus(&MCU_FE00_PORT40_PIN_REG, _BIT0, &MCU_FE01_PORT41_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT10, _BIT0, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE02_PORT42_PIN_REG, _BIT0, &MCU_FE03_PORT43_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT10, _BIT1, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE04_PORT44_PIN_REG, _BIT0, &MCU_FE05_PORT45_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT10, _BIT2, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE06_PORT46_PIN_REG, _BIT0, &MCU_FE07_PORT47_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT10, _BIT3, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE08_PORT50_PIN_REG, _BIT0, &MCU_FE09_PORT51_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT10, _BIT4, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE0A_PORT52_PIN_REG, _BIT0, &MCU_FE0B_PORT53_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT10, _BIT5, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE0C_PORT54_PIN_REG, _BIT0, &MCU_FE0D_PORT55_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT10, _BIT6, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE0E_PORT56_PIN_REG, _BIT0, &MCU_FE0F_PORT57_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT10, _BIT7, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE10_PORT60_PIN_REG, _BIT0, &MCU_FE11_PORT61_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT11, _BIT0, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE12_PORT62_PIN_REG, _BIT0, &MCU_FE13_PORT63_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT11, _BIT1, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE14_PORT64_PIN_REG, _BIT0, &MCU_FE15_PORT65_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT11, _BIT2, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE16_PORT66_PIN_REG, _BIT0, &MCU_FE17_PORT67_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT11, _BIT3, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE18_PORT70_PIN_REG, _BIT0, &MCU_FE19_PORT71_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT11, _BIT4, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE1A_PORT72_PIN_REG, _BIT0, &MCU_FE1B_PORT73_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT11, _BIT5, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE1C_PORT74_PIN_REG, _BIT0, &MCU_FE1D_PORT75_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT11, _BIT6, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE1E_PORT76_PIN_REG, _BIT0, &MCU_FE1F_PORT77_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT11, _BIT7, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE20_PORT80_PIN_REG, _BIT0, &MCU_FE21_PORT81_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT12, _BIT0, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE22_PORT82_PIN_REG, _BIT0, &MCU_FE23_PORT83_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT12, _BIT1, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE24_PORT84_PIN_REG, _BIT0, &MCU_FE25_PORT85_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT12, _BIT2, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE26_PORT86_PIN_REG, _BIT0, &MCU_FE27_PORT87_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT12, _BIT3, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE28_PORT90_PIN_REG, _BIT0, &MCU_FE29_PORT91_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT12, _BIT4, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE2A_PORT92_PIN_REG, _BIT0, &MCU_FE2B_PORT93_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT12, _BIT5, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE2C_PORT94_PIN_REG, _BIT0, &MCU_FE2D_PORT95_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT12, _BIT6, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE2E_PORT96_PIN_REG, _BIT0, &MCU_FE2F_PORT97_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT12, _BIT7, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE30_PORTA0_PIN_REG, _BIT0, &MCU_FE31_PORTA1_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT13, _BIT0, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE32_PORTA2_PIN_REG, _BIT0, &MCU_FE33_PORTA3_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT13, _BIT1, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE34_PORTA4_PIN_REG, _BIT0, &MCU_FE35_PORTA5_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT13, _BIT2, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE36_PORTA6_PIN_REG, _BIT0, &MCU_FE37_PORTA7_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT13, _BIT3, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE38_PORTB0_PIN_REG, _BIT0, &MCU_FE39_PORTB1_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT13, _BIT4, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_FE3A_PORTB2_PIN_REG, _BIT0, &MCU_2207_PORT107_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT13, _BIT5, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2208_PORT110_PIN_REG, _BIT0, &MCU_2209_PORT111_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT13, _BIT6, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_220A_PORT112_PIN_REG, _BIT0, &MCU_220B_PORT113_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT13, _BIT7, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_220C_PORT114_PIN_REG, _BIT0, &MCU_220D_PORT115_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT14, _BIT0, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_220E_PORT116_PIN_REG, _BIT0, &MCU_220F_PORT117_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT14, _BIT1, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2210_PORT120_PIN_REG, _BIT0, &MCU_2211_PORT121_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT14, _BIT2, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2212_PORT122_PIN_REG, _BIT0, &MCU_2213_PORT123_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT14, _BIT3, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2214_PORT124_PIN_REG, _BIT0, &MCU_2215_PORT125_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT14, _BIT4, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2216_PORT126_PIN_REG, _BIT0, &MCU_2217_PORT127_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT14, _BIT5, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2218_PORT130_PIN_REG, _BIT0, &MCU_2219_PORT131_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT14, _BIT6, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_221A_PORT132_PIN_REG, _BIT0, &MCU_221B_PORT133_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT14, _BIT7, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_221C_PORT134_PIN_REG, _BIT0, &MCU_221D_PORT135_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT15, _BIT0, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_221E_PORT136_PIN_REG, _BIT0, &MCU_221F_PORT137_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT15, _BIT1, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2220_PORT140_PIN_REG, _BIT0, &MCU_2221_PORT141_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT15, _BIT2, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2222_PORT142_PIN_REG, _BIT0, &MCU_2223_PORT143_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT15, _BIT3, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2224_PORT144_PIN_REG, _BIT0, &MCU_2225_PORT145_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT15, _BIT4, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2226_PORT146_PIN_REG, _BIT0, &MCU_2228_PORT150_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT15, _BIT5, _IO_TEST_OD);
    ScalerIOToggleIOTESTModus(&MCU_2227_PORT147_PIN_REG, _BIT0, &MCU_2229_PORT151_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT15, _BIT6, _IO_TEST_OD);
    ScalerIOToggleIOTESTModus(&MCU_222A_PORT152_PIN_REG, _BIT0, &MCU_222B_PORT153_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT15, _BIT7, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_222C_PORT154_PIN_REG, _BIT0, &MCU_222D_PORT155_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT16, _BIT0, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_222E_PORT156_PIN_REG, _BIT0, &MCU_222F_PORT157_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT16, _BIT1, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2230_PORT160_PIN_REG, _BIT0, &MCU_2231_PORT161_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT16, _BIT2, _IO_TEST_OD);
    ScalerIOToggleIOTESTModus(&MCU_2233_PORT163_PIN_REG, _BIT0, &MCU_2232_PORT162_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT16, _BIT3, _IO_TEST_OD);
    ScalerIOToggleIOTESTModus(&MCU_2234_PORT164_PIN_REG, _BIT0, &MCU_2235_PORT165_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT16, _BIT4, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2236_PORT166_PIN_REG, _BIT0, &MCU_2237_PORT167_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT16, _BIT5, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_2238_PORT170_PIN_REG, _BIT0, &MCU_2239_PORT171_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT16, _BIT6, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_223A_PORT172_PIN_REG, _BIT0, &MCU_223B_PORT173_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT16, _BIT7, _IO_TEST_B);
    ScalerIOToggleIOTESTModus(&MCU_223C_PORT174_PIN_REG, _BIT0, &MCU_223D_PORT175_PIN_REG, _BIT0, &g_uc_IO_TEST_RESULT17, _BIT0, _IO_TEST_B);
}

//--------------------------------------------------
// Description  : GPIO Toggle Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleIOTESTModus(BYTE *pucIOTestAPortNum, BYTE ucIOTestApin, BYTE *pucIOTestBPortNum, BYTE ucIOTestBpin, BYTE *pucResult, BYTE ucNum, BYTE ucIOtype)
{
    ucIOTestApin = ucIOTestApin;
    ucIOTestBpin = ucIOTestBpin;

    ScalerIOToggleXFRtoXFRTest(pucIOTestAPortNum, pucIOTestBPortNum, pucResult, ucNum, ucIOtype);
}

//--------------------------------------------------
// Description  : XFR IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleXFRtoXFRTest(BYTE *pucIOTestAaddr, BYTE *pucIOTestBaddr, BYTE *pucResult, BYTE ucNum, BYTE ucIOtype)
{
    if(ucIOtype == _IO_TEST_A)
    {
        *pucIOTestAaddr = 1;
        ScalerTimerDelayXms(10);

        if(*pucIOTestBaddr == 0x01)
        {
            *pucIOTestAaddr = 0;
            ScalerTimerDelayXms(10);

            if(*pucIOTestBaddr == 0x00)
            {
                *pucResult &= ~ucNum;
            }
        }
    }
    else if(ucIOtype == _IO_TEST_B)
    {
        *pucIOTestBaddr = 1;
        ScalerTimerDelayXms(10);

        if(*pucIOTestAaddr == 0x01)
        {
            *pucIOTestBaddr = 0;
            ScalerTimerDelayXms(10);

            if(*pucIOTestAaddr == 0x00)
            {
                *pucResult &= ~ucNum;
            }
        }
    }
    else
    {
        ScalerIOToggleIOPullUp();
        ScalerTimerDelayXms(10);

        if(*pucIOTestAaddr == 0x01)
        {
            ScalerIOToggleIOPullDown();
            ScalerTimerDelayXms(10);

            if(*pucIOTestAaddr == 0x00)
            {
                *pucResult &= ~ucNum;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Pinshare Settings for Pull Up Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleIOPullUp(void)
{
    // Set Pull up: D6[1:0]/D7[7:6]/D9[7:4]
    ScalerSetByte(P10_D6_PIN_PULLUP_CTRL16__ON1, 0x01);
    ScalerSetByte(P10_D7_PIN_PULLUP_CTRL17__ON1, 0x40);
    ScalerSetByte(P10_D9_PIN_PULLUP_CTRL19__ON1, 0x50);
}

//--------------------------------------------------
// Description  : Pinshare Settings for Pull Down Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleIOPullDown(void)
{
    // Set Pull down: D6[1:0]/D7[7:6]/D9[7:4]
    ScalerSetByte(P10_D6_PIN_PULLUP_CTRL16__ON1, 0x02);
    ScalerSetByte(P10_D7_PIN_PULLUP_CTRL17__ON1, 0x80);
    ScalerSetByte(P10_D9_PIN_PULLUP_CTRL19__ON1, 0xA0);
}

//--------------------------------------------------
// Description  : Pinshare Settings for LED
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleSetLED(void)
{
    // Set LDE pin pinshare to Push-pull
    ScalerSetByte(P10_6B_PIN_SHARE_CTRL6B__OFF1, 0x01);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__ON2, 0x01);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__ON2, 0x01);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON1, 0x01);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON1, 0x01);
}

//--------------------------------------------------
// Description  : Pinshare Settings for DDC enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOToggleSetDDC(void)
{
    // Set pinshare to DDC_ISP
    ScalerSetByte(P10_97_PIN_SHARE_CTRL97__ON1, 0x03);
    ScalerSetByte(P10_98_PIN_SHARE_CTRL98__ON1, 0x03);
}

#endif // End of #if(_PCB_SUPPORT_IO_TOOGLE == _ON)

