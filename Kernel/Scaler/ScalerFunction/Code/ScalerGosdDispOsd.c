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
// ID Code      : ScalerGosdDispOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GOSDDISPOSD__

#include "ScalerFunctionInclude.h"
#include "Gosd/ScalerGosdDispOsd.h"

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile DWORD g_pulGosdDispOsdDisplayingSurfaceId[_GOSD_PLANE_MAXNUM];

volatile StructGosdDispOsdDisplayArgument g_ppstGosdDispOsdContinuousArgument[_GOSD_PLANE_MAXNUM][_GOSD_CONTINUOUS_STEP_MAX];

__attribute__((section(".ddr_data.g_pstGosdDispOsdPlane")))
StructGosdGdmaOsdCtrl g_pstGosdDispOsdPlane[_GOSD_PLANE_MAXNUM]; // OSD1, OSD2, OSD3

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
__attribute__((section(".ddr_data.g_pstGosdDispOsdPlane_Front")))
StructGosdGdmaOsdCtrl g_pstGosdDispOsdPlane_Front[_GOSD_PLANE_MAXNUM]; // OSD1, OSD2, OSD3

__attribute__((section(".ddr_data.g_pstGosdDispOsdPlane_Back")))
StructGosdGdmaOsdCtrl g_pstGosdDispOsdPlane_Back[_GOSD_PLANE_MAXNUM]; // OSD1, OSD2, OSD3
#endif // End of #if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)

volatile BYTE g_ucGosdDispOsdStatusBackup = 0;
volatile bit g_bGosdDispOsdBackup = _FALSE;
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
//--------------------------------------------------
// Description  : Set DispOsd Sharpness params
// Input Value  : enumOsd : GOsd plane
//                *pulSharpnessTable : params
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetRegSharpness(EnumGosdDisplayOSD enumOsd, DWORD *pulSharpnessTable, EnumDBApply enumDBApply)
{
    switch(enumOsd)
    {
        case _GOSD_PLANE_OSD1:
        case _GOSD_PLANE_OSD2:
        case _GOSD_PLANE_OSD3:
        {
            DWORD ulOffset = GET_GOSD_GDMA_OSD_REG_SR_OFFSET(enumOsd);
            for(BYTE ucIdx = 0; ucIdx < _GOSD_SHARPNESS_TABLE_LENGTH; ucIdx += 3)
            {
                Scaler32SetBit(pulSharpnessTable[ucIdx] + ulOffset, ~(pulSharpnessTable[ucIdx + 1]), pulSharpnessTable[ucIdx + 2]);
            }

            break;
        }
        case _GOSD_PLANE_ALL:
            for(BYTE ucOsdIdx = 0; ucOsdIdx < 3; ucOsdIdx++)
            {
                DWORD ulOffset = GET_GOSD_GDMA_OSD_REG_SR_OFFSET(ucOsdIdx);
                for(BYTE ucIdx = 0; ucIdx < _GOSD_SHARPNESS_TABLE_LENGTH; ucIdx += 3)
                {
                    Scaler32SetBit(pulSharpnessTable[ucIdx] + ulOffset, ~(pulSharpnessTable[ucIdx + 1]), pulSharpnessTable[ucIdx + 2]);
                }
            }
            break;
        default:
            break;
    }

    ScalerGosdDispOsdSetDisplayDBApply(enumDBApply);
}

//--------------------------------------------------
// Description  : GOSD display disable pre process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdDisplayDisableWithBackup(void)
{
    if(g_bGosdDispOsdBackup == _FALSE)
    {
        g_ucGosdDispOsdStatusBackup = ScalerGosdDispOsdClkSelectPreProc();
        g_bGosdDispOsdBackup = _TRUE;
    }
}

//--------------------------------------------------
// Description  : GDMA clock control post process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdDisplayEnableByBackup(void)
{
    if(g_bGosdDispOsdBackup == _TRUE)
    {
        BYTE ucGosdDispOsdStatusBackup = g_ucGosdDispOsdStatusBackup;
        g_bGosdDispOsdBackup = _FALSE;

        ScalerGosdDispOsdClkSelectPostProc(ucGosdDispOsdStatusBackup, _FALSE);
    }
}
#endif

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
//--------------------------------------------------
// Description  : Calculate SR Factor & InitialPhase
// Input Value  : pstSR : output parameters
//                usWinSize : Size before ScaleUp
//                usDispSize :Size after ScaleUp
// Output Value : none
//--------------------------------------------------
void ScalerGosdDispOsdCalculateSRParam(StructGosdGdmaSRParam *pstSR, WORD usWinSize, WORD usDispSize)
{
    memset(pstSR, 0, sizeof(StructGosdGdmaSRParam));

    // SR on
    if(usWinSize < usDispSize)
    {
        pstSR->b1SrEn = _ENABLE;
        // Calculate h sr factor
        pstSR->ulFactor = GET_DWORD_MUL_DIV((1UL << _GOSD_SR_FACTOR_BIT), usWinSize, usDispSize);
        pstSR->ulFactor = CLAMP(pstSR->ulFactor, 0xFFFFF, 0);
        // Calculate h initial phase
        pstSR->ulIni = (1UL << (19)) + GET_DWORD_MUL_DIV((1UL << 19), usWinSize, usDispSize); // (1 + In/Out) / 2 * 2^20
        pstSR->ulIni = CLAMP(pstSR->ulIni, 0xFFFFF, 0); // H initial phase = 20bit
    }
}

//--------------------------------------------------
// Description  : Get bit per pixel
// Input Value  : enumType
// Output Value : None
//--------------------------------------------------
BYTE ScalerGosdDispOsdGetBitPerPixel(EnumGosdGdmaColorType enumType)
{
    BYTE ucBit_per_pixel = 32;

    switch(enumType & 0x1F)
    {
        case _GDMA_COLOR_FORMAT_4BIT:
            ucBit_per_pixel = 4;
            break;
        case _GDMA_COLOR_FORMAT_8BIT:
            ucBit_per_pixel = 8;
            break;
        case _GDMA_COLOR_FORMAT_RGB565:
        case _GDMA_COLOR_FORMAT_ARGB1555:
        case _GDMA_COLOR_FORMAT_ARGB4444:
        case _GDMA_COLOR_FORMAT_YCBYCR88:
        case _GDMA_COLOR_FORMAT_YCBCRA4444:
        case _GDMA_COLOR_FORMAT_RGBA5551:
        case _GDMA_COLOR_FORMAT_RGBA4444:
        case _GDMA_COLOR_FORMAT_RGB556:
        case _GDMA_COLOR_FORMAT_RGB655:
            ucBit_per_pixel = 16;
            break;
        case _GDMA_COLOR_FORMAT_ARGB6666:
        case _GDMA_COLOR_FORMAT_RGB888:
        case _GDMA_COLOR_FORMAT_YCBYCR888:
            ucBit_per_pixel = 24;
            break;
        case _GDMA_COLOR_FORMAT_ARGB8888:
        case _GDMA_COLOR_FORMAT_YCBCRA8888:
        case _GDMA_COLOR_FORMAT_RGBA8888:
            ucBit_per_pixel = 32;
            break;
        default:
            break;
    }

    return ucBit_per_pixel;
}

//--------------------------------------------------
// Description  : Config line buffer
// Input Value  : ucL1_sta
//                ucL4_sta
//                ucL5_sta
//                ucL1_size
//                ucL4_size
//                ucL5_size
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdConfigLineBuffer(BYTE ucL1_sta, BYTE ucL4_sta, BYTE ucL5_sta, BYTE ucL1_size, BYTE ucL4_size, BYTE ucL5_size)
{
    /* line buffer setting */
    // L1 sta = 0, L4 sta = 2, L5 sta = 2
    Scaler32SetByte(PB004FF_10_LINE_BUFFER_STA, 0, (ucL1_sta & 0x0F));
    Scaler32SetByte(PB004FF_10_LINE_BUFFER_STA, 1, ((ucL4_sta & 0x0F) << 4));
    Scaler32SetByte(PB004FF_10_LINE_BUFFER_STA, 2, (ucL5_sta & 0x0F));
    // L1 size = 2, L4 size = 0, L5 size = 0
    Scaler32SetByte(PB004FF_14_LINE_BUFFER_SIZE, 0, (ucL1_size & 0x0F));
    Scaler32SetByte(PB004FF_14_LINE_BUFFER_SIZE, 1, ((ucL4_size & 0x0F) << 4));
    Scaler32SetByte(PB004FF_14_LINE_BUFFER_SIZE, 2, (ucL5_size & 0x0F));
}

//--------------------------------------------------
// Description  : Power on initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdPowerOnInitial(void)
{
    StructGosdMixerLayerSetting stMixerSetting = { _GOSD_B0, { 0x3F /* = -1*/, 0 /* = 0*/, 0x3F /* = -1*/, 0 /* = 0*/}};
    EnumGosdMixerLayer enumLayerSel = _GOSD_B0;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Check FB sepatate
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        // Set SR extension
        ScalerGosdDispOsdSetSRExtension();
    }
    else
#endif
    {
        // EO mode : front_back_separate_en enable
        ScalerGosdDispOsdFBSeperateEnable(_ENABLE);
    }

    // Set Gdma
    // Set line buffer
    // usage: AFBC: 8K, OSD1SR: 4K, OSD2SR: 4K
    // ScalerGosdDispOsdConfigLineBuffer(0x00, 0x02, 0x03, 0x02, 0x01, 0x01);
    // usage: AFBC: 8K, OSD1SR: 8K, OSD2SR: 0K
    // ScalerGosdDispOsdConfigLineBuffer(0x00, 0x02, 0x04, 0x02, 0x02, 0x00);
    // usage: AFBC: 0K, OSD1SR: 8K, OSD2SR: 8K
    ScalerGosdDispOsdConfigLineBuffer(0x00, 0x00, 0x02, 0x00, 0x02, 0x02);

    // Set AFBC 1b, 2b, 4b, 8b Swap
    Scaler32SetBit(PB004F9_2C_DMA_SWAP, ~(_BIT27 | _BIT26 | _BIT25 | _BIT24), (_BIT27 | _BIT26 | _BIT25 | _BIT24));
    // Set gdma_dmy_0_eco_afbc_xst_off
    Scaler32SetDWord(PB004FD_FC_DMY_0, 0x00000002);
    // OSD programming done
    ScalerGosdDispOsdSetGdmaDBApply(_DB_APPLY_NO_POLLING);

    // Set Mixer blending factor
    for(enumLayerSel = _GOSD_B0; enumLayerSel <= _GOSD_B2; enumLayerSel++)
    {
        stMixerSetting.enumLayerSel = enumLayerSel;
        ScalerGosdDispOsdSetMixerFactor(&stMixerSetting, _DB_APPLY_NO_POLLING);
    }

    // Set Mixer Select
    for(BYTE ucOsd = _GOSD_PLANE_OSD1; ucOsd < _GOSD_PLANE_MAXNUM; ucOsd++)
    {
        // default set Osd1: C0, Osd2: C1, Osd3: C2
        ScalerGosdDispOsdSetMixerLayer(ucOsd, ucOsd, _DB_APPLY_NO_POLLING);
    }

    // Set Mixer Enable
    ScalerGosdDispOsdSetMixerDBEnable(_DISABLE);
    ScalerGosdDispOsdSetMixerEnable(_ENABLE, _DB_APPLY_NO_POLLING);
    ScalerGosdDispOsdSetMixerOSDEnable(_GOSD_PLANE_ALL, _ENABLE, _DB_APPLY_NO_POLLING);

    ScalerGosdDispOsdInitial(_GOSD_PLANE_ALL);
}

//--------------------------------------------------
// Description  : Clear Osd
// Input Value  : pstPlane
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdClearOsd(StructGosdGdmaOsdCtrl *pstPlane)
{
    for(BYTE ucIdxBuf = 0; ucIdxBuf < _GOSD_GDMA_BUFFER_CONTROL; ucIdxBuf++)
    {
        memset(&pstPlane->pstOSDWin[ucIdxBuf], 0, sizeof(StructGosdGdmaWinInfo));
        memset(&pstPlane->pstOSDDisp[ucIdxBuf], 0, sizeof(StructGosdGdmaDispInfo));
    }
    pstPlane->b1OSDWinBufIdx = 0;
}

//--------------------------------------------------
// Description  : Initial
// Input Value  : enumOSD
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdInitial(EnumGosdDisplayOSD enumOSD)
{
    BYTE ucOsdIndex = (enumOSD == _GOSD_PLANE_ALL) ? (_GOSD_PLANE_OSD1) : (enumOSD);
    BYTE ucOsdNum = (enumOSD == _GOSD_PLANE_ALL) ? (3) : (enumOSD + 1);

    // Set osd clk by dclk and mclk
    ScalerGosdDispOsdClkSelect();

    for(ucOsdIndex = ucOsdIndex; ucOsdIndex < ucOsdNum; ucOsdIndex++)
    {
        ScalerGosdDispOsdClearOsd(&g_pstGosdDispOsdPlane[ucOsdIndex]);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            ScalerGosdDispOsdClearOsd(&g_pstGosdDispOsdPlane_Front[ucOsdIndex]);
            ScalerGosdDispOsdClearOsd(&g_pstGosdDispOsdPlane_Back[ucOsdIndex]);
        }
#endif
        g_pulGosdDispOsdDisplayingSurfaceId[ucOsdIndex] = _GOSD_SURFACE_NUMBER;
    }
}

