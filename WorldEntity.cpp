#include "WorldEntity.h"

bool WorldEntity::autoExecute(Snake* s){
    return _powerup->autoExecute(s);
}
