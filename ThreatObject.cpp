
#include"ThreatObject.h"

ThreatObject::ThreatObject() {
	
}

ThreatObject::~ThreatObject() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	
}

void ThreatObject::initializeBoom(SDL_Renderer* renderer) {
	coordinates.x = 0;
	coordinates.y = 0;
	coordinates.w = BOOM_WIDTH;
	coordinates.h = BOOM_HEIGHT;
	explosiveEffect = false;
	texture = loadImage("Image\\Boom.png", renderer);
	explosiveEffectTexture = loadImage("Image\\ExplosiveEffect.png", renderer);
}

void ThreatObject::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &coordinates);
	if (explosiveEffect) {
		SDL_RenderCopy(renderer, explosiveEffectTexture, NULL, &coordinates);
		explosiveEffect = false;
	}
}

Heart::~Heart() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Heart::initializeHeart(SDL_Renderer* renderer) {
	coordinates.x = 0;
	coordinates.y = 0;
	coordinates.w = BOOM_WIDTH;
	coordinates.h = BOOM_HEIGHT;
	texture = loadImage("Image\\Heart.png", renderer);
}

void Heart::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &coordinates);
}