#ifndef SRC_MESSAGES_H_
#define SRC_MESSAGES_H_

enum MessageId { BALL_TOUCHES_WALL, BALL_TOUCHES_PADDLE, ROUND_START, ROUND_END, BALL_LEAVES_RIGHT, BALL_LEAVES_LEFT };

struct Message {
	Message(MessageId id) : id_(id) {
	}
	MessageId id_;
};


#endif /* SRC_MESSAGES_H_ */
