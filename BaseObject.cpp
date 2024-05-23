
#include"BaseObject.h"

BaseObject::BaseObject() {
	coordinates.x = 0;
	coordinates.y = 0;
	texture =nullptr;
}

BaseObject::~BaseObject() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void BaseObject:: render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &coordinates);	
}