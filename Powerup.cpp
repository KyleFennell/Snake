#include "Powerup.h"

Powerup::Powerup(std::vector<Effect*>effects, bool autoExecute){
    _effects =  effects;
    _autoExecute = autoExecute;
}

bool Powerup::autoExecute(Snake* s){
    if (_autoExecute){
        std::cout << "autoexecuting powerup" << std::endl;
        execute(s);
    }
    return _autoExecute;
}

void Powerup::execute(Snake* s){
    if (_snake){
        for (Effect* e : _effects){
            e->execute();
        }
    }
    else{
        for (Effect* e : _effects){
            e->execute(s);
        }
    }
}

void Powerup::undo(){

    for (Effect* e : _effects){
        e->undo();
    }
}

void Powerup::addEffect(Effect* e){
    _effects.push_back(e);
}

int Powerup::duration(){
    int duration = 0;
    for (Effect* e : _effects){
        if (e->duration() > duration){
            duration = e->duration();
        }
    }
    return duration;
}
