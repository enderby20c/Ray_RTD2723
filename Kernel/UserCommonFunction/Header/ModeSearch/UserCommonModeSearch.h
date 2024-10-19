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
// ID Code      : UserCommonModeSearch.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_MODE_SEARCH_H__
#define __USER_COMMON_MODE_SEARCH_H__

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of FIFO Mode Match Status
//--------------------------------------------------
#define _MODE_NOT_EXIST_IN_FIFO                     251

//--------------------------------------------------
// Definitions of VTotal Tolerance For Preset Mode
//--------------------------------------------------
#define _PRESET_MODE_VTOTAL_TOLERANCE               2

//--------------------------------------------------
// Definitions of V Height Tolerance For Preset Mode
//--------------------------------------------------
#define _PRESET_MODE_VHEIGHT_TOLERANCE              2

//--------------------------------------------------
// Definitions of The Diffrence Between GTF Height and Mode Table Height
//--------------------------------------------------
#define _USER_MODE_VHEIGHT_GTF_DIFF_TOL             20
#define _USER_MODE_VHEIGHT_GTF_DIFF_MIN             3

//--------------------------------------------------
// Definitions of H Ratio (IHWidth/IHTotal) Tolerance
//--------------------------------------------------
#define _H_RATIO_TOLERANCE                          150

//--------------------------------------------------
// Marcos for Extracting Mode Table Information
//--------------------------------------------------
#define GET_MODE_TABLE_POLARITY(x)                  ((x).ucMiscFlag & 0x0F)
#define GET_MODE_TABLE_INTERLACED(x)                ((bit)(((x).ucMiscFlag & _INTERLACE_MODE) >> 5))
#define GET_MODE_TABLE_VIDEO(x)                     ((bit)((x).ucMiscFlag & (_VIDEO_MODE_GROUP1 | _VIDEO_MODE_GROUP2 | _VIDEO_MODE_GROUP3)))

//--------------------------------------------------
// Macro of Mode Search Type
//--------------------------------------------------
#define GET_MODE_SEARCH_TYPE()                      ((bit)(g_ucModeSearchCtrl & _BIT0))
#define SET_MODE_SEARCH_TYPE(x)                     (g_ucModeSearchCtrl = ((g_ucModeSearchCtrl & ~(_BIT0)) | ((x) << 0)))

//--------------------------------------------------
// Macro of Input Mode GTF Height
//--------------------------------------------------
#define GET_INPUT_MODE_GTF_HEIGHT()                 (g_usModeSearchCurrGTFValue)
#define SET_INPUT_MODE_GTF_HEIGHT(x)                (g_usModeSearchCurrGTFValue = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Check Mode VGA Result Enum
//--------------------------------------------------
typedef enum
{
    _MODE_INDIRECT_DEFLECTION_PIC = 0,
    _MODE_DIRECT_DEFLECTION_PIC,
    _MODE_INDIRECT_MIN_CLOCK,
    _MODE_DIRECT_MIN_CLOCK,
    _MODE_INDIRECT_SUCCESS,
    _MODE_DIRECT_SUCCESS,
}EnumModeFrameSyncGradeResult;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit UserCommonModeSearchOORModeByMeasureInfo(void);
extern BYTE UserCommonModeSearchPresetMode(void);
extern BYTE UserCommonModeSearchUserMode(void);
extern bit UserCommonModeSearchCheckPresetMode(BYTE ucModeIndex);
extern bit UserCommonModeSearchCheckUserModeMode(BYTE ucModeIndex);
extern BYTE UserCommonModeSearchBestMode(BYTE ucCurrModeIndex, BYTE ucLastModeIndex);
extern bit UserCommonModeSearchCheckModeSetting(BYTE ucModeIndex);
extern bit UserCommonModeSearchPresetModeCheckOOR(BYTE ucModeIndex);
extern BYTE UserCommonModeSearchCompareByMultipleCondition(BYTE ucCurrModeIndex, BYTE ucLastModeIndex);

#if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)
extern bit UserCommonModeSearchCompareIVHeight(BYTE ucLastModeIndex, BYTE ucCurrModeIndex, BYTE *pucModeBestInx);
#endif // #if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)

extern WORD UserCommonModeSearchGetHeightByGTF(WORD usVTotal, WORD usVFreq);
extern bit UserCommonModeSearchCheckHFreq(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
extern bit UserCommonModeSearchCheckVFreq(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
extern bit UserCommonModeSearchCheckGTFHeight(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
extern bit UserCommonModeSearchHVSyncPulseCheck(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
extern bit UserCommonModeSearchCompareByPolarity(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
extern bit UserCommonModeSearchCompareByInterlace(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
extern bit UserCommonModeSearchCompareByVideoModeFlg(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
extern void UserCommonModeSearchFIFOSaveModeInfo(BYTE ucIndex);
extern BYTE UserCommonModeSearchCheckFIFOModeSaved(BYTE ucModeIndex);
extern void UserCommonModeSearchUpdateInputDataRefModeTbl(BYTE ucIndex);
extern void UserCommonModeSearchUpdateInputDataRefFIFO(BYTE ucFifoIndex, BYTE ucIndex);
extern bit UserCommonModeSearchCheckFIFOSetting(StructVgaModeUserDataType stFifoUserData, BYTE ucModeIndex);

#endif // End of #if(_VGA_SUPPORT == _ON)


#endif // End of #ifndef __USER_COMMON_MODE_SEARCH_H__
