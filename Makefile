# ===================== Makefile =====================
CC = gcc
CFLAGS = -m32 -ffreestanding -nostdlib -fno-pie -Ikernel -Ilib -Wall -Wextra
LD = ld
ASM = nasm
OBJCOPY = objcopy

BUILD_DIR = build

KERNEL_OBJS = \
    $(BUILD_DIR)/kernel_entry.o \
    $(BUILD_DIR)/kernel.o \
    $(BUILD_DIR)/cli.o \
    $(BUILD_DIR)/stdio.o \
    $(BUILD_DIR)/string.o

.PHONY: all clean run

# === Build everything ===
all: $(BUILD_DIR)/os-image.img

# === Ensure build directory exists ===
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# === Step 1: Assemble bootloader (ensure build dir exists first) ===
$(BUILD_DIR)/bootloader.bin: bootloader.asm | $(BUILD_DIR)
	$(ASM) $< -f bin -o $@

# === Step 2: Kernel Assembly and C files ===
$(BUILD_DIR)/kernel_entry.o: kernel/kernel_entry.asm | $(BUILD_DIR)
	$(ASM) $< -f elf -o $@

$(BUILD_DIR)/kernel.o: kernel/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/cli.o: kernel/cli.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/stdio.o: lib/stdio.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/string.o: lib/string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# === Step 3: Link kernel ELF and convert to raw binary ===
$(BUILD_DIR)/kernel.elf: $(KERNEL_OBJS) | $(BUILD_DIR)
	$(LD) -m elf_i386 -T linker.ld -o $@ $^

$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel.elf
	$(OBJCOPY) -O binary $< $@

# === Step 4: Build full floppy image ===
$(BUILD_DIR)/os-image.img: $(BUILD_DIR)/bootloader.bin $(BUILD_DIR)/kernel.bin | $(BUILD_DIR)
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(BUILD_DIR)/bootloader.bin of=$@ conv=notrunc
	dd if=$(BUILD_DIR)/kernel.bin of=$@ bs=512 seek=1 conv=notrunc

# === Step 5: Run in QEMU ===
run: all
	qemu-system-i386 -fda $(BUILD_DIR)/os-image.img

# === Clean build directory ===
clean:
	rm -rf $(BUILD_DIR)
