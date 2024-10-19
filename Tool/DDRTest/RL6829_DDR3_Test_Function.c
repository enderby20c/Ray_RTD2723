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
// ID Code      : RL6829_DDR3_Test_Function.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDR3_TEST__

#include "ScalerFunctionInclude.h"

#if(_DDR3_PHASE_CALIBRATION == _ON)
#warning "NOTE: _DDR3_PHASE_CALIBRATION is _ON!!!"
#endif


#if(_DDR3_PHASE_CALIBRATION == _ON)
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
//--------------------------------------------------
// DDR3 Offline Search Phase
//--------------------------------------------------
// Read data buffer
BYTE g_pucWriteDataA[16] = {0x33, 0x33, 0x55, 0x55, 0xaa, 0xaa, 0xcc, 0xcc, 0x22, 0x22, 0x44, 0x44, 0x88, 0x88, 0xBB, 0xBB};
BYTE g_pucReadDataA[16];
BYTE g_pucWriteDataB[16] = {0x55, 0x55, 0x33, 0x33, 0xcc, 0xcc, 0xaa, 0xaa, 0x44, 0x44, 0x22, 0x22, 0xbb, 0xbb, 0x88, 0x88};
BYTE g_pucReadDataB[16];
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//--------------------------------------------------
// RLE1039 Offline DDR3 Search Phase
//--------------------------------------------------
//bit g_bDDR3OfflineCalPhaseDone = _FALSE;
BYTE g_ucDDR3OfflineCalPhaseDone = 0x00;
DWORD g_ulDDRPLLPhase0;
DWORD g_ulDDRPLLPhase1;
DWORD g_ulDDRPLLPhase2;
DWORD g_ulDDR3TXFIFOSTR0Cal;
DWORD g_ulDDR3TXFIFOSTR1Cal;

//--------------------------------------------------
// DDR3 Search Phase - Write Leveling
//--------------------------------------------------
#define _SEARCH_PHASE_WRITE_LEVELING                        _ON

typedef struct
{
    BYTE pucWritePIOfClk[11];
    BYTE ucReadDQDelayTap;
    BYTE ucRdFIFOMap;
} StructDDR3OfflinePhaseInfo;

#define _DDR3_INIT_PHASE_CLK10                              32 // 0x00 cs
#define _DDR3_INIT_PHASE_CLK9                               40 // 0x08 dq_3
#define _DDR3_INIT_PHASE_CLK8                               40 // 0x08 dq_2
#define _DDR3_INIT_PHASE_CLK7                               40 // 0x08 dq_1
#define _DDR3_INIT_PHASE_CLK6                               40 // 0x08 dq_0
#define _DDR3_INIT_PHASE_CLK5                               32 // 0x00 dqs_3
#define _DDR3_INIT_PHASE_CLK4                               32 // 0x00 dqs_2
#define _DDR3_INIT_PHASE_CLK3                               32 // 0x00 dqs_1
#define _DDR3_INIT_PHASE_CLK2                               32 // 0x00 das_0
#define _DDR3_INIT_PHASE_CLK1                               32 // 0x00 CMD
#define _DDR3_INIT_PHASE_CLK0                               32 // 0x00 CK

#define _PHASE_CHK_DEBUG_MSG                                _ON

#define _PHASE_CHK_DEBUG_DETAIL_MSG                         _ON

#define SET_BIT_RESULT(pucResBuf, ucIndex, bResult)         ((pucResBuf)[(ucIndex) / 8] = ((pucResBuf)[(ucIndex) / 8] & ~(_BIT0 << ((ucIndex) % 8))) | (((BYTE)(bResult)) << ((ucIndex) % 8)))

#define GET_BIT_RESULT(pucResBuf, ucIndex)                  (((pucResBuf)[(ucIndex) / 8] & (_BIT0 << ((ucIndex) % 8))) >> ((ucIndex) % 8))


#define PI_DIFF(ucPhaseTo, ucPhaseFrom)                     (((ucPhaseTo) + 64 - (ucPhaseFrom)) % 64)

#define GET_FIFO_VALUE(x)                                   ((((x) & (_BIT6 | _BIT5)) >> 5) + 1)

#define GET_PHASE_VALUE(x)                                  ((x) & 0x1F)

typedef enum
{
    _SCAN_RESULT_WR_PI,
    _SCAN_RESULT_RD_DLY_TAP,
    _SCAN_RDQS_EN,
    _SCAN_RESULT_WR_DLY_TAP,
    _SCAN_RESULT_RX_FIFO,
    _SCAN_RESULT_RX_ODT,
} EnumScanResultType;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//****************************************************************************
// RLE1039 Offline DDR3 Search Phase : Start
//****************************************************************************
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
void ScalerDDR3OfflinePhaseCalMCUMode(void);
bit ScalerDDR3OfflinePhaseCheckMCUMode(void);
#endif

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
void ScalerDDR3OfflinePhaseCalFRCMode(void);
void ScalerDDR3OfflineSearchPhaseFRCModePreprocess(void);
void ScalerDDR3OfflineSerachPhaseFRCModeClientAccessCtrl(bit bEnable);
void ScalerDDR3OfflineSearchPhaseFRCModePostprocess(void);
BYTE ScalerDDR3OfflinePhaseCheckFRCMode(void);
#endif

void ScalerDDR3OfflineSearchPhase(void);
bit ScalerDDR3OfflinePhaseCheck(void);

void ScalerDDR3OfflineScanPhaseCK(StructDDR3OfflinePhaseInfo *pstCurrResult);
void ScalerDDR3OfflineScanPhaseCS(StructDDR3OfflinePhaseInfo *pstCurrResult);
#if(_SEARCH_PHASE_WRITE_LEVELING == _ON)
void ScalerDDR3WritleLevleingtest(StructDDR3OfflinePhaseInfo *pstCurrResult);
BYTE ScalerDDR3WLFindProperWDQSPhase(BYTE pucWLResult0[8], BYTE pucWLResult1[8]);
#endif
void ScalerDDR3OfflineScanPhaseDQS(StructDDR3OfflinePhaseInfo *pstCurrResult);

void ScalerDDR3OfflineScanPhaseDQ(StructDDR3OfflinePhaseInfo *pstCurrResult);

void ScalerDDR3OfflineScanRdDQSEn(void);
void ScalerDDR3ReadDlytaptest(void);
void ScalerDDR3OfflineScanRxFIFO(void);
void ScalerDDR3OfflineScanRxODT(void);

void ScalerDDR3OfflineApplyNewPhase(void);
void ScalerDDR3OfflineSetDDRPLLFreqtest(DWORD ulFreq);
void ScalerDDR3OfflineSetDDRPLLWritePhasetest(DWORD ulDDRPLLInitPhase0, DWORD ulDDRPLLInitPhase1, DWORD ulDDRPLLInitPhase2, DWORD ulDDR3TXFIFOSTR0Cal, DWORD ulDDR3TXFIFOSTR1Cal);

void ScalerDDR3OfflineScanPhasePrintScanResult(BYTE pucScanResult[8]);
BYTE ScalerDDR3OfflineFindCentralValueOfLongestPassRange(BYTE pucScanResult[8], EnumScanResultType enumResultType);

//****************************************************************************
// RLE1039 Offline DDR3 Search Phase : END
//****************************************************************************


#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
//--------------------------------------------------
// Description  : DDR3 offline phase calibration - MCU mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflinePhaseCalMCUMode(void)
{
    if(g_ucDDR3OfflineCalPhaseDone == 0x01)
    {
        return;
    }

    //=================================
    // Preprocess of phase calibration
    //=================================
    // Mask all the requests from other client to DC SYS
    Scaler32SetDWord(PB08100_D0_DC_CLIENT_MASK, 0x000017FF);

    //=================================
    // Phase calibration
    //=================================
    ScalerDDR3OfflineSearchPhase();

    //=================================
    // Postprocess of phase calibration
    //=================================
    // Clear DC SYS request mask
    Scaler32SetDWord(PB08100_D0_DC_CLIENT_MASK, 0x00000000);

    // DDR3 Offlie phase cal. done, update flag
    g_ucDDR3OfflineCalPhaseDone = 0x01;
}
//--------------------------------------------------
// Description  : Check DDR R/W correctness with MCU DDR DMA
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerDDR3OfflinePhaseCheckMCUMode(void)
{
    BYTE ucDataBufRegOffset = 0;
    BYTE ucDatatest = 0;

    // Read status flags
    bit bReadDoneA = _TRUE;
    bit bReadDoneB = _TRUE;

    // Phase check result
    bit bPhaseChkResultA = _SUCCESS;
    bit bPhaseChkResultB = _SUCCESS;

    //-------------------------------------------------------------------------
    // Write Data
    // ------------------------------------------------------------------------
    // Write data to DDR data buffer
    for(ucDataBufRegOffset = 0; ucDataBufRegOffset < 16; ucDataBufRegOffset++)
    {
        ScalerSetByte((P37_10_MCU_DC_DATABUF_W_A_00 + ucDataBufRegOffset), g_pucWriteDataA[ucDataBufRegOffset]);

#if(_EMBEDDED_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)

        ScalerSetByte((P37_20_MCU_DC_DATABUF_W_B_00 + ucDataBufRegOffset), g_pucWriteDataB[ucDataBufRegOffset]);
#endif
    }

    // Send DDR write request
    ScalerSetByte(P37_00_MCU_DC_CMD, 0x80);
    ScalerTimerDelayXms(2);

    // Polling qack of write request
    if(ScalerTimerPollingFlagProc(10, P37_00_MCU_DC_CMD, (_BIT7 | _BIT6 | _BIT5), _FALSE) == _FALSE)
    {
        DebugMessageMemoryPhaseCal("DDR3 DMA Write Fail !! Timeout", 0);
    }

    // Delay Time us [5,x] Waiting to ensure that write process is finished
    DELAY_5US();

    //-------------------------------------------------------------------------
    // Read Data
    // ------------------------------------------------------------------------
    // Read data buffer to clear uncleared ready-to-read flag (if it exists).
    for(ucDataBufRegOffset = 0; ucDataBufRegOffset < 16; ucDataBufRegOffset++)
    {
        ScalerSetByte((P37_30_MCU_DC_DATABUF_R_A_00 + ucDataBufRegOffset), 0x00);

#if(_EMBEDDED_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)
        ScalerSetByte((P37_40_MCU_DC_DATABUF_R_B_00 + ucDataBufRegOffset), 0x00);

#endif
    }

    // Send DDR read request
    ScalerSetByte(P37_00_MCU_DC_CMD, 0xA0);
    ScalerTimerDelayXms(2);

    // Read data from DDR data buffer
    for(ucDataBufRegOffset = 0; ucDataBufRegOffset < 16; ucDataBufRegOffset++)
    {
        g_pucReadDataA[ucDataBufRegOffset] = ScalerGetByte((P37_30_MCU_DC_DATABUF_R_A_00 + ucDataBufRegOffset));

#if(_EMBEDDED_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)
        g_pucReadDataB[ucDataBufRegOffset] = ScalerGetByte((P37_40_MCU_DC_DATABUF_R_B_00 + ucDataBufRegOffset));
#endif
    }

    //-------------------------------------------------------------------------
    // Compare read data with writed data
    // ------------------------------------------------------------------------
    bPhaseChkResultA = (memcmp(g_pucReadDataA, g_pucWriteDataA, 16) == 0) ? _SUCCESS : _FAIL;
#if(_EMBEDDED_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)
    bPhaseChkResultB = (memcmp(g_pucReadDataB, g_pucWriteDataB, 16) == 0) ? _SUCCESS : _FAIL;
#endif

    if((bPhaseChkResultA == _SUCCESS) && (bPhaseChkResultB == _SUCCESS))
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}
#endif

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
//--------------------------------------------------
// Description  : DDR3 offline phase calibration - FRC mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflinePhaseCalFRCMode(void)
{
    if(g_ucDDR3OfflineCalPhaseDone == 0x01)
    {
        return;
    }

#if(_OD_FUNCTION == _ON)
    //=================================
    // Disable OD
    //=================================
    ScalerODEnable(_FUNCTION_OFF);
#endif

    //=================================
    // Preprocess of phase calibration
    //=================================
    ScalerDDR3OfflineSearchPhaseFRCModePreprocess();
    ScalerDDR3OfflineSerachPhaseFRCModeClientAccessCtrl(_DISABLE);

    //=================================
    // Phase calibration
    //=================================
    ScalerDDR3OfflineSearchPhase();

    //=================================
    // Postprocess of phase calibration
    //=================================
    ScalerDDR3OfflineSerachPhaseFRCModeClientAccessCtrl(_ENABLE);
    ScalerDDR3OfflineSearchPhaseFRCModePostprocess();

    g_ucDDR3OfflineCalPhaseDone = 0x01;
}
//--------------------------------------------------
// Description  : FRC(M1, M2) client access control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineSerachPhaseFRCModeClientAccessCtrl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable M1, M2 FRC Capture
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_M1_M2, _ENABLE);

        // Enable M1, M2 FRC Display
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_M1_M2, _ENABLE);
        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);
    }
    else
    {
        // Disable M1, M2, S1 and S2 FRC Capture
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);
        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(P85_27_CAP_S1_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(P56_27_CAP_S2_DDR_CTRL1, ~_BIT7, 0x00);

        // Disable M1, M2, S1 and S2 FRC Display
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_ALL, _DISABLE);
        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_ALL, _DB_APPLY_POLLING);
    }
}
//--------------------------------------------------
// Description  : Preprocess of DDR search phase FRC mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineSearchPhaseFRCModePreprocess(void)
{
#if(_DDR3_PHASE_CAL_FRC_MODE_INTERNAL_PG == _ON)
    // Enable I-domain random gen
    ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT7, _BIT7);

    // Set I-domain random gen R != G != B
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_10_I_PG_CTRL_0_M1, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_10_I_PG_CTRL_0_M2, ~_BIT6, _BIT6);
    // Set I-domain random gen pattern reset num
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_17_PATTERN_RESET_M1, 0xFC);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_15_INITIAL_RGB_M_M1, 0x1E);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_17_PATTERN_RESET_M2, 0xFF);
#endif

    // Disable I-dither
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, 0x00);
    ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, 0x00);

    // Disable Watch Dog
    ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _DISABLE);
}
//--------------------------------------------------
// Description  : Postprocess of DDR phase calibration FRC mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineSearchPhaseFRCModePostprocess(void)
{
#if(_DDR3_PHASE_CAL_FRC_MODE_INTERNAL_PG == _ON)
    // Disable I-domain random gen
    ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT7, 0x00);
    // Clear I-domain random gen pattern reset num
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_17_PATTERN_RESET_M1, 0x00);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_17_PATTERN_RESET_M2, 0x00);
#endif

    // Enable I-dither
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, _BIT5);
    ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, _BIT5);

    // Enable Watch Dog
    ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _ENABLE);
}
//--------------------------------------------------
// Description  : Check DDR R/W correctness by comparing I/M CRC
// Input Value  : None
// Output Value : Phase check result byte
//--------------------------------------------------
BYTE ScalerDDR3OfflinePhaseCheckFRCMode(void)
{
    BYTE ucCRCRegOffset = 0;
    BYTE pucICRCValueM1[3];
    BYTE pucICRCValueM2[3];
    BYTE pucMCRCValueM1[3];
    BYTE pucMCRCValueM2[3];
    BYTE *ppucICRC[2] = {pucICRCValueM1, pucICRCValueM2};
    BYTE *ppucMCRC[2] = {pucMCRCValueM1, pucMCRCValueM2};

    bit bResult = _FAIL;

    BYTE ucGlobalDDomainDBCtrlBackup = 0x00;
#if(_PHASE_CHK_DEBUG_MSG == _ON)
#if(_PHASE_CHK_DEBUG_DETAIL_MSG == _ON)
    DWORD ulPrintBuf_0 = 0;
    DWORD ulPrintBuf_1 = 0;
#endif
#endif

    //===========================================
    // Set D-domain global DB event = "DVS"
    //===========================================
    // Backup D-domain global DB setting
    ucGlobalDDomainDBCtrlBackup = ScalerGetBit(P31_B0_D_DB_CTRL0, (_BIT7 | _BIT5));
    // Set D-domain global DB event to DVS
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT5), (_BIT7));

    //===========================================
    // Get I-domain CRC
    //===========================================
    // Wait until IEN_STOP
    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);

    // Enable M1, M2 FRC Capture
    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, _BIT7);

    // Enable M1, M2 I-domain CRC output
    ScalerSetByte(P36_00_I_CRC_CTRL_M1, 0x82);
    ScalerSetByte(P36_08_I_CRC_CTRL_M2, 0x82);
    ScalerSetByte(P36_80_M_CAP_CRC_CTRL_M1, 0x80);
    ScalerSetByte(P36_88_M_CAP_CRC_CTRL_M2, 0x80);

    // Wait until IEN_START
    ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, _INPUT_PATH_M1_M2);

    // Get FRC cap current block num, and set to FRC display block num
    ScalerSetBit(P46_82_M_DISP_BLOCK_SEL, ~(_BIT1 | _BIT0), (ScalerGetBit(P5_2A_CAP_M1_STATUS, (_BIT7 | _BIT6)) >> 6));


    // Wait 1 IVS
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M2);


    // Disable M1_M2 FRC Capture
    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, 0x00);
    ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, 0x00);

    // Read I-domain CRC (First 3 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < 3; ucCRCRegOffset++)
    {
        pucICRCValueM1[ucCRCRegOffset] = ScalerGetByte(P36_81_M_MAIN1_CAP_CRC_1 + ucCRCRegOffset);
        pucICRCValueM2[ucCRCRegOffset] = ScalerGetByte(P36_89_M_MAIN2_CAP_CRC_1 + ucCRCRegOffset);
    }

    // Disable M1, M2 I-domain CRC output
    ScalerSetByte(P36_00_I_CRC_CTRL_M1, 0x00);
    ScalerSetByte(P36_08_I_CRC_CTRL_M2, 0x00);
    ScalerSetByte(P36_80_M_CAP_CRC_CTRL_M1, 0x00);
    ScalerSetByte(P36_88_M_CAP_CRC_CTRL_M2, 0x00);

    //===========================================
    // Get M-domain CRC
    //===========================================
    // Wait until DEN_START
    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

    // Enable M1, M2 FRC Display
    ScalerSetBit(P46_82_M_DISP_BLOCK_SEL, ~(_BIT2), _BIT2);

    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT0, _BIT0);
    ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT0, _BIT0);

    // DB apply no polling
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

    // Enable M1, M2 M-domain CRC output
    ScalerSetByte(P36_40_M_DISP_CRC_CTRL_M1, 0x80);
    ScalerSetByte(P36_48_M_DISP_CRC_CTRL_M2, 0x80);
    // Wait 1 DVS
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    // Disable M1, M2 FRC Display
    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT0, 0x00);
    ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT0, 0x00);

    ScalerSetBit(P46_82_M_DISP_BLOCK_SEL, ~(_BIT2), 0x00);


    // DB apply no polling
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

    // Wait 1 DVS
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    // Read M-domain CRC (First 3 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < 3; ucCRCRegOffset++)
    {
        pucMCRCValueM1[ucCRCRegOffset] = ScalerGetByte(P36_41_M_MAIN1_DISP_CRC_1 + ucCRCRegOffset);
        pucMCRCValueM2[ucCRCRegOffset] = ScalerGetByte(P36_49_M_MAIN2_DISP_CRC_1 + ucCRCRegOffset);
    }

    // Disable M1, M2 M-domain CRC output
    ScalerSetByte(P36_40_M_DISP_CRC_CTRL_M1, 0x00);
    ScalerSetByte(P36_48_M_DISP_CRC_CTRL_M2, 0x00);

    //===========================================
    // Resume D-domain global DB setting
    //===========================================
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT5), ucGlobalDDomainDBCtrlBackup);

    //===========================================
    // Compare I-domain CRC with  M-domain CRC
    //===========================================
    bResult = ((memcmp(ppucICRC[0], ppucMCRC[0], 3) == 0) && (memcmp(ppucICRC[1], ppucMCRC[1], 3) == 0)) ? _SUCCESS : _FAIL;


