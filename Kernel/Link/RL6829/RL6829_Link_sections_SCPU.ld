/*
 * Default linker script for CPU32.
 *
 * To make use of the multi-region initialisations, define
 * OS_INCLUDE_STARTUP_INIT_MULTIPLE_RAM_SECTIONS for the _startup.c file.
 */

#if(_CPU32_SCPU_PROGRAM_TEXT_ON_FLASH == _ON)
    #define _REGION_TEXT                FLASH_TEXT
#else
    #define _REGION_TEXT                RAM_TEXT
#endif

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _ON)
    #define _REGION_RAM                 XRAM_DATA
#else
    #define _REGION_RAM                 RAM_DATA
#endif

/* default stack on ddr */
#define _REGION_STACK               RAM_DATA
#define _RESERVED_STACK_SIZE        524288

/*
 * The '__stack' definition is required by crt0, do not remove it.
 */
__stack = ORIGIN(_REGION_STACK) + LENGTH(_REGION_STACK);

/* STM specific definition */
_estack = __stack;

__scpu_firmware_kernel_estack = __stack;

/*
 * Default stack sizes.
 * These are used by the startup in order to allocate stacks
 * for the different modes.
 */
/* stack size */
__Main_Stack_Size = _RESERVED_STACK_SIZE;

PROVIDE ( _Main_Stack_Size = __Main_Stack_Size );

_Main_Stack_Size = (_Main_Stack_Size > __Main_Stack_Size) ? _Main_Stack_Size : __Main_Stack_Size;

__Main_Stack_Limit = __stack  - _Main_Stack_Size;

/* "PROVIDE" allows to easily override these values from an
 * object file or the command line. */
PROVIDE ( _Main_Stack_Limit = __Main_Stack_Limit );

/*
 * Default heap definitions.
 * The heap start immediately after the last statically allocated
 * .sbss/.noinit section, and extends up to the main stack limit.
 */
PROVIDE ( _Heap_Begin = _end_noinit );
PROVIDE ( _Heap_Limit = __stack - _Main_Stack_Size );

/*
 * The entry point is informative, for debuggers and simulators,
 * since the CPU32 vector points to it anyway.
 */

ENTRY(Reset_Handler)

SECTIONS
{
    /*
     * For CPU32 devices, the beginning of the startup code is stored in
     * the .isr_vector section, which goes to FLASH.
     *
     * This address is used by the startup code to
     * initialise the .ItcmRegion section.
     */

    . = ORIGIN(FLASH_TEXT);
    .firmware_image_kcpu . (NOLOAD): ALIGN(4)
    {
        KEEP(*(.firmware_image_kcpu))
        /* Align Flash Bank Size */
        . = ALIGN(0x10000);

#if(_CPU32_SCPU_PROGRAM_TEXT_ON_FLASH == _ON)
        /* scpu boot placeholder */
        __scpu_firmware_boot_image_length = 0x2000;
        . += __scpu_firmware_boot_image_length;
#endif
    } >FLASH_TEXT

    /*
     * The initialised ItcmRegion section.
     *
     * ITCM Region execute from CPU Core ITCM
     *
     * The program executes knowing that the data is in the ITCM
     * but the loader puts the initial values in the DDR (inidata).
     * It is one task of the startup to copy the initial values from
     * DDR to ITCM.
     */
    . = ORIGIN(ITCM_TEXT);
    .itcm_section . : ALIGN(4)
    {
        __vectors_start = ABSOLUTE(.);
        /* STM specific definition */
        __vectors_start__ = ABSOLUTE(.);

        /* Interrupt vectors */
        KEEP(*(.ISR_MTVEC.itcm_section))
        KEEP(*(.ISR_COMMON.itcm_section))
        KEEP(*(.ISR_TABLE.itcm_section))
        *(.itcm_section .itcm_section.*)
    } >ITCM_TEXT AT>_REGION_TEXT = 0xFF

    __scpu_firmware_image_virtual_address_start = ORIGIN(RAM_TEXT);
    __scpu_firmware_itcm_load_address_start = LOADADDR(.itcm_section);
    __scpu_firmware_itcm_length = SIZEOF(.itcm_section);

    .inits : ALIGN(4)
    {
        /*
         * Memory regions initialisation arrays.
         *
         * Thee are two kinds of arrays for each RAM region, one for
         * data and one for bss. Each is iterrated at startup and the
         * region initialisation is performed.
         *
         * The data array includes:
         * - from (LOADADDR())
         * - region_begin (ADDR())
         * - region_end (ADDR()+SIZEOF())
         *
         * The bss array includes:
         * - region_begin (ADDR())
         * - region_end (ADDR()+SIZEOF())
         *
         * WARNING: It is mandatory that the regions are word aligned,
         * since the initialisation code works only on words.
         */
        . = ALIGN(4);
        __data_regions_array_start = .;

        LONG(LOADADDR(.data));
        LONG(ADDR(.data));
        LONG(ADDR(.data)+SIZEOF(.data));

        LONG(LOADADDR(.fast_data));
        LONG(ADDR(.fast_data));
        LONG(ADDR(.fast_data)+SIZEOF(.fast_data));

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _ON)
        LONG(LOADADDR(.ddr_data));
        LONG(ADDR(.ddr_data));
        LONG(ADDR(.ddr_data)+SIZEOF(.ddr_data));
#endif

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _OFF)
        LONG(LOADADDR(.xram_data));
        LONG(ADDR(.xram_data));
        LONG(ADDR(.xram_data)+SIZEOF(.xram_data));
