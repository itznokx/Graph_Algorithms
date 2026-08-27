main.o:
	gcc -I./lib -o main.o test_main.c lib/node.c
compile: main.o
test_node.o: .FORCE
	gcc -I./lib -o test_node.o test_node.c lib/node.c
testnode: test_node.o
nodetest: node_test.o
node_test.o: .FORCE
    g++ -c node_test.cpp
.FORCE:
clean:
	rm -rf *.o
