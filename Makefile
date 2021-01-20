# GRR20190363 Luan Machado Bernardt
all: ortografia clean

ortografia: ortografia.o dicionario.o
	gcc ortografia.o dicionario.o -o ortografia -Wall

ortografia.o: ortografia.c dicionario.h
	gcc -c ortografia.c -Wall

dicionario.o: dicionario.c dicionario.h
	gcc -c dicionario.c -Wall

clean:
	-rm -f *.o

purge:
	-rm -f ortografia
