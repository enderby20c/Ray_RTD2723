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
// ID Code      : RL6952_Series_PinshareMapping.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifdef _PIN_J4
#define _PACKAGE_TYPE                   _PACKAGE_RL6952_BGA4L
#endif

#ifdef _2L_900PIN_PIN_J4
#include "RL6952_BGA2L_Series_Pin_Mapping.h"
#define _PACKAGE_TYPE                   _PACKAGE_RL6952_BGA2L
#endif

//--------------------------------------------------
// Pin MCU Reg Mapping
//--------------------------------------------------
#define GET_GPIO_PIN_J4()               (MCU_FE00_PORT40_PIN_REG)
#define SET_GPIO_PIN_J4(x)              (MCU_FE00_PORT40_PIN_REG = (x))

#define GET_GPIO_PIN_K4()               (MCU_FE01_PORT41_PIN_REG)
#define SET_GPIO_PIN_K4(x)              (MCU_FE01_PORT41_PIN_REG = (x))

#define GET_GPIO_PIN_H4()               (MCU_FE02_PORT42_PIN_REG)
#define SET_GPIO_PIN_H4(x)              (MCU_FE02_PORT42_PIN_REG = (x))

#define GET_GPIO_PIN_G6()               (MCU_FE03_PORT43_PIN_REG)
#define SET_GPIO_PIN_G6(x)              (MCU_FE03_PORT43_PIN_REG = (x))

#define GET_GPIO_PIN_AD4()              (MCU_FE04_PORT44_PIN_REG)
#define SET_GPIO_PIN_AD4(x)             (MCU_FE04_PORT44_PIN_REG = (x))

#define GET_GPIO_PIN_W4()               (MCU_FE05_PORT45_PIN_REG)
#define SET_GPIO_PIN_W4(x)              (MCU_FE05_PORT45_PIN_REG = (x))

#define GET_GPIO_PIN_W5()               (MCU_FE06_PORT46_PIN_REG)
#define SET_GPIO_PIN_W5(x)              (MCU_FE06_PORT46_PIN_REG = (x))

#define GET_GPIO_PIN_T4()               (MCU_FE07_PORT47_PIN_REG)
#define SET_GPIO_PIN_T4(x)              (MCU_FE07_PORT47_PIN_REG = (x))

#define GET_GPIO_PIN_AA4()              (MCU_FE08_PORT50_PIN_REG)
#define SET_GPIO_PIN_AA4(x)             (MCU_FE08_PORT50_PIN_REG = (x))

#define GET_GPIO_PIN_AA5()              (MCU_FE09_PORT51_PIN_REG)
#define SET_GPIO_PIN_AA5(x)             (MCU_FE09_PORT51_PIN_REG = (x))

#define GET_GPIO_PIN_AB4()              (MCU_FE0A_PORT52_PIN_REG)
#define SET_GPIO_PIN_AB4(x)             (MCU_FE0A_PORT52_PIN_REG = (x))

#define GET_GPIO_PIN_AB5()              (MCU_FE0B_PORT53_PIN_REG)
#define SET_GPIO_PIN_AB5(x)             (MCU_FE0B_PORT53_PIN_REG = (x))

#define GET_GPIO_PIN_AE4()              (MCU_FE0C_PORT54_PIN_REG)
#define SET_GPIO_PIN_AE4(x)             (MCU_FE0C_PORT54_PIN_REG = (x))

#define GET_GPIO_PIN_AE5()              (MCU_FE0D_PORT55_PIN_REG)
#define SET_GPIO_PIN_AE5(x)             (MCU_FE0D_PORT55_PIN_REG = (x))

#define GET_GPIO_PIN_AD5()              (MCU_FE0E_PORT56_PIN_REG)
#define SET_GPIO_PIN_AD5(x)             (MCU_FE0E_PORT56_PIN_REG = (x))

#define GET_GPIO_PIN_AF6()              (MCU_FE0F_PORT57_PIN_REG)
#define SET_GPIO_PIN_AF6(x)             (MCU_FE0F_PORT57_PIN_REG = (x))

#define GET_GPIO_PIN_AF7()              (MCU_FE10_PORT60_PIN_REG)
#define SET_GPIO_PIN_AF7(x)             (MCU_FE10_PORT60_PIN_REG = (x))

#define GET_GPIO_PIN_AG6()              (MCU_FE11_PORT61_PIN_REG)
#define SET_GPIO_PIN_AG6(x)             (MCU_FE11_PORT61_PIN_REG = (x))

#define GET_GPIO_PIN_AG7()              (MCU_FE12_PORT62_PIN_REG)
#define SET_GPIO_PIN_AG7(x)             (MCU_FE12_PORT62_PIN_REG = (x))

#define GET_GPIO_PIN_AF12()             (MCU_FE13_PORT63_PIN_REG)
#define SET_GPIO_PIN_AF12(x)            (MCU_FE13_PORT63_PIN_REG = (x))

