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
// ID Code      : RL6952_Gen_Option_Reg_Mapping.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Definitions of DP PRBS Reverse Enable
//--------------------------------------------------
#define GET_DP_MAC_RX0_PRBS_REVERSE_EN()                    ((bit)ScalerGetBit(PB_08_BIST_PATTERN_SEL, _BIT7))
#define SET_DP_MAC_RX0_PRBS_REVERSE_EN()                    {ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~_BIT7, _BIT7);}
#define CLR_DP_MAC_RX0_PRBS_REVERSE_EN()                    {ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~_BIT7, 0x00);}

//--------------------------------------------------
// Definitions of DP PRBS Reverse Enable
//--------------------------------------------------
#define GET_DP_MAC_RX1_PRBS_REVERSE_EN()                    ((bit)ScalerGetBit(PB0_08_BIST_PATTERN_SEL, _BIT7))
#define SET_DP_MAC_RX1_PRBS_REVERSE_EN()                    {ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~_BIT7, _BIT7);}
#define CLR_DP_MAC_RX1_PRBS_REVERSE_EN()                    {ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~_BIT7, 0x00);}

//--------------------------------------------------
// Definitions of DP PRBS Reverse Enable
//--------------------------------------------------
#define GET_DP_MAC_RX2_PRBS_REVERSE_EN()                    ((bit)ScalerGetBit(PC5_08_BIST_PATTERN_SEL, _BIT7))
#define SET_DP_MAC_RX2_PRBS_REVERSE_EN()                    {ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~_BIT7, _BIT7);}
#define CLR_DP_MAC_RX2_PRBS_REVERSE_EN()                    {ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~_BIT7, 0x00);}

//-------------------------------------------------
// Reg DP SPDIF_TX Channel Status Regen Mode
//-------------------------------------------------
#define _REG_DP14_RX0_AUDIO_SPDIF_TX_REGEN                  PB6_C4_SPDIFTX_CHST_CTRL
#define _REG_DP14_RX1_AUDIO_SPDIF_TX_REGEN                  PB9_C4_SPDIFTX_CHST_CTRL
#define _REG_DP14_RX2_AUDIO_SPDIF_TX_REGEN                  PC7_C4_SPDIFTX_CHST_CTRL
#define _REG_DP14_RX3_AUDIO_SPDIF_TX_REGEN                  _GEN_NONE
#define _REG_DP14_RX4_AUDIO_SPDIF_TX_REGEN                  _GEN_NONE

#define _REG_DP20_RX0_AUDIO_SPDIF_TX_REGEN                  P1B_C6_SPDIFTX_CHST_CTRL
#define _REG_DP20_RX1_AUDIO_SPDIF_TX_REGEN                  P75_C6_SPDIFTX_CHST_CTRL
#define _REG_DP20_RX2_AUDIO_SPDIF_TX_REGEN                  PD4_C6_SPDIFTX_CHST_CTRL
#define _REG_DP20_RX3_AUDIO_SPDIF_TX_REGEN                  _GEN_NONE
#define _REG_DP20_RX4_AUDIO_SPDIF_TX_REGEN                  _GEN_NONE

//-------------------------------------------------
// Reg Display Type
//-------------------------------------------------
#define _REG_DISP_TYPE                                      P39_00_DISP_TYPE

//--------------------------------------------------
//  Reg IDither SuperPix Type
//--------------------------------------------------
#define _REG_IDITHER_SUPERPIX_TYPE                          P0_8B_I_DITHER_COMMON_CTRL3_SETA

//--------------------------------------------------
//  Reg FRC Cap Fifo Status
//--------------------------------------------------
#define _REG_FRC_CAP_FIFO_STATUS                            P5_2B_CAP_M1_FIFO_STATUS

//--------------------------------------------------
//  Reg FRC Disp pre-read vertical start
//--------------------------------------------------
#define _REG_FRC_DISP_PRRD_VST_TOP_H                        P5_A6_DISP_M1_PRRD_VST_H_TOP
#define _REG_FRC_DISP_PRRD_VST_TOP_L                        P5_A7_DISP_M1_PRRD_VST_L_TOP

//--------------------------------------------------
// HDCP2.2 Reg Mapping
//--------------------------------------------------
#define SET_HDCP22_RSA_CLK_M2PLL_DIV2_ENABLE()              {ScalerSetBit(P63_93_HDCP_DUMMY1, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), _BIT7);}
#define SET_HDCP22_RSA_READ_POP_OUT_ENABLE()                {ScalerSetBit(P63_93_HDCP_DUMMY1, ~(_BIT5 | _BIT4 | _BIT3), _BIT3);}
#define SET_HDCP22_RSA_CLK()                                {ScalerSetBit(P63_93_HDCP_DUMMY1, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), 0x00);}

