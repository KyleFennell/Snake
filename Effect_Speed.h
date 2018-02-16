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

    void execute(Snake* s) override {
        s->addSpeed((_multiply)?-(s->speed()/_speed):-(_speed));
    }

    void execute() override {
        _snake->addSpeed((_multiply)?-(_snake->speed()/_speed):-(_speed));
    }

    int duration(){ return _duration; }

    void undo(Snake* s) override {
        s->addSpeed((_multiply)?(s->speed()/_speed):(_speed));
    }

    void undo() override {
        _snake->addSpeed((_multiply)?(_snake->speed()/_speed):(_speed));
    }

    bool autoExecute() { return false; }

private:
    Snake* _snake;
    int _speed;
    bool _multiply;
    int _duration;
};
