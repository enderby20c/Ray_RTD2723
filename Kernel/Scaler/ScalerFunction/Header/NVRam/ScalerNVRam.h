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
// ID Code      : ScalerNVRam.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_NVRAM_H__
#define __SCALER_NVRAM_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _RDSR_OPCODE                                   0x05
#define _RDSR2_OPCODE                                  0x35
// _RDSR3_OPCODE Same With _RDCR_OPCODE
#define _RDCR_OPCODE                                   0x15
#define _RDSR4_OPCODE                                  0x45
#define _RDSR5_OPCODE                                  0x85
#define _ENTER_OTP_OPCODE                              0x3A
#define _EXIT_OTP_OPCODE                               0x04

#define _WRITE_SR_MODE_SEL                             (_FLASH_EWSR_FUNCTION_SUPPORT == _ON)

#define _FLASH_COMMON_INST_POLLING_TIME                2000

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))

extern bit ScalerFlashReadFlashIDCode(BYTE ucRDIDOPCode, BYTE *pucIDArry);
extern void ScalerFlashSetWREN(BYTE ucOpCode);
extern void ScalerFlashSetWRSR(BYTE ucWRSR, bit bIsSST);
extern void ScalerFlashSet2ByteWRSR(BYTE ucWRSR1, BYTE ucWRSR2, bit bIsSST);
extern void ScalerFlashSet2ByteWRSRonebyone(BYTE ucWRSR1, BYTE ucWRSR2, bit bIsSST);
extern void ScalerFlashSet5thWRSR(BYTE ucWRSR, BYTE ucCheckBit, bit bIsSST);

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern bit ScalerFlashErasePageMainProcess(WORD usBank, BYTE ucPage, bit bEnFlashSR, bit bDisFlashSR);
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
extern bit ScalerFlashWriteSecondaryProcess(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData, bit bEnFlashSR, bit bDisFlashSR);
#endif

extern void ScalerFlashSet2ndWRSR(BYTE ucWRSR, bit bIsSST);
extern void ScalerFlashSet3rdWRSR(BYTE ucWRSR, BYTE ucCheckBit, bit bIsSST);
extern void ScalerFlashSet4thWRSR(BYTE ucWRSR, BYTE ucCheckBit, bit bIsSST);
extern BYTE ScalerFlashReadSROnOTPMode(BYTE ucEnterOTPOpCode, BYTE ucExitOTPOpCode, BYTE ucOpCode);

#if(_FLASH_TOP_BOTTOM_PROTECT_SELECT == _FLASH_BOTTOM_PROTECT)
extern void ScalerFlashSetWRSROnOTPMode(BYTE ucEnterOTPOpCode, BYTE ucExitOTPOpCode, BYTE ucWRSR, bit bIsSST);
#endif // End of #if(_FLASH_TOP_BOTTOM_PROTECT_SELECT == _FLASH_BOTTOM_PROTECT)

#endif // End of #if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)

extern BYTE ScalerFlashReadSR(BYTE ucOpCode);
#endif // End of #if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))

#endif // End of #ifndef __SCALER_NVRAM_H__
