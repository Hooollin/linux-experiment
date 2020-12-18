target: test1.o
	g++ test1.o -o main
	make clean

test1.o: test1.cpp A.h
	g++ -c test1.cpp

clean: 
	rm *.o

