//--------------------------------------------------
// EMCU GPIO Control Part 2 (Page 22)
//--------------------------------------------------
#define P22_00_PORT100_PIN_REG                                                                                          0x2200
#define P22_01_PORT101_PIN_REG                                                                                          0x2201
#define P22_02_PORT102_PIN_REG                                                                                          0x2202
#define P22_03_PORT103_PIN_REG                                                                                          0x2203
#define P22_04_PORT104_PIN_REG                                                                                          0x2204
#define P22_05_PORT105_PIN_REG                                                                                          0x2205
#define P22_06_PORT106_PIN_REG                                                                                          0x2206
#define P22_07_PORT107_PIN_REG                                                                                          0x2207
#define P22_08_PORT110_PIN_REG                                                                                          0x2208
#define P22_09_PORT111_PIN_REG                                                                                          0x2209
#define P22_0A_PORT112_PIN_REG                                                                                          0x220A
#define P22_0B_PORT113_PIN_REG                                                                                          0x220B
#define P22_0C_PORT114_PIN_REG                                                                                          0x220C
#define P22_0D_PORT115_PIN_REG                                                                                          0x220D
#define P22_0E_PORT116_PIN_REG                                                                                          0x220E
#define P22_0F_PORT117_PIN_REG                                                                                          0x220F
#define P22_10_PORT120_PIN_REG                                                                                          0x2210
#define P22_11_PORT121_PIN_REG                                                                                          0x2211
#define P22_12_PORT122_PIN_REG                                                                                          0x2212
#define P22_13_PORT123_PIN_REG                                                                                          0x2213
#define P22_14_PORT124_PIN_REG                                                                                          0x2214
#define P22_15_PORT125_PIN_REG                                                                                          0x2215
#define P22_16_PORT126_PIN_REG                                                                                          0x2216
#define P22_17_PORT127_PIN_REG                                                                                          0x2217
#define P22_18_PORT130_PIN_REG                                                                                          0x2218
#define P22_19_PORT131_PIN_REG                                                                                          0x2219
#define P22_1A_PORT132_PIN_REG                                                                                          0x221A
#define P22_1B_PORT133_PIN_REG                                                                                          0x221B
#define P22_1C_PORT134_PIN_REG                                                                                          0x221C
#define P22_1D_PORT135_PIN_REG                                                                                          0x221D
#define P22_1E_PORT136_PIN_REG                                                                                          0x221E
#define P22_1F_PORT137_PIN_REG                                                                                          0x221F
#define P22_20_PORT140_PIN_REG                                                                                          0x2220
#define P22_21_PORT141_PIN_REG                                                                                          0x2221
#define P22_22_PORT142_PIN_REG                                                                                          0x2222
#define P22_23_PORT143_PIN_REG                                                                                          0x2223
#define P22_24_PORT144_PIN_REG                                                                                          0x2224
#define P22_25_PORT145_PIN_REG                                                                                          0x2225
#define P22_26_PORT146_PIN_REG                                                                                          0x2226
#define P22_27_PORT147_PIN_REG                                                                                          0x2227
#define P22_28_PORT150_PIN_REG                                                                                          0x2228
#define P22_29_PORT151_PIN_REG                                                                                          0x2229
#define P22_2A_PORT152_PIN_REG                                                                                          0x222A
#define P22_2B_PORT153_PIN_REG                                                                                          0x222B
#define P22_2C_PORT154_PIN_REG                                                                                          0x222C
#define P22_2D_PORT155_PIN_REG                                                                                          0x222D
#define P22_2E_PORT156_PIN_REG                                                                                          0x222E
#define P22_9A_PORT_READ_CONTROL_3                                                                                      0x229A


//--------------------------------------------------
// EMCU DDC-CI Part 3 (Page FD)
//--------------------------------------------------
#define PFD_00_IIC_4_CH_SEL                                                                                             0xFD00
#define PFD_01_IIC_4_SET_SLAVE                                                                                          0xFD01
#define PFD_02_IIC_4_SUB_IN                                                                                             0xFD02
#define PFD_03_IIC_4_DATA_IN                                                                                            0xFD03
#define PFD_04_IIC_4_DATA_OUT                                                                                           0xFD04
#define PFD_05_IIC_4_STATUS                                                                                             0xFD05
#define PFD_06_IIC_4_IRQ_CONTROL                                                                                        0xFD06
#define PFD_07_IIC_4_STATUS2                                                                                            0xFD07
#define PFD_08_IIC_4_IRQ_CONTROL2                                                                                       0xFD08
#define PFD_09_IIC_4_CHANNEL_CONTROL                                                                                    0xFD09
#define PFD_0A_DDCCI_4_NULL_BYTE1                                                                                       0xFD0A
#define PFD_0B_DDCCI_4_NULL_BYTE2                                                                                       0xFD0B
#define PFD_0C_DDCCI_4_NULL_BYTE3                                                                                       0xFD0C
#define PFD_0D_DDCCI_4_REMAIN_DATA                                                                                      0xFD0D


//--------------------------------------------------
// EMCU IROM Access Port (Page FD)
//--------------------------------------------------
#define PFD_10_IROM_BIST_MISR_4                                                                                         0xFD10
#define PFD_11_IROM_BIST_MISR_5                                                                                         0xFD11
#define PFD_12_IROM_BIST_MISR_6                                                                                         0xFD12
#define PFD_13_IROM_BIST_MISR_7                                                                                         0xFD13
#define PFD_46_EMCU_IROM_MARGIN_CTRL                                                                                    0xFD46
#define PFD_47_IROM_ACCESS_PORT                                                                                         0xFD47
#define PFD_48_IROM_ACCESS_ADDR_L                                                                                       0xFD48
#define PFD_49_IROM_ACCESS_ADDR_H                                                                                       0xFD49
#define PFD_4A_IROM_ACCESS_CTRL                                                                                         0xFD4A
#define PFD_4B_IROM_BIST_CTRL                                                                                           0xFD4B
#define PFD_4C_IROM_BIST_MISR_0                                                                                         0xFD4C
#define PFD_4D_IROM_BIST_MISR_1                                                                                         0xFD4D
#define PFD_4E_IROM_BIST_MISR_2                                                                                         0xFD4E
#define PFD_4F_IROM_BIST_MISR_3                                                                                         0xFD4F


//--------------------------------------------------
// EMCU ROM Mode Setting (Page FD)
//--------------------------------------------------
#define PFD_21_FLASH_STATUS_CHECK                                                                                       0xFD21
#define PFD_22_FLASH_STATUS_CHECK_1                                                                                     0xFD22
#define PFD_23_FLASH_CHECK_VALUE_0                                                                                      0xFD23
#define PFD_24_FLASH_CHECK_VALUE_1                                                                                      0xFD24
#define PFD_25_FLASH_CHECK_VALUE2_0                                                                                     0xFD25
#define PFD_26_FLASH_CHECK_VALUE2_1                                                                                     0xFD26
#define PFD_27_BOOTUP_BANK_START                                                                                        0xFD27


//--------------------------------------------------
// EMCU LSADC Module 2 (Page FD)
//--------------------------------------------------
#define PFD_39_ADC_ANALOG_CONFIG                                                                                        0xFD39
#define PFD_3A_ADC_ACONTROL                                                                                             0xFD3A
#define PFD_3B_ADC_A0_CONVERT_RESULT                                                                                    0xFD3B
#define PFD_3C_ADC_A1_CONVERT_RESULT                                                                                    0xFD3C
#define PFD_3D_ADC_A2_CONVERT_RESULT                                                                                    0xFD3D
#define PFD_3E_ADC_A3_CONVERT_RESULT                                                                                    0xFD3E
#define PFD_3F_ADC_CLK_DIV                                                                                              0xFD3F
#define PFD_40_AUTO_MODE_CTRL01                                                                                         0xFD40
#define PFD_F7_ADC0_THRESHOLD_H                                                                                         0xFDF7
#define PFD_F8_ADC0_THRESHOLD_L                                                                                         0xFDF8
#define PFD_F9_ADC1_THRESHOLD_H                                                                                         0xFDF9
#define PFD_FA_ADC1_THRESHOLD_L                                                                                         0xFDFA
#define PFD_FB_ADC2_THRESHOLD_H                                                                                         0xFDFB
#define PFD_FC_ADC2_THRESHOLD_L                                                                                         0xFDFC
#define PFD_FD_ADC3_THRESHOLD_H                                                                                         0xFDFD
#define PFD_FE_ADC3_THRESHOLD_L                                                                                         0xFDFE
#define PFD_FF_CTRL0_WAIT_TIME_VALUE                                                                                    0xFDFF


//--------------------------------------------------
// CPU Interoperate Control (Page FD)
//--------------------------------------------------
#define PFD_57_MCU_FLASH_BYPASS_MODE                                                                                    0xFD57


//--------------------------------------------------
// EMCU IDCC (Page FD)
//--------------------------------------------------
#define PFD_80_IDCC3_CONTROL0                                                                                           0xFD80
#define PFD_81_IDCC3_CONTROL1                                                                                           0xFD81
#define PFD_82_IDCC3_STATUS                                                                                             0xFD82
#define PFD_83_IDCC3_OFFSET_IN                                                                                          0xFD83
#define PFD_84_IDCC3_LENGTH_IN                                                                                          0xFD84
#define PFD_85_IDCC3_WRITE_ADDR_H                                                                                       0xFD85
#define PFD_86_IDCC3_WRITE_ADDR_L                                                                                       0xFD86
#define PFD_87_IDCC3_READ_ADDR_H                                                                                        0xFD87
#define PFD_88_IDCC3_READ_ADDR_L                                                                                        0xFD88
#define PFD_89_IDCC3_DUMMY1                                                                                             0xFD89
#define PFD_8A_IDCC3_DUMMY2                                                                                             0xFD8A
#define PFD_8B_IDCC3_DUMMY3                                                                                             0xFD8B
#define PFD_A0_IDCC4_CONTROL0                                                                                           0xFDA0
#define PFD_A1_IDCC4_CONTROL1                                                                                           0xFDA1
#define PFD_A2_IDCC4_STATUS                                                                                             0xFDA2
#define PFD_A3_IDCC4_OFFSET_IN                                                                                          0xFDA3
#define PFD_A4_IDCC4_LENGTH_IN                                                                                          0xFDA4
#define PFD_A5_IDCC4_WRITE_ADDR_H                                                                                       0xFDA5
#define PFD_A6_IDCC4_WRITE_ADDR_L                                                                                       0xFDA6
#define PFD_A7_IDCC4_READ_ADDR_H                                                                                        0xFDA7
#define PFD_A8_IDCC4_READ_ADDR_L                                                                                        0xFDA8
#define PFD_A9_IDCC4_DUMMY1                                                                                             0xFDA9
#define PFD_AA_IDCC4_DUMMY2                                                                                             0xFDAA
#define PFD_AB_IDCC4_DUMMY3                                                                                             0xFDAB


//--------------------------------------------------
// Background ISP Speed Up (Page FD)
//--------------------------------------------------
#define PFD_90_BACKGROUND_ISP_CTRL                                                                                      0xFD90
#define PFD_91_BACKGROUND_ISP_STATUS                                                                                    0xFD91
#define PFD_92_BACKGROUND_ISP_SLAVE_ADDRESS                                                                             0xFD92
#define PFD_93_BACKGROUND_ISP_SUB_ADDRESS                                                                               0xFD93
#define PFD_94_BACKGROUND_ISP_ADDR_4TH                                                                                  0xFD94
#define PFD_95_BACKGROUND_ISP_ADDR_H                                                                                    0xFD95
#define PFD_96_BACKGROUND_ISP_ADDR_M                                                                                    0xFD96
#define PFD_97_BACKGROUND_ISP_ADDR_L                                                                                    0xFD97
#define PFD_98_BACKGROUND_ISP_LENGTH                                                                                    0xFD98
#define PFD_99_BACKGROUND_ISP_DUMMY1                                                                                    0xFD99
#define PFD_9A_BACKGROUND_ISP_DUMMY2                                                                                    0xFD9A


//--------------------------------------------------
// EMCU 8to32bits Interface (Page FD)
//--------------------------------------------------
#define PFD_D0_EMCU_TO32B_INF_GRP0_A3                                                                                   0xFDD0
#define PFD_D1_EMCU_TO32B_INF_GRP0_A2                                                                                   0xFDD1
#define PFD_D2_EMCU_TO32B_INF_GRP0_A1                                                                                   0xFDD2
#define PFD_D3_EMCU_TO32B_INF_GRP0_A0                                                                                   0xFDD3
#define PFD_D4_EMCU_TO32B_INF_GRP0_D3                                                                                   0xFDD4
#define PFD_D5_EMCU_TO32B_INF_GRP0_D2                                                                                   0xFDD5
#define PFD_D6_EMCU_TO32B_INF_GRP0_D1                                                                                   0xFDD6
#define PFD_D7_EMCU_TO32B_INF_GRP0_D0                                                                                   0xFDD7
#define PFD_D8_EMCU_TO32B_INF_GRP1_A3                                                                                   0xFDD8
#define PFD_D9_EMCU_TO32B_INF_GRP1_A2                                                                                   0xFDD9
#define PFD_DA_EMCU_TO32B_INF_GRP1_A1                                                                                   0xFDDA
#define PFD_DB_EMCU_TO32B_INF_GRP1_A0                                                                                   0xFDDB
#define PFD_DC_EMCU_TO32B_INF_GRP1_D3                                                                                   0xFDDC
#define PFD_DD_EMCU_TO32B_INF_GRP1_D2                                                                                   0xFDDD
#define PFD_DE_EMCU_TO32B_INF_GRP1_D1                                                                                   0xFDDE
#define PFD_DF_EMCU_TO32B_INF_GRP1_D0                                                                                   0xFDDF
#define PFD_E0_EMCU_TO32B_INF_ADDR3                                                                                     0xFDE0
#define PFD_E1_EMCU_TO32B_INF_ADDR2                                                                                     0xFDE1
#define PFD_E2_EMCU_TO32B_INF_ADDR1                                                                                     0xFDE2
#define PFD_E3_EMCU_TO32B_INF_ADDR0                                                                                     0xFDE3
#define PFD_E4_EMCU_TO32B_INF_DATA                                                                                      0xFDE4
#define PFD_E5_EMCU_TO32B_INF_CTRL                                                                                      0xFDE5
#define PFD_E6_EMCU_TO32_INF_WR                                                                                         0xFDE6
#define PFD_E7_EMCU_TO32_INF_RD                                                                                         0xFDE7
#define PFD_E8_BURST_WRITE_CTRL                                                                                         0xFDE8
#define PFD_E9_EMCU_TO32_INF_DUMMY0                                                                                     0xFDE9
#define PFD_EA_EMCU_TO32_INF_DUMMY1                                                                                     0xFDEA
#define PFD_EB_EMCU_TO32_INF_DUMMY2                                                                                     0xFDEB


