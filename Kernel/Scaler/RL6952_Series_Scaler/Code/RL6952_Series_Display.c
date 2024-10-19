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
// ID Code      : RL6952_Series_Display.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DISPLAY__

#include "ScalerFunctionInclude.h"
#include "Display/ScalerDisplay.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : Set Dual Port LVDS Clk Infomation: CLK set 72ohm as Termination On / CLK set current 2x as Termination Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsClkInfoSelect(void)
{
    // LVDS CLK(1 push 2): CLK set 72ohm as Termination on, parallel with 50 ohm(100 // 100), resistance = 41ohm
    if(_LVDS_TERMINATION_CONTROL == _DISABLE)
    {
#if((_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))

#if(_LVDS_PORT_SEL != _LVDS_2_PORT_CD)
#if(_LVDS_PAIR_MIRROR == _DISABLE)

        // Set LVDS TXAC Current 2x
        ScalerSetBit(P15_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));

#else // Else of #if(_LVDS_PAIR_MIRROR == _DISABLE)

        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            // Set LVDS TXA2 Current 2x
            ScalerSetBit(P15_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        }
        else
        {
            // Set LVDS TXA1 Current 2x
            ScalerSetBit(P15_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        }

#endif // End of #if(_LVDS_PAIR_MIRROR == _DISABLE)
#endif // End of #if(_LVDS_PORT_SEL != _LVDS_2_PORT_CD)

#if(_LVDS_PORT_SEL != _LVDS_2_PORT_AB)
#if(_LVDS_PAIR_MIRROR == _DISABLE)

        // Set LVDS TXAC Current 2x
        ScalerSetBit(P55_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));

#else // Else of #if(_LVDS_PAIR_MIRROR == _DISABLE)

        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            // Set LVDS TXA2 Current 2x
            ScalerSetBit(P55_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        }
        else
        {
            // Set LVDS TXA1 Current 2x
            ScalerSetBit(P55_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        }

#endif // End of #if(_LVDS_PAIR_MIRROR == _DISABLE)
#endif // End of #if(_LVDS_PORT_SEL != _LVDS_2_PORT_AB)
#endif // End of #if((_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
    }
    else
    {
#if((_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))

#if(_LVDS_PORT_SEL != _LVDS_2_PORT_CD)
#if(_LVDS_PAIR_MIRROR == _DISABLE)

        // Set LVDS TXAC Output Termination 72ohm
        ScalerSetBit(P15_28_LVDS_PORTA_CTRL8, ~(_BIT5 | _BIT4), _BIT4);

#else // Else of #if(_LVDS_PAIR_MIRROR == _DISABLE)

        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            // Set LVDS TXA2 Output Termination 72ohm
            ScalerSetBit(P15_28_LVDS_PORTA_CTRL8, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            // Set LVDS TXA1 Output Termination 72ohm
            ScalerSetBit(P15_27_LVDS_PORTA_CTRL7, ~(_BIT1 | _BIT0), _BIT0);
        }

#endif // End of #if(_LVDS_PAIR_MIRROR == _DISABLE)
#endif // End of #if(_LVDS_PORT_SEL != _LVDS_2_PORT_CD)

#if(_LVDS_PORT_SEL != _LVDS_2_PORT_AB)
#if(_LVDS_PAIR_MIRROR == _DISABLE)

        // Set LVDS TXAC Output Termination 72ohm
        ScalerSetBit(P55_28_LVDS_PORTA_CTRL8, ~(_BIT5 | _BIT4), _BIT4);

#else // Else of #if(_LVDS_PAIR_MIRROR == _DISABLE)

        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            // Set LVDS TXA2 Output Termination 72ohm
            ScalerSetBit(P55_28_LVDS_PORTA_CTRL8, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            // Set LVDS TXA1 Output Termination 72ohm
            ScalerSetBit(P55_27_LVDS_PORTA_CTRL7, ~(_BIT1 | _BIT0), _BIT0);
        }

#endif // End of #if(_LVDS_PAIR_MIRROR == _DISABLE)
#endif // End of #if(_LVDS_PORT_SEL != _LVDS_2_PORT_AB)
#endif // End of #if((_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
    }

#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)

    ScalerDisplayLvdsDoubleCurrentUserControl();

    ScalerDisplayLvdsTerminationUserControl();

#endif
}

