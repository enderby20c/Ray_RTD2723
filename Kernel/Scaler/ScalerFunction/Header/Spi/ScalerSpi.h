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
// ID Code      : ScalerSpi.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_SPI_H__
#define __SCALER_SPI_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SPI_TRANSACTION_FINISH_COUNT               (100)

#define _SPI_TX_BUFFER_MAX_LENGTH                   (16)
#define _SPI1_RX_BUFFER_MAX_LENGTH                  (4)
#define _SPI2_RX_BUFFER_MAX_LENGTH                  (4)

#define GET_BROADCAST_PWM_START_ADDRESS()           (tLedSpiPwmStartAddr[0])

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(((_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX == _ON) && (_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_ALIGN_DVS == _ON)) ||\
    ((_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX == _OFF) && (_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)))
#define GET_SMODE_UPDSYNC_MANUAL_APPLY_TIMING()     (_SMODE_UPDSYNC_NEXT_1_DVS)
#else
#define GET_SMODE_UPDSYNC_MANUAL_APPLY_TIMING()     (_SMODE_UPDSYNC_IMMEDIATE)
#endif
#endif

#define LOCAL_DIMMING_SPI_READ_CMD_HEADER_LEN(x)    (_DEVICE_LED_DRIVER_READ_DUMMY_BYTE_NUM + (((x) - 1) * _LOCAL_DIMMING_PWM2SPI_DUMMY_WIDTH_BY_BYTE) + _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_SPI_SUPPORT == _ON)
#if(_SPI0_SUPPORT == _ON)
extern void ScalerSpi0Initial(void);
extern void ScalerSpi0SetCS(EnumSpiCsState enumSpiCsState);
extern bit ScalerSpi0CommonProcess(BYTE ucTxRxBufIndex, BYTE ucWriteLength, BYTE ucReadLength, WORD usOffsetIndex, BYTE *pucWriteBuf);
#endif

#if(_SPI1_SUPPORT == _ON)
extern void ScalerSpi1Initial(void);
extern void ScalerSpi1SetCS(EnumSpiCsState enumSpiCsState);
extern bit ScalerSpi1CommonProcess(BYTE ucTxRxBufIndex, BYTE ucWriteLength, BYTE ucReadLength, WORD usOffsetIndex, BYTE *pucWriteBuf);
#endif

#if(_SPI2_SUPPORT == _ON)
extern void ScalerSpi2Initial(void);
extern void ScalerSpi2SetCS(EnumSpiCsState enumSpiCsState);
extern bit ScalerSpi2CommonProcess(BYTE ucTxRxBufIndex, BYTE ucWriteLength, BYTE ucReadLength, WORD usOffsetIndex, BYTE *pucWriteBuf);
#endif
#endif // End of #if(_SPI_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_SPI_H__
