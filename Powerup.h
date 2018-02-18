#pragma once

#include "Effect.h"
#include "Snake.h"

class Snake;
class Effect;
class Powerup{
public:

    Powerup(){}
    Powerup(std::vector<Effect*> effects, bool autoExecute);
    bool autoExecute(Snake* s);
    void execute(Snake* s);
    void undo();
    void addEffect(Effect* e);
    int duration();


private:

    std::vector<Effect*> _effects;
    Snake* _snake = nullptr;
    bool _autoExecute;
};
