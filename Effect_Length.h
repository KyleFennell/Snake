#pragma once

#include "Effect.h"

class Effect_Lenth : public Effect{
public:
    Effect_Lenth(Snake* s, int length, bool multiply, bool autoExecute){
        _snake = s;
        _length = length;
        _multiply = multiply;
        _autoExecute = autoExecute;
    }

    void execute(Snake* s) override {
        _snake = s;
        s->addLength((_multiply)?((s->length()-1)*(_length-1)):_length);
    }

    void execute() override {
        _snake->addLength((_multiply)?((_snake-1)->length()*_length):_length);
    }

    void undo() override {}

     bool autoExecute(Snake* s) {
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
    Snake* _snake;
    int _length;
    bool _multiply;
    bool _autoExecute;
};
