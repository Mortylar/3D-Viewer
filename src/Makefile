CC=g++ -std=c++17 -O3
MODEL_SOURCE=$(wildcard model/*.cc)
CONTROLLER_SOURCE=$(wildcard controller/*.cc)
VIEW_SOURCE=$(wildcard view/*.cc view/*/*.cc)
GTK_FLAGS=`pkg-config --cflags --libs gtk4`
EPOXY_FLAGS=`pkg-config --cflags --libs epoxy`
MODEL_FLAGS=-ls21_model -L model
VIEW_FLAGS=-ls21_view -L view


lib:
	cd model/ && make s21_model.a
	cd view/ && make s21_view.a
	$(CC) main.cc $(VIEW_FLAGS) $(GTK_FLAGS) $(MODEL_FLAGS) $(EPOXY_FLAGS)
	./a.out

clean:
	cd model/ && make clean  
	cd view/ && make clean
