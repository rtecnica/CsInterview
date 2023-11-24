#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#define STX 0x02
#define ETX 0x03

// GLOBALS
char s1[] = {0x02, 0x11, 0x31, 0x32, 0x2E, 0x31, 0x03, 0x02, 0x13, 0x32, 0x03, 0x02, 0x12, 0x33, 0x03,
             0x02, 0x0A, 0x03, 0x02, 0x18, 0x03, 0x02, 0x11, 0x32, 0x30, 0x30, 0x03, 0x02, 0x0A, 0x03};
char s2[] = {0x02, 0x11, 0x31, 0x32, 0x2E, 0x31, 0x03, 0x02, 0x13, 0x32, 0x03, 0x02, 0x02, 0x12, 0x33, 0x03,
             0x03, 0x02, 0x0A, 0x03, 0x02, 0x18, 0x03, 0x02, 0x11, 0x32, 0x30, 0x30, 0x03, 0x02, 0x0A, 0x03};

enum state {
  WAIT_START,
  PARSING_OPCODE,
  PARSING_OPERAND,
};

enum OPCODE {
  ADD = 0x11,
  SUBS = 0x12,
  MUL = 0x13,
  DIV = 0x14,
  PRNT = 0x0A,
  RST = 0x18,
};

struct operation {
  uint8_t opcode;
  float operand;
} operation;

float accumulator;
char buf[100];
uint8_t buf_len;

void accumulate(void) {
  switch (operation.opcode) {
  case ADD:
    accumulator += operation.operand;
    break;
  case SUBS:
    accumulator -= operation.operand;
    break;
  case MUL:
    accumulator = accumulator * operation.operand;
    break;
  case DIV:
    accumulator = accumulator / operation.operand;
    break;
  case PRNT:
    printf("%f\n", accumulator);
    break;
  case RST:
    accumulator = 0;
    break;
  default:
    return;
  }
  return;
}

uint8_t state_machine(uint8_t state, char input) {
  switch (state) {
  case WAIT_START:
    if (input == STX)
      return PARSING_OPCODE;
    break;
  case PARSING_OPCODE:
    switch (input) {
    case ADD:
      break;
    case SUBS:
      break;
    case MUL:
      break;
    case DIV:
      break;
    case PRNT:
      break;
    case RST:
      break;
    default:
      return WAIT_START;
      break;
    }
    operation.opcode = (uint8_t)input;
    return PARSING_OPERAND;
    break;

  case PARSING_OPERAND:
    if (input == ETX) {
      buf[buf_len] = 0;
      buf_len = 0;
      sscanf(buf, "%f", &(operation.operand));
      accumulate();
      return WAIT_START;
    }
    if (((input < '0') || (input > '9')) && (input != '.'))
      return WAIT_START;
    buf[buf_len] = input;
    buf_len++;
    return PARSING_OPERAND;
    break;
  }
  return WAIT_START;
}

void process_packets(char* stream, size_t str_len) {
  accumulator = 0;
  operation.opcode = 0;
  operation.operand = 0;
  buf_len = 0;
  uint8_t curr_state = WAIT_START;
  for (size_t i = 0; i < str_len; i++) {
    curr_state = state_machine(curr_state, stream[i]);
  }
}

int main(void) {
  size_t s1_len = sizeof(s1);
  process_packets(s1, s1_len);
  size_t s2_len = sizeof(s2);
  process_packets(s2, s2_len);
  return 0;
}
