do: interpol.out open clear

interpol.out: interpol.o interfuns.o
	g++ interpol.o interfuns.o

interpol.o: interpol.cpp
	g++ -c interpol.cpp

interfuns.o: interfuns.cpp
	g++ -c interfuns.cpp

open: interpol.out
	./a.out

clear:
	rm interpol.o interfuns.o a.out
