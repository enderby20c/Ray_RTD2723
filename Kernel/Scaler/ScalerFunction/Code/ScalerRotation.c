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
// ID Code      : ScalerRotation.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_ROTATION__

#include "ScalerFunctionInclude.h"
#include "Rotation/ScalerRotation.h"

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_EAGLE_SIGHT_SUPPORT == _ON))
#warning "NOTE: Rotation can't support when UserAdjustGetMultiDisplayMode select _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT!!"
#endif

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_M_DOMAIN_FORCE_IMG_CMP == _ON))
#warning "NOTE: Rotation can't support when force IMC ON!!"
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructRotationStatus g_stRotationStatus;
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
WORD g_usRotationVFrontPorchMin;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Check rotation status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerRotationCheckStatus(EnumRotationType enumRotationType, EnumInputPort enumInputPort)
{
#if(_DRR_SUPPORT == _ON)

    EnumDisplayMode enumDisplayModeTrans = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayModeTrans = ScalerRegionEagleSightTransDisplayMode(enumDisplayModeTrans);
#endif

    if((enumDisplayModeTrans == _DISPLAY_MODE_1P) &&
       (ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE))
    {
        return _FALSE;
    }
    else
#endif
    {
        enumInputPort = enumInputPort;

        // Rotation only in 1P mode
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            // Rotation only support in E/O mode
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                return (enumRotationType != _ROT_DISABLE);
            }
        }

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check video compensation field
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationCheckVideoCompensation(void)
{
    WORD usSUPageAddr = ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN());

    // Change video compensation field under rotation
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        switch(GET_ROT_TYPE())
        {
            default:
                break;

            case _ROT_DISABLE:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
            case _ROT_HOR_MIRROR:
#endif
                // For 0
                ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), (GET_MDOMAIN_INPUT_VIDEO_FIELD() == _TRUE) ? _BIT6 : 0);
                break;

            case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
            case _ROT_VER_MIRROR:
#endif
                // For vertical flip
                ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), (GET_MDOMAIN_INPUT_VIDEO_FIELD() == _TRUE) ? 0 : _BIT6);
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Set Rotation Enable/Disable
// Input Value  : bEn --> Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetEnable(bit bEn)
{
    if(bEn == _DISABLE)
    {
        // Set Rotation Disable
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), 0x00);

#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
        // Set Rotation Type = No Rotation.
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), 0x00);

        // Set Rotation control disable
        for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            ScalerRotationSetControl(GET_FRC_PAGE_SELECT(ucIndex), _ROT_DISABLE);
        }
#endif
    }
    else
    {
        if(ScalerGetBit(P20_F0_ROTATION_CTRL0, _BIT7) == 0x00)
        {
            // Set Rotation Enable
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), _BIT7);
        }
    }
}

//--------------------------------------------------
// Description  : Rotation control
// Input Value  : stFIFOSize --> FIFO Size
// Output Value : None
//--------------------------------------------------
void ScalerRotationControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    DebugMessageFRC("R_Type", GET_ROT_TYPE());
    DebugMessageFRC("R_Size", GET_ROT_DISP_SIZE());
    DebugMessageFRC("R-IH", pstFIFOSize->usInputHWidth);
    DebugMessageFRC("R_IV", pstFIFOSize->usInputVHeight);
    DebugMessageFRC("R-OH", pstFIFOSize->usOutputHWidth);
    DebugMessageFRC("R_OV", pstFIFOSize->usOutputVHeight);

    switch(GET_ROT_TYPE())
    {
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
        case _ROT_CW90:
        case _ROT_CW270:

            // Set Rotation info
            ScalerRotationSetInfo(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

            // Set Rotation Enable
            ScalerRotationSetEnable(_ENABLE);

            // Set FRC
            ScalerFRCControl(pstFIFOSize);
            break;
#endif

        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
            // Set Roation Enable
            ScalerRotationSetEnable(_ENABLE);

            // Set Rotation Source Pixel Number
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_III)
            ScalerSetBit(P20_F1_ROTATION_IN_WID_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pstFIFOSize->usInputHWidth >> 8) & 0x1F);
            ScalerSetByte(P20_F2_ROTATION_IN_WID_L, (pstFIFOSize->usInputHWidth & 0xFF));
