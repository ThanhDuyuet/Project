#pragma once
#ifndef MENUGAME_H
#define MENUGAME_H

#include"BaseObject.h"
#include<string>

const int PLAY = 8;
const int HELP = 12;
const int EXIT = -1;
const int OUT = 2;
class MenuGame :public BaseObject {
	bool gameOver;	
	SDL_Texture* textureHelp;
	SDL_Texture* textureGameOver;

public:
	Mix_Chunk* gameOverAudio;
	int status;
	~MenuGame();
	void initializeMenuGame(SDL_Renderer* renderer);
	int getStatus() { return status; }
	void render(SDL_Renderer* renderer) override;
	void handInputAction(bool& quit);
	void inputActionGameOver(bool& quit);
	bool exitHelp();
};



#endif