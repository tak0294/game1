#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "library/GameManager.h"
#include "library/Scene.h"
#include "library/Mover.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GameManager *gameManager;

/***************************************************************************************
 * TestPumpkin Class.
 ***************************************************************************************/
class TestPumpkin : public Mover {

public:
	void update();
	sf::Vector2f dst_scale;
};

void TestPumpkin::update() {
	this->rotation += 2.0f;
} 


/***************************************************************************************
 * TestScene Class.
 ***************************************************************************************/
class TestScene : public Scene {
	TestPumpkin *mover2;
public:
	void setup();
	void draw(sf::RenderWindow &window);
	void update();
};

void TestScene::setup() {
	Scene::setup();

	mover2 = new TestPumpkin();
	mover2->setTexture("pumpkin064.png");
	mover2->pos.y = 250;
}

void TestScene::draw(sf::RenderWindow &window) {
	this->mover2->draw(window);

}

void TestScene::update() {
	if(InputSystem::isRight) {
		mover2->pos.x += 2.0f;
	}

	if(InputSystem::isLeft) {
		mover2->pos.x -= 4.0f;
	}

	if(InputSystem::isA) {
		mover2->scale.x = mover2->scale.y = 10;
	}

	mover2->update();
	frame++;
}




/***************************************************************************************
 * Main Func.
 ***************************************************************************************/
int main(int argc, char* argv[]){

	gameManager = new GameManager(WINDOW_WIDTH, WINDOW_HEIGHT);
	TestScene *s = new TestScene();
	s->setup();
	gameManager->setScene(s);
	gameManager->start();

	return 0;
}

