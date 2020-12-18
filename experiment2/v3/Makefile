target: test3.o
	g++ -g test3.o -o main
	make clean
test.o: A.h B.h MOS.h
	g++ -g test3.cpp -c
clean:
	rm *.o
