#include "pipe_networking.h"
static void sighand(int sig) {
	printf("ended\n");
	remove(WKP);
	exit(0);
}

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
	printf("server setup done\n");
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
	int randnumfr;
	srand(time(NULL));
	int from_client;
	from_client = server_setup();
	if (from_client < 0) {
		printf("here line 92\n");
		err();
	}
	char name[HANDSHAKE_BUFFER_SIZE];
	if (read(from_client, name, HANDSHAKE_BUFFER_SIZE) < 0) {
		printf("here line 97\n");
		err();
	}
	printf("6 opened private pipe\n");
	*to_client = open(name, O_WRONLY);
	if (*to_client < 0) {
		printf("here line 102\n");
		err();
	}
	//randnumfr = rand() % 101;
	randnumfr = 8888888;
	int newnum;
	if (randnumfr < 0) {
		randnumfr *= -1;
	}
	if (write(*to_client, &randnumfr, 4) < 0) {
		err();
	}
	printf("7random number: %d\n", randnumfr);
	sleep(1);
	if (read(from_client, &newnum, 4) < 0) {
		err();
	}
	printf("9updated number: %d\n", newnum);
  return from_client;
}

int server_handshake_half(int *to_client, int from_client) {
	int randnumfr;
	srand(time(NULL));
	if (from_client < 0) {
		printf("here line 92\n");
		err();
	}
	char name[HANDSHAKE_BUFFER_SIZE];
	if (read(from_client, name, HANDSHAKE_BUFFER_SIZE) < 0) {
		printf("here line 97\n");
		err();
	}
	printf("6 opened private pipe\n");
	*to_client = open(name, O_WRONLY);
	if (*to_client < 0) {
		printf("here line 102\n");
		err();
	}
	//randnumfr = rand() % 101;
	randnumfr = 8888888;
	int newnum;
	if (randnumfr < 0) {
		randnumfr *= -1;
	}
	if (write(*to_client, &randnumfr, 4) < 0) {
		err();
	}
	printf("7 random number: %d\n", randnumfr);
	sleep(1);
	if (read(from_client, &newnum, 4) < 0) {
		err();
	}
	printf("9 updated number: %d\n", newnum);
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
	int pid = getpid();
	int * pidp = &pid;
	char name[HANDSHAKE_BUFFER_SIZE];
	int randnum;
	snprintf(name, HANDSHAKE_BUFFER_SIZE, "%d", pid);
	//printf("name: %s\n", name);
	if (mkfifo(name, 0666) < 0 ){
		printf("here line 148\n");
		err();
	}
	*to_server = open(WKP, O_WRONLY, 0666);
	if (*to_server < 0) {
		printf("here line 153\n");
		err();
	}
	int servertemp = *to_server;
	if (write(servertemp, name, HANDSHAKE_BUFFER_SIZE) < 0) {
		printf("here line 157\n");
		err();
	}
	from_server = open(name, O_RDONLY, 0666);
	if (from_server < 0) {
		printf("here line 162\n");
		err();
	}
	remove(name);
	if (read(from_server, &randnum, 4) < 0) {
		printf("here line 166\n");
		err();
	}
	printf("random number: %d\n", randnum);
	randnum += 1;
	if (write(servertemp, &randnum, 4) < 0) {
		printf("here line 173\n");
		err();
	}
	printf("updated number: %d\n", randnum);
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
