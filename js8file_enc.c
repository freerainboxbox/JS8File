#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "js8file_enc.h"

// From stdin
void fill_buffer(bool *bitbuf, unsigned int *buf_size){
    // Justify remaining buffer back to the beginning
    if(*buf_size > 0){
        memmove(bitbuf, bitbuf + *buf_size, *buf_size);
    }
    // Read from stdin (indeterminate length), keep track of buffer size
    *buf_size += fread(bitbuf + *buf_size, sizeof(bool), 4 * 1024 * 1024 - *buf_size, stdin);
}

int main(){
    bool bitbuf[4 * 1024 * 1024]; // 4 MiB, not packed
    unsigned int buf_size = 0;
    
}