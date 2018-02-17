#pragma once

#include "Point.h"
#include "Snake.h"
#include "Powerup.h"

class Snake;
class Powerup;
class WorldEntity{
public:

    WorldEntity(Point pos, int type, Powerup* powerup, SDL_Texture* tex){
        _pos = pos;
        _type = type;
        _powerup = powerup;
        _tex = tex;
    }
    ~WorldEntity(){ delete &_pos; }
    Point pos(){ return _pos; }
    int type(){ return _type; }
    bool autoExecute(Snake* s);
    int addLength(){ return _addLength; }
    void execute();
    void execute(Snake* s);
    SDL_Texture* texture() { return _tex; }
    Powerup* powerup(){ return _powerup; }

private:

    Point _pos;
    int _type;
    int _addLength;

    Powerup* _powerup;
    SDL_Texture* _tex;

};
