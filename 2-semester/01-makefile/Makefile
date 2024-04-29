do: functions.out open clear

functions.out: geom.o functions.o
	gcc geom.o functions.o

geom.o: geom.c
	gcc -c geom.c

functions.o: functions.c
	gcc -c functions.c

open: functions.out
	./a.out

clear:
	rm geom.o functions.o a.out
