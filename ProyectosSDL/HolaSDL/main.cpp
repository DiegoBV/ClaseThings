#include "AsteroidsGame.h"
#include "Server.h"

using namespace std;

void server(int port) {
	Server server;
	server.start(port);
}

void client(char* host, int port) {
	AsteroidsGame g(host, port);
	g.start();
}


int main(int argc, char** argv) {

	if (SDLNet_Init() < 0) {
		cout << "Error: " << SDLNet_GetError() << endl;
		exit(1);
	}

	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(atoi(argv[2])); // start in server mode
	} else if (argc == 4 && strcmp(argv[1], "client") == 0) {
		client(argv[2], atoi(argv[3])); // start in client mode
	} else {
		cout << "Usage: " << endl;
		cout << "  " << argv[0] << " client player-name host port " << endl;
		cout << "  " << argv[0] << " server port " << endl;
		cout << endl;
		cout << "Example:" << endl;
		cout << "  " << argv[0] << " server 2000" << endl;
		cout << "  " << argv[0] << " client bart localhost 2000" << endl;
	}

	// finalize SDLNet
	SDLNet_Quit();

	return 0;
}
