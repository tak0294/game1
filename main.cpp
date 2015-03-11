#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BPP 16

/***************************************************************************************
 * VideoSystem Class.
 ***************************************************************************************/
class VideoSystem {
	SDL_Surface *screen;
	int m_width;
	int m_height;
	int m_bpp;

public:
	void initialize(int, int, int);
	void toggleFullScreen();
};

/**
 *	SDL初期化.
 */
void VideoSystem::initialize(int w, int h, int bpp) {
	this->m_width = w;
	this->m_height = h;
	this->m_bpp = bpp;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(1,1000/60);
	SDL_SetVideoMode(w, h, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);	
}


/**
 * フルスクリーン切り替え.
 */
void VideoSystem::toggleFullScreen() {
	SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
}



/***************************************************************************************
 * InputSystem Class.
 ***************************************************************************************/
class InputSystem {
private:
	SDL_Event event;
public:
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	bool isA;
	bool isB;
	bool isESC;

	void updateKeyState();
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

void InputSystem::updateKeyState() {
	if(SDL_PollEvent(&this->event)){
		switch(this->event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_UP:
						this->isUp = true;
						break;
					case SDLK_DOWN:
						this->isDown = true;
						break;
					case SDLK_RIGHT:
						this->isRight = true;
						break;
					case SDLK_LEFT:
						this->isLeft = true;
						break;
					case SDLK_ESCAPE:
						this->isESC = true;
						break;
					default:
						break;

				}
			break;

			case SDL_KEYUP:
				switch(event.key.keysym.sym){
					case SDLK_UP:
						this->isUp = false;
						break;
					case SDLK_DOWN:
						this->isDown = false;
						break;
					case SDLK_RIGHT:
						this->isRight = false;
						break;
					case SDLK_LEFT:
						this->isLeft = false;
						break;
					case SDLK_ESCAPE:
						this->isESC = false;
						break;
					default:
						break;

				}

		}
	}
}


/***************************************************************************************
 * Scene Class.
 ***************************************************************************************/
class Scene {
public:
	virtual void setup() = 0;
	virtual void draw() = 0;
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

	/* イベントループ */
	while(exit_prg == 0){
		this->m_input->updateKeyState();

		if(this->m_input->isESC == true) {
			exit_prg = 1;
		}

		if(this->m_currentScene != NULL) {
			this->m_currentScene->update();
			this->m_currentScene->draw();
		}

		SDL_Delay(1000/60);
	}
}

void GameManager::quit() {
	//SDL_FreeSurface(image);
	SDL_Quit();
}

GameManager *gameManager;

void GameManager::setScene(Scene *scene) {
	this->m_currentScene = scene;
}




class TestScene : Scene {
public:
	void setup();
	void draw();
	void update();
};

void TestScene::setup() {

}

void TestScene::draw() {

}

void TestScene::update() {

}




SDL_Surface* image;
SDL_Rect rect, scr_rect, rect_tmp;

int draw(SDL_Surface *image, SDL_Rect *rect1, SDL_Rect *rect2);

int main(int argc, char* argv[]){

	gameManager = new GameManager(WINDOW_WIDTH, WINDOW_HEIGHT, BPP);
	gameManager->start();
	
	TestScene *s = new TestScene();
	gameManager->setScene(s);

	/* 画像読み込み */
	image = IMG_Load("pumpkin064.png");

	/* 画像の矩形情報設定 */
	rect.x = 0;
	rect.y = 0;
	rect.w = image->w;
	rect.h = image->h;

	/* 画像配置位置情報の設定 */
	scr_rect.x = 0;
	scr_rect.y = 0;

	/* 描画 */
	draw(image, &rect, &scr_rect);

	rect_tmp = scr_rect;


	return 0;
}

int draw(SDL_Surface *image, SDL_Rect *rect1, SDL_Rect *rect2){
	SDL_Rect window_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_Surface *video_surface;
	
	video_surface = SDL_GetVideoSurface();

	/* 背景色塗りつぶし */
	SDL_FillRect(video_surface, &window_rect, SDL_MapRGB(video_surface->format, 0, 0, 0));

	/* サーフェスの複写 */
	SDL_BlitSurface(image, rect1, video_surface, rect2);

	/* サーフェスフリップ */
	SDL_Flip(video_surface);

	return 0;
}