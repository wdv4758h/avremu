#include <avr/io.h>
#include <stdio.h>

volatile char buffer[30];

volatile uint16_t xxx = 165;

int
main(void)
{
    asm volatile("break;");

    // sprintf(buffer, "%d", xxx);
    __ultoa_invert(xxx, buffer, 10);

    asm volatile("break;");


    return 0;
}


/**
   check-name: Print to Stdout
   check-start:

   \avr@instr@stepn{100000}
   \avr@instr@executed=0
   \avr@instr@stepn{100000}

   \avr@test@MEM{96}{00110001} % '1'
   \avr@test@MEM{97}{00110110} % '6'
   \avr@test@MEM{98}{00110101} % '5'   

   check-end:
**/