#if(_PHASE_CHK_DEBUG_MSG == _ON)
#if(_PHASE_CHK_DEBUG_DETAIL_MSG == _ON)
    // If failed, dump read data
    if(memcmp(pucICRCValueM1, pucMCRCValueM1, 3) != 0)
    {
        ulPrintBuf_0 = 0;
        ulPrintBuf_1 = 0;
        for(ucCRCRegOffset = 0; ucCRCRegOffset < 3; ucCRCRegOffset++)
        {
            ulPrintBuf_0 = (ulPrintBuf_0 + pucICRCValueM1[ucCRCRegOffset]) << 8;
            ulPrintBuf_1 = (ulPrintBuf_1 + pucMCRCValueM1[ucCRCRegOffset]) << 8;
        }
        DebugMessageMemoryPhaseCal("M1 FRC CHK Fail", 0);
        DebugMessageMemoryPhaseCal("M1 I-CRC:", ulPrintBuf_0);
        DebugMessageMemoryPhaseCal("M1 M-CRC:", ulPrintBuf_1);
    }
    else
    {
        DebugMessageMemoryPhaseCal("M1 FRC CHK Pass", 0);
    }

    if(memcmp(pucICRCValueM2, pucMCRCValueM2, 3) != 0)
    {
        ulPrintBuf_0 = 0;
        ulPrintBuf_1 = 0;
        for(ucCRCRegOffset = 0; ucCRCRegOffset < 3; ucCRCRegOffset++)
        {
            ulPrintBuf_0 = (ulPrintBuf_0 + pucICRCValueM2[ucCRCRegOffset]) << 8;
            ulPrintBuf_1 = (ulPrintBuf_1 + pucMCRCValueM2[ucCRCRegOffset]) << 8;
        }
        DebugMessageMemoryPhaseCal("M2 FRC CHK Fail", 0);
        DebugMessageMemoryPhaseCal("M2 I-CRC:", ulPrintBuf_0);
        DebugMessageMemoryPhaseCal("M2 M-CRC:", ulPrintBuf_1);
    }
    else
    {
        DebugMessageMemoryPhaseCal("M2 FRC CHK Pass", 0);
    }
#endif
    DebugMessageMemoryPhaseCal("** FRC Phase Chk Result.", bResult);
#endif

    return bResult;
}
#endif // End of #if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)

//--------------------------------------------------
// Description  : DDR3 offline phase calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineSearchPhase(void)
{
    StructDDR3OfflinePhaseInfo structCurrFoundPhase;
    structCurrFoundPhase.pucWritePIOfClk[10] = _DDR3_INIT_PHASE_CLK10;
    structCurrFoundPhase.pucWritePIOfClk[9] = _DDR3_INIT_PHASE_CLK9;
    structCurrFoundPhase.pucWritePIOfClk[8] = _DDR3_INIT_PHASE_CLK8;
    structCurrFoundPhase.pucWritePIOfClk[7] = _DDR3_INIT_PHASE_CLK7;
    structCurrFoundPhase.pucWritePIOfClk[6] = _DDR3_INIT_PHASE_CLK6;
    structCurrFoundPhase.pucWritePIOfClk[5] = _DDR3_INIT_PHASE_CLK5;
    structCurrFoundPhase.pucWritePIOfClk[4] = _DDR3_INIT_PHASE_CLK4;
    structCurrFoundPhase.pucWritePIOfClk[3] = _DDR3_INIT_PHASE_CLK3;
    structCurrFoundPhase.pucWritePIOfClk[2] = _DDR3_INIT_PHASE_CLK2;
    structCurrFoundPhase.pucWritePIOfClk[1] = _DDR3_INIT_PHASE_CLK1;
    structCurrFoundPhase.pucWritePIOfClk[0] = _DDR3_INIT_PHASE_CLK0;

    //===========================================
    // Search phase
    //===========================================
    DebugMessageMemoryPhaseCal("===================", 0);
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
    DebugMessageMemoryPhaseCal("_____MCU_Mode_____", 0);
#elif(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
    DebugMessageMemoryPhaseCal("_____FRC_Mode_____", 0);
#endif
    DebugMessageMemoryPhaseCal("___________Version:", 20210408);
    DebugMessageMemoryPhaseCal("===================", 0);

#if(_SEARCH_PHASE_WRITE_LEVELING == _ON)
    DebugMessageMemoryPhaseCal("====================", 0);
    DebugMessageMemoryPhaseCal("====ScanPhase WL====", 0);
    ScalerDDR3WritleLevleingtest(&structCurrFoundPhase);
#endif
    //===========================================
    // Search phase - CLK
    //===========================================
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[0]: CK====", 0);
    ScalerDDR3OfflineScanPhaseCK(&structCurrFoundPhase);

    //===========================================
    // Search phase - CS
    //===========================================
    DebugMessageMemoryPhaseCal("============================", 0);
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[10]: CS====", 0);
    ScalerDDR3OfflineScanPhaseCS(&structCurrFoundPhase);

    //===========================================
    // Search phase - wDQS
    //===========================================
    DebugMessageMemoryPhaseCal("======================================", 0);
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[2] & Clk[3] & Clk[4] & Clk[5]: DQS====", 0);
    ScalerDDR3OfflineScanPhaseDQS(&structCurrFoundPhase);

    //===========================================
    // Search phase - wDQ
    //===========================================
    DebugMessageMemoryPhaseCal("======================================", 0);
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[6] & Clk[7] & Clk[8] & Clk[9]: DQ====", 0);
    ScalerDDR3OfflineScanPhaseDQ(&structCurrFoundPhase);

    //===========================================
    // Search phase - RdDQSEn Test
    //===========================================
    DebugMessageMemoryPhaseCal("=========================", 0);
    DebugMessageMemoryPhaseCal("====ScanPhase RDDQSEn====", 0);
    ScalerDDR3OfflineScanRdDQSEn();

    //===========================================
    // Search phase - ReadDly
    //===========================================
    DebugMessageMemoryPhaseCal("=========================", 0);
    DebugMessageMemoryPhaseCal("====ScanPhase ReadDly====", 0);
    ScalerDDR3ReadDlytaptest();

    //===========================================
    // Search phase - RXFIFO
    //===========================================
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
    DebugMessageMemoryPhaseCal("========================", 0);
    DebugMessageMemoryPhaseCal("====ScanPhase RXFIFO====", 0);
    ScalerDDR3OfflineScanRxFIFO();
#endif

    //===========================================
    // Search phase - Rx ODT
    //===========================================
    DebugMessageMemoryPhaseCal("========================", 0);
    DebugMessageMemoryPhaseCal("====ScanPhase Rx ODT====", 0);
    ScalerDDR3OfflineScanRxODT();

    DebugMessageMemoryPhaseCal("*******************", 0);
    DebugMessageMemoryPhaseCal("*** DDR3PLL *** fvco=932.998M, N=0x41, F=0x14D ***", 0);
    DebugMessageMemoryPhaseCal("*** DDR3PLL Ncode =", ((Scaler32GetDWord(PB08000_28_SSC3) & 0x0000FF00) >> 8));
    DebugMessageMemoryPhaseCal("*** DDR3PLL Fcode[10:0] =", ((Scaler32GetDWord(PB08000_24_SSC2) & 0xFFFF0000) >> 16));
    DebugMessageMemoryPhaseCal("*** DDR3PLL ~Freq(Mhz) ~=Xtal*Ncode=", (14318 * ((((Scaler32GetDWord(PB08000_28_SSC3)) & 0x0000FF00) >> 8) + 3 + ((Scaler32GetDWord(PB08000_24_SSC2) & 0xFFFF0000) >> 16) / 2048) / 1000));
    DebugMessageMemoryPhaseCal("**********************", 0);
    DebugMessageMemoryPhaseCal("***Cal. Result****", 0);
    DebugMessageMemoryPhaseCal("***** Write Setting*****", 0);
    DebugMessageMemoryPhaseCal("*****  0xB0800010 = ", (DWORD)Scaler32GetDWord(PB08000_10_PLL_PI0));
    DebugMessageMemoryPhaseCal("*****  0xB0800014 = ", (DWORD)Scaler32GetDWord(PB08000_14_PLL_PI1));
    DebugMessageMemoryPhaseCal("*****  0xB0800098 = ", (DWORD)Scaler32GetDWord(PB08000_98_PLL_PI2));
    DebugMessageMemoryPhaseCal("*****  0xB0800080 = ", (DWORD)Scaler32GetDWord(PB08000_80_AFIFO_STR_0));
    DebugMessageMemoryPhaseCal("*****  0xB0800084 = ", (DWORD)Scaler32GetDWord(PB08000_84_AFIFO_STR_1));
    DebugMessageMemoryPhaseCal("*****  0xB0800088 = ", (DWORD)Scaler32GetDWord(PB08000_88_AFIFO_STR_2));
    DebugMessageMemoryPhaseCal("***** Read Setting*****", 0);
    DebugMessageMemoryPhaseCal("*****  0xB08005F8  = ", Scaler32GetDWord(PB08005_F8_READ_CTRL_0));
    DebugMessageMemoryPhaseCal("*****  0xB08005FC  = ", Scaler32GetDWord(PB08005_FC_READ_CTRL_0));
    DebugMessageMemoryPhaseCal("*****  0xB08007F8  = ", Scaler32GetDWord(PB08007_F8_READ_CTRL_0));
    DebugMessageMemoryPhaseCal("*****  0xB08007FC  = ", Scaler32GetDWord(PB08007_FC_READ_CTRL_0));
    DebugMessageMemoryPhaseCal("Rising DQ3~DQ1", Scaler32GetDWord(PB08004_20_DQS_IN_DLY_0));
    DebugMessageMemoryPhaseCal("Rising DQ7~DQ4", Scaler32GetDWord(PB08004_28_DQS_IN_DLY_1));
    DebugMessageMemoryPhaseCal("Rising DQ11~DQ8", Scaler32GetDWord(PB08004_24_DQS_IN_DLY_0));
    DebugMessageMemoryPhaseCal("Rising DQ15~DQ12", Scaler32GetDWord(PB08004_2C_DQS_IN_DLY_1));
    DebugMessageMemoryPhaseCal("Rising DQ19~DQ16", Scaler32GetDWord(PB08006_20_DQS_IN_DLY_0));
    DebugMessageMemoryPhaseCal("Rising DQ23~DQ20", Scaler32GetDWord(PB08006_28_DQS_IN_DLY_1));
    DebugMessageMemoryPhaseCal("Rising DQ27~DQ24", Scaler32GetDWord(PB08006_24_DQS_IN_DLY_0));
    DebugMessageMemoryPhaseCal("Rising DQ31~DQ28", Scaler32GetDWord(PB08006_2C_DQS_IN_DLY_1));
    DebugMessageMemoryPhaseCal("Falling DQ3~DQ1", Scaler32GetDWord(PB08004_38_DQS_IN_DLY_2));
    DebugMessageMemoryPhaseCal("Falling DQ7~DQ4", Scaler32GetDWord(PB08004_40_DQS_IN_DLY_3));
    DebugMessageMemoryPhaseCal("Falling DQ11~DQ8", Scaler32GetDWord(PB08004_3C_DQS_IN_DLY_2));
    DebugMessageMemoryPhaseCal("Falling DQ15~DQ12", Scaler32GetDWord(PB08004_44_DQS_IN_DLY_3));
    DebugMessageMemoryPhaseCal("Falling DQ19~DQ16", Scaler32GetDWord(PB08006_38_DQS_IN_DLY_2));
    DebugMessageMemoryPhaseCal("Falling DQ23~DQ20", Scaler32GetDWord(PB08006_40_DQS_IN_DLY_3));
    DebugMessageMemoryPhaseCal("Falling DQ27~DQ24", Scaler32GetDWord(PB08006_3C_DQS_IN_DLY_2));
    DebugMessageMemoryPhaseCal("Falling DQ31~DQ28", Scaler32GetDWord(PB08006_44_DQS_IN_DLY_3));
    DebugMessageMemoryPhaseCal("RX FIFO", Scaler32GetDWord(PB08001_70_READ_CTRL_1));
    DebugMessageMemoryPhaseCal("0xB0800418", Scaler32GetDWord(PB08004_18_READ_CTRL_6));
    DebugMessageMemoryPhaseCal("0xB080041C", Scaler32GetDWord(PB08004_1C_READ_CTRL_6));
    DebugMessageMemoryPhaseCal("0xB0800618", Scaler32GetDWord(PB08006_18_READ_CTRL_6));
    DebugMessageMemoryPhaseCal("0xB080061C", Scaler32GetDWord(PB08006_1C_READ_CTRL_6));
    DebugMessageMemoryPhaseCal("*******************", 0);
}

