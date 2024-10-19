MEMORY
{
    FLASH_TEXT            (xr)    : ORIGIN = 0x00000000, LENGTH = 16384K
    ITCM_TEXT             (xrw)   : ORIGIN = 0x20000000, LENGTH = 8K

    /* dmem */
    RAM_DMEM              (xrw)   : ORIGIN = 0x30000000, LENGTH = 4K

    /* DDR */
    RAM_TEXT              (xrw)   : ORIGIN = _SCPU_DDR_TEXT_BASE_ADDR, LENGTH = _CPU32_SCPU_DDR_TEXT_SIZE
    RAM_DATA              (xrw)   : ORIGIN = _SCPU_DDR_DATA_BASE_ADDR, LENGTH = _CPU32_SCPU_DDR_DATA_SIZE

    /* share ram */
    XRAM_DATA             (xrw)   : ORIGIN = 0xA0100000, LENGTH = 25K
}
