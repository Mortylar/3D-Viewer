CC=g++ -std=c++17
MODEL_SOURCE=$(wildcard model/*.cc)
CONTROLLER_SOURCE=$(wildcard controller/*.cc)
VIEW_SOURCE=$(wildcard view/*.cc view/*/*.cc)
GTK_FLAGS=`pkg-config --cflags --libs gtk4`
EPOXY_FLAGS=`pkg-config --cflags --libs epoxy`
MODEL_FLAGS=-ls21_model -L model


lib:
	cd model/ && make s21_model.a
	$(CC) main.cc $(GTK_FLAGS) $(EPOXY_FLAGS) $(MODEL_FLAGS)
	./a.out

clean:
	cd model/ && make clean  