#define SET_HDCP22_SOFTWARE_RESET()                         {ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT3 | _BIT0), 0x00);}
#define CLR_HDCP22_SOFTWARE_RESET()                         {ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);}

#define SET_HDCP22_RSA_WRITE_KEY_DONE()                     {ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT0), _BIT0);}
#define SET_HDCP22_RSA_WRITE_KEY_MODE()                     {ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT7 | _BIT5));}
#define SET_HDCP22_RSA_READ_OUT_MODE()                      {ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT6);}
#define CLR_HDCP22_RSA_MODULE_ENABLE()                      {ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT4 | _BIT0), 0x00);}

#define SET_HDCP22_SHA_MODULE_RESET()                       {ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT3 | _BIT0), _BIT3);}
#define CLR_HDCP22_SHA_MODULE_RESET()                       {ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT3 | _BIT0), 0x00);}

#define SET_HDCP22_SHA_FIRST_CALCULATE()                    {ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT1);}
#define CLR_HDCP22_SHA_FIRST_CALCULATE()                    {ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);}

#define SET_HDCP22_SHA_CALCULATE_ENABLE()                   {ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT2 | _BIT0), _BIT2);}

//--------------------------------------------------
// HDCP1.4 Reg Mapping
//--------------------------------------------------
#define SET_DP_MAC_DPHY_RX0_HDCP14_SHA_RESET()              {ScalerSetBit(PB_30_SHA_CONTRL, ~(_BIT5 | _BIT3 | _BIT0), _BIT3);}
#define CLR_DP_MAC_DPHY_RX0_HDCP14_SHA_RESET()              {ScalerSetBit(PB_30_SHA_CONTRL, ~(_BIT5 | _BIT3 | _BIT0), 0x00);}
#define SET_DP_MAC_DPHY_RX0_HDCP14_SHA_FIRST_CALCULATE(x)   {ScalerSetBit(PB_30_SHA_CONTRL, ~(_BIT5 | _BIT1 | _BIT0), (((x) == _TRUE) ? _BIT1 : 0x00));}
#define CLR_DP_MAC_DPHY_RX0_HDCP14_SHA_FIRST_CALCULATE()    {ScalerSetBit(PB_30_SHA_CONTRL, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);}
#define SET_DP_MAC_DPHY_RX0_HDCP14_SHA_CALCULATE_ENABLE()   {ScalerSetBit(PB_30_SHA_CONTRL, ~(_BIT5 | _BIT2 | _BIT0), _BIT2);}

#define SET_DP_MAC_DPHY_RX1_HDCP14_SHA_RESET()              {ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT5 | _BIT3 | _BIT0), _BIT3);}
#define CLR_DP_MAC_DPHY_RX1_HDCP14_SHA_RESET()              {ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT5 | _BIT3 | _BIT0), 0x00);}
#define SET_DP_MAC_DPHY_RX1_HDCP14_SHA_FIRST_CALCULATE(x)   {ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT5 | _BIT1 | _BIT0), (((x) == _TRUE) ? _BIT1 : 0x00));}
#define CLR_DP_MAC_DPHY_RX1_HDCP14_SHA_FIRST_CALCULATE()    {ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);}
#define SET_DP_MAC_DPHY_RX1_HDCP14_SHA_CALCULATE_ENABLE()   {ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT5 | _BIT2 | _BIT0), _BIT2);}

#define SET_DP_MAC_DPHY_RX2_HDCP14_SHA_RESET()              {ScalerSetBit(PC5_30_SHA_CONTRL, ~(_BIT5 | _BIT3 | _BIT0), _BIT3);}
#define CLR_DP_MAC_DPHY_RX2_HDCP14_SHA_RESET()              {ScalerSetBit(PC5_30_SHA_CONTRL, ~(_BIT5 | _BIT3 | _BIT0), 0x00);}
#define SET_DP_MAC_DPHY_RX2_HDCP14_SHA_FIRST_CALCULATE(x)   {ScalerSetBit(PC5_30_SHA_CONTRL, ~(_BIT5 | _BIT1 | _BIT0), (((x) == _TRUE) ? _BIT1 : 0x00));}
#define CLR_DP_MAC_DPHY_RX2_HDCP14_SHA_FIRST_CALCULATE()    {ScalerSetBit(PC5_30_SHA_CONTRL, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);}
#define SET_DP_MAC_DPHY_RX2_HDCP14_SHA_CALCULATE_ENABLE()   {ScalerSetBit(PC5_30_SHA_CONTRL, ~(_BIT5 | _BIT2 | _BIT0), _BIT2);}

