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

void Snake::update(int worldW, int worldH){
    switch (InputHandler::key()){
    case 'w':
        add(head()+((head().y() != 0)?Point(0, -1):Point(0, worldH-1)));
        break;
    case 'a':
        add(head()+((head().x() != 0)?Point(-1, 0):Point(worldW-1, 0)));
        break;
    case 's':
        add(head()+((head().y() != worldH-1)?Point(0, 1):Point(0, -worldH+1)));
        break;
    case 'd':
        add(head()+((head().x() != worldW-1)?Point(1, 0):Point(-worldW+1, 0)));
        break;
    }
    std::cout << "head: " << head().x() << "," << head().y() << std::endl;
}

void Snake::add(Point p){
    _snake.insert(_snake.begin(), p);
}

void Snake::remove(){
    _snake.pop_back();
}