#define GET_GPIO_PIN_AF11()             (MCU_FE14_PORT64_PIN_REG)
#define SET_GPIO_PIN_AF11(x)            (MCU_FE14_PORT64_PIN_REG = (x))

#define GET_GPIO_PIN_AF10()             (MCU_FE15_PORT65_PIN_REG)
#define SET_GPIO_PIN_AF10(x)            (MCU_FE15_PORT65_PIN_REG = (x))

#define GET_GPIO_PIN_AF9()              (MCU_FE16_PORT66_PIN_REG)
#define SET_GPIO_PIN_AF9(x)             (MCU_FE16_PORT66_PIN_REG = (x))

#define GET_GPIO_PIN_AG12()             (MCU_FE17_PORT67_PIN_REG)
#define SET_GPIO_PIN_AG12(x)            (MCU_FE17_PORT67_PIN_REG = (x))

#define GET_GPIO_PIN_AG11()             (MCU_FE18_PORT70_PIN_REG)
#define SET_GPIO_PIN_AG11(x)            (MCU_FE18_PORT70_PIN_REG = (x))

#define GET_GPIO_PIN_AG10()             (MCU_FE19_PORT71_PIN_REG)
#define SET_GPIO_PIN_AG10(x)            (MCU_FE19_PORT71_PIN_REG = (x))

#define GET_GPIO_PIN_AG9()              (MCU_FE1A_PORT72_PIN_REG)
#define SET_GPIO_PIN_AG9(x)             (MCU_FE1A_PORT72_PIN_REG = (x))

#define GET_GPIO_PIN_AG20()             (MCU_FE1B_PORT73_PIN_REG)
#define SET_GPIO_PIN_AG20(x)            (MCU_FE1B_PORT73_PIN_REG = (x))

#define GET_GPIO_PIN_AF20()             (MCU_FE1C_PORT74_PIN_REG)
#define SET_GPIO_PIN_AF20(x)            (MCU_FE1C_PORT74_PIN_REG = (x))

#define GET_GPIO_PIN_AF19()             (MCU_FE1D_PORT75_PIN_REG)
#define SET_GPIO_PIN_AF19(x)            (MCU_FE1D_PORT75_PIN_REG = (x))

#define GET_GPIO_PIN_AG22()             (MCU_FE1F_PORT77_PIN_REG)
#define SET_GPIO_PIN_AG22(x)            (MCU_FE1F_PORT77_PIN_REG = (x))

#define GET_GPIO_PIN_AF22()             (MCU_FE20_PORT80_PIN_REG)
#define SET_GPIO_PIN_AF22(x)            (MCU_FE20_PORT80_PIN_REG = (x))

#define GET_GPIO_PIN_AG23()             (MCU_FE21_PORT81_PIN_REG)
#define SET_GPIO_PIN_AG23(x)            (MCU_FE21_PORT81_PIN_REG = (x))

#define GET_GPIO_PIN_AE23()             (MCU_FE22_PORT82_PIN_REG)
#define SET_GPIO_PIN_AE23(x)            (MCU_FE22_PORT82_PIN_REG = (x))

#define GET_GPIO_PIN_AA22()             (MCU_FE23_PORT83_PIN_REG)
#define SET_GPIO_PIN_AA22(x)            (MCU_FE23_PORT83_PIN_REG = (x))

#define GET_GPIO_PIN_W23()              (MCU_FE24_PORT84_PIN_REG)
#define SET_GPIO_PIN_W23(x)             (MCU_FE24_PORT84_PIN_REG = (x))

#define GET_GPIO_PIN_W22()              (MCU_FE25_PORT85_PIN_REG)
#define SET_GPIO_PIN_W22(x)             (MCU_FE25_PORT85_PIN_REG = (x))

#define GET_GPIO_PIN_AE26()             (MCU_FE26_PORT86_PIN_REG)
#define SET_GPIO_PIN_AE26(x)            (MCU_FE26_PORT86_PIN_REG = (x))

#define GET_GPIO_PIN_AD26()             (MCU_FE27_PORT87_PIN_REG)
#define SET_GPIO_PIN_AD26(x)            (MCU_FE27_PORT87_PIN_REG = (x))

#define GET_GPIO_PIN_AB26()             (MCU_FE28_PORT90_PIN_REG)
#define SET_GPIO_PIN_AB26(x)            (MCU_FE28_PORT90_PIN_REG = (x))

#define GET_GPIO_PIN_AC26()             (MCU_FE29_PORT91_PIN_REG)
#define SET_GPIO_PIN_AC26(x)            (MCU_FE29_PORT91_PIN_REG = (x))

#define GET_GPIO_PIN_Y26()              (MCU_FE2A_PORT92_PIN_REG)
#define SET_GPIO_PIN_Y26(x)             (MCU_FE2A_PORT92_PIN_REG = (x))

#define GET_GPIO_PIN_AA26()             (MCU_FE2B_PORT93_PIN_REG)
#define SET_GPIO_PIN_AA26(x)            (MCU_FE2B_PORT93_PIN_REG = (x))

