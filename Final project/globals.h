#ifndef GLOBALS_H
#define GLOBALS_H

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "LTexture.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int game_width;
extern const int game_height;

extern int score;
extern const int tree_pass;
extern const int cact_pass;
extern const int dia_collect;
extern const int s_killed;
extern int currentframe;
extern const int FPS;
extern const int frameDelay;


extern const int menu;
extern const int level_changed;
extern const int game_over;
extern const int help;
extern const int scores;
extern const int RETURN;
extern const int EXIT;
extern const int Lock;
extern const int unlock1;
extern const int unlock2;
extern const int unlock3;
extern const int credit;

extern int target;
extern int flag;
extern int currentLevel;

extern const int exit_page;
extern SDL_Window * Win;
extern SDL_Renderer * Renderer;
extern TTF_Font * Font;
extern SDL_RendererFlip flipType;
extern SDL_Rect ball;
extern SDL_Rect run[4];
extern SDL_Rect jump[2];
extern SDL_Rect fire;
extern SDL_Rect snake[5];
extern SDL_Rect Rabbit1[5];
extern SDL_Rect Rabbit2[5];
extern SDL_Rect textrect;
extern SDL_Rect rabbit1[6];
extern SDL_Rect rabbit2[6];


extern LTexture menuTexture;
extern LTexture textTexture;
extern LTexture scoreTexture;
extern LTexture highestTexture;
extern LTexture instructionTexture;
extern LTexture exit_pageTexture;
extern LTexture game_overTexture;
extern LTexture game_over2Texrure;
extern LTexture levlockTexture;
extern LTexture levelunlockTexture;
extern LTexture CactusTexture;
extern LTexture TreeTexture;
extern LTexture DiamondTexture;
extern LTexture SnakeTexture;
extern LTexture BG1Texture;
extern LTexture BG2Texture;
extern LTexture BG3Texture;
extern LTexture BG4Texture;
extern LTexture RunTexture;
extern LTexture FireTexture;
extern LTexture JumpTexture;
extern LTexture TextTexture;
extern LTexture BallTexture;
extern LTexture Rabbit1Texture;
extern LTexture Rabbit2Texture;

extern Mix_Chunk *j;
extern Mix_Chunk *f;
extern Mix_Chunk *d;
extern Mix_Chunk *c;


#endif
