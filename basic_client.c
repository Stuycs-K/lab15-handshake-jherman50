#include "pipe_networking.h"

static void sighand(int sig) {
	printf("server ended\n");
	remove(WKP);
	exit(0);
}

int main() {
	signal(SIGINT, sighand);
	int to_server;
	int from_server;
	while (1) {
		from_server = client_handshake( &to_server );
		close(from_server);
		close(to_server);
		sleep(1);
	}
}
