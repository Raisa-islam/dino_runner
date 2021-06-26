#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "LTexture.h"
#include "globals.h"
#include "Dino.h"
#include "Cactus.h"
#include "Ball.h"
#include "Tree.h"
#include "Snake.h"
#include "Rabbit.h"
#include "Diamond.h"
using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 760;
const int game_width = 5000;
const int game_height = 760;

int score = 0;
const int tree_pass = 15;
const int cact_pass = 15;
const int dia_collect = 10;
const int s_killed = 20;
int currentframe;
const int FPS = 30;
const int frameDelay = 500 / FPS;


const int menu = 30;
const int level_changed = 121;
const int game_over = 111;
const int help = 40;
const int scores = 80;
const int RETURN = 90;
const int EXIT = 100;
const int Lock = 23;
const int unlock1 = 22;
const int unlock2 = 24;
const int unlock3 = 25;
const int credit = 29;

int target;
int flag = 0;
int currentLevel = 0;

const int exit_page = 140;
bool init();
bool load_media();
void close();
SDL_Window * Win = NULL;
SDL_Renderer * Renderer = NULL;
TTF_Font * Font = NULL;
SDL_RendererFlip flipType = SDL_FLIP_NONE;
SDL_Rect ball;
SDL_Rect run[4];
SDL_Rect jump[2];
SDL_Rect fire;
SDL_Rect snake[5];
SDL_Rect Rabbit1[5];
SDL_Rect Rabbit2[5];
SDL_Rect textrect;
SDL_Rect rabbit1[6];
SDL_Rect rabbit2[6];

LTexture menuTexture;
LTexture textTexture;
LTexture scoreTexture;
LTexture highestTexture;
LTexture instructionTexture;
LTexture exit_pageTexture;
LTexture game_overTexture;
LTexture game_over2Texrure;
LTexture levlockTexture;
LTexture levelunlockTexture;
LTexture CactusTexture;
LTexture TreeTexture;
LTexture DiamondTexture;
LTexture SnakeTexture;
LTexture BG1Texture;
LTexture BG2Texture;
LTexture BG3Texture;
LTexture BG4Texture;
LTexture RunTexture;
LTexture FireTexture;
LTexture JumpTexture;
LTexture TextTexture;
LTexture BallTexture;
LTexture Rabbit1Texture;
LTexture Rabbit2Texture;

Mix_Music *bg = NULL;
Mix_Chunk *j = NULL;
Mix_Chunk *f = NULL;
Mix_Chunk *c = NULL;
Mix_Chunk *d = NULL;

bool init() {
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }

    //Create window
    Win = SDL_CreateWindow("***DINO RUNNER!***", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (Win == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      //Create vsynced renderer for window
      Renderer = SDL_CreateRenderer(Win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (Renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        //Initialize renderer color
        SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }

        if (TTF_Init() == -1) {
          printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
          success = false;
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
      }
    }
  }

  return success;
}


int getUnlockedLevel() {
  int level;
    FILE* q = fopen("level.txt", "r");
    fscanf(q, "%d", &level);
    fclose(q);
    return level;
}

