#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "library/GameManager.h"
#include "library/Scene.h"
#include "library/Mover.h"
#include "library/ParticleSystem.h"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

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
	ParticleSystem *psys;
public:
	void setup();
	void draw(sf::RenderWindow &window);
	void update();
};

void TestScene::setup() {
	Scene::setup();
	// Video::addSpritePixelShader(Video::SP_1, Video::PS_PIXELIZE);
	// Video::addSpritePixelShader(Video::SP_1, Video::PS_RASTER);

	///////////////////////////////////////////////////////
	//	BG Layers.
	///////////////////////////////////////////////////////
	Video::tiledBgFromFile(Video::BG_2, "pumpkin064.png");
	// Video::bgFromFile(Video::BG_2, "flame.png", -240, -140);
	// Video::tiledBgFromFile(Video::BG_2, "flame.png", Video::BG_TILED_HORIZONTAL, 800);
	// Video::addBgPixelShader(Video::BG_2, Video::PS_PIXELIZE);
	// Video::addBgPixelShader(Video::BG_2, Video::PS_RASTER);
	Video::setBgScrollDirection(Video::BG_2, Video::DIRECTION_LEFT_DOWN);
	Video::setBgScrollSpeed(Video::BG_2, 2);

	Video::tiledBgFromFile(Video::BG_1, "city.png", Video::BG_TILED_HORIZONTAL, 500);
	
	mover2 = new TestPumpkin();
	mover2->setTexture("pumpkin064.png");
	mover2->pos.y = 250;
	mover2->scale.x = mover2->scale.y = 1.5f;

	///////////////////////////////////////////////////////
	//	ParticleSystem setup.
	///////////////////////////////////////////////////////
	psys = new ParticleSystem();
	psys->addColor(sf::Color::Red);
	psys->addColor(sf::Color::Yellow);
}

void TestScene::draw(sf::RenderWindow &window) {
	psys->draw();
	this->mover2->draw();
	Video::drawText("TEXT!!", Video::FONT_NORMAL, 200, 400, 100);
}

void TestScene::update() {
	if(InputSystem::isRight) {
		mover2->pos.x += 4.0f;
		psys->add(mover2->pos.x, mover2->pos.y);
	}

	if(InputSystem::isLeft) {
		mover2->pos.x -= 4.0f;
		psys->add(mover2->pos.x, mover2->pos.y);
	}
	if(InputSystem::isDown) {
		mover2->pos.y += 4.0f;
		psys->add(mover2->pos.x, mover2->pos.y);
	}

	if(InputSystem::isUp) {
		mover2->pos.y -= 4.0f;
		psys->add(mover2->pos.x, mover2->pos.y);
	}

	if(InputSystem::isA) {
		mover2->scale.x = mover2->scale.y = 7;
		Video::clearBg(Video::BG_1);
	}
	psys->update();
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

