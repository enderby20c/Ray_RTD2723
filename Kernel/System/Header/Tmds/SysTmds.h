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
// ID Code      : SysTmds.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_TMDS_H__
#define __SYS_TMDS_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
typedef struct
{
#if(_D0_HDMI_SUPPORT == _ON)
    BYTE b1D0Status : 1;
#endif
#if(_D1_HDMI_SUPPORT == _ON)
    BYTE b1D1Status : 1;
#endif
#if(_D2_HDMI_SUPPORT == _ON)
    BYTE b1D2Status : 1;
#endif
#if(_D3_HDMI_SUPPORT == _ON)
    BYTE b1D3Status : 1;
#endif
#if(_D4_HDMI_SUPPORT == _ON)
    BYTE b1D4Status : 1;
#endif
#if(_D5_HDMI_SUPPORT == _ON)
    BYTE b1D5Status : 1;
#endif
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    BYTE b1D12Status : 1;
#endif
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    BYTE b1D13Status : 1;
#endif
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    BYTE b1D14Status : 1;
#endif
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    BYTE b1D15Status : 1;
#endif
} StructTMDSCableStatus;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif // End of #ifndef __SYS_TMDS_H__
