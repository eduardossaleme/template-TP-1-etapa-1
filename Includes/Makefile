all: geraos principal

principal:
	gcc *.o -Wall -Wextra -o main

geraos: main.c tMapa.c tJogo.c
	gcc -c *.c

clean:
	rm -rf *.o main