#define SET_DP_MST_RX_REG_SHA_ENABLE()                      {ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_MAIN_PORT(), PB_30_SHA_CONTRL), ~(_BIT5 | _BIT3 | _BIT0), 0x00);}
#define CLR_DP_MST_RX_REG_SHA_ENABLE()                      {ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_MAIN_PORT(), PB_30_SHA_CONTRL), ~(_BIT5 | _BIT3 | _BIT0), _BIT3);}
#define SET_DP_MST_RX_REG_SHA_INPUT_DB()                    {ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_MAIN_PORT(), PB_30_SHA_CONTRL), ~(_BIT5 | _BIT0), _BIT0);}

//--------------------------------------------------
// Definitions of DP MST to SST block Mode Config
//--------------------------------------------------
#define SET_DP_MAC_DPHY_RX0_MST2SST_BLOCK_MST_MODE()        {ScalerSetBit(PB5_01_STHD_CTRL_1, ~_BIT0, 0x00);}
#define SET_DP_MAC_DPHY_RX0_MST2SST_BLOCK_SST_MODE()        {ScalerSetBit(PB5_01_STHD_CTRL_1, ~_BIT0, _BIT0);}
#define SET_DP_MAC_DPHY_RX0_MST2SST_BLOCK_MST_MODE_EXINT()  {ScalerSetBit_EXINT(PB5_01_STHD_CTRL_1, ~_BIT0, 0x00);}
#define SET_DP_MAC_DPHY_RX0_MST2SST_BLOCK_SST_MODE_EXINT()  {ScalerSetBit_EXINT(PB5_01_STHD_CTRL_1, ~_BIT0, _BIT0);}

#define SET_DP_MAC_DPHY_RX1_MST2SST_BLOCK_MST_MODE()        {ScalerSetBit(PB8_01_STHD_CTRL_1, ~_BIT0, 0x00);}
#define SET_DP_MAC_DPHY_RX1_MST2SST_BLOCK_SST_MODE()        {ScalerSetBit(PB8_01_STHD_CTRL_1, ~_BIT0, _BIT0);}
#define SET_DP_MAC_DPHY_RX1_MST2SST_BLOCK_MST_MODE_EXINT()  {ScalerSetBit_EXINT(PB8_01_STHD_CTRL_1, ~_BIT0, 0x00);}
#define SET_DP_MAC_DPHY_RX1_MST2SST_BLOCK_SST_MODE_EXINT()  {ScalerSetBit_EXINT(PB8_01_STHD_CTRL_1, ~_BIT0, _BIT0);}

#define SET_DP_MAC_DPHY_RX2_MST2SST_BLOCK_MST_MODE()        {ScalerSetBit(PC6_01_STHD_CTRL_1, ~_BIT0, 0x00);}
#define SET_DP_MAC_DPHY_RX2_MST2SST_BLOCK_SST_MODE()        {ScalerSetBit(PC6_01_STHD_CTRL_1, ~_BIT0, _BIT0);}
#define SET_DP_MAC_DPHY_RX2_MST2SST_BLOCK_MST_MODE_EXINT()  {ScalerSetBit_EXINT(PC6_01_STHD_CTRL_1, ~_BIT0, 0x00);}
#define SET_DP_MAC_DPHY_RX2_MST2SST_BLOCK_SST_MODE_EXINT()  {ScalerSetBit_EXINT(PC6_01_STHD_CTRL_1, ~_BIT0, _BIT0);}

//-------------------------------------------------
// Reg DP BS Miss Ctrl Reg Mapping
//-------------------------------------------------
#define _REG_DP_MAC_STREAM_RX0_BS_MISS_CTRL                 PB5_B8_BS_MISS_CTRL
#define _REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL                 PB8_B8_BS_MISS_CTRL
#define _REG_DP_MAC_STREAM_RX2_BS_MISS_CTRL                 PC6_B8_BS_MISS_CTRL
#define _REG_DP_MAC_STREAM_RX3_BS_MISS_CTRL                 _GEN_NONE
#define _REG_DP_MAC_STREAM_RX4_BS_MISS_CTRL                 _GEN_NONE

//-------------------------------------------------
// Audio Ctrl Reg Mapping
//-------------------------------------------------
#define GET_AUDIO_AIO_POWER()                               ((bit)ScalerGetBit(P6_C0_REG_DAC_POWER0, _BIT5))
#define SET_AUDIO_AIO_POWER()                               {ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT5, _BIT5);}
#define CLR_AUDIO_AIO_POWER()                               {ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT5, 0x00);}
#define GET_AUDIO_HPO_POWER()                               ((bit)ScalerGetBit(P6_C0_REG_DAC_POWER0, _BIT4))
#define SET_AUDIO_HPO_POWER()                               {ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT4, _BIT4);}
#define CLR_AUDIO_HPO_POWER()                               {ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT4, 0x00);}

