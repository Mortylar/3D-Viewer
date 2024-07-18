CC=g++ -std=c++17 -O3

MODEL_SOURCE=$(wildcard model/*.cc)
CONTROLLER_SOURCE=$(wildcard controller/*.cc)
VIEW_SOURCE=$(wildcard view/*.cc view/*/*.cc)

GTK_FLAGS=`pkg-config --cflags --libs gtk4`
EPOXY_FLAGS=`pkg-config --cflags --libs epoxy`

MODEL_FLAGS=-ls21_model -L model
VIEW_FLAGS=-ls21_view -L view

BUILD_DIR=~/3D_Viewer
TARGET_NAME=3D_Viewer

build: libs21_model.a libs21_view.a
	-mkdir $(BUILD_DIR)
	#-mkdir $(BUILD_DIR)/glarea/
	$(CC) main.cc $(VIEW_FLAGS) $(GTK_FLAGS) $(MODEL_FLAGS) $(EPOXY_FLAGS) -o $(TARGET_NAME)
	mv $(TARGET_NAME) $(BUILD_DIR)
	cp -r glarea $(BUILD_DIR)


clean:
	cd model/ && make clean  
	cd view/ && make clean

libs21_model.a:
	cd model/ && make libs21_model.a

libs21_view.a:
	cd view/ && make libs21_view.a
