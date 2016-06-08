#include <stdlib.h>
#include "ARMasm.h"

// Branch

int32_t calculate_branch(enum mnemonic_code cond, char* operand) {
  cond -= 16;
  // Get the number from the string
  int32_t line_diff = strtol(operand, NULL, 10);
  // Need to account for the off-by-8 bytes effect from the ARM pipeline
  int32_t offset = line_diff * INSTRUCTION_BYTE_SIZE - PIPELINE_OFFSET;
  /* Bits 27-24 are always the same (1010). We want to shift the offset
     to the right by 2 and then store the lower 24 bytes in the instruction. */
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