//-------------------------------------------------
// Reg Audio Ctrl Mapping
//-------------------------------------------------
#define _REG_AD_GAIN_DB_L                                   P6_B8_AD_GAIN_L
#define _REG_AD_GAIN_DB_R                                   P6_B9_AD_GAIN_R
#define _REG_AD_SPDIF_CS                                    P6_E2_AD_SPDIF_CS_0

//--------------------------------------------------
// HW DP Rx Aux Mac Reg Define
//--------------------------------------------------
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define _REG_DP_AUX_RX0_MAC_CTRL                            PB18006_00_AUX_MAC_CTRL
#define _REG_DP_AUX_RX0_TPS_OCCR                            PB18006_2C_TPS_OCCR
#define _REG_DP_AUX_RX0_STATUS                              PB18006_10_AUX_STATUS
#define _REG_DP_AUX_RX0_TX_TIMER                            PB18006_C0_AUX_TX_TIMER
#define _REG_DP_AUX_RX0_WILDCARD_ADDR                       PB18005_D8_AUX_WILDCARD_ADDR0
#define _REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_FLAG              PB18005_D4_AUX_WILDCARD_ADDR_IRQ_FLAG
#define _REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_EN                PB18005_D0_AUX_WILDCARD_ADDR_IRQ_EN
#define _REG_DP_AUX_RX0_DPCD_ADDR_INPUT_PORT                PB18006_60_AUX_DPCD_ACCESS_ADDR
#define _REG_DP_AUX_RX0_DPCD_DATA_INPUT_PORT                PB18006_64_AUX_DPCD_ACCESS_DATA
#define _REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL                 PB18006_68_AUX_DPCD_ACCESS_CONTROL
#define _REG_DP_AUX_RX0_DPCD_ADDR_OUTPUT_PORT               PB18006_30_DPCD_ADDR_PORT
#define _REG_DP_AUX_RX0_DPCD_DATA_OUTPUT_PORT               PB18006_34_DPCD_DATA_PORT
#define _REG_DP_AUX_RX0_RECIEVE_CMD                         PB18006_14_AUX_ADDR_SRC
#define _REG_DP_AUX_RX0_RECIEVE_INT_CMD                     PB18006_28_AUX_INT_CMD
#define _REG_DP_AUX_RX0_REPLY_CMD                           PB18006_20_AUX_TX_CMD
#define _REG_DP_AUX_RX0_REPLY_CMD_START                     PB18006_24_AUX_TX_START
#define _REG_DP_AUX_RX0_IIC_CTRL0                           PB18006_D0_IIC_CTRL0
#define _REG_DP_AUX_RX0_IIC_CTRL1                           PB18006_D4_IIC_CTRL1

#define _REG_DP_AUX_RX1_MAC_CTRL                            PB19006_00_AUX_MAC_CTRL
#define _REG_DP_AUX_RX1_TPS_OCCR                            PB19006_2C_TPS_OCCR
#define _REG_DP_AUX_RX1_STATUS                              PB19006_10_AUX_STATUS
#define _REG_DP_AUX_RX1_TX_TIMER                            PB19006_C0_AUX_TX_TIMER
#define _REG_DP_AUX_RX1_WILDCARD_ADDR                       PB19005_D8_AUX_WILDCARD_ADDR0
#define _REG_DP_AUX_RX1_WILDCARD_ADDR_IRQ_FLAG              PB19005_D4_AUX_WILDCARD_ADDR_IRQ_FLAG
#define _REG_DP_AUX_RX1_WILDCARD_ADDR_IRQ_EN                PB19005_D0_AUX_WILDCARD_ADDR_IRQ_EN
#define _REG_DP_AUX_RX1_DPCD_ADDR_INPUT_PORT                PB19006_60_AUX_DPCD_ACCESS_ADDR
#define _REG_DP_AUX_RX1_DPCD_DATA_INPUT_PORT                PB19006_64_AUX_DPCD_ACCESS_DATA
#define _REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL                 PB19006_68_AUX_DPCD_ACCESS_CONTROL
#define _REG_DP_AUX_RX1_DPCD_ADDR_OUTPUT_PORT               PB19006_30_DPCD_ADDR_PORT
#define _REG_DP_AUX_RX1_DPCD_DATA_OUTPUT_PORT               PB19006_34_DPCD_DATA_PORT
#define _REG_DP_AUX_RX1_RECIEVE_CMD                         PB19006_14_AUX_ADDR_SRC
#define _REG_DP_AUX_RX1_RECIEVE_INT_CMD                     PB19006_28_AUX_INT_CMD
#define _REG_DP_AUX_RX1_REPLY_CMD                           PB19006_20_AUX_TX_CMD
#define _REG_DP_AUX_RX1_REPLY_CMD_START                     PB19006_24_AUX_TX_START
#define _REG_DP_AUX_RX1_IIC_CTRL0                           PB19006_D0_IIC_CTRL0
#define _REG_DP_AUX_RX1_IIC_CTRL1                           PB19006_D4_IIC_CTRL1

