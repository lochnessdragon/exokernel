RUNTIME_SRCDIR:=$(dir)src/
RUNTIME_OBJDIR:=$(OBJDIR)$(dir)
RUNTIME_SOURCES:=$(call rwildcard,$(RUNTIME_SRCDIR),*.c)
RUNTIME_OBJS:=$(RUNTIME_SOURCES:$(RUNTIME_SRCDIR)%.c=$(RUNTIME_OBJDIR)%.o)
RUNTIME_BINDIR:=$(BINDIR)$(dir)

$(RUNTIME_OBJDIR)%.o: $(RUNTIME_SRCDIR)%.c 
	$(dir_guard)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	@echo $(COLOR_COMPILE)"Compiled"$(COLOR_CLR) $(COLOR_FILE)$<$(COLOR_CLR) $(COLOR_COMPILE)"successfully!"$(COLOR_CLR)

$(RUNTIME_BINDIR)libk.a: $(RUNTIME_OBJS)
	$(dir_guard)
	@echo $(COLOR_LINK)"Linking:"$(COLOR_CLR) $(COLOR_FILE)$@$(COLOR_CLR)
	ar rcs $@ $^
