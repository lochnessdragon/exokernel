RUNTIME_SRCDIR:=$(dir)src/
RUNTIME_OBJDIR:=$(OBJDIR)$(dir)
RUNTIME_SOURCES:=$(call rwildcard,$(RUNTIME_SRCDIR),*.c)
RUNTIME_OBJS:=$(RUNTIME_SOURCES:$(RUNTIME_SRCDIR)%.c=$(RUNTIME_OBJDIR)%.o)
RUNTIME_BINDIR:=$(BINDIR)$(dir)

RUNTIME_CFLAGS:=-Ikernel/ -D__kernel_libk

$(RUNTIME_OBJDIR)%.o: $(RUNTIME_SRCDIR)%.c 
	$(dir_guard)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(RUNTIME_CFLAGS) $< -o $@
	$(compile_msg)

$(RUNTIME_BINDIR)libk.a: $(RUNTIME_OBJS)
	$(dir_guard)
	$(link_msg)
	ar rcs $@ $^

RUNTIME_TEST_SRCDIR:=$(dir)tests/
RUNTIME_TEST_OBJDIR:=$(OBJDIR)$(dir)tests/
RUNTIME_TEST_SRCS:=$(call rwildcard,$(RUNTIME_TEST_SRCDIR),*.c)
RUNTIME_TEST_OBJS:=$(RUNTIME_TEST_SRCS:$(RUNTIME_TEST_SRCDIR)%.c=$(RUNTIME_TEST_OBJDIR)%.o)
RUNTIME_TEST_FLAGS=

$(RUNTIME_TEST_OBJDIR)%.o: $(RUNTIME_TEST_SRCDIR)%.c 
	$(dir_guard)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(RUNTIME_TEST_FLAGS) $< -o $@
	$(compile_msg)

$(BINDIR)stdctests: $(RUNTIME_TEST_OBJS)
	$(dir_guard)
	$(link_msg)
	$(LD) $(LFLAGS) -o $@ $^