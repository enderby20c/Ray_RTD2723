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
// ID Code      : UserCommonEdid.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_EDID__

#include "UserCommonInclude.h"
#include "EDID/UserCommonEdid.h"

//--------------------------------------------------
// A0 EDID Location Check
//--------------------------------------------------
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
#if((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check A0 EDID table location!!!"
#endif
#endif

//--------------------------------------------------
// D0 EDID Location Check
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#if((_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D0 EDID table location!!!"
#endif

// D0 Multi Edid Check
#if(_D0_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: D0 External Edid's Index Should be 0~11 !!!"
#endif
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

// Dp AdaptiveSync EDID Size Check
#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE < _EDID_SIZE_384) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
#warning "NOTE: _D0_EMBEDDED_DDCRAM_MAX_SIZE Should Be 384 !!!"
#endif
//--------------------------------------------------
// D1 EDID Location Check
//--------------------------------------------------
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#if((_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D1 EDID table location!!!"
#endif

// D1 Multi Edid Check
#if(_D1_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: D1 External Edid's Index Should be 0~11 !!!"
#endif
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

// Dp AdaptiveSync EDID Size Check
#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE < _EDID_SIZE_384) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
#warning "NOTE: _D1_EMBEDDED_DDCRAM_MAX_SIZE Should Be 384 !!!"
#endif
//--------------------------------------------------
// D2 EDID Location Check
//--------------------------------------------------
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#if((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D2 EDID table location!!!"
#endif

// D2 Multi Edid Check
#if(_D2_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: D2 External Edid's Index Should be 0~11 !!!"
#endif
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

// Dp AdaptiveSync EDID Size Check
#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE < _EDID_SIZE_384) && (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))
#warning "NOTE: _D2_EMBEDDED_DDCRAM_MAX_SIZE Should Be 384 !!!"
#endif
//--------------------------------------------------
// D3 EDID Location Check
//--------------------------------------------------
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#if((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D3 EDID table location!!!"
#endif

// D3 Multi Edid Check
#if(_D3_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: D3 External Edid's Index Should be 0~11 !!!"
#endif
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


// Dp AdaptiveSync EDID Size Check
#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE < _EDID_SIZE_384))
#warning "NOTE: _D3_EMBEDDED_DDCRAM_MAX_SIZE Should Be 384 !!!"
#endif
//--------------------------------------------------
// D4 EDID Location Check
//--------------------------------------------------
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#if((_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D4 EDID table location!!!"
#endif

// D4 Multi Edid Check
#if(_D4_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: D4 External Edid's Index Should be 0~11 !!!"
#endif
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

// Dp AdaptiveSync EDID Size Check
#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE < _EDID_SIZE_384))
#warning "NOTE: _D4_EMBEDDED_DDCRAM_MAX_SIZE Should Be 384 !!!"
#endif
//--------------------------------------------------
// D5 EDID Location Check
//--------------------------------------------------
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#if((_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D5 EDID table location!!!"
#endif

// D5 Multi Edid Check
#if(_D5_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: D5 External Edid's Index Should be 0~11 !!!"
#endif
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

// Dp AdaptiveSync EDID Size Check
#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE < _EDID_SIZE_384))
#warning "NOTE: _D5_EMBEDDED_DDCRAM_MAX_SIZE Should Be 384 !!!"
#endif
//--------------------------------------------------
// Multi EDID All Switch Off Check
//--------------------------------------------------
#ifdef _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK
#warning "NOTE: _PCB_MULTI_EDID_ALL_SWITCH_OFF() Should Be Set when Support both Embedded Edid & External Edid!!!"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// EDID DATA TABLE
//--------------------------------------------------
#include "./EDID/EdidTableList.h"

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
#include "./EDID/EdidTableA0.h"
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#include "./EDID/EdidTableD0.h"
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#include "./EDID/EdidTableD1.h"
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#include "./EDID/EdidTableD2.h"
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#include "./EDID/EdidTableD3.h"
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#include "./EDID/EdidTableD4.h"
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#include "./EDID/EdidTableD5.h"
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
#include "./EDID/EdidTableD7.h"
#endif

