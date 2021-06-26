#ifndef CACTUS_H
#define CACTUS_H

class Cactus
{
	public:
		//Initializes the variables
		Cactus();

	//Shows the cactus on the screen relative to the camera
	void render(int camX, int camY);
	void setPosition(int x, int y);
	int checkColision(int dot_x, int dot_y, int dot_width, int dot_height);

	//Position accessors
	int getPosX();
	int getPosY();

	private:
		int cPosX, cPosY;
	const int height = 100;
	const int width = 70;
};


#endif
