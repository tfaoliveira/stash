.PHONY: gen_matrix.s gen_matrix.stack clean

JASMIN ?= jasminc

gen_matrix.s:
	gcc -mavx2 -mbmi2 -mpopcnt -mbmi2 -O3 -I../../keccak/keccakf1600_4x/xkcp/ gen_matrix.c -S -o $@

gen_matrix.stack:
	echo "" > $@ 2>&1

clean:
	rm -f gen_matrix.s gen_matrix.stack

