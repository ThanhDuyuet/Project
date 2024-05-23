#pragma once
#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include"BaseObject.h"
#include<string>
#include<fstream>

const int MAIN_WIDTH = 150;
const int MAIN_HEIGHT = 120;
const int MAX_HP = 5;
const int COORDINATES_X_SCORE = 350;
const int COORDINATES_Y_SCORE = 10;
const int SCORE_HEIGHT = 30;
const int SCORE_WIDTH = 100;
const int SIZE_CUP = 40;
const int SPACE = 20;

class HP {
	SDL_Rect coordinates;
	int Hp;
	SDL_Texture* texture[MAX_HP+1];
public:
	void getDamage() { Hp--; }
	HP();
	~HP();
	void setTextureHP(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer) ;
	bool isOver() { return Hp <= 0; }
	void recover() { Hp = MAX_HP; }
};


class Score :public BaseObject {
	std::string score;
public:
	int point;
	Score();
	~Score();
	void setTextureScore(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer) override;
};

class HighScore :public BaseObject {
	int highScore;
	SDL_Rect coordinatesCup;
	SDL_Texture* cup;
public:
	HighScore();
	~HighScore();
	void setTexture(SDL_Renderer* renderer);
	int getHighScore();
	void recordHighScore();
	void updateTextureHighScore(SDL_Renderer* renderer, int& score);
	void render(SDL_Renderer* renderer) override;
};

class MainObject{	
	//SDL_Texture* textureExplosiveEffect;
	bool isHighScore;
public:
	bool isDied;
	Mix_Chunk* getScoreAudio;
	Mix_Chunk* getBoomAudio;
	Mix_Chunk* getHighScoreAudio;	
	HighScore high_Score;
	int x, y;
	HP hp;
	Score score;
	~MainObject();
	void initializePlayer(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	void setNewTurn();
	//void renderExplosiveEffect(SDL_Renderer* renderer,SDL_Rect rect);
};


#endif