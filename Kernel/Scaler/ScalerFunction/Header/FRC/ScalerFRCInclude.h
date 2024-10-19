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
// ID Code      : ScalerFRCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(((_FRC_SUPPORT == _ON) || (_OD_FUNCTION == _ON)) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
#define GET_FRC_3BLOCK_TOGGLE_STATUS()                    ((GET_MEMORY_DVF_SELECT() == _2_5_IVF) || (GET_MEMORY_DVF_SELECT() == _3_IVF))
#endif
#if(_FRC_SUPPORT == _ON)
#define GET_FRC_CAP_EN_RESET()                            (g_bFRCCapEnRst)
#define SET_FRC_CAP_EN_RESET(x)                           (g_bFRCCapEnRst = (x))

#define GET_FRC_USE_ROW()                                 (g_ulFRCUseRow)
#define SET_FRC_USE_ROW(x)                                (g_ulFRCUseRow = (x))

#define _MEMORY_BOTTOM_ADDRESS                            ((DWORD)_MEMORY_ROW << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) // 0x0200 0000

#define GET_FRC_MAIN_BW()                                 (g_ulFRCMainBW)
#define SET_FRC_MAIN_BW(x)                                (g_ulFRCMainBW = (x))
#define GET_FRC_SUB_BW()                                  (g_ulFRCSubBW)
#define SET_FRC_SUB_BW(x)                                 (g_ulFRCSubBW = (x))

#define GET_FRC_RCP_FIFO_COLOR_DEPTH(x)                   (ScalerFRCGetRcpFifoColorDepthFromIndex(x))
#define GET_FRC_PRE_READ(x)                               (GET_MDOMAIN_OUTPUT_VSTART() - ScalerFRCSetDiffPreReadByPath(x))

#endif // End of #if(_FRC_SUPPORT == _ON)
#define FRC_DISP_LOCAL_DB_APPLY(x)                        {SET_PAGED_BIT((x), P5_AD_DISP_M1_STATUS, ~_BIT4, _BIT4);}

#if(_HDMI21_ALLM_SUPPORT == _ON)
#define GET_FRC_ALLM_ON_STATUS()                          (g_stFRCAllmInfo.bOnStatus)
#define SET_FRC_ALLM_ON_STATUS()                          (g_stFRCAllmInfo.bOnStatus = _TRUE)
#define CLR_FRC_ALLM_ON_STATUS()                          (g_stFRCAllmInfo.bOnStatus = _FALSE)

#define GET_FRC_ALLM_INPUT_PORT()                         (g_stFRCAllmInfo.enumInputPort)
#define SET_FRC_ALLM_INPUT_PORT(x)                        (g_stFRCAllmInfo.enumInputPort = (x))
#define CLR_FRC_ALLM_INPUT_PORT()                         (g_stFRCAllmInfo.enumInputPort = _NO_INPUT_PORT)

#define GET_FRC_ALLM_DELAY_MAX()                          (g_stFRCAllmInfo.usDelayMax)
#define SET_FRC_ALLM_DELAY_MAX(x)                         (g_stFRCAllmInfo.usDelayMax = (x))

#define GET_FRC_ALLM_DELAY_MIN()                          (g_stFRCAllmInfo.usDelayMin)
#define SET_FRC_ALLM_DELAY_MIN(x)                         (g_stFRCAllmInfo.usDelayMin = (x))
#endif

//--------------------------------------------------
// Define Pre-read line
//--------------------------------------------------
#define _PRE_READ_LINE_BUFFER                             (0) // before DDEN line
#define _PRE_READ_LINE_BUFFER_ACCESS_DATA                 (_PRE_READ_LINE_BUFFER + 1) // unit: D line

//--------------------------------------------------
// Deinfe FRC setting path
//--------------------------------------------------
#define _FRC_CAP_MAIN_1                                   (_BIT0)
#define _FRC_CAP_MAIN_2                                   (_BIT1)
#define _FRC_CAP_SUB_1                                    (_BIT2)
#define _FRC_CAP_SUB_2                                    (_BIT3)

#define _FRC_DISP_MAIN_1                                  (_BIT4)
#define _FRC_DISP_MAIN_2                                  (_BIT5)
#define _FRC_DISP_SUB_1                                   (_BIT6)
#define _FRC_DISP_SUB_2                                   (_BIT7) // Only for 4P Case / PBP_TB

