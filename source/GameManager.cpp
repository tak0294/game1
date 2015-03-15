#include "GameManager.h"

GameManager::GameManager(int screen_w, int screen_h, int screen_bpp) {
	this->m_video = new VideoSystem();
	this->m_video->initialize(screen_w, screen_h, screen_bpp);
	InputSystem::initialize();
	this->m_currentScene = NULL;
}

VideoSystem* GameManager::getDisplay() {
	return this->m_video;
}

void GameManager::start() {

	sf::RenderWindow &window = (this->m_video->window);
	
	// Start the game loop
    while (window.isOpen())
    {
    	InputSystem::updateKeyState(this->m_video->window);
    	if(InputSystem::isESC) {
    		window.close();
    	}

        // Clear screen
        window.clear();
        // Draw current scene.
        this->m_currentScene->update();
        this->m_currentScene->draw(window);
        // Update the window
        window.display();
    }
}

void GameManager::quit() {
	//SDL_FreeSurface(image);
	//SDL_Quit();
}


void GameManager::setScene(Scene *scene) {
	this->m_currentScene = scene;
}
