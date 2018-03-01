#include "ExampleGame.h"
#include "DemoActor.h"
#include "Collisions.h"
#include "PaddleKeyboardComponent.h"
#include "PaddlePhysicsComponent.h"
#include "FillRectRenderer.h"
#include "PaddleMouseInputComponent.h"
#include "PaddleAIPhysics.h"
#include "TranRectRenderer.h"
#include "BounceOnBordersPhysics.h"
#include "ImageRenderer.h"
#include "AccelerationInputComponent.h"
#include "StarWarsBulletsManager.h"
#include "Weapon.h"
#include "Asteroid.h"

ExampleGame::ExampleGame() :
		SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
	running_ = false;
	leftScore_ = 0;
	rightScore_ = 0;
}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {

	// hide cursor
	SDL_Rect rect = { 47, 90, 207, 247 };
	SDL_ShowCursor(0);
	Vector2D dirPrub;
	dirPrub.setX(0);
	dirPrub.setY(1);
	Vector2D velPrub;
	velPrub.setX(-1);
	velPrub.setY(-2);


	caza_ = new Container(this);
	caza_->setDirection(dirPrub);
	caza_->setWidth(30);
	caza_->setHeight(30);
	caza_->setPosition(Vector2D(getWindowWidth() / 2 - 6, getWindowHeight() / 2 - 6));
	caza_->setVelocity(velPrub);


	StarWarsBulletsManager* stw = new StarWarsBulletsManager(this);

	/*ball_ = new Container(this);
	ball_->setWidth(11);
	ball_->setHeight(11);
	ball_->setPosition(
			Vector2D(getWindowWidth() / 2 - 6, getWindowHeight() / 2 - 6));

	leftPaddle_ = new Container(this);
	leftPaddle_->setWidth(10);
	leftPaddle_->setHeight(50);
	leftPaddle_->setPosition(Vector2D(5, getWindowHeight() / 2 - 25));

	rightPaddle_ = new Container(this);
	rightPaddle_->setWidth(10);
	rightPaddle_->setHeight(50);
	rightPaddle_->setPosition(
			Vector2D(getWindowWidth() - 15, getWindowHeight() / 2 - 25));

	keyboardIC1_ = new PaddleKeyboardComponent(SDLK_UP, SDLK_DOWN, SDLK_SPACE);
	keyboardIC2_ = new PaddleKeyboardComponent(SDLK_a, SDLK_z, SDLK_s);
	mouseIC1_ = new PaddleMouseInputComponent();*/
	rotater = new RotationComponent(5, SDLK_RIGHT, SDLK_LEFT);
	accelerationComp = new AccelerationInputComponent(SDLK_UP, SDLK_DOWN, 0.75, 0.5, 20);
	InputComponent* gunInput = new Weapon(stw, SDLK_SPACE, 1, 15);

	/*paddlePC_ = new PaddlePhysicsComponent();
	paddleAIPC_ = new PaddleAIPhysics(ball_);
	bouncePC_ = new BounceOnBordersPhysics(false,false,true,true);*/
	circular_ = new CircularMotionPhysics();

	fillrectRC_ = new FillRectRenderer();
	transrectRC_ = new TranRectRenderer();
	/*tennisballRC_ = new ImageRenderer( getResources()->getImageTexture(Resources::TennisBall));
	keyIconRC_ = new ImageRenderer( getResources()->getImageTexture(Resources::KeyBoardIcon));
	mouseIconRC_ = new ImageRenderer( getResources()->getImageTexture(Resources::MouseIcon));
	aiIconRC_ = new ImageRenderer( getResources()->getImageTexture(Resources::AIIcon));*/
	caza2_ = new ImageRenderer(getResources()->getImageTexture(Resources::Airplanes), rect);

	/*cs1_ = new ComponentSwitcher(this,leftPaddle_,SDLK_1);
	cs1_->setPosition(Vector2D(5,5));
	cs1_->setWidth(50);
	cs1_->setHeight(50);

	cs2_ = new ComponentSwitcher(this,rightPaddle_,SDLK_2);
	cs2_->setPosition(Vector2D(getWindowWidth()-55,5));
	cs2_->setWidth(50);
	cs2_->setHeight(50);

	cs1_->addMode( { keyboardIC1_, paddlePC_, fillrectRC_, keyIconRC_} );
	cs1_->addMode( { mouseIC1_, paddlePC_, fillrectRC_, mouseIconRC_} );
	cs1_->addMode( { nullptr, paddleAIPC_, transrectRC_, aiIconRC_} );

	cs2_->addMode( { keyboardIC2_, paddlePC_, fillrectRC_, keyIconRC_} );
	cs2_->addMode( { mouseIC1_, paddlePC_, fillrectRC_, mouseIconRC_} );
	cs2_->addMode( { nullptr, paddleAIPC_, transrectRC_, aiIconRC_} );



	ball_->addPhysicsComponent(bouncePC_);
	ball_->addRenderComponent(tennisballRC_);*/
	caza_->addRenderComponent(caza2_);
	caza_->addInputComponent(rotater);
	caza_->addPhysicsComponent(circular_);
	caza_->addInputComponent(accelerationComp);
	caza_->addInputComponent(gunInput);

	//cs1_->setMode(0);
	//cs2_->setMode(0);

	/*actors_.push_back(cs1_);
	actors_.push_back(cs2_);
	actors_.push_back(leftPaddle_);
	actors_.push_back(rightPaddle_);
	actors_.push_back(ball_);*/
	actors_.push_back(caza_);
	actors_.push_back(stw);
	actors_.push_back(new Asteroid(this, Vector2D(0.25, 0.25)));
	actors_.push_back(new Asteroid(this, Vector2D(0.25, 0.35)));
	actors_.push_back(new Asteroid(this, Vector2D(0.5, 0.25)));
}

