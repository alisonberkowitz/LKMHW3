LIB = /Users/nlintz/Downloads/mongo-c-driver/src

test_seed_DB: test/seedDB.c
	gcc --std=gnu99 -I$(LIB) $(LIB)/*.c test/seedDB.c -o build/seedDB

test_drop_DB: test/dropDB.c
	gcc --std=gnu99 -I$(LIB) $(LIB)/*.c test/dropDB.c -o build/dropDB

Node.o: src/Node.h src/Node.c
	gcc -c src/Node.c -o build/Node.o

Queue.o: src/Queue.h src/Queue.c
	gcc	-c src/Queue.c -o build/Queue.o

Hashmap.o: src/Hashmap.h src/Hashmap.c
	gcc -c src/Hashmap.c -o build/Hashmap.o

testQueue.o: test/testQueue.c src/Queue.h src/Node.h
	gcc -c test/testQueue.c -o build/testQueue.o

testHashmap.o: test/testHashmap.c src/Hashmap.h src/Node.h
	gcc -c test/testHashmap.c -o build/testHashmap.o

testNode.o: test/testNode.c src/Node.h src/Queue.h
	gcc -c test/testNode.c -o build/testNode.o

testQueue: testQueue.o Queue.o Node.o
	gcc build/testQueue.o build/Queue.o build/Node.o -o build/testQueue

testHashmap: testHashmap.o Hashmap.o
	gcc build/Hashmap.o build/testHashmap.o -o build/testHashmap

testNode: testNode.o Node.o
	gcc build/Node.o build/testNode.o -o build/testNode

testQuery: src/Node.h src/Queries.h
	gcc --std=gnu99 -I$(LIB) $(LIB)/*.c test/testQuery.c src/Node.c src/Queries.c -o build/testQuery

BFS: src/BreadthFirstSearch.c src/BreadthFirstSearch.h src/Node.h src/Queries.h src/Queue.h src/Hashmap.h
	gcc --std=gnu99 -I$(LIB) $(LIB)/*.c src/BreadthFirstSearch.c src/Node.c src/Queries.c src/Queue.c src/Hashmap.c -o build/BFS
>>>>>>> 9f9615aa62f4280fb6437df6e3405f74b0e2da52
