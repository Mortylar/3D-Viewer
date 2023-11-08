CC=g++ -std=c++17 -g
W_FLAGS=-Wall -Werror -Wextra
GTEST_FLAGS= -lgtest
COVERAGE_FLAGS = -lgcov --coverage

TARGET=../model/*.cc
EXECUTION=test

OS=`uname -s`

ifeq ($(OS),Linux)
OPEN=xdg-open
else
OPEN=open
endif

.PHONY: test coverage clean

test:
	$(CC) $(W_FLAGS) $(TARGET) test.cc $(GTEST_FLAGS) -o $(EXECUTION)
	./$(EXECUTION)

coverage:
	$(CC) $(TARGET) $(COVERAGE_FLAGS) test.cc $(GTEST_FLAGS) -o $(EXECUTION)
	./$(EXECUTION)
	lcov -t "report" -o affine.info -c -d test-affine_3d.gcda
	lcov -t "report" -o figure.info -c -d test-figure.gcda
	lcov -t "report" -o model.info -c -d test-model.gcda
	lcov -t "report" -o parser.info -c -d test-parser.gcda
	lcov -a affine.info -a figure.info -a parser.info -a model.info -o test.info
	lcov --remove test.info "/usr/include/*" -o mini_test.info
	genhtml -o report mini_test.info
	$(OPEN) report/index.html


clean:
	-rm -rf report/ *.info *.gcda *.gcno *.o $(EXECUTION)

