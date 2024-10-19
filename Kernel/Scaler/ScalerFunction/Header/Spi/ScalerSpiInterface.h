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
// ID Code      : ScalerSpiInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SPI0_RX_BUFFER_MAX_LENGTH                  (4)


#define _MAX_SPI_DEV_NUM                            (MAXOF3(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM))

#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
#define _USE_SPI_INTERFACE_NUM                      (3)
#elif(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
#define _USE_SPI_INTERFACE_NUM                      (2)
#else
#define _USE_SPI_INTERFACE_NUM                      (1)
#endif

#define _MAX_SRAM_DATA_BYTE_SIZE                    (4976)
#define _MAX_CMD_ENTRY_NUM                          (76)

#define _SMODE_VALID_CMD_ENTRY_SEL_01               (0)
#define _SMODE_VALID_CMD_ENTRY_SEL_23               (1)

#define GEN_SPI_CMD_ENTRY_CFG(ucStartIdx, ucCmdNum) (((DWORD)(ucCmdNum) << 16) | (ucStartIdx))

#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)
#if((_DEVICE_LED_DRIVER_SPI0_VALID_CMD_ENTRY_SEL == _SMODE_VALID_CMD_ENTRY_SEL_23) ||\
    (_DEVICE_LED_DRIVER_SPI1_VALID_CMD_ENTRY_SEL == _SMODE_VALID_CMD_ENTRY_SEL_23) ||\
    (_DEVICE_LED_DRIVER_SPI2_VALID_CMD_ENTRY_SEL == _SMODE_VALID_CMD_ENTRY_SEL_23))
#define _VALID_BY_SPI_USE_CMD_ENTRY_NUM             (4)
#else
#define _VALID_BY_SPI_USE_CMD_ENTRY_NUM             (2)
#endif
#else
#define _VALID_BY_SPI_USE_CMD_ENTRY_NUM             (0)
#endif

#define _MAX_SRAM_SPI_UPDSYNC_CMD_SIZE              ((_DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES + 2) * _VALID_BY_SPI_USE_CMD_ENTRY_NUM)
#define _MAX_SPI_ONCE_CMD_BYTE_NUM                  (_DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES + _LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM + _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM)
#define _MAX_USABLE_PWM_CMD_ENTRY_NUM               (_MAX_CMD_ENTRY_NUM - _VALID_BY_SPI_USE_CMD_ENTRY_NUM)

#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#define _MAX_POSSIBLE_SPI_ONCE_PWM_CMD_NUM          ((_MAX_SRAM_DATA_BYTE_SIZE - _MAX_SRAM_SPI_UPDSYNC_CMD_SIZE) / _MAX_SPI_ONCE_CMD_BYTE_NUM)
#define _MAX_SPI_ONCE_TX_CMD_NUM                    (((MINOF(_MAX_POSSIBLE_SPI_ONCE_PWM_CMD_NUM, _MAX_USABLE_PWM_CMD_ENTRY_NUM)) / 2) / _USE_SPI_INTERFACE_NUM)  // div by 2 for pin-pong usage
#else
#define _MAX_POSSIBLE_SPI_ONCE_PWM_CMD_NUM          ((_MAX_SRAM_DATA_BYTE_SIZE - _MAX_SRAM_SPI_UPDSYNC_CMD_SIZE) / (_MAX_SPI_ONCE_CMD_BYTE_NUM * _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME))
#define _MAX_SPI_ONCE_TX_CMD_NUM                    (MAXOF3(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM))
#endif

#define _MAX_SPI_ONCE_TX_BUF_SIZE                   ((((_MAX_SPI_ONCE_CMD_BYTE_NUM * _MAX_SPI_ONCE_TX_CMD_NUM) + 31) / 32) * 32)
#define _MAX_SPI0_TX_TIMES                          ((_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + (_MAX_SPI_ONCE_TX_CMD_NUM - 1)) / _MAX_SPI_ONCE_TX_CMD_NUM)
#define _MAX_SPI1_TX_TIMES                          ((_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM + (_MAX_SPI_ONCE_TX_CMD_NUM - 1)) / _MAX_SPI_ONCE_TX_CMD_NUM)
#define _MAX_SPI2_TX_TIMES                          ((_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM + (_MAX_SPI_ONCE_TX_CMD_NUM - 1)) / _MAX_SPI_ONCE_TX_CMD_NUM)
#define _MAX_PWM2SPI_SMODE_REUSE_TIMES              (MAXOF3(_MAX_SPI0_TX_TIMES, _MAX_SPI1_TX_TIMES, _MAX_SPI2_TX_TIMES))

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)

