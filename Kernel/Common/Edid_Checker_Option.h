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
// ID Code      : Edid_Checker_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// HDMI EDID options
//--------------------------------------------------
#define _EDID_CHECK_HDMI_HDR10                      (_HDMI_HDR10_SUPPORT == _ON)

#define _EDID_CHECK_HDMI_FREESYNC                   (_HDMI_FREESYNC_SUPPORT == _ON)
#define _EDID_CHECK_HDMI_VRR                        (_HDMI21_VRR_SUPPORT == _ON)
#define _EDID_CHECK_HDMI_FREESYNC_II                (_HDMI_FREESYNC_II_SUPPORT == _ON)
#define _EDID_CHECK_HDMI_FREESYNC_MCCS              (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)

#if(_EDID_CHECK_HDMI_FREESYNC_MCCS == _ON)
#define _EDID_HDMI_FREESYNC_MCCS_VALUE              _HDMI_FREESYNC_MCCS_VCP
#else
#define _EDID_HDMI_FREESYNC_MCCS_VALUE              0x00
#endif

#define _EDID_CHECK_HDMI_420                        (_HDMI20_YCBCR420_SUPPORT == _ON)

//--------------------------------------------------
// DP EDID options
//--------------------------------------------------
#define _EDID_CHECK_DP_HDR10                        (_DP_HDR10_SUPPORT == _ON)
#define _EDID_CHECK_DP_FREESYNC                     (_DP_FREESYNC_SUPPORT == _ON)
#define _EDID_CHECK_DP_FREESYNC_II                  (_DP_FREESYNC_II_SUPPORT == _ON)
#define _EDID_CHECK_DP_TYPEC                        (_TYPE_C_PORT_CTRL_SUPPORT == _ON)

