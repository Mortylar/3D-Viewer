CC=g++ -std=c++17 -O3

GTK_FLAGS=`pkg-config --cflags --libs gtk4`
EPOXY_FLAGS=`pkg-config --cflags --libs epoxy`

MODEL_FLAGS=-ls21_model -L model
VIEW_FLAGS=-ls21_view -L view


MODEL_SOURCE=$(wildcard model/*.cc)
CONTROLLER_SOURCE=$(wildcard controller/*.cc)
VIEW_SOURCE=$(wildcard view/*.cc view/*/*.cc)
SOURCE=$(MODEL_SOURCE) $(VIEW_SOURCE) $(CONTROLLER_SOURCE)

MODEL_HEADERS=$(wildcard model/*.h)
CONTROLLER_HEADERS=$(wildcard controller/*.h)
VIEW_HEADERS=$(wildcard view/*.h view/*/*.h)
HEADERS=$(VIEW_HEADERS) $(MODEL_HEADERS) $(CONTROLLER_HEADERS)

LIBS=$(libs/*.h libs/*.cc)

FULL_SOURCE=$(SOURCE) $(HEADERS) $(LIBS)
TEST_FILES=$(wildcard test/*.cc test/*.h)


DIST_NAME=3D_Viewer-2.0.tar.gz

BUILD_DIR=~/3D_Viewer
TARGET_NAME=3D_Viewer

all: gcov_report leaks install open

install: build
	-rm -r $(BUILD_DIR)
	-mkdir $(BUILD_DIR)
	mv $(TARGET_NAME) $(BUILD_DIR)
	cp -r glarea $(BUILD_DIR)

uninstall: clean
	-rm -r $(BUILD_DIR)

build: libs21_model.a libs21_view.a
	$(CC) main.cc $(VIEW_FLAGS) $(GTK_FLAGS) $(MODEL_FLAGS) $(EPOXY_FLAGS) -o $(TARGET_NAME)

rebuild: clean build

open:
	$(BUILD_DIR)/$(TARGET_NAME)


tests:
	cd test/ && make test

gcov_report:
	cd test/ && make coverage

valgrind:
	cd test/ && make valgrind

leaks:
	cd test/ && make leaks

dvi:
	cd report/ && make dvi

pdf:
	cd report/ && make pdf

open_report:
	cd report/ && make open

dist:
	tar -czf $(DIST_NAME) .

dist_clean:
	-rm $(DIST_NAME)

clean:
	cd model/ && make clean  
	cd view/ && make clean
	cd test/ && make clean
	cd report/ && make clean
	-rm $(TARGET_NAME) .3D_conf

libs21_model.a:
	cd model/ && make libs21_model.a

libs21_view.a:
	cd view/ && make libs21_view.a

style:
	clang-format -n --style=google $(FULL_SOURCE) $(TEST_FILES) main.cc

fix_style:
	clang-format -i --style=google $(FULL_SOURCE) $(TEST_FILES) main.cc

cppcheck:
	cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem main.cc $(FULL_SOURCE) $(TEST_FILES)

add: fix_style
	git add $(shell find . -name "*.cc") $(shell find . -name "*.h")	

