CC = g++ -std=c++17
CC_FLAGS = -Wall -Werror -Wextra

a:
	$(CC)  $(CC_FLAGS) *.cc
	./a.out

leaks: a
	leaks -atExit -- ./a.out
