
#include"Common.h"


SDL_Texture* loadImage(std::string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << path << "SDL_image Error: "
            << IMG_GetError() << std::endl;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from " << path << "SDL_Error: "
                << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}


SDL_Texture* loadText(std::string text, SDL_Renderer* renderer) {
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    TTF_Font* font = TTF_OpenFont("BAUHS93.TTF", 80);
    if (font == nullptr) {
        std::cout << "Font is not available" << std::endl << TTF_GetError();
        TTF_Quit();
        return nullptr;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 255,0,0 });
    if (textSurface == nullptr) {
        std::cout << "Failed to render text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        return nullptr;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        return nullptr;
    }
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return textTexture;
}


Mix_Chunk* loadAudio(std::string audioPath) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return nullptr;
    }

    Mix_Chunk* sound = Mix_LoadWAV(audioPath.c_str());
    if (sound == nullptr) {
        return nullptr;
    }
    return sound;
}

void playAudio(Mix_Chunk* sound) {
    if (sound != nullptr) {
        Mix_PlayChannel(-1, sound, 0);
    }
}

bool checkCollision(SDL_Rect a,int& x, int& y) {
    if (a.x + a.w >= x && x >= a.x && a.y + a.h >= y && y >= a.y) {
        return true;
    }
    return false;
}

Mix_Music* loadMusic(const char* path)
{
    Mix_Music* gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_ERROR,
            "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}
void playMusic(Mix_Music* gMusic)
{
    if (gMusic == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gMusic, -1);
    }
    else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}