#define GET_GPIO_PIN_Y23()              (MCU_FE2C_PORT94_PIN_REG)
#define SET_GPIO_PIN_Y23(x)             (MCU_FE2C_PORT94_PIN_REG = (x))

#define GET_GPIO_PIN_Y22()              (MCU_FE2D_PORT95_PIN_REG)
#define SET_GPIO_PIN_Y22(x)             (MCU_FE2D_PORT95_PIN_REG = (x))

#define GET_GPIO_PIN_AA23()             (MCU_FE2E_PORT96_PIN_REG)
#define SET_GPIO_PIN_AA23(x)            (MCU_FE2E_PORT96_PIN_REG = (x))

#define GET_GPIO_PIN_Y24()              (MCU_FE2F_PORT97_PIN_REG)
#define SET_GPIO_PIN_Y24(x)             (MCU_FE2F_PORT97_PIN_REG = (x))

#define GET_GPIO_PIN_AA24()             (MCU_FE30_PORTA0_PIN_REG)
#define SET_GPIO_PIN_AA24(x)            (MCU_FE30_PORTA0_PIN_REG = (x))

#define GET_GPIO_PIN_Y25()              (MCU_FE31_PORTA1_PIN_REG)
#define SET_GPIO_PIN_Y25(x)             (MCU_FE31_PORTA1_PIN_REG = (x))

#define GET_GPIO_PIN_AA25()             (MCU_FE32_PORTA2_PIN_REG)
#define SET_GPIO_PIN_AA25(x)            (MCU_FE32_PORTA2_PIN_REG = (x))

#define GET_GPIO_PIN_AC25()             (MCU_FE33_PORTA3_PIN_REG)
#define SET_GPIO_PIN_AC25(x)            (MCU_FE33_PORTA3_PIN_REG = (x))

#define GET_GPIO_PIN_AB25()             (MCU_FE34_PORTA4_PIN_REG)
#define SET_GPIO_PIN_AB25(x)            (MCU_FE34_PORTA4_PIN_REG = (x))

#define GET_GPIO_PIN_R28()              (MCU_FE35_PORTA5_PIN_REG)
#define SET_GPIO_PIN_R28(x)             (MCU_FE35_PORTA5_PIN_REG = (x))

#define GET_GPIO_PIN_R30()              (MCU_FE36_PORTA6_PIN_REG)
#define SET_GPIO_PIN_R30(x)             (MCU_FE36_PORTA6_PIN_REG = (x))

#define GET_GPIO_PIN_R29()              (MCU_FE37_PORTA7_PIN_REG)
#define SET_GPIO_PIN_R29(x)             (MCU_FE37_PORTA7_PIN_REG = (x))

#define GET_GPIO_PIN_P28()              (MCU_FE38_PORTB0_PIN_REG)
#define SET_GPIO_PIN_P28(x)             (MCU_FE38_PORTB0_PIN_REG = (x))

#define GET_GPIO_PIN_P29()              (MCU_FE39_PORTB1_PIN_REG)
#define SET_GPIO_PIN_P29(x)             (MCU_FE39_PORTB1_PIN_REG = (x))

#define GET_GPIO_PIN_N29()              (MCU_FE3A_PORTB2_PIN_REG)
#define SET_GPIO_PIN_N29(x)             (MCU_FE3A_PORTB2_PIN_REG = (x))

#define GET_GPIO_PIN_N30()              (MCU_FE3B_PORTB3_PIN_REG)
#define SET_GPIO_PIN_N30(x)             (MCU_FE3B_PORTB3_PIN_REG = (x))

#define GET_GPIO_PIN_N28()              (MCU_FE3C_PORTB4_PIN_REG)
#define SET_GPIO_PIN_N28(x)             (MCU_FE3C_PORTB4_PIN_REG = (x))

#define GET_GPIO_PIN_L28()              (MCU_FE3D_PORTB5_PIN_REG)
#define SET_GPIO_PIN_L28(x)             (MCU_FE3D_PORTB5_PIN_REG = (x))

#define GET_GPIO_PIN_L30()              (MCU_FE3E_PORTB6_PIN_REG)
#define SET_GPIO_PIN_L30(x)             (MCU_FE3E_PORTB6_PIN_REG = (x))

#define GET_GPIO_PIN_L29()              (MCU_FE3F_PORTB7_PIN_REG)
#define SET_GPIO_PIN_L29(x)             (MCU_FE3F_PORTB7_PIN_REG = (x))

#define GET_GPIO_PIN_K28()              (MCU_FE40_PORTC0_PIN_REG)
#define SET_GPIO_PIN_K28(x)             (MCU_FE40_PORTC0_PIN_REG = (x))

#define GET_GPIO_PIN_K29()              (MCU_FE41_PORTC1_PIN_REG)
#define SET_GPIO_PIN_K29(x)             (MCU_FE41_PORTC1_PIN_REG = (x))

#define GET_GPIO_PIN_J29()              (MCU_FE42_PORTC2_PIN_REG)
#define SET_GPIO_PIN_J29(x)             (MCU_FE42_PORTC2_PIN_REG = (x))

