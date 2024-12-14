CC=g++ -std=c++17 -g
EPOXY_FLAGS=`pkg-config --libs --cflags epoxy`
GTEST_FLAGS= -lgtest
COVERAGE_FLAGS = -lgcov --coverage

TARGET=../model/matrix_4f.cc ../model/affine_3d.cc ../model/figure.cc ../model/parser.cc
TEST=matrix4f_test.cc affine_test.cc figure_test.cc parser_test.cc
EXECUTION=test

OS=$(shell uname -s)

ifeq ($(OS),Linux)
OPEN=xdg-open
else
OPEN=open
endif

.PHONY: test coverage clean

test:
	$(CC) $(TARGET) $(TEST) test.cc $(GTEST_FLAGS) -o $(EXECUTION)
	./$(EXECUTION)

coverage:
	$(CC) $(TARGET) $(TEST) $(COVERAGE_FLAGS) test.cc $(GTEST_FLAGS) -o $(EXECUTION)
	rm -rf test.dSYM/
	./$(EXECUTION)
	lcov -t "report" -o affine.info -c -d test-affine_3d.gcda
	lcov -t "report" -o figure.info -c -d test-figure.gcda
	lcov -t "report" -o parser.info -c -d test-parser.gcda
	lcov -t "report" -o matrix.info -c -d test-matrix_4f.gcda

	lcov -a matrix.info  -a affine.info -a figure.info -a parser.info -o test.info
	lcov --remove test.info "/usr/include/*" "/Library/*" "/usr/local/*" "/opt/goinfree/*" --ignore-errors unused -o mini_test.info
	genhtml -o report mini_test.info
	$(OPEN) report/index.html

leaks: test
	leaks -atExit -- ./test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all -s ./test

clean:
	-rm -rf report/ test.dSYM/ *.info *.gcda *.gcno *.o $(EXECUTION)
	-rm -rf *.dSYM/ report/ *.info *.gcda *.gcno *.o $(EXECUTION)

