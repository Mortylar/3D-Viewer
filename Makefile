CC=g++ -std=c++17
GTK_FLAGS=`pkg-config --cflags --libs gtk4`

a:
	$(CC) base.cc $(GTK_FLAGS)
	./a.out
