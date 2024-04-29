do: main.out open clear

interpol.out: main.o interfuns.o
	gcc main.o interfuns.o

main.o: main.c
	gcc -c main.c

interfuns.o: interfuns.c
	gcc -c interfuns.c

open: main.out
	./a.out

clear:
	rm main.o interfuns.o a.out
