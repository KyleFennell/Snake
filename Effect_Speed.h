#pragma once

#include "Effect.h"

class Effect_Speed : public Effect{
public:
    Effect_Speed(Snake* s, int speed, bool multiply, int duration){
        _snake = s;
        _speed = speed;
        _multiply = multiply;
        _duration = duration;
    }


    int duration(){ return _duration; }

    void undo() override {
//        std::cout << "undoing speed" << std::endl;
        _snake->addSpeed((_multiply)?(_snake->speed()/_speed):(_speed));
    }

    void execute(Snake* s) override {
        if (!_snake)
            _snake = s;
        execute();
    }

    void execute() override {
//        std::cout << "executing speed" << std::endl;
        _snake->addSpeed((_multiply)?-(_snake->speed()/_speed):-(_speed));
    }

private:
    Snake* _snake;
    int _speed;
    bool _multiply;
    int _duration;
};
