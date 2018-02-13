#include "Snake.h"

Snake::Snake(int x, int y, int maxSpeed, int acceleration, int deceleration){
    init_position = Point(x, y);
    init_acceleration = acceleration;
    init_maxSpeed = maxSpeed;
    init_deceleration = deceleration;
    reset();
}

Snake::~Snake(){
    delete &_snake;
}

void Snake::reset(){
    _stat_acceleration = init_acceleration;
    _stat_maxSpeed = init_maxSpeed;
    _stat_deceleration = init_deceleration;
    _snake.clear();
    add(init_position);
    _speed = 10;
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

void Snake::accelerate(){
    static int count = 0;
    count++;
    if (count >= _stat_acceleration && _speed > _stat_maxSpeed){
        _speed--;
        count = 0;
    }
}

void Snake::decelerate(){
    static int count = 0;
    count++;
    if (count >= _stat_deceleration && _speed < 20){
        _speed++;
        count = 0;
    }
}

void Snake::add(Point p){
    _snake.insert(_snake.begin(), p);
}

void Snake::remove(){
    _snake.pop_back();
}
