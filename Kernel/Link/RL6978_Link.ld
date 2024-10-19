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
__linker_flash_bank_align_64k__ = 1;
__linker_is_final_build__ = 1;

/* Flash mode settings */
__linker_assign_flash_address:tFlashMode__ = 0x00007000;

#include <Scaler_Link.ld>

/*************************/
/* include linker script */
/*************************/
#include <RL6978/RL6978_Link_memory.ld>
#include <RL6978/RL6978_Link_sections.ld>
