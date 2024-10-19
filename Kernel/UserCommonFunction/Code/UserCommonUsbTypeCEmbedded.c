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
// ID Code      : UserCommonUsbTypeCEmbedded.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLEREMBEDDED__

#include "UserCommonInclude.h"
#include "UsbTypeCEmbedded/UserCommonUsbTypeCEmbedded.h"

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON))

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get TypeC Vbus Protect Info
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCEmbeddedGetVbusProtectInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCVbusProtectInfo *pstTypeCVbusProtectInfo)
{
    StructTypeCVbusProtectInfo stTypeCVbusProtectInfo = {100, 0, 0, 0, 0};
    ucPdoIndex = ucPdoIndex;

    if(UserInterfaceUsbTypeCEmbeddedGetVbusProtectReference(enumTypeCPcbPort) == _TYPE_C_VBUS_PROTECT_BY_KERNEL)
    {
        // All PDO Use Same Default Setting
        stTypeCVbusProtectInfo.ucOcpCurRatio = _TYPE_C_PMIC_DEF_OCP_RATIO;

        stTypeCVbusProtectInfo.ucOvpDebounce = _TYPE_C_PMIC_DEF_OVP_DEBOUNCE;
        stTypeCVbusProtectInfo.ucUvpDebounce = _TYPE_C_PMIC_DEF_UVP_DEBOUNCE;
        stTypeCVbusProtectInfo.ucOcpDebounce = _TYPE_C_PMIC_DEF_OCP_DEBOUNCE;

        stTypeCVbusProtectInfo.enumPeakCurrentProtect = _TYPE_C_PEAK_CURRENT_PROTECT_ENABLE;
    }
    else
    {
        // Get User Setting By Different PDO
        UserInterfaceUsbTypeCEmbeddedGetVbusProtectInfo(enumTypeCPcbPort, ucPdoIndex, &stTypeCVbusProtectInfo);

        // OCP ration should not less than 100%
        stTypeCVbusProtectInfo.ucOcpCurRatio = ((stTypeCVbusProtectInfo.ucOcpCurRatio < 100) ? 100 : stTypeCVbusProtectInfo.ucOcpCurRatio);

        // Clip Portect Debounce to 0 ~ 5
        stTypeCVbusProtectInfo.ucOvpDebounce = ((stTypeCVbusProtectInfo.ucOvpDebounce > 5) ? 5 : stTypeCVbusProtectInfo.ucOvpDebounce);
        stTypeCVbusProtectInfo.ucUvpDebounce = ((stTypeCVbusProtectInfo.ucUvpDebounce > 5) ? 5 : stTypeCVbusProtectInfo.ucUvpDebounce);
        stTypeCVbusProtectInfo.ucOcpDebounce = ((stTypeCVbusProtectInfo.ucOcpDebounce > 5) ? 5 : stTypeCVbusProtectInfo.ucOcpDebounce);

        // stTypeCVbusProtectInfo.enumPeakCurrentProtect = stTypeCVbusProtectInfo.enumPeakCurrentProtect;
    }

    *pstTypeCVbusProtectInfo = stTypeCVbusProtectInfo;
}

//--------------------------------------------------
// Description  : Get TypeC Vbus Discharge Count
// Input Value  : enumTypeCPcbPort
// Output Value : return DischargeCount(5 ~ 40)
//--------------------------------------------------
BYTE UserCommonUsbTypeCEmbeddedGetVbusDischargeCount(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDischargeCount = UserInterfaceUsbTypeCEmbeddedGetVbusDischargeCount(enumTypeCPcbPort);

    // Clip Discharge Counter to 5 ~ 40
    ucDischargeCount = ((ucDischargeCount <= 5) ? 5 : ((ucDischargeCount >= 40) ? 40 : ucDischargeCount));

    return ucDischargeCount;
}
#endif // End of #if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON))
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

