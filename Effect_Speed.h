#pragma once

#include "Effect.h"

class Effect_Speed : public Effect{
public:
    Effect_Speed(Snake* s, int speed, bool multiply){
        _snake = s;
        _speed = speed;
        _multiply = multiply;
    }

    void execute(Snake* s) override {
        s->addSpeed((_multiply)?(s->speed()/_speed):(s->speed()-_speed));
    }

    void execute() override {
        _snake->addSpeed((_multiply)?(_snake->speed()/_speed):(_snake->speed()-_speed));
    }
private:
    Snake* _snake;
    int _speed;
    bool _multiply = false;
};
