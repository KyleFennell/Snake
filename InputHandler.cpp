#include "InputHandler.h"

char InputHandler::_key = 's';

void InputHandler::handleEvents(){
    switch(Game::event.key.keysym.sym){
    case SDLK_w:
        _key = 'w';
        break;
    case SDLK_a:
        _key = 'a';
        break;
    case SDLK_s:
        _key = 's';
        break;
    case SDLK_d:
        _key = 'd';
        break;
    }
}