//--------------------------------------------------
// EMCU GPIO Control Part 1 (Page FE)
//--------------------------------------------------
#define PFE_00_PORT40_PIN_REG                                                                                           0xFE00
#define PFE_01_PORT41_PIN_REG                                                                                           0xFE01
#define PFE_02_PORT42_PIN_REG                                                                                           0xFE02
#define PFE_03_PORT43_PIN_REG                                                                                           0xFE03
#define PFE_04_PORT44_PIN_REG                                                                                           0xFE04
#define PFE_05_PORT45_PIN_REG                                                                                           0xFE05
#define PFE_06_PORT46_PIN_REG                                                                                           0xFE06
#define PFE_07_PORT47_PIN_REG                                                                                           0xFE07
#define PFE_08_PORT50_PIN_REG                                                                                           0xFE08
#define PFE_09_PORT51_PIN_REG                                                                                           0xFE09
#define PFE_0A_PORT52_PIN_REG                                                                                           0xFE0A
#define PFE_0B_PORT53_PIN_REG                                                                                           0xFE0B
#define PFE_0C_PORT54_PIN_REG                                                                                           0xFE0C
#define PFE_0D_PORT55_PIN_REG                                                                                           0xFE0D
#define PFE_0E_PORT56_PIN_REG                                                                                           0xFE0E
#define PFE_0F_PORT57_PIN_REG                                                                                           0xFE0F
#define PFE_10_PORT60_PIN_REG                                                                                           0xFE10
#define PFE_11_PORT61_PIN_REG                                                                                           0xFE11
#define PFE_12_PORT62_PIN_REG                                                                                           0xFE12
#define PFE_13_PORT63_PIN_REG                                                                                           0xFE13
#define PFE_14_PORT64_PIN_REG                                                                                           0xFE14
#define PFE_15_PORT65_PIN_REG                                                                                           0xFE15
#define PFE_16_PORT66_PIN_REG                                                                                           0xFE16
#define PFE_17_PORT67_PIN_REG                                                                                           0xFE17
#define PFE_18_PORT70_PIN_REG                                                                                           0xFE18
#define PFE_19_PORT71_PIN_REG                                                                                           0xFE19
#define PFE_1A_PORT72_PIN_REG                                                                                           0xFE1A
#define PFE_1B_PORT73_PIN_REG                                                                                           0xFE1B
#define PFE_1C_PORT74_PIN_REG                                                                                           0xFE1C
#define PFE_1D_PORT75_PIN_REG                                                                                           0xFE1D
#define PFE_1E_PORT76_PIN_REG                                                                                           0xFE1E
#define PFE_1F_PORT77_PIN_REG                                                                                           0xFE1F
#define PFE_20_PORT80_PIN_REG                                                                                           0xFE20
#define PFE_21_PORT81_PIN_REG                                                                                           0xFE21
#define PFE_22_PORT82_PIN_REG                                                                                           0xFE22
#define PFE_23_PORT83_PIN_REG                                                                                           0xFE23
#define PFE_24_PORT84_PIN_REG                                                                                           0xFE24
#define PFE_25_PORT85_PIN_REG                                                                                           0xFE25
#define PFE_26_PORT86_PIN_REG                                                                                           0xFE26
#define PFE_27_PORT87_PIN_REG                                                                                           0xFE27
#define PFE_28_PORT90_PIN_REG                                                                                           0xFE28
#define PFE_29_PORT91_PIN_REG                                                                                           0xFE29
#define PFE_2A_PORT92_PIN_REG                                                                                           0xFE2A
#define PFE_2B_PORT93_PIN_REG                                                                                           0xFE2B
#define PFE_2C_PORT94_PIN_REG                                                                                           0xFE2C
#define PFE_2D_PORT95_PIN_REG                                                                                           0xFE2D
#define PFE_2E_PORT96_PIN_REG                                                                                           0xFE2E
#define PFE_2F_PORT97_PIN_REG                                                                                           0xFE2F
#define PFE_30_PORTA0_PIN_REG                                                                                           0xFE30
#define PFE_31_PORTA1_PIN_REG                                                                                           0xFE31
#define PFE_32_PORTA2_PIN_REG                                                                                           0xFE32
#define PFE_33_PORTA3_PIN_REG                                                                                           0xFE33
#define PFE_34_PORTA4_PIN_REG                                                                                           0xFE34
#define PFE_35_PORTA5_PIN_REG                                                                                           0xFE35
#define PFE_36_PORTA6_PIN_REG                                                                                           0xFE36
#define PFE_37_PORTA7_PIN_REG                                                                                           0xFE37
#define PFE_38_PORTB0_PIN_REG                                                                                           0xFE38
#define PFE_39_PORTB1_PIN_REG                                                                                           0xFE39
#define PFE_3A_PORTB2_PIN_REG                                                                                           0xFE3A
#define PFE_3B_PORTB3_PIN_REG                                                                                           0xFE3B
#define PFE_3C_PORTB4_PIN_REG                                                                                           0xFE3C
#define PFE_3D_PORTB5_PIN_REG                                                                                           0xFE3D
#define PFE_3E_PORTB6_PIN_REG                                                                                           0xFE3E
#define PFE_3F_PORTB7_PIN_REG                                                                                           0xFE3F
#define PFE_40_PORTC0_PIN_REG                                                                                           0xFE40
#define PFE_41_PORTC1_PIN_REG                                                                                           0xFE41
#define PFE_42_PORTC2_PIN_REG                                                                                           0xFE42
#define PFE_43_PORTC3_PIN_REG                                                                                           0xFE43
#define PFE_44_PORTC4_PIN_REG                                                                                           0xFE44
#define PFE_45_PORTC5_PIN_REG                                                                                           0xFE45
#define PFE_46_PORTC6_PIN_REG                                                                                           0xFE46
#define PFE_47_PORTC7_PIN_REG                                                                                           0xFE47
#define PFE_48_PORTD0_PIN_REG                                                                                           0xFE48
#define PFE_49_PORTD1_PIN_REG                                                                                           0xFE49
#define PFE_4A_PORTD2_PIN_REG                                                                                           0xFE4A
#define PFE_4B_PORTD3_PIN_REG                                                                                           0xFE4B
#define PFE_4C_PORTD4_PIN_REG                                                                                           0xFE4C
#define PFE_4D_PORTD5_PIN_REG                                                                                           0xFE4D
#define PFE_4E_PORTD6_PIN_REG                                                                                           0xFE4E
#define PFE_4F_PORTD7_PIN_REG                                                                                           0xFE4F
#define PFE_50_PORTE0_PIN_REG                                                                                           0xFE50
#define PFE_51_PORTE1_PIN_REG                                                                                           0xFE51
#define PFE_52_PORTE2_PIN_REG                                                                                           0xFE52
#define PFE_53_PORTE3_PIN_REG                                                                                           0xFE53
#define PFE_54_PORTE4_PIN_REG                                                                                           0xFE54
#define PFE_55_PORTE5_PIN_REG                                                                                           0xFE55
#define PFE_56_PORTE6_PIN_REG                                                                                           0xFE56
#define PFE_57_PORTE7_PIN_REG                                                                                           0xFE57
#define PFE_58_PORTF0_PIN_REG                                                                                           0xFE58
#define PFE_59_PORTF1_PIN_REG                                                                                           0xFE59
#define PFE_5A_PORTF2_PIN_REG                                                                                           0xFE5A
#define PFE_5B_PORTF3_PIN_REG                                                                                           0xFE5B
#define PFE_5C_PORTF4_PIN_REG                                                                                           0xFE5C
#define PFE_5D_PORTF5_PIN_REG                                                                                           0xFE5D
#define PFE_5E_PORTF6_PIN_REG                                                                                           0xFE5E
#define PFE_5F_PORTF7_PIN_REG                                                                                           0xFE5F
#define PFE_60_PORT_READ_CONTROL                                                                                        0xFE60
#define PFE_61_PORT_READ_CONTROL_2                                                                                      0xFE61


//--------------------------------------------------
// EMCU DDC Part 0 (Page FE)
//--------------------------------------------------
#define PFE_62_DDC2_SEGMENT_ADDRESS                                                                                     0xFE62
#define PFE_63_DDC2_SEGMENT_DATA                                                                                        0xFE63
#define PFE_64_DDC2_DDC_ENABLE                                                                                          0xFE64
#define PFE_65_DDC2_DDC_CONTROL_1                                                                                       0xFE65
#define PFE_66_DDC2_DDC_CONTROL_2                                                                                       0xFE66
#define PFE_67_DDC2_DDC_INDEX                                                                                           0xFE67
#define PFE_68_DDC2_DDC_ACCESS_PORT                                                                                     0xFE68
#define PFE_69_DDC2_EDID_IRQ                                                                                            0xFE69
#define PFE_6A_DDC2_RESERVED                                                                                            0xFE6A
#define PFE_6B_DDC3_SEGMENT_ADDRESS                                                                                     0xFE6B
#define PFE_6C_DDC3_SEGMENT_DATA                                                                                        0xFE6C
#define PFE_6D_DDC3_DDC_ENABLE                                                                                          0xFE6D
#define PFE_6E_DDC3_DDC_CONTROL_1                                                                                       0xFE6E
#define PFE_6F_DDC3_DDC_CONTROL_2                                                                                       0xFE6F
#define PFE_70_DDC3_DDC_INDEX                                                                                           0xFE70
#define PFE_71_DDC3_DDC_ACCESS_PORT                                                                                     0xFE71
#define PFE_72_DDC3_EDID_IRQ                                                                                            0xFE72
#define PFE_73_DDC3_RESERVED                                                                                            0xFE73
#define PFE_74_DDC4_SEGMENT_ADDRESS                                                                                     0xFE74
#define PFE_75_DDC4_SEGMENT_DATA                                                                                        0xFE75
#define PFE_76_DDC4_DDC_ENABLE                                                                                          0xFE76
#define PFE_77_DDC4_DDC_CONTROL_1                                                                                       0xFE77
#define PFE_78_DDC4_DDC_CONTROL_2                                                                                       0xFE78
#define PFE_79_DDC4_DDC_INDEX                                                                                           0xFE79
#define PFE_7A_DDC4_DDC_ACCESS_PORT                                                                                     0xFE7A
#define PFE_7B_DDC4_EDID_IRQ                                                                                            0xFE7B
#define PFE_7C_DDC4_RESERVED                                                                                            0xFE7C


//--------------------------------------------------
// EMCU DDC-CI Part 0 (Page FE)
//--------------------------------------------------
#define PFE_86_IIC_1_CH_SEL                                                                                             0xFE86
#define PFE_87_IIC_1_SET_SLAVE                                                                                          0xFE87
#define PFE_88_IIC_1_SUB_IN                                                                                             0xFE88
#define PFE_89_IIC_1_DATA_IN                                                                                            0xFE89
#define PFE_8A_IIC_1_DATA_OUT                                                                                           0xFE8A
#define PFE_8B_IIC_1_STATUS                                                                                             0xFE8B
#define PFE_8C_IIC_1_IRQ_CONTROL                                                                                        0xFE8C
#define PFE_8D_IIC_1_STATUS2                                                                                            0xFE8D
#define PFE_8E_IIC_1_IRQ_CONTROL2                                                                                       0xFE8E
#define PFE_8F_IIC_1_CHANNEL_CONTROL                                                                                    0xFE8F
#define PFE_90_DDCCI_1_NULL_BYTE1                                                                                       0xFE90
#define PFE_91_DDCCI_1_NULL_BYTE2                                                                                       0xFE91
#define PFE_92_DDCCI_1_NULL_BYTE3                                                                                       0xFE92
#define PFE_93_DDCCI_1_REMAIN_DATA                                                                                      0xFE93


//--------------------------------------------------
// EMCU XRAM Bist Settings (Page FE)
//--------------------------------------------------
#define PFE_B2_XRAM_BIST_CTRL                                                                                           0xFEB2
#define PFE_B3_XRAM_DRF_BIST_CTRL                                                                                       0xFEB3
#define PFE_B4_EMCU_SRAM_MARGIN_CTRL                                                                                    0xFEB4


