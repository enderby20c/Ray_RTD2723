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
// ID Code      : RL6952_Series_OTP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "OTP/ScalerOTP.h"

#if(_HW_FUSE_TYPE == _OTPFUSE_TYPE)
//****************************************************************************
// CODE TABLES
//****************************************************************************
StructOTPMapping g_pstOTPMappingData[] =
{
    {_OTPMEMORY_CHECK_EMPTY,              _HW_OTPFUSE_CHECK_EMPTY_STR,               _HW_OTPFUSE_CHECK_EMPTY_LEN},
    {_OTPMEMORY_HDCP14_RXKEYBKSV,         _HW_OTPFUSE_HDCP14_RXKEYBKSV_STR,          _HW_OTPFUSE_HDCP14_RXKEYBKSV_LEN},
    {_OTPMEMORY_HDCP14_RXKEY,             _HW_OTPFUSE_HDCP14_RXKEY_STR,              _HW_OTPFUSE_HDCP14_RXKEY_LEN},
    {_OTPMEMORY_HDCP14_TXKEYBKSV,         _HW_OTPFUSE_HDCP14_TXKEYBKSV_STR,          _HW_OTPFUSE_HDCP14_TXKEYBKSV_LEN},
    {_OTPMEMORY_HDCP14_TXKEY,             _HW_OTPFUSE_HDCP14_TXKEY_STR,              _HW_OTPFUSE_HDCP14_TXKEY_LEN},
    {_OTPMEMORY_HDCP22_RXKEY,             _HW_OTPFUSE_HDCP22_RXKEY_STR,              _HW_OTPFUSE_HDCP22_RXKEY_LEN},
    {_OTPMEMORY_HDCP22_RXKEY_CERTRX,      _HW_OTPFUSE_HDCP22_RXKEY_CERTRX_STR,       _HW_OTPFUSE_HDCP22_RXKEY_CERTRX_LEN},
    {_OTPMEMORY_HDCP22_RXKEY_KPRIV,       _HW_OTPFUSE_HDCP22_RXKEY_KPRIV_STR,        _HW_OTPFUSE_HDCP22_RXKEY_KPRIV_LEN},
    {_OTPMEMORY_HDCP22_RXKEY_RRMODN,      _HW_OTPFUSE_HDCP22_RXKEY_RRMODN_STR,       _HW_OTPFUSE_HDCP22_RXKEY_RRMODN_LEN},
    {_OTPMEMORY_HDCP22_RXKEY_NPINV,       _HW_OTPFUSE_HDCP22_RXKEY_NPINV_STR,        _HW_OTPFUSE_HDCP22_RXKEY_NPINV_LEN},
    {_OTPMEMORY_HDCP22_RXKEY_DKEY,        _HW_OTPFUSE_HDCP22_RXKEY_DKEY_STR,         _HW_OTPFUSE_HDCP22_RXKEY_DKEY_LEN},
    {_OTPMEMORY_HDCP22_RXKEY_LCKEY,       _HW_OTPFUSE_HDCP22_RXKEY_LCKEY_STR,        _HW_OTPFUSE_HDCP22_RXKEY_LCKEY_LEN},
    {_OTPMEMORY_TYPE_C_0_TRIMDATA,        _HW_OTPFUSE_TYPE_C_0_TRIMDATA_STR,         _HW_OTPFUSE_TYPE_C_0_TRIMDATA_LEN},
    {_OTPMEMORY_TYPE_C_0_1M_TRIMDATA,     _HW_OTPFUSE_TYPE_C_0_1M_TRIMDATA_STR,      _HW_OTPFUSE_TYPE_C_0_1M_TRIMDATA_LEN},
    {_OTPMEMORY_TYPE_C_1_TRIMDATA,        _HW_OTPFUSE_TYPE_C_1_TRIMDATA_STR,         _HW_OTPFUSE_TYPE_C_1_TRIMDATA_LEN},
    {_OTPMEMORY_TYPE_C_1_1M_TRIMDATA,     _HW_OTPFUSE_TYPE_C_1_1M_TRIMDATA_STR,      _HW_OTPFUSE_TYPE_C_1_1M_TRIMDATA_LEN},
    {_OTPMEMORY_LVDS_AB_IBHN_TRIMDATA,    _HW_OTPFUSE_LVDS_AB_IBHN_TRIMDATA_STR,     _HW_OTPFUSE_LVDS_AB_IBHN_TRIMDATA_LEN},
    {_OTPMEMORY_DDC_CONFIG,               _HW_OTPFUSE_DDC_CONFIG_STR,                _HW_OTPFUSE_DDC_CONFIG_LEN},
    {_OTPMEMORY_IOSC_TRIMDATA,            _HW_OTPFUSE_IOSC_TRIMDATA_STR,             _HW_OTPFUSE_IOSC_TRIMDATA_LEN},
    {_OTPMEMORY_HDMI_RETIMER,             _HW_OTPFUSE_HDMI_RETIMER_STR,              _HW_OTPFUSE_HDMI_RETIMER_LEN},
    {_OTPMEMORY_M2PLL_CONFIG,             _HW_OTPFUSE_M2PLL_CONFIG_STR,              _HW_OTPFUSE_M2PLL_CONFIG_LEN},
    {_OTPMEMORY_HDMI_TRIMDATA,            _HW_OTPFUSE_HDMI_TRIMDATA_STR,             _HW_OTPFUSE_HDMI_TRIMDATA_LEN},
    {_OTPMEMORY_CEC1_CONFIG,              _HW_OTPFUSE_CEC1_CONFIG_STR,               _HW_OTPFUSE_CEC1_CONFIG_LEN},
    {_OTPMEMORY_EMCU_CONFIG,              _HW_OTPFUSE_EMCU_CONFIG_STR,               _HW_OTPFUSE_EMCU_CONFIG_LEN},
    {_OTPMEMORY_THERMAL_SENSOR,           _HW_OTPFUSE_THERMAL_SENSOR_STR,            _HW_OTPFUSE_THERMAL_SENSOR_LEN},
    {_OTPMEMORY_SLP_MODE,                 _HW_OTPFUSE_SLP_MODE_STR,                  _HW_OTPFUSE_SLP_MODE_LEN},
    {_OTPMEMORY_HDCP_LOCATION,            _HW_OTPFUSE_HDCP_LOCATION_STR,             _HW_OTPFUSE_HDCP_LOCATION_LEN},
    {_OTPMEMORY_LVDS_CD_IBHN_TRIMDATA,    _HW_OTPFUSE_LVDS_CD_IBHN_TRIMDATA_STR,     _HW_OTPFUSE_LVDS_CD_IBHN_TRIMDATA_LEN},
    {_OTPMEMORY_LVDS_VCM_AB_TRIMDATA,     _HW_OTPFUSE_LVDS_VCM_AB_TRIMDATA_STR,      _HW_OTPFUSE_LVDS_VCM_AB_TRIMDATA_LEN},
    {_OTPMEMORY_LVDS_VCM_CD_TRIMDATA,     _HW_OTPFUSE_LVDS_VCM_CD_TRIMDATA_STR,      _HW_OTPFUSE_LVDS_VCM_CD_TRIMDATA_LEN},
    {_OTPMEMORY_AUDIO_CORNER_CONFIG,      _HW_OTPFUSE_AUDIO_CORNER_CONFIG_STR,       _HW_OTPFUSE_AUDIO_CORNER_CONFIG_LEN},
    {_OTPMEMORY_EARC_TRIMDATA,            _HW_OTPFUSE_EARC_TRIMDATA_STR,             _HW_OTPFUSE_EARC_TRIMDATA_LEN},
    {_OTPMEMORY_TYPE_C_SARADC_TRIMDATA,   _HW_OTPFUSE_TYPE_C_SARADC_TRIMDATA_STR,    _HW_OTPFUSE_TYPE_C_SARADC_TRIMDATA_LEN},
    {_OTPMEMORY_MST_DPTX_IB_TRIMDATA,     _HW_OTPFUSE_MST_DPTX_IB_TRIMDATA_STR,      _HW_OTPFUSE_MST_DPTX_IB_TRIMDATA_LEN},
    {_OTPMEMORY_SINK_ASS_1M_TRIMDATA,     _HW_OTPFUSE_SINK_ASS_1M_TRIMDATA_STR,      _HW_OTPFUSE_SINK_ASS_1M_TRIMDATA_LEN},
    {_OTPMEMORY_FEATURE_CTRL_BYTE,        _HW_OTPFUSE_FEATURE_CTRL_BYTE_STR,         _HW_OTPFUSE_FEATURE_CTRL_BYTE_LEN},
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//----------------------------------------------------------------------------------------------------
// Description  :  ScalerOTPBankRead
// Input Value  :  ucOTPfuseBankBitMode, usOTPfuseBankStrAddr, usLength, *pucOTPfuseData
// Output Value  :  None
//----------------------------------------------------------------------------------------------------
void ScalerOTPBankRead(BYTE ucOTPfuseBankBitMode, WORD usOTPfuseBankStrAddr, WORD usLength, BYTE *pucOTPfuseData)
{
    WORD usOTPfuseAddraSet = 0;
    WORD usi = 0;

    // Debug
    DebugMessageDigital("8. ucOTPfuseBankBitMode", ucOTPfuseBankBitMode);
    DebugMessageDigital("8. usOTPfuseBankStrAddr", usOTPfuseBankStrAddr);
    DebugMessageDigital("8. usLength", usLength);

    // Turn on PLDO
    ScalerSetByte(P24_A7_OTP_HW_CTRL_1, 0x14);
    // Wait more than 10us to avoid Tpls violation
    DELAY_15US();

    // Turn off Deep Standby
    ScalerSetByte(P24_A7_OTP_HW_CTRL_1, 0x10);
    // Wait more than 2us to avoid Tsas violation
    DELAY_5US();

    // Turn on PTRIM
    ScalerSetByte(P24_A7_OTP_HW_CTRL_1, 0x11);
    // Wait more than 50us to avoid Ttas violation
    DELAY_XUS(50);

    // Enable Gated Clock & HW mode.
    ScalerSetByte(P24_A6_OTP_HW_CTRL_0, 0x02);

    // Wait more than 2us to avoid Tsas violation
    DELAY_10US();

    // Set READ mode
    ScalerSetByte(P24_A9_OTP_HW_CTRL_3, 0x00);

    // Disable Gated Clock & HW mode.
    ScalerSetByte(P24_A6_OTP_HW_CTRL_0, 0x00);

    // Wait more than 10us to avoid Tcs violation
    DELAY_20US();

    // Set Div28 for 1us counter (IOSC_28)(0991_IOSC_27)
    ScalerSetByte(P24_AC_OTP_CLK_CTRL, 0x1C);

    if(ucOTPfuseBankBitMode == _HW_OTPFUSE_8BIT)
    {
        DebugMessageDigital("8. OTP fuse 8b mode ***", _HW_OTPFUSE_8BIT);

        for(usi = 0; usi < usLength; usi++) // load one byte one time
        {
            usOTPfuseAddraSet = (usOTPfuseBankStrAddr + usi);

            // Set Read Addr_A
            ScalerSetByte(P24_A1_OTP_ADDR_INPUT_L, LOBYTE(usOTPfuseAddraSet));
            ScalerMcuDelayDot2usPN();
            ScalerMcuDelayDot2usPN();
            ScalerSetByte(P24_A2_OTP_ADDR_INPUT_H, HIBYTE(usOTPfuseAddraSet));
            ScalerMcuDelayDot2usPN();
            ScalerMcuDelayDot2usPN();

            // Read Enable
            ScalerSetBit(P24_A8_OTP_HW_CTRL_2, ~(_BIT0), _BIT0);
            ScalerMcuDelayDot2usPN();
            ScalerMcuDelayDot2usPN();

            // Wait more than 111ns to avoid Tcsp violation
            pData[0] = 30;
            while((ScalerGetBit(P24_A8_OTP_HW_CTRL_2, _BIT0) != 0x00) && (pData[0] > 0))
            {
                DELAY_5US();
                pData[0] = pData[0] - 1;
            }

            pucOTPfuseData[usi] = ScalerGetByte (P24_A5_OTP_PDOUT);

            // Debug
            DebugMessageDigital("8. OTP fuse Addr_A lo Byte", ScalerGetByte(P24_A1_OTP_ADDR_INPUT_L));
            DebugMessageDigital("8. OTP fuse Addr_A hi Byte", ScalerGetByte(P24_A2_OTP_ADDR_INPUT_H));
            DebugMessageDigital("8. OTP fuse Byte", ScalerGetByte(P24_A5_OTP_PDOUT));
            DebugMessageDigital("8. OTP fuse Cnt usi = ", usi);
            DebugMessageDigital("8. pucOTPfuseData[usi]", pucOTPfuseData[usi]);
            DebugMessageDigital("8. *************", 0);
        }
    }
    else
    {
        // Debug
        DebugMessageDigital("8. OTP fuse other Bit mode ***", 0);
    }

    // Enable Gated Clock & HW mode.
    ScalerSetByte(P24_A6_OTP_HW_CTRL_0, 0x02);
    ScalerMcuDelayDot2usPN();
    ScalerMcuDelayDot2usPN();

    // Turn off PTRIM
    ScalerSetByte(P24_A7_OTP_HW_CTRL_1, 0x10);
    // Wait more than 10ns to avoid Tash violation
    DELAY_5US();

    // Turn on Deep Standby
    ScalerSetByte(P24_A7_OTP_HW_CTRL_1, 0x14);
    DELAY_5US();

    // Turn off PLDO
    ScalerSetByte(P24_A7_OTP_HW_CTRL_1, 0x04);
}

//--------------------------------------------------
// Description  : ScalerOTPGetData
// Input Value  : usStrAddr, usLength, pucOTPfuseData
// Output Value : None
//--------------------------------------------------
void ScalerOTPGetData(WORD usStrAddr, WORD usLength, BYTE *pucOTPfuseData)
{
    WORD usOTPfuseBankRdStrAddr = 0;
    WORD usOTPfuseRdLength = 0;
    WORD usOTPfuseRdLengthAcc = 0;
    BYTE uci = 0;
    WORD usCurrStart = 0;
    WORD usCurrEnd = 0;

    BYTE code tOTPFUSE_BITMODE_OF_BANK[] =
    {
        _HW_OTPFUSE_8BIT,
    };

    WORD code tOTPFUSE_STRADDR_OF_BANK[] =
    {
        0,
    };

    WORD code tOTPFUSE_ENDADDR_OF_BANK[] =
    {
        2047,
    };


    if(usLength != 0x00)
    {
        for(uci = 0; uci < _HW_OTPFUSE_TOTAL_BANK_NUM; uci++)
        {
            usCurrStart = tOTPFUSE_STRADDR_OF_BANK[uci];
            usCurrEnd = tOTPFUSE_ENDADDR_OF_BANK[uci];

            if((usStrAddr <= usCurrStart) && ((usStrAddr + usLength - 1) >= usCurrStart)) // start adress is the start of a bank
            {
                usOTPfuseBankRdStrAddr = 0x00;
            }
            else if((usCurrStart < usStrAddr) && (usStrAddr <= usCurrEnd)) // start adress is within the bank
            {
                usOTPfuseBankRdStrAddr = (usStrAddr - usCurrStart);
            }
            else
            {
                usOTPfuseBankRdStrAddr = 0x00; // no need to read within this bank
            }

            if((usStrAddr <= usCurrEnd) && ((usStrAddr + usLength - 1) >= usCurrEnd)) // end adress is at the last of a bank
            {
                usOTPfuseRdLength = (usCurrEnd - usCurrStart - usOTPfuseBankRdStrAddr + 1);
            }
            else if((usCurrStart <= (usStrAddr + usLength - 1)) && ((usStrAddr + usLength - 1) < usCurrEnd))
            {
                usOTPfuseRdLength = ((usStrAddr + usLength - 1) - usCurrStart - usOTPfuseBankRdStrAddr + 1); // end adress is within the bank
            }
            else
            {
                usOTPfuseRdLength = 0x00; // no need to read within this bank
            }

            if(usOTPfuseRdLength != 0x00)
            {
                ScalerOTPBankRead(tOTPFUSE_BITMODE_OF_BANK[uci], usOTPfuseBankRdStrAddr, usOTPfuseRdLength, &pucOTPfuseData[usOTPfuseRdLengthAcc]);
            }

            usOTPfuseRdLengthAcc = usOTPfuseRdLengthAcc + usOTPfuseRdLength;

            if(usOTPfuseRdLengthAcc >= usLength)
            {
                break;
            }
        }
    }
}

//--------------------------------------------------
// Description  : ScalerOTPFuseReadData
// Input Value  : enumOTPMemoryData, pucOTPfuseData
// Output Value : _SUCCESS, _FAIL
//--------------------------------------------------
bit ScalerOTPFuseReadData(EnumOTPMemoryData enumOTPMemoryData, BYTE *pucOTPfuseGetData)
{
    WORD usIndex = 0;

    for(usIndex = 0; usIndex < (sizeof(g_pstOTPMappingData) / sizeof(StructOTPMapping)); ++usIndex)
    {
        if(g_pstOTPMappingData[usIndex].enumDataId == enumOTPMemoryData)
        {
            ScalerOTPGetData(g_pstOTPMappingData[usIndex].usAddress,
                             g_pstOTPMappingData[usIndex].usLength,
                             pucOTPfuseGetData);
            return _SUCCESS;
        }
    }
    return _FAIL;
}

//--------------------------------------------------
// Description  : ScalerOTPFuseCheckDoneBit
// Input Value  : None
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerOTPFuseCheckDoneBit(void)
{
    BYTE ucCheckBit = 0;

    ScalerOTPFuseReadData(_OTPMEMORY_CHECK_EMPTY, &ucCheckBit);

    ucCheckBit = (ucCheckBit & (_BIT0 | _BIT1));

    // RL6952 only check FT done bit[1:0] = 0x01
    if(ucCheckBit == 0x01)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#if(_HW_FUSE_HDCP_1_4_RXKEY == _ON)
//--------------------------------------------------
// Description  : GET HDCP1.4 RX Key
// Input Value  : enumOTPfuseData, usSubAddr, usLength, pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerOTPFuseGetHdcp14RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    if(ScalerOTPFuseCheckDoneBit() == _TRUE)
    {
        if(enumOTPMemoryData == _OTPMEMORY_HDCP14_RXKEY)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP14_RXKEY_STR + usSubAddr), usLength, pucReadArray);
        }
        else if(enumOTPMemoryData == _OTPMEMORY_HDCP14_RXKEYBKSV)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP14_RXKEYBKSV_STR + usSubAddr), usLength, pucReadArray);
        }
    }
    else
    {
        DebugMessageDigital("OTP Fuse is empty!!!", 0);
    }
}
#endif

