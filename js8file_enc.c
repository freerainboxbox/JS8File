#include "js8file_enc.h"

// From stdin
bool fill_buffer(bool * bitbuf, size_t * buf_size, bool * bitbuf_read_head){
    // Justify remaining buffer back to the beginning
    if(*buf_size > 0){
        memmove(bitbuf, bitbuf + *bitbuf_read_head, *buf_size);
    }
    // Read from stdin (indeterminate length), keep track of buffer size
    char buf[(4 * 1024 * 1024)/8];
    // The max bytes here is sizeof(buf) - ceil(*buf_size/8) expressed in a roundabout way.
    // This will fill our byte buffer as much as possible for the bit buffer to be near-full in the next step.
    size_t increase = fread(buf, 1, sizeof(buf) - ((*buf_size+8-1)/8), stdin);
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
    printf("FILE:");
    bool bitbuf[4 * 1024 * 1024]; // 4 MiB, not packed
    bool * bitbuf_read_head = bitbuf;
    size_t buf_size = 0; // In bits
    while(true){
        if(buf_size < 8){ // 8 bits, length of longest key
            if(!fill_buffer(bitbuf, &buf_size, bitbuf_read_head)){
                // There may still be bits remaining (<8), encode the rest
                while(buf_size > 0){
                    for(int i = buf_size; i > 0; i--){
                        if(LUT[i] == NULL){
                            continue;
                        }
                        uint8_t key = 0;
                        for(int j = 0; j < i; j++){
                            key |= bitbuf_read_head[j] << (i - j - 1);
                        }
                        if(LUT[i][key] != 0){
                            putchar(LUT[i][key]);
                            bitbuf_read_head += i;
                            buf_size -= i;
                            break;
                        }
                    }
                }
                break;
            }
        }
        int max_key_size = (buf_size < 8) ? buf_size : 8;
        // Produce keys in descending order, check for first match, write to stdout, then move buffer head.
        // If there are no codewords of length n (that is, LUT[n] is NULL), then we skip to the next length.
        for(int i = max_key_size; i > 0; i--){
            if(LUT[i] == NULL){
                continue;
            }
            uint8_t key = 0;
            for(int j = 0; j < i; j++){
                key |= bitbuf_read_head[j] << (i - j - 1);
            }
            if(LUT[i][key] != 0){
                putchar(LUT[i][key]);
                bitbuf_read_head += i;
                buf_size -= i;
                break;
            }
        }
    }
    printf("<EOF>");
    putchar('\n');
    fflush(stdout);
    return 0;
}