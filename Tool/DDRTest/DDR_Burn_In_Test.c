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
// ID Code      : DDR_Burn_In_Test.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __DDR_BURN_IN_TEST__

#include "ScalerFunctionInclude.h"

#if(_DDR_BURN_IN_TEST == _ON)
#warning "NOTE: _DDR_BURN_IN_TEST is _ON!!!"
#endif


#if(_DDR_BURN_IN_TEST == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Code Tables of Color BYPASS
//--------------------------------------------------
BYTE code tCOLOR_BYPASS[] =
{
    // Disable Watch Dog Timer
    // 4, _NON_AUTOINC_32, 0xA4001104, 0x000000A5,
    // Double Buffer //
    4, _NON_AUTOINC, 0x9F, 0x31,
    4, _NON_AUTOINC, 0xA4, 0x00,
    4, _NON_AUTOINC, 0xB0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // 3DDI //
    // 4, _NON_AUTOINC_32, 0xB0074000, 0x0859F9F5,
    // 4, _NON_AUTOINC_32, 0xB3074000, 0x0859F9F5,

    // DM //
    // 4, _NON_AUTOINC_32, 0xB0030800, 0x0000000F, // set write to 4 path
    // 4, _NON_AUTOINC_32, 0xB0030400, 0x00000000, // disable all block
    // 4, _NON_AUTOINC_32, 0xB0030408, 0x0000000C, // set input 444 12bit(bypass data)

    // 422 to 444 //
    4, _NON_AUTOINC, 0x9F, 0x31,
    4, _NON_AUTOINC, 0x40, 0x00,
    4, _NON_AUTOINC, 0x41, 0x00,
    4, _NON_AUTOINC, 0x42, 0x00,
    4, _NON_AUTOINC, 0x43, 0x00,

    // I-domain Color Conv. //
    4, _NON_AUTOINC, 0x9F, 0x00,
    4, _NON_AUTOINC, 0x9C, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x40,
    4, _NON_AUTOINC, 0x9C, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0x9C, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xC0,
    4, _NON_AUTOINC, 0x9C, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x17,
    4, _NON_AUTOINC, 0x9C, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xDC,
    4, _NON_AUTOINC, 0x9C, 0x00,

    // IDLTI //
    4, _NON_AUTOINC, 0x9F, 0x11,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x51,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x91,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x5A,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x1A,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xDE,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // I-dithering //
    4, _NON_AUTOINC, 0x9F, 0x00,
    4, _NON_AUTOINC, 0x89, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x40,
    4, _NON_AUTOINC, 0x89, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0x89, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xC0,
    4, _NON_AUTOINC, 0x89, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x17,
    4, _NON_AUTOINC, 0x89, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xDC,
    4, _NON_AUTOINC, 0x89, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // LSR //
    4, _NON_AUTOINC, 0x9F, 0x11,
    4, _NON_AUTOINC, 0x11, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x11,
    4, _NON_AUTOINC, 0x61, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x51,
    4, _NON_AUTOINC, 0x11, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x51,
    4, _NON_AUTOINC, 0x61, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x91,
    4, _NON_AUTOINC, 0x11, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x91,
    4, _NON_AUTOINC, 0x61, 0x00,

    //--------------------D Domain------------------//
    // HLW //
    4, _NON_AUTOINC, 0x9F, 0x00,
    4, _NON_AUTOINC, 0x60, 0x0C,
    4, _NON_AUTOINC, 0x61, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // D-Domain SHP //
    4, _NON_AUTOINC, 0x9F, 0x12,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x13,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x52,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x53,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x5B,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x5C,
    4, _NON_AUTOINC, 0x00, 0x00,

    // LocalContrast //
    4, _NON_AUTOINC, 0x9F, 0x32,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xC3,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xDD,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // D-domain Color Conv. //
    4, _NON_AUTOINC, 0x9F, 0x14,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x54,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x94,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x5D,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xE9,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xEA,
    4, _NON_AUTOINC, 0xA1, 0x00,

    // DCC //
    4, _NON_AUTOINC, 0x9F, 0x07,
    4, _NON_AUTOINC, 0xC7, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // DCR //
    4, _NON_AUTOINC, 0x9F, 0x07,
    4, _NON_AUTOINC, 0xD8, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x87,
    4, _NON_AUTOINC, 0xD8, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // ICM //
    4, _NON_AUTOINC, 0x9F, 0x07,
    4, _NON_AUTOINC, 0xD0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x87,
    4, _NON_AUTOINC, 0xD0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // Contrast & Brightness //
    4, _NON_AUTOINC, 0x9F, 0x00,
    4, _NON_AUTOINC, 0x64, 0x27,
    4, _NON_AUTOINC, 0x65, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0x64, 0x27,
    4, _NON_AUTOINC, 0x65, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // IAPSGain //
    4, _NON_AUTOINC, 0x9F, 0x07,
    4, _NON_AUTOINC, 0xE0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x87,
    4, _NON_AUTOINC, 0xE0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // Input Gamma && 3D Gamma //
    4, _NON_AUTOINC, 0x9F, 0x09,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0xB0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x89,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,


    // Y Mapping //
    4, _NON_AUTOINC, 0x9F, 0x09,
    4, _NON_AUTOINC, 0xE0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x49,
    4, _NON_AUTOINC, 0xE0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x89,
    4, _NON_AUTOINC, 0xE0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x58,
    4, _NON_AUTOINC, 0xE0, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // sRGB //
    4, _NON_AUTOINC, 0x9F, 0x00,
    4, _NON_AUTOINC, 0x62, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0x62, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // Post Gamma //
    4, _NON_AUTOINC, 0x9F, 0x09,
    4, _NON_AUTOINC, 0xD9, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x49,
    4, _NON_AUTOINC, 0xD9, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x89,
    4, _NON_AUTOINC, 0xD9, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x58,
    4, _NON_AUTOINC, 0xD9, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // LDHisto //
    // 4, _NON_AUTOINC_32, 0xB0050C00, 0x00000000,
    // 4, _NON_AUTOINC_32, 0xB1050C00, 0x00000000,

    // LDPWMProc //
    // 4, _NON_AUTOINC_32, 0xB0051000, 0x00000000,

    // BLModel //
    // 4, _NON_AUTOINC_32, 0xB0055000, 0x00000000,

    // Panel Uniformity //
    4, _NON_AUTOINC, 0x9F, 0x34,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // Output Gamma //
    4, _NON_AUTOINC, 0x9F, 0x09,
    4, _NON_AUTOINC, 0xC1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x89,
    4, _NON_AUTOINC, 0xC1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // GOSD - DispOsd //
    // 4, _NON_AUTOINC_32, 0xB004F200, 0x00000000,
    // 4, _NON_AUTOINC_32, 0xB004F300, 0x00000000,
    // 4, _NON_AUTOINC_32, 0xB004F400, 0x00000000,
    // 4, _NON_AUTOINC_32, 0xB004FF04, 0x0000000E,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0xA0, 0x00,

    // OSD //
    4, _NON_AUTOINC, 0x9F, 0x3A,
    4, _NON_AUTOINC, 0x00, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0xA0, 0x00,

    // D-dithering //
    4, _NON_AUTOINC, 0x9F, 0x00,
    4, _NON_AUTOINC, 0x6A, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0x6A, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x00,

    // OD //
    4, _NON_AUTOINC, 0x9F, 0x03,
    4, _NON_AUTOINC, 0xA1, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x83,
    4, _NON_AUTOINC, 0xA1, 0x00,

    //---------ICRC_M1-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x00, 0x82,
    //---------ICRC_M2-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x08, 0x82,
    //---------ICRC_S1-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x10, 0x82,
    //---------ICRC_S2-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x18, 0x82,

    //---------MCRC_Cap-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x80, 0x80,
    4, _NON_AUTOINC, 0x88, 0x80,
    4, _NON_AUTOINC, 0xA0, 0x80,
    4, _NON_AUTOINC, 0xA8, 0x80,

    //---------MCRC_Disp_M1-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x40, 0x80,
    //---------MCRC_Disp_M2-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x48, 0x80,
    //---------MCRC_Disp_S1-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x50, 0x80,
    //---------MCRC_Disp_S2-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0x58, 0x80,

    //---------DCRC_M1-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0xC0, 0x82,
    //---------DCRC_M2-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0xC8, 0x82,
    //---------DCRC_M3-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0xD0, 0x82,
    //---------DCRC_M4-------------
    4, _NON_AUTOINC, 0x9F, 0x36,
    4, _NON_AUTOINC, 0xD8, 0x82,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
void ScalerDDRBurnInCRCTest(void);
void ScalerDDRCheckIMDDomainCRC(void);

//--------------------------------------------------
// Description  : ScalerSyncDDRCheckIMDDomainCRC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDRBurnInCRCTest(void)
{
    while(ScalerGetBit(0x000D, _BIT0) == 0x01)
    {
        ScalerDDRCheckIMDDomainCRC();
    }
}

//--------------------------------------------------
// Description  : ScalerSyncDDRCheckIMDDomainCRC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDRCheckIMDDomainCRC(void)
{
    BYTE ucCRCRegOffset = 0;
    BYTE ucResult = 0;
    BYTE ucCounter = 0;
    BYTE ucPatternNo = 0;
    BYTE ucPatternDebounce = 0;
    WORD usPatternCycleCounter = 0;
    bit  bPatternChangeFlag = 0;
    bit  bPatternNO1Flag = 0;
    BYTE pucIDomainM1CRCValue[6] = {0};
    BYTE pucMDomainM1CRCValue[6] = {0};
    BYTE pucDDomainM1CRCValue[6] = {0};
    BYTE pucIDomainM1CRCValue_Backup[6] = {0};
    BYTE pucIDomainM1CRCValue_NO1[6] = {0};

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    BYTE pucIDomainM2CRCValue[6] = {0};
    BYTE pucMDomainM2CRCValue[6] = {0};
    BYTE pucDDomainM2CRCValue[6] = {0};
    BYTE pucIDomainM2CRCValue_Backup[6] = {0};
    BYTE pucIDomainM2CRCValue_NO1[6] = {0};
#endif

    ScalerTimerDelayXms(500);

    DebugMessageMemoryPhaseCal("Check IMD CRC Start", 0x00);

    // Disable Global Double
    ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);

    // Disable Watch Dog
    ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _DISABLE);

    // Disabe I/D dither
