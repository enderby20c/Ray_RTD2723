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
// ID Code      : ScalerMDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
#define _EDID_ANALYSIS_CLK_MARGIN                       (1)
#define _EDID_ANALYSIS_HTOTAL_MARGIN                    (2)
#define _GET_CVT_MIN_VBLANK_PERIOD                      (460) // (us)
#endif

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DVSYNC_HEIGHT_MIN                              (1)
#define _DT_TARGET_PERCENTAGE                           (50)

//--------------------------------------------------
// Macros of Memory Work Type
//--------------------------------------------------
#define SET_MEMORY_WORK_TYPE(x)                         (g_stMDomainInfo.enumMemoryWorkMode = (x))
#define CLR_MEMORY_WORK_TYPE()                          (g_stMDomainInfo.enumMemoryWorkMode = 0)

//--------------------------------------------------
// Macros of Memory Frame buffer
//--------------------------------------------------
#define GET_MEMORY_FRAME_BUFFER()                       (g_stMDomainInfo.enumMemoryFrameBufferType)
#define SET_MEMORY_FRAME_BUFFER(x)                      (g_stMDomainInfo.enumMemoryFrameBufferType = (x))
#define CLR_MEMORY_FRAME_BUFFER()                       (g_stMDomainInfo.enumMemoryFrameBufferType = 0)

//--------------------------------------------------
// Macros of Input Port
//--------------------------------------------------
#define GET_MDOMAIN_INPUT_PORT()                        (g_stMDomainInfo.enumInputPort)

//--------------------------------------------------
// Macros of Source Type
//--------------------------------------------------
#define GET_MDOMAIN_SOURCE_TYPE()                       (g_stMDomainInfo.enumSourceType)

//--------------------------------------------------
// Macros of Input Vtotal Odd
//--------------------------------------------------
#define GET_MDOMAIN_INPUT_VHEIGHT_ODD()                 (g_stMDomainInputData.b1InputVheightOdd)

//--------------------------------------------------
// Macros of MDomain Input Info.
//--------------------------------------------------
#define GET_MDOMAIN_INPUT_VIDEO_FIELD()                 (g_stMDomainInputData.b1VideoField)

//--------------------------------------------------
// Macros of MDomain Output Info.
//--------------------------------------------------
#define GET_MDOMAIN_OUTPUT_RGN()                        (g_stMDomainOutputData.enumDDomainRegion)

//--------------------------------------------------
// Macros of D Clock Freq. Info.
//--------------------------------------------------
#define SET_D_CLK_FREQ(x)                               (g_ulMDomainDClkFreq = (x))

//--------------------------------------------------
// Macros of Input HFreq in DDomain unit
//--------------------------------------------------
#define GET_MDOMAIN_IHF_IN_DDOMAIN()                    (GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_HFREQ(), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT()))

//--------------------------------------------------
// Macros of Display HFreq in IDomain unit
//--------------------------------------------------
#define GET_MDOMAIN_DHF_IN_IDOMAIN()                    (GET_DWORD_MUL_DIV((GET_D_CLK_FREQ() * 10), GET_MDOMAIN_INPUT_VHEIGHT(), ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * GET_MDOMAIN_OUTPUT_VHEIGHT())))

//--------------------------------------------------
// Macros of Frame Sync D Clock Freq. From DHtotal
//--------------------------------------------------
#define GET_FRAME_SYNC_DCLK_FROM_DHTOTAL(x)             (GET_DWORD_MUL_DIV(GET_MDOMAIN_IHF_IN_DDOMAIN(), (x), 10))

//--------------------------------------------------
// Macros of D Clock Calculate Method
//--------------------------------------------------
#define GET_D_CLK_FROM_VFREQ(total_pixel, vfreq)        (GET_DWORD_MUL_DIV((total_pixel), (vfreq), 10000))
#define GET_D_CLK_TYPICAL()                             (GET_D_CLK_FROM_VFREQ((DWORD)_PANEL_DH_TOTAL * _PANEL_DV_TOTAL, _PANEL_TYP_FRAME_RATE))
#define GET_D_CLK_FRAME_BUFFER(vtotal, last_line)       (GET_D_CLK_FROM_VFREQ(((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * (vtotal) + (last_line)), g_usMDomainDVFreq))
#define GET_D_CLK_LINE_BUFFER()                         (GET_DWORD_MUL_DIV(((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * GET_MDOMAIN_INPUT_HFREQ()), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT()) / 10)

