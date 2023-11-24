#include "packets.h"
#include <inttypes.h>
#include <stdlib.h>

typedef struct charop {
  char op;
  float f;
} charop_t;

void generate_charops(charop_t ops[], size_t length);
void convert_to_stream(charop_t ops[], size_t length, char* buf);
void accumulate_charops(charop_t ops[], size_t length);
void print_charop(charop_t charop);
