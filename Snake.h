#pragma once

#include <vector>
#include "Point.h"
#include "InputHandler.h"
#include "Effect.h"
class Effect;

class Snake{
public:

    Snake(int x, int y, int maxSpeed, int acceleration, int deceleration);
    ~Snake();

    bool update(int worldW, int worldH);            // returns true if the snake moved
    void reset();

    void add(Point p);
    void remove();

    std::vector<Point> snake(){ return _snake; }
    Point head(){ return _snake[0]; }
    void addLength(int i){ _addLength += i; }
    void addSpeed(int i){ _speed += i; }
    void givePowerup(Effect* effect);
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

    Effect* _powerup;
    Effect* _powerup_second;

    Point init_position;
    std::vector<Point> _snake;
};