#if(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
#include "./EDID/EdidTableD8.h"
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
#include "./EDID/EdidTableD9.h"
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_EMBEDDED_EDID_SUPPORT == _ON)
BYTE g_ucEdidChecksumFixed;
#if(_DUAL_DP_SUPPORT == _ON)
bit g_bEdidDpDualPortSwitchSelect = _FALSE;
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Online Modify Input Edid Content base on ModifyTarget
// Input Value  : pucEdidAddr; EnumEdidModifyTarget
// Output Value : _TRUE; _FALSE
//--------------------------------------------------
bit UserCommonEdidOnlineEdidModify(BYTE *pucEdidAddr, EnumEdidModifyTarget enumEdidModifyTarget)
{
    WORD pusCtaDataBlockAddr[_CTA_TOTAL_DB] = {0};

    // Check if there are Some Target Task need to modify
    if(enumEdidModifyTarget == 0x00)
    {
        return _FALSE;
    }

    // Scan & Get the DB Start Addr form Raw Edid
    ScalerSyncGetCtaExtDbAddress(pusCtaDataBlockAddr, pucEdidAddr);

    // -------------------------------------------------------
    // Modify Edid case by case
    // -------------------------------------------------------
#if(_EMBEDDED_EDID_SUPPORT == _ON)

#if(_HLG_SUPPORT == _ON)
    // Check HLG EDID Modify
    if(CHECK_EDID_MODIFY_TARGET(enumEdidModifyTarget, _EDID_MODIFY_HLG) == _TRUE)
    {
        if(UserCommonEdidHlgEdidModify(pucEdidAddr, pusCtaDataBlockAddr) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // Check DSC EDID Modify
    if(CHECK_EDID_MODIFY_TARGET(enumEdidModifyTarget, _EDID_MODIFY_HDMI_DSC) == _TRUE)
    {
        if(UserCommonEdidDscHdmiEdidModify(pucEdidAddr, pusCtaDataBlockAddr) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    // Check Freesync EDID MCCS Modify
    if(CHECK_EDID_MODIFY_TARGET(enumEdidModifyTarget, _EDID_MODIFY_HDMI_FREESYNC_MCCS) == _TRUE)
    {
        if(UserCommonEdidHdmiFreesyncModify(pucEdidAddr, pusCtaDataBlockAddr) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
    // Check EDID Audio Capability Modify
    if(CHECK_EDID_MODIFY_TARGET(enumEdidModifyTarget, _EDID_MODIFY_AUDIO_CAPABILITY) == _TRUE)
    {
        if(UserCommonArcTxEdidModify(pucEdidAddr, pusCtaDataBlockAddr) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Remove data block process
// Input Value  : pucDdcRamAddr; pusCtaDataBlockAddr, EnumEdidCtaDataBlock
// Output Value : None
//--------------------------------------------------
void UserCommonEdidRemoveCtaDataBlockProc(BYTE *pucDdcRamAddr, WORD *pusCtaDataBlockAddr, EnumEdidCtaDataBlock enumCtaDataBlock)
{
    // Check DataBlock Exist
    if(pusCtaDataBlockAddr[enumCtaDataBlock] != 0x00)
    {
        // if HF-EEODB, Db addr must in 0x84
        WORD usDbStartAddr = pusCtaDataBlockAddr[enumCtaDataBlock];
        BYTE ucRemoveDbSize = (pucDdcRamAddr[usDbStartAddr] & 0x1F) + 1;
        WORD usShiftDataStartAddr = usDbStartAddr + ucRemoveDbSize;
        WORD usCtaDbStartAddr = (usDbStartAddr >> _EDID_BLOCK_SIZE_BITWIDTH) << _EDID_BLOCK_SIZE_BITWIDTH;

        // Shift Edid Content
        memmove(&pucDdcRamAddr[usDbStartAddr], &pucDdcRamAddr[usShiftDataStartAddr], ((usCtaDbStartAddr + 0x7F) - usShiftDataStartAddr));

        // Zero padding
        memset(&pucDdcRamAddr[(usCtaDbStartAddr + 0x7F) - ucRemoveDbSize], 0x00, ucRemoveDbSize);

        // Repalce DTD Start Addr
        pucDdcRamAddr[usCtaDbStartAddr + _CTA_OFT_DTD_OFFSET] = pucDdcRamAddr[usCtaDbStartAddr + _CTA_OFT_DTD_OFFSET] - ucRemoveDbSize;

        // Shift the later Data Block
        UserCommonEdidShiftCtaDataBlockAddrProc(_DB_SHIFT_REMOVE, ucRemoveDbSize, pusCtaDataBlockAddr, enumCtaDataBlock);

        // Remove DataBlock from pusCtaDataBlockAddr
        pusCtaDataBlockAddr[enumCtaDataBlock] = 0x00;

        // Checksum modify - 1st Ext block
        UserCommonEdidCheckSumCal(pucDdcRamAddr, usCtaDbStartAddr);
        pucDdcRamAddr[usCtaDbStartAddr + 0x7F] = g_ucEdidChecksumFixed;
    }
}

//--------------------------------------------------
// Description  : Shift Data Block Address which follow base Data Block process
// Input Value  : enumShiftDir, LengthExtend, pusCtaDataBlockAddr; enumCtaBaseDataBlock
// Output Value : None
//--------------------------------------------------
void UserCommonEdidShiftCtaDataBlockAddrProc(EnumEdidDataBlockShiftDirect enumShiftDir, BYTE ucLengthExt, WORD *pusCtaDataBlockAddr, EnumEdidCtaDataBlock enumCtaBaseDataBlock)
{
    BYTE ucIdx = 0;

    for(ucIdx = 0; ucIdx < _CTA_TOTAL_DB; ucIdx++)
    {
        if(pusCtaDataBlockAddr[ucIdx] >= pusCtaDataBlockAddr[enumCtaBaseDataBlock])
        {
            if((EnumEdidCtaDataBlock)ucIdx == enumCtaBaseDataBlock)
            {
                // Find the block itself
                continue;
            }

            if(enumShiftDir == _DB_SHIFT_ADD)
            {
                pusCtaDataBlockAddr[ucIdx] = pusCtaDataBlockAddr[ucIdx] + ucLengthExt;
            }
            else if(enumShiftDir == _DB_SHIFT_REMOVE)
            {
                pusCtaDataBlockAddr[ucIdx] = pusCtaDataBlockAddr[ucIdx] - ucLengthExt;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Add data block process
// Input Value  : pucDdcRamAddr; pusCtaDataBlockAddr, enumCtaDataBlock, pucAddCtaDataBlock
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonEdidAddCtaDataBlockProc(BYTE *pucDdcRamAddr, WORD *pusCtaDataBlockAddr, EnumEdidCtaDataBlock enumCtaDataBlock, BYTE *pucAddCtaDataBlock)
{
    BYTE ucTempOffset = 0;
    BYTE ucDtdStartOffset = pusCtaDataBlockAddr[_FIRST_EXT_DTD_ADDR];
    BYTE ucCtaDbIdx = (BYTE)(ucDtdStartOffset >> _EDID_BLOCK_SIZE_BITWIDTH);
    WORD usCtaDbStartOffset = ucCtaDbIdx << _EDID_BLOCK_SIZE_BITWIDTH;
    WORD usCtaDbLastByteAddr = usCtaDbStartOffset + 0x7F;
    BYTE ucAddDataLength = (pucAddCtaDataBlock[0] & 0x1F) + 1; // including Header
    BYTE ucRemainLength = usCtaDbLastByteAddr - ucDtdStartOffset;
    BYTE pucDtdList[ucRemainLength];
    BYTE ucDtdNum = 0;

    DebugMessageSystem("EDID: ucDtdStartOffset", ucDtdStartOffset);
    DebugMessageSystem("EDID: ucAddDataLength", ucAddDataLength);

    if(ucDtdStartOffset == 0x00)
    {
        return _FALSE;
    }

    for(ucTempOffset = 0; ucTempOffset < ucRemainLength; ucTempOffset++)
    {
        pucDtdList[ucTempOffset] = pucDdcRamAddr[ucDtdStartOffset + ucTempOffset];
    }

    ucDtdNum = UserCommonEdidCntDtdNum(pucDtdList, ucRemainLength);
    ucRemainLength = ucRemainLength - (ucDtdNum * 18);

    DebugMessageSystem("EDID: ucDtdNum", ucDtdNum);
    DebugMessageSystem("EDID: ucRemainLength", ucRemainLength);

    // Make sure there is enough space
    // space not enough -> cancel DTD
    while((ucAddDataLength > ucRemainLength) && (ucDtdNum > 0))
    {
        ucDtdNum--;
        ucRemainLength += 18;
    }

    DebugMessageSystem("EDID: Remain ucDtdNum", ucDtdNum);

    if((ucDtdNum == 0) && (ucAddDataLength > ucRemainLength))
    {
        DebugMessageSystem("EDID: EDID No Space!!!", 0);

        return _FALSE;
    }
    else
    {
        BYTE ucTempLength = usCtaDbLastByteAddr - ucDtdStartOffset;

        // Clear DTDs
        for(ucTempOffset = 0; ucTempOffset < ucTempLength; ucTempOffset++)
        {
            pucDdcRamAddr[ucDtdStartOffset + ucTempOffset] = 0;
        }

        // Add Data Block
        for(ucTempOffset = 0; ucTempOffset < ucAddDataLength; ucTempOffset++)
        {
            pucDdcRamAddr[ucDtdStartOffset + ucTempOffset] = pucAddCtaDataBlock[ucTempOffset];
        }

        // Update Data Block Start Address
        pusCtaDataBlockAddr[enumCtaDataBlock] = ucDtdStartOffset;

        ucDtdStartOffset = ucDtdStartOffset + ucAddDataLength;
        ucAddDataLength = ucDtdNum * 18;

        // Recover DTDs
        for(ucTempOffset = 0; ucTempOffset < ucAddDataLength; ucTempOffset++)
        {
            pucDdcRamAddr[ucDtdStartOffset + ucTempOffset] = pucDtdList[ucTempOffset];
        }

        // Update Dtd Start Address
        pusCtaDataBlockAddr[_FIRST_EXT_DTD_ADDR] = ucDtdStartOffset;
        pucDdcRamAddr[usCtaDbStartOffset + 2] = ucDtdStartOffset - usCtaDbStartOffset;

        // CEA Extension General Info Support Basic Audio
        pucDdcRamAddr[usCtaDbStartOffset + 3] |= _BIT6;
    }

    // Checksum modify - 1st Ext block
    UserCommonEdidCheckSumCal(pucDdcRamAddr, usCtaDbStartOffset);
    pucDdcRamAddr[usCtaDbLastByteAddr] = g_ucEdidChecksumFixed;

    return _TRUE;
}

//--------------------------------------------------
// Description  : EDID Count DTD Number
// Input Value  : pucDtd, ucDtdLength
// Output Value : DTD Number
//--------------------------------------------------
BYTE UserCommonEdidCntDtdNum(BYTE *pucDtd, BYTE ucDtdLength)
{
    BYTE ucTempOffset = 0;
    BYTE ucCount = 0;
    BYTE ucDtdMaxNum = ucDtdLength / 18;
    BYTE ucDtdStartOffset = 18 * (ucDtdMaxNum - 1) + 1;
    BYTE pucDtdList[ucDtdLength];

    memcpy(pucDtdList, pucDtd, ucDtdLength);

    if(ucDtdLength >= 18)
    {
        for(ucTempOffset = 0; ucTempOffset < ucDtdStartOffset; ucTempOffset += 18)
        {
            if((pucDtdList[ucTempOffset] != 0) ||
               (pucDtdList[ucTempOffset + 1] != 0) ||
               (pucDtdList[ucTempOffset + 2] != 0) ||
               (pucDtdList[ucTempOffset + 3] != 0))
            {
                ucCount++;
            }
        }
    }

    return ucCount;
}


//--------------------------------------------------
// Description  : Calculate one block of EDID checksum
// Input Value  : Output Port, Start Address
// Output Value : None
//--------------------------------------------------
bit UserCommonEdidCheckSumCal(BYTE *pucDdcRamAddr, WORD usStartAddr)
{
    WORD usEDIDIndex = 0x0000;
    BYTE ucEDIDCheckSum = 0x00;

    for(usEDIDIndex = usStartAddr; usEDIDIndex <= (0x7F + usStartAddr); usEDIDIndex++)
    {
        ucEDIDCheckSum += pucDdcRamAddr[usEDIDIndex];

        if (usEDIDIndex == (0x7E + usStartAddr))
        {
            g_ucEdidChecksumFixed = 0x00 - ucEDIDCheckSum;
        }
        /*
        else if (ucEDIDIndex == 0xFE)
        {
            g_ucInternalExtendEDIDChecksumFixed = 0x00 - ucEDIDCheckSum;
        }
        else if (ucEDIDIndex == 0xFF)
        {
            break;
        }
        */
    }

    if (ucEDIDCheckSum != 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}

#if(_HLG_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modift Edid to HLG type
// Input Value  : pucEdidAddr, pusCtaDataBlockAddr
// Output Value : _FALSE: Modify Error!
//--------------------------------------------------
bit UserCommonEdidHlgEdidModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr)
{
    if(pusCtaDataBlockAddr[_CTA_SHDR_DB] == 0x00)
    {
        return _FALSE;
    }
    else
    {
        WORD usShdrDbStartAddr = pusCtaDataBlockAddr[_CTA_SHDR_DB];

        // Set ET_3 = 1
        pucEdidAddr[usShdrDbStartAddr + 2] |= _BIT3;

        // Calculate EDID Checksum
        UserCommonEdidCheckSumCal(pucEdidAddr, 0x80);

        // Modify EDID Checksum
        pucEdidAddr[0xFF] = g_ucEdidChecksumFixed;
    }

    return _TRUE;
}
#endif // End of #if(_HLG_SUPPORT == _ON)

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modift Edid to DSC type
// Input Value  : pucEdidAddr, pusCtaDataBlockAddr
// Output Value : _FALSE: Modify Error!
//--------------------------------------------------
bit UserCommonEdidDscHdmiEdidModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr)
{
    if(pusCtaDataBlockAddr[_CTA_HF_VSDB] == 0x00)
    {
        return _FALSE;
    }
    else
    {
        WORD usShdrDbStartAddr = pusCtaDataBlockAddr[_CTA_HF_VSDB];

        StructDscHdmiEdidModifyParameter structDscEdidModifyParameter = {0};

        // Get Dsc Modify Parameter
        UserInterfaceDscDecoderGetEdidModifyParameter(&structDscEdidModifyParameter);

        // Modify EDID w/ DSC Feature
        if((pucEdidAddr[usShdrDbStartAddr] & 0x1F) >= 13)
        {
            BYTE ucByte11 = (_BIT7 | (structDscEdidModifyParameter.b1DscNative420 << 6) | (structDscEdidModifyParameter.b1DscAllBpp << 3) |
                             (structDscEdidModifyParameter.b1Dsc12bpc << 1) | structDscEdidModifyParameter.b1Dsc10bpc);
            BYTE ucByte12 = ((structDscEdidModifyParameter.b4DscMaxFrlRate << 4) | structDscEdidModifyParameter.b4DscMaxSlice);
            BYTE ucByte13 = (structDscEdidModifyParameter.b6DscTotalChunkKByte);

            pucEdidAddr[usShdrDbStartAddr + 11] = ucByte11;
            pucEdidAddr[usShdrDbStartAddr + 12] = ucByte12;
            pucEdidAddr[usShdrDbStartAddr + 13] = ucByte13;

            // Calculate EDID Checksum
            UserCommonEdidCheckSumCal(pucEdidAddr, 0x80);

            // Modify EDID Checksum
            pucEdidAddr[0xFF] = g_ucEdidChecksumFixed;
        }
        else
        {
            return _FALSE;
        }
    }

    return _TRUE;
}
#endif // End of #if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modift Edid to DSC type
// Input Value  : pucEdidAddr, pusCtaDataBlockAddr
// Output Value : _FALSE: Modify Error!
//--------------------------------------------------
bit UserCommonEdidHdmiFreesyncModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr)
{
    if(pusCtaDataBlockAddr[_CTA_FS_DB] == 0x00)
    {
        return _FALSE;
    }
    else
    {
        WORD usShdrDbStartAddr = pusCtaDataBlockAddr[_CTA_FS_DB];

        pucEdidAddr[usShdrDbStartAddr + 8] = UserInterfaceFreeSyncGetHdmiMccsAddress();

        // Calculate EDID Checksum
        UserCommonEdidCheckSumCal(pucEdidAddr, 0x80);

        // Modify EDID Checksum
        pucEdidAddr[0xFF] = g_ucEdidChecksumFixed;
    }

    return _TRUE;
}
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)
#endif // End of #if((_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON))

#if(_EMBEDDED_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Edid Info Parse
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void UserCommonEdidEmbeddedInfoParser(EnumInputPort enumInputPort)
{
    WORD pusCtaDataBlockAddr[_CTA_TOTAL_DB] = {0};
    BYTE *pucEdidAddr = UserCommonEdidGetDDCRamAddress(enumInputPort);

#if(_FREESYNC_SUPPORT == _ON)
    EnumAmdVsdbVer enumAmdVer = _AMD_VER_NONE;
#endif

    // Scan & Get the DB Start Addr form Raw Edid
    ScalerSyncGetCtaExtDbAddress(pusCtaDataBlockAddr, pucEdidAddr);

#if(_FREESYNC_SUPPORT == _ON)
    if(pusCtaDataBlockAddr[_CTA_FS_DB] != 0)
    {
        WORD usAmdVsdbStartAddr = pusCtaDataBlockAddr[_CTA_FS_DB];
        enumAmdVer = (pucEdidAddr[usAmdVsdbStartAddr + 4]);
    }

    ScalerDrrSetAmdVsdbVer(enumInputPort, enumAmdVer);
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
    // reset EDID info for all HDMI Rx
    ScalerTmdsMacRxClrEdidVrrCapability(enumInputPort);

    if(pusCtaDataBlockAddr[_CTA_HF_VSDB] != 0)
    {
        WORD usHfVsdbStartAddr = pusCtaDataBlockAddr[_CTA_HF_VSDB];

        StructHdmi21EdidVrrCap stHdmi21EdidVrr;
        memset(&stHdmi21EdidVrr, 0, sizeof(stHdmi21EdidVrr));

        if((pucEdidAddr[usHfVsdbStartAddr] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) >= 8)
        {
            stHdmi21EdidVrr.b1EdidQms = ((pucEdidAddr[usHfVsdbStartAddr + 8] & _BIT6) >> 6);

            if((pucEdidAddr[usHfVsdbStartAddr] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) >= 10)
            {
                stHdmi21EdidVrr.ucEdidVrrMin = (pucEdidAddr[usHfVsdbStartAddr + 9] & (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                stHdmi21EdidVrr.usEdidVrrMax = (((pucEdidAddr[usHfVsdbStartAddr + 9] & (_BIT7 | _BIT6)) << 2) | (pucEdidAddr[usHfVsdbStartAddr + 10]));

                if((pucEdidAddr[usHfVsdbStartAddr] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) >= 11)
                {
                    stHdmi21EdidVrr.b1EdidQmsTfrMin = ((pucEdidAddr[usHfVsdbStartAddr + 11] & _BIT4) >> 4);
                    stHdmi21EdidVrr.b1EdidQmsTfrMax = ((pucEdidAddr[usHfVsdbStartAddr + 11] & _BIT5) >> 5);
                }
            }
        }

        ScalerTmdsMacRxSetEdidVrrCapability(enumInputPort, stHdmi21EdidVrr);
    }
#endif
}

//--------------------------------------------------
// Description  : Set Embedded EDID Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEdidLoadEmbeddedEdidData(void)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDPDualPortDefaultStatus enumDualPortStatus = UserInterfaceDpGetDualDefaultPort();
#endif

// A0 EDID-----------------------------------------------------------------------------------------------------------
#if((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonEdidLoadEmbeddedEdidDataByPort(_A0_INPUT_PORT_EDID);

    // DDC Force Nack Off
    ScalerMcuDdcSetForceNack(_A0_INPUT_PORT, _OFF);

#endif // End of #if((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D0 EDID-----------------------------------------------------------------------------------------------------------
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE))

    UserCommonEdidLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_EDID);

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    // Disable DDC0 Force Nack
    ScalerMcuDdcSetForceNack(_D0_INPUT_PORT, _OFF);

    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D0_INPUT_PORT, _ON);

    // Edid Parse Info (from DDCRAM only)
    UserCommonEdidEmbeddedInfoParser(_D0_INPUT_PORT);

#elif(_D0_HDMI_SUPPORT == _ON)

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D0_INPUT_PORT, _ON);
#endif

#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonEdidGetMultiHdmiEdidLocation(_D0_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D0_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC0 nack off
        ScalerMcuDdcSetForceNack(_D0_INPUT_PORT, _OFF);

        // Edid Parse Info (from DDCRAM only)
        UserCommonEdidEmbeddedInfoParser(_D0_INPUT_PORT);
    }
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#endif // End of #if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D1 EDID-----------------------------------------------------------------------------------------------------------
#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D7_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE) && (_D8_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE))

    UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    // Disable DDC1 Force Nack
    ScalerMcuDdcSetForceNack(_D1_INPUT_PORT, _OFF);

    // Disable Segment Control for Link Layer CTS
    ScalerMcuDdcSetSegmentSwitch(_D1_INPUT_PORT, _ON);

    // Edid Parse Info (from DDCRAM only)
    UserCommonEdidEmbeddedInfoParser(_D1_INPUT_PORT);

#elif(_D1_HDMI_SUPPORT == _ON)

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D1_INPUT_PORT, _ON);
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonEdidGetMultiHdmiEdidLocation(_D1_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D1_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC1 nack off
        ScalerMcuDdcSetForceNack(_D1_INPUT_PORT, _OFF);

        // Edid Parse Info (from DDCRAM only)
        UserCommonEdidEmbeddedInfoParser(_D1_INPUT_PORT);
    }
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#endif // End of #if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D2 EDID-----------------------------------------------------------------------------------------------------------
#if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D8_D2_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE))

    UserCommonEdidLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_EDID);

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    // Disable DDC1 Force Nack
    ScalerMcuDdcSetForceNack(_D2_INPUT_PORT, _OFF);

    // Disable Segment Control for Link Layer CTS
    ScalerMcuDdcSetSegmentSwitch(_D2_INPUT_PORT, _ON);

    // Edid Parse Info (from DDCRAM only)
    UserCommonEdidEmbeddedInfoParser(_D2_INPUT_PORT);

#elif(_D2_HDMI_SUPPORT == _ON)

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D2_INPUT_PORT, _ON);
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonEdidGetMultiHdmiEdidLocation(_D2_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D2_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC1 nack off
        ScalerMcuDdcSetForceNack(_D2_INPUT_PORT, _OFF);

        // Edid Parse Info (from DDCRAM only)
        UserCommonEdidEmbeddedInfoParser(_D2_INPUT_PORT);
    }
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#endif // End of #if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D3 EDID-----------------------------------------------------------------------------------------------------------
#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonEdidLoadEmbeddedEdidDataByPort(_D3_INPUT_PORT_EDID);

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D3_INPUT_PORT, _ON);
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonEdidGetMultiHdmiEdidLocation(_D3_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D3_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerMcuDdcSetForceNack(_D3_INPUT_PORT, _OFF);

        // Edid Parse Info (from DDCRAM only)
        UserCommonEdidEmbeddedInfoParser(_D3_INPUT_PORT);
    }
#endif // End of #if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D4 EDID-----------------------------------------------------------------------------------------------------------
#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonEdidLoadEmbeddedEdidDataByPort(_D4_INPUT_PORT_EDID);

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D4_INPUT_PORT, _ON);
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonEdidGetMultiHdmiEdidLocation(_D4_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D4_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerMcuDdcSetForceNack(_D4_INPUT_PORT, _OFF);

        // Edid Parse Info (from DDCRAM only)
        UserCommonEdidEmbeddedInfoParser(_D4_INPUT_PORT);
    }
#endif // End of #if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D5 EDID-----------------------------------------------------------------------------------------------------------
#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

    UserCommonEdidLoadEmbeddedEdidDataByPort(_D5_INPUT_PORT_EDID);

#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D5_INPUT_PORT, _ON);
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    if(UserCommonEdidGetMultiHdmiEdidLocation(_D5_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D5_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
#endif
    {
        // DDC Force Nack Off
        ScalerMcuDdcSetForceNack(_D5_INPUT_PORT, _OFF);

        // Edid Parse Info (from DDCRAM only)
        UserCommonEdidEmbeddedInfoParser(_D5_INPUT_PORT);
    }
#endif // End of #if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))

// D7 EDID-----------------------------------------------------------------------------------------------------------
#if((_D7_INPUT_PORT_TYPE == _D7_DP_PORT) && (_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))

    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        if(SysSourceGetInputPort() == _D7_INPUT_PORT)
        {
            SET_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D7_INPUT_PORT_EDID);
        }
        else if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D1_INPUT_PORT))
        {
            CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_EDID);
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
        }
        else
        {
            if(enumDualPortStatus == _DP_DUAL_PORT_USE_DUAL_PORT)
            {
                SET_DP_DUAL_PORT_EDID_STATUS_SELECT();
                UserCommonEdidLoadEmbeddedEdidDataByPort(_D7_INPUT_PORT_EDID);
            }
            else
            {
                CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
                UserCommonEdidLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_EDID);
                UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
            }
        }
    }
    else
    {
        CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
        UserCommonEdidLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_EDID);
        UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
    }

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    // Disable DDC0 Force Nack
    ScalerMcuDdcSetForceNack(_D0_INPUT_PORT, _OFF);

    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D0_INPUT_PORT, _ON);
