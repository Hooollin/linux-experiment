target: test4.o
	g++ test4.o -std=c++11 -o main
test4.o: A.h B.h ILSerializable.h ILSerializer.h
	g++ -c test4.cpp -std=c++11
clean:
	rm *.o