//--------------------------------------------------
// EMCU DDCRAM Settings (Page FE)
//--------------------------------------------------
#define PFE_B9_DDC_DID_CTRL                                                                                             0xFEB9
#define PFE_BA_DDC0_DDCRAM_SEL                                                                                          0xFEBA
#define PFE_BB_DDC0_DXINFO_B0_DID                                                                                       0xFEBB
#define PFE_BC_DDC0_DXINFO_B1_DID                                                                                       0xFEBC
#define PFE_BD_DDC0_DXINFO_OFFSL_DID                                                                                    0xFEBD
#define PFE_BE_DDC0_DXINFO_B0_EDID                                                                                      0xFEBE
#define PFE_BF_DDC0_DXINFO_B1_EDID                                                                                      0xFEBF
#define PFE_C0_DDC0_DXINFO_OFFSL_EDID                                                                                   0xFEC0
#define PFE_C1_DDC0_CHECKSUM_DID                                                                                        0xFEC1
#define PFE_C2_DDC0_CHECKSUM_OFFSL_DID                                                                                  0xFEC2
#define PFE_C3_DDC0_CHECKSUM_EDID                                                                                       0xFEC3
#define PFE_C4_DDC0_CHECKSUM_OFFS_EDID                                                                                  0xFEC4
#define PFE_C5_DDC1_DDCRAM_SEL                                                                                          0xFEC5
#define PFE_C6_DDC1_DXINFO_B0_DID                                                                                       0xFEC6
#define PFE_C7_DDC1_DXINFO_B1_DID                                                                                       0xFEC7
#define PFE_C8_DDC1_DXINFO_OFFSL_DID                                                                                    0xFEC8
#define PFE_C9_DDC1_DXINFO_B0_EDID                                                                                      0xFEC9
#define PFE_CA_DDC1_DXINFO_B1_EDID                                                                                      0xFECA
#define PFE_CB_DDC1_DXINFO_OFFSL_EDID                                                                                   0xFECB
#define PFE_CC_DDC1_CHECKSUM_DID                                                                                        0xFECC
#define PFE_CD_DDC1_CHECKSUM_OFFSL_DID                                                                                  0xFECD
#define PFE_CE_DDC1_CHECKSUM_EDID                                                                                       0xFECE
#define PFE_CF_DDC1_CHECKSUM_OFFS_EDID                                                                                  0xFECF
#define PFE_D3_DDC2_DDCRAM_SEL                                                                                          0xFED3
#define PFE_D4_DDC2_DXINFO_D0_DID                                                                                       0xFED4
#define PFE_D5_DDC2_DXINFO_D1_DID                                                                                       0xFED5
#define PFE_D6_DDC2_DXINFO_OFFSL_DID                                                                                    0xFED6
#define PFE_D7_DDC2_DXINFO_D0_EDID                                                                                      0xFED7
#define PFE_D8_DDC2_DXINFO_D1_EDID                                                                                      0xFED8
#define PFE_D9_DDC2_DXINFO_OFFSL_EDID                                                                                   0xFED9
#define PFE_DA_DDC2_CHECKSUM_DID                                                                                        0xFEDA
#define PFE_DB_DDC2_CHECKSUM_OFFSL_DID                                                                                  0xFEDB
#define PFE_DC_DDC2_CHECKSUM_EDID                                                                                       0xFEDC
#define PFE_DD_DDC2_CHECKSUM_OFFS_EDID                                                                                  0xFEDD
#define PFE_DE_DDC3_DDCRAM_SEL                                                                                          0xFEDE
#define PFE_DF_DDC3_DXINFO_D0_DID                                                                                       0xFEDF
#define PFE_E0_DDC3_DXINFO_D1_DID                                                                                       0xFEE0
#define PFE_E1_DDC3_DXINFO_OFFSL_DID                                                                                    0xFEE1
#define PFE_E2_DDC3_DXINFO_D0_EDID                                                                                      0xFEE2
#define PFE_E3_DDC3_DXINFO_D1_EDID                                                                                      0xFEE3
#define PFE_E4_DDC3_DXINFO_OFFSL_EDID                                                                                   0xFEE4
#define PFE_E5_DDC3_CHECKSUM_DID                                                                                        0xFEE5
#define PFE_E6_DDC3_CHECKSUM_OFFSL_DID                                                                                  0xFEE6
#define PFE_E7_DDC3_CHECKSUM_EDID                                                                                       0xFEE7
#define PFE_E8_DDC3_CHECKSUM_OFFS_EDID                                                                                  0xFEE8
#define PFE_E9_DDC4_DDCRAM_SEL                                                                                          0xFEE9
#define PFE_EA_DDC4_DXINFO_D0_DID                                                                                       0xFEEA
#define PFE_EB_DDC4_DXINFO_D1_DID                                                                                       0xFEEB
#define PFE_EC_DDC4_DXINFO_OFFSL_DID                                                                                    0xFEEC
#define PFE_ED_DDC4_DXINFO_D0_EDID                                                                                      0xFEED
#define PFE_EE_DDC4_DXINFO_D1_EDID                                                                                      0xFEEE
#define PFE_EF_DDC4_DXINFO_OFFSL_EDID                                                                                   0xFEEF
#define PFE_F0_DDC4_CHECKSUM_DID                                                                                        0xFEF0
#define PFE_F1_DDC4_CHECKSUM_OFFSL_DID                                                                                  0xFEF1
#define PFE_F2_DDC4_CHECKSUM_EDID                                                                                       0xFEF2
#define PFE_F3_DDC4_CHECKSUM_OFFS_EDID                                                                                  0xFEF3
#define PFE_F4_DDCRAM_A_ADDRESS                                                                                         0xFEF4


//--------------------------------------------------
// 2 CPU Access Flash Setting (Page FE)
//--------------------------------------------------
#define PFE_FF_FLASH_ACCESS_ARBITER                                                                                     0xFEFF


//--------------------------------------------------
// EMCU LSADC (Page FF)
//--------------------------------------------------
#define PFF_02_ADC_ANALOG_CONFIG                                                                                        0xFF02
#define PFF_08_ADC_ACONTROL                                                                                             0xFF08
#define PFF_09_ADC_A0_CONVERT_RESULT                                                                                    0xFF09
#define PFF_0A_ADC_A1_CONVERT_RESULT                                                                                    0xFF0A
#define PFF_0B_ADC_A2_CONVERT_RESULT                                                                                    0xFF0B
#define PFF_0C_ADC_A3_CONVERT_RESULT                                                                                    0xFF0C
#define PFF_0D_ADC_CLK_DIV                                                                                              0xFF0D
#define PFF_0E_AUTO_MODE_CTRL01                                                                                         0xFF0E
#define PFF_0F_ADC0_THRESHOLD_H                                                                                         0xFF0F
#define PFF_10_ADC0_THRESHOLD_L                                                                                         0xFF10
#define PFF_11_ADC1_THRESHOLD_H                                                                                         0xFF11
#define PFF_12_ADC1_THRESHOLD_L                                                                                         0xFF12
#define PFF_13_ADC2_THRESHOLD_H                                                                                         0xFF13
#define PFF_14_ADC2_THRESHOLD_L                                                                                         0xFF14
#define PFF_15_ADC3_THRESHOLD_H                                                                                         0xFF15
#define PFF_16_ADC3_THRESHOLD_L                                                                                         0xFF16
#define PFF_17_CTRL0_WAIT_TIME_VALUE                                                                                    0xFF17


//--------------------------------------------------
// EMCU OSD Reorder Part 1 (Page FF)
//--------------------------------------------------
#define PFF_03_TRIPLE_BYTES_OPERATION                                                                                   0xFF03
#define PFF_04_SHIFT_BITS_NUMBER                                                                                        0xFF04
#define PFF_05_SHIFT_BYTE_ADDRESS                                                                                       0xFF05
#define PFF_06_INPUT_TRIPLE_BYTES                                                                                       0xFF06
#define PFF_07_RESULT_TRIPLE_BYTES                                                                                      0xFF07


//--------------------------------------------------
// EMCU OSD Reorder Part 2 (Page FF)
//--------------------------------------------------
#define PFF_18_BYTE_ADDRESS                                                                                             0xFF18


//--------------------------------------------------
// EMCU DDC Part 1 (Page FF)
//--------------------------------------------------
#define PFF_19_ADC_SEGMENT_ADDRESS                                                                                      0xFF19
#define PFF_1A_ADC_SEGMENT_DATA                                                                                         0xFF1A
#define PFF_1B_ADC_DDC_ENABLE                                                                                           0xFF1B
#define PFF_1C_ADC_DDC_CONTROL_1                                                                                        0xFF1C
#define PFF_1D_ADC_DDC_CONTROL_2                                                                                        0xFF1D
#define PFF_1E_DDC0_DDC_ENABLE                                                                                          0xFF1E
#define PFF_1F_DDC0_DDC_CONTROL_1                                                                                       0xFF1F
#define PFF_20_DDC0_DDC_CONTROL_2                                                                                       0xFF20


//--------------------------------------------------
// EMCU DDC-CI Part 1 (Page FF)
//--------------------------------------------------
#define PFF_22_IIC_CH_SEL                                                                                               0xFF22
#define PFF_23_IIC_SET_SLAVE                                                                                            0xFF23
#define PFF_24_IIC_SUB_IN                                                                                               0xFF24
#define PFF_25_IIC_DATA_IN                                                                                              0xFF25
#define PFF_26_IIC_DATA_OUT                                                                                             0xFF26
#define PFF_27_IIC_STATUS                                                                                               0xFF27
#define PFF_28_IIC_IRQ_CONTROL                                                                                          0xFF28
#define PFF_29_IIC_STATUS2                                                                                              0xFF29
#define PFF_2A_IIC_IRQ_CONTROL2                                                                                         0xFF2A
#define PFF_2B_IIC_CHANNEL_CONTROL                                                                                      0xFF2B


//--------------------------------------------------
// EMCU DDC Part 2 (Page FF)
//--------------------------------------------------
#define PFF_2C_DDC1_DDC_ENABLE                                                                                          0xFF2C
#define PFF_2D_DDC1_DDC_CONTROL_1                                                                                       0xFF2D
#define PFF_2E_DDC1_DDC_CONTROL_2                                                                                       0xFF2E
#define PFF_35_DDCCI_REMAIN_DATA                                                                                        0xFF35
#define PFF_36_DDC0_SEGMENT_ADDRESS                                                                                     0xFF36
#define PFF_37_DDC0_SEGMENT_DATA                                                                                        0xFF37
#define PFF_38_DDC1_SEGMENT_ADDRESS                                                                                     0xFF38
#define PFF_39_DDC1_SEGMENT_DATA                                                                                        0xFF39


//--------------------------------------------------
// EMCU PWM Part 1 (Page FF)
//--------------------------------------------------
#define PFF_3A_PWM_CK_SEL                                                                                               0xFF3A
#define PFF_3B_PWM03_M                                                                                                  0xFF3B
#define PFF_3C_PWM45_M                                                                                                  0xFF3C
#define PFF_3D_PWM01_N_MSB                                                                                              0xFF3D
#define PFF_3E_PWM0_N_LSB                                                                                               0xFF3E
#define PFF_3F_PWM1_N_LSB                                                                                               0xFF3F
#define PFF_40_PWM23_N_MSB                                                                                              0xFF40
#define PFF_41_PWM2_N_LSB                                                                                               0xFF41
#define PFF_42_PWM3_N_LSB                                                                                               0xFF42
#define PFF_43_PWM45_N_MSB                                                                                              0xFF43
#define PFF_44_PWM4_N_LSB                                                                                               0xFF44
#define PFF_45_PWM5_N_LSB                                                                                               0xFF45
#define PFF_46_PWML                                                                                                     0xFF46
#define PFF_47_PWM_VS_CTRL                                                                                              0xFF47
#define PFF_48_PWM_EN                                                                                                   0xFF48
#define PFF_49_PWM_CK                                                                                                   0xFF49
#define PFF_4A_PWM0H_DUT                                                                                                0xFF4A
#define PFF_4B_PWM1H_DUT                                                                                                0xFF4B
#define PFF_4C_PWM01L_DUT                                                                                               0xFF4C
#define PFF_4D_PWM2H_DUT                                                                                                0xFF4D
#define PFF_4E_PWM3H_DUT                                                                                                0xFF4E
#define PFF_4F_PWM23L_DUT                                                                                               0xFF4F
#define PFF_50_PWM4H_DUT                                                                                                0xFF50
#define PFF_51_PWM5H_DUT                                                                                                0xFF51
#define PFF_52_PWM45L_DUT                                                                                               0xFF52
#define PFF_53_PWM_DUT_TYPE                                                                                             0xFF53
#define PFF_54_PWM_CNT_MODE                                                                                             0xFF54


//--------------------------------------------------
// EMCU I2C Control Module (Page FF)
//--------------------------------------------------
#define PFF_55_I2CM_CR0                                                                                                 0xFF55
#define PFF_56_I2CM_CR1                                                                                                 0xFF56
#define PFF_57_I2CM_CR2                                                                                                 0xFF57
#define PFF_58_I2CM_CR3                                                                                                 0xFF58
#define PFF_59_I2CM_STR0                                                                                                0xFF59
#define PFF_5A_I2CM_STR1                                                                                                0xFF5A
#define PFF_5B_I2CM_STR2                                                                                                0xFF5B
#define PFF_5C_I2CM_STR3                                                                                                0xFF5C
#define PFF_5D_I2CM_SR                                                                                                  0xFF5D
#define PFF_5E_I2CM_TD                                                                                                  0xFF5E
#define PFF_5F_I2CM_CCR                                                                                                 0xFF5F
#define PFF_D7_I2CM_STR4                                                                                                0xFFD7
#define PFF_D8_I2CM_STR5                                                                                                0xFFD8


//--------------------------------------------------
// EMCU SPI-FLASH Part 1 (Page FF)
//--------------------------------------------------
#define PFF_60_COMMON_INST_EN                                                                                           0xFF60
#define PFF_61_COMMON_OP_CODE                                                                                           0xFF61
#define PFF_62_WREN_OP_CODE                                                                                             0xFF62
#define PFF_63_EWSR_OP_CODE                                                                                             0xFF63
#define PFF_64_FLASH_PROG_ISP0                                                                                          0xFF64
#define PFF_65_FLASH_PROG_ISP1                                                                                          0xFF65
#define PFF_66_FLASH_PROG_ISP2                                                                                          0xFF66
#define PFF_67_COMMON_INST_READ_PORT0                                                                                   0xFF67
#define PFF_68_COMMON_INST_READ_PORT1                                                                                   0xFF68
#define PFF_69_COMMON_INST_READ_PORT2                                                                                   0xFF69
#define PFF_6A_READ_OP_CODE                                                                                             0xFF6A
#define PFF_6B_FAST_READ_OP_CODE                                                                                        0xFF6B
#define PFF_6C_READ_INSTRUCTION                                                                                         0xFF6C
#define PFF_6D_PROGRAM_OP_CODE                                                                                          0xFF6D
#define PFF_6E_READ_STATUS_REGISTER_OP_CODE                                                                             0xFF6E
#define PFF_6F_PROGRAM_INSTRUCTION                                                                                      0xFF6F
#define PFF_70_PROGRAM_DATA_PORT                                                                                        0xFF70
#define PFF_71_PROGRAM_LENGTH                                                                                           0xFF71
#define PFF_72_CRC_END_ADDR0                                                                                            0xFF72
#define PFF_73_CRC_END_ADDR1                                                                                            0xFF73
#define PFF_74_CRC_END_ADDR2                                                                                            0xFF74
#define PFF_75_CRC_RESULT                                                                                               0xFF75
#define PFF_76_CEN_CTRL                                                                                                 0xFF76
#define PFF_77_REV_DUMMY4                                                                                               0xFF77
#define PFF_78_ACCESS_FLASH_ADDR_0                                                                                      0xFF78
#define PFF_79_ACCESS_FLASH_ADDR_1                                                                                      0xFF79
#define PFF_7A_ACCESS_FLASH_ADDR_2                                                                                      0xFF7A
#define PFF_7B_ACCESS_FLASH_DATA_PORT                                                                                   0xFF7B
#define PFF_7C_ACCESS_FLASH_DATA_CTRL                                                                                   0xFF7C
#define PFF_80_AAI_MODE_BYTE_NUM                                                                                        0xFF80
#define PFF_81_ISP_CMD_INSERT                                                                                           0xFF81
#define PFF_82_ISP_CMD_LENGTH                                                                                           0xFF82


//--------------------------------------------------
// EMCU DDC Part 4 (Page FF)
//--------------------------------------------------
#define PFF_7D_DDC_DID_IRQ_0                                                                                            0xFF7D
#define PFF_7E_DDC_DID_IRQ_1                                                                                            0xFF7E
#define PFF_7F_DDC_DID_IRQ_2                                                                                            0xFF7F


//--------------------------------------------------
// EMCU I2C Slave Module (Page FF)
//--------------------------------------------------
#define PFF_83_I2CS_CTRL0                                                                                               0xFF83
#define PFF_84_I2CS_CTRL1                                                                                               0xFF84
#define PFF_85_I2CS_CTRL2                                                                                               0xFF85
#define PFF_86_I2CS_STATUS0                                                                                             0xFF86
#define PFF_87_I2CS_STATUS1                                                                                             0xFF87
#define PFF_88_I2CS_BUFLEN                                                                                              0xFF88
#define PFF_A0_I2CS_STATUS_BYTE                                                                                         0xFFA0


