CC=gcc
CFLAGS=-Wall -pthread

SRC=src/main.c src/parking_manager.c src/database.c src/ui.c src/auth.c
OUT=parkos

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