#define _REG_DP_AUX_RX2_MAC_CTRL                            PB1A006_00_AUX_MAC_CTRL
#define _REG_DP_AUX_RX2_TPS_OCCR                            PB1A006_2C_TPS_OCCR
#define _REG_DP_AUX_RX2_STATUS                              PB1A006_10_AUX_STATUS
#define _REG_DP_AUX_RX2_TX_TIMER                            PB1A006_C0_AUX_TX_TIMER
#define _REG_DP_AUX_RX2_WILDCARD_ADDR                       PB1A005_D8_AUX_WILDCARD_ADDR0
#define _REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_FLAG              PB1A005_D4_AUX_WILDCARD_ADDR_IRQ_FLAG
#define _REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_EN                PB1A005_D0_AUX_WILDCARD_ADDR_IRQ_EN
#define _REG_DP_AUX_RX2_DPCD_ADDR_INPUT_PORT                PB1A006_60_AUX_DPCD_ACCESS_ADDR
#define _REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT                PB1A006_64_AUX_DPCD_ACCESS_DATA
#define _REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL                 PB1A006_68_AUX_DPCD_ACCESS_CONTROL
#define _REG_DP_AUX_RX2_DPCD_ADDR_OUTPUT_PORT               PB1A006_30_DPCD_ADDR_PORT
#define _REG_DP_AUX_RX2_DPCD_DATA_OUTPUT_PORT               PB1A006_34_DPCD_DATA_PORT
#define _REG_DP_AUX_RX2_RECIEVE_CMD                         PB1A006_14_AUX_ADDR_SRC
#define _REG_DP_AUX_RX2_RECIEVE_INT_CMD                     PB1A006_28_AUX_INT_CMD
#define _REG_DP_AUX_RX2_REPLY_CMD                           PB1A006_20_AUX_TX_CMD
#define _REG_DP_AUX_RX2_REPLY_CMD_START                     PB1A006_24_AUX_TX_START
#define _REG_DP_AUX_RX2_IIC_CTRL0                           PB1A006_D0_IIC_CTRL0
#define _REG_DP_AUX_RX2_IIC_CTRL1                           PB1A006_D4_IIC_CTRL1
#else
#define _REG_DP_AUX_RX0_MAC_CTRL                            PB18002_00_AUX_MAC_CTRL
#define _REG_DP_AUX_RX0_TPS_OCCR                            PB18002_2C_TPS_OCCR
#define _REG_DP_AUX_RX0_STATUS                              PB18002_10_AUX_STATUS
#define _REG_DP_AUX_RX0_TX_TIMER                            PB18002_C0_AUX_TX_TIMER
#define _REG_DP_AUX_RX0_WILDCARD_ADDR                       PB18001_D8_AUX_WILDCARD_ADDR0
#define _REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_FLAG              PB18001_D4_AUX_WILDCARD_ADDR_IRQ_FLAG
#define _REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_EN                PB18001_D0_AUX_WILDCARD_ADDR_IRQ_EN
#define _REG_DP_AUX_RX0_DPCD_ADDR_INPUT_PORT                PB18002_60_AUX_DPCD_ACCESS_ADDR
#define _REG_DP_AUX_RX0_DPCD_DATA_INPUT_PORT                PB18002_64_AUX_DPCD_ACCESS_DATA
#define _REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL                 PB18002_68_AUX_DPCD_ACCESS_CONTROL
#define _REG_DP_AUX_RX0_DPCD_ADDR_OUTPUT_PORT               PB18002_30_DPCD_ADDR_PORT
#define _REG_DP_AUX_RX0_DPCD_DATA_OUTPUT_PORT               PB18002_34_DPCD_DATA_PORT_34
#define _REG_DP_AUX_RX0_RECIEVE_CMD                         PB18002_14_AUX_ADDR_SRC
#define _REG_DP_AUX_RX0_RECIEVE_INT_CMD                     _GEN_NONE
#define _REG_DP_AUX_RX0_REPLY_CMD                           PB18002_20_AUX_TX_CMD
#define _REG_DP_AUX_RX0_REPLY_CMD_START                     PB18002_24_AUX_TX_START
#define _REG_DP_AUX_RX0_IIC_CTRL0                           PB18002_D0_IIC_CTRL0
#define _REG_DP_AUX_RX0_IIC_CTRL1                           PB18002_D4_IIC_CTRL1

