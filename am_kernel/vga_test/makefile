NAME     := vga_test
SRCS      = $(shell find . -name "*.c" -or -name "*.S")
ifneq ($(ARCH),native)
RISCV_CC_OPTS = -DFPGA_GRAGHIC_ON
endif

include $(MYCPU_AM_HOME)/makefile