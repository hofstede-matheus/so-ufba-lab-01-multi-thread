CC=gcc
CFLAGS = -std=c99 -Wall -lm -lpthread -pthread

define clean
    rm -f src/*.o
endef

pi: src/pi.c src/errors.o src/errors.h
	mkdir -p build
	$(CC) $(CFLAGS) src/pi.c src/errors.o -o build/pi
	$(clean)

matrix: src/matrix.c src/errors.o src/errors.h
	mkdir -p build
	$(CC) $(CFLAGS) src/matrix.c src/errors.o -o build/matrix
	$(clean)

clean:
	rm -f src/*.o
