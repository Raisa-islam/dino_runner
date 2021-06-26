#ifndef BALL_H
#define BALL_H


class Ball
{
    public:
		//Initializes the variables
		Ball();

		//Shows the dot on the screen relative to the camera
		void render(int n, int camX, int camY );
		void setPosition(int n, int x, int y );
		int checkColision(int i, int dot_x, int dot_y, int dot_width, int dot_height);
		int killed[20]={0};

		void move();
		int r_velx = -5;
		int r_vely = -5;
		//Position accessors
		int getPosX();
		int getPosY();

    private:
		int rPosX, rPosY;
		const int height = 60;
		const int width = 60;
};

#endif
