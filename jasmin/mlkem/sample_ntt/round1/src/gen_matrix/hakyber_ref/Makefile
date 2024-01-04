.PHONY: gen_matrix.stack clean

JASMIN ?= jasminc

gen_matrix.s: gen_matrix.jazz gen_matrix.jinc fips202.jinc params.jinc
	$(JASMIN) -nowarning -lea -o $@ gen_matrix.jazz

gen_matrix.stack:
	$(JASMIN) -nowarning  -print-stack-alloc -lea gen_matrix.jazz > $@ 2>&1

clean:
	rm -f gen_matrix.s gen_matrix.stack
