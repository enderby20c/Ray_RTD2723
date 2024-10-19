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
// ID Code      : ScalerFRC.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_FRC_H__
#define __SCALER_FRC_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FRC_IVS2DVSDELAY_MARGIN                    (30)  // (IVStart + IDEN) period > (DVStart + DDEN) period

#if(_DRR_SUPPORT == _ON)
#define _FRC_IVS2DVSDELAY_MARGIN_DRR                (4)
#define _FRC_IVS2DVSDELAY_LINE_BUFFER_MARGIN        (4)
#endif


#if(_FRC_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define GET_ROW_FOR_MAIN()                          ((GET_ROT_TYPE() != _ROT_DISABLE) ? GET_ROW_FOR_ROTATION() : (g_ulFRCRowForMain))
#else
#define GET_ROW_FOR_MAIN()                          (g_ulFRCRowForMain)
#endif
#define SET_ROW_FOR_MAIN(x)                         (g_ulFRCRowForMain = (x))
#define GET_ROW_FOR_SUB()                           (g_ulFRCRowForSub)
#define SET_ROW_FOR_SUB(x)                          (g_ulFRCRowForSub = (x))

// FRC Rate Ctrl Param
#define GET_FRC_RCP_IMG_CMP_PARAM(x)                (ScalerFRCGetRcpImcCmpParamFromIndex(x))
#define GET_FRC_RCP_IMG_CMP_EN(x)                   (GET_IMG_CMP_ENABLE(GET_FRC_RCP_IMG_CMP_PARAM(x)))
#define GET_FRC_RCP_IMG_CMP_LLB(x)                  (GET_IMG_CMP_PARAM_LLB(GET_FRC_RCP_IMG_CMP_PARAM(x)))

#define GET_FRC_RCP_FIFO_BPP(x)                     (GET_FRC_RCP_FIFO_COLOR_DEPTH(x) * 3)
#define GET_FRC_RCP_BPP(x)                          (GET_FRC_RCP_IMG_CMP_EN(x) ? GET_FRC_RCP_IMG_CMP_LLB(x) : GET_FRC_RCP_FIFO_BPP(x))
#define GET_FRC_RCP_HSD_EN(x)                       (ScalerFRCGetRcpHsdEnFromIndex(x))

#define GET_FRC_RCP_OD_PARAM(x)                     ((_OD_FUNCTION == _ON) ? (ScalerFRCGetRcpODParamFromIndex(x)) : _OD_PARAM_OFF)

#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
#define GET_MOD_FRC_LEN_WTLVL_STATUS()              (g_bFRCModLenWtlvlStatus)
#define SET_MOD_FRC_LEN_WTLVL_STATUS(x)             (g_bFRCModLenWtlvlStatus = (x))
#endif

#define _SUB_BW_HWIDTH_MARGIN                       (4)
#endif

#define _FRC_MIN_LINE_SUM_BIT                       (128 * 30)

#define _FRAME_SIZE_MARGIN                          (10) // memory row

//--------------------------------------------------
// Define FRC Access Length
//--------------------------------------------------
#if(_FRC_LENGTH_ENLRGE_M1_M2_ONLY == _ON)
#define GET_1P_EO_STATUS()                          ((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE))
#define _FRC_ACCESS_WRITE_LENGTH_ENLRGE             (_FRC_LENGTH_8BIT)
#define _FRC_ACCESS_READ_LENGTH_ENLRGE              (_FRC_LENGTH_8BIT)
#endif

#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
#define _FRC_IMC_ACCESS_WRITE_LENGTH                (0x60)
#define _FRC_IMC_ACCESS_READ_LENGTH                 (0x60)
#define _FRC_DISP_WTLVL                             ((GET_MOD_FRC_LEN_WTLVL_STATUS() == _TRUE) ? 0x40 : (510 - (ScalerFRCGetAccessLength(_FRC_READ_LENGTH) / 2)))
#else
#define _FRC_DISP_WTLVL                             (510 - (ScalerFRCGetAccessLength(_FRC_READ_LENGTH) / 2))
#endif

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
#define _FRC_ROTATION_VERTICAL_ACCESS_WRITE_LENGTH  (0x7C)
#define _FRC_ROTATION_VERTICAL_ACCESS_READ_LENGTH   (0x7C)
#endif

#define _OD_PARAM_LENGTH                            (sizeof(tODParam) / sizeof(tODParam[0]))

#define GET_BW_ALLOCATION_IHTOTAL(x)                (((x) & _INPUT_PATH_M1) ? _PANEL_DH_TOTAL : GET_SUB_ALLOCATION_IHTOTAL())
#define GET_SUB_ALLOCATION_IHTOTAL()                ((g_ulFRCSubAllocateIHtotal == 0) ? _PANEL_DH_TOTAL : g_ulFRCSubAllocateIHtotal)
#define SET_SUB_ALLOCATION_IHTOTAL(x)               (g_ulFRCSubAllocateIHtotal = (x))

