ARCH              = arm64
TARGET            = aarch64-linux-gnu
CC                = clang
CFLAGS            = --target=$(TARGET)
OBJCOPY           = llvm-objcopy

all: BootShim.elf BootShim.bin

# SHIM_SRC selects the assembly source; BootShimProbe.S is the diagnostic
# variant used for headless bring-up. EXTRA_DEFS carries its probe macros.
SHIM_SRC          ?= BootShim.S
EXTRA_DEFS        ?=

BootShim.bin: BootShim.elf
	$(OBJCOPY) -O binary $< $@

BootShim.elf: $(SHIM_SRC)
	$(CC) ${CFLAGS} -c $(SHIM_SRC) -o $@ -DREQUIRES_KERNEL_HEADER=$(REQUIRES_KERNEL_HEADER) -DFD_BASE=$(FD_BASE) -DFD_SIZE=$(FD_SIZE) $(EXTRA_DEFS)
