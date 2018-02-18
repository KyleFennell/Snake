#pragma once

#include <vector>
#include "Point.h"
#include "InputHandler.h"
#include "Powerup.h"

class Powerup;
class Snake{
public:

    Snake(int x, int y, int maxSpeed, int acceleration, int deceleration);
    ~Snake();

    bool update(int worldW, int worldH);            // returns true if the snake moved
    void setSpawn(Point p){ init_position = p; }
    void reset();

    void add(Point p);
    void remove();

    std::vector<Point> snake(){ return _snake; }
    Point head(){ return _snake[0]; }
    void addLength(int i){ _addLength += i; }
    void addSpeed(int i){
        _speed += i;
        if (_speed < _stat_maxSpeed)
            _speed = _stat_maxSpeed;
    }
    void givePowerup(Powerup* powerup);
    void usePowerup();
    int length(){ return _snake.size(); }
    int speed(){ return _speed; }
    void accelerate();
    void decelerate();

private:

    int _speed = 10;
    int _addLength = 0;
    int _stat_maxSpeed;
    int _stat_acceleration;
    int _stat_deceleration;
    int init_maxSpeed;
    int init_acceleration;
    int init_deceleration;
    int c_speed, c_acceleration, c_deceleration;
    int c_powerup_duration;
    bool f_powerup_active = false;
    bool f_powerup_second = false;

    Powerup* _powerup = nullptr;
    Powerup* _powerup_second = nullptr;

    Point init_position;
    std::vector<Point> _snake;
};
