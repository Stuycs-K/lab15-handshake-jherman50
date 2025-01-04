compile: clienttemp servertemp persistenttemp
server: servertemp
	@./servers
client: clienttemp
	@./clients
persistent: persistenttemp
	./persistents
clienttemp: basic_client.o pipe_networking.o
	@gcc -o clients basic_client.o pipe_networking.o
servertemp: basic_server.o pipe_networking.o
	@gcc -o servers basic_server.o pipe_networking.o
persistenttemp: persistent_server.o pipe_networking.o
	gcc -o persistents persistent_server.o pipe_networking.o
basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c
basic_server.o: basic_server.c pipe_networking.h
	@gcc -c basic_server.c
pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c
persistent_server.o: persistent_server.c pipe_networking.h
	gcc -c persistent_server.c
clean:
	@rm *.o
	@rm *~