#define _FRC_INITIAL_INDEX                                (0)
#define _FRC_INITIAL_DATA_PATH                            (_INPUT_PATH_M1_M2)

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
#define _FRC_ADDR_PBP_TB                                  ((DWORD)6144 << 12)
#else
#define _FRC_ADDR_PBP_TB                                  ((DWORD)6144 << 11)
#endif
#endif

//--------------------------------------------------
// Define FRC Length = 120
//--------------------------------------------------
#define _FRC_ACCESS_WRITE_LENGTH_120                      (120)
#define _FRC_ACCESS_READ_LENGTH_120                       (120)

//--------------------------------------------------
// Define ImgCmp
//--------------------------------------------------
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
#define _IMG_CMP_PARAM_LLB_8B_TYP                         _IMG_CMP_PARAM_LLB_8
#define _IMG_CMP_PARAM_LLB_10B_MIN                        _IMG_CMP_PARAM_LLB_8
#define _IMG_CMP_PARAM_LLB_10B_TYP                        _IMG_CMP_PARAM_LLB_10
#define _IMG_CMP_PARAM_LLB_10B_MAX                        _IMG_CMP_PARAM_LLB_12
#endif
#else
#define _IMG_CMP_PARAM_LLB_8B_TYP                         _IMG_CMP_PARAM_OFF // ask wensnoopy if modification is needed!!
#define _IMG_CMP_PARAM_LLB_10B_MIN                        _IMG_CMP_PARAM_OFF
#define _IMG_CMP_PARAM_LLB_10B_TYP                        _IMG_CMP_PARAM_OFF
#define _IMG_CMP_PARAM_LLB_10B_MAX                        _IMG_CMP_PARAM_OFF
#endif

#define GET_IMG_CMP_PARAM()                               (ScalerFRCImgCmpGetPara(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH())))

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
#define GET_BLK_NUM()                                     ((ScalerFRCGetTBMode2BlkSupport() == _ON) ? 2 : ((GET_FRC_TOP_BOTTOM_MODE_STATUS() == _FALSE) ? 2 : 3))
#else
#define GET_BLK_NUM()                                     (2)
#endif

//--------------------------------------------------
// Define Path Bank Offset
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _M1_BANK_OFFSET                                   ((WORD)0x07 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M1: bank7, 0x0E00
#define _M2_BANK_OFFSET                                   ((WORD)0x02 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M2: Bank2, 0x0400
#define _S1_BANK_OFFSET                                   ((WORD)0x03 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S1: bank3, 0x0600
#define _S2_BANK_OFFSET                                   ((WORD)0x01 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S2: Bank1, 0x0200
#define _S3_BANK_OFFSET                                   ((WORD)0x06 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S3: Bank6, 0x0C00
#define _S4_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S3: Bank0, 0x0000

#elif((_MEMORY_TYPE_CONFIG == _MEMORY_DDR2) || (_MEMORY_TYPE_CONFIG == _MEMORY_DDR1))
#define _M1_BANK_OFFSET                                   ((WORD)0x02 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M1: bank2, 0x0400
#define _M2_BANK_OFFSET                                   ((WORD)0x03 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M2: Bank3, 0x0600
#define _S1_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S1: bank0, 0x0000
#define _S2_BANK_OFFSET                                   ((WORD)0x01 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S2: Bank1, 0x0200
#define _S3_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S3: Bank0, 0x0000
#define _S4_BANK_OFFSET                                   ((WORD)0x01 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S3: Bank1, 0x0200

#else
#define _M1_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M1: bank0, 0x0000
#define _M2_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M2: bank0, 0x0000
#define _S1_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S1: bank0, 0x0000
#define _S2_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S2: bank0, 0x0000
#define _S3_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S3: Bank0, 0x0000
#define _S4_BANK_OFFSET                                   ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S3: bank0, 0x0000
#endif

#define _M1_BANK_OFFSET_HSD                               ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M1: bank0, 0x0000
#define _M2_BANK_OFFSET_HSD                               ((WORD)0x02 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M2: Bank2, 0x0400
#define _S1_BANK_OFFSET_HSD                               ((WORD)0x04 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S1: bank4, 0x0800
#define _S2_BANK_OFFSET_HSD                               ((WORD)0x06 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // S2: Bank6, 0x0C00

//--------------------------------------------------
// Deinfe for FRC auto 3 block toggle
//--------------------------------------------------
#define _FRC_R_1ST_BLOCK_STA_ADDR                         (0x00) // 0 row
#define _FRC_R_2ND_BLOCK_STA_ADDR                         ((DWORD)(_MEMORY_ROW / 3 * 2) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM)
#define _FRC_R_3RD_BLOCK_STA_ADDR                         ((DWORD)(_MEMORY_ROW / 3) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM)

#define _M_N_AUTO_BLK_TOGGLE_STABLE_TIME                  (50)

//--------------------------------------------------
// Deinfe for FRC Data Path Info
//--------------------------------------------------
#define GET_FRC_INPUT_DATA_PATH(x)                        (tFRCDataPathInfo[(x)].enumInputDataPath)
#define GET_FRC_OUTPUT_DATA_PATH(x)                       (tFRCDataPathInfo[(x)].enumFRCMDispPath)
#define GET_FRC_CHANNEL_PATH(x)                           (tFRCDataPathInfo[(x)].enumFRCPath)
#define GET_FRC_PAGE_SELECT(x)                            (tFRCDataPathInfo[(x)].enumFRCPageSelect)
#define CHK_FRC_PATH(x, y)                                (((x) & (y)) == (y))

#define GET_DEFAULT_FRAME_USE_MEMORY_ROW(x)               ((DWORD)(x) / _FW_MEM_CLIENT_MEMORY_BIT_NUM / _MEMORY_COL_PER_BANK / _MEMORY_BANK) // memory row

#define _FRC_TOTAL_128BIT                                 (128)
#define _FRC_FRAME_TEAR_PREVENT_LINE                      (2)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define GET_ROW_FOR_ROTATION()                            (g_ulFRCRowForRotation)
#define SET_ROW_FOR_ROTATION(x)                           (g_ulFRCRowForRotation = (x))
#define GET_TOTAL_ROW_FOR_ROTATION_SINGLE_PATH()          (g_ulFRCTotalRowForRotation)
#define SET_TOTAL_ROW_FOR_ROTATION_SINGLE_PATH(x)         (g_ulFRCTotalRowForRotation = (x))
#endif

//--------------------------------------------------
// One Line total pixel for Memory (FRC unit : 64 bits)
//--------------------------------------------------
#define _FRC_UNIT                                         (64)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FRC_INPUT_SLOWER,
    _FRC_INPUT_FASTER,
} EnumFRCStyle;

