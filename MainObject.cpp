
#include"MainObject.h"

HP::HP() {
	Hp = MAX_HP;
	coordinates.x = 5;
	coordinates.y = 5;
	coordinates.w = 200;
	coordinates.h = 40;
}

HP::~HP() {
	for (int i = 0; i <= MAX_HP; i++) {
		if (texture[i] != nullptr)
			SDL_DestroyTexture(texture[i]);
		texture[i] = nullptr;
	}
}
void HP::setTextureHP(SDL_Renderer* renderer) {
	for (int i = 0; i <= MAX_HP; i++) {
		texture[i] = loadImage("Image\\"+std::to_string(i) + "Heart.png", renderer);
	}
}

void HP::render(SDL_Renderer* renderer) {
	switch (Hp) {
	case 0:
		SDL_RenderCopy(renderer, texture[Hp], NULL, &coordinates);
		break;

	case 1:
		SDL_RenderCopy(renderer, texture[Hp], NULL, &coordinates);
		break;
	case 2:

		SDL_RenderCopy(renderer, texture[Hp], NULL, &coordinates);
		break;

	case 3:
		SDL_RenderCopy(renderer, texture[Hp], NULL, &coordinates);
		break;

	case 4:
		SDL_RenderCopy(renderer, texture[Hp], NULL, &coordinates);
		break;

	case 5:
		SDL_RenderCopy(renderer, texture[Hp], NULL, &coordinates);
		break;

	default:
		break;
	}
}



Score::Score() {
	coordinates.x = SCREEN_WIDTH-200;
	coordinates.y = COORDINATES_Y_SCORE;
	coordinates.w = SCORE_WIDTH;
	coordinates.h = SCORE_HEIGHT;
	texture = nullptr;
	score = " Score: ";
	point = 0;
}

Score::~Score() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	texture = nullptr;
}

void Score::setTextureScore(SDL_Renderer* renderer) {
	texture = loadText(score + std::to_string(point), renderer);
}

void Score::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &coordinates);
}

HighScore::HighScore() {
	highScore = getHighScore();
	coordinatesCup.x = COORDINATES_X_SCORE;
	coordinatesCup.y = COORDINATES_Y_SCORE;
	coordinatesCup.w = SIZE_CUP;
	coordinatesCup.h = SIZE_CUP;
	coordinates.x = COORDINATES_X_SCORE + SIZE_CUP + SPACE;
	coordinates.y = COORDINATES_Y_SCORE;
	coordinates.w = SCORE_WIDTH;
	coordinates.h = SCORE_HEIGHT;
	
	texture = nullptr;
	cup = nullptr;
}

HighScore::~HighScore() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	if (cup != nullptr) {
		SDL_DestroyTexture(cup);
	}
}

int HighScore::getHighScore() {
	std::ifstream inFile("HighScore.txt");
	int getScore;
	while (!inFile.eof()) {
		inFile >> getScore;
	}
	inFile.close();
	return getScore;
}


void HighScore::recordHighScore() {
	std::ofstream outFile("HighScore.txt");
	if (outFile.is_open()) {
		outFile << highScore <<" ";
	}
	outFile.close();
}

void HighScore::setTexture(SDL_Renderer* renderer) {
	cup = loadImage("Image\\cup.png", renderer);
	texture = loadText(std::to_string(highScore), renderer);
}

void HighScore::updateTextureHighScore(SDL_Renderer* renderer, int& score) {
	if (score > highScore) {
		texture = loadText(std::to_string(score), renderer);
		highScore = score;
	}
}

void HighScore::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, cup, NULL, &coordinatesCup);
	SDL_RenderCopy(renderer, texture, NULL, &coordinates);
}

MainObject::~MainObject() {
	/*if (textureExplosiveEffect != nullptr) {
		SDL_DestroyTexture(textureExplosiveEffect);
		textureExplosiveEffect = nullptr;
	}*/
	high_Score.~HighScore();
	hp.~HP();
	score.~Score();
	Mix_FreeChunk(getScoreAudio);
	Mix_FreeChunk(getBoomAudio);
	Mix_FreeChunk(getHighScoreAudio);
	getScoreAudio = nullptr;
	getBoomAudio = nullptr;
	getHighScoreAudio = nullptr;
}

void MainObject::initializePlayer(SDL_Renderer* renderer) {
	//textureExplosiveEffect = loadImage("ExposiveEffect.png", renderer);
	isHighScore = false;
	isDied = false;
	getScoreAudio = loadAudio("Audio\\GetScoreAudio.wav");
	getHighScoreAudio = loadAudio("Audio\\LevelUpHighScoreAudio.wav");
	getBoomAudio = loadAudio("Audio\\ClickBoomAudio.wav");
	hp.setTextureHP(renderer);
	high_Score.setTexture(renderer);
}

void MainObject::render(SDL_Renderer* renderer) {
	hp.render(renderer);
	score.setTextureScore(renderer);
	high_Score.render(renderer);
	score.render(renderer);
}

void MainObject::setNewTurn() {
	hp.recover();
	score.point = 0;
}