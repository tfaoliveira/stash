.PHONY: __phony clean

JASMIN ?= jasminc
XED ?= xed

JAZ := $(shell find . -name '*.jazz')
ASM  = $(subst .jazz,.s, $(JAZ))
OBJ  = $(subst .jazz,.o, $(JAZ))
STK  = $(subst .jazz,.stack, $(JAZ))
EXT  = $(subst .jazz,.ext, $(JAZ))

all: assembly object stack extensions

assembly: $(ASM)
object: $(OBJ)
stack: $(STK)
extensions: $(EXT)

$(ASM):
keccakf1600%.s: __phony
	$(JASMIN) -I Keccak:../ -I Stdlib:../../stdlib/ -o $@ keccakf1600$*.jazz

$(OBJ):
keccakf1600%.o: keccakf1600%.s
	as $< -o $@

$(STK):
keccakf1600%.stack: __phony
	$(JASMIN) -print-stack-alloc -I Keccak:../ -I Stdlib:../../stdlib/ keccakf1600$*.jazz > $@ 2>&1

$(EXT):
keccakf1600%.ext: keccakf1600%.o
	$(XED) -xml -i $< | grep "<EXTENSION>" | sed -e 's/ *<EXTENSION>//' -e 's/<\/EXTENSION>//' | sort -u | tr '\n' ',' | sed -e 's/,$$/\n/' > $@

clean:
	rm -f *.s *.o *.stack *.ext

#-------------------------------------------------------------------------------

debug:
	@echo "JAZ:"
	@echo $(JAZ)
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