#if(_DEVICE_LED_DRIVER_PWM_MAX < (1UL << 12))
#define _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT      0
#elif(_DEVICE_LED_DRIVER_PWM_MAX < (1UL << 13))
#define _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT      1
#elif(_DEVICE_LED_DRIVER_PWM_MAX < (1UL << 14))
#define _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT      2
#elif(_DEVICE_LED_DRIVER_PWM_MAX < (1UL << 15))
#define _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT      3
#else
#define _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT      4
#endif

#define _LOCAL_DIMMING_PWM2SPI_PWM_GAIN_CALC        (((((_DEVICE_LED_DRIVER_PWM_MAX - _LOCAL_DIMMING_PWM2SPI_PWM_MIN) >> _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT) * 4096) + 2047) / 4095)


#define _LOCAL_DIMMING_PWM2SPI_PWM_GAIN_VALUE       ((_LOCAL_DIMMING_PWM2SPI_PWM_GAIN_CALC > 0xFFF) ? 0xFFF : ((((((4095 * (_LOCAL_DIMMING_PWM2SPI_PWM_GAIN_CALC + 1)) / 4096) + _LOCAL_DIMMING_PWM2SPI_PWM_MIN) << _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT) > _DEVICE_LED_DRIVER_PWM_MAX) ? (_LOCAL_DIMMING_PWM2SPI_PWM_GAIN_CALC - 1) : _LOCAL_DIMMING_PWM2SPI_PWM_GAIN_CALC))

#define _LOCAL_DIMMING_SPI_CMD_MAX_LENGTH           (_DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES + _LOCAL_DIMMING_PWM2SPI_APPEND_NUM_OF_BYTES + _LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM + _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM + _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM)

#define _LOCAL_DIMMING_SPI0_READ_CMD_HEADER_LEN     (LOCAL_DIMMING_SPI_READ_CMD_HEADER_LEN(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM))
#define _LOCAL_DIMMING_SPI1_READ_CMD_HEADER_LEN     (LOCAL_DIMMING_SPI_READ_CMD_HEADER_LEN(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM))
#define _LOCAL_DIMMING_SPI2_READ_CMD_HEADER_LEN     (LOCAL_DIMMING_SPI_READ_CMD_HEADER_LEN(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM))
#define _LOCAL_DIMMING_MAX_SPI_READ_CMD_HEADER_LEN  (_DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES + MAXOF3(_LOCAL_DIMMING_SPI0_READ_CMD_HEADER_LEN, _LOCAL_DIMMING_SPI1_READ_CMD_HEADER_LEN, _LOCAL_DIMMING_SPI2_READ_CMD_HEADER_LEN))
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HW_CPU32_BW32_SUPPORT == _ON)
__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
typedef struct
{
    BYTE pucSpiSRamBuf[(_MAX_SPI_ONCE_TX_BUF_SIZE * _USE_SPI_INTERFACE_NUM)];
}StructSpiSRamBuf;

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
typedef struct
{
    DWORD pulSpiCmdEntryData[((((_MAX_SPI_ONCE_TX_CMD_NUM * _USE_SPI_INTERFACE_NUM) + 7) / 8) * 8)];
}StructSpiCmdEntryData;

__attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
typedef struct
{
    DWORD pulSpiCmdEntryDummyBytes[((((((_MAX_SPI_ONCE_TX_CMD_NUM * _USE_SPI_INTERFACE_NUM) + 3) / 4) + 7) / 8) * 8)];
}StructSpiCmdEntryDummyBytes;
#else
typedef struct
{
    BYTE pucSpiSRamBuf[((((_MAX_SPI_ONCE_TX_BUF_SIZE * _USE_SPI_INTERFACE_NUM) + 3) / 4) * 4)];
}StructSpiSRamBuf;

typedef struct
{
    DWORD pulSpiCmdEntryData[((((_MAX_SPI_ONCE_TX_CMD_NUM * _USE_SPI_INTERFACE_NUM) + 7) / 8) * 8)];
}StructSpiCmdEntryData;

typedef struct
{
    DWORD pulSpiCmdEntryDummyBytes[((((((_MAX_SPI_ONCE_TX_CMD_NUM * _USE_SPI_INTERFACE_NUM) + 3) / 4) + 7) / 8) * 8)];
}StructSpiCmdEntryDummyBytes;
#endif

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
typedef enum
{
    _SPI_DEBUG_OTHER_REG = 0,
    _SPI_DEBUG_PWM_REG,
} EnumSpiDebugRWDest;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_SPI_SUPPORT == _ON)

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern WORD code tLDPwmToSpiDevAddr[];
extern WORD code tLDPwmToSpiDataByteNum[];
extern WORD code tLDPwmToSpiPwmStartAddr[];
extern BYTE code tLDPwmToSpiDummyByteNum[];
extern WORD code tLDPwmToSpiRemapTable0[];
extern WORD code tLDPwmToSpiRemapTable1[];
extern WORD code tLedSpiDevAddr[];
extern WORD code tLedSpiPwmStartAddr[];
extern WORD code tLedSpiDataByteNum[];
extern BYTE code tLedSpiDummyByteNum[];

