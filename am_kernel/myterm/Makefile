NAME = myterm
SRCS = $(shell find . -name "*.c" -or -name "*.S")
ifneq ($(ARCH),native)
RISCV_CC_OPTS = -D__ARCH_FPGA -DFPGA_GRAGHIC_ON
endif

include $(MYCPU_AM_HOME)/makefile
