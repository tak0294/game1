#include "library/VideoSystem.h"

/**
 *	SDL初期化.
 */
void VideoSystem::initialize(int w, int h, int bpp) {
	this->m_width = w;
	this->m_height = h;
	this->m_bpp = bpp;
    this->window.create(sf::VideoMode(w, h), "SFML works!!!");
}

/**
 * フルスクリーン切り替え.
 */
void VideoSystem::toggleFullScreen() {
	//SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
}

