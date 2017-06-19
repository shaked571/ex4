CC=g++
RANLIB=ranlib

LIBSRC= Algorithm.cpp Algorithm.h Block.cpp Block.h CacheFS.cpp CacheFS.h

LIBOBJ=Algorithm.o Block.o CacheFS.o
EXTRADELETE=CacheFS.a Test Test.o

INCS=-I.
CFLAGS = -Wall -Wextra -g $(INCS)
LOADLIBES = -L./ 
LFLAGS = -o

TAR=tar
TARFLAGS=-cvf
TARNAME=ex4.tar
TARSRCS= Algorithm.cpp Algorithm.h Block.cpp Block.h CacheFS.cpp CacheFS.h README Answers.pdf Makefile

Test: Test.o CacheFS.a
	$(CC) $(CFLAGS) $^ $(LOADLIBES) CacheFS.a -o $@ -lpthread

Test.o: check.cpp
	$(CC) -c $^ -o $@


CacheFS.a: $(LIBOBJ)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

clean:
	$(RM) $(TARGETS) $(OBJ) $(LIBOBJ) $(EXTRADELETE) *~ *core

depend:
	makedepend -- $(CFLAGS) -- $(SRC) $(LIBSRC)

tar:
	$(TAR) $(TARFLAGS) $(TARNAME) $(TARSRCS)


