#include "library/Video.h"

/**
 * Declare real symbols.
 */
int Video::m_width;
int Video::m_height;
sf::Vector2u Video::m_bgSizes[BG_LAYER_NUM];
sf::Vector2i Video::m_bgPositions[BG_LAYER_NUM];
Video::ScrollDirection Video::m_scrollDirections[BG_LAYER_NUM];
sf::RenderTexture Video::m_bgLayers[BG_LAYER_NUM];

sf::RenderWindow Video::window;
int Video::m_bgScrollSpeeds[BG_LAYER_NUM];

/**
 *	SDL初期化.
 */
void Video::initialize(int w, int h) {
	m_width = w;
	m_height = h;
    window.create(sf::VideoMode(w, h), "SFML works!!!");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    for(int ii=0;ii<BG_LAYER_NUM;ii++) {
    	m_scrollDirections[ii] = DIRECTION_NONE;
    	m_bgScrollSpeeds[ii]    = 0;
    }
}

/**
 * フルスクリーン切り替え.
 */
void Video::toggleFullScreen() {
	//SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
}

/**
 * 背景スクロール方向設定.
 */
void Video::setBgScrollDirection(BgLayer layer, ScrollDirection direction) {
	m_scrollDirections[layer] = direction;
}

/**
 * 背景スクロール速度設定.
 */
void Video::setBgScrollSpeed(BgLayer layer, int speed) {
	m_bgScrollSpeeds[layer] = speed;
}

/**
 * 背景.
 */
void Video::tiledBgFromFile(BgLayer layer, std::string image_filename) {
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile(image_filename);
	m_bgSizes[layer] = backgroundTexture.getSize();
	
	int w = m_width + m_bgSizes[layer].x*2;
	int h = m_height + m_bgSizes[layer].y*2;
	
	m_bgLayers[layer].create(w, h);
	backgroundSprite.setTexture(backgroundTexture);
	for(int ii=0;ii<h;ii+=m_bgSizes[layer].y) {
		for(int jj=0;jj<w;jj+=m_bgSizes[layer].x) {
			backgroundSprite.setPosition(jj, ii);
			m_bgLayers[layer].draw(backgroundSprite);
		}
	}
	m_bgPositions[layer].x = -m_bgSizes[layer].x;
	m_bgPositions[layer].y = -m_bgSizes[layer].y;
	m_bgLayers[layer].display();
}

/**
 * 背景スクロール.
 */
void Video::scrollBg() {

	for(int layer=0;layer<BG_LAYER_NUM;layer++) {
		for(int ii=0;ii<m_bgScrollSpeeds[layer];ii++) {
			if(m_scrollDirections[layer] == DIRECTION_VERTICAL) {
				m_bgPositions[layer].y += 1;
			}else if(m_scrollDirections[layer] == DIRECTION_HORIZONTAL) {
				m_bgPositions[layer].x += 1;
			}else if(m_scrollDirections[layer] == DIRECTION_LEFT_DOWN) {
				m_bgPositions[layer].x -= 1;
				m_bgPositions[layer].y += 1;
			}else if(m_scrollDirections[layer] == DIRECTION_RIGHT_DOWN) {
				m_bgPositions[layer].x += 1;
				m_bgPositions[layer].y += 1;
			}
		    
		    if(m_scrollDirections[layer] == DIRECTION_VERTICAL ||
		       m_scrollDirections[layer] == DIRECTION_LEFT_DOWN ||
		       m_scrollDirections[layer] == DIRECTION_RIGHT_DOWN) {
			    if(m_bgPositions[layer].y == 0) {
					m_bgPositions[layer].x = -m_bgSizes[layer].x;
					m_bgPositions[layer].y = -m_bgSizes[layer].y;
			    }
		    }else{
		    	if(m_bgPositions[layer].x == 0) {
					m_bgPositions[layer].x = -m_bgSizes[layer].x;
			    }
		    }
		}

	}
}

/**
 * 背景描画.
 */
void Video::drawBg(sf::RenderWindow &window) {
	for(int layer=0;layer<BG_LAYER_NUM;layer++) {
		sf::Sprite sprite(Video::m_bgLayers[layer].getTexture());
		sprite.setPosition((float)m_bgPositions[layer].x, (float)m_bgPositions[layer].y);
		//sprite.setColor(sf::Color(255,255,255,200));
	    window.draw(sprite);
	}
}

/**
 * 背景消去.
 */
void Video::clearBg(BgLayer layer) {
	m_bgLayers[layer].clear();
}