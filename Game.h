#pragma once

#include "SDL.h"
#include "InputHandler.h"
#include "World.h"
#include <iostream>

class World;

class Game{
public:

    static SDL_Renderer* renderer;
    static SDL_Event event;
    Game();
    ~Game();

    void init(const char* title, int x, int y, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running(){return _running;}
    bool paused(){return _paused;}

private:
    SDL_Window* window;

    World* _world;

    bool _running = false;
    bool _paused = false;

};