#if(_COLOR_IP_I_DITHER == _ON)
    ScalerColorIDitherEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_D_DITHER == _ON)
    ScalerColorDDitherEnable(_FUNCTION_OFF);
#endif

    PCB_LED_ACTIVE();

    ScalerBurstWrite(tCOLOR_BYPASS, sizeof(tCOLOR_BYPASS), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // Enable M1, M2 I-domain CRC output
    ScalerSetByte(P36_00_I_CRC_CTRL_M1, 0x82);
    ScalerSetByte(P36_08_I_CRC_CTRL_M2, 0x82);
    ScalerSetByte(P36_80_M_CAP_CRC_CTRL_M1, 0x80);
    ScalerSetByte(P36_88_M_CAP_CRC_CTRL_M2, 0x80);

    // Enable M1, M2 M-domain CRC output
    ScalerSetByte(P36_40_M_DISP_CRC_CTRL_M1, 0x80);
    ScalerSetByte(P36_48_M_DISP_CRC_CTRL_M2, 0x80);

    // Enable M1, M2 D-domain CRC output
    ScalerSetByte(P36_C0_D_CRC_CTRL_M1, 0x80);
    ScalerSetByte(P36_C8_D_CRC_CTRL_M2, 0x80);

    while(ScalerGetBit(0x000D, _BIT0) == 0x01)
    {
        //===========================================
        // Get I-domain CRC
        //===========================================
        // Wait until DVS_START
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

        // Read I-domain CRC (First 6 Bytes of M1 and M2 CRC)
        for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucIDomainM1CRCValue); ucCRCRegOffset++)
        {
            pucIDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_81_M_MAIN1_CAP_CRC_1 + ucCRCRegOffset);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            pucIDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_89_M_MAIN2_CAP_CRC_1 + ucCRCRegOffset);