#define GET_GPIO_PIN_J30()              (MCU_FE43_PORTC3_PIN_REG)
#define SET_GPIO_PIN_J30(x)             (MCU_FE43_PORTC3_PIN_REG = (x))

#define GET_GPIO_PIN_J28()              (MCU_FE44_PORTC4_PIN_REG)
#define SET_GPIO_PIN_J28(x)             (MCU_FE44_PORTC4_PIN_REG = (x))

#define GET_GPIO_PIN_G28()              (MCU_FE45_PORTC5_PIN_REG)
#define SET_GPIO_PIN_G28(x)             (MCU_FE45_PORTC5_PIN_REG = (x))

#define GET_GPIO_PIN_G30()              (MCU_FE46_PORTC6_PIN_REG)
#define SET_GPIO_PIN_G30(x)             (MCU_FE46_PORTC6_PIN_REG = (x))

#define GET_GPIO_PIN_G29()              (MCU_FE47_PORTC7_PIN_REG)
#define SET_GPIO_PIN_G29(x)             (MCU_FE47_PORTC7_PIN_REG = (x))

#define GET_GPIO_PIN_F28()              (MCU_FE48_PORTD0_PIN_REG)
#define SET_GPIO_PIN_F28(x)             (MCU_FE48_PORTD0_PIN_REG = (x))

#define GET_GPIO_PIN_F29()              (MCU_FE49_PORTD1_PIN_REG)
#define SET_GPIO_PIN_F29(x)             (MCU_FE49_PORTD1_PIN_REG = (x))

#define GET_GPIO_PIN_E29()              (MCU_FE4A_PORTD2_PIN_REG)
#define SET_GPIO_PIN_E29(x)             (MCU_FE4A_PORTD2_PIN_REG = (x))

#define GET_GPIO_PIN_E30()              (MCU_FE4B_PORTD3_PIN_REG)
#define SET_GPIO_PIN_E30(x)             (MCU_FE4B_PORTD3_PIN_REG = (x))

#define GET_GPIO_PIN_E28()              (MCU_FE4C_PORTD4_PIN_REG)
#define SET_GPIO_PIN_E28(x)             (MCU_FE4C_PORTD4_PIN_REG = (x))

#define GET_GPIO_PIN_C28()              (MCU_FE4D_PORTD5_PIN_REG)
#define SET_GPIO_PIN_C28(x)             (MCU_FE4D_PORTD5_PIN_REG = (x))

#define GET_GPIO_PIN_A28()              (MCU_FE4E_PORTD6_PIN_REG)
#define SET_GPIO_PIN_A28(x)             (MCU_FE4E_PORTD6_PIN_REG = (x))

#define GET_GPIO_PIN_B28()              (MCU_FE4F_PORTD7_PIN_REG)
#define SET_GPIO_PIN_B28(x)             (MCU_FE4F_PORTD7_PIN_REG = (x))

#define GET_GPIO_PIN_C27()              (MCU_FE50_PORTE0_PIN_REG)
#define SET_GPIO_PIN_C27(x)             (MCU_FE50_PORTE0_PIN_REG = (x))

#define GET_GPIO_PIN_B27()              (MCU_FE51_PORTE1_PIN_REG)
#define SET_GPIO_PIN_B27(x)             (MCU_FE51_PORTE1_PIN_REG = (x))

#define GET_GPIO_PIN_B26()              (MCU_FE52_PORTE2_PIN_REG)
#define SET_GPIO_PIN_B26(x)             (MCU_FE52_PORTE2_PIN_REG = (x))

#define GET_GPIO_PIN_A26()              (MCU_FE53_PORTE3_PIN_REG)
#define SET_GPIO_PIN_A26(x)             (MCU_FE53_PORTE3_PIN_REG = (x))

#define GET_GPIO_PIN_C26()              (MCU_FE54_PORTE4_PIN_REG)
#define SET_GPIO_PIN_C26(x)             (MCU_FE54_PORTE4_PIN_REG = (x))

#define GET_GPIO_PIN_C24()              (MCU_FE55_PORTE5_PIN_REG)
#define SET_GPIO_PIN_C24(x)             (MCU_FE55_PORTE5_PIN_REG = (x))

#define GET_GPIO_PIN_A24()              (MCU_FE56_PORTE6_PIN_REG)
#define SET_GPIO_PIN_A24(x)             (MCU_FE56_PORTE6_PIN_REG = (x))

#define GET_GPIO_PIN_B24()              (MCU_FE57_PORTE7_PIN_REG)
#define SET_GPIO_PIN_B24(x)             (MCU_FE57_PORTE7_PIN_REG = (x))

#define GET_GPIO_PIN_C23()              (MCU_FE58_PORTF0_PIN_REG)
#define SET_GPIO_PIN_C23(x)             (MCU_FE58_PORTF0_PIN_REG = (x))

#define GET_GPIO_PIN_B23()              (MCU_FE59_PORTF1_PIN_REG)
#define SET_GPIO_PIN_B23(x)             (MCU_FE59_PORTF1_PIN_REG = (x))

