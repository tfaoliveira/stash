.PHONY: gen_matrix.s gen_matrix.stack clean

JASMIN ?= jasminc

gen_matrix.s:
	$(JASMIN) -I Keccak:../../keccak/ -I Stdlib:../../stdlib/ -o $@ gen_matrix.jazz

gen_matrix.stack:
	$(JASMIN) -print-stack-alloc  -I Keccak:../../keccak/ -I Stdlib:../../stdlib/ gen_matrix.jazz > $@ 2>&1

clean:
	rm -f gen_matrix.s gen_matrix.stack

