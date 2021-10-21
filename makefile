CC = gcc
CFLAGS = -g -Wall
IFLAGS = -I $(HPATH)
OPATH = obj/
SPATH = src/
HPATH = include/
BPATH = bin/

VERSION=2_0_5

ARCHIVE = $(SPATH) $(HPATH) makefile Doxyfile
ARCHIVENAME = GallLéon-GoL-$(VERSION)

EXEC = main

vpath %.h $(HPATH)
vpath %.c $(SPATH)
vpath %.o $(OPATH)

SOURCES = $(wildcard $(SPATH)*.c)
OBJETS = $(patsubst %.c,$(OPATH)%.o,$(notdir $(SOURCES)))

	
$(EXEC) : $(OBJETS)
	@mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $(BPATH)$(EXEC) $^

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
	rm -rf $(OPATH) && rm -rf $(BPATH) && rm -rf documentation/

