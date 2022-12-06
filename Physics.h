#pragma once
#include <SDL_rect.h>

static class Physics {

public:
	bool static checkCollision(SDL_Rect* objectA, SDL_Rect* objectB)
	{
		return SDL_HasIntersection(objectA, objectB);
	}

	void static scoreUp(int gamer)
	{
		if (gamer == 1)
		{
			//Aumentar o placar do jogador 1 
		}
		else if (gamer == 2)
		{
			//Aumentar o placar do jogador 2
		}
	}
};