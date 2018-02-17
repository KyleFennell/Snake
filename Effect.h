#pragma once

#include "Snake.h"

class Snake;

class Effect{
public:

    Effect(){}
    ~Effect(){}
    virtual void execute(Snake* s){}
    virtual void execute(){}
    virtual int duration(){ return 0; }
    virtual void undo(){}
    virtual bool autoExecute(Snake* s) {
        if (_autoExecute){
            if (_snake){
                execute();
            }
            else {
                execute(s);
            }
        }
        return _autoExecute;
    }

private:
    Snake* _snake = nullptr;
    bool _autoExecute = false;
};
