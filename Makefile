CC = gcc
CFLAGS = -Wall -Wextra -g

all: tree_tests

tree_tests: tree_tests.o tree.o tree-node.o
	$(CC) $(CFLAGS) -o tree_tests tree_tests.o tree.o tree-node.o

tree_tests.o: tree_tests.c tree.h
	$(CC) $(CFLAGS) -c tree_tests.c

tree.o: tree.c tree.h tree-node.h
	$(CC) $(CFLAGS) -c tree.c

tree-node.o: tree-node.c tree-node.h
	$(CC) $(CFLAGS) -c tree-node.c

tests: tree_tests
	@exec ./tree_tests

charset.o: charset.c charset.h

clean:
	rm -f *.o tree_tests

