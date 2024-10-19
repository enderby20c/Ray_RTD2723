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
// ID Code      : RTD2020UserAdjustOutputGamma.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_OUTPUT_GAMMA__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)
#if(_GAMMA_FUNCTION == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_OGC_FUNCTION == _OFF)
//--------------------------------------------------
// Description  : Get Gamma Table Address
// Input Value  : Gamma Index
// Output Value : Gamma table address
//--------------------------------------------------
BYTE *UserAdjustGetGammaTableAddress(BYTE ucGamma)
{
    return tGAMMA_TABLE[ucGamma];
}

//--------------------------------------------------
// Description  : Get Gamma Table Bank
// Input Value  : None
// Output Value : Gamma table bank
//--------------------------------------------------
BYTE UserAdjustGetGammaTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}
#endif

//--------------------------------------------------
// Description  : Adjust Gamma
// Input Value  : Gamma type
// Output Value : None
//--------------------------------------------------
void UserAdjustGamma(EnumSelRegion enumSelRegion)
{
    UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, _COLOR_FUNCTION_CTS_BRI | _COLOR_FUNCTION_GAMMA);

    UserCommonColorGammaAdjust(enumSelRegion, _DB_APPLY_NONE);

#if(_CONTRAST_FUNCTION == _ON)
    RTDNVRamLoadColorSetting(UserAdjustGetOSDSelectRegion(enumSelRegion));
    UserCommonColorContrastAdjust(enumSelRegion);
#endif

    UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, _COLOR_FUNCTION_CTS_BRI | _COLOR_FUNCTION_GAMMA);
}

#if(_OGC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Mapping User OGC struct to Scaler OGC struct
// Input Value  : EnumGammaType
// Output Value : EnumOGCType
//--------------------------------------------------
EnumOGCType UserAdjustOGCOSDMapping(EnumGammaType enumGammaType)
{
    EnumOGCType enumOGCType = _OGC_OFF;

    switch(enumGammaType)
    {
        case _GAMMA_OFF:
            enumOGCType = _OGC_OFF;
            break;

        case _GAMMA_18:
            enumOGCType = _OGC_MODE1;
            break;

        case _GAMMA_20:
            enumOGCType = _OGC_MODE2;
            break;

        case _GAMMA_22:
            enumOGCType = _OGC_MODE3;
            break;

        case _GAMMA_24:
        default:
            enumOGCType = _OGC_MODE4;
            break;
    }

    return enumOGCType;
}
#endif

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get PCM USer Mode Table Address
// Input Value  : PCM User Mode Table Index
// Output Value : PCM User Modee table address
//--------------------------------------------------
BYTE *UserAdjustGetPCMUserModeTableAddress(BYTE ucPCM)
{
    return tPCM_USER_TABLE[ucPCM];
}

//--------------------------------------------------
// Description  : Get PCM User Mode Table Bank
// Input Value  : None
// Output Value : PCM User Mode table bank
//--------------------------------------------------
BYTE UserAdjustGetPCMUserModeTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

//--------------------------------------------------
// Description  : Adjust PCM
// Input Value  : ucPCM
// Output Value : None
//--------------------------------------------------
void UserAdjustPCM(EnumSelRegion enumSelRegion)
{
#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(enumSelRegion) != _PCM_OSD_NATIVE)
    {
        UserCommonColorDColorConvertAdjust(enumSelRegion, _DB_APPLY_NONE);
    }
#endif

    UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, _COLOR_FUNCTION_3DGAMMA | _COLOR_FUNCTION_CTS_BRI | _COLOR_FUNCTION_PCM);

    UserCommonColorPCMAdjust(enumSelRegion, _DB_APPLY_NONE);

#if(_CONTRAST_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(UserAdjustGetOSDSelectRegion(enumSelRegion)) == _PCM_OSD_NATIVE)
    {
        RTDNVRamLoadColorSetting(UserAdjustGetOSDSelectRegion(enumSelRegion));
    }
    UserCommonColorContrastAdjust(enumSelRegion);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
    UserCommonColorBrightnessAdjust(enumSelRegion);
#endif

#if((_RGB_3D_GAMMA_FUNCTION == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON))
    UserCommonColor3DGammaAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    UserCommonColorLowBlueAdjust(enumSelRegion);
#endif
    UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, _COLOR_FUNCTION_3DGAMMA | _COLOR_FUNCTION_CTS_BRI | _COLOR_FUNCTION_PCM);
}

#if(_OCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Mapping User PCM struct to Scaler PCM struct
// Input Value  : EnumPCMTypeIndex
// Output Value : EnumPCMType
//--------------------------------------------------
EnumPCMType UserAdjustPCMOSDMapping(EnumPCMTypeIndex enumPCMTypeIndex)
{
    EnumPCMType enumPCMType = _PCM_OFF;

    switch(enumPCMTypeIndex)
    {
        case _PCM_OSD_NATIVE:
            enumPCMType = _PCM_OFF;
            break;

        case _PCM_OSD_SRGB:
            enumPCMType = _PCM_SRGB;
            break;

        case _PCM_OSD_ADOBE_RGB:
            enumPCMType = _PCM_ADOBE_RGB;
            break;

#if(_RGB_3D_GAMMA_FUNCTION == _ON)
        case _PCM_OSD_SOFT_PROFT_M1:
        case _PCM_OSD_SOFT_PROFT_M2:
            enumPCMType = _PCM_SOFT_PROFT;
            break;
#endif

        case _PCM_OSD_USER:
        default:
            enumPCMType = _PCM_USER_MODE;
            break;
    }

    return enumPCMType;
}
#endif

