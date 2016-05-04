.PHONY: all
all: server client

server_obj = server.o myerror.o unp.o

server:$(server_obj)
	gcc  $(server_obj) -o server

server.o: unp.h

client_obj = client.o myerror.o unp.o

client:$(client_obj)
	gcc $(client_obj) -o client

clinet.o: unp.h

myerror.o: myerror.h

unp.o: unp.h

.PHONY: clean
clean:
	rm -f *.o
	-rm server client
