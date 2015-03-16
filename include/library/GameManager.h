#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include "library/VideoSystem.h"
#include "library/InputSystem.h"
#include "library/Scene.h"

/***************************************************************************************
 * GameManager Class.
 ***************************************************************************************/
class GameManager {
	VideoSystem *m_video;
	InputSystem *m_input;

	Scene *m_currentScene;
public:
	GameManager(int, int);
	VideoSystem* getDisplay();
	void setScene(Scene *scene);
	void start();
	void quit();
};


#endif