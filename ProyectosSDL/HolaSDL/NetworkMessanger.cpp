#include "NetworkMessanger.h"

NetworkMessanger::NetworkMessanger() :
		conn_(nullptr), socketSet_() {
}

NetworkMessanger::~NetworkMessanger() {
}

void NetworkMessanger::receive(Message* msg) {
	conn_->sendMessage(msg);
}

void NetworkMessanger::update() {
	while (SDLNet_CheckSockets(socketSet_, 0) > 0) {
		if (conn_->ready()) {
			Message* msg = conn_->recvMessage();
			if (msg != nullptr) {
				send(msg);
			}
		}
	}
}

void NetworkMessanger::init(ClientConnection* conn) {
	conn_ = conn;
	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(socketSet_, conn_->getSocket());

}
