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
// ID Code      : ScalerDisplayInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _MEMORY_REF_SOURCE_BIT,
#if(_BW_CUSTOME_MODE == _ENABLE)
    _MEMORY_FORCE_8_BIT,
    _MEMORY_FORCE_10_BIT,
#endif
} EnumMemoryDataBitSelect;

typedef enum
{
    _BW_DEFAULT_TYPE,
#if(_BW_CUSTOME_MODE == _ENABLE)
    _BW_FIX_ORIGINAL_COLOR_DEPTH_TYPE,
    _BW_DECIDE_OD_OFF_FIRST_TYPE,
#endif
} EnumBWCustomeModeType;

typedef struct
{
    EnumMemoryDataBitSelect enumMemoryBitSelect;
    EnumBWCustomeModeType enumBWCustomeModeType;
} StructCustomizedMdomain;

#if(_FRC_SUPPORT == _ON)
typedef enum
{
    _FORCE_FRAME_BUFFER_MODE,
    _MEMORY_CONFIG_AUTO_MODE,
} EnumDecideMemoryConfig;

typedef struct
{
    BYTE b1FORCETOFREERUN : 1;
    EnumDecideMemoryConfig b1DecideMemoryConfig : 1;
    WORD usMaxFreq;
    WORD usTypFreq;
    WORD usMinFreq;
    DWORD ulPanelClockTypical;
    DWORD ulPanelClockMaxSpread;
    DWORD ulPanelClockMinSpread;
} StructDVCustomizedFreq;
#endif

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
typedef enum
{
    _DEFAULT_FREERUN_DDOMAIN_SETTING,
    _KEEP_FREERUN_DDOMAIN_SETTING,
} EnumFreeRunDdomainSetting;
#endif

typedef struct
{
    StructCustomizedMdomain structCustomizedMdomain;

#if(_FRC_SUPPORT == _ON)
    StructDVCustomizedFreq structDVCustomizedFreq;
#endif

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
    EnumFreeRunDdomainSetting enumFreeRunDdomainSetting;
#endif
} StructDisplayCustomizedData;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