#define GET_GPIO_PIN_B22()              (MCU_FE5A_PORTF2_PIN_REG)
#define SET_GPIO_PIN_B22(x)             (MCU_FE5A_PORTF2_PIN_REG = (x))

#define GET_GPIO_PIN_A22()              (MCU_FE5B_PORTF3_PIN_REG)
#define SET_GPIO_PIN_A22(x)             (MCU_FE5B_PORTF3_PIN_REG = (x))

#define GET_GPIO_PIN_C22()              (MCU_FE5C_PORTF4_PIN_REG)
#define SET_GPIO_PIN_C22(x)             (MCU_FE5C_PORTF4_PIN_REG = (x))

#define GET_GPIO_PIN_B20()              (MCU_FE5D_PORTF5_PIN_REG)
#define SET_GPIO_PIN_B20(x)             (MCU_FE5D_PORTF5_PIN_REG = (x))

#define GET_GPIO_PIN_A20()              (MCU_FE5E_PORTF6_PIN_REG)
#define SET_GPIO_PIN_A20(x)             (MCU_FE5E_PORTF6_PIN_REG = (x))

#define GET_GPIO_PIN_B19()              (MCU_FE5F_PORTF7_PIN_REG)
#define SET_GPIO_PIN_B19(x)             (MCU_FE5F_PORTF7_PIN_REG = (x))

#define GET_GPIO_PIN_A19()              (MCU_2200_PORT100_PIN_REG)
#define SET_GPIO_PIN_A19(x)             (MCU_2200_PORT100_PIN_REG = (x))

#define GET_GPIO_PIN_K9()               (MCU_2201_PORT101_PIN_REG)
#define SET_GPIO_PIN_K9(x)              (MCU_2201_PORT101_PIN_REG = (x))

#define GET_GPIO_PIN_H13()              (MCU_2202_PORT102_PIN_REG)
#define SET_GPIO_PIN_H13(x)             (MCU_2202_PORT102_PIN_REG = (x))

#define GET_GPIO_PIN_H11()              (MCU_2203_PORT103_PIN_REG)
#define SET_GPIO_PIN_H11(x)             (MCU_2203_PORT103_PIN_REG = (x))

#define GET_GPIO_PIN_K8()               (MCU_2204_PORT104_PIN_REG)
#define SET_GPIO_PIN_K8(x)              (MCU_2204_PORT104_PIN_REG = (x))

#define GET_GPIO_PIN_H12()              (MCU_2205_PORT105_PIN_REG)
#define SET_GPIO_PIN_H12(x)             (MCU_2205_PORT105_PIN_REG = (x))

#define GET_GPIO_PIN_J8()               (MCU_2206_PORT106_PIN_REG)
#define SET_GPIO_PIN_J8(x)              (MCU_2206_PORT106_PIN_REG = (x))

#define GET_GPIO_PIN_F9()               (MCU_2207_PORT107_PIN_REG)
#define SET_GPIO_PIN_F9(x)              (MCU_2207_PORT107_PIN_REG = (x))

#define GET_GPIO_PIN_F11()              (MCU_2208_PORT110_PIN_REG)
#define SET_GPIO_PIN_F11(x)             (MCU_2208_PORT110_PIN_REG = (x))

#define GET_GPIO_PIN_F12()              (MCU_2209_PORT111_PIN_REG)
#define SET_GPIO_PIN_F12(x)             (MCU_2209_PORT111_PIN_REG = (x))

#define GET_GPIO_PIN_E13()              (MCU_220A_PORT112_PIN_REG)
#define SET_GPIO_PIN_E13(x)             (MCU_220A_PORT112_PIN_REG = (x))

#define GET_GPIO_PIN_F13()              (MCU_220B_PORT113_PIN_REG)
#define SET_GPIO_PIN_F13(x)             (MCU_220B_PORT113_PIN_REG = (x))

#define GET_GPIO_PIN_E12()              (MCU_220C_PORT114_PIN_REG)
#define SET_GPIO_PIN_E12(x)             (MCU_220C_PORT114_PIN_REG = (x))

#define GET_GPIO_PIN_G9()               (MCU_220D_PORT115_PIN_REG)
#define SET_GPIO_PIN_G9(x)              (MCU_220D_PORT115_PIN_REG = (x))

#define GET_GPIO_PIN_F8()               (MCU_220E_PORT116_PIN_REG)
#define SET_GPIO_PIN_F8(x)              (MCU_220E_PORT116_PIN_REG = (x))

#define GET_GPIO_PIN_E3()               (MCU_220F_PORT117_PIN_REG)
#define SET_GPIO_PIN_E3(x)              (MCU_220F_PORT117_PIN_REG = (x))

#define GET_GPIO_PIN_H8()               (MCU_2210_PORT120_PIN_REG)
#define SET_GPIO_PIN_H8(x)              (MCU_2210_PORT120_PIN_REG = (x))

