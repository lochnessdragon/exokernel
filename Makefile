# custom colors for funz!
COLOR_COMPILE='\033[1;32m'
COLOR_LINK='\033[1;95m'
COLOR_FILE='\033[4;94m'
COLOR_CLR='\033[0m'

# sets the folders to use to place object files and the final output
BINDIR=build/
INTDIR=build-int/

AS=nasm
ASFLAGS=-f elf32

LD=ld
LFLAGS=-s

CC=gcc 
CFLAGS=-m32 -Iruntime/include/ -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -fno-pie -Wall -Wextra -Werror -mno-red-zone

OBJDIR=build-int/
BINDIR=build/

dir_guard=@mkdir -p $(@D)
# recursive wildcard
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)$(filter $(subst *,%,$2), $d))

# default target (all)
.PHONY:
all: $(BINDIR)os.iso

# split up project into subdirectories
dir := runtime/
include runtime/runtime.mk 
dir := kernel/
include kernel/kernel.mk 

# make the hard drive/cdrom images
$(BINDIR)os.iso: $(KERNEL_BINDIR)kernel.elf
	@mkdir -p $(BINDIR)iso/boot/grub
	@cp $(KERNEL_BINDIR)kernel.elf $(BINDIR)iso/boot/
	@cp boot/grub.cfg $(BINDIR)iso/boot/grub
	@grub-mkrescue -o $(BINDIR)os.iso $(BINDIR)iso/
	@echo Made os iso image!

# commands to run the emulators
.PHONY:
bochs:
	bochs -f bochsrc.txt

.PHONY:
qemu:
	qemu-system-x86_64 -cdrom build/os.iso -monitor stdio
	@echo

.PHONY:
clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
	rm -rf $(OUTPUTDIR)