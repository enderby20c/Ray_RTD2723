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
// ID Code      : ScalerSpiInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_SPI_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)

#if(_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP == _ON)
#if(_SPI0_SUPPORT == _ON)
#define MAP_SPI_OUTPUT_INTERFACE(enumPwmToSpiInterface) ((((enumPwmToSpiInterface) == _PWMTOSPI_INTERFACE_0) ? (_SPI_INTERFACE_1) : (_SPI_INTERFACE_0)))
#else
#define MAP_SPI_OUTPUT_INTERFACE(enumPwmToSpiInterface) (_SPI_INTERFACE_1)
#endif
#else
#if(_SPI1_SUPPORT == _ON)
#define MAP_SPI_OUTPUT_INTERFACE(enumPwmToSpiInterface) ((((enumPwmToSpiInterface) == _PWMTOSPI_INTERFACE_0) ? (_SPI_INTERFACE_0) : (_SPI_INTERFACE_1)))
#else
#define MAP_SPI_OUTPUT_INTERFACE(enumPwmToSpiInterface) (_SPI_INTERFACE_0)
#endif
#endif

#endif

#define MAXOF3_REMAP_TABLE(tbl0, tbl1, tbl2)            (MAXOF3(GET_TABLE_ELEMENT_NUM(tbl0),\
                                                                GET_TABLE_ELEMENT_NUM(tbl1),\
                                                                GET_TABLE_ELEMENT_NUM(tbl2)))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _SPI_CONTROL_BY_MCU = 0,
    _SPI_CONTROL_BY_PWM2SPI,
} EnumSpiControlSrc;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerSpiInitial(void);

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern void ScalerSpiDimmingSetSpiCtrlSrc(EnumSpiControlSrc enumSpiControlSrc, EnumSpiInterface enumSpiOutputInterface);
extern bit ScalerSpiDimmingGetPwmRemapInfo(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmNum, WORD *pusPwmRemapInfo);
extern bit ScalerSpiDimmingDebugWritePWM(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmWriteNum, WORD *pusPwmValue);
extern bit ScalerSpiDimmingDebugReadPWM(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmReadNum, WORD *pusPwmValue);
extern WORD ScalerSpiDimmingGetTableIndex(EnumPwmToSpiInterface enumPwmToSpiInterface, BYTE ucSpiDevIdx);
extern WORD ScalerSpiDimmingFormatWriteCmdBuffer(EnumPwmToSpiInterface enumPwmToSpiInterface, bit bUseDevIndex, WORD usDevIdxOrBcId, WORD usSpiStartAddr, BYTE *pucPayLoadBuffer, WORD usPayloadBufferSize, BYTE *pucCmdBuffer, WORD usCmdBufferSize, bit bAppendDummyByte, WORD usPwmAllZoneValue);
extern WORD ScalerSpiDimmingFormatReadCmdBuffer(EnumPwmToSpiInterface enumPwmToSpiInterface, BYTE ucDevIndex, WORD usSpiStartAddr, WORD usSpiReadByteNum, BYTE *pucDataBuffer, WORD usDataBufferSize);

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern void ScalerSpiDimmingSyncInit(EnumUpdSyncTriggerSrc enumUpdSyncTriggerSrc);
extern bit ScalerSpiDimmingSyncBaseWrite(EnumPwmToSpiInterface enumPwmToSpiInterface, bit bUseDevIndex, WORD usDevIdxOrBcId, WORD usSpiStartAddr, WORD usSpiWriteByteNum, BYTE *pucWriteBuffer, bit bBypassUpdSyncAsCS, WORD usPwmAllZoneValue);
extern bit ScalerSpiDimmingSyncDebugReadMcuPwm(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmReadNum, WORD *pusPwmValue);
extern bit ScalerSpiDimmingSyncDebugWriteMcuPwm(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmWriteNum, WORD *pusPwmValue);
#endif
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
extern bit ScalerSpiDimmingScpuSyncInit(void);
extern bit ScalerSpiDimmingScpuSyncBaseWrite(void);
extern bit ScalerSpiDimmingScpuSyncMemcpy(void);
extern bit ScalerSpiDimmingScpuSyncReadMcuPwm(void);
extern bit ScalerSpiDimmingScpuSyncWriteMcuPwm(void);
#endif
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME > 1)
extern void ScalerSpiDimmingLDManualApplyUpdSync(void);
#endif
extern void ScalerSpiDimmingLDSramModeSpiTxDoneCallBack(void);
#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)
extern void ScalerSpiDimmingLDSramModeUpdSyncUseSpiInit(void);
#endif
#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE)
extern void ScalerSpiDimmingInitUseDdr(void);
extern void ScalerSpiDimmingLDUpdateSramModeDataUseDdr(WORD *pusPwmTargetBuf, WORD *pusPwmPrevTargetBuf, WORD *pusPwmAdjustCurve);
#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
extern void ScalerSpiDimmingLDUpdateSramADimDataUseDdr(WORD *pusColorApplyADim);
#endif
extern void ScalerSpiDimmingLDSramModeInitBW32CmdInfo(StructBW32CmdInfo *pstBW32CmdInfo);
extern void ScalerSpiDimmingLDSramModeSpiTx(void);
extern void ScalerSpiDimmingLDSramModeNextBW32(void);
extern void ScalerSpiDimmingLDSramModeBW32DoneCallBack(void);
#endif
#else
extern void ScalerSpiDimmingInitUseSram(void);
extern void ScalerSpiDimmingLDUpdateSramModeDataUseSram(WORD *pusPwmTargetBuf, WORD *pusPwmPrevTargetBuf, WORD *pusPwmAdjustCurve);
#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
extern void ScalerSpiDimmingInitADimUseSram(void);
extern void ScalerSpiDimmingLDUpdateSramADimDataUseSram(WORD *pusColorApplyADim);
#endif
#endif
#endif
#endif

#endif
