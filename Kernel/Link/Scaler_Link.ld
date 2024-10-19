/* symbol remapping */
PROVIDE(__real_memcpy = memcpy);
PROVIDE(__real_memset = memset);
PROVIDE(__real_memcmp = memcmp);

/* custom link info */
__linker_constant_flash_base32__ = _DEVICE_FLASH_BASE_ADDR;

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)

    /* reserve xram for DDC ram */
    #if(_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        __linker_reserve_ram_address__ = _EMBEDDED_DDCRAM_VGA_DDC_ADDRESS;
        __linker_reserve_ram_length__ = _MCU_DDCRAM_A0_SIZE;
    #endif

    #if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        #if(_D0_DDC_CHANNEL_SEL == _DDC0)
            __linker_reserve_ram_address__ = _EMBEDDED_DDCRAM_DDC0_ADDRESS;
            __linker_reserve_ram_length__ = _MCU_DDCRAM_D0_SIZE;
        #endif
    #endif

    #if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        #if(_D1_DDC_CHANNEL_SEL == _DDC1)
            __linker_reserve_ram_address__ = _EMBEDDED_DDCRAM_DDC1_ADDRESS;
            __linker_reserve_ram_length__ = _MCU_DDCRAM_D1_SIZE;
        #endif
    #endif

    #if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        #if(_D2_DDC_CHANNEL_SEL == _DDC2)
            __linker_reserve_ram_address__ = _EMBEDDED_DDCRAM_DDC2_ADDRESS;
            __linker_reserve_ram_length__ = _MCU_DDCRAM_D2_SIZE;
        #endif
    #endif

    #if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        #if(_D3_DDC_CHANNEL_SEL == _DDC3)
            __linker_reserve_ram_address__ = _EMBEDDED_DDCRAM_DDC3_ADDRESS;
            __linker_reserve_ram_length__ = _MCU_DDCRAM_D3_SIZE;
        #endif
    #endif

    #if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        #if(_D4_DDC_CHANNEL_SEL == _DDC4)
            __linker_reserve_ram_address__ = _EMBEDDED_DDCRAM_DDC4_ADDRESS;
            __linker_reserve_ram_length__ = _MCU_DDCRAM_D4_SIZE;
        #endif
    #endif

    /* reserve xdata for SPI Rx buffer */
    #if(_HW_SPI2_EXIST == _OFF)
        #if(_SPI0_SUPPORT == _ON)
            __linker_reserve_ram_address__ = _SPI0_RX_BUFFER_ADDRESS;
            __linker_reserve_ram_length__ = _SPI0_RX_BUFFER_MAX_LENGTH;
        #endif
    #endif
    #if((_DUAL_BANK_SUPPORT == _ON) && ((_DUAL_BANK_TYPE == _DUAL_BANK_DIFF_BANK) || (_DUAL_BANK_TYPE == _DUAL_BANK_COPY_BANK)))
        #if((_FW_UPDATE_PROCESS_SUPPORT == _ON) && (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
            __linker_assign_flash_address:tFwPassword__ = (_FW_UPDATE_PASSWORD_BANK << 16) | _FW_UPDATE_PASSWORD_ADDRESS;
        #endif
    #endif

    #if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
        __linker_assign_flash_address:tFwProjectIDTable__ = (_ISP_FW_CHECK_PROJECT_ID_LOCATION_BANK << 16) | _ISP_FW_CHECK_PROJECT_ID_LOCATION_ADDRESS;
    #endif

    #if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
        __linker_assign_flash_address:tFwVersionTable__ = (_CUSTOMER_FW_VERSION_LOCATE_BANK << 16) | _CUSTOMER_FW_VERSION_LOCATE_ADDRESS;
    #endif

    //for FW Update FW Process
    #if((_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON) || (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON) || ((_FW_UPDATE_FOREGROUND_SUPPORT == _ON) && (_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _OFF)))
        __linker_reserve_ram_address__ = _HW_XRAM_ISP_MAPPING_ADDR_START;
        __linker_reserve_ram_length__ = _FLASH_PROGRAM_SIZE;
    #endif

    #if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
        __linker_reserve_ram_address__ = _HW_XRAM_BG_ISP_SPEED_UP_MAPPING_ADDR_START;
        __linker_reserve_ram_length__ = _HW_ISP_SPEED_UP_SRAM_SIZE;
    #endif