#define GET_GPIO_PIN_D5()               (MCU_2211_PORT121_PIN_REG)
#define SET_GPIO_PIN_D5(x)              (MCU_2211_PORT121_PIN_REG = (x))

#define GET_GPIO_PIN_D4()               (MCU_2212_PORT122_PIN_REG)
#define SET_GPIO_PIN_D4(x)              (MCU_2212_PORT122_PIN_REG = (x))

#define GET_GPIO_PIN_D3()               (MCU_2213_PORT123_PIN_REG)
#define SET_GPIO_PIN_D3(x)              (MCU_2213_PORT123_PIN_REG = (x))

#define GET_GPIO_PIN_H7()               (MCU_2214_PORT124_PIN_REG)
#define SET_GPIO_PIN_H7(x)              (MCU_2214_PORT124_PIN_REG = (x))

#define GET_GPIO_PIN_C5()               (MCU_2215_PORT125_PIN_REG)
#define SET_GPIO_PIN_C5(x)              (MCU_2215_PORT125_PIN_REG = (x))

#define GET_GPIO_PIN_B5()               (MCU_2216_PORT126_PIN_REG)
#define SET_GPIO_PIN_B5(x)              (MCU_2216_PORT126_PIN_REG = (x))

#define GET_GPIO_PIN_B4()               (MCU_2217_PORT127_PIN_REG)
#define SET_GPIO_PIN_B4(x)              (MCU_2217_PORT127_PIN_REG = (x))

#define GET_GPIO_PIN_C4()               (MCU_2218_PORT130_PIN_REG)
#define SET_GPIO_PIN_C4(x)              (MCU_2218_PORT130_PIN_REG = (x))

#define GET_GPIO_PIN_C3()               (MCU_2219_PORT131_PIN_REG)
#define SET_GPIO_PIN_C3(x)              (MCU_2219_PORT131_PIN_REG = (x))

#define GET_GPIO_PIN_J9()               (MCU_221A_PORT132_PIN_REG)
#define SET_GPIO_PIN_J9(x)              (MCU_221A_PORT132_PIN_REG = (x))

#define GET_GPIO_PIN_E5()               (MCU_221B_PORT133_PIN_REG)
#define SET_GPIO_PIN_E5(x)              (MCU_221B_PORT133_PIN_REG = (x))

#define GET_GPIO_PIN_D12()              (MCU_221C_PORT134_PIN_REG)
#define SET_GPIO_PIN_D12(x)             (MCU_221C_PORT134_PIN_REG = (x))

#define GET_GPIO_PIN_D13()              (MCU_221D_PORT135_PIN_REG)
#define SET_GPIO_PIN_D13(x)             (MCU_221D_PORT135_PIN_REG = (x))

#define GET_GPIO_PIN_H9()               (MCU_221E_PORT136_PIN_REG)
#define SET_GPIO_PIN_H9(x)              (MCU_221E_PORT136_PIN_REG = (x))

#define GET_GPIO_PIN_A5()               (MCU_221F_PORT137_PIN_REG)
#define SET_GPIO_PIN_A5(x)              (MCU_221F_PORT137_PIN_REG = (x))

#define GET_GPIO_PIN_E11()              (MCU_2220_PORT140_PIN_REG)
#define SET_GPIO_PIN_E11(x)             (MCU_2220_PORT140_PIN_REG = (x))

#define GET_GPIO_PIN_V4()               (MCU_2221_PORT141_PIN_REG)
#define SET_GPIO_PIN_V4(x)              (MCU_2221_PORT141_PIN_REG = (x))

#define GET_GPIO_PIN_U4()               (MCU_2222_PORT142_PIN_REG)
#define SET_GPIO_PIN_U4(x)              (MCU_2222_PORT142_PIN_REG = (x))

#define GET_GPIO_PIN_G8()               (MCU_2223_PORT143_PIN_REG)
#define SET_GPIO_PIN_G8(x)              (MCU_2223_PORT143_PIN_REG = (x))

#define GET_GPIO_PIN_E4()               (MCU_2224_PORT144_PIN_REG)
#define SET_GPIO_PIN_E4(x)              (MCU_2224_PORT144_PIN_REG = (x))

#define GET_GPIO_PIN_G7()               (MCU_2225_PORT145_PIN_REG)
#define SET_GPIO_PIN_G7(x)              (MCU_2225_PORT145_PIN_REG = (x))

#define GET_GPIO_PIN_A2()               (MCU_2226_PORT146_PIN_REG)
#define SET_GPIO_PIN_A2(x)              (MCU_2226_PORT146_PIN_REG = (x))

#define GET_GPIO_PIN_B3()               (MCU_2227_PORT147_PIN_REG)
#define SET_GPIO_PIN_B3(x)              (MCU_2227_PORT147_PIN_REG = (x))

#define GET_GPIO_PIN_B2()               (MCU_2228_PORT150_PIN_REG)
#define SET_GPIO_PIN_B2(x)              (MCU_2228_PORT150_PIN_REG = (x))