#define _REG_DP_AUX_RX1_MAC_CTRL                            PB19002_00_AUX_MAC_CTRL
#define _REG_DP_AUX_RX1_TPS_OCCR                            PB19002_2C_TPS_OCCR
#define _REG_DP_AUX_RX1_STATUS                              PB19002_10_AUX_STATUS
#define _REG_DP_AUX_RX1_TX_TIMER                            PB19002_C0_AUX_TX_TIMER
#define _REG_DP_AUX_RX1_WILDCARD_ADDR                       PB19001_D8_AUX_WILDCARD_ADDR0
#define _REG_DP_AUX_RX1_WILDCARD_ADDR_IRQ_FLAG              PB19001_D4_AUX_WILDCARD_ADDR_IRQ_FLAG
#define _REG_DP_AUX_RX1_WILDCARD_ADDR_IRQ_EN                PB19001_D0_AUX_WILDCARD_ADDR_IRQ_EN
#define _REG_DP_AUX_RX1_DPCD_ADDR_INPUT_PORT                PB19002_60_AUX_DPCD_ACCESS_ADDR
#define _REG_DP_AUX_RX1_DPCD_DATA_INPUT_PORT                PB19002_64_AUX_DPCD_ACCESS_DATA
#define _REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL                 PB19002_68_AUX_DPCD_ACCESS_CONTROL
#define _REG_DP_AUX_RX1_DPCD_ADDR_OUTPUT_PORT               PB19002_30_DPCD_ADDR_PORT
#define _REG_DP_AUX_RX1_DPCD_DATA_OUTPUT_PORT               PB19002_34_DPCD_DATA_PORT_34
#define _REG_DP_AUX_RX1_RECIEVE_CMD                         PB19002_14_AUX_ADDR_SRC
#define _REG_DP_AUX_RX1_RECIEVE_INT_CMD                     _GEN_NONE
#define _REG_DP_AUX_RX1_REPLY_CMD                           PB19002_20_AUX_TX_CMD
#define _REG_DP_AUX_RX1_REPLY_CMD_START                     PB19002_24_AUX_TX_START
#define _REG_DP_AUX_RX1_IIC_CTRL0                           PB19002_D0_IIC_CTRL0
#define _REG_DP_AUX_RX1_IIC_CTRL1                           PB19002_D4_IIC_CTRL1

#define _REG_DP_AUX_RX2_MAC_CTRL                            PB1A002_00_AUX_MAC_CTRL
#define _REG_DP_AUX_RX2_TPS_OCCR                            PB1A002_2C_TPS_OCCR
#define _REG_DP_AUX_RX2_STATUS                              PB1A002_10_AUX_STATUS
#define _REG_DP_AUX_RX2_TX_TIMER                            PB1A002_C0_AUX_TX_TIMER
#define _REG_DP_AUX_RX2_WILDCARD_ADDR                       PB1A001_D8_AUX_WILDCARD_ADDR0
#define _REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_FLAG              PB1A001_D4_AUX_WILDCARD_ADDR_IRQ_FLAG
#define _REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_EN                PB1A001_D0_AUX_WILDCARD_ADDR_IRQ_EN
#define _REG_DP_AUX_RX2_DPCD_ADDR_INPUT_PORT                PB1A002_60_AUX_DPCD_ACCESS_ADDR
#define _REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT                PB1A002_64_AUX_DPCD_ACCESS_DATA
#define _REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL                 PB1A002_68_AUX_DPCD_ACCESS_CONTROL
#define _REG_DP_AUX_RX2_DPCD_ADDR_OUTPUT_PORT               PB1A002_30_DPCD_ADDR_PORT
#define _REG_DP_AUX_RX2_DPCD_DATA_OUTPUT_PORT               PB1A002_34_DPCD_DATA_PORT_34
#define _REG_DP_AUX_RX2_RECIEVE_CMD                         PB1A002_14_AUX_ADDR_SRC
#define _REG_DP_AUX_RX2_RECIEVE_INT_CMD                     _GEN_NONE
#define _REG_DP_AUX_RX2_REPLY_CMD                           PB1A002_20_AUX_TX_CMD
#define _REG_DP_AUX_RX2_REPLY_CMD_START                     PB1A002_24_AUX_TX_START
#define _REG_DP_AUX_RX2_IIC_CTRL0                           PB1A002_D0_IIC_CTRL0
#define _REG_DP_AUX_RX2_IIC_CTRL1                           PB1A002_D4_IIC_CTRL1
#endif