//--------------------------------------------------
// Macros of DVFreq. Info.
//--------------------------------------------------
#define GET_OUTPUT_VFREQ()                              (g_usMDomainDVFreq)

//--------------------------------------------------
// Macros of Display Timing Gen Free Run DVtotal
//--------------------------------------------------
#define GET_FREE_RUN_DVTOTAL()                          (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, _AUTOINC) & _HW_DIS_TIMING_GEN_VTOTAL_BIT)
#define SET_FREE_RUN_DVTOTAL(usBackup)                  {ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, ((usBackup) & _HW_DIS_TIMING_GEN_VTOTAL_BIT));}

#define GET_DIS_TIMING_GEN_WD_VTOTAL()                  (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H, _AUTOINC) & _HW_DIS_TIMING_GEN_VTOTAL_BIT)
#define SET_DIS_TIMING_GEN_WD_VTOTAL(usBackup)          {ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H, ((usBackup) & _HW_DIS_TIMING_GEN_VTOTAL_BIT));}

#define GET_FREE_RUN_LAST_LINE()                        ((ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB, _AUTOINC) & _HW_DIS_TIMING_GEN_HTOTAL_BIT) + _PANEL_DHTOTAL_SETTING_COMPLEMENT)
#define SET_FREE_RUN_LAST_LINE(usBackup)                {\
                                                            WORD usTemp = (usBackup);\
                                                            usTemp -= ((usTemp >= _PANEL_DHTOTAL_SETTING_COMPLEMENT) ? _PANEL_DHTOTAL_SETTING_COMPLEMENT : 0);\
                                                            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB, (usTemp & _HW_DIS_TIMING_GEN_HTOTAL_BIT));\
                                                        }

#if((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
//--------------------------------------------------
// Definitions of VGIP Vsync Enable
//--------------------------------------------------
#define SET_MDOMAIN_VGIP_VSYNC_BY_PASS(x)               (g_stMDomainInfo.b1VgipVsyncBypassEn = (x))
#define GET_MDOMAIN_VGIP_VSYNC_BY_PASS()                (g_stMDomainInfo.b1VgipVsyncBypassEn)

#define SET_MDOMAIN_VGIP_VSYNC_BY_PASS_AFTER_I_DB(x)    (g_stMDomainInfo.b1VgipVsyncBypassSetAfterIDB = (x))
#define GET_MDOMAIN_VGIP_VSYNC_BY_PASS_AFTER_I_DB()     (g_stMDomainInfo.b1VgipVsyncBypassSetAfterIDB)
#endif

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Macros of FRC Style
//--------------------------------------------------
#define GET_MDOMAIN_FRC_STYLE(x)                        (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].enumFRCInputStyle)
#define SET_MDOMAIN_FRC_STYLE(x, y)                     (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].enumFRCInputStyle = (y))

//--------------------------------------------------
// Macros of FRC Control Param Index
//--------------------------------------------------
#define GET_MDOMAIN_FRC_CTRL_PARAM_INDEX(x)             (g_pstMDomainBackupInfo[x].ucFRCCtrlParamIndex)
#define SET_MDOMAIN_FRC_CTRL_PARAM_INDEX(x, y)          (g_pstMDomainBackupInfo[x].ucFRCCtrlParamIndex = (y))
#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Macros of OD use Info.
//--------------------------------------------------

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#define GET_ASPECT_ORIGIN_MODE()                        (g_bMDomainAspectOriginMode)
#define SET_ASPECT_ORIGIN_MODE(x)                       (g_bMDomainAspectOriginMode = (x))
#endif


#define _DCLK_SPREAD_RANGE_MARGIN                       (1)

//--------------------------------------------------
// Macros of MDomain Data Bit
//--------------------------------------------------
#define GET_MEMORY_DATA_BIT()                           (g_stMDomainInfo.b6DataBit)
#define SET_MEMORY_DATA_BIT(x)                          (g_stMDomainInfo.b6DataBit = (x))
#define CLR_MEMORY_DATA_BIT()                           (g_stMDomainInfo.b6DataBit = 0)


