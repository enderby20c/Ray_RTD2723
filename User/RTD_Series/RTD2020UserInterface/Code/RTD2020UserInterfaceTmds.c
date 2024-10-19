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
// ID Code      : RTD2020UserInterfaceTmds.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_TMDS__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceTmds.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Force HPD Toggle when Power Saving Wakeup
// Input Value  : None
// Output Value : _USER_FORCE_PS_TMDS_HPD_TOGGLE->User Want to Toggle HPD When Wakeup
//--------------------------------------------------
EnumUserForcePSTmdsHpdToggle UserInterfaceTmdsForcePSWakeupHpdToggle(void)
{
    return _USER_FORCE_PS_TMDS_HPD_NOT_TOGGLE;
}

#if(((_HDMI20_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON)) && (_HDMI_5V_DETECT_BY_USER == _ON))
//--------------------------------------------------
// Description  : HDMI 5V Detect by user
// Input Value  : enumInputPort
// Output Value : EnumUserHdmi5vStatus
//--------------------------------------------------
EnumUserHdmi5vStatus UserInterfaceTmds5vPinDetect(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;
    return _HDMI_5V_STATUS_LOW;
}
#endif

#if(_DELL_HDMI_HPD_DDC_STYLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : hdcp/scdc disable when ac on by user
// Input Value  : Node
// Output Value : EnumUserHdmi5vStatus
//--------------------------------------------------
EnumUserDdcStatus UserInterfaceTmdsSetHdcpScdcStatusWhenAcOn(void)
{
    return _DISABLE_WHEN_AC_ON;
}
#endif
#endif
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

