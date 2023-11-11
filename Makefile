CC = gcc
CFLAGS = -Wall -Wextra -g

all: tests_tree

tests_tree: tests_tree.o tree.o tree-node.o
	$(CC) $(CFLAGS) -o tests_tree tests_tree.o tree.o tree-node.o

tests_tree.o: tests_tree.c tree.h
	$(CC) $(CFLAGS) -c tests_tree.c

tree.o: tree.c tree.h tree-node.h
	$(CC) $(CFLAGS) -c tree.c

tree-node.o: tree-node.c tree-node.h
	$(CC) $(CFLAGS) -c tree-node.c

clean:
	rm -f *.o tests_tree

