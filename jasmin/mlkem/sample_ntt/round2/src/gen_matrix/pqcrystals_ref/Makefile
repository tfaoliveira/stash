.PHONY: gen_matrix.s gen_matrix.stack clean

JASMIN ?= jasminc

gen_matrix.s:
	gcc -O3 gen_matrix.c -S -o $@

gen_matrix.stack:
	echo "" > $@ 2>&1

clean:
	rm -f gen_matrix.s gen_matrix.stack

