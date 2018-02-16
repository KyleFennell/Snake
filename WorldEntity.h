#pragma once

#include "Point.h"
#include "Effect.h"
#include "Snake.h"

class Snake;
class WorldEntity{
public:

    WorldEntity(Point pos, int type, Effect* effect, SDL_Texture* tex){
        _pos = pos;
        _type = type;
        _effect = effect;
        _tex = tex;
    }
    ~WorldEntity(){ delete &_pos; }
    Point pos(){ return _pos; }
    int type(){ return _type; }
    int addLength(){ return _addLength; }
    void execute(){ _effect->execute(); }
    void execute(Snake* s){ _effect->execute(s); }
    SDL_Texture* texture() { return _tex; }

private:

    Point _pos;
    int _type;
    int _addLength;
    Effect* _effect;
    SDL_Texture* _tex;

};
