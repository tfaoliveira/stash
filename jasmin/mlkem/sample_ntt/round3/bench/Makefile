.PHONY: __phony clean distclean

#-- non jasmin implementations
NJI := \
 ../src/gen_matrix/mlkem512/pqcrystals_ref/gen_matrix_bmi1_bench.s \
 ../src/gen_matrix/mlkem512/pqcrystals_ref/gen_matrix_nobmi1_bench.s \
 ../src/gen_matrix/mlkem512/pqcrystals_avx2/gen_matrix_bmi1_table_bench.s \
 ../src/gen_matrix/mlkem512/pqcrystals_avx2/gen_matrix_nobmi1_table_bench.s \
 ../src/gen_matrix/mlkem512/pqcrystals_avx2/gen_matrix_bmi1_notable_bench.s \
 ../src/gen_matrix/mlkem512/pqcrystals_avx2/gen_matrix_nobmi1_notable_bench.s \
\
 ../src/gen_matrix/mlkem768/pqcrystals_ref/gen_matrix_bmi1_bench.s \
 ../src/gen_matrix/mlkem768/pqcrystals_ref/gen_matrix_nobmi1_bench.s \
 ../src/gen_matrix/mlkem768/pqcrystals_avx2/gen_matrix_bmi1_table_bench.s \
 ../src/gen_matrix/mlkem768/pqcrystals_avx2/gen_matrix_nobmi1_table_bench.s \
 ../src/gen_matrix/mlkem768/pqcrystals_avx2/gen_matrix_bmi1_notable_bench.s \
 ../src/gen_matrix/mlkem768/pqcrystals_avx2/gen_matrix_nobmi1_notable_bench.s \
\
 ../src/gen_matrix/mlkem1024/pqcrystals_ref/gen_matrix_bmi1_bench.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_ref/gen_matrix_nobmi1_bench.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_avx2/gen_matrix_bmi1_table_bench.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_avx2/gen_matrix_nobmi1_table_bench.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_avx2/gen_matrix_bmi1_notable_bench.s \
 ../src/gen_matrix/mlkem1024/pqcrystals_avx2/gen_matrix_nobmi1_notable_bench.s \
\
 ../src/keccak/keccakf1600_4x/xkcp/keccakf1600_4x_xkcp_bench.s

JAZ := $(shell find ../src -name '*_bench.jazz')
DIR := $(dir $(JAZ))
ASM  = $(subst .jazz,.s, $(JAZ)) $(NJI)
EXC := $(subst ../src/,bin/, $(subst .s,, $(ASM)))
CSV := $(addsuffix .csv, $(EXC))

#-------------------------------------------------------------------------------

default: $(CSV)
exec: $(EXC)
asm: $(ASM) 
CSV: $(CSV)

$(ASM):
../src/%.s: __phony
	$(MAKE) -C $(@D) $(@F)

#-

$(EXC):
bin/gen_matrix/mlkem512/%: ../src/gen_matrix/mlkem512/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -DGEN_MATRIX_SIZE=1024 -I../test/common/ -o $@ gen_matrix.c $< -lgsl -lm

bin/gen_matrix/mlkem768/%: ../src/gen_matrix/mlkem768/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -DGEN_MATRIX_SIZE=2304 -I../test/common/ -o $@ gen_matrix.c $< -lgsl -lm

bin/gen_matrix/mlkem1024/%: ../src/gen_matrix/mlkem1024/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -DGEN_MATRIX_SIZE=4096 -I../test/common/ -o $@ gen_matrix.c $< -lgsl -lm

#-

bin/keccak/keccakf1600/%: ../src/keccak/keccakf1600/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -I../test/common/ -o $@ keccakf1600.c $< -lgsl -lm

bin/keccak/keccakf1600_4x/%: ../src/keccak/keccakf1600_4x/%.s | __phony
	mkdir -p $(@D)
	gcc -Wall -Wno-unused-function -Werror -O3 -I../test/common/ -o $@ keccakf1600_4x.c $< -lgsl -lm

#-

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

