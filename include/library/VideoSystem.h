#ifndef VIDEO_SYSTEM_H
#define VIDEO_SYSTEM_H
#include <SFML/Graphics.hpp>
#include <string>

/***************************************************************************************
 * VideoSystem Class.
 ***************************************************************************************/
class VideoSystem {
	int m_width;
	int m_height;

public:
	void initialize(int, int);
	void toggleFullScreen();
	void tiledBackgroundFromFile(std::string image_filename);
	sf::RenderWindow window;
	sf::RenderTexture bgTexture;
};

#endif