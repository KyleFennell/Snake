#pragma once

#include "Game.h"
#include <iostream>

class InputHandler{
public:
    char static p1MovementKey(){ return _p1MovementKey; }
    char static p1PowerupKey(){
        if (_p1PowerupKey != ' '){
            std::cout << _p1PowerupKey << std::endl;
            char out = _p1PowerupKey;
            _p1PowerupKey = ' ';
            return out;
        }
        return ' ';
    }
    void static handleEvents();
private:
    static char _p1MovementKey;
    static char _p1PowerupKey;
    static char _previousKey;
};
