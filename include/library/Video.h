#ifndef VIDEO_SYSTEM_H
#define VIDEO_SYSTEM_H
#include <SFML/Graphics.hpp>
#include <string>

const int BG_LAYER_NUM = 3;
const int PIXEL_SHADER_NUM = 3;
const int VERTEX_SHADER_NUM = 3;
/***************************************************************************************
 * Video Class.
 ***************************************************************************************/
class Video {

/***
 * enum
 */
public:
	enum ScrollDirection {
		DIRECTION_NONE = 0,
		DIRECTION_VERTICAL = 1,
		DIRECTION_HORIZONTAL = 2,
		DIRECTION_RIGHT_DOWN = 3,
		DIRECTION_LEFT_DOWN = 4,
	};
	enum BgLayer {
		BG_1 = 0, 
		BG_2 = 1,
		BG_3 = 2,
	};
	enum PixelShader {
		PS_NONE = 0,
		PS_RASTER = 1,
		PS_PIXELIZE = 2,
	};
	enum VertexShader {
		VS_NONE = 0,
		VS_WATER = 1,
	};
	enum BgTiledType {
		BG_TILED_BOTH = 0,
		BG_TILED_VERTICAL = 1,
		BG_TILED_HORIZONTAL = 2,
	};

/**
 * private members.
 */
private:
	static int m_width;
	static int m_height;
	static sf::Vector2u m_bgSizes[BG_LAYER_NUM];
	static sf::Vector2i m_bgPositions[BG_LAYER_NUM];
	static ScrollDirection m_scrollDirections[BG_LAYER_NUM];
	static sf::RenderTexture m_bgLayers[BG_LAYER_NUM];
	static int m_bgScrollSpeeds[BG_LAYER_NUM];
	static sf::Shader m_bgShader[BG_LAYER_NUM];
	static sf::Clock m_clock;
	static std::string m_pixelShaderScripts[PIXEL_SHADER_NUM];
	static std::string m_vertexShaderScripts[VERTEX_SHADER_NUM];

/**
 * public member.
 */
public:
	static void setupPixelShaderScripts();
	static void initialize(int, int);
	static void toggleFullScreen();
	static void tiledBgFromFile(BgLayer layer, std::string image_filename);
	static void tiledBgFromFile(BgLayer layer, std::string image_filename, BgTiledType tiledType, int offset);
	static void bgFromFile(BgLayer layer, std::string image_filename);
	static void bgFromFile(BgLayer layer, std::string image_filename, int x, int y);

	static void drawBg(sf::RenderWindow &window);
	static void clearBg(BgLayer layer);
	static void scrollBg();
	static void setBgScrollDirection(BgLayer layer, ScrollDirection direction);
	static void setBgScrollSpeed(BgLayer layer, int speed);
	static sf::RenderWindow window;

};

#endif