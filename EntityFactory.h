#pragma once

#include "Effect.h"
#include "Effect_Length.h"
#include "Effect_Speed.h"
#include "WorldEntity.h"
#include "Snake.h"

class EntityFactory{
public:
    static WorldEntity* createEntity(Point p, int type, Snake* s){
        switch (type){
        case 2:
            return new WorldEntity(p, 2, new Effect_Lenth(s, 1, false));
        case 4:
            return new WorldEntity(p, 4, new Effect());
        case 5:
            return new WorldEntity(p, 5, new Effect_Speed(s, 2, true));
        }
        return nullptr;
    }
};
