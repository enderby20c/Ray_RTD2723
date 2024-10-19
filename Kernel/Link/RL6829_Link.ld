#include "SysInclude.h"

____LINKER_SCRIPT____

#include <undef_keyword.ld>

/*************************/
/* project linker settings */
/*************************/
#include "@LINKER_FILE_CPU32@"

/*************************/
/* kernel linker settings */
/*************************/
#ifdef CPU32_BOOTLOADER
    __linker_flash_bank_align_64k__ = 1;
    __linker_is_final_build__ = 1;
#else
    #if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        __linker_flash_bank_align_64k__ = 1;

        #if(_SCPU_SUPPORT == _OFF)
            __linker_is_final_build__ = 1;
        #endif
    #endif
#endif

/* Flash mode settings */
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    __linker_assign_flash_address:tFlashMode__ = 0x00007000;
#endif

#include <Scaler_Link.ld>

/*************************/
/* include linker script */
/*************************/
#if(_CPU32_IP == _CPU32_IP_RX3081)

    #include <RL6829/RL6829_Link_memory_KCPU.ld>
    #include <RL6829/RL6829_Link_sections_KCPU.ld>

#else

    #include <RL6829/RL6829_Link_memory_SCPU.ld>

    #ifdef CPU32_BOOTLOADER
        #include <RL6829/RL6829_Link_sections_SCPU_boot.ld>
    #else
        #include <RL6829/RL6829_Link_sections_SCPU.ld>
    #endif

#endif
