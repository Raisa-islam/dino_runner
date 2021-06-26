#include "Rabbit.h"
#include "globals.h"

Rabbit::Rabbit()
{
    rPosX = -100;
    rPosY = -100;
}

void Rabbit::move()
{
		if(rPosX <= 0)
		{
			rPosX = 0;
			r_velx = -r_velx;
		}
		if(rPosX >= game_width-70)
		{
			rPosX = game_width-70;
			r_velx = -r_velx;
		}

		rPosX += r_velx;
}
void Rabbit::render( int camX, int camY )
{
		if(r_velx>0)
		{
			SDL_Rect *currentClip = &rabbit1[(currentframe / 12) % 6];
			Rabbit1Texture.render( rPosX - camX, rPosY - camY, currentClip, 0, NULL );
		}
		else if(r_velx<0)
		{
			SDL_Rect *currentClip = &rabbit2[(currentframe / 12) % 6];
			Rabbit2Texture.render( rPosX - camX, rPosY - camY, currentClip, 0, NULL );
		}

}

void Rabbit::setPosition(int x, int y )
{
   //killed[n] = 0;
   rPosX = x;
   rPosY = y;
}

int Rabbit::checkColision(int dot_x, int dot_y, int dot_width, int dot_height)
{


		if(dot_x + dot_width - 200 >= rPosX && dot_x + 230 <= rPosX + width && dot_y + dot_height  >= rPosY && dot_y + 200 <= rPosY + height)
		{
			Mix_PlayChannel( -1, c, 0 );
			return 1;
		}

	return 0;
}


int Rabbit::getPosX()
{
	return rPosX;
}

int Rabbit::getPosY()
{
	return rPosY;
}
