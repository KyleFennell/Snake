#pragma once

#include "Effect.h"

class Effect_Accelerate : public Effect{
public:
    Effect_Accelerate(Snake* s, bool autoExecute){
        _snake = s;
        _autoExecute = autoExecute;
    }

    void execute(Snake* s) override {
        _snake = s;
        s->accelerate();
    }

    void execute() override {
        _snake->accelerate();
    }

    void undo() override {}

private:
    Snake* _snake;
    bool _autoExecute;
};

