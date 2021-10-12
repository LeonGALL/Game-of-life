CC = gcc -g

OPATH = obj/
SPATH = src/
HPATH = include/
BPATH = bin/

VERSION=1.0

ARCHIVE = src/ makefile Doxyfile
ARCHIVENAME = leon-gall-v-$(VERSION)

EXEC = main

vpath %.h $(HPATH)
vpath %.c $(SPATH)
vpath %.o $(OPATH)

SOURCES = $(wildcard $(SPATH)*.c)
OBJETS = $(patsubst %.c,$(OPATH)%.o,$(notdir $(SOURCES)))

	
$(EXEC) : $(OBJETS) | bin
	$(CC) -o $(BPATH)$(EXEC) $^

$(OPATH)%.o : %.c | obj
	$(CC) -o $@ -c $< -I $(HPATH)


obj :
	@mkdir $(OPATH)

bin :
	@mkdir $(BPATH)


dist :
	tar -c $(ARCHIVE) | xz > $(ARCHIVENAME).tar.xz

docs :
	doxygen

debug :
	gdb ./$(BPATH)$(EXEC)
	
clean : 
	rm $(OPATH)*.o && rm $(BPATH)$(EXEC)

