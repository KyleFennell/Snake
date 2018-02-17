#include "EntityFactory.h"

WorldEntity* EntityFactory::createEntity(Point p, int type, Snake* s){
    std::vector<Effect*> effects;
    switch (type){
    case 4:    // apple
        effects.push_back(new Effect_Lenth(s, 1, false, true));
        effects.push_back(new Effect_Accelerate(s, true));
        return new WorldEntity(p, type, new Powerup(effects, true), TextureManager::loadTexture("assets/food.png"));
        break;
    case 5:    // speed
        effects.push_back(new Effect_Speed(s, 2, true, 600, false));
        return new WorldEntity(p, type, new Powerup(effects, false), TextureManager::loadTexture("assets/speedUp.png"));
        break;
    case 6:
        effects.push_back(new Effect_Lenth(s, 2, true, true));
        effects.push_back(new Effect_Accelerate(s, true));
        return new WorldEntity(p, type, new Powerup(effects, true), TextureManager::loadTexture("assets/foodPile.png"));
        break;
    default:
        return nullptr;
    }
}
