
CFLAGS=-g
CC=gcc

# the following lines allow to construct dependencies files in the .d directory
# for full description follow the link below
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
# another usefull and simpler article about Makefile;
# http://icps.u-strasbg.fr/people/loechner/public_html/enseignement/GL/make.pdf

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

%.o : %.c
%.o : %.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

SRCS = 	client.c \
	config.c \
        fill_shm_table.c \
        list_shm_table.c \
	search_spectacle.c \
        set_nb_places.c \
        create_message_cons.c \
        create_message_res.c \
        display_message_cons.c \
        display_message_res.c \
	serveur_cons.c\
	serveur_res.c
	

SUBDIRS = ./lib
	
LIBS = lib/lib.a

all: 
	for i in $(SUBDIRS); do (cd $$i; make all); done
	make client
	make config
	make serveur_res
	make serveur_cons

lib.a:
	cd lib;make lib.a

client: client.o $(LIBS)
	$(CC) -o client client.o $(LIBS)

config: config.o fill_shm_table.o list_shm_table.o $(LIBS)
	$(CC) -o config config.o fill_shm_table.o list_shm_table.o $(LIBS)

serveur_res: serveur_res.o list_shm_table.o search_spectacle.o $(LIBS)
	$(CC) -o serveur_res serveur_res.o list_shm_table.o search_spectacle.o $(LIBS) -lpthread

serveur_cons: serveur_cons.o search_spectacle.o $(LIBS)
	$(CC) -o serveur_cons serveur_cons.o search_spectacle.o $(LIBS)

clean : 
	rm client
	rm config
	rm serveur_res
	rm serveur_cons
	rm -f $(OBJ) core *~ $(NAME)
	rm -f .d/*.d
	rm *.o
	for i in $(SUBDIRS); do (cd $$i; make clean); done
	

fclean: clean
	rm $(NAME)

re : fclean all



-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
