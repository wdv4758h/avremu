#include <avr/io.h>
#include <stdio.h>

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
                                         _FDEV_SETUP_WRITE);
static int
uart_putchar(char c, FILE *stream)
{
    UDR = c;
    return 0;
}

volatile uint16_t xxx = 65;

int
main(void)
{
    stdout = &mystdout;
    printf("Hello, world!");

    asm volatile("break;");


    volatile float foo = 0.23;
    printf("%.2f", foo);

    asm volatile("break;");


    return 0;
}


/**
   check-name: Print to Stdout and Float
   check-start:

   \avr@instr@stepn{100000}
   \avr@test@UDR{Hello, world!}
   \xdef\avr@UDR{}

   \avr@instr@stepn{100000}
   \avr@test@UDR{0.23}
   \def\avr@UDR{}
   check-end:
**/
