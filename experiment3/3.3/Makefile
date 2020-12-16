target: client.o server.o
	g++ client.o -o client -std=c++17
	g++ server.o -o server -std=c++17

client.o:
	g++ -c client.cpp -std=c++17

server.o:
	g++ -c server.cpp -std=c++17

clean:
	rm *.o client server
