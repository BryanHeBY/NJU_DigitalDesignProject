NAME = typing-game
SRCS = game.c font.c
ifneq ($(ARCH),native)
RISCV_CC_OPTS = -DFPGA_GRAGHIC_ON
endif

include $(MYCPU_AM_HOME)/makefile
