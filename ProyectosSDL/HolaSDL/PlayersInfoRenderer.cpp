#include "PlayersInfoRenderer.h"

#include "GameManager.h"

PlayersInfoRenderer::PlayersInfoRenderer() {
}

PlayersInfoRenderer::~PlayersInfoRenderer() {
}

void PlayersInfoRenderer::render(GameObject* o, Uint32 time) {

	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game_ = gm->getGame();

	Texture msg_;

	int y = 5;
	for (GameManager::PlayerInfo & p : gm->getPlayereInfo()) {
		if (p.connected_) {
			msg_.loadFromText(game_->getRenderer(), "Player "+std::to_string(p.id_)+": "+(p.alive_ ? "alive" : "dead"),
					*(game_->getResources()->getFont(Resources::ARIAL16)), {
							COLOR(0xffffbbff) });
			msg_.render(game_->getRenderer(), 10, y);
			y += 20;
		}
	}

}