//--------------------------------------------------
// Description  : Set LVDS driving control
// Input Value  : Driving current for Data and Clock pair
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv)
{
    BYTE ucOtpABDriv = 0;
    BYTE ucOtpCDDriv = 0;
    WORD usTempABDriv = 0;
    WORD usTempCDDriv = 0;

    ScalerOTPMemoryReadData(_OTPMEMORY_LVDS_AB_IBHN_TRIMDATA, &ucOtpABDriv);
    ScalerOTPMemoryReadData(_OTPMEMORY_LVDS_CD_IBHN_TRIMDATA, &ucOtpCDDriv);

    if(_LVDS_TERMINATION_CONTROL == _ENABLE)
    {
        // Set LVDS Output Termination 56ohm
        ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0x0A);
        ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0xAA);
        ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0x0A);
        ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0x8A);
        ScalerSetByte(P55_27_LVDS_PORTA_CTRL7, 0x0A);
        ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0xAA);
        ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x0A);
        ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x8A);

        // AB Port Driving Current Independent Multiple Setting
        ScalerSetBit(P15_40_LVDS_PORTA_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_44_LVDS_PORTA_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_45_LVDS_PORTA_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_50_LVDS_PORTB_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_51_LVDS_PORTB_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_52_LVDS_PORTB_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_54_LVDS_PORTB_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P15_55_LVDS_PORTB_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));

        // CD Port Driving Current Independent Multiple Setting
        ScalerSetBit(P55_40_LVDS_PORTA_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_44_LVDS_PORTA_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_45_LVDS_PORTA_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_50_LVDS_PORTB_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_51_LVDS_PORTB_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_52_LVDS_PORTB_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_54_LVDS_PORTB_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
        ScalerSetBit(P55_55_LVDS_PORTB_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));

        if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)
        {
            // Disable LVDS Pre-emphasis
            ScalerDisplayLvdsSetPreEmphasis(_LVDS_PRE_EMPHASIS_0);

            switch(ucDriv)
            {
                case _LVDS_DRIV_CONTROL_2_0:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 25 / 35) : 0x7D;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 25 / 35) : 0x7D;

                    break;

                case _LVDS_DRIV_CONTROL_2_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 262 / 350) : 0x83;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 262 / 350) : 0x83;

                    break;

                case _LVDS_DRIV_CONTROL_3_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 300 / 350) : 0x96;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 300 / 350) : 0x96;

                    break;

                case _LVDS_DRIV_CONTROL_1_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 188 / 350) : 0x44;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 188 / 350) : 0x44;

                    break;

                case _LVDS_DRIV_CONTROL_3_0:
                default:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 275 / 350) : 0x89;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 275 / 350) : 0x89;

                    break;
            }
        }
        else
        {
            // Enable LVDS Pre-emphasis level 1
            ScalerDisplayLvdsSetPreEmphasis(_LVDS_PRE_EMPHASIS_1);

            switch(ucDriv)
            {
                case _LVDS_DRIV_CONTROL_2_0:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 225 / 350) : 0x70;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 225 / 350) : 0x70;

                    break;

                case _LVDS_DRIV_CONTROL_2_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 238 / 350) : 0x76;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 238 / 350) : 0x76;

                    break;

                case _LVDS_DRIV_CONTROL_3_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 275 / 350) : 0x89;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 275 / 350) : 0x89;

                    break;

                case _LVDS_DRIV_CONTROL_1_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 175 / 350) : 0x3E;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 175 / 350) : 0x3E;

                    break;

                case _LVDS_DRIV_CONTROL_3_0:
                default:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 250 / 350) : 0x7D;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 250 / 350) : 0x7D;

                    break;
            }
        }
    }
    else
    {
        // Set LVDS Output Termination Disable
        ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0x00);
        ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0x00);
        ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0x00);
        ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0x00);
        ScalerSetByte(P55_27_LVDS_PORTA_CTRL7, 0x00);
        ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0x00);
        ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x00);
        ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x00);

        // AB Port Driving Current Independent Multiple Setting
        ScalerSetBit(P15_40_LVDS_PORTA_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_44_LVDS_PORTA_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_45_LVDS_PORTA_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_50_LVDS_PORTB_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_51_LVDS_PORTB_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_52_LVDS_PORTB_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_54_LVDS_PORTB_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P15_55_LVDS_PORTB_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

        // CD Port Driving Current Independent Multiple Setting
        ScalerSetBit(P55_40_LVDS_PORTA_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_44_LVDS_PORTA_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_45_LVDS_PORTA_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_50_LVDS_PORTB_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_51_LVDS_PORTB_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_52_LVDS_PORTB_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_54_LVDS_PORTB_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetBit(P55_55_LVDS_PORTB_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

        if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)
        {
            // Disable LVDS Pre-emphasis
            ScalerDisplayLvdsSetPreEmphasis(_LVDS_PRE_EMPHASIS_0);

            switch(ucDriv)
            {
                case _LVDS_DRIV_CONTROL_2_0:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 20 / 35) : 0x64;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 20 / 35) : 0x64;

                    break;

                case _LVDS_DRIV_CONTROL_2_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 25 / 35) : 0x7D;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 25 / 35) : 0x7D;

                    break;

                case _LVDS_DRIV_CONTROL_3_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? (ucOtpABDriv) : 0xAF;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? (ucOtpCDDriv) : 0xAF;

                    break;

                case _LVDS_DRIV_CONTROL_1_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 150 / 350) : 0x4B;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 150 / 350) : 0x4B;

                    break;

                case _LVDS_DRIV_CONTROL_3_0:
                default:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 30 / 35) : 0x96;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 30 / 35) : 0x96;

                    break;
            }
        }
        else
        {
            // Enable LVDS Pre-emphasis level 1
            ScalerDisplayLvdsSetPreEmphasis(_LVDS_PRE_EMPHASIS_1);

            switch(ucDriv)
            {
                case _LVDS_DRIV_CONTROL_2_0:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 225 / 350) : 0x70;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 225 / 350) : 0x70;

                    break;

                case _LVDS_DRIV_CONTROL_2_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 250 / 350) : 0x7D;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 250 / 350) : 0x7D;

                    break;

                case _LVDS_DRIV_CONTROL_3_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 325 / 350) : 0xA2;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 325 / 350) : 0xA2;

                    break;

                case _LVDS_DRIV_CONTROL_1_5:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 150 / 350) : 0x4B;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 150 / 350) : 0x4B;

                    break;

                case _LVDS_DRIV_CONTROL_3_0:
                default:

                    usTempABDriv = ((ucOtpABDriv != 0) && (ucOtpABDriv != 0xFF)) ? ((DWORD)ucOtpABDriv * 300 / 350) : 0x96;
                    usTempCDDriv = ((ucOtpCDDriv != 0) && (ucOtpCDDriv != 0xFF)) ? ((DWORD)ucOtpCDDriv * 300 / 350) : 0x96;

                    break;
            }
        }
    }

    ScalerSetByte(P15_0C_LVDS_COMMON_AB_CTRL12, ((usTempABDriv < 0xFF) ? usTempABDriv : 0xFF));
    ScalerSetByte(P55_0C_LVDS_COMMON_AB_CTRL12, ((usTempCDDriv < 0xFF) ? usTempCDDriv : 0xFF));

