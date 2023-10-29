install: Compilador

Compilador: build/Itens.o \
build/AnalisadorSintatico.o \
build/AnalisadorSemantico.o \
build/AnalisadorLexico.o \
build/main.o

	gcc -g \
	build/main.o \
	build/AnalisadorLexico.o \
	build/AnalisadorSemantico.o \
	build/AnalisadorSintatico.o \
	build/Itens.o \
	-o Compilador

build/AnalisadorSintatico.o: src/AnalisadorSintatico.c \
src/include/AnalisadorSintatico.h \
build 
	gcc -g -c src/AnalisadorSintatico.c -o build/AnalisadorSintatico.o

build/AnalisadorSemantico.o: src/AnalisadorSemantico.c \
src/include/AnalisadorSemantico.h \
build 

	gcc -g -c src/AnalisadorSemantico.c -o build/AnalisadorSemantico.o

build/AnalisadorLexico.o: src/AnalisadorLexico.c \
src/include/AnalisadorLexico.h \
build 

	gcc -g -c src/AnalisadorLexico.c -o build/AnalisadorLexico.o

build/main.o: src/main.c build
	gcc -g -c src/main.c -o build/main.o

build/Itens.o: src/Itens.c src/include/Itens.h build
	gcc -g -c src/Itens.c -o build/Itens.o

build:
	mkdir build

uninstall:
	rm -r build
	rm -r Compilador

