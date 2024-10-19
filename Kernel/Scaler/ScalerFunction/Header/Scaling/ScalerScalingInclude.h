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
// ID Code      : ScalerScalingInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_VER_FILTER_COEF_INI(ulBackup)           {\
                                                        BYTE pucVerCoefIniBackup[3] = {0};\
                                                        pucVerCoefIniBackup[0] = ScalerGetDataPortSingleByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_11_VER_FILTER_COEF_INI_R1_ACTIVE1);\
                                                        pucVerCoefIniBackup[1] = ScalerGetDataPortSingleByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_16_VER_FILTER_COEF_INI_M_R1_ACTIVE1);\
                                                        pucVerCoefIniBackup[2] = ScalerGetDataPortSingleByte(P0_33_SF_ADDR_PORT_R1_ACTIVE1, _P0_34_PT_17_VER_FILTER_COEF_INI_L_R1_ACTIVE1);\
                                                        (ulBackup) = (((((DWORD)pucVerCoefIniBackup[0] << 12) & 0xFF000) | (((DWORD)pucVerCoefIniBackup[1] << 4) & 0x00FF0) | ((pucVerCoefIniBackup[2] >> 4) & 0x0000F)) & 0x000FFFFF);\
                                                        (ulBackup) = ((ulBackup) >> 13);\
                                                    }

//--------------------------------------------------
// Definition of Scaling Factor Bit
//--------------------------------------------------
#define _HSD_FACTOR_BIT                             (20)
#define _HSU_FACTOR_BIT                             (20)
#define _VSU_FACTOR_BIT                             (20)


#define _VSD_FACTOR_BIT                             (20)

//--------------------------------------------------
// Definition of D-domain extension
//--------------------------------------------------
#define GET_DDOMAIN_EXTENSION_LEN()                 (g_stMDomainOutputData.ucExtensionLEn)
#define SET_DDOMAIN_EXTENSION_LEN(x)                (g_stMDomainOutputData.ucExtensionLEn = (x))

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#define GET_DROP_EXTENSION_LENGTH()                 (g_ucScalingDropExtension)
#define SET_DROP_EXTENSION_LENGTH(x)                (g_ucScalingDropExtension = (x))
#endif

#define GET_EXT_RECAP_EXTENSION_LEN_A1()            (g_stScalingInfo.ucExtRecapExtLenA1)
#define SET_EXT_RECAP_EXTENSION_LEN_A1(x)           (g_stScalingInfo.ucExtRecapExtLenA1 = (x))

#define GET_EXT_RECAP_EXTENSION_LEN_A2()            (g_stScalingInfo.ucExtRecapExtLenA2)
#define SET_EXT_RECAP_EXTENSION_LEN_A2(x)           (g_stScalingInfo.ucExtRecapExtLenA2 = (x))

#define GET_EXT_RECAP_MOVING_LEN()                  (g_stScalingInfo.usMoveingLen)
#define SET_EXT_RECAP_MOVING_LEN(x)                 (g_stScalingInfo.usMoveingLen = (x))
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE ucExtRecapExtLenA1;
    BYTE ucExtRecapExtLenA2;
    WORD usMoveingLen;
} StructScalingInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern BYTE g_ucScalingDropExtension;
#endif

extern StructScalingInfo g_stScalingInfo;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerScalingSetInitial(void);
extern void ScalerScalingSetScalingUp(const StructSDRAMDataInfo *pstFIFOScaling);
extern void ScalerScalingSetScalingDown(const StructSDRAMDataInfo *pstFIFOScaling);
extern bit ScalerScalingGetFIFOScalingSize(StructSDRAMDataInfo *pstData);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerScalingGetFBFrameStatus(EnumSelRegion enumSelRegion);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerScalingSetExtensionRecaptureInitial(void);
extern void ScalerScalingSetExtensionRecapture(WORD usMdmInputHWidth, WORD usMdmInputVHeight);
extern void ScalerScalingSetExtensionRecaptureEnable(EnumDDomainRegion enumDDomainRegion, bit bEn);
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
extern WORD ScalerScalingGetExtRecapMovingLength(WORD usMdmInputHWidth);
#endif
extern bit ScalerScalingGetPBPLRSingleRegionStatus(WORD usActiveHstart, WORD usActiveHwidth);
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
extern void ScalerScalingSetScalingCoef(EnumSelRegion enumSelRegion, BYTE *pucAddress1, BYTE *pucAddress2, BYTE ucBankNum);
#endif

#if(_FRC_SUPPORT == _ON)
#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_0)
extern WORD ScalerScalingGetHFrontPorchAfterHSD(EnumInputDataPath enumInputPath, WORD usOutWidth, WORD usInWidth, WORD usHfporch, bit bFBmode);
extern WORD ScalerScalingGetHBackPorchAfterHSD(EnumInputDataPath enumInputPath, WORD usHbporch, bit bFBmode);
#endif
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
extern DWORD ScalerScalingGetESOriginalModeMainSubDiffHstart(void);
extern DWORD ScalerScalingGetESOriginalModeMainSubDiffVstart(void);
#endif
#endif
