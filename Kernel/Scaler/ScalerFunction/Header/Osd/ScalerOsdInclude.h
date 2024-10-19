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
// ID Code      : ScalerOsdInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _OSD_OFFSET_DRAW_WINDOW_H                               0
#define _OSD_OFFSET_DRAW_WINDOW_V                               0

#define _OSD_ROTATE_NO_SWAP                                     0x00

#define _OSD_ROTATE_CCW                                         (_BIT1 | _BIT0)
#define _OSD_ROTATE_CW                                          (_BIT0)
#define _OSD_ROTATE_CW180                                       (_BIT1)

#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
#define _OSD_NEW_DB_DDEN_END_DELAY                              4
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
//--------------------------------------------------
// Struct for OSD Timing gen. DB
//--------------------------------------------------
typedef struct
{
    WORD usOsdVsSta;
    WORD usOsdBvLast;
    WORD usOsdBvSta;
    WORD usDdmVsta;
    BYTE b1RefDmTg : 1;
} StructOsdTimingGenDB;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
extern WORD g_usOsdTgDBCurDdmVSta;
extern WORD g_usOsdTgDBCurDdmVEnd;
extern bit g_bOsdTgDBApply;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerOsdReset(void);
extern void ScalerOsdSetTimingGen(WORD usDVStart, WORD usDVHeight, WORD usDHStart, bit bForceOsdDisable);


//--------------------------------------------------
// Command
//--------------------------------------------------
extern void ScalerOsdSetAddrSramFont(WORD usValue);
extern void ScalerOsdSetAddrSramCommand(WORD usValue);
extern void ScalerOsdSetAddrWindow(WORD usValue);

//--------------------------------------------------
// Windows
//--------------------------------------------------

//--------------------------------------------------
// SRAM
//--------------------------------------------------

//--------------------------------------------------
// Function
//--------------------------------------------------
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerOsdSetExtension(BYTE ucExtension);
#endif

#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
extern void ScalerOsdSetOsdTimingGenDBEnable(bit bEnable);
extern bit ScalerOsdGetOsdTimingGenDBEnable(void);
extern bit ScalerOsdCalOsdTimingGenGlobalDBParam(StructOsdTimingGenDB *pstCurOsdTgDbStatus, StructOsdTimingGenDB *pstNextOsdTgDbStatus);
extern void ScalerOsdTimingGenGlobalDBApply(EnumDBApply enumDBApply);
#endif

#if(_HW_FOSD_REFER_CAP_WIN_BACKGROUND_SUPPORT == _ON)
extern void ScalerOsdSetReferCapWinBackground(bit bEn);
#endif

