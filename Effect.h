#pragma once

#include "Snake.h"

class Snake;

class Effect{
public:

    Effect(){}
    ~Effect(){}
    virtual void execute(Snake* s){}
    virtual void execute(){}
};
