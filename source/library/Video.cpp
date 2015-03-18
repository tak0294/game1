#include "library/Video.h"
#include <stdio.h>
/**
 * Declare real symbols.
 */
int Video::m_width;
int Video::m_height;
sf::Vector2u Video::m_bgSizes[BG_LAYER_NUM];
sf::Vector2i Video::m_bgPositions[BG_LAYER_NUM];
Video::ScrollDirection Video::m_scrollDirections[BG_LAYER_NUM];
sf::RenderTexture Video::m_bgLayers[BG_LAYER_NUM];
sf::Shader Video::m_bgShader[BG_LAYER_NUM];
sf::Clock Video::m_clock;

sf::RenderWindow Video::window;
int Video::m_bgScrollSpeeds[BG_LAYER_NUM];

///////////////////////////////////////////////////////////////////
// ShaderScripts.
///////////////////////////////////////////////////////////////////
std::string Video::m_pixelShaderScripts[PIXEL_SHADER_NUM];
std::string Video::m_vertexShaderScripts[VERTEX_SHADER_NUM];


void Video::setupPixelShaderScripts() {
	m_pixelShaderScripts[Video::PS_RASTER] = \
    "uniform sampler2D texture; \
	uniform float wave_phase; \
	uniform float pixel_threshold; \
\
	void main() \
	{ \
		vec2 pos; \
		pos.x = gl_TexCoord[0].x; \
		pos.y = gl_TexCoord[0].y; \
	    float factor = 1.0 / (pixel_threshold + 0.001); \
		pos.x = floor(pos.x * factor + 0.5) / factor; \
		pos.y = floor(pos.y * factor + 0.5) / factor; \
\
		pos.x = mod(1.0f + pos.x + 0.05f*sin(pos.y * 30.0f + wave_phase * 0.95f), 1.0f); \
\
		gl_FragColor = texture2D(texture, pos) * gl_Color; \
	}";
}


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
    	m_bgScrollSpeeds[ii]   = 0;
    }
    //Shader scripts setup
    Video::setupPixelShaderScripts();

    // m_bgShader[0].loadFromFile("shader/pixelate.frag", sf::Shader::Fragment);
    // m_bgShader[0].loadFromFile("shader/wave.vert", sf::Shader::Vertex);
    // m_bgShader[0].loadFromFile("shader/wave.vert", "shader/pixelate.frag");
    m_bgShader[1].loadFromMemory(m_pixelShaderScripts[Video::PS_RASTER], sf::Shader::Fragment);
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
 * 背景
 */
void Video::bgFromFile(BgLayer layer, std::string image_filename) {
	Video::bgFromFile(layer, image_filename, 0, 0);
}


/**
 * 背景
 */
void Video::bgFromFile(BgLayer layer, std::string image_filename, int x, int y) {
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(image_filename);
	m_bgSizes[layer] = backgroundTexture.getSize();
	m_bgLayers[layer].create(m_bgSizes[layer].x, m_bgSizes[layer].y);

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	m_bgLayers[layer].draw(backgroundSprite);
	m_bgPositions[layer].x = x;
	m_bgPositions[layer].y = y;
	m_bgLayers[layer].display();
}

/**
 * 背景.
 */
void Video::tiledBgFromFile(BgLayer layer, std::string image_filename) {
	Video::tiledBgFromFile(layer, image_filename, BG_TILED_BOTH, 0);
}



/**
 * 背景.
 */
void Video::tiledBgFromFile(BgLayer layer, std::string image_filename, BgTiledType tiledType, int offset) {
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile(image_filename);
	m_bgSizes[layer] = backgroundTexture.getSize();
	
	int w = m_width + m_bgSizes[layer].x*2;
	int h = m_height + m_bgSizes[layer].y*2;
	
	m_bgLayers[layer].create(w, h);
	backgroundSprite.setTexture(backgroundTexture);

	////////////////////////////////////////////
	// BgTiledTypeによって敷き詰め方を変える.
	////////////////////////////////////////////
	if(tiledType == BG_TILED_BOTH) {
		for(int ii=0;ii<h;ii+=m_bgSizes[layer].y) {
			for(int jj=0;jj<w;jj+=m_bgSizes[layer].x) {
				backgroundSprite.setPosition(jj, ii);
				m_bgLayers[layer].draw(backgroundSprite);
			}
		}
	}else if(tiledType == BG_TILED_HORIZONTAL) {
		for(int jj=0;jj<w;jj+=m_bgSizes[layer].x) {
			backgroundSprite.setPosition(jj, offset);
			m_bgLayers[layer].draw(backgroundSprite);
		}
	}else if(tiledType == BG_TILED_VERTICAL) {
		for(int ii=0;ii<h;ii+=m_bgSizes[layer].y) {
			backgroundSprite.setPosition(offset, ii);
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
		//fragment
		m_bgShader[layer].setParameter("texture", sf::Shader::CurrentTexture);
		m_bgShader[layer].setParameter("wave_phase", m_clock.getElapsedTime().asSeconds());

		m_bgShader[layer].setParameter("pixel_threshold", 0.003);
		//vertex
        m_bgShader[layer].setParameter("wave_amplitude", 1 * 200, 0 * 40);
        m_bgShader[layer].setParameter("wave_height", (float)m_bgLayers[layer].getTexture().getSize().y);


	    window.draw(sprite, &m_bgShader[layer]);
	}
}

/**
 * 背景消去.
 */
void Video::clearBg(BgLayer layer) {
	m_bgLayers[layer].clear();
}