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
	pid_t pid;
	while (1) {
		from_client = server_setup();
		pid = fork();
		if (pid < 0) {
			err();
		}
		else if (pid == 0) {
			close(from_client);
			server_handshake_half(&to_client, from_client);
			while(1) {
				int randnum = randomInt() % 101;
				if (write(to_client, &randnum, sizeof(randnum)) < 0) {
					err();
				}
				sleep(1);
			}
		}
		else {
			close(from_client);
		}
	}
}
