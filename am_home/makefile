ifneq ($(ARCH),fpga)

-include $(AM_HOME)/Makefile

else

WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
OBJS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))
#OBJS := $(SRCS:%c=$(BUILD_DIR)/%o)
EXEC := $(BUILD_DIR)/$(NAME)
ARCHIVE   = $(BUILD_DIR)/$(NAME).a

LIBS     := $(sort $(LIBS) am klib) # lazy evaluation ("=") causes infinite recursions
LINKAGE   = $(OBJS)\
    $(addsuffix .a, $(join \
    $(addsuffix /build/, $(addprefix $(MYCPU_AM_HOME)/, $(LIBS))), \
    $(LIBS) )) 

INC_PATH += $(WORK_DIR)/include $(addsuffix /include/, $(addprefix $(MYCPU_AM_HOME)/, $(LIBS)))
INCFLAGS += $(addprefix -I, $(INC_PATH))

default: image

RISCV_PREFIX ?= riscv64-linux-gnu-
RISCV_AS      = $(RISCV_PREFIX)gcc
RISCV_CC      = $(RISCV_PREFIX)gcc
RISCV_CXX     = $(RISCV_PREFIX)g++
RISCV_LD      = $(RISCV_PREFIX)ld
RISCV_OBJDUMP = $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data
RISCV_OBJCOPY = $(RISCV_PREFIX)objcopy -O verilog
LINKER        = $(MYCPU_AM_HOME)/scripts/linker.ld



GCC_WARNS := -Wall -Wno-unused-function -Wcast-align
RISCV_CC_OPTS += -fno-pic -march=rv32i -mabi=ilp32 -static -O2\
					-mcmodel=medany -fvisibility=hidden \
					$(INCFLAGS) \
					-T$(LINKER) \
					-nostdlib -nolibc -nostartfiles -Wl,--build-id=none ${GCC_WARNS}
RISCV_CXX_OPTS += $(RISCV_CC_OPTS) -ffreestanding -fno-rtti -fno-exceptions
RISCV_LD_OPTS +=  -melf32lriscv -T$(LINKER) \
					--gc-sections -e _start


$(BUILD_DIR)/%.o: %.S
	@echo AS "->" $<
	@mkdir -p $(dir $@)
	@$(RISCV_AS) -c $(RISCV_CC_OPTS) $< -o $@

$(BUILD_DIR)/%.o: %.c
	@echo CC "->" $<
	@mkdir -p $(dir $@)
	@$(RISCV_CC) -c $(RISCV_CC_OPTS) $< -o $@

$(BUILD_DIR)/%.o: %.cc
	@echo CXX "->" $<
	@mkdir -p $(dir $@)
	@$(RISCV_CXX) -c $(RISCV_CXX_OPTS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@echo CXX "->" $<
	@mkdir -p $(dir $@)
	@$(RISCV_CXX) -c $(RISCV_CXX_OPTS) $< -o $@

$(LIBS): %:
	@$(MAKE) -s -C $(MYCPU_AM_HOME)/$* archive

$(EXEC).elf: $(OBJS) $(LIBS)
	@echo LD "->" $@
	@${RISCV_LD} ${RISCV_LD_OPTS} --start-group $(LINKAGE) --end-group -o $@
	@${RISCV_OBJDUMP} ${EXEC}.elf > ${EXEC}.dump

$(ARCHIVE): $(OBJS)
	@echo AR "->" $(shell realpath $@ --relative-to .)
	@ar rcs $(ARCHIVE) $(OBJS)

.PHONY: image archive clean

image: $(EXEC).elf

-include $(MYCPU_AM_HOME)/scripts/dump.mk

archive: $(ARCHIVE)

clean:
	rm -rf build
endif