#endif
        }

        //===========================================
        // Get M-domain CRC
        //===========================================
        // Read M-domain CRC (First 6 Bytes of M1 and M2 CRC)
        for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucMDomainM1CRCValue); ucCRCRegOffset++)
        {
            pucMDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_41_M_MAIN1_DISP_CRC_1 + ucCRCRegOffset);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            pucMDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_49_M_MAIN2_DISP_CRC_1 + ucCRCRegOffset);
#endif
        }

        //===========================================
        // Get D-domain CRC
        //===========================================
        // Read D-domain CRC (First 6 Bytes of M1 and M2 CRC)
        for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucDDomainM1CRCValue); ucCRCRegOffset++)
        {
            pucDDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_C1_D_MAIN1_CRC_1 + ucCRCRegOffset);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            pucDDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_C2_D_MAIN1_CRC_2 + ucCRCRegOffset);
#endif
        }

        if(ucCounter > 10)
        {
            ucCounter = 11;

            //===========================================
            // Compare I/M/D-domain CRC with  M-domain CRC
            //===========================================
            // I/M/D M1 CRC
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            if((memcmp(pucIDomainM1CRCValue, pucMDomainM1CRCValue, sizeof(pucIDomainM1CRCValue)) != 0) ||
               (memcmp(pucDDomainM1CRCValue, pucMDomainM1CRCValue, sizeof(pucIDomainM1CRCValue)) != 0) ||
               (memcmp(pucIDomainM2CRCValue, pucMDomainM2CRCValue, sizeof(pucIDomainM2CRCValue)) != 0) ||
               (memcmp(pucDDomainM2CRCValue, pucMDomainM2CRCValue, sizeof(pucIDomainM2CRCValue)) != 0))

#else
            if((memcmp(pucIDomainM1CRCValue, pucMDomainM1CRCValue, sizeof(pucIDomainM1CRCValue)) != 0) ||
               (memcmp(pucDDomainM1CRCValue, pucMDomainM1CRCValue, sizeof(pucIDomainM1CRCValue)) != 0))
#endif
            {
                ucResult = _BIT0;

                SET_LED2(_LED_ON);

                // Debug message for Fail Pattern NO
                DebugMessageMemoryPhaseCal("===== CRC Compare Fail=====", 0x00);
                DebugMessageMemoryPhaseCal("FAIL PatternNo", ucPatternNo);

                // Debug message for IMD CRC failure.
                for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucIDomainM1CRCValue); ucCRCRegOffset++)
                {
                    DebugMessageMemoryPhaseCal("IDomainM1CRC", pucIDomainM1CRCValue[ucCRCRegOffset]);
                }

                for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucMDomainM1CRCValue); ucCRCRegOffset++)
                {
                    DebugMessageMemoryPhaseCal("MDomainM1CRC", pucMDomainM1CRCValue[ucCRCRegOffset]);
                }

                for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucDDomainM1CRCValue); ucCRCRegOffset++)
                {
                    DebugMessageMemoryPhaseCal("DDomainM1CRC", pucDDomainM1CRCValue[ucCRCRegOffset]);
                }

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
                for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucIDomainM2CRCValue); ucCRCRegOffset++)
                {
                    DebugMessageMemoryPhaseCal("IDomainM2CRC", pucIDomainM2CRCValue[ucCRCRegOffset]);
                }


                for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucMDomainM2CRCValue); ucCRCRegOffset++)
                {
                    DebugMessageMemoryPhaseCal("MDomainM2CRC", pucMDomainM2CRCValue[ucCRCRegOffset]);
                }

                for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucDDomainM2CRCValue); ucCRCRegOffset++)
                {
                    DebugMessageMemoryPhaseCal("DDomainM2CRC", pucDDomainM2CRCValue[ucCRCRegOffset]);
                }
