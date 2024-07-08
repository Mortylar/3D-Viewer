CC = g++ -std=c++17 -O3
CFLAGS = -Wall -Werror -Wextra
GTK_FLAGS = `pkg-config --libs --cflags gtk4`
EPOXY_FLAGS = `pkg-config --libs --cflags epoxy`
SOURCE=$(wildcard *.cc)
TEST_DIR=../test/

s21_model.a:
	$(CC) -c $(SOURCE) $(GTK_FLAGS) $(EPOXY_FLAGS)
	ar rcs libs21_model.a *.o
	ranlib libs21_model.a

test:
	cd $(TEST_DIR) && make test

coverage:
	cd $(TEST_DIR) && make coverage

leaks: 
	cd $(TEST_DIR) && make leaks

valgrind:
	cd $(TEST_DIR) && make valgrind

clean:
	cd $(TEST_DIR) && make clean
	-rm *.o libs21_model.a
