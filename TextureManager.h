#pragma once
#include "SDL.h"
#include "Game.h"
#include "SDL_image.h"

class TextureHandler{
public:

    static SDL_Texture* loadTexture(const char* file){
        SDL_Surface* temp = IMG_Load(file);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, temp);
        SDL_FreeSurface(temp);
        return tex;
    }

    static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
        SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    }
};
