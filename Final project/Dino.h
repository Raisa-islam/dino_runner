#ifndef DINO_H
#define DINO_H

class Dino
{
	public:
	static const int Dino_WIDTH = 484;
	static const int Dino_HEIGHT = 280;
	static const int Dino_VEL = 10;

	Dino();

	void handleEvent(SDL_Event & e);
	void scrolling(SDL_Rect & screen);
	void move();
	int flipflag = 0;
	int firing = 0;

	void render(int camX, int camY);
	int Yi;

	int jumpState = 0;

	int getPosX();
	int getPosY();

	private:
		int mPosX, mPosY;

	float mVelX, mVelY;
};


#endif
