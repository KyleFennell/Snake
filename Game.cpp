#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game(){}
Game::~Game(){}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen){
    Uint32 flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (window){
            std::cout << "Window created..." << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            std::cout << "Renderer created..." << std::endl;
        }
        std::cout << "SDL Initialised..." << std::endl;
        _running = true;
    }
    else {
        std::cout << "SDL Initialisation Failed..." << std::endl;
        _running = false;
    }

    _world = new World(50, 40);
}

void Game::handleEvents(){
    if (event.type == SDL_QUIT) {
        _running = false;
    }
    InputHandler::handleEvents();
}

void Game::update(){
    _world->update();
}

void Game::render(){
    SDL_RenderClear(renderer);
    _world->draw();
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "SDL Cleaned..." << std::endl;
}

