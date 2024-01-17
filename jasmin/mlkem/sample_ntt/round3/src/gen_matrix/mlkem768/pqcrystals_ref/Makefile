.PHONY: __phony clean

XED ?= xed

SRC := gen_matrix_bmi1.c gen_matrix_nobmi1.c gen_matrix_bmi1_bench.c gen_matrix_nobmi1_bench.c
ASM  = $(subst .c,.s, $(SRC))
OBJ  = $(subst .c,.o, $(SRC))
STK  = $(subst .c,.stack, $(SRC))
EXT  = $(subst .c,.ext, $(SRC))

all: assembly object stack extensions

assembly: $(ASM)
object: $(OBJ)
stack: $(STK)
extensions: $(EXT)

$(ASM):
gen_matrix_bmi1.s: __phony
	gcc -O3 -mbmi gen_matrix.c -S -o $@

gen_matrix_nobmi1.s: __phony
	gcc -O3 gen_matrix.c -S -o $@

gen_matrix_bmi1_bench.s: __phony
	gcc -O3 -mbmi gen_matrix_bench.c -S -o $@

gen_matrix_nobmi1_bench.s: __phony
	gcc -O3 gen_matrix_bench.c -S -o $@

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



