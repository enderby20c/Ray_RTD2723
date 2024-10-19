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
// ID Code      : ScalerSpiDimming.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Spi/ScalerSpi.h"

#if(_SPI_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)

WORD code tLDPwmToSpiDevAddr[] =
{
#include _LOCAL_DIMMING_PWM2SPI_DEV_ADDR
};

WORD code tLDPwmToSpiDataByteNum[] =
{
#include _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_NUM
};

WORD code tLDPwmToSpiPwmStartAddr[] =
{
#include _LOCAL_DIMMING_PWM2SPI_PWM_START_ADDR
};

BYTE code tLDPwmToSpiDummyByteNum[] =
{
#include _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_NUM
};

WORD code tLDPwmToSpiRemapTable0[] =
{
#include _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE0
};

WORD code tLDPwmToSpiRemapTable1[] =
{
#include _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE1
};

WORD code tLDPwmToSpiRemapTable2[] =
{
#include _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE2
};

WORD code tLedSpiDevAddr[] =
{
#include _LED_SPI_DEV_ADDR
};

WORD code tLedSpiPwmStartAddr[] =
{
#include _LED_SPI_PWM_START_ADDR
};

WORD code tLedSpiDataByteNum[] =
{
#include _LED_SPI_DATA_BYTE_NUM
};

BYTE code tLedSpiDummyByteNum[] =
{
#include _LED_SPI_DUMMY_BYTE_NUM
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
StructPwmToSpiInfo g_stSpiDimmingPwmToSpiInfo;
#if(_DEVICE_LED_DRIVER_MCU_TYPE == _ON)
WORD g_pusSpiDimmingDbgPwmArray[_LOCAL_DIMMING_TOTAL_REGION];
#endif
#if(_SCPU_SUPPORT == _ON)
BYTE g_pucSpiDimmingMemBuf[_DEVICE_LED_DRIVER_SCPU_MEM_CHG_BUF];
#if(_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE)
BYTE g_pucSpiDimmingDdrMemBuf[_LOCAL_DIMMING_SPI_CMD_MAX_LENGTH];
#endif
#endif

volatile bit g_bSpiDimmingSramModeStartTxResult = _TRUE;
volatile bit g_bSpiDimmingSramModeTxDoneFlag;
volatile bit g_bSpiDimmingSramModePendTxFlag;
volatile BYTE g_ucSpiDimmingMultiUpdateIdx;
volatile BYTE g_ucSpiDimmingTxTimeIdx;
WORD g_usSpiDimmingSpiDataByteStartOffset;

// for D-Dimming
#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE)
WORD g_pusSpiDimmingSRamTotalCmdNum[_MAX_PWM2SPI_SMODE_REUSE_TIMES];
DWORD g_ppulSpiDimmingCmdEntryCfg[_MAX_PWM2SPI_SMODE_REUSE_TIMES][_USE_SPI_INTERFACE_NUM];

StructSpiSRamBuf g_ppstSpiDimmingSRamBuf[_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME][_MAX_PWM2SPI_SMODE_REUSE_TIMES];
StructSpiCmdEntryData g_pstSpiDimmingCmdEntryData[_MAX_PWM2SPI_SMODE_REUSE_TIMES];
StructSpiCmdEntryDummyBytes g_pstSpiDimmingCmdEntryDummyBytes[_MAX_PWM2SPI_SMODE_REUSE_TIMES];
#endif
#else
DWORD g_ppulSpiDimmingCmdEntryCfg[_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME][_USE_SPI_INTERFACE_NUM];

WORD g_pusSpiDimmingUpdFrameTotalDataByte[_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME];
StructSpiCmdEntryData g_pstSpiDimmingCmdEntryData[_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME];
StructSpiCmdEntryDummyBytes g_stSpiDimmingCmdEntryDummyBytes;
#endif

// for A-Dimming
#if (_SPI_BOOST_FORMAT_SUPPORT == _ON)
bit g_bSpiDimmingSRamAdimMode = _FALSE;
#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
// TR9
WORD g_pusSpiDimmingADimSRamTotalCmdNum[_MAX_PWM2SPI_SMODE_REUSE_TIMES];
StructSpiSRamBuf g_pstSpiDimmingADimSRamBuf[_MAX_PWM2SPI_SMODE_REUSE_TIMES];
StructSpiCmdEntryData g_pstSpiDimmingADimCmdEntryData[_MAX_PWM2SPI_SMODE_REUSE_TIMES];
#else
// RX3081 only
DWORD g_pulSpiDimmingADimCmdEntryCfg[_USE_SPI_INTERFACE_NUM];
WORD g_usSpiDimmingADimTotalDataByte;
StructSpiCmdEntryData g_stSpiDimmingADimCmdEntryData;
#endif
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Init PWMToSPI for Local Dimming Application
// Input Value  : enumSpiTxTriggerSrc --> PwmToSpi Transmit Trigger Source
//                enumUpdSyncTriggerSrc --> PwmToSpi Upd_Sync Trigger Source
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingInit(void)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    EnumUpdSyncTriggerSrc enumUpdSyncTriggerSrc = _UPD_SYNC_BY_LOCAL_DIMMING_GAIN_SYNC;

#if(_LOCAL_DIMMING_PWM2SPI_MANUAL_MODE == _ON)
    enumUpdSyncTriggerSrc = _UPD_SYNC_BY_MANUAL;
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    if(ScalerCpuCtrlCheckScpuActive() == _TRUE)
    {
        ScalerSpiDimmingSyncInit(enumUpdSyncTriggerSrc);
    }
    else
    {
        DebugMessageHDR("SCPU is Off, Can't Execute ScalerSpiDimmingInit", 0);
    }
#else
    if(ScalerColorLDBLModelGetEnableStatus() == _ON)
    {
        return;
    }

    ScalerColorLDPwmToSpiInitCommon(enumUpdSyncTriggerSrc);

    // PWM2SPI SRAM Mode Enable, Enable SRAM Mode SPI TX done INT
    g_bSpiDimmingSramModeTxDoneFlag = _FALSE;
    g_bSpiDimmingSramModePendTxFlag = _FALSE;

    if(enumUpdSyncTriggerSrc == _UPD_SYNC_BY_LOCAL_DIMMING_GAIN_SYNC)
    {
        ScalerColorLDPwmToSpiSetSramModeControl(_ENABLE, _SMODE_CLK_DCLK, _SMODE_INT_ENABLE, _SMODE_SPI_TX_IMMEDIATE, _TRUE, _DEVICE_LED_DRIVER_UPDSYNC_METHOD, _SMODE_UPDSYNC_IMMEDIATE);
    }
    else
    {
        EnumSModeUpdSyncApplyTiming enumSModeUpdSyncApplyTiming = GET_SMODE_UPDSYNC_MANUAL_APPLY_TIMING();
        ScalerColorLDPwmToSpiSetSramModeControl(_ENABLE, _SMODE_CLK_DCLK, _SMODE_INT_ENABLE, _SMODE_SPI_TX_IMMEDIATE, _FALSE, _DEVICE_LED_DRIVER_UPDSYNC_METHOD, enumSModeUpdSyncApplyTiming);
    }

    ScalerColorLDPwmToSpiSetUpdSyncDeferCnt(_DEVICE_LED_DRIVER_UPDSYNC_DEFER_DCLK_CNT);

#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)
#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
    if(GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_CONSTANT)
#endif
    {
        ScalerSpiDimmingLDSramModeUpdSyncUseSpiInit();
    }
#endif


    // Init PWM2SPI Multi-TX Buffer
#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE)
    ScalerSpiDimmingInitUseDdr();
#endif
#else
    // multi-update sram partition Design
    ScalerSpiDimmingInitUseSram();
#endif

    ScalerColorLDPwmToSpiSwapSpiOutput(_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP);

    // Disable PWM2SPI IP
    ScalerColorLDPwmToSpiEnable(_FUNCTION_OFF);
#endif  // End of #if((_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
#endif  // End of #if(_LOCAL_DIMMING_FUNCTION == _ON)
}

//--------------------------------------------------
// Description  : Set Spi Output interface controlled by MCU
// Input Value  : enumSpiControlSrc  --> Spi IP control Source(MCU/PWM2SPI...etc)
//                enumSpiOutputInterface  --> Spi Output Interface
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingSetSpiCtrlSrc(EnumSpiControlSrc enumSpiControlSrc, EnumSpiInterface enumSpiOutputInterface)
{
    if(enumSpiControlSrc == _SPI_CONTROL_BY_MCU)
    {
#if(_SPI0_SUPPORT == _ON)
        if(enumSpiOutputInterface == _SPI_INTERFACE_0)
        {
            ScalerSetBit(P22_A0_SPI_TRANSACTION_EN, ~(_BIT2), 0x00);
            ScalerSetByte(P22_D4_SPI_S0_WRITE_LENGTH_H, 0x00);
        }
#endif
#if(_SPI1_SUPPORT == _ON)
        if(enumSpiOutputInterface == _SPI_INTERFACE_1)
        {
            ScalerSetBit(P48_A0_SPI_TRANSACTION_EN, ~(_BIT2), 0x00);
            ScalerSetByte(P48_D4_SPI_S0_WRITE_LENGTH_H, 0x00);
        }
#endif
#if(_SPI2_SUPPORT == _ON)
        if(enumSpiOutputInterface == _SPI_INTERFACE_2)
        {
            ScalerSetBit(P4A_A0_SPI_TRANSACTION_EN, ~(_BIT2), 0x00);
            ScalerSetByte(P4A_D4_SPI_S0_WRITE_LENGTH_H, 0x00);
        }
#endif
        return;
    }
    if(enumSpiControlSrc == _SPI_CONTROL_BY_PWM2SPI)
    {
#if(_SPI0_SUPPORT == _ON)
        if(enumSpiOutputInterface == _SPI_INTERFACE_0)
        {
            ScalerSetBit(P22_A0_SPI_TRANSACTION_EN, ~(_BIT2), _BIT2);
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, 0xFF);
            ScalerSetByte(P22_D4_SPI_S0_WRITE_LENGTH_H, 0xFF);
            ScalerSetByte(P22_C4_SPI_BUF_CLR, 0x0F);
        }
#endif
#if(_SPI1_SUPPORT == _ON)
        if(enumSpiOutputInterface == _SPI_INTERFACE_1)
        {
            ScalerSetBit(P48_A0_SPI_TRANSACTION_EN, ~(_BIT2), _BIT2);
            ScalerSetByte(P48_A6_SPI_S0_WRITE_LENGTH, 0xFF);
            ScalerSetByte(P48_D4_SPI_S0_WRITE_LENGTH_H, 0xFF);
            ScalerSetByte(P48_C4_SPI_BUF_CLR, 0x0F);
        }
#endif
#if(_SPI2_SUPPORT == _ON)
        if(enumSpiOutputInterface == _SPI_INTERFACE_2)
        {
            ScalerSetBit(P4A_A0_SPI_TRANSACTION_EN, ~(_BIT2), _BIT2);
            ScalerSetByte(P4A_A6_SPI_S0_WRITE_LENGTH, 0xFF);
            ScalerSetByte(P4A_D4_SPI_S0_WRITE_LENGTH_H, 0xFF);
            ScalerSetByte(P4A_C4_SPI_BUF_CLR, 0x0F);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : PWM2SPI Register Read
// Input Value  : enumPwmToSpiInterface --> pwm2spi interface (0/1)
//                ucDevIndex --> device index (0~31)
//                usSpiStartAddr --> Start Address of Register Reading
//                ucSpiReadByteNum --> read reg number (SPI0 max is 128 bytes , SPI1 max is 4 bytes)
//                pucReadBuffer --> buffer for storing read data
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSpiDimmingRegRead(EnumPwmToSpiInterface enumPwmToSpiInterface, BYTE ucDevIndex, WORD usSpiStartAddr, BYTE ucSpiReadByteNum, BYTE *pucReadBuffer)
{
    bit bRtnStatus = _TRUE;

    BYTE pucSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    WORD usWriteBytes = 0;
    BYTE pucWriteBuffer[_LOCAL_DIMMING_MAX_SPI_READ_CMD_HEADER_LEN];
    EnumSpiInterface enumSpiOutputInterface = MAP_SPI_OUTPUT_INTERFACE(enumPwmToSpiInterface);

    if(ucDevIndex >= pucSpiDevNum[enumPwmToSpiInterface])
    {
        // Device Index Exceed
        return _FALSE;
    }

#if(_DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS == _ON)
    ScalerSpiDimmingToggleUpdateSync();
#endif

    // Switch SPI Control back to MCU
    ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_MCU, enumSpiOutputInterface);

    usWriteBytes = ScalerSpiDimmingFormatReadCmdBuffer(enumPwmToSpiInterface, ucDevIndex, usSpiStartAddr, ucSpiReadByteNum, pucWriteBuffer, sizeof(pucWriteBuffer));

    if(usWriteBytes <= GET_TABLE_ELEMENT_NUM(pucWriteBuffer))
    {
        bRtnStatus = ScalerSpiDataIo(enumSpiOutputInterface, usWriteBytes, ucSpiReadByteNum, pucWriteBuffer, pucReadBuffer);
    }
    else
    {
        DebugMessageHDR("ScalerSpiDimmingRegRead : usWriteBytes > pucWriteBuffer size", usWriteBytes);
        return _FALSE;
    }

    // Restore SPI Switch Control Value
    if(Scaler32GetBit(PB00537_00_PWM2SPI_CONTROL1, _BIT31) == _BIT31)
    {
        ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_PWM2SPI, enumSpiOutputInterface);
    }


#if(_DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS == _ON)
    ScalerSpiDimmingToggleUpdateSync();
#endif

    return bRtnStatus;
}

//--------------------------------------------------
// Description  : PWM2SPI Register Write
// Input Value  : enumSpiInterface --> spi interface (0/1)
//                bUseDevIndex --> use DevIndex(_TRUE) or BroadcastDevId(_FALSE)
//                usDevIdxOrBcId --> devIndex(if bUseDevIndex is _TRUE) or devBcId(if bUseDevIndex is _FALSE)
//                usSpiStartAddr --> Start Address of Register writing
//                usSpiWriteByteNum --> Write reg number(<=32) (NOTE:not include HEAD + Checksum)
//                pucWriteBuffer --> data buffer for writing to SPI, if equal to _NULL_POINTER , fill all zones by using usPwmAllZoneValue
//                usPwmAllZoneValue --> PWM All value
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSpiDimmingBaseWrite(EnumPwmToSpiInterface enumPwmToSpiInterface, bit bUseDevIndex, WORD usDevIdxOrBcId, WORD usSpiStartAddr, WORD usSpiWriteByteNum, BYTE *pucWriteBuffer, bit bBypassUpdSyncAsCS, WORD usPwmAllZoneValue)
{
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    if(ScalerCpuCtrlCheckScpuActive() == _TRUE)
    {
        return ScalerSpiDimmingSyncBaseWrite(enumPwmToSpiInterface, bUseDevIndex, usDevIdxOrBcId, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, bBypassUpdSyncAsCS, usPwmAllZoneValue);
    }
    else
    {
        DebugMessageHDR("SCPU is Off, Can't Execute ScalerSpiDimmingBaseWrite", 0);
        return _FALSE;
    }
#else
    bit bRtnStatus = _TRUE;

    WORD usTotalBytes = 0;
    BYTE pucDataBuf[_LOCAL_DIMMING_SPI_CMD_MAX_LENGTH];
    EnumSpiInterface enumSpiOutputInterface = MAP_SPI_OUTPUT_INTERFACE(enumPwmToSpiInterface);

    if(bBypassUpdSyncAsCS == _FALSE)
    {
        ScalerSpiDimmingToggleUpdateSync();
    }

    // Switch SPI Control back to MCU
    ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_MCU, enumSpiOutputInterface);

    // usTotalBytes = HEAD + DATA + CHECKSUM
    usTotalBytes = ScalerSpiDimmingFormatWriteCmdBuffer(enumPwmToSpiInterface, bUseDevIndex, usDevIdxOrBcId, usSpiStartAddr, pucWriteBuffer, usSpiWriteByteNum, pucDataBuf, sizeof(pucDataBuf), _TRUE, usPwmAllZoneValue);

    bRtnStatus = ScalerSpiDataIo(enumSpiOutputInterface, usTotalBytes, 0, pucDataBuf, pucDataBuf);

    // Restore SPI Switch Control Value
    if(Scaler32GetBit(PB00537_00_PWM2SPI_CONTROL1, _BIT31) == _BIT31)
    {
        // Local Dimming IP is Power On now
        ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_PWM2SPI, enumSpiOutputInterface);
    }

    if(bBypassUpdSyncAsCS == _FALSE)
    {
        ScalerSpiDimmingToggleUpdateSync();
    }

    return bRtnStatus;
