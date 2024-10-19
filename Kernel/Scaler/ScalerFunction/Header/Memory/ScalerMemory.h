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
// ID Code      : ScalerMemory.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_MEMORY_H__
#define __SCALER_MEMORY_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define SET_FIFO_WINDOW_R1_A1(usHWidth, usVHeight)      {\
                                                            ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_00_DISPLAY_READ_WID_BSU_H_R1_ACTIVE1, (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));\
                                                            ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_01_DISPLAY_READ_WID_BSU_L_R1_ACTIVE1, LOBYTE(usHWidth));\
                                                            ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_02_DISPLAY_READ_LEN_BSU_L_R1_ACTIVE1, LOBYTE(usVHeight));\
                                                            ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R1_ACTIVE1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), ((((usHWidth) & 0x3000) >> 8) | (((usVHeight) & 0x3000) >> 12)));\
                                                        }

#define SET_FIFO_WINDOW_R1_A2(usHWidth, usVHeight)      {\
                                                            ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_04_DISPLAY_READ_WID_BSU_H_R1_ACTIVE2, (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));\
                                                            ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_05_DISPLAY_READ_WID_BSU_L_R1_ACTIVE2, LOBYTE(usHWidth));\
                                                            ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_06_DISPLAY_READ_LEN_BSU_L_R1_ACTIVE2, LOBYTE(usVHeight));\
                                                            ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT_R1, _P0_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R1_ACTIVE2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), ((((usHWidth) & 0x3000) >> 8) | (((usVHeight) & 0x3000) >> 12)));\
                                                        }

#define SET_FIFO_WINDOW_R2_A1(usHWidth, usVHeight)      {\
                                                            ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_00_DISPLAY_READ_WID_BSU_H_R2_ACTIVE1, (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));\
                                                            ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_01_DISPLAY_READ_WID_BSU_L_R2_ACTIVE1, LOBYTE(usHWidth));\
                                                            ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_02_DISPLAY_READ_LEN_BSU_L_R2_ACTIVE1, LOBYTE(usVHeight));\
                                                            ScalerSetDataPortBit(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R2_ACTIVE1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), ((((usHWidth) & 0x3000) >> 8) | (((usVHeight) & 0x3000) >> 12)));\
                                                        }

#define SET_FIFO_WINDOW_R2_A2(usHWidth, usVHeight)      {\
                                                            ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_04_DISPLAY_READ_WID_BSU_H_R2_ACTIVE2, (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));\
                                                            ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_05_DISPLAY_READ_WID_BSU_L_R2_ACTIVE2, LOBYTE(usHWidth));\
                                                            ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_06_DISPLAY_READ_LEN_BSU_L_R2_ACTIVE2, LOBYTE(usVHeight));\
                                                            ScalerSetDataPortBit(P80_30_FIFO_WINDOW_ADDR_PORT_R2, _P80_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R2_ACTIVE2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), ((((usHWidth) & 0x3000) >> 8) | (((usVHeight) & 0x3000) >> 12)));\
                                                        }

#define SET_FIFO_WINDOW_R3_A1(usHWidth, usVHeight)      {\
                                                            ScalerSetDataPortByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_00_DISPLAY_READ_WID_BSU_H_R3_ACTIVE1, (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));\
                                                            ScalerSetDataPortByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_01_DISPLAY_READ_WID_BSU_L_R3_ACTIVE1, LOBYTE(usHWidth));\
                                                            ScalerSetDataPortByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_02_DISPLAY_READ_LEN_BSU_L_R3_ACTIVE1, LOBYTE(usVHeight));\
                                                            ScalerSetDataPortBit(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H_R3_ACTIVE1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), ((((usHWidth) & 0x3000) >> 8) | (((usVHeight) & 0x3000) >> 12)));\
                                                        }

#define SET_FIFO_WINDOW_R3_A2(usHWidth, usVHeight)      {\
                                                            ScalerSetDataPortByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_04_DISPLAY_READ_WID_BSU_H_R3_ACTIVE2, (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));\
                                                            ScalerSetDataPortByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_05_DISPLAY_READ_WID_BSU_L_R3_ACTIVE2, LOBYTE(usHWidth));\
                                                            ScalerSetDataPortByte(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_06_DISPLAY_READ_LEN_BSU_L_R3_ACTIVE2, LOBYTE(usVHeight));\
                                                            ScalerSetDataPortBit(PC0_30_FIFO_WINDOW_ADDR_PORT_R3, _PC0_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_R3_ACTIVE2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), ((((usHWidth) & 0x3000) >> 8) | (((usVHeight) & 0x3000) >> 12)));\
                                                        }

