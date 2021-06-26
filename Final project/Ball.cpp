#include "Ball.h"
#include "globals.h"

Ball::Ball()
{
    rPosX = -100;
    rPosY = -100;
}

void Ball::move()
{
		if(rPosX <= 0)
		{
			rPosX = 0;
			r_velx = -r_velx;
		}
		if(rPosY >= game_height-70)
		{
			rPosY = game_height-70;
			r_vely = -r_vely;
		}
		if(rPosX >= game_width-70)
		{
			rPosX = game_width-70;
			r_velx = -r_velx;
		}
		if(rPosY <= 480)
		{
			rPosY = 480;
			r_vely = -r_vely;
		}

		rPosX += r_velx;
		rPosY += r_vely;
}
void Ball::render(int n, int camX, int camY )
{
	if(!killed[n])
	{
		//SDL_Rect * currentClip = & rabbit;
		BallTexture.render( rPosX - camX, rPosY - camY );
	}
}

void Ball::setPosition(int n, int x, int y )
{
   killed[n] = 0;
   rPosX = x;
   rPosY = y;
}

int Ball::checkColision(int i, int dot_x, int dot_y, int dot_width, int dot_height)
{
	if(!killed[i])
	{
		if(dot_x + dot_width - 200 >= rPosX && dot_x + 230 <= rPosX + width && dot_y + dot_height  >= rPosY && dot_y + 230 <= rPosY + height) {/*!collected[n] && dot_x + dot_width - 100 >= dPosX && dot_x + 100 <= dPosX + width && dot_y + dot_height - 40 >= dPosY && dot_y + 100 <= dPosY + height*/
     
     		 Mix_PlayChannel( -1, c, 0 );
      		return 1;
    		}	
	}

	return 0;
}


int Ball::getPosX()
{
	return rPosX;
}

int Ball::getPosY()
{
	return rPosY;
}
