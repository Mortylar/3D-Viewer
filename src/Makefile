CC=g++ -std=c++17
MODEL_SOURCE=$(wildcard model/*.cc)
CONTROLLER_SOURCE=$(wildcard controller/*.cc)
VIEW_SOURCE=$(wildcard view/*.cc view/*/*.cc)
GTK_FLAGS=`pkg-config --cflags --libs gtk4`
EPOXY_FLAGS=`pkg-config --cflags --libs epoxy`


lib:
	cd model/ && make s21_model.a
	$(CC) main.cc $(GTK_FLAGS) $(EPOXY_FLAGS)
	#$(CC) main.o $(GTK_FLAGS) $(EPOXY_FLAGS)
a:
	$(CC) -g main.cc $(GTK_FLAGS) $(EPOXY_FLAGS)
	./a.out

b:
	$(CC) -g asd.cc $(GTK_FLAGS) $(EPOXY_FLAGS)
	./a.out
