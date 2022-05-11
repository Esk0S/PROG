#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "command.h"

enum {
    MaxCodeLength = 4
};

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnits;

int encode(uint32_t, CodeUnits*);
uint32_t decode(const CodeUnits *code_unit);
int write_code_unit(FILE *out, const CodeUnits *code_units);
int read_next_code_unit(FILE *in, CodeUnits *code_units);