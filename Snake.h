#pragma once

#include <vector>
#include "Point.h"
#include "InputHandler.h"

class Snake{
public:

    Snake(int x, int y);
    ~Snake();

    void update(int worldW, int worldH);
    std::vector<Point> snake(){ return _snake; }
    void add(Point p);
    void remove();
    Point head(){ return _snake[0]; }


private:

    std::vector<Point> _snake;
};
