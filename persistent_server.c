#include "pipe_networking.h"

static void sighand(int sig) {
	printf("server ended\n");
	remove(WKP);
	exit(0); 
}

int main() {
  int to_client;
  int from_client;
	signal(SIGINT, sighand);
	while (1) {
		from_client = server_handshake( &to_client );
		close(from_client);
		close(to_client);
	}
}
