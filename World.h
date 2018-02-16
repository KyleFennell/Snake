#pragma once

#include <vector>
#include <map>
#include "SDL.h"
#include "WorldEntity.h"#include "Snake.h"
#include "MapManager.h"

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

    void loadMap();
    void reset();

    int _width;
    int _height;
    int _level = 0;
    std::vector<std::vector<int>> _map;
    std::vector<std::vector<int>> _world;

    Snake* _snake;
    std::map<Point, WorldEntity*> _entities;
    MapManager* _maps;

    SDL_Texture* t_snake;
    SDL_Texture* t_ground;
    SDL_Texture* t_wall;

    WorldEntity* _goal = nullptr;

    int _foodCount = 0;
    int _foodMax = 10;

};
