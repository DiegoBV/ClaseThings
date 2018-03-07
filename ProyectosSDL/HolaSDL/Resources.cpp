#include "SDLGame.h"
#include <tuple>
#include "Resources.h"

std::vector<std::string> Resources::imageFiles_ { "images/blank.png",
		"images/tennis_ball.png", "images/keyboard.png", "images/mouse.png",
		"images/ai.png", "images/spaceships.png", "images/airplanes.png",
		"images/star.png" };

std::vector<Resources::FontInfo> Resources::fontFiles_ {
		{ "fonts/ARIAL.ttf", 16 }, { "fonts/ARIAL.ttf", 24 }, {
				"fonts/NES-Chimera.ttf", 16 }, { "fonts/NES-Chimera.ttf", 24 },
		{ "fonts/Capture_it.ttf", 16 }, { "fonts/Capture_it.ttf", 24 } };

std::vector<Resources::TextMsgInfo> Resources::textMsgs_ { { "Hello World", {
		COLOR(0xaaffffff) }, Resources::ARIAL16 }, { "Press Any Key ...", {
		COLOR(0xaaffbbff) }, Resources::ARIAL24 }, { "Game Over", { COLOR(
		0xffffbbff) }, Resources::ARIAL24 } };

std::vector<std::string> Resources::musicFiles_ { "sound/beat.wav",
		"sound/cheer.wav", "sound/boooo.wav" };

std::vector<std::string> Resources::soundEffectFiles_ { "sound/wall_hit.wav",
		"sound/paddle_hit.wav" };

#include <iostream>

Resources::Resources(SDLGame* game) :
		game_(game), numOfImageTextures_(0), imageTextures_(nullptr), numOfTextTextures_(
				0), textTextures_(nullptr), numOfFonts_(0), fonts_(nullptr), numOfMusic_(
				0), music_(nullptr), numOfSoundEffects_(0), soundEffects_(
				nullptr) {

	setFonts(fontFiles_);
	setMusic(musicFiles_);
	setSoundEffects(soundEffectFiles_);
	setImageTextures(imageFiles_);
	setTextTextures(textMsgs_);
}

Resources::~Resources() {
	closeImageTextures();
	closeFonts();
	closeMusic();
	closeSoundEffects();
}

void Resources::setImageTextures(std::vector<std::string> textures) {
	closeImageTextures();
	numOfImageTextures_ = textures.size();
	imageTextures_ = new Texture*[numOfImageTextures_];
	for (int i = 0; i < numOfImageTextures_; i++) {
		imageTextures_[i] = new Texture(game_->getRenderer(), textures[i]);
	}
}

void Resources::setTextTextures(std::vector<TextMsgInfo> texts) {
	closeTextTextures();
	numOfTextTextures_ = texts.size();
	textTextures_ = new Texture*[numOfTextTextures_];
	for (int i = 0; i < numOfTextTextures_; i++) {
		std::string txt = texts[i].text;
		Font* font = getFont(texts[i].fontId);
		SDL_Color color = texts[i].color;
		textTextures_[i] = new Texture(game_->getRenderer(), txt, *font, color);
	}
}

void Resources::setFonts(std::vector<FontInfo> fonts) {
	closeFonts();
	numOfFonts_ = fonts.size();
	fonts_ = new Font*[numOfFonts_];
	for (int i = 0; i < numOfFonts_; i++) {
		fonts_[i] = new Font(fonts[i].fileName, fonts[i].size);
	}
}

void Resources::setMusic(std::vector<std::string> music) {
	closeMusic();
	numOfMusic_ = music.size();
	music_ = new Music*[numOfMusic_];
	for (int i = 0; i < numOfMusic_; i++) {
		music_[i] = new Music(music[i]);
	}
}

void Resources::setSoundEffects(std::vector<std::string> soundEffects) {
	closeSoundEffects();
	numOfSoundEffects_ = soundEffects.size();
	soundEffects_ = new SoundEffect*[numOfSoundEffects_];
	for (int i = 0; i < numOfSoundEffects_; i++) {
		soundEffects_[i] = new SoundEffect(soundEffects[i]);
	}
}

void Resources::closeImageTextures() {
	for (int i = 0; i < numOfImageTextures_; i++) {
		if (imageTextures_[i] != nullptr) {
			delete imageTextures_[i];
		}
	}
	delete[] imageTextures_;
	numOfImageTextures_ = 0;

}

void Resources::closeTextTextures() {
	for (int i = 0; i < numOfTextTextures_; i++) {
		if (textTextures_[i] != nullptr) {
			delete textTextures_[i];
		}
	}
	delete[] textTextures_;
	numOfTextTextures_ = 0;

}
void Resources::closeFonts() {
	for (int i = 0; i < numOfFonts_; i++) {
		if (fonts_[i] != nullptr) {
			delete fonts_[i];
		}
	}
	delete[] fonts_;
	numOfFonts_ = 0;
}

void Resources::closeMusic() {
	for (int i = 0; i < numOfMusic_; i++) {
		if (music_[i] != nullptr) {
			delete music_[i];
		}
	}
	delete[] music_;
	numOfMusic_ = 0;
}

void Resources::closeSoundEffects() {
	for (int i = 0; i < numOfSoundEffects_; i++) {
		if (soundEffects_[i] != nullptr) {
			delete soundEffects_[i];
		}
	}
	delete[] soundEffects_;
	numOfSoundEffects_ = 0;
}

Texture* Resources::getImageTexture(ImageId i) const {
	if (i < numOfImageTextures_)
		return imageTextures_[i];
	else
		return nullptr;
}

Texture* Resources::getTextTexture(TextId i) const {
	if (i < numOfTextTextures_)
		return textTextures_[i];
	else
		return nullptr;
}

Font* Resources::getFont(FontId i) const {
	if (i < numOfFonts_)
		return fonts_[i];
	else
		return nullptr;
}

Music* Resources::getMusic(MusicId i) const {
	if (i < numOfMusic_)
		return music_[i];
	else
		return nullptr;
}

SoundEffect* Resources::getSoundEffect(SoundEffectId i) const {
	if (i < numOfSoundEffects_)
		return soundEffects_[i];
	else
		return nullptr;
}
