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
// ID Code      : UserCommonModeSearchInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Timing Info
//--------------------------------------------------
typedef enum
{
    _HPOLARITY = 0x00,
    _VPOLARITY,
    _INTERLACE,
    _IHFREQ,
    _IHTOTAL,
    _IHWIDTH,
    _IHSTART,
    _IVFREQ,
    _IVTOTAL,
    _IVHEIGHT,
    _IVSTART,
    _IVSYNC_WIDTH,
    _MISC,
} EnumTimingInfoSelect;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
extern WORD UserCommonModeSearchGetModetableTimingDataItem(BYTE ucModeNumber, EnumTimingInfoSelect enumTimingInfo);
extern bit UserCommonModeSearchCheckPresetModeTable(BYTE ucMatchmode);
#endif