//--------------------------------------------------
// EMCU I2C Slave Module Part 1 (Page FF)
//--------------------------------------------------
#define PFF_89_I2CS_CTRL0                                                                                               0xFF89
#define PFF_8A_I2CS_CTRL1                                                                                               0xFF8A
#define PFF_8B_I2CS_CTRL2                                                                                               0xFF8B
#define PFF_8C_I2CS_STATUS0                                                                                             0xFF8C
#define PFF_8D_I2CS_STATUS1                                                                                             0xFF8D
#define PFF_8E_I2CS_BUFLEN                                                                                              0xFF8E
#define PFF_A1_I2CS_STATUS_BYTE                                                                                         0xFFA1


//--------------------------------------------------
// EMCU PWM Part 2 (Page FF)
//--------------------------------------------------
#define PFF_90_PWM01_TOTALCNT_MSB                                                                                       0xFF90
#define PFF_91_PWM0_TOTALCNT_LSB                                                                                        0xFF91
#define PFF_92_PWM1_TOTALCNT_LSB                                                                                        0xFF92
#define PFF_93_PWM23_TOTALCNT_MSB                                                                                       0xFF93
#define PFF_94_PWM2_TOTALCNT_LSB                                                                                        0xFF94
#define PFF_95_PWM3_TOTALCNT_LSB                                                                                        0xFF95
#define PFF_96_PWM45_TOTALCNT_MSB                                                                                       0xFF96
#define PFF_97_PWM4_TOTALCNT_LSB                                                                                        0xFF97
#define PFF_98_PWM5_TOTALCNT_LSB                                                                                        0xFF98
#define PFF_99_PWM_CK_SEL_HS                                                                                            0xFF99
#define PFF_9A_PWM01_CYCLE_MAX                                                                                          0xFF9A
#define PFF_9B_PWM23_CYCLE_MAX                                                                                          0xFF9B
#define PFF_9C_PWM45_CYCLE_MAX                                                                                          0xFF9C


//--------------------------------------------------
// EMCU DDCCI Part 2 (Page FF)
//--------------------------------------------------
#define PFF_B1_DDCCI_NULL_BYTE1                                                                                         0xFFB1
#define PFF_B2_DDCCI_NULL_BYTE2                                                                                         0xFFB2
#define PFF_B3_DDCCI_NULL_BYTE3                                                                                         0xFFB3


//--------------------------------------------------
// EMCU SRAM Interface Control (Page FF)
//--------------------------------------------------
#define PFF_B4_SRAM_INF_DATA                                                                                            0xFFB4
#define PFF_B5_SRAM_INF_CONTROL                                                                                         0xFFB5
#define PFF_B6_SRAM_INF_ADDR                                                                                            0xFFB6


//--------------------------------------------------
// EMCU Interrupt Control Part 0 (Page FF)
//--------------------------------------------------
#define PFF_B8_EXT_INT0_CONTROL                                                                                         0xFFB8
#define PFF_B9_EXT_INT1_CONTROL                                                                                         0xFFB9


//--------------------------------------------------
// EMCU Test Mode (Page FF)
//--------------------------------------------------
#define PFF_BB_PERI_TEST                                                                                                0xFFBB
#define PFF_BC_CYCLE_GATING                                                                                             0xFFBC
#define PFF_BD_MCU_CLK_DIV_R                                                                                            0xFFBD


//--------------------------------------------------
// EMCU I2C Control Module Part 1 (Page FF)
//--------------------------------------------------
#define PFF_C5_I2CM_CR0                                                                                                 0xFFC5
#define PFF_C6_I2CM_CR1                                                                                                 0xFFC6
#define PFF_C7_I2CM_CR2                                                                                                 0xFFC7
#define PFF_C8_I2CM_CR3                                                                                                 0xFFC8
#define PFF_C9_I2CM_STR0                                                                                                0xFFC9
#define PFF_CA_I2CM_STR1                                                                                                0xFFCA
#define PFF_CB_I2CM_STR2                                                                                                0xFFCB
#define PFF_CC_I2CM_STR3                                                                                                0xFFCC
#define PFF_CD_I2CM_SR                                                                                                  0xFFCD
#define PFF_CE_I2CM_TD                                                                                                  0xFFCE
#define PFF_CF_I2CM_CCR                                                                                                 0xFFCF
#define PFF_D9_I2CM_STR4                                                                                                0xFFD9
#define PFF_DA_I2CM_STR5                                                                                                0xFFDA


//--------------------------------------------------
// EMCU DDCRAM Control (Page FF)
//--------------------------------------------------
#define PFF_D0_A_DDCRAM_CONTROL                                                                                         0xFFD0
#define PFF_D1_DDCRAM0_CONTROL                                                                                          0xFFD1
#define PFF_D2_DDCRAM1_CONTROL                                                                                          0xFFD2
#define PFF_D3_DDCRAM2_CONTROL                                                                                          0xFFD3
#define PFF_D4_DDCRAM3_CONTROL                                                                                          0xFFD4
#define PFF_D5_DDCRAM4_CONTROL                                                                                          0xFFD5


//--------------------------------------------------
// EMCU DDC Part 3 (Page FF)
//--------------------------------------------------
#define PFF_E4_DDC0_EDID_IRQ                                                                                            0xFFE4
#define PFF_E5_DDC1_EDID_IRQ                                                                                            0xFFE5
#define PFF_E7_VGA_EDID_IRQ                                                                                             0xFFE7


//--------------------------------------------------
// EMCU In System Programming Part 1 (Page FF)
//--------------------------------------------------
#define PFF_E8_ISP_CONTROL                                                                                              0xFFE8
#define PFF_E9_MCU_CLK_CONTROL_1                                                                                        0xFFE9


//--------------------------------------------------
// EMCU In System Programming Part 2 (Page FF)
//--------------------------------------------------
#define PFF_EC_ISP_SLAVE_ADDRESS                                                                                        0xFFEC
#define PFF_ED_MCU_CONTROL                                                                                              0xFFED
#define PFF_EE_MCU_CLOCK_CONTROL                                                                                        0xFFEE
#define PFF_EF_RAM_TEST                                                                                                 0xFFEF


//--------------------------------------------------
// EMCU Xdata-SPI-FLASH Write Protect (Page FF)
//--------------------------------------------------
#define PFF_F0_XDATA_SPI_FLASH_WRITE_PROTECT                                                                            0xFFF0
#define PFF_F1_SCA_WR_INTRVL                                                                                            0xFFF1
#define PFF_F2_PWM_I2C_CLOCK_STOP                                                                                       0xFFF2


//--------------------------------------------------
// EMCU Scalar Interface (Page FF)
//--------------------------------------------------
#define PFF_F3_SCA_INF_CONTROL                                                                                          0xFFF3
#define PFF_F4_SCA_INF_ADDR                                                                                             0xFFF4
#define PFF_F5_SCA_INF_DATA                                                                                             0xFFF5
#define PFF_F6_SCA_INF_BWR_ADRH                                                                                         0xFFF6
#define PFF_F7_SCA_INF_BWR_ADRM                                                                                         0xFFF7
#define PFF_F8_SCA_INF_BWR_ADRL                                                                                         0xFFF8
#define PFF_F9_SCA_INF_BWR_COUNT_H                                                                                      0xFFF9
#define PFF_FA_SCA_INF_BWR_COUNT_L                                                                                      0xFFFA
#define PFF_FB_SCA_INF_PERIOD                                                                                           0xFFFB


//--------------------------------------------------
// EMCU Bankswitch (Page FF)
//--------------------------------------------------
#define PFF_FC_BANK_SWICH_CONTROL                                                                                       0xFFFC


//--------------------------------------------------
// EMCU GPIO Control Part 2 (Page 22)
//--------------------------------------------------
#define MCU_2200_PORT100_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_00_PORT100_PIN_REG))))
#define MCU_2201_PORT101_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_01_PORT101_PIN_REG))))
#define MCU_2202_PORT102_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_02_PORT102_PIN_REG))))
#define MCU_2203_PORT103_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_03_PORT103_PIN_REG))))
#define MCU_2204_PORT104_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_04_PORT104_PIN_REG))))
#define MCU_2205_PORT105_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_05_PORT105_PIN_REG))))
#define MCU_2206_PORT106_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_06_PORT106_PIN_REG))))
#define MCU_2207_PORT107_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_07_PORT107_PIN_REG))))
#define MCU_2208_PORT110_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_08_PORT110_PIN_REG))))
#define MCU_2209_PORT111_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_09_PORT111_PIN_REG))))
#define MCU_220A_PORT112_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_0A_PORT112_PIN_REG))))
#define MCU_220B_PORT113_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_0B_PORT113_PIN_REG))))
#define MCU_220C_PORT114_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_0C_PORT114_PIN_REG))))
#define MCU_220D_PORT115_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_0D_PORT115_PIN_REG))))
#define MCU_220E_PORT116_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_0E_PORT116_PIN_REG))))
#define MCU_220F_PORT117_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_0F_PORT117_PIN_REG))))
#define MCU_2210_PORT120_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_10_PORT120_PIN_REG))))
#define MCU_2211_PORT121_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_11_PORT121_PIN_REG))))
#define MCU_2212_PORT122_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_12_PORT122_PIN_REG))))
#define MCU_2213_PORT123_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_13_PORT123_PIN_REG))))
#define MCU_2214_PORT124_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_14_PORT124_PIN_REG))))
#define MCU_2215_PORT125_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_15_PORT125_PIN_REG))))
#define MCU_2216_PORT126_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_16_PORT126_PIN_REG))))
#define MCU_2217_PORT127_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_17_PORT127_PIN_REG))))
#define MCU_2218_PORT130_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_18_PORT130_PIN_REG))))
#define MCU_2219_PORT131_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_19_PORT131_PIN_REG))))
#define MCU_221A_PORT132_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_1A_PORT132_PIN_REG))))
#define MCU_221B_PORT133_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_1B_PORT133_PIN_REG))))
#define MCU_221C_PORT134_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_1C_PORT134_PIN_REG))))
#define MCU_221D_PORT135_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_1D_PORT135_PIN_REG))))
#define MCU_221E_PORT136_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_1E_PORT136_PIN_REG))))
#define MCU_221F_PORT137_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_1F_PORT137_PIN_REG))))
#define MCU_2220_PORT140_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_20_PORT140_PIN_REG))))
#define MCU_2221_PORT141_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_21_PORT141_PIN_REG))))
#define MCU_2222_PORT142_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_22_PORT142_PIN_REG))))
#define MCU_2223_PORT143_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_23_PORT143_PIN_REG))))
#define MCU_2224_PORT144_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_24_PORT144_PIN_REG))))
#define MCU_2225_PORT145_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_25_PORT145_PIN_REG))))
#define MCU_2226_PORT146_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_26_PORT146_PIN_REG))))
#define MCU_2227_PORT147_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_27_PORT147_PIN_REG))))
#define MCU_2228_PORT150_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_28_PORT150_PIN_REG))))
#define MCU_2229_PORT151_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_29_PORT151_PIN_REG))))
#define MCU_222A_PORT152_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_2A_PORT152_PIN_REG))))
#define MCU_222B_PORT153_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_2B_PORT153_PIN_REG))))
#define MCU_222C_PORT154_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_2C_PORT154_PIN_REG))))
#define MCU_222D_PORT155_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_2D_PORT155_PIN_REG))))
#define MCU_222E_PORT156_PIN_REG                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(P22_2E_PORT156_PIN_REG))))
#define MCU_229A_PORT_READ_CONTROL_3                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(P22_9A_PORT_READ_CONTROL_3))))


//--------------------------------------------------
// EMCU DDC-CI Part 3 (Page FD)
//--------------------------------------------------
#define MCU_FD00_IIC_4_CH_SEL                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_00_IIC_4_CH_SEL))))
#define MCU_FD01_IIC_4_SET_SLAVE                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFD_01_IIC_4_SET_SLAVE))))
#define MCU_FD02_IIC_4_SUB_IN                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_02_IIC_4_SUB_IN))))
#define MCU_FD03_IIC_4_DATA_IN                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFD_03_IIC_4_DATA_IN))))
#define MCU_FD04_IIC_4_DATA_OUT                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFD_04_IIC_4_DATA_OUT))))
#define MCU_FD05_IIC_4_STATUS                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_05_IIC_4_STATUS))))
#define MCU_FD06_IIC_4_IRQ_CONTROL                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFD_06_IIC_4_IRQ_CONTROL))))
#define MCU_FD07_IIC_4_STATUS2                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFD_07_IIC_4_STATUS2))))
#define MCU_FD08_IIC_4_IRQ_CONTROL2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_08_IIC_4_IRQ_CONTROL2))))
#define MCU_FD09_IIC_4_CHANNEL_CONTROL                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_09_IIC_4_CHANNEL_CONTROL))))
#define MCU_FD0A_DDCCI_4_NULL_BYTE1                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_0A_DDCCI_4_NULL_BYTE1))))
#define MCU_FD0B_DDCCI_4_NULL_BYTE2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_0B_DDCCI_4_NULL_BYTE2))))
#define MCU_FD0C_DDCCI_4_NULL_BYTE3                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_0C_DDCCI_4_NULL_BYTE3))))
#define MCU_FD0D_DDCCI_4_REMAIN_DATA                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFD_0D_DDCCI_4_REMAIN_DATA))))


//--------------------------------------------------
// EMCU IROM Access Port (Page FD)
//--------------------------------------------------
#define MCU_FD10_IROM_BIST_MISR_4                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_10_IROM_BIST_MISR_4))))
#define MCU_FD11_IROM_BIST_MISR_5                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_11_IROM_BIST_MISR_5))))
#define MCU_FD12_IROM_BIST_MISR_6                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_12_IROM_BIST_MISR_6))))
#define MCU_FD13_IROM_BIST_MISR_7                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_13_IROM_BIST_MISR_7))))
#define MCU_FD46_EMCU_IROM_MARGIN_CTRL                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_46_EMCU_IROM_MARGIN_CTRL))))
#define MCU_FD47_IROM_ACCESS_PORT                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_47_IROM_ACCESS_PORT))))
#define MCU_FD48_IROM_ACCESS_ADDR_L                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_48_IROM_ACCESS_ADDR_L))))
#define MCU_FD49_IROM_ACCESS_ADDR_H                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_49_IROM_ACCESS_ADDR_H))))
#define MCU_FD4A_IROM_ACCESS_CTRL                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_4A_IROM_ACCESS_CTRL))))
#define MCU_FD4B_IROM_BIST_CTRL                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFD_4B_IROM_BIST_CTRL))))
#define MCU_FD4C_IROM_BIST_MISR_0                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_4C_IROM_BIST_MISR_0))))
#define MCU_FD4D_IROM_BIST_MISR_1                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_4D_IROM_BIST_MISR_1))))
#define MCU_FD4E_IROM_BIST_MISR_2                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_4E_IROM_BIST_MISR_2))))
#define MCU_FD4F_IROM_BIST_MISR_3                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_4F_IROM_BIST_MISR_3))))