#elif(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
            ScalerRotationSetInfo(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);
#endif

            ScalerFRCControl(pstFIFOSize);
            break;

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
            ScalerFRCControl(pstFIFOSize);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Rotation Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationInitial(void)
{
    // Rotation Disable
    ScalerSetByte(P20_F0_ROTATION_CTRL0, 0x01);

#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
    // Set Rotation Picture-Set
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        ScalerRotationSetPictSet();
    }
#endif
}

//--------------------------------------------------
// Description  : Rotation Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationReset(void)
{
    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
#endif
            // Set CW180 reset
            ScalerSetBit(P46_00_M_CAP_BLOCK_CTRL, ~_BIT3, 0x00);
#if(_HW_DISPLAY_ROTATION_CTRL_TYPE == _DISPLAY_ROTATION_CTRL_GEN_1)
            ScalerSetBit(P46_80_M_DISP_BLOCK_CTRL, ~_BIT7, 0x00);
#endif

            if(GET_MEMORY_FRAME_BUFFER() != _MEMORY_3_FRAME_BUFFER)
            {
                // FRC rotation activate the next ivs, it's safer to wait for iden_start for both M1/M2 be active in the same frame
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                ScalerSetBit(P46_00_M_CAP_BLOCK_CTRL, ~_BIT3, _BIT3);
#if(_HW_DISPLAY_ROTATION_CTRL_TYPE == _DISPLAY_ROTATION_CTRL_GEN_1)
                ScalerSetBit(P46_80_M_DISP_BLOCK_CTRL, ~_BIT7, _BIT7);
#endif
            }

            break;

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:

            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
            ScalerSetBit(P46_00_M_CAP_BLOCK_CTRL, ~_BIT3, 0x00);
#if(_HW_DISPLAY_ROTATION_CTRL_TYPE == _DISPLAY_ROTATION_CTRL_GEN_1)
            ScalerSetBit(P46_80_M_DISP_BLOCK_CTRL, ~_BIT7, 0x00);
#endif

            break;
#endif

        default:

            ScalerSetBit(P46_00_M_CAP_BLOCK_CTRL, ~_BIT3, 0x00);
#if(_HW_DISPLAY_ROTATION_CTRL_TYPE == _DISPLAY_ROTATION_CTRL_GEN_1)
            ScalerSetBit(P46_80_M_DISP_BLOCK_CTRL, ~_BIT7, 0x00);
#endif

            break;
    }
}
//--------------------------------------------------
// Description  : Set Rotation Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetRotationEnable(void)
{
    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
#endif
            if(GET_MEMORY_FRAME_BUFFER() != _MEMORY_3_FRAME_BUFFER)
            {
                // Set CW180 Enable
                ScalerSetBit(P46_00_M_CAP_BLOCK_CTRL, ~_BIT3, _BIT3);
#if(_HW_DISPLAY_ROTATION_CTRL_TYPE == _DISPLAY_ROTATION_CTRL_GEN_1)
                ScalerSetBit(P46_80_M_DISP_BLOCK_CTRL, ~_BIT7, _BIT7);
#endif
            }
            else
            {
                ScalerSetBit(P46_00_M_CAP_BLOCK_CTRL, ~_BIT3, 0x00);
#if(_HW_DISPLAY_ROTATION_CTRL_TYPE == _DISPLAY_ROTATION_CTRL_GEN_1)
                ScalerSetBit(P46_80_M_DISP_BLOCK_CTRL, ~_BIT7, 0x00);
#endif
            }

            break;

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
        default:

            ScalerSetBit(P46_00_M_CAP_BLOCK_CTRL, ~_BIT3, 0x00);
#if(_HW_DISPLAY_ROTATION_CTRL_TYPE == _DISPLAY_ROTATION_CTRL_GEN_1)
            ScalerSetBit(P46_80_M_DISP_BLOCK_CTRL, ~_BIT7, 0x00);
#endif

            break;
    }
}

