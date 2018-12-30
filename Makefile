CC=gcc
CFLAGS=-Wall
SRC=./src/
BIN=./bin/


$(BIN)minigimp: $(SRC)main.o $(SRC)image.o $(SRC)lut.o
		$(CC) -o $@ $^

main.o: $(SRC)main.c $(SRC)image.h $(SRC)lut.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(SRC)*.o