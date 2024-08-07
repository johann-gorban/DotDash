all:
	gcc `pkg-config --cflags gtk4` ./src/*.c -o ./bin/app -Iinclude -Wall `pkg-config --libs gtk4`
	./bin/app
