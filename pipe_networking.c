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
	char pp[HANDSHAKE_BUFFER_SIZE];
	if (mkfifo(WKP, 0666) < 0 ){
		printf("here line 32\n");
		err();
	}
  from_client = open(WKP, O_RDONLY);
  if (from_client < 0) {
		printf("here line 37\n");
    err();
  }
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
  int from_client;
	char pp[HANDSHAKE_BUFFER_SIZE];
	char randnum[HANDSHAKE_BUFFER_SIZE];
	int randnumfr;
  randnumfr = randomInt();
	from_client = server_setup();
	if (from_client < 0) {
		printf("here line 58\n");
		err();
	}
	char name[HANDSHAKE_BUFFER_SIZE];
	char name1[HANDSHAKE_BUFFER_SIZE];
	if (read(from_client, name, HANDSHAKE_BUFFER_SIZE) < 0) {
		printf("here line 63\n");
		err();
	}
	*to_client = open(name, O_RDWR);
	if (*to_client < 0) {
		printf("here line 68\n");
		err();
	}
	write(*to_client, &randnumfr, 4);
	printf("random number: %d\n", randnumfr);
	from_client = open(name, O_RDONLY);
	read(from_client, &randnumfr, 4);
	printf("updated number: %d\n", randnumfr);
	remove(name);
  return *to_client;
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
	if (from_server < 0) {
		printf("here line 93\n");
		err();
	}
	int pid = getpid();
	int * pidp = &pid;
	char name[HANDSHAKE_BUFFER_SIZE];
	int randnum;
	snprintf(name, HANDSHAKE_BUFFER_SIZE, "%d", pid);
	printf("name: %s\n", name);
	if (mkfifo(name, 0666) < 0 ){
		printf("here line 103\n");
		err();
	}
	*to_server = open(name, O_RDWR);
	if (*to_server < 0) {
		printf("here line 108\n");
		err();
	}
	write(from_server, name, HANDSHAKE_BUFFER_SIZE);
  //*to_server = open(name, O_RDONLY);
	read(*to_server, &randnum, 4);
	printf("random number: %d\n", randnum);
  randnum += 1;
	write(*to_server, &randnum, 4);
  return *to_server;
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