#define GET_GPIO_PIN_A4()               (MCU_2229_PORT151_PIN_REG)
#define SET_GPIO_PIN_A4(x)              (MCU_2229_PORT151_PIN_REG = (x))

#define GET_GPIO_PIN_A3()               (MCU_222A_PORT152_PIN_REG)
#define SET_GPIO_PIN_A3(x)              (MCU_222A_PORT152_PIN_REG = (x))

#define GET_GPIO_PIN_G5()               (MCU_222B_PORT153_PIN_REG)
#define SET_GPIO_PIN_G5(x)              (MCU_222B_PORT153_PIN_REG = (x))

#define GET_GPIO_PIN_F4()               (MCU_222C_PORT154_PIN_REG)
#define SET_GPIO_PIN_F4(x)              (MCU_222C_PORT154_PIN_REG = (x))

#define GET_GPIO_PIN_H5()               (MCU_222D_PORT155_PIN_REG)
#define SET_GPIO_PIN_H5(x)              (MCU_222D_PORT155_PIN_REG = (x))

#define GET_GPIO_PIN_F3()               (MCU_222E_PORT156_PIN_REG)
#define SET_GPIO_PIN_F3(x)              (MCU_222E_PORT156_PIN_REG = (x))


//--------------------------------------------------
// SARADC Mapping
//--------------------------------------------------
#define GET_SARADC_0_0_VALUE()          (MCU_FD3B_ADC_A0_CONVERT_RESULT)
#define GET_SARADC_0_1_VALUE()          (MCU_FD3C_ADC_A1_CONVERT_RESULT)
#define GET_SARADC_0_2_VALUE()          (MCU_FD3D_ADC_A2_CONVERT_RESULT)
#define GET_SARADC_0_3_VALUE()          (MCU_FD3E_ADC_A3_CONVERT_RESULT)

#define GET_SARADC_1_0_VALUE()          (MCU_FF09_ADC_A0_CONVERT_RESULT)
#define GET_SARADC_1_1_VALUE()          (MCU_FF0A_ADC_A1_CONVERT_RESULT)
#define GET_SARADC_1_2_VALUE()          (MCU_FF0B_ADC_A2_CONVERT_RESULT)
#define GET_SARADC_1_3_VALUE()          (MCU_FF0C_ADC_A3_CONVERT_RESULT)

