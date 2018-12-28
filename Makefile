CC=gcc
CFLAGS=-Wall


mon_gimp: main.o image.o
		$(CC) -o $@ $^

main.o: main.c image.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o