//--------------------------------------------------
// Description  : Check DDR R/W correctness of specific phase set
// Input Value  : None
// Output Value : Phase check result
//--------------------------------------------------
bit ScalerDDR3OfflinePhaseCheck(void)
{
    bit bPhaseChkResult = _FAIL;

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
    bPhaseChkResult = ScalerDDR3OfflinePhaseCheckMCUMode();
#elif(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
    bPhaseChkResult = ScalerDDR3OfflinePhaseCheckFRCMode();
#endif

    return bPhaseChkResult;
}
//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineScanPhaseCK(StructDDR3OfflinePhaseInfo *pstCurrResult)
{
    BYTE pucPhaseOfClktestInitial[11] = {0};
    BYTE pucPhaseOfClktest[11] = {0};
    BYTE uctest = 0;
    BYTE ucResult = 0;
    DWORD ulDDR3TXFIFOSTR_0 = 0;
    DWORD ulDDR3TXFIFOSTR_1 = 0;
    BYTE pucScanResultCK[8] = {0};
    BYTE ucCentralValueCK = 0;
    BYTE ucPIDiff = 0;

    //=================================================================
    // Scan for proper phase of CK(Clk0)
    // Clk1, and Clk7 are fixed
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    DebugMessageMemoryPhaseCal("Clk[10]: CS", pucPhaseOfClktestInitial[10]);
    DebugMessageMemoryPhaseCal("Clk[9]: DQ3", pucPhaseOfClktestInitial[9]);
    DebugMessageMemoryPhaseCal("Clk[8]: DQ2", pucPhaseOfClktestInitial[8]);
    DebugMessageMemoryPhaseCal("Clk[7]: DQ1", pucPhaseOfClktestInitial[7]);
    DebugMessageMemoryPhaseCal("Clk[6]: DQ0", pucPhaseOfClktestInitial[6]);
    DebugMessageMemoryPhaseCal("Clk[5]: DQS3", pucPhaseOfClktestInitial[5]);
    DebugMessageMemoryPhaseCal("Clk[4]: DQS2", pucPhaseOfClktestInitial[4]);
    DebugMessageMemoryPhaseCal("Clk[3]: DQS1", pucPhaseOfClktestInitial[3]);
    DebugMessageMemoryPhaseCal("Clk[2]: DQS0", pucPhaseOfClktestInitial[2]);
    DebugMessageMemoryPhaseCal("Clk[1]: CMD", pucPhaseOfClktestInitial[1]);
    DebugMessageMemoryPhaseCal("Clk[0]: CLK", pucPhaseOfClktestInitial[0]);

    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E2032); // cal_set_mode=11 (off-3point); fw_set_mode=10 immediately

    Scaler32SetBit(PB08004_08_READ_CTRL_2, 0xFF3FFFFF, 0x00C00000); // ODT always on
    Scaler32SetBit(PB08004_0C_READ_CTRL_2, 0xFF3FFFFF, 0x00C00000); // ODT always on
    Scaler32SetBit(PB08006_08_READ_CTRL_2, 0xFF3FFFFF, 0x00C00000); // ODT always on
    Scaler32SetBit(PB08006_0C_READ_CTRL_2, 0xFF3FFFFF, 0x00C00000); // ODT always on

    // Triger all DLL setting
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x0000000C); // fw_set_rd_dly
    // Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E2004); // [1:0]fw_set_mode = 'b00 (during no read)

    //=================================================================
    // Scan for Clk0 pass region, phase of Clk1 is fixed to pass value
    //=================================================================
    for(uctest = 0; uctest <= 32; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10] - uctest); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9] - uctest); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8] - uctest); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7] - uctest); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6] - uctest); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5] - uctest); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4] - uctest); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3] - uctest); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2] - uctest); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0] - uctest); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultCK, pucPhaseOfClktest[0], ucResult);
    }

    for(uctest = 0; uctest < 32; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10] + uctest); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9] + uctest); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8] + uctest); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7] + uctest); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6] + uctest); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5] + uctest); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4] + uctest); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3] + uctest); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2] + uctest); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0] + uctest); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultCK, pucPhaseOfClktest[0], ucResult);
    }

    //====================================
    // Pass range of Clk[0] : CLK
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultCK);

    DebugMessageMemoryPhaseCal("*** Clk[0]: CLK ***", 0);

    ucCentralValueCK = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultCK, _SCAN_RESULT_WR_PI);
    ucPIDiff = ucCentralValueCK - pucPhaseOfClktestInitial[0];

    pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10] + ucPIDiff); // CS
    pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9] + ucPIDiff); // DQ3
    pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8] + ucPIDiff); // DQ2
    pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7] + ucPIDiff); // DQ1
    pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6] + ucPIDiff); // DQ0
    pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5] + ucPIDiff); // DQS3
    pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4] + ucPIDiff); // DQS2
    pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3] + ucPIDiff); // DQS1
    pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2] + ucPIDiff); // DQS0
    pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
    pucPhaseOfClktest[0] = (ucCentralValueCK); // CK

    //====================================
    // Update Clk[0] : CK
    //====================================

    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();
}
//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineScanPhaseCS(StructDDR3OfflinePhaseInfo *pstCurrResult)
{
    BYTE pucPhaseOfClktestInitial[11] = {0};
    BYTE pucPhaseOfClktest[11] = {0};
    BYTE uctest = 0;
    BYTE ucResult = 0;
    DWORD ulDDR3TXFIFOSTR_0 = 0;
    DWORD ulDDR3TXFIFOSTR_1 = 0;

    BYTE pucScanResultCS[8] = {0};
    BYTE ucCentralValueCS = 0;
    BYTE ucPIDiff = 0;
    //=================================================================
    // Scan for proper phase of CS,
    // Clk0~Clk5, and Clk7 are fixed
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    DebugMessageMemoryPhaseCal("Clk[10]: CS", pucPhaseOfClktestInitial[10]);
    DebugMessageMemoryPhaseCal("Clk[9]: DQ3", pucPhaseOfClktestInitial[9]);
    DebugMessageMemoryPhaseCal("Clk[8]: DQ2", pucPhaseOfClktestInitial[8]);
    DebugMessageMemoryPhaseCal("Clk[7]: DQ1", pucPhaseOfClktestInitial[7]);
    DebugMessageMemoryPhaseCal("Clk[6]: DQ0", pucPhaseOfClktestInitial[6]);
    DebugMessageMemoryPhaseCal("Clk[5]: DQS3", pucPhaseOfClktestInitial[5]);
    DebugMessageMemoryPhaseCal("Clk[4]: DQS2", pucPhaseOfClktestInitial[4]);
    DebugMessageMemoryPhaseCal("Clk[3]: DQS1", pucPhaseOfClktestInitial[3]);
    DebugMessageMemoryPhaseCal("Clk[2]: DQS0", pucPhaseOfClktestInitial[2]);
    DebugMessageMemoryPhaseCal("Clk[1]: CMD", pucPhaseOfClktestInitial[1]);
    DebugMessageMemoryPhaseCal("Clk[0]: CLK", pucPhaseOfClktestInitial[0]);
    //=================================================================
    // Scan for Clk0 pass region, phase of Clk1 is fixed to pass value
    //=================================================================
    ucPIDiff = 64 - pucPhaseOfClktestInitial[10];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10] + uctest); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultCS, pucPhaseOfClktest[10], ucResult);
    }

    ucPIDiff = pucPhaseOfClktestInitial[10];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10] - uctest); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultCS, pucPhaseOfClktest[10], ucResult);
    }

    //====================================
    // Pass range of Clk[6] =CS
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultCS);

    DebugMessageMemoryPhaseCal("*** Clk[10]: CS ***", 0);

    ucCentralValueCS = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultCS, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[10] = ucCentralValueCS;

    //====================================
    // Update Clk[10] : CS
    //====================================

    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();
}

