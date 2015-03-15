#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "GameManager.h"
#include "Scene.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
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

	sf::Clock clock;
	float lastTime;
public:
	void setup();
	void draw(sf::RenderWindow &window);
	void update();
};

void TestScene::setup() {
	this->frame = 0;
	this->x = .0f;
	this->y = 200.0f;
	this->shape.setRadius(10.0f);
	this->texture.loadFromFile("pumpkin064.png");
	this->sprite.setTexture(this->texture);
	this->font.loadFromFile("yutapon.ttf");
	this->text.setFont(font);
	this->text.setString("10.00");
	this->lastTime = 0;
}

void TestScene::draw(sf::RenderWindow &window) {
	sprite.setPosition(this->x, this->y);
	sprite.setOrigin(32, 32);
	sprite.setRotation(frame);
	window.draw(sprite);
	std::stringstream ss;
	float currentTIme = clock.restart().asSeconds();
	float fps = floor(1.f / (currentTIme));
	lastTime = currentTIme;

    ss << fps;
    text.setString(ss.str());

    window.draw(text);
}

void TestScene::update() {
	if(InputSystem::isRight) {
		this->x += 2.0f;
	}

	if(InputSystem::isLeft) {
		this->x -= 4.0f;
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

