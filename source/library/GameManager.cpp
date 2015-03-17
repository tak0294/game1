#include "library/GameManager.h"

GameManager::GameManager(int screen_w, int screen_h) {
	VideoSystem::initialize(screen_w, screen_h);
	InputSystem::initialize();
	this->m_currentScene = NULL;
}

void GameManager::start() {

	sf::RenderWindow &window = (VideoSystem::window);
    sf::Clock clock;
    float startTime;
    float endTime;

	// Start the game loop
    while (window.isOpen())
    {
    	InputSystem::updateKeyState(window);
    	if(InputSystem::isESC) {
    		window.close();
    	}

        //process start time.
        startTime = clock.restart().asSeconds();

        // Clear screen
        window.clear();
        // Draw background.
        VideoSystem::drawBackground(window);
        VideoSystem::scrollBackground();
        // Draw current scene.
        this->m_currentScene->update();
        this->m_currentScene->draw(window);
        // Update the window
        window.display();

        // process end time & fix fps
        endTime = clock.getElapsedTime().asSeconds();
        float passTime = endTime - startTime;
        //(1000 / 60 > passTime)?sf::sleep(sf::seconds((1000/60 - passTime) / 1000)):sf::sleep(sf::seconds(0));
    }
}

void GameManager::quit() {
	//SDL_FreeSurface(image);
	//SDL_Quit();
}


void GameManager::setScene(Scene *scene) {
	this->m_currentScene = scene;
}