#if(_SEARCH_PHASE_WRITE_LEVELING == _ON)
//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerDDR3WritleLevleingtest(StructDDR3OfflinePhaseInfo *pstCurrResult)
{
    BYTE pucPhaseOfClktestInitial[11] = {0};
    BYTE pucPhaseOfClktest[11] = {0};
    BYTE uctest = 0;
    DWORD ulDDR3TXFIFOSTR_0 = 0;
    DWORD ulDDR3TXFIFOSTR_1 = 0;

    BYTE pucWLResultDQS0[8] = {0};
    BYTE pucWLResultDQS1[8] = {0};
    BYTE pucWLResultDQS2[8] = {0};
    BYTE pucWLResultDQS3[8] = {0};

    BYTE ucWlValue0 = 0;
    BYTE ucWlValue1 = 0;
    BYTE ucWlValue2 = 0;
    BYTE ucWlValue3 = 0;
    //=================================================================
    // Scan for proper phase of wDQS(Clk2, Clk3)
    // Use Wirte Leveling Function
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    DebugMessageMemoryPhaseCal("Clk[10]: CS", pucPhaseOfClktestInitial[10]);
    DebugMessageMemoryPhaseCal("Clk[9]: DQ3", pucPhaseOfClktestInitial[9]);
    DebugMessageMemoryPhaseCal("Clk[8]: DQ2", pucPhaseOfClktestInitial[8]);
    DebugMessageMemoryPhaseCal("Clk[7]: DQ1", pucPhaseOfClktestInitial[7]);
    DebugMessageMemoryPhaseCal("Clk[6]: DQ0", pucPhaseOfClktestInitial[6]);
    DebugMessageMemoryPhaseCal("Clk[5]: DQS3", pucPhaseOfClktestInitial[5]);
    DebugMessageMemoryPhaseCal("Clk[4]: DQS2", pucPhaseOfClktestInitial[4]);
    DebugMessageMemoryPhaseCal("Clk[3]: DQS1", pucPhaseOfClktestInitial[3]);
    DebugMessageMemoryPhaseCal("Clk[2]: DQS0", pucPhaseOfClktestInitial[2]);
    DebugMessageMemoryPhaseCal("Clk[1]: CMD", pucPhaseOfClktestInitial[1]);
    DebugMessageMemoryPhaseCal("Clk[0]: CLK", pucPhaseOfClktestInitial[0]);

    // Enable write leveling (DRAM MR1 bit7 = 1)
    Scaler32SetBit(PB08200_44_MOD_REG, 0xFF7FFFFF, 0x00800000);
    // Write MR1 to DRAM
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x00000030);
    ScalerTimerDelayXms(2);

    for(uctest = 0; uctest < 16; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5] + uctest); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4] + uctest); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3] + uctest); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2] + uctest); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[6]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        // Set phase control // for test
        ScalerDDR3OfflineSetDDRPLLWritePhasetest(g_ulDDRPLLPhase0, g_ulDDRPLLPhase1, g_ulDDRPLLPhase2, g_ulDDR3TXFIFOSTR0Cal, g_ulDDR3TXFIFOSTR1Cal);

        // (b) enable DQ input and DQS output
        Scaler32SetDWord(PB08004_D8_DQ_IO_CTL_0, 0x0000FFFF); // Enable DQ in
        Scaler32SetDWord(PB08004_DC_DQ_IO_CTL_0, 0x0000FFFF);
        Scaler32SetDWord(PB08006_D8_DQ_IO_CTL_0, 0x0000FFFF);
        Scaler32SetDWord(PB08006_DC_DQ_IO_CTL_0, 0x0000FFFF);
        Scaler32SetBit(PB08001_50_DQ_DQS_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0000000D); // Enable DQS out

        // (c) trigger write leveling DQS pulse
        Scaler32SetBit(PB08001_50_DQ_DQS_CTRL, ~_BIT1, 0x00000002); // Trigger DQS pulse
        // (d) read write leveling result
        PDATA_DWORD(0) = Scaler32GetDWord(PB08001_58_DQ_PAT_IN0);
        // DebugMessageMemoryPhaseCal("PDATA_DWORD(0)", PDATA_DWORD(0));
        SET_BIT_RESULT(pucWLResultDQS0, uctest, ((pData[0] != 0x00) ? _SUCCESS : _FAIL));
        SET_BIT_RESULT(pucWLResultDQS1, uctest, ((pData[1] != 0x00) ? _SUCCESS : _FAIL));
        SET_BIT_RESULT(pucWLResultDQS2, uctest, ((pData[2] != 0x00) ? _SUCCESS : _FAIL));
        SET_BIT_RESULT(pucWLResultDQS3, uctest, ((pData[3] != 0x00) ? _SUCCESS : _FAIL));
    }

    // Disable write leveling (DRAM MR1 bit7 = 0)
    Scaler32SetBit(PB08200_44_MOD_REG, 0xFF7FFFFF, 0x00000000);
    // Write MR1 to DRAM
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x00000030);
    //=================================================================
    // Write leveling result
    //=================================================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucWLResultDQS0);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucWLResultDQS1);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucWLResultDQS2);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucWLResultDQS3);

    DebugMessageMemoryPhaseCal("*** Clk2 ***", 0);
    ucWlValue0 = ScalerDDR3WLFindProperWDQSPhase(pucWLResultDQS0, pucWLResultDQS0);
    pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2] + ucWlValue0);
    pucPhaseOfClktest[6] = (pucPhaseOfClktest[2] + 8);

    DebugMessageMemoryPhaseCal("*** Clk3 ***", 0);
    ucWlValue1 = ScalerDDR3WLFindProperWDQSPhase(pucWLResultDQS1, pucWLResultDQS1);
    pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3] + ucWlValue1);
    pucPhaseOfClktest[7] = (pucPhaseOfClktest[3] + 8);

    DebugMessageMemoryPhaseCal("*** Clk4 ***", 0);
    ucWlValue2 = ScalerDDR3WLFindProperWDQSPhase(pucWLResultDQS2, pucWLResultDQS2);
    pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[3] + ucWlValue2);
    pucPhaseOfClktest[8] = (pucPhaseOfClktest[4] + 8);

    DebugMessageMemoryPhaseCal("*** Clk5 ***", 0);
    ucWlValue3 = ScalerDDR3WLFindProperWDQSPhase(pucWLResultDQS3, pucWLResultDQS3);
    pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[3] + ucWlValue3);
    pucPhaseOfClktest[9] = (pucPhaseOfClktest[5] + 8);

    DebugMessageMemoryPhaseCal("Clk[10]: CS", pucPhaseOfClktest[10]);
    DebugMessageMemoryPhaseCal("Clk[9]: DQ3", pucPhaseOfClktest[9]);
    DebugMessageMemoryPhaseCal("Clk[8]: DQ2", pucPhaseOfClktest[8]);
    DebugMessageMemoryPhaseCal("Clk[7]: DQ1", pucPhaseOfClktest[7]);
    DebugMessageMemoryPhaseCal("Clk[6]: DQ0", pucPhaseOfClktest[6]);
    DebugMessageMemoryPhaseCal("Clk[5]: DQS3", pucPhaseOfClktest[5]);
    DebugMessageMemoryPhaseCal("Clk[4]: DQS2", pucPhaseOfClktest[4]);
    DebugMessageMemoryPhaseCal("Clk[3]: DQS1", pucPhaseOfClktest[3]);
    DebugMessageMemoryPhaseCal("Clk[2]: DQS0", pucPhaseOfClktest[2]);
    DebugMessageMemoryPhaseCal("Clk[1]: CMD", pucPhaseOfClktest[1]);
    DebugMessageMemoryPhaseCal("Clk[0]: CLK", pucPhaseOfClktest[0]);

    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);
    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[6]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);


    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);

    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();

}
//--------------------------------------------------
// Description  : Find proper wDQS phase according to write leveling result
// Input Value  : Array of write leveling result
// Output Value : The central phase of longest pass range
//--------------------------------------------------
BYTE ScalerDDR3WLFindProperWDQSPhase(BYTE pucWLResult0[8], BYTE pucWLResult1[8])
{
    BYTE ucPhaseAlignWithCLK = 0;
    BYTE ucTransPtDQS0 = 0;
    BYTE ucTransPtDQS1 = 0;
    bit bFoundTransPtDQS0 = _FALSE;
    bit bFoundTransPtDQS1 = _FALSE;
    BYTE ucWLResultIndex = 0;

    BYTE ucTransPtLess = 0;
    BYTE ucTransPtGreater = 0;
    BYTE ucTransPtDiff = 0;

    for(ucWLResultIndex = 1; ucWLResultIndex < (64 * 2); ucWLResultIndex++)
    {
        if((bFoundTransPtDQS0 == _FALSE) &&
           (GET_BIT_RESULT(pucWLResult0, (ucWLResultIndex % 64)) == _SUCCESS) &&
           (GET_BIT_RESULT(pucWLResult0, ((ucWLResultIndex - 1) % 64)) == _FAIL))
        {
            ucTransPtDQS0 = ucWLResultIndex % 64;
            bFoundTransPtDQS0 = _TRUE;
        }

        if((bFoundTransPtDQS1 == _FALSE) &&
           (GET_BIT_RESULT(pucWLResult1, (ucWLResultIndex % 64)) == _SUCCESS) &&
           (GET_BIT_RESULT(pucWLResult1, ((ucWLResultIndex - 1) % 64)) == _FAIL))
        {
            ucTransPtDQS1 = ucWLResultIndex % 64;
            bFoundTransPtDQS1 = _TRUE;
        }

        if((bFoundTransPtDQS0 == _TRUE) && (bFoundTransPtDQS1 == _TRUE))
        {
            break;
        }
    }

    ucTransPtLess = (ucTransPtDQS0 < ucTransPtDQS1) ? ucTransPtDQS0 : ucTransPtDQS1;
    ucTransPtGreater = (ucTransPtDQS0 < ucTransPtDQS1) ? ucTransPtDQS1 : ucTransPtDQS0;
    ucTransPtDiff = PI_DIFF(ucTransPtGreater, ucTransPtLess);
    if(ucTransPtDiff > (64 - ucTransPtDiff))
    {
        ucPhaseAlignWithCLK = (((ucTransPtLess + 64) + ucTransPtGreater) / 2) % 64;
    }
    else
    {
        ucPhaseAlignWithCLK = ((ucTransPtLess + ucTransPtGreater) / 2) % 64;
    }

    DebugMessageMemoryPhaseCal("Best Phase:", ucPhaseAlignWithCLK);

    return ucPhaseAlignWithCLK;
}

#endif // End of #if(_SEARCH_PHASE_WRITE_LEVELING == _ON)

