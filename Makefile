main.o:
	gcc -I./lib -o main.o test_main.c lib/node.c
compile: main.o
test_node.o:
	gcc -I./lib -o test_node.o test_node.c lib/node.c

testnode: test_node.o
clean:
	rm -rf *.o
force_compile:
	rm -rf *.o
	make compile