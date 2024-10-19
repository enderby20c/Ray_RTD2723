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
// ID Code      : UserCommonColorGlobalDimmingInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of OCC/OGC Options
//--------------------------------------------------
typedef enum
{
    _SDR_SRGB,
    _SDR_ADOBE_RGB,
    _SDR_EBU_MODE,
    _SDR_REC_709,
    _SDR_DCI_P3,
    _SDR_OGC_CASE_1,
    _SDR_OGC_CASE_2,
    _SDR_OGC_CASE_3,
    _SDR_OGC_CASE_4,
    _SDR_OGC_CASE_5,
    _SDR_OGC_CASE_6,
    _SDR_NONE_OGC_OCC,
} EnumSDRMode;

//--------------------------------------------------
// Enumerations of SDR Calibration
//--------------------------------------------------
typedef enum
{
    _SDR_CALIB_FALSE = _FALSE,
    _SDR_CALIB_TRUE = _TRUE,
} EnumSDRCalibrationStatus;


typedef enum
{
    _GD_PATTERN_MIDDLE_BLACK = 0,
    _GD_PATTERN_NONE,
} EnumGDPatternType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
extern EnumGlobalDimmingStatus UserCommonColorGlobalDimmingGetEnableStatus(void);
extern void UserCommonColorGlobalDimmingAdjust(void);
extern WORD UserCommonColorGlobalDimmingGetMainApplyGain(void);
extern void UserCommonColorGlobalDimmingSetForceMainEffect(void);



#if(_GLOBAL_DIMMING_PATTERN_ESTIMATE == _ON)
extern bit UserCommonColorGlobalDimmingPatternEstimate(EnumGDPatternType enumPatternType);
#endif

#endif

