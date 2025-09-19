/* 1. vector table */
/* 2. init .data and .bss with zeroes in ram */
/* 3. call main() */

/* refernce for the vector table, table61
 * https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf*/

/* FLASH memory layout*/

/* unused memory*/
/* .data */
/* .rodata */
/* .text */
/* vector table*/

#include <stdint.h>

extern uint32_t _estack;

extern uint32_t _etext;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void Default_Handler(void);

int main(void);

/* create its own section to put it before .text so no other code will
 * accidentally be the first, handled in the .ld */
__attribute__((section(".isr_vector"))) const uint32_t vector_table[] = {
    (uint32_t)&_estack,        // 0x00: Initial stack pointer (MSP)
    (uint32_t)Reset_Handler,   // 0x04: Reset
    (uint32_t)Default_Handler, // 0x08: NMI
    (uint32_t)Default_Handler, // 0x0C: HardFault
    (uint32_t)Default_Handler, // 0x10: MemManage
    (uint32_t)Default_Handler, // 0x14: BusFault
    (uint32_t)Default_Handler, // 0x18: UsageFault
    0,                         // 0x1C: Reserved
    0, 0, 0, 0,                // 0x20-0x2B: Reserved / padding
    (uint32_t)Default_Handler, // 0x2C: SVCall
    (uint32_t)Default_Handler, // 0x30: Debug Monitor
    0,                         // 0x34: Reserved
    (uint32_t)Default_Handler, // 0x38: PendSV
    (uint32_t)Default_Handler, // 0x3C: SysTick

    // Peripheral interrupts start here
    (uint32_t)Default_Handler, // 0x40: WWDG
    (uint32_t)Default_Handler, // 0x44: PVD
    (uint32_t)Default_Handler, // 0x48: TAMPER
    (uint32_t)Default_Handler, // 0x4C: RTC
    (uint32_t)Default_Handler, // 0x50: FLASH
    (uint32_t)Default_Handler, // 0x54: RCC
    (uint32_t)Default_Handler, // 0x58: EXTI0
    (uint32_t)Default_Handler, // 0x5C: EXTI1
    (uint32_t)Default_Handler, // 0x60: EXTI2
    (uint32_t)Default_Handler, // 0x64: EXTI3
    (uint32_t)Default_Handler, // 0x68: EXTI4
    (uint32_t)Default_Handler, // 0x6C: DMA1_Channel1
    (uint32_t)Default_Handler, // 0x70: DMA1_Channel2
    (uint32_t)Default_Handler, // 0x74: DMA1_Channel3
    (uint32_t)Default_Handler, // 0x78: DMA1_Channel4
    (uint32_t)Default_Handler, // 0x7C: DMA1_Channel5
    (uint32_t)Default_Handler, // 0x80: DMA1_Channel6
    (uint32_t)Default_Handler, // 0x84: DMA1_Channel7
    (uint32_t)Default_Handler, // 0x88: ADC1_2
    (uint32_t)Default_Handler, // 0x8C: USB_HP_CAN_TX
    (uint32_t)Default_Handler, // 0x90: USB_LP_CAN_RX0
    (uint32_t)Default_Handler, // 0x94: CAN_RX1
    (uint32_t)Default_Handler, // 0x98: CAN_SCE
    (uint32_t)Default_Handler, // 0x9C: EXTI9_5
    (uint32_t)Default_Handler, // 0xA0: TIM1_BRK
    (uint32_t)Default_Handler, // 0xA4: TIM1_UP
    (uint32_t)Default_Handler, // 0xA8: TIM1_TRG_COM
    (uint32_t)Default_Handler, // 0xAC: TIM1_CC
    (uint32_t)Default_Handler, // 0xB0: TIM2
    (uint32_t)Default_Handler, // 0xB4: TIM3
    (uint32_t)Default_Handler, // 0xB8: TIM4
    (uint32_t)Default_Handler, // 0xBC: I2C1_EV
    (uint32_t)Default_Handler, // 0xC0: I2C1_ER
    (uint32_t)Default_Handler, // 0xC4: I2C2_EV
    (uint32_t)Default_Handler, // 0xC8: I2C2_ER
    (uint32_t)Default_Handler, // 0xCC: SPI1
    (uint32_t)Default_Handler, // 0xD0: SPI2
    (uint32_t)Default_Handler, // 0xD4: USART1
    (uint32_t)Default_Handler, // 0xD8: USART2
    (uint32_t)Default_Handler, // 0xDC: USART3
    (uint32_t)Default_Handler, // 0xE0: EXTI15_10
    (uint32_t)Default_Handler, // 0xE4: RTCAlarm
    (uint32_t)Default_Handler, // 0xE8: USBWakeup
    (uint32_t)Default_Handler, // 0xEC: TIM8_BRK
    (uint32_t)Default_Handler, // 0xF0: TIM8_UP
    (uint32_t)Default_Handler, // 0xF4: TIM8_TRG_COM
    (uint32_t)Default_Handler, // 0xF8: TIM8_CC
    (uint32_t)Default_Handler, // 0xFC: ADC3
    (uint32_t)Default_Handler, // 0x100: FSMC
    (uint32_t)Default_Handler, // 0x104: SDIO
    (uint32_t)Default_Handler, // 0x108: TIM5
    (uint32_t)Default_Handler, // 0x10C: SPI3
    (uint32_t)Default_Handler, // 0x110: UART4
    (uint32_t)Default_Handler, // 0x114: UART5
    (uint32_t)Default_Handler, // 0x118: TIM6
    (uint32_t)Default_Handler, // 0x11C: TIM7
    (uint32_t)Default_Handler, // 0x120: DMA2_Channel1
    (uint32_t)Default_Handler, // 0x124: DMA2_Channel2
    (uint32_t)Default_Handler, // 0x128: DMA2_Channel3
    (uint32_t)Default_Handler, // 0x12C: DMA2_Channel4_5
};

void Reset_Handler(void) {

  // copy .data to sram

  uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;

  uint8_t *pDst = (uint8_t *)&_sdata; // sram
  uint8_t *pSrc = (uint8_t *)&_etext; // flash

  for (uint32_t i = 0; i < size; i++) {
    *pDst++ = *pSrc++;
  }

  // zero out .bss

  size = (uint32_t)&_ebss - (uint32_t)&_sbss;

  pDst = (uint8_t *)&_sbss;
  pSrc = (uint8_t *)&_ebss;

  for (uint32_t i = 0; i < size; i++) {
    *pDst++ = 0;
  }

  // call main

  main();
}

void Default_Handler(void) {
  while (1)
    ;
}