typedef enum
{
    _FRC_BOUNDARY_DEFAULT,
    _FRC_BOUNDARY_NORMAL,
} EnumFRCBoundary;

typedef enum
{
    _FRC_INDEX_0 = 0x00,
    _FRC_INDEX_1 = 0x01,
    _FRC_INDEX_2 = 0x02,
#if(_HW_I_DOMAIN_PATH_COUNT > 3)
    _FRC_INDEX_3 = 0x03,
    _FRC_INDEX_4 = 0x04,
    _FRC_INDEX_5 = 0x05,
#endif
} EnumFRCIndex;

typedef enum
{
    _FRC_1ST_BLOCK,
    _FRC_2ND_BLOCK,
    _FRC_3RD_BLOCK,
    _FRC_4TH_BLOCK,
} EnumFRCBlock;

typedef enum
{
    _FRC_MAIN1_PAGE = 0x05,
    _FRC_MAIN2_PAGE = 0x45,
    _FRC_SUB1_PAGE = 0x85,
    _FRC_SUB2_PAGE = 0x56,
    _FRC_SUB3_PAGE = 0x61,
    _FRC_SUB4_PAGE = 0x95,
} EnumFRCPageSelect;

typedef enum
{
    _FRC_M1 = 0x00,
    _FRC_M2 = 0x01,
    _FRC_S1 = 0x02,
    _FRC_S2 = 0x03,
    _FRC_S3 = 0x04,
    _FRC_S4 = 0x05,
} EnumFRCPath;

typedef enum
{
    _FRC_CH0_PAGE = 0x46,
    _FRC_CH1_PAGE = 0xD7,
    _FRC_CH2_PAGE = 0xD8,
    _FRC_CH3_PAGE = 0xD9,
} EnumFRCChannelPageSelect;

typedef enum
{
    _FRC_CH0,
    _FRC_CH1,
    _FRC_CH2,
    _FRC_CH3,
} EnumFRCChannel;

typedef enum
{
    _FRC_CH_1_BLK,
    _FRC_CH_2_BLK,
    _FRC_CH_3_BLK,
    _FRC_CH_4_BLK,
} EnumFRCChannelCapBlk;

typedef enum
{
    _FRC_I_DEN_EAQUAL_D_DEN,
    _FRC_I_DEN_LARGE_D_DEN,
    _FRC_I_DEN_SMALL_D_DEN,
} EnumFRCIDDenCompare;

