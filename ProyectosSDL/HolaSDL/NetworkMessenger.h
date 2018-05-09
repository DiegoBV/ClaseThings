#pragma once

#include "Observer.h"
#include "Observable.h"
#include "ClientConnection.h"


/*
 *
 */
class NetworkMessenger : public Observer, public Observable {
public:
	NetworkMessenger();
	virtual ~NetworkMessenger();
	virtual void receive(Message* msg);
	void init(ClientConnection* conn);
	void update();
private:
	ClientConnection* conn_;
	SDLNet_SocketSet socketSet_;
};

