CC=g++ -std=c++17
GTK_FLAGS=`pkg-config --cflags --libs gtk4`

a:
	$(CC) -g main.cc $(GTK_FLAGS)
	./a.out
b:
	$(CC) button.cc $(GTK_FLAGS)
	./a.out
