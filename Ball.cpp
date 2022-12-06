#include "Ball.h"

Ball::Ball(int posX, int posY, int radius)
{
	m_rect = { posX - radius, posY - radius, radius * 2, radius * 2 };

}
void Ball::render(SDL_Renderer* renderer)
{
	SDL_RenderFillRect(renderer, &m_rect);
}
void Ball::update()
{
	
	if (m_rect.y > 680 - m_rect.h || m_rect.y < 0)
	{
		m_speedY *= -1;
	}
	
	move();
}

void Ball::move()
{
	m_rect.x += m_speedX;
	m_rect.y += m_speedY;
	
	
}