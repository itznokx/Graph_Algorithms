main.o:
	gcc -I./lib -o main.o test_main.c lib/node.c
compile: main.o
force_compile:
	rm *.o
	make compile