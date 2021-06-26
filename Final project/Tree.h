#ifndef TREE_H
#define TREE_H

class Tree
{
	public:
		//Initializes the variables
		Tree();

	//Shows the tree on the screen relative to the camera
	void render(int camX, int camY);
	void setPosition(int x, int y);
	int checkColision(int dot_x, int dot_y, int dot_width, int dot_height);

	//Position accessors
	int getPosX();
	int getPosY();

	private:
		int tPosX, tPosY;
	const int height = 70;
	const int width = 100;
};

#endif
