CC=g++ -std=c++17 -g
GTK_FLAGS=`pkg-config --libs --cflags gtk4`
EPOXY_FLAGS=`pkg-config --libs --cflags epoxy`
GTEST_FLAGS= -lgtest
COVERAGE_FLAGS = -lgcov --coverage

TARGET=../model/*.cc
EXECUTION=test

OS=$(shell uname -s)

ifeq ($(OS),Linux)
OPEN=xdg-open
else
OPEN=open
endif

.PHONY: test coverage clean

test:
	$(CC) $(W_FLAGS) $(GTK_FLAGS) $(EPOXY_FLAGS) $(TARGET) test.cc $(GTEST_FLAGS) $(EPOXY_FLAGS) $(GTK_FLAGS) -o $(EXECUTION)
	./$(EXECUTION)

coverage:
	echo $(OS)
	$(CC) $(GTK_FLAGS) $(EPOXY_FLAGS) $(TARGET) $(COVERAGE_FLAGS) test.cc $(GTEST_FLAGS) $(EPOXY_FLAGS) $(GTK_FLAGS) -o $(EXECUTION)
	rm -rf test.dSYM/
	./$(EXECUTION)
#ifeq ($(OS),Darwin)
	lcov -t "report" -o affine.info -c -d test-affine_3d.gcda
	lcov -t "report" -o figure.info -c -d test-figure.gcda
	lcov -t "report" -o model.info -c -d test-model.gcda
	lcov -t "report" -o parser.info -c -d test-parser.gcda
	lcov -t "report" -o matrix_4f.info -c -d test-matrix_4f.gcda

#else
#	lcov -t "report" -o affine.info -c -d affine_3d.gcda
#	lcov -t "report" -o figure.info -c -d figure.gcda
#	lcov -t "report" -o model.info -c -d model.gcda
#	lcov -t "report" -o parser.info -c -d parser.gcda
#	lcov -t "report" -o matrix_4f.info -c -d matrix_4f.gcda

#endif	
	lcov -a affine.info -a figure.info -a matrix_4f.info -a parser.info -a model.info -o test.info
	lcov --remove test.info "/usr/include/*" "/Library/*" "/usr/local/*" "/opt/goinfree/*" "stb/*" --ignore-errors unused -o mini_test.info
	genhtml -o report mini_test.info
	$(OPEN) report/index.html

leaks: test
	leaks -atExit -- ./test

valgrind: test
	valgrind test
clean:
	-rm -rf report/ test.dSYM/ *.info *.gcda *.gcno *.o $(EXECUTION)
	-rm -rf *.dSYM/ report/ *.info *.gcda *.gcno *.o $(EXECUTION)