//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineScanPhaseDQS(StructDDR3OfflinePhaseInfo *pstCurrResult)
{
    BYTE pucPhaseOfClktestInitial[11] = {0};
    BYTE pucPhaseOfClktest[11] = {0};
    BYTE uctest = 0;
    BYTE ucResult = 0;
    DWORD ulDDR3TXFIFOSTR_0 = 0;
    DWORD ulDDR3TXFIFOSTR_1 = 0;

    BYTE pucScanResultDQS0[8] = {0};
    BYTE pucScanResultDQS1[8] = {0};
    BYTE pucScanResultDQS2[8] = {0};
    BYTE pucScanResultDQS3[8] = {0};
    BYTE ucCentralValueDQS0 = 0;
    BYTE ucCentralValueDQS1 = 0;
    BYTE ucCentralValueDQS2 = 0;
    BYTE ucCentralValueDQS3 = 0;
    BYTE ucPIDiff = 0;

    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    //=================================================================
    // Scan for proper phase of DQS0/1/2/3
    //
    //=================================================================
    DebugMessageMemoryPhaseCal("Clk[10]: CS", pucPhaseOfClktestInitial[10]);
    DebugMessageMemoryPhaseCal("Clk[9]: DQ3", pucPhaseOfClktestInitial[9]);
    DebugMessageMemoryPhaseCal("Clk[8]: DQ2", pucPhaseOfClktestInitial[8]);
    DebugMessageMemoryPhaseCal("Clk[7]: DQ1", pucPhaseOfClktestInitial[7]);
    DebugMessageMemoryPhaseCal("Clk[6]: DQ0", pucPhaseOfClktestInitial[6]);
    DebugMessageMemoryPhaseCal("Clk[5]: DQS3", pucPhaseOfClktestInitial[5]);
    DebugMessageMemoryPhaseCal("Clk[4]: DQS2", pucPhaseOfClktestInitial[4]);
    DebugMessageMemoryPhaseCal("Clk[3]: DQS1", pucPhaseOfClktestInitial[3]);
    DebugMessageMemoryPhaseCal("Clk[2]: DQS0", pucPhaseOfClktestInitial[2]);
    DebugMessageMemoryPhaseCal("Clk[1]: CMD", pucPhaseOfClktestInitial[1]);
    DebugMessageMemoryPhaseCal("Clk[0]: CLK", pucPhaseOfClktestInitial[0]);

    //=================================================================
    // Scan for Clk6 pass region, phase of Clk1 is fixed to pass value
    //=================================================================
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[2] : DQS0 ====", 0);
    ucPIDiff = 64 - pucPhaseOfClktestInitial[2];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6] + uctest); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2] + uctest); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQS0, pucPhaseOfClktest[2], ucResult);
    }

    ucPIDiff = pucPhaseOfClktestInitial[2];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6] - uctest); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2] - uctest); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;
        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQS0, pucPhaseOfClktest[2], ucResult);
    }

    //====================================
    // Pass range of Clk[2] : DQS0
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultDQS0);

    DebugMessageMemoryPhaseCal("*** Clk[2]: DQS0 ***", 0);

    ucCentralValueDQS0 = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultDQS0, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[2] = ucCentralValueDQS0;
    pucPhaseOfClktest[6] = ucCentralValueDQS0 + 8;

    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();

    //=================================================================
    // Scan for proper phase of DQS1(Clk3)
    // C
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[3] : DQS1 ====", 0);
    ucPIDiff = 64 - pucPhaseOfClktestInitial[3];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7] + uctest); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3] + uctest); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQS1, pucPhaseOfClktest[3], ucResult);
    }

    ucPIDiff = pucPhaseOfClktestInitial[3];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7] - uctest); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3] - uctest); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQS1, pucPhaseOfClktest[3], ucResult);
    }

    //====================================
    // Pass range of Clk[7] : DQ1
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultDQS1);

    DebugMessageMemoryPhaseCal("*** Clk[3]: DQS1 ***", 0);

    ucCentralValueDQS1 = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultDQS1, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[3] = ucCentralValueDQS1;
    pucPhaseOfClktest[7] = ucCentralValueDQS1 + 8;

    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();
    //=================================================================
    // Scan for proper phase of DQS2(Clk4)
    // C
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[4] : DQS2 ====", 0);
    ucPIDiff = 64 - pucPhaseOfClktestInitial[4];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8] + uctest); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4] + uctest); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQS2, pucPhaseOfClktest[4], ucResult);
    }

    ucPIDiff = pucPhaseOfClktestInitial[4];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8] - uctest); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4] - uctest); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQS2, pucPhaseOfClktest[4], ucResult);
    }

    //====================================
    // Pass range of Clk[8] : DQ2
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultDQS2);

    DebugMessageMemoryPhaseCal("*** Clk[4]: DQS2 ***", 0);

    ucCentralValueDQS2 = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultDQS2, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[4] = ucCentralValueDQS2;
    pucPhaseOfClktest[8] = ucCentralValueDQS2 + 8;

    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();
    //=================================================================
    // Scan for proper phase of DQS3(Clk5)
    // C
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[5] : DQS3 ====", 0);
    ucPIDiff = 64 - pucPhaseOfClktestInitial[5];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9] + uctest); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5] + uctest); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQS3, pucPhaseOfClktest[5], ucResult);
    }

    ucPIDiff = pucPhaseOfClktestInitial[5];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9] - uctest); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5] - uctest); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQS3, pucPhaseOfClktest[5], ucResult);
    }

    //====================================
    // Pass range of Clk[9] : DQ3
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultDQS3);

    DebugMessageMemoryPhaseCal("*** Clk[5]: DQS3 ***", 0);

    ucCentralValueDQS3 = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultDQS3, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[5] = ucCentralValueDQS3;
    pucPhaseOfClktest[9] = ucCentralValueDQS3 + 8;

    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();

}
//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineScanPhaseDQ(StructDDR3OfflinePhaseInfo *pstCurrResult)
{
    BYTE pucPhaseOfClktestInitial[11] = {0};
    BYTE pucPhaseOfClktest[11] = {0};
    BYTE uctest = 0;
    BYTE ucResult = 0;
    DWORD ulDDR3TXFIFOSTR_0 = 0;
    DWORD ulDDR3TXFIFOSTR_1 = 0;

    BYTE pucScanResultDQ0[8] = {0};
    BYTE pucScanResultDQ1[8] = {0};
    BYTE pucScanResultDQ2[8] = {0};
    BYTE pucScanResultDQ3[8] = {0};
    BYTE ucCentralValueDQ0 = 0;
    BYTE ucCentralValueDQ1 = 0;
    BYTE ucCentralValueDQ2 = 0;
    BYTE ucCentralValueDQ3 = 0;
    BYTE ucPIDiff = 0;

    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    //=================================================================
    // Scan for proper phase of DQ0(Clk6)
    // Clk0~Clk3, and Clk5~Clk7 are fixed
    //=================================================================
    DebugMessageMemoryPhaseCal("Clk[10]: CS", pucPhaseOfClktestInitial[10]);
    DebugMessageMemoryPhaseCal("Clk[9]: DQ3", pucPhaseOfClktestInitial[9]);
    DebugMessageMemoryPhaseCal("Clk[8]: DQ2", pucPhaseOfClktestInitial[8]);
    DebugMessageMemoryPhaseCal("Clk[7]: DQ1", pucPhaseOfClktestInitial[7]);
    DebugMessageMemoryPhaseCal("Clk[6]: DQ0", pucPhaseOfClktestInitial[6]);
    DebugMessageMemoryPhaseCal("Clk[5]: DQS3", pucPhaseOfClktestInitial[5]);
    DebugMessageMemoryPhaseCal("Clk[4]: DQS2", pucPhaseOfClktestInitial[4]);
    DebugMessageMemoryPhaseCal("Clk[3]: DQS1", pucPhaseOfClktestInitial[3]);
    DebugMessageMemoryPhaseCal("Clk[2]: DQS0", pucPhaseOfClktestInitial[2]);
    DebugMessageMemoryPhaseCal("Clk[1]: CMD", pucPhaseOfClktestInitial[1]);
    DebugMessageMemoryPhaseCal("Clk[0]: CLK", pucPhaseOfClktestInitial[0]);

    //=================================================================
    // Scan for Clk6 pass region, phase of Clk1 is fixed to pass value
    //=================================================================
    ucPIDiff = 64 - pucPhaseOfClktestInitial[6];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6] + uctest); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQ0, pucPhaseOfClktest[6], ucResult);
    }

    DebugMessageMemoryPhaseCal("====ScanPhase Clk[6] : DQ0 ====", 0);
    ucPIDiff = pucPhaseOfClktestInitial[6];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6] - uctest); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;
        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQ0, pucPhaseOfClktest[6], ucResult);
    }

    //====================================
    // Pass range of Clk[6] : DQ0
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultDQ0);

    DebugMessageMemoryPhaseCal("*** Clk[6]: DQ0 ***", 0);

    ucCentralValueDQ0 = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultDQ0, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[6] = ucCentralValueDQ0;
    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();

    //=================================================================
    // Scan for proper phase of DQ1(Clk7)
    // C
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[7] : DQ1 ====", 0);
    ucPIDiff = 64 - pucPhaseOfClktestInitial[7];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7] + uctest); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQ1, pucPhaseOfClktest[7], ucResult);
    }
    ucPIDiff = pucPhaseOfClktestInitial[7];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7] - uctest); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQ1, pucPhaseOfClktest[7], ucResult);
    }

    //====================================
    // Pass range of Clk[7] : DQ1
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultDQ1);

    DebugMessageMemoryPhaseCal("*** Clk[7]: DQ1 ***", 0);

    ucCentralValueDQ1 = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultDQ1, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[7] = ucCentralValueDQ1;
    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();

    //=================================================================
    // Scan for proper phase of DQ2(Clk8)
    // C
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[8] : DQ2 ====", 0);
    ucPIDiff = 64 - pucPhaseOfClktestInitial[8];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8] + uctest); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQ2, pucPhaseOfClktest[8], ucResult);
    }

    ucPIDiff = pucPhaseOfClktestInitial[8];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9]); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8] - uctest); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQ2, pucPhaseOfClktest[8], ucResult);
    }

    //====================================
    // Pass range of Clk[8] : DQ2
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultDQ2);

    DebugMessageMemoryPhaseCal("*** Clk[8]: DQ2 ***", 0);

    ucCentralValueDQ2 = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultDQ2, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[8] = ucCentralValueDQ2;
    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();

    //=================================================================
    // Scan for proper phase of DQ3(Clk9)
    // C
    //=================================================================
    memcpy(pucPhaseOfClktestInitial, pstCurrResult->pucWritePIOfClk, 11);
    ucPIDiff = 64 - pucPhaseOfClktestInitial[9];
    for(uctest = 0; uctest < ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9] + uctest); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQ3, pucPhaseOfClktest[9], ucResult);
    }
    DebugMessageMemoryPhaseCal("====ScanPhase Clk[9] : DQ3 ====", 0);


    ucPIDiff = pucPhaseOfClktestInitial[9];
    for(uctest = 0; uctest <= ucPIDiff; uctest++)
    {
        pucPhaseOfClktest[10] = (pucPhaseOfClktestInitial[10]); // CS
        pucPhaseOfClktest[9] = (pucPhaseOfClktestInitial[9] - uctest); // DQ3
        pucPhaseOfClktest[8] = (pucPhaseOfClktestInitial[8]); // DQ2
        pucPhaseOfClktest[7] = (pucPhaseOfClktestInitial[7]); // DQ1
        pucPhaseOfClktest[6] = (pucPhaseOfClktestInitial[6]); // DQ0
        pucPhaseOfClktest[5] = (pucPhaseOfClktestInitial[5]); // DQS3
        pucPhaseOfClktest[4] = (pucPhaseOfClktestInitial[4]); // DQS2
        pucPhaseOfClktest[3] = (pucPhaseOfClktestInitial[3]); // DQS1
        pucPhaseOfClktest[2] = (pucPhaseOfClktestInitial[2]); // DQS0
        pucPhaseOfClktest[1] = (pucPhaseOfClktestInitial[1]); // CMD
        pucPhaseOfClktest[0] = (pucPhaseOfClktestInitial[0]); // CK

        pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
        pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
        pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
        pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
        ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

        pData[7] = 0x00;
        pData[6] = 0x0C;
        pData[5] = 0x00;
        pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
        ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
        pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
        pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
        pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

        pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
        pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
        pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
        pData[7] = 0x00;

        pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
        pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
        pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
        pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

        g_ulDDRPLLPhase0 = PDATA_DWORD(0);
        g_ulDDRPLLPhase1 = PDATA_DWORD(1);
        g_ulDDRPLLPhase2 = PDATA_DWORD(2);

        g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
        g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

        ScalerDDR3OfflineApplyNewPhase();
        ScalerTimerDelayXms(2);
        ucResult = ScalerDDR3OfflinePhaseCheck();

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResultDQ3, pucPhaseOfClktest[9], ucResult);
    }
    //====================================
    // Pass range of Clk[9] : DQ3
    //====================================
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultDQ3);

    DebugMessageMemoryPhaseCal("*** Clk[9]: DQ3 ***", 0);

    ucCentralValueDQ3 = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultDQ3, _SCAN_RESULT_WR_PI);
    pucPhaseOfClktest[9] = ucCentralValueDQ3;
    //====================================
    // Update PI
    //====================================
    memcpy(pstCurrResult->pucWritePIOfClk, pucPhaseOfClktest, 11);

    pData[0] = ((GET_FIFO_VALUE(pucPhaseOfClktest[2]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[6])));
    pData[1] = ((GET_FIFO_VALUE(pucPhaseOfClktest[3]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[7])));
    pData[2] = ((GET_FIFO_VALUE(pucPhaseOfClktest[4]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[8])));
    pData[3] = ((GET_FIFO_VALUE(pucPhaseOfClktest[5]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[9])));
    ulDDR3TXFIFOSTR_0 = PDATA_DWORD(0);

    pData[7] = 0x00;
    pData[6] = 0x0C;
    pData[5] = 0x00;
    pData[4] = ((GET_FIFO_VALUE(pucPhaseOfClktest[10]) << 4) | (GET_FIFO_VALUE(pucPhaseOfClktest[1])));
    ulDDR3TXFIFOSTR_1 = PDATA_DWORD(1);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = GET_PHASE_VALUE(pucPhaseOfClktest[0]);
    pData[1] = GET_PHASE_VALUE(pucPhaseOfClktest[1]);
    pData[2] = GET_PHASE_VALUE(pucPhaseOfClktest[2]);
    pData[3] = GET_PHASE_VALUE(pucPhaseOfClktest[3]);

    pData[4] = GET_PHASE_VALUE(pucPhaseOfClktest[4]);
    pData[5] = GET_PHASE_VALUE(pucPhaseOfClktest[5]);
    pData[6] = GET_PHASE_VALUE(pucPhaseOfClktest[6]);
    pData[7] = 0x00;

    pData[8] = GET_PHASE_VALUE(pucPhaseOfClktest[7]);
    pData[9] = GET_PHASE_VALUE(pucPhaseOfClktest[8]);
    pData[10] = GET_PHASE_VALUE(pucPhaseOfClktest[9]);
    pData[11] = GET_PHASE_VALUE(pucPhaseOfClktest[10]);

    g_ulDDRPLLPhase0 = PDATA_DWORD(0);
    g_ulDDRPLLPhase1 = PDATA_DWORD(1);
    g_ulDDRPLLPhase2 = PDATA_DWORD(2);
    g_ulDDR3TXFIFOSTR0Cal = ulDDR3TXFIFOSTR_0;
    g_ulDDR3TXFIFOSTR1Cal = ulDDR3TXFIFOSTR_1;

    ScalerDDR3OfflineApplyNewPhase();
}

//--------------------------------------------------
// Description  : DDR2 offline phase calibration - scan RdDQ Enable
// Input Value  : Previous phase cal result, current phase cal result
// Output Value : Pass range found      -> _SUCCESS
//                Pass range not found  -> _FAIL
//--------------------------------------------------
void ScalerDDR3OfflineScanRdDQSEn(void)
{
    BYTE ucRDQSEnIndex = 0;
    BYTE pucScanResultRdDQSEn0[8] = {0};
    BYTE pucScanResultRdDQSEn1[8] = {0};
    BYTE pucScanResultRdDQSEn2[8] = {0};
    BYTE pucScanResultRdDQSEn3[8] = {0};
    BYTE *ppucScanResultRdDQSEn[4] = {pucScanResultRdDQSEn0,pucScanResultRdDQSEn1,pucScanResultRdDQSEn2,pucScanResultRdDQSEn3};

    bit bResult0 = 0;
    bit bResult1 = 0;
    bit bResult2 = 0;
    bit bResult3 = 0;

    bit bTransitionPre = 0;
    bit bTransitionCur = 0;
    BYTE ucTransitionIndex = 0;
    BYTE pucTransition[4] = {0};

    // (a) PUPD3
    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E2036); // cal_set_mode=11 (off-3point); fw_set_mode=10 immediately

    Scaler32SetDWord(PB08004_08_READ_CTRL_2, 0x00C00000); // ODT always on
    Scaler32SetDWord(PB08004_0C_READ_CTRL_2, 0x00C00000); // ODT always on
    Scaler32SetDWord(PB08006_08_READ_CTRL_2, 0x00C00000); // ODT always on
    Scaler32SetDWord(PB08006_0C_READ_CTRL_2, 0x00C00000); // ODT always on
    Scaler32SetDWord(PB08001_D0_DQS_P_ODT_SEL, 0x11001100);
    Scaler32SetDWord(PB08001_D4_DQS_P_ODT_SEL, 0x11001100);
    Scaler32SetDWord(PB08001_D8_DQS_N_ODT_SEL, 0x00110011);
    Scaler32SetDWord(PB08001_DC_DQS_N_ODT_SEL, 0x00110011);

    //===========================================================================
    // Scan for transition
    //===========================================================================
    for(ucRDQSEnIndex = 0; ucRDQSEnIndex < 64; ucRDQSEnIndex++)
    {
        Scaler32SetDWord(PB08005_F8_READ_CTRL_0, (DWORD)ucRDQSEnIndex); // RLE1039: RW01
        Scaler32SetDWord(PB08005_FC_READ_CTRL_0, (DWORD)ucRDQSEnIndex);
        Scaler32SetDWord(PB08007_F8_READ_CTRL_0, (DWORD)ucRDQSEnIndex); // RLE1039: RW23
        Scaler32SetDWord(PB08007_FC_READ_CTRL_0, (DWORD)ucRDQSEnIndex);


        // fw_set_rd_dly
        Scaler32SetBit(PB08002_3C_DPI_CTRL_1, 0xFFFFFF3, 0x0000000C); // FW Set Enable
        //-----------------------------------
        // Issue read cmd to DRAM to get DQS
        //-----------------------------------
        ScalerSetByte(P37_00_MCU_DC_CMD, 0xA0);
        ScalerTimerDelayXms(2);

        // PDATA_DWORD(0) = ScalerGetDWord(PA7_B0_INT_STATUS_0_B0);
        PDATA_DWORD(0) = Scaler32GetDWord(PB08002_58_INT_STATUS_0);

        bResult0 = ((pData[0] & _BIT0) == _BIT0 ? _HIGH : _LOW);
        bResult1 = ((pData[0] & _BIT1) == _BIT1 ? _HIGH : _LOW);
        bResult2 = ((pData[0] & _BIT2) == _BIT2 ? _HIGH : _LOW);
        bResult3 = ((pData[0] & _BIT3) == _BIT3 ? _HIGH : _LOW);

        SET_BIT_RESULT(pucScanResultRdDQSEn0, ucRDQSEnIndex, bResult0);
        SET_BIT_RESULT(pucScanResultRdDQSEn1, ucRDQSEnIndex, bResult1);
        SET_BIT_RESULT(pucScanResultRdDQSEn2, ucRDQSEnIndex, bResult2);
        SET_BIT_RESULT(pucScanResultRdDQSEn3, ucRDQSEnIndex, bResult3);

        Scaler32SetDWord(PB08002_54_INT_CTRL, 0x00000030);
        Scaler32SetDWord(PB08002_58_INT_STATUS_0, 0x00000000);
    }

    //====================================
    // Transition of Read DOQS
    //====================================
    DebugMessageMemoryPhaseCal("====dqs_in of data Slice0====", 0);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultRdDQSEn0);

    DebugMessageMemoryPhaseCal("====dqs_in of data Slice1====", 0);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultRdDQSEn1);

    DebugMessageMemoryPhaseCal("====dqs_in of data Slice2====", 0);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultRdDQSEn2);

    DebugMessageMemoryPhaseCal("====dqs_in of data Slice3====", 0);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultRdDQSEn3);


    for(ucTransitionIndex = 0; ucTransitionIndex < 4; ucTransitionIndex++)
    {
        for(ucRDQSEnIndex = 0; ucRDQSEnIndex < 64; ucRDQSEnIndex++)
        {
            bTransitionCur = GET_BIT_RESULT(ppucScanResultRdDQSEn[ucTransitionIndex], ucRDQSEnIndex);

            if((bTransitionCur == _LOW) && (bTransitionPre == _HIGH))
            {
                pucTransition[ucTransitionIndex] = ucRDQSEnIndex;
                DebugMessageMemoryPhaseCal("Transition", pucTransition[ucTransitionIndex]);
                break;
            }
            bTransitionPre = bTransitionCur;
        }
    }

    Scaler32SetDWord(PB08005_F8_READ_CTRL_0, (DWORD)pucTransition[0]);
    Scaler32SetDWord(PB08005_FC_READ_CTRL_0, (DWORD)pucTransition[1]);
    Scaler32SetDWord(PB08007_F8_READ_CTRL_0, (DWORD)pucTransition[2]);
    Scaler32SetDWord(PB08007_FC_READ_CTRL_0, (DWORD)pucTransition[3]);

    // Triger all DLL setting
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x0000000C); // fw_set_rd_dly

    Scaler32SetDWord(PB08001_D0_DQS_P_ODT_SEL, 0x00110011);
    Scaler32SetDWord(PB08001_D4_DQS_P_ODT_SEL, 0x00110011);
    Scaler32SetDWord(PB08001_D8_DQS_N_ODT_SEL, 0x11001100);
    Scaler32SetDWord(PB08001_DC_DQS_N_ODT_SEL, 0x11001100);

    Scaler32SetDWord(PB08004_08_READ_CTRL_2, 0x00000000); // ODT always on disable
    Scaler32SetDWord(PB08004_0C_READ_CTRL_2, 0x00000000); // ODT always on disable
    Scaler32SetDWord(PB08006_08_READ_CTRL_2, 0x00000000); // ODT always on disable
    Scaler32SetDWord(PB08006_0C_READ_CTRL_2, 0x00000000); // ODT always on disable

    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E2004); // [1:0]fw_set_mode = 'b00 (during no read)

}

