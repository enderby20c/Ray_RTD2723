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
// ID Code      : ScalerImgCmpInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)

#define _IMG_CMP_MEM_RW_UNIT                            (128)
#define _IMG_CMP_BLK_WIDTH                              (1)
#define _IMG_CMP_STREAM_END_DUMMY_LEN                   (0)
#define _IMC_LATENCY                                    (2) // IMC = IMC encode + IMC decode = 570 pixel + 1 line

#define CHK_PATH_EQUIP_IMG_CMP(x)                       (((x) != _INPUT_PATH_NONE) && ((_HW_M_DOMAIN_IMG_CMP_ALL_PATH & (x)) == (x)))
#define CHK_PATH_EQUIP_IMG_DECMP(x)                     (((x) != _MDOMAIN_DISP_PATH_NONE) && ((_HW_M_DOMAIN_IMG_DECMP_ALL_PATH & (x)) == (x)))
#define CHK_EQUIP_IMG_CMP_DECMP(x, y)                   (CHK_PATH_EQUIP_IMG_CMP(x) && CHK_PATH_EQUIP_IMG_DECMP(y))

#define GET_IMG_CMP_DATA_PATH(x)                        (((x) < _HW_M_DOMAIN_IMG_CMP_PATH_COUNT) ? (tFRCImgCmpDecmpPathInfo[x].enumCmpPath) : (_INPUT_PATH_NONE))
#define GET_IMG_DECMP_DATA_PATH(x)                      (((x) < _HW_M_DOMAIN_IMG_CMP_PATH_COUNT) ? (tFRCImgCmpDecmpPathInfo[x].enumDecmpPath) : (_MDOMAIN_DISP_PATH_NONE))
#define GET_IMG_CMP_REG_PAGE(x)                         (((x) < _HW_M_DOMAIN_IMG_CMP_PATH_COUNT) ? (tFRCImgCmpDecmpPathInfo[x].ucFRCImgCmpRegPage) : (0xFF))
#define GET_IMG_DECMP_REG_PAGE(x)                       (((x) < _HW_M_DOMAIN_IMG_CMP_PATH_COUNT) ? (tFRCImgCmpDecmpPathInfo[x].ucFRCImgDecmpRegPage) : (0xFF))
#endif

#define GET_IMG_CMP_ENABLE(x)                           (g_pstImgCmpParam[(x)].b1Enable)
#define GET_IMG_CMP_PARAM_DATA_DEPTH(x)                 (g_pstImgCmpParam[(x)].b5ColorDepth)
#define GET_IMG_CMP_PARAM_LLB(x)                        (g_pstImgCmpParam[(x)].ucLineLimitBit)

#define _IMG_CMP_MIN_INPUT_WIDTH                        (800)
#define _IMG_CMP_MIN_PIXEL_NUMBER                       (15000)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef struct
{
    BYTE b1Enable : 1;
    BYTE b5ColorDepth : 5;
    BYTE ucLineLimitBit;
} StructImgCmpParam;

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
typedef struct
{
    EnumInputDataPath enumCmpPath;
    EnumMDomainDisplayDataPath enumDecmpPath;
    BYTE ucFRCImgCmpRegPage;
    BYTE ucFRCImgDecmpRegPage;
    BYTE ucFRCRegPage;
} StructFRCImgCmpDecmpPathInfo;

typedef struct
{
    WORD usFullHorSize;
    WORD usFullVerSize;

    EnumInputDataPath enumCmpPath;
    EnumMDomainDisplayDataPath enumDecmpPath;
    EnumImgCmpParamIndex enumCmpParamIndex;

    BYTE b1CmpEOMode : 1;
    BYTE b1DecmpEOMode : 1;
    BYTE b1FrontBackMode : 1;
} StructImgCmpDecmpInfo;

#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructImgCmpParam g_pstImgCmpParam[];


#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
extern StructFRCImgCmpDecmpPathInfo code tFRCImgCmpDecmpPathInfo[_HW_M_DOMAIN_IMG_CMP_PATH_COUNT];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
extern void ScalerImgCmpCtrl(WORD usHWidth, WORD usVHeight, EnumImgCmpParamIndex enumCmpParamIndex);
extern void ScalerImgCmpEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath enumSelFrcCapPath, bit bEn);
extern bit ScalerImgCmpGetMultiSliceEn(EnumDisplayRegion enumDisplayRegion);
#endif

