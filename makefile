all: server client

server: Chat.cpp Server.cpp
	g++ -I. -pthread Chat.cpp Server.cpp -lIce -lIceUtil -o server

client: Chat.cpp Client.cpp
	g++ -I. -pthread Chat.cpp Client.cpp -lIce -lIceUtil -o client

Chat.cpp: Chat.ice
	slice2cpp Chat.ice
	
slice: Chat.ice
	rm -f ChatI.cpp ChatI.h
	slice2cpp --impl Chat.ice

clean:
	rm -f Chat.h Chat.cpp client server ChatI.cpp ChatI.h
