
.PHONY: default clean
default: scaler

scaler: build/main.o build/miniaudio.o
	$(CC) build/main.o build/miniaudio.o -Ofast -s -o scaler -ldl -lm -lpthread

build/main.o: src/main.c | build
	$(CC) -o build/main.o -c -Ofast -Wall -Wextra -Wpedantic -std=c23 src/main.c

build/miniaudio.o: src/miniaudio.c | build
	$(CC) -o build/miniaudio.o -c -Ofast src/miniaudio.c

build: 
	mkdir build/

clean:
	rm build/* scaler
