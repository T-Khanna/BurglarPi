#include <stdlib.h>
#include "ARMasm.h"

// Branch
/* 
  For each of these instructions, there is only one operand. Due to the way
  we assigned the enum value to the function, the condition is always the
  mnemonic_code - 16. Bits 27-24 are 1010. Remaining is the 26-bit signed
  offset between the current address and the label, which should be shifted
  right two bits, only storing the lower 24 bits. This must also take into
  account the off-by-8 bytes effect from the ARM pipeline.
*/

int32_t calculate_branch(enum mnemonic_code cond, char* operand) {
  cond -= 16;
  int32_t line_diff = strtol(operand, NULL, 10);
  int32_t offset = line_diff * INSTRUCTION_BYTE_SIZE - PIPELINE_OFFSET;
  return (cond << 28) | 0x0a000000 | ((offset >> 2) & 0x00ffffff);
}

uint32_t ASMbeq(char * operands[]) {
  return calculate_branch(BEQ, operands[0]);
}

uint32_t ASMbne(char * operands[]) {
  return calculate_branch(BNE, operands[0]);
}

uint32_t ASMbge(char * operands[]) {
  return calculate_branch(BGE, operands[0]);
}

uint32_t ASMblt(char * operands[]) {
  return calculate_branch(BLT, operands[0]);
}

uint32_t ASMbgt(char * operands[]) {
  return calculate_branch(BGT, operands[0]);
}

uint32_t ASMble(char * operands[]) {
  return calculate_branch(BLE, operands[0]);
}

uint32_t ASMb(char * operands[]) {
  return calculate_branch(B, operands[0]);
}
