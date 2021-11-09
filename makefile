CC = gcc
CFLAGS = -g -Wall
IFLAGS = -I $(HPATH)
OPATH = obj/
SPATH = src/
HPATH = include/
BPATH = bin/

VERSION=4_0_1

ARCHIVE = $(SPATH) $(HPATH) makefile Doxyfile README.md
ARCHIVENAME = GallLéon-GoL-$(VERSION)

EXEC = main

vpath %.h $(HPATH)
vpath %.c $(SPATH)
vpath %.o $(OPATH)

SOURCES = $(wildcard $(SPATH)*.c)
OBJETS_ = $(patsubst %.c,$(OPATH)%.o,$(notdir $(SOURCES)))

##### COMPILATION JEU DE LA VIE TERMINAL
ifeq ($(MODE),TEXT)	
OBJETS= $(filter-out %_cairo.o,$(OBJETS_))

##### COMPILATION JEU DE LA VIE GRAPHIQUE
else
IFLAGS += -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
OBJETS = $(filter-out %_terminal.o, $(OBJETS_))
endif

$(EXEC) : $(OBJETS)
	@mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $(BPATH)$(EXEC) $^ $(LDFLAGS)

$(OPATH)%.o : %.c
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(IFLAGS)

dist :
	tar -Jcvf $(ARCHIVENAME).tar.xz $(ARCHIVE)

docs :
	doxygen Doxyfile

debug :
	gdb ./$(BPATH)$(EXEC)
	
clean : 
	rm -rf $(OPATH) && rm -rf $(BPATH) && rm -rf doc/ && rm -f *.tar.xz