#define GET_CVT_MIN_VPORCH(x, y)                    (CEILING_OF_INT_DIVISION(((DWORD)(x) * (y) * _PIP_SUB_BW_RESERVE_INPUT_CVT_TIMING_VPORCH_MIN_US / 10000), (1000 - (y) * _PIP_SUB_BW_RESERVE_INPUT_CVT_TIMING_VPORCH_MIN_US / 10000)))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
extern DWORD g_ulFRCRowForMain;
extern DWORD g_ulFRCRowForSub;
extern DWORD g_ulFRCSubAllocateIHtotal;
#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
extern bit g_bFRCModLenWtlvlStatus;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumDDomainSourceSelect ScalerFRCGetSourceSelect(EnumInputDataPath enumInputPath);
extern void ScalerFRCMuteChannelControl(EnumInputDataPath enumInputPath, bit bEnable);
extern bit ScalerFRCGetMuteChannelEnable(EnumInputDataPath enumInputPath);

#if(_FRC_SUPPORT == _ON)
extern void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize);
extern void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);
extern void ScalerFRCSetFRCEnble(void);
extern DWORD ScalerFRCGetDispAddress(WORD usSelectedPage, EnumFRCBlock enumBlock);
extern void ScalerFRCSetDispTopLinestep(WORD usSelectedPage, DWORD ulLinestep);
extern void ScalerFRCSetDispTopWaterLevel(EnumFRCPageSelect enumPageSelect, BYTE ucLen);
extern void ScalerFRCSetCapLinenum(EnumFRCPageSelect enumPageSelect, WORD usVerSize);
extern void ScalerFRCSetCapLinestep(EnumFRCPageSelect enumPageSelect, DWORD ulLineStep);
extern void ScalerFRCSetFSIVS2DVSDelayWhenActiveState(WORD usIVS2DVSDelay, const StructTimingInfo *pstMdomainInputInfo, const StructDisplayInfo *pstMdomainOutputInfo);
extern void ScalerFRCOneFrameCtrl(void);
extern BYTE ScalerFRCIVS2DVSDelayMargin(void);
extern DWORD ScalerFRCGetPathMaxLineSumBitByBW(DWORD ulGrantBW, StructMemoryBWUsageParam *pstMemBWParam);
extern BYTE ScalerFRCGettFRCRateCtrlParamCnt(void);
extern EnumImgCmpParamIndex ScalerFRCGetRcpImcCmpParamFromIndex(BYTE ucIndex);
extern bit ScalerFRCGetRcpHsdEnFromIndex(BYTE ucIndex);
extern EnumODParamIndex ScalerFRCGetRcpODParamFromIndex(BYTE ucIndex);

#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_HDMI21_ALLM_SUPPORT == _ON))
extern WORD ScalerFRCGetIVS2DVSDelayMax(void);
#endif

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
extern void ScalerFRCSetAspectRatioDDomain(void);
#endif

extern EnumFRCIndex ScalerFRCCalculateAddressMapping(EnumFRCPageSelect enumPageSelect);

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
extern BYTE ScalerFRCGetImgCmpHwidthDivisor(EnumMDomainDisplayDataPath enumMDispPath, EnumImgCmpParamIndex enumImgCmpIndex);
#endif
extern DWORD ScalerFRCGetBaseAddress(EnumFRCIndex enumFRCIndex);
extern void ScalerFRCBWAllocateForSubOption(WORD *pusSubCaphwidth, WORD *pusSubDisphwidth, DWORD *pulSubMaxClk);

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
extern bit ScalerFRC2PFrameSyncBypassNonFrameSyncRegion(void);
#endif

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
extern void ScalerFRCSetDisplayAutoBlkToggle(void);
extern void ScalerFRCSetDisplayAutoBlkToggleEnable(bit bEn);
extern void ScalerFRCSetHWAutoBlockToggle(void);
extern void ScalerFRCSetInputAutoBlkToggle(void);
#endif
extern void ScalerFRCSetInitialRegValue(EnumInputDataPath enumFRCSyncDataPath);
#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
extern bit ScalerFRCModLenWtlvl(void);
#endif
extern void ScalerFRCUpdateFifoScalingSize(StructSDRAMDataInfo *pstFIFOSize);
extern void ScalerFRCSetFrameTearPrevent(EnumInputDataPath enumInputDataPath);

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
extern void ScalerFRCSetDispBotLinestep(WORD usSelectedPage, DWORD ulLinestep);
#endif


#if((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) && (_FRC_CAPTURE_BW_CTRL_SUPPORT == _ON))
extern void ScalerFRCBwCtrlGetCapClientInfo(StructBwCtrlClientInfo *pstInfo);
#endif
#if((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) && (_FRC_DISPLAY_BW_CTRL_SUPPORT == _ON))
extern void ScalerFRCBwCtrlGetDispClientInfo(StructBwCtrlClientInfo *pstInfo);
#endif

#endif // End of #if(_FRC_SUPPORT == _ON)

#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_HDMI21_ALLM_SUPPORT == _ON))
extern WORD ScalerFRCLatencyControl(EnumInputPort enumInputPort, EnumSourceType enumSourceType, WORD usDelayMax, WORD usIVS2DVSDelay);
#endif

#endif // End of #ifndef __SCALER_FRC_H__
