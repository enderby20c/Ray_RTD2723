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
// ID Code      : Scaler3DDIInclude.h
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_COLOR_IP_3DDI == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _3DDI_MAX_HWIDTH                            1920
#define _3DDI_MAX_VHEIGHT                           540
#define _3DDI_MAX_VTOTAL                            573
#define _3DDI_MAX_FRAME_RATE                        60
#define _3DDI_DATA_BIT_NUM                          20
#define _3DDI_INFO_BIT_NUM                          8
#define _3DDI_5A_MAX_HWIDTH                         768
#define _3DDI_MEM_ROW_MARGIN                        5
#define _3DDI_MEM_LENGTH                            32
#define _3DDI_PCLK_LIMIT                            76000 // KHz

#define SET_3DDI_MEMORY_SIZE(x, y)                  (g_pst3DDIstatus[Scaler3DDIGetIndex(x)].ul3DDIMemSize = (y))
#define GET_3DDI_MEMORY_SIZE(x)                     (g_pst3DDIstatus[Scaler3DDIGetIndex(x)].ul3DDIMemSize)
#define SET_3DDI_MEMORY_BW(x, y)                    (g_pst3DDIstatus[Scaler3DDIGetIndex(x)].ul3DDIMemBW = (y))
#define GET_3DDI_MEMORY_BW(x)                       (g_pst3DDIstatus[Scaler3DDIGetIndex(x)].ul3DDIMemBW)
#define SET_3DDI_STATUS(x, y)                       (g_pst3DDIstatus[Scaler3DDIGetIndex(x)].b13DDIEn = (y))
#define GET_3DDI_STATUS(x)                          (g_pst3DDIstatus[Scaler3DDIGetIndex(x)].b13DDIEn)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ul3DDIMemSize;
    DWORD ul3DDIMemBW;
    BYTE b13DDIEn : 1;
}Struct3DDIStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern Struct3DDIStatus g_pst3DDIstatus[2];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern DWORD Scaler3DDICalMaxMemorySize(void);
extern DWORD Scaler3DDICalMaxMemoryBW(void);
extern BYTE Scaler3DDIGetIndex(EnumInputDataPath enum3DDIInputPath);
extern BYTE Scaler3DDIGetPath(EnumInputDataPath enum3DDIInputPath);
extern void Scaler3DDISetDB(DWORD ulPageOffset, bit bEnable);
extern void Scaler3DDISetEnable(DWORD ulPageOffset, bit bEnable);
extern void Scaler3DDISettingProc(EnumInputDataPath enum3DDIInputPath);
extern void Scaler3DDIReset(EnumInputDataPath enum3DDIInputPath);
extern void Scaler3DDIDuplicate(EnumInputDataPath enumInputSrc, EnumInputDataPath enumInputDest);
extern DWORD Scaler3DDIGetRegisterPageOfffset(EnumInputDataPath enum3DDIInputPath);
extern void Scaler3DDISetCtrl(DWORD ulPageOffset);
extern void Scaler3DDISetIf3Aor5A(DWORD ulPageOffset);
extern void Scaler3DDISetIntra(DWORD ulPageOffset, DWORD pulIntraTable[6]);
extern void Scaler3DDISetMaTable(DWORD ulPageOffset, DWORD pulMaTab[6]);
extern void Scaler3DDISetMaCtrl(DWORD ulPageOffset);
extern void Scaler3DDISetMaHFD(DWORD ulPageOffset, bit bEnable);
extern void Scaler3DDISetMaBTR(DWORD ulPageOffset, bit bEnable);
extern void Scaler3DDISetFilmTable(DWORD ulPageOffset, DWORD pulFilmTab[6]);
extern void Scaler3DDISetFilm(DWORD ulPageOffset);
extern void Scaler3DDISetMemory(DWORD ulPageOffset, EnumInputDataPath enum3DDIInputPath);

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
extern bit Scaler3DDIModifyTiming(EnumInputDataPath enum3DDIInputPath);
#endif

#endif
