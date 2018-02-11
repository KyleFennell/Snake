#include "InputHandler.h"

char InputHandler::_key = 's';

void InputHandler::handleEvents(){
    switch(Game::event.key.keysym.sym){
    case SDLK_ESCAPE:
        SDL_Event quit;
        quit.type = SDL_QUIT;
        SDL_PushEvent(&quit);
        break;
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
    default:
        break;
    }
}