#elif(_D0_HDMI_SUPPORT == _ON)
#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D0_INPUT_PORT, _ON);
#endif
    // DDC0 nack off
    ScalerMcuDdcSetForceNack(_D0_INPUT_PORT, _OFF);
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    // Disable DDC1 Force Nack
    ScalerMcuDdcSetForceNack(_D1_INPUT_PORT, _OFF);

    // Disable Segment Control for Link Layer CTS
    ScalerMcuDdcSetSegmentSwitch(_D1_INPUT_PORT, _ON);
#elif(_D1_HDMI_SUPPORT == _ON)
#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D1_INPUT_PORT, _ON);
#endif
    // DDC1 nack off
    ScalerMcuDdcSetForceNack(_D1_INPUT_PORT, _OFF);
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#endif // End of #if((_D7_INPUT_PORT_TYPE != _D7_NO_PORT) && (_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))

// D8 EDID-----------------------------------------------------------------------------------------------------------
#if((_D8_INPUT_PORT_TYPE == _D8_DP_PORT) && (_D8_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D8_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))

    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        if(SysSourceGetInputPort() == _D8_INPUT_PORT)
        {
            SET_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D8_INPUT_PORT_EDID);
        }
        else if((SysSourceGetInputPort() == _D1_INPUT_PORT) || (SysSourceGetInputPort() == _D2_INPUT_PORT))
        {
            CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_EDID);
        }
        else
        {
            if(enumDualPortStatus == _DP_DUAL_PORT_USE_DUAL_PORT)
            {
                SET_DP_DUAL_PORT_EDID_STATUS_SELECT();
                UserCommonEdidLoadEmbeddedEdidDataByPort(_D8_INPUT_PORT_EDID);
            }
            else
            {
                CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
                UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
                UserCommonEdidLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_EDID);
            }
        }
    }
    else
    {
        CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
        UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
        UserCommonEdidLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_EDID);
    }

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    // Disable DDC0 Force Nack
    ScalerMcuDdcSetForceNack(_D1_INPUT_PORT, _OFF);

    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D1_INPUT_PORT, _ON);