int getHighScore() {

    int score;
      FILE* q = fopen("highscore.txt", "r");
      fscanf(q, "%d", &score);
      fclose(q);
      return score;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

flag = getUnlockedLevel();

	//Load snake texture
	if (!SnakeTexture.loadFromFile("snake.png"))
	{
		printf("Failed to load snake texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips
		for (int i = 0; i < 5; i++)
		{
			snake[i].x = 75 * i;
			snake[i].y = 0;
			snake[i].w = 75;
			snake[i].h = 194;
		}
	}

	//Load tree texture
	if (!TreeTexture.loadFromFile("treelog.png"))
	{
		printf("Failed to load tree texture!\n");
		success = false;
	}

	//Load cactus texture
	if (!CactusTexture.loadFromFile("cactus.png"))
	{
		printf("Failed to load cactus texture!\n");
		success = false;
	}

	//Load diamond texture
	if (!DiamondTexture.loadFromFile("diamond.png"))
	{
		printf("Failed to load Object texture!\n");
		success = false;
	}
	if( !BallTexture.loadFromFile( "ball.png" ) )
	{
		printf( "Failed to load Object texture!\n" );
		success = false;
	}

	//Load dot texture
	if (!RunTexture.loadFromFile("run.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips
		for (int i = 0; i < 4; i++)
		{
			run[i].x = 484 * i;
			run[i].y = 0;
			run[i].w = 484;
			run[i].h = 280;
		}
	}
	//load jump texture
	if (!JumpTexture.loadFromFile("jump.png"))
	{
		printf("Failed to load jump animation texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips
		for (int i = 0; i < 2; i++)
		{
			jump[i].x = 484 * i;
			jump[i].y = 0;
			jump[i].w = 484;
			jump[i].h = 280;
		}
	}

	//Load background texture
	if (!BG1Texture.loadFromFile("level1.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!BG2Texture.loadFromFile("level2.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!BG3Texture.loadFromFile("level3.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!BG4Texture.loadFromFile("level4.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!FireTexture.loadFromFile("fire.png"))
	{
		printf("Failed to load fire texture!\n");
		success = false;
	}

	Font = TTF_OpenFont("times.ttf", 56);
	if (Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!TextTexture.loadFromRenderedText("Score:" + to_string(score), textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		else
		{
			textrect.x = 1100;
			textrect.y = 50;
			textrect.w = 90;
			textrect.h = 30;
		}
	}
	if( !Rabbit1Texture.loadFromFile( "rabbit1.png" ) )
	{
		printf( "Failed to load Object texture!\n" );
		success = false;
	}
	else {
    //Set sprite clips
    for (int i = 0; i < 6; i++) {
      rabbit1[i].x =  42* i;
      rabbit1[i].y = 0;
      rabbit1[i].w = 42;
      rabbit1[i].h = 70;
    }
    }
    if( !Rabbit2Texture.loadFromFile( "rabbit2.png" ) )
	{
		printf( "Failed to load Object texture!\n" );
		success = false;
	}
	else {
    //Set sprite clips
    for (int i = 0; i < 6; i++) {
      rabbit2[i].x =  39* i;
      rabbit2[i].y = 0;
      rabbit2[i].w = 39;
      rabbit2[i].h = 70;
    }
    }
    //Load music
	bg = Mix_LoadMUS( "level.mp3" );
	if( bg == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	/*bg2 = Mix_LoadMUS( "menu.wav" );
	if( bg2 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	*/
	//Load sound effects
	j = Mix_LoadWAV( "jump.wav" );
	if( j == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	f = Mix_LoadWAV( "fire.wav" );
	if( f == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	c = Mix_LoadWAV( "col.wav" );
	if( c == NULL )
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	d = Mix_LoadWAV( "low.wav" );
	if( d == NULL )
	{
		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	return success;
}

void close() {

//Free the sound effects
	Mix_FreeChunk( j );
	Mix_FreeChunk( f );
	Mix_FreeChunk( c );
	Mix_FreeChunk( d );
	j = NULL;
	f = NULL;
	c = NULL;
	d = NULL;

	//Free the music
	Mix_FreeMusic( bg );
	//Mix_FreeMusic( bg2 );
	//bg2 = NULL;
	bg = NULL;
  //Destroy window
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Win);
  Win = NULL;
  Renderer = NULL;

  //Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
void level2();
void level3();
void level4();

void level1()
{
	bool quit = false;
	Mix_PlayMusic( bg, -1 );

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dino dino;
			Tree tree[4];
			tree[0].setPosition(1650, 600);
			tree[1].setPosition(3000, 600);

			Cactus cact[4];
			cact[0].setPosition(900, 569);
			cact[1].setPosition(4300, 569);

			Diamond dia[20];

			int dx[] = { 500, 600, 700, 900, 1100, 1250, 1400, 1950, 2100, 2500, 2750, 3000, 3300, 3550, 4000, 4150, 4550, 4750 };
			int dy[] = { 550, 550, 550, 380, 550, 380, 380, 380, 380, 550, 380, 380, 550, 550, 380, 380, 550, 380 };

			for (int i = 0; i < 18; i++)
			{
				dia[i].setPosition(i, dx[i], dy[i]);
			}

			Snake snake[4];
			int sx[] = { 2300, 3800 };
			int sy[] = { 500, 500 };

			for (int i = 0; i < 2; i++)
			{
				snake[i].setPosition(i, sx[i], sy[i]);
			}

			//The camera area
			SDL_Rect screen = { 0,
				0,
				SCREEN_WIDTH,
				SCREEN_HEIGHT
			};
			Uint32 frameStart;
			int frameTime;

			//While application is running
			while (!quit)
			{
			 	//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
				 		//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					dino.handleEvent(e);
				}
				frameStart = SDL_GetTicks();
				currentframe = (SDL_GetTicks() / frameDelay) % FPS;

        if(dino.getPosX() + dino.Dino_WIDTH > game_width - 100) {
          currentLevel++;

          printf("%d\n ", currentLevel);

          int x = getUnlockedLevel();
          if( x < currentLevel ) {
              FILE* q = fopen("level.txt", "w");
              fprintf(q, "%d", currentLevel);
              fclose(q);
          }
          target = level_changed;
          quit=true;
        }

				for (int i = 0; i < 2; i++)
				{
					if (tree[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						quit = true;
            			target = game_over;
					}
				}

				for (int i = 0; i < 2; i++)
				{
					if (cact[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						quit = true;
            			target = game_over;
					}
				}

				for (int i = 0; i < 18; i++)
				{
					if (dia[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						score += dia_collect;
						printf("%d\n", score);
					}
				}
				for (int i = 0; i < 2; i++)
				{
					int x = snake[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT, dino.firing, dino.flipflag);
					if (x == 2)
					{
						score += s_killed;
						printf("%d\n", score);
					}
					else if (x == 1)
					{
						quit = true;
                       target = game_over;
					}
				}

				//Move the dot
				//dino.move();

				dino.scrolling(screen);

				//Clear screen
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);

				//Render background
				BG1Texture.render(0, 0, &screen);

				//Render objects
				dino.render(screen.x, screen.y);

				for (int i = 0; i < 2; i++)
				{
					tree[i].render(screen.x, screen.y);
				}

				for (int i = 0; i < 2; i++)
				{
					cact[i].render(screen.x, screen.y);
				}

				for (int i = 0; i < 18; i++)
				{
					dia[i].render(i, screen.x, screen.y);
				}
				for (int i = 0; i < 2; i++)
				{
					snake[i].render(i, screen.x, screen.y);
				}
				TextTexture.loadFromRenderedText("Score:" + to_string(score),
				{
					255, 0, 0 });
				TextTexture.render(1000, 50);
				//Update screen
				SDL_RenderPresent(Renderer);
			}
}

void level2()
{
	//Main loop flag
			bool quit = false;
			Mix_PlayMusic( bg, -1 );

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dino dino;
			Tree tree[4];
			tree[0].setPosition(900, 600);
			tree[1].setPosition(3000, 600);

			Cactus cact[4];
			cact[0].setPosition(1650, 569);
			cact[1].setPosition(4300, 569);

			Diamond dia[20];

			int dx[] = { 500, 600, 700, 900, 1100, 1250, 1400, 1950, 2100, 2500, 2750, 3000, 3400, 3650, 3900, 4150, 4550, 4750 };
			int dy[] = { 550, 550, 550, 380, 550, 380, 380, 380, 380, 550, 380, 380, 550, 550, 380, 380, 550, 380 };

			for (int i = 0; i < 18; i++)
			{
				dia[i].setPosition(i, dx[i], dy[i]);
			}

			Snake snake[4];
			int sx[] = { 830, 2300, 3260, 4230 };
			int sy[] = { 500, 500, 500, 500 };

			for (int i = 0; i < 4; i++)
			{
				snake[i].setPosition(i, sx[i], sy[i]);
			}
			Ball ball[3];
			ball[0].setPosition(0, 1200, 690);
			ball[1].setPosition(1, 3500, 690);
			ball[2].setPosition(2, 5000, 690);
			//ball[3].setPosition(3, 5000, 690);


			//The camera area
			SDL_Rect screen = { 0,
				0,
				SCREEN_WIDTH,
				SCREEN_HEIGHT
			};
			Uint32 frameStart;
			int frameTime;

			//While application is running
			while (!quit)
			{
			 	//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
				 		//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					dino.handleEvent(e);
				}
				frameStart = SDL_GetTicks();
				currentframe = (SDL_GetTicks() / frameDelay) % FPS;

        if(dino.getPosX() + dino.Dino_WIDTH > game_width - 100) {
          currentLevel++;

          printf("%d\n ", currentLevel);

          int x = getUnlockedLevel();
          if( x < currentLevel ) {
              FILE* q = fopen("level.txt", "w");
              fprintf(q, "%d", currentLevel);
              fclose(q);
          }
          target = level_changed;
          quit=true;
        }

				for (int i = 0; i < 2; i++)
				{
					if (tree[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						quit = true;
            target = game_over;
					}
				}

				for (int i = 0; i < 2; i++)
				{
					if (cact[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						quit = true;
            target = game_over;
					}
				}

				for (int i = 0; i < 18; i++)
				{
					if (dia[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						score += dia_collect;
						printf("%d\n", score);
					}
				}
				for (int i = 0; i < 4; i++)
				{
					int x = snake[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT, dino.firing, dino.flipflag);
					if (x == 2)
					{
						score += s_killed;
						printf("%d\n", score);
					}
					else if (x == 1)
					{
						//quit = true;
					}
				}

				for(int i = 0; i < 3; i++)
				{
					ball[i].move();
  						if(ball[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT)) {
  							quit = true;
                target = game_over;
  						}
				}

				dino.scrolling(screen);
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);
				BG2Texture.render(0, 0, &screen);
				for(int i = 0; i < 3; i++) {
					ball[i].render(i, screen.x, screen.y );
				}


				//Render objects
				dino.render(screen.x, screen.y);

				for (int i = 0; i < 2; i++)
				{
					tree[i].render(screen.x, screen.y);
				}

				for (int i = 0; i < 2; i++)
				{
					cact[i].render(screen.x, screen.y);
				}

				for (int i = 0; i < 18; i++)
				{
					dia[i].render(i, screen.x, screen.y);
				}
				for (int i = 0; i < 4; i++)
				{
					snake[i].render(i, screen.x, screen.y);
				}
				TextTexture.loadFromRenderedText("Score:" + to_string(score),
				{
					255, 0, 0 });
				TextTexture.render(1000, 50);
				//Update screen
				SDL_RenderPresent(Renderer);
			}
}

void level3()
{
	//Main loop flag
			bool quit = false;
			Mix_PlayMusic( bg, -1 );

			SDL_Event e;

			Dino dino;
			Tree tree[4];
			tree[0].setPosition(1650, 600);
			tree[1].setPosition(3000, 600);

			Cactus cact[4];
			cact[0].setPosition(900, 569);
			cact[1].setPosition(4300, 569);

			Diamond dia[21];

			int dx[] = { 500, 600, 700, 900, 1100, 1250, 1450, 1650, 1950, 2100, 2350, 2600, 2900, 3150, 3450, 3750, 4300, 4000, 4550, 4750 };
			int dy[] = { 550, 380, 550, 380, 550, 380, 550, 380, 380, 380, 550, 380, 380, 550, 550, 380, 380, 380, 550, 380 };

			for (int i = 0; i < 20; i++)
			{
				dia[i].setPosition(i, dx[i], dy[i]);
			}

			Snake snake[4];
			int sx[] = { 830, 2300, 2900, 4230 };
			int sy[] = { 500, 500, 500, 500 };

			for (int i = 0; i < 4; i++)
			{
				snake[i].setPosition(i, sx[i], sy[i]);
			}

			Rabbit rabbit[4];

			int rx[]={1000, 2200, 3000, 5000};
			int ry[]= {600, 600, 600, 600};

			for(int i=0; i<4; i++)
			{
				rabbit[i].setPosition(rx[i], ry[i]);
			}


			//The camera area
			SDL_Rect screen = { 0,
				0,
				SCREEN_WIDTH,
				SCREEN_HEIGHT
			};
			Uint32 frameStart;
			int frameTime;

			//While application is running
			while (!quit)
			{
			 	//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
				 		//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					dino.handleEvent(e);
				}
				frameStart = SDL_GetTicks();
				currentframe = (SDL_GetTicks() / frameDelay) % FPS;

        if(dino.getPosX() + dino.Dino_WIDTH > game_width - 100) {
          currentLevel++;

          printf("%d\n ", currentLevel);

          int x = getUnlockedLevel();
          if( x < currentLevel ) {
              FILE* q = fopen("level.txt", "w");
              fprintf(q, "%d", currentLevel);
              fclose(q);
          }
          target = level_changed;
          quit=true;
        }

				for (int i = 0; i < 2; i++)
				{
					if (tree[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						quit = true;
            target = game_over;
					}
				}

				for (int i = 0; i < 2; i++)
				{
					if (cact[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						quit = true;
            target = game_over;
					}
				}

				for (int i = 0; i < 20; i++)
				{
					if (dia[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						score += dia_collect;
						printf("%d\n", score);
					}
				}
				for (int i = 0; i < 4; i++)
				{
					int x = snake[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT, dino.firing, dino.flipflag);
					if (x == 2)
					{
						score += s_killed;
						printf("%d\n", score);
					}
					else if (x == 1)
					{
						//quit = true;
					}
				}
				for(int i = 0; i < 4; i++) {
						if(rabbit[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT)) {
							quit = true;
              target = game_over;
						}
				}

				dino.scrolling(screen);

				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);
				BG3Texture.render(0, 0, &screen);
				for(int i = 0; i<4; i++)
				{
					rabbit[i].move();
				}
				dino.render(screen.x, screen.y);

				for (int i = 0; i < 2; i++)
				{
					tree[i].render(screen.x, screen.y);
				}

				for (int i = 0; i < 2; i++)
				{
					cact[i].render(screen.x, screen.y);
				}

				for (int i = 0; i < 20; i++)
				{
					dia[i].render(i, screen.x, screen.y);
				}
				for (int i = 0; i < 4; i++)
				{
					snake[i].render(i, screen.x, screen.y);
				}
				for(int i = 0; i < 4; i++) {
					rabbit[i].render(screen.x, screen.y );
				}
				TextTexture.loadFromRenderedText("Score:" + to_string(score),
				{
					255, 0, 0 });
				TextTexture.render(1000, 50);
				//Update screen
				SDL_RenderPresent(Renderer);
			}
}

void level4()
{
	//Main loop flag
			bool quit = false;
			Mix_PlayMusic( bg, -1 );

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dino dino;
			Tree tree[4];
			tree[0].setPosition(900, 600);
			tree[1].setPosition(3000, 600);

			Cactus cact[4];
			cact[0].setPosition(1650, 569);
			cact[1].setPosition(4300, 569);

			Diamond dia[20];

			int dx[] = { 500, 600, 700, 900, 1100, 1250, 1400, 1950, 2100, 2500, 2750, 3000, 3300, 3550, 4000, 4150, 4550, 4750 };
			int dy[] = { 550, 550, 550, 380, 550, 380, 380, 380, 380, 550, 380, 380, 550, 550, 380, 380, 550, 380 };

			for (int i = 0; i < 18; i++)
			{
				dia[i].setPosition(i, dx[i], dy[i]);
			}

			Snake snake[4];
			int sx[] = { 830, 2300, 4230 };
			int sy[] = { 500, 500, 500 };

			for (int i = 0; i < 3; i++)
			{
				snake[i].setPosition(i, sx[i], sy[i]);
			}
			Ball ball[4];
			ball[0].setPosition(0, 1600, 690);
			ball[1].setPosition(1, 3000, 690);
			ball[2].setPosition(2, 5000, 690);

			Rabbit rabbit[4];

			int rx[]={1000, 2200, 3000, 5000};
			int ry[]= {620, 620, 620, 620};

			for(int i=0; i<4; i++)
			{
				rabbit[i].setPosition(rx[i], ry[i]);
			}


			//The camera area
			SDL_Rect screen = { 0,
				0,
				SCREEN_WIDTH,
				SCREEN_HEIGHT
			};
			Uint32 frameStart;
			int frameTime;

			//While application is running
			while (!quit)
			{
			 	//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
				 		//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					dino.handleEvent(e);
				}
				frameStart = SDL_GetTicks();
				currentframe = (SDL_GetTicks() / frameDelay) % FPS;

        if(dino.getPosX() + dino.Dino_WIDTH > game_width - 100) {
          currentLevel++;

          printf("%d\n ", currentLevel);

          int x = getUnlockedLevel();
          target = level_changed;
          quit=true;
        }

				for (int i = 0; i < 2; i++)
				{
					if (tree[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						quit = true;
            target = game_over;
					}
				}

				for (int i = 0; i < 2; i++)
				{
					if (cact[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						quit = true;
            target = game_over;
					}
				}

				for (int i = 0; i < 18; i++)
				{
					if (dia[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT))
					{
						score += dia_collect;
						printf("%d\n", score);
					}
				}
				for (int i = 0; i < 3; i++)
				{
					int x = snake[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT, dino.firing, dino.flipflag);
					if (x == 2)
					{
						score += s_killed;
						printf("%d\n", score);
					}
					else if (x == 1)
					{
						//quit = true;
					}
				}
				for(int i = 0; i < 3; i++) {
						if(ball[i].checkColision(i, dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT)) {
							quit = true;
              target = game_over;
							// TODO: Collision Code Here
						}
				}
				for(int i=0; i<3; i++)
				{
					ball[i].move();
				}
				for(int i = 0; i < 4; i++) {
						if(rabbit[i].checkColision(dino.getPosX(), dino.getPosY(), dino.Dino_WIDTH, dino.Dino_HEIGHT)) {
							quit = true;
              target = game_over;
						}
				}

				dino.scrolling(screen);

				//Clear screen
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);

				//Render background
				BG4Texture.render(0, 0, &screen);
				for(int i = 0; i<4; i++)
				{
					rabbit[i].move();
				}
				for(int i = 0; i < 3; i++) {
					ball[i].render(i, screen.x, screen.y );
				}

				//Render objects
				dino.render(screen.x, screen.y);

				for (int i = 0; i < 2; i++)
				{
					tree[i].render(screen.x, screen.y);
				}

				for (int i = 0; i < 2; i++)
				{
					cact[i].render(screen.x, screen.y);
				}

				for (int i = 0; i < 18; i++)
				{
					dia[i].render(i, screen.x, screen.y);
				}
				for (int i = 0; i < 3; i++)
				{
					snake[i].render(i, screen.x, screen.y);
				}
				for(int i = 0; i < 4; i++) {
					rabbit[i].render(screen.x, screen.y );
				}
				TextTexture.loadFromRenderedText("Score:" + to_string(score),
				{
					255, 0, 0 });
				TextTexture.render(1000, 50);
				//Update screen
				SDL_RenderPresent(Renderer);
			}
}

int option_no = 0;

SDL_Rect l1, l2, l3, l4;
void lock_rects()
{
	l1.x = 493;
	l1.y = 80;
	l1.h = 70;
	l1.w = 254;

	l2.x = 496;
	l2.y = 253;
	l2.h = 64;
	l2.w = 261;

	l3.x = 503;
	l3.y = 420;
	l3.h = 64;
	l3.w = 260;

	l4.x = 509;
	l4.y = 599;
	l4.h = 64;
	l4.w = 260;

	if (option_no == 8) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l1);
  }

  if (option_no == 9) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l2);
  }

  if (option_no == 10) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l3);
  }

  if (option_no == 11) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l4);
  }
}

SDL_Rect l_1, l_2, l_3, l_4;
void unlock_rects()
{
	l_1.x = 493;
	l_1.y = 80;
	l_1.h = 63;
	l_1.w = 254;

	l_2.x = 493;
	l_2.y = 254;
	l_2.h = 60;
	l_2.w = 263;

	l_3.x = 503;
	l_3.y = 421;
	l_3.h = 64;
	l_3.w = 260;

	l_4.x = 509;
	l_4.y = 600;
	l_4.h = 64;
	l_4.w = 261;

	if (option_no == 12) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_1);
  }

  if (option_no == 13) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_2);
  }

  if (option_no == 14) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_3);
  }

  if (option_no == 15) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_4);
  }
}

