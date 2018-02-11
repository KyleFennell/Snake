#pragma once

#include <vector>
#include "Point.h"
#include "InputHandler.h"

class Snake{
public:

    Snake(int x, int y);
    ~Snake();

    bool update(int worldW, int worldH);            // returns true if the snake moved
    std::vector<Point> snake(){ return _snake; }
    void add(Point p);
    int& speed(){ return _speed; }
    void remove();
    Point head(){ return _snake[0]; }


private:

    int _speed = 10;
    int _counter = 0;
    std::vector<Point> _snake;
};