#elif(_D1_HDMI_SUPPORT == _ON)
#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D1_INPUT_PORT, _ON);
#endif
    // DDC0 nack off
    ScalerMcuDdcSetForceNack(_D1_INPUT_PORT, _OFF);
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    // Disable DDC1 Force Nack
    ScalerMcuDdcSetForceNack(_D2_INPUT_PORT, _OFF);

    // Disable Segment Control for Link Layer CTS
    ScalerMcuDdcSetSegmentSwitch(_D2_INPUT_PORT, _ON);
#elif(_D2_HDMI_SUPPORT == _ON)
#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384)
    // Enable Segment Control
    ScalerMcuDdcSetSegmentSwitch(_D2_INPUT_PORT, _ON);
#endif
    // DDC1 nack off
    ScalerMcuDdcSetForceNack(_D2_INPUT_PORT, _OFF);
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#endif // End of #if((_D8_INPUT_PORT_TYPE != _D8_NO_PORT) && (_D8_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D8_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))

// D9 EDID-----------------------------------------------------------------------------------------------------------
#if((_D9_INPUT_PORT_TYPE == _D9_DP_PORT) && (_D9_EMBEDDED_XRAM_MAX_SIZE != _EDID_SIZE_NONE))
    UserCommonEdidLoadEmbeddedEdidDataByPort(_D9_INPUT_PORT_EDID);

    // Not Need Edid Parse Info because Pxp Mode not support VRR
#endif
}

//--------------------------------------------------
// Description  : Set Embedded EDID Data for Input Port
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void UserCommonEdidLoadEmbeddedEdidDataByPort(EnumInputPortEdid enumInputPort)
{
    switch(enumInputPort)
    {
// A0 EDID-----------------------------------------------------------------------------------------------------------
#if((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _A0_INPUT_PORT_EDID:

#if(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_A0, tEDID_TABLE_A0, _A0_EMBEDDED_DDCRAM_MAX_SIZE);
#elif(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_A0_ADDRESS_EEPROM, _A0_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_A0);
#elif(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_A0_ADDRESS_FLASH), _A0_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_A0);
#elif(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_A0_INPUT_PORT_EDID);
#endif

            break;
#endif

// D0 EDID-----------------------------------------------------------------------------------------------------------
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D0_INPUT_PORT_EDID:

#if(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D0, tEDID_TABLE_D0, sizeof(tEDID_TABLE_D0));
#elif(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D0_ADDRESS_EEPROM, _D0_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D0);
#elif(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D0_ADDRESS_FLASH), _D0_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D0);
#elif(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D0_INPUT_PORT_EDID);
#endif

            break;
#endif

// D1 EDID-----------------------------------------------------------------------------------------------------------
#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D1_INPUT_PORT_EDID:

#if(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D1, tEDID_TABLE_D1, sizeof(tEDID_TABLE_D1));
#elif(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D1_ADDRESS_EEPROM, _D1_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D1);
#elif(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D1_ADDRESS_FLASH), _D1_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D1);
#elif(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D1_INPUT_PORT_EDID);
#endif

            break;
#endif

// D2 EDID-----------------------------------------------------------------------------------------------------------
#if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D2_INPUT_PORT_EDID:

#if(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D2, 0, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D2, tEDID_TABLE_D2, sizeof(tEDID_TABLE_D2));
#elif(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D2_ADDRESS_EEPROM, _D2_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D2);
#elif(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D2_ADDRESS_FLASH), _D2_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D2);
#elif(_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D2_INPUT_PORT_EDID);
#endif

            break;
#endif

// D3 EDID-----------------------------------------------------------------------------------------------------------
#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D3_INPUT_PORT_EDID:

#if(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D3, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D3, tEDID_TABLE_D3, sizeof(tEDID_TABLE_D3));
#elif(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D3_ADDRESS_EEPROM, _D3_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D3);
#elif(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D3_ADDRESS_FLASH), _D3_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D3);
#elif(_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D3_INPUT_PORT_EDID);
#endif

            break;
#endif

// D4 EDID-----------------------------------------------------------------------------------------------------------
#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D4_INPUT_PORT_EDID:

#if(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D4, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D4, tEDID_TABLE_D4, sizeof(tEDID_TABLE_D4));
#elif(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D4_ADDRESS_EEPROM, _D4_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D4);
#elif(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D4_ADDRESS_FLASH), _D4_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D4);
#elif(_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D4_INPUT_PORT_EDID);
#endif

            break;
#endif

// D5 EDID-----------------------------------------------------------------------------------------------------------
#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D5_INPUT_PORT_EDID:

#if(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memset(MCU_DDCRAM_D5, 0, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D5, tEDID_TABLE_D5, sizeof(tEDID_TABLE_D5));
#elif(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D5_ADDRESS_EEPROM, _D5_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D5);
#elif(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D5_ADDRESS_FLASH), _D5_EMBEDDED_DDCRAM_MAX_SIZE, MCU_DDCRAM_D5);
#elif(_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D5_INPUT_PORT_EDID);
#endif

            break;
#endif

// D7 EDID-----------------------------------------------------------------------------------------------------------
#if((_D7_INPUT_PORT_TYPE != _D7_NO_PORT) && (_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
        case _D7_INPUT_PORT_EDID:

#if(_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_D0, tEDID_TABLE_D7_D0, _D7_D0_EMBEDDED_DDCRAM_SIZE);
            memcpy(MCU_DDCRAM_D1, tEDID_TABLE_D7_D1, _D7_D1_EMBEDDED_DDCRAM_SIZE);
#elif(_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D7_D0_ADDRESS_EEPROM, _D7_D0_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_D0);
            UserCommonNVRamRead(_EDID_D7_D1_ADDRESS_EEPROM, _D7_D1_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_D1);
#elif(_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D7_D0_ADDRESS_FLASH), _D7_D0_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_D0);
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D7_D1_ADDRESS_FLASH), _D7_D1_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_D1);
#elif(_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D7_INPUT_PORT_EDID);
#endif
            break;