#endif
}

//--------------------------------------------------
// Description  : PWM2SPI Register Write
// Input Value  : enumSpiInterface --> spi interface (0/1)
//                ucDevIndex --> device index (0~31)
//                usSpiStartAddr --> Start Address of Register writing
//                usSpiWriteByteNum --> Write reg number(<=32)
//                pucWriteBuffer --> data buffer for writing to SPI
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSpiDimmingRegWrite(EnumPwmToSpiInterface enumPwmToSpiInterface, WORD usDevIndex, WORD usSpiStartAddr, WORD usSpiWriteByteNum, BYTE *pucWriteBuffer)
{
#if(_DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS == _ON)
    return ScalerSpiDimmingBaseWrite(enumPwmToSpiInterface, _TRUE, usDevIndex, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, _FALSE, 0);
#else
    return ScalerSpiDimmingBaseWrite(enumPwmToSpiInterface, _TRUE, usDevIndex, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, _TRUE, 0);
#endif
}

//--------------------------------------------------
// Description  : Adjust SRGB function
// Input Value  : ucSpiInterface --> spi interface (0/1)
//                ucDevIndex --> device index (0~31)
//                usSpiStartAddr --> Start Address of Register Writing
//                usSpiWriteByteNum --> Write reg number
//                pucWriteBuffer --> buffer for storing read data, if equal to _NULL_POINTER , fill all zones by using usPwmAllZoneValue
//                bPwmAllZone --> is apply PWM All the same value
//                usPwmAllZoneValue --> PWM All value
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSpiDimmingRegWriteAll(WORD usSpiStartAddr, WORD usSpiWriteByteNum, BYTE *pucWriteBuffer, WORD usPwmAllZoneValue)
{
    bit bRtnStatus = _TRUE;

#if(_DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS == _ON)
    ScalerSpiDimmingToggleUpdateSync();
#endif

#if(_DEVICE_LED_DRIVER_SUPPORT_BROADCAST == _ON)
#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM != 0)
    bRtnStatus = ScalerSpiDimmingBaseWrite(_PWMTOSPI_INTERFACE_0, _FALSE, _DEVICE_LED_DRIVER_BROADCAST_ID, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, _TRUE, usPwmAllZoneValue);
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
    if(bRtnStatus == _TRUE)
    {
        bRtnStatus = ScalerSpiDimmingBaseWrite(_PWMTOSPI_INTERFACE_1, _FALSE, _DEVICE_LED_DRIVER_BROADCAST_ID, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, _TRUE, usPwmAllZoneValue);
    }
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
    if(bRtnStatus == _TRUE)
    {
        bRtnStatus = ScalerSpiDimmingBaseWrite(_PWMTOSPI_INTERFACE_2, _FALSE, _DEVICE_LED_DRIVER_BROADCAST_ID, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, _TRUE, usPwmAllZoneValue);
    }
#endif
#if(_DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS == _ON)
    ScalerSpiDimmingToggleUpdateSync();
#endif

#else
    // _DEVICE_LED_DRIVER_SUPPORT_BROADCAST == _OFF
    for(WORD usIdx = 0; usIdx < _MAX_SPI_DEV_NUM; usIdx++)
    {
#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM != 0)
        if((usIdx < _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM) && (ScalerSpiDimmingBaseWrite(_PWMTOSPI_INTERFACE_0, _TRUE, usIdx, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, _TRUE, usPwmAllZoneValue) == _FALSE))
        {
            bRtnStatus = _FALSE;
            break;
        }
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
        if((usIdx < _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM) && (ScalerSpiDimmingBaseWrite(_PWMTOSPI_INTERFACE_1, _TRUE, usIdx, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, _TRUE, usPwmAllZoneValue) == _FALSE))
        {
            bRtnStatus = _FALSE;
            break;
        }
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
        if((usIdx < _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM) && (ScalerSpiDimmingBaseWrite(_PWMTOSPI_INTERFACE_2, _TRUE, usIdx, usSpiStartAddr, usSpiWriteByteNum, pucWriteBuffer, _TRUE, usPwmAllZoneValue) == _FALSE))
        {
            bRtnStatus = _FALSE;
            break;
        }
#endif

#if(_DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS == _ON)
        ScalerSpiDimmingToggleUpdateSync();
#endif
    }
#endif

    return bRtnStatus;
}

//--------------------------------------------------
// Description  : set PwmValue for all zones of all Devices
// Input Value  : usPwmValue --> PwmValue for all zones of all Devices
// Output Value : None
//--------------------------------------------------
bit ScalerSpiDimmingSetPwmValueToAllZone(WORD usPwmValue)
{
    WORD usTmpPwmValue = ((usPwmValue > _DEVICE_LED_DRIVER_PWM_MAX) ? _DEVICE_LED_DRIVER_PWM_MAX : usPwmValue);

    return ScalerSpiDimmingRegWriteAll(GET_BROADCAST_PWM_START_ADDRESS(), _LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM, _NULL_POINTER, usTmpPwmValue);
}

//--------------------------------------------------
// Description  : Manual Trigger PwmToSpi Update Sync Signal (Update Sync Source must set to manual mode(_UPD_SYNC_BY_MANUAL),this function can work when PwmToSpi IP disabled)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingToggleUpdateSync(void)
{
    if(ScalerPowerGroupGetPowerCutStatus(_HW_LOCAL_DIMMING_POWER_DOMAIN) == _POWER_CUT_OFF)
    {
        // Local Dimming IP is Power On now
        DWORD ulTmpPwm2SpiCtrl1 = Scaler32GetDWord(PB00537_00_PWM2SPI_CONTROL1) & ~((DWORD)(_BIT10 | _BIT9));

        // FW control upd_sync pin by using invert flag (no need DCLK)
        Scaler32SetDWord(PB00537_00_PWM2SPI_CONTROL1, (ulTmpPwm2SpiCtrl1 ^ ((DWORD)_BIT11)));
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS != 0)
        DELAY_XUS(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS);
#endif
        Scaler32SetDWord(PB00537_00_PWM2SPI_CONTROL1, ulTmpPwm2SpiCtrl1);
    }
    else
    {
        // Local Dimming IP is Power Off now
        ScalerPinsharePwmUpdSyncSwitch();
    }
}

//--------------------------------------------------
// Description  : Set SPI HW controlled By PwmToSpi
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingSetSpiHwToLD(void)
{
#if(_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP == _OFF)
    // Setup SPI Module Controlled By PwmToSpi
    ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_PWM2SPI, _SPI_INTERFACE_0);

#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
    ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_PWM2SPI, _SPI_INTERFACE_1);
#endif

#else
    // Setup SPI Module Controlled By PwmToSpi
    ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_PWM2SPI, _SPI_INTERFACE_1);
#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
    ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_PWM2SPI, _SPI_INTERFACE_0);
#endif
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
    ScalerSpiDimmingSetSpiCtrlSrc(_SPI_CONTROL_BY_PWM2SPI, _SPI_INTERFACE_2);
#endif
}

//--------------------------------------------------
// Description  : Get specified LedDevice's PWM Zones' Pwm Remap Info
// Input Value  : ucDevIndex  --> Led Device Index(0~N)
//                usPwmStartIndex --> Start Index Of Pwm Value(0~N)
//                usPwmNum --> Pwm Number(1~N)
//                pusPwmRemapInfo --> return Pwm Remap Info
// Output Value : execute Status(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerSpiDimmingGetPwmRemapInfo(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmNum, WORD *pusPwmRemapInfo)
{
    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    WORD *ppusRemapTable[3] = {tLDPwmToSpiRemapTable0, tLDPwmToSpiRemapTable1, tLDPwmToSpiRemapTable2};
    WORD pusRemapTableElementNum[3] = {GET_TABLE_ELEMENT_NUM(tLDPwmToSpiRemapTable0), GET_TABLE_ELEMENT_NUM(tLDPwmToSpiRemapTable1), GET_TABLE_ELEMENT_NUM(tLDPwmToSpiRemapTable2)};
    WORD usDevAccIdx = 0;
    for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
    {
        WORD usInterfaceRemapIdx = 0;
        WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];

        for(WORD usSpiDevIdx = 0; usSpiDevIdx < usSpiXDevNum; usSpiDevIdx++)
        {
            if(ucDevIndex == usDevAccIdx)
            {
                usInterfaceRemapIdx += usPwmStartIndex;
                if((usInterfaceRemapIdx + usPwmNum) > pusRemapTableElementNum[ucSpiInterfaceIdx])
                {
                    // index out of bound
                    DebugMessageHDR("ScalerSpiDimmingGetPwmRemapInfo index out of bound", (usInterfaceRemapIdx + usPwmNum));
                    return _FALSE;
                }

                for(WORD usPwmIdx = 0; usPwmIdx < usPwmNum; usPwmIdx++)
                {
                    pusPwmRemapInfo[usPwmIdx] = ppusRemapTable[ucSpiInterfaceIdx][(usInterfaceRemapIdx + usPwmIdx)];
                }
                return _TRUE;
            }
            else
            {
                usInterfaceRemapIdx += (tLedSpiDataByteNum[usDevAccIdx] / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE);
                usDevAccIdx++;
            }
        }
    }
    DebugMessageHDR("ScalerSpiDimmingGetPwmRemapInfo index out of bound", 0);
    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler Debug Write PWM to Led Device
// Input Value  : ucDevIndex  --> Led Device Index(0~31)
//                usPwmStartIndex --> Start Index Of Pwm Value(0~15)
//                usPwmWriteNum --> Pwm Value Write Number(1~16)
//                pusPwmValue --> PWM Write Buffer
// Output Value : execute Status(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerSpiDimmingDebugWritePWM(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmWriteNum, WORD *pusPwmValue)
{
    if(usPwmWriteNum > (_LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE))
    {
        return _FALSE;
    }

#if(_DEVICE_LED_DRIVER_MCU_TYPE == _OFF)
#if(_LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP == _ON)
    for(WORD usIdx = 0; usIdx < usPwmWriteNum; usIdx++)
    {
        pusPwmValue[usIdx] = __REV16(pusPwmValue[usIdx]);
    }
#endif

    return ScalerSpiDimmingDebugWriteReg(ucDevIndex, usPwmStartIndex, usPwmWriteNum, pusPwmValue, _SPI_DEBUG_PWM_REG);
#else

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    if(ScalerCpuCtrlCheckScpuActive() == _TRUE)
    {
        return ScalerSpiDimmingSyncDebugWriteMcuPwm(ucDevIndex, usPwmStartIndex, usPwmWriteNum, pusPwmValue);
    }
    DebugMessageHDR("SCPU is Off, Can't Execute ScalerSpiDimmingSyncDebugWriteMcuPwm", 0);
    return _FALSE;
#else
    WORD pusPwmRemapInfo[(_LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE)];

    if(ScalerSpiDimmingGetPwmRemapInfo(ucDevIndex, 0, (_LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE), pusPwmRemapInfo) == _FALSE)
    {
        return _FALSE;
    }

    for(WORD usIdx = 0; usIdx < usPwmWriteNum; usIdx++)
    {
        g_pusSpiDimmingDbgPwmArray[(pusPwmRemapInfo[(usPwmStartIndex + usIdx)])] = pusPwmValue[usIdx];
    }

    // use pusPwmRemapInfo as temp buffer to store pwm value
#if(_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE == 1)
    BYTE *pucOneBytePwmArray = (BYTE *)pusPwmRemapInfo;
#endif

    for(WORD usIdx = 0; usIdx < (_LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE); usIdx++)
    {
        WORD usPwmValue = g_pusSpiDimmingDbgPwmArray[pusPwmRemapInfo[usIdx]];
#if(_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE == 1)
        pucOneBytePwmArray[usIdx] = (BYTE)usPwmValue;
#else
#if(_LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP == _ON)
        pusPwmRemapInfo[usIdx] = __REV16(usPwmValue);
#else
        pusPwmRemapInfo[usIdx] = usPwmValue;
#endif
#endif
    }

#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM != 0)
    if(ucDevIndex < _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM)
    {
        return ScalerSpiDimmingBaseWrite(
            _PWMTOSPI_INTERFACE_0,
            _TRUE,
            ucDevIndex,
            GET_BROADCAST_PWM_START_ADDRESS(),
            _LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM,
            (BYTE *)pusPwmRemapInfo,
            _TRUE,
            0);
    }
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
    if(ucDevIndex < (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM))
    {
        return ScalerSpiDimmingBaseWrite(
            _PWMTOSPI_INTERFACE_1,
            _TRUE,
            (ucDevIndex - _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM),
            GET_BROADCAST_PWM_START_ADDRESS(),
            _LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM,
            (BYTE *)pusPwmRemapInfo,
            _TRUE,
            0);
    }
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
    if(ucDevIndex < (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM))
    {
        return ScalerSpiDimmingBaseWrite(
            _PWMTOSPI_INTERFACE_2,
            _TRUE,
            (ucDevIndex - _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM - _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM),
            GET_BROADCAST_PWM_START_ADDRESS(),
            _LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM,
            (BYTE *)pusPwmRemapInfo,
            _TRUE,
            0);
    }
#endif
    return _FALSE;
#endif
#endif
}

