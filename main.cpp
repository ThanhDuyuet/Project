
#include"Common.h"
#include"MainObject.h"
#include"ThreatObject.h"
#include"MouseObject.h"
#include<vector>
#include<ctime>
#include<cstdlib>
#include"MenuGame.h"

using namespace std;

const std::string WINDOW_TITLE = " PUNCH MOUSE Game !";
const int AMOUNT_MOUSE = 2;
const int AMOUNT_BOOM = 2;
const int coordinatesMap1X[] = { 100,430,715, 430,100,715, 100,430 };
const int map1X = sizeof(coordinatesMap1X) / sizeof(int);
const int coordinatesMap1Y[] = { 125,295,466, 295, 125, 466, 295, 125 };
const int map1Y = sizeof(coordinatesMap1Y) / sizeof(int);

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal = false);
void waitUntilKeyPressed();


int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
       
    MenuGame menuGame;
    menuGame.initializeMenuGame(renderer);

    SDL_Texture* map1 = loadImage("Image\\Map1.png", renderer);
 
    MainObject player;
    player.initializePlayer(renderer);

    std::vector<MouseObject> mouse(AMOUNT_MOUSE);
    for (int i = 0; i < AMOUNT_MOUSE; i++) {
        mouse[i].setTextureMouse(renderer);
    }
    
    std::vector<ThreatObject> boom(AMOUNT_BOOM);
    for (int i = 0; i < AMOUNT_BOOM; i++) {
        boom[i].initializeBoom(renderer);
    }
    
    Heart heart;
    heart.initializeHeart(renderer);

    bool quit = false;
    SDL_Event e;
   
    Mix_Music* bkGroundMusic = loadMusic("Audio\\LoveMeLikeYouDo.mp3");
    Uint32 startTime = SDL_GetTicks() / 1000;
    std::cout << startTime << std::endl;
    while (!quit) {
        playMusic(bkGroundMusic);
        if (menuGame.status != PLAY) {
            menuGame.render(renderer);
            SDL_RenderPresent(renderer);
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    Mix_HaltMusic();
                    quit = true;
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN) { 
                    menuGame.handInputAction(quit);
                    if (menuGame.status == HELP) {
                        menuGame.render(renderer);
                        SDL_RenderPresent(renderer);
                        bool ExitHelp = false;
                        while (!ExitHelp)
                            while( SDL_PollEvent(&e) != 0) {
                                if (e.type == SDL_MOUSEBUTTONDOWN) {
                                    if (menuGame.exitHelp()) {
                                        ExitHelp = true;
                                        break;
                                    }
                                }
                            }
                    }
                    else if (menuGame.status == PLAY || menuGame.status == EXIT)
                        break;
                }
                else {
                    ;
                }
            }
        }        
        if (quit == true)
            break;
        if (menuGame.status == PLAY) {
            while (!player.isDied) {
                while (SDL_PollEvent(&e) != 0)
                 {
                    if (e.type == SDL_QUIT) {
                        player.isDied = true;
                        quit = true;
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN) {
                        SDL_GetMouseState(&player.x, &player.y);                        
                        for (int i = 0; i < AMOUNT_MOUSE; i++) {
                            if (checkCollision(mouse[i].getCoordinates(), player.x, player.y)) {
                                player.score.point += POINT;
                                playAudio(player.getScoreAudio);
                                player.high_Score.updateTextureHighScore(renderer, player.score.point);
                                player.high_Score.recordHighScore();
                            }
                        }
                        for (int i = 0; i < AMOUNT_BOOM; i++) {
                            if (checkCollision(boom[i].getCoordinates(), player.x, player.y)) {
                                player.hp.getDamage();     
                                boom[i].explosiveEffect = true;
                                playAudio(player.getBoomAudio);
                            }
                        }
                        if (player.hp.isOver()) {
                            player.isDied = true;
                            menuGame.status = EXIT;
                            playAudio(menuGame.gameOverAudio);
                        }
                    }
                    else {
                        ;
                    }
                }
                Uint32 currentTime = SDL_GetTicks() / 1000;
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, map1, NULL, NULL);
                
                for (int i = 0; i < AMOUNT_MOUSE; i++) {
                    if ((currentTime - startTime) % TIME_TO_APPEAR > 0) {
                        mouse[i].setCoordinates(coordinatesMap1X[rand() % map1X], coordinatesMap1Y[rand() % map1Y]);
                    }
                    mouse[i].render(renderer);
                }
                for (int i = 0; i < AMOUNT_BOOM; i++) {
                    if ((currentTime - startTime) % TIME_APPEAR_BOOM > 0) {
                        boom[i].setCoordinates(coordinatesMap1X[rand() % map1X], coordinatesMap1Y[rand() % map1Y]);

                    }
                    boom[i].render(renderer);

                }
                player.render(renderer);
                
                SDL_RenderPresent(renderer);
                SDL_Delay(100);
            }            
        }
        if (menuGame.status == EXIT) {
            bool exitGameOver = false;
            menuGame.render(renderer);
            SDL_RenderPresent(renderer);
            while (!exitGameOver) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit == true;
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN) {
                        menuGame.inputActionGameOver(quit);
                        if (menuGame.status == PLAY || menuGame.status == EXIT) {
                            exitGameOver = true;
                            break;
                        }                            
                    }
                }
            }            
            Mix_HaltMusic();
            player.setNewTurn();
            player.isDied = false;
            SDL_RenderClear(renderer);
        }
        
    }
    player.~MainObject();
    for (int i = 0; i < AMOUNT_MOUSE; i++) {
        mouse[i].~MouseObject();
    }
    for (int i = 0; i < AMOUNT_BOOM; i++) {
        boom[i].~ThreatObject();
    }
    quitSDL(window, renderer);
    return 0;
}


void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}
