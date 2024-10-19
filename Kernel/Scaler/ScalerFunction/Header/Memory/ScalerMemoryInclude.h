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
// ID Code      : ScalerMemoryInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// M domain Fifo bit
//--------------------------------------------------
#define _M_DOMAMAIN_FIFO_BIT                        (131072) // 512*128*2 bit
#define _FRC_CAP_FIFO_BIT_MARGIN                    (61440) // need < 512*128, for 2560 pixel*24bit

//--------------------------------------------------
// Memory Speed
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _MEMORY_DATA_RATE_SPEED                     (_FW_DDR_PLL_CLOCK * 2)
#define _MEMORY_PLL_CLOCK                           (_FW_DDR_PLL_CLOCK / 2)
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#define _MEMORY_DATA_RATE_SPEED                     (_FW_DDR_PLL_CLOCK * 2)
#define _MEMORY_PLL_CLOCK                           (_FW_DDR_PLL_CLOCK / 2)
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
#define _MEMORY_DATA_RATE_SPEED                     (_FW_DDR_PLL_CLOCK * 2)
#define _MEMORY_PLL_CLOCK                           (_FW_DDR_PLL_CLOCK / 2)
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
#define _MEMORY_DATA_RATE_SPEED                     (_FW_DDR_PLL_CLOCK)
#define _MEMORY_PLL_CLOCK                           (_FW_DDR_PLL_CLOCK / 2)
#elif(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_DATA_RATE_SPEED                     (_FW_DDR_PLL_CLOCK * 2)
#define _MEMORY_PLL_CLOCK                           (_FW_DDR_PLL_CLOCK / 2)
#endif

//--------------------------------------------------
// Memory Size
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_BUS_WIDTH                           0
#define _MEMORY_SIZE                                0
#define _MEMORY_BIT_NUM                             0
#define _MEMORY_BANK                                0
#define _MEMORY_COL_PER_BANK                        256
#define _MEMORY_ROW                                 2048
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)

#if(_MEMORY_SIZE_CONFIG == _1M_16BIT_SDRAM)
#define _MEMORY_BUS_WIDTH                           16
#define _MEMORY_SIZE                                _MEMORY_16MB
#define _MEMORY_BIT_NUM                             16
#define _MEMORY_BANK                                2
#define _MEMORY_COL_PER_BANK                        256
#define _MEMORY_ROW                                 2048
#endif

#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_1PC)
#define _MEMORY_BUS_WIDTH                           16
#define _MEMORY_SIZE                                _MEMORY_64MB
#define _MEMORY_BIT_NUM                             16
#define _MEMORY_BANK                                4
#define _MEMORY_COL_PER_BANK                        256
#define _MEMORY_ROW                                 4096
#elif(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
#define _MEMORY_BUS_WIDTH                           32
#define _MEMORY_SIZE                                _MEMORY_128MB
#define _MEMORY_BIT_NUM                             32
#define _MEMORY_BANK                                4
#define _MEMORY_COL_PER_BANK                        256
#define _MEMORY_ROW                                 4096
#endif

#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
// ddr bit unit(bit_num) = 16bit(2^4), frc unit = 64bit(2^6)
// so 1 column = 64 bit, 2^6(64bit) / 2^4(16bit) = 2^2(implicit mapping
// column = 512 = 2^9 -> 2^9 / 2^2 = 2^7
// address row 13bit : bank 2bit : column 7bit
// ddr2 1pc address = 2pcs -> no client use 2pc ddr at the same time (m1 ddrA, m2 ddrB)

#if(_MEMORY_SIZE_CONFIG == _16M_16BIT_DDR2_1PC)
#define _MEMORY_BUS_WIDTH                           16
#define _MEMORY_SIZE                                _MEMORY_256MB
#define _MEMORY_BIT_NUM                             16
#define _MEMORY_BANK                                4
#define _MEMORY_COL_PER_BANK                        512
#define _MEMORY_ROW                                 8192
#elif(_MEMORY_SIZE_CONFIG == _16M_16BIT_DDR2_2PCS)
#define _MEMORY_BUS_WIDTH                           32
#define _MEMORY_SIZE                                _MEMORY_512MB
#define _MEMORY_BIT_NUM                             32
#define _MEMORY_BANK                                4
#define _MEMORY_COL_PER_BANK                        512
#define _MEMORY_ROW                                 8192
#endif

