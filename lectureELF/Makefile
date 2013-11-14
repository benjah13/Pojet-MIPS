CC=`which gcc`
LD=`which gcc`
RM=`which rm` -f
DOXYGEN=`which doxygen`
TAR=`which tar` -czvf

SRCDIR=src
INCDIR= -I include

CFLAGS_DBG=$(CFLAGS) -g -DDEBUG -DVERBOSE
CFLAGS_RLS=$(CFLAGS)
CFLAGS= -Wall $(INCDIR)
LFLAGS= -lelf -lm

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ_DBG=$(SRC:.c=.dbg.o)
OBJ_RLS=$(SRC:.c=.rls.o)

GARBAGE=*~ include/*~ *.orig include/*.orig src/*~ src/*.orig

ARCHNAME=`date +%d-%m-%y-%H-%M`-`whoami`.tgz
ARCHCONTENT=$(SRC) *file res include doc

all : mips-load-test mips-load

mips-load : $(OBJ_RLS)
	$(LD) $^ -o $@ $(LFLAGS)


mips-load-test : $(OBJ_DBG)
	$(LD) $^ -o $@ $(LFLAGS)

%.rls.o : %.c
	$(CC) $< $(CFLAGS) $(CFLAGS_RLS) -c -o $(basename $<).rls.o

%.dbg.o : %.c
	$(CC) $< $(CFLAGS) $(CFLAGS_DBG) -c -o $(basename $<).dbg.o

clean : 
	$(RM) $(OBJ) $(GARBAGE) $(TARGET) $(SRCDIR)/*.o

documentation : 
	$(DOXYGEN)

archive : 
	$(TAR) ../$(ARCHNAME) $(ARCHCONTENT) && mv ../$(ARCHNAME) .
