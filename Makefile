

all:
	gcc sync-output.c -o sync -std=c99 -pthread

clean:
	rm sync