//--------------------------------------------------
// DP MST 128b132b to 8b10b No SF and SDP Split New Mode
//--------------------------------------------------
#define SET_DP_MST_128B132B_TO_8B10B_NO_SF_NEW_MODE()       {ScalerSetBit(P2D_80_STATE_TO_BE, ~_BIT7, _BIT7);}

//--------------------------------------------------
// HW DP Rx Audio Mac Reg Define
//--------------------------------------------------
#define SET_DP_RX0_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(PB6_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX0_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(PB6_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX0_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(P1B_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX0_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(P1B_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX0_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(P1B_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), _BIT2);}
#define CLR_DP_RX0_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(P1B_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), 0x00);}
#define SET_DP_RX0_AUDIO_CS_TRANSFER_BY_CH1_8B10B()         {ScalerSetBit(PB6_AA_SPDIF_TX_1, ~(_BIT5 | _BIT4), _BIT4);}
#define SET_DP_RX0_AUDIO_CS_TRANSFER_BYPASS_128B132B()      {ScalerSetBit(P1B_AA_SPDIF_TX_1, ~(_BIT5 | _BIT4), _BIT5);}

#define SET_DP_RX1_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(PB9_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX1_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(PB9_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX1_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(P75_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX1_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(P75_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX1_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(P75_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), _BIT2);}
#define CLR_DP_RX1_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(P75_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), 0x00);}
#define SET_DP_RX1_AUDIO_CS_TRANSFER_BY_CH1_8B10B()         {ScalerSetBit(PB9_AA_SPDIF_TX_1, ~(_BIT5 | _BIT4), _BIT4);}
#define SET_DP_RX1_AUDIO_CS_TRANSFER_BYPASS_128B132B()      {ScalerSetBit(P75_AA_SPDIF_TX_1, ~(_BIT5 | _BIT4), _BIT5);}

#define SET_DP_RX2_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(PC7_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX2_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(PC7_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX2_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(PD4_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX2_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(PD4_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX2_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(PD4_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), _BIT2);}
#define CLR_DP_RX2_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(PD4_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), 0x00);}
#define SET_DP_RX2_AUDIO_CS_TRANSFER_BY_CH1_8B10B()         {ScalerSetBit(PC7_AA_SPDIF_TX_1, ~(_BIT5 | _BIT4), _BIT4);}
#define SET_DP_RX2_AUDIO_CS_TRANSFER_BYPASS_128B132B()      {ScalerSetBit(PD4_AA_SPDIF_TX_1, ~(_BIT5 | _BIT4), _BIT5);}

#define SET_DP_RX3_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(PEF_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX3_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(PEF_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX3_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(PF2_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX3_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(PF2_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX3_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(PF2_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), _BIT2);}
#define CLR_DP_RX3_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(PF2_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), 0x00);}
#define SET_DP_RX3_AUDIO_CS_TRANSFER_BY_CH1_8B10B()         _GEN_NONE
#define SET_DP_RX3_AUDIO_CS_TRANSFER_BYPASS_128B132B()      _GEN_NONE

#define SET_DP_RX4_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(P35_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX4_AUDIO_SP_BIT_FORCE_1_MODE_8B10B()        {ScalerSetBit(P35_B3_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX4_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(PE1_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), _BIT7);}
#define CLR_DP_RX4_AUDIO_SP_BIT_FORCE_1_MODE_128B132B()     {ScalerSetBit(PE1_CB_DP_SEC_MISC_1, ~(_BIT7 | _BIT4), 0x00);}
#define SET_DP_RX4_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(PE1_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), _BIT2);}
#define CLR_DP_RX4_AUDIO_CH_STATUS_NEW_MODE_128B132B()      {ScalerSetBit(PE1_CB_DP_SEC_MISC_1, ~(_BIT4 | _BIT2), 0x00);}
#define SET_DP_RX4_AUDIO_CS_TRANSFER_BY_CH1_8B10B()         _GEN_NONE
#define SET_DP_RX4_AUDIO_CS_TRANSFER_BYPASS_128B132B()      _GEN_NONE

#define SET_DP_TX_SEC_END_CNT_DB_8B10B()                    {ScalerSetByte(PBB_D6_ARBITER_DEBUG, 0x80);}
#define SET_DP_TX_SEC_END_CNT_DB_128B132B()                 {ScalerSetBit(P2B_D0_ARBITER_DEBUG, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);}

//--------------------------------------------------
// DPRX ADI GLOBAL IRQ
//--------------------------------------------------
#define GET_DP_RX_GLOBAL_INT_FLAG()                         (ScalerGetBit_EXINT(P6F_19_ADI_DP_IRQ7, _BIT7) == _BIT7)