#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC_NORMAL)
#define _MEMORY_BUS_WIDTH                           (16)
#define _MEMORY_SIZE                                (_MEMORY_1GB)
#define _MEMORY_BIT_NUM                             (16)
#define _MEMORY_BANK                                8
#define _MEMORY_COL_PER_BANK                        1024
#define _MEMORY_ROW                                 8192
#elif(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS_NORMAL)
#define _MEMORY_BUS_WIDTH                           (16 * GET_MEMORY_PIECE_INT())
#define _MEMORY_SIZE                                (_MEMORY_1GB * GET_MEMORY_PIECE_INT())
#define _MEMORY_BIT_NUM                             (16 * GET_MEMORY_PIECE_INT())
#define _MEMORY_BANK                                8
#define _MEMORY_COL_PER_BANK                        1024
#define _MEMORY_ROW                                 8192
#endif

#endif

//--------------------------------------------------
// Memory Piece
//--------------------------------------------------
#define GET_MEMORY_PIECE()                          (g_ucMemoryPiece)
#define SET_MEMORY_PIECE(x)                         (g_ucMemoryPiece = (x))
#define GET_MEMORY_PIECE_INT()                      ((GET_MEMORY_PIECE() == _MEMORY_2PCS) ? 2 : 1)

//--------------------------------------------------
// Memory Efficiency
//--------------------------------------------------
#if(_HW_FRC_LENGTH_TYPE == _FRC_LENGTH_7BIT)
#if(_FRC_LENGTH_ENLRGE_M1_M2_ONLY == _ON)
#define _MEMORY_EFFICIENCY_1P                       ((ScalerFRCGetLengthEnlargeM1M2Support() == _ON) ? (80) : (75))
#else
#define _MEMORY_EFFICIENCY_1P                       ((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? (80) : (75))
#endif
#define _MEMORY_EFFICIENCY_MULTI_P                  ((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? (80) : (75))
#define _MEMORY_EFFICIENCY_DROP_HFREQ_RATIO         (5)
#define _MEMORY_EFFICIENCY_DROP                     (5)
#endif

#if(_HW_FRC_LENGTH_TYPE == _FRC_LENGTH_8BIT)
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#define _MEMORY_EFFICIENCY_1P                       (85)
#define _MEMORY_EFFICIENCY_MULTI_P                  (80)

#else
#define _MEMORY_EFFICIENCY_1P                       (80)
#define _MEMORY_EFFICIENCY_MULTI_P                  (80)
#endif
#endif

#define _MEMORY_EFFICIENCY                          ((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) ? (_MEMORY_EFFICIENCY_1P) : (_MEMORY_EFFICIENCY_MULTI_P))


#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Define Total Bandwidth
//--------------------------------------------------
#define _MEMORY_TOTAL_BW                            ((DWORD)_MEMORY_DATA_RATE_SPEED * _MEMORY_EFFICIENCY / 10)
#define _MEMORY_TOTAL_BW_MTP                        ((DWORD)_MEMORY_DATA_RATE_SPEED * _MEMORY_EFFICIENCY_MULTI_P / 10)
#if(_HW_FRC_LENGTH_TYPE == _FRC_LENGTH_7BIT)
#define _MEMORY_TOTAL_BW_DROP                       ((DWORD)_MEMORY_DATA_RATE_SPEED * _MEMORY_EFFICIENCY_DROP / 10)
#endif
#define SET_MEMORY_FRC_OD_BW(x)                     (g_ulMemoryFrcOdBw = (x))
#define GET_MEMORY_FRC_OD_BW()                      (g_ulMemoryFrcOdBw)
// #define GET_MEMORY_FRC_OD_BW()                      ((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) ? _MEMORY_TOTAL_BW : _MEMORY_TOTAL_BW_MTP)
#if(_COLOR_IP_3DDI == _ON)
#define SET_MEMORY_3DDI_BW(x)                       (StructMemoryClientBW.ul3DDIAllocateBW = (x))
#define GET_MEMORY_3DDI_BW()                        (StructMemoryClientBW.ul3DDIAllocateBW)
#endif


#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

#define SET_IVS2DVS_DELAY_16ICLK1(usBackup)         {\
                                                        ScalerSetBit(P0_3F_DISPLAY_ALIGN_CONTROL, ~(_BIT5 | _BIT4), ((HIBYTE(usBackup) & 0x03) << 4));\
                                                        ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, LOBYTE(usBackup));\
                                                    }

