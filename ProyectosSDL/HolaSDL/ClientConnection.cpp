#include "ClientConnection.h"

ClientConnection::ClientConnection() :
		connected_(false), conn_(), buffer_() {
}

ClientConnection::ClientConnection(TCPsocket conn) :
		connected_(true), conn_(conn), buffer_() {
}

ClientConnection::~ClientConnection() {
	close();
}

bool ClientConnection::connect(char* host, int port) {
	if (connected_)
		close();

	// a variable that represents the address of the server we want to connect to
	IPaddress ip;

	// fill in the address address in ip
	if (SDLNet_ResolveHost(&ip, host, port) < 0) {
		return false;
	}

	conn_ = SDLNet_TCP_Open(&ip);
	if (!conn_) {
		return false;
	}

	connected_ = true;
	return true;
}

Message* ClientConnection::recvMessage() {
	if (!connected_)
		return nullptr;

	int result;

	// read the header, which indicates the message size
	int bytesRead = 0;
	while (bytesRead < sizeof(header_t_)) {
		result = SDLNet_TCP_Recv(conn_, buffer_ + bytesRead,
				sizeof(header_t_) - bytesRead);
		if (result < 1)
			return nullptr;
		else {
			bytesRead += result;
		}
	}
	header_t_ msgSize = *((header_t_*) buffer_);

	// read message
	while (bytesRead < msgSize) {
		result = SDLNet_TCP_Recv(conn_, buffer_ + bytesRead,
				msgSize - bytesRead);
		if (result < 1)
			return nullptr;
		else {
			bytesRead += result;
		}
	}

	return (Message*) buffer_;
}

bool ClientConnection::sendMessage(Message* msg) {
	if (!connected_)
		return false;

	int result = SDLNet_TCP_Send(conn_, (char*) msg, msg->size_);
	if (result != msg->size_)
		return false;

	return true;
}

bool ClientConnection::ready() {
	return connected_ && SDLNet_SocketReady(conn_);
}

TCPsocket ClientConnection::getSocket() {
	return conn_;
}

void ClientConnection::close() {
	if (connected_) {
		SDLNet_TCP_Close(conn_);
		connected_ = false;
	}
}
