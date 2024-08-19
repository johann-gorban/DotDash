CC = gcc
CFLAGS = `pkg-config --cflags gtk4`
LIBS = `pkg-config --libs gtk4`

all:
	$(CC) $(CFLAGS) ./src/*.c -o ./bin/app -Iinclude -Wall $(LIBS)
	./bin/app