#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Macros of Memory Bandwidth
//--------------------------------------------------
#define GET_MEMORY_BW(x)                                (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usUseMemoryBW)
#define SET_MEMORY_BW(x, y)                             (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usUseMemoryBW = (y))
#define CLR_MEMORY_BW(x)                                (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usUseMemoryBW = 0)

#define GET_CAPTURE_BW(x)                               (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usCapUsedBW)
#define SET_CAPTURE_BW(x, y)                            (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usCapUsedBW = (y))
#define CLR_CAPTURE_BW(x)                               (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usCapUsedBW = 0)

#define GET_DISPLAY_BW(x)                               (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usDispUsedBW)
#define SET_DISPLAY_BW(x, y)                            (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usDispUsedBW = (y))
#define CLR_DISPLAY_BW(x)                               (g_pstMDomainFRCInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usDispUsedBW = 0)

#define CLR_PATH_MEMORY_BW_CONFIG(x)                    {\
                                                            CLR_MEMORY_BW(x);\
                                                            CLR_CAPTURE_BW(x);\
                                                            CLR_DISPLAY_BW(x);\
                                                        }
#endif

#define SET_FIFO_INPUT_HWIDTH(x, y)                     (g_pstMDomainFifoInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usFIFOInputHwidth = (y))
#define GET_FIFO_INPUT_HWIDTH(x)                        (g_pstMDomainFifoInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usFIFOInputHwidth)

#define SET_FIFO_OUTPUT_HWIDTH(x, y)                    (g_pstMDomainFifoInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usFIFOOutputHwidth = (y))
#define GET_FIFO_OUTPUT_HWIDTH(x)                       (g_pstMDomainFifoInfo[ScalerFRCGetInputDataPathIndexMapping(x)].usFIFOOutputHwidth)

#if(_M_DOMAIN_FRAMESYNC_ACTIVE_TIMING_INFO_SUPPORT == _ON)
//--------------------------------------------------
// Macros of Mdomain Frame Sync Active Info
//--------------------------------------------------
#define SET_MDOMAIN_FRAMESYNC_ACTIVE_INFO(x)            {\
                                                            (g_stMDomainFSActiveInfo.stMDomainFSActiveInputData = g_stMDomainInputData);\
                                                            (g_stMDomainFSActiveInfo.stMDomainFSActiveOutputData = g_stMDomainOutputData);\
                                                        }
#endif

#define _FRC_WRITE_BW_MULTIPLE                          (1)

#if(_OD_FUNCTION == _ON)
#define GET_MEMORY_REMAIN_BW()                          (g_ulMDomainFRCMemoryRemainBW)
#define SET_MEMORY_REMAIN_BW(x)                         (g_ulMDomainFRCMemoryRemainBW = (x))
#else
#define GET_MEMORY_REMAIN_BW()                          (GET_MEMORY_FRC_OD_BW())
#endif

//--------------------------------------------------
// Macros of scaling setting
//--------------------------------------------------
#define SET_H_SCALE_UP()                                (g_stMDomainInfo.b1HSU = _TRUE)
#define CLR_H_SCALE_UP()                                (g_stMDomainInfo.b1HSU = _FALSE)

#define SET_H_SCALE_DOWN()                              (g_stMDomainInfo.b1HSD = _TRUE)
#define CLR_H_SCALE_DOWN()                              (g_stMDomainInfo.b1HSD = _FALSE)

#define SET_V_SCALE_UP()                                (g_stMDomainInfo.b1VSU = _TRUE)
#define CLR_V_SCALE_UP()                                (g_stMDomainInfo.b1VSU = _FALSE)

#define SET_V_SCALE_DOWN()                              (g_stMDomainInfo.b1VSD = _TRUE)
#define CLR_V_SCALE_DOWN()                              (g_stMDomainInfo.b1VSD = _FALSE)

//-------------------------------------------------
// For  MDomain PR Support
//-------------------------------------------------
#if(((_DP_SUPPORT == _ON) && (_DP_PR_MODE_SUPPORT == _ON)) || ((_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)))
#define _MDOMAIN_PR_MODE_SUPPORT                        _ON
#else
#define _MDOMAIN_PR_MODE_SUPPORT                        _OFF
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Structure of DHtotal and DVtotal
//--------------------------------------------------
typedef struct
{
    WORD usDHtotal;
    WORD usDVtotal;
} StructDHVtotal;

