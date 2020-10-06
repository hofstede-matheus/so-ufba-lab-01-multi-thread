CC=gcc
CFLAGS = -std=c99 -Wall -lm -lpthread -pthread

define clean
    rm -f src/*.o
endef

pi: src/calcpi.c
	mkdir -p build
	$(CC) $(CFLAGS) src/calcpi.c -o build/pi
	$(clean)

multmatriz: src/multmatriz.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/multmatriz.c -o build/multmatriz
	$(clean)

estatistica: src/estatistica.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/estatistica.c -o build/estatistica
	$(clean)

primos: src/primos.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/primos.c -o build/primos
	$(clean)

clean:
	rm -f src/*.o
