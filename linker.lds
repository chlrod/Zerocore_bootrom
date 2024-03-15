OUTPUT_ARCH( "riscv" )
ENTRY(_prog_start)

SECTIONS
{
    ROM_BASE = 0xc0000000; /* ... but actually position independent */

    . = ROM_BASE;

    .text.init : { *(.text.init) }

    .text : {
    _TEXT_START_ = .;
        *(.text)
    _TEXT_END_ = .;
    }

    .data : {
    _DATA_START_ = .;
        *(.data)
    _DATA_END_ = .;
    }

    PROVIDE(_data = ADDR(.data));
    PROVIDE(_data_lma = LOADADDR(.data));
    PROVIDE(_edata = .);

    .rodata : {
    _RODATA_START_ = .;
        *(.rodata) 
        /* *(.dtb*) */
        *(.rodata*)
    _RODATA_END_ = .;
    }

    .bss : {
    _BSS_START_ = .;
        *(.bss)
        *(.sbss .sbss.*)
    _BSS_END_ = .;
    }

}
