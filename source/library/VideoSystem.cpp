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
}

/**
 * フルスクリーン切り替え.
 */
void VideoSystem::toggleFullScreen() {
	//SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
}

