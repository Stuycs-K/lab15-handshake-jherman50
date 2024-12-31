#include "pipe_networking.h"
int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}
int randomInt() {
    int randfile;
    int randint;
    randfile = open("/dev/random", O_RDONLY, 0);
    if(randfile == -1) {
        err();
    }
    read(randfile, &randint, 4);
    //printf("randint: %d\n", *randint);
    return randint;
}
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
	int * pp;
	if (mkfifo(WKP, 0666) < 0 ){
		err();
	}
  from_client = open(WKP, O_RDONLY, 0666);
  if (from_client < 0) {
    err();
  }
	if (read(from_client, pp, 4) < 0) {
		err();
	}
	printf("pp: %d\n", *pp);
	remove(WKP);
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
	server_setup();
  int from_client;
	from_client = 0;
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
	from_server = open(WKP, O_WRONLY, 0666);
	int pid = getpid();
	int * pidp = &pid;
	write(from_server, pidp, 4);
	from_server = 0;
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
