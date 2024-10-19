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
// ID Code      : ScalerTcon.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TCON__

#include "ScalerFunctionInclude.h"
#include "Tcon/ScalerTcon.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTconStatus g_stTconStatus;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PWM_RST_SIGNAL_SEL == _TCON)
//--------------------------------------------------
// Description  : PWM reset by TCON,adjust TCON
// Input Value  : usVstart --> TCON phase shift
// Output Value : None
//--------------------------------------------------
void ScalerTconAdjust(BYTE ucArea)
{
    WORD usVstart = 0;

    usVstart = (WORD)(((DWORD)(ucArea) * (DWORD)(GET_INPUT_TIMING_VTOTAL() - 100)) / 100);

    ScalerTcon8Adjust(0x0000, 0x3FFF, usVstart, (usVstart + 0x02)); // 0x02 indicate Tcon pulse width equal to 2 lines
}
#endif

//--------------------------------------------------
// Description  : Set Tcon0 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon0Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon0 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon0Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_10_TC0_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_11_TC0_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_12_TC0_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_13_TC0_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_14_TC0_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_15_TC0_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_16_TC0_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_17_TC0_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon0 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon0InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon1 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon1Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_28_TC1_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon1 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon1Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_20_TC1_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_21_TC1_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_22_TC1_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_23_TC1_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_24_TC1_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_25_TC1_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_26_TC1_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_27_TC1_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon1 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon1InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_28_TC1_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon2 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon2Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_38_TC2_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon2 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon2Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_30_TC2_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_31_TC2_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_32_TC2_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_33_TC2_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_34_TC2_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_35_TC2_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_36_TC2_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_37_TC2_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon2 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon2InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_38_TC2_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon3 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon3Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_48_TC3_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon3 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon3Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_40_TC3_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_41_TC3_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_42_TC3_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_43_TC3_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_44_TC3_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_45_TC3_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_46_TC3_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_47_TC3_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon3 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon3InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_48_TC3_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon4 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon4Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_58_TC4_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon4 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon4Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_50_TC4_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_51_TC4_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_52_TC4_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_53_TC4_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_54_TC4_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_55_TC4_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_56_TC4_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_57_TC4_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon4 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon4InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_58_TC4_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon5 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon5Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_68_TC5_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon5 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon5Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_60_TC5_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_61_TC5_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_62_TC5_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_63_TC5_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_64_TC5_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_65_TC5_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_66_TC5_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_67_TC5_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon5 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon5InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_68_TC5_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon6 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon6Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_78_TC6_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon6 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon6Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_70_TC6_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_71_TC6_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_72_TC6_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_73_TC6_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_74_TC6_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_75_TC6_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_76_TC6_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_77_TC6_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon6 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon6InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_78_TC6_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon7 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon7Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_88_TC7_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon7 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon7Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_80_TC7_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_81_TC7_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_82_TC7_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_83_TC7_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_84_TC7_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_85_TC7_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_86_TC7_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_87_TC7_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon7 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon7InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_88_TC7_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon8 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon8Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_98_TC8_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon8 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon8Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_90_TC8_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_91_TC8_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_92_TC8_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_93_TC8_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_94_TC8_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_95_TC8_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_96_TC8_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_97_TC8_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon8 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon8InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_98_TC8_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon9 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon9Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_A8_TC9_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon9 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon9Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_A0_TC9_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_A1_TC9_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_A2_TC9_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_A3_TC9_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_A4_TC9_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_A5_TC9_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_A6_TC9_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_A7_TC9_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon9 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon9InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_A8_TC9_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}