//--------------------------------------------------
// Description  : Scaler Debug Read PWM from Led Device
// Input Value  : ucDevIndex  --> Led Device Index(0~31)
//                usPwmStartIndex --> Start Index Of Pwm Value(0~15)
//                usPwmReadNum --> Pwm Value Read Number(1~16)
//                pusPwmValue --> PWM Read Buffer
// Output Value : execute Status(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerSpiDimmingDebugReadPWM(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmReadNum, WORD *pusPwmValue)
{
    if(usPwmReadNum > (32 / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE))
    {
        return _FALSE;
    }

#if(_DEVICE_LED_DRIVER_MCU_TYPE == _OFF)
    if(ScalerSpiDimmingDebugReadReg(ucDevIndex, usPwmStartIndex, usPwmReadNum, pusPwmValue, _SPI_DEBUG_PWM_REG) == _TRUE)
    {
#if(_LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP == _ON)
        for(WORD usIdx = 0; usIdx < usPwmReadNum; usIdx++)
        {
            pusPwmValue[usIdx] = __REV16(pusPwmValue[usIdx]);
        }
#endif
        return _TRUE;
    }
#else

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    if(ScalerCpuCtrlCheckScpuActive() == _TRUE)
    {
        return ScalerSpiDimmingSyncDebugReadMcuPwm(ucDevIndex, usPwmStartIndex, usPwmReadNum, pusPwmValue);
    }
    DebugMessageHDR("SCPU is Off, Can't Execute ScalerSpiDimmingSyncDebugReadMcuPwm", 0);
#else
    WORD pusPwmRemapInfo[(32 / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE)];
    if(ScalerSpiDimmingGetPwmRemapInfo(ucDevIndex, usPwmStartIndex, usPwmReadNum, pusPwmRemapInfo) == _TRUE)
    {
        for(WORD usIdx = 0; usIdx < usPwmReadNum; usIdx++)
        {
            pusPwmValue[usIdx] = g_pusSpiDimmingDbgPwmArray[(pusPwmRemapInfo[usIdx])];
        }
        return _TRUE;
    }
#endif
#endif
    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler Debug Write data to Led Device's register
// Input Value  : ucDevIndex  --> Led Device Index(0~31)
//                usRegStartAddr --> Start Address of Normal Reg Write or Start Index of PWM Reg Write
//                usWriteRegNum --> write register number
//                pusRegValue --> Reg Write Buffer
//                enumSpiDebugRWDest --> Write to PWM Register or Other Register
// Output Value : execute Status(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerSpiDimmingDebugWriteReg(BYTE ucDevIndex, WORD usRegStartAddr, WORD usWriteRegNum, WORD *pusRegValue, EnumSpiDebugRWDest enumSpiDebugRWDest)
{
    WORD usWriteByteNum = usWriteRegNum * ((enumSpiDebugRWDest == _SPI_DEBUG_PWM_REG) ? _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE : _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE);

    if(enumSpiDebugRWDest == _SPI_DEBUG_PWM_REG)
    {
        usRegStartAddr = GET_BROADCAST_PWM_START_ADDRESS() + (usRegStartAddr * _DEVICE_LED_DRIVER_PWM_ADDRESS_STEP);
    }

#if((_DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE > 1) && (_DEVICE_LED_DRIVER_REG_BYTE_SWAP == _ON))
    for(WORD usIdx = 0; usIdx < usWriteRegNum; usIdx++)
    {
        pusRegValue[usIdx] = __REV16(pusRegValue[usIdx]);
    }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM != 0)
    if(ucDevIndex < _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM)
    {
        return ScalerSpiDimmingRegWrite(_PWMTOSPI_INTERFACE_0, ucDevIndex, usRegStartAddr, usWriteByteNum, (BYTE *)pusRegValue);
    }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
    if(ucDevIndex < (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM))
    {
        ucDevIndex = ucDevIndex - _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM;
        return ScalerSpiDimmingRegWrite(_PWMTOSPI_INTERFACE_1, ucDevIndex, usRegStartAddr, usWriteByteNum, (BYTE *)pusRegValue);
    }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
    if(ucDevIndex < (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM))
    {
        ucDevIndex = ucDevIndex - _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM - _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM;
        return ScalerSpiDimmingRegWrite(_PWMTOSPI_INTERFACE_2, ucDevIndex, usRegStartAddr, usWriteByteNum, (BYTE *)pusRegValue);
    }
#endif
    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler Debug Read data from Led Device's register
// Input Value  : ucDevIndex  --> Led Device Index(0~31)
//                usRegStartAddr --> Start Address of Normal Reg Read or Start Index of PWM Reg Read
//                usReadRegNum --> read register number
//                pusRegValue --> Reg Read Buffer
//                enumSpiDebugRWDest  --> Read PWM Register or Other Register
// Output Value : execute Status(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerSpiDimmingDebugReadReg(BYTE ucDevIndex, WORD usRegStartAddr, WORD usReadRegNum, WORD *pusRegValue, EnumSpiDebugRWDest enumSpiDebugRWDest)
{
    bit bExeStatus = _FALSE;
    EnumPwmToSpiInterface enumPwmToSpiInterface = _PWMTOSPI_INTERFACE_0;
    BYTE ucSpiRxBufMaxLength = _SPI0_RX_BUFFER_MAX_LENGTH;
    WORD usReadByteNum = usReadRegNum * ((enumSpiDebugRWDest == _SPI_DEBUG_PWM_REG) ? _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE : _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE);
    BYTE *pucRegBuf = (BYTE *)pusRegValue;

    if(enumSpiDebugRWDest == _SPI_DEBUG_PWM_REG)
    {
        usRegStartAddr = GET_BROADCAST_PWM_START_ADDRESS() + (usRegStartAddr * _DEVICE_LED_DRIVER_PWM_ADDRESS_STEP);
    }

    if(ucDevIndex < _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM)
    {
        bExeStatus = _TRUE;
        enumPwmToSpiInterface = _PWMTOSPI_INTERFACE_0;

#if(_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP == _OFF)
        ucSpiRxBufMaxLength = _SPI0_RX_BUFFER_MAX_LENGTH;
#else
        ucSpiRxBufMaxLength = _SPI1_RX_BUFFER_MAX_LENGTH;
#endif
    }
    else
    {
#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
        if(ucDevIndex < (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM))
        {
            ucDevIndex = ucDevIndex - _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM;
            bExeStatus = _TRUE;
            enumPwmToSpiInterface = _PWMTOSPI_INTERFACE_1;

#if(_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP == _OFF)
            ucSpiRxBufMaxLength = _SPI1_RX_BUFFER_MAX_LENGTH;
#else
            ucSpiRxBufMaxLength = _SPI0_RX_BUFFER_MAX_LENGTH;
#endif
        }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
        if(ucDevIndex < (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM))
        {
            ucDevIndex = ucDevIndex - _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM - _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM;
            bExeStatus = _TRUE;
            enumPwmToSpiInterface = _PWMTOSPI_INTERFACE_2;

            ucSpiRxBufMaxLength = _SPI1_RX_BUFFER_MAX_LENGTH;
        }
#endif
    }

    ucSpiRxBufMaxLength = ((ucSpiRxBufMaxLength / _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE) * _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE);


    if(bExeStatus == _TRUE)
    {
        WORD usGotByteNum = 0;

        while((usGotByteNum != usReadByteNum) && (bExeStatus == _TRUE))
        {
            WORD usRegOffsetIdx = (usGotByteNum / _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE);
            if((usReadByteNum - usGotByteNum) > ucSpiRxBufMaxLength)
            {
                bExeStatus = ScalerSpiDimmingRegRead(enumPwmToSpiInterface, ucDevIndex, (usRegStartAddr + usRegOffsetIdx), ucSpiRxBufMaxLength, (&pucRegBuf[usGotByteNum]));
                usGotByteNum += ucSpiRxBufMaxLength;
            }
            else
            {
                bExeStatus = ScalerSpiDimmingRegRead(enumPwmToSpiInterface, ucDevIndex, (usRegStartAddr + usRegOffsetIdx), (usReadByteNum - usGotByteNum), (&pucRegBuf[usGotByteNum]));
                usGotByteNum = usReadByteNum;
            }
        }
    }

#if((_DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE > 1) && (_DEVICE_LED_DRIVER_REG_BYTE_SWAP == _ON))
    for(WORD usIdx = 0; usIdx < usReadRegNum; usIdx++)
    {
        pusRegValue[usIdx] = __REV16(pusRegValue[usIdx]);
    }
#endif

    return bExeStatus;
}

//--------------------------------------------------
// Description  : Get Pwm2Spi table query Index for the device Index on the specified SPI interface
// Input Value  : enumPwmToSpiInterface  --> Spi Interface
//                ucSpiDevIdx --> the device Index on the specified SPI interface
// Output Value : Pwm2Spi table query Index
//--------------------------------------------------
WORD ScalerSpiDimmingGetTableIndex(EnumPwmToSpiInterface enumPwmToSpiInterface, BYTE ucSpiDevIdx)
{
    if(enumPwmToSpiInterface == _PWMTOSPI_INTERFACE_0)
    {
        return ucSpiDevIdx;
    }
    else if(enumPwmToSpiInterface == _PWMTOSPI_INTERFACE_1)
    {
        return (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + ucSpiDevIdx);
    }
    else
    {
        return (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM + ucSpiDevIdx);
    }
}

//--------------------------------------------------
// Description  : Format LED Driver SPI Read Command Buffer
// Input Value  : enumSpiInterface --> spi interface (0/1)
//                ucDevIndex --> device index (0~31)
//                usSpiStartAddr --> Start Address of Register Reading
//                usSpiReadByteNum --> read reg number (SPI0 max is 128 bytes , SPI1 max is 4 bytes)
//                pucDataBuffer: SPI Read Buffer
//                usDataBufferSize: size of SPI Read Buffer
// Output Value : SPI command Write Byte Number
//--------------------------------------------------
WORD ScalerSpiDimmingFormatReadCmdBuffer(EnumPwmToSpiInterface enumPwmToSpiInterface, BYTE ucDevIndex, WORD usSpiStartAddr, WORD usSpiReadByteNum, BYTE *pucDataBuffer, WORD usDataBufferSize)
{
    StructSpiCmdInfo stSpiCmdInfo;
    WORD usPwm2SpiTableIdx = 0;
    WORD usSpiCmdHeaderBytes = 0;
    WORD usWriteBytes = 0;

    switch(enumPwmToSpiInterface)
    {
#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM > 0)
        case _PWMTOSPI_INTERFACE_0:
            usWriteBytes = (WORD)_LOCAL_DIMMING_SPI0_READ_CMD_HEADER_LEN;
            break;
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM > 0)
        case _PWMTOSPI_INTERFACE_1:
            usWriteBytes = (WORD)_LOCAL_DIMMING_SPI1_READ_CMD_HEADER_LEN;
            break;
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM > 0)
        case _PWMTOSPI_INTERFACE_2:
            usWriteBytes = (WORD)_LOCAL_DIMMING_SPI2_READ_CMD_HEADER_LEN;
            break;
#endif
        default:
            return 0;
    }

    usPwm2SpiTableIdx = ScalerSpiDimmingGetTableIndex(enumPwmToSpiInterface, ucDevIndex);

    stSpiCmdInfo.usDevAddr = tLedSpiDevAddr[usPwm2SpiTableIdx];
    stSpiCmdInfo.usRegStartAddr = usSpiStartAddr;

    usSpiCmdHeaderBytes = ExternalDeviceInterfaceLedFormatReadCmdHeader(&stSpiCmdInfo, usSpiReadByteNum, pucDataBuffer);

    if(usSpiCmdHeaderBytes > _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES)
    {
        DebugMessageHDR("usSpiCmdHeaderBytes > _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES", usSpiCmdHeaderBytes);
        // force restrict headerBytes for avoiding memset operation over pucDataBuffer array length
        usSpiCmdHeaderBytes = _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES;
    }

    usWriteBytes += usSpiCmdHeaderBytes;
    memset((&pucDataBuffer[usSpiCmdHeaderBytes]), _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_PATTERN, (usDataBufferSize - usSpiCmdHeaderBytes));

    return usWriteBytes;
}

//--------------------------------------------------
// Description  : Format LED Driver SPI Write Command Buffer
// Input Value  : enumSpiInterface --> spi interface (0/1)
//                bUseDevIndex --> use DevIndex(_TRUE) or BroadcastDevId(_FALSE)
//                usDevIdxOrBcId --> devIndex(if bUseDevIndex is _TRUE) or devBcId(if bUseDevIndex is _FALSE)
//                usSpiStartAddr --> Start Address of Register Reading
//                pucPayLoadBuffer: SPI Write Buffer, if equal to _NULL_POINTER , fill all zones by using usPwmAllZoneValue
//                usPayloadBufferSize: size of SPI Write Buffer (only include DATA part, not include Header && Checksum)
//                pucCmdBuffer: SPI Write Cmd Buffer
//                usCmdBufferSize: size of SPI Write Cmd Buffer
//                bAppendDummyByte --> Append Dummy Bytes
//                usPwmAllZoneValue --> PWM All value
// Output Value : SPI command Write Byte Number (HEAD + DATA + CHECKSUM + DUMMY)
//--------------------------------------------------
WORD ScalerSpiDimmingFormatWriteCmdBuffer(EnumPwmToSpiInterface enumPwmToSpiInterface, bit bUseDevIndex, WORD usDevIdxOrBcId, WORD usSpiStartAddr, BYTE *pucPayLoadBuffer, WORD usPayloadBufferSize, BYTE *pucCmdBuffer, WORD usCmdBufferSize, bit bAppendDummyByte, WORD usPwmAllZoneValue)
{
    StructSpiCmdInfo stSpiCmdInfo;

    WORD usSpiWrtCmdHeaderBytes = 0;
    WORD usHeadPayloadChksumBytes = 0;
    WORD usTotalBytes = 0;

#if(_DEVICE_LED_DRIVER_SUPPORT_BROADCAST == _OFF)
    bUseDevIndex = _TRUE;
#endif

    if(bUseDevIndex == _TRUE)
    {
        WORD usPwm2SpiTableIdx = ScalerSpiDimmingGetTableIndex(enumPwmToSpiInterface, usDevIdxOrBcId);

        if(usPwm2SpiTableIdx < GET_TABLE_ELEMENT_NUM(tLedSpiDevAddr))
        {
            stSpiCmdInfo.usDevAddr = tLedSpiDevAddr[usPwm2SpiTableIdx];
        }
        else
        {
            // Error Handling for table index out of bound
            DebugMessageHDR("tLedSpiDevAddr table index out of bound", usPwm2SpiTableIdx);
            stSpiCmdInfo.usDevAddr = 0;
        }

        if(bAppendDummyByte == _TRUE)
        {
            if(usPwm2SpiTableIdx < GET_TABLE_ELEMENT_NUM(tLedSpiDummyByteNum))
            {
                usTotalBytes += tLedSpiDummyByteNum[usPwm2SpiTableIdx];
            }
            else
            {
                // Error Handling for table index out of bound
                DebugMessageHDR("tLedSpiDummyByteNum table index out of bound", usPwm2SpiTableIdx);
            }
        }
    }
    else
    {
        stSpiCmdInfo.usDevAddr = usDevIdxOrBcId;
        if(bAppendDummyByte == _TRUE)
        {
            usTotalBytes += _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM;
        }
    }

    stSpiCmdInfo.usRegStartAddr = usSpiStartAddr;

    usSpiWrtCmdHeaderBytes = ExternalDeviceInterfaceLedFormatWriteCmdHeader(&stSpiCmdInfo, usPayloadBufferSize, pucCmdBuffer);

    // HEAD + DATA
    usHeadPayloadChksumBytes = (usSpiWrtCmdHeaderBytes + usPayloadBufferSize + _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM);
    usTotalBytes += usHeadPayloadChksumBytes;

    if(pucPayLoadBuffer == _NULL_POINTER)
    {
        WORD usTmpPayloadBufferSize = (usPayloadBufferSize & ~_BIT0);
        BYTE *pucTmpPwmDataBuf = (BYTE *)(&pucCmdBuffer[usSpiWrtCmdHeaderBytes]);
        BYTE ucTmpLowByte = LOBYTE(usPwmAllZoneValue);      // Low Pwm Byte
#if(_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE > 1)
        BYTE ucTmpHighByte = HIBYTE(usPwmAllZoneValue);     // High Pwm Byte
#endif
        WORD usIdx = 0;
        while(usIdx < usTmpPayloadBufferSize)
        {
#if(_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE == 1)
            pucTmpPwmDataBuf[usIdx++] = ucTmpLowByte;
#else
#if(_LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP == _OFF)
            pucTmpPwmDataBuf[usIdx++] = ucTmpLowByte;    // Low Pwm Byte
            pucTmpPwmDataBuf[usIdx++] = ucTmpHighByte;    // High Pwm Byte
#else
            pucTmpPwmDataBuf[usIdx++] = ucTmpHighByte;    // High Pwm Byte
            pucTmpPwmDataBuf[usIdx++] = ucTmpLowByte;    // Low Pwm Byte
#endif
#endif
        }
    }
    else
    {
        memcpy((&pucCmdBuffer[usSpiWrtCmdHeaderBytes]), pucPayLoadBuffer, usPayloadBufferSize);
    }

#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
    ExternalDeviceInterfaceLedDriverCalcChecksum(pucCmdBuffer, usHeadPayloadChksumBytes);
#endif

    if(bAppendDummyByte == _TRUE)
    {
        memset((&pucCmdBuffer[usHeadPayloadChksumBytes]), _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_PATTERN, (usCmdBufferSize - usHeadPayloadChksumBytes));
    }

    return usTotalBytes;
}

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : Init PWMToSPI for Local Dimming Application (KCPU notify SCPU to execute)
// Input Value  : enumSpiTxTriggerSrc --> PwmToSpi Transmit Trigger Source
//                enumUpdSyncTriggerSrc --> PwmToSpi Upd_Sync Trigger Source
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingSyncInit(EnumUpdSyncTriggerSrc enumUpdSyncTriggerSrc)
{
    StructCpuSyncSpiDimmingCmd *pstCmd = &g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd;
    pstCmd->unSubCmdBody.stInitCmd.usUpdSyncTriggerSrc = (WORD)enumUpdSyncTriggerSrc;
    pstCmd->ucSubCmdType = _SPI_DIMMING_INIT;

    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_SPI_DIMMING, _SCALER_CPU_SYNC_TIMEOUT_COLOR_SPI_DIMMING, _NULL_POINTER);
}

