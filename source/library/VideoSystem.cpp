#include "library/VideoSystem.h"

/**
 * Declare real symbols.
 */
int VideoSystem::m_width;
int VideoSystem::m_height;
sf::Vector2u VideoSystem::m_bgSize;
sf::Vector2i VideoSystem::m_bgPos;

sf::RenderWindow VideoSystem::window;
sf::RenderTexture VideoSystem::bgRenderTexture;
sf::Sprite VideoSystem::backgroundSprite;
sf::Texture VideoSystem::backgroundTexture;
int VideoSystem::bgScrollSpeed;

/**
 *	SDL初期化.
 */
void VideoSystem::initialize(int w, int h) {
	m_width = w;
	m_height = h;
    window.create(sf::VideoMode(w, h), "SFML works!!!");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    bgScrollSpeed = 0;
    //bgRenderTexture.create(w, h);
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
	backgroundTexture.loadFromFile(image_filename);
	m_bgSize = backgroundTexture.getSize();
	int w = m_width + m_bgSize.x*2;
	int h = m_height + m_bgSize.y*2;
	bgRenderTexture.create(w, h);
	backgroundSprite.setTexture(backgroundTexture);
	for(int ii=0;ii<h;ii+=m_bgSize.y) {
		for(int jj=0;jj<w;jj+=m_bgSize.x) {
			backgroundSprite.setPosition(jj, ii);
			bgRenderTexture.draw(backgroundSprite);
		}
	}
	m_bgPos.x = -m_bgSize.x;
	m_bgPos.y = -m_bgSize.y;
	bgRenderTexture.display();
}

/**
 * 背景スクロール.
 */
void VideoSystem::scrollBackground() {

	for(int ii=0;ii<bgScrollSpeed;ii++) {
	    m_bgPos.x += 1;
	    m_bgPos.y += 1;
	    if(m_bgPos.y % m_bgSize.y == 0) {
			m_bgPos.x = -m_bgSize.x;
			m_bgPos.y = -m_bgSize.y;
	    }
	}
}

/**
 * 背景描画.
 */
void VideoSystem::drawBackground(sf::RenderWindow &window) {
	sf::Sprite sprite(VideoSystem::bgRenderTexture.getTexture());
	sprite.setPosition((float)m_bgPos.x, (float)m_bgPos.y);
    window.draw(sprite);
}

/**
 * 背景消去.
 */
void VideoSystem::clearBackground() {
	bgRenderTexture.clear();
}