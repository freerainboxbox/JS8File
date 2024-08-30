#include "ref.h"

const codeword ILUT[0xff] = {
    [' '] = {.key=0b0, .bits=1},
    ['E'] = {.key=0b1, .bits=1},
    ['T'] = {.key=0b1101, .bits=4},
    ['A'] = {.key=0b0011, .bits=4},
    ['O'] = {.key=0b11111, .bits=5},
    ['I'] = {.key=0b11100, .bits=5},
    ['N'] = {.key=0b10111, .bits=5},
    ['S'] = {.key=0b10100, .bits=5},
    ['H'] = {.key=0b00011, .bits=5},
    ['R'] = {.key=0b00000, .bits=5},
    ['D'] = {.key=0b111011, .bits=6},
    ['L'] = {.key=0b110011, .bits=6},
    ['C'] = {.key=0b110001, .bits=6},
    ['U'] = {.key=0b101101, .bits=6},
    ['M'] = {.key=0b101011, .bits=6},
    ['W'] = {.key=0b001011, .bits=6},
    ['F'] = {.key=0b001001, .bits=6},
    ['G'] = {.key=0b000101, .bits=6},
    ['Y'] = {.key=0b000011, .bits=6},
    ['P'] = {.key=0b1111011, .bits=7},
    ['B'] = {.key=0b1111001, .bits=7},
    ['.'] = {.key=0b1110100, .bits=7},
    ['V'] = {.key=0b1100101, .bits=7},
    ['K'] = {.key=0b1100100, .bits=7},
    ['-'] = {.key=0b1100001, .bits=7},
    ['+'] = {.key=0b1100000, .bits=7},
    ['?'] = {.key=0b1011001, .bits=7},
    ['!'] = {.key=0b1011000, .bits=7},
    ['"'] = {.key=0b1010101, .bits=7},
    ['X'] = {.key=0b1010100, .bits=7},
    ['0'] = {.key=0b0010101, .bits=7},
    ['J'] = {.key=0b0010100, .bits=7},
    ['1'] = {.key=0b0010001, .bits=7},
    ['Q'] = {.key=0b0010000, .bits=7},
    ['2'] = {.key=0b0001001, .bits=7},
    ['Z'] = {.key=0b0001000, .bits=7},
    ['3'] = {.key=0b0000101, .bits=7},
    ['5'] = {.key=0b0000100, .bits=7},
    ['4'] = {.key=0b11110101, .bits=8},
    ['9'] = {.key=0b11110100, .bits=8},
    ['8'] = {.key=0b11110001, .bits=8},
    ['6'] = {.key=0b11110000, .bits=8},
    ['7'] = {.key=0b11101011, .bits=8},
    ['/'] = {.key=0b11101010, .bits=8}
};
