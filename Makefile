main.o:
	gcc -I./lib -o main.o test_main.c lib/node.c
compile: main.o

test_node.o: .FORCE
	gcc -I./lib -o test_node.o test_node.c lib/node.c
testnode: test_node.o

nodetest: node_test.out

node_test.out: .FORCE
	g++ node_test.cpp -o node_test.out
.FORCE:

graphtest.out: .FORCE
	g++ graphtest.cpp -o graphtest.out

graph: graphtest.out

clean:
	rm -rf *.o
	rm -rf libcpp/*.gch