#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)

    ScalerDisplayLvdsDrivingCurrentUserControl();

#else
#endif // End of #if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
}

//--------------------------------------------------
// Description  : Initial Settings for Display Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsInitialTable(void)
{
    // Set LVDS Display Conversion
    ScalerDisplayLvdsSetDspcControl();

    // Set LVDS BW Parameter Rs[7:5]: 010(8.5k) Icp[4:2]: 0110(17.5uA)
    ScalerSetBit(P15_0D_LVDS_COMMON_AB_CTRL13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT3 | _BIT2));
    ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT3 | _BIT2));

    // Set LVDS CMU High Freq Select: 10 For LVDS 150M
    ScalerSetBit(P15_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit(P55_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT3 | _BIT2), _BIT3);

    // Set LVDS REG_CMU_C2: 1 for LVDS 150M
    ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT2, _BIT2);
    ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT2, _BIT2);

    // Set LVDS common mode Voltage
    ScalerDisplayVcmControl(_LVDS_VCM_CONTROL);

    // Set LVDS Driving Control
    ScalerDisplayLvdsDrivingControl(_LVDS_DRIV_CONTROL);

    // Set LVDS Output Termination Seletcion
    ScalerDisplayLvdsClkInfoSelect();

    // Set LVDS Phase Selection
    ScalerDisplayLvdsPhaseConrol();

    // Set LVDS data slew rate control
    ScalerDisplayLvdsSlewRateConrol();

    // Set LVDS TX output Data selection: Data / Strongly pull down / Termination
    ScalerDisplayLvdsTxDataSel();

    // Set LVDS TX Output Data Swap Selection
    ScalerDisplayLvdsTxPortSwap();

    // Disable LVDS CLK Signal, and Set To DC Level
    ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);

    // Set LVDS Shape-adjustment For Tx Stage
    ScalerSetBit(P15_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P15_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P55_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P55_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // Set LVDS Shape-adjustment For Pre-emphasis Stage
    ScalerSetBit(P15_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P15_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P55_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P55_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
}

//--------------------------------------------------
// Description  : DisplayConversion Settings for LVDS Panel
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetDspcControl(void)
{
    // Set DISP mode is LVDS
    ScalerSetBit(P39_00_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // Set Panel Data Port Number
    ScalerSetBit(P39_27_PANEL_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5), ((_PANEL_LVDS_OUTPUT_PORT + 1) << 5));

    // Set Panel Section
    ScalerSetBit(P39_27_PANEL_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1), ((_PANEL_LVDS_PANEL_SECTION + 1) << 1));

    // Set DSPC Pixel Mode
    ScalerSetBit(P39_28_PANEL_CTRL_2, ~(_BIT7 | _BIT6 | _BIT5), (_PANEL_LVDS_OUTPUT_PORT << 5));

    // Set Fold Disable
    ScalerSetBit(P39_28_PANEL_CTRL_2, ~_BIT4, 0x00);

    // Set Datamux From Front Length
    ScalerSetBit(P39_29_DATAMUX_CONTROL1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Display Resolution Control Settings
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~(_BIT2 | _BIT1), (_PANEL_DISP_BIT_MODE << 1));

    // Dispaly Panel Resoultion
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~_BIT3, ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? _BIT3 : 0x00));

    // Set LVDS Interface Type
    ScalerSetByte(P39_06_LVDS_DISPLAY_CONV_CTRL5, ((_LVDS_RB_SWAP << 7) | (_LVDS_ML_SWAP << 6) | (_LVDS_PN_SWAP << 4) | (_BIT3) | (_LVDS_CLK_CHANNEL_SEL << 1) | (_LVDS_PAIR_MIRROR << 0)));

    // Set LVDS Display Content
    ScalerSetBit(P39_07_LVDS_DISPLAY_CONV_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_DVS_INVERT << 3) | (_LVDS_DHS_INVERT << 2) | (_LVDS_DEN_INVERT << 1) | (_BIT0)));

    // Set OCLK: Inverted (timing constraint confirm with designer)
    ScalerSetBit(P39_17_LVDS_RSV0_CTRL0, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : LVDS PLL(Data) Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPLL(bit bOn)
{
    if(bOn == _ON)
    {
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))
        // Enable CMU Ldo
        ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~_BIT1, _BIT1);

        // Wait for CMU Ldo stable
        ScalerTimerDelayXms(2);

        // Vco Reset Set Normal
        ScalerSetBit(P15_0F_LVDS_COMMON_AB_CTRL15, ~_BIT1, _BIT1);

        // Power Up LVDS Port AB PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));

