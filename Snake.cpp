#include "Snake.h"

Snake::Snake(int x, int y){
    add(Point(x, y));
}

Snake::~Snake(){
    for (int i = 0; i < (int)_snake.size(); i++){
        delete &_snake[i];
    }
    delete &_snake;
}

void Snake::update(){
    switch (InputHandler::key()){
    case 'w':
        add(head()+Point(0, -1));
        break;
    case 'a':
        add(head()+Point(-1, 0));
        break;
    case 's':
        add(head()+Point(0, 1));
        break;
    case 'd':
        add(head()+Point(1, 0));
        break;
    }
}

void Snake::add(Point p){
    _snake.insert(_snake.begin(), p);
}

void Snake::remove(){
    _snake.pop_back();
}