void ExampleGame::closeGame() {
	if (ball_ != nullptr)
		delete ball_;
	if (leftPaddle_ != nullptr)
		delete leftPaddle_;
	if (rightPaddle_ != nullptr)
		delete rightPaddle_;
	if (caza_ != nullptr)
		delete caza_;
}

void ExampleGame::start() {
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();
		handleInput(startTime);
		update(startTime);

		// check for collision of ball with paddles
		/*if (Collisions::collides(ball_, leftPaddle_)
				|| Collisions::collides(ball_, rightPaddle_)) {
			Vector2D v = ball_->getVelocity();
			v.setX(-v.getX());
			ball_->setVelocity(v * 1.2);
			getResources()->getSoundEffect(Resources::Paddle_Hit)->play(0);
		}

		// check if the back exit from sides
		if (ball_->getPosition().getX() <= 0) {
			rightScore_++;
			running_ = false;
			ball_->setVelocity(Vector2D(0, 0));
			ball_->setPosition(
					Vector2D(getWindowWidth() / 2 - 6,
							getWindowHeight() / 2 - 6));

		} else if (ball_->getPosition().getX() - ball_->getWidth()
				>= getWindowWidth()) {
			leftScore_++;
			running_ = false;
			ball_->setPosition(
					Vector2D(getWindowWidth() / 2 - 6,
							getWindowHeight() / 2 - 6));
			ball_->setVelocity(Vector2D(0, 0));
		}*/
		render(startTime);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void ExampleGame::stop() {
	exit_ = true;
}

void ExampleGame::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		/*if (event.type == SDL_KEYDOWN) {

			// if any key pressed while not running, we choose a random velocity of the ball
			/*if (!running_) {
				running_ = true;
				int dx = 1 - 2 * (rand() % 2); // 1 or -1
				int dy = 1 - 2 * (rand() % 2); // 1 or -1
				Vector2D v(dx * ((rand() % 5) + 2), dy * ((rand() % 5) + 2));
				v.normalize();
				ball_->setVelocity(v * 2);

				// rest the score if the game is over
				if (leftScore_ == 5 || rightScore_ == 5) {
					leftScore_ = 0;
					rightScore_ = 0;
				}
			}

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
		}*/     
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void ExampleGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void ExampleGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(getRenderer());

	// draw score
	Texture score(getRenderer(),
			std::to_string(leftScore_) + " - " + std::to_string(rightScore_),
			*(getResources()->getFont(Resources::ARIAL24)),
			{ COLOR(0x111122ff) });
	score.render(getRenderer(), getWindowWidth() / 2 - score.getWidth() / 2,
			10);

	// press any key message when game is not running
	if (!running_) {
		Texture* hitanykey = getResources()->getTextTexture(
				Resources::PresAnyKey);
		hitanykey->render(getRenderer(),
				getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				getWindowHeight() - hitanykey->getHeight() - 50);
	}

	// game over message when game is over
	if (leftScore_ == 5 || rightScore_ == 5) {
		Texture* gameOver = getResources()->getTextTexture(Resources::GameOver);
		gameOver->render(getRenderer(),
				getWindowWidth() / 2 - gameOver->getWidth() / 2,
				getWindowHeight() - gameOver->getHeight() - 150);
	}

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

