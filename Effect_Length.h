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
        if (!_snake)
            _snake = s;
        execute();
    }


    void execute() override {
//        std::cout << "executing length" << std::endl;
        _snake->addLength((_multiply)?(_snake->length()*(_length-1))-1:_length);
    }

    void undo() override {}

private:
    Snake* _snake;
    int _length;
    bool _multiply;
};
