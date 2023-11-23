CC = gcc
CFLAGS = -Wall -Wextra -g

ifdef DEBUG
CFLAGS += -DDEBUG=1
endif

all: tree_tests charset_tests

charset_tests: charset_tests.o charset.o tree.o tree-node.o
	$(CC) $(CFLAGS) -o charset_tests charset_tests.o charset.o tree.o tree-node.o

tree_tests: tree_tests.o tree.o tree-node.o
	$(CC) $(CFLAGS) -o tree_tests tree_tests.o tree.o tree-node.o

charset_tests.o: charset_tests.c charset.h
	$(CC) $(CFLAGS) -c charset_tests.c

tree_tests.o: tree_tests.c tree.h
	$(CC) $(CFLAGS) -c tree_tests.c

charset.o: charset.c charset.h
	$(CC) $(CFLAGS) -c charset.c

tree.o: tree.c tree.h tree-node.h
	$(CC) $(CFLAGS) -c tree.c

tree-node.o: tree-node.c tree-node.h
	$(CC) $(CFLAGS) -c tree-node.c

tests: tree_tests charset_tests
	@exec ./tree_tests
	@exec ./charset_tests

clean:
	rm -f *.o tree_tests charset_tests

