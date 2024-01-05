.PHONY: __phony clean distclean

JAZ := $(shell find ../src -name '*.jazz')
DIR := $(dir $(JAZ))
ASM  = $(subst .jazz,.s, $(JAZ)) ../src/gen_matrix/pqcrystals_ref/gen_matrix.s
EXC := $(subst ../src/,bin/, $(subst .s,, $(ASM)))
CSV := $(addsuffix .csv, $(EXC))

#-------------------------------------------------------------------------------

default: $(CSV)
exec: $(EXC)
asm: $(ASM) 
csv: $(CSV)

$(ASM):
../src/%.s: __phony
	$(MAKE) -C $(@D)

$(EXC):
bin/gen_matrix/%: ../src/gen_matrix/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -I../test/common/ -o $@ gen_matrix.c $< -lgsl -lm

bin/keccak/keccakf1600/%: ../src/keccak/keccakf1600/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -I../test/common/ -o $@ keccakf1600.c $< -lgsl -lm

bin/keccak/keccakf1600_4x/%: ../src/keccak/keccakf1600_4x/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -I../test/common/ -o $@ keccakf1600_4x.c $< -lgsl -lm

$(CSV): | bin/
bin/%.csv: bin/%
	./$< > $@

clean:
	rm -fr bin/

distclean: clean
	for i in $(DIR); do $(MAKE) -C $$i clean; done

#-------------------------------------------------------------------------------

debug:
	@echo "JAZ:"
	@echo $(JAZ)
	@echo ""
	@echo "ASM:"
	@echo $(ASM)
	@echo ""
	@echo "EXC:"
	@echo $(EXC)
	@echo ""
	@echo "CSV:"
	@echo $(CSV)
	@echo ""
