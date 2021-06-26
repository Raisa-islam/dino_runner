#include "Snake.h"
#include "globals.h"
Snake::Snake()
{
	sPosX = -100;
	sPosY = -100;
}

void Snake::render(int n, int camX, int camY)
{
	if (!killed[n])
	{
		SDL_Rect *currentClip = &snake[(currentframe / 20) % 5];
		SnakeTexture.render(sPosX - camX, sPosY - camY, currentClip, 0, NULL, flipType);
	}
}

void Snake::setPosition(int n, int x, int y)
{
	killed[n] = 0;
	sPosX = x;
	sPosY = y;
}

int Snake::checkColision(int n, int dot_x, int dot_y, int dot_width, int dot_height, int firing, int flipflag)
{
	if (!killed[n] && dot_x + dot_width - 100 >= sPosX && dot_x - 100 <= sPosX + width && dot_y + dot_height >= sPosY && firing && flipflag)
	{
		//Mix_PlayChannel( -1, gLow, 0 );
		killed[n] = 1;
		return 2;
	}
  	if (!killed[n] && dot_x + dot_width + 100 >= sPosX && dot_x + 100 <= sPosX + width && dot_y + dot_height >= sPosY && firing && !flipflag)
  	{
  		killed[n] = 1;
  		return 2;
  	}
	else if (!killed[n] && dot_x + dot_width - 100 >= sPosX && dot_x + 150 <= sPosX + width && dot_y + dot_height >= sPosY)
	{
		Mix_PlayChannel( -1, c, 0 );
		return 1;
	}

	return 0;
}

int Snake::getPosX()
{
	return sPosX;
}

int Snake::getPosY()
{
	return sPosY;
}
