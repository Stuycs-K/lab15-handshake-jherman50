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
  char name[15];
  snprintf(name,14, "%d", getpid());
  printf("checkpoint1\n");
  printf("name: %s\n", name);
	if (mkfifo(name, 0666) < 0 ){
		err();
	}
  from_client = open(WKP, O_RDONLY);
  printf("checkpoint2\n");
  if (from_client < 0) {
    err();
  }
  remove(WKP);
  printf("checkpoint3\n");
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
  int * output;
  int * randnum;
  *randnum = randomInt();
  from_client = open(WKP, O_RDONLY);
  printf("checkpoint4\n");
  if (from_client < 0) {
    err();
  }
  read(from_client, output, sizeof(output));
  printf("checkpoint5\n");
  remove(WKP);
  printf("checkpoint6\n");
  pid_t subserver;
  subserver = fork();
  printf("checkpoint7\n");
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
  char name[15];
  snprintf(name,14, "%d", getpid());
  printf("checkpoint8\n");
	if (mkfifo(name, 0666) < 0 ){
		err();
	}
  *to_server = open(name, O_WRONLY);
  printf("checkpoint9\n");
  from_server = open(WKP, O_RDONLY);
  printf("checkpoint10\n");
  write(from_server, name, sizeof(name));
  printf("checkpoint11\n");
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
