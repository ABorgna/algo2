
GCC=g++
CFLAGS= -O0 -Wall -Wextra -ggdb -std=c++03
#CFLAGS= -O0 -Wall -Wextra -ggdb -std=c++03 -D NDEBUG
VALGRIND=valgrind --leak-check=full

MODULES=modulos/dato.cpp modulos/dato.h \
	modulos/db.cpp modulos/db.h \
	modulos/diccLog.h \
	modulos/diccTrie.h \
	modulos/tabla.cpp modulos/tabla.h

TESTS=	tests/testsEjemplo.h \
	tests/testsDiccLog.h

DEPEND= makefile \
	aed2.h \
	Driver.cpp Driver.h \
	Tipos.h \
	aed2/Arreglo.h \
	aed2/Conj.h \
	aed2/ConjAcotado.cpp aed2/ConjAcotado.h \
	aed2/Dicc.h \
	aed2/Lista.h \
	aed2/TiposBasicos.h \
	aed2/Vector.h \
	$(MODULES)

OBJ= $(filter %.o, $(DEPEND:.cpp=.o))

all: build

build: tests.cpp mini_test.h $(OBJ) $(DEPEND)
	$(GCC) $(CFLAGS) $< $(OBJ) -o $@

tests: tests.cpp mini_test.h $(OBJ) $(DEPEND) $(TESTS)
	$(GCC) $(CFLAGS) $< $(OBJ) -o $@

test: tests
	$(VALGRIND) ./tests

%.o: %.cpp %.h
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	find . -name '*.o' -type f -exec rm -f {} \;
	rm -f tests

