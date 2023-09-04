install: AnalisadorLexico

AnalisadorLexico: build/main.o build/TInfoAtomo.o
	gcc build/main.o build/TInfoAtomo.o -o AnalisadorLexico

build/TInfoAtomo.o: src/TInfoAtomo.c src/include/TInfoAtomo.h build
	gcc -c src/TInfoAtomo.c -o build/TInfoAtomo.o

build/main.o: src/main.c build
	gcc -c src/main.c -o build/main.o

build:
	mkdir build

clean:
	rm -r build