#endif

        __data_regions_array_end = .;

        __bss_regions_array_start = .;

        LONG(ADDR(.bss));
        LONG(ADDR(.bss)+SIZEOF(.bss));

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _ON)
        LONG(ADDR(.ddr_bss));
        LONG(ADDR(.ddr_bss)+SIZEOF(.ddr_bss));
#endif

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _OFF)
        LONG(ADDR(.xram_bss));
        LONG(ADDR(.xram_bss)+SIZEOF(.xram_bss));
#endif

        __bss_regions_array_end = .;

        /* End of memory regions initialisation arrays. */

        /*
         * These are the old initialisation sections, intended to contain
         * naked code, with the prologue/epilogue added by crti.o/crtn.o
         * when linking with startup files. The standalone startup code
         * currently does not run these, better use the init arrays below.
         */
        KEEP(*(.init))
        KEEP(*(.fini))

        . = ALIGN(4);

        /*
         * The preinit code, i.e. an array of pointers to initialisation
         * functions to be performed before constructors.
         */
        PROVIDE_HIDDEN (__preinit_array_start = .);

        /*
         * Used to run the SystemInit() before anything else.
         */
        KEEP(*(.preinit_array_sysinit .preinit_array_sysinit.*))

        /*
         * Used for other platform inits.
         */
        KEEP(*(.preinit_array_platform .preinit_array_platform.*))

        /*
         * The application inits. If you need to enforce some order in
         * execution, create new sections, as before.
         */
        KEEP(*(.preinit_array .preinit_array.*))

        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);

        /*
         * The init code, i.e. an array of pointers to static constructors.
         */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);

        /*
         * The fini code, i.e. an array of pointers to static destructors.
         */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >_REGION_TEXT = 0xFF

    /* Startup code and ISR */
    .after_vectors : ALIGN(4)
    {
        __scpu_firmware_reset_handler = .;
        KEEP(*(.reset_vectors))

        *(.after_vectors .after_vectors.*)
    } >_REGION_TEXT

#if(_DM_FUNCTION == _ON)
    . = ORIGIN(RAM_TEXT) + 0x4000;
    .dm_image.text . : ALIGN(4)
    {
        *(.dm_image.text)
    } >RAM_TEXT = 0xFF
#endif

#if(_CPU32_SCPU_PROGRAM_TEXT_ON_FLASH == _ON)
    .ddr_text : ALIGN(4)
    {
        *(.ddr_text .ddr_text.*)
        . = ALIGN(4);
    } >RAM_TEXT AT>FLASH_TEXT = 0xFF

    __scpu_firmware_image_load_address_start = LOADADDR(.ddr_text);
    __scpu_firmware_image_load_address_end = LOADADDR(.ddr_text) + SIZEOF(.ddr_text);
#endif

    /*
     * The program code is stored in the .text section,
     * which goes to FLASH.
     */
    .text : ALIGN(4)
    {
        __text_data_start__ = .;

        __linker_text_start__ = .;

        /* all remaining code */
        *(.text .text.*)

        /* fast text merged with .text */
        *(.fast_text .fast_text.*)

#if(_CPU32_SCPU_PROGRAM_TEXT_ON_FLASH == _OFF)
        *(.ddr_text .ddr_text.*)
#endif

        /* C++ virtual tables */
        *(vtable)

        KEEP(*(.eh_frame*))

        __text_data_end__ = .;
    } >_REGION_TEXT = 0xFF

    .rodata : ALIGN(4)
    {
        __linker_rodata_start__ = .;

        /* keep used table */
        KEEP(*(.used_table  .used_table.*))

         /* read-only data (constants) */
        *(.rodata .rodata.* .constdata .constdata.*)
        *(.srodata .srodata.*)
        *(.sdata2 .sdata2.*)
        *(.sbss2 .sbss2.*)
    } >_REGION_TEXT = 0xFF

    . = ALIGN(4);
    _etext = .;
    __etext = .;

#if(_DM_FUNCTION == _ON)
    .dm_image.data (NOLOAD) : ALIGN(4)
    {
        KEEP(*(.dm_image.bss))
    } >RAM_DATA
#endif

    .kcpu_xram_image (NOLOAD): ALIGN(4)
    {
        . += (__kcpu_firmware_xram_size - 4);
        LONG(0);
    } >XRAM_DATA

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _OFF)
    .xram_bss (NOLOAD): ALIGN(4)
    {
        __linker_xram_bss_start__ = .;

        *(.xram_bss .xram_bss.*)
    } >XRAM_DATA

    .xram_data : ALIGN(4)
    {
        __linker_xram_data_start__ = .;

        *(.xram_data .xram_data.*)

        . = ALIGN(4);
    } >XRAM_DATA AT>_REGION_TEXT = 0xFF
