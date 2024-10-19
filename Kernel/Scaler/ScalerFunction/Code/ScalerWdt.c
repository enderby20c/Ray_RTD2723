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
// ID Code      : ScalerWdt.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Wdt/ScalerWdt.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Init WDT Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerWdtInitial(void)
{
    ScalerWdtEnableWdtINT(_WDT_INT_ENABLE);

    // Set 10 seconds timeout count for WD CLK = 14.318M/27M
    ScalerWdtSetWdtOV(10000, _EXT_XTAL_CLK);

#if(_JTAG_DEBUG == _OFF)
    ScalerWdtEnableWdt(_WDT_ENABLE);
    ScalerCpuHalEnableIRQ(_IRQN_WDT);
#endif
}

//--------------------------------------------------
// Description  : Get WDT NMI INT flag to check if WDT NMI INT happened
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD ScalerWdtGetWdtNmiFlag(void)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    return Scaler32GetBit(PA30003_00_MSK_ISR, _BIT8);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    return Scaler32GetBit(PA40011_00_MSK_ISR, _BIT8);
#endif
}

//--------------------------------------------------
// Description  : Ack to Clear WDT NMI INT flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerWdtAckWdtNmiFlag(void)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30003_00_MSK_ISR, ~(_BIT8), _BIT8);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40011_00_MSK_ISR, ~(_BIT8), _BIT8);
#endif

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}

//--------------------------------------------------
// Description  : Manual trigger WDT reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerWdtTriggerWdtReset(void)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30003_04_TCWCR, ~(_BIT31), _BIT31);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40011_04_TCWCR, ~(_BIT31), _BIT31);
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable WDT INT
// Input Value  : enumWdtIntEn : En/Dis WDT INT
// Output Value : None
//--------------------------------------------------
void ScalerWdtEnableWdtINT(EnumCpuWdtIntEN enumWdtIntEn)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30003_04_TCWCR, ~(_BIT16), enumWdtIntEn);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40011_04_TCWCR, ~(_BIT16), enumWdtIntEn);
#endif
}

//--------------------------------------------------
// Description  : Get WDT NMI Occur times ( only be HW-reset by PowerOnReset )
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD ScalerWdtGetWdtNmiOccurCnt(void)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    return ((Scaler32GetDWord(PA30003_04_TCWCR) >> 12) & (0x0000000F));
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    return ((Scaler32GetDWord(PA40011_04_TCWCR) >> 12) & (0x0000000F));
#endif
}

//--------------------------------------------------
// Description  : Manual Clear WDT NMI Occur times ( SW-reset by writting b'1111 to NMIC )
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerWdtResetWdtNmiOccurCnt(void)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30003_04_TCWCR, ~((0x0F) << 12), ((0x0F) << 12));
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40011_04_TCWCR, ~((0x0F) << 12), ((0x0F) << 12));
#endif
}

//--------------------------------------------------
// Description  : Get WDT INT Occur times ( only be HW-reset by PowerOnReset )
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD ScalerWdtGetWdtOccurCnt(void)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    return ((Scaler32GetDWord(PA30003_04_TCWCR) >> 8) & (0x0000000F));
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    return ((Scaler32GetDWord(PA40011_04_TCWCR) >> 8) & (0x0000000F));
#endif
}

//--------------------------------------------------
// Description  : Manual Clear WDT INT Occur times ( SW-reset by writting b'1111 to WDC )
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerWdtResetWdtOccurCnt(void)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30003_04_TCWCR, ~((0x0F) << 8), ((0x0F) << 8));
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40011_04_TCWCR, ~((0x0F) << 8), ((0x0F) << 8));
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable WDT Counter
// Input Value  : enumWdtIntEn : En/Dis WDT
// Output Value : None
//--------------------------------------------------
void ScalerWdtEnableWdt(EnumCpuWdtEN enumWdtEn)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30003_04_TCWCR, ~((DWORD)0xFF), enumWdtEn);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40011_04_TCWCR, ~((DWORD)0xFF), enumWdtEn);
#endif
}

//--------------------------------------------------
// Description  : Clear WDT Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerWdtClearWDT(void)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetDWord(PA30003_08_TCWTR, _BIT0);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetDWord(PA40011_08_TCWTR, _BIT0);
#endif
}

//--------------------------------------------------
// Description  : Setup NMI Interval , NMI_INterval = TCWNMI_SEL * 1/Xtal MHz
//                EX:if TCWNMI_SEL=0x0070_0000 ,Xtal=14.318MHz,
//                   NMI_Interval=0x00700000/14.381MHz=512643us)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerWdtSetNmiOV(DWORD ulNmiOvMs)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetDWord(PA30003_0C_TCWNMI, (ulNmiOvMs * (_HW_CPU32_CLK_SRC_EXTAL)));
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetDWord(PA40011_0C_TCWNMI, (ulNmiOvMs * (_HW_CPU32_CLK_SRC_EXTAL)));
#endif
}

//--------------------------------------------------
// Description  : Setup WDT Interval , WdtINterval = ((TCWOV_SEL&0xFFFFFF00)|0x80) * 1/Xtal MHz
//                EX:if TCWOV_SEL=0x0070_0000 ,Xtal=14.318MHz,
//                   NMI_Interval=0x00700080/14.381MHz=512652us)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerWdtSetWdtOV(DWORD ulWdtOvMs, EnumClkSel enumSel)
{
    // 14.318MHz , 0.0698421567257us per tick
    // 27MHz , 0.0370370370370us per tick
    // 28MHz , 0.0357142857142us per tick
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    if(enumSel == _EXT_XTAL_CLK)
    {
        Scaler32SetDWord(PA30003_10_TCWOV, (((ulWdtOvMs * (_HW_CPU32_CLK_SRC_EXTAL)))));
    }
    else
    {
        Scaler32SetDWord(PA30003_10_TCWOV, (((ulWdtOvMs * (_HW_CPU32_CLK_SRC_IOSC)))));
    }

#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    if(enumSel == _EXT_XTAL_CLK)
    {
        Scaler32SetDWord(PA40011_10_TCWOV, (((ulWdtOvMs * (_HW_CPU32_CLK_SRC_EXTAL)))));
    }
    else
    {
        Scaler32SetDWord(PA40011_10_TCWOV, (((ulWdtOvMs * (_HW_CPU32_CLK_SRC_IOSC)))));
    }
#endif

    ScalerWdtClearWDT();
}
