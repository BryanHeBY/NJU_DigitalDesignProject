RISCV_HEXGEN ?= 'BEGIN{output=0;}{ gsub("\r","",$$(NF)); if ($$1 ~/@/) \
    {if ($$1 ~/@00000000/) {output=code;} else {output=1- code;}; \
    gsub("@","0x",$$1); addr=strtonum($$1); if (output==1) \
    {printf "@%08x\n",(addr%262144)/4;}} \
    else {if (output==1) { for(i=1;i<NF;i+=4) \
    print $$(i+3)$$(i+2)$$(i+1)$$i;}}}'
RISCV_MIFGEN ?= 'BEGIN{printf "WIDTH=32;\nDEPTH=%d;\n\nADDRESS_RADIX=HEX; \
    \nDATA_RADIX=HEX;\n\nCONTENT BEGIN\n",depth ; addr=0;} { \
    gsub("\r","",$$(NF)); if ($$1 ~/@/) { sub("@","0x",$$1); \
    addr=strtonum($$1);} else {printf "%04X : %s;\n", addr, $$1; \
    addr=addr+1;}} END{print "END\n";}'

${EXEC}.tmp: ${EXEC}.elf
	@$(RISCV_OBJCOPY) $< $@

${EXEC}.hex: ${EXEC}.tmp
	@echo dump "->" $@
	@awk -v code=1 $(RISCV_HEXGEN) $< > $@
	@awk -v code=0 $(RISCV_HEXGEN) $< > ${EXEC}_d.hex

${EXEC}.mif: ${EXEC}.hex
	@echo dump "->" $@
	@awk -v depth=32768 ${RISCV_MIFGEN} $< > $@
	@awk -v depth=40960 ${RISCV_MIFGEN} ${EXEC}_d.hex > ${EXEC}_d.mif

.PHONY: dump update

CPU_FPGA_PATH = /home/hby/Seafile/mycpu

dump: ${EXEC}.mif

update: dump
	@echo "UPDATE" $(shell realpath $(EXEC).mif --relative-to .) $(shell realpath $(EXEC)_d.mif --relative-to .)
	@cp $(EXEC).mif $(CPU_FPGA_PATH)/imem.mif
	@cp $(EXEC)_d.mif $(CPU_FPGA_PATH)/dmem.mif
