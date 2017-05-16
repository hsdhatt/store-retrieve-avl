CC=gcc
CFLAGS= -Wall -c -fPIC

all: avl

app: test
	$(CC) -L$(PWD) test.o -o app -lavl -lpthread

avl: rotate height avlc
	$(CC) -shared height.o rotate.o avl.o -o libavl.so -lm -lpthread

test: test.o
	$(CC) -c -Wall test.c

avlc: avl.o
	$(CC) $(CFLAGS) avl.c

height: height.o
	$(CC) $(CFLAGS) height.c

rotate: rotate.o
	$(CC) $(CFLAGS) rotate.c

clean:
	rm -rf *.o libavl.so app
