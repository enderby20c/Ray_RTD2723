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
// ID Code      : ScalerNVRamInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define FLASH_GET_BYTE(ul32bAddr)       (*((volatile BYTE *)(ul32bAddr)))

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
#define GET_POL_FLASH_ADDR_MODE()       ((MCU_FF77_REV_DUMMY4 & _BIT4) == _BIT4)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerFlashRead(WORD usBank, BYTE *pucAddress, WORD usLength, BYTE *pucData);
extern DWORD ScalerNVRamGetFlashBankOffset(void);

#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
extern bit ScalerFlashWrite(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData);
extern bit ScalerFlashWriteByKernel(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData, bit bEnFlashSR, bit bDisFlashSR);

extern bit ScalerFlashErasePage(WORD usBank, BYTE ucPage, bit bEnFlashSR, bit bDisFlashSR);
extern void ScalerFlashWREN(WORD usBank, BYTE ucPage);
extern void ScalerFlashWRDis(void);
#if((_BILLBOARD_SUPPORT == _ON) || (_FW_UPDATE_PROCESS_SUPPORT == _ON) || (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
extern bit ScalerFlashEraseBank(WORD usBank, bit bEnFlashSR, bit bDisFlashSR);
extern bit ScalerFlashWritePageProgram(WORD usBank, WORD usAddr, WORD usLength, bit bEnFlashSR, bit bDisFlashSR);
#endif
#endif

#if(_FLASH_WR_PROTECT == _ON)
extern void ScalerFlashWRProtect(void);
#endif
#endif // End of #if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))

