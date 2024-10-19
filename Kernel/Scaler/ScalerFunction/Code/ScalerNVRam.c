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
// ID Code      : ScalerNVRam.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCLAER_NVRAM__

#include "ScalerFunctionInclude.h"
#include "NVRam/ScalerNVRam.h"

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
#warning "NOTE: _FLASH_4BYTE_MODE_FUNCTION_SUPPORT If be _ON Should Sync with SD!!!"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))
StructFlashInformation code tFlashInformation[] =
{
    // _FLASH_W25X20A; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x30, 0x12, 0x90, 0xEF, 0x11, 0x00, 0x06, 0x04, 0x20, 0x28, 0xBC, 0x00},
    // _FLASH_W25X21CL; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x30, 0x12, 0x90, 0xEF, 0x11, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_PM25LV020; ucUnprotectWRSR is not used here
    {0x9F, 0x7F, 0x9D, 0x7D, 0xAB, 0x9D, 0x7D, 0x7F, 0x26, 0x24, 0xD7, 0x00, 0x9C, 0x00},
    // _FLASH_MX25L2026; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x12, 0x90, 0xC2, 0x03, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_EN25F20; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x31, 0x12, 0x90, 0x1C, 0x11, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_PM25LD020; ucUnprotectWRSR is not used here
    {0x9F, 0x7F, 0x9D, 0x22, 0x90, 0x9D, 0x11, 0x7F, 0x26, 0x24, 0xD7, 0x00, 0x9C, 0x00},
    // _FLASH_MX25L2025; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x12, 0x90, 0xC2, 0x11, 0x00, 0x06, 0x04, 0x20, 0x02, 0x8C, 0x00},
    // _FLASH_MX25L4006E; ucUnprotectWRSR is not used here
    {0X9F, 0xC2, 0x20, 0x13, 0x90, 0xC2, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_SST25LF020A
    {0x90, 0xBF, 0x43, 0x00, 0x90, 0xBF, 0x43, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_W25X41CL; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x30, 0x13, 0x90, 0xEF, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_FM25F04; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x31, 0x13, 0x90, 0xA1, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_N25S40; ucUnprotectWRSR is not used here
    {0x9F, 0xD5, 0x30, 0x13, 0x90, 0xD5, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_A25L040; ucUnprotectWRSR is not used here
    {0x9F, 0x37, 0x30, 0x13, 0x90, 0x37, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_W25Q80BV; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x14, 0x90, 0xEF, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_PM25LQ020A; ucUnprotectWRSR is not used here
    {0x9F, 0x7F, 0x9D, 0x42, 0x90, 0x9D, 0x11, 0x7F, 0x26, 0x24, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_MX25L4026D; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x13, 0x90, 0xC2, 0x04, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_W25X40CL; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x30, 0x13, 0x90, 0xEF, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_EN25F20A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x31, 0x12, 0x90, 0x1C, 0x11, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_EN25F40A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x31, 0x13, 0x90, 0x1C, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_EN25Q40A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x30, 0x13, 0x90, 0x1C, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_EN25Q80; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x30, 0x14, 0x90, 0x1C, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_GD25Q80B; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x14, 0x90, 0xC8, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_GD25M21B; ucUnprotectWRSR and ucProtectWRSR is not used here
    {0x9F, 0xC8, 0x41, 0x12, 0x90, 0xC8, 0x11, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_GD25M41B; ucUnprotectWRSR and ucProtectWRSR is not used here
    {0x9F, 0xC8, 0x41, 0x13, 0x90, 0xC8, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_MX25L8006E; ucUnprotectWRSR is not used here
    {0X9F, 0xC2, 0x20, 0x14, 0x90, 0xC2, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_PM25LQ080; ucUnprotectWRSR is not used here
    {0x9F, 0x9D, 0x13, 0x44, 0x90, 0x9D, 0x13, 0x7F, 0x26, 0x24, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_GD25Q40B; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x13, 0x90, 0xC8, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_MX25L1606E; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x15, 0x90, 0xC2, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_MX25L3206E; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x16, 0x90, 0xC2, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_A25L016; ucUnprotectWRSR is not used here
    {0x9F, 0x37, 0x30, 0x15, 0x90, 0x37, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_W25Q16DV; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x15, 0x90, 0xEF, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_A25L032; ucUnprotectWRSR is not used here
    {0x9F, 0x37, 0x30, 0x16, 0x90, 0x37, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_W25Q32F; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x16, 0x90, 0xEF, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_GD25Q16; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x15, 0x90, 0xC8, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_MX25L1633E; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x24, 0x15, 0x90, 0xC2, 0x24, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_GD25Q16C; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x15, 0x90, 0xC8, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_MX25L3233F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x16, 0x90, 0xC2, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x08},
    // _FLASH_PM25LQ040; ucUnprotectWRSR is not used here
    {0x9F, 0x7F, 0x9D, 0x7E, 0x90, 0x9D, 0x7E, 0x7F, 0x26, 0x24, 0xD7, 0x00, 0x9C, 0x00},
    // _FLASH_GD25Q41B; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x13, 0x90, 0xC8, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_EN25QH32A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x70, 0x16, 0x90, 0x1C, 0x15, 0x00, 0x06, 0x04, 0x20, 0x42, 0xBC, 0x00},
    // _FLASH_MX25V1635F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x23, 0x15, 0x90, 0xC2, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_AT25SF041; ucUnprotectWRSR is not used here
    {0x9F, 0x1F, 0x84, 0x01, 0x90, 0x1F, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_MX25L6433F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x17, 0x90, 0xC2, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_PM25LQ016; ucUnprotectWRSR is not used here
    {0x9F, 0x9D, 0x14, 0x45, 0x90, 0x9D, 0x14, 0x7F, 0x26, 0x24, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_GD25Q32C; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x16, 0x90, 0xC8, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_MX25V8035F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x23, 0x14, 0x90, 0xC2, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_AT25SF321; ucUnprotectWRSR is not used here
    {0x9F, 0x1F, 0x87, 0x01, 0x90, 0x1F, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_FM25Q08A; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x40, 0x14, 0x90, 0xA1, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x10},
    // _FLASH_FM25Q04; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x40, 0x13, 0x90, 0xA1, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x20},
    // _FLASH_W25Q16JVSIM; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x70, 0x15, 0x90, 0xEF, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_W25Q32JVSIM; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x70, 0x16, 0x90, 0xEF, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_IS25LQ040B; ucUnprotectWRSR is not used here
    {0x9F, 0x9D, 0x40, 0x13, 0x90, 0x9D, 0x12, 0x00, 0x26, 0x24, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_KH25L3236F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x16, 0x90, 0xC2, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x08},
    // _FLASH_W25Q16JVSIQ; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x15, 0x90, 0xEF, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_MX25V4035F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x23, 0x13, 0x90, 0xC2, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_P25Q40H; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x60, 0x13, 0x90, 0x85, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_FM25Q08; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x40, 0x14, 0x90, 0xA1, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_P25Q80H; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x60, 0x14, 0x90, 0x85, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_P25Q16H; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x60, 0x15, 0x90, 0x85, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_BY25D40C; ucUnprotectWRSR is not used here
    {0x9F, 0x68, 0x40, 0x13, 0x90, 0x68, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_GD25VQ16C; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x42, 0x15, 0x90, 0xC8, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_MD25D80DT; ucUnprotectWRSR is not used here
    {0x9F, 0x51, 0x40, 0x14, 0x90, 0x51, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_MD25D40DT; ucUnprotectWRSR is not used here
    {0x9F, 0x51, 0x40, 0x13, 0x90, 0x51, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_EN25QH16B; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x70, 0x15, 0x90, 0x1C, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_IS25LP080D; ucUnprotectWRSR is not used here
    {0x9F, 0x9D, 0x60, 0x14, 0x90, 0x9D, 0x13, 0x00, 0x26, 0x24, 0x20, 0x02, 0xA0, 0x00},
    // _FLASH_BY25D40ASTIG; ucUnprotectWRSR is not used here
    {0x9F, 0x68, 0x40, 0x13, 0x90, 0x68, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_BY25D16ASTIG; ucUnprotectWRSR is not used here
    {0x9F, 0x68, 0x40, 0x15, 0x90, 0x68, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_BY25D80ASTIG; ucUnprotectWRSR is not used here
    {0x9F, 0x68, 0x40, 0x14, 0x90, 0x68, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C, 0x00},
    // _FLASH_XM25QH80B; ucUnprotectWRSR is not used here
    {0x9F, 0x20, 0x40, 0x14, 0x90, 0x20, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_XM25QH40B; ucUnprotectWRSR is not used here
    {0x9F, 0x20, 0x40, 0x13, 0x90, 0x20, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_XT25F08B; ucUnprotectWRSR is not used here
    {0x9F, 0x0B, 0x40, 0x14, 0x90, 0x0B, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_W25Q32JVSSIQ; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x16, 0x90, 0xEF, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_P25Q32H; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x60, 0x16, 0x90, 0x85, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_W25Q128JVSQ; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x18, 0x90, 0xEF, 0x17, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_XM25QH16C; ucUnprotectWRSR is not used here
    {0x9F, 0x20, 0x40, 0x15, 0x90, 0x20, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_BY25Q80BSTIG; ucUnprotectWRSR is not used here
    {0x9F, 0x68, 0x40, 0x14, 0x90, 0x68, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_XM25QH32CHIGT; ucUnprotectWRSR is not used here
    {0x9F, 0x20, 0x40, 0x16, 0x90, 0x20, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_AT25SF041B; ucUnprotectWRSR is not used here
    {0x9F, 0x1F, 0x84, 0x01, 0x90, 0x1F, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_AT25SF081B; ucUnprotectWRSR is not used here
    {0x9F, 0x1F, 0x85, 0x01, 0x90, 0x1F, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_AT25SF321B; ucUnprotectWRSR is not used here
    {0x9F, 0x1F, 0x87, 0x01, 0x90, 0x1F, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_W25Q64JVSIQ; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x17, 0x90, 0xEF, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_AT25SF161B; ucUnprotectWRSR is not used here
    {0x9F, 0x1F, 0x86, 0x01, 0x90, 0x1F, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_EN25QH32B; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x70, 0x16, 0x90, 0x1C, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_ZB25VQ40A; ucUnprotectWRSR is not used here
    {0x9F, 0x5E, 0x60, 0x13, 0x90, 0x5E, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_ZB25VQ80A; ucUnprotectWRSR is not used here
    {0x9F, 0x5E, 0x60, 0x14, 0x90, 0x5E, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_ZB25VQ16A; ucUnprotectWRSR is not used here
    {0x9F, 0x5E, 0x60, 0x15, 0x90, 0x5E, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_UC25HQ80IAT; ucUnprotectWRSR is not used here
    {0x9F, 0xB3, 0x60, 0x14, 0x90, 0xB3, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_IS25LP040E; ucUnprotectWRSR is not used here
    {0x9F, 0x9D, 0x40, 0x13, 0x90, 0x9D, 0x12, 0x00, 0x26, 0x24, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_IS25LP016D; ucUnprotectWRSR is not used here
    {0x9F, 0x9D, 0x60, 0x15, 0x90, 0x9D, 0x14, 0x00, 0x26, 0x24, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_ZB25VQ64B; ucUnprotectWRSR is not used here
    {0x9F, 0x5E, 0x40, 0x17, 0x90, 0x5E, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_P25Q16SH; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x60, 0x15, 0x90, 0x85, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_EN25Q80C; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x30, 0x14, 0x90, 0x1C, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_GD25Q64E; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x17, 0x90, 0xC8, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_PY25Q80HB; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x20, 0x14, 0x90, 0x85, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_GD25Q128E; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x18, 0x90, 0xC8, 0x17, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_PY25Q128HA; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x20, 0x18, 0x90, 0x85, 0x17, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_BY25Q32CSSIG; ucUnprotectWRSR is not used here
    {0x9F, 0x68, 0x40, 0x16, 0x90, 0x68, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_EN25QE16A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x41, 0x15, 0x90, 0x1C, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_EN25QE32A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x41, 0x16, 0x90, 0x1C, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_P25Q64SH; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x60, 0x17, 0x90, 0x85, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_EN25QX64A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x71, 0x17, 0x90, 0x1C, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_EN25QX128A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x71, 0x18, 0x90, 0x1C, 0x17, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_MX25L12833F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x18, 0x90, 0xC2, 0x17, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x00},
    // _FLASH_EN25Q40B; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x30, 0x13, 0x90, 0x1C, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_GT25Q80A; ucUnprotectWRSR is not used here
    {0x9F, 0xC4, 0x60, 0x14, 0x90, 0xC4, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_UC25HQ16; ucUnprotectWRSR is not used here
    {0x9F, 0xB3, 0x60, 0x15, 0x90, 0xB3, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_W25Q80RVSNIQ; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x14, 0x90, 0xEF, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_GT25Q16A; ucUnprotectWRSR is not used here
    {0x9F, 0xC4, 0x60, 0x15, 0x90, 0xC4, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_GT25Q40C; ucUnprotectWRSR is not used here
    {0x9F, 0xC4, 0x40, 0x13, 0x90, 0xC4, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_GT25Q32AU; ucUnprotectWRSR is not used here
    {0x9F, 0xC4, 0x60, 0x16, 0x90, 0xC4, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_PY25Q16HB; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x20, 0x15, 0x90, 0x85, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_MX25L25645G; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x19, 0x90, 0xC2, 0x18, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x00},
    // _FLASH_PY25Q256HB; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x20, 0x19, 0x90, 0x85, 0x18, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_PY25Q64HA; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x20, 0x17, 0x90, 0x85, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_PY25Q40HB; ucUnprotectWRSR is not used here
    {0x9F, 0x85, 0x20, 0x13, 0x90, 0x85, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_FM25Q16; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x40, 0x15, 0x90, 0xA1, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_FM25Q08B; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x40, 0x14, 0x90, 0xA1, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_ZB25VQ16C; ucUnprotectWRSR is not used here
    {0x9F, 0x5E, 0x40, 0x15, 0x90, 0x5E, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_UC25HD40I; ucUnprotectWRSR is not used here
    {0x9F, 0xB3, 0x60, 0x13, 0x90, 0xB3, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_XM25QH256C; ucUnprotectWRSR is not used here
    {0x9F, 0x20, 0x40, 0x19, 0x90, 0x20, 0x18, 0x00, 0x06, 0x04, 0x20, 0x02, 0x7C, 0x40},
    // _FLASH_FM25Q32B; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x40, 0x16, 0x90, 0xA1, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_XM25QH64D; ucUnprotectWRSR is not used here
    {0x9F, 0x20, 0x40, 0x17, 0x90, 0x20, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
    // _FLASH_FM25Q64A; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x40, 0x17, 0x90, 0xA1, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC, 0x40},
    // _FLASH_XM25QH128D; ucUnprotectWRSR is not used here
    {0x9F, 0x20, 0x40, 0x18, 0x90, 0x20, 0x17, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC, 0x40},
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))
BYTE g_ucNVRamFlashType = _FLASH_UNDETECT;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Load data from flash
// Input Value  : usBank: bank index
//                usAddr: address in usBank
//                ucLength: the data length to load
//                pucData: data buffer to save the load data
// Output Value : _TRUE for load success and _FALSE for load fail
//--------------------------------------------------
bit ScalerFlashRead(WORD usBank, BYTE *pucAddress, WORD usLength, BYTE *pucData)
{
    if(usBank == GET_CURRENT_BANK_NUMBER())
    {
        // just want to read code table from text section
        memcpy(pucData, pucAddress, usLength);
        return _TRUE;
    }

    DWORD ulSrcAddr32 = ((DWORD)pucAddress) & 0xFFFF;

#if(_HW_FLASH_READ_ACCESS_METHOD == _MEMORY_MAP_ACCESS)
    DWORD ulAbsoluteFlashAddress = (((DWORD)usBank) << 16) | ulSrcAddr32;

    if(ScalerCpuHalGetCpuFlashAddress(ulAbsoluteFlashAddress, &ulSrcAddr32) == _TRUE)
    {
        memcpy(pucData, (BYTE *)ulSrcAddr32, usLength);

        return _TRUE;
    }
    else
#endif
    {
        WORD usIndex = 0;

        // Enable flash access and address auto increase
        MCU_FF7C_ACCESS_FLASH_DATA_CTRL |= (_BIT1 | _BIT0);
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
        if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
        {
            MCU_FFA4_ACCESS_FLASH_ADDR = (BYTE)(usBank >> 8);
        }
#endif
        MCU_FF78_ACCESS_FLASH_ADDR_0 = (BYTE)(usBank);
        MCU_FF79_ACCESS_FLASH_ADDR_1 = (BYTE)(ulSrcAddr32 >> 8);
        MCU_FF7A_ACCESS_FLASH_ADDR_2 = (BYTE)(ulSrcAddr32);

        for(usIndex = 0; usIndex < usLength; usIndex++)
        {
            pucData[usIndex] = MCU_FF7B_ACCESS_FLASH_DATA_PORT;
        }

        // Disable flash access
        MCU_FF7C_ACCESS_FLASH_DATA_CTRL &= ~_BIT0;

        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Get flash bank offset
// Input Value  : None
// Output Value : GET_FLASH_BANK_OFFSET
//--------------------------------------------------
DWORD ScalerNVRamGetFlashBankOffset(void)
{
    return GET_FLASH_BANK_OFFSET();
}

#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))
//--------------------------------------------------
// Description  : Auto detect current flash type
// Input Value  : None
// Output Value : Detected flash type index
//--------------------------------------------------
void ScalerFlashDetectFlashType(void)
{
    BYTE ucIndex = 0;
    BYTE ucIDCheck1PassFlashCount = 0;
    BYTE pucIDArry[3] = {0};
    BYTE pucFlashType[8] = {0};

    // ID check 1, use 0x9F/0x90/0xAB op code base on flash spec
    for(ucIndex = 0; ucIndex < _FLASH_TOTAL_COUNT; ucIndex++)
    {
        if(ScalerFlashReadFlashIDCode(tFlashInformation[ucIndex].ucIDCheck1OpCode, pucIDArry) == _TRUE)
        {
            // ID = 0 means ignore
            if((tFlashInformation[ucIndex].ucIDCheck1_ID0 == 0x00) || (pucIDArry[0] == tFlashInformation[ucIndex].ucIDCheck1_ID0))
            {
                if((tFlashInformation[ucIndex].ucIDCheck1_ID1 == 0x00) || (pucIDArry[1] == tFlashInformation[ucIndex].ucIDCheck1_ID1))
                {
                    if((tFlashInformation[ucIndex].ucIDCheck1_ID2 == 0x00) || (pucIDArry[2] == tFlashInformation[ucIndex].ucIDCheck1_ID2))
                    {
                        // Save matched flash type index to buffer
                        pucFlashType[ucIDCheck1PassFlashCount] = ucIndex;
                        ucIDCheck1PassFlashCount++;
                    }
                }
            }
        }
        else
        {
            // Read ID code failed
            g_ucNVRamFlashType = _FLASH_DEFAULT_TYPE;
            return;
        }
    }

    // Find only one matched flash type in ID check 1
    if(ucIDCheck1PassFlashCount == 1)
    {
        g_ucNVRamFlashType = pucFlashType[0];
        return;
    }
    // Find more than one flash type in ID check 1
    else if(ucIDCheck1PassFlashCount > 1)
    {
        // Find more than 1 types in ID check 1, use ID check 2 to choose
        for(ucIndex = 0; ucIndex < ucIDCheck1PassFlashCount; ucIndex++)
        {
            // ID check 2
            if(ScalerFlashReadFlashIDCode(tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2OpCode, pucIDArry) == _TRUE)
            {
                // ID = 0 means ignore
                if((tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID0 != 0x00) && (pucIDArry[0] != tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID0))
                {
                    continue;
                }

                if((tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID1 != 0x00) && (pucIDArry[1] != tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID1))
                {
                    continue;
                }

                if((tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID2 != 0x00) && (pucIDArry[2] != tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID2))
                {
                    continue;
                }

                break;
            }
        }

        if(ucIndex >= ucIDCheck1PassFlashCount)
        {
            g_ucNVRamFlashType = pucFlashType[0];
            return;
        }
        else
        {
            g_ucNVRamFlashType = pucFlashType[ucIndex];

#if(_FLASH_TYPE_W25X20A_OR_W25X21CL == _FLASH_W25X20A)
            if(g_ucNVRamFlashType == _FLASH_W25X21CL)
            {
                g_ucNVRamFlashType = _FLASH_W25X20A;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_W25X20A)
            {
                g_ucNVRamFlashType = _FLASH_W25X21CL;
            }
#endif

#if(_FLASH_TYPE_W25X40CL_OR_W25X41CL == _FLASH_W25X40CL)
            if(g_ucNVRamFlashType == _FLASH_W25X41CL)
            {
                g_ucNVRamFlashType = _FLASH_W25X40CL;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_W25X40CL)
            {
                g_ucNVRamFlashType = _FLASH_W25X41CL;
            }
#endif

#if(_FLASH_TYPE_GD25Q16C_OR_GD25Q16 == _FLASH_GD25Q16C)
            if(g_ucNVRamFlashType == _FLASH_GD25Q16)
            {
                g_ucNVRamFlashType = _FLASH_GD25Q16C;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_GD25Q16C)
            {
                g_ucNVRamFlashType = _FLASH_GD25Q16;
            }
#endif

#if(_FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ == _FLASH_W25Q16JVSIQ)
            if(g_ucNVRamFlashType == _FLASH_W25Q16DV)
            {
                g_ucNVRamFlashType = _FLASH_W25Q16JVSIQ;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_W25Q16JVSIQ)
            {
                g_ucNVRamFlashType = _FLASH_W25Q16DV;
            }
#endif

#if(_FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F == _FLASH_KH25L3236F)
            if(g_ucNVRamFlashType == _FLASH_MX25L3206E)
            {
                g_ucNVRamFlashType = _FLASH_KH25L3236F;
            }
            if(g_ucNVRamFlashType == _FLASH_MX25L3233F)
            {
                g_ucNVRamFlashType = _FLASH_KH25L3236F;
            }
#elif(_FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F == _FLASH_MX25L3233F)
            if(g_ucNVRamFlashType == _FLASH_MX25L3206E)
            {
                g_ucNVRamFlashType = _FLASH_MX25L3233F;
            }
            if(g_ucNVRamFlashType == _FLASH_KH25L3236F)
            {
                g_ucNVRamFlashType = _FLASH_MX25L3233F;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_KH25L3236F)
            {
                g_ucNVRamFlashType = _FLASH_MX25L3206E;
            }
            if(g_ucNVRamFlashType == _FLASH_MX25L3233F)
            {
                g_ucNVRamFlashType = _FLASH_MX25L3206E;
            }
#endif

#if(_FLASH_TYPE_GD25Q40B_OR_GD25Q41B == _FLASH_GD25Q41B)
            if(g_ucNVRamFlashType == _FLASH_GD25Q40B)
            {
                g_ucNVRamFlashType = _FLASH_GD25Q41B;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_GD25Q41B)
            {
                g_ucNVRamFlashType = _FLASH_GD25Q40B;
            }
#endif

#if(_FLASH_TYPE_FM25Q08_OR_FM25Q08A_OR_FM25Q08B == _FLASH_FM25Q08B)
            if(g_ucNVRamFlashType == _FLASH_FM25Q08)
            {
                g_ucNVRamFlashType = _FLASH_FM25Q08B;
            }
            if(g_ucNVRamFlashType == _FLASH_FM25Q08A)
            {
                g_ucNVRamFlashType = _FLASH_FM25Q08B;
            }
#elif(_FLASH_TYPE_FM25Q08_OR_FM25Q08A_OR_FM25Q08B == _FLASH_FM25Q08A)
            if(g_ucNVRamFlashType == _FLASH_FM25Q08)
            {
                g_ucNVRamFlashType = _FLASH_FM25Q08A;
            }
            if(g_ucNVRamFlashType == _FLASH_FM25Q08B)
            {
                g_ucNVRamFlashType = _FLASH_FM25Q08A;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_FM25Q08A)
            {
                g_ucNVRamFlashType = _FLASH_FM25Q08;
            }
            if(g_ucNVRamFlashType == _FLASH_FM25Q08B)
            {
                g_ucNVRamFlashType = _FLASH_FM25Q08;
            }
#endif

#if(_FLASH_TYPE_BY25D40C_OR_BY25D40ASTIG == _FLASH_BY25D40C)
            if(g_ucNVRamFlashType == _FLASH_BY25D40ASTIG)
            {
                g_ucNVRamFlashType = _FLASH_BY25D40C;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_BY25D40C)
            {
                g_ucNVRamFlashType = _FLASH_BY25D40ASTIG;
            }
#endif

#if(_FLASH_TYPE_W25Q32F_OR_W25Q32JVSSIQ == _FLASH_W25Q32JVSSIQ)
            if(g_ucNVRamFlashType == _FLASH_W25Q32F)
            {
                g_ucNVRamFlashType = _FLASH_W25Q32JVSSIQ;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_W25Q32JVSSIQ)
            {
                g_ucNVRamFlashType = _FLASH_W25Q32F;
            }
#endif

#if(_FLASH_TYPE_BY25D80ASTIG_OR_BY25Q80BSTIG == _FLASH_BY25Q80BSTIG)
            if(g_ucNVRamFlashType == _FLASH_BY25D80ASTIG)
            {
                g_ucNVRamFlashType = _FLASH_BY25Q80BSTIG;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_BY25Q80BSTIG)
            {
                g_ucNVRamFlashType = _FLASH_BY25D80ASTIG;
            }
#endif

#if(_FLASH_TYPE_AT25SF041_OR_AT25SF041B == _FLASH_AT25SF041B)
            if(g_ucNVRamFlashType == _FLASH_AT25SF041)
            {
                g_ucNVRamFlashType = _FLASH_AT25SF041B;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_AT25SF041B)
            {
                g_ucNVRamFlashType = _FLASH_AT25SF041;
            }
#endif

#if(_FLASH_TYPE_AT25SF321_OR_AT25SF321B == _FLASH_AT25SF321B)
            if(g_ucNVRamFlashType == _FLASH_AT25SF321)
            {
                g_ucNVRamFlashType = _FLASH_AT25SF321B;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_AT25SF321B)
            {
                g_ucNVRamFlashType = _FLASH_AT25SF321;
            }
#endif

#if(_FLASH_TYPE_EN25QH32A_OR_EN25QH32B == _FLASH_EN25QH32B)
            if(g_ucNVRamFlashType == _FLASH_EN25QH32A)
            {
                g_ucNVRamFlashType = _FLASH_EN25QH32B;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_EN25QH32B)
            {
                g_ucNVRamFlashType = _FLASH_EN25QH32A;
            }
#endif

#if(_FLASH_TYPE_IS25LQ040B_OR_IS25LP040E == _FLASH_IS25LP040E)
            if(g_ucNVRamFlashType == _FLASH_IS25LQ040B)
            {
                g_ucNVRamFlashType = _FLASH_IS25LP040E;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_IS25LP040E)
            {
                g_ucNVRamFlashType = _FLASH_IS25LQ040B;
            }
#endif

#if(_FLASH_TYPE_P25Q16H_OR_P25Q16SH == _FLASH_P25Q16SH)
            if(g_ucNVRamFlashType == _FLASH_P25Q16H)
            {
                g_ucNVRamFlashType = _FLASH_P25Q16SH;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_P25Q16SH)
            {
                g_ucNVRamFlashType = _FLASH_P25Q16H;
            }
#endif

#if(_FLASH_TYPE_EN25Q80_OR_EN25Q80C == _FLASH_EN25Q80C)
            if(g_ucNVRamFlashType == _FLASH_EN25Q80)
            {
                g_ucNVRamFlashType = _FLASH_EN25Q80C;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_EN25Q80C)
            {
                g_ucNVRamFlashType = _FLASH_EN25Q80;
            }
#endif

#if(_FLASH_TYPE_EN25Q40A_OR_EN25Q40B == _FLASH_EN25Q40B)
            if(g_ucNVRamFlashType == _FLASH_EN25Q40A)
            {
                g_ucNVRamFlashType = _FLASH_EN25Q40B;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_EN25Q40B)
            {
                g_ucNVRamFlashType = _FLASH_EN25Q40A;
            }
#endif

#if(_FLASH_TYPE_W25Q80BV_OR_W25Q80RVSNIQ == _FLASH_W25Q80RVSNIQ)
            if(g_ucNVRamFlashType == _FLASH_W25Q80BV)
            {
                g_ucNVRamFlashType = _FLASH_W25Q80RVSNIQ;
            }
#else
            if(g_ucNVRamFlashType == _FLASH_W25Q80RVSNIQ)
            {
                g_ucNVRamFlashType = _FLASH_W25Q80BV;
            }
#endif

            return;
        }
    }

    // Do not find 1 type in ID check 1
    g_ucNVRamFlashType = _FLASH_DEFAULT_TYPE;
}

//--------------------------------------------------
// Description  : Read flash ID code
// Input Value  : ucRDIDOPCode: Read ID code op code
//                pucIDArry: Saved the ID code read from flash
// Output Value : _TRUE for read success, else return _FALSE
//--------------------------------------------------
bit ScalerFlashReadFlashIDCode(BYTE ucRDIDOPCode, BYTE *pucIDArry)
{
    BYTE ucIndex = 0;
    BYTE ucTryCount = 10;
    BYTE ucID0 = 0;
    BYTE ucID1 = 0;
    BYTE ucID2 = 0;
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    // Disable write number high bit setting
    MCU_FF77_REV_DUMMY4 &= ~_BIT5;
#endif

    switch(ucRDIDOPCode)
    {
        case 0x9F:

            //////////////////////////////////////////////////////////////////////////
            // Use JEDECID Instruction to get Flash Manufacture ID, Device ID       //
            //////////////////////////////////////////////////////////////////////////
            MCU_FF60_COMMON_INST_EN = 0x46;
            MCU_FF61_COMMON_OP_CODE = ucRDIDOPCode;
            MCU_FF60_COMMON_INST_EN = 0x47;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            pucIDArry[0] = MCU_FF67_COMMON_INST_READ_PORT0;
            pucIDArry[1] = MCU_FF68_COMMON_INST_READ_PORT1;
            pucIDArry[2] = MCU_FF69_COMMON_INST_READ_PORT2;

            // Repeatedly read flash ID code and check flash ID code data between twice RDID instructions
            for(ucIndex = 0; ucIndex < ucTryCount; ucIndex++)
            {
                usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;

                MCU_FF60_COMMON_INST_EN = 0x46;
                MCU_FF61_COMMON_OP_CODE = ucRDIDOPCode;
                MCU_FF60_COMMON_INST_EN = 0x47;

                // polling until prog common instruction done
                while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
                {
                    DELAY_5US();
                }

                ucID0 = MCU_FF67_COMMON_INST_READ_PORT0;
                ucID1 = MCU_FF68_COMMON_INST_READ_PORT1;
                ucID2 = MCU_FF69_COMMON_INST_READ_PORT2;

                if((pucIDArry[0] == ucID0) && (pucIDArry[1] == ucID1) && (pucIDArry[2] == ucID2))
                {
                    break;
                }
                else
                {
                    pucIDArry[0] = ucID0;
                    pucIDArry[1] = ucID1;
                    pucIDArry[2] = ucID2;
                }
            }

            if(ucIndex >= ucTryCount)
            {
                return _FALSE;
            }

            break;

        case 0x90:
        case 0xAB:

            //////////////////////////////////////////////////////////////////////////////////
            // Use RDID(0x90/0xAB) Instruction first to get Flash Manufacture ID, Device ID //
            //////////////////////////////////////////////////////////////////////////////////
            MCU_FF60_COMMON_INST_EN = 0x5E;
            MCU_FF61_COMMON_OP_CODE = ucRDIDOPCode;
            MCU_FF64_FLASH_PROG_ISP0 = 0x00;
            MCU_FF65_FLASH_PROG_ISP1 = 0x00;
            MCU_FF66_FLASH_PROG_ISP2 = 0x00;

            MCU_FF60_COMMON_INST_EN = 0x5F;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            pucIDArry[0] = MCU_FF67_COMMON_INST_READ_PORT0;
            pucIDArry[1] = MCU_FF68_COMMON_INST_READ_PORT1;
            pucIDArry[2] = MCU_FF69_COMMON_INST_READ_PORT2;

            for(ucIndex = 0; ucIndex < ucTryCount; ucIndex++)
            {
                usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;

                MCU_FF60_COMMON_INST_EN = 0x5E;
                MCU_FF61_COMMON_OP_CODE = ucRDIDOPCode;
                MCU_FF64_FLASH_PROG_ISP0 = 0x00;
                MCU_FF65_FLASH_PROG_ISP1 = 0x00;
                MCU_FF66_FLASH_PROG_ISP2 = 0x00;

                MCU_FF60_COMMON_INST_EN = 0x5F;

                // polling until prog common instruction done
                while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
                {
                    DELAY_5US();
                }

                ucID0 = MCU_FF67_COMMON_INST_READ_PORT0;
                ucID1 = MCU_FF68_COMMON_INST_READ_PORT1;
                ucID2 = MCU_FF69_COMMON_INST_READ_PORT2;

                if((pucIDArry[0] == ucID0) && (pucIDArry[1] == ucID1) && (pucIDArry[2] == ucID2))
                {
                    break;
                }
                else
                {
                    pucIDArry[0] = ucID0;
                    pucIDArry[1] = ucID1;
                    pucIDArry[2] = ucID2;
                }
            }

            if(ucIndex >= ucTryCount)
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : WREN instructions for serial flash
// Input Value  : ucOpCode: WREN instruction op code
// Output Value : None
//--------------------------------------------------
void ScalerFlashSetWREN(BYTE ucOpCode)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;

    // WREN instructions

    MCU_FF60_COMMON_INST_EN = 0x20;
    MCU_FF61_COMMON_OP_CODE = ucOpCode;

    MCU_FF60_COMMON_INST_EN = 0x21;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }
}

//--------------------------------------------------
// Description  : WRSR instructions for Serial Flash
// Input Value  : ucWRSR: value written to Flash Status Reg
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSetWRSR(BYTE ucWRSR, bit bIsSST)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR = 0x00;

    ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);
    if((ucWRSR & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR) == (ucRDSR & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR))
    {
        return;
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    // Disable write number high bit setting
    MCU_FF77_REV_DUMMY4 &= ~_BIT5;
#endif

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x01;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(ucWRSR);
    }
    else
#endif
    {
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR;
    }

    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

//--------------------------------------------------
// Description  : WRSR instructions for Serial Flash
// Input Value  : ucWRSR1: value written to Flash Status Register-1
//              : ucWRSR2: value written to Flash Status Register-2
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSet2ByteWRSR(BYTE ucWRSR1, BYTE ucWRSR2, bit bIsSST)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR = 0x00;
    BYTE ucRDSR2 = 0x00;

    ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);
    ucRDSR2 = ScalerFlashReadSR(_RDSR2_OPCODE);
    if(((ucWRSR1 & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR) == (ucRDSR & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)) &&
       ((ucWRSR2 & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR2) == (ucRDSR2 & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR2)))
    {
        return;
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    // Disable write number high bit setting
    MCU_FF77_REV_DUMMY4 &= ~_BIT5;
#endif

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x90;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x70;
    }

    MCU_FF61_COMMON_OP_CODE = 0x01;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(ucWRSR1);
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR2;
    }
    else
#endif
    {
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR1;
        MCU_FF65_FLASH_PROG_ISP1 = ucWRSR2;
    }

    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

//--------------------------------------------------
// Description  : WRSR instructions on two SR one by one for Serial Flash
// Input Value  : ucWRSR1: value written to Flash Status Register-1
//              : ucWRSR2: value written to Flash Status Register-2
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSet2ByteWRSRonebyone(BYTE ucWRSR1, BYTE ucWRSR2, bit bIsSST)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR = 0x00;
    BYTE ucRDSR2 = 0x00;

    ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);
    ucRDSR2 = ScalerFlashReadSR(_RDSR2_OPCODE);
    if(((ucWRSR1 & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR) == (ucRDSR & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)) &&
       ((ucWRSR2 & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR2) == (ucRDSR2 & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR2)))
    {
        return;
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    // Disable write number high bit setting
    MCU_FF77_REV_DUMMY4 &= ~_BIT5;
#endif

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x01;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(ucWRSR1);
    }
    else
#endif
    {
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR1;
    }

    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;

    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x31;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(ucWRSR2);
    }
    else
#endif
    {
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR2;
    }

    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

//--------------------------------------------------
// Description  : RDSR instructions for serial flash
// Input Value  : ucOpCode: RDSR instruction op code
// Output Value : Current SR Value
//--------------------------------------------------
BYTE ScalerFlashReadSR(BYTE ucOpCode)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR = 0;

    // Read SR

    MCU_FF60_COMMON_INST_EN = 0x42;
    MCU_FF61_COMMON_OP_CODE = ucOpCode;

    MCU_FF60_COMMON_INST_EN = 0x43;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    ucRDSR = MCU_FF67_COMMON_INST_READ_PORT0;
    return ucRDSR;
}

//--------------------------------------------------
// Description  : WRSR instructions of Status Register-4 for Serial Flash
// Input Value  : ucWRSR: value written to Flash Status Reg
//                ucCheckBit: Valid Bit of WRSR
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSet5thWRSR(BYTE ucWRSR, BYTE ucCheckBit, bit bIsSST)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR5 = 0x00;

    ucRDSR5 = ScalerFlashReadSR(_RDSR5_OPCODE);
    if((ucWRSR & ucCheckBit) == (ucRDSR5 & ucCheckBit))
    {
        return;
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    // Disable write number high bit setting
    MCU_FF77_REV_DUMMY4 &= ~_BIT5;
#endif

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0xC1;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(ucWRSR);
    }
    else
#endif
    {
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR;
    }

    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Save data to flash
// Input Value  : usBank: bank index
//                usAddr: address in usBank
//                ucLength: the data length to save
//                pucData: data buffer to save
// Output Value : _TRUE for save success and _FALSE for save fail
//--------------------------------------------------
bit ScalerFlashWrite(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData)
{
    return ScalerFlashWriteByKernel(usBank, usAddr, usLength, pucData, _TRUE, _TRUE);
}

//--------------------------------------------------
// Description  : Save data to flash
// Input Value  : usBank: bank index
//                usAddr: address in usBank
//                ucLength: the data length to save
//                pucData: data buffer to save
//                bEnFlashSR: Enable Flash SR
//                bDisFlashSR: : Disable Flash SR
// Output Value : _TRUE for save success and _FALSE for save fail
//--------------------------------------------------
bit ScalerFlashWriteByKernel(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData, bit bEnFlashSR, bit bDisFlashSR)
{
    bit bResult = _FALSE;

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    bResult = ScalerFlashWriteMainProcess(usBank, usAddr, usLength, pucData, bEnFlashSR, bDisFlashSR);
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
    bResult = ScalerFlashWriteSecondaryProcess(usBank, usAddr, usLength, pucData, bEnFlashSR, bDisFlashSR);
#endif

    ScalerCpuHalResetDataCache();
    ScalerCpuHalResetInstructionCache();

    return bResult;
}

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : Save data to flash
// Input Value  : usBank: bank index
//                usAddr: address in usBank
//                ucLength: the data length to save
//                pucData: data buffer to save
// Output Value : _TRUE for save success and _FALSE for save fail
//--------------------------------------------------
bit ScalerFlashWriteMainProcess(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData, bit bEnFlashSR, bit bDisFlashSR)
{
    BYTE ucPage = 0;
    WORD usIndex = 0;
    BYTE ucStartPage = 0;
    BYTE ucEndPage = 0;
    WORD usCurrentAddr = 0;
    WORD usLeftLength = 0;
    WORD usCurrentLength = 0;

#if(_HW_FLASH_WRITE_ACCESS_METHOD == _ISP_PROG_ACCESS)
    WORD usTimeOut = 20;
#endif

    // The access bank is smaller than than the start bank or across bank
    if(((DWORD)usAddr + usLength) > 0x10000)
    {
        return _FALSE;
    }

    // Need detect flash type when never detected
    if(g_ucNVRamFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

    ///////////////////////////////////
    //Avoid Write Across Page(Sector)//
    ///////////////////////////////////

    ucStartPage = usAddr / _FLASH_PAGE_SIZE;
    ucEndPage = ((DWORD)usAddr + usLength) / _FLASH_PAGE_SIZE + ((((DWORD)usAddr + usLength) % _FLASH_PAGE_SIZE == 0) ? 0 : 1);
    usCurrentAddr = usAddr;
    usLeftLength = usLength;

#if(_HW_FLASH_WRITE_ACCESS_METHOD == _FLASH_WRITE_PORT_ACCESS)

    // Enable flash access and address auto increase
    MCU_FF7C_ACCESS_FLASH_DATA_CTRL |= (_BIT1 | _BIT0);

#elif(_HW_FLASH_WRITE_ACCESS_METHOD == _ISP_PROG_ACCESS)
    // Disable Access Flash by 0xFF7B
    MCU_FF7C_ACCESS_FLASH_DATA_CTRL &= ~_BIT0;
#endif

    for(ucPage = ucStartPage; ucPage < ucEndPage; ucPage++)
    {
#if(_HW_FLASH_WRITE_ACCESS_METHOD == _FLASH_WRITE_PORT_ACCESS)
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
        if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
        {
            MCU_FFA4_ACCESS_FLASH_ADDR = (BYTE)(usBank >> 8);
        }
#endif
        MCU_FF78_ACCESS_FLASH_ADDR_0 = usBank;
        MCU_FF79_ACCESS_FLASH_ADDR_1 = (BYTE)(usCurrentAddr >> 8);
        MCU_FF7A_ACCESS_FLASH_ADDR_2 = (BYTE)(usCurrentAddr);
#endif

        // Assign usCurrentLength
        if(((DWORD)_FLASH_PAGE_SIZE * (ucPage + 1)) <= (usCurrentAddr + usLeftLength))
        {
            usCurrentLength = ((DWORD)_FLASH_PAGE_SIZE * (ucPage + 1)) - usCurrentAddr;
        }
        else
        {
            usCurrentLength = usLeftLength;
        }

        // Write usCurrentLength Bytes Data From usCurrentAddr
        if((g_ucNVRamFlashType == _FLASH_MX25L2026) || (g_ucNVRamFlashType == _FLASH_MX25L4026D) || (g_ucNVRamFlashType == _FLASH_BY25D40C))
        {
            for(usIndex = usCurrentAddr - usAddr; usIndex < (usCurrentAddr - usAddr) + usCurrentLength; usIndex++)
            {
                ScalerFlashWREN(usBank, ucPage);

                // When Flash Write SR Use EWSR Mode, Page Program Need Use 0x06 OP Code
                if((MCU_FF60_COMMON_INST_EN & 0xE0) == _BIT7)
                {
                    MCU_FF63_EWSR_OP_CODE = 0x06;
                }

#if(_HW_FLASH_WRITE_ACCESS_METHOD == _FLASH_WRITE_PORT_ACCESS)

                MCU_FF7B_ACCESS_FLASH_DATA_PORT = pucData[usIndex];

#elif(_HW_FLASH_WRITE_ACCESS_METHOD == _ISP_PROG_ACCESS)

                usTimeOut = 20;
                // Disable All interrupt
                SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
                if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
                {
                    ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
                }
#endif
                MCU_FF64_FLASH_PROG_ISP0 = usBank;
                MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((usAddr + usIndex) >> 8);
                MCU_FF66_FLASH_PROG_ISP2 = (BYTE)(usAddr + usIndex);

                // Set Data length 1 byte
                MCU_FF71_PROGRAM_LENGTH = 0x00;

                *((volatile BYTE *)(_HW_XRAM_ISP_MAPPING_ADDR_START)) = (pucData[usIndex]);

                // ISP programming on-going
                MCU_FF6F_PROGRAM_INSTRUCTION |= _BIT5;

                // Enable All interrupt
                SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);

                // Polling Prog Done & TimeOut
                while(((MCU_FF6F_PROGRAM_INSTRUCTION & _BIT5) == _BIT5) && (--usTimeOut > 0))
                {
                    DELAY_5US();
                }

                // 20 us Time-out
                if(usTimeOut == 0)
                {
                    return _FALSE;
                }
#endif
            }

            // After Page Program, Back Up EWSR OP Code 0x50
            if((MCU_FF60_COMMON_INST_EN & 0xE0) == _BIT7)
            {
                MCU_FF63_EWSR_OP_CODE = 0x50;
            }
            if(bDisFlashSR == _TRUE)
            {
                ScalerFlashWRDis();
            }
        }
        else
        {
            if(bEnFlashSR == _TRUE)
            {
                ScalerFlashWREN(usBank, ucPage);
            }

            // When Flash Write SR Use EWSR Mode, Page Program Need Use 0x06 OP Code
            if((MCU_FF60_COMMON_INST_EN & 0xE0) == _BIT7)
            {
                MCU_FF63_EWSR_OP_CODE = 0x06;
            }

            for(usIndex = usCurrentAddr - usAddr; usIndex < (usCurrentAddr - usAddr) + usCurrentLength; usIndex++)
            {
#if(_HW_FLASH_WRITE_ACCESS_METHOD == _FLASH_WRITE_PORT_ACCESS)

                MCU_FF7B_ACCESS_FLASH_DATA_PORT = pucData[usIndex];

#elif(_HW_FLASH_WRITE_ACCESS_METHOD == _ISP_PROG_ACCESS)
                usTimeOut = 20;
                // Disable All interrupt
                SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
                if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
                {
                    ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
                }
#endif
                MCU_FF64_FLASH_PROG_ISP0 = usBank;
                MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((usAddr + usIndex) >> 8);
                MCU_FF66_FLASH_PROG_ISP2 = (BYTE)(usAddr + usIndex);

                // Set Data length 1 byte
                MCU_FF71_PROGRAM_LENGTH = 0x00;

                *((volatile BYTE *)(_HW_XRAM_ISP_MAPPING_ADDR_START)) = pucData[usIndex];

                // ISP programming on-going
                MCU_FF6F_PROGRAM_INSTRUCTION |= _BIT5;

                // Enable All interrupt
                SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);

                // Polling Prog Done & TimeOut
                while(((MCU_FF6F_PROGRAM_INSTRUCTION & _BIT5) == _BIT5) && (--usTimeOut > 0))
                {
                    DELAY_5US();
                }

                // 20 us Time-out
                if(usTimeOut == 0)
                {
                    return _FALSE;
                }
#endif
            }

            // After Page Program, Back Up EWSR OP Code 0x50
            if((MCU_FF60_COMMON_INST_EN & 0xE0) == _BIT7)
            {
                MCU_FF63_EWSR_OP_CODE = 0x50;
            }
            if(bDisFlashSR == _TRUE)
            {
                ScalerFlashWRDis();
            }
        }

        // Assign New usCurrentLength and usLeftLength
        usCurrentAddr = usCurrentAddr + usCurrentLength;
        usLeftLength = usLeftLength - usCurrentLength;
    }

#if(_HW_FLASH_WRITE_ACCESS_METHOD == _FLASH_WRITE_PORT_ACCESS)
    // Disable flash access
    MCU_FF7C_ACCESS_FLASH_DATA_CTRL &= ~_BIT0;
#endif

    return _TRUE;
}
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Save data to flash
// Input Value  : usBank: bank index
//                usAddr: address in usBank
//                ucLength: the data length to save
//                pucData: data buffer to save
//                bEnFlashSR: Enable Flash SR
//                bDisFlashSR: : Disable Flash SR
// Output Value : _TRUE for save success and _FALSE for save fail
//--------------------------------------------------
bit ScalerFlashWriteSecondaryProcess(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData, bit bEnFlashSR, bit bDisFlashSR)
{
    WORD usIndex = 0;
    DWORD ul32BitFlashAddr = (((DWORD)usBank) << 16) | ((DWORD)usAddr);

    while(usIndex < usLength)
    {
        if((usLength - usIndex) >= 9)
        {
            if(ScalerScpuSyncIntFlashWriteCmd(ul32BitFlashAddr, 9, (&pucData[usIndex]), bEnFlashSR, bDisFlashSR) == _TRUE)
            {
                usIndex += 9;
                ul32BitFlashAddr += 9;
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
            if(ScalerScpuSyncIntFlashWriteCmd(ul32BitFlashAddr, (usLength - usIndex), (&pucData[usIndex]), bEnFlashSR, bDisFlashSR) == _TRUE)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}
#endif  // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Write enable process for serial flash
// Input Value  : usBank: bank index
//                ucPage: page index (0 ~ 15)
// Output Value : Return _TURE if succeed, else return _FALSE
//--------------------------------------------------
void ScalerFlashWREN(WORD usBank, BYTE ucPage)
{
    BYTE ucWRSR = 0x00;
    BYTE ucWRSR1 = 0x00;
    BYTE ucWRSR2 = 0x00;
    BYTE ucWRSR3 = 0x00;
    BYTE ucCheckBit = 0x00;
    BYTE ucProtectPage = 0x00;
    BYTE ucRDCR = 0x00;
    BYTE ucRDSR = 0x00;
    BYTE ucCommInst = 0x78;
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;

    // Clear watch dog
    CLR_MCU_WATCH_DOG();

    if(g_ucNVRamFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        MCU_FF77_REV_DUMMY4 |= _BIT5;
        ucCommInst = 0x60;
    }
    else
    {
        MCU_FF77_REV_DUMMY4 &= ~_BIT5;
    }
#endif

    switch(g_ucNVRamFlashType)
    {
        case _FLASH_PM25LV020:
        case _FLASH_PM25LD020:
        case _FLASH_PM25LQ020A:
        case _FLASH_PM25LQ040:
        case _FLASH_PM25LQ080:
        case _FLASH_PM25LQ016:
        case _FLASH_IS25LQ040B:
        case _FLASH_IS25LP080D:

            // Unprotect Enable
            MCU_FF60_COMMON_INST_EN = ucCommInst;
            MCU_FF61_COMMON_OP_CODE = tFlashInformation[g_ucNVRamFlashType].ucWRENOpCode;
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
            if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
            {
                ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
            }
#endif
            MCU_FF64_FLASH_PROG_ISP0 = usBank;
            MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((ucPage << 4) & 0xF0);
            MCU_FF66_FLASH_PROG_ISP2 = 0x00;
            MCU_FF60_COMMON_INST_EN |= _BIT0;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            break;

        case _FLASH_W25X20A:
            switch(usBank)
            {
                case 0:
                case 1:
                    ucWRSR = 0x0A;
                    break;

                case 2:
                case 3:
                    ucWRSR = 0x2A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_AT25SF321:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0xE4;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0xE8;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0xEC;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0xF8;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0xA4;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~63
                    ucWRSR = 0xA8;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~63
                    ucWRSR = 0xAC;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~63
                    ucWRSR = 0xB0;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                    // Protect Bank 10~63
                    ucWRSR = 0xB4;
                    ucWRSR1 = 0x40;
                    break;
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0xB8;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x98;
                    ucWRSR1 = 0x40;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x94;
                    ucWRSR1 = 0x40;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x90;
                    ucWRSR1 = 0x40;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x8C;
                    ucWRSR1 = 0x40;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x88;
                    ucWRSR1 = 0x40;
                    break;

                case 63:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0xC4;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0xC8;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0xCC;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0xD8;
                    }
                    else
                    {
                        // Protect Bank 0~62
                        ucWRSR = 0x84;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_AT25SF321B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0xE4;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0xE8;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0xEC;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0xF8;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0xA4;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~63
                    ucWRSR = 0xA8;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~63
                    ucWRSR = 0xAC;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~63
                    ucWRSR = 0xB0;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 10~63
                    ucWRSR = 0xB4;
                    ucWRSR1 = 0x40;
                    break;
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0xB8;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x98;
                    ucWRSR1 = 0x40;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x94;
                    ucWRSR1 = 0x40;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x90;
                    ucWRSR1 = 0x40;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x8C;
                    ucWRSR1 = 0x40;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x88;
                    ucWRSR1 = 0x40;
                    break;

                case 63:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0xC4;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0xC8;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0xCC;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0xD8;
                    }
                    else
                    {
                        // Protect Bank 0~62
                        ucWRSR = 0x84;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_FM25F04:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    ucWRSR = 0x02;
                    break;

                case 4:
                case 5:
                    ucWRSR = 0x1A;
                    break;

                case 6:
                    ucWRSR = 0x16;
                    break;

                case 7:
                    ucWRSR = 0x12;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_N25S40:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    ucWRSR = 0x0E;
                    break;

                case 4:
                case 5:
                    ucWRSR = 0x3A;
                    break;

                case 6:
                    ucWRSR = 0x36;
                    break;

                case 7:
                    ucWRSR = 0x32;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L2025:
            switch(usBank)
            {
                case 0:
                case 1:
                    ucWRSR = 0x0A;
                    break;

                case 2:
                    ucWRSR = 0x06;
                    break;

                case 3:
                    ucWRSR = 0x02;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L4006E:
        case _FLASH_A25L040:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    ucWRSR = 0x0E;
                    break;
                case 4:
                case 5:
                    ucWRSR = 0x0A;
                    break;
                case 6:
                    ucWRSR = 0x06;
                    break;
                case 7:
                    ucWRSR = 0x02;
                    break;
                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_W25Q80BV:
        case _FLASH_XM25QH80B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 12:
                case 13:
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 14:
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 15:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_EN25F20:
            switch(usBank)
            {
                case 0:
                case 1:
                    ucWRSR = 0x0A;
                    break;

                case 2:
                    ucWRSR = 0x06;
                    break;

                case 3:
                    if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x16;
                    }
                    else if((ucPage == 14) || (ucPage == 15))
                    {
                        ucWRSR = 0x1A;
                    }
                    else
                    {
                        ucWRSR = 0x12;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_W25X21CL:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                    ucWRSR = 0x3E;
                    break;

                case 3:
                    if(ucPage < 10)
                    {
                        ucWRSR = 0x3E;
                    }
                    else if((ucPage >= 10) && (ucPage <= 11))
                    {
                        ucWRSR = 0x5E;
                    }
                    else if((ucPage >= 12) && (ucPage <= 13))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x76;
                    }
                    else if(ucPage == 15)
                    {
                        ucWRSR = 0x7A;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Use general unprotect if BP4(bit6) do not need unlock, else use burst write to unlock BP4
            if((ucWRSR & _BIT6) == _BIT6)
            {
                // Set SRWD = 0
                ScalerFlashSetWRSR(ucWRSR & 0x7F, _FALSE);
                // Set unprotect register
                ScalerFlashSetWRSR(ucWRSR, _FALSE);
            }
            else
            {
                // Special unprotect area is not supported
            }
            break;

        case _FLASH_MX25L2026:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                    ucWRSR = 0x3E;
                    break;

                case 3:
                    if(ucPage < 10)
                    {
                        ucWRSR = 0x3E;
                    }
                    else if((ucPage >= 10) && (ucPage <= 11))
                    {
                        ucWRSR = 0x5E;
                    }
                    else if((ucPage >= 12) && (ucPage <= 13))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x76;
                    }
                    else if(ucPage == 15)
                    {
                        ucWRSR = 0x7A;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Use general unprotect if BP4(bit6) do not need unlock, else use burst write to unlock BP4
            if((ucWRSR & _BIT6) == _BIT6)
            {
                // Set SRWD = 0
                ScalerFlashSetWRSR(ucWRSR & 0x7F, _FALSE);
                // Set unprotect register
                ScalerFlashSetWRSR(ucWRSR, _FALSE);
            }
            else
            {
                // Special unprotect area is not supported
            }
            break;

        case _FLASH_MX25L4026D:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    ucWRSR = 0x3E;
                    break;

                case 7:
                    if(ucPage < 10)
                    {
                        ucWRSR = 0x3E;
                    }
                    else if((ucPage >= 10) && (ucPage <= 11))
                    {
                        ucWRSR = 0x5E;
                    }
                    else if((ucPage >= 12) && (ucPage <= 13))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x76;
                    }
                    else if(ucPage == 15)
                    {
                        ucWRSR = 0x7A;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Use general unprotect if BP4(bit6) do not need unlock, else use burst write to unlock BP4
            if((ucWRSR & _BIT6) == _BIT6)
            {
                // Set SRWD = 0
                ScalerFlashSetWRSR(ucWRSR & 0x7F, _FALSE);
                // Set unprotect register
                ScalerFlashSetWRSR(ucWRSR, _FALSE);
            }
            else
            {
                // Special unprotect area is not supported
            }
            break;

        case _FLASH_SST25LF020A:
            ScalerFlashSetWRSR(tFlashInformation[g_ucNVRamFlashType].ucUnprotectWRSR, _FALSE);
            break;

        case _FLASH_W25X41CL:
        case _FLASH_BY25D40C:
            if((usBank < 7) || ((usBank == 7) && (ucPage < 10)))
            {
                ucWRSR = 0x3E;
            }
            else if(usBank == 7)
            {
                if((ucPage >= 10) && (ucPage <= 11))
                {
                    ucWRSR = 0x5E;
                }
                else if((ucPage >= 12) && (ucPage <= 13))
                {
                    ucWRSR = 0x6E;
                }
                else if(ucPage == 14)
                {
                    ucWRSR = 0x76;
                }
                else if(ucPage == 15)
                {
                    ucWRSR = 0x7A;
                }
            }
            else
            {
                ucWRSR = 0x02;
            }

            // Use general unprotect if BP4(bit6) do not need unlock, else use burst write to unlock BP4
            if((ucWRSR & _BIT6) == _BIT6)
            {
                // Set SRWD = 0
                ScalerFlashSetWRSR(ucWRSR & 0x7F, _FALSE);
                // Set unprotect register
                ScalerFlashSetWRSR(ucWRSR, _FALSE);
            }
            else
            {
                // Special unprotect area is not supported
            }
            break;

        case _FLASH_W25X40CL:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    ucWRSR = 0x0E;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x2E;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_EN25F20A:
            switch(usBank)
            {
                case 0:
                    // Protect Bank 1~3
                    ucWRSR = 0x0E;
                    break;

                case 1:
                    // Protect Bank 2~3
                    ucWRSR = 0x0A;
                    break;

                case 2:
                    // Protect Bank 0~1
                    ucWRSR = 0x2A;
                    break;

                case 3:
                    // Protect Bank 0~2
                    ucWRSR = 0x2E;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_EN25F40A:
            switch(usBank)
            {
                case 0:
                    // Protect Bank 1~7
                    ucWRSR = 0x16;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x12;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x0E;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x2E;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x32;
                    break;

                case 7:
                    // Protect Bank 0~6
                    ucWRSR = 0x36;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_EN25Q40A:
        case _FLASH_IS25LP040E:
            switch(usBank)
            {
                case 0:
                    // Protect Bank 1~7
                    ucWRSR = 0x16;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x12;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x0E;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x2E;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x32;
                    break;

                case 7:
                    // Protect Bank 0~6
                    ucWRSR = 0x36;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_EN25Q80:
        case _FLASH_MD25D80DT:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    // Protect Bank None
                    ucWRSR = 0x02;
                    break;

                case 12:
                case 13:
                    // Protect Bank 0~11
                    ucWRSR = 0x1A;
                    break;

                case 14:
                    // Protect Bank 0~13
                    ucWRSR = 0x16;
                    break;

                case 15:
                    if(ucPage <= 7)
                    {
                        // Protect Sector 0~239
                        ucWRSR = 0x12;
                    }
                    else if((ucPage > 7) && (ucPage <= 11))
                    {
                        // Protect Sector 0~247
                        ucWRSR = 0x0E;
                    }
                    else if((ucPage > 11) && (ucPage <= 13))
                    {
                        // Protect Sector 0~251
                        ucWRSR = 0x0A;
                    }
                    else if((ucPage > 13) && (ucPage <= 15))
                    {
                        // Protect Sector 0~253
                        ucWRSR = 0x06;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MD25D40DT:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    // Protect Bank None
                    ucWRSR = 0x00;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x18;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x14;
                    break;

                case 7:
                    if(ucPage <= 7)
                    {
                        // Protect Sector 0~111
                        ucWRSR = 0x10;
                    }
                    else if((ucPage > 7) && (ucPage <= 11))
                    {
                        // Protect Sector 0~119
                        ucWRSR = 0x0C;
                    }
                    else if((ucPage > 11) && (ucPage <= 13))
                    {
                        // Protect Sector 0~123
                        ucWRSR = 0x08;
                    }
                    else if((ucPage > 13) && (ucPage <= 15))
                    {
                        // Protect Sector 0~125
                        ucWRSR = 0x04;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_GD25Q80B:
        case _FLASH_P25Q80H:
        case _FLASH_PY25Q80HB:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        // Protect Sector 1~255
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        // Protect Sector 2~255
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        // Protect Sector 4~255
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        // Protect Sector 8~255
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Sector 16~255
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;
                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;
                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                    // Protect Bank 0~7
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;
                case 12:
                case 13:
                    // Protect Bank 0~11
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;
                case 14:
                    // Protect Bank 0~13
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;
                case 15:
                    if(ucPage == 15)
                    {
                        // Protect Sector 0~254
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        // Protect Sector 0~253
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        // Protect Sector 0~251
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        // Protect Sector 0~247
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Sector 0~239
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;
                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_GD25M21B:
        case _FLASH_GD25M41B:
            // Sector Unlock Enable
            MCU_FF60_COMMON_INST_EN = ucCommInst;
            MCU_FF61_COMMON_OP_CODE = 0x4C;
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
            if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
            {
                ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
            }
#endif
            MCU_FF64_FLASH_PROG_ISP0 = usBank;
            MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((ucPage << 4) & 0xF0);
            MCU_FF66_FLASH_PROG_ISP2 = 0x00;
            MCU_FF60_COMMON_INST_EN |= _BIT0;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            break;

        case _FLASH_MX25L8006E:
        case _FLASH_EN25Q80C:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x12;
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                    // Protect Bank 12~15
                    ucWRSR = 0x0E;
                    break;
                case 12:
                case 13:
                    // Protect Bank 14~15
                    ucWRSR = 0x0A;
                    break;
                case 14:
                    // Protect Bank 15
                    ucWRSR = 0x06;
                    break;
                case 15:
                    // Protect Bank None
                    ucWRSR = 0x02;
                    break;
                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;


        case _FLASH_GD25Q40B:
        case _FLASH_GD25Q41B:
        case _FLASH_P25Q40H:
        case _FLASH_XM25QH40B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        // Protect Sector 1~127
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        // Protect Sector 2~127
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        // Protect Sector 4~127
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        // Protect Sector 8~127
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Sector 16~127
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;
                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;
                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;
                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;
                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;
                case 7:
                    if(ucPage == 15)
                    {
                        // Protect Sector 0~126
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        // Protect Sector 0~125
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        // Protect Sector 0~123
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        // Protect Sector 0~119
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Sector 0~111
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;
                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_MX25L1606E:
        case _FLASH_MX25L1633E:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 0~15
                    ucWRSR = 0x2A;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 0~23
                    ucWRSR = 0x2E;
                    break;

                case 28:
                case 29:
                    // Protect Bank 0~27
                    ucWRSR = 0x32;
                    break;

                case 30:
                    // Protect Bank 0~29
                    ucWRSR = 0x36;
                    break;

                case 31:
                    // Protect Bank 0~30
                    ucWRSR = 0x3A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L3206E:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x1A;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x26;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x2A;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x2E;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x32;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x36;
                    break;

                case 63:
                    // Protect Bank 0~62
                    ucWRSR = 0x3A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_KH25L3236F:

            ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);

            if((ucRDCR & _BIT3) == 0x08)
            {
                if(usBank == 0)
                {
                    // Protect Bank 1~63
                    ucWRSR = 0x38;
                }
                else if(usBank == 1)
                {
                    // Protect Bank 2~63
                    ucWRSR = 0x34;
                }
                else if((usBank == 2) || (usBank == 3))
                {
                    // Protect Bank 4~63
                    ucWRSR = 0x30;
                }
                else if((usBank >= 4) && (usBank <= 7))
                {
                    // Protect Bank 8~63
                    ucWRSR = 0x2C;
                }
                else if((usBank >= 8) && (usBank <= 15))
                {
                    // Protect Bank 16~63
                    ucWRSR = 0x28;
                }
                else if((usBank >= 16) && (usBank <= 31))
                {
                    // Protect Bank 32~63
                    ucWRSR = 0x24;
                }
                else if((usBank >= 32) && (usBank <= 63))
                {
                    // Protect Bank 0~31
                    ucWRSR = 0x18;
                }
                else
                {
                    ucWRSR = 0x02;
                }
            }
            else
            {
                if(usBank <= 31)
                {
                    // Protect Bank 32~63
                    ucWRSR = 0x18;
                }
                else if((usBank >= 32) && (usBank <= 47))
                {
                    // Protect Bank 0~31
                    ucWRSR = 0x24;
                }
                else if((usBank >= 48) && (usBank <= 55))
                {
                    // Protect Bank 0~47
                    ucWRSR = 0x28;
                }
                else if((usBank >= 56) && (usBank <= 59))
                {
                    // Protect Bank 0~55
                    ucWRSR = 0x2C;
                }
                else if((usBank == 60) || (usBank == 61))
                {
                    // Protect Bank 0~59
                    ucWRSR = 0x30;
                }
                else if(usBank == 62)
                {
                    // Protect Bank 0~61
                    ucWRSR = 0x34;
                }
                else if(usBank == 63)
                {
                    // Protect Bank 0~62
                    ucWRSR = 0x38;
                }
                else
                {
                    ucWRSR = 0x02;
                }
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_A25L016:
        case _FLASH_EN25QH16B:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 24~31
                    ucWRSR = 0x12;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 28~31
                    ucWRSR = 0x0E;
                    break;

                case 28:
                case 29:
                    // Protect Bank 30~31
                    ucWRSR = 0x0A;
                    break;

                case 30:
                    // Protect Bank 31
                    ucWRSR = 0x06;
                    break;

                case 31:
                    // Protect Bank None
                    ucWRSR = 0x02;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_W25Q16DV:
        case _FLASH_GD25Q16C:
        case _FLASH_P25Q16H:
        case _FLASH_GD25VQ16C:
        case _FLASH_EN25QE16A:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        // Protect Sector 1~511
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        // Protect Sector 2~511
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        // Protect Sector 4~511
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        // Protect Sector 8~511
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Sector 16~511
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~31
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~31
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~31
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 0~15
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 0~23
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 28:
                case 29:
                    // Protect Bank 0~27
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 30:
                    // Protect Bank 0~29
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 31:
                    if(ucPage == 15)
                    {
                        // Protect Sector 0~510
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        // Protect Sector 0~509
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        // Protect Sector 0~507
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        // Protect Sector 0~503
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Sector 0~495
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_A25L032:
        case _FLASH_W25Q32F:
        case _FLASH_EN25QE32A:
        case _FLASH_GT25Q32AU:
        case _FLASH_FM25Q32B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~63
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~63
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~63
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~63
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x3A;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x1A;
                    ucWRSR1 = 0x40;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 63:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~62
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_GD25Q16:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 0~15
                    ucWRSR = 0x36;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L3233F:
            ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);
#if(_FLASH_TOP_BOTTOM_PROTECT_SELECT == _FLASH_BOTTOM_PROTECT)
            // _FLASH_MX25L3233F T/B Bit is OTP Bit, Only Support Set To _FLASH_BOTTOM_PROTECT
            if((ucRDCR & _BIT3) != _BIT3)
            {
                ScalerFlashSet2ByteWRSR(0xDC, ucRDCR | _BIT3, _FALSE);
                ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);
            }
#endif
            usBank = ((ucRDCR & _BIT3) == _BIT3) ? (63 - usBank) : usBank;
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x1A;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 48~63
                    ucWRSR = 0x16;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 56~63
                    ucWRSR = 0x12;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 60~63
                    ucWRSR = 0x0E;
                    break;

                case 60:
                case 61:
                    // Protect Bank 62~63
                    ucWRSR = 0x0A;
                    break;

                case 62:
                    // Protect Bank 63
                    ucWRSR = 0x06;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_EN25QH32A:
            if(usBank <= 31)
            {
                // Protect Bank 32~63
                ucWRSR = 0x5A;
            }
            else if((usBank >= 32) && (usBank <= 63))
            {
                // Protect Bank 0~31
                ucWRSR = 0x7A;
            }
            else
            {
                ucWRSR = 0x42;
            }
            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25V1635F:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 0~15
                    ucWRSR = 0x2A;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 0~23
                    ucWRSR = 0x2E;
                    break;

                case 28:
                case 29:
                    // Protect Bank 0~27
                    ucWRSR = 0x32;
                    break;

                case 30:
                    // Protect Bank 0~29
                    ucWRSR = 0x36;
                    break;

                case 31:
                    // Protect Bank 0~30
                    ucWRSR = 0x3A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_AT25SF041:
            switch(usBank)
            {
                case 0:
                    // Protect Bank 1~7
                    ucWRSR = 0x26;
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x02A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x02E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 7:
                    // Protect Bank 0~6
                    ucWRSR = 0x06;
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_MX25L6433F:
            ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);
#if(_FLASH_TOP_BOTTOM_PROTECT_SELECT == _FLASH_BOTTOM_PROTECT)
            // _FLASH_MX25L3233F T/B Bit is OTP Bit, Only Support Set To _FLASH_BOTTOM_PROTECT
            if((ucRDCR & _BIT3) != _BIT3)
            {
                ScalerFlashSet2ByteWRSR(0xDC, ucRDCR | _BIT3, _FALSE);
                ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);
            }
#endif
            usBank = ((ucRDCR & _BIT3) == _BIT3) ? (127 - usBank) : usBank;
            if(usBank <= 63)
            {
                // Protect Bank 64~127
                ucWRSR = 0x1E;
            }
            else if((usBank >= 64) && (usBank <= 95))
            {
                // Protect Bank 96~127
                ucWRSR = 0x1A;
            }
            else if((usBank >= 96) && (usBank <= 111))
            {
                // Protect Bank 112~127
                ucWRSR = 0x16;
            }
            else if((usBank >= 112) && (usBank <= 119))
            {
                // Protect Bank 120~127
                ucWRSR = 0x12;
            }
            else if((usBank >= 120) && (usBank <= 123))
            {
                // Protect Bank 124~127
                ucWRSR = 0x0E;
            }
            else if((usBank >= 124) && (usBank <= 125))
            {
                // Protect Bank 126~127
                ucWRSR = 0x0A;
            }
            else if (usBank == 126)
            {
                // Protect Bank 127
                ucWRSR = 0x06;
            }
            else
            {
                ucWRSR = 0x02;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_GD25Q32C:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~63
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~63
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~63
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~63
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x3A;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x1A;
                    ucWRSR1 = 0x40;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 63:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~62
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_FM25Q08A:
            switch(usBank)
            {
                case 0:
                    // Protect Bank 1~15
                    ucWRSR = 0x24;
                    ucWRSR1 = 0x10;
                    break;

                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0x28;
                    ucWRSR1 = 0x10;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0x2C;
                    ucWRSR1 = 0x10;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x30;
                    ucWRSR1 = 0x10;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    // Protect Bank 0~7
                    ucWRSR = 0x10;
                    ucWRSR1 = 0x10;
                    break;

                case 12:
                case 13:
                    // Protect Bank 0~11
                    ucWRSR = 0x0C;
                    ucWRSR1 = 0x10;
                    break;

                case 14:
                    // Protect Bank 0~13
                    ucWRSR = 0x08;
                    ucWRSR1 = 0x10;
                    break;

                case 15:
                    // Protect Bank 0~14
                    ucWRSR = 0x04;
                    ucWRSR1 = 0x10;
                    break;

                default:
                    ucWRSR = 0x00;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_MX25V4035F:

            ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);

            if((ucRDCR & _BIT3) == 0x00)
            {
                switch(usBank)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        ucWRSR = 0x0E;
                        break;
                    case 4:
                    case 5:
                        ucWRSR = 0x0A;
                        break;
                    case 6:
                        ucWRSR = 0x06;
                        break;
                    case 7:
                        ucWRSR = 0x02;
                        break;
                    default:
                        ucWRSR = 0x02;
                        break;
                }
            }
            else
            {
                switch(usBank)
                {
                    case 0:
                        ucWRSR = 0x02;
                        break;
                    case 1:
                        ucWRSR = 0x06;
                        break;
                    case 2:
                    case 3:
                        ucWRSR = 0x0A;
                        break;
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        ucWRSR = 0x0E;
                        break;
                    default:
                        ucWRSR = 0x02;
                        break;
                }
            }
            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_FM25Q04:
            // Set WPS=1,Use Block Unclok
            ucWRSR1 = 0x20;
            ScalerFlashSet2ndWRSR(ucWRSR1, _FALSE);
            // Set PTB/PD for sector protect
            if(usBank <= 3)
            {
                ucProtectPage = usBank * 16 + ucPage + 1;
                ucWRSR3 = (BYTE)(ucProtectPage & 0x7F);
            }
            else // if(usBank > 3)
            {
                ucProtectPage = usBank * 16 + ucPage - 1;
                ucWRSR3 = (BYTE)(ucProtectPage | 0x80);
            }
            ucCheckBit = 0xFF;
            ScalerFlashSet4thWRSR(ucWRSR3, ucCheckBit, _FALSE);
            // Individual Sector Unlock
            MCU_FF60_COMMON_INST_EN = ucCommInst;
            MCU_FF61_COMMON_OP_CODE = 0x39;
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
            if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
            {
                ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
            }
#endif
            MCU_FF64_FLASH_PROG_ISP0 = usBank;
            MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((ucPage << 4) & 0xF0);
            MCU_FF66_FLASH_PROG_ISP2 = 0x00;
            MCU_FF60_COMMON_INST_EN |= _BIT0;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            break;

        case _FLASH_W25Q16JVSIM:
        case _FLASH_W25Q32JVSIM:
        case _FLASH_W25Q16JVSIQ:
        case _FLASH_W25Q32JVSSIQ:
        case _FLASH_P25Q32H:
        case _FLASH_P25Q16SH:
        case _FLASH_PY25Q128HA:
        case _FLASH_P25Q64SH:

            // Set WPS=1,Use Block Unclok
            ucWRSR2 = 0x64;
            ucCheckBit = ucWRSR2;
            ScalerFlashSet3rdWRSR(ucWRSR2, ucCheckBit, _FALSE);
            // Individual Block/Sector Unlock
            MCU_FF60_COMMON_INST_EN = ucCommInst;
            MCU_FF61_COMMON_OP_CODE = 0x39;
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
            if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
            {
                ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
            }
#endif
            MCU_FF64_FLASH_PROG_ISP0 = usBank;
            MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((ucPage << 4) & 0xF0);
            MCU_FF66_FLASH_PROG_ISP2 = 0x00;
            MCU_FF60_COMMON_INST_EN |= _BIT0;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            break;

        case _FLASH_FM25Q08:
            switch(usBank)
            {
                case 0:
                    // Protect Bank 1~15
                    ucWRSR = 0x24;
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0x28;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0x2C;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x30;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    // Protect Bank 0~7
                    ucWRSR = 0x10;
                    ucWRSR1 = 0x40;
                    break;

                case 12:
                case 13:
                    // Protect Bank 0~11
                    ucWRSR = 0x0C;
                    ucWRSR1 = 0x40;
                    break;

                case 14:
                    // Protect Bank 0~13
                    ucWRSR = 0x08;
                    ucWRSR1 = 0x40;
                    break;

                case 15:
                    // Protect Bank 0~14
                    ucWRSR = 0x04;
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x00;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_BY25D40ASTIG:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    // Protect Bank None
                    ucWRSR = 0x00;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x18;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x14;
                    break;

                case 7:
                    if((ucPage == 14) || (ucPage == 15))
                    {
                        ucWRSR = 0x04;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x08;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x0C;
                    }
                    else
                    {
                        // Protect Bank 0~6
                        ucWRSR = 0x10;
                    }
                    break;

                default:
                    ucWRSR = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_BY25D16ASTIG:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank None
                    ucWRSR = 0x00;
                    break;

                case 28:
                case 29:
                    // Protect Bank 0~27
                    ucWRSR = 0x18;
                    break;

                case 30:
                    // Protect Bank 0~29
                    ucWRSR = 0x14;
                    break;

                case 31:
                    if((ucPage == 14) || (ucPage == 15))
                    {
                        ucWRSR = 0x04;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x08;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x0C;
                    }
                    else
                    {
                        // Protect Bank 0~30
                        ucWRSR = 0x10;
                    }
                    break;

                default:
                    ucWRSR = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_XT25F08B:
            switch(usBank)
            {
                case 0:
                    // Protect Bank 1~15
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0x06;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 0~7
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x40;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _WRITE_SR_MODE_SEL);
            break;

        case _FLASH_BY25D80ASTIG:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    // Protect Bank None
                    ucWRSR = 0x00;
                    break;

                case 12:
                case 13:
                    // Protect Bank 0~11
                    ucWRSR = 0x18;
                    break;

                case 14:
                    // Protect Bank 0~13
                    ucWRSR = 0x14;
                    break;

                case 15:
                    if((ucPage == 14) || (ucPage == 15))
                    {
                        ucWRSR = 0x04;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x08;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x0C;
                    }
                    else
                    {
                        // Protect Bank 0~14
                        ucWRSR = 0x10;
                    }
                    break;

                default:
                    ucWRSR = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_W25Q128JVSQ:
        case _FLASH_W25Q64JVSIQ:
        case _FLASH_ZB25VQ64B:

            // Set WPS=1,Use Block Unclok
            ucWRSR2 = 0x64;
            ucCheckBit = ucWRSR2;
            ScalerFlashSet3rdWRSR(ucWRSR2, ucCheckBit, _WRITE_SR_MODE_SEL);
            // Individual Block/Sector Unlock
            MCU_FF60_COMMON_INST_EN = ucCommInst;
            MCU_FF61_COMMON_OP_CODE = 0x39;
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
            if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
            {
                ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
            }
#endif
            MCU_FF64_FLASH_PROG_ISP0 = usBank;
            MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((ucPage << 4) & 0xF0);
            MCU_FF66_FLASH_PROG_ISP2 = 0x00;
            MCU_FF60_COMMON_INST_EN |= _BIT0;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            break;

        case _FLASH_XM25QH16C:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 28:
                case 29:
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 30:
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 31:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _WRITE_SR_MODE_SEL);
            break;

        case _FLASH_BY25Q80BSTIG:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0xE6;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0xEA;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0xEE;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0xF2;
                    }
                    else
                    {
                        // Protect Bank 1~15
                        ucWRSR = 0xA6;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0xAA;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0xAE;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0xB2;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    ucWRSR = 0x92;
                    ucWRSR1 = 0x40;
                    break;

                case 12:
                case 13:
                    ucWRSR = 0x8E;
                    ucWRSR1 = 0x40;
                    break;

                case 14:
                    ucWRSR = 0x8A;
                    ucWRSR1 = 0x40;
                    break;

                case 15:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0xC6;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0xCA;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0xCE;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0xD2;
                    }
                    else
                    {
                        ucWRSR = 0x86;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _WRITE_SR_MODE_SEL);
            break;

        case _FLASH_XM25QH32CHIGT:
        case _FLASH_BY25Q32CSSIG:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~63
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~63
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~63
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~63
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x3A;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x1A;
                    ucWRSR1 = 0x40;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 63:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~62
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _WRITE_SR_MODE_SEL);
            break;

        case _FLASH_AT25SF041B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x02A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x02E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 7:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~62
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_AT25SF081B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~15
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 12:
                case 13:
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 14:
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 15:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_AT25SF161B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 28:
                case 29:
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 30:
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 31:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_EN25QH32B:
            ucRDSR = ScalerFlashReadSROnOTPMode(_ENTER_OTP_OPCODE, _EXIT_OTP_OPCODE, _RDSR_OPCODE);
#if(_FLASH_TOP_BOTTOM_PROTECT_SELECT == _FLASH_BOTTOM_PROTECT)
            // _FLASH_EN25QH32B T/B Bit is OTP Bit, Only Support Set To _FLASH_BOTTOM_PROTECT
            if((ucRDSR & _BIT3) != _BIT3)
            {
                ScalerFlashSetWRSROnOTPMode(_ENTER_OTP_OPCODE, _EXIT_OTP_OPCODE, 0x08, _FALSE);
                ucRDSR = ScalerFlashReadSROnOTPMode(_ENTER_OTP_OPCODE, _EXIT_OTP_OPCODE, _RDSR_OPCODE);
            }
#endif
            usBank = ((ucRDSR & _BIT3) == _BIT3) ? (63 - usBank) : usBank;
            switch(usBank)
            {
                case 0:
                    ucWRSR = 0x2E;
                    break;

                case 1:
                    ucWRSR = 0x2A;
                    break;

                case 2:
                case 3:
                    ucWRSR = 0x26;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x22;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    ucWRSR = 0x1E;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    ucWRSR = 0x1A;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    ucWRSR = 0x16;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    ucWRSR = 0x12;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    ucWRSR = 0x0E;
                    break;

                case 60:
                case 61:
                    ucWRSR = 0x0A;
                    break;

                case 62:
                    ucWRSR = 0x06;
                    break;

                case 63:
                    ucWRSR = 0x02;
                    break;

                default:
                    ucWRSR = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_ZB25VQ40A:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x02A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x02E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 7:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_ZB25VQ80A:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~15
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 12:
                case 13:
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 14:
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 15:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_ZB25VQ16A:
        case _FLASH_ZB25VQ16C:
        case _FLASH_FM25Q16:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 28:
                case 29:
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 30:
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 31:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_UC25HQ80IAT:
        case _FLASH_GT25Q80A:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~15
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 12:
                case 13:
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 14:
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 15:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_IS25LP016D:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 0~15
                    ucWRSR = 0x2A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_GD25Q64E:
        case _FLASH_EN25QX64A:
        case _FLASH_PY25Q64HA:
        case _FLASH_XM25QH64D:
        case _FLASH_FM25Q64A:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 2~127
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~127
                    ucWRSR = 0x26;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~127
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~127
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~127
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~127
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                case 56:
                case 57:
                case 58:
                case 59:
                case 60:
                case 61:
                case 62:
                case 63:
                    // Protect Bank 64~127
                    ucWRSR = 0x3A;
                    ucWRSR1 = 0x40;
                    break;

                case 64:
                case 65:
                case 66:
                case 67:
                case 68:
                case 69:
                case 70:
                case 71:
                case 72:
                case 73:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                case 80:
                case 81:
                case 82:
                case 83:
                case 84:
                case 85:
                case 86:
                case 87:
                case 88:
                case 89:
                case 90:
                case 91:
                case 92:
                case 93:
                case 94:
                case 95:
                    // Protect Bank 0~63
                    ucWRSR = 0x1A;
                    ucWRSR1 = 0x40;
                    break;

                case 96:
                case 97:
                case 98:
                case 99:
                case 100:
                case 101:
                case 102:
                case 103:
                case 104:
                case 105:
                case 106:
                case 107:
                case 108:
                case 109:
                case 110:
                case 111:
                    // Protect Bank 0~95
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 112:
                case 113:
                case 114:
                case 115:
                case 116:
                case 117:
                case 118:
                case 119:
                    // Protect Bank 0~111
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 120:
                case 121:
                case 122:
                case 123:
                    // Protect Bank 0~119
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 124:
                case 125:
                    // Protect Bank 0~123
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 126:
                    // Protect Bank 0~125
                    ucWRSR = 0x06;
                    ucWRSR1 = 0x40;
                    break;

                case 127:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~125
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_GD25Q128E:
        case _FLASH_EN25QX128A:
        case _FLASH_XM25QH128D:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 4~255
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                case 2:
                case 3:
                    // Protect Bank 4~255
                    ucWRSR = 0x26;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~255
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~255
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~255
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                case 56:
                case 57:
                case 58:
                case 59:
                case 60:
                case 61:
                case 62:
                case 63:
                    // Protect Bank 64~255
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 64:
                case 65:
                case 66:
                case 67:
                case 68:
                case 69:
                case 70:
                case 71:
                case 72:
                case 73:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                case 80:
                case 81:
                case 82:
                case 83:
                case 84:
                case 85:
                case 86:
                case 87:
                case 88:
                case 89:
                case 90:
                case 91:
                case 92:
                case 93:
                case 94:
                case 95:
                case 96:
                case 97:
                case 98:
                case 99:
                case 100:
                case 101:
                case 102:
                case 103:
                case 104:
                case 105:
                case 106:
                case 107:
                case 108:
                case 109:
                case 110:
                case 111:
                case 112:
                case 113:
                case 114:
                case 115:
                case 116:
                case 117:
                case 118:
                case 119:
                case 120:
                case 121:
                case 122:
                case 123:
                case 124:
                case 125:
                case 126:
                case 127:
                    // Protect Bank 128~255
                    ucWRSR = 0x3A;
                    ucWRSR1 = 0x40;
                    break;

                case 128:
                case 129:
                case 130:
                case 131:
                case 132:
                case 133:
                case 134:
                case 135:
                case 136:
                case 137:
                case 138:
                case 139:
                case 140:
                case 141:
                case 142:
                case 143:
                case 144:
                case 145:
                case 146:
                case 147:
                case 148:
                case 149:
                case 150:
                case 151:
                case 152:
                case 153:
                case 154:
                case 155:
                case 156:
                case 157:
                case 158:
                case 159:
                case 160:
                case 161:
                case 162:
                case 163:
                case 164:
                case 165:
                case 166:
                case 167:
                case 168:
                case 169:
                case 170:
                case 171:
                case 172:
                case 173:
                case 174:
                case 175:
                case 176:
                case 177:
                case 178:
                case 179:
                case 180:
                case 181:
                case 182:
                case 183:
                case 184:
                case 185:
                case 186:
                case 187:
                case 188:
                case 189:
                case 190:
                case 191:
                    // Protect Bank 0~127
                    ucWRSR = 0x1A;
                    ucWRSR1 = 0x40;
                    break;

                case 192:
                case 193:
                case 194:
                case 195:
                case 196:
                case 197:
                case 198:
                case 199:
                case 200:
                case 201:
                case 202:
                case 203:
                case 204:
                case 205:
                case 206:
                case 207:
                case 208:
                case 209:
                case 210:
                case 211:
                case 212:
                case 213:
                case 214:
                case 215:
                case 216:
                case 217:
                case 218:
                case 219:
                case 220:
                case 221:
                case 222:
                case 223:
                    // Protect Bank 0~191
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;


                case 224:
                case 225:
                case 226:
                case 227:
                case 228:
                case 229:
                case 230:
                case 231:
                case 232:
                case 233:
                case 234:
                case 235:
                case 236:
                case 237:
                case 238:
                case 239:
                    // Protect Bank 0~223
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 240:
                case 241:
                case 242:
                case 243:
                case 244:
                case 245:
                case 246:
                case 247:
                    // Protect Bank 0~239
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 248:
                case 249:
                case 250:
                case 251:
                    // Protect Bank 0~247
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 252:
                case 253:
                case 254:
                    // Protect Bank 0~251
                    ucWRSR = 0x06;
                    ucWRSR1 = 0x40;
                    break;

                case 255:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~251
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_MX25L12833F:
            ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);
#if(_FLASH_TOP_BOTTOM_PROTECT_SELECT == _FLASH_BOTTOM_PROTECT)
            // _FLASH_MX25L12833F T/B Bit is OTP Bit, Only Support Set To _FLASH_BOTTOM_PROTECT
            if((ucRDCR & _BIT3) != _BIT3)
            {
                ScalerFlashSet2ByteWRSR(0xDC, ucRDCR | _BIT3, _FALSE);
                ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);
            }
#endif
            usBank = ((ucRDCR & _BIT3) == _BIT3) ? (127 - usBank) : usBank;
            if(usBank <= 127)
            {
                // Protect Bank 128~255
                ucWRSR = 0x22;
            }
            else if((usBank >= 128) && (usBank <= 191))
            {
                // Protect Bank 192~255
                ucWRSR = 0x1E;
            }
            else if((usBank >= 192) && (usBank <= 223))
            {
                // Protect Bank 224~255
                ucWRSR = 0x1A;
            }
            else if((usBank >= 224) && (usBank <= 239))
            {
                // Protect Bank 240~255
                ucWRSR = 0x16;
            }
            else if((usBank >= 240) && (usBank <= 247))
            {
                // Protect Bank 248~255
                ucWRSR = 0x12;
            }
            else if((usBank >= 248) && (usBank <= 251))
            {
                // Protect Bank 252~255
                ucWRSR = 0x0E;
            }
            else if ((usBank >= 252) && (usBank <= 253))
            {
                // Protect Bank 254~255
                ucWRSR = 0x0A;
            }

            else if (usBank == 254)
            {
                // Protect Bank 255
                ucWRSR = 0x06;
            }
            else
            {
                ucWRSR = 0x02;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_UC25HQ16:
        case _FLASH_GT25Q16A:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~31
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~31
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~31
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~31
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 0~15
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 0~23
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 28:
                case 29:
                    // Protect Bank 0~27
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 30:
                    // Protect Bank 0~29
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 31:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~30
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_GT25Q40C:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~7
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 7:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~6
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_EN25Q40B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x02A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x02E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 7:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            ucCheckBit = ucWRSR1;
            ScalerFlashSet5thWRSR(ucWRSR1, ucCheckBit, _FALSE);
            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_PY25Q16HB:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~31
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~31
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~31
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~31
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 0~15
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 0~23
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 28:
                case 29:
                case 30:
                    // Protect Bank 0~27
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 31:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~30
                        ucWRSR = 0x0A;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_MX25L25645G:
            ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);
            if((ucRDCR & _BIT3) != _BIT3)
            {
                if(usBank <= 255)
                {
                    // Protect Bank 256~511
                    ucWRSR = 0x26;
                }
                else if((usBank >= 256) && (usBank <= 383))
                {
                    // Protect Bank 384~511
                    ucWRSR = 0x22;
                }
                else if((usBank >= 384) && (usBank <= 447))
                {
                    // Protect Bank 448~511
                    ucWRSR = 0x1E;
                }
                else if((usBank >= 448) && (usBank <= 479))
                {
                    // Protect Bank 480~511
                    ucWRSR = 0x1A;
                }
                else if((usBank >= 480) && (usBank <= 495))
                {
                    // Protect Bank 496~511
                    ucWRSR = 0x16;
                }
                else if((usBank >= 496) && (usBank <= 503))
                {
                    // Protect Bank 504~511
                    ucWRSR = 0x12;
                }
                else if((usBank >= 504) && (usBank <= 507))
                {
                    // Protect Bank 508~511
                    ucWRSR = 0x0E;
                }
                else if ((usBank >= 508) && (usBank <= 509))
                {
                    // Protect Bank 510~511
                    ucWRSR = 0x0A;
                }
                else if (usBank == 510)
                {
                    // Protect Bank 511
                    ucWRSR = 0x06;
                }
                else
                {
                    ucWRSR = 0x02;
                }
            }
            else
            {
                if(usBank == 1)
                {
                    // Protect Bank 0
                    ucWRSR = 0x06;
                }
                else if((usBank >= 2) && (usBank <= 3))
                {
                    // Protect Bank 0~1
                    ucWRSR = 0x0A;
                }
                else if((usBank >= 4) && (usBank <= 7))
                {
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                }
                else if((usBank >= 8) && (usBank <= 15))
                {
                    // Protect Bank 0~7
                    ucWRSR = 0x12;
                }
                else if((usBank >= 16) && (usBank <= 31))
                {
                    // Protect Bank 0~15
                    ucWRSR = 0x16;
                }
                else if((usBank >= 32) && (usBank <= 63))
                {
                    // Protect Bank 0~31
                    ucWRSR = 0x1A;
                }
                else if((usBank >= 64) && (usBank <= 127))
                {
                    // Protect Bank 0~63
                    ucWRSR = 0x1E;
                }
                else if((usBank >= 128) && (usBank <= 255))
                {
                    // Protect Bank 0~127
                    ucWRSR = 0x22;
                }
                else if ((usBank >= 256) && (usBank <= 511))
                {
                    // Protect Bank 0~255
                    ucWRSR = 0x26;
                }
                else
                {
                    ucWRSR = 0x02;
                }
            }
            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_PY25Q256HB:
            switch(usBank)
            {
                case 0:
                    // Protect Bank 1~511
                    ucWRSR = 0x46;
                    ucWRSR1 = 0x40;
                    break;
                case 1:
                    // Protect Bank 2~511
                    ucWRSR = 0x4A;
                    ucWRSR1 = 0x40;
                    break;
                case 2:
                case 3:
                    // Protect Bank 4~511
                    ucWRSR = 0x4E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~511
                    ucWRSR = 0x52;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~511
                    ucWRSR = 0x56;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~511
                    ucWRSR = 0x5A;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                case 56:
                case 57:
                case 58:
                case 59:
                case 60:
                case 61:
                case 62:
                case 63:
                    // Protect Bank 64~511
                    ucWRSR = 0x5E;
                    ucWRSR1 = 0x40;
                    break;

                case 64:
                case 65:
                case 66:
                case 67:
                case 68:
                case 69:
                case 70:
                case 71:
                case 72:
                case 73:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                case 80:
                case 81:
                case 82:
                case 83:
                case 84:
                case 85:
                case 86:
                case 87:
                case 88:
                case 89:
                case 90:
                case 91:
                case 92:
                case 93:
                case 94:
                case 95:
                case 96:
                case 97:
                case 98:
                case 99:
                case 100:
                case 101:
                case 102:
                case 103:
                case 104:
                case 105:
                case 106:
                case 107:
                case 108:
                case 109:
                case 110:
                case 111:
                case 112:
                case 113:
                case 114:
                case 115:
                case 116:
                case 117:
                case 118:
                case 119:
                case 120:
                case 121:
                case 122:
                case 123:
                case 124:
                case 125:
                case 126:
                case 127:
                    // Protect Bank 128~511
                    ucWRSR = 0x62;
                    ucWRSR1 = 0x40;
                    break;

                case 128:
                case 129:
                case 130:
                case 131:
                case 132:
                case 133:
                case 134:
                case 135:
                case 136:
                case 137:
                case 138:
                case 139:
                case 140:
                case 141:
                case 142:
                case 143:
                case 144:
                case 145:
                case 146:
                case 147:
                case 148:
                case 149:
                case 150:
                case 151:
                case 152:
                case 153:
                case 154:
                case 155:
                case 156:
                case 157:
                case 158:
                case 159:
                case 160:
                case 161:
                case 162:
                case 163:
                case 164:
                case 165:
                case 166:
                case 167:
                case 168:
                case 169:
                case 170:
                case 171:
                case 172:
                case 173:
                case 174:
                case 175:
                case 176:
                case 177:
                case 178:
                case 179:
                case 180:
                case 181:
                case 182:
                case 183:
                case 184:
                case 185:
                case 186:
                case 187:
                case 188:
                case 189:
                case 190:
                case 191:
                case 192:
                case 193:
                case 194:
                case 195:
                case 196:
                case 197:
                case 198:
                case 199:
                case 200:
                case 201:
                case 202:
                case 203:
                case 204:
                case 205:
                case 206:
                case 207:
                case 208:
                case 209:
                case 210:
                case 211:
                case 212:
                case 213:
                case 214:
                case 215:
                case 216:
                case 217:
                case 218:
                case 219:
                case 220:
                case 221:
                case 222:
                case 223:
                case 224:
                case 225:
                case 226:
                case 227:
                case 228:
                case 229:
                case 230:
                case 231:
                case 232:
                case 233:
                case 234:
                case 235:
                case 236:
                case 237:
                case 238:
                case 239:
                case 240:
                case 241:
                case 242:
                case 243:
                case 244:
                case 245:
                case 246:
                case 247:
                case 248:
                case 249:
                case 250:
                case 251:
                case 252:
                case 253:
                case 254:
                case 255:
                    // Protect Bank 256~511
                    ucWRSR = 0x66;
                    ucWRSR1 = 0x40;
                    break;

                case 256:
                case 257:
                case 258:
                case 259:
                case 260:
                case 261:
                case 262:
                case 263:
                case 264:
                case 265:
                case 266:
                case 267:
                case 268:
                case 269:
                case 270:
                case 271:
                case 272:
                case 273:
                case 274:
                case 275:
                case 276:
                case 277:
                case 278:
                case 279:
                case 280:
                case 281:
                case 282:
                case 283:
                case 284:
                case 285:
                case 286:
                case 287:
                case 288:
                case 289:
                case 290:
                case 291:
                case 292:
                case 293:
                case 294:
                case 295:
                case 296:
                case 297:
                case 298:
                case 299:
                case 300:
                case 301:
                case 302:
                case 303:
                case 304:
                case 305:
                case 306:
                case 307:
                case 308:
                case 309:
                case 310:
                case 311:
                case 312:
                case 313:
                case 314:
                case 315:
                case 316:
                case 317:
                case 318:
                case 319:
                case 320:
                case 321:
                case 322:
                case 323:
                case 324:
                case 325:
                case 326:
                case 327:
                case 328:
                case 329:
                case 330:
                case 331:
                case 332:
                case 333:
                case 334:
                case 335:
                case 336:
                case 337:
                case 338:
                case 339:
                case 340:
                case 341:
                case 342:
                case 343:
                case 344:
                case 345:
                case 346:
                case 347:
                case 348:
                case 349:
                case 350:
                case 351:
                case 352:
                case 353:
                case 354:
                case 355:
                case 356:
                case 357:
                case 358:
                case 359:
                case 360:
                case 361:
                case 362:
                case 363:
                case 364:
                case 365:
                case 366:
                case 367:
                case 368:
                case 369:
                case 370:
                case 371:
                case 372:
                case 373:
                case 374:
                case 375:
                case 376:
                case 377:
                case 378:
                case 379:
                case 380:
                case 381:
                case 382:
                case 383:
                    // Protect Bank 0~255
                    ucWRSR = 0x26;
                    ucWRSR1 = 0x40;
                    break;

                case 384:
                case 385:
                case 386:
                case 387:
                case 388:
                case 389:
                case 390:
                case 391:
                case 392:
                case 393:
                case 394:
                case 395:
                case 396:
                case 397:
                case 398:
                case 399:
                case 400:
                case 401:
                case 402:
                case 403:
                case 404:
                case 405:
                case 406:
                case 407:
                case 408:
                case 409:
                case 410:
                case 411:
                case 412:
                case 413:
                case 414:
                case 415:
                case 416:
                case 417:
                case 418:
                case 419:
                case 420:
                case 421:
                case 422:
                case 423:
                case 424:
                case 425:
                case 426:
                case 427:
                case 428:
                case 429:
                case 430:
                case 431:
                case 432:
                case 433:
                case 434:
                case 435:
                case 436:
                case 437:
                case 438:
                case 439:
                case 440:
                case 441:
                case 442:
                case 443:
                case 444:
                case 445:
                case 446:
                case 447:
                    // Protect Bank 0~383
                    ucWRSR = 0x22;
                    ucWRSR1 = 0x40;
                    break;

                case 448:
                case 449:
                case 450:
                case 451:
                case 452:
                case 453:
                case 454:
                case 455:
                case 456:
                case 457:
                case 458:
                case 459:
                case 460:
                case 461:
                case 462:
                case 463:
                case 464:
                case 465:
                case 466:
                case 467:
                case 468:
                case 469:
                case 470:
                case 471:
                case 472:
                case 473:
                case 474:
                case 475:
                case 476:
                case 477:
                case 478:
                case 479:
                    // Protect Bank 0~447
                    ucWRSR = 0x1E;
                    ucWRSR1 = 0x40;
                    break;

                case 480:
                case 481:
                case 482:
                case 483:
                case 484:
                case 485:
                case 486:
                case 487:
                case 488:
                case 489:
                case 490:
                case 491:
                case 492:
                case 493:
                case 494:
                case 495:
                    // Protect Bank 0~479
                    ucWRSR = 0x1A;
                    ucWRSR1 = 0x40;
                    break;

                case 496:
                case 497:
                case 498:
                case 499:
                case 500:
                case 501:
                case 502:
                case 503:
                    // Protect Bank 0~495
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 504:
                case 505:
                case 506:
                case 507:
                    // Protect Bank 0~503
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 508:
                case 509:
                    // Protect Bank 0~507
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 510:
                    // Protect Bank 0~509
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 511:
                    // Protect Bank 0~510
                    ucWRSR = 0x06;
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_MX25V8035F:
            ucRDCR = ScalerFlashReadSR(_RDCR_OPCODE);
            if((ucRDCR & _BIT3) != _BIT3)
            {
                if(usBank <= 7)
                {
                    // Protect Bank 8~15
                    ucWRSR = 0x12;
                }
                else if((usBank >= 8) && (usBank <= 11))
                {
                    // Protect Bank 12~15
                    ucWRSR = 0x0E;
                }
                else if((usBank >= 12) && (usBank <= 13))
                {
                    // Protect Bank 14~15
                    ucWRSR = 0x0A;
                }
                else if (usBank == 14)
                {
                    // Protect Bank 15
                    ucWRSR = 0x06;
                }
                else
                {
                    ucWRSR = 0x02;
                }
            }
            else
            {
                if(usBank == 1)
                {
                    // Protect Bank 0
                    ucWRSR = 0x06;
                }
                else if((usBank >= 2) && (usBank <= 3))
                {
                    // Protect Bank 0~1
                    ucWRSR = 0x0A;
                }
                else if((usBank >= 4) && (usBank <= 7))
                {
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                }
                else if((usBank >= 8) && (usBank <= 15))
                {
                    // Protect Bank 0~7
                    ucWRSR = 0x12;
                }
                else
                {
                    ucWRSR = 0x02;
                }
            }
            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_PY25Q40HB:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~7
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 7:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _TRUE);
            break;

        case _FLASH_FM25Q08B:
            switch(usBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~15
                        ucWRSR = 0x24;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~15
                    ucWRSR = 0x28;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~15
                    ucWRSR = 0x2C;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x30;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    // Protect Bank 0~7
                    ucWRSR = 0x10;
                    ucWRSR1 = 0x40;
                    break;

                case 12:
                case 13:
                    // Protect Bank 0~11
                    ucWRSR = 0x0C;
                    ucWRSR1 = 0x40;
                    break;

                case 14:
                    // Protect Bank 0~13
                    ucWRSR = 0x08;
                    ucWRSR1 = 0x40;
                    break;

                case 15:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x04;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _TRUE);
            break;

        case _FLASH_UC25HD40I:
            switch(usBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    ucWRSR = 0x30;
                    ucWRSR1 = 0x40;
                    break;
                case 5:
                case 6:
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;
                case 7:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;
                case 8:
                    if((ucPage > 12) && (ucPage <= 15))
                    {
                        ucWRSR = 0x0E;
                    }
                    else if((ucPage > 10) && (ucPage <= 12))
                    {
                        ucWRSR = 0x0A;
                    }
                    else if((ucPage > 6) && (ucPage <= 10))
                    {
                        ucWRSR = 0x06;
                    }
                    else
                    {
                        ucWRSR = 0x1E;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_XM25QH256C:
            if(usBank == 0)
            {
                // Protect Bank 1~511
                ucWRSR = 0x44;
                ucWRSR1 = 0x40;
            }
            else if(usBank == 1)
            {
                // Protect Bank 2~511
                ucWRSR = 0x48;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 2) && (usBank <= 3))
            {
                // Protect Bank 4~511
                ucWRSR = 0x4C;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 4) && (usBank <= 7))
            {
                // Protect Bank 8~511
                ucWRSR = 0x50;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 8) && (usBank <= 15))
            {
                // Protect Bank 16~511
                ucWRSR = 0x54;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 16) && (usBank <= 31))
            {
                // Protect Bank 32~511
                ucWRSR = 0x58;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 32) && (usBank <= 63))
            {
                // Protect Bank 64~511
                ucWRSR = 0x5C;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 64) && (usBank <= 127))
            {
                // Protect Bank 128~511
                ucWRSR = 0x60;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 128) && (usBank <= 255))
            {
                // Protect Bank 256~511
                ucWRSR = 0x64;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 256) && (usBank <= 383))
            {
                // Protect Bank 0~255
                ucWRSR = 0x24;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 384) && (usBank <= 447))
            {
                // Protect Bank 0~383
                ucWRSR = 0x20;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 448) && (usBank <= 479))
            {
                // Protect Bank 0~447
                ucWRSR = 0x1C;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 480) && (usBank <= 495))
            {
                // Protect Bank 0~479
                ucWRSR = 0x18;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 496) && (usBank <= 503))
            {
                // Protect Bank 0~495
                ucWRSR = 0x14;
                ucWRSR1 = 0x40;
            }
            else if((usBank >= 504) && (usBank <= 507))
            {
                // Protect Bank 0~503
                ucWRSR = 0x10;
                ucWRSR1 = 0x40;
            }
            else if ((usBank >= 508) && (usBank <= 509))
            {
                // Protect Bank 0~507
                ucWRSR = 0x0C;
                ucWRSR1 = 0x40;
            }
            else if (usBank == 510)
            {
                // Protect Bank 0~509
                ucWRSR = 0x08;
                ucWRSR1 = 0x40;
            }
            else
            {
                ucWRSR = 0x04;
                ucWRSR1 = 0x40;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_W25Q80RVSNIQ:
            switch(usBank)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x12;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    ucWRSR = 0x32;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        default:
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;
    }

    // Program OP Code
    MCU_FF6D_PROGRAM_OP_CODE = 0x02;
    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;
}

//--------------------------------------------------
// Description  : Write disable process for serial flash
// Input Value  : None
// Output Value : Return _TURE if succeed, else return _FALSE
//--------------------------------------------------
void ScalerFlashWRDis(void)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;

    // Clear watch dog
    CLR_MCU_WATCH_DOG();

    if(g_ucNVRamFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

    switch(g_ucNVRamFlashType)
    {
        case _FLASH_PM25LV020:
        case _FLASH_PM25LD020:
        case _FLASH_PM25LQ020A:
        case _FLASH_PM25LQ040:
        case _FLASH_PM25LQ080:
        case _FLASH_PM25LQ016:
        case _FLASH_IS25LQ040B:
        case _FLASH_IS25LP080D:

            // Sector Unprotect Disable
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_W25X20A:
        case _FLASH_MX25L2026:
        case _FLASH_EN25F20:
        case _FLASH_MX25L2025:
        case _FLASH_MX25L4006E:
        case _FLASH_W25X21CL:
        case _FLASH_W25X41CL:
        case _FLASH_FM25F04:
        case _FLASH_N25S40:
        case _FLASH_A25L040:
        case _FLASH_MX25L4026D:
        case _FLASH_W25X40CL:
        case _FLASH_EN25F20A:
        case _FLASH_EN25F40A:
        case _FLASH_EN25Q40A:
        case _FLASH_EN25Q80:
        case _FLASH_MX25L8006E:
        case _FLASH_MX25L1606E:
        case _FLASH_MX25L3206E:
        case _FLASH_A25L016:
        case _FLASH_MX25L1633E:
        case _FLASH_GD25Q16C:
        case _FLASH_MX25L3233F:
        case _FLASH_EN25QH32A:
        case _FLASH_MX25V1635F:
        case _FLASH_MX25L6433F:
        case _FLASH_MX25V8035F:
        case _FLASH_KH25L3236F:
        case _FLASH_MX25V4035F:
        case _FLASH_BY25D40C:
        case _FLASH_MD25D80DT:
        case _FLASH_MD25D40DT:
        case _FLASH_EN25QH16B:
        case _FLASH_BY25D40ASTIG:
        case _FLASH_BY25D16ASTIG:
        case _FLASH_BY25D80ASTIG:
        case _FLASH_EN25QH32B:
        case _FLASH_IS25LP040E:
        case _FLASH_IS25LP016D:
        case _FLASH_EN25Q80C:
        case _FLASH_MX25L12833F:
        case _FLASH_W25Q80RVSNIQ:
        case _FLASH_MX25L25645G:

            ScalerFlashSetWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_SST25LF020A:

            ScalerFlashSetWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, _TRUE);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_GD25M21B:
        case _FLASH_GD25M41B:

            // Sector Unlock Disable

            MCU_FF60_COMMON_INST_EN = 0x20;
            MCU_FF61_COMMON_OP_CODE = 0x4D;

            MCU_FF60_COMMON_INST_EN = 0x21;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_W25Q32F:
        case _FLASH_GD25Q41B:
        case _FLASH_FM25Q08A:
        case _FLASH_FM25Q08:
        case _FLASH_AT25SF041B:
        case _FLASH_AT25SF081B:
        case _FLASH_AT25SF161B:
        case _FLASH_UC25HQ80IAT:
        case _FLASH_W25Q80BV:
        case _FLASH_GD25Q80B:
        case _FLASH_GD25Q40B:
        case _FLASH_W25Q16DV:
        case _FLASH_A25L032:
        case _FLASH_GD25Q16:
        case _FLASH_AT25SF041:
        case _FLASH_AT25SF321:
        case _FLASH_P25Q40H:
        case _FLASH_P25Q80H:
        case _FLASH_P25Q16H:
        case _FLASH_GD25VQ16C:
        case _FLASH_XM25QH80B:
        case _FLASH_XM25QH40B:
        case _FLASH_PY25Q80HB:
        case _FLASH_EN25QE16A:
        case _FLASH_EN25QE32A:
        case _FLASH_GT25Q80A:
        case _FLASH_UC25HQ16:
        case _FLASH_GT25Q16A:
        case _FLASH_GT25Q40C:
        case _FLASH_GT25Q32AU:
        case _FLASH_PY25Q16HB:
        case _FLASH_PY25Q256HB:
        case _FLASH_UC25HD40I:
        case _FLASH_FM25Q32B:

            ScalerFlashSet2ByteWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, 0x00, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_FM25Q08B:
        case _FLASH_PY25Q40HB:

            ScalerFlashSet2ByteWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, 0x00, _TRUE);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_GD25Q32C:
        case _FLASH_ZB25VQ40A:
        case _FLASH_ZB25VQ80A:
        case _FLASH_ZB25VQ16A:
        case _FLASH_GD25Q64E:
        case _FLASH_GD25Q128E:
        case _FLASH_AT25SF321B:
        case _FLASH_EN25QX64A:
        case _FLASH_EN25QX128A:
        case _FLASH_PY25Q64HA:
        case _FLASH_FM25Q16:
        case _FLASH_ZB25VQ16C:
        case _FLASH_XM25QH256C:
        case _FLASH_XM25QH64D:
        case _FLASH_FM25Q64A:
        case _FLASH_XM25QH128D:

            ScalerFlashSet2ByteWRSRonebyone(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, 0x00, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_FM25Q04:
            // Global Block Lock

            MCU_FF60_COMMON_INST_EN = 0x60;
            MCU_FF61_COMMON_OP_CODE = 0x7E;

            MCU_FF60_COMMON_INST_EN = 0x61;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            //// Set PTB/PD for sector protect
            ScalerFlashSet4thWRSR(0xFF, 0xFF, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_W25Q16JVSIM:
        case _FLASH_W25Q32JVSIM:
        case _FLASH_W25Q16JVSIQ:
        case _FLASH_W25Q32JVSSIQ:
        case _FLASH_P25Q32H:
        case _FLASH_W25Q128JVSQ:
        case _FLASH_W25Q64JVSIQ:
        case _FLASH_ZB25VQ64B:
        case _FLASH_P25Q16SH:
        case _FLASH_PY25Q128HA:
        case _FLASH_P25Q64SH:

            // Global Block Lock

            MCU_FF60_COMMON_INST_EN = 0x60;
            MCU_FF61_COMMON_OP_CODE = 0x7E;

            MCU_FF60_COMMON_INST_EN = 0x61;

            // polling until prog common instruction done
            while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
            {
                DELAY_5US();
            }

            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_XT25F08B:
        case _FLASH_XM25QH16C:
        case _FLASH_BY25Q80BSTIG:
        case _FLASH_XM25QH32CHIGT:
        case _FLASH_BY25Q32CSSIG:

            ScalerFlashSet2ByteWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, 0x00, _WRITE_SR_MODE_SEL);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        case _FLASH_EN25Q40B:

            ScalerFlashSet5thWRSR(0x00, 0x00, _FALSE);
            ScalerFlashSetWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        default:

            ScalerFlashSetWRSR(0xFF, _FALSE);
            ScalerFlashSetWREN(0x04);
            break;
    }

    // Disable Program OP code
    MCU_FF6D_PROGRAM_OP_CODE = 0xFF;

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;
}

//--------------------------------------------------
// Description  : WRSR instructions of Status Register-2 for Serial Flash
// Input Value  : ucWRSR: value written to Flash Status Reg
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSet2ndWRSR(BYTE ucWRSR, bit bIsSST)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR2 = 0x00;

    ucRDSR2 = ScalerFlashReadSR(_RDSR2_OPCODE);
    if((ucWRSR & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR2) == (ucRDSR2 & tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR2))
    {
        return;
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    // Disable write number high bit setting
    MCU_FF77_REV_DUMMY4 &= ~_BIT5;
#endif

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x31;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(ucWRSR);
    }
    else
#endif
    {
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR;
    }

    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

//--------------------------------------------------
// Description  : WRSR instructions of Status Register-3 for Serial Flash
// Input Value  : ucWRSR: value written to Flash Status Reg
//                ucCheckBit: Valid Bit of WRSR
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSet3rdWRSR(BYTE ucWRSR, BYTE ucCheckBit, bit bIsSST)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR3 = 0x00;

    ucRDSR3 = ScalerFlashReadSR(_RDCR_OPCODE);
    if((ucWRSR & ucCheckBit) == (ucRDSR3 & ucCheckBit))
    {
        return;
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    // Disable write number high bit setting
    MCU_FF77_REV_DUMMY4 &= ~_BIT5;
#endif

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x11;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(ucWRSR);
    }
    else
#endif
    {
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR;
    }

    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

//--------------------------------------------------
// Description  : WRSR instructions of Status Register-4 for Serial Flash
// Input Value  : ucWRSR: value written to Flash Status Reg
//                ucCheckBit: Valid Bit of WRSR
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSet4thWRSR(BYTE ucWRSR, BYTE ucCheckBit, bit bIsSST)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR4 = 0x00;

    ucRDSR4 = ScalerFlashReadSR(_RDSR4_OPCODE);
    if((ucWRSR & ucCheckBit) == (ucRDSR4 & ucCheckBit))
    {
        return;
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    // Disable write number high bit setting
    MCU_FF77_REV_DUMMY4 &= ~_BIT5;
#endif

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x41;

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(ucWRSR);
    }
    else
#endif
    {
        MCU_FF64_FLASH_PROG_ISP0 = ucWRSR;
    }

    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // polling until prog common instruction done
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}


//--------------------------------------------------
// Description  : RDSR instructions for serial flash On OTP Mode
// Input Value  : ucEnterOTPOpCode  : Enter OTP Mode OpCode
//                ucExitOTPOpCode   : Exit OTP Mode OpCode
//                ucOpCode          : RDSR instruction op code
// Output Value : Current SR Value
//--------------------------------------------------
BYTE ScalerFlashReadSROnOTPMode(BYTE ucEnterOTPOpCode, BYTE ucExitOTPOpCode, BYTE ucOpCode)
{
    BYTE ucRDSR = 0;

    // Enter OTP Mode
    ScalerFlashSetWREN(ucEnterOTPOpCode);

    // Read Status Register
    ucRDSR = ScalerFlashReadSR(ucOpCode);

    // Exit OTP Mode
    ScalerFlashSetWREN(ucExitOTPOpCode);

    return ucRDSR;
}

#if(_FLASH_TOP_BOTTOM_PROTECT_SELECT == _FLASH_BOTTOM_PROTECT)
//--------------------------------------------------
// Description  : WRSR instructions for Serial Flash On OTP Mode
// Input Value  : ucEnterOTPOpCode  : Enter OTP Mode OpCode
//                ucExitOTPOpCode   : Exit OTP Mode OpCode
//                ucWRSR            : value written to Flash Status Reg
//                ucIsSST           : _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSetWRSROnOTPMode(BYTE ucEnterOTPOpCode, BYTE ucExitOTPOpCode, BYTE ucWRSR, bit bIsSST)
{
    // Enter OTP Mode
    ScalerFlashSetWREN(ucEnterOTPOpCode);

    // Write Status Register
    ScalerFlashSetWRSR(ucWRSR, bIsSST);

    // Exit OTP Mode
    ScalerFlashSetWREN(ucExitOTPOpCode);
}
#endif // End of #if(_FLASH_TOP_BOTTOM_PROTECT_SELECT == _FLASH_BOTTOM_PROTECT)

//--------------------------------------------------
// Description  : Erase page
// Input Value  : usBank: bank index
//                ucPage: page index (0 ~ 15)
//                bEnFlashSR: Need Enable Enable SR
//                bDisFlashSR: Need Enable Disable SR
// Output Value : _TRUE for erase success and _FALSE for erase fail
//--------------------------------------------------
bit ScalerFlashErasePage(WORD usBank, BYTE ucPage, bit bEnFlashSR, bit bDisFlashSR)
{
    bit bResult = _FALSE;

    bEnFlashSR = bEnFlashSR;
    bDisFlashSR = bDisFlashSR;

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    bResult = ScalerFlashErasePageMainProcess(usBank, ucPage, bEnFlashSR, bDisFlashSR);
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
    bResult = ScalerScpuSyncIntErasePageCmd(usBank, ucPage);
#endif

    ScalerCpuHalResetDataCache();
    ScalerCpuHalResetInstructionCache();

    return bResult;
}

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : Erase page
// Input Value  : ucBank: bank index
//                ucPage: page index (0 ~ 15)
//                bEnFlashSR: Need Enable Enable SR
//                bDisFlashSR: Need Enable Disable SR
// Output Value : _TRUE for erase success and _FALSE for erase fail
//--------------------------------------------------
bit ScalerFlashErasePageMainProcess(WORD usBank, BYTE ucPage, bit bEnFlashSR, bit bDisFlashSR)
{
    WORD usTimeOut = 500;
    BYTE ucCommInst = 0xB8;

    if(g_ucNVRamFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

    if(g_ucNVRamFlashType >= (sizeof(tFlashInformation) / sizeof(tFlashInformation[0])))
    {
        return _FALSE;
    }

    if(bEnFlashSR == _TRUE)
    {
        ScalerFlashWREN(usBank, ucPage);
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        MCU_FF77_REV_DUMMY4 |= _BIT5;
        ucCommInst = 0xA0;
    }
    else
    {
        MCU_FF77_REV_DUMMY4 &= ~_BIT5;
    }
#endif

    // Sector Erase
    MCU_FF60_COMMON_INST_EN = ucCommInst;
    MCU_FF61_COMMON_OP_CODE = tFlashInformation[g_ucNVRamFlashType].ucPageEraseOpCode;

    // Set WR address
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
    }
#endif
    MCU_FF64_FLASH_PROG_ISP0 = usBank;
    MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((ucPage << 4) & 0xF0);
    MCU_FF66_FLASH_PROG_ISP2 = 0x00;

    // Start Bit0
    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // Polling Prog Done & TimeOut
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        ScalerTimerDelayXms(1);
    }

    // 500 ms Time-out
    if(usTimeOut == 0)
    {
        return _FALSE;
    }

    MCU_FF61_COMMON_OP_CODE = 0xFF;

    if(bDisFlashSR == _TRUE)
    {
        ScalerFlashWRDis();
    }

    return _TRUE;
}
#endif

#if((_BILLBOARD_SUPPORT == _ON) || (_FW_UPDATE_PROCESS_SUPPORT == _ON) || (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Erase page
// Input Value  : usBank: bank index
//                bEnFlashSR: Need Enable Enable SR
//                bDisFlashSR: Need Enable Disable SR
// Output Value : _TRUE for erase success and _FALSE for erase fail
//--------------------------------------------------
bit ScalerFlashEraseBank(WORD usBank, bit bEnFlashSR, bit bDisFlashSR)
{
    bit bResult = _FALSE;

    WORD usTimeOut = 2500;
    BYTE ucCommInst = 0xB8;

    if(bEnFlashSR == _TRUE)
    {
        if(g_ucNVRamFlashType == _FLASH_UNDETECT)
        {
            ScalerFlashDetectFlashType();
        }
        ScalerFlashWREN(usBank, 0xFF);
    }

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        MCU_FF77_REV_DUMMY4 |= _BIT5;
        ucCommInst = 0xA0;
    }
    else
    {
        MCU_FF77_REV_DUMMY4 &= ~_BIT5;
    }
#endif


    // Sector Erase
    MCU_FF60_COMMON_INST_EN = ucCommInst;
    MCU_FF61_COMMON_OP_CODE = 0xD8;

    // Set WR address
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
    }
#endif
    MCU_FF64_FLASH_PROG_ISP0 = usBank;
    MCU_FF65_FLASH_PROG_ISP1 = 0;
    MCU_FF66_FLASH_PROG_ISP2 = 0x00;

    // Start Bit0
    MCU_FF60_COMMON_INST_EN |= _BIT0;

    // Polling Erase Done & TimeOut
    while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
    {
        ScalerTimerDelayXms(1);
    }

    // 2500 ms Time-out
    if(usTimeOut == 0)
    {
        bResult = _FALSE;
    }
    else
    {
        bResult = _TRUE;

        MCU_FF61_COMMON_OP_CODE = 0xFF;

        if(bDisFlashSR == _TRUE)
        {
            ScalerFlashWRDis();
        }
    }

    ScalerCpuHalResetDataCache();
    ScalerCpuHalResetInstructionCache();

    return bResult;
}

//--------------------------------------------------
// Description  : Write 256byte to Flash using ISP program mode
// Input Value  : usBank: bank index
//                usAddr: address in usBank
//                ucLength: the data length to save
//                bEnFlashSR: Enable Flash SR
//                bDisFlashSR: : Disable Flash SR
// Output Value : _TRUE for save success and _FALSE for save fail
//--------------------------------------------------
bit ScalerFlashWritePageProgram(WORD usBank, WORD usAddr, WORD usLength, bit bEnFlashSR, bit bDisFlashSR)
{
    bit bResult = _FALSE;

    BYTE ucStartPage = 0;
    WORD usTimeOut = 20000;

    // The access bank is smaller than than the start bank or across bank
    if(((DWORD)usAddr + usLength) > 0x10000)
    {
        return _FALSE;
    }

    // Need detect flash type when never detected
    if(g_ucNVRamFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

    ///////////////////////////////////
    //Avoid Write Across Page(Sector)//
    ///////////////////////////////////
    if(bEnFlashSR == _TRUE)
    {
        ucStartPage = usAddr / _FLASH_PAGE_SIZE;
        ScalerFlashWREN(usBank, ucStartPage);
    }

    // Disable All interrupt
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet((BYTE)(usBank >> 8));
    }
#endif
    MCU_FF64_FLASH_PROG_ISP0 = usBank;
    MCU_FF65_FLASH_PROG_ISP1 = (BYTE)(usAddr >> 8);
    MCU_FF66_FLASH_PROG_ISP2 = (BYTE)usAddr;

    // Set Data length
    MCU_FF71_PROGRAM_LENGTH = usLength - 1;

    // ISP programming on-going

    MCU_FF6F_PROGRAM_INSTRUCTION |= _BIT5;

    // Enable All interrupt
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);

    // Polling Prog Done & TimeOut
    while(((MCU_FF6F_PROGRAM_INSTRUCTION & _BIT5) == _BIT5) && (--usTimeOut > 0))
    {
        DELAY_5US();
    }

    // 100 ms Time-out
    if(usTimeOut == 0)
    {
        bResult = _FALSE;
    }
    else
    {
        bResult = _TRUE;

        if(bDisFlashSR == _TRUE)
        {
            ScalerFlashWRDis();
        }
    }

    ScalerCpuHalResetDataCache();
    ScalerCpuHalResetInstructionCache();

    return bResult;
}

#endif // End of #if((_BILLBOARD_SUPPORT == _ON) || ((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT) && (_IMAGE_FILE_LAYOUT_MODE == _IMAGE_BOOT_COPY_USER)))
#endif // End of #if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)

#if(_FLASH_WR_PROTECT == _ON)
//--------------------------------------------------
// Description  : Set SR to protect flash
// Input Value  : None
// Output Value : Return _TURE if succeed, else return _FALSE
//--------------------------------------------------
void ScalerFlashWRProtect(void)
{
    WORD usTimeOut = _FLASH_COMMON_INST_POLLING_TIME;
    BYTE ucRDSR = 0;

    // Clear watch dog
    CLR_MCU_WATCH_DOG();

    // Detect flash type first
    if(g_ucNVRamFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

    switch(g_ucNVRamFlashType)
    {
        case _FLASH_PM25LV020:
        case _FLASH_PM25LD020:
        case _FLASH_PM25LQ020A:
        case _FLASH_PM25LQ040:
        case _FLASH_PM25LQ080:
        case _FLASH_W25X20A:
        case _FLASH_MX25L2026:
        case _FLASH_EN25F20:
        case _FLASH_MX25L2025:
        case _FLASH_MX25L4006E:
        case _FLASH_W25X21CL:
        case _FLASH_W25X41CL:
        case _FLASH_FM25F04:
        case _FLASH_N25S40:
        case _FLASH_A25L040:
        case _FLASH_MX25L4026D:
        case _FLASH_W25X40CL:
        case _FLASH_EN25F20A:
        case _FLASH_EN25F40A:
        case _FLASH_EN25Q40A:
        case _FLASH_EN25Q80:
        case _FLASH_MX25L8006E:
        case _FLASH_MX25L1606E:
        case _FLASH_MX25L3206E:
        case _FLASH_A25L016:
        case _FLASH_MX25L1633E:
        case _FLASH_GD25Q16C:
        case _FLASH_MX25L3233F:
        case _FLASH_EN25QH32A:
        case _FLASH_MX25V1635F:
        case _FLASH_MX25L6433F:
        case _FLASH_PM25LQ016:
        case _FLASH_MX25V8035F:
        case _FLASH_IS25LQ040B:
        case _FLASH_KH25L3236F:
        case _FLASH_MX25V4035F:
        case _FLASH_BY25D40C:
        case _FLASH_MD25D80DT:
        case _FLASH_MD25D40DT:
        case _FLASH_EN25QH16B:
        case _FLASH_IS25LP080D:
        case _FLASH_BY25D40ASTIG:
        case _FLASH_BY25D16ASTIG:
        case _FLASH_BY25D80ASTIG:
        case _FLASH_EN25QH32B:
        case _FLASH_IS25LP040E:
        case _FLASH_IS25LP016D:
        case _FLASH_EN25Q80C:
        case _FLASH_MX25L12833F:
        case _FLASH_W25Q80RVSNIQ:
        case _FLASH_MX25L25645G:

            // Read SR
            ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);

            if(ucRDSR != tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)
            {
                ScalerFlashSetWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, _FALSE);
                ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            }
            break;

        case _FLASH_SST25LF020A:

            // Read SR
            ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);

            if(ucRDSR != tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)
            {
                ScalerFlashSetWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, _TRUE);
                ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            }
            break;

        case _FLASH_GD25M21B:
        case _FLASH_GD25M41B:

            // Read SR
            ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);

            if(ucRDSR != tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)
            {
                // Sector Unlock Disable

                MCU_FF60_COMMON_INST_EN = 0x20;
                MCU_FF61_COMMON_OP_CODE = 0x4D;

                MCU_FF60_COMMON_INST_EN = 0x21;

                // polling until prog common instruction done
                while(((MCU_FF60_COMMON_INST_EN & _BIT0) == _BIT0) && (--usTimeOut > 0))
                {
                    DELAY_5US();
                }

                ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            }
            break;

        case _FLASH_W25Q32F:
        case _FLASH_GD25Q41B:
        case _FLASH_FM25Q08A:
        case _FLASH_FM25Q04:
        case _FLASH_W25Q16JVSIM:
        case _FLASH_W25Q32JVSIM:
        case _FLASH_W25Q16JVSIQ:
        case _FLASH_FM25Q08:
        case _FLASH_XT25F08B:
        case _FLASH_W25Q32JVSSIQ:
        case _FLASH_P25Q32H:
        case _FLASH_BY25Q80BSTIG:
        case _FLASH_AT25SF041B:
        case _FLASH_AT25SF081B:
        case _FLASH_AT25SF161B:
        case _FLASH_UC25HQ80IAT:
        case _FLASH_W25Q80BV:
        case _FLASH_GD25Q80B:
        case _FLASH_GD25Q40B:
        case _FLASH_W25Q16DV:
        case _FLASH_A25L032:
        case _FLASH_GD25Q16:
        case _FLASH_AT25SF041:
        case _FLASH_AT25SF321:
        case _FLASH_P25Q40H:
        case _FLASH_P25Q80H:
        case _FLASH_P25Q16H:
        case _FLASH_GD25VQ16C:
        case _FLASH_XM25QH80B:
        case _FLASH_XM25QH40B:
        case _FLASH_PY25Q80HB:
        case _FLASH_PY25Q128HA:
        case _FLASH_EN25QE16A:
        case _FLASH_EN25QE32A:
        case _FLASH_P25Q64SH:
        case _FLASH_GT25Q80A:
        case _FLASH_UC25HQ16:
        case _FLASH_GT25Q16A:
        case _FLASH_GT25Q40C:
        case _FLASH_GT25Q32AU:
        case _FLASH_PY25Q16HB:
        case _FLASH_PY25Q256HB:
        case _FLASH_UC25HD40I:
        case _FLASH_FM25Q32B:

            // Read SR
            ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);

            if(ucRDSR != tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)
            {
                ScalerFlashSet2ByteWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, 0x00, _FALSE);
                ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            }
            break;

        case _FLASH_FM25Q08B:
        case _FLASH_PY25Q40HB:

            // Read SR
            ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);

            if(ucRDSR != tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)
            {
                ScalerFlashSet2ByteWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, 0x00, _TRUE);
                ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            }
            break;

        case _FLASH_GD25Q32C:
        case _FLASH_ZB25VQ40A:
        case _FLASH_ZB25VQ80A:
        case _FLASH_ZB25VQ16A:
        case _FLASH_P25Q16SH:
        case _FLASH_GD25Q64E:
        case _FLASH_GD25Q128E:
        case _FLASH_AT25SF321B:
        case _FLASH_EN25QX64A:
        case _FLASH_EN25QX128A:
        case _FLASH_PY25Q64HA:
        case _FLASH_FM25Q16:
        case _FLASH_ZB25VQ16C:
        case _FLASH_XM25QH256C:
        case _FLASH_XM25QH64D:
        case _FLASH_FM25Q64A:
        case _FLASH_XM25QH128D:

            // Read SR
            ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);

            if(ucRDSR != tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)
            {
                ScalerFlashSet2ByteWRSRonebyone(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, 0x00, _FALSE);
                ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            }
            break;

        case _FLASH_W25Q128JVSQ:
        case _FLASH_W25Q64JVSIQ:
        case _FLASH_ZB25VQ64B:
        case _FLASH_XM25QH16C:
        case _FLASH_XM25QH32CHIGT:
        case _FLASH_BY25Q32CSSIG:

            // Read SR
            ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);

            if(ucRDSR != tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR)
            {
                ScalerFlashSet2ByteWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, 0x00, _WRITE_SR_MODE_SEL);
                ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            }
            break;

        case _FLASH_EN25Q40B:

            ScalerFlashSet5thWRSR(0x00, 0x00, _FALSE);
            ScalerFlashSetWRSR(tFlashInformation[g_ucNVRamFlashType].ucProtectWRSR, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucNVRamFlashType].ucWRDisOpCode);
            break;

        default:
            // Read SR
            ucRDSR = ScalerFlashReadSR(_RDSR_OPCODE);

            if(ucRDSR != 0xFF)
            {
                ScalerFlashSetWRSR(0xFF, _FALSE);
                ScalerFlashSetWREN(0x04);
            }
            break;
    }

    // Disable Program OP code
    MCU_FF6D_PROGRAM_OP_CODE = 0xFF;

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;
}

#endif // End of #if(_FLASH_WR_PROTECT ==_ON)
#endif // End of #if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))
