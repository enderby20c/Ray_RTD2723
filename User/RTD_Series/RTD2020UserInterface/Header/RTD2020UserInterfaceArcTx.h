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
// ID Code      : RTD2020UserInterfaceArcTx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
#if(_AUDIO_ARC_SUPPORT == _ON)
#define GET_ARC_TX_LINK_STATUS()                                (g_stArcTxUserInfo.enumArcLinkStatus)
#define SET_ARC_TX_LINK_STATUS(x)                               (g_stArcTxUserInfo.enumArcLinkStatus = (x))

#define GET_ARC_TX_EDID_TYPE()                                  (g_stArcTxUserInfo.enumArcEdidType)
#define SET_ARC_TX_EDID_TYPE(x)                                 (g_stArcTxUserInfo.enumArcEdidType = (x))

#if(_AUDIO_EARC_SUPPORT == _ON)
#define GET_ARC_TX_EARC_CDS_PARSE_DONE_EVER()                   (g_stArcTxUserInfo.b1EarcCdsParseDoneEver)
#define SET_ARC_TX_EARC_CDS_PARSE_DONE_EVER()                   (g_stArcTxUserInfo.b1EarcCdsParseDoneEver = _TRUE)
#define CLR_ARC_TX_EARC_CDS_PARSE_DONE_EVER()                   (g_stArcTxUserInfo.b1EarcCdsParseDoneEver = _FALSE)

#define GET_ARC_TX_EARC_CDS_PARSE_DONE()                        (g_stArcTxUserInfo.b1EarcCdsParseDone)
#define SET_ARC_TX_EARC_CDS_PARSE_DONE()                        (g_stArcTxUserInfo.b1EarcCdsParseDone = _TRUE)
#define CLR_ARC_TX_EARC_CDS_PARSE_DONE()                        (g_stArcTxUserInfo.b1EarcCdsParseDone = _FALSE)
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
#if(_AUDIO_ARC_SUPPORT == _ON)
typedef struct
{
#if(_AUDIO_EARC_SUPPORT == _ON)
    BYTE b1EarcCdsParseDoneEver : 1;
    BYTE b1EarcCdsParseDone : 1;
#endif
    EnumAudioArcMode enumArcLinkStatus;
    EnumEdidAudioType enumArcEdidType;
} StructArcTxUserInfo;
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