//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------

void ScalerDDR3ReadDlytaptest(void)
{
    BYTE ucChkResByte = 0;
    BYTE pucScanResultRisingDly[8] = {0};
    BYTE pucScanResultFallingDly[8] = {0};
    BYTE ucCentralValueRisingDly = 0;
    BYTE ucCentralValueFallingDly = 0;
    BYTE ucDQI = 0;
    BYTE ucDQRDDly = 0;
    DWORD pusDlytapRisingReg[] =
    {
        PB08004_20_DQS_IN_DLY_0,
        PB08004_28_DQS_IN_DLY_1,
        PB08004_24_DQS_IN_DLY_0,
        PB08004_2C_DQS_IN_DLY_1,
        PB08006_20_DQS_IN_DLY_0,
        PB08006_28_DQS_IN_DLY_1,
        PB08006_24_DQS_IN_DLY_0,
        PB08006_2C_DQS_IN_DLY_1,
    };

    DWORD pusDlytapFallingReg[] =
    {
        PB08004_38_DQS_IN_DLY_2,
        PB08004_40_DQS_IN_DLY_3,
        PB08004_3C_DQS_IN_DLY_2,
        PB08004_44_DQS_IN_DLY_3,
        PB08006_38_DQS_IN_DLY_2,
        PB08006_40_DQS_IN_DLY_3,
        PB08006_3C_DQS_IN_DLY_2,
        PB08006_44_DQS_IN_DLY_3,
    };

    //=========================
    //=== SCAN RX Delay tap==
    //=========================
    DebugMessageMemoryPhaseCal("Rising DQ3~DQ1", Scaler32GetDWord(PB08004_20_DQS_IN_DLY_0));
    DebugMessageMemoryPhaseCal("Rising DQ7~DQ4", Scaler32GetDWord(PB08004_28_DQS_IN_DLY_1));
    DebugMessageMemoryPhaseCal("Rising DQ11~DQ8", Scaler32GetDWord(PB08004_24_DQS_IN_DLY_0));
    DebugMessageMemoryPhaseCal("Rising DQ15~DQ12", Scaler32GetDWord(PB08004_2C_DQS_IN_DLY_1));
    DebugMessageMemoryPhaseCal("Rising DQ19~DQ16", Scaler32GetDWord(PB08006_20_DQS_IN_DLY_0));
    DebugMessageMemoryPhaseCal("Rising DQ23~DQ20", Scaler32GetDWord(PB08006_28_DQS_IN_DLY_1));
    DebugMessageMemoryPhaseCal("Rising DQ27~DQ24", Scaler32GetDWord(PB08006_24_DQS_IN_DLY_0));
    DebugMessageMemoryPhaseCal("Rising DQ31~DQ28", Scaler32GetDWord(PB08006_2C_DQS_IN_DLY_1));
    DebugMessageMemoryPhaseCal("Falling DQ3~DQ1", Scaler32GetDWord(PB08004_38_DQS_IN_DLY_2));
    DebugMessageMemoryPhaseCal("Falling DQ7~DQ4", Scaler32GetDWord(PB08004_40_DQS_IN_DLY_3));
    DebugMessageMemoryPhaseCal("Falling DQ11~DQ8", Scaler32GetDWord(PB08004_3C_DQS_IN_DLY_2));
    DebugMessageMemoryPhaseCal("Falling DQ15~DQ12", Scaler32GetDWord(PB08004_44_DQS_IN_DLY_3));
    DebugMessageMemoryPhaseCal("Falling DQ19~DQ16", Scaler32GetDWord(PB08006_38_DQS_IN_DLY_2));
    DebugMessageMemoryPhaseCal("Falling DQ23~DQ20", Scaler32GetDWord(PB08006_40_DQS_IN_DLY_3));
    DebugMessageMemoryPhaseCal("Falling DQ27~DQ24", Scaler32GetDWord(PB08006_3C_DQS_IN_DLY_2));
    DebugMessageMemoryPhaseCal("Falling DQ31~DQ28", Scaler32GetDWord(PB08006_44_DQS_IN_DLY_3));
    //---------------------------
    // DPI setting
    //---------------------------
    Scaler32SetBit(PB08001_70_READ_CTRL_1, ~_BIT10, 0x00000000); // rd_dly_follow_dq0 =0

    // Disable on the fly calibration function
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00000032);
    // Delay Time us [5,x] Waiting for DDR3 setting
    DELAY_5US();

    //===========================================================================
    // Scan RDQ dly tap - rising
    //===========================================================================
    DebugMessageMemoryPhaseCal("**********************", 0);
    DebugMessageMemoryPhaseCal("=== RDQ DLY Rising===", 0);
    DebugMessageMemoryPhaseCal("**********************", 0);

    for(ucDQI = 0; ucDQI < 32; ucDQI++)
    {
        BYTE ucRegI = ucDQI / 4;
        BYTE ucByteI = ucDQI % 4;

        for(ucDQRDDly = 0; ucDQRDDly < 32; ucDQRDDly++)
        {
            PDATA_DWORD(0) = Scaler32GetDWord(pusDlytapRisingReg[ucRegI]) & ~(0xFFUL << (ucByteI * 8));
            PDATA_DWORD(0) |= ((DWORD)ucDQRDDly << (ucByteI * 8));
            Scaler32SetDWord(pusDlytapRisingReg[ucRegI], PDATA_DWORD(0));

            // fw_set_rd_dly
            Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);

            ucChkResByte = ScalerDDR3OfflinePhaseCheck();

            // Save check result to result buffer
            SET_BIT_RESULT(pucScanResultRisingDly, ucDQRDDly, ucChkResByte);
        }

        //====================================
        // Pass range
        //====================================
        DebugMessageMemoryPhaseCal(" DQ = ", ucDQI);
        ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultRisingDly);
        ucCentralValueRisingDly = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultRisingDly, _SCAN_RESULT_RD_DLY_TAP);
        // set the Best Delay Tap
        PDATA_DWORD(0) = Scaler32GetDWord(pusDlytapRisingReg[ucRegI]) & ~(0xFFUL << (ucByteI * 8));
        PDATA_DWORD(0) |= ((DWORD)ucCentralValueRisingDly << (ucByteI * 8));
        Scaler32SetDWord(pusDlytapRisingReg[ucRegI], PDATA_DWORD(0));

        // fw_set_rd_dly
        Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);
    }


    //===========================================================================
    // Scan RDQ dly tap - Falling
    //===========================================================================

    DebugMessageMemoryPhaseCal("**********************", 0);
    DebugMessageMemoryPhaseCal("=== RDQ DLY Falling===", 0);
    DebugMessageMemoryPhaseCal("**********************", 0);

    for(ucDQI = 0; ucDQI < 32; ucDQI++)
    {
        BYTE ucRegI = ucDQI / 4;
        BYTE ucByteI = ucDQI % 4;

        for(ucDQRDDly = 0; ucDQRDDly < 32; ucDQRDDly++)
        {
            PDATA_DWORD(0) = Scaler32GetDWord(pusDlytapFallingReg[ucRegI]) & ~(0xFFUL << (ucByteI * 8));
            PDATA_DWORD(0) |= ((DWORD)ucDQRDDly << (ucByteI * 8));
            Scaler32SetDWord(pusDlytapFallingReg[ucRegI], PDATA_DWORD(0));

            // fw_set_rd_dly
            Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);

            ucChkResByte = ScalerDDR3OfflinePhaseCheck();
            // Save check result to result buffer
            SET_BIT_RESULT(pucScanResultFallingDly, ucDQRDDly, ucChkResByte);
        }

        //====================================
        // Pass range
        //====================================
        DebugMessageMemoryPhaseCal(" DQ = ", ucDQI);
        ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultFallingDly);
        ucCentralValueFallingDly = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultFallingDly, _SCAN_RESULT_RD_DLY_TAP);
        // set the Best Delay Tap
        PDATA_DWORD(0) = Scaler32GetDWord(pusDlytapFallingReg[ucRegI]) & ~(0xFFUL << (ucByteI * 8));
        PDATA_DWORD(0) |= ((DWORD)ucCentralValueFallingDly << (ucByteI * 8));
        Scaler32SetDWord(pusDlytapFallingReg[ucRegI], PDATA_DWORD(0));

        // fw_set_rd_dly
        Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);
    }

    // ScalerMaskSetDWord(PA6_54_READ_CTRL_1_54, 0xFFFFFBFF, 0x00000000); // rd_dly_follow_dq0 =0
    Scaler32SetBit(PB08001_70_READ_CTRL_1, ~_BIT10, 0x00000000); // rd_dly_follow_dq0 =0

    // fw_set_rd_dly
    Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);

    // Enable on the fly calibration function
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00000000);
}

//--------------------------------------------------
// Description  : DDR3 offline phase calibration - scan Rx FIFO
// Input Value  : Previous phase cal result, current phase cal result
// Output Value : Pass range found      -> _SUCCESS
//                Pass range not found  -> _FAIL
//--------------------------------------------------
void ScalerDDR3OfflineScanRxFIFO(void)
{
    // BYTE ucDQIndex = 0;
    BYTE ucRxFIFOIndex = 0;
    BYTE ucChkResByte = 0;
    BYTE pucScanResult[8] = {0};
    BYTE ucRXFIFO = 0;

    //===========================================================================
    // DPI setting
    //===========================================================================
    // FW set mode = 'b10 (immediately)
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00000032);
    //===========================================================================
    // Scan Rx FIFO
    //===========================================================================
    for(ucRxFIFOIndex = 0; ucRxFIFOIndex < 32; ucRxFIFOIndex++)
    {
        // Set Rx FIFO Latency
        Scaler32SetDWord(PB08001_70_READ_CTRL_1, (DWORD)ucRxFIFOIndex);
        // fw_set_rd_dly
        Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);

        // Phase check
        ucChkResByte = ScalerDDR3OfflinePhaseCheck();

#if(_PHASE_CHK_DEBUG_MSG == _ON)
        DebugMessageMemoryPhaseCal("RXFIFO Index", ucRxFIFOIndex);
        DebugMessageMemoryPhaseCal("RXFIFO Result", ucChkResByte);
#endif

        Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT3 | _BIT2), 0x0000000C); // reset fifo
        Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT3 | _BIT2), 0x00000008); // disable reset
        Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT3 | _BIT2), 0x00000004); // during refresh

        // Save check result to result buffer
        SET_BIT_RESULT(pucScanResult, ucRxFIFOIndex, ucChkResByte);
    }

    // Print scan result
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResult);
    ucRXFIFO = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResult, _SCAN_RESULT_RX_FIFO);

    // TODO: resume Rx FIFO setting to default value
    // Set Rx FIFO
    Scaler32SetBit(PB08001_70_READ_CTRL_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (DWORD)ucRXFIFO);
    // fw_set_rd_dly
    Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);
    // fw_set_rd_dly
    // Scaler32SetBit(PB08002_38_DPI_CTRL_0, 0xFFFFFFCC, 0x00000000); // cal_set_mode=00 (ON-3point); fw_set_mode=00
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00000000);
}

