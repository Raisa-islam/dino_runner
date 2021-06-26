#ifndef RABBIT_H
#define RABBIT_H

class Rabbit
{
    public:
		//Initializes the variables
		Rabbit();

		//Shows the dot on the screen relative to the camera
		void render(int camX, int camY );
		void setPosition(int x, int y );
		int checkColision(int dot_x, int dot_y, int dot_width, int dot_height);
		//int killed[20]={0};

		void move();
		int r_velx = -5;
		//int r_vely = -5;
		//Position accessors
		int getPosX();
		int getPosY();

    private:
		int rPosX, rPosY;
		const int height = 70;
		const int width = 42;
};

#endif
