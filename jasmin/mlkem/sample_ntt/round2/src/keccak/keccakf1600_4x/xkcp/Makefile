.PHONY: __phony clean distclean

default: keccakf1600_4x_xkcp.s

keccakf1600_4x_xkcp.s: __phony
	gcc -mavx2 -O3 keccakf1600_4x_xkcp.c -S -o $@

%.stack: %.jazz __phony
	echo "" > $@ 2>&1

clean:
	rm -f keccakf1600_4x_xkcp.s *.stack


