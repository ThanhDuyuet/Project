
#pragma once

#ifndef COMMON_H
#define COMMON_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = 650;

SDL_Texture* loadText(std::string text, SDL_Renderer* renderer);
SDL_Texture* loadImage(std::string path, SDL_Renderer* renderer);
Mix_Chunk* loadAudio(std::string audioPath);
void playAudio(Mix_Chunk* sound);

bool checkCollision(SDL_Rect a, int& x, int& y);
Mix_Music* loadMusic(const char* path);
void playMusic(Mix_Music* gMusic);

#endif