//--------------------------------------------------
// Description  : PWM2SPI Register Write (KCPU notify SCPU to execute)
// Input Value  : enumSpiInterface --> spi interface (0/1)
//                bUseDevIndex --> use DevIndex(_TRUE) or BroadcastDevId(_FALSE)
//                usDevIdxOrBcId --> devIndex(if bUseDevIndex is _TRUE) or devBcId(if bUseDevIndex is _FALSE)
//                usSpiStartAddr --> Start Address of Register writing
//                usSpiWriteByteNum --> Write reg number(<=32) (NOTE:not include HEAD + Checksum)
//                pucWriteBuffer --> data buffer for writing to SPI, if equal to _NULL_POINTER , fill all zones by using usPwmAllZoneValue
//                usPwmAllZoneValue --> PWM All value
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSpiDimmingSyncBaseWrite(EnumPwmToSpiInterface enumPwmToSpiInterface, bit bUseDevIndex, WORD usDevIdxOrBcId, WORD usSpiStartAddr, WORD usSpiWriteByteNum, BYTE *pucWriteBuffer, bit bBypassUpdSyncAsCS, WORD usPwmAllZoneValue)
{
    BYTE *pucTmpWriteBuffer = pucWriteBuffer;
    UnionCpuSyncReplyCmdBody unCpuSyncToScpuCmdReplyBody = {0};

    if(pucWriteBuffer != _NULL_POINTER)
    {
        switch(ScalerUtilGetAddressType((DWORD)pucWriteBuffer))
        {
            case _ADDRESS_TYPE_FLASH:
            {
                DWORD ulAddress = 0;

                // Convert KCPU 32bits Flash Address to SCPU 32bits Flash Address
                ScalerCpuHalGetScpuFlashAddressPointer((DWORD)pucTmpWriteBuffer, &ulAddress);

                pucTmpWriteBuffer = (BYTE *)ulAddress;
                break;
            }

            case _ADDRESS_TYPE_IMEM:
            case _ADDRESS_TYPE_DMEM:
                if(usSpiWriteByteNum > _LOCAL_DIMMING_SPI_CMD_MAX_LENGTH)
                {
                    // Error Condition
                    DebugMessageHDR("usSpiWriteByteNum > _LOCAL_DIMMING_SPI_CMD_MAX_LENGTH", usSpiWriteByteNum);
                    return _FALSE;
                }

                // from KCPU IMEM or DMEM,SCPU can't direct access
                WORD usIdx = 0;
                while(usIdx < usSpiWriteByteNum)
                {
                    WORD usTxByteNum = (usSpiWriteByteNum - usIdx);
                    if(usTxByteNum > _DEVICE_LED_DRIVER_SCPU_MEM_CHG_BUF)
                    {
                        usTxByteNum = _DEVICE_LED_DRIVER_SCPU_MEM_CHG_BUF;
                    }

                    {
                        WORD usExChgBufIdx = 0;
                        BYTE *pucWrtBufOffset = (BYTE *)&pucWriteBuffer[usIdx];
                        while(usExChgBufIdx < usTxByteNum)
                        {
                            g_pucSpiDimmingMemBuf[usExChgBufIdx] = pucWrtBufOffset[usExChgBufIdx];
                            usExChgBufIdx++;
                        }
                    }
                    StructCpuSyncSpiDimmingMemcpyCmd *pstMemcpyCmd = &g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd.unSubCmdBody.stMemcpyCmd;
                    pstMemcpyCmd->usWriteOffset = usIdx;
                    pstMemcpyCmd->usWriteByteLength = usTxByteNum;
                    g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd.ucSubCmdType = _SPI_DIMMING_MEMCPY;

                    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_SPI_DIMMING, _SCALER_CPU_SYNC_TIMEOUT_COLOR_SPI_DIMMING, &unCpuSyncToScpuCmdReplyBody);
                    if(unCpuSyncToScpuCmdReplyBody.stCpuSyncSpiDimmingCmdReply.bExecuteStatus == _FALSE)
                    {
                        // Error Condition
                        DebugMessageHDR("Execute SPI_DIMMING_MEMCPY Failed, Address =", (DWORD)pucWriteBuffer);
                        DebugMessageHDR("Execute SPI_DIMMING_MEMCPY Failed, Length =", (DWORD)usSpiWriteByteNum);
                        return _FALSE;
                    }
                    usIdx += usTxByteNum;
                }
                pucTmpWriteBuffer = (BYTE *)unCpuSyncToScpuCmdReplyBody.stCpuSyncSpiDimmingCmdReply.ulMemAddress;
                break;

            case _ADDRESS_TYPE_XRAM:
            case _ADDRESS_TYPE_ROM:
                // No Need advance process
                break;

            default:
                // Not Support
                return _FALSE;
                break;
        }
    }

    StructCpuSyncSpiDimmingBaseWriteCmd *pstSpiDimmingBaseWriteCmd = &g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd.unSubCmdBody.stBaseWriteCmd;
    pstSpiDimmingBaseWriteCmd->usPwmToSpiInterface = (WORD)enumPwmToSpiInterface;
    pstSpiDimmingBaseWriteCmd->bUseDevIndex = bUseDevIndex;
    pstSpiDimmingBaseWriteCmd->usDevIdxOrBcId = usDevIdxOrBcId;
    pstSpiDimmingBaseWriteCmd->usSpiStartAddr = usSpiStartAddr;
    pstSpiDimmingBaseWriteCmd->usSpiWriteByteNum = usSpiWriteByteNum;
    pstSpiDimmingBaseWriteCmd->pucWriteBuffer = pucTmpWriteBuffer;
    pstSpiDimmingBaseWriteCmd->bBypassUpdSyncAsCS = bBypassUpdSyncAsCS;
    pstSpiDimmingBaseWriteCmd->usPwmAllZoneValue = usPwmAllZoneValue;
    g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd.ucSubCmdType = _SPI_DIMMING_BASE_WRITE;

    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_SPI_DIMMING, _SCALER_CPU_SYNC_TIMEOUT_COLOR_SPI_DIMMING, &unCpuSyncToScpuCmdReplyBody);
    return unCpuSyncToScpuCmdReplyBody.stCpuSyncSpiDimmingCmdReply.bExecuteStatus;
}

//--------------------------------------------------
// Description  : Scaler Debug Read PWM from Led Device (KCPU notify SCPU to execute)
// Input Value  : ucDevIndex  --> Led Device Index(0~31)
//                usPwmStartIndex --> Start Index Of Pwm Value(0~15)
//                usPwmReadNum --> Pwm Value Read Number(1~16)
//                pusPwmValue --> PWM Read Buffer
// Output Value : execute Status(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerSpiDimmingSyncDebugReadMcuPwm(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmReadNum, WORD *pusPwmValue)
{
    StructCpuSyncSpiDimmingRWPwmCmd *pstSpiDimmingReadPwmCmd = &g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd.unSubCmdBody.stRWPwmCmd;
    pstSpiDimmingReadPwmCmd->ucDevIndex = ucDevIndex;
    pstSpiDimmingReadPwmCmd->usPwmStartIndex = usPwmStartIndex;
    pstSpiDimmingReadPwmCmd->usPwmNum = usPwmReadNum;

    g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd.ucSubCmdType = _SPI_DIMMING_READ_PWM;

    UnionCpuSyncReplyCmdBody unCpuSyncToScpuCmdReplyBody = {0};
    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_SPI_DIMMING, _SCALER_CPU_SYNC_TIMEOUT_COLOR_SPI_DIMMING, &unCpuSyncToScpuCmdReplyBody);

    for(WORD usIdx = 0; usIdx < usPwmReadNum; usIdx++)
    {
        pusPwmValue[usIdx] = ((((WORD)g_pucSpiDimmingMemBuf[((usIdx * 2) + 1)]) << 8) + g_pucSpiDimmingMemBuf[(usIdx * 2)]);
    }

    return unCpuSyncToScpuCmdReplyBody.stCpuSyncSpiDimmingCmdReply.bExecuteStatus;
}

//--------------------------------------------------
// Description  : Scaler Debug Write PWM to Led Device (KCPU notify SCPU to execute)
// Input Value  : ucDevIndex  --> Led Device Index(0~31)
//                usPwmStartIndex --> Start Index Of Pwm Value(0~15)
//                usPwmWriteNum --> Pwm Value Write Number(1~16)
//                pusPwmValue --> PWM Write Buffer
// Output Value : execute Status(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerSpiDimmingSyncDebugWriteMcuPwm(BYTE ucDevIndex, WORD usPwmStartIndex, WORD usPwmWriteNum, WORD *pusPwmValue)
{
    StructCpuSyncSpiDimmingRWPwmCmd *pstSpiDimmingWritePwmCmd = &g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd.unSubCmdBody.stRWPwmCmd;
    pstSpiDimmingWritePwmCmd->ucDevIndex = ucDevIndex;
    pstSpiDimmingWritePwmCmd->usPwmStartIndex = usPwmStartIndex;
    pstSpiDimmingWritePwmCmd->usPwmNum = usPwmWriteNum;

    for(WORD usIdx = 0; usIdx < usPwmWriteNum; usIdx++)
    {
        g_pucSpiDimmingMemBuf[(usIdx * 2)] = LOBYTE(pusPwmValue[usIdx]);
        g_pucSpiDimmingMemBuf[((usIdx * 2) + 1)] = HIBYTE(pusPwmValue[usIdx]);
    }

    g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncSpiDimmingCmd.ucSubCmdType = _SPI_DIMMING_WRITE_PWM;

    UnionCpuSyncReplyCmdBody unCpuSyncToScpuCmdReplyBody = {0};
    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_SPI_DIMMING, _SCALER_CPU_SYNC_TIMEOUT_COLOR_SPI_DIMMING, &unCpuSyncToScpuCmdReplyBody);

    return unCpuSyncToScpuCmdReplyBody.stCpuSyncSpiDimmingCmdReply.bExecuteStatus;
}
#endif

#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
//--------------------------------------------------
// Description  : Scpu Spi Dimming Sync Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingScpuSyncHandler(void)
{
    StructCpuSyncSpiDimmingCmdReply *pstSpiDimmingCmdReply = &g_stCpuSyncToScpuCmdReply.unCmdBody.stCpuSyncSpiDimmingCmdReply;

    switch(g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncSpiDimmingCmd.ucSubCmdType)
    {
        case _SPI_DIMMING_INIT:
            pstSpiDimmingCmdReply->bExecuteStatus = ScalerSpiDimmingScpuSyncInit();
            break;

        case _SPI_DIMMING_BASE_WRITE:
            pstSpiDimmingCmdReply->bExecuteStatus = ScalerSpiDimmingScpuSyncBaseWrite();
            break;
        case _SPI_DIMMING_MEMCPY:
            pstSpiDimmingCmdReply->bExecuteStatus = ScalerSpiDimmingScpuSyncMemcpy();
            break;
        case _SPI_DIMMING_READ_PWM:
            pstSpiDimmingCmdReply->bExecuteStatus = ScalerSpiDimmingScpuSyncReadMcuPwm();
            break;
        case _SPI_DIMMING_WRITE_PWM:
            pstSpiDimmingCmdReply->bExecuteStatus = ScalerSpiDimmingScpuSyncWriteMcuPwm();
            break;
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Scpu Spi Dimming Sync Init Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSpiDimmingScpuSyncInit(void)
{
    ScalerSpiDimmingInit();
    return _TRUE;
}

//--------------------------------------------------
// Description  : Scpu Spi Dimming Sync Base Write Handler
// Input Value  : None
// Output Value : Execute Status
//--------------------------------------------------
bit ScalerSpiDimmingScpuSyncBaseWrite(void)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(ScalerColorLDPwmToSpiCheckSramModeEnable() == _TRUE)
    {
        if(ScalerColorLDPwmToSpiWaitToIdle() == _FALSE)
        {
            DebugMessageHDR("ScpuSyncBaseWrite fail to set FW SPI", 0);
            return _FALSE;
        }
    }
#endif

    StructCpuSyncSpiDimmingBaseWriteCmd *pstBaseWrtCmd = &g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncSpiDimmingCmd.unSubCmdBody.stBaseWriteCmd;

    return ScalerSpiDimmingBaseWrite(
        (EnumPwmToSpiInterface)(pstBaseWrtCmd->usPwmToSpiInterface),
        pstBaseWrtCmd->bUseDevIndex,
        pstBaseWrtCmd->usDevIdxOrBcId,
        pstBaseWrtCmd->usSpiStartAddr,
        pstBaseWrtCmd->usSpiWriteByteNum,
        pstBaseWrtCmd->pucWriteBuffer,
        pstBaseWrtCmd->bBypassUpdSyncAsCS,
        pstBaseWrtCmd->usPwmAllZoneValue);
}

//--------------------------------------------------
// Description  : Scpu Spi Dimming Sync Memcpy Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSpiDimmingScpuSyncMemcpy(void)
{
    StructCpuSyncSpiDimmingMemcpyCmd *pstMemcpyCmd = &g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncSpiDimmingCmd.unSubCmdBody.stMemcpyCmd;
    WORD usWriteOffset = pstMemcpyCmd->usWriteOffset;
    WORD usWriteByteLength = pstMemcpyCmd->usWriteByteLength;
    BYTE *pucDdrBufOffset = (BYTE *)&g_pucSpiDimmingDdrMemBuf[usWriteOffset];
    WORD usIdx = 0;
    while(usIdx < usWriteByteLength)
    {
        pucDdrBufOffset[usIdx] = g_pucSpiDimmingMemBuf[usIdx];
        usIdx++;
    }
    g_stCpuSyncToScpuCmdReply.unCmdBody.stCpuSyncSpiDimmingCmdReply.ulMemAddress = (DWORD)g_pucSpiDimmingDdrMemBuf;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Scpu Spi Dimming Sync Read PWM Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSpiDimmingScpuSyncReadMcuPwm(void)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(ScalerColorLDPwmToSpiCheckSramModeEnable() == _TRUE)
    {
        if(ScalerColorLDPwmToSpiWaitToIdle() == _FALSE)
        {
            DebugMessageHDR("ScpuSyncReadMcuPwm fail to set FW SPI", 0);
            return _FALSE;
        }
    }
#endif
    WORD pusPwmValue[(32 / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE)];
    StructCpuSyncSpiDimmingRWPwmCmd *pstReadPwmCmd = &g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncSpiDimmingCmd.unSubCmdBody.stRWPwmCmd;

    bit bExecuteStatus = ScalerSpiDimmingDebugReadPWM(
        pstReadPwmCmd->ucDevIndex,
        pstReadPwmCmd->usPwmStartIndex,
        pstReadPwmCmd->usPwmNum,
        pusPwmValue);

    for(WORD usIdx = 0; usIdx < pstReadPwmCmd->usPwmNum; usIdx++)
    {
        g_pucSpiDimmingMemBuf[(usIdx * 2)] = LOBYTE(pusPwmValue[usIdx]);
        g_pucSpiDimmingMemBuf[((usIdx * 2) + 1)] = HIBYTE(pusPwmValue[usIdx]);
    }

    return bExecuteStatus;
}

//--------------------------------------------------
// Description  : Scpu Spi Dimming Sync Write PWM Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSpiDimmingScpuSyncWriteMcuPwm(void)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(ScalerColorLDPwmToSpiCheckSramModeEnable() == _TRUE)
    {
        if(ScalerColorLDPwmToSpiWaitToIdle() == _FALSE)
        {
            DebugMessageHDR("ScpuSyncWriteMcuPwm fail to set FW SPI", 0);
            return _FALSE;
        }
    }
#endif

    WORD pusPwmValue[(32 / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE)];
    StructCpuSyncSpiDimmingRWPwmCmd *pstWritePwmCmd = &g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncSpiDimmingCmd.unSubCmdBody.stRWPwmCmd;

    for(WORD usIdx = 0; usIdx < pstWritePwmCmd->usPwmNum; usIdx++)
    {
        pusPwmValue[usIdx] = ((((WORD)g_pucSpiDimmingMemBuf[((usIdx * 2) + 1)]) << 8) + g_pucSpiDimmingMemBuf[(usIdx * 2)]);
    }

    bit bStus = ScalerSpiDimmingDebugWritePWM(
        pstWritePwmCmd->ucDevIndex,
        pstWritePwmCmd->usPwmStartIndex,
        pstWritePwmCmd->usPwmNum,
        pusPwmValue);

    if(bStus == _TRUE)
    {
        ScalerMcuDelayXus(150);
        ScalerSpiDimmingToggleUpdateSync();
    }

    return bStus;
}
#endif
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)
//--------------------------------------------------
// Description  : Init Pwm2Spi Sram New Mode UpdSync SPI Command's SRAM Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDSramModeUpdSyncUseSpiInit(void)
{
    // Init UpdSync via SPI Command Buffer
    BYTE pucSpiUpdSyncCmdArray[_MAX_SRAM_SPI_UPDSYNC_CMD_SIZE];

    // CmdEntry0
    WORD usSpiDataByteIdx = ExternalDeviceInterfaceLedUpdateSyncbySpiCE(&pucSpiUpdSyncCmdArray[0]);
    ScalerColorLDPwmToSpiSetCmdEntryDataRange(0, 0, usSpiDataByteIdx);
    ScalerColorLDPwmToSpiSetCmdEntryDummyByteNum(0, _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM);
    // CmdEntry1
    WORD usSpiDataByteCnt = ExternalDeviceInterfaceLedUpdateSyncbySpiVS(&pucSpiUpdSyncCmdArray[usSpiDataByteIdx]);
    ScalerColorLDPwmToSpiSetCmdEntryDataRange(1, usSpiDataByteIdx, usSpiDataByteCnt);
    ScalerColorLDPwmToSpiSetCmdEntryDummyByteNum(1, _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM);
    usSpiDataByteIdx += usSpiDataByteCnt;

#if(_VALID_BY_SPI_USE_CMD_ENTRY_NUM == 4)
    // CmdEntry2
    usSpiDataByteCnt = ExternalDeviceInterfaceLedUpdateSyncbySpiCE(&pucSpiUpdSyncCmdArray[usSpiDataByteIdx]);
    ScalerColorLDPwmToSpiSetCmdEntryDataRange(2, usSpiDataByteIdx, usSpiDataByteCnt);
    usSpiDataByteIdx += usSpiDataByteCnt;
    ScalerColorLDPwmToSpiSetCmdEntryDummyByteNum(2, _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM);
    // CmdEntry3
    usSpiDataByteCnt = ExternalDeviceInterfaceLedUpdateSyncbySpiVS(&pucSpiUpdSyncCmdArray[usSpiDataByteIdx]);
    ScalerColorLDPwmToSpiSetCmdEntryDataRange(3, usSpiDataByteIdx, usSpiDataByteCnt);
    usSpiDataByteIdx += usSpiDataByteCnt;
    ScalerColorLDPwmToSpiSetCmdEntryDummyByteNum(3, _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM);
#endif
    // align SMODE_UPDSYNC_USE_SPI Buffer to 4
    g_usSpiDimmingSpiDataByteStartOffset = (((usSpiDataByteIdx + 3) / 4) * 4);
    // Copy SMODE_UPDSYNC_USE_SPI Buffer to SRAM reg
    for(WORD usTmpIdx = 0; usTmpIdx < g_usSpiDimmingSpiDataByteStartOffset; usTmpIdx += 4)
    {
        Scaler32SetDWord((PB0053B_00_PWM2SPI_SPI_DATA + usTmpIdx), ((DWORD *)&pucSpiUpdSyncCmdArray[usTmpIdx])[0]);
    }
}
#endif  // End of #if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)