//--------------------------------------------------
// Description  : Set Tcon10 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon10Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_B8_TC10_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon10 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon10Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_B0_TC10_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_B1_TC10_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_B2_TC10_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_B3_TC10_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_B4_TC10_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_B5_TC10_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_B6_TC10_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_B7_TC10_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon10 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon10InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_B8_TC10_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon11 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon11Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_C8_TC11_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon11 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon11Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_C0_TC11_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_C1_TC11_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_C2_TC11_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_C3_TC11_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_C4_TC11_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_C5_TC11_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_C6_TC11_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_C7_TC11_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon11 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon11InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_C8_TC11_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon12 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon12Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_D8_TC12_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon12 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon12Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_D0_TC12_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_D1_TC12_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_D2_TC12_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_D3_TC12_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_D4_TC12_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_D5_TC12_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_D6_TC12_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_D7_TC12_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon12 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon12InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_D8_TC12_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon13 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon13Enable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_E8_TC13_CTRL, ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Tcon13 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTcon13Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_E0_TC13_VS_MSB, HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_E1_TC13_VS_LSB, LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_E2_TC13_VE_MSB, HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_E3_TC13_VE_LSB, LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_E4_TC13_HS_MSB, HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_E5_TC13_HS_LSB, LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_E6_TC13_HE_MSB, HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_E7_TC13_HE_LSB, LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Set Tcon13 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTcon13InvEnable(bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_E8_TC13_CTRL, ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Enable TCON
// Input Value  : bEnable --> Enable TCON
// Output Value : None
//--------------------------------------------------
void ScalerTconEnable(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Enable All TCON
        ScalerTconGlobalEnable(_ON);
#if(_PWM_RST_SIGNAL_SEL == _TCON)
#if(_HW_PWM_RST_BY_TCON_SELECT == _TCON4)
        // Enable TCON4
        ScalerTcon4Enable(_ON);
#elif(_HW_PWM_RST_BY_TCON_SELECT == _TCON8)
        // Enable TCON8
        ScalerTcon8Enable(_ON);
#endif
#endif

#if(_HW_TCON_TYPE == _TCON_GEN_1)
        ScalerTconCompensationAdjust(_HW_TCON_COMPENSATION);
#endif
    }
    else
    {
        // Disable All TCON
        ScalerTconGlobalEnable(_OFF);
#if(_PWM_RST_SIGNAL_SEL == _TCON)
#if(_HW_PWM_RST_BY_TCON_SELECT == _TCON4)
        // Disable TCON4
        ScalerTcon4Enable(_OFF);
#elif(_HW_PWM_RST_BY_TCON_SELECT == _TCON8)
        // Disable TCON8
        ScalerTcon8Enable(_OFF);
#endif
#endif
    }
}

//--------------------------------------------------
// Description  : Set Tcon global control
// Input Value  : bEnable --> Tcon global enable
// Output Value : None
//--------------------------------------------------
void ScalerTconGlobalEnable(bit bEnable)
{
    if(bEnable == _ON)
    {
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, ~(_BIT7), (_BIT7));
        SET_TCON_GLOBAL_ENABLE(_ENABLE);
    }
    else
    {
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, ~(_BIT7), 0x00);
        SET_TCON_GLOBAL_ENABLE(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : Set Specified Tcon invert enable
// Input Value  : ucTconIndex --> Specified Tcon Index
//                bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTconInvEnableByIndex(BYTE ucTconIndex, bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (ucTconIndex << 4), ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon logical operation enable
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerTconLogicalOpEnable(EnumTconLogicalOpSet enumTconLogicalOpSet, EnumTconLogicalOp enumTconLogicalOp, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        switch(enumTconLogicalOp)
        {
            case _TCON_LOGICAL_OP_AND:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                break;
            case _TCON_LOGICAL_OP_OR:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                break;
            case _TCON_LOGICAL_OP_XOR:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                break;
            case _TCON_TOGGLE_OP_NORMAL:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
                break;
            case _TCON_TOGGLE_OP_AND:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
                break;
            case _TCON_TOGGLE_OP_OR:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
                break;
            default:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                break;
        }
    }
    else
    {
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}
//--------------------------------------------------
// Description  : Set Tcon Gated by PWM enable
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerTconGatedByPwmEnable(EnumTconGatedByPwmSet enumTconGatedByPWM, BYTE ucPWM, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        switch(ucPWM)
        {
            case _PWM0:
                ScalerSetBit(PFF_3C_PWM45_M, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
                break;
            case _PWM1:
                ScalerSetBit(PFF_3C_PWM45_M, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
                break;
            case _PWM2:
                ScalerSetBit(PFF_3C_PWM45_M, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
                break;
            case _PWM3:
                ScalerSetBit(PFF_3C_PWM45_M, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
                break;
            case _PWM4:
                ScalerSetBit(PFF_3C_PWM45_M, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
                break;
            case _PWM5:
                ScalerSetBit(PFF_3C_PWM45_M, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
                break;
            default:
                break;
        }
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_28_TC1_CTRL + (BYTE)((enumTconGatedByPWM - 1) << 4), ~(_BIT4), _BIT4);
    }
    else
    {
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_28_TC1_CTRL + (BYTE)((enumTconGatedByPWM - 1) << 4), ~(_BIT4), 0x00);
    }
}
//--------------------------------------------------
// Description  : Adjust Horizontal value of TCON in FB mode
// Input Value  : pusHstart --> Horizontal start
//                pusHend --> Horizontal end
// Output Value : None
//--------------------------------------------------
void ScalerTconFBmodeAdjust(WORD *pusHstart, WORD *pusHend)
{
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        if(ScalerGetBit(P0_29_DISPLAY_CONTROL, _BIT4) == _BIT4)
        {
            *pusHstart = (*pusHstart + 1) / 2;
            *pusHend = (*pusHend + 1) / 2;
        }
    }
    else
#endif
    {
        pusHstart = pusHstart;
        pusHend = pusHend;
    }
}

//--------------------------------------------------
// Description  : Set Specified Tcon local enable
// Input Value  : ucTconIndex --> Specified Tcon Index
//                bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTconEnableByIndex(BYTE ucTconIndex, bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (ucTconIndex << 4), ~(_BIT7), ((BYTE)bEnable << 7));
}

//--------------------------------------------------
// Description  : Set Specified Tcon Region
// Input Value  : ucTconIndex --> Specified Tcon Index
//                usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void ScalerTconAdjustByIndex(BYTE ucTconIndex, WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    usVstart &= 0x7FFF;
    usVend &= 0x7FFF;

    usHstart &= 0x3FFF;
    usHend &= 0x3FFF;

    ScalerTconFBmodeAdjust(&usHstart, &usHend);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_10_TC0_VS_MSB + (ucTconIndex << 4), HIBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_11_TC0_VS_LSB + (ucTconIndex << 4), LOBYTE(usVstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_12_TC0_VE_MSB + (ucTconIndex << 4), HIBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_13_TC0_VE_LSB + (ucTconIndex << 4), LOBYTE(usVend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_14_TC0_HS_MSB + (ucTconIndex << 4), HIBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_15_TC0_HS_LSB + (ucTconIndex << 4), LOBYTE(usHstart));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_16_TC0_HE_MSB + (ucTconIndex << 4), HIBYTE(usHend));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_17_TC0_HE_LSB + (ucTconIndex << 4), LOBYTE(usHend));
}

