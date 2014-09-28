#include <avr/io.h>

volatile char foo[30];

int main() {
  foo[0] = 23;
  foo[1] = 42;
  // Should produce a mul
  foo[2] = foo[0] * foo[1];

  // Contains a decrement (8 Bit Dividend)
  foo[3] = (unsigned char)((unsigned char )foo[1] / (unsigned char)foo[0]);

  foo[4] = foo[1] % foo[0];

  asm volatile ("break");
}

/*
  check-name: Complex Memory Operations
  check-start:
  \avr@instr@stepn{100000}

  \avr@test@MEM{96}{00010111} % 23
  \avr@test@MEM{97}{00101010} % 42
  \avr@test@MEM{98}{11000110} % 198

  \avr@test@MEM{99}{00000001} % 1
  \avr@test@MEM{100}{00010011} % 19

  check-end:
*/