#if(_DT_RANGE_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Macros of Dt Upper Scan Flag
//--------------------------------------------------
#define GET_DT_UPPER_SCAN_FLAG()                        (g_bMemoryDtUpScan)
#define SET_DT_UPPER_SCAN_FLAG()                        (g_bMemoryDtUpScan = _TRUE)
#define CLR_DT_UPPER_SCAN_FLAG()                        (g_bMemoryDtUpScan = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

#if(_COLOR_IP_3DDI == _ON)
#define SET_3DDI_START_ADDRESS(x)                       (g_stMemoryClientAddress.ul3DDIStartAddress = (x))
#define SET_3DDI_END_ADDRESS(x)                         (g_stMemoryClientAddress.ul3DDIEndAddress = (x))
#endif
#if(_FRC_SUPPORT == _ON)
#define SET_FRC_START_ADDRESS(x)                        (g_stMemoryClientAddress.ulFRCStartAddress = (x))
#define SET_FRC_END_ADDRESS(x)                          (g_stMemoryClientAddress.ulFRCEndAddress = (x))
#endif
#if(_OD_FUNCTION == _ON)
#define SET_OD_START_ADDRESS(x)                         (g_stMemoryClientAddress.ulODStartAddress = (x))
#define SET_OD_END_ADDRESS(x)                           (g_stMemoryClientAddress.ulODEndAddress = (x))
#endif
#if(_GOSD_SUPPORT == _ON)
#define SET_GOSD_START_ADDRESS(x)                       (g_stMemoryClientAddress.ulGOSDStartAddress = (x))
#define SET_GOSD_END_ADDRESS(x)                         (g_stMemoryClientAddress.ulGOSDEndAddress = (x))
#endif

#if(_DT_RANGE_TEST_SUPPORT == _ON)
typedef struct
{
    DWORD ulDVstart;
    DWORD ulIVStoDVSPixels;
} StructDtCalInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern DWORD ScalerMemoryGetDtMaxMin(WORD usVheight);
extern WORD ScalerMemoryGetScalingDownDtFineTune(WORD usDt);
extern WORD ScalerMemoryGetScalingUpDtFineTune(WORD usDt);
extern WORD ScalerMemoryGetScaleUpDt(WORD usVheight);
extern void ScalerMemorySetFifoWindow(EnumDisplayRegion enumDisplayRegion, WORD usHWidth, WORD usVHeight);
extern void ScalerMemorySetCapInputFormat(EnumFRCPageSelect enumPageSelect);
extern void ScalerMemorySetDispInputFormat(EnumFRCPageSelect enumPageSelect);
extern bit ScalerMemoryGetMdomainIVSReset(EnumInputDataPath enumInputDataPath);
extern DWORD ScalerMemoryTransDDomainToIDomainPixel(DWORD ulDDomainPixel);
extern DWORD ScalerMemoryTransIDomainToDDomainPixel(DWORD ulIDomainPixel);

#if(_DT_RANGE_TEST_SUPPORT == _ON)
extern void ScalerMemoryDtRangeInitial(void);
extern void ScalerMemoryDtRangeScan(WORD usVheight);
extern void ScalerMemoryDtRangePrintFWDt(WORD usVheight);
extern WORD ScalerMemoryDtRangeRealDt(void);
#if(_HW_FORMAT_CONVERSION_EO_MODE == _OFF)
extern void ScalerMemoryDtUpperScanForSinglePath(DWORD ulLineData, DWORD ulIVstart, StructDtCalInfo *pstDtCalInfo);
#endif
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
extern DWORD ScalerMemoryGetFRCODBoundary(void);
#endif

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
extern bit ScalerMemoryGetFramesyncFixLastlinesStatus(void);
#endif
#endif // End of #ifndef __SCALER_MEMORY_H__
