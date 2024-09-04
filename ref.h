#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
// DEFAULT SETTING: 524288
// 512 KiB, packed (bytes read from stdin)
// 4 MiB, unpacked (512 KiB worth of bits stored in bitbuf)
// Changed for debugging purposes
#define BUF_SIZE 524288

typedef const struct codeword{
    const uint8_t key;
    const uint8_t bits;
} codeword;