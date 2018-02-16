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
    _map = std::vector<std::vector<int>>(_height);        // this section will be replaces with map loading
    for (int i = 0; i < _height; i++){
        _map[i] = std::vector<int>(_width);
        for (int j = 0; j < _width; j++){
            _map[i][j] = 0;
        }
    }

    t_ground = TextureManager::loadTexture("assets/ground.png");
    t_snake = TextureManager::loadTexture("assets/snake.png");
    t_wall = TextureManager::loadTexture("assets/wall.png");
    _snake = new Snake(_width/2, _height/2, 2, 1, 30);
    reset();
//    std::cout << "world started" << std::endl;
}

World::~World(){
    for (int i = 0; i < _height; i++){
        delete &_world[i];
    }
    delete &_world;
}

void World::update(){

    _world = _map;                                             // clear the world back to default state
    //std::cout << "map drawn" << std::endl;
    while (_foodCount < _foodMax){                             // add food
        addEntity(4);
        _foodCount++;
    }
//    std::cout << "food drawn" << std::endl;
    for (Point p : _snake->snake()){
        if (p != _snake->head()){
            _world[p.y()][p.x()] = -1;
        }
    }                       // add snake to the map for collision checking
//    std::cout << "snake drawn" << std::endl;
    for(std::map<Point, WorldEntity*>::iterator i=_entities.begin(); i !=_entities.end(); i++){             // populate the world with entities
//        std::cout << i->second->pos().y() << "," << i->second->pos().x() << std::endl;
        _world[i->second->pos().y()][i->second->pos().x()] = 4;
    }
//    std::cout << "entities drawn" << std::endl;
    if (_goal){
        _world[_goal->pos().y()][_goal->pos().x()] = 3;
    }
//    std::cout << "goal drawn" << std::endl;
    if (_snake->update(_width, _height)){                                   // move snake taking in width and height for edge checking and warping
        _snake->decelerate();
        if (_world[_snake->head().y()][_snake->head().x()] != 0){           // if snake ate something
            if (_world[_snake->head().y()][_snake->head().x()] == -1 ||
                  _world[_snake->head().y()][_snake->head().x()] == 2){     // if it ate snake or wall
                reset();
            }
            else if (_world[_snake->head().y()][_snake->head().x()] == 3){  // snake ate the goal
                _level = (_level+1+_maps->mapCount())%_maps->mapCount();
                std::cout << "level completed" << _level << std::endl;
                loadMap();
                std::cout << "loading level " << _level << std::endl;
                reset();
            }
            else {                                                          // snake has eaten an entity and its exetuce() is being run
                _entities[Point(_snake->head().x(), _snake->head().y())]->execute(_snake);
                removeEntity(_snake->head().x(), _snake->head().y());
                if (_snake->length()%5 == 0){
                    addEntity(5);
                }
                _snake->remove();    // snake stays same length
            }
        }
        else {
            _snake->remove();
        }
        if (_snake->length() == 10 && !_goal){
            _goal = new WorldEntity(Point(_width/2, _height/2), 3, new Effect(), TextureManager::loadTexture("assets/goal.png"));
        }
//        std::cout << "collision checkes completed" << std::endl;
    }

    for (Point p : _snake->snake()){
        _world[p.y()][p.x()] = 1;
    }                       // add snake to the map
}

void World::addEntity(int type){
    bool placed = false;
    while (!placed){
        int x = rand()%_width;
        int y = rand()%_height;
        if (_world[y][x] == 0){
            _entities[Point(x,y)] = EntityFactory::createEntity(Point(x,y), type, nullptr);
            placed = true;
        }
    }
}

void World::removeEntity(int x, int y){
    switch (_entities[Point(x, y)]->type()){
        case 4: _foodCount--;
            _snake->accelerate();
            break;
        default:
            break;
    }
    _entities.erase(Point(x,y));
}

void World::reset(){
    _snake->reset();
    _entities.clear();
    _foodCount = 0;
    _goal = nullptr;
    _world = _map;
    addEntity(6);
}

void World::loadMap(){
    std::vector<std::vector<int>> nextMap = _maps->getMap(_level).map();
    std::cout << _level << std::endl;
    for (int i = 0; i < _height; i++){
        for (int j = 0; j < _width; j++){
            _map[i][j] = nextMap[i][j];
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
            case 0:
                TextureManager::draw(t_ground, src, dest);
                break;
            case 1:
                TextureManager::draw(t_snake, src, dest);
                break;
            case 2:
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