#elif((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))
        // Enable CMU Ldo
        ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~_BIT1, _BIT1);

        // Wait for CMU Ldo stable
        ScalerTimerDelayXms(2);

        // Vco Reset Set Normal
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~_BIT1, _BIT1);

        // Power Up LVDS Port CD PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)
        // Enable CMU Ldo
        ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~_BIT1, _BIT1);

        // Wait for CMU Ldo stable
        ScalerTimerDelayXms(2);

        // Vco Reset Set Normal
        ScalerSetBit(P15_0F_LVDS_COMMON_AB_CTRL15, ~_BIT1, _BIT1);
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~_BIT1, _BIT1);

        // Power Up LVDS Port ABCD PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));

#endif // #if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

        // Wait for LVDS PLL stable
        ScalerTimerDelayXms(2);

        // Set LVDS CLK Signal
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0xE3);
    }
    else
    {
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

        // Power Down LVDS Port AB PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT3 | _BIT1), 0x00);

        // Vco Reset Set Reset
        ScalerSetBit(P15_0F_LVDS_COMMON_AB_CTRL15, ~_BIT1, 0x00);

        // Disable CMU Ldo Enable
        ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~_BIT1, 0x00);

#elif((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))

        // Power Down LVDS Port CD PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT3 | _BIT1), 0x00);

        // Vco Reset Set Reset
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~_BIT1, 0x00);

        // Disable CMU Ldo Enable
        ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~_BIT1, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Power Down LVDS Port ABCD PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT3 | _BIT1), 0x00);
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT3 | _BIT1), 0x00);

        // Vco Reset Set Reset
        ScalerSetBit(P15_0F_LVDS_COMMON_AB_CTRL15, ~_BIT1, 0x00);
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~_BIT1, 0x00);

        // Disable CMU Ldo Enable
        ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~_BIT1, 0x00);

#endif // #if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

        // Disable LVDS CLK Signal, and Set To DC Level
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);
    }
}

//--------------------------------------------------
// Description  : LVDS Phase Selection Contorl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPhaseConrol(void)
{
    BYTE ucLvdsPhaseSeedH = 0x03;
    BYTE ucLvdsPhaseSeedL = 0x0F;
    BYTE ucLvdsPhaseH = 0x00;
    BYTE ucLvdsPhaseL = 0x00;

    ScalerSetBit(P15_21_LVDS_PORTA_CTRL1, ~_BIT7, 0x00);
    ScalerSetBit(P15_31_LVDS_PORTB_CTRL1, ~_BIT7, 0x00);
    ScalerSetBit(P55_21_LVDS_PORTA_CTRL1, ~_BIT7, 0x00);
    ScalerSetBit(P55_31_LVDS_PORTB_CTRL1, ~_BIT7, 0x00);

// PI_Phase_AB0 select
#if(_LVDS_PI_PHASE_AB0_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB0_SEL >> 2));  // ((_LVDS_PI_PHASE_AB0_SEL - (_LVDS_PI_PHASE_AB0_SEL % 4)) >> 2)
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB0_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_05_LVDS_COMMON_AB_CTRL5, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_05_LVDS_COMMON_AB_CTRL5, 0x30);
#endif

// PI_Phase_AB1 select
#if(_LVDS_PI_PHASE_AB1_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB1_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB1_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_07_LVDS_COMMON_AB_CTRL7, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_07_LVDS_COMMON_AB_CTRL7, 0x30);
#endif

// PI_Phase_AB2 select
#if(_LVDS_PI_PHASE_AB2_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB2_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB2_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_09_LVDS_COMMON_AB_CTRL9, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_09_LVDS_COMMON_AB_CTRL9, 0x30);
#endif

