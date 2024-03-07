CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra
SOURCE=$(wildcard *.cc)
TEST_DIR=../test/

s21_model.a:
	$(CC) -c $(SOURCE)
	ar rcs s21_model.a *.o
	ranlib s21_model.a

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
	-rm *.o s21_model.a
