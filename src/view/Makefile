CC=g++ -std=c++17
GTK_FLAGS=`pkg-config --cflags --libs gtk4`

base:
	$(CC) base.cc pannel.cc $(GTK_FLAGS)
	./a.out
a:
	$(CC) button.cc $(GTK_FLAGS)
	./a.out