//--------------------------------------------------
// EMCU ROM Mode Setting (Page FD)
//--------------------------------------------------
#define MCU_FD21_FLASH_STATUS_CHECK                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_21_FLASH_STATUS_CHECK))))
#define MCU_FD22_FLASH_STATUS_CHECK_1                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_22_FLASH_STATUS_CHECK_1))))
#define MCU_FD23_FLASH_CHECK_VALUE_0                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFD_23_FLASH_CHECK_VALUE_0))))
#define MCU_FD24_FLASH_CHECK_VALUE_1                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFD_24_FLASH_CHECK_VALUE_1))))
#define MCU_FD25_FLASH_CHECK_VALUE2_0                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_25_FLASH_CHECK_VALUE2_0))))
#define MCU_FD26_FLASH_CHECK_VALUE2_1                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_26_FLASH_CHECK_VALUE2_1))))
#define MCU_FD27_BOOTUP_BANK_START                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFD_27_BOOTUP_BANK_START))))


//--------------------------------------------------
// EMCU LSADC Module 2 (Page FD)
//--------------------------------------------------
#define MCU_FD39_ADC_ANALOG_CONFIG                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFD_39_ADC_ANALOG_CONFIG))))
#define MCU_FD3A_ADC_ACONTROL                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_3A_ADC_ACONTROL))))
#define MCU_FD3B_ADC_A0_CONVERT_RESULT                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_3B_ADC_A0_CONVERT_RESULT))))
#define MCU_FD3C_ADC_A1_CONVERT_RESULT                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_3C_ADC_A1_CONVERT_RESULT))))
#define MCU_FD3D_ADC_A2_CONVERT_RESULT                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_3D_ADC_A2_CONVERT_RESULT))))
#define MCU_FD3E_ADC_A3_CONVERT_RESULT                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_3E_ADC_A3_CONVERT_RESULT))))
#define MCU_FD3F_ADC_CLK_DIV                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFD_3F_ADC_CLK_DIV))))
#define MCU_FD40_AUTO_MODE_CTRL01                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_40_AUTO_MODE_CTRL01))))
#define MCU_FDF7_ADC0_THRESHOLD_H                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_F7_ADC0_THRESHOLD_H))))
#define MCU_FDF8_ADC0_THRESHOLD_L                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_F8_ADC0_THRESHOLD_L))))
#define MCU_FDF9_ADC1_THRESHOLD_H                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_F9_ADC1_THRESHOLD_H))))
#define MCU_FDFA_ADC1_THRESHOLD_L                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_FA_ADC1_THRESHOLD_L))))
#define MCU_FDFB_ADC2_THRESHOLD_H                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_FB_ADC2_THRESHOLD_H))))
#define MCU_FDFC_ADC2_THRESHOLD_L                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_FC_ADC2_THRESHOLD_L))))
#define MCU_FDFD_ADC3_THRESHOLD_H                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_FD_ADC3_THRESHOLD_H))))
#define MCU_FDFE_ADC3_THRESHOLD_L                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_FE_ADC3_THRESHOLD_L))))
#define MCU_FDFF_CTRL0_WAIT_TIME_VALUE                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_FF_CTRL0_WAIT_TIME_VALUE))))


//--------------------------------------------------
// CPU Interoperate Control (Page FD)
//--------------------------------------------------
#define MCU_FD57_MCU_FLASH_BYPASS_MODE                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_57_MCU_FLASH_BYPASS_MODE))))


//--------------------------------------------------
// EMCU IDCC (Page FD)
//--------------------------------------------------
#define MCU_FD80_IDCC3_CONTROL0                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFD_80_IDCC3_CONTROL0))))
#define MCU_FD81_IDCC3_CONTROL1                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFD_81_IDCC3_CONTROL1))))
#define MCU_FD82_IDCC3_STATUS                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_82_IDCC3_STATUS))))
#define MCU_FD83_IDCC3_OFFSET_IN                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFD_83_IDCC3_OFFSET_IN))))
#define MCU_FD84_IDCC3_LENGTH_IN                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFD_84_IDCC3_LENGTH_IN))))
#define MCU_FD85_IDCC3_WRITE_ADDR_H                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_85_IDCC3_WRITE_ADDR_H))))
#define MCU_FD86_IDCC3_WRITE_ADDR_L                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_86_IDCC3_WRITE_ADDR_L))))
#define MCU_FD87_IDCC3_READ_ADDR_H                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFD_87_IDCC3_READ_ADDR_H))))
#define MCU_FD88_IDCC3_READ_ADDR_L                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFD_88_IDCC3_READ_ADDR_L))))
#define MCU_FD89_IDCC3_DUMMY1                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_89_IDCC3_DUMMY1))))
#define MCU_FD8A_IDCC3_DUMMY2                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_8A_IDCC3_DUMMY2))))
#define MCU_FD8B_IDCC3_DUMMY3                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_8B_IDCC3_DUMMY3))))
#define MCU_FDA0_IDCC4_CONTROL0                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A0_IDCC4_CONTROL0))))
#define MCU_FDA1_IDCC4_CONTROL1                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A1_IDCC4_CONTROL1))))
#define MCU_FDA2_IDCC4_STATUS                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A2_IDCC4_STATUS))))
#define MCU_FDA3_IDCC4_OFFSET_IN                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A3_IDCC4_OFFSET_IN))))
#define MCU_FDA4_IDCC4_LENGTH_IN                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A4_IDCC4_LENGTH_IN))))
#define MCU_FDA5_IDCC4_WRITE_ADDR_H                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A5_IDCC4_WRITE_ADDR_H))))
#define MCU_FDA6_IDCC4_WRITE_ADDR_L                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A6_IDCC4_WRITE_ADDR_L))))
#define MCU_FDA7_IDCC4_READ_ADDR_H                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A7_IDCC4_READ_ADDR_H))))
#define MCU_FDA8_IDCC4_READ_ADDR_L                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A8_IDCC4_READ_ADDR_L))))
#define MCU_FDA9_IDCC4_DUMMY1                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_A9_IDCC4_DUMMY1))))
#define MCU_FDAA_IDCC4_DUMMY2                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_AA_IDCC4_DUMMY2))))
#define MCU_FDAB_IDCC4_DUMMY3                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_AB_IDCC4_DUMMY3))))


//--------------------------------------------------
// Background ISP Speed Up (Page FD)
//--------------------------------------------------
#define MCU_FD90_BACKGROUND_ISP_CTRL                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFD_90_BACKGROUND_ISP_CTRL))))
#define MCU_FD91_BACKGROUND_ISP_STATUS                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_91_BACKGROUND_ISP_STATUS))))
#define MCU_FD92_BACKGROUND_ISP_SLAVE_ADDRESS                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFD_92_BACKGROUND_ISP_SLAVE_ADDRESS))))
#define MCU_FD93_BACKGROUND_ISP_SUB_ADDRESS                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFD_93_BACKGROUND_ISP_SUB_ADDRESS))))
#define MCU_FD94_BACKGROUND_ISP_ADDR_4TH                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFD_94_BACKGROUND_ISP_ADDR_4TH))))
#define MCU_FD95_BACKGROUND_ISP_ADDR_H                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_95_BACKGROUND_ISP_ADDR_H))))
#define MCU_FD96_BACKGROUND_ISP_ADDR_M                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_96_BACKGROUND_ISP_ADDR_M))))
#define MCU_FD97_BACKGROUND_ISP_ADDR_L                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_97_BACKGROUND_ISP_ADDR_L))))
#define MCU_FD98_BACKGROUND_ISP_LENGTH                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_98_BACKGROUND_ISP_LENGTH))))
#define MCU_FD99_BACKGROUND_ISP_DUMMY1                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_99_BACKGROUND_ISP_DUMMY1))))
#define MCU_FD9A_BACKGROUND_ISP_DUMMY2                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFD_9A_BACKGROUND_ISP_DUMMY2))))


//--------------------------------------------------
// EMCU 8to32bits Interface (Page FD)
//--------------------------------------------------
#define MCU_FDD0_EMCU_TO32B_INF_GRP0_A3                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D0_EMCU_TO32B_INF_GRP0_A3))))
#define MCU_FDD1_EMCU_TO32B_INF_GRP0_A2                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D1_EMCU_TO32B_INF_GRP0_A2))))
#define MCU_FDD2_EMCU_TO32B_INF_GRP0_A1                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D2_EMCU_TO32B_INF_GRP0_A1))))
#define MCU_FDD3_EMCU_TO32B_INF_GRP0_A0                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D3_EMCU_TO32B_INF_GRP0_A0))))
#define MCU_FDD4_EMCU_TO32B_INF_GRP0_D3                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D4_EMCU_TO32B_INF_GRP0_D3))))
#define MCU_FDD5_EMCU_TO32B_INF_GRP0_D2                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D5_EMCU_TO32B_INF_GRP0_D2))))
#define MCU_FDD6_EMCU_TO32B_INF_GRP0_D1                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D6_EMCU_TO32B_INF_GRP0_D1))))
#define MCU_FDD7_EMCU_TO32B_INF_GRP0_D0                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D7_EMCU_TO32B_INF_GRP0_D0))))
#define MCU_FDD8_EMCU_TO32B_INF_GRP1_A3                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D8_EMCU_TO32B_INF_GRP1_A3))))
#define MCU_FDD9_EMCU_TO32B_INF_GRP1_A2                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_D9_EMCU_TO32B_INF_GRP1_A2))))
#define MCU_FDDA_EMCU_TO32B_INF_GRP1_A1                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_DA_EMCU_TO32B_INF_GRP1_A1))))
#define MCU_FDDB_EMCU_TO32B_INF_GRP1_A0                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_DB_EMCU_TO32B_INF_GRP1_A0))))
#define MCU_FDDC_EMCU_TO32B_INF_GRP1_D3                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_DC_EMCU_TO32B_INF_GRP1_D3))))
#define MCU_FDDD_EMCU_TO32B_INF_GRP1_D2                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_DD_EMCU_TO32B_INF_GRP1_D2))))
#define MCU_FDDE_EMCU_TO32B_INF_GRP1_D1                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_DE_EMCU_TO32B_INF_GRP1_D1))))
#define MCU_FDDF_EMCU_TO32B_INF_GRP1_D0                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFD_DF_EMCU_TO32B_INF_GRP1_D0))))
#define MCU_FDE0_EMCU_TO32B_INF_ADDR3                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E0_EMCU_TO32B_INF_ADDR3))))
#define MCU_FDE1_EMCU_TO32B_INF_ADDR2                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E1_EMCU_TO32B_INF_ADDR2))))
#define MCU_FDE2_EMCU_TO32B_INF_ADDR1                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E2_EMCU_TO32B_INF_ADDR1))))
#define MCU_FDE3_EMCU_TO32B_INF_ADDR0                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E3_EMCU_TO32B_INF_ADDR0))))
#define MCU_FDE4_EMCU_TO32B_INF_DATA                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E4_EMCU_TO32B_INF_DATA))))
#define MCU_FDE5_EMCU_TO32B_INF_CTRL                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E5_EMCU_TO32B_INF_CTRL))))
#define MCU_FDE6_EMCU_TO32_INF_WR                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E6_EMCU_TO32_INF_WR))))
#define MCU_FDE7_EMCU_TO32_INF_RD                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E7_EMCU_TO32_INF_RD))))
#define MCU_FDE8_BURST_WRITE_CTRL                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E8_BURST_WRITE_CTRL))))
#define MCU_FDE9_EMCU_TO32_INF_DUMMY0                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_E9_EMCU_TO32_INF_DUMMY0))))
#define MCU_FDEA_EMCU_TO32_INF_DUMMY1                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_EA_EMCU_TO32_INF_DUMMY1))))
#define MCU_FDEB_EMCU_TO32_INF_DUMMY2                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFD_EB_EMCU_TO32_INF_DUMMY2))))


