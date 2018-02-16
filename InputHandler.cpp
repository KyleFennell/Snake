#include "InputHandler.h"

char InputHandler::_p1MovementKey = 's';
char InputHandler::_p1PowerupKey = ' ';

void InputHandler::handleEvents(){
    switch(Game::event.key.keysym.sym){
    case SDLK_ESCAPE:
        SDL_Event quit;
        quit.type = SDL_QUIT;
        SDL_PushEvent(&quit);
        break;
    case SDLK_w:
        _p1MovementKey = 'w';
        break;
    case SDLK_a:
        _p1MovementKey = 'a';
        break;
    case SDLK_s:
        _p1MovementKey = 's';
        break;
    case SDLK_d:
        _p1MovementKey = 'd';
        break;
    case SDLK_e:
        _p1PowerupKey = 'e';
        SDL_Event key;
        key.key.keysym.sym = SDLK_0;
        SDL_PushEvent(&key);
        break;
    default:
        break;
    }
}
