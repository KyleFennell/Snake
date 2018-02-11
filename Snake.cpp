#include "Snake.h"

Snake::Snake(int x, int y){
    add(Point(x, y));
}

Snake::~Snake(){
    delete &_snake;
}

bool Snake::update(int worldW, int worldH){
    if (_counter < _speed){
        _counter++;
        return false;
    }
    else {
        _counter = 0;
        switch (InputHandler::key()){
        case 'w':
            add(head()+((head().y() != 0)?Point(0, -1):Point(0, worldH-1)));
            break;
        case 'a':
            add(head()+((head().x() != 0)?Point(-1, 0):Point(worldW-1, 0)));
            break;
        case 's':
            add(head()+((head().y() != worldH-1)?Point(0, 1):Point(0, -worldH+1)));
            break;
        case 'd':
            add(head()+((head().x() != worldW-1)?Point(1, 0):Point(-worldW+1, 0)));
            break;
        }
    }
    return true;
}

void Snake::add(Point p){
    _snake.insert(_snake.begin(), p);
}

void Snake::remove(){
    _snake.pop_back();
}
