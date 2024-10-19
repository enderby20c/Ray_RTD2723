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
// ID Code      : ScalerScaling.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_SCALING_H__
#define __SCALER_SCALING_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _HSD_TABLE_SIZE                                   128
#define _VSD_TABLE_SIZE                                   64
#if((_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON))
#define _A1A2_REG_ADDR_OFFSET                             (WORD)(P0_39_SF_ADDR_PORT_R1_ACTIVE2 - P0_33_SF_ADDR_PORT_R1_ACTIVE1)
#endif

#if(_SHARPNESS_FUNCTION == _OFF)
#define _HSU_TABLE_SIZE                                   128
#define _VSU_TABLE_SIZE                                   128
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#define GET_IDOMAIN_4PATH_STATUS()                        (g_ucScalingIdomain4PathStatus)
#define SET_IDOMAIN_4PATH_STATUS(x)                       (g_ucScalingIdomain4PathStatus = (x))
#endif

#if(_SHARPNESS_FUNCTION == _ON)
#define _SHARPNESS_TABLE_SIZE                             (128)
#define _HSU_MIN_PORCH_SIZE                               (300)// unit : us
#endif

#define _SD_BYPASS_FACTOR                                 0x100000

#define _DDOMAIN_IN_EXTENSION_DEFAULT                     (6)

#define GET_MDOMAIN_EXT_RECAP_EXTENSION_LEN()             (((GET_MDOMAIN_OUTPUT_RGN() & (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R3_A1)) != 0) ? GET_EXT_RECAP_EXTENSION_LEN_A1() : GET_EXT_RECAP_EXTENSION_LEN_A2())

#define _ES_ORIGINAL_MODE_ADJUST_TOLERANCE                (6)

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
#define _FB_PBPLR_MINIMUM_LEN                             (8)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_SHARPNESS_FUNCTION == _ON)
typedef enum
{
    _FORCE_TO_BG_STATUS,
    _NORMAL_STATUS,
    _LIMITED_PORCH_STATUS,
} EnumSharpnessWaitStatus;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern BYTE g_ucScalingIdomain4PathStatus;
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerScalingSetScalingDownInitial(bit bEvenOdd, WORD usRegPageSel);
extern void ScalerScalingSetHScalingDown(const StructSDRAMDataInfo *pstFIFOScaling, bit bEvenOdd, WORD usRegPageSel);
extern void ScalerScalingSetVScalingDown(const StructSDRAMDataInfo *pstFIFOScaling, bit bEvenOdd, WORD usRegPageSel);
extern void ScalerScalingSetScalingDownWindow(const StructSDRAMDataInfo *pstFIFOScaling, bit bEvenOdd, WORD usRegPageSel);
extern void ScalerScalingSetScalingUpInitial(WORD usRegPagedAddrSel);
extern void ScalerScalingSetHScalingUp(const StructSDRAMDataInfo *pstFIFOScaling, WORD usRegPagedAddrSel);
extern void ScalerScalingSetVScalingUp(const StructSDRAMDataInfo *pstFIFOScaling, WORD usRegPagedAddrSel);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerScalingSetDDomainExtension(void);
#endif

#if(((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON)) && (_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE) && (_SD_TABLE_SEL_FUNCTION == _OFF))
extern void ScalerScalingSetFSScalingDown(WORD usRegPageSel);
#endif

extern void ScalerScalingUpdateFIFOScalingSize(StructSDRAMDataInfo *pstData);
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern void ScalerScalingSetRotationFrameBuffer(void);
extern bit ScalerScalingGetRotation3FrameBufferHSDstatus(WORD usWidth, WORD usVheight);
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
extern void ScalerScalingUpdatePBPTopDVHeight(StructSDRAMDataInfo *pstData);
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
extern WORD ScalerScalingGetEOModePageMapping(WORD usRegPageSel);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern BYTE ScalerScalingCalculateExtensionRecaptureExtNum(WORD usMdmInputHWidth);
#endif

extern bit ScalerScalingGetVScalingDownBypass(WORD usRegPageSel);
extern void ScalerScalingSetHScalingUpInitialPhase(WORD usRegPagedAddrSel, DWORD ulHSUI);

#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_1)
extern void ScalerScalingSetHScalingDownVactRefInputWindow(bit bEnable, bit bEvenOdd, WORD usRegPageSel, WORD usEOPage);
extern void ScalerScalingSetVScalingDownVactRefInputWindowSelect(bit bEnable, bit bEvenOdd, WORD usRegPageSel, WORD usEOPage);
#endif

#endif // End of #ifndef __SCALER_SCALING_H__
