
CFLAGS := -O3 -mtune=native -march=native

all: clean js8file-enc js8file-dec

install: js8file-enc js8file-dec
	sudo cp js8file-enc /usr/local/bin
	sudo cp js8file-dec /usr/local/bin

uninstall:
	sudo rm -f /usr/local/bin/js8file-enc
	sudo rm -f /usr/local/bin/js8file-dec

js8file-enc: js8file_enc.c
	gcc $(CFLAGS) -o $@ $<

js8file-dec: js8file_dec.c
	gcc $(CFLAGS) -o $@ $<

clean-enc:
	rm -f js8file-enc

clean-dec:
	rm -f js8file-dec

clean: clean-enc clean-dec