# JS8File

These are small C helpers that allow you to encode and decode arbitrary binary files and transmit them over JS8call.

## How does it work?

JS8call's implementation uses a Huffman code to transmit characters efficiently. To encode a binary file, we create a buffer of booleans and keep on grabbing the symbol with the longest matching codeword that matches our current read position.

## What if we don't find a match at a particular sequence?

The code table has two most common symbols: ' ' and 'E'. Each consumes only 2 and 3 bits, respectively. Therefore, when no other codeword is found, we can encode a single bit with one of these. This makes our encoding scheme complete and optimal.

## Why not just base64?

First of all, base64 comprises a larger symbol set than supported by JS8.

Second, even if we were to use a smaller baseN encoding that happened to fit the limited set of symbols, it would not be optimized to the codebook, and will always be longer than this implementation.

## How do I use it?

You need a C compiler and `make`. If you're on Windows, either use MinGW or just run it on a WSL distro.

Clone the repo and just run `make` inside the repo directory. This will produce `js8file-enc` and `js8file-dec`.

Both of these programs operate through standard input and output. You cannot specify a filename as an argument, instead, use I/O redirection (in line with [Unix philosophy](http://www.catb.org/~esr/writings/taoup/html/ch01s06.html)).

`js8file-enc`: Given a filename `file.dat`, run `./js8file-enc < file.dat`, and it will output to your terminal screen. You can then copy this to the transmit window in JS8call (be sure to include the `FILE:` prefix!)

_NOTE_: `js8file-enc` emits an `<EOF>` tag that should not be copied. This exists because the encoding might have spaces at the end of it. This should help you see the message end boundary.

`./js8file-dec`: Given an encoded string, `<string>` (it should start with `FILE:`), run `echo -n "<string>" | js8file-dec > decoded.dat`.

## Why did you make this?

1. As a coding exercise. I wanted an excuse to do some encoding stuff in C, to keep my skills fresh.

2. Because it's something JS8call can't do, and that just won't do!

3. It might find some use for hams who aren't using English. Any UTF-8 encoded file can be fed into this program and sent over the air, meaning all languages are supported.

_de KD2STC_