CC = g++
SERVER_CPP = server.cpp
CLIENT_CPP = client.cpp
SERVER_TARGET = server.exe
CLIENT_TARGET = client.exe
 
.SUFFIXES : .o
 
all : $(SERVER_TARGET) $(CLIENT_TARGET)
 
$(SERVER_TARGET): $(SERVER_CPP)
	$(CC) -W $(SERVER_CPP) -o $(SERVER_TARGET)
$(CLIENT_TARGET): $(CLIENT_CPP)
	$(CC) -W $(CLIENT_CPP) -o $(CLIENT_TARGET)
 
clean :
	rm -f *.exe