// PI_Phase_CD0 select
#if(_LVDS_PI_PHASE_CD0_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD0_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD0_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_05_LVDS_COMMON_AB_CTRL5, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_05_LVDS_COMMON_AB_CTRL5, 0x30);
#endif

// PI_Phase_CD1 select
#if(_LVDS_PI_PHASE_CD1_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD1_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD1_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_07_LVDS_COMMON_AB_CTRL7, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_07_LVDS_COMMON_AB_CTRL7, 0x30);
#endif

// PI_Phase_CD2 select
#if(_LVDS_PI_PHASE_CD2_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD2_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD2_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_09_LVDS_COMMON_AB_CTRL9, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_09_LVDS_COMMON_AB_CTRL9, 0x30);
#endif

    // Set Port A Phase selection (Analog Port A)
    ScalerSetBit(P15_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_A0_PHASE << 2) | (_LVDS_A1_PHASE << 0)));
    ScalerSetByte(P15_25_LVDS_PORTA_CTRL5, ((_LVDS_A2_PHASE << 6) | (_LVDS_AC_PHASE << 4) | (_LVDS_A3_PHASE << 2) | (_LVDS_A4_PHASE << 0)));

    // Set Port B Phase selection (Analog Port B)
    ScalerSetBit(P15_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_B0_PHASE << 2) | (_LVDS_B1_PHASE << 0)));
    ScalerSetByte(P15_35_LVDS_PORTB_CTRL5, ((_LVDS_B2_PHASE << 6) | (_LVDS_BC_PHASE << 4) | (_LVDS_B3_PHASE << 2) | (_LVDS_B4_PHASE << 0)));

    // Set Port C Phase selection (Analog Port A)
    ScalerSetBit(P55_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_C0_PHASE << 2) | (_LVDS_C1_PHASE << 0)));
    ScalerSetByte(P55_25_LVDS_PORTA_CTRL5, ((_LVDS_C2_PHASE << 6) | (_LVDS_CC_PHASE << 4) | (_LVDS_C3_PHASE << 2) | (_LVDS_C4_PHASE << 0)));

    // Set Port D Phase selection (Analog Port B)
    ScalerSetBit(P55_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_D0_PHASE << 2) | (_LVDS_D1_PHASE << 0)));
    ScalerSetByte(P55_35_LVDS_PORTB_CTRL5, ((_LVDS_D2_PHASE << 6) | (_LVDS_DC_PHASE << 4) | (_LVDS_D3_PHASE << 2) | (_LVDS_D4_PHASE << 0)));

    // Set LVDS PI Control Enable, and Set LVDS ckpixel_inv Rising Edge
    ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT0), _BIT4);
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT0), _BIT4);
}

//--------------------------------------------------
// Description  : LVDS Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPower(bit bOn)
{
    if(bOn == _ON)
    {
#if(_LVDS_SETTING_CONTROL_BY_USER == _DISABLE)
        // Disable Strongly Pull Down
        ScalerDisplayLvdsStronglyPullDown(_OFF);

        // Disable Weakly Pull Down
        ScalerDisplayLvdsWeaklyPullDown(_OFF);
#endif

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Enable LVDS Port AB IBGEN Power
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, _BIT7);
#endif

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Enable LVDS Port CD IBGEN Power
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, _BIT7);
#endif
    }
    else
    {
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Disable LVDS Port AB IBGEN Power
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, 0x00);
#endif

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Disable LVDS Port CD IBGEN Power
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, 0x00);
#endif

#if(_LVDS_SETTING_CONTROL_BY_USER == _DISABLE)
        // Enable Strongly Pull Down
        ScalerDisplayLvdsStronglyPullDown(_ON);

        // Enable Weakly Pull Down
        ScalerDisplayLvdsWeaklyPullDown(_ON);
#endif
    }
}

//--------------------------------------------------
// Description  : Set LVDS PI Operation band
// Input Value  : ucPhaseBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand)
{
    ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
}

//--------------------------------------------------
// Description  : Manual set LVDS VCO band
// Input Value  : ucVcoBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand)
{
    ScalerSetBit(P15_13_LVDS_COMMON_AB_CTRL18, ~(_BIT7 | _BIT6 | _BIT5), ucVcoBand);
    ScalerSetBit(P55_13_LVDS_COMMON_AB_CTRL18, ~(_BIT7 | _BIT6 | _BIT5), ucVcoBand);
}

//--------------------------------------------------
// Description  : LVDS Slew rate Contorl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSlewRateConrol(void)
{
    if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_0)
    {
        ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), 0x00);

        ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), 0x00);
    }
    else if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_1)
    {
        ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), (_BIT6));
        ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), (_BIT6));

        ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), (_BIT6));
        ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), (_BIT6));
    }
    else if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_2)
    {
        ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), (_BIT7));
        ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), (_BIT7));

        ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), (_BIT7));
        ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), (_BIT7));
    }
    else if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_3)
    {
        ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
}

