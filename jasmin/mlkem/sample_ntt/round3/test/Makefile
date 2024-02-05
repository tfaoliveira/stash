.PHONY: __phony clean distclean

UNAME = $(shell uname)

#-- non jasmin implementations
NJI := \
 ../src/gen_matrix/mlkem512/pqcrystals_ref/gen_matrix_bmi1.s \
 ../src/gen_matrix/mlkem512/pqcrystals_ref/gen_matrix_nobmi1.s \
 ../src/gen_matrix/mlkem512/pqcrystals_avx2/gen_matrix_bmi1_table.s \
 ../src/gen_matrix/mlkem512/pqcrystals_avx2/gen_matrix_nobmi1_table.s \
 ../src/gen_matrix/mlkem512/pqcrystals_avx2/gen_matrix_bmi1_notable.s \
 ../src/gen_matrix/mlkem512/pqcrystals_avx2/gen_matrix_nobmi1_notable.s \
\
 ../src/gen_matrix/mlkem768/pqcrystals_ref/gen_matrix_bmi1.s \
 ../src/gen_matrix/mlkem768/pqcrystals_ref/gen_matrix_nobmi1.s \
 ../src/gen_matrix/mlkem768/pqcrystals_avx2/gen_matrix_bmi1_table.s \
 ../src/gen_matrix/mlkem768/pqcrystals_avx2/gen_matrix_nobmi1_table.s \
 ../src/gen_matrix/mlkem768/pqcrystals_avx2/gen_matrix_bmi1_notable.s \
 ../src/gen_matrix/mlkem768/pqcrystals_avx2/gen_matrix_nobmi1_notable.s \
\
 ../src/gen_matrix/mlkem1024/pqcrystals_ref/gen_matrix_bmi1.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_ref/gen_matrix_nobmi1.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_avx2/gen_matrix_bmi1_table.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_avx2/gen_matrix_nobmi1_table.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_avx2/gen_matrix_bmi1_notable.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_avx2/gen_matrix_nobmi1_notable.s \
\
 ../src/keccak/keccakf1600_4x/xkcp/keccakf1600_4x_xkcp.s

JAZ := $(shell find ../src -name '*.jazz')
DIR := $(dir $(JAZ))
ASM  = $(subst .jazz,.s, $(JAZ)) $(NJI)
EXC := $(subst ../src/,bin/, $(subst .s,, $(ASM)))
OUT := $(addsuffix .out, $(EXC))

ifneq ($(UNAME),Linux)
LDFLAGS ?= -framework Accelerate
endif

#-------------------------------------------------------------------------------

default: $(OUT)
exec: $(EXC)
asm: $(ASM) 
out: $(OUT)

$(ASM):
../src/%.s: __phony
	$(MAKE) -C $(@D) $(@F)

#-

$(EXC):
bin/gen_matrix/mlkem512/%: ../src/gen_matrix/mlkem512/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror $(LDFLAGS) -O3 -g -DGEN_MATRIX_SIZE=1024 -o $@ gen_matrix.c $< -lgsl -lm

bin/gen_matrix/mlkem768/%: ../src/gen_matrix/mlkem768/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror $(LDFLAGS) -O3 -g -DGEN_MATRIX_SIZE=2304 -o $@ gen_matrix.c $< -lgsl -lm

bin/gen_matrix/mlkem1024/%: ../src/gen_matrix/mlkem1024/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror $(LDFLAGS) -O3 -g -DGEN_MATRIX_SIZE=4096 -o $@ gen_matrix.c $< -lgsl -lm

#-

bin/keccak/keccakf1600/%: ../src/keccak/keccakf1600/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror $(LDFLAGS) -O3 -g -o $@ keccakf1600.c $< -lgsl -lm

bin/keccak/keccakf1600_avx2/%: ../src/keccak/keccakf1600_avx2/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror $(LDFLAGS) -O3 -g -o $@ keccakf1600.c $< -lgsl -lm

bin/keccak/keccakf1600_4x/%: ../src/keccak/keccakf1600_4x/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror $(LDFLAGS) -O3 -g -o $@ keccakf1600_4x.c $< -lgsl -lm

#-

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
	@echo "UNAME:"
	@echo $(UNAME)
	@echo ""
	@echo "LDFLAGS:"
	@echo $(LDFLAGS)

