CC=g++ -std=c++17
GTK_FLAGS=`pkg-config --cflags --libs gtk4`
V=glarea-gl.vs.glsl
F=glarea-gl.fs.glsl
GLEW=`pkg-config --cflags --libs glew`

a:
	$(CC) -g main.cc $(GTK_FLAGS) -lepoxy
	./a.out

t: 
	g++ -c -g t.cc -lepoxy -lglfw $(GTK_FLAGS) -lGL 
	g++ t.o $(GTK_FLAGS) -lepoxy
	./a.out