#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Color Transfer Matrix TABLE For CCT adjust
// Input Value  : User Mode Table Index
// Output Value : PCM User Modee table address
//--------------------------------------------------
void UserAdjustGetColorTransferUserModeTableAddress(EnumPCMType enumPCMType, EnumOSDColorTempDef enumOSDColorTempIndex, WORD *pusTable)
{
    BYTE ucI = 0;
    EnumColorimetryTransfer enumColorimetryTransfer = _COLORIMETRY_TRANSFER_DEFUALT_CCT;
    if(enumPCMType == _PCM_SRGB)
    {
        switch(enumOSDColorTempIndex)
        {
            case _CT_9300:
                enumColorimetryTransfer = _COLORIMETRY_TRANSFER_USER_DEFINE_6;
                break;
            case _CT_7500:
                enumColorimetryTransfer = _COLORIMETRY_TRANSFER_USER_DEFINE_4;
                break;
            case _CT_6500:
            default:
                enumColorimetryTransfer = _COLORIMETRY_TRANSFER_DEFUALT_CCT;
                break;
        }
    }
    else if(enumPCMType == _PCM_DCI_P3)
    {
        switch(enumOSDColorTempIndex)
        {
            case _CT_9300:
                enumColorimetryTransfer = _COLORIMETRY_TRANSFER_USER_DEFINE_12;
                break;
            case _CT_7500:
                enumColorimetryTransfer = _COLORIMETRY_TRANSFER_USER_DEFINE_10;
                break;
            case _CT_6500:
            default:
                enumColorimetryTransfer = _COLORIMETRY_TRANSFER_DEFUALT_CCT;
                break;
        }
    }
    for(ucI = 0; ucI < _COLORIMETRY_TRANSFER_MATRIX_SIZE; ucI++)
    {
        pusTable[ucI] = *(tPCM_COLORTRANSFER_MATRIX + (enumColorimetryTransfer * _COLORIMETRY_TRANSFER_MATRIX_SIZE) + ucI);
    }
}
#endif

#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mapping User OGC struct to Scaler PCM Gamma struct
// Input Value  : EnumGammaType
// Output Value : EnumPCMGammaType
//--------------------------------------------------
EnumOCCPCMGammaType UserAdjustOCCPCMGammaOSDMapping(EnumGammaType enumGammaType)
{
    EnumOCCPCMGammaType enumOCCPCMGammaType = _OCC_PCM_GAMMA_OFF;

    switch(enumGammaType)
    {
        case _GAMMA_OFF:
            enumOCCPCMGammaType = _OCC_PCM_GAMMA_OFF;
            break;

        case _GAMMA_18:
            enumOCCPCMGammaType = _OCC_PCM_GAMMA_18;
            break;

        case _GAMMA_20:
            enumOCCPCMGammaType = _OCC_PCM_GAMMA_20;
            break;

        case _GAMMA_22:
            enumOCCPCMGammaType = _OCC_PCM_GAMMA_22;
            break;

        case _GAMMA_24:
        default:
            enumOCCPCMGammaType = _OCC_PCM_GAMMA_24;
            break;
    }

    return enumOCCPCMGammaType;
}

//--------------------------------------------------
// Description  : Mapping User Temperature struct to Scaler PCM Gamma Temperature struct
// Input Value  : EnumGammaType
// Output Value : EnumPCMGammaType
//--------------------------------------------------
EnumOCCPCMGammaCTMatrix UserAdjustOCCPCMGammaCTOSDMapping(EnumOSDColorTempDef enumOSDColorTempDef)
{
    EnumOCCPCMGammaCTMatrix enumOCCPCMGammaCTMatrix = _OCC_PCM_GAMMA_CT_OFF;

    switch(enumOSDColorTempDef)
    {
        case _CT_9300:
            enumOCCPCMGammaCTMatrix = _OCC_PCM_GAMMA_CT_MODE1;
            break;

        case _CT_7500:
            enumOCCPCMGammaCTMatrix = _OCC_PCM_GAMMA_CT_MODE2;
            break;

        case _CT_6500:
            enumOCCPCMGammaCTMatrix = _OCC_PCM_GAMMA_CT_MODE3;
            break;

        case _CT_5800:
            enumOCCPCMGammaCTMatrix = _OCC_PCM_GAMMA_CT_MODE4;
            break;

        case _CT_SRGB:
            enumOCCPCMGammaCTMatrix = _OCC_PCM_GAMMA_CT_MODE5;
            break;

        case _CT_USER:
        default:
            enumOCCPCMGammaCTMatrix = _OCC_PCM_GAMMA_CT_MODE6;
            break;
    }

    return enumOCCPCMGammaCTMatrix;
}
#endif

#endif  // End of #if(_PCM_FUNCTION == _ON)

#endif // End of #if(_GAMMA_FUNCTION == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
