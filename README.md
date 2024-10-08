# JS8File

These are small C helpers that allow you to encode and decode arbitrary binary files and transmit them over JS8call.

## How does it work?

JS8call's implementation uses a Huffman code to transmit characters efficiently. To encode a binary file, we create a buffer of booleans and keep on grabbing the symbol with the longest matching codeword that matches our current read position.

## What if we don't find a match at a particular sequence?

The code table has two most common symbols: ' ' and 'E'. Each consumes only 2 and 3 bits, respectively. Therefore, when no other codeword is found, we can encode a single bit with one of these. This makes our encoding scheme complete and optimal.

## Why not just base64?

As far as I can tell from the source code, only the symbols I have selected have dedicated short codewords. Anything from an extended character set is less efficient.

JS8call does not send lowercase. Even if we were to use a BaseN scheme fitting into the dedicated short codeword alphabet that just listed characters in lexicographic order, it would not be as efficient.

UPDATE: Looking more carefully, it seems to be some subset of Varicode (which is used by PSK31). It should be possible to extend my usable symbols even further, and this will be done in a future iteration.

## How do I use it?

You need a C compiler and `make`. If you're on Windows, either use Cygwin or just run it on a WSL distro. If you try to compile this program for Windows natively, you will need to increase the stack size manually (the default is 1 MiB, where for Linux it's 8 MiB). Standard streams expect text, not binary in this mode, so you may encounter undefined behavior. Use natively on Windows at your own risk.

Clone the repo and just run `make` inside the repo directory. This will produce `js8file-enc` and `js8file-dec`.

Both of these programs operate through standard input and output. You cannot specify a filename as an argument, instead, use I/O redirection (in line with [Unix philosophy](http://www.catb.org/~esr/writings/taoup/html/ch01s06.html)).

`js8file-enc`: Given a filename `file.dat`, run `./js8file-enc < file.dat`, and it will output to your terminal screen. You can then copy this to the transmit window in JS8call (be sure to include the `FILE:` prefix!)

_NOTE_: `js8file-enc` emits an `<EOF>` tag that should not be copied. This exists because the encoding might have spaces at the end of it. This should help you see the message end boundary.

`./js8file-dec`: Given an encoded string, `<string>` (it should start with `FILE:`), run `echo -n "<string>" | js8file-dec > decoded.dat`.

You can also install the programs locally with `make install` after running `make`. You can then uninstall them using `make uninstall`.

## Why did you make this?

1. As a coding exercise. I wanted an excuse to do some encoding stuff in C, to keep my skills fresh.

2. Because it's something JS8call can't do, and that just won't do!

3. It might find some use for hams who aren't using English. Any UTF-8 encoded file can be fed into this program and sent over the air, meaning all languages are supported.

Also, this is not 100% uber stress tested. There may be a couple of stray, hard-to-spot bugs.

_de KD2STC_
