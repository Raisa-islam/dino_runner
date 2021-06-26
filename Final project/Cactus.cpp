#include "globals.h"
#include "Cactus.h"
Cactus::Cactus()
{
	cPosX = -100;
	cPosY = -100;
}

void Cactus::render(int camX, int camY)
{
	CactusTexture.render(cPosX - camX, cPosY - camY);
}

void Cactus::setPosition(int x, int y)
{
	cPosX = x;
	cPosY = y;
}

int Cactus::checkColision(int dot_x, int dot_y, int dot_width, int dot_height)
{
	if (dot_x + dot_width - 150 >= cPosX && dot_x + 200 <= cPosX + width && dot_y + dot_height - 40 >= cPosY && dot_y + 40 <= cPosY + height)
	{
	    Mix_PlayChannel( -1, c, 0 );
		return 1;
	}
	else
	{
		return 0;
	}
}

int Cactus::getPosX()
{
	return cPosX;
}

int Cactus::getPosY()
{
	return cPosY;
}
