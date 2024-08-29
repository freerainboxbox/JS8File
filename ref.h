#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

typedef const struct codeword{
    const uint8_t key;
    const uint8_t bits;
} codeword;