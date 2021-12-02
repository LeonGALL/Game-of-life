CC = gcc
CFLAGS = -g -Wall
IFLAGS = -I$(HPATH)
LDFLAGS = -L$(LPATH) -ljeu
OPATH = obj/
SPATH = src/
HPATH = include/
BPATH = bin/
LPATH = lib/

VERSION=5_0_3

ARCHIVE = $(SPATH) $(HPATH) makefile Doxyfile README.md
ARCHIVENAME = GallLéon-GoL-$(VERSION)

LIB = $(LPATH)libjeu.a

EXEC = main

vpath %.h $(HPATH)
vpath %.c $(SPATH)
vpath %.o $(OPATH)
vpath %.a $(LPATH)

SOURCES = $(wildcard $(SPATH)*.c)
OBJETS_ALL = $(patsubst %.c,$(OPATH)%.o,$(notdir $(SOURCES))) 								# Tous les objets
LIBOBJ = $(filter %jeu.o, $(OBJETS_ALL))  $(filter %grille.o, $(OBJETS_ALL))	# Objets de la librairie
OBJETS__ = $(filter-out %jeu.o, $(OBJETS_ALL))
OBJETS_ = $(filter-out %grille.o, $(OBJETS__)) 																# Objets sans ceux de la librairie

##### COMPILATION JEU DE LA VIE TERMINAL
ifeq ($(MODE),TEXTE)	
OBJETS= $(filter-out %_cairo.o,$(OBJETS_))

##### COMPILATION JEU DE LA VIE GRAPHIQUE

else ifeq ($(MODE),PERSO) ### PATH LIBRAIRIES ORDINATEUR PERSONNEL
IFLAGS += -I/sw/include/cairo -I/usr/X11/include/
LDFLAGS += -L/sw/lib/ -L/usr/X11/lib/ -lcairo -lm -lX11 -lfontconfig
OBJETS = $(filter-out %_terminal.o, $(OBJETS_))
else ### PATH LIBRAIRIES ORDINATEUR UNISTRA
IFLAGS += -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11 -lfontconfig
OBJETS = $(filter-out %_terminal.o, $(OBJETS_))
endif

$(EXEC) : $(OBJETS) $(LIB)
	@mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $(BPATH)$(EXEC) $(OBJETS) $(LDFLAGS)

$(OPATH)%.o : %.c
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(IFLAGS)

$(LPATH)%.a: $(LIBOBJ)
	@mkdir -p $(LPATH)
	ar -crv $@ $^
	ranlib $@

dist :
	tar -Jcvf $(ARCHIVENAME).tar.xz $(ARCHIVE)

docs :
	doxygen Doxyfile

debug :
	gdb ./$(BPATH)$(EXEC)
	
clean : 
	rm -rf $(OPATH) && rm -rf $(BPATH) && rm -rf doc/ && rm -f *.tar.xz && rm -rf lib/