#define GET_DP_AUX_RX0_GLOBAL_IRQ_FLAG()                    (ScalerGetBit_EXINT(P6F_13_ADI_DP_IRQ1, _BIT5) == _BIT5)
#define GET_DP_AUX_RX0_GLOBAL_IRQ_FLAG_T2INT()              (ScalerGetBit_T2INT(P6F_13_ADI_DP_IRQ1, _BIT5) == _BIT5)

#define GET_DP_AUX_RX1_GLOBAL_IRQ_FLAG()                    (ScalerGetBit_EXINT(P6F_13_ADI_DP_IRQ1, _BIT4) == _BIT4)
#define GET_DP_AUX_RX1_GLOBAL_IRQ_FLAG_T2INT()              (ScalerGetBit_T2INT(P6F_13_ADI_DP_IRQ1, _BIT4) == _BIT4)

#define GET_DP_AUX_RX2_GLOBAL_IRQ_FLAG()                    (ScalerGetBit_EXINT(P6F_13_ADI_DP_IRQ1, _BIT3) == _BIT3)
#define GET_DP_AUX_RX2_GLOBAL_IRQ_FLAG_T2INT()              (ScalerGetBit_T2INT(P6F_13_ADI_DP_IRQ1, _BIT3) == _BIT3)

#define GET_DP_MAC_DPHY_RX0_DPHY_GLOBAL_IRQ_FLAG()          (ScalerGetBit_EXINT(P6F_19_ADI_DP_IRQ7, _BIT4) == _BIT4)
#define GET_DP_MAC_DPHY_RX1_DPHY_GLOBAL_IRQ_FLAG()          (ScalerGetBit_EXINT(P6F_19_ADI_DP_IRQ7, _BIT3) == _BIT3)
#define GET_DP_MAC_DPHY_RX2_DPHY_GLOBAL_IRQ_FLAG()          (ScalerGetBit_EXINT(P6F_19_ADI_DP_IRQ7, _BIT2) == _BIT2)

#define GET_DP_MAC_STREAM_RX0_MAC_GLOBAL_IRQ_FLAG()         (ScalerGetBit_EXINT(P6F_13_ADI_DP_IRQ1, _BIT7) == _BIT7)
#define GET_DP_MAC_STREAM_RX1_MAC_GLOBAL_IRQ_FLAG()         (ScalerGetBit_EXINT(P6F_13_ADI_DP_IRQ1, _BIT6) == _BIT6)
#define GET_DP_MAC_STREAM_RX2_MAC_GLOBAL_IRQ_FLAG()         (ScalerGetBit_EXINT(P6F_14_ADI_DP_IRQ2, _BIT7) == _BIT7)
#define GET_DP_MAC_STREAM_RX3_MAC_GLOBAL_IRQ_FLAG()         _GEN_NONE
#define GET_DP_MAC_STREAM_RX4_MAC_GLOBAL_IRQ_FLAG()         _GEN_NONE

//--------------------------------------------------
// HDMI DPF OUTPUT
//--------------------------------------------------
#define SET_HDMI_FRL_RX3_DPF_RGB_CLK_OUTPUT_ENABLE()        {ScalerSetBit(P68_A0_DPF_OUTPUT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4));}
#define SET_HDMI_FRL_RX3_DPF_RGB_CLK_OUTPUT_DISABLE()       {ScalerSetBit(P68_A0_DPF_OUTPUT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);}
#define SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE()           {ScalerSetBit(P68_A0_DPF_OUTPUT_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);}

#define SET_HDMI_FRL_RX4_DPF_RGB_CLK_OUTPUT_ENABLE()        {ScalerSetBit(P69_A0_DPF_OUTPUT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4));}
#define SET_HDMI_FRL_RX4_DPF_RGB_CLK_OUTPUT_DISABLE()       {ScalerSetBit(P69_A0_DPF_OUTPUT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);}
#define SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE()           {ScalerSetBit(P69_A0_DPF_OUTPUT_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);}

#define SET_HDMI_RX3_OFF_MEASURE_RESET_EXINT()              {ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_28_PORT_PAGE72_HDMI_NTX1024TR0, ~(_BIT5 | _BIT3), 0x00);}
#define SET_HDMI_RX4_OFF_MEASURE_RESET_EXINT()              {ScalerSetDataPortBit_EXINT0(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0, ~(_BIT5 | _BIT3), 0x00);}

#define SET_HDMI_RX3_EMP_TIMEOUT_WD_DISABLE()               {ScalerSetBit(P67_55_EMP_TIMEOUT_2, ~(_BIT2 | _BIT1), 0x00);}
#define SET_HDMI_RX4_EMP_TIMEOUT_WD_DISABLE()               {ScalerSetBit(P1E_55_EMP_TIMEOUT_2, ~(_BIT2 | _BIT1), 0x00);}