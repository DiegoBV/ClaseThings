#pragma once

#include "sdl_includes.h"
#include "Messages.h"
#include <string>


/*
 *
 */
class ClientConnection {
public:
	ClientConnection();
	ClientConnection(TCPsocket conn);
	virtual ~ClientConnection();
	bool connect(char* host, int port);
	bool ready();
	TCPsocket getSocket();
	Message* recvMessage();
	bool sendMessage(Message* msg);
	void close();
private:
	bool connected_;
	TCPsocket conn_;
	Uint8 buffer_[MAX_MSG_SIZE];
};

