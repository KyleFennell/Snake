#pragma once

#include "Effect.h"
#include "Effect_Length.h"
#include "Effect_Speed.h"
#include "Effect_Accelerate.h"
#include "WorldEntity.h"
#include "Snake.h"
#include "TextureManager.h"

class EntityFactory{
public:
    static WorldEntity* createEntity(Point p, int type, Snake* s);
};