//--------------------------------------------------
// Description  : Set LVDS driving control
// Input Value  : VCM for Data and Clock pair
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVcmControl(BYTE ucType)
{
    // Set LVDS Common Mode Voltage
    switch(ucType)
    {
        case _LVDS_VCM_LOW:

            // Vcm: 1.050V
            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

            break;

        case _LVDS_VCM_NORMAL:

            // Vcm: 1.250V
            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));

            break;

        case _LVDS_VCM_HIGH:

            // Vcm: 1.475V
            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT0));
            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT0));

            break;

        case _LVDS_VCM_USER:

            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _LVDS_VCM_USER_LEVEL);
            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _LVDS_VCM_USER_LEVEL);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Lvds Pll Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetLvdsPllPowerStatus(void)
{
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) ||\
    (_LVDS_PORT_SEL == _LVDS_1_PORT_B) ||\
    (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

    // Get Power of LVDS Port AB PLL
    if(ScalerGetBit(P15_00_LVDS_COMMON_AB_CTRL0, _BIT3) != 0)
    {
        return _TRUE;
    }

#elif((_LVDS_PORT_SEL == _LVDS_1_PORT_C) ||\
      (_LVDS_PORT_SEL == _LVDS_1_PORT_D) ||\
      (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))

    // Get Power of LVDS Port CD PLL
    if(ScalerGetBit(P55_00_LVDS_COMMON_AB_CTRL0, _BIT3) != 0)
    {
        return _TRUE;
    }

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

    // Power Up LVDS Port ABCD PLL
    if((ScalerGetBit(P15_00_LVDS_COMMON_AB_CTRL0, _BIT3) != 0) ||
       (ScalerGetBit(P55_00_LVDS_COMMON_AB_CTRL0, _BIT3) != 0))
    {
        return _TRUE;
    }

#endif // #if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set LVDS Pre Emphasis Level
// Input Value  : ucPhaseBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetPreEmphasis(BYTE ucPreEmphais)
{
    BYTE ucPreEmphasisLevel = 0x00;
    bit bPreEmphasisEnable = 0x00;

    switch(ucPreEmphais)
    {
        case _LVDS_PRE_EMPHASIS_1:

            // Set Tx Pre-emphasis current selection: 3 Level
            ucPreEmphasisLevel |= 0x00;
            bPreEmphasisEnable = _ENABLE;

            break;

        case _LVDS_PRE_EMPHASIS_2:

            // Tx Pre-emphasis current selection: 6 Level
            ucPreEmphasisLevel |= 0x66;
            bPreEmphasisEnable = _ENABLE;

            break;

        case _LVDS_PRE_EMPHASIS_3:

            // Tx Pre-emphasis current selection: 9 Level
            ucPreEmphasisLevel |= 0xCC;
            bPreEmphasisEnable = _ENABLE;

            break;

        case _LVDS_PRE_EMPHASIS_0:
        default:

            ucPreEmphasisLevel |= 0x00;
            bPreEmphasisEnable = _DISABLE;

            break;
    }

    if(bPreEmphasisEnable == _ENABLE)
    {
        ScalerSetByte(P15_29_LVDS_PORTA_CTRL9, ucPreEmphasisLevel);
        ScalerSetByte(P15_2A_LVDS_PORTA_CTRL10, ucPreEmphasisLevel);
        ScalerSetByte(P15_2C_LVDS_PORTA_CTRL12, ucPreEmphasisLevel);
        ScalerSetByte(P15_39_LVDS_PORTB_CTRL9, ucPreEmphasisLevel);
        ScalerSetByte(P15_3A_LVDS_PORTN_CTRL10, (ucPreEmphasisLevel & 0xF0));
        ScalerSetByte(P15_3C_LVDS_PORTB_CTRL12, ucPreEmphasisLevel);

        ScalerSetByte(P55_29_LVDS_PORTA_CTRL9, ucPreEmphasisLevel);
        ScalerSetByte(P55_2A_LVDS_PORTA_CTRL10, ucPreEmphasisLevel);
        ScalerSetByte(P55_2C_LVDS_PORTA_CTRL12, ucPreEmphasisLevel);
        ScalerSetByte(P55_39_LVDS_PORTB_CTRL9, ucPreEmphasisLevel);
        ScalerSetByte(P55_3A_LVDS_PORTN_CTRL10, (ucPreEmphasisLevel & 0xF0));
        ScalerSetByte(P55_3C_LVDS_PORTB_CTRL12, ucPreEmphasisLevel);

        ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : LVDS Strongly Pull Down Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsStronglyPullDown(bit bOn)
{
    if(bOn == _ON)
    {
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

        // Set LVDS Port A Strongly Pull Down Initially
        ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

        // Set LVDS Port B Strongly Pull Down Initially
        ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

        // Set LVDS Port C Strongly Pull Down Initially
        ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

        // Set LVDS Port D Strongly Pull Down Initially
        ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Set LVDS Port AB Strongly Pull Down Initially
        ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~_BIT6, _BIT6);
        ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Set LVDS Port CD Strongly Pull Down Initially
        ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~_BIT6, _BIT6);
        ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Set LVDS Port ABCD Strongly Pull Down Initially
        ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~_BIT6, _BIT6);
        ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~_BIT6, _BIT6);
        ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~_BIT6, _BIT6);
        ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~_BIT6, _BIT6);

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
    }
    else
    {
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

        // Set LVDS Port A Strongly Pull Down Initially
        ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~_BIT6, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

        // Set LVDS Port B Strongly Pull Down Initially
        ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~_BIT6, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

        // Set LVDS Port C Strongly Pull Down Initially
        ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~_BIT6, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

        // Set LVDS Port D Strongly Pull Down Initially
        ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~_BIT6, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Set LVDS Port AB Strongly Pull Down Initially
        ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~_BIT6, 0x00);
        ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~_BIT6, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Set LVDS Port CD Strongly Pull Down Initially
        ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~_BIT6, 0x00);
        ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~_BIT6, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Set LVDS Port ABCD Strongly Pull Down Initially
        ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~_BIT6, 0x00);
        ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~_BIT6, 0x00);
        ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~_BIT6, 0x00);
        ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~_BIT6, 0x00);

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
    }
}

