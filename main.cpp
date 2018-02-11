#include "Game.h"
#include "SDL.h"

int main(int argc, char* argv[]){

    Game g;
    g.init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while(g.running()){
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&Game::event) == 1){}

        g.handleEvents();
        g.update();
        g.render();

        frameTime = SDL_GetTicks()-frameStart;

        if (frameDelay > frameTime){
            SDL_Delay(frameDelay-frameTime);
        }
    }
    g.clean();

    return 0;
}
