#include "js8file_enc.h"

// From stdin
bool fill_buffer(bool * bitbuf, size_t * buf_size, bool * bitbuf_read_head){
    // Justify remaining buffer back to the beginning
    if(*buf_size > 0){
        memmove(bitbuf, bitbuf + *buf_size, *buf_size);
    }
    // Read from stdin (indeterminate length), keep track of buffer size
    char buf[(4 * 1024 * 1024)/8];
    size_t increase = fread(buf, 1, sizeof(buf), stdin);
    // Extract bits from byte buffer
    for(size_t i = 0; i < increase; i++){
        for(int j = 0; j < 8; j++){
            bitbuf[*buf_size] = (buf[i] >> (7 - j)) & 1;
            (*buf_size)++;
        }
    }
    bitbuf_read_head = bitbuf + *buf_size;
    return increase > 0;
}

int main(){
    bool bitbuf[4 * 1024 * 1024]; // 4 MiB, not packed
    bool * bitbuf_read_head = bitbuf;
    size_t buf_size = 0; // In bits
    while(true){
        if(buf_size < 8){ // 8 bits, length of longest key
            bitbuf_read_head = bitbuf;
            if(!fill_buffer(bitbuf, &buf_size)){
                break;
            }
        }
        int max_key_size = (buf_size < 8) ? buf_size : 8;
        // Produce keys in descending order, check for first match, write to stdout, then move buffer head
        for(int key_size = max_key_size; key_size > 0; key_size--){
            uint8_t key = 0;
            for(int i = 0; i < key_size; i++){
                key |= bitbuf_read_head[i] << (key_size - i - 1);
            }
            if(LUT[key]){
                putchar(LUT[key]);
                bitbuf_read_head += key_size;
                buf_size -= key_size;
                break;
            }
        }
    }
    // Flush stdout
    putchar('\n');
}