//--------------------------------------------------
// Description  : DDR3 offline phase calibration - scan Rx ODT
// Input Value  : Previous phase cal result, current phase cal result
// Output Value : Pass range found      -> _SUCCESS
//                Pass range not found  -> _FAIL
//--------------------------------------------------
void ScalerDDR3OfflineScanRxODT(void)
{
    BYTE ucRxODTIndex = 0;
    BYTE ucChkResByte = 0;
    BYTE ucODTBoundryBeg = 0;
    BYTE ucODTBoundryEnd = 0;

    DWORD ulODTMapTmpBegin = 0;
    DWORD ulODTMapTmpEnd = 0;
    DWORD ulODTMapTmp = 0;

    DWORD ultmodten300 = 0;
    DWORD ultmodten = 0;
    BYTE pucScanResultStart[8] = {0};
    BYTE pucScanResultEnd[8] = {0};

    // FW set mode = 'b10 (immediately)
    // Disable on the fly calibration function
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00000032);

    // ODT not always on, odt_en = 0xFFFFF
    Scaler32SetBit(PB08004_08_READ_CTRL_2, ~(_BIT23 | _BIT22 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
    Scaler32SetBit(PB08004_0C_READ_CTRL_2, ~(_BIT23 | _BIT22 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
    Scaler32SetBit(PB08006_08_READ_CTRL_2, ~(_BIT23 | _BIT22 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
    Scaler32SetBit(PB08006_0C_READ_CTRL_2, ~(_BIT23 | _BIT22 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);

    Scaler32SetDWord(PB08004_18_READ_CTRL_6, 0xFFFFFFFF); // odt_en = FFFFF
    Scaler32SetDWord(PB08004_1C_READ_CTRL_6, 0xFFFFFFFF);
    Scaler32SetDWord(PB08006_18_READ_CTRL_6, 0xFFFFFFFF);
    Scaler32SetDWord(PB08006_1C_READ_CTRL_6, 0xFFFFFFFF);

    //===========================================================================
    // Scan Rx ODT map - Begin
    //===========================================================================
    for(ucRxODTIndex = 0; ucRxODTIndex < 32; ucRxODTIndex++)
    {
        ultmodten300 = ((DWORD)0xFFFFFFFF << ucRxODTIndex) & 0x7FFFFFFF;

        // a
        Scaler32SetBit(PB08004_08_READ_CTRL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
        Scaler32SetBit(PB08004_0C_READ_CTRL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
        Scaler32SetBit(PB08006_08_READ_CTRL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
        Scaler32SetBit(PB08006_0C_READ_CTRL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);

        ultmodten = (0x80000000 | ultmodten300);
        Scaler32SetDWord(PB08004_18_READ_CTRL_6, ultmodten); // odt_en = FFFFF
        Scaler32SetDWord(PB08004_1C_READ_CTRL_6, ultmodten);
        Scaler32SetDWord(PB08006_18_READ_CTRL_6, ultmodten);
        Scaler32SetDWord(PB08006_1C_READ_CTRL_6, ultmodten);

        // fw_set_rd_dly
        Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);
        DELAY_5US();
        // Phase check
        ucChkResByte = ScalerDDR3OfflinePhaseCheck();
        SET_BIT_RESULT(pucScanResultStart, ucRxODTIndex, ucChkResByte);

#if(_PHASE_CHK_DEBUG_MSG == _ON)
        DebugMessageMemoryPhaseCal("PB08004_18_READ_CTRL_6", Scaler32GetDWord(PB08004_18_READ_CTRL_6));
        DebugMessageMemoryPhaseCal("ODT Map uctest", ucRxODTIndex);
        DebugMessageMemoryPhaseCal("ODT Map result", ucChkResByte);
#endif
    }
    //===========================================================================
    // Scan Rx ODT map - End
    //===========================================================================
    ultmodten = 0xFFFFFFFF;

    for(ucRxODTIndex = 0; ucRxODTIndex < 32; ucRxODTIndex++)
    {
        ultmodten300 = ((DWORD)0xFFFFFFFF >> ucRxODTIndex);

        // ODT not always on, odt_en = 0xFFFFF
        Scaler32SetBit(PB08004_08_READ_CTRL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
        Scaler32SetBit(PB08004_0C_READ_CTRL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
        Scaler32SetBit(PB08006_08_READ_CTRL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
        Scaler32SetBit(PB08006_0C_READ_CTRL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);

        Scaler32SetDWord(PB08004_18_READ_CTRL_6, ultmodten300); // odt_en = FFFFF
        Scaler32SetDWord(PB08004_1C_READ_CTRL_6, ultmodten300);
        Scaler32SetDWord(PB08006_18_READ_CTRL_6, ultmodten300);
        Scaler32SetDWord(PB08006_1C_READ_CTRL_6, ultmodten300);

        // fw_set_rd_dly
        Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);
        DELAY_5US();
        // Phase check
        ucChkResByte = ScalerDDR3OfflinePhaseCheck();
        SET_BIT_RESULT(pucScanResultEnd, ucRxODTIndex, ucChkResByte);

#if(_PHASE_CHK_DEBUG_MSG == _ON)
        DebugMessageMemoryPhaseCal("PB08004_18_READ_CTRL_6", Scaler32GetDWord(PB08004_18_READ_CTRL_6));
        DebugMessageMemoryPhaseCal("ODT Map uctest", ucRxODTIndex);
        DebugMessageMemoryPhaseCal("ODT Map result", ucChkResByte);
#endif
    }

    // Print scan result
    DebugMessageMemoryPhaseCal("===ODT Map Start===", ucRxODTIndex);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultStart);
    ucODTBoundryBeg = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultStart, _SCAN_RESULT_RX_ODT);
    ulODTMapTmpBegin = ((DWORD)0xFFFFFFFF << ucODTBoundryBeg) & 0x7FFFFFFF;

    DebugMessageMemoryPhaseCal("===ODT Map End===", ucRxODTIndex);
    ScalerDDR3OfflineScanPhasePrintScanResult(pucScanResultEnd);
    ucODTBoundryEnd = ScalerDDR3OfflineFindCentralValueOfLongestPassRange(pucScanResultEnd, _SCAN_RESULT_RX_ODT);
    ulODTMapTmpEnd = ((DWORD)0xFFFFFFFF >> ucODTBoundryEnd);

    ulODTMapTmp = (ulODTMapTmpBegin & ulODTMapTmpEnd);
    DebugMessageMemoryPhaseCal("ulODTMapTmp", ulODTMapTmp);

    // odt_en length = Request length + 0.5T (1T = DDRPLL)
    Scaler32SetDWord(PB08004_08_READ_CTRL_2, 0x00000000);
    Scaler32SetDWord(PB08004_0C_READ_CTRL_2, 0x00000000);
    Scaler32SetDWord(PB08006_08_READ_CTRL_2, 0x00000000);
    Scaler32SetDWord(PB08006_0C_READ_CTRL_2, 0x00000000);
    // odt_en dealy
    Scaler32SetDWord(PB08004_18_READ_CTRL_6, ulODTMapTmp); // odt_en = FFFFF
    Scaler32SetDWord(PB08004_1C_READ_CTRL_6, ulODTMapTmp);
    Scaler32SetDWord(PB08006_18_READ_CTRL_6, ulODTMapTmp);
    Scaler32SetDWord(PB08006_1C_READ_CTRL_6, ulODTMapTmp);

    // fw_set_rd_dly
    Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT3 | _BIT2), 0x0000000C);
    DELAY_5US();
    // Enable on the fly calibration function
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00000000);
}

//--------------------------------------------------
// Description  : Reset memory related blocks
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineApplyNewPhase(void)
{
    //------------------------------
    // Reset DC Sys
    //------------------------------
    ScalerSetBit(P33_A0_M_DOMAIN_SB_RESET_A, ~_BIT1, _BIT1);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P33_A0_M_DOMAIN_SB_RESET_A, ~_BIT1, 0x00);
    ScalerTimerDelayXms(2);
    ScalerDDR3DCSysInitial();

    //------------------------------
    // Reset DC PHY
    //------------------------------
    // Set DDRPLL ICG_clk_en Disable
    Scaler32SetBit(PB08000_04_PLL_CTL0, ~(_BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);

    // Set DDRPLL clk_oe Disable
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT18 | _BIT17 | _BIT16), 0x00000000);
    // PLL LDO reset
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);

    ScalerSetBit(P33_90_M_DOMAIN_MCLK_SET_A, ~_BIT2, 0x00);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P33_90_M_DOMAIN_MCLK_SET_A, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(2);

    ScalerDDR3OfflineSetDDRPLLFreqtest((DWORD)_MEMORY_DATA_RATE_SPEED * 1000);

    // Init DC PHY
    ScalerDDR3DCPHYInitial();

    ScalerTimerDelayXms(2);
}

//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineSetDDRPLLFreqtest(DWORD ulFreq)
{
    // change DDR3 Data Rate to Clock Rate (Khz)
    ulFreq = ulFreq / 2;

    // release PLL LDO reset
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000009);

    // Clock Tree: Dpi_vout_ext_sel = 1b'0 (from DVDD), VCO: Dpi_pll_ext_sel =  1b'1(from LDO)
    Scaler32SetDWord(PB08000_5C_PLL_CTL6, 0x00000002);

    // Clock tree power from DVDD
    Scaler32SetDWord(PB08000_0C_PLL_CTL2, 0x0000000F);

    //===========================
    // PLL initial value setting
    //===========================

    // Set Icp 'b100, cco_kvco 'b1, reg_cco_band for CLK(HZ) 400MHz~1600MHz
    if(ulFreq >= 900000)
    {
        pData[3] = 0x77;
    }
    else if((ulFreq < 900000) && (ulFreq >= 650000))
    {
        pData[3] = 0x76;
    }
    else if((ulFreq < 650000) && (ulFreq >= 530000))
    {
        pData[3] = 0x75;
    }
    else
    {
        pData[3] = 0x74;
    }

    // Set LPF_SR '011, LPF_CP 'b1, loop_PI_Isel
    if(ulFreq >= 1000000)
    {
        pData[2] = 0x76;
    }
    else if((ulFreq < 1000000) && (ulFreq > 800000))
    {
        pData[2] = 0x75;
    }
    else if((ulFreq <= 800000) && (ulFreq >= 600000))
    {
        pData[2] = 0x74;
    }
    else if((ulFreq < 600000) && (ulFreq >= 400000))
    {
        pData[2] = 0x73;
    }
    else
    {
        pData[2] = 0x72;
    }

    // Set post_PI_bias[0], PLL_SEL_CPMODE,  PLL_LDO_Vsel 'b010, PreDiv 'b0
    if(ulFreq >= 800000)
    {
        pData[1] = 0x60;
    }
    else if((ulFreq < 800000) && (ulFreq >= 500000))
    {
        pData[1] = 0xE8;
    }
    else
    {
        pData[1] = 0x60;
    }

    // Set V11_LDO_Vsel , CkRef_Sel = 1'b1(CKREF_TOP), post_PI_RS, post_PI_RL, post_PI_bias[1]
    if(ulFreq >= 800000)
    {
        pData[0] = 0x05; // CLKREFPAD
    }
    else if((ulFreq < 800000) && (ulFreq >= 500000))
    {
        pData[0] = 0x02;
    }
    else
    {
        pData[0] = 0x00;
    }

    Scaler32SetDWord(PB08000_18_PLL_CTL3, (((DWORD)pData[0] << 24) | ((DWORD)pData[1] << 16) | ((DWORD)pData[2] << 8) | ((DWORD)pData[3])));

    // Set Ncode, Fcode
#if(_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_3)
    // _DDR_PLL_CLOCK, 933M, 800M, 667M, 533M.
    if((ulFreq == ((DWORD)_FW_DDR_PLL_CLOCK * 1000)))
    {
#if(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_1066MHZ)
        Scaler32SetBit(PB08000_28_SSC3, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8), (0x00000047 << 8));
        Scaler32SetBit(PB08000_24_SSC2, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28 | _BIT27 | _BIT26 | _BIT25 | _BIT24 | _BIT23 | _BIT22 | _BIT21 | _BIT20 | _BIT19 | _BIT18 | _BIT17 | _BIT16), (0x000003E4 << 16));
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_933MHZ)
        Scaler32SetBit(PB08000_28_SSC3, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8), (0x0000003E << 8));
        Scaler32SetBit(PB08000_24_SSC2, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28 | _BIT27 | _BIT26 | _BIT25 | _BIT24 | _BIT23 | _BIT22 | _BIT21 | _BIT20 | _BIT19 | _BIT18 | _BIT17 | _BIT16), (0x0000014D << 16));
#endif
    }
    else
#endif
    {
        //=============================================
        // Calculate Freq. & Set N F code & Disable SSC
        //=============================================
        BYTE ucNCode = 0;
        DWORD ulNCodeFreq = 0;
        DWORD ulFCode = 0;

        ucNCode = ulFreq / (DWORD)_EXT_XTAL;

        // Calculate DDRPLL Output Freq. According to current Settings
        ulNCodeFreq = (DWORD)_EXT_XTAL * 1000 * ucNCode;

        // Offset resolution (Dclk / 2^11) in Hz
        ulFCode = ((DWORD)_EXT_XTAL * 1000 + (1 << 10)) >> 11;

        // Target frequency of DDR clk in Hz
        ulFCode = ((ulFreq * 1000) - ulNCodeFreq / ulFCode);
        ulFCode = ulFCode & 0x3ff;

        // Set DDR PLL N code / Offset / SSC Enable bit
        ucNCode = ucNCode - ((ucNCode >= 3) ? 3 : 0);

        // Set Ncode
        Scaler32SetBit(PB08000_28_SSC3, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8), ((DWORD)ucNCode << 8));

        // Set Fcode
        Scaler32SetBit(PB08000_24_SSC2, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28 | _BIT27 | _BIT26 | _BIT25 | _BIT24 | _BIT23 | _BIT22 | _BIT21 | _BIT20 | _BIT19 | _BIT18 | _BIT17 | _BIT16), (ulFCode << 16));
    }

    // _DDR3_PLL_INITIAL_PHASE_0 = {ck[0],ck[1],ck[2],ck[3]}
    // _DDR3_PLL_INITIAL_PHASE_0 = {ck, cmd, dqs_0, dqs_1}

    // _DDR3_PLL_INITIAL_PHASE_1 = {ck[4],ck[5],ck[6], int_ck}
    // _DDR3_PLL_INITIAL_PHASE_1 = {dqs_2, dqs_3, dq_0, int_ck}

    // _DDR3_PLL_INITIAL_PHASE_1 = {ck[7],ck[8],ck[9],ck[10]}
    // _DDR3_PLL_INITIAL_PHASE_1 = {dq_1, dq_2, dq_3, CS}

    // Set phase control
    ScalerDDR3OfflineSetDDRPLLWritePhasetest(g_ulDDRPLLPhase0, g_ulDDRPLLPhase1, g_ulDDRPLLPhase2, g_ulDDR3TXFIFOSTR0Cal, g_ulDDR3TXFIFOSTR1Cal);

    // Set WD disable
    Scaler32SetBit(PB08000_2C_WDOG, ~(_BIT0), 0x00000000);

    // Set SSC disable
    Scaler32SetBit(PB08000_1C_SSC0, ~(_BIT1), 0x00000000);