#endif

// D8 EDID-----------------------------------------------------------------------------------------------------------
#if((_D8_INPUT_PORT_TYPE != _D8_NO_PORT) && (_D8_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D8_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
        case _D8_INPUT_PORT_EDID:

#if(_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)
            memcpy(MCU_DDCRAM_D1, tEDID_TABLE_D8_D1, _D8_D1_EMBEDDED_DDCRAM_SIZE);
            memcpy(MCU_DDCRAM_D2, tEDID_TABLE_D8_D2, _D8_D2_EMBEDDED_DDCRAM_SIZE);
#elif(_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)
            UserCommonNVRamRead(_EDID_D8_D1_ADDRESS_EEPROM, _D8_D1_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_D1);
            UserCommonNVRamRead(_EDID_D8_D2_ADDRESS_EEPROM, _D8_D2_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_D2);
#elif(_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D8_D1_ADDRESS_FLASH), _D8_D1_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_D1);
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D8_D2_ADDRESS_FLASH), _D8_D2_EMBEDDED_DDCRAM_SIZE, MCU_DDCRAM_D2);
#elif(_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D8_INPUT_PORT_EDID);
#endif
            break;
#endif

#if((_DP_SUPPORT == _ON) && (_D9_INPUT_PORT_TYPE != _D9_NO_PORT) && (_D9_EMBEDDED_XRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D9_INPUT_PORT_EDID:

#if(_D9_EMBEDDED_XRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)

#if(_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            memset(g_pucDpRx0PxpEdid, 0, _D9_EMBEDDED_XRAM_MAX_SIZE);
            memcpy(g_pucDpRx0PxpEdid, tEDID_TABLE_D9, sizeof(tEDID_TABLE_D9));
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            memset(g_pucDpRx1PxpEdid, 0, _D9_EMBEDDED_XRAM_MAX_SIZE);
            memcpy(g_pucDpRx1PxpEdid, tEDID_TABLE_D9, sizeof(tEDID_TABLE_D9));
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            memset(g_pucDpRx2PxpEdid, 0, _D9_EMBEDDED_XRAM_MAX_SIZE);
            memcpy(g_pucDpRx2PxpEdid, tEDID_TABLE_D9, sizeof(tEDID_TABLE_D9));
#endif
#else
            memset(g_pucDpRxPxpEdid, 0, _D9_EMBEDDED_XRAM_MAX_SIZE);
            memcpy(g_pucDpRxPxpEdid, tEDID_TABLE_D9, sizeof(tEDID_TABLE_D9));
#endif

#elif(_D9_EMBEDDED_XRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)

#if(_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            UserCommonNVRamRead(_EDID_D9_ADDRESS_EEPROM, _D9_EMBEDDED_XRAM_MAX_SIZE, g_pucDpRx0PxpEdid);
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            UserCommonNVRamRead(_EDID_D9_ADDRESS_EEPROM, _D9_EMBEDDED_XRAM_MAX_SIZE, g_pucDpRx1PxpEdid);
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            UserCommonNVRamRead(_EDID_D9_ADDRESS_EEPROM, _D9_EMBEDDED_XRAM_MAX_SIZE, g_pucDpRx2PxpEdid);
#endif
#else
            UserCommonNVRamRead(_EDID_D9_ADDRESS_EEPROM, _D9_EMBEDDED_XRAM_MAX_SIZE, g_pucDpRxPxpEdid);
#endif

#elif((_D9_EMBEDDED_XRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) && (_FLASH_READ_FUNCTION_SUPPORT == _ON))

#if(_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D9_ADDRESS_FLASH), _D9_EMBEDDED_XRAM_MAX_SIZE, g_pucDpRx0PxpEdid);
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D9_ADDRESS_FLASH), _D9_EMBEDDED_XRAM_MAX_SIZE, g_pucDpRx1PxpEdid);
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D9_ADDRESS_FLASH), _D9_EMBEDDED_XRAM_MAX_SIZE, g_pucDpRx2PxpEdid);
#endif
#else
            UserCommonFlashRead(_EDID_FLASH_BANK, (_EDID_D9_ADDRESS_FLASH), _D9_EMBEDDED_XRAM_MAX_SIZE, g_pucDpRxPxpEdid);
#endif

#elif(_D9_EMBEDDED_XRAM_LOCATION == _EDID_TABLE_LOCATION_USER)
            UserInterfaceEdidGetEmbeddedEdidData(_D9_INPUT_PORT_EDID);
#endif

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get HDMI EDID DDC Ram Address
// Input Value  : enumInputPort --> target input port
// Output Value : DDCRAM pointer
//--------------------------------------------------
BYTE *UserCommonEdidGetDDCRamAddress(EnumInputPort enumInputPort)
{
    EnumPortType enumPortType = SysSourceGetPortTypeFromInputPort(enumInputPort);

    if(enumPortType == _PORT_HDMI)
    {
        // Check Current Edid is embedded
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
        if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, UserInterfaceEdidGetMultiHdmiEdidIndex(enumInputPort)) == _HDMI_EDID_EMBEDDED)
#endif
        {
            switch(enumInputPort)
            {
#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
                case _D1_INPUT_PORT:

                    return MCU_DDCRAM_D1;
#endif
#endif

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D2_DDC_CHANNEL_SEL == _DDC2)
                case _D2_INPUT_PORT:

                    return MCU_DDCRAM_D2;
#endif
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D3_DDC_CHANNEL_SEL == _DDC3)
                case _D3_INPUT_PORT:

                    return MCU_DDCRAM_D3;
#endif
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D4_DDC_CHANNEL_SEL == _DDC4)
                case _D4_INPUT_PORT:

                    return MCU_DDCRAM_D4;
#endif
#endif

#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D5_DDC_CHANNEL_SEL == _DDC5)
                case _D5_INPUT_PORT:

                    return MCU_DDCRAM_D5;
#endif
#endif

                default:
                    break;
            }
        }
    }
    else if(enumPortType == _PORT_DP)
    {
        switch(enumInputPort)
        {
#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
            case _D0_INPUT_PORT:

                return MCU_DDCRAM_D0;
#endif
#endif

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
            case _D1_INPUT_PORT:

                return MCU_DDCRAM_D1;
#endif
#endif

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D2_DDC_CHANNEL_SEL == _DDC2)
            case _D2_INPUT_PORT:

                return MCU_DDCRAM_D2;
#endif
#endif

            default:
                break;
        }
    }

    return _NULL_POINTER;
}

