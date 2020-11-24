target: A.o
	g++ A.o -std=c++17
A.o: A.c
	g++ -c A.c
clean:
	rm A.o

