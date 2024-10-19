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
// ID Code      : ScalerDebug.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DEBUG_H__
#define __SCALER_DEBUG_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DEBUG_DEST_ADDRESS                       0x6A
#define _DATA_OUT_COUNT                           0x05

#define _SCALER_DEBUG_DATA_COUNT                  0x18
#define _SCALER_DEBUG_BUF_LEN                     (_SCALER_DEBUG_DATA_COUNT + 8)

// Scaler Command Define
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
#define _SCALER_WRITE_PWMTOSPI_WORD_CMD           0x96
#define _SCALER_READ_PWMTOSPI_WORD_CMD            0x97
#define _SCALER_WRITE_PWMTOSPI_WORD_DEV_CMD       0x98
#define _SCALER_READ_PWMTOSPI_WORD_DEV_CMD        0x99
#define _SCALER_WRITE_PWMTOSPI_REG_CMD            0x9A
#define _SCALER_READ_PWMTOSPI_REG_CMD             0x9B
#define _SCALER_WRITE_PWMTOSPI_DEV_CMD            0x9C
#define _SCALER_READ_PWMTOSPI_DEV_CMD             0x9D
#endif

#define _SCALER_WRITE_32BITSREGISTERS_CMD         0xAA
#define _SCALER_READ_32BITSREGISTERS_CMD          0xAB

#define _SCALER_WRITE_DDRSPACE_CMD                0xAC
#define _SCALER_READ_DDRSPACE_CMD                 0xAD

#define _SCALER_WRITE_REGISTERS_CMD               0xBA
#define _SCALER_READ_REGISTERS_CMD                0xBB

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
#define _SCALER_DUAL_BANK_SWITCH_DDCCI_MODE_CMD   0x71
#endif
#define _SCALER_GET_CURRENT_FW_VER_CMD            0xC9
#define _SCALER_DUAL_BANK_BOOT_PROC_CMD           0xCA

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
#define _SCALER_CUSTOMER_DEBUG_PROC_CMD           0xCC
#endif

// Error code
#define _SCALER_DEBUG_NO_ERROR                    0x00
#define _SCALER_DEBUG_DATA_LEN_ERROR              0xE1
#define _SCALER_DEBUG_CHECKSUM_ERROR              0xE2
#define _SCALER_DEBUG_SET_SPI_DEV_ERROR           0xE3
#define _SCALER_DEBUG_GET_SPI_DEV_ERROR           0xE4
#define _SCALER_DEBUG_SET_SPI_REG_ERROR           0xE5
#define _SCALER_DEBUG_GET_SPI_REG_ERROR           0xE6

#define _SCALER_GET_CURRENT_FW_VERSION_OP_CODE    0x01
#define _SCALER_GET_FW_VERSION_LOCATE_OP_CODE     0x02
#define _SCALER_GET_DUAL_BANK_INFO_OP_CODE        0x09

#define _WAIT_DBG_MSG_TIMEOUT                     (500 * 100)   // (500ms * 100) * 10us
#define _DATA_OUT_COUNT                           0x05
#define _DBG_MSG_CIRCULAR_QUEUE_SIZE              512

#define CHK_ADDRESS_ACCESSIBLE(ulTargetAddr)      ((((ulTargetAddr) >= GET_XDATA_REG_32BIT_ADDR(PFD_D0_EMCU_TO32B_INF_GRP0_A3)) && ((ulTargetAddr) <= GET_XDATA_REG_32BIT_ADDR(PFD_EB_EMCU_TO32_INF_DUMMY2))) ? _FALSE : _TRUE)


#if((_PROMOTE_DDC_INT_TO_HW4_INT_LVL == _OFF) &&\
    ((_IS_MAIN_PROCESS_CPU == _TRUE) ||\
    ((_IS_MAIN_PROCESS_CPU == _FALSE) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))))
#define SKIP_DBG_IN_INTERRUPT()                   (CPU32_IS_INSIDE_INTERRUPT())
#else
#define SKIP_DBG_IN_INTERRUPT()                   (_FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile BYTE g_pucDebugDdcciData[_SCALER_DEBUG_BUF_LEN];
extern volatile BYTE g_ucDebugDdcciCommandNumber;

extern EnumDDCCIDebugMode g_enumDebugDdcciMode;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern volatile WORD g_usDebugFilterPro;
extern volatile bit g_bDebugFwHalt;
extern bit g_bDebugMessageStart;
extern BYTE idata g_pucDebugMessageBUF[4];
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDebugGetRegisters(void);
extern void ScalerDebugSetRegisters(void);

extern void ScalerDebugGet32BitRegisters(BYTE ucDebugCmd);
extern void ScalerDebugSet32BitRegisters(BYTE ucDebugCmd);

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
extern void ScalerDebugGetCurrentFwInfo(void);
#endif
extern void ScalerDebugDualBankHandler(BYTE ucSubCode);

#if(_SPI_SUPPORT == _ON)
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern void ScalerDebugGetPwmToSpiDevice(void);
extern void ScalerDebugSetPwmToSpiDevice(void);
extern void ScalerDebugGetPwmToSpiRegisters(void);
extern void ScalerDebugSetPwmToSpiRegisters(void);
extern void ScalerDebugGetPwmToSpiDeviceGen2(void);
extern void ScalerDebugSetPwmToSpiDeviceGen2(void);
extern void ScalerDebugGetPwmToSpiRegistersGen2(void);
extern void ScalerDebugSetPwmToSpiRegistersGen2(void);
#endif
#endif

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
extern void ScalerDebugCustomerDebugProc(void);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern void ScalerDebugMessageProcess(SBYTE *pchMessage, DWORD ulValue);
#endif

#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
extern void ScalerDebugFwCheck(void);
#endif


#endif // End of #ifndef __SCALER_DEBUG_H__
