#include "World.h"
#include "TextureManager.h"


World::World(int w, int h){
    _width = w;
    _height = h;
    _map = std::vector<std::vector<int>>(_height);        // this section will be replaces with map loading
    for (int i = 0; i < _height; i++){
        _map[i] = std::vector<int>(_width);
        for (int j = 0; j < _width; j++){
            _map[i][j] = 0;
        }
    }

    t_ground = TextureHandler::loadTexture("assets/ground.png");
    t_snake = TextureHandler::loadTexture("assets/snake.png");
    t_food = TextureHandler::loadTexture("assets/food.png");
    _snake = new Snake(_width/2, _height/2);
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
    }

    for (Point p : _snake->snake()){
        _world[p.y()][p.x()] = -1;
    }                       // add snake to the map

    for(int i = 0; i < (int)_entities.size(); i++){             // populate the world with entities
        _world[_entities[i]->pos().y()][_entities[i]->pos().x()] = _entities[i]->type();
    }

    _snake->update(_width, _height);                            // move snake taking in width and height for edge checking and warping
    std::cout << "updated" << std::endl;
    if (_world[_snake->head().y()][_snake->head().x()] != 0){   // if snake ate something
        if (_world[_snake->head().y()][_snake->head().x()] == -1){   // if it are snake
            reset();
        }
        if (_world[_snake->head().y()][_snake->head().x()] == 2){   // if it are food
            removeEntity(_snake->head().x(), _snake->head().y());
            _foodCount--;
        }
    }
    else {                  // snake didnt eat anything;
        _snake->remove();    // snake stays same length
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
            _entities.push_back(new WorldEntity(Point(x, y), type));
            _foodCount++;
            placed = true;
            std::cout << "food added: " << x << "," << y << std::endl;
        }
    }
}

void World::removeEntity(int x, int y){
    for (int i = 0; i < _entities.size(); i++){
        if (_entities[i]->pos() == Point(x,y)){
            _entities.erase(_entities.begin()+i);
        }
    }
}

void World::reset(){
    delete _snake;
    _snake = new Snake(_width/2, _height/2);
    for (int i = 0; i < (int)_entities.size(); i++){
        _entities.pop_back();
    }
    _foodCount = 0;


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
                TextureHandler::draw(t_ground, src, dest);
                break;
            case 1:
                TextureHandler::draw(t_snake, src, dest);
                break;
            case 2:
                TextureHandler::draw(t_food, src, dest);
                break;
            default:
                TextureHandler::draw(t_ground, src, dest);
                break;
            }
        }
    }
}
