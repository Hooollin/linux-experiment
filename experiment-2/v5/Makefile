target: test5.o
	g++ test5.o -std=c++11
test5.o: A.h B.h ILSerializable.h ILSerializer.h
	g++ -c test5.cpp -std=c++11
clean:
	rm *.o *.out
