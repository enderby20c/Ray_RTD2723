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
/* 6KB stack size */
__Main_Stack_Size = 6144;

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

/* Placeholder for flash bank count
 * Will be replaced later by auto-link32
 */
__flash_bank_count__ = 0;

/*
 * The entry point is informative, for debuggers and simulators,
 * since the CPU32 vector points to it anyway.
 */

ENTRY(ResetVectorRedirect)

SECTIONS
{
    /* Keep Reset Vector Redirect Code */
    . = ORIGIN(RESET_VECTOR_REDIRECT);
    .ResetVectorRedirect . (NOLOAD): ALIGN(4)
    {
        KEEP(*(.ResetVectorRedirect))
    } >RESET_VECTOR_REDIRECT

    /* Keep Exception Vector Redirect Code */
    . = ORIGIN(EXCEPTION_VECTOR_REDIRECT);
    .ExceptionVectorRedirect . (NOLOAD) : ALIGN(4)
    {
        KEEP(*(.ExceptionVectorRedirect))
    } >EXCEPTION_VECTOR_REDIRECT

    /*
     * The initialised ItcmRegion section.
     *
     * ITCM Region execute from CPU Core ITCM
     *
     * The program executes knowing that the data is in the ITCM
     * but the loader puts the initial values in the Flash (inidata).
     * It is one task of the startup to set hardware to init the values from
     * flash to ITCM.
     */
    . = ORIGIN(ITCM_TEXT);
    .itcm_section . : AT(ORIGIN(FLASH_TEXT)) ALIGN(4)
    {
        KEEP(*(.ExceptionVector.itcm_section))
        KEEP(*(.ISR_TABLE.itcm_section))

        /* Interrupt handler && other fast-response function */
        *(.itcm_section .itcm_section.*)
    } >ITCM_TEXT = 0xFF

    /* reset vector in flash */
    . = ORIGIN(BOOT_RESET_TEXT);
    .BootResetVector . : ALIGN(4)
    {
        KEEP(*(.BootResetVector))
    } >FLASH_TEXT = 0xFF

    /* Simple Boot exception vector (before ITCM init.) in flash */
    . = ORIGIN(BOOT_EXCEPTION_TEXT);
    .BootExceptionVector . : ALIGN(4)
    {
        KEEP(*(.BootExceptionVector))
    } >FLASH_TEXT = 0xFF

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

        LONG(LOADADDR(.fast_text));
        LONG(ADDR(.fast_text));
        LONG(ADDR(.fast_text)+SIZEOF(.fast_text));

        __data_regions_array_end = .;

        __bss_regions_array_start = .;

        LONG(ADDR(.bss));
        LONG(ADDR(.bss)+SIZEOF(.bss));

        __bss_regions_array_end = .;

        __off_region_data_regions_array_start = .;

        LONG(LOADADDR(.off_region_data));
        LONG(ADDR(.off_region_data));
        LONG(ADDR(.off_region_data)+SIZEOF(.off_region_data));

        __off_region_data_regions_array_end = .;

        __off_region_bss_regions_array_start = .;

        LONG(ADDR(.off_region_bss));
        LONG(ADDR(.off_region_bss)+SIZEOF(.off_region_bss));

        __off_region_bss_regions_array_end = .;

#if(_EMBEDDED_RESOURCE_FILE_SUPPORT == _ON)
        __resource_info_region_start = .;
#if(_SCPU_SUPPORT == _ON)
        LONG(0x00000000);
#else
        LONG(ADDR(.resource_info) - __linker_constant_flash_base32__);
#endif
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
    } >FLASH_TEXT

    /* Startup code and ISR */
    .after_vectors : ALIGN(4)
    {
        *(.after_vectors .after_vectors.*)
    } >FLASH_TEXT

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

        /* C++ virtual tables */
        *(vtable)

        KEEP(*(.eh_frame*))

        __text_data_end__ = .;
    } >FLASH_TEXT = 0xFF

    .rodata : ALIGN(4)
    {
        __linker_rodata_start__ = .;

        /* keep used table */
        KEEP(*(.used_table  .used_table.*))

         /* read-only data (constants) */
        *(.rodata .rodata.* .constdata .constdata.*)
    } >FLASH_TEXT = 0xFF

    __kcpu_firmware_xram_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.fast_text);

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
        *(.xram_data .xram_data.*)

        *(.data_end .data_end.*)

        . = ALIGN(4);

        /* This is used by the startup code to initialise the .data section */
        /* STM specific definition */
        _edata = .;
        __data_end__ = .;
    } >XRAM_DATA AT>FLASH_TEXT = 0xFF

    .off_region_data : ALIGN(4)
    {
        *(.off_region_data .off_region_data.*)

        . = ALIGN(4);
    } >XRAM_DATA AT>FLASH_TEXT = 0xFF

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
        *(.xram_bss .xram_bss.*)

        *(COMMON)

        *(.bss_end .bss_end.*)

        . = ALIGN(4);

        /* standard newlib definition */
        __bss_end__ = .;
        /* STM specific definition */
        _ebss = .;
    } >XRAM_DATA

    .off_region_bss (NOLOAD) : ALIGN(4)
    {
        *(.off_region_bss .off_region_bss.*)

        . = ALIGN(4);
    } >XRAM_DATA

    .fast_text (ADDR(.off_region_bss) + SIZEOF(.off_region_bss) - 0x20000000) : ALIGN(4)
    {
        __linker_fast_text_start__ = .;

        *(.fast_text .fast_text.*)

        . = ALIGN(4);
        __linker_fast_text_end__ = .;
    } >XRAM_TEXT AT>FLASH_TEXT = 0xFF

    .noinit (ADDR(.fast_text) + SIZEOF(.fast_text) + 0x20000000)(NOLOAD) : ALIGN(4)
    {
        _noinit = .;

        *(.noinit .noinit.*)

         . = ALIGN(4);
        _end_noinit = .;
    } > XRAM_DATA

    .clip.redirect : ALIGN(65536)
    {
        SORT_BY_NAME(*)(.clip.redirect .clip.redirect.*)
    } >FLASH_TEXT

    .clip.text : ALIGN(4)
    {
        SORT_BY_NAME(*)(.clip.text .clip.text.*)
    } >FLASH_TEXT

    .clip.rodata : ALIGN(4)
    {
        SORT_BY_NAME(*)(.clip.rodata .clip.rodata.*)
    } >FLASH_TEXT

#if(_EMBEDDED_RESOURCE_FILE_SUPPORT == _ON)
#if(_SCPU_SUPPORT == _ON)
    .resource_info   0 : { *(.resource_info .resource_info.*) }
    .resource        0 : { *(.resource .resource.*) }
#else
    .resource_info : ALIGN(4)
    {
        KEEP(*(.resource_info .resource_info.*))
    } >FLASH_TEXT

    .resource : ALIGN(4)
    {
        KEEP(*(.resource .resource.*))
    } >FLASH_TEXT
#endif
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
        . += _Main_Stack_Size;
    } >RAM_DATA

    DISCARD :
    {
        *(.ddr_text .ddr_text.*)
        *(.ddr_data .ddr_data.*)
        *(.ddr_bss .ddr_bss.*)
    /* After that there are only debugging sections. */

    /* This can remove the debugging information from the standard libraries */
    /*
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    */
    }

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
    .MIPS.abiflags   0 : { *(.MIPS.abiflags) }
    .reginfo         0 : { *(.reginfo) }
}