//--------------------------------------------------
// Description  : Rotation Set Capture
// Input Value  : enumPageSelect, pstStep
// Output Value : None
//--------------------------------------------------
void ScalerRotationInputCtrl(EnumFRCPageSelect enumPageSelect, StructMemoryLineBlockStep *pstStep)
{
    DWORD ulRotationFrame = (pstStep->ulLineStep * (pstStep->usVerSize - 1));
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
    BYTE ucLen = 0;
    BYTE ucPictSetNum = 0;
    WORD usRemainData = 0;
    DWORD ulNumRemain = 0;
#endif

#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
    ScalerRotationSetControl(enumPageSelect, GET_ROT_TYPE());
#endif

    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
#endif

            // Set FRC capture address
            ScalerFRCCalculateAddress(enumPageSelect, ScalerFRCGetShiftBankOffset(enumPageSelect));

            if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER) // default 3 buffer, change 1 buffer for not hsd, change address with bank shift
            {
                ScalerFRCSetCapAddress(enumPageSelect, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(enumPageSelect, _FRC_1ST_BLOCK) + ulRotationFrame);
            }
            else if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER) // default 3 buffer, change 2 buffer for not hsd, change address with bank shift
            {
                ScalerFRCSetCapAddress(enumPageSelect, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(enumPageSelect, _FRC_1ST_BLOCK) + ulRotationFrame);
                ScalerFRCSetCapAddress(enumPageSelect, _FRC_4TH_BLOCK, ScalerFRCGetCapAddress(enumPageSelect, _FRC_2ND_BLOCK) + ulRotationFrame);
            }

            break;

