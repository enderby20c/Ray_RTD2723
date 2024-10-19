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
// ID Code      : ScalerCecInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _CEC_RX_INT_SUPPORT                      _ON

#if(_CEC_RX_INT_SUPPORT == _ON)
#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_NEW_MODE)
//--------------------------------------------------
// Macro of CEC IRQ Flag
//--------------------------------------------------
#define GET_HDMI_CEC_IRQ_FLAG()                  (ScalerGetBit_EXINT(P6F_1D_HDMIRX_CEC_ARC_IRQ, _BIT0) == _BIT0)
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerCecIrqEnable(bit bEnable, StructHdmiIrqStatus *pstTmdsMacIrqStatus);


#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)
