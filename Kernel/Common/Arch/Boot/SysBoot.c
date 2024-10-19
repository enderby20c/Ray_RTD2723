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
// ID Code      : SysBoot.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "SysBoot.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_CPU32_COMPRESSED_IMAGE_SUPPORT == _ON)
__attribute__((section(".noinit.g_pulDecompressBuffer")))
DWORD g_pulDecompressBuffer[1024 * 1024 / sizeof(DWORD)];
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_CPU32_COMPRESSED_IMAGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decompress firmware image
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysBootLoadCompressedFirmwareImage(void)
{
    DWORD ulContentSize = ((DWORD)&__scpu_firmware_image_load_address_end) - ((DWORD)&__scpu_firmware_image_load_address_start);

    EnumDecompressStatus enumStatus = _DECOMPRESS_SUCCESS;

    // copy compressed firmware image to ram
    SysBootLoadFirmwareImage(g_pulDecompressBuffer);

    // Decompress compressed firmware image
    enumStatus = DECOMPRESS(
        (BYTE *)g_pulDecompressBuffer,
        (BYTE *)(&__scpu_firmware_image_virtual_address_start),
        ulContentSize
    );

    // sync D-Cache content with external memory(DDR)
    ScalerCpuHalCleanDataCache();

    switch(enumStatus)
    {
        case _DECOMPRESS_SUCCESS:
            return;

        case _DECOMPRESS_ERROR_INVALID_MAGIC_NUMBER:
        case _DECOMPRESS_ERROR_WRT_BUFFER_OVERFLOW:
        case _DECOMPRESS_ERROR_REF_OFFSET_UNDERFLOW:
        case _DECOMPRESS_ERROR_INTPUT_DATA_ERROR:
        case _DECOMPRESS_ERROR_EOF:
        default:
            // Notify Decompress Extract Fail
            SysBootNotifyBootStatus(_FAIL);
            while(1){};
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : load firmware image to target address
// Input Value  : pulDest -> destination address
// Output Value : None
//--------------------------------------------------
void SysBootLoadFirmwareImage(DWORD *pulDest)
{
    DWORD *pulSrc = (DWORD *)(&__scpu_firmware_image_load_address_start);
    DWORD *pulSrcEnd = (DWORD *)(&__scpu_firmware_image_load_address_end);

    // Iterate and copy word by word.
    // It is assumed that the pointers are word aligned.
    while(pulSrc < pulSrcEnd)
    {
        *pulDest++ = *pulSrc++;
    }

    ASM_DSB();

    // sync D-Cache content with external memory(DDR)
    ScalerCpuHalCleanDataCache();
}

//--------------------------------------------------
// Description  : Initialize ITCM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysBootInitItcm(void)
{
    // Set IMEM Fill Content Source Range
    SET_IMEM_RANGE(
        (DWORD)&__scpu_firmware_itcm_load_address_start,
        (DWORD)&__scpu_firmware_itcm_load_address_start + (_ITCM_E_ADDRESS - _ITCM_B_ADDRESS)
    );

    // Fill IMEM by HW and auto Enable after fill done
    IMEM_FILL_AND_ENABLE();	// consume 19us at rtlsim at 480MHz

    // Set IMEM to Active Range
    SET_IMEM_RANGE(_ITCM_B_ADDRESS, _ITCM_E_ADDRESS);

#if(__MPU_PRESENT == 1)
    // MPU2: Non-Cache && Privileged Read Only for ITCM Region
    ScalerCpuHalSetupItcmMemoryAttribute(_MPU_REGION_R_ONLY_PRIVILEGED_ONLY);
#endif

    // sync D-Cache content with external memory(DDR)
    ScalerCpuHalCleanDataCache();
}

//--------------------------------------------------
// Description  : Notify boot status to other cpu
// Input Value  : bStatus: status to be notified
// Output Value : None
//--------------------------------------------------
void SysBootNotifyBootStatus(bit bStatus)
{
    if(bStatus == _SUCCESS)
    {
        // Extract done and success
        // 0xA3000040[0]: Bootloader Extract Success
        // 0xA3000040[1]: Bootloader Extract Done(maybe success or failed)
        Scaler32SetBit(PA30000_04_GLOBAL_CTRL_DUMMY0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
    else
    {
        // Extract done but failed
        // 0xA3000040[0]: Bootloader Extract Success
        // 0xA3000040[1]: Bootloader Extract Done(maybe success or failed)
        Scaler32SetBit(PA30000_04_GLOBAL_CTRL_DUMMY0, ~(_BIT1 | _BIT0), _BIT1);
    }
}

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : dm init
// Input Value  : None
// Output Value : None
//--------------------------------------------------
__attribute__((weak))
bit __scpu_firmware_dm_init(void)
{
    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : The main function for SCPU boot
// Input Value  : None
// Output Value : None
//--------------------------------------------------
SWORD main(void)
{
    // Switch CPU Freq to PLL source
    ScalerMcu1usDelayCalc(_M2PLL_CLK);
    // Switch CPU Freq to PLL source(Already done in Reset_Handler)
    ScalerGlobalCtrlSetSys32ClkSrc(_M2PLL_CLK);

#if(_JTAG_DEBUG == _ON)
    Scaler32SetDWord(PA30000_04_GLOBAL_CTRL_DUMMY0, 0);
#endif

    if(Scaler32GetBit(PA30000_04_GLOBAL_CTRL_DUMMY0, _BIT0) == 0)
    {
#if(_CPU32_COMPRESSED_IMAGE_SUPPORT == _ON)
        // Decompress firmware image
        SysBootLoadCompressedFirmwareImage();
#else
        // Copy firmware image
        SysBootLoadFirmwareImage((DWORD *)(&__scpu_firmware_image_virtual_address_start));
#endif

#if(_DM_FUNCTION == _ON)
        __scpu_firmware_dm_init();
        ScalerCpuHalCleanDataCache();
#endif
    }

    // Notify KCPU boot success
    SysBootNotifyBootStatus(_SUCCESS);

    // Initialize ITCM
    SysBootInitItcm();

#if(__MPU_PRESENT == 1)
    // Set Vector Table Offset Register(VTOR) to _ITCM_B_ADDRESS
    SET_VTOR(_ITCM_B_ADDRESS);
#endif

    // Switch MSP && PC for executing firmware image
    __set_MSP((DWORD)&__scpu_firmware_kernel_estack);
    ASM_JUMP_TO_PC((DWORD)&__scpu_firmware_reset_handler);

    // will never be executed
    __builtin_unreachable();

    return 0;
}

