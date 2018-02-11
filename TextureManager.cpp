#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* file){

    SDL_Surface* tempSurface = IMG_Load(file);
    //printf("IMG_Load: %s\n", IMG_GetError());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Manager::renderer, tempSurface);
    //printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Manager::renderer, tex, &src, &dest);
}

