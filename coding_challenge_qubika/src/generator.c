#include "../inc/generator.h"
#include <stdio.h>
#include <sys/random.h>
#include <time.h>

#define MEAN 50
#define VARIANCE 50
#define CRPTD 0x7F

uint8_t possible_ops[] = {ADD, SUBS, MUL, DIV, PRNT, RST, CRPTD};

void generate_charops(charop_t ops[], size_t length) {
  srand((unsigned int)time(NULL));
  for (size_t i = 0; i < (length - 1); i++) {
    uint8_t temp;
    getrandom(&(temp), sizeof(uint8_t), GRND_NONBLOCK);
    ops[i].op = possible_ops[(temp % 6)];
    ops[i].f = (((float)rand() / (float)(RAND_MAX)) * VARIANCE) + MEAN;
    srand(*((unsigned int*)&(ops[i].f)));
  }
  ops[length - 1].op = PRNT;
}

void convert_to_stream(charop_t ops[], size_t length, char* buf) {
  size_t cursor = 0;
  for (size_t i = 0; i < length; i++) {
    buf[cursor] = STX;
    cursor++;
    buf[cursor] = ops[i].op;
    cursor++;
    int written = sprintf((char*)(buf + cursor), "%f", ops[i].f);
    cursor += written;
    buf[cursor] = ETX;
    cursor++;
  }
}

void accumulate_charops(charop_t ops[], size_t length) {
  float accumulator = 0;
  for (size_t i = 0; i < length; i++) {
    switch (ops[i].op) {
    case ADD:
      accumulator += ops[i].f;
      break;
    case SUBS:
      accumulator -= ops[i].f;
      break;
    case MUL:
      accumulator = accumulator * ops[i].f;
      break;
    case DIV:
      accumulator = accumulator / ops[i].f;
      break;
    case PRNT:
      printf("%f\n", accumulator);
      break;
    case RST:
      accumulator = 0;
      break;
    default:
      break;
    }
  }
}

void print_charop(charop_t charop) {
  char op;
  uint8_t voper;
  switch (charop.op) {
  case ADD:
    op = '+';
    voper = 1;
    break;
  case SUBS:
    op = '-';
    voper = 1;
    break;
    break;
  case MUL:
    op = '*';
    voper = 1;
    break;
    break;
  case DIV:
    op = '/';
    voper = 1;
    break;
    break;
  case PRNT:
    op = 'P';
    voper = 0;
    break;
    break;
  case RST:
    op = 'R';
    voper = 0;
    break;
    break;
  default:
    break;
  }
  if (voper) {
    printf("%c %f\n", op, charop.f);
  } else {
    printf("%c ---\n", op);
  }
}
