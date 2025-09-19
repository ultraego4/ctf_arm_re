ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
  SRAM (rwx) : ORIGIN = 0X20000000, LENGTH = 20K
}


_estack = ORIGIN(SRAM) + LENGTH(SRAM);


/* need the symbols so in the startup code i can copy the .data from flash to ram*/

SECTIONS
{
  .text : 
  {
    *(.isr_vector)
    *(.text)
    *(.rodata)
    . = ALIGN(4);
    _etext = .;

  } > FLASH

  .data : 
  { 
    _sdata = .;
    *(.data)
    . = ALIGN(4);
    _edata = .;

  } > SRAM AT > FLASH


  .bss : 
  {
    _sbss = .;
    *(.bss)
    . = ALIGN(4);
    _ebss = .;
    
  } > SRAM
}
