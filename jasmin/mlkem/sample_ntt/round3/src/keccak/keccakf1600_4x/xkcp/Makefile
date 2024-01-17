.PHONY: __phony clean

XED ?= xed

SRC := keccakf1600_4x_xkcp.c keccakf1600_4x_xkcp_bench.c
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
keccakf1600_4x_xkcp.s: __phony
	gcc -O3 -mavx2 keccakf1600_4x_xkcp.c -S -o $@

keccakf1600_4x_xkcp_bench.s: __phony
	gcc -O3 -mavx2 keccakf1600_4x_xkcp_bench.c -S -o $@

$(OBJ):
keccakf1600_4x_xkc%.o: keccakf1600_4x_xkc%.s
	as $< -o $@

$(STK):
keccakf1600_4x_xkc%.stack: __phony
	echo "" > $@ 2>&1

$(EXT):
keccakf1600_4x_xkc%.ext: keccakf1600_4x_xkc%.o
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

