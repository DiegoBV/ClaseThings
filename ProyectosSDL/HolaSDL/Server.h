#pragma once

#include <iostream>
#include "Messages.h"
#include "sdl_includes.h"
#include "ClientConnection.h"
#include <vector>

using namespace std;

/*
 *
 */
class Server {
public:
	Server();
	virtual ~Server();
	void start(int port);
private:
	void error();
	vector<ClientConnection*> clients_;
};