//--------------------------------------------------
// SPI Funtion Pinshare Config Option
//--------------------------------------------------
#define _PIN_SPI_CLK_SELECTED_0         ((_PIN_J4 == _PIN_J4_USB_SPI_CLK_0_4) || (_PIN_K4 == _PIN_K4_USB_SPI_CLK_0_5) || (_PIN_AA22_OFF_REGION == _PIN_AA22_USB_SPI_CLK_0_3) || (_PIN_AA23_OFF_REGION == _PIN_AA23_USB_SPI_CLK_0_1) || (_PIN_D5 == _PIN_D5_USB_SPI_CLK_0_6) || (_PIN_D4 == _PIN_D4_USB_SPI_CLK_0_7) || (_PIN_J9 == _PIN_J9_USB_SPI_CLK_0_2) || (_PIN_E11 == _PIN_E11_USB_SPI_CLK_0_0))
#define _PIN_SPI_CLK_SELECTED_1         ((_PIN_J4 == _PIN_J4_USB_SPI_CLK_1_4) || (_PIN_K4 == _PIN_K4_USB_SPI_CLK_1_5) || (_PIN_AA22_OFF_REGION == _PIN_AA22_USB_SPI_CLK_1_3) || (_PIN_AA23_OFF_REGION == _PIN_AA23_USB_SPI_CLK_1_1) || (_PIN_D5 == _PIN_D5_USB_SPI_CLK_1_6) || (_PIN_D4 == _PIN_D4_USB_SPI_CLK_1_7) || (_PIN_J9 == _PIN_J9_USB_SPI_CLK_1_2) || (_PIN_E11 == _PIN_E11_USB_SPI_CLK_1_0))
#define _PIN_SPI_CLK_SELECTED_2         ((_PIN_J4 == _PIN_J4_USB_SPI_CLK_2_4) || (_PIN_K4 == _PIN_K4_USB_SPI_CLK_2_5) || (_PIN_AA22_OFF_REGION == _PIN_AA22_USB_SPI_CLK_2_3) || (_PIN_AA23_OFF_REGION == _PIN_AA23_USB_SPI_CLK_2_1) || (_PIN_D5 == _PIN_D5_USB_SPI_CLK_2_6) || (_PIN_D4 == _PIN_D4_USB_SPI_CLK_2_7) || (_PIN_J9 == _PIN_J9_USB_SPI_CLK_2_2) || (_PIN_E11 == _PIN_E11_USB_SPI_CLK_2_0))
#define _PIN_SPI_SI_SELECTED_0          ((_PIN_W23_OFF_REGION == _PIN_W23_USB_SPI_SI_0_3) || (_PIN_Y24_OFF_REGION == _PIN_Y24_USB_SPI_SI_0_1) || (_PIN_E5 == _PIN_E5_USB_SPI_SI_0_2) || (_PIN_V4 == _PIN_V4_USB_SPI_SI_0_0))
#define _PIN_SPI_SI_SELECTED_1          ((_PIN_W23_OFF_REGION == _PIN_W23_USB_SPI_SI_1_3) || (_PIN_Y24_OFF_REGION == _PIN_Y24_USB_SPI_SI_1_1) || (_PIN_E5 == _PIN_E5_USB_SPI_SI_1_2) || (_PIN_V4 == _PIN_V4_USB_SPI_SI_1_0))
#define _PIN_SPI_SI_SELECTED_2          ((_PIN_W23_OFF_REGION == _PIN_W23_USB_SPI_SI_2_3) || (_PIN_Y24_OFF_REGION == _PIN_Y24_USB_SPI_SI_2_1) || (_PIN_E5 == _PIN_E5_USB_SPI_SI_2_2) || (_PIN_V4 == _PIN_V4_USB_SPI_SI_2_0))
#define _PIN_SPI_SO_SELECTED_0          ((_PIN_W22_OFF_REGION == _PIN_W22_USB_SPI_SO_0_3) || (_PIN_AA24_OFF_REGION == _PIN_AA24_USB_SPI_SO_0_1) || (_PIN_D12 == _PIN_D12_USB_SPI_SO_0_2) || (_PIN_U4 == _PIN_U4_USB_SPI_SO_0_0))
#define _PIN_SPI_SO_SELECTED_1          ((_PIN_W22_OFF_REGION == _PIN_W22_USB_SPI_SO_1_3) || (_PIN_AA24_OFF_REGION == _PIN_AA24_USB_SPI_SO_1_1) || (_PIN_D12 == _PIN_D12_USB_SPI_SO_1_2) || (_PIN_U4 == _PIN_U4_USB_SPI_SO_1_0))
#define _PIN_SPI_SO_SELECTED_2          ((_PIN_W22_OFF_REGION == _PIN_W22_USB_SPI_SO_2_3) || (_PIN_AA24_OFF_REGION == _PIN_AA24_USB_SPI_SO_2_1) || (_PIN_D12 == _PIN_D12_USB_SPI_SO_2_2) || (_PIN_U4 == _PIN_U4_USB_SPI_SO_2_0))
#define _PIN_SPI_CEB0_SELECTED_0        ((_PIN_AE26_OFF_REGION == _PIN_AE26_USB_SPI_CEB0_0_3) || (_PIN_Y25_OFF_REGION == _PIN_Y25_USB_SPI_CEB0_0_1) || (_PIN_D13 == _PIN_D13_USB_SPI_CEB0_0_2) || (_PIN_G8 == _PIN_G8_USB_SPI_CEB0_0_0))
#define _PIN_SPI_CEB0_SELECTED_1        ((_PIN_AE26_OFF_REGION == _PIN_AE26_USB_SPI_CEB0_1_3) || (_PIN_Y25_OFF_REGION == _PIN_Y25_USB_SPI_CEB0_1_1) || (_PIN_D13 == _PIN_D13_USB_SPI_CEB0_1_2) || (_PIN_G8 == _PIN_G8_USB_SPI_CEB0_1_0))
#define _PIN_SPI_CEB0_SELECTED_2        ((_PIN_AE26_OFF_REGION == _PIN_AE26_USB_SPI_CEB0_2_3) || (_PIN_Y25_OFF_REGION == _PIN_Y25_USB_SPI_CEB0_2_1) || (_PIN_D13 == _PIN_D13_USB_SPI_CEB0_1_2) || (_PIN_G8 == _PIN_G8_USB_SPI_CEB0_2_0))
#define _PIN_SPI_CEB1_SELECTED_0        ((_PIN_AD26_OFF_REGION == _PIN_AD26_USB_SPI_CEB1_0_3) || (_PIN_AA25_OFF_REGION == _PIN_AA25_USB_SPI_CEB1_0_1) || (_PIN_H9 == _PIN_H9_USB_SPI_CEB1_0_2) || (_PIN_E4 == _PIN_E4_USB_SPI_CEB1_0_0))
#define _PIN_SPI_CEB1_SELECTED_1        ((_PIN_AD26_OFF_REGION == _PIN_AD26_USB_SPI_CEB1_1_3) || (_PIN_AA25_OFF_REGION == _PIN_AA25_USB_SPI_CEB1_1_1) || (_PIN_H9 == _PIN_H9_USB_SPI_CEB1_1_2) || (_PIN_E4 == _PIN_E4_USB_SPI_CEB1_1_0))
#define _PIN_SPI_CEB1_SELECTED_2        ((_PIN_AD26_OFF_REGION == _PIN_AD26_USB_SPI_CEB1_2_3) || (_PIN_AA25_OFF_REGION == _PIN_AA25_USB_SPI_CEB1_2_1) || (_PIN_H9 == _PIN_H9_USB_SPI_CEB1_2_2) || (_PIN_E4 == _PIN_E4_USB_SPI_CEB1_2_0))
