#pragma once

#include "Effect.h"

class Effect_Accelerate : public Effect{
public:
    Effect_Accelerate(Snake* s){
        _snake = s;
    }

    void execute(Snake* s) override {
        if (!_snake)
            _snake = s;
        execute();
    }


    void execute() override {
        std::cout << "executing acceleration" << std::endl;
        _snake->accelerate();
    }

    void undo() override {}

private:
    Snake* _snake;
};