//--------------------------------------------------
// Description  : Set mixer DB enable/disable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetMixerDBEnable(bit bEnable)
{
    Scaler32SetBit(PB004B0_A0_OSD_DB_CTRL, ~_BIT1, (bEnable == _TRUE) ? (_BIT1) : (0x00));
}

//--------------------------------------------------
// Description  : Set Mixer enable/disable
// Input Value  : bEnable
//                enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetMixerEnable(bit bEnable, EnumDBApply enumDBApply)
{
    // Set Mixer enable/disable
    Scaler32SetBit(PB004B0_00_MIXER_CTRL2, ~_BIT0, bEnable);

    // Check DB status
    ScalerGosdDispOsdSetMixerDBApply(enumDBApply);
}

//--------------------------------------------------
// Description  : CLUT select
// Input Value  : enumOSD
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetGdmaPaletteSelect(EnumGosdDisplayOSD enumOSD)
{
    Scaler32SetBit(PB004FF_18_LINE_BUFFER_END, ~(_BIT11 | _BIT10), ((DWORD)enumOSD + 1) << 10);
}

//--------------------------------------------------
// Description  : Set DisplayOsd Scale Up register
// Input Value  : enumOSD
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetRegScaleUp(EnumGosdDisplayOSD enumOSD)
{
    StructGosdGdmaDispInfo *pstDisp = &g_pstGosdDispOsdPlane[enumOSD].pstOSDDisp[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx];
    StructGosdGdmaSRParam *pstSR;
    DWORD ulOffset = GET_GOSD_GDMA_OSD_REG_SR_OFFSET(enumOSD);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    StructGosdGdmaDispInfo *pstDisp_Front = &g_pstGosdDispOsdPlane_Front[enumOSD].pstOSDDisp[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx];
    StructGosdGdmaDispInfo *pstDisp_Back = &g_pstGosdDispOsdPlane_Back[enumOSD].pstOSDDisp[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx];

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerGosdDispOsdFBSeperateEnable(_ENABLE);

        // Set Front and Back
        pstDisp = pstDisp_Front;
        for(BYTE ucIdx = 0; ucIdx < 2; ucIdx++)
        {
            // Set h factor and h initial value
            pstSR = &pstDisp->stDispSRParam.stHParam;
            Scaler32SetDWord(PB00494_04_OSD_SR_1_SCALEUP_CTRL1 + ulOffset, (((BYTE)pstSR->b1SrEn << 31) | (((pstSR->ulIni >> 12) & 0xFF) << 22) | (pstSR->ulFactor & 0xFFFFF))); // 0xB0049404 [31]+[29:22]+[19:0] : h_zoom_en+Hinit[19:12]+Hfactor
            Scaler32SetBit(PB00494_38_OSD_SR_1_SCALEUP_CTRL2 + ulOffset, ~(0x0FFF0000), (((pstSR->ulIni & 0x0F) << 24) | (((pstSR->ulIni >> 4) & 0xFF) << 16))); // 0xB0049438 [27:24]+[23:16] : init[3:0]+init[11:4]

            // Set v factor and v initial value
            pstSR = &pstDisp->stDispSRParam.stVParam;
            Scaler32SetDWord(PB00494_00_OSD_SR_1_SCALEUP_CTRL0 + ulOffset, (((BYTE)pstSR->b1SrEn << 31) | ((pstSR->ulIni & 0xFF) << 22) | (pstSR->ulFactor & 0xFFFFF))); // 0xB0049400 [31]+[29:22]+[21:20]+[19:0] : v_zoom_en+Vinit+VtapNum+Vfactor

            // Set display position & size
            Scaler32SetDWord(PB00494_08_OSD_SR_1_H_LOCATION_CTRL + ulOffset, (((pstDisp->stDispXY.usX & 0x1FFF) << 16) | (pstDisp->stDispWH.usWidth & 0x1FFF))); // 0xB0049408 [28:16]+[12:0] : Hstart+Hwidth
            Scaler32SetDWord(PB00494_0C_OSD_SR_1_V_LOCATION_CTRL + ulOffset, (((pstDisp->stDispXY.usY & 0x1FFF) << 16) | (pstDisp->stDispWH.usHeight & 0x1FFF))); // 0xB004940C [28:16]+[12:0] : Vstart+Hheight

            ulOffset += GET_GOSD_GDMA_OSD_REG_FB_OFFSET();
            pstDisp = pstDisp_Back;
        }

        ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
    }
    else // if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
#endif // #if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    {
        DWORD ulLocation_H = ((((pstDisp->stDispXY.usX) & 0x1FFF) << 16) | (pstDisp->stDispWH.usWidth & 0x1FFF));
        DWORD ulLocation_V = ((((pstDisp->stDispXY.usY) & 0x1FFF) << 16) | (pstDisp->stDispWH.usHeight & 0x1FFF));
#if(_PANEL_ASYMMETRIC == _ON)
        ulLocation_H += ((_PANEL_ASYMMETRIC_DUMMY_NUM_LEFT & 0x1FFF) << 16);
        ulLocation_V += ((_PANEL_ASYMMETRIC_DUMMY_NUM_TOP & 0x1FFF) << 16);
#endif

        // Set h factor and h initial value
        pstSR = &pstDisp->stDispSRParam.stHParam;
        Scaler32SetDWord(PB00494_04_OSD_SR_1_SCALEUP_CTRL1 + ulOffset, (((BYTE)pstSR->b1SrEn << 31) | (((pstSR->ulIni >> 12) & 0xFF) << 22) | (pstSR->ulFactor & 0xFFFFF))); // 0xB0049404 [31]+[29:22]+[19:0] : h_zoom_en+Hinit[19:12]+Hfactor
        Scaler32SetBit(PB00494_38_OSD_SR_1_SCALEUP_CTRL2 + ulOffset, ~(0x0FFF0000), (((pstSR->ulIni & 0x0F) << 24) | (((pstSR->ulIni >> 4) & 0xFF) << 16))); // 0xB0049438 [27:24]+[23:16] : init[3:0]+init[11:4]

        // Set v factor and v initial value
        pstSR = &pstDisp->stDispSRParam.stVParam;
        Scaler32SetDWord(PB00494_00_OSD_SR_1_SCALEUP_CTRL0 + ulOffset, (((BYTE)pstSR->b1SrEn << 31) | ((pstSR->ulIni & 0xFF) << 22) | (pstSR->ulFactor & 0xFFFFF))); // 0xB0049400 [31]+[29:22]+[21:20]+[19:0] : v_zoom_en+Vinit+VtapNum+Vfactor

        // Set display position & size
        Scaler32SetDWord(PB00494_08_OSD_SR_1_H_LOCATION_CTRL + ulOffset, ulLocation_H); // 0xB0049408 [28:16]+[12:0] : Hstart+Hwidth
        Scaler32SetDWord(PB00494_0C_OSD_SR_1_V_LOCATION_CTRL + ulOffset, ulLocation_V); // 0xB004940C [28:16]+[12:0] : Vstart+Hheight
    }
}

//--------------------------------------------------
// Description  : Set OSD HW registers according to parameter pstDisp which indicate OSD number
// Input Value  : pstDisp
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetRegGdma(EnumGosdDisplayOSD enumOSD, bit bDispOn)
{
    BYTE ucCurrentBufIdx = g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx;
    DWORD ulTemp = 0;
    WORD usOffset = 0;
    StructGosdGdmaOsdCtrl *pstOsdPlane;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    StructGosdGdmaOsdCtrl *pstOsdPlane_front;
    StructGosdGdmaOsdCtrl *pstOsdPlane_back;
#endif

    usOffset = GET_GOSD_GDMA_OSD_REG_OFFSET(enumOSD);

    if(bDispOn == _DISABLE)
    {
        Scaler32SetDWord((PB004F2_00_OSD1_CTRL + usOffset), 0x00000000);
        return;
    }

    pstOsdPlane = &g_pstGosdDispOsdPlane[enumOSD];

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        BYTE ucIdx = 0;
        DWORD ulFBOffset = 0;
        pstOsdPlane_front = &g_pstGosdDispOsdPlane_Front[enumOSD];
        pstOsdPlane_back = &g_pstGosdDispOsdPlane_Back[enumOSD];

        ScalerGosdDispOsdFBSeperateEnable(_ENABLE);

        // Set win info address
        pstOsdPlane = pstOsdPlane_front;
        for(ucIdx = 0; ucIdx < 2; ucIdx++)
        {
            Scaler32SetDWord((PB004F2_10_OSD1_WI + ulFBOffset + usOffset), GET_PHY_32BIT_DDR_ADDR((DWORD)(&pstOsdPlane->pstOSDWin[ucCurrentBufIdx])));
            // Set canvas width, height
            ulTemp = ((DWORD)pstOsdPlane->pstOSDWin[ucCurrentBufIdx].stWinWH.usWidth << 16) |
                     ((DWORD)pstOsdPlane->pstOSDWin[ucCurrentBufIdx].stWinWH.usHeight & 0xFFFF);
            Scaler32SetDWord((PB004F2_18_OSD1_SIZE + ulFBOffset + usOffset), ulTemp);

            ulFBOffset = GET_GOSD_GDMA_OSD_REG_FB_OFFSET();
            pstOsdPlane = pstOsdPlane_back;
        }

        // Set osd enable
        if(pstOsdPlane_front->pstOSDDisp[ucCurrentBufIdx].b1OSDDisplayEn == _FALSE)
        {
            // back only
            ulTemp = ((DWORD)bDispOn << 1);
            Scaler32SetDWord((PB004F2_00_OSD1_CTRL + usOffset), 0x00000000);
            Scaler32SetDWord((PB104F2_00_BACK_OSD1_CTRL + usOffset), ulTemp);
#if((_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON) && (_GOSD_DISPLAY_BW_CTRL_SUPPORT == _ON))
            StructBwCtrlClientInfo stBwCtrlInfo = {0};
            ScalerGosdDispOsdBwCtrlGetClientInfo(&stBwCtrlInfo, &pstOsdPlane_back->pstOSDWin[ucCurrentBufIdx], enumOSD, _TRUE);
            ScalerMemorySetBwCtrl(_MEM_CLIENT_GOSD_B, enumOSD, &stBwCtrlInfo);
#endif
        }
        else if(pstOsdPlane_back->pstOSDDisp[ucCurrentBufIdx].b1OSDDisplayEn == _FALSE)
        {
            // front only
            ulTemp = ((DWORD)bDispOn << 1);
            Scaler32SetDWord((PB004F2_00_OSD1_CTRL + usOffset), ulTemp);
            Scaler32SetDWord((PB104F2_00_BACK_OSD1_CTRL + usOffset), 0x00000000);
#if((_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON) && (_GOSD_DISPLAY_BW_CTRL_SUPPORT == _ON))
            StructBwCtrlClientInfo stBwCtrlInfo = {0};
            ScalerGosdDispOsdBwCtrlGetClientInfo(&stBwCtrlInfo, &pstOsdPlane_front->pstOSDWin[ucCurrentBufIdx], enumOSD, _FALSE);
            ScalerMemorySetBwCtrl(_MEM_CLIENT_GOSD_F, enumOSD, &stBwCtrlInfo);
#endif
        }
        else
        {
            // front + back
            ulTemp = ((DWORD)bDispOn << 1);
            Scaler32SetDWord((PB004F2_00_OSD1_CTRL + usOffset), ulTemp);
            Scaler32SetDWord((PB104F2_00_BACK_OSD1_CTRL + usOffset), ulTemp);
#if((_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON) && (_GOSD_DISPLAY_BW_CTRL_SUPPORT == _ON))
            StructBwCtrlClientInfo stBwCtrlInfo = {0};
            ScalerGosdDispOsdBwCtrlGetClientInfo(&stBwCtrlInfo, &pstOsdPlane_front->pstOSDWin[ucCurrentBufIdx], enumOSD, _FALSE);
            ScalerMemorySetBwCtrl(_MEM_CLIENT_GOSD_F, enumOSD, &stBwCtrlInfo);
            ScalerGosdDispOsdBwCtrlGetClientInfo(&stBwCtrlInfo, &pstOsdPlane_back->pstOSDWin[ucCurrentBufIdx], enumOSD, _TRUE);
            ScalerMemorySetBwCtrl(_MEM_CLIENT_GOSD_B, enumOSD, &stBwCtrlInfo);
#endif
        }

        ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
    }
    else
#endif
    {
        // Set osd enable
        Scaler32SetBit((PB004F2_00_OSD1_CTRL + usOffset), ~_BIT1, (bDispOn == _ENABLE) ? (_BIT1) : (0));

        // Set win info address
        Scaler32SetDWord((PB004F2_10_OSD1_WI + usOffset), GET_PHY_32BIT_DDR_ADDR((DWORD)(&pstOsdPlane->pstOSDWin[ucCurrentBufIdx])));

        // Set canvas width, height
        ulTemp = ((DWORD)pstOsdPlane->pstOSDWin[ucCurrentBufIdx].stWinWH.usWidth << 16) |
                 ((DWORD)pstOsdPlane->pstOSDWin[ucCurrentBufIdx].stWinWH.usHeight & 0xFFFF);
        Scaler32SetDWord((PB004F2_18_OSD1_SIZE + usOffset), ulTemp);
#if((_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON) && (_GOSD_DISPLAY_BW_CTRL_SUPPORT == _ON))
        StructBwCtrlClientInfo stBwCtrlInfo = {0};
        ScalerGosdDispOsdBwCtrlGetClientInfo(&stBwCtrlInfo, &pstOsdPlane->pstOSDWin[ucCurrentBufIdx], enumOSD, _FALSE);
        ScalerMemorySetBwCtrl(_MEM_CLIENT_GOSD_F, enumOSD, &stBwCtrlInfo);
#endif
    }

    // Select clut
    switch(pstOsdPlane->penumCLUTSel[ucCurrentBufIdx])
    {
        default:
        case _GOSD_PLANE_OSD1:
            Scaler32SetDWord(PB004FF_18_LINE_BUFFER_END, 0x00000400);
            break;
        case _GOSD_PLANE_OSD2:
            Scaler32SetDWord(PB004FF_18_LINE_BUFFER_END, 0x00000800);
            break;
        case _GOSD_PLANE_OSD3:
            Scaler32SetDWord(PB004FF_18_LINE_BUFFER_END, 0x00000C00);
            break;
    }
}

