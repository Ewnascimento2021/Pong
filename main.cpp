#include "SDL.h"
#include <iostream>
#include "PlayerBar.h"
#include "Ball.h"
#include "Physics.h"
#include <SDL_ttf.h>
#include <cstring>
#include <string>

using namespace std;

#pragma region VARIABLES
//Game window setup
const char GAME_TITLE[32] = "SUPER GAME TURBO DELUX";
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 680;
const bool IS_FULLSCREEN = false;
const int rectHeight = SCREEN_HEIGHT / 7;
const int rectWidth = SCREEN_WIDTH / 100 * 3;
const int playerSpace = SCREEN_WIDTH / 100;



//GAME FPS setup
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

//Game loop
bool m_isRunning;

//SDL References
SDL_Window* m_Window;
SDL_Renderer* m_Renderer;

// Players

PlayerBar* player01;
PlayerBar* player02;

//Placar do Jogo
int placar1 = 0;
int placar2 = 0;

//Ball

Ball* bolaQuadrada;

//Fontes
TTF_Font* m_Font = NULL;
SDL_Color textColor = { 255, 255, 255 };
int fontSize = 18;

#pragma endregion


#pragma region FUNCTIONS
bool init();
void handleEvents();
void update();
void render();
void clearMemory();
void quit();
void loadFont();
#pragma endregion


int main(int argc, char* args[])
{
	//Usado para controlar o FPS do jogo
	Uint32 frameStart, frameTime;

	if (init()) {
		cout << "GAME INIT SUCCESS\n";
		player01 = new PlayerBar(playerSpace, SCREEN_HEIGHT / 2 - rectHeight / 2 , rectWidth, rectHeight);
		player02 = new PlayerBar(SCREEN_WIDTH - playerSpace - rectWidth, SCREEN_HEIGHT / 2 - rectHeight / 2, rectWidth, rectHeight);
		bolaQuadrada = new Ball(200, 200, 10);
		
		loadFont();
		
		while (m_isRunning)
		{
			frameStart = SDL_GetTicks();

			handleEvents();
			update();
			render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else {
		cout << "GAME INIT FAIL - " << SDL_GetError() << "\n";
		return -1;
	}

	cout << "game closing...\n";
	delete player01;
	delete player02;
	delete bolaQuadrada;
	clearMemory();

	return 0;
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "FAIL TO INIT SDL\n";
		return false;
	}

	m_Window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, IS_FULLSCREEN);
	if (m_Window == 0) {
		cout << "FAIL TO CREATE WINDOW\n";
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
	if (m_Renderer == 0) {
		cout << "FAIL TO CREATE RENDERER\n";
		return false;
	}

	if (TTF_Init() == -1)
	{
		cout << "FAIL TO INIT TTF\n";
		return false;
	}

	m_isRunning = true;
	return true;
}

void loadFont()
{
	m_Font = TTF_OpenFont("resources/pixelFont.ttf", fontSize);

	if (m_Font == NULL) {
		string error = TTF_GetError();
		cout << error << endl;
	}
}

void handleEvents()
{


	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit();

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w)
			{
				player01->setDirection(-1);
			} else if(event.key.keysym.sym == SDLK_s)
			{
				player01->setDirection(1);
			}
			if (event.key.keysym.sym == SDLK_UP)
			{
				player02->setDirection(-1);
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				player02->setDirection(1);
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s)
			{
				player01->setDirection(0);
			}
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
			{
				player02->setDirection(0);
			}
			break;
		default:
			break;
		}
	}
}

void update()
{
	if (Physics::checkCollision(player01->getRect(), bolaQuadrada->getRect()) ||
		Physics::checkCollision(player02->getRect(), bolaQuadrada->getRect())) {
		
		bolaQuadrada->invertBall();
	}
	player01->update();
	player02->update();
	bolaQuadrada->update();

	if (bolaQuadrada->getRectX() > SCREEN_WIDTH)
	{
		placar1++;
		SDL_Delay(1000);
		bolaQuadrada->setRectX(SCREEN_WIDTH - 200);
		bolaQuadrada->setRectY(200);
		bolaQuadrada->invertBall();
	}

	if (bolaQuadrada->getRectX() < 0)
	{	
		placar2++;
		SDL_Delay(1000);
		bolaQuadrada->setRectX(200);
		bolaQuadrada->setRectY(200);
		bolaQuadrada->invertBall();
	}

}

void render()
{
	SDL_SetRenderDrawColor(m_Renderer, 40, 40, 40, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_Renderer);

	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	//Variaveis do Placar

	
	
	string heitor[1] = { to_string(placar1) + " X " + to_string(placar2)};


	//const char mensagem = "nenem";
	SDL_Surface* message = TTF_RenderText_Solid(m_Font, heitor->c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, message);

	SDL_Rect renderQuad = { 0, 0, 1000, 100 };
	SDL_RenderCopyEx(m_Renderer, texture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
	
	player01->render(m_Renderer);
	player02->render(m_Renderer);
	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
	bolaQuadrada->render(m_Renderer);
	
	
	


	SDL_RenderPresent(m_Renderer);
}

void clearMemory()

{
	TTF_CloseFont(m_Font);
	TTF_Quit();

	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	SDL_Quit();

}

void quit()
{
	m_isRunning = false;
}


