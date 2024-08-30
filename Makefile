
CFLAGS := -O3 -mtune=native -march=native

all: js8file-enc js8file-dec

js8file-enc: js8file_enc.c
	gcc $(CFLAGS) -o $@ $<

js8file-dec: js8file_dec.c
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -f js8file-enc js8file-dec
