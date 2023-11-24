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

enum OPCODE {
  ADD = 0x11,
  SUBS = 0x12,
  MUL = 0x13,
  DIV = 0x14,
  PRNT = 0x0A,
  RST = 0x18,
};

enum statescodes {
  pSTX,
  pOPC,
  pOPE_ETX,
};

enum retcodes {
  OK,
  FAIL,
  REPEAT,
  SRT_OVER,
};

struct parsed_op {
  uint8_t opcode;
  float operand;
} parsed_op;

struct parsed_operand {
  uint8_t length;
  char buf[100];
} parsed_operand;

float accumulator;

typedef struct transition {
  enum statescodes src;
  enum retcodes ret;
  enum statescodes dest;
} transitions;

transitions state_transitions[] = {
    {pSTX, OK, pOPC},       {pOPC, OK, pOPE_ETX},       {pOPE_ETX, REPEAT, pOPE_ETX}, {pOPE_ETX, OK, pSTX},
    {pSTX, FAIL, pSTX},     {pOPC, FAIL, pSTX},         {pOPE_ETX, FAIL, pSTX},       {pSTX, SRT_OVER, pOPC},
    {pOPC, SRT_OVER, pOPC}, {pOPE_ETX, SRT_OVER, pOPC},
};

void accumulate(void) {
  switch (parsed_op.opcode) {
  case ADD:
    accumulator += parsed_op.operand;
    break;
  case SUBS:
    accumulator -= parsed_op.operand;
    break;
  case MUL:
    accumulator = accumulator * parsed_op.operand;
    break;
  case DIV:
    accumulator = accumulator / parsed_op.operand;
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

// STATE FUNCTIONS
int pSTX_state(char curr_char) {
  if (curr_char != STX)
    return FAIL;
  return OK;
}

int pOPC_state(char curr_char) {
  switch (curr_char) {
  case ADD:
    parsed_op.opcode = ADD;
    break;
  case SUBS:
    parsed_op.opcode = SUBS;
    break;
  case MUL:
    parsed_op.opcode = MUL;
    break;
  case DIV:
    parsed_op.opcode = DIV;
    break;
  case PRNT:
    parsed_op.opcode = PRNT;
    break;
  case RST:
    parsed_op.opcode = RST;
    break;
  case STX:
    return SRT_OVER;
    break;
  default:
    return FAIL;
    break;
  }
  return OK;
}

int pOPE_state(char curr_char) {
  uint8_t isValidNum = ((curr_char >= '0') && (curr_char <= '9') || curr_char == '.');
  if (isValidNum) {
    parsed_operand.buf[parsed_operand.length] = curr_char;
    parsed_operand.length++;
    return REPEAT;
  } else if (curr_char == ETX) {
    parsed_operand.buf[parsed_operand.length] = 0x00;
    parsed_operand.length = 0;

    sscanf(parsed_operand.buf, "%f", &(parsed_op.operand));
    accumulate();
    return OK;
  } else {
    parsed_operand.length = 0;
    return FAIL;
  }
}

int (*state[])(char) = {pSTX_state, pOPC_state, pOPE_state};

// AUX FUNCS
enum statescodes transition_lookup(enum statescodes cur_state, enum retcodes ret_code) {
  int length = sizeof(state_transitions) / sizeof(transitions);
  for (int i = 0; i < length; i++) {
    if ((state_transitions[i].src == cur_state) && (state_transitions[i].ret == ret_code))
      return state_transitions[i].dest;
  }
  return pSTX;
}

void process_packets(char* data, int len) {
  int (*state_fun)(char);
  enum statescodes current_state = pSTX;
  enum retcodes rc;

  accumulator = 0;
  parsed_operand.length = 0;
  parsed_op.opcode = -1;
  parsed_op.operand = 0;

  for (int i = 0; i < len; i++) {
    state_fun = state[current_state];
    rc = state_fun(data[i]);
    current_state = transition_lookup(current_state, rc);
  }
  return;
}

int main(void) {
  size_t s1_len = sizeof(s1);
  process_packets(s1, s1_len);
  size_t s2_len = sizeof(s2);
  process_packets(s2, s2_len);
  return 0;
}
