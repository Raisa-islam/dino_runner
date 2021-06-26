#ifndef DIAMOND_H
#define DIAMOND_H

class Diamond
{
	public:
		//Initializes the variables
		Diamond();

	//Shows the diamond on the screen relative to the camera
	void render(int n, int camX, int camY);
	void setPosition(int n, int x, int y);
	int checkColision(int i, int dot_x, int dot_y, int dot_width, int dot_height);
	int collected[50] = { 0 };

	//Position accessors
	int getPosX();
	int getPosY();

	private:
		int dPosX, dPosY;
	const int height = 50;
	const int width = 50;
};

#endif
