# custom colors for funz!
COLOR_COMPILE='\033[1;32m'
COLOR_LINK='\033[1;95m'
COLOR_FILE='\033[4;94m'
COLOR_FILE2='\033[4;93m'
COLOR_CLR='\033[0m'
COLOR_SUCCESS='\033[1;36m'

# sets the folders to use to place object files and the final output
BINDIR=build/
INTDIR=build-int/

AS=nasm
ASFLAGS=

LD=ld
LFLAGS=

CC=gcc 
CFLAGS=
# could optimize by only including general registers on idts.
K32_CFLAGS=-m32 -Iruntime/include/ -ffreestanding -fno-stack-protector -nostartfiles -nodefaultlibs -fno-pie -Wall -Wextra -Werror -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mgeneral-regs-only

OBJDIR=build-int/
BINDIR=build/

dir_guard=@mkdir -p $(@D)
link_msg=@echo $(COLOR_LINK)"Linking:"$(COLOR_CLR) $(COLOR_FILE)$@$(COLOR_CLR)
compile_msg=@echo $(COLOR_COMPILE)"Compiled"$(COLOR_CLR) $(COLOR_FILE)$<$(COLOR_CLR) $(COLOR_COMPILE)"successfully!"$(COLOR_CLR)
compile_asm_msg=@echo $(COLOR_COMPILE)"Compiled"$(COLOR_CLR) $(COLOR_FILE2)$<$(COLOR_CLR) $(COLOR_COMPILE)"successfully!"$(COLOR_CLR)

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
	@echo $(COLOR_SUCCESS)Made os iso image!$(COLOR_CLR) 🚀 # <- yes, that is an emoji

# commands to run the emulators
.PHONY:
bochs: $(BINDIR)os.iso
	bochs -f bochsrc.txt

.PHONY:
qemu: $(BINDIR)os.iso
	qemu-system-x86_64 -cdrom build/os.iso -monitor stdio -D qemu.log -d guest_errors,pcall
	@echo

.PHONY:
clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY:
check: $(BINDIR)stdctests
	$(BINDIR)stdctests