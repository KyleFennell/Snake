#pragma once

#include "Effect.h"
#include "Effect_Length.h"
#include "Effect_Speed.h"
#include "WorldEntity.h"
#include "Snake.h"
#include "TextureManager.h"

class EntityFactory{
public:
    static WorldEntity* createEntity(Point p, int type, Snake* s){
        switch (type){
        case 4:    // apple
            return new WorldEntity(p, type, new Effect_Lenth(s, 1, false), TextureManager::loadTexture("assets/food.png"));
        case 5:    // speed
            return new WorldEntity(p, type, new Effect_Speed(s, 2, true), TextureManager::loadTexture("assets/speedUp.png"));
        case 6:
            return new WorldEntity(p, type, new Effect_Lenth(s, 2, true), TextureManager::loadTexture("assets/foodPile.png"));
        }
        return nullptr;
    }
};