#endif
            }
        }

        // bLED1 indicates IMD CRC check passing or not now. bLED1 ON is passing.
        if(ucResult == 0x00)
        {
            SET_LED1(_LED_ON);
        }
        else
        {
            SET_LED1(_LED_OFF);
        }

        // Check the Pattern Number(Add Number if IDomain CRC changed and the new CRC is stable over many check)
        if(ucResult == 0x00)
        {
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            if((memcmp(pucIDomainM1CRCValue, pucIDomainM1CRCValue_Backup, sizeof(pucIDomainM1CRCValue)) != 0) ||
               (memcmp(pucIDomainM2CRCValue, pucIDomainM2CRCValue_Backup, sizeof(pucIDomainM2CRCValue)) != 0))
#else
            if(memcmp(pucIDomainM1CRCValue, pucIDomainM1CRCValue_Backup, sizeof(pucIDomainM1CRCValue)) != 0)
#endif
            {
                memcpy(pucIDomainM1CRCValue_Backup, pucIDomainM1CRCValue, sizeof(pucIDomainM1CRCValue));

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
                memcpy(pucIDomainM2CRCValue_Backup, pucIDomainM2CRCValue, sizeof(pucIDomainM2CRCValue));
#endif
                ucPatternDebounce = 0x00;
                bPatternChangeFlag = 1;
            }
            else
            {
                ucPatternDebounce++;

                if((bPatternChangeFlag == 1) && (ucPatternDebounce > 50))
                {
                    bPatternChangeFlag = 0;

                    if(bPatternNO1Flag == 0)
                    {
                        bPatternNO1Flag = 1;
                        memcpy(pucIDomainM1CRCValue_NO1, pucIDomainM1CRCValue, sizeof(pucIDomainM1CRCValue));
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
                        memcpy(pucIDomainM2CRCValue_NO1, pucIDomainM2CRCValue, sizeof(pucIDomainM2CRCValue));
#endif
                    }

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
                    if ((memcmp(pucIDomainM1CRCValue, pucIDomainM1CRCValue_NO1, sizeof(pucIDomainM1CRCValue)) != 0) ||
                        (memcmp(pucIDomainM2CRCValue, pucIDomainM2CRCValue_NO1, sizeof(pucIDomainM2CRCValue)) != 0))
#else
                    if (memcmp(pucIDomainM1CRCValue, pucIDomainM1CRCValue_NO1, sizeof(pucIDomainM1CRCValue)) != 0)
#endif
                    {
                        ucPatternNo++;
                    }
                    else
                    {
                        ucPatternNo = 1;
                        usPatternCycleCounter++;
                        DebugMessageMemoryPhaseCal("usPatternCycleCounter", usPatternCycleCounter);
                    }

                    // Pattern Numner and CEC Value
                    DebugMessageMemoryPhaseCal("PatternNo", ucPatternNo);
                }
            }
        }

        // Debounce counter to bypass the beginning of test
        ucCounter++;

        // Reest result
        ucResult = 0x00;

        ScalerDebug();
    }
}
#endif // End of #if(_DDR_BURN_IN_TEST == _ON)