#define SET_IVS2DVS_DELAY_16ICLK2(usBackup)         {\
                                                        ScalerSetBit(P0_3F_DISPLAY_ALIGN_CONTROL, ~(_BIT1 | _BIT0), (HIBYTE(usBackup) & 0x03));\
                                                        ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, LOBYTE(usBackup));\
                                                    }

//--------------------------------------------------
// D Domain Request
//--------------------------------------------------
#define GET_D_DOMAIN_REQUEST()                      (_1_LINE_AFTER_DVS)

#define _MEMORY_NUM_LEN_REM_MULTIPLE                (2)


#if(_COLOR_IP_3DDI == _ON)
#define GET_3DDI_START_ADDRESS()                    (g_stMemoryClientAddress.ul3DDIStartAddress)
#define GET_3DDI_END_ADDRESS()                      (g_stMemoryClientAddress.ul3DDIEndAddress)
#endif
#if(_FRC_SUPPORT == _ON)
#define GET_FRC_START_ADDRESS()                     (g_stMemoryClientAddress.ulFRCStartAddress)
#define GET_FRC_END_ADDRESS()                       (g_stMemoryClientAddress.ulFRCEndAddress)
#endif
#if(_OD_FUNCTION == _ON)
#define GET_OD_START_ADDRESS()                      (g_stMemoryClientAddress.ulODStartAddress)
#define GET_OD_END_ADDRESS()                        (g_stMemoryClientAddress.ulODEndAddress)
#endif
#if(_GOSD_SUPPORT == _ON)
#define GET_GOSD_START_ADDRESS()                    (g_stMemoryClientAddress.ulGOSDStartAddress)
#define GET_GOSD_END_ADDRESS()                      (g_stMemoryClientAddress.ulGOSDEndAddress)
#endif

#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Memory BW Ctrl Related
//--------------------------------------------------
#define _BW_CTRL_CLIENT_INDEX_DEFAULT               (0)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of D Domain Request
//--------------------------------------------------
typedef enum
{
    _1_LINE_AFTER_DVS,
    _64_PIXELS_AFTER_DVS,
    _7_LINES_BEFORE_DEN,
} EnumDDomainRequest;

//--------------------------------------------------
// Structure of Memory Line Block Step
//--------------------------------------------------
typedef struct
{
    DWORD ulLineStep;
    DWORD ulBlockStep;
    WORD usHorSize;
    WORD usVerSize;
} StructMemoryLineBlockStep;

//--------------------------------------------------
// Enumerations of FIFO Frequency
//--------------------------------------------------
typedef enum
{
    _SCALER_FIFO_FREQ_M2PLL,
    _SCALER_FIFO_FREQ_MPLL,
    _SCALER_FIFO_FREQ_DDRPLL,
    _SCALER_FIFO_FREQ_DCLK,
} EnumScalerFIFOFreq;

//--------------------------------------------------
// Structure of Memory Dt Fine Tune
//--------------------------------------------------
typedef struct
{
    WORD usInputVheight;
    WORD usPanelVheight;
    bit bMinusDt;
    WORD usDtFineTune;
} StructMemoryDtFineTune;


typedef struct
{
#if(_COLOR_IP_3DDI == _ON)
    DWORD ul3DDIAllocateBW;
#endif
#if(_FRC_SUPPORT == _ON)
    DWORD ulFRCAllocateBW;
#endif
#if(_OD_FUNCTION == _ON)
    DWORD ulODAllocateBW;
#endif
/*#if(_GOSD_SUPPORT == _ON)
    DWORD ulGOSDAllocateBW;
#endif*/
} StructMemoryClientBW;


typedef struct
{
#if(_COLOR_IP_3DDI == _ON)
    DWORD ul3DDIStartAddress;
    DWORD ul3DDIEndAddress;
#endif
#if(_FRC_SUPPORT == _ON)
    DWORD ulFRCStartAddress;
    DWORD ulFRCEndAddress;
#endif
#if(_OD_FUNCTION == _ON)
    DWORD ulODStartAddress;
    DWORD ulODEndAddress;
#endif
#if(_GOSD_SUPPORT == _ON)
    DWORD ulGOSDStartAddress;
    DWORD ulGOSDEndAddress;
#endif
} StructMemoryClientAddress;


#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Memory BW Ctrl Related
//--------------------------------------------------
typedef enum
{
    _BW_CTRL_REQ_MODE,
    _BW_CTRL_LEN_MODE,
} EnumBwCtrlMode;

