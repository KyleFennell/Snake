#pragma once

#include "Point.h"
#include "Effect.h"
#include "Snake.h"

class Snake;
class WorldEntity{
public:

    WorldEntity(Point pos, int type, Effect* effect){
        _pos = pos;
        _type = type;
        _effect = effect;
    }
    ~WorldEntity(){ delete &_pos; }
    Point pos(){ return _pos; }
    int type(){ return _type; }
    int addLength(){ return _addLength; }
    void execute(){ _effect->execute(); }
    void execute(Snake* s){ _effect->execute(s); }

private:

    Point _pos;
    int _type;
    int _addLength;
    Effect* _effect;

};
