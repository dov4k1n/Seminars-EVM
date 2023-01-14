do: functions.out open clear

functions.out: geom.o functions.o
	g++ geom.o functions.o

geom.o: geom.cpp
	g++ -c geom.cpp

functions.o: functions.cpp
	g++ -c functions.cpp

open: functions.out
	./a.out

clear:
	rm geom.o functions.o a.out
