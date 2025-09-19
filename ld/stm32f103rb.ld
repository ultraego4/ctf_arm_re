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
    _etext = .;

  } > FLASH

  .data : 
  { 
    _sdata = .;
    *(.data) 
    _edata = .;

  } > SRAM AT > FLASH


  .bss : 
  {
    _sbss = .;
    *(.bss)
    _ebss = .;
    
  } > SRAM
}
