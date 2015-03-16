#ifndef VIDEO_SYSTEM_H
#define VIDEO_SYSTEM_H
#include <SFML/Graphics.hpp>

/***************************************************************************************
 * VideoSystem Class.
 ***************************************************************************************/
class VideoSystem {
	int m_width;
	int m_height;

public:
	void initialize(int, int);
	void toggleFullScreen();
	sf::RenderWindow window;
};

#endif