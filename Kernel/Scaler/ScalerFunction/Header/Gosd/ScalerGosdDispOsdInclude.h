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
// ID Code      : ScalerGosdDispOsdInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// 2 buffer control
#define _GOSD_GDMA_BUFFER_CONTROL                       (2)

// Register mapping for osd1,osd2, osd3
#define GET_GOSD_GDMA_OSD_REG_OFFSET(x)                 (((x) == _GOSD_PLANE_OSD1) ? (0x0000) : (((x) == _GOSD_PLANE_OSD3) ? (0x0200) : (0x0100)))

#define GET_GOSD_DISPLAY_PLANE_BY_WDTEVENT(x)           (((x) == _SCALER_WD_TIMER_EVENT_GOSD_OSD1_CONTINUOUS_START) ? (_GOSD_PLANE_OSD1) :\
                                                        (((x) == _SCALER_WD_TIMER_EVENT_GOSD_OSD2_CONTINUOUS_START) ? (_GOSD_PLANE_OSD2) :\
                                                        (_GOSD_PLANE_OSD3)))

#define GET_GOSD_WDTEVENT_BY_DISPLAY_PLANE(x)           (((x) == _GOSD_PLANE_OSD1) ? (_SCALER_WD_TIMER_EVENT_GOSD_OSD1_CONTINUOUS_START) :\
                                                        (((x) == _GOSD_PLANE_OSD2) ? (_SCALER_WD_TIMER_EVENT_GOSD_OSD2_CONTINUOUS_START) :\
                                                        (_SCALER_WD_TIMER_EVENT_GOSD_OSD3_CONTINUOUS_START)))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD b31Addr           : 31;
    DWORD b1Last             : 1;
} StructGosdGdmaWinNextAddr;

typedef struct
{
    DWORD b5Type             : 5;
    DWORD b1Reserved2        : 1;
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    DWORD b1IMGcompress      : 1;
#else
    DWORD b1Reserved3        : 1;
#endif
    DWORD b1Compress         : 1;
    DWORD b1KeepPreCLUT      : 1;
    DWORD b1LittleEndian     : 1;
    DWORD b1ClutFmt          : 1;
    DWORD b5Reserved1        : 5;
    DWORD b8AlphaValue       : 8;
    DWORD b1ObjType          : 1;
    DWORD b1Reserved0        : 1;
    DWORD b1AlphaEn          : 1;
    DWORD b1AlphaType        : 1;
    DWORD b3RgbOrder         : 3;
    DWORD b1ExtendMode       : 1;
} StructGosdGdmaWinAttr;

typedef struct
{
    DWORD b24Key            : 24;
    DWORD b1KeyEn            : 1;
    DWORD b7Reserved         : 7;
} StructGosdGdmaWinKey;

typedef struct
{
    WORD usObjXoffset;
    WORD usObjYoffset;
} StructGosdGdmaWinInit;

typedef struct
{
    DWORD b5AfbcArgbOrder    : 5;
    DWORD b11Reserved1       : 11;
    DWORD b1AfbcYuvTrans     : 1;
    DWORD b7Reserved0        : 7;
    DWORD b1Afbc_fmt_1st     : 1;
    DWORD b7Reserved         : 7;
} StructGosdGdmaWinAFBCFormat;

typedef struct
{
    WORD usX_total_tile;
    WORD usY_total_tile;
} StructGosdGdmaWinAFBCTotalTile;

typedef struct
{
    WORD usX_pic_pixel;
    WORD usY_pic_pixel;
} StructGosdGdmaWinAFBCPicPixelXY;

typedef struct
{
    WORD usX_sta;
    WORD usY_sta;
} StructGosdGdmaWinAFBCStartXY;

typedef struct
{
    BYTE ucId; // _GDMA_MAX_NUM_OSD_WIN
    BYTE ucPrevId;
    BYTE ucNextId;
    // BYTE b1Drawn           : 1;
    BYTE b1Occupied        : 1;
    StructGosdSurfaceHandler stSurfaceHandler;
} StructGosdGdmaWinCtrl;

typedef struct
{
    StructGosdGdmaWinNextAddr stNxtAddr;
    // Window Region
    StructGosdGdmaWinXY stWinXY;
    StructGosdGdmaWinWH stWinWH;
    // Window Attribute
    StructGosdGdmaWinAttr stAttr;
    DWORD ulCLUT_addr;
    StructGosdGdmaWinKey stColorKey;
    DWORD ulTop_addr; // top or progressive OSD start address
    DWORD ulBot_addr; // bottom OSD start address (interlace mode)
    DWORD ulPitch;
    StructGosdGdmaWinInit stObjOffset;
    DWORD pulReserved[2];
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    StructGosdGdmaWinAFBCFormat stAfbc_format;
    StructGosdGdmaWinAFBCTotalTile stAfbc_totaltile;
    StructGosdGdmaWinAFBCPicPixelXY stAfbc_xy_pixel;
    StructGosdGdmaWinAFBCStartXY stAfbc_xy_sta;
#else
    DWORD pulReserved1[4];
#endif
} StructGosdGdmaWinInfo;

typedef struct
{
    DWORD ulFactor;
    DWORD ulIni;
    BYTE b1SrEn                : 1;
} StructGosdGdmaSRParam;

typedef struct
{
    StructGosdGdmaSRParam stHParam;
    StructGosdGdmaSRParam stVParam;
} StructGosdGdmaPlaneSRParam;

typedef struct
{
    BYTE b1OSDDisplayEn         : 1;
    StructGosdGdmaWinXY stDispXY;
    StructGosdGdmaWinWH stDispWH;
    StructGosdGdmaPlaneSRParam stDispSRParam;
} StructGosdGdmaDispInfo;

typedef struct
{
    EnumGosdDisplayOSD penumCLUTSel[_GOSD_GDMA_BUFFER_CONTROL];
    StructGosdGdmaDispInfo pstOSDDisp[_GOSD_GDMA_BUFFER_CONTROL];

    __attribute__((aligned(16)))
    StructGosdGdmaWinInfo pstOSDWin[_GOSD_GDMA_BUFFER_CONTROL];

    BYTE b1OSDWinBufIdx         : 1;
} StructGosdGdmaOsdCtrl;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructGosdDispOsdDisplayArgument g_pstGosdDispOsdContinuousArgument[_GOSD_CONTINUOUS_STEP_MAX];


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
extern BYTE ScalerGosdDispOsdGetBitPerPixel(EnumGosdGdmaColorType enumType);
extern void ScalerGosdDispOsdPowerOnInitial(void);
extern void ScalerGosdDispOsdSetMixerDBEnable(bit bEnable);
extern void ScalerGosdDispOsdSetMixerEnable(bit bEnable, EnumDBApply enumDBApply);
#endif

extern BYTE ScalerGosdDispOsdClkSelectPreProc(void);
extern void ScalerGosdDispOsdClkSelectPostProc(BYTE ucOsdStatus, bit bGosdClkSelect);
extern void ScalerGosdDispOsdClkSelect(void);
extern void ScalerGosdDispOsdFBSeperateEnable(bit bEn);

#endif // #if(_GOSD_SUPPORT == _ON)
