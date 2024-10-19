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
// ID Code      : RL6952_Series_McuMemLayout.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// 16B_SCALER_IP
#define _XDATA_16B_SCALER_IP_B_ADDR             0x0000
#define _XDATA_16B_SCALER_IP_E_ADDR             0xFFFF

// Peripheral and SRAM base address
#define _SHARE_RAM_B_ADDRESS                    (0xA0100000)
#define _SHARE_RAM_E_ADDRESS                    (0xA0105FFF)
#define _DEVICE_16BXRAM_BASE_ADDR               _SHARE_RAM_B_ADDRESS
#define _KCPU_FLASH_BASE_ADDR                   (0x86000000)
#define _KCPU_FLASH_MAX_ADDR                    (0x8FFFFFFF)
#define _KCPU_DDR_BASE_ADDR                     (0xC0000000)
#define _KCPU_DDR_MAX_ADDR                      (0xCFFFFFFF)


#define _DEVICE_16BSCALERIP_BASE_ADDR           (0xA0000000)    // (16bits ScalerIP Mapping) Base Address
#define _DEVICE_PERIPHERAL_BASE_ADDR            (0xA2000000)    // (Peripheral) Base Address
#define _DEVICE_CPU1_BASE_ADDR                  (0xA3000000)    // (CPU1 specific) Base Address
#define _DEVICE_CPU2_BASE_ADDR                  (0xA4000000)    // (CPU2 specific) Base Address
#define _DEVICE_32BSCALERIP_BASE_ADDR           (0xB0000000)    // (CPU2 specific) Base Address
#define _DEVICE_32BSCALERIP_MAX_ADDR            (0xBEFFFFFF)    // 32bits ScalerIP Max Address

#define _ROM_CODE_BASE_ADDR                     (0xBFC00000)    // ROM Code Base Address
#define _ROM_CODE_MAX_ADDR                      (0xBFFFFFFF)    // ROM Code Max Address

// Xdata Reg Address Mapping
#define GET_XDATA_REG_16BIT_ADDR(ulAddr)        ((WORD)(((DWORD)(ulAddr) - _DEVICE_16BSCALERIP_BASE_ADDR) >> 2))
#define GET_XDATA_REG_32BIT_ADDR(usAddr)        (((DWORD)(usAddr) << 2) + _DEVICE_16BSCALERIP_BASE_ADDR)

#define GET_KCPU_FLASH_BANK_OFFSET()            ((DWORD)Scaler32GetDWord(PA40010_50_MIPS_CPU1_FLASH_BANK_OFFSET) << 16)

// XRAM Address Mpping
#define GET_PHY_XRAM_ADDR(ulXramAddr)           ((ulXramAddr) - _DEVICE_16BXRAM_BASE_ADDR)


#if(_CPU32_IP == _CPU32_IP_RX3081)
// KCPU::RX3081

// IMEM and DMEM
#define _ITCM_B_ADDRESS                         (0x85000000)
#define _ITCM_E_ADDRESS                         (0x85000FFF)
#define _DTCM_B_ADDRESS                         (0xA5100000)
#define _DTCM_E_ADDRESS                         (0xA5101FFF)
// Flash Address Mapping
#define _DEVICE_FLASH_BASE_ADDR                 _KCPU_FLASH_BASE_ADDR
#define GET_FLASH_BANK_OFFSET()                 (GET_KCPU_FLASH_BANK_OFFSET())
#endif

#define GET_DDCRAM_POINTER(ulAddr)              ((BYTE *)(ulAddr))

#if(_FW_CPU32_USE_INT31_FOR_SCALER_INT == _ON)
#define _IRQ_MASK_SCALER_ALL_UNION              (_IRQ_MASK_SCALER_OTHER | _IRQ_MASK_SCALER_ERROR | _IRQ_MASK_SCALER_ALL)
#else
#define _IRQ_MASK_SCALER_ALL_UNION              (_IRQ_MASK_SCALER_OTHER | _IRQ_MASK_SCALER_ERROR | (_IRQ_MASK_IMD_EVENT | _IRQ_MASK_TX | _IRQ_MASK_VGA | _IRQ_MASK_MST_MSG | _IRQ_MASK_DP_HIGH | _IRQ_MASK_DP_LOW | _IRQ_MASK_HDMI_HIGH | _IRQ_MASK_HDMI_LOW))
#endif

#define _SCALER_ALL_IRQ_UNION_NUM               (10)

#define _IRQ_MASK_PDCC_UNION                    (_IRQ_MASK_PDCC_HIGH | _IRQ_MASK_PDCC_LOW)

#define _IRQ_MASK_TCPM                          (0)

#define _IRQ_MASK_DP_RX_UNION                   (_IRQ_MASK_TX | _IRQ_MASK_MST_MSG | _IRQ_MASK_DP_HIGH | _IRQ_MASK_DP_LOW)

//--------------------------------------------------
// ScalerGetByte / ScalerSetByte
//--------------------------------------------------
#define SCALER32_GET_XDATA_REG(usAddr)          (*((volatile BYTE *)(GET_XDATA_REG_32BIT_ADDR((usAddr)))))
#define SCALER32_SET_XDATA_REG(usAddr, ucValue) (*((volatile BYTE *)(GET_XDATA_REG_32BIT_ADDR((usAddr)))) = ((BYTE)(ucValue)))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

