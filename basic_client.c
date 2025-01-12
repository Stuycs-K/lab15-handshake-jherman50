#include "pipe_networking.h"

int main() {
	int to_server;
	int from_server;
	from_server = client_handshake( &to_server );
	while (1) {
		char text[] = "im a client";
		write(to_server, text, sizeof(text));
		printf("message sent: %s\n", text);
		sleep(1);
	}
}