//--------------------------------------------------
// Description  : Update LD Pwm Buffer
// Input Value  : pusPwmTargetBuf --> New Pwm Target Buffer
//                pusPwmPrevTargetBuf --> Previous Pwm Target Buffer
//                pusPwmAdjustCurve --> Pwm Adjust Curve for PWM Multiple-Update in one Frame(0 ~ 256, 256 means 100%)
//                bPwm2SpiTxNow --> Transmit SPI immediately
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDUpdateSramModeData(WORD *pusPwmTargetBuf, WORD *pusPwmPrevTargetBuf, WORD *pusPwmAdjustCurve, bit bPwm2SpiTxNow)
{
    if(g_stSpiDimmingPwmToSpiInfo.ulDclkValue != GET_D_CLK_FREQ())
    {
        g_stSpiDimmingPwmToSpiInfo.ulDclkValue = GET_D_CLK_FREQ();
        ScalerColorLDPwmToSpiSetSyncPulseWidth(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS);
    }
#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE)
    ScalerSpiDimmingLDUpdateSramModeDataUseDdr(pusPwmTargetBuf, pusPwmPrevTargetBuf, pusPwmAdjustCurve);

    if(bPwm2SpiTxNow == _TRUE)
    {
        ScalerSpiDimmingLDSramModeTxNow();
    }
#else
    pusPwmTargetBuf = pusPwmTargetBuf;
    pusPwmPrevTargetBuf = pusPwmPrevTargetBuf;
    pusPwmAdjustCurve = pusPwmAdjustCurve;
    bPwm2SpiTxNow = bPwm2SpiTxNow;
#endif
#else
    // multi-update sram partition Design
    ScalerSpiDimmingLDUpdateSramModeDataUseSram(pusPwmTargetBuf, pusPwmPrevTargetBuf, pusPwmAdjustCurve);

    if(bPwm2SpiTxNow == _TRUE)
    {
        ScalerSpiDimmingLDSramModeTxNow();
    }
#endif
}

//--------------------------------------------------
// Description  : SRAM Mode SPI TX Now
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDSramModeTxNow(void)
{
    g_bSpiDimmingSramModeTxDoneFlag = _FALSE;
    g_ucSpiDimmingMultiUpdateIdx = 0;
    g_ucSpiDimmingTxTimeIdx = 0;
#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
    g_bSpiDimmingSRamAdimMode = _FALSE;
#endif
    g_bSpiDimmingSramModeStartTxResult = ScalerSpiDimmingLDSramModeStartTX();
}

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Old Mode Update LD A-Dimming Data
// Input Value  : pusColorApplyADim --> ADim Target Buffer
//                bPwm2SpiTxNow --> Transmit SPI immediately
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDUpdateSramADimData(WORD *pusColorApplyADim, bit bPwm2SpiTxNow)
{
#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE)
    ScalerSpiDimmingLDUpdateSramADimDataUseDdr(pusColorApplyADim);
#else
    pusColorApplyADim = pusColorApplyADim;
#endif
#else
    ScalerSpiDimmingLDUpdateSramADimDataUseSram(pusColorApplyADim);
#endif

    if(bPwm2SpiTxNow == _TRUE)
    {
        ScalerSpiDimmingLDSramModeADimTxNow();
    }
}

//--------------------------------------------------
// Description  : SRAM Mode SPI TX Now
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDSramModeADimTxNow(void)
{
    g_bSpiDimmingSramModeTxDoneFlag = _FALSE;
    g_ucSpiDimmingMultiUpdateIdx = 0;
    g_ucSpiDimmingTxTimeIdx = 0;
    g_bSpiDimmingSRamAdimMode = _TRUE;
    g_bSpiDimmingSramModeStartTxResult = ScalerSpiDimmingLDSramModeStartTX();
}
#endif

