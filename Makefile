all: convert

convert: build/main.o build/command.o src/command.h 
	mkdir -p bin
	gcc -Wall -Werror build/main.o build/command.o -o convert 
build/main.o: src/main.c src/command.h
	mkdir -p build
	gcc -Wall -Werror -c src/main.c -o build/main.o
build/command.o: src/command.c src/command.h
	mkdir -p build
	gcc -Wall -Werror -c src/command.c -o build/command.o 

.PHONY: clean
clean:
	rm -f build/* convert

.PHONY: gdb
gdb:
	gcc -Wall -g -O0 src/main.c src/command.c -o tr
	gdb --args ./tr a.md -t b.html		
