CC=g++ -std=c++17
GTK_FLAGS=`pkg-config --cflags --libs gtk4`
EPOXY_FLAGS=`pkg-config --cflags --libs epoxy`

a:
	$(CC) -g main.cc $(GTK_FLAGS) $(EPOXY_FLAGS)
	./a.out

