target: server.o client.o
	g++ server.o -o server
	g++ client.o -o client

server.o: 
	g++ -c server.cpp

client.o:
	g++ -c client.cpp

clean: 
	rm server client *.o
