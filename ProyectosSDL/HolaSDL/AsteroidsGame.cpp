#include "AsteroidsGame.h"
#include "FightersManager.h"

AsteroidsGame::AsteroidsGame(char* host, int port) :
		SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_), //
		host_(host), //
		port_(port), //
		networkMessenger_(), //
		gameManager_(this), //
		bulletsManager_(this), //
		fightersManager_(this, &networkMessenger_, &bulletsManager_), //
		asteroidsManager_(this), //
		collisionManager_(this, &bulletsManager_, &fightersManager_,
				&asteroidsManager_) //
{
	exit_ = false;
	initGame();
}

AsteroidsGame::~AsteroidsGame() {
	closeGame();
}

void AsteroidsGame::initGame() {

	// hide cursor
	SDL_ShowCursor(0);

	// connect to server
	if (!conn_.connect(host_, port_)) {
		cout << "Error: " << SDLNet_GetError() << endl;
		exit(1);
	}

	// get your client id
	Message *msg = conn_.recvMessage();
	client_id = static_cast<ConnectedMsg*>(msg)->clientId_;
	cout << "Connected with ID : " << (int) client_id << endl;

	/** TODO
	 *
	 *  Add the asteroidsManager_ to the game
	 *
	 **/

	gameManager_.registerObserver(&asteroidsManager_); //registramos como observer del gm el asteroidsManager

	gameManager_.registerObserver(&networkMessenger_);
	gameManager_.registerObserver(&fightersManager_);
	gameManager_.registerObserver(&bulletsManager_);

	asteroidsManager_.registerObserver(&gameManager_);

	networkMessenger_.registerObserver(&gameManager_);
	networkMessenger_.registerObserver(&fightersManager_);
	networkMessenger_.registerObserver(&bulletsManager_);

	fightersManager_.registerObserver(&networkMessenger_);

	collisionManager_.registerObserver(&networkMessenger_);
	collisionManager_.registerObserver(&fightersManager_);
	collisionManager_.registerObserver(&bulletsManager_);
	collisionManager_.registerObserver(&gameManager_);

	networkMessenger_.init(&getConnection());
	gameManager_.init();

	actors_.push_back(&gameManager_);
	actors_.push_back(&asteroidsManager_); //añadimos el asteroids Manager
	actors_.push_back(&fightersManager_);
	actors_.push_back(&bulletsManager_);
	actors_.push_back(&collisionManager_); // should be last to check collision at the end

}

void AsteroidsGame::closeGame() {
}

void AsteroidsGame::start() {
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();
		networkMessenger_.update(); // poll all messages from network
		handleInput(startTime);
		update(startTime);
		render(startTime);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void AsteroidsGame::stop() {
	exit_ = true;
}

void AsteroidsGame::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				} else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void AsteroidsGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void AsteroidsGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

