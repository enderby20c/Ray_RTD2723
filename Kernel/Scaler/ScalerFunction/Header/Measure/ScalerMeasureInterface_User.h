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
// ID Code      : ScalerMeasureInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1HSP : 1;             // HSP
    BYTE b1VSP : 1;             // VSP
    BYTE b1Interlace : 1;       // Interlace
    BYTE b1DpInterlaceVBID : 1; // Interlace For Dp VBID
    BYTE b1VideoField : 1;      // Field for video compensation
    BYTE b1InputVheightOdd : 1; // Vheight is odd
    WORD usHFreq;               // Horizontal Freq. (unit: 0.1kHz)
    WORD usHFreqAdjusted;       // Horizontal Freq. adjusted (unit: 0.1kHz)
    WORD usHTotal;              // Horizontal Total length (unit: Pixel)
    WORD usHWidth;              // Horizontal Active Width (unit: Pixel)
    WORD usHStart;              // Horizontal Start (unit: Pixel)
    WORD usHSWidth;             // Horizontal Sync Pulse Count (unit: SyncProc Clock)

    EnumInputDataPath enumInputDataPath;        // Input data path (M1 ~ S3)
    WORD usVFreq;               // Vertical Freq. (unit: 0.1Hz)
    WORD usVFreqAdjusted;       // Vertical Freq. adjusted (unit: 0.1Hz)
    WORD usVTotal;              // Vertical Total length (unit: HSync)
    WORD usVTotalOdd;           // Vertical Total Odd length (unit: HSync)
    WORD usVHeight;             // Vertical Active Height (unit: HSync)
    WORD usVStart;              // Vertical Start (unit: HSync)
    WORD usVSWidth;             // Vertical Sync Width    (unit: HSync)
}StructTimingInfo;

typedef struct
{
    BYTE b1HSP : 1;
    BYTE b1VSP : 1;
    WORD usHSPeriod;
    WORD usHSWidth;
    WORD usVSPeriod;
    WORD usVSWidth;
    WORD usHTotal;
    WORD usHWidth;
    WORD usVHeight;
#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
    WORD usHStart;
#endif
#if(_HW_IDOMAIN_OFFLINE_VSTART_MEASURE_SUPPORT == _ON)
    WORD usVStart;
#endif
}StructMeasureSyncData;

typedef struct
{
    WORD usVActiveStart;
    WORD usVActiveEnd;
    WORD usHActiveStart;
    WORD usHActiveEnd;
    BYTE ucColorAverageValue;
}StructAutoActiveData;

typedef struct
{
    StructTimingInfo stTimingInfo;
    StructMeasureSyncData stMeasureSyncData;
    StructAutoActiveData stAutoActiveData;
    DWORD ulActiveRegionCount;
}StructRegionTimingInfo;

#if(_DYNAMIC_DATA_BOUNDARY_AUTO_MEASURE == _ON)
typedef struct
{
    WORD usImageHStart;
    WORD usImageHWidth;
    WORD usImageVStart;
    WORD usImageVHeight;
}StructImageRegion;
#endif
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


