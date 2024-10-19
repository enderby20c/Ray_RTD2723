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
// ID Code      : ScalerVgipInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of VGIP IH Capture Start Min Value
//--------------------------------------------------
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#define _VGIP_IH_CAPTURE_MIN_VALUE                  ((ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE) ? 20 : 10)
#define _VGIP_IV_CAPTURE_MIN_VALUE                  ((ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE) ? 8 : 4)
#else
#define _VGIP_IH_CAPTURE_MIN_VALUE                  (10)
#define _VGIP_IV_CAPTURE_MIN_VALUE                  (4)
#endif

//--------------------------------------------------
// Definitions of VGIP IV Capture Start Max Value
//--------------------------------------------------
#define _VGIP_IV_CAPTURE_MAX_VALUE                  _HW_VGIP_IV_CAPTURE_BIT

//--------------------------------------------------
// Definitions of VGIP IHDelay Max Value
//--------------------------------------------------
#define _VGIP_IH_DELAY_MAX_VALUE                    1023

//--------------------------------------------------
// Definitions of VGIP IHstart Max Value
//--------------------------------------------------
#define _VGIP_IH_START_MAX_VALUE                    0xFFC

//--------------------------------------------------
// Definitions of VGIP latched HSW
//--------------------------------------------------
#define _VGIP_LATCHED_HSYNCWIDTH                    ((ScalerFmtCnvFtoPGetStatus(g_pstMeasureRegionTimingInfoPointer->stTimingInfo.enumInputDataPath) == _TRUE) ? 16 : 8)

//--------------------------------------------------
// Definitions of VGIP latched VSW
//--------------------------------------------------
#define _VGIP_LATCHED_VSYNCWIDTH                    ((ScalerFmtCnvFtoPGetStatus(g_pstMeasureRegionTimingInfoPointer->stTimingInfo.enumInputDataPath) == _TRUE) ? 6 : 3)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerVgipInputInitial(EnumSourceType enumSourceType, EnumInputPort enumInputPort);

extern void ScalerVgipSetInputPath(EnumInputDataPath enumVgipInputPath);
extern void ScalerVgipCaptureEnable(bit bEnable);
extern void ScalerVgipSetVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable);
extern bit ScalerVgipGetVsBypassEnable(EnumInputDataPath enumInputDataPath);
extern void ScalerVgipModifyPolarity(EnumSourceType enumSourceType);

extern void ScalerVgipSetDigitalCaptureStatus(bit bEnable);

extern void ScalerVgipSetCaptureHWidth(WORD usIHwidth);

extern void ScalerVgipSetCaptureVHeight(WORD usIVheight);
extern void ScalerVgipSetCaptureVStartPosition(WORD usIVstart);

#if(_MULTI_DISPLAY_MAX != 0x01)
extern void ScalerVgipClearInterlaceFlag(EnumInputDataPath enumInputDataPath);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
extern void ScalerVgipVgipDoubleBufferApply(EnumDBApply enumDBApply);
extern EnumVGIPDBEnableStatus ScalerVgipGetVGIPDBStatus(void);
#endif