//--------------------------------------------------
// Description  : Calculate DispOsd settine params
// Input Value  : pstDispParam : output
//                pstWinRect : Window position and size
//                pstDispRect : Display position and size
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdCalculateParam(StructGosdDisplayParam *pstDispParam, StructGosdGdmaRectangle *pstWinRect, StructGosdGdmaRectangle *pstDispRect)
{
    StructGosdGdmaPlaneSRParam *pstSR;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    StructGosdGdmaPlaneSRParam *pstSR_Front;
    StructGosdGdmaPlaneSRParam *pstSR_Back;
#endif
    memcpy(&pstDispParam->stWinRect, pstWinRect, sizeof(StructGosdGdmaRectangle));
    memcpy(&pstDispParam->stDispRect, pstDispRect, sizeof(StructGosdGdmaRectangle));

    pstSR = &pstDispParam->stDispSRParam;
    ScalerGosdDispOsdCalculateSRParam(&pstSR->stHParam, pstWinRect->stWinWH.usWidth, pstDispRect->stWinWH.usWidth);
    ScalerGosdDispOsdCalculateSRParam(&pstSR->stVParam, pstWinRect->stWinWH.usHeight, pstDispRect->stWinWH.usHeight);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    pstSR_Front = &pstDispParam->stDispSRParam_Front;
    pstSR_Back = &pstDispParam->stDispSRParam_Back;
    memcpy(pstSR_Front, pstSR, sizeof(StructGosdGdmaPlaneSRParam));
    memcpy(pstSR_Back, pstSR, sizeof(StructGosdGdmaPlaneSRParam));

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        // front only
        if(pstDispRect->stWinXY.usX + pstDispRect->stWinWH.usWidth < (_PANEL_DH_WIDTH / 2))
        {
            // front
            pstDispParam->bOSDDisplayEn_Front = _TRUE;
            memcpy(&pstDispParam->stWinRect_Front, pstWinRect, sizeof(StructGosdGdmaRectangle));
            memcpy(&pstDispParam->stDispRect_Front, pstDispRect, sizeof(StructGosdGdmaRectangle));
            // back
            pstDispParam->bOSDDisplayEn_Back = _FALSE;
        }
        // back only
        else if(pstDispRect->stWinXY.usX > (_PANEL_DH_WIDTH / 2))
        {
            // front
            pstDispParam->bOSDDisplayEn_Front = _FALSE;
            // back
            pstDispParam->bOSDDisplayEn_Back = _TRUE;
            memcpy(&pstDispParam->stWinRect_Back, pstWinRect, sizeof(StructGosdGdmaRectangle));
            memcpy(&pstDispParam->stDispRect_Back, pstDispRect, sizeof(StructGosdGdmaRectangle));
            pstDispParam->stDispRect_Back.stWinXY.usX = pstDispRect->stWinXY.usX - (_PANEL_DH_WIDTH / 2) + _GOSD_SR_EXTENSION;
        }
        // front + back
        else
        {
            DWORD ulHfactor = pstSR->stHParam.ulFactor;
            DWORD ulHIni = pstSR->stHParam.ulIni;
            WORD usFrontInWidth = 0;
            WORD usFrontOutWidth = 0;
            WORD usBackInWidth = 0;
            WORD usBackOutWidth = 0;
            WORD usBackInExt = 0;
            WORD usBackOutExt = 0;
            DWORD ulBackHIni = 0;

            usFrontOutWidth = (_PANEL_DH_WIDTH / 2) - pstDispRect->stWinXY.usX;
            usBackOutWidth = pstDispRect->stWinWH.usWidth - usFrontOutWidth;

            if(pstSR->stHParam.b1SrEn == _TRUE)
            {
                // calculate back_initial & back_extension
                usFrontInWidth = ((usFrontOutWidth * ulHfactor << 1) / (1UL << 20) + 1) >> 1;
                usBackInWidth = pstWinRect->stWinWH.usWidth - usFrontInWidth;

                usBackInExt = (usFrontInWidth >= 4) ? (4) : (usFrontInWidth);
                usBackOutExt = GET_DWORD_MUL_DIV(usBackInExt, (1UL << 20), ulHfactor);

                ulBackHIni = ulHIni + (usFrontOutWidth - usBackOutExt) * ulHfactor - ((DWORD)(usFrontInWidth - usBackInExt) << 20);
                while(ulBackHIni > 0x000FFFFFUL)
                {
                    usBackOutExt += 1;
                    ulBackHIni -= ulHfactor;
                }

                usBackOutWidth += usBackOutExt;
            }
            else
            {
                usFrontInWidth = usFrontOutWidth;
                usBackInWidth = usBackOutWidth;
            }

            // front
            pstDispParam->bOSDDisplayEn_Front = _TRUE;
            pstDispParam->stDispRect_Front.stWinXY.usX = pstDispRect->stWinXY.usX;
            pstDispParam->stDispRect_Front.stWinXY.usY = pstDispRect->stWinXY.usY;
            pstDispParam->stDispRect_Front.stWinWH.usWidth = usFrontOutWidth;
            pstDispParam->stDispRect_Front.stWinWH.usHeight = pstDispRect->stWinWH.usHeight;
            pstDispParam->stWinRect_Front.stWinXY.usX = pstWinRect->stWinXY.usX;
            pstDispParam->stWinRect_Front.stWinXY.usY = pstWinRect->stWinXY.usY;
            pstDispParam->stWinRect_Front.stWinWH.usWidth = usFrontInWidth;
            pstDispParam->stWinRect_Front.stWinWH.usHeight = pstWinRect->stWinWH.usHeight;

            // back
            pstDispParam->bOSDDisplayEn_Back = _TRUE;
            pstDispParam->stDispRect_Back.stWinXY.usX = _GOSD_SR_EXTENSION - usBackOutExt;
            pstDispParam->stDispRect_Back.stWinXY.usY = pstDispRect->stWinXY.usY;
            pstDispParam->stDispRect_Back.stWinWH.usWidth = usBackOutWidth;
            pstDispParam->stDispRect_Back.stWinWH.usHeight = pstDispRect->stWinWH.usHeight;
            pstDispParam->stWinRect_Back.stWinXY.usX = pstWinRect->stWinXY.usX + usFrontInWidth - usBackInExt;
            pstDispParam->stWinRect_Back.stWinXY.usY = pstWinRect->stWinXY.usY;
            pstDispParam->stWinRect_Back.stWinWH.usWidth = usBackInWidth + usBackInExt;
            pstDispParam->stWinRect_Back.stWinWH.usHeight = pstWinRect->stWinWH.usHeight;

            pstSR_Back->stHParam.ulIni = ulBackHIni;
        }
    }
    else // else if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
#endif
    {
        pstDispParam->bOSDDisplayEn = _TRUE;
    }
}

//--------------------------------------------------
// Description  : Check DispOsd position and size
// Input Value  : enumOSD : which OSD plane
//                pstSurfaceInfo : surface parameters
//                pstDispParam : Display params
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdDispOsdCheckPositionAndSize(EnumGosdDisplayOSD enumOSD, StructGosdSurfaceInfo *pstSurfaceInfo, StructGosdDisplayParam *pstDispParam)
{
    WORD usMaxInputSize = 0;

    if(enumOSD == _GOSD_PLANE_OSD3)
    {
        usMaxInputSize = _GOSD_GDMA_MAX_WIDTH_OSD3;
    }
    else
    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            usMaxInputSize = MINOF((_PANEL_DH_TOTAL / 4), _GOSD_GDMA_MAX_WIDTH_OSD1);
        }
        else
#endif
        {
            usMaxInputSize = MINOF((_PANEL_DH_TOTAL / 2), _GOSD_GDMA_MAX_WIDTH_OSD1);
        }
    }

    DebugMessageGOSD("usMaxInputSize", usMaxInputSize);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        if(usMaxInputSize < pstDispParam->stWinRect_Front.stWinWH.usWidth)
        {
            DebugMessageGOSD("Front Window Width is larger than MaxInputSize", 0);
            DebugMessageGOSD("  MaxInputSize", usMaxInputSize);
            DebugMessageGOSD("  Window_W", pstDispParam->stWinRect_Front.stWinWH.usWidth);
            return _FALSE;
        }

        if(usMaxInputSize < pstDispParam->stWinRect_Back.stWinWH.usWidth)
        {
            DebugMessageGOSD("Back Window Width is larger than MaxInputSize", 0);
            DebugMessageGOSD("  MaxInputSize", usMaxInputSize);
            DebugMessageGOSD("  Window_W", pstDispParam->stWinRect_Back.stWinWH.usWidth);
            return _FALSE;
        }
    }
    else
