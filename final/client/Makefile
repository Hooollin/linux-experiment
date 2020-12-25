target client: client.o
	g++ client.o -o client
client.o: ../common/Command.h
	g++  -c client.cpp
.PHONY: run clean
clean:
	rm *.o
run: 
	./client
