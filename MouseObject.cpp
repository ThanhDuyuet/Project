
#include"MouseObject.h"

MouseObject::MouseObject() {
	coordinates.x = 0;
	coordinates.y = 0;
	coordinates.w = MOUSE_WIDTH;
	coordinates.h = MOUSE_HEIGHT;
	texture = nullptr;
	point = POINT;
}

MouseObject::~MouseObject() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	
}

void MouseObject::setTextureMouse(SDL_Renderer* renderer) {
	texture = loadImage("Image\\Mouse.png", renderer);
}

void MouseObject::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &coordinates);
}
