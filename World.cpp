#include "World.h"
#include "TextureManager.h"
#include "EntityFactory.h"
#include <ctime>

World::World(int w, int h){

    std::srand(std::time(0));

    _width = w;
    _height = h;
    _maps = new MapManager();

    _maps->loadMaps();
    _mapData = std::vector<std::vector<int>>(_height, std::vector<int>(_width));

    loadMap();

    t_ground = TextureManager::loadTexture("assets/ground.png");
    t_snake = TextureManager::loadTexture("assets/snake.png");
    t_wall = TextureManager::loadTexture("assets/wall.png");
    _snake = new Snake(_width/2, _height/2, 2, 1, 30);
    resetWorld();

    std::cout << "world started" << std::endl;
}

World::~World(){
    for (int i = 0; i < _height; i++){
        delete &_world[i];
    }
    delete &_world;
}

void World::update(){
    _world = _mapData;                                         // clear the world back to default state
//    std::cout << "map drawn" << std::endl;
    while (_foodCount < _foodMax){                             // add food
        addEntity(Point(), Tile_Entity);
        _foodCount++;
    }
    spawnPowerups();
//    std::cout << "food drawn" << std::endl;
    placeSnakeCollider();                       // add snake to the map for collision checking
//    std::cout << "snake drawn" << std::endl;
    for(std::map<Point, WorldEntity*>::iterator i=_entities.begin(); i !=_entities.end(); i++){             // populate the world with entities
//        std::cout << i->second->pos().x() << "," << i->second->pos().y() << " " << i->second->type() << std::endl;
        _world[i->second->pos().y()][i->second->pos().x()] = Tile_Entity;
    }
//    std::cout << "entities drawn" << std::endl;
    if (_goal){
        _world[_goal->pos().y()][_goal->pos().x()] = Tile_Goal;
//        std::cout << "goal drawn" << std::endl;
    }
    if (_snake->update(_width, _height)){                                   // move snake taking in width and height for edge checking and warping
        _snake->decelerate();
        if (_world[_snake->head().y()][_snake->head().x()] != Tile_Ground){           // if snake ate something
            if (_world[_snake->head().y()][_snake->head().x()] == Tile_SnakeCollider ||
                  _world[_snake->head().y()][_snake->head().x()] == Tile_Wall){     // if it ate snake or wall
//                std::cout << "snake hit wall or itself" << std::endl;
                resetWorld();
            }
            else if (_world[_snake->head().y()][_snake->head().x()] == Tile_Goal){  // snake ate the goal
//                std::cout << "level completed" << _level << std::endl;
                _level = (_level+1+_maps->mapCount())%_maps->mapCount();    // level++ with wrapping back to 0
                loadMap();
//                std::cout << "loading level " << _level << std::endl;
                resetWorld();
            }
            else {                                                          // snake has eaten an entity and its exetuce() is being run
                if (!_entities[Point(_snake->head().x(), _snake->head().y())]->autoExecute(_snake)){
//                    std::cout << "snake eating a powerup" << std::endl;
                    _snake->givePowerup(_entities[Point(_snake->head().x(), _snake->head().y())]->powerup());
//                    std::cout << "snake ate: " << _entities[Point(_snake->head().x(), _snake->head().y())]->type() << std::endl;
                }
                removeEntity(_snake->head().x(), _snake->head().y());
                _snake->remove();    // snake stays same length
            }
        }
        else {
            _snake->remove();
        }
        if (_snake->length() == 10 && !_goal){
            _goal = new WorldEntity(Point(_width/2, _height/2), 3, new Powerup(), TextureManager::loadTexture("assets/goal.png"));
        }
//        std::cout << "collision checkes completed" << std::endl;
    }

    for (Point p : _snake->snake()){
        _world[p.y()][p.x()] = Tile_Snake;
    }                       // add snake to the map
}

void World::spawnPowerups(){
    for (PowerupSpawn* p : _map->powerupSpawns()){
        if (p->update()){
            if (!_entities[p->pos()]){
                p->resetRespawnTime();
                addEntity(p->pos(), p->type());
            }
        }
    }
}

void World::placeSnakeCollider(){
    for (Point p : _snake->snake()){
        if (p != _snake->head()){
            _world[p.y()][p.x()] = Tile_SnakeCollider;
        }
    }
}

void World::addEntity(Point p, int type){
    bool placed = false;
    if (p == Point()){
        while (!placed){
            int x = rand()%_width;
            int y = rand()%_height;
            if (_world[y][x] == Tile_Ground && !_entities[Point(x,y)]){
//                std::cout << "creating entity" << std::endl;
                _entities[Point(x,y)] = EntityFactory::createEntity(Point(x,y), type, nullptr);
                placed = true;
//                std::cout << "placed entity" << std::endl;
            }
        }
    }
    else {
        std::cout << "creating entity from spawner " << type << std::endl;
        _entities[p] = EntityFactory::createEntity(p, type, nullptr);
    }
}

void World::removeEntity(int x, int y){
    for (PowerupSpawn* p : _map->powerupSpawns()){
        if (p->pos() == Point(x, y)){
            p->resetRespawnTime();
            break;
        }
    }
    switch (_entities[Point(x, y)]->type()){
        case 4: _foodCount--;
            break;
        default:
            break;
    }
    _entities.erase(Point(x,y));
}

void World::resetWorld(){
    _snake->reset();
    _entities.clear();
    _foodCount = 0;
    _goal = nullptr;
    _world = _mapData;
    for (int i = 0; i < (int)_map->powerupSpawns().size(); i++){
        addEntity(_map->powerupSpawns()[i]->pos(), _map->powerupSpawns()[i]->type());
    }
}

void World::loadMap(){
    _map = _maps->getMap(_level);
    std::vector<std::vector<int>> nextMap = _map->map();
    std::cout << _level << std::endl;
    for (int i = 0; i < _height; i++){
        for (int j = 0; j < _width; j++){
            _mapData[i][j] = nextMap[i][j];
        }
    }
}

void World::draw(){
    SDL_Rect src;
    SDL_Rect dest;
    src.x = src.y = 0;
    src.w = src.h = 8;
    dest.w = dest.h = 16;
    for (int i = 0; i < _height; i++){
        for (int j = 0; j < _width; j++){
            dest.x = j*16;
            dest.y = i*16;
            switch (_world[i][j]){
            case Tile_Ground:
                TextureManager::draw(t_ground, src, dest);
                break;
            case Tile_Snake:
                TextureManager::draw(t_snake, src, dest);
                break;
            case Tile_Wall:
                TextureManager::draw(t_wall, src, dest);
                break;
            default:
                TextureManager::draw(t_ground, src, dest);
                break;
            }
        }
    }
    for(std::map<Point, WorldEntity*>::iterator i=_entities.begin(); i !=_entities.end(); i++){   // draw the entities
        dest.x = i->second->pos().x()*16;
        dest.y = i->second->pos().y()*16;
        TextureManager::draw(i->second->texture(), src, dest);
    }
    if (_goal){
        dest.x = _goal->pos().x()*16;
        dest.y = _goal->pos().y()*16;
        TextureManager::draw(_goal->texture(), src, dest);
    }
}
