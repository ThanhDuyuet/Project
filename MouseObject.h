#pragma once
#ifndef MOUSEOBJECT_H
#define MOUSEOBJECT_H

#include"BaseObject.h"

const int MOUSE_WIDTH = 100;
const int MOUSE_HEIGHT = 100;
const int POINT = 20;
const int TIME_TO_APPEAR = 2;

class MouseObject : public BaseObject {
	int point;

public:

	MouseObject();
	~MouseObject();
	void setTextureMouse(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer) override;
};


#endif