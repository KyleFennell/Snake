#pragma once

#include <vector>
#include "SDL.h"
#include "Snake.h"

class Snake;

class World{
public:

    World(int w, int h);
    ~World();
    std::vector<std::vector<int>>* world() { return &_world; }
    void update();
    void draw();
private:

    int _width;
    int _height;
    std::vector<std::vector<int>> _map;
    std::vector<std::vector<int>> _world;

    Snake* snake;

    SDL_Texture* t_snake;
    SDL_Texture* t_ground;
};
