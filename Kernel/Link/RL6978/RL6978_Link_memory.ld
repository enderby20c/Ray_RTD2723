MEMORY
{
    FLASH_TEXT                    (xr)    : ORIGIN = 0x00000000, LENGTH = 16384K
    BOOT_RESET_TEXT               (xr)    : ORIGIN = 0x00002000, LENGTH = 0x180
    BOOT_EXCEPTION_TEXT           (xr)    : ORIGIN = 0x00002180, LENGTH = 640
    ITCM_TEXT                     (xrw)   : ORIGIN = 0x20000000, LENGTH = 8K

    /* dmem */
    RAM_DATA                      (xrw)   : ORIGIN = 0x30000000, LENGTH = 8K

    /* DDR */
    DDR_TEXT                      (xrw)   : ORIGIN = 0x60000000, LENGTH = 2048K
    DDR_DATA                      (xrw)   : ORIGIN = 0x60200000, LENGTH = 2048K

    /* share ram */
    XRAM_DATA                     (xrw)   : ORIGIN = 0xA0100000, LENGTH = 20K
}