SDL_Rect l_12, l_22, l_32, l_42;
void unlock2_rects()
{
	l_12.x = 496;
	l_12.y = 80;
	l_12.h = 63;
	l_12.w = 250;

	l_22.x = 495;
	l_22.y = 254;
	l_22.h = 64;
	l_22.w = 260;

	l_32.x = 504;
	l_32.y = 420;
	l_32.h = 60;
	l_32.w = 257;

	l_42.x = 506;
	l_42.y = 600;
	l_42.h = 60;
	l_42.w = 260;

	if (option_no == 16) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_12);
  }

  if (option_no == 17) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_22);
  }

  if (option_no == 18) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_32);
  }

  if (option_no == 19) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_42);
  }
}

SDL_Rect l_13, l_23, l_33, l_43;
void unlock3_rects()
{
	l_13.x = 495;
	l_13.y = 84;
	l_13.h = 60;
	l_13.w = 252;

	l_23.x = 495;
	l_23.y = 254;
	l_23.h = 60;
	l_23.w = 263;

	l_33.x = 503;
	l_33.y = 421;
	l_33.h = 60;
	l_33.w = 260;

	l_43.x = 508;
	l_43.y = 600;
	l_43.h = 60;
	l_43.w = 260;

	if (option_no == 20) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_13);
  }

  if (option_no == 21) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_23);
  }

  if (option_no == 22) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_33);
  }

  if (option_no == 23) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & l_43);
  }
}
SDL_Rect yes, no;

