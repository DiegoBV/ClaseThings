#ifndef SRC_NETWORKMESSANGER_H_
#define SRC_NETWORKMESSANGER_H_

#include "Observer.h"
#include "Observable.h"
#include "ClientConnection.h"


/*
 *
 */
class NetworkMessanger : public Observer, public Observable {
public:
	NetworkMessanger();
	virtual ~NetworkMessanger();
	virtual void receive(Message* msg);
	void init(ClientConnection* conn);
	void update();
private:
	ClientConnection* conn_;
	SDLNet_SocketSet socketSet_;
};

#endif /* SRC_NETWORKMESSANGER_H_ */
