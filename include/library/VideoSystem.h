#ifndef VIDEO_SYSTEM_H
#define VIDEO_SYSTEM_H
#include <SFML/Graphics.hpp>
#include <string>

/***************************************************************************************
 * VideoSystem Class.
 ***************************************************************************************/
class VideoSystem {
	static int m_width;
	static int m_height;
	static sf::Vector2u m_bgSize;
	static sf::Vector2i m_bgPos;

public:
	static void initialize(int, int);
	static void toggleFullScreen();
	static void tiledBackgroundFromFile(std::string image_filename);
	static void drawBackground(sf::RenderWindow &window);
	static void clearBackground();
	static void scrollBackground();
	static sf::RenderWindow window;
	static sf::RenderTexture bgRenderTexture;
	static sf::Sprite backgroundSprite;
	static sf::Texture backgroundTexture;

	static int bgScrollSpeed;
};

#endif