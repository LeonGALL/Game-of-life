CC = gcc
CFLAGS = -g
OPATH = obj/
SPATH = src/
HPATH = include/
BPATH = bin/

VERSION=1.0

ARCHIVE = $(SPATH) $(HPATH) makefile Doxyfile
ARCHIVENAME = leon-gall-v-$(VERSION)

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
	$(CC) $(CFLAGS) -o $@ -c $< -I $(HPATH)

dist :
	tar -Jcv $(ARCHIVE) -f $(ARCHIVENAME).tar.xz

docs :
	doxygen

debug :
	gdb ./$(BPATH)$(EXEC)
	
clean : 
	rm $(OPATH)*.o && rm $(BPATH)$(EXEC)

