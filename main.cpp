#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BPP 16

/***************************************************************************************
 * VideoSystem Class.
 ***************************************************************************************/
class VideoSystem {
	int m_width;
	int m_height;
	int m_bpp;

public:
	void initialize(int, int, int);
	void toggleFullScreen();
	sf::RenderWindow window;
};

/**
 *	SDL初期化.
 */
void VideoSystem::initialize(int w, int h, int bpp) {
	this->m_width = w;
	this->m_height = h;
	this->m_bpp = bpp;
    this->window.create(sf::VideoMode(w, h), "SFML works!!!");
}

/**
 * フルスクリーン切り替え.
 */
void VideoSystem::toggleFullScreen() {
	//SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
}



/***************************************************************************************
 * InputSystem Class.
 ***************************************************************************************/
class InputSystem {
private:
	sf::Event event;
public:
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	bool isA;
	bool isB;
	bool isESC;

	void updateKeyState(sf::RenderWindow &window);
	void initialize();
};

void InputSystem::initialize() {
	this->isLeft = false;
	this->isRight = false;
	this->isUp = false;
	this->isDown = false;
	this->isA = false;
	this->isB = false;
	this->isESC = false;
}

void InputSystem::updateKeyState(sf::RenderWindow &window) {

	if(window.pollEvent(this->event)){
		switch(this->event.type){
			case sf::Event::KeyPressed:
				switch(this->event.key.code){
					case sf::Keyboard::Up:
						this->isUp = true;
						break;
					case sf::Keyboard::Down:
						this->isDown = true;
						break;
					case sf::Keyboard::Right:
						this->isRight = true;
						break;
					case sf::Keyboard::Left:
						this->isLeft = true;
						break;
					case sf::Keyboard::Escape:
						this->isESC = true;
						break;
					default:
						break;

				}
			break;

			case sf::Event::KeyReleased:
				switch(this->event.key.code){
					case sf::Keyboard::Up:
						this->isUp = false;
						break;
					case sf::Keyboard::Down:
						this->isDown = false;
						break;
					case sf::Keyboard::Right:
						this->isRight = false;
						break;
					case sf::Keyboard::Left:
						this->isLeft = false;
						break;
					case sf::Keyboard::Escape:
						this->isESC = false;
						break;
					default:
						break;

				}
			break;
		}
	}
}


/***************************************************************************************
 * Scene Class.
 ***************************************************************************************/
class Scene {
public:
	virtual void setup() = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
};


/***************************************************************************************
 * GameManager Class.
 ***************************************************************************************/
class GameManager {
	VideoSystem *m_video;
	InputSystem *m_input;

	Scene *m_currentScene;
public:
	GameManager(int, int, int);
	VideoSystem* getDisplay();
	void setScene(Scene *scene);
	void start();
	void quit();
};

GameManager::GameManager(int screen_w, int screen_h, int screen_bpp) {
	this->m_video = new VideoSystem();
	this->m_video->initialize(screen_w, screen_h, screen_bpp);
	this->m_input = new InputSystem();
	this->m_input->initialize();
	this->m_currentScene = NULL;
}

VideoSystem* GameManager::getDisplay() {
	return this->m_video;
}

void GameManager::start() {
	int exit_prg = 0;

	// Start the game loop
    while (this->m_video->window.isOpen())
    {
    	this->m_input->updateKeyState(this->m_video->window);
    	if(this->m_input->isESC) {
    		this->m_video->window.close();
    	}

        // Clear screen
        this->m_video->window.clear();
        // Draw current scene.
        this->m_currentScene->update();
        this->m_currentScene->draw(this->m_video->window);
        // Update the window
        this->m_video->window.display();
    }
}

void GameManager::quit() {
	//SDL_FreeSurface(image);
	//SDL_Quit();
}

GameManager *gameManager;

void GameManager::setScene(Scene *scene) {
	this->m_currentScene = scene;
}




/***************************************************************************************
 * TestScene Class.
 ***************************************************************************************/
class TestScene : public Scene {
public:
	void setup();
	void draw(sf::RenderWindow &window);
	void update();
};

void TestScene::setup() {

}

void TestScene::draw(sf::RenderWindow &window) {
	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}

void TestScene::update() {

}




/***************************************************************************************
 * Main Func.
 ***************************************************************************************/
int main(int argc, char* argv[]){

	gameManager = new GameManager(WINDOW_WIDTH, WINDOW_HEIGHT, BPP);
	TestScene *s = new TestScene();
	gameManager->setScene(s);

	gameManager->start();
	

	return 0;
}