#endif
    {
        if(usMaxInputSize < pstDispParam->stWinRect.stWinWH.usWidth)
        {
            DebugMessageGOSD("Window Width is larger than MaxInputSize", 0);
            DebugMessageGOSD("  MaxInputSize", usMaxInputSize);
            DebugMessageGOSD("  Window_W", pstDispParam->stWinRect.stWinWH.usWidth);
            return _FALSE;
        }
    }

    if((_PANEL_DH_WIDTH < pstDispParam->stDispRect.stWinXY.usX + pstDispParam->stDispRect.stWinWH.usWidth) ||
       (_PANEL_DV_HEIGHT < pstDispParam->stDispRect.stWinXY.usY + pstDispParam->stDispRect.stWinWH.usHeight))
    {
        DebugMessageGOSD("Display size out of panel boundary", 0);
        DebugMessageGOSD("  Disp_X", pstDispParam->stDispRect.stWinXY.usX);
        DebugMessageGOSD("  Disp_Y", pstDispParam->stDispRect.stWinXY.usY);
        DebugMessageGOSD("  Disp_W", pstDispParam->stDispRect.stWinWH.usWidth);
        DebugMessageGOSD("  Disp_H", pstDispParam->stDispRect.stWinWH.usHeight);
        return _FALSE;
    }

    if((pstSurfaceInfo->usWidth < pstDispParam->stWinRect.stWinXY.usX + pstDispParam->stWinRect.stWinWH.usWidth) ||
       (pstSurfaceInfo->usHeight < pstDispParam->stWinRect.stWinXY.usY + pstDispParam->stWinRect.stWinWH.usHeight))
    {
        DebugMessageGOSD("Window size out of surface boundary", 0);
        DebugMessageGOSD("  Window_X", pstDispParam->stWinRect.stWinXY.usX);
        DebugMessageGOSD("  Window_Y", pstDispParam->stWinRect.stWinXY.usY);
        DebugMessageGOSD("  Window_W", pstDispParam->stWinRect.stWinWH.usWidth);
        DebugMessageGOSD("  Window_H", pstDispParam->stWinRect.stWinWH.usHeight);
        return _FALSE;
    }

    if((pstDispParam->stDispRect.stWinWH.usWidth < pstDispParam->stWinRect.stWinWH.usWidth) ||
       (pstDispParam->stDispRect.stWinWH.usHeight < pstDispParam->stWinRect.stWinWH.usHeight))
    {
        DebugMessageGOSD("Disp Size must greater than or equal to Window size", 0);
        DebugMessageGOSD("  Disp_W", pstDispParam->stDispRect.stWinWH.usWidth);
        DebugMessageGOSD("  Disp_H", pstDispParam->stDispRect.stWinWH.usHeight);
        DebugMessageGOSD("  Window_W", pstDispParam->stWinRect.stWinWH.usWidth);
        DebugMessageGOSD("  Window_H", pstDispParam->stWinRect.stWinWH.usHeight);
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Calculate Position and Size parameters
// Input Value  : enumOSD : which OSD plane
//                pstFullWH : Full Size
//                pstDispParam : Display params
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetPositionAndSize(EnumGosdDisplayOSD enumOSD, StructGosdGdmaWinWH *pstFullWH, StructGosdDisplayParam *pstDispParam)
{
    StructGosdGdmaOsdCtrl *pstOsdPlane;
    StructGosdGdmaDispInfo *pstDisp;
    StructGosdGdmaWinInfo *pstWin;
    BYTE ucCurrentBufIdx = 0;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    StructGosdGdmaOsdCtrl *pstOsdPlane_Front;
    StructGosdGdmaOsdCtrl *pstOsdPlane_Back;
    StructGosdGdmaDispInfo *pstDisp_Front;
    StructGosdGdmaDispInfo *pstDisp_Back;
    StructGosdGdmaWinInfo *pstWin_Front;
    StructGosdGdmaWinInfo *pstWin_Back;
#endif

#if(_GOSD_FW_MODE == _GOSD_FW_ONE_CPU_MODE)
    pstFullWH = pstFullWH;
#endif
    pstOsdPlane = &g_pstGosdDispOsdPlane[enumOSD];
    ucCurrentBufIdx = pstOsdPlane->b1OSDWinBufIdx;
    pstDisp = &pstOsdPlane->pstOSDDisp[ucCurrentBufIdx];
    pstWin = &pstOsdPlane->pstOSDWin[ucCurrentBufIdx];

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    pstOsdPlane_Front = &g_pstGosdDispOsdPlane_Front[enumOSD];
    pstOsdPlane_Back = &g_pstGosdDispOsdPlane_Back[enumOSD];
    pstDisp_Front = &pstOsdPlane_Front->pstOSDDisp[ucCurrentBufIdx];
    pstDisp_Back = &pstOsdPlane_Back->pstOSDDisp[ucCurrentBufIdx];
    pstWin_Front = &pstOsdPlane_Front->pstOSDWin[ucCurrentBufIdx];
    pstWin_Back = &pstOsdPlane_Back->pstOSDWin[ucCurrentBufIdx];
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        // set front
        if(pstDispParam->bOSDDisplayEn_Front == _TRUE)
        {
            pstDisp_Front->b1OSDDisplayEn = _TRUE;
            memcpy(&pstDisp_Front->stDispWH, &pstDispParam->stDispRect_Front.stWinWH, sizeof(StructGosdGdmaWinWH));
            memcpy(&pstDisp_Front->stDispXY, &pstDispParam->stDispRect_Front.stWinXY, sizeof(StructGosdGdmaWinXY));
            memcpy(&pstOsdPlane_Front->pstOSDWin[ucCurrentBufIdx].stWinWH, &pstDispParam->stWinRect_Front.stWinWH, sizeof(StructGosdGdmaWinWH));
            pstWin_Front->stObjOffset.usObjXoffset = pstDispParam->stWinRect_Front.stWinXY.usX;
            pstWin_Front->stObjOffset.usObjYoffset = pstDispParam->stWinRect_Front.stWinXY.usY;
        }
        else
        {
            pstDisp_Front->b1OSDDisplayEn = _FALSE;
        }

        // set back
        if(pstDispParam->bOSDDisplayEn_Back == _TRUE)
        {
            pstDisp_Back->b1OSDDisplayEn = _TRUE;
            memcpy(&pstDisp_Back->stDispWH, &pstDispParam->stDispRect_Back.stWinWH, sizeof(StructGosdGdmaWinWH));
            memcpy(&pstDisp_Back->stDispXY, &pstDispParam->stDispRect_Back.stWinXY, sizeof(StructGosdGdmaWinXY));
            memcpy(&pstOsdPlane_Back->pstOSDWin[ucCurrentBufIdx].stWinWH, &pstDispParam->stWinRect_Back.stWinWH, sizeof(StructGosdGdmaWinWH));
            pstWin_Back->stObjOffset.usObjXoffset = pstDispParam->stWinRect_Back.stWinXY.usX;
            pstWin_Back->stObjOffset.usObjYoffset = pstDispParam->stWinRect_Back.stWinXY.usY;
        }
        else
        {
            pstDisp_Back->b1OSDDisplayEn = _FALSE;
        }

#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        if(pstWin->stAttr.b1IMGcompress == _TRUE)
        {
            pstWin = pstWin_Front;
            for(BYTE ucIdx = 0; ucIdx < 2; ucIdx++)
            {
                pstWin->stAfbc_totaltile.usX_total_tile = pstFullWH->usWidth;
                pstWin->stAfbc_totaltile.usY_total_tile = pstFullWH->usHeight;

                // In FDBC format, ObjOffset
                pstWin->stAfbc_xy_sta.usX_sta = pstWin->stObjOffset.usObjXoffset;
                pstWin->stAfbc_xy_sta.usY_sta = pstWin->stObjOffset.usObjYoffset;
                pstWin->stObjOffset.usObjYoffset = (WORD)((pstWin->ulTop_addr & 0xFFFF0000) >> 16);
                pstWin->stObjOffset.usObjXoffset = (WORD)(pstWin->ulTop_addr & 0xFFFF);
                pstWin->stAfbc_xy_pixel.usX_pic_pixel = pstWin->stWinWH.usWidth;
                pstWin->stAfbc_xy_pixel.usY_pic_pixel = pstWin->stWinWH.usHeight;

                pstWin = pstWin_Back;
            }
        }
#endif
    }
    else // else if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
#endif
    {
        pstDisp->b1OSDDisplayEn = _TRUE;
        memcpy(&pstDisp->stDispWH, &pstDispParam->stDispRect.stWinWH, sizeof(StructGosdGdmaWinWH));
        memcpy(&pstDisp->stDispXY, &pstDispParam->stDispRect.stWinXY, sizeof(StructGosdGdmaWinXY));
        memcpy(&pstOsdPlane->pstOSDWin[ucCurrentBufIdx].stWinWH, &pstDispParam->stWinRect.stWinWH, sizeof(StructGosdGdmaWinWH));
        pstWin->stObjOffset.usObjXoffset = pstDispParam->stWinRect.stWinXY.usX;
        pstWin->stObjOffset.usObjYoffset = pstDispParam->stWinRect.stWinXY.usY;

#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        if(pstWin->stAttr.b1IMGcompress == _TRUE)
        {
            pstWin->stAfbc_totaltile.usX_total_tile = pstFullWH->usWidth;
            pstWin->stAfbc_totaltile.usY_total_tile = pstFullWH->usHeight;

            // In FDBC format, ObjOffset
            pstWin->stAfbc_xy_sta.usX_sta = pstWin->stObjOffset.usObjXoffset;
            pstWin->stAfbc_xy_sta.usY_sta = pstWin->stObjOffset.usObjYoffset;
            pstWin->stObjOffset.usObjYoffset = (WORD)((pstWin->ulTop_addr & 0xFFFF0000) >> 16);
            pstWin->stObjOffset.usObjXoffset = (WORD)(pstWin->ulTop_addr & 0xFFFF);
            pstWin->stAfbc_xy_pixel.usX_pic_pixel = pstWin->stWinWH.usWidth;
            pstWin->stAfbc_xy_pixel.usY_pic_pixel = pstWin->stWinWH.usHeight;
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Set Window Info
// Input Value  : enumOSD : which OSD plane
//                pstCreatWin : Window parameters
//                pstDispParam : Display params
// Output Value : _GDMA_SUCCESS / _GDMA_FAIL
//--------------------------------------------------
EnumGosdGdmaStatus ScalerGosdDispOsdSetWindow(EnumGosdDisplayOSD enumOSD, StructGosdGdmaCreateWin *pstCreatWin, StructGosdDisplayParam *pstDispParam)
{
    StructGosdGdmaWinInfo *pstWin = &g_pstGosdDispOsdPlane[enumOSD].pstOSDWin[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx];

    pstWin->stNxtAddr.b1Last = _TRUE;

    // position in canvas : default (0, 0)
    pstWin->stWinXY.usX = 0;
    pstWin->stWinXY.usY = 0;

    pstWin->stAttr.b8AlphaValue = pstCreatWin->ucAlpha;
    pstWin->stAttr.b1AlphaEn = ((pstWin->stAttr.b8AlphaValue) > 0) ? (1) : (0);
    pstWin->stAttr.b5Type = pstCreatWin->enumColorType & 0x1F;
    pstWin->stAttr.b1LittleEndian = pstCreatWin->enumColorType >> 5;
    pstWin->stAttr.b3RgbOrder = pstCreatWin->enumRgbOrder;
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    pstWin->stAttr.b1IMGcompress = pstCreatWin->b1Compressed;
#endif
    pstWin->stColorKey.b1KeyEn = pstCreatWin->b1ColorKeyEn;
    pstWin->stColorKey.b24Key = pstCreatWin->ulColorKey;
    pstWin->ulPitch = pstCreatWin->ulPitch;

    pstWin->ulTop_addr = pstCreatWin->ulOsdAddr;

    switch(pstWin->stAttr.b5Type)
    {
        case _GDMA_COLOR_FORMAT_4BIT:
        case _GDMA_COLOR_FORMAT_8BIT:
            pstWin->ulCLUT_addr = pstCreatWin->ulPaletteAddr;
            pstWin->stAttr.b1KeepPreCLUT = 0;
            pstWin->stAttr.b1ClutFmt = 1; // Fixed Clut format = RGBA
            g_pstGosdDispOsdPlane[enumOSD].penumCLUTSel[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx] = enumOSD;
            break;
        default:
            break;
    }

#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    if(pstWin->stAttr.b1IMGcompress == _TRUE)
    {
        // AFBC Setting
        switch(pstWin->stAttr.b5Type)
        {
            case _GDMA_COLOR_FORMAT_ARGB8888:
            case _GDMA_COLOR_FORMAT_RGBA8888:
            case _GDMA_COLOR_FORMAT_ARGB8888_RGB6TO8:
            case _GDMA_COLOR_FORMAT_ARGB8888_ARGB6TO8:
                pstWin->stAfbc_format.b1Afbc_fmt_1st = 0; // ARGB8888
                break;
            case _GDMA_COLOR_FORMAT_RGB888:
            case _GDMA_COLOR_FORMAT_RGB888_RGB6TO8:
                pstWin->stAfbc_format.b1Afbc_fmt_1st = 1; // RGB888
                break;
            default:
                DebugMessageGOSD("Error: AFBC type error", pstWin->stAttr.b5Type);
                return _GDMA_FAIL;
        }
        pstWin->stAfbc_format.b5AfbcArgbOrder = 5;

        pstWin->stAttr.b1AlphaEn = _FALSE; // FBDC has alpha fucntion itself
        pstWin->stAttr.b8AlphaValue = 0; // FBDC has alpha fucntion itself
        pstWin->ulCLUT_addr = 0;
    }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        StructGosdGdmaWinInfo *pstWin_Front = &g_pstGosdDispOsdPlane_Front[enumOSD].pstOSDWin[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx];
        StructGosdGdmaWinInfo *pstWin_Back = &g_pstGosdDispOsdPlane_Back[enumOSD].pstOSDWin[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx];
        StructGosdGdmaPlaneSRParam *pstSR_Front = &g_pstGosdDispOsdPlane_Front[enumOSD].pstOSDDisp[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx].stDispSRParam;
        StructGosdGdmaPlaneSRParam *pstSR_Back = &g_pstGosdDispOsdPlane_Back[enumOSD].pstOSDDisp[g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx].stDispSRParam;
        memcpy(pstWin_Front, pstWin, sizeof(StructGosdGdmaWinInfo));
        memcpy(pstWin_Back, pstWin, sizeof(StructGosdGdmaWinInfo));
        memcpy(pstSR_Front, &pstDispParam->stDispSRParam_Front, sizeof(StructGosdGdmaPlaneSRParam));
        memcpy(pstSR_Back, &pstDispParam->stDispSRParam_Back, sizeof(StructGosdGdmaPlaneSRParam));
    }
#endif

    ScalerGosdDispOsdSetPositionAndSize(enumOSD, &(pstCreatWin->stFullWH), pstDispParam);

    return _GDMA_SUCCESS;
}

//--------------------------------------------------
// Description  : Set Window parameters
// Input Value  : pstCreatWin : Output Window parameters
//                pstSurface : Surface
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdCreateWindow(StructGosdGdmaCreateWin *pstCreatWin, DWORD ulSurfaceId)
{
    BYTE ucTemp = 0;
    StructGosdSurfaceInfo stSurfaceInfo = ScalerGosdGetSurfaceInfo(ulSurfaceId);

    memset(pstCreatWin, 0, sizeof(StructGosdGdmaCreateWin));

    pstCreatWin->stFullWH.usWidth = stSurfaceInfo.usWidth;
    pstCreatWin->stFullWH.usHeight = stSurfaceInfo.usHeight;

    pstCreatWin->ucAlpha = 0;
    pstCreatWin->b1ColorKeyEn = 0;
    pstCreatWin->ulColorKey = 0;

    pstCreatWin->ulOsdAddr = stSurfaceInfo.ulAddress;
    pstCreatWin->ulPitch = stSurfaceInfo.usPitch;

    switch(stSurfaceInfo.enumPixelFormat)
    {
        case _GOSD_PIXEL_FORMAT_ARGB8888:
            pstCreatWin->enumColorType = _GDMA_COLOR_FORMAT_ARGB8888;
            break;
        case _GOSD_PIXEL_FORMAT_RGB888:
            pstCreatWin->enumColorType = _GDMA_COLOR_FORMAT_RGB888;
            break;
        case _GOSD_PIXEL_FORMAT_ARGB4444:
            pstCreatWin->enumColorType = _GDMA_COLOR_FORMAT_ARGB4444;
            break;
        case _GOSD_PIXEL_FORMAT_ARGB1555:
            pstCreatWin->enumColorType = _GDMA_COLOR_FORMAT_ARGB1555;
            break;
        case _GOSD_PIXEL_FORMAT_RGB565:
            pstCreatWin->enumColorType = _GDMA_COLOR_FORMAT_RGB565;
            break;
        case _GOSD_PIXEL_FORMAT_INDEX8:
            pstCreatWin->enumColorType = _GDMA_COLOR_FORMAT_8BIT;
            break;
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        case _GOSD_PIXEL_FORMAT_AFBC4U8:
            pstCreatWin->enumColorType = _GDMA_COLOR_FORMAT_ARGB8888;
            pstCreatWin->b1Compressed = 1;
            break;
        case _GOSD_PIXEL_FORMAT_AFBC3U8:
            pstCreatWin->enumColorType = _GDMA_COLOR_FORMAT_RGB888;
            pstCreatWin->b1Compressed = 1;
            break;
#endif
        default:
            break;
    }

    ucTemp = pstCreatWin->enumColorType;
    pstCreatWin->enumColorType = (stSurfaceInfo.b1BigEndian == _FALSE) ? (ucTemp | _BIT5) : (pstCreatWin->enumColorType);
    pstCreatWin->ulOsdAddr = stSurfaceInfo.ulAddress;
    pstCreatWin->ulPaletteAddr = stSurfaceInfo.ulClutAddress;
}

//--------------------------------------------------
// Description  : Display Surface
// Input Value  : pstArgument : Display arguments
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack ScalerGosdDispOsdDisplaySurface(StructGosdDispOsdDisplayArgument *pstArgument)
{
    if((GOSD_GET_SURFACE_STATUS(pstArgument->ulSurfaceId) == _GOSD_SURFACE_UNCREATED) ||
       (GOSD_GET_SURFACE_STATUS(pstArgument->ulSurfaceId) == _GOSD_SURFACE_UNDEFINED) ||
       (GOSD_GET_SURFACE_STATUS(pstArgument->ulSurfaceId) == _GOSD_SURFACE_LOADING) ||
       (GOSD_GET_SURFACE_STATUS(pstArgument->ulSurfaceId) == _GOSD_SURFACE_SE_WORKING_WRITE))
    {
        DebugMessageGOSD("Surface not ready for Display", pstArgument->ulSurfaceId);
        DebugMessageGOSD("  Status", GOSD_GET_SURFACE_STATUS(pstArgument->ulSurfaceId));
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSurfaceInfo stSurfaceInfo = ScalerGosdGetSurfaceInfo(pstArgument->ulSurfaceId);
    StructGosdGdmaRectangle *pstWinRect = &(pstArgument->stWinRect);
    StructGosdGdmaRectangle *pstDispRect = &(pstArgument->stDispRect);
    EnumGosdDisplayOSD enumOSD = pstArgument->enumOSD;
    EnumDBApply enumDBApply = pstArgument->enumDBApply;

    if(enumOSD > _GOSD_PLANE_OSD3)
    {
        DebugMessageGOSD("Error : osd idx", enumOSD);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    if((stSurfaceInfo.enumPixelFormat == _GOSD_PIXEL_FORMAT_AFBC4U8) || (stSurfaceInfo.enumPixelFormat == _GOSD_PIXEL_FORMAT_AFBC3U8))
    {
        if(enumOSD != _GOSD_PLANE_OSD1)
        {
            DebugMessageGOSD("Error : Only Osd1 support AFBC", enumOSD);
            return _GOSD_SYNC_FEEDBACK_ERROR;
        }
    }
#endif

    StructGosdDisplayParam stDispParam;
    memset(&stDispParam, 0, sizeof(StructGosdDisplayParam));
    ScalerGosdDispOsdCalculateParam(&stDispParam, pstWinRect, pstDispRect);

    if(ScalerGosdDispOsdCheckPositionAndSize(enumOSD, &stSurfaceInfo, &stDispParam) == _FALSE)
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdGdmaCreateWin stCreatWin;
    BYTE ucCurrentBufIdx = g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx;
    BYTE ucNextBufIdx = (ucCurrentBufIdx == 0) ? 1 : 0;
    // BYTE ucPrevBufIdx = (ucCurrentBufIdx == 0) ? 1 : 0;
    StructGosdGdmaPlaneSRParam *pstSrParam = &g_pstGosdDispOsdPlane[enumOSD].pstOSDDisp[ucCurrentBufIdx].stDispSRParam;

    // Get Window arguments
    ScalerGosdDispOsdCreateWindow(&stCreatWin, pstArgument->ulSurfaceId);

    // Set SR Parameter
    memcpy(pstSrParam, &stDispParam.stDispSRParam, sizeof(StructGosdGdmaPlaneSRParam));

    // Set Window Info
    ScalerGosdDispOsdSetWindow(enumOSD, &stCreatWin, &stDispParam);

    // Set Gdma Reg
    ScalerGosdDispOsdSetRegGdma(enumOSD, _ENABLE);

    // Set SR Reg
    ScalerGosdDispOsdSetRegScaleUp(enumOSD);

    // DBApplay
    ScalerGosdDispOsdSetGdmaDBApply(enumDBApply);

    // Change double buffer index
    g_pstGosdDispOsdPlane[enumOSD].b1OSDWinBufIdx = ucNextBufIdx;

    // reset previous surface status
    if(g_pulGosdDispOsdDisplayingSurfaceId[enumOSD] < _GOSD_SURFACE_NUMBER)
    {
        GOSD_SET_SURFACE_STATUS(g_pulGosdDispOsdDisplayingSurfaceId[enumOSD], _GOSD_SURFACE_IDLE);
    }
    // set Displaying surfaceId
    g_pulGosdDispOsdDisplayingSurfaceId[enumOSD] = pstArgument->ulSurfaceId;
    // set surface status
    GOSD_SET_SURFACE_STATUS(pstArgument->ulSurfaceId, _GOSD_SURFACE_DISPOSD_SHOWING);

    return _GOSD_SYNC_FEEDBACK_SUCCESS;
}

//--------------------------------------------------
// Description  : Get Gosd Displaying Param
// Input Value  : enumOsd : OSD1, OSD2, OSD3
//                pstArgument [out]: Display arguments
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdDispOsdGetOsdParam(EnumGosdDisplayOSD enumOsd, StructGosdDisplayOsdParam *pstParam)
{
    // get win info
    DWORD ulWinInfoAddress = Scaler32GetDWord(PB004F2_10_OSD1_WI + 0x100UL * enumOsd);
    DWORD ulSurfaceAddress = 0;
    WORD usWinX = 0;
    WORD usWinY = 0;
    WORD usWinW = 0;
    WORD usWinH = 0;
    StructGosdGdmaWinInfo *pstWinInfo = (StructGosdGdmaWinInfo *)GET_DDR_32BIT_ADDR(ulWinInfoAddress);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerGosdDispOsdFBSeperateEnable(_ENABLE);

        DWORD ulWinInfoAddress_Back = Scaler32GetDWord(PB104F2_10_BACK_OSD1_WI + 0x100UL * enumOsd);
        WORD usWinW_Back = 0;
        StructGosdGdmaWinInfo *pstWinInfo_Back = (StructGosdGdmaWinInfo *)GET_DDR_32BIT_ADDR(ulWinInfoAddress_Back);

        // BIT0: osd1, BIT2: osd2, BIT4: osd3
        // front + back
        if((Scaler32GetBit(PB004FF_20_OSD_STATUS, 1UL << (enumOsd << 1)) != 0) &&
           (Scaler32GetBit(PB104FF_20_BACK_OSD_STATUS, 1UL << (enumOsd << 1)) != 0))
        {
            // get WinRect
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
            if(pstWinInfo->stAttr.b1IMGcompress == _FALSE)
            {
                ulSurfaceAddress = pstWinInfo->ulTop_addr;
                usWinX = pstWinInfo->stObjOffset.usObjXoffset;
                usWinY = pstWinInfo->stObjOffset.usObjYoffset;
                usWinW = pstWinInfo->stWinWH.usWidth;
                usWinH = pstWinInfo->stWinWH.usHeight;
                usWinW_Back = pstWinInfo_Back->stWinWH.usWidth;
            }
            else
            {
                ulSurfaceAddress = ((DWORD)pstWinInfo->stObjOffset.usObjYoffset << 16) + (DWORD)pstWinInfo->stObjOffset.usObjXoffset;
                usWinX = pstWinInfo->stAfbc_xy_sta.usX_sta;
                usWinY = pstWinInfo->stAfbc_xy_sta.usY_sta;
                usWinW = pstWinInfo->stAfbc_xy_pixel.usX_pic_pixel;
                usWinH = pstWinInfo->stAfbc_xy_pixel.usY_pic_pixel;
                usWinW_Back = pstWinInfo_Back->stAfbc_xy_pixel.usX_pic_pixel;
            }
#else
            ulSurfaceAddress = pstWinInfo->ulTop_addr;
            usWinX = pstWinInfo->stObjOffset.usObjXoffset;
            usWinY = pstWinInfo->stObjOffset.usObjYoffset;
            usWinW = pstWinInfo->stWinWH.usWidth;
            usWinH = pstWinInfo->stWinWH.usHeight;
            usWinW_Back = pstWinInfo_Back->stWinWH.usWidth;
#endif
            // get surface ID
            if(ScalerGosdGetSurfaceId(ulSurfaceAddress - sizeof(StructGosdSurfaceHeader), &(pstParam->ulSurfaceId)) == _FALSE)
            {
                ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
                return _FALSE;
            }
            pstParam->stWinRect.stPosition.usX = usWinX;
            pstParam->stWinRect.stPosition.usY = usWinY;
            pstParam->stWinRect.stSize.usH = usWinH;
            WORD usFrontInWidth = usWinW;
            WORD usBackInExt = (usFrontInWidth >= 4) ? (4) : (usFrontInWidth);
            WORD usBackInWidth = usWinW_Back;
            pstParam->stWinRect.stSize.usW = usFrontInWidth + usBackInWidth - usBackInExt;
            // get DispRect
            // [12:0]: size, [28:16]: position
            pstParam->stDispRect.stPosition.usX = (Scaler32GetDWord(PB00494_08_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF;
            pstParam->stDispRect.stPosition.usY = (Scaler32GetDWord(PB00494_0C_OSD_SR_1_V_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF;
            pstParam->stDispRect.stSize.usH = (Scaler32GetDWord(PB00494_0C_OSD_SR_1_V_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
            WORD usFrontOutWidth = (Scaler32GetDWord(PB00494_08_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
            WORD usBackOutWidth = (Scaler32GetDWord(PB10494_08_BACK_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
            WORD usBackOutX = (Scaler32GetDWord(PB10494_08_BACK_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF;
            WORD usBackOutExt = _GOSD_SR_EXTENSION - usBackOutX;
            pstParam->stDispRect.stSize.usW = usFrontOutWidth + usBackOutWidth - usBackOutExt;
        }
        // back only
        else if(Scaler32GetBit(PB104FF_20_BACK_OSD_STATUS, 1UL << (enumOsd << 1)) != 0)
        {
            // get WinRect
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
            if(pstWinInfo_Back->stAttr.b1IMGcompress == _FALSE)
            {
                ulSurfaceAddress = pstWinInfo_Back->ulTop_addr;
                usWinX = pstWinInfo_Back->stObjOffset.usObjXoffset;
                usWinY = pstWinInfo_Back->stObjOffset.usObjYoffset;
                usWinW = pstWinInfo_Back->stWinWH.usWidth;
                usWinH = pstWinInfo_Back->stWinWH.usHeight;
            }
            else
            {
                ulSurfaceAddress = ((DWORD)pstWinInfo_Back->stObjOffset.usObjYoffset << 16) + (DWORD)pstWinInfo_Back->stObjOffset.usObjXoffset;
                usWinX = pstWinInfo_Back->stAfbc_xy_sta.usX_sta;
                usWinY = pstWinInfo_Back->stAfbc_xy_sta.usY_sta;
                usWinW = pstWinInfo_Back->stAfbc_xy_pixel.usX_pic_pixel;
                usWinH = pstWinInfo_Back->stAfbc_xy_pixel.usY_pic_pixel;
            }
#else
            ulSurfaceAddress = pstWinInfo_Back->ulTop_addr;
            usWinX = pstWinInfo_Back->stObjOffset.usObjXoffset;
            usWinY = pstWinInfo_Back->stObjOffset.usObjYoffset;
            usWinW = pstWinInfo_Back->stWinWH.usWidth;
            usWinH = pstWinInfo_Back->stWinWH.usHeight;
#endif
            // get Surface ID
            if(ScalerGosdGetSurfaceId(ulSurfaceAddress - sizeof(StructGosdSurfaceHeader), &(pstParam->ulSurfaceId)) == _FALSE)
            {
                ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
                return _FALSE;
            }
            pstParam->stWinRect.stPosition.usX = usWinX;
            pstParam->stWinRect.stPosition.usY = usWinY;
            pstParam->stWinRect.stSize.usW = usWinW;
            pstParam->stWinRect.stSize.usH = usWinH;
            // get DispRect
            pstParam->stDispRect.stPosition.usX = ((Scaler32GetDWord(PB10494_08_BACK_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF) + (_PANEL_DH_WIDTH / 2) - _GOSD_SR_EXTENSION;
            pstParam->stDispRect.stPosition.usY = (Scaler32GetDWord(PB10494_0C_BACK_OSD_SR_1_V_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF;
            pstParam->stDispRect.stSize.usW = (Scaler32GetDWord(PB10494_08_BACK_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
            pstParam->stDispRect.stSize.usH = (Scaler32GetDWord(PB10494_0C_BACK_OSD_SR_1_V_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
        }
        // front only
        else if(Scaler32GetBit(PB004FF_20_OSD_STATUS, 1UL << (enumOsd << 1)) != 0)
        {
            // get WinRect
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
            if(pstWinInfo->stAttr.b1IMGcompress == _FALSE)
            {
                ulSurfaceAddress = pstWinInfo->ulTop_addr;
                usWinX = pstWinInfo->stObjOffset.usObjXoffset;
                usWinY = pstWinInfo->stObjOffset.usObjYoffset;
                usWinW = pstWinInfo->stWinWH.usWidth;
                usWinH = pstWinInfo->stWinWH.usHeight;
            }
            else
            {
                ulSurfaceAddress = ((DWORD)pstWinInfo->stObjOffset.usObjYoffset << 16) + (DWORD)pstWinInfo->stObjOffset.usObjXoffset;
                usWinX = pstWinInfo->stAfbc_xy_sta.usX_sta;
                usWinY = pstWinInfo->stAfbc_xy_sta.usY_sta;
                usWinW = pstWinInfo->stAfbc_xy_pixel.usX_pic_pixel;
                usWinH = pstWinInfo->stAfbc_xy_pixel.usY_pic_pixel;
            }
#else
            ulSurfaceAddress = pstWinInfo->ulTop_addr;
            usWinX = pstWinInfo->stObjOffset.usObjXoffset;
            usWinY = pstWinInfo->stObjOffset.usObjYoffset;
            usWinW = pstWinInfo->stWinWH.usWidth;
            usWinH = pstWinInfo->stWinWH.usHeight;
#endif
            // get Surface ID
            if(ScalerGosdGetSurfaceId(ulSurfaceAddress - sizeof(StructGosdSurfaceHeader), &(pstParam->ulSurfaceId)) == _FALSE)
            {
                ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
                return _FALSE;
            }
            pstParam->stWinRect.stPosition.usX = usWinX;
            pstParam->stWinRect.stPosition.usY = usWinY;
            pstParam->stWinRect.stSize.usW = usWinW;
            pstParam->stWinRect.stSize.usH = usWinH;
            // get DispRect
            pstParam->stDispRect.stPosition.usX = (Scaler32GetDWord(PB00494_08_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF;
            pstParam->stDispRect.stPosition.usY = (Scaler32GetDWord(PB00494_0C_OSD_SR_1_V_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF;
            pstParam->stDispRect.stSize.usW = (Scaler32GetDWord(PB00494_08_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
            pstParam->stDispRect.stSize.usH = (Scaler32GetDWord(PB00494_0C_OSD_SR_1_V_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
        }
        else
        {
            DebugMessageGOSD("GosdDispOsdGetOsdParam Error : osd is not displaying!!!", 0);
            DebugMessageGOSD("  osd=", enumOsd);
            ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
            return _FALSE;
        }

        ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
    }
    else // if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
#endif // #if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    {
        if(Scaler32GetBit(PB004FF_20_OSD_STATUS, 1UL << (enumOsd << 1)) != 0)
        {
            // get WinRect
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
            if(pstWinInfo->stAttr.b1IMGcompress == _FALSE)
            {
                ulSurfaceAddress = pstWinInfo->ulTop_addr;
                usWinX = pstWinInfo->stObjOffset.usObjXoffset;
                usWinY = pstWinInfo->stObjOffset.usObjYoffset;
                usWinW = pstWinInfo->stWinWH.usWidth;
                usWinH = pstWinInfo->stWinWH.usHeight;
            }
            else
            {
                ulSurfaceAddress = ((DWORD)pstWinInfo->stObjOffset.usObjYoffset << 16) + (DWORD)pstWinInfo->stObjOffset.usObjXoffset;
                usWinX = pstWinInfo->stAfbc_xy_sta.usX_sta;
                usWinY = pstWinInfo->stAfbc_xy_sta.usY_sta;
                usWinW = pstWinInfo->stAfbc_xy_pixel.usX_pic_pixel;
                usWinH = pstWinInfo->stAfbc_xy_pixel.usY_pic_pixel;
            }
#else
            ulSurfaceAddress = pstWinInfo->ulTop_addr;
            usWinX = pstWinInfo->stObjOffset.usObjXoffset;
            usWinY = pstWinInfo->stObjOffset.usObjYoffset;
            usWinW = pstWinInfo->stWinWH.usWidth;
            usWinH = pstWinInfo->stWinWH.usHeight;
#endif

            // get Surface ID
            if(ScalerGosdGetSurfaceId(ulSurfaceAddress - sizeof(StructGosdSurfaceHeader), &(pstParam->ulSurfaceId)) == _FALSE)
            {
                return _FALSE;
            }
            pstParam->stWinRect.stPosition.usX = usWinX;
            pstParam->stWinRect.stPosition.usY = usWinY;
            pstParam->stWinRect.stSize.usW = usWinW;
            pstParam->stWinRect.stSize.usH = usWinH;
            // get DispRect
            pstParam->stDispRect.stPosition.usX = (Scaler32GetDWord(PB00494_08_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF;
            pstParam->stDispRect.stPosition.usY = (Scaler32GetDWord(PB00494_0C_OSD_SR_1_V_LOCATION_CTRL + 0x80UL * enumOsd) >> 16) & 0x1FFF;
            pstParam->stDispRect.stSize.usW = (Scaler32GetDWord(PB00494_08_OSD_SR_1_H_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
            pstParam->stDispRect.stSize.usH = (Scaler32GetDWord(PB00494_0C_OSD_SR_1_V_LOCATION_CTRL + 0x80UL * enumOsd)) & 0x1FFF;
        }
        else
        {
            DebugMessageGOSD("GosdDispOsdGetOsdParam Error : osd is not displaying!!!", 0);
            DebugMessageGOSD("  osd=", enumOsd);
            return _FALSE;
        }
    }

    return _TRUE;
}


#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SR extension
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetSRExtension(void)
{
    ScalerGosdDispOsdFBSeperateEnable(_ENABLE);
    // front
    // osd_display_extension_sr_den_end
    Scaler32SetByte(PB0049D_E0_GOSD_TIMING_DELAY, 1, _GOSD_SR_EXTENSION);
    // osd_display_extension_sr_den_start
    Scaler32SetByte(PB0049D_E0_GOSD_TIMING_DELAY, 2, 0);
    // back
    // osd_display_extension_sr_den_end
    Scaler32SetByte(PB1049D_E0_BACK_GOSD_TIMING_DELAY, 1, 0);
    // osd_display_extension_sr_den_start
    Scaler32SetByte(PB1049D_E0_BACK_GOSD_TIMING_DELAY, 2, _GOSD_SR_EXTENSION);

    ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
}
#endif

#if((_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON) && (_GOSD_DISPLAY_BW_CTRL_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get BW Ctrl client info - GOSD_F1
// Input Value  : pstWinInfo : Pointer to client info
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdBwCtrlGetClientInfo(StructBwCtrlClientInfo *pstClientInfo, StructGosdGdmaWinInfo *pstWinInfo, EnumGosdDisplayOSD enumOSD, bit bBack)
{
    // B (request threshold) = (Total bit of 4 line * Compress Ratio + Total bits of header) / 4 line / 128
    // T (time threshold) = (B * 128 * MPLL_freq ) / ((Hactive / Htotal) * Pixel_rate * (Bit * Compress Ratio + Header bit))
    // Format |     Compress ratio   | header bit | Total bits of header
    // -------------------------     -----------------------------------------
    // RGB    |       0              |      0     |    0
    // AFBC   | ratio (must > 0.5)   |      1     |    width * bit / 32 * 128
    DWORD ulLineSumBit = 0;
    BYTE code ucTimeThdPercent = 90; // margin 10%
    BYTE code ucLenModeLimit = 32;
    BYTE ucBit = ScalerGosdDispOsdGetBitPerPixel(pstWinInfo->stAttr.b5Type);
    DWORD ulDenominator = 0; // ((Hactive / Htotal) * Pixel_rate * (Bit * Compress Ratio + Header bit))
    DWORD ulBackOffset = 0;
    BYTE ucMaxBurstLen = 0xFC;

    pstClientInfo = pstClientInfo;
    bBack = bBack;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        if(bBack == _TRUE)
        {
            ulBackOffset = 0x0100000;
        }
    }
#endif
    ucMaxBurstLen = MINOF(Scaler32GetByte(PB004F9_24_DMA_BL_2 + ulBackOffset, enumOSD + 1),
                          Scaler32GetByte(PB0049D_F4_GOSD_DBUS_MAX_BL_OSD1 + ulBackOffset, enumOSD)) * 2;

    pstClientInfo->bEnable = _TRUE;
    ulLineSumBit = (DWORD)(pstWinInfo->stWinWH.usWidth * ucBit);
    ulDenominator = ScalerGlobalComputeDwordMulDiv(ulLineSumBit, GET_D_CLK_FREQ(), ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL)) / 1000;

    if(pstWinInfo->stWinWH.usWidth >= ucLenModeLimit)
    {
        pstClientInfo->enumMode = _BW_CTRL_LEN_MODE;
        pstClientInfo->ulReqThd = 4 * ulLineSumBit;
        pstClientInfo->ulReqThd = CEILING_OF_INT_DIVISION(pstClientInfo->ulReqThd, 512);
        pstClientInfo->ulTimeThd = (pstClientInfo->ulReqThd * 128 * _MEMORY_PLL_CLOCK) / ulDenominator;
        pstClientInfo->ulTimeThd = (DWORD)(pstClientInfo->ulTimeThd * ucTimeThdPercent) / 100;
        pstClientInfo->ulReqThd = CEILING(pstClientInfo->ulReqThd, 16);
    }
    else
    {
        DWORD ulLineTotalLen = 0;
        WORD usLineRWNum = 0;

        pstClientInfo->enumMode = _BW_CTRL_REQ_MODE;
        pstClientInfo->ulReqThd = 0x01U;
        ulLineTotalLen = CEILING_OF_INT_DIVISION(ulLineSumBit, 64);
        usLineRWNum = LOWORD(ScalerMemoryCalculateNumberAndRemain(ulLineTotalLen, ucMaxBurstLen, 1));
        pstClientInfo->ulTimeThd = ScalerGlobalComputeDwordMulDiv(((DWORD)ulLineTotalLen * 64 * _MEMORY_PLL_CLOCK), ucTimeThdPercent, ulDenominator) / (usLineRWNum + 1) / 100;
    }
    DebugMessageGOSD("GosdDisp BW Ctrl _BW_CTRL_LEN_MODE", pstClientInfo->enumMode);
    DebugMessageGOSD("GosdDisp BW Ctrl usX_pic_pixel", pstWinInfo->stWinWH.usWidth);
    DebugMessageGOSD("GosdDisp BW Ctrl ulDenominator", ulDenominator);
    DebugMessageGOSD("GosdDisp BW Ctrl ulReqThd", pstClientInfo->ulReqThd);
    DebugMessageGOSD("GosdDisp BW Ctrl ulTimeThd", pstClientInfo->ulTimeThd);
}
#endif
#endif // end of #if(_IS_MAIN_PROCESS_CPU == _FALSE)

//--------------------------------------------------
// Description  : Set front_back_separate_en enable/disable
// Input Value  : bEn
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdFBSeperateEnable(bit bEn)
{
    bEn = bEn;
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    Scaler32SetBit(PB0049F_00_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, (((DWORD)bEn) << 7));
#endif
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set extension
// Input Value  : void
// Output Value :
//--------------------------------------------------
void ScalerGosdDispOsdSetExtension(BYTE ucExtension)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerGosdDispOsdFBSeperateEnable(_ENABLE);
        Scaler32SetByte(PB0049D_DC_GOSD_TIMING_RESERVED_DC, 1, 0);
        Scaler32SetByte(PB1049D_DC_BACK_GOSD_TIMING_RESERVED_DC, 1, ucExtension);
        ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
    }
    else
    {
        Scaler32SetByte(PB0049D_DC_GOSD_TIMING_RESERVED_DC, 1, 0);
    }
}
#endif

//--------------------------------------------------
// Description  : Set DispOsd timing gen. enable/disable
// Input Value  : bEn
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetTimingGenEn(bit bEn)
{
    Scaler32SetBit(PB0049D_D0_GOSD_TIMING_GEN_CTRL, ~_BIT7, (bEn == _ENABLE) ? (_BIT7) : (0x00));
}

//--------------------------------------------------
// Description  : Get Gosd Displaying status
// Input Value  : enumOsd
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdDispOsdGetDisplaying(EnumGosdDisplayOSD enumOsd)
{
    bit bReturn = _FALSE;

    switch(enumOsd)
    {
        case _GOSD_PLANE_OSD1:
            bReturn = (Scaler32GetBit(PB004F2_00_OSD1_CTRL, _BIT1) == (_BIT1));
            break;
        case _GOSD_PLANE_OSD2:
            bReturn = (Scaler32GetBit(PB004F3_00_OSD2_CTRL, _BIT1) == (_BIT1));
            break;
        case _GOSD_PLANE_OSD3:
            bReturn = (Scaler32GetBit(PB004F4_00_OSD3_CTRL, _BIT1) == (_BIT1));
            break;
        case _GOSD_PLANE_ALL:
            bReturn = ((Scaler32GetBit(PB004F2_00_OSD1_CTRL, _BIT1) == (_BIT1)) ||
                       (Scaler32GetBit(PB004F3_00_OSD2_CTRL, _BIT1) == (_BIT1)) ||
                       (Scaler32GetBit(PB004F4_00_OSD3_CTRL, _BIT1) == (_BIT1)));
            break;
        default:
            break;
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerGosdDispOsdFBSeperateEnable(_ENABLE);
        switch(enumOsd)
        {
            case _GOSD_PLANE_OSD1:
                bReturn |= (Scaler32GetBit(PB104F2_00_BACK_OSD1_CTRL, _BIT1) == (_BIT1));
                break;
            case _GOSD_PLANE_OSD2:
                bReturn |= (Scaler32GetBit(PB104F3_00_BACK_OSD2_CTRL, _BIT1) == (_BIT1));
                break;
            case _GOSD_PLANE_OSD3:
                bReturn |= (Scaler32GetBit(PB104F4_00_BACK_OSD3_CTRL, _BIT1) == (_BIT1));
                break;
            case _GOSD_PLANE_ALL:
                bReturn |= ((Scaler32GetBit(PB104F2_00_BACK_OSD1_CTRL, _BIT1) == (_BIT1)) ||
                            (Scaler32GetBit(PB104F3_00_BACK_OSD2_CTRL, _BIT1) == (_BIT1)) ||
                            (Scaler32GetBit(PB104F4_00_BACK_OSD3_CTRL, _BIT1) == (_BIT1)));
                break;
            default:
                break;
        }
        ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
    }
#endif

    return bReturn;
}

//--------------------------------------------------
// Description  : GDMA Get FontOsd, Gosd status
// Input Value  : None
// Output Value : ucOsdStatus : _BIT0: Osd status, _BIT1: Gosd_Osd1 status, _BIT2: Gosd_Osd2 status, _BIT3: Gosd_Osd3 status
//                              _BIT4: Gosd_Osd1_Back status, _BIT5: Gosd_Osd2_Back status, _BIT6: Gosd_Osd3_Back status
//--------------------------------------------------
BYTE ScalerGosdDispOsdGetOsdStatus(void)
{
    BYTE ucOsdStatus = 0;

    // record Osd enabled
    ucOsdStatus |= (ScalerGetBit(P80_A0_OVERLAY_CTRL, _BIT0) == _BIT0) ? (_BIT0) : (0);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerGosdDispOsdFBSeperateEnable(_ENABLE);
        // record Gosd each plane enabled
        ucOsdStatus |= (Scaler32GetBit(PB004F2_00_OSD1_CTRL, _BIT1) == _BIT1) ? (_BIT1) : (0);
        ucOsdStatus |= (Scaler32GetBit(PB004F3_00_OSD2_CTRL, _BIT1) == _BIT1) ? (_BIT2) : (0);
        ucOsdStatus |= (Scaler32GetBit(PB004F4_00_OSD3_CTRL, _BIT1) == _BIT1) ? (_BIT3) : (0);
        // record Gosd each back plane enabled
        ucOsdStatus |= (Scaler32GetBit(PB104F2_00_BACK_OSD1_CTRL, _BIT1) == _BIT1) ? (_BIT4) : (0);
        ucOsdStatus |= (Scaler32GetBit(PB104F3_00_BACK_OSD2_CTRL, _BIT1) == _BIT1) ? (_BIT5) : (0);
        ucOsdStatus |= (Scaler32GetBit(PB104F4_00_BACK_OSD3_CTRL, _BIT1) == _BIT1) ? (_BIT6) : (0);
        ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
    }
    else
#endif
    {
        // record Gosd each plane enabled
        ucOsdStatus |= (Scaler32GetBit(PB004F2_00_OSD1_CTRL, _BIT1) == _BIT1) ? (_BIT1) : (0);
        ucOsdStatus |= (Scaler32GetBit(PB004F3_00_OSD2_CTRL, _BIT1) == _BIT1) ? (_BIT2) : (0);
        ucOsdStatus |= (Scaler32GetBit(PB004F4_00_OSD3_CTRL, _BIT1) == _BIT1) ? (_BIT3) : (0);
    }

    return ucOsdStatus;
}

//--------------------------------------------------
// Description  : GDMA clock control pre process
// Input Value  : None
// Output Value : ucOsdStatus : _BIT0: Osd status, _BIT1: Gosd_Osd1 status, _BIT2: Gosd_Osd2 status, _BIT3: Gosd_Osd3 status
//                              _BIT4: Gosd_Osd1_Back status, _BIT5: Gosd_Osd2_Back status, _BIT6: Gosd_Osd3_Back status
//--------------------------------------------------
BYTE ScalerGosdDispOsdClkSelectPreProc(void)
{
    // Pause Gosd continuous step when disposd clk select
    g_bGosdContinuousGlobalPause = _TRUE;

    BYTE ucOsdStatus = ScalerGosdDispOsdGetOsdStatus();

    // check Gosd enabled
    if((ucOsdStatus & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1)) != 0)
    {
#if(_GOSD_OSD_LINK_DISABLE_IN_DCLK_CHANGING == _OFF)
        // OSD Disable
        ScalerOsdDisableOsd();
#endif
        // Gosd disposd Disable
        ScalerGosdDispOsdSetGdmaOsdDisable(_GOSD_PLANE_ALL, _DB_APPLY_POLLING);
        // Gosd disposd timing gen Disable
        ScalerGosdDispOsdSetTimingGenEn(_DISABLE);
    }

    return ucOsdStatus;
}

//--------------------------------------------------
// Description  : GDMA clock control post process
// Input Value  : ucOsdStatus : _BIT0: Osd status, _BIT1: Gosd_Osd1 status, _BIT2: Gosd_Osd2 status, _BIT3: Gosd_Osd3 status
//                              _BIT4: Gosd_Osd1_Back status, _BIT5: Gosd_Osd2_Back status, _BIT6: Gosd_Osd3_Back status
//                bGosdClkSelect: select Gosd clk
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdClkSelectPostProc(BYTE ucOsdStatus, bit bGosdClkSelect)
{
    if(bGosdClkSelect == _TRUE)
    {
        // Disposd clk select
        ScalerGosdDispOsdClkSelect();
    }

    // check Gosd enabled
    if((ucOsdStatus & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1)) != 0)
    {
        // Gosd disposd timing gen Enable
        ScalerGosdDispOsdSetTimingGenEn(_ENABLE);
        // Gosd disposd Enable
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            DWORD ulFBOffset = 0;
            ScalerGosdDispOsdFBSeperateEnable(_ENABLE);

            for(BYTE ucFBIdx = 0; ucFBIdx < 2; ucFBIdx++)
            {
                for(BYTE ucOsdIdx = 0; ucOsdIdx < 3; ucOsdIdx++)
                {
                    // _BIT1 ~ _BIT3: front, _BIT4 ~ _BIT6: back
                    if((ucOsdStatus & (1 << (ucOsdIdx + (ucFBIdx * 3) + 1))) != 0)
                    {
                        Scaler32SetBit(PB004F2_00_OSD1_CTRL + ulFBOffset + GET_GOSD_GDMA_OSD_REG_OFFSET(ucOsdIdx), ~(_BIT1), _BIT1);
                        ScalerGosdSetSurfaceStatus(g_pulGosdDispOsdDisplayingSurfaceId[ucOsdIdx], _GOSD_SURFACE_DISPOSD_SHOWING);
                    }
                }
                ulFBOffset += GET_GOSD_GDMA_OSD_REG_FB_OFFSET();
            }

            ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
        }
        else
#endif
        {
            for(BYTE ucOsdIdx = 0; ucOsdIdx < 3; ucOsdIdx++)
            {
                // _BIT1 ~ _BIT3
                if((ucOsdStatus & (1 << (ucOsdIdx + 1))) != 0)
                {
                    Scaler32SetBit(PB004F2_00_OSD1_CTRL + GET_GOSD_GDMA_OSD_REG_OFFSET(ucOsdIdx), ~(_BIT1), _BIT1);
                    ScalerGosdSetSurfaceStatus(g_pulGosdDispOsdDisplayingSurfaceId[ucOsdIdx], _GOSD_SURFACE_DISPOSD_SHOWING);
                }
            }
        }

        // DB apply
        ScalerGosdDispOsdSetDisplayDBApply(_DB_APPLY_POLLING);

#if(_GOSD_OSD_LINK_DISABLE_IN_DCLK_CHANGING == _OFF)
        // OSD Enable
        if((ucOsdStatus & _BIT0) == _BIT0)
        {
            ScalerOsdEnableOsd();
        }
#endif
    }

    // Resume Gosd continuous step
    g_bGosdContinuousGlobalPause = _FALSE;
}

//--------------------------------------------------
// Description  : GDMA clock control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdClkSelect(void)
{
    // clk_osd_sel -> 00: from dclk, 01 : from mclk, 10 : from mpll output, 11 : reserved
    // OSD clock should be meet osd clock >= dclk & osd clock >= mclk /2
    DWORD ulDclk = GET_D_CLK_FREQ() - GET_CLOCK_SPREAD(GET_D_CLK_FREQ(), _DCLK_SPREAD_RANGE_MAX);
    if((ulDclk >> (GET_D_DOMAIN_PATH())) < (((DWORD)(1000 * _MEMORY_PLL_CLOCK) / 2) + 10))
    {
        // clk_osd from mclk
        ScalerSetBit(P80_DE_GOSD_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
    }
    else
    {
        // clk_osd from dclk
        ScalerSetBit(P80_DE_GOSD_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Gosd DisplayOsd prog done apply
// Input Value  : enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetDisplayDBApply(EnumDBApply enumDBApply)
{
    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }

    // set prog_done = 1
    Scaler32SetBit(PB004FF_04_CTRL, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2 | _BIT1));

    if(enumDBApply == _DB_APPLY_POLLING)
    {
        if(Scaler32GetBit(PB004FF_00_UPDATE, _BIT1) == 0x00)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        }
        else
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        }
    }
}

//--------------------------------------------------
// Description  : Set gdma DB apply
// Input Value  : enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetGdmaDBApply(EnumDBApply enumDBApply)
{
    bit bCleanCache = _FALSE;

    bCleanCache = ((Scaler32GetBit(PB004F2_00_OSD1_CTRL, _BIT1) == _BIT1) ||
                   (Scaler32GetBit(PB004F3_00_OSD2_CTRL, _BIT1) == _BIT1) ||
                   (Scaler32GetBit(PB004F4_00_OSD3_CTRL, _BIT1) == _BIT1));

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerGosdDispOsdFBSeperateEnable(_ENABLE);
        bCleanCache |= ((Scaler32GetBit(PB104F2_00_BACK_OSD1_CTRL, _BIT1) == _BIT1) ||
                        (Scaler32GetBit(PB104F3_00_BACK_OSD2_CTRL, _BIT1) == _BIT1) ||
                        (Scaler32GetBit(PB104F4_00_BACK_OSD3_CTRL, _BIT1) == _BIT1));
        ScalerGosdDispOsdFBSeperateEnable(_DISABLE);
    }
#endif

    if(bCleanCache == _TRUE)
    {
        ScalerCpuHalCleanDataCache();
    }

    ScalerGosdDispOsdSetDisplayDBApply(enumDBApply);
}

//--------------------------------------------------
// Description  : Set gdma DB event
// Input Value  : enumDBEvent
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetGdmaSetDBTriggerEvent(EnumGosdGdmaDBTriggerEvent enumDBEvent)
{
    Scaler32SetBit(PB004FF_00_UPDATE, ~_BIT1, (enumDBEvent == _DB_TRIGGER_EVENT_DVS) ? (0x00) : (_BIT1));
}

//--------------------------------------------------
// Description  : Set Clear Region
// Input Value  : enumOSD
//                stClear_x
//                stClear_y
//                ucClearEnable
//                enumDBApply
// Output Value : None
//--------------------------------------------------
EnumGosdGdmaStatus ScalerGosdDispOsdSetGdmaClearRegion(EnumGosdDisplayOSD enumOSD, StructGosdGdmaClearX stClear_x, StructGosdGdmaClearY stClear_y, bit bClearEnable, EnumDBApply enumDBApply)
{
    WORD usOffset = GET_GOSD_GDMA_OSD_REG_OFFSET(enumOSD);
    DWORD ulTemp = 0;
    WORD usWidth = 0;
    WORD usHeight = 0;

    // Get canvas width, height
    ulTemp = Scaler32GetDWord(PB004F2_18_OSD1_SIZE + usOffset);
    usWidth = ((ulTemp >> 16) & 0x1FFF);
    usHeight = (ulTemp & 0x1FFF);

    if((usWidth < (stClear_x.b13X_end - stClear_x.b13X_sta)) ||
       (usHeight < (stClear_y.b13Y_end - stClear_y.b13Y_sta)))
    {
        DebugMessageGOSD("Error: Clear region > canvas, usWidth:", usWidth);
        DebugMessageGOSD("Error: Clear region > canvas, usHeight:", usHeight);
        return _GDMA_FAIL;
    }

    // Set clear region
    Scaler32SetDWord((PB004F2_80_OSD1_CLEAR1 + usOffset), ((DWORD)stClear_x.b13X_sta << 16) | ((DWORD)stClear_x.b13X_end & 0xFFFF));
    Scaler32SetDWord((PB004F2_84_OSD1_CLEAR2 + usOffset), ((DWORD)stClear_y.b13Y_sta << 16) | ((DWORD)stClear_y.b13Y_end & 0xFFFF));
    // Clear region enable/disable
    Scaler32SetBit((PB004F2_04_OSD1 + usOffset), ~_BIT1, (bClearEnable == _ENABLE) ? _BIT1 : 0x00);
    // DB apply
    ScalerGosdDispOsdSetGdmaDBApply(enumDBApply);

    return _GDMA_SUCCESS;
}

//--------------------------------------------------
// Description  : Set OSD Disable
// Input Value  : enumOSD
//                enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetGdmaOsdDisable(EnumGosdDisplayOSD enumOSD, EnumDBApply enumDBApply)
{
    DWORD ulOffset = 0;
    BYTE ucOsdCnt = 0;
    EnumGosdDisplayOSD enumOsd = _GOSD_PLANE_OSD1;

    ucOsdCnt = (enumOSD == _GOSD_PLANE_ALL) ? (_GOSD_PLANE_MAXNUM) : (1);
    enumOsd = (enumOSD == _GOSD_PLANE_ALL) ? (_GOSD_PLANE_OSD1) : (enumOSD);

    for(BYTE ucIdx = 0; ucIdx < ucOsdCnt; ucIdx++)
    {
        // Get osd register offset
        ulOffset = GET_GOSD_GDMA_OSD_REG_OFFSET(enumOsd);

        // Set Gdma disable
        Scaler32SetBit((PB004F2_00_OSD1_CTRL + ulOffset), ~_BIT1, 0);

        // Set surface status
        ScalerGosdSetSurfaceStatus(g_pulGosdDispOsdDisplayingSurfaceId[enumOsd], _GOSD_SURFACE_IDLE);

        enumOsd += 1;
    }

    // DB apply
    ScalerGosdDispOsdSetGdmaDBApply(enumDBApply);
}

//--------------------------------------------------
// Description  : Set mxer DB apply
// Input Value  : enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetMixerDBApply(EnumDBApply enumDBApply)
{
    if((enumDBApply == _DB_APPLY_NONE) || (Scaler32GetBit(PB004B0_A0_OSD_DB_CTRL, _BIT1) == 0x00))
    {
        return;
    }

    Scaler32SetBit(PB004B0_A0_OSD_DB_CTRL, ~_BIT0, _BIT0);

    if(enumDBApply == _DB_APPLY_POLLING)
    {
        ScalerTimerPollingFlagProc32Bit(_GOSD_BUFFER_WAIT_TIME, PB004B0_A0_OSD_DB_CTRL, _BIT0, 0);
    }
}

//--------------------------------------------------
// Description  : Set OSDx Mixer enable
// Input Value  : enumOSD
//                bEnable
//                enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetMixerOSDEnable(EnumGosdDisplayOSD enumOSD, bit bEnable, EnumDBApply enumDBApply)
{
    switch(enumOSD)
    {
        case _GOSD_PLANE_OSD1:
            Scaler32SetBit(PB004B0_00_MIXER_CTRL2, ~_BIT1, (DWORD)bEnable << 1);
            break;
        case _GOSD_PLANE_OSD2:
            Scaler32SetBit(PB004B0_00_MIXER_CTRL2, ~_BIT2, (DWORD)bEnable << 2);
            break;
        case _GOSD_PLANE_OSD3:
            Scaler32SetBit(PB004B0_00_MIXER_CTRL2, ~_BIT3, (DWORD)bEnable << 3);
            break;
        case _GOSD_PLANE_ALL:
            Scaler32SetBit(PB004B0_00_MIXER_CTRL2, ~(_BIT3 | _BIT2 | _BIT1), (bEnable == _ENABLE) ? (_BIT3 | _BIT2 | _BIT1) : (0x00));
            break;
        default:
            break;
    }

    // Check DB status
    ScalerGosdDispOsdSetMixerDBApply(enumDBApply);
}

//--------------------------------------------------
// Description  : Set Mixer Plane Alpha, Offset
// Input Value  : enumMixerOrder
//                stARGB
//                ucPlaneAlphaEnable
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetMixerPlaneAlpha(EnumGosdMixerOrder enumMixerOrder, StructGosdMixerPlaneAlpha_ARGB stAlphaARGB, StructGosdMixerPlaneOffset_ARGB stOffsetARGB, BYTE ucPlaneAlphaEnable, EnumDBApply enumDBApply)
{
    switch(enumMixerOrder)
    {
        default:
        case _GOSD_C0:
            Scaler32SetDWord(PB004B0_08_MIXER_C0_PLANE_ALPHA1, ((DWORD)stAlphaARGB.b9PlaneAlphaA << 16) | stAlphaARGB.b9PlaneAlphaR);
            Scaler32SetDWord(PB004B0_0C_MIXER_C0_PLANE_ALPHA2, ((DWORD)stAlphaARGB.b9PlaneAlphaG << 16) | stAlphaARGB.b9PlaneAlphaB);
            Scaler32SetDWord(PB004B0_10_MIXER_C0_PLANE_OFFSET, TO_DWORD(stOffsetARGB.ucPlaneOffsetA, stOffsetARGB.ucPlaneOffsetR, stOffsetARGB.ucPlaneOffsetG, stOffsetARGB.ucPlaneOffsetB));
            // Set c0_plane_alpha_en
            Scaler32SetBit(PB004B0_04_MIXER_LAYER_SEL, ~_BIT24, ((ucPlaneAlphaEnable == _ENABLE) ? (_BIT24) : (0x00)));
            break;

        case _GOSD_C1:
            Scaler32SetDWord(PB004B0_14_MIXER_C1_PLANE_ALPHA1, ((DWORD)stAlphaARGB.b9PlaneAlphaA << 16) | stAlphaARGB.b9PlaneAlphaR);
            Scaler32SetDWord(PB004B0_18_MIXER_C1_PLANE_ALPHA2, ((DWORD)stAlphaARGB.b9PlaneAlphaG << 16) | stAlphaARGB.b9PlaneAlphaB);
            Scaler32SetDWord(PB004B0_1C_MIXER_C1_PLANE_OFFSET, TO_DWORD(stOffsetARGB.ucPlaneOffsetA, stOffsetARGB.ucPlaneOffsetR, stOffsetARGB.ucPlaneOffsetG, stOffsetARGB.ucPlaneOffsetB));
            // Set c1_plane_alpha_en
            Scaler32SetBit(PB004B0_04_MIXER_LAYER_SEL, ~_BIT25, ((ucPlaneAlphaEnable == _ENABLE) ? (_BIT25) : (0x00)));
            break;

        case _GOSD_C2:
            Scaler32SetDWord(PB004B0_20_MIXER_C2_PLANE_ALPHA1, ((DWORD)stAlphaARGB.b9PlaneAlphaA << 16) | stAlphaARGB.b9PlaneAlphaR);
            Scaler32SetDWord(PB004B0_24_MIXER_C2_PLANE_ALPHA2, ((DWORD)stAlphaARGB.b9PlaneAlphaG << 16) | stAlphaARGB.b9PlaneAlphaB);
            Scaler32SetDWord(PB004B0_28_MIXER_C2_PLANE_OFFSET, TO_DWORD(stOffsetARGB.ucPlaneOffsetA, stOffsetARGB.ucPlaneOffsetR, stOffsetARGB.ucPlaneOffsetG, stOffsetARGB.ucPlaneOffsetB));
            // Set c2_plane_alpha_en
            Scaler32SetBit(PB004B0_04_MIXER_LAYER_SEL, ~_BIT26, ((ucPlaneAlphaEnable == _ENABLE) ? (_BIT26) : (0x00)));
            break;

        case _GOSD_C3:
            Scaler32SetDWord(PB004B0_2C_MIXER_C3_PLANE_ALPHA1, ((DWORD)stAlphaARGB.b9PlaneAlphaA << 16) | stAlphaARGB.b9PlaneAlphaR);
            Scaler32SetDWord(PB004B0_30_MIXER_C3_PLANE_ALPHA2, ((DWORD)stAlphaARGB.b9PlaneAlphaG << 16) | stAlphaARGB.b9PlaneAlphaB);
            Scaler32SetDWord(PB004B0_34_MIXER_C3_PLANE_OFFSET, TO_DWORD(stOffsetARGB.ucPlaneOffsetA, stOffsetARGB.ucPlaneOffsetR, stOffsetARGB.ucPlaneOffsetG, stOffsetARGB.ucPlaneOffsetB));
            // Set c3_plane_alpha_en
            Scaler32SetBit(PB004B0_04_MIXER_LAYER_SEL, ~_BIT27, ((ucPlaneAlphaEnable == _ENABLE) ? (_BIT27) : (0x00)));
            break;
    }

    // check DB status
    ScalerGosdDispOsdSetMixerDBApply(enumDBApply);
}

//--------------------------------------------------
// Description  : Set Mixer Layer Select
// Input Value  : enumOSD: Osd1, Osd2, Osd3
//                enumMixerOrder: C0, C1, C2
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetMixerLayer(EnumGosdDisplayOSD enumOSD, EnumGosdMixerOrder enumMixerOrder, EnumDBApply enumDBApply)
{
    StructGosdMixerLayerSel stCurrentMixerLayer;
    BYTE ucCx_sel_old = 0;
    BYTE ucCx_sel_new = 0;
    DWORD ulTemp = 0;

    ulTemp = Scaler32GetDWord(PB004B0_04_MIXER_LAYER_SEL);
    stCurrentMixerLayer.b2C0_sel = (ulTemp & (_BIT1 | _BIT0));
    stCurrentMixerLayer.b2C1_sel = ((ulTemp & (_BIT5 | _BIT4)) >> 4);
    stCurrentMixerLayer.b2C2_sel = ((ulTemp & (_BIT9 | _BIT8)) >> 8);
    stCurrentMixerLayer.b2C3_sel = ((ulTemp & (_BIT13 | _BIT12)) >> 12);
    switch(enumMixerOrder)
    {
        default:
        case _GOSD_C0:
            ucCx_sel_old = stCurrentMixerLayer.b2C0_sel;
            stCurrentMixerLayer.b2C0_sel = enumOSD + 1;
            ucCx_sel_new = stCurrentMixerLayer.b2C0_sel;
            break;
        case _GOSD_C1:
            ucCx_sel_old = stCurrentMixerLayer.b2C1_sel;
            stCurrentMixerLayer.b2C1_sel = enumOSD + 1;
            ucCx_sel_new = stCurrentMixerLayer.b2C1_sel;
            break;
        case _GOSD_C2:
            ucCx_sel_old = stCurrentMixerLayer.b2C2_sel;
            stCurrentMixerLayer.b2C2_sel = enumOSD + 1;
            ucCx_sel_new = stCurrentMixerLayer.b2C2_sel;
            break;
        case _GOSD_C3:
            ucCx_sel_old = stCurrentMixerLayer.b2C3_sel;
            stCurrentMixerLayer.b2C3_sel = enumOSD + 1;
            ucCx_sel_new = stCurrentMixerLayer.b2C3_sel;
            break;
    }

    // Conflict protect
    if((stCurrentMixerLayer.b2C0_sel == ucCx_sel_new) && (enumMixerOrder != _GOSD_C0))
    {
        stCurrentMixerLayer.b2C0_sel = ucCx_sel_old;
    }
    else if((stCurrentMixerLayer.b2C1_sel == ucCx_sel_new) && (enumMixerOrder != _GOSD_C1))
    {
        stCurrentMixerLayer.b2C1_sel = ucCx_sel_old;
    }
    else if((stCurrentMixerLayer.b2C2_sel == ucCx_sel_new) && (enumMixerOrder != _GOSD_C2))
    {
        stCurrentMixerLayer.b2C2_sel = ucCx_sel_old;
    }
    else if((stCurrentMixerLayer.b2C3_sel == ucCx_sel_new) && (enumMixerOrder != _GOSD_C3))
    {
        stCurrentMixerLayer.b2C3_sel = ucCx_sel_old;
    }
    ulTemp = Scaler32GetDWord(PB004B0_04_MIXER_LAYER_SEL);
    ulTemp = (ulTemp & ~(_BIT13 | _BIT12 | _BIT9 | _BIT8 | _BIT5 | _BIT4 | _BIT1 | _BIT0)) |
             ((DWORD)stCurrentMixerLayer.b2C3_sel << 12) |
             ((DWORD)stCurrentMixerLayer.b2C2_sel << 8) |
             ((DWORD)stCurrentMixerLayer.b2C1_sel << 4) |
             ((DWORD)stCurrentMixerLayer.b2C0_sel);
    Scaler32SetDWord(PB004B0_04_MIXER_LAYER_SEL, ulTemp);

    // Check DB status
    ScalerGosdDispOsdSetMixerDBApply(enumDBApply);
}

//--------------------------------------------------
// Description  : Set Mixer Blend
// Input Value  : pstMixer
//                enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerGosdDispOsdSetMixerFactor(StructGosdMixerLayerSetting *pstMixer, EnumDBApply enumDBApply)
{
    DWORD ulValue = TO_DWORD(pstMixer->stFactor.b6K1, pstMixer->stFactor.b6K2, pstMixer->stFactor.b6K3, pstMixer->stFactor.b6K4);

    switch(pstMixer->enumLayerSel)
    {
        case _GOSD_B0:
            Scaler32SetDWord(PB004B0_64_MIXER_B1, ulValue);
            break;
        case _GOSD_B1:
            Scaler32SetDWord(PB004B0_68_MIXER_B2, ulValue);
            break;
        case _GOSD_B2:
            Scaler32SetDWord(PB004B0_6C_MIXER_B3, ulValue);
            break;
        default:
            return;
    }

    // Check DB status
    ScalerGosdDispOsdSetMixerDBApply(enumDBApply);
}
#endif // #if(_GOSD_SUPPORT == _ON)

