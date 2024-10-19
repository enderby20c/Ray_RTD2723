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
// ID Code      : RTD2020UserInterfaceDscDecoder.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_FREESYNC__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceDscDecoder.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable Dsc Decoder or Not
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumDscDecoderSupport UserInterfaceDscDecoderGetEnable(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        if(GET_OSD_1P_DSC_PORT() == _DSC_OFF)
        {
            return _DSC_DECODER_SUPPORT_OFF;
        }
        else
        {
            return _DSC_DECODER_SUPPORT_ON;
        }
    }
    else
    {
#if(_DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT == _ON)
        if(GET_OSD_DSC_PORT() == _DSC_PORT_AUTO_SELECT)
        {
            return _DSC_DECODER_SUPPORT_ON;
        }
        else
        {
            return _DSC_DECODER_SUPPORT_OFF;
        }
#else
        switch(enumInputPort)
        {
            case _D0_INPUT_PORT:

                if(GET_OSD_DSC_PORT() == _DSC_FROM_D0_PORT)
                {
                    return _DSC_DECODER_SUPPORT_ON;
                }
                else
                {
                    return _DSC_DECODER_SUPPORT_OFF;
                }

                break;

            case _D1_INPUT_PORT:

                if(GET_OSD_DSC_PORT() == _DSC_FROM_D1_PORT)
                {
                    return _DSC_DECODER_SUPPORT_ON;
                }
                else
                {
                    return _DSC_DECODER_SUPPORT_OFF;
                }

                break;

            case _D2_INPUT_PORT:

                if(GET_OSD_DSC_PORT() == _DSC_FROM_D2_PORT)
                {
                    return _DSC_DECODER_SUPPORT_ON;
                }
                else
                {
                    return _DSC_DECODER_SUPPORT_OFF;
                }

                break;

            case _D3_INPUT_PORT:

                if(GET_OSD_DSC_PORT() == _DSC_FROM_D3_PORT)
                {
                    return _DSC_DECODER_SUPPORT_ON;
                }
                else
                {
                    return _DSC_DECODER_SUPPORT_OFF;
                }

                break;

            case _D4_INPUT_PORT:

                if(GET_OSD_DSC_PORT() == _DSC_FROM_D4_PORT)
                {
                    return _DSC_DECODER_SUPPORT_ON;
                }
                else
                {
                    return _DSC_DECODER_SUPPORT_OFF;
                }

                break;


            case _D5_INPUT_PORT:

                if(GET_OSD_DSC_PORT() == _DSC_FROM_D5_PORT)
                {
                    return _DSC_DECODER_SUPPORT_ON;
                }
                else
                {
                    return _DSC_DECODER_SUPPORT_OFF;
                }

                break;

            default:
                break;
        }
#endif
    }

    return _DSC_DECODER_SUPPORT_OFF;
}

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable MST2SST Branch Dsc Decoder or Not
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumDscDecoderSupport UserInterfaceDscDecoderMst2sstGetEnable(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        return _DSC_DECODER_SUPPORT_ON;
    }
    else
    {
        return _DSC_DECODER_SUPPORT_OFF;
    }
}
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserInterfaceDscDecoderGetEdidModifyParameter(StructDscHdmiEdidModifyParameter *pstructDscHdmiEdidModifyParameter)
{
    pstructDscHdmiEdidModifyParameter->b1Dsc10bpc = 1;
    pstructDscHdmiEdidModifyParameter->b1Dsc12bpc = 1;
    pstructDscHdmiEdidModifyParameter->b1DscAllBpp = 1;
    pstructDscHdmiEdidModifyParameter->b1DscNative420 = 1;
    pstructDscHdmiEdidModifyParameter->b4DscMaxFrlRate = 3;
    pstructDscHdmiEdidModifyParameter->b4DscMaxSlice = 4;
    pstructDscHdmiEdidModifyParameter->b6DscTotalChunkKByte = 22;
}
#endif

#endif // End of #if(_DSC_DECODER_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