//--------------------------------------------------
// EMCU GPIO Control Part 1 (Page FE)
//--------------------------------------------------
#define MCU_FE00_PORT40_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_00_PORT40_PIN_REG))))
#define MCU_FE01_PORT41_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_01_PORT41_PIN_REG))))
#define MCU_FE02_PORT42_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_02_PORT42_PIN_REG))))
#define MCU_FE03_PORT43_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_03_PORT43_PIN_REG))))
#define MCU_FE04_PORT44_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_04_PORT44_PIN_REG))))
#define MCU_FE05_PORT45_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_05_PORT45_PIN_REG))))
#define MCU_FE06_PORT46_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_06_PORT46_PIN_REG))))
#define MCU_FE07_PORT47_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_07_PORT47_PIN_REG))))
#define MCU_FE08_PORT50_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_08_PORT50_PIN_REG))))
#define MCU_FE09_PORT51_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_09_PORT51_PIN_REG))))
#define MCU_FE0A_PORT52_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_0A_PORT52_PIN_REG))))
#define MCU_FE0B_PORT53_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_0B_PORT53_PIN_REG))))
#define MCU_FE0C_PORT54_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_0C_PORT54_PIN_REG))))
#define MCU_FE0D_PORT55_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_0D_PORT55_PIN_REG))))
#define MCU_FE0E_PORT56_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_0E_PORT56_PIN_REG))))
#define MCU_FE0F_PORT57_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_0F_PORT57_PIN_REG))))
#define MCU_FE10_PORT60_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_10_PORT60_PIN_REG))))
#define MCU_FE11_PORT61_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_11_PORT61_PIN_REG))))
#define MCU_FE12_PORT62_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_12_PORT62_PIN_REG))))
#define MCU_FE13_PORT63_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_13_PORT63_PIN_REG))))
#define MCU_FE14_PORT64_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_14_PORT64_PIN_REG))))
#define MCU_FE15_PORT65_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_15_PORT65_PIN_REG))))
#define MCU_FE16_PORT66_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_16_PORT66_PIN_REG))))
#define MCU_FE17_PORT67_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_17_PORT67_PIN_REG))))
#define MCU_FE18_PORT70_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_18_PORT70_PIN_REG))))
#define MCU_FE19_PORT71_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_19_PORT71_PIN_REG))))
#define MCU_FE1A_PORT72_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_1A_PORT72_PIN_REG))))
#define MCU_FE1B_PORT73_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_1B_PORT73_PIN_REG))))
#define MCU_FE1C_PORT74_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_1C_PORT74_PIN_REG))))
#define MCU_FE1D_PORT75_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_1D_PORT75_PIN_REG))))
#define MCU_FE1E_PORT76_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_1E_PORT76_PIN_REG))))
#define MCU_FE1F_PORT77_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_1F_PORT77_PIN_REG))))
#define MCU_FE20_PORT80_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_20_PORT80_PIN_REG))))
#define MCU_FE21_PORT81_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_21_PORT81_PIN_REG))))
#define MCU_FE22_PORT82_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_22_PORT82_PIN_REG))))
#define MCU_FE23_PORT83_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_23_PORT83_PIN_REG))))
#define MCU_FE24_PORT84_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_24_PORT84_PIN_REG))))
#define MCU_FE25_PORT85_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_25_PORT85_PIN_REG))))
#define MCU_FE26_PORT86_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_26_PORT86_PIN_REG))))
#define MCU_FE27_PORT87_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_27_PORT87_PIN_REG))))
#define MCU_FE28_PORT90_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_28_PORT90_PIN_REG))))
#define MCU_FE29_PORT91_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_29_PORT91_PIN_REG))))
#define MCU_FE2A_PORT92_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_2A_PORT92_PIN_REG))))
#define MCU_FE2B_PORT93_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_2B_PORT93_PIN_REG))))
#define MCU_FE2C_PORT94_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_2C_PORT94_PIN_REG))))
#define MCU_FE2D_PORT95_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_2D_PORT95_PIN_REG))))
#define MCU_FE2E_PORT96_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_2E_PORT96_PIN_REG))))
#define MCU_FE2F_PORT97_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_2F_PORT97_PIN_REG))))
#define MCU_FE30_PORTA0_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_30_PORTA0_PIN_REG))))
#define MCU_FE31_PORTA1_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_31_PORTA1_PIN_REG))))
#define MCU_FE32_PORTA2_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_32_PORTA2_PIN_REG))))
#define MCU_FE33_PORTA3_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_33_PORTA3_PIN_REG))))
#define MCU_FE34_PORTA4_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_34_PORTA4_PIN_REG))))
#define MCU_FE35_PORTA5_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_35_PORTA5_PIN_REG))))
#define MCU_FE36_PORTA6_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_36_PORTA6_PIN_REG))))
#define MCU_FE37_PORTA7_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_37_PORTA7_PIN_REG))))
#define MCU_FE38_PORTB0_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_38_PORTB0_PIN_REG))))
#define MCU_FE39_PORTB1_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_39_PORTB1_PIN_REG))))
#define MCU_FE3A_PORTB2_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_3A_PORTB2_PIN_REG))))
#define MCU_FE3B_PORTB3_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_3B_PORTB3_PIN_REG))))
#define MCU_FE3C_PORTB4_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_3C_PORTB4_PIN_REG))))
#define MCU_FE3D_PORTB5_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_3D_PORTB5_PIN_REG))))
#define MCU_FE3E_PORTB6_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_3E_PORTB6_PIN_REG))))
#define MCU_FE3F_PORTB7_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_3F_PORTB7_PIN_REG))))
#define MCU_FE40_PORTC0_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_40_PORTC0_PIN_REG))))
#define MCU_FE41_PORTC1_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_41_PORTC1_PIN_REG))))
#define MCU_FE42_PORTC2_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_42_PORTC2_PIN_REG))))
#define MCU_FE43_PORTC3_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_43_PORTC3_PIN_REG))))
#define MCU_FE44_PORTC4_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_44_PORTC4_PIN_REG))))
#define MCU_FE45_PORTC5_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_45_PORTC5_PIN_REG))))
#define MCU_FE46_PORTC6_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_46_PORTC6_PIN_REG))))
#define MCU_FE47_PORTC7_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_47_PORTC7_PIN_REG))))
#define MCU_FE48_PORTD0_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_48_PORTD0_PIN_REG))))
#define MCU_FE49_PORTD1_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_49_PORTD1_PIN_REG))))
#define MCU_FE4A_PORTD2_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_4A_PORTD2_PIN_REG))))
#define MCU_FE4B_PORTD3_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_4B_PORTD3_PIN_REG))))
#define MCU_FE4C_PORTD4_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_4C_PORTD4_PIN_REG))))
#define MCU_FE4D_PORTD5_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_4D_PORTD5_PIN_REG))))
#define MCU_FE4E_PORTD6_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_4E_PORTD6_PIN_REG))))
#define MCU_FE4F_PORTD7_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_4F_PORTD7_PIN_REG))))
#define MCU_FE50_PORTE0_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_50_PORTE0_PIN_REG))))
#define MCU_FE51_PORTE1_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_51_PORTE1_PIN_REG))))
#define MCU_FE52_PORTE2_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_52_PORTE2_PIN_REG))))
#define MCU_FE53_PORTE3_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_53_PORTE3_PIN_REG))))
#define MCU_FE54_PORTE4_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_54_PORTE4_PIN_REG))))
#define MCU_FE55_PORTE5_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_55_PORTE5_PIN_REG))))
#define MCU_FE56_PORTE6_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_56_PORTE6_PIN_REG))))
#define MCU_FE57_PORTE7_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_57_PORTE7_PIN_REG))))
#define MCU_FE58_PORTF0_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_58_PORTF0_PIN_REG))))
#define MCU_FE59_PORTF1_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_59_PORTF1_PIN_REG))))
#define MCU_FE5A_PORTF2_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_5A_PORTF2_PIN_REG))))
#define MCU_FE5B_PORTF3_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_5B_PORTF3_PIN_REG))))
#define MCU_FE5C_PORTF4_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_5C_PORTF4_PIN_REG))))
#define MCU_FE5D_PORTF5_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_5D_PORTF5_PIN_REG))))
#define MCU_FE5E_PORTF6_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_5E_PORTF6_PIN_REG))))
#define MCU_FE5F_PORTF7_PIN_REG                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_5F_PORTF7_PIN_REG))))
#define MCU_FE60_PORT_READ_CONTROL                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_60_PORT_READ_CONTROL))))
#define MCU_FE61_PORT_READ_CONTROL_2                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_61_PORT_READ_CONTROL_2))))


//--------------------------------------------------
// EMCU DDC Part 0 (Page FE)
//--------------------------------------------------
#define MCU_FE62_DDC2_SEGMENT_ADDRESS                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFE_62_DDC2_SEGMENT_ADDRESS))))
#define MCU_FE63_DDC2_SEGMENT_DATA                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_63_DDC2_SEGMENT_DATA))))
#define MCU_FE64_DDC2_DDC_ENABLE                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_64_DDC2_DDC_ENABLE))))
#define MCU_FE65_DDC2_DDC_CONTROL_1                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_65_DDC2_DDC_CONTROL_1))))
#define MCU_FE66_DDC2_DDC_CONTROL_2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_66_DDC2_DDC_CONTROL_2))))
#define MCU_FE67_DDC2_DDC_INDEX                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_67_DDC2_DDC_INDEX))))
#define MCU_FE68_DDC2_DDC_ACCESS_PORT                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFE_68_DDC2_DDC_ACCESS_PORT))))
#define MCU_FE69_DDC2_EDID_IRQ                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFE_69_DDC2_EDID_IRQ))))
#define MCU_FE6A_DDC2_RESERVED                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFE_6A_DDC2_RESERVED))))
#define MCU_FE6B_DDC3_SEGMENT_ADDRESS                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFE_6B_DDC3_SEGMENT_ADDRESS))))
#define MCU_FE6C_DDC3_SEGMENT_DATA                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_6C_DDC3_SEGMENT_DATA))))
#define MCU_FE6D_DDC3_DDC_ENABLE                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_6D_DDC3_DDC_ENABLE))))
#define MCU_FE6E_DDC3_DDC_CONTROL_1                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_6E_DDC3_DDC_CONTROL_1))))
#define MCU_FE6F_DDC3_DDC_CONTROL_2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_6F_DDC3_DDC_CONTROL_2))))
#define MCU_FE70_DDC3_DDC_INDEX                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_70_DDC3_DDC_INDEX))))
#define MCU_FE71_DDC3_DDC_ACCESS_PORT                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFE_71_DDC3_DDC_ACCESS_PORT))))
#define MCU_FE72_DDC3_EDID_IRQ                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFE_72_DDC3_EDID_IRQ))))
#define MCU_FE73_DDC3_RESERVED                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFE_73_DDC3_RESERVED))))
#define MCU_FE74_DDC4_SEGMENT_ADDRESS                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFE_74_DDC4_SEGMENT_ADDRESS))))
#define MCU_FE75_DDC4_SEGMENT_DATA                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_75_DDC4_SEGMENT_DATA))))
#define MCU_FE76_DDC4_DDC_ENABLE                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_76_DDC4_DDC_ENABLE))))
#define MCU_FE77_DDC4_DDC_CONTROL_1                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_77_DDC4_DDC_CONTROL_1))))
#define MCU_FE78_DDC4_DDC_CONTROL_2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_78_DDC4_DDC_CONTROL_2))))
#define MCU_FE79_DDC4_DDC_INDEX                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_79_DDC4_DDC_INDEX))))
#define MCU_FE7A_DDC4_DDC_ACCESS_PORT                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFE_7A_DDC4_DDC_ACCESS_PORT))))
#define MCU_FE7B_DDC4_EDID_IRQ                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFE_7B_DDC4_EDID_IRQ))))
#define MCU_FE7C_DDC4_RESERVED                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFE_7C_DDC4_RESERVED))))


//--------------------------------------------------
// EMCU DDC-CI Part 0 (Page FE)
//--------------------------------------------------
#define MCU_FE86_IIC_1_CH_SEL                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFE_86_IIC_1_CH_SEL))))
#define MCU_FE87_IIC_1_SET_SLAVE                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_87_IIC_1_SET_SLAVE))))
#define MCU_FE88_IIC_1_SUB_IN                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFE_88_IIC_1_SUB_IN))))
#define MCU_FE89_IIC_1_DATA_IN                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFE_89_IIC_1_DATA_IN))))
#define MCU_FE8A_IIC_1_DATA_OUT                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_8A_IIC_1_DATA_OUT))))
#define MCU_FE8B_IIC_1_STATUS                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFE_8B_IIC_1_STATUS))))
#define MCU_FE8C_IIC_1_IRQ_CONTROL                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_8C_IIC_1_IRQ_CONTROL))))
#define MCU_FE8D_IIC_1_STATUS2                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFE_8D_IIC_1_STATUS2))))
#define MCU_FE8E_IIC_1_IRQ_CONTROL2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_8E_IIC_1_IRQ_CONTROL2))))
#define MCU_FE8F_IIC_1_CHANNEL_CONTROL                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFE_8F_IIC_1_CHANNEL_CONTROL))))
#define MCU_FE90_DDCCI_1_NULL_BYTE1                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_90_DDCCI_1_NULL_BYTE1))))
#define MCU_FE91_DDCCI_1_NULL_BYTE2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_91_DDCCI_1_NULL_BYTE2))))
#define MCU_FE92_DDCCI_1_NULL_BYTE3                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_92_DDCCI_1_NULL_BYTE3))))
#define MCU_FE93_DDCCI_1_REMAIN_DATA                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_93_DDCCI_1_REMAIN_DATA))))


//--------------------------------------------------
// EMCU XRAM Bist Settings (Page FE)
//--------------------------------------------------
#define MCU_FEB2_XRAM_BIST_CTRL                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFE_B2_XRAM_BIST_CTRL))))
#define MCU_FEB3_XRAM_DRF_BIST_CTRL                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_B3_XRAM_DRF_BIST_CTRL))))
#define MCU_FEB4_EMCU_SRAM_MARGIN_CTRL                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFE_B4_EMCU_SRAM_MARGIN_CTRL))))