#if(_HW_FUSE_HDCP_1_4_TXKEY == _ON)
//--------------------------------------------------
// Description  : GET HDCP1.4 TX Key
// Input Value  : enumOTPfuseData, usSubAddr, usLength, pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerOTPFuseGetHdcp14TxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    if(ScalerOTPFuseCheckDoneBit() == _TRUE)
    {
        if(enumOTPMemoryData == _OTPMEMORY_HDCP14_TXKEY)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP14_TXKEY_STR + usSubAddr), usLength, pucReadArray);
        }
        else if(enumOTPMemoryData == _OTPMEMORY_HDCP14_TXKEYBKSV)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP14_TXKEYBKSV_STR + usSubAddr), usLength, pucReadArray);
        }
    }
    else
    {
        DebugMessageDigital("OTP Fuse is empty!!!", 0);
    }
}
#endif

#if(_HW_FUSE_HDCP_2_2_RXKEY == _ON)
//--------------------------------------------------
// Description  : GET HDCP2 RX Key
// Input Value  : enumOTPfuseData, usSubAddr, usLength, pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerOTPFuseGetHdcp22RxKey(EnumOTPMemoryData enumOTPMemoryData, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    if(ScalerOTPFuseCheckDoneBit() == _TRUE)
    {
        if(enumOTPMemoryData == _OTPMEMORY_HDCP22_RXKEY_CERTRX)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP22_RXKEY_CERTRX_STR + usSubAddr), usLength, pucReadArray);
        }
        else if(enumOTPMemoryData == _OTPMEMORY_HDCP22_RXKEY_KPRIV)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP22_RXKEY_KPRIV_STR + usSubAddr), usLength, pucReadArray);
        }
        else if(enumOTPMemoryData == _OTPMEMORY_HDCP22_RXKEY_RRMODN)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP22_RXKEY_RRMODN_STR + usSubAddr), usLength, pucReadArray);
        }
        else if(enumOTPMemoryData == _OTPMEMORY_HDCP22_RXKEY_NPINV)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP22_RXKEY_NPINV_STR + usSubAddr), usLength, pucReadArray);
        }
        else if(enumOTPMemoryData == _OTPMEMORY_HDCP22_RXKEY_DKEY)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP22_RXKEY_DKEY_STR + usSubAddr), usLength, pucReadArray);
        }
        else if(enumOTPMemoryData == _OTPMEMORY_HDCP22_RXKEY_LCKEY)
        {
            ScalerOTPGetData((_HW_OTPFUSE_HDCP22_RXKEY_LCKEY_STR + usSubAddr), usLength, pucReadArray);
        }
    }
    else
    {
        DebugMessageDigital("OTP Fuse is empty!!!", 0);
    }
}
#endif
#endif // End of #if(_HW_FUSE_TYPE == _OTPFUSE_TYPE)
