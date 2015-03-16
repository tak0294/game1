#include "library/VideoSystem.h"

/**
 *	SDL初期化.
 */
void VideoSystem::initialize(int w, int h) {
	this->m_width = w;
	this->m_height = h;
    this->window.create(sf::VideoMode(w, h), "SFML works!!!");
    this->window.setVerticalSyncEnabled(true);
    this->window.setFramerateLimit(60);
    //this->bgTexture.create(w, h);
}

/**
 * フルスクリーン切り替え.
 */
void VideoSystem::toggleFullScreen() {
	//SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
}

/**
 * 背景.
 */
void VideoSystem::tiledBackgroundFromFile(std::string image_filename) {
	this->backgroundTexture.loadFromFile(image_filename);
	//this->m_textureSize = this->m_texture.getSize();
	this->backgroundSprite.setTexture(this->backgroundTexture);
}
