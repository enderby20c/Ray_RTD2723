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
// ID Code      : UserCommonDscInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DSC from Which Port
//--------------------------------------------------
typedef enum
{
    _DSC_FROM_NO_PORT = 0x00,
#if(_DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT == _ON)
    _DSC_PORT_AUTO_SELECT,
#endif
    _DSC_FROM_D0_PORT,
    _DSC_FROM_D1_PORT,
    _DSC_FROM_D2_PORT,
    _DSC_FROM_D3_PORT,
    _DSC_FROM_D4_PORT,
    _DSC_FROM_D5_PORT,
}EnumDscSelectPort;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DSC_DECODER_SUPPORT == _ON)
extern void UserCommonDscSwitchPortCapability(BYTE ucPreviousPort, BYTE ucCurrentPort);
extern void UserCommonDscSwitchDisplayModeCapability(void);
extern WORD UserCommonDscMenuKeyGetInputPortType(BYTE ucDscMenuKey);
extern bit UserCommonDscGetEnable(EnumInputPort enumInputPort);
extern BYTE UserCommonDscGetVersion(EnumInputPort enumInputPort);
extern WORD UserCommonDscGetSliceHeight(EnumInputPort enumInputPort);
extern WORD UserCommonDscGetSliceWidth(EnumInputPort enumInputPort);
extern WORD UserCommonDscGetChunkSize(EnumInputPort enumInputPort);
extern WORD UserCommonDscGetBpc(EnumInputPort enumInputPort);
extern WORD UserCommonDscGetBitPerPixel(EnumInputPort enumInputPort);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern WORD UserCommonDscGetHCActive(EnumInputPort enumInputPort);
extern WORD UserCommonDscGetHCBlank(EnumInputPort enumInputPort);
#endif

#endif

