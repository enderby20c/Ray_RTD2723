/*
 * Default linker script for CPU32.
 *
 * To make use of the multi-region initialisations, define
 * OS_INCLUDE_STARTUP_INIT_MULTIPLE_RAM_SECTIONS for the _startup.c file.
 */

/*
 * The '__stack' definition is required by crt0, do not remove it.
 */
__stack = ORIGIN(RAM_DATA) + LENGTH(RAM_DATA);

/* STM specific definition */
_estack = __stack;

/*
 * Default stack sizes.
 * These are used by the startup in order to allocate stacks
 * for the different modes.
 */
/* 32KB stack size (Max SCPU compressed Kernel size = (2MB - 32KB)) */
__Main_Stack_Size = 32768;

PROVIDE ( _Main_Stack_Size = __Main_Stack_Size );

_Main_Stack_Size = (_Main_Stack_Size > __Main_Stack_Size) ? _Main_Stack_Size : __Main_Stack_Size ;

__Main_Stack_Limit = __stack  - _Main_Stack_Size ;

/* "PROVIDE" allows to easily override these values from an
 * object file or the command line. */
PROVIDE ( _Main_Stack_Limit = __Main_Stack_Limit );

/*
 * Default heap definitions.
 * The heap start immediately after the last statically allocated
 * .sbss/.noinit section, and extends up to the main stack limit.
 */
PROVIDE ( _Heap_Begin = _end_noinit );
PROVIDE ( _Heap_Limit = __stack - _Main_Stack_Size ) ;

/*
 * The entry point is informative, for debuggers and simulators,
 * since the CPU32 vector points to it anyway.
 */

ENTRY(Reset_Handler)

SECTIONS
{
    . = ORIGIN(FLASH_TEXT);
    .firmware_image_kcpu . : ALIGN(4)
    {
        KEEP(*(.firmware_image_kcpu))
    } >FLASH_TEXT

    /*
     * For CPU32 devices, the beginning of the startup code is stored in
     * the .isr_vector section, which goes to FLASH.
     */
    . = ALIGN(0x10000);
    .isr_vector . :
    {
        __vectors_start = ABSOLUTE(.);
        /* STM specific definition */
        __vectors_start__ = ABSOLUTE(.);

        /* Interrupt vectors */
        KEEP(*(.isr_vector))

        /*
         * This section is here for convenience, to store the
         * startup code at the beginning of the flash area, hoping that
         * this will increase the readability of the listing.
         */
        KEEP(*(.BootResetVector .BootResetVector.*))
        *(.reset_vectors .reset_vectors.*)
    } >FLASH_TEXT = 0xFF

    /* Startup code and ISR */
    . = ADDR(.isr_vector) + _SCPU_BOOT_DEFAULT_EXCEPTION_OFFSET;
    .after_vectors . : ALIGN(4)
    {
        *(.after_vectors.SysIntDefaultHandler)
        *(.after_vectors .after_vectors.*)
    } >FLASH_TEXT

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

        __data_regions_array_start = .;

        LONG(LOADADDR(.data));
        LONG(ADDR(.data));
        LONG(ADDR(.data)+SIZEOF(.data));

        LONG(LOADADDR(.fast_data));
        LONG(ADDR(.fast_data));
        LONG(ADDR(.fast_data)+SIZEOF(.fast_data));

        __data_regions_array_end = .;

        __bss_regions_array_start = .;

        LONG(ADDR(.bss));
        LONG(ADDR(.bss)+SIZEOF(.bss));

        __bss_regions_array_end = .;

#if(_EMBEDDED_RESOURCE_FILE_SUPPORT == _ON)
        __resource_info_region_start = .;
        LONG(ADDR(.resource_info) - __linker_constant_flash_base32__);
#endif

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
    } >FLASH_TEXT = 0xFF

    /*
     * The program code is stored in the .text section,
     * which goes to FLASH.
     */

    .text : ALIGN(4)
    {
        __text_data_start__ = .;

        __linker_text_start__ = .;

        /* all remaining code */
        *( .text .text.* )
        *(.ddr_text .ddr_text.*)

        /* fast text merged with .text */
        *(.fast_text .fast_text.*)

        /* C++ virtual tables */
        *( vtable )

        KEEP(*(.eh_frame*))

        __text_data_end__ = .;
    } >FLASH_TEXT = 0xFF

    .rodata : ALIGN(4)
    {
        __linker_rodata_start__ = .;

        /* keep used table */
        KEEP(*(.used_table .used_table.*))

        /* read-only data (constants) */
        *(.rodata .rodata.* .constdata .constdata.*)
        *(.srodata .srodata.*)
        *(.sdata2 .sdata2.*)
        *(.sbss2 .sbss2.*)
    } >FLASH_TEXT = 0xFF

#if(_CPU32_SCPU_PROGRAM_TEXT_ON_FLASH == _OFF)
    /* firmware image data */
    .firmware_image_scpu : ALIGN(16)
    {
        __scpu_firmware_image_load_address_start = .;
        KEEP(*(.firmware_image_scpu))
        __scpu_firmware_image_load_address_end = .;
    } >FLASH_TEXT
#endif

    . = ALIGN(4);
    _etext = .;
    __etext = .;

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

        *(.ddr_data .ddr_data.*)
        *(.off_region_data .off_region_data.*)

        *(.data_end .data_end.*)

        . = ALIGN(4);

        /* This is used by the startup code to initialise the .data section */
        /* STM specific definition */
        _edata = .;
        __data_end__ = .;
    } >RAM_DATA AT>FLASH_TEXT = 0xFF

    .fast_data : ALIGN(4)
    {
        __linker_fast_data_start__ = .;

        *(.fast_data .fast_data.*)

        . = ALIGN(4);
    } >RAM_DATA AT>FLASH_TEXT = 0xFF

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

        *(.ddr_bss .ddr_bss.*)
        *(.off_region_bss .off_region_bss.*)

        *(COMMON)

        *(.bss_end .bss_end.*)

        . = ALIGN(4);

        /* standard newlib definition */
        __bss_end__ = .;
        /* STM specific definition */
        _ebss = .;
    } >RAM_DATA AT> RAM_DATA /* workaround for .map file */

    .noinit (NOLOAD) : ALIGN(4)
    {
        _noinit = .;

        *(.noinit .noinit.*)

        . = ALIGN(4);
        _end_noinit = .;
    } > RAM_DATA

#if(_CPU32_SCPU_PROGRAM_TEXT_ON_FLASH == _ON)
    /* firmware image data */
    . = ORIGIN(FLASH_TEXT) + SIZEOF(.firmware_image_kcpu) + __scpu_firmware_boot_image_length;

    .firmware_image_scpu . : ALIGN(16)
    {
        KEEP(*(.firmware_image_scpu))
    } >FLASH_TEXT
#endif

#if(_EMBEDDED_RESOURCE_FILE_SUPPORT == _ON)
    .resource_info : ALIGN(4)
    {
        KEEP(*(.resource_info .resource_info.*))
    } >FLASH_TEXT

    .resource : ALIGN(4)
    {
        KEEP(*(.resource .resource.*))
    } >FLASH_TEXT
#endif

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
        . += _Main_Stack_Size ;
    } >RAM_DATA AT> RAM_DATA /* workaround for .map file */

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