typedef struct
{
    bit bEnable;
    EnumBwCtrlMode enumMode;
    DWORD ulReqThd;
    DWORD ulTimeThd;
} StructBwCtrlClientInfo;
#endif // End of #if(_MEMORY_BW_CTRL_SUPPORT == _ON)

//--------------------------------------------------
// IVS2DVS delay fine tune
//--------------------------------------------------
typedef struct
{
    WORD usOldIVS2DVSDelay;
    WORD usNewIVS2DVSDelay;
    WORD usIVS2DVSChgLimit;
} StructIVS2DVSDelayFineTune;

#if(_FRC_SUPPORT == _ON)
typedef struct
{
    BYTE ucMcode;
    BYTE ucNcode;
} StructMemoryMNTracking;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern BYTE g_ucMemoryPiece;
extern DWORD g_ulMemoryFrcOdBw;
extern StructMemoryClientAddress g_stMemoryClientAddress;
extern StructMemoryClientBW g_stMemoryClientBW;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq);
extern void ScalerMemoryInitial(void);
extern bit ScalerMemoryGetPowerControlStatus(void);

#if(_PANEL_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
extern void ScalerMemoryCompensateDtForLastLine(DWORD ulTargetLastLine, DWORD ulCurrentLastLine);
#endif

extern void ScalerMemorySetIVS2DVSLineDelay(WORD usIVS2DVSDelay, EnumInputDataPath enumInputDataPath);
extern void ScalerMemoryFineTuneIVS2DVSDelay(WORD usOldIVS2DVSDelay, WORD usNewIVS2DVSDelay, WORD usIVS2DVSChgLimit);
extern void ScalerMemoryFineTuneIVS2DVSDelayWhenActiveState(StructIVS2DVSDelayFineTune *pstFineTune, const StructTimingInfo *pstMdomainInputInfo, const StructDisplayInfo *pstMdomainOutputInfo);

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
extern void ScalerMemoryReset(void);
#endif

extern DWORD ScalerMemoryCalculateNumberAndRemain(DWORD ulTotalSize, WORD usLength, bit bDummy);

#if(_FRC_SUPPORT == _ON)
extern bit ScalerMemoryGetFrameTrackingEnable(void);
extern void ScalerMemorySetFrameTrackingEnable(bit bEn);
extern void ScalerMemoryFrameTracking(void);
extern void ScalerMemoryGetMNRatio(StructMemoryMNTracking *pstMNTracking, EnumDVFSelect enumDVFSelect);
extern void ScalerMemoryCalculateLineStepAndBlockStep(DWORD ulLinetotalpixel, StructMemoryLineBlockStep *pstMemoryLineBlockStep);
extern BYTE ScalerMemoryGetFrameBufferCount(void);
#endif

extern void ScalerMemoryFrameSyncSetDt(BYTE ucNum, WORD usVheight);
extern void ScalerMemorySetIVS2DVSDelayPixel(DWORD ulIVStoDVSPixels, const StructTimingInfo *pstMdomainInputInfo);
extern DWORD ScalerMemoryGetIVS2DVSDelayPixel(const StructTimingInfo *pstMdomainInputInfo);
extern bit ScalerMemoryCheckScreenCoverStatus(void);

#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
extern bit ScalerMemoryGetShiftOneLineSupport(void);
extern void ScalerMemorySetShiftOneLine(bit bEnable, EnumInputDataPath enumInputDataPath);
#endif

#if(_DT_RANGE_TEST_SUPPORT == _ON)
extern void ScalerMemoryDtRangeTest(WORD usVheight);
#endif

#if(_M_DOMAIN_LSR_LINE_BUFFER_DT_FORCE_10_TO_8_BIT == _ON)
extern void ScalerMemoryForceMemoryDataBit10to8(void);
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

extern void ScalerMemoryBwAllocation(void);
extern void ScalerMemorySpaceAllocation(void);
extern void ScalerMemoryAdjustFRCODBoundary(void);

#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
extern void ScalerMemorySetBwCtrlEnable(EnumMemoryClientType enumClientType, BYTE ucClientIndex, bit bEnable);
extern void ScalerMemorySetBwCtrl(EnumMemoryClientType enumClientType, BYTE ucClientIndex, StructBwCtrlClientInfo *pstClientInfo);
#endif

#endif

extern WORD ScalerMemoryGetFifoWidth(EnumDDomainRegion enumDDomainRegion);
extern WORD ScalerMemoryGetFifoVheight(EnumDDomainRegion enumDDomainRegion);

