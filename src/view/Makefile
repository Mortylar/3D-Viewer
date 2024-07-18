CC=g++ -std=c++17 -O3
GTK_FLAGS=`pkg-config --cflags --libs gtk4`
SOURCE=$(wildcard *.cc widget/*.cc)

libs21_view.a:
	$(CC) -c $(SOURCE) $(GTK_FLAGS)
	ar rcs libs21_view.a *.o
	ranlib libs21_view.a

clean:
	-rm *.o libs21_view.a