#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
        case _ROT_CW90:
        case _ROT_CW270:

            // Set FRC capture address
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_1ST_BLOCK, 0x00);
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_2ND_BLOCK, 0x00);
            ScalerFRCSetCapAddress(enumPageSelect, _FRC_3RD_BLOCK, 0x00);

            // Set blk_strt_x
            SET_PAGED_BIT(enumPageSelect, P5_60_ROT_CAP_M1_BLK_STRT_X_MSB, ~(_BIT1 | _BIT0), 0x00);
            SET_PAGED_BYTE(enumPageSelect, P5_61_ROT_CAP_M1_BLK_STRT_X_LSB, 0x00);

            // Set blk_strt_y
            if(GET_ROT_TYPE() == _ROT_CW270)
            {
                PDATA_WORD(0) = (((ScalerGetByte(P5_21_CAP_M1_LINE_NUM_H) << 8) | (ScalerGetByte(P5_22_CAP_M1_LINE_NUM_L))) - 1);
            }
            else
            {
                PDATA_WORD(0) = 0;
            }

            SET_PAGED_BIT(enumPageSelect, P5_62_ROT_CAP_M1_BLK_STRT_Y_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(PDATA_WORD(0)) & 0x0F));
            SET_PAGED_BYTE(enumPageSelect, P5_63_ROT_CAP_M1_BLK_STRT_Y_LSB, LOBYTE(PDATA_WORD(0)));

            // Set blk_lr
            SET_PAGED_BYTE(enumPageSelect, P5_64_ROT_CAP_M1_BLK_LR, 0x01);

            // _BIT1: Set blk_mode, 0:16x1 mode, 1: 8x2 mode
            // _Bit0: Set blk_offset, 0: Frame mode, 1: Field mode
            SET_PAGED_BIT(enumPageSelect, P5_65_ROT_CAP_M1_CTRL1, ~(_BIT1 | _BIT0), 0x00);

            // Set pict set num
            ucPictSetNum = (CEILING_OF_INT_DIVISION(pstStep->usHorSize, _PICT_SET_MAX_WIDTH) - 1);
            SET_PAGED_BYTE(enumPageSelect, P5_6F_ROT_CAP_M1_PICT_NUM, ucPictSetNum);

            ucLen = ScalerFRCGetAccessLength(_FRC_WRITE_LENGTH);

            if(ucPictSetNum == 0) // 1 picture: Use Remain pict set
            {
                // Set General pict number
                SET_PAGED_BYTE(enumPageSelect, P5_23_CAP_M1_WR_NUM_H, 0x00);
                SET_PAGED_BYTE(enumPageSelect, P5_24_CAP_M1_WR_NUM_L, 0x00);

                // Set General pict length
                SET_PAGED_BYTE(enumPageSelect, P5_25_CAP_M1_WR_LEN, 0x00);

                // Set General pict remain
                SET_PAGED_BYTE(enumPageSelect, P5_26_CAP_M1_WR_REMAIN, 0x00);

                // Set remain data
                usRemainData = pstStep->usHorSize;
            }
            else // 2 or 3 picture: Use General + Remain pict set
            {
                // Set General pict number
                SET_PAGED_BYTE(enumPageSelect, P5_23_CAP_M1_WR_NUM_H, (((_PICT_SET_MAX_WIDTH / ucLen) >> 8) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_24_CAP_M1_WR_NUM_L, ((_PICT_SET_MAX_WIDTH / ucLen) & 0xFF));

                // Set General pict length
                SET_PAGED_BYTE(enumPageSelect, P5_25_CAP_M1_WR_LEN, ucLen);

                // Set General pict remain
                SET_PAGED_BYTE(enumPageSelect, P5_26_CAP_M1_WR_REMAIN, (_PICT_SET_MAX_WIDTH % ucLen));

                // Set remain data
                if((pstStep->usHorSize % _PICT_SET_MAX_WIDTH) != 0)
                {
                    usRemainData = pstStep->usHorSize % _PICT_SET_MAX_WIDTH;
                }
                else // consider usWidth = n * 1024
                {
                    usRemainData = pstStep->usHorSize - (ucPictSetNum * _PICT_SET_MAX_WIDTH);
                }
            }

            // Calculate Remain pict number and remain
            ulNumRemain = ScalerMemoryCalculateNumberAndRemain((DWORD)usRemainData, ucLen, 1);

            // Set Remain pict number
            SET_PAGED_BYTE(enumPageSelect, P5_69_ROT_CAP_M1_REMAINPICT_NUM, (ulNumRemain & 0xFF));

            // Set Remain pict length
            SET_PAGED_BYTE(enumPageSelect, P5_6A_ROT_CAP_M1_REMAINPICT_LEN, ucLen);

            // Set Remain pict remain
            SET_PAGED_BYTE(enumPageSelect, P5_6B_ROT_CAP_M1_REMAINPICT_REM, ((ulNumRemain >> 16) & 0xFF));

            break;
#endif

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Rotation Set Display
// Input Value  : enumPageSelect, pstStep
// Output Value : None
//--------------------------------------------------
void ScalerRotationDisplayCtrl(EnumFRCPageSelect enumPageSelect, StructMemoryLineBlockStep *pstStep)
{
    DWORD ulRotationFrame = (pstStep->ulLineStep * (pstStep->usVerSize - 1));
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
    BYTE ucLen = 0;
    DWORD ulTotalData = 0;
    DWORD ulNumRemain = 0;
#endif

    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
#endif

            // Set FRC display address
            // M1 Disp = M2 start - line num + 1
            // M2 Disp = M1 start - line num + 1
            if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_3_FRAME_BUFFER)
            {
                SET_PAGED_BIT(enumPageSelect, P5_99_DISP_M1_LINE_STEP_TOP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((((~pstStep->ulLineStep) + 1) >> 24) & 0x0F));
                SET_PAGED_BYTE(enumPageSelect, P5_9A_DISP_M1_LINE_STEP_TOP_H, ((((~pstStep->ulLineStep) + 1) >> 16) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_9B_DISP_M1_LINE_STEP_TOP_M, ((((~pstStep->ulLineStep) + 1) >> 8) & 0xFF));
                SET_PAGED_BYTE(enumPageSelect, P5_9C_DISP_M1_LINE_STEP_TOP_L, (((~pstStep->ulLineStep) + 1) & 0xFF));
            }

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
            if(((_FW_MEM_CLIENT_SHARE_ADDR_SPACE == _TRUE) && (enumPageSelect == _FRC_MAIN2_PAGE)) ||
               ((_FW_MEM_CLIENT_SHARE_ADDR_SPACE == _FALSE) && (enumPageSelect == _FRC_MAIN1_PAGE)))
#else
            if(enumPageSelect == _FRC_MAIN1_PAGE)
#endif
            {
                if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER) || (GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER))
                {
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK));
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_4TH_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_4TH_BLOCK));
                }
                else
                {
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK) + ulRotationFrame);
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_2ND_BLOCK) + ulRotationFrame);
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_3RD_BLOCK) + ulRotationFrame);
                }
            }
            else
            {
                if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER) || (GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER))
                {
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK));
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK));
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK));
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_4TH_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_4TH_BLOCK));
                }
                else
                {
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK) + ulRotationFrame);
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_2ND_BLOCK) + ulRotationFrame);
                    ScalerFRCSetDispAddress(enumPageSelect, _FRC_3RD_BLOCK, ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_3RD_BLOCK) + ulRotationFrame);
                }
            }

            break;

