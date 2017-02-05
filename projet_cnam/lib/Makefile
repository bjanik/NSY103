CC = gcc

# the following lines allow to construct dependencies files in the .d directory
# for full description follow the link below
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

%.o : %.c
%.o : %.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d


SUBDIR= lib

NAME = lib.a

SRCS = 	create_shm.c \
	attach_shm.c \
	remove_shm.c \
	create_msgq.c \
	get_next_line.c \
	ft_strsplit.c \
	ft_memalloc.c \

OBJ=$(subst .c,.o,$(SRCS))

all : $(NAME)
$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)
clean : 
	rm -f $(OBJ) core *~ $(NAME)
	rm -f $(OBJ) core *~ $(NAME)
	rm -f .d/*.d

fclean: clean
	rm $(NAME)

re : fclean all


-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
