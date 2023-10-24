CC = g++ -std=c++17
CC_FLAGS = -Wall -Werror -Wextra

a:
	$(CC)  $(CC_FLAGS) main.cc affine_3d.cc figure.cc
	./a.out

p:
	$(CC) $(CC_FLAGS) test.cc

leaks: a
	leaks -atExit -- ./a.out
