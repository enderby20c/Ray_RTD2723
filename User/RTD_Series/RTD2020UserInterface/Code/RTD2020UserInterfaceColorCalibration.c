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
// ID Code      : RTD2020UserInterfaceColorCalibration.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_COLORCALIBRATION__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceColorCalibration.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
//--------------------------------------------------
// Description  : User function Before Calibration Start
// Input Value  : EnumCaliType
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorCalibrationBeforeProc(EnumCaliType enumMode)
{
    if(enumMode == _UNIFORMITY_CAL)// for Uniformity
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else // OGC/OCC/DICOM
    {
    }
}

//--------------------------------------------------
// Description  : User function After Calibration Start
// Input Value  : EnumCaliType
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorCalibrationAfterProc(EnumCaliType enumMode)
{
    if(enumMode == _UNIFORMITY_CAL)// for Uniformity
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else // OGC/OCC/DICOM
    {
    }
}
//--------------------------------------------------
// Description  : User function Backlight Adjust for Calibration
// Input Value  : 0(Min Backlight) ~ 255(Max Backlight)
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorCalibrationAdjustBacklight(BYTE ucBacklight)
{
    UserAdjustBacklight(_BACKLIGHT_MIN + ((DWORD)(_BACKLIGHT_MAX - _BACKLIGHT_MIN) * ucBacklight) / 255);
}

#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function For LD Boost White Pattern
// Input Value  : _ON/_OFF
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorCalibrationLDBoostAdjust(bit bBoost)
{
    BYTE ucBoostGain = _LOCAL_DIMMING_BOOST_ADMING;

    if(bBoost == _ON) // turn on boost
    {
        ExternalDeviceInterfaceLedDriverBoostAdjust(ucBoostGain);
    }
    else // turn off boost
    {
        ExternalDeviceInterfaceLedDriverBoostAdjust(100);
    }
}
#endif // #if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)

#if((_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE) || (_OCC_RGB_3D_GAMMA_SUPPORT == _ON))
//--------------------------------------------------
// Description  : User function For Multi Backlight Setting
// Input Value  : ucColorBacklightFlag
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorCalibrationAdjustMultiBacklight(EnumColorBacklightType enumColorBacklightType)
{
    switch(enumColorBacklightType)
    {
        case _MULTI_BACKLIGHT_3_CAL:
        case _MULTI_BACKLIGHT_4_CAL:
        case _MULTI_BACKLIGHT_HDR10_PEAK_LV_CHECK:
        case _MULTI_BACKLIGHT_HDR10_REMAP_TYPE1:
        case _MULTI_BACKLIGHT_HDR10_REMAP_TYPE2:
        default:
            UserAdjustBacklight(_BACKLIGHT_MAX);
            break;
    }
}
#endif // #if(_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE || _OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#endif // #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function Before Calibration Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorCalibrationBeforeDimmingProc(void)
{
}

//--------------------------------------------------
// Description  : User function After Calibration Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorCalibrationAfterDimmingProc(void)
{
}

#endif // End of #if(_BACKLIGHT_DIMMING_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

