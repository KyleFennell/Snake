#pragma once

#include "Effect.h"

class Effect_Speed : public Effect{
public:
    Effect_Speed(Snake* s, int speed, bool multiply, int duration, bool autoExecute){
        _snake = s;
        _speed = speed;
        _multiply = multiply;
        _duration = duration;
        _autoExecute = autoExecute;
    }

    void execute(Snake* s) override {
        _snake = s;
        s->addSpeed((_multiply)?-(s->speed()/_speed):-(_speed));
    }

    void execute() override {
        _snake->addSpeed((_multiply)?-(_snake->speed()/_speed):-(_speed));
    }

    int duration(){ return _duration; }

    void undo() override {
        _snake->addSpeed((_multiply)?(_snake->speed()/_speed):(_speed));
    }

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
    int _speed;
    bool _multiply;
    int _duration;
    bool _autoExecute;
};
