.PHONY: gen_matrix.stack clean

JASMIN ?= jasminc

gen_matrix.s: gen_matrix.jazz consts.jinc fips202_4x.jinc fips202_common.jinc fips202.jinc gen_matrix.jinc keccakf1600.jinc params.jinc shuffle.jinc
	$(JASMIN) -nowarning -lea -o $@ gen_matrix.jazz

gen_matrix.stack:
	$(JASMIN) -nowarning  -print-stack-alloc -lea gen_matrix.jazz > $@ 2>&1

clean:
	rm -f gen_matrix.s gen_matrix.stack