void exit_rects()
{
	yes.x = 204;
	yes.y = 410;
	yes.h = 150;
	yes.w = 250;

	no.x = 720;
	no.y = 410;
	no.h = 150;
	no.w = 250;

	if (option_no == 6) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & yes);
  }

  if (option_no == 7) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & no);
  }


}
SDL_Rect option_1, option_2, option_3, option_4, option_5;

void menu_rects() {

  option_1.x = 475;
  option_1.y = 209;
  option_1.h = 73;
  option_1.w = 345;

  option_2.x = 440;
  option_2.y = 318;
  option_2.h = 84;
  option_2.w = 440;

  option_3.x = 445;
  option_3.y = 440;
  option_3.h = 78;
  option_3.w = 418;

  option_4.x = 499;
  option_4.y = 552;
  option_4.h = 82;
  option_4.w = 292;

  option_5.x = 550;
  option_5.y = 658;
  option_5.h = 83;
  option_5.w = 190;

  if (option_no == 1) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & option_1);
  }

  if (option_no == 2) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & option_2);
  }

  if (option_no == 3) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & option_3);
  }

  if (option_no == 4) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & option_4);
  }

  if (option_no == 5) {
    SDL_SetRenderDrawColor(Renderer, 0xFF, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, & option_5);
  }

}


