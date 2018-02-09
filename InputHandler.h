#pragma once

#include "Game.h"

class InputHandler{
public:
    char static key(){ return _key; }
    void static handleEvents();
private:
    static char _key;
};
