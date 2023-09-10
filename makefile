install: Compilador

Compilador: build/main.o build/AnalisadorLexico.o
	gcc -g build/main.o build/AnalisadorLexico.o -o Compilador

build/AnalisadorLexico.o: src/AnalisadorLexico.c src/include/AnalisadorLexico.h build
	gcc -g -c src/AnalisadorLexico.c -o build/AnalisadorLexico.o

build/main.o: src/main.c build
	gcc -g -c src/main.c -o build/main.o

build:
	mkdir build

clean:
	rm -r build
	rm -r Compilador

