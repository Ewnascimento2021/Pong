#include "PlayerBar.h"


PlayerBar::PlayerBar(int posX, int posY, int width, int height)
{
	m_rect = { posX, posY, width, height};

}

void PlayerBar::render(SDL_Renderer* renderer)
{
	SDL_RenderFillRect(renderer, &m_rect);
}

void PlayerBar::setDirection(int direction)
{
	m_direction = direction;
}

void PlayerBar::update()
{
	if (m_direction != 0 && m_rect.y + m_speed * m_direction < 680 - m_rect.h && m_rect.y + m_speed * m_direction > 0)
	{
		move();
	}
}

void PlayerBar::move()
{
	m_rect.y += m_speed * m_direction;
}


