CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra
GTK_FLAGS=`pkg-config --cflags --libs gtk4`
SOURCE=$(wildcard *.cc)

a:
	$(CC) $(GTK_FLAGS) $(SOURCE)
	./a.out

leaks: a
	leaks -atExit -- ./a.out