#endif

#if((_SCPU_SUPPORT == _OFF) || (defined(CPU32_BOOTLOADER) == _TRUE))
    //for FW Update FW Process
    #if((_DUAL_BANK_SUPPORT == _ON) && ((_DUAL_BANK_TYPE == _DUAL_BANK_DIFF_BANK) || (_DUAL_BANK_TYPE == _DUAL_BANK_COPY_BANK)))
        #if((_FW_UPDATE_PROCESS_SUPPORT == _ON) || ((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW)))
            __linker_flash_bank_fill__ = _DUAL_BANK_USER_FW_CODE_SIZE;
        #endif
        #if((_FW_UPDATE_PROCESS_SUPPORT == _ON) && ((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072)))
            __linker_assign_flash_address:tFW_UPDATE_SIGNATURE_TABLE__ = ((_DUAL_BANK_USER_FW_CODE_SIZE - 1) << 16) | _FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS;
        #endif
        #if((_FW_UPDATE_PROCESS_SUPPORT == _ON) && ((_FW_UPDATE_CHECK_TYPE != _FW_UPDATE_CHECK_RTK_RSA2048) && (_FW_UPDATE_CHECK_TYPE != _FW_UPDATE_CHECK_RTK_RSA3072)))
            // Can't support link last byte
            __linker_assign_flash_address:tFwCrc__ = ((_DUAL_BANK_USER_FW_CODE_SIZE - 1) << 16) | 0xFFFC;
        #endif
    #endif

    /* Limit total fw size */
    #if((_DUAL_BANK_SUPPORT == _ON) &&\
        ((_DUAL_BANK_TYPE == _DUAL_BANK_DIFF_BANK) ||\
        (_DUAL_BANK_TYPE == _DUAL_BANK_COPY_BANK)))
        __linker_memory_length_limit:FLASH_TEXT__ = _DUAL_BANK_USER_FW_CODE_SIZE * 65536;
    #endif

    #if(((_DUAL_BANK_SUPPORT == _ON) && (_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION)) && (_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
            __linker_flash_bank_fill__ = _DUAL_BANK_USER_FW_CODE_SIZE;
    #endif
#endif

#if((_DUAL_BANK_FP_USER_FLAG_TABLE_SUPPORT == _ON) && (_DUAL_BANK_USER_I_TABLE_SUPPORT == _ON))
    __linker_assign_flash_address:tDUALBANKUSERFLAGTABLE__ = (_DUAL_BANK_USER_I_FLAG_LOCATE_BANK << 16) | _DUAL_BANK_FLASH_PARTITION_USER_FLAG_ADDRESS;
#endif

#if(_DUAL_BANK_USER_DATA_TABLE_SUPPORT == _ON)
    #if(_DUAL_BANK_USER_I_TABLE_SUPPORT == _ON)
        __linker_assign_flash_address:tDUALBANK_FILLHEX__ = (_DUAL_BANK_USER_I_FLAG_LOCATE_BANK << 16) | _DUAL_BANK_USER_DATA_SECTOR_ADDRESS;
    #endif
    #if((_DUAL_BANK_USER_I_FLAG_LOCATE_BANK != _DUAL_BANK_USER_II_FLAG_LOCATE_BANK) && (_DUAL_BANK_USER_II_TABLE_SUPPORT == _ON))
        __linker_assign_flash_address:tDUALBANK_FILLHEXII__ = (_DUAL_BANK_USER_II_FLAG_LOCATE_BANK << 16) | _DUAL_BANK_USER_DATA_SECTOR_ADDRESS;
    #endif
#endif