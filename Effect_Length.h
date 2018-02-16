#pragma once

#include "Effect.h"

class Effect_Lenth : public Effect{
public:
    Effect_Lenth(Snake* s, int length, bool multiply){
        _snake = s;
        _length = length;
        _multiply = multiply;
    }

    void execute(Snake* s) override {
        s->addLength((_multiply)?((s->length()-1)*(_length-1)):_length);
    }

    void execute() override {
        _snake->addLength((_multiply)?((_snake-1)->length()*_length):_length);
    }

    void undo(Snake* s) override {}

    void undo() override {}

    bool autoExecute() { return true; }

private:
    Snake* _snake;
    int _length;
    bool _multiply;
};