typedef enum
{
    _FRC_READ_LENGTH,
    _FRC_WRITE_LENGTH,
} EnumFRCReadWriteLength;

typedef enum
{
    _FRC_CAP = 0x01,
    _FRC_DISP = 0x02,
} EnumFRCClient;

//--------------------------------------------------
// Structure of SDRAM Data
//--------------------------------------------------
typedef struct
{
    WORD usInputHWidth;
    WORD usInputVHeight;
    WORD usOutputHWidth;
    WORD usOutputVHeight;
} StructSDRAMDataInfo;

#if((_FRC_SUPPORT == _ON) || (_OD_FUNCTION == _ON))
typedef struct
{
    BYTE ucFBCoopEn;
    DWORD ulIHFreq;
    DWORD ulDHFreq;
    EnumDisplayMode enumDisplayMode;
    EnumDVFSelect enumDVFSelect;
    EnumDDomainRegion enumMDomainOutputRgn;
} StructMemoryBWUsageParam;
#endif

#if(_FRC_SUPPORT == _ON)
typedef struct
{
    BYTE ucImgCmpUsable;
    WORD usInputHWidth;
    WORD usFifoHWidth;
    WORD usFifoVHeight;
    DWORD ulGrantBW;
    StructMemoryBWUsageParam stMemBWParam;
} StructFRCRateCtrlInfo;
#endif

//--------------------------------------------------
// Structure of PQC Data
//--------------------------------------------------
#if(_FRC_SUPPORT == _ON)

typedef struct
{
    BYTE b5FifoColorDepth : 5;
    BYTE b1AllowHSD : 1;
    EnumImgCmpParamIndex enumImgCmpParamIndex;
    EnumODParamIndex enumExpectODParamIndex;
} StructFRCRateCtrlParam;

#endif

//--------------------------------------------------
// Structure of FRC DataPath Info
//--------------------------------------------------
typedef struct
{
    EnumInputDataPath enumInputDataPath;
    EnumMDomainDisplayDataPath enumFRCMDispPath;
    EnumFRCPath enumFRCPath;
    EnumFRCPageSelect enumFRCPageSelect;
} StructFRCDataPathInfo;

//--------------------------------------------------
// Structure of Allm Info
//--------------------------------------------------
#if((_FRC_SUPPORT == _ON) && (_HDMI21_ALLM_SUPPORT == _ON))

typedef struct
{
    bit bOnStatus;
    WORD usDelayMax;
    WORD usDelayMin;
    EnumInputPort enumInputPort;
} StructFRCAllmInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructFRCDataPathInfo code tFRCDataPathInfo[];

#if(_FRC_SUPPORT == _ON)
extern bit g_bFRCCapEnRst;
extern DWORD g_ulFRCUseRow;
extern DWORD g_ulFRCMainBW;
extern DWORD g_ulFRCSubBW;

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern StructFRCAllmInfo g_stFRCAllmInfo;
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern DWORD g_ulFRCRowForRotation;
extern DWORD g_ulFRCTotalRowForRotation;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumFRCIndex ScalerFRCGetInputDataPathIndexMapping(EnumInputDataPath enumInputPath);
extern EnumFRCPageSelect ScalerFRCCapGetPageSelect(EnumInputDataPath enumInputPath);
extern EnumFRCPageSelect ScalerFRCDispGetPageSelect(EnumInputDataPath enumInputPath);
extern EnumFRCChannel ScalerFRCGetChannelFromInputpath(EnumInputDataPath enumInputPath);
extern EnumFRCChannelPageSelect ScalerFRCGetChannelPage(EnumFRCChannel enumFRCChannel);
extern void ScalerFRCPowerOnInitial(void);
extern void ScalerFRCInitial(void);
extern DWORD ScalerFRCGetLineSumBit(WORD usHorSize, BYTE ucFIFOMemBits, EnumImgCmpParamIndex enumImgCmpIndex);
extern BYTE ScalerFRCGetAccessLength(EnumFRCReadWriteLength enumFRCReadWriteLength);
extern void ScalerFRCSetDispTopNumLengthRemain(EnumFRCPageSelect enumPageSelect, DWORD ulNumRemain, BYTE ucLen);
extern void ScalerFRCSetCapNumLengthRemain(EnumFRCPageSelect enumPageSelect, DWORD ulNumRemain, BYTE ucLen);
extern void ScalerFRCSetChannelClient(EnumDisplayRegion enumDisplayRegion);
extern void ScalerFRCSetChannelBlkNum(EnumFRCChannelPageSelect enumChannelSel, EnumFRCClient enumFRCClient, EnumMemoryFrameBufferType enumFrameBufferType);
extern bit ScalerFRCGetLineBufferMode(EnumInputDataPath enumSelectedDataPath);
extern EnumFRCChannelCapBlk ScalerFRCGetChannelFRCCapBlkNum(EnumFRCChannelPageSelect enumFRCChPage);
extern void ScalerFRCSetCapDispChannel(EnumDisplayRegion enumDisplayRegion);

