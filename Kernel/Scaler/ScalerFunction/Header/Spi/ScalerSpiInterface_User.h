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
// ID Code      : ScalerSpiInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_SPI_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SPI_EXT_XTAL_CLK 0x00
#define _SPI_M2PLL_CLK    0x01


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//------------------------------------------------------------
// Definitions of SPI Mode
//------------------------------------------------------------
typedef enum
{
    _SPI_NORMAL_MODE = 0x00,
    _SPI_STANDARD_MODE
}EnumSpiProtocol;

typedef enum
{
#if(_SPI0_SUPPORT == _ON)
    _SPI_INTERFACE_0 = 0x00,
#endif
#if(_SPI1_SUPPORT == _ON)
    _SPI_INTERFACE_1 = 0x01,
#endif
#if(_SPI2_SUPPORT == _ON)
    _SPI_INTERFACE_2 = 0x02,
#endif
} EnumSpiInterface;

typedef enum
{
    _SPI_USE_CS0 = 0x00,
    _SPI_USE_CS1,
}EnumSpiCsSel;

typedef enum
{
    _SPI_CS_DEASSERT = 0x00,
    _SPI_CS_ASSERT,
}EnumSpiCsState;

typedef struct
{
    BYTE ucSpiClkPreDiv;                    // SPI CLK PreDivider
    BYTE ucSpiClkDiv;                       // SPI CLK Divider
    EnumSpiInterface b2SpiInterface : 2;    // 0:Use 1 SPI Interface ; 1:Use 2 SPI Interfaces ; 2:Use 3 SPI Interfaces
    EnumSpiProtocol b1SpiProtocolSel : 1;   // SPI Protocol Select
    BYTE b1SpiClkSel : 1;                   // SPI CLK Source
    BYTE b1MosiIdleState : 1;               // 0:low ; 1:high
    BYTE b1SclkIdleState : 1;               // 0:low ; 1:high
    BYTE b1SpiCsSel : 1;                    // SPI CS Pin Select, 0:CS0 ; 1:CS1
    BYTE b1SpiCsPol : 1;                    // SPI CS Pin Polarity Select, 0:low active ; 1:high active
    BYTE b2SpiCsSetup : 2;                  // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
    BYTE b2SpiCsHold : 2;                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
    BYTE b3SpiSuppressBits : 3;             // SPI Suppress Bits(value = 0~7)
}StructSpiConfigInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif

