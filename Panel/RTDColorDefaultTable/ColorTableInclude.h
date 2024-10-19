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
// Color Default Value
//----------------------------------------------------------------------------------------------------
#include <RTDColorDefaultTable/ColorDitherDefault.h>
#include <RTDColorDefaultTable/ColorTempDefault.h>

#ifdef __USER_PANEL__

#if(_DCC_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// DCC Table
//----------------------------------------------------------------------------------------------------
BYTE code tDCC_GAME[] =
{
#include <RTDColorDefaultTable/DCC/DccModeGame.h>
};

BYTE code tDCC_MOVIE[] =
{
#include <RTDColorDefaultTable/DCC/DccModeMovie.h>
};

BYTE code tDCC_PHOTO[] =
{
#include <RTDColorDefaultTable/DCC/DccModePhoto.h>
};

BYTE code tDCC_VIVID[] =
{
#include <RTDColorDefaultTable/DCC/DccModeVivid.h>
};

BYTE * code tDCC_TABLE[] =
{
    _NULL_POINTER,  // Standard
    tDCC_GAME,
    tDCC_MOVIE,
    tDCC_PHOTO,
    tDCC_VIVID,
};
#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_ICM_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// ICM Table
//----------------------------------------------------------------------------------------------------
BYTE code tICM_GAME[] =
{
#include <RTDColorDefaultTable/ICM/IcmModeGame.h>
};

BYTE code tICM_MOVIE[] =
{
#include <RTDColorDefaultTable/ICM/IcmModeMovie.h>
};

BYTE code tICM_PHOTO[] =
{
#include <RTDColorDefaultTable/ICM/IcmModePhoto.h>
};

BYTE code tICM_VIVID[] =
{
#include <RTDColorDefaultTable/ICM/IcmModeVivid.h>
};

BYTE * code tICM_TABLE[] =
{
    _NULL_POINTER,  // Standard
    tICM_GAME,
    tICM_MOVIE,
    tICM_PHOTO,
    tICM_VIVID,
};

//----------------------------------------------------------------------------------------------------
// SCM Table
//----------------------------------------------------------------------------------------------------
BYTE code tSCM_VIVID[] =
{
#include <RTDColorDefaultTable/ICM/ScmModeVivid.h>
};

BYTE * code tSCM_TABLE[] =
{
    _NULL_POINTER,  // Standard
    _NULL_POINTER,  // Game
    _NULL_POINTER,  // Movie
    _NULL_POINTER,  // Photo
    tSCM_VIVID,
};

#endif // End of #if(_ICM_SUPPORT == _ON)

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
#if(_ICM_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
//ICM Table For LC
//----------------------------------------------------------------------------------------------------
BYTE code tICM_LC_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrast_ColorEnhanceTable.h>
};
#endif // End of #if(_ICM_FUNCTION == _ON)
#endif // End of #if(_LOCAL_CONTRAST_FUNCTION == _ON)

#if(_SDR_PLUS_FUNCTION == _ON)
#if(_ICM_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
//ICM Table For SDR+
//----------------------------------------------------------------------------------------------------
BYTE code tICM_SDR_PLUS_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrast_SDRPlus_ColorEnhanceTable.h>
};
#endif
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
BYTE code tSDRTOHDR_INPUTGAMMA[] =
{
#include <RTDColorDefaultTable/SDRtoHDR/SDRtoHDRInputGammaTable.h>
};

BYTE code tSDRTOHDR_ICM[] =
{
#include <RTDColorDefaultTable/SDRtoHDR/SDRtoHDRICMTable.h>
};

BYTE code tSDRTOHDR_DCC[] =
{
#include <RTDColorDefaultTable/SDRtoHDR/SDRtoHDRDCCTable.h>
};
#endif

#if(_DM_FUNCTION == _ON)
BYTE code tDM_INPUTGAMMA[] =
{
#include <RTDColorDefaultTable/DM/DMInputGammaTable.h>
};
#endif
#endif // End of #ifdef __USER_PANEL__



#ifdef __USER_ADJUST__
#if(_OD_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// OD Table
//----------------------------------------------------------------------------------------------------
#include <RTDColorDefaultTable/ODTable.h>

BYTE * code tOD_TABLE[] =
{
    tOD_TABLE_COMMON,
};

#if(_FREESYNC_SUPPORT == _ON)
BYTE * code tOD_FREESYNC_TABLE[] =
{
    tOD_TABLE_FREESYNC,
};
#endif

#if(_OD_BY_POSITION_SUPPORT == _ON)
#include <RTDColorDefaultTable/BPODTable.h>

BYTE * code tOD_BYPOS_TABLE[] =
{
    tOD_BYPOS_TABLE_SET0,
};
#endif

#endif // End of #if(_OD_SUPPORT == _ON)

BYTE code tHDR_INPUT_GAMMA_540_TONE_MAPPING_DARK_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/RTK_ToneMapping_540_Dark.h>
};

BYTE code tHDR_INPUT_GAMMA_540_TONE_MAPPING_NORMAL_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/RTK_ToneMapping_540_Normal.h>
};

BYTE code tHDR_INPUT_GAMMA_1200_TONE_MAPPING_NORMAL_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/RTK_ToneMapping_1200_Normal.h>
};

BYTE code tHDR_INPUT_GAMMA_1200_TONE_MAPPING_DARK_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/RTK_ToneMapping_1200_Dark.h>
};

BYTE code tHDR_INPUT_GAMMA_4000_TONE_MAPPING_NORMAL_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/RTK_ToneMapping_4000_Normal.h>
};

BYTE code tHDR_INPUT_GAMMA_4000_TONE_MAPPING_DARK_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/RTK_ToneMapping_4000_Dark.h>
};

BYTE code tHDR_INPUT_GAMMA_10000_TONE_MAPPING_NORMAL_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/RTK_ToneMapping_10000_Normal.h>
};

BYTE code tHDR_INPUT_GAMMA_10000_TONE_MAPPING_DARK_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/RTK_ToneMapping_10000_Dark.h>
};

BYTE code tHDR_INPUT_GAMMA_PEAK_NOTONE_MAPPING_NORMAL_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/NoToneMapping_Normal.h>
};

BYTE code tHDR_INPUT_GAMMA_PEAK_NOTONE_MAPPING_DARK_LUT[] =
{
#include <RTDColorDefaultTable/HDR/HDRTable/NoToneMapping_Dark.h>
};

BYTE * code tusHDR10_IG_USER_ADDRESS_INDEX[] =
{
    tHDR_INPUT_GAMMA_540_TONE_MAPPING_NORMAL_LUT,
    tHDR_INPUT_GAMMA_540_TONE_MAPPING_DARK_LUT,
    tHDR_INPUT_GAMMA_1200_TONE_MAPPING_NORMAL_LUT,
    tHDR_INPUT_GAMMA_1200_TONE_MAPPING_DARK_LUT,
    tHDR_INPUT_GAMMA_4000_TONE_MAPPING_NORMAL_LUT,
    tHDR_INPUT_GAMMA_4000_TONE_MAPPING_DARK_LUT,
    tHDR_INPUT_GAMMA_10000_TONE_MAPPING_NORMAL_LUT,
    tHDR_INPUT_GAMMA_10000_TONE_MAPPING_DARK_LUT,
    tHDR_INPUT_GAMMA_PEAK_NOTONE_MAPPING_NORMAL_LUT,
    tHDR_INPUT_GAMMA_PEAK_NOTONE_MAPPING_DARK_LUT,
};
#endif // __USER_ADJUST__

#ifdef __USER_COMMON_COLOR__

//----------------------------------------------------------------------------------------------------
// Dithering Table
//----------------------------------------------------------------------------------------------------
#if(_I_DITHER_FUNCTION == _ON)
BYTE code tIDITHER_TABLE_FIFO8[] =
{
#if((_HW_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT))
#include <RTDColorDefaultTable/IDither/IDitherTableGen0Fifo8.h>
#elif((_HW_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) ||\
      (_HW_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) ||\
      (_HW_IDITHER_TYPE == _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
#if(_HW_IDITHER_SUPER_PIXEL_SUPPORT == _OFF)
#include <RTDColorDefaultTable/IDither/IDitherTableGen1Fifo8.h>
#else
#if(_I_DITHER_SUPER_PIXEL_SIZE == _IDITHER_SUPER_PIXEL_2X2)
#include <RTDColorDefaultTable/IDither/IDitherTableGen1Fifo8.h>
#else
#include <RTDColorDefaultTable/IDither/IDitherTableGen2Fifo8.h>
#endif
#endif
#endif
};

BYTE code tIDITHER_TABLE_FIFO10[] =
{
#if((_HW_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT))
#include <RTDColorDefaultTable/IDither/IDitherTableGen0Fifo10.h>
#elif((_HW_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) ||\
      (_HW_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) ||\
      (_HW_IDITHER_TYPE == _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
#include <RTDColorDefaultTable/IDither/IDitherTableGen1Fifo10.h>
#endif
};

BYTE code tIDITHER_SEQ_TABLE[] =
{
#if((_HW_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT))
#include <RTDColorDefaultTable/IDither/IDitherTableSeq1.h>
#elif((_HW_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) ||\
      (_HW_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) ||\
      (_HW_IDITHER_TYPE == _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
#if((_I_DITHER_MULTI_SEQ_ENABLE == _DISABLE) &&\
    (_I_DITHER_SERIES_SEQ_ENABLE == _DISABLE) &&\
    (_I_DITHER_12_TO_10_MULTI_SEQ_ENABLE == _DISABLE) &&\
    (_I_DITHER_12_TO_10_SERIES_SEQ_ENABLE == _DISABLE))
#include <RTDColorDefaultTable/IDither/IDitherTableSeq1.h>
#else
#include <RTDColorDefaultTable/IDither/IDitherTableSeq4.h>
#endif
#endif
};

#if((_HW_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
BYTE code tIDITHER_TEMPOFFSET_TABLE[] =
{
#include <RTDColorDefaultTable/IDither/IDitherTableTempo.h>
};
#endif
#endif // End of #if(_I_DITHER_SUPPORT == _ON)

#if(_D_DITHER_FUNCTION == _ON)

#if(_PANEL_EXIST_MULTIPANEL == _OFF)

BYTE code tDDITHER_TABLE[] =
{
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include <RTDColorDefaultTable/DDither/DDitherGen0Dither18Bit.h>
#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
#include <RTDColorDefaultTable/DDither/DDitherGen1Dither30Bit.h>
#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2)
#include <RTDColorDefaultTable/DDither/DDitherGen1Dither24Bit.h>
#endif

#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include <RTDColorDefaultTable/DDither/DDitherGen0Dither24Bit.h>
#elif((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#include <RTDColorDefaultTable/DDither/DDitherGen1Dither24Bit.h>
#endif

#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include <RTDColorDefaultTable/DDither/DDitherGen0Dither30Bit.h>
#elif((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#include <RTDColorDefaultTable/DDither/DDitherGen1Dither30Bit.h>
#endif

#endif
};

#else // Else of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

#if(_HW_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
BYTE code tDDITHER_TABLE18Bit[] =
{
#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include <RTDColorDefaultTable/DDither/DDitherGen0Dither18Bit.h>
#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
#include <RTDColorDefaultTable/DDither/DDitherGen1Dither30Bit.h>
#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2)
#include <RTDColorDefaultTable/DDither/DDitherGen1Dither24Bit.h>
#endif
};
#endif

BYTE code tDDITHER_TABLE24Bit[] =
{
#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include <RTDColorDefaultTable/DDither/DDitherGen0Dither24Bit.h>
#elif((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#include <RTDColorDefaultTable/DDither/DDitherGen1Dither24Bit.h>
#endif
};

BYTE code tDDITHER_TABLE30Bit[] =
{
#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include <RTDColorDefaultTable/DDither/DDitherGen0Dither30Bit.h>
#elif((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#include <RTDColorDefaultTable/DDither/DDitherGen1Dither30Bit.h>
#endif
};

#endif

BYTE code tDDITHER_SEQ_TABLE[] =
{
#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#if(_D_DITHER_MULTI_SEQ_ENABLE == _DISABLE)
#include <RTDColorDefaultTable/DDither/DDitherGen0Seq1.h>
#else
#include <RTDColorDefaultTable/DDither/DDitherGen0Seq4.h>
#endif
#elif((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#if(((_D_DITHER_MULTI_SEQ_ENABLE == _DISABLE) &&\
     (_D_DITHER_SERIES_SEQ_ENABLE == _DISABLE)) &&\
     (_D_DITHER_ADVANCE_SETTING_ENABLE != _ENABLE))
#include <RTDColorDefaultTable/DDither/DDitherGen1Seq1.h>
#else
#include <RTDColorDefaultTable/DDither/DDitherGen1Seq4.h>
#endif
#endif
};

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
BYTE code tDDITHER_TEMPOFFSET_TABLE[] =
{
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL)
#include <RTDColorDefaultTable/DDither/DDitherGen0Tempo.h>
#elif((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
      (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#include <RTDColorDefaultTable/DDither/DDitherGen1Tempo.h>
#endif
};
#endif

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#if(_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE)
BYTE code tDDITHER_REALIGN_TABLE[] =
{
#include <RTDColorDefaultTable/DDither/DDitherGen1Realign.h>
};

BYTE code tDDITHER_REALIGN_TEMPO_TABLE[] =
{
#include <RTDColorDefaultTable/DDither/DDitherGen1RealignTempo.h>
};

#if(_PANEL_EXIST_MULTIPANEL == _OFF)

BYTE code tDDITHER_LSB_TABLE[] =
{
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
#include <RTDColorDefaultTable/DDither/DDitherGen1LSB30Bit.h>
#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2)
#include <RTDColorDefaultTable/DDither/DDitherGen1LSB24Bit.h>
#endif
#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)
#include <RTDColorDefaultTable/DDither/DDitherGen1LSB24Bit.h>
#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
#include <RTDColorDefaultTable/DDither/DDitherGen1LSB30Bit.h>
#endif
};

BYTE code tDDITHER_ADVANCE_SETTING_TABLE[] =
{
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
#include <RTDColorDefaultTable/DDither/DDitherGen1AdvanceS418Bit.h>
#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2)
#include <RTDColorDefaultTable/DDither/DDitherGen1AdvanceS218Bit.h>
#endif
#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)
#include <RTDColorDefaultTable/DDither/DDitherGen1Advance24Bit.h>
#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
#include <RTDColorDefaultTable/DDither/DDitherGen1Advance30Bit.h>
#endif
};

#else // Else of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
BYTE code tDDITHER_LSB_TABLE18Bit[] =
{
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
#include <RTDColorDefaultTable/DDither/DDitherGen1LSB30Bit.h>
#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2)
#include <RTDColorDefaultTable/DDither/DDitherGen1LSB24Bit.h>
#endif
};
#endif

BYTE code tDDITHER_LSB_TABLE24Bit[] =
{
#include <RTDColorDefaultTable/DDither/DDitherGen1LSB24Bit.h>
};

BYTE code tDDITHER_LSB_TABLE30Bit[] =
{
#include <RTDColorDefaultTable/DDither/DDitherGen1LSB30Bit.h>
};

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
BYTE code tDDITHER_ADVANCE_SETTING_TABLE18Bit[] =
{
#if(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
#include <RTDColorDefaultTable/DDither/DDitherGen1AdvanceS418Bit.h>
#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2)
#include <RTDColorDefaultTable/DDither/DDitherGen1AdvanceS218Bit.h>
#endif
};
#endif

BYTE code tDDITHER_ADVANCE_SETTING_TABLE24Bit[] =
{
#include <RTDColorDefaultTable/DDither/DDitherGen1Advance24Bit.h>
};

BYTE code tDDITHER_ADVANCE_SETTING_TABLE30Bit[] =
{
#include <RTDColorDefaultTable/DDither/DDitherGen1Advance30Bit.h>
};

#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

#endif
#endif
#endif

#endif // End of #ifdef __USER_COMMON_ADJUST__

#ifdef __USER_ADJUST_OUTPUT_GAMMA__

#if(_GAMMA_FUNCTION == _ON)
#if(_OGC_FUNCTION == _OFF)
//----------------------------------------------------------------------------------------------------
// Gamma Table
//----------------------------------------------------------------------------------------------------
BYTE code tLUTGAMMA_18_TABLE[] =
{
#include <RTDColorDefaultTable/Gamma/Gamma18.h>
};

BYTE code tLUTGAMMA_20_TABLE[] =
{
#include <RTDColorDefaultTable/Gamma/Gamma20.h>
};

BYTE code tLUTGAMMA_22_TABLE[] =
{
#include <RTDColorDefaultTable/Gamma/Gamma22.h>
};

BYTE code tLUTGAMMA_24_TABLE[] =
{
#include <RTDColorDefaultTable/Gamma/Gamma24.h>
};

BYTE * code tGAMMA_TABLE[] =
{
    tLUTGAMMA_18_TABLE,
    tLUTGAMMA_20_TABLE,
    tLUTGAMMA_22_TABLE,
    tLUTGAMMA_24_TABLE,
};
#endif
#endif // End of #if(_GAMMA_FUNCTION == _ON)

#if(_PCM_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// PCM Table
//----------------------------------------------------------------------------------------------------
BYTE code tPCM_USER_INPUT_GAMMA_TABLE[] =
{
#include <RTDColorDefaultTable/PCM/PCMUserInputGammaTable.h>
};

BYTE code tPCM_USER_MATRIX[] =
{
#include <RTDColorDefaultTable/PCM/PCMUserColorMatrixTable.h>
};

BYTE code tPCM_USER_OUTPUT_GAMMA_TABLE[] =
{
#include <RTDColorDefaultTable/PCM/PCMUserOutputGammaTable.h>
};

// Color Transfer Matrix TABLE For CCT adjust
#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
WORD code tPCM_COLORTRANSFER_MATRIX[] =
{
#include <RTDColorDefaultTable/PCM/PCMUserColorMatrixTransferMatrixTable.h>
};
#endif

BYTE * code tPCM_USER_TABLE[] =
{
    tPCM_USER_INPUT_GAMMA_TABLE,
    tPCM_USER_OUTPUT_GAMMA_TABLE,
    tPCM_USER_MATRIX,
};
#endif // End of #if(_PCM_FUNCTION == _ON)

#endif // End of #ifdef __USER_ADJUST_OUTPUT_GAMMA__



#ifdef __USER_ADJUST_3D_GAMMA__

#if(_RGB_3D_GAMMA_FUNCTION == _ON)
BYTE code tRGB3DGAMMA_MODE0_TABLE[] =
{
#include <RTDColorDefaultTable/Gamma/3DGammaTable.h>
};

BYTE * code tRGB3DGAMMA_TABLE[] =
{
    tRGB3DGAMMA_MODE0_TABLE,
};

#endif // End of #if(_RGB_3D_GAMMA == _ON)
#endif // End of #ifdef __USER_ADJUST_3D_GAMMA__

#ifdef __USER_ADJUST_LOWBLUE__
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
BYTE code tDynamicLowBluePara[] =
{
#include <RTDColorDefaultTable/DynamicLowBlue/DynamicLowBluePara.h>
};
BYTE code tDynamicLowBlueMatrixSize81[] =
{
#include <RTDColorDefaultTable/DynamicLowBlue/DynamicLowBlueBlurMatrixSize81.h>
};
BYTE code tDynamicLowBlueMatrixSize121[] =
{
#include <RTDColorDefaultTable/DynamicLowBlue/DynamicLowBlueBlurMatrixSize121.h>
};
#endif
#endif
#ifdef __USER_ADJUST_3D_GAMMA_GAMUTCMP__

#if((_RGB_3D_GAMMA_FUNCTION == _ON) && (_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON))
//----------------------------------------------------------------------------------------------------
// Color Gamut compression Table
//----------------------------------------------------------------------------------------------------
BYTE code tRGB3DGAMMA_HDR10_GAMUT_COMPRESSION_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_GamutCompression_3DGamma_Table.h>
};

BYTE * code tRGB3DGAMMA_GAMUTCMP_TABLE[] =
{
    tRGB3DGAMMA_HDR10_GAMUT_COMPRESSION_TABLE,
};

#endif // End of #if((_RGB_3D_GAMMA_FUNCTION == _ON) && (_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON))
#endif // End of #ifdef __USER_ADJUST_3D_GAMMA_GAMUTCMP__

#ifdef __USER_ADJUST_3D_GAMMA_HDR10RMP__

#if((_RGB_3D_GAMMA_FUNCTION == _ON) && (_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON))
//----------------------------------------------------------------------------------------------------
// Color 3D Gamma HDR Remap Table
//----------------------------------------------------------------------------------------------------
BYTE code tRGB3DGAMMA_HDR10_REMAP_TABLE_TYPE1[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_3DGamma_Remap_Table_Type1.h>
};

BYTE * code tRGB3DGAMMA_HDR10_REMAP_TABLE[] =
{
    tRGB3DGAMMA_HDR10_REMAP_TABLE_TYPE1,
};

#endif // End of #if((_RGB_3D_GAMMA_FUNCTION == _ON) && (_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON))
#endif // End of #ifdef __USER_ADJUST_3D_GAMMA_HDR10RMP__


#ifdef __USER_ADJUST_LOCAL_CONTRAST__
#if((_LOCAL_CONTRAST_FUNCTION == _ON) || (_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON) || (_IP_LOCAL_CONTRAST_ON == _ON) || (_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _ON))
//----------------------------------------------------------------------------------------------------
// LOCAL CONTRAST TABLE
//----------------------------------------------------------------------------------------------------
// LocalContrast Temporal Table
BYTE code tCOLOR_LOCALCONTRAST_TEMPORAL_24_TABLE[] =
{
// For Input DVD 24Hz
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTemporalTable_24Hz.h>
};

BYTE code tCOLOR_LOCALCONTRAST_TEMPORAL_60_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTemporalTable_60Hz.h>
};

BYTE code tCOLOR_LOCALCONTRAST_TEMPORAL_120_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTemporalTable_120Hz.h>
};

BYTE code tCOLOR_LOCALCONTRAST_TEMPORAL_144_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTemporalTable_144Hz.h>
};

BYTE code tCOLOR_LOCALCONTRAST_TEMPORAL_165_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTemporalTable_165Hz.h>
};

BYTE code tCOLOR_LOCALCONTRAST_TEMPORAL_240_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTemporalTable_240Hz.h>
};

BYTE * code tCOLOR_LOCALCONTRAST_TEMPORAL_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_TEMPORAL_24_TABLE,
    tCOLOR_LOCALCONTRAST_TEMPORAL_60_TABLE,
    tCOLOR_LOCALCONTRAST_TEMPORAL_120_TABLE,
    tCOLOR_LOCALCONTRAST_TEMPORAL_144_TABLE,
    tCOLOR_LOCALCONTRAST_TEMPORAL_165_TABLE,
    tCOLOR_LOCALCONTRAST_TEMPORAL_240_TABLE,
};
#endif // End of #if((_LOCAL_CONTRAST_FUNCTION == _ON) || (_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON) || (_IP_LOCAL_CONTRAST_ON == _ON))

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
BYTE code tCOLOR_LOCALCONTRAST_SETTING_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL.h>
};

BYTE code tCOLOR_LOCALCONTRAST_SETTING_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM.h>
};

BYTE code tCOLOR_LOCALCONTRAST_SETTING_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH.h>
};

BYTE * code tCOLOR_LOCALCONTRAST_SETTING_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_SETTING_L,
    tCOLOR_LOCALCONTRAST_SETTING_M,
    tCOLOR_LOCALCONTRAST_SETTING_H,
};

#if(_SDR_PLUS_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// SDR+ LOCAL CONTRAST TABLE
//----------------------------------------------------------------------------------------------------
BYTE code tCOLOR_LOCALCONTRAST_SDR_PLUS_TABLE_0[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrast_SDRPlus_Table.h>
};

BYTE * code tCOLOR_LOCALCONTRAST_SDR_PLUS_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_SDR_PLUS_TABLE_0,
};
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// Night Sniper LOCAL CONTRAST TABLE
//----------------------------------------------------------------------------------------------------
BYTE code tCOLOR_LOCALCONTRAST_NIGHT_SNIPER_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTable_NightSniper.h>
};
#endif