//--------------------------------------------------
// EMCU DDCRAM Settings (Page FE)
//--------------------------------------------------
#define MCU_FEB9_DDC_DID_CTRL                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFE_B9_DDC_DID_CTRL))))
#define MCU_FEBA_DDC0_DDCRAM_SEL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_BA_DDC0_DDCRAM_SEL))))
#define MCU_FEBB_DDC0_DXINFO_B0_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_BB_DDC0_DXINFO_B0_DID))))
#define MCU_FEBC_DDC0_DXINFO_B1_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_BC_DDC0_DXINFO_B1_DID))))
#define MCU_FEBD_DDC0_DXINFO_OFFSL_DID                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFE_BD_DDC0_DXINFO_OFFSL_DID))))
#define MCU_FEBE_DDC0_DXINFO_B0_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_BE_DDC0_DXINFO_B0_EDID))))
#define MCU_FEBF_DDC0_DXINFO_B1_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_BF_DDC0_DXINFO_B1_EDID))))
#define MCU_FEC0_DDC0_DXINFO_OFFSL_EDID                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C0_DDC0_DXINFO_OFFSL_EDID))))
#define MCU_FEC1_DDC0_CHECKSUM_DID                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C1_DDC0_CHECKSUM_DID))))
#define MCU_FEC2_DDC0_CHECKSUM_OFFSL_DID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C2_DDC0_CHECKSUM_OFFSL_DID))))
#define MCU_FEC3_DDC0_CHECKSUM_EDID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C3_DDC0_CHECKSUM_EDID))))
#define MCU_FEC4_DDC0_CHECKSUM_OFFS_EDID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C4_DDC0_CHECKSUM_OFFS_EDID))))
#define MCU_FEC5_DDC1_DDCRAM_SEL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C5_DDC1_DDCRAM_SEL))))
#define MCU_FEC6_DDC1_DXINFO_B0_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C6_DDC1_DXINFO_B0_DID))))
#define MCU_FEC7_DDC1_DXINFO_B1_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C7_DDC1_DXINFO_B1_DID))))
#define MCU_FEC8_DDC1_DXINFO_OFFSL_DID                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C8_DDC1_DXINFO_OFFSL_DID))))
#define MCU_FEC9_DDC1_DXINFO_B0_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_C9_DDC1_DXINFO_B0_EDID))))
#define MCU_FECA_DDC1_DXINFO_B1_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_CA_DDC1_DXINFO_B1_EDID))))
#define MCU_FECB_DDC1_DXINFO_OFFSL_EDID                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFE_CB_DDC1_DXINFO_OFFSL_EDID))))
#define MCU_FECC_DDC1_CHECKSUM_DID                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_CC_DDC1_CHECKSUM_DID))))
#define MCU_FECD_DDC1_CHECKSUM_OFFSL_DID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_CD_DDC1_CHECKSUM_OFFSL_DID))))
#define MCU_FECE_DDC1_CHECKSUM_EDID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_CE_DDC1_CHECKSUM_EDID))))
#define MCU_FECF_DDC1_CHECKSUM_OFFS_EDID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_CF_DDC1_CHECKSUM_OFFS_EDID))))
#define MCU_FED3_DDC2_DDCRAM_SEL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_D3_DDC2_DDCRAM_SEL))))
#define MCU_FED4_DDC2_DXINFO_D0_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_D4_DDC2_DXINFO_D0_DID))))
#define MCU_FED5_DDC2_DXINFO_D1_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_D5_DDC2_DXINFO_D1_DID))))
#define MCU_FED6_DDC2_DXINFO_OFFSL_DID                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFE_D6_DDC2_DXINFO_OFFSL_DID))))
#define MCU_FED7_DDC2_DXINFO_D0_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_D7_DDC2_DXINFO_D0_EDID))))
#define MCU_FED8_DDC2_DXINFO_D1_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_D8_DDC2_DXINFO_D1_EDID))))
#define MCU_FED9_DDC2_DXINFO_OFFSL_EDID                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFE_D9_DDC2_DXINFO_OFFSL_EDID))))
#define MCU_FEDA_DDC2_CHECKSUM_DID                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_DA_DDC2_CHECKSUM_DID))))
#define MCU_FEDB_DDC2_CHECKSUM_OFFSL_DID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_DB_DDC2_CHECKSUM_OFFSL_DID))))
#define MCU_FEDC_DDC2_CHECKSUM_EDID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_DC_DDC2_CHECKSUM_EDID))))
#define MCU_FEDD_DDC2_CHECKSUM_OFFS_EDID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_DD_DDC2_CHECKSUM_OFFS_EDID))))
#define MCU_FEDE_DDC3_DDCRAM_SEL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_DE_DDC3_DDCRAM_SEL))))
#define MCU_FEDF_DDC3_DXINFO_D0_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_DF_DDC3_DXINFO_D0_DID))))
#define MCU_FEE0_DDC3_DXINFO_D1_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E0_DDC3_DXINFO_D1_DID))))
#define MCU_FEE1_DDC3_DXINFO_OFFSL_DID                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E1_DDC3_DXINFO_OFFSL_DID))))
#define MCU_FEE2_DDC3_DXINFO_D0_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E2_DDC3_DXINFO_D0_EDID))))
#define MCU_FEE3_DDC3_DXINFO_D1_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E3_DDC3_DXINFO_D1_EDID))))
#define MCU_FEE4_DDC3_DXINFO_OFFSL_EDID                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E4_DDC3_DXINFO_OFFSL_EDID))))
#define MCU_FEE5_DDC3_CHECKSUM_DID                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E5_DDC3_CHECKSUM_DID))))
#define MCU_FEE6_DDC3_CHECKSUM_OFFSL_DID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E6_DDC3_CHECKSUM_OFFSL_DID))))
#define MCU_FEE7_DDC3_CHECKSUM_EDID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E7_DDC3_CHECKSUM_EDID))))
#define MCU_FEE8_DDC3_CHECKSUM_OFFS_EDID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E8_DDC3_CHECKSUM_OFFS_EDID))))
#define MCU_FEE9_DDC4_DDCRAM_SEL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFE_E9_DDC4_DDCRAM_SEL))))
#define MCU_FEEA_DDC4_DXINFO_D0_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_EA_DDC4_DXINFO_D0_DID))))
#define MCU_FEEB_DDC4_DXINFO_D1_DID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_EB_DDC4_DXINFO_D1_DID))))
#define MCU_FEEC_DDC4_DXINFO_OFFSL_DID                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFE_EC_DDC4_DXINFO_OFFSL_DID))))
#define MCU_FEED_DDC4_DXINFO_D0_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_ED_DDC4_DXINFO_D0_EDID))))
#define MCU_FEEE_DDC4_DXINFO_D1_EDID                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFE_EE_DDC4_DXINFO_D1_EDID))))
#define MCU_FEEF_DDC4_DXINFO_OFFSL_EDID                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFE_EF_DDC4_DXINFO_OFFSL_EDID))))
#define MCU_FEF0_DDC4_CHECKSUM_DID                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFE_F0_DDC4_CHECKSUM_DID))))
#define MCU_FEF1_DDC4_CHECKSUM_OFFSL_DID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_F1_DDC4_CHECKSUM_OFFSL_DID))))
#define MCU_FEF2_DDC4_CHECKSUM_EDID                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFE_F2_DDC4_CHECKSUM_EDID))))
#define MCU_FEF3_DDC4_CHECKSUM_OFFS_EDID                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFE_F3_DDC4_CHECKSUM_OFFS_EDID))))
#define MCU_FEF4_DDCRAM_A_ADDRESS                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFE_F4_DDCRAM_A_ADDRESS))))


//--------------------------------------------------
// 2 CPU Access Flash Setting (Page FE)
//--------------------------------------------------
#define MCU_FEFF_FLASH_ACCESS_ARBITER                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFE_FF_FLASH_ACCESS_ARBITER))))


//--------------------------------------------------
// EMCU LSADC (Page FF)
//--------------------------------------------------
#define MCU_FF02_ADC_ANALOG_CONFIG                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_02_ADC_ANALOG_CONFIG))))
#define MCU_FF08_ADC_ACONTROL                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_08_ADC_ACONTROL))))
#define MCU_FF09_ADC_A0_CONVERT_RESULT                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFF_09_ADC_A0_CONVERT_RESULT))))
#define MCU_FF0A_ADC_A1_CONVERT_RESULT                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFF_0A_ADC_A1_CONVERT_RESULT))))
#define MCU_FF0B_ADC_A2_CONVERT_RESULT                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFF_0B_ADC_A2_CONVERT_RESULT))))
#define MCU_FF0C_ADC_A3_CONVERT_RESULT                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFF_0C_ADC_A3_CONVERT_RESULT))))
#define MCU_FF0D_ADC_CLK_DIV                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_0D_ADC_CLK_DIV))))
#define MCU_FF0E_AUTO_MODE_CTRL01                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_0E_AUTO_MODE_CTRL01))))
#define MCU_FF0F_ADC0_THRESHOLD_H                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_0F_ADC0_THRESHOLD_H))))
#define MCU_FF10_ADC0_THRESHOLD_L                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_10_ADC0_THRESHOLD_L))))
#define MCU_FF11_ADC1_THRESHOLD_H                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_11_ADC1_THRESHOLD_H))))
#define MCU_FF12_ADC1_THRESHOLD_L                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_12_ADC1_THRESHOLD_L))))
#define MCU_FF13_ADC2_THRESHOLD_H                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_13_ADC2_THRESHOLD_H))))
#define MCU_FF14_ADC2_THRESHOLD_L                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_14_ADC2_THRESHOLD_L))))
#define MCU_FF15_ADC3_THRESHOLD_H                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_15_ADC3_THRESHOLD_H))))
#define MCU_FF16_ADC3_THRESHOLD_L                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_16_ADC3_THRESHOLD_L))))
#define MCU_FF17_CTRL0_WAIT_TIME_VALUE                                                                                  (*((volatile REG_TYPE *)(REG_MAPPING(PFF_17_CTRL0_WAIT_TIME_VALUE))))


//--------------------------------------------------
// EMCU OSD Reorder Part 1 (Page FF)
//--------------------------------------------------
#define MCU_FF03_TRIPLE_BYTES_OPERATION                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFF_03_TRIPLE_BYTES_OPERATION))))
#define MCU_FF04_SHIFT_BITS_NUMBER                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_04_SHIFT_BITS_NUMBER))))
#define MCU_FF05_SHIFT_BYTE_ADDRESS                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_05_SHIFT_BYTE_ADDRESS))))
#define MCU_FF06_INPUT_TRIPLE_BYTES                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_06_INPUT_TRIPLE_BYTES))))
#define MCU_FF07_RESULT_TRIPLE_BYTES                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_07_RESULT_TRIPLE_BYTES))))


//--------------------------------------------------
// EMCU OSD Reorder Part 2 (Page FF)
//--------------------------------------------------
#define MCU_FF18_BYTE_ADDRESS                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_18_BYTE_ADDRESS))))


//--------------------------------------------------
// EMCU DDC Part 1 (Page FF)
//--------------------------------------------------
#define MCU_FF19_ADC_SEGMENT_ADDRESS                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_19_ADC_SEGMENT_ADDRESS))))
#define MCU_FF1A_ADC_SEGMENT_DATA                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_1A_ADC_SEGMENT_DATA))))
#define MCU_FF1B_ADC_DDC_ENABLE                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFF_1B_ADC_DDC_ENABLE))))
#define MCU_FF1C_ADC_DDC_CONTROL_1                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_1C_ADC_DDC_CONTROL_1))))
#define MCU_FF1D_ADC_DDC_CONTROL_2                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_1D_ADC_DDC_CONTROL_2))))
#define MCU_FF1E_DDC0_DDC_ENABLE                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_1E_DDC0_DDC_ENABLE))))
#define MCU_FF1F_DDC0_DDC_CONTROL_1                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_1F_DDC0_DDC_CONTROL_1))))
#define MCU_FF20_DDC0_DDC_CONTROL_2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_20_DDC0_DDC_CONTROL_2))))


//--------------------------------------------------
// EMCU DDC-CI Part 1 (Page FF)
//--------------------------------------------------
#define MCU_FF22_IIC_CH_SEL                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_22_IIC_CH_SEL))))
#define MCU_FF23_IIC_SET_SLAVE                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_23_IIC_SET_SLAVE))))
#define MCU_FF24_IIC_SUB_IN                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_24_IIC_SUB_IN))))
#define MCU_FF25_IIC_DATA_IN                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_25_IIC_DATA_IN))))
#define MCU_FF26_IIC_DATA_OUT                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_26_IIC_DATA_OUT))))
#define MCU_FF27_IIC_STATUS                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_27_IIC_STATUS))))
#define MCU_FF28_IIC_IRQ_CONTROL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_28_IIC_IRQ_CONTROL))))
#define MCU_FF29_IIC_STATUS2                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_29_IIC_STATUS2))))
#define MCU_FF2A_IIC_IRQ_CONTROL2                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_2A_IIC_IRQ_CONTROL2))))
#define MCU_FF2B_IIC_CHANNEL_CONTROL                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_2B_IIC_CHANNEL_CONTROL))))


//--------------------------------------------------
// EMCU DDC Part 2 (Page FF)
//--------------------------------------------------
#define MCU_FF2C_DDC1_DDC_ENABLE                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_2C_DDC1_DDC_ENABLE))))
#define MCU_FF2D_DDC1_DDC_CONTROL_1                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_2D_DDC1_DDC_CONTROL_1))))
#define MCU_FF2E_DDC1_DDC_CONTROL_2                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_2E_DDC1_DDC_CONTROL_2))))
#define MCU_FF35_DDCCI_REMAIN_DATA                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_35_DDCCI_REMAIN_DATA))))
#define MCU_FF36_DDC0_SEGMENT_ADDRESS                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFF_36_DDC0_SEGMENT_ADDRESS))))
#define MCU_FF37_DDC0_SEGMENT_DATA                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_37_DDC0_SEGMENT_DATA))))
#define MCU_FF38_DDC1_SEGMENT_ADDRESS                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFF_38_DDC1_SEGMENT_ADDRESS))))
#define MCU_FF39_DDC1_SEGMENT_DATA                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_39_DDC1_SEGMENT_DATA))))


//--------------------------------------------------
// EMCU PWM Part 1 (Page FF)
//--------------------------------------------------
#define MCU_FF3A_PWM_CK_SEL                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_3A_PWM_CK_SEL))))
#define MCU_FF3B_PWM03_M                                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFF_3B_PWM03_M))))
#define MCU_FF3C_PWM45_M                                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFF_3C_PWM45_M))))
#define MCU_FF3D_PWM01_N_MSB                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_3D_PWM01_N_MSB))))
#define MCU_FF3E_PWM0_N_LSB                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_3E_PWM0_N_LSB))))
#define MCU_FF3F_PWM1_N_LSB                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_3F_PWM1_N_LSB))))
#define MCU_FF40_PWM23_N_MSB                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_40_PWM23_N_MSB))))
#define MCU_FF41_PWM2_N_LSB                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_41_PWM2_N_LSB))))
#define MCU_FF42_PWM3_N_LSB                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_42_PWM3_N_LSB))))
#define MCU_FF43_PWM45_N_MSB                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_43_PWM45_N_MSB))))
#define MCU_FF44_PWM4_N_LSB                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_44_PWM4_N_LSB))))
#define MCU_FF45_PWM5_N_LSB                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_45_PWM5_N_LSB))))
#define MCU_FF46_PWML                                                                                                   (*((volatile REG_TYPE *)(REG_MAPPING(PFF_46_PWML))))
#define MCU_FF47_PWM_VS_CTRL                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_47_PWM_VS_CTRL))))
#define MCU_FF48_PWM_EN                                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFF_48_PWM_EN))))
#define MCU_FF49_PWM_CK                                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFF_49_PWM_CK))))
#define MCU_FF4A_PWM0H_DUT                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_4A_PWM0H_DUT))))
#define MCU_FF4B_PWM1H_DUT                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_4B_PWM1H_DUT))))
#define MCU_FF4C_PWM01L_DUT                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_4C_PWM01L_DUT))))
#define MCU_FF4D_PWM2H_DUT                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_4D_PWM2H_DUT))))
#define MCU_FF4E_PWM3H_DUT                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_4E_PWM3H_DUT))))
#define MCU_FF4F_PWM23L_DUT                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_4F_PWM23L_DUT))))
#define MCU_FF50_PWM4H_DUT                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_50_PWM4H_DUT))))
#define MCU_FF51_PWM5H_DUT                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_51_PWM5H_DUT))))
#define MCU_FF52_PWM45L_DUT                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_52_PWM45L_DUT))))
#define MCU_FF53_PWM_DUT_TYPE                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_53_PWM_DUT_TYPE))))
#define MCU_FF54_PWM_CNT_MODE                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_54_PWM_CNT_MODE))))


//--------------------------------------------------
// EMCU I2C Control Module (Page FF)
//--------------------------------------------------
#define MCU_FF55_I2CM_CR0                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_55_I2CM_CR0))))
#define MCU_FF56_I2CM_CR1                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_56_I2CM_CR1))))
#define MCU_FF57_I2CM_CR2                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_57_I2CM_CR2))))
#define MCU_FF58_I2CM_CR3                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_58_I2CM_CR3))))
#define MCU_FF59_I2CM_STR0                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_59_I2CM_STR0))))
#define MCU_FF5A_I2CM_STR1                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_5A_I2CM_STR1))))
#define MCU_FF5B_I2CM_STR2                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_5B_I2CM_STR2))))
#define MCU_FF5C_I2CM_STR3                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_5C_I2CM_STR3))))
#define MCU_FF5D_I2CM_SR                                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFF_5D_I2CM_SR))))
#define MCU_FF5E_I2CM_TD                                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFF_5E_I2CM_TD))))
#define MCU_FF5F_I2CM_CCR                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_5F_I2CM_CCR))))
#define MCU_FFD7_I2CM_STR4                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D7_I2CM_STR4))))
#define MCU_FFD8_I2CM_STR5                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D8_I2CM_STR5))))


