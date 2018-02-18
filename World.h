#pragma once

#include <vector>
#include <map>
#include "SDL.h"
#include "WorldEntity.h"#include "Snake.h"
#include "MapManager.h"

class Snake;
class WorldEntity;

class World{
public:

    enum {Tile_SnakeCollider = -1, Tile_Ground = 0, Tile_Snake = 1, Tile_Wall = 2, Tile_Goal = 3, Tile_Entity = 4};

    World(int w, int h);
    ~World();
    std::vector<std::vector<int>>* world() { return &_world; }


    void update();
    void draw();

private:

    void addEntity(Point p, int type);
    void removeEntity(int x, int y);

    void placeSnakeCollider();
    void spawnPowerups();


    void loadMap();
    void resetWorld();

    int _width;
    int _height;
    int _level = 3;
    std::vector<std::vector<int>> _mapData;
    std::vector<std::vector<int>> _world;
    Map* _map;

    Snake* _snake;
    std::map<Point, WorldEntity*> _entities;
    std::vector<PowerupSpawn*> _powerupSpawns;
    MapManager* _maps;

    SDL_Texture* t_snake;
    SDL_Texture* t_ground;
    SDL_Texture* t_wall;

    WorldEntity* _goal = nullptr;

    int _foodCount = 0;
    int _foodMax = 10;

};