#if(_HDR10_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// HDR10 LOCAL CONTRAST TABLE
//----------------------------------------------------------------------------------------------------
BYTE code tCOLOR_LOCALCONTRAST_HDR10_540_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL_HDR10_540nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_540_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM_HDR10_540nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_540_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH_HDR10_540nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_1200_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL_HDR10_1200nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_1200_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM_HDR10_1200nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_1200_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH_HDR10_1200nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_4000_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL_HDR10_4000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_4000_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM_HDR10_4000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_4000_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH_HDR10_4000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_10000_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL_HDR10_10000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_10000_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM_HDR10_10000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_10000_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH_HDR10_10000nit.h>
};


BYTE * code tCOLOR_LOCALCONTRAST_HDR10_540_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_HDR10_540_L,
    tCOLOR_LOCALCONTRAST_HDR10_540_M,
    tCOLOR_LOCALCONTRAST_HDR10_540_H,
};

BYTE * code tCOLOR_LOCALCONTRAST_HDR10_1200_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_HDR10_1200_L,
    tCOLOR_LOCALCONTRAST_HDR10_1200_M,
    tCOLOR_LOCALCONTRAST_HDR10_1200_H,
};

BYTE * code tCOLOR_LOCALCONTRAST_HDR10_4000_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_HDR10_4000_L,
    tCOLOR_LOCALCONTRAST_HDR10_4000_M,
    tCOLOR_LOCALCONTRAST_HDR10_4000_H,
};

BYTE * code tCOLOR_LOCALCONTRAST_HDR10_10000_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_HDR10_10000_L,
    tCOLOR_LOCALCONTRAST_HDR10_10000_M,
    tCOLOR_LOCALCONTRAST_HDR10_10000_H,
};

#if(_LOCAL_DIMMING_FUNCTION == _ON)
BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_540_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL_HDR10_LD_540nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_540_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM_HDR10_LD_540nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_540_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH_HDR10_LD_540nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_1200_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL_HDR10_LD_1200nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_1200_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM_HDR10_LD_1200nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_1200_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH_HDR10_LD_1200nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_4000_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL_HDR10_LD_4000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_4000_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM_HDR10_LD_4000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_4000_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH_HDR10_LD_4000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_10000_L[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableL_HDR10_LD_10000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_10000_M[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableM_HDR10_LD_10000nit.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_LD_10000_H[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrastTableH_HDR10_LD_10000nit.h>
};


BYTE * code tCOLOR_LOCALCONTRAST_HDR10_LD_540_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_HDR10_LD_540_L,
    tCOLOR_LOCALCONTRAST_HDR10_LD_540_M,
    tCOLOR_LOCALCONTRAST_HDR10_LD_540_H,
};

BYTE * code tCOLOR_LOCALCONTRAST_HDR10_LD_1200_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_HDR10_LD_1200_L,
    tCOLOR_LOCALCONTRAST_HDR10_LD_1200_M,
    tCOLOR_LOCALCONTRAST_HDR10_LD_1200_H,
};

BYTE * code tCOLOR_LOCALCONTRAST_HDR10_LD_4000_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_HDR10_LD_4000_L,
    tCOLOR_LOCALCONTRAST_HDR10_LD_4000_M,
    tCOLOR_LOCALCONTRAST_HDR10_LD_4000_H,
};

BYTE * code tCOLOR_LOCALCONTRAST_HDR10_LD_10000_TABLE[] =
{
    tCOLOR_LOCALCONTRAST_HDR10_LD_10000_L,
    tCOLOR_LOCALCONTRAST_HDR10_LD_10000_M,
    tCOLOR_LOCALCONTRAST_HDR10_LD_10000_H,
};
#endif  // End of #if(_LOCAL_DIMMING_FUNCTION == _ON)
#endif  // End of #if(_HDR10_SUPPORT == _ON)
#endif  // End of #if(_LOCAL_CONTRAST_SUPPORT == _ON)
#endif // End of #ifdef __USER_ADJUST_LOCAL_CONTRAST__

#ifdef __USER_INTERFACE_COLOR__

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// LightEnhance TABLE
//----------------------------------------------------------------------------------------------------
BYTE code tDCC_LIGHTENHANCE_120_540_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type1_540nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_120_1200_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type1_1200nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_120_4000_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type1_4000nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_120_10000_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type1_10000nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_140_540_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type2_540nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_140_1200_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type2_1200nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_140_4000_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type2_4000nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_140_10000_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type2_10000nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_160_540_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type3_540nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_160_1200_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type3_1200nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_160_4000_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type3_4000nit_Table.h>
};

