INPUT=input.txt

all: clean main test

main:
	gcc -Wall -Wextra -Werror -Wpedantic -I./include -o main *.c

test:
	valgrind --leak-check=yes ./main $(INPUT)

test_full:
	valgrind --leak-check=yes --track-origins=yes -s ./main $(INPUT)

clean:
	-rm main

clean_vgcore:
	-rm vgcore.*