//--------------------------------------------------
// Description  : LVDS Weakly Pull Down Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsWeaklyPullDown(bit bOn)
{
    if(bOn == _ON)
    {
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

        // Enable Port A Weakly Pull Down, Disable Port BCD Weakly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

        // Enable Port B Weakly Pull Down, Disable Port ACD Weakly Pull Down
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

        // Enable Port C Weakly Pull Down, Disable Port ABD Weakly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

        // Enable Port D Weakly Pull Down, Disable Port ABC Weakly Pull Down
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Enable Port AB Weakly Pull Down, Disable Port CD Weakly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Enable Port CD Weakly Pull Down, Disable Port AB Weakly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Enable Port ABCD Weakly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, _BIT7);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, _BIT7);

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
    }
    else
    {
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

        // Disable Port A Weakly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

        // Disable Port B Weakly Pull Down
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

        // Disable Port C Weakly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

        // Disable Port D Weakly Pull Down
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Disable Port AB Weakly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Disable Port CD Weakly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Disable Port ABCD Weakly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT7, 0x00);

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
    }
}

#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//--------------------------------------------------
// Description  : LVDS Strongly Weakly Pull Down by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsStronglyWeaklyPullDownUserControl(void)
{
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7), _LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL << 7);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7), _LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL << 7);
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7), _LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL << 7);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7), _LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL << 7);

#if(_LVDS_PORTA_STRONGLY_PULL_DOWN_USER_CONTROL == _ENABLE)
    ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~(_BIT6), _BIT6);
#else
    ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~(_BIT6), 0x00);
#endif

#if(_LVDS_PORTB_STRONGLY_PULL_DOWN_USER_CONTROL == _ENABLE)
    ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~(_BIT6), _BIT6);
#else
    ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~(_BIT6), 0x00);
#endif

#if(_LVDS_PORTC_STRONGLY_PULL_DOWN_USER_CONTROL == _ENABLE)
    ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~(_BIT6), _BIT6);
#else
    ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~(_BIT6), 0x00);
#endif

#if(_LVDS_PORTD_STRONGLY_PULL_DOWN_USER_CONTROL == _ENABLE)
    ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~(_BIT6), _BIT6);
#else
    ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~(_BIT6), 0x00);
#endif
}

