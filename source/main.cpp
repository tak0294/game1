#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

#include "GameManager.h"
#include "Scene.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BPP 16


GameManager *gameManager;


/***************************************************************************************
 * TestScene Class.
 ***************************************************************************************/
class TestScene : public Scene {
	float x;
	float y;
	int frame;
	sf::CircleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;
	sf::Text text;
public:
	void setup();
	void draw(sf::RenderWindow &window);
	void update();
};

void TestScene::setup() {
	this->frame = 0;
	this->x = .0f;
	this->y = .0f;
	this->shape.setRadius(10.0f);
	this->texture.loadFromFile("pumpkin064.png");
	this->sprite.setTexture(this->texture);
	this->font.loadFromFile("yutapon.ttf");
	this->text.setFont(font);
	this->text.setString("10.00");
}

void TestScene::draw(sf::RenderWindow &window) {
	sprite.setPosition(this->x, this->y);
    window.draw(sprite);
	std::stringstream ss;

    ss << frame;
    text.setString(ss.str());

    window.draw(text);
}

void TestScene::update() {
	if(InputSystem::isRight) {
		this->x += 2.0f;
	}

	frame++;
}




/***************************************************************************************
 * Main Func.
 ***************************************************************************************/
int main(int argc, char* argv[]){

	gameManager = new GameManager(WINDOW_WIDTH, WINDOW_HEIGHT, BPP);
	TestScene *s = new TestScene();
	s->setup();
	gameManager->setScene(s);
	gameManager->start();
		

	return 0;
}