void game_over_rects() {
  option_1 = option_2 = option_3 = option_4 = option_5 = {0, 0, 0, 0};
}

int main(int argc, char * args[]) {
  int level_swap;

  if (!init()) {
    printf("FAILED TO INITIALIZE!!\n");
  }
  else{
  if(!loadMedia())
  {
  	printf("FAILED TO LOAD MEDIA!!");
  }
  else{
    if (!menuTexture.loadFromFile("menu.png")) {
      printf("FAILED TO LOAD MEDIA!!\n");
    } else {
      int start_game;
      bool quit = false;
      target = menu;

      SDL_Event e;

      SDL_Rect camera = {
        0,
        0,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
      };
      Uint32 frame_start;
      int frame_time;


      while (!quit) {
        start_game = 0;

        while (target != EXIT) {
          SDL_RenderClear(Renderer);
          menuTexture.render(0, 0);
          if (target == menu) {
            Mix_HaltMusic();
            menu_rects();
            menuTexture.loadFromFile("menu.png");
          }

          if (target == scores) {
            menuTexture.loadFromFile("score.png");
            int high = getHighScore();
            TextTexture.loadFromRenderedText("Highest Score: " + to_string(high),
            {
              255, 0, 0 });
            TextTexture.render(500, 350);
          }

          if (target == game_over) {
            game_over_rects();
            int high = getHighScore();
            if(high < score) {

                  FILE* q = fopen("highscore.txt", "w");
                  fprintf(q, "%d", score);
                  fclose(q);
            }
            menuTexture.loadFromFile("gameOver.png");

    				TextTexture.loadFromRenderedText(to_string(score),
    				{
    					255, 0, 0 });
    				TextTexture.render(750, 520);
          }

          if (target == level_changed) {
            printf("Here");
              printf("%d\n", currentLevel);
            game_over_rects();
            if(currentLevel == 1) level2();
            if(currentLevel == 2) level3();
            if(currentLevel == 3) level4();
            if(currentLevel == 4) {menuTexture.loadFromFile("gameWin.png");

    				TextTexture.loadFromRenderedText(to_string(score),
    				{
    					255, 0, 0 });
    				TextTexture.render(750, 550);
          }
          }

          if(target == RETURN)
          {
            Mix_HaltMusic();
          	exit_rects();
          	menuTexture.loadFromFile("exit_page.png");
          }
	   if(target == Lock)
	   {
	   	//Mix_HaltMusic();
	   	lock_rects();
	   	 menuTexture.loadFromFile("lock.png");
	   }
	   if(target == unlock1)
	   {
	    //Mix_HaltMusic();
	   	unlock_rects();
	   	 menuTexture.loadFromFile("unlock1.png");
	   }
	    if(target == unlock2)
	   {
	     //Mix_HaltMusic();
	   	unlock2_rects();
	   	 menuTexture.loadFromFile("unlock2.png");
	   }
	    if(target == unlock3)
	   {
	    //Mix_HaltMusic();
	   	unlock3_rects();
	   	 menuTexture.loadFromFile("unlock3.png");
	   }
          while (SDL_PollEvent( & e) != 0) {
            if (e.type == SDL_QUIT)
            {
              quit = true; // cmnt krt hbe
              /*level_swap = target;
              target = RETURN;*/
              target = EXIT;
            }

            if( e.type == SDL_KEYDOWN)
    			{

        			switch( e.key.keysym.sym )
        			{
            			case SDLK_ESCAPE:
            			{
               				target = menu;

               				break;
            			}
              		}
           	 	}

            if (e.button.x > option_1.x && e.button.x < option_1.x + option_1.w && e.button.y > option_1.y && e.button.y < option_1.y + option_1.h)
            {
              option_no = 1;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              		if(flag == 0)
              		{
              			target = Lock;
              		}
              		else if(flag == 1)
              		{
              			target = unlock1;
              		}
              		else if(flag == 2)
              		{
              			target = unlock2;
              		}
              		else if(flag == 3)
              		{
              			target = unlock3;
              		}
              }
            }

            if (e.button.x > option_2.x && e.button.x < option_2.x + option_2.w && e.button.y > option_2.y && e.button.y < option_2.y + option_2.h)
            {
              option_no = 2;
              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0) {
                target = scores;
              }
            }

            if (e.button.x > option_3.x && e.button.x < option_3.x + option_3.w && e.button.y > option_3.y && e.button.y < option_3.y + option_3.h)
            {
              option_no = 3;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0) {

                target = help;
                menuTexture.loadFromFile("instruction.png");
              }
            }

            if (e.button.x > option_4.x && e.button.x < option_4.x + option_4.w && e.button.y > option_4.y && e.button.y < option_4.y + option_4.h)
            {
              option_no = 4;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {

                target = credit;
                menuTexture.loadFromFile("credit.png");
           	 }
           	}

            if (e.button.x > option_5.x && e.button.x < option_5.x + option_5.w && e.button.y > option_5.y && e.button.y < option_5.y + option_5.h)
            {
              option_no = 5;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0) {
              	level_swap = target;
                target = RETURN;
              }

            }

            if (e.button.x > yes.x && e.button.x < yes.x + yes.w && e.button.y > yes.y && e.button.y < yes.y + yes.h)
            {
              option_no = 6;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
				  target = EXIT;
				  quit = true;
              }
            }

            if (e.button.x > no.x && e.button.x < no.x + no.w && e.button.y > no.y && e.button.y < no.y + no.h)
            {
              option_no = 7;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              	target = level_swap;
              }
            }

            if (e.button.x > l1.x && e.button.x < l1.x + l1.w && e.button.y > l1.y && e.button.y < l1.y + l1.h)
            {
              option_no = 8;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 0;
              		level1();
              }

            }

            if (e.button.x > l2.x && e.button.x < l2.x + l2.w && e.button.y > l2.y && e.button.y < l2.y + l2.h)
            {
              option_no = 9;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              }

            }

            if (e.button.x > l3.x && e.button.x < l3.x + l3.w && e.button.y > l3.y && e.button.y < l3.y + l3.h)
            {
              option_no = 10;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              }
            }

            if (e.button.x > l4.x && e.button.x < l4.x + l4.w && e.button.y > l4.y && e.button.y < l4.y + l4.h)
            {
              option_no = 11;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              }
            }

            if (e.button.x > l_1.x && e.button.x < l_1.x + l_1.w && e.button.y > l_1.y && e.button.y < l_1.y + l_1.h)
            {
              option_no = 12;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {

                currentLevel = 0;
              		level1();
              }
            }

            if (e.button.x > l_2.x && e.button.x < l_2.x + l_2.w && e.button.y > l_2.y && e.button.y < l_2.y + l_2.h)
            {
              option_no = 13;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 1;
				  level2();
              }
            }

            if (e.button.x > l_3.x && e.button.x < l_3.x + l_3.w && e.button.y > l_3.y && e.button.y < l_3.y + l_3.h)
            {
              option_no = 14;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              }

            }

            if (e.button.x > l_4.x && e.button.x < l_4.x + l_4.w && e.button.y > l_4.y && e.button.y < l_4.y + l_4.h)
            {
              option_no = 15;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              }

            }

            if (e.button.x > l_12.x && e.button.x < l_12.x + l_12.w && e.button.y > l_12.y && e.button.y < l_12.y + l_12.h)
            {
              option_no = 16;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 0;
              			level1();
              }
            }

            if (e.button.x > l_22.x && e.button.x < l_22.x + l_22.w && e.button.y > l_22.y && e.button.y < l_22.y + l_22.h)
            {
              option_no = 17;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 1;
				  level2();
              }
            }

            if (e.button.x > l_32.x && e.button.x < l_32.x + l_32.w && e.button.y > l_32.y && e.button.y < l_32.y + l_32.h)
            {
              option_no = 18;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 2;
				  level3();
              }

              printf("%d  %d \n", e.button.x, e.button.y);
            }

            if (e.button.x > l_42.x && e.button.x < l_42.x + l_42.w && e.button.y > l_42.y && e.button.y < l_42.y + l_42.h)
            {
              option_no = 19;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              }
            }

            if (e.button.x > l_13.x && e.button.x < l_13.x + l_13.w && e.button.y > l_13.y && e.button.y < l_13.y + l_13.h)
            {
              option_no = 20;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 0;
				  level1();
              }
            }

            if (e.button.x > l_23.x && e.button.x < l_23.x + l_23.w && e.button.y > l_23.y && e.button.y < l_23.y + l_23.h)
            {
              option_no = 21;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 1;
				  level2();
              }
            }

            if (e.button.x > l_33.x && e.button.x < l_33.x + l_33.w && e.button.y > l_33.y && e.button.y < l_33.y + l_33.h)
            {
              option_no = 22;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 2;
				  level3();
              }
            }

            if (e.button.x > l_43.x && e.button.x < l_43.x + l_43.w && e.button.y > l_43.y && e.button.y < l_43.y + l_43.h)
            {
              option_no = 23;

              if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
              {
              currentLevel = 3;
				  level4();
              }
            }
          }
          SDL_RenderPresent(Renderer);
        }
        }
      }
    }
  }
  close();
  return 0;

}