#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) || (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)))
//--------------------------------------------------
// Description  : Reload HDMI EDID
// Input Value  : enumInputPort --> switch target
// Output Value : None
//--------------------------------------------------
void UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(EnumInputPort enumInputPort)
{
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
#if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
    // Check for Ddc Busy
    ScalerTmdsMacRxDdcCheckBusy(_D4_INPUT_PORT, _DELAY_20US_TIMESCALE, 1, 1500);
#endif

    // Enable D4 DDCRAM Force Nack
    ScalerMcuDdcSetForceNack(_D4_INPUT_PORT, _ON);

    // Reload EDID
    UserInterfaceEdidReloadHdmiExternalSwitchEmbeddedEdid(enumInputPort);

    // Disable D4 DDCRAM Force Nack
    ScalerMcuDdcSetForceNack(_D4_INPUT_PORT, _OFF);

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
    // Check for Ddc Busy
    ScalerTmdsMacRxDdcCheckBusy(_D3_INPUT_PORT, _DELAY_20US_TIMESCALE, 1, 1500);
#endif

    // Enable D3 DDCRAM Force Nack
    ScalerMcuDdcSetForceNack(_D3_INPUT_PORT, _ON);

    // Reload EDID
    UserInterfaceEdidReloadHdmiExternalSwitchEmbeddedEdid(enumInputPort);

    // Disable D3 DDCRAM Force Nack
    ScalerMcuDdcSetForceNack(_D3_INPUT_PORT, _OFF);
#endif
}
#endif
#endif // End of #if(_EMBEDDED_EDID_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check Current HDMI EDID Location
// Input Value  : enumInputPort
// Output Value : EnumEdidSelection
//--------------------------------------------------
EnumHdmiEdidLocation UserCommonEdidCheckHdmiCurrentEdidLocation(EnumInputPort enumInputPort)
{
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    EnumEdidSelection enumEdidSel = UserInterfaceEdidGetMultiHdmiEdidIndex(enumInputPort);
#endif

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumEdidSel) == _HDMI_EDID_EXTERNAL)
            {
                return _HDMI_EDID_EXTERNAL;
            }
            else
            {
                return _HDMI_EDID_EMBEDDED;
            }
#elif(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
            return _HDMI_EDID_EMBEDDED;
#else
            return _HDMI_EDID_EXTERNAL;
#endif
            break;

        case _D1_INPUT_PORT:
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumEdidSel) == _HDMI_EDID_EXTERNAL)
            {
                return _HDMI_EDID_EXTERNAL;
            }
            else
            {
                return _HDMI_EDID_EMBEDDED;
            }
#elif(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
            return _HDMI_EDID_EMBEDDED;
#else
            return _HDMI_EDID_EXTERNAL;
#endif
            break;

        case _D2_INPUT_PORT:
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumEdidSel) == _HDMI_EDID_EXTERNAL)
            {
                return _HDMI_EDID_EXTERNAL;
            }
            else
            {
                return _HDMI_EDID_EMBEDDED;
            }
#elif(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
            return _HDMI_EDID_EMBEDDED;
#else
            return _HDMI_EDID_EXTERNAL;
#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumEdidSel) == _HDMI_EDID_EXTERNAL)
            {
                return _HDMI_EDID_EXTERNAL;
            }
            else
            {
                return _HDMI_EDID_EMBEDDED;
            }
#elif(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
            return _HDMI_EDID_EMBEDDED;
#else
            return _HDMI_EDID_EXTERNAL;
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumEdidSel) == _HDMI_EDID_EXTERNAL)
            {
                return _HDMI_EDID_EXTERNAL;
            }
            else
            {
                return _HDMI_EDID_EMBEDDED;
            }
#elif(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
            return _HDMI_EDID_EMBEDDED;
#else
            return _HDMI_EDID_EXTERNAL;
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumEdidSel) == _HDMI_EDID_EXTERNAL)
            {
                return _HDMI_EDID_EXTERNAL;
            }
            else
            {
                return _HDMI_EDID_EMBEDDED;
            }
#elif(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
            return _HDMI_EDID_EMBEDDED;
#else
            return _HDMI_EDID_EXTERNAL;
#endif
            break;

        default:
            break;
    }

    return _HDMI_EDID_EXTERNAL;
}

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch HDMI EDID from user OSD
// Input Value  : enumInputPort --> switch target
//                enumHDMIEDIDSelection --> Edid Index
// Output Value : None
//--------------------------------------------------
void UserCommonEdidSwitchHdmiEdid(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection)
{
    EnumTMDSHpdEventType enumHpdEventType = ((UserInterfaceEdidGetHpdToggleResetToSearch() == _EDID_HPD_RETURN_SEARCH) ? _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH : _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE);

    if(UserCommonEdidCheckMultiEdidSupport(enumInputPort) == _TRUE)
    {
        // Before Reload Edid Process
        UserCommonEdidBeforeReloadHdmiEdidProc(enumInputPort, enumHDMIEDIDSelection);

        // Reload Edid Process
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
        UserCommonEdidReloadHdmiEdid(enumInputPort);
#endif

        // After Reload Edid Process
        UserCommonEdidAfterReloadHdmiEdidProc(enumInputPort, enumHDMIEDIDSelection);

        // Edid Parser for New Edid
#if(_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE)
        if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumHDMIEDIDSelection) == _HDMI_EDID_EXTERNAL)
        {
            // Edid Parse don't support External
            UserCommonEdidHdmiExternalInfoParser(enumInputPort);
        }
        else
#endif
        {
            // Edid Parse Info (from DDCRAM only)
            UserCommonEdidEmbeddedInfoParser(enumInputPort);
        }

        // HPD Trigger Event Set
        ScalerTmdsMacRxEdidSwitch(enumInputPort, enumHpdEventType);
    }
    else
    {
        DebugMessageSystem("Current InputPort Not Support Multi-Edid Switch", enumInputPort);
    }
}

#if((_TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch HDMI EDID from user OSD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEdidSwitchHdmiAllPortEdidToggleTargetPortHpd(void)
{
    EnumInputPort enumFreesyncTargetPort = SysSourceGetFreesyncInputPort();

#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D0_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D0_INPUT_PORT));

    if(enumFreesyncTargetPort != _D0_INPUT_PORT)
    {
        ScalerTmdsMacRxClrHPDTriggerEvent(_D0_INPUT_PORT);
    }
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D1_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D1_INPUT_PORT));

    if(enumFreesyncTargetPort != _D1_INPUT_PORT)
    {
        ScalerTmdsMacRxClrHPDTriggerEvent(_D1_INPUT_PORT);
    }
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D2_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D2_INPUT_PORT));

    if(enumFreesyncTargetPort != _D2_INPUT_PORT)
    {
        ScalerTmdsMacRxClrHPDTriggerEvent(_D2_INPUT_PORT);
    }
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D3_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D3_INPUT_PORT));

    if(enumFreesyncTargetPort != _D3_INPUT_PORT)
    {
        ScalerTmdsMacRxClrHPDTriggerEvent(_D3_INPUT_PORT);
    }
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D4_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D4_INPUT_PORT));

    if(enumFreesyncTargetPort != _D4_INPUT_PORT)
    {
        ScalerTmdsMacRxClrHPDTriggerEvent(_D4_INPUT_PORT);
    }
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D5_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D5_INPUT_PORT));

    if(enumFreesyncTargetPort != _D5_INPUT_PORT)
    {
        ScalerTmdsMacRxClrHPDTriggerEvent(_D5_INPUT_PORT);
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Switch HDMI EDID from user OSD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEdidSwitchHdmiAllPortEdid(void)
{
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D0_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D0_INPUT_PORT));
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D1_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D1_INPUT_PORT));
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D2_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D2_INPUT_PORT));
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D3_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D3_INPUT_PORT));
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D4_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D4_INPUT_PORT));
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    UserCommonEdidSwitchHdmiEdid(_D5_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D5_INPUT_PORT));
#endif
}

//--------------------------------------------------
// Description  : Get the HDMI Port Edid location
// Input Value  : enumInputPort --> target port
//                enumHDMIEDIDSelection --> EDID selection id
// Output Value : location of the Edid index
//--------------------------------------------------
EnumHdmiEdidLocation UserCommonEdidGetMultiHdmiEdidLocation(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection)
{
    bit bDxMultiEdidSupport = _TRUE;

    // Check Dx MultiEdid Support or not
    switch(enumInputPort)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
        case _D0_INPUT_PORT:
            bDxMultiEdidSupport = _FALSE;
            break;
#endif
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
        case _D1_INPUT_PORT:
            bDxMultiEdidSupport = _FALSE;
            break;
#endif
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
        case _D2_INPUT_PORT:
            bDxMultiEdidSupport = _FALSE;
            break;
#endif
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
        case _D3_INPUT_PORT:
            bDxMultiEdidSupport = _FALSE;
            break;
#endif
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
        case _D4_INPUT_PORT:
            bDxMultiEdidSupport = _FALSE;
            break;
#endif
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
        case _D5_INPUT_PORT:
            bDxMultiEdidSupport = _FALSE;
            break;
#endif

        default:
            break;
    }


    if((bDxMultiEdidSupport == _TRUE) && (enumHDMIEDIDSelection < _HDMI_EXT_EDID_MAX_CNT))
    {
        BYTE ucPortIndex = (enumInputPort - _D0_INPUT_PORT);
        return UserInterfaceEdidGetMultiHdmiEdidLocation(ucPortIndex, enumHDMIEDIDSelection);
    }

    return _HDMI_EDID_EMBEDDED;
}