#endif

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _ON)
    .ddr_bss (NOLOAD) : ALIGN(4)
    {
        __linker_ddr_bss_start__ = .;

        *(.ddr_bss .ddr_bss.*)
        *(.off_region_bss .off_region_bss.*)
    } >RAM_DATA

    .ddr_data : ALIGN(4)
    {
        __linker_ddr_data_start__ = .;

        *(.ddr_data .ddr_data.*)
        *(.off_region_data .off_region_data.*)

        . = ALIGN(4);
    } >RAM_DATA AT>_REGION_TEXT = 0xFF
#endif

    /*
     * This address is used by the startup code to
     * initialise the .data section.
     */
    _sidata = LOADADDR(.data);

    /*
     * The initialised data section.
     *
     * The program executes knowing that the data is in the RAM
     * but the loader puts the initial values in the FLASH (inidata).
     * It is one task of the startup to copy the initial values from
     * FLASH to RAM.
     */
    .data : ALIGN(4)
    {
        /* This is used by the startup code to initialise the .data section */
        /* STM specific definition */
        _sdata = .;
        __data_start__ = .;

        __linker_data_start__ = .;

        *(.data_begin .data_begin.*)

        *(.data .data.*)
        *(.sdata .sdata.*)

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _ON)
        *(.xram_data .xram_data.*)
#endif

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _OFF)
        *(.ddr_data .ddr_data.*)
        *(.off_region_data .off_region_data.*)
#endif

        *(.data_end .data_end.*)

        . = ALIGN(4);

        /* This is used by the startup code to initialise the .data section */
        /* STM specific definition */
        _edata = .;
        __data_end__ = .;
    } >_REGION_RAM AT>_REGION_TEXT = 0xFF

    .fast_data : ALIGN(4)
    {
        __linker_fast_data_start__ = .;

        *(.fast_data .fast_data.*)

        . = ALIGN(4);
    } >RAM_DMEM AT>_REGION_TEXT = 0xFF

    /*
     * The uninitialised data sections. NOLOAD is used to avoid
     * the "section `.bss' type changed to PROGBITS" warning
     */

    /* The primary uninitialised data section. */
    .bss (NOLOAD) : ALIGN(4)
    {
        /* standard newlib definition */
        __bss_start__ = .;
        /* STM specific definition */
        _sbss = .;

        __linker_bss_start__ = .;

        *(.bss_begin .bss_begin.*)

        *(.bss .bss.*)
        *(.sbss .sbss.*)

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _ON)
        *(.xram_bss .xram_bss.*)
#endif

#if(_CPU32_SCPU_PROGRAM_DATA_ON_XRAM == _OFF)
        *(.ddr_bss .ddr_bss.*)
        *(.off_region_bss .off_region_bss.*)
#endif

        *(COMMON)

        *(.bss_end .bss_end.*)

        . = ALIGN(4);

        /* standard newlib definition */
        __bss_end__ = .;
        /* STM specific definition */
        _ebss = .;
    } >_REGION_RAM

    .noinit (NOLOAD) : ALIGN(4)
    {
        _noinit = .;

        *(.noinit .noinit.*)

        . = ALIGN(4);
        _end_noinit = .;
    } > _REGION_RAM

    .clip.redirect : ALIGN(4)
    {
        SORT_BY_NAME(*)(.clip.redirect .clip.redirect.*)
    } >_REGION_TEXT

    .clip.text : ALIGN(4)
    {
        SORT_BY_NAME(*)(.clip.text .clip.text.*)
    } >_REGION_TEXT

    .clip.rodata : ALIGN(4)
    {
        SORT_BY_NAME(*)(.clip.rodata .clip.rodata.*)
    } >_REGION_TEXT

    /* Mandatory to be word aligned, _sbrk assumes this */
    /* was _ebss */
    PROVIDE ( end = _end_noinit );
    PROVIDE ( _end = _end_noinit );
    PROVIDE ( __end = _end_noinit );
    PROVIDE ( __end__ = _end_noinit );

    /*
     * Used for validation only, do not allocate anything here!
     *
     * This is just to check that there is enough RAM left for the Main
     * stack. It should generate an error if it's full.
     */
    ._check_stack : ALIGN(4)
    {
        . += _Main_Stack_Size;
    } >_REGION_STACK

    /* After that there are only debugging sections. */

    /* This can remove the debugging information from the standard libraries */
    /*
    DISCARD :
    {
     libc.a ( * )
     libm.a ( * )
     libgcc.a ( * )
     }
     */

    /* Stabs debugging sections.  */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }

    /*
     * DWARF debug sections.
     * Symbols in the DWARF debugging sections are relative to the beginning
     * of the section so we begin them at 0.
     */
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_ranges   0 : { *(.debug_ranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
}
