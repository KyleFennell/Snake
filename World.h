#pragma once

#include <vector>
#include "SDL.h"
#include "Snake.h"
#include "WorldEntity.h"

class Snake;

class World{
public:

    World(int w, int h);
    ~World();
    std::vector<std::vector<int>>* world() { return &_world; }

    void update();
    void draw();

private:

    void addEntity(int type);
    void removeEntity(int x, int y);

    void reset();

    int _width;
    int _height;
    std::vector<std::vector<int>> _map;
    std::vector<std::vector<int>> _world;

    Snake* _snake;
    std::vector<WorldEntity*> _entities;

    SDL_Texture* t_snake;
    SDL_Texture* t_ground;
    SDL_Texture* t_food;

    int _foodCount = 0;
    int _foodMax = 10;

};