//--------------------------------------------------
// Description  : Get the HDMI Port Edid Max Count
// Input Value  : enumInputPort --> target port
// Output Value : Max Cnt of the Port
//--------------------------------------------------
BYTE UserCommonEdidGetHdmiEdidCount(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return _D0_MAX_HDMI_EDID_COUNT;
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return _D1_MAX_HDMI_EDID_COUNT;
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return _D2_MAX_HDMI_EDID_COUNT;
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return _D3_MAX_HDMI_EDID_COUNT;
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return _D4_MAX_HDMI_EDID_COUNT;
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return _D5_MAX_HDMI_EDID_COUNT;
#endif

        default:
            return 1;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Check Multi EDID Support
// Input Value  : enumInputPort
// Output Value : True/False
//--------------------------------------------------
bit UserCommonEdidCheckMultiEdidSupport(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return _TRUE;
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return _TRUE;
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return _TRUE;
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return _TRUE;
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return _TRUE;
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return _TRUE;
#endif

        default:
            return _FALSE;
    }
    return _FALSE;
}

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch HDMI EDID process -- Reload Edid
// Input Value  : enumInputPort --> target port
// Output Value : None
//--------------------------------------------------
void UserCommonEdidReloadHdmiEdid(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if((_D0_HDMI_SUPPORT == _ON) &&\
    (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D0_INPUT_PORT:

            UserInterfaceEdidGetEmbeddedEdidData(_D0_INPUT_PORT_EDID);

            break;
#endif

#if((_D1_HDMI_SUPPORT == _ON) &&\
    (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D1_INPUT_PORT:

            UserInterfaceEdidGetEmbeddedEdidData(_D1_INPUT_PORT_EDID);

            break;
#endif

#if((_D2_HDMI_SUPPORT == _ON) &&\
    (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D2_INPUT_PORT:

            UserInterfaceEdidGetEmbeddedEdidData(_D2_INPUT_PORT_EDID);

            break;
#endif

#if((_D3_HDMI_SUPPORT == _ON) &&\
    (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D3_INPUT_PORT:

            UserInterfaceEdidGetEmbeddedEdidData(_D3_INPUT_PORT_EDID);

            break;
#endif

#if((_D4_HDMI_SUPPORT == _ON) &&\
    (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D4_INPUT_PORT:

            UserInterfaceEdidGetEmbeddedEdidData(_D4_INPUT_PORT_EDID);

            break;
#endif

#if((_D5_HDMI_SUPPORT == _ON) &&\
    (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER) &&\
    (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
        case _D5_INPUT_PORT:

            UserInterfaceEdidGetEmbeddedEdidData(_D5_INPUT_PORT_EDID);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Switch HDMI EDID process before reload Edid
// Input Value  : enumInputPort --> target port
//                enumHDMIEDIDSelection --> Edid Index
// Output Value : None
//--------------------------------------------------
void UserCommonEdidBeforeReloadHdmiEdidProc(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection)
{
    bit b1DdcStatus = 0;

    b1DdcStatus = ScalerMcuDdcGetForceNackStatus(enumInputPort);

    // Check for Ddc Busy
    ScalerTmdsMacRxDdcCheckBusy(enumInputPort, _DELAY_20US_TIMESCALE, 1, 1500);

#if(_EMBEDDED_EDID_SUPPORT == _ON)
    ScalerMcuDdcSetForceNack(enumInputPort, _ON);
#endif

    if(b1DdcStatus == _FALSE)
    {
        BYTE ucEdidCount = UserCommonEdidGetHdmiEdidCount(enumInputPort);

        if(ucEdidCount > 1)
        {
            if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumHDMIEDIDSelection) != _HDMI_EDID_EXTERNAL)
            {
                BYTE ucTempEEPROM = 0;
                BYTE ucLoopStop = MINOF(ucEdidCount, _HDMI_EXT_EDID_MAX_CNT);

                for(; ucTempEEPROM < ucLoopStop; ++ucTempEEPROM)
                {
                    if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, ucTempEEPROM) == _HDMI_EDID_EXTERNAL)
                    {
                        UserCommonEdidSwitchMultiHdmiEeprom(enumInputPort, ucTempEEPROM);
                        break;
                    }
                }
            }
        }
    }
}


//--------------------------------------------------
// Description  : Switch HDMI EDID process after reload Edid
// Input Value  : enumInputPort --> target port
//                enumHDMIEDIDSelection --> Edid Index
// Output Value : None
//--------------------------------------------------
void UserCommonEdidAfterReloadHdmiEdidProc(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection)
{
    BYTE ucEdidCount = UserCommonEdidGetHdmiEdidCount(enumInputPort);

    // If Target Edid: External--> Open the Target Eeprom
    UserCommonEdidSwitchMultiHdmiEeprom(enumInputPort, enumHDMIEDIDSelection);

    if(ucEdidCount > 1)
    {
        if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumHDMIEDIDSelection) != _HDMI_EDID_EXTERNAL)
        {
#if(_EMBEDDED_EDID_SUPPORT == _ON)
            ScalerMcuDdcSetForceNack(enumInputPort, _OFF);
#endif
        }
    }
}

//--------------------------------------------------
// Description  : All port external EDID switch turn on/off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEdidMultiHdmiEdidInitial(void)
{
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D0 External Edid Config Setting
    UserCommonEdidSwitchMultiHdmiEeprom(_D0_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D0_INPUT_PORT));
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D1 External Edid Config Setting
    UserCommonEdidSwitchMultiHdmiEeprom(_D1_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D1_INPUT_PORT));
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D2 External Edid Config Setting
    UserCommonEdidSwitchMultiHdmiEeprom(_D2_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D2_INPUT_PORT));
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D3 External Edid Config Setting
    UserCommonEdidSwitchMultiHdmiEeprom(_D3_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D3_INPUT_PORT));
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D4 External Edid Config Setting
    UserCommonEdidSwitchMultiHdmiEeprom(_D4_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D4_INPUT_PORT));
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    // D5 External Edid Config Setting
    UserCommonEdidSwitchMultiHdmiEeprom(_D5_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D5_INPUT_PORT));
#endif
}

//--------------------------------------------------
// Description  : Multi Edid switch
// Input Value  : Input TMDS Port
//                enumHDMIEDIDSelection --> Edid Index
// Output Value : None
//--------------------------------------------------
void UserCommonEdidSwitchMultiHdmiEeprom(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection)
{
    BYTE ucEdidCount = UserCommonEdidGetHdmiEdidCount(enumInputPort);

    if(ucEdidCount > 1)
    {
        PCB_MULTI_EDID_SWITCH(enumInputPort, enumHDMIEDIDSelection);

        if(UserCommonEdidGetMultiHdmiEdidLocation(enumInputPort, enumHDMIEDIDSelection) != _HDMI_EDID_EXTERNAL)
        {
            // Turn off All External Edid's GPO
            PCB_MULTI_EDID_ALL_SWITCH_OFF(enumInputPort);
        }
    }
}

#endif // End of #if(_HDMI_MULTI_EDID_SUPPORT == _ON)

#if((_HDMI_SUPPORT == _ON) && (_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE))
//--------------------------------------------------
// Description  : All port external EDID Parser
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEdidHdmiAllPortExternalEdidParser(void)
{
#if(_D0_HDMI_SUPPORT == _ON)
    UserCommonEdidHdmiExternalInfoParser(_D0_INPUT_PORT);
#endif
#if(_D1_HDMI_SUPPORT == _ON)
    UserCommonEdidHdmiExternalInfoParser(_D1_INPUT_PORT);
#endif
#if(_D2_HDMI_SUPPORT == _ON)
    UserCommonEdidHdmiExternalInfoParser(_D2_INPUT_PORT);
#endif
#if(_D3_HDMI_SUPPORT == _ON)
    UserCommonEdidHdmiExternalInfoParser(_D3_INPUT_PORT);
#endif
#if(_D4_HDMI_SUPPORT == _ON)
    UserCommonEdidHdmiExternalInfoParser(_D4_INPUT_PORT);
#endif
#if(_D5_HDMI_SUPPORT == _ON)
    UserCommonEdidHdmiExternalInfoParser(_D5_INPUT_PORT);
#endif
}

