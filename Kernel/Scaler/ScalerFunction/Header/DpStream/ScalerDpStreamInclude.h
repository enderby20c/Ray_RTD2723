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
// ID Code      : ScalerDpStreamInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Channel Coding Conversion
//--------------------------------------------------
typedef enum
{
    _CODINT_TYPE_CONVERSION_NODEFINE = ((_CODING_TYPE_NONE << 4) | (_CODING_TYPE_NONE)),
    _CODING_TYPE_128B132B_TO_128B132B = ((_CODING_TYPE_128B132B << 4) | (_CODING_TYPE_128B132B)),
    _CODING_TYPE_128B132B_TO_8B10B = ((_CODING_TYPE_128B132B << 4) | (_CODING_TYPE_8B10B)),
    _CODING_TYPE_8B10B_TO_128B132B = ((_CODING_TYPE_8B10B << 4) | (_CODING_TYPE_128B132B)),
    _CODING_TYPE_8B10B_TO_8B10B = ((_CODING_TYPE_8B10B << 4) | (_CODING_TYPE_8B10B)),
}EnumDpLinkChannelCodingTypeConversion;


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern DWORD ScalerDpStreamGetRxVideoElement(EnumDpStreamType enumDpStreamType, EnumDpStreamElement enumElement);

#endif