//--------------------------------------------------
// Description  : Enable Tcon Double Buffer
// Input Value  : bEnable --> Tcon Double Buffer Enable
// Output Value : None
//--------------------------------------------------
void ScalerTconDBEnable(bit bEnable)
{
    BYTE ucTconCtrl = (ScalerGetDataPortSingleByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0) | (GET_TCON_GLOBAL_ENABLE() << 7));

    if(bEnable == _ON)
    {
        ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, (ucTconCtrl | _BIT1));
    }
    else
    {
        ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, (ucTconCtrl & ~(_BIT1)));
    }
}

//--------------------------------------------------
// Description  : Apply Tcon Double Buffer
// Input Value  : EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerTconDBApply(EnumDBApply enumDBApply)
{
    BYTE ucTconCtrl = (ScalerGetDataPortSingleByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0) | (GET_TCON_GLOBAL_ENABLE() << 7));

    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }
    // Set TCON Double Buffer Apply Bit
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, (ucTconCtrl | _BIT0));

    if(enumDBApply == _DB_APPLY_POLLING)
    {
        if(ScalerTimerPollingPortFlagProc(_TCON_DOUBLE_BUFFER_WAIT_TIME, P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, _BIT0, 0) == _FALSE)
        {
            // Disable Apply Bit when TCON double buffer timeout
            ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, (ucTconCtrl & ~(_BIT0)));
        }
    }
}

//-----------------------------------------------------------------------------------------
// Description  : Select whether Tcon[n+1] do logical operation with Tcon[n] gated by pwm
// Input Value  : EnumTconLogicalOpPwmGatedSel
//                _AFTER_TCON_GATED_BY_PWM --> Yes
//                _BEFORE_TCON_GATED_BY_PWM --> No
// Output Value : None
//-----------------------------------------------------------------------------------------
void ScalerTconLogicalOpWithGatedByPwmSel(EnumTconLogicalOpPwmGatedSel enumTconPWMGated)
{
    BYTE ucTconCtrl = (ScalerGetDataPortSingleByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0) | (GET_TCON_GLOBAL_ENABLE() << 7));

    if(enumTconPWMGated == _AFTER_TCON_GATED_BY_PWM)
    {
        ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, (ucTconCtrl | _BIT4));
    }
    else
    {
        ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, (ucTconCtrl & ~(_BIT4)));
    }
}

//-----------------------------------------------------------------------------------------
// Description  : Set Tcon Compensation
// Input Value  : usHCompensate
// Output Value : None
//-----------------------------------------------------------------------------------------
void ScalerTconCompensationAdjust(WORD usHCompensate)
{
    WORD usHstart = 0x0000;
    usHCompensate &= 0x3FFF;
    ScalerTconFBmodeAdjust(&usHstart, &usHCompensate);

    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_06_TC_CTRL2, HIBYTE(usHCompensate));
    ScalerSetDataPortByte(P15_A3_TCON_ADDR, _P15_A4_PT_07_TC_CTRL3, LOBYTE(usHCompensate));
}