#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE)
//--------------------------------------------------
// Description  : ScalerSpiDimming Init Buffer by using DDR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingInitUseDdr(void)
{
    WORD usSpiDataByteCnt = 0;
    WORD usSpiDataByteIdx = 0;
    WORD usSpiDevIdxAcc = 0;
    BYTE ucCmdEntryOffset = 0;
    BYTE *pucSpiDataByteArray = _NULL_POINTER;
    BYTE *pucSpiDummyByteArray = _NULL_POINTER;
    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    EnumPwmToSpiInterface penumPwmToSpiInterface[3] = {_PWMTOSPI_INTERFACE_0, _PWMTOSPI_INTERFACE_1, _PWMTOSPI_INTERFACE_2};

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
    WORD usSpiADimByteCnt = 0;
    WORD usSpiADimByteIdx = 0;
#endif

    // repeat use PWM2SPI sram for high zone LD
    DWORD ulLastDummyRegValue = 0;

    for(WORD usTxTimeIdx = 0; usTxTimeIdx < _MAX_PWM2SPI_SMODE_REUSE_TIMES; usTxTimeIdx++)
    {
        WORD usSpiDataByteIdxOffset = 0;

        usSpiDataByteIdx = 0;
        pucSpiDataByteArray = (BYTE *)(&g_ppstSpiDimmingSRamBuf[0][usTxTimeIdx].pucSpiSRamBuf[0]);
#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
        usSpiADimByteIdx = 0;
        BYTE *pucSpiADimByteArray = (BYTE *)(&g_pstSpiDimmingADimSRamBuf[usTxTimeIdx].pucSpiSRamBuf[0]);
#endif
        // ping-pong Buffer Design
        if(usTxTimeIdx & _BIT0)
        {
            usSpiDataByteIdxOffset = g_usSpiDimmingSpiDataByteStartOffset + (_MAX_SPI_ONCE_TX_BUF_SIZE * _USE_SPI_INTERFACE_NUM);
            ucCmdEntryOffset = _VALID_BY_SPI_USE_CMD_ENTRY_NUM + (_MAX_SPI_ONCE_TX_CMD_NUM * _USE_SPI_INTERFACE_NUM);
            g_pstSpiDimmingCmdEntryDummyBytes[usTxTimeIdx].pulSpiCmdEntryDummyBytes[0] = ulLastDummyRegValue;
            pucSpiDummyByteArray = &((BYTE *)(&g_pstSpiDimmingCmdEntryDummyBytes[usTxTimeIdx].pulSpiCmdEntryDummyBytes[0]))[(ucCmdEntryOffset % 4)];
        }
        else
        {
            usSpiDataByteIdxOffset = g_usSpiDimmingSpiDataByteStartOffset;
            ucCmdEntryOffset = _VALID_BY_SPI_USE_CMD_ENTRY_NUM;
            g_pstSpiDimmingCmdEntryDummyBytes[usTxTimeIdx].pulSpiCmdEntryDummyBytes[0] = ((_LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM << 24) | (_LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM << 16) | (_LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM << 8) | (_LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM << 0));
            pucSpiDummyByteArray = &((BYTE *)(&g_pstSpiDimmingCmdEntryDummyBytes[usTxTimeIdx].pulSpiCmdEntryDummyBytes[(_VALID_BY_SPI_USE_CMD_ENTRY_NUM / 4)]))[(ucCmdEntryOffset % 4)];
        }

        WORD usIdx = 0;  // as CmdEntry Index

        for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
        {
            WORD usUseCmdEntryNum = 0;

            WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];
            EnumPwmToSpiInterface enumPwmToSpiInterface = penumPwmToSpiInterface[ucSpiInterfaceIdx];

            for(WORD usSpiDevIdx = 0; usSpiDevIdx < usSpiXDevNum; usSpiDevIdx++)
            {
                if(usIdx < (_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
                {
                    if((usSpiDevIdxAcc < GET_TABLE_ELEMENT_NUM(tLedSpiPwmStartAddr)) && (usSpiDevIdxAcc < GET_TABLE_ELEMENT_NUM(tLDPwmToSpiDataByteNum)))
                    {
                        usSpiDataByteCnt = ScalerSpiDimmingFormatWriteCmdBuffer(enumPwmToSpiInterface, _TRUE, usSpiDevIdx, tLedSpiPwmStartAddr[usSpiDevIdxAcc], _NULL_POINTER, tLDPwmToSpiDataByteNum[usSpiDevIdxAcc], &pucSpiDataByteArray[usSpiDataByteIdx], 0, _FALSE, 0);
                    }
                    else
                    {
                        if(usSpiDevIdxAcc >= GET_TABLE_ELEMENT_NUM(tLedSpiPwmStartAddr))
                        {
                            DebugMessageHDR("tLedSpiPwmStartAddr access overrun!!", usSpiDevIdxAcc);
                        }
                        if(usSpiDevIdxAcc >= GET_TABLE_ELEMENT_NUM(tLDPwmToSpiDataByteNum))
                        {
                            DebugMessageHDR("tLDPwmToSpiDataByteNum access overrun!!", usSpiDevIdxAcc);
                        }
                    }
                    g_pstSpiDimmingCmdEntryData[usTxTimeIdx].pulSpiCmdEntryData[usIdx] = ((((DWORD)usSpiDataByteCnt) << 16) + (usSpiDataByteIdx + usSpiDataByteIdxOffset));

                    usSpiDataByteIdx += usSpiDataByteCnt;

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
                    usSpiADimByteCnt = ScalerSpiDimmingFormatWriteCmdBuffer(enumPwmToSpiInterface, _TRUE, usSpiDevIdx, _DEVICE_LED_DRIVER_ADIM_ADDR, _NULL_POINTER, (_DEVICE_LED_DRIVER_ADIM_WIDTH_BY_BYTE * (tLDPwmToSpiDataByteNum[usSpiDevIdxAcc] / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE)), &pucSpiADimByteArray[usSpiADimByteIdx], 0, _FALSE, 0);

                    g_pstSpiDimmingADimCmdEntryData[usTxTimeIdx].pulSpiCmdEntryData[usIdx] = ((((DWORD)usSpiADimByteCnt) << 16) + (usSpiADimByteIdx + usSpiDataByteIdxOffset));

                    usSpiADimByteIdx += usSpiADimByteCnt;
#endif
                    if(usSpiDevIdxAcc < GET_TABLE_ELEMENT_NUM(tLDPwmToSpiDummyByteNum))
                    {
                        pucSpiDummyByteArray[usIdx] = tLDPwmToSpiDummyByteNum[usSpiDevIdxAcc];
                    }
                    else
                    {
                        DebugMessageHDR("tLDPwmToSpiDummyByteNum access overrun!!", usSpiDevIdxAcc);
                    }
                    usSpiDevIdxAcc++;
                    usUseCmdEntryNum++;
                    usIdx++;
                }
                else
                {
                    break;
                }
            }
            g_ppulSpiDimmingCmdEntryCfg[usTxTimeIdx][ucSpiInterfaceIdx] = GEN_SPI_CMD_ENTRY_CFG(ucCmdEntryOffset, usUseCmdEntryNum);
            ucCmdEntryOffset += usUseCmdEntryNum;
        }
        if((usTxTimeIdx & _BIT0) == 0)
        {
            // keep overlap DummyByte Reg Setting(for FW ping-pong Buffer design)
            ulLastDummyRegValue = g_pstSpiDimmingCmdEntryDummyBytes[usTxTimeIdx].pulSpiCmdEntryDummyBytes[(((((DWORD)ucCmdEntryOffset) % 4) + usIdx) / 4)];
        }

        g_pusSpiDimmingSRamTotalCmdNum[usTxTimeIdx] = ((usSpiDataByteIdx + 3) / 4);
#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
        g_pusSpiDimmingADimSRamTotalCmdNum[usTxTimeIdx] = ((usSpiADimByteIdx + 3) / 4);
#endif
    }

    // duplicate TX Buffer for Multi-time Update in one frame
    for(WORD usTmpIdx = 1; usTmpIdx < _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME; usTmpIdx++)
    {
        for(WORD usTxTimeIdx = 0; usTxTimeIdx < _MAX_PWM2SPI_SMODE_REUSE_TIMES; usTxTimeIdx++)
        {
            memcpy((&g_ppstSpiDimmingSRamBuf[usTmpIdx][usTxTimeIdx]), (&g_ppstSpiDimmingSRamBuf[0][usTxTimeIdx]), sizeof(StructSpiSRamBuf));
        }
    }
}

//--------------------------------------------------
// Description  : Update LD Pwm Buffer to DDR
// Input Value  : pusPwmTargetBuf --> New Pwm Target Buffer
//                pusPwmPrevTargetBuf --> Previous Pwm Target Buffer
//                pusPwmAdjustCurve --> Pwm Adjust Curve for PWM Multiple-Update in one Frame(0 ~ 256, 256 means 100%)
//                bPwm2SpiTxNow --> Transmit SPI immediately
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDUpdateSramModeDataUseDdr(WORD *pusPwmTargetBuf, WORD *pusPwmPrevTargetBuf, WORD *pusPwmAdjustCurve)
{
    WORD usIdx = 0;
    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    WORD *ppusLDPwmToSpiRemapTable[3] = {tLDPwmToSpiRemapTable0, tLDPwmToSpiRemapTable1, tLDPwmToSpiRemapTable2};
    WORD usSpiPwmDataOffsetIdx = 0;
    // repeat use PWM2SPI sram for high zone LD


#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
    WORD ppusPwmDataOffset[_USE_SPI_INTERFACE_NUM][_MAX_SPI_DEV_NUM] = {0};
#endif

    for(BYTE ucTxTimeIdx = 0; ucTxTimeIdx < _MAX_PWM2SPI_SMODE_REUSE_TIMES; ucTxTimeIdx++)
    {
        for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
        {
            WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];

            if(usSpiXDevNum != 0)
            {
                WORD usRemapTableIdx = 0;
                WORD *pusLDPwmToSpiRemapTable = ppusLDPwmToSpiRemapTable[ucSpiInterfaceIdx];

                for(WORD usSpiXDevIdx = 0; usSpiXDevIdx < usSpiXDevNum; usSpiXDevIdx++)
                {
                    if(usIdx < ((WORD)_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
                    {
                        WORD usDevDataByteNumber = (WORD)(g_pstSpiDimmingCmdEntryData[ucTxTimeIdx].pulSpiCmdEntryData[usIdx] >> 16);

                        WORD usSpiDataByteIdx = _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES;
                        WORD usDevPwmDataByteNumber = usDevDataByteNumber - _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM;
#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
                        ppusPwmDataOffset[ucSpiInterfaceIdx][usSpiXDevIdx] = usSpiPwmDataOffsetIdx;
#endif
                        while(usSpiDataByteIdx < usDevPwmDataByteNumber)
                        {
                            // convert data bytes to pwm number
                            WORD usRemapIdx = pusLDPwmToSpiRemapTable[usRemapTableIdx];

                            SDWORD lCvtCurrPwmValue = (SDWORD)ExternalDeviceInterfaceLedConvertPwmToSpiFormat(pusPwmTargetBuf[usRemapIdx]);
                            SDWORD lCvtPrevPwmValue = (SDWORD)ExternalDeviceInterfaceLedConvertPwmToSpiFormat(pusPwmPrevTargetBuf[usRemapIdx]);
                            SDWORD lPwmDiffValue = lCvtCurrPwmValue - lCvtPrevPwmValue;


                            for(BYTE ucUpdTimesIdx = 0; ucUpdTimesIdx < _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME; ucUpdTimesIdx++)
                            {
                                WORD usUpdPwmValue = (WORD)(lCvtPrevPwmValue + ((lPwmDiffValue *  pusPwmAdjustCurve[ucUpdTimesIdx]) >> 8));

                                BYTE *pucSpiXPwmData = (BYTE *)(&g_ppstSpiDimmingSRamBuf[ucUpdTimesIdx][ucTxTimeIdx].pucSpiSRamBuf[usSpiPwmDataOffsetIdx]);

#if(_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE == 1)
                                pucSpiXPwmData[usSpiDataByteIdx] = LOBYTE(usUpdPwmValue);
#else
#if(_LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP == _ON)
                                pucSpiXPwmData[usSpiDataByteIdx] = HIBYTE(usUpdPwmValue);
                                pucSpiXPwmData[(usSpiDataByteIdx + 1)] = LOBYTE(usUpdPwmValue);
#else
                                pucSpiXPwmData[usSpiDataByteIdx] = LOBYTE(usUpdPwmValue);
                                pucSpiXPwmData[(usSpiDataByteIdx + 1)] = HIBYTE(usUpdPwmValue);
#endif
#endif
                            }
#if(_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE == 1)
                            usSpiDataByteIdx++;
#else
                            usSpiDataByteIdx += 2;
#endif
                            usRemapTableIdx++;
                        }
                        usSpiPwmDataOffsetIdx += usDevDataByteNumber;

                        usIdx++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
        usIdx = 0;
        for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
        {
            WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];

            if(usSpiXDevNum != 0)
            {
                for(WORD usSpiXDevIdx = 0; usSpiXDevIdx < usSpiXDevNum; usSpiXDevIdx++)
                {
                    if(usIdx < ((WORD)_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
                    {
                        WORD usDevDataByteNumber = (WORD)(g_pstSpiDimmingCmdEntryData[ucTxTimeIdx].pulSpiCmdEntryData[usIdx] >> 16);

                        for(BYTE ucUpdTimesIdx = 0; ucUpdTimesIdx < _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME; ucUpdTimesIdx++)
                        {
                            BYTE *pucSpiXPwmData = (BYTE *)(&g_ppstSpiDimmingSRamBuf[ucUpdTimesIdx][ucTxTimeIdx].pucSpiSRamBuf[(ppusPwmDataOffset[ucSpiInterfaceIdx][usSpiXDevIdx])]);

                            ExternalDeviceInterfaceLedDriverCalcChecksum(pucSpiXPwmData, usDevDataByteNumber);
                        }

                        usIdx++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
#endif
    }
}

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Old Mode Update LD A-Dimming Data Use DDR
// Input Value  : pusColorApplyADim --> ADim Target Buffer
//                bPwm2SpiTxNow --> Transmit SPI immediately
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDUpdateSramADimDataUseDdr(WORD *pusColorApplyADim)
{
    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    WORD *ppusLDPwmToSpiRemapTable[3] = {tLDPwmToSpiRemapTable0, tLDPwmToSpiRemapTable1, tLDPwmToSpiRemapTable2};

    WORD usIdx = 0;
    WORD usSpiPwmDataOffsetIdx = 0;
    WORD ppusPwmDataOffset[_USE_SPI_INTERFACE_NUM][_MAX_SPI_DEV_NUM] = {0};

    for(BYTE ucTxTimeIdx = 0; ucTxTimeIdx < _MAX_PWM2SPI_SMODE_REUSE_TIMES; ucTxTimeIdx++)
    {
        for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
        {
            WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];

            if(usSpiXDevNum != 0)
            {
                WORD usRemapTableIdx = 0;
                WORD *pusLDPwmToSpiRemapTable = ppusLDPwmToSpiRemapTable[ucSpiInterfaceIdx];

                for(WORD usSpiXDevIdx = 0; usSpiXDevIdx < usSpiXDevNum; usSpiXDevIdx++)
                {
                    if(usIdx < ((WORD)_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
                    {
                        WORD usDevADimByteNumber = (WORD)(g_pstSpiDimmingADimCmdEntryData[ucTxTimeIdx].pulSpiCmdEntryData[usIdx] >> 16);

                        WORD usSpiDataByteIdx = _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES;

                        WORD usDevADimDataByteNumber = usDevADimByteNumber - _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM;
                        ppusPwmDataOffset[ucSpiInterfaceIdx][usSpiXDevIdx] = usSpiPwmDataOffsetIdx;
                        while(usSpiDataByteIdx < usDevADimDataByteNumber)
                        {
                            // convert data bytes to pwm number
                            WORD usRemapIdx = pusLDPwmToSpiRemapTable[usRemapTableIdx];

                            WORD usCvtADimValue = ExternalDeviceInterfaceLedConvertADimFormat(pusColorApplyADim[usRemapIdx]);

                            BYTE *pucSpiXADimData = (BYTE *)(&g_pstSpiDimmingADimSRamBuf[ucTxTimeIdx].pucSpiSRamBuf[usSpiPwmDataOffsetIdx]);

#if(_DEVICE_LED_DRIVER_ADIM_WIDTH_BY_BYTE == 1)
                            pucSpiXADimData[usSpiDataByteIdx] = LOBYTE(usCvtADimValue);
#else
#if(_DEVICE_LED_DRIVER_ADIM_BYTE_SWAP == _ON)
                            pucSpiXADimData[usSpiDataByteIdx] = HIBYTE(usCvtADimValue);
                            pucSpiXADimData[(usSpiDataByteIdx + 1)] = LOBYTE(usCvtADimValue);
#else
                            pucSpiXADimData[usSpiDataByteIdx] = LOBYTE(usCvtADimValue);
                            pucSpiXADimData[(usSpiDataByteIdx + 1)] = HIBYTE(usCvtADimValue);
#endif
#endif
#if(_DEVICE_LED_DRIVER_ADIM_WIDTH_BY_BYTE == 1)
                            usSpiDataByteIdx++;
#else
                            usSpiDataByteIdx += 2;
#endif
                            usRemapTableIdx++;
                        }
                        usSpiPwmDataOffsetIdx += usDevADimByteNumber;

                        usIdx++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
        usIdx = 0;
        for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
        {
            WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];

            if(usSpiXDevNum != 0)
            {
                for(WORD usSpiXDevIdx = 0; usSpiXDevIdx < usSpiXDevNum; usSpiXDevIdx++)
                {
                    if(usIdx < ((WORD)_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
                    {
                        WORD usDevADimByteNumber = (WORD)(g_pstSpiDimmingADimCmdEntryData[ucTxTimeIdx].pulSpiCmdEntryData[usIdx] >> 16);

                        BYTE *pucSpiXADimData = (BYTE *)(&g_pstSpiDimmingADimSRamBuf[ucTxTimeIdx].pucSpiSRamBuf[(ppusPwmDataOffset[ucSpiInterfaceIdx][usSpiXDevIdx])]);
                        ExternalDeviceInterfaceLedDriverCalcChecksum(pucSpiXADimData, usDevADimByteNumber);

                        usIdx++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
#endif
    }
}
#endif
//--------------------------------------------------
// Description  : SRAM Mode SPI TX done CallBack function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDSramModeInitBW32CmdInfo(StructBW32CmdInfo *pstBW32CmdInfo)
{
    WORD usSpiDataByteIdxOffset = g_usSpiDimmingSpiDataByteStartOffset;
    WORD usSpi0CmdEntryStartIdx = g_ppulSpiDimmingCmdEntryCfg[g_ucSpiDimmingTxTimeIdx][0] & 0x0000FFFF;
    WORD usSpiCmdEntryNum = 0;
    BYTE ucSpiInterfaceIdx = 0;
    while(ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM)
    {
        usSpiCmdEntryNum += ((g_ppulSpiDimmingCmdEntryCfg[g_ucSpiDimmingTxTimeIdx][ucSpiInterfaceIdx] >> 16) & 0x0000FFFF);
        ucSpiInterfaceIdx++;
    }

    if(g_ucSpiDimmingTxTimeIdx & _BIT0)
    {
        usSpiDataByteIdxOffset += (_MAX_SPI_ONCE_TX_BUF_SIZE * _USE_SPI_INTERFACE_NUM);
    }

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
    if(g_bSpiDimmingSRamAdimMode == _TRUE)
    {
        // A-Dimming
        // SRAM Buffer
        pstBW32CmdInfo[0].stBW32BaseInfo.enumBW32CmdFormat = _BW32_DATA_FORMAT;
        pstBW32CmdInfo[0].stBW32BaseInfo.ulDdrSrcAddr = (DWORD)(&g_pstSpiDimmingADimSRamBuf[g_ucSpiDimmingTxTimeIdx].pucSpiSRamBuf[0]);
        pstBW32CmdInfo[0].stBW32BaseInfo.ulDestRBusdRegAddr = PB0053B_00_PWM2SPI_SPI_DATA + usSpiDataByteIdxOffset;
        pstBW32CmdInfo[0].stBW32BaseInfo.ulTotalCmdNum = g_pusSpiDimmingADimSRamTotalCmdNum[g_ucSpiDimmingTxTimeIdx];
        pstBW32CmdInfo[0].stBW32BaseInfo.bAddrAutoInc = _TRUE;
        pstBW32CmdInfo[0].enumBW32TriggerSource = _BW32_TRIGGER_MANUAL;

        // Command Entry Table
        pstBW32CmdInfo[1].stBW32BaseInfo.enumBW32CmdFormat = _BW32_DATA_FORMAT;
        pstBW32CmdInfo[1].stBW32BaseInfo.ulDdrSrcAddr = (DWORD)(&g_pstSpiDimmingADimCmdEntryData[g_ucSpiDimmingTxTimeIdx]);
        pstBW32CmdInfo[1].stBW32BaseInfo.ulDestRBusdRegAddr = PB00539_00_PWM2SPI_NEW_CMD_ENTRY + (usSpi0CmdEntryStartIdx * 4);
        pstBW32CmdInfo[1].stBW32BaseInfo.ulTotalCmdNum = usSpiCmdEntryNum;
        pstBW32CmdInfo[1].stBW32BaseInfo.bAddrAutoInc = _TRUE;
        pstBW32CmdInfo[1].enumBW32TriggerSource = _BW32_TRIGGER_MANUAL;
    }
    else
#endif
    {
        // D-Dimming
        // SRAM Buffer
        pstBW32CmdInfo[0].stBW32BaseInfo.enumBW32CmdFormat = _BW32_DATA_FORMAT;
        pstBW32CmdInfo[0].stBW32BaseInfo.ulDdrSrcAddr = (DWORD)(&g_ppstSpiDimmingSRamBuf[g_ucSpiDimmingMultiUpdateIdx][g_ucSpiDimmingTxTimeIdx].pucSpiSRamBuf[0]);
        pstBW32CmdInfo[0].stBW32BaseInfo.ulDestRBusdRegAddr = PB0053B_00_PWM2SPI_SPI_DATA + usSpiDataByteIdxOffset;
        pstBW32CmdInfo[0].stBW32BaseInfo.ulTotalCmdNum = g_pusSpiDimmingSRamTotalCmdNum[g_ucSpiDimmingTxTimeIdx];
        pstBW32CmdInfo[0].stBW32BaseInfo.bAddrAutoInc = _TRUE;
        pstBW32CmdInfo[0].enumBW32TriggerSource = _BW32_TRIGGER_MANUAL;

        // Command Entry Table
        pstBW32CmdInfo[1].stBW32BaseInfo.enumBW32CmdFormat = _BW32_DATA_FORMAT;
        pstBW32CmdInfo[1].stBW32BaseInfo.ulDdrSrcAddr = (DWORD)(&g_pstSpiDimmingCmdEntryData[g_ucSpiDimmingTxTimeIdx]);
        pstBW32CmdInfo[1].stBW32BaseInfo.ulDestRBusdRegAddr = PB00539_00_PWM2SPI_NEW_CMD_ENTRY + (usSpi0CmdEntryStartIdx * 4);
        pstBW32CmdInfo[1].stBW32BaseInfo.ulTotalCmdNum = usSpiCmdEntryNum;
        pstBW32CmdInfo[1].stBW32BaseInfo.bAddrAutoInc = _TRUE;
        pstBW32CmdInfo[1].enumBW32TriggerSource = _BW32_TRIGGER_MANUAL;
    }
    // Command Entry Dummy Bytes Table
    pstBW32CmdInfo[2].stBW32BaseInfo.enumBW32CmdFormat = _BW32_DATA_FORMAT;
    pstBW32CmdInfo[2].stBW32BaseInfo.ulDdrSrcAddr = (DWORD)(&g_pstSpiDimmingCmdEntryDummyBytes[g_ucSpiDimmingTxTimeIdx]);
    pstBW32CmdInfo[2].stBW32BaseInfo.ulDestRBusdRegAddr = PB00538_30_SRAM_MODE_CMD_ENTRY_DUMMY_CFG0 + ((usSpi0CmdEntryStartIdx / 4) * 4);
    pstBW32CmdInfo[2].stBW32BaseInfo.ulTotalCmdNum = ((usSpiCmdEntryNum + 3) / 4);
    pstBW32CmdInfo[2].stBW32BaseInfo.bAddrAutoInc = _TRUE;
    pstBW32CmdInfo[2].enumBW32TriggerSource = _BW32_TRIGGER_MANUAL;
}

//--------------------------------------------------
// Description  : SRAM Mode Start SPI TX
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDSramModeSpiTx(void)
{
    g_bSpiDimmingSramModePendTxFlag = _FALSE;
#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM != 0)
    ScalerColorLDPwmToSpiSetCmdEntryConfig(_PWMTOSPI_INTERFACE_0, g_ppulSpiDimmingCmdEntryCfg[g_ucSpiDimmingTxTimeIdx][0]);
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
    ScalerColorLDPwmToSpiSetCmdEntryConfig(_PWMTOSPI_INTERFACE_1, g_ppulSpiDimmingCmdEntryCfg[g_ucSpiDimmingTxTimeIdx][1]);
#endif
#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
    ScalerColorLDPwmToSpiSetCmdEntryConfig(_PWMTOSPI_INTERFACE_2, g_ppulSpiDimmingCmdEntryCfg[g_ucSpiDimmingTxTimeIdx][2]);
#endif
    ScalerColorLDPwmToSpiStartTX();
}

//--------------------------------------------------
// Description  : SRAM Mode Check && Start Next BW32 fill job
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDSramModeNextBW32(void)
{
    if(g_ucSpiDimmingTxTimeIdx != (_MAX_PWM2SPI_SMODE_REUSE_TIMES - 1))
    {
        // LD Sram Mode Next run reuse Tx BW32 job
        g_ucSpiDimmingTxTimeIdx++;

        if(ScalerMcuCheckHwBW32Avaiable() == _TRUE)
        {
            g_bSpiDimmingSramModeStartTxResult = ScalerSpiDimmingLDSramModeStartTX();
        }
        else
        {
            g_bSpiDimmingSramModeStartTxResult = _FALSE;
        }
    }
}

//--------------------------------------------------
// Description  : SRAM Mode BW32 update SRAM Buffer done CallBack function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDSramModeBW32DoneCallBack(void)
{
    if((g_bSpiDimmingSramModeTxDoneFlag == _FALSE) && (ScalerColorLDPwmToSpiCheckSpiIsBusy() == _FALSE))
    {
        // SPI TX is idle(1st SPI TX)
        ScalerSpiDimmingLDSramModeSpiTx();
        // Check&&Start Next run BW32
        ScalerSpiDimmingLDSramModeNextBW32();
    }
    else
    {
        // SPI TX is busy now
        g_bSpiDimmingSramModePendTxFlag = _TRUE;
    }
}
#endif
#else
//--------------------------------------------------
// Description  : ScalerSpiDimming Init Buffer by using SRAM Reg
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingInitUseSram(void)
{
    WORD usSpiDataByteCnt = 0;
    WORD usSpiDataByteIdx = 0;
    WORD usSpiDevIdxAcc = 0;
    BYTE ucCmdEntryOffset = 0;
    BYTE *pucSpiDummyByteArray = _NULL_POINTER;
    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    EnumPwmToSpiInterface penumPwmToSpiInterface[3] = {_PWMTOSPI_INTERFACE_0, _PWMTOSPI_INTERFACE_1, _PWMTOSPI_INTERFACE_2};

    ucCmdEntryOffset = _VALID_BY_SPI_USE_CMD_ENTRY_NUM;
    for(WORD usUpdTimePerFrameIdx = 0; usUpdTimePerFrameIdx < _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME; usUpdTimePerFrameIdx++)
    {
        WORD usSpiDataByteArrayIdx = 0;
        WORD usSRamAddressOffset = (((WORD)sizeof(StructSpiSRamBuf)) * usUpdTimePerFrameIdx);
        BYTE pucSpiDataByteArray[sizeof(StructSpiSRamBuf)];

        if(usUpdTimePerFrameIdx == 0)
        {
            g_stSpiDimmingCmdEntryDummyBytes.pulSpiCmdEntryDummyBytes[0] = ((_LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM << 24) | (_LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM << 16) | (_LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM << 8) | (_LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM << 0));

            pucSpiDummyByteArray = &((BYTE *)(&g_stSpiDimmingCmdEntryDummyBytes.pulSpiCmdEntryDummyBytes[(_VALID_BY_SPI_USE_CMD_ENTRY_NUM / 4)]))[(ucCmdEntryOffset % 4)];
        }

        WORD usIdx = 0;  // as CmdEntry Index
        usSpiDevIdxAcc = 0;
        usSpiDataByteIdx = g_usSpiDimmingSpiDataByteStartOffset + usSRamAddressOffset;

        for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
        {
            WORD usUseCmdEntryNum = 0;
            WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];
            EnumPwmToSpiInterface enumPwmToSpiInterface = penumPwmToSpiInterface[ucSpiInterfaceIdx];

            for(WORD usSpiDevIdx = 0; usSpiDevIdx < usSpiXDevNum; usSpiDevIdx++)
            {
                if(usIdx < (_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
                {
                    usSpiDataByteCnt = ScalerSpiDimmingFormatWriteCmdBuffer(enumPwmToSpiInterface, _TRUE, usSpiDevIdx, tLedSpiPwmStartAddr[usSpiDevIdxAcc], _NULL_POINTER, tLDPwmToSpiDataByteNum[usSpiDevIdxAcc], &pucSpiDataByteArray[usSpiDataByteArrayIdx], 0, _FALSE, 0);

                    g_pstSpiDimmingCmdEntryData[usUpdTimePerFrameIdx].pulSpiCmdEntryData[usIdx] = ((((DWORD)usSpiDataByteCnt) << 16) + (usSpiDataByteIdx));

                    if(usUpdTimePerFrameIdx == 0)
                    {
                        pucSpiDummyByteArray[usIdx] = tLDPwmToSpiDummyByteNum[usSpiDevIdxAcc];
                    }
                    usSpiDataByteIdx += usSpiDataByteCnt;
                    usSpiDataByteArrayIdx += usSpiDataByteCnt;

                    usSpiDevIdxAcc++;
                    usUseCmdEntryNum++;
                    usIdx++;
                }
                else
                {
                    break;
                }
            }
            g_ppulSpiDimmingCmdEntryCfg[usUpdTimePerFrameIdx][ucSpiInterfaceIdx] = GEN_SPI_CMD_ENTRY_CFG(ucCmdEntryOffset, usUseCmdEntryNum);
            ucCmdEntryOffset += usUseCmdEntryNum;
        }
        // DataBytes align to 4 bytes
        usSpiDataByteArrayIdx = ((usSpiDataByteArrayIdx + 3) / 4) * 4;
        g_pusSpiDimmingUpdFrameTotalDataByte[usUpdTimePerFrameIdx] = usSpiDataByteArrayIdx;
        {
            DWORD ulTargetSRamBufRegAddr = PB0053B_00_PWM2SPI_SPI_DATA + g_usSpiDimmingSpiDataByteStartOffset + usSRamAddressOffset;

            for(WORD usTmpIdx = 0; usTmpIdx < usSpiDataByteArrayIdx; usTmpIdx += 4)
            {
                Scaler32SetDWord((ulTargetSRamBufRegAddr + usTmpIdx), ((DWORD *)&pucSpiDataByteArray[usTmpIdx])[0]);
            }
        }
    }

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
    ScalerSpiDimmingInitADimUseSram();
#endif
}

//--------------------------------------------------
// Description  : Update LD Pwm Buffer to SRAM Buffer
// Input Value  : pusPwmTargetBuf --> New Pwm Target Buffer
//                pusPwmPrevTargetBuf --> Previous Pwm Target Buffer
//                pusPwmAdjustCurve --> Pwm Adjust Curve for PWM Multiple-Update in one Frame(0 ~ 256, 256 means 100%)
//                bPwm2SpiTxNow --> Transmit SPI immediately
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDUpdateSramModeDataUseSram(WORD *pusPwmTargetBuf, WORD *pusPwmPrevTargetBuf, WORD *pusPwmAdjustCurve)
{
    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    WORD *ppusLDPwmToSpiRemapTable[3] = {tLDPwmToSpiRemapTable0, tLDPwmToSpiRemapTable1, tLDPwmToSpiRemapTable2};
    WORD pusLDPwmToSpiRemapTableSize[3] = {(sizeof(tLDPwmToSpiRemapTable0) / sizeof(tLDPwmToSpiRemapTable0[0])), (sizeof(tLDPwmToSpiRemapTable1) / sizeof(tLDPwmToSpiRemapTable1[0])), (sizeof(tLDPwmToSpiRemapTable2) / sizeof(tLDPwmToSpiRemapTable2[0]))};
    // multi-update sram partition Design

    for(WORD usUpdTimePerFrameIdx = 0; usUpdTimePerFrameIdx < _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME; usUpdTimePerFrameIdx++)
    {
        WORD usSRamAddressOffset = (((WORD)sizeof(StructSpiSRamBuf)) * usUpdTimePerFrameIdx);
        WORD usPwmAdjustCurve = pusPwmAdjustCurve[usUpdTimePerFrameIdx];
        BYTE pucSpiDataByteArray[sizeof(StructSpiSRamBuf)];

        WORD usIdx = 0;  // as CmdEntry Index

        for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
        {
            WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];

            WORD usRemapTableIdx = 0;
            WORD *pusLDPwmToSpiRemapTable = ppusLDPwmToSpiRemapTable[ucSpiInterfaceIdx];

            // for avoiding 3081 flash table access performance problem
            WORD pusSpiXRemapTable[MAXOF3_REMAP_TABLE(tLDPwmToSpiRemapTable0, tLDPwmToSpiRemapTable1, tLDPwmToSpiRemapTable2)];
            WORD usRemapTableSize = pusLDPwmToSpiRemapTableSize[ucSpiInterfaceIdx];
            for(WORD usSpiXDevIdx = 0; usSpiXDevIdx < usRemapTableSize; usSpiXDevIdx++)
            {
                pusSpiXRemapTable[usSpiXDevIdx] = pusLDPwmToSpiRemapTable[usSpiXDevIdx];
            }

            for(WORD usSpiXDevIdx = 0; usSpiXDevIdx < usSpiXDevNum; usSpiXDevIdx++)
            {
                if(usIdx < (_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
                {
                    WORD usSpiDataByteStartIdx = (WORD)(g_pstSpiDimmingCmdEntryData[usUpdTimePerFrameIdx].pulSpiCmdEntryData[usIdx] & 0x0000FFFF);
                    WORD usSpiDataByteCnt = (WORD)(g_pstSpiDimmingCmdEntryData[usUpdTimePerFrameIdx].pulSpiCmdEntryData[usIdx] >> 16);
                    WORD usSpiPwmDataByteStartIdx = usSpiDataByteStartIdx + _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES;
                    WORD usSpiDataByteIdx = usSpiDataByteStartIdx;

                    while(usSpiDataByteIdx < usSpiPwmDataByteStartIdx)
                    {
                        pucSpiDataByteArray[(usSpiDataByteIdx - usSRamAddressOffset)] = Scaler32GetByte((PB0053B_00_PWM2SPI_SPI_DATA + usSpiDataByteIdx), 0);
                        usSpiDataByteIdx++;
                    }

                    WORD usDataByteEnd = (usSpiDataByteStartIdx + usSpiDataByteCnt) - _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM;
                    while(usSpiDataByteIdx < usDataByteEnd)
                    {
                        // convert data bytes to pwm number
                        WORD usRemapIdx = pusSpiXRemapTable[usRemapTableIdx++];

                        SDWORD lCvtCurrPwmValue = (SDWORD)ExternalDeviceInterfaceLedConvertPwmToSpiFormat(pusPwmTargetBuf[usRemapIdx]);
                        SDWORD lCvtPrevPwmValue = (SDWORD)ExternalDeviceInterfaceLedConvertPwmToSpiFormat(pusPwmPrevTargetBuf[usRemapIdx]);

                        WORD usUpdPwmValue = (WORD)(lCvtPrevPwmValue + (((lCvtCurrPwmValue - lCvtPrevPwmValue) *  usPwmAdjustCurve) >> 8));
                        WORD usTmpIdx = (usSpiDataByteIdx - usSRamAddressOffset);
#if(_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE == 1)
                        pucSpiDataByteArray[usTmpIdx] = LOBYTE(usUpdPwmValue);
                        usSpiDataByteIdx++;
#else
#if(_LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP == _ON)
                        pucSpiDataByteArray[usTmpIdx] = HIBYTE(usUpdPwmValue);
                        pucSpiDataByteArray[(usTmpIdx + 1)] = LOBYTE(usUpdPwmValue);
                        usSpiDataByteIdx += 2;
#else
                        pucSpiDataByteArray[usTmpIdx] = LOBYTE(usUpdPwmValue);
                        pucSpiDataByteArray[(usTmpIdx + 1)] = HIBYTE(usUpdPwmValue);
                        usSpiDataByteIdx += 2;
#endif
#endif
                    }
#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
                    ExternalDeviceInterfaceLedDriverCalcChecksum((BYTE *)(&pucSpiDataByteArray[(usSpiDataByteStartIdx - usSRamAddressOffset)]), usSpiDataByteCnt);
#endif
                    usIdx++;
                }
                else
                {
                    break;
                }
            }
        }
        {
            WORD usTotalDataBytes = g_pusSpiDimmingUpdFrameTotalDataByte[usUpdTimePerFrameIdx];
            WORD usFrameDataByteStartOffset = g_usSpiDimmingSpiDataByteStartOffset;
            DWORD ulFrameSRamBufRegStartAddr = PB0053B_00_PWM2SPI_SPI_DATA + usFrameDataByteStartOffset + usSRamAddressOffset;

            for(WORD usTmpIdx = 0; usTmpIdx < usTotalDataBytes; usTmpIdx += 4)
            {
                Scaler32SetDWord((ulFrameSRamBufRegStartAddr + usTmpIdx), ((DWORD *)&pucSpiDataByteArray[(usFrameDataByteStartOffset + usTmpIdx)])[0]);
            }
        }
    }
}

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : ScalerSpiDimming Init Adim Buffer by using SRAM Reg
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingInitADimUseSram(void)
{
    // A-Dimming
    WORD usSpiDevIdxAcc = 0;
    WORD usSpiADimByteArrayIdx = 0;
    WORD usADimSRamAddressOffset = (((WORD)sizeof(StructSpiSRamBuf)) * _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME);
    BYTE pucSpiADimByteArray[sizeof(StructSpiSRamBuf)];
    BYTE ucCmdEntryOffset = _VALID_BY_SPI_USE_CMD_ENTRY_NUM;
    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    EnumPwmToSpiInterface penumPwmToSpiInterface[3] = {_PWMTOSPI_INTERFACE_0, _PWMTOSPI_INTERFACE_1, _PWMTOSPI_INTERFACE_2};

    WORD usIdx = 0;  // as CmdEntry Index
    WORD usSpiDataByteIdx = g_usSpiDimmingSpiDataByteStartOffset + usADimSRamAddressOffset;
    for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
    {
        WORD usUseCmdEntryNum = 0;

        WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];
        EnumPwmToSpiInterface enumPwmToSpiInterface = penumPwmToSpiInterface[ucSpiInterfaceIdx];

        for(WORD usSpiDevIdx = 0; usSpiDevIdx < usSpiXDevNum; usSpiDevIdx++)
        {
            if(usIdx < (_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
            {
                WORD usSpiADimByteCnt = ScalerSpiDimmingFormatWriteCmdBuffer(enumPwmToSpiInterface, _TRUE, usSpiDevIdx, _DEVICE_LED_DRIVER_ADIM_ADDR, _NULL_POINTER, (_DEVICE_LED_DRIVER_ADIM_WIDTH_BY_BYTE * (tLDPwmToSpiDataByteNum[usSpiDevIdxAcc] / _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE)) , &pucSpiADimByteArray[usSpiADimByteArrayIdx], 0, _FALSE, 0);

                g_stSpiDimmingADimCmdEntryData.pulSpiCmdEntryData[usIdx] = ((((DWORD)usSpiADimByteCnt) << 16) + (usSpiDataByteIdx));

                usSpiDataByteIdx += usSpiADimByteCnt;
                usSpiADimByteArrayIdx += usSpiADimByteCnt;

                usSpiDevIdxAcc++;
                usUseCmdEntryNum++;
                usIdx++;
            }
            else
            {
                break;
            }
        }
        g_pulSpiDimmingADimCmdEntryCfg[ucSpiInterfaceIdx] = GEN_SPI_CMD_ENTRY_CFG(ucCmdEntryOffset, usUseCmdEntryNum);
        ucCmdEntryOffset += usUseCmdEntryNum;
    }
    // DataBytes align to 4 bytes
    usSpiADimByteArrayIdx = ((usSpiADimByteArrayIdx + 3) / 4) * 4;
    g_usSpiDimmingADimTotalDataByte = usSpiADimByteArrayIdx;
    {
        DWORD ulTargetSRamBufRegAddr = PB0053B_00_PWM2SPI_SPI_DATA + g_usSpiDimmingSpiDataByteStartOffset + usADimSRamAddressOffset;

        for(WORD usTmpIdx = 0; usTmpIdx < usSpiADimByteArrayIdx; usTmpIdx += 4)
        {
            Scaler32SetDWord((ulTargetSRamBufRegAddr + usTmpIdx), ((DWORD *)&pucSpiADimByteArray[usTmpIdx])[0]);
        }
    }
}

//--------------------------------------------------
// Description  : Old Mode Update LD A-Dimming Data Use Sram
// Input Value  : pusColorApplyADim --> ADim Target Buffer
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDUpdateSramADimDataUseSram(WORD *pusColorApplyADim)
{
    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    WORD *ppusLDPwmToSpiRemapTable[3] = {tLDPwmToSpiRemapTable0, tLDPwmToSpiRemapTable1, tLDPwmToSpiRemapTable2};
    WORD pusLDPwmToSpiRemapTableSize[3] = {(sizeof(tLDPwmToSpiRemapTable0) / sizeof(tLDPwmToSpiRemapTable0[0])), (sizeof(tLDPwmToSpiRemapTable1) / sizeof(tLDPwmToSpiRemapTable1[0])), (sizeof(tLDPwmToSpiRemapTable2) / sizeof(tLDPwmToSpiRemapTable2[0]))};
    WORD usSRamAddressOffset = (((WORD)sizeof(StructSpiSRamBuf)) * _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME);
    BYTE pucSpiADimByteArray[sizeof(StructSpiSRamBuf)];
    WORD usIdx = 0;  // as CmdEntry Index

    for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
    {
        WORD usSpiXDevNum = pusSpiDevNum[ucSpiInterfaceIdx];

        WORD usRemapTableIdx = 0;
        WORD *pusLDPwmToSpiRemapTable = ppusLDPwmToSpiRemapTable[ucSpiInterfaceIdx];

        // for avoiding 3081 flash table access performance problem
        WORD pusSpiXRemapTable[MAXOF3_REMAP_TABLE(tLDPwmToSpiRemapTable0, tLDPwmToSpiRemapTable1, tLDPwmToSpiRemapTable2)];
        WORD usRemapTableSize = pusLDPwmToSpiRemapTableSize[ucSpiInterfaceIdx];
        for(WORD usSpiXDevIdx = 0; usSpiXDevIdx < usRemapTableSize; usSpiXDevIdx++)
        {
            pusSpiXRemapTable[usSpiXDevIdx] = pusLDPwmToSpiRemapTable[usSpiXDevIdx];
        }

        for(WORD usSpiXDevIdx = 0; usSpiXDevIdx < usSpiXDevNum; usSpiXDevIdx++)
        {
            if(usIdx < (_MAX_SPI_ONCE_TX_CMD_NUM * (ucSpiInterfaceIdx + 1)))
            {
                WORD usSpiDataByteStartIdx = (WORD)(g_stSpiDimmingADimCmdEntryData.pulSpiCmdEntryData[usIdx] & 0x0000FFFF);
                WORD usSpiDataByteCnt = (WORD)(g_stSpiDimmingADimCmdEntryData.pulSpiCmdEntryData[usIdx] >> 16);
                WORD usSpiPwmDataByteStartIdx = usSpiDataByteStartIdx + _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES;
                WORD usSpiDataByteIdx = usSpiDataByteStartIdx;


                while(usSpiDataByteIdx < usSpiPwmDataByteStartIdx)
                {
                    pucSpiADimByteArray[(usSpiDataByteIdx - usSRamAddressOffset)] = Scaler32GetByte((PB0053B_00_PWM2SPI_SPI_DATA + usSpiDataByteIdx), 0);
                    usSpiDataByteIdx++;
                }

                WORD usDataByteEnd = (usSpiDataByteStartIdx + usSpiDataByteCnt) - _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM;
                while(usSpiDataByteIdx < usDataByteEnd)
                {
                    // convert data bytes to pwm number
                    WORD usRemapIdx = pusSpiXRemapTable[usRemapTableIdx++];

                    WORD usCvtADimValue = ExternalDeviceInterfaceLedConvertADimFormat(pusColorApplyADim[usRemapIdx]);
                    WORD usTmpIdx = (usSpiDataByteIdx - usSRamAddressOffset);
#if(_DEVICE_LED_DRIVER_ADIM_WIDTH_BY_BYTE == 1)
                    pucSpiADimByteArray[usTmpIdx] = LOBYTE(usCvtADimValue);
                    usSpiDataByteIdx++;
#else
#if(_DEVICE_LED_DRIVER_ADIM_BYTE_SWAP == _ON)
                    pucSpiADimByteArray[usTmpIdx] = HIBYTE(usCvtADimValue);
                    pucSpiADimByteArray[(usTmpIdx + 1)] = LOBYTE(usCvtADimValue);
                    usSpiDataByteIdx += 2;
#else
                    pucSpiADimByteArray[usTmpIdx] = LOBYTE(usCvtADimValue);
                    pucSpiADimByteArray[(usTmpIdx + 1)] = HIBYTE(usCvtADimValue);
                    usSpiDataByteIdx += 2;
#endif
#endif
                }
#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
                ExternalDeviceInterfaceLedDriverCalcChecksum((BYTE *)(&pucSpiADimByteArray[(usSpiDataByteStartIdx - usSRamAddressOffset)]), usSpiDataByteCnt);
#endif
                usIdx++;
            }
            else
            {
                break;
            }
        }
    }

    {
        WORD usFrameDataByteStartOffset = g_usSpiDimmingSpiDataByteStartOffset;
        DWORD ulTargetSRamBufRegAddr = PB0053B_00_PWM2SPI_SPI_DATA + usFrameDataByteStartOffset + usSRamAddressOffset;

        for(usIdx = 0; usIdx < g_usSpiDimmingADimTotalDataByte; usIdx += 4)
        {
            Scaler32SetDWord((ulTargetSRamBufRegAddr + usIdx), ((DWORD *)&pucSpiADimByteArray[(usFrameDataByteStartOffset + usIdx)])[0]);
        }
    }
}
#endif
#endif

//--------------------------------------------------
// Description  : Start SRAM Mode SPI TX
// Input Value  : None
// Output Value : execute Status
//--------------------------------------------------
bit ScalerSpiDimmingLDSramModeStartTX(void)
{
#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
#if(_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE)
    // Use TR9 for LD calculating (Use BW32 for Updating)
    StructBW32CmdInfo pstBW32CmdInfo[3];
    ScalerSpiDimmingLDSramModeInitBW32CmdInfo(pstBW32CmdInfo);
    g_enumColorPwm2SpiSramModeTxCallBackFuncId = _COLOR_PWM2SPI_SRAM_TX_CALLBACK_LD;


    if(ScalerMcuCheckHwBW32Avaiable() == _TRUE)
    {
        if(ScalerBW32LaunchCmdX(3, pstBW32CmdInfo, 0, _FALSE, 0, _BW32_CALLBACK_SPI_DIMMING_LD_SRAM) == _FALSE)
        {
            g_enumColorPwm2SpiSramModeTxCallBackFuncId = _COLOR_PWM2SPI_SRAM_TX_CALLBACK_NULL;
            return _FALSE;
        }
    }
    else
    {
        if(ScalerBW32LaunchCmdX(3, pstBW32CmdInfo, 0, _FALSE, 0, _BW32_CALLBACK_NULL) == _FALSE)
        {
            g_enumColorPwm2SpiSramModeTxCallBackFuncId = _COLOR_PWM2SPI_SRAM_TX_CALLBACK_NULL;
            return _FALSE;
        }

        if((g_bSpiDimmingSramModeTxDoneFlag == _FALSE) && (ScalerColorLDPwmToSpiCheckSpiIsBusy() == _FALSE))
        {
            ScalerSpiDimmingLDSramModeSpiTx();
        }
        else
        {
            // SPI TX is busy now
            g_bSpiDimmingSramModePendTxFlag = _TRUE;
        }
    }
#endif
    return _TRUE;
#else

// RX3081 only
    // config i-th PWM update info
    WORD usTotalCmdEntryNum = 0;

    WORD pusSpiDevNum[3] = {_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM, _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM};
    EnumPwmToSpiInterface penumPwmToSpiInterface[3] = {_PWMTOSPI_INTERFACE_0, _PWMTOSPI_INTERFACE_1, _PWMTOSPI_INTERFACE_2};
    DWORD *pulCmdEntryCfg = &g_ppulSpiDimmingCmdEntryCfg[g_ucSpiDimmingMultiUpdateIdx][0];
    // D-Dimming
    WORD usSpi0CmdEntryStartIdx = LOWORD(pulCmdEntryCfg[0]);
    DWORD *pulSrcData = &g_pstSpiDimmingCmdEntryData[g_ucSpiDimmingMultiUpdateIdx].pulSpiCmdEntryData[0];
#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
    if(g_bSpiDimmingSRamAdimMode == _TRUE)
    {
        // A-Dimming
        pulCmdEntryCfg = &g_pulSpiDimmingADimCmdEntryCfg[0];
        usSpi0CmdEntryStartIdx = LOWORD(pulCmdEntryCfg[0]);
        pulSrcData = &g_stSpiDimmingADimCmdEntryData.pulSpiCmdEntryData[0];
    }
#endif

    for(BYTE ucSpiInterfaceIdx = 0; ucSpiInterfaceIdx < _USE_SPI_INTERFACE_NUM; ucSpiInterfaceIdx++)
    {
        if(pusSpiDevNum[ucSpiInterfaceIdx] > 0)
        {
            DWORD ulSpiXCmdEntryCfg = pulCmdEntryCfg[ucSpiInterfaceIdx];
            usTotalCmdEntryNum += HIWORD(ulSpiXCmdEntryCfg);

            // init CmdEntryCfg
            ScalerColorLDPwmToSpiSetCmdEntryConfig(penumPwmToSpiInterface[ucSpiInterfaceIdx], ulSpiXCmdEntryCfg);
        }
    }
    // init CmdEntryData
    volatile DWORD *pulDestReg = (volatile DWORD *)(PB00539_00_PWM2SPI_NEW_CMD_ENTRY + (usSpi0CmdEntryStartIdx * 4));

    for(WORD usIdx = 0; usIdx < usTotalCmdEntryNum; usIdx++)
    {
        pulDestReg[usIdx] = pulSrcData[usIdx];
    }

    // init CmdEntryDummyByte
    pulDestReg = (volatile DWORD *)(PB00538_30_SRAM_MODE_CMD_ENTRY_DUMMY_CFG0 + ((usSpi0CmdEntryStartIdx / 4) * 4));
    pulSrcData = &g_stSpiDimmingCmdEntryDummyBytes.pulSpiCmdEntryDummyBytes[0];

    usTotalCmdEntryNum = (usTotalCmdEntryNum + 3) / 4;
    for(WORD usIdx = 0; usIdx < usTotalCmdEntryNum; usIdx++)
    {
        pulDestReg[usIdx] = pulSrcData[usIdx];
    }

    // Use RX3081 for LD calculating
    g_enumColorPwm2SpiSramModeTxCallBackFuncId = _COLOR_PWM2SPI_SRAM_TX_CALLBACK_LD;

    // trigger SRAM Mode SPI TX
    ScalerColorLDPwmToSpiStartTX();

    return _TRUE;
#endif
}

#if(_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME > 1)
//--------------------------------------------------
// Description  : SRAM Mode Manual Apply UpdSync(UpdSync Pin or SPI Cmd)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDManualApplyUpdSync(void)
{
    if(g_ucSpiDimmingTxTimeIdx == (_MAX_PWM2SPI_SMODE_REUSE_TIMES - 1))
    {
        // clear apply done flag first
        ScalerColorLDPwmToSpiAckUpdSyncApplyDone();
        // Manual Apply UpdSync
        ScalerColorLDPwmToSpiManualApplyUpdSync();

        for(WORD usCnt = 0; usCnt < 200; usCnt++)
        {
            if(ScalerColorLDPwmToSpiCheckUpdSyncApplyDone() == _TRUE)
            {
                break;
            }
            DELAY_10US();
        }
    }
}
#endif

//--------------------------------------------------
// Description  : SRAM Mode SPI TX Done CallBack function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSpiDimmingLDSramModeSpiTxDoneCallBack(void)
{
#if((_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE) && (_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
    if(g_bSpiDimmingSramModePendTxFlag == _TRUE)
    {
#if(_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME > 1)
        ScalerSpiDimmingLDManualApplyUpdSync();
#endif
        // SRAM Buffer is ready now
        ScalerSpiDimmingLDSramModeSpiTx();
        // Check&&Start Next run BW32
        ScalerSpiDimmingLDSramModeNextBW32();
        return;
    }
    else
    {
        if(g_ucSpiDimmingTxTimeIdx != (_MAX_PWM2SPI_SMODE_REUSE_TIMES - 1))
        {
            // Do NOTHING, should not enter here(BW32 slower than SPI TX), just wait BW32 done && BW32 INT Handler
            return;
        }
        g_ucSpiDimmingTxTimeIdx = 0;
    }
#endif

#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
    if(g_bSpiDimmingSRamAdimMode == _TRUE)
    {
        // LD Sram Mode Tx is all done
#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)
#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
        if(GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_CONSTANT)
#endif
        {
            ScalerColorLDPwmToSpiTxForUpdSync();
        }
#endif
        // Mark Pwm2Spi SRAM Mode is TX done
        g_bSpiDimmingSramModeTxDoneFlag = _TRUE;
    }
    else
#endif
    {
#if(_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME > 1)
        ScalerSpiDimmingLDManualApplyUpdSync();
#endif

        if(g_ucSpiDimmingMultiUpdateIdx == (_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME - 1))
        {
            // LD Sram Mode Tx is all done
#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)
#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
            if(GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_CONSTANT)
#endif
            {
                ScalerColorLDPwmToSpiTxForUpdSync();
            }
#endif
            // Mark Pwm2Spi SRAM Mode is TX done
            g_bSpiDimmingSramModeTxDoneFlag = _TRUE;
            g_enumColorPwm2SpiSramModeTxCallBackFuncId = _COLOR_PWM2SPI_SRAM_TX_CALLBACK_NULL;

#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_VSYNC)
            if(ScalerColorLDPwmToSpiGetUpdateSyncTriggerSource() == _UPD_SYNC_BY_LOCAL_DIMMING_GAIN_SYNC)
#endif
            {
                // Notify BLModel SPI TX is done
                ScalerColorLDPwmToSpiNotifyBLModelSpiTxDone();
            }
        }
        else
        {
            // LD Sram Mode Start Next run PWM Update job
            g_ucSpiDimmingMultiUpdateIdx++;
            g_bSpiDimmingSramModeStartTxResult = ScalerSpiDimmingLDSramModeStartTX();
        }
    }
}

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : remap data of boost gain array
// Input Value  : boost gain data sorted by driver IC index, boost gain data sorted by panel region
// Output Value : none
//--------------------------------------------------
void ScalerSpiDimmingLocalDimmingRegionBoostAdjust(WORD *pusBoostGainData, WORD *pusBoostGainRemap)
{
    BYTE ucI = 0;
#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM != 0)
    for(ucI = 0; ucI < _LOCAL_DIMMING_TOTAL_AREA_OF_SPI0; ucI++)
    {
        pusBoostGainRemap[ucI] = pusBoostGainData[tLDPwmToSpiRemapTable0[ucI]];
    }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
    for(ucI = 0; ucI < _LOCAL_DIMMING_TOTAL_AREA_OF_SPI1; ucI++)
    {
        pusBoostGainRemap[_LOCAL_DIMMING_TOTAL_AREA_OF_SPI0 + ucI] = pusBoostGainData[tLDPwmToSpiRemapTable1[ucI]]
    }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
    for(ucI = 0; ucI < _LOCAL_DIMMING_TOTAL_AREA_OF_SPI2; ucI++)
    {
        pusBoostGainRemap[_LOCAL_DIMMING_TOTAL_AREA_OF_SPI0 + _LOCAL_DIMMING_TOTAL_AREA_OF_SPI1 + ucI] = pusBoostGainData[tLDPwmToSpiRemapTable2[ucI]]
    }
#endif
}
#endif
#endif  // End of #if(_LOCAL_DIMMING_FUNCTION == _ON)
#endif  // End of #if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
#endif  // End of #if(_SPI_SUPPORT == _ON)