//--------------------------------------------------
// Description  : LVDS Double Current Control by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsDoubleCurrentUserControl(void)
{
#if(_LVDS_PORTA_DATA0_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_40_LVDS_PORTA_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_40_LVDS_PORTA_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA1_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA2_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_CLK_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA3_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_44_LVDS_PORTA_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_44_LVDS_PORTA_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA4_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_45_LVDS_PORTA_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_45_LVDS_PORTA_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA0_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_50_LVDS_PORTB_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_50_LVDS_PORTB_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA1_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_51_LVDS_PORTB_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_51_LVDS_PORTB_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA2_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_52_LVDS_PORTB_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_52_LVDS_PORTB_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA3_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_54_LVDS_PORTB_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_54_LVDS_PORTB_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA4_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P15_55_LVDS_PORTB_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P15_55_LVDS_PORTB_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA0_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_40_LVDS_PORTA_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_40_LVDS_PORTA_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA1_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_41_LVDS_PORTA_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA2_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_42_LVDS_PORTA_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_CLK_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_43_LVDS_PORTA_CTRL18, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA3_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_44_LVDS_PORTA_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_44_LVDS_PORTA_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTA_DATA4_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_45_LVDS_PORTA_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_45_LVDS_PORTA_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA0_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_50_LVDS_PORTB_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_50_LVDS_PORTB_CTRL15, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA1_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_51_LVDS_PORTB_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_51_LVDS_PORTB_CTRL16, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA2_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_52_LVDS_PORTB_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_52_LVDS_PORTB_CTRL17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA3_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_54_LVDS_PORTB_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_54_LVDS_PORTB_CTRL19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

#if(_LVDS_PORTB_DATA4_DRIV_2X_USER_CTRL == _ENABLE)
    ScalerSetBit(P55_55_LVDS_PORTB_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    ScalerSetBit(P55_55_LVDS_PORTB_CTRL20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif
}

//--------------------------------------------------
// Description  : LVDS Driving Current Control by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsDrivingCurrentUserControl(void)
{
    ScalerSetByte(P15_0C_LVDS_COMMON_AB_CTRL12, (_LVDS_DRIV_CURRENT_USER_ADUST & 0xFF));
    ScalerSetByte(P55_0C_LVDS_COMMON_AB_CTRL12, (_LVDS_DRIV_CURRENT_USER_ADUST & 0xFF));
}

//--------------------------------------------------
// Description  : LVDS Termaination Control by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsTerminationUserControl(void)
{
    // Set LVDS TXA Output Termination
    ScalerSetBit(P15_27_LVDS_PORTA_CTRL7, ~(_BIT3 | _BIT2), (_LVDS_PORTA_DATA0_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P15_27_LVDS_PORTA_CTRL7, ~(_BIT1 | _BIT0), (_LVDS_PORTA_DATA1_TERMINATION_USER_ADJUST & 0x03) << 0);

    ScalerSetBit(P15_28_LVDS_PORTA_CTRL8, ~(_BIT7 | _BIT6), (_LVDS_PORTA_DATA2_TERMINATION_USER_ADJUST & 0x03) << 6);
    ScalerSetBit(P15_28_LVDS_PORTA_CTRL8, ~(_BIT3 | _BIT2), (_LVDS_PORTA_DATA3_TERMINATION_USER_ADJUST & 0x03) << 2);

    // Set LVDS TXB Output Termination
    ScalerSetBit(P15_37_LVDS_PORTB_CTRL7, ~(_BIT3 | _BIT2), (_LVDS_PORTB_DATA0_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P15_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), (_LVDS_PORTB_DATA1_TERMINATION_USER_ADJUST & 0x03) << 0);

    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), (_LVDS_PORTB_DATA2_TERMINATION_USER_ADJUST & 0x03) << 6);
    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), (_LVDS_PORTB_CLK_TERMINATION_USER_ADJUST & 0x03) << 4);
    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT3 | _BIT2), (_LVDS_PORTB_DATA3_TERMINATION_USER_ADJUST & 0x03) << 2);

    // Set LVDS TXC Output Termination
    ScalerSetBit(P55_27_LVDS_PORTA_CTRL7, ~(_BIT3 | _BIT2), (_LVDS_PORTC_DATA0_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P55_27_LVDS_PORTA_CTRL7, ~(_BIT1 | _BIT0), (_LVDS_PORTC_DATA1_TERMINATION_USER_ADJUST & 0x03) << 0);

    ScalerSetBit(P55_28_LVDS_PORTA_CTRL8, ~(_BIT7 | _BIT6), (_LVDS_PORTC_DATA2_TERMINATION_USER_ADJUST & 0x03) << 6);
    ScalerSetBit(P55_28_LVDS_PORTA_CTRL8, ~(_BIT3 | _BIT2), (_LVDS_PORTC_DATA3_TERMINATION_USER_ADJUST & 0x03) << 2);

    // Set LVDS TXD Output Termination
    ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT3 | _BIT2), (_LVDS_PORTD_DATA0_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), (_LVDS_PORTD_DATA1_TERMINATION_USER_ADJUST & 0x03) << 0);

    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), (_LVDS_PORTD_DATA2_TERMINATION_USER_ADJUST & 0x03) << 6);
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), (_LVDS_PORTD_CLK_TERMINATION_USER_ADJUST & 0x03) << 4);
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT3 | _BIT2), (_LVDS_PORTD_DATA3_TERMINATION_USER_ADJUST & 0x03) << 2);
}
#endif
#endif

//--------------------------------------------------
// Description  : Display Output Pad Power Control --> LVDS, TTL, GPIO
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayPadPower(bit bOn)
{
#if(_PANEL_STYLE == _PANEL_LVDS)
#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
    ScalerDisplayLvdsStronglyWeaklyPullDownUserControl();
#else
    // Enable Strongly Pull Down
    ScalerDisplayLvdsStronglyPullDown(_ON);
    // Enable Weakly Pull Down
    ScalerDisplayLvdsWeaklyPullDown(_ON);
#endif
#else
    // Disable Port ABCD Weakly and Strongly Pull Down
    ScalerSetBit(P15_2B_LVDS_PORTA_CTRL11, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P15_3B_LVDS_PORTB_CTRL11, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P55_2B_LVDS_PORTA_CTRL11, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P55_3B_LVDS_PORTB_CTRL11, ~(_BIT7 | _BIT6), 0x00);
#endif

    if(bOn == _ON)
    {
        // Power Up Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
        // Power Up Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // Power Down Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
        // Power Down Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
    }
}


