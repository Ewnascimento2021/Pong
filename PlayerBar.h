#pragma once
#include<SDL_render.h>

class PlayerBar
{
public:
	PlayerBar(int posX, int posY, int width, int height);
	void render(SDL_Renderer* renderer);
	void setDirection(int direction);
	void update();
	SDL_Rect* getRect() { return &m_rect; };
	

private:
	void move();
	SDL_Rect m_rect;
	int m_speed = 10;
	int m_direction = 0;



};
