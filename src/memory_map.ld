MEMORY
{
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K
    CCMRAM (xrw)    : ORIGIN = 0x10000000, LENGTH = 64K
    BOOT_ROM (rx)   : ORIGIN = 0x8000000, LENGTH = 160K
    APP_ROM (rx)    : ORIGIN = 0x8040000, LENGTH = 864K
}

/* Flash layout: FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 1024K  */

PROVIDE(__bootrom_start__ = ORIGIN(BOOT_ROM));
PROVIDE(__bootrom_size__ = LENGTH(BOOT_ROM));
PROVIDE(__approm_start__ = ORIGIN(APP_ROM));
PROVIDE(__approm_size__ = LENGTH(APP_ROM));