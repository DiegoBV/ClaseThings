#include "Server.h"

Server::Server() :
		clients_() {

}

Server::~Server() {
}

void Server::start(int port) {

	// some types of message that we use later
	ConnectedMsg msg_connected = { 0 };
	Message* msg;

	// a variable that represents the address -- in this case only the port
	IPaddress ip;

	// fill in the address in 'ip' -- note that the 2nd parameter is 'nullptr'
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
		error();
	}

	// Since the host in 'ip' is 0 (we provided 'nullptr' above), SDLNet_TCP_Open starts
	// a server listening at the port specified in 'ip' and returns a socket for listening
	// to connection requests
	TCPsocket masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) {
		error();
	}

	// We want to use non-blocking communication, the way to do this is via a socket set.
	// We add sockets to this set and then we can ask if any socket in this has some
	// activity without blocking.
	// Non-blocking communication is the adequate one for video games!!
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1000);

	// add the masterSocket to the set
	SDLNet_TCP_AddSocket(socketSet, masterSocket);

	while (true) {
		// The call to SDLNet_CheckSockets returns the number of sockets with activity
		// in socketSet. The 2nd parameter tells the method to wait up to SDL_MAX_UINT32
		// if there is no activity -- no need to put it 0 in this case since the server
		// does not do anything else. With 0 it would consume CPU unnecessarily
		if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {

			// if there is an activity in masterSocket we process it. Note that
			// before calling SDLNet_SocketReady we must have called SDLNet_CheckSockets
			if (SDLNet_SocketReady(masterSocket)) {

				// accept the connection (activity on master socket is always a connection
				// request, sending and receiving data is done via the socket returned by
				// SDLNet_TCP_Accept. This way we can serve several clients ...
				TCPsocket client = SDLNet_TCP_Accept(masterSocket);

				// look for the first free slot in the clients array
				Uint8 j = 0;
				while (j < clients_.size() && clients_[j] != nullptr)
					j++;

				if (j >= clients_.size()) {
					clients_.resize(j + 1); // if clients array is full add some space
				}

				cout << "Client " << static_cast<int>(j) << " has connected ..."
						<< endl;

				// We keep the connection at position j, and add the socket to the
				// sockets set so we can ask for activity later ...
				clients_[j] = new ClientConnection(client);
				SDLNet_TCP_AddSocket(socketSet, client);

				// send the client her/his ID
				msg_connected.clientId_ = j;
				clients_[j]->sendMessage(&msg_connected);
			}

			// check activity from clients
			for (int i = 0; i < clients_.size(); i++) {
				if (clients_[i] != nullptr && clients_[i]->ready()) {
					// receive a message from the i-th client
					msg = clients_[i]->recvMessage();

					if (msg == nullptr) {
						// either the client closed the connection, or something went wrong,
						// we disconnect the client
						SDLNet_TCP_DelSocket(socketSet,
								clients_[i]->getSocket()); // remove it from set -- very important!!
						clients_[i]->close();
						delete clients_[i];
						clients_[i] = nullptr;
						for (int j = 0; j < clients_.size(); j++) {
							if (i != j && clients_[j] != nullptr) {
								clients_[j]->sendMessage(&PlayerDis(i)); // normally we should check for error
							}
						}
						cout << "Client " << i << " disconnected" << endl;
					} else {
						// if no error, forward the message to all clients
						for (int j = 0; j < clients_.size(); j++) {
							if (i != j && clients_[j] != nullptr) {
								clients_[j]->sendMessage(msg); // normally we should check for error
							}
						}
					}

				}
			}
		}
	}

	// close the master socket when we exit the loop
	SDLNet_TCP_Close(masterSocket);
}

void Server::error() {
	cout << "Error: " << SDLNet_GetError() << endl;
	exit(1);
}
