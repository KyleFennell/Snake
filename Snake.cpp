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
    _stat_deceleration = init_deceleration;
    _stat_maxSpeed = init_maxSpeed;
    _snake.clear();
    add(init_position);
    _speed = 10;
    c_speed = c_acceleration = c_deceleration = 0;
}

bool Snake::update(int worldW, int worldH){

    if (c_speed < _speed){
        c_speed++;
        return false;
    }
    else {
        c_speed = 0;
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
    c_acceleration++;
    if (c_acceleration >= _stat_acceleration && _speed > _stat_maxSpeed){
        _speed--;
        c_acceleration = 0;
    }
}

void Snake::decelerate(){
    c_deceleration++;
    if (c_deceleration >= _stat_deceleration && _speed < 20){
        _speed++;
        c_deceleration = 0;
    }
}

void Snake::add(Point p){
    _snake.insert(_snake.begin(), p);
}

void Snake::remove(){
    //std::cout << _addLength << std::endl;
    if (_addLength > 0){
        _addLength--;
    }
    else {
        _snake.pop_back();
    }
}
