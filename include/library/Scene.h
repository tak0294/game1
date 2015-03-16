#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>

/***************************************************************************************
 * Scene Class.
 ***************************************************************************************/
class Scene {
public:
	virtual void setup() = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
};

#endif