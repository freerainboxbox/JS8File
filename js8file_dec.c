#include "js8file_dec.h"

void emit_bytes(bool * bitbuf, size_t * buf_size, bool ** bitbuf_write_head_ptr){
    // Putchar for every byte in bitbuf
    bool * bitbuf_read_head = bitbuf;
    while(*buf_size >= 8){
        uint8_t byte = 0;
        for(int i = 0; i < 8; i++){
            byte |= bitbuf_read_head[i] << (7 - i);
        }
        putchar(byte);
        bitbuf_read_head += 8;
        *buf_size -= 8;
    }
    // Justify remaining buffer back to the beginning
    if(*buf_size > 0){
        memmove(bitbuf, bitbuf_read_head, *buf_size);
    }
    // Set write head to next available bit
    *bitbuf_write_head_ptr = bitbuf + *buf_size;
}

int main(){
    bool bitbuf[BUF_SIZE*8];
    bool * bitbuf_write_head = bitbuf;
    size_t buf_size = 0; // In bits
    // Load 5 bytes from stdin (fail if less than 5 bytes)
    char header[6];
    if(fread(header, 1, 5, stdin) < 5){
        return 1;
    }
    header[5] = '\0';
    // Check that header is "FILE:"
    if(strcmp(header, "FILE:")){
        return 1;
    }
    /* Read symbols from stdin, decode into bits and append to bitbuf.
    Once bitbuf is near capacity (< 8 bits left), emit bytes.
    This check should be at the beginning of each iteration. */
    while(true){
        if(__builtin_expect(sizeof(bitbuf) - buf_size < 8, false)){
            emit_bytes(bitbuf, &buf_size, &bitbuf_write_head);
        }
        // Load 1 unsigned char from stdin, break if EOF
        int candidate = getchar();
        if(__builtin_expect(candidate == EOF, false)){
            emit_bytes(bitbuf, &buf_size, &bitbuf_write_head);
            fflush(stdout);
            break;
        }
        codeword * cw = &ILUT[candidate];
        // Append codeword to bitbuf
        for(int i = 0; i < cw->bits; i++){
            *bitbuf_write_head = (cw->key >> (cw->bits - i - 1)) & 1;
            bitbuf_write_head++;
            buf_size++;
        }
    }
    return 0;
}