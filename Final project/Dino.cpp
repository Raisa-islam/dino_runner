#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Dino.h"
#include "globals.h"

Dino::Dino()
{
	mPosX = 0;
	mPosY = (int) SCREEN_HEIGHT *.55;
	Yi = (int) SCREEN_HEIGHT *.55;

	mVelX = 0;
	mVelY = 0;
}

void Dino::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
				Mix_PlayChannel( -1, j, 0 );
				if (mPosY >= Yi)
				{
					mVelY = -27;
				}
				break;
			case SDLK_LEFT:
				mVelX -= Dino_VEL;
				break;
			case SDLK_RIGHT:
				mVelX += Dino_VEL;
				break;
			case SDLK_f:
				Mix_PlayChannel( -1, f, 0 );
				firing = 1;
				break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
				mVelX = 0;
				break;
			case SDLK_RIGHT:
				mVelX = 0;
				break;
			case SDLK_f:
				firing = 0;
				break;
		}
	}
}

void Dino::scrolling(SDL_Rect & screen)
{
	screen.x = (getPosX() + Dino::Dino_WIDTH / 2) - SCREEN_WIDTH / 2;
	screen.y = (getPosY() + Dino::Dino_HEIGHT / 2) - SCREEN_HEIGHT / 2;
	if (screen.x < 0)
	{
		screen.x = 0;
	}
	if (screen.y < 0)
	{
		screen.y = 0;
	}
	if (screen.x > game_width - screen.w)
	{
		screen.x = game_width - screen.w;
	}
	if (screen.y > game_height - screen.h)
	{
		screen.y = game_height - screen.h;
	}
}

void Dino::render(int camX, int camY)
{

	if (mVelX > 0 && !firing)
	{
		if (flipflag == 1)
		{
			flipType = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			flipType = SDL_FLIP_NONE;
		}

		SDL_Rect *currentClip = &run[(currentframe / 5) % 4];

		RunTexture.render(mPosX - camX, mPosY - camY, currentClip, 0, NULL, flipType);

		mPosX += mVelX;

		if ((mPosX < 0) || (mPosX + Dino_WIDTH > game_width))
		{
			mPosX -= mVelX;
		}
	}
	if (mVelX < 0 && !firing)
	{
		if (flipflag == 0) flipType = SDL_FLIP_HORIZONTAL;
		else flipType = SDL_FLIP_NONE;

		SDL_Rect * currentClip;
		if (mPosY >= Yi)
			currentClip = &run[(currentframe / 5) % 4];
		else currentClip = &jump[0];

		if (!firing) RunTexture.render(mPosX - camX, mPosY - camY, currentClip, 0, NULL, flipType);

		mPosX += mVelX;

		if ((mPosX < 0) || (mPosX + Dino_WIDTH > game_width))
		{
			mPosX -= mVelX;
		}
	}

	if (mVelX == 0.0 && mPosY == Yi)
	{
		SDL_Rect *currentClip = &run[0];

		if (!firing)
			RunTexture.render(mPosX - camX, mPosY - camY, currentClip, 0, NULL, flipType);
	}
	if (mVelY < 0)
	{
		mPosY += mVelY;
		SDL_Rect *currentClip = &jump[0];
		if (mVelY >= -1) mVelY = 1;
		mVelY += 1;
		if (!firing)
			JumpTexture.render(mPosX - camX, mPosY - camY, currentClip, 0, NULL, flipType);
	}
	if (mVelY > 0)
	{
		SDL_Rect *currentClip = &jump[1];
		mPosY += mVelY;
		if (!firing)
			JumpTexture.render(mPosX - camX, mPosY - camY, currentClip, 0, NULL, flipType);

		mPosY += mVelY;
		mVelY += .5;

		if (mPosY > Yi)
		{
			mPosY = Yi;
			mVelY = 0.0;
		}
	}
	if (firing)
	{
		SDL_Rect *currentClip = &jump[1];
		// JumpTexture.render(mPosX - camX, mPosY - camY, currentClip, 0, NULL, flipType);
		FireTexture.render(mPosX - camX, mPosY - camY, &jump[0], 0, NULL, flipType);
	}
}

int Dino::getPosX()
{
	return mPosX;
}

int Dino::getPosY()
{
	return mPosY;
}
