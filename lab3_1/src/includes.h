#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

uint32_t generate_number();
size_t encode_varint(uint32_t, uint8_t*);
uint32_t decode_varint(const uint8_t**);