// (a) DCC initial value setting

    // Set DQS1 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_34_DCC_DQS, 0x15053833);

    // Set DQS2 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_38_DCC_DQS, 0x15053833);

    // Set DQS3 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_3C_DCC_DQS, 0x15053833);

    // Set DQS4 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_40_DCC_DQS, 0x15053833);

    // Set DQ1 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_44_DCC_DQ, 0x15053833);

    // Set DQ2 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_48_DCC_DQ, 0x15053833);

    // Set DQ3 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_4C_DCC_DQ, 0x15053833);

    // Set DQ4 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_50_DCC_DQ, 0x15053833);

    // Set CK_1 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_54_DCC_CK, 0x15053833);

    // Set CMD close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_30_DCC_CMD, 0x15053833);

    // Set CS close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_A4_DCC_CS, 0x15053833);

    // Set CS1 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_A8_DCC_CS1, 0x15053833);

// ( b ) DPI initial value setting

    // Set mode & pin mux setting (choose one mode)
    Scaler32SetDWord(PB08000_00_CRT_CTL, 0x0C000821);// DDR3

    // Release SSC NFCODE sync_reset Set rst_n = 1, b1 & ptr_rst_n = 1'b1
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT1), 0x00000002);

    // Enable mck_mc Set mck_mc_en = 1
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT31), 0x80000000);

    // Set ptr_rst_n = 1'b0
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3), 0x00000000);

    // Set rst_n = 1'b1
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT2), 0x00000004);

    // Set ptr_rst_n = 1'b1
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3), 0x00000008);

    // Set OC_EN, ensure N_code, F_code load successfully
    Scaler32SetBit(PB08000_28_SSC3, ~(_BIT26), 0x04000000);// OC_EN 0->1
    Scaler32SetBit(PB08000_28_SSC3, ~(_BIT26), 0x00000000);// OC_EN 1->0

    // Set Flag_initial = 1
    Scaler32SetBit(PB08000_1C_SSC0, ~(_BIT3), 0x00000008);

    // (d) Turn on clock flow
    // Set ICG_clk_en
    Scaler32SetBit(PB08000_04_PLL_CTL0, ~(_BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00001FFF);
    // Set clk_oe Enable
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT18 | _BIT17 | _BIT16), 0x00070000);

    ScalerTimerDelayXms(2);
    Scaler32SetDWord(PB08000_00_CRT_CTL, 0x04000021);// DDR3 Modify

    // Wait for DDR3PLL Stable (2ms)
    ScalerTimerDelayXms(2);

    // Debug
    DebugMessageDigital("6. DDR3PLL *** fvco=932.998M, N=0x41, F=0x14D ***", 0);
    DebugMessageDigital("6. DDR3DPLL Ncode =", ((Scaler32GetDWord(PB08000_28_SSC3) & 0x0000FF00) >> 8));
    DebugMessageDigital("6. DDR3DPLL Fcode[10:0] =", ((Scaler32GetDWord(PB08000_24_SSC2) & 0xFFFF0000) >> 16));
    DebugMessageDigital("6. DDR3DPLL ~Freq(Mhz) ~=Xtal*Ncode=", (14318 * ((((Scaler32GetDWord(PB08000_28_SSC3)) & 0x0000FF00) >> 8) + 3 + ((Scaler32GetDWord(PB08000_24_SSC2) & 0xFFFF0000) >> 16) / 2048) / 1000));
    DebugMessageDigital("6. DDR3DPLL **********************", 0);
}

//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineSetDDRPLLWritePhasetest(DWORD ulDDRPLLInitPhase0, DWORD ulDDRPLLInitPhase1, DWORD ulDDRPLLInitPhase2, DWORD ulDDR3TXFIFOSTR0Cal, DWORD ulDDR3TXFIFOSTR1Cal)
{
    BYTE ucSyncSel_0 = 0x00;
    BYTE ucSyncSel_1 = 0x00;
    BYTE pucPhaseOfClk[11];
    BYTE ucCmdRdStrNumSel = 0x00;

    // _DDR3_PLL_INITIAL_PHASE_0 = {ck[3],ck[2],ck[1],ck[0]}
    // _DDR3_PLL_INITIAL_PHASE_0 = {dqs_1, dqs_0, cmd, ck}
    Scaler32SetDWord(PB08000_10_PLL_PI0, ulDDRPLLInitPhase0);

    // _DDR3_PLL_INITIAL_PHASE_1 = {int_ck, ck[6],ck[5],ck[4]}
    // _DDR3_PLL_INITIAL_PHASE_1 = {int_ck, dq_0, dqs_3, dqs_2}
    Scaler32SetDWord(PB08000_14_PLL_PI1, ulDDRPLLInitPhase1);

    // _DDR3_PLL_INITIAL_PHASE_1 = {ck[10],ck[9],ck[8],ck[7]}
    // _DDR3_PLL_INITIAL_PHASE_1 = {CS, dq_3, dq_2, dq_1}
    Scaler32SetDWord(PB08000_98_PLL_PI2, ulDDRPLLInitPhase2);

    // valid phase range: 0~31
    pucPhaseOfClk[0] = (BYTE)(ulDDRPLLInitPhase0 >> 0) & 0x1F; // CK
    pucPhaseOfClk[1] = (BYTE)(ulDDRPLLInitPhase0 >> 8) & 0x1F; // CMD
    pucPhaseOfClk[2] = (BYTE)(ulDDRPLLInitPhase0 >> 16) & 0x1F; // dqs_0
    pucPhaseOfClk[3] = (BYTE)(ulDDRPLLInitPhase0 >> 24) & 0x1F; // dqs_1

    pucPhaseOfClk[4] = (BYTE)(ulDDRPLLInitPhase1 >> 0) & 0x1F; // dqs_2
    pucPhaseOfClk[5] = (BYTE)(ulDDRPLLInitPhase1 >> 8) & 0x1F; // dqs_3
    pucPhaseOfClk[6] = (BYTE)(ulDDRPLLInitPhase1 >> 16) & 0x1F; // dq_0: DQ0~DQ7
    pucPhaseOfClk[7] = (BYTE)(ulDDRPLLInitPhase2 >> 0) & 0x1F; // dq_1: DQ8~DQ15

    pucPhaseOfClk[8] = (BYTE)(ulDDRPLLInitPhase2 >> 8) & 0x1F; // dq_2: DQ16~DQ23
    pucPhaseOfClk[9] = (BYTE)(ulDDRPLLInitPhase2 >> 16) & 0x1F; // dq_3: DQ24~DQ31
    pucPhaseOfClk[10] = (BYTE)(ulDDRPLLInitPhase2 >> 24) & 0x1F; // cs


    // DDR PLL sync select setting
    // Fast version of "if((16 <= phase <= 31) OR (48 <= phase <= 63)), then corresponding SyncSel bit is set to 1"
    ucSyncSel_0 |= (((pucPhaseOfClk[0] & _BIT4) == _BIT4) ? _BIT0 : 0x00);
    ucSyncSel_0 |= (((pucPhaseOfClk[1] & _BIT4) == _BIT4) ? _BIT1 : 0x00);
    ucSyncSel_0 |= (((pucPhaseOfClk[2] & _BIT4) == _BIT4) ? _BIT2 : 0x00);
    ucSyncSel_0 |= (((pucPhaseOfClk[3] & _BIT4) == _BIT4) ? _BIT3 : 0x00);
    ucSyncSel_0 |= (((pucPhaseOfClk[4] & _BIT4) == _BIT4) ? _BIT4 : 0x00);
    ucSyncSel_0 |= (((pucPhaseOfClk[5] & _BIT4) == _BIT4) ? _BIT5 : 0x00);
    ucSyncSel_0 |= (((pucPhaseOfClk[6] & _BIT4) == _BIT4) ? _BIT6 : 0x00);
    ucSyncSel_0 |= (((pucPhaseOfClk[7] & _BIT4) == _BIT4) ? _BIT7 : 0x00);

    ucSyncSel_1 |= (((pucPhaseOfClk[8] & _BIT4) == _BIT4) ? _BIT0 : 0x00);
    ucSyncSel_1 |= (((pucPhaseOfClk[9] & _BIT4) == _BIT4) ? _BIT1 : 0x00);
    ucSyncSel_1 |= (((pucPhaseOfClk[10] & _BIT4) == _BIT4) ? _BIT2 : 0x00);

    // Set oesync_op_sel
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucSyncSel_0);
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8), (ucSyncSel_1 << 8));

    // DDR FIFO Threshold
    Scaler32SetDWord(PB08000_80_AFIFO_STR_0, ulDDR3TXFIFOSTR0Cal); // DQS,DQ TX FIFO threshold setting
    Scaler32SetBit(PB08000_84_AFIFO_STR_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), ulDDR3TXFIFOSTR1Cal); // CMD TX FIFO threshold setting
    Scaler32SetDWord(PB08000_88_AFIFO_STR_2, 0x00001111); // RX FIFO threshold setting

    ucCmdRdStrNumSel = (((ulDDR3TXFIFOSTR1Cal & 0x000000FF) == 0x00000012) ? 0x03 : 0x00);
    Scaler32SetDWord(PB08000_94_AFIFO_STR_SEL, ((DWORD)(ucCmdRdStrNumSel << 28))); // [28:29]CS : cmd_ex_rd_str_num : cs and cmd same threshold

}

//--------------------------------------------------
// Description  : Print scan phase result of search phase subroutine
// Input Value  : Array of scan phase result
// Output Value : None
//--------------------------------------------------
void ScalerDDR3OfflineScanPhasePrintScanResult(BYTE pucScanResult[8])
{
    pucScanResult = pucScanResult;

    DebugMessageMemoryPhaseCal("=====Scan Result=====", 0);
    DebugMessageMemoryPhaseCal("63~32", (((DWORD)pucScanResult[7] << 24) | ((DWORD)pucScanResult[6] << 16) | ((DWORD)pucScanResult[5] << 8) | pucScanResult[4]));
    DebugMessageMemoryPhaseCal("31~00", (((DWORD)pucScanResult[3] << 24) | ((DWORD)pucScanResult[2] << 16) | ((DWORD)pucScanResult[1] << 8) | pucScanResult[0]));
}

//--------------------------------------------------
// Description  : Find central value of longest pass range according to scan result
// Input Value  : Array of scan result
// Output Value : The central value of longest pass range
//--------------------------------------------------
BYTE ScalerDDR3OfflineFindCentralValueOfLongestPassRange(BYTE pucScanResult[8], EnumScanResultType enumResultType)
{
    BYTE ucLongestPassIntvlStart = 0;
    BYTE ucLongestPassIntvlEnd = 0;
    BYTE ucLongestPassIntvlLength = 0;
    BYTE ucCentralValue = 0;

    BYTE ucPassIntvlStart = 0;
    BYTE ucPassIntvlEnd = 0;
    BYTE ucPassIntvlLength = 0;

    BYTE ucScanResultIndex = 0;

    if(GET_BIT_RESULT(pucScanResult, 0) == _SUCCESS)
    {
        ucPassIntvlStart = 0;
    }

    for(ucScanResultIndex = 1; ucScanResultIndex < (64 * 2); ucScanResultIndex++)
    {
        if((GET_BIT_RESULT(pucScanResult, (ucScanResultIndex % 64)) == _SUCCESS) && (GET_BIT_RESULT(pucScanResult, ((ucScanResultIndex - 1) % 64)) == _FAIL))
        {
            ucPassIntvlStart = ucScanResultIndex;
        }
        else if((GET_BIT_RESULT(pucScanResult, (ucScanResultIndex % 64)) == _FAIL) && (GET_BIT_RESULT(pucScanResult, ((ucScanResultIndex - 1) % 64)) == _SUCCESS))
        {
            ucPassIntvlEnd = ucScanResultIndex - 1;
            ucPassIntvlLength = ucPassIntvlEnd - ucPassIntvlStart + 1;

            if(ucPassIntvlLength > ucLongestPassIntvlLength)
            {
                ucLongestPassIntvlLength = ucPassIntvlLength;
                ucLongestPassIntvlStart = ucPassIntvlStart;
                ucLongestPassIntvlEnd = ucPassIntvlEnd;
            }
        }
    }

    ucCentralValue = ((ucLongestPassIntvlStart + ucLongestPassIntvlEnd) / 2) % 64;

    DebugMessageMemoryPhaseCal("Pass Intvl Start:", (ucLongestPassIntvlStart % 64));
    DebugMessageMemoryPhaseCal("Pass Intvl End:", (ucLongestPassIntvlEnd % 64));

    switch(enumResultType)
    {
        case _SCAN_RESULT_WR_PI:
            DebugMessageMemoryPhaseCal("Best Phase:", ucCentralValue);
            return ucCentralValue;

        case _SCAN_RESULT_RD_DLY_TAP:
            DebugMessageMemoryPhaseCal("Best Delay Tap:", ucCentralValue);
            return ucCentralValue;

        case _SCAN_RESULT_RX_FIFO:
            DebugMessageMemoryPhaseCal("Best RX FIFO:", ((ucLongestPassIntvlStart % 64) + 1));
            return ((ucLongestPassIntvlStart % 64) + 1);

        case _SCAN_RESULT_RX_ODT:
            DebugMessageMemoryPhaseCal("Best RX ODT:", (ucLongestPassIntvlEnd % 64));
            return ((ucLongestPassIntvlEnd % 64));

        default:
            return ucCentralValue;
    }
}

#endif // End of #if(_DDR3_PHASE_CALIBRATION == _ON)
#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

