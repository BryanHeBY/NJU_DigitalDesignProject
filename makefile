CPU_SRCS  = $(shell find $(CPU_HOME)/hardware_src/cpu -name "*.vt" -or -name "*.v")
CPU = $(CPU_HOME)/hardware_src/cpu.vh
CPU_CT = $(CPU_HOME)/hardware_src/cpu.vout
CFLAGS += -Wimplicit -Wportbind -Wselect-range -Winfloop

TEST_SRCS ?= 
TEST_MODULE ?=
TESTBENCH = $(TEST_MODULE)_test

$(CPU): $(CPU_SRCS)
	iverilog -o $@ -E $(CPU_SRCS)

$(CPU_CT): $(CPU_SRCS)
	iverilog -o $@ $(CFLAGS) $(CPU_SRCS)

$(TESTBENCH): $(TEST_SRCS) $(CPU)
	iverilog -s $(TEST_MODULE) -o $@ $(CFLAGS) $(TEST_SRCS) $(CPU)

.PHONY: cpu test test_wave clean update

cpu: $(CPU_CT) $(CPU)

update: cpu
	@cp $(CPU) ~/Seafile/mycpu/rv32is.v


test: $(TESTBENCH)
	vvp -n $(TESTBENCH) -lxt2

test.vcd: $(TESTBENCH)
	vvp -n $(TESTBENCH) -lxt2

test_wave: test.vcd
	gtkwave $<

clean:
	rm -f $(TESTBENCH) test.vcd