BYTE code tDCC_LIGHTENHANCE_160_10000_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_LightEnhance_Type3_10000nit_Table.h>
};
#endif

#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
BYTE code tICM_COLORENHANCE_LEVEL1_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_ColorEnhance_Level1_Table.h>
};

BYTE code tICM_COLORENHANCE_LEVEL2_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_ColorEnhance_Level2_Table.h>
};

BYTE code tICM_COLORENHANCE_LEVEL3_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_ColorEnhance_Level3_Table.h>
};

BYTE * code tICM_COLORENHANCE_TABLE[] =
{
    tICM_COLORENHANCE_LEVEL1_TABLE,
    tICM_COLORENHANCE_LEVEL2_TABLE,
    tICM_COLORENHANCE_LEVEL3_TABLE,
};
#endif

#if(_HDR10_SUPPORT == _ON)
#if(_DCC_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// HDR10 DCC Table
//----------------------------------------------------------------------------------------------------
BYTE code tDCC_HDR10_GAME[] =
{
#include <RTDColorDefaultTable/DCC/DccModeGame.h>
};

BYTE code tDCC_HDR10_MOVIE[] =
{
#include <RTDColorDefaultTable/DCC/DccModeMovie.h>
};

BYTE code tDCC_HDR10_PHOTO[] =
{
#include <RTDColorDefaultTable/DCC/DccModePhoto.h>
};

BYTE code tDCC_HDR10_VIVID[] =
{
#include <RTDColorDefaultTable/DCC/DccModeVivid.h>
};

BYTE * code tDCC_HDR10_TABLE[] =
{
    _NULL_POINTER,  // Standard
    tDCC_HDR10_GAME,
    tDCC_HDR10_MOVIE,
    tDCC_HDR10_PHOTO,
    tDCC_HDR10_VIVID,
};
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
#if(_ICM_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// ICM Table For LC
//----------------------------------------------------------------------------------------------------
BYTE code tICM_LC_HDR10_TABLE[] =
{
#include <RTDColorDefaultTable/LocalContrast/Game/LocalContrast_HDR_ColorEnhanceTable.h>
};
#endif // End of #if(_ICM_FUNCTION == _ON)
#endif // End of #if(_LOCAL_CONTRAST_FUNCTION == _ON)

#if(_ICM_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// HDR10 ICM Table
//----------------------------------------------------------------------------------------------------
BYTE code tICM_HDR10_GAME[] =
{
#include <RTDColorDefaultTable/ICM/IcmModeGame.h>
};

BYTE code tICM_HDR10_MOVIE[] =
{
#include <RTDColorDefaultTable/ICM/IcmModeMovie.h>
};

BYTE code tICM_HDR10_PHOTO[] =
{
#include <RTDColorDefaultTable/ICM/IcmModePhoto.h>
};

BYTE code tICM_HDR10_VIVID[] =
{
#include <RTDColorDefaultTable/ICM/IcmModeVivid.h>
};

BYTE * code tICM_HDR10_TABLE[] =
{
    _NULL_POINTER,  // Standard
    tICM_HDR10_GAME,
    tICM_HDR10_MOVIE,
    tICM_HDR10_PHOTO,
    tICM_HDR10_VIVID,
};
#endif

#if(_HLG_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// HLG YMapping Table
//----------------------------------------------------------------------------------------------------
BYTE code tYM_HLG_OOTF_USERMODE1[] =
{
#include <RTDColorDefaultTable/Ymapping/HLG_OOTF_UserMode1_Table.h>
};

BYTE code tYM_HLG_OOTF_USERMODE2[] =
{
#include <RTDColorDefaultTable/Ymapping/HLG_OOTF_UserMode2_Table.h>
};

BYTE code tYM_HLG_OOTF_USERMODE3[] =
{
#include <RTDColorDefaultTable/Ymapping/HLG_OOTF_UserMode3_Table.h>
};
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// HDR SBTM Table
//----------------------------------------------------------------------------------------------------
BYTE code tHDR10_SBTM_TABLE[] =
{
#include <RTDColorDefaultTable/HDR/HDR10_SBTM_EOTF_Table.h>
};
#endif
#endif

#endif

