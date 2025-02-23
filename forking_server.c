#include "pipe_networking.h"
static void sighand(int sig) {
	printf("server ended\n");
	remove(WKP);
	exit(0);
}
static int counter;

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
			//printf("i am child %d\n", counter++);
			server_handshake_half(&to_client, from_client);
			while(1) {
				char text[256];
				read(from_client, text, sizeof(text));
				printf("message received: %s\n", text);
				sleep(1);
			}
		}
		else {
			close(from_client);
			close(to_client);
		}
	}
}
