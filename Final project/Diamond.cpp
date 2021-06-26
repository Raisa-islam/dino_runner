#include "Diamond.h"
#include "globals.h"

Diamond::Diamond()
{
	dPosX = -100;
	dPosY = -100;
}

void Diamond::render(int n, int camX, int camY)
{
	if (!collected[n])
	{
		DiamondTexture.render(dPosX - camX, dPosY - camY);
	}
}

void Diamond::setPosition(int n, int x, int y)
{
	collected[n] = 0;
	dPosX = x;
	dPosY = y;
}

int Diamond::checkColision(int n, int dot_x, int dot_y, int dot_width, int dot_height)
{
	if (!collected[n] && dot_x + dot_width - 100 >= dPosX && dot_x + 100 <= dPosX + width && dot_y + dot_height - 40 >= dPosY && dot_y + 100 <= dPosY + height)
	{
		Mix_PlayChannel( -1, d, 0 );
		collected[n] = 1;
		return 1;
	}
	return 0;
}

int Diamond::getPosX()
{
	return dPosX;
}

int Diamond::getPosY()
{
	return dPosY;
}