#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
        case _ROT_CW90:
        case _ROT_CW270:

            // Set FRC display address
            ScalerFRCSetDispAddress(enumPageSelect, _FRC_1ST_BLOCK, 0x00);
            ScalerFRCSetDispAddress(enumPageSelect, _FRC_2ND_BLOCK, 0x00);
            ScalerFRCSetDispAddress(enumPageSelect, _FRC_3RD_BLOCK, 0x00);

            // Set blk_strt_x
            SET_PAGED_BIT(enumPageSelect, P5_70_ROT_DISP_M1_BLK_STRT_X_MSB, ~(_BIT1 | _BIT0), 0x00);
            SET_PAGED_BYTE(enumPageSelect, P5_71_ROT_DISP_M1_BLK_STRT_X_LSB, 0x00);

            // Set blk_strt_y
            SET_PAGED_BIT(enumPageSelect, P5_72_ROT_DISP_M1_BLK_STRT_Y_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            SET_PAGED_BYTE(enumPageSelect, P5_73_ROT_DISP_M1_BLK_STRT_Y_LSB, 0x00);

            // Set blk_w
            SET_PAGED_BIT(enumPageSelect, P5_74_ROT_DISP_M1_BLK_W, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ROTATION_DISP_BLK_W);

            // _BIT1: Set blk_mode, 0:16x1 mode, 1: 8x2 mode
            // _Bit0: Set blk_offset, 0: Frame mode, 1: Field mode
            SET_PAGED_BIT(enumPageSelect, P5_76_ROT_DISP_M1_CTRL1, ~(_BIT1 | _BIT0), 0x00);

            // Calculate number and remain
            ulTotalData = ((ScalerGetByte(P5_21_CAP_M1_LINE_NUM_H) << 8) | (ScalerGetByte(P5_22_CAP_M1_LINE_NUM_L))) * _ROTATION_DISP_BLK_W;
            ucLen = ScalerFRCGetAccessLength(_FRC_READ_LENGTH);
            ulNumRemain = ScalerMemoryCalculateNumberAndRemain(ulTotalData, ucLen, 1);

            // Set number
            SET_PAGED_BYTE(enumPageSelect, P5_A8_DISP_M1_READ_NUM_TOP_H, ((ulNumRemain >> 8) & 0xFF));
            SET_PAGED_BYTE(enumPageSelect, P5_A9_DISP_M1_READ_NUM_TOP_L, (ulNumRemain & 0xFF));

            // Set length
            SET_PAGED_BYTE(enumPageSelect, P5_AA_DISP_M1_READ_TOP_LEN, (ucLen / _ROTATION_DISP_BLK_W));

            // Set remain
            SET_PAGED_BYTE(enumPageSelect, P5_AB_DISP_M1_READ_REMAIN_TOP, (((ulNumRemain >> 16) & 0xFF) / _ROTATION_DISP_BLK_W));

            // Set pict set num
            SET_PAGED_BYTE(enumPageSelect, P5_7C_ROT_DISP_M1_PICT_NUM, GET_PAGED_BYTE(enumPageSelect, P5_6F_ROT_CAP_M1_PICT_NUM));

            // Set pict width
            SET_PAGED_BYTE(enumPageSelect, P5_7A_ROT_DISP_M1_PICT_FST_WID_H, ((_PICT_SET_MAX_WIDTH >> 8) & 0x07));
            SET_PAGED_BYTE(enumPageSelect, P5_7B_ROT_DISP_M1_PICT_FST_WID_L, (_PICT_SET_MAX_WIDTH & 0xFF));

            break;
#endif

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
        default:

            break;
    }
}

