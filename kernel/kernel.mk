KERNEL_OBJDIR:=$(OBJDIR)$(dir)
KERNEL_BINDIR:=$(BINDIR)$(dir)
KERNEL_SRCDIR:=$(dir)
KERNEL_C_SOURCES:=$(call rwildcard,$(KERNEL_SRCDIR),*.c)
KERNEL_C_OBJS:=$(KERNEL_C_SOURCES:$(KERNEL_SRCDIR)%.c=$(KERNEL_OBJDIR)%.o)
KERNEL_ASM_SOURCES:=$(call rwildcard,$(KERNEL_SRCDIR),*.asm)
KERNEL_ASM_OBJS:=$(KERNEL_ASM_SOURCES:$(KERNEL_SRCDIR)%.asm=$(KERNEL_OBJDIR)%.o)

KERNEL_LFLAGS:=-s -m elf_i386 -T $(KERNEL_SRCDIR)link.ld #-L$(RUNTIME_BINDIR)k
KERNEL_CFLAGS:=-I$(KERNEL_SRCDIR)
KERNEL_ASFLAGS:=-I$(KERNEL_SRCDIR)common -I$(KERNEL_SRCDIR)arch/i386/

KERNEL_OBJS := $(KERNEL_C_OBJS) $(KERNEL_ASM_OBJS) $(RUNTIME_BINDIR)libk.a

# compile kernel c sources
$(KERNEL_C_OBJS): $(KERNEL_OBJDIR)%.o : $(KERNEL_SRCDIR)%.c
	$(dir_guard)
	$(CC) $(CFLAGS) $(K32_CFLAGS) $(KERNEL_CFLAGS) -c $< -o $@
	$(compile_msg)

# building assembly files with nasm
$(KERNEL_ASM_OBJS): $(KERNEL_OBJDIR)%.o: $(KERNEL_SRCDIR)%.asm
	$(dir_guard)
	$(AS) $(ASFLAGS) $(KERNEL_ASFLAGS) $< -o $@
	@echo $(COLOR_COMPILE)"Compiled"$(COLOR_CLR) $(COLOR_FILE2)$<$(COLOR_CLR) $(COLOR_COMPILE)"successfully!"$(COLOR_CLR)

# build kernel elf image
$(KERNEL_BINDIR)kernel.elf: $(KERNEL_OBJS)
	$(dir_guard)
	$(LD) $(LFLAGS) $(KERNEL_LFLAGS) -o $@ $^
	$(link_msg)