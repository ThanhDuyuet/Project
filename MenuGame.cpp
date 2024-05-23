
#include"MenuGame.h"

void MenuGame::initializeMenuGame(SDL_Renderer* renderer) {
	coordinates.x = 0;
	coordinates.y = 0;
	texture = loadImage("Image\\MenuGame.png", renderer);
	textureHelp = loadImage("image\\Instruction.png", renderer);
	textureGameOver = loadImage("Image\\GameOver.png", renderer);
	status = 1;
	gameOver = false;
	gameOverAudio = loadAudio("Audio\\GameOverAudio.wav");
}

MenuGame::~MenuGame() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	
	if (textureHelp != nullptr) {
		SDL_DestroyTexture(textureHelp);
		textureHelp = nullptr;
	}
	
	if (textureGameOver != nullptr) {
		SDL_DestroyTexture(textureGameOver);
		textureGameOver = nullptr;
	}
	
	Mix_FreeChunk(gameOverAudio);
	gameOverAudio = nullptr;
}


void MenuGame::render(SDL_Renderer* renderer) {	
	if (status == HELP) {
		SDL_RenderCopy(renderer, textureHelp, NULL, NULL);
	}
	else if (status == EXIT) {
		SDL_RenderCopy(renderer, textureGameOver, NULL, NULL);
	}
	else if (status == PLAY) {
		return;
	}
	else {
		SDL_RenderCopy(renderer, texture, NULL, NULL);
	}
}

void MenuGame::handInputAction(bool& quit) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= 350 && x<=625 && y >= 95 && y<=195) {
		status = PLAY;
	}
	else  if (x >= 350 && x <= 625 && y >= 260 && y <= 360) {
		status = HELP;
	}
	else if (x >= 350 && x <= 625 && y >= 440 && y <= 540) {
		quit = true;
	}
	else {
		;
	}
}

void MenuGame::inputActionGameOver(bool& quit) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= 325 && x <= 600 && y >= 295 && y <= 395) {
		status = PLAY;
	}
	else  if (x >= 330 && x <= 605 && y >= 460 && y <= 560) {		
		status = EXIT;
		quit = true;
	}
	else {
		status=EXIT;
	}
}

bool MenuGame::exitHelp() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= 910 && x <= SCREEN_WIDTH && y >= 0 && y <= 100) {
		status = OUT;
		return true;
	}		
	else 
		return false;
}