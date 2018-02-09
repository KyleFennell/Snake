#pragma once

#include "Point.h"

class WorldEntity{
public:

    WorldEntity(Point pos, int type){ _pos = pos; _type = type; }
    ~WorldEntity(){ delete &_pos; }
    Point pos(){ return _pos; }
    int type(){ return _type; }

private:

    Point _pos;
    int _type;

};
