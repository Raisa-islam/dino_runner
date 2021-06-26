#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
	public:
		//Initializes the variables
		Snake();

	//Shows the dot on the screen relative to the camera
	void render(int n, int camX, int camY);
	void setPosition(int n, int x, int y);
	int checkColision(int n, int dot_x, int dot_y, int dot_width, int dot_height, int firing, int flipflag);
	int killed[50] = { 0 };

	//Position accessors
	int getPosX();
	int getPosY();

	private:
		int sPosX, sPosY;
	const int height = 194;
	const int width = 75;
};

#endif
