CC = g++
SERVER_OBJS = server.o
CLIENT_OBJS = client.o 
SERVER_TARGET = client
CLIENT_TARGET = server
 
.SUFFIXES : .c .o
 
all : $(SERVER_TARGET) $(CLIENT_TARGET)
 
$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) -o $@ $(SERVER_OBJS)
$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CC) -o $@ $(CLIENT_OBJS)
 
clean :
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
