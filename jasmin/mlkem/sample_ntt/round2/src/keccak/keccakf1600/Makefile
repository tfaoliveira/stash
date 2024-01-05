.PHONY: __phony clean distclean

JASMIN ?= jasminc

JAZ := $(shell find . -name '*.jazz')
ASM := $(subst .jazz,.s, $(JAZ))

default: asm
asm: $(ASM)

$(ASM):
%.s: %.jazz __phony
	$(JASMIN) -I Keccak:../ -o $@ $<

%.stack: %.jazz __phony
	$(JASMIN) -print-stack-alloc -I Keccak:../ $< > $@ 2>&1

clean:
	rm -f $(ASM) *.stack

#-------------------------------------------------------------------------------

debug:
	@echo "JAZ:"
	@echo $(JAZ)
	@echo ""
	@echo "ASM:"
	@echo $(ASM)
	@echo ""

