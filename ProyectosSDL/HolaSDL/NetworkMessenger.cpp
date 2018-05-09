#include "NetworkMessenger.h"

NetworkMessenger::NetworkMessenger() :
		conn_(nullptr), socketSet_() {
}

NetworkMessenger::~NetworkMessenger() {
}

void NetworkMessenger::receive(Message* msg) {
	conn_->sendMessage(msg);
}

void NetworkMessenger::update() {
	while (SDLNet_CheckSockets(socketSet_, 0) > 0) {
		if (conn_->ready()) {
			Message* msg = conn_->recvMessage();
			if (msg != nullptr) {
				send(msg);
			}
		}
	}
}

void NetworkMessenger::init(ClientConnection* conn) {
	conn_ = conn;
	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(socketSet_, conn_->getSocket());

}
