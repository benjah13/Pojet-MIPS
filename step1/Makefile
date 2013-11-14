TARGET=simMips

CC=`which gcc`
LD=`which gcc`
RM=`which rm` -f

SRCDIR=src
INCDIR=include
%TESTDIR=testing


GARBAGE=*~ $(SRCDIR)/*~ $(INCDIR)/*~ $(TESTDIR)/*~ $(SRCDIR)/*.orig $(INCDIR)/*.orig

INCLUDE=-I$(INCDIR)

CFLAGS=-Wall $(INCLUDE)
LFLAGS=-lreadline -lm -lcurses

CFLAGS_DBG=$(CFLAGS) -g -DDEBUG -DVERBOSE
CFLAGS_RLS=$(CFLAGS)

SRC=$(wildcard $(SRCDIR)/*.c)

OBJ_DBG=$(SRC:.c=.dbg.o)
OBJ_RLS=$(SRC:.c=.rls.o)

all : 
	@echo ""
	@echo "Usage:"
	@echo ""
	@echo "make debug   => build DEBUG   version"
	@echo "make release => build RELEASE version"
	@echo "make clean   => clean everything"
	@echo "make tarball => produce archive .tar.gz in ../ directory"

debug   : $(OBJ_DBG)
	$(LD) $^ $(LFLAGS) -o $(TARGET)

release : $(OBJ_RLS)
	$(LD) $^ $(LFLAGS) -o $(TARGET)

%.rls.o : %.c
	$(CC) $< $(CFLAGS_RLS) -c -o $(basename $<).rls.o

%.dbg.o : %.c
	$(CC) $< $(CFLAGS_DBG) -c -o $(basename $<).dbg.o

clean : 
	$(RM) $(TARGET) $(SRCDIR)/*.o $(GARBAGE)

tarball : 
	make clean 
	tar -czvf ../$(notdir $(PWD) )-`whoami`-`date +%d-%m-%H-%M`.tgz .
	echo "Fichier archive ../simMips-`whoami`-`date +%d-%m-%H-%M`.tgz genere"
