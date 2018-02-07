#include "Game.h"
#include "SDL.h"

int main(int argc, char* argv[]){

    Game g;
    g.init(title, x, y, w, h, fs);
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while(g.isRunning()){
        frameStart = SDL_GetTicks();

        if (SDL_PollEvent(&g::event) == 1){
            g.handleEvents();
        }

        g.update();
        g.draw();

        frameTime = SDL_GetTicks()-frameStart;

        if (activeDelay > frameTime){
            SDL_Delay(activeDelay-frameTime);
        }
    }
    g.clean();

    return 0;
}
