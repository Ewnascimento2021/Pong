#pragma once
#include<SDL_render.h>
class Ball
{
public:
	Ball(int posX, int posY, int radius);
	void render(SDL_Renderer* renderer);
	void update();
	SDL_Rect* getRect() { return &m_rect; }
	void invertBall() { m_speedX *= -1; }
	int getRectX () { return m_rect.x; }
	void setRectX(int posX) { m_rect.x = posX; }
	void setRectY(int posY) { m_rect.y = posY; }
private:

	void move();
	SDL_Rect m_rect;
	int m_speedX = 10;
	int m_speedY = 10;
};

