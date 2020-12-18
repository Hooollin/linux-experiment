target: test2.o
	g++ test2.o -g -o main
	make clean

test2.o: A.h As.h
	g++ -c test2.cpp -g
clean:
	rm *.o *.out
