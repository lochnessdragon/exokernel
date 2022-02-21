RUNTIME_SRCDIR:=$(dir)src/
RUNTIMEK_OBJDIR:=$(OBJDIR)$(dir)libk/
RUNTIMEC_OBJDIR:=$(OBJDIR)$(dir)libc/
RUNTIME_SOURCES:=$(call rwildcard,$(RUNTIME_SRCDIR),*.c)
RUNTIMEK_OBJS:=$(RUNTIME_SOURCES:$(RUNTIME_SRCDIR)%.c=$(RUNTIMEK_OBJDIR)%.o)
RUNTIMEC_OBJS:=$(RUNTIME_SOURCES:$(RUNTIME_SRCDIR)%.c=$(RUNTIMEC_OBJDIR)%.o)
RUNTIME_BINDIR:=$(BINDIR)$(dir)

RUNTIMEK_CFLAGS:=-Ikernel/ -D__kernel_libk
RUNTIMEC_CFLAGS:=-I$(dir)include/ -nostdlib -fno-builtin

# for kernel libk compilation
$(RUNTIMEK_OBJDIR)%.o: $(RUNTIME_SRCDIR)%.c 
	$(dir_guard)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(K32_CFLAGS) $(RUNTIMEK_CFLAGS) $< -o $@
	$(compile_msg)

# for regular libc compilation
$(RUNTIMEC_OBJDIR)%.o: $(RUNTIME_SRCDIR)%.c 
	$(dir_guard)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(RUNTIMEC_CFLAGS) $< -o $@
	$(compile_msg)

$(RUNTIME_BINDIR)libk.a: $(RUNTIMEK_OBJS)
	$(dir_guard)
	$(link_msg)
	ar rcs $@ $^

$(RUNTIME_BINDIR)libc.a: $(RUNTIMEC_OBJS)
	$(dir_guard)
	$(link_msg)
	ar rcs $@ $^
	ranlib $@

RUNTIME_TEST_SRCDIR:=$(dir)tests/
RUNTIME_TEST_OBJDIR:=$(OBJDIR)$(dir)tests/
RUNTIME_TEST_SRCS:=$(call rwildcard,$(RUNTIME_TEST_SRCDIR),*.c)
RUNTIME_TEST_OBJS:=$(RUNTIME_TEST_SRCS:$(RUNTIME_TEST_SRCDIR)%.c=$(RUNTIME_TEST_OBJDIR)%.o)
RUNTIME_TEST_FLAGS=

$(RUNTIME_TEST_OBJDIR)%.o: $(RUNTIME_TEST_SRCDIR)%.c 
	$(dir_guard)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(RUNTIMEC_CFLAGS) $(RUNTIME_TEST_FLAGS) $< -o $@
	$(compile_msg)

$(BINDIR)stdctests: $(RUNTIME_BINDIR)libc.a $(RUNTIME_TEST_OBJS)
	$(dir_guard)
	$(link_msg)
	$(LD) $(LFLAGS) -o $@ $^