extern StructPwmToSpiInfo g_stSpiDimmingPwmToSpiInfo;
extern volatile bit g_bSpiDimmingSramModeStartTxResult;
extern volatile bit g_bSpiDimmingSramModeTxDoneFlag;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_SPI_SUPPORT == _ON)
extern void ScalerSpiConfigSetting(StructSpiConfigInfo *pstSpiConfigInfo);
extern void ScalerSpiSclkSel(EnumClkSel enumClock);

#if(_SPI0_SUPPORT == _ON)
extern void ScalerSpi0Reset(void);
extern bit ScalerSpi0DataIo(WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray);
extern void ScalerSpi0CSPinSel(EnumSpiCsSel enumSpiCsSel);
#endif

#if(_SPI1_SUPPORT == _ON)
extern void ScalerSpi1Reset(void);
extern bit ScalerSpi1DataIo(WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray);
extern void ScalerSpi1CSPinSel(EnumSpiCsSel enumSpiCsSel);
#endif

#if(_SPI2_SUPPORT == _ON)
extern void ScalerSpi2Reset(void);
extern bit ScalerSpi2DataIo(WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray);
extern void ScalerSpi2CSPinSel(EnumSpiCsSel enumSpiCsSel);
#endif

extern bit ScalerSpiDataIo(EnumSpiInterface enumSpiInterface, WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray);
extern void ScalerSpiSetPinConfigForPowerState(EnumSpiInterface enumSpiInterface, EnumPowerTarget enumPowerTarget);

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern void ScalerSpiDimmingSetSpiHwToLD(void);
extern bit ScalerSpiDimmingBaseWrite(EnumPwmToSpiInterface enumPwmToSpiInterface, bit bUseDevIndex, WORD usDevIdxOrBcId, WORD usSpiStartAddr, WORD usSpiWriteByteNum, BYTE *pucWriteBuffer, bit bBypassUpdSyncAsCS, WORD usPwmAllZoneValue);
extern void ScalerSpiDimmingInit(void);
extern bit ScalerSpiDimmingRegRead(EnumPwmToSpiInterface enumPwmToSpiInterface, BYTE ucDevIndex, WORD usSpiStartAddr, BYTE ucSpiReadByteNum, BYTE *pucReadBuffer);
extern bit ScalerSpiDimmingRegWrite(EnumPwmToSpiInterface enumPwmToSpiInterface, WORD usDevIndex, WORD usSpiStartAddr, WORD usSpiWriteByteNum, BYTE *pucWriteBuffer);
extern bit ScalerSpiDimmingRegWriteAll(WORD usSpiStartAddr, WORD usSpiWriteByteNum, BYTE *pucWriteBuffer, WORD usPwmAllZoneValue);
extern bit ScalerSpiDimmingDebugWriteReg(BYTE ucDevIndex, WORD usRegStartAddr, WORD usWriteRegNum, WORD *pusRegValue, EnumSpiDebugRWDest enumSpiDebugRWDest);
extern bit ScalerSpiDimmingDebugReadReg(BYTE ucDevIndex, WORD usRegStartAddr, WORD usReadRegNum, WORD *pusRegValue, EnumSpiDebugRWDest enumSpiDebugRWDest);

extern void ScalerSpiDimmingToggleUpdateSync(void);
extern bit ScalerSpiDimmingSetPwmValueToAllZone(WORD usPwmValue);

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
extern void ScalerSpiDimmingScpuSyncHandler(void);
#endif
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
extern void ScalerSpiDimmingLDUpdateSramModeData(WORD *pusPwmTargetBuf, WORD *pusPwmPrevTargetBuf, WORD *pusPwmAdjustCurve, bit bPwm2SpiTxNow);
extern bit ScalerSpiDimmingLDSramModeStartTX(void);
extern void ScalerSpiDimmingLDSramModeTxNow(void);

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
extern void ScalerSpiDimmingLDUpdateSramADimData(WORD *pusColorApplyADim, bit bPwm2SpiTxNow);
extern void ScalerSpiDimmingLDSramModeADimTxNow(void);
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
extern void ScalerSpiDimmingLocalDimmingRegionBoostAdjust(WORD *pusBoostGainData, WORD *pusBoostGainRemap);
#endif

#endif
#endif

#if(_SPI0_SUPPORT == _ON)
extern bit ScalerSpiData(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf);
extern bit ScalerSpiSPIDataCeForceLow(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf);
#endif

#endif