//--------------------------------------------------
// Description  : External EDID Parser
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEdidHdmiExternalInfoParser(EnumInputPort enumInputPort)
{
    if(UserCommonEdidCheckHdmiCurrentEdidLocation(enumInputPort) == _HDMI_EDID_EXTERNAL)
    {
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
        BYTE pucEdidContent[_EDID_EXTERNAL_EEPROM_MAX_SIZE] = {0};
        WORD pusCtaDataBlockAddr[_CTA_TOTAL_DB] = {0};
#endif
        // ----------------------------
        // Case by case to parser info
        // ----------------------------
#if(_HDMI_FREESYNC_SUPPORT == _ON)
        EnumAmdVsdbVer enumAmdVer = _AMD_VER_NONE;

        // Get Edid Content
        UserInterfaceEdidGetExternalEdid(enumInputPort, pucEdidContent);

        // Scan & Get the DB Start Addr form Raw Edid
        ScalerSyncGetCtaExtDbAddress(pusCtaDataBlockAddr, pucEdidContent);

        if(pusCtaDataBlockAddr[_CTA_FS_DB] != 0)
        {
            WORD usAmdVsdbStartAddr = pusCtaDataBlockAddr[_CTA_FS_DB];
            enumAmdVer = (pucEdidContent[usAmdVsdbStartAddr + 4]);
        }

        ScalerDrrSetAmdVsdbVer(enumInputPort, enumAmdVer);
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
        // reset EDID info for all HDMI Rx
        ScalerTmdsMacRxClrEdidVrrCapability(enumInputPort);

        if(pusCtaDataBlockAddr[_CTA_HF_VSDB] != 0)
        {
            WORD usHfVsdbStartAddr = pusCtaDataBlockAddr[_CTA_HF_VSDB];

            StructHdmi21EdidVrrCap stHdmi21EdidVrr;
            memset(&stHdmi21EdidVrr, 0, sizeof(stHdmi21EdidVrr));

            if((pucEdidContent[usHfVsdbStartAddr] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) >= 8)
            {
                stHdmi21EdidVrr.b1EdidQms = ((pucEdidContent[usHfVsdbStartAddr + 8] & _BIT6) >> 6);

                if((pucEdidContent[usHfVsdbStartAddr] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) >= 10)
                {
                    stHdmi21EdidVrr.ucEdidVrrMin = (pucEdidContent[usHfVsdbStartAddr + 9] & (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    stHdmi21EdidVrr.usEdidVrrMax = (((pucEdidContent[usHfVsdbStartAddr + 9] & (_BIT7 | _BIT6)) << 2) | (pucEdidContent[usHfVsdbStartAddr + 10]));

                    if((pucEdidContent[usHfVsdbStartAddr] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) >= 11)
                    {
                        stHdmi21EdidVrr.b1EdidQmsTfrMin = ((pucEdidContent[usHfVsdbStartAddr + 11] & _BIT4) >> 4);
                        stHdmi21EdidVrr.b1EdidQmsTfrMax = ((pucEdidContent[usHfVsdbStartAddr + 11] & _BIT5) >> 5);
                    }
                }
            }

            ScalerTmdsMacRxSetEdidVrrCapability(enumInputPort, stHdmi21EdidVrr);
        }
#endif
    }
}
#endif

#if(_DP_SUPPORT == _ON)
#if(_EMBEDDED_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP EDID Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEdidSwitchDpEdid(BYTE ucSelectedPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDPDualPortDefaultStatus enumDualPortStatus = UserInterfaceDpGetDualDefaultPort();
#endif

    switch(ucSelectedPort)
    {
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

        case _D7_INPUT_PORT:

            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
            {
                if((SysSourceGetInputPort() == _D7_INPUT_PORT) ||
                   ((SysSourceGetInputPort() != _D0_INPUT_PORT) &&
                    (SysSourceGetInputPort() != _D1_INPUT_PORT) &&
                    (enumDualPortStatus == _DP_DUAL_PORT_USE_DUAL_PORT)))
                {
#if(_AUDIO_SUPPORT == _ON)
                    // Mute Audio Output
                    UserCommonAudioMuteCurrentDigitalPortProc(_D7_DP_PORT);
#endif
                    UserCommonEdidLoadEmbeddedEdidDataByPort(_D7_INPUT_PORT_EDID);
                    ScalerDpRxEdidSwitch(_D7_INPUT_PORT);
                }
            }

            break;
#endif

#if(_D8_INPUT_PORT_TYPE == _D8_DP_PORT)

        case _D8_INPUT_PORT:

            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
            {
                if((SysSourceGetInputPort() == _D8_INPUT_PORT) ||
                   ((SysSourceGetInputPort() != _D1_INPUT_PORT) &&
                    (SysSourceGetInputPort() != _D2_INPUT_PORT) &&
                    (enumDualPortStatus == _DP_DUAL_PORT_USE_DUAL_PORT)))
                {
#if(_AUDIO_SUPPORT == _ON)
                    // Mute Audio Output
                    UserCommonAudioMuteCurrentDigitalPortProc(_D8_DP_PORT);
#endif
                    UserCommonEdidLoadEmbeddedEdidDataByPort(_D8_INPUT_PORT_EDID);
                    ScalerDpRxEdidSwitch(_D8_INPUT_PORT);
                }
            }

            break;
#endif

#if(_D9_INPUT_PORT_TYPE == _D9_DP_PORT)

        case _D9_INPUT_PORT:

#if(_AUDIO_SUPPORT == _ON)
            // Mute Audio Output
            UserCommonAudioMuteCurrentDigitalPortProc(_D9_INPUT_PORT);
#endif
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D9_INPUT_PORT_EDID);
            ScalerDpRxEdidSwitch(_D9_INPUT_PORT);

            break;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if(_AUDIO_SUPPORT == _ON)
            // Mute Audio Output
            UserCommonAudioMuteCurrentDigitalPortProc(_D0_INPUT_PORT);
#endif
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_EDID);
            ScalerDpRxEdidSwitch(_D0_INPUT_PORT);

            // Edid Parse Info (from DDCRAM only)
            UserCommonEdidEmbeddedInfoParser(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

#if(_AUDIO_SUPPORT == _ON)
            // Mute Audio Output
            UserCommonAudioMuteCurrentDigitalPortProc(_D1_INPUT_PORT);
#endif
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
            ScalerDpRxEdidSwitch(_D1_INPUT_PORT);

            // Edid Parse Info (from DDCRAM only)
            UserCommonEdidEmbeddedInfoParser(_D1_INPUT_PORT);

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _D2_INPUT_PORT:

#if(_AUDIO_SUPPORT == _ON)
            // Mute Audio Output
            UserCommonAudioMuteCurrentDigitalPortProc(_D2_INPUT_PORT);
#endif
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_EDID);
            ScalerDpRxEdidSwitch(_D2_INPUT_PORT);

            // Edid Parse Info (from DDCRAM only)
            UserCommonEdidEmbeddedInfoParser(_D2_INPUT_PORT);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Switch DP ports Embedded EDID Data
// Input Value  : void
// Output Value : None
//--------------------------------------------------
void UserCommonEdidSwitchDpAllPortEdid(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    UserCommonEdidSwitchDpEdid(_D0_INPUT_PORT);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    UserCommonEdidSwitchDpEdid(_D1_INPUT_PORT);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    UserCommonEdidSwitchDpEdid(_D2_INPUT_PORT);
#endif
}

#if(_DUAL_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP EDID Switch for 5K3K QQHD
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void UserCommonEdidDpDualPortEdidTableSwitch(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

            CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D0_INPUT_PORT_EDID);
            ScalerDpRxVersionSwitch(_D0_INPUT_PORT, UserInterfaceDpGetVersion(_D0_INPUT_PORT), UserCommonDpGetMSTCapablePort());
            ScalerDpRxEdidSwitch(_D0_INPUT_PORT);
            break;

        case _D1_INPUT_PORT:

            CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D1_INPUT_PORT_EDID);
            ScalerDpRxVersionSwitch(_D1_INPUT_PORT, UserInterfaceDpGetVersion(_D1_INPUT_PORT), UserCommonDpGetMSTCapablePort());
            ScalerDpRxEdidSwitch(_D1_INPUT_PORT);
            break;

        case _D2_INPUT_PORT:

            CLR_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D2_INPUT_PORT_EDID);
            ScalerDpRxVersionSwitch(_D2_INPUT_PORT, UserInterfaceDpGetVersion(_D2_INPUT_PORT), UserCommonDpGetMSTCapablePort());
            ScalerDpRxEdidSwitch(_D2_INPUT_PORT);
            break;

        case _D7_INPUT_PORT:

            SET_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D7_INPUT_PORT_EDID);
            ScalerDpRxVersionSwitch(_D7_INPUT_PORT, UserInterfaceDpGetVersion(_D7_INPUT_PORT), UserCommonDpGetMSTCapablePort());
            ScalerDpRxEdidSwitch(_D7_INPUT_PORT);
            break;

        case _D8_INPUT_PORT:

            SET_DP_DUAL_PORT_EDID_STATUS_SELECT();
            UserCommonEdidLoadEmbeddedEdidDataByPort(_D8_INPUT_PORT_EDID);
            ScalerDpRxVersionSwitch(_D8_INPUT_PORT, UserInterfaceDpGetVersion(_D8_INPUT_PORT), UserCommonDpGetMSTCapablePort());
            ScalerDpRxEdidSwitch(_D8_INPUT_PORT);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP EDID Status for DP Dual Port
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonEdidDpGetDualPortEdidSelectStatus(void)
{
    return GET_DP_DUAL_PORT_EDID_STATUS_SELECT();
}
#endif // End of #if(_DUAL_DP_SUPPORT == _ON)
#endif // End of #if(_EMBEDDED_EDID_SUPPORT == _ON)
#endif
