.PHONY: __phony clean distclean

JAZ := $(shell find ../src -name '*.jazz')
DIR := $(dir $(JAZ))
ASM  = $(subst .jazz,.s, $(JAZ))
EXC := $(subst ../src/,bin/, $(subst .s,, $(ASM)))
OUT := $(addsuffix .out, $(EXC))

#-------------------------------------------------------------------------------

default: $(OUT)
exec: $(EXC)
asm: $(ASM) 
out: $(OUT)

$(ASM):
../src/%.s: __phony
	$(MAKE) -C $(@D)

$(EXC):
bin/gen_matrix/%: ../src/gen_matrix/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -o $@ gen_matrix.c $< -lgsl -lm

bin/keccak/keccakf1600/%: ../src/keccak/keccakf1600/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -o $@ keccakf1600.c $< -lgsl -lm

bin/keccak/keccakf1600_4x/%: ../src/keccak/keccakf1600_4x/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -o $@ keccakf1600_4x.c $< -lgsl -lm

$(OUT): | bin/
bin/%.out: bin/%
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
	@echo "OUT:"
	@echo $(OUT)
	@echo ""

