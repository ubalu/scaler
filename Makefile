
.PHONY: default clean
default: scaler scalerd

scaler: build/main.o build/miniaudio.o
	$(CC) build/main.o build/miniaudio.o -Ofast -s -o scaler -ldl -lm -lpthread

scalerd: build/maind.o build/miniaudiod.o
	$(CC) build/maind.o build/miniaudiod.o -O0 -ggdb -o scalerd -ldl -lm -lpthread

build/main.o: src/main.c | build
	$(CC) -o build/main.o -c -Ofast -Wall -Wextra -Wpedantic -std=c23 src/main.c

build/miniaudio.o: src/miniaudio.c | build
	$(CC) -o build/miniaudio.o -c -Ofast src/miniaudio.c

build/maind.o: src/main.c | build
	$(CC) -o build/maind.o -c -O0 -ggdb -Wall -Wextra -Wpedantic -std=c23 src/main.c

build/miniaudiod.o: src/miniaudio.c | build
	$(CC) -o build/miniaudiod.o -c -O0 -ggdb src/miniaudio.c

build: 
	mkdir build/

clean:
	rm build/* scaler
