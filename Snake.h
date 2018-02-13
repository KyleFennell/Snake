#pragma once

#include <vector>
#include "Point.h"
#include "InputHandler.h"

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
    int& speed(){ return _speed; }
    void accelerate();
    void decelerate();

private:

    int _speed = 10;
    int _counter = 0;
    int _stat_maxSpeed;
    int _stat_acceleration;
    int _stat_deceleration;
    int init_maxSpeed;
    int init_acceleration;
    int init_deceleration;
    Point init_position;
    std::vector<Point> _snake;
};