#if(_FRC_SUPPORT == _ON)
extern void ScalerFRCControl(StructSDRAMDataInfo *pstFIFOSize);
extern void ScalerFRCCalculateAddress(EnumFRCPageSelect enumPageSelect, WORD usOffset);
extern WORD ScalerFRCGetShiftBankOffset(EnumFRCPageSelect enumPageSelect);
extern DWORD ScalerFRCGetCapAddress(WORD usSelectedPage, EnumFRCBlock enumBlock);
extern void ScalerFRCSetCapAddress(WORD usSelectedPage, EnumFRCBlock enumBlock, DWORD ulCapAddress);
extern WORD ScalerFRCRegPageSelection(EnumInputDataPath enumInputPath);
extern DWORD ScalerFRCGetCapLinestep(WORD usSelectedPage);
extern WORD ScalerFRCGetDispTopLineTotalPixel(WORD usSelectedPage);
extern void ScalerFRCAdjustIVS2DVSDelay(void);
extern void ScalerFRCCompareDenForFRCStyle(void);
extern EnumFRCIDDenCompare ScalerFRCCompareDenTime(WORD usInputVHeight);
extern WORD ScalerFRCSetOneFrameDVTotal(void);
extern void ScalerFRCSetDispAddress(WORD usSelectedPage, EnumFRCBlock enumBlock, DWORD ulDispAddress);
extern bit ScalerFRCGetImgCmpHWUsability(void);
extern bit ScalerFRCGetImgCmpRunTimeUsability(WORD usWidth, WORD usHeight);
extern BYTE ScalerFRCGetMemRateCtrlParamIndex(StructFRCRateCtrlInfo *pstRateCtrlInfo);
extern void ScalerFRCApplyMemRateCtrlParam(BYTE ucRateCtrlParamIndex);
extern void ScalerFRCSetMemoryBoundary(EnumFRCBoundary enumFRCBoundary);

extern void ScalerFRCGetFRCBottomAddress(void);
#if(_FW_FRC_DYNAMIC_SPACE_ALLOCATION == _ON)
extern void ScalerFRCCalculateBlockRowSpace(DWORD ulRemainSize);
#endif
extern WORD ScalerFRCSetDiffPreReadByPath(EnumFRCPageSelect enumPageSelect);
extern void ScalerFRCBWInitialAllocation(void);
extern DWORD ScalerFRCBWCalUsage(WORD usCaphwidth, WORD usDisphwidth, WORD usColorDepth, EnumImgCmpParamIndex enumLLB, DWORD ulPixelclk, EnumInputDataPath enumInputPath, bit bDefaultMode);
extern void ScalerFRCUpdateCurrentBW(void);

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
extern bit ScalerFRCGetAutoBlkToggleEn(void);
#endif
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
extern void ScalerFRCDisplayFreezeDisable(void);
#endif
extern BYTE ScalerFRCGetRcpFifoColorDepthFromIndex(BYTE ucIndex);

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
extern void ScalerFRCSetDispBotAddress(WORD usSelectedPage, EnumFRCBlock enumBlock, DWORD ulDispAddress);
extern void ScalerFRCTopBottomModeDisplaySetting(EnumFRCChannel enumFRCCh);
extern bit ScalerFRCGetBottomSettingStatusFromPage(EnumInputDataPath enumInputPath, EnumFRCPageSelect enumPageSelect);
extern bit ScalerFRCGetBottomSettingStatusFromInputDataPath(EnumInputDataPath enumInputPath);
extern bit ScalerFRCGetTBMode2BlkSupport(void);
#endif // End of #if(_TB_DISPLAY_MODE_SUPPORT == _ON)
#endif // End of #if(_FRC_SUPPORT == _ON)

#if(_FRC_LENGTH_ENLRGE_M1_M2_ONLY == _ON)
extern bit ScalerFRCGetLengthEnlargeM1M2Support(void);
#endif
extern bit ScalerFRCDBWaitForIDomainEvent(EnumWaitIDomainEventType enumEvent, EnumInputDataPath enumInputDataPath);

