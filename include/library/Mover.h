#ifndef MOVER_H
#define MOVER_H
#include <string>
#include <SFML/Graphics.hpp>

class Mover {

	sf::Texture m_texture;
	sf::Vector2u m_textureSize;
	sf::Sprite m_sprite;

public:
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f scale;
	float rotation;

	Mover();
	void setTexture(std::string texture_filename);
	void draw(sf::RenderWindow &window);
	void update();
};

#endif