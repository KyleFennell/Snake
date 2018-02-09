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
    snake = new Snake(_width/2, _height/2);
}

World::~World(){
    for (int i = 0; i < _height; i++){
        delete &_world[i];
    }
    delete &_world;
}

void World::update(){

    _world = _map;          //clear the world back to default state
                            // add food
    if (snake->head().x() == 0 || snake->head().x() == _width
        || snake->head().y() == 0 || snake->head().y() == _height){

        }
    snake->update();        // move snake
    if (_world[snake->head().y()][snake->head().x()] != 0){  // if snake ate something
        // deal with it
    }
    else {                  // snake didnt eat anything;
        snake->remove();    // snake stays same length
    }

    for (Point p : snake->snake()){
        _world[p.y()][p.x()] = 1;
    }                       // add snake to the map
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
            }
        }
    }
}
