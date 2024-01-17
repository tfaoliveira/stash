.PHONY: __phony clean

XED ?= xed

SRC := \
  gen_matrix_bmi1_table.c   gen_matrix_nobmi1_table.c   gen_matrix_bmi1_table_bench.c   gen_matrix_nobmi1_table_bench.c \
  gen_matrix_bmi1_notable.c gen_matrix_nobmi1_notable.c gen_matrix_bmi1_notable_bench.c gen_matrix_nobmi1_notable_bench.c

ASM  = $(subst .c,.s, $(SRC))
OBJ  = $(subst .c,.o, $(SRC))
STK  = $(subst .c,.stack, $(SRC))
EXT  = $(subst .c,.ext, $(SRC))

all: assembly object stack extensions

assembly: $(ASM)
object: $(OBJ)
stack: $(STK)
extensions: $(EXT)

# note: checkme: bmi2 is required to avoid compilation error wrt _pext_u32

#-------------------------------------------------------------------------------

$(ASM):
gen_matrix_bmi1_table.s: __phony
	gcc -O3 -mavx2 -mbmi2 -mbmi gen_matrix.c -I../../../keccak/keccakf1600_4x/xkcp/ -S -o $@

gen_matrix_nobmi1_table.s: __phony
	gcc -O3 -mavx2 -mbmi2 gen_matrix.c  -I../../../keccak/keccakf1600_4x/xkcp/ -S -o $@

gen_matrix_bmi1_table_bench.s: __phony
	gcc -O3 -mavx2 -mbmi2 -mbmi gen_matrix_bench.c -I../../../keccak/keccakf1600_4x/xkcp/ -S -o $@

gen_matrix_nobmi1_table_bench.s: __phony
	gcc -O3 -mavx2 -mbmi2 gen_matrix_bench.c -I../../../keccak/keccakf1600_4x/xkcp/ -S -o $@

#-------------------------------------------------------------------------------

gen_matrix_bmi1_notable.s: __phony
	gcc -O3 -mavx2 -mbmi2 -mbmi -DBMI gen_matrix.c -I../../../keccak/keccakf1600_4x/xkcp/ -S -o $@

gen_matrix_nobmi1_notable.s: __phony
	gcc -O3 -mavx2 -mbmi2 -DBMI gen_matrix.c  -I../../../keccak/keccakf1600_4x/xkcp/ -S -o $@

gen_matrix_bmi1_notable_bench.s: __phony
	gcc -O3 -mavx2 -mbmi2 -mbmi -DBMI gen_matrix_bench.c -I../../../keccak/keccakf1600_4x/xkcp/ -S -o $@

gen_matrix_nobmi1_notable_bench.s: __phony
	gcc -O3 -mavx2 -mbmi2 -DBMI gen_matrix_bench.c -I../../../keccak/keccakf1600_4x/xkcp/ -S -o $@

#-------------------------------------------------------------------------------

$(OBJ):
gen_matri%.o: gen_matri%.s
	as $< -o $@

$(STK):
gen_matri%.stack: __phony
	echo "" > $@ 2>&1

$(EXT):
gen_matri%.ext: gen_matri%.o
	$(XED) -xml -i $< | grep "<EXTENSION>" | sed -e 's/ *<EXTENSION>//' -e 's/<\/EXTENSION>//' | sort -u | tr '\n' ',' | sed -e 's/,$$/\n/' > $@

clean:
	rm -f *.s *.o *.stack *.ext

#-------------------------------------------------------------------------------

debug:
	@echo "SRC:"
	@echo $(SRC)
	@echo ""
	@echo "ASM:"
	@echo $(ASM)
	@echo ""
	@echo "OBJ:"
	@echo $(OBJ)
	@echo ""
	@echo "STK:"
	@echo $(STK)
	@echo ""
	@echo "EXT:"
	@echo $(EXT)
	@echo ""



