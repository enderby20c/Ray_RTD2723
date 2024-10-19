MEMORY
{
    /* share ram */
    XRAM_TEXT                     (xrw)   : ORIGIN = 0x80100000, LENGTH = 25K

    ITCM_TEXT                     (xrw)   : ORIGIN = 0x85000000, LENGTH = 4K
    FLASH_TEXT                    (xr)    : ORIGIN = 0x86000000, LENGTH = 16384K

    BOOT_RESET_TEXT               (xr)    : ORIGIN = 0x86002000, LENGTH = 0x180
    BOOT_EXCEPTION_TEXT           (xr)    : ORIGIN = 0x86002180, LENGTH = 640

    /* share ram */
    XRAM_DATA                     (xrw)   : ORIGIN = 0xA0100000, LENGTH = 25K

    /* dmem */
    RAM_DATA                      (xrw)   : ORIGIN = 0xA5100000, LENGTH = 8K

    RESET_VECTOR_REDIRECT         (xr)    : ORIGIN = 0xBFC00000, LENGTH = 16
    EXCEPTION_VECTOR_REDIRECT     (xr)    : ORIGIN = 0xBFC00180, LENGTH = 24
}
