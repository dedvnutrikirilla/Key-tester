all:
	gcc -std=c11 -Wall -Werror -Wextra -Wpedantic -ggdb3 -I ./inc/ -s ./src/*.c -o main 