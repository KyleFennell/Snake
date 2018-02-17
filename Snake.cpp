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
    _powerup = new Powerup();
    c_speed = c_acceleration = c_deceleration = c_powerup_duration = 0;
    _addLength = 0;
}

bool Snake::update(int worldW, int worldH){
    if (c_powerup_duration > 0){
        c_powerup_duration--;
    }
    else if (c_powerup_duration == 0){
        _powerup->undo();
        c_powerup_duration--; //pushes it below the threshold.
        f_powerup_active = false;
        _powerup = _powerup_second;
    }
    if (c_speed < _speed){
        c_speed++;
        return false;
    }
    else {
        c_speed = 0;
        switch (InputHandler::p1MovementKey()){
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
        switch (InputHandler::p1PowerupKey()){
        case 'e':
            if (!f_powerup_active || f_powerup_second){
                usePowerup();
            }
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

void Snake::givePowerup(Powerup* powerup){
    if (f_powerup_active){
        f_powerup_second = true;
        _powerup_second = powerup;
    }
    else{
        _powerup = powerup;
    }
}

void Snake::usePowerup(){
    if (_powerup){
        f_powerup_active = true;
        if (f_powerup_second){
            _powerup->undo();
            f_powerup_second = false;
            _powerup = _powerup_second;
            _powerup_second = nullptr;
        }
        _powerup->execute(this);
        c_powerup_duration = _powerup->duration();
    }
}

void Snake::add(Point p){
    _snake.insert(_snake.begin(), p);
}

void Snake::remove(){
    if (_addLength > 0){
        _addLength--;
    }
    else {
        _snake.pop_back();
    }
}
