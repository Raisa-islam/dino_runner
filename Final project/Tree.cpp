#include "Tree.h"
#include "globals.h"

Tree::Tree()
{
	tPosX = -100;
	tPosY = -100;
}

void Tree::render(int camX, int camY)
{
	TreeTexture.render(tPosX - camX, tPosY - camY);
}

void Tree::setPosition(int x, int y)
{
	tPosX = x;
	tPosY = y;
}

int Tree::checkColision(int dot_x, int dot_y, int dot_width, int dot_height)
{
	if (dot_x + dot_width - 150 >= tPosX && dot_x + 200 <= tPosX + width && dot_y + dot_height >= tPosY && dot_y <= tPosY + height)
	{
		Mix_PlayChannel( -1, c, 0 );
		return 1;
	}
	else
	{
		return 0;
	}
}

int Tree::getPosX()
{
	return tPosX;
}

int Tree::getPosY()
{
	return tPosY;
}
