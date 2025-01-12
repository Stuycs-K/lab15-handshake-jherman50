#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
	char message[256];
	read(from_client, message, sizeof(message));
	printf("server received: %s\n", message);
}