//--------------------------------------------------
// Structure of DHtotal Fine tune Type
//--------------------------------------------------
typedef struct
{
    BYTE b1DHtotalFineTuneStatus : 1;
    WORD usDHtotal;
} StructDHtotalFTStatus;

#if(_FRC_SUPPORT == _ON)
typedef struct
{
    EnumFRCStyle enumFRCInputStyle;
    WORD usUseMemoryBW;
    WORD usCapUsedBW;
    WORD usDispUsedBW;
}StructFRCInfo;
#endif // End of #if(_FRC_SUPPORT == _ON)

typedef struct
{
    WORD usFIFOInputHwidth;
    WORD usFIFOOutputHwidth;
}StructFifoInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern bit g_bMDomainAspectOriginMode;
#endif

#if(_OD_FUNCTION == _ON)
extern DWORD g_ulMDomainFRCMemoryRemainBW;
#endif

#if(_FRC_SUPPORT == _ON)
extern StructFRCInfo g_pstMDomainFRCInfo[_HW_I_DOMAIN_PATH_COUNT];
#endif

extern StructFifoInfo g_pstMDomainFifoInfo[_HW_I_DOMAIN_PATH_COUNT];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMDomainControlDBApply(void);
extern BYTE ScalerMDomainGetInputPathCount(EnumInputDataPath enumInputDataPath);
extern void ScalerMDomainSetDclkConfig(void);
extern EnumMemoryConfig ScalerMDomainMemorySelectConfirm(void);
extern void ScalerMDomainGetBackground_R1(StructTimingFormat *pstTimingFormat);
extern DWORD ScalerMDomainGetDisplayActiveRegion(void);
extern StructDHtotalFTStatus ScalerMDomainDHtotalFinetune(DWORD ulDclk, DWORD ulDclkMaxBoundary, DWORD ulDclkMinBoundary);
extern DWORD ScalerMDomainDtotalLastLineFinetune(DWORD ulDclk, DWORD ulDclkMaxBoundary, DWORD ulDclkMinBoundary, DWORD ulDtotal);
extern void ScalerMDomainFrameSyncSwitchtoFreeRunMode(void);

#if(_FRC_SUPPORT == _ON)
extern DWORD ScalerMDomainGetCurBW(void);
extern WORD ScalerMDomainGetCurODReservedBW(BYTE ucODBit10x, StructMemoryBWUsageParam *pstMemBWParam);
#endif

#if((_FRC_SUPPORT == _ON) || (_OD_FUNCTION == _ON))
extern void ScalerMDomainGetMemBWParam(StructMemoryBWUsageParam *pstMemBWParam);
#endif

#if(_OD_FUNCTION == _ON)
extern void ScalerMDomainODFlagInitial(void);
extern WORD ScalerMDomainODCalculateMemoryUseSpace(BYTE ucODBit10x);
extern WORD ScalerMDomainODCalculateMemoryUseBW(BYTE ucODBit10x, StructMemoryBWUsageParam *pstMemBWParam);
#endif // End of #if(_OD_SUPPORT == _ON)

extern void ScalerMDomainSetDisplayTimingGenDHTotalLastline(WORD usHTotal);
extern void ScalerMDomainSetMemoryFrameBuffer(BYTE ucType);
extern WORD ScalerMDomainGetMDomainOutputVFreq(void);
extern WORD ScalerMDomainGetMDomainOutputHTotal(void);
extern void ScalerMDomainSetMDomainOutputVTotal(WORD usVTotal);
extern void ScalerMDomainGetEnumMemoryWorkMode(BYTE *pucDestMode, BYTE ucSrcMode);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
extern void ScalerMDomainDisplayTimingGenDBEnable(bit bEnable);
extern void ScalerMDomainDisplayTimingGenDBApply(EnumDBApply enumDBApply);
extern bit ScalerMDomainDisplayTimingGenGetDBStatus(void);
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
extern WORD ScalerMDomainLocalContrastGetVtotal(void);
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void ScalerMDomainGetRtkAdvMbrPanelInfo(StructRtkAdvMbrPanelInfo *pstPanelInfo);
#endif

extern bit ScalerMDomainSetDisplayTimingGen(EnumDDomainRegion enumDDomainRegion);

#if(_MDOMAIN_PR_MODE_SUPPORT == _ON)
extern void ScalerMDomainPRModeInitial(void);
#endif
