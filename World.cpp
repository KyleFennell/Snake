#include "World.h"
#include "TextureManager.h"
#include "EntityFactory.h"

World::World(int w, int h){
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
    t_food = TextureManager::loadTexture("assets/food.png");
    t_wall = TextureManager::loadTexture("assets/wall.png");
    t_goal = TextureManager::loadTexture("assets/goal.png");
    t_speedUp = TextureManager::loadTexture("assets/speedUp.png");
    _snake = new Snake(_width/2, _height/2, 2, 1, 30);

}

World::~World(){
    for (int i = 0; i < _height; i++){
        delete &_world[i];
    }
    delete &_world;
}

void World::update(){

    _world = _map;                                              //clear the world back to default state

    while (_foodCount < _foodMax){                             // add food
        addEntity(2);
        _foodCount++;
    }
    for (Point p : _snake->snake()){
        if (p != _snake->head()){
            _world[p.y()][p.x()] = -1;
        }
    }                       // add snake to the map for collision checking

    for(std::map<Point, WorldEntity*>::iterator i=_entities.begin(); i !=_entities.end(); i++){             // populate the world with entities
        _world[i->second->pos().y()][i->second->pos().x()] = i->second->type();
    }

    if (_snake->update(_width, _height)){                                // move snake taking in width and height for edge checking and warping
        _snake->decelerate();
        if (_world[_snake->head().y()][_snake->head().x()] != 0){        // if snake ate something
            if (_world[_snake->head().y()][_snake->head().x()] == -1 ||
                  _world[_snake->head().y()][_snake->head().x()] == 3){   // if it ate snake or wall
                reset();
            }
            else if (_world[_snake->head().y()][_snake->head().x()] == 4){  // snake ate the goal
                std::cout << "level completed: " << _level << std::endl;
                _level++;
                std::cout << "next level: " << _level << std::endl;
                loadMap();
                std::cout << "loaded level: " << _level << std::endl;
                reset();
            }
            else {                                                       // snake has eaten an entity and its exetuce() is being run
                _entities[Point(_snake->head().x(), _snake->head().y())]->execute(_snake);
                std::cout << "removing entity: " << _entities[Point(_snake->head().x(), _snake->head().y())]->pos().x() << "," << _entities[Point(_snake->head().x(), _snake->head().y())]->pos().y() << " at: " <<
                        _snake->head().x() << "," << _snake->head().y() << std::endl;
                removeEntity(_snake->head().x(), _snake->head().y());
                if (_snake->length() == 10){
                    addEntity(4);
                }
                if (_snake->length()%5 == 0){
                    addEntity(5);
                }
                _snake->remove();    // snake stays same length
            }
        }
        else {
            _snake->remove();
        }
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
        case 2: _foodCount--;
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
}

void World::loadMap(){
    std::vector<std::vector<int>> nextMap = _maps->getMap(_level).map();
    std::cout << _map.size() << "," << _map[0].size() << " " << nextMap.size() << "," << nextMap[0].size() << std::endl;
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
                TextureManager::draw(t_food, src, dest);
                break;
            case 3:
                TextureManager::draw(t_wall, src, dest);
                break;
            case 4:
                TextureManager::draw(t_goal, src, dest);
                break;
            case 5:
                TextureManager::draw(t_speedUp, src, dest);
                break;
            default:
                TextureManager::draw(t_ground, src, dest);
                break;
            }
        }
    }
}
