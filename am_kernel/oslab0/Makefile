GAMES = $(shell ls)

ifeq ($(filter $(GAME), $(GAMES)), )
  $(error Expected $$GAME in {$(GAMES)}, Got "$(GAME)")
endif

NAME     := game_$(GAME)
SRCS      = $(shell find $(GAME) -name "*.c" -or -name "*.S" -or -name "*.cc" -or -name "*.cpp")
INC_PATH  = ../include

ifneq ($(ARCH),native)
RISCV_CC_OPTS = -DFPGA_GRAGHIC_ON
endif

include $(MYCPU_AM_HOME)/makefile
