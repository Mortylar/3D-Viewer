CC=g++ -std=c++17
GTK_FLAGS=`pkg-config --cflags --libs gtk4`
EPOXY_FLAGS=`pkg-config --cflags --libs epoxy`
V=glarea-gl.vs.glsl
F=glarea-gl.fs.glsl
GLEW=`pkg-config --cflags --libs glew`

a:
	$(CC) -g main.cc $(GTK_FLAGS) $(EPOXY_FLAGS)
	./a.out

t: 
	g++ -c -g t.cc $(EPOXY_FLAGS) $(GTK_FLAGS)
	g++ t.o $(GTK_FLAGS) $(EPOXY_FLAGS)
	./a.out