#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
//--------------------------------------------------
// Description  : Check rotation vertical status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerRotationCheckVerticalStatus(void)
{
    if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
    {
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check rotation vertical v front porch limitation
// Input Value  : bDigitalCapture
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerRotationCheckVFrontPorch(bit bDigitalCapture)
{
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        bit bRotationEnable = _DISABLE;

        // Analog capture
        if(bDigitalCapture == _FALSE)
        {
            // IVstart_min = _VGIP_IV_CAPTURE_MIN_VALUE at ScalerIDomainVgipAdjustIHVDelay
            if((GET_MDOMAIN_INPUT_VTOTAL() - _VGIP_IV_CAPTURE_MIN_VALUE - GET_MDOMAIN_INPUT_VHEIGHT()) >= GET_ROT_V_FRONT_PORCH_MIN_VALUE())
            {
                bRotationEnable = _ENABLE;
            }
            else
            {
                bRotationEnable = _DISABLE;
            }
        }
        // Digital capture
        else
        {
            if(ScalerVgipGetVsBypassEnable(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
            {
                // Current v front porch is enough
                if((GET_MDOMAIN_INPUT_VTOTAL() - GET_MDOMAIN_INPUT_VSTART() - GET_MDOMAIN_INPUT_VHEIGHT()) >= GET_ROT_V_FRONT_PORCH_MIN_VALUE())
                {
                    bRotationEnable = _ENABLE;
                }
                else
                {
                    bRotationEnable = _DISABLE;
                }
            }
            else
            {
                // IVstart >= _VGIP_IV_CAPTURE_MIN_VALUE
                if((GET_MDOMAIN_INPUT_VTOTAL() - _VGIP_IV_CAPTURE_MIN_VALUE - GET_MDOMAIN_INPUT_VHEIGHT()) >= GET_ROT_V_FRONT_PORCH_MIN_VALUE())
                {
                    bRotationEnable = _ENABLE;

                    // Need to use analog capture to match new rotation v front porch limitation
                    if((GET_MDOMAIN_INPUT_VTOTAL() - GET_MDOMAIN_INPUT_VSTART() - GET_MDOMAIN_INPUT_VHEIGHT()) < GET_ROT_V_FRONT_PORCH_MIN_VALUE())
                    {
                        bDigitalCapture = _FALSE;
                    }
                }
                else
                {
                    bRotationEnable = _DISABLE;
                }
            }
        }

        if(bRotationEnable == _DISABLE)
        {
            DebugMessageSystem("[Warning]!!!!!! Input v total porch is too small to support rotation CW90/270", 0);
            DebugMessageSystem("[Warning]!!!!!! Input v total", GET_MDOMAIN_INPUT_VTOTAL());
            DebugMessageSystem("[Warning]!!!!!! Input v height", GET_MDOMAIN_INPUT_VHEIGHT());
            DebugMessageSystem("[Warning]!!!!!! Input v start", GET_MDOMAIN_INPUT_VSTART());
            DebugMessageSystem("[Warning]!!!!!! Input v sync width", GET_MDOMAIN_INPUT_VSYNCWIDTH());
            DebugMessageSystem("[Warning]!!!!!! Rotation v front porch min", GET_ROT_V_FRONT_PORCH_MIN_VALUE());

            SET_ROT_TYPE(_ROT_DISABLE);
        }
    }

    return bDigitalCapture;
}

//--------------------------------------------------
// Description  : Rotation Set Pictset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetPictSet(void)
{
    BYTE ucPictIndex = 0;
    DWORD ulPictInitPage = 0;
    DWORD ulDcPictSet = 0;
    DWORD ulDcPictSetOffset = 0;

    for(ucPictIndex = 0; ucPictIndex < _TOTOAL_PICT_SET_NUM; ucPictIndex++)
    {
        // Set DC_PICT_SET, Scaler32SetDWord: set register 0x04 -> 0x00 = DWORD MSB -> LSB
        ulDcPictSet = (ulPictInitPage & 0xFF) |
                      (((ulPictInitPage >> 8) & 0xFF) << 8) |
                      ((((PICT_SET_WIDTH_SCALE(ucPictIndex) << 1) & 0x7E) | (((ulPictInitPage >> 16) & _BIT0))) << 16);
        Scaler32SetDWord(PB08100_00_DC_PICT_SET, ulDcPictSet);

        // Update next pict init page
        ulPictInitPage = ulPictInitPage + PICT_SET_INIT_PAGE_WIDTH(ucPictIndex);

        // Set DC_PICT_SET_OFFSET
        ulDcPictSetOffset = (ucPictIndex << 24);
        Scaler32SetDWord(PB08100_20_DC_PICT_SET_OFFSET, ulDcPictSetOffset);
    }

    // Set Capture picture set idx
    ScalerSetByte(P5_6C_ROT_CAP_M1_PICT_FST_IDX, 0x00);
    ScalerSetByte(P5_6D_ROT_CAP_M1_PICT_SEC_IDX, 0x03);
    ScalerSetByte(P5_6E_ROT_CAP_M1_PICT_THI_IDX, 0x06);
    ScalerSetByte(P45_6C_ROT_CAP_M2_PICT_FST_IDX, 0x09);
    ScalerSetByte(P45_6D_ROT_CAP_M2_PICT_SEC_IDX, 0x0C);
    ScalerSetByte(P45_6E_ROT_CAP_M2_PICT_THI_IDX, 0x0F);

    // Set Display picture set idx
    ScalerSetByte(P5_77_ROT_DISP_M1_PICT_FST_IDX, 0x00);
    ScalerSetByte(P5_78_ROT_DISP_M1_PICT_SEC_IDX, 0x03);
    ScalerSetByte(P5_79_ROT_DISP_M1_PICT_THI_IDX, 0x06);
    ScalerSetByte(P45_77_ROT_DISP_M2_PICT_FST_IDX, 0x09);
    ScalerSetByte(P45_78_ROT_DISP_M2_PICT_SEC_IDX, 0x0C);
    ScalerSetByte(P45_79_ROT_DISP_M2_PICT_THI_IDX, 0x0F);
}

//--------------------------------------------------
// Description  : Rotation Set Info
// Input Value  : usCaphwidth, usCapvheight
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetInfo(WORD usCaphwidth, WORD usCapvheight)
{
    BYTE ucRotationVerticalFactor = 0;

    // Set Rotation type
    switch(GET_ROT_TYPE())
    {
        case _ROT_CW90:
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), _BIT5);
            break;

        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), _BIT6);
            break;

        case _ROT_CW270:
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
            break;

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
#endif
        default:
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), 0x00);
            break;
    }

    // Set Rotation support bit, pixel remain
    if((GET_ROT_TYPE() == _ROT_CW90) || ((GET_ROT_TYPE() == _ROT_CW270)))
    {
        if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
        {
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT3), _BIT3);
            ScalerSetBit(P20_F5_ROTATION_CTRL1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (((usCapvheight % 64) == 0) ? (0x00) : ((usCapvheight % 64) - 1)));
        }
        else
        {
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT3), 0x00);
            ScalerSetBit(P20_F5_ROTATION_CTRL1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (((usCapvheight % 16) == 0) ? (0x00) : ((usCapvheight % 16) - 1)));
        }
    }
    else
    {
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT3), _BIT3);
    }

    // Set Rotation source pixel number(hwidth)
    ScalerSetBit(P20_F1_ROTATION_IN_WID_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usCaphwidth >> 8) & 0x1F);
    ScalerSetByte(P20_F2_ROTATION_IN_WID_L, (usCaphwidth & 0xFF));

    // Set Rotation source line number(usVSize / 2): E/O mode
    ScalerSetBit(P20_F3_ROTATION_IN_LEN_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usCapvheight / 2) >> 8) & 0x1F);
    ScalerSetByte(P20_F4_ROTATION_IN_LEN_L, ((usCapvheight / 2) & 0xFF));

    // Set Vertical Rotation Factor For Reading Line Buffer
    ucRotationVerticalFactor = ScalerRotationGetVerticalFactor(usCaphwidth);

    ScalerSetByte(P20_F6_ROTATION_CTRL2, ucRotationVerticalFactor);
}