//--------------------------------------------------
// EMCU SPI-FLASH Part 1 (Page FF)
//--------------------------------------------------
#define MCU_FF60_COMMON_INST_EN                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFF_60_COMMON_INST_EN))))
#define MCU_FF61_COMMON_OP_CODE                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFF_61_COMMON_OP_CODE))))
#define MCU_FF62_WREN_OP_CODE                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_62_WREN_OP_CODE))))
#define MCU_FF63_EWSR_OP_CODE                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_63_EWSR_OP_CODE))))
#define MCU_FF64_FLASH_PROG_ISP0                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_64_FLASH_PROG_ISP0))))
#define MCU_FF65_FLASH_PROG_ISP1                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_65_FLASH_PROG_ISP1))))
#define MCU_FF66_FLASH_PROG_ISP2                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_66_FLASH_PROG_ISP2))))
#define MCU_FF67_COMMON_INST_READ_PORT0                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFF_67_COMMON_INST_READ_PORT0))))
#define MCU_FF68_COMMON_INST_READ_PORT1                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFF_68_COMMON_INST_READ_PORT1))))
#define MCU_FF69_COMMON_INST_READ_PORT2                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFF_69_COMMON_INST_READ_PORT2))))
#define MCU_FF6A_READ_OP_CODE                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_6A_READ_OP_CODE))))
#define MCU_FF6B_FAST_READ_OP_CODE                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_6B_FAST_READ_OP_CODE))))
#define MCU_FF6C_READ_INSTRUCTION                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_6C_READ_INSTRUCTION))))
#define MCU_FF6D_PROGRAM_OP_CODE                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_6D_PROGRAM_OP_CODE))))
#define MCU_FF6E_READ_STATUS_REGISTER_OP_CODE                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_6E_READ_STATUS_REGISTER_OP_CODE))))
#define MCU_FF6F_PROGRAM_INSTRUCTION                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_6F_PROGRAM_INSTRUCTION))))
#define MCU_FF70_PROGRAM_DATA_PORT                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_70_PROGRAM_DATA_PORT))))
#define MCU_FF71_PROGRAM_LENGTH                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFF_71_PROGRAM_LENGTH))))
#define MCU_FF72_CRC_END_ADDR0                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_72_CRC_END_ADDR0))))
#define MCU_FF73_CRC_END_ADDR1                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_73_CRC_END_ADDR1))))
#define MCU_FF74_CRC_END_ADDR2                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_74_CRC_END_ADDR2))))
#define MCU_FF75_CRC_RESULT                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_75_CRC_RESULT))))
#define MCU_FF76_CEN_CTRL                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_76_CEN_CTRL))))
#define MCU_FF77_REV_DUMMY4                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_77_REV_DUMMY4))))
#define MCU_FF78_ACCESS_FLASH_ADDR_0                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_78_ACCESS_FLASH_ADDR_0))))
#define MCU_FF79_ACCESS_FLASH_ADDR_1                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_79_ACCESS_FLASH_ADDR_1))))
#define MCU_FF7A_ACCESS_FLASH_ADDR_2                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_7A_ACCESS_FLASH_ADDR_2))))
#define MCU_FF7B_ACCESS_FLASH_DATA_PORT                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFF_7B_ACCESS_FLASH_DATA_PORT))))
#define MCU_FF7C_ACCESS_FLASH_DATA_CTRL                                                                                 (*((volatile REG_TYPE *)(REG_MAPPING(PFF_7C_ACCESS_FLASH_DATA_CTRL))))
#define MCU_FF80_AAI_MODE_BYTE_NUM                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_80_AAI_MODE_BYTE_NUM))))
#define MCU_FF81_ISP_CMD_INSERT                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFF_81_ISP_CMD_INSERT))))
#define MCU_FF82_ISP_CMD_LENGTH                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFF_82_ISP_CMD_LENGTH))))


//--------------------------------------------------
// EMCU DDC Part 4 (Page FF)
//--------------------------------------------------
#define MCU_FF7D_DDC_DID_IRQ_0                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_7D_DDC_DID_IRQ_0))))
#define MCU_FF7E_DDC_DID_IRQ_1                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_7E_DDC_DID_IRQ_1))))
#define MCU_FF7F_DDC_DID_IRQ_2                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_7F_DDC_DID_IRQ_2))))


//--------------------------------------------------
// EMCU I2C Slave Module (Page FF)
//--------------------------------------------------
#define MCU_FF83_I2CS_CTRL0                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_83_I2CS_CTRL0))))
#define MCU_FF84_I2CS_CTRL1                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_84_I2CS_CTRL1))))
#define MCU_FF85_I2CS_CTRL2                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_85_I2CS_CTRL2))))
#define MCU_FF86_I2CS_STATUS0                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_86_I2CS_STATUS0))))
#define MCU_FF87_I2CS_STATUS1                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_87_I2CS_STATUS1))))
#define MCU_FF88_I2CS_BUFLEN                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_88_I2CS_BUFLEN))))
#define MCU_FFA0_I2CS_STATUS_BYTE                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_A0_I2CS_STATUS_BYTE))))


//--------------------------------------------------
// EMCU I2C Slave Module Part 1 (Page FF)
//--------------------------------------------------
#define MCU_FF89_I2CS_CTRL0                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_89_I2CS_CTRL0))))
#define MCU_FF8A_I2CS_CTRL1                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_8A_I2CS_CTRL1))))
#define MCU_FF8B_I2CS_CTRL2                                                                                             (*((volatile REG_TYPE *)(REG_MAPPING(PFF_8B_I2CS_CTRL2))))
#define MCU_FF8C_I2CS_STATUS0                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_8C_I2CS_STATUS0))))
#define MCU_FF8D_I2CS_STATUS1                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_8D_I2CS_STATUS1))))
#define MCU_FF8E_I2CS_BUFLEN                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_8E_I2CS_BUFLEN))))
#define MCU_FFA1_I2CS_STATUS_BYTE                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_A1_I2CS_STATUS_BYTE))))


//--------------------------------------------------
// EMCU PWM Part 2 (Page FF)
//--------------------------------------------------
#define MCU_FF90_PWM01_TOTALCNT_MSB                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_90_PWM01_TOTALCNT_MSB))))
#define MCU_FF91_PWM0_TOTALCNT_LSB                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_91_PWM0_TOTALCNT_LSB))))
#define MCU_FF92_PWM1_TOTALCNT_LSB                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_92_PWM1_TOTALCNT_LSB))))
#define MCU_FF93_PWM23_TOTALCNT_MSB                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_93_PWM23_TOTALCNT_MSB))))
#define MCU_FF94_PWM2_TOTALCNT_LSB                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_94_PWM2_TOTALCNT_LSB))))
#define MCU_FF95_PWM3_TOTALCNT_LSB                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_95_PWM3_TOTALCNT_LSB))))
#define MCU_FF96_PWM45_TOTALCNT_MSB                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_96_PWM45_TOTALCNT_MSB))))
#define MCU_FF97_PWM4_TOTALCNT_LSB                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_97_PWM4_TOTALCNT_LSB))))
#define MCU_FF98_PWM5_TOTALCNT_LSB                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_98_PWM5_TOTALCNT_LSB))))
#define MCU_FF99_PWM_CK_SEL_HS                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_99_PWM_CK_SEL_HS))))
#define MCU_FF9A_PWM01_CYCLE_MAX                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_9A_PWM01_CYCLE_MAX))))
#define MCU_FF9B_PWM23_CYCLE_MAX                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_9B_PWM23_CYCLE_MAX))))
#define MCU_FF9C_PWM45_CYCLE_MAX                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_9C_PWM45_CYCLE_MAX))))


//--------------------------------------------------
// EMCU DDCCI Part 2 (Page FF)
//--------------------------------------------------
#define MCU_FFB1_DDCCI_NULL_BYTE1                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_B1_DDCCI_NULL_BYTE1))))
#define MCU_FFB2_DDCCI_NULL_BYTE2                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_B2_DDCCI_NULL_BYTE2))))
#define MCU_FFB3_DDCCI_NULL_BYTE3                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_B3_DDCCI_NULL_BYTE3))))


//--------------------------------------------------
// EMCU SRAM Interface Control (Page FF)
//--------------------------------------------------
#define MCU_FFB4_SRAM_INF_DATA                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_B4_SRAM_INF_DATA))))
#define MCU_FFB5_SRAM_INF_CONTROL                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_B5_SRAM_INF_CONTROL))))
#define MCU_FFB6_SRAM_INF_ADDR                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_B6_SRAM_INF_ADDR))))


//--------------------------------------------------
// EMCU Interrupt Control Part 0 (Page FF)
//--------------------------------------------------
#define MCU_FFB8_EXT_INT0_CONTROL                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_B8_EXT_INT0_CONTROL))))
#define MCU_FFB9_EXT_INT1_CONTROL                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_B9_EXT_INT1_CONTROL))))


//--------------------------------------------------
// EMCU Test Mode (Page FF)
//--------------------------------------------------
#define MCU_FFBB_PERI_TEST                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_BB_PERI_TEST))))
#define MCU_FFBC_CYCLE_GATING                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_BC_CYCLE_GATING))))
#define MCU_FFBD_MCU_CLK_DIV_R                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_BD_MCU_CLK_DIV_R))))


//--------------------------------------------------
// EMCU I2C Control Module Part 1 (Page FF)
//--------------------------------------------------
#define MCU_FFC5_I2CM_CR0                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_C5_I2CM_CR0))))
#define MCU_FFC6_I2CM_CR1                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_C6_I2CM_CR1))))
#define MCU_FFC7_I2CM_CR2                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_C7_I2CM_CR2))))
#define MCU_FFC8_I2CM_CR3                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_C8_I2CM_CR3))))
#define MCU_FFC9_I2CM_STR0                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_C9_I2CM_STR0))))
#define MCU_FFCA_I2CM_STR1                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_CA_I2CM_STR1))))
#define MCU_FFCB_I2CM_STR2                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_CB_I2CM_STR2))))
#define MCU_FFCC_I2CM_STR3                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_CC_I2CM_STR3))))
#define MCU_FFCD_I2CM_SR                                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFF_CD_I2CM_SR))))
#define MCU_FFCE_I2CM_TD                                                                                                (*((volatile REG_TYPE *)(REG_MAPPING(PFF_CE_I2CM_TD))))
#define MCU_FFCF_I2CM_CCR                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_CF_I2CM_CCR))))
#define MCU_FFD9_I2CM_STR4                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D9_I2CM_STR4))))
#define MCU_FFDA_I2CM_STR5                                                                                              (*((volatile REG_TYPE *)(REG_MAPPING(PFF_DA_I2CM_STR5))))


//--------------------------------------------------
// EMCU DDCRAM Control (Page FF)
//--------------------------------------------------
#define MCU_FFD0_A_DDCRAM_CONTROL                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D0_A_DDCRAM_CONTROL))))
#define MCU_FFD1_DDCRAM0_CONTROL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D1_DDCRAM0_CONTROL))))
#define MCU_FFD2_DDCRAM1_CONTROL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D2_DDCRAM1_CONTROL))))
#define MCU_FFD3_DDCRAM2_CONTROL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D3_DDCRAM2_CONTROL))))
#define MCU_FFD4_DDCRAM3_CONTROL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D4_DDCRAM3_CONTROL))))
#define MCU_FFD5_DDCRAM4_CONTROL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_D5_DDCRAM4_CONTROL))))


//--------------------------------------------------
// EMCU DDC Part 3 (Page FF)
//--------------------------------------------------
#define MCU_FFE4_DDC0_EDID_IRQ                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_E4_DDC0_EDID_IRQ))))
#define MCU_FFE5_DDC1_EDID_IRQ                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_E5_DDC1_EDID_IRQ))))
#define MCU_FFE7_VGA_EDID_IRQ                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_E7_VGA_EDID_IRQ))))


//--------------------------------------------------
// EMCU In System Programming Part 1 (Page FF)
//--------------------------------------------------
#define MCU_FFE8_ISP_CONTROL                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_E8_ISP_CONTROL))))
#define MCU_FFE9_MCU_CLK_CONTROL_1                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_E9_MCU_CLK_CONTROL_1))))


//--------------------------------------------------
// EMCU In System Programming Part 2 (Page FF)
//--------------------------------------------------
#define MCU_FFEC_ISP_SLAVE_ADDRESS                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_EC_ISP_SLAVE_ADDRESS))))
#define MCU_FFED_MCU_CONTROL                                                                                            (*((volatile REG_TYPE *)(REG_MAPPING(PFF_ED_MCU_CONTROL))))
#define MCU_FFEE_MCU_CLOCK_CONTROL                                                                                      (*((volatile REG_TYPE *)(REG_MAPPING(PFF_EE_MCU_CLOCK_CONTROL))))
#define MCU_FFEF_RAM_TEST                                                                                               (*((volatile REG_TYPE *)(REG_MAPPING(PFF_EF_RAM_TEST))))


//--------------------------------------------------
// EMCU Xdata-SPI-FLASH Write Protect (Page FF)
//--------------------------------------------------
#define MCU_FFF0_XDATA_SPI_FLASH_WRITE_PROTECT                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F0_XDATA_SPI_FLASH_WRITE_PROTECT))))
#define MCU_FFF1_SCA_WR_INTRVL                                                                                          (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F1_SCA_WR_INTRVL))))
#define MCU_FFF2_PWM_I2C_CLOCK_STOP                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F2_PWM_I2C_CLOCK_STOP))))


//--------------------------------------------------
// EMCU Scalar Interface (Page FF)
//--------------------------------------------------
#define MCU_FFF3_SCA_INF_CONTROL                                                                                        (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F3_SCA_INF_CONTROL))))
#define MCU_FFF4_SCA_INF_ADDR                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F4_SCA_INF_ADDR))))
#define MCU_FFF5_SCA_INF_DATA                                                                                           (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F5_SCA_INF_DATA))))
#define MCU_FFF6_SCA_INF_BWR_ADRH                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F6_SCA_INF_BWR_ADRH))))
#define MCU_FFF7_SCA_INF_BWR_ADRM                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F7_SCA_INF_BWR_ADRM))))
#define MCU_FFF8_SCA_INF_BWR_ADRL                                                                                       (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F8_SCA_INF_BWR_ADRL))))
#define MCU_FFF9_SCA_INF_BWR_COUNT_H                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_F9_SCA_INF_BWR_COUNT_H))))
#define MCU_FFFA_SCA_INF_BWR_COUNT_L                                                                                    (*((volatile REG_TYPE *)(REG_MAPPING(PFF_FA_SCA_INF_BWR_COUNT_L))))
#define MCU_FFFB_SCA_INF_PERIOD                                                                                         (*((volatile REG_TYPE *)(REG_MAPPING(PFF_FB_SCA_INF_PERIOD))))


//--------------------------------------------------
// EMCU Bankswitch (Page FF)
//--------------------------------------------------
#define MCU_FFFC_BANK_SWICH_CONTROL                                                                                     (*((volatile REG_TYPE *)(REG_MAPPING(PFF_FC_BANK_SWICH_CONTROL))))