//--------------------------------------------------
// Description  : Set Rotation Control
// Input Value  : enumPageSelect, enumRotationType
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetControl(EnumFRCPageSelect enumPageSelect, EnumRotationType enumRotationType)
{
    switch(enumRotationType)
    {
        case _ROT_DISABLE:
        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
#endif
        default:

            SET_PAGED_BIT(enumPageSelect, P5_65_ROT_CAP_M1_CTRL1, ~(_BIT6 | _BIT5), 0x00);
            break;

        case _ROT_CW90:

            SET_PAGED_BIT(enumPageSelect, P5_65_ROT_CAP_M1_CTRL1, ~(_BIT6 | _BIT5), _BIT5);
            break;

        case _ROT_CW270:

            SET_PAGED_BIT(enumPageSelect, P5_65_ROT_CAP_M1_CTRL1, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
            break;
    }
}

//--------------------------------------------------
// Description  : Calculate Rotation Cap BW
// Input Value  : ulPixelclk, usCaphwidth
// Output Value : None
//--------------------------------------------------
DWORD ScalerRotationCalculateCaptureBW(DWORD ulPixelclk, WORD usCaphwidth)
{
    BYTE ucRotationVerticalFactor = 0;
    DWORD ulFRCWriteBw = 0;

    ucRotationVerticalFactor = ScalerRotationGetVerticalFactor(usCaphwidth);

    // Cap_BW = pixel rate x 128 x (P20_F6_ROTATION_CTRL2 / 256) x 0.5
    ulFRCWriteBw = GET_DWORD_MUL_DIV(((ulPixelclk / 2) / 10), ((DWORD)ucRotationVerticalFactor * 100), _MEMORY_BUS_WIDTH) / 1000 / 2;

    return ulFRCWriteBw;
}

//--------------------------------------------------
// Description  : Get Rotation Vertical factor
// Input Value  : usCaphwidth
// Output Value : None
//--------------------------------------------------
BYTE ScalerRotationGetVerticalFactor(WORD usCaphwidth)
{
    WORD usRotationVerticalFactor = 0;

    // Bits per pixel * 2 * HWidth = 120 * Factor * HTotal
    // --> 24bit: Factor = (2 * HWidth / (5 * HTotal)) * 2^8.
    // --> 30bit: Factor = (HWidth / (2*Htoal)) * 2^8.
    if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
    {
        usRotationVerticalFactor = (((DWORD)usCaphwidth << 8) * 100) / 2 / GET_MDOMAIN_INPUT_HTOTAL();
    }
    else
    {
        usRotationVerticalFactor = (((DWORD)usCaphwidth << 8) * 100) / 5 * 2 / GET_MDOMAIN_INPUT_HTOTAL();
    }

    usRotationVerticalFactor = ((usRotationVerticalFactor % 100) != 0) ? (usRotationVerticalFactor / 100 + 1) : (usRotationVerticalFactor / 100);

    return ((BYTE)usRotationVerticalFactor);
}
#endif

#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
